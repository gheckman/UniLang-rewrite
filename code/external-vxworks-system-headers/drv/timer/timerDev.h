/* timerDev.h - Generic Timer header */

/*
 * Copyright (c) 1992, 1996, 2003, 2009-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01i,19aug11,dee  WIND00278138 - 64-bit timestamp support
01h,07oct10,rec  change sysOneShotDisable and sysOneShotEnable prototypes
01g,17mar09,h_k  updated for LP64 support.
01f,06nov03,rec  add sysOneShotEnable and sysOneShotDisable prototypes
01e,27aug03,rec  add power management prototypes
01d,06aug96,dat  merged in timestamp support
01c,22sep92,rrr  added support for c++
01b,07jul92,ccc  change name to timerDev.h
01a,22jun92,ccc  created.
*/

/*
DESCRIPTION
This file contains header information for generic timer routines.
*/

#ifndef __INCtimerDevh
#define __INCtimerDevh

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

#ifndef	_ASMLANGUAGE

IMPORT	STATUS	sysClkConnect (FUNCPTR routine, _Vx_usr_arg_t arg);
IMPORT	void	sysClkDisable (void);
IMPORT	void	sysClkEnable (void);
IMPORT	int	sysClkRateGet (void);
IMPORT	STATUS	sysClkRateSet (int ticksPerSecond);
IMPORT	STATUS	sysAuxClkConnect (FUNCPTR routine, _Vx_usr_arg_t arg);
IMPORT	void	sysAuxClkDisable (void);
IMPORT	void	sysAuxClkEnable (void);
IMPORT	int	sysAuxClkRateGet (void);
IMPORT	STATUS	sysAuxClkRateSet (int ticksPerSecond);
IMPORT	STATUS	sysTimestampConnect (FUNCPTR routine, _Vx_usr_arg_t arg);
IMPORT	STATUS	sysTimestampEnable (void);
IMPORT	STATUS	sysTimestampDisable (void);
IMPORT	UINT32	sysTimestampFreq (void);
IMPORT	UINT32	sysTimestampPeriod (void);
IMPORT	UINT32	sysTimestamp (void);
IMPORT	UINT32	sysTimestampLock (void);
IMPORT	UINT64	sysTimestamp64Freq (void);
IMPORT	UINT64	sysTimestamp64Period (void);
IMPORT  STATUS	sysTimestamp64 (UINT64 * counterVal);
IMPORT  STATUS	sysTimestamp64Lock (UINT64 * counterVal);
IMPORT	void    sysOneShotEnable (UINT32 nTicks);
IMPORT	UINT32  sysOneShotDisable (void);
IMPORT  void    sysOneShotInit (void);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCtimerDevh */
