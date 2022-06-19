/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Sandro Pinto <sandro@bao-project.org>
 *      Afonso Santos <afomms@gmail.com>
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
#include <mem_prot/mem.h>

#define PRIO_ORDER          NO_PRIORITY
#define MP_GRANULARITY      PAGE_SIZE

struct memory_protection_dscr{
    unsigned long entries;
    unsigned long granularity;
    unsigned long priority_order;
}mp;

bool mem_translate(struct addr_space* as, vaddr_t va, paddr_t* pa)
{
    return false;
}

void mem_attributes_init()
{
    // TODO: Init mem attributes on HMAIR0 and HMAIR1
}

static inline void mem_set_memory_struct()
{
    mp.granularity = MP_GRANULARITY;
    mp.priority_order = PRIO_ORDER;
    mp.entries = (sysreg_hmpuir_read() & HMPUIR_REGIONS);
}

void as_arch_init(struct addr_space* as)
{
    if (cpu()->id == CPU_MASTER){
        mem_attributes_init();
        mem_set_memory_struct();
    }
    as->mem_prot_desc = &mp;
}

unsigned long mem_get_granularity()
{
    return PAGE_SIZE;
}

unsigned long mem_get_mp_entries()
{
    return cpu()->as.mem_prot_desc->entries;
}

