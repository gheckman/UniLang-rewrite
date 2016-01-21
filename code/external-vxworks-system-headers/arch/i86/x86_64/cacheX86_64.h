/* cacheX86_64Lib.h - x86_64 cache library header file */

/*
 * Copyright 2009, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01d,29apr10,pad  Moved extern C statement after include statements.
01c,18mar09,jb   Add override for 64-bit calls
01b,13feb09,jb   Fix cache type conflict
01a,27jan09,jb   Created from 32-bit version 01f
*/

#ifndef __INCcacheX86_64Libh
#define __INCcacheX86_64Libh

#include "vxWorks.h"

#ifdef __cplusplus
extern "C" {
#endif


#define	CLFLUSH_DEF_BYTES	64	/* def bytes flushed by CLFLUSH */
#define	CLFLUSH_MAX_BYTES	255	/* max bytes flushed with CLFLUSH */

    /* Override cache calls */
#define cacheI86Reset cacheX86_64Reset
#define cacheI86Enable cacheX86_64Enable
#define cacheI86Disable cacheX86_64Disable
#define cacheI86Lock cacheX86_64Lock
#define cacheI86Unlock cacheX86_64Unlock
#define cacheI86Clear cacheX86_64Clear
#define cacheI86Flush cacheX86_64Flush

#define cachePen4Reset cacheX86_64Reset
#define cachePen4Enable cacheX86_64Enable
#define cachePen4Disable cacheX86_64Disable
#define cachePen4Lock cacheX86_64Lock
#define cachePen4Unlock cacheX86_64Unlock
#define cachePen4Clear cacheX86_64Clear
#define cachePen4Flush cacheX86_64Flush

#ifndef	_ASMLANGUAGE

#if defined(__STDC__) || defined(__cplusplus)

extern void cacheX86_64Reset (void);
extern void cacheX86_64Enable (void);
extern void cacheX86_64Disable (void);
extern void cacheX86_64Lock (void);
extern void cacheX86_64Unlock (void);
extern void cacheX86_64Clear (CACHE_TYPE cache, void * address, size_t bytes);
extern void cacheX86_64Flush (CACHE_TYPE cache, void * address, size_t bytes);

#else

extern void cacheX86_64Reset ();
extern void cacheX86_64Enable ();
extern void cacheX86_64Disable ();
extern void cacheX86_64Lock ();
extern void cacheX86_64Unlock ();
extern void cacheX86_64Clear ();
extern void cacheX86_64Flush ();

#endif /* __STDC__ */

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCcacheX86_64Libh */
