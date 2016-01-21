/* fppArmLib.h - ARM floating-point coprocessor support header file */

/* 
 * Copyright 1996, 2012 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,11jan12,jdw  Update to call the VFP routines, WIND00327855
01a,09may96,cdp  created
*/

#ifndef	__INCfppArmLibh
#define	__INCfppArmLibh

#include <arch/arm/vfpArmLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	_ASMLANGUAGE

#define FP_CONTEXT VFP_CONTEXT

#define FPREG_SET FP_CONTEXT


/* variable declarations */

extern REG_INDEX fpRegName[];		/* f-point data register table */
extern REG_INDEX fpCtlRegName[];	/* f-point control register table */
extern WIND_TCB *pFppTaskIdPrevious;	/* task id for deferred exceptions */
extern FUNCPTR	 fppCreateHookRtn;	/* arch dependent create hook routine */
extern FUNCPTR	 fppDisplayHookRtn;	/* arch dependent display routine */


/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

IMPORT void	fppArchInit (void);
IMPORT void	fppArchTaskCreateInit (FP_CONTEXT *pFpContext);

#else	/* __STDC__ */

IMPORT void	fppArchInit ();
IMPORT void	fppArchTaskCreateInit ();

#endif	/* __STDC__ */

#endif	/* _ASMLANGUAGE */


#ifdef __cplusplus
}
#endif

#endif	/* __INCfppArmLibh */
