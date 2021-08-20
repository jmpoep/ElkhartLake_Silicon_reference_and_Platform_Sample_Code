#!/bin/bash

## @file
# Post build FitGen script.
#
# @copyright
#  INTEL CONFIDENTIAL
#  Copyright 2016 - 2019 Intel Corporation.
#
#  The source code contained or described herein and all documents related to the
#  source code ("Material") are owned by Intel Corporation or its suppliers or
#  licensors. Title to the Material remains with Intel Corporation or its suppliers
#  and licensors. The Material may contain trade secrets and proprietary and
#  confidential information of Intel Corporation and its suppliers and licensors,
#  and is protected by worldwide copyright and trade secret laws and treaty
#  provisions. No part of the Material may be used, copied, reproduced, modified,
#  published, uploaded, posted, transmitted, distributed, or disclosed in any way
#  without Intel's prior express written permission.
#
#  No license under any patent, copyright, trade secret or other intellectual
#  property right is granted to or conferred upon you by disclosure or delivery
#  of the Materials, either expressly, by implication, inducement, estoppel or
#  otherwise. Any license under such intellectual property rights must be
#  express and approved by Intel in writing.
#
#  Unless otherwise agreed by Intel in writing, you may not remove or alter
#  this notice or any other notice embedded in Materials by Intel or
#  Intel's suppliers or licensors in any way.
#
#  This file contains a 'Sample Driver' and is licensed as such under the terms
#  of your license agreement with Intel or your vendor. This file may be modified
#  by the user, subject to the additional terms of the license agreement.
#
# @par Specification
##

BIOS_INFO_GUID="4A4CA1C6-871C-45bb-8801-6910A7AA5807"
STARTUP_AC_MODULE_GUID="26fdaa3d-b7ed-4714-8509-eecf1593800d"

STARTUP_ACM_FOUND=0

grep $STARTUP_AC_MODULE_GUID $BUILD_DIR/FV/FvFwBinaries.inf > /dev/null
if [ $? -eq 0 ]; then
  STARTUP_ACM_FOUND=1
fi

if [ $STARTUP_ACM_FOUND -eq 1 ]; then
  STARTUP_AC_PARA="-S $STARTUP_AC_MODULE_GUID"
fi

cp -f $WORKSPACE/$BUILD_DIR/FV/CLIENTBIOS.fd $WORKSPACE/$BUILD_DIR/FV/CLIENTBIOS_ORG.fd

if [ "$COMPILER" = "" ]; then
  FitGen -D $WORKSPACE/$BUILD_DIR/FV/CLIENTBIOS.fd $WORKSPACE/$BUILD_DIR/FV/CLIENTBIOS_FIT.fd -F 0x40 -NA -I $BIOS_INFO_GUID $STARTUP_AC_PARA -O 0x0C RESERVE 0x600 -O 0x0B RESERVE 0x400
else
  FitGen -D $WORKSPACE/$BUILD_DIR/FV/CLIENTBIOS.fd $WORKSPACE/$BUILD_DIR/FV/CLIENTBIOS_FIT.fd -F 0x40 -NA -I $BIOS_INFO_GUID
fi

if [ $? -ne 0 ]; then
  exit $?
fi

cp -f $WORKSPACE/$BUILD_DIR/FV/CLIENTBIOS_FIT.fd $WORKSPACE/$BUILD_DIR/FV/CLIENTBIOS.fd
