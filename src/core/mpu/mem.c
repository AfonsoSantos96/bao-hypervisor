#include <mem.h>

#include <cpu.h>
#include <bao.h>
#include <fences.h>

extern bool mem_reserve_ppages(struct ppages *ppages);
extern bool mem_reserve_ppool_ppages(struct page_pool *pool, struct ppages *ppages);
extern bool mem_are_ppages_reserved(struct ppages *ppages);

void mem_prot_init() {
    as_init(&cpu()->as, AS_HYP, 0);
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
}

vaddr_t mem_alloc_vpage(struct addr_space *as, enum AS_SEC section,
                            vaddr_t at, size_t n)
{
    return NULL_VA;
}

bool mem_set_region_mpu(vaddr_t va, size_t n, mem_flags_t flags)
{
    /* Search for a free slot region */
    /* Fill mpu registers */
    return true;
}

bool mem_map(struct addr_space *as, vaddr_t va, struct ppages *ppages,
            size_t n, mem_flags_t flags)
{
        /* Address does not belong to a device/shared memory region */
        /* TODO: Redefine PTE_HYP_DEV_FLAGS value */
    if ((flags != PTE_HYP_DEV_FLAGS) && !mem_are_ppages_reserved(ppages)){
        mem_reserve_ppages(ppages);
        if (!mem_set_region_mpu(va, n, flags)){ 
            ERROR ("Error setting mpu region for %x addr", va);
        }
        fence_sync();
    } else if ((flags == PTE_HYP_DEV_FLAGS)){
        if (!mem_set_region_mpu(va, n, flags)){
            ERROR ("Error setting mpu region for device at %x addr", va);
        }
    } else {
        ERROR ("Address already allocated!");
    }

    return true;
}

vaddr_t mem_alloc_map(struct addr_space* as, enum AS_SEC section, struct ppages *page,
                        vaddr_t at, size_t size, mem_flags_t flags)
{
    // TODO: Check if page->base, page->size and vaddr_t at are page_size align?
    // TODO: Change flag to some different from the PTE (or refactor it)
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
                             vaddr_t at, size_t size)
{
        /* Change flag to some different from the PTE (or refactor it) */
    mem_flags_t flags = PTE_HYP_DEV_FLAGS;
    struct ppages temp_page = mem_ppages_get(at, size);
    vaddr_t address = mem_map(as, at, &temp_page, size, flags);

    return address;
}
