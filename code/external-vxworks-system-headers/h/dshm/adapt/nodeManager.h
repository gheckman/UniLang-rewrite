/* nodeManager.h - dSHM node manager service functionalities */

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
01d,15jul10,gjj  deprecated the DSHM technology and added deprecation macros.
01c,06apr07,bwa  updated dshmAdaptPeerFind().
01b,29jul06,bwa  renamed routines.
01a,05jul06,bwa  written.
*/

#ifndef __INCnodeManagerh
#define __INCnodeManagerh

#ifdef __cplusplus
extern "C" {
#endif

void dshmAdaptPeerFind ( const DSHM_HW_ID id, const uint16_t addr )
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
void dshmAdaptPeerQuit ( const DSHM_HW_ID id, const uint16_t addr )
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");

#ifdef __cplusplus
}
#endif

#endif	/* __INCnodeManagerh */
 
