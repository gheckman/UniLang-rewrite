/* loginLibCommon.h - common password/login subroutine library header file */

/* 
 * Copyright (c) 2006, 2010 Wind River Systems, Inc. 
 * 
 * The right to copy, distribute, modify, or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01d,30sep10,ggz  Add salt support
01c,28apr10,pad  Moved extern C statement after include statements.
01b,24oct06,v_r  Fixed defect CQ:WIND00054774 (loginLib does not support
                 encrypted passwords > 80 characters).
01a,26jun06,v_r  Written. Based on loginLib.h from kernel and user sides.
*/

#ifndef __INCloginLibCommonh
#define __INCloginLibCommonh

#include <vwModNum.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DOC
#define MAX_LOGIN_NAME_LEN    80
#define MAX_PASSWORD_LEN      128
#define AUTH_SALT_LENGTH      8 

/* Backward compatible version of the password field */

#define MAX_PASSWORD_LEN_OLD   80
#endif	/* DOC */

/* status messages */

#define S_loginLib_UNKNOWN_USER			(M_loginLib | 1)
#define S_loginLib_USER_ALREADY_EXISTS		(M_loginLib | 2)
#define S_loginLib_INVALID_PASSWORD		(M_loginLib | 3)

/* Structure for passing login user info to sysctl (backward compatible) */

struct loginVerifyArgsOld
    {
    char name[MAX_LOGIN_NAME_LEN+1];
    char passwd[MAX_PASSWORD_LEN_OLD+1];
    };

/* Structure for passing login user info to sysctl */

struct loginVerifyArgs 
    {
    char name[MAX_LOGIN_NAME_LEN+1];
    char passwd[MAX_PASSWORD_LEN+1];
    };

/* function declarations */

extern STATUS 	loginUserVerify (char * name, char * passwd);

#ifdef __cplusplus
}
#endif

#endif /* __INCloginLibCommonh */
