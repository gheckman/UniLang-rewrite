/* dshmPow2.h - power of two utilities */

/*
 * Copyright (c) 2006-2007, 2010 Wind River Systems, Inc.
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
01a,24aug06,bwa  written.
*/

#ifndef __INCdshmPow2h
#define __INCdshmPow2h

#include <dshm/dshm.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DSHM_POW2_SMALLER	-1
#define DSHM_POW2_LARGER	1
#define DSHM_POW2_ANY		0

int dshmPow2Verify ( const uint32_t value )
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
uint32_t dshmPow2ClosestFind ( const uint32_t value, const int condition )
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");

#ifdef __cplusplus
}
#endif

#endif	/* __INCdshmPow2h */

