/** @file
  This PEI HybridGraphics Library initialize GPIO programming for the platform.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2019 Intel Corporation.

  The source code contained or described herein and all documents related to the
  source code ("Material") are owned by Intel Corporation or its suppliers or
  licensors. Title to the Material remains with Intel Corporation or its suppliers
  and licensors. The Material may contain trade secrets and proprietary and
  confidential information of Intel Corporation and its suppliers and licensors,
  and is protected by worldwide copyright and trade secret laws and treaty
  provisions. No part of the Material may be used, copied, reproduced, modified,
  published, uploaded, posted, transmitted, distributed, or disclosed in any way
  without Intel's prior express written permission.

  No license under any patent, copyright, trade secret or other intellectual
  property right is granted to or conferred upon you by disclosure or delivery
  of the Materials, either expressly, by implication, inducement, estoppel or
  otherwise. Any license under such intellectual property rights must be
  express and approved by Intel in writing.

  Unless otherwise agreed by Intel in writing, you may not remove or alter
  this notice or any other notice embedded in Materials by Intel or
  Intel's suppliers or licensors in any way.

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/
#include <Library/HobLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/TimerLib.h>
#include <Library/PciSegmentLib.h>
#include <CpuRegs.h>
#include <PcieRegs.h>
#include <Library/PeiHybridGraphicsInitLib.h>
#include <Library/PeiServicesLib.h>
#include <HgInfoHob.h>
#include <Library/GpioLib.h>
#include <Library/GpioNativeLib.h>

/**
  Initialize the HybridGraphics support (PEI).

  @param[in] HYBRID_GRAPHICS_CONFIG      *HgGpioData to access the HG related settings
**/
VOID
PeiHybridGraphicsInit (
  IN   HYBRID_GRAPHICS_CONFIG            *HgGpioData
  )
{
  HG_INFO_HOB             *HgInfoHob;
  EFI_STATUS              Status;

  DEBUG ((DEBUG_INFO, "HG:: HybridGraphics PEI initialization Starting\n"));
  HgInfoHob = NULL;
  ///
  /// Create HOB for HG Data
  ///
  Status = PeiServicesCreateHob (
             EFI_HOB_TYPE_GUID_EXTENSION,
             sizeof (HG_INFO_HOB),
             (VOID **) &HgInfoHob
             );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Initialize default HOB data

  HgInfoHob->EfiHobGuidType.Name = gHybridGraphicsInfoHobGuid;
  DEBUG ((DEBUG_INFO, "HgInfoHob->EfiHobGuidType.Name: %g\n", &HgInfoHob->EfiHobGuidType.Name));
  ZeroMem (&(HgInfoHob->HgInfo), sizeof (HG_INFO_HOB) - sizeof (EFI_HOB_GUID_TYPE));
  DEBUG ((DEBUG_INFO, "HgInfoHob @ %X\n", HgInfoHob));
  DEBUG ((DEBUG_INFO, "HgInfoHobSize - HobHeader: %X\n", sizeof (HG_INFO_HOB) - sizeof (EFI_HOB_GUID_TYPE)));
  DEBUG ((DEBUG_INFO, "HgInfoHobSize: %X\n", sizeof (HG_INFO_HOB)));
  DEBUG((DEBUG_INFO, "Install HG Info HOB\n"));

  //
  // Get the HOB for HG INFO
  //
  HgInfoHob = (HG_INFO_HOB *) GetFirstGuidHob (&gHybridGraphicsInfoHobGuid);
  if (HgInfoHob == NULL) {
    DEBUG ((EFI_D_INFO, "HG Info Hob not found\n"));
    return;
  }
  if (HgGpioData != NULL) {
    HgInfoHob->HgInfo.HgMode               = HgGpioData->HgMode;
    HgInfoHob->HgInfo.DelayAfterHoldReset  = HgGpioData->HgDelayAfterHoldReset;
    HgInfoHob->HgInfo.DelayAfterPwrEn      = HgGpioData->HgDelayAfterPwrEn;

    ///
    /// GPIO Assigned from policy
    ///
    HgInfoHob->HgInfo.Rtd3Pcie0Gpio.GpioSupport = HgGpioData->CpuPcie0Rtd3Gpio.GpioSupport;

    ///
    /// GPIO for PCIe 0
    ///
    if (HgInfoHob->HgInfo.Rtd3Pcie0Gpio.GpioSupport != NotSupported) {
      if (HgInfoHob->HgInfo.Rtd3Pcie0Gpio.GpioSupport == PchGpio) {
        HgInfoHob->HgInfo.Rtd3Pcie0Gpio.HoldRst.GpioNo   = HgGpioData->CpuPcie0Rtd3Gpio.HoldRst.GpioNo;
        HgInfoHob->HgInfo.Rtd3Pcie0Gpio.PwrEnable.GpioNo = HgGpioData->CpuPcie0Rtd3Gpio.PwrEnable.GpioNo;
      }
      HgInfoHob->HgInfo.Rtd3Pcie0Gpio.HoldRst.ExpanderNo   = HgGpioData->CpuPcie0Rtd3Gpio.HoldRst.ExpanderNo;
      HgInfoHob->HgInfo.Rtd3Pcie0Gpio.PwrEnable.ExpanderNo = HgGpioData->CpuPcie0Rtd3Gpio.PwrEnable.ExpanderNo;
      HgInfoHob->HgInfo.Rtd3Pcie0Gpio.HoldRst.Active       = HgGpioData->CpuPcie0Rtd3Gpio.HoldRst.Active;
      HgInfoHob->HgInfo.Rtd3Pcie0Gpio.PwrEnable.Active     = HgGpioData->CpuPcie0Rtd3Gpio.PwrEnable.Active;
      HgInfoHob->HgInfo.RootPortIndex = HgGpioData->RootPortIndex;
    }
  }

  DEBUG ((DEBUG_INFO, "HG:: HybridGraphics PEI initialization Ends\n"));
}
