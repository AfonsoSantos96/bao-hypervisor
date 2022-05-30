/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      Afonso Santos <afomms@gmail.com>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#ifndef __MEM_PROT_H__
#define __MEM_PROT_H__

#include <bao.h>
#include <arch/mem.h>

enum AS_TYPE { AS_HYP = 0, AS_VM, AS_HYP_CPY };

#define HYP_ASID  0
struct addr_space {
    enum AS_TYPE type;
    colormap_t colors;
};

typedef unsigned long long mem_flags_t;

void as_init(struct addr_space* as, enum AS_TYPE type,
            colormap_t colors);

#endif /* __MEM_PROT_H__ */
