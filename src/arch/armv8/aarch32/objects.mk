## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

cpu-objs-y+=$(ARCH_SUB)/boot.o
cpu-objs-y+=$(ARCH_SUB)/exceptions.o
cpu-objs-y+=$(ARCH_SUB)/vm.o
cpu-objs-y+=$(ARCH_SUB)/aborts.o
cpu-objs-y+=$(ARCH_SUB)/vtimer.o
cpu-objs-y+=$(ARCH_SUB)/vfp.o
