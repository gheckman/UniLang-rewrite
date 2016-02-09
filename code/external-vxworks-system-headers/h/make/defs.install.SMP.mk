# defs.install.SMP.mk - make options definitions for SMP
#
# Copyright (c) 2007 Wind River Systems, Inc.
#
# The right to copy, distribute, modify or otherwise make use
# of this software may be licensed only pursuant to the terms
# of an applicable Wind River license agreement.
#
#
# modification history
# --------------------
# 01c,18sep07,pee  created

_OPTIONS_MAJOR += SMP

CFLAGS_OPTION_SMP = -D_WRS_VX_SMP
CFLAGS_AS_OPTION_SMP = -D_WRS_VX_SMP
C++FLAGS_OPTION_SMP = -D_WRS_VX_SMP
AS_FLAGS_OPTION_SMP = -D_WRS_VX_SMP
CFLAGS_PIC_OPTION_SMP = -D_WRS_VX_SMP

_SUFFIX_OPTION_SMP = _smp


