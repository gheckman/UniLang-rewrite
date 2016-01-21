/* instrx86_64.h - header for x86_64 instruction fields */

/*
 * Copyright (c) 2004,2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01d,20sep10,scm  add additional trc/dbg constants...
01c,01apr10,scm  update instruction codes...
01b,01jun09,scm  add REX and RIP idents...
01a,26apr04,jmp  created from target/h/dbgI86Lib.h
*/

/*
 * WARNING: This file is shared between i86 and VxSim/i86 arches,
 *	    and between Kernel and User sides.
 *	    Please make sure that any modifications to this file
 *	    does not break other arches.
 */

#ifndef __INCinstrI86h
#define __INCinstrI86h

/* defines */

#define ADDI08_0            (0x83)
#define ADDI08_1            (0xc4)
#define ADDI32_0            (0x81)
#define ADDI32_1            (0xc4)
#define ADD_EAX             (0x01)
#define SUB_EAX             (0x29)
#define INC_EDX             (0xff)
#define LEAD08_0            (0x8d)
#define LEAD08_1            (0x64)
#define LEAD08_2            (0x24)
#define LEAD32_0            (0x8d)
#define LEAD32_1            (0xa4)
#define LEAD32_2            (0x24)
#define JMPD08              (0xeb)
#define JMPD32              (0xe9)
#define ENTER               (0xc8)
#define SC_PUSH             (0x68)
#define PUSH_EBX            (0x53)
#define POP_EBX             (0x5b)
#define POP_EBP             (0x5d)
#define POP_REG             (0x50)
#define PUSH_EBP            (0x55)
#define PUSH_ESI            (0x56)
#define MOV_EAX             (0x89)
#define MOV_EDI             (0xbf)
#define MOV_ESP0            (0x89)
#define MOV_ESP1            (0xe5)
#define MOV_ESP_ESI         (0xe689)
#define MOV_RIP             (0x8b)
#define CMP1_EAX            (0x39)
#define CMP2_EAX            (0x38)
#define LEAVE               (0xc9)
#define RET                 (0xc3)
#define RETADD              (0xc2)
#define REX_PRE             (0x40)
#define REX_PRE_B           (0x41)
#define REX_PRE_X           (0x42)
#define REX_PRE_R           (0x44)
#define REX_PRE_W           (0x48)
#define RIP_REL             (0x05)
#define SC_CALL0            (0xff)
#define SC_CALL1            (0x1c)
#define SC_CALL2            (0x25)
#define CALL_DIR            (0xe8)
#define CALL_INDIR0         (0xff)
#define CALL_INDIR1         (0x10)
#define CALL_INDIR_REG_EAX  (0xd0)
#define CALL_INDIR_REG_ECX  (0xd1)
#define CALL_INDIR_REG_EDX  (0xd2)
#define CALL_INDIR_REG_EBX  (0xd3)
#define MOV_ECX             (0x0d8b)
#define MOV_EDX             (0x158b)
#define MOV_EBP_ESP         (0xe589)

#define ADDI08_0_MASK       (0xff)
#define ADDI08_1_MASK       (0xff)
#define ADDI32_0_MASK       (0xff)
#define ADDI32_1_MASK       (0xff)
#define ADD_MASK            (0xff)
#define SUB_MASK            (0xff)
#define INC_MASK            (0xff)
#define LEAD08_0_MASK       (0xff)
#define LEAD08_1_MASK       (0xff)
#define LEAD08_2_MASK       (0xff)
#define LEAD32_0_MASK       (0xff)
#define LEAD32_1_MASK       (0xff)
#define LEAD32_2_MASK       (0xff)
#define JMPD08_MASK         (0xff)
#define JMPD32_MASK         (0xff)
#define ENTER_MASK          (0xff)
#define POP_EBX_MASK        (0xff)
#define POP_EBP_MASK        (0xff)
#define POP_REG_MASK        (0xff)
#define SC_PUSH_MASK        (0xff)
#define PUSH_EBX_MASK       (0xff)
#define PUSH_EBP_MASK       (0xff)
#define PUSH_ESI_MASK       (0xff)
#define MOV_MASK            (0xff)
#define MOV_ESP0_MASK       (0xff)
#define MOV_ESP1_MASK       (0xff)
#define MOV_ESP_ESI_MASK    (0xffff)
#define MOV_RIP_MASK        (0xff)
#define CMP_MASK            (0xff)
#define LEAVE_MASK          (0xff)
#define RET_MASK            (0xff)
#define RETADD_MASK         (0xff)
#define REX_PRE_MASK        (0xff)
#define RIP_REL_MASK        (0xff)
#define SC_CALL_MASK        (0xff)
#define CALL_DIR_MASK       (0xff)
#define CALL_INDIR0_MASK    (0xff)
#define CALL_INDIR1_MASK    (0x38)
#define CALL_INDIR_REG_MASK (0xdf)
#define MOV_ECX_MASK        (0xffff)
#define MOV_EDX_MASK        (0xffff)
#define MOV_EBP_ESP_MASK    (0xffff)

#endif	/* __INCinstrx86_64h */
