/* omap35xxSmartReflex.h - OMAP35x Smart Reflex header file */

/*
 * Copyright (c) 2010, 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
 

/*
modification history
--------------------
01k,24mar11,rdl  WIND00262928: BSP specific macro definitions in driver headers
01j,07feb11,rec  fix DPLL3_MNM2MSK value
01i,11jan11,rdl  add definitions for some masks, fix offset bug
01h,06dec10,rdl  fix some macro problems with SR
01g,22nov10,rdl  add voltage processor offsets
01f,12nov10,rec  DPLL1 unit test changes
01e,10nov10,rec  test fixes - correct DPLL3_MNM2MSK constant
01d,09nov10,rdl  add SR registers
01c,19oct10,rec  fix compiler warning
01b,26oct10,rdl  add macros for efuse values needed by SmartReflex
01a,30Aug10,rec  created
*/

/*
 * This file contains memory, I/O address and related Smart Reflex and DPLL
 * constants for the OMAP35x chip.
 *
 * See Also OMAP35xx Applications Processor NDA Technical Reference Manual,
 * Texas Instruments.
 *
 */

#ifndef _INC_OMAP35XXSMARTREFLEX_H
#define _INC_OMAP35XXSMARTREFLEX_H

/* SmartReflex constants for the OMAP35xx */

#define SR_CLK          100 /* khz */
#define ACCUMDATA_WINDOW  5 /* ms Smart Reflex window period */
#define ERRWEIGHT       0x07
#define ERRMINLIMIT     0xF9

/* DPLL Jitter Correction values in khz (TRM table 4-39) */

#define DPLL_JITTER_00750   0x3
#define DPLL_JITTER_01000   0x4
#define DPLL_JITTER_01250   0x5
#define DPLL_JITTER_01500   0x6
#define DPLL_JITTER_01750   0x7
#define DPLL_JITTER_07500   0xb
#define DPLL_JITTER_10000   0xc
#define DPLL_JITTER_12500   0xc
#define DPLL_JITTER_15000   0xe
#define DPLL_JITTER_17500   0xf

/* 
 * definitions for setting up the DPLL register tables in hwconf
 * (see TRM 4.7.6.1) 
 *
 * Register fields are scattered among various registers in the register set. 
 * Most vxBus devices would use a base address that defines a standard set
 * of device registers.  Accesses to the register set would be relative to 
 * that base.  TI didn't lay the hardware out that way however.  Accesses
 * performed to setup the hardware is done using a table.  Entries within the
 * table provide register address, field mask, and value required to setup
 * each voltage setpoint.  More than one table entry is required for each
 * setpoint.  
 *
 * There are three types of register records, a register setting record used
 * to modify the value of a register, a register condition record used
 * to test a register field and spin until the hardware responds, and an
 * end of record marker.
 *
 * The list of entries associated with each setpoint is terminated
 * with an REG_SETTING_END_MARKER record.  The macros below are used to 
 * construct table entries.
 */
 
#define REG_SETTING_END_MARKER 0, 0, 0, REG_SETTING_END

#define DPLL1_MNVAL(m,n)    ((m << 8) | n )
#define DPLL1_MNMSK         0x7ff7f
#define DPLL1_M2VAL(m2)     (m2)
#define DPLL1_M2MSK         0x1f
#define DPLL1_FRESELMSK     0xf0
#define DPLL1_JITTER(j)     (j << 4)
#define DPLL1_RAMPMSK       0x300
#define DPLL1_RAMP(r)       (r << 8)
#define DPLL1_ENABLE        7
#define DPLL1_BYPASS        5
#define DPLL1_BYPASSED      0
#define DPLL1_LOCKED        1

/* register configuration settings for DPPL1 {address, mask, value, jitter} */

#define DPLL1REGCFG(m,n,m2,j) \
 {(UINT32 *)OMAP35XX_CM_CLKSEL1_PLL_MPU, DPLL1_MNMSK, DPLL1_MNVAL(m,n), \
    PLL_REG_VALUE}, \
 {(UINT32 *)OMAP35XX_CM_CLKSEL2_PLL_MPU, DPLL1_M2MSK, DPLL1_M2VAL(m2), \
    PLL_REG_VALUE},  \
 {(UINT32 *)OMAP35XX_CM_CLKEN_PLL_MPU, DPLL1_FRESELMSK | DPLL1_ENABLE, \
    DPLL1_JITTER(j) | DPLL1_BYPASS, PLL_REG_VALUE},\
 {(UINT32 *)OMAP35XX_CM_IDLEST_PLL_MPU, DPLL1_LOCKED, DPLL1_BYPASSED, \
    PLL_CONDITION}, \
 {(UINT32 *)OMAP35XX_CM_CLKEN_PLL_MPU, DPLL1_RAMPMSK | DPLL1_ENABLE, \
    DPLL1_RAMP(2) | DPLL1_ENABLE, PLL_REG_VALUE}, \
 {(UINT32 *)OMAP35XX_CM_IDLEST_PLL_MPU, DPLL1_LOCKED, DPLL1_LOCKED, \
    PLL_CONDITION},\
 {REG_SETTING_END_MARKER}

#define DPLL3_MNM2VAL(m,n,m2) ((m << 16) | (n << 8) | (m2 << 27))
#define DPLL3_MNM2MSK 0x000080ff
#define DPLL3_FRESELMSK     0xf0
#define DPLL3_JITTER(j)     (j << 4)
#define DPLL3_RAMPMSK       0x300
#define DPLL3_RAMP(r)       (r << 8)
#define DPLL3_M2VAL(m2) (m2 << 27)  /* only M2 changed for this dpll */
#define DPLL3_M2MSK 0x07ffffff

/* 
 * Register configuration settings for DPPL3
 *
 * Two macros are defined.  Once changes only M2 while the other changes 
 * the multipliers and dividers also.
 * 
 */

#define DPLL3REGCFG(m,n,m2,j) \
    {(UINT32 *)OMAP35XX_CM_CLKSEL1_PLL, DPLL3_MNM2MSK, DPLL3_MNM2VAL(m,n,m2), \
    PLL_REG_VALUE}, \
    {REG_SETTING_END_MARKER}

#define DPLL3M2REGCFG(m2) \
    {(UINT32 *)OMAP35XX_CM_CLKSEL1_PLL, DPLL3_M2MSK, DPLL3_M2VAL(m2), \
    PLL_REG_VALUE}, \
    {REG_SETTING_END_MARKER}

#define NUMBER_POWER_DOMAINS 2
#define MPU_DOMAIN 0
#define CORE_DOMAIN 1
#define VDD_DEVICE 0
#define DPLL_DEVICE 1

/* constants for computing clock switch latency */

#define DPLL_LATENCY(refFreq, rate) \
	(((((refFreq / 1000000 << 8) >> 9) + 1) * 9) >> 8) >0 ? \
        ((((refFreq / 1000000 << 8) >> 9) + 1) * 9) >> 8 : 1

/* number of Smart Reflex units */

#define SR_UNITS  2

/* offsets between SR1 and SR2 */

#define SR1_OFFSET  0x0000
#define SR2_OFFSET  0x2000

/* Smart reflex address offsets (from OMAP35xTRM 4.14.3 P660) */

#define SRCONFIG			0x00
#define SRSTATUS			0x04
#define SENVAL				0x08
#define SENMIN				0x0C
#define SENMAX				0x10
#define SENAVG				0x14
#define AVGWEIGHT			0x18
#define NVALUERECIPROCAL                0x1C
#define SENERROR			0x20
#define ERRCONFIG			0x24

/* SRCONFIG register definitions */

/* TRM equation-2 (TRM 4.10.5.4.3) */

#define SRCONFIG_ACCUMDATA_MSK		(0xFFC << 22)
#define SRCONFIG_ACCUMDATA_POS          22
#define SRCONFIG_ACCUMDATA_VAL          (ACCUMDATA_WINDOW * SR_CLK)
#define SRCONFIG_ACCUMDATA              (SRCONFIG_ACCUMDATA_VAL << \
					 SRCONFIG_ACCUMDATA_POS)
#define SRCONFIG_ACCUMDATA_R(val)       ((val >> \
					  SRCONFIG_ACCUMDATA_POS) & 0x3FF)

/* TRM equation-1 (TRM 4.10.5.4.3) */

#define SRCONFIG_SRCLKLENGTH_MSK       (0x3FF << 12)
#define SRCONFIG_SRCLKLENGTH_POS       12
#define SR_ALWON_FCLK   (sysPrmClk/1000)
#define SRCONFIG_SRCLKLENGTH_VAL       (SR_ALWON_FCLK/(2 * SR_CLK))

/* 
 * Clock setting (TRM 4.12.6.4, cookbook 14.2.2.1 i)
 * Setting the clock consists of configuring the internal clock frequency 
 * of the SmartReflex module and the state of the functional clock when 
 * the module switches to inactive state, and then enabling the
 * functional clock from the PRCM module of the device.  The internal clock
 * frequency configuration depends on the frequency of SR_ALWON_FCLK and 
 * can be calculated from Equation 2. 
 *
 * For example, if SR_ALWON_FCLK has a frequency of 38.4 MHz, and
 * the target SR_CLK frequency is 100 kHz, SRCLKLENGTH is set to 192 (0x0C0)
 * SRn.SRCONFIG[21:12] SRCLKLENGTH Calculated from Equation 1
 */

#define SRCONFIG_SRCLKLENGTH          ((sysClkFreqGet()/1000)/(2 * SR_CLK) \
                                          << SRCONFIG_SRCLKLENGTH_POS)
#define SRCONFIG_SRCLKLENGTH_R(val)    ((val >> \
                                        SRCONFIG_SRCLKLENGTH_POS) & 0x3FF)

#define SRENABLE_POS		       11 /* 1 = enable */
#define SRENABLE                       (1 << SRENABLE_POS)

#define SENENABLE_POS		       10 /* 1 = enable */
#define SENENABLE                      (1 << SENENABLE_POS)

#define ERRORGENERATORENABLE_POS       9  /* 1 = Enable error generator */
#define ERRORGENERATORENABLE           (1 << ERRORGENERATORENABLE_POS)

#define MINMAXAVGENABLE_POS	       8  /* 1 = Enable minmax avg detector*/
#define MINMAXAVGENABLE                (1 << MINMAXAVGENABLE_POS)

#define SENNENABLE_POS		       5  /* Selects different SenN modes */
#define SENNENABLE_MSK		       (0x3 << SENNENABLE_POS)
#define SENNENABLE(val)                ((val & 0x3) << SENNENABLE_POS)
#define SENNENABLE_R(val)              ((val >> SENNENABLE_POS) & 0x3)
#define SENNENABLE_DIS_VAL	       0  /* Disables all SenN sensors */
#define SENNENABLE_NM3EN_VAL	       1  /* SenN-M3 enabled */
#define SENNENABLE_NM4EN_VAL	       2  /* SenN-M4 enabled */
#define SENNENABLE_NM5EN_VAL	       3  /* SenN-M5 enabled */

#define SENPENABLE_POS		       3  /* Selects different SenN modes */
#define SENPENABLE_MSK                 (0x3 << SENPENABLE_POS)
#define SENPENABLE(val)                ((val & 0x3) << SENPENABLE_POS)
#define SENPENABLE_R(val)              ((val >> SENPENABLE_POS) & 0x3)
#define SENPENABLE_DIS_VAL	       0  /* Disables all SenN sensors */
#define SENPENABLE_NM3EN_VAL	       1  /* SenN-M3 enabled */
#define SENPENABLE_NM4EN_VAL	       2  /* SenN-M4 enabled */
#define SENPENABLE_NM5EN_VAL	       3  /* SenN-M5 enabled */

#define SRDELAYCTRL_POS		       2  /*characterization mode (set 1)*/
#define SRDELAYCTRL                    (1 << SRDELAYCTRL_POS)

#define SRCLKCTRL_POS		       0 /* CLKCTRL Div down SenN and SenP */
#define SRCLKCTRL(val)	               (val << SRCLKCTRL_POS) 
#define SRCLKCTRL_R(val)	       ((val >> SRCLKCTRL_POS) & 0x3)
#define SRCLKCTRL_VAL4		       0  /* Divide by 4 */
#define SRCLKCTRL_VAL8		       1  /* Divide by 8 */
#define SRCLKCTRL_VAL16		       2  /* Divide by 16 */
#define SRCLKCTRL_VAL32		       3  /* Divide by 32 */

/* SRSTATUS register definitions */

#define AVGERRVALID_POS		       3  /* 1 = SenAvg register valid */
#define AVGERRVALID(regVal)	       ((regVal & \
					 (1 << AVGERRVALID_POS)) != 0)
#define MINMAXAVGVALID_POS	       2  /* 1 = SenVal,Min,Max,Avg valid */
#define MINMAXAVGVALID(regVal)	       ((regVal & \
					 (1 << MINMAXAVGVALID_POS)) != 0)
#define ERRORGENERATORVALID_POS	       1  /* 1 = SenErr register valid */
#define ERRORGENERATORVALID(regVal)    ((regVal & \
					 (1 << ERRORGENERATORVALID_POS)) \
					!= 0)
#define MINMAXAVGACCUMFINAL_POS	       0  /* 1= SenVal,Min,Max,Avg valid */
#define MINMAXAVGACCUMFINAL(regVal)    ((regVal & \
					 (1 << MINMAXAVGACCUMFINAL_POS)) \
					!= 0)

/* SENVAL register definitions */

#define SENPVAL(regVal)	               ((regVal >> 16) & 0xffff)
#define SENNVAL(regVal)                (regVal & 0xffff)

/* SENMIN register definitions */

#define SENPMIN(regVal)	               ((regVal >> 16) & 0xffff)
#define SENNMIN(regVal)	               (regVal & 0xffff)

/* SENMAX register definitions */

#define SENPMAX(regVal)	               ((regVal >> 16) & 0xffff)
#define SENNMAX(regVal)	               (regVal & 0xffff)

/* SENAVG register definitions */

#define SENPAVG(regVal)	               ((regVal >> 16) & 0xffff)
#define SENNAVG(regVal)	               (regVal & 0xffff)

/* AVGWEIGHT register definitions */

#define SENPAVGWEIGHT(regVal)	       ((regVal >> 2) & 0x3)
#define SENNAVGWEIGHT(regVal)	       (regVal & 0x3)

/* NVALUERECIPROCAL register definitions (used for reading values) */

#define SENPGAIN(regVal)	       ((regVal >> 20) & 0xf)
#define SENNGAIN(regVal)	       ((regVal >> 16) & 0x3)
#define RNSENP(regVal)	               ((regVal >> 8) & 0xff)
#define RNSENN(regVal)	               (regVal & 0xff)

/* SENERROR register definitions (used for reading values) */

#define SRFUSEVALUE(regVal)            ((regVal >> 16) & 0xff)
#define SRAVGERROR(regVal)             ((regVal >> 8) & 0xff)
#define SRSENERROR(regVal)             (regVal & 0xff)

/* ERRCONFIG - error configuration register */

#define VPBOUNDINTEN_POS       31	/* 1 = VP bounded interrupt enable */
#define VPBOUNDINTEN           (1 << VPBOUNDINTEN_POS)

#define VPBOUNDINTST_POS       30	/* 1 = Interrupt is pending */
#define VPBOUNDINTST_R	       (1 << VPBOUNDINTST_POS)
#define VPBOUNDINTST(regVal)   ((regVal & (1 << VPBOUNDINTST_POS)) != 0)
#define VPBOUNDINCTLR(regAdr)  (*regAdr |= (1 << VPBOUNDINTST_POS)

#define MCUACCUMINTEN_POS      29	/* 1 = MCU Accum interrupt enable */
#define MCUACCUMINTEN          (1 << MCUACCUMINTEN_POS)
#define MCUACCUMINTST_POS      28	/* 1 = Interrupt is pending */
#define MCUACCUMINTST(regVal)  ((regVal & (1 << MCUACCUMINTST_POS)) != 0)
#define MCUACCUMINCTLR(regAdr) (*regAdr |= (1 << MCUACCUMINTST_POS)

#define MCUVALIDINTEN_POS      27	/* 1 = Enable MCU Valid Interrupt */
#define MCUVALIDINTEN          (1 << MCUVALIDINTEN_POS)

#define MCUVALIDINTST_POS      26	/* 1 = Interrupt is pending */
#define MCUVALIDINTST(regVal)  ((regVal & (1 << MCUVALIDINTST_POS)) != 0)
#define MCUVALIDINTCLR(regAdr) (*regAdr |= (1 << MCUVALIDINTST_POS)

#define MCUBOUNDINTEN_POS      25	/* 1 = Enable MCU bound interrupt */
#define MCUBOUNDINTEN          (1 << MCUBOUNDINTEN_POS)

#define MCUBOUNDINTST_POS      24	/* 1 = Interrupt is pending */
#define MCUBOUNDINTST(regVal)  ((regVal & (1 << MCUBOUNDINTST_POS)) != 0)
#define MCUBOUNDINCTLR(regAdr) (*regAdr |= (1 << MCUBOUNDINTST_POS)

#define MCUDISACKINTEN_POS     23	/* 1 = Enable MCU Disable Ack Int */
#define MCUDISACKINTEN         (1 << MCUDISACKINTEN_POS)

#define MCUDISACKINTST_POS     22	/* 1 = Interrupt is pending */
#define MCUDISACKINTST_R       (1 << MCUDISACKINTST_POS)
#define MCUDISACKINTST(regVal) ((regVal & (1 << MCUDISACKINTST_POS)) != 0)

#define SRCLOCKACTIVITY_POS    20 /* Clock activity selection bits [21,20] */
#define SRCLOCKACTIVITY_VAL(regVal) ((regVal >> SRCLOCKACTIVITY_POS) & 3)
#define SRCLOCKACTIVITY_GATED   0x0  /* clocks can be gated */
#define SRCLOCKACTIVITY_ACTIVE1 0x1  /* clock must be kept active and the */
                                     /* interface clock can be cut off */
#define SRCLOCKACTIVITY_ACTIVE2 0x2  /* clock must be kept active and the */
                                     /* interface clock can be cut off */
#define SRCLOCKACTIVITY_ACTIVE3 0x3  /* clock must be kept active and the */
                                     /* interface clock can be cut off */
#define SRCLOCKACTIVITY SRCLOCKACTIVITY_VAL(SRCLOCKACTIVITY_GATED) /* def */
 
#define ERRWEIGHT_POS           16   /* avg sensor error weight [18..16]*/
#define ERRWEIGHT_VAL(regVal)   ((regVal & 0x7) << ERRWEIGHT_POS)
#define ERRWEIGHT_VAL_R(regVal) ((regVal >> ERRWEIGHT_POS) & 0x7)
#define ERRWEIGHT_MASK		(0x7 << ERRWEIGHT_POS)

#define ERRMAXLIMIT_POS         8    /* High limit of sensor erro [15..8] */
#define ERRMAXLIMIT_VAL(regVal) ((regVal & 0xff) << ERRMAXLIMIT_POS)
#define ERRMAXLIMIT_VAL_R(regVal) ((regVal >> ERRMAXLIMIT_POS) & 0xff)
#define ERRMAXLIMIT_MASK	(0xFF << ERRMAXLIMIT_POS)

#define ERRMINLIMIT_POS         0    /* Low limit of sensor error [7..0] */
#define ERRMINLIMIT_VAL(regVal) ((regVal & 0xff) << ERRMINLIMIT_POS)
#define ERRMINLIMIT_VAL_R(regVal) ((regVal >> ERRMINLIMIT_POS) & 0xff)
#define ERRMINLIMIT_MASK	(0xFF << ERRMINLIMIT_POS)


/* number of Voltage Processor units */

#define VP_UNITS  2

/* offsets of SR1 and SR2 */

#define     VP1_OFFSET   0xB0
#define     VP2_OFFSET   0xD0

/* voltage processor register offsets (rel. to OMAP35XX_PRM_VPn_CONFIG) */

#define PRM_VP_CONFIG     0x00
#define PRM_VP_VSTEPMIN   0x04
#define PRM_VP_VSTEPMAX   0x08
#define PRM_VP_VLIMITTO   0x0C
#define PRM_VP_VOLTAGE    0x10
#define PRM_VP_STATUS     0x14

/* VP_CONFIG fields TRM table 4-480 */

#define VPENABLE                1
#define VPENABLE_MSK            1
#define VPFORCEUPDATE           2
#define VPFORCEUPDATE_MSK       2
#define VPINITVDD               4
#define VPINITVDD_MSK           4
#define VPTIMEOUT               8
#define VPTIMEOUT_MSK           8
#define VPINITVOLTAGE(v)        (v << 8)           
#define VPINITVOLTAGE_MSK       0x0000ff00           
#define VPERRORGAIN(g)          (g << 16)
#define VPERRORGAIN_MSK         0x00ff0000
#define VPERROFFSET(o)          (o << 24)
#define VPERROFFSET_MSK         0xff000000

/* VP_VSTEPMIN TRM table 4-482 */

#define VPVSTEPMIN(v)           (v)
#define VPVSTEPMIN_MSK          0x0000ff
#define VPSMPSWAITTIMEMIN(v)    (v << 8)
#define VPSMPSWAITTIMEMIN_MSK   0xffff00

/* VP_VSTEPMAX TRM table 4-484 */

#define VPVSTEPMAX(v)           (v)
#define VPVSTEPMAX_MSK          0x0000ff
#define VPSMPSWAITTIMEMAX(v)    (v << 8)
#define VPSMPSWAITTIMEMAX_MSK   0xffff00

/* VP_VLIMITTO TRM table 4-486 */

#define VPVLIMITTO(v)           (v)
#define VPVLIMITTO_MSK          0x0000ffff
#define VPVVDDMIN(v)            (v << 16)
#define VPVVDDMIN_MSK           0x00ff0000
#define VPVVDDMAX(v)            (v << 24)
#define VPVVDDMAX_MSK           0xff000000

/* VP_VOLTAG TRM table 4-488 */

#define VPVOLTAGE (v)           (v)
#define VPVOLTAGE_MSK           0xff

/* VP_STATUS TRM table 4-490 */

#define VPSTATUS_MSK            0x1

/*
 * These are register definitions for the EFuses needed in SmartReflex
 * calculations.
 */

#define OMAP35XX_SCM_GENERAL (OMAP35XX_L4_SYSCTRL + 0x270)

#define OMAP35XX_OPP1_VDD1 (OMAP35XX_SCM_GENERAL + 0x110)
#define OMAP35XX_OPP2_VDD1 (OMAP35XX_SCM_GENERAL + 0x114)
#define OMAP35XX_OPP3_VDD1 (OMAP35XX_SCM_GENERAL + 0x118)
#define OMAP35XX_OPP4_VDD1 (OMAP35XX_SCM_GENERAL + 0x11C)
#define OMAP35XX_OPP5_VDD1 (OMAP35XX_SCM_GENERAL + 0x120)

#define OMAP35XX_OPP1_VDD2 (OMAP35XX_SCM_GENERAL + 0x124)
#define OMAP35XX_OPP2_VDD2 (OMAP35XX_SCM_GENERAL + 0x128)
#define OMAP35XX_OPP3_VDD2 (OMAP35XX_SCM_GENERAL + 0x12C)

#define OMAP35XX_FUSE_SR (OMAP35XX_SCM_GENERAL + 0x130)

#define OMAP35XX_PRCM_SR_REGS 0x480C9000

#endif  /* _INC_OMAP35XXSMARTREFLEX_H */
