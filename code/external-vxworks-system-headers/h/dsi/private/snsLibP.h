/* snsLibP.h - Socket Name Service library private header file */

/*
 * Copyright (c) 2003-2005, 2007, 2010-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01n,19jul11,shi  LP64 conversion
01m,28apr10,pad  Moved extern C statement after include statements.
01l,15oct07,ebh  Added new command DSAL_CMD_SNS_NETWORK
01k,04jan07,mze  added extern of new snsfreeaddrinfo
01j,10may05,ebh  update to use a single instance for distributed SAL
                 ensure all fields are 32-bit values for dsal messaging
01i,25apr05,ebh  fix structure for distributed removal messages
01h,07mar05,ebh  added sockaddr_max structure to the sns_register_reply struct
                 added distributed SAL define(s)
01g,01sep04,ymz  added snsPatchMatch prototyping.
01f,19may04,ymz  coding convention alignment.
01e,13apr04,ymz  code review changes.
01d,30mar04,ymz  added new messaging types.
01c,02mar04,ymz  code review changes
01b,09feb04,ymz  add RTP cleanup, and URL support.
01a,26nov03,als  created.
*/

#ifndef __INCsnsLibPh
#define __INCsnsLibPh

/* includes */

#include "vxWorks.h"
#include "netdb.h"
#include "dsi/snsLib.h"
#include "sys/un.h"

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* socket address used by SNS server */

#define SNS_SERVER_PATH "/comp/socket/0x405"

/* 
 * alias for the largest possible socket address structure
 * (currently an AF_LOCAL-type socket address)
 */

#define sockaddr_max sockaddr_un

/* number of attempts connecting to the SNS server */

#define SNS_INIT_RETRY   12

/* retry internal in ticks */

#define SNS_INIT_TIMEOUT   10

/* wildcards characters */ 

#define SNS_WILDCARDS     "*?"

/* reserved characters not allowed as service name */

#define SNS_URL_RESERVES_FULL "*?@:#/<>%|[]{},\\ \'&;=+$"

/* SNS_URL_RESERVES minus wildcards characters */

#define SNS_URL_RESERVES_LESS_WILDCARD "@:#/<>%|[]{},\\ \'&;=+$"

/* define size of a service name plus text version of its scope */

#define SAL_SERV_NAME_SCOPE_MAXSIZE	\
    (SAL_SERV_NAME_MAXSIZE+sizeof(SNS_SCOPE_LONGEST_ENTRY_STR))

/* Distributed SAL entries */

#define DSAL_SNS_DEFAULT_TYPE     51        /* default SAL TIPC type */
#define DSAL_SNS_DEFAULT_INSTANCE 51        /* default SAL TIPC instance */
#define DSAL_VERSION		0           /* version of DSAL, part of CMD */
#define DSAL_REMOTE_NODE_ID	((long)(-2)) /* indicate remote owner */
#define DSAL_INVALID_SOCKFD	(-1)        /* sock fd that is not active */
#define DSAL_NAMES_MSG_SIZE_MAX	1000        /* maximum msg payload size */

/* typedefs */

typedef struct                              /* distributed SAL message */
    {
    UINT32  cmd;                    /* DSAL Command */
    char    bytes[1];		    /* empty */
    } DSAL_BASE_MSG;

/*
 * The contents of the DSAL_ADD_MSG are placed inside the DSAL_GENERIC_NAME_MSG
 * and this structure is not used directly.
 */
typedef struct                              /* dSAL add one name message */
    {
    UINT32  cmd;                            /* DSAL Command */
    UINT32  ai_flags;	                    /* AI_PASSIVE, AI_CANONNAME, ... */
    UINT32  ai_family;	                    /* AF_xxx */
    UINT32  ai_socktype;                    /* SOCK_xxx */
    UINT32  ai_protocol;                    /* sockProtocol */
    UINT32  scope;		            /* service scope */
    /* the following indented fields are fairly TIPC specific
     * - other protocols may modify these and the receiver would have
     * to base processing on the ai_family field above. */
    /* probably best to make the following a union when other protocols added */
      UINT32 ai_id_ref;	                    /* TIPC port ID reference */
      UINT32 ai_id_node;		    /* TIPC port ID node */
    /* the name field was added to the end of this message so that the
     * null terminator can be the terminator of the record.  A subsequent
     * record could then be appended directly starting with the first
     * field after 'cmd'. */
    char    name[SAL_SERV_NAME_SCOPE_MAXSIZE]; /* service name (4 byte padded)*/
    } DSAL_ADD_MSG;

/*
 * The structure of a message that is sent across the network. set up to
 * be aligned to an integer.  The structure is that of DSAL_ADD_MSG but
 * potentially with the record (less the cmd field) portion repeated for
 * each name to add.
 */
typedef struct                              /* dSAL add name(s) message */
    {
    UINT32  spaceholder[DSAL_NAMES_MSG_SIZE_MAX/sizeof(UINT32) + 1];
    } DSAL_GENERIC_NAME_MSG;

/*
 * The sns_remove_msg structure is not used directly, but the removal message
 * sent across the network uses the fields in this order and meaning when
 * constructing and destructing the message.
 */
typedef struct                              /* dSAL remove name message */
    {
    UINT32  cmd;                            /* DSAL Command */
    UINT32  scope;                          /* service scope of the entry */
    /* the following is fairly TIPC specific - other protocols may modify
     * and the receiver will have to base everything on the ai_family above. */
    /* probably best to make the following a union when other protocols added */
    UINT32  ai_id_ref;			    /* TIPC port ID reference */
    UINT32  ai_id_node;			    /* TIPC port ID node */
    /* note that all fields above are 32-bit aligned if required */
    char    name[SAL_SERV_NAME_MAXSIZE];    /* service name (4 byte padded) */
    } DSAL_REMOVE_MSG;

typedef struct                              /* dSAL SNS server change message */
    {
    UINT32  cmd;                            /* DSAL Command */
    UINT32  nodeId;                         /* node number of SNS server */
    UINT32  ref;                            /* socket ref  of SNS server */
    } DSAL_SNS_MSG;

typedef struct                              /* dSAL Get Names message */
    {
    UINT32  cmd;                            /* DSAL Command */
    } DSAL_SNS_GET_NAMES_MSG;

typedef struct serv_sock                    /* service socked info */
    {
    struct addrinfo sockInfo;               /* info for first/next socket */
    struct sockaddr_max sockAddr;           /* socket address */
    }  SNS_SERV_SOCK;

enum sns_cmd_value                          /* SNS message codes */
    {
    SNS_CMD_NOOP        = 0,
    SNS_CMD_REGISTER    = 1,                /* register a service */
    SNS_CMD_REGCONT     = 2,                /* continue the registeration */
    SNS_CMD_DEREGISTER  = 3,                /* deregister */
    SNS_CMD_REMOVE      = 4,                /* SNS entry remove by name */
    SNS_CMD_FINDSERV    = 5,                /* find a service */
    SNS_CMD_GETSOCK     = 6,                /* get a service sock info */
    SNS_CMD_NEXTSERV    = 7,                /* find the next service */
    SNS_CMD_CLEANUP     = 8,                /* cleanup services of dead RTP */
    SNS_CMD_MAX
    };

enum dsal_cmd_value			    /* DSAL message codes */
    {
    DSAL_CMD_SNS_WITHDRAWN	= 20,	    /* specified node has disappeared */
    DSAL_CMD_SNS_PUBLISHED	= 21,	    /* specified node has appeared */
    DSAL_CMD_GET_NAMES		= 22,	    /* request full database */
    DSAL_CMD_ADD_NAMES		= 23,	    /* specified names are available */
    DSAL_CMD_REMOVE_NAMES	= 24,	    /* specified names are removed */
    DSAL_CMD_SNS_NETWORK	= 25,       /* our node now in network mode */
    DSAL_CMD_MAX
    };

    /* SERVICE REGISTRATION MESSAGE STRUCTURES */

typedef struct sns_register_msg             /* service registration message */
    {
    uint8_t cmd;                            /* SNS_CMD_REGISTER */
    long rtpId;                           /* RTP making request */
    int  scope;                             /* scope (NONE forces decode) */
    char name[SAL_SERV_NAME_SCOPE_MAXSIZE]; /* service name or pattern */
    struct addrinfo sockInfo;               /* first socket to register */
    struct sockaddr_max sockAddr;           /* socket address */
    BOOL done;                              /* TRUE if no more to register */
    } SNS_REGISTER_MSG;

typedef struct sns_register_reply           /* service registration reply */
    {
    snsServDesc service;                    /* service descriptor */
    int regErrno;                           /* registration result */
    } SNS_REGISTER_REPLY_MSG;

    /* CONTINUE SERVICE REGISTRATION MESSAGE STRUCTURES */

typedef struct sns_regcont_msg              /* continue registration message */
    {
    uint8_t cmd;                            /* SNS_CMD_REGCONT */
    long rtpId;                           /* RTP making request */
    snsServDesc service;                    /* service descriptor */
    struct addrinfo sockInfo;               /* next socket to register */
    struct sockaddr_max sockAddr;           /* socket address */
    BOOL done;                              /* TRUE if no more to register */
    } SNS_REGCONT_MSG;
    
    /* note: uses the same reply as a service registration msg */

    /* SERVICE DEREGISTRATION MESSAGE STRUCTURES */
    
typedef struct sns_deregister_msg           /* service deregistration message */
    {
    uint8_t cmd;                            /* SNS_CMD_DEREGISTER */
    long rtpId;                           /* RTP making request */
    snsServDesc service;                    /* service descriptor */
    } SNS_DEREGISTER_MSG;

typedef struct sns_deregister_reply         /* service deregistration reply */
    {
    int deregErrno;                         /* deregistration result */
    } SNS_DEREGISTER_REPLY_MSG;

    /* SERVICE REMOVAL BY NAME MESSAGE STRUCTURES */

typedef struct sns_remove_msg               /* service remove message */
    {
    uint8_t cmd;                            /* SNS_CMD_REMOVE */
    long  rtpId;                          /* RTP making the request */
    int     scope;                          /* service scope of entry */
    char name[SAL_SERV_NAME_SCOPE_MAXSIZE]; /* service name or pattern */
    } SNS_REMOVE_MSG;

typedef struct sns_remove_reply             /* service remove reply */
    {
    int removeErrno;                        /* deregistration result */
    } SNS_REMOVE_REPLY_MSG;

    /* FIND SERVICE MESSAGE STRUCTURES */

typedef struct sns_findserv_msg             /* find service message */
    {
    uint8_t cmd;                            /* SNS_CMD_FINDSERV */
    BOOL    findSocket;                     /* TRUE for salSocketFind req */
                                            /* FALSE for salNameFind req */
    snsServDesc service;                    /* last matching addr */
    long  rtpId;                          /* RTP making request */
    char name[SAL_SERV_NAME_SCOPE_MAXSIZE]; /* service name or pattern */
    } SNS_FINDSERV_MSG;

    /* note: uses the same reply as a get socket info message */

    /* GET SOCKET INFO MESSAGE STRUCTURES */

typedef struct sns_getsock_msg              /* get socket info message */
    {
    uint8_t cmd;                            /* SNS_CMD_GETSOCK */
    long rtpId;                           /* RTP making request */
    snsServDesc service;                    /* service descriptor */
    int numSockets;                         /* # sockets already gotten */ 
    } SNS_GETSOCK_MSG;

    /* reply to sns_findserv_msg or sns_getsock_msg */

typedef struct sns_get_namesock_reply       /* get name or socket reply */
    {
    snsServDesc service;                    /* service descriptor */
    int getSockErrno;                       /* error # (if invalid service) */
    BOOL done;                              /* TRUE if no more info to get */
    union {                                 /* server socket or name info */
      SNS_SERV_SOCK  servSocketinfo;        /* server socket info */
      char name[SAL_SERV_NAME_SCOPE_MAXSIZE]; /* service name or pattern */
      } serNameSockInfo;                    /* server socket or name info */
#define serName     serNameSockInfo.name
#define servSockInfo serNameSockInfo.servSocketinfo.sockInfo
#define servSockAddr serNameSockInfo.servSocketinfo.sockAddr
    } SNS_GET_NAMESOCK_REPLY_MSG;

    /* GET NEXT SERVICE MESSAGE STRUCTURES */

typedef struct sns_nextserv_msg             /* get next service message */
    {
    uint8_t cmd;                            /* SNS_CMD_NEXTSERV */
    snsServDesc service;                    /* last known service */
    } SNS_NEXTSERV_MSG;

typedef struct sns_nextserv_reply                   /* get next service reply */
    {
    snsServDesc service;                    /* service descriptor */
    int nextServErrno;                      /* error # (if invalid service) */
    BOOL servAvail;                         /* service completely registered */
    long servOwner;                       /* RTP that registered service */
    int servScope;                          /* service scope */
    char servName[SAL_SERV_NAME_SCOPE_MAXSIZE]; /* service name or pattern */
    } SNS_NEXTSERV_REPLY_MSG;

    /* RTP SERVICE CLEANUP MESSAGE STRUCTURES */

typedef struct sns_serv_cleanup
    {
    uint8_t cmd;                         /* SNS_CMD_CLEANUP */
    long  rtpId;                       /* rtp being deleted */
    } SNS_SERV_CLEANUP_MSG;

    /* GENERIC MESSAGE STRUCTURES */

union sns_msg                     /* summary of all SNS protocol messages */
    {
    SNS_REGISTER_MSG            reg_msg;
    SNS_REGISTER_REPLY_MSG      regreply_msg;
    SNS_REGCONT_MSG             regcont_msg;
    SNS_DEREGISTER_MSG          dereg_msg;
    SNS_DEREGISTER_REPLY_MSG    deregreply_msg;
    SNS_REMOVE_MSG              remove_msg;
    SNS_REMOVE_REPLY_MSG        remreply_msg;
    SNS_FINDSERV_MSG            findserv_msg;
    SNS_GETSOCK_MSG             getsock_msg;
    SNS_GET_NAMESOCK_REPLY_MSG  getnmsockreply_msg;
    SNS_NEXTSERV_MSG            nextserv_msg;
    SNS_NEXTSERV_REPLY_MSG      nextservreply_msg;
    SNS_SERV_CLEANUP_MSG        servcleanup_msg;
    };

/* size of largest message used by SNS */

#define SNS_MSG_MAXSIZE sizeof (union sns_msg)

struct sns_dsal_msg
    {
    union		 /* summary of all Distributed SAL messages */
	{
	DSAL_BASE_MSG		base_msg;
	DSAL_SNS_MSG		node_msg;
	DSAL_SNS_GET_NAMES_MSG	get_msg;
	DSAL_ADD_MSG		add_msg;
	DSAL_REMOVE_MSG		remove_msg;
	} dsal;
    };

/* size of largest message used by Distributed SAL */

#define DSAL_MSG_MAXSIZE sizeof (struct sns_dsal_msg)

struct sns_max_msg                          /* largest possible SNS message */
    {
    uint8_t cmd;                            /* command byte */
    char dummy[SNS_MSG_MAXSIZE-1];          /* space for rest of message */
    };

struct sns_scope_info                       /* scope information structure */
    {
    int    value;                           /* numeric form of scope */
    char * exactScope;                      /* exact scope */
    char * uptoScope;                       /* text form of exact scope */
    char * displayScope;		    /* displayed text for snsShow */
    };

/* function declarations */
    
void snsfreeaddrinfo (struct addrinfo * ai );

extern int snsPatMatch (const char * pat, const char * str);

/* externs */

/* table used in converting text form of scope to numeric form */

extern const struct sns_scope_info snsScopeTbl[];

#ifdef __cplusplus
}
#endif

#endif /* __INCsnsLibPh */
