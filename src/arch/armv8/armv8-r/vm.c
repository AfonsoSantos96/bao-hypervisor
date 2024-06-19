/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vm.h>
#include <config.h>
#include <arch/sysregs.h>

static inline size_t mpu_num_el1_entries()
{
    return (size_t)MPUIR_EL1_REGION(sysreg_mpuir_el1_read());
}

void vcpu_arch_profile_init(struct vcpu* vcpu, struct vm* vm)
{
    sysreg_vsctlr_el2_write((vm->id << VSCTLR_EL2_VMID_OFF) & VSCTLR_EL2_VMID_MSK);

    if (DEFINED(MEM_PROT_MPU) && DEFINED(AARCH64) && vm->config->platform.mmu) {
        uint64_t vtcr = VTCR_MSA;
        sysreg_vtcr_el2_write(vtcr);
    }
}

void vcpu_arch_profile_save_state(struct vcpu* vcpu)
{
    for (mpid_t mpid = 0; mpid < mpu_num_el1_entries(); mpid++) {
        sysreg_prselr_el1_write(mpid);
        vcpu->regs.mpu_regs_el1.prbar[mpid] = sysreg_prbar_el1_read();
        vcpu->regs.mpu_regs_el1.prlar[mpid] = sysreg_prlar_el1_read();
        
        /*  clear guest physical mpu */
        sysreg_prbar_el1_write(0);
        sysreg_prlar_el1_write(0);
    }

    mpu_set_active(&vcpu->vm->as, false);
}

static mpid_t get_vm_region(struct vcpu* vcpu)
{    
    struct list* mpu_order_list = &cpu()->arch.profile.mpu.order.list;
    mpid_t mpid_vcpu = 0;
    list_foreach ((*mpu_order_list), struct mpu_node, entry) {
        mpid_vcpu = entry->mpid;
        sysreg_prselr_el2_write(mpid_vcpu);
        unsigned long prbar = sysreg_prbar_el2_read();
        unsigned long prlar = sysreg_prlar_el2_read();
        unsigned long base  = PRBAR_BASE(prbar);
        unsigned long size  = (PRLAR_LIMIT(prlar) + 1) - base;
        if (((unsigned long)vcpu >= base) && ((unsigned long)vcpu <= (base + size))) break;
    }
    // 2 regions are associated to a VM, the VM + vCPU and the vGIC
    return (3<<mpid_vcpu);
}

void vcpu_arch_profile_restore_state(struct vcpu* vcpu)
{
    unsigned long prenr = 0;
    prenr = get_vm_region(vcpu);
    mpu_set_active(&vcpu->vm->as, true);

    size_t hyp_regions = bitmap_count_consecutive((bitmap_t*)&cpu()->as.arch.mpu.prenr,
                                                  REG_LENGTH, 0, REG_LENGTH);
    size_t vm_regions = bitmap_count_consecutive((bitmap_t*)&vcpu->vm->as.arch.mpu.prenr,
                                                  REG_LENGTH, 0, REG_LENGTH);
    for (mpid_t mpid = 0; mpid < vm_regions; mpid++) {
        unsigned long lim = vcpu->vm->as.vmpu[mpid].region.base +
                            vcpu->vm->as.vmpu[mpid].region.size - 1;
        sysreg_prselr_el2_write(mpid + hyp_regions);
        sysreg_prbar_el2_write((vcpu->vm->as.vmpu[mpid].region.base & PRBAR_BASE_MSK) |
                                (unsigned long) vcpu->vm->as.vmpu[mpid].region.mem_flags.prbar);
        sysreg_prlar_el2_write((lim & PRLAR_LIMIT_MSK) | 
                                (unsigned long) vcpu->vm->as.vmpu[mpid].region.mem_flags.prlar);
        prenr |= (1<<(mpid + hyp_regions));
    }

    for (mpid_t mpid = 0; mpid < mpu_num_el1_entries(); mpid++) {
        sysreg_prselr_el1_write(mpid);
        sysreg_prbar_el1_write(vcpu->regs.mpu_regs_el1.prbar[mpid]);
        sysreg_prlar_el1_write(vcpu->regs.mpu_regs_el1.prlar[mpid]);
    }

   sysreg_prenr_el2_write(prenr | cpu()->as.arch.mpu.locked);
}

void vcpu_restore_arch_banked_registers(struct vcpu* vcpu)
{
    /* usr */
    sysreg_x8_usr_write(vcpu->regs.usr_regs[0]);
    sysreg_x9_usr_write(vcpu->regs.usr_regs[1]);
    sysreg_x10_usr_write(vcpu->regs.usr_regs[2]);
    sysreg_x11_usr_write(vcpu->regs.usr_regs[3]);
    sysreg_x12_usr_write(vcpu->regs.usr_regs[4]);

    /* fiq */
    sysreg_x8_fiq_write(vcpu->regs.fiq_regs[0]);
    sysreg_x9_fiq_write(vcpu->regs.fiq_regs[1]);
    sysreg_x10_fiq_write(vcpu->regs.fiq_regs[2]);
    sysreg_x11_fiq_write(vcpu->regs.fiq_regs[3]);
    sysreg_x12_fiq_write(vcpu->regs.fiq_regs[4]);

    /* spsr registers */
    sysreg_spsr_el1_write(vcpu->regs.spsr_regs[0]); // svc
    sysreg_spsr_abt_write(vcpu->regs.spsr_regs[1]);
    sysreg_spsr_und_write(vcpu->regs.spsr_regs[2]);
    sysreg_spsr_irq_write(vcpu->regs.spsr_regs[3]);
    sysreg_spsr_fiq_write(vcpu->regs.spsr_regs[4]);

    /* sp registers */
    sysreg_sp_el0_write(vcpu->regs.sp_regs[0]); // usr
    sysreg_sp_el1_write(vcpu->regs.sp_regs[1]); // svc
    sysreg_sp_abt_write(vcpu->regs.sp_regs[2]);
    sysreg_sp_und_write(vcpu->regs.sp_regs[3]);
    sysreg_sp_irq_write(vcpu->regs.sp_regs[4]);
    sysreg_sp_fiq_write(vcpu->regs.sp_regs[5]);

    /* lr registers */
    sysreg_lr_el1_write(vcpu->regs.lr_regs[0]); // svc
    sysreg_lr_abt_write(vcpu->regs.lr_regs[1]);
    sysreg_lr_und_write(vcpu->regs.lr_regs[2]);
    sysreg_lr_irq_write(vcpu->regs.lr_regs[3]);
    sysreg_lr_fiq_write(vcpu->regs.lr_regs[4]);
}

void vcpu_save_arch_banked_registers(struct vcpu* vcpu)
{
    /* usr */
    vcpu->regs.usr_regs[0] = sysreg_x8_usr_read();
    vcpu->regs.usr_regs[1] = sysreg_x9_usr_read();
    vcpu->regs.usr_regs[2] = sysreg_x10_usr_read();
    vcpu->regs.usr_regs[3] = sysreg_x11_usr_read();
    vcpu->regs.usr_regs[4] = sysreg_x12_usr_read();

    /* fiq */
    vcpu->regs.fiq_regs[0] = sysreg_x8_fiq_read();
    vcpu->regs.fiq_regs[1] = sysreg_x9_fiq_read();
    vcpu->regs.fiq_regs[2] = sysreg_x10_fiq_read();
    vcpu->regs.fiq_regs[3] = sysreg_x11_fiq_read();
    vcpu->regs.fiq_regs[4] = sysreg_x12_fiq_read();

    /* spsr registers */
    vcpu->regs.spsr_regs[0] = sysreg_spsr_el1_read(); // svc
    vcpu->regs.spsr_regs[1] = sysreg_spsr_abt_read();
    vcpu->regs.spsr_regs[2] = sysreg_spsr_und_read();
    vcpu->regs.spsr_regs[3] = sysreg_spsr_irq_read();
    vcpu->regs.spsr_regs[4] = sysreg_spsr_fiq_read();

    /* sp registers */
    vcpu->regs.sp_regs[0] = sysreg_sp_el0_read(); // usr
    vcpu->regs.sp_regs[1] = sysreg_sp_el1_read(); // svc
    vcpu->regs.sp_regs[2] = sysreg_sp_abt_read();
    vcpu->regs.sp_regs[3] = sysreg_sp_und_read();
    vcpu->regs.sp_regs[4] = sysreg_sp_irq_read();
    vcpu->regs.sp_regs[5] = sysreg_sp_fiq_read();

    /* lr registers */
    vcpu->regs.lr_regs[0] = sysreg_lr_el1_read(); // svc
    vcpu->regs.lr_regs[1] = sysreg_lr_abt_read();
    vcpu->regs.lr_regs[2] = sysreg_lr_und_read();
    vcpu->regs.lr_regs[3] = sysreg_lr_fiq_read();
    vcpu->regs.lr_regs[4] = sysreg_lr_irq_read();
}
