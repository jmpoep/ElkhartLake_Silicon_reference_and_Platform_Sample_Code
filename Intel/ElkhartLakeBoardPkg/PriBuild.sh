#!/bin/bash

## @file
#
# @copyright
#  INTEL CONFIDENTIAL
#  Copyright 2016 - 2018 Intel Corporation.
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

#
# Performs the primary build
#

function BuildFail {
  cd $WORKSPACE_PLATFORM/$PLATFORM_BOARD_PACKAGE
  echo
  echo "The EDKII BIOS Build has failed!"
  echo
  exit $1
}

cd $WORKSPACE

cat "$WORKSPACE_PLATFORM/$PLATFORM_BOARD_PACKAGE/BoardPkgConfig.dsc" | grep "gPlatformModuleTokenSpaceGuid.PcdUnitoolEnable|TRUE" > /dev/null
if [ $? -eq 0 ]; then
  . $WORKSPACE_PLATFORM/$PLATFORM_PACKAGE/Tools/UniTool/UniTool.sh
else
  echo "Skip UniTool."
fi

#
# Run the actual build
#
if [ "$SILENT_MODE" = "TRUE" ]; then
  echo > Build.log
  echo "************************************************************************" >> Build.log
  echo "***********            build.sh is launched here             ***********" >> Build.log
  echo "************************************************************************" >> Build.log
  build -n $NUMBER_OF_PROCESSORS $EXT_BUILD_FLAGS $BUILD_OPTION_PCD >> Build.log 2>&1
  ret=$?
  if [ $ret -ne 0 ]; then
    BuildFail $ret
  fi
  echo >> Build.log
  echo "Running PostBuild.sh to complete the build process." >> Build.log
  echo >> Build.log
  . $WORKSPACE_PLATFORM/$PLATFORM_BOARD_PACKAGE/PostBuild.sh >> Build.log 2>&1
  ret=$?
  if [ $ret -ne 0 ]; then
    BuildFail $ret
  fi
  if [ -f EDK2.log ]; then
    rm EDK2.log
  fi
  if [ -f Prep.log ] && [ -f Build.log ]; then
    cat Prep.log  >  EDK2.log
    cat Build.log >> EDK2.log
  fi
else
  build -n $NUMBER_OF_PROCESSORS $EXT_BUILD_FLAGS $BUILD_OPTION_PCD
  ret=$?
  if [ $ret -ne 0 ]; then
    BuildFail $ret
  fi
  echo
  echo "Running PostBuild.sh to complete the build process."
  echo
  . $WORKSPACE_PLATFORM/$PLATFORM_BOARD_PACKAGE/PostBuild.sh
  ret=$?
  if [ $ret -ne 0 ]; then
    BuildFail $ret
  fi
fi

echo
echo "TARGET:               $TARGET"
echo "TOOL_CHAIN_TAG:       $TOOL_CHAIN_TAG"
echo "BIOS location:        $BUILD_DIR/FV"
echo "SPI Images location:  $WORKSPACE/RomImages"
echo
echo "The EDKII BIOS build has successfully completed!"
echo

FSP_WRAPPER_ENABLE=FALSE
echo $EXT_BUILD_FLAGS | grep "FSP_WRAPPER_ENABLE=TRUE"
if [ $? -eq 0 ]; then
  FSP_WRAPPER_ENABLE=TRUE
else
    cat "$WORKSPACE_PLATFORM/$PLATFORM_BOARD_PACKAGE/BoardPkgConfig.dsc" | grep "FSP_WRAPPER_ENABLE = TRUE" > /dev/null
    if [ $? -eq 0 ]; then
      FSP_WRAPPER_ENABLE=TRUE
    fi
fi

if [ "$FSP_WRAPPER_ENABLE" = "TRUE" ]; then
  #@todo: Implement FSP Wrapper Support
  echo "TODO: FSP Wrapper support not implemented!"
  exit 1
else
  cd $WORKSPACE_PLATFORM/$PLATFORM_BOARD_PACKAGE
fi
