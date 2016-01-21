/* vxsimHostLib.h - Host/VxSim interface header */

/*
 * Copyright (c) 2003-2007,2010,2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this
 * software may be licensed only pursuant to the terms of an applicable
 * Wind River license agreement.
 */

/*
modification history
--------------------
02d,06jan11,dbt  Updated vxsimHostProcCall() to return a ULONG instead of
                 UINT32 (CQ:WIND00249917).
02c,08jan10,elp  64bits support (host calls).
02b,23jul07,elp  moved includes to vxsimHostLibP.h.
02a,30jan07,elp  added vxsimHostProcCall().
01z,20oct06,elp  moved vxsimHostWdbPipe* routines in private.
01y,11jan05,jmp  added vxsimHostWdbPipe* routines.
01x,03may04,jeg  moved the private APIs to vxsimHostLibP.h file.
01w,14apr04,elp  added vxsimHostSimnetParamGet/Set().
01v,09apr04,jeg  removed vxsimBufLib.h header included
01u,08mar04,jmp  updated vxsimHostBufInit() & vxsimHostBufDelete() prototypes.
		 added missing passfs prototypes.
01t,05mar04,dbt  Removed simip references.
01s,25nov03,jmp  added vxsimHostVirtualMemInfoGet().
01r,13oct03,jeg  added vxsimHostOpendir () prototype. Renamed passFs specific 
		 routines.
01q,07oct03,elp  removed vxsimNetArchLib.h, added SIMNET host driver interfaces.
01p,03oct03,dbt  Added vxsimHostSimipEnetAddrGet() interface.
01o,01oct03,jmp  added MMU routines.
01n,30sep03,elp  added vxsimNetArchLib.h.
01m,26sep03,dbt  Added SIMIP host driver interfaces.
01l,05sep03,jmp  added vxsimHostDllLoad().
01k,07aug03,jeg  added vxsimHostShMemInit () and vxsimHostBusIntGen ()
		 prototypes.
01j,31jul03,jeg  added non-volatile RAM routines declarations
01i,31jul03,jmp  added VxSim buffer library support.
01h,30jul03,jeg  added vxsimHostFtruncate () prototype.
01g,19jun03,jmp  added prototype for vxsimHostDbg().
01f,17jun03,dbt  Added vxsimHostTimeGet() & vxsimHostStat() prototypes.
01e,15may03,jmp  added vxsimHostCurrentPathGet().
01d,30apr03,dbt  Added timestamp timer prototypes.
01c,04apr03,dbt  Removed vxsimHostIntLock().
01b,04apr03,jeg  add common host interface prototypes
01a,30jan03,jmp  written.
*/

#ifndef __INCvxsimHostLibh
#define __INCvxsimHostLibh

/* includes */

/* common host side defined routines */

extern FUNCPTR  vxsimHostProcAddrGet 	(char * routine);
extern STATUS	vxsimHostDllLoad	(char * dllName);
extern ULONG	vxsimHostProcCall	(FUNCPTR rtnAddr,
					 _Vx_usr_arg_t arg0,
					 _Vx_usr_arg_t arg1,
					 _Vx_usr_arg_t arg2,
					 _Vx_usr_arg_t arg3,
					 _Vx_usr_arg_t arg4,
					 _Vx_usr_arg_t arg5,
					 _Vx_usr_arg_t arg6,
					 _Vx_usr_arg_t arg7,
					 _Vx_usr_arg_t arg8);

#endif	/* __INCvxsimHostLibh */
