/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#include <mem.h>
#include <cpu.h>
#include <arch/sysregs.h>
#include <arch/fences.h>

void as_arch_init(struct addr_space* as)
{
    size_t index;

    /*
     * If the address space is a copy of an existing hypervisor space it's not
     * possible to use the PT_CPU_REC index to navigate it, so we have to use
     * the PT_VM_REC_IND.
     */
    if (as->type == AS_HYP_CPY || as->type == AS_VM) {
        index = PT_VM_REC_IND;
    } else {
        index = PT_CPU_REC_IND;
    }
    pt_set_recursive(&as->pt, index);
}

bool mem_translate(struct addr_space* as, vaddr_t va, paddr_t* pa)
{
    uint64_t par = 0, par_saved = 0;

    /**
     * TODO: are barriers needed in this operation?
     */

    par_saved = sysreg_par_el1_read();

    if (as->type == AS_HYP || as->type == AS_HYP_CPY)
        arm_at_s1e2w(va);
    else
        arm_at_s12e1w(va);

    ISB();
    par = sysreg_par_el1_read();
    sysreg_par_el1_write(par_saved);
    if (par & PAR_F) {
        return false;
    } else {
        if (pa != NULL)
            *pa = (par & PAR_PA_MSK) | (va & (PAGE_SIZE - 1));
        return true;
    }
}
