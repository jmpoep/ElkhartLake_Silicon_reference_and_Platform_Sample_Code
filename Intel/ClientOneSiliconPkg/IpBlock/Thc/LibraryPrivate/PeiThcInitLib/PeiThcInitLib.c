/** @file
  Initializes THC Devices in PEI

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/ThcLib.h>
#include <Library/GpioLib.h>
#include <Library/PeiItssLib.h>
#include <Library/PsfLib.h>
#include <Library/GpioPrivateLib.h>
#include <Library/GpioNativePads.h>
#include <Register/PchRegs.h>
#include <Register/ThcRegs.h>
#include <Ppi/SiPolicy.h>
#include <IndustryStandard/Pci30.h>

/**
  Disables THC

  @param[in] ThcNumber           Touch Controller Number

**/
VOID
STATIC
ThcDisableController (
  IN UINT8                ThcNumber
  )
{
  PciSegmentOr32 (ThcGetPciConfigSpace (ThcNumber) + R_THC_CFG_PMD_PMCSRBSE_PMCSR, V_THC_CFG_PMD_PMCSRBSE_PMCSR_PWRST_D3);
  PsfDisableThcDevice (ThcNumber);
}

/**
  Configures GPIO in Native Mode for THC

  @param[in] SpiIndex            SPI Index
  @param[in] IntPinMuxing        Each GPIO SPIx INTB Pin has different muxing options
                                 refer to GPIO_*_MUXING_THC_SPIx_*

**/
VOID
STATIC
ThcSetSpiGpio (
  IN UINT32               SpiIndex,
  IN GPIO_NATIVE_PAD      IntPinMuxing
  )
{
  UINT32                      Index;
  GPIO_PAD_NATIVE_FUNCTION    ThcPad;

  ThcPad = GpioGetThcSpiClk (SpiIndex);
  GpioSetPadMode (ThcPad.Pad, ThcPad.Mode);

  ThcPad = GpioGetThcSpiCs (SpiIndex);
  GpioSetPadMode (ThcPad.Pad, ThcPad.Mode);

  ThcPad = GpioGetThcSpiReset (SpiIndex);
  GpioSetPadMode (ThcPad.Pad, ThcPad.Mode);

  for (Index = 0; Index <= 3; Index++) {
    ThcPad = GpioGetThcSpiIo (SpiIndex, Index);
    GpioSetPadMode (ThcPad.Pad, ThcPad.Mode);
  }

  GpioSetInputInversion (GpioGetNativePadByFunction (GPIO_FUNCTION_THC_SPI_INT(SpiIndex)), 0x0);

  GpioSetNativePadByFunction (GPIO_FUNCTION_THC_SPI_INT(SpiIndex), IntPinMuxing);

  if (IsPchLp ()) {
    GpioSetNativePadByFunction (GPIO_FUNCTION_THC_CLK_LOOPBACK(SpiIndex), 0x0);
  }
}

/**
  Configures THC PM Ctrl D0i2 Entry Timer

  @param[in] PortId           THCn SB Port Id
  @param[in] D0i2EntryTimer   D0i2 Entry Timer value

**/
VOID
STATIC
ThcPmCtrlD0i2EntryTimer (
  IN PCH_SBI_PID         PortId,
  IN UINT32              D0i2EntryTimer

  )
{
  UINT32 DataOr32 = 0x0;

  DataOr32 |= (D0i2EntryTimer << N_THC_PCR_SB_PM_CTRL_D0I2_ENTRY_TIMER);
  PchPcrAndThenOr32 (PortId, R_THC_PCR_SB_PM_CTRL, (UINT32) ~(B_THC_PCR_SB_PM_CTRL_D0I2_ENTRY_TIMER), DataOr32);
}


/**
  Configures THC Port

  @param[in] Port           THC Port
  @param[in] SiPolicy       Policy

**/
VOID
STATIC
ThcConfigurePort (
  IN THC_PORT            Port,
  IN SI_POLICY_PPI       *SiPolicy
  )
{
  UINT64       PciBase;
  UINT32       TempMemBase;
  UINT8        InterruptPin;
  UINT8        ThcNum;

  DEBUG ((DEBUG_INFO, "ThcConfigurePort Entry \n"));
  if (Port.Assignment == ThcAssignmentThc0) {
    ThcNum = 0;
  } else if (Port.Assignment == ThcAssignmentThc1) {
    ThcNum = 1;
  } else {
    DEBUG ((DEBUG_ERROR, "ThcConfigurePort returning as Port.Assignment=%d is not ThcAssignmentThc0 or ThcAssignmentThc1  \n", Port.Assignment));
    return;
  }

  //
  // Configure Gpio
  //
  ThcSetSpiGpio (ThcNum, Port.InterruptPinMuxing);

  //
  // Configure Interrupts
  //
  InterruptPin = ItssGetDevIntPin (SiPolicy, ThcGetDeviceNumber (ThcNum), ThcGetFunctionNumber (ThcNum));
  PciBase      = ThcGetPciConfigSpace (ThcNum);
  PciSegmentWrite8 (PciBase + PCI_INT_PIN_OFFSET, InterruptPin);

  //
  // Set the THC PCI Config Power Control Enable register D3HE bit
  //
  PciSegmentOr32 (PciBase + R_THC_CFG_PCE, B_THC_CFG_PCE_D3HE);

  //
  // Enable Memory decoding
  //
  TempMemBase  = PcdGet32 (PcdSiliconInitTempMemBaseAddr);

  PciSegmentWrite32 (PciBase + PCI_BASE_ADDRESSREG_OFFSET, TempMemBase);
  PciSegmentWrite32 (PciBase + PCI_BASE_ADDRESSREG_OFFSET + 0x4, 0);
  PciSegmentOr16 (PciBase + PCI_COMMAND_OFFSET, (UINT16) EFI_PCI_COMMAND_MEMORY_SPACE);

  //
  // Set Port Supported
  //
  MmioOr32 (TempMemBase + R_THC_MEM_PORT_CONTROL, B_THC_MEM_PORT_CONTROL_PORT_SUPPORTED);

  //
  // Lock Port Control Register
  //
  MmioOr32 (TempMemBase + R_THC_MEM_PORT_CONTROL, B_THC_MEM_PORT_CONTROL_BIOS_LOCK_EN);

  //
  // Disable Memory decoding and put THC in D3
  //
  PciSegmentAnd16 (PciBase + PCI_COMMAND_OFFSET, (UINT16) (~EFI_PCI_COMMAND_MEMORY_SPACE));
  PciSegmentOr32 (PciBase + R_THC_CFG_PMD_PMCSRBSE_PMCSR, V_THC_CFG_PMD_PMCSRBSE_PMCSR_PWRST_D3);
  PciSegmentWrite32 (PciBase + PCI_BASE_ADDRESSREG_OFFSET, 0);
  DEBUG ((DEBUG_INFO, "ThcConfigurePort Exit \n"));
}

/**
  Validates THC Port Configuration

  @param[in] Port0             Port 0 Policy
  @param[in] Port1             Port 1 Policy
  @retval TRUE                 Validation Passed
          FALSE                Validation Failed
**/
BOOLEAN
STATIC
ThcPolicyValidate (
  IN THC_PORT    Port0,
  IN THC_PORT    Port1
  )
{
  if (Port0.Assignment >= ThcAssignmentThc1 ||
      Port1.Assignment == ThcAssignmentThc0 ||
      Port1.Assignment > ThcAssignmentThc1) {
    DEBUG ((DEBUG_ERROR, "Wrong Thc Assignment settigns in policy!\n"));
    DEBUG ((DEBUG_ERROR, "Port0 Assignment: %d \n", Port0.Assignment));
    DEBUG ((DEBUG_ERROR, "Port1 Assignment: %d \n", Port1.Assignment));
    ASSERT (FALSE);
    return FALSE;
  }

  return TRUE;
}

/**
  Initialize the Intel Touch Host Controller

  @param[in] SiPolicy             Policy

**/
VOID
ThcInit (
  IN SI_POLICY_PPI      *SiPolicy
  )
{
  EFI_STATUS     Status;
  THC_CONFIG     *ThcConfig;

  DEBUG ((DEBUG_INFO, "ThcInit() Start\n"));

  Status = GetConfigBlock ((VOID *) SiPolicy, &gThcConfigGuid, (VOID *) &ThcConfig);
  ASSERT_EFI_ERROR (Status);


  //
  // Validate THC policy
  //
  if (ThcConfig->ThcPort[0].Assignment > ThcAssignmentNone) {
    if (!ThcPolicyValidate (ThcConfig->ThcPort[0], ThcConfig->ThcPort[1])) {
      DEBUG ((DEBUG_ERROR, "THC Policy Validation Failed! Disabling both Controllers\n"));
      ThcDisableController (0);
      ThcDisableController (1);
      DEBUG ((DEBUG_INFO, "ThcInit() End\n"));
      return;
    }
  }

  //
  // Initialize THC only when below conditions are met:
  // 1. Port 0 is assigned to THC 0
  // 2. Gpio for Port 0 are available for BIOS to change
  // 3. THC0 Enabled
  //
  if ((ThcConfig->ThcPort[0].Assignment == ThcAssignmentThc0) &&
       ThcIsSupported () &&
       ThcIsEnabled (0)) {
    //
    // Configuring the THC SB PM CTRL register's D0i2 Entry Timer value as 10us (0x3)
    //
    ThcPmCtrlD0i2EntryTimer (PID_THC0, V_THC_PCR_SB_PM_CTRL_D0I2_ENTRY_TIMER_10US);
    ThcPmCtrlD0i2EntryTimer (PID_THC1, V_THC_PCR_SB_PM_CTRL_D0I2_ENTRY_TIMER_10US);
    ThcConfigurePort (ThcConfig->ThcPort[0], SiPolicy);
    ThcConfigurePort (ThcConfig->ThcPort[1], SiPolicy);
    if (ThcConfig->ThcPort[1].Assignment == ThcAssignmentNone) {
      ThcDisableController (1);
    }
  } else {
    ThcDisableController (0);
    ThcDisableController (1);
  }

  DEBUG ((DEBUG_INFO, "ThcInit() End\n"));
}

