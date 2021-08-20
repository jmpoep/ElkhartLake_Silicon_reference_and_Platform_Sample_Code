#!/bin/bash

## @file
#
# @copyright
#  INTEL CONFIDENTIAL
#  Copyright 2017 - 2018 Intel Corporation.
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
# Build GenBiosId tools.
#
if [ ! -d $WORKSPACE_CORE/BaseTools/Source/C/GenBiosId ]; then
  cp -rf $WORKSPACE_COMMON/BpCommonPkg/Tools/GenBiosId $WORKSPACE_CORE/BaseTools/Source/C
#
# Create BinWrappers script for GenBiosId.
#
  cp -f $WORKSPACE_CORE/BaseTools/BinWrappers/PosixLike/Split $WORKSPACE_CORE/BaseTools/BinWrappers/PosixLike/GenBiosId
fi
cd $WORKSPACE_CORE/BaseTools/Source/C/GenBiosId
make
if [ $? -ne 0 ]; then
  echo "Build GenBiosId tools fail."
fi

#
# Build FCE tools.
#
if [ ! -d $WORKSPACE_CORE/BaseTools/Source/C/FCE ]; then
  cp -rf $WORKSPACE_COMMON/BpCommonPkg/Tools/FCE/Source/FCE $WORKSPACE_CORE/BaseTools/Source/C
#
# Create BinWrappers script for FCE.
#
  cp -f $WORKSPACE_CORE/BaseTools/BinWrappers/PosixLike/Split $WORKSPACE_CORE/BaseTools/BinWrappers/PosixLike/FCE
fi
cd $WORKSPACE_CORE/BaseTools/Source/C/FCE
make
if [ $? -ne 0 ]; then
  echo "Build FCE tools fail."
fi

#
# Build BfmLib tools.
#
if [ ! -d $WORKSPACE_CORE/BaseTools/Source/C/BfmLib ]; then
  cp -rf $WORKSPACE_COMMON/BpCommonPkg/Tools/FCE/Source/BfmLib $WORKSPACE_CORE/BaseTools/Source/C
fi
cd $WORKSPACE_CORE/BaseTools/Source/C/BfmLib
make
if [ $? -ne 0 ]; then
  echo "Build BfmLib tools fail."
fi

#
# Build FitGen tools.
#
if [ ! -d $WORKSPACE_CORE/BaseTools/Source/C/FitGen ]; then
  cp -rf $WORKSPACE_COMMON/BpCommonPkg/Tools/FitGen $WORKSPACE_CORE/BaseTools/Source/C
#
# Create BinWrappers script for FitGen.
#
  cp -f $WORKSPACE_CORE/BaseTools/BinWrappers/PosixLike/Split $WORKSPACE_CORE/BaseTools/BinWrappers/PosixLike/FitGen
fi
cd $WORKSPACE_CORE/BaseTools/Source/C/FitGen
make
if [ $? -ne 0 ]; then
  echo "Build FitGen tools fail."
fi

#
# Build BpmGen tools.
#
if [ ! -d $WORKSPACE_CORE/BaseTools/Source/C/BpmGen ]; then
  cp -rf $WORKSPACE_COMMON/BpCommonPkg/Tools/BpmGen $WORKSPACE_CORE/BaseTools/Source/C
#
# Create BinWrappers script for BpmGen.
#
  cp -f $WORKSPACE_CORE/BaseTools/BinWrappers/PosixLike/Split $WORKSPACE_CORE/BaseTools/BinWrappers/PosixLike/BpmGen
fi
cd $WORKSPACE_CORE/BaseTools/Source/C/BpmGen
make
if [ $? -ne 0 ]; then
  echo "Build BpmGen tools fail."
fi

#
# Build FMMT tools.
#
if [ ! -d $WORKSPACE_CORE/BaseTools/Source/C/FMMT ]; then
  cp -rf $WORKSPACE_COMMON/BpCommonPkg/Tools/FMMT/Source/FMMT $WORKSPACE_CORE/BaseTools/Source/C
#
# Create BinWrappers script for FMMT.
#
  cp -f $WORKSPACE_CORE/BaseTools/BinWrappers/PosixLike/Split $WORKSPACE_CORE/BaseTools/BinWrappers/PosixLike/FMMT
fi
cd $WORKSPACE_CORE/BaseTools/Source/C/FMMT
make
if [ $? -ne 0 ]; then
  echo "Build FMMT tools fail."
fi

#
# Build KeyEnroll tools.
#
if [ ! -d $WORKSPACE_CORE/BaseTools/Source/C/KeyEnroll ]; then
  cp -rf $WORKSPACE_COMMON/BpCommonPkg/Tools/KeyEnroll $WORKSPACE_CORE/BaseTools/Source/C
#
# Create BinWrappers script for KeyEnroll.
#
  cp -f $WORKSPACE_CORE/BaseTools/BinWrappers/PosixLike/Split $WORKSPACE_CORE/BaseTools/BinWrappers/PosixLike/KeyEnroll
fi
cd $WORKSPACE_CORE/BaseTools/Source/C/KeyEnroll
make
if [ $? -ne 0 ]; then
  echo "Build KeyEnroll tools fail."
fi

#
# Add additional tools in PATH.
#
export PATH=$WORKSPACE_PLATFORM/ClientCommonPkg/Tools/FCE:$PATH
export PATH=$WORKSPACE_PLATFORM/ClientCommonPkg/Tools/FMMT:$PATH
export PATH=$WORKSPACE_PLATFORM/$PLATFORM_PACKAGE/Tools/ToolScripts/SignFv:$PATH
export PATH=$WORKSPACE_PLATFORM/$PLATFORM_PACKAGE/Tools/ToolScripts/FitGen:$PATH
export PATH=$WORKSPACE_PLATFORM/$PLATFORM_PACKAGE/Tools/ToolScripts/BpmGen:$PATH
