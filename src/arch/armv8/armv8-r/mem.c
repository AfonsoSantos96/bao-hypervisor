/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <mem.h>
#include <cpu.h>
#include <arch/sysregs.h>
#include <mem_prot/mem.h>

// josecm : this has to be arch indenepdent?
struct memory_protection_dscr {
    size_t entries;
    size_t granularity;
} mp;

bool mem_translate(struct addr_space* as, vaddr_t va, paddr_t* pa)
{
    // josecm: TODO
    // if va exists in the as:
    //      *pa = va;
    //      return true
    return false;
}

static inline void mem_set_memory_struct()
{
    mp.granularity = PAGE_SIZE;
    mp.entries = MPUIR_REGION(sysreg_mpuir_el2_read());
}

void as_arch_init(struct addr_space* as)
{
    if (cpu()->id == CPU_MASTER){
        mem_set_memory_struct();
    }

    // josecm: missing cpu_sync?

    as->mem_prot_desc = &mp;
}

// josecm: shoulndt this both be architecture agnostic?
size_t mem_get_granularity()
{
    return mp.granularity; 
}

size_t mem_get_mp_entries()
{
    return cpu()->as.mem_prot_desc->entries;
}

void mem_read_physical_entry(struct memory_protection *mp_entry, unsigned long region)
{
    sysreg_prselr_el2_write(region);
    unsigned long prbar = sysreg_prbar_el2_read();
    unsigned long prlar = sysreg_prlar_el2_read();
    mp_entry->assigned = !!(prlar & PRLAR_EN);
    mp_entry->mem_flags.prbar = PRBAR_FLAGS(prbar);
    mp_entry->mem_flags.prlar = PRLAR_FLAGS(prlar);
    mp_entry->base_addr = PRBAR_BASE(prbar);
    mp_entry->size = (PRLAR_LIMIT(prlar) + 1) - mp_entry->base_addr;
}

static inline mpid_t get_region_by_addr(paddr_t addr)
{
    ssize_t reg_num;
    struct memory_protection region;

    for(reg_num = 0; reg_num < mem_get_mp_entries(); reg_num++) {
        if (bitmap_get(cpu()->arch.profile.mem_p, reg_num)) {
            mem_read_physical_entry(&region, reg_num);
            vaddr_t limit_addr = region.base_addr + region.size - 1;
            if(addr >= region.base_addr && addr <= limit_addr) {
                break;
            }
        }
    }
    
    if (reg_num >= mem_get_mp_entries()) {
        reg_num = INVALID_MPID;
    }

    return reg_num;
}

mpid_t get_available_physical_region()
{
    mpid_t reg_num = INVALID_MPID;
    for (mpid_t i = 0; i < mem_get_mp_entries(); i++) {
        if (bitmap_get(cpu()->arch.profile.mem_p, i) == 0) {
            reg_num = i;
            break;
        }
    }
    return reg_num;
}

// josecm: should be refactored in two functios
//     - get region id from addr
//     - free region by id
bool mem_free_physical_region(paddr_t addr)
{
    mpid_t reg_num = get_region_by_addr(addr);
    if(reg_num != INVALID_MPID) {
        bitmap_clear(cpu()->arch.profile.mem_p, reg_num);
        sysreg_prselr_el2_write(reg_num);
        sysreg_prlar_el2_write(0);
        sysreg_prbar_el2_write(0);
        return true;
    }

    return false;
}

// josecm: should receive a struct mpu_blabla
void mem_write_mp(paddr_t pa, size_t n, mem_flags_t flags)
{
    unsigned long lim = (pa + n - 1);
    mpid_t reg = get_available_physical_region();
    if (reg == INVALID_MPID) ERROR("No more available MPU regions.");
    bitmap_set(cpu()->arch.profile.mem_p, reg);
    sysreg_prselr_el2_write(reg);
    sysreg_prbar_el2_write((pa & PRBAR_BASE_MSK) | flags.prbar);
    sysreg_prlar_el2_write((lim & PRLAR_LIMIT_MSK) | flags.prlar);
}
