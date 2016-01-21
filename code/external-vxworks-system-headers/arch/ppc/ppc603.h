/* ppc603.h - PowerPC 603 and PowerPC EC 603 specific header */

/*
 * Copyright (c) 1994-1996, 1998, 2001-2007,
 *               2009-2010, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01z,27mar12,cww  Added dsisr bits 1 and 4
01y,29jul10,pad  Moved extern C statement after include statements.
01x,06jul09,b_m  add DTLB miss related defines for e300.
01w,19jul07,mmi  add _U verion of HID0 bit definitions
01v,16jul07,pch  CQ86377: re-enable MSR[FP] for syscall handler if enabled in
		 caller
01u,29jun07,pch  CQ96747: add RI to _PPC_MSR_MMU_EXTRACT macro
01t,06jun06,dtr  Enable software floating point build.
01s,01jun06,pch  consolidate vector offset definitions in excPpcLib.h
01r,20apr06,pch  add snoop abstraction
01q,01mar06,pch  SPR 117925: add SPRG4-7 for applicable variants
01p,25mar05,dtr  Add support for 83xx and g2le variant.
01o,16may04,mil  Added _CPU_CACHE_ALIGN_SHIFT.
01n,12feb04,jtp  Add _WRS_MMU_CLASS_* macro
01m,05dec03,jtp  Add _WRS_TLB_MISS_CLASS_HW, _PPC_MSR_MMU_EXTRACT
01l,13mar03,pch  Add PPC32 support
01k,13jun02,jtp  identify class of MMU support (SPR #78396)
01j,12dec01,kab  add immr reg
01i,02may01,dat  65984, Portable C Code, added HID1
01h,14oct98,elg  added hardware breakpoints for PPC603 and PPC604
01g,19aug98,tpr added PowerPC EC 603 support.
01f,11nov96,tam added/modified HID0 macros.
01e,08oct96,tam added MSR and HID0 bit definition macros.
01d,17jun96,tpr added PowerPC 603 specific macros.
01c,21feb96,tpr added new macros.
01b,05oct95,kvk filled the dummy defines with proper values.
01a,17mar94,yao written.
*/

#ifndef __INCppc603h
#define __INCppc603h

#ifdef __cplusplus
extern "C" {
#endif

/*
 * If compiling for a variant, the preprocessor symbol CPU_VARIANT will be
 * defined as the directory suffix, e.g. _83xx for the MPC83xx processors
 * (whose objects go in target/lib/ppc/PPC603/common_83xx).
 *
 * We really want something like #if ("CPU_VARIANT" == "_83xx")
 * which ANSI C does not allow.  However, it does allow the expansion
 * of CPU_VARIANT to be re-expanded according to another #define.
 */
#ifdef  CPU_VARIANT

#define _83xx  8349
#define _g2le  8270

#if (CPU_VARIANT == _83xx)
#define PPC_83xx     1
#endif  /* CPU_VARIANT == _83xx */
#undef  _83xx

#if (CPU_VARIANT == _g2le)
#define PPC_g2le     1
#endif  /* CPU_VARIANT == _g2le */
#undef  _g2le

#endif  /* CPU_VARIANT */


#define _PPC_MSR_TGPR	0x00020000	/* temporary gpr remapping */

/* MMU supports software TLB miss handler */
#define _WRS_TLB_MISS_CLASS_SW	1
#undef  _WRS_TLB_MISS_CLASS_HW

/* MMU uses SR registers to establish contexts */
#undef	_WRS_MMU_CLASS_PID_REG
#define	_WRS_MMU_CLASS_SR_REGS	1
#undef	_WRS_MMU_CLASS_NONE

/*
 * MMU supports the M attribute bit, allowing the coherency-required property
 * to be configured on a per-page basis.  Therefore, even when snooping is
 * enabled, cacheDmaMalloc needs to call arch support to set the M bit.
 */
#define	_WRS_SNOOP_NEEDS_DMA_MALLOC_SUPPORT

#define	TBLR	268	/* lower time base register (read only) */
#define	TBUR	269	/* upper time base register (read only) */
#define	TBLW	TBL	/* lower time base register (write only) */
#define	TBUW	TBU	/* upper time base register (write only) */

#define IMMR    638     /* Internal mem map reg - from 82xx slave SIU */

/* software table search registers */

#define	DMISS	976	/* data tlb miss address register */
#define	DCMP	977	/* data tlb miss compare register */
#define	HASH1	978	/* PTEG1 address register */
#define	HASH2	979	/* PTEG2 address register */
#define	IMISS	980	/* instruction tlb miss address register */
#define	ICMP	981	/* instruction tlb mis compare register */
#define	RPA	982	/* real page address register */

#define	HID0	1008	/* hardware implementation register 0 */
#define	HID1	1009	/* hardware implementation register 1 */
#define	IABR	1010	/* instruction address breakpoint register */

#ifdef __cplusplus
}
#endif

#if (defined (PPC_83xx) || defined (PPC_g2le))
/* These variants provide SPRG4-7 */
#include <arch/ppc/sprg4_7.h>
#define IABR2   1018
#define IBCR    309
#define DABR    1013
#define DABR2   317
#define DBCR    310
#define HID2    1011
#define _PPC_HID2_HIGH_BAT_EN_U 0x0004          /* High Bat enable  */
#endif	/* PPC_83xx || PPC_g2le */

#ifdef __cplusplus
extern "C" {
#endif

#define	_CPU_CACHE_ALIGN_SHIFT	5	/* cache line size = 32 */
#undef	_CPU_CACHE_ALIGN_SIZE
#define	_CPU_CACHE_ALIGN_SIZE	32      /* cannot use (1<<5) because compiler
					 * directive __attribute__ cant hdl */

/* spr976 - DMISS data tlb miss address register 
 * spr977 - DCMP data tlb miss compare register 
 * spr978 - HASH1 PTEG1 address register
 * spr980 - HASH2 PTEG2 address register
 * IMISS  - instruction tlb miss address register
 * ICMP   - instruction TLB mis compare register
 * RPA    - real page address register
 * HID0   - hardware implemntation register
 * HID2   - instruction address breakpoint register
 */

#define	_PPC_HID0_EMCP	0x80000000	/* enable machine check pin */
#define	_PPC_HID0_EBA	0x20000000	/* enable bus adress parity checking */
#define	_PPC_HID0_EBD	0x10000000	/* enable bus data parity checking */
#define	_PPC_HID0_SBCLK	0x08000000	/* select bus clck for test clck pin */
#define	_PPC_HID0_EICE	0x04000000	/* enable ICE outputs */
#define	_PPC_HID0_ECLK	0x02000000	/* enable external test clock pin */
#define	_PPC_HID0_PAR	0x01000000	/* disable precharge of ARTRY */

/* 
 * _PPC_HID0_XX_U definitions are used with in assembly to minimize the number
 * instructions used for setting a bit mask in a general purpose register
 */

#define	_PPC_HID0_DOZE_U    0x0080	/* DOZE power management mode */
#define	_PPC_HID0_NAP_U	    0x0040	/* NAP power management mode */
#define	_PPC_HID0_SLEEP_U   0x0020	/* SLEEP power management mode */
#define	_PPC_HID0_DPM_U	    0x0010	/* enable dynamic power management */
#define	_PPC_HID0_DOZE	0x00800000	/* DOZE power management mode */
#define	_PPC_HID0_NAP	0x00400000	/* NAP power management mode */
#define	_PPC_HID0_SLEEP	0x00200000	/* SLEEP power management mode */
#define	_PPC_HID0_DPM	0x00100000	/* enable dynamic power management */
#define	_PPC_HID0_RISEG	0x00080000	/* reserved for test */
#define	_PPC_HID0_NHR	0x00010000	/* reserved */
#define _PPC_HID0_ICE   0x00008000	/* inst cache enable */
#define _PPC_HID0_DCE   0x00004000	/* data cache enable */
#define _PPC_HID0_ILOCK 0x00002000	/* inst cache lock */
#define _PPC_HID0_DLOCK 0x00001000	/* data cache lock */
#define _PPC_HID0_ICFI  0x00000800	/* inst cache flash invalidate */
#define _PPC_HID0_DCFI  0x00000400	/* data cache flash invalidate */
#define _PPC_HID0_SIED  0x00000080	/* serial instr exec disable */
#define _PPC_HID0_BHTE  0x00000004	/* branch history table enable */

/* HID0 bit definitions */

#define _PPC_HID0_BIT_ICE       16	/* HID0 ICE bit for 603 */
#define _PPC_HID0_BIT_DCE       17	/* HID0 DCE bit for 603 */
#define _PPC_HID0_BIT_ILOCK     18	/* HID0 ILOCK bit for 603 */
#define _PPC_HID0_BIT_DLOCK     19	/* HID0 DLOCK bit for 603 */
#define _PPC_HID0_BIT_ICFI      20	/* HID0 ICFI bit for 603 */
#define _PPC_HID0_BIT_DCFI      21	/* HID0 DCFI bit for 603 */
#define _PPC_HID0_BIT_SIED      24	/* HID0 SIED bit for 603 */
#define _PPC_HID0_BIT_BHTE      29	/* HID0 BHTE bit for 603 */

/* MSR bit definitions */

#define _PPC_MSR_BIT_POW 	13	/* MSR Power Management bit - POW */
#define _PPC_MSR_BIT_TGPR 	14	/* MSR Temporary GPR remapping - TGPR */
#define _PPC_MSR_BIT_ILE 	15	/* MSR Excep little endian bit - ILE */
#define _PPC_MSR_BIT_FP  	18	/* MSR Floating Ponit Aval. bit - FP */
#define _PPC_MSR_BIT_FE0 	20  	/* MSR FP exception mode 0 bit - FE0 */
#define _PPC_MSR_BIT_SE  	21  	/* MSR Single Step Trace bit - SE */
#define _PPC_MSR_BIT_BE  	22  	/* MSR Branch Trace Enable bit - BE */
#define _PPC_MSR_BIT_FE1 	23  	/* MSR FP exception mode 1 bit - FE1 */
#define _PPC_MSR_BIT_IP  	25	/* MSR Exception Prefix bit - EP */
#define _PPC_MSR_BIT_IR  	26	/* MSR Inst Translation bit - IR */
#define _PPC_MSR_BIT_DR  	27	/* MSR Data Translation bit - DR */
#define _PPC_MSR_BIT_RI  	30	/* MSR Exception Recoverable bit - RI */

/* PowerPC EC 603 does not have floating point unit */

#if	(CPU == PPCEC603)
#undef  _PPC_MSR_FP                     /* hardware floating point unsupported*/
#undef	_PPC_MSR_BIT_FP  		/* MSR Floating Ponit Aval. bit - FP */
#undef	_PPC_MSR_BIT_FE0 	  	/* MSR FP exception mode 0 bit - FE0 */
#undef	_PPC_MSR_BIT_FE1 	  	/* MSR FP exception mode 1 bit - FE1 */
#endif	/* (CPU == PPCEC603) */

#ifndef _WRS_HARDWARE_FP
#undef  _PPC_MSR_FP             /* floating point unsupported */
#undef  _PPC_MSR_FE1            /* floating point not supported */
#undef  _PPC_MSR_FE0            /* floating point not supported */
#endif /* _WRS_HARDWARE_FP */

/* MSR MMU/RI Bit extraction */

#define _PPC_MSR_MMU_RI_EXTRACT(src, dst) \
	li	dst, _PPC_MSR_IR | _PPC_MSR_DR | _PPC_MSR_RI ; \
	and	dst, dst, src

#ifndef	_PPC_MSR_FP

/* No FP, so _PPC_MSR_MMU_RI_FP_EXTRACT is the same */

#define	_PPC_MSR_MMU_RI_FP_EXTRACT	_PPC_MSR_MMU_RI_EXTRACT

#else	/* _PPC_MSR_FP */

#define _PPC_MSR_MMU_RI_FP_EXTRACT(src, dst) \
	li	dst, _PPC_MSR_IR | _PPC_MSR_DR | _PPC_MSR_RI | _PPC_MSR_FP ; \
	and	dst, dst, src

#endif	/* _PPC_MSR_FP */

/* IABR bit definitions */

/* set and get address in IABR */

#define _PPC_IABR_ADD(x)	((x) & 0xFFFFFFFC)

#define _PPC_IABR_BE		0x00000002	/* breakpoint enabled */

#if (defined (PPC_83xx) || defined (PPC_g2le))

/* DABR bits definition */

/* set and get address in DABR */

#define _PPC_DABR_DAB(x)	((x) & 0xFFFFFFF8)

#define _PPC_DABR_BT		0x00000004	/* breakpoint translation */
#define	_PPC_DABR_DW		0x00000002	/* data write enable */
#define _PPC_DABR_DR		0x00000001	/* data read enable */

/* mask for read and write operations */

#define _PPC_DABR_D_MSK		(_PPC_DABR_DW | _PPC_DABR_DR)

#endif /* (defined (PPC_83xx) || defined (PPC_g2le))*/

/* DSISR bits definition */

#define _PPC_DSISR_TRANS	0x40000000	/* translation no found */
#define _PPC_DSISR_ACCESS	0x08000000	/* access not permitted */
#define _PPC_DSISR_BRK		0x00400000	/* DABR match occurs */

#ifdef PPC_83xx

#define _PPC_SRR1_LRU_WAY	14
#define _PPC_MMU_WAY_SIZE_SHIFT	5

#endif /* PPC_83xx */

#ifdef __cplusplus
}
#endif

#endif /* __INCppc603h */
