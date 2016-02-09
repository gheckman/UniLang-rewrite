/* pgPoolPhysLibP.h - physical page pool object library header file */

/* 
 * Copyright (c) 2003-2006, 2009-2010 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01h,29apr10,pad  Moved extern C statement after include statements.
01g,18sep09,zl   use fully qualified function pointer for pgPoolPhysRangeEach().
01f,17jun09,zl   updated for LP64 build
01e,07jul06,zl   updated the pgPoolPhysAvailAlloc() arguments.
01d,21jul05,zl   updated pgPoolLib API
01c,13sep04,zl   converted to private header file
01b,30nov03,yp   adding error code for address out of range
01a,08jul03,yp   written.
*/

#ifndef __INCpgPoolPhysLibPh
#define __INCpgPoolPhysLibPh

/* includes */

#include <vxWorks.h>
#include <private/pgPoolLibP.h>

#ifdef __cplusplus
extern "C" {
#endif


#ifndef	_ASMLANGUAGE

/* function declarations */

extern STATUS	 pgPoolPhysLibInit (void);
extern STATUS	 pgPoolPhysAddToPool (PAGE_POOL_ID poolId, PHYS_ADDR addr, 
				      size_t numPages, UINT state);
extern STATUS	 pgPoolPhysRemoveFromPool (PAGE_POOL_ID poolId, PHYS_ADDR addr,
					   size_t numPages);
extern PHYS_ADDR pgPoolPhysAlloc (PAGE_POOL_ID poolId, size_t numPages);
extern PHYS_ADDR pgPoolPhysAlignedAlloc (PAGE_POOL_ID poolId, size_t numPages,
					 size_t alignment);
extern PHYS_ADDR pgPoolPhysAllocAt (PAGE_POOL_ID poolId, PHYS_ADDR startAddr,
				    size_t numPages);
extern PHYS_ADDR pgPoolPhysAvailAlloc (PAGE_POOL_ID poolId, size_t numPagesReq,
				       size_t * pNumPagesGot);
extern STATUS	 pgPoolPhysFree (PAGE_POOL_ID poolId, PHYS_ADDR startAddr,
				 size_t numPages);
extern BOOL	 pgPoolPhysRangeIsFree (PAGE_POOL_ID poolId, PHYS_ADDR startAddr,
				        size_t numPages);
extern BOOL	 pgPoolPhysRangeIsAllocated (PAGE_POOL_ID poolId,
					     PHYS_ADDR startAddr,
					     size_t numPages);
extern BOOL	 pgPoolPhysRangeVerify (PAGE_POOL_ID poolId,
					PHYS_ADDR pageAddr, size_t numPages);
extern STATUS	 pgPoolPhysNextFreeGet (PAGE_POOL_ID poolId, PHYS_ADDR refAddr,
					PHYS_ADDR * pFreeAddr, 
					size_t * pNumPages);
extern STATUS	 pgPoolPhysRangeEach (PAGE_POOL_ID poolId, UINT state,
				      STATUS (*usrRtn) 
					(
					PHYS_ADDR physAddr, 
					size_t numPages, 
					UINT state, 
					void * pArg
					), 
				      void * pArg);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCpgPoolPhysLibPh */
