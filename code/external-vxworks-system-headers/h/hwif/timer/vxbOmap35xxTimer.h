/* vxbOmap35xxTimer.h - vxbus OMAP35xx timer interfaces header file */

/*
 * Copyright (c) 2008-2011, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
14jan15,swu  added support for AM437x. (US51994)
01d,13jul11,clx  add dm81xx timer support
01c,07oct10,rec  add tickless-idle support functions
01b,02mar09,m_h  Cleanup
01a,08jul08,m_h  written.
*/

/*
DESCRIPTION

This file provides the OMAP timers specific definitions.

*/

#ifndef __INCvxbOmap35xxTimerh
#define __INCvxbOmap35xxTimerh

#include <vxBusLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Maximum number of timers */
#define OMAP35XX_MAX_TIMERS          12

/*
 * These base addresses are used for purposes of identifying which timer is
 * being used
 */

#define OMAP35XX_BASE_ADDR_GPTIMER1          0x48318000
#define OMAP35XX_BASE_ADDR_GPTIMER2          0x49032000
#define OMAP35XX_BASE_ADDR_GPTIMER3          0x49034000
#define OMAP35XX_BASE_ADDR_GPTIMER4          0x49036000
#define OMAP35XX_BASE_ADDR_GPTIMER5          0x49038000
#define OMAP35XX_BASE_ADDR_GPTIMER6          0x4903A000
#define OMAP35XX_BASE_ADDR_GPTIMER7          0x4903C000
#define OMAP35XX_BASE_ADDR_GPTIMER8          0x4903E000
#define OMAP35XX_BASE_ADDR_GPTIMER9          0x49040000
#define OMAP35XX_BASE_ADDR_GPTIMER10         0x48086000
#define OMAP35XX_BASE_ADDR_GPTIMER11         0x48088000
#define OMAP35XX_BASE_ADDR_GPTIMER12         0x48304000

#define OMAP35XX_BASE_ADDR_CM_CLKOUT_CTRL    0x48004D70


/* GP Timer offsets */

#define OMAP35XX_TIMER_TIOCP_CFG_OFFSET    0x010
#define OMAP35XX_TIMER_TISTAT_OFFSET       0x014
#define OMAP35XX_TIMER_TISR_OFFSET         0x018
#define OMAP35XX_TIMER_TIER_OFFSET         0x01C
#define OMAP35XX_TIMER_TWER_OFFSET         0x020
#define OMAP35XX_TIMER_TCLR_OFFSET         0x024
#define OMAP35XX_TIMER_TCRR_OFFSET         0x028
#define OMAP35XX_TIMER_TLDR_OFFSET         0x02C
#define OMAP35XX_TIMER_TTGR_OFFSET         0x030
#define OMAP35XX_TIMER_TWPS_OFFSET         0x034
#define OMAP35XX_TIMER_TMAR_OFFSET         0x038
#define OMAP35XX_TIMER_TCAR1_OFFSET        0x03C
#define OMAP35XX_TIMER_TSICR_OFFSET        0x040
#define OMAP35XX_TIMER_TCAR2_OFFSET        0x044
#define OMAP35XX_TIMER_TPIR_OFFSET         0x048
#define OMAP35XX_TIMER_TNIR_OFFSET         0x04C
#define OMAP35XX_TIMER_TCVR_OFFSET         0x050
#define OMAP35XX_TIMER_TOCR_OFFSET         0x054
#define OMAP35XX_TIMER_TOWR_OFFSET         0x058

/* DM81xx GP Timer offsets */

#define DM81XX_TIMER_IRQSTATUS_OFFSET       0x028
#define DM81XX_TIMER_IRQSTATUS_SET_OFFSET   0x02C
#define DM81XX_TIMER_IRQWAKEEN_OFFSET       0x034
#define DM81XX_TIMER_TIOCP_CFG_OFFSET       0x010
#define DM81XX_TIMER_TCLR_OFFSET            0x038
#define DM81XX_TIMER_TCRR_OFFSET            0x03C
#define DM81XX_TIMER_TLDR_OFFSET            0x040
#define DM81XX_TIMER_TTGR_OFFSET            0x044
#define DM81XX_TIMER_TWPS_OFFSET            0x048
#define DM81XX_TIMER_TMAR_OFFSET            0x04C
#define DM81XX_TIMER_TCAR1_OFFSET           0x050
#define DM81XX_TIMER_TSICR_OFFSET           0x054
#define DM81XX_TIMER_TCAR2_OFFSET           0x058

#define TIMER_W_PEND_TCLR                   0x1
#define TIMER_W_PEND_TCRR                   0x2
#define TIMER_W_PEND_TLDR                   0x4
#define TIMER_W_PEND_TTGR                   0x8
#define TIMER_W_PEND_TMAR                   0x10
#define TIMER_W_PEND_TPIR                   0x20
#define TIMER_W_PEND_TNIR                   0x40
#define TIMER_W_PEND_TCVR                   0x80
#define TIMER_W_PEND_TOCR                   0x100
#define TIMER_W_PEND_TOWR                   0x200

#define TIMER_POSTED                        0x4

#define OMAP35XX_TIMER_ID_OFFSET            (0x0)

/* AM437x Timer ID */

#define AM437X_DMTIMER_ID                   (0x4FFF0301)
#define AM437X_DMTIMER_1MS_ID               (0x15)

/* AM335x Timer ID */

#define AM335X_DMTIMER_ID                   (0x40001000)
#define AM335X_DMTIMER_1MS_ID               (0x15)

/* AM389x Timer ID */

#define AM389X_DMTIMER_ID                   (0x4FFF1301)

/* prototypes */

#ifndef _ASMLANGUAGE
IMPORT void omap35xxOneShotEnable (VXB_DEVICE_ID pInst, UINT32 nTicks);
IMPORT UINT32 omap35xxOneShotDisable (VXB_DEVICE_ID pInst);
#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbOmap35xxTimerh */
