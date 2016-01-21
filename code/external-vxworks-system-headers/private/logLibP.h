/* logLibP.h - private header for logLib logging facility */

/* Copyright 2004, 2008 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
 
/* modification history
--------------------
01b,15sep08,rlp  Added logFdFromRlogin definition (CQ:WIND00116711).
01a,17sep04,dlk	 written,
*/

#ifndef __INClogLibPh
#define __INClogLibPh

#include <vxWorks.h>
#include <logLib.h>
#include <private/semLibP.h>

/*
 * These two should arguably be in a public header, as
 * they refer to the public API.
 */

#define MAX_LOGARGS	6	/* max args to log message */
#define MAX_LOGFDS	5	/* max log fds */


#ifdef __cplusplus
extern "C" {
#endif

/*
 * The FD array and the semaphore which guards it are made
 * external since they are shared by nbioLogLib.
 */

extern SEMAPHORE logFdSem;

extern int logFd [MAX_LOGFDS];
extern int numLogFds;

extern int logFdFromRlogin;

#ifdef __cplusplus
    }
#endif

#endif /* __INClogLibPh */

