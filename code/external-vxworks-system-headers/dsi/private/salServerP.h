/* salServerP.h - socket application library server private header file */

/* Copyright 2003-2004, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01d,28apr10,pad  Moved extern C statement after include statements.
01c,10jun04,ymz  made salRegister and salUnregister private.
01b,01mar04,ymz  code review changes
01a,26nov03,als  created
*/

#ifndef __INCsalServerPh
#define __INCsalServerPh

/* includes */

#include "dsi/salServer.h"
#include "dsi/private/salCommonP.h"

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* number of backlog for SAL server listening */

#define SAL_LISTEN_BACKLOG   15

/* typedef */

/* SAL server handle */

typedef struct salServer                /* socket application server */
    {
    struct salServer * magic;           /* structure integrity check */
    snsServDesc service;                /* service descriptor */
    fd_set allSockets;                  /* all server sockets */
    fd_set readSockets;                 /* sockets used with read fn */
    int numSockets;                     /* # of server sockets */
    int maxSockfd;                      /* upper bound on server's fd's */
    SAL_SERV_RTN acceptFn;
                                        /* accept processing routine */
    SAL_SERV_RTN readFn;
                                        /* read processing routine */
    } SAL_SERVER;

/* function declarations */

extern SAL_SERVER_ID     salInit  (void);
extern STATUS  salTerm  (SAL_SERVER_ID servId);
extern snsServDesc salRegister (const char * name, 
                                struct addrinfo * pSockInfoList);
extern STATUS  salDeregister   (snsServDesc service);

#ifdef __cplusplus
}
#endif

#endif /* __INCsalServerPh */


