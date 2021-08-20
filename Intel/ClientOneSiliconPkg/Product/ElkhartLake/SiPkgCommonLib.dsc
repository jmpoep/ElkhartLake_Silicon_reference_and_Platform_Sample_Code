## @file
#  Component description file for the ElkhartLake SiPkg both Pei and Dxe libraries DSC file.
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
!if gSiPkgTokenSpaceGuid.PcdEhlPchEnable == TRUE
DEFINE  PCH = Ehl
!else
DEFINE  PCH = Jsl
!endif

!include $(PLATFORM_SI_PACKAGE)/UniversalCommonLib.dsc
#
# FRUs
#
!include $(PLATFORM_SI_PACKAGE)/Fru/EhlCpu/CommonLib.dsc
!if gSiPkgTokenSpaceGuid.PcdEhlPchEnable == TRUE
!include $(PLATFORM_SI_PACKAGE)/Fru/EhlPch/CommonLib.dsc
!else
!include $(PLATFORM_SI_PACKAGE)/Fru/JslPch/CommonLib.dsc
!endif

#
# Common
#
 PreSiliconEnvDetectLib|$(PLATFORM_SI_PACKAGE)/Library/BasePreSiliconEnvDetectLib/BasePreSiliconEnvDetectLib.inf
 MmPciLib|$(PLATFORM_SI_PACKAGE)/Library/PeiDxeSmmMmPciLib/PeiDxeSmmMmPciLib.inf
 PciExpressLib|$(PLATFORM_SI_PACKAGE)/Library/BasePciExpressMultiSegLib/BasePciExpressMultiSegLib.inf
 PciSegmentLib|$(PLATFORM_SI_PACKAGE)/Library/BasePciSegmentMultiSegLibPci/BasePciSegmentMultiSegLibPci.inf
!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
 CircularBufferLib|$(PLATFORM_SI_PACKAGE)/Library/BaseCircularBufferLib/BaseCircularBufferLib.inf
 VariableNvmStorageLib|$(PLATFORM_SI_PACKAGE)/Library/BaseVariableNvmStorageLib/BaseVariableNvmStorageLib.inf
 CseVariableStorageLib|$(PLATFORM_SI_PACKAGE)/VariableStorage/LibraryPrivate/BaseCseVariableStorageLib/BaseCseVariableStorageLib.inf
 CseVariableStorageIndexLib|$(PLATFORM_SI_PACKAGE)/VariableStorage/LibraryPrivate/BaseCseVariableStorageIndexLib/BaseCseVariableStorageIndexLib.inf
 CseVariableStorageSelectorLib|$(PLATFORM_SI_PACKAGE)/VariableStorage/LibraryPrivate/BaseCseSelectorLib/BaseCseSelectorLib.inf
!endif

#
# Cpu
#
 SecCpuLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/SecCpuLib/SecCpuLib.inf
!if gSiPkgTokenSpaceGuid.PcdTxtEnable == TRUE
 TxtLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiDxeTxtLib/PeiDxeTxtLib.inf
!else
 TxtLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiDxeTxtLibNull/PeiDxeTxtLibNull.inf
!endif
 CpuPlatformLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiDxeSmmCpuPlatformLib/PeiDxeSmmCpuPlatformLib.inf

!if gSiPkgTokenSpaceGuid.PcdBootGuardEnable == TRUE
 BootGuardLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiDxeSmmBootGuardLib/PeiDxeSmmBootGuardLib.inf
!else
 BootGuardLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiDxeSmmBootGuardLibNull/PeiDxeSmmBootGuardLibNull.inf
!endif

!if gSiPkgTokenSpaceGuid.PcdSoftwareGuardEnable == TRUE
 SoftwareGuardLib|$(PLATFORM_SI_PACKAGE)/Cpu/LibraryPrivate/PeiDxeSoftwareGuardLib/PeiDxeSoftwareGuardLib.inf
!else
 SoftwareGuardLib|$(PLATFORM_SI_PACKAGE)/Cpu/LibraryPrivate/BaseSoftwareGuardLibNull/BaseSoftwareGuardLibNull.inf
!endif

 CpuMailboxLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiDxeSmmCpuMailboxLib/PeiDxeSmmCpuMailboxLib.inf

#
# Pch
#
 SerialIoUartDebugPropertyPcdLib|$(PLATFORM_SI_PACKAGE)/IpBlock/SerialIo/Uart/Library/SerialIoUartDebugPropertyPcdLib/SerialIoUartDebugPropertyPcdLib.inf
 SecPchLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/SecPchLib/SecPchLib.inf
 PchCycleDecodingLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchCycleDecodingLib/PeiDxeSmmPchCycleDecodingLib.inf
!if gSiPkgTokenSpaceGuid.PcdEhlPchEnable == TRUE
  PchInfoLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchInfoLib/PeiDxeSmmPchInfoLibEhl.inf
!else
  PchInfoLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchInfoLib/PeiDxeSmmPchInfoLibJsl.inf
!endif
 CpuPcieInfoLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/Library/PeiDxeSmmCpuPcieInfoLib/PeiDxeSmmCpuPcieInfoLibTgl.inf
 CpuPcieInitCommonLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/Library/PeiDxeSmmCpuPcieInitCommonLib/PeiDxeSmmCpuPcieInitCommonLib.inf
 CpuPcieRpLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/Library/PeiDxeSmmCpuPcieRpLib/PeiDxeSmmCpuPcieRpLib.inf
 CpuSbiAccessLib|$(PLATFORM_SI_PACKAGE)/IpBlock/P2sb/Library/PeiDxeSmmCpuSbiAccessLib/PeiDxeSmmCpuSbiAccessLib.inf
!if gSiPkgTokenSpaceGuid.PcdSerialIoUartEnable == TRUE
 SerialIoUartLib|$(PLATFORM_SI_PACKAGE)/IpBlock/SerialIo/Uart/Library/PeiDxeSmmSerialIoUartLib/PeiDxeSmmSerialIoUartLib.inf
!else
 SerialIoUartLib|$(PLATFORM_SI_PACKAGE)/IpBlock/SerialIo/Uart/Library/BaseSerialIoUartLibNull/BaseSerialIoUartLibNull.inf
!endif

!if gSiPkgTokenSpaceGuid.PcdEhlPchEnable == TRUE
  SerialIoPrivateLib|$(PLATFORM_SI_PACKAGE)/IpBlock/SerialIo/LibraryPrivate/PeiDxeSmmSerialIoPrivateLib/PeiDxeSmmSerialIoPrivateLibVer3.inf
!else
  SerialIoPrivateLib|$(PLATFORM_SI_PACKAGE)/IpBlock/SerialIo/LibraryPrivate/PeiDxeSmmSerialIoPrivateLib/PeiDxeSmmSerialIoPrivateLibVer1.inf
!endif

 SerialIoAccessLib|$(PLATFORM_SI_PACKAGE)/IpBlock/SerialIo/Library/PeiDxeSmmSerialIoAccessLib/PeiDxeSmmSerialIoAccessLib.inf
 PchPseIoLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchPseIoLib/PeiDxeSmmPchPseIoLibEhl.inf
 ResetSystemLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/BaseResetSystemLib/BaseResetSystemLib.inf
 #private
!if gSiPkgTokenSpaceGuid.PcdEhlPchEnable == TRUE
   GpioPrivateLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gpio/LibraryPrivate/PeiDxeSmmGpioPrivateLib/PeiDxeSmmGpioPrivateLibVer3.inf
!else
   GpioPrivateLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gpio/LibraryPrivate/PeiDxeSmmGpioPrivateLib/PeiDxeSmmGpioPrivateLibVer1.inf
!endif

 PchXhciLib|$(PLATFORM_SI_PACKAGE)/Pch/LibraryPrivate/PeiDxeSmmPchXhciLib/PeiDxeSmmPchXhciLib.inf
 SerialIoI2cMasterCommonLib|$(PLATFORM_SI_PACKAGE)/IpBlock/SerialIo/I2c/LibraryPrivate/PeiDxeSerialIoI2cMasterCommonLib/PeiDxeSerialIoI2cMasterCommonLib.inf

!if gSiPkgTokenSpaceGuid.PcdEhlPchEnable == TRUE
 PeiHsioLib|$(PLATFORM_SI_PACKAGE)/Pch/LibraryPrivate/PeiHsioLib/PeiHsioLibTgl.inf
!else
 PeiHsioLib|$(PLATFORM_SI_PACKAGE)/Pch/LibraryPrivate/PeiHsioLib/PeiHsioLibIcl.inf
!endif
 SiScheduleResetLib|$(PLATFORM_SI_PACKAGE)/Pch/LibraryPrivate/BaseSiScheduleResetLib/BaseSiScheduleResetLib.inf
 SiScheduleResetLib|$(PLATFORM_SI_PACKAGE)/Pch/LibraryPrivate/BaseSiScheduleResetLib/BaseSiScheduleResetLib.inf

#
# SA
#
 SecSaLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/SecSaLib/SecSaLib.inf
 SaPlatformLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/PeiDxeSmmSaPlatformLib/PeiDxeSmmSaPlatformLib.inf
 ItbtPcieRpLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/LibraryPrivate/DxeItbtPcieRpLibNull/DxeItbtPcieRpLibNull.inf
 CpuRegbarAccessLib|$(PLATFORM_SI_PACKAGE)/IpBlock/P2sb/Library/PeiDxeSmmCpuRegbarAccessLib/PeiDxeSmmCpuRegbarAccessLib.inf

#
# TBT
#

  TbtCommonLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tbt/Library/PeiDxeSmmTbtCommonLib/TbtCommonLib.inf
  SmmTbtCommonLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tbt/Library/SmmTbtCommonLib/SmmTbtCommonLib.inf
  DxeTbtDisBmeLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tbt/Library/DxeTbtDisBmeLib/DxeTbtDisBmeLib.inf
