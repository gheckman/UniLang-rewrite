/* vxAtomicArchLibCommon.h - ARM specific atomic library header */

/*
 * Copyright (c) 2009-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01g,18may12,j_b  add support for ARMARCH7M
01f,04mar11,j_b  replace hardcoded DMB, DSB opcodes after compiler fix
01e,12jan11,jdw  Fix inline assembly opcodes for T2 (WIND00249791)
01d,21oct10,j_b  add memory barrier support for ARMv7
01c,07jun09,kk   add VX_INSTR_BARRIER() back
01b,05jun09,kk   move inlines from vxAtomicArchLib.h to here
01a,17may09,gls  written.
*/

#ifndef __INCvxAtomicArchLibCommonh
#define __INCvxAtomicArchLibCommonh

#ifdef __cplusplus
extern "C" {
#endif

/* Remove this line when all arch implement memory barrier API */

#define _WRS_ARCH_SUPPORTS_MEM_BARRIER

/*
 * ARM architecture 6 and later defines two kinds of memory barriers:
 *  - Data Synchronization Barrier (DSB)
 *  - Data Memory Barrier (DMB)
 *
 * DMB is enough for read/write memory barrier.
 */

#if (CPU == ARMARCH6) || (CPU == ARMARCH7) || \
    (CPU == ARMARCH7_T2) || (CPU == ARMARCH7M)

#  if (CPU == ARMARCH6)
/* ARMARCH6 provides memory barrier operations via system control processor */

#    if defined (__DCC__)

__asm volatile void __dmb ()
{
! "r0"
	mov	r0, #0
	mcr	p15, 0, r0, c7, c10, 5
}

__asm volatile void __dsb ()
{
! "r0"
	mov	r0, #0
	mcr	p15, 0, r0, c7, c10, 4
}

#    elif defined (__GNUC__)

static __inline__ void __dmb (void)
    {
    int sbz = 0;
    __asm__ volatile (
	"mcr	p15, 0, %0, c7, c10, 5"
        : /* no output */
        : "r" (sbz)
        : "memory");
    }

static __inline__ void __dsb (void)
    {
    int sbz = 0;
    __asm__ volatile (
	"mcr	p15, 0, %0, c7, c10, 4"
        : /* no output */
        : "r" (sbz)
        : "memory");
    }

#    else  /* !__DCC_ && !__GNUC__ */
#error "error!!! unsupported compiler!!!"
#    endif  /* __DCC__ */

#  elif (CPU == ARMARCH7) || (CPU == ARMARCH7_T2) || \
        (CPU == ARMARCH7M)

/* ARMARCH7 provides memory barrier instructions */

#    if defined (__DCC__)

	__asm volatile void __dmb ()
{
	DMB
}

__asm volatile void __dsb ()
{
	DSB
}

#    elif defined (__GNUC__)

static __inline__ void __dmb (void)
    {
    __asm__ volatile (
	"dmb"
        : /* no output */
        : /* no input */
        : "memory");
    }

static __inline__ void __dsb (void)
    {
    __asm__ volatile (
	"dsb"
        : /* no output */
        : /* no input */
        : "memory");
    }

#    else  /* !__DCC_ && !__GNUC__ */
#error "error!!! unsupported compiler!!!"
#    endif  /* __DCC__ */

#  endif  /* (CPU == ARMARCH6) */

#define VX_MEM_BARRIER_R()	__dmb()
#define VX_MEM_BARRIER_W()	__dmb()
#define VX_MEM_BARRIER_RW()	__dmb()
#define VX_INSTR_BARRIER()	__dmb()

#define VX_SYNC_BARRIER()	__dsb()

#else	/* (CPU == ARMARCH6) || (CPU == ARMARCH7) || (CPU == ARMARCH7_T2) */

#define VX_MEM_BARRIER_R()	_WRS_ASM("NOP")
#define VX_MEM_BARRIER_W()	_WRS_ASM("NOP")
#define VX_MEM_BARRIER_RW()	_WRS_ASM("NOP")
#define VX_INSTR_BARRIER()	_WRS_ASM("NOP")

#define VX_SYNC_BARRIER()	_WRS_ASM("NOP")

#endif	/* (CPU == ARMARCH6) || (CPU == ARMARCH7) || (CPU == ARMARCH7_T2) */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxAtomicArchLibCommonh */
