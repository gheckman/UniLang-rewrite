/* dsiUtilLib.h -  DSI stack utilities header */

/* Copyright 2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,17aug04,dlk  written.
*/

#ifndef __INCdsiUtilLibh
#define __INCdsiUtilLibh

#include <vxWorks.h>
#include <semLib.h>

#ifdef __cplusplus
extern "C" {
#endif

extern STATUS   dsiLockInit (void);
extern int      dsiLock (void);
extern void     dsiUnlock (int);

extern STATUS   dsiTsleep (SEM_ID semId, int timeo_val);

#ifdef __cplusplus
}
#endif

#endif    /* __INCdsiUtilLibh */

