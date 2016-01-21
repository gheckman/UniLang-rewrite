# defs.vsbvars.mk - VSB default variable defintions.
#
# Copyright 2008-2009 Wind River Systems, Inc.
#
# The right to copy, distribute, modify or otherwise make use
# of this software may be licensed only pursuant to the terms
# of an applicable Wind River license agreement.
#
# modification history
# --------------------
# 01h,28aug09,pee  pass #VSB_DIR# to bdgen
# 01g,24jul09,pee  modification to tag file path.
# 01f,15jun09,pee  adding tag files.
# 01g,20may09,pee  moification to VSB header path.
# 01f,04may09,pee  adding VSB private include directory
# 01e,16mar09,pee  adding VSB_INCLUDE_DIR
# 01d,06nov08,pee  WIND00139818
# 01c,08oct08,pee  WIND00137789.
# 01b,02oct08,mze  changes to the use of _WRS_CONFIG_ADDEDCFLAGS
# 01a,29Auu08,pee  created

# use this variable to find if this file was already included
__DEFS_VSBVARS_MK_INCLUDED = TRUE

ifndef __DEFS_OPTIONS_INCLUDED
include $(WIND_BASE)/target/h/make/defs.options
endif

# VSB default and definitions
ifdef VSB_DIR
ifeq ($(origin VSB_DIR),command line)
ifndef __VSB_DIR_ABS
__ABS_VSB_DIR :=  $(shell cd $(subst \,/,$(VSB_DIR));pwd)
override VSB_DIR := $(__ABS_VSB_DIR)
MAKEOVERRIDES := $(patsubst VSB_DIR=%,VSB_DIR=$(__ABS_VSB_DIR), $(MAKEOVERRIDES)) __VSB_DIR_ABS=TRUE
endif
endif
else
VSB_DIR = $(WIND_BASE)/target/lib$(MAJOR_CLI_OPTION_SUFFIX)
endif

VSB_INCLUDE_DIR = $(VSB_DIR)/h/$(VX_CPU_FAMILY)$(ARCH_OPTION_SUFFIX)/$(CPU)$(CPU_OPTION_SUFFIX)/$(TOOL_COMMON_DIR)$(LIB_DIR_TAG)$(MINOR_OPTION_SUFFIX)
VSB_PRIVATE_INCLUDE_DIR=$(VSB_INCLUDE_DIR)/private
VSB_CONFIG_DIR = $(VSB_DIR)/h/config
VSB_CONFIG_FILE_NAME = vsbConfig.h
VSB_AUTOCONF_FILE_NAME = autoconf.h
VSB_MAKE_CONFIG_FILE_NAME = auto.conf

VSB_CONFIG_FILE = $(VSB_CONFIG_DIR)/$(VSB_CONFIG_FILE_NAME)
VSB_MAKE_CONFIG_FILE = $(VSB_CONFIG_DIR)/$(VSB_MAKE_CONFIG_FILE_NAME)

ALLFLAGS_VSBDEFS = -D_VSB_CONFIG_FILE=\"$(VSB_CONFIG_FILE)\" $(_VSB_CONFIG_ADDEDCFLAGS) -I$(VSB_INCLUDE_DIR)

# tag data
ifeq ($(_BDGEN_),TRUE)
VSB_TAG_DIR = \#VSB_DIR\#/tags/$(VX_CPU_FAMILY)$(ARCH_OPTION_SUFFIX)/$(CPU)$(CPU_OPTION_SUFFIX)/$(TOOL_COMMON_DIR)$(LIB_DIR_TAG)$(MINOR_OPTION_SUFFIX)
else
VSB_TAG_DIR = $(VSB_DIR)/tags/$(VX_CPU_FAMILY)$(ARCH_OPTION_SUFFIX)/$(CPU)$(CPU_OPTION_SUFFIX)/$(TOOL_COMMON_DIR)$(LIB_DIR_TAG)$(MINOR_OPTION_SUFFIX)
endif
TAG_FILENAME_KERNEL = kernel.tags
VSB_TAG_FILE_KERNEL = $(VSB_TAG_DIR)/$(TAG_FILENAME_KERNEL)
TAG_FILENAME_DKM = dkm.tags
VSB_TAG_FILE_DKM = $(VSB_TAG_DIR)/$(TAG_FILENAME_DKM)
