/* mipc_os_adapt.h - MIPC OS adaptation header file for VxWorks */

/*
 * Copyright (c) 2008-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01w,08sep10,h_w  Add definition of MIPC_MSG_TRUNC
01v,26aug10,jlk  Make sure #ifdef __cplusplus starts after #includes
01u,02jun10,als  Remove code for deprecated MIPC 1.0 APIs
01t,04mar10,als  Add support for 64-bit memory addressing
01s,10feb10,h_w  Update after code inspection 
01r,10jan10,h_w  Add AF_MIPC support
01q,29oct09,als  Fix minor API issues (WIND00186193)
01p,18aug09,jlk  WIND00177194 - Remove deferred semaphore code.
01o,28jul09,als  Add/revise APIs to reflect feedback from HLD review
01n,26jun09,h_w  Add MIPC_64bit data type definition
01m,22jun09,ebh  Add -MIPC_EFAULT to the error codes
01l,17jun09,als  Enhance error path code during initialization
01k,03jun09,als  Rework system configuration/initialization as per HLD and CI
01j,28may09,als  Revise configuration based on MIPC 2.0 HLD feedback
01i,22apr09,ebh  Add in MIPC_EPROTONOSUPPORT
01h,27mar09,ebh  Add in MIPC_ENOENT error code
01g,11mar09,ebh  Add in MIPC_EPIPE as an error code
01f,12jan09,ebh  Update for MIPC 2.0
01e,16oct08,apa  Removed definitions conflicting with TIPC.
01d,18sep08,apa  Changes and fixes following code review.
01c,19aug08,apa  Added MIPC_MSG_USER
01b,30mar08,bwa  added description.
01a,07feb08,bwa  written.
*/

/*
DESCRIPTION

MIPC OS adaptation. The definitions in this file allow MIPC to run on any
OS without major changes to the MIPC code, other than adjustments in this
file and the Multios adaptation file.
*/

#ifndef __INCmipc_os_adapth
#define __INCmipc_os_adapth

#include <vxWorks.h>
#include <tickLib.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <../usr/h/multios_ipc/mipc.h>

#ifdef __cplusplus
extern "C" {
#endif

#define inline __inline__

#define __stringify_1(x)        #x
#define __stringify(x)          __stringify_1(x)
 
/* MIPC socket family support */
#define MIPC_AF			AF_MIPC

/* Support MIPC socket types */
#define MIPC_SOCK_STREAM	1
#define MIPC_SOCK_DGRAM		2
#define MIPC_SOCK_RDM		4
#define MIPC_SOCK_SEQPACKET	5

/* log2 of MIPC socket structure size (rounded up to an integer value) */
#ifndef _WRS_CONFIG_LP64
	#define MIPC_SD_BITS 9
#else
	#define MIPC_SD_BITS 10
#endif /* _WRS_CONFIG_LP64 */

/* MIPC error codes */
#define MIPC_OK			0
#define MIPC_ENOENT		ENOENT		/* no such file or directory */
#define MIPC_EBADF		EBADF  		/* bad socket number */
#define MIPC_EAGAIN		EAGAIN 		/* try again */
#define MIPC_ENOMEM		ENOMEM		/* out of memory */
#define MIPC_EFAULT		EFAULT		/* bad address */
#define MIPC_EINVAL		EINVAL 		/* invalid argument */
#define MIPC_ENFILE		ENFILE		/* socket table overflow */
#define MIPC_EWOULDBLOCK 	EWOULDBLOCK	/* operation would block */
#define MIPC_ENOMSG		ENOMSG		/* no message of desired type */
#define MIPC_EMSGSIZE		EMSGSIZE	/* message too long */
#define MIPC_EPIPE		EPIPE		/* broken pipe */
#define MIPC_EPROTOTYPE		EPROTOTYPE	/* protocol wrong type for socket */
#define MIPC_EAFNOSUPPORT	EAFNOSUPPORT	/* addr family not supported */
#define MIPC_EOPNOTSUPP		EOPNOTSUPP	/* operation not supported */
#define MIPC_EADDRINUSE		EADDRINUSE	/* address already in use */
#define MIPC_EADDRNOTAVAIL	EADDRNOTAVAIL	/* cannot assign requested address */
#define MIPC_ENETUNREACH	ENETUNREACH	/* network is unreachable */
#define MIPC_ECONNABORTED	ECONNABORTED	/* software caused connection abort */
#define MIPC_ECONNRESET		ECONNRESET	/* connection reset by peer */
#define MIPC_ENOBUFS		ENOBUFS		/* no buffer space available */
#define MIPC_EISCONN		EISCONN		/* socket is already connected */
#define MIPC_ENOTCONN		ENOTCONN	/* socket is not connected */
#define MIPC_ESHUTDOWN		ESHUTDOWN	/* cannot send after socket shutdown */
#define MIPC_ETIMEDOUT		ETIMEDOUT	/* operation timed out */
#define MIPC_ECONNREFUSED	ECONNREFUSED	/* connection refused */
#define MIPC_EALREADY		EALREADY	/* operation already in progress */
#define MIPC_EINPROGRESS	EINPROGRESS	/* operation now in progress */
#define MIPC_EINTR		EINTR		/* interrupted */
#define MIPC_ENOPROTOOPT 	ENOPROTOOPT 	/* protocol option not available */
#define MIPC_EDESTADDRREQ	EDESTADDRREQ	/* destination address required */
#define MIPC_ENODEV		ENODEV    	/* no such device */
#define MIPC_EOVERFLOW		EOVERFLOW	/* value too large for data type */

/* To be used with mipc_shutdown() */
#define MIPC_SHUT_RDWR		SHUT_RDWR

/* To be used with the receive functions */
#define MIPC_MSG_DONTWAIT	MSG_DONTWAIT
#define MIPC_MSG_WAITALL	MSG_WAITALL
#define MIPC_MSG_PEEK		MSG_PEEK
#define MIPC_MSG_USER		MSG_COMPAT
#define MIPC_MSG_TRUNC		MSG_TRUNC

/* MIPC output definitions */
#define MIPC_CONS_HDR		"MIPC: "
#define MIPC_INFO		MIPC_CONS_HDR "<info> "
#define MIPC_ALERT		MIPC_CONS_HDR "<alert> "

#define MIPC_PRINT		printf


/* Prototypes associated with ISR handler */

typedef void (*MIPC_ISR_FUNC) (void *arg);

extern int mipc_sm_isr_set(uint16_t intId, MIPC_ISR_FUNC func, void *arg);

#ifdef __cplusplus
}
#endif

#endif /* __INCmipc_os_adapth */

