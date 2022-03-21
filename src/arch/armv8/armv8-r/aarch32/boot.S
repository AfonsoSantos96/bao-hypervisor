/** 
 * Bao, a Lightweight Static Partitioning Hypervisor 
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Sandro Pinto <sandro@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details. 
 *
 */

#include <arch/bao.h>
#include <arch/sysregs.h>
#include <asm_defs.h>

.section ".boot", "ax"
.global boot_arch_profile_init
boot_arch_profile_init:

    /* Disable MPU and Caches */
    mrc p15, 4, r3, c1, c0, 0 // read HSCTLR
    bic r3, r3, #0x5 // disable MPU (M) and DCache (C)
    bic r3, r3, #0x1000 // disable ICache (I)
    dsb
    mrc p15, 4, r3, c1, c0, 0 // write HSCTLR
    isb

    // TODO - Set MPU hypervisor regions
    // ...

    /* Enable MMU and caches */
    mrc p15, 4, r3, c1, c0, 0 // read HSCTLR
    //orr r3, r3, #0x1 // enable MPU (M)
    orr r3, r3, #0x4 // enable DCache (C)
    orr r3, r3, #0x1000 // disable ICache (I)
    mrc p15, 4, r3, c1, c0, 0 // write HSCTLR
    dsb
    isb

/* In Armv8-R there is no virtual address space (VAS). Notwithstanding,  
 * we define VAS as an identity map of the PAS with MPU rules enforced 
 * using an equivalent "page size" of (at least) 64 bytes (minimal MPU 
 * granularity). 
 */
_enter_vas:

    bx lr

