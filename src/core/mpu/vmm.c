/**
 * SPDX-License-Identifier: GPL-2.0 
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vmm.h>
#include <io.h>

extern void mem_set_shared_region(unsigned long as, vaddr_t va, size_t n, 
                            mem_flags_t flags);

void vmm_io_init() {

}

struct vm_install_info vmm_get_vm_install_info(struct vm* vm) {
    return (struct vm_install_info){.base_addr = (vaddr_t)vm, .size = sizeof(*vm)};
}

void vmm_vm_install(struct vm* vm, struct vm_install_info *install_info) {
    /*  Define "0" */
    mem_set_shared_region(0, install_info->base_addr, install_info->size, 
                            0x100);//PTE_VM_FLAGS);

}
