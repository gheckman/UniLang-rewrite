/* smObjLibP.h - private shared memory objects library header file */

/*
 * Copyright (c) 1992-1994, 2010-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01j,26dec11,swg  remove _func_smObjObjShow (CQ:WIND00291069)
01i,02sep10,jpb  Added function pointer _func_smObjObjShow.
01h,29apr10,pad  Moved extern C statement after include statements.
01g,01aug94,dvs  backed out pme's changes for reserved fields in main data structures.
01f,20mar94,pme  added reserved fields in main data structures to allow
		 compatibility between future versions.
01e,29jan93,pme  added little endian support
01d,22sep92,rrr  added support for c++
01c,23aug92,jcf  fixed struct reference.
01b,30jul92,pme  added smObjTaskDeleteFailRtn declaration.
01a,19jul92,pme  extracted from smObjLib v1d.
*/

#ifndef __INCsmObjLibPh
#define __INCsmObjLibPh

#include <vwModNum.h>
#include <smObjLib.h>
#include <smDllLib.h>
#include <smLib.h>
#include <private/smNameLibP.h>
#include <private/smFixBlkLibP.h>
#include <private/smMemLibP.h>
#include <private/semSmLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

#if (defined (CPU_FAMILY) && (CPU_FAMILY==I960) && (defined __GNUC__))
#pragma align 1                 /* tell gcc960 not to optimize alignments */
#endif  /* CPU_FAMILY==I960 */

/* typedefs */

typedef struct sm_obj_tcb        /* SM_OBJ_TCB - shared memory object tcb */
    {
    SM_DL_NODE        qNode;     /* 0x00: multiway q node for pend q */
    struct windTcb *  localTcb;  /* 0x10: address of local TCB */
    UINT32            ownerCpu;  /* 0x14: cpu number on which task runs */
    UINT32            action;    /* 0x18: action when put on CPU event queue */
    UINT32            removedByGive;/* TRUE: if removed from pend Q by give */
    } SM_OBJ_TCB;

#if (defined (CPU_FAMILY) && (CPU_FAMILY==I960) && (defined __GNUC__))
#pragma align 0                 /* turn off alignment requirement */
#endif  /* CPU_FAMILY==I960 */

/* globals */

extern SM_FIX_BLK_PART_ID smTcbPartId;	/* shared TCB partition */

extern FUNCPTR smObjTcbFreeRtn;		/* shared TCB free routine */
extern FUNCPTR smObjTcbFreeFailRtn;	/* shared TCB free fail routine */
extern FUNCPTR smObjTaskDeleteFailRtn;	/* taskDelete fail routine */

/* function declarations */

extern STATUS smObjTcbInit ();
extern STATUS smObjTcbFree (SM_OBJ_TCB * pSmObjTcb);
extern void   smObjTimeoutLogMsg (char * routineName, char * lockLocalAdrs);
extern void   smObjTcbFreeLogMsg ();
extern STATUS smObjEventSend (SM_DL_LIST * pEventList, UINT32 destCpu);
extern void   smObjEventProcess (SM_DL_LIST * pEventList);
extern void   smObjObjShow (int smObjId, int level);

#ifdef __cplusplus
}
#endif

#endif /* __INCsmObjLibPh */
