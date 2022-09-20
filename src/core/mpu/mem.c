/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <mem.h>
#include <cpu.h>
#include <vm.h>
#include <bao.h>
#include <fences.h>
#include <platform_defs.h>
#include <objpool.h>

// josecm: should we move this to an header?
extern void mem_write_mp(paddr_t pa, size_t size, mem_flags_t flags);
extern bool mem_free_physical_region(paddr_t num_region);
extern size_t mem_get_granularity();
extern void mem_read_physical_entry(struct memory_protection *mp_entry, 
                                    unsigned long region);
extern struct shared_region* cpu_msg_get_mem_alloc();

void mem_set_region(struct addr_space *as, vaddr_t va, size_t size, 
    mem_flags_t flags, cpumap_t shared_cpus);

struct shared_region {
    node_t node;
    enum AS_TYPE as_type;
    asid_t asid;
    vaddr_t base_addr;
    size_t size;
    mem_flags_t mem_flags;
    cpumap_t trgt_cpu;
    spinlock_t trgt_bitmap_lock;
};


#define SHARED_REGION_POOL_SIZE_DEFAULT (128)
#ifndef SHARED_REGION_POOL_SIZE
#define SHARED_REGION_POOL_SIZE SHARED_REGION_POOL_SIZE_DEFAULT
#endif
OBJPOOL_ALLOC(shared_region_pool, struct shared_region, SHARED_REGION_POOL_SIZE);

void update_virtual_memprot(struct addr_space *as, vaddr_t va, size_t size, 
                            mem_flags_t flags, mpid_t reg)
{
    cpu()->as.mem_prot[reg].base_addr = va;
    cpu()->as.mem_prot[reg].size = size;
    cpu()->as.mem_prot[reg].mem_flags = flags;
    cpu()->as.mem_prot[reg].assigned = true;
    bitmap_set(cpu()->arch.profile.mem_p, reg);
}

void mem_prot_boot_sync()
{
    struct memory_protection mp_entry;
    mpid_t region_num = 0;
    mem_read_physical_entry(&mp_entry, region_num);
    while(mp_entry.assigned)
    {
        update_virtual_memprot(&cpu()->as, mp_entry.base_addr, mp_entry.size, 
                              mp_entry.mem_flags, region_num);
        region_num++;
        mem_read_physical_entry(&mp_entry, region_num);
    }
}

void mem_prot_init() {
    as_init(&cpu()->as, AS_HYP, HYP_ASID);
    cpu_sync_barrier(&cpu_glb_sync);    
    cpu_mem_prot_bitmap_init(&cpu()->arch.profile);
    list_init(&cpu()->interface->memprot.shared_mem_prot);
    mem_prot_boot_sync();
}

size_t mem_cpu_boot_alloc_size() {
    size_t size = ALIGN(sizeof(struct cpu), PAGE_SIZE);
    return size;
}

void as_init(struct addr_space *as, enum AS_TYPE type, asid_t id)
{
    as->type = type;
    as->colors = 0;
    as->id = id;
    as_arch_init(as);
    for(size_t i=0; i<MPU_ABST_ENTRIES; i++)
    {
        as->mem_prot[i].assigned = false;
        as->mem_prot[i].base_addr = 0;
        as->mem_prot[i].size = 0;
        as->mem_prot[i].mem_flags = PTE_INVALID;
    }
}

mpid_t mem_get_available_region(struct addr_space *as)
{   
    for (mpid_t i=0; i<MPU_ABST_ENTRIES; i++)
        if (!as->mem_prot[i].assigned) return i;
    
    return INVALID_MPID;
}

void mem_write_broadcast_region(uint64_t data)
{
    
    struct shared_region* region = NULL;
    struct list* list_ptr = &cpu_interfaces[data].memprot.shared_mem_prot;

    /* Find the first region for the source cpu, the current one hasn't read */
    list_foreach((*list_ptr), struct shared_region, curr_region) {
        if (!!bit_get(curr_region->trgt_cpu, cpu()->id)) {
            region = curr_region;
            break;
        }
    }

    if(region != NULL) {
        vaddr_t base_addr = region->base_addr;
        size_t size = region->size;
        mem_flags_t mem_flags = region->mem_flags;
        struct addr_space *as;

        if (region->as_type == AS_HYP) {
            as = &cpu()->as;
        } else {
            struct addr_space *vm_as = &cpu()->vcpu->vm->as;
            if (vm_as->id != region->asid) {
                ERROR("Received shared region for unkown vm address space.");
            }
            as = vm_as;
        }
        
        spin_lock(&region->trgt_bitmap_lock);

        /* Clear itself from the unread message list */
        region->trgt_cpu = bit_clear(region->trgt_cpu, cpu()->id);

        /**
         * If we are the last cpu checking the message, we should remove it
         * from the list.
         */
        if ((region->trgt_cpu & BIT_MASK(0, PLAT_CPU_NUM)) == 0) {
            list_rm(list_ptr, &region->node);
            objpool_free(&shared_region_pool, region);
        }
        spin_unlock(&region->trgt_bitmap_lock);

        mem_set_region(as, base_addr, size, mem_flags, (cpumap_t)0);
    }
}

void mem_msg_handler(uint32_t event, uint64_t data)
{
    switch(event){
        case MP_MSG_REGION:
            mem_write_broadcast_region(data);
        break;
    }
}
CPU_MSG_HANDLER(mem_msg_handler, MEM_PROT_SYNC);

void mem_region_broadcast(struct addr_space *as, vaddr_t va, size_t size, 
                            mem_flags_t flags, cpumap_t shared_cpus)
{
    struct shared_region *node = objpool_alloc(&shared_region_pool);
    node->base_addr = va;
    node->size = size;
    node->mem_flags = flags;
    node->trgt_bitmap_lock = SPINLOCK_INITVAL;
    node->trgt_cpu = shared_cpus;
    node->as_type = as->type;
    node->asid = as->id;

    /* Cleaning itself from the unread list */
    node->trgt_cpu = bit_clear(node->trgt_cpu, cpu()->id);

    list_push(&cpu()->interface->memprot.shared_mem_prot, (node_t*) node);

    struct cpu_msg msg = {MEM_PROT_SYNC, MP_MSG_REGION, cpu()->id};
    
    for (size_t i = 0; i < PLAT_CPU_NUM; i++) {
        if (bit_get(node->trgt_cpu, i)) {
            cpu_send_msg(i, &msg);
        }
    }
}

cpumap_t mem_section_shareable(struct addr_space *as, enum AS_SEC section)
{
    cpumap_t cpus = 0;
    if (as->type == AS_HYP) {
        if ((section == SEC_HYP_GLOBAL) ||  (section == SEC_HYP_IMAGE)) {
            cpus = BIT_MASK(0, PLAT_CPU_NUM);
        } else if (section == SEC_HYP_VM) {
            /**
             * If we don't have a valid vcpu at this point, it means we are
             * creating this region before even having a vm. Therefore, the
             * sharing of the region must be guaranteed by other means (e.g.
             * vmm_vm_install)
             */
            if (cpu()->vcpu != NULL) {
                cpus = cpu()->vcpu->vm->cpus;
            }
        }
    } else {
        cpus = cpu()->vcpu->vm->cpus;
    }
    
    return cpus;
}

void mem_set_region(struct addr_space *as, vaddr_t va, size_t size, 
    mem_flags_t flags, cpumap_t shared_cpus)
{
    if ((size % mem_get_granularity()) != 0) {
        ERROR ("trying to set mpu region which is not a multiple of granularity");
    }

    mpid_t region_num = mem_get_available_region(as);
    if (region_num >= 0) {
        as->mem_prot[region_num].assigned = true;
        as->mem_prot[region_num].base_addr = va;
        as->mem_prot[region_num].size = size;
        as->mem_prot[region_num].mem_flags = flags;
        mem_write_mp(va, size, flags);
    }

    if(shared_cpus) {
        mem_region_broadcast(as, va, size, flags, shared_cpus);
    }
}

mpid_t mem_get_region_by_address(struct addr_space* as, paddr_t addr)
{
    mpid_t mpid = INVALID_MPID;

    for (mpid_t i = 0; i < MPU_ABST_ENTRIES; i++) {
        vaddr_t limit_addr = as->mem_prot[i].base_addr + as->mem_prot[i].size;
        if((addr >= as->mem_prot[i].base_addr) && (addr < limit_addr)) {
                mpid = i;
                break;
         }
    }

    return mpid;
}

bool mem_erase_region_by_address(struct addr_space* as, paddr_t addr)
{
    mpid_t reg_num = mem_get_region_by_address(as, addr);
    
    if (reg_num >= 0){
        as->mem_prot[reg_num].assigned = false;
        as->mem_prot[reg_num].base_addr = 0;
        as->mem_prot[reg_num].size = 0;
        as->mem_prot[reg_num].mem_flags = PTE_INVALID;
        mem_free_physical_region(addr);
        return true;
    } 

    return false;
}

void merge_regions(struct addr_space* as, struct memory_protection* dst, 
                    struct memory_protection* origin)
{
    dst->size += origin->size;
    mem_erase_region_by_address(as, origin->base_addr);
}

void search_regions_to_merge(struct addr_space* as)
{
    for(size_t i=0; i<(MPU_ABST_ENTRIES-1) && as->mem_prot[i].assigned; i++)
    {
        for (size_t j=(i+1); j<(MPU_ABST_ENTRIES-1) && as->mem_prot[j].assigned; j++) {
            vaddr_t limit_addr = as->mem_prot[i].base_addr + as->mem_prot[i].size;
            if(limit_addr == as->mem_prot[j].base_addr) {
                if(as->mem_prot[i].mem_flags.raw ==
                    as->mem_prot[j].mem_flags.raw)
                {
                    merge_regions(as, &as->mem_prot[i],
                                    &as->mem_prot[j]);
                }
            }
        }
    }
}

bool mem_map(struct addr_space *as, vaddr_t va, struct ppages *ppages,
            size_t num_pages, mem_flags_t flags, cpumap_t shared_cpus)
{
    /* Address does not belong to a device/shared memory region */
    /* TODO: Redefine PTE_HYP_DEV_FLAGS value */ 

    if (ppages == NULL){
        ERROR ("Error mapping memory! Memory was not allocated.");
    }

    if (va != ppages->base) {
        ERROR ("Trying to map non identity");
    }

    mem_set_region(as, va, (num_pages * PAGE_SIZE), flags, shared_cpus);

    return true;
}

vaddr_t mem_alloc_map(struct addr_space* as, enum AS_SEC section,
    struct ppages *ppages, vaddr_t at, size_t size, mem_flags_t flags)
{
    // TODO: Check if page->base, page->size and vaddr_t at are page_size align?

    struct ppages temp_ppages;

    if (at == NULL_VA && ppages == NULL) {
        ERROR ("Can't map an MPU region because neither the virtual"
            "or phsyical address was specified.");
    } else if (at == NULL_VA) {
        at = ppages->base;
    } else if (ppages == NULL) {
        temp_ppages = mem_ppages_get(at, size);
        ppages = &temp_ppages;
    } 

    cpumap_t shared_cpus = mem_section_shareable(as, section);

    mem_map(as, at, ppages, size, flags, shared_cpus);

    return at;
}

vaddr_t mem_alloc_map_dev(struct addr_space* as, enum AS_SEC section,
                             vaddr_t at, paddr_t pa, size_t size)
{
    struct ppages temp_page = mem_ppages_get(pa, size);
    return mem_alloc_map(as, section, &temp_page, at, size,
                   as->type == AS_HYP ? PTE_HYP_DEV_FLAGS : PTE_VM_DEV_FLAGS);
}

vaddr_t mem_map_cpy(struct addr_space *ass, struct addr_space *asd, vaddr_t vas,
                vaddr_t vad, size_t num_pages) {
    // josecm: todo
    return vas;
}

void mem_unmap(struct addr_space *as, vaddr_t at, size_t num_pages,
                    bool free_ppages)
{
    // josecm: todo check free pages and unmap if needed
    mem_erase_region_by_address(as, at);
}
