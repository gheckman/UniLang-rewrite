/* flash28.h - header for 28FXXX FLASH memory devices */

/*
Copyright (c) 1994, 1996-1997, 1999-2001, 2005-2006 Wind River Systems, Inc.

The right to copy, distribute, modify or otherwise make use
of this software may be licensed only pursuant to the terms
of an applicable Wind River license agreement.
*/

/*
modification history
--------------------
01k,23jan06,j_b  add FLASH_28F800/160/320/640C3 support
01j,28nov05,j_b  add FLASH28_CMD_LOCK block lock/unlock cmds and K3/K18 parts.
01i,15feb01,frf  added intel Flash 28F128J3A,28F320J3A,28F640J3A support.
01h,01feb00,jpd  added defs for Intel 28F320, Sharp 28F160S3. SPR 31293
01e,28aug98,jpd  added 28F016 defs, including FLASH_WIDTH_SPECIAL_2 version.
01f,03aug99,dat  merge from HIT group T2 branch
01e,04may99,cn   added 28F016 definitions.
01d,04jul97,jpd  added 28F008 definitions.
01c,26jan96,dzb  added casts for CMD constants.
01b,24feb94,dzb  added device codes for different flash devices.
01a,10feb94,dzb  created.
*/

/*
DESCRIPTION
This file contains header information for 28F0X0 FLASH memory devices.
*/

#ifndef __INCflash28h
#define __INCflash28h

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define FLASH28_CMD_READ_MEM        (FLASH_DEF) 0x00000000
#define FLASH28_CMD_READ_ID     (FLASH_DEF) 0x90909090
#define FLASH28_CMD_ERASE_SETUP     (FLASH_DEF) 0x20202020
#define FLASH28_CMD_ERASE       (FLASH_DEF) 0x20202020
#define FLASH28_CMD_ERASE_VERIFY    (FLASH_DEF) 0xa0a0a0a0
#define FLASH28_CMD_PROG_SETUP      (FLASH_DEF) 0x40404040
#define FLASH28_CMD_PROG_VERIFY     (FLASH_DEF) 0xc0c0c0c0
#define FLASH28_CMD_RESET       (FLASH_DEF) 0xffffffff
#define FLASH28_CMD_LOCK_SETUP      (FLASH_DEF) 0x60606060
#define FLASH28_CMD_LOCK            (FLASH_DEF) 0x01010101
#define FLASH28_CMD_UNLOCK          (FLASH_DEF) 0xD0D0D0D0
#define FLASH28F008_CMD_READ_STATUS (FLASH_DEF) 0x70707070
#define FLASH28F008_CMD_CLEAR_STATUS    (FLASH_DEF) 0x50505050
#define FLASH28F008_CMD_ERASE       (FLASH_DEF) 0xD0D0D0D0

#ifdef FLASH_WIDTH_SPECIAL_2
#define FLASH28F008_STAT_WSMS       (FLASH_DEF) 0x00800080
#else
#define FLASH28F008_STAT_WSMS       (FLASH_DEF) 0x80808080
#endif /* FLASH_WIDTH_SPECIAL_2 */
#define FLASH28F008_STAT_BWS        (FLASH_DEF) 0x10101010
#define FLASH28F008_STAT_EWS        (FLASH_DEF) 0x20202020

#define FLASH_28F256            0xa1        /* device code 28F256 */
#define FLASH_28F512            0x25        /* device code 28F512 */
#define FLASH_28F128J3A         0x18        /* device code 28F128J3 */
#define FLASH_28F640J3A         0x17        /* device code 28F640J3 */
#define FLASH_28F320J3A         0x16        /* device code 28F320J3 */
#define FLASH_28F010            0xa7        /* device code 28F010 */
#define FLASH_28F020            0x2a        /* device code 28F020 */
#define FLASH_28F008            0xa2        /* device code 28F008 */
#define FLASH_28F016            0xaa        /* device code 28F016 */
#define FLASH_28F160            0xd0        /* device code 28F160 */
#define FLASH_28F320            0xd4        /* device code 28F320 */
/*
 * Note: the following K3/K18/C3 family parts are 16-bit and have a prefix
 * of 0x88 in the upper byte (bits 8:15) of their ID, but are not required
 * to make them unique.
 */
#define FLASH_28F640K3          0x01        /* device code 28F640K3 */
#define FLASH_28F128K3          0x02        /* device code 28F128K3 */
#define FLASH_28F256K3          0x03        /* device code 28F640K3 */
#define FLASH_28F640K18         0x05        /* device code 28F640K18 */
#define FLASH_28F128K18         0x06        /* device code 28F128K18 */
#define FLASH_28F256K18         0x07        /* device code 28F640K18 */
#define FLASH_28F800C3T         0xC0        /* device code 28F800C3T */
#define FLASH_28F800C3B         0xC1        /* device code 28F800C3B */
#define FLASH_28F160C3T         0xC2        /* device code 28F160C3T */
#define FLASH_28F160C3B         0xC3        /* device code 28F160C3B */
#define FLASH_28F320C3T         0xC4        /* device code 28F320C3T */
#define FLASH_28F320C3B         0xC5        /* device code 28F320C3B */
#define FLASH_28F640C3T         0xCC        /* device code 28F640C3T */
#define FLASH_28F640C3B         0xCD        /* device code 28F640C3B */

#ifdef __cplusplus
}
#endif

#endif /* __INCflash28h */
