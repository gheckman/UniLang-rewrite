/* loginLib.h - user password/login subroutine library header file */

/* 
 * Copyright (c) 1984-2006, 2009-2010 Wind River Systems, Inc. 
 * 
 * The right to copy, distribute, modify, or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
02b,30sep10,ggz  Added salt support. 
02a,24aug10,ggz  Added SHA256 hash algorithm support.
01z,29apr10,pad  Moved extern C statement after include statements.
01y,08sep09,v_r  Moved loginPrompt2 to loginLibP.h
01x,25sep06,v_r  Fixed defect CQ:WIND00066254 (build warning because of
                 missing loginInit() signature).
01w,26jun06,v_r  Rework following split into user/kernel parts and common
		 header creation.
01v,10mar06,jmp  fixed loginUserAdd() arguments (SPR #117429).
01u,26apr04,bpn  Added loginPrompt2() prototype to fix SPR#96149.
01t,12feb04,asr  added #ifdef _WRS_KERNEL sections to allow loginLib.h
                 to be included from user and kernel mode builds. Also
                 added loginVerifyArgs structure for sysctl use.
01s,22sep92,rrr  added support for c++
01r,04jul92,jcf  cleaned up.
01q,26may92,rrr  the tree shuffle
01p,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed VOID to void
		  -changed copyright notice
01o,19aug91,rrr  fixed the ansi prototype for loginUserAdd
01d,01may91,jdi  added ifndef for DOC.
01c,21jan91,shl  fixed arguments type in loginUserAdd().
01b,05oct90,shl  added ANSI function prototypes.
                 made #endif ANSI style.
                 added copyright notice.
01a,18apr90,shl  written.
*/

#ifndef __INCloginLibh
#define __INCloginLibh

#include "loginLibCommon.h" 

#ifdef __cplusplus
extern "C" {
#endif

extern void	loginInit (void);
extern STATUS 	loginDefaultEncrypt (char * in, char *salt, size_t size,
                                     char * out);
extern STATUS 	loginPrompt (char * userName);
extern STATUS 	loginUserAdd (char name[MAX_LOGIN_NAME_LEN + 1],
                              char passwd[MAX_PASSWORD_LEN + 1],
   		              char salt[2 * AUTH_SALT_LENGTH]);
extern STATUS 	loginUserDelete (char * name, char * passwd);
extern void 	loginEncryptInstall (FUNCPTR rtn, int var);
extern void 	loginStringSet (char * newString);
extern void 	loginUserShow (void);
extern STATUS   loginEncryptGet (size_t *digest);

#ifdef __cplusplus
}
#endif

#endif /* __INCloginLibh */
