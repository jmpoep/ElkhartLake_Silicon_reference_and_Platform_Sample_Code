## @file
#  Component description file for the ElkhartLake PCH DXE FRU drivers.
#
# @copyright
#  INTEL CONFIDENTIAL
#  Copyright 2018 - 2020 Intel Corporation.
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

  $(PLATFORM_SI_PACKAGE)/IpBlock/Wdt/Dxe/WdtDxe.inf
!if gSiPkgTokenSpaceGuid.PcdSmmVariableEnable == TRUE
  $(PLATFORM_SI_PACKAGE)/IpBlock/Spi/Smm/SpiSmm.inf
  $(PLATFORM_SI_PACKAGE)/IpBlock/Spi/Dxe/SpiSmmStub.inf
  $(PLATFORM_SI_PACKAGE)/IpBlock/Spi/Dxe/SpiSmmDxe.inf
!else
  $(PLATFORM_SI_PACKAGE)/IpBlock/Spi/RuntimeDxe/SpiRuntime.inf
!endif
  $(PLATFORM_SI_PACKAGE)/IpBlock/Smbus/Smm/SmbusSmm.inf
  $(PLATFORM_SI_PACKAGE)/IpBlock/Smbus/Dxe/SmbusDxe.inf
  $(PLATFORM_SI_PACKAGE)/IpBlock/Scs/EmmcSoftwareTuning/EmmcSoftwareTuning.inf

!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
  $(PLATFORM_SI_PACKAGE)/IpBlock/Me/HeciInit/RunTimeDxe/HeciRuntimeDxe.inf
  $(PLATFORM_SI_PACKAGE)/IpBlock/Me/HeciInit/Smm/HeciInitSmm.inf
  $(PLATFORM_SI_PACKAGE)/IpBlock/Me/TrustedChannel/Smm/TrustedChannelSmm.inf
  $(PLATFORM_SI_PACKAGE)/IpBlock/Me/HeciInit/Dxe/HeciInitBfx.inf
  $(PLATFORM_SI_PACKAGE)/IpBlock/Me/StorageProxy/Dxe/StorageProxyDxe.inf {
     <LibraryClasses>
!if $(TARGET) == DEBUG
       DebugLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseDebugLibAllDebugPort/BaseDebugLibAllDebugPort.inf
     <PcdsPatchableInModule>
       gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel|0x80000147
!endif
  }
!else
  $(PLATFORM_SI_PACKAGE)/IpBlock/Me/HeciInit/Dxe/HeciInit.inf
!endif
  $(PLATFORM_SI_PACKAGE)/IpBlock/Me/MeFwDowngrade/Dxe/MeFwDowngrade.inf
  $(PLATFORM_SI_PACKAGE)/IpBlock/Me/Asf/Dxe/AsfDxe.inf
  $(PLATFORM_SI_PACKAGE)/IpBlock/Me/HwAsset/Dxe/HwAssetDxe.inf
!if gSiPkgTokenSpaceGuid.PcdIntegratedTouchEnable == TRUE
  $(PLATFORM_SI_PACKAGE)/IpBlock/Me/IntegratedTouch/IntegratedTouch.inf
!endif

!if gSiPkgTokenSpaceGuid.PcdAmtEnable == TRUE
  $(PLATFORM_SI_PACKAGE)/IpBlock/Amt/AmtInit/Dxe/AmtInitDxe.inf
  $(PLATFORM_SI_PACKAGE)/IpBlock/Amt/BiosExtensionLoader/Dxe/BiosExtensionLoader.inf
!endif

  $(PLATFORM_SI_PACKAGE)/IpBlock/Tcc/Dxe/TccTuningDxe.inf
