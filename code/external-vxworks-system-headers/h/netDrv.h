/* netDrv.h - netDrv header */

/* Copyright 1984-2003, 2010-2011 Wind River Systems, Inc. */

/*
modification history
--------------------
01h,28dec11,zly  Fix defect WIND00266530,dirList does not send the output to
                 specified fd when listing a network mounted drive.
01g,29jul10,pad  Moved extern C statement after include statements.
01f,05nov03,cdw  Removal of unnecessary _KERNEL guards.
01e,04nov03,rlm  Ran batch header path update for header re-org.
01d,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01c,10jun03,vvv  include netVersion.h
01b,19jul02,ppp  merging from veloce version 01m
01a,06mar02,ann  ported to clarinet from AE1.1 ver 01m
*/

#ifndef __INCnetDrvh
#define __INCnetDrvh

#include <vwModNum.h>
#include <netVersion.h>

#ifdef __cplusplus
extern "C" {
#endif

/* netDrv status codes */

#define S_netDrv_INVALID_NUMBER_OF_BYTES	(M_netDrv | 1)
#define S_netDrv_SEND_ERROR			(M_netDrv | 2)
#define S_netDrv_RECV_ERROR			(M_netDrv | 3)
#define S_netDrv_UNKNOWN_REQUEST		(M_netDrv | 4)
#define S_netDrv_BAD_SEEK			(M_netDrv | 5)
#define S_netDrv_SEEK_PAST_EOF_ERROR		(M_netDrv | 6)
#define S_netDrv_BAD_EOF_POSITION		(M_netDrv | 7)
#define S_netDrv_SEEK_FATAL_ERROR		(M_netDrv | 8)
#define	S_netDrv_WRITE_ONLY_CANNOT_READ		(M_netDrv | 9)
#define	S_netDrv_READ_ONLY_CANNOT_WRITE		(M_netDrv | 10)
#define	S_netDrv_READ_ERROR			(M_netDrv | 11)
#define S_netDrv_WRITE_ERROR			(M_netDrv | 12)
#define S_netDrv_NO_SUCH_FILE_OR_DIR		(M_netDrv | 13)
#define S_netDrv_PERMISSION_DENIED		(M_netDrv | 14)
#define S_netDrv_IS_A_DIRECTORY			(M_netDrv | 15)
#define S_netDrv_UNIX_FILE_ERROR		(M_netDrv | 16)
#define S_netDrv_ILLEGAL_VALUE			(M_netDrv | 17)

/* flags for debuging */

#define NETLIB_DEBUG_OFF			0
#define NETLIB_DEBUG_ERRORS			1
#define NETLIB_DEBUG_ALL			2

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern STATUS   netDrvDebugLevelSet (UINT32 debugLevel);
extern STATUS 	netDevCreate (char *devName, char *host, int protocol);
extern STATUS 	netDrv (void);
extern STATUS   netLsByName (char *dirName, int fd);

#else	/* __STDC__ */

extern STATUS   netDrvDebugLevelSet ();
extern STATUS 	netDevCreate ();
extern STATUS 	netDrv ();
extern STATUS   netLsByName ();

#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCnetDrvh */
