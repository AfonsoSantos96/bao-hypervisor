#include <arch/bao.h>
#include <arch/sysregs.h>
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
	ldr r1, =_image_start

	mrc p15, 0, r5, c0, c2, 4
	
	/* 
	 * Install vector table physical address early, in case exception occurs
	 * during this initialization.
	 */
	ldr	r3, =_hyp_vector_table
	mcr p15, 4, r3, c12, c0, 0       // Write HVBAR


	/**
	 * 	Linearize cpu id according to the number of clusters and processors per
	 * cluster. We are only considering two levels of affinity.
	 *  TODO: this should be done some other way. We shouln'd depend on the platform
	 * description this early in the initialization.
	 */

	mov r3, r0, lsr #8 
	and r3, r3, #0xff
	ldr r4, =platform
	ldr r4, [r4, #280]
	ldr r5, =BAO_AS_BASE
	sub r4, r4, r5													//////////////////////// REVIEW THIS PART!!!!!!!!!!!!!!
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
	ldr	r3, =_master_set
	ldr r9, [r3]
	cmp r9, #0
	bne 7f
	mov	r9, #1
	str r9, [r3]
	mov r9, #0
	ldr r3, =CPU_MASTER
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
//	mrc p15, 0, r8, c1, c0, 0       // Read SCTLR
	mcr p15, 4, r8, c1, c0, 0		// HSCTRL ->  EL2-MPU

    bic r8, r8, #0x05               // Disable MPU (M bit) and data cache (C bit)
    bic r8, r8, #0x1000             // Disable instruction cache (I bit)
    dsb                             // Ensure all previous loads/stores have completed
    mcr p15, 4, r8, c1, c0, 0		///// HSCTRL ->  EL2-MPU
//    mcr p15, 0, r8, c1, c0, 0       // Write SCTLR
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

	/* this instruction ignores the r10 value */
	mcr p15, 0, r10, c7, c5, 0		// iciallu

map_cpu:
	/**
	 *    r3 -> cpu_X base phys
	 *    r4 -> cpu if base
	 *	  r7 -> aux
	 *    r8 -> aux 
	 */

	/* get CPUs base address */
	mov r8, #128
	ldr r3, =_cpu_if_base
	add r3, r3, r8

	/* get self CPU_X base address */
	mov r7, CPU_SIZE
	add r7, r7, CPU_STACK_SIZE //////////////////////////////////////////
	mla r3, r0, r7, r3


	mcr p15, 4, r3, c13, c0, 2                  // write HTPIDR
	mov	r11, r3	
	add	r12, r3, r7
	bl	clear	

	mov	r11, r3									// r11 stores the cpuX struct base address

	/* Region 0 - CPU Struct 
    ldr r8, =((Non_Shareable<<3) | (RW_Access<<1))							/////////////// ROTATE R11 << 6
    orr r11, r11, r8
    mcr p15, 0, r11, c6, c8, 0                  // write PRBAR0
	
	mov r11, r3
	add r11, r11, r7
//    add r11, r11, #63
//    bfc r11, #0, #6                           // align Limit to 64bytes
    ldr r8, =((AttrIndx0<<1) | (ENable))
    orr r11, r11, r8
    mcr p15, 0, r11, c6, c8, 1                   // write PRLAR0
	*/
	
map_cpu_interface:

	/* Region 1 - CPU Interfaces 
    ldr r4, =_cpu_if_base						// Initial region address
    mov r8, #CPU_IF_SIZE_SECTION
	ldr r7, =((Non_Shareable<<3) | (RW_Access<<1))
    orr r7, r7, r4
    mcr p15, 0, r7, c6, c8, 4                   // write PRBAR1

	add r4, r4, r8								// Limit region adress
    //add r4, r4, #63
    //bfc r1, #0, #6                            // align Limit to 64bytes
    ldr r8, =((AttrIndx0<<1) | (ENable))
    orr r4, r4, r8
    mcr p15, 0, r4, c6, c8, 5                   // write PRLAR1
	
	
	
	// Region 3 - Peripherals
	ldr     r1, =0x9A000000
    ldr     r2, =((Non_Shareable<<3) | (RW_Access<<1))
	orr     r1, r1, r2
	mcr     p15, 0, r1, c6, c9, 4                   // write PRBAR3
	ldr     r1, =0xAFFFFFC0
	sub     r1, r1, #1
	bfc     r1, #0, #6
	ldr     r2, =((AttrIndx0<<1) | (ENable))
	orr     r1, r1, r2
	mcr     p15, 0, r1, c6, c9, 5                   // write PRLAR3
	*/
	
setup_cpu:
	/**
	 *    r3 -> cpu_X base phys
	 *    r4 -> cpu if base
	 *	  r7 -> aux
	 *    r8 -> aux 
	 */

	mov r7, #0
	mcr p15, 4, r7, c1, c1, 2					// Write on HCPTR

	/* set up cpu stack */
//	mov r3, #(SPSel_SP)								
//	msr SPSEL, r3	

//	ldr r3, =BAO_CPU_BASE
	add r3, r3, CPU_STACK_OFF
	add r3, r3, CPU_STACK_SIZE
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

	/* Enable MPU and caches */
	ldr r7, =(SCTLR_RES1 | SCTLR_M | SCTLR_C | SCTLR_I)
//	mcr p15, 4, r7, c1, c0, 0		///// HSCTRL ->  EL2-MPU
//	mcr p15, 0, r7, c1, c0, 0		///// SCTLR  ->  EL1-MPU
	
	dsb	nsh
	isb


_enter_vas:		/// change label name to something like _clear_bss

	/* If this is bsp (cpu 0) clear bss */
	cmp r9, #0
	bne 1f
	ldr	r11, =_bss_start	
	ldr	r12, =_bss_end	
	bl	clear	

	ldr r5, =_barrier
	mov r7, #2
	str r7, [r5]	

1:
	/* wait for bsp to finish clearing bss */
	ldr r7, =_barrier
	ldr r8, [r7]
	cmp r8, #2
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
	bx lr
.endfunc

/*
 * Code taken from "Application Note Bare-metal Boot Code for ARMv8-A
 * Processors - Version 1.0"
 *
 * r0 - cache level to be invalidated (0 - dl1$, 1 - il1$, 2 - l2$)
 */
.func cache_invalidate
cache_invalidate:
	MCR p15, 2, r0, c0, c0, 0 // msr csselr_el1, r0 
//	mrs r4, ccsidr_el1 				
	MRC p15, 1, r4, c0, c0, 0 		// read cache size id.
	and r1, r4, #0x7
	add r1, r1, #0x4 				// r1 = cache line size.
	ldr r3, =0x7fff
	and r2, r3, r4, lsr #13 		// r2 = cache set number – 1.
	ldr r3, =0x3ff
	and r3, r3, r4, lsr #3 			// r3 = cache associativity number – 1.
	clz r4, r3 						// r4 = way position in the cisw instruction.
	mov r5, #0 						// r5 = way counter way_loop.
way_loop:
	mov r6, #0 						// r6 = set counter set_loop.
set_loop:
	lsl r7, r5, r4
	orr r7, r0, r7 					// set way.
	lsl r8, r6, r1
	orr r7, r7, r8 					// set set.
	mcr p15, 0, r7, c7, c14, 2 		// clean and invalidate cache line.
	add r6, r6, #1 					// increment set counter.
	cmp r6, r2 						// last set reached yet?
	ble set_loop 					// if not, iterate set_loop,
	add r5, r5, #1 					// else, next way.
	cmp r5, r3 						// last way reached yet?
	ble way_loop 					// if not, iterate way_loop
	bx lr
.endfunc




.global psci_boot_entry
.func psci_boot_entry
psci_boot_entry:
warm_boot:

	/*adr	r3, _hyp_vector_table
	msr	VBAR_EL2, r3*/

	/* save r0 which contains pointer to saved state psci context */
	mov r10, r0
    	/* invalidate l1$ */
	mov r0, #0
	bl	cache_invalidate

	/* restore all needed register state */

	ldr r5, [r10, #8]			//	ldp r5, r6, [r10, #16]
	ldr r6, [r10, #8]			// Ver com o Martins a necessidade de restaurar MAIR_EL1 e MAIR_EL2
	mcr p15, 4, r5, c10, c2, 0	//msr MAIR_EL2, r5
	mcr p15, 4, r6, c1, c1, 2 	//msr HCPTR, r6

	ldr r5, [r10, #16]			//ldp r5, r6, [r10, #32]
	ldr r6, [r10, #16]
	mcr p15, 4, r5, c1, c1, 0	//msr HCR_EL2, r5
	mcr p15, 4, r6, c0, c0, 5	//msr VMPIDR_EL2, r6

//	ldr r5, [r10, #24]			//	ldp r5, r6, [r10, #48]
//	ldr r6, [r10, #24]	
//	msr VTCR_EL2, r5
//	msr VTTBR_EL2, r6
//    ldp r0, r5, [r10, #64]   /* wake up reason is the arg of the later psci_wake call */

	/* Install vector table virtual address */
	ldr	r3, =_hyp_vector_table
	mcr p15, 4, r3, c12, c0, 0	// msr	VBAR_EL2, r3

 //   tlbi	alle2 
	dsb	nsh
	isb

	/* Enable MPU and caches */
	ldr r4, =(SCTLR_RES1 | SCTLR_M | SCTLR_C | SCTLR_I)
	mcr p15, 4, r4, c1, c0, 0		// msr	HSCTLR, r4

	dsb	nsh
	isb
	


_enter_vas_warm:
	/* Unmap bootstrat flat mappings */
	ldr r4, =BAO_CPU_BASE
	// TODO: Calculate offset when not using virtualization
	add r3, r4, #(128)

    /* Initialize stack pointer */
    mov sp, r3

//	bl	psci_wake
	b 	.

.endfunc
