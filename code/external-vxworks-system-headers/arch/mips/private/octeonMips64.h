/* octeon_mips64.h */

/*
* Copyright (c) 2008,2010 Wind River Systems, Inc.
*
* The right to copy, distribute, modify or otherwise make use
* of this software may be licensed only pursuant to the terms
* of an applicable Wind River license agreement.
*/

/*

modification history
--------------------
01e,11nov10,slk  add configuration 4 reg
01d,09nov10,d_c  Add default definition of CVMX_CACHE_LINE_SIZE
01c,01nov10,d_c  Add scratch memory defines
01b,14oct10,rlg  addition of checks for assembler to keep from getting
                 warnings is c code
01a,24sep08,pgh  Fix copyright.

DESCRIPTION

*/

#ifndef _OCTEON_MIPS64_H_
#define _OCTEON_MIPS64_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "arch/mips/private/octeonBoard.h"

#ifdef _ASMLANGUAGE
/*
* MIPS Coprocessor 0 regs
*/
#ifdef C0_INDEX
	#undef C0_INDEX
#endif /* C0_INDEX */
#define C0_INDEX        $0,0
#ifdef C0_RANDOM
	#undef C0_RANDOM
#endif /* C0_RANDOM */
#define C0_RANDOM       $1,0
#ifdef C0_ENTRYLO0
	#undef C0_ENTRYLO0
#endif /* C0_ENTRYLO0 */
#define C0_ENTRYLO0     $2,0
#ifdef C0_ENTRYLO1
	#undef C0_ENTRYLO1
#endif /* C0_ENTRYLO1 */
#define C0_ENTRYLO1     $3,0
#ifdef C0_CONTEXT
	#undef C0_CONTEXT
#endif /* C0_CONTEXT */
#define C0_CONTEXT      $4,0
#ifdef C0_PAGEMASK
	#undef C0_PAGEMASK
#endif /* C0_PAGEMASK */
#define C0_PAGEMASK	$5,0
#ifdef C0_PAGEGRAIN
	#undef C0_PAGEGRAIN
#endif /* C0_PAGEGRAIN */
#define C0_PAGEGRAIN	$5,1
#ifdef C0_WIRED
	#undef C0_WIRED
#endif /* C0_WIRED */
#define C0_WIRED	$6,0
#ifdef C0_HWRENA
	#undef C0_HWRENA
#endif/* C0_HWRENA */
#define C0_HWRENA	$7,0
#ifdef C0_BADVADDR
	#undef C0_BADVADDR
#endif /* C0_BADVADDR */
#define C0_BADVADDR	$8,0
#ifdef C0_COUNT
	#undef C0_COUNT
#endif /* C0_COUNT */
#define C0_COUNT	$9,0
#ifdef C0_ENTRYHI
	#undef C0_ENTRYHI
#endif /* C0_ENTRYHI */
#define C0_ENTRYHI	$10,0
#ifdef C0_COMPARE
	#undef C0_COMPARE
#endif /* C0_COMPARE */
#define C0_COMPARE	$11,0
#ifdef C0_STATUS
	#undef C0_STATUS
#endif /* C0_STATUS */
#define C0_STATUS	$12,0
#ifdef C0_INTCTL
	#undef C0_INTCTL
#endif /* C0_INTCTL */
#define C0_INTCTL	$12,1
#ifdef C0_SRSCTL
	#undef C0_SRSCTL
#endif /* C0_SRSCTL */
#define C0_SRSCTL	$12,1
#ifdef C0_CAUSE
	#undef C0_CAUSE
#endif /* C0_CAUSE */
#define C0_CAUSE	$13,0
#ifdef C0_EPC
	#undef C0_EPC
#endif /* C0_EPC */
#define C0_EPC		$14,0
#ifdef C0_PRIID
	#undef C0_PRIID
#endif /* C0_PRIID */
#define C0_PRIID	$15,0
#ifdef C0_EBASE
	#undef C0_EBASE
#endif /* C0_EBASE */
#define C0_EBASE	$15,1
#ifdef C0_CONFIG
	#undef C0_CONFIG
#endif /* C0_CONFIG */
#define C0_CONFIG	$16,0
#ifdef C0_CONFIG1
	#undef C0_CONFIG1
#endif /* C0_CONFIG1 */
#define C0_CONFIG1	$16,1
#ifdef C0_CONFIG2
	#undef C0_CONFIG2
#endif /* C0_CONFIG2 */
#define C0_CONFIG2	$16,2
#ifdef C0_CONFIG3
	#undef C0_CONFIG3
#endif /* C0_CONFIG3 */
#define C0_CONFIG3	$16,3
#ifdef C0_CONFIG4
	#undef C0_CONFIG4
#endif /* C0_CONFIG4 */
#define C0_CONFIG4	$16,4
#ifdef C0_WATCHLO0
	#undef C0_WATCHLO0
#endif /* C0_WATCHLO0 */
#define C0_WATCHLO0	$18,0
#ifdef C0_WATCHLO1
	#undef C0_WATCHLO1
#endif /* C0_WATCHLO1 */
#define C0_WATCHLO1	$18,1
#ifdef C0_WATCHHI0
	#undef C0_WATCHHI0
#endif /* C0_WATCHHI0 */
#define C0_WATCHHI0	$19,0
#ifdef C0_WATCHHI1
	#undef C0_WATCHHI1
#endif /* C0_WATCHHI1 */
#define C0_WATCHHI1	$19,1
#ifdef C0_XCONTEXT
	#undef C0_XCONTEXT
#endif /* C0_XCONTEXT */
#define C0_XCONTEXT	$20,0
#ifdef C0_DEBUG
	#undef C0_DEBUG
#endif /* C0_DEBUG */
#define C0_DEBUG	$23,0
#ifdef C0_DEPC
	#undef C0_DEPC
#endif /* C0_DEPC */
#define C0_DEPC		$24,0
#ifdef C0_PERFCNT0
	#undef C0_PERFCNT0
#endif /* C0_PERFCNT0 */
#define C0_PERFCNT0	$25,1
#ifdef C0_PERFCNT1
	#undef C0_PERFCNT1
#endif /* C0_PERFCNT1 */
#define C0_PERFCNT1	$25,3
#ifdef C0_CACHEERR0
	#undef C0_CACHEERR0
#endif /* C0_CACHEERR0 */
#define C0_CACHEERR0	$27,0
#ifdef C0_CACHEERR1
	#undef C0_CACHEERR1
#endif /* C0_CACHEERR1 */
#define C0_CACHEERR1	$27,1
#ifdef C0_TAGLO
	#undef C0_TAGLO
#endif /* C0_TAGLO */
#define C0_TAGLO	$28,2
#ifdef C0_DATALO
	#undef C0_DATALO
#endif /* C0_DATALO */
#define C0_DATALO	$28,3
#ifdef C0_TAGHI
	#undef C0_TAGHI
#endif /* C0_TAGHI */
#define C0_TAGHI	$29,2
#ifdef C0_DATAHI
	#undef C0_DATAHI
#endif /*C0_DATAHI */
#define C0_DATAHI	$29,3
#ifdef C0_ERROREPC
	#undef C0_ERROREPC
#endif /* C0_ERROREPC */
#define C0_ERROREPC	$30,0
#ifdef C0_DESAVE
	#undef C0_DESAVE
#endif /* C0_DESAVE */
#define C0_DESAVE	$31,0
#ifdef C0_CVMCTL
	#undef C0_CVMCTL
#endif /* C0_CVMCTL */
#define C0_CVMCTL	$9,7
#ifdef C0_CVMMEMCTL
	#undef C0_CVMMEMCTL
#endif /* C0_CVMMEMCTL */
#define C0_CVMMEMCTL	$11,7
#ifdef C0_CVMCOUNT
	#undef C0_CVMCOUNT
#endif /* C0_CVMCOUNT */
#define C0_CVMCOUNT	$9,6
#ifdef C0_MULTICOREDEBEG
	#undef C0_MULTICOREDEBEG
#endif /* C0_MULTICOREDEBEG */
#define C0_MULTICOREDEBEG	$22,0


#endif /* _ASMLANGUAGE */


/*
 * Other Octeon defines 
 */


#define INT_VEC_BASE            0x40

#define IV_INTSW0_NUM           (INT_VEC_BASE+0)
#define IV_INTSW1_NUM           (INT_VEC_BASE+1)
#define IV_INT0_NUM             (INT_VEC_BASE+2)        /* INT 0 */
#define IV_INT1_NUM             (INT_VEC_BASE+3)        /* INT 1 */
#define IV_ETHER_NUM            (INT_VEC_BASE+4)        /* INT 2 */
#define IV_AUXCLK_NUM           (INT_VEC_BASE+5)        /* INT 3 */
#define IV_UART0_NUM            (INT_VEC_BASE+6)        /* INT 4 */
#define IV_CLOCK_NUM            (INT_VEC_BASE+7)        /* INT 5 */
#define IV_UART1_NUM            (INT_VEC_BASE+8)


#define OCTEON_NUM_CORES    16 
#define C0_EBASE_CORE_MASK 0xff

 
/* Interrupts for clk, CIU0, CIU1 */
/*
 * interrupt priority: 7=high----0=low
 */
#define INT_PRIO_MSB    TRUE 
#define INTERRUPT_CLOCK SR_IBIT8
#define INTERRUPT_CIU_0 SR_IBIT4
#define INTERRUPT_CIU_1 SR_IBIT3


#define DEFAULT_SR (SR_CU2|SR_CU0| \
	INTERRUPT_CLOCK|INTERRUPT_CIU_0|INTERRUPT_CIU_1| \
	SR_KX|SR_SX|SR_UX|SR_INT_ENABLE)


/* Debugger related defines */
#define DEBUG_STACK_SIZE        1024    /* Size of the debugger stack */
#define DEBUG_NUMREGS           64    /* Total number of (64 bit)registers stored. Must match debug_handler.S */


#define EXCEPTION_BASE_BASE     0          /* must be 4k aligned */
#define EXCEPTION_BASE_INCR     (4*1024)   /* Increment size for exception base addresses (4k minimum) */
#define OCTEON_EXCEPTION_VECTOR_BLOCK_SIZE  (OCTEON_NUM_CORES*EXCEPTION_BASE_INCR) /* 16 4k blocks */

/* Bootloader debugger stub register save area follows exception vector space */
#define BOOTLOADER_DEBUG_REG_SAVE_BASE  (EXCEPTION_BASE_BASE + OCTEON_EXCEPTION_VECTOR_BLOCK_SIZE)
#define BOOTLOADER_DEBUG_REG_SAVE_SIZE  (OCTEON_NUM_CORES * DEBUG_NUMREGS * 8)

/* debugger stack follows reg save area */
#define BOOTLOADER_DEBUG_STACK_BASE  (BOOTLOADER_DEBUG_REG_SAVE_BASE + BOOTLOADER_DEBUG_REG_SAVE_SIZE)
#define BOOTLOADER_DEBUG_STACK_SIZE  (OCTEON_NUM_CORES * DEBUG_STACK_SIZE)
#define BOOTLOADER_END_RESERVED_SPACE   (BOOTLOADER_DEBUG_STACK_BASE + BOOTLOADER_DEBUG_STACK_SIZE)

#define BOOTLOADER_PRIV_DATA_BASE       (EXCEPTION_BASE_BASE + 0x800)
#define BOOTLOADER_BOOT_VECTOR          (BOOTLOADER_PRIV_DATA_BASE)
#define BOOTLOADER_DEBUG_TRAMPOLINE     (BOOTLOADER_BOOT_VECTOR + BOOT_VECTOR_SIZE)   /* WORD */
#define BOOTLOADER_DEBUG_GP_REG         (BOOTLOADER_DEBUG_TRAMPOLINE + 4)   /* WORD */
#define BOOTLOADER_DEBUG_FLAGS_BASE     (BOOTLOADER_DEBUG_GP_REG + 4)  /* WORD * NUM_CORES */
#define BOOTLOADER_NEXT_AVAIL_ADDR      (BOOTLOADER_DEBUG_FLAGS_BASE + 4*OCTEON_NUM_CORES)

/* Address used for boot vectors for non-zero cores */
#define BOOT_VECTOR_BASE    (0x80000000 | BOOTLOADER_BOOT_VECTOR)
#define BOOT_VECTOR_NUM_WORDS           (8)
#define BOOT_VECTOR_SIZE                ((OCTEON_NUM_CORES*4)*BOOT_VECTOR_NUM_WORDS)

/* Addresses used to pass parameters to secondary cores at startup */
#define BOOT_REGION_STORE_START		0x80000600
#define BOOT_REGION_STORE_ENTRY		(BOOT_REGION_STORE_START+0x00)
#define BOOT_REGION_STORE_PARAMETER	(BOOT_REGION_STORE_START+0x08)
#define BOOT_REGION_STORE_SP		(BOOT_REGION_STORE_START+0x10)
#define BOOT_REGION_STORE_GP		(BOOT_REGION_STORE_START+0x18)
#define BOOT_REGION_WAIT_CHANNEL	BOOT_REGION_STORE_ENTRY

/* Scratch memory used by early boot code */

#define SCRATCH_MEM_ADRS                0xffff9B00
#define SCRATCH_MEM_SIZE                0x1B00

/* Flag to track whether DDR clock has been initialized */
#define SCRATCH_MEM_DDR_CLOCK_INIT_ADRS (SCRATCH_MEM_ADRS - 0x08)

/* Flag to track whether cpu clock rate been initialized */
#define SCRATCH_MEM_CPU_CLOCK_RATE_ADRS (SCRATCH_MEM_ADRS - 0x10)

/* Top of stack */
#define SCRATCH_MEM_STACK_ADRS          (SCRATCH_MEM_ADRS - 0x18)

/* Warning - this is copied from the SDK */

#ifndef CVMX_CACHE_LINE_SIZE
#define CVMX_CACHE_LINE_SIZE     128
#elif CVMX_CACHE_LINE_SIZE != 128
#warning CVMX_CACHE_LINE_SIZE is not consistent between Cavium SDK and \
  vxWorks arch. See target/src/hwif/fw/cavium_sdk for conflicting definition.
#endif

#ifndef CVMX_CACHE_LINE_ALIGNED
#define CVMX_CACHE_LINE_ALIGNED \
  __attribute__ ((aligned (CVMX_CACHE_LINE_SIZE)))
#endif

#ifdef __cplusplus
}
#endif


#endif /* _OCTEON_MIPS64_H_ */
