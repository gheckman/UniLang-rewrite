/* vxbQeIntCtlr.h - Quicc Engine interrupt controller header file */

/* Copyright (c) 2007 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,03jun07,dtr  adapted from qeIntrCtl.h.
*/

#ifndef __INCvxbQeIntCtlrh
#define __INCvxbQeIntCtlrh

#include "vxWorks.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef  _ASMLANGUAGE
#define CAST(x)
#else /* _ASMLANGUAGE */
#define CAST(x) (x)
#endif  /* _ASMLANGUAGE */

#ifdef QE_IVEC_TO_INUM
# undef QE_IVEC_TO_INUM
#endif /* IVEC_TO_INUM */

#ifdef QE_INUM_TO_IVEC
# undef QE_INUM_TO_IVEC
#endif /* INUM_TO_IVEC */

#define QE_IVEC_TO_INUM(intVec)    (qeIvecToInum(intVec))
#define QE_INUM_TO_IVEC(intNum)    (qeInumToIvec(intNum))

#define QE_INUM_MAX		64
#define QE_IVEC_MAX		64
#ifndef _ASMLANGUAGE
#define CAST(x) (x)
#ifndef VUINT32
typedef volatile UINT32 VUINT32; /* volatile unsigned word */
#endif
#else
#define CAST(x) 
#endif

#define QE_CICR(base)         ((VUINT32 *) ((base) + 0x80)) /* interrupt configuration Register */
#define QE_CIVEC(base)        ((VUINT32 *) ((base) + 0x84)) 
#define QE_CRIPNR(base)       ((VUINT32 *) ((base) + 0x88))
#define QE_CIPNR(base)        ((VUINT32 *) ((base) + 0x8C))
#define QE_CIPXCC(base)       ((VUINT32 *) ((base) + 0x90))
#define QE_CIPYCC(base)       ((VUINT32 *) ((base) + 0x94))
#define QE_CIPWCC(base)       ((VUINT32 *) ((base) + 0x98))
#define QE_CIPZCC(base)       ((VUINT32 *) ((base) + 0x9C))
#define QE_CIMR(base)         ((VUINT32 *) ((base) + 0xA0))
#define QE_CRIMR(base)        ((VUINT32 *) ((base) + 0xA4))
#define QE_CICNR(base)        ((VUINT32 *) ((base) + 0xA8))
#define QE_CIPRTA(base)       ((VUINT32 *) ((base) + 0xB0))
#define QE_CIPRTB(base)       ((VUINT32 *) ((base) + 0xB4))
#define QE_CRIC(base)         ((VUINT32 *) ((base) + 0xBC))
#define QE_CHIVEC(base)       ((VUINT32 *) ((base) + 0xE0))


#ifndef _ASMLANGUAGE
typedef struct qe_intr_handler
    {
    VOIDFUNCPTR vec;    /* interrupt vector */
    int         arg;    /* interrupt handler argument */
    void        *pNext;
    } QE_INTR_HANDLER;

/* SIU Interrupt Mask structure; a value for the high and low parts */
typedef struct qe_siu_int_mask
    {
    UINT32  crimr;
    UINT32  cimr;
    } QE_SIU_INT_MASK;

/* function declarations */

IMPORT STATUS vxbQeIntrInit ();
extern STATUS vxbQeIntDisable (int );
IMPORT STATUS vxbQeIntEnable (int );
extern int qeIvecToInum(VOIDFUNCPTR *);
extern VOIDFUNCPTR * qeInumToIvec(int);
extern void vxbQeIntCtlrRegister(void);

#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbQeIntCtlrh */

