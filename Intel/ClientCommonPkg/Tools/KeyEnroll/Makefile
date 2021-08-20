#
# This file contains a 'Sample Driver' and is licensed as such
# under the terms of your license agreement with Intel or your
# vendor.  This file may be modified by the user, subject to
# the additional terms of the license agreement
#
#/** @file
#  makefile for building the KeyEnroll utility.
#  
#  Copyright (c) 2014, Intel Corporation. All rights reserved.<BR>
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

APPNAME = KeyEnroll

LIBS = $(LIB_PATH)\Common.lib $(OPENSSL_HOME)\out32\libeay32.lib user32.lib advapi32.lib gdi32.lib

OBJECTS =  KeyEnroll.obj Variable.obj AuthVarCertDB.obj AuthVariable.obj Pkcs7Verify.obj Unaligned.obj

!INCLUDE $(EDK_TOOLS_PATH)\Source\C\Makefiles\ms.app

