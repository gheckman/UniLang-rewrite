/* syscall.h - System Call Group and Number definition file */

/* Copyright (c) 2003-2010 Wind River Systems, Inc. */

/* THIS FILE IS AUTO_GENERATED. PLEASE DO NOT EDIT. */

#ifndef __INCsyscallh
#define __INCsyscallh

#ifdef __cplusplus
extern "C" {
#endif

    /* defines */

    /*
     * SYSTEM CALL NUMBERS:
     * System Call Numbers (SCN) are unique 32-bit numbers identifying 
     * the kernel routine requested by the user. The SCI decodes this  
     * number to identify and call the requested kernel function on 
     * behalf of the application. The SCN is organized as follows:
     * 
     *                  SYSCALL_GROUP_NUM_BITS  SYSCALL_ROUTINE_NUM_BITS
     * -----------------------------------------------------------------
     * |               |                       |                       |
     * |   reserved    |         Group#        |        Routine#       |
     * |               |                       |                       |
     * -----------------------------------------------------------------
     * 31                                                              0
     */

#define SYSCALL_GROUP_NUM_BITS		10
#define SYSCALL_ROUTINE_NUM_BITS		6
#define SYSCALL_GROUP_NO_BIT_START		6

#define SYSCALL_NUMBER(grp,rtn) \
        (((grp) << SYSCALL_GROUP_NO_BIT_START) _WRS_BIT_OR (rtn))


    /* List of System Call Groups 
     * 
     * Groups 0 and 1 are reserved for future Wind River use. 
     * Groups 2 through 7 are for customer use.
     * Groups 8 onwards are for Wind River and partner use.
     */

#define SCG_RESERVED0 		0
#define SCG_RESERVED0_Name 		"RESERVED0Group"
#define SCG_RESERVED1 		1
#define SCG_RESERVED1_Name 		"RESERVED1Group"
#define SCG_USER0 		2
#define SCG_USER0_Name 		"USER0Group"
#define SCG_USER1 		3
#define SCG_USER1_Name 		"USER1Group"
#define SCG_USER2 		4
#define SCG_USER2_Name 		"USER2Group"
#define SCG_USER3 		5
#define SCG_USER3_Name 		"USER3Group"
#define SCG_USER4 		6
#define SCG_USER4_Name 		"USER4Group"
#define SCG_USER5 		7
#define SCG_USER5_Name 		"USER5Group"
#define SCG_STANDARD 		8
#define SCG_STANDARD_Name 		"STANDARDGroup"
#define SCG_VXWORKS 		9
#define SCG_VXWORKS_Name 		"VXWORKSGroup"
#define SCG_VXTEST 		10
#define SCG_VXTEST_Name 		"VXTESTGroup"
#define SCG_RTI 		11
#define SCG_RTI_Name 		"RTIGroup"
#define SCG_RADSTONE 		12
#define SCG_RADSTONE_Name 		"RADSTONEGroup"

/* Routines for SCG_STANDARD */

#define SCN__exit 		 SYSCALL_NUMBER (SCG_STANDARD, 0)
#define SCN__creat 		 SYSCALL_NUMBER (SCG_STANDARD, 1)
#define SCN__open 		 SYSCALL_NUMBER (SCG_STANDARD, 2)
#define SCN__close 		 SYSCALL_NUMBER (SCG_STANDARD, 3)
#define SCN__read 		 SYSCALL_NUMBER (SCG_STANDARD, 4)
#define SCN__write 		 SYSCALL_NUMBER (SCG_STANDARD, 5)
#define SCN__ioctl 		 SYSCALL_NUMBER (SCG_STANDARD, 6)
#define SCN_dup 		 SYSCALL_NUMBER (SCG_STANDARD, 7)
#define SCN_dup2 		 SYSCALL_NUMBER (SCG_STANDARD, 8)
#define SCN_pipe 		 SYSCALL_NUMBER (SCG_STANDARD, 9)
#define SCN_remove 		 SYSCALL_NUMBER (SCG_STANDARD, 10)
#define SCN_select 		 SYSCALL_NUMBER (SCG_STANDARD, 11)
#define SCN_socket 		 SYSCALL_NUMBER (SCG_STANDARD, 12)
#define SCN_bind 		 SYSCALL_NUMBER (SCG_STANDARD, 13)
#define SCN_listen 		 SYSCALL_NUMBER (SCG_STANDARD, 14)
#define SCN_accept 		 SYSCALL_NUMBER (SCG_STANDARD, 15)
#define SCN_connect 		 SYSCALL_NUMBER (SCG_STANDARD, 16)
#define SCN_sendto 		 SYSCALL_NUMBER (SCG_STANDARD, 17)
#define SCN_send 		 SYSCALL_NUMBER (SCG_STANDARD, 18)
#define SCN_sendmsg 		 SYSCALL_NUMBER (SCG_STANDARD, 19)
#define SCN_recvfrom 		 SYSCALL_NUMBER (SCG_STANDARD, 20)
#define SCN_recv 		 SYSCALL_NUMBER (SCG_STANDARD, 21)
#define SCN_recvmsg 		 SYSCALL_NUMBER (SCG_STANDARD, 22)
#define SCN_setsockopt 		 SYSCALL_NUMBER (SCG_STANDARD, 23)
#define SCN_getsockopt 		 SYSCALL_NUMBER (SCG_STANDARD, 24)
#define SCN_getsockname 		 SYSCALL_NUMBER (SCG_STANDARD, 25)
#define SCN_getpeername 		 SYSCALL_NUMBER (SCG_STANDARD, 26)
#define SCN_shutdown 		 SYSCALL_NUMBER (SCG_STANDARD, 27)
#define SCN_mmap 		 SYSCALL_NUMBER (SCG_STANDARD, 28)
#define SCN_munmap 		 SYSCALL_NUMBER (SCG_STANDARD, 29)
#define SCN_mprotect 		 SYSCALL_NUMBER (SCG_STANDARD, 30)
#define SCN_kill 		 SYSCALL_NUMBER (SCG_STANDARD, 31)
#define SCN__pause 		 SYSCALL_NUMBER (SCG_STANDARD, 32)
#define SCN_sigpending 		 SYSCALL_NUMBER (SCG_STANDARD, 33)
#define SCN_sigprocmask 		 SYSCALL_NUMBER (SCG_STANDARD, 34)
#define SCN__sigqueue 		 SYSCALL_NUMBER (SCG_STANDARD, 35)
#define SCN__sigsuspend 		 SYSCALL_NUMBER (SCG_STANDARD, 36)
#define SCN__sigtimedwait 		 SYSCALL_NUMBER (SCG_STANDARD, 37)
#define SCN__sigaction 		 SYSCALL_NUMBER (SCG_STANDARD, 38)
#define SCN__sigreturn 		 SYSCALL_NUMBER (SCG_STANDARD, 39)
#define SCN_chdir 		 SYSCALL_NUMBER (SCG_STANDARD, 40)
#define SCN__getcwd 		 SYSCALL_NUMBER (SCG_STANDARD, 41)
#define SCN_getpid 		 SYSCALL_NUMBER (SCG_STANDARD, 43)
#define SCN_getppid 		 SYSCALL_NUMBER (SCG_STANDARD, 44)
#define SCN__waitpid 		 SYSCALL_NUMBER (SCG_STANDARD, 45)
#define SCN_sysctl 		 SYSCALL_NUMBER (SCG_STANDARD, 46)
#define SCN__schedPxInfoGet 		 SYSCALL_NUMBER (SCG_STANDARD, 47)
#define SCN_sigaltstack 		 SYSCALL_NUMBER (SCG_STANDARD, 48)
#define SCN_unlink 		 SYSCALL_NUMBER (SCG_STANDARD, 49)
#define SCN_link 		 SYSCALL_NUMBER (SCG_STANDARD, 50)
#define SCN__fsync 		 SYSCALL_NUMBER (SCG_STANDARD, 51)
#define SCN__fdatasync 		 SYSCALL_NUMBER (SCG_STANDARD, 52)
#define SCN_rename 		 SYSCALL_NUMBER (SCG_STANDARD, 53)
#define SCN_fpathconf 		 SYSCALL_NUMBER (SCG_STANDARD, 54)
#define SCN_pathconf 		 SYSCALL_NUMBER (SCG_STANDARD, 55)
#define SCN_access 		 SYSCALL_NUMBER (SCG_STANDARD, 56)
#define SCN_chmod 		 SYSCALL_NUMBER (SCG_STANDARD, 57)
#define SCN_pxTraceCreation 		 SYSCALL_NUMBER (SCG_STANDARD, 58)
#define SCN_pxTraceCtl 		 SYSCALL_NUMBER (SCG_STANDARD, 59)
#define SCN_pxTraceEvent 		 SYSCALL_NUMBER (SCG_STANDARD, 60)
#define SCN_pxTraceEventNameQuery 		 SYSCALL_NUMBER (SCG_STANDARD, 61)
#define SCN_pxTraceLog 		 SYSCALL_NUMBER (SCG_STANDARD, 62)
#define SCN_pxTraceEventGet 		 SYSCALL_NUMBER (SCG_STANDARD, 63)

#define STANDARDRtnTblNum (sizeof(STANDARDRtnTbl)/sizeof(STANDARDRtnTbl[0]))

/* Routines for SCG_VXWORKS */

#define SCN_eventReceive 		 SYSCALL_NUMBER (SCG_VXWORKS, 0)
#define SCN_eventSend 		 SYSCALL_NUMBER (SCG_VXWORKS, 1)
#define SCN_eventCtl 		 SYSCALL_NUMBER (SCG_VXWORKS, 2)
#define SCN_msgQSend 		 SYSCALL_NUMBER (SCG_VXWORKS, 3)
#define SCN_msgQReceive 		 SYSCALL_NUMBER (SCG_VXWORKS, 4)
#define SCN__msgQOpen 		 SYSCALL_NUMBER (SCG_VXWORKS, 5)
#define SCN_objDelete 		 SYSCALL_NUMBER (SCG_VXWORKS, 6)
#define SCN_objInfoGet 		 SYSCALL_NUMBER (SCG_VXWORKS, 7)
#define SCN__semTake 		 SYSCALL_NUMBER (SCG_VXWORKS, 8)
#define SCN__semGive 		 SYSCALL_NUMBER (SCG_VXWORKS, 9)
#define SCN__semOpen 		 SYSCALL_NUMBER (SCG_VXWORKS, 10)
#define SCN_semCtl 		 SYSCALL_NUMBER (SCG_VXWORKS, 11)
#define SCN__taskOpen 		 SYSCALL_NUMBER (SCG_VXWORKS, 12)
#define SCN_taskCtl 		 SYSCALL_NUMBER (SCG_VXWORKS, 13)
#define SCN_taskDelay 		 SYSCALL_NUMBER (SCG_VXWORKS, 14)
#define SCN_rtpSpawn 		 SYSCALL_NUMBER (SCG_VXWORKS, 15)
#define SCN_rtpInfoGet 		 SYSCALL_NUMBER (SCG_VXWORKS, 16)
#define SCN_taskKill 		 SYSCALL_NUMBER (SCG_VXWORKS, 17)
#define SCN__taskSigqueue 		 SYSCALL_NUMBER (SCG_VXWORKS, 18)
#define SCN__timer_open 		 SYSCALL_NUMBER (SCG_VXWORKS, 19)
#define SCN_timerCtl 		 SYSCALL_NUMBER (SCG_VXWORKS, 20)
#define SCN_pxOpen 		 SYSCALL_NUMBER (SCG_VXWORKS, 21)
#define SCN_pxClose 		 SYSCALL_NUMBER (SCG_VXWORKS, 22)
#define SCN_pxUnlink 		 SYSCALL_NUMBER (SCG_VXWORKS, 23)
#define SCN_pxCtl 		 SYSCALL_NUMBER (SCG_VXWORKS, 24)
#define SCN_pxMqReceive 		 SYSCALL_NUMBER (SCG_VXWORKS, 25)
#define SCN_pxMqSend 		 SYSCALL_NUMBER (SCG_VXWORKS, 26)
#define SCN_pxSemWait 		 SYSCALL_NUMBER (SCG_VXWORKS, 27)
#define SCN_pxSemPost 		 SYSCALL_NUMBER (SCG_VXWORKS, 28)
#define SCN_pipeDevCreate 		 SYSCALL_NUMBER (SCG_VXWORKS, 29)
#define SCN_pipeDevDelete 		 SYSCALL_NUMBER (SCG_VXWORKS, 30)
#define SCN__sdCreate 		 SYSCALL_NUMBER (SCG_VXWORKS, 31)
#define SCN__sdOpen 		 SYSCALL_NUMBER (SCG_VXWORKS, 32)
#define SCN_sdDelete 		 SYSCALL_NUMBER (SCG_VXWORKS, 33)
#define SCN_sdMap 		 SYSCALL_NUMBER (SCG_VXWORKS, 34)
#define SCN_sdUnmap 		 SYSCALL_NUMBER (SCG_VXWORKS, 35)
#define SCN_sdProtect 		 SYSCALL_NUMBER (SCG_VXWORKS, 36)
#define SCN__edrErrorInject 		 SYSCALL_NUMBER (SCG_VXWORKS, 37)
#define SCN_edrFlagsGet 		 SYSCALL_NUMBER (SCG_VXWORKS, 38)
#define SCN_wvEvent 		 SYSCALL_NUMBER (SCG_VXWORKS, 40)
#define SCN_rtpVarAdd 		 SYSCALL_NUMBER (SCG_VXWORKS, 41)
#define SCN_sdInfoGet 		 SYSCALL_NUMBER (SCG_VXWORKS, 42)
#define SCN__shlOpen 		 SYSCALL_NUMBER (SCG_VXWORKS, 43)
#define SCN__shlUnlock 		 SYSCALL_NUMBER (SCG_VXWORKS, 44)
#define SCN__shlClose 		 SYSCALL_NUMBER (SCG_VXWORKS, 45)
#define SCN__shlGet 		 SYSCALL_NUMBER (SCG_VXWORKS, 46)
#define SCN__shlPut 		 SYSCALL_NUMBER (SCG_VXWORKS, 47)
#define SCN_objUnlink 		 SYSCALL_NUMBER (SCG_VXWORKS, 48)
#define SCN_getprlimit 		 SYSCALL_NUMBER (SCG_VXWORKS, 49)
#define SCN_setprlimit 		 SYSCALL_NUMBER (SCG_VXWORKS, 50)
#define SCN__mctl 		 SYSCALL_NUMBER (SCG_VXWORKS, 51)
#define SCN__taskOpenWithGuard 		 SYSCALL_NUMBER (SCG_VXWORKS, 52)
#define SCN_clockCtl 		 SYSCALL_NUMBER (SCG_VXWORKS, 53)
#define SCN__semRTake 		 SYSCALL_NUMBER (SCG_VXWORKS, 54)
#define SCN__semWTake 		 SYSCALL_NUMBER (SCG_VXWORKS, 55)
#define SCN__semExchange 		 SYSCALL_NUMBER (SCG_VXWORKS, 56)
#define SCN_wvRtpEvent 		 SYSCALL_NUMBER (SCG_VXWORKS, 57)
#define SCN__taskTcbCurrentGet 		 SYSCALL_NUMBER (SCG_VXWORKS, 58)

#define VXWORKSRtnTblNum (sizeof(VXWORKSRtnTbl)/sizeof(VXWORKSRtnTbl[0]))

#ifdef __cplusplus
}
#endif

#endif /* __INCsyscallh */
