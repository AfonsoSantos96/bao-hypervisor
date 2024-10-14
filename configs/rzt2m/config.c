/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <config.h>

/**
 * Declare VM images using the VM_IMAGE macro, passing an identifier and the
 * path for the image.
 */
VM_IMAGE(vm1, "/path/to/vm1/binary.bin");
VM_IMAGE(vm2, "/path/to/vm2/binary.bin");

/**
 * The configuration itself is a struct config that MUST be named config.
 */
struct config config = {
    
    /**
     * This macro must be always placed in the config struct, to initialize,
     * configuration independent fields.
     */
    CONFIG_HEADER


    /**
     * This defines an array of shared memory objects that may be associated
     * with inter-partition communication objects in the VM platform definition
     * below using the shared memory object ID, ie, its index in the list.
     */
    .shmemlist_size = 1,
    .shmemlist = (struct shmem[]) {
        [0] = {.base = 0x10140000, .size = 0x1000,}
    },

    /**
     * This configuration has 2 VMs.
     */
    .vmlist_size = 2,
    .vmlist = {
        {   // use VM_IMAGE_LOADED macro if image is loaded externally
            // .image = VM_IMAGE_LOADED(0x10100000, 0x10100000, 0x400),
            .image = {
                .base_addr = 0x10100000,
                /** 
                 * Use the  VM_IMAGE_OFFSET and VM_IMAGE_SIZE to initialize
                 * the image fields passing the identifier of the image.
                 */
                .load_addr = VM_IMAGE_OFFSET(vm1),
                .size = VM_IMAGE_SIZE(vm1)
            },

            .entry = 0x10100000,
            .cpu_affinity = 0x0,

            .platform = {

                .cpu_num = 1,       
                .region_num = 1,
                .regions =  (struct vm_mem_region[]) {
                    {
                        .base = 0x10100000,
                        .size = 0x00040000,
                    }
                },

                .dev_num = 1,
                .devs =  (struct vm_dev_region[]) {
                    {   
                        /* UART 0 */
                        .pa = 0x80001000,
                        .va = 0x80001000,
                        .size = 0x400,
                        .interrupt_num = 1,
                        .interrupts = (irqid_t[]) {289}   // SCI0 Receive data full
                                                          // {291} Transmit end (SCI0_TEI)
                    },
                },

                .ipc_num = 1,
                .ipcs = (struct ipc[]) {
                    {
                        .base = 0x10140000,
                        .size = 0x1000,
                        .shmem_id = 0,
                        .interrupt_num = 1,
                        .interrupts = (irqid_t[]) {42}
                    }
                },

                .arch = {
                    .gic = {
                        .gicc_addr = 0x94100000,
                        .gicd_addr = 0x94000000
                    }
                }
            },
        },
        {
            // .image = VM_IMAGE_LOADED(0x10150000, 0x10150000, 0x400),
            .image = {
                .base_addr = 0x10150000,
                /** 
                 * Use the  VM_IMAGE_OFFSET and VM_IMAGE_SIZE to initialize
                 * the image fields passing the identifier of the image.
                 */
                .load_addr = VM_IMAGE_OFFSET(vm2),
                .size = VM_IMAGE_SIZE(vm2)
            },

            .entry = 0x10150000,
            .cpu_affinity = 0x0,

            .platform = {

                .cpu_num = 1,       
                .region_num = 1,
                .regions =  (struct vm_mem_region[]) {
                    {
                        .base = 0x10150000,
                        .size = 0x00020000, 
                    }
                },

                .dev_num = 1,
                .devs =  (struct vm_dev_region[]) {
                    {   
                        /* UART 3 */
                        .pa = 0x80001C00,
                        .va = 0x80001C00,
                        .size = 0x400,
                        .interrupt_num = 1,
                        .interrupts = (irqid_t[]) {301}   // SCI3 Receive data full
                                                          // {303} SCI3 Transmit end (SCI3_TEI)
                    },
                },

                .ipc_num = 1,
                .ipcs = (struct ipc[]) {
                    {
                        .base = 0x10140000,
                        .size = 0x1000,
                        .shmem_id = 0,
                        .interrupt_num = 1,
                        .interrupts = (irqid_t[]) {112}
                    }
                },

                .arch = {
                    .gic = {
                        .gicc_addr = 0x94100000,
                        .gicd_addr = 0x94000000
                    }
                }
            },
        },   
    },
};
