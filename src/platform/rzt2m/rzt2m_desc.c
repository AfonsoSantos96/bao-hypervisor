/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

struct platform platform = {

    .cpu_num = 1,
    .region_num = 1,
    .regions =  (struct mem_region[]) {
        {
            // DRAM, 0GB-2GB
            .base = 0x10000000,
            .size = 0x00180000
        }
    },

    .console = {      // Baudrate 19200
        .base = 0x80001000, // Uart0 (USB connection: CN16 - USB_ser)
        // .base = 0x80001C00, // Uart3 (J25/PMOD2: w/FTDI -> Tx - pin2 and Rx -> pin3)
    },

    .arch = {
        .gic = {
            .gicd_addr = 0x94000000,
            .gicc_addr = 0x91000000,
            .gich_addr = 0x91010000,
            .gicv_addr = 0x9102F000,
            .gicr_addr = 0x94100000,
            .maintenance_id = 25
        },

        .generic_timer = {
            .base_addr = 0xC0060000
        },
    }

};
