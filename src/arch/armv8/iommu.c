/** 
 * Bao, a Lightweight Static Partitioning Hypervisor 
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      David Cerdeira <davidmcerdeira@gmail.com>
 *      Jose Martins <jose.martins@bao-project.org>
 *      Angelo Ruocco <angeloruocco90@gmail.com>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details. 
 *
 */

#include <iommu.h>
#include <arch/smmuv2.h>

<<<<<<< HEAD
long iommu_arch_init()
=======
bool iommu_arch_init()
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    if(platform.arch.smmu.base){
        smmu_init();
        return true;
    }

    return false;
}

static ssize_t iommu_vm_arch_init_ctx(struct vm *vm)
{
    ssize_t ctx_id = vm->iommu.arch.ctx_id;
    if (ctx_id < 0) {

        /* Set up ctx bank to vm address space in an available ctx. */
        ctx_id = smmu_alloc_ctxbnk();
        if (ctx_id >= 0) {
<<<<<<< HEAD
            size_t rootpt;
            mem_translate(&cpu.as, vm->as.pt.root, &rootpt);
            smmu_write_ctxbnk(ctx_id, (void *)rootpt, vm->id);
=======
            paddr_t rootpt;
            mem_translate(&cpu.as, (vaddr_t)vm->as.pt.root, &rootpt);
            smmu_write_ctxbnk(ctx_id, rootpt, vm->id);
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
            vm->iommu.arch.ctx_id = ctx_id;
        } else {
            INFO("iommu: smmuv2 could not allocate ctx for vm: %d", vm->id);
        }
    }

    /* Ctx is valid when we get here. */
    return ctx_id;
}

<<<<<<< HEAD
static long iommu_vm_arch_add(vm_t *vm, uint16_t mask, uint16_t id)
=======
static bool iommu_vm_arch_add(struct vm *vm, streamid_t mask, streamid_t id)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    ssize_t vm_ctx = iommu_vm_arch_init_ctx(vm);
    streamid_t glbl_mask = vm->iommu.arch.global_mask;
    streamid_t prep_mask = (mask & SMMU_ID_MSK) | glbl_mask;
    streamid_t prep_id = (id & SMMU_ID_MSK);
    bool group = (bool) mask;
    
    if(vm_ctx < 0){
        return false;
    }

    if (!smmu_compatible_sme_exists(prep_mask, prep_id, vm_ctx, group)) {
        size_t sme = smmu_alloc_sme();
        if(sme < 0){
            INFO("iommu: smmuv2 no more free sme available.");
            return false;
        }
        smmu_write_sme(sme, prep_mask, prep_id, group);
        smmu_write_s2c(sme, vm_ctx);
    }

    return true;
}

<<<<<<< HEAD
inline long iommu_arch_vm_add_device(vm_t *vm, int id)
=======
inline bool iommu_arch_vm_add_device(struct vm *vm, streamid_t id)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    return iommu_vm_arch_add(vm, 0, id);
}

<<<<<<< HEAD
long iommu_arch_vm_init(vm_t *vm, const vm_config_t *config)
=======
bool iommu_arch_vm_init(struct vm *vm, const struct vm_config *config)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    vm->iommu.arch.global_mask = 
        config->platform.arch.smmu.global_mask | platform.arch.smmu.global_mask;
    vm->iommu.arch.ctx_id = -1;

    /* This section relates only to arm's iommu so we parse it here. */
    for (size_t i = 0; i < config->platform.arch.smmu.group_num; i++) {
        /* Register each group. */
        const struct smmu_group *group =
            &config->platform.arch.smmu.smmu_groups[i];
        if(!iommu_vm_arch_add(vm, group->group_mask, group->group_id)){
            return false;
        }
    }

    return true;
}
