/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef REDUNDANCY_H
#define REDUNDANCY_H

#include <cpu.h>
#include <hypercall.h>

void data_hashing(struct vcpu* vcpu, size_t count, unsigned long* hash);
unsigned long redundancy_hypercall(void);
unsigned long monitor_hypercall(long voting_result);
void redundancy_checkpoint(struct vcpu* vcpu);

#endif /* REDUNDANCY_H */
