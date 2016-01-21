
/* arm-m.h - ARM CPU registers and flags for ARM-M architecture */

/*
 * Copyright (c) 2012-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */


/*
modification history
--------------------
01f,01aug13,yjw  add cache support
01e,03aug12,jdw  Add boot macro _WRS_ARM_BOOT_THUMB2
01d,06jun12,j_b  add core control registers and initialization values
01c,29may12,j_b  add control and configuration registers
01b,24may12,m_h  Add CPUID address
01a,03feb12,jdw  Created
*/

#ifndef	__INCarm_mh
#define	__INCarm_mh

#ifndef	_ASMLANGUAGE
extern int cacheArchAlignSize;
#endif	/* _ASMLANGUAGE */

#undef _CACHE_ALIGN_SIZE
#define _CACHE_ALIGN_SIZE cacheArchAlignSize

/* Define Arch features which are supported by ARM-M */

/* ARM-M only operates in Thumb2 mode */

#define ARM_THUMB2 TRUE
#define PORTABLE

/* multiple cache libraries */

#define	_ARCH_MULTIPLE_CACHELIB	TRUE

/* ARMv7-M support exclusive load/store */

#define ARM_HAS_LDREX_STREX TRUE

#define ARM_HAS_HALFWORD_INSTRUCTIONS TRUE

/* MPU is optional on some ARM-M cores */

#define ARM_HAS_NO_MMU TRUE

/* ARM-M always boots in Thumb2 mode */

#define _WRS_ARM_BOOT_THUMB2 TRUE

#define _WRS_ARCH_HAS_CPU_PWR_MGMT

/* bits in the PSR */

#define Q_BIT   (1<<27)
#define	V_BIT	(1<<28)
#define	C_BIT	(1<<29)
#define	Z_BIT	(1<<30)
#define	N_BIT	(1<<31)
#define	T_BIT	(1<<24)

/*
 * On entry to an exception the processor will use xPSR bit 9
 * to indicate if the SP has been aligned to an 8-byte boundary
 */

#define PSR_STK_ALIGN (1<<9)

/* masks for getting bits from PSR */

#define MASK_EXC_NUM      0x000001FF
#define MASK_ICIIT        0x0600FC00
#define MASK_GE           0x000F0000
#define MASK_T            0x01000000
#define MASK_CC           0xF8000000

/* PRIMASK, FAULTMASK, & BASEMASK fields */

#define PRIMASK_PM        0x00000001
#define FAULTMASK_FM      0x00000001
#define MASK_BASEPRI      0x000000FF

/* Bits in EXC_RETURN */

#define EXC_RTN_BASE          0xFFFFFFF1
#define EXC_RTN_MODE_THREAD   0x00000008
#define EXC_RTN_MODE_HANDLER  0x00000000
#define EXC_RTN_STACK_PROCESS 0x00000004
#define EXC_RTN_STACK_MAIN    0x00000000

#define MASK_EXC_RTN_MODE     0x00000008
#define MASK_EXC_RTN_STACK    0x00000004


/* 
 * System Control Block Registers
 */


/* CPU ID Base Register */

#define CORTEXM_CPUID_BASE_REGISTER     (0xE000ED00)

/* Interrupt Controller Type Register */

#define CORTEXM_ICTR		        (0xE000E004)

#define CORTEXM_ICTR_INTNUM_MASK        (0xF)	/* # of interrupt lines field */
#define CORTEXM_ICTR_INTNUM_MAX         (0xF)	/* # of interrupt lines field max */

/* Auxiliary Control Register - usage is implementation-defined/core-specific */

#define CORTEXM_ACTLR		        (0xE000E008)

/* Interrupt Controller State Register */

#define CORTEXM_ICSR                    (0xE000ED04)

/* Vector Table Offset Register */

#define CORTEXM_VTOR		        (0xE000ED08)

#define CORTEXM_VTOR_MASK	        (0xFFFFFF80)  /* reserved bits 6:0  */

/* 
 * Application Interrupt and Reset Control Register
 * 
 * Note that the proper access key must be included in a write to this
 * regsiter or the write is ignored.
 */

#define CORTEXM_AIRCR		        (0xE000ED0C)

#define CORTEXM_AIRCR_VECTKEY           0x05FA0000  /* Access Key for writes */
#define CORTEXM_AIRCR_VECTKEY_MASK      0xFFFF0000  /* (0xFA05 is the read value) */

#define CORTEXM_AIRCR_PRIGROUP_SHIFT     8         /* Priority Group */
#define CORTEXM_AIRCR_PRIGROUP_MASK     (0x7 << CORTEXM_AIRCR_PRIGROUP_SHIFT)

/* System Control and Register */

#define CORTEXM_SCR		        (0xE000ED10)

/* Configuration and Control Register */

#define CORTEXM_CCR		        (0xE000ED14)

#define CORTEXM_CCR_DIV0TRP	        (0x00000010)  /* divide by zero trap enable */
#define CORTEXM_CCR_STKALIGN	        (0x00000200)  /* 8-byte stacking align enable */

/* 
 * System Handler Priority Level Registers
 * (aka System Exception Priority Level Registers)
 */

#define CORTEXM_SHPR1		        (0xE000ED18)  /* Pri lvl for Exceptions 4-7 */
#define CORTEXM_SHPR2		        (0xE000ED1C)  /* Pri lvl for Exceptions 8-11 */
#define CORTEXM_SHPR3		        (0xE000ED20)  /* Pri lvl for Exceptions 12-15 */

/*
 * Note: SHPR actually starts with PRI_4.  There is no such thing as PRI_0 but
 * this makes the address calculation easier.
 */

#define CORTEXM_SHPR_PRI_0              (0xE000ED14)
#define CORTEXM_SHPR_PRI_15             (0xE000ED23)

#define CORTEXM_SHPR_PENDSV  (CORTEXM_SHPR_PRI_14)
#define CORTEXM_SHPR_SYSTICK (CORTEXM_SHPR_PRI_15)

/* system priority register address, calculated by exception # (= offset) */

#define CORTEXM_SHPR_PRI_BYTE(n) (CORTEXM_SHPR_PRI_0 + (n))

/* System Handler Control and State Register */

#define CORTEXM_SHCSR		        (0xE000ED24)

#define CORTEXM_SHCSR_USGFLT_EN	        (0x00040000)  /* Usage Fault Enable bit */
#define CORTEXM_SHCSR_BUSFLT_EN	        (0x00020000)  /* Bus Fault Enable bit */
#define CORTEXM_SHCSR_MEMFLT_EN         (0x00010000)  /* Memory Mgt Fault Enable bit */

#define CORTEXM_SHCSR_SVC_PEND		(0x00008000)  /* SVCall Pending bit */
#define CORTEXM_SHCSR_BUSFLT_PEND	(0x00004000)  /* Bus Fault Pend bit */
#define CORTEXM_SHCSR_MEMFLT_PEND	(0x00002000)  /* Memory Mgt Pend bit */
#define CORTEXM_SHCSR_USGFLT_PEND	(0x00001000)  /* Usage Fault Pend bit */

#define CORTEXM_SHCSR_SYSTCK_ACT	(0x00000800)  /* SysTick Active bit */
#define CORTEXM_SHCSR_PENDSV_ACT	(0x00000400)  /* PendSV Active bit */
#define CORTEXM_SHCSR_DBGMON_ACT	(0x00000100)  /* Debug Monitor Active */
#define CORTEXM_SHCSR_SVC_ACT		(0x00000080)  /* SVCall Active */
#define CORTEXM_SHCSR_USGFLT_ACT	(0x00000008)  /* Usage Fault Active */
#define CORTEXM_SHCSR_BUSFLT_ACT	(0x00000002)  /* Usage Fault Active */
#define CORTEXM_SHCSR_MEMFLT_ACT	(0x00000001)  /* Usage Fault Active */

/* Debug Exception and Monitor Control Register */

#define CORTEXM_DEMCR                   (0xE000EDFC)
#define CORTEXM_DEMCR_MON_STEP          (0x00040000)
#define CORTEXM_DEMCR_MON_PEND          (0x00020000)
#define CORTEXM_DEMCR_MON_EN            (0x00010000)

/* ROM table for debug */

#define CORTEXM_ROM_TABLE               (0xE00FF000)
#define CORTEXM_ROM_TABLE_FPB_OFFSET    (0x00000008)
#define CORTEXM_FPB_VALID               (0xFFF03003)

/* FlashPatch Control Register */

#define CORTEXM_FP_CTRL                 (0xE0002000)
#define CORTEXM_FP_CTRL_ENABLE          (3)

/* FlashPatch Comparatorregister */

#define CORTEXM_FP_COMP0                (0xE0002008)

/*
 * Configurable Fault Status Register 
 * This register includes the:
 * - 8-bit Memory Management Fault Status Register
 * - 8-bit Bus Fault Status Register; and
 * - 16-bit Usage Fault Status Register;
 */

#define CORTEXM_CFSR		        (0xE000ED28)
#define CORTEXM_BFSR_SHIFT	        (8)           /* Bus Fault Status bit shift */
#define CORTEXM_UFSR_SHIFT	        (16)          /* Usage Fault Status bit shift */

#define CORTEXM_DFSR		        (0xE000ED30)
#define CORTEXM_HALTED	                (0x1)         /* trace */
#define CORTEXM_BKPT	                (0x2)         /* FPB break point */

#define CORTEXM_MMFSR		        CORTEXM_CFSR  /* Mem Manage Fault Status byte */
#define CORTEXM_MMFSR_FARVALID          (0x80)        /* fault address valid mask */

#define CORTEXM_BFSR		        (0xE000ED29)  /* Bus Fault Status byte */
#define CORTEXM_BFSR_FARVALID           (0x80)        /* fault address valid mask */

#define CORTEXM_UFSR		        (0xE000ED2A)  /* Usage Fault Status halfword */

/* Usage Fault Status fields */

#define CORTEXM_UFSR_DIV0	        (0x00000200)  /* Divide by Zero */
#define CORTEXM_UFSR_UNALIGN	        (0x00000100)  /* Unaligned Access */
#define CORTEXM_UFSR_NOCP	        (0x00000008)  /* Coprocessor Access */
#define CORTEXM_UFSR_INVPC              (0x00000004)  /* Invalid EXC_RETURN */
#define CORTEXM_UFSR_INVSTATE	        (0x00000002)  /* Invalid State */
#define CORTEXM_UFSR_UNDEF	        (0x00000001)  /* Undefined Instruction */

/* Hard Fault Status Register */

#define CORTEXM_HFSR		        (0xE000ED2C)

#define CORTEXM_HFSR_FORCED             (0x40000000)  /* escalated configurable fault */
                                                      /* (bus/mem mgt/usage fault) */
#define CORTEXM_HFSR_CLRALL             (0xC0000002)  /* clear all Hard faults */

/* Memory Manage Fault Address Register */

#define CORTEXM_MMFAR		        (0xE000ED34)

/* Bus Fault Address Register */

#define CORTEXM_BFAR		        (0xE000ED38)

/* MPU Control Register */

#define CORTEXM_MPU_CTRL	        (0xE000ED94)

/* Software Trigger Interrupt Register */

#define CORTEXM_STIR		        (0xE000EF00)

#define INVALID_INST                    (0xFF00FF00)  /* invalid opcode */
#endif /* __INCarm_mh */
