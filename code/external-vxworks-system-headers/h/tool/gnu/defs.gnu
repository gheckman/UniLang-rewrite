# defs.gnu - definitions for GNU toolchain builds
#
# Copyright (c) 2000-12 Wind River Systems, Inc.
#
# The right to copy, distribute, modify or otherwise make use
# of this software may be licensed only pursuant to the terms
# of an applicable Wind River license agreement.
#
# modification history
# --------------------
# 04l,29aug12,mze  change to system-headers warning
# 04k,21aug12,mze  add -Wsystem-headers flag
# 04j,05jul12,pee  WIND00356899
# 04i,13jun11,mze  add DEBUG FLAGS
# 04h,16nov10,pee  WIND00240589
# 04g,08nov10,zl   added CC_WARNINGS_IGNORE_DEPRECATED
# 04g,28oct10,pee  WIND00233594
# 04f,16jul10,mze  add fno-zero-initialized-in-bss to CC_COMPILER
# 04e,26may10,pee  adding line no to CPP
# 04d,08apr10,pee  adding missing vxWorks link flags
# 04c,16dec09,mcm  Adding option to enable warnings for system headers
# 04b,02jul09,pee  define section splittion option for CC
# 04a,26jun09,pee  adding defs for section splitting.
# 03z,17jun09,pee  moving munch to defs.common
# 03y,28jul09,svc  pick up 64 bit compiler change
# 03x,28jul09,jam  64 bit compiler fix
# 03w,21jul09,mcm  Adding extra link flags for BSP builds.
# 03v,08jul09,pee  adding linker options derived from VSB.
# 03u,11jun08,pee  VSB adaptation
# 03t,11sep07,pes  Remove -fpic from OPTION_PIC
# 03s,02jul07,zl   added -ansi to CPP_PRINT_MACROS.
# 03r,27jun07,mcm  Adding support for abridged and standard versions of
#                  libstdc++.a
# 03q,07jun07,pee  reorganized SDA builds for VIP.
# 03p,11may07,dcc  temporal disable of SDA builds.
# 03o,05may07,dcc  added CC_SDA_FLAGS.
# 03n,10feb06,pee  added linker symbol definition
# 03m,22aug05,pee  Added OPTION_DEPEND_TARGET
# 02y,18jul05,pee  Added CC_LIBINTRINSICS
# 02x,08Jul05,pee  Added OPTION_CC_GENMAP
# 02w,29apr05,md   Added OPTION_DEPEND_GEN_D 
# 02v,16feb05,pee  Added OPTION_POINTERS_VOLATILE 
# 02u,15nov04,gvm  Fix for SPR103853: no -P when pre-processing assembly files.
# 02t,16sep04,mcm  Adding -fno-zero-initialized-in-bss
# 02s,12jul04,fle  Improved support for data alignment
# 02r,15jun04,fle  SPR#98164 : substitute backslashes with slashes in CC_BASE
# 02q,29apr04,c_c  Get compiler version from the resource file.
# 02p,04may04,mcm  Updating compiler version to 3.3.2-vxworks60
# 02o,26apr04,f_b  Removed absolute path to objcopy to prepare for new
#                  directory structure and align with how nm & size are found
# 02n,03feb04,mcm  Fix for SPR 93149
# 02m,09feb04,fle  Updated to new host utilities location
# 02l,22jan04,zmm  Moved definitions of  ROM_ENTRY, SYS_ENTRY and USR_ENTRY
#                  into defs.common
# 02k,09jan04,c_c  Don't hardcode compiler path in macro (SPR #92774).
# 02j,10dec03,dbt  Updated for GCC 3.3.2 compiler
# 02i,07nov03,c_c  Check compiler version.
# 02h,15oct03,dat  New warning macros
# 02g,19aug03,fle  SPR#88802, set TCL to tclsh and added WTXTCL macro
# 02f,06may02,sn   SPR 76627 - Use CC to link by default
# 02e,03may02,tpw  LD_SCRIPT_DOWNLOAD cannot be derived from LD_SCRIPT_RAM.
#                  It meshes poorly with scripts not named link.RAM (PPC4xx).
# 02d,01may02,sn   Restore TOOL_VENDOR (some people use it)
# 02c,24apr02,sn   SPR 75835 - collapse sections into text/data/bss before
#                  download
# 02b,24apr02,sn   SPR 75123 - always munch -c (avoiding idiosyncratic asm
#                  behaviour)
# 02a,25apr02,pai  introduced HLL_PREFIX so that prepended underscores could
#                  be redefined in architecture/toolchain fragments (SPR 73382)
# 01z,21mar02,rbl  adding macro so that project facility can add -fvolatile to
#                  bsp files
# 01y,19mar02,dat  Adding PIC flags for bootInit.o (72825)
# 01x,13mar02,sn   SPR 74080 - added large project support for Diab
# 01w,12feb02,sn   removed obsolete refs to GCC_EXEC_PREFIX
# 01v,06feb02,t_m  change ranlib to ranlib$(TOOLENV)
# 01u,21jan02,sn   removed obsolete WFC flags
# 01t,13dec01,jab  added make variable BOOTCONFIG_FLAGS
# 01s,05dec01,tpw  Use TGT_DIR to find linker scripts.
# 01r,13nov01,tam  changed definition of CC_LIB (repackaging)
# 01q,05nov01,rbl  let project facility know about optimization flags
# 01p,09nov01,tam  fixed use of OPTION_PASS_TO_LD; renamed TOOL_CONFIG
# 01o,02nov01,dat  adding -w to dependency generation options
# 01n,30oct01,tpw  Take generic defaults from new fragment defs.common
# 01m,29oct01,jab  added new ld script variables
# 01l,26oct01,tam  fixed Wl usage after merge
# 01k,19oct01,j_s  define cyclic link support macros
#		   add TOOL_CONFIG
# 01j,24oct01,dat  Relocating tool specific macros
# 01i,24oct01,jab  added new dependency generation variables
# 01h,23oct01,jab  added variables from defs.default cleanup
# 01g,19oct01,jab  added make variables for dependency generation option
# 01f,18oct01,dat  Moving tool specific defines out of target/h/make
# 01e,12sep01,sn   added LARGE_PROJECT, MUNCH_FLAGS and LD_PARTIAL
# 01d,05jun01,mem  Added EXTRACT_HEX_FLAG, EXTRACT_BIN_FLAG, VMA_START &
#                  VMA_FLAGS
# 01c,13mar01,sn   added defn of OPTION_LANG_ASM
# 01b,10jan01,sn   added defn of OPTION_LANG_C
# 01a,16oct00,sn   wrote
#
# DESCRIPTION
# This file contains default definitions and flags for builds that use the 
# GNU toolchain.

## generic defaults from defs.common come first, so they can be overridden

include $(TGT_DIR)/h/tool/common/defs.common

# get TOOL_COMMON_DIR, TOOL_DIAB and TOOL_GNU from TOOL

TOOL_FAMILY	= gnu
# TOOL_COMMON_DIR	= $(subst gnu,common,$(TOOL))
TOOL_COMMON_DIR = $(BUILD_FP_PREFIX)common$(BUILD_ENDIAN_SUFFIX)
TOOL_SPECIFIC_DIR       = $(BUILD_FP_PREFIX)$(TOOL_FAMILY)$(BUILD_ENDIAN_SUFFIX)
TOOL_DIAB	= $(subst gnu,diab,$(TOOL))
TOOL_GNU	= $(TOOL)

# Deprecated, use TOOL_FAMILY instead
TOOL_VENDOR     = gnu

# Preprocessor option forcing every input file to be treated as a "C" file
OPTION_LANG_C=-xc

## set path to gnu utilities 

CC_HOST = $(WIND_HOST_TYPE)

# Set path to gnu utilities:
# if WIND_GNU_PATH is set, then use it as the compiler base directory.
# else, if WIND_GNU_VERSION is set, use it.
# else, get the version from tools.version file.

ifneq ($(WIND_GNU_PATH),)
CC_BASE		= $(subst \,/,$(WIND_GNU_PATH))
else
# set default version to WIND_GNU_VERSION set in 
# $(WIND_BASE)/host/resource/hutils/tools.version, but allow environment, 
# ARCH or CPU specific make fragment to override the value.

ifeq ($(WIND_GNU_VERSION),)
include $(WIND_BASE)/host/resource/hutils/tools.version
endif
CC_VERSION	= $(WIND_GNU_VERSION)
endif

ifeq ($(WIND_HOST_TYPE),x86-win32)
ifneq ($(Path),)
export Path		:= $(CC_BIN_DIR);$(Path)
endif
ifneq ($(PATH),)
export PATH		:= $(CC_BIN_DIR);$(PATH)
endif
else
ifneq ($(PATH),)
export PATH		:= $(CC_BIN_DIR):$(PATH)
endif
endif

# Preprocessor option forcing every input file to be treated as a assembly
# file requiring C preprocessing
OPTION_LANG_ASM=-xassembler-with-cpp

# Library containing compiler support routines
CC_LIB=
CC_LIBINTRINSICS	= -lgcc


OPTION_PP		= -E
OPTION_PP_AS		=
OPTION_PP_NOLINENO	= -P
OPTION_PP_COMMENT	= -C
OPTION_DOLLAR_SYMBOLS	= -fdollars-in-identifiers
OPTION_DEPEND		= -M -w
OPTION_DEPEND_GEN	= -M -MG -w
OPTION_DEPEND_GEN_D	= -MD
OPTION_DEPEND_C		= $(OPTION_DEPEND_GEN)
OPTION_DEPEND_AS	= $(OPTION_DEPEND)
OPTION_DEPEND_TARGET	= -MT
OPTION_NO_WARNINGS	= -w
OPTION_ANSI		= -ansi
OPTION_OBJECT_ONLY	= -c
OPTION_INCLUDE_DIR	= -I
OPTION_CC_GENMAP	= -Wl,-Map,$@.map,-cref
OPTION_LD_GENMAP	= -Map $@.map -cref

OPTION_CC_SPLIT_SECTIONS = -ffunction-sections -fdata-sections

# this line has a space at the end ("-o ")
OPTION_OBJECT_NAME	= -o 
OPTION_EXE_NAME		= $(OPTION_OBJECT_NAME)
OPTION_DEFINE_MACRO	= -D
OPTION_PIC		=
OPTION_POINTERS_VOLATILE = -fvolatile

CC_OPTIM_XO =  -O
CC_OPTIM_DEBUG =
CC_OPTIM_DRIVER		= $(CC_OPTIM_DEBUG) -fvolatile
CC_OPTIM_NORMAL		= $(CC_OPTIM_DEBUG) $(CC_OPTIM_XO) -fstrength-reduce -fcombine-regs
CC_OPTIM_TARGET		= $(CC_OPTIM_DEBUG) $(CC_OPTIM_XO) -fvolatile

ifeq ($(VX_CPU_FAMILY), ppc)
ifeq ($(SDA_DISABLE),)
CC_SDA_FLAGS = -G8 -msdata=eabi
endif
endif

LD_LINK_PATH_EXTRA      += -L$(LD_LINK_TOOL_DIR)_$(CXX_STL_VARIANT)$(MINOR_OPTION_SUFFIX) 

ifeq ($(CXX_STL_VARIANT),)
CXX_STL_VARIANT         = standard 
# If you would like to create projects using the abridged standard library,
# replace the above line with:
# CXX_STL_VARIANT       = abridged
endif

# Old warning macros
OPTION_SYS_HEADERS = -Wsystem-headers
CC_WARN_SYSTEM_HEADERS  =

CC_WARNINGS_ALL		= -Wall $(CC_WARN_SYSTEM_HEADERS)
CC_WARNINGS_NONE	=

# option to override warnings for symbols declared with _WRS_DEPRECATED 

CC_WARNINGS_IGNORE_DEPRECATED = -Wno-deprecated-declarations

# New warning macros.  The new default is CC_WARNINGS_LOW, but for GNU
# we are leaving the setting the same as before (-Wall).  As we switch
# to Diab, we are also requiring that the base library build be error
# AND warning free.  The higher settings are for code inspection and lint
# purposes.

CC_WARNINGS_HIGH	= $(CC_WARNINGS_ALL)
CC_WARNINGS_MED		= $(CC_WARNINGS_ALL)
CC_WARNINGS_LOW		= $(CC_WARNINGS_ALL)

CC_COMPILER		= -ansi -fno-zero-initialized-in-bss 
C++_COMPILER		= -ansi -fno-zero-initialized-in-bss 

# used by project facility

CC_PROJECT_OPTIMIZE_FLAGS = -O -O1 -O2 -O3 -O4
PROJECT_BSP_FLAGS_EXTRA = $(filter -fvolatile,$(CC_OPTIM_TARGET)) $(CC_SDA_FLAGS)

# For generating PIC code
# For T2.2, CC_PIC is only defined for MIPS architecture see defs.mips.
# CC_PIC		= $(OPTION_PIC)

## C flags

#CFLAGS += -fno-zero-initialized-in-bss

## toolchain binaries

AS              	= as$(TOOLENV)
CC              	= cc$(TOOLENV)
CF			= CC
CXX			= $(CC)
LD              	= ld$(TOOLENV)
RANLIB          	= ranlib$(TOOLENV)
CPP			= $(CC) -E
CPP_PRINT_MACROS	= $(CPP) -dM -E -pipe -ansi $(CC_INCLUDE) $(CC_DEFINES)
TCL			= tclsh
WTXTCL			= wtxtcl
OBJCPY	         	= objcopy$(TOOLENV)
SIZE            	= size$(TOOLENV)
NM              	= nm$(TOOLENV)
AR              	= ar$(TOOLENV)

LARGE_PROJECT   	= true
OPTION_INDIRECT_FILE    = @
OPTION_NM_INDIRECT_FILE = @

NM_GLOB_FLAGS		= -g


BOOTCONFIG_FLAGS	=

define link_symdef
--defsym (word 1, $(1))=$(word 2, $(1))
endef


LDFLAGS         	= -X -N $(LDFLAGS_ENDIAN) $(LDFLAGS_VSB) $(LINK_FLAGS_EXTRA) $(_USER_LDFLAGS)

LD_ENTRY_OPT		= -e
LD_PARTIAL_FLAGS	= -X -r $(LD_PARTIAL_FLAGS_ENDIAN) $(LD_PARTIAL_FLAGS_VSB) $(LINK_FLAGS_EXTRA)

# Wherever possible we use the compiler driver as a frontend to
# the linker. In particular this facilitates the GNU -frepo
# template repository system. Configurations using GNU Tools
# but non-GNU linkers (such as SIMHPPA)  should define
# GNU_USE_LD_TO_LINK = yes

ifeq ($(GNU_USE_LD_TO_LINK),)
BASE_LD_PARTIAL_FLAGS   = $(filter-out -r -nostdlib,$(LD_PARTIAL_FLAGS))
LD_PARTIAL              = $(CC) -r -nostdlib $(patsubst %,$(OPTION_PASS_TO_LD)%,$(BASE_LD_PARTIAL_FLAGS))
OPTION_PASS_TO_LD       = -Wl,
else
LD_PARTIAL            = $(LD) $(LD_PARTIAL_FLAGS)
OPTION_PASS_TO_LD     =
endif

# These are flags to pass to the linker the last time we do a
# relocatable link. They never get used by a bootable project
# and they only get used once by a downloadable project.

LD_SCRIPT_DOWNLOAD      = -T $(TGT_DIR)/h/tool/gnu/ldscripts/link.OUT
LD_COLLAPSE_SECTIONS    = $(LD_SCRIPT_DOWNLOAD)
LD_PARTIAL_LAST_FLAGS   = $(LD_COLLAPSE_SECTIONS)

LD_SCRIPT_RAM	= -T $(TGT_DIR)/h/tool/gnu/ldscripts/link.RAM
LD_SCRIPT_ROM	= -T $(TGT_DIR)/h/tool/gnu/ldscripts/link.ROM

# for cyclic link support

LD_START_GROUP  	= --start-group
LD_END_GROUP		= --end-group
LD_PARTIAL_START_GROUP	= $(OPTION_PASS_TO_LD)$(LD_START_GROUP)
LD_PARTIAL_END_GROUP	= $(OPTION_PASS_TO_LD)$(LD_END_GROUP)

LD_DATA_SEG_ALIGN_FLAG	= -defsym _VX_DATA_ALIGN

LD_LOW_FLAGS    	= -Ttext $(RAM_LOW_ADRS)
LD_HIGH_FLAGS   	= -Ttext $(RAM_HIGH_ADRS)
RES_LOW_FLAGS   	= -Ttext $(ROM_LINK_ADRS) -Tdata $(RAM_LOW_ADRS)
RES_HIGH_FLAGS  	= -Ttext $(ROM_LINK_ADRS) -Tdata $(RAM_HIGH_ADRS)

# Flags for VxWorks Project builds

LD_RAM_FLAGS     = $(LD_LOW_FLAGS)
LD_ROM_CPY_FLAGS = $(ROM_LDFLAGS) $(RES_LDFLAGS) $(RES_HIGH_FLAGS)
LD_ROM_CMP_FLAGS = $(ROM_LDFLAGS) $(RES_LDFLAGS) $(RES_HIGH_FLAGS)
LD_ROM_RES_FLAGS= $(ROM_LDFLAGS) $(RES_LDFLAGS) $(RES_LOW_FLAGS)


# For 960 IMI
LD_IMI_ADRS		= -Ttext $(IMI_TEXT_ADRS) -Tdata $(IMI_DATA_ADRS)

# linker flag for section splitting and removal of unused sections.
LD_REMOVE_UNUSED_SECTIONS = --gc-sections

# 64 bit mode linker options
LDFLAG_64BIT = -m elf_x86_64_vxworks
LD_PARTIAL_FLAG_64BIT = -m elf_x86_64_vxworks

# define data models supported for VIPs
ifdef TC_INFO
DATA_MODELS = ILP32 LP64
endif
