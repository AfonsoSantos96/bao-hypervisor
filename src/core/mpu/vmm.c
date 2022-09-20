/**
 * SPDX-License-Identifier: GPL-2.0 
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <vmm.h>
#include <io.h>

extern void mem_set_region(struct addr_space *as, vaddr_t va, size_t n, 
    mem_flags_t flags, cpumap_t shared_cpus);

void vmm_io_init() {

}

struct vm_install_info vmm_get_vm_install_info(struct vm_allocation* vm_alloc) {
    return (struct vm_install_info) { vm_alloc->base,  vm_alloc->size };
}

void vmm_vm_install(struct vm_install_info *install_info) {
    mem_set_region(&cpu()->as, install_info->base_addr, install_info->size,
            PTE_HYP_FLAGS, (cpumap_t)0);
}
