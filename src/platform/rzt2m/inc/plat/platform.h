/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __PLAT_PLATFORM_H__
#define __PLAT_PLATFORM_H__

#include <drivers/rzt2m_uart.h>

#define CONFIG_TIMER_ARCH_FREQ (25000000ull)  // 25 MHz
#define CNTDIF_VALUE           (0x017D7840)   // CNTDIF register value for 25 MHz counter frequency

#endif
