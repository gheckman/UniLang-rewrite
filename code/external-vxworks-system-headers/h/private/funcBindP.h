/* funcBindP.h - private function binding header */

/*
 * Copyright (c) 1992-1998, 2000-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
-------------------- 
06d,07feb12,pad  Adjusted declarations of _func_rtpSigExcKill and
		 _func_sigExcKill after the routine's signatures changed.
06r,02nov11,swu  remove _func_fppTaskRegsShow from funcBind. (WIND00245382)
06q,17jan11,vhe  Removed pWvNetEventMap from funcBind.c (WIND00240778)
06p,05jul10,liu  declare _func_fppTaskRegsShow. (WIND00192339)
06o,04nov10,swg  Removed  _procNumWasSet(to fix WIND00237118).
06n,22oct10,h_x  Removed _func_remCurIdGet & _func_remCurIdSet.
06m,22oct10,h_x  Removed _func_netLsByName 
06l,18oct10,jpb  Removed Fast UDP function pointers.
06k,30sep10,jpb  Removed exception handling function pointers
06j,29sep10,jpb  Removed evtAction and placed in eventP.h
06k,29sep10,h_x  Remove the pointers related with vxcoreip and vxcompat
06j,28sep10,jpb  Removed memPartClassId & memSysPartId.
06i,25sep10,jxu  Removed _func_ioTaskStdSet, _func_ioGlobalStdGet and
		 _func_consoleOut.
06h,21sep10,jpb  Removed _func_SysBootParamsGet.
06g,19sep10,fan  removed _func_fioFltFormatRtn, _func_fioFltScanRtn and
                 _func_fclose for LP64 mode
06g,13sep10,jpb  Removed func ptrs.
06f,02sep10,jxu  Moved _func_lf_advlock, _func_iosRtpIoTableSizeSet, 
                 _func_iosRtpIoTableSizeGet, select related and utf related 
                 function pointers to respective xxFuncBind.c, and removed 
                 sfsFmtRtn.
06e,01sep10,jpb  Removed func ptrs.
06d,09jun10,jxu  LP64: changed type of _func_objRtpObjEachHook to fully 
                 qualified function pointer instead of FUNCPTR and included
                 objLibP.h.
06m,21jan10,zly  added _func_objRtpObjEachHook for WIND00196335
06l,26may10,rec  remove cpu power management functions
06k,24may10,pad  Added a comment regarding the obsolete nature of this file.
06j,17may10,jpb  Removed taskPx functions.
06i,29apr10,pad  Moved extern C statement after include statements.
06h,02apr10,jpb  Removed a number of func pointers to its respective private
                 file.
06f,09apr10,rlp  Moved VxDBG function pointers to vxdbgLibP.h.
06h,02apr10,rec  add func_cpuPwrPriorityRaise
06g,30mar10,h_k  moved VxBus Dynamic interrupt function pointers to
                 vxbIntDynaCtlrLib.h.
06f,02mar10,cww  Moved rtpSig pointers to rtpSigLibP.h
06f,10jan10,tcr  move SV function pointers out
06e,12jan10,zl   moved page manager function pointers to pgMgrLibP.h
06d,15dec09,cww  Moved remaining rtp pointers to rtpLibP and taskMemLibP
06c,03dec09,cww  Moved rtp-related pointers to rtpfuncBind and taskMemFuncBind
06b,01nov09,hps  merge fix for defect WIND00059482 (it also fixes WIND00182301)
06q,21oct09,cww  Moved _func_windTickAnnounceHook to windLibP.h
06p,25sep09,v_r  Moved loadLib, unldLib and moduleLib function pointers to
                 their respective private headers.
06o,23sep09,jpb  Moved pxCpuTimerLib function pointers to timerLibP.h.
06n,10sep09,cww  Moved sigLib function pointers to sigLibP.h
06m,26aug09,cww  Moved envLib function pointers to envLibP.h
06l,01jul09,jmp  Moved spyLib function pointers to spyLibP.h.
		 Moved tipLib function pointers to tipLibP.h.
		 Moved shell function pointers to shellLibP.h.
06k,22jun09,jmp  Moved symLib function pointers to symLibP.h.
06j,04jun09,cww  Removed fppLib and coproc routines
06i,11may09,pcs  Updated all _func_eventXXX to fully qualified function
                 pointers.
06i,06may09,jpb  _func_logMsg() now a fully qualified function pointer
06h,15apr09,mcm  Updates for the LP64 data model
06g,14apr09,v_r   _func_shellExcPrint now a fully qualified function pointer.
06f,27mar09,zl   changed job deferral fptrs to fully qualified. Removed 
                 unused _func_evtLogCpc.
06e,17mar09,jmp  Updated symLib function pointers.
06d,15mar09,zl   Moved task create/delete hook installers to taskLibP.h. 
                 Removed _func_regsShow. Changed _func_taskMemCtxSwitch
                 to fully qualified function pointer.
06c,05mar09,cww  LP64 update
06b,19feb09,zl   moved object management function pointers to objLib.
06a,11spe08,v_r  Added tip library function pointer (req CQ:WIND00114857).
05z,03sep08,jpb  Renamed VSB header file
05y,19aug08,tcr  add dataCollector function list
05x,25apr08,tcr  remove unneeded WV funcptrs, add SV logging rtn
05w,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
05v,19mar08,v_r  Added RTP debug command facility function pointers (req
                 CQ:WIND00004496).
05u,30oct07,tor  add vxbus legacy interrupt support
05t,01aug07,act  io footprint work, from pcm
05s,25jul07,rlp  Added _func_shellBpByIdRemove function pointer
		 (Defect CQ:WIND00099168).
05r,12jul07,mmi  WIND0097363: added _func_cpuPwrXX hooks
05p,27jun07,lei  added _func_pxCpuTimerCancelVerify for SMP.
05o,19jun07,dtr  Aupdate for vxBus function ptrs.
05n,09may07,v_r  Added rtpSymTblIdGet() function pointer.
05m,23aug06,pcm  added UTF function pointers
05l,10apr07,zl   moved _func_isr* to isrLibP.h
05k,31mar07,jpb  Added _func_rtpVarAdd.
05j,13mar07,rlp  Extend array of function pointers for VxDBG library.
05i,20dec06,tcr  add funcptrs for System Viewer SMP
05h,01mar07,rlp  Added array of function pointers for VxDBG library.
05g,22nov06,v_r  Add new symLib function pointers replacing the deprecated
                 ones (req CQ:WIND00068611).
05f,20oct06,rlp  Added more prototype for vxdbg library (REQ00007655).
05e,21aug06,jpb  Removed _func_rtpPthreadSetCancelType references 
                 (WIND00062557)
05d,10jul06,gls  added _func_sigeventInit
05c,06jul06,jln  added _func_pxSSthreadStateInit and _func_pxSSThreadIntHook
05b,19jun06,rlg  CFE upgrade for bcm1250
05a,12jun06,pcm  made modifications for pthread cancellation points
04z,22feb06,jln  added _func_pxCpuTimerCreate/_func_taskPxAttrCreate
04y,31jan06,jln  added _func_pxCpuTimerStart/Cancel/Delete
04x,07feb06,gls  added _func_signalMmanHook
04w,29sep05,kk   removed deprecated message for excJobAdd (SPR# 111818)
04v,27sep05,kk   added _func_fioFltFormatRtn and _func_fioFltScanRtn for
                 fioLib
04u,16aug05,gls  added objOwnerLibfunction pointers
04t,12aug05,pes  Add _func_dspProbe (conditional if _WRS_DSP_SUPPORT defined)
04s,08jul05,jln  added _func_windTickAnnounceHook
04r,25jun05,jln  Added _func_taskPxAttrSet/Get
04q,08jun05,yvp  Reverted excExcepHook.
04p,07jun05,yvp  Updated copyright. #include now with angle-brackets.
04o,07jun05,yvp  Renamed _func_jobExcAdd to _func_jobTaskWorkAdd.
04n,27apr05,yvp  Added _func_classListUnlock and _func_classListLock.
04m,26apr05,yvp  Removed _func_eventInit and _func_eventRsrcShow.
04l,06apr05,yvp  Added _func_event_* - decouple eventLib from sem's & msgQ's.
04k,18mar05,yvp  Added _func_excExcepHook and _func_exit.
04j,05feb05,dlk  Added _func_scMemValidate.
04i,10jan05,bpn  Added _func_dbgRtpStop, _func_dbgRtpCont entries.
04h,16dec04,yvp  Added _func_ioGlobalStdGet, _func_consoleOut & _func_event_*.
                 Added _func_isrCreate, _func_isrDelete.
		 Moved _func_isrDispatcher here from isrLib.
04g,23nov04,gls  added _func_rtpSig entries
04f,03nov04,hya  added _func_sigfillset
04e,06oct04,aeg  added _func_jobExcAdd
04d,30sep04,lei  added jobLibTaskInstalled
04c,29sep04,kk   added _func_symTblShutdown & _func_symRegister
04b,27sep04,gls  added _func_sdUnmapAll
04a,21sep04,zl   added __rta_longjmp
03z,18sep04,jn   Move toward shared code on host and target
03y,04sep04,dbt  Fixed _func_excJobAdd declaration.
03x,02sep04,ans  Added _func_jobAdd and deprecated _func_excJobAdd
03w,30aug04,dcc  Added declaration of _func_objHandleToObjId.
03v,26aug04,ymz  Added declaration of _func_rtpHandleIdGet.
03v,30aug04,jn   Add function bindings for unldLib
03w,23sep04,ann  Merge networking: Removed fastUdpInitialized var.
03v,23aug04,bpn  Added _func_symEach, _func_symFindByName (SPR#100715).
03u,04aug04,sru  Added declaration of _func_aimMmuLockRegionsImport.
03t,11jun04,pad  Added declaration of _func_rtpPthreadSetCancelType.
03s,08jun04,md   added loader function bindings
03r,17may04,pad  Added declaration of _func_loadRtpSymsPolicyOverride.
03q,14may04,mil  Added _func_mmuCacheFlushLoadAdrsGet.
03p,07may04,pad  Added declarations of func_rtpShlSymbolsRegister and
                 _func_rtpShlSymbolsUnregister.
03p,30apr04,pad  Added declaration of _func_shlRtpInfoGet.
03o,21apr04,cjj  Added _func_workQDbgTextDump and cleaned up file.
03n,16apr04,kk   added _func_shlRtpDeleteAll
03m,16apr04,yvp  Added FUNCPTRS for rtpHookLib functions.
03l,09apr04,ans  added _func_rtpTaskSigCheck
03k,07apr04,bpn  Addded _func_shellExcPrint.
03j,29mar04,jn   Add func pointer to allow use of kernel .o loader 
                 without rtp loader
03i,17mar04,pad  Added external declaration for _func_envGet.
03h,19feb04,yp   adding _func_virtExtraMapInfoGet
03g,16dec03,syy  Added func ptr _func_evtLogOBinary
03f,26nov03,jn   Add _func_rtpIdVerify
03e,19nov03,kk   remove rtpOrEdrInstalled
03d,13nov03,yp   added declaration for _func_virtSegInfoGet
03c,10nov03,tam  added _func_pgMgrPageAlloc _func_pgMgrPageMap
                 _func_pgMgrPageFree
03b,19sep03,aim  added _func_edrEvt
03a,10sep03,dbs  remove edrErrorInject funcptr
02z,06nov03,nrj  added signal block func for RTP
02y,21oct03,nrj  added RTP task exception signal functions
02x,16oct03,nrj  added missing RTP signal funcs
02w,16oct03,nrj  added support for RTP signal functions
02k,03nov03,tcr  add WindView syscall logging rtn
02j,12sep03,tcr  remove wvObjIsEnabled
02i,02sep03,tcr  add funcptr for WindView
02h,22aug03,dbs  ED&R merge to baseline
02g,18aug03,dbs  add _func_edrErrorInject
02f,29jul03,dbs  add _func_regsShow
02v,19sep03,pad  Added declaration for _func_rtpSpawn
02u,19sep03,kk   update comment on rtpOrEdrInstalled
02t,12sep03,kk   added variable rtpOrEdrInstalled for scalability
02s,22aug03,dbs  ED&R merge to baseline
02r,18aug03,dbs  add _func_edrErrorInject
02q,29jul03,dbs  add _func_regsShow
02p,01aug03,pch  support coprocessor on PPC604/AltiVec for PPC32
02o,10apr03,pes  PAL Coprocessor Abstraction
02n,22jul03,pad  Added external declaration for _func_rtpDelete.
02m,20mar03,wap  added m2If64BitCounters (SPR #86776)
02l,28feb03,bpn  Changed _func_bdall to _func_dbgTaskBpRemove.
02k,13jan03,rae  Merged from velocecp branch
02j,21nov02,pch  SPR 84107: add _func_altivecTaskRegsGet and _func_altivecProbe
02g,09jun03,dtr  CP1 Merge.
02f,03sep02,dtr  ADDED _func_speTaskRegsShow.
02i,26mar02,pai  added _func_sseTaskRegsShow (SPR 74103).
02h,09nov01,jn   added internal API for symLib
02g,29oct01,gls  added pthread support
02f,26oct01,brk  added _func_selPtyAdd & _func_selPtyDelete (SPR 65498)
02e,21sep01,aeg  added _func_selWakeupListTerm.
02d,16mar01,pcs  ADDED _func_altivecTaskRegsShow
02c,28feb00,frf  Add SH support for T2
02b,08aug98,kab  added _func_dspRegsListHook, _func_dspMregsHook.
02a,23jul98,mem  added _func_dspTaskRegsShow
01z,10aug98,pr   added WindView function pointers for i960
01y,15apr98,cth  added definition of _func_evtLogReserveTaskName
01x,08apr98,pr   added _func_evtLogT0_noInt. Set evtAction as UINT32
01w,13dec97,pr   moved some variables from eventP.h
		 removed some windview 1.0 variables
01v,13nov97,cth  removed evtBuf and scrPad references for WV2.0
01u,24jun97,pr   added evtInstMode
01t,09oct97,ms   added _func_ioTaskStdSet
01s,21feb97,tam  added _dbgDsmInstRtn
01r,08jul96,pr   added _func_evtLogT1_noTS
01q,12may95,p_m  added _func_printErr, _func_symFindByValue, _func_spy*
                       _func_taskCreateHookAdd and _func_taskDeleteHookAdd.
01p,24jan94,smb  added function pointers for windview portable kernel.
01o,10dec93,smb  added function pointers for windview.
01n,05sep93,jcf  added _remCurId[SG]et.
01m,20aug93,jmm  added _bdall
01l,22jul93,jmm  added _netLsByName
01k,13feb93,kdl  added _procNumWasSet.
01j,13nov92,jcf  added _func_logMsg.
01i,22sep92,rrr  added support for c++
01h,20sep92,kdl  added _func_ftpLs, ftpErrorSuppress.
01g,31aug92,rrr  added _func_sigprocmask
01f,23aug92,jcf  added _func_sel*, _func_excJobAdd,_func_memalign,_func_valloc
01e,02aug92,jcf  added/changed _exc*.
01d,29jul92,jcf  added _func_fclose
01c,29jul92,rrr  added _func_sigExcKill, _func_sigTimeoutRecalc,
                 _func_excEsfCrack and _func_excSuspend.
01b,19jul92,pme  added _func_smObjObjShow.
01a,04jul92,jcf  written
*/

/*
*******************************************************************************
ATTENTION: this file is now OBSOLETE and NO new declarations of generic
function pointers should be added here. Instead, declarations of fully-qualified
function pointers should be added in private header files related to the feature
they describe.
*******************************************************************************
*/

#ifndef __INCfuncBindPh
#define __INCfuncBindPh

#include <vxWorks.h>
#include <vsbConfig.h>
#include <stdarg.h>
#include <private/objLibP.h>

#ifdef __cplusplus
extern "C" {
#endif


extern int	 (*_func_printErr)(const char *, ...);

#ifdef __cplusplus
}
#endif

#endif /* __INCfuncBindPh */
