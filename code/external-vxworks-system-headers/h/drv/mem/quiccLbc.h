/* quiccLbc.h - Motorola PowerQuicc Local Bus controller header */

/* Copyright 1984-2005 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,10jan05,dtr  adapted from ads85xx.h
*/

#ifndef	INCquiccLbch
#define	INCquiccLbch

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define  QUICC_BR0(base)     (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x000))
#define  QUICC_OR0(base)     (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x004))
#define  QUICC_BR1(base)     (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x008))
#define  QUICC_OR1(base)     (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x00c))
#define  QUICC_BR2(base)     (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x010))
#define  QUICC_OR2(base)     (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x014))
#define  QUICC_BR3(base)     (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x018))
#define  QUICC_OR3(base)     (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x01c))
#define  QUICC_BR4(base)     (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x020))
#define  QUICC_OR4(base)     (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x024))
#define  QUICC_BR5(base)     (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x028))
#define  QUICC_OR5(base)     (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x02C))
#define  QUICC_BR6(base)     (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x030))
#define  QUICC_OR6(base)     (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x034))
#define  QUICC_BR7(base)     (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x038))
#define  QUICC_OR7(base)     (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x03C))

#define  QUICC_MAR(base)     (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x068))
#define  QUICC_MAMR(base)    (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x070))
#define  QUICC_MBMR(base)    (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x074))
#define  QUICC_MCMR(base)    (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x078))
#define  QUICC_MRTPR(base)   (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x084))
#define  QUICC_MDR(base)     (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x088))

#define  QUICC_LSDMR(base)   (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x094))
#define  QUICC_MDR(base)     (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x088))

#define  QUICC_LSDMR(base)   (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x094))

#define  QUICC_LURT(base)    (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x0A0))
#define  QUICC_LSRT(base)    (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x0A4))
#define  QUICC_LTESR(base)   (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x0B0))
#define  QUICC_LTEDR(base)   (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x0B4))
#define  QUICC_LTEIR(base)   (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x0B8))
#define  QUICC_LTEATR(base)  (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x0BC))
#define  QUICC_LTEAR(base)   (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x0C0))

/* LBC Clock Configuration */
#define  QUICC_LBCR(base)    (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x0D0))
#define  QUICC_LCRR(base)    (CAST(VUINT32 *)((base) + LBC_REG_BA + 0x0D4))


#ifdef PQ2PRO

/* Local Bus Controller (LBC) Registers */
/* BRx 0-16 Base Address
 *     17-18 Extended Base Address 
 *     19-20 Port Size - 00 reserved
 *                     - 01 8bit
 *                     - 10 16bit
 *                     - 11 32bit
 *     21-22 Data Error Correction
 *                     - 00 reserved
 *                     - 01 Normal parity 
 *                     - 10 RMW parity generation (32-bit)
 *                     - 11 reserved
 *     23    Write Protect
 *     24-26 Machine Select = 000 GPCM
 *                          - 001->010 reserved
 *                          - 011 SDRAM
 *                          - 100->110 UPMA->UPMC
 *                          - 111 reserved
 *     28-29 Atomic Access  - 00 No atomic access
 *                          - 01 Read-after-write
 *                          - 10 Write-after-read
 *                          - 11 reserved
 *     31    Valid     
 *      
 * ORx for SDRAM
 *     0-16  Address mask 
 *     17-18 Extended address mask
 *     19-21 Column address lines - 000->111 7->14
 *     23-25 Number of row address lines - 000->110 9->15
 *                                       - 111 Reserved
 *     26    Page mode select
 *     31    External address latch delay 
 *
 * ORx for GPCM Mode
 *     0-16  Address mask 
 *     17-18 Extended address mask
 *     19    Buffer Control Disable
 *     20    Chip select negation
 *     21-22 Addres to chip select setup
 *     23    Extra Address to chip select setup
 *     24-27 Cycle length in Bus clocks - 0000->1111 0->15 wait states
 *     28    External address termination
 *     29    Timing relaxed
 *     30    Extended hold time for read access
 *     31    External address latch delay  
 */

#define  MRTPR_PTP_MASK 0xff000000
#define  MRTPR_PTP_WRITE(x)   ( (x << 24) & MRTPR_PTP_MASK)
#define  LSDMR_RFEN     0x40000000 /* Refresh Enable */
/* LSDMR OP - 000 Normal operation
 *          - 001 Auto Refresh  (Initialization)
 *          - 010 Self Refresh
 *          - 011 Mode Register Write (Initialization)
 *          - 100 Precharge Bank
 *          - 101 Precharge all banks (Initialization)
 *          - 110 Activate Bank
 *          - 111 Read/Write without valid transfer
 */      
#define  LSDMR_OP_MASK  0x38000000
#define  LSDMR_OP_SHIFT(x) ((x << 27) & LSDMR_OP_MASK)
/* Bank Select Multiplexed address line - 000 lines 12:13
 *                                      - 001       13:14
 *                                      - 010       14:15
 *                                      - 011       15:16
 *                                      - 100       16:17
 *                                      - 101       17:18
 *                                      - 110       18:19
 *                                      - 111       19:20
 */
#define  LSDMR_BSMA_MASK 0x00E00000
#define  LSDMR_BSMA_SHIFT(x) ((x << 23) & LSDMR_BSMA_MASK)
/* RFCR Refresh recovery 000 - reserved
 *                       001->110 - 3->8 clocks
 *                       111 - 16 clocks
 */
#define  LSDMR_RFCR_MASK 0x00038000
#define  LSDMR_RFCR_SHIFT(x) ((x << 15) & LSDMR_RFCR_MASK)
/* Incomplete LSDMR definitions */
#endif /* PQ2PRO */

#ifndef _ASMLANGUAGE
/* Memory controller registers.
*/
typedef struct  mem_ctlr {
        uint32_t    memc_br0;
        uint32_t    memc_or0;
        uint32_t    memc_br1;
        uint32_t    memc_or1;
        uint32_t    memc_br2;
        uint32_t    memc_or2;
        uint32_t    memc_br3;
        uint32_t    memc_or3;
        uint32_t    memc_br4;
        uint32_t    memc_or4;
        uint32_t    memc_br5;
        uint32_t    memc_or5;
        uint32_t    memc_br6;
        uint32_t    memc_or6;
        uint32_t    memc_br7;
        uint32_t    memc_or7;
        uint32_t    memc_br8;
        uint32_t    memc_or8;
        uint32_t    memc_br9;
        uint32_t    memc_or9;
        uint32_t    memc_br10;
        uint32_t    memc_or10;
        uint32_t    memc_br11;
        uint32_t    memc_or11;
        char        res1[8];
        uint32_t    memc_mar;
        char        res2[4];
        uint32_t    memc_mamr;
        uint32_t    memc_mbmr;
        uint32_t    memc_mcmr;
        char        res3[8];		/* manual wrong, says 48 bits */
        uint16_t    memc_mptpr;
        char        res4[2];
        uint32_t    memc_mdr;
        char        res5[4];
        uint32_t    memc_psdmr;
        uint32_t    memc_lsdmr;
        uint8_t     memc_purt;
        char        res6[3];
        uint8_t     memc_psrt;
        char        res7[3];
        uint8_t     memc_lurt;
        char        res8[3];
        uint8_t     memc_lsrt;
        char        res9[3];
        uint32_t    memc_immr;
        char        res10[84];
} memctl834x_t;

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INCquiccLbch */
