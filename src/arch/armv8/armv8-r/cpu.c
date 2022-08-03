/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <cpu.h>
#include <platform.h>

void cpu_arch_profile_init(cpuid_t cpuid, paddr_t load_addr) {

}

void cpu_mem_prot_bitmap_init(struct cpu_arch_profile* mp)
{
    if (PLAT_MP_ENTRIES > mem_get_mp_entries())
    {
        ERROR("Defined more entries on memory protection than available on hardware");
    }
    bitmap_clear_consecutive(mp->mem_p, 0, mem_get_mp_entries());
}

void cpu_arch_profile_idle() {
    asm volatile("wfi");
}

void cpu_wait_memprot_update(unsigned long cores){
    
    while (cpu()->interface->memprot.cpu_region_sync->n < cores)
    {
        cpu_msg_handler();
    }

}
