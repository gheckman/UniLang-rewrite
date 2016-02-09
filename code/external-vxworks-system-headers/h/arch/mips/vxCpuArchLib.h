/*
 * vxCpuArchLib.h - header for arch/board dependent CPU Identification 
 * support routines 
 */

/* 
 * Copyright (c) 2006 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 


/*
modification history
--------------------
01c,31oct06,pes  Rename vxCpuLib.h to vxCpuArchLib.h
01b,16oct06,pes  Rename vxCpuCountGet as vxCpuConfiguredGet, and add prototype
                 for vxCpuEnabledGet.
01a,12sep06,pes  written.
*/

#ifndef __INCvxCpuLibh
#define __INCvxCpuLibh

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

IMPORT UINT32 vxCpuIndexGet (void);
IMPORT UINT32 vxCpuConfiguredGet (void);
IMPORT cpuset_t vxCpuEnabledGet (void);

/* vxCpuLib definitions - used by vxCpuIndexGet/vxCpuCountGet */

IMPORT UINT32 vxCpuConfigured;

#ifdef __cplusplus
}
#endif

#endif /* __INCvxCpuLibh */
