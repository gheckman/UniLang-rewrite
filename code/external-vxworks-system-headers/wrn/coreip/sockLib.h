/* sockLib.h -  UNIX BSD 4.3 compatible socket library header */

/*
* Copyright (c) 1984-2005, 2009 Wind River Systems, Inc.
*
* The right to copy, distribute or otherwise make use of this software
* may be licensed only pursuant to the terms of an applicable Wind River
* license agreement.
*/

/*
modification history
--------------------
03p,05jan11,h_x  Fix WIND00248759
03o,28may09,dlk  Change to Posix-compatible signatures, apart from 'restrict'
                 (LP64 conversion).
03n,17aug05,mcm  Using sys/time.h for RTP space.
03m,14sep04,dlk  Omit kernel APIs when _WRS_KERNEL is not defined.
03n,28may04,dlk  Make all socket back-ends share a single IO system device.
		 Remove fdMax parameter to sockLibInit().
03m,24mar04,mcm  Including time.h instead of sys/time.h.
03m,28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
                 /main/vdt/base6_itn5-int/1)
03l,18nov03,nee  adding <sys/time.h> for RTPs
03k,05nov03,cdw  Removal of unnecessary _KERNEL guards.
03j,04nov03,rlm  Ran batch header path update for header re-org.
03i,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
03h,27oct03,cdw  update include statements post header re-org.
03g,24oct03,cdw  update include statements post header re-org.
03f,10jun03,vvv  include netVersion.h
03e,27feb02,ann  correcting the path to sockFunc.h after relocation
03d,02feb02,ham  changed for tornado build.
03c,30oct01,ppp  merging from munich
03b,28aug01,ann  correcting the return value in the prototype for sockLibInit
03a,15aug01,ann  ported to clarinet from AE1.1 version 02l.
*/

#ifndef __INCsockLibh
#define __INCsockLibh

#ifdef _WRS_KERNEL    
#include <sys/times.h>
#else
#include <sys/time.h>    
#endif
#include <sys/socket.h>
#include <netVersion.h>

#include <version.h>

/* typedefs */

#ifdef _WRS_KERNEL
#include <sockFunc.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WRS_KERNEL
typedef struct sockLibMap
    {
    int			domainMap;	/* mapping address family  */
    int			domainReal;	/* real address family     */
    SOCK_FUNC *		pSockFunc;	/* socket function table   */
    struct sockLibMap *	pNext;		/* next socket lib mapping */
    } SOCK_LIB_MAP;
#endif /* _WRS_KERNEL */

struct sockFunc; /* See sockFunc.h */

typedef struct sockFunc * (*SOCK_LIB_INIT_RTN) (void);

/* function declarations */

#ifdef _WRS_KERNEL
extern STATUS   sockLibInit (void);
extern STATUS 	sockLibAdd (SOCK_LIB_INIT_RTN sockLibInitRtn, int domainMap,
                            int domainReal);
#endif /* _WRS_KERNEL */

extern int 	accept (int s, struct sockaddr *addr, socklen_t *addrlen);
extern STATUS 	bind (int s, const struct sockaddr *name, socklen_t namelen);
extern STATUS 	connect (int s, const struct sockaddr *name,
			 socklen_t namelen);

#if defined(_WRS_KERNEL) ||			\
    defined(RUNTIME_64BIT_NAME) /* FIXME */ ||	\
    (_WRS_VXWORKS_MAJOR >= 6 && _WRS_VXWORKS_MINOR >= 9)
extern STATUS 	connectWithTimeout (int sock, const struct sockaddr *adrs,
				    socklen_t adrsLen, const struct timeval *timeVal);
#else
extern STATUS 	connectWithTimeout (int sock, struct sockaddr *adrs,
				    int adrsLen, struct timeval *timeVal);
#endif

extern STATUS 	getpeername (int s, struct sockaddr *name, socklen_t *namelen);
extern STATUS 	getsockname (int s, struct sockaddr *name, socklen_t *namelen);
extern STATUS 	getsockopt (int s, int level, int optname, void *optval,
			    socklen_t *optlen);
extern STATUS 	listen (int s, int backlog);
extern ssize_t 	recv (int s, void *buf, size_t bufLen, int flags);
extern ssize_t 	recvfrom (int s, void *buf, size_t bufLen, int flags,
			  struct sockaddr *from, socklen_t *pFromLen);
extern ssize_t	recvmsg (int sd, struct msghdr *mp, int flags);
extern ssize_t 	send (int s, const void *buf, size_t bufLen, int flags);
extern ssize_t 	sendmsg (int sd, const struct msghdr *mp, int flags);
extern ssize_t 	sendto (int s, const void *buf, size_t bufLen, int flags,
			const struct sockaddr *to, socklen_t tolen);
extern int 	setsockopt (int s, int level, int optname, const void *optval,
			    socklen_t optlen);
extern STATUS 	shutdown (int s, int how);
extern int 	socket (int domain, int type, int protocol);

#ifdef __cplusplus
}
#endif

#endif /* __INCsockLibh */
