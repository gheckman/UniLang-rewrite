/* taskMipsLib.h - generic kernel interface header */

/*
 * Copyright (c) 1991-1993, 2001, 2003, 2007, 2009-2011
 * Wind River Systems, Inc.
 *
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
 * This file has been developed or significantly modified by the
 * MIPS Center of Excellence Dedicated Engineering Staff.
 * This notice is as per the MIPS Center of Excellence Master Partner
 * Agreement, do not remove this notice without checking first with
 * WR/Platforms MIPS Center of Excellence engineering management.
 */

/*
modification history
--------------------
01r,31may11,slk  Add extended interrupts for RMI _xlp variant
01q,27may10,d_c  Rename CAVIUM_CNMIPS_* to _WRS_CAVIUM_CNMIPS_* and define in
                 arch Makefile
01p,31mar10,d_c  Add cav_cn5xxx and cav_cn6xxx variants
01o,01may09,slk  add flag to TCB to identify task context saved TCB
01n,26sep07,d_c  Add extended interrupts for RMI _xlr variant
01m,10aug07,rlg  MIPS library restructure changes
01l,29jul07,pes  Addition of more registers for Cavium save/restore
01k,11sep03,jmt  Modify Exception Stack for Base 6
01j,22aug03,jmt  Add MMU Support
01i,16jul01,ros  add CofE comment
01h,18oct93,cd   added R4000 support.
01g,02apr93,caf  prototyped taskSRInit().
01f,22sep92,rrr  added support for c++
01e,03jun92,ajm  updated file name references to match real name
01d,26may92,rrr  the tree shuffle
01c,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed copyright notice
01b,28may91,ajm  reordered WIND_TCB_REGS order due to REG_SET change
01a,01may91,ajm  split/derived from 68k version 01k.
*/

#ifndef __INCtaskMipsLibh
#define __INCtaskMipsLibh

#include <arch/mips/archMips.h>

#ifdef __cplusplus
extern "C" {
#endif

#define WIND_TCB_GREG_BASE	(WIND_TCB_REGS+2*4+2*_RTypeSize)
#define WIND_TCB_GREG_OFFSET(n) (WIND_TCB_GREG_BASE + (n)*_RTypeSize)
#define	WIND_TCB_SR 		(WIND_TCB_REGS + 0*4)
#define	WIND_TCB_PC 		(WIND_TCB_REGS + 1*4)
#define	WIND_TCB_LO		(WIND_TCB_REGS + 2*4+0*_RTypeSize)
#define	WIND_TCB_HI		(WIND_TCB_REGS + 2*4+1*_RTypeSize)
#define	WIND_TCB_ZERO		WIND_TCB_GREG_OFFSET(0)
#define	WIND_TCB_AT		WIND_TCB_GREG_OFFSET(1)
#define	WIND_TCB_V0		WIND_TCB_GREG_OFFSET(2)
#define	WIND_TCB_V1		WIND_TCB_GREG_OFFSET(3)
#define	WIND_TCB_A0		WIND_TCB_GREG_OFFSET(4)
#define	WIND_TCB_A1		WIND_TCB_GREG_OFFSET(5)
#define	WIND_TCB_A2		WIND_TCB_GREG_OFFSET(6)
#define	WIND_TCB_A3		WIND_TCB_GREG_OFFSET(7)
#define	WIND_TCB_T0		WIND_TCB_GREG_OFFSET(8)
#define	WIND_TCB_T1		WIND_TCB_GREG_OFFSET(9)
#define	WIND_TCB_T2		WIND_TCB_GREG_OFFSET(10)
#define	WIND_TCB_T3		WIND_TCB_GREG_OFFSET(11)
#define	WIND_TCB_T4		WIND_TCB_GREG_OFFSET(12)
#define	WIND_TCB_T5		WIND_TCB_GREG_OFFSET(13)
#define	WIND_TCB_T6		WIND_TCB_GREG_OFFSET(14)
#define	WIND_TCB_T7		WIND_TCB_GREG_OFFSET(15)
#define	WIND_TCB_S0		WIND_TCB_GREG_OFFSET(16)
#define	WIND_TCB_S1		WIND_TCB_GREG_OFFSET(17)
#define	WIND_TCB_S2		WIND_TCB_GREG_OFFSET(18)
#define	WIND_TCB_S3		WIND_TCB_GREG_OFFSET(19)
#define	WIND_TCB_S4		WIND_TCB_GREG_OFFSET(20)
#define	WIND_TCB_S5		WIND_TCB_GREG_OFFSET(21)
#define	WIND_TCB_S6		WIND_TCB_GREG_OFFSET(22)
#define	WIND_TCB_S7		WIND_TCB_GREG_OFFSET(23)
#define	WIND_TCB_T8		WIND_TCB_GREG_OFFSET(24)
#define	WIND_TCB_T9		WIND_TCB_GREG_OFFSET(25)
#define	WIND_TCB_K0		WIND_TCB_GREG_OFFSET(26)
#define	WIND_TCB_K1		WIND_TCB_GREG_OFFSET(27)
#define	WIND_TCB_GP		WIND_TCB_GREG_OFFSET(28)
#define	WIND_TCB_SP		WIND_TCB_GREG_OFFSET(29)
#define	WIND_TCB_S8		WIND_TCB_GREG_OFFSET(30)
#define	WIND_TCB_RA		WIND_TCB_GREG_OFFSET(31)
#define WIND_TCB_GREG_END	(WIND_TCB_GREG_BASE+32*_RTypeSize)
#define WIND_TCB_WDB_CAUSE      (WIND_TCB_GREG_END + 0*4)
#define WIND_TCB_WDB_FPCSR      (WIND_TCB_GREG_END + 1*4)
#define WIND_TCB_INTCTRL        (WIND_TCB_GREG_END + 2*4)
#define WIND_TCB_EXTRA1         (WIND_TCB_GREG_END + 3*4)
#define WIND_TCB_TLBHI          (WIND_TCB_GREG_END + 4*4 + 0*_RTypeSize)
#define WIND_TCB_EXTRA2         (WIND_TCB_GREG_END + 4*4 + 1*_RTypeSize)
#define WIND_TCB_EXTRA3         (WIND_TCB_GREG_END + 4*4 + 2*_RTypeSize)
#define WIND_TCB_EXTRA4         (WIND_TCB_GREG_END + 4*4 + 3*_RTypeSize)
#define WIND_TCB_EXTRA5         (WIND_TCB_GREG_END + 4*4 + 4*_RTypeSize)
#define WIND_TCB_EXTRA6         (WIND_TCB_GREG_END + 4*4 + 5*_RTypeSize)
#define WIND_TCB_EXTRA7         (WIND_TCB_GREG_END + 4*4 + 6*_RTypeSize)
#define WIND_TCB_EXTRA8         (WIND_TCB_GREG_END + 4*4 + 7*_RTypeSize)
#define WIND_TCB_EXTRA9         (WIND_TCB_GREG_END + 4*4 + 8*_RTypeSize)
#define WIND_TCB_EXTRA10        (WIND_TCB_GREG_END + 4*4 + 9*_RTypeSize)

/* flag to identify TCB context was saved from task mode */
#define WIND_TCB_TASK_CONTEXT	WIND_TCB_EXTRA1

#if defined(_WRS_CAVIUM_CNMIPS_CORE) || defined(_WRS_CAVIUM_CNMIPS_II_CORE)
#define WIND_TCB_P0		WIND_TCB_EXTRA3
#define WIND_TCB_P1		WIND_TCB_EXTRA4
#define WIND_TCB_P2		WIND_TCB_EXTRA5
#define WIND_TCB_MPL0		WIND_TCB_EXTRA6
#define WIND_TCB_MPL1		WIND_TCB_EXTRA7
#define WIND_TCB_MPL2		WIND_TCB_EXTRA8
#define WIND_TCB_TLO		WIND_TCB_EXTRA9
#define WIND_TCB_THI		WIND_TCB_EXTRA10
#endif /* defined(_WRS_CAVIUM_CNMIPS_CORE) || defined(_WRS_CAVIUM_CNMIPS_II_CORE) */

#if defined(MIPSXX_xlr) || defined(MIPSXX_xlp)
#define WIND_TCB_EIMR           WIND_TCB_EXTRA3
#endif  /* defined(MIPSXX_xlr) || defined(MIPSXX_xlp) */

#ifndef	_ASMLANGUAGE
#if	defined(__STDC__) || defined(__cplusplus)

extern ULONG taskSRInit (ULONG newValue);
#if defined(MIPSXX_xlr) || defined(MIPSXX_xlp)
extern UINT64 taskExtendedIntInit (UINT64 newValue);
#endif  /* defined(MIPSXX_xlr) || defined(MIPSXX_xlp) */

#else	/* __STDC__ */

extern ULONG taskSRInit ();
#if defined(MIPSXX_xlr) || defined(MIPSXX_xlp)
extern UINT64 taskExtendedIntInit ();
#endif  /* defined(MIPSXX_xlr) || defined(MIPSXX_xlp) */

#endif	/* __STDC__ */
#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCtaskMipsLibh */
