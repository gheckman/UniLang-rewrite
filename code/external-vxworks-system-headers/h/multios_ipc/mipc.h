/* mipc.h - Library for multi-OS IPC */

/********************************************************************
The following file is dual licensed and is available under either 
the GPL version 2 or a Wind River commercial license.

*********************************************************************
Copyright (c) 2008-2011 Wind River Systems, Inc.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License version 2 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

*********************************************************************
Copyright (c) 2008-2011 Wind River Systems, Inc.

The right to copy, distribute, modify, or otherwise make use
of this software may be licensed pursuant to the terms
of an applicable Wind River license agreement.

*********************************************************************/

/*
modification history
--------------------
02m,07jan11,jlk  Update license header and update version to 2.2
02l,24sep10,jlk  Add support for setting and getting debug mode
02k,03jun10,als  Ensure address argument to mipc_bind() is not altered
02j,02jun10,als  Remove code for deprecated MIPC 1.0 APIs
02i,02mar10,als  Add support for 64-bit memory addressing
02h,29oct09,als  Fix minor API issues (WIND00186193)
02g,15sep09,als  Adjust MIPC_SD_BITS to account for smaller socket structure
02f,09sep09,als  Correct minor statistics collection issues
02e,19aug09,h_x  Fix for WIND00176194
02d,19aug09,als  Correct port number usage definitions
02c,11aug09,ebh  Add in suggested port number for applications to start using
02b,07aug09,als  Make socket descriptors simple positive integers
02a,04aug09,als  Convert shared memory offsets to use MIPC_OFFSET type
01z,29jul09,als  Add support for per-bus statistics collection
01y,28jul09,als  Add/revise APIs to reflect feedback from HLD review
01x,03jul09,als  Remove socket option default symbols
01w,30jun09,als  Make express callback arg types consistent with rx callback
01v,26jun09,h_w  Rename express data messaging send routine 'mipc_send_express'
                 to 'mipc_sendexpress64'
01u,17jun09,ebh  Add MIPC_SD_BITS definition
01t,13jun09,ebh  Add mipc_zallocbuf for fast buffer allocations
01s,09jun09,als  Rework system configuration/initialization as per HLD and CI
01r,03jun09,ebh  Add support for a callback on a listening socket for incoming
                 connect request
01q,25may09,ebh  Remove the MIPC_BROADCAST macro that is obsolete
01p,13may09,ebh  Turn on CHECK_ARGS and KEEP_STATS
01o,01may09,ebh  Update the getuserhandle and setuserhandle macros
01n,29apr09,ebh  Remove unused macro MIPC_SO_USER_DATA
01m,28apr09,ebh  Modify the API for mipc_setuserhandle() and
                 mipc_getuserhandle()
01l,24apr09,ebh  Restore MIPC_BROADCAST temporarily
01k,21apr09,ebh  Add in macros for ANY parameter specification for mipc_bind
01j,20apr09,ebh  Add mipc_getbusmaxnodes API
01i,25mar09,ebh  Add in define for MIPC_BUFFER_STARVATION_PREVENTION
01h,20mar09,ebh  Fix Default TIMEOUTS to include WAIT_FOREVER values
01g,11mar09,ebh  Add in a macro for wait forever on a receive
01f,15dec08,apa  Added MIPC 2.0 changes.
01e,27nov08,ebh  Turn off default API parameter checks MIPC_CHECK_ARGS
01d,24nov08,ebh  Add in versioning macros
01c,15sep08,apa  Changes and fixes following code review.
01b,11aug08,apa  Changes to sync up with latest MIPC HLD.
01a,11jun08,apa  Initial version.
*/

#ifndef __INCmipch
#define __INCmipch

#include "multios_adapt.h"
#include "mipc_os_adapt.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------
 *                              Version Macros
 *---------------------------------------------------------------------------
 */

#define MIPC_VERSION_MAJOR	2	/* major version of MIPC */
#define MIPC_VERSION_MINOR	2	/* minor version of MIPC */

/*---------------------------------------------------------------------------
 *                           API - Constants and Types
 *---------------------------------------------------------------------------
 */

/* Socket option level */
#define MIPC_SOL 				0

/* Socket options [used with mipc_getsockopt() and mipc_setsockopt()] */
#define MIPC_SO_TXBUFS				0
#define MIPC_SO_MTU				1
#define MIPC_SO_RX_CALLBACK			2
#define MIPC_SO_NODEJOIN_CALLBACK		3
#define MIPC_SO_NODELEFT_CALLBACK		4
#define MIPC_SO_TXBUFAVAIL_CALLBACK		5
#define MIPC_SO_NBIO				6
/* for  MIPC_SO_TXBUFAVAIL_THRESHOLD		7	now unsupported */
#define MIPC_SO_CONN_TIMEOUT 			8
#define MIPC_SO_SEND_TIMEOUT			9
#define MIPC_SO_CONNECTED_CALLBACK		10
#define MIPC_SO_CONNECTREFUSED_CALLBACK		11
#define MIPC_SO_DISCONNECTED_CALLBACK		12
#define MIPC_SO_RECEIVE_TIMEOUT			13
#define MIPC_SO_RXBUFS				14
/* for  MIPC_SO_SHUTDOWN_TIMEOUT		15	now unsupported */
#define MIPC_SO_EXPRESS_CALLBACK		16
/* for  MIPC_SO_EVENTQUEUE_SIZE			17	now unsupported */
#define MIPC_SO_RXQUEUED_CALLBACK		18
#define MIPC_SO_CONNECTREQUEST_CALLBACK		19

/* Socket and timing option */
#define MIPC_TIMEOUT_FOREVER			(-1)

/* Return values of MIPC_RX_CALLBACK */
#define MIPC_RX_RELEASEBUF			0
#define MIPC_RX_QUEUEBUF			1
#define MIPC_RX_KEEPBUF				2

/* Addressing values for mipc_bind calls */
#define MIPC_BUS_ANY				((uint16_t)(~0))
#define MIPC_NODE_ANY				((uint16_t)(~0))
#define MIPC_PORT_ANY				((uint16_t)(~0))

/* MIPC port number allocations */
#define MIPC_SYS_PORT_BASE	0	/* lowest reserved port number */
#define MIPC_OPEN_PORT_BASE	3	/* lowest unreseved port number */

/* MIPC socket address structure */
struct mipc_sockaddr
{
	unsigned short family;		/* family number (MIPC_AF) */
	unsigned short busNum;		/* bus number */
	unsigned short nodeNum;		/* node number */
	unsigned short portNum;		/* port number */
};

/* MIPC statistics structure (one per active bus) */
struct mipc_stats {
	uint32_t bufs_sent;		/* # buffers sent */
	uint32_t bufs_rcvd;		/* # buffers received */
	uint32_t bytes_sent;		/* # buffer bytes sent */
	uint32_t bytes_rcvd;		/* # buffer bytes received */
	uint32_t bufs_allocated;	/* # buffers allocated */
	uint32_t bufs_freed;		/* # buffers freed */
	uint32_t buf_cong_wait;		/* buffer congestion (blocking) */
	uint32_t buf_cong_no_wait;	/* buffer congestion (non-blocking) */
	uint32_t buf_avail_sent;	/* buffer available events sent */
	uint32_t buf_avail_rcvd;	/* buffer available events received */
	uint32_t express_msgs_sent;	/* express messages sent */
	uint32_t express_msgs_rcvd;	/* express messages received */
	uint32_t buffer_not_avail;	/* couldn't get buffer from packet pool */
	uint32_t event_not_avail;      	/* couldn't get event from event pool */
	uint32_t interrupts_sent;	/* # interrupts sent */
	uint32_t interrupts_rcvd;	/* # interrupts received */
	uint32_t interrupts_deferred;	/* # invocations of deferred work thead */
	uint32_t sockets_bound;		/* # sockets bound to bus */
	uint32_t sockets_closed;	/* # sockets closed after binding to bus */
	uint32_t socket_rx_queue_err;	/* # socket rx queue errors (full q) */
};

/* Node-independent memory offset [opaque type; definition subject to change] */
typedef uint32_t MIPC_OFFSET;

/* Zero-copy buffer handle [opaque type; definition subject to change] */
typedef void *MIPC_ZBUFFER;

/* Called when an incoming buffer has been received */
typedef int (*MIPC_RX_CALLBACK) (int sd, 
				 const unsigned char *buff, 
				 size_t nbytes, 
				 unsigned short srcNodeNum,
				 unsigned short srcPortNum,
				 MIPC_ZBUFFER zbuf);

/* Called when an incoming buffer has been queued */
typedef int (*MIPC_RXQUEUED_CALLBACK) (int sd);

/* Called when a node has joined the bus */
typedef void (*MIPC_NODEJOIN_CALLBACK) (int sd, unsigned short nodeNum);

/* Called when a node has left the bus */
typedef void (*MIPC_NODELEFT_CALLBACK) (int sd, unsigned short nodeNum);

/* Called when there are transmission buffers available */
typedef void (*MIPC_TXBUFAVAIL_CALLBACK) (int sd);

/* Called when a connection is established on a socket */
typedef void (*MIPC_CONNECTED_CALLBACK) (int sd);

/* Called when a connection is refused on a socket */
typedef void (*MIPC_CONNECTREFUSED_CALLBACK) (int sd);

/* Called when a socket become disconnected */
typedef void (*MIPC_DISCONNECTED_CALLBACK) (int sd);

/* Called when a connect request is received on a listening socket */
typedef void (*MIPC_CONNECTREQUEST_CALLBACK) (int sd);

/* Called when 64-bit express data is received */
typedef void (*MIPC_EXPRESS_CALLBACK) (int sd, unsigned short srcNode,
				       unsigned short srcPort, uint64_t data);

/*---------------------------------------------------------------------------
 *                            API - Functions
 *---------------------------------------------------------------------------
 */

/* Accept a connection on a MIPC socket */
int mipc_accept(int sd, struct mipc_sockaddr *addr, socklen_t *addrlen);

/* Convert a local pointer address to a node-independent offset */
static MULTIOS_INLINE MIPC_OFFSET mipc_addr2offset(void *address);

/* Bind an address to a MIPC socket */
int mipc_bind(int sd, const struct mipc_sockaddr *myaddr, socklen_t addrlen);

/* Clear MIPC statistics for a bus */
int mipc_clearstatsbybus(int busnum);

/* Close a MIPC socket */
int mipc_close(int sd);

/* Request a connection to a MIPC socket */
int mipc_connect(int sd, const struct mipc_sockaddr *servaddr,
		 socklen_t addrlen);

/* Get bitfield of the buses this node can utilize */
int mipc_getactivebusesl(unsigned char *buses, size_t buseslen);

/* Get bitfield of the active nodes on a bus */
int mipc_getactivenodes(int bus, unsigned long long *nodes);

/* Get bitfield of the active nodes on a bus */
int mipc_getactivenodesl(int bus, unsigned char *nodes, size_t nodeslen);

/* Get the number of a bus given its name */
int mipc_getbusbyname(const char *name, int *busnum);

/* Get the number of nodes present on a bus */
int mipc_getbusmaxnodes(int busnum);

/* Get the name of a bus given its number */
int mipc_getnamebybus(int busnum, char *name, size_t namelen);

/* Get the node number of this node on a bus */
int mipc_getnodebybus(int busnum);

/* Get the address of the peer MIPC socket */
int mipc_getpeername(int sd, struct mipc_sockaddr *addr, socklen_t *addrlen);

/* Get the address of a MIPC socket */
int mipc_getsockname(int sd, struct mipc_sockaddr *addr, socklen_t *addrlen);

/* Get the value of an option associated with a MIPC socket */
int mipc_getsockopt(int sd, int level, int optname, void *optval,
		    socklen_t *optlen);

/* Get MIPC statistics for a bus */
int mipc_getstatsbybus(int busnum, struct mipc_stats *buf);

/* Enable a MIPC socket to listen for connection requests */
int mipc_listen(int sd, int backlog);

/* Convert a node-independent offset to a local pointer address */
static MULTIOS_INLINE void *mipc_offset2addr(MIPC_OFFSET offset);

/* Process bus events (for polled buses) */
int mipc_processbus(int busId);

/* Receive a message from a MIPC socket */
ssize_t mipc_recv(int sd, void *buf, size_t buflen, int flags);

/* Receive a message from a MIPC socket */
ssize_t mipc_recvfrom(int sd, void *buf, size_t buflen, int flags,
		      struct mipc_sockaddr *from, socklen_t *fromlen);

/* Send a message to a MIPC socket */
ssize_t mipc_send(int sd, const void *buf, size_t buflen, int flags);

/* Send a message to a MIPC socket */
ssize_t mipc_sendto(int sd, const void *buf, size_t buflen, int flags,
		    const struct mipc_sockaddr *to, socklen_t tolen);

/* Send 64-bit data (fast datapath) */
int mipc_sendexpress64(int sd, const struct mipc_sockaddr *to,
		       uint64_t data);

/* Set the value of an option associated to a MIPC socket */
int mipc_setsockopt(int sd, int level, int optname, 
		    const void *optval, socklen_t optlen);

/* Shutdown a MIPC connection */
int mipc_shutdown(int sd, int how);

/* Creates a MIPC socket */
int mipc_socket(int family, int type, int protocol);

/* Allocate a zero-copy buffer */
int mipc_zalloc(int sd, size_t nbytes, uint8_t **buf, MIPC_ZBUFFER *zbuf,
		int flags);

/* Allocate a zero-copy buffer of MTU size */
int mipc_zallocbuf(int sd, uint8_t **buf, MIPC_ZBUFFER *zbuf, int flags);

/* Free a zero-copy buffer */
int mipc_zfree(int sd, MIPC_ZBUFFER zbuf);

/* Receive a zero-copy message from a MIPC socket */
ssize_t mipc_zrecv(int sd, void **buf, MIPC_ZBUFFER *zbuf, int flags);

/* Receive a zero-copy message from a MIPC socket */
ssize_t mipc_zrecvfrom(int sd, void **buf, MIPC_ZBUFFER *zbuf, int flags, 
		       struct mipc_sockaddr *from, socklen_t *fromlen);

/* Send a zero-copy message to a MIPC socket */
ssize_t mipc_zsend(int sd, MIPC_ZBUFFER zbuf, size_t buflen, int flags);

/* Send a zero-copy message to a MIPC socket */
ssize_t mipc_zsendto(int sd, MIPC_ZBUFFER zbuf, size_t buflen, int flags,
		     const struct mipc_sockaddr *to, socklen_t tolen);

/* Get the user handle of a socket */
static MULTIOS_INLINE int mipc_getuserhandle(int sd, unsigned long *userhandle);

/* Set the user handle of a socket */
static MULTIOS_INLINE int mipc_setuserhandle(int sd, unsigned long userhandle);

/*---------------------------------------------------------------------------
 * Implementation of inlined APIs -- NOT FOR USE BY MIPC APPLICATIONS!
 *---------------------------------------------------------------------------
 */
 
/* Functions to get/set the debug mode */
int mipc_getdebugmode(void);
void mipc_setdebugmode(int value);


#define MIPC_SD_MODE 1
	/* 0 = sd is socket array index; 1 = sd is socket array byte offset */

extern char *mipcSmStartAddr;
extern unsigned long *mipcUserHandles;
extern unsigned int mipcMaxSockets;

static MULTIOS_INLINE unsigned int mipc_sd2index(int sd)
{
#if (MIPC_SD_MODE == 0)
	return (unsigned int)sd;
#else
	return (unsigned int)sd >> MIPC_SD_BITS;
#endif
}

static MULTIOS_INLINE int mipc_index2sd(unsigned int index)
{
#if (MIPC_SD_MODE == 0)
	return (int)index;
#else
	return (int)(index << MIPC_SD_BITS);
#endif
}

static MULTIOS_INLINE unsigned int mipc_sd2offset(int sd)
{
#if (MIPC_SD_MODE == 0)
	return (unsigned int)sd << MIPC_SD_BITS;
#else
	return (unsigned int)sd;
#endif
}

static MULTIOS_INLINE int mipc_offset2sd(unsigned int offset)
{
#if (MIPC_SD_MODE == 0)
	return (int)(offset >> MIPC_SD_BITS);
#else
	return (int)offset;
#endif
}

static MULTIOS_INLINE int mipc_sd_legal(int sd)
{
#if (MIPC_SD_MODE == 0)
	return (sd >= 0) && ((unsigned int)sd < mipcMaxSockets);
#else
	return (sd >= 0) && (mipc_sd2index(sd) < mipcMaxSockets) &&
		!(sd & ((1 << MIPC_SD_BITS) - 1));
#endif
}

static MULTIOS_INLINE MIPC_OFFSET mipc_addr2offset(void *address)
{
	return (MIPC_OFFSET)((char *)address - mipcSmStartAddr);
}

static MULTIOS_INLINE void *mipc_offset2addr(MIPC_OFFSET offset)
{
	return (void *)(mipcSmStartAddr + offset);
}

static MULTIOS_INLINE int mipc_getuserhandle(int sd, unsigned long *userhandle)
{
#ifdef MIPC_CHECK_ARGS
	if (!mipc_sd_legal(sd))
		return -MIPC_EBADF;
#endif
	*userhandle = mipcUserHandles[mipc_sd2index(sd)];
	return MIPC_OK;
}

static MULTIOS_INLINE int mipc_setuserhandle(int sd, unsigned long userhandle)
{
#ifdef MIPC_CHECK_ARGS
	if (!mipc_sd_legal(sd))
		return -MIPC_EBADF;
#endif
	mipcUserHandles[mipc_sd2index(sd)] = userhandle;
	return MIPC_OK;
}

#ifdef __cplusplus
}
#endif

#endif /* __INCmipch */

