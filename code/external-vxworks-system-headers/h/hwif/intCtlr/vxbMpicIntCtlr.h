/* vxbMpicIntCtlr.h - Multicore Programmable Interrupt Controller driver */

/*
 * Copyright (c) 2010-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01i,09may12,syt  Added TRIG_ENTRY_NUM and IPI vector defines. (WIND00341799)
01h,22sep11,syt  Added macro MPIC_QUIRK_IACK.(WIND00295774)
01g,29jun11,syt  Added MPIC register resource flag defines.
01f,23mar11,x_s  Added macro MPIC_EOI_P0_REG.
01e,06mar11,x_s  Added SMP support.
01d,12jan11,x_z  Fixed documentation issue.
01c,15oct10,x_z  Fixed macro MPIC_IPI0_VEC and MPIC_MAX_EXT_VEC.
01b,27jun10,x_z  Fixed some macros and code clean.
01a,30mar10,x_s  Modified from vxbEpicIntCtlr.h/01s
*/

#ifndef __INCvxbMpicIntCtlrh
#define __INCvxbMpicIntCtlrh

#ifdef __cplusplus
extern "C" {
#endif

/* Registers Offsets */

#define MPIC_VP0_REG            0x10000 /* Vector/Priority */
#define MPIC_DST0_REG           0x10010 /* Destination */
#define MPIC_IPI_DPATCH_REG0    0x00040 /* IPI0 dispatch */
#define MPIC_IPI_DPATCH_REG1    0x00050 /* IPI1 dispatch */
#define MPIC_IPI_DPATCH_REG2    0x00060 /* IPI2 dispatch */
#define MPIC_IPI_DPATCH_REG3    0x00070 /* IPI3 dispatch */

#define MPIC_CTASK_PRI_REG      0x20080 /* Cur Task Prio for CPU0 */
#define MPIC_WHO_AM_I_REG       0x00090 /* Who am I */
#define MPIC_INT_ACK_REG        0x000A0 /* Non Critical Interrupt Acknowledge */
#define MPIC_EOI_REG            0x000B0 /* Non Critical End of Interrupt */
#define MPIC_EOI_P0_REG         0x200B0 /* Non Critical End of Interrupt for CPU0 */
#define MPIC_CRT_INT_ACK_REG    0x000C0 /* Critical Interrupt Acknowledge */
#define MPIC_CRT_EOI_REG        0x000D0 /* Critical End of Interrupt */
#define MPIC_MC_INT_ACK_REG     0x000E0 /* MachineCheck Interrupt Acknowledge */
#define MPIC_MC_EOI_REG         0x000F0 /* MachineCheck End of Interrupt */

#define MPIC_FEATURES_REG0      0x01000 /* Feature reporting */
#define MPIC_GLOBAL_REG0        0x01020 /* Global config */
#define MPIC_VENDOR_TYPE_REG    0x01040 /* Vendor Interrupt Type Config */
#define MPIC_VENDOR_VIRD_REG    0x01050 /* Vendor raw interrupt debug config */
#define MPIC_VENDOR_REVID_REG   0x01070 /* Vendor soft core revision ID */
#define MPIC_VENDOR_ID_REG      0x01080 /* Vendor id */
#define MPIC_PROC_INIT_REG      0x01090 /* Processor init. */

#define MPIC_IPI_VEC_REG0       0x010A0 /* IPI0 vect/prio */
#define MPIC_IPI_VEC_REG1       0x010B0 /* IPI1 vect/prio */
#define MPIC_IPI_VEC_REG2       0x010C0 /* IPI2 vect/prio */
#define MPIC_IPI_VEC_REG3       0x010D0 /* IPI3 vect/prio */
#define MPIC_SPUR_VEC_REG       0x010E0 /* Spurious vector */

#define MPIC_TVP0_REG           0x01120 /* Timer0 Vector/Priority */
#define MPIC_TDST0_REG          0x01130 /* Timer0 Destination */

#define MPIC_NAME                "mpic"

/* Vector/Priority Registers */

#define MPIC_VECPRI_MASK                    0x80000000
#define MPIC_VECPRI_ACTIVITY                0x40000000 /* Read Only */
#define MPIC_VECPRI_PRIORITY_MASK           0xf
#define MPIC_VECPRI_PRIORITY_SHIFT          16
#define MPIC_VECPRI_VECTOR_MASK             0x000000ff
#define MPIC_VECPRI_POLARITY_POSITIVE       0x00800000
#define MPIC_VECPRI_POLARITY_NEGATIVE       0x00000000
#define MPIC_VECPRI_POLARITY_MASK           0x00800000
#define MPIC_VECPRI_SENSE_LEVEL             0x00400000
#define MPIC_VECPRI_SENSE_EDGE              0x00000000
#define MPIC_VECPRI_SENSE_MASK              0x00400000

/* FRR (feature reporting register) */

#define MPIC_FRR_NIRQ_MASK                  0x007f0000
#define MPIC_FRR_NIRQ_SHIFT                 16
#define MPIC_FRR_NCPU_MASK                  0x00001f00
#define MPIC_FRR_NCPU_SHIFT                 8

/* Global configuration register */

#define MPIC_GLOBAL_GCONF_RESET             0x80000000
#define MPIC_GLOBAL_GCONF_8259_PTHROU_DIS   0x20000000
#define MPIC_GLOBAL_GCONF_NO_BIAS           0x10000000
#define MPIC_GLOBAL_GCONF_BASE_MASK         0x000fffff
#define MPIC_GLOBAL_GCONF_MCK               0x08000000

/* Vendor Interrupt Type Configuration Register */

#define MPIC_VENDOR_TYPE_MCB_MASK           0x1F /* Lower MachineCheck Border */
#define MPIC_VENDOR_TYPE_MCB_SHIFT          8
#define MPIC_VENDOR_TYPE_CRB_MASK           0x1F /* Lower Critical Interrupt */
                                                 /* Border */

/* Vector Destination Register */

#define MPIC_CPUID_DST_MASK                 0x0000000F
#define MPIC_CPUID_DST(cpuid)               (1 << (cpuid))

/* General vector configuration */

#define MPIC_MAX_EXT_VEC                    128
#define MPIC_SPUR_VEC                       255
#define MPIC_MAX_IPI_IRQS                   4
#define MPIC_IPI0_VEC                       (MPIC_SPUR_VEC - 4)
#define MPIC_IPI1_VEC                       (MPIC_IPI0_VEC + 1)
#define MPIC_IPI2_VEC                       (MPIC_IPI0_VEC + 2)
#define MPIC_IPI3_VEC                       (MPIC_IPI0_VEC + 3)

#define MPIC_MAX_TIMER_IRQS                 4
#define MPIC_TIMER0_VEC                     (MPIC_IPI0_VEC - 4)

#define MPIC_PRI_DEF                        10
#define MPIC_PRIORITY_MIN                   0 /* lowest priority */
#define MPIC_PRIORITY_MAX                   15 /* highest priority */

/* Register Access Macro */

#define MPIC_PIN_TO_VEC_ADDR(pin)           (MPIC_VP0_REG + ((pin) * 0x20))
#define MPIC_PIN_TO_DST_ADDR(pin)           (MPIC_DST0_REG + ((pin) * 0x20))

#define MPIC_IPIID_TO_DPATCH_ADDR(id)       (MPIC_IPI_DPATCH_REG0 + ((id) * 0x10))
#define MPIC_IPIID_TO_IVP_ADDR(id)          (MPIC_IPI_VEC_REG0 + ((id) * 0x10))

#define MPIC_TIMERID_TO_DPATCH_ADDR(id)     (MPIC_TDST0_REG + ((id) * 0x40))
#define MPIC_TIMERID_TO_IVP_ADDR(id)        (MPIC_TVP0_REG + ((id) * 0x40))
#define MPIC_CPUID_TO_CTASK_PRI_ADDR(id)    (MPIC_CTASK_PRI_REG + ((id) * 0x1000))
#define MPIC_CPUID_TO_EOI_ADDR(id)          (MPIC_EOI_P0_REG + ((id) * 0x1000))

/* MPIC driver resource flags bit defines */

#define MPIC_REG_DCR                        0x00000000
#define MPIC_REG_MEM                        0x00000001
#define MPIC_REG_MEM_BE                     0x00000002
#define MPIC_REG_MEM_LE                     0x00000004
#define MPIC_QUIRK_WHOAMI                   0x00000008
#define MPIC_QUIRK_NO_REG                   0x00000010
#define MPIC_QUIRK_IACK                     0x00000020

#define MPIC_REG_ACS_MASK                   0x00000003

/* The number of IRQ trigger table's entry */

#define TRIG_ENTRY_NUM                      256

#ifdef __cplusplus
}
#endif

#endif  /* __INCvxbMpicIntCtlrh */
