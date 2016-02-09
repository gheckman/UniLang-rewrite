/* intLibP.h - private interrupt header file */

/* 
 * Copyright (c) 2007-2010, 2014 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01h,01apr14,h_k  added intCpuEnable().
01g,29apr10,pad  Moved extern C statement after include statements.
01f,16oct09,cww  Added intStartupUnlock
01e,26aug09,cww  Added prototype for intRestrict
01f,14jul09,s_s  moved intCpuMicroLock/Unlock declaration to intMicroLibP.h
01e,06jun09,kk   added prototype of intCpuMicroLock/Unlock
01d,27aug08,jpb  Renamed VSB header file
01c,08jul08,gls  added warning about inclusion in semLibInline.h
01b,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
01a,03feb07,jmg  Written, moved IS_INT_CONTEXT and VX_INT_RESTRICT to here and
		 added the prefix _WRS_ to both macros.
*/

#ifndef __INCintLibPh
#define __INCintLibPh

#include <vxWorks.h>
#include <vsbConfig.h>
#include <private/windLibP.h>	/* _WRS_KERNEL_GLOBLAL_ACCESS () */

#ifdef __cplusplus
extern "C" {
#endif

    /*
     *  ***** WARNING *****
     *
     * This private header file is included by the public header file(s):
     *   - h/inline/semLibInline.h 
     *
     * Ensure that no usage of a VSB source configuration macro is made 
     * by any structure or macro in this file that is also used(directly or 
     * indirectly) by the above list of public header files.
     */

/* variable declarations */

#ifndef _ASMLANGUAGE

#ifndef _WRS_CONFIG_SMP

IMPORT int intCnt;            /* count of nested interrupt service routines */

STATUS intRestrict (void);

#endif /* _WRS_CONFIG_SMP */

extern void intCpuEnable (void);

#ifdef _WRS_CONFIG_DELAYED_HW_INIT
extern void intStartupUnlock (void);
#endif

#endif /* _ASMLANGUAGE */

/*******************************************************************************
*
* _WRS_INT_RESTRICT - restrict interrupt context from using a routine
*
* This routine returns OK if and only if we are executing in a
* task's context and ERROR if called within an interrupt context.
* 
* This routine is used only in the vxWorks kernel libraries for perfromace.  In
* general APIs should use the routines or macros defined in intLib.h instead.
*
* SEE ALSO: INT_RESTRICT(), intRestrict()
*
* RETURNS: OK or ERROR
*
* \NOMANUAL
*/

#ifdef _WRS_CONFIG_SMP
#define _WRS_INT_RESTRICT() INT_RESTRICT()				
#else
#define _WRS_INT_RESTRICT() (_WRS_INT_CONTEXT() ? errno = 		\
				S_intLib_NOT_ISR_CALLABLE, ERROR : OK)
#endif /* _WRS_CONFIG_SMP */

/*******************************************************************************
*
* _WRS_INT_CONTEXT - determine if executing in interrupt context
*
* This routine returns TRUE only if the caller is executing in an
* interrupt context.  If executing in a task context FALSE is
* returned. 
*
* This routine is used only in the vxWorks kernel libraries for perfromace.  In
* general APIs should use the routines or macros defined in intLib.h instead
*
* RETURNS: TRUE or FALSE.
*
* ERRNO: N/A
* 
* \NOMANUAL
* 
*/

#ifdef _WRS_CONFIG_SMP
#define _WRS_INT_CONTEXT() INT_CONTEXT ()
#else
#define _WRS_INT_CONTEXT() (intCnt > 0)
#endif /* _WRS_CONFIG_SMP */

/*******************************************************************************
*
* _WRS_SAFE_INT_CONTEXT - determine if executing in interrupt context
*
* This routine returns TRUE only if the caller is executing in an
* interrupt context.  If executing in a task context FALSE is
* returned. 
*
* This routine is used only in the vxWorks kernel libraries for perfromace.  In
* general APIs should use the routines or macros defined in intLib.h instead
*
* SMP CONSIDERATIONS
* 
* This macro uses a non-locked access and may only be used where it is 
* protected from task migration.
* 
* RETURNS: TRUE or FALSE.
*
* ERRNO: N/A
* 
* \NOMANUAL
* 
*/

 #define _WRS_SAFE_INT_CONTEXT() (_WRS_KERNEL_GLOBAL_ACCESS (intCnt) > 0)

#ifdef __cplusplus
}
#endif

#endif /* __INCintLibPh */
