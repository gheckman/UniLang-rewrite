/* usrLibP.h - private header file for user interface library */

/* Copyright 2003-2005, 2009-2011 Wind River Systems, Inc. */

/*
modification history
--------------------
01h,16mar11,jmp  Added usrLibInit() (CQ:WIND00235451).
01g,29apr10,pad  Moved extern C statement after include statements.
01f,28apr09,jmp  Adapted for 64-bit support.
01e,25jan05,bpn  Added changeFpReg(), changeReg(), substrcmp() prototypes.
01d,08nov04,bpn  Added taskRegsModify() prototype (SPR#103922).
01c,02jun04,bpn  Added usrModuleLoad() prototype.
01b,18may04,bpn  Added function prototypes.
01a,12nov03,jn   written
*/

#ifndef __INCusrLibPh
#define __INCusrLibPh

#include <moduleLib.h>
#include <objLib.h>
#include <symLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

extern STATUS	usrLibInit	(size_t spStackSize, int spPriority,
				 int spOptions);
extern TASK_ID  taskIdFigure    (long taskNameOrId);
extern STATUS	lkAddrInternal	(void * addr, SYMTAB_ID symTabId);
extern STATUS	objectShow	(OBJ_ID objId, int level,
				 const char * errorStr);
extern STATUS	memoryDump	(void * adrs, int nunits, int width,
				 const char * errorStr);
extern STATUS	memoryModify	(void * adrs, int width, const char * errorStr);
extern MODULE_ID usrModuleLoad	(int fd, int loadFlags, BOOL noAbort,
				 const char * errorStr);
extern STATUS	taskRegsModify	(char * regName, TASK_ID taskId,
				 const char * errorStr);

extern STATUS	changeFpReg	(char * pPrompt, double value, double * pValue);
extern STATUS	changeReg	(char * pPrompt, void * pValue, int width);
extern BOOL	substrcmp	(char * s, char * s1);

/* usrFsShellCmd.c functions below this comment */

extern STATUS	usrFsShellCmdInit ();

#ifdef __cplusplus
}
#endif

#endif /* __INCusrLibPh */
