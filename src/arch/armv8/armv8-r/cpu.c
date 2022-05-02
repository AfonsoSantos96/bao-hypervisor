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
    if (cpuid == CPU_MASTER) {
        /* power on necessary, but still sleeping, secondary cpu cores
         * Assumes CPU zero is doing this */
        for (size_t cpu_core_id = 0; cpu_core_id < platform.cpu_num;
             cpu_core_id++) {
            if(cpu_core_id == cpuid) continue;
            cpu_id_to_mpidr(cpu_core_id);
            // TODO: pass config addr in contextid (x0 register)
            // TODO: use returned value from "cpu_id_to_mpidr" function to
            //       implement power management mechanisms to wake up cores
        }
    }
}

void cpu_arch_profile_idle() {
<<<<<<< HEAD
    /* TBD */
=======
>>>>>>> 95cc7e1... add aarch32 cpu profile
    asm volatile("wfi");
}
