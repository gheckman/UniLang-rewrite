/* loadFileLibP.h - header for utility func. lib. shared by loader libraries */

/*
 * Copyright (c) 2004-2006, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01o,29apr10,pad  Moved extern C statement after include statements.
01n,23feb10,v_r  Removed unused SEG_INFO structure.
01m,23feb10,v_r  Revert structure fields reorganization until we can update
                 host side as well.
01l,22feb10,v_r  LP64 TODOS cleanup + structure reorganization.
01k,16jun09,v_r  LP64 adaptation: updated segment/section structures to size_t.
01j,30apr09,v_r  LP64 adaptation (phase #1) : updated code following adaptation
		 guidelines (excepted struct reorg).
		 Removed unneeded SEC_NAME_MAX define.
01i,23oct06,dbt  Added alignment information in section descriptor.
01h,23nov05,v_r  Implemented loader's cache. This fixes SPR#113798 and
		 SPR#112398.
01g,07mar05,v_r  Included symbol.h
01f,01mar05,v_r  Moved segment type enum to moduleLib.h.
01e,06oct04,jn   Clean up comments
01d,17sep04,jn   Move towards shared files
01c,08apr04,jn   Adjustment needed in segment descriptor structure to handle
                 and track alignments correctly
01b,05apr04,jn   Clean up development-related comments
01a,19feb04,jn   Derived from AE's malLib.h
*/

#ifndef __INCloadFileLibPh
#define __INCloadFileLibPh

/* Includes */

#ifdef HOST
#include <host.h>
#include <objLib.h>
#else
#include <vxWorks.h>
#include <errno.h>
#include <vwModNum.h>
#include <private/handleLibP.h>
#endif	/* HOST */

#include <symbol.h>
#include <private/symbolP.h>
#include <dllLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Status codes */

/* Defines */

/* Indexes into the array of segment descriptors */

#define TEXT_SEG_DESC_INDEX 0
#define DATA_SEG_DESC_INDEX 1
#define BSS_SEG_DESC_INDEX 2

#define NUM_KERNEL_MODULE_SEGS  3

/* Type definitions */

typedef unsigned int LOAD_FLAG_T;       /* load flag type */

/* information associated with module while loading is in progress */

typedef enum module_source		/* method file was specified by */
    {
    FROM_FD	   = 0,			/* opened from file descriptor */
    FROM_FILENAME  = 1			/* opened from file name */
    } MODULE_SOURCE;
						   
typedef enum mseek_mode			/* Module position mode flags     */
    {
    MSEEK_SET	= 0,			/* Set pos. from the beginnning   */
    MSEEK_CUR	= 1			/* Set pos. from the current loc. */
    } MSEEK_MODE;

/* Types used throughout various loader header files */

typedef void *          SYM_ADRS;               /* symbol's address */
typedef void **         SYM_ADRS_TBL;           /* table of symbol's addr */

typedef void *          SCN_ADRS;               /* section's address */
typedef void **         SCN_ADRS_TBL;           /* table of section's addr */

typedef enum load_type			/* type of load being performed */
    {
    LOAD_UNKNOWN       = 0,
    LOAD_SYS_SYM_TBL   = 1,  /* Load the system symbol table */
    LOAD_VXWORKS_IMG   = 2,  /* Load vxWorks image (copy on host for tgtsvr) */
    LOAD_STAT_EXE      = 3,  /* Load statically linked executable */
    LOAD_DYN_EXE       = 4,  /* Load dynamically linked executable */
    LOAD_KERNEL_MODULE = 5,  /* Load relocatable module into kernel */
    LOAD_SYMS_ONLY     = 6   /* Load symbols only */
    } LOAD_TYPE;

/* 
 * Encapsulation of filesystem accesses. This is where the target loader's cache
 * sits (no cache for the host loader).
 */

typedef struct load_module_info		/* information about file to load */
    {
    int			fd;		/* file descriptor */
    char *		fileName;	/* textual filename from descriptor */
    MODULE_SOURCE       moduleOpened;   /* FROM_FD or FROM_FILENAME */
    LOAD_TYPE           loadType;	/* relocatable, executable, ... */
#ifndef HOST
    void * 		cacheBuffer;	/* readahead buffer */
    size_t		usedCacheSize;  /* soft limit of the cache buffer */
    size_t		cacheIndex;	/* seek pointer into cache buffer */
    size_t		maxCacheSize;	/* tweakable cache size */
    off_t		fileIndex;	/* seek index into fd */
#endif
    } LOAD_MODULE_INFO;

typedef struct
    {
    SYM_ADRS    pAddr;  /* symbol's address */
    SYM_TYPE    type;   /* symbol's type */
    SYMBOL_ID   symId;  /* ID of the symbol */
    } SYM_INFO;
 
typedef SYM_INFO *      SYM_INFO_TBL;   /* table of symbol address/type info */
typedef SYM_INFO_TBL *  SYMINFO_REFS;   /* table of ptr to symbol info tables */ 
/* section types */

typedef enum section_type       /* Section types */
    {
    SECTION_UNKNOWN =   0,
    SECTION_RODATA =    1,      /* read-only data section */
    SECTION_TEXT =      2,      /* text section */
    SECTION_DATA =      3,      /* data section */
    SECTION_BSS =       4       /* bss section */
    } SECTION_TYPE;

typedef struct modListDesc * MODLIST_ID;        /* module list ID */
typedef struct sectionDesc * SECTION_ID;        /* section ID */

typedef enum section_type SECTION_T;

typedef struct sectionDesc      /* module section descriptor */
    {
#ifdef HOST
    OBJ_CORE    handle;                 /* handle management */
#else
    HANDLE  handle;                     /* handle management */
#endif  /* HOST */
    DL_NODE             sectionNode;    /* double-linked list node information*/
    char *              name;           /* section name */
    void *              address;        /* section address */
    size_t		size;           /* section size */
    enum section_type   type;           /* section type */
    int                 flags;          /* section flags */
    size_t		alignment;	/* section alignment */
    UINT32		checksum;       /* section cksum */
    } SECTION_DESC;

typedef struct section_info_desc        /* Info about a loadable section   */ 
    {
    SL_NODE             scnInfoNode;    /* Point to next node in list      */
    char *              name;           /* Section's name                  */
    enum section_type   type;           /* Section's type                  */
    off_t		offset;         /* Offset of section in object module*/
    size_t		size;           /* Section's size                    */
    size_t		alignment;      /* Section's alignment               */
    UINT32              flags;          /* Section's flags                   */
    void *              address;	/* Section's address             */
    off_t		offsetInSeg;    /* Section's offset in segment  */
    UINT32              directiveIdx;  /* Index of the related load directive*/
#ifdef HOST
    BOOL                scnIsCached;
#endif
    SECTION_ID          sectionId;
    } SECTION_INFO_DESC;

typedef struct load_segment_directive
    {
    UINT32	type;                    /* type of the segment */
    void *      address;                 /* address of the segment */
    BOOL        memAllocatedByCaller; /* True iff the caller allocated mem. */
    } LOAD_SEGMENT_DIRECTIVE;

/* variable declarations */

extern size_t	loaderCacheBufferSize;	    /* loader's cache buffer size */

/* declarations */

extern STATUS   loadModuleInfoFromFd (int fd, 
				      LOAD_MODULE_INFO * pLoadModuleInfo);
extern STATUS   loadModuleInfoFromFilenameOpen (char * fileName, 
						LOAD_MODULE_INFO * pLoadModuleInfo);
extern STATUS   loadModuleInfoRelease (LOAD_MODULE_INFO loadModuleInfo);
extern off_t	loadModuleSeek (LOAD_MODULE_INFO * pLoadModuleInfo, 
				off_t offset, MSEEK_MODE mode);
extern STATUS   loadModuleStringRead (LOAD_MODULE_INFO * pLoadModuleInfo, 
				      char * buffer, size_t nBytes);
extern STATUS	loadModuleInfoInit (LOAD_MODULE_INFO * pLoadModuleInfo, int fd,
				    char * fileName, MODULE_SOURCE source);
extern STATUS   loadModuleValueRead (LOAD_MODULE_INFO * pLoadModuleInfo, 
				     void * buffer, size_t nBytes);

#ifdef __cplusplus
}
#endif

#endif /* __INCloadFileLibPh */
