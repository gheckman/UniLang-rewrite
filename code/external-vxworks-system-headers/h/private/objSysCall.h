/* objSysCall.h - VxWorks object system call definitions */

/*
 * Copyright 2003, 2008, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01h,28apr10,pad  Moved extern C statement after include statements.
01g,28aug08,nld  added VX_OBJ_INFO_GET_TASK_DELAYED
01f,26nov03,dcc  added VX_OBJ_DELETE_CLOSE.
01e,25nov03,aeg  added VX_OBJ_INFO_GET_SEM_DESC.
01d,30oct03,aeg  added VX_OBJ_INFO_GET_MSGQ_DESC
01c,30oct03,dcc  moved objInfoGet and objDelete prototypes to objLib.h, user
		 version.
01b,01oct03,aeg  changed value of VX_OBJ_DELETE_TASK_FORCE.
01a,03sep03,aeg  written
*/

#ifndef __INCobjSysCallh
#define __INCobjSysCallh

#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 'level' definitions for the objInfoGet() system call on tasks */

#define VX_OBJ_INFO_GET_TASK_NAME       0
#define VX_OBJ_INFO_GET_TASK_DESC       1
#define VX_OBJ_INFO_GET_TASK_SUSPENDED  2
#define VX_OBJ_INFO_GET_TASK_READY      3
#define VX_OBJ_INFO_GET_TASK_PENDED     4
#define VX_OBJ_INFO_GET_TASK_DELAYED    5

/* 'level' definitions for the objInfoGet() system call on message queues */

#define VX_OBJ_INFO_GET_MSGQ_DESC	10

/* 'level' definitions for the objInfoGet() system call on semaphores */

#define VX_OBJ_INFO_GET_SEM_DESC	20

/* options for the objDelete() system call */

#define VX_OBJ_DELETE_TASK_FORCE        1
#define VX_OBJ_DELETE_CLOSE        	2

#ifdef __cplusplus
}
#endif

#endif /* __INCobjSysCallh */
