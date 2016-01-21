/* virtualDiskLibP.h - private VxSim virtual disk header file */

/* Copyright 2003 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,30jul03,jeg  written.
*/

#ifndef __INCvirtualDiskLibPh
#define __INCvirtualDiskLibPh

#ifdef __cplusplus
extern "C" {
#endif

/* forwared declarations */

BLK_DEV * virtualDiskOldCreate (char * hostFile, int bytesPerBlk,
	int blksPerTrack, int nBlocks);

#ifdef __cplusplus
}
#endif

#endif /* __INCvirtualDiskLibPh */

