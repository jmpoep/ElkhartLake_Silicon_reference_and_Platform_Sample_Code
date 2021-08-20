## @file
#  Component description file for the IceLake SiPkg both Pei and Dxe libraries DSC file.
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
# Silicon Init Common Library
#

#
# Set PCH generation according PCD.
# The DEFINE will be used to select PCH library INF file corresponding to PCH generation
#
DEFINE  PCH = Cnl

!include $(PLATFORM_SI_PACKAGE)/UniversalCommonLib.dsc
#
# FRUs
#
!include $(PLATFORM_SI_PACKAGE)/Fru/IclCpu/CommonLib.dsc
!include $(PLATFORM_SI_PACKAGE)/Fru/IclPch/CommonLib.dsc

#
# Common
#
 MmPciLib|$(PLATFORM_SI_PACKAGE)/Library/PeiDxeSmmMmPciLib/PeiDxeSmmMmPciLib.inf
 PciExpressLib|$(PLATFORM_SI_PACKAGE)/Library/BasePciExpressMultiSegLib/BasePciExpressMultiSegLib.inf
 PciSegmentLib|$(PLATFORM_SI_PACKAGE)/Library/BasePciSegmentMultiSegLibPci/BasePciSegmentMultiSegLibPci.inf

#
# Cpu
#
 SecCpuLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/SecCpuLib/SecCpuLib.inf
 TxtLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiDxeTxtLib/PeiDxeTxtLib.inf
 CpuPlatformLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiDxeSmmCpuPlatformLib/PeiDxeSmmCpuPlatformLib.inf

!if gSiPkgTokenSpaceGuid.PcdBootGuardEnable == TRUE
 BootGuardLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiDxeSmmBootGuardLib/PeiDxeSmmBootGuardLib.inf
!else
 BootGuardLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiDxeSmmBootGuardLibNull/PeiDxeSmmBootGuardLibNull.inf
!endif

 SoftwareGuardLib|$(PLATFORM_SI_PACKAGE)/Cpu/LibraryPrivate/PeiDxeSoftwareGuardLib/PeiDxeSoftwareGuardLib.inf
 CpuMailboxLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiDxeSmmCpuMailboxLib/PeiDxeSmmCpuMailboxLib.inf

#
# Pch
#
 SecPchLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/SecPchLib/SecPchLib.inf
 PchCycleDecodingLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchCycleDecodingLib/PeiDxeSmmPchCycleDecodingLib.inf
 PchInfoLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchInfoLib/PeiDxeSmmPchInfoLibIcl.inf
 !if gSiPkgTokenSpaceGuid.PcdTraceHubEnable == TRUE
 PchTraceHubLib|$(PLATFORM_SI_PACKAGE)/Pch/LibraryPrivate/PeiDxeSmmPchTraceHubLib/PeiDxeSmmPchTraceHubLib.inf
!else
 PchTraceHubLib|$(PLATFORM_SI_PACKAGE)/Pch/LibraryPrivate/BasePchTraceHubLibNull/BasePchTraceHubLibNull.inf
!endif

!if gSiPkgTokenSpaceGuid.PcdSerialIoUartEnable == TRUE
 SerialIoUartLib|$(PLATFORM_SI_PACKAGE)/IpBlock/SerialIo/Uart/Library/PeiDxeSmmSerialIoUartLib/PeiDxeSmmSerialIoUartLib.inf
!else
 SerialIoUartLib|$(PLATFORM_SI_PACKAGE)/IpBlock/SerialIo/Uart/Library/BaseSerialIoUartLibNull/BaseSerialIoUartLibNull.inf
!endif

 SerialIoAccessLib|$(PLATFORM_SI_PACKAGE)/IpBlock/SerialIo/Library/PeiDxeSmmSerialIoAccessLib/PeiDxeSmmSerialIoAccessLib.inf
 SerialIoPrivateLib|$(PLATFORM_SI_PACKAGE)/IpBlock/SerialIo/LibraryPrivate/PeiDxeSmmSerialIoPrivateLib/PeiDxeSmmSerialIoPrivateLibVer1.inf
 ResetSystemLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/BaseResetSystemLib/BaseResetSystemLib.inf
 #private

 PchXhciLib|$(PLATFORM_SI_PACKAGE)/Pch/LibraryPrivate/PeiDxeSmmPchXhciLib/PeiDxeSmmPchXhciLib.inf
 SerialIoI2cMasterCommonLib|$(PLATFORM_SI_PACKAGE)/IpBlock/SerialIo/I2c/LibraryPrivate/PeiDxeSerialIoI2cMasterCommonLib/PeiDxeSerialIoI2cMasterCommonLib.inf
!if gSiPkgTokenSpaceGuid.PcdIclPchEnable == TRUE
  PchPsfPrivateLib|$(PLATFORM_SI_PACKAGE)/Pch/LibraryPrivate/PeiDxeSmmPchPsfPrivateLib/PeiDxeSmmPchPsfPrivateLibIcl.inf
!else
  PchPsfPrivateLib|$(PLATFORM_SI_PACKAGE)/Pch/LibraryPrivate/PeiDxeSmmPchPsfPrivateLib/PeiDxeSmmPchPsfPrivateLibCnl.inf
!endif
 PeiHsioLib|$(PLATFORM_SI_PACKAGE)/Pch/LibraryPrivate/PeiHsioLib/PeiHsioLibIcl.inf
 SiScheduleResetLib|$(PLATFORM_SI_PACKAGE)/Pch/LibraryPrivate/BaseSiScheduleResetLib/BaseSiScheduleResetLib.inf

#
# SA
#
 SecSaLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/SecSaLib/SecSaLib.inf
 SaPlatformLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/PeiDxeSmmSaPlatformLib/PeiDxeSmmSaPlatformLib.inf
!if gSiPkgTokenSpaceGuid.PcdIclPchEnable == TRUE
 ItbtPcieRpLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/LibraryPrivate/DxeItbtPcieRpLib/DxeItbtPcieRpLib.inf
!endif
!if gSiPkgTokenSpaceGuid.PcdIclCpuEnable == TRUE
 CpuRegbarAccessLib|$(PLATFORM_SI_PACKAGE)/IpBlock/P2sb/Library/PeiDxeSmmCpuRegbarAccessLib/PeiDxeSmmCpuRegbarAccessLib.inf
!endif
#
# TBT
#
  TbtCommonLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tbt/Library/PeiDxeSmmTbtCommonLib/TbtCommonLib.inf
  DxeTbtDisBmeLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tbt/Library/DxeTbtDisBmeLib/DxeTbtDisBmeLib.inf
