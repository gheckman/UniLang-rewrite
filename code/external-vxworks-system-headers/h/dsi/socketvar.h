/* dsi/socketvar.h - internal socket structures and definitions for DSI */

/*
 * Copyright (c) 2007 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)socketvar.h	8.3 (Berkeley) 2/19/95
 * $FreeBSD: src/sys/sys/socketvar.h,v 1.46.2.9 2002/08/14 22:23:10 dg Exp $
 */

/*
modification history
--------------------
01a,22jun07,ebh  Created from net/socketvar.h (02g,27dec06,wap) for DSI changes
*/


#ifndef _DSI_SOCKETVAR_H_
#define _DSI_SOCKETVAR_H_

#include <net/protosw.h>
#include <sys/queue.h>
#include <semLib.h>
#include <selectLib.h>
#include <sockFunc.h>

#ifdef __cplusplus
 extern "C" {
#endif

/*
 * Kernel structure per socket.
 * Contains send and receive buffer queues,
 * handle on protocol and pointer to protocol
 * private data and error information.
 */
typedef	u_quad_t so_gen_t;

/*
 * WRS-port
 * - if 0'd so_zone, and the accept filter members
 */

#ifdef _WRS_KERNEL
struct socket {
        struct sockFunc *pSockFuncTbl;  /* socket backend function table */
	short	so_type;		/* generic type, see socket.h */
	short	so_options;		/* from socket call, see socket.h */
	u_short	so_linger;		/* time to linger while closing */
	short	so_state;		/* internal state flags SS_*, below */
	caddr_t	so_pcb;			/* protocol control block */
	struct	protosw *so_proto;	/* protocol handle */

/*
 * Variables for connection queuing.
 * Socket where accepts occur is so_head in all subsidiary sockets.
 * If so_head is 0, socket is not related to an accept.
 * For head socket so_incomp queues partially completed connections,
 * while so_comp is a queue of connections ready to be accepted.
 * If a connection is aborted and it has so_head set, then
 * it has to be pulled out of either so_incomp or so_comp.
 * We allow connections to queue up based on current queue lengths
 * and limit on number of queued connections for this socket.
 */
	struct	socket *so_head;	/* back pointer to accept socket */
	TAILQ_HEAD(, socket) so_incomp;	/* queue of partial unaccepted connections */
	TAILQ_HEAD(, socket) so_comp;	/* queue of complete unaccepted connections */
	TAILQ_ENTRY(socket) so_list;	/* list of unaccepted connections */
	short	so_qlen;		/* number of unaccepted connections */
	short	so_incqlen;		/* number of unaccepted incomplete
					   connections */
	short	so_qlimit;		/* max number queued connections */
	short	so_timeo;		/* connection timeout */
	u_short	so_error;		/* error affecting connection */
	u_long	so_oobmark;		/* chars to oob mark */

        short        so_pgrp;           /* WRS extension for ASYNC oper */
        int          so_fd;             /* WRS extension for storing FD */

        SEL_WAKEUP_LIST  so_selWakeupList;  /* WRS extension for select */

/*
 * Variables for socket buffering.
 */
	struct	sockbuf {
		u_long	sb_cc;		/* actual chars in buffer */
		u_long	sb_hiwat;	/* max actual char count */
		u_long	sb_mbcnt;	/* chars of mbufs used */
		u_long	sb_mbmax;	/* max chars of mbufs to use */
		long	sb_lowat;	/* low water mark */
		struct	mbuf *sb_mb;	/* the mbuf chain */

		short	sb_flags;	/* flags, see below */
		short	sb_timeo;	/* timeout for read/write */
		u_long	sb_selCount;

		SEMAPHORE sb_Sem;	/* WRS extension for sb semaphore */
		int	sb_refCount;	/* WRS extension for users of sem */
		/* struct socket * sb_so;  ptr to socket if closing, or NULL */
	} so_rcv, so_snd;
#define	SB_MAX		(256*1024)	/* default for max chars in sockbuf */
#define	SB_LOCK		0x01		/* lock on data queue */
#define	SB_WANT		0x02		/* someone is waiting to lock */
#define	SB_WAIT		0x04		/* someone is waiting for data/space */
#define	SB_SEL		0x08		/* someone is selecting */
#define	SB_ASYNC	0x10		/* ASYNC I/O, need signals */
#define	SB_UPCALL	0x20		/* someone wants an upcall */
#define	SB_NOINTR	0x40		/* operations not interruptible */
#define SB_AIO		0x80		/* AIO operations queued */
#define SB_KNOTE	0x100		/* kernel note attached */

	void	(*so_upcall) __P((struct socket *, void *, int));
	void	*so_upcallarg;

	/* NB: generation count must not be first; easiest to make it last. */
	so_gen_t _so_gencnt;		/* generation count */
	void	*so_emuldata;		/* private data for emulators */

	int    connTimeo;		  /* connection establishment timeout */

	void	*so_bkendaux;     /* socket backend auxiliary data */
};
#endif /* _WRS_KERNEL */

/*
 * Socket state bits.
 */
#define	SS_NOFDREF		0x0001	/* no file table ref any more */
#define	SS_ISCONNECTED		0x0002	/* socket connected to a peer */
#define	SS_ISCONNECTING		0x0004	/* in process of connecting to peer */
#define	SS_ISDISCONNECTING	0x0008	/* in process of disconnecting */
#define	SS_CANTSENDMORE		0x0010	/* can't send more data to peer */
#define	SS_CANTRCVMORE		0x0020	/* can't receive more data from peer */
#define	SS_RCVATMARK		0x0040	/* at mark on input */

#define SS_PRIV                 0x0080  /* privileged for broadcast, raw... */

#define	SS_NBIO			0x0100	/* non-blocking ops */
#define	SS_ASYNC		0x0200	/* async i/o notify */
#define	SS_ISCONFIRMING		0x0400	/* deciding to accept connection req */

#define	SS_INCOMP		0x0800	/* unaccepted, incomplete connection */
#define	SS_COMP			0x1000	/* unaccepted, complete connection */
#define	SS_ISDISCONNECTED	0x2000	/* socket disconnected from peer */


/*
 * Macros for sockets and socket buffering.
 */

/*
 * Do we need to notify the other side when I/O is possible?
 */
#define	sb_notify(sb)	(((sb)->sb_flags & (SB_WAIT | SB_SEL | SB_ASYNC | \
    SB_UPCALL | SB_AIO | SB_KNOTE)) != 0)

/*
 * How much space is there in a socket buffer (so->so_snd or so->so_rcv)?
 * This is problematical if the fields are unsigned, as the space might
 * still be negative (cc > hiwat or mbcnt > mbmax).  Should detect
 * overflow and return 0.  Should use "lmin" but it doesn't exist now.
 */
#define	sbspace(sb) \
    ((long) imin((int)((sb)->sb_hiwat - (sb)->sb_cc), \
	 (int)((sb)->sb_mbmax - (sb)->sb_mbcnt)))

/* do we have to send all at once on a socket? */
#define	sosendallatonce(so) \
    ((so)->so_proto->pr_flags & PR_ATOMIC)

/* can we read something from so? */
#define	soreadable(so) \
    ((so)->so_rcv.sb_cc >= (so)->so_rcv.sb_lowat || \
	((so)->so_state & SS_CANTRCVMORE) || \
	(so)->so_comp.tqh_first || (so)->so_error)

/* can we write something to so? */
#define	sowriteable(so) \
    ((sbspace(&(so)->so_snd) >= (so)->so_snd.sb_lowat && \
	(((so)->so_state&SS_ISCONNECTED) || \
	  ((so)->so_proto->pr_flags&PR_CONNREQUIRED)==0)) || \
     ((so)->so_state & SS_CANTSENDMORE) || \
     (so)->so_error)

/* adjust counters in sb reflecting freeing of m */
#define	sbfree(sb, m) { \
	(sb)->sb_cc -= (m)->m_len; \
	(sb)->sb_mbcnt -= MSIZE; \
	if ((m)->m_flags & M_EXT) \
		(sb)->sb_mbcnt -= (m)->m_extSize; \
}

/* return total number of pended users of this socket */
#define sbusercount(so)  \
	((int)((so)->so_rcv.sb_refCount + (so)->so_snd.sb_refCount))

#ifdef _WRS_KERNEL

/*
 * Macro to add the socket-based VLAN to the m_pkthdr. This is in the
 * _WRS_KERNEL section because it will never be used by user code.
 */
#ifdef SOCKET_VLAN
/* 
 * Keep the vlan in the m_pkthdr in host byte order until it needs to be
 * put into the packet (by the MUX-L2 egress code).
 */
#define SO_VLAN_ADD(m, so) \
			  if ((so)->so_options & SO_VLAN) \
			    { \
			    (m)->m_pkthdr.vlan = (so)->so_vlan; \
			    (m)->m_pkthdr.csum_flags |= (so)->so_vlan_options; \
			    }
#endif /* SOCKET_VLAN */

/*
 * Argument structure for sosetopt et seq.  This is in the _WRS_KERNEL
 * section because it will never be visible to user code.
 */

enum sopt_dir { SOPT_GET, SOPT_SET };
struct sockopt {
	enum	sopt_dir sopt_dir; /* is this a get or a set? */
	int	sopt_level;	/* second arg of [gs]etsockopt */
	int	sopt_name;	/* third arg of [gs]etsockopt */
	void   *sopt_val;	/* fourth arg of [gs]etsockopt */
	size_t	sopt_valsize;	/* (almost) fifth arg of [gs]etsockopt */
	struct	proc *sopt_p;	/* calling process or null if kernel */
};

struct sf_buf {
	SLIST_ENTRY(sf_buf) free_list;	/* list of free buffer slots */
	int		refcnt;		/* reference count */
};

extern STATUS unixIoctlMemValidate (unsigned int cmd, const void * pData);

#endif /* _WRS_KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* !_DSI_SOCKETVAR_H_ */
