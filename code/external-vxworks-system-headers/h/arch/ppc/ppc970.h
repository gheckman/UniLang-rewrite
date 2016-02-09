/* ppc970.h - PowerPC 970 specific header */

/*
 * Copyright (c) 2003-2008, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01z,27mar12,cww  Added dsisr bits 1 and 4
01y,29aug08,pch  add _PPC_HID0_BIT_NAP
01x,23apr08,to   define _WRS_PPC_STMW_SLOW
01w,16jul07,pch  CQ86377: re-enable MSR[FP] for syscall handler if enabled in
		 caller
01v,29jun07,pch  CQ96747: add RI to _PPC_MSR_MMU_EXTRACT macro
01u,29sep06,lei  added INT_UNMASK
01t,01jun06,pch  consolidate vector offset definitions in excPpcLib.h
01s,06oct05,pch  add cache and SCOM definitions
01r,24feb05,pch  Add _WRS_WDB_CPU_TYPE
		 Replace PPC970_64 placeholder with _WRS_OS_64BIT
01q,17nov04,to   PPC970 does not implement mcrxr instruction.
01p,25jun04,to   add _CPU_CACHE_ALIGN_SHIFT.
01o,04jun04,to   define _WRS_FP_CLASS_HW. define RFI only for _ASMLANGUAGE.
01n,28may04,to   define _WRS_ALTIVEC_SUPPORT. remove tmp rfid def.
01m,26apr04,to   define _WRS_PPC_OEA, _WRS_PPC_64BIT macros.
01l,22apr04,to   define _WRS_PPC_HAS_HV_MODE.
01k,08mar04,to   define _WRS_MMU_NO_BAT.
01j,05mar04,to   use _WRS_MMU_64BIT for 64-bit MMU implementations. fix typos.
01i,04mar04,rec  add 64 bit SR1 and PTE
01h,01mar04,rec  fix HID5 address
01g,20feb04,to   define RFI and RFI_OPCODE
01f,19feb04,to   remove LL from constants for assembly code.
01e,19feb04,to   tmp rfid def
01d,17feb04,to   misc changes.
01c,12feb04,to   remove underscore from const.
01b,12feb04,rec  review comments
01a,23dec03,rec  written. based on ppc604.h v01n
*/

#ifndef __INCppc970h
#define __INCppc970h

#ifdef __cplusplus
extern "C" {
#endif

#ifdef	_ASMLANGUAGE
#undef	RFI
#define	RFI			rfid
#endif	/* _ASMLANGUAGE */

#undef	RFI_OPCODE
#define	RFI_OPCODE		0x4c000024

/*
 * Set _WRS_OS_64BIT only if building a full 64-bit OS.
 * This is not currently supported.
 */
#ifdef	_WRS_OS_64BIT
#undef	_PPC_REG_SIZE
#define	_PPC_REG_SIZE		8
#endif	/* _WRS_OS_64BIT */

/* 970 conforms to the PowerPC OEA */
#define	_WRS_PPC_OEA

/* 970 is a 64-bit PowerPC implementation */
#define	_WRS_PPC_64BIT

/* 970 implements hypervisor mode */
#define	_WRS_PPC_HAS_HV_MODE

/* 970 implements PowerPC MMU specs for 64-bit implementations */
#define	_WRS_MMU_64BIT

/* 970 does not implement BAT */
#define	_WRS_MMU_NO_BAT

/* MMU supports TLB miss with hardware (not SRR0/SRR1) see 970 UM 5.2.1 */
#undef	_WRS_TLB_MISS_CLASS_SW
#define	_WRS_TLB_MISS_CLASS_HW	1

/* MMU uses SR registers to establish contexts */
#undef	_WRS_MMU_CLASS_PID_REG
#define	_WRS_MMU_CLASS_SR_REGS	1
#undef	_WRS_MMU_CLASS_NONE

/* 970 implements FPU */
#undef	_WRS_FP_CLASS_SW
#define	_WRS_FP_CLASS_HW	1

/* 970 does not implement mcrxr instruction */
#define	_WRS_PPC_NO_MCRXR

/* 970 take an alignment exception if the EA of lmw/stmw is uncached */
#define	_WRS_PPC_STMW_SLOW

/* 970 reports itself to WDB as CPU==PPC32, not as CPU==PPC970 */
#define	_WRS_WDB_CPU_TYPE	PPC32

/*
 * This is essentially a compiler switch to remove/add altivec support
 * in the target src. The BSP code is controlled using INCLUDE_ALTIVEC
 * in config.h
 */
#define _WRS_ALTIVEC_SUPPORT 1


#define	_CPU_CACHE_ALIGN_SHIFT	7	/* cache line size = 128 */
#define	_CPU_CACHE_ALIGN_SIZE	128	/* cache line size */

#define ICACHE_SIZE 64 * 1024
#define ICACHE_WAYS 1
#define DCACHE_SIZE 32 * 1024
#define DCACHE_WAYS 2
#define L2CACHE_SIZE 512 * 1024
#define L2CACHE_WAYS 8
#define	BLOCK_SIZE_4MB	0x400000

#undef  SPRG4
#undef  SPRG5

#define SCOMC	276	/* Scan Communications Facility */
#define SCOMD	277	/* Scan Communications Facility */

#define PVR	287	/* processor version register */

/* LPAR registers */
#define HSPRG0	304	/* Hypervisor SPRG 0 Register */
#define HSPRG1	305	/* Hypervisor SPRG 1 Register */
#define HDEC	310	/* Hypervisor Decrementer Interrupt Register */
#define HIOR	311	/* Hypervisor Interrupt Offset Register */
#define HSSR0	314	/* Hypervisor Save/Restore Register 1 */
#define HSSR1	315	/* Hypervisor Save/Restore Register 2 */

/* Performance Monitor Registers */
#define UPMC1	771	/* Performance Counter 1 */
#define UPMC2	772	/* Performance Counter 2 */
#define UPMC3	773	/* Performance Counter 3 */
#define UPMC4	774	/* Performance Counter 4 */
#define UPMC5	775	/* Performance Counter 5 */
#define UPMC6	776	/* Performance Counter 6 */
#define UPMC7	777	/* Performance Counter 7 */
#define UPMC8	778	/* Performance Counter 8 */

#define UMMCR0	779	/* Monitor Control Register 0 */
#define UMMCR1	782	/* Monitor Control Register 1 */
#define UMMCRA	770	/* Monitor Control Register A */

#define USIAR	780	/* Sampled Instruction Address Register */
#define USDAR	781	/* Sampled Data Address Register */



#define IMC	783	/* IMC Array Address */
#define UIMC	799	/* User IMC Array Address */

#define MMCR0	795	/* Monitor Mode Control Register 0 */
#define MMCR1	798	/* Monitor Mode Control Register 1 */
#define MMCRA	786	/* Monitor Mode Control Register  */

#define PMC1	787	/* Performance Monitor Counter Register 1 */
#define PMC2	788	/* Performance Monitor Counter Register 2 */
#define PMC3	789	/* Performance Monitor Counter Register 3 */
#define PMC4	790	/* Performance Monitor Counter Register 4 */
#define PMC5	791	/* Performance Monitor Counter Register 5 */
#define PMC6	792	/* Performance Monitor Counter Register 6 */
#define PMC7	793	/* Performance Monitor Counter Register 7 */
#define PMC8	794	/* Performance Monitor Counter Register 8 */


#define SIA	796	/* Sampled Instruction Address Register */
#define SDA	797	/* Sampled Data Address Register */

#define TRIG0	976	/* Trigger 0 Register */
#define TRIG1	977	/* Trigger 1 Register */
#define TRIG2	978	/* Trigger 2 Register */


#define HID0	1008	/* hardware implementation register 0 */
#define HID1	1009	/* hardware implementation register 1 */
#define HID4	1012	/* hardware implementation register 4 */
#define HID5	1014	/* hardware implementation register 5 */

#define DABR	1013	/* Data Address Breakpoint Register */
#define DABRX	1015	/* Data Address Breakpoint Register */

#define PIR	1023	/* Processor Identification Register */


#ifdef _ASMLANGUAGE
#define _LL(a)        a
/* XXX - temporary assists */
#define	mfscomc(x)	mfspr	x, SCOMC
#define	mfscomd(x)	mfspr	x, SCOMD
#define	mtscomc		mtspr	SCOMC,
#define	mtscomd		mtspr	SCOMD,
#else
#define _LL(a)        a##LL
#endif

/* SCOM definitions */

#define	SCOM_ADDR_PSR_READ		0x4080
#define	SCOM_ADDR_STS_MODE		0x0430
#define	SCOM_DATA_STS_MODE_L2_DIRECT	0x8000


/* HID0 bit definitions */

#define	_PPC_HID0_BIT_NAP	9	/* HID0 nap bit */

#define	_PPC_HID0_ONEPPC    _LL(0x8000000000000000) /* One instruction per dispatch */
#define	_PPC_HID0_DOSINGLE  _LL(0x4000000000000000) /* complete instruction then flush */
#define	_PPC_HID0_IOSYNC_SC _LL(0x2000000000000000) /* disable iosync scoreboard */
#define	_PPC_HID0_SER_GP    _LL(0x1000000000000000) /* Serialize group dispatch */
#define	_PPC_HID0_DEEPNAP   _LL(0x0100000000000000) /* deep nap */
#define	_PPC_HID0_NAP       _LL(0x0040000000000000) /* nap */
#define	_PPC_HID0_DPM       _LL(0x0010000000000000) /* dynamic power management */
#define	_PPC_HID0_TG        _LL(0x0004000000000000) /* Performance monitor threshold granularity */
#define	_PPC_HID0_HANG_DIS  _LL(0x0002000000000000) /* disable hang detection */
#define	_PPC_HID0_NHR       _LL(0x0001000000000000) /* not hard reset */
#define	_PPC_HID0_INORDER   _LL(0x0000800000000000) /* next group not issued until current done */
#define	_PPC_HID0_TB_CTRL   _LL(0x0000200000000000) /* time base counts when core stopped */
#define	_PPC_HID0_EXT_TBEN  _LL(0x0000100000000000) /* use external clock */
#define	_PPC_HID0_CIABR_EN  _LL(0x0000020000000000) /* enable completion instruction ABR */
#define	_PPC_HID0_HDEC_EN   _LL(0x0000010000000000) /* hypervisor decrementer enable */
#define	_PPC_HID0_EBPTHERM  _LL(0x0000008000000000) /* enable thermal interrupt */
#define	_PPC_HID0_EN_ATTN   _LL(0x0000000100000000) /* enable support processor ATTN inst */
#define	_PPC_HID0_EN_MCK    _LL(0x0000000080000000) /* enable machine check interrupts */

/* HID1 bit definitions */

#define	_PPC_HID1_BIT_EN_IC	5	/* HID1 enable I-cache bit */
#define	_PPC_HID1_BIT_PF0	7	/* HID1 prefetch field bit 7 */
#define	_PPC_HID1_BIT_PF1	8	/* HID1 prefetch field bit 8 */
#define	_PPC_HID1_BIT_EN_ICBI	9	/* HID1 enable icbi forced match */
#define	_PPC_HID1_BIT_EN_IFCACH	10	/* HID1 enable I-fetch cacheability */

#define	_PPC_HID1_BHT_STAT  _LL(0x0000000000000000) /* static bht prediction */
#define	_PPC_HID1_BHT_GLOB  _LL(0x4000000000000000) /* global bht prediction */
#define	_PPC_HID1_BHT_LOCAL _LL(0x8000000000000000) /* local bht prediction */
#define	_PPC_HID1_BHT_FULL  _LL(0xC000000000000000) /* full loc/glob bht prediction */
#define	_PPC_HID1_BHT_HIST  _LL(0x6000000000000000) /* global bht prediction with history */
#define	_PPC_HID1_BHT_GSEL  _LL(0xE000000000000000) /* FULL with gsel bht prediction */
#define	_PPC_HID1_EN_LS     _LL(0x1000000000000000) /* enable link stack */
#define	_PPC_HID1_EN_CC     _LL(0x0800000000000000) /* enable count cache */
#define	_PPC_HID1_EN_IC     _LL(0x0400000000000000) /* enable instruction cache */
#define	_PPC_HID1_PF_NONE   _LL(0x0000000000000000) /* no instruction prefetch */
#define	_PPC_HID1_PF_NSA    _LL(0x0080000000000000) /* next sequential instruction prefetch */
#define	_PPC_HID1_PF_DNSA   _LL(0x0100000000000000) /* next two sequential instruction prefetch */
#define	_PPC_HID1_PF_DIS    _LL(0x0180000000000000) /* disable instruction prefetch */
#define	_PPC_HID1_EN_ICBI   _LL(0x0040000000000000) /* enable forced icbi match mode */
#define	_PPC_HID1_EN_IFCACH _LL(0x0020000000000000) /* ifetch controlled by ibit */
#define	_PPC_HID1_EN_ICREC  _LL(0x0010000000000000) /* enable icache parity error recovery */
#define	_PPC_HID1_EN_IDREC  _LL(0x0008000000000000) /* enable i-directory parity error recovery */
#define	_PPC_HID1_EN_ERREC  _LL(0x0004000000000000) /* enable I-ERAT parity error recovery */
#define	_PPC_HID1_IC_PE     _LL(0x0002000000000000) /* instruction cache parity error inject */
#define	_PPC_HID1_ICD0_PE   _LL(0x0001000000000000) /* i-directory 0 cache parity error inject */
#define	_PPC_HID1_IER_PE    _LL(0x0000400000000000) /* I-ERAT parity error inject */
#define	_PPC_HID1_EN_SPITW  _LL(0x0000200000000000) /* enable speculative table walks */
#define	_PPC_HID1_SUPERCHIX _LL(0x0000100000000000) /* super chicken safe mode */

/* HID4 bit definitions */

#define	_PPC_HID4_BIT_RM_CI	23	/* HID4 real mode cache-inhibited bit */
#define	_PPC_HID4_BIT_DIS_PREF	25	/* HID4 disable data prefetch bit */
#define	_PPC_HID4_BIT_L1DC_FLSH	28	/* HID4 L1 data cache flash invalidate bit */

#define	_PPC_HID4_RMOR_MSK  _LL(0x01FFFE0000000000) /* real mode offset register mask */
#define	_PPC_HID4_RM_CI     _LL(0x0000010000000000) /* real mode access cache inhibited */
#define	_PPC_HID4_FORCE_AI  _LL(0x0000008000000000) /* data access real mode cache inh */
#define	_PPC_HID4_DIS_PREF  _LL(0x0000004000000000) /* disable data prefetch */
#define	_PPC_HID4_RES_PREF  _LL(0x0000002000000000) /* reset data prefetch */
#define	_PPC_HID4_EN_SP_DTW _LL(0x0000001000000000) /* enable speculative table walk */
#define	_PPC_HID4_L1DC_FLSH _LL(0x0000000800000000) /* L1 data cache flash invalidate */
#define	_PPC_HID4_DISDERPC0 _LL(0x0000000400000000) /* disable D-ERAT parity checking set 0 */
#define	_PPC_HID4_DISDERPC1 _LL(0x0000000200000000) /* disable D-ERAT parity checking set 1 */
#define	_PPC_HID4_DIS_DERPG _LL(0x0000000100000000) /* disable D-ERAT parity generation */
#define	_PPC_HID4_DISDERAT0 _LL(0x0000000080000000) /* disable D-ERAT set 0 */
#define	_PPC_HID4_DISDERAT1 _LL(0x0000000040000000) /* disable D-ERAT set 1 */
#define	_PPC_HID4_DISDCTPC0 _LL(0x0000000020000000) /* disable cache tag parity checking set 0 */
#define	_PPC_HID4_DISDCTPC1 _LL(0x0000000010000000) /* disable cache tag parity checking set 1 */
#define	_PPC_HID4_DIS_DCTPG _LL(0x0000000008000000) /* disable cache tag parity generation */
#define	_PPC_HID4_DISDCSET0 _LL(0x0000000004000000) /* disable data cache set 0 */
#define	_PPC_HID4_DISDCSET1 _LL(0x0000000002000000) /* disable data cache set 1 */
#define	_PPC_HID4_DIS_DCPC0 _LL(0x0000000001000000) /* disable data cache parity checking set 0 */
#define	_PPC_HID4_DIS_DCPC1 _LL(0x0000000000800000) /* disable data cache parity checking set 1 */
#define	_PPC_HID4_DIS_DCPG  _LL(0x0000000000400000) /* disable data cache parity generation */
#define	_PPC_HID4DISDCRTPC0 _LL(0x0000000000200000) /* disable data cache real addr tag parity 0 */
#define	_PPC_HID4DISDCRTPC1 _LL(0x0000000000100000) /* disable data cache real addr tag parity 1 */
#define	_PPC_HID4DISTLBCHK0 _LL(0x0000000000080000) /* disable TLB parity checking set 0 */
#define	_PPC_HID4DISTLBCHK1 _LL(0x0000000000040000) /* disable TLB parity checking set 1 */
#define	_PPC_HID4DISTLBCHK2 _LL(0x0000000000020000) /* disable TLB parity checking set 2 */
#define	_PPC_HID4DISTLBCHK3 _LL(0x0000000000010000) /* disable TLB parity checking set 3 */
#define	_PPC_HID4_DIS_TLBPG _LL(0x0000000000008000) /* disable TLB parity generation */
#define	_PPC_HID4DISTLBSET0 _LL(0x0000000000004000) /* disable TLB set 0 */
#define	_PPC_HID4DISTLBSET1 _LL(0x0000000000002000) /* disable TLB set 1 */
#define	_PPC_HID4DISTLBSET2 _LL(0x0000000000001000) /* disable TLB set 2 */
#define	_PPC_HID4DISTLBSET3 _LL(0x0000000000000800) /* disable TLB set 3 */
#define	_PPC_HID4_DIS_SLBPC _LL(0x0000000000000400) /* disable SLB parity checking */
#define	_PPC_HID4_DIS_SLBPG _LL(0x0000000000000200) /* disable SLB parity generation */
#define	_PPC_HID4_MCK_INJ   _LL(0x0000000000000100) /* machine check injection enable */
#define	_PPC_HID4_DIS_STFWD _LL(0x0000000000000080) /* disable store forwarding */
#define	_PPC_HID4_LPES0     _LL(0x0000000000000000) /* LPES=0 V2.00 PPC environment */
#define	_PPC_HID4_LPES1     _LL(0x1000000000000000) /* LPES=1 V2.00 PPC environment */
#define	_PPC_HID4_LPES_NEW  _LL(0x1000000000000040) /* environment is new */
#define	_PPC_HID4_RMLR_16G  _LL(0x2000000000000000) /* real mode limit register 16 GB */
#define	_PPC_HID4_RMLR_1G   _LL(0x4000000000000000) /* real mode limit register 1 GB */
#define	_PPC_HID4_RMLR_64M  _LL(0x6000000000000000) /* real mode limit register 64 MB */
#define	_PPC_HID4_RMLR256M  _LL(0x0000000000000010) /* real mode limit register 256 MB */
#define	_PPC_HID4_RMLR128M  _LL(0x6000000000000010) /* real mode limit register 128 MB */
#define	_PPC_HID4_DISSPLARX _LL(0x0000000000000008) /* disable speculative lwarx, ldarx */
#define	_PPC_HID4_LG_PG_EN  _LL(0x0000000000000004) /* disable large page support */
#define	_PPC_HID4_LPID0     _LL(0x0000000000000002) /* LPID 0 */
#define	_PPC_HID4_LPID1     _LL(0x0000000000000001) /* LPID 1 */
#define	_PPC_HID4_LPID2     _LL(0x1000000000000000) /* LPID 2 */
#define	_PPC_HID4_LPID3     _LL(0x0800000000000000) /* LPID 3 */
#define	_PPC_HID4_LPID4     _LL(0x0400000000000000) /* LPID 4 */
#define	_PPC_HID4_LPID5     _LL(0x0200000000000000) /* LPID 5 */


/* HID5 bit definitions */

#define	_PPC_HID5_HRMOR     _LL(0x00000000FFFF0000) /* mask for real mode offset register */
#define	_PPC_HID5_DC_MCK    _LL(0x0000000000002000) /* machine check enable for tag parity err */
#define	_PPC_HID5_DISPWRSAV _LL(0x0000000000001000) /* disable power savings */
#define	_PPC_HID5_FORCE_G   _LL(0x0000000000000800) /* force guarded load */
#define	_PPC_HID5_DC_REPL   _LL(0x0000000000000400) /* data cache replacement (1=FIFO) */
#define	_PPC_HID5_HWR_STMS  _LL(0x0000000000000200) /* number of HW prefetch streams 1:8, 0:4 */
#define	_PPC_HID5_DST_NOP   _LL(0x0000000000000100) /* DST no-op'ed */
#define	_PPC_HID5_DCBZ_SZ   _LL(0x0000000000000080) /* make DCB a 32 bit store */
#define	_PPC_HID5_DCBZ_ILL  _LL(0x0000000000000040) /* DCB illegal */
#define	_PPC_HID5_TLB_MAP   _LL(0x0000000000000020) /* TLB mapping 0:4-way, 1:direct */
#define	_PPC_HID5_LMQ_PORT  _LL(0x0000000000000010) /* demand miss (LMQ to STS) */
#define	_PPC_HID5_LMQ_SIZE0 _LL(0x0000000000000008) /* Number of outstanding requests bit 0 */
#define	_PPC_HID5_DPFLOOD   _LL(0x0000000000000004) /* data prefetch flood mode */
#define	_PPC_HID5_TCH_NOP   _LL(0x0000000000000002) /* make tcbt and dcbtst act like nop */
#define	_PPC_HID5_LMQ_SIZE1 _LL(0x0000000000000001) /* Number of outstanding requests bit 1 */



/* for 64-bit implementations, registers bit positions are found in the high word */
#ifdef	_WRS_OS_64BIT
#define MODE_OFFS 32		/* 64-bit mode bit offset */
#else	/* _WRS_OS_64BIT */
#define MODE_OFFS 0		/* 32-bit mode bit offset */
#endif	/* _WRS_OS_64BIT */

/* MSR bit definitions */

#undef _PPC_MSR_BIT_EE
#undef _PPC_MSR_BIT_PR
#undef _PPC_MSR_BIT_ME
#undef _PPC_MSR_BIT_LE

#ifdef	_WRS_OS_64BIT
#define _PPC_MSR_BIT_SF  0		/* MSR Sixty-Four bit mode */
#define _PPC_MSR_BIT_ISF 2		/* MSR Exception Sixty-Four bit mode */
#endif	/* _WRS_OS_64BIT */

#define _PPC_MSR_BIT_POW (13+MODE_OFFS)	/* MSR Power Management bit - POW */
#define _PPC_MSR_BIT_EE  (16+MODE_OFFS)	/* MSR Ext. Intr. Enable bit - EE */
#define _PPC_MSR_BIT_PR  (17+MODE_OFFS)	/* MSR Privilege Level bit - PR */
#define _PPC_MSR_BIT_FP  (18+MODE_OFFS)	/* MSR Floating Point Avail. bit - FP */
#define _PPC_MSR_BIT_ME  (19+MODE_OFFS)	/* MSR Machine Check Enable bit - ME */
#define _PPC_MSR_BIT_FE0 (20+MODE_OFFS)	/* MSR FP exception mode 0 bit - FE0 */
#define _PPC_MSR_BIT_SE  (21+MODE_OFFS)	/* MSR Single Step Trace bit - SE */
#define _PPC_MSR_BIT_BE  (22+MODE_OFFS)	/* MSR Branch Trace Enable bit - BE */
#define _PPC_MSR_BIT_FE1 (23+MODE_OFFS)	/* MSR FP exception mode 1 bit - FE1 */
#define _PPC_MSR_BIT_IP  (25+MODE_OFFS)	/* MSR Exception Prefix bit - EP */
#define _PPC_MSR_BIT_IR  (26+MODE_OFFS)	/* MSR Inst Translation bit - IR */
#define _PPC_MSR_BIT_DR  (27+MODE_OFFS)	/* MSR Data Translation bit - DR */
#define _PPC_MSR_BIT_RI  (30+MODE_OFFS)	/* MSR Exception Recoverable bit - RI */

#ifdef _WRS_ALTIVEC_SUPPORT
#define _PPC_MSR_VEC		0x0200	/* Bit 6 of MSR */
#define _PPC_MSR_BIT_VEC  (6+MODE_OFFS)	/* MSR Altivec Available bit - VEC */
#endif


/* MSR MMU/RI Bit extraction */

#define _PPC_MSR_MMU_RI_EXTRACT(src, dst) \
	li	dst, _PPC_MSR_IR | _PPC_MSR_DR | _PPC_MSR_RI ; \
	and	dst, dst, src

#define _PPC_MSR_MMU_RI_FP_EXTRACT(src, dst) \
	li	dst, _PPC_MSR_IR | _PPC_MSR_DR | _PPC_MSR_RI | _PPC_MSR_FP ; \
	and	dst, dst, src

/*
 * IABR bit definitions
 *
 * The 970's IABR is accessible only via JTAG or the "support processor".
 */

/* set and get address in IABR */

#ifdef	_WRS_OS_64BIT
#define	_PPC_IABR_ADD(x)	((x) & _LL(0xFFFFFFFFFFFFFFFC))
#else	/* _WRS_OS_64BIT */
#define	_PPC_IABR_ADD(x)	((x) & 0xFFFFFFFC)
#endif	/* _WRS_OS_64BIT */

#define	_PPC_IABR_BE		0x00000002	/* breakpoint enabled */
#define	_PPC_IABR_TE		0x00000001	/* translation enabled */

/* DABR and DABRX bits definition */

/* set and get address in DABR/DBRX */

#ifdef	_WRS_OS_64BIT
#define	_PPC_DABR_DAB(x)	((x) & _LL(0xFFFFFFFFFFFFFFF8))
#else	/* _WRS_OS_64BIT */
#define	_PPC_DABR_DAB(x)	((x) & 0xFFFFFFF8)
#endif	/* _WRS_OS_64BIT */

#define	_PPC_DABR_BT		0x00000004	/* breakpoint translation */
#define	_PPC_DABR_DW		0x00000002	/* data write enable */
#define	_PPC_DABR_DR		0x00000001	/* data read enable */

/* mask for read and write operations */

#define	_PPC_DABR_D_MSK		(_PPC_DABR_DW | _PPC_DABR_DR)

/* DSISR bits definition */

#define _PPC_DSISR_TRANS	0x40000000	/* translation no found */
#define _PPC_DSISR_ACCESS	0x08000000	/* access not permitted */
#define	_PPC_DSISR_BRK		0x00400000	/* DABR match occurs */

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

#endif /* __INCppc970h */
