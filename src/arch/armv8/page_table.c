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

#include <bao.h>
#include <page_table.h>
#include <arch/sysregs.h>
#include <cpu.h>

struct page_table_dscr armv8_pt_dscr = {
    .lvls = PT_LVLS,
    .lvl_wdt = (size_t[]){48, 39, 30, 21},
    .lvl_off = (size_t[]){39, 30, 21, 12},
    .lvl_term = (bool[]){false, true, true, true},
};

/**
 * This might be modified at initialization depending on the
 * value of parange and consequently SL0 in VTCR_EL2.
 */
struct page_table_dscr armv8_pt_s2_dscr = {
    .lvls = PT_LVLS,
    .lvl_wdt = (size_t[]){48, 39, 30, 21},
    .lvl_off = (size_t[]){39, 30, 21, 12},
    .lvl_term = (bool[]){false, true, true, true},
};

size_t parange_table[] = {32, 36, 40, 42, 44, 48};

struct page_table_dscr* hyp_pt_dscr = &armv8_pt_dscr;
struct page_table_dscr* vm_pt_dscr = &armv8_pt_s2_dscr;

size_t parange __attribute__((section(".data")));

<<<<<<< HEAD
void pt_set_recursive(page_table_t* pt, size_t index)
{
    size_t pa;
    mem_translate(&cpu.as, pt->root, &pa);
=======
void pt_set_recursive(struct page_table* pt, size_t index)
{
    paddr_t pa;
    mem_translate(&cpu.as, (vaddr_t)pt->root, &pa);
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
    pte_t* pte = cpu.as.pt.root + index;
    pte_set(pte, pa, PTE_TABLE | PTE_HYP_FLAGS);
    pt->root_flags &= ~PT_ROOT_FLAGS_REC_IND_MSK;
    pt->root_flags |=
        (index << PT_ROOT_FLAGS_REC_IND_OFF) & PT_ROOT_FLAGS_REC_IND_MSK;
}

<<<<<<< HEAD
pte_t* pt_get_pte(page_table_t* pt, size_t lvl, void* va)
=======
pte_t* pt_get_pte(struct page_table* pt, size_t lvl, vaddr_t va)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    struct page_table* cpu_pt = &cpu.as.pt;

    size_t rec_ind_off = cpu_pt->dscr->lvl_off[cpu_pt->dscr->lvls - lvl - 1];
    size_t rec_ind_len = cpu_pt->dscr->lvl_wdt[cpu_pt->dscr->lvls - lvl - 1];
<<<<<<< HEAD
    size_t mask = (1UL << rec_ind_off) - 1;
    size_t rec_ind_mask = ((1UL << rec_ind_len) - 1) & ~mask;
    size_t rec_ind = ((pt->root_flags & PT_ROOT_FLAGS_REC_IND_MSK) >>
                        PT_ROOT_FLAGS_REC_IND_OFF);
    size_t addr = ~mask;
    addr &= PTE_ADDR_MSK;
    addr &= ~(rec_ind_mask);
    addr |= ((rec_ind << rec_ind_off) & rec_ind_mask);
    addr |=
        (((((size_t)va) >> pt->dscr->lvl_off[lvl]) * sizeof(pte_t)) & (mask));
=======
    pte_t mask = (1UL << rec_ind_off) - 1;
    pte_t rec_ind_mask = ((1UL << rec_ind_len) - 1) & ~mask;
    size_t rec_ind = ((pt->root_flags & PT_ROOT_FLAGS_REC_IND_MSK) >>
                        PT_ROOT_FLAGS_REC_IND_OFF);
    pte_t addr = ~mask;
    addr &= PTE_ADDR_MSK;
    addr &= ~(rec_ind_mask);
    addr |= ((rec_ind << rec_ind_off) & rec_ind_mask);
    addr |= (((va >> pt->dscr->lvl_off[lvl]) * sizeof(pte_t)) & (mask));
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff

    return (pte_t*)addr;
}

<<<<<<< HEAD
pte_t* pt_get(page_table_t* pt, size_t lvl, void* va)
{
    if (lvl == 0) return pt->root;

    size_t pte = (size_t)pt_get_pte(pt, lvl, va);
=======
pte_t* pt_get(struct page_table* pt, size_t lvl, vaddr_t va)
{
    if (lvl == 0) return pt->root;

    uintptr_t pte = (uintptr_t)pt_get_pte(pt, lvl, va);
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
    pte &= ~(PAGE_SIZE - 1);
    return (pte_t*)pte;
}

<<<<<<< HEAD
size_t pt_pte_type(page_table_t* pt, size_t lvl)
=======
pte_t pt_pte_type(struct page_table* pt, size_t lvl)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    return (lvl == pt->dscr->lvls - 1) ? PTE_PAGE : PTE_SUPERPAGE;
}

<<<<<<< HEAD
bool pte_page(page_table_t* pt, pte_t* pte, size_t lvl)
=======
bool pte_page(struct page_table* pt, pte_t* pte, size_t lvl)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    if (lvl != pt->dscr->lvls - 1) {
        return false;
    }

    return (*pte & PTE_TYPE_MSK) == PTE_PAGE;
}

<<<<<<< HEAD
bool pte_table(page_table_t* pt, pte_t* pte, size_t lvl)
=======
bool pte_table(struct page_table* pt, pte_t* pte, size_t lvl)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    if (lvl == pt->dscr->lvls - 1) {
        return false;
    }

    return (*pte & PTE_TYPE_MSK) == PTE_TABLE;
}
