## @file
# platform build option configuration file.
#
# @copyright
#  INTEL CONFIDENTIAL
#  Copyright 2017 - 2019 Intel Corporation.
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


  DEFINE DSC_S3_BUILD_OPTIONS =

  DEFINE DSC_CSM_BUILD_OPTIONS =

!if gSiPkgTokenSpaceGuid.PcdAcpiEnable == TRUE
  DEFINE DSC_ACPI_BUILD_OPTIONS = -DACPI_SUPPORT=1
!else
  DEFINE DSC_ACPI_BUILD_OPTIONS =
!endif


  DEFINE BIOS_GUARD_BUILD_OPTIONS =

  DEFINE OVERCLOCKING_BUILD_OPTION =

  DEFINE FSP_BINARY_BUILD_OPTIONS =

  DEFINE FSP_WRAPPER_BUILD_OPTIONS = -DFSP_WRAPPER_FLAG

  DEFINE SKIP_FSP_TEMPRAM_INIT_AND_EXIT_OPTIONS =

!if gSiPkgTokenSpaceGuid.PcdOptimizeCompilerEnable == FALSE
  DEFINE OPTIMIZE_DISABLE_OPTIONS = -Od -GL-
!else
  DEFINE OPTIMIZE_DISABLE_OPTIONS =
!endif

  DEFINE UP_SERVER_SUPPORT_BUILD_OPTIONS =


  DEFINE TPM_BUILD_OPTION =

  DEFINE TPM2_BUILD_OPTION =

  DEFINE DSC_TBT_BUILD_OPTIONS =

  DEFINE DSC_DCTT_BUILD_OPTIONS =

  DEFINE EMB_BUILD_OPTIONS =

  DEFINE DSC_MEMORY_DOWN_BUILD_OPTIONS = -DMEM_DOWN_FLAG=1

  DEFINE DSC_KBCEMUL_BUILD_OPTIONS =

  DEFINE BOOT_GUARD_BUILD_OPTIONS =

  DEFINE SECURE_BOOT_BUILD_OPTIONS =

  DEFINE USBTYPEC_BUILD_OPTION =

  DEFINE CAPSULE_BUILD_OPTIONS =

  DEFINE PERFORMANCE_BUILD_OPTION =

  DEFINE DEBUGUSEUSB_BUILD_OPTION =

#@todo: Needs further check this statement is necessary or not for MinPlatform
!if gPlatformModuleTokenSpaceGuid.PcdDeprecatedFunctionRemove == TRUE
  DEFINE DISABLE_NEW_DEPRECATED_INTERFACES_BUILD_OPTION = -DDISABLE_NEW_DEPRECATED_INTERFACES=1
!else
  DEFINE DISABLE_NEW_DEPRECATED_INTERFACES_BUILD_OPTION =
!endif

!if gBoardModuleTokenSpaceGuid.PcdEcEnable == TRUE
  DEFINE EC_SUPPORT_BUILD_OPTION = -DEC_SUPPORT=1
!else
  DEFINE EC_SUPPORT_BUILD_OPTION =
!endif

!if gBoardModuleTokenSpaceGuid.PcdEcLitePseEnable == TRUE
  DEFINE ECLITE_PSE_SUPPORT_BUILD_OPTION = -DECLITE_PSE_SUPPORT=1
!else
  DEFINE ECLITE_PSE_SUPPORT_BUILD_OPTION =
!endif


  DEFINE SINITBIN_BUILD_OPTION =

  DEFINE MINTREE_FLAG_BUILD_OPTION = -DMINTREE_FLAG=1

DEFINE DSC_PLTPKG_FEATURE_BUILD_OPTIONS = $(DSC_SIPKG_FEATURE_BUILD_OPTIONS)  $(OVERCLOCKING_BUILD_OPTION) $(PERFORMANCE_BUILD_OPTION) $(EMB_BUILD_OPTIONS) $(BIOS_GUARD_BUILD_OPTIONS) $(DSC_TBT_BUILD_OPTIONS)
DEFINE DSC_PLTPKG_FEATURE_BUILD_OPTIONS = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS) $(BOOT_GUARD_BUILD_OPTIONS) $(DSC_MEMORY_DOWN_BUILD_OPTIONS) $(DEBUGUSEUSB_BUILD_OPTION) $(DSC_S3_BUILD_OPTIONS)
DEFINE DSC_PLTPKG_FEATURE_BUILD_OPTIONS = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS) $(FSP_BINARY_BUILD_OPTIONS) $(FSP_WRAPPER_BUILD_OPTIONS) $(SKIP_FSP_TEMPRAM_INIT_AND_EXIT_OPTIONS)
DEFINE DSC_PLTPKG_FEATURE_BUILD_OPTIONS = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS) $(DSC_KBCEMUL_BUILD_OPTIONS) $(CAPSULE_BUILD_OPTIONS) $(SECURE_BOOT_BUILD_OPTIONS) $(DSC_CSM_BUILD_OPTIONS) $(DISABLE_NEW_DEPRECATED_INTERFACES_BUILD_OPTION)
DEFINE DSC_PLTPKG_FEATURE_BUILD_OPTIONS = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS) $(TPM2_BUILD_OPTION) $(TPM_BUILD_OPTION) $(DSC_DCTT_BUILD_OPTIONS)
DEFINE DSC_PLTPKG_FEATURE_BUILD_OPTIONS = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS) $(DSC_ACPI_BUILD_OPTIONS) $(UP_SERVER_SUPPORT_BUILD_OPTIONS) $(USBTYPEC_BUILD_OPTION) $(SINITBIN_BUILD_OPTION) $(MINTREE_FLAG_BUILD_OPTION)
DEFINE DSC_PLTPKG_FEATURE_BUILD_OPTIONS = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS) $(TEST_MENU_BUILD_OPTION)  $(PO_FLAGS)
DEFINE DSC_PLTPKG_FEATURE_BUILD_OPTIONS = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS) $(EC_SUPPORT_BUILD_OPTION)
DEFINE DSC_PLTPKG_FEATURE_BUILD_OPTIONS = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS) $(ECLITE_PSE_SUPPORT_BUILD_OPTION)

[BuildOptions.Common.EDKII]

#
# For IA32 Global Build Flag
#
       *_*_IA32_CC_FLAGS      = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS) -D PI_SPECIFICATION_VERSION=0x00010015 -DASF_PEI
       *_*_IA32_VFRPP_FLAGS   = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS)
       *_*_IA32_APP_FLAGS     = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS)
       *_*_IA32_ASLPP_FLAGS   = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS)
       *_*_IA32_ASLCC_FLAGS   = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS)
       *_*_IA32_NASM_FLAGS    = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS)

#
# For IA32 Specific Build Flag
#
GCC:   *_*_IA32_PP_FLAGS      = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS)
MSFT:  *_*_IA32_ASM_FLAGS     = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS)
MSFT:  *_*_IA32_CC_FLAGS      = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS) $(OPTIMIZE_DISABLE_OPTIONS) -D PI_SPECIFICATION_VERSION=0x00010015 -DASF_PEI
MSFT:  *_*_IA32_VFRPP_FLAGS   = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS) $(OPTIMIZE_DISABLE_OPTIONS)
MSFT:  *_*_IA32_APP_FLAGS     = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS) $(OPTIMIZE_DISABLE_OPTIONS)
MSFT:  *_*_IA32_ASLPP_FLAGS   = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS) $(OPTIMIZE_DISABLE_OPTIONS)
MSFT:  *_*_IA32_ASLCC_FLAGS   = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS) $(OPTIMIZE_DISABLE_OPTIONS)

#
# For X64 Global Build Flag
#
       *_*_X64_CC_FLAGS       = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS) -D PI_SPECIFICATION_VERSION=0x00010015
       *_*_X64_VFRPP_FLAGS    = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS)
       *_*_X64_APP_FLAGS      = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS)
       *_*_X64_ASLPP_FLAGS    = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS)
       *_*_X64_ASLCC_FLAGS    = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS)
       *_*_X64_NASM_FLAGS     = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS)


#
# For X64 Specific Build Flag
#
GCC:   *_*_X64_PP_FLAGS       = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS)
MSFT:  *_*_X64_ASM_FLAGS      = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS)
MSFT:  *_*_X64_CC_FLAGS       = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS) $(OPTIMIZE_DISABLE_OPTIONS) -D PI_SPECIFICATION_VERSION=0x00010015
MSFT:  *_*_X64_VFRPP_FLAGS    = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS) $(OPTIMIZE_DISABLE_OPTIONS)
MSFT:  *_*_X64_APP_FLAGS      = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS) $(OPTIMIZE_DISABLE_OPTIONS)
MSFT:  *_*_X64_ASLPP_FLAGS    = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS)
MSFT:  *_*_X64_ASLCC_FLAGS    = $(DSC_PLTPKG_FEATURE_BUILD_OPTIONS)

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
*_*_*_RSA2048SHA256SIGN_PATH  = Rsa2048Sha256SignPlatform
*_*_*_RSA2048SHA256SIGN_GUID  = A7717414-C616-4977-9420-844712A735BF

# Force PE/COFF sections to be aligned at 4KB boundaries to support page level protection
[BuildOptions.common.EDKII.DXE_SMM_DRIVER, BuildOptions.common.EDKII.SMM_CORE]
  MSFT:*_*_*_DLINK_FLAGS = /ALIGN:4096
  GCC:*_GCC*_*_DLINK_FLAGS = -z common-page-size=0x1000

# Force PE/COFF sections to be aligned at 4KB boundaries to support MemoryAttribute table
[BuildOptions.common.EDKII.DXE_RUNTIME_DRIVER]
  MSFT:*_*_*_DLINK_FLAGS = /ALIGN:4096
  GCC:*_GCC*_*_DLINK_FLAGS = -z common-page-size=0x1000

# Force PE/COFF sections to be aligned at 4KB boundaries to support NX protection
[BuildOptions.common.EDKII.DXE_DRIVER, BuildOptions.common.EDKII.DXE_CORE, BuildOptions.common.EDKII.UEFI_DRIVER, BuildOptions.common.EDKII.UEFI_APPLICATION]
  #MSFT:*_*_*_DLINK_FLAGS = /ALIGN:4096
  #GCC:*_GCC*_*_DLINK_FLAGS = -z common-page-size=0x1000

