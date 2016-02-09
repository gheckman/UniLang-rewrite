/* salCommonP.h - socket application library common private header file */

/*
 * Copyright (c) 2003-2004, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01i,09sep10,jpb  Removed unused function pointer salEvtRtn.
01h,29jul10,pad  Moved extern C statement after include statements.
01g,26may04,ymz  updated debugging info due to file merging.
01f,06may04,ymz  fixed salEvtRtn build error for wvLib.c.
01e,29apr04,ymz  added salEvtRtn definition.
01d,20feb04,ymz  code review changes
01c,05dec03,als  add debugging code support to RTP space
01b,03dec03,als  restrict debugging code to kernel space only
01a,26nov03,als  created
*/

#ifndef __INCsalCommonPh
#define __INCsalCommonPh

/* includes */

#include "dsi/salCommon.h"

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#ifdef _WRS_KERNEL
/* uncomment the following line to include SAL debugging code in kernel apps */
/* #define SAL_DEBUG_ON */
#else
/* uncomment the following line to include SAL debugging code in RTP apps */
/* #define SAL_DEBUG_ON */
#endif

#ifdef SAL_DEBUG_ON         /* define SAL debugging tools */

#ifdef __cplusplus
}
#endif

#ifdef _WRS_KERNEL
/* use logMsg() to display debugging messages in kernel apps */
#include <logLib.h>
#else
/* logMsg() isn't available to RTP apps, so use printf() instead */
#include <stdio.h>
#define logMsg printf
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* output levels used for SAL debugging, in order of decreasing importance
*/
#define SAL_DEBUG_NONE      0               /* disable debug output */
#define SAL_DEBUG_SEVERE    1               /* for an unexpected error path */
#define SAL_DEBUG_ERROR     3               /* for an expected error path */
#define SAL_DEBUG_SUCCESS   5               /* for a success path */
#define SAL_DEBUG_CONTROL   7               /* for a change in control */
#define SAL_DEBUG_ALL       9               /* for super-detailed info */

/* define the current debug level */

#define SAL_DEBUG_LEVEL	SAL_DEBUG_NONE

/* macro that prints out debugging info using logMsg
   - level: minimum debug level required to activate output
   - format: printf-style format string
   - value: single numeric value that can be referenced by "format"
   macro automatically includes the name of the invoking function
*/
#define SAL_DEBUG(level, format, value) \
    if (SAL_DEBUG_LEVEL >= (level)) \
        { logMsg ("%s: " format "\n", \
                  (_Vx_usr_arg_t)__FUNCTION__, (_Vx_usr_arg_t)value, \
                  0, 0, 0, 0); } \
    else \
        { /* prevent accidental mismatch with nested if's */ }
        
/* current debugging level used for SAL debugging;
   the higher the value, the more output is shown
*/

#else   /* alternate SAL debugging tools (when no debugging is required) */
    
/* macro that prints out debugging info does nothing */
#define SAL_DEBUG(level, format, value)

#endif /* SAL_DEBUG_ON */

#ifdef __cplusplus
}
#endif

#endif /* __INCsalCommonPh */

