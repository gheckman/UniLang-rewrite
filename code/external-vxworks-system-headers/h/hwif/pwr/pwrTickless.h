/* pwrTickless.h - cpu power header file */

/*
 * Copyright (c) 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01d,25oct11,jlv  WIND00312777 - Tickless optimizations
01c,07sep11,j_l  WIND00297582 - Move sysCpuPwr.h from IA BSP to here and rename
                                it to pwrTickless.h
01b,22aug11,j_l  WIND00255353: IA PPM integration.
01a,07jul11,j_l  WIND00255353 PwrMgmt: VxWorks Tickless operating mode.
                 Written based on lpd_zoomOmap35x_som_lv/sysCpuPwr.h (01e).
*/

/*
This file contains prototypes and data definitions for CPU
power management.

*/

#ifndef _INC_pwrTickless_H
#define _INC_pwrTickless_H

#include <vxWorks.h>
#include <hwif/util/vxbParamSys.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define PWR_TICKLESS_C0       0    /* C0  state   */
#define PWR_TICKLESS_C1       1    /* C1  state   */
#define PWR_TICKLESS_C2       2    /* C2  state   */
#define PWR_TICKLESS_C3       3    /* C3  state   */
#define PWR_TICKLESS_C4       4    /* C4  state   */
#define PWR_TICKLESS_C5       5    /* C5  state   */
#define PWR_TICKLESS_C6       6    /* C6  state   */
#define PWR_TICKLESS_C7       7    /* C7  state   */
#define PWR_TICKLESS_C8       8    /* C8  state   */
#define PWR_TICKLESS_C9       9    /* C9  state   */
#define PWR_TICKLESS_C10      10   /* C10 state   */
#define PWR_TICKLESS_C11      11   /* C11 state   */
#define PWR_TICKLESS_C12      12   /* C12 state   */
#define PWR_TICKLESS_C13      13   /* C13 state   */
#define PWR_TICKLESS_C14      14   /* C14 state   */
#define PWR_TICKLESS_C15      15   /* C15 state   */
#define PWR_TICKLESS_C16      16   /* C16 state   */
#define PWR_TICKLESS_C17      17   /* C17 state   */
#define PWR_TICKLESS_C18      18   /* C18 state   */
#define PWR_TICKLESS_C19      19   /* C19 state   */
#define PWR_TICKLESS_C20      20   /* C20 state   */
#define PWR_TICKLESS_C21      21   /* C21 state   */
#define PWR_TICKLESS_C22      22   /* C22 state   */
#define PWR_TICKLESS_C23      23   /* C23 state   */
#define PWR_TICKLESS_C24      24   /* C24 state   */
#define PWR_TICKLESS_C25      25   /* C25 state   */
#define PWR_TICKLESS_C26      26   /* C26 state   */
#define PWR_TICKLESS_C27      27   /* C27 state   */
#define PWR_TICKLESS_C28      28   /* C28 state   */
#define PWR_TICKLESS_C29      29   /* C29 state   */
#define PWR_TICKLESS_C30      30   /* C30 state   */
#define PWR_TICKLESS_C31      31   /* C31 state   */
#define PWR_TICKLESS_CMAX     31   /* Max C state */

#define PWR_TICKLESS_C0_BIT   (1 << PWR_TICKLESS_C0  ) /* C0  state bit   */
#define PWR_TICKLESS_C1_BIT   (1 << PWR_TICKLESS_C1  ) /* C1  state bit   */
#define PWR_TICKLESS_C2_BIT   (1 << PWR_TICKLESS_C2  ) /* C2  state bit   */
#define PWR_TICKLESS_C3_BIT   (1 << PWR_TICKLESS_C3  ) /* C3  state bit   */
#define PWR_TICKLESS_C4_BIT   (1 << PWR_TICKLESS_C4  ) /* C4  state bit   */
#define PWR_TICKLESS_C5_BIT   (1 << PWR_TICKLESS_C5  ) /* C5  state bit   */
#define PWR_TICKLESS_C6_BIT   (1 << PWR_TICKLESS_C6  ) /* C6  state bit   */
#define PWR_TICKLESS_C7_BIT   (1 << PWR_TICKLESS_C7  ) /* C7  state bit   */
#define PWR_TICKLESS_C8_BIT   (1 << PWR_TICKLESS_C8  ) /* C8  state bit   */
#define PWR_TICKLESS_C9_BIT   (1 << PWR_TICKLESS_C9  ) /* C9  state bit   */
#define PWR_TICKLESS_C10_BIT  (1 << PWR_TICKLESS_C10 ) /* C10 state bit   */
#define PWR_TICKLESS_C11_BIT  (1 << PWR_TICKLESS_C11 ) /* C11 state bit   */
#define PWR_TICKLESS_C12_BIT  (1 << PWR_TICKLESS_C12 ) /* C12 state bit   */
#define PWR_TICKLESS_C13_BIT  (1 << PWR_TICKLESS_C13 ) /* C13 state bit   */
#define PWR_TICKLESS_C14_BIT  (1 << PWR_TICKLESS_C14 ) /* C14 state bit   */
#define PWR_TICKLESS_C15_BIT  (1 << PWR_TICKLESS_C15 ) /* C15 state bit   */
#define PWR_TICKLESS_C16_BIT  (1 << PWR_TICKLESS_C16 ) /* C16 state bit   */
#define PWR_TICKLESS_C17_BIT  (1 << PWR_TICKLESS_C17 ) /* C17 state bit   */
#define PWR_TICKLESS_C18_BIT  (1 << PWR_TICKLESS_C18 ) /* C18 state bit   */
#define PWR_TICKLESS_C19_BIT  (1 << PWR_TICKLESS_C19 ) /* C19 state bit   */
#define PWR_TICKLESS_C20_BIT  (1 << PWR_TICKLESS_C20 ) /* C20 state bit   */
#define PWR_TICKLESS_C21_BIT  (1 << PWR_TICKLESS_C21 ) /* C21 state bit   */
#define PWR_TICKLESS_C22_BIT  (1 << PWR_TICKLESS_C22 ) /* C22 state bit   */
#define PWR_TICKLESS_C23_BIT  (1 << PWR_TICKLESS_C23 ) /* C23 state bit   */
#define PWR_TICKLESS_C24_BIT  (1 << PWR_TICKLESS_C24 ) /* C24 state bit   */
#define PWR_TICKLESS_C25_BIT  (1 << PWR_TICKLESS_C25 ) /* C25 state bit   */
#define PWR_TICKLESS_C26_BIT  (1 << PWR_TICKLESS_C26 ) /* C26 state bit   */
#define PWR_TICKLESS_C27_BIT  (1 << PWR_TICKLESS_C27 ) /* C27 state bit   */
#define PWR_TICKLESS_C28_BIT  (1 << PWR_TICKLESS_C28 ) /* C28 state bit   */
#define PWR_TICKLESS_C29_BIT  (1 << PWR_TICKLESS_C29 ) /* C29 state bit   */
#define PWR_TICKLESS_C30_BIT  (1 << PWR_TICKLESS_C30 ) /* C30 state bit   */
#define PWR_TICKLESS_C31_BIT  (1 << PWR_TICKLESS_C31 ) /* C31 state bit   */
#define PWR_TICKLESS_CMAX_BIT (1 << PWR_TICKLESS_CMAX) /* Max C state bit */


/*
 * The following typedefs must be defined for all architectures with support
 * for idle power management.
 */

#if    (CPU_FAMILY==ARM)
typedef _Vx_ticks_t   PWR_TICKLESS_CLOCK_TICK_TYPE;
typedef _Vx_ticks64_t PWR_TICKLESS_EVENT_TICK_TYPE;
typedef UINT32        PWR_TICKLESS_ONE_SHOT_TICK_TYPE;
#elif  (CPU_FAMILY==I80X86) && (CPU != PENTIUM)
typedef _Vx_ticks_t   PWR_TICKLESS_CLOCK_TICK_TYPE;
typedef _Vx_ticks64_t PWR_TICKLESS_EVENT_TICK_TYPE;
typedef UINT64        PWR_TICKLESS_ONE_SHOT_TICK_TYPE;
#else
#error "This architecture does not support idle power management."
#endif /* (CPU_FAMILY) */

/* prototypes */

IMPORT  STATUS pwrTicklessInit (void);
IMPORT  void pwrTicklessCStateConfig (UINT32 cpu, UINT32 config);

/*
 * The following functions must be defined for all BSPs with support
 * for idle power management.
 */

IMPORT  VXB_DEVICE_ID pwrTicklessOneShotTimerFind(void);
IMPORT  STATUS pwrTicklessOneShotTimerEnable(VXB_DEVICE_ID pInst,
                                      PWR_TICKLESS_ONE_SHOT_TICK_TYPE val,
                                      void *pIsr,
                                      UINT32 arg);
IMPORT  PWR_TICKLESS_ONE_SHOT_TICK_TYPE pwrTicklessOneShotTimerDisable(VXB_DEVICE_ID pInst);
IMPORT  PWR_TICKLESS_CLOCK_TICK_TYPE pwrTicklessConvertToTicks(PWR_TICKLESS_ONE_SHOT_TICK_TYPE val);
IMPORT  PWR_TICKLESS_ONE_SHOT_TICK_TYPE pwrTicklessConvertFromTicks(PWR_TICKLESS_CLOCK_TICK_TYPE ticks);
IMPORT  void pwrTicklessSystemClockOff(void);
IMPORT  void pwrTicklessSystemClockOn(void);
IMPORT  void pwrTicklessCStateSetRetention(UINT32 cState);
IMPORT  void pwrTicklessCStateSetRefresh(UINT32 cState);
IMPORT  void pwrTicklessCStateSet(UINT32 cState);

#ifdef __cplusplus
}
#endif

#endif  /* _INC_pwrTickless_H */
