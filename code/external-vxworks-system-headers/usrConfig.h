/* usrConfig.h - header file for usrConfig.c */

/*
 * Copyright (c) 1984-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
05m,17aug11,jxu  Added inclusion of selectLibP.h (WIND00289739).
05l,22oct10,rlp  Added more header files for WDB and target shell.
05k,29apr10,pad  Moved extern C statement after include statements.
05j,05jun09,cww  Removed coprocLib.h include
05i,11feb09,zl   removed qLib.h inclusion
05h,13oct08,rbc  Update for efi header move.
05g,22aug08,rbc  Changes for passing EFI memory map and ACPI table pointer.
05f,27sep07,rlp  Used the INCLUDE_VXDBG_CPU_CONTROL component to include
                 vxdbgCpuLibP.h (CQ:WIND00105692).
05e,24sep07,pee  WIND00037049 removing obsolete file symSyncLib.h
05d,26jul07,v_r  Renamed INCLUDE_SHELL_SAVE_LOAD_HISTORY to
                 INCLUDE_SHELL_HISTORY_FILE.
05c,25jul07,v_r  Added shellHistCmdInit() prototype (req CQ:WIND00005098).
05b,15jun07,rlp  Added SMP support for WDB agent.
05a,31aug06,kch  Removed the unnecessary coreip header files and prototypes.
04z,18oct06,rlp  Renamed dbgRtpLibP.h to vxdbgRtpLibP.h (REQ00007655).
04y,23jan06,v_r  Use SYMBOL_ID instead of SYMBOL *. This is the proper way of
                 declaring symbols as the structure is private.
04x,08sep05,dcc  removed INCLUDE_TAPEFS component (SPR# 111788)
04w,25feb05,h_k  included aimMmuLib.h and added prototype declaration for
                 usrAimMmuConfig(). (SPR #106193).
04v,23feb05,gls  added wdb/wdbLib.h
04u,14feb05,dlk  Remove include of ftpdLib.h.
04t,12oct04,kk   updated kernelBaseLib.h to private/kernelBaseLibP.h
04s,29sep04,tam  removed edrKHLib.h, added private/taskMemLibP.h
04r,24sep04,jn   Make prototype of loadLibInit visible
04q,13sep04,kk   renamed rtpBaseLib.h to kernelBaseLib.h
04p,09sep04,bpn  Added shell commands init routines prototypes.
04s,24sep04,rfr  Added #include <usrTransLib.h>
04r,23sep04,rfr  Added transCbio.h
04q,23sep04,ann  merge from networking: removed usrFtpInit.
04p,07sep04,jyo  Fixing SPR 100119: Removing references to RT11.
04o,13jul04,p_r  added SNS_SHOW info (SPR#99392)
04n,02jun04,bpn  Added moduleShellCmdInit() and unloadShellCmdInit() prototypes.
04m,18may04,bpn  Added usrRtpLibInit() prototype.
04l,18may04,bpn  Added usrFsShellCmdInit() prototype.
04k,02apr04,jn   Move loader related includes into usrConfig.c.
04j,29apr04,cjj  Added includes for rtpBaseLib.h and isrLibP.h
04i,24feb04,jln  remove smNetLib.h
04i,02mar04,pad  Removed stray slash character at end of line (SPR 94513).
04h,05dec03,jn   Remove references to a.out and coff
04g,03dec03,dat  added dirent.h for POSIX_DIRLIB component
04f,02dec03,p_r  added SAL headers
04e,17nov03,rp   header file path update
04d,18nov03,bpn  Added includes for shellConfigLib.h
04c,17nov03,yvp  Added includes for rtpLibP.h and syscallLibP.h
04b,06oct03,dbs  add EDR KH support
04a,26aug03,dbs  added ED&R features
03z,24jul03,jeg  added vxsim virtual disk support
03y,10apr03,pes  PAL Coprocessor Abstraction
03x,15jul03,kam  rebased to Base6 integration branch
03w,19may03,to   added include of rtpLib.h, deleted K&R style prototypes.
03v,20feb03,jmp  simulator code cleanup.
03u,20feb03,bpn  Added ledLib header file.
03v,16aug02,ham  guarded SM stuffs.
03u,13aug02,ham  merged IPv6 version 01g,10jun02,rvr to Veloce.
03t,05mar02,mas  updated to support new SM components (SPR 73371)
03s,22jan02,mas  made smObjLib.h and smNetLib.h conditional inclusions
03r,21jan02,sn   include cplusLib.h
03q,13nov01,yvp  Added include for private/excLibP.h
03p,31oct01,gls  merged in pthread code from AE
03o,04oct01,jkf  added dosFs2 headers.
03n,14oct99,jk   added conditional include for sound driver (sb16drv.h).
03m,01sep98,drm  added extern for usrWindMPInit()
03l,18jun98,cjtc including header files to prevent compilation warnings for
                 WV2.0 (SPR 21494)
03s,04may98,cym  fixed end and edata for SIMNT.
03r,27jan98,cth  changed INCLUDE_INSTRUMENTATION to INCLUDE_WINDVIEW,
		 removed connLib.h
03p,21jan98,jmb  removed end and edata for SIMNT (only when using Visual C)
03o,02jan98,cym  removed end and edata for SIMNT.
03n,16nov97,cth  removed includes of evtTsfsSockLibP.h and evtSockLibP.h
03m,21aug97,cth  added conditional include of evtTsfsSockLibP.h
03l,18aug97,cdp  added conditional declaration of thumbSymTblAdd().
03k,07apr97,spm  added support for unit numbers
03j,24feb97,gnn  added conditional RIP includes
03i,27nov96,spm  added conditional includes for DHCP client
03h,28dec96,ms   added conditional include of tapeFs.h
03g,13dec96,elp  changed syncLib.c into symSyncLib.c
03f,30oct96,elp  Added syncLib.h.
03e,09aug96,dbt  include all posix headers if INCLUDE_POSIX_ALL is defined
		 (SPR #5524).
03d,26jul96,hdn  added a function declaration of usrAtaConfig().
03c,20mar96,hdn  made inclusion of pppLib.h conditional.
03b,15mar96,sgv  made inclusion of strmLib.h conditional.
03a,22jun95,caf  no longer need "_" for GHSxPPC.
02m,10oct95,dat	 removed #include "bspVersion.h"
02l,27jul95,dzb  added strmLib.h inclusion.  Added usrStrmInit().
02k,25jul95,dzb  added sockLib.h and bsdSockLib.h inclusion.
02j,09may95,ms	 prototype for WDB agent
02i,28mar95,kkk  changed edata and end to arrays (SPR #3917)
02h,09jan95,dzb  added prototype for PPP.
02h,22may95,yao  add "_" to edata, end for PowerPC with Green Hills tool.
02g,25oct93,hdn  added prototype for floppy and IDE driver.
02m,22feb94,elh  added function defs for snmp.
02m,25jul94,jmm  removed prototype of printConfig() (spr 3461)
02l,28jan94,dvs  changed INCLUDE_POSIX_MM_MAN to INCLUDE_POSIX_MEM
02k,12jan94,kdl  changed aio includes.
02j,10dec93,smb  added include of seqDrvP.h  for windview
02i,07dec93,dvs  added #ifdef's around POSIX includes for component releases
02h,02dec93,dvs  added includes for POSIX modules
02g,22nov93,dvs  added include of sched.h
02f,23aug93,srh  added include of private/cplusLibP.h.
02e,20oct92,pme  added vxLib.h.
02d,22sep92,rrr  added support for c++
02c,21sep92,ajm  fixes for lack of #elif support on mips
02b,20sep92,kdl  added include of private/ftpLibP.h.
02a,18sep92,jcf  major clean up.  added prototypes and #includes.
01d,04jul92,jcf  cleaned up.
01c,26may92,rrr  the tree shuffle
01b,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed VOID to void
		  -changed copyright notice
01a,05oct90,shl created.
*/

#ifndef __INCusrConfigh
#define __INCusrConfigh

#ifdef	INCLUDE_AIM_MMU_SHOW
#include "aimMmuLib.h"
#endif	/* INCLUDE_AIM_MMU_SHOW */
#include "bootLib.h"
#include "cacheLib.h"
#include "cplusLib.h"
#include "ctype.h"
#include "dbgLib.h"
#include "dosFsLib.h"
#if defined (_WRS_PAL_COPROC_LIB)
#include "private/coprocLibP.h"
#endif /* _WRS_PAL_COPROC_LIB */
#include "cbioLib.h"
#include "tarLib.h"
#include "transCbio.h"
#include "usrTransLib.h"
#include "dcacheCbio.h"
#include "dpartCbio.h"
#include "usrFdiskPartLib.h"
#include "ramDiskCbio.h"
#include "edrLib.h"
#include "private/edrLibP.h"
#include "envLib.h"
#include "errno.h"
#include "esf.h"
#include "fcntl.h"
#include "fioLib.h"
#include "fppLib.h"
#include "hookLib.h"	/* for hookLibInit() and hookShowInit() prototypes */
#include "if_bp.h"
#include "if_sl.h"
#include "intLib.h"
#include "ioLib.h"
#include "iosLib.h"
#include "iv.h"
#include "kernelLib.h"
#include "ledLib.h"
#include "loadLib.h"
#include "logLib.h"
#include "loginLib.h"
#include "math.h"
#include "memLib.h"
#include "mmuLib.h"
#include "msgQLib.h"
#include "pmLib.h"
#include "pipeDrv.h"
#include "ramDrv.h"
#include "rawFsLib.h"
#include "rebootLib.h"
#include "rpcLib.h"
#include "rtpLib.h" 		/* XXX tmp */
#include "private/kernelBaseLibP.h"	/* for kernelBaseInit() prototype */
#include "scsiLib.h"
#include "selectLib.h"
#include "semLib.h"
#include "shellLib.h"
#include "shellInterpLib.h"
#include "shellConfigLib.h"
#include <sockLib.h>
#include "spyLib.h"
#include "stdio.h"
#include "string.h"
#include "sysLib.h"
#include "sysSymTbl.h"
#include "taskHookLib.h"
#include "taskLib.h"
#include "taskVarLib.h"
#include "tickLib.h"
#include "time.h"
#include "timers.h"
#include "timexLib.h"
#include "unistd.h"
#include "unldLib.h"
#include "usrLib.h"
#include "version.h"
#include "vxLib.h"
#include "wdLib.h"
#include "rpc/rpcGbl.h"
#include "rpc/rpctypes.h"
#include "rpc/xdr.h"
#include "private/cplusLibP.h"
#include "private/excLibP.h"
#include "private/isrLibP.h"	/* for isrLibInit() and isrShowInit() prototypes */
#include "private/kernelLibP.h"
#include "private/sigLibP.h"
#include "private/vmLibP.h"
#include "private/workQLibP.h"	/* for workQInit() prototype */
#include "wdb/wdbLib.h"
#ifdef	INCLUDE_VXDBG_CPU_CONTROL
#include "private/vxdbgCpuLibP.h"
#endif	/* INCLUDE_VXDBG_CPU_CONTROL */
#include "private/intLibP.h"

#ifdef	INCLUDE_SYSDBG_FLAG
#include "private/sysDbgLibP.h"
#endif	/* INCLUDE_SYSDBG_FLAG */

#ifdef	INCLUDE_STAT_SYM_TBL
#include "private/symLibP.h"
#endif	/* INCLUDE_STAT_SYM_TBL */

#ifdef INCLUDE_SM_COMMON
#include "smLib.h"
#include "smUtilLib.h"
#endif /* INCLUDE_SM_COMMON */

#ifdef INCLUDE_SM_OBJ
#include "smObjLib.h"
#include "smDllLib.h"
#include "smMemLib.h"
#include "smNameLib.h"
#endif /* INCLUDE_SM_OBJ */

#ifdef INCLUDE_SM_NET
#include "smPktLib.h"
#endif /* INCLUDE_SM_NET */

#ifdef INCLUDE_VIRTUAL_DISK
#include "virtualDiskLib.h"
#endif	/* INCLUDE_VIRTUAL_DISK */

#ifdef	INCLUDE_POSIX_ALL

#include "aio.h"		/* INCLUDE_POSIX_AIO */
#include "aioSysDrv.h"		/* INCLUDE_POSIX_AIO_SYSDRV */
#include "private/mqPxLibP.h"	/* INCLUDE_POSIX_MQ */
#include "mqPxShow.h"		/* INCLUDE_SHOW_ROUTINES */
#include "pthread.h"		/* INCLUDE_POSIX_PTHREADS */
#include "sched.h"		/* INCLUDE_POSIX_SCHED */
#include "private/semPxLibP.h"	/* INCLUDE_POSIX_SEM */
#include "semPxShow.h"		/* INCLUDE_POSIX_SEM */
#include "sys/mman.h"		/* INCLUDE_POSIX_MEM */
#include "dirent.h"		/* INCLUDE_POSIX_DIRLIB */

#else   /* INCLUDE_POSIX_ALL */

#ifdef	INCLUDE_POSIX_AIO
#include "aio.h"
#ifdef	INCLUDE_POSIX_AIO_SYSDRV
#include "aioSysDrv.h"
#endif  /* INCLUDE_POSIX_AIO_SYSDRV */
#endif	/* INCLUDE_POSIX_AIO */

#ifdef	INCLUDE_POSIX_MQ
#include "private/mqPxLibP.h"
#ifdef	INCLUDE_SHOW_ROUTINES
#include "mqPxShow.h"
#endif  /* INCLUDE_SHOW_ROUTINES */
#endif  /* INCLUDE_POSIX_MQ */

#ifdef INCLUDE_POSIX_PTHREADS
#include "pthread.h"
#endif  /* INCLUDE_POSIX_PTHREADS */

#ifdef	INCLUDE_POSIX_SCHED
#include "sched.h"
#endif	/* INCLUDE_POSIX_SCHED */

#ifdef	INCLUDE_POSIX_SEM
#include "private/semPxLibP.h"
#ifdef	INCLUDE_SHOW_ROUTINES
#include "semPxShow.h"
#endif  /* INCLUDE_SHOW_ROUTINES */
#endif	/* INCLUDE_POSIX_SEM */

#ifdef	INCLUDE_POSIX_MEM
#include "sys/mman.h"
#endif  /* INCLUDE_POSIX_MEM */

#ifdef INCLUDE_POSIX_DIRLIB
#include "dirent.h"
#endif

#endif  /* INCLUDE_POSIX_ALL */

#if     defined(INCLUDE_SAL_CLIENT)
#include "dsi/salClient.h"
#endif  /* INCLUDE_SAL_CLIENT */

#if     defined(INCLUDE_SAL_SERVER)
#include "dsi/salServer.h"
#endif  /* INCLUDE_SAL_SERVER */

#if     defined(INCLUDE_SNS_SHOW)
#include "dsi/snsLib.h"
#endif  /* INCLUDE_SNS_SHOW */

#if     defined(INCLUDE_RBUFF)
#include "rBuffLib.h"
#endif  /* INCLUDE_RBUFF */

#if	defined(INCLUDE_WINDVIEW)
#include "wvLib.h"
#include "wvTmrLib.h"
#include "private/seqDrvP.h"
#endif  /* INCLUDE_WINDVIEW */

#if	defined(INCLUDE_TRIGGERING)
#include "private/trgLibP.h"
#endif  /* INCLUDE_TRIGGERING */

#if	defined(INCLUDE_SHELL_INTERP_CMD) && defined(INCLUDE_SHOW_ROUTINES)
#include "private/shellCmdP.h"
#endif

#if defined(INCLUDE_SOUND) && defined(INCLUDE_SB16)
#include "drv/sound/sb16drv.h"
#endif /* INCLUDE_SOUND && INCLUDE_SB16 */

#ifdef INCLUDE_PCCARD
#include "drv/pccard/csLib.h"
#ifdef INCLUDE_PCCARD_SHOW
#include "drv/pccard/csShow.h"
#endif /* INCLUDE_PCCARD_SHOW */
#endif /* INCLUDE_PCCARD */

#ifdef INCLUDE_RTP
#include "private/rtpLibP.h"
#include "private/syscallLibP.h"
#include <private/vxdbgRtpLibP.h>
#endif  /* INCLUDE_RTP */

#if	defined(INCLUDE_PROTECT_TASK_STACK) ||	\
	defined(INCLUDE_TASK_STACK_NO_EXEC) ||	\
	defined(INCLUDE_KERNEL_HARDENING)
#include "private/taskMemLibP.h"
#endif

#ifdef INCLUDE_UEFI_BOOT_SUPPORT
#include <private/efi/uefiVxWorksTypes.h>  /* UEFI types in VxWorksish form */
#include <private/efi/efiVxWorks.h> /* UEFI definitions */
#endif

#ifdef INCLUDE_SELECT
#include "private/selectLibP.h"         /* for selectLibInit() prototype */
#endif /* INCLUDE_SELECT */

#ifdef __cplusplus
extern "C" {
#endif

/* variable declarations */

extern char	edata [];		/* automatically defined by loader */
extern char	end [];			/* automatically defined by loader */

/* function declarations */

#ifdef INCLUDE_UEFI_BOOT_SUPPORT
extern void	usrInit (int startType, VxWorksOSLoaderMemoryMapHeader *pUefiMemAddress, UINT32 *pUefiAcpiAddress );
#else /* not defined INCLUDE_UEFI_BOOT_SUPPORT */
extern void	usrInit (int startType);
#endif /* #ifdef INCLUDE_UEFI_BOOT_SUPPORT */

extern void	usrRoot (char * pMemPoolStart, unsigned memPoolSize);
extern void	usrClock (void);
extern STATUS	usrScsiConfig (void);
extern STATUS	usrFdConfig (int type, int drive, char * fileName);
extern STATUS	usrIdeConfig (int drive, char * fileName);
extern STATUS	usrAtaConfig (int ctrl, int drive, char * fileName);
extern void	devSplit (char * fullFileName, char * devName);
extern STATUS	usrNetInit (char * bootString);
extern STATUS	checkInetAddrField (char * pInetAddr, BOOL subnetMaskOK);
extern STATUS	netLoadSymTbl (void);
extern STATUS	usrBootLineCrack (char * bootString, BOOT_PARAMS * pParams);
extern void	usrBootLineInit (int startType);
extern STATUS	usrBpInit (char * devName, int unitNum, u_long startAddr);
extern void	usrDemo (void);
extern STATUS	usrEdrInit (void);
extern STATUS	usrSlipInit (char * pBootDev, int unitNum, char * localAddr,
                             char * peerAddr);

#ifdef  INCLUDE_SM_OBJ
extern STATUS	usrSmObjInit (char * bootString);
#endif  /* INCLUDE_SM_OBJ */

extern STATUS	usrWindMPInit (char * bootString);
extern void	usrStartupScript (char * fileName);
extern STATUS	usrStrmInit (void);
extern STATUS	usrSnmpdInit (void);
extern STATUS	wdbConfig (void);

#if (defined(INCLUDE_STANDALONE_SYM_TBL) && (CPU_FAMILY == ARM) && ARM_THUMB)
extern STATUS	thumbSymTblAdd (SYMTAB_ID, SYMBOL_ID);
#endif

extern STATUS	usrFsShellCmdInit ();
extern STATUS	usrRtpLibInit ();

#ifdef INCLUDE_LOADER
extern STATUS	moduleShellCmdInit (void);
extern STATUS   loadLibInit (BOOL storeAbsSyms);
#endif

#ifdef INCLUDE_UNLOADER
extern STATUS	unloadShellCmdInit (void);
#endif

#ifdef INCLUDE_SHELL_HISTORY_FILE
extern STATUS	histShellCmdInit (void);
#endif

#ifdef INCLUDE_DEBUG
extern STATUS	dbgShellCmdInit (void);
#endif

extern STATUS	symShellCmdInit (void);
extern STATUS	taskShellCmdInit (void);

#ifdef	INCLUDE_AIM_MMU_CONFIG
extern void	usrAimMmuConfig (void);
#endif	/* INCLUDE_AIM_MMU_CONFIG */

#ifdef __cplusplus
}
#endif

#endif /* __INCusrConfigh */
