# rules.vsb.mk - Host independent definitions for making VxWorks Source Build projects
#
# Copyright 2008, Wind River Systems, Inc.
#
# modification history
# --------------------
# 01c,15oct09,mze  convert WIND_HOME and WIND_USR to remove backslash
# 01b,02oct09,mze  adding a new macro
# 01a,16apr09,mze  adding usr into the VSB
#
# 01a,04apr08,pee  created

# use this variable to protect from multiple inclusion.
# with make 3.80, it is not possible to use eval inside ifdef
# so, the user needs to test this flag beforeinclusion of this file

__DEFS_LIBPRJ_MK__ = TRUE

WIND_BASE :=  $(subst \,/,$(WIND_BASE))
WIND_HOME :=  $(subst \,/,$(WIND_HOME))
WIND_USR :=  $(subst \,/,$(WIND_USR))

TGT_DIR = $(WIND_BASE)/target

SRCDIR = $(TGT_DIR)/src
CDFDIR = $(TGT_DIR)/config/comps/vxWorks

VSB_DIR := $(subst \,/,$(shell pwd))

ifeq ($(BSP_DIR),)
BSP_DIR = $(TGT_DIR)/config
endif

# 
_CONFIG_SRC_DIRS = $(TGT_DIR)/src
_CONFIG_USR_DIRS = $(WIND_USR)
_CONFIG_USR_SRC_DIRS = $(WIND_USR)/src
_CONFIG_USR_APPS_DIRS = $(WIND_USR)/apps

