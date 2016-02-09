/* wdbRtpLibP.h - private header file for RTP runtime interface */

/*
 * Copyright (c) 2005,2010 Wind River Systems, Inc.  
 *
 * The right to copy, distribute, modify or otherwise make use  of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
01c,29apr10,pad  Moved extern C statement after include statements.
01b,05mar10,rlp  LP64 adaptation.
01a,25jul05,bpn  Created.
*/

#ifndef __INCwdbRtpLibPh
#define __INCwdbRtpLibPh

/* includes */

#include <rtpLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* data types */

typedef struct wdb_rtp_info
    {
    /* RTP exit hook for WDB */
    void	(*wdbDeleteHook) (WDB_CTX ctx, UINT32 exitCode, UINT32 err);
    /* RTP Detach routine */
    void	(*wdbDetachHook) (RTP_ID rtpId, struct wdb_rtp_info * pInfo);
    /* TRUE if CPS is set for that task */
    BOOL	childProcessStop;
    } WDB_RTP_INFO;

/* function prototypes */

extern void		wdbRtpCtrlLibInit (void);
extern STATUS		wdbRtpDeleteHookManage (BOOL addHook);
extern WDB_RTP_INFO *	wdbRtpInfoAlloc (RTP_ID pid);

#ifdef __cplusplus
}
#endif

#endif /* __INCwdbRtpLibPh */
