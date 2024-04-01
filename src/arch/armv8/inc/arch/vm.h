/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_VM_H__
#define __ARCH_VM_H__

#include <bao.h>
#include <arch/subarch/vm.h>
#include <arch/vgic.h>
#include <arch/psci.h>
#include <vtimer.h>
#ifdef MEM_PROT_MMU
#include <arch/smmuv2.h>
#endif
#include <list.h>

struct arch_vm_platform {
    struct vgic_dscrp {
        paddr_t gicd_addr;
        paddr_t gicc_addr;
        paddr_t gicr_addr;
        size_t interrupt_num;
    } gic;

#ifdef MEM_PROT_MMU
    struct {
        streamid_t global_mask;
        size_t group_num;
        struct smmu_group {
            streamid_t mask;
            streamid_t id;
        }* groups;
    } smmu;
#endif
};

struct vm_arch {
    struct vgic vgic;
#ifdef MEM_PROT_MMU
    unsigned long vttbr_el2;
#endif
};

struct vcpu_arch {
    unsigned long vmpidr;
    struct vgic_priv vgic_priv;
    struct psci_ctx psci_ctx;
    struct vtimer vtimer;
};

struct vcpu* vm_get_vcpu_by_mpidr(struct vm* vm, unsigned long mpidr);
void vcpu_arch_entry();

bool vcpu_arch_profile_on(struct vcpu* vcpu);
void vcpu_arch_profile_init(struct vcpu* vcpu, struct vm* vm);
void vcpu_arch_profile_save_state(struct vcpu* vcpu);
void vcpu_arch_profile_restore_state(struct vcpu* vcpu);
void vcpu_subarch_reset(struct vcpu* vcpu);

static inline void vcpu_arch_inject_hw_irq(struct vcpu* vcpu, irqid_t id)
{
    vgic_inject_hw(vcpu, id);
}

static inline void vcpu_arch_inject_irq(struct vcpu* vcpu, irqid_t id)
{
    vgic_inject(vcpu, id, 0);
}

#endif /* __ARCH_VM_H__ */
