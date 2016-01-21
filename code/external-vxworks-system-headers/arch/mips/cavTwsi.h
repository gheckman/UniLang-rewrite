/* cavTwsi.h -  Cavium Twsi Support Routines */

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
01d,09dec11,x_f  add functions declaration for CN68XX
01c,05oct10,d_c  Change ull to ULL to be Diab compatible
01b,21sep10,d_c  correct typo
01a,14sep10,rlg  Written
*/

/*
DESCRIPTION

This file declares macros, typedefs, and prototypes for general,
non-device-specific access routines for Cavium hardware.

*/

#ifndef __INCcavTwsih
#define __INCcavTwsih

#ifdef __cplusplus
extern "C" {
#endif


/* Some TWSI register bits */

#define TWS_SW_TWSI_V (0x8000000000000000ULL) /* Valid - clears on complete */
#define TWS_SW_TWSI_R (0x0100000000000000ULL) /* Read / Result */

#define TWS_SW_TWSI_OP_SHIFT	(57)
#define TWS_SW_TWSI_OP(x) (((uint64_t)(x)) << TWS_SW_TWSI_OP_SHIFT)

#define TWS_SW_TWSI_OP0 (0x1ULL << 57)
#define TWS_SW_TWSI_OP1 (0x1ULL << 58)  /* 10 bit */
#define TWS_SW_TWSI_OP2 (0x1ULL << 59)
#define TWS_SW_TWSI_OP3 (0x1ULL << 60)

#define TWS_SW_TWSI_A_SHIFT  (40)
#define TWS_SW_TWSI_A(x)  (((uint64_t)x) << TWS_SW_TWSI_A_SHIFT)

#define TWS_SW_TWSI_IA_SHIFT  (35)
#define TWS_SW_TWSI_IA(x) (((uint64_t)x) << TWS_SW_TWSI_IA_SHIFT)

#define TWS_SW_TWSI_EOP_IA_SHIFT (32)
#define TWS_SW_TWSI_EOP_IA(x) (((uint64_t)x) << TWS_SW_TWSI_EOP_IA_SHIFT)

/* functions */

extern int cavTwsiRead(uint8_t, uint8_t);
extern int cavTwsiWrite(uint8_t, uint8_t, uint8_t);
extern int cavTwsixReadIa(int, uint8_t, uint16_t, int, int, uint64_t *);
extern int cavTwsixWriteIa(int, uint8_t, uint16_t, int, int, uint64_t);
extern int cavTwsiSetAddr16(uint8_t, uint16_t);
extern int cavTwsiRead8_curAddr(uint8_t);
extern int cavTwsiRead8(uint8_t, uint16_t);
extern int cavTwsiRead16_curAddr(uint8_t);
extern int cavTwsiRead16(uint8_t, uint16_t);
extern int cavTwsiWrite16(uint8_t, uint16_t, uint16_t);
extern void cavTwsiLock(void);
extern void cavTwsiUnlock(void);
extern void cavTwsiSemCreate(void);

#ifdef __cplusplus
}
#endif

#endif /* __INCcavTwsih */
