/* dspMipsLib.h - MIPS DSP ASE Header */

/*
 * Copyright (C) 2005-2006 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
01b,12jan06,pes  Correct macros for MIPS R2 ISA support. (Macros are
		 retained for backward compatability. Current tool release
		 implements native support for the DSP instructions.)
01a,27jul05,pes  Created
*/

#ifndef __INCdspMipsLibh
#define __INCdspMipsLibh

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE
typedef struct dspContext	/* DSP_CONTEXT */
    {
    struct
	{
	UINT32	hi;
	UINT32	lo;
	} accum[3];
    UINT32 dspcr;
    UINT32 pad;	/* pad size to doubleword boundary */
    } DSP_CONTEXT;

#define DSPREG_SET DSP_CONTEXT

/* variable declarations */

/* function declarations */

IMPORT void     dspArchUnitInit (void);
IMPORT void     dspInitialize (void);
IMPORT DSP_CONTEXT * dspCtxCreate (int);
IMPORT STATUS	dspCtxDelete (DSP_CONTEXT *);
IMPORT void	dspEnable(void);
IMPORT void	dspDisable(void);

IMPORT FUNCPTR _func_dspInitializeHook;
IMPORT FUNCPTR _func_dspSaveHook;
IMPORT FUNCPTR _func_dspRestoreHook;
    
#endif	/* _ASMLANGUAGE */

/* DSP_CONTEXT structure offsets */
#define DSP_CTX_HI1	0x0	/* OFFSET(dsp.accum[0].hi) */
#define DSP_CTX_LO1	0x4	/* OFFSET(dsp.accum[0].lo) */
#define DSP_CTX_HI2	0x8	/* OFFSET(dsp.accum[1].hi) */
#define DSP_CTX_LO2	0xc	/* OFFSET(dsp.accum[1].lo) */
#define DSP_CTX_HI3	0x10	/* OFFSET(dsp.accum[2].hi) */
#define DSP_CTX_LO3	0x14	/* OFFSET(dsp.accum[2].lo) */
#define DSP_CTX_DSPCR	0x18	/* OFFSET(dsp.dspcr) */

/* DSP Present bit in CONFIG3 register */
#define CFG3_DSPP	0x400

#ifdef _ASMLANGUAGE
/* Macros to synthesize the new DSP instructions */
/* These macros are retained for legacy purposes */

#define STRINGIZE(a,b)	a##b
#define R2_MFHI(a,b)  mfhi STRINGIZE($,a),STRINGIZE($ac,b)
#define R2_MFLO(a,b)  mflo STRINGIZE($,a),STRINGIZE($ac,b)
#define R2_MTHI(a,b)  mthi STRINGIZE($,a),STRINGIZE($ac,b)
#define R2_MTLO(a,b)  mtlo STRINGIZE($,a),STRINGIZE($ac,b)
#define R2_RDDSP(rd)  rddsp $rd
#define R2_WRDSP(rs)  wrdsp $rs
#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCdspMipsLibh */
