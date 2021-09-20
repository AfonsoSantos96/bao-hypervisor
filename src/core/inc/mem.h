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

#ifndef __MEM_H__
#define __MEM_H__

#include <bao.h>
#include <arch/mem.h>
#include <page_table.h>
#include <list.h>
#include <spinlock.h>
#include <cache.h>

#ifndef __ASSEMBLER__

enum AS_TYPE { AS_HYP = 0, AS_VM, AS_HYP_CPY };
enum AS_SEC {
    /*--- VM AS SECTIONS -----*/
    SEC_HYP_GLOBAL = 0,
    SEC_HYP_IMAGE,
    SEC_HYP_DEVICE,
    SEC_HYP_PRIVATE,
    SEC_HYP_VM,
    SEC_HYP_ANY, /* must be last */
    /*--- VM AS SECTIONS -----*/
    SEC_VM_ANY = 0, /* must be last */
};

#define HYP_ASID  0
struct addr_space {
    struct page_table pt;
    enum AS_TYPE type;
<<<<<<< HEAD
    size_t colors;
    size_t id;
=======
    colormap_t colors;
    asid_t id;
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
    spinlock_t lock;
};

<<<<<<< HEAD
typedef struct {
    size_t base;
    size_t size;
    size_t colors;
} ppages_t;

struct mem_region {
    size_t base;
    size_t size;
    size_t colors;
    bool place_phys;
    size_t phys;
};

struct dev_region {
    size_t pa;
    size_t va;
    size_t size;
    size_t interrupt_num;
    intptr_t *interrupts;
    size_t id; /* bus master id for iommu effects */
};

typedef struct shmem {
    size_t size;
    size_t colors;
    bool place_phys;
    size_t phys;
    size_t cpu_masters;
} shmem_t;

static inline ppages_t mem_ppages_get(size_t base, size_t size)
=======
struct ppages {
    paddr_t base;
    size_t size;
    colormap_t colors;
};

struct mem_region {
    paddr_t base;
    size_t size;
    colormap_t colors;
    bool place_phys;
    paddr_t phys;
};

struct dev_region {
    paddr_t pa;
    vaddr_t va;
    size_t size;
    size_t interrupt_num;
    irqid_t *interrupts;
    streamid_t id; /* bus master id for iommu effects */
};

struct shmem {
    size_t size;
    colormap_t colors;
    bool place_phys;
    paddr_t phys;
    cpumap_t cpu_masters;
};

static inline struct ppages mem_ppages_get(paddr_t base, size_t size)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    return (struct ppages){.colors = 0, .base = base, .size = size};
}

<<<<<<< HEAD
static inline bool all_clrs(size_t clrs)
=======
static inline bool all_clrs(colormap_t clrs)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    return (clrs == 0) ||
           ((clrs & ((1ULL << COLOR_NUM) - 1)) == ((1ULL << COLOR_NUM) - 1));
}

<<<<<<< HEAD
void mem_init(size_t load_addr, size_t config_addr);
void as_init(addr_space_t* as, enum AS_TYPE type, size_t id, void* root_pt,
             size_t colors);
void* mem_alloc_page(size_t n, enum AS_SEC sec, bool phys_aligned);
ppages_t mem_alloc_ppages(size_t colors, size_t n, bool aligned);
void* mem_alloc_vpage(addr_space_t* as, enum AS_SEC section, void* at,
                      size_t n);
void mem_free_vpage(addr_space_t* as, void* at, size_t n, bool free_ppages);
int mem_map(addr_space_t* as, void* va, ppages_t* ppages, size_t n,
            size_t flags);
int mem_map_reclr(addr_space_t* as, void* va, ppages_t* ppages, size_t n,
                  size_t flags);
int mem_map_dev(addr_space_t* as, void* va, size_t base, size_t n);

/* Functions implemented in architecture dependent files */

void as_arch_init(addr_space_t* as);
bool mem_translate(addr_space_t* as, void* va, intptr_t* pa);
=======
void mem_init(paddr_t load_addr, paddr_t config_addr);
void as_init(struct addr_space* as, enum AS_TYPE type, asid_t id, 
            pte_t* root_pt, colormap_t colors);
void* mem_alloc_page(size_t n, enum AS_SEC sec, bool phys_aligned);
struct ppages mem_alloc_ppages(colormap_t colors, size_t n, bool aligned);
vaddr_t mem_alloc_vpage(struct addr_space* as, enum AS_SEC section,
                    vaddr_t at, size_t n);
void mem_free_vpage(struct addr_space* as, vaddr_t at, size_t n,
                    bool free_ppages);
bool mem_map(struct addr_space* as, vaddr_t va, struct ppages* ppages,
            size_t n, pte_t flags);
bool mem_map_reclr(struct addr_space* as, vaddr_t va, struct ppages* ppages,
                size_t n, pte_t flags);
bool mem_map_dev(struct addr_space* as, vaddr_t va, paddr_t base, size_t n);

/* Functions implemented in architecture dependent files */

void as_arch_init(struct addr_space* as);
bool mem_translate(struct addr_space* as, vaddr_t va, paddr_t* pa);
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff

#endif /* |__ASSEMBLER__ */

#endif /* __MEM_H__ */
