/* vxIpiLib.h - VxWorks IPI management library */

/*
 * Copyright (c) 2007, 2008, 2010-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/* 
modification history
--------------------
01j,26jul12,sye  Removed duplicate method declaration. (WIND00365654)
01i,31jan11,to   WIND00251990: restore backward compatibility for ILP32
01h,27may10,pad  Added 'extern C' statement.
01g,14may10,cww  LP64 adaptation
01f,26jan10,d_c  SMP M-N updates: Change VXIPI_EMIT_FUNC type to pass
                 a physical CPU set (phys_cpuset_t). Add prototype
		 for vxIpiPhysEmit()
01e,23sep08,kab  Fix CQ:133672 - AMP cannot share SMP IPI
                 Added IPI_INTR_ID_MIPC
01d,16feb08,zl   added IPI_INTR_ID_SCHED
01c,01jun07,tor  prevent recursive inclusion
01b,04apr07,tor  change CPC to VXCPC
01a,27Mar07,tor  created
*/

#ifndef __INCvxIpiLibh
#define __INCvxIpiLibh

/* includes */

#include <vxWorks.h>
#include <sllLib.h>
#include <vxBusLib.h>
#include <hwif/vxbus/vxBus.h>

/* defines */

#define IPI_INTR_ID_CPC		0
#define IPI_INTR_ID_DEBUG	1
#define IPI_INTR_ID_SCHED	2
#define IPI_INTR_ID_MIPC	3

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

typedef void   (*IPI_HANDLER_FUNC)	(void * pArg);
typedef STATUS (*VXIPI_EMIT_FUNC)	(VXB_DEVICE_ID pCtlr, INT32 ipiIntrptId,
					 phys_cpuset_t cpus);
typedef STATUS (*VXIPI_CONNECT_FUNC)	(VXB_DEVICE_ID pCtlr, INT32 ipiIntrptId,
					 IPI_HANDLER_FUNC ipiHandler,
					 void * ipiArg);
typedef STATUS (*VXIPI_DISCONN_FUNC)	(VXB_DEVICE_ID pCtlr, INT32 ipiIntrptId,
					 IPI_HANDLER_FUNC ipiHandler,
					 void * ipiArg);
typedef STATUS (*VXIPI_ENABLE_FUNC)	(VXB_DEVICE_ID pCtlr,
					 INT32 ipiIntrptId);
typedef STATUS (*VXIPI_DISABLE_FUNC)	(VXB_DEVICE_ID pCtlr,
					 INT32 ipiIntrptId);
typedef INT32  (*VXIPI_PRIOGET_FUNC)	(VXB_DEVICE_ID pCtlr,
					 INT32 ipiIntrptId);
typedef STATUS (*VXIPI_PRIOSET_FUNC)	(VXB_DEVICE_ID pCtlr, INT32 ipiIntrptId,
					 INT32 prio); 

/* globals */

/* 
 * The vxIpiCntrlInit structure is defined differently in ILP32 and LP64.
 * More specifically, the member pCpus has been moved down in the structure
 * for LP64.  This was done to avoid padding the structure to meet alignment
 * constraints.  However, the ILP32 version must stay the same for backward
 * compatibility, and so the VXIPI_CTRL_INIT_DECL macro was introduced to
 * allow the same code to work in both environments.
 */

typedef struct vxIpiCntrlInit
    {
    SL_NODE                ipiList;	   /* Next IPI structure             */
#ifndef _WRS_CONFIG_LP64
    phys_cpuset_t          pCpus;	   /* destination CPUs interruptable */
					   /* by this struct; source CPU is  */
					   /* implicit			     */
#endif /* _WRS_CONFIG_LP64 */
    VXIPI_EMIT_FUNC        ipiEmitFunc;    /* Trigger an IPI int             */
    VXIPI_CONNECT_FUNC     ipiConnectFunc; /* Install an IPI int handler     */
    VXIPI_ENABLE_FUNC      ipiEnableFunc;  /* Enable int                     */
    VXIPI_DISABLE_FUNC     ipiDisableFunc; /* Disable int                    */
    VXIPI_DISCONN_FUNC     ipiDisconnFunc; /* Disconnect handler             */
    VXIPI_PRIOGET_FUNC     ipiPrioGetFunc; /* Get IPI priority               */
    VXIPI_PRIOSET_FUNC     ipiPrioSetFunc; /* Set IPI priority               */
#ifdef _WRS_CONFIG_LP64
    phys_cpuset_t          pCpus;	   /* destination CPUs interruptable */
					   /* by this struct; source CPU is  */
					   /* implicit			     */
#endif /* _WRS_CONFIG_LP64 */
    INT32                  ipiCount;       /* Number of IPIs available       */
    VXB_DEVICE_ID          pCtlr;	   /* Interrupt Controller           */
    } VXIPI_CTRL_INIT, * VXIPI_CTRL_INIT_PTR;

#ifndef _WRS_CONFIG_LP64

#define VXIPI_CTRL_INIT_DECL(name, \
			     ipiList, pCpus, ipiEmitFunc, ipiConnectFunc, \
			     ipiEnableFunc, ipiDisableFunc, ipiDisconnFunc, \
			     ipiPrioGetFunc, ipiPrioSetFunc, ipiCount, pCtlr) \
	VXIPI_CTRL_INIT	name = \
			{ipiList, pCpus, ipiEmitFunc, ipiConnectFunc, \
			 ipiEnableFunc, ipiDisableFunc, ipiDisconnFunc, \
			 ipiPrioGetFunc, ipiPrioSetFunc, ipiCount, pCtlr}

#else /* _WRS_CONFIG_LP64 */

#define VXIPI_CTRL_INIT_DECL(name, \
			     ipiList, pCpus, ipiEmitFunc, ipiConnectFunc, \
			     ipiEnableFunc, ipiDisableFunc, ipiDisconnFunc, \
			     ipiPrioGetFunc, ipiPrioSetFunc, ipiCount, pCtlr) \
	VXIPI_CTRL_INIT	name = \
			{ipiList, ipiEmitFunc, ipiConnectFunc, ipiEnableFunc, \
			 ipiDisableFunc, ipiDisconnFunc, ipiPrioGetFunc, \
			 ipiPrioSetFunc, pCpus, ipiCount, pCtlr}

#endif /* _WRS_CONFIG_LP64 */

/* function prototypes */

IMPORT STATUS vxIpiLibInit		(void);
IMPORT STATUS vxIpiConnect		(INT32 ipiIntrptId,
					 IPI_HANDLER_FUNC ipiHandler,
					 void * ipiArg );
IMPORT STATUS vxIpiEnable		(INT32 ipiIntrptId);
IMPORT STATUS vxIpiEmit			(INT32 ipiIntrptId, cpuset_t cpus);
IMPORT STATUS vxIpiPhysEmit		(INT32 ipiIntrptId,
					 phys_cpuset_t phys_cpuset);
IMPORT STATUS vxIpiDisable		(INT32 ipiIntrptId);
IMPORT STATUS vxIpiDisconnect		(INT32 ipiIntrptId,
					 IPI_HANDLER_FUNC ipiHandler,
					 void * ipiArg);
IMPORT INT32  vxIpiAvailableAlloc	(void);
IMPORT STATUS vxIpiAvailableFree	(INT32 ipiId);
IMPORT STATUS vxIpiPrioGet		(INT32 ipiIntrptId);
IMPORT STATUS vxIpiPrioSet		(INT32 ipiIntrptId);

#ifdef __cplusplus
}
#endif

#endif /* __INCvxIpiLibh */
