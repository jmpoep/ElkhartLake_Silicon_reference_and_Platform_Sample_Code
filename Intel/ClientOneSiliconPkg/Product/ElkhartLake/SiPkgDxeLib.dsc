# @file
#  Component description file for the ElkhartLake SiPkg DXE libraries.
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
#  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
#  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
#  the terms of your license agreement with Intel or your vendor. This file may
#  be modified by the user, subject to additional terms of the license agreement.
#
#@par Specification Reference:
#
##

#
# Silicon Init Dxe Library
#
!include $(PLATFORM_SI_PACKAGE)/UniversalDxeLib.dsc

#
# FRUs
#
!include $(PLATFORM_SI_PACKAGE)/Fru/EhlCpu/DxeLib.dsc
!if gSiPkgTokenSpaceGuid.PcdEhlPchEnable == TRUE
!include $(PLATFORM_SI_PACKAGE)/Fru/EhlPch/DxeLib.dsc
!else
!include $(PLATFORM_SI_PACKAGE)/Fru/JslPch/DxeLib.dsc
!endif

#
# Common
#
!if gSiPkgTokenSpaceGuid.PcdAcpiEnable == TRUE
 AslUpdateLib|$(PLATFORM_SI_PACKAGE)/Library/DxeAslUpdateLib/DxeAslUpdateLib.inf
!else
 AslUpdateLib|$(PLATFORM_SI_PACKAGE)/Library/DxeAslUpdateLibNull/DxeAslUpdateLibNull.inf
!endif
 SiFviLib|$(PLATFORM_SI_PACKAGE)/Library/DxeSiFviLib/DxeSiFviLib.inf
 SiFviInitLib|$(PLATFORM_SI_PACKAGE)/LibraryPrivate/DxeSiFviInitLib/DxeSiFviInitLib.inf
 SiConfigBlockLib|$(PLATFORM_SI_PACKAGE)/Library/BaseSiConfigBlockLib/BaseSiConfigBlockLib.inf
 BootMediaLib|$(PLATFORM_SI_PACKAGE)/Library/PeiDxeSmmBootMediaLib/DxeSmmBootMediaLib.inf

#
# Cpu
#
 CpuCommonLib|$(PLATFORM_SI_PACKAGE)/Cpu/LibraryPrivate/PeiDxeSmmCpuCommonLib/PeiDxeSmmCpuCommonLib.inf
!if gSiPkgTokenSpaceGuid.PcdSoftwareGuardEnable == TRUE
 SoftwareGuardLib|$(PLATFORM_SI_PACKAGE)/Cpu/LibraryPrivate/PeiDxeSoftwareGuardLib/PeiDxeSoftwareGuardLib.inf
!else
 SoftwareGuardLib|$(PLATFORM_SI_PACKAGE)/Cpu/LibraryPrivate/BaseSoftwareGuardLibNull/BaseSoftwareGuardLibNull.inf
!endif
 SmmCpuFeaturesLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/SmmCpuFeaturesLib/SmmCpuFeaturesLib.inf

#
# Pch
#
 DxePchPolicyLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/DxePchPolicyLib/DxePchPolicyLib.inf
 SmmPchPrivateLib|$(PLATFORM_SI_PACKAGE)/Pch/LibraryPrivate/SmmPchPrivateLib/SmmPchPrivateLib.inf

!if gBoardModuleTokenSpaceGuid.PcdUfsEnable == TRUE
!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
  BlockIoWrapperLib|$(PLATFORM_SI_PACKAGE)/Library/BlockIoWrapperLib/BlockIoWrapperLib.inf
  RpmbLib|$(PLATFORM_SI_PACKAGE)/Library/RpmbLib/RpmbLib.inf
!else
  BlockIoWrapperLib|$(PLATFORM_SI_PACKAGE)/Library/BlockIoWrapperLibNull/BlockIoWrapperLibNull.inf
!endif
!endif
#
# SystemAgent
#
 DxeSaPolicyLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/DxeSaPolicyLib/DxeSaPolicyLib.inf
 CpuPcieLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/LibraryPrivate/DxeSmmCpuPcieLib/DxeSmmCpuPcieLib.inf
!if gSiPkgTokenSpaceGuid.PcdSmbiosEnable == TRUE
 SmbiosMemoryLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/LibraryPrivate/DxeSmbiosMemoryLib/DxeSmbiosMemoryLib.inf
!else
 SmbiosMemoryLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/LibraryPrivate/DxeSmbiosMemoryLibNull/DxeSmbiosMemoryLibNull.inf
!endif

#
# TBT
#
 DxeITbtPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tbt/Library/DxeITbtPolicyLibNull/DxeITbtPolicyLibNull.inf
 DxeTcssInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tcss/LibraryPrivate/DxeTcssInitLibNull/DxeTcssInitLibNull.inf
