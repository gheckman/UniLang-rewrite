/* envLib.h - environment varable library header file */

/*
 * Copyright (c) 1990-2005, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01m,29apr10,pad  Moved extern C statement after include statements.
01l,26aug09,cww  Add LP64 support
01k,27apr05,kk   add NOMANUAL to environ macro for apigen (SPR# 108372)
01j,17mar04,pad  Added envGet() prototype.
01i,22sep92,rrr  added support for c++
01h,19jul92,smb  moved prototype for getenv to stdlib.h
                 added include stdlib.h
01g,04jul92,jcf  cleaned up.
01f,26may92,rrr  the tree shuffle
01e,09dec91,rrr  fixed bad prototype (envShow).
01d,04oct91,rrr  passed through the ansification filter
		  -changed copyright notice
01c,05oct90,shl  added copyright notice.
                 made #endif ANSI style.
01b,01aug90,jcf  cleanup.
01a,12jul90,rdc  written.
*/

#ifndef __INCenvLibh
#define __INCenvLibh

#include "taskLib.h"
#include "stdlib.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
*
* environ - environment pointer
*
* The following macro is provided for code that manipulates the environment
* variable array directly.
*
* \NOMANUAL
*/

#define environ 							\
    (								      	\
    (taskIdCurrent->ppEnviron == NULL) ? 				\
    ppGlobalEnviron : taskIdCurrent->ppEnviron 				\
    )

extern STATUS 	envLibInit (BOOL installHooks);
extern STATUS 	envPrivateCreate (TASK_ID taskId, _Vx_usr_arg_t envSource);
extern STATUS 	envPrivateDestroy (TASK_ID taskId);
extern char **	envGet (TASK_ID taskId);
extern STATUS 	putenv (char * pEnvString);
extern void 	envShow (TASK_ID taskId);

#ifdef __cplusplus
}
#endif

#endif /* __INCenvLibh */
