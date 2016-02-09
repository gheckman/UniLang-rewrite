# Makefile - makefile for regenerating GNU linker scripts from common template
#
# modification history
# --------------------
# 01a,10mar10,gvm  adapted from h/tool/gnu/ldscripts/Makefile
#
# DESCRIPTION
# This file contains the makefile rules to regenerate cross-target linker
# scripts using the template system in tool/common/ldscripts.
#
# icc uses GNU binutils.
#*/

TGT_DIR=$(WIND_BASE)/target
GEN_DIR=$(TGT_DIR)/h/tool/common/ldscripts
REGEN_SH=$(GEN_DIR)/regen.sh
TOOL=icc

regen all:
	sh $(REGEN_SH) $(TOOL)

update:
	sh $(REGEN_SH) -update $(TOOL)
