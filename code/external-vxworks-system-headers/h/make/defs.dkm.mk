# defs.dkm.mk - Host independent rules for making VxWorks Downloadable Kernel Modules
#
# Copyright 2008, Wind River Systems, Inc.
#
# modification history
# --------------------
# 04d,21jun10,pee  modify for dkm project
# 04c,04sep08,pee  removing defs.options, now included from defs.default.
# 04b,26aug08,pee  created


ifndef __DEFS_DEFAULT_INCLUDED
include $(TGT_DIR)/h/make/defs.default
endif

include $(TGT_DIR)/h/tool/$(TOOL_FAMILY)/make.$(CPU)$(TOOL)
include $(TGT_DIR)/h/make/defs.option
include $(TGT_DIR)/h/make/defs.$(WIND_HOST_TYPE)

ifneq ($(wildcard $(VSB_MAKE_CONFIG_FILE)),)
include $(VSB_MAKE_CONFIG_FILE)
endif



DEFS_DKM_MK_INCLUDED = TRUE

# default values
ifdef OBJ_BASE_NAME
OBJ_BASE_NAMES ?= $(OBJ_BASE_NAME)
endif

# set directories

OBJ_DIR_ROOT ?= .

$(foreach base,$(OBJ_BASE_NAMES),$(eval OBJ_SUBDIR_$(base)=obj$$(CPU)$$(TOOL_SPECIFIC_DIR)$(base)))

$(foreach base,$(OBJ_BASE_NAMES),$(eval OBJDIR_$(base)=$$(OBJ_DIR_ROOT)/$$(OBJ_SUBDIR_$(base))))

$(foreach base,$(OBJ_BASE_NAMES),$(eval OBJS_$(base)?=$$(OBJS)))

$(foreach base,$(OBJ_BASE_NAMES),$(eval DEPEND_$(base)=$$(OBJS_$(base):.o=.d)))

ALL_OBJS =  $(foreach base,$(OBJ_BASE_NAMES),$(OBJDIR_$(base))/$(OBJS_$(base))) $(OBJS)

EXISTING_OBJECTS = $(wildcard $(ALL_OBJS))
REQUIRED_DEPFILES = $(EXISTING_OBJECTS:.o=.d)
EXISTING_DEPFILES = $(wildcard $(REQUIRED_DEPFILES))
MISSING_DEPFILES = $(filter-out $(EXISTING_DEPFILES), $(REQUIRED_DEPFILES))


