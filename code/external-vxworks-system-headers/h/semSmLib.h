/* semSmLib.h - shared semaphore library header file */

/* Copyright 1984-1992, 2010 Wind River Systems, Inc. */
/*
modification history
--------------------
01g,15sep10,swg  change the parameter type of VXMP dedicated APIs:
           from SM_XXX_ID to XXX_ID(WIND00145226)
01f,23jul10,swg  Add VxMP dedicated APIs.
01e,29apr10,pad  Moved extern C statement after include statements.
01d,29sep92,pme  changed semSm[BC]Create to sem[BC]SmCreate.
01c,22sep92,rrr  added support for c++
01b,28jul92,pme  added #include "semLib.h".
01a,19jul92,pme  written.
*/

#ifndef __INCsemSmLibh
#define __INCsemSmLibh

#include "vxWorks.h"
#include "semLib.h"
#include "smDllLib.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct sm_semaphore * SM_SEM_ID;

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern    SEM_ID       semBSmCreate (int options, SEM_B_STATE initialState);
extern    SEM_ID       semCSmCreate (int options, int initialCount);
extern    void         semSmShowInit ();
extern    STATUS       semSmGive(SEM_ID smSemIdIn);
extern    STATUS       semSmTake(SEM_ID smSemIdIn, int timeout);
extern    STATUS       semSmFlush(SEM_ID smSemIdIn);
extern    int          semSmShow(SEM_ID smSemIdIn, int level);
extern    int          semSmInfo(SEM_ID smSemIdIn, int idList[], int maxTasks);

#else   /* __STDC__ */
extern    SEM_ID       semBSmCreate ();
extern    SEM_ID       semCSmCreate ();
extern    void         semSmShowInit ();
extern    STATUS       semSmGive();
extern    STATUS       semSmTake();
extern    STATUS       semSmFlush();
extern    int          semSmShow();
extern    int          semSmInfo();
#endif	/* __STDC__ */

#ifdef __cplusplus
}

#endif
#endif /* __INCsemSmLibh */
