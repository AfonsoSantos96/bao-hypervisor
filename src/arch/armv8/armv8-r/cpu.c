/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <cpu.h>
#include <platform.h>
#include <arch/gic.h>

void cpu_arch_profile_init(cpuid_t cpuid, paddr_t load_addr) {
    /*  Enable Interrupt Controller to send ipi during memory initialization */
    sysreg_icc_sre_el2_write(ICC_SRE_SRE_BIT | ICC_SRE_ENB_BIT);
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
