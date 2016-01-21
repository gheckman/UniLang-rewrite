# rules.bspmacros.mk - BSP2 makefile target rules  
#
# Copyright (c) 2010-2012 Wind River Systems, Inc.
#
# The right to copy, distribute, modify or otherwise make use
# of this software may be licensed only pursuant to the terms
# of an applicable Wind River license agreement.
#
# modification history
# --------------------
# 01h,22aug13,rtm  fix for defect WIND00429956
# 01g,02feb12,mze  add .CPP as a valid suffix
# 01f,18nov11,jph  replace the versioned mapping file name with
#                  mappingfile.txt
# 01e,28jul11,jam  update mapping file for docs
# 01d,12may11,jam  change mapping file version
# 01c,06jan11,jph  check if mapping file exists
# 01b,03dec10,mze  created
# 01a,01dec10,mze  created
#
# DESCRIPTION
# This file contains rules used in building macros and header from the BSP directories.
#
#

 
###############################################################################
#
# headerMacros - output the values of all header macros
#
# Used by the project creation scripts

headerMacros: sysLib.c $(TOOL_OPTIONS_FILES_ALL)
	@@  $(CPP_PRINT_MACROS) $(CDF_OVERRIDE) $(CFLAGS_OPTIONS_ALL) $(ALLFLAGS_VSBDEFS) sysLib.c

###############################################################################
#
# makeMacrosReferred - output makefile-macros referred by project
#

makeMacrosReferred:
	$(NOP) VX_OS_LIBS = $(VX_OS_LIBS)

###############################################################################
#
# makeMacros - output makefile-macros related to toolchain settings
#
# Used by the project creation scripts

makeMacros:
	@ $(ECHO) '$(NOP) CPU = $(CPU)\n\
$(NOP) TOOL = $(TOOL)\n\
$(NOP) AR = $(AR)\n\
$(NOP) CC = $(CC)\n\
$(NOP) CPP = $(CPP)\n\
$(NOP) NM = $(NM)\n\
$(NOP) SIZE = $(SIZE)\n\
$(NOP) AS = $(AS)\n\
$(NOP) LD = $(LD)\n\
$(NOP) CFLAGS_AS = $(CFLAGS_AS)\n\
$(NOP) C++FLAGS = $(C++FLAGS)\n\
$(NOP) CFLAGS_PROJECT = $(CFLAGS_PROJECT)\n\
$(NOP) CFLAGS_AS_PROJECT = $(CFLAGS_AS_PROJECT)\n\
$(NOP) EXTRA_CFLAGS = $(EXTRA_INCLUDE) $(EXTRA_DEFINE) $(OPT_DEFINE) $(ADDED_CFLAGS)\n\
$(NOP) EXTRA_DEFINE = $(EXTRA_DEFINE)\n\
$(NOP) EXTRA_INCLUDE = $(EXTRA_INCLUDE)\n\
$(NOP) LIBS = $(LIB_EXTRA) $$(VX_OS_LIBS)\n\
$(NOP) LD_LINK_PATH = $(LD_LINK_PATH)\n\
$(NOP) LDDEPS = $(LDDEPS)\n\
$(NOP) BOOT_EXTRA = $(BOOT_EXTRA)\n\
$(NOP) MACH_DEP = $(MACH_DEP)\n\
$(NOP) OPTION_DEPEND = $(OPTION_DEPEND)\n\
$(NOP) OPTION_LANG_C = $(OPTION_LANG_C)\n\
$(NOP) TOOL_FAMILY = $(TOOL_FAMILY)\n\
$(NOP) HEX_FLAGS = $(HEX_FLAGS)'
ifneq ($(DEPEND_GEN_UTIL),)
	@ $(ECHO) "$(NOP) DEPEND_GEN_UTIL = $(DEPEND_GEN_UTIL)"
endif
ifeq ($(TC_INFO),TRUE)
	@ $(ECHO) "$(NOP) CC_ARCH_SPEC = $(CC_ARCH_SPEC)"
endif

ifeq ($(CPU_TO_BUILD),$(CPU))
ifeq ($(TOOL_TO_USE),$(TOOL))
checkCpuAndBuild: $(TARGET)
	@echo done
else
checkCpuAndBuild:
	@echo nothing to do for BSP $(BSP_NAME)
endif
else
checkCpuAndBuild:
	@echo nothing to do for BSP $(BSP_NAME)
endif

.PHONY : echoBsp

.PHONY : echoCpuVariant

echoBsp :
	@echo Bsp $(BSP_NAME) {
	@echo CPU $(CPU)
ifdef ENDIAN
	@echo ENDIAN $(ENDIAN)
endif
ifdef FP
	@echo FP $(FP)
endif
	@echo }

echoCpuVariant :
	@echo $(CPU_VARIANT)

#
# It is possible to generate dependency lists automatically by depending on
# a make include file:
#
#     with:             GNU make, SunOS 4.x/5.x make.
#     but not with:     clearmake, HPUX 9.x make, and probably plenty of others.
#
# If depend.$(BSP_NAME) has been removed and you are haplessly without
# a copy of GNU make:
#
#       % # In the BSP in question...
#       % touch depend.$(BSP_NAME)
#       % make depend.$(BSP_NAME)
#       % make
#
# Order in the Universe should be restored.
#


C_FILES := $(wildcard *.c $(CONFIG_ALL)/*.c)
CPP_FILES := $(wildcard *.cpp *.CPP $(CONFIG_ALL)/*.cpp $(CONFIG_ALL)/*.CPP)

#
# Create a dependency file if there are any C_FILES or CPP_FILES discovered
#
depend.$(BSP_NAME) : $(TOOL_OPTIONS_FILES_ALL)
	@echo "# Dependency file created for $@" > $@
ifneq ($(C_FILES),)
	# C dependencies found
	#
	$(CC) $(OPTION_DEPEND_C) $(CFLAGS) $(filter-out $(NODEPENDOBJS),$(C_FILES)) >> $@
endif
ifneq ($(CPP_FILES),)
	# CPP dependencies found
	#
	$(CPP) $(OPTION_DEPEND_C) $(C++FLAGS) $(filter-out $(NODEPENDOBJS),$(CPP_FILES)) >> $@
endif

# The two files below may not be present for simulators. So ignore the error
# returned by the compiler if the file does not exist.

ifneq ($(wildcard romInit.s),)
	$(CPP) $(OPTION_DEPEND_AS) $(CASFLAGS) romInit.s >> $@
endif
ifneq ($(wildcard sysALib.s),)
	$(CPP) $(OPTION_DEPEND_AS) $(CASFLAGS) sysALib.s >> $@
endif

# Post process the dependencies to substitute WIND variables

	- @ $(BSP_PROCESS_DEP)

# XXX generic rule for assembly files forthcoming
ifneq ($(IS_PRJ),TRUE)

BSP2PRJ=FALSE
ifeq ($(BSP2PRJ),FALSE)
ifneq ($(MAKECMDGOALS),clean)
ifeq ($(wildcard depend.$(BSP_NAME)),depend.$(BSP_NAME))
-include depend.$(BSP_NAME)
endif
endif
endif

endif


# Include BSP Test component rules if installed.
-include $(TGT_DIR)/h/make/rules.bsptest

include $(TGT_DIR)/h/make/rules.$(WIND_HOST_TYPE)
# Check if mapping file exists
ifneq ($(wildcard $(DOCS_ROOT)/mappingfile.txt),)
-include $(wildcard $(DOCS_ROOT)/mappingfile.txt)
endif

# Include rules that support packaging of a bsp
-include $(WIND_HOME)/setup/make/rules.resourcezip

DOC_DIR = $(DOCS_ROOT)/$(DOC_BSP_DIR)
# Include IPCOM make rules to support IPCOM build
include $(WRVX_COMPBASE)/$(COMP_IPNET2)/osconfig/vxworks/make/rules.ipcom
																							
