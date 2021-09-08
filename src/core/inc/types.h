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

#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef signed long ssize_t;

#define HYP_ASID  0
typedef uint64_t asid_t;
typedef uint64_t vmid_t;

typedef uint64_t phys_addr_t;
typedef uint64_t virt_addr_t;

typedef uint64_t colormap_t;

typedef uint64_t cpuid_t;
typedef unsigned long cpumap_t;

#endif
