/* ppc604.h - PowerPC 604 specific header */

/*
 * Copyright (c) 1996, 1998, 2001-2004, 2006-2007, 2010,
 *               2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01f,21nov12,ylu  added load/store control register LDSTCR definition macro.
                 (WIND00382987)
02e,26mar12,cww  Added dsisr bits 1 and 4
02d,29apr10,swu  fix PIR register write error. (WIND00208699)
02c,22apr10,rgo  CQID:209335 - PIR is not available for mv5100 w/ mpc750
02b,19jul07,mmi  add bit definitions and ICTC register for ppc745x, and _U
		 versions of HID0 bit definitions
02a,16jul07,pch  CQ86377: re-enable MSR[FP] for syscall handler if enabled in
		 caller
01z,29jun07,pch  CQ96747: add RI to _PPC_MSR_MMU_EXTRACT macro
01y,12jan07,pch  add HID0[TBEN] for MPC745x, and SVR for MPC8641
01x,21nov06,pch  MPC745x updates to MSSCR0 definitions
01w,29sep06,lei  added INT_UNMASK
01v,01jun06,pch  consolidate vector offset definitions in excPpcLib.h
01u,08mar06,pch  SPR 118651: add symbolic definitions for PVR values
		 add snoop abstraction
01t,01mar06,pch  SPR 117925: add mention of SPRG4-7
01s,26jul04,pch  SPR 99846: Add support for _745x variant
01r,16may04,mil  Added _CPU_CACHE_ALIGN_SHIFT.
01q,12feb04,jtp  Add _WRS_MMU_CLASS_* macro
01p,05dec03,jtp  Add _WRS_TLB_MISS_CLASS_HW, _PPC_MSR_MMU_EXTRACT
01o,13mar03,pch  Add PPC32 support
01n,12sep02,pch  SPR 80642: add MSSCR0 for MPC7400 and MPC7410 L1 dCache flush
01m,13jun02,jtp  identify class of MMU support (SPR #78396)
01l,23may02,pcs  Implemented code review changes for Extra BAT support.
01k,08may02,mil  Relocated _EXC_OFF_PERF to avoid corruption by the extended
		 _EXC_ALTIVEC_UNAVAILABLE vector (SPR #76916).
		 Added _EXC_OFF_THERMAL for PPC604 (SPR #77552).
01j,29apr02,pcs  Add defined for EXTRA BAT support.
01i,12dec01,kab  add immr reg
01h,02may01,dat  65984, Portable C Code, added HID1
01g,30mar01,pcs  ADDED _PPC_MSR_VEC if _WRS_ALTIVEC_SUPPORT is defined.
01f,28mar01,dtr  Adding define _WRS_ALTIVEC_SUPPORT.
01e,09nov98,ms   fixed last checkin - removed extra __cplusplus bracket.
01d,14oct98,elg  added hardware breakpoints for PPC603 and PPC604
01c,08oct96,tam  added MSR and HID0 bit definition macros.
01b,09apr96,tpr  added PowerPC 604 specific macros.
01a,14feb96,tpr  written.
*/

#ifndef __INCppc604h
#define __INCppc604h

#ifdef __cplusplus
extern "C" {
#endif

/*
 * If compiling for a variant, the preprocessor symbol CPU_VARIANT will be
 * defined as the directory suffix, e.g. _745x for the MPC745x processors
 * (whose objects go in target/lib/ppc/PPC604/common_745x).
 *
 * We really want something like #if ("CPU_VARIANT" == "_745x")
 * which ANSI C does not allow.  However, it does allow the expansion
 * of CPU_VARIANT to be re-expanded according to another #define.
 */
#ifdef  CPU_VARIANT
#define _745x  7450
#if (CPU_VARIANT == _745x)
#define PPC_745x     1
#endif  /* CPU_VARIANT == _745x */
#undef  _745x
#endif  /* CPU_VARIANT */

#if (defined(PPC_745x))
/*
 * Not including arch/ppc/sprg4_7.h here, because SPRG4-7 exist only in
 * 7445/7455 and later (PVR >= 0x8001xxxx) and PPC_745x also supports
 * the 7440, 7441, and 7450 (PVR = 0x8000xxxx).  BSP's or kernel-mode
 * applications which do not need to support the earlier processors may
 * #include <arch/ppc/sprg4_7.h> to pick up the definitions of SPRG4-7.
 */
#endif	/* PPC_745x */

/* MMU supports TLB miss with hardware (not SRR0/SRR1) */
#undef	_WRS_TLB_MISS_CLASS_SW
#define	_WRS_TLB_MISS_CLASS_HW	1

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

/*
 * This is essentially a compiler switch to remove/add altivec support
 * in the target src. The BSP code is controlled using INCLUDE_ALTIVEC
 * in config.h
 */
#define _WRS_ALTIVEC_SUPPORT 1

/* Special Purpose Register PowerPC604 specific */

#define IMMR    638     /* Internal mem map reg - from 82xx slave SIU */

#undef	ASR		/* 64 bit implementation only */

#define MMCR0	952	/* Monitor Mode Control Register 0 */
#define PMC1	953	/* Performance Monitor Counter Register 1 */
#define PMC2 	954	/* Performance Monitor Counter Register 2 */
#define SIA	955	/* Sampled Instruction Address Register */
#define SDA	959	/* Sampled Data Address Register */
#define	HID0	1008	/* hardware implementation register 0 */
#define	HID1	1009	/* hardware implementation register 1 */
#define HID2    1011    /* hardware implementation register 2 (MPC755)*/
#define IABR	1010	/* Instruction Address Breakpoint Register */
#define DABR	1013	/* Data Address Breakpoint Register */
#define LDSTCR  1016    /* load/store control register */

#ifdef	PPC_745x	
#define PIR	1023	/* Processor Identification Register */
#endif

#ifdef	PPC_745x	
#define _WRS_ARCH_HAS_DPM
#define ICTC	1019	/* Instruction cache throttling */
#endif

#ifdef	_WRS_ALTIVEC_SUPPORT
/* MSSCR0 exists only in MPC74xx/8641 */
#define	MSSCR0	1014	/* Memory Subsystem Control Register */

# ifdef	PPC_745x
/*
 * The following MSSCR0 fields exist in MPC744x, MPC745x, and MPC8641
 * (PVR=800xxxxx).  We use the _PPC_MSSCR0_ID bit to recognize CPU 0
 * in the bootrom, and define the other fields here for completeness.
 */
#define	_PPC_MSSCR0_DTQ_U	0x1c00	/* DTQ size                          */
#define	_PPC_MSSCR0_EIDIS_U	0x0100	/* disable external MPX intervention */
#define	_PPC_MSSCR0_L3TCEXT_U	0x0020	/* L3 turnaround clock count (7457)  */
#define	_PPC_MSSCR0_ABD_U	0x0010	/* Address Bus Driven mode           */
#define	_PPC_MSSCR0_L3TCEN_U	0x0008	/* L3 turnaround clock enable (7457) */
#define	_PPC_MSSCR0_L3TC_U	0x0006	/* L3 turnaround clock count (7457)  */
#define	_PPC_MSSCR0_BMODE	0xc000	/* Bus Mode                          */
#define	_PPC_MSSCR0_ID		0x0020	/* Set if SMP CPU ID != 0            */
#define	_PPC_MSSCR0_BIT_ID	26
#define	_PPC_MSSCR0_L2PFE	0x0003	/* # of L2 prefetch engines enabled  */
# else	/* PPC_745x */
/*
 * The following MSSCR0 fields exist only in MPC7400 (PVR=000Cxxxx)
 * and MPC7410 (PVR=800Cxxxx).  We use the DL1HWF bit in cacheALib.s,
 * and define the other fields here for completeness.  All are in the
 * MS half of the register.
 */
#define	_PPC_MSSCR0_SHDEN_U	0x8000	/* Shared-state (MESI) enable */
#define	_PPC_MSSCR0_SHDPEN3_U	0x4000	/* MEI mode SHD0/SHD1 signal enable */
#define	_PPC_MSSCR0_L1_INTVEN_U	0x3800	/* L1 data cache HIT intervention */
#define	_PPC_MSSCR0_L2_INTVEN_U	0x0700	/* L2 data cache HIT intervention */
#define	_PPC_MSSCR0_DL1HWF_U	0x0080	/* L1 data cache hardware flush */
#define	_PPC_MSSCR0_BIT_DL1HWF	8
#define	_PPC_MSSCR0_EMODE_U	0x0020	/* MPX bus mode (read-only) */
#define	_PPC_MSSCR0_ABD_U	0x0010	/* Address bus driven (read-only) */
# endif	/* PPC_745x */
#endif	/* _WRS_ALTIVEC_SUPPORT */

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

#define	_PPC_HID0_EMCP		0x80000000	/* Enable machine check pin */
#define _PPC_HID0_ECPC		0x40000000	/* Enable cache parity check */
#define	_PPC_HID0_EBA		0x20000000	/* Enable address bus parity */
#define	_PPC_HID0_EBD		0x10000000	/* Enable data bus parity */
# ifdef	PPC_745x
#define	_PPC_HID0_TBEN		0x04000000	/* Enable timebase & decr */
#define	_PPC_HID0_NAP_U		0x0040		/* NAP power management mode */
#define	_PPC_HID0_SLEEP_U	0x0020		/* SLEEP power management mode */
#define	_PPC_HID0_DPM_U		0x0010		/* enable dynamic power management */
#define	_PPC_HID0_NAP		0x00400000	/* NAP power management mode */
#define	_PPC_HID0_SLEEP		0x00200000	/* SLEEP power management mode */
#define	_PPC_HID0_DPM		0x00100000	/* enable dynamic power management */
# endif	/* PPC_745x */
#define	_PPC_HID0_PAR		0x01000000	 
#define	_PPC_HID0_NHR		0x00010000	/* Not hard reset */
#define _PPC_HID0_ICE   	0x00008000	/* inst cache enable */
#define _PPC_HID0_DCE		0x00004000	/* data cache enable */
#define _PPC_HID0_ILOCK 	0x00002000	/* inst cache lock */
#define _PPC_HID0_DLOCK		0x00001000	/* data cache lock */
#define _PPC_HID0_ICFI		0x00000800	/* inst cache flash invalidate*/
#define _PPC_HID0_DCFI		0x00000400	/* data cache flash invalidate*/
#define _PPC_HID0_SIED		0x00000080	/* serial instr exec disable */
#define _PPC_HID0_DCFA		0x00000040	/* dCache flush assist on 7xx */
#define _PPC_HID0_BHTE		0x00000004	/* branch history table enable*/

#define _PPC_HID0_XBSEN         0x0100          /* Extended Block Size enable */
# ifdef	PPC_745x
#define	_PPC_HID0_TBEN_U	0x0400		/* Enable timebase & decr */
#define	_PPC_HID1_EMCP		0x80000000	/* Enable machine check pin */
#define	_PPC_HID1_EBA		0x20000000	/* Enable address bus parity */
#define	_PPC_HID1_EBD		0x10000000	/* Enable data bus parity */
#define	_PPC_HID1_DSF4		0x00400000	/* Dynamic frequency scaling */
#define	_PPC_HID1_DSF2		0x00200000	/* Dynamic frequency scaling */

#define	_PPC_HID1_PC5		0x00040000	/* PLL configuration bit 5 */
#define	_PPC_HID1_PC0		0x00020000	/* PLL configuration bit 0 */
#define	_PPC_HID1_PC1		0x00008000	/* PLL configuration bit 1 */
#define	_PPC_HID1_PC2		0x00004000	/* PLL configuration bit 2 */
#define	_PPC_HID1_PC3		0x00002000	/* PLL configuration bit 3 */
#define	_PPC_HID1_PC4		0x00001000	/* PLL configuration bit 4 */
#define	_PPC_HID1_SYNCBE	0x00000800	/* addr. broadcast for sync, eieio */
#define	_PPC_HID1_ABE		0x00000400	/* addr. broadcast enable  */
#define _PPC_ICTC_FI_MASK	0x000001FE	/* Instruction forwarding interval */
#define _PPC_ICTC_FI_45		0x0000005A	/* fetch instr. every 45 cycles */
#define _PPC_ICTC_FI_85		0x000000AA	/* fetch instr. every 85 cycles */
#define _PPC_ICTC_FI_130	0x00000104	/* fetch instr. every 130 cycles */
#define _PPC_ICTC_FI_175	0x0000015E	/* fetch instr. every 175 cycles */
#define _PPC_ICTC_FI_210	0x000001A4	/* fetch instr. every 210 cycles */
#define _PPC_ICTC_FI_255	0x000001FE	/* fetch instr. every 255 cycles */
#define _PPC_ICTC_FI_EN		0x00000001	/* Instruction cache throttling enable */
# endif	/* PPC_745x */

#define _PPC_HID0_HIGH_BAT_EN_U 0x0080          /* High Bat enable on MPC7455 */
#define _PPC_HID2_HIGH_BAT_EN_U 0x0004          /* High Bat enable on MPC755 */

#define	SVR			286		/* "system" version register */
#define	_PPC_SVR_VER_MASK	0xffffff00	/* "version" field */
#define	_PPC_SVR_REV_MASK	0x000000ff	/* "revision" field */
#define	_PPC_SVR_MPC8641	0x80900000	/* single-core 8641 */
#define	_PPC_SVR_MPC8641D	0x80910000	/* dual-core 8641D */

#define	PVR			287		/* processor version register */

/*
 * Values of upper half of PVR, used in cache code
 * to discern cache size and select flush algorithm
 */

#define	_PPC_PVR_PPC604_U	0x0004
#define	_PPC_PVR_PPC750_U	0x0008
#define	_PPC_PVR_PPC604E_U	0x0009
#define	_PPC_PVR_PPC604R_U	0x000a
#define	_PPC_PVR_MPC7400_U	0x000c
#define	_PPC_PVR_MPC755_U	0x3200
#define	_PPC_PVR_MPC745_U	0x3202
#define	_PPC_PVR_PPC750FX_0_U	0x7000		/* lowest PPC750FX PVR value */
#define	_PPC_PVR_PPC750FX_f_U	0x700f		/* highest PPC750FX PVR value */
#define	_PPC_PVR_MPC7450_U	0x8000		/* also 7440, 7441 */
#define	_PPC_PVR_MPC7455_U	0x8001		/* also 7445 */
#define	_PPC_PVR_MPC7457_U	0x8002		/* also 7447 */
#define	_PPC_PVR_MPC7447A_U	0x8003
#define	_PPC_PVR_MPC7448_U	0x8004
#define	_PPC_PVR_MPC7410_U	0x800c

/* HID0 bit definitions */

#define _PPC_HID0_BIT_ICE	16		/* HID0 ICE bit for 604 */
#define _PPC_HID0_BIT_DCE	17		/* HID0 DCE bit for 604 */
#define _PPC_HID0_BIT_ILOCK	18		/* HID0 ILOCK bit for 604 */
#define _PPC_HID0_BIT_DLOCK	19		/* HID0 DLOCK bit for 604 */
#define _PPC_HID0_BIT_ICFI	20		/* HID0 ICFI bit for 604 */
#define _PPC_HID0_BIT_DCFI	21		/* HID0 DCFI bit for 604 */
#define _PPC_HID0_BIT_SIED	24		/* HID0 SIED bit for 604 */
#define _PPC_HID0_BIT_DCFA	25		/* HID0 DCFA bit for 7xx/74xx */
#define _PPC_HID0_BIT_BHTE	29		/* HID0 BHTE bit for 604 */

#define _PPC_HID0_BIT_XBSEN	23		/* HID0 XBSEN bit for 7455 */
#define _PPC_HID0_BIT_HIGH_BAT_EN 8       /* HID0 HIGH_BAT_EN bit for 7455 */
#define _PPC_HID2_BIT_HIGH_BAT_EN 13      /* HID2 HIGH_BAT_EN bit for 755 */

/* MSR bit definitions */

#define _PPC_MSR_BIT_POW 	13	/* MSR Power Management bit - POW */
#define _PPC_MSR_BIT_ILE 	15	/* MSR Excep little endian bit - ILE */
#define _PPC_MSR_BIT_FP  	18	/* MSR Floating Ponit Aval. bit - FP */
#define _PPC_MSR_BIT_FE0 	20	/* MSR FP exception mode 0 bit - FE0 */
#define _PPC_MSR_BIT_SE  	21	/* MSR Single Step Trace bit - SE */
#define _PPC_MSR_BIT_BE  	22	/* MSR Branch Trace Enable bit - BE */
#define _PPC_MSR_BIT_FE1 	23	/* MSR FP exception mode 1 bit - FE1 */
#define _PPC_MSR_BIT_IP  	25	/* MSR Exception Prefix bit - EP */
#define _PPC_MSR_BIT_IR  	26	/* MSR Inst Translation bit - IR */
#define _PPC_MSR_BIT_DR  	27	/* MSR Data Translation bit - DR */
#define _PPC_MSR_BIT_PM  	29	/* MSR Performance Monitor bit - MR */
#define _PPC_MSR_BIT_RI  	30	/* MSR Exception Recoverable bit - RI */

#ifdef _WRS_ALTIVEC_SUPPORT
#define _PPC_MSR_VEC        0x0200      /* Bit 6 of MSR                      */
#define _PPC_MSR_BIT_VEC  	06	/* MSR Altivec Available bit - VEC */
#endif	/* _WRS_ALTIVEC_SUPPORT */

/* MSR MMU/RI Bit extraction */

#define _PPC_MSR_MMU_RI_EXTRACT(src, dst) \
	li	dst, _PPC_MSR_IR | _PPC_MSR_DR | _PPC_MSR_RI ; \
	and	dst, dst, src

#define _PPC_MSR_MMU_RI_FP_EXTRACT(src, dst) \
	li	dst, _PPC_MSR_IR | _PPC_MSR_DR | _PPC_MSR_RI | _PPC_MSR_FP ; \
	and	dst, dst, src


/* IABR bit definitions */

/* set and get address in IABR */

#define _PPC_IABR_ADD(x)    	((x) & 0xFFFFFFFC)

#define _PPC_IABR_BE            0x00000002      /* breakpoint enabled */
#define	_PPC_IABR_TE		0x00000001	/* translation enabled */

/* DABR bits definition */

/* set and get address in DABR */

#define _PPC_DABR_DAB(x)	((x) & 0xFFFFFFF8)

#define _PPC_DABR_BT		0x00000004	/* breakpoint translation */
#define	_PPC_DABR_DW		0x00000002	/* data write enable */
#define _PPC_DABR_DR		0x00000001	/* data read enable */

/* mask for read and write operations */

#define _PPC_DABR_D_MSK		(_PPC_DABR_DW | _PPC_DABR_DR)

/* DSISR bits definition */

#define _PPC_DSISR_TRANS	0x40000000	/* translation not found */
#define _PPC_DSISR_ACCESS	0x08000000	/* access not permitted */
#define _PPC_DSISR_BRK		0x00400000	/* DABR match occurs */

/* set EE bit to 1 */

#undef  INT_UNMASK
#define INT_UNMASK(reg) 						 \
	mfmsr	reg				/* load msr */         ; \
	ori	reg, reg, _PPC_MSR_EE		/* set EE bit */       ; \
	mtmsr	reg				/* UNLOCK INTERRUPT */ ; \
	isync

#ifdef __cplusplus
}
#endif

#endif /* __INCppc604h */
