/* wdbSlipPktLib.h - header file for WDB agents SLIP packet driver */

/*
 * Copyright (c) 1994-1995,2002,2007-2008,2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01g,28apr10,jmp  Updated WDB_SLIP_PKT_DEV to replace inBufBase[SLMTU] by a
                 buffer pointer.
		 Updated wdbSlipPktDevInit() prototype.
01f,27aug08,jpb  Renamed VSB header file
01e,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
01d,05jul07,rlp  Made serial line packetizer driver SMP safe.
01c,26apr02,dat  Adding cplusplus protection, SPR 75017
01b,15jun95,ms	changed SIO_DEV to SIO_CHAN
01a,20dec94,ms  written.
*/

#ifndef __INCwdbSlipPktLibh
#define __INCwdbSlipPktLibh

/* includes */

#include <vsbConfig.h>
#include <sioLib.h>
#include <wdb/wdb.h>
#include <wdb/wdbCommIfLib.h>
#include <wdb/wdbMbufLib.h>
#ifdef	_WRS_CONFIG_SMP
#include <spinLockLib.h>
#endif	/* _WRS_CONFIG_SMP */

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define SLMTU           1006    /* be compatible with BSD 4.3 SLIP */

/* data types */

typedef struct		/* hidden */
    {
    WDB_DRV_IF		wdbDrvIf;	/* all packet device have this */
    SIO_CHAN *		pSioChan;	/* underlying serial channel */
    u_int		mode;

    /* only one input buffer at a time for RPC's */

    u_int		inputState;
    caddr_t		inBufPtr;
    char *		inBufBase;
    caddr_t		inBufEnd;

    /* output is a chain of mbufs */

    struct mbuf *	pMbuf;
    u_int		outputState;
    int			outputIx;
#ifdef	_WRS_CONFIG_SMP
    spinlockIsr_t	outputLock;
#endif	/* _WRS_CONFIG_SMP */
    } WDB_SLIP_PKT_DEV;

/* function prototypes */

extern void    wdbSlipPktDevInit (WDB_SLIP_PKT_DEV *pPktDev,
				  SIO_CHAN *pSioChan,
				  void (*inputRtn)(),
				  char * inputBuffer,
				  UINT32 deviceMtu);

#ifdef __cplusplus
}
#endif

#endif  /* __INCwdbSlipPktLibh */

