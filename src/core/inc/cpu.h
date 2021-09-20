/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      Sandro Pinto <sandro.pinto@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#ifndef __CPU_H__
#define __CPU_H__

#include <bao.h>
#include <arch/cpu.h>

#include <spinlock.h>
#include <mem.h>
#include <list.h>

#define STACK_SIZE (PAGE_SIZE)

#ifndef __ASSEMBLER__

extern unsigned char _cpu_if_base;

struct cpuif {
    struct list event_list;

} __attribute__((aligned(PAGE_SIZE))) ;

struct vcpu;

<<<<<<< HEAD
typedef struct cpu {
    size_t id;
    addr_space_t as;
=======
struct cpu {
    cpuid_t id;
    struct addr_space as;
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff

    struct vcpu* vcpu;

    struct cpu_arch arch;

<<<<<<< HEAD
    unsigned char root_pt[PT_SIZE] __attribute__((aligned(PT_SIZE)));
=======
    pte_t root_pt[PT_SIZE/sizeof(pte_t)] __attribute__((aligned(PT_SIZE)));
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff

    unsigned char stack[STACK_SIZE] __attribute__((aligned(PAGE_SIZE)));

    /******************* PUBLIC INTERFACE  **************************/

    struct cpuif interface __attribute__((aligned(PAGE_SIZE)));

} __attribute__((aligned(PAGE_SIZE)));

extern struct cpu cpu;

<<<<<<< HEAD
typedef struct {
    unsigned int handler;
    unsigned int event;
    size_t data;
} cpu_msg_t;

void cpu_send_msg(size_t cpu, cpu_msg_t* msg);
=======
struct cpu_msg {
    uint32_t handler;
    uint32_t event;
    uint64_t data;
};

void cpu_send_msg(cpuid_t cpu, struct cpu_msg* msg);
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff

typedef void (*cpu_msg_handler_t)(uint32_t event, size_t data);

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
<<<<<<< HEAD
} cpu_synctoken_t;
=======
};
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff

extern struct cpu_synctoken cpu_glb_sync;

<<<<<<< HEAD
static inline void cpu_sync_init(cpu_synctoken_t* token, size_t n)
=======
static inline void cpu_sync_init(struct cpu_synctoken* token, size_t n)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
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

<<<<<<< HEAD
static inline cpuif_t* cpu_if(size_t cpu_id)
=======
static inline struct cpuif* cpu_if(cpuid_t cpu_id)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    return (struct cpuif*)(((vaddr_t)&_cpu_if_base) +
           (cpu_id * ALIGN(sizeof(struct cpuif), PAGE_SIZE)));
}

<<<<<<< HEAD
void cpu_init(size_t cpu_id, size_t load_addr);
void cpu_send_msg(size_t cpu, cpu_msg_t* msg);
bool cpu_get_msg(cpu_msg_t* msg);
void cpu_msg_handler();
void cpu_msg_set_handler(size_t id, cpu_msg_handler_t handler);
void cpu_idle();
void cpu_idle_wakeup();

void cpu_arch_init(size_t cpu_id, size_t load_addr);
=======
void cpu_init(cpuid_t cpu_id, paddr_t load_addr);
void cpu_send_msg(cpuid_t cpu, struct cpu_msg* msg);
bool cpu_get_msg(struct cpu_msg* msg);
void cpu_msg_handler();
void cpu_msg_set_handler(cpuid_t id, cpu_msg_handler_t handler);
void cpu_idle();
void cpu_idle_wakeup();

void cpu_arch_init(cpuid_t cpu_id, paddr_t load_addr);
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
void cpu_arch_idle();

#endif /* __ASSEMBLER__ */

#endif /* __CPU_H__ */
