/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Sandro Pinto <sandro@bao-project.org>
 *      Afonso Santos <afomms@gmail.com>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#include <cpu.h>
#include <platform.h>

void cpu_arch_profile_init(cpuid_t cpuid, paddr_t load_addr) {

}

void cpu_mem_prot_bitmap_init(struct cpu_arch_profile* mp)
{
    BITMAP_ALLOC(mem_p, mem_get_mp_entries());
    bitmap_clear_consecutive(mem_p, 0, mem_get_mp_entries());
    mp->mem_p = mem_p;
}

void cpu_arch_profile_idle() {
    asm volatile("wfi");
}
