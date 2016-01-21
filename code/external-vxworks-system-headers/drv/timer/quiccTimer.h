/* quiccTimer.h */

/* Copyright 1984-2005 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,2mar05,dtr  adapted from m8260Timer.
*/

/*
DESCRIPTION
This file contains header information for PowerPC timer routines.
*/

#ifndef __INCquiccTimerh
#define __INCquiccTimerh

#ifdef __cplusplus
extern "C" {
#endif

/* Real Time Clock Module Registers */

#define  RTCNR  0x00300
#define  RTLDR  0x00304
#define  RTPSR  0x00308
#define  RTCTR  0x0030c
#define  RTEVR  0x00310
#define  RTALR  0x00314

#define  QUICC_RTCNR(base)          (CAST(VUINT32 *)((base) | RTCNR))
#define  QUICC_RTLDR(base)          (CAST(VUINT32 *)((base) | RTLDR))
#define  QUICC_RTPSR(base)          (CAST(VUINT32 *)((base) | RTPSR))
#define  QUICC_RTCTR(base)          (CAST(VUINT32 *)((base) | RTCTR))
#define  QUICC_RTEVR(base)          (CAST(VUINT32 *)((base) | RTEVR))
#define  QUICC_RTALR(base)          (CAST(VUINT32 *)((base) | RTALR))

/* Periodic Interval Timer Registers */

#define  PTCNR  0x00400
#define  PTLDR  0x00404
#define  PTPSR  0x00408
#define  PTCTR  0x0040c
#define  PTEVR  0x00410

#define  QUICC_PTCNR(base)          (CAST(VUINT32 *)((base) | PTCNR))
#define  QUICC_PTLDR(base)          (CAST(VUINT32 *)((base) | PTLDR))
#define  QUICC_PTPSR(base)          (CAST(VUINT32 *)((base) | PTPSR))
#define  QUICC_PTCTR(base)          (CAST(VUINT32 *)((base) | PTCTR))
#define  QUICC_PTEVR(base)          (CAST(VUINT32 *)((base) | PTEVR))

/* Global Timers Module 1 */

/* 
  Example usage:

  *QUICC_GTCFR1(immrVal, GTM1_MODULE_BASE) = 0 ;
  or
  *QUICC_GTCFR1(immrVal, GTM2_MODLUE_BASE) = 0 ;
*/

#define  QUICC_GTCFR1(base,mbase)   (CAST(VUINT8 *)((base) | (mbase) | 0x00000))
#define  QUICC_GTCFR2(base,mbase)   (CAST(VUINT8 *)((base) | (mbase) | 0x00004))
#define  QUICC_GTMDR1(base,mbase)   (CAST(VUINT16 *)((base) | (mbase) | 0x00010))
#define  QUICC_GTMDR2(base,mbase)   (CAST(VUINT16 *)((base) | (mbase) | 0x00012))

/* 16 bit mode */
#define  QUICC_GTRFR1(base,mbase)   (CAST(VUINT16 *)((base) | (mbase) | 0x00014))
#define  QUICC_GTRFR2(base,mbase)   (CAST(VUINT16 *)((base) | (mbase) | 0x00016))
#define  QUICC_GTCPR1(base,mbase)   (CAST(VUINT16 *)((base) | (mbase) | 0x00018))
#define  QUICC_GTCPR2(base,mbase)   (CAST(VUINT16 *)((base) | (mbase) | 0x0001a))
#define  QUICC_GTCNR1(base,mbase)   (CAST(VUINT16 *)((base) | (mbase) | 0x0001c))
#define  QUICC_GTCNR2(base,mbase)   (CAST(VUINT16 *)((base) | (mbase) | 0x0001e))
/* 32 bit cascaded mode */
#define  QUICC_GTRFR1_2(base,mbase)   (CAST(VUINT32 *)((base) | (mbase) | 0x00014))
#define  QUICC_GTCPR1_2(base,mbase)   (CAST(VUINT32 *)((base) | (mbase) | 0x00018))
#define  QUICC_GTCNR1_2(base,mbase)   (CAST(VUINT32 *)((base) | (mbase) | 0x0001c))

#define  QUICC_GTMDR3(base,mbase)   (CAST(VUINT16 *)((base) | (mbase) | 0x00020))
#define  QUICC_GTMDR4(base,mbase)   (CAST(VUINT16 *)((base) | (mbase) | 0x00022))

/* 16 bit mode */
#define  QUICC_GTRFR3(base,mbase)   (CAST(VUINT16 *)((base) | (mbase) | 0x00024))
#define  QUICC_GTRFR4(base,mbase)   (CAST(VUINT16 *)((base) | (mbase) | 0x00026))
#define  QUICC_GTCPR3(base,mbase)   (CAST(VUINT16 *)((base) | (mbase) | 0x00028))
#define  QUICC_GTCPR4(base,mbase)   (CAST(VUINT16 *)((base) | (mbase) | 0x0002a))
#define  QUICC_GTCNR3(base,mbase)   (CAST(VUINT16 *)((base) | (mbase) | 0x0002c))
#define  QUICC_GTCNR4(base,mbase)   (CAST(VUINT16 *)((base) | (mbase) | 0x0002e))
/* 32 bit cascaded mode */
#define  QUICC_GTRFR3_4(base,mbase)   (CAST(VUINT32 *)((base) | (mbase) | 0x00024))
#define  QUICC_GTCPR3_4(base,mbase)   (CAST(VUINT32 *)((base) | (mbase) | 0x00028))
#define  QUICC_GTCNR3_4(base,mbase)   (CAST(VUINT32 *)((base) | (mbase) | 0x0002c))


#define  QUICC_GTEVR1(base,mbase)   (CAST(VUINT16 *)((base) | (mbase) | 0x00030))
#define  QUICC_GTEVR2(base,mbase)   (CAST(VUINT16 *)((base) | (mbase) | 0x00032))
#define  QUICC_GTEVR3(base,mbase)   (CAST(VUINT16 *)((base) | (mbase) | 0x00034))
#define  QUICC_GTEVR4(base,mbase)   (CAST(VUINT16 *)((base) | (mbase) | 0x00036))
#define  QUICC_GTPSR1(base,mbase)   (CAST(VUINT16 *)((base) | (mbase) | 0x00038))
#define  QUICC_GTPSR2(base,mbase)   (CAST(VUINT16 *)((base) | (mbase) | 0x0003a))
#define  QUICC_GTPSR3(base,mbase)   (CAST(VUINT16 *)((base) | (mbase) | 0x0003c))
#define  QUICC_GTPSR4(base,mbase)   (CAST(VUINT16 *)((base) | (mbase) | 0x0003e))

#ifdef __cplusplus
}
#endif

#endif /* __INCquiccTimerh */
