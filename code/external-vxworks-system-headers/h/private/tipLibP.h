/* tipLibP.h - serial connection management library private header */

/*
 * Copyright (c) 2008-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01f,30nov10,jmp  Fixed build warnings (CQ:WIND00243794).
01e,29apr10,pad  Moved extern C statement after include statements.
01d,01jul09,jmp  Moved tipLib function pointers from funcBindP.h.
01c,15jun09,jmp  Adapted for 64-bit support.
01b,16sep08,v_r	 Added function pointers to decouple from network and shell (def
		 CQ:WIND00134830).
01a,11sep08 v_r  Written. Contains private interface of the tip library (req
		 CQ:WIND00114857).
*/

#ifndef __INCtipLibPh
#define __INCtipLibPh 

#include <shellLib.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Typedefs */

typedef struct tip_func_ptr
    {
    SHELL_ID		(* shellFromTaskGetPtr) (TASK_ID taskId);
    STATUS		(* shellHookSetPtr) (SHELL_ID shellId);
    STATUS		(* shellHookUnsetPtr) (SHELL_ID shellId);
    struct hostent *	(* getHostByNamePtr) (const char * hostId);
    uint32_t		(* inetAddrPtr) (const char * hostId);
    void		(* hostEntFreePtr) (struct hostent * pHost);
    int			(* socketPtr) (int domain, int type, int protocol);
    STATUS		(* connectPtr) (int sockId,
					const struct sockaddr * host,
					socklen_t addr_len);
    STATUS		(* setSockOptPtr) (int socket, int level, int optName, 
					   const void * optVal,
					   socklen_t optLen);
    } TIP_FUNC_PTR;

/* Tip library function pointer */

extern void (* _func_tipStart)
    (
    char *  dev1Str,	/* first device configuration string */
    va_list argList,	/* other arguments */
    int	    options	/* special options */
    );

/* Function declarations */

extern void tipLibInit (char * configString, char * escapeCharStr, 
			TIP_FUNC_PTR * pTipPtrs);
extern void tipStart (char * dev1Str, va_list argList, int options);

#ifdef __cplusplus
}
#endif
#endif /* __INCtipLibPh */

