/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 * 		David Cerdeira <david.mcerdeira@gmail.com>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#ifndef __PSCI_H__
#define __PSCI_H__

#include <bao.h>
#include <spinlock.h>
#include <plat/psci.h>
#include <arch/gic.h>

#define PSCI_VERSION (0x84000000)
#define PSCI_CPU_SUSPEND_AARCH32 (0x84000001)
#define PSCI_CPU_SUSPEND_AARCH64 (0xc4000001)
#define PSCI_CPU_OFF (0x84000002)
#define PSCI_CPU_ON_AARCH32 (0x84000003)
#define PSCI_CPU_ON_AARCH64 (0xc4000003)
#define PSCI_AFFINITY_INFO_AARCH32 (0x84000004)
#define PSCI_AFFINITY_INFO_AARCH64 (0xc4000004)
#define PSCI_FEATURES (0x8400000A)
#define PSCI_MIG_INFO_TYPE (0x84000006)

#define PSCI_TOS_NOT_PRESENT_MP 2

#define PSCI_CPU_IS_ON 0
#define PSCI_CPU_IS_OFF 1

#define PSCI_INVALID_ADDRESS (-1L)

#define PSCI_GET_VERSION_MAJOR(ver) (u16)((ver) >> 16)
#define PSCI_GET_VERSION(major, minor) (((major) << 16) | (minor))

#define PSCI_E_SUCCESS 0
#define PSCI_E_NOT_SUPPORTED -1
#define PSCI_E_INVALID_PARAMS -2
#define PSCI_E_DENIED -3
#define PSCI_E_ALREADY_ON -4
#define PSCI_E_ON_PENDING -5
#define PSCI_E_INTERN_FAIL -6
#define PSCI_E_NOT_PRESENT -7
#define PSCI_E_DISABLED -8
#define PSCI_E_INVALID_ADDRESS -9

/* The macros below are used to identify PSCI calls from the SMC function ID */
#define SMC_FID_MASK (0xff000000)

#define SMC32_STDSRVC_FID_VALUE (0x84000000)
#define is_smc32_stdsrvc_fid(_fid) \
    (((_fid)&SMC_FID_MASK) == SMC32_STDSRVC_FID_VALUE)

#define SMC64_STDSRVC_FID_VALUE (0xc4000000)
#define is_smc64_stdsrvc_fid(_fid) \
    (((_fid)&SMC_FID_MASK) == SMC64_STDSRVC_FID_VALUE)

#define is_smc_stdsrvc_fid(_fid) \
    (is_smc64_stdsrvc_fid(_fid) || is_smc32_stdsrvc_fid(_fid))

#define PSCI_FID_MASK (0xffe0)
#define PSCI_FID_VALUE (00)
#define is_psci_fid(_fid) \
    (is_smc_stdsrvc_fid(_fid) && (((_fid)&PSCI_FID_MASK) == PSCI_FID_VALUE))

typedef struct {
    spinlock_t lock;
    uintptr_t entrypoint;
    uintptr_t context_id;
    enum { ON, OFF, ON_PENDING } state;
} psci_ctx_t;

typedef struct {
    size_t tcr_el2;
    size_t ttbr0_el2;
    size_t mair_el2;
    size_t cptr_el2;
    size_t hcr_el2;
    size_t vmpidr_el2;
    size_t vtcr_el2;
    size_t vttbr_el2;
    size_t wakeup_reason;
    size_t flat_map;
    gicc_state_t gicc_state;
} __attribute__((packed, aligned(8))) psci_off_state_t;

enum wakeup_reason {
    PSCI_WAKEUP_CPU_OFF,
    PSCI_WAKEUP_POWERDOWN,
    PSCI_WAKEUP_IDLE,
    PSCI_WAKEUP_NUM
};

/* --------------------------------
        SMC Trapping
--------------------------------- */

long psci_smc_handler(size_t smc_fid, size_t x1, size_t x2,
                         size_t x3);

size_t psci_standby();
size_t psci_power_down(size_t reason);

/* --------------------------------
        SMC PSCI interface
--------------------------------- */

size_t psci_version(void);

size_t psci_cpu_suspend(size_t power_state, uintptr_t entrypoint,
                          size_t context_id);

size_t psci_cpu_off(void);

size_t psci_cpu_on(size_t target_cpu, uintptr_t entrypoint,
                     size_t context_id);

size_t psci_affinity_info(size_t target_affinity,
                            size_t lowest_affinity_level);

#endif /* __PSCI_H__ */
