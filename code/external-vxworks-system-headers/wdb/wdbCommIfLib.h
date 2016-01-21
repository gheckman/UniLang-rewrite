/* wdbCommIfLib.h - header file for the WDB agents communication interface */

/*
 * Copyright (c) 1994,1995,2002,2005,2010,2011 Wind River Systems, Inc.  
 *
 * The right to copy, distribute, modify or otherwise make use  of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
01j,08apr11,rlp  Added ioctl method to WDB_COMM_IF structure.
01i,04mar11,jmp  Fixed foundation/wdbagent-ptrace build.
01h,31jan11,rlp  Fully qualified all function pointers of wdb_comm_if structure.
01g,29jul10,pad  Moved extern C statement after include statements.
01f,06dec05,dbt  Remove references to sockaddr_in.
01e,01dec05,dbt  Removed references to timeval structure.
01d,25apr02,jhw  Added C++ support (SPR 76304).
01c,03jun95,ms	 changed read/write to sendto/rcvfrom
01b,05apr95,ms 	 new data types.
01a,23sep94,ms 	 written.
*/

#ifndef __INCwdbCommIfLibh
#define __INCwdbCommIfLibh

/* includes */

#ifndef	LINUX_TARGET
#include <vxWorks.h>
#include <netBufLib.h>
#endif	/* !LINUX_TARGET */
#include <wdb/wdb.h>


#ifdef __cplusplus
extern "C" {
#endif

/* definitions */

#define WDB_COMM_MODE_POLL      1
#define WDB_COMM_MODE_INT       2

/* data types */

/*
 * WDB_COMM_IF - interface used by the agent to talk to the host.
 */

typedef void * WDB_COMM_ID;

typedef struct wdb_comm_if
    {
    WDB_COMM_ID	      commId;
    int (*rcvfrom)    (WDB_COMM_ID commId, char * addr, UINT32 len,
			void * pAddr, UINT32 addrLength, INT32 timeout);
    int (*sendto)     (WDB_COMM_ID commId, char * addr, UINT32 len,
			void * pAddr, UINT32 addrLength);
    int (*modeSet)    (WDB_COMM_ID commId, UINT32 newMode);
    int (*cancel)     (WDB_COMM_ID commId);
    int (*hookAdd)    (WDB_COMM_ID commId, void (*rout)(UINT32 arg),UINT32 arg);
    int (*notifyHost) (WDB_COMM_ID commId);
    int (*ioctl)      (WDB_COMM_ID commId, int function, long arg);
    } WDB_COMM_IF;

#ifndef	LINUX_TARGET
/*
 * WDB_DRV_IF - interface between a driver and the agents pseudo-UDP/IP stack
 *
 * The default agent configuration uses the native VxWorks UDP/IP stack which
 * has its own interface to a driver (a net_if structure).
 * The agent can also be configured to use a pseudo-UDP/IP stack that
 * is independant of the OS. The pseudo-UDP/IP stack is used for
 * communication with the system mode agent.
 * The WDB_DRV_IF structure allows new drivers to be installed in the
 * pseudo-UDP/IP stack.
 */

typedef struct wdb_drv_if
    {
    UINT32	mode;			/* available device modes */
    UINT32  	mtu;			/* maximum transmit packet size */ 
    					/* callback when pkt arrives */
    void    	(*stackRcv)(struct mbuf * pMbuf);

    /* driver routines */

    void *   	devId;			/* device ID */
    					/* poll device for data */
    STATUS	(*pollRtn)(void * pDev);
    					/* transmit a packet */
    STATUS 	(*pktTxRtn)(void * pDev, struct mbuf * pMbuf);
    					/* toggle driver mode */
    STATUS 	(*modeSetRtn)(void * pDev, uint_t mode);
    int		(*ioctlRtn)(void * pDev, int function, _Vx_usr_arg_t arg);		/* misc */
    } WDB_DRV_IF;
#endif	/* !LINUX_TARGET */
#ifdef __cplusplus
}
#endif

#endif  /* __INCwdbCommIfLibh */

