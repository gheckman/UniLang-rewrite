/* usbPdiusbd12Debug.h - Defines the debug macros used by the PDIUSBD12 sub-modules */

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
01b,19jul04,ami  Coding Convention Changes
01a,18mar04,ami  First.
*/

/*
DESCRIPTION

Defines the debug macros which are used by the usbPdiusbd12 sub-modules

*/
#ifndef __INCusbPdiusbd12Debugh
#define __INCusbPdiusbd12Debugh

/* includes */

#include <logLib.h>

#ifdef	__cplusplus
extern "C" {
#endif

extern void usbPeriLogMsg (char *,long,long,long,long,long,long);

/* defines */

#define USBPDIUSBD12_DEBUG_MSG        0x01    /* For Debuging Macros */
#define USBPDIUSBD12_DEBUG_ERR        0x02    /* For Error Macros */

#define USBPDIUSBD12_DEBUG                  \
        if (usbPdiusbd12Debug & USBPDIUSBD12_DEBUG_MSG)  \
            usbPeriLogMsg		/* debugging Macros */

#define USBPDIUSBD12_ERROR                    \
        if (usbPdiusbd12Debug & USBPDIUSBD12_DEBUG_ERR)  \
            usbPeriLogMsg		/* error Macros */

extern UINT32 usbPdiusbd12Debug;       /* Define the debugging flag */

#ifdef	__cplusplus
}
#endif

#endif	/* __INCusbPdiusbd12Debugh */
