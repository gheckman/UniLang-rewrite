/* usbPeriphInstr.h - WindView Instrumentation  for Peripheral Stack */

/* Copyright 2004, 2009 Wind River Systems, Inc.

   This software includes software licensed to Wind River Systems, Inc.
   by Wipro, Ltd. Wind River licensees may use this software according
   to the terms of their Wind River license agreement(s) applicable to
   this software.
*/

/*
modification history
--------------------
01c,08feb09,w_x  Event IDs for FSL Dual role USB controller added
01b,08sep04,ami  Event IDs for NET2280 added
01a,11aug04,ami Initial Version
*/

/*
DESCRIPTION

This file contains the definitions for the WindView Instrumentation for all
the modules for the USB2.0 Peripheral Stack i.e.
 1) The Target Layer
 2) The HAL Layer
 3) The TCD Layer (PDIUSBD12 & ISP1582)
*/

#ifndef __INCusbPeriphInstrh
#define __INCusbPeriphInstrh

#ifdef	__cplusplus
extern "C" {
#endif

/* defines */

/* Event Ids */

/* Event ID for Target Layer */

#define USB_TARG_INIT_EXIT            10120
#define USB_TARG_DEFAULT_PIPE         10121
#define USB_TARG_DEVICE_CONTROL       10122
#define USB_TARG_PIPE_FUNC            10123

/* Event IDs for HAL */

#define USB_HAL_INIT_EXIT              10124
#define USB_HAL_INTERRUPT_HANDLER      10125
#define USB_HAL_DEVICE_CNTL            10126
#define USB_HAL_ENDPOINT               10127

/* Event IDs for TCD */

#define USB_TCD_ISP1582_INIT_EXIT      10128
#define USB_TCD_ISP1582_INTERRUPT      10129
#define USB_TCD_ISP1582_ENDPOINT       10130
#define USB_TCD_ISP1582_DEVICE_CONTROL 10131

#define USB_TCD_PDIUSBD12_DEVCE_CONTROL 10132
#define USB_TCD_PDIUSBD12_ENDPOINT     10133
#define USB_TCD_PDIUSBD12_INIT_EXIT    10134
#define USB_TCD_PDIUSBD12_INTERRUPT    10135

/* The  needs to be verified */
#define USB_TCD_NET2280_INIT_EXIT      10136
#define USB_TCD_NET2280_INTERRUPT      10137
#define USB_TCD_NET2280_DEVICE_CONTROL 10138
#define USB_TCD_NET2280_ENDPOINT       10139

/* Event IDs for FSL TCD */
#define USB_TCD_FSL_INIT_EXIT          10150
#define USB_TCD_FSL_INTERRUPT          10151
#define USB_TCD_FSL_ENDPOINT           10152
#define USB_TCD_FSL_DEVICE_CONTROL     10153

/* Event filters */

#define	USB_TARG_WV_FILTER	        0x00000001
#define	USB_HAL_WV_FILTER	        0x00000002
#define USB_TCD_ISP582_WV_FILTER        0x00000004
#define USB_TCD_PDIUSBD12_WV_FILTER     0x00000008
#define USB_TCD_NET2280_WV_FILTER       0x00000010
#define USB_TCD_FSL_WV_FILTER           0x00000020

extern void usbPeriphWindViewLog (UINT32, char *, UINT32);

/* Macro to log the instrumentation event */

#define USB_TCD_LOG_EVENT(eventId, eventBuf, USB2_FILTER)  \
         usbPeriphWindViewLog (eventId, eventBuf, USB2_FILTER);

#define USB_HAL_LOG_EVENT(eventId, eventBuf, USB2_FILTER)  \
         usbPeriphWindViewLog (eventId, eventBuf, USB2_FILTER);

#define USB_TARG_LOG_EVENT(eventId, eventBuf, USB2_FILTER)  \
         usbPeriphWindViewLog (eventId, eventBuf, USB2_FILTER);

#ifdef	__cplusplus
}
#endif

#endif	/* usbPeriphInstr */
