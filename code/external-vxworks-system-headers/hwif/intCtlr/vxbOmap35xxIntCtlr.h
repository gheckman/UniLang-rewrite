/* vxbOmap35xxIntCtlr.h - interrupt controller for TI OMAP CPU */

/*
 * Copyright (c) 2008-2009, 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,07jul11,clx  add definitions to support 128 interrupts.
01b,02mar09,m_h  cleanup
01a,01jul08,m_h   created
*/

#ifndef	__INCvxbOmap35xxIntCtlrh
#define	__INCvxbOmap35xxIntCtlrh

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/********* Bitmaps defining default setup values *********/

/* Priority Threshold.  Default = disabled */
#define OMAP_DEFAULT_PRIORITY_THRESHOLD   0xff

/* power saving through INTCPS_IDLE latency */
#define OMAP_DEFAULT_LATENCY              0x00000000

/* Soft reset with autoidle */
#define OMAP_DEFAULT_SYSCONFIG            0x00000003

/* Protection disabled */
#define OMAP_DEFAULT_PROTECTION           0x00000000

/* Enable IRQ, not FIQ */
#define OMAP_INTCPS_CONTROL_NEWIRQAGR     0x00000001


/************ Register Offsets *****************/

#define OMAP_INTCPS_SYSCONFIG    (0x0010)
#define OMAP_INTCPS_SYSSTATUS    (0x0014)
#define OMAP_INTCPS_SIR_IRQ      (0x0040)
#define OMAP_INTCPS_SIR_FIQ      (0x0044)
#define OMAP_INTCPS_CONTROL      (0x0048)
#define OMAP_INTCPS_PROTECTION   (0x004C)
#define OMAP_INTCPS_IDLE         (0x0050)
#define OMAP_INTCPS_IRQ_PRIORITY (0x0060)
#define OMAP_INTCPS_FIQ_PRIORITY (0x0064)
#define OMAP_INTCPS_THRESHOLD    (0x0068)
#define OMAP_INTCPS_ITR0         (0x0080 + (0x20 * 0))
#define OMAP_INTCPS_ITR1         (0x0080 + (0x20 * 1))
#define OMAP_INTCPS_ITR2         (0x0080 + (0x20 * 2))
#define OMAP_INTCPS_ITR3         (0x0080 + (0x20 * 3))
#define OMAP_INTCPS_MIR0         (0x0084 + (0x20 * 0))
#define OMAP_INTCPS_MIR1         (0x0084 + (0x20 * 1))
#define OMAP_INTCPS_MIR2         (0x0084 + (0x20 * 2))
#define OMAP_INTCPS_MIR3         (0x0084 + (0x20 * 3))
#define OMAP_INTCPS_MIR_CLEAR0   (0x0088 + (0x20 * 0))
#define OMAP_INTCPS_MIR_CLEAR1   (0x0088 + (0x20 * 1))
#define OMAP_INTCPS_MIR_CLEAR2   (0x0088 + (0x20 * 2))
#define OMAP_INTCPS_MIR_CLEAR3   (0x0088 + (0x20 * 3))
#define OMAP_INTCPS_MIR_SET0     (0x008C + (0x20 * 0))
#define OMAP_INTCPS_MIR_SET1     (0x008C + (0x20 * 1))
#define OMAP_INTCPS_MIR_SET2     (0x008C + (0x20 * 2))
#define OMAP_INTCPS_MIR_SET3     (0x008C + (0x20 * 3))
#define OMAP_INTCPS_ISR_SET0     (0x0090 + (0x20 * 0))
#define OMAP_INTCPS_ISR_SET1     (0x0090 + (0x20 * 1))
#define OMAP_INTCPS_ISR_SET2     (0x0090 + (0x20 * 2))
#define OMAP_INTCPS_ISR_SET3     (0x0090 + (0x20 * 3))
#define OMAP_INTCPS_ISR_CLEAR0   (0x0094 + (0x20 * 0))
#define OMAP_INTCPS_ISR_CLEAR1   (0x0094 + (0x20 * 1))
#define OMAP_INTCPS_ISR_CLEAR2   (0x0094 + (0x20 * 2))
#define OMAP_INTCPS_ISR_CLEAR3   (0x0094 + (0x20 * 3))
#define OMAP_INTCPS_PENDING_IRQ0 (0x0098 + (0x20 * 0))
#define OMAP_INTCPS_PENDING_IRQ1 (0x0098 + (0x20 * 1))
#define OMAP_INTCPS_PENDING_IRQ2 (0x0098 + (0x20 * 2))
#define OMAP_INTCPS_PENDING_IRQ3 (0x0098 + (0x20 * 3))
#define OMAP_INTCPS_PENDING_FIQ0 (0x009C + (0x20 * 0))
#define OMAP_INTCPS_PENDING_FIQ1 (0x009C + (0x20 * 1))
#define OMAP_INTCPS_PENDING_FIQ2 (0x009C + (0x20 * 2))
#define OMAP_INTCPS_ILR(m)       (0x0100 + (0x4 * (m)))

#define OMAP_INTCPS_ITR(n)          (0x0080 + (0x20 * (n)))
#define OMAP_INTCPS_MIR(n)          (0x0084 + (0x20 * (n)))
#define OMAP_INTCPS_MIR_CLEAR(n)    (0x0088 + (0x20 * (n)))
#define OMAP_INTCPS_MIR_SET(n)      (0x008C + (0x20 * (n)))
#define OMAP_INTCPS_ISR_SET(n)      (0x0090 + (0x20 * (n)))
#define OMAP_INTCPS_ISR_SET(n)      (0x0090 + (0x20 * (n)))
#define OMAP_INTCPS_PENDING_IRQ(n)  (0x0098 + (0x20 * (n)))
#define OMAP_INTCPS_PENDING_FIQ(n)  (0x009C + (0x20 * (n)))

#ifdef __cplusplus
}
#endif

#endif	/* __INCvxbOmap35xxIntCtlrh */

