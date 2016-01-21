/*
 * vxCpuSimsolarisLib.h - header for arch/board vxsim dependent CPU
 * Identification support routines 
 */

/* 
 * Copyright (c) 2006-2007 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01b,03jul07,elp  added vxCpuAvailableGet().
01a,27jul06,elp  written.
*/

#ifndef __INCvxCpuSimsolarisLibh
#define __INCvxCpuSimsolarisLibh

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

extern UINT32		vxCpuAvailableGet (void);
extern STATUS		vxCpuStateInit (unsigned int cpu,	
					WIND_CPU_STATE * pCpuState, 
					char * stackBase, FUNCPTR entry);

extern void		vxCpuStart (int cpu, WIND_CPU_STATE * pCpuState);

#ifdef __cplusplus
}
#endif

#endif /* __INCvxCpuSimsolarisLibh */
