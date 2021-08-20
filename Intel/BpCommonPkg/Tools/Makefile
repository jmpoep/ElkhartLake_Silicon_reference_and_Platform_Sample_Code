#
# This file contains a 'Sample Driver' and is licensed as such
# under the terms of your license agreement with Intel or your
# vendor.  This file may be modified by the user, subject to
# the additional terms of the license agreement
#
#/** @file
#  makefile for building C utilities.
#  
#  Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
#  This software and associated documentation (if any) is furnished
#  under a license and may only be used or copied in accordance
#  with the terms of the license. Except as permitted by such
#  license, no part of this software or documentation may be
#  reproduced, stored in a retrieval system, or transmitted in any
#  form or by any means without the express written consent of
#  Intel Corporation.
#  
#**/
HOST_ARCH = IA32

!INCLUDE $(EDK_TOOLS_PATH)\Source\C\Makefiles\ms.common

APPLICATIONS = \
  FCE\Source\BfmLib \
  FCE\Source\FCE \
  FitGen \
  FMMT\Source\FMMT \
  GenBiosId

all: $(APPLICATIONS)
	@echo.
	@echo ######################
	@echo # Build executables
	@echo ######################
	@if not exist $(BIN_PATH) mkdir $(BIN_PATH)
	@$(EDK_TOOLS_PATH)\Source\C\Makefiles\NmakeSubdirs.bat all $**

.PHONY: clean
clean: $(APPLICATIONS)
  @$(EDK_TOOLS_PATH)\Source\C\Makefiles\NmakeSubdirs.bat clean $**

.PHONY: cleanall
cleanall: $(APPLICATIONS)
  @$(EDK_TOOLS_PATH)\Source\C\Makefiles\NmakeSubdirs.bat cleanall $**

!INCLUDE $(EDK_TOOLS_PATH)\Source\C\Makefiles\ms.rule

