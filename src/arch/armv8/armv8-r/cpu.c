/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <cpu.h>
#include <platform.h>
#include <arch/generic_timer.h>

void cpu_arch_profile_init(cpuid_t cpuid, paddr_t load_addr) {
    /** 
     * Since there is no firmware in cortex-r platforms, we need to
     * initialize the system counter.
     */
    volatile struct generic_timer_cntctrl *timer_ctl =
        (void*) platform.arch.generic_timer.base_addr;
    if (cpu()->id == CPU_MASTER) {
        timer_ctl->CNTCR |= GENERIC_TIMER_CNTCTL_CNTCR_EN;
    }
    sysreg_cntfrq_el0_write(timer_ctl->CNTDIF0);
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
