/* regsMips.h - MIPS registers */

/*
 * Copyright (c) 1991-1993, 1996-1997, 2001, 2003,
 *		2006-2007, 2010-2011 Wind River Systems, Inc.
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
01u,25may11,slk  Add extended interrupts for RMI _xlp variant
01t,27may10,d_c  Rename CAVIUM_CNMIPS_* to _WRS_CAVIUM_CNMIPS_* and define in
                 arch Makefile
01s,31mar10,d_c  Add cav_cn5xxx and cav_cn6xxx variants
01r,20sep07,d_c  Add extended interrupts for RMI _xlr variant
01q,10aug07,rlg  MIPS library restructure changes
01p,29jul07,pes  Addition of more registers for Cavium save/restore
01o,20sep06,pes  Add declaration of WIND_CPU_STATE.
01n,11sep03,jmt  Modify Register Set for Base 6
01m,22aug03,jmt  Add MMU Support
01l,16jul01,ros  add CofE comment
01k,30dec97,dbt  added common names for registers
01j,16jan96,mem  added cause and fpcsr to REG_SET.
01i,18oct93,cd   added R4000 support.
01h,22sep92,rrr  added support for c++
01g,09jul92,ajm  added defines for ASMLANGUAGE signals
01f,03jun92,ajm  updated file name references to match real name
01e,26may92,rrr  the tree shuffle
01d,12mar92,yao  added SR_OFFSET, PC_OFFSET, GREG_BASE,GREG_OFFSET.
01c,04oct91,rrr  passed through the ansification filter
		  -changed ASMLANGUAGE to _ASMLANGUAGE
		  -changed copyright notice
01b,27may91,ajm  reordered REG_SET to mirror R3KESF
01a,01apr91,ajm  derived from 01d of 68K.
*/

#ifndef __INCregsMipsh
#define __INCregsMipsh

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	_ASMLANGUAGE

typedef struct		/* REG_SET - MIPS architecture register set */
    {
    ULONG sr;			/* process status register */
    INSTR *pc;			/* program counter - really epc! */
    _RType lo;			/* divide lo register */
    _RType hi;			/* divide hi register */
    _RType gpreg[32];		/* data registers */

    /* cause & fpcsr are only set for wdb traps, from ESFMIPS */

    ULONG cause;                /* cause reg for branch bit in getNpc() */
    ULONG fpcsr;                /* fp cause reg for getNpc() */

    ULONG intCtrl;              /* extended interrupt control */
    ULONG _ULextra1;            /* extra */
    _RType tlbhi;		/* current address space storage */
    _RType _RTextra2;           /* extra */
    _RType _RTextra3;           /* extra */
    _RType _RTextra4;           /* extra */
    _RType _RTextra5;           /* extra */
    _RType _RTextra6;           /* extra */
    _RType _RTextra7;           /* extra */
    _RType _RTextra8;           /* extra */
    _RType _RTextra9;           /* extra */
    _RType _RTextra10;          /* extra */
    } REG_SET;

#if defined(_WRS_CAVIUM_CNMIPS_CORE) || defined(_WRS_CAVIUM_CNMIPS_II_CORE)
    /* use "extra" registers for the multiplier context */
#define regP0	_RTextra3
#define regP1	_RTextra4
#define regP2	_RTextra5
#define regMPL0	_RTextra6
#define regMPL1	_RTextra7
#define regMPL2	_RTextra8
#define regTlo	_RTextra9
#define regThi	_RTextra10
#endif /* defined(_WRS_CAVIUM_CNMIPS_CORE) || defined(_WRS_CAVIUM_CNMIPS_II_CORE) */

#if defined(_WRS_MIPS_NETLOGIC_CPU)
#define regEIMR	_RTextra3
#endif /* _WRS_MIPS_NETLOGIC_CPU */

/* Used to describe the register state of a cpu. May ultimately be
 * replaced by using REG_SET directly if no other elements are needed */

typedef struct wind_cpu_state
    {
    REG_SET	regs;
    } WIND_CPU_STATE;

/* some common names for registers */

#define zeroReg		gpreg[0]	/* wired zero */
#define atReg		gpreg[1]	/* assembler temp */
#define v0Reg		gpreg[2]	/* function return 0 */
#define v1Reg		gpreg[3]	/* function return 1 */
#define a0Reg		gpreg[4]	/* parameter 0 */
#define a1Reg		gpreg[5]	/* parameter 1 */
#define a2Reg		gpreg[6]	/* parameter 2 */
#define a3Reg		gpreg[7]	/* parameter 3 */
#define t0Reg		gpreg[8]	/* caller saved 0 */
#define t1Reg		gpreg[9]	/* caller saved 1 */
#define t2Reg		gpreg[10]	/* caller saved 2 */
#define t3Reg		gpreg[11]	/* caller saved 3 */
#define t4Reg		gpreg[12]	/* caller saved 4 */
#define t5Reg		gpreg[13]	/* caller saved 5 */
#define t6Reg		gpreg[14]	/* caller saved 6 */
#define t7Reg		gpreg[15]	/* caller saved 7 */
#define s0Reg		gpreg[16]	/* callee saved 0 */
#define s1Reg		gpreg[17]	/* callee saved 1 */
#define s2Reg		gpreg[18]	/* callee saved 2 */
#define s3Reg		gpreg[19]	/* callee saved 3 */
#define s4Reg		gpreg[20]	/* callee saved 4 */
#define s5Reg		gpreg[21]	/* callee saved 5 */
#define s6Reg		gpreg[22]	/* callee saved 6 */
#define s7Reg		gpreg[23]	/* callee saved 7 */
#define t8Reg		gpreg[24]	/* caller saved 8 */
#define t9Reg		gpreg[25]	/* caller saved 8 */
#define k0Reg		gpreg[26]	/* kernal reserved 0 */
#define k1Reg		gpreg[27]	/* kernal reserved 1 */
#define gpReg		gpreg[28]	/* global pointer */
#define spReg		gpreg[29]	/* stack pointer */
#define s8Reg		gpreg[30]	/* callee saved 8 */
#define fpReg           s8Reg           /* gcc says this is frame pointer */
#define raReg		gpreg[31]	/* return address */
#define reg_pc		pc		/* program counter */
#define reg_sp		spReg		/* stack pointer */
#define reg_fp		fpReg		/* frame pointer */	

#define SR_OFFSET	(0*4)		/* sr register offset */
#define PC_OFFSET	(1*4)		/* pc register offset */

#endif	/* _ASMLANGUAGE */

#define GREG_BASE	(2*4+2*_RTypeSize)
#define GREG_OFFSET(n)  (GREG_BASE + (n)*_RTypeSize)

#define	SRREG		(0*4)			/* process status register */
#define PCREG		(1*4)			/* program counter */
#define	LOREG		(2*4+0*_RTypeSize)	/* lo register */
#define	HIREG		(2*4+1*_RTypeSize)	/* hi register */
#define ZEROREG		GREG_OFFSET(0)		/* wired zero */
#define ATREG		GREG_OFFSET(1)		/* assembler temp */
#define V0REG		GREG_OFFSET(2)		/* function return 0 */
#define V1REG		GREG_OFFSET(3)		/* function return 1 */
#define A0REG		GREG_OFFSET(4)		/* parameter 0 */
#define A1REG		GREG_OFFSET(5)		/* parameter 1 */
#define A2REG		GREG_OFFSET(6)		/* parameter 2 */
#define A3REG		GREG_OFFSET(7)		/* parameter 3 */
#define T0REG		GREG_OFFSET(8)		/* caller saved 0 */
#define T1REG		GREG_OFFSET(9)		/* caller saved 1 */
#define T2REG		GREG_OFFSET(10)		/* caller saved 2 */
#define T3REG		GREG_OFFSET(11)		/* caller saved 3 */
#define T4REG		GREG_OFFSET(12)		/* caller saved 4 */
#define T5REG		GREG_OFFSET(13)		/* caller saved 5 */
#define T6REG		GREG_OFFSET(14)		/* caller saved 6 */
#define T7REG		GREG_OFFSET(15)		/* caller saved 7 */
#define S0REG		GREG_OFFSET(16)		/* callee saved 0 */
#define S1REG		GREG_OFFSET(17)		/* callee saved 1 */
#define S2REG		GREG_OFFSET(18)		/* callee saved 2 */
#define S3REG		GREG_OFFSET(19)		/* callee saved 3 */
#define S4REG		GREG_OFFSET(20)		/* callee saved 4 */
#define S5REG		GREG_OFFSET(21)		/* callee saved 5 */
#define S6REG		GREG_OFFSET(22)		/* callee saved 6 */
#define S7REG		GREG_OFFSET(23)		/* callee saved 7 */
#define T8REG		GREG_OFFSET(24)		/* caller saved 8 */
#define T9REG		GREG_OFFSET(25)		/* caller saved 8 */
#define K0REG		GREG_OFFSET(26)		/* kernal reserved 0 */
#define K1REG		GREG_OFFSET(27)		/* kernal reserved 1 */
#define GPREG		GREG_OFFSET(28)		/* global pointer */
#define SPREG		GREG_OFFSET(29)		/* stack pointer */
#define S8REG		GREG_OFFSET(30)		/* callee saved 8 */
#define RAREG		GREG_OFFSET(31)		/* return address */
#define GREG_END        (GREG_BASE+32*_RTypeSize)

#define WDBCAUSEREG	(GREG_END+0*4)          /* Cause reg (for wdb) */
#define WDBFPCSRREG	(GREG_END+1*4)          /* FPCSR reg (for wdb) */
#define INTCTRLREG	(GREG_END+2*4)          /* ext intr control reg */
#define ULEXTRA1	(GREG_END+3*4)          /* extra - 4 bytes pad */
#define TLBHIREG	(GREG_END+4*4+0*_RTypeSize) /* adrs spc id reg */
#define RTEXTRA2	(GREG_END+4*4+1*_RTypeSize) /* extra */
#define RTEXTRA3	(GREG_END+4*4+2*_RTypeSize) /* extra */
#define RTEXTRA4	(GREG_END+4*4+3*_RTypeSize) /* extra */
#define RTEXTRA5	(GREG_END+4*4+4*_RTypeSize) /* extra */
#define RTEXTRA6	(GREG_END+4*4+5*_RTypeSize) /* extra */
#define RTEXTRA7	(GREG_END+4*4+6*_RTypeSize) /* extra */
#define RTEXTRA8	(GREG_END+4*4+7*_RTypeSize) /* extra */
#define RTEXTRA9	(GREG_END+4*4+8*_RTypeSize) /* extra */
#define RTEXTRA10	(GREG_END+4*4+9*_RTypeSize) /* extra */

#if defined(_WRS_CAVIUM_CNMIPS_CORE) || defined(_WRS_CAVIUM_CNMIPS_II_CORE)
#define P0REG		RTEXTRA3
#define P1REG		RTEXTRA4
#define P2REG		RTEXTRA5
#define MPL0REG		RTEXTRA6
#define MPL1REG		RTEXTRA7
#define MPL2REG		RTEXTRA8
#define TLOREG		RTEXTRA9
#define THIREG		RTEXTRA10
#endif /* defined(_WRS_CAVIUM_CNMIPS_CORE) || defined(_WRS_CAVIUM_CNMIPS_II_CORE) */

#if defined(_WRS_MIPS_NETLOGIC_CPU)
/* Use RT Extra 3 for EIMRREG */
#define EIMRREG         RTEXTRA3
#endif  /* _WRS_MIPS_NETLOGIC_CPU */

#define REG_SET_SIZE	(GREG_END+4*4+10*_RTypeSize)

#ifdef __cplusplus
}
#endif

#endif /* __INCregsMipsh */
