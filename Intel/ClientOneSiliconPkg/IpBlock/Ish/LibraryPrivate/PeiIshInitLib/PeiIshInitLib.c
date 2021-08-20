/** @file
  Initializes Integrated Sensor Hub Controller (ISH 3.0).

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2018 Intel Corporation.

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

#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PmcLib.h>
#include <Library/PchPcrLib.h>
#include <PchResetPlatformSpecific.h>
#include <Ppi/SiPolicy.h>
#include <Library/GpioPrivateLib.h>
#include <Library/GpioNativePads.h>
#include <Library/PeiIshLib.h>
#include <Library/PeiIshInitLib.h>
#include <Library/IshInfoLib.h>
#include <Library/SiScheduleResetLib.h>
#include <Library/PeiPmcPrivateLib.h>
#include <Library/PmcPrivateLib.h>
#include <Library/PsfLib.h>
#include <Library/PeiItssLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PeiServicesLib.h>

#include <Register/PchRegs.h>
#include <Register/IshRegs.h>

#include "PeiIshInitLibInternal.h"

/**
  Configures ISH-related GPIO pins to ISH native mode
**/
STATIC
VOID
IshSetGpio (
  IN  SI_POLICY_PPI    *SiPolicy
  )
{
  EFI_STATUS           Status;
  ISH_CONFIG       *IshConfig;
  UINT32               Index1;
  UINT32               Index2;
  UINT32               GpNumber;


  DEBUG ((DEBUG_INFO, "IshSetGpio() Start\n"));

  Status = GetConfigBlock ((VOID *) SiPolicy, &gIshConfigGuid, (VOID *) &IshConfig);
  ASSERT_EFI_ERROR (Status);

  for (Index1 = 0; Index1 < GetPchMaxIshSpiControllersNum (); Index1++) {
    if (IshConfig->Spi[Index1].Enable) {
      DEBUG ((DEBUG_INFO, "ISH SPI_%d pins set to Native Mode\n", Index1));
      GpioSetNativePadByFunction (GPIO_FUNCTION_ISH_SPI_MOSI(Index1), IshConfig->Spi[Index1].PinConfig.Mosi.PinMux);
      GpioSetNativePadByFunction (GPIO_FUNCTION_ISH_SPI_MISO(Index1), IshConfig->Spi[Index1].PinConfig.Miso.PinMux);
      GpioSetNativePadByFunction (GPIO_FUNCTION_ISH_SPI_CLK(Index1), IshConfig->Spi[Index1].PinConfig.Clk.PinMux);
      for (Index2 = 0; Index2 < GetPchMaxIshSpiControllerCsPinsNum (); Index2++) {
        if (IshConfig->Spi[Index1].CsEnable[Index2]) {
          GpioSetNativePadByFunction (GPIO_FUNCTION_ISH_SPI_CS(Index1, Index2), IshConfig->Spi[Index1].PinConfig.Cs[Index2].PinMux);
        }
      }
    }
  }

  for (Index1 = 0; Index1 < GetPchMaxIshUartControllersNum (); Index1++) {
    if (IshConfig->Uart[Index1].Enable) {
      DEBUG ((DEBUG_INFO, "ISH UART%d pins set to Native Mode\n", Index1));
      GpioSetNativePadByFunction (GPIO_FUNCTION_ISH_UART_RX (Index1), IshConfig->Uart[Index1].PinConfig.Rx.PinMux);
      GpioSetNativePadByFunction (GPIO_FUNCTION_ISH_UART_TX (Index1), IshConfig->Uart[Index1].PinConfig.Tx.PinMux);
      GpioSetNativePadByFunction (GPIO_FUNCTION_ISH_UART_RTS (Index1), IshConfig->Uart[Index1].PinConfig.Rts.PinMux);
      GpioSetNativePadByFunction (GPIO_FUNCTION_ISH_UART_CTS (Index1), IshConfig->Uart[Index1].PinConfig.Cts.PinMux);
    }
  }

  for (Index1 = 0; Index1 < GetPchMaxIshI2cControllersNum (); Index1++) {
    if (IshConfig->I2c[Index1].Enable) {
      DEBUG ((DEBUG_INFO, "ISH I2C%d pins set to Native Mode\n", Index1));
      GpioSetNativePadByFunction (GPIO_FUNCTION_ISH_I2C_SDA (Index1), IshConfig->I2c[Index1].PinConfig.Sda.PinMux);
      GpioSetNativePadByFunction (GPIO_FUNCTION_ISH_I2C_SCL (Index1), IshConfig->I2c[Index1].PinConfig.Scl.PinMux);
    }
  }

  for (Index1 = 0; Index1 < GetPchMaxIshGpNum (); Index1++) {
    if (IshConfig->Gp[Index1].Enable) {
      GpNumber = IshGetGpNumber (Index1);
      DEBUG ((DEBUG_INFO, "ISH GP_%d pin set to Native Mode\n", GpNumber));
      GpioSetNativePadByFunction (GPIO_FUNCTION_ISH_GP (GpNumber), IshConfig->Gp[Index1].PinConfig.PinMux);
    }
  }
}

/**
  Schedules Global Reset required to change ISH static power gating state.
**/
STATIC
VOID
IshPerformGlobalReset (
  VOID
  )
{
  PCH_RESET_DATA             ResetData;

  DEBUG((DEBUG_INFO, "IshPerformGlobalReset()\n"));

  CopyMem (&ResetData.Guid, &gPchGlobalResetGuid, sizeof (EFI_GUID));
  StrCpyS (ResetData.Description, PCH_RESET_DATA_STRING_MAX_LENGTH, PCH_PLATFORM_SPECIFIC_RESET_STRING);
  SiScheduleResetSetType (EfiResetPlatformSpecific, &ResetData);
}

/**
  Configures Integrated Sensor Hub (ISH) Controller

  @param[in] SiPolicy
**/
STATIC
VOID
IshConfigure (
  IN  SI_POLICY_PPI   *SiPolicy
  )
{
  UINT64    IshPciBase;
  UINT8     InterruptPin;
  UINT8     Irq;
  UINT32    Data32Or;
  UINT32    Data32And;
  UINT8     IshDeviceNumber;
  UINT8     IshFunctionNumber;

  DEBUG ((DEBUG_INFO, "IshConfigure() Start\n"));

  //
  // Check if ISH is disabled by static PG
  //
  if (PmcIsIshFunctionDisabled ()) {
    DEBUG ((DEBUG_INFO, "ISH Static PG disabled - Enable and issue reset!\n"));

    //
    // Enable ISH controller by disabling static PG
    //
    PmcEnableIsh ();

    IshPerformGlobalReset ();

    return;
  }

  DEBUG ((DEBUG_INFO, "ISH: BAR1 - Shadowed PCI Config Space Disabled\n"));
  //
  // Configure in PCI mode - disable BAR1 (Shadowed PCI)
  // Set PCICFGCTR.BAR1_DISABLE (PCR[ISHBR] + 200h[7] = 1b)
  // Read back is needed to enforce the sideband and primary ordering.
  //
  PchPcrAndThenOr32WithReadback (
    PID_ISHBR,
    R_ISH_PCR_PCICFGCTRL,
    (UINT32) ~0,
    B_ISH_PCR_PCICFGCTRL_BAR1DIS
    );

  //
  // Disable ISH BAR1 in PSF
  //
  PsfDisableIshBar1 ();

  //
  // Power management programming
  // Set PMCTL = 3Fh (PCR[ISHBR] + 1D0h[5:0] = 111111b)
  //
  PchPcrAndThenOr32 (
    PID_ISHBR,
    R_ISH_PCR_PMCTL,
    (UINT32) ~(0),
    (BIT5 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0)
    );

  //
  // Set RSCTRL.OTHER_RS_US_EN (PCR[ISHBR] + 300h[1] = 1b)
  //
  PchPcrAndThenOr32 (
    PID_ISHBR,
    R_ISH_PCR_RSCTRL,
    (UINT32) ~0,
    B_ISH_PCR_RSCTRL_OTHER_RS_US_EN
    );

  IshDeviceNumber = IshGetDeviceNumber ();
  IshFunctionNumber = IshGetFunctionNumber ();

  IshPciBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 IshDeviceNumber,
                 IshFunctionNumber,
                 0
                 );

  //
  // Set D0Idle Max Power On Latency register (RWO)
  //
  PciSegmentOr16 (IshPciBase + R_ISH_CFG_D0I3_MAX_PW_ON_LATENCY, 0);

  //
  // Set Hardware Autonomous Enable to allow ISH to independently enter/exit IPAPG states
  // Set PCE.HAE (PCI[ISH] + A2h[5] = 1b)
  //
  PciSegmentOr16 (IshPciBase + R_ISH_CFG_PCE, B_ISH_CFG_PCE_HAE);

  IshSetGpio (SiPolicy);

  ///
  /// Configure ISH interrupt
  ///
  ItssGetDevIntConfig (
    SiPolicy,
    IshDeviceNumber,
    IshFunctionNumber,
    &InterruptPin,
    &Irq
    );

  Data32Or =  (UINT32) ((InterruptPin << N_ISH_PCR_PCICFGCTRL_IPIN1) |
                        (Irq << N_ISH_PCR_PCICFGCTRL_PCI_IRQ));
  Data32And =~(UINT32) (B_ISH_PCR_PCICFGCTRL_PCI_IRQ | B_ISH_PCR_PCICFGCTRL_ACPI_IRQ | B_ISH_PCR_PCICFGCTRL_IPIN1);

  PchPcrAndThenOr32 (PID_ISHBR, R_ISH_PCR_PCICFGCTRL, Data32And, Data32Or);

  DEBUG ((DEBUG_INFO, "IshConfigure() End\n"));
}

/**
  Sets Integrated Sensor Hub (ISH) PSF Function Disable
**/
STATIC
VOID
IshDisable (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "IshDisable() Start\n"));

  PsfDisableIshDevice ();

  //
  // Check if ISH is static power gated
  //
  if (PmcIsIshFunctionDisabled ()) {
    DEBUG ((DEBUG_INFO, "ISH found already static power gated\n"));
    return;
  }

  //
  // Before modifying ISH Disable bit, make sure it's not locked.
  //
  if (!PmcIsFunctionDisableConfigLocked ()) {
    //
    // Statically disable ISH Controller
    //
    DEBUG ((DEBUG_INFO, "ISH found enabled and requested to be disabled - set PG bit and issue reset!\n"));
    PmcStaticDisableIsh ();

    //
    // Perform reset for disabling to take effect
    //
    IshPerformGlobalReset ();
  } else {
    DEBUG ((DEBUG_ERROR, "ISH function disable bit is locked!\n"));
  }

  DEBUG ((DEBUG_INFO, "IshDisable() End \n"));
}

/**
  Initialize Integrated Sensor Hub (ISH)

  @param[in] SiPolicy
**/
VOID
IshInit (
  IN  SI_POLICY_PPI    *SiPolicy
  )
{
  DEBUG ((DEBUG_INFO, "IshInit() Start\n"));

  if (!PmcIsIshSupported ()) {
    //
    // PSF Function Disable already set in PchEarlyDisabledDeviceHandling()
    //
    return;
  }

  IshSocInit (SiPolicy);

  if (IsIshEnabled ()) {
    IshConfigure (SiPolicy);
  } else {
    IshDisable ();
  }

  DEBUG ((DEBUG_INFO, "IshInit() End\n"));
}
