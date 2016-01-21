/* coreDumpLibCommon.h - common core dump library header file */

/* 
 * Copyright (c) 2008 Wind River Systems, Inc. 
 * 
 * The right to copy, distribute, modify, or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01a,18jun08,jmp  Written.
*/

#ifndef __INCcoreDumpLibCommonh
#define __INCcoreDumpLibCommonh

#ifdef __cplusplus
extern "C" {
#endif

/* Structure for passing RTP memory filter to sysctl */

typedef struct core_dump_rtp_mem_filter_args
    {
    void *      addr;           /* address of memory region to filter */
    size_t      size;           /* size of memory region to filter */
    } CORE_DUMP_RTP_MEM_FILTER_ARGS;

/* generic status codes */

#define S_coreDumpLib_CORE_DUMP_HOOK_TABLE_FULL		(M_coreDumpLib | 1)
#define S_coreDumpLib_CORE_DUMP_HOOK_NOT_FOUND		(M_coreDumpLib | 2)
#define S_coreDumpLib_CORE_DUMP_INVALID_DEVICE		(M_coreDumpLib | 3)
#define S_coreDumpLib_CORE_DUMP_DEVICE_READ_ERROR	(M_coreDumpLib | 4)
#define S_coreDumpLib_CORE_DUMP_DEVICE_WRITE_ERROR	(M_coreDumpLib | 5)
#define S_coreDumpLib_CORE_DUMP_DEVICE_ERASE_ERROR	(M_coreDumpLib | 6)
#define S_coreDumpLib_CORE_DUMP_DEVICE_OPEN_ERROR	(M_coreDumpLib | 7)
#define S_coreDumpLib_CORE_DUMP_DEVICE_CLOSE_ERROR	(M_coreDumpLib | 8)
#define S_coreDumpLib_CORE_DUMP_INVALID_ARGS		(M_coreDumpLib | 9)
#define S_coreDumpLib_CORE_DUMP_INVALID_CORE_DUMP	(M_coreDumpLib | 10)
#define S_coreDumpLib_CORE_DUMP_STORAGE_NOT_FORMATED	(M_coreDumpLib | 11)
#define S_coreDumpLib_CORE_DUMP_DEVICE_NOT_INITIALIZED	(M_coreDumpLib | 12)
#define S_coreDumpLib_CORE_DUMP_TOO_MANY_CORE_DUMP	(M_coreDumpLib | 13)
#define S_coreDumpLib_CORE_DUMP_COMPRESSION_ERROR	(M_coreDumpLib | 14)
#define S_coreDumpLib_CORE_DUMP_FILTER_TABLE_FULL	(M_coreDumpLib | 15)
#define S_coreDumpLib_CORE_DUMP_GENERATE_ALREADY_RUNNING (M_coreDumpLib | 16)
#define S_coreDumpLib_CORE_DUMP_PATH_TOO_LONG		(M_coreDumpLib | 17)
#define S_coreDumpLib_CORE_DUMP_GENERATE_NOT_RUNNING	(M_coreDumpLib | 18)
#define S_coreDumpLib_CORE_DUMP_DEVICE_TOO_SMALL	(M_coreDumpLib | 19)
#define S_coreDumpLib_CORE_DUMP_FILTER_NOT_FOUND	(M_coreDumpLib | 20)
#define S_coreDumpLib_CORE_DUMP_CKSUM_VERIFY_ERROR	(M_coreDumpLib | 21)
#define S_coreDumpLib_CORE_DUMP_VARIABLES_CORRUPTED	(M_coreDumpLib | 22)
#define S_coreDumpLib_CORE_DUMP_STREAM_DEV_ALREADY_INITIALIZED (M_coreDumpLib | 23)
#define S_coreDumpLib_CORE_DUMP_RAW_DEV_ALREADY_INITIALIZED (M_coreDumpLib | 24)

#ifdef __cplusplus
}
#endif

#endif /* __INCcoreDumpLibCommonh */
