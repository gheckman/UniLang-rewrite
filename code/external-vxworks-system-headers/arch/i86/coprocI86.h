/* coprocI86.h - coprocessor management library header */

/*
 * Copyright 2003-2004, 2010, 2012 Wind River Systems, Inc.
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,15may12,jmp  CQID: Fix WIND00309977 : Added VX_COPROCS_ALL_TASK
                 definition.
01b,28apr10,pad  Moved extern C statement after include statements.
01a,13apr04,zmm  written based on coprocPpc.h 01c.
*/

#ifndef __INCcoprocI86h
#define __INCcoprocI86h

/* includes */

#include "taskLib.h"

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define VX_FP_TASK         VX_COPROC1_TASK

#define VX_COPROCS_ALL_TASK	VX_FP_TASK

#ifdef __cplusplus
}
#endif

#endif /* __INCcoprocI86h */
