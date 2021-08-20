## @file
#  Component description file for the Jasperlake PCH Common FRU libraries.
#
# @copyright
#  INTEL CONFIDENTIAL
#  Copyright 2019 Intel Corporation.
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

  PsfLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Psf/LibraryPrivate/PsfLib/PeiDxeSmmPsfLibVer1.inf
  P2sbLib|$(PLATFORM_SI_PACKAGE)/IpBlock/P2sb/Library/PeiDxeSmmP2sbLib/PeiDxeSmmP2sbLib.inf
  PchPcrLib|$(PLATFORM_SI_PACKAGE)/IpBlock/P2sb/Library/PeiDxeSmmPchPcrLib/PeiDxeSmmPchPcrLib.inf
  PchSbiAccessLib|$(PLATFORM_SI_PACKAGE)/IpBlock/P2sb/LibraryPrivate/PeiDxeSmmPchSbiAccessLib/PeiDxeSmmPchSbiAccessLib.inf
  IshInfoLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Ish/Library/IshInfoLib/IshInfoLibVer1.inf
  PseInfoLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Pse/Library/PseInfoLibNull/PseInfoLibNull.inf
  TccLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tcc/Library/PeiDxeSmmTccLibNull/PeiDxeSmmTccLibNull.inf
  SciLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Sci/Library/PeiDxeSmmSciLibNull/PeiDxeSmmSciLibNull.inf
  TsnLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tsn/Library/PeiDxeSmmTsnLibNull/PeiDxeSmmTsnLibNull.inf
  GbeMdiLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gbe/LibraryPrivate/PeiDxeSmmGbeMdiLib/PeiDxeSmmGbeMdiLib.inf
  GbeLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gbe/Library/PeiDxeSmmGbeLib/PeiDxeSmmGbeLib.inf
  EspiLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Espi/Library/PeiDxeSmmEspiLib/PeiDxeSmmEspiLib.inf
  EspiAccessPrivateLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Espi/LibraryPrivate/PeiDxeSmmEspiAccessPrivateLib/PeiDxeSmmEspiAccessPrivateLib.inf
  UsbLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Usb/Library/PeiDxeSmmUsbLib/PeiDxeSmmUsbLib.inf
  PchFiaLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Fia/LibraryPrivate/PeiPchFiaLib/PeiPchFiaLibVer1.inf
  PmcLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Pmc/Library/PeiDxeSmmPmcLib/PeiDxeSmmPmcLib.inf
  PmcPrivateLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Pmc/LibraryPrivate/PeiDxeSmmPmcPrivateLib/PeiDxeSmmPmcPrivateLibVer1.inf
  PmcPrivateLibWithS3|$(PLATFORM_SI_PACKAGE)/IpBlock/Pmc/LibraryPrivate/PeiDxeSmmPmcPrivateLib/PeiDxeSmmPmcPrivateLibWithS3.inf
  SmbusInfoLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Smbus/Library/PeiDxeSmmSmbusInfoLib/SmbusInfoLib.inf
  SmbusLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Smbus/LibraryPrivate/BaseSmbusLib/BaseSmbusLib.inf
  SpiCommonLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Spi/LibraryPrivate/BaseSpiCommonLib/BaseSpiCommonLib.inf
  SmbusCommonLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Smbus/LibraryPrivate/PeiDxeSmmSmbusCommonLib/PeiDxeSmmSmbusCommonLib.inf
  WdtCommonLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Wdt/LibraryPrivate/PeiDxeSmmWdtCommonLib/PeiDxeSmmWdtCommonLib.inf
  SataLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Sata/Library/PeiDxeSmmSataLib/PeiDxeSmmSataLibVer1.inf
  GpioLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gpio/Library/PeiDxeSmmGpioLib/PeiDxeSmmGpioLib.inf
  GpioPrivateLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gpio/LibraryPrivate/PeiDxeSmmGpioPrivateLib/PeiDxeSmmGpioPrivateLibVer1.inf
  GpioCheckConflictLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gpio/Library/BaseGpioCheckConflictLib/BaseGpioCheckConflictLib.inf
!if gSiPkgTokenSpaceGuid.PcdOcWdtEnable == TRUE
  OcWdtLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Wdt/Library/PeiOcWdtLib/PeiOcWdtLib.inf
!else
  OcWdtLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Wdt/Library/PeiOcWdtLibNull/PeiOcWdtLibNull.inf
!endif
  PeiWdtLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Wdt/LibraryPrivate/PeiWdtLib/PeiWdtLib.inf
  HdaLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Hda/Library/HdaLib/HdaLib.inf
  MeTypeLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/Library/PeiDxeMeTypeLib/PeiDxeMeTypeLib.inf
  MeChipsetLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/Library/PeiDxeMeChipsetLib/PeiDxeMeChipsetLib.inf
  MeShowBufferLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/Library/PeiDxeMeShowBufferLib/PeiDxeMeShowBufferLib.inf
  MeFwStsLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/Library/BaseMeFwStsLib/BaseMeFwStsLib.inf
  HeciInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/LibraryPrivate/PeiDxeHeciInitLib/PeiDxeHeciInitLib.inf
  AsfMsgLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Amt/LibraryPrivate/PeiDxeAsfMsgLib/PeiDxeAsfMsgLib.inf
  PchDmiAccessLib|$(PLATFORM_SI_PACKAGE)/IpBlock/PchDmi/Library/PeiDxeSmmPchDmiAccessLib/PeiDxeSmmPchDmiAccessLib.inf
  PchDmiLib|$(PLATFORM_SI_PACKAGE)/IpBlock/PchDmi/LibraryPrivate/PeiDxeSmmPchDmiLib/PeiDxeSmmPchDmiLib.inf
  PchDmiWithS3Lib|$(PLATFORM_SI_PACKAGE)/IpBlock/PchDmi/LibraryPrivate/PeiDxeSmmPchDmiLib/PeiDxeSmmPchDmiWithS3Lib.inf
  SpiAccessLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Spi/Library/PeiDxeSmmSpiAccessLib/PeiDxeSmmSpiAccessLib.inf
  SpiAccessPrivateLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Spi/LibraryPrivate/PeiDxeSmmSpiAccessPrivateLib/PeiDxeSmmSpiAccessPrivateLib.inf
  DciPrivateLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Dci/LibraryPrivate/PeiDxeSmmDciPrivateLib/PeiDxeSmmDciPrivateLibVer1.inf
  CnviLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Cnvi/Library/PeiDxeSmmCnviLib/PeiDxeSmmCnviLib.inf
  ItssLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Itss/Library/PeiDxeSmmItssLib/PeiDxeSmmItssLib.inf
  ThermalAccessLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Thermal/Library/PeiDxeSmmThermalAccessLib/PeiDxeSmmThermalAccessLib.inf
  RtcAccessLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Rtc/Library/PeiDxeSmmRtcAccessLib/PeiDxeSmmRtcAccessLib.inf
  PchTraceHubInfoLib|$(PLATFORM_SI_PACKAGE)/IpBlock/TraceHub/Library/PeiDxeSmmPchTraceHubInfoLib/PeiDxeSmmPchTraceHubInfoLib.inf
!if gSiPkgTokenSpaceGuid.PcdTraceHubEnable == TRUE
  PchTraceHubLib|$(PLATFORM_SI_PACKAGE)/IpBlock/TraceHub/LibraryPrivate/PeiDxeSmmPchTraceHubLib/PeiDxeSmmPchTraceHubLib.inf
  TraceHubHookLib|$(PLATFORM_SI_PACKAGE)/IpBlock/TraceHub/Library/PeiDxeSmmTraceHubHookLib/PeiDxeSmmTraceHubHookLib.inf
!else
  PchTraceHubLib|$(PLATFORM_SI_PACKAGE)/IpBlock/TraceHub/LibraryPrivate/BasePchTraceHubLibNull/BasePchTraceHubLibNull.inf
!endif
  PchPcieRpLib|$(PLATFORM_SI_PACKAGE)/IpBlock/PcieRp/Library/PeiDxeSmmPchPcieRpLib/PeiDxeSmmPchPcieRpLib.inf
  PciExpressHelpersLib|$(PLATFORM_SI_PACKAGE)/IpBlock/PcieRp/LibraryPrivate/PciExpressHelpersLibrary/PeiDxeSmmPciExpressHelpersLib.inf
  BasePcieHelperLib|$(PLATFORM_SI_PACKAGE)/IpBlock/PcieRp/Library/BasePcieHelperLib/BasePcieHelperLib.inf
  RstCrLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Rst/Library/PeiDxeSmmRstCrLib/PeiDxeSmmRstCrLibVer1.inf
  PsthLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Psth/Library/PeiDxeSmmPsthLib/PeiDxeSmmPsthLib.inf