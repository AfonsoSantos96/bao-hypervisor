/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vm.h>

void vm_mem_prot_init(struct vm* vm, const struct vm_config* config) {
    as_init(&vm->as, AS_VM, vm->id);
}

bool vm_mem_region_is_phys(struct vm_mem_region *region) {
    return true;
}

paddr_t vm_mem_region_get_phys(struct vm_mem_region *region) {
    return region->base;
}
