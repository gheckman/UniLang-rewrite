/* mmuArmLib.h - ARM MMU library header file */

/* 
 * Copyright (c) 1996-2001, 2003-2008, 2010 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
02a,29jul10,pad  Moved extern C statement after include statements.
01z,04jun10,wqi  corrected spelling mistake. (WIND00203804)
01y,11jul07,j_b  add ARMMMU_11MPCORE support
01x,12jun08,j_b  add Cortex-A MMU support
01w,13jul06,m_h  MPU Support
01v,25jan06,m_h  Manzano Support
01u,29mar05,jb   Adding ARMARCH6 and 1136 support
01t,08feb05,rec  use VIRT_ADDR and PHYS_ADDR instead of void
01s,09dec04,jb   Palifying mmu
                 See mmuArmPalLib.h for previous contents
01r,10aug04,scm  adjust for removal of MPU support, add 926E...
01q,18sep03,scm  BASE 6 port...
01p,04oct01,scm  add extended small page table support for XScale...
01o,23jul01,scm  change XScale name to conform to coding standards...
01n,11jul01,scm  add support for XScale...
01m,29mar01,jpd  removed externs for mmyPhysToVirt & mmuVirtToPhys (SPR #63512).
01l,19mar01,jpd  redefine MMU_ATTR_BUFFERABLE and MMU_ATTR_CACHE_MINICACHE
		 (SPR #64788).
01k,16aug00,jpd  no longer clear MMUCR Reserved/Should Be Zero bits (SPR #33608)
01j,14jun00,jpd  reworked MMU_STATE_WRITETHROUGH definition.
01i,17feb00,jpd  T3: prefixed defs with MMU_; added new defs; changed SR to 10.
01h,07sep99,jpd  added ARM740T, ARM920T support.
01g,20jan99,cdp  removed support for old ARM libraries;
		 add prefix to MMU_IDs.
01f,24nov98,jpd  added ARM940T support, added other CPU ids; removed
		 mmuIntLock/Unlock as intIFLock/Unlock to be used instead;
            cdp  restructured for multiple cache/MMU libraries; big-endian.
01e,09mar98,jpd  added MMUCTR_ definitions for ARM810 and extra cache states.
01d,20jan98,jpd  added _func_armPhysToVirt() etc. function pointers.
01c,17sep97,jpd  added MMU_INIT_VALUE and mmuIntLock/Unlock definitions.
01b,24jan97,jpd  modified mmuAEnable definition.
01a,09may96,cdp  created.
*/

#ifndef	__INCmmuArmLibh
#define	__INCmmuArmLibh

#if (ARMMMU != ARMMMU_NONE)

#if     (ARMMMU == ARMMMU_710A)
#include "mmuArm710aLib.h"
#elif   (ARMMMU == ARMMMU_720T)
#include "mmuArm720tLib.h"
#elif   (ARMMMU == ARMMMU_810)
#include "mmuArm810Lib.h"
#elif   (ARMMMU == ARMMMU_SA110)
#include "mmuArmSA110Lib.h"
#elif   (ARMMMU == ARMMMU_SA1100)
#include "mmuArmSA1100Lib.h"
#elif   (ARMMMU == ARMMMU_SA1500)
#include "mmuArmSA1500Lib.h"
#elif   (ARMMMU == ARMMMU_920T)
#include "mmuArm920tLib.h"
#elif   (ARMMMU == ARMMMU_926E)
#include "mmuArm926eLib.h"
#elif   (ARMMMU == ARMMMU_XSCALE)
#include "mmuArmXSCALELib.h"
#elif   (ARMMMU == ARMMMU_MANZANO)
#include "mmuArmManzanoLib.h"
#elif   (ARMMMU == ARMMMU_1020E)
#include "mmuArm1020eLib.h"
#elif   (ARMMMU == ARMMMU_1022E)
#include "mmuArm1022eLib.h"
#elif   (ARMMMU == ARMMMU_1136JF)
#include "mmuArm1136jfLib.h"
#elif   (ARMMMU == ARMMMU_CORTEXA8)
#include "mmuCortexA8Lib.h"
#elif   (ARMMMU == ARMMMU_11MPCORE)
#include "mmuArm11MPCoreLib.h"

#elif   (ARMMMU == ARMMPU_740T)
#include "mpuArm740tLib.h"
#elif   (ARMMMU == ARMMPU_940T)
#include "mpuArm940tLib.h"
#elif   (ARMMMU == ARMMPU_946E)
#include "mpuArm946eLib.h"

#else
#error "Unknown MMU specified"
#endif  /* ARMMMU == ARMMMU_710A */

#endif /* (ARMMMU != ARMMMU_NONE) */

#ifdef __cplusplus
extern "C" {
#endif

/* Any expression using C statements must be defined here */

#ifdef __cplusplus
}
#endif

#endif  /* __INCmmuArmLibh */
