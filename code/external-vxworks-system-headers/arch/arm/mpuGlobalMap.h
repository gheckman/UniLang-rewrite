/* mpuGlobalMap.h - arch "independent" header MPU functionality */

/* 
 * Copyright (c) 2006 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01b,13jul06,m_h  Arch "independent" MPU definitions normally found in vmLib.h
                 (actually vmLibP.h)
01a,13jul06,m_h  written.
*/

#ifndef __INCmpuGlobalMaph
#define __INCmpuGlobalMaph

#include <private/vmLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

typedef struct mpuTransTblStruct * MPU_TRANS_TBL_ID;

typedef STATUS (*MPUGLOBALPAGEMAPFUNCPTR)(VIRT_ADDR, PHYS_ADDR, UINT, BOOL);
typedef STATUS (*MPUTRANSLATEFUNCPTR)(struct mpuTransTblStruct *, 
				      VIRT_ADDR, PHYS_ADDR *);
typedef STATUS (*MPUPHYSTRANSLATEFUNCPTR)(struct mpuTransTblStruct *,
					  PHYS_ADDR, VIRT_ADDR *);


typedef struct
    {
    FUNCPTR                 mpuLibInit;
    MPU_TRANS_TBL_ID      (*mpuTransTblCreate) ();
    FUNCPTR                 mpuTransTblDelete;
    FUNCPTR                 mpuEnable;
    FUNCPTR                 mpuStateSetRegion;
    FUNCPTR                 mpuStateGet;
    MPUGLOBALPAGEMAPFUNCPTR mpuGlobalPageMap;
    MPUTRANSLATEFUNCPTR     mpuTranslate;
    VOIDFUNCPTR             mpuCurrentSet;
    FUNCPTR                 mpuAttrTranslate;
    FUNCPTR                 mpuShow;
    } MPU_LIB_FUNCS;


#define MPU_ENABLE              (*(mpuLibFuncs.mpuEnable))
#define MPU_TRANS_TBL_CREATE    (*(mpuLibFuncs.mpuTransTblCreate))
#define MPU_STATE_SET_REGION    (*(mpuLibFuncs.mpuStateSetRegion))
#define MPU_CURRENT_SET         (*(mpuLibFuncs.mpuCurrentSet))
#define MPU_GLOBAL_PAGE_MAP     (*(mpuLibFuncs.mpuGlobalPageMap))
#define MPU_ATTR_TRANSLATE      (*(mpuLibFuncs.mpuAttrTranslate))

#define MPU_TRANSLATE 	        (*(mpuLibFuncs.mpuTranslate))

#define MPU_TRANS_TBL_DELETE    (*(mpuLibFuncs.mpuTransTblDelete))

#define MPU_SHOW                (*(mpuLibFuncs.mpuShow))

IMPORT MPU_LIB_FUNCS mpuLibFuncs;

IMPORT void mpuLibInstall (void);

IMPORT STATUS
    mpuGlobalMapInit (PHYS_MEM_DESC * pMemDescArray,
                      int numDescArrayElements,
                      BOOL enable,
                      int cacheDefault);

IMPORT STATUS
    mpuStateSet (void *addr, int len, UINT stateMask, UINT state);

IMPORT STATUS mpuShow (void);

#endif /*_ASMLANGUAGE*/



#ifdef __cplusplus
}
#endif

#endif /* __INCmpuGlobalMaph */
