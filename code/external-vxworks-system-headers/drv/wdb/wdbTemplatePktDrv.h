/* wdbTemplatePktLib.h - header file for WDB agents template packet driver */

/*
 * Copyright (c) 1995-2005 Wind River Systems, Inc.  
 *
 * The right to copy, distribute, modify or otherwise make use  of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
01c,07dec05,dbt  Replaced bool_t with BOOL.
		 Cleanup header files inclusion
01b,26apr02,dat  Adding cplusplus protection, SPR 75017
01a,23aug95,ms	 written.
*/

#ifndef __INCwdbTemplatePktLibh
#define __INCwdbTemplatePktLibh

/* includes */

#include "wdb/wdb.h"
#include "wdb/wdbCommIfLib.h"
#include "wdb/wdbMbufLib.h"

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define WDB_TEMPLATE_PKT_MTU           1000    /* MTU of this driver */

/* data types */

typedef struct		/* hidden */
    {
    WDB_DRV_IF	wdbDrvIf;		/* a packet dev must have this first */

    u_int	mode;			/* current mode - poll or int */

    /* input buffer - loaned to the agent when a packet arrives */

    BOOL	inputBusy;
    char	inBuf [WDB_TEMPLATE_PKT_MTU];

    /* output buffers - a chain of mbufs given to us by the agent */

    BOOL	outputBusy;

    /* device register addresses etc */

    } WDB_TEMPLATE_PKT_DEV;

/* function prototypes */

#if defined(__STDC__)

extern void	wdbTemplatePktDevInit (WDB_TEMPLATE_PKT_DEV *pPktDev,
				  /* device specific init params, */
				  void (*stackRcv)());

#else   /* __STDC__ */

extern void    wdbTemplatePktDevInit ();

#endif  /* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif  /* __INCwdbTemplatePktLibh */

