/* wdbLib.h - header file for remote debug server */

/*
 * Copyright (c) 1994-1995,1998-2000,2002-2005,2007, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this
 * software may be licensed only pursuant to the terms of an applicable Wind
 * River license agreement.
 */

/*
modification history
--------------------
02b,29jul10,pad  Moved extern C statement after include statements.
02a,26jun07,tbu  Added 64 bit support
           +p_b  completed support
01z,20dec05,dbt  Moved OS specific routines to wdbOsLib.h.
01y,08dec05,dbt  Updated wdbInstallCommIf() prototype to add MTU parameter.
01x,06dec05,dbt  Removed wdbBpLib.h inclusion.
01w,23sep04,elg  Change wdbGopherLibInit() prototype.
01v,15dec03,elg  Add new initialization routine: wdbTaskHookInit().
01u,04jul03,elg  Export wdbTaskModeInit() instead of wdbTaskRtIfInit().
01t,27feb03,elg  Merge file with BSD.
01s,13feb03,elg  Add WDB_MAX_ARGS ddefinition.
01r,25apr02,jhw  Added C++ support (SPR 76304).
01q,28aug00,elg  Add wdbPdLibInit() declaration.
01p,21aug00,elg  Add a new routine wdbFuncCallFpLibInit() (SPR 33747).
01o,31jan00,dbt  Added wdbUserSvcLibInit() and wdbTrgLibInit() prototypes.
01n,14jan00,dbt  Renamed wdbSymSyncLibInit().
01m,16dec99,elg  Add WDB_MAX_ARGS.
01l,19oct99,dbt  added wdbSymSyncLibInit() prototype.
01k,02aug99,dbt  added support for standalonagent.
01j,26may99,elg  Add new facilities for protection domain debug.
01i,25mar98,dbt  added wdbSystemSuspend() prototype.
01h,04mar98,dbt  added wdbCtxStartLibInit(), wdbUserEvtLibInit() and
                 wdbUserEvtPost() prototypes.
		 added WDB_MAX_USER_EVT_SIZE define.
01g,04feb98,dbt  added wdbEvtptLibInit() prototype. Undo 01f change
01f,12jan98,dbt  moved wdbSysBpLibInit() and wdbTaskBpLibInit() to wdbBpLib.h
01e,20jun95,tpr  added wdbMemCoreLibInit() prototype.
01d,19jun95,ms	 added prototypes for wdbCtxExitLibInit and wdbSioTest
01c,01jun95,ms	 changed prototype for wdbGopherLibInit.
01b,05apr95,ms   new data types.
01a,20sep94,ms   written.
*/

#ifndef __INCwdbLibh
#define __INCwdbLibh

/* includes */

#include "wdb/wdb.h"
#include "wdb/wdbLibP.h"
#include "wdb/wdbRtIfLib.h"
#include "wdb/wdbRpcLib.h"
#include "wdb/wdbCommIfLib.h"

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define WDB_MAX_USER_EVT_SIZE	250	/* max. WDB user event size (bytes) */
#define	WDB_MAX_ARGS		10	/* maximum of arguments in a task */

/* function prototypes */

extern STATUS	wdbExternInit		(void * stackBase);
extern void	wdbInstallRtIf		(WDB_RT_IF *);
extern void	wdbInstallCommIf	(WDB_COMM_IF * pCommIf,
					 WDB_XPORT * pXport,
					 UINT32 wdbCommMtu);
extern void	wdbConnectLibInit	(void);
extern void	wdbMemLibInit		(void);
extern void	wdbMemCoreLibInit	(void);
extern void	wdbCtxExitLibInit	(void);
extern void	wdbRegsLibInit		(void);
extern void	wdbEventLibInit		(void);
extern void	wdbEvtptLibInit		(void);
extern void	wdbFuncCallLibInit	(void);
extern void	wdbDirectCallLibInit	(void);
extern void	wdbGopherLibInit	(char primaryTape [], UINT32 tapeLen,
					 UINT32 tapeNb);
extern void	wdbVioLibInit		(void);
extern void	wdbExcLibInit		(void);
extern void	wdbUserEvtLibInit	(void);
extern STATUS	wdbUserEvtPost		(char * event);
extern void	wdbUserSvcLibInit	(WDB_USR_SVC * pWdbUsrSvcStruct,
					 UINT32 numService);
extern void	wdbCtxStartLibInit	(void);
extern STATUS	wdbSystemSuspend	(void);
extern void	wdbCtxLibInit		(void);
extern void	wdbTgtInfoLibInit	(void);

#ifdef __cplusplus
}
#endif

#endif /* __INCwdbLibh */

