/* cavFau.h - FAU data types, macros and addresses */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01d,09nov10,d_c  Encapsulate computation of Tx buffer chunk addresses
01c,05oct10,d_c  Remove extra comma from enum
01b,13aug10,d_c  Add interface elements to support vxbOcteonEnd.c
01a,06aug10,d_c  written
*/

#ifndef __INCcavFauh
#define __INCcavFauh


#ifdef	__cplusplus
extern "C" {
#endif

/* defines */

/* typedefs */

/* functions */

IMPORT int64_t cavFauTxChunkAddrGet
    (
    int octQueue,		/* Base PKO queue number */
    int forwarderNum		/* Forwarder number */
    );

#ifdef	__cplusplus
}
#endif
  
#endif /* __INCcavFauh */
