/* qeIntrCtl.h - Quicc Engine interrupt controller header file */

/* Copyright (c)  Wind River Systems, Inc. */

/*
modification history
--------------------
01a,10jan05,dtr  adapted from m85xxIntrCtl.
*/

#ifndef __INCqeIntrCtlh
#define __INCqeIntrCtlh

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

/* This offset used to allow intConnect/Enable etc to direct a call to the 
 * quiccEngine controller vs the e300 or e500 interrupt controller 
 * append this to int<func> call vector/intNum.
 * eg intEnable(QE_INUM_UCC1 + QE_INUM_OFFSET)
 */
#define QE_INUM_OFFSET    IVEC_MAX
   
#define QE_INUM_ERROR           0
#define QE_INUM_SPI2            1
#define QE_INUM_SPI1            2
#define QE_INUM_RTT             3
#define QE_INUM_SDMA            10
#define QE_INUM_USB             11
#define QE_INUM_TIMER1          12
#define QE_INUM_TIMER2          13
#define QE_INUM_TIMER3          14          
#define QE_INUM_TIMER4          15          
#define QE_INUM_VT              20
#define QE_INUM_EXT1            25
#define QE_INUM_EXT2            26                      
#define QE_INUM_EXT3            27           
#define QE_INUM_EXT4            28
#define QE_INUM_UCC1            32
#define QE_INUM_UCC2            33          
#define QE_INUM_UCC3            34           
#define QE_INUM_UCC4            35           
#define QE_INUM_MCC1            36           
#define QE_INUM_UCC5            40           
#define QE_INUM_UCC6            41
#define QE_INUM_UCC7            42           
#define QE_INUM_UCC8            43           

#define QE_INUM_MAX		64
#define QE_IVEC_MAX		64

#if 0

#define QE_CICR         0x80 /* interrupt configuration Register */
#define QE_CIVEC        0x84 
#define QE_CRIPNR       0x88
#define QE_CIPNR        0x8C
#define QE_CIPXCC       0x90
#define QE_CIPYCC       0x94
#define QE_CIPWCC       0x98
#define QE_CIPZCC       0x9C
#define QE_CIMR         0xA0
#define QE_CRIMR        0xA4
#define QE_CICNR        0xA8
#define QE_CIPRTA       0xB0
#define QE_CIPRTB       0xB4
#define QE_CRIC         0xBC
#define QE_CHIVEC       0xE0

#else

#define QE_CICR(base)         ((VUINT32 *) ((base) + QUICC_ENGINE_BA + 0x80)) /* interrupt configuration Register */
#define QE_CIVEC(base)        ((VUINT32 *) ((base) + QUICC_ENGINE_BA + 0x84)) 
#define QE_CRIPNR(base)       ((VUINT32 *) ((base) + QUICC_ENGINE_BA + 0x88))
#define QE_CIPNR(base)        ((VUINT32 *) ((base) + QUICC_ENGINE_BA + 0x8C))
#define QE_CIPXCC(base)       ((VUINT32 *) ((base) + QUICC_ENGINE_BA + 0x90))
#define QE_CIPYCC(base)       ((VUINT32 *) ((base) + QUICC_ENGINE_BA + 0x94))
#define QE_CIPWCC(base)       ((VUINT32 *) ((base) + QUICC_ENGINE_BA + 0x98))
#define QE_CIPZCC(base)       ((VUINT32 *) ((base) + QUICC_ENGINE_BA + 0x9C))
#define QE_CIMR(base)         ((VUINT32 *) ((base) + QUICC_ENGINE_BA + 0xA0))
#define QE_CRIMR(base)        ((VUINT32 *) ((base) + QUICC_ENGINE_BA + 0xA4))
#define QE_CICNR(base)        ((VUINT32 *) ((base) + QUICC_ENGINE_BA + 0xA8))
#define QE_CIPRTA(base)       ((VUINT32 *) ((base) + QUICC_ENGINE_BA + 0xB0))
#define QE_CIPRTB(base)       ((VUINT32 *) ((base) + QUICC_ENGINE_BA + 0xB4))
#define QE_CRIC(base)        ((VUINT32 *) ((base) + QUICC_ENGINE_BA + 0xBC))
#define QE_CHIVEC(base)       ((VUINT32 *) ((base) + QUICC_ENGINE_BA + 0xE0))

#endif

#ifndef _ASMLANGUAGE
typedef struct qe_intr_handler
    {
    VOIDFUNCPTR vec;    /* interrupt vector */
    int         arg;    /* interrupt handler argument */
    void        *pNext;
    } QE_INTR_HANDLER;


/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

IMPORT STATUS qeIntrInit ();
extern STATUS qeIntDisable (int );
IMPORT STATUS qeIntEnable (int );
extern int qeIvecToInum(VOIDFUNCPTR *);
extern VOIDFUNCPTR * qeInumToIvec(int);

#else

IMPORT STATUS qeIntrInit ();
extern STATUS qeIntDisable ();
IMPORT STATUS qeIntEnable ();
extern int qeIvecToInum();
extern VOIDFUNCPTR * qeInumToIvec();

#endif	/* __STDC__ */
#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCqeIntrCtlh */

