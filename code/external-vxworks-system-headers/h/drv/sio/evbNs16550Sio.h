/* evbNs16550Sio.h - header file for binary interface NS 16550 UART driver */

/* Copyright 1984-1996, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01c,29apr10,pad  Moved extern C statement after include statements.
01b,02dec97,db   changed type from char to UCHAR for element outByte() in 
		 EVBNS16550_CHAN structure for compatibility with sysLib.h.
01a,07mar96,tam  written (from i8250Sio.h)
*/

#ifndef	__INCevbNs16550Sioh
#define	__INCevbNs16550Sioh


#ifndef _ASMLANGUAGE

#include "vxWorks.h"
#include "sioLib.h"

#ifdef __cplusplus
extern "C" {
#endif

/* channel data structure  */

typedef struct EVBNS16550_CHAN
    {
    SIO_DRV_FUNCS * pDrvFuncs;       /* driver functions */

    STATUS      (*getTxChar) ();
    STATUS      (*putRcvChar) ();
    void *      getTxArg;
    void *      putRcvArg;

    UINT16  int_vec;                 /* interrupt vector number */
    UINT16  channelMode;             /* SIO_MODE_[INT | POLL] */
    UCHAR   (*inByte) (ULONG);       /* routine to read a byte from register */
    void    (*outByte)(ULONG,UCHAR); /* routine to write a byte to register */

    UINT32  clkFreq;                 /* baud rate generator clock */
    int     baudRate;                /* baud rate */

    ULONG   lcr;                     /* UART line control register */
    ULONG   lst;                     /* UART line status register */
    ULONG   mdc;                     /* UART modem control register */
    ULONG   msr;                     /* UART modem status register */
    ULONG   ier;                     /* UART interrupt enable register */
    ULONG   iid;                     /* UART interrupt ID register */
    ULONG   brdl;                    /* UART baud rate register */
    ULONG   brdh;                    /* UART baud rate register */
    ULONG   data;                    /* UART data register */
    } EVBNS16550_CHAN;

/* register definitions */

#define UART_THR        0x00	/* Transmitter holding reg. */
#define UART_RDR        0x00	/* Receiver data reg.       */
#define UART_BRDL       0x00	/* Baud rate divisor (LSB)  */
#define UART_BRDH       0x01	/* Baud rate divisor (MSB)  */
#define UART_IER        0x01	/* Interrupt enable reg.    */
#define UART_IID        0x02	/* Interrupt ID reg.        */
#define UART_LCR        0x03	/* Line control reg.        */
#define UART_MDC        0x04	/* Modem control reg.       */
#define UART_LST        0x05	/* Line status reg.         */
#define UART_MSR        0x06	/* Modem status reg.        */

#if defined(__STDC__) || defined(__cplusplus)

extern void evbNs16550HrdInit(EVBNS16550_CHAN *pDev);
extern void evbNs16550Int (EVBNS16550_CHAN  *pDev);

#else

extern void evbNs16550HrdInit();
extern void evbNs16550Int();
	     
#endif  /* __STDC__ */

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif	/* __INCevbNs16550Sioh */
