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

#include <vm.h>
#include <page_table.h>
#include <arch/sysregs.h>
#include <fences.h>
#include <arch/tlb.h>
#include <string.h>

void vm_arch_init(struct vm* vm, const struct vm_config* config)
{
    if (vm->master == cpu.id) {
        vgic_init(vm, &config->platform.arch.gic);
    }
}

struct vcpu* vm_get_vcpu_by_mpidr(struct vm* vm, unsigned long mpidr)
{
    list_foreach(vm->vcpu_list, struct vcpu, vcpu)
    {
        if ((vcpu->arch.vmpidr & MPIDR_AFF_MSK) == (mpidr & MPIDR_AFF_MSK))  {
            return vcpu;
        }
    }

    return NULL;
}

<<<<<<< HEAD
static size_t vm_cpuid_to_mpidr(vm_t* vm, size_t cpuid)
=======
static unsigned long vm_cpuid_to_mpidr(struct vm* vm, cpuid_t cpuid)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    return platform_arch_cpuid_to_mpdir(&vm->config->platform, cpuid);
}

void vcpu_arch_init(struct vcpu* vcpu, struct vm* vm)
{
    vcpu->arch.vmpidr = vm_cpuid_to_mpidr(vm, vcpu->id);
    MSR(VMPIDR_EL2, vcpu->arch.vmpidr);

    vcpu->arch.psci_ctx.state = vcpu->id == 0 ? ON : OFF;

<<<<<<< HEAD
    size_t root_pt_pa;
    mem_translate(&cpu.as, vm->as.pt.root, &root_pt_pa);
=======
    paddr_t root_pt_pa;
    mem_translate(&cpu.as, (vaddr_t)vm->as.pt.root, &root_pt_pa);
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
    MSR(VTTBR_EL2, ((vm->id << VTTBR_VMID_OFF) & VTTBR_VMID_MSK) |
                       (root_pt_pa & ~VTTBR_VMID_MSK));

    ISB();  // make sure vmid is commited befor tlbi
    tlb_vm_inv_all(vm->id);

    vgic_cpu_init(vcpu);
}

<<<<<<< HEAD
void vcpu_arch_reset(vcpu_t* vcpu, size_t entry)
=======
void vcpu_arch_reset(struct vcpu* vcpu, vaddr_t entry)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    memset(vcpu->regs, 0, sizeof(struct arch_regs));

    vcpu->regs->elr_el2 = entry;
    vcpu->regs->spsr_el2 = SPSR_EL1h | SPSR_F | SPSR_I | SPSR_A | SPSR_D;

    MSR(CNTVOFF_EL2, 0);

    /**
     *  See ARMv8-A ARM section D1.9.1 for registers that must be in a known
     * state at reset.
     */
    MSR(SCTLR_EL1, SCTLR_RES1);
    MSR(CNTKCTL_EL1, 0);
    MSR(PMCR_EL0, 0);

    /**
     *  TODO: ARMv8-A ARM mentions another implementation optional registers
     * that reset to a known value.
     */
}

<<<<<<< HEAD
size_t vcpu_readreg(vcpu_t* vcpu, size_t reg)
=======
unsigned long vcpu_readreg(struct vcpu* vcpu, unsigned long reg)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    if (reg > 30) return 0;
    return vcpu->regs->x[reg];
}

<<<<<<< HEAD
void vcpu_writereg(vcpu_t* vcpu, size_t reg, size_t val)
=======
void vcpu_writereg(struct vcpu* vcpu, unsigned long reg, unsigned long val)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    if (reg > 30) return;
    vcpu->regs->x[reg] = val;
}

<<<<<<< HEAD
size_t vcpu_readpc(vcpu_t* vcpu)
=======
unsigned long vcpu_readpc(struct vcpu* vcpu)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    return vcpu->regs->elr_el2;
}

<<<<<<< HEAD
void vcpu_writepc(vcpu_t* vcpu, size_t pc)
=======
void vcpu_writepc(struct vcpu* vcpu, unsigned long pc)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    vcpu->regs->elr_el2 = pc;
}

bool vm_readmem(struct vm* vm, void* dest, vaddr_t vmaddr, size_t n)
{
    // TODO

    return false;
}

void vcpu_arch_run(struct vcpu* vcpu)
{
    // TODO: consider using TPIDR_EL2 to store vcpu pointer
    if (vcpu->arch.psci_ctx.state == ON) {
        vcpu_arch_entry();
    } else {
        cpu_idle();
    }
    
}
