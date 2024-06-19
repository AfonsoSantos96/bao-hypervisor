/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef VM_SUBARCH_H
#define VM_SUBARCH_H

#include <bao.h>
#include <vfp.h>
#include <mem.h>

struct mpu_regs {
    unsigned long prbar[MPU_EL1_ARCH_MAX_NUM_ENTRIES];
    unsigned long prlar[MPU_EL1_ARCH_MAX_NUM_ENTRIES];
};


struct arch_regs {
    uint32_t elr_hyp;
    uint32_t spsr_hyp;
    uint32_t x[15];

    uint32_t usr_regs[5];
    uint32_t fiq_regs[5];
    uint32_t spsr_regs[5];
    uint32_t sp_regs[6];
    uint32_t lr_regs[5];
        
    uint32_t elr_el1;
    uint32_t sctlr_el1;
    uint32_t vbar_el1;
    uint64_t mair_el1;
    uint64_t par_el1;
    uint64_t far_el1;
    uint32_t esr_el1;     // dfsr_el1
    uint32_t cpacr_el1;
    uint32_t contextidr_el1;
    uint32_t tpidr_el0;   // tpidrurw
    uint32_t tpidrro_el0; // tpidruro
    uint32_t tpidr_el1;   // tpidrprw
    uint32_t csselr_el1;
    uint32_t vmpidr_el2;
    uint32_t cptr_el2;

    struct mpu_regs mpu_regs_el1;
    struct vfp vfp;
};

#endif /* VM_SUBARCH_H */
