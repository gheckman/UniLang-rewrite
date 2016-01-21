/* wancomEnd.h - Marvel/Galileo GT642xx network interface header */

/*
 * Copyright (c) 2002, 2004-2005, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
/* Copyright 2002 Motorola, Inc. All Rights Reserved */

/*
modification history
--------------------
01f,06may10,c_t  change WANCOM_BUF_DEF_SIZE from 1518 to 1520(WIND00204839)
01e,09feb05,mdo  Documentation fixes for apigen
01d,28jun04,h_k  added pNetBufCfg and initType, deleted memBaseState and
                 hashState in WANCOM_DRV_CTRL and pMblk in RX_DESC.
01c,11jun04,h_k  changed comment for baseAddr. merged wancomDefs.h.
01b,26mar04,h_k  merged from cp7000g BSP.
01a,28oct02,scb  Copied from hxeb100 base version 01a.
*/

/*
********************************************************************************
*              (c), Copyright 2001, Marvell International Ltd.                 *
* THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL SEMICONDUCTOR, INC.   *
* NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT  *
* OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE        *
* DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.     *
* THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESS, IMPLIED *
* OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.           *
********************************************************************************
* wancomEnd.h - Header File for : GT-642xx network interface header 
*
* DESCRIPTION:
*       This file defines the network devices that can be attached to the MUX.
*
* DEPENDENCIES:
*       WRS endLib library.
*
********************************************************************************
*/

#ifndef __INCwancomEndh
#define __INCwancomEndh

/* includes */

#include "etherLib.h"
#include "miiLib.h"

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define DRV_NAME                                "wancom"

/* descriptor defines */

#define SHADOW_OWNER_BY_GT                      1
#define SHADOW_OWNER_BY_CPU                     0
#define OWNER_BY_GT                             (1<<31)
#define FIRST                                   (1<<17)
#define LAST                                    (1<<16)
#define ENABLE_INTERRUPT                        (1<<23)
#define PADDING                                 (1<<18)
#define GENERATE_CRC                            (1<<22)
#define ERROR_SUMMARY                           (1<<15)

/* this macros are used to enable access to MPSC_SDCMR */

#define ENABLE_RX_DMA                           (1<<7)
#define ABORT_RECEIVE                           (1<<15)
#define STOP_TRANSMIT                           (1<<16)
#define PORT_SDMA_STOP_TX_LOW                   (1<<17)
#define TX_DEMAND                               (1<<23)
#define PORT_SDMA_START_TX_LOW                  (1<<24)
#define ABORT_TRANSMIT                          (1<<31)

/* Serial second layer cause registers bits definition */
/* Ethernet mask bits */

#define RX_BUFFER_RETURN                        0x1
#define TX_BUFFER_HIGH_PRIO                     0x4
#define TX_BUFFER_LOW_PRIO                      0x8
#define TX_END_HIGH_PRIO                        0x40
#define TX_END_LOW_PRIO                         0x80
#define RX_RESOURCE_ERR                         0x100
#define TX_RESOURCE_ERR_HIGH_PRIO               0x400
#define TX_RESOURCE_ERR_LOW_PRIO                0x800
#define RX_OVERRUN                              0x1000
#define TX_UNDERRUN                             0x2000
#define RX_BUFFER_QUEUE_0                       (1<<16)
#define RX_BUFFER_QUEUE_1                       (1<<17)
#define RX_BUFFER_QUEUE_2                       (1<<18)
#define RX_BUFFER_QUEUE_3                       (1<<19)
#define RX_ERROR_QUEUE_0                        (1<<20)
#define RX_ERROR_QUEUE_1                        (1<<21)
#define RX_ERROR_QUEUE_2                        (1<<22)
#define RX_ERROR_QUEUE_3                        (1<<23)
#define MII_PHYS_STATUS_CHANGE                  0x10000000
#define SMI_COMMAND_DONE                        0x20000000
#define ETHER_INT_SUM                           0x80000000

/* Serial Port Multiplex register (connect to MII control) */

#define SERIAL_PORT_MULTIPLEX                   0xf010

#define ETHERNET_PORTS_DIFFERENCE_OFFSETS       0x400 

#define NIBBLE_SWAPPING_16_BIT(X) (((X&0xf)<<4) | ((X&0xf0)>>4) |        \
        ((X&0xf00)<<4) | ((X&0xf000)>>4))

#define NIBBLE_SWAPPING_32_BIT(X) (((X&0xf)<<4) | ((X&0xf0)>>4) |        \
        ((X&0xf00)<<4) | ((X&0xf000)>>4) | ((X&0xf0000)<<4) |            \
        ((X&0xf00000)>>4) | ((X&0xf000000)<<4) | ((X&0xf0000000)>>4))

#define GT_NIBBLE(X) ((X&0x1)<<3)+((X&0x2)<<1)+((X&0x4)>>1)+((X&0x8)>>3)

#define FLIP_6_BITS(X) (((X&0x1)<<5)+((X&0x2)<<3)+((X&0x4)<<1)+          \
        ((X&0x8)>>1)+((X&0x10)>>3)+((X&0x20)>>5))

#define FLIP_9_BITS(X) (((X&0x1)<<8)+((X&0x2)<<6)+((X&0x4)<<4)+          \
        ((X&0x8)<<2)+((X&0x10)<<0)+((X&0x20)>>2)+((X&0x40)>>4)+          \
        ((X&0x80)>>6)+((X&0x100)>>8))

#define _8K_TABLE                           0
/* size of hash entry for an address */

#define MAC_ENTRY_SIZE                      8
/* hash table entry fields */

#define VALID_BIT                           0
#define VALID                               1
#define NOT_VALID                           0
#define SKIP_BIT                            1
#define SKIP                                (1<<1)
#define DONT_SKIP                           0
#define RD_BIT                              2
#define RCV_PKT                             1
#define DROP_RCV_PKT                        0

#define HOP_NUMBER                          12

#define EIGHT_K 0x8000
#define HALF_K  0x8000/16

#define HASH_DEFUALT_MODE                   14
#define HASH_MODE                           13
#define HASH_SIZE                           12
#define PROMISCUOUS_MODE                    0

#define WANCOM_BUF_DEF_SIZE           (SIZEOF_ETHERHEADER + ETHERMTU + 4 + 2)

/* For buffers less than 8 bytes */

#define TX_BUF_OFFSET_IN_DESC               0x18
/* ethernet configuration value */

#define PORT_CONFIG_VALUE                   0x00000081

/* Ethernet config ext. value */

#define PORT_CONFIG_EXTEND_VALUE            0x00010800

/* SDMA configure value */

#if (_BYTE_ORDER == _BIG_ENDIAN)
/* big endian DMA transfer mode */

#define PORT_SDMA_CONFIG_VALUE              0x00002000

#else
/* little endian DMA transfer mode */

#define PORT_SDMA_CONFIG_VALUE              0x000020c0

#endif /* _BYTE_ORDER == _BIG_ENDIAN */

/* serial ports multiple x reg (RMII and mpsc's connected) */

#define GT_SERIAL_PORT_MUX                  0x00000001

#ifndef WANCOM_SYS_INT_CONNECT
#define WANCOM_SYS_INT_CONNECT(pDrvCtrl, pFunc, arg, pRet)               \
        {                                                                \
        *pRet = ERROR ;                                                  \
        if(wancomEndIntConnect != NULL)                                  \
        {                                                                \
        *pRet = (wancomEndIntConnect) (                                  \
                             INUM_TO_IVEC (pDrvCtrl->port.vector),        \
                             (VOIDFUNCPTR*)(pFunc), (int) (arg));        \
        }                                                                \
        }
#endif /* WANCOM_SYS_INT_CONNECT */

#ifndef WANCOM_SYS_INT_DISCONNECT
#define WANCOM_SYS_INT_DISCONNECT(pDrvCtrl, pFunc, arg, pRet)            \
        {                                                                \
        *pRet = ERROR ;                                                  \
        if(wancomEndIntDisconnect != NULL)                               \
        {                                                                \
        *pRet = (wancomEndIntDisconnect) ((VOIDFUNCPTR*)                 \
                 INUM_TO_IVEC (pDrvCtrl->port.level),                    \
                 (pFunc), (int) (arg));                                  \
        }                                                                \
        }
#endif /* WANCOM_SYS_INT_DISCONNECT */

#ifndef WANCOM_SYS_INT_ENABLE
#define WANCOM_SYS_INT_ENABLE(pDrvCtrl)                                  \
if (WANCOM_INT_ENABLE (pDrvCtrl))                                        \
    ((*(FUNCPTR) (WANCOM_INT_ENABLE (pDrvCtrl))) (pDrvCtrl->unit))
#endif /* WANCOM_SYS_INT_ENABLE */

#ifndef WANCOM_SYS_INT_DISABLE
#define WANCOM_SYS_INT_DISABLE(pDrvCtrl)                                 \
if (WANCOM_INT_DISABLE (pDrvCtrl))                                       \
    ((*(FUNCPTR) (WANCOM_INT_DISABLE (pDrvCtrl))) (pDrvCtrl->unit))
#endif /* WANCOM_SYS_INT_DISABLE */

#ifndef WANCOM_SYS_INT_ACK
#define WANCOM_SYS_INT_ACK(pDrvCtrl)                                     \
if (WANCOM_INT_ACK (pDrvCtrl))                                           \
    ((*(FUNCPTR) (WANCOM_INT_ACK (pDrvCtrl))) (pDrvCtrl->unit))
#endif /* WANCOM_SYS_INT_ACK */

#ifndef LOCAL_TO_SYS_ADDR
#define LOCAL_TO_SYS_ADDR(unit,localAddr)                                \
    ((int) pDrvCtrl->port.sysLocalToBus ?                                \
    (*pDrvCtrl->port.sysLocalToBus) (unit, localAddr) : localAddr)
#endif /* LOCAL_TO_SYS_ADDR */

#ifndef SYS_TO_LOCAL_ADDR
#define SYS_TO_LOCAL_ADDR(unit,sysAddr)                                  \
    ((int) pDrvCtrl->port.sysBusToLocal ?                                \
    (*pDrvCtrl->port.sysBusToLocal)(unit, sysAddr) : sysAddr)
#endif /* SYS_TO_LOCAL_ADDR */


/* CPU interface registers */

#define WANCOM_DEV_NAME          "wancom"
#define WANCOM_DEV_NAME_LEN      7
#define DEF_NUM_CFDS             32         /* default number of CFDs (Hex) */
#define DEF_NUM_RFDS             32         /* default number of RFDs (Hex) */
#define WANCOM_100MBS            100000000  /* bits per sec */
#define WANCOM_10MBS             10000000   /* bits per sec */
#define WANCOM_ADDR_LEN          6          /* ethernet address length */

/* constants needed within this file */

#define EH_SIZE                  14         /* avoid structure padding issues */
#define N_MCAST                  12

/* offsets from 642xx register base address */

#define PORT0_BASE_OFFSET        0x2400     /* ethernet 0 base addr */
#define ETH_SMIR_BASE_OFFSET     0x2010     /* SMIR register */
#define ETH_PHY_BASE_OFFSET      0x2000     /* Phy register */

/* Ethernet port register offsets from port base address */

#define PORT_CONFIG_REG                     0x000
#define PORT_CONFIG_EXTEND_REG              0x008
#define PORT_COMMAND_REG                    0x010
#define PORT_STATUS_REG                     0x018
#define SERIAL_PARAMETERS_REG               0x020
#define HASH_TABLE_POINTER_REG              0x028
#define FLOW_CONTROL_SOURCE_ADDRESS_LOW     0x030
#define FLOW_CONTROL_SOURCE_ADDRESS_HIGH    0x038
#define SDMA_CONFIGURATION_REG              0x040
#define SDMA_COMMAND_REG                    0x048
#define INTERRUPT_CAUSE_REG                 0x050
#define INTERRUPT_MASK_REG                  0x058
#define FIRST_RX_DESC_PTR0_OFFSET           0x080
#define FIRST_RX_DESC_PTR1_OFFSET           0x084
#define FIRST_RX_DESC_PTR2_OFFSET           0x088
#define FIRST_RX_DESC_PTR3_OFFSET           0x08c
#define CURRENT_RX_DESC_PTR0_OFFSET         0x0a0
#define CURRENT_RX_DESC_PTR1_OFFSET         0x0a4
#define CURRENT_RX_DESC_PTR2_OFFSET         0x0a8
#define CURRENT_RX_DESC_PTR3_OFFSET         0x0ac
#define CURRENT_TX_DESC_PTR0_OFFSET         0x0e0
#define CURRENT_TX_DESC_PTR1_OFFSET         0x0e4
#define MIB_COUNTER_BASE                    0x100 
#define MIB_COUNTER_END                     0x200

/* Port status register bits offset in register */

#define SPEED_100MBS                        (1<<0)
#define LINK_UP_BIT                         (1<<3)
#define TX_LOW_RUNNING                      (1<<5)
#define TX_HIGH_RUNNING                     (1<<6)
#define TX_IN_PROGRESS                      (1<<7)

/* Port Config register bits offset in register */

#define	PROMISCUOUS_MODE_BIT                (1<<0)


/* typedefs */
/* board specific information */

typedef struct
    {
    UINT32 vector;                          /* interrupt vector */
    UINT32 level;                           /* interrupt level */
    UINT32 baseAddr;                        /* Port registers base address */
    UCHAR  enetAddr[8];                     /* eth address with 2 byte pad */
    int (*intEnable)(int unit);             /* port interrupt enable routine */
    int (*intDisable)(int unit);            /* port interrupt disable routine */
    int (*intAck) (int unit);               /* interrupt ack */
    UINT32  portConfig;
    UINT32  portConfigExtend;
    UINT32  portCommand;
    UINT32  portSdmaConfig;
    int     offset;
    } WANCOM_PORT_INFO;

typedef unsigned int              RX_COMMAND;

typedef struct SdmaRxDesc
    {
#if (_BYTE_ORDER == _BIG_ENDIAN)
    unsigned int		bufsize :16;
    volatile unsigned int	bytecnt :16;
    volatile RX_COMMAND		cmd_sts; 
    unsigned int		next_desc_ptr; 
    volatile unsigned int	buf_ptr;  
#else /* _BYTE_ORDER == _BIG_ENDIAN */
    volatile RX_COMMAND		cmd_sts; 
    volatile unsigned int	bytecnt :16;
    unsigned int		bufsize :16;
    unsigned int		buf_ptr;  
    unsigned int		next_desc_ptr; 
#endif /* _BYTE_ORDER == _BIG_ENDIAN */
    M_BLK_ID			pMblk;
    /* to be safe, align the structure size multiple of 32 bytes */
    unsigned int		reserved [3];
    } RX_DESC;

typedef unsigned int              TX_COMMAND;

/* tx descriptor definition.  buf is used for sending small buffers
 * less than 8 bytes in size.  buf is placed so it is on a boundary
 * that is divisible by 8 (required for buffers <= 8 bytes) and
 * sized so the descriptor is divisible evenly by 16
 */

typedef struct SdmaTxDesc
    {
#if (_BYTE_ORDER == _BIG_ENDIAN)
    unsigned int          bytecnt     :16;
    unsigned int          shadowOwner :16;
    volatile TX_COMMAND            cmd_sts;
    unsigned int          next_desc_ptr; 
    unsigned int          buf_ptr;
#else /* _BYTE_ORDER == _BIG_ENDIAN */
    volatile TX_COMMAND            cmd_sts;
    unsigned int          shadowOwner :16;
    unsigned int          bytecnt     :16;
    unsigned int          buf_ptr;
    unsigned int          next_desc_ptr; 
#endif /* _BYTE_ORDER == _BIG_ENDIAN */
    UINT8                 buf [8];
    M_BLK *		  pointerToRxQueue;
    char *		  txBuffPtr;
    } TX_DESC;

/* The definition of the driver control structure */

typedef struct wancom_drv_ctrl
    {
    END_OBJ     endObj;          /* base class */
    int         unit;            /* unit number */
    char *      pMemBase;        /* memory pool base */
    ULONG       memSize;         /* memory pool size */
    char *      pClsBase;        /* cluster pool base */
    char *      pMemArea;        /* Mblk Clblk pool pointer */
    char *      pTxBuffBase;     /* tx buffer base address */
    int         nCFDs;           /* how many CFDs to create */
    volatile int nFreeCFDs;      /* how many CFDs freed */
    int         nRFDs;           /* how many RFDs to create */
    UINT32      pCSR;            /* pointer to CSR base */

    RX_DESC*    headRxDescPtr;   /* Pointer to head Rx desc queue       */
    RX_DESC*    rxDescMem;       /* Pointer to start of Rx desc memory */
    TX_DESC*    usedTxDescPtr;   /* Pointer to head Tx desc queue       */
    TX_DESC*    currTxDescPtr;   /* Pointer to next available Tx desc */
    TX_DESC*    txDescMem;       /* Pointer to start of Tx desc memory */

    UINT16      flags;           /* driver state */
    BOOL        attached;        /* interface has been attached */
    BOOL        rxHandle;        /* rx handler scheduled */
    BOOL        txHandle;        /* tx handler scheduled */
    BOOL        txStall;         /* tx handler stalled - no CFDs */
    END_ERR     lastError;       /* Last error passed to muxError */
    WANCOM_PORT_INFO port;       /* port specific info */
    CL_POOL_ID  pClPoolId;       /* cluster pool identifier */
    int         addressTableHashMode ;
    int         addressTableHashSize ;
    UINT32      addressTableBase ;
    char *      addressTableMalloc ;
    int         initType;        /* memory pool initialization type */
    NETBUF_CFG * pNetBufCfg;
    } WANCOM_DRV_CTRL;

#if (_BYTE_ORDER == _BIG_ENDIAN)
#define PSWAP(x)	LONGSWAP(x)
#else /* _BYTE_ORDER == _LITTLE_ENDIAN */
#define PSWAP(x)	(x)
#endif

#ifndef	EIEIO
#define EIEIO
#endif

#define WANCOM_REG_RD(x,val)   \
        { \
                UINT32 tmp ; \
                tmp = *((volatile UINT32*)(x)); \
                EIEIO ; \
                (*val) = PSWAP(tmp); \
                EIEIO ; \
        }

#define WANCOM_REG_WR(x,val)   \
        {       \
                UINT32 tmp ; \
        	tmp = PSWAP(val); \
                EIEIO ; \
                *((volatile UINT32*)(x)) = tmp ; \
                EIEIO ; \
                tmp = *((volatile UINT32*)(x)); \
        }

#ifdef __cplusplus
}
#endif

#endif /* __INCwancomEndh */

