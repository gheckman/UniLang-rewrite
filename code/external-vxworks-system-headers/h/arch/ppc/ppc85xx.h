/* ppc85xx.h - PowerPC specific header */

/*
 * Copyright (c) 1984-2010, 2012-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
04may15,d_l  Do not use UINT8/UINT32/UCHAR. (VXW6-84224)
26feb15,wyt  exclude e6500 errata based on silicon versions (VXW6-84087)
03jan14,p_x  add _PPC_MSR_BIT_SPE macro (WIND00444989)
02x,07mar13,pcs  Add macro _PPC_MAS1_V and _PPC_MAS6_SIND
02w,26feb13,h_k  added T4_ERRATUM_CPU6198 for e6500.
                 removed unused INT_UNMASK macro.
02v,21feb13,h_k  added IVOR32 and IVOR33 for e6500. (WIND00404757)
02u,12feb13,pcs  Add macro T4_ERRATUM_CPU4801
02t,04feb13,pcs  Move typedef struct tlb1EntrySelect from mmuE500Lib.h to
                 here.
02s,17jan13,h_k  removed THREAD_OPCODE macro definition.
                 added T4_ERRATUM_CPU4792 and T4_ERRATUM_CPU4809 macros.
02r,05dec12,pcs  Decouple macro PPC_e500mc for e6500 core.
02q,04dec12,h_k  removed unused SPR631 macro.
                 added T4_ERRATUM_CPUXXXX macros
                 to create errata workaround options.
02p,23nov12,x_s  added Thread definitions for e6500.
02o,09nov12,h_k  added L2CSR1 bit definitions for e6500.
02n,23oct12,x_s  added L2C_REG_ADDR_OFFSET for e6500 to support assemble.
02m,19sep12,h_k  added Altivec support for e6500.
02l,25jul12,h_k  added L2 cache definitions for e6500.
02k,24jul12,h_k  added e6500 CPU variant support. (WIND00333229)
02k,01aug12,c_l  add SVR definition. (WIND00366668)
02j,13dec10,agf  make MCSR bit defs mut-ex between e500mc and rest of 85xx
02i,07may10,dhy  clear MCSR register  
02m,22jun10,pmr  disable P4080 rev1 errata workarounds
02l,05mar10,pmr  add MCSR and bits, and L2 cache registers, for e500mc
02k,12jan10,pmr  add LPIDR and fix MAS5/8 (e500mc) 
02j,03nov09,rab  Fix _PPC_MSR_MMU_RI_EXTRACT for sfdiab and e500mc
02i,12oct09,pmr  P4080 errata CPU6 and CPU8
02h,16jun09,pmr  e500mc 36-bit
02g,12may09,rec  add PVR_VALUE definition
02f,22sep08,pmr  remove vxWorks.h include (WIND00134296)
02e,09sep08,pch  CQ133354: e500mc does not have SPE
02d,04sep08,pmr  update e500mc for hard float
02c,14apr08,pmr  add e500mc
02b,22jan08,dtr  UPdate macros to use SPE.
02a,06nov07,dtr  Add definitions for SPEFSCR reg.
01z,26sep07,dtr  Support power mode.
01y,19jul07,mmi  add HID0 _U version bit definitions
01y,30aug07,dtr  Add PIR SPR definition.
01x,16jul07,pch  CQ86377: re-enable MSR[FP] for syscall handler if enabled in
		 caller
01w,29jun07,pch  CQ96747: rename _PPC_MSR_MMU_EXTRACT macro
01v,16may07,dtr  Remove MCSRR0 for e200.
01u,09may07,dtr  Add e200 cpu variant.
01t,06jul06,pch  add MSR bit definitions & use in INT_MASK
01s,20apr06,pch  add snoop abstraction
01r,02feb06,dtr  Allow powerdown. SPR#117436
01q,18jul05,dtr  Add _e500v2 cpu variant.
01p,23sep04,pch  resumeInVector support
01o,30jul04,mil  Added PPC85XX_ERRATA_CPU29 workaround.
01n,10may04,mil  Added _CPU_CACHE_ALIGN_SHIFT.
01m,26feb04,mil  Added _WRS_MMU_CLASS_* macros.
01l,13aug03,mil  Added MCAR.
01k,20jun03,mil  Fixed _CACHE_ALIGN_SIZE macro.
01j,12jun03,dtr  Adding CACH_ALIGN_SIZE.
01i,08apr03,dtr  Adding define for E500 Fixed point support.
01h,05feb03,dtr  Missed comment closure, fixed TBEN define and added HID1_ABE.
01g,07jan03,dtr  Adding defines for MAS0.
01f,18dec02,dtr  Adding Cache and MMU defines.
01e,08nov02,mil  Added and modified registers definitions.
01d,05nov02,pcs  Add defines required my the E500 MMU.
01c,17oct02,dtr  _WRS_SUPPORT_SPE set to 1.
01b,03oct02,dtr  Putting in more 85XX defines.
01a,17sep02,dtr  written.
*/
#ifndef __INCppc85xxh
#define __INCppc85xxh

#ifndef _ASMLANGUAGE
#include <types.h>
#endif

#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * If compiling for a variant, the preprocessor symbol CPU_VARIANT will be
 * defined as the directory suffix, e.g. _e500v2 for the MPC8548 processors
 * (whose objects go in target/lib/ppc/PPC85XX/common_e500v2).
 *
 * We really want something like #if ("CPU_VARIANT" == "_e500v2")
 * which ANSI C does not allow.  However, it does allow the expansion
 * of CPU_VARIANT to be re-expanded according to another #define.
 */
#ifdef CPU_VARIANT

#define _e200    5553
#define _e500mc  8578
#define _e500v2  8548
#define _e6500   4240
#if (CPU_VARIANT == _e200)
#define PPC_e200     1
#endif  /* CPU_VARIANT == _e200 */
#if (CPU_VARIANT == _e500mc)
#define PPC_e500mc     1
#endif  /* CPU_VARIANT == _e500mc */
#if (CPU_VARIANT == _e500v2)
#define PPC_e500v2     1
#endif  /* CPU_VARIANT == _e500v2 */
#if (CPU_VARIANT == _e6500)
#define PPC_e6500      1
#endif  /* CPU_VARIANT == _e6500 */
#undef  _e200
#undef  _e500mc
#undef  _e500v2
#undef  _e6500
#endif  /* CPU_VARIANT */


/* Erratum CPU29 for E500 exists on all Rev.2 cores.
 * mtmsr with change to IS bit may corrupt system state.
 * Workaround is to use rfi instead of mtmsr.
 */
#ifndef PPC_e200
# if (!defined(PPC_e500mc) && !defined(PPC_e6500))
#define PPC85XX_ERRATA_CPU29 1
# endif	/* !PPC_e500mc && !PPC_e6500 */
#endif	/* PPC_e200 */

/* Rev 1 silicon errata for P4080 */
#ifdef PPC_e500mc
#undef P4080_ERRATUM_CPU6
#undef P4080_ERRATUM_CPU8
#endif /* PPC_e500mc */

/* Rev 1 silicon errata for T4240 and T4160 */

#if defined(PPC_e6500) && !defined(_WRS_CONFIG_E6500_REV_2)

/*
 * Create the workaround for errata CPU A004779:
 * Misaligned bank collisions in the L1 Data Cache may cause a hang.
 *
 * Workaround: Follow all of these steps.
 * 1. Set bit 32 of SPR978 to 1.
 * 2. Set bits 33:39 of SPR978 to 0b0000011.
 * 3. Set bits 41:47 of SPR978 to 0b0000011.
 *
 * BSP needs to define FSL_ERRATA_CPU_A004779 macro to apply the workaround.
 */

#define T4_ERRATUM_CPU4779

/*
 * Create the workaround for errata CPU A004786:
 * Speculative lbarx, lharx, lwarx, ldarx are not supported on e6500 Rev1.
 *
 * Workaround:
 * Set bit 32 of SPR631 to 1.
 *
 * BSP needs to define FSL_ERRATA_CPU_A004786 macro to apply the workaround.
 */

#define T4_ERRATUM_CPU4786

/*
 * Create the workaround for errata CPU A004792:
 * Lightweight memory barriers including lightweight sync, eieio, and elemental
 * barriers may not perform the intended synchronization, resulting in
 * issues.
 *
 * Workaround:
 * Set bit 49 of SPR 976 to 1.
 *
 * BSP needs to define FSL_ERRATA_CPU_A004792 macro to apply the workaround.
 */

#define T4_ERRATUM_CPU4792

/*
 * Create the workaround for errata CPU A004801:
 * Software thread synchronization is required for MMU accesses.
 * Simultaneous MMU accesses from both threads may result in a hang or corrupt 
 * MMU state.
 * The following MMU accesses are affected:
 * tlbre, tlbwe, tlbsx, tlbilx, mt mmucsr0 when writing the flash invalidate 
 * bits
 *
 * Impact: Two threads simultaneously performing MMU accesses without 
 * synchronization may result in a hang or corrupt MMU state.
 *
 * Workaround: Protect tlbre, tlbwe, tlbsx, tlbilx and mt mmucsr0 instructions 
 * within a mutual exclusion block 
 */

#define T4_ERRATUM_CPU4801

/*
 * Create the workaround for errata CPU A004806:
 * Load data returned from the system may be observed in a different order by
 * threads on the same core.
 *
 * Workaround:
 * Set bit 34 of SPR631 to 1.
 *
 * BSP needs to define FSL_ERRATA_CPU_A004806 macro to apply the workaround.
 */

#define T4_ERRATUM_CPU4806

/*
 * Create the workaround for errata CPU A004809:
 * Instruction Line Fill Buffer entries that are canceled because of a change
 * in flow can be overwritten with a new demand fetch. If instruction fetch is
 * aliasing one EA to multiple RAs, the new fetch may incorrectly complete from
 * the old context.
 *
 * Workaround:
 * 1. Set bit 39 of SPR 976 to 1. This will disable instruction prefetch.
 * 2. Set bit 48 of SPR 976 to 1. This will prevent new fetches from
 *    overwriting a canceled nstruction Line Fill Buffer entry until
 *    the previous entry has been loaded into the Instruction Cache.
 *
 * BSP needs to define FSL_ERRATA_CPU_A004809 macro to apply the workaround.
 */

#define T4_ERRATUM_CPU4809

/*
 * Create the workaround for errata CPU A004857:
 * Shared L2 cache may drop a reload to the core when certain snoops hit on
 * a victim castout.
 *
 * Workaround:
 * Set bits 40:41 of L2 cache register offset 0xf04 to 0b01. This workaround
 * option may have a performance impact.
 *
 * BSP needs to define FSL_ERRATA_CPU_A004857 macro to apply the workaround.
 */

#define T4_ERRATUM_CPU4857

/*
 * Create the workaround for errata CPU A005553:
 * A non-stcx store from one core on a cluster to the same coherency granule
 * used as a reservation by a different core on the same cluster may not kill
 * the reservation.
 *
 * Workaround:
 * 1. Set the L2 cache register offset 0xf04 bit 54 to 1'b1 to disable CoreNet
 *    reordering from different sources.
 * 2. Set the L2 cache register offset 0xf00 bit 41 to 1'b1 to disable
 *    the cluster-level store merging.
 *
 * BSP needs to define FSL_ERRATA_CPU_A005553 macro to apply the workaround.
 */

#define T4_ERRATUM_CPU5553

/*
 * Create the workaround for errata CPU A006198:
 * Core may hang if a mtmsr[EE,CE,DE] or wrtee/wrteei is coincident with an
 * asynchronous interrupt and the mtmsr[EE,CE,DE] or wrtee/wrteei is
 * delayed by activity on the other thread
 *
 * Workaround:
 * Each instance of a mtmsr which disables any interrupt enables (i.e. EE, CE,
 * or DE transitions from 1 to 0 as a result of the mtmsr) and must be replaced
 * by a sequence which uses MCSRR0/1 and rfmci to perform the MSR manipulation.
 * Also, any wrtee or wrteei which sets MSR[EE] to 0 must be replaced with the
 * same sequence.
 */

#define T4_ERRATUM_CPU6198

#endif	/* PPC_e6500 && !_WRS_CONFIG_E6500_REV_2 */

/* Maximum cache line size for the cpu */
#if defined(PPC_e500mc) || defined(PPC_e6500)
#define	_CPU_CACHE_ALIGN_SHIFT	6	/* cache align size = 64 */
#else
#define	_CPU_CACHE_ALIGN_SHIFT	5	/* cache align size = 32 */
#endif	/* PPC_e500mc || PPC_e6500 */

#undef	_CPU_CACHE_ALIGN_SIZE

#if defined(PPC_e500mc) || defined(PPC_e6500)
#define	_CPU_CACHE_ALIGN_SIZE	64
#else
#define	_CPU_CACHE_ALIGN_SIZE	32	/* cannot use (1<<5) because compiler
					 * directive __attribute__ cant hdl */
#endif	/* PPC_e500mc || PPC_e6500 */

/* MMU supports software TLB miss handler */
#undef  _WRS_TLB_MISS_CLASS_HW
#define _WRS_TLB_MISS_CLASS_SW  1

/* MMU uses PID register to extend virtual address tag */
#undef	_WRS_MMU_CLASS_NONE
#undef	_WRS_MMU_CLASS_SR_REGS
#define _WRS_MMU_CLASS_PID_REG	1

/* MMU ASID context register name for _WRS_MMU_CLASS_PID_REG */
#define	_PPC_PID_REG		PID0

/* MMU cannot be disabled */
#define	PPC_NO_REAL_MODE

/*
 * MMU supports the M attribute bit, allowing the coherency-required property
 * to be configured on a per-page basis.  Therefore, even when snooping is
 * enabled, cacheDmaMalloc needs to call arch support to set the M bit.
 */
#define	_WRS_SNOOP_NEEDS_DMA_MALLOC_SUPPORT

#define _WRS_E500_FIXED_POINT_SUPPORT 1

#if !defined(PPC_e500mc) && !defined(PPC_e6500)
#define _WRS_SPE_SUPPORT	1
#endif /* PPC_e500mc */

#ifdef	PPC_e6500
#define _WRS_ALTIVEC_SUPPORT	1
#endif	/* PPC_e6500 */

#ifdef _WRS_SPE_SUPPORT
#undef _PPC_MSR_FP
#define _PPC_MSR_SPE_U		0x0200
#define _PPC_MSR_SPE		0x02000000
#define MSR_SPE_BIT_SHIFT	25
#define _PPC_MSR_BIT_SPE    6
#endif /* _WRS_SPE_SUPPORT */

#ifdef	_WRS_ALTIVEC_SUPPORT
#define _PPC_MSR_VEC		0x0200	/* Bit 6 of MSR */
#define _PPC_MSR_BIT_VEC	6	/* MSR Altivec Available bit - VEC */
#endif	/* _WRS_ALTIVEC_SUPPORT */

/* #define IMMR	638	* bogus hack */

/* Special Purpose Register (SPR) numbers */
#define CSRR0   58      /* Critical SRR0 */
#define CSRR1   59      /* Critical SRR1 */
#define DEAR    61      /* Data Exception Address Register */
#define ESR     62      /* Exception Syndrome Register */
#define IVPR    63      /* Interrupt Vector Prefix Register */
#define IVOR0   400     /* IVOR Critical Input */
#define IVOR1   401     /* IVOR Machine Check */
#define IVOR2   402     /* IVOR Data Storage */
#define IVOR3   403     /* IVOR Instruction Storage */
#define IVOR4   404     /* IVOR External Input */
#define IVOR5   405     /* IVOR Alignment */
#define IVOR6   406     /* IVOR Program */
#define IVOR7   407     /* IVOR Floating Point Unavailable */
#define IVOR8   408     /* IVOR System Call */
#define IVOR9   409     /* IVOR Auxiliary Processor Unavailable */
#define IVOR10  410     /* IVOR Decrementer */
#define IVOR11  411     /* IVOR Fixed Interval Timer */
#define IVOR12  412     /* IVOR Watchdog Timer */
#define IVOR13  413     /* IVOR Data TLB Error */
#define IVOR14  414     /* IVOR Instruction TLB Error */
#define IVOR15  415     /* IVOR Debug */
#ifdef _WRS_ALTIVEC_SUPPORT
#define IVOR32  528     /* IVOR AltiVec unavailable */
#define IVOR33  529     /* IVOR AltiVec assist */
#endif  /* _WRS_ALTIVEC_SUPPORT */
#ifdef _WRS_SPE_SUPPORT
#define IVOR32  528     /* IVOR SPE */
#define IVOR33  529     /* IVOR Vector FP Data */
#define IVOR34  530     /* IVOR Vector FP Round */
#endif	/* _WRS_SPE_SUPPORT */
#ifndef PPC_e200 
#define IVOR35  531     /* IVOR Performance Monitor */
#endif	/* PPC_e200 */
#if  defined(PPC_e500mc) || defined(PPC_e6500)
#define IVOR36  532     /* IVOR Processor Doorbell Interrupt */
#define IVOR37  533     /* IVOR Processor Doorbell Critical Interrupt */
#define IVOR38  534     /* IVOR Guest Processor Doorbell Interrupt */
#define IVOR39  535     /* IVOR Guest Processor Doorbell Critical Interrupt */
#define IVOR40  536     /* IVOR Ultravisor System Call Interrupt */
#define IVOR41  537     /* IVOR Ultravisor Privilege Interrupt */
#define DBSRWR  564     /* Debug Status Register Write Register */
#define DSRR0   574     /* Debug SRR0 */ 
#define DSRR1   575     /* Debug SRR1 */
#endif	/* PPC_e500mc || PPC_e6500 */
#ifndef PPC_e200 
#define MCSRR0  570     /* Machine Check SRR0 */
#define MCSRR1  571     /* Machine Check SRR1 */
#define MCAR    573     /* Machine Check Address Register */
#else	/* PPC_e200 */
#define MCSRR0  CSRR0     /* Machine Check SRR0 */
#define MCSRR1  CSRR1     /* Machine Check SRR1 */
#undef MCAR         /* Machine Check Address Register */
#endif	/* PPC_e200 */

#define MCSR    572     /* Machine Check Syndrome Register */

#ifdef PPC_e6500
/* Thread definitions */

#define E6500_THREAD_NUM            2
#define E6500_THREAD(n)             (n % E6500_THREAD_NUM)
#define E6500_THREAD_BIT(n)         (1 << E6500_THREAD(n))
#define E6500_THREAD_ALL            ((1 << E6500_THREAD_NUM) - 1)
#define E6500_THREAD_OTHERS         (E6500_THREAD_ALL & ~1)

/* SPR #s for threads */

#define _SPR_TENSR                  437
#define _SPR_TENS                   438
#define _SPR_TENC                   439
#define _SPR_TIR                    446

/* TMRN definitions */

#define _TMR_TMCFG0                 16
#define _TMR_TPRI0                  192
#define _TMR_TPRI1                  193
#define _TMR_IMSR0                  288
#define _TMR_IMSR1                  289
#define _TMR_INIA0                  320
#define _TMR_INIA1                  321

#define HID0_MCP                    0x80000000
#endif 

#if !defined(PPC_e500mc) && !defined(PPC_e6500)
/* MCSR bit definitions */                                             
#define	_PPC_MCSR_BIT_MCP	0	/* Machine check input pin */              
#define	_PPC_MCSR_BIT_ICPERR	1	/* Instruction cache parity error */   
#define	_PPC_MCSR_BIT_DCP_PERR	2	/* Data cache push parity error */   
#define	_PPC_MCSR_BIT_DCPERR	3	/* Data cache parity error */          
#define	_PPC_MCSR_BIT_GL_CI	15	/* guarded load etc, see manual. using it for clear MCSR */     
#define	_PPC_MCSR_BIT_BUS_IAERR	24	/* Bus instruction address error */
#define	_PPC_MCSR_BIT_BUS_RAERR	25	/* Bus read address error */       
#define	_PPC_MCSR_BIT_BUS_WAERR	26	/* Bus write address error */      
#define	_PPC_MCSR_BIT_BUS_IBERR	27	/* Bus instruction data bus error */
#define	_PPC_MCSR_BIT_BUS_RBERR	28	/* Bus read data bus error */      
#define	_PPC_MCSR_BIT_BUS_WBERR	29	/* Bus write bus error */          
#define	_PPC_MCSR_BIT_BUS_IPERR	30	/* Bus instruction parity error */ 
#define	_PPC_MCSR_BIT_BUS_RPERR	31	/* Bus read parity error */        

#else /* PPC_e500mc || PPC_e6500 */
/* MCSR bit definitions */                                             
#define _PPC_MCSR_BIT_MCP		0	/* mchk input signal assert */
#define _PPC_MCSR_BIT_ICPERR		1	/* i-cache/tag parity error */
#define _PPC_MCSR_BIT_DCPERR		2	/* d-cache/tag parity error */
#ifdef	PPC_e6500
#define _PPC_MCSR_BIT_TLBPERR		3	/* TLB0 array parity error */
#endif	/* PPC_e6500 */
#define _PPC_MCSR_BIT_L2MMU_MHIT	4	/* L2 MMU simultaneous hit */
#define _PPC_MCSR_BIT_NMI		11	/* nonmaskable interrupt */
#define _PPC_MCSR_BIT_MAV		12	/* MCAR valid */
#define _PPC_MCSR_BIT_MEA		13	/* MCAR effective address */
#ifndef	PPC_e6500
#define _PPC_MCSR_BIT_STE		14	/* Self-test error */
#endif	/* !PPC_e6500 */
#define _PPC_MCSR_BIT_IF		15	/* instr fetch error report */
#define _PPC_MCSR_BIT_LD		16	/* load instr error report */
#define _PPC_MCSR_BIT_ST		17	/* store instr error report */
#define _PPC_MCSR_BIT_LDG		18	/* guarded ld instr error */
#ifdef	PPC_e6500
#define _PPC_MCSR_BIT_LRAT_MHIT		29	/* LRAT translation */
#else
#define _PPC_MCSR_BIT_TLBSYNC		30	/* simultaneous tlbsync */
#define _PPC_MCSR_BIT_BSL2_ERR		31	/* L2 cache error */
#endif	/* PPC_e6500 */

/* Guest O/S registers */
#define GSPRG0  592     /* Guest SPR General 0 */
#define GSPRG1  593     /* Guest SPR General 1 */
#define GSPRG2  594     /* Guest SPR General 2 */
#define GSPRG3  595     /* Guest SPR General 3 */
#define GESR    596     /* Guest Exception Syndrome Register */
#define GEPR    698     /* Guest External Input Vector Register */
#define GSRR0   699     /* Guest SRR0 */
#define GSRR1   700     /* Guest SRR1 */
#define GPIR    701     /* Guest PIR */

/* Ultravisor registers */
#define EPR     702     /* External Input Proxy Register (RO) */
#define UVCSR   703     /* Ultravisor Control and Status Register */
#define GIVPR   912     /* Guest Interrupt Vector Prefix Register */
#define GIVOR2  913     /* Guest IVOR Data Storage */
#define GIVOR3  914     /* Guest IVOR Instruction Storage */
#define GIVOR4  915     /* Guest IVOR External Input */
#define GIVOR8  918     /* Guest IVOR System Call */
#define GIVOR13 919     /* Guest IVOR Data TLB Error */
#define GIVOR14 920     /* Guest IVOR Instruction TLB Error */

#endif /* PPC_e500mc */

#ifdef _WRS_SPE_SUPPORT
#define SPEFSCR 512     /* SPE Floating-pt Status and Control Register */

/* High word error bits */
#define _PPC_SPEFSCR_SOVH    0x80000000
#define _PPC_SPEFSCR_OVH     0x40000000
#define _PPC_SPEFSCR_FGH     0x20000000
#define _PPC_SPEFSCR_FXH     0x10000000
#define _PPC_SPEFSCR_FINVH   0x08000000
#define _PPC_SPEFSCR_FDBZH   0x04000000
#define _PPC_SPEFSCR_FUNFH   0x02000000
#define _PPC_SPEFSCR_FOVFH   0x01000000

/* Status Bits */
#define _PPC_SPEFSCR_FINXS   0x00200000
#define _PPC_SPEFSCR_FINVS   0x00100000
#define _PPC_SPEFSCR_FDBZS   0x00080000
#define _PPC_SPEFSCR_FUNFS   0x00040000
#define _PPC_SPEFSCR_FOVFS   0x00020000
#define _PPC_SPEFSCR_MODE    0x00010000

#define _PPC_SPEFSCR_SOV     0x00008000
#define _PPC_SPEFSCR_OV      0x00004000
#define _PPC_SPEFSCR_FG      0x00002000
#define _PPC_SPEFSCR_FX      0x00001000
#define _PPC_SPEFSCR_FINV    0x00000800
#define _PPC_SPEFSCR_FDBZ    0x00000400
#define _PPC_SPEFSCR_FUNF    0x00000200
#define _PPC_SPEFSCR_FOVF    0x00000100

#define _PPC_SPEFSCR_FINXE   0x00000040
#define _PPC_SPEFSCR_FINVE   0x00000020
#define _PPC_SPEFSCR_FDBZE   0x00000010
#define _PPC_SPEFSCR_FUNFE   0x00000008
#define _PPC_SPEFSCR_FOVFE   0x00000004
#define _PPC_SPEFSCR_FRMC_RND_NR 0x00000000
#define _PPC_SPEFSCR_FRMC_RND_ZERO 0x00000001
#define _PPC_SPEFSCR_FRMC_RND_PINF 0x00000002
#define _PPC_SPEFSCR_FRMC_RND_NINF 0x00000003
#endif /* _WRS_SPE_SUPPORT */

/* SPRG0-SPRG3 are defined correctly in asmPpc.h */
#define SPRG4_R 260     /* Special Purpose Register General 4, read */
#define SPRG4_W 276     /* Special Purpose Register General 4, write */
#define SPRG5_R 261     /* Special Purpose Register General 5, read */
#define SPRG5_W 277     /* Special Purpose Register General 5, write */
#define SPRG6_R 262     /* Special Purpose Register General 6, read */
#define SPRG6_W 278     /* Special Purpose Register General 6, write */
#define SPRG7_R 263     /* Special Purpose Register General 7, read */
#define SPRG7_W 279     /* Special Purpose Register General 7, write */
#define TBL_R   268     /* Time Base Lower, read */
#define TBL_W   284     /* Time Base Lower, write */
#define TBU_R   269     /* Time Base Upper, read */
#define TBU_W   285     /* Time Base Upper, write */
#define TCR     340     /* Timer Control Register */
#define TSR     336     /* Timer Status Register */
#define USPRG0  256     /* User Special Purpose Register General 0 */
#define DBCR0   308     /* Debug Control Register 0 */
#define DBCR1   309     /* Debug Control Register 1 */
#define DBCR2   310     /* Debug Control Register 2 */
#define DBSR    304     /* Debug Status Register */
#define IAC1    312     /* Instr Address Compare Register 1 */
#define IAC2    313     /* Instr Address Compare Register 2 */
#define DAC1    316     /* Data Address Compare Register 1 */
#define DAC2    317     /* Data Address Compare Register 2 */
#define L1CFG0  515     /* L1 Config Register 0 */
#define L1CFG1  516     /* L1 Config Register 1 */
#define L1CSR0  1010    /* L1 Control Status Register 0 */
#define L1CSR1  1011    /* L1 Control Status Register 1 */
#if defined(PPC_e500mc) || defined(PPC_e6500)
#define L1CSR2  606     /* L1 Control Status Register 2 */

/* L2 Cache defines */

#ifdef PPC_e6500
#ifdef  _ASMLANGUAGE
#   define CAST(x)
#else /* _ASMLANGUAGE */
typedef volatile unsigned char  VCHAR;      /* shorthand for volatile unsigned char */
typedef volatile signed int     VINT32;     /* volatile signed word */
typedef volatile signed short   VINT16;     /* volatile signed halfword */
typedef volatile signed char    VINT8;      /* volatile signed byte */
typedef volatile unsigned int   VUINT32;    /* volatile unsigned word */
typedef volatile unsigned short VUINT16;    /* volatile unsigned halfword */
typedef volatile unsigned char  VUINT8;     /* volatile unsigned byte */
#   define CAST(x)  (x)
#endif  /* _ASMLANGUAGE */

/* L2 Cache register defines*/

#define L2CACHE_REG_BASE	0xC20000
#define L2CSR0_OFFSET		0x000
#define L2CSR1_OFFSET		0x004
#define L2CFG0_OFFSET		0x008
#define L2ERRINJCTL_OFFSET	0xE08
#define L2CAPTDATAHI_OFFSET	0xE20
#define L2CAPTDATALO_OFFSET	0xE24
#define L2CAPTECC_OFFSET	0xE28
#define L2ERRDET_OFFSET		0xE40
#define L2ERRINTEN_OFFSET	0xE48
#define L2ERRATTR_OFFSET	0xE4C
#define L2ERRADDR_OFFSET	0xE50
#define L2ERRCTL_OFFSET		0xE58
#define L2C_REG_INTERVAL	0x40000
#define L2C_REG_ADDR(cluster, ccsbar, offset) \
	(CAST(VUINT32 *)(ccsbar + L2CACHE_REG_BASE + offset + \
			 (cluster * L2C_REG_INTERVAL)))

#define L2C_REG_ADDR_OFFSET(cluster, offset) \
	 (L2CACHE_REG_BASE + offset + (cluster * L2C_REG_INTERVAL))
			 
#define L2CSR0(cluster, ccsbar) L2C_REG_ADDR(cluster, ccsbar, L2CSR0_OFFSET)
#define L2CSR1(cluster, ccsbar) L2C_REG_ADDR(cluster, ccsbar, L2CSR1_OFFSET)
#define L2CFG0(cluster, ccsbar) L2C_REG_ADDR(cluster, ccsbar, L2CFG0_OFFSET)
#define L2ERRINJCTL(cluster, ccsbar)	L2C_REG_ADDR(cluster, ccsbar, L2ERRINJCTL_OFFSET)

#define L2ERRINJCTL_CLUSTER_OFFSET(cluster) (L2CACHE_REG_BASE + L2ERRINJCTL_OFFSET + (cluster * L2C_REG_INTERVAL))

#define L2CAPTDATAHI(cluster, ccsbar)	L2C_REG_ADDR(cluster, ccsbar, L2CAPTDATAHI_OFFSET)
#define L2CAPTDATALO(cluster, ccsbar)	L2C_REG_ADDR(cluster, ccsbar, L2CAPTDATALO_OFFSET)
#define L2CAPTECC(cluster, ccsbar)	L2C_REG_ADDR(cluster, ccsbar, L2CAPTECC_OFFSET)
#define L2ERRDET(cluster, ccsbar)	L2C_REG_ADDR(cluster, ccsbar, L2ERRDET_OFFSET)
#define L2ERRINTEN(cluster, ccsbar)	L2C_REG_ADDR(cluster, ccsbar, L2ERRINTEN_OFFSET)
#define L2ERRATTR(cluster, ccsbar)	L2C_REG_ADDR(cluster, ccsbar, L2ERRATTR_OFFSET)
#define L2ERRADDR(cluster, ccsbar)	L2C_REG_ADDR(cluster, ccsbar, L2ERRADDR_OFFSET)
#define L2ERRCTL(cluster, ccsbar)	L2C_REG_ADDR(cluster, ccsbar, L2ERRCTL_OFFSET)

/* L2CSR0 BIT MASKS and BIT SHIFTS */

#define L2CSR0_L2E_BIT      0             /* L2 Enable */
#define L2CSR0_L2PE_BIT     1             /* L2 Parity Enable */
#define L2CSR0_L2FI_BIT     10            /* L2 Flash Invalidate */
#define L2CSR0_L2REP_BIT    19            /* L2 Line Replcmnt Algo. (2) */
#define L2CSR0_L2FL_BIT     20            /* L2 Flush */
#define L2CSR0_L2LFC_BIT    21            /* L2 Lock Flush Clear */
#define L2CSR0_L2LOA_BIT    24            /* L2 Lock Overflow Allocate */
#define L2CSR0_L2LO_BIT     26            /* L2 Lock Overflow */

#define L2CSR0_L2E_MSK      (1U << (31 - L2CSR0_L2E_BIT))
#define L2CSR0_L2PE_MSK     (1U << (31 - L2CSR0_L2PE_BIT))
#define L2CSR0_L2FI_MSK     (1U << (31 - L2CSR0_L2FI_BIT))
#define L2CSR0_L2REP_MSK    (3U << (31 - L2CSR0_L2REP_BIT))
#define L2CSR0_L2FL_MSK     (1U << (31 - L2CSR0_L2FL_BIT))
#define L2CSR0_L2LFC_MSK    (1U << (31 - L2CSR0_L2LFC_BIT))
#define L2CSR0_L2LOA_MSK    (1U << (31 - L2CSR0_L2LOA_BIT))
#define L2CSR0_L2LO_MSK     (1U << (31 - L2CSR0_L2LO_BIT))

/* L2CSR1 BIT MASKS and BIT SHIFTS */

#define L2CSR1_DYNAMICHARVARD_BIT 0	/* Dynamic harvard mode */
#define L2CSR1_L2BHM_BIT          1	/* Bank hash mode */
#define L2CSR1_L2STASHRSRV_BIT    3	/* L2 stashing reserved resources */
#define L2CSR1_L2STASHID_BIT      24	/* L2 cache stash ID */

#define L2CSR1_DYNAMICHARVARD_MSK (1U << (31 - L2CSR1_DYNAMICHARVARD_BIT))
#define L2CSR1_L2BHM_MSK          (1U << (31 - L2CSR1_L2BHM_BIT))
#define L2CSR1_L2CSR1_MSK         (3U << (31 - L2CSR1_L2STASHRSRV_BIT))
#define L2CSR1_L2STASHID_MSK      (255U < (31 - L2CSR1_L2STASHID_MSK))

/* L3 Cache register defines */

#define CPCCSR0(addr, cpcNum)   (CAST(VUINT32 *) (addr + 0x010000  \
                                          +(cpcNum * 0x001000)))

#define CPCPAR(addr, cpcNum,n)  (CAST(VUINT32 *) (addr + 0x010000  \
                                          +(cpcNum * 0x001000)     \
                                          + 0x000208  + n*0x10 ))

#define CPCEWCR(addr, cpcNum,n) (CAST(VUINT32 *) (addr + 0x010000  \
                                          +(cpcNum * 0x001000)     \
                                          + 0x000010  + n*0x10 ))

#define CPCEWBAR(addr, cpcNum,n)(CAST(VUINT32 *) (addr + 0x010000  \
                                          +(cpcNum * 0x001000)     \
                                          + 0x000014  + n*0x10 ))

#define CPCHDBCR(addr, cpcNum)  (CAST(VUINT32 *) (addr + 0x010000  \
                                          +(cpcNum * 0x001000)     \
                                          + 0x000F00  ))

#define CPC_ENABLE          0x80000000  /* CPCCSR0_CPCE */
#define CPC_FLUSH           0x00000800  /* CPCCSR0_CPCFL */
#define CPC_INVALIDATE      0x00200400  /* CPCCSR0_CPCFI | CPCCSR0_CPCLFC */
#define CPC_CLEAR_LOCKS     0x00000400  /* CPCCSR0_CPCLFC */

#define CPC_MODE_WRITE_THROUGH  0x00080000  /* CPCCSR0_CPCWT */

/* Per sect 8.2.9  (sect. 2.7.3 set reserved = 0) */

#define CPCPAR_RESET_VALUE  0x000003fb

#define CPC1_BASE_ADDR		0x010000
#define CPC2_BASE_ADDR		0x011000
#define CPC3_BASE_ADDR		0x012000

#define CPCEWCR0(x)		    (x + 0x010)
#define CPCEWBAR0(x)        (x + 0x014)
#define CPCEWCR1(x)		    (x + 0x020)
#define CPCEWBAR1(x)	    (x + 0x024)
#define CPCSRCR1(x)		    (x + 0x100)
#define CPCSRCR0(x)		    (x + 0x104)
#define CPCPIR(x,y)		    (x + 0x200 + y * 0x10)
#define CPCPWR(x,y)		    (x + 0x20C + y * 0x10)
#define CPCERRINJHI(x)		(x + 0xE00)
#define CPCERRINJLO(x)		(x + 0xE04)
#define CPCERRINJCTL(x)		(x + 0xE08)
#define CPCCAPTDATAHI(x)	(x + 0xE20)
#define CPCCAPTDATALOW(x)	(x + 0xE24)
#define CPCCAPTECC(x)		(x + 0xE28)
#define CPCERRDET(x)		(x + 0xE40)
#define CPCERRDIS(x)		(x + 0xE44)
#define CPCERRINTEN(x)		(x + 0xE48)
#define CPCERRATTR(x)		(x + 0xE4C)
#define CPCERREADDR(x)		(x + 0xE50)
#define CPCERRADDR(x)		(x + 0xE54)
#define CPCERRCTL(x)		(x + 0xE58)

#define CPCCSR0_CPCE_BIT	0 	/* CPC enable */
#define CPCCSR0_CPCPE_BIT	1 	/* CPC parity/ECC enable */
#define CPCCSR0_CPCFI_BIT	10 	/* CPC flash invalidate */
#define CPCCSR0_CPCWT_BIT	12 	/* CPC write-through mode */
#define CPCCSR0_CPCREP_BIT	18 	/* CPC line replacement algorithm (2) */
#define CPCCSR0_CPCFL_BIT	20 	/* CPC flush */
#define CPCCSR0_CPCLFC_BIT	21 	/* CPC lock flash clear */
#define CPCCSR0_CPCLOA_BIT	24 	/* CPC lock overflow allocate */
#define CPCCSR0_CPCLO_BIT	26 	/* CPC lock overflow */

#define CPCCSR0_CPCE_MSK	(1U << (31 - CPCCSR0_CPCE_BIT))
#define CPCCSR0_CPCPE_MSK	(1U << (31 - CPCCSR0_CPCPE_BIT))
#define CPCCSR0_CPCFI_MSK	(1U << (31 - CPCCSR0_CPCFI_BIT))
#define CPCCSR0_CPCWT_MSK	(1U << (31 - CPCCSR0_CPCWT_BIT))
#define CPCCSR0_CPCREP_MSK	(3U << (31 - CPCCSR0_CPCREP_BIT - 1))
#define CPCCSR0_CPCFL_MSK	(1U << (31 - CPCCSR0_CPCFL_BIT))
#define CPCCSR0_CPCLFC_MSK	(1U << (31 - CPCCSR0_CPCLFC_BIT))
#define CPCCSR0_CPCLOA_MSK	(1U << (31 - CPCCSR0_CPCLOA_BIT))
#define CPCCSR0_CPCLO_MSK	(1U << (31 - CPCCSR0_CPCLO_BIT))

#define CPC_WRITE_MODE_WT   0x00080000  /* CPCCSR0_CPCWT */
#define CPC_WRITE_MODE_CB   0

/* CPCEWCRn field definitions */

#define CPCEWCRN_E_BIT		0	/* Enable */
#define CPCEWCRN_LOCK_BIT	1	/* Lock */
#define CPCEWCRN_SIZE_BIT	10	/* Size (6) 2^(size + 6) */
#define CPCEWCRN_EADDRBASE_BIT	16	/* Extended base address (16) */
#else
#define L2CAPTDATAHI 988 /* L2 Error Capture Data High */
#define L2CAPTDATALO 989 /* L2 Error Capture Data Low */
#define L2CAPTECC 990   /* L2 Error Capture ECC Syndrome */
#define L2CFG0 	519	/* L2 Configuration Register */
#define L2CSR0	1017	/* L2 Control and Status Register 0 */
#define L2CSR1	1018	/* L2 Control and Status Register 1 */
#define L2ERRADDR 722	/* L2 Error Address */
#define L2ERRATTR 721	/* L2 Error Attribute */
#define L2ERRCTL 724	/* L2 Error Control */
#define L2ERRDET 991	/* L2 Error Detect */
#define L2ERRDIS 725	/* L2 Error Disable */
#define L2ERREADDR 723	/* L2 Error Extended Address */
#define L2ERRINJCTL 987	/* L2 Error Injection Control */
#define L2ERRINJHI 985	/* L2 Error Injection Mask High */
#define L2ERRINJLO 986	/* L2 Error Injection Mask Low */
#define L2ERRINTEN 720	/* L2 Error Interrupt Enable */
#endif /* PPC_e6500 */
#endif /* PPC_e500mc */
#ifdef PPC_e200
#define L1FINV0 1016
#endif	/* PPC_e200 */

#define MAS0    624     /* MMU Assist Register 0 */
#define MAS1    625     /* MMU Assist Register 1 */
#define MAS2    626     /* MMU Assist Register 2 */
#define MAS3    627     /* MMU Assist Register 3 */
#define MAS4    628     /* MMU Assist Register 4 */
#if defined(PPC_e500mc) || defined(PPC_e6500)
#define MAS5    339     /* MMU Assist Register 5 */
#endif /* PPC_e500mc */
#define MAS6    630     /* MMU Assist Register 6 */
#if defined(PPC_e500v2) || defined(PPC_e500mc) || defined(PPC_e6500)
#define MAS7    944     /* MMU Assist Register 7 */
#endif /* PPC_e500v2 */
#if defined(PPC_e500mc) || defined(PPC_e6500)
#define MAS8    341     /* MMU Assist Register 8 */
#endif /* PPC_e500mc */

#define TLB0CFG 688     /* TLB 0 Config Register */
#define TLB1CFG 689     /* TLB 1 Config Register */
#define MMUCSR0 1012    /* MMU Control Status Register 0 */
#define MMUCFG  1015    /* MMU Config Register */

#ifndef _ASMLANGUAGE
#if defined(PPC_e6500)
/*
 * The TLB miss handler implementing the Hardware table walk creates an 
 * indirect TBL entry in TLB1. The TLB1 is also used for defining static
 * TLB entries. The TLB1 entries need to be shared by both of them.
 * The tlb1EntrySelect structure entries are used by the hardware table walk
 * algorithm to manage the useage of the TLB1 entries.
 * eselLock entry is used as a spinlock to ensure that at any given time only 
 * one thread is running the miss handlers.
 */

typedef struct tlb1EntrySelect  /* TLB1 ESEL */
    {
    unsigned char eselNext;             /* next index for TLB1 ESEL */
    unsigned char eselStart;            /* first index for TLB1 ESEL */
    unsigned char eselMax;              /* last index for TLB1 ESEL */
    unsigned char eselLock;             /* Per core spinlock for e6500 hw table walk */
    } TLB1ESEL;
#endif
#endif

#define PIR     286
#define SVR     1023    /* silicon version register */

#if defined(PPC_e500mc) || defined(PPC_e6500)
#define LPIDR   338     /* Logical Partition ID Register */
#endif /* PPC_e500mc */

/* MSR (upper half) definitions */
/* ppcArch.h defines a generic MSR.  Here we define changes from that base */

#undef  _PPC_MSR_SF_U           /* 64 bit mode not implemented */
#undef  _PPC_MSR_ILE_U          /* little endian mode not supported */

/* wait state enable is equivalent to the power down enable for 60x */
#define _PPC_MSR_WE_U   0x0004          /* wait state enable */
#undef _PPC_MSR_POW_U
#define _PPC_MSR_POW_U  _PPC_MSR_WE_U

#define _PPC_MSR_WE     0x00040000      /* wait state enable */

#define _PPC_MSR_CE_U   0x0002          /* critical interrupt enable */
#define _PPC_MSR_CE     0x00020000      /* critical interrupt enable */


/* MSR (lower half) definitions */

#undef  _PPC_MSR_IR             /* insn address translation (always on) */
#undef  _PPC_MSR_DR             /* data address translation (always on) */
#undef  _PPC_MSR_SE             /* single step unsupported */
#undef  _PPC_MSR_BE             /* branch trace not supported */
#undef  _PPC_MSR_IP             /* exception prefix bit not supported */
#undef  _PPC_MSR_RI             /* recoverable interrupt unsupported */
#undef  _PPC_MSR_LE             /* little endian mode unsupported */
#undef  _PPC_MSR_BIT_LE         /* little endian mode unsupported */

/*
 * Machine check exception class is new to PPC in E500.  Although
 * bit position is same as classic MSR[ME] and is named the same,
 * the define of _PPC_MSR_MCE signifies the present of this
 * class of exception.  If present, both _PPC_MSR_MCE and
 * _PPC_MSR_ME should be defined to the mask of 0x1000.
 * In addition, Critical Exception Class is also a requirement.
 * The critical exception code stub does not mask exceptions
 * and is used for machine check exception class as well.
 * Therefore, _EXC_OFF_CRTL should be defined.
 */
#ifndef PPC_e200
#define _PPC_MSR_MCE    _PPC_MSR_ME	/* machine check enable */
#else
#undef _PPC_MSR_MCE
#endif	/* PPC_e200 */

#define _PPC_MSR_DE     0x0200		/* debug exception enable */
#define _PPC_MSR_IS     0x0020		/* insn address space selector */
#define _PPC_MSR_DS     0x0010		/* data address space selector */

#define	_PPC_MSR_BIT_WE		13
#define	_PPC_MSR_BIT_CE		14
#define	_PPC_MSR_BIT_DE		22
#define _PPC_MSR_BIT_IS		26
#define _PPC_MSR_BIT_DS		27

/* INT_MASK definition (mask EE & CE bits) : overwrite the one in asmPpc.h */

#undef  INT_MASK
#define INT_MASK(src, des) \
	rlwinm  des, src, 0, _PPC_MSR_BIT_EE+1, _PPC_MSR_BIT_EE-1; \
	rlwinm  des, des, 0, _PPC_MSR_BIT_CE+1, _PPC_MSR_BIT_CE-1

#undef  INT_WE_MASK
#define INT_WE_MASK(src, des) \
	rlwinm  des, src, 0, _PPC_MSR_BIT_WE+1, _PPC_MSR_BIT_WE-1
	
#define HID0  1008
#if !defined(PPC_e500mc) && !defined(PPC_e6500)
#define HID1  1009
#endif /* PPC_e500mc */
#define DECAR 54
#define BUCSR 1013

#define _PPC_BUCSR_FI 0x200            /* Invalidate branch cache */
#define _PPC_BUCSR_E 0x1               /* Enable branch prediction */


/* E500core other than e500mc has no FPU */
#ifndef _WRS_HARDWARE_FP
#undef  _PPC_MSR_FP             /* floating point not available */
#undef  _PPC_MSR_FE1            /* floating point not available */
#undef  _PPC_MSR_FE0            /* floating point not available */
#undef  _PPC_MSR_BIT_FP         /* MSR Floating Point Aval. bit - FP */
#undef  _PPC_MSR_BIT_FE0        /* MSR FP exception mode 0 bit - FE0 */
#undef  _PPC_MSR_BIT_FE1        /* MSR FP exception mode 1 bit - FE1 */
#undef  _EXC_PROG_SRR1_FPU      /* floating point not available */
#else	/* _WRS_HARDWARE_FP */
#define _WRS_FP_CLASS_HW	1
#define  _PPC_MSR_BIT_FP         18
#define  _PPC_MSR_BIT_FE0        20
#define  _PPC_MSR_BIT_FE1        23
#endif	/* _WRS_HARDWARE_FP */

/* MSR MMU Bit extraction */

#define _PPC_MSR_MMU_RI_EXTRACT(src, dst) \
	rlwinm	dst, src, 0, _PPC_MSR_BIT_IS, _PPC_MSR_BIT_DS

#ifdef	_WRS_HARDWARE_FP
#define	_PPC_MSR_MMU_RI_FP_EXTRACT(src, dst) \
	li	dst, _PPC_MSR_FP | _PPC_MSR_IS | _PPC_MSR_DS ; \
	and	dst, dst, src
#else	/* _WRS_HARDWARE_FP */
#if defined(PPC_e500mc) || defined(PPC_e6500)
#define	_PPC_MSR_MMU_RI_FP_EXTRACT(src, dst) \
	li	dst, _PPC_MSR_IS | _PPC_MSR_DS ; \
	and	dst, dst, src
#else	/* PPC_e500mc */
#define	_PPC_MSR_MMU_RI_FP_EXTRACT(src, dst) \
	lis	dst, _PPC_MSR_SPE_U ;\
	ori	dst, dst, _PPC_MSR_IS | _PPC_MSR_DS ; \
	and	dst, dst, src
#endif /* PPC_e500mc */
#endif	/* _WRS_HARDWARE_FP */

/*
 * Exception syndrome register mask bits:
 * 0 - error not occured 1 - error occured
 */
#define _PPC_ESR_PIL_U 0x0800      /* Pgm Interrupt -- Illegal Insn */
#define _PPC_ESR_PPR_U 0x0400      /* Pgm Interrupt -- Previleged Insn */
#define _PPC_ESR_PTR_U 0x0200      /* Pgm Interrupt -- Trap */
#if defined(PPC_e500mc) || defined(PPC_e6500)
#define _PPC_ESR_FP_U  0x0100      /* Floating Point Operation */
#endif /* PPC_e500mc */
#define _PPC_ESR_ST_U  0x0080      /* Store Operation */
#define _PPC_ESR_DLK_U 0x0020      /* Data Locked -- DSI occured */
#define _PPC_ESR_ILK_U 0x0010      /* Inst Locked -- DSI occured */
#define _PPC_ESR_AP_U  0x0008      /* AP Operation */
#define _PPC_ESR_BO_U  0x0002      /* Byte Ordering Exception */
#define _PPC_ESR_PIL   0x08000000  /* Pgm Interrupt -- Illegal Insn */
#define _PPC_ESR_PPR   0x04000000  /* Pgm Interrupt -- Previleged Insn */
#define _PPC_ESR_PTR   0x02000000  /* Pgm Interrupt -- Trap */
#if defined(PPC_e500mc) || defined(PPC_e6500)
#define _PPC_ESR_FP    0x01000000  /* Floating Point Operation */
#endif /* PPC_e500mc */
#define _PPC_ESR_ST    0x00800000  /* Store Operation */
#define _PPC_ESR_DLK   0x00200000  /* Data Storage Interrupt -- Locking */
#define _PPC_ESR_ILK   0x00100000  /* Inst Locked -- DSI occured */
#define _PPC_ESR_AP    0x00080000  /* AP Operation */
#define _PPC_ESR_BO    0x00020000  /* Byte Ordering Exception */
#ifdef _WRS_SPE_SUPPORT
#define _PPC_ESR_SPE   0x00000080  /* SPE exception */
#endif /* _WRS_SPE_SUPPORT */

/* Bits in the upper half of TCR */
#define _PPC_TCR_WP_U     0xc000  /* Watchdog Timer Period */
#define _PPC_TCR_WRC_U    0x3000  /* Watchdog Timer Reset Control */
#define _PPC_TCR_WIE_U    0x0800  /* Watchdog Timer Interrupt Enable */
#define _PPC_TCR_DIE_U    0x0400  /* Decrementer Interrupt Enable */
#define _PPC_TCR_FP_U     0x0300  /* Fixed Interval Timer Period */
#define _PPC_TCR_FIE_U    0x0080  /* Fixed Interval Timer Interrupt Enable */
#define _PPC_TCR_ARE_U    0x0040  /* Decrementer Auto-Reload Enable */
#define _PPC_TCR_WPEXT_U  0x0040  /* Decrementer Auto-Reload Enable */
#define _PPC_TCR_FPEXT_U  0x0040  /* Decrementer Auto-Reload Enable */

/* Bits in the upper half of TSR */
#define _PPC_TSR_ENW_U  0x8000  /* Enable Next Watchdog Timer Exception */
#define _PPC_TSR_WIS_U  0x4000  /* Watchdog Timer Interrupt Status */
#define _PPC_TSR_WRS_U  0x3000  /* Watchdog Timer Reset Status */
#define _PPC_TSR_DIS_U  0x0800  /* Decrementer Interrupt Status */
#define _PPC_TSR_FIS_U  0x0400  /* Fixed Interval Timer Interrupt Status */

/* versions of the aligned for 32-bit TCR/TSR register access */
#define _PPC_TCR_DIE (_PPC_TCR_DIE_U << 16)
#define _PPC_TSR_DIS (_PPC_TSR_DIS_U << 16)

/* hardware dependent register 0 */
#define _PPC_HID0_DOZE_U    0x0080      /* DOZE power management mode */
#define _PPC_HID0_NAP_U	    0x0040      /* NAP power management mode */
#define _PPC_HID0_SLEEP_U   0x0020      /* SLEEP power management mode */
#define _PPC_HID0_DOZE  0x00800000      /* DOZE power management mode */
#define _PPC_HID0_NAP   0x00400000      /* NAP power management mode */
#define _PPC_HID0_SLEEP 0x00200000      /* SLEEP power management mode */
#define _PPC_HID0_TBEN	0x00004000	/* time base enable */
#if defined(PPC_e500v2) || defined(PPC_e500mc) || defined(PPC_e6500)
#define _PPC_HID0_MAS7EN  0x00000080    /* Enable use of MAS7 for tlbre */
#define _PPC_HID0_DCFA    0x00000040    /* Use this bit to flush only valid entries same as 74XX */
#define _PPC_HID0_BIT_MAS7EN   24
#define _PPC_HID0_BIT_DCFA     25
#define _PPC_85XX_USE_DCFA
#endif	/* PPC_e500v2 */

/* hardware dependent register 1 */
#define _PPC_HID1_ABE   0x00001000      /* Address broadcast enable */

/* Cache Defines */ 

/* Instruction and Data Cache bit fields are the same */
#ifndef PPC_e200
#define _PPC_L1CSR_E   0x00000001 /* Enable */
#define _PPC_L1CSR_FI  0x00000002 /* Flash Invalidate */
#define _PPC_L1CSR_FLR 0x00000100 /* Lock Bits Flash */
#define _PPC_L1CSR_LO  0x00000200 /* Lock Overflow */
#define _PPC_L1CSR_UL  0x00000400 /* Unable to lock   - status bit */
#define _PPC_L1CSR_UL_V(x)  (x >> 10)
#define _PPC_L1CSR_SLC 0x00000800 /* Snoop lock clear  - status bit */
#define _PPC_L1CSR_SLC_V(x) (x >> 11)
#define _PPC_L1CSR_PIE 0x00008000 /* Parity Injection Enable */
#define _PPC_L1CSR_CPE 0x00010000 /* Parity Enable */

/* Instruction and Datat Cache bit fields are the same */
#define _PPC_L1CFG_SIZE_MASK   0x00000FFF
#define _PPC_L1CFG_NWAY_MASK   0x000FF000
#define _PPC_L1CFG_NWAY_V(x)   (x >> 12)
#define _PPC_L1CFG_PA_MASK     0x00100000
#define _PPC_L1CFG_PA_V(x)     (x >> 16)
#define _PPC_L1CFG_LA_MASK     0x00200000
#define _PPC_L1CFG_LA_V(x)     (x >> 17)
#define _PPC_L1CFG_REPL_MASK   0x00400000
#define _PPC_L1CFG_REPL_V(x)   (x >> 18)
#define _PPC_L1CFG_BSIZE_MASK  0x01800000
#define _PPC_L1CFG_BSIZE_V(x)  (x >> 19)
#define _PPC_L1CFG_CARCH_MASK  0xC0000000    /* L1CFG0 only */
#define _PPC_L1CFG_CARCH_V(x)  (x >> 30)

#else /* PPC_e200 */

#define _PPC_L1CSR_WID_MSK 0xf0000000
#define _PPC_L1CSR_WID_SHFT 28
#define _PPC_L1CSR_WDD_MSK 0x0f000000
#define _PPC_L1CSR_WDD_SHFT 24
#define _PPC_L1CSR_WID_SET(x)  ((x<<_PPC_L1CSR_WID_SHFT) & _PPC_L1CSR_WID_MSK)
#define _PPC_L1CSR_WDD_SET(x)  ((x<<_PPC_L1CSR_WDD_SHFT) & _PPC_L1CSR_WDD_MSK)
#define _PPC_L1CSR_WID_GET(x)  ((x & _PPC_L1CSR_WID_MSK)>>_PPC_L1CSR_WID_SHFT)
#define _PPC_L1CSR_WDD_GET(x)  ((x & _PPC_L1CSR_WDD_MSK)>>_PPC_L1CSR_WDD_SHFT)

#define _PPC_L1CSR_AWID   0x00800000
#define _PPC_L1CSR_AWDD   0x00400000
#define _PPC_L1CSR_CWM    0x00100000
#define _PPC_L1CSR_DPB    0x00080000
#define _PPC_L1CSR_DSB    0x00040000
#define _PPC_L1CSR_DSTRM  0x00020000
#define _PPC_L1CSR_CPE    0x00010000
#define _PPC_L1CSR_CUL    0x00000800
#define _PPC_L1CSR_CLO    0x00000400
#define _PPC_L1CSR_CLFC   0x00000200
#define _PPC_L1CSR_CABT   0x00000004
#define _PPC_L1CSR_CINV   0x00000002
#define _PPC_L1CSR_CE     0x00000001

#define _PPC_L1CFG_SIZE_MASK   0x000007FF
#define _PPC_L1CFG_NWAY_MASK   0x007FF100
#define _PPC_L1CFG_NWAY_V(x)   (x >> 11)
#define _PPC_L1CFG_PA_MASK     0x00080000
#define _PPC_L1CFG_PA_V(x)     (x >> 19)
#define _PPC_L1CFG_LA_MASK     0x00100000
#define _PPC_L1CFG_LA_V(x)     (x >> 20)
#define _PPC_L1CFG_REPL_MASK   0x00600000
#define _PPC_L1CFG_REPL_V(x)   (x >> 21)
#define _PPC_L1CFG_BSIZE_MASK  0x01800000
#define _PPC_L1CFG_BSIZE_V(x)  (x >> 23)
#define _PPC_L1CFG_CFISWA_MASK 0x08000000  
#define _PPC_L1CFG_CFAHA_MASK  0x10000000
#define _PPC_L1CFG_CWPA_MASK   0x20000000
#define _PPC_L1CFG_CARCH_MASK  0xC0000000  
#define _PPC_L1CFG_CARCH_V(x)  (x >> 30)

#define _PPC_L1FINV0_CWAY_MSK  0x07000000
#define _PPC_L1FINV0_CWAY_SET(x) ((x << 24) & _PPC_L1FINV0_CWAY_MSK)
#define _PPC_L1FINV0_CSET_MSK  0x00000FC0
#define _PPC_L1FINV0_CSET_SET(x) ((x << 6) & _PPC_L1FINV0_CSET_MSK)
#define _PPC_L1FINV0_CCMD_MSK  0x00000003
#define _PPC_L1FINV0_CCMD_SET(x) (x & _PPC_L1FINV0_CCMD_MSK)

#ifndef _ASMLANGUAGE
typedef union e200_l1cfg0
    {
    unsigned int l1Cfg0;
    struct 
	{
	unsigned int carch:2;
	unsigned int cwpa:1;
	unsigned int cfaha:1;
	unsigned int cfiswa:1;
	unsigned int :2;
	unsigned int cbsize:2;
	unsigned int crepl:2;
	unsigned int cla:1;
	unsigned int cpa:1;
	unsigned int cnway:8;
	unsigned int csize:11;
	} field;
    } E200_L1CFG0;
#endif /* _ASMLANGUAGE */

#endif /* PPC_e200 */

#if defined(PPC_e500mc) || defined(PPC_e6500)
#define _PPC_L1CSR2_DCWS  	 0x40000000 /* Data cache write shadow */
#endif /* PPC_e500mc */

/* MMU register defines */
				 
#define PID     48
#define PID_MASK 0x0FF
#define PID0    48
#if !defined(PPC_e500mc) && !defined(PPC_e6500)
#define PID1    633
#define PID2    634
#endif /* PPC_e500mc */

#define _PPC_MMUCSR0_L2TLB1_FI  0x00000002
#define _PPC_MMUCSR0_L2TLB1_FI_V(x) (x >> 1)
#define _PPC_MMUCSR0_L2TLB0_FI  0x00000004
#define _PPC_MMUCSR0_L2TLB0_FI_V(x) (x >> 2)
#define _PPC_MMUCSR0_DL1MMU_FI  0x00000008
#define _PPC_MMUCSR0_DL1MMU_FI_V(x) (x >> 3)
#define _PPC_MMUCSR0_IL1MMU_FI  0x00000010
#define _PPC_MMUCSR0_IL1MMU_FI_V(x) (x >> 4)


#define _PPC_MAS0_NV           0x00000000
#define _PPC_MAS0_ESEL_MASK    0x03ff0000
#define _PPC_MAS0_ESEL_BIT     16
#define _PPC_MAS0_ESEL_V(x)    (x >> _PPC_MAS0_ESEL_BIT)
#define _PPC_MAS0_TLBSEL1      0x10000000
#define _PPC_MAS0_TLBSEL_MASK  0x30000000
#define _PPC_MAS1_V            0x80000000
#define _PPC_MAS6_SIND         0x00000002

/* processor version register value */

#define PVR_VALUE       0x80210030      /* expected value in PVR */

/* Range of hardware context numbers (PID register & TLB TID field) */

#define MMU_ASID_MIN            1
#define MMU_ASID_MAX            255
#define MMU_ASID_GLOBAL         MMU_ASID_MIN

/* debug control register 0 */
#define _DBCR0_IDM_U    0x4000          /* internal debug mode */
#define _DBCR0_RST_U    0x3000          /* reset */
#define _DBCR0_ICMP_U   0x0800          /* instruction completion debug event */
#define _DBCR0_BRT_U    0x0400          /* branch taken debug event */
#define _DBCR0_IRPT_U   0x0200          /* interrupt debug event */
#define _DBCR0_TRAP_U   0x0100          /* trap debug event */
#define _DBCR0_IAC1_U   0x0080          /* instruction address compare 1 */
#define _DBCR0_IAC2_U   0x0040          /* instruction address compare 2 */
#define _DBCR0_DAC1R_U  0x0008          /* data address compare 1 Read */
#define _DBCR0_DAC1W_U  0x0004          /* data address compare 1 Write */
#define _DBCR0_DAC2R_U  0x0002          /* data address compare 2 Read */
#define _DBCR0_DAC2W_U  0x0001          /* data address compare 2 Write */
#define _DBCR0_IDM      0x40000000      /* internal debug mode */
#define _DBCR0_RST      0x30000000      /* reset */
#define _DBCR0_ICMP     0x08000000      /* instruction completion debug event */
#define _DBCR0_BRT      0x04000000      /* branch taken */
#define _DBCR0_IRPT     0x02000000      /* exception debug event */
#define _DBCR0_TRAP     0x01000000      /* trap debug event */
#define _DBCR0_IAC1     0x00800000      /* instruction address compare 1 */
#define _DBCR0_IAC2     0x00400000      /* instruction address compare 2 */
#define _DBCR0_DAC1R    0x00080000      /* data address compare 1 Read */
#define _DBCR0_DAC1W    0x00040000      /* data address compare 1 Write */
#define _DBCR0_DAC2R    0x00020000      /* data address compare 2 Read */
#define _DBCR0_DAC2W    0x00010000      /* data address compare 2 Write */
#define _DBCR0_RET      0x00008000      /* return debug event */
#define _DBCR0_FT       0x00000001      /* freeze timers on debug */

/* debug control register 1 */
#define _DBCR1_IAC1US_U   0xc000        /* IAC 1 User/Supervisor */
#define _DBCR1_IAC1ER_U   0x3000        /* IAC 1 Effective/Real */
#define _DBCR1_IAC2US_U   0x0c00        /* IAC 2 User/Supervisor */
#define _DBCR1_IAC2ER_U   0x0300        /* IAC 2 Effective/Real */
#define _DBCR1_IAC12M_U   0x00c0        /* IAC 1/2 Mode */
#define _DBCR1_IAC12AT_U  0x0001        /* IAC 1/2 Auto-Toggle Enable */
#define _DBCR1_IAC1US     0xc0000000    /* IAC 1 User/Supervisor */
#define _DBCR1_IAC1ER     0x30000000    /* IAC 1 Effective/Real */
#define _DBCR1_IAC2US     0x0c000000    /* IAC 2 User/Supervisor */
#define _DBCR1_IAC2ER     0x03000000    /* IAC 2 Effective/Real */
#define _DBCR1_IAC12M     0x00c00000    /* IAC 1/2 Mode */

/* debug control register 2 */
#define _DBCR2_DAC1US_U   0xc000        /* DAC 1 User/Supervisor */
#define _DBCR2_DAC1ER_U   0x3000        /* DAC 1 Effective/Real */
#define _DBCR2_DAC2US_U   0x0c00        /* DAC 2 User/Supervisor */
#define _DBCR2_DAC2ER_U   0x0300        /* DAC 2 Effective/Real */
#define _DBCR2_DAC12M_U   0x00c0        /* DAC 1/2 Mode */
#define _DBCR2_DAC1US     0xc0000000    /* DAC 1 User/Supervisor */
#define _DBCR2_DAC1ER     0x30000000    /* DAC 1 Effective/Real */
#define _DBCR2_DAC2US     0x0c000000    /* DAC 2 User/Supervisor */
#define _DBCR2_DAC2ER     0x03000000    /* DAC 2 Effective/Real */
#define _DBCR2_DAC12M     0x00c00000    /* DAC 1/2 Mode */

/* debug status register */
#define _DBSR_IDE_U     0x8000          /* Imprecise Debug Event */
#define _DBSR_UDE_U     0x4000          /* Unconditional Debug Event */
#define _DBSR_MRR_U     0x3000          /* Most Recent Reset */
#define _DBSR_ICMP_U    0x0800          /* Instruction Completion Debug Event */
#define _DBSR_BRT_U     0x0400          /* Branch Taken Debug Event */
#define _DBSR_IRPT_U    0x0200          /* Interrupt Debug Event */
#define _DBSR_TRAP_U    0x0100          /* Trap Debug Event */
#define _DBSR_IAC1_U    0x0080          /* IAC 1 Debug Event */
#define _DBSR_IAC2_U    0x0040          /* IAC 2 Debug Event */
#define _DBSR_DAC1R_U   0x0008          /* DAC/DVC 1 Read Debug Event */
#define _DBSR_DAC1W_U   0x0004          /* DAC/DVC 1 Write Debug Event */
#define _DBSR_DAC2R_U   0x0002          /* DAC/DVC 2 Read Debug Event */
#define _DBSR_DAC2W_U   0x0001          /* DAC/DVC 2 Write Debug Event */
#define _DBSR_IDE       0x80000000      /* Imprecise Debug Event */
#define _DBSR_UDE       0x40000000      /* Unconditional Debug Event */
#define _DBSR_MRR       0x30000000      /* Most Recent Reset */
#define _DBSR_ICMP      0x08000000      /* Instruction Completion Debug Event */
#define _DBSR_BRT       0x04000000      /* Branch Taken Debug Event */
#define _DBSR_IRPT      0x02000000      /* Interrupt Debug Event */
#define _DBSR_TRAP      0x01000000      /* Trap Debug Event */
#define _DBSR_IAC1      0x00800000      /* IAC 1 Debug Event */
#define _DBSR_IAC2      0x00400000      /* IAC 2 Debug Event */
#define _DBSR_DAC1R     0x00080000      /* DAC/DVC 1 Read Debug Event */
#define _DBSR_DAC1W     0x00040000      /* DAC/DVC 1 Write Debug Event */
#define _DBSR_DAC2R     0x00020000      /* DAC/DVC 2 Read Debug Event */
#define _DBSR_DAC2W     0x00010000      /* DAC/DVC 2 Write Debug Event */
#define _DBSR_RET       0x00008000      /* Return Debug Event */

/* mask for hardware breakpoints */
#define _DBSR_HWBP_MSK  ( _DBSR_IAC1 | _DBSR_IAC2 | \
			  _DBSR_DAC1R | _DBSR_DAC1W | \
			  _DBSR_DAC2R | _DBSR_DAC2W )

#ifdef __cplusplus
}
#endif

#endif /* __INCppc85xxh */
