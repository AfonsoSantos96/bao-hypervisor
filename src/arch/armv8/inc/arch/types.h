/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2021-
 *
 * Authors:
 *      Aras Ashraf Gandomi <aras.ashrafgandomi2@unibo.it>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#ifndef __ARCH_TYPES_H__
#define __ARCH_TYPES_H__

#include <stdint.h>

typedef uint64_t phys_addr_t;
typedef uint64_t ctx_id_t;
typedef uint64_t pt_lvl_t;
typedef uint64_t pte_flag_t;
typedef uint64_t pte_type_t;
typedef uint64_t cpuid_t;

#endif /* __ARCH_TYPES_H__ */