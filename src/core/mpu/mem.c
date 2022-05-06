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

bool mem_map(struct addr_space *as, vaddr_t va, struct ppages *ppages,
            size_t n, mem_flags_t flags)
{
    return false;
}

vaddr_t mem_alloc_map (struct addr_space* as, enum AS_SEC section, struct ppages *page, 
                        vaddr_t at, size_t size, mem_flags_t flags)
{
    vaddr_t address = mem_alloc_vpage (as, section, at, size);
    if (address != at) ERROR("Can't allocate address");
    mem_map(as, address, page, size, flags);

    return address;
}
