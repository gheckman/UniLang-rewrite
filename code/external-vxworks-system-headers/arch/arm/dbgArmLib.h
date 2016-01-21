/* dbgArmLib.h - header file for ARM-dependent part of debugger */

/* 
 * Copyright 1996-2004, 2005, 2010, 2013 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use  of this
 * software may be licensed only pursuant to the terms of an applicable Wind
 * River license agreement.
 */

/*
modification history
--------------------
01j,26may13,pma  Update for ARMARCH7M
01i,26jul10,jdw  Update with support for THUMB2
01h,29apr10,pad  Moved extern C statement after include statements.
01g,24feb05,jb   Correct definition of SYSCALL_INST
01f,09dec04,scm  resolve DBG_SYSCALL_SIZE warning, define DBG_SYSCALL_INST
01e,11feb04,elg  Add syscall instruction size macro.
01d,12nov98,cdp  added support for ARM generic Thumb library.
01c,20apr98,dbt  modified for new breakpoint scheme
01b,24apr97,cdp  added Thumb (ARM7TDMI_T) support;
		 changed DBG_BREAK_INST for non-Thumb processors.
01a,09may96,cdp  created
*/

#ifndef	__INCdbgArmLibh
#define	__INCdbgArmLibh


#include "esf.h"

#ifdef __cplusplus
extern "C" {
#endif


#define	BREAK_ESF	ESF
#define	TRACE_ESF	ESF

#define DBG_SYSCALL_SIZE        (sizeof (INSTR) / sizeof (INSTR))

#if (ARM_THUMB2)
#define	DBG_SYSCALL_INST        0xDF00       /* SVC */
#define	DBG_SYSCALL_MASK        0xFF00       
#else  /* (ARM_THUMB2) */
#define	DBG_SYSCALL_INST        0xEF0000FA   /* SVC (formerly SWI) */
#endif /* (ARM_THUMB2) */

#if (ARM_THUMB2)
/* 
 * For Thumb2 we can not support cret() without a valid frame pointer so
 * support is disabled here.
 */
#define DBG_CRET FALSE
#endif /* (ARM_THUMB2) */

#if (ARM_THUMB) || (ARM_THUMB2)

  /*
   * TODO -- The WDB code which inserts breakpoints needs to be smarter
   * than it is. We need to use a 16- or 32-bit value depending on the
   * instruction we are going to break on.
   */

#define DBG_BREAK_INST	0xDEFE		/* The undefined instruction used as a
                                     * breakpoint for Thumb-state */
#define DBG_INST_ALIGN	2
#else /* (ARM_THUMB) || (ARM_THUMB2) */

#define DBG_BREAK_INST	0xE7FDDEFE	/* The undefined instruction used as a
					                 * breakpoint for ARM-state */
#define DBG_INST_ALIGN	4
#endif	 /* (ARM_THUMB) || (ARM_THUMB2) */

#define DBG_NO_SINGLE_STEP	1	/* no hardware trace support */

#if (CPU == ARMARCH7M)

#define BRK_INST	0x0		/* hardware instruction breakpoint */
#define DEFAULT_HW_BP	(BRK_INST)	/* default hardware breakpoint */
#define BRK_HARDWARE	(0x10)    /* hardware breakpoint bit */
#define BRK_HARDMASK	(0x0f)    /* hardware breakpoint mask */

#define DBG_HARDWARE_BP	1

#ifdef DBG_NO_SINGLE_STEP
#undef DBG_NO_SINGLE_STEP
#endif
#define DBG_NO_SINGLE_STEP	0	/* no trace support */
#define MAX_HW_BP_NUM           6

#ifndef _ASMLANGUAGE

/* hardware breakpoint registers */

typedef struct              /* DBG_REGS */
    {
    unsigned int    fp_compx[MAX_HW_BP_NUM];   /* debug register: flash patch */
    } DBG_REGS;

#endif /* _ASMLANGUAGE */

#endif /* ARMARCH7M */

#ifdef __cplusplus
}
#endif

#endif	/* __INCdbgArmLibh */
