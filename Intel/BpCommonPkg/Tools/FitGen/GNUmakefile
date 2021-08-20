#
# This file contains a 'Sample Driver' and is licensed as such
# under the terms of your license agreement with Intel or your
# vendor.  This file may be modified by the user, subject to
# the additional terms of the license agreement
#
#/** @file
#  GNUmakefile for building the FitGen utility.
#
#  Copyright (c) 2017 - 2018, Intel Corporation. All rights reserved.<BR>
#  This software and associated documentation (if any) is furnished
#  under a license and may only be used or copied in accordance
#  with the terms of the license. Except as permitted by such
#  license, no part of this software or documentation may be
#  reproduced, stored in a retrieval system, or transmitted in any
#  form or by any means without the express written consent of
#  Intel Corporation.
#
#**/

ifndef ARCH
  #
  # If ARCH is not defined, then we use 'uname -m' to attempt
  # try to figure out the appropriate ARCH.
  #
  uname_m = $(shell uname -m)
  $(info Attempting to detect ARCH from 'uname -m': $(uname_m))
  ifneq (,$(strip $(filter $(uname_m), x86_64 amd64)))
    ARCH=X64
  endif
  ifeq ($(patsubst i%86,IA32,$(uname_m)),IA32)
    ARCH=IA32
  endif
  ifneq (,$(findstring aarch64,$(uname_m)))
    ARCH=AARCH64
  endif
  ifneq (,$(findstring arm,$(uname_m)))
    ARCH=ARM
  endif
  ifndef ARCH
    $(info Could not detect ARCH from uname results)
    $(error ARCH is not defined!)
  endif
  $(info Detected ARCH of $(ARCH) using uname.)
endif

export ARCH
export HOST_ARCH=$(ARCH)

MAKEROOT ?= $(EDK_TOOLS_PATH)/Source/C

APPNAME = FitGen

OBJECTS = FitGen.o

include $(MAKEROOT)/Makefiles/app.makefile

LIBS = -lCommon


