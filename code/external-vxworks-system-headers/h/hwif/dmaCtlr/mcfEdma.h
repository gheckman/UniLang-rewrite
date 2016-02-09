/* mcfEdma.h - coldfire Enhanced Edma device header */

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

#ifndef __INCmcfEdmah
#define __INCmcfEdmah


/* register offsets */
#define MCF_EDMA_CR_OFF                     0x0000
#define MCF_EDMA_ES_OFF                     0x0004
#define MCF_EDMA_ERQ_OFF                    0x000E
#define MCF_EDMA_EEI_OFF                    0x0016
#define MCF_EDMA_SERQ_OFF                   0x0018
#define MCF_EDMA_CERQ_OFF                   0x0019
#define MCF_EDMA_SEEI_OFF                   0x001A
#define MCF_EDMA_CEEI_OFF                   0x001B
#define MCF_EDMA_CINT_OFF                   0x001C
#define MCF_EDMA_CERR_OFF                   0x001D
#define MCF_EDMA_SSRT_OFF                   0x001E
#define MCF_EDMA_CDNE_OFF                   0x001F
#define MCF_EDMA_INT_OFF                    0x0026
#define MCF_EDMA_ERR_OFF                    0x002E
#define MCF_EDMA_DCHPRI0_OFF                0x0100
#define MCF_EDMA_DCHPRI1_OFF                0x0101
#define MCF_EDMA_DCHPRI2_OFF                0x0102
#define MCF_EDMA_DCHPRI3_OFF                0x0103
#define MCF_EDMA_DCHPRI4_OFF                0x0104
#define MCF_EDMA_DCHPRI5_OFF                0x0105
#define MCF_EDMA_DCHPRI6_OFF                0x0106
#define MCF_EDMA_DCHPRI7_OFF                0x0107
#define MCF_EDMA_DCHPRI8_OFF                0x0108
#define MCF_EDMA_DCHPRI9_OFF                0x0109
#define MCF_EDMA_DCHPRI10_OFF               0x010A
#define MCF_EDMA_DCHPRI11_OFF               0x010B
#define MCF_EDMA_DCHPRI12_OFF               0x010C
#define MCF_EDMA_DCHPRI13_OFF               0x010D
#define MCF_EDMA_DCHPRI14_OFF               0x010E
#define MCF_EDMA_DCHPRI15_OFF               0x010F
#define MCF_EDMA_TCD0_SADDR_OFF             0x1000
#define MCF_EDMA_TCD1_SADDR_OFF             0x1020
#define MCF_EDMA_TCD2_SADDR_OFF             0x1040
#define MCF_EDMA_TCD3_SADDR_OFF             0x1060
#define MCF_EDMA_TCD4_SADDR_OFF             0x1080
#define MCF_EDMA_TCD5_SADDR_OFF             0x10A0
#define MCF_EDMA_TCD6_SADDR_OFF             0x10C0
#define MCF_EDMA_TCD7_SADDR_OFF             0x10E0
#define MCF_EDMA_TCD8_SADDR_OFF             0x1100
#define MCF_EDMA_TCD9_SADDR_OFF             0x1120
#define MCF_EDMA_TCD10_SADDR_OFF            0x1140
#define MCF_EDMA_TCD11_SADDR_OFF            0x1160
#define MCF_EDMA_TCD12_SADDR_OFF            0x1180
#define MCF_EDMA_TCD13_SADDR_OFF            0x11A0
#define MCF_EDMA_TCD14_SADDR_OFF            0x11C0
#define MCF_EDMA_TCD15_SADDR_OFF            0x11E0
#define MCF_EDMA_TCD0_ATTR_OFF              0x1004
#define MCF_EDMA_TCD1_ATTR_OFF              0x1024
#define MCF_EDMA_TCD2_ATTR_OFF              0x1044
#define MCF_EDMA_TCD3_ATTR_OFF              0x1064
#define MCF_EDMA_TCD4_ATTR_OFF              0x1084
#define MCF_EDMA_TCD5_ATTR_OFF              0x10A4
#define MCF_EDMA_TCD6_ATTR_OFF              0x10C4
#define MCF_EDMA_TCD7_ATTR_OFF              0x10E4
#define MCF_EDMA_TCD8_ATTR_OFF              0x1104
#define MCF_EDMA_TCD9_ATTR_OFF              0x1124
#define MCF_EDMA_TCD10_ATTR_OFF             0x1144
#define MCF_EDMA_TCD11_ATTR_OFF             0x1164
#define MCF_EDMA_TCD12_ATTR_OFF             0x1184
#define MCF_EDMA_TCD13_ATTR_OFF             0x11A4
#define MCF_EDMA_TCD14_ATTR_OFF             0x11C4
#define MCF_EDMA_TCD15_ATTR_OFF             0x11E4
#define MCF_EDMA_TCD0_SOFF_OFF              0x1006
#define MCF_EDMA_TCD1_SOFF_OFF              0x1026
#define MCF_EDMA_TCD2_SOFF_OFF              0x1046
#define MCF_EDMA_TCD3_SOFF_OFF              0x1066
#define MCF_EDMA_TCD4_SOFF_OFF              0x1086
#define MCF_EDMA_TCD5_SOFF_OFF              0x10A6
#define MCF_EDMA_TCD6_SOFF_OFF              0x10C6
#define MCF_EDMA_TCD7_SOFF_OFF              0x10E6
#define MCF_EDMA_TCD8_SOFF_OFF              0x1106
#define MCF_EDMA_TCD9_SOFF_OFF              0x1126
#define MCF_EDMA_TCD10_SOFF_OFF             0x1146
#define MCF_EDMA_TCD11_SOFF_OFF             0x1166
#define MCF_EDMA_TCD12_SOFF_OFF             0x1186
#define MCF_EDMA_TCD13_SOFF_OFF             0x11A6
#define MCF_EDMA_TCD14_SOFF_OFF             0x11C6
#define MCF_EDMA_TCD15_SOFF_OFF             0x11E6
#define MCF_EDMA_TCD0_NBYTES_OFF            0x1008
#define MCF_EDMA_TCD1_NBYTES_OFF            0x1028
#define MCF_EDMA_TCD2_NBYTES_OFF            0x1048
#define MCF_EDMA_TCD3_NBYTES_OFF            0x1068
#define MCF_EDMA_TCD4_NBYTES_OFF            0x1088
#define MCF_EDMA_TCD5_NBYTES_OFF            0x10A8
#define MCF_EDMA_TCD6_NBYTES_OFF            0x10C8
#define MCF_EDMA_TCD7_NBYTES_OFF            0x10E8
#define MCF_EDMA_TCD8_NBYTES_OFF            0x1108
#define MCF_EDMA_TCD9_NBYTES_OFF            0x1128
#define MCF_EDMA_TCD10_NBYTES_OFF           0x1148
#define MCF_EDMA_TCD11_NBYTES_OFF           0x15168
#define MCF_EDMA_TCD12_NBYTES_OFF           0x1188
#define MCF_EDMA_TCD13_NBYTES_OFF           0x11A8
#define MCF_EDMA_TCD14_NBYTES_OFF           0x11C8
#define MCF_EDMA_TCD15_NBYTES_OFF           0x11E8
#define MCF_EDMA_TCD0_SLAST_OFF             0x100C
#define MCF_EDMA_TCD1_SLAST_OFF             0x102C
#define MCF_EDMA_TCD2_SLAST_OFF             0x104C
#define MCF_EDMA_TCD3_SLAST_OFF             0x106C
#define MCF_EDMA_TCD4_SLAST_OFF             0x108C
#define MCF_EDMA_TCD5_SLAST_OFF             0x10AC
#define MCF_EDMA_TCD6_SLAST_OFF             0x10CC
#define MCF_EDMA_TCD7_SLAST_OFF             0x10EC
#define MCF_EDMA_TCD8_SLAST_OFF             0x110C
#define MCF_EDMA_TCD9_SLAST_OFF             0x112C
#define MCF_EDMA_TCD10_SLAST_OFF            0x114C
#define MCF_EDMA_TCD11_SLAST_OFF            0x116C
#define MCF_EDMA_TCD12_SLAST_OFF            0x118C
#define MCF_EDMA_TCD13_SLAST_OFF            0x11AC
#define MCF_EDMA_TCD14_SLAST_OFF            0x11CC
#define MCF_EDMA_TCD15_SLAST_OFF            0x11EC
#define MCF_EDMA_TCD0_DADDR_OFF             0x1010
#define MCF_EDMA_TCD1_DADDR_OFF             0x1030
#define MCF_EDMA_TCD2_DADDR_OFF             0x1050
#define MCF_EDMA_TCD3_DADDR_OFF             0x1070
#define MCF_EDMA_TCD4_DADDR_OFF             0x1090
#define MCF_EDMA_TCD5_DADDR_OFF             0x10B0
#define MCF_EDMA_TCD6_DADDR_OFF             0x10D0
#define MCF_EDMA_TCD7_DADDR_OFF             0x10F0
#define MCF_EDMA_TCD8_DADDR_OFF             0x1110
#define MCF_EDMA_TCD9_DADDR_OFF             0x1130
#define MCF_EDMA_TCD10_DADDR_OFF            0x1150
#define MCF_EDMA_TCD11_DADDR_OFF            0x1170
#define MCF_EDMA_TCD12_DADDR_OFF            0x1190
#define MCF_EDMA_TCD13_DADDR_OFF            0x11B0
#define MCF_EDMA_TCD14_DADDR_OFF            0x11D0
#define MCF_EDMA_TCD15_DADDR_OFF            0x11F0
#define MCF_EDMA_TCD0_CITER_OFF             0x1014
#define MCF_EDMA_TCD1_CITER_OFF             0x1034
#define MCF_EDMA_TCD2_CITER_OFF             0x1054
#define MCF_EDMA_TCD3_CITER_OFF             0x1074
#define MCF_EDMA_TCD4_CITER_OFF             0x1094
#define MCF_EDMA_TCD5_CITER_OFF             0x10B4
#define MCF_EDMA_TCD6_CITER_OFF             0x10D4
#define MCF_EDMA_TCD7_CITER_OFF             0x10F4
#define MCF_EDMA_TCD8_CITER_OFF             0x1114
#define MCF_EDMA_TCD9_CITER_OFF             0x1134
#define MCF_EDMA_TCD10_CITER_OFF            0x1154
#define MCF_EDMA_TCD11_CITER_OFF            0x1174
#define MCF_EDMA_TCD12_CITER_OFF            0x1194
#define MCF_EDMA_TCD13_CITER_OFF            0x11B4
#define MCF_EDMA_TCD14_CITER_OFF            0x11D4
#define MCF_EDMA_TCD15_CITER_OFF            0x11F4
#define MCF_EDMA_TCD0_CITER_ELINK_OFF       0x1014
#define MCF_EDMA_TCD1_CITER_ELINK_OFF       0x1034
#define MCF_EDMA_TCD2_CITER_ELINK_OFF       0x1054
#define MCF_EDMA_TCD3_CITER_ELINK_OFF       0x15074
#define MCF_EDMA_TCD4_CITER_ELINK_OFF       0x1094
#define MCF_EDMA_TCD5_CITER_ELINK_OFF       0x10B4
#define MCF_EDMA_TCD6_CITER_ELINK_OFF       0x10D4
#define MCF_EDMA_TCD7_CITER_ELINK_OFF       0x10F4
#define MCF_EDMA_TCD8_CITER_ELINK_OFF       0x1114
#define MCF_EDMA_TCD9_CITER_ELINK_OFF       0x1134
#define MCF_EDMA_TCD10_CITER_ELINK_OFF      0x1154
#define MCF_EDMA_TCD11_CITER_ELINK_OFF      0x1174
#define MCF_EDMA_TCD12_CITER_ELINK_OFF      0x1194
#define MCF_EDMA_TCD13_CITER_ELINK_OFF      0x11B4
#define MCF_EDMA_TCD14_CITER_ELINK_OFF      0x11D4
#define MCF_EDMA_TCD15_CITER_ELINK_OFF      0x11F4
#define MCF_EDMA_TCD0_DOFF_OFF              0x1016
#define MCF_EDMA_TCD1_DOFF_OFF              0x1036
#define MCF_EDMA_TCD2_DOFF_OFF              0x1056
#define MCF_EDMA_TCD3_DOFF_OFF              0x1076
#define MCF_EDMA_TCD4_DOFF_OFF              0x1096
#define MCF_EDMA_TCD5_DOFF_OFF              0x10B6
#define MCF_EDMA_TCD6_DOFF_OFF              0x10D6
#define MCF_EDMA_TCD7_DOFF_OFF              0x10F6
#define MCF_EDMA_TCD8_DOFF_OFF              0x1116
#define MCF_EDMA_TCD9_DOFF_OFF              0x1136
#define MCF_EDMA_TCD10_DOFF_OFF             0x1156
#define MCF_EDMA_TCD11_DOFF_OFF             0x1176
#define MCF_EDMA_TCD12_DOF_OFF              0x1196
#define MCF_EDMA_TCD13_DOFF_OFF             0x11B6
#define MCF_EDMA_TCD14_DOFF_OFF             0x11D6
#define MCF_EDMA_TCD15_DOFF_OFF             0x11F6
#define MCF_EDMA_TCD0_DLAST_SGA_OFF         0x1018
#define MCF_EDMA_TCD1_DLAST_SGA_OFF         0x1038
#define MCF_EDMA_TCD2_DLAST_SGA_OFF         0x1058
#define MCF_EDMA_TCD3_DLAST_SGA_OFF         0x1078
#define MCF_EDMA_TCD4_DLAST_SGA_OFF         0x1098
#define MCF_EDMA_TCD5_DLAST_SGA_OFF         0x10B8
#define MCF_EDMA_TCD6_DLAST_SGA_OFF         0x10D8
#define MCF_EDMA_TCD7_DLAST_SGA_OFF         0x10F8
#define MCF_EDMA_TCD8_DLAST_SGA_OFF         0x1118
#define MCF_EDMA_TCD9_DLAST_SGA_OFF         0x1138
#define MCF_EDMA_TCD10_DLAST_SGA_OFF        0x1158
#define MCF_EDMA_TCD11_DLAST_SGA_OFF        0x1178
#define MCF_EDMA_TCD12_DLAST_SGA_OFF        0x1198
#define MCF_EDMA_TCD13_DLAST_SGA_OFF        0x11B8
#define MCF_EDMA_TCD14_DLAST_SGA_OFF        0x11D8
#define MCF_EDMA_TCD15_DLAST_SGA_OFF        0x11F8
#define MCF_EDMA_TCD0_BITER_OFF             0x101C
#define MCF_EDMA_TCD1_BITER_OFF             0x103C
#define MCF_EDMA_TCD2_BITER_OFF             0x105C
#define MCF_EDMA_TCD3_BITER_OFF             0x107C
#define MCF_EDMA_TCD4_BITER_OFF             0x109C
#define MCF_EDMA_TCD5_BITER_OFF             0x10BC
#define MCF_EDMA_TCD6_BITER_OFF             0x10DC
#define MCF_EDMA_TCD7_BITER_OFF             0x10FC
#define MCF_EDMA_TCD8_BITER_OFF             0x111C
#define MCF_EDMA_TCD9_BITER_OFF             0x113C
#define MCF_EDMA_TCD10_BITER_OFF            0x115C
#define MCF_EDMA_TCD11_BITER_OFF            0x117C
#define MCF_EDMA_TCD12_BITER_OFF            0x119C
#define MCF_EDMA_TCD13_BITER_OFF            0x11BC
#define MCF_EDMA_TCD14_BITER_OFF            0x11DC
#define MCF_EDMA_TCD15_BITER_OFF            0x11FC
#define MCF_EDMA_TCD0_BITER_ELINK_OFF       0x101C
#define MCF_EDMA_TCD1_BITER_ELINK_OFF       0x103C
#define MCF_EDMA_TCD2_BITER_ELINK_OFF       0x105C
#define MCF_EDMA_TCD3_BITER_ELINK_OFF       0x107C
#define MCF_EDMA_TCD4_BITER_ELINK_OFF       0x109C
#define MCF_EDMA_TCD5_BITER_ELINK_OFF       0x10BC
#define MCF_EDMA_TCD6_BITER_ELINK_OFF       0x10DC
#define MCF_EDMA_TCD7_BITER_ELINK_OFF       0x10FC
#define MCF_EDMA_TCD8_BITER_ELINK_OFF       0x111C
#define MCF_EDMA_TCD9_BITER_ELINK_OFF       0x113C
#define MCF_EDMA_TCD10_BITER_ELINK_OFF      0x115C
#define MCF_EDMA_TCD11_BITER_ELINK_OFF      0x117C
#define MCF_EDMA_TCD12_BITER_ELINK_OFF      0x119C
#define MCF_EDMA_TCD13_BITER_ELINK_OFF      0x11BC
#define MCF_EDMA_TCD14_BITER_ELINK_OFF      0x11DC
#define MCF_EDMA_TCD15_BITER_ELINK_OFF      0x11FC
#define MCF_EDMA_TCD0_CSR_OFF               0x101E
#define MCF_EDMA_TCD1_CSR_OFF               0x103E
#define MCF_EDMA_TCD2_CSR_OFF               0x105E
#define MCF_EDMA_TCD3_CSR_OFF               0x107E
#define MCF_EDMA_TCD4_CSR_OFF               0x109E
#define MCF_EDMA_TCD5_CSR_OFF               0x10BE
#define MCF_EDMA_TCD6_CSR_OFF               0x10DE
#define MCF_EDMA_TCD7_CSR_OFF               0x10FE
#define MCF_EDMA_TCD8_CSR_OFF               0x111E
#define MCF_EDMA_TCD9_CSR_OFF               0x113E
#define MCF_EDMA_TCD10_CSR_OFF              0x115E
#define MCF_EDMA_TCD11_CSR_OFF              0x117E
#define MCF_EDMA_TCD12_CSR_OFF              0x119E
#define MCF_EDMA_TCD13_CSR_OFF              0x11BE
#define MCF_EDMA_TCD14_CSR_OFF              0x11DE
#define MCF_EDMA_TCD15_CSR_OFF              0x11FE

/* Register read/write macros */

#define MCF_EDMA_CR		(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_CR_OFF))
#define MCF_EDMA_ES		(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_ES_OFF))
#define MCF_EDMA_ERQ		(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_ERQ_OFF))
#define MCF_EDMA_EEI		(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_EEI_OFF))
#define MCF_EDMA_SERQ		(CAST_MCF_VOLPTR( UINT8 )(MCF_EDMA_BASE \
                                + MCF_EDMA_SERQ_OFF))
#define MCF_EDMA_CERQ		(CAST_MCF_VOLPTR( UINT8 )(MCF_EDMA_BASE \
                                + MCF_EDMA_CERQ_OFF))
#define MCF_EDMA_SEEI		(CAST_MCF_VOLPTR( UINT8 )(MCF_EDMA_BASE \
                                + MCF_EDMA_SEEI_OFF))
#define MCF_EDMA_CEEI		(CAST_MCF_VOLPTR( UINT8 )(MCF_EDMA_BASE \
                                + MCF_EDMA_CEEI_OFF))
#define MCF_EDMA_CINT		(CAST_MCF_VOLPTR( UINT8 )(MCF_EDMA_BASE \
                                + MCF_EDMA_CINT_OFF))
#define MCF_EDMA_CERR		(CAST_MCF_VOLPTR( UINT8 )(MCF_EDMA_BASE \
                                + MCF_EDMA_CERR_OFF))
#define MCF_EDMA_SSRT		(CAST_MCF_VOLPTR( UINT8 )(MCF_EDMA_BASE \
                                + MCF_EDMA_SSRT_OFF))
#define MCF_EDMA_CDNE		(CAST_MCF_VOLPTR( UINT8 )(MCF_EDMA_BASE \
                                + MCF_EDMA_CDNE_OFF))
#define MCF_EDMA_INT		(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_INT_OFF))
#define MCF_EDMA_ERR		(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_ERR_OFF))
#define MCF_EDMA_DCHPRI0	(CAST_MCF_VOLPTR( UINT8 )(MCF_EDMA_BASE \
                                + MCF_EDMA_DCHPRI0_OFF))
#define MCF_EDMA_DCHPRI1	(CAST_MCF_VOLPTR( UINT8 )(MCF_EDMA_BASE \
                                + MCF_EDMA_DCHPRI1_OFF))
#define MCF_EDMA_DCHPRI2	(CAST_MCF_VOLPTR( UINT8 )(MCF_EDMA_BASE \
                                + MCF_EDMA_DCHPRI2_OFF))
#define MCF_EDMA_DCHPRI3	(CAST_MCF_VOLPTR( UINT8 )(MCF_EDMA_BASE \
                                + MCF_EDMA_DCHPRI3_OFF))
#define MCF_EDMA_DCHPRI4	(CAST_MCF_VOLPTR( UINT8 )(MCF_EDMA_BASE \
                                + MCF_EDMA_DCHPRI4_OFF))
#define MCF_EDMA_DCHPRI5	(CAST_MCF_VOLPTR( UINT8 )(MCF_EDMA_BASE \
                                + MCF_EDMA_DCHPRI5_OFF))
#define MCF_EDMA_DCHPRI6	(CAST_MCF_VOLPTR( UINT8 )(MCF_EDMA_BASE \
                                + MCF_EDMA_DCHPRI6_OFF))
#define MCF_EDMA_DCHPRI7	(CAST_MCF_VOLPTR( UINT8 )(MCF_EDMA_BASE \
                                + MCF_EDMA_DCHPRI7_OFF))
#define MCF_EDMA_DCHPRI8	(CAST_MCF_VOLPTR( UINT8 )(MCF_EDMA_BASE \
                                + MCF_EDMA_DCHPRI8_OFF))
#define MCF_EDMA_DCHPRI9	(CAST_MCF_VOLPTR( UINT8 )(MCF_EDMA_BASE \
                                + MCF_EDMA_DCHPRI9_OFF))
#define MCF_EDMA_DCHPRI10	(CAST_MCF_VOLPTR( UINT8 )(MCF_EDMA_BASE \
                                + MCF_EDMA_DCHPRI10_OFF))
#define MCF_EDMA_DCHPRI11	(CAST_MCF_VOLPTR( UINT8 )(MCF_EDMA_BASE \
                                + MCF_EDMA_DCHPRI11_OFF))
#define MCF_EDMA_DCHPRI12	(CAST_MCF_VOLPTR( UINT8 )(MCF_EDMA_BASE \
                                + MCF_EDMA_DCHPRI12_OFF))
#define MCF_EDMA_DCHPRI13	(CAST_MCF_VOLPTR( UINT8 )(MCF_EDMA_BASE \
                                + MCF_EDMA_DCHPRI13_OFF))
#define MCF_EDMA_DCHPRI14	(CAST_MCF_VOLPTR( UINT8 )(MCF_EDMA_BASE \
                                + MCF_EDMA_DCHPRI14_OFF))
#define MCF_EDMA_DCHPRI15	(CAST_MCF_VOLPTR( UINT8 )(MCF_EDMA_BASE \
                                + MCF_EDMA_DCHPRI15_OFF))
#define MCF_EDMA_TCD0_SADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD0_SADDR_OFF))
#define MCF_EDMA_TCD1_SADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD1_SADDR_OFF))
#define MCF_EDMA_TCD2_SADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD2_SADDR_OFF))
#define MCF_EDMA_TCD3_SADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD3_SADDR_OFF))
#define MCF_EDMA_TCD4_SADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD4_SADDR_OFF))
#define MCF_EDMA_TCD5_SADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD5_SADDR_OFF))
#define MCF_EDMA_TCD6_SADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD6_SADDR_OFF))
#define MCF_EDMA_TCD7_SADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD7_SADDR_OFF))
#define MCF_EDMA_TCD8_SADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD8_SADDR_OFF))
#define MCF_EDMA_TCD9_SADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD9_SADDR_OFF))
#define MCF_EDMA_TCD10_SADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD10_SADDR_OFF))
#define MCF_EDMA_TCD11_SADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD11_SADDR_OFF))
#define MCF_EDMA_TCD12_SADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD12_SADDR_OFF))
#define MCF_EDMA_TCD13_SADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD13_SADDR_OFF))
#define MCF_EDMA_TCD14_SADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD14_SADDR_OFF))
#define MCF_EDMA_TCD15_SADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD15_SADDR_OFF))
#define MCF_EDMA_TCD0_ATTR	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD0_ATTR_OFF))
#define MCF_EDMA_TCD1_ATTR	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD1_ATTR_OFF))
#define MCF_EDMA_TCD2_ATTR	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD2_ATTR_OFF))
#define MCF_EDMA_TCD3_ATTR	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD3_ATTR_OFF))
#define MCF_EDMA_TCD4_ATTR	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD4_ATTR_OFF))
#define MCF_EDMA_TCD5_ATTR	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD5_ATTR_OFF))
#define MCF_EDMA_TCD6_ATTR	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD6_ATTR_OFF))
#define MCF_EDMA_TCD7_ATTR	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD7_ATTR_OFF))
#define MCF_EDMA_TCD8_ATTR	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD8_ATTR_OFF))
#define MCF_EDMA_TCD9_ATTR	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD9_ATTR_OFF))
#define MCF_EDMA_TCD10_ATTR	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD10_ATTR_OFF))
#define MCF_EDMA_TCD11_ATTR	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD11_ATTR_OFF))
#define MCF_EDMA_TCD12_ATTR	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD12_ATTR_OFF))
#define MCF_EDMA_TCD13_ATTR	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD13_ATTR_OFF))
#define MCF_EDMA_TCD14_ATTR	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD14_ATTR_OFF))
#define MCF_EDMA_TCD15_ATTR	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD15_ATTR_OFF))
#define MCF_EDMA_TCD0_SOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD0_SOFF_OFF))
#define MCF_EDMA_TCD1_SOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD1_SOFF_OFF))
#define MCF_EDMA_TCD2_SOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD2_SOFF_OFF))
#define MCF_EDMA_TCD3_SOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD3_SOFF_OFF))
#define MCF_EDMA_TCD4_SOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD4_SOFF_OFF))
#define MCF_EDMA_TCD5_SOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD5_SOFF_OFF))
#define MCF_EDMA_TCD6_SOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD6_SOFF_OFF))
#define MCF_EDMA_TCD7_SOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD7_SOFF_OFF))
#define MCF_EDMA_TCD8_SOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD8_SOFF_OFF))
#define MCF_EDMA_TCD9_SOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD9_SOFF_OFF))
#define MCF_EDMA_TCD10_SOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD10_SOFF_OFF))
#define MCF_EDMA_TCD11_SOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD11_SOFF_OFF))
#define MCF_EDMA_TCD12_SOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD12_SOFF_OFF))
#define MCF_EDMA_TCD13_SOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD13_SOFF_OFF))
#define MCF_EDMA_TCD14_SOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD14_SOFF_OFF))
#define MCF_EDMA_TCD15_SOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD15_SOFF_OFF))
#define MCF_EDMA_TCD0_NBYTES	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD0_NBYTES_OFF))
#define MCF_EDMA_TCD1_NBYTES	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD1_NBYTES_OFF))
#define MCF_EDMA_TCD2_NBYTES	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD2_NBYTES_OFF))
#define MCF_EDMA_TCD3_NBYTES	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD3_NBYTES_OFF))
#define MCF_EDMA_TCD4_NBYTES	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD4_NBYTES_OFF))
#define MCF_EDMA_TCD5_NBYTES	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD5_NBYTES_OFF))
#define MCF_EDMA_TCD6_NBYTES	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD6_NBYTES_OFF))
#define MCF_EDMA_TCD7_NBYTES	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD7_NBYTES_OFF))
#define MCF_EDMA_TCD8_NBYTES	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD8_NBYTES_OFF))
#define MCF_EDMA_TCD9_NBYTES	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD9_NBYTES_OFF))
#define MCF_EDMA_TCD10_NBYTES	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD10_NBYTES_OFF))
#define MCF_EDMA_TCD11_NBYTES	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD11_NBYTES_OFF))
#define MCF_EDMA_TCD12_NBYTES	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD12_NBYTES_OFF))
#define MCF_EDMA_TCD13_NBYTES	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD13_NBYTES_OFF))
#define MCF_EDMA_TCD14_NBYTES	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD14_NBYTES_OFF))
#define MCF_EDMA_TCD15_NBYTES	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD15_NBYTES_OFF))
#define MCF_EDMA_TCD0_SLAST	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD0_SLAST_OFF))
#define MCF_EDMA_TCD1_SLAST	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD1_SLAST_OFF))
#define MCF_EDMA_TCD2_SLAST	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD2_SLAST_OFF))
#define MCF_EDMA_TCD3_SLAST	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD3_SLAST_OFF))
#define MCF_EDMA_TCD4_SLAST	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD4_SLAST_OFF))
#define MCF_EDMA_TCD5_SLAST	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD5_SLAST_OFF))
#define MCF_EDMA_TCD6_SLAST	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD6_SLAST_OFF))
#define MCF_EDMA_TCD7_SLAST	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD7_SLAST_OFF))
#define MCF_EDMA_TCD8_SLAST	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD8_SLAST_OFF))
#define MCF_EDMA_TCD9_SLAST	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD9_SLAST_OFF))
#define MCF_EDMA_TCD10_SLAST	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD10_SLAST_OFF))
#define MCF_EDMA_TCD11_SLAST	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD11_SLAST_OFF))
#define MCF_EDMA_TCD12_SLAST	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD12_SLAST_OFF))
#define MCF_EDMA_TCD13_SLAST	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD13_SLAST_OFF))
#define MCF_EDMA_TCD14_SLAST	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD14_SLAST_OFF))
#define MCF_EDMA_TCD15_SLAST	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD15_SLAST_OFF))
#define MCF_EDMA_TCD0_DADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD0_DADDR_OFF))
#define MCF_EDMA_TCD1_DADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD1_DADDR_OFF))
#define MCF_EDMA_TCD2_DADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD2_DADDR_OFF))
#define MCF_EDMA_TCD3_DADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD3_DADDR_OFF))
#define MCF_EDMA_TCD4_DADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD4_DADDR_OFF))
#define MCF_EDMA_TCD5_DADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD5_DADDR_OFF))
#define MCF_EDMA_TCD6_DADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD6_DADDR_OFF))
#define MCF_EDMA_TCD7_DADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD7_DADDR_OFF))
#define MCF_EDMA_TCD8_DADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD8_DADDR_OFF))
#define MCF_EDMA_TCD9_DADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD9_DADDR_OFF))
#define MCF_EDMA_TCD10_DADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD10_DADDR_OFF))
#define MCF_EDMA_TCD11_DADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD11_DADDR_OFF))
#define MCF_EDMA_TCD12_DADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD12_DADDR_OFF))
#define MCF_EDMA_TCD13_DADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD13_DADDR_OFF))
#define MCF_EDMA_TCD14_DADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD14_DADDR_OFF))
#define MCF_EDMA_TCD15_DADDR	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD15_DADDR_OFF))
#define MCF_EDMA_TCD0_CITER	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD0_CITER_OFF))
#define MCF_EDMA_TCD1_CITER	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD1_CITER_OFF))
#define MCF_EDMA_TCD2_CITER	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD2_CITER_OFF))
#define MCF_EDMA_TCD3_CITER	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD3_CITER_OFF))
#define MCF_EDMA_TCD4_CITER	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD4_CITER_OFF))
#define MCF_EDMA_TCD5_CITER	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD5_CITER_OFF))
#define MCF_EDMA_TCD6_CITER	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD6_CITER_OFF))
#define MCF_EDMA_TCD7_CITER	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD7_CITER_OFF))
#define MCF_EDMA_TCD8_CITER	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD8_CITER_OFF))
#define MCF_EDMA_TCD9_CITER	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD9_CITER_OFF))
#define MCF_EDMA_TCD10_CITER	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD10_CITER_OFF))
#define MCF_EDMA_TCD11_CITER	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD11_CITER_OFF))
#define MCF_EDMA_TCD12_CITER	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD12_CITER_OFF))
#define MCF_EDMA_TCD13_CITER	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD13_CITER_OFF))
#define MCF_EDMA_TCD14_CITER	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD14_CITER_OFF))
#define MCF_EDMA_TCD15_CITER	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD15_CITER_OFF))
#define MCF_EDMA_TCD0_CITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD0_CITER_ELINK_OFF))
#define MCF_EDMA_TCD1_CITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD1_CITER_ELINK_OFF))
#define MCF_EDMA_TCD2_CITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD2_CITER_ELINK_OFF))
#define MCF_EDMA_TCD3_CITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD3_CITER_ELINK_OFF))
#define MCF_EDMA_TCD4_CITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD4_CITER_ELINK_OFF))
#define MCF_EDMA_TCD5_CITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD5_CITER_ELINK_OFF))
#define MCF_EDMA_TCD6_CITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD6_CITER_ELINK_OFF))
#define MCF_EDMA_TCD7_CITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD7_CITER_ELINK_OFF))
#define MCF_EDMA_TCD8_CITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD8_CITER_ELINK_OFF))
#define MCF_EDMA_TCD9_CITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD9_CITER_ELINK_OFF))
#define MCF_EDMA_TCD10_CITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD10_CITER_ELINK_OFF))
#define MCF_EDMA_TCD11_CITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD11_CITER_ELINK_OFF))
#define MCF_EDMA_TCD12_CITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD12_CITER_ELINK_OFF))
#define MCF_EDMA_TCD13_CITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD13_CITER_ELINK_OFF))
#define MCF_EDMA_TCD14_CITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD14_CITER_ELINK_OFF))
#define MCF_EDMA_TCD15_CITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD15_CITER_ELINK_OFF))
#define MCF_EDMA_TCD0_DOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD0_DOFF_OFF))
#define MCF_EDMA_TCD1_DOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD1_DOFF_OFF))
#define MCF_EDMA_TCD2_DOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD2_DOFF_OFF))
#define MCF_EDMA_TCD3_DOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD3_DOFF_OFF))
#define MCF_EDMA_TCD4_DOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD4_DOFF_OFF))
#define MCF_EDMA_TCD5_DOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD5_DOFF_OFF))
#define MCF_EDMA_TCD6_DOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD6_DOFF_OFF))
#define MCF_EDMA_TCD7_DOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD7_DOFF_OFF))
#define MCF_EDMA_TCD8_DOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD8_DOFF_OFF))
#define MCF_EDMA_TCD9_DOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD9_DOFF_OFF))
#define MCF_EDMA_TCD10_DOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD10_DOFF_OFF))
#define MCF_EDMA_TCD11_DOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD11_DOFF_OFF))
#define MCF_EDMA_TCD12_DOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD12_DOFF_OFF))
#define MCF_EDMA_TCD13_DOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD13_DOFF_OFF))
#define MCF_EDMA_TCD14_DOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD14_DOFF_OFF))
#define MCF_EDMA_TCD15_DOFF	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD15_DOFF_OFF))
#define MCF_EDMA_TCD0_DLAST_SGA	 (CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD0_DLAST_SGA_OFF))
#define MCF_EDMA_TCD1_DLAST_SGA	 (CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD1_DLAST_SGA_OFF))
#define MCF_EDMA_TCD2_DLAST_SGA	 (CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD2_DLAST_SGA_OFF))
#define MCF_EDMA_TCD3_DLAST_SGA	 (CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD3_DLAST_SGA_OFF))
#define MCF_EDMA_TCD4_DLAST_SGA	 (CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD4_DLAST_SGA_OFF))
#define MCF_EDMA_TCD5_DLAST_SGA	 (CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD5_DLAST_SGA_OFF))
#define MCF_EDMA_TCD6_DLAST_SGA	 (CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD6_DLAST_SGA_OFF))
#define MCF_EDMA_TCD7_DLAST_SGA	 (CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD7_DLAST_SGA_OFF))
#define MCF_EDMA_TCD8_DLAST_SGA	 (CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD8_DLAST_SGA_OFF))
#define MCF_EDMA_TCD9_DLAST_SGA	 (CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD9_DLAST_SGA_OFF))
#define MCF_EDMA_TCD10_DLAST_SGA (CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD10_DLAST_SGA_OFF))
#define MCF_EDMA_TCD11_DLAST_SGA (CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD11_DLAST_SGA_OFF))
#define MCF_EDMA_TCD12_DLAST_SGA (CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD12_DLAST_SGA_OFF))
#define MCF_EDMA_TCD13_DLAST_SGA (CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD13_DLAST_SGA_OFF))
#define MCF_EDMA_TCD14_DLAST_SGA (CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD14_DLAST_SGA_OFF))
#define MCF_EDMA_TCD15_DLAST_SGA (CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD15_DLAST_SGA_OFF))
#define MCF_EDMA_TCD0_BITER	 (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD0_BITER_OFF))
#define MCF_EDMA_TCD1_BITER	 (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD1_BITER_OFF))
#define MCF_EDMA_TCD2_BITER	 (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD2_BITER_OFF))
#define MCF_EDMA_TCD3_BITER	 (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD3_BITER_OFF))
#define MCF_EDMA_TCD4_BITER	 (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD4_BITER_OFF))
#define MCF_EDMA_TCD5_BITER	 (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD5_BITER_OFF))
#define MCF_EDMA_TCD6_BITER	 (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD6_BITER_OFF))
#define MCF_EDMA_TCD7_BITER	 (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD7_BITER_OFF))
#define MCF_EDMA_TCD8_BITER	 (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD8_BITER_OFF))
#define MCF_EDMA_TCD9_BITER	 (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD9_BITER_OFF))
#define MCF_EDMA_TCD10_BITER	 (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD10_BITER_OFF))
#define MCF_EDMA_TCD11_BITER	 (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD11_BITER_OFF))
#define MCF_EDMA_TCD12_BITER	 (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD12_BITER_OFF))
#define MCF_EDMA_TCD13_BITER	 (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD13_BITER_OFF))
#define MCF_EDMA_TCD14_BITER	 (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD14_BITER_OFF))
#define MCF_EDMA_TCD15_BITER	 (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD15_BITER_OFF))
#define MCF_EDMA_TCD0_BITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD0_BITER_ELINK_OFF))
#define MCF_EDMA_TCD1_BITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD1_BITER_ELINK_OFF))
#define MCF_EDMA_TCD2_BITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD2_BITER_ELINK_OFF))
#define MCF_EDMA_TCD3_BITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD3_BITER_ELINK_OFF))
#define MCF_EDMA_TCD4_BITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD4_BITER_ELINK_OFF))
#define MCF_EDMA_TCD5_BITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD5_BITER_ELINK_OFF))
#define MCF_EDMA_TCD6_BITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD6_BITER_ELINK_OFF))
#define MCF_EDMA_TCD7_BITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD7_BITER_ELINK_OFF))
#define MCF_EDMA_TCD8_BITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD8_BITER_ELINK_OFF))
#define MCF_EDMA_TCD9_BITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD9_BITER_ELINK_OFF))
#define MCF_EDMA_TCD10_BITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD10_BITER_ELINK_OFF))
#define MCF_EDMA_TCD11_BITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD11_BITER_ELINK_OFF))
#define MCF_EDMA_TCD12_BITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD12_BITER_ELINK_OFF))
#define MCF_EDMA_TCD13_BITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD13_BITER_ELINK_OFF))
#define MCF_EDMA_TCD14_BITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD14_BITER_ELINK_OFF))
#define MCF_EDMA_TCD15_BITER_ELINK (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD15_BITER_ELINK_OFF))
#define MCF_EDMA_TCD0_CSR         (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD0_CSR_OFF))
#define MCF_EDMA_TCD1_CSR         (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD1_CSR_OFF))
#define MCF_EDMA_TCD2_CSR         (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD2_CSR_OFF))
#define MCF_EDMA_TCD3_CSR         (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD3_CSR_OFF))
#define MCF_EDMA_TCD4_CSR         (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD4_CSR_OFF))
#define MCF_EDMA_TCD5_CSR         (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD5_CSR_OFF))
#define MCF_EDMA_TCD6_CSR         (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD6_CSR_OFF))
#define MCF_EDMA_TCD7_CSR         (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD7_CSR_OFF))
#define MCF_EDMA_TCD8_CSR         (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD8_CSR_OFF))
#define MCF_EDMA_TCD9_CSR         (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD9_CSR_OFF))
#define MCF_EDMA_TCD10_CSR	 (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD10_CSR_OFF))
#define MCF_EDMA_TCD11_CSR	 (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD11_CSR_OFF))
#define MCF_EDMA_TCD12_CSR	 (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD12_CSR_OFF))
#define MCF_EDMA_TCD13_CSR	 (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD13_CSR_OFF))
#define MCF_EDMA_TCD14_CSR	 (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD14_CSR_OFF))
#define MCF_EDMA_TCD15_CSR	 (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD15_CSR_OFF))

#define MCF_EDMA_TCD_ATTR(x)	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD0_ATTR_OFF+((x)*0x020)))
#define MCF_EDMA_DCHPRI(x)	(CAST_MCF_VOLPTR( UINT8 )(MCF_EDMA_BASE \
                                + MCF_EDMA_DCHPRI0_OFF+((x)*0x001)))
#define MCF_EDMA_TCD_SADDR(x)	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD0_SADDR_OFF+((x)*0x020)))
#define MCF_EDMA_TCD_SOFF(x)	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD0_SOFF_OFF+((x)*0x020)))
#define MCF_EDMA_TCD_NBYTES(x)	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD0_NBYTES_OFF+((x)*0x020)))
#define MCF_EDMA_TCD_SLAST(x)	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD0_SLAST_OFF+((x)*0x020)))
#define MCF_EDMA_TCD_DADDR(x)	(CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD0_DADDR_OFF+((x)*0x020)))
#define MCF_EDMA_TCD_CITER(x)	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD0_CITER_OFF+((x)*0x020)))
#define MCF_EDMA_TCD_CITER_ELINK(x) (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD0_CITER_ELINK_OFF+((x)*0x020)))
#define MCF_EDMA_TCD_DOFF(x)	(CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD0_DOFF_OFF+((x)*0x020)))
#define MCF_EDMA_TCD_DLAST_SGA(x) (CAST_MCF_VOLPTR( UINT32 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD0_DLAST_SGA_OFF+((x)*0x020)))
#define MCF_EDMA_TCD_BITER(x)	 (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD0_BITER_OFF+((x)*0x020)))
#define MCF_EDMA_TCD_BITER_ELINK(x) (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD0_BITER_ELINK_OFF+((x)*0x020)))
#define MCF_EDMA_TCD_CSR(x)  (CAST_MCF_VOLPTR( UINT16 )(MCF_EDMA_BASE \
                                + MCF_EDMA_TCD0_CSR_OFF+((x)*0x020)))

/* Bit definitions and macros for MCF_EDMA_CR */
#define MCF_EDMA_CR_EDBG	   (0x00000002)
#define MCF_EDMA_CR_ERCA	   (0x00000004)

/* Bit definitions and macros for MCF_EDMA_ES */
#define MCF_EDMA_ES_DBE	                (0x00000001)
#define MCF_EDMA_ES_SBE	                (0x00000002)
#define MCF_EDMA_ES_SGE	                (0x00000004)
#define MCF_EDMA_ES_NCE	                (0x00000008)
#define MCF_EDMA_ES_DOE	                (0x00000010)
#define MCF_EDMA_ES_DAE	                (0x00000020)
#define MCF_EDMA_ES_SOE	                (0x00000040)
#define MCF_EDMA_ES_SAE	                (0x00000080)
#define MCF_EDMA_ES_ERRCHN(x)		(((x)&0x0000000F)<<8)
#define MCF_EDMA_ES_CPE	                (0x00004000)
#define MCF_EDMA_ES_VLD	                (0x80000000)

/* Bit definitions and macros for MCF_EDMA_ERQ */
#define MCF_EDMA_ERQ_ERQ0	   (0x0001)
#define MCF_EDMA_ERQ_ERQ1	   (0x0002)
#define MCF_EDMA_ERQ_ERQ2	   (0x0004)
#define MCF_EDMA_ERQ_ERQ3	   (0x0008)
#define MCF_EDMA_ERQ_ERQ4	   (0x0010)
#define MCF_EDMA_ERQ_ERQ5	   (0x0020)
#define MCF_EDMA_ERQ_ERQ6	   (0x0040)
#define MCF_EDMA_ERQ_ERQ7	   (0x0080)
#define MCF_EDMA_ERQ_ERQ8	   (0x0100)
#define MCF_EDMA_ERQ_ERQ9	   (0x0200)
#define MCF_EDMA_ERQ_ERQ10	   (0x0400)
#define MCF_EDMA_ERQ_ERQ11	   (0x0800)
#define MCF_EDMA_ERQ_ERQ12	   (0x1000)
#define MCF_EDMA_ERQ_ERQ13	   (0x2000)
#define MCF_EDMA_ERQ_ERQ14	   (0x4000)
#define MCF_EDMA_ERQ_ERQ15	   (0x8000)

/* Bit definitions and macros for MCF_EDMA_EEI */
#define MCF_EDMA_EEI_EEI0	   (0x0001)
#define MCF_EDMA_EEI_EEI1	   (0x0002)
#define MCF_EDMA_EEI_EEI2	   (0x0004)
#define MCF_EDMA_EEI_EEI3	   (0x0008)
#define MCF_EDMA_EEI_EEI4	   (0x0010)
#define MCF_EDMA_EEI_EEI5	   (0x0020)
#define MCF_EDMA_EEI_EEI6	   (0x0040)
#define MCF_EDMA_EEI_EEI7	   (0x0080)
#define MCF_EDMA_EEI_EEI8	   (0x0100)
#define MCF_EDMA_EEI_EEI9	   (0x0200)
#define MCF_EDMA_EEI_EEI10	   (0x0400)
#define MCF_EDMA_EEI_EEI11	   (0x0800)
#define MCF_EDMA_EEI_EEI12	   (0x1000)
#define MCF_EDMA_EEI_EEI13	   (0x2000)
#define MCF_EDMA_EEI_EEI14	   (0x4000)
#define MCF_EDMA_EEI_EEI15	   (0x8000)

/* Bit definitions and macros for MCF_EDMA_SERQ */
#define MCF_EDMA_SERQ_SERQ(x)		 (((x)&0x0F)<<0)
#define MCF_EDMA_SERQ_SAER		 (0x40)

/* Bit definitions and macros for MCF_EDMA_CERQ */
#define MCF_EDMA_CERQ_CERQ(x)		 (((x)&0x0F)<<0)
#define MCF_EDMA_CERQ_CAER		 (0x40)

/* Bit definitions and macros for MCF_EDMA_SEEI */
#define MCF_EDMA_SEEI_SEEI(x)		 (((x)&0x0F)<<0)
#define MCF_EDMA_SEEI_SAEE		 (0x40)

/* Bit definitions and macros for MCF_EDMA_CEEI */
#define MCF_EDMA_CEEI_CEEI(x)		 (((x)&0x0F)<<0)
#define MCF_EDMA_CEEI_CAEE		 (0x40)

/* Bit definitions and macros for MCF_EDMA_CINT */
#define MCF_EDMA_CINT_CINT(x)		 (((x)&0x0F)<<0)
#define MCF_EDMA_CINT_CAIR		 (0x40)

/* Bit definitions and macros for MCF_EDMA_CERR */
#define MCF_EDMA_CERR_CERR(x)		 (((x)&0x0F)<<0)
#define MCF_EDMA_CERR_CAER		 (0x40)

/* Bit definitions and macros for MCF_EDMA_SSRT */
#define MCF_EDMA_SSRT_SSRT(x)		 (((x)&0x0F)<<0)
#define MCF_EDMA_SSRT_SAST		 (0x40)

/* Bit definitions and macros for MCF_EDMA_CDNE */
#define MCF_EDMA_CDNE_CDNE(x)		 (((x)&0x0F)<<0)
#define MCF_EDMA_CDNE_CADN		 (0x40)

/* Bit definitions and macros for MCF_EDMA_INT */
#define MCF_EDMA_INT_INT0	   (0x0001)
#define MCF_EDMA_INT_INT1	   (0x0002)
#define MCF_EDMA_INT_INT2	   (0x0004)
#define MCF_EDMA_INT_INT3	   (0x0008)
#define MCF_EDMA_INT_INT4	   (0x0010)
#define MCF_EDMA_INT_INT5	   (0x0020)
#define MCF_EDMA_INT_INT6	   (0x0040)
#define MCF_EDMA_INT_INT7	   (0x0080)
#define MCF_EDMA_INT_INT8	   (0x0100)
#define MCF_EDMA_INT_INT9	   (0x0200)
#define MCF_EDMA_INT_INT10	   (0x0400)
#define MCF_EDMA_INT_INT11	   (0x0800)
#define MCF_EDMA_INT_INT12	   (0x1000)
#define MCF_EDMA_INT_INT13	   (0x2000)
#define MCF_EDMA_INT_INT14	   (0x4000)
#define MCF_EDMA_INT_INT15	   (0x8000)

/* Bit definitions and macros for MCF_EDMA_ERR */
#define MCF_EDMA_ERR_ERR0	   (0x0001)
#define MCF_EDMA_ERR_ERR1	   (0x0002)
#define MCF_EDMA_ERR_ERR2	   (0x0004)
#define MCF_EDMA_ERR_ERR3	   (0x0008)
#define MCF_EDMA_ERR_ERR4	   (0x0010)
#define MCF_EDMA_ERR_ERR5	   (0x0020)
#define MCF_EDMA_ERR_ERR6	   (0x0040)
#define MCF_EDMA_ERR_ERR7	   (0x0080)
#define MCF_EDMA_ERR_ERR8	   (0x0100)
#define MCF_EDMA_ERR_ERR9	   (0x0200)
#define MCF_EDMA_ERR_ERR10	   (0x0400)
#define MCF_EDMA_ERR_ERR11	   (0x0800)
#define MCF_EDMA_ERR_ERR12	   (0x1000)
#define MCF_EDMA_ERR_ERR13	   (0x2000)
#define MCF_EDMA_ERR_ERR14	   (0x4000)
#define MCF_EDMA_ERR_ERR15	   (0x8000)

/* Bit definitions and macros for MCF_EDMA_DCHPRI */
#define MCF_EDMA_DCHPRI_CHPRI(x)	 (((x)&0x0F)<<0)
#define MCF_EDMA_DCHPRI_ECP		 (0x80)

/* Bit definitions and macros for MCF_EDMA_TCD_SADDR */
#define MCF_EDMA_TCD_SADDR_SADDR(x)	 (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_EDMA_TCD_ATTR */
#define MCF_EDMA_TCD_ATTR_DSIZE(x)	 (((x)&0x0007)<<0)
#define MCF_EDMA_TCD_ATTR_DMOD(x)	 (((x)&0x001F)<<3)
#define MCF_EDMA_TCD_ATTR_SSIZE(x)	 (((x)&0x0007)<<8)
#define MCF_EDMA_TCD_ATTR_SMOD(x)	 (((x)&0x001F)<<11)
#define MCF_EDMA_TCD_ATTR_SSIZE_8BIT	 (0x0000)
#define MCF_EDMA_TCD_ATTR_SSIZE_16BIT	 (0x0100)
#define MCF_EDMA_TCD_ATTR_SSIZE_32BIT	 (0x0200)
#define MCF_EDMA_TCD_ATTR_SSIZE_16BYTE   (0x0400)
#define MCF_EDMA_TCD_ATTR_DSIZE_8BIT	 (0x0000)
#define MCF_EDMA_TCD_ATTR_DSIZE_16BIT	 (0x0001)
#define MCF_EDMA_TCD_ATTR_DSIZE_32BIT	 (0x0002)
#define MCF_EDMA_TCD_ATTR_DSIZE_16BYTE   (0x0004)

/* Bit definitions and macros for MCF_EDMA_TCD_SOFF */
#define MCF_EDMA_TCD_SOFF_SOFF(x)	 (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF_EDMA_TCD_NBYTES */
#define MCF_EDMA_TCD_NBYTES_NBYTES(x)	 (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_EDMA_TCD_SLAST */
#define MCF_EDMA_TCD_SLAST_SLAST(x)	 (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_EDMA_TCD_DADDR */
#define MCF_EDMA_TCD_DADDR_DADDR(x)	 (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_EDMA_TCD_CITER */
#define MCF_EDMA_TCD_CITER_CITER(x)	 (((x)&0x7FFF)<<0)
#define MCF_EDMA_TCD_CITER_E_LINK	 (0x8000)

/* Bit definitions and macros for MCF_EDMA_TCD_CITER_ELINK */
#define MCF_EDMA_TCD_CITER_ELINK_CITER(x)    (((x)&0x01FF)<<0)
#define MCF_EDMA_TCD_CITER_ELINK_LINKCH(x)   (((x)&0x003F)<<9)
#define MCF_EDMA_TCD_CITER_ELINK_E_LINK      (0x8000)

/* Bit definitions and macros for MCF_EDMA_TCD_DOFF */
#define MCF_EDMA_TCD_DOFF_DOFF(x)	 (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF_EDMA_TCD_DLAST_SGA */
#define MCF_EDMA_TCD_DLAST_SGA_DLAST_SGA(x)  (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_EDMA_TCD_BITER */
#define MCF_EDMA_TCD_BITER_BITER(x)	 (((x)&0x7FFF)<<0)
#define MCF_EDMA_TCD_BITER_E_LINK	 (0x8000)

/* Bit definitions and macros for MCF_EDMA_TCD_BITER_ELINK */
#define MCF_EDMA_TCD_BITER_ELINK_BITER(x)    (((x)&0x01FF)<<0)
#define MCF_EDMA_TCD_BITER_ELINK_LINKCH(x)   (((x)&0x003F)<<9)
#define MCF_EDMA_TCD_BITER_ELINK_E_LINK      (0x8000)

/* Bit definitions and macros for MCF_EDMA_TCD_CSR */
#define MCF_EDMA_TCD_CSR_START	         (0x0001)
#define MCF_EDMA_TCD_CSR_INT_MAJOR	 (0x0002)
#define MCF_EDMA_TCD_CSR_INT_HALF	 (0x0004)
#define MCF_EDMA_TCD_CSR_D_REQ	         (0x0008)
#define MCF_EDMA_TCD_CSR_E_SG		 (0x0010)
#define MCF_EDMA_TCD_CSR_E_LINK	         (0x0020)
#define MCF_EDMA_TCD_CSR_ACTIVE	         (0x0040)
#define MCF_EDMA_TCD_CSR_DONE		 (0x0080)
#define MCF_EDMA_TCD_CSR_LINKCH(x)	 (((x)&0x003F)<<8)
#define MCF_EDMA_TCD_CSR_BWC(x)	 (((x)&0x0003)<<14)
#define MCF_EDMA_TCD_CSR_BWC_NO_STALL	 (0x0000)
#define MCF_EDMA_TCD_CSR_BWC_4CYC_STALL  (0x8000)
#define MCF_EDMA_TCD_CSR_BWC_8CYC_STALL  (0xC000)

#endif

