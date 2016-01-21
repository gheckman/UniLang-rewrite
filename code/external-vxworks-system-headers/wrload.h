/* wrload.h - wrload header file */

/*
 * Copyright (c) 2008-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable
 * Wind River license agreement.
 */

/*
modification history
--------------------
01b,27may10,pad  Moved extern C statement after include statements.
01e,08jun10,v_r  wrload ID type now stored on 8 bits.
01d,30mar10,v_r  Hypervisor-specific updates :
		 + Moved cpu number to generic id.
		 + Added ability to override CPU prepare/enable routines.
01c,01mar10,v_r  Linux types now in a dedicated header.
		 WRLOAD_ADDR_T now a public type (needed by public APIs).
01b,24nov09,v_r  Mods for P4080 36bits support (CQ:WIND00174166):
		 + added CPU-specific routines support.
		 + added symbol list parsing routine.
01a,08aug08,mak  written
*/

/*
DESCRIPTION

This header file provides access to the wrload interface.
*/

#ifndef __INCwrloadh
#define __INCwrloadh

#ifndef LINUX
#include <vxWorks.h>
#else
#include <sys/types.h>
#include "wrloadLinux.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Retrieve the actual value encoded within the wrload opaque ID */

#define WRLOAD_ID_VALUE_GET(wrloadId)	((wrloadId) & 0xFFFFFF)

/* Do the same for the ID type */

#define WRLOAD_ID_TYPE_GET(wrloadId)	(((wrloadId) >> 24) & 0xFF)
#define WRLOAD_ID_DEFAULT_TYPE		0

typedef unsigned long long  WRLOAD_ADDR_T;
typedef UINT32		    WRLOAD_ID;

typedef enum wrload_cpu_rtn_desc
    {
    WRLOAD_CPU_MEM_READ,
    WRLOAD_CPU_MEM_WRITE,
    WRLOAD_CPU_MEM_FILL,
    WRLOAD_CPU_MEM_OPEN,
    WRLOAD_CPU_MEM_CLOSE,
    WRLOAD_CPU_MEM_MAP,
    WRLOAD_CPU_MEM_UNMAP,
    WRLOAD_CPU_PREPARE,
    WRLOAD_CPU_ENABLE
    } WRLOAD_CPU_RTN_DESC;

typedef union wrload_cpu_rtn
    {
    ssize_t (* read) (WRLOAD_ID id, WRLOAD_ADDR_T address, void * buffer,
                      size_t size);
    ssize_t (* write) (WRLOAD_ID id, WRLOAD_ADDR_T address, void * buffer,
                       size_t size);
    ssize_t (* fill) (WRLOAD_ID id, WRLOAD_ADDR_T address, char pattern,
                      size_t size);
    STATUS  (* open) (WRLOAD_ID id);
    STATUS  (* close) (WRLOAD_ID id);
    void *  (* map) (WRLOAD_ID id, WRLOAD_ADDR_T phys_addr, size_t size);
    void    (* unmap) (WRLOAD_ID id, void * virt_addr, size_t size);
    STATUS  (* prepare) (WRLOAD_ID id, void * arg);
    STATUS  (* enable) (WRLOAD_ADDR_T entry, WRLOAD_ID id);
    } WRLOAD_CPU_RTN;
extern STATUS	wrload (const char * argsString);
extern STATUS	wrloadSymValueGet (WRLOAD_ID id, char * symName, 
				   void * pValue, size_t bufLen);
extern STATUS	wrloadCpuRtnSet (WRLOAD_CPU_RTN_DESC cpuRtnDesc, 
				 WRLOAD_CPU_RTN routine);
extern STATUS	wrloadCpuRtnGet (WRLOAD_CPU_RTN_DESC cpuRtnDesc, 
				 WRLOAD_CPU_RTN * pRoutine);

#ifdef __cplusplus
}
#endif

#endif /* __INCwrloadh */


