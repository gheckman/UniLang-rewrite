/* cavLmcx.h - SDK-derived Lmcx data types, macros and addresses */

/*
 * Copyright (c) 2010-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01g,09dec11,x_f  update defines for OcteonII CN68xx
01f,06jul11,rlg  data structures pulled. now use SDK.  addresses are still
                 defined here. Note this file was moved into h/arch/mips
                 previously resided in src/vendor/octeon

01e,28apr11,rlg  updates for REV 2 63xx boards
01d,30oct10,slk  add defines for memory controller
01c,28oct10,rlg  adding CAV_LMCX_PHY_CTL
01b,20oct10,rlg  fix typo for dfm address
01a,21sep10,rlg  written
*/

#ifndef __INCocteonLmcxh
#define __INCocteonLmcxh

#ifdef  __cplusplus
extern "C" {
#endif

/* address defines */

#define CAV_LMCX_BASE_ADDR          0x8001180088000000ULL
#define CAV_LMCX_SP                 0x60000000ULL

#define CAV_LMCX_CONFIG_OFF	    0x0188
#define CAV_LMCX_CONFIG(blkId) \
     (CAV_LMCX_BASE_ADDR + CAV_LMCX_CONFIG_OFF + ((blkId) & 3) * 0x1000000ull) 

#define CAV_LMCX_CONTROL_OFF	    0x0190
#define CAV_LMCX_CONTROL(blkId)   \
     (CAV_LMCX_BASE_ADDR + CAV_LMCX_CONTROL_OFF + ((blkId) & 3) * 0x1000000ull) 

#define CAV_LMCX_TIMING_PARAMS0_OFF	    0x0198
#define CAV_LMCX_TIMING_PARAMS0(blkId) \
     (CAV_LMCX_BASE_ADDR + CAV_LMCX_TIMING_PARAMS0_OFF + ((blkId) & 3) * 0x1000000ull) 

#define CAV_LMCX_TIMING_PARAMS1_OFF	    0x01A0
#define CAV_LMCX_TIMING_PARAMS1(blkId) \
     (CAV_LMCX_BASE_ADDR + CAV_LMCX_TIMING_PARAMS1_OFF + ((blkId) & 3) * 0x1000000ull) 

#define CAV_LMCX_MODEREG_PARAMS0_OFF	    0x01A8
#define CAV_LMCX_MODEREG_PARAMS0(blkId) \
     (CAV_LMCX_BASE_ADDR + CAV_LMCX_MODEREG_PARAMS0_OFF + ((blkId) & 3) * 0x1000000ull) 

#define CAV_LMCX_MODEREG_PARAMS1_OFF	    0x0260
#define CAV_LMCX_MODEREG_PARAMS1(blkId) \
     (CAV_LMCX_BASE_ADDR + CAV_LMCX_MODEREG_PARAMS1_OFF + ((blkId) & 3) * 0x1000000ull) 

#define CAV_LMCX_DUAL_MEMCFG_OFF	    0x098
#if (OCTEON_MODEL == OCTEON_CN68XX)
#define CAV_LMCX_DUAL_MEMCFG(blkId) \
     ((CAV_LMCX_BASE_ADDR + CAV_LMCX_DUAL_MEMCFG_OFF) + \
     ((blkId) & 3) * 0x1000000ull)
#else /* ! (OCTEON_MODEL == OCTEON_CN68XX) */
#define CAV_LMCX_DUAL_MEMCFG(blkId) \
     ((CAV_LMCX_BASE_ADDR + CAV_LMCX_DUAL_MEMCFG_OFF) + \
     ((blkId) & 1) * 0x60000000ULL)
#endif /* (OCTEON_MODEL == OCTEON_CN68XX) */

#define CAV_LMCX_NXM_OFF	    0x00C8
#if (OCTEON_MODEL == OCTEON_CN68XX)
#define CAV_LMCX_NXM(blkId) \
     ((CAV_LMCX_BASE_ADDR + CAV_LMCX_NXM_OFF) + ((blkId) & 3) * 0x1000000ull)
#else /* !(OCTEON_MODEL == OCTEON_CN68XX) */
#define CAV_LMCX_NXM(blkId) \
     ((CAV_LMCX_BASE_ADDR + CAV_LMCX_NXM_OFF) + ((blkId) & 1) * 0x60000000ull)
#endif /* (OCTEON_MODEL == OCTEON_CN68XX) */

#define CAV_LMCX_RODT_MASK_OFF	    0x0268
#define CAV_LMCX_RODT_MASK(blkId) \
    (CAV_LMCX_BASE_ADDR + CAV_LMCX_RODT_MASK_OFF + ((blkId) & 3) * 0x1000000ull) 

#define CAV_LMCX_WODT_MASK_OFF	    0x01b0
#define CAV_LMCX_WODT_MASK(blkId) \
    (CAV_LMCX_BASE_ADDR + CAV_LMCX_WODT_MASK_OFF + ((blkId) & 3) * 0x1000000ull) 

#define CAV_LMCX_COMP_CTL2_OFF	    0x01b8
#define CAV_LMCX_COMP_CTL2(blkId) \
    (CAV_LMCX_BASE_ADDR + CAV_LMCX_COMP_CTL2_OFF + ((blkId) & 3) * 0x1000000ull)

#define CAV_LMCX_DIMMX_PARAMS_OFF	    0x0270
#define CAV_LMCX_DIMMX_PARAMS(offset, blkId ) \
    ((CAV_LMCX_BASE_ADDR + CAV_LMCX_DIMMX_PARAMS_OFF) + \
    (((offset) & 1) + ((blkId) & 3) * 0x200000ull) * 8)
     
#define CAV_LMCX_DIMM_CTL_OFF	    0x0310
#define CAV_LMCX_DIMM_CTL(blkId) \
    (CAV_LMCX_BASE_ADDR + CAV_LMCX_DIMM_CTL_OFF + ((blkId) & 3) * 0x1000000ull) 

#define CAV_LMCX_WLEVEL_CTL_OFF	    0x0300
#define CAV_LMCX_WLEVEL_CTL(blkId) \
    (CAV_LMCX_BASE_ADDR + CAV_LMCX_WLEVEL_CTL_OFF + ((blkId) & 3) * 0x1000000ull) 

#define CAV_LMCX_WLEVEL_RANKX_OFF	    0x02b0
#define CAV_LMCX_WLEVEL_RANKX(offset, blkId) \
    ((CAV_LMCX_BASE_ADDR + CAV_LMCX_WLEVEL_RANKX_OFF) + \
    (((offset) & 3) + ((blkId) & 3) * 0x200000ull) * 8)
     
#define CAV_LMCX_RLEVEL_CTL_OFF	    0x02a0
#define CAV_LMCX_RLEVEL_CTL(blkId)  \
    (CAV_LMCX_BASE_ADDR + CAV_LMCX_RLEVEL_CTL_OFF + ((blkId) & 3) * 0x1000000ull) 

#define CAV_LMCX_RLEVEL_RANKX_OFF	0x0280
#define CAV_LMCX_RLEVEL_RANKX(offset, blkId ) \
    ((CAV_LMCX_BASE_ADDR + CAV_LMCX_RLEVEL_RANKX_OFF) + \
    (((offset) & 3) + ((blkId) & 3) * 0x200000ull) * 8)

#define CAV_LMCX_INT_OFF	        0x01f0
#define CAV_LMCX_INT(blkId)   \
    (CAV_LMCX_BASE_ADDR + CAV_LMCX_INT_OFF + ((blkId) & 3) * 0x1000000ull) 

#define CAV_LMCX_SLOT_CTL0_OFF	    0x01f8
#define CAV_LMCX_SLOT_CTL0(blkId)   \
    (CAV_LMCX_BASE_ADDR + CAV_LMCX_SLOT_CTL0_OFF + ((blkId) & 3) * 0x1000000ull) 

#define CAV_LMCX_SLOT_CTL1_OFF	    0x0200
#define CAV_LMCX_SLOT_CTL1(blkId)   \
    (CAV_LMCX_BASE_ADDR + CAV_LMCX_SLOT_CTL1_OFF + ((blkId) & 3) * 0x1000000ull) 

#define CAV_LMCX_SLOT_CTL2_OFF	    0x0208
#define CAV_LMCX_SLOT_CTL2(blkId)   \
    (CAV_LMCX_BASE_ADDR + CAV_LMCX_SLOT_CTL2_OFF + ((blkId) & 3) * 0x1000000ull) 

#define CAV_LMCX_DDR_PLL_CTL_OFF	0x0258
#define CAV_LMCX_DDR_PLL_CTL(blkId) \
    (CAV_LMCX_BASE_ADDR + CAV_LMCX_DDR_PLL_CTL_OFF + ((blkId) & 3) * 0x1000000ull) 

#define CAV_LMCX_DLL_CTL2_OFF	    0x01c8
#define CAV_LMCX_DLL_CTL2(blkId)    \
    (CAV_LMCX_BASE_ADDR + CAV_LMCX_DLL_CTL2_OFF + ((blkId) & 3) * 0x1000000ull) 

#define CAV_LMCX_RESET_CTL_OFF	    0x0180
#define CAV_LMCX_RESET_CTL(blkId)   \
    (CAV_LMCX_BASE_ADDR + CAV_LMCX_RESET_CTL_OFF + ((blkId) & 3) * 0x1000000ull) 

#define CAV_LMCX_RLEVEL_DBG_OFF	    0x02A8
#define CAV_LMCX_RLEVEL_DBG(blkId)  \
    (CAV_LMCX_BASE_ADDR + CAV_LMCX_RLEVEL_DBG_OFF + ((blkId) & 3) * 0x1000000ull) 

#define CAV_LMCX_WLEVEL_DBG_OFF	    0x0308
#define CAV_LMCX_WLEVEL_DBG(blkId)  \
    (CAV_LMCX_BASE_ADDR + CAV_LMCX_WLEVEL_DBG_OFF + ((blkId) & 3) * 0x1000000ull) 

#define CAV_LMCX_DCLK_CNT_OFF       0x01e0
#define CAV_LMCX_DCLK_CNT(blkId)    \
    (CAV_LMCX_BASE_ADDR + CAV_LMCX_DCLK_CNT_OFF + ((blkId) & 3) * 0x1000000ull)

#define CAV_LMCX_PHY_CTL_OFF        0x0210
#define CAV_LMCX_PHY_CTL(blkId)     \
    (CAV_LMCX_BASE_ADDR + CAV_LMCX_PHY_CTL_OFF + ((blkId) & 3) * 0x1000000ull)

#define CAV_LMCX_DLL_CTL3_OFF       0x0218
#define CAV_LMCX_DLL_CTL3(blkId)    \
    (CAV_LMCX_BASE_ADDR + CAV_LMCX_DLL_CTL3_OFF + ((blkId) & 3) * 0x1000000ull)

#define CAV_DFM_BASE_ADDR           0x80011800D4000000ULL

#define CAV_DFM_DLL_CTL3_OFF	    0x0218
#define CAV_DFM_DLL_CTL3(blckId) \
     (CAV_DFM_BASE_ADDR + CAV_DFM_DLL_CTL3_OFF) 

#define CAV_DFM_DLL_CTL2_OFF	    0x01c8
#define CAV_DFM_DLL_CTL2(blckId) \
     (CAV_DFM_BASE_ADDR + CAV_DFM_DLL_CTL2_OFF) 

#define CAV_DFM_COMP_CTL2_OFF	    0x01b8
#define CAV_DFM_COMP_CTL2         \
     (CAV_DFM_BASE_ADDR + CAV_DFM_COMP_CTL2_OFF) 

#define CAV_DFM_RESET_CTL_OFF	    0x0180
#define CAV_DFM_RESET_CTL         \
     (CAV_DFM_BASE_ADDR + CAV_DFM_RESET_CTL_OFF) 

#define CAV_DFM_FCLK_CNTL_OFF	    0x01e0
#define CAV_DFM_FCLK_CNT(blckId)         \
     (CAV_DFM_BASE_ADDR + CAV_DFM_FCLK_CNTL_OFF) 

#define CAV_DFM_FLK_CNTL_OFF	    0x01e0
#define CAV_DFM_FLK_CNT(blckId)         \
     (CAV_DFM_BASE_ADDR + CAV_DFM_FLK_CNTL_OFF) 

#define CAV_DFM_FLK_SCLK_OFF	    0x0418
#define CAV_DFM_FLK_SCLK         \
     (CAV_DFM_BASE_ADDR + CAV_DFM_FLK_SCLK_OFF) 

#define CAV_DFM_FNT_CTL_OFF	    0x0400
#define CAV_DFM_FNT_CTL         \
     (CAV_DFM_BASE_ADDR + CAV_DFM_FNT_CTL_OFF) 

#define CAV_DFM_CONFIG_OFF	    0x0188
#define CAV_DFM_CONFIG         \
     (CAV_DFM_BASE_ADDR + CAV_DFM_CONFIG_OFF) 

#define CAV_DFM_CONTROL_OFF	    0x0190
#define CAV_DFM_CONTROL         \
     (CAV_DFM_BASE_ADDR + CAV_DFM_CONTROL_OFF) 

#define CAV_DFM_TIMING_PARAMS0_OFF	    0x0198
#define CAV_DFM_TIMING_PARAMS0         \
     (CAV_DFM_BASE_ADDR + CAV_DFM_TIMING_PARAMS0_OFF) 

#define CAV_DFM_TIMING_PARAMS1_OFF	    0x01a0
#define CAV_DFM_TIMING_PARAMS1         \
     (CAV_DFM_BASE_ADDR + CAV_DFM_TIMING_PARAMS1_OFF) 

#define CAV_DFM_MODEREG_PARAMS0_OFF	    0x01a8
#define CAV_DFM_MODEREG_PARAMS0         \
     (CAV_DFM_BASE_ADDR + CAV_DFM_MODEREG_PARAMS0_OFF) 

#define CAV_DFM_MODEREG_PARAMS1_OFF	    0x0260
#define CAV_DFM_MODEREG_PARAMS1         \
     (CAV_DFM_BASE_ADDR + CAV_DFM_MODEREG_PARAMS1_OFF) 

#define CAV_DFM_WODT_MASK_OFF	    0x01b0
#define CAV_DFM_WODT_MASK         \
     (CAV_DFM_BASE_ADDR + CAV_DFM_WODT_MASK_OFF) 

#define CAV_DFM_RODT_MASK_OFF	    0x0268
#define CAV_DFM_RODT_MASK         \
     (CAV_DFM_BASE_ADDR + CAV_DFM_RODT_MASK_OFF) 

#define CAV_DFM_WLEVEL_CTL_OFF	    0x0300
#define CAV_DFM_WLEVEL_CTL         \
     (CAV_DFM_BASE_ADDR + CAV_DFM_WLEVEL_CTL_OFF) 

#define CAV_DFM_WLEVEL_DBG_OFF	    0x0308
#define CAV_DFM_WLEVEL_DBG         \
     (CAV_DFM_BASE_ADDR + CAV_DFM_WLEVEL_DBG_OFF) 

#define CAV_DFM_WLEVEL_RANKX_OFF	    0x02b0
#define CAV_DFM_WLEVEL_RANKX(offset) \
     (CAV_DFM_BASE_ADDR + CAV_DFM_WLEVEL_RANKX_OFF + (((offset) & 1) * 8)) 

#define CAV_DFM_RLEVEL_CTL_OFF	    0x02a0
#define CAV_DFM_RLEVEL_CTL         \
     (CAV_DFM_BASE_ADDR + CAV_DFM_RLEVEL_CTL_OFF) 

#define CAV_DFM_RLEVEL_RANKX_OFF	    0x0280
#define CAV_DFM_RLEVEL_RANKX(offset)         \
     (CAV_DFM_BASE_ADDR + CAV_DFM_RLEVEL_RANKX_OFF + (((offset) & 1) * 8)) 

#define CAV_DFM_RLEVEL_DBG_OFF	    0x02a8
#define CAV_DFM_RLEVEL_DBG         \
     (CAV_DFM_BASE_ADDR + CAV_DFM_RLEVEL_DBG_OFF) 

#define CAV_DFM_SLOT_CTL0_OFF	    0x01f8
#define CAV_DFM_SLOT_CTL0         \
     (CAV_DFM_BASE_ADDR + CAV_DFM_SLOT_CTL0_OFF) 

#define CAV_DFM_SLOT_CTL1_OFF	    0x01f8
#define CAV_DFM_SLOT_CTL1         \
     (CAV_DFM_BASE_ADDR + CAV_DFM_SLOT_CTL1_OFF) 

/* earlier stuff */

#define CAV_LMCX_BIST_CTL_OFF       0x00F0
#define CAV_LMCX_BIST_CTL(blkId) \
     ((CAV_LMCX_BASE_ADDR + CAV_LMCX_BIST_CTL_OFF) + \
      (((blkId) & 1) * CAV_LMCX_SP))

#define CAV_LMCX_BIST_RESULT_OFF    0x00F8
#define CAV_LMCX_BIST_RESULT(blkId) \
     ((CAV_LMCX_BASE_ADDR + CAV_LMCX_BIST_RESULT_OFF) + \
      (((blkId) & 1) * CAV_LMCX_SP))

#define CAV_LMCX_COMP_CTL_OFF       0x0028
#define CAV_LMCX_COMP_CTL(blkId) \
     ((CAV_LMCX_BASE_ADDR + CAV_LMCX_COMP_CTL_OFF) + \
      (((blkId) & 1) * CAV_LMCX_SP))

#define CAV_LMCX_CTL_OFF            0x0010
#define CAV_LMCX_CTL(blkId) \
     ((CAV_LMCX_BASE_ADDR + CAV_LMCX_CTL_OFF) + \
      (((blkId) & 1) * CAV_LMCX_SP))

#define CAV_LMCX_CTL1_OFF           0x0090
#define CAV_LMCX_CTL1(blkId) \
     ((CAV_LMCX_BASE_ADDR + CAV_LMCX_CTL1_OFF) + \
      (((blkId) & 1) * CAV_LMCX_SP))

#define CAV_LMCX_DCLK_CTL_OFF       0x00B8
#define CAV_LMCX_DCLK_CTL(blkId) \
     ((CAV_LMCX_BASE_ADDR + CAV_LMCX_DCLK_CTL_OFF) + \
      (((blkId) & 1) * CAV_LMCX_SP))

#define CAV_LMCX_DDR2_CTL_OFF       0x0018
#define CAV_LMCX_DDR2_CTL(blkId) \
     ((CAV_LMCX_BASE_ADDR + CAV_LMCX_DDR2_CTL_OFF) + \
      (((blkId) & 1) * CAV_LMCX_SP))

#define CAV_LMCX_DELAY_CFG_OFF      0x0088
#define CAV_LMCX_DELAY_CFG(blkId) \
     ((CAV_LMCX_BASE_ADDR + CAV_LMCX_DELAY_CFG_OFF) + \
      (((blkId) & 1) * CAV_LMCX_SP))

#define CAV_LMCX_DLL_CTL_OFF        0x00C0
#define CAV_LMCX_DLL_CTL(blkId) \
     ((CAV_LMCX_BASE_ADDR + CAV_LMCX_DLL_CTL_OFF) + \
      (((blkId) & 1) * CAV_LMCX_SP))

#define CAV_LMCX_MEM_CFG0_OFF       0x0000
#define CAV_LMCX_MEM_CFG0(blkId) \
     ((CAV_LMCX_BASE_ADDR + CAV_LMCX_MEM_CFG0_OFF) + \
      (((blkId) & 1) * CAV_LMCX_SP))

#define CAV_LMCX_MEM_CFG1_OFF       0x0008
#define CAV_LMCX_MEM_CFG1(blkId) \
     ((CAV_LMCX_BASE_ADDR + CAV_LMCX_MEM_CFG1_OFF) + \
      (((blkId) & 1) * CAV_LMCX_SP))

#define CAV_LMCX_PLL_CTL_OFF        0x00A8
#define CAV_LMCX_PLL_CTL(blkId) \
     ((CAV_LMCX_BASE_ADDR + CAV_LMCX_PLL_CTL_OFF) + \
      (((blkId) & 1) * CAV_LMCX_SP))

#define CAV_LMCX_PLL_STATUS_OFF     0x00B0
#define CAV_LMCX_PLL_STATUS(blkId) \
     ((CAV_LMCX_BASE_ADDR + CAV_LMCX_PLL_STATUS_OFF) + \
      (((blkId) & 1) * CAV_LMCX_SP))

#define CAV_LMCX_READ_LEVEL_CTL_OFF 0x0140
#define CAV_LMCX_READ_LEVEL_CTL(blkId) \
     ((CAV_LMCX_BASE_ADDR + CAV_LMCX_READ_LEVEL_CTL_OFF) + \
      (((blkId) & 1) * CAV_LMCX_SP))

#define CAV_LMCX_RODT_COMP_CTL_OFF  0x00A0
#define CAV_LMCX_RODT_COMP_CTL(blkId) \
     ((CAV_LMCX_BASE_ADDR + CAV_LMCX_RODT_COMP_CTL_OFF) + \
      (((blkId) & 1) * CAV_LMCX_SP))

#define CAV_LMCX_RODT_CTL_OFF       0x0078
#define CAV_LMCX_RODT_CTL(blkId) \
     ((CAV_LMCX_BASE_ADDR + CAV_LMCX_RODT_CTL_OFF) + \
      (((blkId) & 1) * CAV_LMCX_SP))

#define CAV_LMCX_WODT_CTL0_OFF      0x0030
#define CAV_LMCX_WODT_CTL0(blkId) \
     ((CAV_LMCX_BASE_ADDR + CAV_LMCX_WODT_CTL0_OFF) + \
      (((blkId) & 1) * CAV_LMCX_SP))

#define CAV_LMCX_WODT_CTL1_OFF      0x0080
#define CAV_LMCX_WODT_CTL1(blkId) \
     ((CAV_LMCX_BASE_ADDR + CAV_LMCX_WODT_CTL1_OFF) + \
      (((blkId) & 1) * CAV_LMCX_SP))



#ifdef  __cplusplus
}
#endif

#endif /* __INCocteonLmcxh */


