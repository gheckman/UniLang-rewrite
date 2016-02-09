/* dbgLib.h - header file for dbgLib.c */

/*
 * Copyright (c) 2003-2006, 2009-2010 Wind River Systems, Inc.  
 *
 * The right to copy, distribute, modify or otherwise make use  of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
02l,22oct10,jmp  Removed obsolete INST_CMP() macro - Replaced by
                 VXDBG_INSTR_CMP().
02k,29apr10,pad  Moved extern C statement after include statements.
02j,15apr09,jmp  Adapted for 64-bit support.
02i,18oct06,rlp  Removed wdbDbgLib header files (REQ00007655).
02h,08jul03,bpn  Moved ALL definition to dbgTaskLibP.h
02g,01jul03,jmp  removed SIMNT specific code.
02f,28feb03,bpn  Clean-up.
02e,30apr98,dbt  removed unused DBG_TT.
02d,12jan98,dbt  modified for new debugger scheme.
02c,15aug97,cym  added SIMNT support.
02b,28nov96,cdp  added ARM support.
02a,26may94,yao  added PPC support.
01t,19mar95,dvs  removed #ifdef TRON - tron no longer supported.
01s,15dec93,hdn  added support for I80X86.
01r,02dec93,pad  Added Am29k family support.
01q,11aug93,gae  vxsim hppa.
01p,20jun93,gae  vxsim.
01r,22feb94,smb  changed typedef EVENT_TYPE to event_t (SPR #3064)
01q,14jan94,c_s  changed protoype of e ().
01p,10dec93,smb  added instrumentation for eventpoints
01o,13nov92,dnw  removed DBG_INFO typedef to taskLib.h (SPR #1768)
01n,22sep92,rrr  added support for c++
01m,25aug92,yao  added function prototypes for dbgBreakNotifyInstall(),
		 dbgStepQuiet(), bdTask().
01l,29jul92,wmd  place #pragma aligns around DBG_INFO for the i960.
01k,10jul92,yao  renamed DBG_STATE to DBG_INFO.  removed dbgMode, pDbgSave,
		 BOOLS resumeTask, sstepTask, sstepQuite, pInterruptBreak.
		 added dbgState to DBG_INFO.  added DBG_TASK_RESUME,
		 DBG_TASK_S_STEP, DBG_TASK_QUIET.  added dbgBrkExists ().
		 added BRK_SINGLE_STEP.  renamed BRK_SO to BRK_STEP_OVER.
01j,06jul92,yao  removed dbgLockCnt in DBG_STATE.
01i,04jul92,jcf  cleaned up.
01h,12mar92,yao  moved TRON related stuff to dbgTRONLib.h. added macros
		 LST_FIRST, LST_NEXT, INST_CMP.  added data structure HWBP,
		 BRKENTRY, DBG_STATE.  added ANSI prototype for architecture
		 interface routines.
01j,26may92,rrr  the tree shuffle
01i,23apr92,wmd  moved include of dbg960Lib.h after defines of structures.
01g,09jan92,jwt  converted CPU==SPARC to CPU_FAMILY==SPARC.
01f,16dec91,hdn  changed a type of bp->code, from INSTR to int, for G100.
01e,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed VOID to void
		  -changed ASMLANGUAGE to _ASMLANGUAGE
		  -changed copyright notice
01d,11sep91,hdn  added things for redesigned dbgLib.c for TRON.
01c,10jun91,del  added pragma for gnu960 alignment.
01b,24mar91,del  added things for redesigned dbgLib.c only available on
		 i960ca.
01a,05oct90,shl created.
*/

#ifndef __INCdbgLibh
#define __INCdbgLibh

#include <vxWorks.h>
#ifndef _ASMLANGUAGE
#include <private/eventP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Defines */

/* function declarations */

/* 
 * For compatibility purpose with vxWorks 5.5, the definition of the 
 * shell debug functions are written in this file.
 */

IMPORT STATUS 	dbgInit (void);

IMPORT void 	dbgHelp (void);
IMPORT STATUS 	c	(long taskNameOrId, void * addr, void * addr1);
IMPORT STATUS 	s	(long taskNameOrId, void * addr, void * addr1);
IMPORT STATUS 	b	(void * addr, long taskNameOrId, int count,
			 BOOL quiet);
IMPORT STATUS 	e	(void * addr, event_t eventId, long taskNameOrId,
			 FUNCPTR evtRtn, _Vx_usr_arg_t arg);
#if	DBG_HARDWARE_BP
IMPORT STATUS	bh	(void * addr, int access, long taskNameOrId,
			 int count, BOOL quiet);
#endif	/* DBG_HARDWARE_BP */
IMPORT STATUS 	bd	(void * addr, long taskNameOrId);
IMPORT STATUS 	bdall	(long taskNameOrId);
IMPORT STATUS 	cret	(long taskNameOrId);
IMPORT STATUS 	so	(long taskNameOrId);
IMPORT void 	l	(void * addr, int count);
IMPORT STATUS 	tt	(long taskNameOrId);

#endif	/* _ASMLANGUAGE */
#ifdef __cplusplus
}
#endif

#endif /* __INCdbgLibh */
