## @file
#  Component description file for the ElkhartLake SiPkg PEI libraries.
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
# Silicon Init Pei Library
#
!include $(PLATFORM_SI_PACKAGE)/UniversalPeiLib.dsc

#
# FRUs
#
!include $(PLATFORM_SI_PACKAGE)/Fru/EhlCpu/PeiLib.dsc
!if gSiPkgTokenSpaceGuid.PcdEhlPchEnable == TRUE
!include $(PLATFORM_SI_PACKAGE)/Fru/EhlPch/PeiLib.dsc
!else
!include $(PLATFORM_SI_PACKAGE)/Fru/JslPch/PeiLib.dsc
!endif

 SiPolicyLib|$(PLATFORM_SI_PACKAGE)/Library/PeiSiPolicyLib/PeiSiPolicyLib.inf
 SiConfigBlockLib|$(PLATFORM_SI_PACKAGE)/Library/BaseSiConfigBlockLib/BaseSiConfigBlockLib.inf
 SiFviInitLib|$(PLATFORM_SI_PACKAGE)/LibraryPrivate/PeiSiFviInitLib/PeiSiFviInitLib.inf
 StallPpiLib|$(PLATFORM_SI_PACKAGE)/Library/PeiInstallStallPpiLib/PeiStallPpiLib.inf
 SiPolicyOverrideLib|$(PLATFORM_SI_PACKAGE)/LibraryPrivate/PeiPolicyOverrideLib/PeiSiPolicyOverrideLib.inf
 PeiSiSsidLib|$(PLATFORM_SI_PACKAGE)/LibraryPrivate/PeiSiSsidLib/PeiSiSsidLib.inf
 BootMediaLib|$(PLATFORM_SI_PACKAGE)/Library/PeiDxeSmmBootMediaLib/PeiBootMediaLib.inf
 SiMtrrLib|$(PLATFORM_SI_PACKAGE)/Library/SiMtrrLib/SiMtrrLib.inf
 CacheAsRamLib|$(PLATFORM_SI_PACKAGE)/Library/BaseCacheAsRamLib/BaseCacheAsRamLib.inf
 BaseBfxTempRamLib|$(PLATFORM_SI_PACKAGE)/Library/BaseBfxTempRamLib/BaseBfxTempRamLib.inf

#
# Pch
#
!if gSiPkgTokenSpaceGuid.PcdEhlPchEnable == TRUE
 PchInitLib|$(PLATFORM_SI_PACKAGE)/Pch/LibraryPrivate/PeiPchInitLib/PeiPchInitLibEhl.inf
!else
 PchInitLib|$(PLATFORM_SI_PACKAGE)/Pch/LibraryPrivate/PeiPchInitLib/PeiPchInitLibIcl.inf
!endif
 PchPolicyLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiPchPolicyLib/PeiPchPolicyLib.inf
!if gSiPkgTokenSpaceGuid.PcdS3Enable == TRUE
 PchSmmControlLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiPchSmmControlLib/PeiPchSmmControlLib.inf
!else
 PchSmmControlLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiPchSmmControlLibNull/PeiPchSmmControlLibNull.inf
!endif
 SerialIoI2cMasterLib|$(PLATFORM_SI_PACKAGE)/IpBlock/SerialIo/I2c/Library/PeiSerialIoI2cMasterLib/PeiSerialIoI2cMasterLib.inf
 PeiLpcLib|$(PLATFORM_SI_PACKAGE)/Pch/LibraryPrivate/PeiLpcLib/PeiLpcLib.inf
 PeiSerialIoInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/SerialIo/LibraryPrivate/PeiSerialIoInitLib/PeiSerialIoInitLib.inf
 PeiCpuPcieRpInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/LibraryPrivate/PeiCpuPcieRpInitLibNull/PeiCpuPcieRpInitLibNull.inf
#
# Cpu
#
 CpuCommonLib|$(PLATFORM_SI_PACKAGE)/Cpu/LibraryPrivate/PeiDxeSmmCpuCommonLib/PeiDxeSmmCpuCommonLib.inf
 CpuInitLib|$(PLATFORM_SI_PACKAGE)/Cpu/LibraryPrivate/PeiCpuInitLib/PeiCpuInitLib.inf
!if gSiPkgTokenSpaceGuid.PcdBiosGuardEnable == TRUE
 BiosGuardLib|$(PLATFORM_SI_PACKAGE)/IpBlock/BiosGuard/LibraryPrivate/PeiBiosGuardLib/PeiBiosGuardLib.inf
!else
 BiosGuardLib|$(PLATFORM_SI_PACKAGE)/IpBlock/BiosGuard/LibraryPrivate/PeiBiosGuardLibNull/PeiBiosGuardLibNull.inf
!endif
 CpuPowerMgmtLib|$(PLATFORM_SI_PACKAGE)/Cpu/LibraryPrivate/PeiCpuPowerMgmtLib/PeiCpuPowerMgmtLib.inf
!if gSiPkgTokenSpaceGuid.PcdTxtEnable == TRUE
 PeiTxtLib|$(PLATFORM_SI_PACKAGE)/Cpu/LibraryPrivate/PeiTxtLib/PeiTxtLib.inf
!else
 PeiTxtLib|$(PLATFORM_SI_PACKAGE)/Cpu/LibraryPrivate/PeiTxtLibNull/PeiTxtLibNull.inf
!endif
!if gSiPkgTokenSpaceGuid.PcdCpuPowerOnConfigEnable == TRUE
 CpuPowerOnConfigLib|$(PLATFORM_SI_PACKAGE)/Cpu/LibraryPrivate/PeiCpuPowerOnConfigLib/PeiCpuPowerOnConfigLib.inf
!else
 CpuPowerOnConfigLib|$(PLATFORM_SI_PACKAGE)/Cpu/LibraryPrivate/PeiCpuPowerOnConfigLibDisable/PeiCpuPowerOnConfigLibDisable.inf
!endif
!if gSiPkgTokenSpaceGuid.PcdSoftwareGuardEnable == TRUE
 SoftwareGuardLib|$(PLATFORM_SI_PACKAGE)/Cpu/LibraryPrivate/PeiDxeSoftwareGuardLib/PeiDxeSoftwareGuardLib.inf
!else
 SoftwareGuardLib|$(PLATFORM_SI_PACKAGE)/Cpu/LibraryPrivate/BaseSoftwareGuardLibNull/BaseSoftwareGuardLibNull.inf
!endif
!if gSiPkgTokenSpaceGuid.PcdSmbiosEnable == TRUE
 SmbiosCpuLib|$(PLATFORM_SI_PACKAGE)/Cpu/LibraryPrivate/PeiSmbiosCpuLib/PeiSmbiosCpuLib.inf
!else
 SmbiosCpuLib|$(PLATFORM_SI_PACKAGE)/Cpu/LibraryPrivate/PeiSmbiosCpuLibNull/PeiSmbiosCpuLibNull.inf
!endif

 PeiCpuPciePreMemRpInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/LibraryPrivate/PeiCpuPcieRpInitLibNull/PeiCpuPciePreMemRpInitLibNull.inf
 SaInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/LibraryPrivate/PeiSaInitLib/PeiSaInitLibEhl.inf

 PcieInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/LibraryPrivate/PeiPcieInitLib/PeiPcieInitLib.inf

!if gSiPkgTokenSpaceGuid.PcdPegEnable == TRUE
 SaPcieInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/LibraryPrivate/PeiSaPcieInitLib/PeiSaPcieInitLib.inf
!else
 SaPcieInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/LibraryPrivate/PeiSaPcieInitLib/PeiSaPcieInitLibDisableEhl.inf
!endif
!if gSiPkgTokenSpaceGuid.PcdSaDmiEnable == TRUE
 SaDmiInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/LibraryPrivate/PeiSaDmiInitLib/PeiSaDmiInitLib.inf
!else
 SaDmiInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/LibraryPrivate/PeiSaDmiInitLibNull/PeiSaDmiInitLibNull.inf
!endif


!if gSiPkgTokenSpaceGuid.PcdS3Enable == TRUE
 SmmAccessLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/PeiSmmAccessLib/PeiSmmAccessLib.inf
!else
 SmmAccessLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/PeiSmmAccessLibNull/PeiSmmAccessLibNull.inf
!endif

!if (gSiPkgTokenSpaceGuid.PcdPegEnable == TRUE) OR (gSiPkgTokenSpaceGuid.PcdSaDmiEnable == TRUE)
 SaPcieDmiLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/LibraryPrivate/PeiSaPcieDmiLib/PeiSaPcieDmiLib.inf
!endif
  PeiTcssPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tcss/LibraryPrivate/PeiTcssPolicyLibNull/PeiTcssPolicyLibNull.inf
  TcssPmcLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tcss/LibraryPrivate/PeiTcssPmcLibNull/PeiTcssPmcLibNull.inf
  PeiTcssInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tcss/LibraryPrivate/PeiTcssInitLibNull/PeiTcssInitLibNull.inf

  PeiSaPolicyLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/PeiSaPolicyLib/PeiSaPolicyLib.inf
  PeiMemPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/MemoryInit/Icl/Library/PeiMemPolicyLib/PeiMemPolicyLib.inf

#
# TBT
#
  PeiTbtTaskDispatchLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tbt/Library/PeiTbtTaskDispatchLibNull/PeiTbtTaskDispatchLibNull.inf
  PeiITbtInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tbt/LibraryPrivate/PeiITbtInitLibNull/PeiITbtInitLibNull.inf
  PeiITbtPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tbt/Library/PeiITbtPolicyLibNull/PeiITbtPolicyLibNull.inf

#
# Cpu
#
 CpuPolicyLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiCpuPolicyLib/PeiCpuPolicyLib.inf
