/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <sched.h>
#include <list.h>
#include <timer.h>
#include <objpool.h>
#include <config.h>
#include <vm.h>
#include <cpu.h>
#include <hypercall.h>
#include <redundancy.h>

void sched_init()
{

}

static inline timer_value_t sched_next_event_time(void) 
{
    // hardcoded 10 ms time slice
    return timer_arch_get_count() + TIME_MS(10);
}

static void sched_timer_event_handler(struct timer_event *timer_event);

static void sched_set_next_timer_event(void)
{
    struct timer_event *timer_event = &cpu()->sched.timer_event;
    timer_value_t timer = sched_next_event_time();
    timer_event_set(timer_event, timer, sched_timer_event_handler);
    timer_event_add(timer_event);
}

static void sched_next(void) {
    node_t *next_node = list_pop(&cpu()->vcpu_list);
    list_push(&cpu()->vcpu_list, next_node);
    struct vcpu *vcpu = CONTAINER_OF(struct vcpu, cpu_vcpu_list_node, next_node);
    cpu()->next_vcpu = vcpu;
}

void sched_monitor_next(void) {
    struct vcpu* aux;
    aux = cpu()->vcpu;
    cpu()->next_vcpu = cpu()->monitor_vcpu;
    cpu()->monitor_vcpu = aux;
    sched_set_next_timer_event();       // Timeout to vote
}

static void sched_timer_event_handler(struct timer_event *timer_event)
{
    (void)timer_event;

    if(cpu()->monitor_vcpu == NULL){
        sched_next();
        sched_set_next_timer_event();    // timeout for voting
        return;
    }

    unsigned long vcpu_hash = 0;
    
    data_hashing(cpu()->vcpu, sizeof(cpu()->vcpu->regs.x)/sizeof(long), &vcpu_hash);

    sched_monitor_next();

       /* Send number of voters on R9 */
    cpu()->vcpu->regs.x[9] = PLAT_CPU_NUM;

       /* Send vcpu hash result on R10 */
    cpu()->vcpu->regs.x[10] = vcpu_hash;

    sched_set_next_timer_event();    // Timeout to vote

}

void sched_yield()
{
    sched_timer_event_handler(NULL);
}

void sched_start() {
    sched_next();
    if (list_size(&cpu()->vcpu_list) > 1) {
        sched_set_next_timer_event();
    }
}

void sched_child(){
    sched_set_next_timer_event();
    sched_next();
}

long sched_hypercall(void)
{
    long res = HC_E_SUCCESS;

    sched_set_next_timer_event();
    sched_next();

    /**
     * If there is a new vcpu we need to check if its PSCI state is on. If not,
     * let's enter idle and wait for someaone to wake us up.
     * TODO: rewrite this check with an arch agnostic api
     */
    if (cpu()->vcpu->arch.psci_ctx.state == OFF) {
        cpu_idle();
    }

    return res;
}
