/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <mem.h>
#include <cpu.h>

void mem_prot_init() {
    as_init(&cpu()->as, AS_HYP, 0);
}


size_t mem_cpu_boot_alloc_size() {
    size_t size = ALIGN(sizeof(struct cpu), PAGE_SIZE);
    return size;
}

bool mem_map(struct addr_space *as, vaddr_t va, struct ppages *ppages,
            size_t n, mem_flags_t flags)
{
    return false;
}

void as_init(struct addr_space *as, enum AS_TYPE type, 
            colormap_t colors)
{
    as->type = type;
    as->colors = 0;
}

vaddr_t mem_alloc_map(struct addr_space* as, enum AS_SEC section, struct ppages *page,
                        vaddr_t at, size_t size, mem_flags_t flags)
{
    // TODO: Check if page->base, page->size and vaddr_t at are page_size align?
    vaddr_t address = NULL_VA;
    if (page == NULL){
        struct ppages temp_page = mem_ppages_get(at, size);
        address = mem_map(as, at, &temp_page, size, flags);
    }
    else {
        address = mem_map(as, at, page, size, flags);
    }

    return address;
}

vaddr_t mem_alloc_map_dev(struct addr_space* as, enum AS_SEC section,
                             vaddr_t at, paddr_t pa, size_t size)
{
    mem_flags_t flags = PTE_HYP_DEV_FLAGS;
    struct ppages temp_page = mem_ppages_get(at, size);
    vaddr_t address = mem_map(as, at, &temp_page, size, flags);
    return address;
}

vaddr_t mem_map_cpy(struct addr_space *ass, struct addr_space *asd, vaddr_t vas,
                vaddr_t vad, size_t n) {
    return vas;
}

void mem_unmap(struct addr_space *as, vaddr_t at, size_t n,
                    bool free_ppages)
{

}
