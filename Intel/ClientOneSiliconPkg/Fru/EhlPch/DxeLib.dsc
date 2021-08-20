# @file
#  Component description file for the ElkhartLake PCH DXE FRU libraries.
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
  DxeHdaNhltLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Hda/Library/DxeHdaNhltLib/DxeHdaNhltLib.inf
  DxeHdaPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Hda/LibraryPrivate/DxeHdaPolicyLib/DxeHdaPolicyLib.inf
  DxeMeLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/Library/DxeMeLib/DxeMeLib.inf
  MbpDataLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/Library/DxeMbpDataLib/DxeMbpDataLib.inf
  DxeMePolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/Library/DxeMePolicyLib/DxeMePolicyLib.inf
  PttHeciLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/Library/DxePttHeciLib/DxePttHeciLib.inf
  !if gSiPkgTokenSpaceGuid.PcdIntegratedTouchEnable == TRUE
    DxeTouchHeciMsgsLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/Library/DxeTouchHeciMsgsLib/DxeTouchHeciMsgsLib.inf
  !endif
  !if gSiPkgTokenSpaceGuid.PcdJhiEnable == TRUE
    DxeJhiSupportLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/Jhi/DxeJhiSupportLib/DxeJhiSupportLib.inf
    DxeBeihaiLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/LibraryPrivate/DxeBeihaiLib/DxeBeihaiLib.inf
  !endif
  DxeAsfLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/Library/DxeAsfLib/DxeAsfLib.inf
  DxeAsfHeciLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/Library/DxeAsfHeciLib/DxeAsfHeciLib.inf
  !if gSiPkgTokenSpaceGuid.PcdAmtEnable == TRUE
    DxeAmtHeciLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Amt/Library/DxeAmtHeciLib/DxeAmtHeciLib.inf
    DxeAmtPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Amt/Library/DxeAmtPolicyLib/DxeAmtPolicyLib.inf
  !else
    DxeAmtPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Amt/Library/DxeAmtPolicyLibNull/DxeAmtPolicyLibNull.inf
  !endif
  GpioHelpersLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gpio/LibraryPrivate/BaseGpioHelpersLibNull/BaseGpioHelpersLibNull.inf
  GpioNameBufferLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gpio/LibraryPrivate/DxeGpioNameBufferLib/DxeGpioNameBufferLib.inf
  DxeGpioPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gpio/LibraryPrivate/DxeGpioPolicyLib/DxeGpioPolicyLib.inf
  ScsLocationLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Scs/LibraryPrivate/BaseScsLocationLib/BaseScsLocationLibVer3.inf
  DxePchPcieRpPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/PcieRp/LibraryPrivate/DxePchPcieRpPolicyLib/DxePchPcieRpPolicyLib.inf
  TopSwapLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Rtc/Library/SmmTopSwapLib/SmmTopSwapLib.inf
!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
  DxeHeciInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/LibraryPrivate/DxeHeciInitLib/DxeHeciInitLib.inf
  StorageProxyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/Library/DxeStorageProxyLib/DxeStorageProxyLib.inf
  HeciRuntimeLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/LibraryPrivate/RuntimeDxeSmmHeciRuntimeLib/SmmHeciRuntimeLib.inf
  CseVariableStorageGeneralDataLib|$(PLATFORM_SI_PACKAGE)/VariableStorage/LibraryPrivate/BaseCseGeneralDataLib/BaseCseGeneralDataLib.inf
  CseVariableStorageInitLib|$(PLATFORM_SI_PACKAGE)/VariableStorage/LibraryPrivate/DxeSmmCseInitLib/DxeSmmCseInitLib.inf
  CseVariableStorageIoLib|$(PLATFORM_SI_PACKAGE)/VariableStorage/LibraryPrivate/SmmCseVariableStorageIoLib/SmmCseVariableStorageIoLib.inf
  CseVariableStorageOsProxyLib|$(PLATFORM_SI_PACKAGE)/VariableStorage/LibraryPrivate/BaseCseOsProxyLib/BaseCseOsProxyLib.inf
  CseVariableStorageStatusLib|$(PLATFORM_SI_PACKAGE)/VariableStorage/LibraryPrivate/PeiDxeSmmCseVariableStorageStatusLib/DxeSmmCseVariableStorageStatusLib.inf

[LibraryClasses.X64.DXE_RUNTIME_DRIVER]
  HeciRuntimeLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/LibraryPrivate/RuntimeDxeSmmHeciRuntimeLib/RuntimeDxeHeciRuntimeLib.inf
!endif
