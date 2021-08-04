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

#ifndef __BIT_H__
#define __BIT_H__

#include <bao.h>

/**
 * The extra shift is because both arm and riscv logical shift instructions
 * support a maximum of machine word length minus one bit shits. This covers
 * the corner case of runtime full machine word length masks with the cost of
 * an extra shift instruction. For static masks, there should be no extra costs.
 */
#define BIT_MASK(OFF, LEN) ((((1ULL<<((LEN)-1))<<1)-1)<<(OFF))

#ifndef __ASSEMBLER__

size_t bit_ctz(size_t n);
size_t bit_clz(size_t n);

static inline size_t bit_get(size_t word, size_t off)
{
    return word & (1UL << off);
}

static inline size_t bit_set(size_t word, size_t off)
{
    return word |= (1UL << off);
}

static inline size_t bit_clear(size_t word, size_t off)
{
    return word &= ~(1UL << off);
}

static inline size_t bit_extract(size_t word, size_t off, size_t len)
{
    return (word >> off) & BIT_MASK(0, len);
}

static inline size_t bit_insert(size_t word, size_t val, size_t off,
                                  size_t len)
{
    return (~BIT_MASK(off, len) & word) | ((BIT_MASK(0, len) & val) << off);
}

#endif /* |__ASSEMBLER__ */

#endif /* __BIT_H__ */
