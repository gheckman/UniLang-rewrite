/*
 * vxCpuArchLib.h - header for arch/board dependent CPU Identification
 * support routines
 */

/*
 * Copyright (c) 2006, 2008-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */


/*
modification history
--------------------
01k,28jan10,jb   modifying per uHLD 1044
01j,18sep09,scm  remove _WRS_CPU_BIOS_CONFIGURED ...
01i,16jan09,scm  declare _func_cpuIndexGet...
01h,05jun08,rec  add vxRsdpPtr
01g,01nov06,scm  remove arch definitions for vxCpuEnabledGet &
                 vxCpuConfiguredGet
01f,30oct06,scm  change references from vxCpuLib to vxCpuArchLib...
01e,14sep06,scm  add count to track SMP initialized CPUs
01d,26jul06,scm  tie vxCpuCount to MP Configuration Entry CPU counter
                 (mpApicNcpu).
01c,21jul06,scm  _func_cpuIndexGet not required at this time...
01b,21jul06,scm  Move SMP macros to private header.
01a,05jul06,scm  written.
*/

#ifndef __INCvxCpuArchLibh
#define __INCvxCpuArchLibh

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

typedef unsigned int cpuid_t;   /* hardware CPU identification */

/* function declarations */

/* Arch or BSP system-dependent implementation routine */

extern unsigned int (*_func_cpuIndexGet) (void);

extern unsigned int vxCpuIndexGet (void);

extern unsigned int vxCpuPhysIndexGet (void);

extern unsigned int vxCpuIdToPhysIndex (cpuid_t cpuID);

extern cpuid_t vxCpuPhysIndexToId (unsigned int cpuPhysIdx);

extern unsigned int vxCpuCount;

extern char * vxRsdpPtr;

#ifdef __cplusplus
}
#endif

#endif /* __INCvxCpuArchLibh */
