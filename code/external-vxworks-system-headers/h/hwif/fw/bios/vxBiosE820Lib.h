/* vxBiosE820Lib.h - Intel E820 BIOS memory map header */

/* 
 * Copyright (c) 2010, 2012 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,26nov12,yjw  move struct definition to this header file.
                 (WIND00380360)
01b,29jul10,pad  Moved extern C statement after include statements.
01a,28mar10,sem  written
*/

/*
DESCRIPTION
  Intel memory auto-size support using E820 BIOS memory map information.

*/

#ifndef __INCvxBiosE820Libh
#define __INCvxBiosE820Libh

#ifdef _WRS_CONFIG_LP64

#include <vmLib.h>

#endif /* _WRS_CONFIG_LP64 */

#ifdef __cplusplus
extern "C" {
#endif

/* E820 memory auto-size status codes */

#define BIOS_E820_MAP_OK              0x0 /* No map error detected */

#define BIOS_E820_MAP_SIG_ERR         0x1 /* "SMAP" signature not verified in BIOS output */

#define BIOS_E820_MAP_CF_ERR          0x2 /* Carry flag set on first E820 call - error */

#define BIOS_E820_MAP_SIZE_ERR        0x3 /* Invalid buffer size returned by BIOS */

#define BIOS_E820_MAP_ENTRY_ERR       0x4 /* Invalid entry count  */

#define BIOS_E820_MAP_ADR_ERR         0x5 /* Invalid final descriptor address pointer */

#define BIOS_E820_MAP_TYPE_ERR        0x6 /* Invalid descriptor type value */

#define BIOS_E820_MAP_LEN_ERR         0x7 /* Invalid descriptor length value */

#define BIOS_E820_MAP_RANGE_ERR       0x8 /* Invalid or conflicting address range */

#define BIOS_E820_MAP_SPACE_ERR       0x9 /* Insufficient table space available in sysPhysRamDesc */

/* E820 memory map types */

#define BIOS_E820_MEM_TYPE_UNDEFINED  0x0 /* Undefined memory type */            

#define BIOS_E820_MEM_TYPE_USABLE     0x1 /* Usable memory type */               

#define BIOS_E820_MEM_TYPE_RESERVED   0x2 /* Reserved memory type */             

#define BIOS_E820_MEM_TYPE_ACPI       0x3 /* ACPI memory type */                 

#define BIOS_E820_MEM_TYPE_NVS        0x4 /* ACPI NVS memory type */

#define BIOS_E820_MEM_TYPE_UNUSABLE   0x5 /* Unusable memory type */             

#define BIOS_E820_MEM_TYPE_DISABLED   0x6 /* Disabled memory type */             

#ifndef _ASMLANGUAGE

/* structure of the BIOS E820 map table info */

typedef struct bios_e820_tbl_info
    {
    unsigned int smap;    /* "SMAP" signature (eax register) at query return */
    unsigned int ebx;     /* contents of ebx register at query return */
    unsigned int ecx;     /* contents of ecx register at query return */
    unsigned int edx;     /* contents of edx register at query return */
    unsigned int adr;     /* final buffer address (edi register) at query return */
    unsigned int carry;   /* carry bit */
    unsigned int entries; /* entry count */
    unsigned int err;     /* error word */
    } BIOS_E820_TBL_INFO;

/* structure of an entry in the BIOS E820 map table */

typedef struct bios_e820_map_desc 
    {
    unsigned long long addr;    /* start of memory segment   */
    unsigned long long len;     /* length of memory segment  */
    unsigned int type;          /* type of memory segment    */
    } __attribute__((packed)) BIOS_E820_MAP_DESC;

extern STATUS vxBiosE820MapDescGet
    (
    unsigned int index,
    BIOS_E820_MAP_DESC *pMapDesc
    );

extern unsigned int vxBiosE820MapStatusGet (void);

extern void vxBiosE820MapShow (void);

#ifndef _WRS_CONFIG_LP64

/* forward declarations */

extern char * vxBiosE820MemTopPhys32 (void);

#else

extern STATUS vxBiosE820MapGet64 
    (
    PHYS_MEM_DESC *sysPhysRamDesc, 
    int sysPhysRamDescCount
    );
    
#endif /* !_WRS_CONFIG_LP64 */

#endif /* !_ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxBiosE820Libh */
