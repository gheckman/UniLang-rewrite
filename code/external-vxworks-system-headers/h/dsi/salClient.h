/* salClient.h -  socket application library client header file */

/* Copyright 2003 - 2004, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01g,28apr10,pad  Moved extern C statement after include statements.
01f,19may04,ymz  modified for coding convention
01e,08apr04,ymz  code review modifications.
01d,31mar04,ymz  renamed salFind to salSocketFind, added salNameFind.
01c,11mar04,ymz  removed salClose and client structure.
01b,20feb04,ymz  code review changes
01a,26nov03,als  created
*/

#ifndef __INCsalClienth
#define __INCsalClienth

/* includes */

#include "vxWorks.h"
#include "netdb.h"
#include "dsi/salCommon.h"

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

extern int  salOpen      (const char * servId);
extern int  salCall      (int sockfd, void * pSendBuff, int sendLen,
                          void * pRecvBuff, int recvLen);

extern STATUS  salSocketFind (const char * name, int sockFamily, 
                              int sockType, int sockProtocol, 
                              struct addrinfo ** ppSockInfoList);
extern int salNameFind (const char * pattern, 
                        char servName[][SAL_SERV_NAME_MAXSIZE], int num,
                        void  ** ppCookie);

#ifdef __cplusplus
}
#endif

#endif /* __INCsalClienth */

