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

#include <arch/bao.h>
#include <arch/sysregs.h>
#include <asm_defs.h>

#define ENTRY_SIZE   (0x80)

.text 

.macro SAVE_HYP_GPRS
 /* 
    sub sp, sp, 32*8

    stp r0, r1,   [sp, #(8*0)]
    stp r2, r3,   [sp, #(8*2)]
    stp r4, r5,   [sp, #(8*4)]
    stp r6, r7,   [sp, #(8*6)]
    stp r8, r9,   [sp, #(8*8)]
    stp r10, r11, [sp, #(8*10)]
    stp r12, r13, [sp, #(8*12)]
    stp r14, r15, [sp, #(8*14)]
    stp r16, r17, [sp, #(8*16)]
    stp r18, r19, [sp, #(8*18)]
    stp r20, r21, [sp, #(8*20)]
    stp r22, r23, [sp, #(8*22)]
    stp r24, r25, [sp, #(8*24)]
    stp r26, r27, [sp, #(8*26)]
    stp r28, r29, [sp, #(8*28)]
    mov r29, sp 
    add r29, r29, 32*8
    stp r30, r29, [sp, #(8*30)]
*/
.endm

.macro VM_EXIT
 /*   sub sp, sp, #(VCPU_REGS_SIZE)

    stp r0, r1,   [sp, #(8*0)]
    stp r2, r3,   [sp, #(8*2)]
    stp r4, r5,   [sp, #(8*4)]
    stp r6, r7,   [sp, #(8*6)]
    stp r8, r9,   [sp, #(8*8)]
    stp r10, r11, [sp, #(8*10)]
    stp r12, r13, [sp, #(8*12)]
    stp r14, r15, [sp, #(8*14)]
    stp r16, r17, [sp, #(8*16)]
    stp r18, r19, [sp, #(8*18)]
    stp r20, r21, [sp, #(8*20)]
    stp r22, r23, [sp, #(8*22)]
    stp r24, r25, [sp, #(8*24)]
    stp r26, r27, [sp, #(8*26)]
    stp r28, r29, [sp, #(8*28)]
    str r30,      [sp, #(8*30)]

    mrs r0, ELR_EL2
    mrs r1, SPSR_EL2
    stp r0, r1,   [sp, #(8*31)]

    mrs r0, TPIDR_EL2
    ldr r0, [r0, #CPU_VCPU_OFF]
    mov r1, sp
    str r1, [r0, #VCPU_REGS_OFF]
*/
.endm

.global vcpu_arch_entry
vcpu_arch_entry:
 /*   mrs r0, TPIDR_EL2
    ldr r0, [r0, #CPU_VCPU_OFF]
    ldr r0, [r0, #VCPU_REGS_OFF]
    mov sp, r0

    ldp r0, r1, [sp, #(8*31)]
    msr ELR_EL2, r0
    msr SPSR_EL2, r1

    ldp r0, r1,   [sp, #(8*0)]
    ldp r2, r3,   [sp, #(8*2)]
    ldp r4, r5,   [sp, #(8*4)]
    ldp r6, r7,   [sp, #(8*6)]
    ldp r8, r9,   [sp, #(8*8)]
    ldp r10, r11, [sp, #(8*10)]
    ldp r12, r13, [sp, #(8*12)]
    ldp r14, r15, [sp, #(8*14)]
    ldp r16, r17, [sp, #(8*16)]
    ldp r18, r19, [sp, #(8*18)]
    ldp r20, r21, [sp, #(8*20)]
    ldp r22, r23, [sp, #(8*22)]
    ldp r24, r25, [sp, #(8*24)]
    ldp r26, r27, [sp, #(8*26)]
    ldp r28, r29, [sp, #(8*28)]
    ldr r30,      [sp, #(8*30)]

    add sp, sp, #(VCPU_REGS_SIZE)
*/    
    eret
    b   .

.balign 0x800
.global _hyp_vector_table	
_hyp_vector_table:

/* 
 * EL2 with SP0
 */  
.balign ENTRY_SIZE
curr_el_sp0_sync:        
    b	.
.balign ENTRY_SIZE
curr_el_sp0_irq:  
    b   .
.balign ENTRY_SIZE
curr_el_sp0_fiq:         
    b	.
.balign ENTRY_SIZE
curr_el_sp0_serror:      
    b	.
          

/* 
 * EL2 with SPx
 */  
.balign ENTRY_SIZE  
curr_el_spx_sync:
    SAVE_HYP_GPRS
    mov r0, sp
    bl	internal_abort_handler        
    b	.
.balign ENTRY_SIZE
curr_el_spx_irq:         
    b	.
.balign ENTRY_SIZE
curr_el_spx_fiq:         
    b	.
.balign ENTRY_SIZE
curr_el_spx_serror:
    SAVE_HYP_GPRS
    mov r0, sp
    bl	internal_abort_handler       
    b	.         

/* 
 * Lower EL using AArch64
 */  

.balign ENTRY_SIZE
lower_el_aarch64_sync:
    VM_EXIT
    bl	aborts_sync_handler
    b   vcpu_arch_entry
.balign ENTRY_SIZE
lower_el_aarch64_irq:    
    VM_EXIT
    bl  gic_handle
    b   vcpu_arch_entry
.balign ENTRY_SIZE
lower_el_aarch64_fiq:    
    b	.
.balign ENTRY_SIZE
lower_el_aarch64_serror: 
    b	.          

/* 
 * Lower EL using AArch32
 */  
.balign ENTRY_SIZE   
lower_el_aarch32_sync:   
    b	.
.balign ENTRY_SIZE
lower_el_aarch32_irq:    
    b	.
.balign ENTRY_SIZE
lower_el_aarch32_fiq:    
    b	.
.balign ENTRY_SIZE
lower_el_aarch32_serror: 
    b	.

.balign ENTRY_SIZE          
