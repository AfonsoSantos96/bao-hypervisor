/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      David Cerdeira <davidmcerdeira@gmail.com>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#ifndef IPC_H
#define IPC_H

#include <bao.h>
#include <mem.h>

<<<<<<< HEAD
typedef struct ipc {
    size_t base;
    size_t size;
    size_t shmem_id;
    size_t interrupt_num;
    intptr_t *interrupts;
} ipc_t;
=======
struct ipc {
    paddr_t base;
    size_t size;
    size_t shmem_id;
    size_t interrupt_num;
    irqid_t *interrupts;
};
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff

struct vm_config;

<<<<<<< HEAD
long ipc_hypercall(size_t arg0, size_t arg1, size_t arg2);
void ipc_init(const vm_config_t* vm_config, bool vm_master);
shmem_t* ipc_get_shmem(size_t shmem_id);
=======
unsigned long ipc_hypercall(unsigned long arg0, unsigned long arg1, unsigned long arg2);
void ipc_init(const struct vm_config* vm_config, bool vm_master);
struct shmem* ipc_get_shmem(size_t shmem_id);
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff

#endif /* IPC_H */
