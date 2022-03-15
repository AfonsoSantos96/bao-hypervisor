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

.text 

.macro SAVE_HYP_GPRS

    subs sp, sp, #(14*4)

    str r0,  [sp, #(4*0)]
    str r1,  [sp, #(4*1)]
    str r2,  [sp, #(4*2)]
    str r3,  [sp, #(4*3)]
    str r4,  [sp, #(4*4)]
    str r5,  [sp, #(4*5)]
    str r6,  [sp, #(4*6)]
    str r7,  [sp, #(4*7)]
    str r8,  [sp, #(4*8)]
    str r9,  [sp, #(4*9)]
    str r10, [sp, #(4*10)]
    str r11, [sp, #(4*11)]
    str r12, [sp, #(4*12)]
    bl guest_mode_read
    str r0,  [sp, #(4*13)]
    str r1,  [sp, #(4*14)]

.endm

.macro VM_EXIT

    str r0,  [sp, #(4*0)]
    str r1,  [sp, #(4*1)]
    str r2,  [sp, #(4*2)]
    str r3,  [sp, #(4*3)]
    str r4,  [sp, #(4*4)]
    str r5,  [sp, #(4*5)]
    str r6,  [sp, #(4*6)]
    str r7,  [sp, #(4*7)]
    str r8,  [sp, #(4*8)]
    str r9,  [sp, #(4*9)]
    str r10, [sp, #(4*10)]
    str r11, [sp, #(4*11)]
    str r12, [sp, #(4*12)]

    mrs r2,  ELR_hyp
    mrs r3,  SPSR_hyp
    str r2,  [sp, #(4*15)]
    str r3,  [sp, #(4*16)]

    bl guest_mode_read
    str r0,  [sp, #(4*13)]
    str r1,  [sp, #(4*14)]

    mcr p15, 4, r0, c13, c0, 2
    add r0, r0, CPU_STACK_OFF
    add r0, r0, CPU_STACK_SIZE
    mov sp, r0
    
.endm



/** 
 *  @param r3 SPSR_hyp
 *  @return Executing mode SP on R0 and LR on R1
 */
guest_mode_read:
    mrs r3,  SPSR_hyp
    and r3, r3, #0xF
    
    cmp r3, #0
    beq read_usr
    cmp r3, #2
    beq read_irq
    cmp r3, #3
    beq read_svc
    cmp r3, #7
    beq read_abt
    cmp r3, #11
    beq read_und
    
    read_usr:
        mrs r0,  sp_usr
        mrs r1,  lr_usr
        bx lr
    read_irq:
        mrs r0,  sp_irq
        mrs r1,  lr_irq
        bx lr
    read_svc:
        mrs r0,  sp_svc
        mrs r1,  lr_svc
        bx lr
    read_abt:
        mrs r0,  sp_abt
        mrs r1,  lr_abt
        bx lr
    read_und:
        mrs r0,  sp_und
        mrs r1,  lr_und
        bx lr


/** 
 *  @param r3 SPSR_hyp
 *  @param r1 SP to be used by the guest
 *  @param r0 LR to be used by the guest
 */
guest_mode_write:
    mrs r3,  SPSR_hyp
    and r3, r3, #0xF
    
    cmp r3, #0
    beq write_usr
    cmp r3, #2
    beq write_irq
    cmp r3, #3
    beq write_svc
    cmp r3, #7
    beq write_abt
    cmp r3, #11
    beq write_und
    
    write_usr:
        msr sp_usr, r0
        msr lr_usr, r1
        bx lr
    write_irq:
        msr sp_irq, r0  
        msr lr_irq, r1  
        bx lr
    write_svc:
        msr sp_svc, r0  
        msr lr_svc, r1  
        bx lr
    write_abt:
        msr sp_abt, r0  
        msr lr_abt, r1  
        bx lr
    write_und:
        msr sp_und, r0  
        msr lr_und, r1  
        bx lr



.global vcpu_arch_entry
vcpu_arch_entry:
    mcr p15, 4, r0, c13, c0, 2
    ldr r0, [r0, CPU_VCPU_OFF]
    add r0, r0, VCPU_REGS_OFF
    mov sp, r0

    ldr r0, [sp, #(4*15)]
    ldr r1, [sp, #(4*16)]
    msr ELR_hyp, r0
    msr SPSR_hyp, r1

    ldr r0, [sp, #(4*13)]
    ldr r1, [sp, #(4*14)]
    bl guest_mode_write

    ldr r0,  [sp, #(4*0)]
    ldr r1,  [sp, #(4*1)]
    ldr r2,  [sp, #(4*2)]
    ldr r3,  [sp, #(4*3)]
    ldr r4,  [sp, #(4*4)]
    ldr r5,  [sp, #(4*5)]
    ldr r6,  [sp, #(4*6)]
    ldr r7,  [sp, #(4*7)]
    ldr r8,  [sp, #(4*8)]
    ldr r9,  [sp, #(4*9)]
    ldr r10, [sp, #(4*10)]
    ldr r11, [sp, #(4*11)]
    ldr r12, [sp, #(4*12)]

    eret
    b   .



.balign 0x20
.global _hyp_vector_table
_hyp_vector_table:

.balign ENTRY_SIZE
not_used:
    b	.

.balign ENTRY_SIZE
undefined_instr:
    b	und_pre_handler

.balign ENTRY_SIZE
svc_call:
    b	svc_pre_handler

.balign ENTRY_SIZE
prefetch_abt:
    b	fetch_abt_pre_handler

.balign ENTRY_SIZE
data_abt:
    b	data_abt_pre_handler

.balign ENTRY_SIZE
not__used:
    b	.

.balign ENTRY_SIZE
irq_int:
    b   irq_pre_handler

.balign ENTRY_SIZE
fiq_int:
    b	fiq_pre_handler



.global und_pre_handler
und_pre_handler:
    SAVE_HYP_GPRS
    /* TBD */
    b	.  


.global svc_pre_handler
svc_pre_handler:
    SAVE_HYP_GPRS
    /* TBD */
    b	. 


.global fetch_abt_pre_handler
fetch_abt_pre_handler:
    SAVE_HYP_GPRS
    /* TBD */
    b	.  


.global data_abt_pre_handler
data_abt_pre_handler:
    SAVE_HYP_GPRS
    b vcpu_arch_entry
    /* TBD */
    b	.  


.global irq_pre_handler
irq_pre_handler:
    VM_EXIT
    bl  gic_handle
    b   vcpu_arch_entry


.global fiq_pre_handler
fiq_pre_handler:
    VM_EXIT
    /* TBD */
    b   .
