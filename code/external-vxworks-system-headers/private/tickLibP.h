/* tickLibP.h - VxWorks tickLib library private header file */

/*
 * Copyright (c) 2007-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01g,19jan11,gls  added tick specific queue macros (WIND00200778)
01f,13jul10,pcs  Update the data ypte of the return value of fn. vxAbsTicksGet
                 from UINT64 to _Vx_ticks64_t.
01e,29apr10,pad  Moved extern C statement after include statements.
01d,10feb09,gls  added vxAbsTicksGet() for UP
01c,27aug08,jpb  Renamed VSB header file
01b,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
01a,25apr07,mmi	written
*/

#ifndef __INCtickLibPh
#define __INCtickLibPh

	
#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/* definitions */

/* the tick queue is a delta queue */

#define TICKQ_NEXT(pQHead,pQNode)        qPriDeltaNext(pQHead,pQNode)
#define TICKQ_PUT(pQHead,pQNode,key)     qPriDeltaPut(pQHead,pQNode,key)
#define TICKQ_GET(pQHead)                qPriDeltaGet(pQHead)
#define TICKQ_REMOVE(pQHead,pQNode)      qPriDeltaRemove(pQHead,pQNode)
#define TICKQ_ADVANCEN(pQHead, n)        qPriDeltaAdvance(pQHead, n)
#define TICKQ_GET_EXPIRED(pQHead)        qPriDeltaGetExpired(pQHead)
#define TICKQ_KEY(pQHead,pQNode,keyType) qPriDeltaKey((Q_NODE *)(pQNode))

#define TICKQ_RESORT(pQHead,pQNode,newKey)    \
                                       qPriDeltaResort(pQHead,pQNode,newKey)
#define TICKQ_INFO(pQHead,nodeArray,maxNodes) \
                                       qPriDeltaInfo(pQHead,nodeArray,maxNodes)
#define TICKQ_EACH(pQHead,routine,routineArg) \
                                       qPriDeltaEach(pQHead,routine,routineArg)

#ifdef _WRS_CONFIG_SMP

/* vxWorks ticks validation  */

typedef struct vxAbsTicksCheck {
    UINT32	start;
    UINT32	stop; 
    } VX_ABS_TICKS_CHECK;

/* Ticks preamble */

extern volatile VX_ABS_TICKS_CHECK	vxAbsTicksCheck;

/* funtion declarations */

extern _Vx_ticks64_t vxAbsTicksGet (void);

#else  /* _WRS_CONFIG_SMP */

#define vxAbsTicksGet() vxAbsTicks

#endif /* _WRS_CONFIG_SMP */

/* variable declarations */

extern volatile _Vx_ticks64_t vxAbsTicks;	/* absolute time counter */

#ifdef __cplusplus
}
#endif

#endif /* __INCtickLibPh */
