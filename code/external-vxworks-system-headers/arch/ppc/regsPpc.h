/* regsPpc.h - PowerPC registers */

/* Copyright 1984-2008, 2010, 2011 Wind River Systems, Inc. */

/*
modification history
--------------------
01n,03may11,syt  add support for PPC465.
01n,20aug10,x_z  add support for PPC476.
01m,03sep08,pmr  remove SPE for e500mc
01l,26oct06,to   add WIND_CPU_STATE
01k,15apr06,pch  add REG_SET_SP
01j,12feb04,jtp  Apply _WRS_MMU_CLASS_* macros.
01i,15jan04,jtp  SPR 93230 - make PPC32 REG_SET struct size match other PPC.
01h,01dec03,jtp  Add PPC440 ASID storage; size & offset cleanup
01g,13nov03,pcs  Make the size of REG_SET the same for all CPU variants.
01f,09oct03,pcs  Add context information to the REG_SET.
01f,03oct02,dtr  Adding speFpscr to standard register set for 85XX.
01e,30dec97,dbt  added common names for registers
01d,20apr95,yao  add padding word for PPC604 and PPC603.
01c,02mar95,yao  changed PPC403GA to PPC403.
01b,07nov94,yao  moved tool related definition to tools.h.
xxxxxxxxxxx,yao  written.
*/

#ifndef __INCregsPpch
#define __INCregsPpch

#ifdef __cplusplus
extern "C" {
#endif

#define GREG_NUM	32	/* has 32 32/64-bit data registers */

#ifndef	_ASMLANGUAGE

typedef struct		/* REG_SET */
    {
    _RType gpr[GREG_NUM];	/* general purpose registers */
    _RType msr;			/* machine state register */
    _RType lr;			/* link register */
    _RType ctr;			/* count register */
    _RType pc;			/* program counter */
    UINT32 cr;			/* condition register */
    UINT32 xer;			/* fixed-point exception register */
#if	(CPU==PPC601)
    UINT32 mq;			/* MQ register */
#else
    UINT32 pgTblPtr;		/* base of page table */
#endif	/* (CPU==PPC601) */
#if	defined(_WRS_MMU_CLASS_SR_REGS)
    UINT32 scSrTblPtr;		/* SR regs array ptr - kernel protection map */
    UINT32 srTblPtr;		/* SR regs array ptr - user protection map */
#elif	defined(_WRS_MMU_CLASS_PID_REG)
    UINT32 casid;               /* PPC405, Book E PID and PPC860 M_CASID */
# if (CPU == PPC85XX)
    UINT32 spefscr;             /* SPE floating-point status & ctrl reg */
# else  /* CPU == PPC85XX */
    UINT32 spare1;		/* keeps struct size consistent */
# endif  /* CPU == PPC85XX */
#else	/* _WRS_MMU_CLASS_ */
    UINT32 spare0;		/* keeps struct size consistent */
    UINT32 spare1;		/* keeps struct size consistent */
#endif /* _WRS_MMU_CLASS_* */
    } REG_SET;

typedef struct wind_cpu_state
    {
    REG_SET	regs;
    } WIND_CPU_STATE;

/* some common names for registers */

#undef	spReg
#define spReg	gpr[1]	/* stack pointer */
#undef	fpReg
#define	fpReg	gpr[31]	/* frame pointer */
#define reg_pc	pc	/* program counter */
#define reg_sp	spReg	/* stack pointer */
#define reg_fp	fpReg	/* frame pointer */

#endif	/* _ASMLANGUAGE */


#define PPC_ARG0_REG		3	/* params start at register 3 */
#define PPC_MAX_ARG_REGS	8	/* max # of params passed in register */

#define REG_SET_GRBASE	0x00	/* general purpose register base */
#define REG_SET_GR(n)	(REG_SET_GRBASE + _PPC_REG_SIZE*(n))
#define REG_SET_MSR	(REG_SET_GR(GREG_NUM))
#define REG_SET_LR	(REG_SET_MSR + _PPC_REG_SIZE)
#define REG_SET_CTR	(REG_SET_LR + _PPC_REG_SIZE)
#define REG_SET_PC	(REG_SET_CTR + _PPC_REG_SIZE)
#define REG_SET_CR	(REG_SET_PC + _PPC_REG_SIZE)
#define REG_SET_XER	(REG_SET_CR + 4)
#define REG_SET_SP	(REG_SET_GR(1))

#if	(CPU==PPC601)
#define REG_SET_MQ	(REG_SET_XER + 4)
#else	/* (CPU==PPC601) */
#define REG_SET_PG_TBL_PTR    (REG_SET_XER + 4)    /* ptr to pgTbl */
#endif	/* (CPU==PPC601) */

#if	defined(_WRS_MMU_CLASS_SR_REGS)
#define REG_SET_SC_SR_TBL_PTR   (REG_SET_PG_TBL_PTR + 4)
#define REG_SET_SR_TBL_PTR      (REG_SET_SC_SR_TBL_PTR + 4)
#elif	defined(_WRS_MMU_CLASS_PID_REG)
#define REG_SET_CASID   (REG_SET_PG_TBL_PTR + 4)      /* current ASID */
#if	(CPU == PPC85XX)
#ifdef _WRS_SPE_SUPPORT
#define REG_SET_SPEFSCR	(REG_SET_CASID + 4)
#endif  /* _WRS_SPE_SUPPORT */
#endif	/* CPU == PPC85XX */
#endif	/* _WRS_MMU_CLASS_* */

#define	PC_OFFSET	REG_SET_PC

#define WIND_TCB_R0		(WIND_TCB_REGS + REG_SET_GR(0))
#define WIND_TCB_R1		(WIND_TCB_REGS + REG_SET_GR(1))
#define WIND_TCB_R2		(WIND_TCB_REGS + REG_SET_GR(2))
#define WIND_TCB_R3		(WIND_TCB_REGS + REG_SET_GR(3))
#define WIND_TCB_R4		(WIND_TCB_REGS + REG_SET_GR(4))
#define WIND_TCB_R5		(WIND_TCB_REGS + REG_SET_GR(5))
#define WIND_TCB_R6		(WIND_TCB_REGS + REG_SET_GR(6))
#define WIND_TCB_R7		(WIND_TCB_REGS + REG_SET_GR(7))
#define WIND_TCB_R8		(WIND_TCB_REGS + REG_SET_GR(8))
#define WIND_TCB_R9		(WIND_TCB_REGS + REG_SET_GR(9))
#define WIND_TCB_R10		(WIND_TCB_REGS + REG_SET_GR(10))
#define WIND_TCB_R11		(WIND_TCB_REGS + REG_SET_GR(11))
#define WIND_TCB_R12		(WIND_TCB_REGS + REG_SET_GR(12))
#define WIND_TCB_R13		(WIND_TCB_REGS + REG_SET_GR(13))
#define WIND_TCB_R14		(WIND_TCB_REGS + REG_SET_GR(14))
#define WIND_TCB_R15		(WIND_TCB_REGS + REG_SET_GR(15))
#define WIND_TCB_R16		(WIND_TCB_REGS + REG_SET_GR(16))
#define WIND_TCB_R17		(WIND_TCB_REGS + REG_SET_GR(17))
#define WIND_TCB_R18		(WIND_TCB_REGS + REG_SET_GR(18))
#define WIND_TCB_R19		(WIND_TCB_REGS + REG_SET_GR(19))
#define WIND_TCB_R20		(WIND_TCB_REGS + REG_SET_GR(20))
#define WIND_TCB_R21		(WIND_TCB_REGS + REG_SET_GR(21))
#define WIND_TCB_R22		(WIND_TCB_REGS + REG_SET_GR(22))
#define WIND_TCB_R23		(WIND_TCB_REGS + REG_SET_GR(23))
#define WIND_TCB_R24		(WIND_TCB_REGS + REG_SET_GR(24))
#define WIND_TCB_R25		(WIND_TCB_REGS + REG_SET_GR(25))
#define WIND_TCB_R26		(WIND_TCB_REGS + REG_SET_GR(26))
#define WIND_TCB_R27		(WIND_TCB_REGS + REG_SET_GR(27))
#define WIND_TCB_R28		(WIND_TCB_REGS + REG_SET_GR(28))
#define WIND_TCB_R29		(WIND_TCB_REGS + REG_SET_GR(29))
#define WIND_TCB_R30		(WIND_TCB_REGS + REG_SET_GR(30))
#define WIND_TCB_R31		(WIND_TCB_REGS + REG_SET_GR(31))
#define WIND_TCB_MSR		(WIND_TCB_REGS + REG_SET_MSR)
#define WIND_TCB_LR		(WIND_TCB_REGS + REG_SET_LR)
#define WIND_TCB_CTR		(WIND_TCB_REGS + REG_SET_CTR)
#define WIND_TCB_PC		(WIND_TCB_REGS + REG_SET_PC)
#define WIND_TCB_CR		(WIND_TCB_REGS + REG_SET_CR)
#define WIND_TCB_XER		(WIND_TCB_REGS + REG_SET_XER)
#if	(CPU==PPC601)
#define WIND_TCB_MQ		(WIND_TCB_REGS + REG_SET_MQ)
#else	/* (CPU==PPC601) */
#define WIND_TCB_PG_TBL_PTR     (WIND_TCB_REGS + REG_SET_PG_TBL_PTR)
#endif	/* (CPU==PPC601) */

#if	defined(_WRS_MMU_CLASS_SR_REGS)
#define WIND_TCB_SC_SR_TBL_PTR  (WIND_TCB_REGS + REG_SET_SC_SR_TBL_PTR)
#define WIND_TCB_SR_TBL_PTR     (WIND_TCB_REGS + REG_SET_SR_TBL_PTR)
#elif	defined(_WRS_MMU_CLASS_PID_REG)
#define WIND_TCB_CASID          (WIND_TCB_REGS + REG_SET_CASID)
#if     (CPU == PPC85XX)
#ifdef _WRS_SPE_SUPPORT
#define WIND_TCB_SPEFSCR        (WIND_TCB_REGS + REG_SET_SPEFSCR)
#endif  /* _WRS_SPE_SUPPORT */
#endif  /* CPU == PPC85XX */
#endif	/* _WRS_MMU_CLASS_* */

#define WIND_TCB_SP		WIND_TCB_R1
#define WIND_TCB_P0		WIND_TCB_R3
#define WIND_TCB_P1		WIND_TCB_R4
#define WIND_TCB_P2		WIND_TCB_R5
#define WIND_TCB_P3		WIND_TCB_R6
#define WIND_TCB_P4		WIND_TCB_R7
#define WIND_TCB_P5		WIND_TCB_R8
#define WIND_TCB_P6		WIND_TCB_R9
#define WIND_TCB_P7		WIND_TCB_R10

#define WIND_TCB_T0		WIND_TCB_R14
#define WIND_TCB_T1		WIND_TCB_R15
#define WIND_TCB_T2		WIND_TCB_R16
#define WIND_TCB_T3		WIND_TCB_R17
#define WIND_TCB_T4		WIND_TCB_R18
#define WIND_TCB_T5		WIND_TCB_R19
#define WIND_TCB_T6		WIND_TCB_R20
#define WIND_TCB_T7		WIND_TCB_R21
#define WIND_TCB_T8		WIND_TCB_R22
#define WIND_TCB_T9		WIND_TCB_R23
#define WIND_TCB_T10		WIND_TCB_R24
#define WIND_TCB_T11		WIND_TCB_R25
#define WIND_TCB_T12		WIND_TCB_R26
#define WIND_TCB_T13		WIND_TCB_R27
#define WIND_TCB_T14		WIND_TCB_R28
#define WIND_TCB_T15		WIND_TCB_R29
#define WIND_TCB_T16		WIND_TCB_R30
#define WIND_TCB_T17		WIND_TCB_R31

#ifdef	_AIX_TOOL
#define WIND_TCB_RTOC		WIND_TCB_R2
#endif	/* _AIX_TOOL */

/* size of the full REG_SET structure, including spare bytes */

#define _PPC_REG_SET_SIZE       (_PPC_REG_SIZE * (GREG_NUM + 9))

#if     (CPU == PPC860)

/* Last valid number for the ASID register on the 8xx family */

#define LAST_ASID       15

#elif   ((CPU == PPC405) || (CPU == PPC440) || (CPU == PPC85XX) || (CPU == PPC465))
#define LAST_ASID       255
#elif   (CPU == PPC476)
#define LAST_ASID       65535
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCregsPpch */
