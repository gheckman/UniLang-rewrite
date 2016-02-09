/*
 * tipc.h: Include file for TIPC interface
 * 
 * Copyright (c) 2003-2006, Ericsson AB
 * Copyright (c) 2004-2010, Wind River Systems
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * ------------------------------------------------------------------------
 * modification history
 * --------------------
 * 02a,09dec10,h_x  Fix warnings
 * 01z,16jul10,h_x  Fix WIND00220144
 * 01y,11may10,h_x  Port the patches to VxWorks from Linux TIPC 1.7.7
 * 01x,28apr10,pad  Moved extern C statement after include statements.
 * 01w,18sep09,h_x  Fix WIND00156921 and WIND00172937
 * 01v,20jan09,h_w  add TIPC_SMP_SUPPORT and TIPC_WV_SUPPORT definitions
 * 01u,08oct08,als  Update to TIPC 1.7.6 (Defect WIND00127984)
 * 01t,30mar07,mze  post SMP review changes 
 * 01s,21feb07,ggz  moving spinLock_t and some other declarations into tipc_locklib.h 
 * 01r,20jun06,mze  code review changes for TIPC portability 
 * 01q,14jun06,ggz  added AF_TIPC support in vxWorks6.0 for TIPC portability 
 * 01p,13mar06,ebh  change family field type in sockaddr_tipc to unsigned char
 * 01o,15feb06,bwa  remove unused fields in media descriptor as per code review
 * 01n,06feb06,bwa  'media start' routine now returns success/error code.
 * 01m,19jan06,mze  added TASK defines
 * 01l,16jan06,als  updated to Linux TIPC 1.5.9-equivalence
 * 01k,15nov05,ebh  Port of SF TIPC 1.6 code base
 * 01j,12may05,als  update AF_TIPC to avoid conflict with AF_ATM
 * 01i,08apr05,als  consolidate copyright info; fix compiler inlining warnings 
 * 01h,08feb05,bwa  added shared memory address type.
 * 01g,15dec04,als  add support for poll()-like events
 * 01f,25oct04,als  fix comment
 * 01e,05oct04,als  Fix misleading comment
 * 01d,14sep04,als  name table display enhancements
 * 01c,03sep04,als  incorporated code inspection feedback
 * 01b,07aug04,p_r  code update
 * 01a,30jun04,als  Ported to VxWorks
 *
 */

#ifndef _VXWORKS_TIPC_H_
#define _VXWORKS_TIPC_H_

#include <vxWorks.h>
#include <sys/socket.h>

#ifdef __cplusplus
extern "C" {
#endif 


/* Scalar data types used by TIPC */

typedef	unsigned char  	u8,  __u8, unchar;
typedef	char		s8,  __s8;
typedef	unsigned short	u16, __u16, __be16;
typedef	short		s16, __s16;
typedef	unsigned int    u32, __u32, __be32, uint;
typedef	int		s32, __s32;

/*
 * COMPILER-RELATED APIS REQUIRED BY TIPC COMMON FILES
 */
 
/* Define alternative form of "inline" keyword used by compiler */

#define inline  __inline__

/* Define alternative form of "typeof" keyword used by compiler */

#define typeof __typeof__

/* Compiler doesn't support branch prediction hints, so treat as a no-op */

#define likely(X)   (X)
#define unlikely(X) (X)

/*
 * Macros for number representation conversion.
 * (Can't get these by including netinet/in.h because it indirectly includes 
 * a .h file that contains a typedef for "struct node"; this typedef conflicts 
 * with the typedef for "struct node" defined by TIPC in tipc_node.h.)
 */

#if	_BYTE_ORDER==_BIG_ENDIAN

#ifndef ntohl
#define	ntohl(x)	(x)
#endif

#ifndef ntohs
#define	ntohs(x)	(x)
#endif

#ifndef htonl
#define	htonl(x)	(x)
#endif

#ifndef htons
#define	htons(x)	(x)
#endif

#endif	/* _BYTE_ORDER==_BIG_ENDIAN */

#if	_BYTE_ORDER==_LITTLE_ENDIAN

#ifndef ntohl
#define ntohl(x)	((((x) & 0x000000ff) << 24) | \
			 (((x) & 0x0000ff00) <<  8) | \
			 (((x) & 0x00ff0000) >>  8) | \
			 (((x) & 0xff000000) >> 24))
#endif

#ifndef htonl
#define htonl(x)	((((x) & 0x000000ff) << 24) | \
			 (((x) & 0x0000ff00) <<  8) | \
			 (((x) & 0x00ff0000) >>  8) | \
			 (((x) & 0xff000000) >> 24))
#endif

#ifndef ntohs
#define ntohs(x)	(__be16)((((x) & 0x00ff) << 8) | \
			 (((x) & 0xff00) >> 8))
#endif

#ifndef htons
#define htons(x)	(__be16)((((x) & 0x00ff) << 8) | \
			 (((x) & 0xff00) >> 8))
#endif

#endif	/* _BYTE_ORDER==_LITTLE_ENDIAN */

/*  declare existence of spinlock_t */

struct tipc_lock_item;
typedef struct tipc_lock_item *spinlock_t;

/*
 * TIPC addressing primitives
 *
 * (Uses macros rather than inline functions to avoid compiler warnings)
 */
 
struct tipc_portid {
	__u32 ref;
	__u32 node;
};

struct tipc_name {
	__u32 type;
	__u32 instance;
};

struct tipc_name_seq {
	__u32 type;
	__u32 lower;
	__u32 upper;
};

#define tipc_addr(Z,C,N) (((Z)<<24)|((C)<<12)|(N))
#define tipc_zone(A)     ((A)>> 24)
#define tipc_cluster(A)  (((A) >> 12) & 0xfff)
#define tipc_node(A)     ((A) & 0xfff)

/*
 * Task defines for handler.c and others that need to know the PRIORITY
 */

#define TIPC_TASK_PRIORITY  (52)
#define TIPC_TASK_OPTIONS   (0)
#define TIPC_TASK_STACKSIZE (5000)

/*
 * Application-accessible port name types
 */

#define TIPC_CFG_SRV		0	/* configuration service name type */
#define TIPC_TOP_SRV		1	/* topology service name type */
#define TIPC_RESERVED_TYPES	64	/* lowest user-publishable name type */

/* 
 * Publication scopes when binding port names and port name sequences
 */

#define TIPC_ZONE_SCOPE		1
#define TIPC_CLUSTER_SCOPE	2
#define TIPC_NODE_SCOPE		3
#define TIPC_NETWORK_SCOPE	4	/* NOT AVAILABLE YET */

/*
 * Limiting values for messages
 */

#define TIPC_MAX_USER_MSG_SIZE	66000

/*
 * Message importance levels
 */

#define TIPC_LOW_IMPORTANCE		0
#define TIPC_MEDIUM_IMPORTANCE		1
#define TIPC_HIGH_IMPORTANCE		2
#define TIPC_CRITICAL_IMPORTANCE	3

/* 
 * Msg rejection/connection shutdown reasons
 */

#define TIPC_OK			0
#define TIPC_ERR_NO_NAME	1
#define TIPC_ERR_NO_PORT	2
#define TIPC_ERR_NO_NODE	3
#define TIPC_ERR_OVERLOAD	4
#define TIPC_CONN_SHUTDOWN	5

/*
 * TIPC topology subscription service definitions
 */

#define TIPC_SUB_PORTS     	0x01  	/* filter for port availability */
#define TIPC_SUB_SERVICE     	0x02  	/* filter for service availability */
#define TIPC_SUB_CANCEL         0x04    /* cancel a subscription */

#define TIPC_WAIT_FOREVER   ((__u32)~0)	/* timeout for permanent subscription */

struct tipc_subscr {
	struct tipc_name_seq seq;	/* name sequence of interest */
	__u32 timeout;			/* subscription duration (in ms) */
        __u32 filter;   		/* bitmask of filter options */
	char usr_handle[8];		/* available for subscriber use */
};

#define TIPC_PUBLISHED		1	/* publication event */
#define TIPC_WITHDRAWN		2	/* withdraw event */
#define TIPC_SUBSCR_TIMEOUT	3	/* subscription timeout event */

struct tipc_event {
	__u32 event;			/* event type */
	__u32 found_lower;		/* matching name seq instances */
	__u32 found_upper;		/*    "      "    "     "      */
	struct tipc_portid port;	/* associated port */
	struct tipc_subscr s;		/* associated subscription */
};

/*
 * Socket API
 */

#ifndef AF_TIPC

#if ((_WRS_VXWORKS_MAJOR == 6) && (_WRS_VXWORKS_MINOR == 0))
#error 'vxWorks6.0 does not support AF_TIPC. Reserve any unused AF from the stack, check target/h/wrn/coreip/sys/socket.h and define it here.'
/* An example: AF_ATM is defined as 30. Use this value for AF_TIPC */
/* #define AF_TIPC 30 */
#else
#error  'AF_TIPC = 33 should have been defined in target/h/wrn/coreip/sys/socket.h' 
#endif

#endif	/* ifndef AF_TIPC */

#if (AF_TIPC > AF_MAX)
#error 'AF_TIPC incorrectly defined to be > AF_MAX in target/h/wrn/coreip/sys/socket.h'
#endif

#define TIPC_ADDR_NAMESEQ	1
#define TIPC_ADDR_MCAST		1
#define TIPC_ADDR_NAME		2
#define TIPC_ADDR_ID		3

struct sockaddr_tipc {
    unsigned char  addrlen;             /* 16 */
    unsigned char  family;              /* AF_TIPC */
    unsigned char  addrtype;            /* TIPC_ADDR_xxx */
    signed   char  scope;               /* used with bind */
    union {
        struct tipc_portid id;          /* if TIPC_ADDR_ID */
        struct tipc_name_seq nameseq;   /* if TIPC_ADDR_NAMESEQ/_MCAST */
        struct {                        /* if TIPC_ADDR_NAME */
        struct tipc_name name;
        __u32 domain;                   /* used w/ connect, sendto */
        } name;
    } addr;
};

/*
 * Ancillary data objects supported by recvmsg()
 */

#define TIPC_ERRINFO	1	/* error info */
#define TIPC_RETDATA	2	/* returned data */
#define TIPC_DESTNAME	3	/* destination name */

/*
 * TIPC-specific socket option values
 */

#define SOL_TIPC                 50     /* TIPC socket option level */
#define TIPC_IMPORTANCE		127	/* Default: TIPC_LOW_IMPORTANCE */
#define TIPC_SRC_DROPPABLE	128	/* Default: based on socket type */
#define TIPC_DEST_DROPPABLE	129	/* Default: based on socket type */
#define TIPC_CONN_TIMEOUT	130	/* Default: 8000 (ms) */
#define TIPC_NODE_RECVQ_DEPTH 131
#define TIPC_SOCK_RECVQ_DEPTH 132


/* 
 * Build interface: (WRS only)
 * ---------------
 */

struct tipc_media_descr {
    FUNCPTR     start;                  /* media initialization routine */
    VOIDFUNCPTR stop;                   /* media termination routine */
};

/*
 * Global configuration variables
 */

extern int tipc_max_nodes;
extern int tipc_max_clusters;
extern int tipc_max_zones;
extern int tipc_max_remotes;
extern int tipc_max_ports;
extern int tipc_max_subscriptions;
extern int tipc_max_publications;
extern int tipc_net_id;
extern int tipc_log_size;
extern int tipc_remote_management;

#ifdef __KERNEL__

/* 
 * Native API
 * ----------
 */

struct sk_buff;

/*
 * TIPC operating mode routines
 */

u32 tipc_get_addr(void);

#define TIPC_NOT_RUNNING  0
#define TIPC_NODE_MODE    1
#define TIPC_NET_MODE     2

typedef void (*tipc_mode_event)(void *usr_handle, int mode, u32 addr);

int tipc_attach(unsigned int *userref, tipc_mode_event, void *usr_handle);

void tipc_detach(unsigned int userref);

int tipc_get_mode(void);

/*
 * TIPC port manipulation routines
 */

typedef void (*tipc_msg_err_event) (void *usr_handle,
				    u32 portref,
				    struct sk_buff **buf,
				    unsigned char const *data,
				    unsigned int size,
				    int reason, 
				    struct tipc_portid const *attmpt_destid);

typedef void (*tipc_named_msg_err_event) (void *usr_handle,
					  u32 portref,
					  struct sk_buff **buf,
					  unsigned char const *data,
					  unsigned int size,
					  int reason, 
					  struct tipc_name_seq const *attmpt_dest);

typedef void (*tipc_conn_shutdown_event) (void *usr_handle,
					  u32 portref,
					  struct sk_buff **buf,
					  unsigned char const *data,
					  unsigned int size,
					  int reason);

typedef void (*tipc_msg_event) (void *usr_handle,
				u32 portref,
				struct sk_buff **buf,
				unsigned char const *data,
				unsigned int size,
				unsigned int importance, 
				struct tipc_portid const *origin);

typedef void (*tipc_named_msg_event) (void *usr_handle,
				      u32 portref,
				      struct sk_buff **buf,
				      unsigned char const *data,
				      unsigned int size,
				      unsigned int importance, 
				      struct tipc_portid const *orig,
				      struct tipc_name_seq const *dest);

typedef void (*tipc_conn_msg_event) (void *usr_handle,
				     u32 portref,
				     struct sk_buff **buf,
				     unsigned char const *data,
				     unsigned int size);

typedef void (*tipc_continue_event) (void *usr_handle, 
				     u32 portref);

int tipc_createport(unsigned int tipc_user, 
		    void *usr_handle, 
		    unsigned int importance, 
		    tipc_msg_err_event error_cb, 
		    tipc_named_msg_err_event named_error_cb, 
		    tipc_conn_shutdown_event conn_error_cb, 
		    tipc_msg_event message_cb, 
		    tipc_named_msg_event named_message_cb, 
		    tipc_conn_msg_event conn_message_cb, 
		    tipc_continue_event continue_event_cb,
		    u32 *portref);

int tipc_deleteport(u32 portref);

int tipc_ownidentity(u32 portref, struct tipc_portid *port);

int tipc_portimportance(u32 portref, unsigned int *importance);
int tipc_set_portimportance(u32 portref, unsigned int importance);

int tipc_portunreliable(u32 portref, unsigned int *isunreliable);
int tipc_set_portunreliable(u32 portref, unsigned int isunreliable);

int tipc_portunreturnable(u32 portref, unsigned int *isunreturnable);
int tipc_set_portunreturnable(u32 portref, unsigned int isunreturnable);

int tipc_publish(u32 portref, unsigned int scope, 
		 struct tipc_name_seq const *name_seq);
int tipc_withdraw(u32 portref, unsigned int scope,
		  struct tipc_name_seq const *name_seq);

int tipc_connect2port(u32 portref, struct tipc_portid const *port);

int tipc_disconnect(u32 portref);

int tipc_shutdown(u32 ref);

int tipc_isconnected(u32 portref, int *isconnected);

int tipc_peer(u32 portref, struct tipc_portid *peer);

int tipc_ref_valid(u32 portref); 

/*
 * TIPC messaging routines
 */

#define TIPC_PORT_IMPORTANCE 100        /* send using current port setting */

int tipc_send(u32 portref,
	      unsigned int num_sect,
	      struct iovec const *msg_sect);

int tipc_send_buf(u32 portref,
		  struct sk_buff *buf,
		  unsigned int dsz);

int tipc_send2name(u32 portref, 
		   struct tipc_name const *name, 
		   u32 domain,
		   unsigned int num_sect,
		   struct iovec const *msg_sect);

int tipc_send_buf2name(u32 portref,
		       struct tipc_name const *name,
		       u32 domain,
		       struct sk_buff *buf,
		       unsigned int dsz);

int tipc_forward2name(u32 portref, 
		      struct tipc_name const *name, 
		      u32 domain,
		      unsigned int section_count,
		      struct iovec const *msg_sect,
		      struct tipc_portid const *origin,
		      unsigned int importance);

int tipc_forward_buf2name(u32 portref,
			  struct tipc_name const *name,
			  u32 domain,
			  struct sk_buff *buf,
			  unsigned int dsz,
			  struct tipc_portid const *orig,
			  unsigned int importance);

int tipc_send2port(u32 portref,
		   struct tipc_portid const *dest,
		   unsigned int num_sect,
		   struct iovec const *msg_sect);

int tipc_send_buf2port(u32 portref,
		       struct tipc_portid const *dest,
		       struct sk_buff *buf,
		       unsigned int dsz);

int tipc_forward2port(u32 portref,
		      struct tipc_portid const *dest,
		      unsigned int num_sect,
		      struct iovec const *msg_sect,
		      struct tipc_portid const *origin,
		      unsigned int importance);

int tipc_forward_buf2port(u32 portref,
			  struct tipc_portid const *dest,
			  struct sk_buff *buf,
			  unsigned int dsz,
			  struct tipc_portid const *orig,
			  unsigned int importance);

int tipc_multicast(u32 portref, 
		   struct tipc_name_seq const *seq, 
		   u32 domain,   /* currently unused */
		   unsigned int section_count,
		   struct iovec const *msg);

/*
 * TIPC subscription routines
 */

int tipc_ispublished(struct tipc_name const *name);

/*
 * Get number of available nodes within specified domain (excluding own node)
 */

unsigned int tipc_available_nodes(const u32 domain);

#endif	/* KERNEL */

#ifdef __cplusplus
}
#endif

#endif	/* __NET_TIPC_H_ */
