#!/bin/bash

## @file
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

#
# UniTool v2.x
# Syntax:  UniTool.py [-b] [-u] [-l] [-x] [-h] [-d 'rootDirectory1'] [-d 'rootDirectory2'] [-d 'rootDirectory3']... [-q e|w] 'rootDirectory0' 'uqiFile'|'uqiFileDirectory' ['excludedDirectory1'] ['excludedDirectory2'] ['excludedDirectory3']...
#
# Function will sync up UQI definitions with uni files based on vfi/vfr/hfr/sd/sdi in the tree.
#
# Required Arguments:
#   'rootdirectory0'       path to root directory
#   'uqiFileDirectory'     path to UQI file(UqiList.uni)
#   'uqiFile'              UQI file
# 
# Options:
#   -h                    Show this help
#   -b                    Build option returns error if any new UQI needs assigning
#                         based on vfi/vfr/hfr/sd/sdi when no -u option is specified
#   -u                    Create new UQIs that does not already exist in uqiFile for
#                         any string requiring a UQI based on vfi/vfr/hfr/sd/sdi
#                         NOTE: 'uqiFile' cannot be readonly!
#   -l                    Language deletion option (keeps only English and uqi)
#                         moves all UQIs to 'uqiFile'
#                         NOTE: Uni files cannot be readonly!
#   -x                    Exclude 'rootDirectory'/'excludedDirectory1' &
#                         'rootDirectory'/'excludedDirectory2'... from UQI list build
#                         NOTE: Cannot be the same as rootDirectory
#   -d                    Add multiple root directories to process
#   -q                    Print warning(w) or return error(e) if different HII questions
#                         are referring same string token
#

if [ -e $WORKSPACE_PLATFORM/BpCommonPkg/Tools/UniTool/UniTool.py ]; then

#
#  - Non-restricted items: $WORKSPACE_PLATFORM/$PLATFORM_PACKAGE/Setup/UqiList.uni
#
#  Scan non-restricted items using "%WORKSPACE_PLATFORM%/CannonLakePlatSamplePkg" as root.
#
  python $WORKSPACE_COMMON/BpCommonPkg/Tools/UniTool/UniTool.py -b -u $WORKSPACE_PLATFORM/$PLATFORM_PACKAGE $WORKSPACE_PLATFORM/$PLATFORM_PACKAGE/Setup/UqiList.uni
  if [ $? -ne 0 ]; then
    echo "Generate PlatSamplePkg UQI definitions Fail!"
    exit $?
  fi


else
  echo "No UniTool.py!"
  exit $?
fi
