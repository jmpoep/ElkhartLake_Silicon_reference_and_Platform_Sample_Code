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

# !!! This postbuild.sh must run under workspace root using $WORKSPACE/$PLATFORM_BOARD_PACKAGE/PostBuild.sh !!!"
#cd $WORKSPACE
echo "PostBuild."


#
# Run FCE tool to write default setup variable to FD image
#
cp $BUILD_DIR/FV/CLIENTBIOS.fd $BUILD_DIR/FV/CLIENTBIOS_FcePre.fd
cat $BUILD_DIR/FV/FVSETUPDATA.Fv $BUILD_DIR/FV/CLIENTBIOS.fd > $BUILD_DIR/FV/CLIENTSETUP_Pre.fd
# UQI 0006 005C 0078 0030 0034 0039 0046 is for PlatId question prompt (STR_PLATID_PROMPT) UQI string value.
# First 0006 is the length of string; Next six byte values are mapped to STR_PLATID_PROMPT string value (\x049F) defined in $PLATFORM_PACKAGE/Setup/UqiList.uni.
FCE read -i $BUILD_DIR/FV/CLIENTSETUP_Pre.fd 0006 005C 0078 0030 0034 0039 0046 > $BUILD_DIR/FV/CLIENTBIOS.fd.config
if [ $? -ne 0 ]; then
  echo "FCE utility - CLIENTBIOS.fd.config generate fail."
  exit $?
fi

FCE update -i $BUILD_DIR/FV/CLIENTSETUP_Pre.fd -s $BUILD_DIR/FV/CLIENTBIOS.fd.config -o $BUILD_DIR/FV/CLIENTSETUP.fd -g FC8FE6B5-CD9B-411E-BD8F-31824D0CDE3D -a
if [ $? -ne 0 ]; then
  echo "FCE utility - FCE update .fd fail."
  exit $?
fi

Split -f $BUILD_DIR/FV/CLIENTSETUP.fd -s 0x100000
if [ $? -ne 0 ]; then
  echo "Split utility - fail."
  exit $?
fi
rm $BUILD_DIR/FV/CLIENTSETUP.fd1
mv -f $BUILD_DIR/FV/CLIENTSETUP.fd2 $BUILD_DIR/FV/CLIENTBIOS_FcePOST.fd


cp -f $BUILD_DIR/FV/CLIENTBIOS_FcePOST.fd $BUILD_DIR/FV/CLIENTBIOS.fd
if [ "$FSP_WRAPPER_BUILD" = "TRUE" ]; then
  if [ ! -d "$WORKSPACE/RomImages" ]; then
    mkdir -p $WORKSPACE/RomImages
  fi
fi

echo --- Analyze ASL runtime behavior using acpiexec ---
cd $BUILD_X64
if [ ! -d AslAnalyze ]; then
  mkdir -p AslAnalyze
fi
if [ ! -d AslAnalyze/Sds ]; then
  mkdir -p AslAnalyze/Sds
fi

cd AslAnalyze
find ../ -name '*.aml' -exec cp -f '{}' . \;
cd ../Sds
mv -f ../*Sds*.aml .
cd ..
if [ "$COMPILER" != "XCODE" ]; then
echo q | acpiexec -di -l *.aml Sds/*.aml > $WORKSPACE/$BUILD_DIR/AslAnalyzeSds.log

echo --- ASL analysis completed ---
fi
cd $WORKSPACE
#
# ---run TXTSX tool to generate FIT table---
#
    if [ -f $WORKSPACE_PLATFORM/$PLATFORM_PACKAGE/Tools/ToolScripts/FitGen/postbuildFitGen.sh ]; then
      . $WORKSPACE_PLATFORM/$PLATFORM_PACKAGE/Tools/ToolScripts/FitGen/postbuildFitGen.sh
      if [ $? -ne 0 ]; then
        echo "postbuildFitGen.sh - fail."
        exit $?
      fi
    fi

    BPMGEN=FALSE
    if [ "$COMPILER" != "XCODE" ]; then
      if [ "$BPMGEN" = "TRUE" ]; then
        if [ -f $WORKSPACE_PLATFORM/$PLATFORM_PACKAGE/Tools/ToolScripts/BpmGen/postbuildBpmGen.sh ]; then
          . $WORKSPACE_PLATFORM/$PLATFORM_PACKAGE/Tools/ToolScripts/BpmGen/postbuildBpmGen.sh CLIENTBIOS_FIT CLIENTBIOS
          if [ $? -ne 0 ]; then
            echo "postbuildBpmGen.sh - fail."
            exit $?
          fi
        fi
      fi
    fi #if [ "$COMPILER" != "XCODE" ]

#if [ -f $WORKSPACE_PLATFORM/$PLATFORM_PACKAGE/InternalOnly/ToolScripts/KeyEnroll/MsEnrollRestricted.sh ]; then
#  . $WORKSPACE_PLATFORM/$PLATFORM_PACKAGE/InternalOnly/ToolScripts/KeyEnroll/MsEnrollRestricted.sh CLIENTBIOS $WORKSPACE/$BUILD_DIR
#  if [ $? -ne 0 ]; then
#    echo "MsEnrollRestricted.sh - fail."
#    exit $?
#  fi
#fi

#
# ---Create ROM and Simics images---
#
if [ -d $BUILD_X64/$PLATFORM_SI_PACKAGE/Pch ]; then
  . $WORKSPACE_PLATFORM/$PLATFORM_PACKAGE/Tools/RomImage/SetupRomDirs.sh
  #@todo: BuildBGUP.bat
fi

