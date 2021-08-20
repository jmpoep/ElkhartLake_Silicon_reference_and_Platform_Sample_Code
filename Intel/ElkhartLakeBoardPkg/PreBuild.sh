#!/bin/bash

## @file
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

function EndPreBuild {
  cd $WORKSPACE_PLATFORM/$PLATFORM_BOARD_PACKAGE
}

cd $WORKSPACE


#
# Set build capsule flag with default of OFF
#
CAPSULE_BUILD=0
if [ "$2" = "TRUE" ]; then
  CAPSULE_BUILD=1
fi

echo
echo "Prebuild:  Set build environment."
echo

if [ ! -d $BUILD_DIR ]; then
  mkdir -p $BUILD_DIR
fi

grep -v 'ACTIVE_PLATFORM\|TARGET\|TARGET_ARCH\|TOOL_CHAIN_TAG\|BUILD_RULE_CONF' Conf/target.txt > $BUILD_DIR/target.txt
echo "ACTIVE_PLATFORM   = $PLATFORM_BOARD_PACKAGE/BoardPkg.dsc" >> $BUILD_DIR/target.txt
echo "TARGET            = $TARGET"                              >> $BUILD_DIR/target.txt
echo "TARGET_ARCH       = $TARGET_ARCH"                         >> $BUILD_DIR/target.txt
echo "TOOL_CHAIN_TAG    = $TOOL_CHAIN_TAG"                      >> $BUILD_DIR/target.txt
echo "BUILD_RULE_CONF   = $WORKSPACE/Conf/build_rule.txt"       >> $BUILD_DIR/target.txt
mv -f $BUILD_DIR/target.txt $WORKSPACE/Conf

if [ $CAPSULE_BUILD -eq 0 ]; then
  echo
  echo "Prebuild:  Create BiosId"
  echo
  if [ ! -d $BUILD_X64 ]; then
    mkdir -p $BUILD_X64
  fi
  #
  # @todo: Code Coverage not supported at this time
  #

  #
  # @Todo: Need to check if the copies from ElkhartLakeSvRestrictedPkg are required or not

  #
  # Create BiosId.env based on the build type
  #
  BIOSID_FILENAME=BiosId
  if [ "$EMBEDDED_BUILD" = "TRUE" ]; then
    BIOSID_FILENAME=BiosIdEmb
  fi
  cp -f $WORKSPACE_PLATFORM/$PLATFORM_PACKAGE/Tools/GenBiosId/$BIOSID_FILENAME.env $BIOS_ID_FILE
  if [ "$EMBEDDED_BUILD" = "TRUE" ]; then
    echo "BOARD_ID      = EHLI" >> $BIOS_ID_FILE
  else
    #
    # S = SPT, E = ERB (LPT)
    #
    PCH_TYPE=S
    BOARD_ID_STRING="BOARD_ID      = EHL$PCH_TYPE"
    BOARD_ID_STRING+="E2$BUILD"
    echo "$BOARD_ID_STRING" >> $BIOS_ID_FILE
  fi
  BOARD_EXT_STRING="BOARD_EXT    = $TARGET_SHORT"
  BOARD_EXT_STRING+="00"
  echo "$BOARD_EXT_STRING" >> $BIOS_ID_FILE
  BIOS_ID_OUTPUT_DIR=$BUILD_IA32
  if [ ! -d $BIOS_ID_OUTPUT_DIR ]; then
    mkdir -p $BIOS_ID_OUTPUT_DIR
  fi
  GenBiosId -i $BIOS_ID_FILE -o $BIOS_ID_OUTPUT_DIR/BiosId.bin
  ret=$?
  if [ $ret -ne 0 ]; then
    EndPreBuild
    exit $ret
  fi

  if [ ! -d $BUILD_DIR/FV ]; then
    mkdir -p $BUILD_DIR/FV
  fi
  echo 2> $BUILD_DIR/FV/CLIENTBIOS.fd
fi
echo
echo "Prebuild is complete."
echo "  ACTIVE_PLATFORM      = $PLATFORM_BOARD_PACKAGE/BoardPkg.dsc"
echo "  EFI_SOURCE           = $EFI_SOURCE"
echo "  TARGET               = $TARGET"
echo "  TARGET_ARCH          = IA32 X64"
echo "  TOOL_CHAIN_TAG       = $TOOL_CHAIN_TAG"
echo "  WORKSPACE            = $WORKSPACE"
echo "  EXT_BUILD_FLAGS      = $EXT_BUILD_FLAGS"
echo "  BUILD_OPTION_PCD     = $BUILD_OPTION_PCD"
echo
EndPreBuild
