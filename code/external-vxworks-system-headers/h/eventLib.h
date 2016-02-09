/* eventLib.h - events library header file */

/*
 * Copyright (c) 2001-2003, 2008-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01j,16jun10,pcs  Change data type of timeout from an int to _Vx_ticks_t
01i,29apr10,pad  Moved extern C statement after include statements.
01h,15may09,pcs  Add new datatype _Vx_event_t.
01g,12mar09,pcs  Updated to add support for the LP64 data model.
01f,23oct08,zl   added interruptible events options.
01e,18nov02,bwa  Added EVENTS_KEEP_UNWANTED option (SPR 84417).
01d,15jan02,bwa  Removed events 25 to 32 from list of events available to user.
01c,13nov01,bwa  Changed EVENTxx defs to VXEVxx.
01b,17oct01,bwa  Added #include "vwModNum.h". Added 2 errnos.
01a,20sep01,bwa  Created
*/

#ifndef __INCeventLibh
#define __INCeventLibh

#include <vxWorks.h>
#include <vwModNum.h>

#ifdef __cplusplus
extern "C" {
#endif

/* errnos */

#define S_eventLib_TIMEOUT			(M_eventLib | 0x0001)
#define S_eventLib_NOT_ALL_EVENTS		(M_eventLib | 0x0002)
#define S_eventLib_ALREADY_REGISTERED		(M_eventLib | 0x0003)
#define S_eventLib_EVENTSEND_FAILED		(M_eventLib | 0x0004)
#define S_eventLib_ZERO_EVENTS			(M_eventLib | 0x0005)
#define S_eventLib_TASK_NOT_REGISTERED		(M_eventLib | 0x0006)
#define S_eventLib_NULL_TASKID_AT_INT_LEVEL	(M_eventLib | 0x0007)

/* options */

#define EVENTS_WAIT_ALL		0x00	/* wait for all events to occur */
#define EVENTS_WAIT_ANY		0x01	/* wait for one of many events  */
#define EVENTS_RETURN_ALL	0x02	/* return all events received   */
#define EVENTS_KEEP_UNWANTED	0x04	/* don't clear unwanted events	*/
#define EVENTS_FETCH		0x80	/* return events received immediately */

/* resource-related options */

#define EVENTS_OPTIONS_NONE	0x00
#define EVENTS_SEND_ONCE	0x01  /* unregister events after eventSend   */
#define EVENTS_ALLOW_OVERWRITE	0x02  /* can overwrite previous registration */
#define EVENTS_SEND_IF_FREE	0x04  /* send events in xxxEvStart()         */

/* configuration options */

#define EVENTS_NONINTERRUPTIBLE	0x00	/* signals don't wake up RTP tasks */
#define EVENTS_INTERRUPTIBLE	0x01	/* signals wake up RTP tasks */

/*
 * Defines for all 24 events available to users. Events 25 to 32 are reserved
 * for system use and should never be used outside of that scope
 */

#define VXEV01 0x00000001
#define VXEV02 0x00000002
#define VXEV03 0x00000004
#define VXEV04 0x00000008
#define VXEV05 0x00000010
#define VXEV06 0x00000020
#define VXEV07 0x00000040
#define VXEV08 0x00000080
#define VXEV09 0x00000100
#define VXEV10 0x00000200
#define VXEV11 0x00000400
#define VXEV12 0x00000800
#define VXEV13 0x00001000
#define VXEV14 0x00002000
#define VXEV15 0x00004000
#define VXEV16 0x00008000
#define VXEV17 0x00010000
#define VXEV18 0x00020000
#define VXEV19 0x00040000
#define VXEV20 0x00080000
#define VXEV21 0x00100000
#define VXEV22 0x00200000
#define VXEV23 0x00400000
#define VXEV24 0x00800000

#define VXEV_USER_MASK 0x00ffffff

#ifndef	_ASMLANGUAGE

/* function declaration */

typedef UINT32 _Vx_event_t;

extern STATUS eventSend (TASK_ID taskId, _Vx_event_t events);
extern STATUS eventReceive (
			    _Vx_event_t events,
			    UINT8 options,
			    _Vx_ticks_t timeout,
			    UINT32 *eventsReceived
			   );
extern STATUS eventClear (void);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCeventLibh */

