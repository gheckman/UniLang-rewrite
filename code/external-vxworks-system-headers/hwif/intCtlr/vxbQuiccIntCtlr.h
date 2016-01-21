/* vxbQuiccIntCtlr.h - PowerQuicc interrupt controller header file */

/*
 * Copyright (c) 2005, 2008, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,29jul10,pad  Moved extern C statement after include statements.
01b,21feb08,x_s  Support 8377 version of interrupt controller.
01a,10jan05,dtr  created from quiccIntrCtl.h/01b.
*/

#ifndef __INCvxbQuiccIntCtlrh
#define __INCvxbQuiccIntCtlrh

#include <vxWorks.h>

#ifdef  _ASMLANGUAGE
#define CAST(x)
#else /* _ASMLANGUAGE */
#include <vxBusLib.h>
#define CAST(x) (x)
#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef IVEC_TO_INUM
# undef IVEC_TO_INUM
#endif /* IVEC_TO_INUM */

#ifdef INUM_TO_IVEC
# undef INUM_TO_IVEC
#endif /* INUM_TO_IVEC */

#define IVEC_TO_INUM(intVec)    (quiccIvecToInum(intVec))
#define INUM_TO_IVEC(intNum)    (quiccInumToIvec(intNum))

#ifndef _ASMLANGUAGE
#define CAST(x) (x)
#ifndef VUINT32
typedef volatile UINT32 VUINT32; /* volatile unsigned word */
#endif
#else
#define CAST(x) 
#endif



#define QUICC_IVEC_MAX 128
/* Interrupt Controller Registers */

#define	QUICC_SICR(base)	((VUINT32 *) ((base) + 0x000))
#define	QUICC_SIVEC(base)	((VUINT32 *) ((base) + 0x004))
#define	QUICC_SIPNR_H(base)	((VUINT32 *) ((base) + 0x008))
#define	QUICC_SIPNR_L(base)	((VUINT32 *) ((base) + 0x00C))

#define	QUICC_SIPRR_A(base)	((VUINT32 *) ((base) + 0x010))

#define	QUICC_SIPRR_D(base)	((VUINT32 *) ((base) + 0x01C))

#define	QUICC_SIMR_H(base)	((VUINT32 *) ((base) + 0x020))
#define	QUICC_SIMR_L(base)	((VUINT32 *) ((base) + 0x024))

#define	QUICC_SICNR(base)	((VUINT32 *) ((base) + 0x028))
#define	QUICC_SEPNR(base)	((VUINT32 *) ((base) + 0x02C))
#define	QUICC_SMPRR_A(base)	((VUINT32 *) ((base) + 0x030))
#define	QUICC_SMPRR_B(base)	((VUINT32 *) ((base) + 0x034))

#define	QUICC_SEMSR(base)	((VUINT32 *) ((base) + 0x038))
#define	QUICC_SECNR(base)	((VUINT32 *) ((base) + 0x03C))

#define	QUICC_SERSR(base)	((VUINT32 *) ((base) + 0x040))
#define	QUICC_SERMR(base)	((VUINT32 *) ((base) + 0x044))
#define	QUICC_SERCR(base)	((VUINT32 *) ((base) + 0x048))
#define	QUICC_SEPCR(base)	((VUINT32 *) ((base) + 0x04C))



#define	QUICC_SIFCR_H(base)	((VUINT32 *) ((base) + 0x050))
#define	QUICC_SIFCR_L(base)	((VUINT32 *) ((base) + 0x054))
#define	QUICC_SEFCR(base)	((VUINT32 *) ((base) + 0x058))
#define	QUICC_SERFR(base)	((VUINT32 *) ((base) + 0x05C))
#define	QUICC_SCVCR(base)	((VUINT32 *) ((base) + 0x060))
#define	QUICC_SMVCR(base)	((VUINT32 *) ((base) + 0x064))

#define QUICC_MSIR0(base)       ((VUINT32 *) ((base) + 0x0C0))
#define QUICC_MSIR1(base)       ((VUINT32 *) ((base) + 0x0C4))
#define QUICC_MSIR2(base)       ((VUINT32 *) ((base) + 0x0C8))
#define QUICC_MSIR3(base)       ((VUINT32 *) ((base) + 0x0CC))
#define QUICC_MSIR4(base)       ((VUINT32 *) ((base) + 0x0D0))
#define QUICC_MSIR5(base)       ((VUINT32 *) ((base) + 0x0D4))
#define QUICC_MSIR6(base)       ((VUINT32 *) ((base) + 0x0D8))
#define QUICC_MSIR7(base)       ((VUINT32 *) ((base) + 0x0DC))

#define QUICC_MSIMR(base)       ((VUINT32 *) ((base) + 0x0F0))
#define QUICC_MSISR(base)       ((VUINT32 *) ((base) + 0x0F4))
#define QUICC_MSIIR(base)       ((VUINT32 *) ((base) + 0x0F8))

/* interrupt handler */

#ifndef _ASMLANGUAGE
typedef struct intr_handler
    {
    VOIDFUNCPTR vec;    /* interrupt vector */
    int         arg;    /* interrupt handler argument */
    void        *pNext;
    } INTR_HANDLER;

typedef struct siu_int_mask
    {
    UINT32  simr_h;
    UINT32  simr_l;
    UINT32  semr;
    } SIU_INT_MASK;

/* function declarations */

IMPORT STATUS vxbSysQuiccIntrInit (VXB_DEVICE_ID pInst);
extern STATUS vxbSysQuiccIntDisable (int );
IMPORT STATUS vxbSysQuiccIntEnable (int );
extern int quiccIvecToInum(VOIDFUNCPTR *);
extern VOIDFUNCPTR * quiccInumToIvec(int);
extern void vxbQuiccIntCtlrRegister(void);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbQuiccIntCtlrh */
