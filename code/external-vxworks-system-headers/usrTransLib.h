/* usrTransLib.h - Access library for transCbio */

/*
 * Copyright 2004 - 2005 - Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,26aug05,jlk  modified usrTransCommit to take a path instead of an XBD
01b,20jun05,act  transaction CBIO device is now a transaction XBD
01a,05oct04,rfr  Removed unnecessary parameter "blkshift" from
                 usrFormatTrans()
*/

#ifndef __INCusrTransLibh
#define __INCusrTransLibh

#include <cbioLib.h>

#ifdef __cplusplus
extern "C" {
#endif

extern STATUS usrFormatTrans
	(
	char *dev,  /* Reference to the cbioTrans we are going to format */
	int overhead,     /* Maximum size of uncommitted transactions */
	int type          /* 0 = FORMAT_REGULAR, 1 = FORMAT_TFFS */
	);

extern STATUS usrTransCommit
	(
	char *volume      /* path for the trans XBD to commit */
	);

extern STATUS usrTransCommitFd
	(
	int fd            /* File descriptor referencing the F/S to commit */  
	);

#ifdef __cplusplus
}
#endif
#endif
