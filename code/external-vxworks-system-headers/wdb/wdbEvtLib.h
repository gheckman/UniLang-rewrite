/* wdbEvtLib.h - header file for remote debug events */

/*
 * Copyright (c) 2003-2005, 2009-2010 Wind River Systems, Inc.  
 *
 * The right to copy, distribute, modify or otherwise make use  of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
01j,29jul10,pad  Moved extern C statement after include statements.
01i,29sep09,rlp  Removed obsolete structure definition.
01h,06dec05,dbt  Removed IMPORT references.
01g,28feb03,elg  Merge file from BSD/OS.
01f,25apr02,jhw  Added C++ support (SPR 76304).
01e,12feb99,dbt  use wdb/ prefix to include wdb.h header file.
01d,04feb98,dbt  moved eventpoint handling to wdbEvtptLib.h
01c,07jun95,ms	 added prototype for wdbEvtptDeleteAll
01b,05apr95,ms 	 new data types.
01a,20sep94,ms 	 written.
*/

#ifndef __INCwdbEvtLibh
#define __INCwdbEvtLibh

/* includes */

#include <wdb/dll.h>
#include <wdb/wdb.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define	wdbEventListIsEmpty()	(__wdbEventListIsEmpty == NULL ? TRUE : \
				(*__wdbEventListIsEmpty)())

/* data types */

typedef struct
    {
    dll_t	node;
    void        (*getEvent)     (void *arg, WDB_EVT_DATA *pEvtData);
    void        (*deq)          (void *arg);
    void *      arg;
    BOOL	onQueue;
    } WDB_EVT_NODE;

/* function prototypes */

extern void   	wdbEventNodeInit	(WDB_EVT_NODE * pEvtNode,
					 void (*getEvent) (void *arg,
					 	WDB_EVT_DATA *pEvtData),
						void (*deq) (void *arg),
						void *arg);
extern void   	wdbEventPost		(WDB_EVT_NODE * pEvtNode);
extern STATUS	wdbEventDeq		(WDB_EVT_NODE * pEvtNode);
extern BOOL 	(*__wdbEventListIsEmpty) (void);

#ifdef __cplusplus
}
#endif

#endif  /* __INCwdbEvtLibh */

