/* fppSimSolarisLib.h - Solaris VxSim floating-point header */

/* Copyright (c) 1985 by Sun Microsystems, Inc.  */

/* Copyright 1993-2003, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01e,29apr10,pad  Moved extern C statement after include statements.
01d,21aug03,dbt  Added FPSR macros.
01c,19aug03,dbt  Added PAL support.
01b,19mar03,dbt  Fixed fp status register offset.
01a,07jun95,ism  derived from simsparc
*/

#ifndef __INCfppSimsolarisLibh
#define __INCfppSimsolarisLibh

#include "vxWorks.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of bits in the Sun-4 FSR (Floating-point Status Register)
 *   _____________________________________________________________
 *  |  RD |  RP | TEM |  res | FTT | QNE | PR | FCC | AEXC | CEXC |
 *  |-----|---- |-----|------|-----|-----|----|-----|------|------|
 *   31 30 29 28 27 23 22  17 16 14   13   12  11 10 9    5 4    0
 */

#define FSR_CEXC	0x0000001f	/* Current Exception */
#define FSR_AEXC	0x000003e0	/* ieee accrued exceptions */
#define FSR_FCC		0x00000c00	/* Floating-point Condition Codes */
#define FSR_PR		0x00001000	/* Partial Remainder */
#define FSR_QNE		0x00002000	/* Queue not empty */
#define FSR_FTT		0x0001c000	/* Floating-point Trap Type */
#define FSR_VER         0x000E0000      /* Version */
#define FSR_RESV	0x007e0000	/* reserved */
#define FSR_TEM		0x0f100000	/* ieee Trap Enable Mask */
#define FSR_RP		0x30000000	/* Rounding Precision */
#define FSR_RD		0xc0000000	/* Rounding Direction */

#define	FSR_AEXC_SHIFT	5	/* shift needed for ieee accrued exceptions */
#define FSR_FCC_SHIFT	10	/* shift needed for Floating-point Condition Codes */
#define FSR_FTT_SHIFT	14	/* shift needed for trap type */
#define FSR_TEM_SHIFT	23	/* shift needed for ieee Trap Enable Mask */
#define FSR_RP_SHIFT	28	/* shift needed for Rounding Precision */
#define FSR_RD_SHIFT	30	/* shift needed for Rounding Direction */

/*
 * Definition of CEXC (Current EXCeption) bit field of fsr
 */
#define	FSR_CEXC_NX	0x00000001	/* inexact */
#define FSR_CEXC_DZ	0x00000002	/* divide-by-zero */
#define FSR_CEXC_UF	0x00000004	/* underflow */
#define FSR_CEXC_OF	0x00000008	/* overflow */
#define FSR_CEXC_NV	0x00000010	/* invalid */

/*
 * Definition of AEXC (Accrued EXCeption) bit field of fsr
 */
#define	FSR_AEXC_NX	(0x1 << 5)	/* inexact */
#define FSR_AEXC_DZ	(0x2 << 5)	/* divide-by-zero */
#define FSR_AEXC_UF	(0x4 << 5)	/* underflow */
#define FSR_AEXC_OF	(0x8 << 5)	/* overflow */
#define FSR_AEXC_NV	(0x10 << 5)	/* invalid */

/*
 * Definition of FCC (Floating-point Condition Code) field within the FSR
 */
#define FCC_EQUAL	0		/* equal */
#define FCC_LT		1		/* less than */
#define FCC_GT		2		/* greater than */
#define FCC_UNORD	3		/* unordered */
#define FSR_FCC_EQUAL	(FCC_EQUAL   << FSR_FCC_SHIFT)
#define FSR_FCC_LT	(FCC_LT   << FSR_FCC_SHIFT)
#define FSR_FCC_GT	(FCC_GT  << FSR_FCC_SHIFT)
#define FSR_FCC_UNORD	(FCC_UNORD  << FSR_FCC_SHIFT)

/*
 * Definition of FTT (Floating-point Trap Type) field within the FSR
 */
#define FTT_NONE	0		/* no exceptions */
#define FTT_IEEE	1		/* IEEE exception */
#define FTT_UNFIN	2		/* unfinished fpop */
#define FTT_UNIMP	3		/* unimplemented fpop */
#define FTT_SEQ		4		/* sequence error */
#define FTT_ALIGN	5	/* alignment, by software convention */
#define	FTT_DFAULT	6	/* data fault, by software convention */
#define FSR_FTT_IEEE	(FTT_IEEE   << FSR_FTT_SHIFT)
#define FSR_FTT_UNFIN	(FTT_UNFIN  << FSR_FTT_SHIFT)
#define FSR_FTT_UNIMP	(FTT_UNIMP  << FSR_FTT_SHIFT)
#define FSR_FTT_SEQ	(FTT_SEQ    << FSR_FTT_SHIFT)
#define FSR_FTT_ALIGN	(FTT_ALIGN  << FSR_FTT_SHIFT)
#define FSR_FTT_DFAULT	(FTT_DFAULT << FSR_FTT_SHIFT)

/*
 * Definition of TEM (Trap Enable Mask) bit field of fsr
 */
#define	FSR_TEM_NX	(0x1 << 23)	/* inexact */
#define FSR_TEM_DZ	(0x2 << 23)	/* divide-by-zero */
#define FSR_TEM_UF	(0x4 << 23)	/* underflow */
#define FSR_TEM_OF	(0x8 << 23)	/* overflow */
#define FSR_TEM_NV	(0x10 << 23)	/* invalid */

/*
 * Definition of RP (Rounding Precision) field of fsr
 */
#define RP_DBLEXT	0		/* double-extended */
#define RP_SINGLE	1		/* single */
#define RP_DOUBLE	2		/* double */
#define RP_RESERVED	3		/* unused and reserved */

/*
 * Definition of RD (Rounding Direction) field of fsr
 */
#define RD_NEAR		0		/* nearest or even if tie */
#define RD_ZER0		1		/* to zero */
#define RD_POSINF	2		/* positive infinity */
#define RD_NEGINF	3		/* negative infinity */

/* Number of floating point data registers */

#define  FP_NUM_DREGS	16		/* Floating-Point Data Registers */

/* equates for fppState, fpstate */

#define UNKNOWN			0x00	/* default */
#define FPU_TESTED		0x01	/* set by fppProbe */
#define FPU_TESTED_TRUE		0x02	/* set by fppProbe */
#define FPU_TESTED_FALSE	0x00	/* set by fppProbe */
#define FPU_AVAILABLE		(FPU_TESTED + FPU_TESTED_TRUE)
#define NO_FPU_AVAILABLE	(FPU_TESTED + FPU_TESTED_FALSE)

#ifndef _ASMLANGUAGE

typedef struct fpContext                /* Floating-Point Context */
    {
    double fpd[FP_NUM_DREGS];	/* Data Registers */
    unsigned int fsr;		/* Status Register */
    } FP_CONTEXT;

#define FPREG_SET	FP_CONTEXT

/* variable declarations */

extern REG_INDEX fpRegName[];		/* f-point data register table */
extern REG_INDEX fpCtlRegName[];	/* f-point control register table */
extern WIND_TCB *pFppTaskIdPrevious;	/* task id for deferred exceptions */
extern FUNCPTR	 fppCreateHookRtn;	/* arch dependent create hook routine */
extern FUNCPTR	 fppDisplayHookRtn;	/* arch dependent display routine */

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern void		fppNan (FP_CONTEXT *pFpContext, ULONG fppFsr);
extern FP_CONTEXT *	fppCtxCreate (int tid);
extern STATUS		fppCtxDelete (FP_CONTEXT * pCtx);
extern void		fppCtxShow (FP_CONTEXT * pFpContext);
extern STATUS		fppEnable (void);
extern STATUS		fppDisable (void);

#else

extern void		fppNan ();
extern FP_CONTEXT *	fppCtxCreate ();
extern STATUS		fppCtxDelete ();
extern void		fppCtxShow ();
extern STATUS		fppEnable ();
extern STATUS		fppDisable ();

#endif	/* __STDC__ */

#endif	/* _ASMLANGUAGE */

#define FP_DATA         0x0           		/* Data Registers */
#define FPD(n)          (FP_DATA + (4 * (n)))
#define FP_QUEUE        (FPD(FP_NUM_DREGS*2))	/* Q Registers (dword aligned)*/
#define FSR             (FP_QUEUE)		/* Status Register */

#ifdef __cplusplus
}
#endif

#endif /* __INCfppSimsolarisLibh */
