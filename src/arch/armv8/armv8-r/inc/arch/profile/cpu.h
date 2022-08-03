/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef ARCH_PROFILE_CPU_H
#define ARCH_PROFILE_CPU_H

#include <bao.h>
#include <arch/sysregs.h>
#include <bitmap.h>
#include <platform_defs.h>

struct cpu_arch_profile {
    // TODO: Declare the power-off state struct
    bitmap_t mem_p[PLAT_MP_ENTRIES];
};

struct cpuif_memprot {
    unsigned long base_addr;
    unsigned long size;
    unsigned long mem_flags;
    struct addr_space* as;
    struct cpu_synctoken* cpu_region_sync;
};

static inline struct cpu* cpu() {
    return (struct cpu*) sysreg_tpidr_el2_read();
}

void cpu_mem_prot_bitmap_init(struct cpu_arch_profile* mp);

#endif /* ARCH_PROFILE_CPU_H */
