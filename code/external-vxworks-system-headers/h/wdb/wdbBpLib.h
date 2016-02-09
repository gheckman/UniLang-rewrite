/* wdbBpLib.h - wdb break point library */

/*
 * Copyright (c) 1994-1999,2002-2010 Wind River Systems, Inc.  
 *
 * The right to copy, distribute, modify or otherwise make use of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
02f,22sep10,rlp  Modified WDB_BP_ADD_HOOK_FUNCPTR typedef (WIND00186557).
02e,29apr10,pad  Moved extern C statement after include statements.
02d,10dec09,rlp  Adapted to LP64 model.
02c,27aug08,jpb  Renamed VSB header file
02b,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
02a,18jun08,dbt  Added wdbBpAddHookAdd() routine.
01z,11jul07,rlp  Added SMP support.
01y,06jul07,p_b  Added 64bits support
01x,18oct06,rlp  Used debug library (REQ00007655).
01w,14nov05,dbt  Removed wdbRegs.h inclusiong.
01v,08mar04,elg  Change WDB_CTX structure.
01u,13nov03,elg  Change WDB_BP_CTX_BP_ADD() prototype.
01t,10oct03,elg  Remove debug handler function pointers.
01s,29sep03,tbu  go back
01r,15sep03,tbu  Added wdbSysBpLibInit prototype
01q,27feb03,elg  Merge file with BSD and define new interface.
01p,25apr02,jhw  Added C++ support (SPR 76304).
01o,28oct99,elg  Add support for all-tasks breakpoints.
01n,07oct99,elg  Remove _wdbPdStop() and _wdbPdCont() declarations.
01m,04aug99,elg  Fix WDB dependencies problem.
01l,26may99,elg  Add new debug facilities for protection domains.
01k,21apr98,dbt  removed useless defines for ARM.
01j,04feb98,dbt  moved wdbSysBpLibInit() and wdbTaskBpLibInit() to wdbLib.h
01i,12jan98,dbt  modified for new debugger scheme
01h,17apr97,cdp added Thumb (ARM7TDMI_T) support.
01g,28nov96,cdp added ARM support.
01f,22jul96,jmb  merged mem's (ease) patch for HPSIM.
01e,20may96,ms   imported prototypes and macros from wdb[Task]BpLib.h.
01d,25feb96,tam  added single step support for PPC403.
01d,04apr96,ism  added simsolaris support
01c,23jan96,tpr  added PowerPC support.
01c,28nov95,mem  added MIPS support, added macros WDB_CTX_{LOAD,SAVE}.
01b,08jun95,ms   change CPU==SPARC to CPU_FAMILY==SPARC
01a,20nov94,rrr  written.
*/

#ifndef __INCwdbBpLibh
#define __INCwdbBpLibh

/* includes */
	
#include <vsbConfig.h>
#include <private/vxdbgLibP.h>
#include <wdb/dll.h>
#ifdef  _WRS_CONFIG_SMP
#include <cpuset.h>
#endif  /* _WRS_CONFIG_SMP */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/* defines */

/* Breakpoint macros */

#define	BP_INSTALLED		0x80		/* breakpoint installed */

#define BP_BASE(p)		((struct wdb_brkpt *) (p))

/* Breakpoint context macros */

#define	WDB_BP_CTX(pCtx)	(pWdbCtxBpIf [(pCtx)->contextType])
#define	WDB_BP_ENTRY(pCtx)	(pWdbCtxBpIf [(pCtx)->context.contextType])

#define	WDB_BP_CTX_BP_ADD(pCtx, pAction, addr, count, type, pId)	\
	(WDB_BP_CTX (pCtx) == NULL ?					\
	    WDB_ERR_NO_RT_CTX :						\
	    ((WDB_BP_CTX (pCtx))->bpAdd == NULL ?			\
	    	WDB_ERR_NO_RT_PROC :					\
		(WDB_BP_CTX (pCtx))->bpAdd ((pCtx), (pAction), (addr),	\
					    (count), (type), (pId))))

#define	WDB_BP_CTX_STEP(pCtx)						\
	(WDB_BP_ENTRY (pCtx) == NULL ?					\
	    WDB_ERR_NO_RT_CTX :						\
	    (WDB_BP_ENTRY (pCtx))->step == NULL ?			\
	    	WDB_ERR_NO_RT_PROC :					\
		(WDB_BP_ENTRY (pCtx))->step (WDB_CTX_ID_GET (&(pCtx)->context),\
					     (pCtx)->startAddr,		\
			 		     (pCtx)->endAddr))

#define	WDB_BP_CTX_STOP(pCtx)						\
	(WDB_BP_CTX (pCtx) == NULL ?					\
	    WDB_ERR_NO_RT_CTX :						\
	    (WDB_BP_CTX (pCtx))->stop == NULL ?				\
	    	WDB_ERR_NO_RT_PROC :					\
		(WDB_BP_CTX (pCtx))->stop (WDB_CTX_ID_GET (pCtx)))

#define	WDB_BP_CTX_CONT(pCtx)						\
	(WDB_BP_CTX (pCtx) == NULL ?					\
	    WDB_ERR_NO_RT_CTX :						\
	    (WDB_BP_CTX (pCtx))->cont == NULL ?				\
	    	WDB_ERR_NO_RT_PROC :					\
		(WDB_BP_CTX (pCtx))->cont (WDB_CTX_ID_GET (pCtx)))

/* typedefs */

typedef struct wdb_ctx_bp_if
    {
    UINT32 (*bpAdd)	(WDB_CTX * pCtx, WDB_ACTION * pAction, void * addr,
    			 UINT32 count, UINT32 type, ULONG * pId);
    UINT32 (*step)	(ULONG contextId, INSTR * startAddr, INSTR * endAddr);
    UINT32 (*stop)	(ULONG contextId);
    UINT32 (*cont)	(ULONG contextId);
    } WDB_CTX_BP_IF;

typedef struct wdb_brkpt	/* breakpoint structure */
    {
    dll_t	chain;		/* breakpoint chain */
    void *	addr;		/* breakpoint address */
    void	(*callRtn)(_Vx_usr_arg_t callArg, REG_SET * pRegSet);
    				/* routine to call (if any) */
    _Vx_usr_arg_t callArg;	/* called routine argument */
    UINT32	id;		/* breakpoint ID */
    UINT32	count;		/* breakpoint count */
    UINT32	action;		/* action associated with breakpoint */
    INSTR	instr;		/* instruction at breakpoint address */
    UINT16	type;		/* breakpoint type (software or hardware) */
    UINT8	flags;		/* breapoint flags */
#ifdef  _WRS_CONFIG_SMP
    cpuset_t	cpus;		/* processors number where */
       				/* hardware BP is installed */
#endif  /* _WRS_CONFIG_SMP */
    } WDB_BRKPT;

typedef UINT32 (*WDB_BP_ADD_HOOK_FUNCPTR) (WDB_EVTPT_ADD_DESC * pBp);

/* externs */

/* context specific debug interface */

extern WDB_CTX_BP_IF *	pWdbCtxBpIf [WDB_CTX_TYPE_NUM];

extern void	(*wdbBpSysEnterHook) (void);
extern void	(*wdbBpSysExitHook) (void);

#ifdef  _WRS_BP_ACTION_SYS_STOP
/*
 * We no longer support task-mode breakpoints with WDB_ACTION_SYS_STOP
 * action. We keep the code for now, in case this type of action will
 * be needed again.
 */

extern void		(*_func_wdbSystemStop) (WDB_IU_REGS * pRegisters,
				void * addr, BOOL notify);
#endif	/* _WRS_BP_ACTION_SYS_STOP */

/* function declarations */

extern void		wdbSysBpEnableAll (void);
extern void		wdbSysBpDisableAll (void);
extern STATUS		wdbBpAddHookAdd (WDB_BP_ADD_HOOK_FUNCPTR hook);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif	/* __INCwdbBpLibh */
