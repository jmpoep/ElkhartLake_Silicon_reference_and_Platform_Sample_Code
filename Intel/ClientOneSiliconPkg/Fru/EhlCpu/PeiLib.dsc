## @file
#  Component description file for the Elkhartlake CPU PEI FRU ibraries.
#
# @copyright
#  INTEL CONFIDENTIAL
#  Copyright 2018 - 2019 Intel Corporation.
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
#  IpBlock Memory Init
#
MemoryInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/MemoryInit/Icl/LibraryPrivate/PeiMemoryInitLib/PeiMemoryInitLib.inf
MemoryAddressEncodeLib|$(PLATFORM_SI_PACKAGE)/IpBlock/MemoryInit/Icl/Library/PeiDxeSmmMemAddrEncodeLib/PeiDxeSmmMemAddrEncodeLib.inf

#
#  IPU IpBlock and Fru Library
#
!if gSiPkgTokenSpaceGuid.PcdIpuEnable == TRUE
 PeiIpuPolicyPrivateLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Ipu/LibraryPrivate/PeiIpuPolicyPrivateLib/PeiIpuPolicyPrivateLibVer1.inf
 IpuInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Ipu/LibraryPrivate/PeiIpuInitPrivateLib/PeiIpuInitLib.inf
 IpuInitFruLib|$(PLATFORM_SI_PACKAGE)/Fru/JslCpu/Ipu/LibraryPrivate/PeiIpuInitFruLib/PeiIpuInitFruLib.inf
!else
 PeiIpuPolicyPrivateLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Ipu/LibraryPrivate/PeiIpuPolicyPrivateLibNull/PeiIpuPolicyPrivateLibNull.inf
 IpuInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Ipu/LibraryPrivate/PeiIpuInitPrivateLibNull/PeiIpuInitLibNull.inf
!endif

 UsbHostControllerInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Usb/LibraryPrivate/PeiUsbHostControllerInitLib/PeiUsbHostControllerInitLib.inf
 UsbDeviceControllerInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Usb/LibraryPrivate/PeiUsbDeviceControllerInitLib/PeiUsbDeviceControllerInitLib.inf

#
#  Intel Graphics IpBlock and Fru Library
#
PeiGraphicsPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Graphics/LibraryPrivate/PeiGraphicsPolicyLibGen11/PeiGraphicsPolicyLib.inf
!if gSiPkgTokenSpaceGuid.PcdIgdEnable == TRUE
 GraphicsInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Graphics/LibraryPrivate/PeiGraphicsInitLibGen11/PeiGraphicsInitLib.inf
 DisplayInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Graphics/LibraryPrivate/PeiDisplayInitLibGen11/PeiDisplayInitLib.inf
!else
 GraphicsInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Graphics/LibraryPrivate/PeiGraphicsDisableInitLib/PeiGraphicsDisableInitLib.inf
 DisplayInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Graphics/LibraryPrivate/PeiDisplayInitLibNull/PeiDisplayInitLibNull.inf
!endif

!if gSiPkgTokenSpaceGuid.PcdPeiDisplayEnable == TRUE
 DisplayLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Graphics/LibraryPrivate/PeiDisplayLib/PeiDisplayLib.inf
!else
 DisplayLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Graphics/LibraryPrivate/PeiDisplayLibNull/PeiDisplayLibNull.inf
!endif

#
#  Intel Overclocking IpBlock and Fru Library
#
#
  PeiOcPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Overclocking/LibraryPrivate/PeiOcPolicyLibNull/PeiOcPolicyLibNull.inf
!if gSiPkgTokenSpaceGuid.PcdOverclockEnable == TRUE
  PeiOcLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Overclocking/LibraryPrivate/PeiOcLib/PeiOcLib.inf
  PeiOcInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Overclocking/LibraryPrivate/PeiOcInitLib/PeiOcInitLib.inf
!else
  PeiOcLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Overclocking/LibraryPrivate/PeiOcLibNull/PeiOcLibNull.inf
  PeiOcInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Overclocking/LibraryPrivate/PeiOcInitLibNull/PeiOcInitLibNull.inf
!endif

 PeiCpuTraceHubPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/TraceHub/LibraryPrivate/PeiCpuTraceHubPolicyLib/PeiCpuTraceHubPolicyLib.inf
 PeiCpuTraceHubLib|$(PLATFORM_SI_PACKAGE)/IpBlock/TraceHub/LibraryPrivate/PeiCpuTraceHubLib/PeiCpuTraceHubLib.inf

#
#  VTD IpBlock
#
!if gSiPkgTokenSpaceGuid.PcdVtdEnable == TRUE
  PeiVtdPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Vtd/LibraryPrivate/PeiVtdPolicyLib/PeiVtdPolicyLib.inf
  VtdInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Vtd/LibraryPrivate/PeiVtdInitLib/PeiVtdInitLib.inf
!else
  PeiVtdPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Vtd/LibraryPrivate/PeiVtdPolicyLibNull/PeiVtdPolicyLibNull.inf
  VtdInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Vtd/LibraryPrivate/PeiVtdInitLibNull/PeiVtdInitLibNull.inf
!endif

#
# GNA
#
!if gSiPkgTokenSpaceGuid.PcdGnaEnable == TRUE
  GnaInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gna/LibraryPrivate/PeiGnaInitLib/PeiGnaInitLib.inf
  PeiGnaPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gna/LibraryPrivate/PeiGnaPolicyLib/PeiGnaPolicyLib.inf
!else
  GnaInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gna/LibraryPrivate/PeiGnaInitLibNull/PeiGnaInitLibNull.inf
  PeiGnaPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gna/LibraryPrivate/PeiGnaPolicyLibNull/PeiGnaPolicyLibNull.inf
!endif

#
# PSMI
#
!if gSiPkgTokenSpaceGuid.PcdPsmiEnable == TRUE
  PeiPsmiInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Psmi/LibraryPrivate/PeiPsmiInitLib/PeiPsmiInitLib.inf
!else
  PeiPsmiInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Psmi/LibraryPrivate/PeiPsmiInitLibNull/PeiPsmiInitLibNull.inf
!endif

#
#  PCIe IpBlock
#
  PeiPcieRpPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/PcieRp/LibraryPrivate/PeiPcieRpPolicyLib/PeiPcieRpPolicyLib.inf
  PeiPcieRpLib|$(PLATFORM_SI_PACKAGE)/IpBlock/PcieRp/Library/PeiPcieRpLib/PeiPcieRpLib.inf

#
#  BiosGuard IpBlock
#
!if gSiPkgTokenSpaceGuid.PcdBiosGuardEnable == TRUE
  BiosGuardLib|$(PLATFORM_SI_PACKAGE)/IpBlock/BiosGuard/LibraryPrivate/PeiBiosGuardLib/PeiBiosGuardLib.inf
!else
  BiosGuardLib|$(PLATFORM_SI_PACKAGE)/IpBlock/BiosGuard/LibraryPrivate/PeiBiosGuardLibNull/PeiBiosGuardLibNull.inf
!endif

#
#  TwoLm IpBlock
#
!if gSiPkgTokenSpaceGuid.Pcd2lmEnable == TRUE
  FmssMbLib|$(PLATFORM_SI_PACKAGE)/IpBlock/TwoLm/LibraryPrivate/FmssMbLib/FmssMbLib.inf
  TwoLmInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/TwoLm/LibraryPrivate/TwoLmInitLib/TwoLmInitLib.inf
  TwoLmPreMemPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/TwoLm/LibraryPrivate/TwoLmPreMemPolicyLib/TwoLmPreMemPolicyLib.inf
!else
  TwoLmInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/TwoLm/LibraryPrivate/TwoLmInitLibNull/TwoLmInitLibNull.inf
  TwoLmPreMemPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/TwoLm/LibraryPrivate/TwoLmPreMemPolicyLibNull/TwoLmPreMemPolicyLibNull.inf
!endif

#
#  VMD IpBlock
#
!if gSiPkgTokenSpaceGuid.PcdVmdEnable == TRUE
 PeiVmdInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Vmd/LibraryPrivate/PeiVmdInitLib/PeiVmdInitLib.inf
 PeiVmdPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Vmd/LibraryPrivate/PeiVmdPolicyLib/PeiVmdPolicyLib.inf
!else
 PeiVmdInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Vmd/LibraryPrivate/PeiVmdInitLibNull/PeiVmdInitLibNull.inf
 PeiVmdPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Vmd/LibraryPrivate/PeiVmdPolicyLibNull/PeiVmdPolicyLibNull.inf
!endif

#
# Cpu Pcie IpBlock
#
!if gSiPkgTokenSpaceGuid.PcdCpuPcieEnable == TRUE
 PeiCpuPciePreMemRpInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/LibraryPrivate/PeiCpuPcieRpInitLib/PeiCpuPciePreMemRpInitLib.inf
 PeiCpuPcieRpInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/LibraryPrivate/PeiCpuPcieRpInitLib/PeiCpuPcieRpInitLib.inf
 PeiCpuPciePolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/LibraryPrivate/PeiCpuPciePolicyLib/PeiCpuPciePolicyLib.inf
 DekelInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/LibraryPrivate/PeiCpuPcieDekelInitLib/PeiCpuPcieDekelInitLib.inf
!else
 PeiCpuPciePreMemRpInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/LibraryPrivate/PeiCpuPcieRpInitLibNull/PeiCpuPciePreMemRpInitLibNull.inf
 PeiCpuPcieRpInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/LibraryPrivate/PeiCpuPcieRpInitLibNull/PeiCpuPcieRpInitLibNull.inf
 DekelInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/LibraryPrivate/PeiCpuPcieDekelInitLibNull/PeiCpuPcieDekelInitLibNull.inf
 PeiCpuPciePolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/LibraryPrivate/PeiCpuPciePolicyLibNull/PeiCpuPciePolicyLibNull.inf
!endif

#
#  Telemetry
#
PeiTelemetryPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Telemetry/LibraryPrivate/PeiTelemetryPolicyLibNull/PeiTelemetryPolicyLibNull.inf

#
# Hybrid Grapics IpBlock
#
!if gSiPkgTokenSpaceGuid.PcdHgEnable == TRUE
  PeiHybridGraphicsInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/HybridGraphics/LibraryPrivate/PeiHybridGraphicsInitLib/PeiHybridGraphicsInitLib.inf
  PeiHybridGraphicsPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/HybridGraphics/LibraryPrivate/PeiHybridGraphicsPolicyLib/PeiHybridGraphicsPolicyLib.inf
!else
  PeiHybridGraphicsInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/HybridGraphics/LibraryPrivate/PeiHybridGraphicsInitLibNull/PeiHybridGraphicsInitLibNull.inf
  PeiHybridGraphicsPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/HybridGraphics/LibraryPrivate/PeiHybridGraphicsPolicyLibNull/PeiHybridGraphicsPolicyLibNull.inf
!endif

#
# PSF
#
  PeiCpuPsfInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Psf/LibraryPrivate/PeiCpuPsfInitLibNull/PeiCpuPsfInitLibNull.inf