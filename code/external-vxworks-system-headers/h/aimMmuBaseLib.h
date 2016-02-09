/* aimMmuBaseLib.h - Base of the MMU Architecture Independent Manager */

/* Copyright 1984-2004, 2010 Wind River Systems, Inc.  */

/*
modification history
--------------------
01c,29apr10,pad  Moved extern C statement after include statements.
01b,31aug04,dtr  Add new attribute available for tlb locking.
01a,07jun04,sru  written
*/

#ifndef __INCaimMmuBaseLibh
#define __INCaimMmuBaseLibh

#include "vxWorks.h"

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

/*
 * MMU_ARCH_LIB_ATTRS is a data structure that is allocated by the AIM
 * base library.  It is filled in with MMU-specific attributes during
 * the initialization of the architecture-dependent MMU library.  From
 * that point forward, the data structure is used by the AIM for its
 * internal management.
 */

typedef struct
    {
    /* fields filled in by the AD-MMU */

    UINT pageSizeMask;
    UINT lockSizeMask;
    UINT contextMin;		/* inclusive */
    UINT contextMax;		/* inclusive */
    UINT pteSize;		/* units are bytes */
    UINT contextTblAlign;
    UINT regionTblNumEntries;
    UINT pageTblNumEntries;
    UINT tlbNumEntries;		/* sum of hardware TLB resources */
    UINT tlbLockNumEntries;     /* sum of hardware TLB resources available 
				   for locking */
    UINT sizeOfRegionTbl;
    UINT sizeOfPageTbl;
    UINT sizeOfContextTbl;

    /* fields filled in by the AIM during initialization */

    UINT pageSize;
    UINT blockSize;
    UINT regionShift;		/* rightward bitshift to create region idx */
    UINT regionMask;		/* post-shift mask of region idx */
    UINT pageShift;		/* rightward bitshift to create page idx */
    UINT pageMask;		/* post-shift mask of page idx */

    } MMU_ARCH_LIB_ATTRS;

/* externs */

extern STATUS aimMmuBaseLibInit ();
extern MMU_ARCH_LIB_ATTRS mmuArchLibAttrs;

#ifdef __cplusplus
}
#endif

#endif /* __INCaimMmuBaseLibh */
