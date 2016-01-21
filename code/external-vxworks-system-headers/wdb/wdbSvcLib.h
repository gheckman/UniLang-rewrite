/* wdbSvcLib.h - header file for remote debug server */

/*
 * Copyright (c) 1994-2005,2009-2010 Wind River Systems, Inc.  
 *
 * The right to copy, distribute, modify or otherwise make use  of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
01k,30mar10,pad  Moved 'extern "C"' statement and applied C++ inline scheme for
		 wdbSvcHookAdd().
01k,19jan10,pad  Removed usage of _WRS_KEEP_USING_FUNCPTR.
01j,20oct09,rlp  Adapted to LP64 model.
01i,06dec05,dbt  Removed u_int & IMPORT references.
		 Replaced XDR references with WDB XDR references.
01h,28jul05,bpn  Remove DSA support.
01g,27feb03,elg  Merge file with BSD.
01f,25apr02,jhw  Added C++ support (SPR 76304).
01e,11jan99,dbt  added wdbSvcHookAdd() prototype (SPR #24323).
01d,12feb98,dbt  added "dynamic" field in WDB_SVC structure
		 added wdbSvcDsaSvcRemove() declaration.
01c,05apr95,ms   new data types.
01b,06feb95,ms	 added XPORT handle to dispatch routine.
01a,20sep94,ms   written.
*/

#ifndef __INCwdbSvcLibh
#define __INCwdbSvcLibh

/* includes */

#include <wdb/wdb.h>
#include <wdb/xdrwdb.h>
#include <wdb/wdbRpcLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* data types */

typedef UINT32	(*WDB_SVC_HOOK_FUNCPTR) (unsigned long arg);

typedef struct			/* hidden */
    {
    UINT32		serviceNum;	
    UINT32		(*serviceRtn)();
    wdbXdrProc_t	inProc;
    wdbXdrProc_t	outProc;
    } WDB_SVC;

/* function prototypes */

extern void	wdbSvcLibInit	(WDB_SVC * wdbSvcArray, UINT32 size);
extern STATUS	wdbSvcAdd	(UINT32 procNum, UINT32 (*rout) (),
				 wdbXdrProc_t xdrIn, wdbXdrProc_t xdrOut);
extern void	wdbSvcDispatch	(WDB_XPORT * pXport, UINT32 procNum);
extern void	wdbSvcHookAdd	(UINT32 (*hookRtn) (unsigned long arg),
							unsigned long arg);
#ifdef __cplusplus
}

/*
 * Inlined C++ wrapper for the old-style FUNCPTR based wdbSvcHookAdd() function
 * prototype.
 */

extern void wdbSvcHookAdd (FUNCPTR hookRtn, unsigned long arg) \
	_WRS_DEPRECATED ("please use fully qualified function pointer version "
	"of API");

inline void wdbSvcHookAdd
    (
    FUNCPTR hookRtn,
    unsigned long arg
    )
    {
    return wdbSvcHookAdd ((WDB_SVC_HOOK_FUNCPTR)hookRtn, arg);
    }
#endif /* __cplusplus */

#endif  /* __INCwdbSvcLibh */
