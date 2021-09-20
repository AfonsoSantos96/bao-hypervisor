/** 
 * Bao, a Lightweight Static Partitioning Hypervisor 
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details. 
 *
 */

#ifndef __ARCH_VM_H__
#define __ARCH_VM_H__

#include <bao.h>
#include <arch/vgic.h>
#include <arch/psci.h>

struct vm_arch {
    struct vgicd vgicd;
    vaddr_t vgicr_addr;
};

<<<<<<< HEAD
typedef struct {
    size_t vmpidr;
    vgic_priv_t vgic_priv;
    psci_ctx_t psci_ctx;
} vcpu_arch_t;
=======
struct vcpu_arch {
    unsigned long vmpidr;
    struct vgic_priv vgic_priv;
    struct psci_ctx psci_ctx;
};
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff

struct arch_regs {
    size_t x[31];
    size_t elr_el2;
    size_t spsr_el2;
} __attribute__((aligned(16)));  // makes size always aligned to 16 to respect
                                 // stack alignment

<<<<<<< HEAD
vcpu_t* vm_get_vcpu_by_mpidr(vm_t* vm, size_t mpidr);
=======
struct vcpu* vm_get_vcpu_by_mpidr(struct vm* vm, unsigned long mpidr);
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
void vcpu_arch_entry();


#endif /* __ARCH_VM_H__ */
