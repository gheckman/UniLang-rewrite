/* vxsimHostLibP.h - private Host/VxSim interface header */

/*
 * Copyright (c) 2004-2011,2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved 
 * by Wind River. 
 */

/*
modification history
--------------------
02d,04aug14,elp  VXW6-80640 fix (provide 64 bit timestamp).
02c,24feb11,elp  added vxsimHostCpuDelay()/vxsimHostCpuWakeup() CQ:WIND00151275,
		 added vxsimHostExcEnterHook() (CQ:WIND00257359).
02b,04jan11,elp  added vxsimHostFsBaseSet/Get() (CQ:WIND00247541).
02a,27may10,pad  Added 'extern C' statement.
01z,20jan10,elp  fixed vxsimHostWdbPipeRead prototype.
01y,07jan10,elp  64bit support.
01x,22dec09,dbt  Updated vxsimHostSimnetIntClear & vxsimHostSimnetAttach for
                 NAT support.
01w,29jul09,elp  made vxsimHostIpiEmit()available for UP.
01v,08sep08,elp  added vxsimHostShMemLockf() (CQ:WIND133160).
01u,27aug08,jpb  Renamed VSB header file
01t,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
01s,08feb08,elp  removed SIMNET_PKT type.
01r,05sep07,elp  modified vxsimHostWdbPipeInit() (CQ:WIND103423).
01q,20aug07,dbt  Added fd parameter to vxsimHostPassfsFileStatGet()
		 routine (CQ:WIND00101812).
01p,16aug07,elp  moved header files inclusion from vxsimHostLib.h,
		 moved existing prototypes from vxsimHostArchLib.h,
		 removed internal passfs structure references.
01o,10aug07,elp  added missing vxsimLoadDllEx() and vxsimHostCpuVarsInit().
01n,15jul07,elp  added vxsimUsrSvcRegister(), vxsimUsrSvcCall().
01m,27jun07,elp  added vxsimHostSimnetBufSend().
01l,23apr07,elp  fixed mmu api names.
01k,13feb07,elp  added sio API.
01j,07feb07,elp  added ipi level to vxsimHostIpiEmit().
01i,18jan07,elp  added interrupt pending calls, removed useless SMP calls.
01h,07nov06,elp  added SMP support
01g,19oct06,elp  updated vxsimBootStrategyGet() moved vxsimHostWdbPipe*
		 routines from public header.
01f,15sep05,elp  added passFs 64 bits operations (SPR #111187).
01e,29jun05,jmp  reworked vxsimHostModel() to no longer return a host side
                 address.
01d,29sep04,jmp  added vxsimBootStrategyGet().
01c,09sep04,jmp  updated vxsimHostRename() prototype (SPR #97903).
01b,03may04,dbt  Added vxsimHostIntLock() API.
01a,29may04,jeg  written.
*/

#ifndef __INCvxsimHostLibPh
#define __INCvxsimHostLibPh

#include <vsbConfig.h>
#include <sys/stat.h>
#include <utime.h>
#include <regs.h>
#include <vxsimHostLib.h>
#include <drv/end/simnetEnd.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void *	SIO_ID;

/* DLL load option */

#define VXSIM_HOST_DLL_LOAD_ON_CPU0	0
#define VXSIM_HOST_DLL_LOAD_ON_ALL_CPU	1

/* user service max name length */

#define VXSIM_HOST_USR_SVC_MAX_NAME_LEN	50

/* user service register option */

#define VXSIM_HOST_USR_SVC_ON_CPU0	0x1

extern STATUS	vxsimHostClose		(int fd);
extern STATUS	vxsimHostPassfsDirRead	(char *	path,  void ** pDirFd,
					 char * pEntryName);
extern STATUS   vxsimHostPassfsDelete	(char * name);
extern int	vxsimHostErrnoGet	(void);
extern void	vxsimHostExit 		(void);
extern STATUS   vxsimHostPassfsClose	(int fileFd, void * dirFd);
extern STATUS	vxsimHostPassfsStatGet	(char * path, void * pVolumeDesc,
					 struct statfs * pStatfs);
extern STATUS	vxsimHostFtruncate	(int fd, off_t length); 
extern void 	vxsimHostIfInit		(void * pHostInfo);
extern off_t 	vxsimHostLseek		(int fd, off_t offset, int whence);
extern STATUS	vxsimHostPassfsMkdir	(char *path);
extern STATUS	vxsimHostPassfsOpen	(char *name, int flags, int mode);
extern STATUS	vxsimHostOpen		(char *name, int flags, int mode);
extern void *	vxsimHostOpendir	(char *dirname);
extern void	vxsimHostPowerDown	(void);
extern void 	vxsimHostPrintf		(const char * fmt, ...);
extern ssize_t	vxsimHostRead		(int fd, char *buf, size_t len);
extern STATUS	vxsimHostPassfsRename	(char * path, int * pFileFd,
					 void * dirFd, int mode, int flags,
					 char * newPath);
extern STATUS 	vxsimHostReboot		(int startType);
extern STATUS	vxsimHostPassfsRmdir	(char * path);
extern STATUS 	vxsimHostPassfsFileStatGet (char * path, int fd,
					 void * pVolumeDesc,
					 struct stat * pStat);
extern STATUS 	vxsimHostTimerInit 	(int sysVirtualTimeDef,
					int auxVirtualTimeDef);

extern void	vxsimHostTimerDisable	(int clk);
extern STATUS	vxsimHostTimerTimestampEnable	(int tsRollOverIntNum);
extern STATUS	vxsimHostTimerTimestampDisable	(void);
extern UINT32	vxsimHostTimerTimestampFreqGet	(void);
extern UINT32	vxsimHostTimerTimestampGet	(void);
extern STATUS	vxsimHostTimerTimestamp64FreqGet(UINT64 * pFreq);
extern STATUS	vxsimHostTimerTimestamp64Get	(UINT64 * pVal);
extern STATUS	vxsimHostPassfsUnlink	(char *path);
extern int	vxsimHostPassfsCreate	(char * name, int flags);
extern STATUS	vxsimHostPassfsTimeSet	(char * path,
					 struct utimbuf * pTime);
extern ssize_t	vxsimHostWrite		(int fd, char *buf, size_t len);
extern void	vxsimHostDbg		(char * format, ...);
extern STATUS	vxsimHostCurrentPathGet	(char * buf, size_t size);
extern char *	vxsimHostModel		(char * sysModelStr,
					 size_t sysModelStrMaxLen);
extern STATUS	vxsimHostStat		(char * path, struct stat * pStat);
extern UINT32	vxsimHostTimeGet	(void);
extern int	vxsimHostIntPendingGet	(void);
extern STATUS	vxsimHostSysNvRamGet	(char *	string, size_t strLen,
					 off_t offset, size_t nvRamSize);
extern STATUS	vxsimHostSysNvRamSet	(char *	string, size_t strLen,
					 off_t offset, size_t nvRamSize);
extern void *	vxsimHostShMemInit	(void * smMemAddr, int smMemSize,
					 int * smLevel);
extern STATUS	vxsimHostShMemLockf	(BOOL lock, void * addr);
extern STATUS	vxsimHostBusIntGen	(int smLevel, int smBusInt);
extern STATUS	vxsimHostSimnetAttach	(char * devName, 
					 char * paramString, char * ipAddr,
					 int netType, void ** ppNetCfg,
					 int * pIntId);
extern void	vxsimHostSimnetDetach	(void ** ppNetCfg);
extern void	vxsimHostSimnetIntClear (void * pNetCfg, int intId);
extern void	vxsimHostSimnetIntEnable (void * pNetCfg, int intId,
					  BOOL enable);
extern int	vxsimHostSimnetPhysAddrLenGet (void * ppNetCfg);
extern void	vxsimHostSimnetPhysAddrGet (void * ppNetCfg, UINT8 * enetAddr,
					    int len);
extern STATUS	vxsimHostSimnetPhysAddrSet (void * ppNetCfg, UINT8 * enetAddr,
					    int len);
extern void	vxsimHostSimnetBrdAddrGet (void * ppNetCfg, UINT8 * enetAddr,
					   int len);
extern int	vxsimHostSimnetPktReceive (void * ppNetCfg, char * buffer,
					   size_t * pBufSize);
extern char *	vxsimHostSimnetPktGet (void * ppNetCfg, size_t len);
extern void *	vxsimHostSimnetPktAlloc (void * ppNetCfg, char ** pBuffer,
					 size_t * pBufSize);
extern STATUS	vxsimHostSimnetPktSend (void * ppNetCfg, void * pPkt, size_t
					bufSize);
extern STATUS	vxsimHostSimnetBufSend (void * ppNetCfg, char * pBuf,
					size_t bufSize);
extern STATUS	vxsimHostSimnetPromiscModeSet (void * pNetCfg, BOOL promisc);
extern STATUS	vxsimHostSimnetMCastModeSet (void * pNetCfg, BOOL mcast);
extern STATUS	vxsimHostSimnetParamGet (void * pNetCfg, int param, 
					 UCHAR * buf, size_t len);
extern STATUS	vxsimHostSimnetParamSet (void * pNetCfg, int param,
					 UCHAR * buf, size_t len);

extern STATUS	vxsimHostNetAddIfGet (int index, char ** ppDevice, int * pUnit,
				      char ** ppDevStr, char ** ppIpAddr,
				      char ** ppIpMask);
extern void	vxsimHostVirtualMemInfoGet
					(VIRT_ADDR * pVxsimVirtMemBaseAddr,
					 size_t * pVxsimVirtMemSize);

extern UINT32	vxsimBootStrategyConvert (UINT32 bootStrategy);
extern STATUS	vxsimHostLseek64 (int fd, INT64 * pOffset, int whence);
extern STATUS	vxsimHostFtruncate64 (int fd, INT64 * length);
extern STATUS   vxsimHostWdbPipeInit    (void * inputBuffer,
					 int * pHostTargetFd,
					 int * pTargetHostFd,
					 int * pIntVecNum,
					 UINT32 pipePktMtu,
					 size_t * pPktSize);
extern void	vxsimHostWdbPipeModeSet	(int pipeFd, int newMode);
extern void	vxsimHostWdbPipeFlush	(int pipeFd);
extern STATUS	vxsimHostWdbPipeRead	(int pipeFd, void * inputBuffer,
					 size_t * pSize);
extern ssize_t	vxsimHostWdbPipeWrite	(int pipeFd, void * buffer, size_t len);
extern STATUS	vxsimHostWdbPipePoll	(void);
extern void	vxsimHostSleep		(UINT32 duration);

extern SIO_ID	vxsimHostSioDevFind (char * name);
extern int	vxsimHostSioIntVecGet (SIO_ID sioId);
extern ssize_t	vxsimHostSioWrite (SIO_ID sioId, char * buf, size_t len);
extern ssize_t	vxsimHostSioRead (SIO_ID sioId, char * buf, size_t len);
extern STATUS	vxsimHostSioOpen (SIO_ID sioId);
extern STATUS 	vxsimHostSioClose (SIO_ID sioId);
extern STATUS	vxsimHostSioModeSet (SIO_ID sioId, int mode);
extern STATUS	vxsimHostSioBaudRateSet (SIO_ID sioId, int baudRate);

#if CPU==SIMNT
extern STATUS	vxsimHostVxWorksInstrCacheFlush (void * address, size_t size);
extern int	vxsimHostTimerRateGet (int clk);
extern STATUS	vxsimHostTimerRateSet (int clk, int ticksPerSecond);
extern void	vxsimHostTimerEnable (int clk);
extern void	vxsimHostDebugBreak (void);
#else
extern int	vxsimHostGetgid (void);
extern void	vxsimHostTimerEnable (int clk, int ticksPerSecond);
#endif /* CPU==SIMNT */

#ifdef _WRS_CONFIG_SMP
extern STATUS	vxsimHostCpuEnable (int cpuNum, INSTR * startFunc,
				    ULONG stackPtr);	
extern void	vxsimHostCpuDelay (int milliseconds);
extern void	vxsimHostCpuWakeup (cpuset_t processors);
#endif /* _WRS_CONFIG_SMP */
extern STATUS	vxsimHostIpiEmit (cpuset_t processor, UINT8 ipiLvl);

extern STATUS	vxsimHostUsrSvcRegister (UINT32 * pUsrSvcNum,
					 char * usrSvcName, char usrSvcFlags);
extern STATUS	vxsimHostUsrSvcCall (ULONG * pResult, UINT32 svcNum, 
				     ULONG arg0, ULONG arg1, ULONG arg2,
				     ULONG arg3, ULONG arg4, ULONG arg5,
				     ULONG arg6, ULONG arg7, ULONG arg8,
				     ULONG arg9);
extern STATUS	vxsimHostDllLoadEx (char * dllName, UINT32 options);
extern void	vxsimHostCpuVarsInit (void);
extern STATUS	vxsimHostFsBaseSet (ULONG fsBase);
extern STATUS	vxsimHostFsBaseGet (ULONG * pFsBase);
extern void	vxsimHostExcEnterHook (void);
#ifdef __cplusplus
}
#endif

#endif	/* __INCvxsimHostLibPh */
