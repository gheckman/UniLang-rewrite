/* quiccIntrCtl.h - PowerQuicc interrupt controller header file */

/* Copyright (c) 2005-2007 Wind River Systems, Inc. */

/*
modification history
--------------------
01c,05sep07,dtr  WIND0045894 - INUM_CPIO1 to INUM_GPIO1.
01b,09may06,dtr  Add 8360 support.
01a,10jan05,dtr  adapted from m85xxIntrCtl.
*/

#ifndef __INCquiccIntrCtlh
#define __INCquiccIntrCtlh

#include "vxWorks.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef  _ASMLANGUAGE
#define CAST(x)
#else /* _ASMLANGUAGE */
#define CAST(x) (x)
#endif  /* _ASMLANGUAGE */

#ifdef IVEC_TO_INUM
# undef IVEC_TO_INUM
#endif /* IVEC_TO_INUM */

#ifdef INUM_TO_IVEC
# undef INUM_TO_IVEC
#endif /* INUM_TO_IVEC */

#define IVEC_TO_INUM(intVec)    (quiccIvecToInum(intVec))
#define INUM_TO_IVEC(intNum)    (quiccInumToIvec(intNum))

#ifdef PQ2PRO
#define INUM_UART1         9
#define INUM_UART2        10
#define INUM_SEC          11
#define INUM_I2C1         14
#define INUM_I2C2         15
#define INUM_SPI          16
#define INUM_IRQ1         17
#define INUM_IRQ2         18
#define INUM_IRQ3         19
#define INUM_IRQ4         20
#define INUM_IRQ5         21
#define INUM_IRQ6         22
#define INUM_IRQ7         23
#define INUM_TSEC1_TX     32
#define INUM_TSEC1_RX     33
#define INUM_TSEC1_ERR    34
#define INUM_TSEC2_TX     35
#define INUM_TSEC2_RX     36
#define INUM_TSEC2_ERR    37
#define INUM_USB2_DR      38
#define INUM_USB2_MPH     39
#define INUM_IRQ0         48
#define INUM_RTC_SEC      64
#define INUM_PIT          65
#define INUM_PCI1         66
#define INUM_PCI2         67
#define INUM_RTC_ALR      68 
#define INUM_MU           69
#define INUM_SBA          70
#define INUM_DMA          71
#define INUM_GTM4         72
#define INUM_GTM8         73
#define INUM_GPIO1        74
#define INUM_GPIO2        75
#define INUM_DDR          76
#define INUM_LBC          77
#define INUM_GTM2         78
#define INUM_GTM6         79
#define INUM_PMC          80
#define INUM_GTM3         84
#define INUM_GTM7         85
#define INUM_GTM1         90
#define INUM_GTM5         91

#define INUM_MAX		128
#define IVEC_MAX		128

#endif

#ifdef PQ2PRO_QE
#define INUM_UART1         9
#define INUM_UART2        10
#define INUM_SEC          11
#define INUM_I2C1         14
#define INUM_I2C2         15
#define INUM_IRQ1         17
#define INUM_IRQ2         18
#define INUM_IRQ3         19
#define INUM_IRQ4         20
#define INUM_IRQ5         21
#define INUM_IRQ6         22
#define INUM_IRQ7         23
#define INUM_QE_HIGH      32
#define INUM_QE_LOW       33

#define INUM_IRQ0         48
#define INUM_RTC_SEC      64 /* ??? */
#define INUM_PIT          65 /* ??? */
#define INUM_PCI1         66
#define INUM_RTC_ALR      68 
#define INUM_MU           69
#define INUM_SBA          70
#define INUM_DMA          71
#define INUM_GTM4         72
#define INUM_GTM8         73
#define INUM_QE_PORTS     74
#define INUM_SDDR         75
#define INUM_DDR          76
#define INUM_LBC          77
#define INUM_GTM2         78
#define INUM_GTM6         79
#define INUM_PMC          80
#define INUM_GTM3         84
#define INUM_GTM7         85
#define INUM_GTM1         90
#define INUM_GTM5         91

#define INUM_MAX		128
#define IVEC_MAX		128

#endif

/* Interrupt Controller Registers */

#define	QUICC_SICR(base)	((VINT32 *) ((base) + SIC_REG_BA + 0x000))
#define	QUICC_SIVEC(base)	((VINT32 *) ((base) + SIC_REG_BA + 0x004))
#define	QUICC_SIPNR_H(base)	((VINT32 *) ((base) + SIC_REG_BA + 0x008))
#define	QUICC_SIPNR_L(base)	((VINT32 *) ((base) + SIC_REG_BA + 0x00C))

#define	QUICC_SIPRR_A(base)	((VINT32 *) ((base) + SIC_REG_BA + 0x010))

#define	QUICC_SIPRR_D(base)	((VINT32 *) ((base) + SIC_REG_BA + 0x01C))

#define	QUICC_SIMR_H(base)	((VINT32 *) ((base) + SIC_REG_BA + 0x020))
#define	QUICC_SIMR_L(base)	((VINT32 *) ((base) + SIC_REG_BA + 0x024))

#define	QUICC_SICNR(base)	((VINT32 *) ((base) + SIC_REG_BA + 0x028))
#define	QUICC_SEPNR(base)	((VINT32 *) ((base) + SIC_REG_BA + 0x02C))
#define	QUICC_SMPRR_A(base)	((VINT32 *) ((base) + SIC_REG_BA + 0x030))
#define	QUICC_SMPRR_B(base)	((VINT32 *) ((base) + SIC_REG_BA + 0x034))

#define	QUICC_SEMSR(base)	((VINT32 *) ((base) + SIC_REG_BA + 0x038))
#define	QUICC_SECNR(base)	((VINT32 *) ((base) + SIC_REG_BA + 0x03C))

#define	QUICC_SERSR(base)	((VINT32 *) ((base) + SIC_REG_BA + 0x040))
#define	QUICC_SERMR(base)	((VINT32 *) ((base) + SIC_REG_BA + 0x044))
#define	QUICC_SERCR(base)	((VINT32 *) ((base) + SIC_REG_BA + 0x048))


#define	QUICC_SIFCR_H(base)	((VINT32 *) ((base) + SIC_REG_BA + 0x050))
#define	QUICC_SIFCR_L(base)	((VINT32 *) ((base) + SIC_REG_BA + 0x054))
#define	QUICC_SEFCR(base)	((VINT32 *) ((base) + SIC_REG_BA + 0x058))
#define	QUICC_SERFR(base)	((VINT32 *) ((base) + SIC_REG_BA + 0x05C))
#define	QUICC_SCVCR(base)	((VINT32 *) ((base) + SIC_REG_BA + 0x060))
#define	QUICC_SMVCR(base)	((VINT32 *) ((base) + SIC_REG_BA + 0x064))

/* interrupt handler */

#ifndef _ASMLANGUAGE
typedef struct intr_handler
    {
    VOIDFUNCPTR vec;    /* interrupt vector */
    int         arg;    /* interrupt handler argument */
    void        *pNext;
    } INTR_HANDLER;


/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

IMPORT STATUS quiccIntrInit ();
extern STATUS quiccIntDisable (int );
IMPORT STATUS quiccIntEnable (int );
extern int quiccIvecToInum(VOIDFUNCPTR *);
extern VOIDFUNCPTR * quiccInumToIvec(int);

#else

IMPORT STATUS quiccIntrInit ();
extern STATUS quiccIntDisable ();
IMPORT STATUS quiccIntEnable ();
extern int quiccIvecToInum();
extern VOIDFUNCPTR * quiccInumToIvec();

#endif	/* __STDC__ */
#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCquiccIntrCtlh */
