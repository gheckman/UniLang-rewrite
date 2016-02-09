/* uncomp_var.h - AF_LOCAL/COMP protocol control block definition */

/*
 * Copyright (c) 2003-2004, 2007, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01d,29apr10,pad  Moved extern C statement after include statements.
01c,22jun07,ebh  change reference to dsi/socketvar.h from net/socketvar.h
01b,12apr04,bwa  moved DS_xxx macros to h/dsiSockLib.h.
01b,20jan04,bwa  added pRegQTail field; renamed pExpQ field to pExpQTail;
                 added pRecvPacket field;
                 removed selfGenCnt and xxxMaxData fields;
                 removed _ASM_LANGUAGE references.
01a,30sep03,bwa  written.
*/

#ifndef __INCuncomp_varh
#define __INCuncomp_varh

#include <vxWorks.h>
#include <dllLib.h>

#ifdef __cplusplus
extern "C" {
#endif

struct socket;

/* data structures */

typedef struct uncompcb             /* AF_LOCAL/COMP protocol control block  */
    {                               /* ------------------------------------- */
    DL_NODE          node;          /* 0x00: entry in the uncomp socket list */
    struct socket *  pSelfSocket;   /* 0x08: back pointer to socket          */
    struct socket *  pPeerSocket;   /* 0x0c: connected socket                */
    uint16_t         selfState;     /* 0x10: state of socket                 */
    uint16_t         selfName;      /* 0x12: name of socket (/comp/socket/X) */
    struct mbuf *    pLastReg;      /* 0x14: ptr to last regular message     */
    struct mbuf *    pLastExp;      /* 0x18: ptr to last express message     */
    struct mbuf *    pRecvPacket;   /* 0x1c: ptr to packet being received    */
    uint16_t         hiwatermark;   /* 0x1e: largest amount of data queued   */
    uint16_t         dropped;       /* 0x20: amount of packets dropped       */
    } UNCOMPCB;                     /* 0x24: TOTAL SIZE                      */

/* useful macros */

#define SO_TO_UNCOMPCB(so)   ((struct uncompcb *)(so->so_pcb))
#define UNCOMPCB_TO_SO(cb)   ((struct socket *)(cb->pSelfSocket))

#ifdef __cplusplus
}
#endif

#endif /* __INCuncomp_varh */

