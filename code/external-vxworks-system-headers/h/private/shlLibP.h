/* shlLibP.h - private shared library support library header file */

/*
 * Copyright (c) 2004, 2007, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01f,02jun10,zl   added 64-bit specific entries to SHL_NODE
01e,06oct07,zl   added _func_shlGottSet
01d,05nov04,kk   updated prototype of shlRtpDeleteAll()
01c,21sep04,bpn  Added functions prototypes shlNodeTake(), shlIdGive() and
                 shlNodeToShlId().
01b,16apr04,pad  Added structure type RTP_SHL_INFO to return information about
                 a SL bound to a RTP. Added declaration of shlRtpInfoGet().
		 Declarations of shlLibInit() and shlRtpDeleteAll() moved here.
01a,26mar04,dms  created based on sdLib.h
*/

#ifndef __INCshlLibPh
#define	__INCshlLibPh

#include <vxWorks.h>
#include <shlLibCommon.h>
#include <dllLib.h>

#define	RTPSHL_MUTEX_TAKEN	0x00000001 /* set if RTP owns shlNode mutex */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
    {
    DL_NODE	next;		/* chain of all SHL_NODEs */
    char *	name;		/* unique string identifier */
    UINT	GOTTIndex;
    UINT32	flags;
    UINT32	count;		/* number of references */
    SEM_ID	mutex;		/* lock for text segment initialization */
    VIRT_ADDR	textBase;	/* address of shared library text segment */
    size_t	textSize;	/* size of shared library text segment */
    size_t	dataSize;	/* size of shared library data segment */
#ifdef _WRS_CONFIG_LP64
    VIRT_ADDR	dataBase;	/* address of shared library data segment */
    VIRT_ADDR	bssBase;	/* address of shared library bss  */
    size_t	bssSize;	/* size of shared library BSS section */
    PHYS_ADDR	textPhysAddr;	/* physical address of shared text segment */
    size_t	textPageCnt;	/* actual page count for text segment */
    VIRT_ADDR	dataCopyAddr;	/* global copy of data section */
#endif
    } SHL_NODE;

typedef struct
    {
    DL_NODE	next;		/* per-RTP chain of RTP_SHL_NODEs */
    SHL_NODE	*pShlNode;
    UINT32	flags;
    VIRT_ADDR	dataBase;	/* address of shared library data in the RTP */
    } RTP_SHL_NODE;

typedef struct rtpShlInfo	/* information about a SL bound to a RTP */
    {
    char *	fileName;	/* .so file name and path */
    VIRT_ADDR	textBase;	/* base address of SL text segment */
    size_t	textSize;
    VIRT_ADDR	dataBase;	/* base address of RTP's copy of SL data seg */
    size_t	dataSize;
    } RTP_SHL_INFO;

typedef void *** (* FUNC_SHL_GOTT_SET) (void ** gott);

/* gloabl variable declarations */

extern FUNC_SHL_GOTT_SET _func_shlGottSet;
				/* decouple shlLib.c from rtpSysctl.c */
				/* _func_shlGottSet is in rtpSysctl.c */

/* function declarations */

extern STATUS		shlLibInit (void);
extern void		shlRtpDeleteAll (RTP_ID rtpId);
extern STATUS		shlRtpInfoGet (SHL_ID shlId, RTP_ID rtpId,
			       	       RTP_SHL_INFO * pRtpShlInfo);

extern SHL_NODE *	shlNodeTake (SHL_ID shlId);
extern void		shlIdGive (SHL_NODE * pShlNode);
extern SHL_ID		shlNodeToShlId (SHL_NODE * pShlNode);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* __INCshlLibPh */
