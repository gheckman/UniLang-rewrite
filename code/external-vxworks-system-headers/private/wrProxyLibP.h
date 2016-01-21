/* wrProxyLibP.h - private proxy interface header */

/*
 * Copyright (c) 2005-2006,2009,2011-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
 
/*
modification history
--------------------
01g,06jan12,elp  added amio protocol handling,
		 made wrProxyServerCreate() external, added
		 wrProxyServerDelete().
01f,22apr11,rlp  Added wrProxySslCertGen prototype from wrProxyLib.h.
01e,01apr11,rlp  Fixed dependencies on SSL library.
01d,22mar11,rlp  Added SSL support.
01c,17nov09,jmp  LP64 Adaptation.
01b,20jun06,dbt  Added <pServer> list in proxy structure
		 Removed pProxyList global variable.
01a,15apr05,dbt  written
*/

#ifndef __INCwrProxyLibPh
#define __INCwrProxyLibPh

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HOST
#ifndef WIN32
#include <netinet/in.h>
#endif /* WIN32 */
#else
#include <netinet/in.h>
#endif /* HOST */

/* Connection status */

#define	PROXY_STATUS_CONNECTED	1	/* proxy connected to target */

/* defines */

#ifdef WIN32
#define	CLOSE_SOCKET		closesocket
#else /* WIN32 */
#define	CLOSE_SOCKET		close
#endif /* WIN32 */

/* error messages */

#define PROXY_MEM_ALLOC_FAILURE		"wrproxy: Error allocating memory"
#define	PROXY_CMDLINE_PARSE_ERROR	"wrproxy: Error parsing command line"
#define PROXY_PPORT_PARSE_ERROR	"wrproxy: Unable to parse pport argument"
#define PROXY_PPORT_ALREADY_IN_USE	\
			"wrproxy: Specified proxy port is already in use"

#define	PROXY_PPORT_OPTION_NAME		"pport="

/* Proxy connection mode */

typedef enum proxy_mode 
    {
    PROXY_MODE_RAW	= 0,	/* raw mode */
    PROXY_MODE_PACKET	= 1	/* packet mode */
    } PROXY_MODE;

/* Proxy connection protocol */

typedef enum proxy_protocol
    {
    PROXY_PROT_RAW		= 0,	/* raw protocol */
    PROXY_PROT_WDBSERIAL	= 1,	/* wdbserial protocol */
    PROXY_PROT_AMIO		= 2	/* amio protocol */
    } PROXY_PROTOCOL;

typedef enum proxy_port_type
    {
    PORT_UDP    = 0,
    PORT_TCP    = 1,
    PORT_SERIAL = 2,
#ifdef  _WRS_CONFIG_SSL
    PORT_SSL	= 3,
#endif /* _WRS_CONFIG_SSL */
    } PROXY_PORT_TYPE;

/* Proxy maximum packet size */

#define	PROXY_MAX_PACKET_SIZE	4000

/* typedefs */

typedef struct proxy_server	/* Proxy Server description */
    {
    void *			next;		/* next proxy connection */
    						/* in list */
    void *			prev;		/* previous proxy connection */
    						/* in list */
    char *			cnctArgs;	/* optional connect args */
    int				sockId;		/* server socket id */
    int				cnctMaxNum;	/* maximum number of */
    						/* simultaneous connections */
						/* for this server */
    int				cnctNum;	/* current number of */
    						/* connections for this */
						/* server */
    u_short			portNumber;	/* port number used for this */
    						/* server connection */
    PROXY_PORT_TYPE		portType;	/* proxy port type */
    struct sockaddr_in		svrAddr;	/* server address */
    } PROXY_SERVER;

typedef struct proxy_connection
    {
    void *			next;		/* next proxy connection */
    						/* in list */
    void *			prev;		/* previous proxy connection */
    						/* in list */
    struct proxy_bkend_proto * 	pProto;		/* protocol used by this */
    						/* connection */
    void *			protoArgs;	/* connection specific */
    						/* protocol args */
    struct proxy_backend *	pBackend;	/* backend used by this */
    						/* connection */
    void *			backendArgs;	/* connection specific */
    						/* backend args */
    char *			buffer;		/* buffer used for wdbserial */
    						/* protocol */
    struct proxy_server *	pServer;	/* server that has been used */
    						/* to establish connection */
#ifdef	_WRS_CONFIG_SSL
    void *			pSsl;		/* TLS/SSL connection cookie */
#endif	/* _WRS_CONFIG_SSL */
    int				clientFd;	/* client file descriptor */
    int				status;		/* connection status */
    int				tgtFd;		/* target file descriptor */
    int				bufIx;		/* buffer index */
    PROXY_MODE			mode;		/* connection mode (raw, */
    						/* packet) */
    PROXY_PROTOCOL		protocol;	/* connection protocol */
    } PROXY_CONNECTION;

/* function declarations */

extern int wrProxyClientCommandArgGet (char * args, const char * argName,
					int * pIntResult,
					char * pCharResult, UINT32 length);
extern void wrProxyClientCommandArgRemove (char * args, const char * argName);
extern int wrProxyClientCommandArgInstGet (char * args, const char * argName,
					   int * pIntResult,
					   char * pCharResult, UINT32 length,
					   char ** pNextStart);
extern PROXY_SERVER * wrProxyServerCreate (u_short portNumber,
					   PROXY_PORT_TYPE portType,
					   int cnctMaxNum, char * cnctArgs,
					   char * errorMsg, int errorMsgLength);
extern STATUS wrProxyServerDelete (u_short portnumber,
				   PROXY_PORT_TYPE portType);

extern int wrProxyClientWrite (PROXY_CONNECTION * pProxy, char * buffer,
			       int nBytes);
extern void wrProxyTask (void);

#ifdef	_WRS_CONFIG_SSL
extern void *   wrProxySslConnectionCreate (int sock, BOOL  server);
extern void     wrProxySslConnectionDelete (void * pCookie);
extern ssize_t  wrProxySslRead (void * pCookie, char * buf, size_t size);
extern ssize_t  wrProxySslWrite (void * pCookie, char * buf, size_t size);

#ifndef	HOST
extern STATUS   wrProxySslCertGen (char * certRepo, int rsaKeyLength,
				   char * startDate, char * endDate,
				   long numDays);
extern void *   (*_func_wrProxySslConnectionCreate) (int sock, BOOL  server);
extern void     (*_func_wrProxySslConnectionDelete) (void * pCookie);
extern ssize_t  (*_func_wrProxySslRead) (void * pCookie,
					char * buf, size_t size);
extern ssize_t  (*_func_wrProxySslWrite) (void * pCookie,
					 char * buf, size_t size);
#endif	/* HOST */
#endif	/* _WRS_CONFIG_SSL */

#ifdef __cplusplus
}
#endif

#endif	/* __INCwrProxyLibPh */
