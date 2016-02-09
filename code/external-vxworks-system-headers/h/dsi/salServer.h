/* salServer.h - socket application library server header file */

/* Copyright 2003-2004, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01h,28apr10,pad  Moved extern C statement after include statements.
01g,16feb05,ebh  rename sockopt struct to salSockopt (it conflicts with
                 target/h/wrn/coreip/net/socketvar.h)
01f,07jun04,ymz  removed private functions.
01e,19may04,ymz  changed for coding convention.
01d,13apr04,ymz  code review changes.
01c,30mar04,ymz  added salRemove, modified to event based cleanup.
01b,13feb04,ymz  added timeoutFn entry to salServer.
01a,26nov03,als  created
*/

#ifndef __INCsalServerh
#define __INCsalServerh

/* includes */

#include "vxWorks.h"
#include "netdb.h"
#include "dsi/snsLib.h"

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

/* SAL server processing routine type */

typedef enum 
    {
    SAL_RTN_READ = 1,    /* socket read routine Id */
    SAL_RTN_ACCEPT       /* socket accept routine Id */
    } SAL_RTN_TYPE;

/* return value from SAL processing routine indicating salRun what to do */

typedef enum
    {
    SAL_SOCK_KEEP,                      /* keep the socket */
    SAL_SOCK_CLOSE,                     /* close the socket */
    SAL_SOCK_IGNORE,                    /* do not polling the socket any more */
    SAL_RUN_TERMINATE                   /* terminate salRun */
    } SAL_RTN_STATUS;

/* typedef SAL server processing routine */

typedef SAL_RTN_STATUS (* SAL_SERV_RTN)(int sockfd, void * pData);

typedef struct salServer * SAL_SERVER_ID;

/* function declarations */

extern SAL_SERVER_ID  salCreate    (const char * name, int sockFamily, 
                                    int sockType, int sockProtocol, 
                                    const struct salSockopt * options, 
                                    int numOptions);

extern STATUS  salDelete    (SAL_SERVER_ID  servId);

extern STATUS  salServerRtnSet (SAL_SERVER_ID  servId, SAL_RTN_TYPE id, 
                                SAL_SERV_RTN rtn);

extern STATUS  salRun       (SAL_SERVER_ID servId, void * pData);

extern STATUS  salRemove   (const char * name);

#ifdef __cplusplus
}
#endif

#endif /* __INCsalServerh */

