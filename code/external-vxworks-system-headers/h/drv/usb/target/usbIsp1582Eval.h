/* usbIsp1582Eval.h - Definitions for Philips ISP 1582 eval board */

/* Copyright 2004, 2010 Wind River Systems, Inc. */

/*
Modification history
--------------------
01e,29apr10,pad  Moved extern C statement after include statements.
01d,02aug04,mta  Modification History Changes
01c,19jul04,ami  Coding Convention Changes
01b,01jun04,mta  Changes for Interrupt Mode
01a,21apr04,ami  First.
*/

/*
DESCRIPTION

Defines constants related to the Philips ISP 1582 evaluation board.
*/

#ifndef __INCusbIsp1582Evalh
#define __INCusbIsp1582Evalh

/* includes */

#include "usb/usbPciLib.h"	            /* PCI bus functions */

#ifdef	__cplusplus
extern "C" {
#endif


/* defines */

/* evaluation board I/O address offsets */

/* 
 * There are four ports that are utilized by the firmware. The Address port is
 * a gateway for the PCI bus to assign the register address to the ISP1582.
 * The Data port holds the 16-bit data that is to be written to or read out
 * from the ISP1582 register. The Control port has only a single function: to
 * mask the interrupt from the ISP1582. This allows the processor to branch to
 * the interrupt service routine to clear the respective interrupt. The DMA
 * port controls the function of the external master DMA controller.
 */

#define ISP1582EVAL_ADDRESS_PORT    0	    /* address port */
#define ISP1582EVAL_DATA_PORT       2	    /* data port */
#define ISP1582EVAL_CNTL_PORT       4	    /* control port */
#define ISP1582EVAL_DMA_PORT        6       /* dma port */

/* default settings for DMA */

#define ISP1582EVAL_DEFAULT_DMA	    6	    /* default DMA channel */

/* macros used to read/write ISP 1582 registers. ISP 1582 uses 16 bit bus
 * access. So all read/ writes to/from the registers will be 16 bits read
 * write.
 */

#define OUT_ISP1582_CMD(pTarget,b)	\
   USB_PCI_WORD_OUT (pTarget->ioBase + ISP1582EVAL_ADDRESS_PORT , (b))
                                     /* Macro to write in address port */
#define OUT_ISP1582_DATA(pTarget,b) \
    USB_PCI_WORD_OUT (pTarget->ioBase + ISP1582EVAL_DATA_PORT , (b))
                                     /* Macro to write on data port */

#define IN_ISP1582_DATA(pTarget)	\
    USB_PCI_WORD_IN (pTarget->ioBase + ISP1582EVAL_DATA_PORT)
                                     /* Macro to read from data port */

#define OUT_ISP1582_CNTL(pTarget,b) \
    USB_PCI_WORD_OUT (pTarget->ioBase + ISP1582EVAL_CNTL_PORT , (b))
                                     /* Macro to write on Control Port */

#define OUT_ISP1582_DMA(pTarget,b)  \
    USB_PCI_WORD_OUT (pTarget->ioBase + ISP1582EVAL_DMA_PORT , (b))
                                     /* Macro to write on DMA Port */

#define IN_ISP1582_DMA(pTarget)  \
    USB_PCI_WORD_OUT (pTarget->ioBase + ISP1582EVAL_DMA_PORT)
                                     /* Macro to read on DMA port */

#ifdef	__cplusplus
}
#endif

#endif	/* __INCusbIsp1582Evalh */
