# rules.bsp2.mk - BSP2 makefile target rules  
#
# Copyright (c) 2010 Wind River Systems, Inc.
#
# The right to copy, distribute, modify or otherwise make use
# of this software may be licensed only pursuant to the terms
# of an applicable Wind River license agreement.
#
# modification history
# --------------------
# 01f,14dec10,mze  change tools
# 01e,13dec10,mze  update
# 01d,13dec10,pee  tuning
# 01c,10dec10,pee  update
# 01b,08dec10,mze  more tweaks
# 01a,01dec10,mze  created
#
# DESCRIPTION
# This file contains rules used in building targets from the BSP2 directories.
#
# This file is only for command line builds from the BSP directory.  BSPs that include
# rules.bsp2.mk are only capable of building VIP projects this is inclusive of bootroms
# of all natures.
#


include $(WRVX_COMPBASE)/$(COMP_IPNET2)/osconfig/vxworks/make/defs.ipcom

include $(TGT_DIR)/h/make/rules.memory
include $(TGT_DIR)/h/make/defs.base.mk

################################################################################
#
# Dependency search path of .a files
#

vpath %.a $(patsubst -L%,%,$(LD_LINK_PATH))

################################################################################
#
# meta build targets
#
release : $(RELEASE)
#$(warning release is set to $(RELEASE))
## make will default to "exe"


# check to see if it is a SMP project
ifdef _WRS_CONFIG_SMP
prjOpt  = -smp
newPRJNAME = $(BSP_NAME)_$(TOOL)_$(newName)_vxWorks

_BOOTROM_TARGETS = bootrom bootrom_uncmp bootrom_res bootrom_res_high bootapp bootapp.sym bootapp.hex

$(_BOOTROM_TARGETS):
	@echo ERROR: SMP bootrom image builds are not supported.
	@cho "       Please build VxWorks UP bootrom image to boot"
	echo "       VxWorks $(VXBUILD) images."

newName = smp
# check to see if it is also LP64 project
ifdef _WRS_CONFIG_LP64
prjOpt  += -lp64
newName =lp64_smp
endif
else

# check if  LP64 project
ifdef _WRS_CONFIG_LP64
prjOpt  += -lp64
newName = lp64
newPRJNAME = $(BSP_NAME)_$(TOOL)_$(newName)_vxWorks
endif
endif

# parameters:
# $1 project name - will be preceedeed by $(BSP_NAME)_$(TOOL)
# $2 build targets
# $3 profile
# $4 options

_VIP_TOOLS = $(TOOL)

release : _VIP_TOOLS=$(RELEASE_TOOLS)
release : _PreWarning=
release : _PostWarning=

define __createVIP
	$(call print,$(call _PreWarning,$(BSP_NAME)_$(TOOL)$1,$(TGT_DIR)/proj/),)
	@echo creating project
	$(foreach tool,$(_VIP_TOOLS),$(newline)$(tab)cd $(TGT_DIR)/proj && vxprj create -force $4 $(if $3, -profile $3) $(BSP_NAME) $(tool) $(BSP_NAME)_$(tool)$1)
	 @echo building project
	$(foreach btool,$(_VIP_TOOLS),$(foreach spec, $2,$(newline)$(tab)cd $(TGT_DIR)/proj/$(BSP_NAME)_$(btool)$1 && vxprj build $(spec)))
	$(call print,$(call _PostWarning,$(BSP_NAME)_$(TOOL)$1,$(TGT_DIR)/proj/),)
	@echo  done
endef

exe :
ifndef _WRS_CONFIG_SMP
ifndef _WRS_CONFIG_LP64
	$(call __createVIP,, default)
endif
endif
ifdef _WRS_CONFIG_SMP
ifndef _WRS_CONFIG_LP64
	$(call __createVIP,_smp,default,,-smp)
endif
endif
ifndef _WRS_CONFIG_SMP
ifdef _WRS_CONFIG_LP64
	$(call __createVIP,_lp64,default,,-lp64)
endif
endif
ifdef _WRS_CONFIG_SMP
ifdef _WRS_CONFIG_LP64
	$(call __createVIP,_lp64_smp,default,,-lp64 -smp)
endif
endif
	


vxWorks : 
	$(call __createVIP,, default)

vxWorks_smp:
	$(call __createVIP,_smp,default,,-smp)

vxWorks_lp64:
	$(call __createVIP,_lp64,default,,-lp64)

vxWorks_lp64_smp:
	$(call __createVIP,_lp64_smp,default,,-lp64 -smp)


vxWorks.st: 
	$(call __createVIP,_vxWorks.st,default,PROFILE_STANDALONE_DEVELOPMENT,)

vxWorks.st_smp:
	$(call __createVIP,_smp_vxWorks.st,default,PROFILE_STANDALONE_DEVELOPMENT,-smp)

vxWorks.st_lp64:
	$(call __createVIP,_lp64_vxWorks.st,default,PROFILE_STANDALONE_DEVELOPMENT,-lp64)

vxWorks.st_lp64_smp:
	$(call __createVIP,_lp64_smp_vxWorks.st,default,PROFILE_STANDALONE_DEVELOPMENT,-lp64 -smp)

vip_bootrom:
	$(call __createVIP,_bootrom,vxWorks_romCompress.bin,PROFILE_BOOTROM_COMPRESSED_BASIC,)

vip_lp64_bootrom:
	$(call __createVIP,_lp64_bootrom,vxWorks_romCompress.bin,PROFILE_BOOTROM_COMPRESSED_BASIC,-lp64)

vip_bootrompxe:
	$(call __createVIP,_bootrom,vxWorks_romCompress.bin vxWorks_romCompress.pxe,PROFILE_BOOTROM_COMPRESSED_BASIC,)

vip_lp64_bootrompxe:
	$(call __createVIP,_lp64_bootrom,vxWorks_romCompress.bin vxWorks_romCompress.pxe,PROFILE_BOOTROM_COMPRESSED_BASIC,-lp64)

NEW_VX_TARGETS = exe vxWorks_lp64 vxWorks_lp64_smp vxWorks vxWorks_smp vxWorks.st vxWorks.st_smp vxWorks.st_lp64 vxWorks.st_lp64_smp

NEW_VIP_BOOT = vip_lp64_bootrom  vip_bootrom
NEW_VIP_BOOTPXE = vip_lp64_bootrompxe  vip_bootrompxe

# _BOOTROM_TARGETS = bootrom bootrom_uncmp bootapp

# bootrom_uncmp: PROFILE= -profile PROFILE_BOOTROM_BASIC
# bootapp : PROFILE= -profile PROFILE_BOOTAPP_BASIC

# bootrom_uncmp: newPRJNAME = $(BSP_NAME)_$(TOOL)_$(newName)_bootrom_uncmp
# bootapp : newPRJNAME = $(BSP_NAME)_$(TOOL)_$(newName)_bootram


define _PreWarning 

"*********************************************************************"
"* WARNING: make from the BSP directory is not supported for $(BSP_NAME),"
"* please move to using the 'vxprj' command line build."
"* To ease migration, the project $(1)"
"    will be created in directory:"
" $(2)"
"*********************************************************************"
endef


define _PostWarning

"*********************************************************************"
"* WARNING: make from the BSP directory is not supported for $(BSP_NAME),"
"* please move to using the 'vxprj' command line build."
"* To ease migration, the project $(1)"
"    has been created in directory:"
""
" $(2)"
""
"* Changes made in $(1) will be"
"    deleted the next time make is invoked in the BSP directory."
"* Do not mix using BSP builds and vxprj command builds."
"*********************************************************************"
endef


newPRJ_FULLPATH = $(TGT_DIR)/proj/$(newPRJNAME)

_OTHER_TARGETS = vxWorks_rom vxWorks.res_rom vxWorks.res_rom_res_low vxWorks.res_rom_nosym vxWorks.res_rom_nosym_res_low vxWorks.sym vxWorks.hex vxWorks.old vxWorks.bin

.PHONY : $(_BOOTROM_TARGETS) $(_STANDALONE_TARGETS) $(_OTHER_TARGETS) clean

$(_OTHER_TARGETS) :
	@echo ERROR: Building target $@ is not supported for
	@echo "       VxWorks $(BSP_NAME) from BSP builds."
	@echo "       Please use the 'vxprj' project facility."

clean :
	@echo ERROR: Cleaning $(BSP_NAME) project is not supported from BSP directory.
	@echo "       Please look at $(newPRJ_FULLPATH)"
	@echo "       for the $(BSP_NSME) project created from this directory."

%.old %.bin %.hex : % ;


include $(TGT_DIR)/h/make/rules.bspmacros.mk
