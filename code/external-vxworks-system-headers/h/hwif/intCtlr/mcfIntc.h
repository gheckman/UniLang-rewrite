/* mcfIntc.h - coldfire programmable interrupt timer device header */

/*
 * Copyright 2007, 2008 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,06feb08,rec  change CAST_M5208 macros to more generic type
01a,14nov07,rec	 created
*/

#ifndef __INCmcfIntch
#define __INCmcfIntch

/* Register read/write macros */
#define MCF_INTC_IPRH_OFF           0x000
#define MCF_INTC_IPRL_OFF           0x004
#define MCF_INTC_IMRH_OFF           0x008
#define MCF_INTC_IMRL_OFF           0x00C
#define MCF_INTC_INTFRCH_OFF        0x010
#define MCF_INTC_INTFRCL_OFF        0x014
#define MCF_INTC_ICONFIG_OFF        0x01A
#define MCF_INTC_SIMR_OFF           0x01C
#define MCF_INTC_CIMR_OFF           0x01D
#define MCF_INTC_CLMASK_OFF         0x01E
#define MCF_INTC_SLMASK_OFF         0x01F
#define MCF_INTC_ICR0_OFF           0x040
#define MCF_INTC_ICR1_OFF           0x041
#define MCF_INTC_ICR2_OFF           0x042
#define MCF_INTC_ICR3_OFF           0x043
#define MCF_INTC_ICR4_OFF           0x044
#define MCF_INTC_ICR5_OFF           0x045
#define MCF_INTC_ICR6_OFF           0x046
#define MCF_INTC_ICR7_OFF           0x047
#define MCF_INTC_ICR8_OFF           0x048
#define MCF_INTC_ICR9_OFF           0x049
#define MCF_INTC_ICR10_OFF          0x04A
#define MCF_INTC_ICR11_OFF          0x04B
#define MCF_INTC_ICR12_OFF          0x04C
#define MCF_INTC_ICR13_OFF          0x04D
#define MCF_INTC_ICR14_OFF          0x04E
#define MCF_INTC_ICR15_OFF          0x04F
#define MCF_INTC_ICR16_OFF          0x050
#define MCF_INTC_ICR17_OFF          0x051
#define MCF_INTC_ICR18_OFF          0x052
#define MCF_INTC_ICR19_OFF          0x053
#define MCF_INTC_ICR20_OFF          0x054
#define MCF_INTC_ICR21_OFF          0x055
#define MCF_INTC_ICR22_OFF          0x056
#define MCF_INTC_ICR23_OFF          0x057
#define MCF_INTC_ICR24_OFF          0x058
#define MCF_INTC_ICR25_OFF          0x059
#define MCF_INTC_ICR26_OFF          0x05A
#define MCF_INTC_ICR27_OFF          0x05B
#define MCF_INTC_ICR28_OFF          0x05C
#define MCF_INTC_ICR29_OFF          0x05D
#define MCF_INTC_ICR30_OFF          0x05E
#define MCF_INTC_ICR31_OFF          0x05F
#define MCF_INTC_ICR32_OFF          0x060
#define MCF_INTC_ICR33_OFF          0x061
#define MCF_INTC_ICR34_OFF          0x062
#define MCF_INTC_ICR35_OFF          0x063
#define MCF_INTC_ICR36_OFF          0x064
#define MCF_INTC_ICR37_OFF          0x065
#define MCF_INTC_ICR38_OFF          0x066
#define MCF_INTC_ICR39_OFF          0x067
#define MCF_INTC_ICR40_OFF          0x068
#define MCF_INTC_ICR41_OFF          0x069
#define MCF_INTC_ICR42_OFF          0x06A
#define MCF_INTC_ICR43_OFF          0x06B
#define MCF_INTC_ICR44_OFF          0x06C
#define MCF_INTC_ICR45_OFF          0x06D
#define MCF_INTC_ICR46_OFF          0x06E
#define MCF_INTC_ICR47_OFF          0x06F
#define MCF_INTC_ICR48_OFF          0x070
#define MCF_INTC_ICR49_OFF          0x071
#define MCF_INTC_ICR50_OFF          0x072
#define MCF_INTC_ICR51_OFF          0x073
#define MCF_INTC_ICR52_OFF          0x074
#define MCF_INTC_ICR53_OFF          0x075
#define MCF_INTC_ICR54_OFF          0x076
#define MCF_INTC_ICR55_OFF          0x077
#define MCF_INTC_ICR56_OFF          0x078
#define MCF_INTC_ICR57_OFF          0x079
#define MCF_INTC_ICR58_OFF          0x07A
#define MCF_INTC_ICR59_OFF          0x07B
#define MCF_INTC_ICR60_OFF          0x07C
#define MCF_INTC_ICR61_OFF          0x07D
#define MCF_INTC_ICR62_OFF          0x07E
#define MCF_INTC_ICR63_OFF          0x07F
#define MCF_INTC_SWIACK_OFF         0x0E0
#define MCF_INTC_L1IACK_OFF         0x0E4
#define MCF_INTC_L2IACK_OFF         0x0E8
#define MCF_INTC_L3IACK_OFF         0x0EC
#define MCF_INTC_L4IACK_OFF         0x0F0
#define MCF_INTC_L5IACK_OFF         0x0F4
#define MCF_INTC_L6IACK_OFF         0x0F8
#define MCF_INTC_L7IACK_OFF         0x0FC



#define MCF_INTC_IPRH        (CAST_MCF_VOL(UINT32)(MCF_INTC_BASE + \
                                MCF_INTC_IPRH_OFF))
#define MCF_INTC_IPRL        (CAST_MCF_VOL(UINT32)(MCF_INTC_BASE + \
                                MCF_INTC_IPRL_OFF))
#define MCF_INTC_IMRH        (CAST_MCF_VOL(UINT32)(MCF_INTC_BASE + \
                                MCF_INTC_IMRH_OFF))
#define MCF_INTC_IMRL        (CAST_MCF_VOL(UINT32)(MCF_INTC_BASE + \
                                MCF_INTC_IMRL_OFF))
#define MCF_INTC_INTFRCH     (CAST_MCF_VOL(UINT32)(MCF_INTC_BASE + \
                                MCF_INTC_INTFRCH_OFF))
#define MCF_INTC_INTFRCL     (CAST_MCF_VOL(UINT32)(MCF_INTC_BASE + \
                                MCF_INTC_INTFRCL_OFF))
#define MCF_INTC_ICONFIG     (CAST_MCF_VOL(UINT16))(MCF_INTC_BASE + \
                                MCF_INTC_ICONFIG_OFF))
#define MCF_INTC_SIMR        (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_SIMR_OFF))
#define MCF_INTC_CIMR        (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_CIMR_OFF))
#define MCF_INTC_CLMASK      (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_CLMASK_OFF))
#define MCF_INTC_SLMASK      (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_SLMASK_OFF))
#define MCF_INTC_ICR0        (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR0_OFF))
#define MCF_INTC_ICR1        (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR1_OFF))
#define MCF_INTC_ICR2        (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR2_OFF))
#define MCF_INTC_ICR3        (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR3_OFF))
#define MCF_INTC_ICR4        (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR4_OFF))
#define MCF_INTC_ICR5        (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR5_OFF))
#define MCF_INTC_ICR6        (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR6_OFF))
#define MCF_INTC_ICR7        (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR7_OFF))
#define MCF_INTC_ICR8        (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR8_OFF))
#define MCF_INTC_ICR9        (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR9_OFF))
#define MCF_INTC_ICR10       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR10_OFF))
#define MCF_INTC_ICR11       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR11_OFF))
#define MCF_INTC_ICR12       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR12_OFF))
#define MCF_INTC_ICR13       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR13_OFF))
#define MCF_INTC_ICR14       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR14_OFF))
#define MCF_INTC_ICR15       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR15_OFF))
#define MCF_INTC_ICR16       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR16_OFF))
#define MCF_INTC_ICR17       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR17_OFF))
#define MCF_INTC_ICR18       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR18_OFF))
#define MCF_INTC_ICR19       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR19_OFF))
#define MCF_INTC_ICR20       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR20_OFF))
#define MCF_INTC_ICR21       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR21_OFF))
#define MCF_INTC_ICR22       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR22_OFF))
#define MCF_INTC_ICR23       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR23_OFF))
#define MCF_INTC_ICR24       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR24_OFF))
#define MCF_INTC_ICR25       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR25_OFF))
#define MCF_INTC_ICR26       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR26_OFF))
#define MCF_INTC_ICR27       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR27_OFF))
#define MCF_INTC_ICR28       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR28_OFF))
#define MCF_INTC_ICR29       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR29_OFF))
#define MCF_INTC_ICR30       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR30_OFF))
#define MCF_INTC_ICR31       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR31_OFF))
#define MCF_INTC_ICR32       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR32_OFF))
#define MCF_INTC_ICR33       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR33_OFF))
#define MCF_INTC_ICR34       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR34_OFF))
#define MCF_INTC_ICR35       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR35_OFF))
#define MCF_INTC_ICR36       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR36_OFF))
#define MCF_INTC_ICR37       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR37_OFF))
#define MCF_INTC_ICR38       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR38_OFF))
#define MCF_INTC_ICR39       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR39_OFF))
#define MCF_INTC_ICR40       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR40_OFF))
#define MCF_INTC_ICR41       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR41_OFF))
#define MCF_INTC_ICR42       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR42_OFF))
#define MCF_INTC_ICR43       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR43_OFF))
#define MCF_INTC_ICR44       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR44_OFF))
#define MCF_INTC_ICR45       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR45_OFF))
#define MCF_INTC_ICR46       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR46_OFF))
#define MCF_INTC_ICR47       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR47_OFF))
#define MCF_INTC_ICR48       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR48_OFF))
#define MCF_INTC_ICR49       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR49_OFF))
#define MCF_INTC_ICR50       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR50_OFF))
#define MCF_INTC_ICR51       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR51_OFF))
#define MCF_INTC_ICR52       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR52_OFF))
#define MCF_INTC_ICR53       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR53_OFF))
#define MCF_INTC_ICR54       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR54_OFF))
#define MCF_INTC_ICR55       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR55_OFF))
#define MCF_INTC_ICR56       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR56_OFF))
#define MCF_INTC_ICR57       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR57_OFF))
#define MCF_INTC_ICR58       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR58_OFF))
#define MCF_INTC_ICR59       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR59_OFF))
#define MCF_INTC_ICR60       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR60_OFF))
#define MCF_INTC_ICR61       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR61_OFF))
#define MCF_INTC_ICR62       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR62_OFF))
#define MCF_INTC_ICR63       (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR63_OFF))
#define MCF_INTC_ICR(x)      (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_ICR0_OFF+((x)*0x001)))
#define MCF_INTC_SWIACK      (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_SWIACK_OFF))
#define MCF_INTC_L1IACK      (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_L1IACK_OFF))
#define MCF_INTC_L2IACK      (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_L2IACK_OFF))
#define MCF_INTC_L3IACK      (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_L3IACK_OFF))
#define MCF_INTC_L4IACK      (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_L4IACK_OFF))
#define MCF_INTC_L5IACK      (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_L5IACK_OFF))
#define MCF_INTC_L6IACK      (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_L6IACK_OFF))
#define MCF_INTC_L7IACK      (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_L7IACK_OFF))
#define MCF_INTC_LIACK(x)    (CAST_MCF_VOL(UINT8)(MCF_INTC_BASE + \
                                MCF_INTC_L1IACK_OFF+((x-1)*0x004)))

/*
 *
 * Interrupt Controller (INTC_IACK)
 *
 */

/* Register read/write macros */
#define MCF_INTC_IACK_GSWIACK      (CAST_MCF_VOL(UINT8)(0xFC0540E0))
#define MCF_INTC_IACK_GL1IACK      (CAST_MCF_VOL(UINT8)(0xFC0540E4))
#define MCF_INTC_IACK_GL2IACK      (CAST_MCF_VOL(UINT8)(0xFC0540E8))
#define MCF_INTC_IACK_GL3IACK      (CAST_MCF_VOL(UINT8)(0xFC0540EC))
#define MCF_INTC_IACK_GL4IACK      (CAST_MCF_VOL(UINT8)(0xFC0540F0))
#define MCF_INTC_IACK_GL5IACK      (CAST_MCF_VOL(UINT8)(0xFC0540F4))
#define MCF_INTC_IACK_GL6IACK      (CAST_MCF_VOL(UINT8)(0xFC0540F8))
#define MCF_INTC_IACK_GL7IACK      (CAST_MCF_VOL(UINT8)(0xFC0540FC))
#define MCF_INTC_IACK_GLIACK(x)    (CAST_MCF_VOL(UINT8)(0xFC0540E4+ \
                                        ((x-1)*0x004)))

/* Bit definitions and macros for MCF_INTC_IACK_GSWIACK */
#define MCF_INTC_IACK_GSWIACK_VECTOR(x)  (((x)&0xFF)<<0)

/* Bit definitions and macros for MCF_INTC_IACK_GLIACK */
#define MCF_INTC_IACK_GLIACK_VECTOR(x)   (((x)&0xFF)<<0)



/* Bit definitions and macros for MCF_INTC_IPRH */
#define MCF_INTC_IPRH_INT32        (0x00000001)
#define MCF_INTC_IPRH_INT33        (0x00000002)
#define MCF_INTC_IPRH_INT34        (0x00000004)
#define MCF_INTC_IPRH_INT35        (0x00000008)
#define MCF_INTC_IPRH_INT36        (0x00000010)
#define MCF_INTC_IPRH_INT37        (0x00000020)
#define MCF_INTC_IPRH_INT38        (0x00000040)
#define MCF_INTC_IPRH_INT39        (0x00000080)
#define MCF_INTC_IPRH_INT40        (0x00000100)
#define MCF_INTC_IPRH_INT41        (0x00000200)
#define MCF_INTC_IPRH_INT42        (0x00000400)
#define MCF_INTC_IPRH_INT43        (0x00000800)
#define MCF_INTC_IPRH_INT44        (0x00001000)
#define MCF_INTC_IPRH_INT45        (0x00002000)
#define MCF_INTC_IPRH_INT46        (0x00004000)
#define MCF_INTC_IPRH_INT47        (0x00008000)
#define MCF_INTC_IPRH_INT48        (0x00010000)
#define MCF_INTC_IPRH_INT49        (0x00020000)
#define MCF_INTC_IPRH_INT50        (0x00040000)
#define MCF_INTC_IPRH_INT51        (0x00080000)
#define MCF_INTC_IPRH_INT52        (0x00100000)
#define MCF_INTC_IPRH_INT53        (0x00200000)
#define MCF_INTC_IPRH_INT54        (0x00400000)
#define MCF_INTC_IPRH_INT55        (0x00800000)
#define MCF_INTC_IPRH_INT56        (0x01000000)
#define MCF_INTC_IPRH_INT57        (0x02000000)
#define MCF_INTC_IPRH_INT58        (0x04000000)
#define MCF_INTC_IPRH_INT59        (0x08000000)
#define MCF_INTC_IPRH_INT60        (0x10000000)
#define MCF_INTC_IPRH_INT61        (0x20000000)
#define MCF_INTC_IPRH_INT62        (0x40000000)
#define MCF_INTC_IPRH_INT63        (0x80000000)

/* Bit definitions and macros for MCF_INTC_IPRL */
#define MCF_INTC_IPRL_INT0         (0x00000001)
#define MCF_INTC_IPRL_INT1         (0x00000002)
#define MCF_INTC_IPRL_INT2         (0x00000004)
#define MCF_INTC_IPRL_INT3         (0x00000008)
#define MCF_INTC_IPRL_INT4         (0x00000010)
#define MCF_INTC_IPRL_INT5         (0x00000020)
#define MCF_INTC_IPRL_INT6         (0x00000040)
#define MCF_INTC_IPRL_INT7         (0x00000080)
#define MCF_INTC_IPRL_INT8         (0x00000100)
#define MCF_INTC_IPRL_INT9         (0x00000200)
#define MCF_INTC_IPRL_INT10        (0x00000400)
#define MCF_INTC_IPRL_INT11        (0x00000800)
#define MCF_INTC_IPRL_INT12        (0x00001000)
#define MCF_INTC_IPRL_INT13        (0x00002000)
#define MCF_INTC_IPRL_INT14        (0x00004000)
#define MCF_INTC_IPRL_INT15        (0x00008000)
#define MCF_INTC_IPRL_INT16        (0x00010000)
#define MCF_INTC_IPRL_INT17        (0x00020000)
#define MCF_INTC_IPRL_INT18        (0x00040000)
#define MCF_INTC_IPRL_INT19        (0x00080000)
#define MCF_INTC_IPRL_INT20        (0x00100000)
#define MCF_INTC_IPRL_INT21        (0x00200000)
#define MCF_INTC_IPRL_INT22        (0x00400000)
#define MCF_INTC_IPRL_INT23        (0x00800000)
#define MCF_INTC_IPRL_INT24        (0x01000000)
#define MCF_INTC_IPRL_INT25        (0x02000000)
#define MCF_INTC_IPRL_INT26        (0x04000000)
#define MCF_INTC_IPRL_INT27        (0x08000000)
#define MCF_INTC_IPRL_INT28        (0x10000000)
#define MCF_INTC_IPRL_INT29        (0x20000000)
#define MCF_INTC_IPRL_INT30        (0x40000000)
#define MCF_INTC_IPRL_INT31        (0x80000000)

/* Bit definitions and macros for MCF_INTC_IMRH */
#define MCF_INTC_IMRH_INT_MASK32   (0x00000001)
#define MCF_INTC_IMRH_INT_MASK33   (0x00000002)
#define MCF_INTC_IMRH_INT_MASK34   (0x00000004)
#define MCF_INTC_IMRH_INT_MASK35   (0x00000008)
#define MCF_INTC_IMRH_INT_MASK36   (0x00000010)
#define MCF_INTC_IMRH_INT_MASK37   (0x00000020)
#define MCF_INTC_IMRH_INT_MASK38   (0x00000040)
#define MCF_INTC_IMRH_INT_MASK39   (0x00000080)
#define MCF_INTC_IMRH_INT_MASK40   (0x00000100)
#define MCF_INTC_IMRH_INT_MASK41   (0x00000200)
#define MCF_INTC_IMRH_INT_MASK42   (0x00000400)
#define MCF_INTC_IMRH_INT_MASK43   (0x00000800)
#define MCF_INTC_IMRH_INT_MASK44   (0x00001000)
#define MCF_INTC_IMRH_INT_MASK45   (0x00002000)
#define MCF_INTC_IMRH_INT_MASK46   (0x00004000)
#define MCF_INTC_IMRH_INT_MASK47   (0x00008000)
#define MCF_INTC_IMRH_INT_MASK48   (0x00010000)
#define MCF_INTC_IMRH_INT_MASK49   (0x00020000)
#define MCF_INTC_IMRH_INT_MASK50   (0x00040000)
#define MCF_INTC_IMRH_INT_MASK51   (0x00080000)
#define MCF_INTC_IMRH_INT_MASK52   (0x00100000)
#define MCF_INTC_IMRH_INT_MASK53   (0x00200000)
#define MCF_INTC_IMRH_INT_MASK54   (0x00400000)
#define MCF_INTC_IMRH_INT_MASK55   (0x00800000)
#define MCF_INTC_IMRH_INT_MASK56   (0x01000000)
#define MCF_INTC_IMRH_INT_MASK57   (0x02000000)
#define MCF_INTC_IMRH_INT_MASK58   (0x04000000)
#define MCF_INTC_IMRH_INT_MASK59   (0x08000000)
#define MCF_INTC_IMRH_INT_MASK60   (0x10000000)
#define MCF_INTC_IMRH_INT_MASK61   (0x20000000)
#define MCF_INTC_IMRH_INT_MASK62   (0x40000000)
#define MCF_INTC_IMRH_INT_MASK63   (0x80000000)

/* Bit definitions and macros for MCF_INTC_IMRL */
#define MCF_INTC_IMRL_INT_MASK0    (0x00000001)
#define MCF_INTC_IMRL_INT_MASK1    (0x00000002)
#define MCF_INTC_IMRL_INT_MASK2    (0x00000004)
#define MCF_INTC_IMRL_INT_MASK3    (0x00000008)
#define MCF_INTC_IMRL_INT_MASK4    (0x00000010)
#define MCF_INTC_IMRL_INT_MASK5    (0x00000020)
#define MCF_INTC_IMRL_INT_MASK6    (0x00000040)
#define MCF_INTC_IMRL_INT_MASK7    (0x00000080)
#define MCF_INTC_IMRL_INT_MASK8    (0x00000100)
#define MCF_INTC_IMRL_INT_MASK9    (0x00000200)
#define MCF_INTC_IMRL_INT_MASK10   (0x00000400)
#define MCF_INTC_IMRL_INT_MASK11   (0x00000800)
#define MCF_INTC_IMRL_INT_MASK12   (0x00001000)
#define MCF_INTC_IMRL_INT_MASK13   (0x00002000)
#define MCF_INTC_IMRL_INT_MASK14   (0x00004000)
#define MCF_INTC_IMRL_INT_MASK15   (0x00008000)
#define MCF_INTC_IMRL_INT_MASK16   (0x00010000)
#define MCF_INTC_IMRL_INT_MASK17   (0x00020000)
#define MCF_INTC_IMRL_INT_MASK18   (0x00040000)
#define MCF_INTC_IMRL_INT_MASK19   (0x00080000)
#define MCF_INTC_IMRL_INT_MASK20   (0x00100000)
#define MCF_INTC_IMRL_INT_MASK21   (0x00200000)
#define MCF_INTC_IMRL_INT_MASK22   (0x00400000)
#define MCF_INTC_IMRL_INT_MASK23   (0x00800000)
#define MCF_INTC_IMRL_INT_MASK24   (0x01000000)
#define MCF_INTC_IMRL_INT_MASK25   (0x02000000)
#define MCF_INTC_IMRL_INT_MASK26   (0x04000000)
#define MCF_INTC_IMRL_INT_MASK27   (0x08000000)
#define MCF_INTC_IMRL_INT_MASK28   (0x10000000)
#define MCF_INTC_IMRL_INT_MASK29   (0x20000000)
#define MCF_INTC_IMRL_INT_MASK30   (0x40000000)
#define MCF_INTC_IMRL_INT_MASK31   (0x80000000)

/* Bit definitions and macros for MCF_INTC_INTFRCH */
#define MCF_INTC_INTFRCH_INTFRC32  (0x00000001)
#define MCF_INTC_INTFRCH_INTFRC33  (0x00000002)
#define MCF_INTC_INTFRCH_INTFRC34  (0x00000004)
#define MCF_INTC_INTFRCH_INTFRC35  (0x00000008)
#define MCF_INTC_INTFRCH_INTFRC36  (0x00000010)
#define MCF_INTC_INTFRCH_INTFRC37  (0x00000020)
#define MCF_INTC_INTFRCH_INTFRC38  (0x00000040)
#define MCF_INTC_INTFRCH_INTFRC39  (0x00000080)
#define MCF_INTC_INTFRCH_INTFRC40  (0x00000100)
#define MCF_INTC_INTFRCH_INTFRC41  (0x00000200)
#define MCF_INTC_INTFRCH_INTFRC42  (0x00000400)
#define MCF_INTC_INTFRCH_INTFRC43  (0x00000800)
#define MCF_INTC_INTFRCH_INTFRC44  (0x00001000)
#define MCF_INTC_INTFRCH_INTFRC45  (0x00002000)
#define MCF_INTC_INTFRCH_INTFRC46  (0x00004000)
#define MCF_INTC_INTFRCH_INTFRC47  (0x00008000)
#define MCF_INTC_INTFRCH_INTFRC48  (0x00010000)
#define MCF_INTC_INTFRCH_INTFRC49  (0x00020000)
#define MCF_INTC_INTFRCH_INTFRC50  (0x00040000)
#define MCF_INTC_INTFRCH_INTFRC51  (0x00080000)
#define MCF_INTC_INTFRCH_INTFRC52  (0x00100000)
#define MCF_INTC_INTFRCH_INTFRC53  (0x00200000)
#define MCF_INTC_INTFRCH_INTFRC54  (0x00400000)
#define MCF_INTC_INTFRCH_INTFRC55  (0x00800000)
#define MCF_INTC_INTFRCH_INTFRC56  (0x01000000)
#define MCF_INTC_INTFRCH_INTFRC57  (0x02000000)
#define MCF_INTC_INTFRCH_INTFRC58  (0x04000000)
#define MCF_INTC_INTFRCH_INTFRC59  (0x08000000)
#define MCF_INTC_INTFRCH_INTFRC60  (0x10000000)
#define MCF_INTC_INTFRCH_INTFRC61  (0x20000000)
#define MCF_INTC_INTFRCH_INTFRC62  (0x40000000)
#define MCF_INTC_INTFRCH_INTFRC63  (0x80000000)

/* Bit definitions and macros for MCF_INTC_INTFRCL */
#define MCF_INTC_INTFRCL_INTFRC0   (0x00000001)
#define MCF_INTC_INTFRCL_INTFRC1   (0x00000002)
#define MCF_INTC_INTFRCL_INTFRC2   (0x00000004)
#define MCF_INTC_INTFRCL_INTFRC3   (0x00000008)
#define MCF_INTC_INTFRCL_INTFRC4   (0x00000010)
#define MCF_INTC_INTFRCL_INTFRC5   (0x00000020)
#define MCF_INTC_INTFRCL_INTFRC6   (0x00000040)
#define MCF_INTC_INTFRCL_INTFRC7   (0x00000080)
#define MCF_INTC_INTFRCL_INTFRC8   (0x00000100)
#define MCF_INTC_INTFRCL_INTFRC9   (0x00000200)
#define MCF_INTC_INTFRCL_INTFRC10  (0x00000400)
#define MCF_INTC_INTFRCL_INTFRC11  (0x00000800)
#define MCF_INTC_INTFRCL_INTFRC12  (0x00001000)
#define MCF_INTC_INTFRCL_INTFRC13  (0x00002000)
#define MCF_INTC_INTFRCL_INTFRC14  (0x00004000)
#define MCF_INTC_INTFRCL_INTFRC15  (0x00008000)
#define MCF_INTC_INTFRCL_INTFRC16  (0x00010000)
#define MCF_INTC_INTFRCL_INTFRC17  (0x00020000)
#define MCF_INTC_INTFRCL_INTFRC18  (0x00040000)
#define MCF_INTC_INTFRCL_INTFRC19  (0x00080000)
#define MCF_INTC_INTFRCL_INTFRC20  (0x00100000)
#define MCF_INTC_INTFRCL_INTFRC21  (0x00200000)
#define MCF_INTC_INTFRCL_INTFRC22  (0x00400000)
#define MCF_INTC_INTFRCL_INTFRC23  (0x00800000)
#define MCF_INTC_INTFRCL_INTFRC24  (0x01000000)
#define MCF_INTC_INTFRCL_INTFRC25  (0x02000000)
#define MCF_INTC_INTFRCL_INTFRC26  (0x04000000)
#define MCF_INTC_INTFRCL_INTFRC27  (0x08000000)
#define MCF_INTC_INTFRCL_INTFRC28  (0x10000000)
#define MCF_INTC_INTFRCL_INTFRC29  (0x20000000)
#define MCF_INTC_INTFRCL_INTFRC30  (0x40000000)
#define MCF_INTC_INTFRCL_INTFRC31  (0x80000000)

/* Bit definitions and macros for MCF_INTC_ICONFIG */
#define MCF_INTC_ICONFIG_EMASK     (0x0020)
#define MCF_INTC_ICONFIG_ELVLPRI1  (0x0200)
#define MCF_INTC_ICONFIG_ELVLPRI2  (0x0400)
#define MCF_INTC_ICONFIG_ELVLPRI3  (0x0800)
#define MCF_INTC_ICONFIG_ELVLPRI4  (0x1000)
#define MCF_INTC_ICONFIG_ELVLPRI5  (0x2000)
#define MCF_INTC_ICONFIG_ELVLPRI6  (0x4000)
#define MCF_INTC_ICONFIG_ELVLPRI7  (0x8000)

/* Bit definitions and macros for MCF_INTC_SIMR */
#define MCF_INTC_SIMR_SIMR(x)      (((x)&0x7F)<<0)

/* Bit definitions and macros for MCF_INTC_CIMR */
#define MCF_INTC_CIMR_CIMR(x)      (((x)&0x7F)<<0)

/* Bit definitions and macros for MCF_INTC_CLMASK */
#define MCF_INTC_CLMASK_CLMASK(x)  (((x)&0x0F)<<0)

/* Bit definitions and macros for MCF_INTC_SLMASK */
#define MCF_INTC_SLMASK_SLMASK(x)  (((x)&0x0F)<<0)

/* Bit definitions and macros for MCF_INTC_ICR */
#define MCF_INTC_ICR_IL(x)         (((x)&0x07)<<0)

/* Bit definitions and macros for MCF_INTC_SWIACK */
#define MCF_INTC_SWIACK_VECTOR(x)  (((x)&0xFF)<<0)

/* Bit definitions and macros for MCF_INTC_LIACK */
#define MCF_INTC_LIACK_VECTOR(x)   (((x)&0xFF)<<0)

#endif
