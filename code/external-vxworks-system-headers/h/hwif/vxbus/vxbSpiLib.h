/* vxbSpiLib.h - SPI bus header file for vxBus */

/*
 * Copyright (c) 2012, 2013, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
16apr15,d_l  add spiRegister and spiDevAddDynamic declaration.(VXW6-83934)
01c,21mar13,y_y  clean up.
01b,12dec12,mpc  added macro SPI_FULL_DUPLEX
01a,22oct12,y_y  created
*/

#ifndef __INCvxbSpiLibh
#define __INCvxbSpiLibh

#ifdef __cplusplus
    extern "C" {
#endif /* __cplusplus */

/* defines */

/* SPI device mode defines */

/* clock phase */

#define SPI_CKPHA           0x01

/* clock polarity */

#define SPI_CKPOL           0x02

#define SPI_MODE_0          (0 | 0)

#define SPI_MODE_1          (0 | SPI_CKPHA)

#define SPI_MODE_2          (SPI_CKPOL | 0)

#define SPI_MODE_3          (SPI_CKPOL | SPI_CKPHA)

/* CS active high: active-low; normal */

#define SPI_CSPOL_HIGH      0x04

#define SPI_LSB_FIRST       0x08

#define SPI_LOOP            0x10

#define SPI_FULL_DUPLEX     0x20

/* Ioctl option values */

#define SPI_CS_GET              0       /* chipselect get/set */
#define SPI_CS_SET              1
#define SPI_WIDTH_GET           2       /* bits in word get/set */
#define SPI_WIDTH_SET           3
#define SPI_FREQ_GET            4       /* bus frequency get/set */
#define SPI_FREQ_SET            5
#define SPI_MODE_GET            6       /* SPI mode get/set */
#define SPI_MODE_SET            7
#define SPI_CS_POL_GET          8       /* chipselect polarity get/set */
#define SPI_CS_POL_SET          9
#define SPI_ORDER_GET           10      /* reverse data mode get/set */
#define SPI_ORDER_SET           11

/* Ceiling division - not the fastest way, but safer in terms of overflow */

#define DIV_CEIL(x,y)       (((x)/(y)) + ((((((x)/(y)))*(y)) == (x)) ? 0 : 1))

/* typedefs */

/* SPI Bit Order */

/* 
 * Reverse data mode. Determines the receive and transmit character bit order.
 */

typedef enum spiBitOrder
    {
    MSB_FIRST = 1,
    LSB_FIRST = 0
    } spiBitOrder;

/* CS Polarity */

typedef enum spiCsPol
    {
    HIGH_ACTIVE = 1,
    LOW_ACTIVE = 0
    } spiCsPol;

struct vxbSpiRegister
    {
    struct vxbDevRegInfo    b;
    };

/*
 * The vxbSpiDevInfo struct used to store the SPI device feature, such as
 * chipSelect, spi_device mode,etc. User will fill this struct in hwconf.c
 */

typedef struct vxbSpiDevInfo
    {
    /* SPI device name, used for match the corresponding driver */
    char *  deviceName;

   /* connect on which CS */
    UINT8   chipSelect;

    /* the bit width per words */
    UINT8   bitWidth;

    /* the maximum work frequerence of the SPI device */
    UINT32  devFreq;

    /* device mode - see SPI device mode defines */
    UINT32   mode;

    }SPI_DEV_INFO;

/*
 * The spiTransfer struct used to store the SPI transfer data info,
 * the spi device driver will fill this struct.
 */

typedef struct spiTransfer 
    {
    UINT8 * txBuf;    /* data to be written, or NULL */
    UINT8 * rxBuf;    /* data to be read, or NULL */
    UINT32  txLen;    /* size of tx buffers in bytes */
    UINT32  rxLen;    /* size of rx buffers in bytes */
    UINT32  usDelay;
    }SPI_TRANSFER;

typedef struct vxbSpiDevice SPI_HARDWARE;

typedef STATUS (*VXB_SPI_TRANSFER_FUNC) (VXB_DEVICE_ID pDev,
                                         SPI_HARDWARE * pSpiDev, 
                                         SPI_TRANSFER * spiTransfer);

typedef struct vxbSpiBusCtrl
    {
    VXB_SPI_TRANSFER_FUNC spiTransfer;    /* transfer routine */
    } VXB_SPI_BUS_CTRL;

typedef VXB_SPI_BUS_CTRL *          (*VXB_SPI_CTRL_FUNC) (VXB_DEVICE_ID);

/* 
 * This struct contains SPI controller driver ID, SPI device features and
 * transfer routine.
 */

struct vxbSpiDevice
    {
    VXB_DEVICE_ID      pCtlr;              /* SPI bus Controller */
    SPI_DEV_INFO *     devInfo;
    VXB_SPI_BUS_CTRL * pSpiBusCtrl;
    };

/* This struct saves SPI master constraints */

#define SPI_TRANS_LIMIT  0x0001    /* have trans length limit */

typedef struct vxbSpiMasterSpecial
    {
    UINT32      flag;
    UINT32      windowSize;
    void *      pArg;
    }VXB_SPI_MAST_SPEC;

/* function declarations */

extern STATUS spiRegister (void);
extern STATUS spiDevAddDynamic (VXB_DEVICE_ID busCtrlID, SPI_DEV_INFO * pSpiDevInfo);
extern STATUS vxbSpiTransfer (VXB_DEVICE_ID  pDev, SPI_TRANSFER * transInfo);
extern STATUS vxbSpiIoctl (VXB_DEVICE_ID pDev, int request, int arg);
extern void spiBusAnnounceDevices (VXB_DEVICE_ID busCtrlId);

#ifdef __cplusplus
    }
#endif /* __cplusplus */

#endif /* __INCvxbSpiLibh */
