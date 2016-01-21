/* pciXLib.h - PCI-X bus constants header file */

/* 
 * Copyright (c) 2005, 2011 Wind River Systems, Inc.
 * 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */


/*
modification history
--------------------
01b,11nov11,sye  Fix wrong BIT definition. (WIND00266428)
01a,24jun05,mdo  Written.
*/

#ifndef __INCpciXLibh
#define __INCpciXLibh

#ifdef __cplusplus
extern "C" {
#endif
   
#ifndef BIT
#define BIT(bitNumber) (1 << (bitNumber))
#endif
 
/* PCI-X Non-Bridged Configuration Registers */

/* PCI-X Capability Command Register */

#define  PCI_X_CMD               0x02    /* Offset of PCI-X command register */
#define  PCI_X_CMD_DPERR_ENB     BIT(0)  /* Data Parity Error Recovery Enable */
#define  PCI_X_CMD_RO_ENB        BIT(1)  /* Enable Relaxed Ordering */
#define  PCI_X_CMD_MAX_READ      0xc     /* Max Memory Read Byte Count */
#define  PCI_X_CMD_MAX_SPLIT     0x70    /* Max Outstanding Split Trans. */
    #define  PCI_X_MAX_SPLIT_1   0x0     /* 1 Max Outstanding Split Trans. */
    #define  PCI_X_MAX_SPLIT_2   0x1     /* 2 Max Outstanding Split Trans. */
    #define  PCI_X_MAX_SPLIT_3   0x2     /* 3 Max Outstanding Split Trans. */
    #define  PCI_X_MAX_SPLIT_4   0x3     /* 4 Max Outstanding Split Trans. */
    #define  PCI_X_MAX_SPLIT_8   0x4     /* 8 Max Outstanding Split Trans. */
    #define  PCI_X_MAX_SPLIT_12  0x5     /* 12 Max Outstanding Split Trans. */
    #define  PCI_X_MAX_SPLIT_16  0x6     /* 16 Max Outstanding Split Trans. */
    #define  PCI_X_MAX_SPLIT_32  0x7     /* 32 Max Outstanding Split Trans. */


/* PCI-X Capability Status Register */

#define  PCI_X_STATUS              0x04         /* Offset of PCI-X status register */
#define  PCI_X_STATUS_FUNC_NUM     0x7          /* Function Number */
#define  PCI_X_STATUS_DEV_NUM      0xF8         /* Device Number */
#define  PCI_X_STATUS_BUS_NUM      0xFF00       /* Bus Number */
#define  PCI_X_STATUS_64BIT        0x10000      /* 64-bit device */
#define  PCI_X_STATUS_133MHZ       0x20000      /* 133 MHz Capable */
#define  PCI_X_STATUS_SCOMP_DISC   0x40000      /* Split Completion Discarded */
#define  PCI_X_STATUS_UNEX_SCOMP   0x80000      /* Unexpected Split Completion */
#define  PCI_X_STATUS_DEVCPLX      0x100000     /* Device Complexity */
#define  PCI_X_STATUS_MAX_READ     0x600000     /* Designed Max Memory Read Byte Count */
#define  PCI_X_STATUS_MAX_SPLIT    0x3800000    /* Designed Max Outstanding Split Trans. */
#define  PCI_X_STATUS_MAX_CUMRD    0x1c000000   /* Designed Max Cumulative Read Size */
#define  PCI_X_STATUS_SCOMP_ERR    0x20000000   /* Rcv'd Split Completion Error Msg */
#define  PCI_X_STATUS_266MHZ       0x40000000   /* 266 MHz capable */
#define  PCI_X_STATUS_533MHZ       0x80000000   /* 533 MHz capable */


/* PCI-X Bridged Configuration Registers */

/* PCI-X Capability Secondary Status Register */

#define  PCI_X_SECSTAT             0x02          /* Offset of PCI-X 2ndary status register */
#define  PCI_X_SECSTAT_64BIT       0x1           /* 64-bit device */
#define  PCI_X_SECSTAT_133MHZ      0x2           /* 133MHz Capable */
#define  PCI_X_SECSTAT_SCOMP_DISC  0x4           /* Split Completion Discarded */
#define  PCI_X_SECSTAT_UNEX_SCOMP  0x8           /* Unexpected Split Completion */
#define  PCI_X_SECSTAT_SCOMP_ORUN  0x10          /* Split Completion Overrun */
#define  PCI_X_SECSTAT_SCOMP_DLYD  0x20          /* Split Request Delayed */
#define  PCI_X_SECSTAT_CLKFREQ     0x1C0         /* Secondary Clock Freq. */
    
/* PCI-X Capability Primary Status Register */

#define  PCI_X_PRISTAT             0x04                     /* Offset of bridge status register */
#define  PCI_X_PRISTAT_FUNC_NUM    PCI_X_STATUS_FUNC_NUM    /* Function Number */
#define  PCI_X_PRISTAT_DEV_NUM     PCI_X_STATUS_DEV_NUM     /* Device Number */
#define  PCI_X_PRISTAT_BUS_NUM     PCI_X_STATUS_BUS_NUM     /* Bus Number */
#define  PCI_X_PRISTAT_64BIT       PCI_X_STATUS_64BIT       /* 64-bit device */
#define  PCI_X_PRISTAT_133MHZ      PCI_X_STATUS_133MHZ      /* 133 MHz capable */
#define  PCI_X_PRISTAT_SCOMP_DISC  PCI_X_STATUS_SCOMP_DISC  /* Split Completion Discarded */
#define  PCI_X_PRISTAT_UNEX_SCOMP  PCI_X_STATUS_UNEX_SCOMP  /* Unexpected Split Completion */
#define  PCI_X_PRISTAT_SCOMP_ORUN  0x100000                 /* Split Completion Overrun */
#define  PCI_X_PRISTAT_SCOMP_DLYD  0x200000                 /* Split Request Delayed */

/* PCI-X Capability Upstream Split Transaction Control Register */

#define  PCI_X_UP_SXACTION_CTRL    0x08
#define  PCI_X_UP_SXACTION_CAP     0xFF      /* Split Xaction Capacity Register RO */
#define  PCI_X_UP_SXACTION_LIMIT   0xFF00    /* Split Xaction Commit Limit Register */
    

/* PCI-X Capability Downstream Split Transaction Control Register */

#define  PCI_X_DWN_SXACTION_CTRL   0x0C
#define  PCI_X_DWN_SXACTION_CAP    PCI_X_UP_SXACTION_CAP   /* Split Xaction Capacity Reg. RO */
#define  PCI_X_DWN_SXACTION_LIMIT  PCI_X_UP_SXACTION_LIMIT /* Split Xaction Commit Limit Reg. */


#ifdef __cplusplus
}
#endif

#endif /* __INCpciXLibh */

