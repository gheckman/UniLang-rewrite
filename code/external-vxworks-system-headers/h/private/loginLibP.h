/* loginLibP.h - private user password/login subroutine library header file */

/* 
 * Copyright (c) 2009-2010 Wind River Systems, Inc. 
 * 
 * The right to copy, distribute, modify, or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01c,02aug10,v_r  Added LOGIN_NO_PASSWORD_CHECK flag, loginStringGet()
		 prototype (req CQ:WIND00190686) as well as function bindings.
01b,06jul10,v_r  Added login security facility boolean (req CQ:WIND00190686).
01a,08sep09,v_r  Split from loginLib.h
		 Updated loginPrompt2 signature following loginLib def
                 CQ:WIND00155318 fix, merged from 6.5 sustaining).
*/

#ifndef __INCloginLibPh
#define __INCloginLibPh

#ifdef __cplusplus
extern "C" {
#endif

/* System-wide login security setting */

extern BOOL systemSecurityIsEnabled;

/* Function bindings */

extern void (* _func_loginStringSet)
    (
    char * newString /* string to become new login prompt */
    );

extern size_t (* _func_loginStringGet)
    (
    char *  loginStringBuf, /* buffer to hold current login string */
    size_t  bufSize         /* buffer size */
    );

extern STATUS (* _func_loginPrompt2)
    (
    char *  userName,       /* user name, ask if NULL or not provided */
    UINT32  options,        /* option flags to control routine behavior */
    char *  pUserName,      /* user which logged in */
    size_t  nameLength,     /* length of username field */
    char *  pUserPasswd,    /* password of logged in user */
    size_t  passwdLength    /* length of password field */
    );

/* Timeout is enabled at login prompt */

#define LOGIN_WITH_TIMEOUT  0x2

/* Do not set global user id/password (using remCurIdSet) after login */

#define LOGIN_NO_REMID_SET  0x4

/* Do not perform password verification */

#define LOGIN_NO_PASSWORD_CHECK 0x8

extern STATUS   loginPrompt2 (char * userName, UINT32 options,
                              char * loginUserName, size_t nameLength,
                              char * loginUserPasswd, size_t passwdLength);
extern void	usrSecurity (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCloginLibPh */
