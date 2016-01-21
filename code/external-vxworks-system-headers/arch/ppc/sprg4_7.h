/* sprg4_7.h - definitions of SPRG4 - SPRG7 for recent PPC60x variants */

/* Copyright 2006 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,28feb06,pch  written, from ppc5200.h and ppc405.h */

/*
This file contains definitions for SPRG4 - SPRG7, which are
provided by some (but not all) variants of PPC603 and PPC604.
(Similar functionality is also present in PPC4xx and MPC85xx,
but they use different definitions to account for different
handling of read vs write access.)
*/

#ifndef	__INCsprg4_7
#define	__INCsprg4_7

#ifdef	__cplusplus
extern "C" {
#endif

#define	SPRG4	276	/* 0x114 */
#define	SPRG5	277	/* 0x115 */
#define	SPRG6	278	/* 0x116 */
#define	SPRG7	279	/* 0x117 */

#ifdef	__cplusplus
}
#endif

#endif	/* __INCsprg4_7 */
