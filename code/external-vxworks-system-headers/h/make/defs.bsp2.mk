# defs.bsp2.mk - bsp2 default makefile definitions
#
# Copyright (c) 2010 Wind River Systems, Inc.
#
# The right to copy, distribute, modify or otherwise make use
# of this software may be licensed only pursuant to the terms
# of an applicable Wind River license agreement.
#
# modification history
# --------------------
# 01a,01dec10,mze  derived from defs.bsp
#
# DESCRIPTION
# This file is included into bsp makefiles to define the default makefile
# definitions.  After the include the Makefile may customize the definitions
# found here to suit the circumstance.
#
# Redefinitions of make variables earlier than the include of this file will
# have no affect.
#
# This file is only for command line builds from the BSP directory.  For the users
# of defs.bsp2.mk it is expected that VIP projects are the only viable project types
# this is inclusive of bootroms of all natures
#

# map TOOL to TOOL_FAMILY, if not already done in BSP Makefile

ifeq ($(TOOL_FAMILY),)
ifeq  ($(findstring gnu,$(TOOL)),gnu)
TOOL_FAMILY     = gnu
endif
ifeq  ($(findstring diab,$(TOOL)),diab)
TOOL_FAMILY     = diab
endif
ifeq  ($(findstring icc,$(TOOL)),icc)
TOOL_FAMILY     = icc
endif
endif
# Include resource definitions that support packaging of a bsp


include $(TGT_DIR)/h/make/defs.vsbvars.mk
#TOOL_OPTIONS_FILES_DIR = .

ifndef TC_INFO
-include $(VSB_MAKE_CONFIG_FILE)
#makeMacros : ALLFLAGS_VSBDEFS = -D_VSB_CONFIG_FILE=\"$$(VSB_CONFIG_FILE)\"  $(_VSB_CONFIG_ADDEDCFLAGS) -I$$(VSB_INCLUDE_DIR)
endif
include $(TGT_DIR)/h/make/defs.bsp
