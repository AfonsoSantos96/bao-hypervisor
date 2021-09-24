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

/*
 *		TODO: 
 *				psci_boot_entry
 *				warm_boot
 *				MPU initialization of the guests
 */


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
	 * 		x0 -> contains cpu id
	 *		x1 -> contains image base load address
	 *		x2 -> contains config binary load address (passed in x0) 
	 * Register x9 is reserved to indicate if the current cpu is master (negated)
	 */

	MRC p15, 0, r0, c0, c0, 5       // Read MPIDR
	ANDS r0, r0, 0xF				// R0 contains the CPUID
	adrp r1, _image_start


    // Change EL2 exception base address
    LDR r0, =_hyp_vector_table
    MCR p15, 4, r0, c12, c0, 0      //  Write to R0 to HVBAR


	/**
	 * 	Linearize cpu id according to the number of clusters and processors per
	 * cluster. We are only considering two levels of affinity.
	 *  TODO: this should be done some other way. We shouln'd depend on the platform
	 * description this early in the initialization.
	 */

/*				Analyze this section for the Cortex-R52				*/

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
	b.ge	2f
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
 * As a result x9 should be set to !is_cpu_master
 */
_set_master_cpu:
	adr	r3, _master_set
	ldr r9, [x3]
	cbnz r9, 7f
	mov	r9, #1
	str r9, [x3]
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

//----------------------------------------------------------------
// Disable MPU and caches
//----------------------------------------------------------------

    // Disable MPU and cache in case it was left enabled from an earlier run
    // This does not need to be done from a cold reset

        MRC p15, 0, r3, c1, c0, 0       // Read System Control Register
        BIC r3, r3, #0x05               // Disable MPU (M bit) and data cache (C bit)
        BIC r3, r3, #0x1000             // Disable instruction cache (I bit)
        DSB                             // Ensure all previous loads/stores have completed
        MCR p15, 0, r3, c1, c0, 0       // Write System Control Register
        ISB                             // Ensure subsequent insts execute wrt new MPU settings


//----------------------------------------------------------------
// Cache invalidation. However Cortex-R52 provides CFG signals to 
// invalidate cache automatically out of reset (CFGL1CACHEINVDISx)
//----------------------------------------------------------------

        DSB             // Complete all outstanding explicit memory operations

        MOV r0, #0

        MCR p15, 0, r0, c7, c5, 0       // Invalidate entire instruction cache

        // Invalidate Data/Unified Caches

        MRC     p15, 1, r0, c0, c0, 1      // Read CLIDR
        ANDS    r3, r0, #0x07000000        // Extract coherency level
        MOV     r3, r3, LSR #23            // Total cache levels << 1
        B.EQ     Finished                   // If 0, no need to clean

        MOV     r10, #0                    // R10 holds current cache level << 1
Loop1:  ADD     r2, r10, r10, LSR #1       // R2 holds cache "Set" position 
        MOV     r1, r0, LSR r2             // Bottom 3 bits are the Cache-type for this level
        AND     r1, r1, #7                 // Isolate those lower 3 bits
        CMP     r1, #2
        B.LT     Skip                       // No cache or only instruction cache at this level

        MCR     p15, 2, r10, c0, c0, 0     // Write the Cache Size selection register
        ISB                                // ISB to sync the change to the CacheSizeID reg
        MRC     p15, 1, r1, c0, c0, 0      // Reads current Cache Size ID register
        AND     r2, r1, #7                 // Extract the line length field
        ADD     r2, r2, #4                 // Add 4 for the line length offset (log2 16 bytes)
        LDR     r4, =0x3FF
        ANDS    r4, r4, r1, LSR #3         // R4 is the max number on the way size (right aligned)
        CLZ     r5, r4                     // R5 is the bit position of the way size increment
        LDR     r7, =0x7FFF
        ANDS    r7, r7, r1, LSR #13        // R7 is the max number of the index size (right aligned)

Loop2:  MOV     r9, r4                     // R9 working copy of the max way size (right aligned)

#ifdef __THUMB__
Loop3:  LSL     r12, r9, r5
        ORR     r11, r10, r12              // Factor in the Way number and cache number into R11
        LSL     r12, r7, r2
        ORR     r11, r11, r12              // Factor in the Set number
#else
Loop3:  ORR     r11, r10, r9, LSL r5       // Factor in the Way number and cache number into R11
        ORR     r11, r11, r7, LSL r2       // Factor in the Set number
#endif
        MCR     p15, 0, r11, c7, c6, 2     // Invalidate by Set/Way
        SUBS    r9, r9, #1                 // Decrement the Way number
        B.GE     Loop3
        SUBS    r7, r7, #1                 // Decrement the Set number
        B.GE     Loop2
Skip:   ADD     r10, r10, #2               // Increment the cache number
        CMP     r3, r10
        B.GT     Loop1



setup_cpu:

	/**
	 * 	The operation is purposely commented out.
	 *  We are assuming monitor code already enabled smp coherency.
	 */ 
	/* Turn on smp coherence */
	//mrs	x3, CPUECTLR_EL1  	
	//orr	x3, x3, #(CPUECTLR_SPEN_BIT)
	//msr	CPUECTLR_EL1, x3 

	mov r3, #0
	msr CPTR_EL2, r3

	/* set hypervisor default memory attributes */
	ldr r3, =MAIR_EL2_DFLT
	msr	MAIR_EL2, r3

	mov r8, #(CPU_SIZE + (PT_SIZE*(PT_LVLS-1)))
	adrp r3, _dmem_phys_beg
	madd x3, x0, x8, x3								// REVIEW THIS
	add r3, r3, #CPU_ROOT_PT_OFF
	msr HTTBR, x3

	/* set up cpu stack */
	mov r3, #(SPSel_SP)								
	msr SPSEL, r3									// REVIEW THIS
	ldr r3, =cpu
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

//----------------------------------------------------------------
// Enable MPU and branch to C library init
// Global Enable for Instruction and Data Caching
//----------------------------------------------------------------

        MRC     p15, 0, r0, c1, c0, 0       // Read System Control Register
        ORR     r0, r0, #0x01               // Set M bit to enable MPU
        DSB                                 // Ensure all previous loads/stores have completed
        MCR     p15, 0, r0, c1, c0, 0       // Write System Control Register
        ISB                                 // Ensure subsequent insts execute wrt new MPU settings
		
		MRC     p15, 0, r0, c1, c0, 0       // read System Control Register
		ORR     r0, r0, #(0x1 << 12)        // enable I Cache
        ORR     r0, r0, #(0x1 << 2)         // enable D Cache
        MCR     p15, 0, r0, c1, c0, 0       // write System Control Register
        ISB

	
	br  r5

_enter_vas:

	/* If this is bsp (cpu 0) clear bss */
	cbnz r9, 1f
	ldr	r10, =_bss_start	
	ldr	r11, =_bss_end	
	bl	clear	

	adr r5, _barrier
	mov r4, #2
	str r4, [r5]	

1:
	/* wait for bsp to finish clearing bss */
	ldr r4, _barrier
	cmp r4, #2
	b.lt 1b

	isb

	b init

	/* This point should never be reached */
	b	.				

/***** 	Helper functions for boot code. ******/

 .func clear
clear:
2:
	cmp	r10, r11			
	b.ge 1f				
	str	xzr, [r10], #8			// REVIEW XZR register on this instruction
	b	2b				
1:
	ret
.endfunc



/******		Still have to work from this on	 ******/

.global psci_boot_entry
.func psci_boot_entry
psci_boot_entry:
warm_boot:

	adr	x3, _hyp_vector_table
	msr	VBAR_EL2, x3

	/* save x0 which contains pointer to saved state psci context */
	mov x19, x0
    	/* invalidate l1$ */
	mov x0, #0
	bl	cache_invalidate

	/* restore all needed register state */
	ldp x5, x6, [x19, #0]
	msr TCR_EL2, x5
	msr TTBR0_EL2, x6
	ldp x5, x6, [x19, #16]
	msr MAIR_EL2, x5
	msr CPTR_EL2, x6
	ldp x5, x6, [x19, #32]
	msr HCR_EL2, x5
	msr VMPIDR_EL2, x6
	ldp x5, x6, [x19, #48]
	msr VTCR_EL2, x5
	msr VTTBR_EL2, x6
    ldp x0, x5, [x19, #64]   /* wake up reason is the arg of the later psci_wake call */

	/* map original bootstrap flat mappings */
	mrs x3, TTBR0_EL2
	adrp x1, _image_start
	PTE_INDEX_ASM x1, x1, 0 
	add x3, x3, x1
	dc civac, x3  //we invalidated l1$, but make sure the pte is not in l2$
	add x5, x5, #(PTE_HYP_FLAGS | PTE_TABLE)
	str x5, [x3]

	/* Install vector table virtual address*/
	ldr	x3, =_hyp_vector_table
	msr	VBAR_EL2, x3

    tlbi	alle2 
	dsb	nsh
	isb

	/* Enable MMU and caches */
	ldr x4, =(SCTLR_RES1 | SCTLR_M | SCTLR_C | SCTLR_I)
	msr	SCTLR_EL2, x4

	dsb	nsh
	isb
	
	ldr x5, =_enter_vas_warm
	br  x5		

_enter_vas_warm:
	/* Unmap bootstrat flat mappings */
	ldr x4, =cpu
	add x3, x4, #(CPU_STACK_OFF+CPU_STACK_SIZE)

	add x4, x4, #CPU_ROOT_PT_OFF
	PTE_INDEX_ASM x5, x1, 0 
	str xzr, [x4, x5]
    tlbi	alle2
	dsb	nsh
	isb

    /* Initialize stack pointer */
    mov sp, x3

	bl	psci_wake
	b 	.

.endfunc
