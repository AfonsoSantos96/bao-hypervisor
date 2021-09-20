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

#include <bao.h>
#include <interrupts.h>

#include <cpu.h>
#include <platform.h>
#include <arch/gic.h>
#include <mem.h>
#include <arch/sysregs.h>
#include <vm.h>

#ifndef GIC_VERSION
#error "GIC_VERSION not defined for this platform"
#endif

void interrupts_arch_init()
{
    gic_init();
    interrupts_cpu_enable(platform.arch.gic.maintenance_id, true);
}

<<<<<<< HEAD
void interrupts_arch_ipi_send(size_t target_cpu, size_t ipi_id)
=======
void interrupts_arch_ipi_send(cpuid_t target_cpu, irqid_t ipi_id)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    if (ipi_id < GIC_MAX_SGIS) gic_send_sgi(target_cpu, ipi_id);
}

<<<<<<< HEAD
void interrupts_arch_enable(size_t int_id, bool en)
=======
void interrupts_arch_enable(irqid_t int_id, bool en)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    gic_set_enable(int_id, en);
    gic_set_prio(int_id, 0x01);
    if (GIC_VERSION == GICV2) {
        gicd_set_trgt(int_id, 1 << cpu.id);
    } else {
        gicd_set_route(int_id, cpu.arch.mpidr);
    }
}

<<<<<<< HEAD
bool interrupts_arch_check(size_t int_id)
=======
bool interrupts_arch_check(irqid_t int_id)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    return gic_get_pend(int_id);
}

<<<<<<< HEAD
inline bool interrupts_arch_conflict(bitmap_t interrupt_bitmap, size_t int_id)
=======
inline bool interrupts_arch_conflict(bitmap_t* interrupt_bitmap, irqid_t int_id)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    return (bitmap_get(interrupt_bitmap, int_id) && int_id > GIC_CPU_PRIV);
}

<<<<<<< HEAD
void interrupts_arch_clear(size_t int_id)
=======
void interrupts_arch_clear(irqid_t int_id)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    gic_set_act(int_id, false);
    gic_set_pend(int_id, false);
}

<<<<<<< HEAD
void interrupts_arch_vm_assign(vm_t *vm, size_t id)
=======
void interrupts_arch_vm_assign(struct vm *vm, irqid_t id)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    vgic_set_hw(vm, id);
}

<<<<<<< HEAD
void interrupts_arch_vm_inject(vm_t *vm, size_t id)
=======
void interrupts_arch_vm_inject(struct vm *vm, irqid_t id)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    vgic_inject(&vm->arch.vgicd, id, cpu.vcpu->id);
}
