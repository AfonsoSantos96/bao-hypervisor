/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      David Cerdeira <davidmcerdeira@gmail.com>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#include <ipc.h>

#include <cpu.h>
#include <vmm.h>
#include <hypercall.h>

enum {IPC_NOTIFY};

union ipc_msg_data {
    struct {
        unsigned char shmem_id;
        unsigned char event_id;
    };
<<<<<<< HEAD
    size_t raw;
} ipc_msg_data_t;
=======
    uint64_t raw;
};
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff

static size_t shmem_table_size;
static struct shmem *shmem_table;

<<<<<<< HEAD
shmem_t* ipc_get_shmem(size_t shmem_id) {
=======
struct shmem* ipc_get_shmem(size_t shmem_id) {
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
    if(shmem_id < shmem_table_size) {
        return &shmem_table[shmem_id];
    } else {
        return NULL;
    }
}

<<<<<<< HEAD
static ipc_t* ipc_find_by_shmemid(vm_t* vm, size_t shmem_id) {
=======
static struct ipc* ipc_find_by_shmemid(struct vm* vm, size_t shmem_id) {
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff

    struct ipc* ipc_obj = NULL;

<<<<<<< HEAD
    for(size_t i = 0; i < vm->ipc_num; i++) {
=======
    for (size_t i = 0; i < vm->ipc_num; i++) {
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
        if(vm->ipcs[i].shmem_id == shmem_id) {
            ipc_obj = &vm->ipcs[i];
            break;
        }
    }

    return ipc_obj;
}

static void ipc_notify(size_t shmem_id, size_t event_id) {
<<<<<<< HEAD
    ipc_t* ipc_obj = ipc_find_by_shmemid(cpu.vcpu->vm, shmem_id);
    if(ipc_obj != NULL && event_id < ipc_obj->interrupt_num) {
        size_t irq_id = ipc_obj->interrupts[event_id];
=======
    struct ipc* ipc_obj = ipc_find_by_shmemid(cpu.vcpu->vm, shmem_id);
    if(ipc_obj != NULL && event_id < ipc_obj->interrupt_num) {
        irqid_t irq_id = ipc_obj->interrupts[event_id];
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
        interrupts_vm_inject(cpu.vcpu->vm, irq_id);
    }
}

<<<<<<< HEAD
static void ipc_handler(uint32_t event, size_t data){
    ipc_msg_data_t ipc_data = { .raw = data };
=======
static void ipc_handler(uint32_t event, uint64_t data){
    union ipc_msg_data ipc_data = { .raw = data };
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
    switch(event){
        case IPC_NOTIFY: 
            ipc_notify(ipc_data.shmem_id, ipc_data.event_id);
        break;
    }
}
CPU_MSG_HANDLER(ipc_handler, IPC_CPUSMG_ID);

<<<<<<< HEAD
long ipc_hypercall(size_t arg0, size_t arg1, size_t arg2)
{
    size_t ipc_id = arg0;
    size_t ipc_event = arg1;
    long ret = -HC_E_SUCCESS;
=======
unsigned long ipc_hypercall(unsigned long ipc_id, unsigned long ipc_event, 
                                                unsigned long arg2)
{
    unsigned long ret = -HC_E_SUCCESS;
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff

    struct shmem *shmem = NULL; 
    bool valid_ipc_obj = ipc_id < cpu.vcpu->vm->ipc_num;
    if(valid_ipc_obj) {
        shmem = ipc_get_shmem(cpu.vcpu->vm->ipcs[ipc_id].shmem_id);
    }
    bool valid_shmem = shmem != NULL;

    if(valid_ipc_obj && valid_shmem) {

<<<<<<< HEAD
        size_t ipc_cpu_masters = shmem->cpu_masters & ~cpu.vcpu->vm->cpus;
=======
        cpumap_t ipc_cpu_masters = shmem->cpu_masters & ~cpu.vcpu->vm->cpus;
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff

        union ipc_msg_data data = {
            .shmem_id = cpu.vcpu->vm->ipcs[ipc_id].shmem_id,
            .event_id = ipc_event,
        };
        struct cpu_msg msg = {IPC_CPUSMG_ID, IPC_NOTIFY, data.raw};

        for (size_t i = 0; i < platform.cpu_num; i++) {
<<<<<<< HEAD
            if (ipc_cpu_masters & (1UL << i)) {
=======
            if (ipc_cpu_masters & (1ULL << i)) {
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
                cpu_send_msg(i, &msg);
            }
        }

    } else {
        ret = -HC_E_INVAL_ARGS;
    }

    return ret;
}

static void ipc_alloc_shmem() {
    for (size_t i = 0; i < shmem_table_size; i++) {
<<<<<<< HEAD
        shmem_t *shmem = &shmem_table[i];
=======
        struct shmem *shmem = &shmem_table[i];
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
        if(!shmem->place_phys) {
            size_t n_pg = NUM_PAGES(shmem->size);
            struct ppages ppages = mem_alloc_ppages(shmem->colors, n_pg, false);
            if(ppages.size < n_pg) {
                ERROR("failed to allocate shared memory");
            }
            shmem->phys = ppages.base;
        }
    }
}

static void ipc_setup_masters(const struct vm_config* vm_config, bool vm_master) {
    
    static spinlock_t lock = SPINLOCK_INITVAL;

<<<<<<< HEAD
    for(size_t i = 0; i < vm_config_ptr->shmemlist_size; i++) {
=======
    for (size_t i = 0; i < vm_config_ptr->shmemlist_size; i++) {
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
        vm_config_ptr->shmemlist[i].cpu_masters = 0;
    }

    cpu_sync_barrier(&cpu_glb_sync);

    if(vm_master) {
<<<<<<< HEAD
        for(size_t i = 0; i < vm_config->platform.ipc_num; i++) {
=======
        for (size_t i = 0; i < vm_config->platform.ipc_num; i++) {
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
            spin_lock(&lock);
            struct shmem *shmem = ipc_get_shmem(vm_config->platform.ipcs[i].shmem_id);
            if(shmem != NULL) {
                shmem->cpu_masters |= (1ULL << cpu.id);
            }
            spin_unlock(&lock);
        }
    }
}

void ipc_init(const struct vm_config* vm_config, bool vm_master) {

    shmem_table_size = vm_config_ptr->shmemlist_size;
    shmem_table = vm_config_ptr->shmemlist;
    
    if(cpu.id == CPU_MASTER) {
        ipc_alloc_shmem();
    }

    ipc_setup_masters(vm_config, vm_master);

}
