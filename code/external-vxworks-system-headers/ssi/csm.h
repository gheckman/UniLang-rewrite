/* csm.h - Contains definitions used by csm.c */

/* Copyright 2004-2005 Wind River Systems, Inc. */

/* 
Modification History
--------------------
01d,19jan06.xli  Added csmInit() to this header file.
01c,14jan06,tkf  Added CSM_EV_STR_NONE and corrected CSM_EV_STR_LAUNCH.
01b,09jan06,tkf  Fix DIAB compiler warnings.
01a,21aug05,tkf  Header file for csm.c
*/

/*
DESCRIPTION

This file contains the public definitions for CSM.

*/

#ifndef __INCcsmh
#define __INCcsmh
#ifdef  __cplusplus
extern "C" {
#endif /* __cplusplus */

/* enums */

/* defines */

#define CSM_EV_STR_MAX_LEN      16
#define CSM_EV_STR_NONE         "everror"        /* 'invalid' */
#define CSM_EV_STR_LAUNCH       "evlaunch"        /* 'launch' event:
                                                    Sent by CSM to components */
#define CSM_EV_STR_INITIALIZE   "evinit"        /* 'initialize' event:
                                                   Sent by CSM to components */
#define CSM_EV_STR_CREATED      "evcreated"     /* 'created' event:
                                                   Sent by components to CSM */
#define CSM_EV_STR_READY        "evready"       /* 'ready' event:
                                                   Sen by components to CSM */
#define CSM_EV_STR_MONITORED    "monitored"     /* 'ready' event:
                                                   Sen by components to CSM */
#define CSM_EV_STR_NEXT         "evnext"        /* 'next event':
                                                   Sent by components to CSM to
                                                   learn their next event */

/* The following defines are used to identify events internally */
#define CSM_EV_NONE         0   /* invalid event */
#define CSM_EV_LAUNCH       1   /* 'launch' event:
                               Sent by CSM to components */
#define CSM_EV_INITIALIZE   2   /* 'initialize' event:
                               Sent by CSM to components */
#define CSM_EV_CREATED      3   /* 'created' event:
                               Sent by components to CSM */
#define CSM_EV_READY        4   /* 'ready' event:
                               Sen by components to CSM */
#define CSM_EV_MONITORED    5   /* 'monitored' event
                                   sent by CSM to comps */
#define CSM_EV_NEXT         6   /* 'next event': Sent by components to CSM to
                                   learn their next event */

#define CSM_READ        1   /* CSM Read command */
#define CSM_WRITE       2   /* CSM Write command */

#define CSM_STATE_INVALID       -1
#define CSM_STATE_NEW           0
#define CSM_STATE_CREATED       1 
#define CSM_STATE_INITIALIZE  2
#define CSM_STATE_READY         3
#define CSM_STATE_MONITORED     4

/* typedefs */

/* forward declarations */
STATUS csmInit (BOOL useLocalReadServer);
IMPORT STATUS csmRead
    (char * pObj, char * pAppReadBuf, ulong_t bufLen, ulong_t * pReadLen);
IMPORT STATUS csmWrite
    (char * pObj, char * pReadBuf, ulong_t bufLen, char * pReplyBuf,
     ulong_t * pReplyDataLen);
IMPORT STATUS csmEventFormat
    (char *  pCompName, long reqType, long event, char * pBuf, long bufLen);
IMPORT void csmCompInit
    (char *  pComp);
IMPORT void csmCompReady
    (char *  pComp);
IMPORT STATUS csmEventStrToType
    (char *  pEvStr, long *  pEvInt);
IMPORT STATUS csmEventTypeToStr
    (long event, char *  pEvBuf, long evBufLen);
IMPORT STATUS csmDataFormat
    (char * pCompName, long event, char * pBuf, long bufLen);

#ifdef  __cplusplus
}
#endif /* __cplusplus */
#endif /* __INCcsmh */
