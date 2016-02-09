/* vbiDeviceConfig.h - Device Configuration VBI */

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
01d,08feb11,jlv  Sync with HV 1.3 04-Feb-11 DVD
01c,01jun10,mmi  fix file name
01b,21may10,mpk  add DeviceTreeSource VBI calls
01a,12apr10,mpk  created
*/

/* DESCRIPTION
 *
 * VBI calls used by Guest OSs to discover Guest Devices
 *
 */

#ifndef __INCvbiDeviceConfigh
#define __INCvbiDeviceConfigh


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef _ASMLANGUAGE

extern uint32_t vbiDeviceCount (void);
extern status_t vbiDeviceGet (uint32_t deviceIndex, VB_DEV_INFO **vbiDevInfo);
extern vbiStatus_t vbiDeviceInterruptGet (uint32_t deviceIndex, 
					  uint32_t intIndex, 
					  VB_DEV_INT_INFO **vbiIntDetails);
extern vbiStatus_t vbiDeviceRegisterSetGet (uint32_t deviceIndex, 
					    uint32_t regSetIndex, 
					    VB_DEV_REGSET_INFO **vbiRegSetDetails);
extern vbiStatus_t vbiDeviceDeviceTreeSourceGet (uint32_t deviceIndex, 
						 uint32_t deviceTreeSourceIndex, 
						 VB_DEV_DEVICETREESOURCE_INFO **vbiDeviceTreeSourceDetails);

#endif 

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* __INCvbiDeviceConfigh */
