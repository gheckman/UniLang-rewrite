/* coreDumpLibP.h - core dump private interface header */

/*
 * Copyright (c) 2005-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
 
/*
modification history
--------------------
02n,20apr12,jmp  CQID: Fix WIND00346084 : No longer assume in coreDumpCksum()
                 that when sumInit=0 means the begining of a core dump
                 checksum.
02m,13apr11,jmp  Added coreDumpMemPartRegister().
02l,25feb11,jmp  Fixed core dump magic number.
02k,04feb11,jmp  Update coreDumpInit() prototype for LP64 support.
02j,23nov10,jmp  Added coreDumpMemFilterParsingReset() (CQ:WIND00242762).
02i,04jun10,jmp  Added a parameter to coreDumpFreeBlockFilterAdd() to control
                 the minimal block size for the free block filtering
                 mechanism.
02h,29apr10,pad  Moved extern C statement after include statements.
02g,03mar10,jmp  Added coreDumpRtpNameGenerate() (CQ:WIND00183676).
02f,17dec09,jmp  Added <protect> argument to coreDumpMemAlloc().
02e,11dec09,jmp  LP64 code adaptation.
02d,16jul09,jmp  Added coreDumpRtpFsDevInit().
02c,27aug08,jpb  Renamed VSB header file
02b,10jul08,jmp  added rtpId and taskId parameters to coreDumpRtpGenerate().
02a,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
01z,14apr08,jmp  Added support for multiple core dump interfaces
		 (REQ CQ:WIND00005075).
01y,26feb08,jmp  made coreDumpSizeCompute() global for internal purpose (REQ
                 CQ:WIND00105547).
01x,21sep07,jmp  added EDR string to TGT_INFO_NOTE (CQ:WIND00104805).
01w,31aug07,jmp  renamed coreDumpMemPoolProtectEnable() argument.
01v,10jul07,jmp  Added coreDumpTaskId and coreDumpCpuId to TGT_INFO_NOTE.
		 Updated coreDumpMemPoolWrite() prototype.
01u,26jun07,jmp  added SMP support.
01t,18jun07,jmp  Updated coreDumpMemPoolLibInit() call to pass the
                 CORE_DUMP_MEM_POOL_PROTECTION_ENABLE parameter.
01s,21dec06,jmp  removed coreDumpMemProtect() and added
                 coreDumpMemPoolWrite().
01r,23oct06,jmp  moved all the definitions that are only used in
		 src/debug/coredump/ to src/debug/coredump/coreDumpDefs.h.
01q,30jun06,jmp  added pInfoWriteRtn to CORE_DUMP_DEV_INFO.
		 added CORE_DUMP_DATA_TYPE enum.
		 updated coreDumpDevWrite() prototype.
		 fixed BLOCK_ROUND_UP to allow using block size that are
		 not a power of two (Defect #50073).
		 renamed some CORE_DUMP_STREAM_DEV_DESC fields following design
		 review.
01p,23jun06,jmp  added Core Dump Stream device support.
01o,13mar06,jmp  Added sysPhysMemSize field to CORE_DUMP_LIB_INFO (SPR #118953).
01n,02dec05,jmp  renamed coreDumpCompressLibInit into coreDumpZLibInit.
		 added coreDumpRleInit().
		 added coreDumpCksum to CORE_DUMP_HDR structure.
01m,13sep05,dbt  Fixed pMemWriteFilter() prototype.
01l,07sep05,jmp  Performed some updates required for the coreDumpLib.c split.
		 Added support for core dump alternate stack switch.
		 Provide the ability to install core dump filters before
		 usrCoreDumpInit() call.
01k,01sep05,dbt  Updated TGT_INFO structure.
		 Added coreDumpMemCksum() prototype.
01j,16aug05,dbt  Added device storage size in CORE_DUMP_DEV_INFO structure.
01i,11aug05,dbt  Added coreDumpGenerate() prototype.
01h,10aug05,dbt  Removed unused coreDumpMemWriteFilter() prototype.
01g,08aug05,dbt  Moved some definitions from coreDumpLib.h
01f,04aug05,jmp  updated coreDumpWrite().
01e,03aug05,dbt  Added coreDumpHookInit() & coreDumpCreateHooksRun()
                 prototypes.
01d,28jul05,jmp  moved CORE_DUMP_DEV_INFO from coreDumpLib.c.
		 added core dump memory region filtering.
01c,27jul05,jmp  added compression level to coreDumpCompressLibInit().
01b,18jul05,jmp  added compression support.
01a,01jul05,jmp  written.
*/

#ifndef __INCcoreDumpLibPh
#define __INCcoreDumpLibPh

/* includes */

#include <vsbConfig.h>
#include <regs.h>
#include <excLib.h>
#include <coreDumpLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#ifndef _WRS_CONFIG_LP64
#define CORE_DUMP_MAGIC_NUMBER		0x45524f43	/* core dump 32 magic */
							/* 'C','O','R','E' */
#else	/* _WRS_CONFIG_LP64 */
#define CORE_DUMP_MAGIC_NUMBER		0x38524f43	/* core dump 64 magic */
							/* 'C','O','R','8' */
#endif	/* _WRS_CONFIG_LP64 */

#define CORE_DUMP_VERSION		1	/* core dump version number */

#define CORE_DUMP_PROTECT_MEM_ALLOC(size, alignment)			\
	coreDumpMemAlloc (NULL, size, alignment,TRUE)
#define CORE_DUMP_PROTECT_MEM_WITH_KEY_ALLOC(allocKey, size, alignment)	\
	coreDumpMemAlloc (allocKey, size, alignment, TRUE)

#define CORE_DUMP_MEM_ALLOC(size, alignment)				\
	coreDumpMemAlloc (NULL, size, alignment,FALSE)
#define CORE_DUMP_MEM_WITH_KEY_ALLOC(allocKey, size, alignment) 	\
	coreDumpMemAlloc (allocKey, size, alignment, FALSE)

#define CORE_DUMP_MEM_POOL_TYPED_VALUE_WRITE(TYPE,pVal,value,status)	\
    {									\
    TYPE typedVal = value;						\
    if (coreDumpMemPoolWrite (&typedVal, pVal, sizeof (TYPE)) == ERROR) \
	status = ERROR;							\
    }

/* Runtime information fields length */

#define	CORE_DUMP_RT_NAME_LEN		50
#define	CORE_DUMP_RT_VER_LEN		50
#define	CORE_DUMP_CPU_VARIANT_LEN	20
#define	CORE_DUMP_TOOL_NAME_LEN		20
#define	CORE_DUMP_BSP_SHORT_NAME_LEN	100
#define	CORE_DUMP_BSP_NAME_LEN		100

/* typedefs */

typedef struct core_dump_cpu_info
    {
    REG_SET	cpuRegSet;		/* CPU system register set */
    BOOL	cpuRegSetIsValid;	/* cpuRegSet is valid ? */
    TASK_ID	cpuTaskIdCurrent;	/* task running on CPU at the time */
    					/* of the core dump generation */
    } CORE_DUMP_CPU_INFO;

typedef struct tgt_info_note	/* TGT_INFO_NOTE - target information note */
    {
    /* runtime information */

    char 	rtName[CORE_DUMP_RT_NAME_LEN];
    char 	rtVersion[CORE_DUMP_RT_VER_LEN];
    UINT32	cpuFamily;
    UINT32	cpuType;
    char 	cpuVariant[CORE_DUMP_CPU_VARIANT_LEN];
    char 	toolName[CORE_DUMP_TOOL_NAME_LEN];
    char 	bspShortName[CORE_DUMP_BSP_SHORT_NAME_LEN];
    UINT32	hasCoprocessor;
    BOOL	hasWriteProtect;
    UINT32	pageSize;
    UINT32	endian;
    char 	bspName [CORE_DUMP_BSP_NAME_LEN];
    ULONG	memBase;
    ULONG	memSize;
    UINT32	textScnCksum;

    /* exception information */

    BOOL	excValid;
    UINT32	excVecNum;
    void *	excCtxId;

    /* core dump information */

    char 	coreDumpType [CORE_DUMP_TYPE_LEN];

    /* CPUs information */

#ifdef	_WRS_CONFIG_SMP
    CORE_DUMP_CPU_INFO	cpuInfo[VX_MAX_SMP_CPUS];
#else
    CORE_DUMP_CPU_INFO	cpuInfo;	/* Only one CPU in UP mode */
#endif /* _WRS_CONFIG_SMP */
    UINT32	cpuInfoMaxCpus;		/* Number of entries in cpuInfo array */
    TASK_ID	coreDumpTaskId;		/* Id of the Task generating coredump */
    UINT32	coreDumpCpuId;		/* Id of the CPU generating coredump */

    char	infoString[MAX_CORE_DUMP_INFO_LEN];
					/* core dump information string */
    } TGT_INFO_NOTE;

typedef struct core_dump_stream_dev_desc   /* coredump stream device desc */
    {
    UINT32	devCacheSize;		/* device cache size */
    void *	deviceId;		/* device ID used for various rtns */
    char *	pDevCache;		/* device cache buffer */
    FUNCPTR	pDevOpenRtn;		/* device open() routine */
    FUNCPTR	pDevReadRtn;		/* device read() routine (OPTIONAL) */
    FUNCPTR	pDevWriteRtn;		/* device write() routine */
    FUNCPTR	pDevCloseRtn;		/* device close() routine */
    } CORE_DUMP_STREAM_DEV_DESC;

typedef struct core_dump_dev_desc	/* coredump generic device descriptor */
    {
    UINT32	devWrtBlkSize;		/* device write block size */
    char *	pDevWrtBlkCache;	/* device cache buffer */
    FUNCPTR	pDevEraseRtn;		/* device erase() routine */
    FUNCPTR	pDevOpenRtn;		/* device open() routine */
    FUNCPTR	pDevWriteRtn;		/* device write() routine */
    FUNCPTR	pDevReadRtn;		/* device read() routine */
    FUNCPTR	pDevFlushRtn;		/* device flush() routine */
    FUNCPTR	pDevCloseRtn;		/* device close() routine */
    } CORE_DUMP_DEV_DESC;

typedef enum
    {
    CORE_DUMP_DEVICE_KERNEL,		/* 0: device for kernel core dump */
    CORE_DUMP_DEVICE_RTP		/* 1: device for RTP core dump */
    } CORE_DUMP_DEVICE_TYPE;

/* core dump data types (type of data that can be written to device) */

typedef enum
    {
    CORE_DUMP_DATA,			/* 0: core dump content */
    CORE_DUMP_INFO_DATA			/* 1: information on core dump */
    } CORE_DUMP_DATA_TYPE;

typedef enum
    {
    CORE_DUMP_INVALID_FILTER,		/* 0 : Invalid filter */
    CORE_DUMP_USER_FILTER,		/* 1 : User filter */
    CORE_DUMP_SYSTEM_FILTER,		/* 2 : System filters*/
    CORE_DUMP_TMP_SYSTEM_FILTER		/* 3 : Temporary system filter */
    } CORE_DUMP_FILTER_TYPE;

typedef void (*CORE_DUMP_RT_INFO_GET)	(TGT_INFO_NOTE * pRtInfo);
typedef BOOL (*CORE_DUMP_PHYS_MEM_CHECK)(PHYS_ADDR paddr, size_t size,
					 PHYS_ADDR * pBlockPaddr,
					 size_t * pBlockSize);
typedef STATUS (*CORE_DUMP_PHYS_MEM_DUMP)(FUNCPTR pDumpRtn, void * pKernelIf,
					 UINT32 state, UINT32 alignment);


/* variable declarations */

extern char *	rtpCoreDumpNameSuffix;	/* RTP Core Dump name suffix */

/* function declarations */

/* initialization routines */

extern STATUS   coreDumpInit            (size_t stackSize,
					 CORE_DUMP_RT_INFO_GET pRtInfoGet,
					 CORE_DUMP_PHYS_MEM_CHECK pPhysMemCheck,
					 CORE_DUMP_PHYS_MEM_DUMP pPhysMemDump,
					 BOOL cksumEnabled);
extern STATUS   coreDumpRtpInit		(CORE_DUMP_RT_INFO_GET pRtInfoGet);
extern STATUS	coreDumpUtilLibInit	(void);
extern STATUS   coreDumpRawDevInit	(CORE_DUMP_RAW_DEV_DESC * pDesc);
extern STATUS	coreDumpStreamDevLibInit(void);
extern STATUS   coreDumpStreamDevInit	(CORE_DUMP_STREAM_DEV_DESC * pDesc,
					 CORE_DUMP_DEVICE_TYPE devType);
extern STATUS	coreDumpCacheLibInit	(CORE_DUMP_DEVICE_TYPE deviceType,
					 char * pCacheBuffer, size_t cacheSize);
extern STATUS	coreDumpZLibInit	(CORE_DUMP_DEVICE_TYPE deviceType,
					 int level);
extern STATUS	coreDumpRleInit		(CORE_DUMP_DEVICE_TYPE deviceType);
extern STATUS	coreDumpHookInit	(UINT32 tableSize);
extern STATUS	coreDumpMemFilterLibInit(UINT32 usrFilterMaxCount,
					 UINT32 sysFilterMaxCount);
extern STATUS	coreDumpMemFilterInstall(void * addr, size_t size,
					 CORE_DUMP_FILTER_TYPE type);
extern STATUS	coreDumpMemFilterUninstall (void * addr, size_t size,
					 CORE_DUMP_FILTER_TYPE type);
extern STATUS	coreDumpMemFilterParsingReset (void);
extern STATUS	coreDumpMemPoolLibInit	(char * pStaticPool,
					 UINT32 poolPageSize, BOOL protect);
extern STATUS	coreDumpRtpFsDevInit	(char * coreDumpRtpPath,
					 BOOL enableCache);
extern char *	coreDumpRtpNameGenerate	(int rtpCoreDumpIndex);

/* private routines that can be used by confliglette code */

extern STATUS	coreDumpGenerate	(int vector, char * pEsf,
					 REG_SET * pRegs, EXC_INFO * pExcInfo,
					 CORE_DUMP_TYPE coreDumpType,
					 char * pInfoString, BOOL isException);
extern STATUS	coreDumpRtpGenerate	(RTP_ID rtpId, TASK_ID taskId,
					 int vector, char * pEsf,
					 REG_SET * pRegs, EXC_INFO * pExcInfo,
					 CORE_DUMP_TYPE coreDumpType,
					 char * pInfoString, BOOL isException);
extern void *	coreDumpMemAlloc	(const char * allocKey, size_t size,
					 size_t alignment, BOOL protect);
extern void *	coreDumpMemByKeyFind	(char * allocKey);
extern STATUS	coreDumpMemPartRegister (PART_ID partId);
extern STATUS	coreDumpFreeBlockFilterAdd (size_t minBlockSize);
extern STATUS	coreDumpMemPoolWrite	(void * fromAddr, void * toAddr,
					 size_t nBytes);
extern STATUS	coreDumpMemPoolProtectEnable (BOOL protect);
extern STATUS	coreDumpMemPoolFiltersInstall (void);
extern UINT32	coreDumpCksum		(char * addr, size_t len,
					 UINT32 sumInit, size_t * pCksumLen,
					 BOOL moreData);
extern STATUS	coreDumpSizeCompute	(size_t * pCoreDumpSize);
extern STATUS	coreDumpMemDevInit	(CORE_DUMP_RAW_DEV_DESC * pDesc,
					 size_t coreDumpPmSize);
#ifdef __cplusplus
}
#endif

#endif /* __INCcoreDumpLibPh */
