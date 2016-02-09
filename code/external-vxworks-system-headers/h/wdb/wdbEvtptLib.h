/* wdbEvtptLib.h - header file for remote debug eventpoints */

/*
 * Copyright (c) 1998-2000,2002-2003,2005,2007, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this
 * software may be licensed only pursuant to the terms of an applicable Wind
 * River license agreement.
 */

/*
modification history
--------------------
01h,29jul10,pad  Moved extern C statement after include statements.
01g,26jun07,tbu  Added 64 bit support
          + p_b  completed support
01f,07nov05,dbt  Removed wdbEvtptDeleteAll() macro.
		 Replaced IMPORT with extern.
01e,28feb03,elg  Merge file from BSD/OS.
01d,25apr02,jhw  Added C++ support (SPR 76304).
01c,25jan00,elg  Add WDB_CORE in evtptAdd().
01b,12feb99,dbt  use wdb/ prefix to include wdb.h header file.
01a,12feb98,dbt	 written.
*/

#ifndef __INCwdbEvtptLibh
#define __INCwdbEvtptLibh

/* includes */

#include <wdb/dll.h>
#include <wdb/wdb.h>

#ifdef __cplusplus
extern "C" {
#endif

/* data types */

typedef struct			/* hidden */
    {
    dll_t		evtptList;
    WDB_EVT_TYPE	evtptType;
    UINT32		(*evtptAdd) (WDB_CORE * pWdbCore,
    				     WDB_EVTPT_ADD_DESC * pEvtpt,
				     TGT_LONG_T * pId);
    UINT32		(*evtptDel) (TGT_LONG_T * pId);
    } WDB_EVTPT_CLASS;

/* function prototypes */

extern void   	wdbEvtptClassConnect	(WDB_EVTPT_CLASS * pEvtList);

#ifdef __cplusplus
}
#endif

#endif  /* __INCwdbEvtptLibh */
