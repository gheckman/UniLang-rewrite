/* vxAtomicArchLib.h - x86_64 IA32 specific atomic library header */

/*
 * Copyright (c) 2006-2008, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01i,13sep10,scm  WIND002322578 remove type-punning warnings...
01h,29apr10,pad  Moved extern C statement after include statements.
01g,23mar10,scm  add inline gnu routines for 64 bit
01f,23mar10,scm  add fixed size APIs, made memory barriers available in user space
01e,16jun08,zl   use _WRS_BARRIER() for memory barrier implementations.
01d,17jan08,gls  renamed inline routines
01c,03jan08,gls  fixed DCC _inline_vxCas()
01b,11dec07,gls  Added _inline_vxCas()
01a,29nov06,scm  Created
*/

#ifndef __INCvxAtomicArchLibh
#define __INCvxAtomicArchLibh

#include <arch/i86/x86_64/vxAtomicArchLibCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

#if defined (__DCC__)

#define vxCas_inline            vxAtomicCas
#define vxAtomicCas_inline      vxAtomicCas
#define vxAtomic64Cas_inline    vxAtomic64Cas
#define vxAtomic32Cas_inline    vxAtomic32Cas
#define vxAtomicAdd_inline      vxAtomicAdd
#define vxAtomic64Add_inline    vxAtomic64Add
#define vxAtomic32Add_inline    vxAtomic32Add
#define vxAtomicSub_inline      vxAtomicSub
#define vxAtomic64Sub_inline    vxAtomic64Sub
#define vxAtomic32Sub_inline    vxAtomic32Sub
#define vxAtomicInc_inline      vxAtomicInc
#define vxAtomic64Inc_inline    vxAtomic64Inc
#define vxAtomic32Inc_inline    vxAtomic32Inc
#define vxAtomicDec_inline      vxAtomicDec
#define vxAtomic64Dec_inline    vxAtomic64Dec
#define vxAtomic32Dec_inline    vxAtomic32Dec
#define vxAtomicGet_inline      vxAtomicGet
#define vxAtomic64Get_inline    vxAtomic64Get
#define vxAtomic32Get_inline    vxAtomic32Get
#define vxAtomicSet_inline      vxAtomicSet
#define vxAtomic64Set_inline    vxAtomic64Set
#define vxAtomic32Set_inline    vxAtomic32Set
#define vxAtomicClear_inline    vxAtomicClear
#define vxAtomic64Clear_inline  vxAtomic64Clear
#define vxAtomic32Clear_inline  vxAtomic32Clear

#elif defined (__GNUC__)

static __inline__ BOOL vxAtomic64Cas_inline
    (
    atomic64_t *        target,         /* memory location to compare-and-swap */
    atomic64Val_t       oldValue,       /* compare to this value */
    atomic64Val_t       newValue        /* swap with this value */
    )
    {
    BOOL swapped;
    __asm__ volatile
    (
    "movq   %2, %%rax;"     /* move oldValue to %rax */
    "lock;"                 /* lock the Bus during the next inst */
    "cmpxchgq %3, %1;"      /* if (%rax == *target) */
                            /*   {ZF = 1; *target = newValue;} */
                            /* else              */
                            /*   {ZF = 0; %rax = *target;} */
    "setz   %%al;"          /* if success, set swapped to TRUE else FALSE */
    "movzb  %%al, %0"       /* zero extend swapped */
    : "=&a" (swapped)       /* output: swapped  is %0 */
    : "m"   (*(target)),    /* input:  *target  is %1 */
      "g"   (oldValue),     /*         oldValue is %2 */
      "r"   (newValue)      /*         newValue is %3 */
    : "memory"              /* memory clobber for code barrier */
    );
    return swapped;
    }

static __inline__ BOOL vxAtomic32Cas_inline
    (
    atomic32_t *        target,         /* memory location to compare-and-swap */
    atomic32Val_t       oldValue,       /* compare to this value */
    atomic32Val_t       newValue        /* swap with this value */
    )
    {
    BOOL swapped;
    __asm__ volatile
    (
    "movl   %2, %%eax;"     /* move oldValue to %eax */
    "lock;"                 /* lock the Bus during the next inst */
    "cmpxchgl %3, %1;"      /* if (%eax == *target) */
                            /*   {ZF = 1; *target = newValue;} */
                            /* else              */
                            /*   {ZF = 0; %eax = *target;} */
    "setz   %%al;"          /* if success, set swapped to TRUE else FALSE */
    "movzbl %%al, %0"       /* zero extend swapped */
    : "=&a" (swapped)       /* output: swapped  is %0 */
    : "m"   (*(target)),    /* input:  *target  is %1 */
      "g"   (oldValue),     /*         oldValue is %2 */
      "r"   (newValue)      /*         newValue is %3 */
    : "memory"              /* memory clobber for code barrier */
    );
    return swapped;
    }

static __inline__ atomic64Val_t vxAtomic64Add_inline
    (
    atomic64_t *        target,
    atomic64Val_t       value
    )
    {
    __asm__ volatile
    (
    "lock;"                 /* lock the Bus during the next inst */
    "xaddq  %0, %1"         /* TMP = value + *target */
                            /* value = *target */
                            /* *target = TMP */
    : "+r"  (value)         /* output: value   is %0 */
    : "m"   (*(target))     /* input:  *target is %1 */
    : "memory"              /* memory clobber for code barrier */
    );
    return value;
    }

static __inline__ atomic32Val_t vxAtomic32Add_inline
    (
    atomic32_t *        target,
    atomic32Val_t       value
    )
    {
    __asm__ volatile
    (
    "lock;"                 /* lock the Bus during the next inst */
    "xaddl  %0, %1"         /* TMP = value + *target */
                            /* value = *target */
                            /* *target = TMP */
    : "+r"  (value)         /* output: value   is %0 */
    : "m"   (*(target))     /* input:  *target is %1 */
    : "memory"              /* memory clobber for code barrier */
    );
    return value;
    }

static __inline__ atomic64Val_t vxAtomic64Sub_inline
    (
    atomic64_t *        target,
    atomic64Val_t       value
    )
    {
    __asm__ volatile
    (
    "negq   %0;"            /* Negate value... */
    "lock;"                 /* lock the Bus during the next inst */
    "xaddq  %0, %1"         /* TMP = -value + *target */
                            /* value = *target */
                            /* *target = TMP */
    : "+r"  (value)         /* output: value   is %0 */
    : "m"   (*(target))     /* input:  *target is %1 */
    : "memory"              /* memory clobber for code barrier */
    );
    return value;
    }

static __inline__ atomic32Val_t vxAtomic32Sub_inline
    (
    atomic32_t *        target,
    atomic32Val_t       value
    )
    {
    __asm__ volatile
    (
    "negl   %0;"            /* Negate value... */
    "lock;"                 /* lock the Bus during the next inst */
    "xaddl  %0, %1"         /* TMP = -value + *target */
                            /* value = *target */
                            /* *target = TMP */
    : "+r"  (value)         /* output: value   is %0 */
    : "m"   (*(target))     /* input:  *target is %1 */
    : "memory"              /* memory clobber for code barrier */
    );
    return value;
    }

static __inline__ atomic64Val_t vxAtomic64Inc_inline
    (
    atomic64_t *        target
    )
    {
    atomic64Val_t value;
    __asm__ volatile
    (
    "movq   $1, %0;"        /* inc by 1 */
    "lock;"                 /* lock the Bus during the next inst */
    "xaddq  %0, %1"         /* TMP = *target + 1 */
                            /* value = *target */
                            /* *target = TMP */
    : "=&r" (value)         /* output: value   is %0 */
    : "m"   (*(target))     /* input:  *target is %1 */
    : "memory"              /* memory clobber for code barrier */
    );
    return value;
    }

static __inline__ atomic32Val_t vxAtomic32Inc_inline
    (
    atomic32_t *        target
    )
    {
    atomic32Val_t value;
    __asm__ volatile
    (
    "movl   $1, %0;"        /* inc by 1 */
    "lock;"                 /* lock the Bus during the next inst */
    "xaddl  %0, %1"         /* TMP = *target + 1 */
                            /* value = *target */
                            /* *target = TMP */
    : "=&r" (value)         /* output: value   is %0 */
    : "m"   (*(target))     /* input:  *target is %1 */
    : "memory"              /* memory clobber for code barrier */
    );
    return value;
    }

static __inline__ atomic64Val_t vxAtomic64Dec_inline
    (
    atomic64_t *        target
    )
    {
    atomic64Val_t value;
    __asm__ volatile
    (
    "movq   $(-1), %0;"     /* dec by 1 */
    "lock;"                 /* lock the Bus during the next inst */
    "xaddq  %0, %1"         /* TMP = *target - 1 */
                            /* value = *target */
                            /* *target = TMP */
    : "=&r" (value)         /* output: value   is %0 */
    : "m"   (*(target))     /* input:  *target is %1 */
    : "memory"              /* memory clobber for code barrier */
    );
    return value;
    }

static __inline__ atomic32Val_t vxAtomic32Dec_inline
    (
    atomic32_t *        target
    )
    {
    atomic32Val_t value;
    __asm__ volatile
    (
    "movl   $(-1), %0;"     /* dec by 1 */
    "lock;"                 /* lock the Bus during the next inst */
    "xaddl  %0, %1"         /* TMP = *target - 1 */
                            /* value = *target */
                            /* *target = TMP */
    : "=&r" (value)         /* output: value   is %0 */
    : "m"   (*(target))     /* input:  *target is %1 */
    : "memory"              /* memory clobber for code barrier */
    );
    return value;
    }

static __inline__ atomic64Val_t vxAtomic64Get_inline
    (
    atomic64_t *        target
    )
    {
    atomic64Val_t value;
    __asm__ volatile
    (
    "movq   %1, %0"        /* get value with bus-lock */
    : "=r" (value)         /* output: value   is %0 */
    : "m"   (*(target))    /* input:  *target is %1 */
    : "memory"             /* memory clobber for code barrier */
    );
    return value;
    }

static __inline__ atomic32Val_t vxAtomic32Get_inline
    (
    atomic32_t *        target
    )
    {
    atomic32Val_t value;
    __asm__ volatile
    (
    "movl   %1, %0"        /* get value with bus-lock */
    : "=r" (value)         /* output: value   is %0 */
    : "m"   (*(target))    /* input:  *target is %1 */
    : "memory"             /* memory clobber for code barrier */
    );
    return value;
    }

static __inline__ atomic64Val_t vxAtomic64Set_inline
    (
    atomic64_t *        target,
    atomic64Val_t       value
    )
    {
    __asm__ volatile
    (
    "xchgq  %0, %1"         /* set value with bus-lock */
    : "+r"  (value)         /* output: value   is %0 */
    : "m"   (*(target))     /* input:  *target is %1 */
    : "memory"              /* memory clobber for code barrier */
    );
    return value;
    }

static __inline__ atomic32Val_t vxAtomic32Set_inline
    (
    atomic32_t *        target,
    atomic32Val_t       value
    )
    {
    __asm__ volatile
    (
    "xchgl  %0, %1"         /* set value with bus-lock */
    : "+r"  (value)         /* output: value   is %0 */
    : "m"   (*(target))     /* input:  *target is %1 */
    : "memory"              /* memory clobber for code barrier */
    );
    return value;
    }

static __inline__ atomic64Val_t vxAtomic64Clear_inline
    (
    atomic64_t *        target
    )
    {
    atomic64Val_t value;
    __asm__ volatile
    (
    "movq   $0, %0;"        /* 'clear' value to set */
    "xchgq  %0, %1"         /* swap 'clear' value with bus-lock */
    : "=&r" (value)         /* output: value   is %0 */
    : "m"   (*(target))     /* input:  *target is %1 */
    : "memory"              /* memory clobber for code barrier */
    );
    return value;
    }

static __inline__ atomic32Val_t vxAtomic32Clear_inline
    (
    atomic32_t *        target
    )
    {
    atomic32Val_t value;
    __asm__ volatile
    (
    "movl   $0, %0;"        /* 'clear' value to set */
    "xchgl  %0, %1"         /* swap 'clear' value with bus-lock */
    : "=&r" (value)         /* output: value   is %0 */
    : "m"   (*(target))     /* input:  *target is %1 */
    : "memory"              /* memory clobber for code barrier */
    );
    return value;
    }

#define vxCas_inline            vxAtomic64Cas_inline
#define vxAtomicCas_inline      vxAtomic64Cas_inline
#define vxAtomicAdd_inline      vxAtomic64Add_inline
#define vxAtomicSub_inline      vxAtomic64Sub_inline
#define vxAtomicInc_inline      vxAtomic64Inc_inline
#define vxAtomicDec_inline      vxAtomic64Dec_inline
#define vxAtomicGet_inline      vxAtomic64Get_inline
#define vxAtomicSet_inline      vxAtomic64Set_inline
#define vxAtomicClear_inline    vxAtomic64Clear_inline

#else

#define vxCas_inline            vxAtomicCas
#define vxAtomicCas_inline      vxAtomicCas
#define vxAtomic64Cas_inline    vxAtomic64Cas
#define vxAtomic32Cas_inline    vxAtomic32Cas
#define vxAtomicAdd_inline      vxAtomicAdd
#define vxAtomic64Add_inline    vxAtomic64Add
#define vxAtomic32Add_inline    vxAtomic32Add
#define vxAtomicSub_inline      vxAtomicSub
#define vxAtomic64Sub_inline    vxAtomic64Sub
#define vxAtomic32Sub_inline    vxAtomic32Sub
#define vxAtomicInc_inline      vxAtomicInc
#define vxAtomic64Inc_inline    vxAtomic64Inc
#define vxAtomic32Inc_inline    vxAtomic32Inc
#define vxAtomicDec_inline      vxAtomicDec
#define vxAtomic64Dec_inline    vxAtomic64Dec
#define vxAtomic32Dec_inline    vxAtomic32Dec
#define vxAtomicGet_inline      vxAtomicGet
#define vxAtomic64Get_inline    vxAtomic64Get
#define vxAtomic32Get_inline    vxAtomic32Get
#define vxAtomicSet_inline      vxAtomicSet
#define vxAtomic64Set_inline    vxAtomic64Set
#define vxAtomic32Set_inline    vxAtomic32Set
#define vxAtomicClear_inline    vxAtomicClear
#define vxAtomic64Clear_inline  vxAtomic64Clear
#define vxAtomic32Clear_inline  vxAtomic32Clear

#endif /* _VX_TOOL_FAMILY */

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxAtomicArchLibh */
