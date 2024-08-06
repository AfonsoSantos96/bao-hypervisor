/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <redundancy.h>
#include <string.h>
#include <config.h>
#include <sched.h>
#include <objpool.h>

#define GET_RESULT(val) (val & (1 << cpu()->id))
#define IS_CPU_SHEPPERD(val) (val == cpu()->id)

#define SHARED_CPU_STATE_POOL_SIZE_DEFAULT (128)
#ifndef SHARED_CPU_STATE_POOL_SIZE
#define SHARED_CPU_STATE_POOL_SIZE SHARED_CPU_STATE_POOL_SIZE_DEFAULT
#endif
OBJPOOL_ALLOC(shared_cpu_state_pool, struct checkpoint, SHARED_CPU_STATE_POOL_SIZE);

extern void mpu_monitor_vcpu_entry_enable();

void data_hashing(struct vcpu* vcpu, size_t count, unsigned long* hash){

    unsigned long sum1 = 0;
    unsigned long sum2 = 0;
    unsigned long size = ((long)-1);
    size = size >> (sizeof(long)*4);

    for(size_t index = 0; index < count; index++)
    {
        unsigned long adjusted_value = vcpu->regs.x[index];
        if(adjusted_value != 0){
            sum1 = (sum1 + adjusted_value) % (unsigned long) size;
            sum2 = (sum2 + sum1) % (unsigned long) size;
        }
    }
    sum2 = (sum2 << sizeof(cpu()->vcpu->regs.x)/sizeof(long));
    *hash = (sum2 | sum1);
}

static void redundancy_create_delta(struct checkpoint *delta){
    unsigned long *actual_vcpu = (unsigned long*)&cpu()->next_vcpu->regs;
    unsigned long *check_vcpu  = (unsigned long*)&cpu()->next_vcpu->check.regs;
    unsigned long *calc_delta  = (unsigned long*)&delta->regs;

    for (size_t i = 0; i < (sizeof(struct vcpu_arch)/sizeof(unsigned long)); i++){
        *calc_delta = *actual_vcpu - *check_vcpu;
        calc_delta++; actual_vcpu++; check_vcpu++;
    }

    actual_vcpu = (unsigned long*)&cpu()->next_vcpu->arch;
    check_vcpu  = (unsigned long*)&cpu()->next_vcpu->check.arch;
    calc_delta  = (unsigned long*)&delta->arch;
    for (size_t i = 0; i < (sizeof(struct arch_regs)/sizeof(unsigned long)); i++){
        *calc_delta = *actual_vcpu - *check_vcpu;
        calc_delta++; actual_vcpu++; check_vcpu++;
    }    
}

void redundancy_reset(struct vcpu* vcpu)
{
    vcpu_arch_init(vcpu, vcpu->vm);
    vcpu_arch_reset(vcpu, config.vmlist[vcpu->vm->id].entry);
    redundancy_checkpoint(vcpu);
}

void redundancy_checkpoint(struct vcpu* vcpu)
{
    memcpy(&vcpu->check.regs, &vcpu->regs, sizeof(struct arch_regs));
    memcpy(&vcpu->check.arch, &vcpu->arch, sizeof(struct vcpu_arch));
        //TODO: Store stack
    vcpu->check.rollback = false;
}

void redundancy_recovery(struct vcpu* vcpu)
{   
    // Add delta (fetched from the cpu interface) to the previous checkpoint
    struct cpu_msg msg;
    while(!cpu_get_msg(&msg));

    // Delta to recover registers is in msg
    unsigned long **delta = (unsigned long**)&msg.data;

    unsigned long *recovering_vcpu = (unsigned long*)&cpu()->next_vcpu->regs;
    unsigned long *prev_check_vcpu = (unsigned long*)&cpu()->next_vcpu->check.arch;

    for (size_t i = 0; i < (sizeof(struct vcpu_arch) / sizeof(unsigned long)); i++) {
        *recovering_vcpu = *prev_check_vcpu + **delta;
        recovering_vcpu++;
        prev_check_vcpu++;
        (*delta)++;
    }

    recovering_vcpu = (unsigned long*)&cpu()->next_vcpu->arch;
    prev_check_vcpu = (unsigned long*)&cpu()->next_vcpu->check.arch;
    
    for (size_t i = 0; i < (sizeof(struct arch_regs)/sizeof(unsigned long)); i++){
        *recovering_vcpu = *prev_check_vcpu + **delta;
        recovering_vcpu++;
        prev_check_vcpu++;
        (*delta)++;
    }   
}

void redundancy_rollback(struct vcpu* vcpu)
{
    if(vcpu->check.rollback == true){
        redundancy_reset(vcpu);
    }
    memcpy(&vcpu->regs, &vcpu->check.regs, sizeof(struct arch_regs));
    memcpy(&vcpu->arch, &vcpu->check.arch, sizeof(struct vcpu_arch));
    vcpu->check.rollback = true;
}

unsigned long redundancy_hypercall()
{
    unsigned long res = HC_E_SUCCESS;
    unsigned long vcpu_hash = 0;

    data_hashing(cpu()->vcpu, sizeof(cpu()->vcpu->regs.x)/sizeof(long), &vcpu_hash);

        /* Send vcpu hash result on R10 */
    cpu()->monitor_vcpu->regs.x[10] = vcpu_hash;
    
    sched_monitor_next();

    return res;
}

static void set_monitor_vcpu_next(void) {
    struct vcpu* temp;
        // Store the monitor vcpu address
    temp = cpu()->monitor_vcpu;
    cpu()->monitor_vcpu = cpu()->vcpu;
    cpu()->next_vcpu = temp;
}

unsigned long monitor_hypercall(long voting_result)
{
    unsigned long res = HC_E_SUCCESS;
    unsigned long faulty_votes = 0, correct_votes = 0;
    cpuid_t shepperd_cpu = 0;

    set_monitor_vcpu_next();

    for (size_t i = 0; i < PLAT_CPU_NUM; i++){
        unsigned long vote = (voting_result & (1 << i));
        if (vote){
            faulty_votes++;
        }else {
            correct_votes++;
            shepperd_cpu = i;
        }
    }
    // Check voting consensus. A roll-back must be triggered if monitors didn't reach an agreement
    if (faulty_votes >= correct_votes){
        redundancy_rollback(cpu()->next_vcpu);
    } else{ 

        switch(GET_RESULT(voting_result))
        {
            case 0: 
                struct checkpoint delta;
                if (faulty_votes){
                    // if there's any faulty VM, the delta must be created by the shepperd
                    if (voting_result && IS_CPU_SHEPPERD(shepperd_cpu)){
                        redundancy_create_delta(&delta);
                        while (faulty_votes--){
                            struct checkpoint* node = objpool_alloc(&shared_cpu_state_pool);
                            if (node == NULL) {
                                ERROR("Failed allocating shared region node");
                            }
                            *node = delta;

                            struct cpu_msg msg = { 
                                (unsigned long) NULL, 
                                (unsigned long) NULL, 
                                (uintptr_t)node };
                            size_t faulty_cpu = 
                                bitmap_find_nth((bitmap_t*) &voting_result, PLAT_CPU_NUM, 1, 0, true);
                            cpu_send_msg(faulty_cpu, &msg);
                        }
                    }
                }
                redundancy_checkpoint(cpu()->next_vcpu);
                break;

            case 1:
                redundancy_recovery(cpu()->next_vcpu);
                break;
        }
    }
    sched_child();
    cpu_sync_barrier(&cpu_glb_sync);
    return res;
}
