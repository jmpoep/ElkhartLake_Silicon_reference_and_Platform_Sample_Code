## @file
#  Component description file for the IceLake SiPkg DXE drivers.
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

!include $(PLATFORM_SI_PACKAGE)/UniversalDxe.dsc
#
# FRUs
#
!include $(PLATFORM_SI_PACKAGE)/Fru/IclCpu/Dxe.dsc
!include $(PLATFORM_SI_PACKAGE)/Fru/IclPch/Dxe.dsc

#
# Common
#
  $(PLATFORM_SI_PACKAGE)/Product/IceLake/SiInit/Dxe/SiInitDxe.inf

#
# Pch
#
  $(PLATFORM_SI_PACKAGE)/Pch/PchInit/Dxe/PchInitDxeIcl.inf
  $(PLATFORM_SI_PACKAGE)/IpBlock/SerialIo/I2c/I2cDriver/SerialIoI2cDriver.inf
  $(PLATFORM_SI_PACKAGE)/IpBlock/SerialIo/Uart/UartDriver/SerialIoUartDriver.inf
  $(PLATFORM_SI_PACKAGE)/Pch/SmmControl/RuntimeDxe/SmmControl.inf

  $(PLATFORM_SI_PACKAGE)/Pch/PchSmiDispatcher/Smm/PchSmiDispatcher.inf{
    <LibraryClasses>
      #SmiHandlerProfileLib|MdeModulePkg/Library/SmmSmiHandlerProfileLib/SmmSmiHandlerProfileLib.inf
      SmiHandlerProfileLib|Edk2/MdePkg/Library/SmiHandlerProfileLibNull/SmiHandlerProfileLibNull.inf
  }
  $(PLATFORM_SI_PACKAGE)/Pch/PchInit/Smm/PchInitSmm.inf

#
# SystemAgent
#
  $(PLATFORM_SI_PACKAGE)/SystemAgent/SmmAccess/Dxe/SmmAccess.inf

  $(PLATFORM_SI_PACKAGE)/SystemAgent/SaInit/Dxe/SaInitDxe.inf

  $(PLATFORM_SI_PACKAGE)/SystemAgent/BdatAccessHandler/Dxe/BdatAccessHandler.inf

!if gSiPkgTokenSpaceGuid.PcdHgEnable == TRUE
!if gSiPkgTokenSpaceGuid.PcdAcpiEnable == TRUE
  $(PLATFORM_SI_PACKAGE)/SystemAgent/AcpiTables/HybridGraphics/Peg/HgAcpiTables.inf
  $(PLATFORM_SI_PACKAGE)/SystemAgent/AcpiTables/HybridGraphics/Pch/HgAcpiTablesPch.inf
!endif
!endif

  $(PLATFORM_SI_PACKAGE)/SystemAgent/SaInit/Smm/SaLateInitSmm.inf {
    <LibraryClasses>
      S3BootScriptLib|MdePkg/Library/BaseS3BootScriptLibNull/BaseS3BootScriptLibNull.inf
  }

!if gSiPkgTokenSpaceGuid.PcdAcpiEnable == TRUE
  $(PLATFORM_SI_PACKAGE)/SystemAgent/AcpiTables/SaSsdt/SaSsdt.inf
  $(PLATFORM_SI_PACKAGE)/IpBlock/Graphics/AcpiTables/IgfxSsdt.inf
  $(PLATFORM_SI_PACKAGE)/IpBlock/Ipu/AcpiTables/IpuSsdt.inf
  $(PLATFORM_SI_PACKAGE)/IpBlock/Tcss/AcpiTables/SegSsdt/SegSsdt.inf
  $(PLATFORM_SI_PACKAGE)/IpBlock/Tcss/AcpiTables/TcssSsdt/TcssSsdt.inf
!endif

#
# Cpu
#
  $(PLATFORM_SI_PACKAGE)/Cpu/CpuInit/Dxe/CpuInitDxe.inf {
    <BuildOptions>
!if gSiPkgTokenSpaceGuid.PcdSourceDebugEnable == TRUE
      *_*_*_CC_FLAGS       = -DSOURCE_DEBUG_ENABLE
!endif
  }

!if gSiPkgTokenSpaceGuid.PcdBiosGuardEnable == TRUE
  $(PLATFORM_SI_PACKAGE)/IpBlock/BiosGuard/Smm/BiosGuardServices.inf
!endif

!if gSiPkgTokenSpaceGuid.PcdAcpiEnable == TRUE
  $(PLATFORM_SI_PACKAGE)/Cpu/AcpiTables/CpuAcpiTables.inf
!endif

!if gSiPkgTokenSpaceGuid.PcdPpmEnable == TRUE
  $(PLATFORM_SI_PACKAGE)/Cpu/PowerManagement/Dxe/PowerMgmtDxe.inf
  $(PLATFORM_SI_PACKAGE)/Cpu/PowerManagement/Smm/PowerMgmtSmm.inf
!endif

!if gSiPkgTokenSpaceGuid.PcdTxtEnable == TRUE
  $(PLATFORM_SI_PACKAGE)/Cpu/TxtInit/Dxe/TxtDxe.inf
!endif

!if gSiPkgTokenSpaceGuid.PcdJhiEnable == TRUE
  $(PLATFORM_SI_PACKAGE)/IpBlock/Me/Jhi/Dxe/JhiDxe.inf
!endif

#
# TBT
#
!if gSiPkgTokenSpaceGuid.PcdTbtEnable == TRUE
  $(PLATFORM_SI_PACKAGE)/IpBlock/Tbt/TbtInit/Smm/TbtSmm.inf
  $(PLATFORM_SI_PACKAGE)/IpBlock/Tbt/TbtInit/Dxe/TbtDxe.inf
!endif


