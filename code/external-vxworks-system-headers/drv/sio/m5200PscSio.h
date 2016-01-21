/* m5200PscSio.h - Motorola MPC5200 internal UART header file */

/* Copyright 1984-2003, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01d,29apr10,pad  Moved extern C statement after include statements.
01c,25Jun03,pkr	 created
*/

/*
This file contains constants for the UART contained in the Motorola MCF5200.
The constant SIO must defined when
including this header file.
*/

#ifndef __INCm5200PscSioh
#define __INCm5200PscSioh

#ifndef	_ASMLANGUAGE

#include "sioLib.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct		
    {
    SIO_DRV_FUNCS  * pDrvFuncs;	/* Driver functions */
				/* CallBacks */
    STATUS   (*getTxChar)();
    STATUS   (*putRcvChar)();
    void *   getTxArg;
    void *   putRcvArg;
    
    UINT		clkRate;	/* system clock rate */
    UINT16		mode;		/* SIO_MODE */
    VOIDFUNCPTR *intVec;
    int			options;
    int			intEnable;
    UINT		baudRate;
    UCHAR		acrCopy;
    USHORT		imrCopy;
    int			portNum;

    volatile UCHAR	*mr;	/* UART mode register */
    volatile USHORT	*sr;	/* UART status register */
    volatile USHORT	*csr;	/* UART clock select register */
    volatile UCHAR	*cr;	/* UART command register */
    volatile ULONG	*rb;	/* UART receive buffer register */
    volatile UCHAR	*tb;	/* UART transmit buffer register */
    volatile UCHAR	*ipcr;	/* UART input port change register */
    volatile UCHAR	*acr;	/* UART auxiliary control register */
    volatile USHORT	*isr;	/* UART interrupt status register */
    volatile USHORT	*imr;	/* UART interrupt mask register */
#if 0
    volatile UCHAR	*ivr;	/* UART interrupt vector register */
#endif
   volatile UCHAR	*op1;	/* UART output port set cmd */
   volatile UCHAR	*sicr;	/* UART ??? */
   volatile UCHAR	*dp;	/* UART divisor high */
   volatile UCHAR	*dl;	/* UART divisor low */
   volatile USHORT	*rfalarm;	/* UART ??? */
   volatile USHORT	*tfalarm;	/* UART ??? */
    } M5200_PSC_CHAN;

#endif	/* _ASMLANGUAGE */

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

IMPORT	void	m5200PscSioDevInit (M5200_PSC_CHAN *pChan);
IMPORT	void	m5200PscSioDevInit2 (M5200_PSC_CHAN *pChan);
IMPORT  void    m5200PscSioInt (M5200_PSC_CHAN *pChan);

#else	/* __STDC__ */

IMPORT	void	m5200PscSioDevInit ();
IMPORT	void	m5200PscSioDevInit2 ();
IMPORT  void    m5200PscSioInt ();

#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCm5200PscSioh */
