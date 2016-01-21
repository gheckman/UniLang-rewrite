/* mcfUart.h - coldfire UART device header */

/*
 * Copyright (c) 2007 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01a,10dec07,rec	 created
*/

#ifndef __INCmcfUart
#define __INCmcfUart

/* register offset values */

#define COLDFIRE_UART_MR		0
#define COLDFIRE_UART_SR		4
#define COLDFIRE_UART_CSR		4
#define COLDFIRE_UART_CR		8
#define COLDFIRE_UART_RB		0x0C
#define COLDFIRE_UART_TB		0x0C
#define COLDFIRE_UART_IPCR		0x10
#define COLDFIRE_UART_ACR		0x10
#define COLDFIRE_UART_ISR		0x14
#define COLDFIRE_UART_IMR		0x14
#define COLDFIRE_UART_CTUR		0x18
#define COLDFIRE_UART_CTLR		0x1C
#define COLDFIRE_UART_IP		0x34
#define COLDFIRE_UART_OPSET		0x38
#define COLDFIRE_UART_OPRESET		0x3C
#define COLDFIRE_UART_SICR		0x40

/* register bit definitions */

/* MR1 - mode register 1 */

#define COLDFIRE_UART_MR1_BC0	(1 << 0)	/* bits per char 0 */
#define COLDFIRE_UART_MR1_BC1	(1 << 1)	/* bits per char 1 */
#define COLDFIRE_UART_MR1_PT	(1 << 2)	/* parity type */
#define COLDFIRE_UART_MR1_PM0	(1 << 3)	/* parity mode 0 */
#define COLDFIRE_UART_MR1_PM1	(1 << 4)	/* parity mode 1 */
#define COLDFIRE_UART_MR1_ERR	(1 << 5)	/* error mode */
#define COLDFIRE_UART_MR1_RX_IRQ (1 << 6)       /* receiver interrupt select */
#define COLDFIRE_UART_MR1_RX_RTS (1 << 7)	/* Rx RTS control */

/* Some common modes */

#define COLDFIRE_UART_MR1_BITS_CHAR_5	0
#define COLDFIRE_UART_MR1_BITS_CHAR_6	COLDFIRE_UART_MR1_BC0
#define COLDFIRE_UART_MR1_BITS_CHAR_7	COLDFIRE_UART_MR1_BC1
#define COLDFIRE_UART_MR1_BITS_CHAR_8	(COLDFIRE_UART_MR1_BC0 \
					 | COLDFIRE_UART_MR1_BC1)
#define COLDFIRE_UART_MR1_NO_PARITY	(COLDFIRE_UART_MR1_PM1)
#define COLDFIRE_UART_MR1_PAR_MODE_MULTI	(COLDFIRE_UART_MR1_PM0 \
					 | COLDFIRE_UART_MR1_PM1)
#define COLDFIRE_UART_MR1_EVEN_PARITY	0
#define COLDFIRE_UART_MR1_ODD_PARITY	COLDFIRE_UART_MR1_PT

/* MR2 - mode register 2 */

#define COLDFIRE_UART_MR2_SB0	(1 << 0)	/* stop bit control 0 */
#define COLDFIRE_UART_MR2_SB1	(1 << 1)	/* stop bit control 1 */
#define COLDFIRE_UART_MR2_SB2	(1 << 2)	/* stop bit control 2 */
#define COLDFIRE_UART_MR2_SB3	(1 << 3)	/* stop bit control 3 */
#define COLDFIRE_UART_MR2_TX_CTS	(1 << 4)	/* Tx CTS control */
#define COLDFIRE_UART_MR2_TX_RTS	(1 << 5)	/* Tx RTS control */
#define COLDFIRE_UART_MR2_CM0	(1 << 6)	/* channel mode 0 */
#define COLDFIRE_UART_MR2_CM1	(1 << 7)	/* channel mode 1 */

/* Some common bit lengths */

#define COLDFIRE_UART_MR2_STOP_BITS_1	(COLDFIRE_UART_MR2_SB0 \
					 | COLDFIRE_UART_MR2_SB1 \
					 | COLDFIRE_UART_MR2_SB2)
#define COLDFIRE_UART_MR2_STOP_BITS_2	(COLDFIRE_UART_MR2_SB0 \
					 | COLDFIRE_UART_MR2_SB1 \
					 | COLDFIRE_UART_MR2_SB2 \
					 | COLDFIRE_UART_MR2_SB3)

/* SR - status register */

#define COLDFIRE_UART_SR_RXRDY	(1 << 0)	/* Rx ready */
#define COLDFIRE_UART_SR_FFULL	(1 << 1)	/* FIFO full */
#define COLDFIRE_UART_SR_TXRDY	(1 << 2)	/* Tx ready */
#define COLDFIRE_UART_SR_TXEMP	(1 << 3)	/* Tx empty */
#define COLDFIRE_UART_SR_OE	(1 << 4)	/* overrun error */
#define COLDFIRE_UART_SR_PE	(1 << 5)	/* parity error */
#define COLDFIRE_UART_SR_FE	(1 << 6)	/* framing error */
#define COLDFIRE_UART_SR_RB	(1 << 7)	/* received break */

/* CSR - clock select register */

#define COLDFIRE_UART_CSR_TCS0	(1 << 0)	/* Tx clock select 0 */
#define COLDFIRE_UART_CSR_TCS1	(1 << 1)	/* Tx clock select 1 */
#define COLDFIRE_UART_CSR_TCS2	(1 << 2)	/* Tx clock select 2 */
#define COLDFIRE_UART_CSR_TCS3	(1 << 3)	/* Tx clock select 3 */
#define COLDFIRE_UART_CSR_RCS0	(1 << 4)	/* Rx clock select 0 */
#define COLDFIRE_UART_CSR_RCS1	(1 << 5)	/* Rx clock select 1 */
#define COLDFIRE_UART_CSR_RCS2	(1 << 6)	/* Rx clock select 2 */
#define COLDFIRE_UART_CSR_RCS3	(1 << 7)	/* Rx clock select 3 */

#define COLDFIRE_UART_CSR_TIMER_TX	(COLDFIRE_UART_CSR_TCS0 \
				 | COLDFIRE_UART_CSR_TCS2 \
				 | COLDFIRE_UART_CSR_TCS3)
#define COLDFIRE_UART_CSR_TIMER_RX	(COLDFIRE_UART_CSR_RCS0 \
				 | COLDFIRE_UART_CSR_RCS2 \
				 | COLDFIRE_UART_CSR_RCS3)

/* CR - command register */

#define COLDFIRE_UART_CR_RC0	(1 << 0)	/* receiver control bit 0 */
#define COLDFIRE_UART_CR_RC1	(1 << 1)	/* receiver control bit 1 */
#define COLDFIRE_UART_CR_TC0	(1 << 2)	/* transmitter control bit 0 */
#define COLDFIRE_UART_CR_TC1	(1 << 3)	/* transmitter control bit 1 */
#define COLDFIRE_UART_CR_MISC0	(1 << 4)	/* misc control bit 0 */
#define COLDFIRE_UART_CR_MISC1	(1 << 5)	/* misc control bit 1 */
#define COLDFIRE_UART_CR_MISC2	(1 << 6)	/* misc control bit 2 */

/* Some common commands */

#define COLDFIRE_UART_CR_TX_ENABLE	(COLDFIRE_UART_CR_TC0)
#define COLDFIRE_UART_CR_TX_DISABLE	(COLDFIRE_UART_CR_TC1)
#define COLDFIRE_UART_CR_RX_ENABLE	(COLDFIRE_UART_CR_RC0)
#define COLDFIRE_UART_CR_RX_DISABLE	(COLDFIRE_UART_CR_RC1)
#define COLDFIRE_UART_CR_RESET_MODE_PTR	(COLDFIRE_UART_CR_MISC0)
#define COLDFIRE_UART_CR_RESET_RX	(COLDFIRE_UART_CR_MISC1)
#define COLDFIRE_UART_CR_RESET_TX	(COLDFIRE_UART_CR_MISC1 \
					 | COLDFIRE_UART_CR_MISC0)
#define COLDFIRE_UART_CR_RESET_ERR	(COLDFIRE_UART_CR_MISC2)
#define COLDFIRE_UART_CR_RESET_BRK	(COLDFIRE_UART_CR_MISC2 \
					 | COLDFIRE_UART_CR_MISC0)

/* ACR - auxiliary control register */

#define COLDFIRE_UART_ACR_IEC	(1 << 0)	/* input enable control */

/* IMR - interrupt mask register */

#define COLDFIRE_UART_IMR_TXRDY	(1 << 0)	/* transmitter ready */
#define COLDFIRE_UART_IMR_RXRDY	(1 << 1)	/* receiver ready */
#define COLDFIRE_UART_IMR_DB	(1 << 2)	/* delta break */
#define COLDFIRE_UART_IMR_COS	(1 << 7)	/* change of CTS state */

/* ISR - interrupt status register */

#define COLDFIRE_UART_ISR_TXRDY	(1 << 0)	/* transmitter ready */
#define COLDFIRE_UART_ISR_RXRDY	(1 << 1)	/* receiver ready */
#define COLDFIRE_UART_ISR_DB	(1 << 2)	/* delta break */
#define COLDFIRE_UART_ISR_COS	(1 << 7)	/* change of CTS state */

/* IP - input port register */

#define COLDFIRE_UART_IP_CTS	(1 << 0)	/* current CTS state */

/* OP1 - output set register */

#define COLDFIRE_UART_OP1_RTS	(1 << 0)	/* set RTS */

/* OP2 - output reset register */

#define COLDFIRE_UART_OP2_RTS	(1 << 0)	/* clear RTS */

#endif

