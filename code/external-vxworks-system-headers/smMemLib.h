/* smMemLib.h - shared memory management library header file */

/* Copyright 1984-1992, 2010 Wind River Systems, Inc. */
/*
modification history
--------------------
01j,15sep10,swg  change the parameter type of VXMP dedicated APIs:
           from SM_XXX_ID to XXX_ID(WIND00145226)
01i,23jul10,swg  Add VxMP dedicated APIs
01h,29apr10,pad  Moved extern C statement after include statements.
01g,29jan93,pme  made smMemAddToPool() return STATUS.
01f,15oct92,rrr  silenced warnings
01e,29sep92,pme  changed user callable routine names 
                 moved smMemPartShow prototype to private/smMemPartLibP.h
01d,22sep92,rrr  added support for c++
01c,28jul92,pme  made smMemPartCreate return PART_ID instead of SM_PART_ID.
01b,28jul92,pme  removed unnecessary includes.
01a,19jul92,pme  written from 03f memLib.h
*/

#ifndef __INCsmMemLibh
#define __INCsmMemLibh

#include "memLib.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sm_obj_partition * SM_PART_ID;

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern PART_ID 	  memPartSmCreate (char * pPool, unsigned poolSize);
extern STATUS     smMemFree (void * ptr);
extern int        smMemFindMax (void);
extern void *     smMemMalloc (unsigned nBytes);
extern void *     smMemCalloc (int elemNum, int elemSize);
extern void *     smMemRealloc (void * pBlock, unsigned newSize);
extern STATUS     smMemAddToPool (char * pPool, unsigned poolSize);
extern STATUS     smMemOptionsSet (unsigned options);
extern void       smMemShowInit (void);
extern void       smMemShow (int type);
extern STATUS     smMemPartAddToPool(PART_ID volatile partIdIn, char * pPool, unsigned poolSize);
extern STATUS     smMemPartFree(PART_ID volatile partIdIn, char * pBlock);
extern void *     smMemPartAlloc(PART_ID partIdIn, unsigned nBytes);
extern STATUS     smMemPartOptionsSet(PART_ID volatile partIdIn, unsigned options);
extern int        smMemPartFindMax(PART_ID volatile partIdIn);
extern void *     smMemPartRealloc(PART_ID volatile partIdIn, char * pBlock, unsigned nBytes);
extern STATUS     smMemPartShow (PART_ID PartIdIn, int type);
#else	/* __STDC__ */

extern PART_ID    memPartSmCreate ();
extern STATUS     smMemFree ();
extern int        smMemFindMax ();
extern void *     smMemMalloc ();
extern void *     smMemCalloc ();
extern void *     smMemRealloc ();
extern STATUS     smMemAddToPool ();
extern STATUS     smMemOptionsSet ();
extern void       smMemShowInit ();
extern void       smMemShow ();
extern STATUS     smMemPartAddToPool();
extern STATUS     smMemPartFree();
extern void *     smMemPartAlloc();
extern STATUS     smMemPartOptionsSet();
extern int        smMemPartFindMax();
extern void *     smMemPartRealloc();
extern STATUS     smMemPartShow ();

#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCsmMemLibh */
