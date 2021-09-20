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

#include <iommu.h>

/**
 * TODO: No IOMMU available in riscv
 */

<<<<<<< HEAD
long iommu_arch_init()
=======
bool iommu_arch_init()
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{   
    return true;
}

<<<<<<< HEAD
inline long iommu_arch_vm_add_device(vm_t *vm, long id)
=======
inline bool iommu_arch_vm_add_device(struct vm *vm, streamid_t id)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    return true;
}

<<<<<<< HEAD
long iommu_arch_vm_init(vm_t *vm, const vm_config_t *config)
=======
bool iommu_arch_vm_init(struct vm *vm, const struct vm_config *config)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    return true;
}
