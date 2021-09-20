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

#include <config.h>

<<<<<<< HEAD
void config_arch_adjust_to_va(struct config *config, size_t phys)
=======
void config_arch_adjust_to_va(struct config *config, paddr_t phys)
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
{
    for (size_t i = 0; i < config->vmlist_size; i++) {
	    adjust_ptr(config->vmlist[i].platform.arch.smmu.smmu_groups, config);
    }
}
