/* fsl_Kinetis.h - SOC specific header file */

/*
 * Copyright (c) 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01a,02aug13,yjw  Created
*/

/*
DESCRIPTION
This file contains register definitions specifc to the Kinetis series SOC.

SEE ALSO:
\tb "Freescale K70 Sub-Family Reference Manual"

*/

#ifndef __INCfsl_Kinetish
#define __INCfsl_Kinetish

#ifdef __cplusplus
extern "C" {
#endif

/* Peripheral memory map */

#define KINETIS_AIPS0PERIPH_BASE	0x40000000
#define KINETIS_AIPS1PERIPH_BASE	0x40080000

/* UART registers bases */

#define KINETIS_UART0_BASE	(KINETIS_AIPS0PERIPH_BASE + 0x0006A000)
#define KINETIS_UART1_BASE	(KINETIS_AIPS0PERIPH_BASE + 0x0006B000)
#define KINETIS_UART2_BASE	(KINETIS_AIPS0PERIPH_BASE + 0x0006C000)
#define KINETIS_UART3_BASE	(KINETIS_AIPS0PERIPH_BASE + 0x0006D000)
#define KINETIS_UART4_BASE	(KINETIS_AIPS1PERIPH_BASE + 0x0006A000)
#define KINETIS_UART5_BASE	(KINETIS_AIPS1PERIPH_BASE + 0x0006B000)

/* ENET register base */

#define KINETIS_ENET_BASE   (KINETIS_AIPS1PERIPH_BASE + 0x00040000)

/* PIT register base */

#define KINETIS_PIT_BASE    (KINETIS_AIPS0PERIPH_BASE + 0x00037000)

/* Clock gates for the modules inside the MCU */

/* UARTs */

#define SIM_SCGC1_UART4_MASK   0x00000400
#define SIM_SCGC1_UART5_MASK   0x00000800
#define SIM_SCGC1_UART0_MASK   0x00000400
#define SIM_SCGC4_UART1_MASK   0x00000800
#define SIM_SCGC4_UART2_MASK   0x00001000
#define SIM_SCGC4_UART3_MASK   0x00002000

/* Ports */

#define SIM_SCGC5_PORTA_MASK   0x00000200
#define SIM_SCGC5_PORTB_MASK   0x00000400
#define SIM_SCGC5_PORTC_MASK   0x00000800
#define SIM_SCGC5_PORTD_MASK   0x00001000
#define SIM_SCGC5_PORTE_MASK   0x00002000

/* ENET */

#define SIM_SCGC2_ENET_MASK    0x00000001

/* PIT  */

#define SIM_SCGC6_PIT_MASK     0x00800000

/* DDR */

#define SIM_SCGC3_DDR_MASK     0x00004000

/* OSC1 */

#define SIM_SCGC1_OSC1_MASK    0x00000020

/* MPU  */

#define SIM_SCGC7_MPU_MASK     0x00000004

/* I2C */    

#define SIM_SCGC4_IIC0_MASK    (1 << 6)

/* System Integration Module (SIM) register map */

struct kinetis_sim_regs {
	UINT32 sopt1;	/* System Options Register 1 */
	UINT32 rsv0[1024];
	UINT32 sopt2;	/* System Options Register 2 */
	UINT32 rsv1;
	UINT32 sopt4;	/* System Options Register 4 */
	UINT32 sopt5;	/* System Options Register 5 */
	UINT32 sopt6;	/* System Options Register 6 */
	UINT32 sopt7;	/* System Options Register 7 */
	UINT32 rsv2[2];
	UINT32 sdid;	/* System Device Identification Register */
	UINT32 scgc[7];	/* Clock Gating Regs 1...7 */
	UINT32 clkdiv1;	/* System Clock Divider Register 1 */
	UINT32 clkdiv2;	/* System Clock Divider Register 2 */
	UINT32 fcfg1;	/* Flash Configuration Register 1 */
	UINT32 fcfg2;	/* Flash Configuration Register 2 */
	UINT32 uidh;	/* Unique Identification Register High */
	UINT32 uidmh;	/* Unique Identification Register Mid-High */
	UINT32 uidml;	/* Unique Identification Register Mid Low */
	UINT32 uidl;	/* Unique Identification Register Low */
	UINT32 clkdiv3;	/* System Clock Divider Register 3 */
	UINT32 clkdiv4;	/* System Clock Divider Register 4 */
	UINT32 mcr;	/* Misc Control Register */
};

/* SIM registers base */

#define KINETIS_SIM_BASE		(KINETIS_AIPS0PERIPH_BASE + 0x00047000)
#define KINETIS_SIM			((volatile struct kinetis_sim_regs *) \
					KINETIS_SIM_BASE)
					
/* System Clock Divider Register 1 */

/* Clock 1 output divider value */

#define KINETIS_SIM_CLKDIV1_OUTDIV1_BITS	28

/* Clock 2 output divider value */

#define KINETIS_SIM_CLKDIV1_OUTDIV2_BITS	24

/* Clock 3 output divider value */

#define KINETIS_SIM_CLKDIV1_OUTDIV3_BITS	20

/* Clock 4 output divider value */

#define KINETIS_SIM_CLKDIV1_OUTDIV4_BITS	16

/* Misc Control Register (SIM_MCR) */

/* Pin enable for all DDR I/O */

#define KINETIS_SIM_MCR_DDRPEN_MSK	(1 << 2)

/* DDR configuration select */

#define KINETIS_SIM_MCR_DDRCFG_BITS	5

/* DDR2 Full Strength */

#define KINETIS_SIM_MCR_DDRCFG_DDR2FULL	(6 << KINETIS_SIM_MCR_DDRCFG_BITS)

/* Multipurpose Clock Generator (MCG) register map */

struct kinetis_mcg_regs {
	UINT8 c1;		/* MCG Control 1 Register */
	UINT8 c2;		/* MCG Control 2 Register */
	UINT8 c3;		/* MCG Control 3 Register */
	UINT8 c4;		/* MCG Control 4 Register */
	UINT8 c5;		/* MCG Control 5 Register */
	UINT8 c6;		/* MCG Control 6 Register */
	UINT8 status;	/* MCG Status Register */
	UINT8 rsv0;
	UINT8 atc;		/* MCG Auto Trim Control Register */
	UINT8 rsv1;
	UINT8 atcvh;	/* MCG Auto Trim Compare Value High Register */
	UINT8 atcvl;	/* MCG Auto Trim Compare Value Low Register */
	UINT8 c7;		/* MCG Control 7 Register */
	UINT8 c8;		/* MCG Control 8 Register */
	UINT8 rsv2;
	UINT8 c10;		/* MCG Control 10 Register */
	UINT8 c11;		/* MCG Control 11 Register */
	UINT8 c12;		/* MCG Control 12 Register */
	UINT8 status2;	/* MCG Status 2 Register */
};

/* MCG registers base */

#define KINETIS_MCG_BASE		(KINETIS_AIPS0PERIPH_BASE + 0x00064000)
#define KINETIS_MCG			((volatile struct kinetis_mcg_regs *) \
					KINETIS_MCG_BASE)

/* Clock rate at the EXTAL0 input */

#define KINETIS_OSC0_RATE	50000000

/* Use external reference clock from Ethernet PHY as main MCG input */

#define KINETIS_MCG_PLLREFSEL	0	/* OSC0 */

/*
 * The EXTAL rate divided by the divisor value (2**10 = 1024) specified by this
 * constant should be as close to the 32..40 kHz range as possible.
 */

#define KINETIS_MCG_FRDIV_POW	10

/* Core/system clock divider: 120/1 = 120 MHz */

#define KINETIS_CCLK_DIV	1

/* Peripheral clock divider: 120/2 = 60 MHz */

#define KINETIS_PCLK_DIV	2

/* FlexBus clock divider: 120/3 = 40 MHz */

#define KINETIS_FLEXBUS_CLK_DIV	3

/* Flash clock divider: 120/5 = 24 MHz */

#define KINETIS_FLASH_CLK_DIV	5

/* PLL input divider: 50/5 = 10 MHz */

#define KINETIS_PLL_PRDIV	5

/* PLL multiplier: 10*24/2 = 120 MHz */

#define KINETIS_PLL_VDIV	24

/* PLL1 input divider: 50/5 = 10 MHz */

#define KINETIS_PLL1_PRDIV	5

/* PLL1 multiplier: 10*24/2 = 120 MHz */

#define KINETIS_PLL1_VDIV	24

/* Use PLL1 for MCGOUT */

#define KINETIS_MCGOUT_PLL1

#define KINETIS_PLL_PRDIV_MAX	8
#define KINETIS_PLL_VDIV_MIN	16
#define KINETIS_PLL_VDIV_MAX	47

#define KINETIS_PLL_REF_MIN	(8 * 1000 * 1000)	/* 8 MHz */
#define KINETIS_PLL_REF_MAX	(16 * 1000 * 1000)	/* 16 MHz */

#define KINETIS_PLL_VCO_DIV	2	/* There is a /2 divider after VCO */

/* Clock rate on the input of the MCG (Multipurpose Clock Generator) */

#define KINETIS_MCG_PLLREFSEL 0
#define KINETIS_MCG_PLL_IN_RATE		KINETIS_OSC0_RATE

/* Set KINETIS_MCG_FREQ_RANGE according to the crystal oscillator */

#define KINETIS_MCG_FREQ_RANGE	1	/* 1 MHz to 8 MHz */

/*
 * Set KINETIS_MCG_FRDIV to the code for writing into the FRDIV bit field
 * of the MCG_C1 register.
 */
 
#define KINETIS_MCG_FRDIV	(KINETIS_MCG_FRDIV_POW - 5)

/* MCGOUTCLK rate */

#ifdef KINETIS_MCGOUT_PLL1
#define KINETIS_MCGOUT_RATE \
	(KINETIS_MCG_PLL_IN_RATE / KINETIS_PLL1_PRDIV * KINETIS_PLL1_VDIV / \
	KINETIS_PLL_VCO_DIV)
#else
#define KINETIS_MCGOUT_RATE \
	(KINETIS_MCG_PLL_IN_RATE / KINETIS_PLL_PRDIV * KINETIS_PLL_VDIV / \
	KINETIS_PLL_VCO_DIV)
#endif /* KINETIS_MCGOUT_PLL1 */

/* PLL1 output rate */

#define KINETIS_PLL1OUT_RATE \
	(KINETIS_MCG_PLL_IN_RATE / KINETIS_PLL1_PRDIV * KINETIS_PLL1_VDIV / \
	KINETIS_PLL_VCO_DIV)

/* Core/system clock rate */

#define KINETIS_CPU_RATE	(KINETIS_MCGOUT_RATE / KINETIS_CCLK_DIV)

/* Peripheral clock rate */

#define KINETIS_PCLK_RATE	(KINETIS_MCGOUT_RATE / KINETIS_PCLK_DIV)

/* FlexBus clock rate */

#define KINETIS_FLEXBUS_RATE	(KINETIS_MCGOUT_RATE / KINETIS_FLEXBUS_CLK_DIV)

/* Flash clock rate */

#define KINETIS_FLASH_RATE	(KINETIS_MCGOUT_RATE / KINETIS_FLASH_CLK_DIV)

#ifdef CONFIG_KINETIS_DDR

/* DDR clock rate */

#define KINETIS_DDR_RATE	KINETIS_PLL1OUT_RATE
#endif /* CONFIG_KINETIS_DDR */

/* MCG registers */

/* MCG Control 1 Register */

#define KINETIS_MCG_C1_FRDIV_BITS	3

/* Clock Source Select bits (CLKS) */

#define KINETIS_MCG_C1_CLKS_BITS	6
#define KINETIS_MCG_C1_CLKS_MSK		(3 << KINETIS_MCG_C1_CLKS_BITS)
#define KINETIS_MCG_C1_CLKS_FLLPLL_MSK	(0 << KINETIS_MCG_C1_CLKS_BITS)
#define KINETIS_MCG_C1_CLKS_INT_REF_MSK	(1 << KINETIS_MCG_C1_CLKS_BITS)
#define KINETIS_MCG_C1_CLKS_EXT_REF_MSK	(2 << KINETIS_MCG_C1_CLKS_BITS)

/* MCG Control 2 Register */

/* Frequency Range Select bits */

#define KINETIS_MCG_C2_RANGE0_BITS	4

/*
 * External Reference Select for OSC0
 *    0 = External reference clock requested.
 *    1 = Oscillator requested.
 */

#define KINETIS_MCG_C2_EREFS0_MSK	(1 << 2)

/* Configure crystal oscillator for high-gain operation */

#define KINETIS_MCG_C2_HGO_MSK		(1 << 3)

/* MCG Control 5 Register */

/* PLL External Reference Divider */

#define KINETIS_MCG_C5_PRDIV_BITS	0

/* PLL Stop Enable */

#define KINETIS_MCG_C5_PLLSTEN_MSK	(1 << 5)

/* PLL0 Clock Enable */

#define KINETIS_MCG_C5_PLLCLKEN_MSK	(1 << 6)

/* PLL External Reference Select (for K70@120MHz) */

#define KINETIS_MCG_C5_PLLREFSEL_BIT	7
#define KINETIS_MCG_C5_PLLREFSEL_MSK	(1 << KINETIS_MCG_C5_PLLREFSEL_BIT)

/* MCG Control 6 Register */

/* VCO Divider */

#define KINETIS_MCG_C6_VDIV_BITS	0

/* PLL Select */

#define KINETIS_MCG_C6_PLLS_MSK		(1 << 6)

/* MCG Control 7 Register */

/* MCG OSC Clock Select */

#define KINETIS_MCG_C7_OSCSEL_MSK	(1 << 0)

/* MCG Control 10 Register */

/* Frequency Range1 Select */

#define KINETIS_MCG_C10_RANGE1_BITS	4

/*
 * External Reference Select for OSC1
 *    0 = External reference clock requested.
 *    1 = Oscillator requested.
 */

#define KINETIS_MCG_C10_EREFS1_MSK	(1 << 2)

/* MCG Control 11 Register */

/* PLL1 External Reference Divider */

#define KINETIS_MCG_C11_PRDIV_BITS	0

/* PLL Clock Select: PLL0 or PLL1 */

#define KINETIS_MCG_C11_PLLCS_MSK	(1 << 4)

/* PLL1 Stop Enable */

#define KINETIS_MCG_C11_PLLSTEN1_MSK	(1 << 5)

/* PLL1 Clock Enable */

#define KINETIS_MCG_C11_PLLCLKEN1_MSK	(1 << 6)

/* PLL1 External Reference Select (for K70@120MHz) */

#define KINETIS_MCG_C11_PLLREFSEL1_BIT	7
#define KINETIS_MCG_C11_PLLREFSEL1_MSK	(1 << KINETIS_MCG_C11_PLLREFSEL1_BIT)

/* MCG Control 12 Register */

/* VCO1 Divider */

#define KINETIS_MCG_C12_VDIV1_BITS	0

/* MCG Status Register */

/* Oscillator 0 initialization */

#define KINETIS_MCG_S_OSCINIT0_MSK	(1 << 1)

/* Clock Mode Status */

#define KINETIS_MCG_S_CLKST_MSK		(3 << 2)
#define KINETIS_MCG_S_CLKST_FLL		(0 << 2)
#define KINETIS_MCG_S_CLKST_INT_REF	(1 << 2)
#define KINETIS_MCG_S_CLKST_EXT_REF	(2 << 2)
#define KINETIS_MCG_S_CLKST_PLL		(3 << 2)

/* Internal Reference Status */

#define KINETIS_MCG_S_IREFST_MSK	(1 << 4)

/* PLL Select Status */

#define KINETIS_MCG_S_PLLST_MSK		(1 << 5)

/* Indicates whether the PLL has acquired lock */

#define KINETIS_MCG_S_LOCK_MSK		(1 << 6)

/* MCG Status 2 Register */

/* This bit indicates whether PLL1 has acquired lock */

#define KINETIS_MCG_S2_LOCK1_MSK	(1 << 6)

/* Oscillator 1 initialization */

#define KINETIS_MCG_S2_OSCINIT1_MSK	(1 << 1)

/* OSC registers base */

#define KINETIS_OSC0_BASE		(KINETIS_AIPS0PERIPH_BASE + 0x00065000)
#define KINETIS_OSC1_BASE		(KINETIS_AIPS0PERIPH_BASE + 0x000E5000)

/* Oscillator (OSC) registers */

/* OSC_CR register */

/* External Reference Enable */

#define KINETIS_OSC_CR_EREFSTEN_MSK	(1 << 5)

/* External Reference Stop Enable */

#define KINETIS_OSC_CR_ERCLKEN_MSK	(1 << 7)


/* Miscellaneous Control Module (MCM) register map */

struct kinetis_mcm_regs {
	UINT32 rsv0[2];
	UINT16 plasc;	/* Crossbar switch (AXBS) slave configuration */
	UINT16 plamc;	/* Crossbar switch (AXBS) master configuration */
	UINT32 cr;		/* Control register */
};

/* MCM registers base */

#define KINETIS_MCM_BASE		0xE0080000
#define KINETIS_MCM			((volatile struct kinetis_mcm_regs *) \
					KINETIS_MCM_BASE)

/* Watchdog timer (WDOG) register map */

struct kinetis_wdt_regs {
	UINT16 stctrlh;	/* Status and Control Register High */
	UINT16 stctrll;	/* Status and Control Register Low */
	UINT16 tovalh;	/* Time-out Value Register High */
	UINT16 tovall;	/* Time-out Value Register Low */
	UINT16 winh;	/* Window Register High */
	UINT16 winl;	/* Window Register Low */
	UINT16 refresh;	/* Refresh Register */
	UINT16 unlock;	/* Unlock Register */
	UINT16 tmrouth;	/* Timer Output Register High */
	UINT16 tmroutl;	/* Timer Output Register Low */
	UINT16 rstcnt;	/* Reset Count Register */
	UINT16 presc;	/* Prescaler Register */
};

/* Watchdog Timer registers base */

#define KINETIS_WDT_BASE		(KINETIS_AIPS0PERIPH_BASE + 0x00052000)
#define KINETIS_WDT			((volatile struct kinetis_wdt_regs *) \
					KINETIS_WDT_BASE)

#define KINETIS_WDT_UNLOCK_KEY1		0xC520
#define KINETIS_WDT_UNLOCK_KEY2		0xD928

#define KINETIS_WDT_ENABLE          (1 << 0)

/* GPIO port register map */

#define PORTA_PCR(n)     *(volatile UINT32 *)(KINETIS_AIPS0PERIPH_BASE + \
                                    0x49000 + (4 * (n)))
#define PORTB_PCR(n)     *(volatile UINT32 *)(KINETIS_AIPS0PERIPH_BASE + \
                                    0x4a000 + (4 * (n)))
#define PORTC_PCR(n)     *(volatile UINT32 *)(KINETIS_AIPS0PERIPH_BASE + \
                                    0x4b000 + (4 * (n)))
#define PORTD_PCR(n)     *(volatile UINT32 *)(KINETIS_AIPS0PERIPH_BASE + \
                                    0x4c000 + (4 * (n)))
#define PORTE_PCR(n)     *(volatile UINT32 *)(KINETIS_AIPS0PERIPH_BASE + \
                                    0x4d000 + (4 * (n)))							
#define PORTF_PCR(n)     *(volatile UINT32 *)(KINETIS_AIPS0PERIPH_BASE + \
                                    0x4e000 + (4 * (n)))

#define PORT_PCR_MUX(alt)  (alt << 8)

#define KINETIS_PORT_BASE(n) (KINETIS_AIPS0PERIPH_BASE + \
                                    0x49000 + (0x1000 * (n)))

#define KINETIS_GPIO_MODULE_BASE(n) (0x400ff000 + (0x40 * (n)))

#ifdef __cplusplus
}
#endif

#endif  /* __INCfsl_Kinetish */
