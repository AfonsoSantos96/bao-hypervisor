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

void interrupts_arch_ipi_send(cpuid_t target_cpu, unsigned long ipi_id)
{
    if (ipi_id < GIC_MAX_SGIS) gic_send_sgi(target_cpu, ipi_id);
}

void interrupts_arch_enable(unsigned long int_id, bool en)
{
    gic_set_enable(int_id, en);
    gic_set_prio(int_id, 0x01);
    if (GIC_VERSION == GICV2) {
        gicd_set_trgt(int_id, 1 << cpu.id);
    } else {
        gicd_set_route(int_id, cpu.arch.mpidr);
    }
}

bool interrupts_arch_check(unsigned long int_id)
{
    return gic_get_pend(int_id);
}

inline bool interrupts_arch_conflict(bitmap_t interrupt_bitmap, unsigned long int_id)
{
    return (bitmap_get(interrupt_bitmap, int_id) && int_id > GIC_CPU_PRIV);
}

void interrupts_arch_clear(unsigned long int_id)
{
    gic_set_act(int_id, false);
    gic_set_pend(int_id, false);
}

void interrupts_arch_vm_assign(vm_t *vm, unsigned long id)
{
    vgic_set_hw(vm, id);
}

void interrupts_arch_vm_inject(vm_t *vm, unsigned long id)
{
    vgic_inject(&vm->arch.vgicd, id, cpu.vcpu->id);
}
