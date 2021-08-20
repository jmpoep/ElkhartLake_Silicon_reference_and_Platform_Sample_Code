/** @file
  This files contains CNVi devices configuration

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2018 Intel Corporation.

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

#include <Ppi/SiPolicy.h>
#include <PchResetPlatformSpecific.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PchPcrLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/CnviLib.h>
#include <Library/PmcPrivateLib.h>
#include <Library/GpioPrivateLib.h>
#include <Library/GpioNativePads.h>
#include <Library/PsfLib.h>
#include <Library/PeiItssLib.h>
#include "PeiCnviLibHelper.h"
#include <Library/SiScheduleResetLib.h>
#include <IndustryStandard/Pci30.h>
#include <Register/PchRegs.h>
#include <Register/CnviRegs.h>
#include <CnviConfigHob.h>
#include <Library/HobLib.h>

/**
  Schedules Global Reset required to change CNVi static power gating state.
**/
STATIC
VOID
CnviPerformGlobalReset (
  VOID
  )
{
  PCH_RESET_DATA             ResetData;

  DEBUG ((DEBUG_INFO, "CnviPerformGlobalReset()\n"));

  CopyMem (&ResetData.Guid, &gPchGlobalResetGuid, sizeof (EFI_GUID));
  StrCpyS (ResetData.Description, PCH_RESET_DATA_STRING_MAX_LENGTH, PCH_PLATFORM_SPECIFIC_RESET_STRING);
  SiScheduleResetSetType (EfiResetPlatformSpecific, &ResetData);
}

/**
  Enable CNVi

  @retval EFI_SUCCESS    CNVi is enabled
  @retval EFI_NOT_FOUND  CNVi is not present
**/
STATIC
EFI_STATUS
CnviEnable (
  VOID
  )
{
  //
  // If CNVi is static power gated but has not been fused out, clear the static power gate bit and do a reset.
  //
  if (PmcIsCnviFunctionDisabled ()) {
    DEBUG ((DEBUG_INFO, "CNVi WiFi found disabled and requested to be enabled - clear PG bit in PMC and issue reset!\n"));
    //
    // CNVi PMC function enable
    //
    PmcEnableCnvi ();

    //
    // Schedule reset for enabling to take effect
    //
    CnviPerformGlobalReset ();
  }

  //
  // Check if CNVi WiFi PCI function is visible - that means CNVi is the active Connectivity Solution
  //
  if (!CnviIsPresent ()) {
    DEBUG ((DEBUG_INFO, "CNVi WiFi function not found.\n"));

    // Clear BTEN to disable UTMI2UTMI bridge if CNVi is not present.
    GpioSetCnviBtEnState (0);

    return EFI_NOT_FOUND;
  }
  return EFI_SUCCESS;
}

/**
  Disable CNVi
**/
STATIC
VOID
CnviDisable (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "PchDisableCnvi() - Start\n"));

  // Clear BTEN to disable UTMI2UTMI bridge if CNVi is disabled.
  GpioSetCnviBtEnState (0);

  //
  // Check if CNVi is static power gated
  //
  if (PmcIsCnviFunctionDisabled ()) {
    DEBUG ((DEBUG_INFO, "CNVi found already static power gated\n"));
    return;
  }
  //
  // Perform PSF function disable
  //
  DEBUG ((DEBUG_INFO, "Disable Cnvi Wifi on PSF\n"));
  PsfDisableCnviWifiDevice ();

  //
  // CNVi PMC function disable
  //
  DEBUG ((DEBUG_INFO, "CNVi WiFi found enabled and requested to be disabled - set PG bit and issue reset!\n"));
  PmcStaticDisableCnvi ();

  //
  // Schedule reset for disabling to take effect
  //
  CnviPerformGlobalReset ();
}

/**
  Configure CNVi BT

  @param[in] CnviConfig The CNVI_CONFIG policy instance
**/
STATIC
VOID
CnviConfigureBt (
  IN CNVI_CONFIG *CnviConfig
  )
{
  if (CnviConfig->BtCore) {
    // BT over USB
    DEBUG ((DEBUG_INFO, "Set BT interface: USB\n"));
    GpioSetCnviBtInterface (GpioCnviBtIfUsb);
    GpioConfigureCnviBtUartConnection (GpioCnviBtUartNotConnected);
    // Configure BT I2S pins for cAVS connection
    if (CnviConfig->BtAudioOffload) {
      GpioConfigureCnviBtI2sConnection (GpioCnviBtI2sToSsp2);
      DEBUG ((DEBUG_INFO, "Configure BT I2S to SSP2\n"));
    } else {
      GpioConfigureCnviBtI2sConnection (GpioCnviBtI2sNotConnected);
    }

    // Enable BT core
    DEBUG ((DEBUG_INFO, "Enable BT core\n"));
    GpioSetCnviBtEnState (1);
  } else {
    //
    // Configure BT related pins to not connected
    //
    GpioConfigureCnviBtUartConnection (GpioCnviBtUartNotConnected);
    GpioConfigureCnviBtI2sConnection (GpioCnviBtI2sNotConnected);
    //
    // Disable BT core
    //
    DEBUG ((DEBUG_INFO, "Disable BT core\n"));
    GpioSetCnviBtEnState (0);
  }
}

/**
  Configures CNVi WiFi IRQ assignment.

  @param[in] SiPolicy   The SI Policy PPI instance
**/
VOID
CnviWifiIntSet (
  IN  SI_POLICY_PPI     *SiPolicy
  )
{
  UINT8    InterruptPin;
  UINT8    Irq;

  ItssGetDevIntConfig (
    SiPolicy,
    PCI_DEVICE_NUMBER_PCH_CNVI_WIFI,
    PCI_FUNCTION_NUMBER_PCH_CNVI_WIFI,
    &InterruptPin,
    &Irq
    );

  //
  // Set Interrupt Pin
  //
  PciSegmentWrite8 (
    PCI_SEGMENT_LIB_ADDRESS (
      DEFAULT_PCI_SEGMENT_NUMBER_PCH,
      DEFAULT_PCI_BUS_NUMBER_PCH,
      PCI_DEVICE_NUMBER_PCH_CNVI_WIFI,
      PCI_FUNCTION_NUMBER_PCH_CNVI_WIFI,
      PCI_INT_PIN_OFFSET),
    InterruptPin);

  //
  // Assign interrupt number
  //
  PchPcrAndThenOr32 (
    PID_CNVI,
    R_CNVI_PCR_WIFI_WIDGET_CONTROL,
    (UINT32)~B_CNVI_PCR_WIFI_WIDGET_CONTROL_MEM_INT,
    Irq
    );
}

/**
  The function update CNVi config HOB

  @param[in] CnviConfig The CNVI_CONFIG policy instance
**/
VOID
BuildCnviConfigHob (
  IN CNVI_CONFIG *CnviConfig
  )
{
  CNVI_CONFIG_HOB *CnviConfigHob;

  CnviConfigHob = BuildGuidHob (&gCnviConfigHobGuid, sizeof (CNVI_CONFIG_HOB));
  ASSERT (CnviConfigHob != 0);
  if (CnviConfigHob == NULL) {
    return;
  }

  CnviConfigHob->Mode           = CnviConfig->Mode;
  CnviConfigHob->BtCore         = CnviConfig->BtCore;
  CnviConfigHob->BtAudioOffload = CnviConfig->BtAudioOffload;
}

/**
  Initialize CNVi devices according to Silicon Policy PPI

  @param[in] SiPolicy The SI Policy PPI instance
**/
VOID
CnviInit (
  IN SI_POLICY_PPI *SiPolicy
  )
{
  UINT32      Status;
  UINT64      CnviWifiBase;
  UINT16      Data16;
  CNVI_CONFIG *CnviConfig;

  DEBUG ((DEBUG_INFO, "CnviInit() - Start\n"));

  Status = GetConfigBlock ((VOID *) SiPolicy, &gCnviConfigGuid, (VOID *) &CnviConfig);
  ASSERT_EFI_ERROR (Status);

  if (!PmcIsCnviSupported ()) {
    //
    // PSF Function Disable already set in PchEarlyDisabledDeviceHandling()
    //
    DEBUG ((DEBUG_INFO, "CNVi has been fused out\n"));
    return;
  }

  if (CnviConfig->Mode == CnviModeAuto) {
    //
    // BIOS menu option configured to [Auto] - Check if CNVi is enabled
    //
    if (CnviEnable () == EFI_SUCCESS) {
      DEBUG ((DEBUG_INFO, "CNVi discovered\n"));
      //
      // CNVi detected. Configure CNVi components.
      //
      GpioConfigureCnviCrfConnection ();
      GpioSetNativePadByFunction (GPIO_FUNCTION_CNVI_RF_RESET, CnviConfig->PinMux.RfReset);
      GpioSetNativePadByFunction (GPIO_FUNCTION_CNVI_CLKREQ, CnviConfig->PinMux.Clkreq);

      //
      // Configure sideband communication channel for WiFi
      //
      GpioConfigureCnviMfUart1Connection (GpioCnviMfUart1ToPseUart0);

      // Miscellaneous configuration
      CnviConfigureMisc (CnviConfig);

      CnviWifiBase = PCI_SEGMENT_LIB_ADDRESS (
                       DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                       DEFAULT_PCI_BUS_NUMBER_PCH,
                       PCI_DEVICE_NUMBER_PCH_CNVI_WIFI,
                       PCI_FUNCTION_NUMBER_PCH_CNVI_WIFI,
                       0
                       );
      Data16 = PciSegmentRead16 (CnviWifiBase + R_CNVI_CFG_WIFI_GIO_DEV_CAP_2);
      if (Data16 & B_CNVI_CFG_WIFI_GIO_DEV_CAP_2_LTR_MEC_SUP) {
        PciSegmentOr16 (CnviWifiBase + R_CNVI_CFG_WIFI_GIO_DEV_2, B_CNVI_CFG_WIFI_GIO_DEV_2_LTR_MEC_EN);
      }
      //
      // Configure BT
      //
      CnviConfigureBt (CnviConfig);

      //
      // Configure CNVi interrupt
      //
      CnviWifiIntSet (SiPolicy);
    }
  } else {
    //
    // Disable CNVi
    //
    CnviDisable ();
  }

  BuildCnviConfigHob (CnviConfig);

  DEBUG ((DEBUG_INFO, "CnviInit() - End\n"));
}
