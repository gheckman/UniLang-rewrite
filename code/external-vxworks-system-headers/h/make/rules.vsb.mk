# rules.vsb.mk - Host independent rules for making VxWorks Source Build projects
#
# Copyright 2008-2012, Wind River Systems, Inc.
#
# The right to copy, distribute, modify or otherwise make use
# of this software may be licensed only pursuant to the terms
# of an applicable Wind River license agreement.
#
# modification history
# --------------------
# 02k,22aug12,mze  changes for default libraries
# 02j,31jan12,mze  add component valid check
# 02i,05jan12,mze  add supported tools
# 02h,13dec11,mze  change clean
# 02g,15jun11,mze  add more flags for checking
# 02f,21oct10,mze  fix IPLITE implementation
# 02e,15sep10,xhs  support IPLITE
# 02d,14jun10,mze  adding VSB info on tools to generated file.
# 02c,10mar10,mze  adding board items to vsbdefs.tcl
# 02c,03feb10,mze  change to -basic is handled in rules-lib.unix
# 02b,28dec09,mze  Alter CFLAGS when building with APP_TOOL
# 02a,09dec09,mze  adding logic to build the -basic libraries
# 01z,17nov09,mze  never use RTP CPU for building vxconfig
# 01y,06nov09,mze  post merge changes
# 01x,01oct09,mze  changes to the TOOL used for target/usr/apps
# 01w,16sep09,mze  mod to the user directories to be built.
# 01v,12sep09,mze  adding new parameter
# 01u,04sep09,mze  change build of vsbConfig.h
# 01t,03sep09,mze  adding checks for source and build flags
# 01s,01sep09,mze  adding bypass for TOOL2 not being specified.
# 01r,12aug09,mze  more restrictions on MSP user builds.
# 01p,01jun09,mze  changing LP64 MACRO
# 01o,24feb09,mze  adding lp64 option
# 01q,10aug09,mze  block MSP if not MSP build
# 01p,22apr09,mze  adding USR build rules
# 01o,24mar09,pee  fixing ipnet6only option.
# 01n,06nov08,pee  cleanup
# 01p,29oct08,mze  typo in CPU section
# 01o,28oct08,mze  mod to MSP component ADDEDCFLAG
# 01n,27oct08,mze  adding "" around the ADDEDCFLAGS
# 01m,08oct08,pee  typo in last checkin.
# 01l,02oct08,mze  changes to ADDEDCFLAGS
# 01k,23sep08,mze  add rule to clean VSB if configuration changed
# 01j,29aug08,mze  changes to SMP
# 01i,26aug08,pee  adding rule to build vsbConfig.h
# 01i,22aug08,pee  using different toolchain definition for external
#                  components.
# 01h,12aug08,mze  include -I. for all makes
# 01g,31jul08,mze  adding more vsbdefs symbols
# 01f,25jul08,pee  adding clean rule
# 01f,24jul08,mze  changes for vsbdefs.tcl SMP
# 01e,22jul08,mze  vsbdefs.tcl changes
# 01d,22jul08,pee  adding tcl info generation.
# 01c,16jul08,pee  adding building of installed components.
# 01b,27jun08,pee  adding extra build for IPV6.
# 01a,11jun08,pee  adding support for secondary compiler.
#
# 01a,04apr08,pee  created


ifneq ($(__DEFS_LIBPRJ_MK__),TRUE)
include $(WIND_BASE)/target/h/make/defs.vsb.mk
endif

include $(WIND_BASE)/target/h/make/defs.base.mk
include $(WIND_BASE)/target/h/make/defs.vsbvars.mk

VSBCLEANFILES=$(wildcard $(VSB_DIR)/vs*Clean.mk)

ifneq ($(VSBCLEANFILES),)
-include $(VSBCLEANFILES)
endif

ifneq ($(strip $(_WRS_CONFIG_ADDEDCFLAGS)),)
__VSB_ADDEDCFLAGS="$(_WRS_CONFIG_ADDEDCFLAGS)"
endif

ifneq ($(strip $(_WRS_CONFIG_ADDEDCFLAGS2)),)
__VSB_ADDEDCFLAGS2="$(_WRS_CONFIG_ADDEDCFLAGS2)"
endif

# this macro is only used for the direct compilation of MSP components
ifneq ($(strip $(_WRS_CONFIG_ADDEDCFLAGS_APP)),)
__VSB_ADDEDCFLAGSAPP="$(_WRS_CONFIG_ADDEDCFLAGS_APP)"
endif

# the rules of interrest are _build
# _build does the actual build of the VSB libraries

.PHONY : all _build 

all : _build vsbdefs.tcl

# this will ensure that the configuration files are generated before the build starts
_build :  


# list concatenation function
_concat = $(if $(word 2,$(1)),$(firstword $1)$(call _concat,$(wordlist 2,$(words $1),$1)),$1)

define common_builddef

ifeq ($(_WRS_CONFIG_$1_TOOL),)
_WRS_CONFIG_$1_TOOL = $(_WRS_CONFIG_TOOL)
endif

__CAT__ = $(call _concat,$(sort $$(_WRS_CONFIG_$1_TOOL) $(_WRS_CONFIG_$1_CPU) $(_WRS_CONFIG_$1_CPU_VARIANT)))_$3

ifeq ($(_WRS_CONFIG_$1_CPU_VARIANT),)
_CONFIG_CPUSPEC_$1_$3_ = CPU=$(_WRS_CONFIG_$1_CPU)
else
_CONFIG_CPUSPEC_$1_$3_ = CPU=$(_WRS_CONFIG_$1_CPU) ONLY_CPU_VARIANT=$(_WRS_CONFIG_$1_CPU_VARIANT)
endif

CONFIG_CLI_OPTIONS = $(foreach option,ENDIAN FP SMP,$(if $(_WRS_CONFIG_$1_$(option)),_WRS_CONFIG_$(option)=$(_WRS_CONFIG_$1_$(option)))) $$(if $$(TARGET),TARGET=$$(TARGET),)


ENDIAN = $(_WRS_CONFIG_$1_ENDIAN)
FP =  $(_WRS_CONFIG_$1_FP)
SMP = $(_WRS_CONFIG_SMP)
# temporary fix to ensure that the local directory contents get included
temp_include_current = ADDED_CFLAGS+=-I.
endef


#
# This is the section that deals with the kernel library builds for the non-MSP components 
# including target/src and IPNET. This section handles the VSB building for BSP
#


define bsp_buildrule

$(call common_builddef,$1,$2,$3)

ifneq ($$(__DEFINED_RULE_$$(__CAT__)),TRUE)

__DEFINED_RULE_$$(__CAT__) = TRUE

.PHONY : _target_$$(__CAT__)

_build : _target_$$(__CAT__)

_target_$$(__CAT__):
ifdef vsbClean
	rm -rf usr test arm cf mips ppc pentium simpc simlinux simso vsbClean.mk vsbClean.tcl
endif
ifdef _WRS_CONFIG_KSOURCE
ifdef _WRS_CONFIG_BUILD_KERNEL
	cd $2 && $(MAKE) $$(_CONFIG_CPUSPEC_$1_$3_) TOOL=$$(_WRS_CONFIG_$1_TOOL) SPACE=kernel _VSB_CONFIG_ADDEDCFLAGS=$(__VSB_ADDEDCFLAGS) _WRS_CONFIG_APP_TOOL=$$(_WRS_CONFIG_$1_APP_TOOL) VSB_DIR=$(VSB_DIR) BSPNAME=$1 $$(CONFIG_CLI_OPTIONS) $$(temp_include_current) DUAL_BUILD=false
# extra stage for default libraries build the inet6 libraries
ifdef _WRS_CONFIG_DEFAULT_VSB
	cd $2/ipnet && $(MAKE) $$(_CONFIG_CPUSPEC_$1_$3_) TOOL=$$(_WRS_CONFIG_$1_APP_TOOL) OPT=-inet6 SPACE=kernel _VSB_CONFIG_ADDEDCFLAGS=$(__VSB_ADDEDCFLAGSAPP) _WRS_CONFIG_APP_TOOL=$$(_WRS_CONFIG_$1_APP_TOOL) VSB_DIR=$(VSB_DIR) BSPNAME=$1 $$(CONFIG_CLI_OPTIONS) $$(temp_include_current) DUAL_BUILD=false
endif
endif
endif

ifndef _WRS_CONFIG_BUILD_KERNEL
ifdef _WRS_CONFIG_NETSOURCE
ifndef _WRS_CONFIG_NO_IP
	cd $(SRCDIR) && $(MAKE) vsbconfig VSB_DIR=$(VSB_DIR)  $$(_CONFIG_CPUSPEC_$1_$3_)  TOOL=$$(_WRS_CONFIG_$1_APP_TOOL)
	cd $2/ipnet  && $(MAKE) $$(_CONFIG_CPUSPEC_$1_$3_) TOOL=$$(_WRS_CONFIG_$1_APP_TOOL) SPACE=kernel _VSB_CONFIG_ADDEDCFLAGS=$(__VSB_ADDEDCFLAGSAPP) _WRS_CONFIG_APP_TOOL=$$(_WRS_CONFIG_$1_APP_TOOL) VSB_DIR=$(VSB_DIR) BSPNAME=$1 $$(CONFIG_CLI_OPTIONS) $$(temp_include_current) DUAL_BUILD=false
	cd $2/wrn    && $(MAKE) $$(_CONFIG_CPUSPEC_$1_$3_) TOOL=$$(_WRS_CONFIG_$1_APP_TOOL) SPACE=kernel _VSB_CONFIG_ADDEDCFLAGS=$(__VSB_ADDEDCFLAGSAPP) _WRS_CONFIG_APP_TOOL=$$(_WRS_CONFIG_$1_APP_TOOL) VSB_DIR=$(VSB_DIR) BSPNAME=$1 $$(CONFIG_CLI_OPTIONS) $$(temp_include_current) DUAL_BUILD=false
endif

ifdef _WRS_CONFIG_DEFAULT_VSB
ifdef _WRS_CONFIG_COMPONENT_IPNET
	cd $2/ipnet && $(MAKE) $$(_CONFIG_CPUSPEC_$1_$3_) TOOL=$$(_WRS_CONFIG_$1_APP_TOOL) OPT=-basic SPACE=kernel _VSB_CONFIG_ADDEDCFLAGS=$(__VSB_ADDEDCFLAGSAPP) _WRS_CONFIG_APP_TOOL=$$(_WRS_CONFIG_$1_APP_TOOL) VSB_DIR=$(VSB_DIR) BSPNAME=$1 $$(CONFIG_CLI_OPTIONS) $$(temp_include_current) DUAL_BUILD=false
	cd $2/ipnet && $(MAKE) $$(_CONFIG_CPUSPEC_$1_$3_) TOOL=$$(_WRS_CONFIG_$1_APP_TOOL) OPT=-inet6 SPACE=kernel _VSB_CONFIG_ADDEDCFLAGS=$(__VSB_ADDEDCFLAGSAPP) _WRS_CONFIG_APP_TOOL=$$(_WRS_CONFIG_$1_APP_TOOL) VSB_DIR=$(VSB_DIR) BSPNAME=$1 $$(CONFIG_CLI_OPTIONS) $$(temp_include_current) DUAL_BUILD=false
endif
endif

endif
endif

ifdef _WRS_CONFIG_KSOURCE 
ifdef _WRS_CONFIG_BUILD_KERNEL
ifdef _WRS_CONFIG_ENABLE_TOOL2
ifdef _WRS_CONFIG_DEFAULT_VSB
$(foreach stool, $(filter-out $(_WRS_CONFIG_$1_TOOL),$(_WRS_CONFIG_SECTOOLS)),$(newline)$(tab)+cd $2 && $(MAKE) $$(_CONFIG_CPUSPEC_$1_$3_) TOOL=$(stool) SPACE=kernel _VSB_CONFIG_ADDEDCFLAGS=$(__VSB_ADDEDCFLAGS2) VSB_DIR=$(VSB_DIR) $$(CONFIG_CLI_OPTIONS) $$(temp_include_current) VENDOR_DEFAULT=disabled DUAL_BUILD=true)
endif
ifndef _WRS_CONFIG_DEFAULT_VSB
	cd $2 && $(MAKE) $$(_CONFIG_CPUSPEC_$1_$3_) TOOL=$$(_WRS_CONFIG_$1_TOOL2) SPACE=kernel _VSB_CONFIG_ADDEDCFLAGS=$(__VSB_ADDEDCFLAGS2) VSB_DIR=$(VSB_DIR) BSPNAME=$1 $$(CONFIG_CLI_OPTIONS) $$(temp_include_current) VENDOR_DEFAULT=disabled DUAL_BUILD=true
endif
endif
endif
endif

else

$$(warning warning skipping duplicate rules for $$(__CAT__))

endif

endef


#
# This is the section that deals with the kernel library builds for the non-MSP components 
# including target/src and IPNET. This section handles the VSB building for CPU
#

define cpu_buildrule

$(call common_builddef,$1,$2,$3)

ifneq ($$(__DEFINED_RULE_$$(__CAT__)),TRUE)

__DEFINED_RULE_$$(__CAT__) = TRUE

.PHONY : _target_$$(__CAT__)

_build : _target_$$(__CAT__)

_target_$$(__CAT__):
ifdef vsbClean
	rm -rf usr test arm cf mips ppc pentium simpc simlinux simso vsbClean.mk vsbClean.tcl
endif
ifdef _WRS_CONFIG_KSOURCE 
ifdef _WRS_CONFIG_BUILD_KERNEL
	+cd $2 && $(MAKE) $$(_CONFIG_CPUSPEC_$1_$3_) TOOL=$$(_WRS_CONFIG_$1_TOOL) SPACE=kernel _WRS_CONFIG_APP_TOOL=$$(_WRS_CONFIG_$1_APP_TOOL) _VSB_CONFIG_ADDEDCFLAGS=$(__VSB_ADDEDCFLAGS) VSB_DIR=$(VSB_DIR) $$(CONFIG_CLI_OPTIONS) $$(temp_include_current) DUAL_BUILD=false
# extra stage for default libraries build the inet6 libraries
ifdef _WRS_CONFIG_DEFAULT_VSB
	+cd $2/ipnet && $(MAKE) $$(_CONFIG_CPUSPEC_$1_$3_) TOOL=$$(_WRS_CONFIG_$1_APP_TOOL) OPT=-inet6 SPACE=kernel _WRS_CONFIG_APP_TOOL=$$(_WRS_CONFIG_$1_APP_TOOL) _VSB_CONFIG_ADDEDCFLAGS=$(__VSB_ADDEDCFLAGSAPP) VSB_DIR=$(VSB_DIR) $$(CONFIG_CLI_OPTIONS) $$(temp_include_current) DUAL_BUILD=false
endif
endif
endif

ifndef _WRS_CONFIG_BUILD_KERNEL
ifdef _WRS_CONFIG_NETSOURCE
ifndef _WRS_CONFIG_NO_IP
	+cd $(SRCDIR) && $(MAKE) vsbconfig VSB_DIR=$(VSB_DIR) $$(_CONFIG_CPUSPEC_$1_$3_) TOOL=$$(_WRS_CONFIG_$1_APP_TOOL)
	+cd $2/ipnet  && $(MAKE) $$(_CONFIG_CPUSPEC_$1_$3_) TOOL=$$(_WRS_CONFIG_$1_APP_TOOL) SPACE=kernel _WRS_CONFIG_APP_TOOL=$$(_WRS_CONFIG_$1_APP_TOOL) _VSB_CONFIG_ADDEDCFLAGS=$(__VSB_ADDEDCFLAGSAPP) VSB_DIR=$(VSB_DIR) $$(CONFIG_CLI_OPTIONS) $$(temp_include_current) DUAL_BUILD=false
	+cd $2/wrn    && $(MAKE) $$(_CONFIG_CPUSPEC_$1_$3_) TOOL=$$(_WRS_CONFIG_$1_APP_TOOL) SPACE=kernel _WRS_CONFIG_APP_TOOL=$$(_WRS_CONFIG_$1_APP_TOOL) _VSB_CONFIG_ADDEDCFLAGS=$(__VSB_ADDEDCFLAGSAPP) VSB_DIR=$(VSB_DIR) $$(CONFIG_CLI_OPTIONS) $$(temp_include_current) DUAL_BUILD=false

endif

ifdef _WRS_CONFIG_DEFAULT_VSB  
ifdef _WRS_CONFIG_COMPONENT_IPNET
	+cd $2/ipnet && $(MAKE) $$(_CONFIG_CPUSPEC_$1_$3_) TOOL=$$(_WRS_CONFIG_$1_APP_TOOL) OPT=-basic SPACE=kernel _WRS_CONFIG_APP_TOOL=$$(_WRS_CONFIG_$1_APP_TOOL) _VSB_CONFIG_ADDEDCFLAGS=$(__VSB_ADDEDCFLAGSAPP) VSB_DIR=$(VSB_DIR) $$(CONFIG_CLI_OPTIONS) $$(temp_include_current) DUAL_BUILD=false
	+cd $2/ipnet && $(MAKE) $$(_CONFIG_CPUSPEC_$1_$3_) TOOL=$$(_WRS_CONFIG_$1_APP_TOOL) OPT=-inet6 SPACE=kernel _WRS_CONFIG_APP_TOOL=$$(_WRS_CONFIG_$1_APP_TOOL) _VSB_CONFIG_ADDEDCFLAGS=$(__VSB_ADDEDCFLAGSAPP) VSB_DIR=$(VSB_DIR) $$(CONFIG_CLI_OPTIONS) $$(temp_include_current) DUAL_BUILD=false
endif
endif
endif
endif

ifdef _WRS_CONFIG_KSOURCE 
ifdef _WRS_CONFIG_BUILD_KERNEL
ifdef _WRS_CONFIG_ENABLE_TOOL2
# for the default VSB build all available tools
ifdef _WRS_CONFIG_DEFAULT_VSB
$(foreach stool, $(filter-out $(_WRS_CONFIG_$1_TOOL),$(_WRS_CONFIG_SECTOOLS)),$(newline)$(tab)+cd $2 && $(MAKE) $$(_CONFIG_CPUSPEC_$1_$3_) TOOL=$(stool) SPACE=kernel _VSB_CONFIG_ADDEDCFLAGS=$(__VSB_ADDEDCFLAGS2) VSB_DIR=$(VSB_DIR) $$(CONFIG_CLI_OPTIONS) $$(temp_include_current) VENDOR_DEFAULT=disabled DUAL_BUILD=true)
endif
# for the non default VSB only build the secondary tool if enabled
ifndef _WRS_CONFIG_DEFAULT_VSB
	+cd $2 && $(MAKE) $$(_CONFIG_CPUSPEC_$1_$3_) TOOL=$$(_WRS_CONFIG_$1_TOOL2) SPACE=kernel _VSB_CONFIG_ADDEDCFLAGS=$(__VSB_ADDEDCFLAGS2) VSB_DIR=$(VSB_DIR) $$(CONFIG_CLI_OPTIONS) $$(temp_include_current) VENDOR_DEFAULT=disabled DUAL_BUILD=true
endif
endif
endif
endif

else

$$(warning warning skipping duplicate rules for $$(__CAT__))

endif

endef

#
# This is the section that deals with the kernel library builds	of the contents of the 
# wind components directory, the directory is based on a filtered list generated by vxprj when
# the VSB is created. If a directory has a VSB configuration in it then it will be added to the list that
# gets processed here.
#


define external_comp_buildrule

$(call common_builddef,$1,$2,$3)

ifneq ($$(__DEFINED_RULE_$$(__CAT__)),TRUE)

__DEFINED_RULE_$$(__CAT__) = TRUE

.PHONY : _target_$$(__CAT__)

_build : _target_$$(__CAT__)

_target_$$(__CAT__):
ifdef _WRS_CONFIG_NETSOURCE
	+cd $2 && $(MAKE) $$(_CONFIG_CPUSPEC_$1_$3_) TOOL=$$(_WRS_CONFIG_$1_APP_TOOL) SPACE=kernel _VSB_CONFIG_ADDEDCFLAGS=$(__VSB_ADDEDCFLAGSAPP) VSB_DIR=$(VSB_DIR) $$(CONFIG_CLI_OPTIONS) $$(temp_include_current) $4
endif
else

$$(warning warning skipping duplicate rules for $$(__CAT__))

endif

endef

#
# This is the section that deals with the user side library builds
#

define usr_src_buildrule

$(call common_builddef,$1,$2,$3)

ifneq ($$(__DEFINED_USR_SRC_RULE_$$(__CAT__)),TRUE)

__DEFINED_USR_SRC_RULE_$$(__CAT__) = TRUE

.PHONY : _target_usr_src_$$(__CAT__)

_build : _target_usr_src_$$(__CAT__)

_target_usr_src_$$(__CAT__):
ifdef _WRS_CONFIG_FEATURE_USR
ifdef _WRS_CONFIG_COMPONENT_USR_SRC
	+cd $(SRCDIR) && $(MAKE) vsbconfig VSB_DIR=$(VSB_DIR) $$(_CONFIG_CPUSPEC_$1_$3_)  TOOL=$$(_WRS_CONFIG_$1_TOOL)
	+cd $2 && $(MAKE) CPU=$$(_HW_$1_USR_MODEL)  TOOL=$$(_WRS_CONFIG_$1_TOOL)  SPACE=user _VSB_CONFIG_ADDEDCFLAGS=$(__VSB_ADDEDCFLAGS) VSB_DIR=$(VSB_DIR) $$(CONFIG_CLI_OPTIONS) $$(temp_include_current) $4
endif
endif
else

$$(warning warning skipping duplicate rules for $$(__CAT__))

endif

endef

#
# This is the section that deals with the user side library builds of the MSP component directories
# Note that this section is based on the call to $(WIND_BASE) and will only function if the build is a MSP build
#

define external_comp_usr_buildrule

$(call common_builddef,$1,$2,$3)

ifneq ($$(__DEFINED_EUSR_RULE_$$(__CAT__)),TRUE)

__DEFINED_EUSR_RULE_$$(__CAT__) = TRUE

.PHONY : _target_eusr_$$(__CAT__)

_build : _target_eusr_$$(__CAT__)

_target_eusr_$$(__CAT__):
ifdef _WRS_CONFIG_FEATURE_USR
ifdef _WRS_CONFIG_MSP_KERNEL
	$(MAKE) -C $2 CPU=$$(_HW_$1_USR_MODEL) TOOL=$$(_WRS_CONFIG_$1_APP_TOOL) comp-usr  _VSB_CONFIG_ADDEDCFLAGS=$(__VSB_ADDEDCFLAGSAPP) VSB_DIR=$(VSB_DIR) $$(CONFIG_CLI_OPTIONS) $$(temp_include_current) $4
endif
endif
else

$$(warning warning skipping duplicate rules for $$(__CAT__))

endif

endef


#
# This is the section that deals with the user side builds of applications, 
# this must be done after the user side libraries have been build or link failures will ocurr.
#

define usr_apps_buildrule

$(call common_builddef,$1,$2,$3)

ifneq ($$(__DEFINED_USR_APPS_RULE_$$(__CAT__)),TRUE)

__DEFINED_USR_APPS_RULE_$$(__CAT__) = TRUE

.PHONY : _target_usr_apps_$$(__CAT__)

_build : _target_usr_apps_$$(__CAT__)

_target_usr_apps_$$(__CAT__):
ifdef _WRS_CONFIG_FEATURE_USR
ifdef _WRS_CONFIG_COMPONENT_USR_APPS
	+cd $(SRCDIR) && $(MAKE) vsbconfig VSB_DIR=$(VSB_DIR) $$(_CONFIG_CPUSPEC_$1_$3_)  TOOL=$$(_WRS_CONFIG_$1_TOOL)
	+cd $2 && $(MAKE) CPU=$$(_HW_$1_USR_MODEL)  TOOL=$$(_WRS_CONFIG_$1_TOOL)  SPACE=user _VSB_CONFIG_ADDEDCFLAGS=$(__VSB_ADDEDCFLAGS) VSB_DIR=$(VSB_DIR) $$(CONFIG_CLI_OPTIONS) $$(temp_include_current) $4
ifdef _WRS_CONFIG_$1_TOOL2
ifdef _WRS_CONFIG_ENABLE_TOOL2
ifdef _WRS_CONFIG_DEFAULT_VSB
$(foreach stool, $(_WRS_CONFIG_SECTOOLS),$(newline)$(tab)+cd $2 && $(MAKE) CPU=$$(_HW_$1_USR_MODEL)  TOOL=$(stool) SPACE=user _VSB_CONFIG_ADDEDCFLAGS=$(__VSB_ADDEDCFLAGS2) VSB_DIR=$(VSB_DIR) $$(CONFIG_CLI_OPTIONS) $$(temp_include_current) $4)
endif
ifndef _WRS_CONFIG_DEFAULT_VSB
	+cd $2 && $(MAKE) CPU=$$(_HW_$1_USR_MODEL)  TOOL=$$(_WRS_CONFIG_$1_TOOL2) SPACE=user _VSB_CONFIG_ADDEDCFLAGS=$(__VSB_ADDEDCFLAGS2) VSB_DIR=$(VSB_DIR) $$(CONFIG_CLI_OPTIONS) $$(temp_include_current) $4
endif
endif
endif
endif
endif
else

$$(warning warning skipping duplicate rules for $$(__CAT__))

endif

endef

#
# This is the main build section, due to the differences in building based on 
# BSPs and CPUs this section is devided into 2 sections only one will be executed
#

# process BSPs

$(eval \
	$(foreach hwconfig,$(_HW_CONFIGURATION_BSPS),\
		$(foreach srcdir,$(_CONFIG_SRC_DIRS), $(call bsp_buildrule,$(hwconfig),$(srcdir),foo$(subst :,_,$(srcdir))))\
		$(foreach srcdir,$(_VSB_WINDCOMPONENTS), $(call external_comp_buildrule,$(hwconfig),$(srcdir),foo$(subst :,_,$(srcdir)),BSPNAME=$(hwconfig)))\
		$(foreach srcdir,$(_CONFIG_USR_SRC_DIRS), $(call usr_src_buildrule,$(hwconfig),$(srcdir),foo$(subst :,_,$(srcdir)),))\
		$(call external_comp_usr_buildrule,$(hwconfig),$(WIND_BASE),foo$(subst :,_,$(WIND_BASE)),)\
		$(foreach srcdir,$(_CONFIG_USR_APPS_DIRS), $(call usr_apps_buildrule,$(hwconfig),$(srcdir),foo$(subst :,_,$(srcdir)),))\
	)\
)


# process CPUs 

$(eval \
	$(foreach hwconfig,$(_HW_CONFIGURATION_CPUS),\
		$(foreach srcdir,$(_CONFIG_SRC_DIRS), $(call cpu_buildrule,$(hwconfig),$(srcdir),foo$(subst :,_,$(srcdir))))\
		$(foreach srcdir,$(_VSB_WINDCOMPONENTS), $(call external_comp_buildrule,$(hwconfig),$(srcdir),foo$(subst :,_,$(srcdir)),))\
		$(foreach srcdir,$(_CONFIG_USR_SRC_DIRS), $(call usr_src_buildrule,$(hwconfig),$(srcdir),foo$(subst :,_,$(srcdir)),))\
		$(call external_comp_usr_buildrule,$(hwconfig),$(WIND_BASE),foo$(subst :,_,$(WIND_BASE)),)\
		$(foreach srcdir,$(_CONFIG_USR_APPS_DIRS), $(call usr_apps_buildrule,$(hwconfig),$(srcdir),foo$(subst :,_,$(srcdir)),))\
	)\
)


all : 
	@echo done all

# this will ensure that all the directories listed in vsb_comp_list.mk are still valid
__EXISTING_WINDCOMPONENTS = $(wildcard $(_VSB_WINDCOMPONENTS))

ifneq ($(strip $(filter-out $(__EXISTING_WINDCOMPONENTS),$(_VSB_WINDCOMPONENTS))),)
__MISSING_WINDCOMPONENTS = $(strip $(filter-out $(__EXISTING_WINDCOMPONENTS),$(_VSB_WINDCOMPONENTS)))
endif

ifdef __MISSING_WINDCOMPONENTS
$(warning "Your installation has changed.")
$(warning "This VSB references missing components$(__MISSING_WINDCOMPONENTS) . ")
$(warning "This VSB must be reconfigured before it can be built")
$(error exiting build)
endif



	
_build : ;


#
# These are the	sections that build up tcl encoded information about the VSB build
#

_TCL_CONF_VARS = FP ENDIAN TOOL TOOL2 

define tclout

	@echo "set "_VSB_CONFIG_$2 $(if $(_WRS_CONFIG_$1_$2),$(_WRS_CONFIG_$1_$2),"{}") >> $3
endef

_TCL_CONF_VARS1 = SUPPORTED_TOOLS

define tclout1

	@echo "set "_VSB_CONFIG_$2 "{"$(if $(_WRS_CONFIG_diab_SUPPORTED),"diab","") $(if $(_WRS_CONFIG_gnu_SUPPORTED),"gnu","") $(if $(_WRS_CONFIG_icc_SUPPORTED),"icc","")"}" >> $3
endef

_TCL_CONF_VARS2 = SMP LP64 WRHV_GUEST BUILD_BASIC_IPNET DEFAULT_VSB DEFAULT_PRECOMP BOARD BOARD_CPU DEBUG_FLAG DEBUG_FLAG_ALLOW_OPTIMIZATION

define tclout2

	@echo "set "_VSB_CONFIG_$1 $(if $(_WRS_CONFIG_$1),$1,"{}") >> $2
endef

_TCL_CONF_VARS3 = CPU

define tclout3

	@echo "set "_VSB_CONFIG_$1 $(if $(_HW_CONFIGURATION_CPUS),$(_HW_CONFIGURATION_CPUS),"{}") >> $2
endef

_TCL_CONF_VARS4 = BSP

define tclout4

	@echo "set "_VSB_CONFIG_$1 $(if $(_HW_CONFIGURATION_BSPS),$(_HW_CONFIGURATION_BSPS),"{}") >> $2
endef

_TCL_CONF_VARS5 = INET6 INET6_ONLY INET4_ONLY

ifdef _WRS_CONFIG_COMPONENT_IPNET
define tclout5

	@echo "set "_VSB_CONFIG_$1 $(if $(_WRS_CONFIG_FEATURE_IPNET_$1),$1,"{}") >> $2
endef
endif

ifdef _WRS_CONFIG_COMPONENT_IPLITE
define tclout5

	@echo "set "_VSB_CONFIG_$1 $(if $(_WRS_CONFIG_FEATURE_IPLITE_$1),$1,"{}") >> $2
endef
endif

ifndef _WRS_CONFIG_COMPONENT_IPNET
ifndef _WRS_CONFIG_COMPONENT_IPLITE
define tclout5

	@echo "set "_VSB_CONFIG_$1 $(if $(_WRS_CONFIG_FEATURE_IPNET_$1),$1,"{}") >> $2
endef
endif
endif



vsbdefs.tcl : h/config/auto.conf vsb_defs.mk
	@echo "# this file is automatically generated" > $@
	$(foreach conf,$(_HW_CONFIGURATION_CPUS) $(_HW_CONFIGURATION_BSPS),$(foreach var,$(_TCL_CONF_VARS),$(call tclout,$(conf),$(var),$@)))
	$(foreach conf,$(_HW_CONFIGURATION_CPUS) $(_HW_CONFIGURATION_BSPS),$(foreach var,$(_TCL_CONF_VARS1),$(call tclout1,$(conf),$(var),$@)))
	$(foreach var,$(_TCL_CONF_VARS2),$(call tclout2,$(var),$@))
	$(foreach var,$(_TCL_CONF_VARS3),$(call tclout3,$(var),$@))
	$(foreach var,$(_TCL_CONF_VARS4),$(call tclout4,$(var),$@))
	$(foreach var,$(_TCL_CONF_VARS5),$(call tclout5,$(var),$@))

vsbconfig : h/config/vsbConfig.h vsbdefs.tcl

h/config/vsbConfig.h :
	+cd $(SRCDIR) && $(MAKE) vsbconfig VSB_DIR=$(VSB_DIR)



# make clean command. This is simply a build with TARGET=rclean - now optimized to just remove the VSB contents

clean :
	rm -rf usr test arm cf mips ppc pentium simpc simlinux simso vsbClean.mk vsbClean.tcl
#	$(MAKE) TARGET=rclean

default:
	@echo No Target to Build
