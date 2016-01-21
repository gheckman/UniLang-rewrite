/* pciHeaderDefs.h - PCI bus config space header definitions */

/* Copyright 1984-2005, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01d,29apr10,pad  Moved extern C statement after include statements.
01c,26jul05,mdo  Add includes for other bus technologies
01b,23jun03,m_h  Cardbus support
01a,04mar98,tm   adapted from pciIomapLib.h v01j
*/

#ifndef __INCpciHeaderDefsh
#define __INCpciHeaderDefsh

#include "msi.h"
#include "pciXLib.h"
#include "pciExpressLib.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/* structure for the device & bridge header */

typedef struct pciHeaderDevice
    {
    short   vendorId;   /* vendor ID */
    short   deviceId;   /* device ID */
    short   command;    /* command register */
    short   status;     /* status register */
    char    revisionId; /* revision ID */
    char    classCode;  /* class code */
    char    subClass;   /* sub class code */
    char    progIf;     /* programming interface */
    char    cacheLine;  /* cache line */
    char    latency;    /* latency time */
    char    headerType; /* header type */
    char    bist;       /* BIST */
    int     base0;      /* base address 0 */
    int     base1;      /* base address 1 */
    int     base2;      /* base address 2 */
    int     base3;      /* base address 3 */
    int     base4;      /* base address 4 */
    int     base5;      /* base address 5 */
    int     cis;        /* cardBus CIS pointer */
    short   subVendorId;    /* sub system vendor ID */
    short   subSystemId;    /* sub system ID */
    int     romBase;    /* expansion ROM base address */
    int     reserved0;  /* reserved */
    int     reserved1;  /* reserved */
    char    intLine;    /* interrupt line */
    char    intPin;     /* interrupt pin */
    char    minGrant;   /* min Grant */
    char    maxLatency; /* max Latency */
    } PCI_HEADER_DEVICE;

typedef struct pciHeaderBridge
    {
    short   vendorId;   /* vendor ID */
    short   deviceId;   /* device ID */
    short   command;    /* command register */
    short   status;     /* status register */
    char    revisionId; /* revision ID */
    char    classCode;  /* class code */
    char    subClass;   /* sub class code */
    char    progIf;     /* programming interface */
    char    cacheLine;  /* cache line */
    char    latency;    /* latency time */
    char    headerType; /* header type */
    char    bist;       /* BIST */
    int     base0;      /* base address 0 */
    int     base1;      /* base address 1 */
    char    priBus;     /* primary bus number */
    char    secBus;     /* secondary bus number */
    char    subBus;     /* subordinate bus number */
    char    secLatency; /* secondary latency timer */
    char    ioBase;     /* IO base */
    char    ioLimit;    /* IO limit */
    short   secStatus;  /* secondary status */
    short   memBase;    /* memory base */
    short   memLimit;   /* memory limit */
    short   preBase;    /* prefetchable memory base */
    short   preLimit;   /* prefetchable memory limit */
    int     preBaseUpper;   /* prefetchable memory base upper 32 bits */
    int     preLimitUpper;  /* prefetchable memory base upper 32 bits */
    short   ioBaseUpper;    /* IO base upper 16 bits */
    short   ioLimitUpper;   /* IO limit upper 16 bits */
    int     reserved;   /* reserved */
    int     romBase;    /* expansion ROM base address */
    char    intLine;    /* interrupt line */
    char    intPin;     /* interrupt pin */
    short   control;    /* bridge control */
    } PCI_HEADER_BRIDGE;

typedef struct pciHeaderCardBusBridge
    {
    short   vendorId;   /* vendor ID */
    short   deviceId;   /* device ID */
    short   command;    /* command register */
    short   status;     /* status register */
    char    revisionId; /* revision ID */
    char    classCode;  /* class code */
    char    subClass;   /* sub class code */
    char    progIf;     /* programming interface */
    char    cacheLine;  /* cache line */
    char    latency;    /* latency time */
    char    headerType; /* header type */
    char    bist;       /* BIST */
    int     base0;      /* base address 0 */
    char    capPtr;     /* capabilities pointer */
    char        reserved;   /* reserved */
    short   secStatus;  /* secondary status */
    char    priBus;     /* primary bus number */
    char    secBus;     /* secondary bus number */
    char    subBus;     /* subordinate bus number */
    char    secLatency; /* secondary latency timer */
    int     memBase0;   /* memory base 0 */
    int     memLimit0;  /* memory limit 0 */
    int     memBase1;   /* memory base 1 */
    int     memLimit1;  /* memory limit 1 */
    int     ioBase0;    /* IO base 0 */
    int     ioLimit0;   /* IO limit 0 */
    int     ioBase1;    /* IO base 1 */
    int     ioLimit1;   /* IO limit 1 */
    char    intLine;    /* interrupt line */
    char    intPin;     /* interrupt pin */
    short   control;    /* bridge control */
    short   subVendorId;    /* sub system vendor ID */
    short   subSystemId;    /* sub system ID */
    int     legacyBase; /* pccard 16-bit legacy mode base */    
    } PCI_HEADER_CB_BRIDGE;
    
#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCpciHeaderDefsh */
