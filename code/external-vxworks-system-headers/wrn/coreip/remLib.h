/* remLib.h - structures for remLib.c */

/*
 * Copyright (c) 1984-2005, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

/*
modification history
--------------------
01k,09jan12,h_x  Move extern "C" after last header file include.
01j,01oct10,rlp  Removed iam and whoami prototypes.
01i,24jun05,vvv  added rcmd_af()
01h,22feb05,wap  Allow sysctl init routines to be scaled out
o1g,23feb04,kkz  added new functions for user-space
01f,04nov03,rlm  Ran batch header path update for header re-org.
01e,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01d,24oct03,cdw  update include statements post header re-org.
01c,09may03,vvv  included socket.h
01b,10jun02,ann  forward declarations for rresvportCommon() and
                 bindresvportCommon()
01a,06mar02,ann  ported to clarinet from AE1.1 ver 02d 
*/

#ifndef __INCremLibh
#define __INCremLibh

#include <netinet/in.h>
#include <sockLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_IDENTITY_LEN	100
#define MIN_RESV_PORT           600
#define MAX_RESV_PORT          1023

/* status messages */

#define S_remLib_ALL_PORTS_IN_USE		(M_remLib | 1)
#define S_remLib_RSH_ERROR			(M_remLib | 2)
#define S_remLib_IDENTITY_TOO_BIG		(M_remLib | 3)
#define S_remLib_RSH_STDERR_SETUP_FAILED	(M_remLib | 4)
#define S_remLib_RCMD_INPUT_ERROR               (M_remLib | 5)

/* variable declarations */

extern int	remLastResvPort;        /* last port num used (from bootroms) */

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)
extern void     remLibInit (long timeout);
extern void	remLibSysctlInit(void);
extern STATUS 	bindresvport (int sd, struct sockaddr_in *sin);
extern STATUS 	bindresvport_af (int sd, struct sockaddr *sin, int family);
extern int 	rcmd (char *host, int remotePort, char *localUser,
		      char *remoteUser, char *cmd, int *fd2p);
extern int 	rcmd_af (char *host, int remotePort, char *localUser,
		         char *remoteUser, char *cmd, int *fd2p, int family);
extern int 	rresvport (int *alport);
extern int 	rresvport_af (int *alport, int family);
extern void 	remCurIdGet (char *user, char *passwd);

#ifdef _WRS_KERNEL
extern STATUS 	remCurIdSet (char *newUser, char *newPasswd);
#else
extern STATUS setlogin    (char * login);
extern STATUS getlogin_r (char * login, size_t length);
extern STATUS setpassword(char * passwd);
extern STATUS getpassword_r(char * passwd, size_t length);
#endif

/* deprecated functions - use rresvport_af and bindresvport_af instead */
extern int 	rresvportCommon (int *alport, int family);
extern STATUS 	bindresvportCommon (int sd, struct sockaddr *sin, int family);
#else	/* __STDC__ */

extern void     remLibInit ();
extern void	remLibSysctlInit();
extern STATUS 	bindresvport ();
extern STATUS 	bindresvport_af ();
extern int 	rcmd ();
extern int 	rresvport ();
extern int 	rresvport_af ();
extern void 	remCurIdGet ();

#ifdef _WRS_KERNEL
extern STATUS 	remCurIdSet ();
extern STATUS 	iam ();
extern void 	whoami ();
#else
extern STATUS setlogin ();
extern STATUS getlogin_r ();
extern STATUS setpassword ();
extern STATUS getpassword_r ();
#endif

/* deprecated functions - use rresvport_af and bindresvport_af instead */
extern STATUS 	bindresvportCommon ();
extern int 	rresvportCommon ();
#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCremLibh */
