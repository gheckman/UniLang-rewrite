/* cavEeprom.h - Wind River API for reading EEPROM data from Cavium Board */

/*
 * Copyright 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01b,28sep10,d_c  Make cav header names consistent.
01a,06aug10,d_c  Written
*/

#ifndef __INCcavEepromLibh
#define __INCcavEepromLibh

#ifdef	__cplusplus
extern "C" {
#endif

IMPORT void cavEepromMacAddrGet
    (
    UINT8 *macAddr,             /* returned ethernet MAC address */
    int macAddrLen		/* length of <macAddr> buffer */
    );


#ifdef	__cplusplus
}
#endif
  
#endif /* __INCcavEepromLibh */
