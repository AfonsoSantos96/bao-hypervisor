/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      Angelo Ruocco <angeloruocco90@gmail.com>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#include <interrupts.h>

#include <cpu.h>
#include <vm.h>
#include <bitmap.h>
#include <string.h>

BITMAP_ALLOC(hyp_interrupt_bitmap, MAX_INTERRUPTS);
BITMAP_ALLOC(global_interrupt_bitmap, MAX_INTERRUPTS);

irq_handler_t interrupt_handlers[MAX_INTERRUPTS];

<<<<<<< HEAD
inline void interrupts_cpu_sendipi(size_t target_cpu, size_t ipi_id)
=======
inline void interrupts_cpu_sendipi(cpuid_t target_cpu, irqid_t ipi_id)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    interrupts_arch_ipi_send(target_cpu, ipi_id);
}

<<<<<<< HEAD
inline void interrupts_cpu_enable(size_t int_id, bool en)
=======
inline void interrupts_cpu_enable(irqid_t int_id, bool en)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    interrupts_arch_enable(int_id, en);
}

<<<<<<< HEAD
inline bool interrupts_check(size_t int_id)
=======
inline bool interrupts_check(irqid_t int_id)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    return interrupts_arch_check(int_id);
}

<<<<<<< HEAD
inline void interrupts_clear(size_t int_id)
=======
inline void interrupts_clear(irqid_t int_id)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    interrupts_arch_clear(int_id);
}

inline void interrupts_init()
{
    interrupts_arch_init();

    if (cpu.id == CPU_MASTER) {
        interrupts_reserve(IPI_CPU_MSG, cpu_msg_handler);
    }

    interrupts_cpu_enable(IPI_CPU_MSG, true);
}

<<<<<<< HEAD
static inline bool interrupt_is_reserved(size_t int_id)
=======
static inline bool interrupt_is_reserved(irqid_t int_id)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    return bitmap_get(hyp_interrupt_bitmap, int_id);
}

<<<<<<< HEAD
inline void interrupts_vm_inject(vm_t *vm, size_t id)
=======
inline void interrupts_vm_inject(struct vm *vm, irqid_t id)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    interrupts_arch_vm_inject(vm, id);
}

<<<<<<< HEAD
enum irq_res interrupts_handle(size_t int_id)
=======
enum irq_res interrupts_handle(irqid_t int_id)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    if (vm_has_interrupt(cpu.vcpu->vm, int_id)) {
        interrupts_vm_inject(cpu.vcpu->vm, int_id);

        return FORWARD_TO_VM;

    } else if (interrupt_is_reserved(int_id)) {
        interrupt_handlers[int_id](int_id);

        return HANDLED_BY_HYP;

    } else {
        ERROR("received unknown interrupt id = %d", int_id);
    }
}

<<<<<<< HEAD
void interrupts_vm_assign(vm_t *vm, size_t id)
=======
void interrupts_vm_assign(struct vm *vm, irqid_t id)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    if (interrupts_arch_conflict(global_interrupt_bitmap, id)) {
        ERROR("Interrupts conflict, id = %d\n", id);
    }

    interrupts_arch_vm_assign(vm, id);

    bitmap_set(vm->interrupt_bitmap, id);
    bitmap_set(global_interrupt_bitmap, id);
}

<<<<<<< HEAD
void interrupts_reserve(size_t int_id, irq_handler_t handler)
=======
void interrupts_reserve(irqid_t int_id, irq_handler_t handler)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    if (int_id < MAX_INTERRUPTS) {
        interrupt_handlers[int_id] = handler;
        bitmap_set(hyp_interrupt_bitmap, int_id);
        bitmap_set(global_interrupt_bitmap, int_id);
    }
}
