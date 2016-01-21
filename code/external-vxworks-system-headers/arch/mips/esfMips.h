/* esfMips.h - exception stack frame for MIPS architecture */

/*
 * Copyright (c) 1990-1993, 1996, 2001, 2003-2004,
 *		 2007, 2010-2011 Wind River Systems, Inc.
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
01v,31may11,slk  Add extended interrupts for RMI _xlp variant
01u,27may10,d_c  Rename CAVIUM_CNMIPS_* to _WRS_CAVIUM_CNMIPS_* and define in
                 arch Makefile
01t,29apr10,pad  Moved extern C statement after include statements.
01t,31mar10,d_c  Add cav_cn5xxx and cav_cn6xxx variants
01s,26sep07,d_c  Add extended interrupts for RMI _xlr variant
01r,10aug07,rlg  MIPS library restructure changes
01q,29jul07,pes  Addition of more registers for Cavium save/restore
01p,14jul04,agf  Replace _pad with previousEsf ptr
01o,11sep03,jmt  Modify Exception Stack for Base 6
01n,26aug03,jmt  Add TLBHI registers to E_STK
01m,16jul01,ros  add CofE comment
01l,12feb96,mem  Added cause and fpscr to REG_SET.
0ik,22oct93,cd   added R4000 support, added 64bit support.
01j,22sep92,rrr  added support for c++
01i,19jul92,rrr  changed ESFR3K member errno to _errno so it would compile
01h,03jun92,ajm  updated file name referenced to match real name
01g,26may92,rrr  the tree shuffle
		  -changed includes to have absolute path from h/
01f,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed ASMLANGUAGE to _ASMLANGUAGE
		  -changed copyright notice
01e,27may91,ajm  reordered ESF to model REG_SET
01d,19sep90,ajm  merged in space for fpcsr
01c,08may90,ajm  added stack space for call with up to four parameters
01b,16apr90,ajm  moved epc and sp to top of stack for use by
		  windALib.s
01a,13apr90,ajm  written
*/

#ifndef __INCesfMipsh
#define __INCesfMipsh

#include <arch/mips/regsMips.h>
#include <arch/mips/archMips.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
*  Exception stack frame.  Since done in common software routine,
*  there exists merely one frame.  Notice the coordination of
*  stack frame definitions for assembler routines, and the
*  order of the structure ESFMIPS!!!
*
*/

/* ESFMIPS - all inclusive stack frame */

#ifndef	_ASMLANGUAGE

typedef struct
    {
    ULONG param1;		/* space for param 1 */
    ULONG param2;		/* space for param 2 */
    ULONG param3;		/* space for param 3 */
    ULONG param4;		/* space for param 3 */
    ULONG _errno;		/* errno */
    ULONG cause;		/* cause register */
    ULONG cntxt;		/* context reg */
    ULONG fpcsr;		/* float status register */
    ULONG badva;		/* bad virtual address reg */
    ULONG * previousEsf;	/* pointer to nested ESF */
    REG_SET esfRegs;		/* general register set */
    } ESFMIPS;

#endif	/* _ASMLANGUAGE */

/*
* The following list of definitions tell me where I saved state on
* the process stack.  See excALib.s
*
*/

#define E_STK_PARAM1 	(0*4)	/* saved for param 1 */
#define E_STK_PARAM2 	(1*4)	/* saved for param 2 */
#define E_STK_PARAM3 	(2*4)	/* saved for param 3 */
#define E_STK_PARAM4 	(3*4)	/* saved for param 4 */
#define E_ERRNO		(4*4)	/* errno */
#define E_STK_CAUSE 	(5*4)	/* cause register */
#define E_STK_CTX	(6*4)	/* context reg */
#define E_STK_FPCSR	(7*4)	/* float status register */
#define E_STK_BADVADDR	(8*4)	/* bad virtual address reg */
#define E_STK_PREVESF	(9*4)	/* pointer to nested stack frame */

#define E_STK_SR	(10*4)	/* status register */
#define E_STK_EPC	(11*4)	/* calculated epc */

#define E_STK_LO	(12*4+0*_RTypeSize) /* mul/div low   */
#define E_STK_HI	(12*4+1*_RTypeSize) /* mul/div hi   */
#define E_STK_GREG_BASE	(12*4+2*_RTypeSize)
#define E_STK_GREG_OFFSET(n) (E_STK_GREG_BASE + (n)*_RTypeSize)
#define E_STK_ZERO	E_STK_GREG_OFFSET(0) /* just for kicks, always zero */
#define E_STK_AT	E_STK_GREG_OFFSET(1) /* assembler temporary */
#define E_STK_V0	E_STK_GREG_OFFSET(2) /* return value 1 */
#define E_STK_V1	E_STK_GREG_OFFSET(3) /* return value 2 */
#define E_STK_A0	E_STK_GREG_OFFSET(4) /* passed parameter 1 */
#define E_STK_A1	E_STK_GREG_OFFSET(5) /* passed parameter 2 */
#define E_STK_A2	E_STK_GREG_OFFSET(6) /* passed parameter 3 */
#define E_STK_A3	E_STK_GREG_OFFSET(7) /* passed parameter 4 */
#define E_STK_T0	E_STK_GREG_OFFSET(8) /* temp reg t0 */
#define E_STK_T1	E_STK_GREG_OFFSET(9) /* temp reg t1 */
#define E_STK_T2	E_STK_GREG_OFFSET(10) /* temp reg t2 */
#define E_STK_T3	E_STK_GREG_OFFSET(11) /* temp reg t3 */
#define E_STK_T4	E_STK_GREG_OFFSET(12) /* temp reg t4 */
#define E_STK_T5	E_STK_GREG_OFFSET(13) /* temp reg t5 */
#define E_STK_T6	E_STK_GREG_OFFSET(14) /* temp reg t6 */
#define E_STK_T7	E_STK_GREG_OFFSET(15) /* temp reg t7 */
#define E_STK_S0	E_STK_GREG_OFFSET(16) /* saved reg s0 */
#define E_STK_S1	E_STK_GREG_OFFSET(17) /* saved reg s1 */
#define E_STK_S2	E_STK_GREG_OFFSET(18) /* saved reg s2 */
#define E_STK_S3	E_STK_GREG_OFFSET(19) /* saved reg s3 */
#define E_STK_S4	E_STK_GREG_OFFSET(20) /* saved reg s4 */
#define E_STK_S5	E_STK_GREG_OFFSET(21) /* saved reg s5 */
#define E_STK_S6	E_STK_GREG_OFFSET(22) /* saved reg s6 */
#define E_STK_S7	E_STK_GREG_OFFSET(23) /* saved reg s7 */
#define E_STK_T8	E_STK_GREG_OFFSET(24) /* temp reg t8 */
#define E_STK_T9	E_STK_GREG_OFFSET(25) /* temp reg t9 */
#define E_STK_K0	E_STK_GREG_OFFSET(26) /* kernel reg 0 */
#define E_STK_K1	E_STK_GREG_OFFSET(27) /* kernel reg 1, not saved */
#define E_STK_GP	E_STK_GREG_OFFSET(28) /* global pointer */
#define E_STK_SP	E_STK_GREG_OFFSET(29) /* stack pointer */
#define E_STK_FP	E_STK_GREG_OFFSET(30) /* saved reg */
#define E_STK_RA	E_STK_GREG_OFFSET(31) /* return addr reg */

#define E_STK_GREG_END  (E_STK_GREG_BASE + 32*_RTypeSize)

#define E_STK_WDB_CAUSE (E_STK_GREG_END + 0*4)
#define E_STK_WDB_FPCSR (E_STK_GREG_END + 1*4)

#define E_STK_INTCTRL	(E_STK_GREG_END + 2*4) /* Ext Intr Ctrl */
#define E_STK_ULEXTRA1	(E_STK_GREG_END + 3*4) /* extra, 4 bytes for padding */
#define E_STK_TLBHI	(E_STK_GREG_END + 4*4 + 0*_RTypeSize) /* addr space storage */
#define E_STK_RTEXTRA2	(E_STK_GREG_END + 4*4 + 1*_RTypeSize) /* extra */
#define E_STK_RTEXTRA3	(E_STK_GREG_END + 4*4 + 2*_RTypeSize) /* extra */
#define E_STK_RTEXTRA4	(E_STK_GREG_END + 4*4 + 3*_RTypeSize) /* extra */
#define E_STK_RTEXTRA5	(E_STK_GREG_END + 4*4 + 4*_RTypeSize) /* extra */
#define E_STK_RTEXTRA6	(E_STK_GREG_END + 4*4 + 5*_RTypeSize) /* extra */
#define E_STK_RTEXTRA7	(E_STK_GREG_END + 4*4 + 6*_RTypeSize) /* extra */
#define E_STK_RTEXTRA8	(E_STK_GREG_END + 4*4 + 7*_RTypeSize) /* extra */
#define E_STK_RTEXTRA9	(E_STK_GREG_END + 4*4 + 8*_RTypeSize) /* extra */
#define E_STK_RTEXTRA10	(E_STK_GREG_END + 4*4 + 9*_RTypeSize) /* extra */

#if defined(_WRS_CAVIUM_CNMIPS_CORE) || defined(_WRS_CAVIUM_CNMIPS_II_CORE)
#define E_STK_P0	E_STK_RTEXTRA3
#define E_STK_P1	E_STK_RTEXTRA4
#define E_STK_P2	E_STK_RTEXTRA5
#define E_STK_MPL0	E_STK_RTEXTRA6
#define E_STK_MPL1	E_STK_RTEXTRA7
#define E_STK_MPL2	E_STK_RTEXTRA8
#define E_STK_TLO	E_STK_RTEXTRA9
#define E_STK_THI	E_STK_RTEXTRA10
#endif /* defined(_WRS_CAVIUM_CNMIPS_CORE) || defined(_WRS_CAVIUM_CNMIPS_II_CORE) */


#if defined(_WRS_MIPS_NETLOGIC_CPU)
#define E_STK_EIMR      E_STK_RTEXTRA3
#endif  /* _WRS_MIPS_NETLOGIC_CPU */

#define	ESTKSIZE	(E_STK_GREG_END + 4*4 +10*_RTypeSize)	/* exception stack frame size */

#ifdef __cplusplus
}
#endif

#endif /* __INCesfMipsh */

