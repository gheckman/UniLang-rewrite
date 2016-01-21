/* vbiInterrupt.h - WR Hypervisor virtual interrupt utility functions */

/*
 * Copyright (c) 2007-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01i,35may10,jl   Remove vbiVersion=1 interface
01h,29apr10,pad  Moved extern C statement after include statements.
01g,15jul09,to   fix VBI 1.0 support
01f,30jun09,to   VBI 2.0 support
01e,16dec08,to   modified for vxWorks
01d,20nov08,mmi  adopt new naming convention
01c,04sep08,dcc  modified vbiIntConnect() signature
01b,27nov07,foo  fix parameter
01a,25may07,foo  written
*/

#ifndef __INCvbiInterrupth
#define __INCvbiInterrupth

#include <vxWorks.h>
#include <vsbConfig.h>
#include <wrhv/vbiVersion.h>
#include <wrhv/vbInterface.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

extern vbiIrq_t vbiIntVecFind (char * intName, int32_t intDirection);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif  /* __INCvbiInterrupth */
