/* dshmMem.h - local shared memory allocator/deallocator */

/*
 * Copyright (c) 2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,15jul10,gjj  deprecated the DSHM technology and added deprecation macros.
01b,29apr10,pad  Moved extern C statement after include statements.
01a,17jul06,bwa  written.
*/

#ifndef __INCdshmMemh
#define __INCdshmMemh

#include <dshm/dshm.h>

#ifdef __cplusplus
extern "C" {
#endif

int dshmMemSetup (void * const pSmPool, const int size) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
void * dshmMemAlloc (const int handle, int * const pSize, const int min,
			const unsigned int align)
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
STATUS dshmMemFree (const int handle, void * const pAlloc)
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");

#ifdef __cplusplus
}
#endif

#endif	/* __INCdshmMemh */
 
