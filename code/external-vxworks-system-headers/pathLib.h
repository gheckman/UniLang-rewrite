/* pathLib.h - path library header file */

/* Copyright 1984-2003, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01l,29apr10,pad  Moved extern C statement after include statements.
01k,28jul03,dat  strict const char * prototypes, removed non-ANSI prototypes
01j,22sep92,rrr  added support for c++
01i,04jul92,jcf  cleaned up.
01h,26may92,rrr  the tree shuffle
01g,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed VOID to void
		  -changed copyright notice
01f,05oct90,dnw  removed private functions.
01e,05oct90,shl  added ANSI function prototypes.
                 made #endif ANSI style.
                 added copyright notice.
01d,30jul90,dnw  added pathLastNamePtr() and changed pathLastName() to void.
01c,01may90,llk  changed pathBuild() and pathCat() to return STATUS.
01b,01apr90,llk  deleted pathArrayFree().
01a,06jul89,llk  written.
*/

#ifndef __INCpathLibh
#define __INCpathLibh

#include "vwModNum.h"

#ifdef __cplusplus
extern "C" {
#endif


/* function declarations */

extern STATUS 	pathBuild (const char ** nameArray, char ** nameArrayEnd,
			   char *destString);
extern STATUS 	pathCat (const char *dirName, const char *fileName,
			   char *result);
extern char *	pathLastNamePtr (const char *pathName);
extern void 	pathCondense (char *pathName);
extern void 	pathLastName (char *pathName, char ** pLastName);
extern void 	pathParse (const char *longName, char ** nameArray,
				char *nameBuf);
extern void 	pathSplit (const char *fullFileName, char *dirName,
				char *fileName);

#ifdef __cplusplus
}
#endif

#endif /* __INCpathLibh */
