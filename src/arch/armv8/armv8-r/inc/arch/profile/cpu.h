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

#ifndef ARCH_PROFILE_CPU_H
#define ARCH_PROFILE_CPU_H

#include <bao.h>
#include <arch/sysregs.h>
#include <bitmap.h>

struct cpu_arch_profile {
    // TODO: Declare the power-off state struct
    bitmap_t* mem_p;
};

struct cpuif_memprot {
    unsigned long base_addr;
    unsigned long limit_addr;
    unsigned long mem_flags;
};

static inline struct cpu* cpu() {
    return (struct cpu*) sysreg_tpidr_el2_read();
}

void cpu_mem_prot_bitmap_init(struct cpu_arch_profile* mp);

#endif /* ARCH_PROFILE_CPU_H */
