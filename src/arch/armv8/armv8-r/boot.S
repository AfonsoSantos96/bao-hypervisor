/** 
 * Bao, a Lightweight Static Partitioning Hypervisor 
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      Gero Schwaericke <gero.schwaericke@tum.de>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details. 
 *
 */

#include <arch/bao.h>
#include <arch/sysregs.h>
#include <arch/page_table.h>
#include <asm_defs.h>

.data 
.align 3
/**
 * barrier is used to minimal synchronization in boot - other cores wait for
 * bsp to set it.
 */
_barrier: .8byte 0			

/**
 * 	The following code MUST be at the base of the image, as this is bao's entry
 *	point. Therefore .boot section must also be the first in the linker script.
 *  DO NOT implement any code before the _reset_handler in this section.
 */
 .section ".boot", "ax"
.globl _reset_handler
.globl _el2_entry
_el2_entry:
_reset_handler:

	/** 
	 * TODO: before anything...
	 * perform sanity checks on ID registers to ensure support for
	 * VE and TZ, 4K granule and possibly other needed features. 
	 * Also, check current exception level. Act accordingly. 
	 * However, we expect to be running at EL2 at this point.
	 */

	/**
	 * Not following any ABI for registers in this boot code.
	 * The following registers are however reserved to be passed to main
	 * as arguments:
	 * 		r0 -> contains cpu id
	 *		r1 -> contains image base load address
	 *		r2 -> contains config binary load address (passed in x0) 
	 * Register x9 is reserved to indicate if the current cpu is master (negated)
	 */

	mov r2, r0
	mrc p15, 0, r0, c0, c0, 5       // Read MPIDR
	adr r1, _image_start

	/* 
	 * Install vector table physical address early, in case exception occurs
	 * during this initialization.
	 */
	adr	r3, _hyp_vector_table
	mcr p15, 4, r3, c12, c0, 0       // Write HVBAR


	/**
	 * 	Linearize cpu id according to the number of clusters and processors per
	 * cluster. We are only considering two levels of affinity.
	 *  TODO: this should be done some other way. We shouln'd depend on the platform
	 * description this early in the initialization.
	 */

	mov r3, r0, lsr #8 
	and r3, r3, 0xff
	adr r4, platform
	ldr r4, [r4, PLAT_ARCH_OFF+PLAT_ARCH_CLUSTERS_OFF+PLAT_CLUSTERS_CORES_NUM_OFF]
	ldr r5, =BAO_VAS_BASE
	sub r4, r4, r5
	add r4, r4, r1
	mov r5, #0
	mov r7, #0
1:
	cmp r5, r3
	bge	2f
	ldrb r6, [r4]
	add r4, r4, #1
	add r5, r5, #1
	add r7, r7, r6
	b 	1b
2:
	and r0, r0, #0xff
	add r0, r0, r7

.pushsection .data
_master_set:
	.8byte 	0
.popsection
/**
 * For setting the master cpu, we assume only one cpu is initially activated 
 * which later will turn on all the others. Therefore, there is no concurrency 
 * when setting CPU_MASTER and no atomic operations are needed.
 * As a result r9 should be set to !is_cpu_master
 */
_set_master_cpu:
	adr	r3, _master_set
	ldr r9, [r3]
	cmp r9, #0
	bne 7f
	mov	r9, #1
	str r9, [r3]
	mov r9, #0
	adr r3, CPU_MASTER
	str r0, [r3]
7: 

	/** 
	 * TODO: bring the system to a well known state. This includes disabling 
	 * the MMU (done), all caches (missing i$), BP and others...
	 * and invalidating them.	
	 */
 
	/* Clear stack pointer to avoid unaligned SP exceptions during boot */
    mov r3, #0
	mov sp, r3

	/* Disable caches and MPU */
	mrc p15, 0, r0, c1, c0, 0       // Read SCTLR
    bic r0, r0, #0x05               // Disable MPU (M bit) and data cache (C bit)
    bic r0, r0, #0x1000             // Disable instruction cache (I bit)
    dsb                             // Ensure all previous loads/stores have completed
    mcr p15, 0, r0, c1, c0, 0       // Write SCTLR
    isb                             // Ensure subsequent insts execute wrt new MPU settings


	/* Invalidate caches */
	/* Should we also clean ? */
	mov r10, r0
	mov r11, r1
	mov r12, r2

	mov r0, #0
	bl	cache_invalidate
	cmp r9, #0
	bne 1f
	mov r0, #2
	bl	cache_invalidate
1:
	mov r0,	r10
	mov r1,	r11
	mov r2,	r12

	iciallu


map_cpu:
	/**
	 *    r3 -> cpu base phys
	 *    r4 -> current pt base phys
	 *    r5 -> pte index
	 *    r6 -> phys addr
	 *    r8 -> aux 
	 */

	/* get CPUs base address */
	mov r8, #CPU_IF_SIZE_SECTION
	adr r3, _cpu_if_base
	add r3, r3, r8
	/* get self cpu base address */
	mov r8, #CPU_SIZE
	
	madd r3, r0, r8, r3
	msr HTPIDR, r3
	mov	r11, r3	
	add	r12, r3, r8
	bl	clear	

	mov	r11, r3									// r11 stores the cpu struct address
	/* Region 0 - CPU Struct */
//    LDR     r3, =Image$$DATA$$Base
    ldr r2, =((Non_Shareable<<3) | (RW_Access<<1))
    orr r11, r11, r2
    mcr p15, 0, r11, c6, c8, 0                   // write PRBAR0
	add r11, r11, r8
//	LDR r3, =Image$$DATA$$ZI$$Limit
    add r11, r11, #63
    bfc r11, #0, #6                              // align Limit to 64bytes
    ldr r11, =((AttrIndx0<<1) | (ENable))
    orr r11, r11, r2
    mcr p15, 0, r3, c6, c8, 1                   // write PRLAR0
	
	
map_cpu_interface:

	/* Region 1 - CPU Interfaces */
//    LDR     r1, =Image$$DATA$$Base
    adr r3, _cpu_if_base
	ldr r8, =((Non_Shareable<<3) | (RW_Access<<1))
    orr r3, r3, r8
    mcr p15, 0, r3, c6, c8, 4                   // write PRBAR1
	mov r8, #CPU_IF_SIZE_SECTION
	add r3, r3, r8								//    ldr r1, =Image$$DATA$$ZI$$Limit
    //add r3, r3, #63
    //bfc r1, #0, #6                              // align Limit to 64bytes
    ldr r8, =((AttrIndx0<<1) | (ENable))
    orr r3, r3, r8
    mcr p15, 0, r3, c6, c8, 5                   // write PRLAR1
	
	
setup_cpu:

	mov r3, #0
	mcr p15, 4, r3, c1, c1, 2		// Write on HCPTR

	/* setup translation configurations */
	//ldr r3, =TCR_EL2_DFLT
	//msr	TCR_EL2, r3

	/* set hypervisor default memory attributes */
	//ldr r3, =MAIR_EL2_DFLT
	//msr	MAIR_EL2, r3

/*	mov r8, #(CPU_SIZE + (PT_SIZE*(PT_LVLS-1)))
	adrp r3, _dmem_phys_beg
	madd r3, r0, r8, r3
	add r3, r3, #CPU_ROOT_PT_OFF
	msr TTBR0_EL2, r3
*/

	/* set up cpu stack */
//	mov r3, #(SPSel_SP)								
//	msr SPSEL, r3	
	ldr r3, =BAO_CPU_BASE
	add r3, r3, #(CPU_STACK_OFF + CPU_STACK_SIZE)
	mov SP, r3

	/**	
	 * TODO: set implementation defined registers such as ACTLR or AMAIR.
	 * Maybe define a macro for this in a implementation oriented directory
	 * inside arch.
	 */

	/**
	 * TODO: invalidate caches, TLBs and branch prediction.
	 * Need for barriers?
	 */

	ldr r5, =_enter_vas

	/* Enable MPU and caches */
	ldr r4, =(SCTLR_RES1 | SCTLR_M | SCTLR_C | SCTLR_I)
	mcr p15, 4, r4, c1, c0, 0
	
	dsb	nsh
	isb
	
	b  r5

_enter_vas:		/// change label name to _clear_bss

	/* If this is bsp (cpu 0) clear bss */
	cmp r9, #0
	bne 1f
	ldr	r11, =_bss_start	
	ldr	r12, =_bss_end	
	bl	clear	

	adr r5, _barrier
	mov r4, #2
	str r4, [r5]	

1:
	/* wait for bsp to finish clearing bss */
	ldr r4, _barrier
	cmp r4, #2
	blt 1b

	isb

	b init

	/* This point should never be reached */
	b	.				

/***** 	Helper functions for boot code. ******/

 .func clear
clear:
2:
	mov r8, #0
	cmp	r11, r12			
	bge 1f
	str	r8, [r11]
	add r11, r11, #8 	
	b	2b				
1:
	ret
.endfunc

/*
 * Code taken from "Application Note Bare-metal Boot Code for ARMv8-A
 * Processors - Version 1.0"
 *
 * r0 - cache level to be invalidated (0 - dl1$, 1 - il1$, 2 - l2$)
 */
.func cache_invalidate
cache_invalidate:
//	msr csselr_el1, r0 
	MCR p15, 2, r0, c0, c0, 0 
//	mrs r4, ccsidr_el1 // read cache size id.
	MRC p15, 1, r4, c0, c0, 0 
	and r1, r4, #0x7
	add r1, r1, #0x4 // r1 = cache line size.
	ldr r3, =0x7fff
	and r2, r3, r4, lsr #13 // r2 = cache set number – 1.
	ldr r3, =0x3ff
	and r3, r3, r4, lsr #3 // r3 = cache associativity number – 1.
	clz w4, w3 // r4 = way position in the cisw instruction.
	mov r5, #0 // r5 = way counter way_loop.
way_loop:
	mov r6, #0 // r6 = set counter set_loop.
set_loop:
	lsl r7, r5, r4
	orr r7, r0, r7 // set way.
	lsl r8, r6, r1
	orr r7, r7, r8 // set set.
	dc cisw, r7 // clean and invalidate cache line.
	add r6, r6, #1 // increment set counter.
	cmp r6, r2 // last set reached yet?
	ble set_loop // if not, iterate set_loop,
	add r5, r5, #1 // else, next way.
	cmp r5, r3 // last way reached yet?
	ble way_loop // if not, iterate way_loop
	ret
.endfunc


.global psci_boot_entry
.func psci_boot_entry
psci_boot_entry:
warm_boot:

	adr	r3, _hyp_vector_table
	msr	VBAR_EL2, r3

	/* save r0 which contains pointer to saved state psci context */
	mov r10, r0
    	/* invalidate l1$ */
	mov r0, #0
	bl	cache_invalidate

	/* restore all needed register state */
	ldp r5, r6, [r10, #0]
//	msr TCR_EL2, r5
//	msr TTBR0_EL2, r6
	ldp r5, r6, [r10, #16]
	msr MAIR_EL2, r5
	msr HCPTR, r6
	ldp r5, r6, [r10, #32]
	msr HCR_EL2, r5
	msr VMPIDR_EL2, r6
	ldp r5, r6, [r10, #48]
//	msr VTCR_EL2, r5
	msr VTTBR_EL2, r6
    ldp r0, r5, [r10, #64]   /* wake up reason is the arg of the later psci_wake call */

	/* map original bootstrap flat mappings */
//	mrs r3, TTBR0_EL2
	adrp r1, _image_start
	PTE_INDEX_ASM r1, r1, 0 
	add r3, r3, r1
	dc civac, r3  //we invalidated l1$, but make sure the pte is not in l2$
	add r5, r5, #(PTE_HYP_FLAGS | PTE_TABLE)
	str r5, [r3]

	/* Install vector table virtual address*/
	ldr	r3, =_hyp_vector_table
	msr	VBAR_EL2, r3

    tlbi	alle2 
	dsb	nsh
	isb

	/* Enable MMU and caches */
	ldr r4, =(SCTLR_RES1 | SCTLR_M | SCTLR_C | SCTLR_I)
	msr	HSCTLR, r4

	dsb	nsh
	isb
	
	ldr r5, =_enter_vas_warm
	br  r5		

_enter_vas_warm:
	/* Unmap bootstrat flat mappings */
	ldr r4, =BAO_CPU_BASE
	// TODO: Calculate offset when not using virtualization
	add r3, r4, #(CPU_STACK_OFF+CPU_STACK_SIZE)

	add r4, r4, #CPU_ROOT_PT_OFF
	PTE_INDEX_ASM r5, r1, 0 
	str xzr, [r4, r5]
    tlbi	alle2
	dsb	nsh
	isb

    /* Initialize stack pointer */
    mov sp, r3

	bl	psci_wake
	b 	.

.endfunc
