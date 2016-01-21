/* vxbOmap35xDpll.h - OMAP35x vxBus DPLL header file */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,12nov10,rec  DPLL1 unit test changes
01b,15oct10,rec  update PLL control sequence
01a,30Aug10,rec  created
*/

/*
This file contains data definitions and prototypes for the vxBus driver for 
the OMAP 35x DPLL.

See Also OMAP35xx Applications Processor NDA Technical Reference Manual,
Texas Instruments.

*/

#ifndef _INC_VXBOMPAP35XDPLL_H
#define _INC_VXBOMPAP35XDPLL_H

#define REG_SETTING_END 0
#define PLL_REG_VALUE   1
#define PLL_CONDITION   2
#define MAX_PLL_CONDITION_LOOPS 0xfffff

#define REG_SETTING_END_MARKER 0, 0, 0, REG_SETTING_END



typedef void (*DPLL_SET_FUNC)
    (
    UINT32 *regAddress,
    UINT32 regValue,
    BOOL unlock, 
    UINT32 waitCycles, 
    BOOL freqIncrease
    );

/* data definitions */

/*
 * Each record is a sequence of pll control register values to modify.
 * Processing will start with the first record in the sequence and continue
 * until REG_SETTING_END_MARKER is read.  It will modify the register
 * contents for each register commanded.
 *
 * Each sequence defines the pll register values for one operating point.
 *
 * Entries of type CONDITION are used to test a register value and will
 * spin until the condition is statisfied.  Condition loops are limited to
 * no more than MAX_PLL_CONDITION_LOOPS as defined above.
 */

typedef struct pll_reg
    {
    UINT32  *address;   /* register address */
    UINT32  mask;       /* register mask */
    UINT32  value;      /* register value */
    UINT32  entryType;  /* REG_SETTING_END, PLL_REG_VALUE, or PLL_CONDITION */
    } PLLREG;
    
typedef struct pll_control /* device context passed from hwconf to driver */
    {
    VXB_DEVICE_ID	pDev;       /* filled in during driver init */
    int                 numOpp;     /* number of supported OPPs 1..7 */
    UINT32              refRate;    /* clock reference rate (khz) */
    UINT32              *oppFreq;   /* array of frequencies for each OPP (khz)*/
    DPLL_SET_FUNC       setFunc;    /* if non-zero, use this to set DPLL */
    PLLREG		**ppPllreg; /* sequence of register values */
    } PLL_CONTROL;

/* global data */

/* public API */

IMPORT void vxbOmap35xDpllDrvRegister (void);

IMPORT STATUS vxbOmap35xDpllSet
    (
    VXB_DEVICE_ID	pDev,
    int                 opp         /* range 1..n where n is the highest opp */
    );
    
IMPORT int vxbOmap35xDpllGet
    (
    VXB_DEVICE_ID	pDev
    );

#endif  /* _INC_VXBOMPAP35XDPLL_H */
