/* pmLib.h - persistent memory header */

/*
 * Copyright (c) 2002-2004, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01j,29mar10,cww  LP64 adaptation
01i,14may04,md   track size of arena in header
01h,05aug03,dbs  allow more than one PM arena
01g,04aug03,dbs  ensure pmLib has no globals
01f,29jul03,dbs  re-introduce idea of 'closing' a region
01e,29jul03,dbs  remove pmRegionDelete API, add pmInvalidate
01d,18jul03,dbs  remove hard-coded limit on number of regions
01c,15jul03,dbs  increase size of key string
01b,14jul03,dbs  rename phpLib to pmLib
01a,11jul03,dbs  add phpFreeSpace API
000,28oct02, md  written, initial version
*/

#ifndef __INCpmLib_h
#define __INCpmLib_h

#ifdef __cplusplus
extern "C" {
#endif

/* general settings */

/* maximum number of regions available */

#define	PM_MAX_REGIONS	64
    
/* magic number of persistent heap */

#define	PM_MAGIC	((int) 0xBEEFBABE)

/* max length of key string */

#define PM_KEY_LEN	20

/* open region with 'read' enabled */

#define PM_PROT_RDONLY	0

/* open region with 'read' and 'write' enabled */

#define PM_PROT_RDWR	1

#define PM_PAGE_ALIGN(_ptr, _pageSize)	\
	((unsigned long) _ptr - ((unsigned long) _ptr % _pageSize))

/* types */

typedef void * (*PM_ARENA_DEF) (size_t *);

/*
 * PM region header.
 *
 * Each distinct region in the PM has a header at it start, with a
 * short human-readable 'key' and some housekeeping data. It is 16
 * bytes long, including the checksum field.
 */

typedef struct pm_region
    {
    off_t	offset;			/* offset of data block		*/
    size_t	size;			/* size of data block		*/
    int		magic;			/* magic number			*/
    char	key [PM_KEY_LEN];	/* textual key			*/
    } PM_REGION;
    
/*
 * Persistent memory block header
 *
 * One of these exists at the start of the memory region which is
 * owned and managed by pmLib.
 */

typedef struct pm_arena
    {
    int   checksum;			/* header checksum		    */
    struct 
	{
	void 	* raddr;		/* real address of memory	    */
	void 	* vaddr;		/* aliased virtual address 	    */
	size_t  arena_size;		/* total size of arena in bytes	    */
	size_t  data_size;		/* total size of block in bytes	    */
	off_t	next_free_offset;	/* next free offset		    */
	int	magic;			/* magic number			    */
	int	max_region;		/* max number of allocated regions  */
	PM_REGION region [1];		/* extensible array of regions	    */
	} field;
    }  PM_ARENA;

/* function declarations */

extern STATUS  pmLibInit	(void);
extern STATUS  pmInit		(PM_ARENA_DEF arena);
extern ssize_t pmFreeSpace	(PM_ARENA_DEF arena);
extern int     pmRegionCreate	(PM_ARENA_DEF arena, const char * key,
				 size_t size, int mode);
extern int     pmRegionOpen	(PM_ARENA_DEF arena, const char *key);
extern void *  pmRegionAddr	(PM_ARENA_DEF arena, int region);
extern ssize_t pmRegionSize	(PM_ARENA_DEF arena, int region);
extern STATUS  pmRegionProtect	(PM_ARENA_DEF arena, int region, int mode);
extern STATUS  pmRegionClose	(PM_ARENA_DEF arena, int region);
extern STATUS  pmInvalidate	(PM_ARENA_DEF arena);
extern STATUS  pmValidate	(PM_ARENA_DEF arena);
extern STATUS  pmShow		(PM_ARENA_DEF arena);

extern void * pmDefaultArena	(size_t *);

#ifdef  __cplusplus
}
extern STATUS pmInit (void * (*arena)(UINT32 *))
	   _WRS_DEPRECATED ("please use fully qualified function pointer "
			    "version of API");
extern ssize_t pmFreeSpace (void * (*arena)(UINT32 *))
	   _WRS_DEPRECATED ("please use fully qualified function pointer "
			    "version of API");
extern int pmRegionCreate (void * (*arena)(UINT32 *), const char * key,
			   size_t size, int mode)
	   _WRS_DEPRECATED ("please use fully qualified function pointer "
			    "version of API");
extern int pmRegionOpen (void * (*arena)(UINT32 *), const char * key)
	   _WRS_DEPRECATED ("please use fully qualified function pointer "
			    "version of API");
extern void * pmRegionAddr (void * (*arena)(UINT32 *), int region)
	   _WRS_DEPRECATED ("please use fully qualified function pointer "
			    "version of API");
extern ssize_t pmRegionSize (void * (*arena)(UINT32 *), int region)
	   _WRS_DEPRECATED ("please use fully qualified function pointer "
			    "version of API");
extern STATUS pmRegionProtect (void * (*arena)(UINT32 *), int region,
			       int mode)
	   _WRS_DEPRECATED ("please use fully qualified function pointer "
			    "version of API");
extern STATUS pmRegionClose (void * (*arena)(UINT32 *), int region)
	   _WRS_DEPRECATED ("please use fully qualified function pointer "
			    "version of API");
extern STATUS pmValidate (void * (*arena)(UINT32 *))
	   _WRS_DEPRECATED ("please use fully qualified function pointer "
			    "version of API");
extern STATUS pmInvalidate (void * (*arena)(UINT32 *))
	   _WRS_DEPRECATED ("please use fully qualified function pointer "
			    "version of API");
extern STATUS pmShow (void * (*arena)(UINT32 *))
	   _WRS_DEPRECATED ("please use fully qualified function pointer "
			    "version of API");

inline STATUS pmInit (void * (*arena)(UINT32 *))
    {
    return pmInit ((PM_ARENA_DEF) arena);
    }

inline ssize_t pmFreeSpace (void * (*arena)(UINT32 *))
    {
    return pmFreeSpace ((PM_ARENA_DEF) arena);
    }

inline int pmRegionCreate (void * (*arena)(UINT32 *), const char * key,
			   size_t size, int mode)
    {
    return pmRegionCreate ((PM_ARENA_DEF) arena, key, size, mode);
    }

inline int pmRegionOpen (void * (*arena)(UINT32 *), const char * key)
    {
    return pmRegionOpen ((PM_ARENA_DEF) arena, key);
    }

inline void * pmRegionAddr (void * (*arena)(UINT32 *), int region)
    {
    return pmRegionAddr ((PM_ARENA_DEF) arena, region);
    }

inline ssize_t pmRegionSize (void * (*arena)(UINT32 *), int region)
    {
    return pmRegionSize ((PM_ARENA_DEF) arena, region);
    }

inline STATUS pmRegionProtect (void * (*arena)(UINT32 *), int region,
			       int mode)
    {
    return pmRegionProtect ((PM_ARENA_DEF) arena, region, mode);
    }

inline STATUS pmRegionClose (void * (*arena)(UINT32 *), int region)
    {
    return pmRegionClose ((PM_ARENA_DEF) arena, region);
    }

inline STATUS pmValidate (void * (*arena)(UINT32 *))
    {
    return pmValidate ((PM_ARENA_DEF) arena);
    }

inline STATUS pmInvalidate (void * (*arena)(UINT32 *))
    {
    return pmInvalidate ((PM_ARENA_DEF) arena);
    }

inline STATUS pmShow (void * (*arena)(UINT32 *))
    {
    return pmShow ((PM_ARENA_DEF) arena);
    }

#endif /* __cplusplus */

#endif /* __INCpmLib_h */
