/* wvTsfsUploadPathLibP.h - tsfs event-upload mechanism library header */

/* Copyright 1997-1998, 2003, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01g,29apr10,pad  Moved extern C statement after include statements.
01g,10feb10,tcr  update for 64bit
01f,04sep03,tcr  rename init function
01e,27jan98,cth  removed tsfsUploadPathError prototypes, SOSENDBUFSIZE
01d,18dec97,cth  renamed again to wvTsfsUploadPathLibP.h from, updated include,
		 wvTsfsUploadPathP.h, added tsfsUploadPathLibInit prototype 
01c,16nov97,cth  renamed again to wvTsfsUploadPathP.h from tsfsUploadPathP.h
01b,16nov97,cth  changed prototypes to match new WV2.0 upload-path model
                 renamed to tsfsUploadPathP.h from evtTsfsSockLibP.h
01a,21aug97,cth  created, modified from evtSockLibP.h
*/

#ifndef __INCwvtsfsuploadpathlibph
#define __INCwvtsfsuploadpathlibph


#include "private/wvUploadPathP.h"

#ifdef __cplusplus
extern "C" {
#endif


extern STATUS	    wvTsfsUploadPathLibInit (void);
extern UPLOAD_ID    wvTsfsUploadPathCreate (char *ipAddress, int port);
extern STATUS       wvTsfsUploadPathClose (UPLOAD_ID upId);
extern ssize_t      wvTsfsUploadPathWrite (UPLOAD_ID upId, char * buffer,
                                           size_t bufSize);

#ifdef __cplusplus
}
#endif

#endif /* __INCwvtsfsuploadpathlibph*/

