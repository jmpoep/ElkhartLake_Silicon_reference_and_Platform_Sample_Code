## @file
# Fsp build option configuration file.
#
# @copyright
#  INTEL CONFIDENTIAL
#  Copyright 2014 - 2017 Intel Corporation.
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

[BuildOptions]
# Define Build Options both for EDK and EDKII drivers.

!if gElkhartLakeFspPkgTokenSpaceGuid.PcdSymbolInReleaseEnable == TRUE
  DEFINE DSC_SYMBOL_IN_RELEASE_BUILD_OPTIONS = /Zi
  DEFINE DSC_SYMBOL_IN_RELEASE_LINK_BUILD_OPTIONS = /DEBUG
!else
  DEFINE DSC_SYMBOL_IN_RELEASE_BUILD_OPTIONS =
  DEFINE DSC_SYMBOL_IN_RELEASE_LINK_BUILD_OPTIONS =
!endif

#
# Catalog
#
*_*_*_PYTHON_PATH             = $(PYTHON_DIR)\python.exe
*_*_*_CATALOGENCODER_PATH     = $(CATALOG_ENCODER)

##################
# Rsa2048Sha256Sign tool definitions
#
# Notes: This tool defintion uses a test signing key for development purposes only.
#        The tool Rsa2048Sha256GenerateKeys can be used to generate a new private/public key
#        and the gEfiSecurityPkgTokenSpaceGuid.PcdRsa2048Sha256PublicKeyBuffer PCD value.
#        A custom tool/script can be implemented using the new private/public key with
#        the Rsa2048Sha256Sign tool and this tool defintiion can be updated to use a
#        custom tool/script.
#
#   Generate new private/public key and gEfiSecurityPkgTokenSpaceGuid.PcdRsa2048Sha256PublicKeyBuffer PCD value
#
#       Rsa2048Sha256GenerateKeys.py -o MyKey.pem --public-key-hash-c MyKey.pcd
#
#   Custom script example (MyRsa2048Sha256Sign.cmd):
#
#       Rsa2048Sha256Sign --private-key MyKey.pem %1 %2 %3 %4 %5 %6 %7 %8 %9
#
#   WARNING: Vendors that uses private keys are responsible for proper management and protection
#            of private keys.  Vendors may choose to use infrastructure such as signing servers
#            or signing portals to support the management and protection of private keys.
#
##################
#
# ROYAL_PARK_OVERRIDE: RoyalParkOverrideBegin - RPPO-CNL-0057
#
*_*_*_RSA2048SHA256SIGN_PATH = Rsa2048Sha256SignPlatform
*_*_*_RSA2048SHA256SIGN_GUID = A7717414-C616-4977-9420-844712A735BF
#
# ROYAL_PARK_OVERRIDE: RoyalParkOverrideEnd
#

[BuildOptions.Common.EDKII]
!if gElkhartLakeFspPkgTokenSpaceGuid.PcdSymbolInReleaseEnable == TRUE
MSFT:  RELEASE_*_*_CC_FLAGS    = $(DSC_SYMBOL_IN_RELEASE_BUILD_OPTIONS)
MSFT:  RELEASE_*_*_ASM_FLAGS   = $(DSC_SYMBOL_IN_RELEASE_BUILD_OPTIONS)
MSFT:  RELEASE_*_*_DLINK_FLAGS = $(DSC_SYMBOL_IN_RELEASE_LINK_BUILD_OPTIONS)
!endif










