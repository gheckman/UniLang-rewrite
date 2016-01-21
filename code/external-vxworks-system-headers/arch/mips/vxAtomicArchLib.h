/* vxAtomicArchLib.h - MIPS specific atomic library header */

/*
 * Copyright (c) 2006-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01k,22may10,gls  added vxAtomic32XXX_inline definitions for GCC
01j,28apr10,pad  Moved extern C statement after include statements.
01i,22mar10,dhy(slk)  delete a unused variable
01h,09jun09,slk  add gnu inline atomics
01g,15may09,gls  made memory barriers available in user space
01f,28apr09,cww  Add fixed size APIs
01e,15aug08,slk  add additional atomic inline operators
01d,16jun08,zl   use _WRS_BARRIER() for memory barrier implementations
01c,17jan08,gls  renamed inline routines
01b,14dec07,wap  Add inline versions of some vxAtomic functions
01a,21nov06,slk  Created
*/

#ifndef __INCvxAtomicArchLibh
#define __INCvxAtomicArchLibh

#include <arch/mips/vxAtomicArchLibCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

#if defined (__DCC__)

#define vxCas_inline vxAtomicCas_inline

__asm volatile BOOL vxAtomicCas_inline (atomic_t * address, 
					atomicVal_t old_value,
				  	atomicVal_t new_value)
{
% reg address; reg old_value; reg new_value; \
  lab vxCas1_inline, vxCas2_inline
vxCas1_inline:
	.set noreorder
	ll	t0, 0(address)
	bne	t0, old_value, vxCas2_inline
	li	v0, FALSE
	move	t1, new_value
	sc	t1, 0(address)
	beqz	t1, vxCas1_inline
	li	v0, FALSE
	li	v0, TRUE
	.set reorder
vxCas2_inline:
}

__asm volatile BOOL vxAtomic32Cas_inline (atomic32_t * address, 
					  atomic32Val_t old_value,
				  	  atomic32Val_t new_value)
{
% reg address; reg old_value; reg new_value; \
  lab vxCas1_inline, vxCas2_inline
vxCas1_inline:
	.set noreorder
	ll	t0, 0(address)
	bne	t0, old_value, vxCas2_inline
	li	v0, FALSE
	move	t1, new_value
	sc	t1, 0(address)
	beqz	t1, vxCas1_inline
	li	v0, FALSE
	li	v0, TRUE
	.set reorder
vxCas2_inline:
}

__asm volatile atomicVal_t vxAtomicSet_inline (atomic_t * address,
					       atomicVal_t value)
{
% reg address; reg value; \
  lab vxAtomicSet1_inline
	.set noreorder
	move	t0, value
vxAtomicSet1_inline:
	ll	v0, 0(address)
	sc	t0, 0(address)
	beqz	t0, vxAtomicSet1_inline
	move	t0, value
	.set reorder
}

__asm volatile atomic32Val_t vxAtomic32Set_inline (atomic32_t * address,
					       	   atomic32Val_t value)
{
% reg address; reg value; \
  lab vxAtomicSet1_inline
	.set noreorder
	move	t0, value
vxAtomicSet1_inline:
	ll	v0, 0(address)
	sc	t0, 0(address)
	beqz	t0, vxAtomicSet1_inline
	move	t0, value
	.set reorder
}

__asm volatile atomicVal_t vxAtomicGet_inline (atomic_t * address)
{
% reg address;
	lw	v0, 0(address)
}

__asm volatile atomic32Val_t vxAtomic32Get_inline (atomic32_t * address)
{
% reg address;
	lw	v0, 0(address)
}

__asm volatile atomicVal_t vxAtomicAnd_inline (atomic_t * address, 
					       atomicVal_t value)
{
% reg address; reg value; \
  lab vxAtomicAnd1_inline
vxAtomicAnd1_inline:
	.set noreorder
	ll	v0, 0(address)
	and	t0, value, v0
	sc	t0, 0(address)
	beqz	t0, vxAtomicAnd1_inline
	nop
	.set reorder
}

__asm volatile atomic32Val_t vxAtomic32And_inline (atomic32_t * address, 
					       atomic32Val_t value)
{
% reg address; reg value; \
  lab vxAtomicAnd1_inline
vxAtomicAnd1_inline:
	.set noreorder
	ll	v0, 0(address)
	and	t0, value, v0
	sc	t0, 0(address)
	beqz	t0, vxAtomicAnd1_inline
	nop
	.set reorder
}

__asm volatile atomicVal_t vxAtomicOr_inline (atomic_t * address, 
					      atomicVal_t value)
{
% reg address; reg value; \
  lab vxAtomicOr1_inline
vxAtomicOr1_inline:
	.set noreorder
	ll	v0, 0(address)
	or	t0, value, v0
	sc	t0, 0(address)
	beqz	t0, vxAtomicOr1_inline
	nop
	.set reorder
}

__asm volatile atomic32Val_t vxAtomic32Or_inline (atomic32_t * address, 
					       atomic32Val_t value)
{
% reg address; reg value; \
  lab vxAtomicOr1_inline
vxAtomicOr1_inline:
	.set noreorder
	ll	v0, 0(address)
	or	t0, value, v0
	sc	t0, 0(address)
	beqz	t0, vxAtomicOr1_inline
	nop
	.set reorder
}

__asm volatile atomicVal_t vxAtomicXor_inline (atomic_t * address, 
					       atomicVal_t value)
{
% reg address; reg value; \
  lab vxAtomicXor1_inline
vxAtomicXor1_inline:
	.set noreorder
	ll	v0, 0(address)
	xor	t0, value, v0
	sc	t0, 0(address)
	beqz	t0, vxAtomicXor1_inline
	nop
	.set reorder
}

__asm volatile atomic32Val_t vxAtomic32Xor_inline (atomic32_t * address, 
						   atomic32Val_t value)
{
% reg address; reg value; \
  lab vxAtomicXor1_inline
vxAtomicXor1_inline:
	.set noreorder
	ll	v0, 0(address)
	xor	t0, value, v0
	sc	t0, 0(address)
	beqz	t0, vxAtomicXor1_inline
	nop
	.set reorder
}

__asm volatile atomicVal_t vxAtomicNand_inline (atomic_t * address, 
					        atomicVal_t value)
{
% reg address; reg value; \
  lab vxAtomicNand1_inline
vxAtomicNand1_inline:
	.set noreorder
	ll	v0, 0(address)
	and	t0, value, v0
	not	t0
	sc	t0, 0(address)
	beqz	t0, vxAtomicNand1_inline
	nop
	.set reorder
}

__asm volatile atomic32Val_t vxAtomic32Nand_inline (atomic32_t * address, 
						    atomic32Val_t value)
{
% reg address; reg value; \
  lab vxAtomicNand1_inline
vxAtomicNand1_inline:
	.set noreorder
	ll	v0, 0(address)
	and	t0, value, v0
	not	t0
	sc	t0, 0(address)
	beqz	t0, vxAtomicNand1_inline
	nop
	.set reorder
}

__asm volatile atomicVal_t vxAtomicDec_inline (atomic_t * address)
{
% reg address; \
  lab vxAtomicDec1_inline
vxAtomicDec1_inline:
	.set noreorder
	ll	v0, 0(address)
	subu	t0, v0, 1
	sc	t0, 0(address)
	beqz	t0, vxAtomicDec1_inline
	nop
	.set reorder
}

__asm volatile atomic32Val_t vxAtomic32Dec_inline (atomic32_t * address)
{
% reg address; \
  lab vxAtomicDec1_inline
vxAtomicDec1_inline:
	.set noreorder
	ll	v0, 0(address)
	subu	t0, v0, 1
	sc	t0, 0(address)
	beqz	t0, vxAtomicDec1_inline
	nop
	.set reorder
}

__asm volatile atomicVal_t vxAtomicInc_inline (atomic_t * address)
{
% reg address; \
  lab vxAtomicInc1_inline
vxAtomicInc1_inline:
	.set noreorder
	ll	v0, 0(address)
	addu	t0, v0, 1
	sc	t0, 0(address)
	beqz	t0, vxAtomicInc1_inline
	nop
	.set reorder
}

__asm volatile atomic32Val_t vxAtomic32Inc_inline (atomic32_t * address)
{
% reg address; \
  lab vxAtomicInc1_inline
vxAtomicInc1_inline:
	.set noreorder
	ll	v0, 0(address)
	addu	t0, v0, 1
	sc	t0, 0(address)
	beqz	t0, vxAtomicInc1_inline
	nop
	.set reorder
}

__asm volatile atomicVal_t vxAtomicClear_inline (atomic_t * address)
{
% reg address; \
  lab vxAtomicClear1_inline
	.set noreorder
	move	t0, zero
vxAtomicClear1_inline:
	ll	v0, 0(address)
	sc	t0, 0(address)
	beqz	t0, vxAtomicClear1_inline
	move	t0, zero
	.set reorder
}

__asm volatile atomic32Val_t vxAtomic32Clear_inline (atomic32_t * address)
{
% reg address; \
  lab vxAtomicClear1_inline
	.set noreorder
	move	t0, zero
vxAtomicClear1_inline:
	ll	v0, 0(address)
	sc	t0, 0(address)
	beqz	t0, vxAtomicClear1_inline
	move	t0, zero
	.set reorder
}

__asm volatile atomicVal_t vxAtomicAdd_inline (atomic_t * address, 
					       atomicVal_t value)
{
% reg address; reg value; \
  lab vxAtomicAdd1_inline
vxAtomicAdd1_inline:
	.set noreorder
	ll	v0, 0(address)
	addu	t0, v0, value
	sc	t0, 0(address)
	beqz	t0, vxAtomicAdd1_inline
	nop
	.set reorder
}

__asm volatile atomic32Val_t vxAtomic32Add_inline (atomic32_t * address, 
					       atomic32Val_t value)
{
% reg address; reg value; \
  lab vxAtomicAdd1_inline
vxAtomicAdd1_inline:
	.set noreorder
	ll	v0, 0(address)
	addu	t0, v0, value
	sc	t0, 0(address)
	beqz	t0, vxAtomicAdd1_inline
	nop
	.set reorder
}

__asm volatile atomicVal_t vxAtomicSub_inline (atomic_t * address, 
					       atomicVal_t value)
{
% reg address; reg value; \
  lab vxAtomicSub1_inline
vxAtomicSub1_inline:
	.set noreorder
	ll	v0, 0(address)
	subu	t0, v0, value
	sc	t0, 0(address)
	beqz	t0, vxAtomicSub1_inline
	nop
	.set reorder
}

__asm volatile atomic32Val_t vxAtomic32Sub_inline (atomic32_t * address, 
					       atomic32Val_t value)
{
% reg address; reg value; \
  lab vxAtomicSub1_inline
vxAtomicSub1_inline:
	.set noreorder
	ll	v0, 0(address)
	subu	t0, v0, value
	sc	t0, 0(address)
	beqz	t0, vxAtomicSub1_inline
	nop
	.set reorder
}

#elif defined (__GNUC__)

#define vxCas_inline vxAtomicCas_inline

static __inline__ BOOL vxAtomicCas_inline(atomic_t * address, 
					  atomicVal_t old_value,
					  atomicVal_t new_value)
{
    int rtn;
    __asm__ (
            ".set noreorder   \n"
            "ll    %0, %1     \n" 
            "bne   %0, %2, 1f \n" 
            "move  %0, $0     \n" 
            "move  %0, %3     \n" 
            "sc    %0, %1     \n" 
            "beqz  %0, 1f     \n" 
            "move  %0, $0     \n" 
            "ori   %0, 1      \n" 
            "1:                \n" 
            ".set reorder     \n"
            : "=&r" (rtn), "+m" (*address)
            : "r" (old_value), "r" (new_value)  : "memory");
    return (rtn);
}

static __inline__ BOOL vxAtomic32Cas_inline(atomic_t * address, 
					    atomicVal_t old_value,
					    atomicVal_t new_value)
{
    int rtn;
    __asm__ (
            ".set noreorder   \n"
            "ll    %0, %1     \n" 
            "bne   %0, %2, 1f \n" 
            "move  %0, $0     \n" 
            "move  %0, %3     \n" 
            "sc    %0, %1     \n" 
            "beqz  %0, 1f     \n" 
            "move  %0, $0     \n" 
            "ori   %0, 1      \n" 
            "1:                \n" 
            ".set reorder     \n"
            : "=&r" (rtn), "+m" (*address)
            : "r" (old_value), "r" (new_value)  : "memory");
    return (rtn);
}

static __inline__ atomicVal_t vxAtomicGet_inline(atomic_t * address)
{
    int rtn;
    __asm__ ("lw  %0, %1" : "=r" (rtn) : "m" (*address) );
    return (rtn);
}

static __inline__ atomicVal_t vxAtomic32Get_inline(atomic_t * address)
{
    int rtn;
    __asm__ ("lw  %0, %1" : "=r" (rtn) : "m" (*address) );
    return (rtn);
}

static __inline__ atomicVal_t vxAtomicSet_inline(atomic_t * address,
                                                 atomicVal_t value)
{
    int rtn, tmp;
    __asm__ (
            ".set noreorder   \n"
            "move  %2, %3     \n" 
            "0: ll %0, %1     \n" 
            "sc    %2, %1     \n" 
            "beqz  %2, 0b     \n" 
            "move  %2, %3     \n" 
            ".set reorder     \n"
            : "=&r" (rtn), "+m" (*address), "=r" (tmp)  
            : "r" (value)  : "memory");
    return (rtn);
}

static __inline__ atomicVal_t vxAtomic32Set_inline(atomic_t * address,
						   atomicVal_t value)
{
    int rtn, tmp;
    __asm__ (
            ".set noreorder   \n"
            "move  %2, %3     \n" 
            "0: ll %0, %1     \n" 
            "sc    %2, %1     \n" 
            "beqz  %2, 0b     \n" 
            "move  %2, %3     \n" 
            ".set reorder     \n"
            : "=&r" (rtn), "+m" (*address), "=r" (tmp)  
            : "r" (value)  : "memory");
    return (rtn);
}

static __inline__ atomicVal_t vxAtomicAnd_inline(atomic_t * address,
                                                 atomicVal_t value)
{
    int rtn, tmp;
    __asm__ (
            ".set noreorder   \n"
            "0: ll %0, %1     \n" 
            "and   %2, %0, %3 \n" 
            "sc    %2, %1     \n" 
            "beqz  %2, 0b     \n" 
            "nop              \n" 
            ".set reorder     \n"
            : "=&r" (rtn), "+m" (*address), "=r" (tmp)  
            : "r" (value)  : "memory");
    return (rtn);
}

static __inline__ atomicVal_t vxAtomic32And_inline(atomic_t * address,
						   atomicVal_t value)
{
    int rtn, tmp;
    __asm__ (
            ".set noreorder   \n"
            "0: ll %0, %1     \n" 
            "and   %2, %0, %3 \n" 
            "sc    %2, %1     \n" 
            "beqz  %2, 0b     \n" 
            "nop              \n" 
            ".set reorder     \n"
            : "=&r" (rtn), "+m" (*address), "=r" (tmp)  
            : "r" (value)  : "memory");
    return (rtn);
}

static __inline__ atomicVal_t vxAtomicNand_inline(atomic_t * address,
                                                 atomicVal_t value)
{
    int rtn, tmp;
    __asm__ (
            ".set noreorder   \n"
            "0: ll %0, %1     \n" 
            "and   %2, %0, %3 \n" 
            "not   %2         \n" 
            "sc    %2, %1     \n" 
            "beqz  %2, 0b     \n" 
            "nop              \n" 
            ".set reorder     \n"
            : "=&r" (rtn), "+m" (*address), "=r" (tmp)  
            : "r" (value)  : "memory");
    return (rtn);
}

static __inline__ atomicVal_t vxAtomic32Nand_inline(atomic_t * address,
						    atomicVal_t value)
{
    int rtn, tmp;
    __asm__ (
            ".set noreorder   \n"
            "0: ll %0, %1     \n" 
            "and   %2, %0, %3 \n" 
            "not   %2         \n" 
            "sc    %2, %1     \n" 
            "beqz  %2, 0b     \n" 
            "nop              \n" 
            ".set reorder     \n"
            : "=&r" (rtn), "+m" (*address), "=r" (tmp)  
            : "r" (value)  : "memory");
    return (rtn);
}

static __inline__ atomicVal_t vxAtomicOr_inline(atomic_t * address,
                                                 atomicVal_t value)
{
    int rtn, tmp;
    __asm__ (
            ".set noreorder   \n"
            "0: ll %0, %1     \n" 
            "or    %2, %0, %3 \n" 
            "sc    %2, %1     \n" 
            "beqz  %2, 0b     \n" 
            "nop              \n" 
            ".set reorder     \n"
            : "=&r" (rtn), "+m" (*address), "=r" (tmp)  
            : "r" (value)  : "memory");
    return (rtn);
}

static __inline__ atomicVal_t vxAtomic32Or_inline(atomic_t * address,
						  atomicVal_t value)
{
    int rtn, tmp;
    __asm__ (
            ".set noreorder   \n"
            "0: ll %0, %1     \n" 
            "or    %2, %0, %3 \n" 
            "sc    %2, %1     \n" 
            "beqz  %2, 0b     \n" 
            "nop              \n" 
            ".set reorder     \n"
            : "=&r" (rtn), "+m" (*address), "=r" (tmp)  
            : "r" (value)  : "memory");
    return (rtn);
}

static __inline__ atomicVal_t vxAtomicXor_inline(atomic_t * address,
                                                 atomicVal_t value)
{
    int rtn, tmp;
    __asm__ (
            ".set noreorder   \n"
            "0: ll %0, %1     \n" 
            "xor   %2, %0, %3 \n" 
            "sc    %2, %1     \n" 
            "beqz  %2, 0b     \n" 
            "nop              \n" 
            ".set reorder     \n"
            : "=&r" (rtn), "+m" (*address), "=r" (tmp)  
            : "r" (value)  : "memory");
    return (rtn);
}

static __inline__ atomicVal_t vxAtomic32Xor_inline(atomic_t * address,
						   atomicVal_t value)
{
    int rtn, tmp;
    __asm__ (
            ".set noreorder   \n"
            "0: ll %0, %1     \n" 
            "xor   %2, %0, %3 \n" 
            "sc    %2, %1     \n" 
            "beqz  %2, 0b     \n" 
            "nop              \n" 
            ".set reorder     \n"
            : "=&r" (rtn), "+m" (*address), "=r" (tmp)  
            : "r" (value)  : "memory");
    return (rtn);
}

static __inline__ atomicVal_t vxAtomicDec_inline(atomic_t * address)
{
    int rtn, tmp;
    __asm__ (
            ".set noreorder   \n"
            "0: ll %0, %1     \n" 
            "addiu  %2, %0, -1 \n" 
            "sc    %2, %1     \n" 
            "beqz  %2, 0b     \n" 
            "nop              \n" 
            ".set reorder     \n"
            : "=&r" (rtn), "+m" (*address), "=r" (tmp)  : : "memory");
    return (rtn);
}

static __inline__ atomicVal_t vxAtomic32Dec_inline(atomic_t * address)
{
    int rtn, tmp;
    __asm__ (
            ".set noreorder   \n"
            "0: ll %0, %1     \n" 
            "addiu  %2, %0, -1 \n" 
            "sc    %2, %1     \n" 
            "beqz  %2, 0b     \n" 
            "nop              \n" 
            ".set reorder     \n"
            : "=&r" (rtn), "+m" (*address), "=r" (tmp)  : : "memory");
    return (rtn);
}

static __inline__ atomicVal_t vxAtomicInc_inline(atomic_t * address)
{
    int rtn, tmp;
    __asm__ (
            ".set noreorder   \n"
            "0: ll %0, %1     \n" 
            "addiu  %2, %0, 1  \n" 
            "sc    %2, %1     \n" 
            "beqz  %2, 0b     \n" 
            "nop              \n" 
            ".set reorder     \n"
            : "=&r" (rtn), "+m" (*address), "=r" (tmp)  : : "memory");
    return (rtn);
}

static __inline__ atomicVal_t vxAtomic32Inc_inline(atomic_t * address)
{
    int rtn, tmp;
    __asm__ (
            ".set noreorder   \n"
            "0: ll %0, %1     \n" 
            "addiu  %2, %0, 1  \n" 
            "sc    %2, %1     \n" 
            "beqz  %2, 0b     \n" 
            "nop              \n" 
            ".set reorder     \n"
            : "=&r" (rtn), "+m" (*address), "=r" (tmp)  : : "memory");
    return (rtn);
}

static __inline__ atomicVal_t vxAtomicClear_inline(atomic_t * address)
{
    int rtn, tmp;
    __asm__ (
            ".set noreorder   \n"
            "move  %2, $0     \n" 
            "0: ll %0, %1     \n" 
            "sc    %2, %1     \n" 
            "beqz  %2, 0b     \n" 
            "move  %2, $0     \n" 
            ".set reorder     \n"
            : "=&r" (rtn), "+m" (*address), "=r" (tmp)  : : "memory");
    return (rtn);
}

static __inline__ atomicVal_t vxAtomic32Clear_inline(atomic_t * address)
{
    int rtn, tmp;
    __asm__ (
            ".set noreorder   \n"
            "move  %2, $0     \n" 
            "0: ll %0, %1     \n" 
            "sc    %2, %1     \n" 
            "beqz  %2, 0b     \n" 
            "move  %2, $0     \n" 
            ".set reorder     \n"
            : "=&r" (rtn), "+m" (*address), "=r" (tmp)  : : "memory");
    return (rtn);
}

static __inline__ atomicVal_t vxAtomicAdd_inline(atomic_t * address,
                                                 atomicVal_t value)
{
    int rtn, tmp;
    __asm__ (
            ".set noreorder   \n"
            "0: ll %0, %1     \n" 
            "addu   %2, %0, %3 \n" 
            "sc    %2, %1     \n" 
            "beqz  %2, 0b     \n" 
            "nop              \n" 
            ".set reorder     \n"
            : "=&r" (rtn), "+m" (*address), "=r" (tmp)  
            : "r" (value)  : "memory");
    return (rtn);
}

static __inline__ atomicVal_t vxAtomic32Add_inline(atomic_t * address,
						   atomicVal_t value)
{
    int rtn, tmp;
    __asm__ (
            ".set noreorder   \n"
            "0: ll %0, %1     \n" 
            "addu   %2, %0, %3 \n" 
            "sc    %2, %1     \n" 
            "beqz  %2, 0b     \n" 
            "nop              \n" 
            ".set reorder     \n"
            : "=&r" (rtn), "+m" (*address), "=r" (tmp)  
            : "r" (value)  : "memory");
    return (rtn);
}

static __inline__ atomicVal_t vxAtomicSub_inline(atomic_t * address,
                                                 atomicVal_t value)
{
    int rtn, tmp;
    __asm__ (
            ".set noreorder   \n"
            "0: ll %0, %1     \n" 
            "subu   %2, %0, %3 \n" 
            "sc    %2, %1     \n" 
            "beqz  %2, 0b     \n" 
            "nop              \n" 
            ".set reorder     \n"
            : "=&r" (rtn), "+m" (*address), "=r" (tmp)  
            : "r" (value)  : "memory");
    return (rtn);
}

static __inline__ atomicVal_t vxAtomic32Sub_inline(atomic_t * address,
						   atomicVal_t value)
{
    int rtn, tmp;
    __asm__ (
            ".set noreorder   \n"
            "0: ll %0, %1     \n" 
            "subu   %2, %0, %3 \n" 
            "sc    %2, %1     \n" 
            "beqz  %2, 0b     \n" 
            "nop              \n" 
            ".set reorder     \n"
            : "=&r" (rtn), "+m" (*address), "=r" (tmp)  
            : "r" (value)  : "memory");
    return (rtn);
}

#else

#define vxCas_inline		vxAtomicCas
#define vxAtomicCas_inline	vxAtomicCas
#define vxAtomic32Cas_inline	vxAtomic32Cas
#define vxAtomicAdd_inline	vxAtomicAdd
#define vxAtomic32Add_inline	vxAtomic32Add
#define vxAtomicSub_inline	vxAtomicSub
#define vxAtomic32Sub_inline	vxAtomic32Sub
#define vxAtomicInc_inline	vxAtomicInc
#define vxAtomic32Inc_inline	vxAtomic32Inc
#define vxAtomicDec_inline	vxAtomicDec
#define vxAtomic32Dec_inline	vxAtomic32Dec
#define vxAtomicSet_inline	vxAtomicSet
#define vxAtomic32Set_inline	vxAtomic32Set
#define vxAtomicClear_inline	vxAtomicClear
#define vxAtomic32Clear_inline	vxAtomic32Clear
#define vxAtomicGet_inline    	vxAtomicGet
#define vxAtomic32Get_inline    vxAtomic32Get
#define vxAtomicAnd_inline      vxAtomicAnd
#define vxAtomic32And_inline    vxAtomic32And
#define vxAtomicNand_inline     vxAtomicNand
#define vxAtomic32Nand_inline   vxAtomic32Nand
#define vxAtomicOr_inline       vxAtomicOr
#define vxAtomic32Or_inline     vxAtomic32Or
#define vxAtomicXor_inline      vxAtomicXor
#define vxAtomic32Xor_inline    vxAtomic32Xor

#endif /* _VX_TOOL_FAMILY */

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxAtomicArchLibh */
