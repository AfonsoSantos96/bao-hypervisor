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

mpid_t sort_reg_num()
{
    unsigned long _temp = 0;
    asm volatile ("mov %0, r7 \n\r": "=r"(_temp));
    return (_temp % cpu()->as.mem_prot_desc->entries);
}

mpid_t get_region_num(paddr_t addr)
{
    ssize_t reg_num = 0;
    unsigned long region_base_addr = 0;
    unsigned long region_limit_addr = 0;
    while(bitmap_get(cpu()->arch.profile.mem_p, reg_num) ||
            reg_num<cpu()->as.mem_prot_desc->entries)
    {
        sysreg_hprselr_write(reg_num);
        region_base_addr = GET_REGION_BASE_ADDRESS(sysreg_hprbar_read());
        region_limit_addr = GET_REGION_LIMIT_ADDRESS(sysreg_hprlar_read());
        if(addr >= region_base_addr || addr <= region_limit_addr) break;
        reg_num++;
    }
    if (reg_num<cpu()->as.mem_prot_desc->entries) reg_num = -1;
    return reg_num;
}

mpid_t get_available_physical_region()
{
    mpid_t reg_num = 0;
    unsigned long status = 0;
    while(reg_num<cpu()->as.mem_prot_desc->entries || !status)
    {
        if (!bitmap_get(cpu()->arch.profile.mem_p, reg_num)) status = 1;
        reg_num++;
    }
    if (!status) reg_num = -1;
    return (--reg_num);
}

void mem_free_physical_region(paddr_t addr)
{
    mpid_t reg_num = get_region_num(addr);
    bitmap_clear(cpu()->arch.profile.mem_p, reg_num);
    sysreg_hprselr_write(reg_num);
    sysreg_hprbar_write(0);
    sysreg_hprlar_write(0);
}

void mem_write_mp(paddr_t pa, size_t n, mem_flags_t flags)
{
    unsigned long lim = (pa+n);
    mpid_t reg = get_available_physical_region();
    if (reg == -1) reg = sort_reg_num();
    bitmap_set(cpu()->arch.profile.mem_p, reg);
    sysreg_hprselr_write(reg);
    sysreg_hprbar_write(ADDR_OFFSET(pa) || HPRBAR_CONF(flags));
    sysreg_hprlar_write(ADDR_OFFSET(lim) || HPRLAR_CONF(flags) || ENABLE_MASK);
}
