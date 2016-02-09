/* cavClock.h -  Cavium Clock Support Routines */
/*
 * Copyright 2010, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01c,feb0912,x_f  import cavIOClockRateGet() for CN68XX
01b,31aug10,rlg  update with new prototype for cn63xx
01a,12aug10,rlg  Written
*/

/*
DESCRIPTION

This file declares macros, typedefs, and prototypes for general,
non-device-specific access routines for Cavium hardware.

*/

#ifndef __INCcavClockh
#define __INCcavClockh

#ifdef __cplusplus
extern "C" {
#endif


/*
 * prototypes
 */

IMPORT void cavCyclesDelay(UINT64);
IMPORT void cavWait(UINT64);
IMPORT UINT cavCpuClockRateGet(void);
IMPORT UINT cavIOClockRateGet(void);
IMPORT void cavUDelay(UINT64);
IMPORT UINT cavCopClockRateGet (void);


#ifdef __cplusplus
}
#endif
#endif /* __INCcavClockh */


