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

#ifndef __INTERRUPTS_H__
#define __INTERRUPTS_H__

#include <bao.h>
#include <arch/interrupts.h>

#include <bitmap.h>

struct vm;

typedef void (*irq_handler_t)(unsigned long int_id);

void interrupts_init();
void interrupts_reserve(unsigned long int_id, irq_handler_t handler);

void interrupts_cpu_sendipi(cpuid_t target_cpu, unsigned long  ipi_id);
void interrupts_cpu_enable(unsigned long  int_id, bool en);

bool interrupts_check(unsigned long  int_id);
void interrupts_clear(unsigned long  int_id);

enum irq_res { HANDLED_BY_HYP, FORWARD_TO_VM };
enum irq_res interrupts_handle(unsigned long  int_id);

void interrupts_vm_assign(struct vm *vm, unsigned long  id);
void interrupts_vm_inject(struct vm *vm, unsigned long  id);

/* Must be implemented by architecture */

void interrupts_arch_init();
void interrupts_arch_enable(unsigned long  int_id, bool en);
bool interrupts_arch_check(unsigned long  int_id);
void interrupts_arch_clear(unsigned long  int_id);
void interrupts_arch_ipi_send(cpuid_t cpu_target, unsigned long ipi_id);
void interrupts_arch_vm_assign(struct vm *vm, unsigned long id);
void interrupts_arch_vm_inject(struct vm *vm, unsigned long id);
bool interrupts_arch_conflict(bitmap_t interrupt_bitmap, unsigned long  id);

#endif /* __INTERRUPTS_H__ */
