/** @file
  PEIM to initialize Early Display.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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

#include <Library/PeiDisplayInitLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/PostCodeLib.h>
#include <CpuRegs.h>
#include <Library/CpuPlatformLib.h>
#include <Register/IgdRegs.h>
#include <Library/GpioNativePads.h>
#include <Library/GpioPrivateLib.h>

EFI_PEI_PPI_DESCRIPTOR  mEnablePeiGraphicsPpi = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEnablePeiGraphicsPpiGuid,
  NULL
};


/**
  ProgramDisplayWorkaround: Programs Display specific Workarounds

  @param[in]  GtPreMemConfig  - GRAPHICS_PEI_PREMEM_PREMEM_CONFIG to access the GtPreMemConfig related information

  @retval     EFI_SUCCESS     - Display workarounds done
**/
EFI_STATUS
ProgramDisplayWorkaround (
  IN   GRAPHICS_PEI_PREMEM_CONFIG      *GtPreMemConfig
  )
{
  UINT32          GttMmAdr;
  UINT16          IsPciCmdEnabled;
  UINT64          McD2BaseAddress;
  CPU_STEPPING    CpuSteppingId;
  CPU_GENERATION  CpuGeneration;
  CPU_SKU         CpuSku;
  UINT32          Data32;
  UINT32          Data32And;
  Data32          = 0;
  Data32And       = 0;

  DEBUG ((DEBUG_INFO, "ProgramDisplayWorkaround: Begin \n"));

  CpuSteppingId   = GetCpuStepping ();
  CpuGeneration   = GetCpuGeneration ();
  CpuSku          = GetCpuSku ();

  McD2BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, 0);

  if (PciSegmentRead16 (McD2BaseAddress + R_SA_IGD_VID) == 0xFFFF) {
    return EFI_SUCCESS;
  }

  GttMmAdr = (PciSegmentRead32 (McD2BaseAddress + R_SA_IGD_GTTMMADR)) & 0xFFFFFFF0;
  if (GttMmAdr == 0) {
    GttMmAdr = GtPreMemConfig->GttMmAdr;
    PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR, (UINT32) (GttMmAdr & 0xFFFFFFFF));
    PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR + 4, 0);
  }

  IsPciCmdEnabled = ((PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS(SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, 0) + R_SA_IGD_CMD)) & (UINT16)(BIT2 | BIT1));
  if (!IsPciCmdEnabled) {
    ///
    /// Enable Bus Master and Memory access on 0:2:0
    ///
    PciSegmentOr16 (McD2BaseAddress + R_SA_IGD_CMD, (BIT2 | BIT1));
  }

  //
  // Disable DGR clock gating
  //
  Data32 = BIT13;
  //
  // Set Fclk hysteresis idle timer to 15 clocks
  //
  Data32 |= 0xF;
  MmioOr32 (GttMmAdr + R_SA_GTTMMADR_OFFSET_101014, Data32);
  //
  // Disable the interrupt entry cache in the IOMMU (0x10105C bit [23] to 1)
  //
  MmioOr32 (GttMmAdr + R_SA_GTTMMADR_OFFSET_10105C, BIT23);
  //
  // Sets the Powerdown override for pending queue allocation to disable BDF hit2pend logic
  //
  MmioOr32 (GttMmAdr + R_SA_GTTMMADR_OFFSET_101058, BIT2);
  return EFI_SUCCESS;
}

/**
  DisplayNativeGpioInit: Initialize the Display Native Gpio

  @param[in] GtConfig        - GRAPHICS_PEI_CONFIG to access the GtConfig related information

  @retval    EFI_STATUS
**/
EFI_STATUS
DisplayNativeGpioInit (
  IN   GRAPHICS_PEI_CONFIG             *GtConfig
  )
{

  EFI_STATUS         Status;

  DEBUG ((DEBUG_INFO, "DisplayNativeGpioInit: Begin \n"));

  //
  // Enable EDP HPD, VDD and BKLT pins for eDP Panel
  //
  if (GtConfig->DdiConfiguration.DdiPortAConfig == DdiPortAEdp) {
    GpioSetNativePadByFunction (GPIO_FUNCTION_PANEL_AVDD_EN(0), 0);
    GpioSetNativePadByFunction (GPIO_FUNCTION_PANEL_BKLTEN(0), 0);
    GpioSetNativePadByFunction (GPIO_FUNCTION_PANEL_BKLTCTL(0), 0);
    GpioSetNativePadByFunction (GPIO_FUNCTION_DDSP_HPD('A'), 0);
  } else if (GtConfig->DdiConfiguration.DdiPortAConfig == DdiPortAMipiDsi) {
    GpioSetNativePadByFunction(GPIO_FUNCTION_PANEL_BKLTEN(0), 0);
    GpioSetNativePadByFunction(GPIO_FUNCTION_PANEL_BKLTCTL(0), 0);
  } else if (GtConfig->DdiConfiguration.DdiPortAConfig == DdiPortADp) {
    GpioSetNativePadByFunction(GPIO_FUNCTION_DDSP_HPD('A'), 0);
  }

  if (GtConfig->DdiConfiguration.DdiPortBConfig == DdiPortBDp) {
    GpioSetNativePadByFunction (GPIO_FUNCTION_DDSP_HPD('B'), 0);
  } else if (GtConfig->DdiConfiguration.DdiPortBConfig == DdiPortBHdmi) {
    GpioSetNativePadByFunction (GPIO_FUNCTION_DDSP_HPD('B'), 0);
  } else if (GtConfig->DdiConfiguration.DdiPortBConfig == DdiPortBMipiDsi) {
    GpioSetNativePadByFunction(GPIO_FUNCTION_PANEL_TE_EN(0), 0);
    GpioSetNativePadByFunction(GPIO_FUNCTION_PANEL_VIO_EN(0), 0);
    GpioSetNativePadByFunction(GPIO_FUNCTION_PANEL_BKLTEN(0), 0);
    GpioSetNativePadByFunction(GPIO_FUNCTION_PANEL_BKLTCTL(0), 0);
    GpioSetNativePadByFunction(GPIO_FUNCTION_PANEL_RESET(0), 0);
  }

  if (GtConfig->DdiConfiguration.DdiPortCConfig == DdiPortCHdmi) {
    GpioSetNativePadByFunction (GPIO_FUNCTION_DDSP_HPD('C'), 0);
  } else if (GtConfig->DdiConfiguration.DdiPortCConfig == DdiPortCDp) {
    GpioSetNativePadByFunction (GPIO_FUNCTION_DDSP_HPD('C'), 0);
  }
  ///
  /// Enable DDSP_HPD pins for DP HotPlug
  ///
  if (GtConfig->DdiConfiguration.DdiPortBHpd) {
    GpioSetNativePadByFunction (GPIO_FUNCTION_DDSP_HPD('B'), 0);
  }
  if (GtConfig->DdiConfiguration.DdiPortCHpd) {
    GpioSetNativePadByFunction (GPIO_FUNCTION_DDSP_HPD('C'), 0);
  }
  if (GtConfig->DdiConfiguration.DdiPort1Hpd) {
    GpioSetNativePadByFunction (GPIO_FUNCTION_DDSP_HPD(1), 0);
  }
  if (GtConfig->DdiConfiguration.DdiPort2Hpd) {
    GpioSetNativePadByFunction (GPIO_FUNCTION_DDSP_HPD(2), 0);
  }
  if (GtConfig->DdiConfiguration.DdiPort3Hpd) {
    GpioSetNativePadByFunction (GPIO_FUNCTION_DDSP_HPD(3), 0);
  }
  if (GtConfig->DdiConfiguration.DdiPort4Hpd) {
    GpioSetNativePadByFunction (GPIO_FUNCTION_DDSP_HPD(4), 0);
  }

  ///
  /// Enable DDP CTRLCLK and CTRLDATA pins OR TBT RX and TX pins
  ///
  //
  // DDI Port B
  //
  if (GtConfig->DdiConfiguration.DdiPortBDdc == DdiDdcEnable) {
    GpioEnableDpInterface (GpioDdpB);
  }
  //
  // DDI Port C
  //
  if (GtConfig->DdiConfiguration.DdiPortCDdc == DdiDdcEnable) {
    GpioEnableDpInterface (GpioDdpC);
  }
  //
  // DDI Port 1
  //
  if (GtConfig->DdiConfiguration.DdiPort1Ddc == DdiDdcEnable) {
    GpioEnableDpInterface (GpioDdp1);
  }
  //
  // DDI Port 2
  //
  if (GtConfig->DdiConfiguration.DdiPort2Ddc == DdiDdcEnable) {
    GpioEnableDpInterface (GpioDdp2);
  }
  //
  // DDI Port 3
  //
  if (GtConfig->DdiConfiguration.DdiPort3Ddc == DdiDdcEnable) {
    GpioEnableDpInterface (GpioDdp3);
  }
  //
  // DDI Port 4
  //
  if (GtConfig->DdiConfiguration.DdiPort4Ddc == DdiDdcEnable) {
    GpioEnableDpInterface (GpioDdp4);
  }

  ///
  /// Install PPI to enable Gfx PEIM
  ///
  if ((GtConfig->PeiGraphicsPeimInit == 1) && (GtConfig->GraphicsConfigPtr != NULL)) {
    Status = PeiServicesInstallPpi (&mEnablePeiGraphicsPpi);
    ASSERT_EFI_ERROR (Status);
  }

  DEBUG ((DEBUG_INFO, "DisplayNativeGpioInit: End \n"));

  return EFI_SUCCESS;
}