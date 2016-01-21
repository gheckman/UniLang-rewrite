/* vbiX86Arch.h - x86 architecture specific definitions */

/*
 * Copyright (c) 2009-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01q,26apr12,jjk  WIND00344535 - Fix build warnings
01q,17feb12,c_t  sync with HV 2.0 27-jan-12 DVD
01p,04apr11,jlv  Sync with HV 1.3 01-Apr-11(WIND00265419)
01o,08feb11,jlv  Sync with HV 1.3 04-Feb-11 DVD
01n,28dec10,jlv  Fix compiler warning with 64-bit build
01m,28sep10,jl   add inline wrhvAmpCpuHreg32Set
01l,24may10,jl   Sync with HV 1.2 25-May-10
01k,20may10,rgo  fix unresolved _RType
01j,03mar10,rgo  sync-up with hv1.2 view on 3/3/10
01i,31aug09,mmi  move VBI_HREG_SET to vbiX86Arch.h
01h,26aug09,mmi  fix WIND00178026: update file name
01g,17aug09,md   fix comments
01f,14aug09,md   update to match hypervisor version
01e,28jul09,mpk  add hardware register set to vbi
01d,08jun09,md   add define for maximum number of cores
01c,25may09,md   add byte order define
01b,06feb09,mmi  add MAX interrupts definition
01a,14jan09,mmi  created
*/

#ifndef __INCvbiX86Archh
#define __INCvbiX86Archh

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/* structure of the system descriptor table registers (VBI_GDTR, VBI_IDTR, VBI_LDTR) */

struct VBI_XDTR64
    {
	uint16_t limit;		/* maximum size of the DT */
	uint64_t base;		/* address of DT */
	uint16_t pad[3];
    } __attribute__((packed));

struct VBI_XDTR32
    {
	uint16_t limit;
	uint32_t base;
	uint16_t pad;
    } __attribute__((packed));


typedef struct VBI_XDTR64 VBI_GDTR;
typedef struct VBI_XDTR64 VBI_IDTR;
typedef struct VBI_XDTR64 VBI_LDTR;

typedef struct VBI_XDTR32 VBI_GDTR32;
typedef struct VBI_XDTR32 VBI_IDTR32;
typedef struct VBI_XDTR32 VBI_LDTR32;


/*******************************************************************************
*
* VBI_HREG_SET - hardware register set, for read/write
*
* Used by vbiVbRegisterRead/vbiVbRegisterWrite to read/write registers in 
* another VB
* 
* SYNOPSIS
*
* VB hardware register set C data structure type definition
*
*\cs
*     typedef struct		/@ VB_REG_SET - used for sys_regsRead/Write @/
*         {
*         vbiRType32_t  eax;	/@ 00: general register		@/
*         vbiRType32_t  ebx;	/@ 04: general register		@/
*         vbiRType32_t  ecx;	/@ 08: general register		@/
*         vbiRType32_t  edx;	/@ 0C: general register		@/
*         vbiRType32_t  esi;	/@ 10: general register		@/
*         vbiRType32_t  edi;	/@ 14: general register		@/
*         vbiRType32_t  eip;	/@ 18: program counter		@/
*         vbiRType32_t  ebp;	/@ 1C: frame pointer register	@/
*         vbiRType32_t  esp;	/@ 20: stack pointer register	@/
*         vbiRType32_t  eflags;	/@ 24: status register		@/
*         vbiRType32_t  cr0;	/@ 28: control register 0	@/
*         vbiRType32_t  cr3;	/@ 2C: control register 3	@/
*         vbiRType32_t  cr4;	/@ 30: control register 4	@/
*         vbiRType32_t  idtr;	/@ 34: IDT task register	@/
*         vbiRType32_t  gdtr;	/@ 38: GDT task register	@/
*         vbiRType32_t  ldtr;	/@ 3C: LDT task register	@/
*         vbiRType32_t  cs;		/@ 40: code segment		@/
*         vbiRType32_t  ss;		/@ 44: stack segment		@/
*         vbiRType32_t  ds;		/@ 48: data segment		@/
*         vbiRType32_t  es;		/@ 4C: E segment		@/
*         vbiRType32_t  fs;		/@ 50: F segment		@/
*         vbiRType32_t  gs;		/@ 54: G segment		@/
*         vbiRType32_t  tr;		/@ 58: task register		@/
*         } VBI_HREG_SET;
*
*\ce
* SEE ALSO: NONE
* 
*/

typedef struct			/* VBI_REG_SET - used for sys_regsRead/Write */
    {
    vbiRType32_t  eax;		/* 00: general register		*/
    vbiRType32_t  ebx;		/* 04: general register		*/
    vbiRType32_t  ecx;		/* 08: general register		*/
    vbiRType32_t  edx;		/* 0C: general register		*/
    vbiRType32_t  esi;		/* 10: general register		*/
    vbiRType32_t  edi;		/* 14: general register		*/
    vbiRType32_t  eip;		/* 18: program counter		*/
    vbiRType32_t  ebp;		/* 1C: frame pointer register	*/
    vbiRType32_t  esp;		/* 20: stack pointer register	*/
    vbiRType32_t  eflags;	/* 24: status register		*/
    vbiRType32_t  cr0;		/* 28: control register 0	*/
    vbiRType32_t  cr3;		/* 2C: control register 3	*/
    vbiRType32_t  cr4;		/* 30: control register 4	*/
    VBI_IDTR32	  idtr;		/* 34: IDT task register	*/
    VBI_GDTR32	  gdtr;		/* 3C: GDT task register	*/
    VBI_LDTR32	  ldtr;		/* 44: LDT task register	*/
    vbiRType32_t  cs;		/* 4C: code segment		*/
    vbiRType32_t  ss;		/* 50: stack segment		*/
    vbiRType32_t  ds;		/* 54: data segment		*/
    vbiRType32_t  es;		/* 58: E segment		*/
    vbiRType32_t  fs;		/* 5C: F segment		*/
    vbiRType32_t  gs;		/* 60: G segment		*/
    vbiRType32_t  tr;		/* 64: task register		*/
    } VBI_HREG_SET;

typedef struct			/* REG_SET - x86 register set	*/
    {
    vbiRType64_t   rax;		/* 00: general register		*/
    vbiRType64_t   rbx;		/* 08: general register		*/
    vbiRType64_t   rcx;		/* 10: general register		*/
    vbiRType64_t   rdx;		/* 18: general register		*/
    vbiRType64_t   rsp;		/* 20: stack pointer register	*/
    vbiRType64_t   rbp;		/* 28: frame pointer register	*/
    vbiRType64_t   rsi;		/* 30: general register		*/
    vbiRType64_t   rdi;		/* 38: general register		*/
    vbiRType64_t   r8;	 	/* 40: general register		*/
    vbiRType64_t   r9;	 	/* 48: general register		*/
    vbiRType64_t   r10;		/* 50: general register		*/
    vbiRType64_t   r11;		/* 58: general register		*/
    vbiRType64_t   r12;		/* 60: general register		*/
    vbiRType64_t   r13;		/* 68: general register		*/
    vbiRType64_t   r14;		/* 70: general register		*/
    vbiRType64_t   r15;		/* 78: general register		*/
    vbiRType64_t   rip;		/* 80: program counter		*/
    vbiRType64_t   rflags;	/* 88: status register		*/
    vbiRType64_t   cr0;		/* 90: control register 0	*/
    vbiRType64_t   cr2;		/* 98: control register 2	*/
    vbiRType64_t   cr3;		/* 100: control register 3	*/
    vbiRType64_t   cr4;		/* 108: control register 4	*/
    VBI_IDTR	   idtr;	/* 110: IDT task register	*/
    VBI_GDTR	   gdtr;	/* 11a: GDT task register	*/
    VBI_LDTR	   ldtr;	/* 136: LDT task register	*/
    vbiRType64_t   cs;		/* 140: code segment		*/
    vbiRType64_t   ds;		/* 148: data segment		*/
    vbiRType64_t   ss;		/* 150: stack segment		*/
    vbiRType64_t   es;		/* 158: E segment		*/
    vbiRType64_t   fs;		/* 160: F segment		*/
    vbiRType64_t   gs;		/* 168: G segment		*/
    vbiRType64_t   tr;		/* 170: Task register		*/
    /* xxx(gws): excluding FP support */
    } VBI_HREG_SET_64;



/* complex register set definition */

typedef union
    {
    VBI_HREG_SET    hreg32;	/* 32 bit register set */
    VBI_HREG_SET_64 hreg64;	/* 64 bit register set */
    } VBI_HREG_SET_CMPLX;


typedef struct
    {
    vbiRegSet_t     vbiRegType;  /* 00: register set to use */
    uint32_t	    qualifier;   /* 04: optional field, used for alignment */

    VBI_HREG_SET_CMPLX vbiRegSet;
    } VBI_HREG_SET_CMPLX_QUALIFIED;

#ifndef _WRS_CONFIG_LP64

/******************************************************************************
*
* wrhvAmpCpuHreg32Set - Init the guestOS of VBI_HREG_SET_CMPLX_QUALIFIED data 
* structure.
*
* This function sets the specific parameters which are CPU/Arch dependent 
* and it will be called by wrhvAmpCpuEnable before resuming the Virtual Board
* during the GuestOS wrload operation. Note that the register-width is assumed 
* to be 32bits. 
*
* ERRNO: - N/A
* RETURNS:None 
* \NOMANUAL
*
*/

_WRS_INLINE void wrhvAmpCpuHreg32Set
    (
    VBI_HREG_SET_CMPLX_QUALIFIED *	pRegSet,
    FUNCPTR             		entryPt,
    vbiGuestPhysAddr_t  		cfgAddr
    )
    {

    /* IP and eax parameters are set */

    pRegSet->vbiRegSet.hreg32.eip      = (vbiRType32_t) entryPt;
    pRegSet->vbiRegSet.hreg32.eax      = (vbiRType32_t) cfgAddr;

    return;
    }

#endif /* _WRS_CONFIG_LP64 */

#endif /* _ASMLANGUAGE */

/* x86 uses little endian byte ordering */

#define __VBI_BYTE_ORDER __VBI_LITTLE_ENDIAN

#ifdef __cplusplus
}
#endif
#endif /* __INCVbiX86Archh */
