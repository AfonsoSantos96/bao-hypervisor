#include <mem.h>

#include <cpu.h>
#include <bao.h>

void mem_prot_init() {

}

size_t mem_cpu_boot_alloc_size() {
    size_t size = ALIGN(sizeof(struct cpu), PAGE_SIZE);
    return size;
}

vaddr_t mem_alloc_vpage(struct addr_space *as, enum AS_SEC section,
                            vaddr_t at, size_t n)
{
    return NULL_VA;
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
    //vaddr_t address = mem_map_dev(as, at, at, size);

    return address;
}
