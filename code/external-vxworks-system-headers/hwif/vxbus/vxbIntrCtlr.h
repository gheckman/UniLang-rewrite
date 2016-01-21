/* vxbIntrCtlr.h -- interrupt controller structures used by BSPs */

/*
 * Copyright (c) 2007, 2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
* of this software may be licensed only pursuant to the terms
* of an applicable Wind River license agreement.
*/

/*
modification history
--------------------
01e,20feb09,pmr  interrupt triggering options
01d,20sep07,b_m  fix doc error.
01c,15jul07,tor  dynamic interrupt support
01b,19Mar07,tor  update intCtlr structs
01a,01Mar07,tor  created
*/

#ifndef vxbintrCtlr_H
#define vxbintrCtlr_H

/* includes */

#include <vxWorks.h>
#include <vxBusLib.h>
#include <hwif/vxbus/vxBus.h>

/* defines */

/*
 * This value should be:
 *      ( VXB_INTCTLRLIB_TOPLVL_SIZE * VXB_INTCTLRLIB_LOWLVL_SIZE ) - 1 
 * We make it a constant here, because we don't want to include a
 * header file from target/src/hwif/h.
 */
#define VXB_INTR_DYNAMIC        0x00000F7F

/* triggering codes */
#define VXB_INTR_TRIG_NEG	0x01
#define VXB_INTR_TRIG_POS	0x02
#define VXB_INTR_TRIG_EDGE 	0x10
#define VXB_INTR_TRIG_LEVEL	0x20

/* for convenience */
#define VXB_INTR_TRIG_FALLING_EDGE  (VXB_INTR_TRIG_NEG | VXB_INTR_TRIG_EDGE)
#define VXB_INTR_TRIG_RISING_EDGE   (VXB_INTR_TRIG_POS | VXB_INTR_TRIG_EDGE)
#define VXB_INTR_TRIG_ACTIVE_LOW    (VXB_INTR_TRIG_NEG | VXB_INTR_TRIG_LEVEL)
#define VXB_INTR_TRIG_ACTIVE_HIGH   (VXB_INTR_TRIG_POS | VXB_INTR_TRIG_LEVEL)

#define VXB_INTR_PRIO_FORCE	0x8000

/* typedefs */

/*
 * intrCtlrInputs structure is used to associate a device with
 * the interrupt controller to which the device's interrupt
 * output is connected.  Note that multiple devices can be
 * connected to a single input pin; therefore, multiple
 * intrCtlrInputs table entries can be present for a single
 * input pin.  Also note that some input pins may not be
 * connected, which may leave holes in the table, where no
 * entry is present for a specific input pin.
 */

struct intrCtlrInputs
    {
    int		inputPin;
    char *	drvName;
    int		drvUnit;
    int		drvIndex;
    };

/*
 * intrCtlrPriority is used to set the priority of
 * a specified input pin on an interrupt controller
 */

struct intrCtlrPriority
    {
    int		inputPin;
    UINT16	priority;
    };

/*
 * intrCtlrTrigger is used to set the triggering of
 * a specified input pin on an interrupt controller
 */

struct intrCtlrTrigger
    {
    int		inputPin;
    UINT8	trigger;
    };

/*
 * intrCtlrXBar is used to manage cross-bar associations
 * on interrupt controllers so that the interrupt controller
 * routes the specified input pin to the specified output
 * pin
 */

struct intrCtlrXBar
    {
    int		inputPin;
    int		outputPin;
    };

/*
 * intrCtlrCpu is used on SMP systems only.  It indicates
 * which CPU the interrupt controller should route the
 * input pin to
 */

struct intrCtlrCpu
    {
    int		inputPin;
    int		cpuNum;
    };

/* globals */

/* locals */

#endif /* vxbintrCtlr_H */
