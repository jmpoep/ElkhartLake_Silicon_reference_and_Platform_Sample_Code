#!/bin/bash

## @file
# Post build BpmGen script.
#
# @copyright
#  INTEL CONFIDENTIAL
#  Copyright 2017 Intel Corporation.
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

SCRIPT_ERROR=0
BIOS_INFO_GUID=4A4CA1C6-871C-45bb-8801-6910A7AA5807
#
# NEM_DATA_SIZE should match PcdTemporaryRamSize value
#
NEM_DATA_SIZE=0x40
FLAGS=0
BP_REVOCATION=0
ACM_REVOCATION=0
KM_REVOCATION=0
KM_ID=0x01
MCH_BAR=0xFED10000
VTD_BAR=0xFED90000
PMRL_BASE=0x100000
PMRL_SIZE=0xF00000
PMRH_BASE=0x100000000
PMRH_SIZE=0xF00000000
PBET_VALUE=0x0F
IBB_ENTRY_POINT=0xFFFFFFF0


echo "#### BpmGen2:  Generating KeyManifest.bin ####"
cd $WORKSPACE_PLATFORM/$PLATFORM_PACKAGE/Tools/ToolScripts/BpmGen
#wine $WORKSPACE_PLATFORM/$PLATFORM_PACKAGE/Override/ClientCommonPkg/Tools/BpmGen2/BpmGen2.exe KMGEN -KEY pubkey.pem BPM -KM $WORKSPACE/$BUILD_DIR/FV/KeyManifest.bin -SIGNKEY keyprivkey.pem -SIGNPUBKEY keypubkey.pem -KMID $KM_ID -SVN $KM_REVOCATION -d:2 >bpmgen2_km.txt
wine $WORKSPACE_PLATFORM/ClientCommonPkg/Tools/BpmGen2/BpmGen2.exe KMGEN -KEY pubkey.pem BPM -KM $WORKSPACE/$BUILD_DIR/FV/KeyManifest.bin -SIGNKEY 3k_key_private.pem  -SIGHASHALG SHA384 -KMKHASH SHA384 -KMID $KM_ID -SVN $KM_REVOCATION -d:2 >bpmgen2_km.txt
if [ $? -ne 0 ]; then
  echo "#### Error generating KM file #####"
  exit
fi

echo "#### BpmGen2:  Generating Manifest.bin ####"
#wine $WORKSPACE_PLATFORM/$PLATFORM_PACKAGE/Override/ClientCommonPkg/Tools/BpmGen2/BpmGen2.exe GEN $WORKSPACE/$BUILD_DIR/FV/$1.fd bpmgen2.params -BPM $WORKSPACE/$BUILD_DIR/FV/Manifest.bin -U $WORKSPACE/$BUILD_DIR/FV/$1_MBIOS.fd -KM $WORKSPACE/$BUILD_DIR/FV/KeyManifest.bin -d:2 >bpmgen2_bpm.txt
wine $WORKSPACE_PLATFORM/ClientCommonPkg/Tools/BpmGen2/BpmGen2.exe GEN $WORKSPACE/$BUILD_DIR/FV/$1.fd bpmgen2.params -BPM $WORKSPACE/$BUILD_DIR/FV/Manifest.bin -U $WORKSPACE/$BUILD_DIR/FV/$1_MBIOS.fd -KM $WORKSPACE/$BUILD_DIR/FV/KeyManifest.bin -d:2 >bpmgen2_bpm.txt
if [ $? -ne 0 ]; then
  echo "#### Error generating BPM file #####"
  exit
fi

cp -f $WORKSPACE/$BUILD_DIR/FV/$1_MBIOS.fd $WORKSPACE/$BUILD_DIR/FV/$2.fd

cd $WORKSPACE
