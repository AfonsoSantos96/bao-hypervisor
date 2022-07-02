/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __MEM_PROT_H__
#define __MEM_PROT_H__

#include <bao.h>
#include <arch/mem.h>

enum AS_TYPE { AS_HYP = 0, AS_VM, AS_HYP_CPY };

struct addr_space {
    enum AS_TYPE type;
    colormap_t colors;
};

typedef unsigned long long mem_flags_t;

#endif /* __MEM_PROT_H__ */
