# rules.fs - makefile target rules for embedding a ROMFS file system image
#
# Copyright 2004-2005, Wind River Systems, Inc.
#
# modification history
# --------------------
# 01g,29jul05,rec  coldfire support.
# 01f,02feb05,lei  print out a message for target ROMFS_CONTENT.
# 01e,06oct04,h_k  added prefix "_" to romfsImage and romfsImageEnd for SH.
#                  (SPR #102341)
# 01d,24sep04,c_c  Allow possible previous definition of ROMFS_CONTENT to take
# 		   precedence over the default value.
# 01c,24sep04,c_c  Fixed a problem when ROMFS_CONTENT is set to nothing.
# 01b,17sep04,c_c  Fixed SPR 99797.
# 01a,22jun04,c_c  written
#
# DESCRIPTION
# This file contains rules used for embedding a filesystem within vxWorks image.
# One can change default build by overriding either:
# ROMFS_CONTENT, which is a binary image of a ROMFS filesystem filled with 
# files that are to be embedded on the target
# ROMFS_DIR, which represent a directory tree on the local filesystem that
# contains all the files that are to be embedded on the target.
#
# This file is included by rules.project and rules.bsp, and rely on all the 
# rules that are defined by regular target builds (.o.s, $(CC), ...), and 
# therefore may not work is included standalone.

# We must provide different name for the generated assembly file (ROMFS_IMAGE),
# to avoid any problem if the generated file exists in the BSP directory, and,
# therefore could be fetched through the vpath directive.

ifneq ($(PRJ_DIR),)

ifeq ($(ROMFS_DIR),)
ROMFS_DIR	= $(PRJ_DIR)/romfs
endif

ifeq ($(ROMFS_CONTENT),)
ROMFS_CONTENT	= $(PRJ_DIR)/content.romfs
endif

ROMFS_IMAGE	= romfs_image_prj.o
else

ifeq ($(ROMFS_DIR),)
ROMFS_DIR	= romfs
endif

ifeq ($(ROMFS_CONTENT),)
ROMFS_CONTENT	= content.romfs
endif

ROMFS_IMAGE	= romfs_image.o
endif

ifneq ($(VX_CPU_FAMILY),sh)
 ifeq ($(VX_CPU_FAMILY),cf)
    # cf require leading prefix "_"
    ROMFSIMAGE_SYM_NAME = _romfsImage
 else
    # everyone else
    ROMFSIMAGE_SYM_NAME = romfsImage
 endif
else
    # sh require leading prefix "_"
    ROMFSIMAGE_SYM_NAME = _romfsImage
endif

# Be sure that if some variable have been given as WIN32 path we handle them
# correctly

override ROMFS_CONTENT	:= $(subst \,/,$(ROMFS_CONTENT))
override ROMFS_DIR	:= $(subst \,/,$(ROMFS_DIR))

###############################################################################
#
# Rule for rebuilding ROMFS image
#
#  mkromfs:  -q 		quiet mode
#	     -n 		only create filesys if files changed in input
#	     -o $(ROMFS_CONTENT)output file name
# 

# Dummy target to force call to MKROMFS, which will take care of updating
# ROMFS content.
__always_build:

# Create a filesystem binary image from a directory content.
# We do the binary image if ROMFS_DIR is really a dir. Otherwise, we create a
# zero-length file if no file was existing before.

$(ROMFS_CONTENT) : __always_build
	@if [ -d "$(ROMFS_DIR)" ]; then \
	$(MKROMFS) -q -n -o $@ $(ROMFS_DIR) ; \
	else \
	    if [ ! -f "$@" ]; then touch $@; fi; \
	fi
	@$(ECHO) "$(ROMFS_CONTENT) build done"

# Create on object file from a filesystem image;
# - We use an assembly file that will include the binary image. 
# - we create two symbols that will point to the beginning and the end of this
#   binary image.
#
# The configlette and the BSP init code will guess if there is an embedded file
# system if the difference between the two symbols' address is > 0.


$(ROMFS_IMAGE:.o=.s) : $(ROMFS_CONTENT)
	@if [ -s "$<" ]; then \
	$(ECHO) "\t.section \".rodata\"\n\
\t.global	$(ROMFSIMAGE_SYM_NAME)\n\
\t.global	$(ROMFSIMAGE_SYM_NAME)End\n\
$(ROMFSIMAGE_SYM_NAME):\n\
\t.incbin	\"$<\"\n\
$(ROMFSIMAGE_SYM_NAME)End:\n" > $@; \
	else \
	$(ECHO) "\t.section \".rodata\"\n\
\t.global	$(ROMFSIMAGE_SYM_NAME)\n\
\t.global	$(ROMFSIMAGE_SYM_NAME)End\n\
$(ROMFSIMAGE_SYM_NAME):\n\
$(ROMFSIMAGE_SYM_NAME)End:\n" > $@;\
	fi

