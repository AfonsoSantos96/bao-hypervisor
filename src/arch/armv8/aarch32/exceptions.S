/** 
 * Bao, a Lightweight Static Partitioning Hypervisor 
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Sandro Pinto <sandro@bao-project.org>
 *      Afonso Santos <afomms@gmail.com>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details. 
 *
 */

#include <asm_defs.h>

#define ENTRY_SIZE   (0x4)
#define usr          (0x10)
#define irq          (0x12)
#define hvc          (0x13)
#define abt          (0x17)
#define hyp          (0x1a)
#define und          (0x1b)

.text 

.macro SAVE_HYP_GPRS

    sub sp, sp, #(14*4)
    push {r0-r12}

.endm


.macro FROM_HYP_MODE

    push {r0}
    mrs r0, SPSR_hyp
    and r0, r0, #0x1F
    cmp r0, #hyp
    pop {r0}    
    beq hyp_mode_handler

.endm


.macro VM_EXIT

    push {r0-r12}
    guest_mode_read

.endm


.macro SAVE_RETURN_OFFSET offset

    mrs r0, ELR_hyp
    mrs r1, SPSR_hyp
    sub r0, r0, #\offset
    push {r0, r1}

.endm


.macro SET_SP

    mcr p15, 4, r0, c13, c0, 2
    add r0, r0, CPU_STACK_OFF
    add r0, r0, CPU_STACK_SIZE
    mov sp, r0
    
.endm


.macro guest_mode_read offset
    mrs r3, SPSR_hyp
    and r3, r3, #0x1F
    
    cmp r3, #usr
    beq 1f  //read_usr
    cmp r3, #irq
    beq 2f //read_irq
    cmp r3, #hvc
    beq 3f //read_hvc
    cmp r3, #abt
    beq 4f //read_abt
    cmp r3, #und
    beq 5f //read_und
    
    1:  //read_usr:
        mrs r0,  sp_usr
        mrs r1,  lr_usr
        b 6f
    2:  //read_irq:
        mrs r0,  sp_irq
        mrs r1,  lr_irq
        b 6f
    3:  //read_hvc:
        mrs r0,  sp_svc
        mrs r1,  lr_svc
        b 6f
    4:  //read_abt:
        mrs r0,  sp_abt
        mrs r1,  lr_abt
        b 6f
    5:  //read_und:
        mrs r0,  sp_und
        mrs r1,  lr_und
        b 6f
    6:
        push {r0-r1}
.endm


.macro guest_mode_write
    pop {r0-r1}
    msr ELR_hyp, r0
    msr SPSR_hyp, r1
    and r1, r1, #0x1F
    pop {r2-r3}
    
    cmp r1, #usr
    beq 1f  //write_usr
    cmp r1, #irq
    beq 2f  //write_irq
    cmp r1, #hvc
    beq 3f  //write_hvc
    cmp r1, #abt
    beq 4f  //write_abt
    cmp r1, #und
    beq 5f  //write_und
    
    1:  //write_usr
        msr sp_usr, r2
        msr lr_usr, r3
        b 6f
    2:  //write_irq
        msr sp_irq, r2  
        msr lr_irq, r3
        b 6f
    3:  //write_hvc
        msr sp_svc, r2  
        msr lr_svc, r3
        b 6f
    4:  //write_abt
        msr sp_abt, r2  
        msr lr_abt, r3
        b 6f
    5:  //write_und
        msr sp_und, r2  
        msr lr_und, r3
        b 6f
    6:
        pop {r0-r12}
.endm


.global vcpu_arch_entry
vcpu_arch_entry:
    mcr p15, 4, r0, c13, c0, 2
    ldr r0, [r0, CPU_VCPU_OFF]
    add r0, r0, VCPU_REGS_OFF
    mov sp, r0
    guest_mode_write
    eret
    b   .


.balign 0x20
.global _hyp_vector_table
_hyp_vector_table:
    b	.
    b	hyp_und_handler
    b	hyp_hvc_handler
    b	hyp_fetch_abt_handler
    b	hyp_data_abt_handler
    b	hyp_trap_handler
    b   hyp_irq_handler
    b   hyp_fiq_handler


.global hyp_und_handler
hyp_und_handler:
    /* TBD */
    b	.  


.global hyp_hvc_handler
hyp_hvc_handler:
    /* TBD */
    b	. 


.global hyp_fetch_abt_handler
hyp_fetch_abt_handler:
    FROM_HYP_MODE
    VM_EXIT
    SAVE_RETURN_OFFSET 4
    SET_SP
    bl	aborts_sync_handler 
    b   vcpu_arch_entry


.global hyp_data_abt_handler
hyp_data_abt_handler:
    FROM_HYP_MODE
    VM_EXIT
    SAVE_RETURN_OFFSET 8
    SET_SP
    bl	aborts_sync_handler 
    b   vcpu_arch_entry

.global hyp_trap_handler
hyp_trap_handler:
    VM_EXIT
    SAVE_RETURN_OFFSET 0
    SET_SP
    bl	aborts_sync_handler
    b   vcpu_arch_entry


.global hyp_irq_handler
hyp_irq_handler:
    VM_EXIT
    SAVE_RETURN_OFFSET 4
    SET_SP
    bl  gic_handle
    b   vcpu_arch_entry


.global hyp_fiq_handler
hyp_fiq_handler:
    b   .


hyp_mode_handler: 
    SAVE_HYP_GPRS
    mov r0, sp
    bl internal_abort_handler
    b .
