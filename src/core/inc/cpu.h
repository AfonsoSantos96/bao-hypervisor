/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __CPU_H__
#define __CPU_H__

#include <bao.h>
#include <arch/cpu.h>

#include <spinlock.h>
#include <mem.h>
#include <list.h>

#ifndef __ASSEMBLER__

struct cpuif {
    struct list event_list;
    struct cpuif_memprot memprot;
} __attribute__((aligned(PAGE_SIZE))) ;

struct vcpu;

struct cpu {
    cpuid_t id;
    
    struct addr_space as;

    struct vcpu* vcpu;

    struct cpu_arch arch;

    struct cpuif* interface;

    uint8_t stack[STACK_SIZE] __attribute__((aligned(PAGE_SIZE)));
    
} __attribute__((aligned(PAGE_SIZE)));
struct cpu_msg {
    uint32_t handler;
    uint32_t event;
    uint64_t data;
};

void cpu_send_msg(cpuid_t cpu, struct cpu_msg* msg);

typedef void (*cpu_msg_handler_t)(uint32_t event, uint64_t data);

#define CPU_MSG_HANDLER(handler, handler_id)                    \
    __attribute__((section(".ipi_cpumsg_handlers"), used))      \
        cpu_msg_handler_t __cpumsg_handler_##handler = handler; \
    __attribute__((section(".ipi_cpumsg_handlers_id"),          \
                   used)) volatile const size_t handler_id;

struct cpu_synctoken {
    spinlock_t lock;
    volatile size_t n;
    volatile bool ready;
    volatile size_t count;
};

extern struct cpu_synctoken cpu_glb_sync;

static inline void cpu_sync_init(struct cpu_synctoken* token, size_t n)
{
    token->lock = SPINLOCK_INITVAL;
    token->n = n;
    token->count = 0;
    token->ready = true;
}

static inline void cpu_sync_barrier(struct cpu_synctoken* token)
{
    // TODO: no fence/barrier needed in this function?

    size_t next_count = 0;

    while (!token->ready);

    spin_lock(&token->lock);
    token->count++;
    next_count = ALIGN(token->count, token->n);
    spin_unlock(&token->lock);

    while (token->count < next_count);
}

extern struct cpuif cpu_interfaces[];
static inline struct cpuif* cpu_if(cpuid_t cpu_id)
{
    return &cpu_interfaces[cpu_id];
}

void cpu_init(cpuid_t cpu_id, paddr_t load_addr);
void cpu_broadcast_init(struct addr_space *as);
void cpu_send_msg(cpuid_t cpu, struct cpu_msg* msg);
bool cpu_get_msg(struct cpu_msg* msg);
void cpu_msg_handler();
void cpu_msg_set_handler(cpuid_t id, cpu_msg_handler_t handler);
void cpu_idle();
void cpu_idle_wakeup();

void cpu_arch_init(cpuid_t cpu_id, paddr_t load_addr);
void cpu_arch_idle();

void cpu_sync_memprot();

#endif /* __ASSEMBLER__ */

#endif /* __CPU_H__ */
