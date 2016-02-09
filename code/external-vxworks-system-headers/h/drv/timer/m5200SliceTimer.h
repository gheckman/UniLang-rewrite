/* m5200SliceTimer.h - PowerPC Slice Timer (SLT) header */

/* Copyright 1984-2003 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,15sep03,pdr  created.
*/

/*
DESCRIPTION
This file contains header information for PowerPC Slice timer routines.
*/

#ifndef __INCm5200SliceTimerh
#define __INCm5200SliceTimerh

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

#ifndef	_ASMLANGUAGE
#if defined(__STDC__) || defined(__cplusplus)

IMPORT	STATUS	sysAuxClkConnect (FUNCPTR routine, int arg);
IMPORT	void	sysAuxClkDisable (void);
IMPORT	void	sysAuxClkEnable (void);
IMPORT	int	sysAuxClkRateGet (void);
IMPORT	STATUS	sysAuxClkRateSet (int ticksPerSecond);

#else	/* __STDC__ */

IMPORT	STATUS	sysAuxClkConnect ();
IMPORT	void	sysAuxClkDisable ();
IMPORT	void	sysAuxClkEnable ();
IMPORT	int	sysAuxClkRateGet ();
IMPORT	STATUS	sysAuxClkRateSet ();

#endif	/* __STDC__ */

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCm5200SliceTimerh */
