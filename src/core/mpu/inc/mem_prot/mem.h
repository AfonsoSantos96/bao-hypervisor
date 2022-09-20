/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __MEM_PROT_H__
#define __MEM_PROT_H__

#include <bao.h>
#include <arch/mem.h>

#define HYP_ASID  0
#define MPU_ABST_ENTRIES  64

enum AS_TYPE { AS_HYP = 0, AS_VM, AS_HYP_CPY };

struct memory_protection{
    bool assigned;
    unsigned long base_addr;
    unsigned long limit_addr;
    unsigned long mem_flags;
};

struct addr_space {
    enum AS_TYPE type;
    colormap_t colors;
    struct memory_protection mem_prot[MPU_ABST_ENTRIES];
    struct memory_protection_dscr* mem_prot_desc;
};

typedef unsigned long long mem_flags_t;

void as_init(struct addr_space* as, enum AS_TYPE type,
            colormap_t colors);
unsigned long mem_get_mp_entries();
void mem_attributes_init();

#endif /* __MEM_PROT_H__ */
