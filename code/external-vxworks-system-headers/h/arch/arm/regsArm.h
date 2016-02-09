/* regsArm.h - ARM registers */

/*
 * Copyright (c) 1996, 1998, 2003, 2004, 2007, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */


/*
modification history
--------------------
01i,09may12,j_b  enable ARMARCH7M-specific header usage
01h,03may12,j_b  revert to remove ARMARCH7M-specific header usage
01g,01may12,j_b  Update for ARMv7M
01f,18jun07,m_h  Adding definition for WIND_CPU_STATE
01e,25aug04,scm  add lrReg alternative name
01d,18mar04,scm  add usr mode rtp support...
01c,07may03,pes  PAL conditional compilation cleanup.
01b,15apr98,kkk	 added reg_pc, reg_sp, and reg_fp.
01a,08may96,cdp  written, based on I86 version
*/

#ifndef	__INCregsArmh
#define	__INCregsArmh

#if (CPU == ARMARCH7M)

#include "arch/arm/arm-m/regsArm-m.h"

#else /* (CPU == ARMARCH7M) */


#ifdef __cplusplus
extern "C" {
#endif

#define GREG_NUM	15	/* has 15 32-bit general registers */

#ifndef	_ASMLANGUAGE

/* REG_SET - ARM Register set
 * Note that the exception stack frame relies on the order of items
 * in this so don't change this without changing the ESF and the stub
 * in excALib which creates it.
 */

typedef struct			/* REG_SET - ARM register set */
    {
    ULONG r[GREG_NUM];		/* general purpose registers 0-14 */
    INSTR *pc;			/* program counter */
    ULONG cpsr;			/* current PSR */
    ULONG ttbase;		/* Trans Table Base */
    } REG_SET;

typedef struct wind_cpu_state
    {
    REG_SET	regs;
    } WIND_CPU_STATE;

#define fpReg		r[11]	/* frame pointer */
#define spReg		r[13]	/* stack pointer */
#define lrReg		r[14]	/* link reg pointer */

#define reg_pc		pc	/* program counter */

#define reg_lr		lrReg	/* link reg pointer */
#define reg_sp		spReg	/* stack pointer */
#define reg_fp		fpReg	/* frame pointer */

#endif	/* _ASMLANGUAGE */

#define	ARM_REG_SIZE	4
#define REG_SET_G_REG_BASE	0x00	/* data reg's base offset to REG_SET */
#define REG_SET_G_REG_OFFSET(n)	(REG_SET_G_REG_BASE + (n)*ARM_REG_SIZE)
#define REG_SET_PC_OFFSET	(REG_SET_G_REG_OFFSET(GREG_NUM))
#define REG_SET_CPSR_OFFSET	(REG_SET_PC_OFFSET + ARM_REG_SIZE)

#define REG_SET_TTBASE_OFFSET	(REG_SET_CPSR_OFFSET + ARM_REG_SIZE)

#define PC_OFFSET		REG_SET_PC_OFFSET

/* PAL additions */

/* moved here from h/private/taskLibP.h */
   
#define WIND_TCB_R0     WIND_TCB_REGS
#define WIND_TCB_R1     (WIND_TCB_R0+4*1)
#define WIND_TCB_R4     (WIND_TCB_R0+4*4)
#define WIND_TCB_R5     (WIND_TCB_R0+4*5)
#define WIND_TCB_SP     (WIND_TCB_R0+4*13)
#define WIND_TCB_PC     (WIND_TCB_R0+4*15)
#define WIND_TCB_CPSR   (WIND_TCB_PC+4)

#define WIND_TCB_TTBASE (WIND_TCB_CPSR+4)

/* End PAL */

#ifdef __cplusplus
}
#endif

#endif /* (CPU == ARMARCH7M) */

#endif /* __INCregsArmh */
