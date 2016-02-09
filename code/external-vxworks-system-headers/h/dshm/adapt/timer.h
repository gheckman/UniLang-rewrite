/* timer.h - DSHM adaptation layer: timer functionalities */

/*
 * Copyright (c) 2006-2007, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01g,15jul10,gjj  deprecated dshm technolgy from vxworks.
01f,29apr10,pad  Moved extern C statement after include statements.
01e,02jul07,bwa  updated dshmSm.h path
01d,08apr07,bwa  modified to sleep instead of busy wait; added extern "C".
01c,21dec06,bwa  changed beat units to ms; added usage of sysMsDelay() for
                 usage before tasks are up.
01b,29jul06,bwa  updated heartbeat timer definitions.
01a,05jul06,bwa  written.
*/

#ifndef __INCdshmadapttimerh
#define __INCdshmadapttimerh

#include <dshm/dshm.h>
#include <dshm/util/dshmSm.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int sysClkRateGet (void);

DSHM_TIMER_ID dshmAdaptHeartbeatStart (DSHM_SM_INFO * const pInfo) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
    
#define DSHM_BEAT_PERIOD 100		/* in ms */ /* TODO: config param */

#define DSHM_DELAY(ms) taskDelay((ms * CLOCKS_PER_SEC) / 1000)

#define DSHM_SM_HEARTBEAT_START(pInfo) dshmAdaptHeartbeatStart(pInfo);
#define DSHM_SM_HEARTBEAT_STOP(pInfo)  wdDelete(pInfo->heart);

#ifdef __cplusplus
}
#endif

#endif	/* __INCdshmadapttimerh */

