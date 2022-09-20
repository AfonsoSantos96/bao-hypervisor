/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_MEM_H__
#define __ARCH_MEM_H__

#include <bao.h>
#include <arch/sysregs.h>

typedef union {
    unsigned long raw;
    struct {
        uint16_t prbar;
        uint16_t prlar;
    };
} mem_flags_t;

#define PTE_FLAGS(_prbar, _prlar) ((mem_flags_t) { \
    .prbar = (_prbar), \
    .prlar = (_prlar), \
} )

#define PTE_INVALID PTE_FLAGS(0, 0)
#define PTE_HYP_FLAGS \
    PTE_FLAGS(PRBAR_AP_RW_EL2 | PRBAR_SH_IS, PRLAR_ATTR(1) | PRLAR_EN)
#define PTE_HYP_DEV_FLAGS \
    PTE_FLAGS(PRBAR_AP_RW_EL2 | PRBAR_SH_IS, PRLAR_ATTR(2) | PRLAR_EN)
#define PTE_VM_FLAGS \
    PTE_FLAGS(PRBAR_AP_RW_EL1_EL2 | PRBAR_SH_IS, PRLAR_ATTR(1) | PRLAR_EN)
#define PTE_VM_DEV_FLAGS PTE_VM_FLAGS

#endif /* __ARCH_MEM_H__ */
