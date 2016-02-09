/* regsArm-m.h - ARMv7-M registers */

/*
 * Copyright (c) 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01e,19jul12,jdw  Add missing TCB offset register definitions
01d,23may12,jdw  Add PRIMASK and BASEPRI offsets 
01c,10may12,j_b  fix tabs/spacing
01b,03may12,j_b  replace "-" in filename include macro
01a,03apr12,j_b  created from target/h/arch/arm/regsArm.f version 01f
*/

#ifndef	__INCregsArm_mh
#define	__INCregsArm_mh

#ifdef __cplusplus
extern "C" {
#endif

#define GREG_NUM	15	/* has 15 32-bit general registers */

#ifndef	_ASMLANGUAGE

/* 
 * REG_SET - ARMv7-M Register set
 * Note that the exception stack frame relies on the order of items
 * in this so don't change this without changing the ESF and the stub
 * in excALib which creates it.
 */

typedef struct			/* REG_SET - ARMv7-M register set */
    {
    ULONG r[GREG_NUM];		/* general purpose registers 0-14 */
    INSTR *pc;			/* program counter */
    ULONG psr;			/* combined A/I/E PSR */
    ULONG basepri;		/* BASEPRI */
    ULONG demcr;		/* MON_STEP in DEMCR */
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

#define	ARM_REG_SIZE		4
#define REG_SET_G_REG_BASE	0x00	/* data reg's base offset to REG_SET */
#define REG_SET_G_REG_OFFSET(n)	(REG_SET_G_REG_BASE + (n)*ARM_REG_SIZE)
#define REG_SET_PC_OFFSET	(REG_SET_G_REG_OFFSET(GREG_NUM))
#define REG_SET_CPSR_OFFSET	(REG_SET_PC_OFFSET + ARM_REG_SIZE)
#define REG_SET_BASEPRI_OFFSET	(REG_SET_CPSR_OFFSET + ARM_REG_SIZE)
#define REG_SET_DEMCR_OFFSET    (REG_SET_BASEPRI_OFFSET + ARM_REG_SIZE)

#define PC_OFFSET		REG_SET_PC_OFFSET

/* PAL additions */

/* moved here from h/private/taskLibP.h */
   
#define WIND_TCB_R0     WIND_TCB_REGS
#define WIND_TCB_R1     (WIND_TCB_R0+4*1)
#define WIND_TCB_R2     (WIND_TCB_R0+4*2)
#define WIND_TCB_R3     (WIND_TCB_R0+4*3)
#define WIND_TCB_R4     (WIND_TCB_R0+4*4)
#define WIND_TCB_R5     (WIND_TCB_R0+4*5)
#define WIND_TCB_R6     (WIND_TCB_R0+4*6)
#define WIND_TCB_R7     (WIND_TCB_R0+4*7)
#define WIND_TCB_R8     (WIND_TCB_R0+4*8)
#define WIND_TCB_R9     (WIND_TCB_R0+4*9)
#define WIND_TCB_R10    (WIND_TCB_R0+4*10)
#define WIND_TCB_R11    (WIND_TCB_R0+4*11)
#define WIND_TCB_R12    (WIND_TCB_R0+4*12)
#define WIND_TCB_SP     (WIND_TCB_R0+4*13)
#define WIND_TCB_LR     (WIND_TCB_R0+4*14)
#define WIND_TCB_PC     (WIND_TCB_R0+4*15)
#define WIND_TCB_CPSR   (WIND_TCB_PC+4)
#define WIND_TCB_BASEPRI  (WIND_TCB_PC+8)
#define WIND_TCB_DEMCR  (WIND_TCB_PC+12)


/* End PAL */

#ifdef __cplusplus
}
#endif

#endif	/* __INCregsArm_mh */
