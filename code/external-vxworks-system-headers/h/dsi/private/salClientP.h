/* salClientP.h - socket application library client private header file */

/* Copyright 2003-2004, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01f,28apr10,pad  Moved extern C statement after include statements.
01e,16feb05,ebh  rename sockopt struct to salSockopt (it conflicts with
                 target/h/wrn/coreip/net/socketvar.h)
01d,19may04,ymz  coding convention alignment.
01c,08apr04,ymz  code review changes.
01b,23feb04,ymz  changed salClient to socket fd.
01a,26nov03,als  created.
*/

#ifndef __INCsalClientPh
#define __INCsalClientPh

/* includes */

#include "dsi/salClient.h"
#include "dsi/private/salCommonP.h"

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

extern int salSnsClientCreate (void);
extern STATUS salSnsClientDelete       (int  sockfd);
extern STATUS salSnsClientReplyCheck   (int actualSize, int expectedSize);
extern int  salAttach  (struct addrinfo * pSockInfoList,
                        struct salSockopt * pSockOptions, int numOptions);

#ifdef __cplusplus
}
#endif

#endif /* __INCsalClientPh */


