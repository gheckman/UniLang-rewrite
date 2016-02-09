/* pwrCpuLib.h - CPU power library manager header file */

/*
 * Copyright (c) 2011, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01d,12jan12,jlv  WIND00325775 - Add CPU Pwr Mgr event callbacks
01c,22aug11,j_l  WIND00255353: Tickless mode/IA PPM integration.
01b,01aug11,jlv  Update extern statement
01a,15jul11,jlv  created
*/

#ifndef __INCpwrCpuLibh
#define __INCpwrCpuLibh

#include <drv/erf/erfLib.h>
#include <hwif/pwr/pwrPolicyLib.h>

#ifdef __cplusplus
extern "C" {
#endif

IMPORT UINT32 pwrCpuPStateSet(UINT32 cpuIndex, UINT32 cpuPState);
IMPORT UINT32 pwrCpuPStateGet(UINT32 cpuIndex);

IMPORT STATUS pwrCpuEventHandlerRegister
    (
    pwrEventType 	    eventType,
    erfHandlerPrototype *pEventHandler,
    void 		        *pUserData
    );

IMPORT STATUS pwrCpuEventHandlerUnregister
    (
    pwrEventType 	    eventType,
    erfHandlerPrototype *pEventHandler,
    void 		        *pUserData
    );

#if !defined(__RTP__)  /* define only if not RTP */

/*
 * State change event notification objects
 * These events are available for registration through erfLib.
 */

IMPORT UINT16 pwrCpuEventCategory;
IMPORT UINT16 pwrCpuPstateChange;  /* P-state change event */
IMPORT UINT16 pwrCpuC1stateChange; /* C1-state change event */
IMPORT UINT16 pwrCpuC3stateChange; /* C3-state change event */

#endif /* define only if not RTP */

#ifdef __cplusplus
}
#endif

#endif /* __INCpwrCpuLibh */
