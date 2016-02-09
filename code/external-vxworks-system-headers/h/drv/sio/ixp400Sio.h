/* ixp400Sio.h - Intel IXP400 UART header file */

/*
Copyright (c) 2002-2004 Wind River Systems, Inc.  All rights reserved.
Certain portions of these files may be copyright (c) 2002-2004 Intel
Corporation.
*/

/*
modification history
--------------------
01e,25aug05,m_h  SIO for ixdp4xx XSCALE processors
01d,20jul05,m_h  serial driver for ixdp465 and related XSCALE BSPs
01c,20dec04,pai  Updated copyright notice.
01b,30jan03,jb3  Fix SPR 85040 Serialdata corruption.
01a,05jun02,jb  initial version...
*/

#ifndef __INCixp400Sioh 
#define __INCixp400Sioh 

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************
 *
 * Register descriptions
 *
 ******************************************************************************/

#ifndef _ASMLANGUAGE

/* Register offsets from base address */

#define RBR	(0x00)	/* receiver buffer register (read only) */
#define THR	(0x00)	/* transmit holding register (write only) */
#define IER	(0x01) 	/* interrupt enable register (r/w) */
#define IIR	(0x02)	/* interrupt identification register (read only) */
#define FCR	(0x02)	/* FIFO control register (write only) */
#define LCR	(0x03)	/* line control register (r/w) */
#define MCR	(0x04) 	/* modem control register (r/w) */
#define LSR	(0x05)	/* line status register (read only) */
#define MSR	(0x06)	/* modem status register (read only) */
#define SCR	(0x07)	/* scratch pad register (r/w) */
#define DLL	(0x00)	/* divisor latch lower byte (r/w) */
#define DLM	(0x01)	/* divisor latch upper bytes (r/w) */


/* Line Control Register */

#define CHAR_LEN_5	0x00	/* 5bit data length (default) */
#define CHAR_LEN_6	0x01	/* 6bit data length */
#define CHAR_LEN_7	0x02	/* 7bit data length */
#define CHAR_LEN_8	0x03	/* 8bit data length */
#define LCR_STB_1	0x00	/* 1 stop bit */
#define LCR_STB_2	0x04	/* 2 stop bits */
#define LCR_PEN		0x08	/* parity enable */
#define LCR_PDIS	0x00	/* parity disable */
#define LCR_EPS		0x10	/* even parity select */
#define LCR_STCKP	0x20	/* sticky parity select */
#define LCR_SBRK	0x40	/* set break control */
#define LCR_DLAB	0x80	/* divisor latch access enable */


/* Line Status Register */

#define LSR_DR		0x01	/* data ready */
#define LSR_OE		0x02	/* overrun error */
#define LSR_PE		0x04	/* parity error */
#define LSR_FE		0x08	/* framing error */
#define LSR_BI		0x10	/* break interrupt */
#define LSR_TDRQ	0x20	/* transmit data request */
#define LSR_TEMT	0x40	/* transmitter empty */
#define LSR_FIFOE	0x80	/* in FIFO mode, set when PE, FE or BI error */


/* Interrupt Enable Register */

#define IER_RAVIE	0x01	/* received data available int enable */
#define IER_TIE		0x02	/* transmitter data request int enable */
#define IER_RLSE 	0x04	/* receiver line status int enable */
#define IER_MIE		0x08	/* modem status int enable */
#define IER_RTOIE	0x10	/* receiver timeout int enable */
#define IER_NRZIE	0x20	/* NZR coding enable */
#define IER_UUE		0x40	/* UART Unit enable */
#define IER_DMAE	0x80	/* DMA Requests enable */


/* Interrupt Identification Register */

#define IIR_IP		0x00	/* interrupt pending */
#define IIR_RLS		0x06	/* received line status int */
#define IIR_RDA		0x04	/* received data available int */
#define IIR_TIMEOUT	0x0C	/* receive data timeout (FIFO mode only) */
#define IIR_THRE	0x02	/* transmit data request int */
#define IIR_MSTAT	0x00	/* modem status int */
#define IIR_FIFOES	0xC0	/* FIFO mode enable status */


/* Modem Control Register */

#define MCR_RTS		0x02	/* request to send output */
#define MCR_OUT1	0x04	/* output #1 */
#define MCR_OUT2	0x08	/* output #2 */
#define MCR_LOOP	0x10	/* loopback mode enable */

/* Modem Status Register */

#define MSR_DCTS	0x01	/* clear to send change */
#define MSR_CTS		0x10	/* complement of cts input */

/* FIFO Control Register */

#define FCR_TRFIFOE	0x01	/* enable xmit and rcvr FIFOs */
#define FCR_RESETRF	0x02	/* reset receiver FIFO */
#define FCR_RESETTF	0x04	/* reset trasmitter FIFO */
#define FCR_ITL_1	0x00	/* 1byte receiver trigger level */
#define FCR_ITL_8	0x40	/* 8byte receiver trigger level */
#define FCR_ITL_16	0x80	/* 16byte receiver trigger level */
#define FCR_ITL_32	0xC0	/* 32byte receiver trigger level */

/* 
 * Max iterations for servicing chars during ISR. This value should not be greater 
 * than 32 i.e. half the UART FIFO size.
 * #define IXP400_SIO_MAX_CNT 30
 */
#define IXP400_SIO_MAX_CNT 32
#define IXP400_SIO_MAX_RX_CNT 63
#define IXP400_SIO_MAX_TX_CNT 31


typedef  struct 	/* IXP400_SIO_CHAN */
    {
    /* always goes first */

    SIO_DRV_FUNCS *     pDrvFuncs;      /* driver functions */

    /* callbacks */
    void *      getTxArg;
    void *      putRcvArg;
    STATUS      (*getTxChar) (); /* pointer to xmitr function */	
    STATUS      (*putRcvChar) (); /* pointer to rcvr function */

    UINT8 	*regs;		/* IXP400 UART registers */
    UINT8 	level;		/* 8259a interrupt level for this device */
    UINT8 	ier;		/* copy of ier */
    UINT8 	lcr;		/* copy of lcr */
    UINT8 	mcr;		/* copy of mcr */

    UINT16      channelMode;	/* such as INT, POLL modes */
    UINT16      regDelta;	/* register address spacing */
    int         baudRate;
    UINT32      xtal;		/* UART clock frequency     */     
    UINT32	options;	/* hardware setup options */

#ifdef IXP400_SIO_DEBUG
    UINT32	rxCount;	/* UART statistics counters */
    UINT32	txCount;
    UINT32	overrunErr;
    UINT32	parityErr;
    UINT32	framingErr;
    UINT32	breakErr;
#endif

    } IXP400_SIO_CHAN;

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern void ixp400SioInt (IXP400_SIO_CHAN *);
extern void ixp400SioDevInit (IXP400_SIO_CHAN *);
extern void ixp400SioStatsShow (IXP400_SIO_CHAN *);

#else

extern void ixp400SioInt ();
extern void ixp400SioInit ();
extern void ixp400SioStatsShow ();

#endif  /* __STDC__ */

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif
 
#endif /* __INCixp400Sioh */
