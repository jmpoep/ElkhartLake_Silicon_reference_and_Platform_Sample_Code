#
# This file contains 'Framework Code' and is licensed as such
# under the terms of your license agreement with Intel or your
# vendor.  This file may not be modified, except as allowed by
# additional terms of your license agreement.
#
#/** @file
#  makefile for building the BpmGen utility.
#
#  Copyright (c) 2012 - 2015, Intel Corporation. All rights reserved.<BR>
#  This software and associated documentation (if any) is furnished
#  under a license and may only be used or copied in accordance
#  with the terms of the license. Except as permitted by such
#  license, no part of this software or documentation may be
#  reproduced, stored in a retrieval system, or transmitted in any
#  form or by any means without the express written consent of
#  Intel Corporation.
#
#**/

!IFNDEF OPENSSL_HOME
!ERROR Please make sure openssl is installed and OPENSSL_HOME is defined to your own openssl dir!
!ENDIF

INC = $(INC) -I $(OPENSSL_HOME)\include -I $(OPENSSL_HOME)\inc32

!INCLUDE $(EDK_TOOLS_PATH)\Source\C\Makefiles\ms.common

APPNAME = BpmGen

LIBS = $(LIB_PATH)\Common.lib $(OPENSSL_HOME)\out32\libeay32.lib user32.lib advapi32.lib gdi32.lib

OBJECTS = BpmGen.obj

!INCLUDE $(EDK_TOOLS_PATH)\Source\C\Makefiles\ms.app

