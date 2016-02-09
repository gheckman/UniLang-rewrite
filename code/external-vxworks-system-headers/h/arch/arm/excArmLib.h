/* excArmLib.h - ARM exception library header file */

/*
 * Copyright (c) 1996-2003,2006,2009,2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01g,14may12,m_h  enable ARMARCH7M-specific header usage
01f,23mar09,m_h  Support for non-zero exception vector base
01e,01feb06,jb  Adding VFP Support
01d,26nov03,pes  Correct _WRS_IS_SUPV_EXC macro.
01c,18nov03,pes  Add _WRS_IS_SUPV_EXC macro.
01b,23jul01,scm  change XScale name to conform to coding standards...
01a,11dec00,scm  replace references to ARMSA2 with XScale
01c,16oct00,scm  reverse back I & F bits for SA2
01b,15sep00,scm  update for SA2 support...
01a,09may96,cdp  created
*/

#ifndef	__INCexcArmLibh
#define	__INCexcArmLibh

#if (CPU == ARMARCH7M)

#include "arch/arm/arm-m/excArmLib-m.h"

#else /* (CPU == ARMARCH7M) */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/*
 * NOTE: if this structure changes, the TCB offsets in h/private/taskLibP.h
 *	 must be updated. See also taskLib.h.
 */

typedef struct
    {
    UINT32	valid;		/* indicators that following fields are valid */
    UINT32	vecAddr;	/* exception vector address */
    INSTR *	pc;		/* PC */
    UINT32	cpsr;		/* CPSR */
    } EXC_INFO;

#define _WRS_IS_SUPV_EXC() (((excInfo.cpsr & MASK_MODE) == MODE_USER32) ? FALSE : TRUE)

extern FUNCPTR excExcepHook;	/* add'l rtn to call when exceptions occur */
extern VOIDFUNCPTR _func_excBreakpoint; /* called to handle breakpoints */

extern void excVecBaseSet (UINT32 base); /* non-zero exception base address */

#if defined(__STDC__) || defined(__cplusplus)

extern STATUS  	excIntConnect (VOIDFUNCPTR *, VOIDFUNCPTR);
extern void	excVecSet (FUNCPTR *, FUNCPTR);
extern FUNCPTR	excVecGet (FUNCPTR *);


#else	/* __STDC__ */

extern STATUS  	excIntConnect ();
extern void	excVecSet ();
extern FUNCPTR	excVecGet ();

#endif	/* __STDC__ */

#endif	/* ASMLANGUAGE */


/* exception information valid bits */

#define EXC_INFO_VECADDR	0x01	/* vector is valid */
#define EXC_INFO_PC		0x02	/* PC is valid */
#define EXC_INFO_CPSR		0x04	/* CPSR is valid */
#define EXC_INFO_VFPCSR         0x08    /* VFP CSR is valid */


/* exception vector addresses */

#define EXC_OFF_RESET		0x00	/* reset */
#define EXC_OFF_UNDEF		0x04	/* undefined instruction */
#define EXC_OFF_SWI		0x08	/* software interrupt */
#define EXC_OFF_PREFETCH	0x0c	/* prefetch abort */
#define EXC_OFF_DATA		0x10	/* data abort */
#define EXC_OFF_IRQ             0x18    /* interrupt */
#define EXC_OFF_FIQ             0x1C    /* fast interrupt */

/* Exception Vector Base */
#define ARM_EXC_VEC_BASE        0x00

/*
 * In coyanosa I80310 the default vector base is 0x00,
 * can be relocated into 0xFFFF0000
 *
 */

#if ((CPU==XSCALE) || (CPU==ARMSA110))
#define ARM_EXC_VEC_BASE_RELOCATED      0xffff0000
#endif

#ifdef __cplusplus
}
#endif

#endif /* (CPU == ARMARCH7M) */

#endif	/* __INCexcArmLibh */



