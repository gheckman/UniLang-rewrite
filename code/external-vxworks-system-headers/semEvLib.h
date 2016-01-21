/* semEvLib.h - semaphore events library header file */

/* Copyright 2001, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,29apr10,pad  Moved extern C statement after include statements.
01a,20sep01.bwa  Initial creation.
*/

#ifndef __INCsemEvLibh
#define __INCsemEvLibh

#include "vxWorks.h"
#include "semLib.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	_ASMLANGUAGE

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern STATUS 	semEvStart (SEM_ID semId, UINT32 events, UINT8 options);
extern STATUS	semEvStop  (SEM_ID semId);

#else /* __STDC__ */

extern STATUS 	semEvStart ();
extern STATUS	semEvStop  ();

#endif /* __STDC__ */

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCsemEvLibh */

