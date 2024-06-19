/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef ARCH_VFP_H
#define ARCH_VFP_H

#include <types.h>

#define VFP_NUM_REGS    (31)

struct vfp_reg {

} __attribute__((aligned(16)));

struct vfp {

};

void vfp_reset(struct vfp* vfp);
void vfp_save_state(struct vfp* vfp);
void vfp_restore_state(struct vfp* vfp);

#endif /* ARCH_VFP_H */
