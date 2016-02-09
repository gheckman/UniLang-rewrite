/* octeonBoard.h - Board configuration file */

/*
* Copyright (c) 2008-2011 Wind River Systems, Inc.
*
* The right to copy, distribute, modify or otherwise make use
* of this software may be licensed only pursuant to the terms
* of an applicable Wind River license agreement.
*/

/*

modification history
--------------------
01j,20dec11,x_f  Add CN68XX board type
01i,05jan11,d_c  Defect WIND00249323 Fix WIND00249325 - configure PCIe bus
01h,09nov10,d_c  Remove definition of OCTEON_CACHE_ALIGN_SIZE.
                 It's redundant with respect to CVMX_CACHE_LINE_SIZE
                 in octeonMips64.h
01g,04sep10,d_c  Change CFG_I2C_EEPROM_ADDR for 63xx
01f,31aug10,rlg  addition of cn63xx defines
01e,26aug10,pgh  Removed octeon-model.h
01d,09mar09,j_z  add macros for 56xx and normalize file header
01c,24sep08,pgh  Fix copyright.
01b,12jul08,l_z  add macros for 50xx and normalize file header
01a,14may08,l_z  add macros for 58xx and normalize file header

DESCRIPTION

*/


#ifndef OCTEON_BOARD_H
#define OCTEON_BOARD_H

#define CONFIG_OCTEON        1

#define CAVIUM_BOARD_EBH3010        1
#define CAVIUM_BOARD_EBH3100        2
#define CAVIUM_BOARD_EBT3000        3
#define CAVIUM_BOARD_EBH50XX        4
#define CAVIUM_BOARD_EBH5020        5
#define CAVIUM_BOARD_EVB5860        6
#define CAVIUM_BOARD_EBH5600        7
#define CAVIUM_BOARD_EVB6300        8
#define CAVIUM_BOARD_EVB6800        9

#define CPU_CLOCK_RATE              (cavCpuClockRateGet())

#if OCTEON_BOARD == CAVIUM_BOARD_EBT3000
#define BOARD_REV_MAJOR             3
#define BOARD_REV_MINOR             1

#define DEFAULT_CPU_CLOCK_RATE      500000000

#define CFG_ATA_BASE_ADDR           (OCTEON_CF_COMMON_BASE_ADDR + 0x800)
#define CFG_ATA_DATA_OFFSET         0x400
#define CFG_ATA_REG_OFFSET          0

#define CFG_I2C_EEPROM_ADDR_LEN     2
#define CFG_I2C_EEPROM_ADDR         0x52

#endif /* OCTEON_BOARD == CAVIUM_BOARD_EBT3000 */ 


#if OCTEON_BOARD == CAVIUM_BOARD_EBH3010
#define BOARD_REV_MINOR             0
#define BOARD_REV_MAJOR             1

#define DEFAULT_CPU_CLOCK_RATE      500000000
#define CFG_ATA_BASE_ADDR           (OCTEON_CF_COMMON_BASE_ADDR + 0x800)
#define CFG_ATA_DATA_OFFSET         0x400
#define CFG_ATA_REG_OFFSET          0

#define CFG_I2C_EEPROM_ADDR_LEN     2
#define CFG_I2C_EEPROM_ADDR         0x56

#endif /* OCTEON_BOARD == CAVIUM_BOARD_EBH3010 */ 


#if OCTEON_BOARD == CAVIUM_BOARD_EBH3100
#define BOARD_REV_MINOR             0
#define BOARD_REV_MAJOR             1

#define DEFAULT_CPU_CLOCK_RATE      500000000

#define CFG_ATA_BASE_ADDR           (OCTEON_CF_COMMON_BASE_ADDR + 0x800)
#define CFG_ATA_DATA_OFFSET         0x400
#define CFG_ATA_REG_OFFSET          0

#define CFG_I2C_EEPROM_ADDR_LEN     2
#define CFG_I2C_EEPROM_ADDR         0x56

#endif /* OCTEON_BOARD == CAVIUM_BOARD_EBH3100 */ 


#if OCTEON_BOARD == CAVIUM_BOARD_EBH50XX
#define BOARD_REV_MINOR             0
#define BOARD_REV_MAJOR             1

#define DEFAULT_CPU_CLOCK_RATE      400000000

#define CFG_ATA_BASE_ADDR           (OCTEON_CF_COMMON_BASE_ADDR + 0x800)
#define CFG_ATA_DATA_OFFSET         0x400
#define CFG_ATA_REG_OFFSET          0

#define CFG_I2C_EEPROM_ADDR_LEN     2 
#define CFG_I2C_EEPROM_ADDR         0x56
                                      
#endif /* OCTEON_MODEL == OCTEON_CN50XX */


#if OCTEON_BOARD == CAVIUM_BOARD_EBH5020
#define BOARD_REV_MINOR             0
#define BOARD_REV_MAJOR             1

#define DEFAULT_CPU_CLOCK_RATE      400000000

#define CFG_ATA_BASE_ADDR           (OCTEON_CF_COMMON_BASE_ADDR + 0x800)
#define CFG_ATA_DATA_OFFSET         0x400
#define CFG_ATA_REG_OFFSET          0

#define CFG_I2C_EEPROM_ADDR_LEN     2
#define CFG_I2C_EEPROM_ADDR         0x56

#define PCI_IO_ADRS                 0x00001000
#define PCI_IO_SIZE                 0x08000000
#define PCI_IO16_SIZE               0x0

#define PCI_MEM_ADRS                0x80000000
#define PCI_MEM_SIZE                0x40000000

#define OCTEON_PCI_LAT_TIMER        0xff

#define I2C_RTC_ADDR                (0x68)

#endif /* OCTEON_BOARD == OCTEON_CN5020 */


#if OCTEON_BOARD == CAVIUM_BOARD_EBH5600
#define BOARD_REV_MAJOR             1
#define BOARD_REV_MINOR             1

#define DEFAULT_CPU_CLOCK_RATE      800000000

#define CFG_ATA_BASE_ADDR           (OCTEON_CF_COMMON_BASE_ADDR + 0x800)
#define CFG_ATA_DATA_OFFSET         0x400
#define CFG_ATA_REG_OFFSET          0

#define CFG_I2C_EEPROM_ADDR_LEN     2
#define CFG_I2C_EEPROM_ADDR         0x56

#define PCIE0_IO_ADRS               0x00001000
#define PCIE0_IO_SIZE               0x04000000
#define PCIE0_MEM_ADRS              0x80000000
#define PCIE0_MEM_SIZE              0x20000000

#define PCIE1_IO_ADRS               (PCIE0_IO_ADRS + PCIE0_IO_SIZE)
#define PCIE1_IO_SIZE               PCIE0_IO_SIZE
#define PCIE1_MEM_ADRS              (PCIE0_MEM_ADRS + PCIE0_MEM_SIZE)
#define PCIE1_MEM_SIZE              PCIE0_MEM_SIZE

#define I2C_RTC_ADDR                (0x68)

#endif /* OCTEON_BOARD == CAVIUM_BOARD_EBH5600 */


#if OCTEON_BOARD == CAVIUM_BOARD_EVB5860
#define BOARD_REV_MAJOR             3
#define BOARD_REV_MINOR             1

#define DEFAULT_CPU_CLOCK_RATE      800000000

#define CFG_ATA_BASE_ADDR           (OCTEON_CF_COMMON_BASE_ADDR + 0x800)
#define CFG_ATA_DATA_OFFSET         0x400
#define CFG_ATA_REG_OFFSET          0

#define CFG_I2C_EEPROM_ADDR_LEN     2
#define CFG_I2C_EEPROM_ADDR         0x52

#define I2C_RTC_ADDR                (0x68)

#endif /* OCTEON_BOARD == CAVIUM_BOARD_EVB5860 */

#if OCTEON_BOARD == CAVIUM_BOARD_EVB6300
#define BOARD_REV_MAJOR             1
#define BOARD_REV_MINOR             0

#define DEFAULT_CPU_CLOCK_RATE      800000000

#define CFG_ATA_BASE_ADDR           (OCTEON_CF_COMMON_BASE_ADDR + 0x800)
#define CFG_ATA_DATA_OFFSET         0x400
#define CFG_ATA_REG_OFFSET          0

#define CFG_I2C_EEPROM_ADDR_LEN     2

#define CFG_I2C_EEPROM_ADDR         0x56

#define PCIE0_IO_ADRS               0x00001000
#define PCIE0_IO_SIZE               0x04000000 /* 64M */

#define PCIE0_MEM_ADRS              0x80000000
#define PCIE0_MEM_SIZE              0x20000000 /* 512M */

#define PCIE1_IO_ADRS               (PCIE0_IO_ADRS + PCIE0_IO_SIZE)
#define PCIE1_IO_SIZE               PCIE0_IO_SIZE

#define PCIE1_MEM_ADRS              (PCIE0_MEM_ADRS + PCIE0_MEM_SIZE)
#define PCIE1_MEM_SIZE              PCIE0_MEM_SIZE

#define I2C_RTC_ADDR                (0x68)

#endif /* OCTEON_BOARD == CAVIUM_BOARD_EVB6300 */

#if OCTEON_BOARD == CAVIUM_BOARD_EVB6800
#define BOARD_REV_MAJOR             1
#define BOARD_REV_MINOR             0

#define DEFAULT_CPU_CLOCK_RATE      800000000

#define CFG_ATA_BASE_ADDR           (OCTEON_CF_COMMON_BASE_ADDR + 0x800)
#define CFG_ATA_DATA_OFFSET         0x400
#define CFG_ATA_REG_OFFSET          0

#define CFG_I2C_EEPROM_ADDR_LEN     2

#define CFG_I2C_EEPROM_ADDR         0x56

#define I2C_RTC_ADDR                (0x68)

#endif /* OCTEON_BOARD == CAVIUM_BOARD_EVB6800 */

/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */
#define CFG_MAX_FLASH_BANKS    1    /* max number of memory banks */
#define CFG_MAX_FLASH_SECT     (512)    /* max number of sectors on one chip */

#define PHYS_FLASH_1           0xbf400000 /* Flash Bank #1 */

#define    CFG_MONITOR_BASE    TEXT_BASE
#define    CFG_MONITOR_LEN     (192 << 10)

#define CFG_INIT_SP_OFFSET     0x400000

#define CFG_FLASH_BASE         PHYS_FLASH_1
#define CFG_FLASH_PROTECT_LEN  0x80000  /* protect low 512K */

#define CFG_FLASH_CFI          1
#define CFG_FLASH_CFI_DRIVER   1


#endif /* OCTEON_BOARD_H */
