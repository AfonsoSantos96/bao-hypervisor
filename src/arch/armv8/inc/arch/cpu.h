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

#ifndef __ARCH_CPU_H__
#define __ARCH_CPU_H__

#include <bao.h>
#include <arch/psci.h>

#define CPU_MAX (8UL)

<<<<<<< HEAD
typedef struct cpu_arch {
    psci_off_state_t psci_off_state;
    size_t mpidr;
} cpu_arch_t;

size_t cpu_id_to_mpidr(size_t id);
long cpu_mpidr_to_id(size_t mpdir);

extern size_t CPU_MASTER;
=======
struct cpu_arch {
    struct psci_off_state psci_off_state;
    unsigned long mpidr;
};

unsigned long cpu_id_to_mpidr(cpuid_t id);

extern cpuid_t CPU_MASTER;
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff

#endif /* __ARCH_CPU_H__ */
