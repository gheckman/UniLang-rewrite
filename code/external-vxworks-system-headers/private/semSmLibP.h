/* semSmLibP.h - private shared semaphore library header file */

/*
 * Copyright (c) 1992-1993, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01f,15sep10,swg  remove VxMP APIs for these APIs will be published
          And change the typedef for shared semaphore(WIND00145226)
01e,09sep10,jpb  Removed unused function pointer semSmInfoRtn.
01d,29apr10,pad  Moved extern C statement after include statements.
01c,29jan93,pme  added little endian support
01b,22sep92,rrr  added support for c++
01a,19jul92,pme  extracted from semSmLib v1c.
*/

#ifndef __INCsemSmLibPh
#define __INCsemSmLibPh

#include <vxWorks.h>
#include <vwModNum.h>
#include <semSmLib.h>
#include <smDllLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

#define SEM_TYPE_SM_BINARY      0x0     /* shared binary semaphore */
#define SEM_TYPE_SM_COUNTING    0x1     /* shared counting semaphore */

#if (defined (CPU_FAMILY) && (CPU_FAMILY==I960) && (defined __GNUC__))
#pragma align 1                 /* tell gcc960 not to optimize alignments */
#endif  /* CPU_FAMILY==I960 */

typedef struct  sm_semaphore    /* SHARED MEMORY SEMAPHORE */
    {
    UINT32      verify;         /* 0x00: semaphore verification */
    UINT32      objType;        /* 0x04: semaphore type */
    UINT32      lock;           /* 0x08: semaphore spin lock */
    SM_DL_LIST  smPendQ;        /* 0x0c: semaphore pend Queue */
    union
        {
        UINT32           flag;  /* 0x14: current state */
        UINT32           count; /* 0x14: semaphore counter */
        } state;

    } SM_SEMAPHORE;

#if (defined (CPU_FAMILY) && (CPU_FAMILY==I960) && (defined __GNUC__))
#pragma align 0                 /* turn off alignment requirement */
#endif  /* CPU_FAMILY==I960 */

/* variable declarations */

extern FUNCPTR semSmShowRtn;		/* shared semaphore show routine ptr */

/* function declarations */

extern void   semSmLibInit (void);
extern STATUS semSmBInit (SM_SEMAPHORE * pSem, int options,
                          SEM_B_STATE initialState);
extern STATUS semSmCInit (SM_SEMAPHORE * pSem, int options, int initialCount);

#ifdef __cplusplus
}
#endif

#endif /* __INCsemSmLibPh */
