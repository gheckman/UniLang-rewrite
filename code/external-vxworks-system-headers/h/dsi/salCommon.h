/* salCommon.h - socket application library common header file */

/* Copyright 2003-2005, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01e,28apr10,pad  Moved extern C statement after include statements.
01d,16feb05,ebh  rename sockopt struct to salSockopt (it conflicts with
                 target/h/wrn/coreip/net/socketvar.h)
01d,09feb05,vvv  temporary change to workaround sockopt redefinition
01c,20apr04,ymz  code review changes.
01b,03dec03,als  snsLib error codes now part of salLib.
01a,26nov03,als  created.
*/

#ifndef __INCsalCommonh
#define __INCsalCommonh

/* includes */

#include "vwModNum.h"

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* error codes */
#define S_salLib_INTERNAL_ERROR             (M_salLib | 0x0001)
#define S_salLib_INVALID_ARGUMENT           (M_salLib | 0x0002)
#define S_salLib_SNS_UNAVAILABLE            (M_salLib | 0x0003)
#define S_salLib_SNS_DID_NOT_REPLY          (M_salLib | 0x0004)
#define S_salLib_SNS_PROTOCOL_ERROR         (M_salLib | 0x0005)
#define S_salLib_CLIENT_SOCKET_ERROR        (M_salLib | 0x0006)
#define S_salLib_SERVER_SOCKET_ERROR        (M_salLib | 0x0007)
#define S_salLib_SERVER_EXIT                (M_salLib | 0x0008)
#define S_salLib_SNS_INTERNAL_ERROR         (M_salLib | 0x0009)
#define S_salLib_SNS_OUT_OF_MEMORY          (M_salLib | 0x000a)
#define S_salLib_INVALID_SERVICE_ID         (M_salLib | 0x000b)
#define S_salLib_INVALID_SERVICE_DESCRIPTOR (M_salLib | 0x000c)
#define S_salLib_SERVICE_NOT_FOUND          (M_salLib | 0x000d)
#define S_salLib_SERVICE_ALREADY_EXISTS     (M_salLib | 0x000e)
#define S_salLib_NO_SOCKET_FOUND            (M_salLib | 0x000f)

#define SAL_SERV_NAME_MAXSIZE 63    /* max length for an SAL service name */
                                    /* (including trailing null) */

/* typedefs */

struct salSockopt                           /* socket option structure */
    {
    int so_level;                           /* option level */
    int so_name;                            /* option name */
    void * so_value;                        /* ptr to option value */
    int so_length;                          /* option length */
    };

#ifdef __cplusplus
}
#endif

#endif /* __INCsalCommonh */

