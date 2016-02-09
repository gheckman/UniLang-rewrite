/* usbIsp1582Debug.h - Defines the debug macros used by the ISP1582 sub-modules */

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
01f,29apr10,pad  Moved extern C statement after include statements.
01e,13jan10,ghs  vxWorks 6.9 LP64 adapting
01d,26oct04,ami  Debug Messages Changes
01c,06oct04,ami  SPR #94684 Fix
01b,12jul04,ami  Coding Convention Changes
01a,28apr04,ami  First.
*/

/*
DESCRIPTION

Defines the debug macros which are used by the usbPdiusbd12 sub-modules
*/
#ifndef __INCusbIsp1582Debugh
#define __INCusbIsp1582Debugh

/* includes */
#include <logLib.h>

#ifdef	__cplusplus
extern "C" {
#endif

/* defines */

#define USBISP1582_DEBUG_MSG        0x01   /* For Debugging Log Messages */
#define USBISP1582_DEBUG_ERR        0x02   /* For Error Log Messages */

extern void usbPeriLogMsg (char *,long,long,long,long,long,long);

#define USBISP1582_DEBUG                  \
        if (usbIsp1582Debug & USBISP1582_DEBUG_MSG)  \
            usbPeriLogMsg		/* debugging Macros */

#define USBISP1582_ERROR                    \
        if (usbIsp1582Debug & USBISP1582_DEBUG_ERR)   \
            usbPeriLogMsg		/* error macros */

extern UINT32 usbIsp1582Debug;       /* Define the debugging flag */

#ifdef	__cplusplus
}
#endif

#endif	/* __INCusbIsp1582Debugh */
