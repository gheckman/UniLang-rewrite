/* usbTcdNET2280Debug.h - Debug macros for Net2280 TCD */

/*
 * Copyright (c) 2004, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
Modification history
--------------------
01g,29apr10,pad  Moved extern C statement after include statements.
01f,13jan10,ghs  vxWorks 6.9 LP64 adapting
01e,26oct04,ami  Debug Messages Changes
01d,06oct04,ami  SPR #94684 Fix
01c,17sep04,ami  Declaration of usbNET2280Debug flag moved
01b,08sep04,ami  Code Review Comments Incorporated
01a,03sep04,gpd  written
*/

/*
DESCRIPTION

This file contains the macro definitions used for debugging the
Netchip2280 TCD.
*/
#ifndef __INCusbTcdNET2280Debugh
#define __INCusbTcdNET2280Debugh

/* includes */
#include <logLib.h>

#ifdef	__cplusplus
extern "C" {
#endif

extern void usbPeriLogMsg (char *,long,long,long,long,long,long);

/* defines */

#define USBNET2280_DEBUG_MSG        0x01
#define USBNET2280_DEBUG_ERR        0x02

#define USB_NET2280_DEBUG                  \
        if (usbNET2280Debug & USBNET2280_DEBUG_MSG)  \
            usbPeriLogMsg		/* debugging Macros */

#define USB_NET2280_ERROR                    \
        if (usbNET2280Debug & USBNET2280_DEBUG_ERR)  \
            usbPeriLogMsg		/* error Macros */

/* Define the debugging flag */

extern UINT32 usbNET2280Debug;

#ifdef	__cplusplus
}
#endif

#endif	/* __INCusbTcdNET2280Debugh */

