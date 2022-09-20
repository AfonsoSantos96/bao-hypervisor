/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __MEM_PROT_H__
#define __MEM_PROT_H__

#include <bao.h>
#include <bitmap.h>
#include <arch/mem.h>

#define HYP_ASID  0
#define MPU_ABST_ENTRIES  64

enum AS_TYPE { AS_HYP = 0, AS_VM, AS_HYP_CPY };
enum {MP_MSG_REGION};

struct memory_protection {
    bool assigned;
    vaddr_t base_addr;
    size_t size;
    mem_flags_t mem_flags;
};

struct addr_space {
    asid_t id;
    enum AS_TYPE type;
    colormap_t colors;
    struct memory_protection mem_prot[MPU_ABST_ENTRIES];
    struct memory_protection_dscr* mem_prot_desc;
};

void as_init(struct addr_space* as, enum AS_TYPE type,
            colormap_t colors);
size_t mem_get_mp_entries();
void mem_attributes_init();
void mem_set_shared_region(vaddr_t va, size_t n, mem_flags_t flags);

#endif /* __MEM_PROT_H__ */
