/* rm9000x2glSio.h - rm9000x2gl  DUART header file */

/* Copyright 2005, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01c,29apr10,pad  Moved extern C statement after include statements.
01b,13apr05,rlg  fix for misplacement of assembly if def, discoverd in build of bootroms
01a,05apr05,rlg  created for rm9000x2gl (yosemite). Created from the
                 wind river ns16552Sio.h file, version 01f,07sep04.
*/

#ifndef __INCrm9000x2glSioh 
#define __INCrm9000x2glSioh 

/*
 *********************************************************************
 * 		Copyright (c) 1990,1991 Intel Corporation
 *
 * Intel hereby grants you permission to copy, modify, and
 * distribute this software and its documentation.  Intel grants
 * this permission provided that the above copyright notice
 * appears in all copies and that both the copyright notice and
 * this permission notice appear in supporting documentation.  In
 * addition, Intel grants this permission provided that you
 * prominently mark as not part of the original any modifications
 * made to this software or documentation, and that the name of
 * Intel Corporation not be used in advertising or publicity
 * pertaining to distribution of the software or the documentation
 * without specific, written prior permission.
 *
 * Intel Corporation does not warrant, guarantee or make any
 * representations regarding the use of, or the results of the use
 * of, the software and documentation in terms of correctness,
 * accuracy, reliability, currentness, or otherwise; and you rely
 * on the software, documentation and results solely at your own risk.
 *
 *\NOMANUAL
 **********************************************************************
*/

/*
 ******************************************************************************
 *
 * REGISTER DESCRIPTION OF RM9000x2gl  DUART
 *
 * $Id: rm9000x2gl.h,v 1.0 1993/06/07 15:07:59 wise active $
 *
 *\NOMANUAL
 *******************************************************************************
*/


/* Register offsets from base address */

#define RBR             0x08    /* receiver buffer register */
#define THR             0x0C    /* transmit holding register */
#define DLL             0x10    /* divisor latch */
#define IER             0x14    /* interrupt enable register */
#define DLM             0x18    /* divisor latch(MS) */
#define IIR             0x1C    /* interrupt identification register */
#define FCR             0x20    /* FIFO control register */
#define LCR             0x24    /* line control register */
#define MCR             0x28    /* modem control register */
#define LSR             0x2C    /* line status register */
#define MSR             0x30    /* modem status register */
#define SCR             0x34    /* scratch register */

#define BAUD_LO(baud)  ((XTAL/(16*baud)) & 0xff)
#define BAUD_HI(baud)  (((XTAL/(16*baud)) & 0xff00) >> 8)

/* Line Control Register */

#define CHAR_LEN_5	0x00	/* 5bits data size */
#define CHAR_LEN_6	0x01	/* 6bits data size */
#define CHAR_LEN_7	0x02	/* 7bits data size */
#define CHAR_LEN_8	0x03	/* 8bits data size */
#define LCR_STB		0x04	/* 2 stop bits */
#define ONE_STOP	0x00	/* one stop bit */
#define LCR_PEN		0x08	/* parity enable */
#define PARITY_NONE	0x00	/* parity disable */
#define LCR_EPS		0x10	/* even parity select */
#define LCR_SP		0x20	/* stick parity select */
#define LCR_SBRK	0x40	/* break control bit */
#define LCR_DLAB	0x80	/* divisor latch access enable */
#define DLAB		LCR_DLAB

/* Line Status Register */

#define LSR_DR		0x01	/* data ready */
#define RxCHAR_AVAIL	LSR_DR	/* data ready */
#define LSR_OE		0x02	/* overrun error */
#define LSR_PE		0x04	/* parity error */
#define LSR_FE		0x08	/* framing error */
#define LSR_BI		0x10	/* break interrupt */
#define LSR_THRE	0x20	/* transmit holding register empty */
#define LSR_TEMT	0x40	/* transmitter empty */
#define LSR_FERR	0x80	/* in fifo mode, set when PE,FE or BI error */

/* Interrupt Identification Register */

#define IIR_IP		0x01
#define IIR_ID		0x0e
#define IIR_RLS		0x06	/* received line status */
#define Rx_INT		IIR_RLS /* received line status */
#define IIR_RDA		0x04	/* received data available */
#define RxFIFO_INT	IIR_RDA /* received data available */
#define IIR_THRE	0x02	/* transmit holding register empty */
#define TxFIFO_INT	IIR_THRE 
#define IIR_MSTAT	0x00	/* modem status */
#define IIR_TIMEOUT	0x0c	/* char receive timeout */

/* Interrupt Enable Register */

#define IER_ERDAI	0x01	/* received data avail. & timeout int */
#define RxFIFO_BIT	IER_ERDAI
#define IER_ETHREI	0x02	/* transmitter holding register empty int */
#define TxFIFO_BIT	IER_ETHREI
#define IER_ELSI	0x04	/* receiver line status int enable */
#define Rx_BIT		IER_ELSI
#define IER_EMSI	0x08	/* modem status int enable */

/* Modem Control Register */

#define MCR_DTR		0x01	/* dtr output */
#define DTR		MCR_DTR
#define MCR_RTS		0x02	/* rts output */
#define MCR_OUT1	0x04	/* output #1 */
#define MCR_OUT2	0x08	/* output #2 */
#define MCR_LOOP	0x10	/* loopback enable */

/* Modem Status Register */

#define MSR_DCTS	0x01	/* cts change */
#define MSR_DDSR	0x02	/* dsr change */
#define MSR_TERI	0x04	/* ring indicator change */
#define MSR_DDCD	0x08	/* data carrier indicator change */
#define MSR_CTS		0x10	/* complement of cts */
#define MSR_DSR		0x20	/* complement of dsr */
#define MSR_RI		0x40	/* complement of ring signal */
#define MSR_DCD		0x80	/* complement of dcd */ 

/* FIFO Control Register */

#define FCR_EN		0x01	/* enable xmit and rcvr */
#define FIFO_ENABLE	FCR_EN
#define FCR_RXCLR	0x02	/* clears rcvr fifo */
#define RxCLEAR		FCR_RXCLR
#define FCR_TXCLR	0x04	/* clears xmit fifo */
#define TxCLEAR		FCR_TXCLR
#define FCR_DMA		0x08	/* dma */
#define FCR_RXTRIG_L	0x40	/* rcvr fifo trigger lvl low */
#define FCR_RXTRIG_H	0x80	/* rcvr fifo trigger lvl high */

#ifndef _ASMLANGUAGE

#include "sioLib.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef  struct 	/* RM9000x2gl_CHAN * */
    {
    /* always goes first */

    SIO_DRV_FUNCS *     pDrvFuncs;      /* driver functions */

    /* callbacks */

    STATUS      (*getTxChar) (); /* pointer to xmitr function */	
    STATUS      (*putRcvChar) (); /* pointer to rcvr function */
    void *      getTxArg;
    void *      putRcvArg;

    UINT8 	*regs;		/* RM9000x2gl  registers */
    UINT8 	level;		/* 8259a interrupt level for this device */
    UINT8 	ier;		/* copy of ier */
    UINT8 	lcr;		/* copy of lcr, not used by rm9000x2gl driver */
    UINT8 	mcr;		/* copy of modem control register */
    UINT8 	pad1;

    UINT16      channelMode;	/* such as INT, POLL modes */
    UINT16      regDelta;	/* register address spacing */
    int         baudRate;
    UINT32      xtal;		/* UART clock frequency     */     
    UINT32	options;	/* hardware setup options */

    } RM9000x2gl_CHAN;

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern void rm9000x2glInt (RM9000x2gl_CHAN *);
extern void rm9000x2glDevInit (RM9000x2gl_CHAN *);

#else

extern void rm9000x2glInt ();
extern void rm9000x2glDevInit ();

#endif  /* __STDC__ */

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif
 
#endif /* __INCrm9000x2glSioh */
