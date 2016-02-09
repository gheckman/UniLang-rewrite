/* m5200GPTimer.h - Motorola MPC5200 General Purpose Timer (GPT) driver */

/* Copyright 2000-2003 Wind River Systems, Inc. */
#include "copyright_wrs.h"

/*
modification history
--------------------
01a,06dec03,pdr   created

*/

#ifndef __INCm5200GPTimerh
#define __INCm5200GPTimerh

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* routines */

/* TMU3 routines */
IMPORT STATUS   sysUserClkConnect       ( FUNCPTR routine, int arg );
IMPORT void     sysUserClkDisable       ( void );
IMPORT void     sysUserClkEnable        ( void );
IMPORT int      sysUserClkRateGet       ( void );
IMPORT STATUS   sysUserClkRateSet       ( int ticksPerSecond );
IMPORT BOOL     sysUserClkIsRunning     ( void );

/* TMU4 routines */
IMPORT STATUS   sysUserAuxClkConnect    ( FUNCPTR routine, int arg );
IMPORT void     sysUserAuxClkDisable    ( void );
IMPORT void     sysUserAuxClkEnable     ( void );
IMPORT int      sysUserAuxClkRateGet    ( void );
IMPORT STATUS   sysUserAuxClkRateSet    ( int ticksPerSecond );
IMPORT BOOL     sysUserAuxClkIsRunning  ( void );


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __INCm5200GPTimerh */











										
												














































