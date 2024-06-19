/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef SCHED_H
#define SCHED_H

#include <bao.h>

void sched_start(void);
long sched_hypercall(void);

#endif /* SCHED_H */
