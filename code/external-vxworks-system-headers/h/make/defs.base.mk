#
# defs.base - generig utility make definitions.
#
# Copyright 2009, Wind River Systems, Inc.
#
# This file contains generig make utility definitions.
# The variables defined in this file are not specific to any product.
#
# modification history
# --------------------
# 01a,30jun09,pee  created

# whitespace characters
blank:=
space:=$(blank) $(blank)
tab:=$(blank)	$(blank)

# this defines a single newline character
define newline


endef

# print function
# this routine allows to print a multi line variable in a make command
# first parameter is the text
# second optional parameter is the output file. The function will output to stdout if $2 not provided
# This function uses the echo command.
#
# exmaple of usage:
# target :
#	$(call print,$(CONTENTS),$@)
#
define print

$(foreach line,$(subst $(newline),[:newline:]$(space),$(subst $(space),[:space:],$(subst $(tab),[:tab:],$1))),
	@echo '$(subst [:newline:],,$(subst [:space:],$(space),$(subst [:tab:],$(tab),$(line))))' $(if $2,>> $2,)
)
endef


