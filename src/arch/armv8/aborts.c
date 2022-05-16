/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      Afonso Santos <afomms@gmail.com>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#include <arch/aborts.h>
#include <arch/sysregs.h>
#include <cpu.h>
#include <vm.h>
#include <emul.h>
#include <hypercall.h>

typedef void (*abort_handler_t)(unsigned long, unsigned long, unsigned long, unsigned long);

void internal_abort_handler(unsigned long gprs[]) {

    for(size_t i = 0; i < REG_NUM; i++) {
        printk("x%d:\t\t0x%0lx\n", i, gprs[i]);
    }
    printk("SP:\t\t0x%0lx\n", gprs[REG_NUM]);
    printk("ESR:\t0x%0lx\n", sysreg_esr_el2_read());
    printk("ELR:\t0x%0lx\n", sysreg_elr_el2_read());
    printk("FAR:\t0x%0lx\n", sysreg_far_el2_read());
    ERROR("cpu%d internal hypervisor abort - PANIC\n", cpu()->id);
}

void aborts_data_lower(unsigned long iss, unsigned long far, unsigned long il, unsigned long ec)
{
    if (!(iss & ESR_ISS_DA_ISV_BIT) || (iss & ESR_ISS_DA_FnV_BIT)) {
        ERROR("no information to handle data abort (0x%x)", far);
    }

    unsigned long DSFC =
        bit64_extract(iss, ESR_ISS_DA_DSFC_OFF, ESR_ISS_DA_DSFC_LEN) & (0xf << 2);

    if (DSFC != ESR_ISS_DA_DSFC_TRNSLT) {
        ERROR("data abort is not translation fault - cant deal with it");
    }

    vaddr_t addr = far;
    emul_handler_t handler = vm_emul_get_mem(cpu()->vcpu->vm, addr);
    if (handler != NULL) {
        struct emul_access emul;
        emul.addr = addr;
        emul.width =
            (1 << bit64_extract(iss, ESR_ISS_DA_SAS_OFF, ESR_ISS_DA_SAS_LEN));
        emul.write = iss & ESR_ISS_DA_WnR_BIT ? true : false;
        emul.reg = bit64_extract(iss, ESR_ISS_DA_SRT_OFF, ESR_ISS_DA_SRT_LEN);
        emul.reg_width =
            4 + (4 * bit64_extract(iss, ESR_ISS_DA_SF_OFF, ESR_ISS_DA_SF_LEN));
        emul.sign_ext =
            bit64_extract(iss, ESR_ISS_DA_SSE_OFF, ESR_ISS_DA_SSE_LEN);

        // TODO: check if the access is aligned. If not, inject an exception in
        // the vm

        if (handler(&emul)) {
            unsigned long pc_step = 2 + (2 * il);
            vcpu_writepc(cpu()->vcpu, vcpu_readpc(cpu()->vcpu) + pc_step);
        } else {
            ERROR("data abort emulation failed (0x%x)", far);
        }
    } else {
        ERROR("no emulation handler for abort(0x%x at 0x%x)", far,
              vcpu_readpc(cpu()->vcpu));
    }
}

__attribute__((weak))
void smc_handler(unsigned long iss, unsigned long far, unsigned long il, unsigned long ec)
{
    WARNING("smc call but there is no handler");
}

void hvc_handler(unsigned long iss, unsigned long far, unsigned long il, unsigned long ec)
{
    unsigned long hvc_fid = vcpu_readreg(cpu()->vcpu, 0);
    unsigned long x1 = vcpu_readreg(cpu()->vcpu, 1);
    unsigned long x2 = vcpu_readreg(cpu()->vcpu, 2);
    unsigned long x3 = vcpu_readreg(cpu()->vcpu, 3);

    int64_t ret = -HC_E_INVAL_ID;
    switch(hvc_fid){
        case HC_IPC:
            ret = ipc_hypercall(x1, x2, x3);
        break;
    }

    vcpu_writereg(cpu()->vcpu, 0, ret);
}

static regaddr_t reg_addr_translate (unsigned long iss)
{
    iss &= ESR_ISS_SYSREG_ADDR_64;
    if (iss == ICC_SGI1R_CASE) {return (regaddr_t) ICC_SGI1R_ADDR;}
        else {return (regaddr_t) UNDEFINED_REG_ADDR;}
}

void sysreg_handler(unsigned long iss, unsigned long far, unsigned long il, unsigned long ec)
{
    regaddr_t reg_addr = 0;
    if (ec == ESR_EC_RG_64) reg_addr = reg_addr_translate(iss);
        else reg_addr = (iss & ESR_ISS_SYSREG_ADDR_32) | OP0_MRS_CP15;

    emul_handler_t handler = vm_emul_get_reg(cpu()->vcpu->vm, reg_addr);
    if(handler != NULL){
        struct emul_access emul;
        emul.addr = reg_addr;
        emul.width = 8;
        emul.write = iss & ESR_ISS_SYSREG_DIR ? false : true;
        emul.reg = bit64_extract(iss, ESR_ISS_SYSREG_REG_OFF, ESR_ISS_SYSREG_REG_LEN);
        emul.reg_high = bit64_extract(iss, ESR_ISS_SYSREG_REG2_OFF, ESR_ISS_SYSREG_REG2_LEN);
        emul.reg_width = 8;
        emul.multi_reg = (ec == ESR_EC_RG_64)? true : false;
        emul.sign_ext = false;

        if (handler(&emul)) {
            unsigned long pc_step = 2 + (2 * il);
            vcpu_writepc(cpu()->vcpu, vcpu_readpc(cpu()->vcpu) + pc_step);
        } else {
            ERROR("register access emulation failed (0x%x)", reg_addr);
        }
    } else {
        ERROR("no emulation handler for register access (0x%x at 0x%x)", reg_addr,
              vcpu_readpc(cpu()->vcpu));
    }
}

abort_handler_t abort_handlers[64] = {[ESR_EC_DALEL] = aborts_data_lower,
                                      [ESR_EC_SMC32] = smc_handler,
                                      [ESR_EC_SMC64] = smc_handler,
                                      [ESR_EC_SYSRG] = sysreg_handler,
                                      [ESR_EC_RG_32] = sysreg_handler,
                                      [ESR_EC_RG_64] = sysreg_handler,
                                      [ESR_EC_HVC32] = hvc_handler,
                                      [ESR_EC_HVC64] = hvc_handler,};

void aborts_sync_handler()
{
    unsigned long esr = sysreg_esr_el2_read();
    unsigned long far = sysreg_far_el2_read();
    unsigned long hpfar = sysreg_hpfar_el2_read();
    unsigned long ipa_fault_addr = 0;

    ipa_fault_addr = (far & 0xFFF) | (hpfar << 8);

    unsigned long ec = bit64_extract(esr, ESR_EC_OFF, ESR_EC_LEN);
    unsigned long il = bit64_extract(esr, ESR_IL_OFF, ESR_IL_LEN);
    unsigned long iss = bit64_extract(esr, ESR_ISS_OFF, ESR_ISS_LEN);

    abort_handler_t handler = abort_handlers[ec];
    if (handler)
        handler(iss, ipa_fault_addr, il, ec);
    else
        ERROR("no handler for abort ec = 0x%x", ec);  // unknown guest exception
}
