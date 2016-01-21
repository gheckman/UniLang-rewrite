
/* THIS FILE IS AUTO_GENERATED. PLEASE DO NOT EDIT. */

extern long _exitSc(void *);
extern long _creatSc(void *);
extern long _openSc(void *);
extern long _closeSc(void *);
extern long _readSc(void *);
extern long _writeSc(void *);
extern long _ioctlSc(void *);
extern long dupSc(void *);
extern long dup2Sc(void *);
extern long pipeSc(void *);
extern long removeSc(void *);
extern long selectSc(void *);
extern long socketSc(void *);
extern long bindSc(void *);
extern long listenSc(void *);
extern long acceptSc(void *);
extern long connectSc(void *);
extern long sendtoSc(void *);
extern long sendSc(void *);
extern long sendmsgSc(void *);
extern long recvfromSc(void *);
extern long recvSc(void *);
extern long recvmsgSc(void *);
extern long setsockoptSc(void *);
extern long getsockoptSc(void *);
extern long getsocknameSc(void *);
extern long getpeernameSc(void *);
extern long shutdownSc(void *);
extern long mmapSc(void *);
extern long munmapSc(void *);
extern long mprotectSc(void *);
extern long killSc(void *);
extern long _pauseSc(void *);
extern long sigpendingSc(void *);
extern long sigprocmaskSc(void *);
extern long _sigqueueSc(void *);
extern long _sigsuspendSc(void *);
extern long _sigtimedwaitSc(void *);
extern long _sigactionSc(void *);
extern long _sigreturnSc(void *);
extern long chdirSc(void *);
extern long _getcwdSc(void *);
extern long getpidSc(void *);
extern long getppidSc(void *);
extern long _waitpidSc(void *);
extern long sysctlSc(void *);
extern long _schedPxInfoGetSc(void *);
extern long sigaltstackSc(void *);
extern long unlinkSc(void *);
extern long linkSc(void *);
extern long _fsyncSc(void *);
extern long _fdatasyncSc(void *);
extern long renameSc(void *);
extern long fpathconfSc(void *);
extern long pathconfSc(void *);
extern long accessSc(void *);
extern long chmodSc(void *);
extern long pxTraceCreationSc(void *);
extern long pxTraceCtlSc(void *);
extern long pxTraceEventSc(void *);
extern long pxTraceEventNameQuerySc(void *);
extern long pxTraceLogSc(void *);
extern long pxTraceEventGetSc(void *);
extern long eventReceiveSc(void *);
extern long eventSendSc(void *);
extern long eventCtlSc(void *);
extern long msgQSendSc(void *);
extern long msgQReceiveSc(void *);
extern long _msgQOpenSc(void *);
extern long objDeleteSc(void *);
extern long objInfoGetSc(void *);
extern long _semTakeSc(void *);
extern long _semGiveSc(void *);
extern long _semOpenSc(void *);
extern long semCtlSc(void *);
extern long _taskOpenSc(void *);
extern long taskCtlSc(void *);
extern long taskDelaySc(void *);
extern long rtpSpawnSc(void *);
extern long rtpInfoGetSc(void *);
extern long taskKillSc(void *);
extern long _taskSigqueueSc(void *);
extern long _timer_openSc(void *);
extern long timerCtlSc(void *);
extern long pxOpenSc(void *);
extern long pxCloseSc(void *);
extern long pxUnlinkSc(void *);
extern long pxCtlSc(void *);
extern long pxMqReceiveSc(void *);
extern long pxMqSendSc(void *);
extern long pxSemWaitSc(void *);
extern long pxSemPostSc(void *);
extern long pipeDevCreateSc(void *);
extern long pipeDevDeleteSc(void *);
extern long _sdCreateSc(void *);
extern long _sdOpenSc(void *);
extern long sdDeleteSc(void *);
extern long sdMapSc(void *);
extern long sdUnmapSc(void *);
extern long sdProtectSc(void *);
extern long _edrErrorInjectSc(void *);
extern long edrFlagsGetSc(void *);
extern long wvEventSc(void *);
extern long rtpVarAddSc(void *);
extern long sdInfoGetSc(void *);
extern long _shlOpenSc(void *);
extern long _shlUnlockSc(void *);
extern long _shlCloseSc(void *);
extern long _shlGetSc(void *);
extern long _shlPutSc(void *);
extern long objUnlinkSc(void *);
extern long getprlimitSc(void *);
extern long setprlimitSc(void *);
extern long _mctlSc(void *);
extern long _taskOpenWithGuardSc(void *);
extern long clockCtlSc(void *);
extern long _semRTakeSc(void *);
extern long _semWTakeSc(void *);
extern long _semExchangeSc(void *);
extern long wvRtpEventSc(void *);
extern long _taskTcbCurrentGetSc(void *);

_WRS_DATA_ALIGN_BYTES(16) SYSCALL_RTN_TBL_ENTRY STANDARDRtnTbl [] = {
/*0*/	SYSCALL_DESC_ENTRY (_exitSc,    "_exit", 1),
/*1*/	SYSCALL_DESC_ENTRY (_creatSc,    "_creat", 2),
/*2*/	SYSCALL_DESC_ENTRY (_openSc,    "_open", 3),
/*3*/	SYSCALL_DESC_ENTRY (_closeSc,    "_close", 1),
/*4*/	SYSCALL_DESC_ENTRY (_readSc,    "_read", 3),
/*5*/	SYSCALL_DESC_ENTRY (_writeSc,    "_write", 3),
/*6*/	SYSCALL_DESC_ENTRY (_ioctlSc,    "_ioctl", 3),
/*7*/	SYSCALL_DESC_ENTRY (dupSc,    "dup", 1),
/*8*/	SYSCALL_DESC_ENTRY (dup2Sc,    "dup2", 2),
/*9*/	SYSCALL_DESC_ENTRY (pipeSc,    "pipe", 1),
/*10*/	SYSCALL_DESC_ENTRY (removeSc,    "remove", 1),
/*11*/	SYSCALL_DESC_ENTRY (selectSc,    "select", 5),
#if defined(INCLUDE_SC_SOCKLIB)
/*12*/	SYSCALL_DESC_ENTRY (socketSc,    "socket", 3),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_SC_SOCKLIB)
/*13*/	SYSCALL_DESC_ENTRY (bindSc,    "bind", 3),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_SC_SOCKLIB)
/*14*/	SYSCALL_DESC_ENTRY (listenSc,    "listen", 2),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_SC_SOCKLIB)
/*15*/	SYSCALL_DESC_ENTRY (acceptSc,    "accept", 3),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_SC_SOCKLIB)
/*16*/	SYSCALL_DESC_ENTRY (connectSc,    "connect", 3),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_SC_SOCKLIB)
/*17*/	SYSCALL_DESC_ENTRY (sendtoSc,    "sendto", 6),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_SC_SOCKLIB)
/*18*/	SYSCALL_DESC_ENTRY (sendSc,    "send", 4),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_SC_SOCKLIB)
/*19*/	SYSCALL_DESC_ENTRY (sendmsgSc,    "sendmsg", 3),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_SC_SOCKLIB)
/*20*/	SYSCALL_DESC_ENTRY (recvfromSc,    "recvfrom", 6),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_SC_SOCKLIB)
/*21*/	SYSCALL_DESC_ENTRY (recvSc,    "recv", 4),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_SC_SOCKLIB)
/*22*/	SYSCALL_DESC_ENTRY (recvmsgSc,    "recvmsg", 3),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_SC_SOCKLIB)
/*23*/	SYSCALL_DESC_ENTRY (setsockoptSc,    "setsockopt", 5),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_SC_SOCKLIB)
/*24*/	SYSCALL_DESC_ENTRY (getsockoptSc,    "getsockopt", 5),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_SC_SOCKLIB)
/*25*/	SYSCALL_DESC_ENTRY (getsocknameSc,    "getsockname", 3),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_SC_SOCKLIB)
/*26*/	SYSCALL_DESC_ENTRY (getpeernameSc,    "getpeername", 3),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_SC_SOCKLIB)
/*27*/	SYSCALL_DESC_ENTRY (shutdownSc,    "shutdown", 2),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
/*28*/	SYSCALL_DESC_ENTRY (mmapSc,    "mmap", 8),
/*29*/	SYSCALL_DESC_ENTRY (munmapSc,    "munmap", 2),
/*30*/	SYSCALL_DESC_ENTRY (mprotectSc,    "mprotect", 3),
/*31*/	SYSCALL_DESC_ENTRY (killSc,    "kill", 2),
/*32*/	SYSCALL_DESC_ENTRY (_pauseSc,    "_pause", 0),
/*33*/	SYSCALL_DESC_ENTRY (sigpendingSc,    "sigpending", 1),
/*34*/	SYSCALL_DESC_ENTRY (sigprocmaskSc,    "sigprocmask", 3),
/*35*/	SYSCALL_DESC_ENTRY (_sigqueueSc,    "_sigqueue", 4),
/*36*/	SYSCALL_DESC_ENTRY (_sigsuspendSc,    "_sigsuspend", 1),
/*37*/	SYSCALL_DESC_ENTRY (_sigtimedwaitSc,    "_sigtimedwait", 3),
/*38*/	SYSCALL_DESC_ENTRY (_sigactionSc,    "_sigaction", 4),
/*39*/	SYSCALL_DESC_ENTRY (_sigreturnSc,    "_sigreturn", 0),
/*40*/	SYSCALL_DESC_ENTRY (chdirSc,    "chdir", 1),
/*41*/	SYSCALL_DESC_ENTRY (_getcwdSc,    "_getcwd", 2),
/*42*/	{ NULL, },
/*43*/	SYSCALL_DESC_ENTRY (getpidSc,    "getpid", 0),
/*44*/	SYSCALL_DESC_ENTRY (getppidSc,    "getppid", 0),
/*45*/	SYSCALL_DESC_ENTRY (_waitpidSc,    "_waitpid", 3),
#if defined(INCLUDE_SC_SYSCTL)
/*46*/	SYSCALL_DESC_ENTRY (sysctlSc,    "sysctl", 6),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_RTP_POSIX_PSE52)
/*47*/	SYSCALL_DESC_ENTRY (_schedPxInfoGetSc,    "_schedPxInfoGet", 2),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
/*48*/	SYSCALL_DESC_ENTRY (sigaltstackSc,    "sigaltstack", 2),
/*49*/	SYSCALL_DESC_ENTRY (unlinkSc,    "unlink", 1),
/*50*/	SYSCALL_DESC_ENTRY (linkSc,    "link", 2),
/*51*/	SYSCALL_DESC_ENTRY (_fsyncSc,    "_fsync", 1),
/*52*/	SYSCALL_DESC_ENTRY (_fdatasyncSc,    "_fdatasync", 1),
/*53*/	SYSCALL_DESC_ENTRY (renameSc,    "rename", 2),
/*54*/	SYSCALL_DESC_ENTRY (fpathconfSc,    "fpathconf", 2),
/*55*/	SYSCALL_DESC_ENTRY (pathconfSc,    "pathconf", 2),
/*56*/	SYSCALL_DESC_ENTRY (accessSc,    "access", 2),
/*57*/	SYSCALL_DESC_ENTRY (chmodSc,    "chmod", 2),
#if defined(INCLUDE_POSIX_TRACE)
/*58*/	SYSCALL_DESC_ENTRY (pxTraceCreationSc,    "pxTraceCreation", 5),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_POSIX_TRACE)
/*59*/	SYSCALL_DESC_ENTRY (pxTraceCtlSc,    "pxTraceCtl", 7),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_POSIX_TRACE)
/*60*/	SYSCALL_DESC_ENTRY (pxTraceEventSc,    "pxTraceEvent", 7),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_POSIX_TRACE)
/*61*/	SYSCALL_DESC_ENTRY (pxTraceEventNameQuerySc,    "pxTraceEventNameQuery", 7),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_POSIX_TRACE)
/*62*/	SYSCALL_DESC_ENTRY (pxTraceLogSc,    "pxTraceLog", 4),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_POSIX_TRACE)
/*63*/	SYSCALL_DESC_ENTRY (pxTraceEventGetSc,    "pxTraceEventGet", 8),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
};
#define STANDARDRtnTblNum (sizeof(STANDARDRtnTbl)/sizeof(STANDARDRtnTbl[0]))

_WRS_DATA_ALIGN_BYTES(16) SYSCALL_RTN_TBL_ENTRY VXWORKSRtnTbl [] = {
/*0*/	SYSCALL_DESC_ENTRY (eventReceiveSc,    "eventReceive", 4),
/*1*/	SYSCALL_DESC_ENTRY (eventSendSc,    "eventSend", 2),
/*2*/	SYSCALL_DESC_ENTRY (eventCtlSc,    "eventCtl", 4),
#if defined(INCLUDE_MSG_Q)
/*3*/	SYSCALL_DESC_ENTRY (msgQSendSc,    "msgQSend", 5),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_MSG_Q)
/*4*/	SYSCALL_DESC_ENTRY (msgQReceiveSc,    "msgQReceive", 4),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_MSG_Q)
/*5*/	SYSCALL_DESC_ENTRY (_msgQOpenSc,    "_msgQOpen", 6),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
/*6*/	SYSCALL_DESC_ENTRY (objDeleteSc,    "objDelete", 2),
/*7*/	SYSCALL_DESC_ENTRY (objInfoGetSc,    "objInfoGet", 4),
/*8*/	SYSCALL_DESC_ENTRY (_semTakeSc,    "_semTake", 2),
/*9*/	SYSCALL_DESC_ENTRY (_semGiveSc,    "_semGive", 1),
/*10*/	SYSCALL_DESC_ENTRY (_semOpenSc,    "_semOpen", 6),
/*11*/	SYSCALL_DESC_ENTRY (semCtlSc,    "semCtl", 4),
/*12*/	SYSCALL_DESC_ENTRY (_taskOpenSc,    "_taskOpen", 1),
/*13*/	SYSCALL_DESC_ENTRY (taskCtlSc,    "taskCtl", 4),
/*14*/	SYSCALL_DESC_ENTRY (taskDelaySc,    "taskDelay", 1),
/*15*/	SYSCALL_DESC_ENTRY (rtpSpawnSc,    "rtpSpawn", 7),
/*16*/	SYSCALL_DESC_ENTRY (rtpInfoGetSc,    "rtpInfoGet", 2),
/*17*/	SYSCALL_DESC_ENTRY (taskKillSc,    "taskKill", 2),
/*18*/	SYSCALL_DESC_ENTRY (_taskSigqueueSc,    "_taskSigqueue", 4),
#if defined(INCLUDE_POSIX_TIMERS)
/*19*/	SYSCALL_DESC_ENTRY (_timer_openSc,    "_timer_open", 5),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_POSIX_TIMERS)
/*20*/	SYSCALL_DESC_ENTRY (timerCtlSc,    "timerCtl", 4),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_POSIX_SEM) || defined(INCLUDE_POSIX_MQ)
/*21*/	SYSCALL_DESC_ENTRY (pxOpenSc,    "pxOpen", 4),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_POSIX_SEM) || defined(INCLUDE_POSIX_MQ)
/*22*/	SYSCALL_DESC_ENTRY (pxCloseSc,    "pxClose", 1),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_POSIX_SEM) || defined(INCLUDE_POSIX_MQ)
/*23*/	SYSCALL_DESC_ENTRY (pxUnlinkSc,    "pxUnlink", 2),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_POSIX_SEM) || defined(INCLUDE_POSIX_MQ)
/*24*/	SYSCALL_DESC_ENTRY (pxCtlSc,    "pxCtl", 4),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_POSIX_MQ)
/*25*/	SYSCALL_DESC_ENTRY (pxMqReceiveSc,    "pxMqReceive", 6),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_POSIX_MQ)
/*26*/	SYSCALL_DESC_ENTRY (pxMqSendSc,    "pxMqSend", 6),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_POSIX_SEM)
/*27*/	SYSCALL_DESC_ENTRY (pxSemWaitSc,    "pxSemWait", 3),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_POSIX_SEM)
/*28*/	SYSCALL_DESC_ENTRY (pxSemPostSc,    "pxSemPost", 1),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_PIPES)
/*29*/	SYSCALL_DESC_ENTRY (pipeDevCreateSc,    "pipeDevCreate", 3),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_PIPES)
/*30*/	SYSCALL_DESC_ENTRY (pipeDevDeleteSc,    "pipeDevDelete", 2),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_SHARED_DATA)
/*31*/	SYSCALL_DESC_ENTRY (_sdCreateSc,    "_sdCreate", 8),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_SHARED_DATA)
/*32*/	SYSCALL_DESC_ENTRY (_sdOpenSc,    "_sdOpen", 8),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_SHARED_DATA)
/*33*/	SYSCALL_DESC_ENTRY (sdDeleteSc,    "sdDelete", 2),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_SHARED_DATA)
/*34*/	SYSCALL_DESC_ENTRY (sdMapSc,    "sdMap", 3),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_SHARED_DATA)
/*35*/	SYSCALL_DESC_ENTRY (sdUnmapSc,    "sdUnmap", 2),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_SHARED_DATA)
/*36*/	SYSCALL_DESC_ENTRY (sdProtectSc,    "sdProtect", 2),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
/*37*/	SYSCALL_DESC_ENTRY (_edrErrorInjectSc,    "_edrErrorInject", 6),
/*38*/	SYSCALL_DESC_ENTRY (edrFlagsGetSc,    "edrFlagsGet", 0),
/*39*/	{ NULL, },
#if defined(INCLUDE_WINDVIEW)
/*40*/	SYSCALL_DESC_ENTRY (wvEventSc,    "wvEvent", 3),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
/*41*/	SYSCALL_DESC_ENTRY (rtpVarAddSc,    "rtpVarAdd", 2),
#if defined(INCLUDE_SHARED_DATA)
/*42*/	SYSCALL_DESC_ENTRY (sdInfoGetSc,    "sdInfoGet", 2),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_SHL)
/*43*/	SYSCALL_DESC_ENTRY (_shlOpenSc,    "_shlOpen", 2),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_SHL)
/*44*/	SYSCALL_DESC_ENTRY (_shlUnlockSc,    "_shlUnlock", 1),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_SHL)
/*45*/	SYSCALL_DESC_ENTRY (_shlCloseSc,    "_shlClose", 1),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_SHL)
/*46*/	SYSCALL_DESC_ENTRY (_shlGetSc,    "_shlGet", 2),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
#if defined(INCLUDE_SHL)
/*47*/	SYSCALL_DESC_ENTRY (_shlPutSc,    "_shlPut", 2),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
/*48*/	SYSCALL_DESC_ENTRY (objUnlinkSc,    "objUnlink", 2),
/*49*/	SYSCALL_DESC_ENTRY (getprlimitSc,    "getprlimit", 4),
/*50*/	SYSCALL_DESC_ENTRY (setprlimitSc,    "setprlimit", 4),
/*51*/	SYSCALL_DESC_ENTRY (_mctlSc,    "_mctl", 4),
/*52*/	SYSCALL_DESC_ENTRY (_taskOpenWithGuardSc,    "_taskOpenWithGuard", 1),
/*53*/	SYSCALL_DESC_ENTRY (clockCtlSc,    "clockCtl", 4),
/*54*/	SYSCALL_DESC_ENTRY (_semRTakeSc,    "_semRTake", 2),
/*55*/	SYSCALL_DESC_ENTRY (_semWTakeSc,    "_semWTake", 2),
/*56*/	SYSCALL_DESC_ENTRY (_semExchangeSc,    "_semExchange", 3),
#if defined(INCLUDE_WINDVIEW)
/*57*/	SYSCALL_DESC_ENTRY (wvRtpEventSc,    "wvRtpEvent", 3),
#else
	SYSCALL_DESC_ENTRY (NULL, NULL, 0),
#endif
/*58*/	SYSCALL_DESC_ENTRY (_taskTcbCurrentGetSc,    "_taskTcbCurrentGet", 0),
};
#define VXWORKSRtnTblNum (sizeof(VXWORKSRtnTbl)/sizeof(VXWORKSRtnTbl[0]))

SYSCALL_GROUP_ENTRY syscallGroupTbl [SYSCALL_GROUPS_MAX] = {
	{ NULL, 0},
	{ NULL, 0},
	{ NULL, 0},
	{ NULL, 0},
	{ NULL, 0},
	{ NULL, 0},
	{ NULL, 0},
	{ NULL, 0},
	{ STANDARDRtnTbl, STANDARDRtnTblNum, },
	{ VXWORKSRtnTbl, VXWORKSRtnTblNum, },
	{ NULL, 0},
	{ NULL, 0},
	{ NULL, 0},
};

char * syscallGroupName [SYSCALL_GROUPS_MAX] = {
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	"STANDARDGroup",
	"VXWORKSGroup",
	 NULL,
	 NULL,
	 NULL,
};

