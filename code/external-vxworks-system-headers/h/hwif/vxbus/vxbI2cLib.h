/* vxbI2cLib.h - I2C bus header file for vxBus */

/*
 * Copyright (c) 2011, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01d,09nov12,syt  add parameters i2cDevEnableArg and pI2cDevEnableHook. 
01c,14may12,y_y  add readDelay parameter.
01b,19mar12,y_y  add vxbI2cByNameRead()/vxbI2cByNameWrite() routines for generic 
                 I2C device access.
01a,25aug11,l_z  created
*/

#ifndef __INCvxbI2cLibh
#define __INCvxbI2cLibh

#ifdef __cplusplus
    extern "C" {
#endif /* __cplusplus */

/* defines */

#define I2C_READ             0x01
#define I2C_WRITE            0x00

/*
 * Flag values for open(2) and fcntl(2)
 * The kernel adds 1 to the open modes to turn it into some
 * combination of FREAD and FWRITE.
 */

#define I2C_RDONLY           0x01        /* read only flag */
#define I2C_WORDADDR         0x02        /* word address flag */
#define I2C_BYTE_WR_ONLY     0x04        /* byte write only */
#define I2C_BYTE_RD_ONLY     0x08        /* byte read only */
#define I2C_RD_EXT_ACK       0x10        /* need a extra ACK when the address is word address */

typedef enum
    {
    DEV_TYPE = 0,                       /* device */
    ADDR_TYPE = 1,                      /* address */
    DATA_TYPE = 2                       /* data  */
    } I2C_REG_TYPES;

typedef STATUS (*VXB_I2C_LOCK_BUS_FUNC) (VXB_DEVICE_ID);
typedef STATUS (*VXB_I2C_START_FUNC) (VXB_DEVICE_ID, BOOL);
typedef STATUS (*VXB_I2C_READ_FUNC) (VXB_DEVICE_ID, UINT8 *,UINT32);
typedef STATUS (*VXB_I2C_WRITE_FUNC) ( VXB_DEVICE_ID, UINT8 *, UINT32, I2C_REG_TYPES, BOOL);
typedef STATUS (*VXB_I2C_STOP_FUNC) (VXB_DEVICE_ID);
typedef STATUS (*VXB_I2C_UNLOCK_BUS_FUNC) (VXB_DEVICE_ID);
typedef STATUS (*VXB_I2C_DEV_READ) (VXB_DEVICE_ID, UINT8, UINT32, UINT8 *,UINT32);
typedef STATUS (*VXB_I2C_DEV_WRITE) ( VXB_DEVICE_ID, UINT8, UINT32, UINT8 *, UINT32);
typedef void   (*VXB_I2C_DEV_ENABLE) (void *);

typedef struct i2cDevInputs
    {
    char * deviceName;
    UINT8  deviceAddr;
    UINT32 flag; 
    } I2C_DEV_INPUTS;

typedef struct vxbI2cBusCtrl
    {
    VXB_I2C_LOCK_BUS_FUNC   vxbI2cLock;     /* I2C lock by a devcie  */
    VXB_I2C_START_FUNC      vxbI2cStart;    /* start I2C bus */
    VXB_I2C_READ_FUNC       vxbI2cRead;
    VXB_I2C_WRITE_FUNC      vxbI2cWrite;
    VXB_I2C_STOP_FUNC       vxbI2cStop;     /* start I2C bus */
    VXB_I2C_UNLOCK_BUS_FUNC vxbI2cUnLock;   /* I2C unlock by a devcie  */
    VXB_I2C_DEV_READ        vxbI2cDevRead;  /* I2C device read */
    VXB_I2C_DEV_WRITE       vxbI2cDevWrite; /* I2C device read */
    } VXB_I2C_BUS_CTRL;

typedef struct vxbI2cDevice
    {
    UINT8               deviceAddr;
    VXB_DEVICE_ID       pCtlr;              /* I2C bus Controller */
    VXB_I2C_BUS_CTRL *  pI2cBusCtrl;        /* bus controller function */
    UINT32              flag; 
    UINT32              writeDelay;
    UINT32              readDelay;
    void *              i2cDevEnableArg;
    VXB_I2C_DEV_ENABLE  pI2cDevEnableHook;
    } I2C_HARDWARE;

typedef VXB_I2C_BUS_CTRL *(*VX_I2C_CTRL_FUNC) (VXB_DEVICE_ID);

struct vxbI2cRegister
    {
    struct vxbDevRegInfo    b;
    };

/* forward declarations */

void i2cBusAnnounceDevices (VXB_DEVICE_ID busCtrlId);
STATUS vxbI2cBusLock (VXB_DEVICE_ID pDev);
STATUS vxbI2cBusStart (VXB_DEVICE_ID pDev, BOOL reStart);
STATUS vxbI2cBusAddrWrite (VXB_DEVICE_ID pDev, UINT8, I2C_REG_TYPES regType, BOOL ack);
STATUS vxbI2cBusWrite (VXB_DEVICE_ID pDev,UINT8 *, int );
STATUS vxbI2cBusRead (VXB_DEVICE_ID pDev,UINT8 *, int );
STATUS vxbI2cDevRead (VXB_DEVICE_ID pDev, UINT32, UINT8 * pDataBuf, UINT32);
STATUS vxbI2cDevWrite (VXB_DEVICE_ID pDev, UINT32, UINT8 * pDataBuf, UINT32);
STATUS vxbI2cByNameRead (char *, UINT8, UINT32, UINT8 *, UINT32);
STATUS vxbI2cByNameWrite (char *, UINT8, UINT32, UINT8 *, UINT32);
STATUS vxbI2cBusStop (VXB_DEVICE_ID pDev);
STATUS vxbI2cBusUnLock (VXB_DEVICE_ID pDev);
void vxbI2cBusShow (VXB_DEVICE_ID busCtrlID);
void vxbI2cDeviceShow (VXB_DEVICE_ID pDev);

#ifdef __cplusplus
    }
#endif /* __cplusplus */

#endif /* __INCvxbI2cLibh */

