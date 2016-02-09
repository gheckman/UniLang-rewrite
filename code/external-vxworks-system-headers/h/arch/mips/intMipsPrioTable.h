/* intMipsPrioTable.h - MIPS interrupt priority table */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01a,19mar10,pch  written
*/

#ifndef __INCintMipsPrioTableh
#define __INCintMipsPrioTableh

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Interrupt priority table, defined in BSP and referenced in excALib.s and
 * vxbMipsIntCtlrIsr.c.  The typedef should be in the arch because BSPs are
 * not free to change it, but it is defined in a separate .h file to avoid
 * breaking the many MIPS BSPs that already contain the typedef.
 */

typedef struct
    {
    ULONG	intCause;	/* CAUSE IP bit of int source		     */
    ULONG	bsrTableOffset;	/* index into BSR table (aka vecNum),	     */
				/* or address of demux function		     */
    ULONG	intMask;	/* interrupt mask			     */
    ULONG	demux;		/* arg passed to demux fcn, NULL => no demux */
    } PRIO_TABLE;

#ifdef __cplusplus
}
#endif

#endif /* __INCintMipsPrioTableh */
