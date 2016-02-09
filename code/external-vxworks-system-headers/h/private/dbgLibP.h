/* dbgLibP.h - private debugging facility header */

/*
 * Copyright (c) 1992-1993, 1998-1999, 2003-2004, 2006-2010
 * Wind River Systems, Inc.  
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01x,22oct10,jmp  Removed obsolete INST_CMP() macro - Replaced by
                 VXDBG_INSTR_CMP().
01w,20sep10,jpb  Added function pointer _dbgDsmInstRtn
01v,12may10,rlp  Moved VxDBG client descriptor definition to shellLibP.
01v,29apr10,pad  Moved extern C statement after include statements.
01u,05mar10,rlp  Fixed dprintf prototype.
01t,12feb10,jmp  Removed compat flag from dbgBpListPrint().
01s,02jun09,rlp  Added DBG_CRET macro (WIND00168837).
01t,29jun09,jmp  Added verbose mode to b().
		 Added bi() command.
01s,15apr09,jmp  Adapted for 64-bit support.
01r,08jul08,v_r  Renamed dbgDprintfInternal() to follow coding conventions.
01q,17jun08,v_r  Added dbgDprintfInternal() prototype.
01p,05sep07,rlp  Modified dbgBpEpCoreRtn prototype (CD:WIND00098754).
01o,30oct06,rlp  Modified to use VxDBG library (REQ00007655).
01n,17mar04,bpn  Exported several functions for command line interpreter.
01m,09feb04,elg  Add definition of _dbgInstSizeGet().
01l,25nov03,bpn  Added several prototypes.
01k,21oct03,bpn  Moved several definitions to dbgTaskLibP.h.
01j,05mar03,bpn  Removed some definitions and external declatations.
01i,28feb03,bpn  Moved in definitions from dbgLib.h. Added declaration of
		 dbgBpAdd(), dbgBpRemove() and dbgHwBpSet(). Clean up.
01h,18jan99,elg  Authorize breakpoints in branch delay slot (SPR 24356).
01g,13jan98,dbt  modified for new breakpoint scheme
01f,20aug93,dvs  removed declaration of dsmNbytes(), added include dsmLib.h 
		 (SPR #2266).
01e,01oct92,yao  added to pass pEsf, pRegSet to _dbgStepAdd().
01d,22sep92,rrr  added support for c++
01c,21jul92,yao  added declaration of trcDefaultArgs.  changed IMPORT
		 to extern.
01b,06jul92,yao  made user uncallable globals started with '_'.
01a,16jun92,yao  written based on mc68k dbgLib.c ver08f.
*/

#ifndef __INCdbgLibPh
#define __INCdbgLibPh

#include <vxWorks.h>
#include <regs.h>
#include <symLib.h>
#include <dbgLib.h>
#include <stdarg.h>
#include <private/vxdbgLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Defines */

#ifndef DBG_CRET                /* continue until return (cret) support */
#define DBG_CRET                TRUE
#endif  /* DBG_CRET */

/* typedefs */

typedef enum dbg_bp_list_type
    {
    DBG_BP_LIST_BY_CTX,
    DBG_BP_LIST_BY_ID
    } DBG_BP_LIST_TYPE;


/* Function declarations */

extern STATUS	dbgBpListPrint		(DBG_BP_LIST_TYPE listType,
					 VXDBG_BP_ID bpId, VXDBG_CTX * pCtx,
					 BOOL verbose);
extern void	dbgCallPrint		(INSTR * callAdrs, INSTR * funcAdrs,
					 int nargs, _Vx_usr_arg_t * args,
					 TASK_ID taskId, BOOL isKernelAdrs);
extern STATUS	dbgStackTrace		(TASK_ID taskId, const char * errorStr);
extern STATUS	dbgDisassemble		(INSTR * addr, int count,
					 SYMTAB_ID symTabId,
					 const char * errorStr);
extern void     _dbgArchInit		(void);
extern INSTR *  _dbgRetAdrsGet		(REG_SET * pRegSet);
extern BOOL     _dbgFuncCallCheck	(INSTR * addr);
extern int      _dbgInstSizeGet		(INSTR * brkInst);
extern INSTR *  _dbgTaskPCGet		(TASK_ID tid);
extern void     _dbgTaskPCSet		(TASK_ID tid, INSTR * pc, INSTR * npc);
extern void     _dbgBrkDisplayHard	(BRKPT * pBp);

extern STATUS	dbgBpEpCoreRtn		(void * addr, VXDBG_CTX * pCtx,
					 UINT16 bpAccess,
					 VXDBG_BP_ACTION bpAction,
					 VXDBG_BP_ATTR bpAttr, BOOL hard,
					 int count, VXDBG_BP_CALL_RTN callRtn,
					 _Vx_usr_arg_t callArg,
					 const char * errorStr);
extern STATUS   dbgDynPrintfCommonRtn	(void * addr, VXDBG_CTX bpCtx, 
					 BOOL hardBp, UINT16 accessType,
					 int cnt, char * fmt, va_list argPtr,
					 const char * errorStr);
extern STATUS	dbgTaskTraceCoreRtn	(TASK_ID taskId, const char * errorStr);
extern STATUS	dprintf			(void * addr, long taskNameOrId,
					 int count, char * format, ...);
extern STATUS	hdprintf		(void * addr, int access,
					 long taskNameOrId, int count,
					 char * format, ...);
extern STATUS	bh			(void * addr, int acces,
					 long taskNameOrId, int count,
					 BOOL quiet);
extern STATUS	bi			(void * bpId);

/* function pointers */

/* TODO: make _dbgDsmInstRtn fully-typed */

extern FUNCPTR     _dbgDsmInstRtn;

#ifdef __cplusplus
}
#endif

#endif /* __INCdbgLibPh */
