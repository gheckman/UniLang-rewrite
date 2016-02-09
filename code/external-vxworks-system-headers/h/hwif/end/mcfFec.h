/* mcfFec.h - Motorola/Freescale FEC END device header */

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
01a,14dec07,rec	 created
*/

#ifndef __INCmcfFech
#define __INCmcfFech

/* register offsets */

#define MCF_FEC_EIR_OFF                     0x004
#define MCF_FEC_EIMR_OFF                    0x008
#define MCF_FEC_RDAR_OFF                    0x010
#define MCF_FEC_TDAR_OFF                    0x014
#define MCF_FEC_ECR_OFF                     0x024
#define MCF_FEC_MMFR_OFF                    0x040
#define MCF_FEC_MSCR_OFF                    0x044
#define MCF_FEC_MIBC_OFF                    0x064
#define MCF_FEC_RCR_OFF                     0x084
#define MCF_FEC_TCR_OFF                     0x0C4
#define MCF_FEC_PALR_OFF                    0x0E4
#define MCF_FEC_PAUR_OFF                    0x0E8
#define MCF_FEC_OPD_OFF                     0x0EC
#define MCF_FEC_IAUR_OFF                    0x118
#define MCF_FEC_IALR_OFF                    0x11C
#define MCF_FEC_GAUR_OFF                    0x120
#define MCF_FEC_GALR_OFF                    0x124
#define MCF_FEC_TFWR_OFF                    0x144
#define MCF_FEC_FRBR_OFF                    0x14C
#define MCF_FEC_FRSR_OFF                    0x150
#define MCF_FEC_ERDSR_OFF                   0x180
#define MCF_FEC_ETDSR_OFF                   0x184
#define MCF_FEC_EMRBR_OFF                   0x188
#define MCF_FEC_RMON_T_DROP_OFF             0x200
#define MCF_FEC_RMON_T_PACKETS_OFF          0x204
#define MCF_FEC_RMON_T_BC_PKT_OFF           0x208
#define MCF_FEC_RMON_T_MC_PKT_OFF           0x20C
#define MCF_FEC_RMON_T_CRC_ALIGN_OFF        0x210
#define MCF_FEC_RMON_T_UNDERSIZE_OFF        0x214
#define MCF_FEC_RMON_T_OVERSIZE_OFF         0x218
#define MCF_FEC_RMON_T_FRAG_OFF             0x21C
#define MCF_FEC_RMON_T_JAB_OFF              0x220
#define MCF_FEC_RMON_T_COL_OFF              0x224
#define MCF_FEC_RMON_T_P64_OFF              0x228
#define MCF_FEC_RMON_T_P65TO127_OFF         0x22C
#define MCF_FEC_RMON_T_P128TO255_OFF        0x230
#define MCF_FEC_RMON_T_P256TO511_OFF        0x234
#define MCF_FEC_RMON_T_P512TO1023_OFF       0x238
#define MCF_FEC_RMON_T_P1024TO2047_OFF      0x23C
#define MCF_FEC_RMON_T_P_GTE2048_OFF        0x240
#define MCF_FEC_RMON_T_OCTETS_OFF           0x244
#define MCF_FEC_IEEE_T_DROP_OFF             0x248
#define MCF_FEC_IEEE_T_FRAME_OK_OFF         0x24C
#define MCF_FEC_IEEE_T_1COL_OFF             0x250
#define MCF_FEC_IEEE_T_MCOL_OFF             0x254
#define MCF_FEC_IEEE_T_DEF_OFF              0x258
#define MCF_FEC_IEEE_T_LCOL_OFF             0x25C
#define MCF_FEC_IEEE_T_EXCOL_OFF            0x260
#define MCF_FEC_IEEE_T_MACERR_OFF           0x264
#define MCF_FEC_IEEE_T_CSERR_OFF            0x268
#define MCF_FEC_IEEE_T_SQE_OFF              0x26C
#define MCF_FEC_IEEE_T_FDXFC_OFF            0x270
#define MCF_FEC_IEEE_T_OCTETS_OK_OFF        0x274
#define MCF_FEC_RMON_R_PACKETS_OFF          0x284
#define MCF_FEC_RMON_R_BC_PKT_OFF           0x288
#define MCF_FEC_RMON_R_MC_PKT_OFF           0x28C
#define MCF_FEC_RMON_R_CRC_ALIGN_OFF        0x290
#define MCF_FEC_RMON_R_UNDERSIZE_OFF        0x294
#define MCF_FEC_RMON_R_OVERSIZE_OFF         0x298
#define MCF_FEC_RMON_R_FRAG_OFF             0x29C
#define MCF_FEC_RMON_R_JAB_OFF              0x2A0
#define MCF_FEC_RMON_R_RESVD_0_OFF          0x2A4
#define MCF_FEC_RMON_R_P64_OFF              0x2A8
#define MCF_FEC_RMON_R_P65TO127_OFF         0x2AC
#define MCF_FEC_RMON_R_P128TO255_OFF        0x2B0
#define MCF_FEC_RMON_R_P256TO511_OFF        0x2B4
#define MCF_FEC_RMON_R_512TO1023_OFF        0x2B8
#define MCF_FEC_RMON_R_P_GTE2048_OFF        0x2C0
#define MCF_FEC_RMON_R_1024TO2047_OFF       0x2BC
#define MCF_FEC_RMON_R_OCTETS_OFF           0x2C4
#define MCF_FEC_IEEE_R_DROP_OFF             0x2C8
#define MCF_FEC_IEEE_R_FRAME_OK_OFF         0x2CC
#define MCF_FEC_IEEE_R_CRC_OFF              0x2D0
#define MCF_FEC_IEEE_R_ALIGN_OFF            0x2D4
#define MCF_FEC_IEEE_R_MACERR_OFF           0x2D8
#define MCF_FEC_IEEE_R_FDXFC_OFF            0x2DC
#define MCF_FEC_IEEE_R_OCTETS_OK_OFF        0x2E0

/* Register read/write macros */

#define MCF_FEC_EIR		  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_EIR_OFF))
#define MCF_FEC_EIMR		  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_EIMR_OFF))
#define MCF_FEC_RDAR		  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RDAR_OFF))
#define MCF_FEC_TDAR		  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_TDAR_OFF))
#define MCF_FEC_ECR		  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_ECR_OFF))
#define MCF_FEC_MMFR		  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_MMFR_OFF))
#define MCF_FEC_MSCR		  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_MSCR_OFF))
#define MCF_FEC_MIBC		  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_MIBC_OFF))
#define MCF_FEC_RCR		  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RCR_OFF))
#define MCF_FEC_TCR		  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_TCR_OFF))
#define MCF_FEC_PALR		  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_PALR_OFF))
#define MCF_FEC_PAUR		  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_PAUR_OFF))
#define MCF_FEC_OPD		  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_OPD_OFF))
#define MCF_FEC_IAUR		  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_IAUR_OFF))
#define MCF_FEC_IALR		  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_IALR_OFF))
#define MCF_FEC_GAUR		  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_GAUR_OFF))
#define MCF_FEC_GALR		  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_GALR_OFF))
#define MCF_FEC_TFWR		  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_TFWR_OFF))
#define MCF_FEC_FRBR		  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_FRBR_OFF))
#define MCF_FEC_FRSR		  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_FRSR_OFF))
#define MCF_FEC_ERDSR		  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_ERDSR_OFF))
#define MCF_FEC_ETDSR		  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_ETDSR_OFF))
#define MCF_FEC_EMRBR		  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_EMRBR_OFF))
#define MCF_FEC_RMON_T_DROP	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_T_DROP_OFF))
#define MCF_FEC_RMON_T_PACKETS	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_T_PACKETS_OFF))
#define MCF_FEC_RMON_T_BC_PKT	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_T_BC_PKT_OFF))
#define MCF_FEC_RMON_T_MC_PKT	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_T_MC_PKT_OFF))
#define MCF_FEC_RMON_T_CRC_ALIGN  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_T_CRC_ALIGN_OFF))
#define MCF_FEC_RMON_T_UNDERSIZE  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_T_UNDERSIZE_OFF))
#define MCF_FEC_RMON_T_OVERSIZE	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_T_OVERSIZE_OFF))
#define MCF_FEC_RMON_T_FRAG	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_T_FRAG_OFF))
#define MCF_FEC_RMON_T_JAB	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_T_JAB_OFF))
#define MCF_FEC_RMON_T_COL	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_T_COL_OFF))
#define MCF_FEC_RMON_T_P64	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_T_P64_OFF))
#define MCF_FEC_RMON_T_P65TO127	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_T_P65TO127_OFF))
#define MCF_FEC_RMON_T_P128TO255  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_T_P128TO255_OFF))
#define MCF_FEC_RMON_T_P256TO511  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_T_P256TO511_OFF))
#define MCF_FEC_RMON_T_P512TO1023 (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_T_P512TO1023_OFF))
#define MCF_FEC_RMON_T_P1024TO2047 (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_T_P1024TO2047_OFF))
#define MCF_FEC_RMON_T_P_GTE2048  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_T_P_GTE2048_OFF))
#define MCF_FEC_RMON_T_OCTETS	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_T_OCTETS_OFF))
#define MCF_FEC_IEEE_T_DROP	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_IEEE_T_DROP_OFF))
#define MCF_FEC_IEEE_T_FRAME_OK	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_IEEE_T_FRAME_OK_OFF))
#define MCF_FEC_IEEE_T_1COL	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_IEEE_T_1COL_OFF))
#define MCF_FEC_IEEE_T_MCOL	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_IEEE_T_MCOL_OFF))
#define MCF_FEC_IEEE_T_DEF	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_IEEE_T_DEF_OFF))
#define MCF_FEC_IEEE_T_LCOL	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_IEEE_T_LCOL_OFF))
#define MCF_FEC_IEEE_T_EXCOL	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_IEEE_T_EXCOL_OFF))
#define MCF_FEC_IEEE_T_MACERR	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_IEEE_T_MACERR_OFF))
#define MCF_FEC_IEEE_T_CSERR	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_IEEE_T_CSERR_OFF))
#define MCF_FEC_IEEE_T_SQE	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                   MCF_FEC_IEEE_T_SQE_OFF))
#define MCF_FEC_IEEE_T_FDXFC	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_IEEE_T_FDXFC_OFF))
#define MCF_FEC_IEEE_T_OCTETS_OK  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_IEEE_T_OCTETS_OK_OFF))
#define MCF_FEC_RMON_R_PACKETS	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_R_PACKETS_OFF))
#define MCF_FEC_RMON_R_BC_PKT	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_R_BC_PKT_OFF))
#define MCF_FEC_RMON_R_MC_PKT	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_R_MC_PKT_OFF))
#define MCF_FEC_RMON_R_CRC_ALIGN  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_R_CRC_ALIGN_OFF))
#define MCF_FEC_RMON_R_UNDERSIZE  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_R_UNDERSIZE_OFF))
#define MCF_FEC_RMON_R_OVERSIZE	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_R_OVERSIZE_OFF))
#define MCF_FEC_RMON_R_FRAG	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_R_FRAG_OFF))
#define MCF_FEC_RMON_R_JAB	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_R_JAB_OFF))
#define MCF_FEC_RMON_R_RESVD_0	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_R_RESVD_0_OFF))
#define MCF_FEC_RMON_R_P64	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_R_P64_OFF))
#define MCF_FEC_RMON_R_P65TO127	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_R_P65TO127_OFF))
#define MCF_FEC_RMON_R_P128TO255  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_R_P128TO255_OFF))
#define MCF_FEC_RMON_R_P256TO511  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_R_P256TO511_OFF))
#define MCF_FEC_RMON_R_512TO1023  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_R_512TO1023_OFF))
#define MCF_FEC_RMON_R_P_GTE2048  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_R_P_GTE2048_OFF))
#define MCF_FEC_RMON_R_1024TO2047 (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_R_1024TO2047_OFF))
#define MCF_FEC_RMON_R_OCTETS	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_RMON_R_OCTETS_OFF))
#define MCF_FEC_IEEE_R_DROP	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_IEEE_R_DROP_OFF))
#define MCF_FEC_IEEE_R_FRAME_OK	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_IEEE_R_FRAME_OK_OFF))
#define MCF_FEC_IEEE_R_CRC	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_IEEE_R_CRC_OFF))
#define MCF_FEC_IEEE_R_ALIGN	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_IEEE_R_ALIGN_OFF))
#define MCF_FEC_IEEE_R_MACERR	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_IEEE_R_MACERR_OFF))
#define MCF_FEC_IEEE_R_FDXFC	  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_IEEE_R_FDXFC_OFF))
#define MCF_FEC_IEEE_R_OCTETS_OK  (CAST_MCF_VOLPTR( UINT32 )(MCF_FEC_BASE + \
                                    MCF_FEC_IEEE_R_OCTETS_OK_OFF))

/* Bit definitions and macros for MCF_FEC_EIR */
#define MCF_FEC_EIR_UN	        (0x00080000)
#define MCF_FEC_EIR_RL	        (0x00100000)
#define MCF_FEC_EIR_LC	        (0x00200000)
#define MCF_FEC_EIR_EBERR       (0x00400000)
#define MCF_FEC_EIR_MII	        (0x00800000)
#define MCF_FEC_EIR_RXB	        (0x01000000)
#define MCF_FEC_EIR_RXF	        (0x02000000)
#define MCF_FEC_EIR_TXB	        (0x04000000)
#define MCF_FEC_EIR_TXF	        (0x08000000)
#define MCF_FEC_EIR_GRA	        (0x10000000)
#define MCF_FEC_EIR_BABT        (0x20000000)
#define MCF_FEC_EIR_BABR        (0x40000000)
#define MCF_FEC_EIR_HBERR       (0x80000000)
#define MCF_FEC_EIR_CLEAR_ALL	(0xFFFFFFFF)

/* Bit definitions and macros for MCF_FEC_EIMR */
#define MCF_FEC_EIMR_UN	        (0x00080000)
#define MCF_FEC_EIMR_RL	        (0x00100000)
#define MCF_FEC_EIMR_LC	        (0x00200000)
#define MCF_FEC_EIMR_EBERR	(0x00400000)
#define MCF_FEC_EIMR_MII	(0x00800000)
#define MCF_FEC_EIMR_RXB	(0x01000000)
#define MCF_FEC_EIMR_RXF	(0x02000000)
#define MCF_FEC_EIMR_TXB	(0x04000000)
#define MCF_FEC_EIMR_TXF	(0x08000000)
#define MCF_FEC_EIMR_GRA	(0x10000000)
#define MCF_FEC_EIMR_BABT	(0x20000000)
#define MCF_FEC_EIMR_BABR	(0x40000000)
#define MCF_FEC_EIMR_HBERR	(0x80000000)
#define MCF_FEC_EIMR_MASK_ALL	(0x00000000)
#define MCF_FEC_EIMR_UNMASK_ALL	(0xFFFFFFFF)

/* Bit definitions and macros for MCF_FEC_RDAR */
#define MCF_FEC_RDAR_R_DES_ACTIVE	(0x01000000)

/* Bit definitions and macros for MCF_FEC_TDAR */
#define MCF_FEC_TDAR_X_DES_ACTIVE	(0x01000000)

/* Bit definitions and macros for MCF_FEC_ECR */
#define MCF_FEC_ECR_RESET	  (0x00000001)
#define MCF_FEC_ECR_ETHER_EN	  (0x00000002)

/* Bit definitions and macros for MCF_FEC_MMFR */
#define MCF_FEC_MMFR_DATA(x)	  (((x)&0x0000FFFF)<<0)
#define MCF_FEC_MMFR_TA(x)	  (((x)&0x00000003)<<16)
#define MCF_FEC_MMFR_RA(x)	  (((x)&0x0000001F)<<18)
#define MCF_FEC_MMFR_PA(x)	  (((x)&0x0000001F)<<23)
#define MCF_FEC_MMFR_OP(x)	  (((x)&0x00000003)<<28)
#define MCF_FEC_MMFR_ST(x)	  (((x)&0x00000003)<<30)
#define MCF_FEC_MMFR_ST_01	  (0x40000000)
#define MCF_FEC_MMFR_OP_READ	  (0x20000000)
#define MCF_FEC_MMFR_OP_WRITE	  (0x10000000)
#define MCF_FEC_MMFR_TA_10	  (0x00020000)

/* Bit definitions and macros for MCF_FEC_MSCR */
#define MCF_FEC_MSCR_MII_SPEED(x)	(((x)&0x0000003F)<<1)
#define MCF_FEC_MSCR_DIS_PREAMBLE	(0x00000080)

/* Bit definitions and macros for MCF_FEC_MIBC */
#define MCF_FEC_MIBC_MIB_IDLE		(0x40000000)
#define MCF_FEC_MIBC_MIB_DISABLE	(0x80000000)

/* Bit definitions and macros for MCF_FEC_RCR */
#define MCF_FEC_RCR_LOOP	  (0x00000001)
#define MCF_FEC_RCR_DRT	          (0x00000002)
#define MCF_FEC_RCR_MII_MODE	  (0x00000004)
#define MCF_FEC_RCR_PROM	  (0x00000008)
#define MCF_FEC_RCR_BC_REJ	  (0x00000010)
#define MCF_FEC_RCR_FCE	          (0x00000020)
#define MCF_FEC_RCR_MAX_FL(x)	  (((x)&0x000007FF)<<16)

/* Bit definitions and macros for MCF_FEC_TCR */
#define MCF_FEC_TCR_GTS	          (0x00000001)
#define MCF_FEC_TCR_HBC	          (0x00000002)
#define MCF_FEC_TCR_FDEN	  (0x00000004)
#define MCF_FEC_TCR_TFC_PAUSE	  (0x00000008)
#define MCF_FEC_TCR_RFC_PAUSE	  (0x00000010)

/* Bit definitions and macros for MCF_FEC_PALR */
#define MCF_FEC_PALR_PADDR1(x)	(((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_FEC_PAUR */
#define MCF_FEC_PAUR_TYPE(x)	  (((x)&0x0000FFFF)<<0)
#define MCF_FEC_PAUR_PADDR2(x)	(((x)&0x0000FFFF)<<16)

/* Bit definitions and macros for MCF_FEC_OPD */
#define MCF_FEC_OPD_PAUSE_DUR(x)	(((x)&0x0000FFFF)<<0)
#define MCF_FEC_OPD_OPCODE(x)		(((x)&0x0000FFFF)<<16)

/* Bit definitions and macros for MCF_FEC_IAUR */
#define MCF_FEC_IAUR_IADDR1(x)	(((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_FEC_IALR */
#define MCF_FEC_IALR_IADDR2(x)	(((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_FEC_GAUR */
#define MCF_FEC_GAUR_GADDR1(x)	(((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_FEC_GALR */
#define MCF_FEC_GALR_GADDR2(x)	(((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_FEC_TFWR */
#define MCF_FEC_TFWR_X_WMRK(x)	(((x)&0x00000003)<<0)

/* Bit definitions and macros for MCF_FEC_FRBR */
#define MCF_FEC_FRBR_R_BOUND(x)	(((x)&0x000000FF)<<2)

/* Bit definitions and macros for MCF_FEC_FRSR */
#define MCF_FEC_FRSR_R_FSTART(x)	(((x)&0x000000FF)<<2)

/* Bit definitions and macros for MCF_FEC_ERDSR */
#define MCF_FEC_ERDSR_R_DES_START(x)	(((x)&0x3FFFFFFF)<<2)

/* Bit definitions and macros for MCF_FEC_ETDSR */
#define MCF_FEC_ETDSR_X_DES_START(x)	(((x)&0x3FFFFFFF)<<2)

/* Bit definitions and macros for MCF_FEC_EMRBR */
#define MCF_FEC_EMRBR_R_BUF_SIZE(x)	(((x)&0x0000007F)<<4)



/* register offsets */

#endif

