/* strSearchLib.h - String search library header file */

/* 
 * Copyright (c) 2005, 2010-2011 Wind River Systems, Inc. 
 * 
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
01c,09may11,jpb  Added deprecated messages.
01b,19oct10,jpb  Updated signatures for LP64 adaptation.
01a,04apr05,svk  written
*/

#ifndef __INCstrSearchLibh
#define __INCstrSearchLibh

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

extern char * fastStrSearch (char * pattern, size_t patternLen, 
                             char * buffer,  size_t bufferLen, 
                             BOOL caseSensitive)
    _WRS_DEPRECATED ("Use memmem() instead");
extern char * bmsStrSearch  (char * pattern, size_t patternLen, 
                             char * buffer,  size_t bufferLen, 
                             BOOL caseSensitive)
    _WRS_DEPRECATED ("Use memmem() instead");
extern char * bfStrSearch   (char * pattern, size_t patternLen, 
                             char * buffer,  size_t bufferLen, 
                             BOOL caseSensitive)
    _WRS_DEPRECATED ("Use memmem() instead");

#ifdef __cplusplus
}
#endif

#endif /* __INCstrSearchLibh */

