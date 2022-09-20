/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef ARCH_PROFILE_CPU_H
#define ARCH_PROFILE_CPU_H

#include <bao.h>
#include <arch/sysregs.h>
#include <bitmap.h>
#include <list.h>
#include <platform_defs.h>

struct cpu_arch_profile {
    // TODO: Declare the power-off state struct
    BITMAP_ALLOC(mem_p, PLAT_MP_ENTRIES);
};

struct cpuif_memprot {
    struct list shared_mem_prot;
};

static inline struct cpu* cpu() {
    return (struct cpu*) sysreg_tpidr_el2_read();
}

void cpu_mem_prot_bitmap_init(struct cpu_arch_profile* mp);

#endif /* ARCH_PROFILE_CPU_H */
