/* cavSpi4000.h - Cavium SPI 4000 interface support */

/*
 * Copyright (c) 2010,2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01d,07jul11,rlg  Setup for SDK TYPEDEFS only
01c,05oct10,d_c  Remove extra comma from enum
01b,13aug10,d_c  Add interface elements to support vxbOcteonEnd.c
01a,06aug10,d_c  written
*/

#ifndef __INCcavSpi4000h
#define __INCcavSpi4000h

#include <arch/mips/private/cavSdkDrvInclude.h>
#define CAV_INCLUDE_TYPEDEFS_ONLY
#include CAV_SDK_DRV_INCLUDE(cvmx-spi.h)


#ifdef	__cplusplus
extern "C" {
#endif

/* defines */

/* typedefs */

typedef enum
{
    CAV_SPI_MODE_UNKNOWN       = CVMX_SPI_MODE_UNKNOWN,
    CAV_SPI_MODE_TX_HALFPLEX   = CVMX_SPI_MODE_TX_HALFPLEX,
    CAV_SPI_MODE_RX_HALFPLEX   = CVMX_SPI_MODE_RX_HALFPLEX,
    CAV_SPI_MODE_DUPLEX        = CVMX_SPI_MODE_DUPLEX
} CAV_SPI_MODE_T;

/* functions */

IMPORT int cavSpi4000IsPresent
    (
    int ifaceNum
    );

IMPORT int cavSpiInterfaceStart
    (
    int interface,
    CAV_SPI_MODE_T mode,
    int timeout,
    int num_ports
    );

IMPORT void cavSpi4000Write
    (
    int interface,
    int address,
    uint32_t data
    );

IMPORT uint32_t cavSpi4000Read
    (
    int interface,
    int address
    );

IMPORT void cavSpi4000Lock (void);
IMPORT void cavSpi4000Unlock (void);


IMPORT BOOL cavSpi4000BackPressureDisabled (void);


#ifdef	__cplusplus
}
#endif
  
#endif /* __INCcavSpi4000h */
