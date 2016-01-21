/* mcfI2c.h - coldfire I2C device header */

/*
 * Copyright 2007, 2008 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,06feb08,rec  change CAST_M5208 macros to more generic type
01a,14dec07,rec	 created
*/

#ifndef __INCmcfI2ch
#define __INCmcfI2ch

/* register offsets */

#define MCF_I2C_I2AR_OFF    0x00
#define MCF_I2C_I2FDR_OFF   0x04
#define MCF_I2C_I2CR_OFF    0x08
#define MCF_I2C_I2SR_OFF    0x0C
#define MCF_I2C_I2DR_OFF    0x10

/* Register read/write macros */

#define MCF_I2C_I2AR	  (CAST_MCF_VOLPTR( UINT8 )(MCF_I2C_BASE + \
                                MCF_I2C_I2AR_OFF))
#define MCF_I2C_I2FDR	  (CAST_MCF_VOLPTR( UINT8 )(MCF_I2C_BASE + \
                                MCF_I2C_I2FDR_OFF))
#define MCF_I2C_I2CR	  (CAST_MCF_VOLPTR( UINT8 )(MCF_I2C_BASE + \
                                MCF_I2C_I2CR_OFF))
#define MCF_I2C_I2SR	  (CAST_MCF_VOLPTR( UINT8 )(MCF_I2C_BASE + \
                                MCF_I2C_I2SR_OFF))
#define MCF_I2C_I2DR	  (CAST_MCF_VOLPTR( UINT8 )(MCF_I2C_BASE + \
                                MCF_I2C_I2DR_OFF))

/* Bit definitions and macros for MCF_I2C_I2AR */

#define MCF_I2C_I2AR_ADR(x)	(((x)&0x7F)<<1)

/* Bit definitions and macros for MCF_I2C_I2FDR */

#define MCF_I2C_I2FDR_IC(x)	(((x)&0x3F)<<0)

/* Bit definitions and macros for MCF_I2C_I2CR */

#define MCF_I2C_I2CR_RSTA	(0x04)
#define MCF_I2C_I2CR_TXAK	(0x08)
#define MCF_I2C_I2CR_MTX	(0x10)
#define MCF_I2C_I2CR_MSTA	(0x20)
#define MCF_I2C_I2CR_IIEN	(0x40)
#define MCF_I2C_I2CR_IEN	(0x80)

/* Bit definitions and macros for MCF_I2C_I2SR */

#define MCF_I2C_I2SR_RXAK	(0x01)
#define MCF_I2C_I2SR_IIF	(0x02)
#define MCF_I2C_I2SR_SRW	(0x04)
#define MCF_I2C_I2SR_IAL	(0x10)
#define MCF_I2C_I2SR_IBB	(0x20)
#define MCF_I2C_I2SR_IAAS	(0x40)
#define MCF_I2C_I2SR_ICF	(0x80)

/* Bit definitions and macros for MCF_I2C_I2DR */

#define MCF_I2C_I2DR_DATA(x)	(((x)&0xFF)<<0)


#endif

