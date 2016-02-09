/* vxbI8259IntCtlr.h - Intel 8259a PIC (Programmable Interrupt Controller) */

/*
* Copyright (C) 2007  Wind River Systems, Inc. All rights are reserved.
*
* The right to copy, distribute, modify, or otherwise make use
* of this software may be licensed only pursuant to the terms
* of an applicable Wind River license agreement.
*/

/*
modification history
--------------------
01a,11jun07,ami   added
*/

#ifndef	__INCvxbI8259IntCtlrh
#define	__INCvxbI8259IntCtlrh

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* ICW1 */

#define I8259_PIC_ICW4_NEEDED         0x01
#define I8259_PIC_N0_ICW4_NEEDED      0x00
#define I8259_PIC_SINGLE_MODE         0x02
#define I8259_PIC_CASCADE_MODE        0x00
#define I8259_PIC_INTERVAL_4          0x04
#define I8259_PIC_INTERVAL_8          0x00
#define I8259_PIC_LEVEL_TRIGGER       0x08
#define I8259_PIC_EDGE_TRIGGER        0x00
#define I8259_PIC_ICW1                0x10

/* ICW4 */

#define I8259_I8259_PIC_8086_MODE     0x01
#define I8259_I8259_PIC_8080_MODE     0x00
#define I8259_PIC_AUTO_EOI            0x02
#define I8259_PIC_NORMAL_EOI          0x00
#define I8259_PIC_NON_BUFFERED        0x04
#define I8259_PIC_BUFFERED_SLAVE      0x08
#define I8259_PIC_BUFFERED_MASTER     0x0C
#define I8259_PIC_SPECIAL_NESTED      0x10
#define I8259_PIC_NOT_SPECIAL_NESTED  0x00

/* Operational Command Word 1 */

#define I8259_PIC_MASK_ALL_INTR       0xFF

/* Operational Command Word 2 */

#define I8259_PIC_NONSPECIFIC_EOI     0x20
#define I8259_PIC_SPECIFIC_EOI        0x60
#define I8259_PIC_ROT_NONSPEC_EOI     0xA0
#define I8259_PIC_ROT_AUT_EOI_SET     0x80
#define I8259_PIC_ROT_AUT_EOI_CLR     0x00
#define I8259_PIC_ROT_SPEC_AUT_EOI    0xE0
#define I8259_PIC_SET_PRIORTY_CMD     0xC0
#define I8259_PIC_OCW2_NOP            0x40

/* Operational Command Word 3 */

#define I8259_PIC_RESET_SPECIAL_MASK  0x40
#define I8259_PIC_SET_SPECIAL_MASK    0x60
#define I8259_PIC_OCW3                0x08
#define I8259_PIC_POLL_CMD            0x04
#define I8259_PIC_NO_POLL_CMD         0x00
#define I8259_PIC_READ_IR_REG         0x02
#define I8259_PIC_READ_IS_REG         0x03
#define I8259_PIC_DISABLE_SMM         0x08
#define I8259_PIC_ENABLE_SMM          0x68

#define I8259_PORTB_OFFSET            0x1

#ifdef __cplusplus
}
#endif

#endif	/* __INCvxbI8259IntCtlrh */

