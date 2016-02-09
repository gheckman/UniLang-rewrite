/* cnsLib.h - Contains definitions used to communicate with the BSP */

/* Copyright 2004-2005 Wind River Systems, Inc. */

/* 
Modification History
--------------------
01f,09feb06,xli  define __SSI_DEBUG__ flag
01g,19jan06,xli  added cnsLibInit
01f,14jan06,tkf  Fix CNS_MSGTYPE_REPLY_OK and CNS_MSGTYPE_REPLY_ERR.
01e,09jan06,tkf  Change cnsConnErrorWrite() prototype. Fix DIAB compiler
                 errors.
01d,05jan05,tkf  Changed the accept prototype.
01c,19dec05,xli  Added the cnsIoctl API and the function pointer  
01b,19dec05,xli  Accept function pointer updated and cnsConnClose function signature changed
01a,21nov05,tkf  Header file for cnsLib.c
*/

/*
DESCRIPTION

This file contains the public definitions for the CNS library (cnsLib).

*/

#ifndef __INCcnsLibh
#define __INCcnsLibh
#ifdef  __cplusplus
extern "C" {
#endif /* __cplusplus */

/* enums */

/* Local API commands */
typedef enum
{
    CNS_LOCAL_WRITE = 1,
    CNS_LOCAL_READ
} cnsCmd_t;

/* defines */
#define CNS_MEDIA_NAME_LEN  16

#define CNS_LOCAL_MEDIA         "local"
#define CNS_CONNSTATE_NEW   0
#define CNS_CONNSTATE_LISTENING 1
#define CNS_CONNSTATE_CONNECTED (CNS_CONNSTATE_LISTENING << 1)
#define CNS_CONNSTATE_REMOVED   (CNS_CONNSTATE_LISTENING << 2)

/* Error message defines */
#define CNS_ERR_INVALID_MSG     "InvalidMsgRx"
#define CNS_ERR_INVALID_COMP    "InvalidCompName"
#define CNS_ERR_INVALID_OBJ     "InvalidObject"
#define CNS_ERR_WRITEREQ_ERR    "WriteRequestFailed"
#define CNS_ERR_READREQ_ERR     "ReadRequestFailed"
#define CNS_ERR_GEN             "GeneralError"

/* Message type defines */
#define CNS_MSGTYPE_READREQ         "readreq"
#define CNS_MSGTYPE_WRITEREQ        "writereq"
#define CNS_MSGTYPE_WRITEREQ_WACK   "writereqwack"
#define CNS_MSGTYPE_REPLY_OK        "writeok"
#define CNS_MSGTYPE_REPLY_ERR       "writeerr"

#define CNS_REQ_READ                1
#define CNS_REQ_WRITE               2
#define CNS_REQ_WRITE_WACK          3
#define CNS_REPLY_OK                4
#define CNS_REPLY_ERR               5

#if defined __SSI_DEBUG__
    #define SSI_PRINTF printf
#else
    #define SSI_PRINTF(...)
#endif /*__SSI_DEBUG__*/


/* TODO: Remove all code that originated from cnsLib */

/* typedefs */

/*
 * 'cnsMediaId_t'
 *
 * Members of 'cnsMediaId_t' are used to identify the media being used during
 * open/close, and read/write accesses.
 *
 * 'pName' specifies the name of the media together with the address and the
 * name of the component to which the media is bound. The below example
 * illustrates how 'pName' can be used:
 *
 * \cs
 * cnsOpen (&mediaId, TRUE);
 * \ce
 *
 * 'mediaId can take one of the following forms
 *
 * \cs
 * mediaId.compInfo = "compInfo";           /@ Caller assumed to be local.
 *                                             Use registered local API call @/
 * mediaId.compInfo = "local:/compInfo";    /@ Local caller.
 *                                             Use registered local API call @/
 * mediaId.compInfo = "/compInfo";          /@ Caller intra-target.
 *                                             Use default intra-target media @/
 * mediaId.compInfo = "comp:/compInfo";     /@ Use the "comp" media @/
 *
 * mediaId.compInfo = "tipc:/<tipcAddress>/compInfo"
 *                                          /@ External caller using the tipc
 *                                             media. @/
 * mediaId.compInfo = "tcpip:/<IP-Address>/compInfo"
 *                                          /@ External caller using the tipc
 *                                              media. @/
 * \ce
 *
 * 'connId' is returned by cnsOpen() and it identifies a specific connection
 * via the media.
 */
typedef struct
{
    char *  pName;          /* Identifies the media to be used */
    long    mediaTypeId;    /* Media Type - returned by cnsOpen() */
    long    connId;         /* Connection ID - returned by cnsOpen */
} cnsMediaId_t;

/*
 * 'CNS_APP_WRITE_FUNCPTR' defines a type of a pointer to local WRITE
 * function.
 */
typedef STATUS (* CNS_APP_WRITE_FUNCPTR)(char * pObj, char * pBuf,
                                         ulong_t bufLen, char * pReplyBuf,
                                         ulong_t * pBytesWriten);

/*
 * 'CNS_APP_READ_FUNCPTR' defines a type of a pointer to local READ
 * function.
 */
typedef STATUS (* CNS_APP_READ_FUNCPTR)(char * pObj, char * pBuf,
                                        ulong_t bufLen, ulong_t * pBytesRead);

/*
 * 'CNS_OPEN_FUNCPTR' defines a type of a pointer to function that is used to
 * open/create a media.
 */
typedef STATUS (* CNS_OPEN_FUNCPTR)(char * pName, BOOL create, long * pConnId,
                            long * pConnState);

/*
 * 'CNS_CLOSE_FUNCPTR' defines a type of a pointer to function that is used to
 * close an open media.
 */
typedef STATUS (* CNS_CLOSE_FUNCPTR)(long connId);

/*
 * 'CNS_ACCEPT_FUNCPTR' defines a type of a pointer to function that is used to
 * accept a connection request on an open media.
 */
typedef STATUS (* CNS_ACCEPT_FUNCPTR)(long connId, void * pLocalAddr,
                                      int localAddrLen, long * pNewConnId);
/*
 * 'CNS_IOCTL_FUNCPTR' defines a type of a pointer to function that is used to
 * call ioctl on an open media.
 */
typedef STATUS (* CNS_IOCTL_FUNCPTR)(long connId,
                                     long function,
                                     long arg );
/*
 * 'CNS_READ_FUNCPTR' defines a type of a pointer to function that is used to
 * read from a media.
 */
typedef STATUS (* CNS_READ_FUNCPTR)(long connId, char * pBuf, 
                                    ulong_t bufLen, ulong_t * pReadBytes);
/*
 * 'CNS_WRITE_FUNCPTR' defines a type of a pointer to function that is used to
 * write to a media.
 *
 * For non-local media type, 'pReplyBuf' and 'pReplyLen' are always NULL.
 */
typedef STATUS (* CNS_WRITE_FUNCPTR)(long connId, char * pBuf, 
                                     ulong_t bufLen, char * pReplyBuf,
                                     ulong_t * pReplyLen);

/*
 * 'CNS_CONN_VALID_FUNCPTR' defines a type of a pointer to function that is
 * used to validate an open connection.
 */
typedef BOOL (* CNS_CONN_VALID_FUNCPTR)(long connId);

/*
 * 'CNS_MEDIATYPE_ADD_FUNCPTR' defines a type of a pointer to function that
 * 'cnsLib' calls everytime a new media type is registered.
 */
typedef STATUS (* CNS_MEDIATYPE_ADD_FUNCPTR)(void * pApp, long type);

/*
 * 'CNS_MEDIATYPE_REMOVE_FUNCPTR' defines a type of a pointer to function that
 * 'cnsLib' calls everytime a media type is de-registered.
 */
typedef STATUS (* CNS_MEDIATYPE_REMOVE_FUNCPTR)(void * pApp, long type);

/*
 * 'CNS_DATA_PARSE_FUNCPTR' defines a type of a pointer to function that
 * 'cnsLib' calls when parsing data belonging to a registered application.
 */
typedef STATUS (* CNS_DATA_PARSE_FUNCPTR)(char * pData,char ** ppObj,
                char ** ppTrailer);

/*
 * 'cnsMediaInfo_t'
 *
 * Members of the 'cnsMediaInfo_t' structure represent the information passed
 * when registering the communication media.
 *
 * 'pName' identifies the media type.
 *
 * 'openFunc' is a pointer to the routine to open the media.
 *
 * 'readFunc' is a pointer to the routine used to read from the media.
 *
 * 'writeFunc' is a pointer to the routine to wtite to the media.
 *
 * 'closeFunc' is a pointer to the routine to close the media.
 */
typedef struct
{
    char *                  pName;
    CNS_OPEN_FUNCPTR        openFunc;
    CNS_READ_FUNCPTR        readFunc;
    CNS_WRITE_FUNCPTR       writeFunc;
    CNS_CLOSE_FUNCPTR       closeFunc;
    CNS_ACCEPT_FUNCPTR      acceptFunc;
    CNS_IOCTL_FUNCPTR       ioctlFunc;
    CNS_CONN_VALID_FUNCPTR  connIsValid;    /* Not used currently */
} cnsMediaInfo_t;

/* forward declarations */
STATUS cnsLibInit 
    ( ulong_t  maxMediaCount);

IMPORT STATUS cnsOpen
    (cnsMediaId_t * pMedia, BOOL create, long * pConnState);
IMPORT STATUS cnsClose
    (cnsMediaId_t * pMedia);
IMPORT STATUS cnsRead
    (cnsMediaId_t * pMedia, char * pReqBuf, char * pBuf, ulong_t bufLen,
     ulong_t * pReadLen);
IMPORT STATUS cnsWrite
    (cnsMediaId_t * pMedia, char * pReqBuf, char * pBuf, ulong_t bufLen,
     char * pReplyBuf, ulong_t * pReplyLen);

IMPORT STATUS cnsValidate (cnsMediaId_t *pMediaId);

IMPORT STATUS cnsMediaRegister
    (cnsMediaInfo_t * pDefMedia);

IMPORT STATUS cnsAppRegister
    (char * pName,
     CNS_APP_READ_FUNCPTR readFunc,
     CNS_APP_WRITE_FUNCPTR writeFunc,
     CNS_MEDIATYPE_ADD_FUNCPTR mediaTypeAddFunc,
     CNS_MEDIATYPE_REMOVE_FUNCPTR mediaTypeRemove,
    CNS_DATA_PARSE_FUNCPTR dataParse
     );

IMPORT STATUS cnsConnClose
    (long mediaType, long connId);

IMPORT STATUS cnsConnAccept
    (long mediaType, long connId, void * pLocalAddr, long localAddrLen,
     long * pConnId);

IMPORT STATUS cnsConnOpen
    (long mediaType, char * pAppName, BOOL create, long * pConnId,
     long * pConnState);

IMPORT STATUS cnsConnRead
    (long mediaType, long connId, char * pReadBuf, ulong_t bufLen,
     ulong_t * pReadLen);

IMPORT STATUS cnsConnWrite
    (long mediaType, long connId, char * pWriteBuf, ulong_t bufLen,
     char * pReplyBuf, ulong_t * pReplyLen);

IMPORT STATUS cnsConnErrorWrite
    (long mediaType, long connId, char * pWriteBuf, long bufLen);
IMPORT STATUS cnsMsgEncode
    (long type, char * pData, char * pFormat, ulong_t * pFormatLen);
#ifdef  __cplusplus
}
#endif /* __cplusplus */
#endif /* __INCcnsLibh */
