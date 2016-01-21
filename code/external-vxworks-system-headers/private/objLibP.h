/* objLibP.h - private object management library header */

/*
 * Copyright (c) 1992-1993, 2003-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
03m,12sep13,dee  cleanup static analysis defects WIND00433361
03l,09jul12,wzc  WIND00361531 - Remove building warnings.
03k,24apr12,jpb  Added declaration of objRoutineNameGet().
03j,11jan11,gls  fixed objVerifyAndProtect and objUnprotect when
                 _WRS_CONFIG_OBJECT_VERIFICATION not defined (WIND00247724)
03i,13oct10,jpb  Added sizeof OBJ_CORE to offset comments
03h,17sep10,gls  added alignment to OBJ_ALLOC_FUNC
03g,02sep10,jpb  Added function pointer *_func_objRtpObjEachHook.
03f,16aug10,cww  Use dynamically generated offsets in offset macros
03e,17feb10,pch  small footprint
03d,29apr10,pad  Moved extern C statement after include statements.
03c,06apr10,jpb  Added prototype for objClassTypeShow.
03b,31mar10,gls  fixed OBJ_PROTECT macros for OBJ_VERIFICATION VSB option
03a,12feb10,gls  added OBJ_VERIFY_AND_PROTECT() and OBJ_UNPROTECT()
02z,23dec09,zl   added OBJ_HANDLE_GEN_INCR and OBJ_HANDLE_GEN_MAX. Derive all
		 object handle macros from bit count definitions.
02y,16dec09,zl   added objMemAllot().
02x,23oct09,zl   use union for overloading middle field of HANDLE_TABLE_ENTRY.
02w,25sep09,zl   added OBJ_OWNER_NODE_TO_ID()
02v,16mar09,zl   fixed OBJ_SHOW_FUNC typedef.
02u,18feb09,zl   updated for LP64 support
02t,17sep09,s_s  modified OBJ_LOCK to use INT_CPU_MICRO_LOCK/UNLOCK
02s,14jul09,s_s  OBJ_LOCK now calls KERNEL_INT_CPU_LOCK/UNLOCK instead of
		 INT_CPU_LOCK/UNLOCK for UP
02r,07oct08,jpb  Defect 137389.  Renamed second parameter in OBJ_EACH.
02q,27aug08,jpb  Renamed VSB header file
02p,12aug08,jpb  Added macro for objEach to be shared through multiple files.
02o,09jul08,jpb  Remove _func_ownerListXXX if OBJECT_VERIFICATION not defined.
02n,18jun08,jpb  Added include path for kernel configurations options set in
		 vsb.
02m,20may08,jpb  Modifications for source build.  Renamed
		 INCLUDE_OBJ_VERIFY to _WRS_CONFIG_OBJECT_VERIFICATION,
		 _WRS_VX_SMP to _WRS_CONFIG_SMP.
02l,11mar08,mfj  Making OBJ_VERIFY conditional on _WRS_CONFIG_OBJ_VERIFY
02k,20aug07,pgh  Fix apigen failure for KERNEL_LOCK_OBJ_UNLOCK
02j,11apr07,jmg  Changed intLock()\intUnlock() in OBJ_LOCK()\OBJ_UNLOCK() to
		 be INT_CPU_LOCK()\INT_CPU_UNLOCK().
02i,03jan07,to   added KERNEL_LOCK_OBJ_UNLOCK macro
02h,07dec06,jln  modified OBJ_TRY_LOCK to return a BOOL value
02g,17nov06,mmi  update lock macro to use newer kernellock API's
02f,30aug06,lei  added _WRS_ARCH_HAS_NEW_KERNEL_LOCK
02e,07aug06,pcs  Add macro's OBJ_LOCK and OBJ_UNLOCK.
02d,16aug05,gls  added objOwnerLibInstalled
02c,25jul05,yvp  Reworked OBJ_VERIFY conditional definition.
02b,07jun05,yvp  Updated copyright. #include now with angle-brackets.
02a,02jun05,yvp  Reworked OBJ_VERIFY conditional for MKL.
01z,25mar05,job  OBJ_VERIFY only defined in checked build
01y,05may05,gls  added objShowInit()
01x,07apr05,gls  added objOwnershipInit() (SPR #106150)
01w,24jan05,aeg  added objRtpLibInit() function prototype (SPR #106381).
01v,01feb05,kk   moved objOwnerGet(), objHandleShow(), objHandleTblShow()
		 to objLib.h
01u,07sep04,dcc  added accessCnt to OBJ_CORE.
01t,14sep04,lei  moved objOwnerSet() prototype to objLib.h
01s,28sep04,fr   removed objCreateRtn from objOpen (SPR 101349)
01r,16aug04,dcc  added _objClose() prototype.
01q,16jul04,aeg  added objArchLibInit() function prototype, and changed
		 OBJ_VERIFY() to invoke arch specific objVerify() (SPR# 98168).
01p,05jul04,dcc  added handle table growing support.
01o,05may04,cjj  added objIdToObjHandle() definition.  Removed I960
		 preprocessor directives.
01n,29apr04,dcc  added objRtpIdToObjHandle() definition.
01m,09mar04,dcc  added WIND_OBJ_NAMED and WIND_OBJ_DELETE_ON_LAST_CLOSE
		 attributes. Moved objNameSet(), objOwnerGet(), and
		 objOwnerSet() prototypes from objLib.h
01l,04feb04,dcc  added reference counter to OBJ_CORE.
01k,06jan04,dcc  added OBJ_IS_REFERENCED macro
01j,26nov03,dcc  updated definition of OBJ_HANDLE
01i,31oct03,dcc  implemented modifications from code review.
01h,11sep03,dcc  added objHandleList member to the OBJ_CORE structure, and
		 added handle table management support.
01g,21aug03,dcc  removed WIND_OBJ_DISTRIBUTED and WIND_OBJ_SHARED flags. Added
		 objOpen() prototype.
01f,05apr03,to   replace PD with RTP
01e,14mar03,dcc  ported from AE1.1
01d,15oct93,cd   added #ifndef _ASMLANGUAGE.
01c,10dec93,smb  removed objHelp
01b,22sep92,rrr  added support for c++
01a,04jul92,jcf  extracted from v1j objLib.h.
*/

#ifndef __INCobjLibPh
#define __INCobjLibPh

#include <vxWorks.h>
#include <vsbConfig.h>
#include <dllLib.h>
#include <objLib.h>
#include <classLib.h>
#include <private/handleLibP.h>
#include <private/intMicroLibP.h>

#ifndef _ASMLANGUAGE
#include <stdarg.h>
#endif	/* _ASMLANGUAGE */

#ifdef _WRS_CONFIG_SMP
#include <vxAtomicLib.h>
#include <private/vxSmpP.h>
#include <private/kernelLockLibP.h>
#endif /* _WRS_CONFIG_SMP */

/* object attributes */

#define WIND_OBJ_NAME_DYNAMIC  0x01	/* object name dynamically allocated */
#define WIND_OBJ_DEALLOC_MEM   0x02	/* free object memory on destroy */
#define WIND_OBJ_INSTRUMENTED  0x04	/* WindView instrumented object */
#define WIND_OBJ_DELETE_ON_LAST_CLOSE 0x08  /* object will be deleted on the */
					    /* last close even if it is not */
					    /* previously unlinked */
#define WIND_OBJ_ORPHANED      0x10	/* unable to reclaim object */
#define WIND_OBJ_NO_RECLAIM    0x20	/* automatic reclamation disabled */
#define WIND_OBJ_PUBLIC	       0x40	/* object is public */
#define WIND_OBJ_NAMED	       0x80	/* object is named */
#define WIND_OBJ_DELETED       0x100    /* object is deleted */

#ifndef _ASMLANGUAGE

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct wind_obj		/* OBJ_CORE */
    {
    HANDLE		handle;		/* 0x00/0x00: handle */
    DL_LIST		ownerList;	/* 0x10/0x18: list of owned objects */
    DL_NODE		ownerNode;	/* 0x18/0x28: owner list node */
    DL_NODE		classNode;	/* 0x20/0x38: class list node */
    struct wind_obj *	ownerId;	/* 0x28/0x48: pointer to obj owner */
    RTP_ID		ownerRtpId;	/* 0x2c/0x50: object owner's RTP */
    char *		name;		/* 0x30/0x58: object name */
    struct wind_class *	pObjClass;	/* 0x34/0x60: pointer to obj class */
    DL_LIST		objHandleList;	/* 0x38/0x68: list of handles */
    UINT16		refCnt;		/* 0x40/0x78: reference counter */
    UINT16		accessCnt;	/* 0x42/0x7a: access counter */
#ifdef _WRS_CONFIG_LP64
    UINT32		padding;	/* ----/0x7c: explicit padding */
#endif	/* _WRS_CONFIG_LP64 */
    } OBJ_CORE;				/* 0x44/0x80: sizeof OBJ_CORE */


/*
 * Handles are constructed from three fields: handle index, generation 
 * count, and a reserved bit.
 * 
 * Handles are stored in a two-level table structure: a master table with
 * OBJ_MASTER_TBL_SIZE number of entries entries (populated as needed) 
 * pointing to the second-level handle tables with OBJ_HANDLE_TBL_SIZE 
 * number of entries.
 * 
 * The maximum number of handles is OBJ_HANDLE_INDEX_CNT.
 *
 * OBJ_INDEX_GET() macro returns the handle index
 * OBJ_ENTRY_INDEX_GET() macro returns the index in the second-level table
 * OBJ_TABLE_INDEX_GET() macro returns the index in the master table
 */

#define OBJ_HANDLE_INDEX_BITS	16	/* bit count for handle index */
#define OBJ_HANDLE_GEN_BITS	15	/* bit count for generation nunmber */
#define OBJ_HANDLE_ENTRY_BITS	8	/* portion of index used for */
					/* second-level table */

#define OBJ_HANDLE_INDEX_CNT	(1 << OBJ_HANDLE_INDEX_BITS)	/* 00010000 */
#define OBJ_HANDLE_TBL_SIZE	(1 << OBJ_HANDLE_ENTRY_BITS)	/* 256 */
#define OBJ_MASTER_TBL_SIZE	(OBJ_HANDLE_INDEX_CNT / OBJ_HANDLE_TBL_SIZE)

#define OBJ_INDEX_GET(objHdl)		((objHdl) & (OBJ_HANDLE_INDEX_CNT - 1))
#define OBJ_ENTRY_INDEX_GET(objHdl)	((objHdl) & (OBJ_HANDLE_TBL_SIZE - 1))
#define OBJ_TABLE_INDEX_GET(objHdl)	(OBJ_INDEX_GET(objHdl) >> 	       \
					 OBJ_HANDLE_ENTRY_BITS)

/* increment for generation number */

#define OBJ_HANDLE_GEN_INCR	OBJ_HANDLE_INDEX_CNT		/* 00010000 */
#define OBJ_HANDLE_GEN_MAX	(((1 << OBJ_HANDLE_GEN_BITS) - 1) <<	      \
				   OBJ_HANDLE_INDEX_BITS)	/* 7fff0000 */

/* convert a specific object type's struct ptr to an OBJ_CORE ptr */

#define OBJ_RESOLVE(pObj) ((OBJ_CORE *)(pObj))

/* convert an OBJ_CORE ptr to a specific object type's struct ptr */

#define OBJ_UNRESOLVE(pObj) ((OBJ_ID)(pObj))

/* convert from ownerNode to object ID */

#define OBJ_OWNER_NODE_TO_ID(pNode)	((OBJ_CORE *)((long)(pNode) - \
						OFFSET (OBJ_CORE, ownerNode)))
    
#define MAX_ROUTINE_NAME_LEN	64	/* maximum length for routine symbol */    

typedef struct handle_table_entry
    {
    DL_NODE		handleNode;	/* node for OBJ_CORE.objHandleList */
    union
	{
	OBJ_ID		entryObjId;	/* if allocated: object ID */
	int		nextFree;	/* if free: link to next free entry */
	} u;
    OBJ_HANDLE		objHandle;	/* object handle */
    } HANDLE_TABLE_ENTRY;

/*
 * the order of the members in HANDLE_TABLE is important. Some routines such
 * as objHandleFreeAll() rely on the fact that handleTable is the first
 * member.
 */

typedef struct handle_table
    {
    HANDLE_TABLE_ENTRY		 handleTable [OBJ_HANDLE_TBL_SIZE];
    struct master_handle_table * pMasterTbl;
    } HANDLE_TABLE;

typedef struct master_handle_table
    {
    struct handle_table * pHandleTable [OBJ_MASTER_TBL_SIZE];
    int			  firstFree; /* index of most recent free slot */
    int			  size;      /* size of all handle tables combined */
    UINT32		  initIndex;
    UINT32		  genNumber;
    SEM_ID		  hdlTblSemId;
    } MASTER_HANDLE_TABLE;

typedef OBJ_ID (*OBJ_CREATE_FUNC)	 (const char * name, va_list vaList);
typedef STATUS (*OBJ_DESTROY_FUNC)	 (OBJ_ID objId, BOOL dealloc);
typedef STATUS (*OBJ_SHOW_FUNC)		 (OBJ_ID objId, int showType);
typedef void * (*OBJ_ALLOC_FUNC)	 (void * pMemPool, size_t nbytes,
					  size_t alignment);
typedef STATUS (*OBJ_FREE_FUNC)		 (void * pMemPool, void * pObj);
typedef BOOL   (*OBJ_EACH_FUNC)		 (OBJ_ID objId, void * pArg);

typedef STATUS (*OBJ_OWNER_LOCK_FUNC)	 (RTP_ID classId);
typedef STATUS (*OBJ_OWNER_UNLOCK_FUNC)  (RTP_ID classId);
typedef void   (*OBJ_OWNER_ADD_FUNC)	 (OBJ_CORE * pObjCore);
typedef void   (*OBJ_OWNER_REMOVE_FUNC)  (OBJ_CORE * pObjCore);
typedef STATUS (*OBJ_OWNER_RECLAIM_FUNC) (OBJ_CORE * pObjCore);
typedef STATUS (*OBJ_OWNER_SETBASE_FUNC) (OBJ_CORE * pObj, OBJ_CORE * pOwner);
typedef STATUS (*OBJ_OWNER_SET_FUNC)	 (OBJ_ID objId, OBJ_ID ownerId);

typedef void   (*OBJ_HFREE_ALL_FUNC)	 (OBJ_CORE * pObjCore);
typedef OBJ_HANDLE (*OBJ_HALLOC_FUNC)	 (OBJ_ID objId, RTP_ID rtpId);
typedef STATUS (*OBJ_CORE_RLS_FUNC)	 (OBJ_ID objId);
typedef OBJ_ID (*OBJ_HANDLE_TO_ID_FUNC)	 (OBJ_HANDLE handle, RTP_ID rtpId,
					  BOOL access);
typedef STATUS (*OBJ_NAME_SET_FUNC)	 (OBJ_CORE * pObj, CLASS_ID classId,
					  char * name);

/*******************************************************************************
*
* OBJ_LOCK - lock the object to perform kernel work
*
* This macro
*    acquires the kernel spinlock "kernelStateLock"for an SMP based system.
*    locks the interrupt for a UP based system.
*
* classId  - is not used for now. It is there so that in future each of the WIND
*             kernel object's could have there own spinlock's if desired.
* lockLevel - is not used for an SMP based system. It is required for a UP based
*              system.
*
* \NOMANUAL
*/

#ifdef  _WRS_CONFIG_SMP

#define OBJ_TRY_LOCK(classId,lockLevel)		KERNEL_LOCK_TRY()

#define OBJ_LOCK(classId,lockLevel)		KERNEL_LOCK_TAKE()

#else /* _WRS_CONFIG_SMP */

#define OBJ_LOCK(classId,lockLevel)                                          \
    do                                                                       \
	{                                                                    \
	lockLevel = INT_CPU_MICRO_LOCK();                         	     \
	} while ((0))

#endif /* _WRS_CONFIG_SMP */


/*******************************************************************************
*
* OBJ_UNLOCK - unlock the object after performing kernel work
*
* This macro
*    drains the work queue by calling windExit() for an SMP based system.
*    unlocks the interrupt for a UP based system.
*
* classId  - is not used for now. It is there so that in future each of the WIND
*             kernel object's could have there own spinlock's if desired.
* lockLevel - is not used for an SMP based system. It is required for a UP based
*              system.
*
* \NOMANUAL
*/

#ifdef  _WRS_CONFIG_SMP

#define OBJ_UNLOCK(classId,lockLevel)	windExit()

#else /* _WRS_CONFIG_SMP */

#define OBJ_UNLOCK(classId,lockLevel)	INT_CPU_MICRO_UNLOCK (lockLevel)

#endif /* _WRS_CONFIG_SMP */


/*******************************************************************************
*
* KERNEL_LOCK_OBJ_UNLOCK - take kernelLock then unlock the object
*
* This macro
*    locks the kernel, then unlocks the object.
*
* classId  - is not used for now. It is there so that in future each of the
*	     WIND kernel objects could have its own spinlock if desired.
* lockLevel - is not used for an SMP based system. It is required for a UP
*	      based system.
*
* \NOMANUAL
*/

#ifdef  _WRS_CONFIG_SMP

#define KERNEL_LOCK_OBJ_UNLOCK(classId,lockLevel)	/* no-op for SMP */

#else /* _WRS_CONFIG_SMP */

#define KERNEL_LOCK_OBJ_UNLOCK(classId,lockLevel)                            \
    do                                                                       \
	{                                                                    \
	KERNEL_LOCK();                                                       \
	OBJ_UNLOCK(classId,lockLevel);                                       \
	} while ((0))

#endif /* _WRS_CONFIG_SMP */

/*******************************************************************************
*
* OBJ_SET_DEALLOC_MEM - object memory to be freed when destroyed
*
* This macro sets the appropriate object attribute bit such that the
* object memory is deallocated when the object destroy routine is called
* through the automatic resource reclamation mechanism.
*
* This macro is only useful for object classes that register a destroy
* routine that requires a 'dealloc' parameter.
*
* RETURNS: N/A
*
* \NOMANUAL
*/

#ifdef	_WRS_CONFIG_MEM_ALLOT
#define OBJ_SET_DEALLOC_MEM(objId)	/* empty, since nothing can be freed */
#else	/* _WRS_CONFIG_MEM_ALLOT */
#define OBJ_SET_DEALLOC_MEM(objId)					     \
    (									     \
    ((OBJ_CORE *)(objId))->handle.attributes |= WIND_OBJ_DEALLOC_MEM	     \
    )
#endif	/* _WRS_CONFIG_MEM_ALLOT */


/*******************************************************************************
*
* OBJ_RECLAIM_DISABLE - disable automatic resource reclamation
*
* This macro sets the appropriate object attribute bit such that the
* object will not be destroyed by the automatic resource reclamation
* mechanism.
*
* RETURNS: N/A
*
* \NOMANUAL
*/

#ifdef	_WRS_CONFIG_MEM_ALLOT
#define OBJ_RECLAIM_DISABLE(objId)	/* empty, since nothing is reclaimed */
#else	/* _WRS_CONFIG_MEM_ALLOT */
#define OBJ_RECLAIM_DISABLE(objId)					     \
    (									     \
    ((OBJ_CORE *)(objId))->handle.attributes |= WIND_OBJ_NO_RECLAIM	     \
    )
#endif	/* _WRS_CONFIG_MEM_ALLOT */


/*******************************************************************************
*
* OBJ_IS_RECLAIM_DISABLE - is object disabled from automatic RR?
*
* This macro checks whether the specified object is disabled from automatic
* resource reclamation.
*
* RETURNS: TRUE if object is disabled from RR, otherwise FALSE.
*
* \NOMANUAL
*/

#ifdef	_WRS_CONFIG_MEM_ALLOT
#define OBJ_IS_RECLAIM_DISABLE(objId)	TRUE	/* no reclamation */
#else	/* _WRS_CONFIG_MEM_ALLOT */
#define OBJ_IS_RECLAIM_DISABLE(objId)					    \
    (									    \
    (((OBJ_CORE *)(objId))->handle.attributes & WIND_OBJ_NO_RECLAIM) != 0   \
    )
#endif	/* _WRS_CONFIG_MEM_ALLOT */


/*******************************************************************************
*
* OBJ_INSTRUMENTATION_ENABLE - enable WindView instrumentation
*
* This macro sets the appropriate object attribute bit such that the
* WindView instrumentation is enabled for the specified object.
*
* RETURNS: N/A
*
* \NOMANUAL
*/

#define OBJ_INSTRUMENTATION_ENABLE(objId)				     \
    (									     \
    ((OBJ_CORE *)(objId))->handle.attributes |= WIND_OBJ_INSTRUMENTED	     \
    )


/*******************************************************************************
*
* OBJ_INSTRUMENTATION_DISABLE - disable WindView instrumentation
*
* This macro clears the appropriate object attribute bit such that the
* WindView instrumentation is disabled for the specified object.
*
* RETURNS: N/A
*
* \NOMANUAL
*/

#define OBJ_INSTRUMENTATION_DISABLE(objId)				     \
    (									                     \
    (((OBJ_CORE *)(objId))->handle.attributes =              \
     (UINT16)((((OBJ_CORE *)(objId))->handle.attributes)     \
     &(~WIND_OBJ_INSTRUMENTED)))                             \
    )


/*******************************************************************************
*
* OBJ_VERIFY - check the validity of an object pointer
*
* This macro verifies the existence of the specified object by comparing the
* object's classId with the expected class id.  If the object does not check
* out, errno is set with the invalid id status.
*
* If the customer builds the system without object verification (for a faster
* and smaller kernel) the function call is simply replaced with "OK". In the
* case where this makes one branch of an "if-else" statement dead (e.g. "if
* (OBJ_VERIFY(objId) == OK) {..." ) the compiler will remove everything except
* the live statement from the resulting assembly code.
*
* RETURNS: OK or ERROR if invalid object id
*
* \NOMANUAL
*/

#ifdef _WRS_CONFIG_OBJECT_VERIFICATION
#define OBJ_VERIFY(objId,classId)		objVerify (objId, classId)
#else	/* _WRS_CONFIG_OBJECT_VERIFICATION */
#define OBJ_VERIFY(objId, classId)		OK
#endif	/* _WRS_CONFIG_OBJECT_VERIFICATION */


/*******************************************************************************
*
* OBJ_IS_OWNER - does the object own any other objects?
*
* This macro checks whether the specified object is the owner of
* any other object.
*
* RETURNS: TRUE if object owns at least one other object, otherwise FALSE.
*
* \NOMANUAL
*/

#define OBJ_IS_OWNER(objId)						    \
    (									    \
    DLL_FIRST (&((OBJ_CORE *)(objId))->ownerList) != NULL		    \
    )


/*******************************************************************************
*
* OBJ_IS_REFERENCED - is this object referenced by an object handle?
*
* This macro checks whether there is any object handle referencing this object.
*
* RETURNS: TRUE if object has at least one object handle, otherwise FALSE.
*
* \NOMANUAL
*/

#define OBJ_IS_REFERENCED(objId)					    \
    (									    \
    DLL_FIRST (&((OBJ_CORE *)(objId))->objHandleList) != NULL		    \
    )


/*******************************************************************************
*
* OBJ_IS_PUBLIC - is the object public ?
*
* This macro checks if the object is public or not
*
* RETURNS: TRUE if object is public, otherwise FALSE.
*
* \NOMANUAL
*/

#define OBJ_IS_PUBLIC(objId)						    \
    (									    \
    (((OBJ_CORE *)(objId))->handle.attributes & WIND_OBJ_PUBLIC) != 0	    \
    )


/*******************************************************************************
*
* OBJ_SET_PUBLIC - set an object as public
*
* This macro sets the bit WIND_OBJ_PUBLIC in OBJ_CORE.handle.attributes
*
* \NOMANUAL
*/

#define OBJ_SET_PUBLIC(objId)						    \
    (									    \
    ((OBJ_CORE *)(objId))->handle.attributes |= WIND_OBJ_PUBLIC		    \
    )


/*******************************************************************************
*
* OBJ_IS_NAMED - is the object named ?
*
* This macro checks if the object is named or not. This macro is used to
* determine if an object must follow the POSIX model for deletion
* (i.e. unlink + close).
*
* RETURNS: TRUE if object is named, otherwise FALSE.
*
* \NOMANUAL
*/

#define OBJ_IS_NAMED(objId)						    \
    (									    \
    (((OBJ_CORE *)(objId))->handle.attributes & WIND_OBJ_NAMED) != 0	    \
    )


/*******************************************************************************
*
* OBJ_SET_NAMED - set an object as named
*
* This macro sets the bit WIND_OBJ_NAMED in OBJ_CORE.handle.attributes. The
* setting of this bit indicates that an object must follow the POSIX model
* for deletion, i.e. must be unlinked and closed.
*
* \NOMANUAL
*/

#define OBJ_SET_NAMED(objId)						    \
    (									    \
    ((OBJ_CORE *)(objId))->handle.attributes |= WIND_OBJ_NAMED		    \
    )


/*******************************************************************************
*
* OBJ_IS_DELETE_ON_LAST_CLOSE - is the object to be deleted on the last close?
*
* This macro checks if the object is set to be deleted on the last close, i.e.
* no need to be unlinked first.
*
* RETURNS: TRUE if object is to be deleted on the last close, otherwise FALSE.
*
* \NOMANUAL
*/

#define OBJ_IS_DELETE_ON_LAST_CLOSE(objId)				    \
    (									    \
    (((OBJ_CORE *)(objId))->handle.attributes &				    \
    WIND_OBJ_DELETE_ON_LAST_CLOSE) != 0					    \
    )


/*******************************************************************************
*
* OBJ_SET_DELETE_ON_LAST_CLOSE - set an object to be deleted on the last close
*
* This macro sets the bit WIND_OBJ_DELETE_ON_LAST_CLOSE in
* OBJ_CORE.handle.attributes. The setting of this bit indicates that a named
* object does not need to be unlinked before being deleted.
*
* \NOMANUAL
*/

#define OBJ_SET_DELETE_ON_LAST_CLOSE(objId)				    \
    (									    \
    ((OBJ_CORE *)(objId))->handle.attributes |=				    \
    WIND_OBJ_DELETE_ON_LAST_CLOSE					    \
    )


/*******************************************************************************
*
* OBJ_IS_DELETED - is the object deleted?
*
* This macro checks if the object has been already deleted or not. This macro
* is used to determine if an object's memory should be freed when its access
* counter is zero.
*
* RETURNS: TRUE if object is being deleted, otherwise FALSE.
*
* \NOMANUAL
*/

#define OBJ_IS_DELETED(objId)						    \
    (									    \
    (((OBJ_CORE *)(objId))->handle.attributes & WIND_OBJ_DELETED) != 0      \
    )


/*******************************************************************************
*
* OBJ_SET_DELETED - set an object as deleted
*
* This macro sets the bit WIND_OBJ_DELETED in OBJ_CORE.handle.attributes
* The setting of this bit indicates that a the object has been deleted and its
* memory is ready to be freed when its access counter is zero.
*
* \NOMANUAL
*/

#define OBJ_SET_DELETED(objId)						    \
    (									    \
    ((OBJ_CORE *)(objId))->handle.attributes |= WIND_OBJ_DELETED	    \
    )


/*******************************************************************************
*
* OBJ_EACH - Call routine to examine each object of the specified object type
*
* This macro traverses object list and calls routine passed in.
*
* \NOMANUAL
*/

#define OBJ_EACH(list, pNode, routine, arg, objId)			\
	{								\
	DL_NODE * pNextNode;						\
	pNode = DLL_FIRST (&list);				    	\
	while (pNode != NULL)                          			\
	    {                                                           \
	    objId = CLASS_NODE_TO_OBJ_ID (pNode);			\
	    pNextNode = DLL_NEXT (pNode);				\
	    if ((* routine) (objId, arg) == FALSE)			\
	    	    break;						\
	    pNode = pNextNode;						\
	    }								\
	}


/* variable declarations */

extern BOOL objOwnerLibInstalled;

#ifdef _WRS_CONFIG_OBJECT_OWNERSHIP
extern OBJ_OWNER_LOCK_FUNC	_func_ownerListLock;
extern OBJ_OWNER_UNLOCK_FUNC	_func_ownerListUnlock;
extern OBJ_OWNER_ADD_FUNC	_func_objOwnerListAdd;
extern OBJ_OWNER_REMOVE_FUNC	_func_objOwnerListRemove;
extern OBJ_OWNER_RECLAIM_FUNC	_func_objOwnerReclaim;
extern OBJ_OWNER_SETBASE_FUNC	_func_objOwnerSetBaseInternal;
extern OBJ_OWNER_SET_FUNC	_func_objOwnerSetInternal;
#endif /* _WRS_CONFIG_OBJECT_OWNERSHIP */

extern OBJ_HFREE_ALL_FUNC	_func_handleFreeAll;
extern OBJ_HALLOC_FUNC		_func_handleAlloc;
extern OBJ_CORE_RLS_FUNC	_func_objCoreRelease;
extern OBJ_HANDLE_TO_ID_FUNC	_func_objHandleToObjId;
extern OBJ_NAME_SET_FUNC	_func_objNameVerifiedSet;

/* function declarations */

extern void *	objAlloc		(CLASS_ID classId);
extern void *	objAllocExtra		(CLASS_ID classId, size_t nExtraBytes,
					 void ** ppExtra);
#ifdef _WRS_CONFIG_MEM_ALLOT
extern void *	objMemAllot		(void * pMemPool, size_t nbytes,
					 size_t alignment);
#endif	/* _WRS_CONFIG_MEM_ALLOT */

extern CLASS_ID objClassIdGet		(enum windObjClassType classType);
extern void	objCoreInit		(OBJ_CORE * pObjCore,
					 CLASS_ID pObjClass);
extern STATUS	objCoreTerminate	(OBJ_CORE * pObjCore);
extern void	objCoreUnlink		(OBJ_CORE * pObjCore, CLASS_ID classId);
extern OBJ_ID	objEach			(enum windObjClassType classType,
					 OBJ_EACH_FUNC routine, void * pArg,
					 BOOL objPublic);
extern STATUS	objFree			(CLASS_ID classId, OBJ_ID objectId);
extern int	objInfo			(enum windObjClassType classType,
					 OBJ_ID objIdArray[],
					 int maxIds);
extern char *	objNamePtrGet		(OBJ_ID objId);
extern STATUS	objNamePtrSet		(OBJ_ID objId, char * name);
extern STATUS	objNameSet		(OBJ_ID objId, const char *name);
extern STATUS	objVerify		(OBJ_ID objId, CLASS_ID classId);
extern STATUS	objGenericVerify	(OBJ_ID objId);
extern STATUS	objRtpTaskDelete	(RTP_ID rtpId);
extern STATUS	objOwnerSetBase		(OBJ_CORE * pObj, OBJ_CORE * pOwnerObj);
extern STATUS	objLibInit		(OBJ_ALLOC_FUNC objMemAllocRtn,
					 OBJ_FREE_FUNC objMemFreeRtn,
					 void * objMemPoolId, int options);
extern void	objOwnershipInit	(void);
extern BOOL	objOwnerListInstalled	(void);
extern STATUS	objArchLibInit		(void);
extern void	objShowInit		(void);

extern STATUS	objCoreReclaim		(OBJ_CORE * pObjCore);
extern void	objCoreInvalidate	(OBJ_CORE * pObjCore);
extern OBJ_HANDLE objHandleAlloc	(OBJ_ID objId, RTP_ID rtpId);
extern OBJ_ID   objHandleToObjId	(OBJ_HANDLE handle, RTP_ID rtpId,
					 BOOL access);
extern STATUS   objHandleDelete		(OBJ_HANDLE handle, int options);

extern OBJ_ID   objOpen			(const char * name, int flags,
					 CLASS_ID classId, ...);
extern STATUS	objHandleClose		(OBJ_HANDLE handle, RTP_ID rtpId);
extern STATUS   objClose		(OBJ_ID objId, CLASS_ID	classId);
extern STATUS	objUnlink		(const char * name, CLASS_ID classId);

extern void	objHandleTblTerminate	(RTP_ID rtpId);
extern STATUS	objHandleTblCreate	(RTP_ID rtpId);
extern OBJ_HANDLE objIdToObjHandle	(OBJ_ID objId, RTP_ID rtpId);
extern OBJ_HANDLE objRtpIdToObjHandle	(RTP_ID rtpId);
extern STATUS	_objClose		(OBJ_CORE * pObjCore, int level,
					 BOOL dealloc);
extern void *	objMemAlloc		(size_t nBytes);
extern STATUS	objMemFree		(void * pBuffer);
extern STATUS	objCoreRelease		(OBJ_ID objId);
extern STATUS	objRtpLibInit		(void);

extern void objClassTypeShow		(OBJ_CORE * pObj, char * fmt,
					 int level);
extern char * objRoutineNameGet 	(FUNCPTR   entry, char * pString,
                              		 size_t strLen);

#ifdef _WRS_ARCH_HAS_OBJ_SAFE
#ifdef _WRS_CONFIG_SMP

extern STATUS	objVerifiedSafe		(OBJ_ID objId, CLASS_ID classId);
extern void	objUnprotect		(OBJ_ID objId, CLASS_ID classId,
					 int level);

/*******************************************************************************
*
* objVerifyAndProtect - check the validity of an object and increment safeCnt
*
* This macro verifies the existence of the specified object by comparing the
* object's classId with the expected class id.  If the object does not check
* out, errno is set with the invalid id status.
*
* If valid, the 'safeCnt' of the object is incremented and interrupts are
* locked.  The lock level is written to the location pointed to by 'pLevel'.
*
* If the customer builds the system without object verification (for a faster 
* and smaller kernel) the function call is simply replaced with "OK". In the 
* case where this makes one branch of an "if-else" statement dead (e.g. "if 
* (OBJ_VERIFY_AND_PROTECT(objId) == OK) {..." ) the compiler will remove 
* everything except the live statement from the resulting assembly code.
*
* RETURNS: OK or ERROR if invalid object id
*
* \NOMANUAL
*/

_WRS_INLINE STATUS objVerifyAndProtect 
    (
    OBJ_ID	objId,
    CLASS_ID	classId,
    int *	pLevel
    )
    {
    int level;

    level = INT_CPU_MICRO_LOCK ();

#ifdef _WRS_CONFIG_OBJECT_VERIFICATION
    if (objVerifiedSafe (objId, classId) != OK)
	{
	INT_CPU_MICRO_UNLOCK (level);
	return (ERROR);
	}
#endif /* _WRS_CONFIG_OBJECT_VERIFICATION */

    *pLevel = level;

    return (OK);
    }

/*******************************************************************************
*
* objUnprotect_inline - decrement an object's safeCnt
*
* This routine decrements an object's safe count.
*
* If the customer builds the system without object verification (for a faster 
* and smaller kernel) the function call will simply unlock interrupts using
* the locking level passed in 'level'.
*
* If the customer builds the system without object verification (for a faster 
* and smaller kernel) the function call is omitted.
*
* RETURNS: N/A
*
* \NOMANUAL
*/

_WRS_INLINE void objUnprotect_inline
    (
    OBJ_ID   objId,
    CLASS_ID classId,
    int      level
    )
    {
#ifdef _WRS_CONFIG_OBJECT_VERIFICATION
    (void)vxAtomic32Dec_inline ((atomic32_t *)&((HANDLE_ID) objId)->safeCnt);
#endif /* _WRS_CONFIG_OBJECT_VERIFICATION */

    INT_CPU_MICRO_UNLOCK (level);

    return;
    }

#define OBJ_VERIFY_AND_PROTECT objVerifyAndProtect
#define OBJ_UNPROTECT objUnprotect
#define OBJ_UNPROTECT_INLINE objUnprotect_inline

#endif /* _WRS_CONFIG_SMP */
#endif /* _WRS_ARCH_HAS_OBJ_SAFE */

/* function pointers */

extern OBJ_ID (*_func_objRtpObjEachHook)(enum windObjClassType classType, 
                                         OBJ_EACH_FUNC routine,
                                         void *  arg, 
                                         BOOL objPublic);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#else	/* _ASMLANGUAGE */

/*
 * offsets for architecture optimized implementations - these must be in an ASM
 * section due to a circular dependency when compiling offsets.c
 *
 * WARNING: the old offset macros are provided temporarily only for a
 * transitionary phase.  They will be removed once existing references are
 * updated to use the dynamically generated offsets.
 */

#ifndef _WRS_CONFIG_LP64
#include <private/offsetMacrosP.h>

#define WIND_OBJ_CORE_SIZE		WIND_OBJ_SIZEOF
#define WIND_OBJ_CORE_HANDLE_ATTRIBUTES	HANDLE_ATTRIB
#define WIND_OBJ_CORE_CLASS_ID		WIND_OBJ_pObjClass_OFFSET
#endif	/* _WRS_CONFIG_LP64 */

#endif /* _ASMLANGUAGE */

#endif /* __INCobjLibPh */
