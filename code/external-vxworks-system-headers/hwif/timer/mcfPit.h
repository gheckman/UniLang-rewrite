/* mcfPit.h - coldfire programmable interrupt timer device header */

/*
 * Copyright (c) 2007 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01a,14nov07,rec	 created
*/

#ifndef __INCmcfPith
#define __INCmcfPith


/* register offsets */

#define VXB_MCF_PIT_PCSR	        0
#define VXB_MCF_PIT_PMR	                2
#define VXB_MCF_PIT_PCNTR               4

/* Register read/write macros */

#ifndef MCF_PIT_REG_OFFSET
#define MCF_PIT_REG_OFFSET  0x4000
#endif

#define MCF_PIT0_PCSR	       ((volatile UINT16*)(MCF_PIT0_BASE + \
                                    VXB_MCF_PIT_PCSR))
#define MCF_PIT0_PMR	       ((volatile UINT16*)(MCF_PIT0_BASE + \
                                    VXB_MCF_PIT_PMR))
#define MCF_PIT0_PCNTR	       ((volatile UINT16*)(MCF_PIT0_BASE + \
                                    VXB_MCF_PIT_PCNTR))

#define MCF_PIT1_PCSR	       ((volatile UINT16*)(MCF_PIT1_BASE + \
                                    VXB_MCF_PIT_PCSR))
#define MCF_PIT1_PMR	       ((volatile UINT16*)(MCF_PIT1_BASE + \
                                    VXB_MCF_PIT_PMR))
#define MCF_PIT1_PCNTR	       ((volatile UINT16*)(MCF_PIT1_BASE + \
                                    VXB_MCF_PIT_PCNTR))

#define MCF_PIT2_PCSR	       ((volatile UINT16*)(MCF_PIT2_BASE + \
                                    VXB_MCF_PIT_PCSR))
#define MCF_PIT2_PMR	       ((volatile UINT16*)(MCF_PIT2_BASE + \
                                    VXB_MCF_PIT_PMR))
#define MCF_PIT2_PCNTR	       ((volatile UINT16*)(MCF_PIT2_BASE + \
                                    VXB_MCF_PIT_PCNTR))

#define MCF_PIT3_PCSR	       ((volatile UINT16*)(MCF_PIT3_BASE + \
                                    VXB_MCF_PIT_PCSR))
#define MCF_PIT3_PMR	       ((volatile UINT16*)(MCF_PIT3_BASE + \
                                    VXB_MCF_PIT_PMR))
#define MCF_PIT3_PCNTR	       ((volatile UINT16*)(MCF_PIT3_BASE + \
                                    VXB_MCF_PIT_PCNTR))

#define MCF_PIT_PCSR(x)	       ((volatile UINT16*)((MCF_PIT0_BASE + \
                                    (x) * MCF_PIT_REG_OFFSET)))
#define MCF_PIT_PMR(x)	       ((volatile UINT16*)((MCF_PIT0_BASE + \
                                    (x) * MCF_PIT_REG_OFFSET)))
#define MCF_PIT_PCNTR(x)       ((volatile UINT16*)((MCF_PIT0_BASE + \
                                    (x) * MCF_PIT_REG_OFFSET)))

/* Bit definitions and macros for MCF_PIT_PCSR */

#define MCF_PIT_PCSR_EN      (0x0001)
#define MCF_PIT_PCSR_RLD     (0x0002)
#define MCF_PIT_PCSR_PIF     (0x0004)
#define MCF_PIT_PCSR_PIE     (0x0008)
#define MCF_PIT_PCSR_OVW     (0x0010)
#define MCF_PIT_PCSR_HALTED  (0x0020)
#define MCF_PIT_PCSR_DOZE    (0x0040)
#define MCF_PIT_PCSR_PRE(x)  (((x)&0x000F)<<8)

/* Bit definitions and macros for MCF_PIT_PMR */

#define MCF_PIT_PMR_PM(x)    (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF_PIT_PCNTR */

#define MCF_PIT_PCNTR_PC(x)  (((x)&0xFFFF)<<0)



#endif

