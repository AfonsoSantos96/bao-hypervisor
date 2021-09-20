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

#ifndef __PAGE_TABLE_H__
#define __PAGE_TABLE_H__

#include <bao.h>
#include <arch/page_table.h>

#ifndef __ASSEMBLER__

struct page_table_dscr {
    size_t lvls;
    size_t* lvl_off;
    size_t* lvl_wdt;
    bool* lvl_term;
};

struct page_table {
    pte_t* root;
    pte_t root_flags;
    struct page_table_dscr* dscr;
};

extern struct page_table_dscr* hyp_pt_dscr;
extern struct page_table_dscr* vm_pt_dscr;

<<<<<<< HEAD
static inline size_t pt_nentries(page_table_t* pt, size_t lvl)
=======
static inline size_t pt_nentries(struct page_table* pt, size_t lvl)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    return (1UL << pt->dscr->lvl_wdt[lvl]) >> pt->dscr->lvl_off[lvl];
}

<<<<<<< HEAD
static inline size_t pt_lvlsize(page_table_t* pt, size_t lvl)
=======
static inline size_t pt_lvlsize(struct page_table* pt, size_t lvl)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    return 1UL << pt->dscr->lvl_off[lvl];
}

<<<<<<< HEAD
static inline size_t pt_getpteindex(page_table_t* pt, pte_t* pte, size_t lvl)
=======
static inline size_t pt_getpteindex(struct page_table* pt, pte_t* pte, size_t lvl)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    return (size_t)(((size_t)pte) & (PT_SIZE - 1)) / sizeof(pte_t);
}

<<<<<<< HEAD
static inline size_t pt_size(page_table_t* pt, size_t lvl)
=======
static inline size_t pt_size(struct page_table* pt, size_t lvl)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    return pt_nentries(pt, lvl) * sizeof(pte_t);
}

static inline bool pt_lvl_terminal(struct page_table* pt, size_t lvl)
{
    return pt->dscr->lvl_term[lvl];
}

/* Functions implemented in architecture dependent files */

<<<<<<< HEAD
pte_t* pt_get_pte(page_table_t* pt, size_t lvl, void* va);
pte_t* pt_get(page_table_t* pt, size_t lvl, void* va);
void pte_set(pte_t* pte, size_t addr, size_t type, size_t flags);

void pte_set_rsw(pte_t* pte, size_t flag);
bool pte_check_rsw(pte_t* pte, size_t flag);

bool pte_valid(pte_t* pte);
bool pte_table(page_table_t* pt, pte_t* pte, size_t lvl);
bool pte_page(page_table_t* pt, pte_t* pte, size_t lvl);
size_t pt_pte_type(page_table_t* pt, size_t lvl);
=======
pte_t* pt_get_pte(struct page_table* pt, size_t lvl, vaddr_t va);
pte_t* pt_get(struct page_table* pt, size_t lvl, vaddr_t va);
void pte_set(pte_t* pte, paddr_t addr, pte_t flags);

void pte_set_rsw(pte_t* pte, pte_t flag);
bool pte_check_rsw(pte_t* pte, pte_t flag);

bool pte_valid(pte_t* pte);
bool pte_table(struct page_table* pt, pte_t* pte, size_t lvl);
bool pte_page(struct page_table* pt, pte_t* pte, size_t lvl);
pte_t pt_pte_type(struct page_table* pt, size_t lvl);
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff

#endif /* __ASSEMBLER__ */

#endif /* __PAGE_TABLE_H__ */
