# rules.dkm.mk - Host independent rules for making VxWorks Downloadable Kernel Modules
#
# Copyright 2008, 2010, 2012 Wind River Systems, Inc.
#
# The right to copy, distribute, modify or otherwise make use
# of this software may be licensed only pursuant to the terms
# of an applicable Wind River license agreement.
#
# modification history
# --------------------
# 01e,07aug12,pee  WIND00368576 fixed typo in c++/s rules
# 01d,02feb12,mze  add .CPP as a valid suffix
# 01c,02jul10,pee  update clean
# 01b,21jun10,pee  modify for dkm project
# 01a,26aug08,pee  created

ifndef DEFS_DKM_MK_INCLUDED
include $(TGT_DIR)/h/make/defs.dkm.mk
endif

define buildrule

$$(OBJDIR_$(1)) :
	$$(MKDIR) $$(OBJDIR_$(1))

# rules to build objects in $(OBJDIR)
$$(OBJDIR_$(1))/%.o : %.c | $(TOOL_OPTIONS_FILES_ALL) $$(OBJDIR_$1)
	$$(CC) $$(CFLAGS) $$(CFLAGS_OBJ_$1) $$(CC_SDA_FLAGS) $$(OPTION_DEPEND_GEN_D) $$(CFLAGS_$$(<:.c=.o)) $$(OPTION_OBJECT_ONLY) $$(OPTION_OBJECT_NAME)$$@ $$<

$$(OBJDIR_$(1))/%.o : %.s $(TOOL_OPTIONS_FILES_ALL) $$(OBJDIR_$1)
	$$(CC) $$(CFLAGS_AS) $$(CFLAGS_AS_OBJ_$1) $$(OPTION_DEPEND_GEN_D) $$(CFLAGS_AS_$$(<:.s=.o)) $$(OPTION_OBJECT_ONLY) $$(OPTION_OBJECT_NAME)$$@ $$<

# rule for munchless C++ compiles
$$(OBJDIR_$(1))/%.o : %.CPP $(TOOL_OPTIONS_FILES_ALL) $$(OBJDIR_$1)
	$$(CXX) $$(C++FLAGS) $$(C++FLAGS_OBJ_$1) $$(OPTION_DEPEND_GEN_D) $$(CFLAGS_$$(<:.CPP=.o)) $$(OPTION_OBJECT_ONLY) $$(OPTION_OBJECT_NAME)$$@ $$<

$$(OBJDIR_$(1))/%.o : %.cpp $(TOOL_OPTIONS_FILES_ALL) $$(OBJDIR_$1)
	$$(CXX) $$(C++FLAGS) $$(C++FLAGS_OBJ_$1) $$(OPTION_DEPEND_GEN_D) $$(CFLAGS_$$(<:.cpp=.o)) $$(OPTION_OBJECT_ONLY) $$(OPTION_OBJECT_NAME)$$@ $$<

endef

# rules to build objects in current directory
%.o : %.c | $(TOOL_OPTIONS_FILES_ALL)
	$(CC) $(CFLAGS) $(CFLAGS_$@) $(CC_SDA_FLAGS) $(OPTION_DEPEND_GEN_D) $(CFLAGS_$(<:.c=.o)) $(OPTION_OBJECT_ONLY) $(OPTION_OBJECT_NAME)$@ $<

%.o : %.s | $(TOOL_OPTIONS_FILES_ALL)
	$(CC) $(CFLAGS_AS) $(CFLAGS_AS_$@) $(OPTION_DEPEND_GEN_D) $(CFLAGS_AS_$(<:.s=.o)) $(OPTION_OBJECT_ONLY) $(OPTION_OBJECT_NAME)$@ $<

# rule for munchless C++ compiles
%.o : %.CPP | $(TOOL_OPTIONS_FILES_ALL)
	$(CXX) $(C++FLAGS) $(C++FLAGS_$@) $(OPTION_DEPEND_GEN_D) $(CFLAGS_$(<:.CPP=.o)) $(OPTION_OBJECT_ONLY) $(OPTION_OBJECT_NAME)$@ $<

%.o : %.cpp | $(TOOL_OPTIONS_FILES_ALL)
	$(CXX) $(C++FLAGS) $(C++FLAGS_$@) $(OPTION_DEPEND_GEN_D) $(CFLAGS_$(<:.cpp=.o)) $(OPTION_OBJECT_ONLY) $(OPTION_OBJECT_NAME)$@ $<

# define targets

all : $(ALL_OBJS)

release : all

clean :
	$(RM) $(ALL_OBJS) 
	$(RM) $(EXISTING_DEPFILES) 

precomp :

# expand build rules

$(eval $(foreach base, $(OBJ_BASE_NAMES), $(call buildrule,$(base))))

# include dependency files
ifneq ($(EXISTING_DEPFILES),)
include $(EXISTING_DEPFILES)
endif
ifneq ($(MISSING_DEPFILES),)
$(warning missing dependency files $(MISSING_DEPFILES))
endif

