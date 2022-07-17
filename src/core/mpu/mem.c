/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <mem.h>
#include <cpu.h>
#include <bao.h>
#include <fences.h>

extern bool mem_reserve_ppages(struct ppages *ppages);
extern bool mem_are_ppages_reserved(struct ppages *ppages);
extern void mem_write_mp(paddr_t pa, size_t n, mem_flags_t flags);
extern void mem_free_physical_region(size_t num_region);
extern unsigned long mem_get_granularity();
void mem_msg_handler(uint32_t event, uint64_t data);

void mem_prot_init() {
    as_init(&cpu()->as, AS_HYP, 0);
    cpu_sync_barrier(&cpu_glb_sync);    
    cpu_mem_prot_bitmap_init(&cpu()->arch.profile);
}

size_t mem_cpu_boot_alloc_size() {
    size_t size = ALIGN(sizeof(struct cpu), PAGE_SIZE);
    return size;
}

void as_init(struct addr_space *as, enum AS_TYPE type, 
            colormap_t colors)
{
    as->type = type;
    as->colors = 0;
    as_arch_init(as);
    for(size_t i=0; i<MPU_ABST_ENTRIES; i++)
    {
        as->mem_prot[i].assigned = false;
        as->mem_prot[i].base_addr = 0;
        as->mem_prot[i].limit_addr = 0;
        as->mem_prot[i].mem_flags = 0;
    }
}

mpid_t mem_get_available_region(struct addr_space *as)
{   
    for (mpid_t i=0; i<MPU_ABST_ENTRIES; i++)
        if (!as->mem_prot[i].assigned) return i;
    
    return -1;
}

void mem_set_shared_region(struct addr_space *as, vaddr_t va, size_t n, 
                            mem_flags_t flags)
{
    if (n < mem_get_granularity())
            ERROR ("region must be bigger than granularity");

    mpid_t region_num = mem_get_available_region(as);
    if(region_num>=0) {
        as->mem_prot[region_num].assigned = true;
        mem_write_mp(va, n, flags);
    }

}

void mem_write_broadcast_region(uint64_t data)
{
    mem_set_shared_region(cpu_interfaces[data].memprot.as,
                          cpu_interfaces[data].memprot.base_addr,
                          cpu_interfaces[data].memprot.size,
                          cpu_interfaces[data].memprot.mem_flags);
    
    cpu_interfaces[data].memprot.cpu_region_sync->count++;
}

CPU_MSG_HANDLER(mem_msg_handler, MEM_PROT_SYNC);

void mem_msg_handler(uint32_t event, uint64_t data)
{
    switch(event){
        case MP_MSG_REGION:
            mem_write_broadcast_region(data);
        break;
    }
}

void mem_set_region(struct addr_space *as, vaddr_t va, size_t n, mem_flags_t flags)
{
    if (n < mem_get_granularity())
            ERROR ("region must be bigger than granularity");

    mpid_t region_num = mem_get_available_region(as);
    if(region_num>=0) {
        as->mem_prot[region_num].assigned = true;
        mem_write_mp(va, n, flags);
    }
}

mpid_t mem_get_address_region(struct addr_space* as, paddr_t addr)
{
    for(size_t i=0; i<MPU_ABST_ENTRIES && as->mem_prot[i].assigned; i++)
        if((addr >= as->mem_prot[i].base_addr) && (
            addr <= as->mem_prot[i].limit_addr)) return i;

    return -1;
}

bool mem_free_region_by_address(struct addr_space* as, paddr_t addr)
{
    mpid_t reg_num = mem_get_address_region(as, addr);
    if (reg_num >= 0) mem_free_physical_region(addr);
        else return false;
    return true;
}

bool mem_erase_region_by_address(struct addr_space* as, paddr_t addr)
{
    mpid_t reg_num = mem_get_address_region(as, addr);
    if (reg_num >= 0){
        as->mem_prot[reg_num].assigned = false;
        as->mem_prot[reg_num].base_addr = 0;
        as->mem_prot[reg_num].limit_addr = 0;
        as->mem_prot[reg_num].mem_flags = 0;
        mem_free_physical_region(addr);
    } 
        else return false;
    return true;
}

void merge_regions(struct addr_space* as, struct memory_protection* dst, 
                    struct memory_protection* origin)
{
    dst->limit_addr = origin->limit_addr;
    mem_erase_region_by_address(as, origin->base_addr);
}

void search_regions_to_merge(struct addr_space* as)
{
    for(size_t i=0; i<(MPU_ABST_ENTRIES-1) && as->mem_prot[i].assigned; i++)
    {
        for (size_t j=(i+1); j<(MPU_ABST_ENTRIES-1) && as->mem_prot[j].assigned; j++)
            if((as->mem_prot[i].limit_addr) ==
                as->mem_prot[j].base_addr)
                {
                    if(as->mem_prot[i].mem_flags ==
                        as->mem_prot[j].mem_flags)
                    {
                        merge_regions(as, &as->mem_prot[i],
                                        &as->mem_prot[j]);
                    }
                }
    }
}

bool mem_map(struct addr_space *as, vaddr_t va, struct ppages *ppages,
            size_t n, mem_flags_t flags)
{
        /* Address does not belong to a device/shared memory region */
        /* TODO: Redefine PTE_HYP_DEV_FLAGS value */
    if ((flags != PTE_HYP_DEV_FLAGS) && !mem_are_ppages_reserved(ppages)){
        mem_reserve_ppages(ppages);
        mem_set_region(as, va, n, flags);
    } else if ((flags == PTE_HYP_DEV_FLAGS)){
        mem_set_region(as, va, n, flags);
    } else {
        ERROR ("Address already allocated!");
    }

    return true;
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
