/* vxCpuLibP.h - private header for runtime Identification */

/* 
 * Copyright (c) 2006-2010 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01g,08jul10,cww  Removed vxCpuSetConfigured
01f,29apr10,pad  Moved extern C statement after include statements.
01e,02feb09,cww  Add dynamic CPU reservation
01d,13may08,zl   added private API for CPU reservation.
01c,08aug07,zl   added _WRS_CPUSET_CONFIGURED()
01b,05feb07,pes  Remove 'const' designation from vxCpuConfigured definition.
01a,26oct06,lei  Created based on vxCpuLib.h
*/

#ifndef __INCvxCpuLibPh
#define __INCvxCpuLibPh

#include <cpuset.h>

#ifdef __cplusplus
extern "C" {
#endif

/* extern */

extern cpuset_t vxCpuEnabled; /* set of CPUs enabled */

/* configuration parameter defined in a configlette, usrKernel.c */

extern unsigned int vxCpuConfigured; 
extern cpuset_t     vxCpuSetReserved;

/* macro */

#define _WRS_CPU_ENABLED()		(vxCpuEnabled) 
#define _WRS_CPU_CONFIGURED()		(vxCpuConfigured)
#define _WRS_CPUSET_RESERVED()		(vxCpuSetReserved)

/* private API */

void 	vxCpuReservedStringParse (char *pExplicitCpus);

#ifdef __cplusplus
}
#endif

#endif /* __INCvxCpuLibPh */
