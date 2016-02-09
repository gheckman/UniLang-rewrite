/* efiVxWorks.h - Header file for the EFI OS loader application */

/*
 * Copyright (c) 2007, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

/*
modification history
--------------------
01b,29apr10,pad  Moved extern C statement after include statements.
01a,15Oct07,d_z  created
*/

#ifndef VXWORKS_OSLOADER_INCLUDED
#define VXWORKS_OSLOADER_INCLUDED


/* These files are from EFI Sample implementation 1.10.14.62 or later
 * They need to be in the VxWorks build tree.
 */
#include "efidef.h"
#include "efiapi.h" /* definitions for structures etc, esp runtime services table */

#ifdef __cplusplus
extern "C" {
#endif

/* OS Loader application revision level */
#define VXWORKS_OS_LOADER_MAJOR_REV           1
#define VXWORKS_OS_LOADER_MINOR_REV           0

/* EFI/UEFI revision level contants */
#define VXWORKS_OS_LOADER_EFI_MAJOR_REV       1
#define VXWORKS_OS_LOADER_EFI_MINOR_REV       10

#define MAX_VXWORKS_EFI_BANNER_OFFSET         200 /* maximum bytes to examine in image for EFI string */

/* Constants for Stall routine during fast booting */
#define MICROSECONDS_PER_SECOND               1000000 /* count to convert for pause routine */
#define VXWORKS_OS_LOADER_PAUSE_SECS          5 /* 5 seconds */
#define VXWORKS_OS_LOADER_ERROR_PAUSE_SECS    10 /* 10 seconds */

/* Defaults */

#define VXWORKS_DEFAULT_BOOTROM_FILE    L"BOOTROM_UEFI.BIN"

/* buffer space needed contants */
#define NUM_BOOTROM_IMAGE_BUFFER_PAGES        256
#define NUM_EFI_DATA_BLOCK_BUFFER_PAGES       10
#define NUM_VXWORKS_BUFFER_PAGES        (NUM_BOOTROM_IMAGE_BUFFER_PAGES + NUM_EFI_DATA_BLOCK_BUFFER_PAGES)



/* derive the size of the header in units of 8 bytes (64 bits) */
#define VXWORKS_OS_MEMORY_HEADER_8BYTE_SIZE ((sizeof(VxWorksOSLoaderMemoryMapHeader)+7)&0xFFF8)

/* OS loader private memory type definitions
   This will show "WRS" as a string in the memory type field.
 */
#define VXWORKS_OS_LOADER_KERNELCODE_MEM_TYPE  \
        ((UINT32) 0x80000000 | (((UINT32) 'S') << 16) | (((UINT32) 'R') << 8) | (UINT32) 'W')
#define VXWORKS_OS_LOADER_DATA_MEM_TYPE  \
        ((UINT32) 0x81000000 | (((UINT32) 'S') << 16) | (((UINT32) 'R') << 8) | (UINT32) 'W')

#define VXWORKS_GUID    \
  { 0xd1e731a0, 0x2fa6, 0x11cf, {0x8a, 0x33, 0x00, 0x80, 0xc8, 0xab, 0x7e, 0x9c} }

#define NUM_VXWORKS_HEADER_FIELDS 11

/* intermediate sizing so this is always an even multiple of 32 bit fields */
#define NUM_VXWORKS_HEADER_FIELDS_EVEN (NUM_VXWORKS_HEADER_FIELDS + (NUM_VXWORKS_HEADER_FIELDS & 1))

/*
 * this is the memory data block header.  It describes the memory data block contents
 * and provides error-checking mechanisms to ensure only a valid memory block is used.
 * It also describes the virtual map that VxWorks may generate if virtual mapping is 
 * being used in the OS.  This virtual map will be constructed after the UEFI memory
 * map in the same buffer, and is used to call SetVirtualAddressMap().
 *
 * NOTE: New fields should only be added at the end of this structure in order to 
 * preserve backward compatibility.
 */
typedef struct VxWorksOSLoaderMemoryMapHeader_struct {
    UINT32                  HeaderSize; /* size of this header in bytes */
    UINT32                  NumberofFields; /* number of fields after the FieldWidths array */
    UINT32                  FieldWidths[NUM_VXWORKS_HEADER_FIELDS_EVEN]; /* size in bits of each field after this point */
    EFI_GUID                VxWorksGUID; /* Identify this as Vxworks table */
    EFI_SYSTEM_TABLE        *pSystemTable;  /* pointer to the system table, with runtime services etc */
    UINT32                  pad1; /* pad to align 64 bit pointer value */
    EFI_PHYSICAL_ADDRESS    PhysMemoryMapBuffer;
    UINTN                   PhysMemoryMapBufferSize; /* in bytes */
    EFI_MEMORY_DESCRIPTOR   *MemoryMapBuffer;    /* virtual address */
    UINTN                   MemoryMapBufferSize; /* in bytes */
    UINTN                   MapKey;              /* key returned by GetMemoryMap() */
    UINTN                   DescriptorSize;      /* size returned by GetMemoryMap() */
    UINT32                  DescriptorVersion;   /* version returned by GetMemoryMap() */
    EFI_MEMORY_DESCRIPTOR   *VxWorksVirtualMap;       /* used by VxWorks UEFI routines */
    UINTN                   VxWorksVirtualMapEntries; /* used by VxWorks UEFI routines */

    /* end of REVISION 1.0 VxWorksOSLoaderMemoryMapHeader.  Add fields below! */

        /* memory map contents will be after this in RAM, possibly with space 
           between so that it is aligned on an 8 byte boundary */
    } VxWorksOSLoaderMemoryMapHeader;

#ifdef INCLUDE_VXWORKS_OS_LOADER_MEMTYPES
static UEFI_CHARSIZE *OsLoaderMemoryTypeDesc[EfiMaxMemoryType+2]  = {
            UEFI_CHARSYM("reserved  "),
            UEFI_CHARSYM("LoaderCode"),
            UEFI_CHARSYM("LoaderData"),
            UEFI_CHARSYM("BS_code   "),
            UEFI_CHARSYM("BS_data   "),
            UEFI_CHARSYM("RT_code   "),
            UEFI_CHARSYM("RT_data   "),
            UEFI_CHARSYM("available "),
            UEFI_CHARSYM("Unusable  "),
            UEFI_CHARSYM("ACPI_recl "),
            UEFI_CHARSYM("ACPI_NVS  "),
            UEFI_CHARSYM("MemMapIO  "),
            UEFI_CHARSYM("MemPortIO "),
            UEFI_CHARSYM("PAL_code  "),
            UEFI_CHARSYM("VxWKernCod"),
            UEFI_CHARSYM("VxWLdrData")
    };
#endif /* #ifdef INCLUDE_VXWORKS_OS_LOADER_MEMTYPES */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VXWORKS_OSLOADER_INCLUDED */
