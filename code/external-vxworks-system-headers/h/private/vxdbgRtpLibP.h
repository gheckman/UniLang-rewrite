/* vxdbgRtpLibP.h - private RTP debugging facility header */

/*
 * Copyright (c) 2004-2006 Wind River Systems, Inc.  
 *
 * The right to copy, distribute, modify or otherwise make use  of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
01c,26oct06,rlp  Renamed dbgRtpLibP.h header file (REQ00007655).
01b,10jan05,bpn  Added dbgRtpInit() prototype. Removed dbgRtpBpAllRemove().
01a,05apr04,bpn  Written.
*/

#ifndef __INCvxdbgRtpLibPh
#define __INCvxdbgRtpLibPh

#ifdef __cplusplus
extern "C" {
#endif

/* Function declarations */

extern STATUS	vxdbgRtpLibInit (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCvxdbgRtpLibPh */

