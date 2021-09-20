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

typedef struct cpu_arch {
    psci_off_state_t psci_off_state;
    size_t mpidr;
} cpu_arch_t;

size_t cpu_id_to_mpidr(size_t id);
long cpu_mpidr_to_id(size_t mpdir);

extern size_t CPU_MASTER;

#endif /* __ARCH_CPU_H__ */
