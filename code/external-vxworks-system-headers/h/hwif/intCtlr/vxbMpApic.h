/* vxbMpApic.h - VxBus driver header files for the
 *               Intel MP APIC/xAPIC (Advanced PIC)
 */

/*
 * Copyright (c) 2007-2010,2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01p,18aug14,jb   VXW6-83164 - MPAPIC_DATA_MAX_LEN of 4096 is too small for
                 large SMP systems
01o,13aug10,j_l  Adjust BIOS_ROM_START and BIOS_ROM_SIZE.
                 Fix for WIND00227546 - does not boot on Hanlan Creek.
01n,24jun10,j_l  Add local APIC global variables.
01m,30apr10,jb   Merge from 64bit view
01l,21apr10,h_k  made MP_APIC_DATA compatible between 32-bit and 64-bit.
01k,12apr10,h_k  LP64 adaptation.
01j,14jan10,sem  Corrected IOAPIC_LENGTH constant
01i,10aug09,rec  WIND00176001 - multiple IO Apic support mods...
                 add MPAPIC_DATA_MAX_LEN
01h,21nov08,scm  multiple IO Apic support mods...
01g,03oct08,rec  WIND00137112 - restore MPAPIC_DATA_START definition
01f,29sep08,rec  remove MPAPIC_DATA_START
01e,24jun08,scm  clean up for acpi support...
01c,24apr08,scm  WIND00103470 - SMP/SYMMETRIC_IO_MODE warm re-boot support.
01b,27feb08,h_k  changed LOAPIC_IPI_INFO.
01a,21Mar07,scm  created.
*/

/*
 * DESCRIPTION
 * This is the VxBus driver for the Local APIC Interrupt Driver
 */

#ifndef __INCvxbMpApic
#define __INCvxbMpApic

#ifdef __cplusplus
extern "C" {
#endif

/* Extended BIOS Data Area */
#define EBDA_START              0x9d000
#define EBDA_SIZE               0x03000
#define EBDA_END                (EBDA_START + (EBDA_SIZE - 1))

/* memory location where MP data stored for warm reboot */
#ifndef MPAPIC_DATA_START
#define MPAPIC_DATA_START	0x00102000
#endif

#ifndef MPAPIC_DATA_MAX_LEN
#define MPAPIC_DATA_MAX_LEN	8192    /* max buf size vxMP table */
#endif

/* identify startup structure  used for initialization: NONE/MP/ACPI/USR */
#define NO_MP_STRUCT            0x0
#define MP_MP_STRUCT            0x1
#define ACPI_MP_STRUCT          0x2
#define USR_MP_STRUCT           0x3

/* BIOS ROM space */
#define BIOS_ROM_START          0xef000
#define BIOS_ROM_SIZE           0x11000
#define BIOS_ROM_END            (BIOS_ROM_START + (BIOS_ROM_SIZE - 1))

/* Local APIC base addr */
#define LOAPIC_BASE             0xfee00000
#define LOAPIC_LENGTH           0x00001000

/* EOI Register */
#define LOAPIC_EOI              0xb0

/* IO APIC Index base addr */
#define IOAPIC_BASE             0xfec00000
#define IOAPIC_LENGTH           0x00001000

/* NOTE: entry into the sysMmuPhysDesc[] done once at initialization,
 * for now, IOAPIC_LENGTH expected to equal maximum apic space required.
 */

#define IOAPIC_MAX_LENGTH       0x00001000

/* Maximum Number of IOAPICs in the system */
#ifndef MAX_IOAPICS
#define MAX_IOAPICS             0x10
#endif

/* EOI Register */
#define IOAPIC_EOI              0x40

/* MP Apic Table Phys-To-Virt translation */

#ifdef  _WRS_CONFIG_LP64
#define MPAPIC_PHYS_TO_VIRT(x)  (void *) ((ULONG)pMpApicData + \
                                (pMpApicData->x - pMpApicData->mpApicDataLoc))
#else
#define MPAPIC_PHYS_TO_VIRT(x)  (void *) (pMpApicData->x)
#endif  /* _WRS_CONFIG_LP64 */

/* MultiProcessor Specification version 1.4 */

typedef struct                  /* MP Floating Pointer Structure */
    {
    char    signature [4];      /* "_MP_" */
    UINT32  configTableAddr;    /* address of the MP configuration table */
    UINT8   length;             /* length of the floating pointer structure */
    UINT8   specRev;            /* version number of the MP specification */
    UINT8   cksum;              /* checksum of the pointer structure */
    UINT8   featureByte[5];     /* MP feature bytes 1 - 5 */
    } MP_FPS;

typedef struct                  /* MP Configuration Table Header */
    {
    char    mpSignature[4];     /* "PCMP" */
    UINT16  tableLength;        /* length of the base configuration table */
    UINT8   specRevision;       /* version number of the MP specification */
    UINT8   cksum;              /* checksum of the base configuration table */
    char    oemId[8];           /* string that identifies the manufacturer */
    char    prodId[12];         /* string that identifies the product */
    UINT32  oemTablePtr;        /* address to an OEM configuration table */
    UINT16  oemTableSize;       /* size of the OEM configuration table */
    UINT16  entryCount;         /* number of entries in the variable table */
    UINT32  localApicBaseAddr;  /* address of the Local APIC */
    UINT16  extendedTableLength; /* length of the extended entries */
    UINT8   extendedTableCksum; /* checksum of the extended table entries */
    UINT8   reserved;
    } MP_HEADER;

typedef struct                  /* MP Config Table Entry for CPU's */
    {
    UINT8   entryType;          /* 0 identifies a processor entry */
    UINT8   localApicId;        /* Local APIC ID number */
    UINT8   localApicVersion;   /* Local APIC's version number */
    UINT8   cpuFlags;           /* EN: usable, BP: boot-processor */
    UINT32  cpuSig;             /* stepping, model, family of the CPU */
    UINT32  featureFlags;       /* feature definition flag */
    UINT32  reserved[2];
    } MP_CPU;

typedef struct                  /* MP Config Table Entry for IO APIC's */
    {
    UINT8  entryType;           /* 2 identifies an IO APIC entry */
    UINT8  ioApicId;            /* ID of this IO APIC */
    UINT8  ioApicVersion;       /* version of this IO APIC */
    UINT8  ioApicFlags;         /* usable or not */
    UINT32 ioApicBaseAddress;   /* address of this IO APIC */
    } MP_IOAPIC;

typedef struct
    {
    UINT8  entryType;
    UINT8  busId;
    UINT8  busType[6];
    } MP_BUS;

typedef struct
    {
    UINT8         entryType;
    UINT8     interruptType;
    UINT16   interruptFlags;
    UINT8       sourceBusId;
    UINT8      sourceBusIrq;
    UINT8        destApicId;
    UINT8     destApicIntIn;
    } MP_INTERRUPT;

typedef MP_INTERRUPT MP_IOINTERRUPT;
typedef MP_INTERRUPT MP_LOINTERRUPT;

typedef struct apic_info
    {
    UINT8  id;
    UINT32 *addr;
    } APIC_INFO;

typedef union loapic_ipi_info
    {
    UINT32 all;

    struct {
        UINT32 vectorNo:8;
        UINT32 deliMode:3;
        UINT32 destMode:1;
        UINT32 reserve2:2;
        UINT32 level:1;
        UINT32 trigger:1;
        UINT32 reserve1:2;
        UINT32 shortHand:2;
        UINT32 reserve0:4;
        UINT32 apicId:8;
        } icr;
    } LOAPIC_IPI_INFO;

/* mpApicData structure - structure holding mpApic details retrieved from
 *                        BIOS/ACPI/or USER defined methods.
 *
 *
 * The dynamic tables/structures are found contiguosly in memory following
 * the mpApicData structure. So, if the mpApicData structure is stored
 * at LOCAL_MEM_LOCAL_ADR + 0x2000, we look something like:
 *
 *
 *         |                      |
 *         |                      |
 *         ------------------------ <--- LOCAL_MEM_LOCAL_ADR + 0x2000
 *         |                      |
 *         | mpApicData Struct.   |
 *         |                      |
 *         |                      | <--- sizeof(MP_APIC_DATA)
 *   +-----| ptr to Local Apic    |
 *   |     |    Index Tbl         |
 *   |     |                      |
 *   |+----| ptr to Bus Routing   |
 *   ||    |    Tbl               |
 *   ||    |                      |
 *   ||+---| ptr to Interrupt     |
 *   |||   |    Routing Tbl       |
 *   |||   |                      |
 *   |||+--| ptr to Logical Tbl   |
 *   ||||  |                      |
 *   ||||+-| ptr to Address Tbl   |
 *   ||||| |                      |
 *   ||||| |                      |
 *   ||||| ------------------------
 *   ||||+>|                      |
 *   ||||  | mpApicAddrTable      | <--- (mpApicNioApic * sizeof(UINT32))
 *   ||||  |                      |
 *   ||||  ------------------------
 *   |||+->|                      |
 *   |||   | mpApicLogicalTable   | <--- (mpApicNioApic * sizeof(UINT8))
 *   |||   |                      |
 *   |||   ------------------------
 *   ||+-->|                      |
 *   |||   ------------------------
 *   ||+-->|                      |
 *   ||    | mpApicInterruptTable | <--- ((mpApicNioint + mpApicNloint) *
 *   ||    |                      |       sizeof(MP_INTERRUPT))
 *   ||    |                      |
 *   ||    ------------------------
 *   |+--->|                      |
 *   |     | mpApicBusTable       | <--- (mpApicNbus * sizeof(MP_BUS))
 *   |     |                      |
 *   |     ------------------------
 *   +---->|                      |
 *         | mploApicIndexTable   | <--- (mpApicCpuCount * sizeof(UINT8))
 *         |                      |
 *         ------------------------
 *         |                      |
 *
 */

typedef struct mpApicData
    {
#ifdef	_WRS_CONFIG_LP64
     UINT32         reserved;       /* (not used in LP64) */
#else
     void           *pInst;         /* instance pointer */
#endif

     UINT32         mpApicDataLoc;  /* mem location of MP_APIC_DATA */
     UINT32         mpApicMpSize;   /* size of MP_APIC_DATA */

     UINT32         mpApicBootOpt;  /* NONE/MP/ACPI/USR boot structure used */

     MP_FPS         mpApicFps;      /* MP Floating Pointer Structure */

     MP_HEADER      mpApicHeader;   /* MP Configuration Table Header */

     UINT32         mpApicloBase;   /* def Local APIC addr */

     UINT32         mpApicNioApic;  /* number of IO APICs (MP Table) */

     /* logical io apic id to address mapping */

#ifdef	_WRS_CONFIG_LP64
     UINT32         reserved1;      /* (not used in LP64) */
#else
     UINT32         *mpApicAddrTable;
#endif	/* _WRS_CONFIG_LP64 */

     UINT32         mpApicAtLoc;    /* mem location of mpApicAddrTable */
     UINT32         mpApicAtSize;   /* size of mpApicAddrTable */

     /* recorded id mapping */

#ifdef	_WRS_CONFIG_LP64
     UINT32         reserved2;      /* (not used in LP64) */
#else
     UINT8          *mpApicLogicalTable;
#endif	/* _WRS_CONFIG_LP64 */

     UINT32         mpApicLtLoc;    /* mem location of mpApicLogicalTable */
     UINT32         mpApicLtSize;   /* size of mpApicLogicalTable */

     /* interrupt routing table */

     UINT32         mpApicNioint;   /* number of io interrupts (MP Table) */
     UINT32         mpApicNloint;   /* number of local interrupts (MP Table) */

#ifdef	_WRS_CONFIG_LP64
     UINT32         reserved3;      /* (not used in LP64) */
#else
     MP_INTERRUPT   *mpApicInterruptTable;
#endif

     UINT32         mpApicItLoc;    /* mem location of mpApicInterruptTable */
     UINT32         mpApicItSize;   /* size of mpApicInterruptTable */

     /* bus routing table */

     UINT32         mpApicNbus;     /* number of buses (MP Table) */

#ifdef	_WRS_CONFIG_LP64
     UINT32         reserved4;      /* (not used in LP64) */
#else
     MP_BUS         *mpApicBusTable;
#endif	/* _WRS_CONFIG_LP64 */

     UINT32         mpApicBtLoc;    /* mem location of mpApicBusTable */
     UINT32         mpApicBtSize;   /* size of mpApicBusTable */

     /* NOTE: mploApicIndexTable, mpApicLaLoc, mpApicLaSize, mpCpuIndexTable,
      * and mpApicCpuCount are used under SMP and AMP, they are considered
      * RESERVED for future use under standard UP builds.
      */

     /* loApic Id translation */

#ifdef	_WRS_CONFIG_LP64
     UINT32         reserved5;      /* (not used in LP64) */
#else
     UINT8          *mploApicIndexTable;
#endif	/* _WRS_CONFIG_LP64 */

     UINT32         mpApicLaLoc;    /* mem location of mploApicIndexTable */
     UINT32         mpApicLaSize;   /* size of mploApicIndexTable */

     /* cpu Id translation */

     UINT8          mpCpuIndexTable[256];

     UINT32         mpApicCpuCount; /* CPU counter */
     UINT8          mpApicCpuBSP;   /* Boot Strap Processor localApicId */
    }MP_APIC_DATA;

/* MP Configuration Table Entries */

#define MP_ENTRY_CPU            0       /* Entry Type: CPU */
#define MP_ENTRY_BUS            1       /* Entry Type: BUS */
#define MP_ENTRY_IOAPIC         2       /* Entry Type: IO APIC */
#define MP_ENTRY_IOINTERRUPT    3       /* Entry Type: IO INT */
#define MP_ENTRY_LOINTERRUPT    4       /* Entry Type: LO INT */

/* Extended MP Configuration Table Entries */

#define EXT_MP_ENTRY_SASM       128 /* Entry Type: System Address Space Map */
#define EXT_MP_ENTRY_BHD        129 /* Entry Type: Bus Hierarchy Descriptor */
#define EXT_MP_ENTRY_CBASM      130 /* Entry Type: Comp Addr Space Modifier */

/* MP Configuration Table CPU Flags */

#define MP_CPU_FLAGS_BP         0x02

/* Local APIC global variables */

IMPORT UINT32 glbLoApicOldSvr;        /* original SVR */
IMPORT UINT32 glbLoApicOldLint0;      /* original LINT0 */
IMPORT UINT32 glbLoApicOldLint1;      /* original LINT1 */
IMPORT char * glbLoApicBaseAdrs;      /* Lo Apic Register Base address */
#ifdef _WRS_CONFIG_LP64
IMPORT char * glbLoApicIdAdrs;        /* Lo Apic ID register address */
#endif /* _WRS_CONFIG_LP64 */

#ifdef __cplusplus
}
#endif

#endif  /* __INCvxbMpAPic */
