/* edrLib.h - Error Detection and Reporting subsystem */

/*
 * Copyright (c) 2003-2005, 2008-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
03l,20jan11,cww  Save 32-bit tick in records to avoid ILP32 misaligned access
                 (WIND00251544)
03k,22oct10,rlp  Made edrSystemDebugXXX routine deprecated.
03j,18aug10,cww  Additional 64-bit updates
03i,13apr10,cww  Updated edrPmArena signature
03h,03jun09,pcs  Updated to add support for LP64 data model.
03h,11dec08,gls  made trace in EDR_REBOOT_INJECT contingent on valid
                 taskIdCurrent (WIND00036637)
03g,27aug08,jpb  Renamed VSB header file
03f,02jun08,jpb  Removed include of vxLibCfgDefsP.h.  Added include path for 
                 kernel configurations options set in vsb.
03e,08may08,jpb  Modifications for source build.  Renamed INCLUDE_FULL_EDR_STUBS
                 to _WRS_CONFIG_FULL_EDR_STUBS.
03d,12aug05,yvp  Moved vxLibCfgDefsP.h to h/sys.
03c,25may05,md   fix for SMP support
03c,25jul04,md   added scalability of injection macros
03b,23sep04,md   fix macros to avoid warnings
03c,25may05,md   fix for SMP support
03b,23sep04,md   fix macros to avoid warnings
03a,10sep04,md   added passing injection message to policy handlers
02z,26aug04,md   make record size configurable
02y,23aug04,md   added new style hook routines
02x,29jul04,md   added edrSystemDebugModeInit()
02w,21jul04,md   add text injection hook prototypes
02v,30jun04,md   fix for SPR 98727
02u,07jun04,md   add additional fields for a memory map
02t,21may04,md   added inject options
02s,11may04,md   added support for encoding OS version
02r,06may04,md   added prototype for edrShellCmdInit() 
02p,28apr04,elg  Modify EDR macro prototype.
02o,06apr04,pes  clean up compilation warnings.
02n,20apr04,md   move private entries to edrLibP.h
02m,30mar04,md   convert some fields to ascii instead of binary data
02l,11mar04,md   add ED&R printf like output routines
02k,03feb04,md   move common RTP defines to edrLibCommon.h
02j,11nov03,dbs  update policy handler prototypes
02i,06nov03,dbs  add INIT facility
02h,04nov03,dbs  move error-log and record structures into edrErrLogLib.h
02g,31oct03,dbs  add support for user-mode (RTP) error injection
02f,24oct03,dbs  re-implement stack tracing
02e,15oct03,dbs  add API to get boot count
02d,06oct03,dbs  re-introduce optional stack-trace arg to EDR_USER_INJECT
02c,29sep03,dbs  use setjmp() to get current regs in user-inject case
02b,25sep03,dbs  implement ED&R system policies
02a,24sep03,dbs  add prototype for edrHelp, add stack trace to REBOOT event
01z,18sep03,dbs  add user inject macro
01y,17sep03,dbs  add pre- and post-hooks
01x,17sep03,dbs  add hook for error-injection
01w,12sep03,dbs  reduce interrupt latency, introduce N-deep buffering
01v,11sep03,dbs  record init failures, display in edrShow as necessary
01u,10sep03,dbs  add edrErrorInject wrapper, remove reliance on funcptr
01t,29aug03,dbs  update after review comments
01s,19aug03,dbs  add ED&R system debug mode flag
01r,18aug03,dbs  fix error codes
01q,18aug03,dbs  add _func_edrErrorInject
01p,13aug03,aim  added symbol names to stack trace
01o,11aug03,aim  added boot count to error log header
01n,07aug03,dbs  add extended ED&R show routines
01m,06aug03,dbs  allow for more than one PM arena
01l,04aug03,dbs  move 'missed errors' count into error-log
01k,31jul03,dbs  use named constants for stack-trace and code-dump
01j,31jul03,dbs  add separate edrShow component
01i,31jul03,dbs  add transaction-like guards against errors early in boot
01h,30jul03,dbs  add edrErrorRecordShow routine
01g,28jul03,dbs  change 'location' to 'facility' and allow more of them
01f,28jul03,dbs  add more error codes
01e,25jul03,dbs  add fields to allow version checking
                 introduce EDR_ERROR_LOG structure
01d,18jul03,dbs  improve printing of error records
01c,18jul03,dbs  update for memLogLib changes
01b,17jul03,dbs  add error codes
01a,15jul03,dsellars  created
*/

#ifndef __INCedrLib_h
#define __INCedrLib_h

#include <vxWorks.h>
#include <vsbConfig.h>
#include <stdlib.h>
#include <setjmp.h>
#include <edrErrLogLib.h>
#include <regs.h>
#include <excLib.h>
#include <edrLibCommon.h>
#include <taskLib.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* version of ED&R record format we're currently using */

#define EDR_VERSION             1

/*
 * IMPORTANT: do NOT add members to the middle of this structure, only
 * to the end (but before 'text'). Offsets to the textual data are
 * stored as offsets from the beginning of the structure, so it it
 * still possible to read an OLDER kind of error-record.
 *
 * The 'size' field determines the actual number of bytes in the
 * entire record, including all the trailing text. The 'size_of' field
 * indicates the size of the structure (i.e. sizeof(EDR_ERROR_RECORD)
 * at the time the system which generated this record was
 * compiled. This allows edrLib to handle error records from older
 * systems compatibly.
 */

typedef struct edr_error_record
    {
    UINT32	  version;		/* version identifier		*/
    size_t	  size;			/* actual size of entire record */
					/* incl. trailing text		*/
    size_t	  size_of;		/* sizeof (EDR_ERROR_RECORD)	*/
    UINT32	  kind;			/* severity / facility		*/
    UINT32	  flags;		/* error-record options		*/
#ifdef _WRS_CONFIG_LP64
    _Vx_ticks64_t ticks;		/* VxWorks time stamp		*/
#else
    _Vx_ticks_t   ticks;		/* VxWorks time stamp		*/
#endif /* _WRS_CONFIG_LP64 */
    time_t	  time;			/* calendar time		*/
    UINT32	  osVersion;		/* version of OS/ED&R		*/
    UINT32	  cpuNumber;		/* CPU number (e.g. for MP) 	*/
    UINT32	  cpuType;		/* WindRiver CPU type code	*/
    UINT32        bootCycle;	        /* the bootCount this error     */
					/* was recorded in.             */
    TASK_ID	  taskId;		/* ID of executing task		*/
    RTP_ID	  rtpId;		/* ID of executing RTP		*/
    void *	  rtpAddrStart;		/* start address of RTP space	*/
    void *	  rtpAddrEnd;		/* end address of RTP space	*/
    INSTR *	  codeAddress;		/* address of code fragment	*/
    int		  lineNumber;		/* line number in source file	*/
    int		  reserved[8];		/* reserved for future use	*/
    ptrdiff_t	  offsetFileName;	/* offset to source file name	*/
    ptrdiff_t	  offsetTaskName;	/* offset to task name		*/
    ptrdiff_t	  offsetRtpName;	/* offset to RTP name		*/
    ptrdiff_t	  offsetMemoryMap;	/* offset to memory map	        */
    ptrdiff_t	  offsetExcinfo;	/* offset to exception info     */
    ptrdiff_t	  offsetRegisters;	/* offset to registers	        */
    ptrdiff_t	  offsetDisassembly;	/* offset to code disassembly	*/
    ptrdiff_t	  offsetTraceback;	/* offset to stack traceback	*/
    ptrdiff_t	  offsetPayload;	/* offset to text payload	*/
    /*************** IMPORTANT: ADD NEW FIELDS HERE! ********************/
    char	  text [4];		/* beginning of all textual info*/
    } EDR_ERROR_RECORD;

/* mask and shift counts for encoding version number in osVersion field */

#define	EDR_OS_VERSION_MAJOR_MASK	0xff
#define	EDR_OS_VERSION_MAJOR_SHIFT	16
#define	EDR_OS_VERSION_MINOR_MASK	0xff
#define	EDR_OS_VERSION_MINOR_SHIFT	8
#define	EDR_OS_VERSION_MAINT_MASK	0xff
#define	EDR_OS_VERSION_MAINT_SHIFT	0

/* optional information which may be provided for RTP policy handling */

typedef struct
    {
    RTP_ID	 rtpId;		/* RTP's id				*/
    TASK_ID	 taskId;	/* task id within RTP			*/
    int		 options;	/* options to use when deleting		*/
    int		 status;	/* exit status to provide when deleting	*/
    int		 vector;	/* exception vector number		*/
    char *	 pEsf;		/* exception frame pointer		*/
    REG_SET *	 pRegs;		/* exception register set		*/
    EXC_INFO *	 pExcInfo;	/* exception information		*/
    BOOL	 isException;	/* are we handling an exception?	*/
    const char * msg;		/* ED&R record optional message		*/
    } EDR_RTP_INFO;

/* optional information which may be provided for task policy handling */

typedef struct
    {
    TASK_ID		taskId;		/* task's id			    */
    _Vx_exit_code_t	status;		/* exit status to use when deleting */
    int			vector;		/* exception vector number	    */
    char *		pEsf;		/* exception frame pointer	    */
    REG_SET *		pRegs;		/* exception register set	    */
    EXC_INFO *		pExcInfo;	/* exception information	    */
    BOOL		isException;	/* are we handling an exception?    */
    const char *	msg;		/* ED&R record optional message	    */
    } EDR_TASK_INFO;

/* optional information which may be provided for interrupt policy handling */

typedef struct
    {
    int		 vector;	/* exception vector number		*/
    char *	 pEsf;		/* exception frame pointer		*/
    REG_SET *	 pRegs;		/* exception register set		*/
    EXC_INFO *	 pExcInfo;	/* exception information		*/
    BOOL	 isException;	/* are we handling an exception?	*/
    const char * msg;		/* ED&R record optional message		*/
    } EDR_INTERRUPT_INFO;

/* optional information which may be provided for init policy handling */

typedef struct
    {
    int		 vector;	/* exception vector number		*/
    char *	 pEsf;		/* exception frame pointer		*/
    REG_SET *	 pRegs;		/* exception register set		*/
    EXC_INFO *	 pExcInfo;	/* exception information		*/
    BOOL	 isException;	/* are we handling an exception?	*/
    const char * msg;		/* ED&R record optional message		*/
    } EDR_INIT_INFO;

/*
 * The type of a hook-function for error injection. It gets called
 * back for every error that is injected.
 */

typedef void (*EDR_ERRINJ_HOOK_FUNCPTR) (
		int          kind,	 /* severity | facility		*/
		const char * fileName,	 /* name of source file		*/
		int          lineNumber, /* line number of source code	*/
		void *       address,	 /* faulting address		*/
		const char * msg	 /* additional text string	*/
		);

/*
 * The type of a hook-function for additional text error injection. It gets
 * called back for every error that is injected.
 */

typedef size_t (*EDR_ERRINJ_TEXT_HOOK_FUNCPTR) (
		char *       p,		 /* pointer to buffer		*/
		size_t	     size,	 /* size of buffer		*/
		int          kind,	 /* severity | facility		*/
		const char * fileName,	 /* name of source file		*/
		int          lineNumber, /* line number of source code	*/
		void *       address	 /* faulting address		*/
		);

/* 
 * The type of a hook-function for pre/post hooks.
 */

typedef void (*EDR_HOOK_FUNCPTR) (
		int          type	/* pre/post injection indicator	*/
		);

#define	EDR_HOOK_TYPE_PRE	0	/* hook called pre injection	*/
#define	EDR_HOOK_TYPE_POST	1	/* hook called post injectsion	*/

/* defines */

/* init status - 0,1 are boolean uninit/init, negative values are errors */

#define EDR_INIT_UNINITIALIZED		(0)
#define EDR_INIT_OK			(1)
#define EDR_INIT_edrErrLogCreate_FAILED	(-1)
#define EDR_INIT_edrErrLogAttach_FAILED	(-2)
#define EDR_INIT_pmRegionSize_FAILED	(-3)
#define EDR_INIT_pmRegionAddr_FAILED	(-4)
#define EDR_INIT_pmRegionProtect_FAILED	(-5)
#define EDR_INIT_pmRegionCreate_FAILED	(-6)
#define EDR_INIT_PM_FAILURE		(-7)
#define EDR_INIT_ERROR_LOG_NEWER	(-8)

/* maximum number of inject hook callout routines */

#define EDR_MAX_INJECT_HOOK_RTNS	16	/* general injection hooks  */
#define EDR_MAX_INJECT_TEXT_HOOK_RTNS	16	/* text injection hooks     */
#define EDR_MAX_INJECT_PP_HOOK_RTNS	16	/* pre/post injection hooks */

/* system generated ED&R fatal messages */

/* Kernel fatal errors */

#define EDR_KERNEL_FATAL_INJECT_FULL(taskInfo, regs, excinfo, pc, reason) \
    do { \
    EDR_TASK_INFO *p = taskInfo; \
    EDR_INJECT(EDR_SEVERITY_FATAL | EDR_FACILITY_KERNEL, \
		   __FILE__, __LINE__, regs, excinfo, pc, reason); \
    if ((p != NULL)) \
	p->msg = reason; \
    edrKernelFatalPolicyHandler(taskInfo); \
    } while ((0))

#ifdef	_WRS_CONFIG_FULL_EDR_STUBS
# define EDR_KERNEL_FATAL_INJECT(taskInfo, regs, excinfo, pc, reason) \
	 EDR_KERNEL_FATAL_INJECT_FULL(taskInfo, regs, excinfo, pc, reason)
#else
# define EDR_KERNEL_FATAL_INJECT(taskInfo, regs, excinfo, pc, reason) \
	 edrKernelFatalPolicyHandler(taskInfo)
#endif /* _WRS_CONFIG_FULL_EDR_STUBS */


/* Interrupt fatal errors */

#define EDR_INTERRUPT_FATAL_INJECT_FULL(intInfo, regs, excinfo, pc, reason) \
    do { \
    EDR_INTERRUPT_INFO *p = intInfo; \
    EDR_INJECT(EDR_SEVERITY_FATAL | EDR_FACILITY_INTERRUPT, \
		   __FILE__, __LINE__, regs, excinfo, pc, reason); \
    if ((p != NULL)) \
	p->msg = reason; \
    edrInterruptFatalPolicyHandler(intInfo); \
    } while ((0))

#ifdef	_WRS_CONFIG_FULL_EDR_STUBS
# define EDR_INTERRUPT_FATAL_INJECT(intInfo, regs, excinfo, pc, reason) \
	 EDR_INTERRUPT_FATAL_INJECT_FULL(intInfo, regs, excinfo, pc, reason)
#else
# define EDR_INTERRUPT_FATAL_INJECT(intInfo, regs, excinfo, pc, reason) \
	 edrInterruptFatalPolicyHandler(intInfo)
#endif /* _WRS_CONFIG_FULL_EDR_STUBS */


/* Init fatal errors */

#define EDR_INIT_FATAL_INJECT_FULL(initInfo, regs, excinfo, pc, reason) \
    do { \
    EDR_INIT_INFO *p = initInfo; \
    EDR_INJECT(EDR_SEVERITY_FATAL | EDR_FACILITY_INIT, \
		   __FILE__, __LINE__, regs, excinfo, pc, reason); \
    if ((p != NULL)) \
	p->msg = reason; \
    edrInitFatalPolicyHandler(initInfo); \
    } while ((0))

#ifdef	_WRS_CONFIG_FULL_EDR_STUBS
# define EDR_INIT_FATAL_INJECT(initInfo, regs, excinfo, pc, reason) \
	 EDR_INIT_FATAL_INJECT_FULL(initInfo, regs, excinfo, pc, reason)
#else
# define EDR_INIT_FATAL_INJECT(initInfo, regs, excinfo, pc, reason) \
	 edrInitFatalPolicyHandler(initInfo)
#endif /* _WRS_CONFIG_FULL_EDR_STUBS */


/* RTP fatal errors */

#define EDR_RTP_FATAL_INJECT_FULL(rtpInfo, regs, excinfo, pc, reason) \
    do { \
    EDR_RTP_INFO *p = rtpInfo; \
    EDR_INJECT(EDR_SEVERITY_FATAL | EDR_FACILITY_RTP, \
		   __FILE__, __LINE__, regs, excinfo, pc, reason); \
    if ((p != NULL)) \
	p->msg = reason; \
    edrRtpFatalPolicyHandler(rtpInfo); \
    } while ((0))

#ifdef	_WRS_CONFIG_FULL_EDR_STUBS
# define EDR_RTP_FATAL_INJECT(rtpInfo, regs, excinfo, pc, reason) \
	 EDR_RTP_FATAL_INJECT_FULL(rtpInfo, regs, excinfo, pc, reason)
#else
# define EDR_RTP_FATAL_INJECT(rtpInfo, regs, excinfo, pc, reason) \
	 edrRtpFatalPolicyHandler(rtpInfo)
#endif /* _WRS_CONFIG_FULL_EDR_STUBS */


/* system generated ED&R boot/reboot messages */

#define EDR_BOOT_INJECT(msg) \
    EDR_INJECT_TRACE(EDR_SEVERITY_INFO, EDR_FACILITY_BOOT, \
		     EDR_EXCLUDE_MEMORYMAP, FALSE, msg)

#define EDR_REBOOT_INJECT(msg) \
    EDR_INJECT_TRACE(EDR_SEVERITY_INFO, EDR_FACILITY_REBOOT, \
		     EDR_EXCLUDE_REGISTERS, (taskIdCurrent != NULL), msg)


/* user generated ED&R messages */

#define EDR_USER_INFO_INJECT(trace, msg) \
	EDR_INJECT_TRACE(EDR_SEVERITY_INFO, EDR_FACILITY_USER, 0, trace, msg)

#define EDR_USER_WARNING_INJECT(trace, msg) \
	EDR_INJECT_TRACE(EDR_SEVERITY_WARNING, EDR_FACILITY_USER, 0, trace, msg)
    
#define EDR_USER_FATAL_INJECT(trace, msg) \
	EDR_INJECT_TRACE(EDR_SEVERITY_FATAL, EDR_FACILITY_USER, 0, trace, msg)


/* macros for injecting ED&R records */

#define EDR_INJECT(kind, file, line, regs, exc, addr, msg) \
	edrErrorInjectStub (kind, file, line, regs, exc, addr, msg)

#define EDR_INJECT_TRACE_FULL(sev, fac, opt, trace, msg) \
    do { \
	REG_SET *pRegs = NULL; \
	jmp_buf env; \
	int doTrace=trace; \
	if ((doTrace != 0) && (setjmp(env) == 0)) { pRegs = &env[0].reg; } \
	EDR_INJECT(sev|fac|opt, __FILE__, __LINE__, pRegs, NULL, NULL, msg); \
    } while ((0))

#ifdef	_WRS_CONFIG_FULL_EDR_STUBS
# define EDR_INJECT_TRACE(sev, fac, opt, trace, msg) \
	 EDR_INJECT_TRACE_FULL(sev, fac, opt, trace, msg)
#else
# define EDR_INJECT_TRACE(sev, fac, opt, trace, msg) \
	 EDR_INJECT(sev|fac|opt, NULL, 0, NULL, NULL, NULL, msg)
#endif /* _WRS_CONFIG_FULL_EDR_STUBS */


/* globals */

/* functions */

extern void * edrPmArena    (size_t * pSize);
extern int    edrPmRegion   (void);

extern STATUS edrErrorInjectStub
    (
    int			kind,		/* severity | facility		*/
    const char *	fileName,	/* name of source file		*/
    int			lineNumber,	/* line number of source code	*/
    const REG_SET *	pRegSet,	/* current register values	*/
    const EXC_INFO *	pExcInfo,	/* CPU-specific exception info	*/
    void *		addr,		/* faulting address (e.g. PC)	*/
    const char *	msg		/* additional text string	*/
    );

extern STATUS edrErrorInject
    (
    int			kind,		/* severity | facility | option	*/
    const char *	fileName,	/* name of source file		*/
    int			lineNumber,	/* line number of source code	*/
    const REG_SET *	pRegSet,	/* current register values	*/
    const EXC_INFO *	pExcInfo,	/* CPU-specific exception info	*/
    void *		addr,		/* faulting address (e.g. PC)	*/
    const char *	msg		/* additional text string	*/
    );

extern STATUS edrErrorRecordDecode
    (
    EDR_ERROR_RECORD *  pER,            /* pointer to error record	*/
    char *              pBuf,           /* pointer to output buffer	*/
    size_t              bufSize         /* size of output buffer	*/
    );

extern STATUS	edrErrorLogClear	(void);
extern int	edrBootCountGet		(void);
extern int	edrErrorRecordCount	(void);

/* debug flag manipulation routines */

extern BOOL   edrSystemDebugModeGet	(void)
		_WRS_DEPRECATED ("please use sysDebugModeGet() instead");
extern void   edrSystemDebugModeSet	(BOOL mode)
		_WRS_DEPRECATED ("please use sysDebugModeSet() instead");
extern BOOL   edrIsDebugMode		(void);
extern int    edrFlagsGet		(void);

/* hook manipulation routines */

extern STATUS edrErrorInjectHookAdd	(EDR_ERRINJ_HOOK_FUNCPTR hook);
extern STATUS edrErrorInjectHookDelete	(EDR_ERRINJ_HOOK_FUNCPTR hook);
    
extern STATUS edrErrorInjectPrePostHookAdd	(EDR_HOOK_FUNCPTR hook);
extern STATUS edrErrorInjectPrePostHookDelete	(EDR_HOOK_FUNCPTR hook);

extern STATUS edrErrorInjectTextHookAdd	   (EDR_ERRINJ_TEXT_HOOK_FUNCPTR hook);
extern STATUS edrErrorInjectTextHookDelete (EDR_ERRINJ_TEXT_HOOK_FUNCPTR hook);

/* system policy routines */

extern void edrKernelFatalPolicyHandler		(EDR_TASK_INFO *);
extern void edrInterruptFatalPolicyHandler	(EDR_INTERRUPT_INFO *);
extern void edrRtpFatalPolicyHandler		(EDR_RTP_INFO *);
extern void edrInitFatalPolicyHandler		(EDR_INIT_INFO *);

/* show routines */

extern STATUS edrShow		(int start, int count, int facility,
				 int severity);
extern STATUS edrFatalShow	(int start, int count);
extern STATUS edrInfoShow	(int start, int count);
extern STATUS edrIntShow	(int start, int count);
extern STATUS edrInitShow	(int start, int count);
extern STATUS edrRebootShow	(int start, int count);
extern STATUS edrBootShow	(int start, int count);
extern STATUS edrKernelShow	(int start, int count);
extern STATUS edrUserShow	(int start, int count);
extern STATUS edrRtpShow	(int start, int count);

/* misc routines */

extern STATUS edrClear		(void);
extern STATUS edrHelp		(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCedrLib_h */
