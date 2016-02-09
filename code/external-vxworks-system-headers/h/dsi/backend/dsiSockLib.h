/* dsiSockLib.h -  DSI sockets backend */

/*
 * Copyright (c) 2004-2007, 2010-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01o,12jul12,shi  clean up warnings (WIND00357529)
01n,08sep11,shi  fix defect WIND00297134; update the declaration of dsiGetsockopt() and dsiSetsockopt() 
01m,24jun11,shi  LP64 conversion
01l,29apr10,pad  Moved extern C statement after include statements.
01k,19jun07,ebh  Changes to allow COMP to run on SMP systems (SMP-safe)
01j,09may07,ebh  Changed dsiSoFree to return a STATUS (Defect #91328)
01i,16sep06,kch  Replaced (struct ifnet *) references with (void *).
01h,10feb05,dlk  Embed socket semaphores in struct socket, and remove
                 so_timeoSem and so_lingerSem.
01g,23sep04,bwa  added dsiDomainAdd() prototype.
01f,19aug04,bwa  added dsiDataPoolShow() and dsiSysPoolShow() prototypes.
01e,16aug04,bwa  updated dsiPoolInit() prototype.
01d,11jun04,ymz  removed compiler warning
01c,31may04,bwa  added DSI_PKT_SZ and DSI_SB_ALLOC macro.
01b,12may04,bwa  modified dsiPoolInit() prototype's parameters list.
01a,18mar04,bwa  written, copied from bsdSockLib.h
*/

#ifndef __INCdsiSockLibh
#define __INCdsiSockLibh

/* includes */

#include <netVersion.h>
#include <dsi/socketvar.h>
#include <sockFunc.h>
#include <stat.h>
#include <cfgDefs.h>
#include <netBufLib.h>
#include <net/domain.h>

#ifdef __cplusplus
extern "C" {
#endif

/* DSI buffer pools */

extern NET_POOL_ID _pDsiDpool;
extern NET_POOL_ID _pDsiSysPool;

/* allocation of clusters for address holders and PCBs */

#define DSI_SO_ALLOC(ds)    (void *) netClusterGet(_pDsiSysPool, \
                            netClPoolIdGet(_pDsiSysPool, (sizeof(ds)), TRUE))
#define DSI_PCB_ALLOC(ds)   DSI_SO_ALLOC(ds)
#define DSI_ADDR_ALLOC(ds)  DSI_SO_ALLOC(ds)

#define DSI_SO_FREE(x)      netClFree (_pDsiSysPool, (UCHAR *)(x))
#define DSI_PCB_FREE(x)     DSI_SO_FREE(x)
#define DSI_ADDR_FREE(x)    DSI_SO_FREE(x)

/* wrapper macros */

#define DSI_SB_LOCK(sb, wf) ((sb)->sb_flags & SB_LOCK ? \
                (((wf) == M_WAITOK) ? dsiSbLock(sb) : EWOULDBLOCK) : \
                (((sb)->sb_flags |= SB_LOCK), 0))

/* release lock on sockbuf sb */
#define DSI_SB_UNLOCK(sb) { \
        (sb)->sb_flags &= ~SB_LOCK; \
        if ((sb)->sb_flags & SB_WANT) { \
                (sb)->sb_flags &= ~SB_WANT; \
				{ \
				int i;		/* loop counter */ \
				for (i=sb->sb_refCount; i>0; i--) \
					{ \
					semGive(&sb->sb_Sem); \
					} \
				} \
        } \
}

/* wake up all pending tasks on the socket for receive */
#define DSI_SO_R_WAKEUP(so)                             \
    do                                                  \
        {                                               \
        if (sb_notify(&(so)->so_rcv))                   \
            dsiSbWakeup((so), &(so)->so_rcv, SELREAD);  \
        } while ((0))

/* indicate that one task can receive a packet on the receive socket */
#define DSI_SO_R_WAKEUP_ONE(so)                         \
    do                                                  \
        {                                               \
        dsiSbWakeupOne((so), &(so)->so_rcv, SELREAD);   \
        } while ((0))

#define DSI_SO_W_WAKEUP(so)  \
                        do { \
                          if (sb_notify(&(so)->so_snd)) \
                            dsiSbWakeup((so), &(so)->so_snd, SELWRITE); \
                        } while ((0))

/*
 * DSI_PKT_SZ - compute the size and cnt of a DSI packet
 *
 * void DSI_PKT_SZ
 *     (
 *      mbuf * pMbuf,   /# the packet in mbuf form     #/
 *      int    sz,      /# return value: packet size   #/
 *      int    cnt      /# return value: cluster count #/
 *     )
 */

#define DSI_PKT_SZ(pMbuf, sz, cnt)                      \
    do                                                  \
        {                                               \
        struct mbuf * DSI_PKT_SZ_pCur = (pMbuf);        \
        while (DSI_PKT_SZ_pCur != NULL)                 \
            {                                           \
            sz  += DSI_PKT_SZ_pCur->m_len;              \
            cnt += MSIZE;                               \
            if (DSI_PKT_SZ_pCur->m_flags & M_EXT)       \
                cnt += DSI_PKT_SZ_pCur->m_extSize;      \
            DSI_PKT_SZ_pCur = DSI_PKT_SZ_pCur->m_next;  \
            }                                           \
        }                                               \
    while ((0))

#define DSI_SB_ALLOC(pSb, sz, cnt)                      \
    do                                                  \
        {                                               \
        (pSb)->sb_cc  += sz;                            \
        (pSb)->sb_mbcnt += cnt;                         \
        }                                               \
    while ((0))
    
/* function declarations */

extern STATUS   dsiDomainAdd (struct domain * pDomain);
extern SOCK_FUNC *dsiSockLibInit (void);
extern void     dsiSysPoolShow (void);
extern void     dsiDataPoolShow (void);
extern STATUS   dsiPoolInit (NET_POOL_CONFIG_PARAMS * pPools);
extern STATUS 	dsiConnect (struct socket *so, struct sockaddr *name, int namelen);
extern STATUS 	dsiConnectWithTimeout (struct socket *so, struct sockaddr *adrs,
				    int adrsLen, struct timeval *timeVal);
extern STATUS 	dsiGetpeername (struct socket *so, struct sockaddr *name, int *namelen);
extern STATUS 	dsiGetsockname (struct socket *so, struct sockaddr *name, int *namelen);
extern STATUS 	dsiGetsockopt (struct socket *so, int level, int optname, char *optval,
			    socklen_t *optlen);
extern STATUS 	dsiSetsockopt (struct socket *so, int level, int optname, char *optval,
			    socklen_t optlen);
extern STATUS 	dsiShutdown (struct socket *so, int how);
extern int 	dsiAccept (struct socket **pSo, struct sockaddr *addr, int *addrlen);
extern ssize_t 	dsiRecv (struct socket *so, char *buf, size_t bufLen, int flags);
extern int 	dsiRecvfrom (struct socket *so, char *buf, int bufLen, int flags,
			  struct sockaddr *from, int *pFromLen);
extern int 	dsiRecvmsg (struct socket *so, struct msghdr *mp, int flags);
extern ssize_t 	dsiSend (struct socket *so, char *buf, size_t bufLen, int flags);
extern int 	dsiSendmsg (struct socket *so, struct msghdr *mp, int flags);
extern int 	dsiSendto (struct socket *so, caddr_t buf, int bufLen, int flags,
			struct sockaddr *to, int tolen);
extern STATUS   dsiZbufSockRtn (void);
extern struct   socket * dsiSoAlloc (void);
extern struct   socket * dsiSoNewConn3 (struct socket * head, int connstatus,
                                         struct proc * p);
extern int      dsiSoCreate   (int dom, struct socket ** aso, int type,
                               int proto, struct proc * p);

extern STATUS dsiSoFree(struct socket * so);
extern int  dsiSoClose(struct socket * so);
extern int  dsiSoAbort(struct socket * so);
extern void dsiSoIsConnected (struct socket *so);
extern void dsiSoIsDisconnected (struct socket *so);
extern void dsiSoCantSendMore (struct socket *so);
extern void dsiSoCantRcvMore (struct socket *so);
extern int  dsiSbLock (struct sockbuf *sb);
extern void dsiSbWakeup (struct socket *so, struct sockbuf *sb,
						 SELECT_TYPE wakeupType);
extern void dsiSbWakeupOne (struct socket *so, struct sockbuf *sb,
		         SELECT_TYPE wakeupType);
extern int dsiControlNotSupp (struct socket *so, u_long cmd, caddr_t data,
                              void *ifp, struct proc *p);
extern int dsiRcvoobNotSupp (struct socket *so, struct mbuf *m, int flags);
extern int dsiSenseNull (struct socket *so, struct stat *sb);
int dsiSoReserve (struct socket *so, u_long sndcc, u_long rcvcc);
ssize_t dsiSbReserve (struct sockbuf *sb, u_long cc, struct socket *so,
                  struct proc *p);
extern int dsiSbWait (struct sockbuf *sb);
extern int dsiSbNoWait (struct sockbuf *sb);

#ifdef __cplusplus
}
#endif

#endif    /* __INCdsisocklibh */

