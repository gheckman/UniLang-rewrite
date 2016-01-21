/* passFsLib.h - pass-through file system library header */

/*
 * Copyright (c) 1984-1993,2003-2005,2007 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this
 * software may be licensed only pursuant to the terms of an applicable
 * Wind River license agreement.
 */

/*
modification history
--------------------
01j,30jul07,elp  moved type definitions to passFsLib.c (CQ:WIND101721).
01i,01jun07,elp  renamed readCache field, added mutual exclusion semaphore.
01h,15sep05,elp  added passFs 64 bits operations (SPR #111187).
01g,11feb05,dbt  Fixed cache support (SPR #106354).
01f,13sep04,jmp  made passFs cache configurable.
01e,09sep04,jmp  added flags and mode to PASS_FILE_DESC (SPR #97903).
01d,02apr04,jeg  Updated PASS_FILE_DESC fd field name.
01c,18mar03,jeg  removed passFs flags and conversion macro.
01b,05mar03,jeg  add several Unix file specific definitions
01a,05jun93,gae  written.
*/

#ifndef __INCpassFsLibh
#define __INCpassFsLibh

#ifdef __cplusplus
extern "C" {
#endif

/* Function declarations */

extern void *passFsDevInit (char *devName);
extern STATUS passFsInit (int passfs, BOOL cacheEnable);
	      
#ifdef __cplusplus
}
#endif

#endif /* __INCpassFsLibh */
