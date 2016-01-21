/* ixp400Timer.h - ixp400 processor timer library */

/*
Copyright (c) 2002-2004 Wind River Systems, Inc.  All rights reserved.
Certain portions of these files may be copyright (c) 2002-2004 Intel
Corporation.
*/

#include "copyright_wrs.h" 

/*
modification history
--------------------
01e,24aug05,m_h  vxWorks 6.1 support
01d,20dec04,pai  Updated copyright notice.
01c,09jul03,m_h  multiple callouts from auxClk
01b,27feb03,jb3  add C++ protection
01a,05jun02,jb  initial version...
*/

#ifndef INCixp400Timerh
#define INCixp400Timerh

#ifdef __cplusplus
extern "C" {
#endif

#define SYS_CLK_RATE_MIN (10)	  /* Minimum rate at which the system clock can run */
#define SYS_CLK_RATE_MAX (1000)	  /* 1000 ticks, Maximum rate at which the system clock can run */

/* Do not actually have an auxiliary clock */
#define AUX_CLK_RATE_MIN (10)	  /* Minimum rate at which the auxiliary clock can run */
#define AUX_CLK_RATE_MAX (1000)	  /* 1000 ticks, Maximum rate at which the auxiliary clock can run */


/* auxClk functionality used within this BSP */
STATUS ixpAuxClkConnect (FUNCPTR routine, int arg);
void ixpAuxClkDisconnect (void);
void ixpAuxClkDisable (void);
void ixpAuxClkEnable (void);
int ixpAuxClkRateGet (void);
STATUS ixpAuxClkRateSet (int ticksPerSecond);


/* 50MHz emulation mode for ixp465 */
BOOL ixpTimer20NsEmulSet(BOOL useEmul);
BOOL ixpTimer20NsEmulGet(void);
BOOL ixpAuxTimer20NsEmulSet(BOOL useEmul);
BOOL ixpAuxTimer20NsEmulGet(void);

void	ixp400WatchDogInt (void);
STATUS	ixp400WatchDogConnect(FUNCPTR routine, int arg);		  
STATUS	ixp400WatchDogEnable(void);
STATUS	ixp400WatchDogDisable (void);
UINT32	ixp400WatchdogPeriod (void);
STATUS	ixp400WatchDogPeriodSet(UINT32 counts);
UINT32	ixp400WatchDogFreq (void);
void	ixp400WatchDogService(void);

/* Assembly specific defs */
#ifndef _ASMLANGUAGE
#endif


#ifdef __cplusplus
}
#endif


#endif	/* INCixp400Timer.h */

