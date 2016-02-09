/* usbHalDebug.h - Defines the debug macros used by the HAL sub-modules */

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
01h,29apr10,pad  Moved extern C statement after include statements.
01g,13jan10,ghs  vxWorks 6.9 LP64 adapting
01f,20jan05,hch  Corrected the _WRS_VXWORKS_MAJOR usage
01e,31oct04,hch  comment out the extern for usbLogMsg temperarily.
01d,26oct04,ami  Debug Messages Changes
01c,06oct04,ami  SPR #94684 Fix
01b,19jul04,ami  Coding Convention Changes
01a,08mar04,pdg  First.
*/

/*
DESCRIPTION

Defines the debug macros which are used by the HAL sub-modules
*/

#ifndef __INCusbHalDebugh
#define __INCusbHalDebugh

/* includes */
#include <logLib.h>

#ifdef	__cplusplus
extern "C" {
#endif

#if (defined(_WRS_VXWORKS_MAJOR) && (_WRS_VXWORKS_MAJOR >= 6))

   extern void usbPeriLogMsg (char *,long,long,long,long,long,long);

#else /* _WRS_VXWORKS_MAJOR */

/* SPR #85391 is included in the cumulative patch. If customer has
 * installed the cumulative patch, then it is OK for customer to
 * uncomment out the following extern definition. Curretnly, there will
 * be some warnings when build USB Periphral source
 */
    /* extern void usbPeriLogMsg (char *,int,int,int,int,int,int);*/

#endif /* _WRS_VXWORKS_MAJOR */

/* defines */

#define	USBHAL_DEBUG_MSG	0x01	/* for debugging macros */
#define USBHAL_DEBUG_ERR        0x02	/* for Error macros */

#define USBHAL_DEBUG                  \
        if (usbHalDebug & USBHAL_DEBUG_MSG)   \
            usbPeriLogMsg		/* debugging Macros */

#define USBHAL_ERR                    \
        if (usbHalDebug & USBHAL_DEBUG_ERR)   \
            usbPeriLogMsg		/* error macros */

extern UINT32 usbHalDebug;       /* define the debugging flag */

#ifdef	__cplusplus
}
#endif

#endif	/* __INCusbHalDebugh */

