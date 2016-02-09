/* logLib.h - message logging library header */

/*
 * Copyright (c) 1990-1993, 2009-2010, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01m,20may15,h_k  removed logInit prototype. (VXW6-84370)
01l,14apr10,jpb  Added _func_logMsg prototype.
01k,01may09,jpb  Updated for LP64 support.
01j,11feb93,jcf  added __PROTOTYPE_5_0 for compatibility.
01i,22sep92,rrr  added support for c++
01h,17jul92,gae  undid 01e.
01g,04jul92,jcf  cleaned up.
01f,26may92,rrr  the tree shuffle
01e,05mar92,gae  changed logMsg() to be true variable args.
01d,04oct91,rrr  passed through the ansification filter
		  -changed VOID to void
		  -changed copyright notice
01c,19oct90,shl  changed logMsg() to use variable length argument list.
01b,05oct90,shl  added ANSI function prototypes.
                 made #endif ANSI style.
                 added copyright notice.
01a,10aug90,dnw  written
*/

#ifndef __INClogLibh
#define __INClogLibh

#include <vsbConfig.h>		/* for _Vx_usr_arg_t */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	_ASMLANGUAGE

/* function declarations */

extern STATUS 	logFdAdd (int fd);
extern STATUS 	logFdDelete (int fd);
extern void 	logFdSet (int fd);
extern void 	logShow (void);
extern void 	logTask (void);

/* __PROTOTYPE_5_0 is used for the tools */
#ifdef	__PROTOTYPE_5_0
extern int	logMsg (char *fmt, ...);
#else
extern int	logMsg (char *fmt, _Vx_usr_arg_t arg1, _Vx_usr_arg_t arg2,
	                _Vx_usr_arg_t arg3, _Vx_usr_arg_t arg4, 
	                _Vx_usr_arg_t arg5, _Vx_usr_arg_t arg6);
#endif /* __PROTOTYPE_5_0 */

/* function pointer prototypes */

extern int (*_func_logMsg)(char *fmt, _Vx_usr_arg_t arg1, 
                           _Vx_usr_arg_t arg2, _Vx_usr_arg_t arg3,
                           _Vx_usr_arg_t arg4, _Vx_usr_arg_t arg5,
                           _Vx_usr_arg_t arg6);

#endif /* !_ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INClogLibh */
