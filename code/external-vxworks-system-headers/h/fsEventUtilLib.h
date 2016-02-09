/* fsEventUtilLib.h - header file for the fsEventUtilLib component */

/* 
* Copyright (c) 2005 Wind River Systems, Inc. 
* 
* The right to copy, distribute, modify or otherwise make use 
* of this software may be licensed only pursuant to the terms 
* of an applicable Wind River license agreement. 
*/

/*
modification history
--------------------
01c,11jul05,jlk  fixed typo in fsEventUtilLibInit() prototype
01b,23jun05,jlk  renamed file
01a,22jun05,jlk  written
*/

#ifndef __INCfsEventUtilLibh
#define __INCfsEventUtilLibh

typedef struct pathWaitStruct
    {
    char * path;
    SEM_ID waitSem;
    } FS_PATH_WAIT_STRUCT;


#ifdef __cplusplus
extern "C" {
#endif
              
extern STATUS fsEventUtilLibInit (void);
extern STATUS fsPathAddedEventSetup (FS_PATH_WAIT_STRUCT *, char *);
extern void   fsPathAddedEventRaise (char *);
extern STATUS fsWaitForPath (FS_PATH_WAIT_STRUCT *);

#ifdef __cplusplus
}
#endif

#endif
