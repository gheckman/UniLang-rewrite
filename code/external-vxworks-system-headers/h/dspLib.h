/* dspLib.h - dsp coprocessor support library header */

/*
 * Copyright (C) 1998, 2005, 2010-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01e,29nov11,cww  Fixed mis-positioned extern C statement (WIND00288939)
01d,29apr10,pad  Moved extern C statement after include statements.
01c,27jul05,pes  Handle MIPS DSP include file.
01b,08aug98,kab  fixed default typedef of DSP_CONTEXT.  Cleanup after review.
01a,22jul98,mem  written.
*/

#ifndef __INCdspLibh
#define __INCdspLibh

#include <vxWorks.h>
#include <taskLib.h>

#if (CPU_FAMILY==SH)
#include <arch/sh/dspShLib.h>
#elif (CPU_FAMILY==MIPS)
#include <arch/mips/dspMipsLib.h>
#else
#define _NEED_DEFAULT_DSP_CONTEXT
#endif	/* CPU_FAMILY==SH */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

#ifdef _NEED_DEFAULT_DSP_CONTEXT
#define DSPREG_SET	DSP_CONTEXT
typedef ULONG		DSP_CONTEXT;		/* in case of allocation */
#endif /* _NEED_DEFAULT_DSP_CONTEXT */

/* variable declarations */

IMPORT REG_INDEX  dspRegName[];		/* dsp data register table */
IMPORT REG_INDEX  dspCtlRegName[];	/* dsp control register table */
IMPORT WIND_TCB * pDspTaskIdPrevious;	/* task id for deferred exceptions */
IMPORT FUNCPTR	  dspCreateHookRtn;	/* arch dependent create hook routine */
IMPORT FUNCPTR	  dspDisplayHookRtn;	/* arch dependent display routine */

/* function declarations */

/* 
 * The interface is set in os/dspLib.c through dspInit().  Some of
 * the functions are actually implemented in architecture dependent
 * files.
 */

IMPORT void 	dspInit		(void);
IMPORT void	dspShowInit	(void);
IMPORT void 	dspTaskRegsShow	(int task);
IMPORT STATUS 	dspTaskRegsGet	(int task, DSPREG_SET * pDspRegSet);
IMPORT STATUS 	dspTaskRegsSet	(int task, DSPREG_SET * pDspRegSet);
IMPORT STATUS 	dspProbe	(void);
IMPORT void 	dspRestore	(DSP_CONTEXT * pDspContext);
IMPORT void 	dspSave		(DSP_CONTEXT * pDspContext);
IMPORT void	dspRegsToCtx	(DSPREG_SET * pDspRegSet,
				 DSP_CONTEXT * pDspContext);
IMPORT void	dspCtxToRegs	(DSP_CONTEXT * pDspContext,
				 DSPREG_SET * pDspRegSet);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCdspLibh */
