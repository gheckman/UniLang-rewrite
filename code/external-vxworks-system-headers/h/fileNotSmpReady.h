/* fileNotSmpReady.h - header to be included to flag file as not SMP-ready */

/*
 * Copyright (c) 2007-2008, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01d,29apr10,pad  Moved extern C statement after include statements.
01c,27aug08,jpb  Renamed VSB header file
01b,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
01a,31aug07,mil  Created.
*/

#ifndef __INCfileNotSmpReadyh
#define __INCfileNotSmpReadyh

#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Debug Info: The source file that directly includes this header 
 * file should not be use in a SMP configuration.  
 */

#ifdef _WRS_CONFIG_SMP
#error source module is not SMP-ready
#endif /* _WRS_CONFIG_SMP */

/*
 * This header file can be included by a source file which is determined 
 * and designated as not SMP-ready.  If the file that includes this file 
 * is compiled for SMP, the compiler will flag an error.  
 * 
 * This is useful in flagging invalid file usage in an SMP configuration.  
 * An example would be a file in a BSP.  If the source file of a 
 * driver is designated as not SMP-ready, the user will be alerted to 
 * an error if the BSP file #include the driver file that is not SMP-ready.  
 * 
 * For library build of files which is not normally performed by a user 
 * with a binary installation, files that are not SMP-ready should 
 * have its build disabled in the Makefile.  The intend of flagging not 
 * SMP-ready by the inclusion of this file is not meant to be a pervasive 
 * signalling mechanism for the source base.  In other words, having 
 * this file directly included conclusively communicates the designation 
 * that the file that includes this file is not SMP-ready.  However, for 
 * source files that do not include this header file, their SMP-readiness 
 * cannot be determined from the non-inclusion of this file.  In addition, 
 * the SMP-readiness of a file that indirectly includes this header file 
 * cannot be determined as well.  
 */                                                                        

#ifdef __cplusplus
}
#endif

#endif /* __INCfileNotSmpReadyh */

