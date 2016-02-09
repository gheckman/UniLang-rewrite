/* esfArm.h - ARM exception stack frames */

/* 
 * Copyright (c) 1996, 2004, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01e,09may12,j_b  enable ARMARCH7M-specific header usage
01d,03may12,j_b  revert to remove ARMARCH7M-specific header usage
01c,01may12,j_b  Update for ARMv7M
01b,09sep04,scm  add ttbase to ESF, so structs REG_SET & ESF overlap correctly
01a,09may96,cdp  created
*/

#ifndef	__INCesfArmh
#define	__INCesfArmh

#if (CPU == ARMARCH7M)

#include "arch/arm/arm-m/esfArm-m.h"

#else /* (CPU == ARMARCH7M) */


#ifdef __cplusplus
extern "C" {
#endif

#ifndef	_ASMLANGUAGE

/* The Exception Stack Frame
 * On the ARM, this is faked by a stub and the pointer
 * passed back points to the PC and CPSR at the end of the
 * register structure. If that changes, so must this.
 *
 * I.E. REG_SET struct & ESf struct 'overlap' on last 3 
 * elements of REG_SET (pc,cpsr,ttbase)...
 */

typedef struct
    {
    INSTR *pc;		/* program counter */
    ULONG cpsr;		/* current PSR */
    ULONG ttbase;       /* Trans Table Base */
    UINT32 vecAddr;	/* address of exception vector => type */
    } ESF;

#endif	/* _ASMLANGUAGE */


#ifdef __cplusplus
}
#endif


#endif /* (CPU == ARMARCH7M) */

#endif /* __INCesfArmh */
