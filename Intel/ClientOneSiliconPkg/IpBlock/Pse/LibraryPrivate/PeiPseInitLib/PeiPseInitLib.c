/** @file
  Initializes Programmable Service Engine Controller (PSE).

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2020 Intel Corporation.

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
#include <Library/PeiPseLib.h>
#include <Library/PeiPseInitLib.h>
#include <Library/PseInfoLib.h>
#include <Library/SiScheduleResetLib.h>
#include <Library/PeiPmcPrivateLib.h>
#include <Library/PmcPrivateLib.h>
#include <Library/PchPseIoLib.h>
#include <Library/PsfLib.h>
#include <Library/PeiItssLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PciLib.h>
#include <Library/PchInfoLib.h>
#include <Library/IoLib.h>
#include <Library/CpuPlatformLib.h>

#include <IndustryStandard/Pci30.h>
#include <Register/PchRegs.h>
#include <Register/PseRegs.h>

GLOBAL_REMOVE_IF_UNREFERENCED PSE_CONFIG               *mPseConfig = NULL;

/* Ownership assigned order based on the setup configuration */
GLOBAL_REMOVE_IF_UNREFERENCED DEVICE_OWNERSHIP          DevOwnConfig[] =
{
   {"NONE", 0x2},
   {"PSE",  0x0},
   {"HOST", 0x1},
};

GLOBAL_REMOVE_IF_UNREFERENCED INTR_DELIVERY_ROUTE       IntrDeliverConfig[] =
{
   {"MSI", 0x0},
   {"SB",  0x8},
};

/**
  Configures PSE devices interrupt pin and IRQ assignment

  @param[in]  SiPolicy       Pointer to SI_POLICY_PPI
  @param[in] Controller      PSE IO Controller
**/
VOID
PseIoIntSet (
  IN SI_POLICY_PPI               *SiPolicy,
  IN PCH_PSE_IO_CONTROLLER       Controller
  )
{
  UINT16    Offset;
  UINT32    Data32Or;
  UINT32    Data32And;
  UINT8     DeviceNumber;
  UINT8     FunctionNumber;
  UINT8     InterruptPin;
  UINT8     Irq;
  UINT64    PsePciBase;

  Offset = 0x0;

  DeviceNumber = GetPseIoDeviceNumber (Controller);
  FunctionNumber = GetPseIoFunctionNumber (Controller);

  ///
  /// Get SerialIo controller interrupt configuration
  ///
  ItssGetDevIntConfig (
    SiPolicy,
    DeviceNumber,
    FunctionNumber,
    &InterruptPin,
    &Irq
    );

  //
  // Assign interrupt pin in PCI space for PSE devices
  //
  PsePciBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 DeviceNumber,
                 FunctionNumber,
                 0
                 );
  PciSegmentWrite8 (PsePciBase + PCI_INT_PIN_OFFSET, InterruptPin);

  //
  // Match SerialIo Dxx:Fx with appropriate PCICFGCTRLx register
  //
  Offset = GetPseIoConfigControlOffset (DeviceNumber, FunctionNumber);

  ASSERT (Offset != 0);

  //
  // Set Interrupt Pin and Irq number
  //
  Data32Or  = (UINT32) ((InterruptPin << N_PSE_PCR_PCICFGCTRL_IPIN1) |
                        (Irq << N_PSE_PCR_PCICFGCTRL_PCI_IRQ));
  Data32And =~(UINT32) (B_PSE_PCR_PCICFGCTRL_PCI_IRQ | B_PSE_PCR_PCICFGCTRL_ACPI_IRQ | B_PSE_PCR_PCICFGCTRL_INT_PIN);

  PchPcrAndThenOr32 (PID_PSEBR, Offset, Data32And, Data32Or);
  DEBUG ((DEBUG_INFO, "Configured PSE Irq # %d Interrupt # %d for device 0x%x and function 0x%x\n",
      Irq, InterruptPin, DeviceNumber, FunctionNumber));
  DEBUG ((DEBUG_INFO, "\tPCR port %x, offset %x, DataAnd 0x%x and DataOr 0x%x\n",
     PID_PSEBR, Offset, Data32And, Data32Or));

  DEBUG ((DEBUG_INFO, "\tPerforming a readback on the same port and offset.\n"));
  DEBUG ((DEBUG_INFO, "\tData read: 0x%x\n", PchPcrRead32 (PID_PSEBR, Offset)));
}

/**
  Program TGPIO ownership HOST/PSE/NONE based on the setup config.

  @param[in] MmioBase        Address to be used to access MMIO space
**/
VOID
PseControllerTgpioOwnerShip (
  IN  UINTN   MmioBase
  )
{
  UINT32                Index1;
  UINT32                Data;

  for (Index1 = 0; Index1 < GetPchMaxPseTimedGpioControllersNum (); Index1++) {
    DEBUG ((DEBUG_INFO, "PSE TGPIO%d IP set to %s owned\n", Index1, DevOwnConfig[mPseConfig->TimedGpio[Index1].OwnerShip].Name));

    Data = MmioRead32(MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP2_OFFSET);
    Data = ((Data & (~(V_DEV3_OWNERSHIP_MASK << (S_OWNERSHIP_CTRL * Index1)))) | \
            (DevOwnConfig[mPseConfig->TimedGpio[Index1].OwnerShip].ConfigValue << (S_OWNERSHIP_CTRL * (DEVICE_6_INDEX + Index1))));
    MmioWrite32 (MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP2_OFFSET, Data);

    if (mPseConfig->TimedGpio[Index1].OwnerShip != HOST_OWNED) {
      PsfDisablePseBar1 (PchPseIoIndexTGpio0 + Index1);
      PsfHidePseDevice (PchPseIoIndexTGpio0 + Index1);
    }
  }

  return;
}

/**
  Program I2S ownership HOST/PSE/NONE based on the setup config.

  @param[in] MmioBase        Address to be used to access MMIO space
**/
VOID
PseControllerI2sOwnerShip (
  IN  UINTN   MmioBase
  )
{
  UINT32                Index1;
  UINT32                Data;

  for (Index1 = 0; Index1 < GetPchMaxPseI2sControllersNum (); Index1++) {
    //
    // I2S 0-1 GPIO programming
    //
    if (mPseConfig->I2s[Index1].OwnerShip != NONE_OWNED) {
      DEBUG ((DEBUG_INFO, "PSE I2S%d pins set to Native Mode\n", Index1));
      GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_I2S_RX (Index1), mPseConfig->I2s[Index1].PinMux.Rx);
      GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_I2S_TX (Index1), mPseConfig->I2s[Index1].PinMux.Tx);
      GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_I2S_CLK (Index1), mPseConfig->I2s[Index1].PinMux.Clk);
      GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_I2S_SFRM (Index1), mPseConfig->I2s[Index1].PinMux.Sfrm);
    }

    //
    // I2S 0-1 Ownership programming
    //
    DEBUG ((DEBUG_INFO, "PSE I2S%d IP set to %s owned\n", Index1, DevOwnConfig[mPseConfig->I2s[Index1].OwnerShip].Name));
    if (Index1 == 0) {
      Data = MmioRead32(MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP3_OFFSET);
      Data = ((Data & (~V_DEV7_OWNERSHIP_MASK)) | (DevOwnConfig[mPseConfig->I2s[Index1].OwnerShip].ConfigValue << (S_OWNERSHIP_CTRL * DEVICE_7_INDEX)));
      MmioWrite32 (MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP3_OFFSET, Data);
    }

    if (Index1 == 1) {
      Data = MmioRead32(MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP4_OFFSET);
      Data = ((Data & (~V_DEV0_OWNERSHIP_MASK)) | (DevOwnConfig[mPseConfig->I2s[Index1].OwnerShip].ConfigValue << (S_OWNERSHIP_CTRL * DEVICE_0_INDEX)));
      MmioWrite32 (MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP4_OFFSET, Data);
    }

    //
    // I2S 0-1 Interrupt programming
    //
    if (mPseConfig->I2s[Index1].OwnerShip != NONE_OWNED) {
      DEBUG ((DEBUG_INFO, "PSE I2S%d interrupt set to %s\n", Index1, IntrDeliverConfig[mPseConfig->I2s[Index1].SbInterruptEnable].Name)); 

      if (Index1 == 0) {
        Data = MmioRead32(MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP3_OFFSET);
        Data = ((Data & (~V_DEV7_INTERRUPT_MASK)) | (IntrDeliverConfig[mPseConfig->I2s[Index1].SbInterruptEnable].ConfigValue << (S_OWNERSHIP_CTRL * DEVICE_7_INDEX)));
        MmioWrite32 (MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP3_OFFSET, Data);
      }

      if (Index1 == 1) {
        Data = MmioRead32(MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP4_OFFSET);
        Data = ((Data & (~V_DEV0_INTERRUPT_MASK)) | (IntrDeliverConfig[mPseConfig->I2s[Index1].SbInterruptEnable].ConfigValue << (S_OWNERSHIP_CTRL * DEVICE_0_INDEX)));
        MmioWrite32 (MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP4_OFFSET, Data);
      }
    }

    if (mPseConfig->I2s[Index1].OwnerShip != HOST_OWNED) {
      PsfDisablePseBar1 (PchPseIoIndexI2S0 + Index1);
      PsfHidePseDevice (PchPseIoIndexI2S0 + Index1);
    }
  }
}

/**
  Program PWM ownership HOST/PSE/NONE based on the setup config.

  @param[in] MmioBase        Address to be used to access MMIO space
**/
VOID
PseControllerPwmOwnerShip (
  IN  UINTN   MmioBase
  )
{
  UINT32                Index1;
  UINT32                Data;

  //
  // PWM GPIO programming
  //
  if (mPseConfig->Pwm.OwnerShip != NONE_OWNED) {
    for (Index1 = 0; Index1 < GetPchMaxPsePwmControllerPinsNum (); Index1++) {
      DEBUG ((DEBUG_INFO, "PSE PWM_%d pin set to Native Mode\n", Index1));
      if (mPseConfig->Pwm.PinEnable[Index1]){
        GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_PWM (Index1), mPseConfig->Pwm.PinMux.Pin[Index1]);
      }
    }
  }

  //
  // PWM Ownership programming
  //
  DEBUG ((DEBUG_INFO, "PSE PWM IP set to %s owned\n", DevOwnConfig[mPseConfig->Pwm.OwnerShip].Name));
  Data = MmioRead32(MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP4_OFFSET);
  Data = ((Data & (~V_DEV1_OWNERSHIP_MASK)) | (DevOwnConfig[mPseConfig->Pwm.OwnerShip].ConfigValue << (S_OWNERSHIP_CTRL * DEVICE_1_INDEX)));
  MmioWrite32 (MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP4_OFFSET, Data);

  //
  // PWM Interrupt programming
  //
  if (mPseConfig->Pwm.OwnerShip != NONE_OWNED) {
    DEBUG ((DEBUG_INFO, "PSE PWM interrupt set to %s\n", IntrDeliverConfig[mPseConfig->Pwm.SbInterruptEnable].Name));
    Data = MmioRead32(MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP4_OFFSET);
    Data = ((Data & (~V_DEV1_INTERRUPT_MASK)) | (IntrDeliverConfig[mPseConfig->Pwm.SbInterruptEnable].ConfigValue << (S_OWNERSHIP_CTRL * DEVICE_1_INDEX)));
    MmioWrite32 (MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP4_OFFSET, Data);
  }

  if (mPseConfig->Pwm.OwnerShip != HOST_OWNED) {
    PsfDisablePseBar1 (PchPseIoIndexPwm);
    PsfHidePseDevice (PchPseIoIndexPwm);
  }

  return;
}

/**
  Program QEP ownership HOST/PSE/NONE based on the setup config.

  @param[in] MmioBase        Address to be used to access MMIO space
**/
VOID
PseControllerQepOwnerShip (
  IN  UINTN   MmioBase
  )
{
  UINT32                Index1;
  UINT32                Data;

  for (Index1 = 0; Index1 < GetPchMaxPseQepControllersNum (); Index1++) {
    //
    // QEP 0-3 GPIO programming
    //
    if (mPseConfig->Qep[Index1].OwnerShip != NONE_OWNED) {
      DEBUG ((DEBUG_INFO, "PSE QEP%d pins set to Native Mode\n", Index1));
      GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_QEP_A (Index1), mPseConfig->Qep[Index1].PinMux.QepA);
      GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_QEP_B (Index1), mPseConfig->Qep[Index1].PinMux.QepB);
      GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_QEP_I (Index1), mPseConfig->Qep[Index1].PinMux.QepI);
    }

    //
    // QEP 0-3 Ownership programming
    //
    DEBUG ((DEBUG_INFO, "PSE QEP%d IP set to %s owned\n", Index1, DevOwnConfig[mPseConfig->Qep[Index1].OwnerShip].Name));
    Data = MmioRead32(MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP3_OFFSET);
    Data = ((Data & (~(V_DEV3_OWNERSHIP_MASK << (S_OWNERSHIP_CTRL * Index1)))) | \
                   (DevOwnConfig[mPseConfig->Qep[Index1].OwnerShip].ConfigValue << (S_OWNERSHIP_CTRL * (DEVICE_3_INDEX + Index1))));
    MmioWrite32 (MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP3_OFFSET, Data);

    //
    // QEP 0-3 Interrupt programming
    //
    if (mPseConfig->Qep[Index1].OwnerShip != NONE_OWNED) {
      DEBUG ((DEBUG_INFO, "PSE Qep%d interrupt set to %s\n", Index1, IntrDeliverConfig[mPseConfig->Qep[Index1].SbInterruptEnable].Name));
      Data = MmioRead32(MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP3_OFFSET);
      Data = ((Data & (~(V_DEV3_INTERRUPT_MASK << (S_OWNERSHIP_CTRL * Index1)))) | \
             (IntrDeliverConfig[mPseConfig->Qep[Index1].SbInterruptEnable].ConfigValue << (S_OWNERSHIP_CTRL * (DEVICE_3_INDEX + Index1))));
      MmioWrite32 (MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP4_OFFSET, Data);
    }

    if (mPseConfig->Qep[Index1].OwnerShip != HOST_OWNED) {
      PsfDisablePseBar1 (PchPseIoIndexQep0 + Index1);
      PsfHidePseDevice (PchPseIoIndexQep0 + Index1);
    }
  }

  return;
}

/**
  Program I2C ownership HOST/PSE/NONE based on the setup config.

  @param[in] MmioBase        Address to be used to access MMIO space
**/
VOID
PseControllerI2cOwnerShip (
  IN  UINTN   MmioBase
  )
{
  UINT32                Index1;
  UINT32                Data;

  for (Index1 = 0; Index1 < GetPchMaxPseI2cControllersNum (); Index1++) {
    //
    // I2C 0-7 GPIO programming
    //
    if (mPseConfig->I2c[Index1].OwnerShip != NONE_OWNED) {
      DEBUG ((DEBUG_INFO, "PSE I2C%d pins set to Native Mode\n", Index1));
      GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_I2C_SDA (Index1), mPseConfig->I2c[Index1].PinMux.Sda);
      GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_I2C_SCL (Index1), mPseConfig->I2c[Index1].PinMux.Scl);
    }

    //
    // I2C 0-7 Ownership programming
    //
    DEBUG ((DEBUG_INFO, "PSE I2C%d IP set to %s owned\n", Index1, DevOwnConfig[mPseConfig->I2c[Index1].OwnerShip].Name));
    Data = MmioRead32(MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP0_OFFSET);
    Data = ((Data & (~(V_DEV0_OWNERSHIP_MASK << (S_OWNERSHIP_CTRL * Index1)))) | \
            (DevOwnConfig[mPseConfig->I2c[Index1].OwnerShip].ConfigValue << (S_OWNERSHIP_CTRL * (DEVICE_0_INDEX + Index1))));
    MmioWrite32 (MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP0_OFFSET, Data);

    //
    // I2C 0-7 Interrupt programming
    //
    if (mPseConfig->I2c[Index1].OwnerShip != NONE_OWNED) {
      DEBUG ((DEBUG_INFO, "PSE I2c%d interrupt set to %s\n", Index1, IntrDeliverConfig[mPseConfig->I2c[Index1].SbInterruptEnable].Name));
      Data = MmioRead32(MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP0_OFFSET);
      Data = ((Data & (~(V_DEV0_INTERRUPT_MASK << (S_OWNERSHIP_CTRL * Index1)))) | \
             (IntrDeliverConfig[mPseConfig->I2c[Index1].SbInterruptEnable].ConfigValue << (S_OWNERSHIP_CTRL * (DEVICE_0_INDEX+Index1))));
      MmioWrite32 (MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP0_OFFSET, Data);
    }

    if (mPseConfig->I2c[Index1].OwnerShip != HOST_OWNED) {
      PsfDisablePseBar1 (PchPseIoIndexI2C0 + Index1);
      PsfHidePseDevice (PchPseIoIndexI2C0 + Index1);
    }
  }

  return;
}

/**
  Program SPI ownership HOST/PSE/NONE based on the setup config.

  @param[in] MmioBase        Address to be used to access MMIO space
**/
VOID
PseControllerSpiOwnerShip (
  IN  UINTN   MmioBase
  )
{
  UINT32                Index1;
  UINT32                Index2;
  UINT32                Data;

  for (Index1 = 0; Index1 < GetPchMaxPseSpiControllersNum (); Index1++) {
    //
    // SPI 0-3 GPIO programming
    //
    if (mPseConfig->Spi[Index1].OwnerShip != NONE_OWNED) {
      DEBUG ((DEBUG_INFO, "PSE SPI%d pins set to Native Mode\n", Index1));
      GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_SPI_MOSI(Index1), mPseConfig->Spi[Index1].PinMux.Mosi);
      GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_SPI_MISO(Index1), mPseConfig->Spi[Index1].PinMux.Miso);
      GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_SPI_CLK(Index1), mPseConfig->Spi[Index1].PinMux.Clk);
      for (Index2 = 0; Index2 < GetPchMaxPseSpiControllerCsPinsNum (); Index2++) {
        if (mPseConfig->Spi[Index1].CsEnable[Index2]) {
          GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_SPI_CS(Index1, Index2), mPseConfig->Spi[Index1].PinMux.Cs[Index2]);
        }
      }
    }

    //
    // SPI 0-3 Ownership programming
    //
    DEBUG ((DEBUG_INFO, "PSE SPI%d IP set to %s owned\n", Index1, DevOwnConfig[mPseConfig->Spi[Index1].OwnerShip].Name));

    if (Index1 <= 1) {
      Data = MmioRead32(MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP1_OFFSET);
      Data = ((Data & (~(V_DEV6_OWNERSHIP_MASK << (S_OWNERSHIP_CTRL * Index1)))) | \
            (DevOwnConfig[mPseConfig->Spi[Index1].OwnerShip].ConfigValue << (S_OWNERSHIP_CTRL * (DEVICE_6_INDEX + Index1))));
      MmioWrite32 (MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP1_OFFSET, Data);
    } else {
      Data = MmioRead32(MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP2_OFFSET);
      Data = ((Data & (~(V_DEV0_OWNERSHIP_MASK << (S_OWNERSHIP_CTRL * (Index1-2)))) | \
            (DevOwnConfig[mPseConfig->Spi[Index1].OwnerShip].ConfigValue << (S_OWNERSHIP_CTRL * (DEVICE_0_INDEX + Index1 - 2)))));
      MmioWrite32 (MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP2_OFFSET, Data);
    }

    //
    // SPI 0-3 Interrupt programming
    //
    if (mPseConfig->Spi[Index1].OwnerShip != NONE_OWNED) {
      DEBUG ((DEBUG_INFO, "PSE SPI%d interrupt set to %s \n", Index1, IntrDeliverConfig[mPseConfig->Spi[Index1].SbInterruptEnable].Name));
      if (Index1 <= 1) {
        Data = MmioRead32(MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP1_OFFSET);
        Data = ((Data & (~(V_DEV6_INTERRUPT_MASK << (S_OWNERSHIP_CTRL * Index1)))) | \
             (IntrDeliverConfig[mPseConfig->Spi[Index1].SbInterruptEnable].ConfigValue << (S_OWNERSHIP_CTRL * (DEVICE_6_INDEX + Index1))));
        MmioWrite32 (MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP1_OFFSET, Data);
      } else {
        Data = MmioRead32(MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP2_OFFSET);
        Data = ((Data & (~(V_DEV0_INTERRUPT_MASK << (S_OWNERSHIP_CTRL * (Index1 - 2))))) | \
             (IntrDeliverConfig[mPseConfig->Spi[Index1].SbInterruptEnable].ConfigValue << (S_OWNERSHIP_CTRL * (DEVICE_0_INDEX + Index1 - 2))));
        MmioWrite32 (MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP2_OFFSET, Data);
      }
    }

    if (mPseConfig->Spi[Index1].OwnerShip != HOST_OWNED) {
      PsfDisablePseBar1 (PchPseIoIndexSpi0 + Index1);
      PsfHidePseDevice (PchPseIoIndexSpi0 + Index1);
    }
  }

  return;
}

/**
  Program DMA ownership HOST/PSE/NONE based on the setup config.

  @param[in] MmioBase        Address to be used to access MMIO space
**/
VOID
PseControllerDmaOwnerShip (
  IN  UINTN   MmioBase
  )
{
  UINT32                Index1;
  UINT32                Data;

  for (Index1 = 0; Index1 < GetPchMaxPseDmaControllersNum (); Index1++) {
    //
    // DMA 0-2 Ownership programming
    //
    DEBUG ((DEBUG_INFO, "PSE DMA%d IP set to %s owned\n", Index1, DevOwnConfig[mPseConfig->Dma[Index1].OwnerShip].Name));

    Data = MmioRead32(MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP3_OFFSET);
    Data = ((Data & (~(V_DEV0_OWNERSHIP_MASK << (S_OWNERSHIP_CTRL * Index1)))) | \
            (DevOwnConfig[mPseConfig->Dma[Index1].OwnerShip].ConfigValue << (S_OWNERSHIP_CTRL * (DEVICE_0_INDEX + Index1))));
    MmioWrite32 (MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP3_OFFSET, Data);

    //
    // DMA 0-2 Interrupt programming
    //
    if (mPseConfig->Dma[Index1].OwnerShip != NONE_OWNED) {
      DEBUG ((DEBUG_INFO, "PSE DMA%d interrupt set to %s \n", Index1, IntrDeliverConfig[mPseConfig->Dma[Index1].SbInterruptEnable].Name));
      Data = MmioRead32(MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP3_OFFSET);
      Data = ((Data & (~(V_DEV0_INTERRUPT_MASK << (S_OWNERSHIP_CTRL * Index1)))) | \
             (IntrDeliverConfig[mPseConfig->Dma[Index1].SbInterruptEnable].ConfigValue << (S_OWNERSHIP_CTRL * (DEVICE_0_INDEX + Index1))));
      MmioWrite32 (MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP3_OFFSET, Data);
    }

    if (mPseConfig->Dma[Index1].OwnerShip != HOST_OWNED) {
      PsfDisablePseBar1 (PchPseIoIndexDma0 + Index1);
      PsfHidePseDevice (PchPseIoIndexDma0 + Index1);
    }
  }

  return;
}

/**
  Program ADC ownership HOST/PSE/NONE based on the setup config.

  @param[in] MmioBase        Address to be used to access MMIO space
**/
VOID
PseControllerAdcOwnerShip (
  IN  UINTN   MmioBase
  )
{
  UINT32                Data;

  //
  // ADC Ownership programming
  //
  DEBUG ((DEBUG_INFO, "PSE ADC IP set to %s owned\n", DevOwnConfig[mPseConfig->Adc.OwnerShip].Name));

  Data = MmioRead32(MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP4_OFFSET);
  Data = ((Data & ~(V_DEV2_OWNERSHIP_MASK)) | \
          (DevOwnConfig[mPseConfig->Adc.OwnerShip].ConfigValue << (S_OWNERSHIP_CTRL * DEVICE_2_INDEX)));
  MmioWrite32 (MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP4_OFFSET, Data);

  //
  // ADC Interrupt programming
  //
  if (mPseConfig->Adc.SbInterruptEnable) {
    DEBUG ((DEBUG_INFO, "PSE ADC interrupt set to %s\n", IntrDeliverConfig[mPseConfig->Adc.SbInterruptEnable].Name));
    Data = MmioRead32(MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP4_OFFSET);
    Data = ((Data & (~(V_DEV2_INTERRUPT_MASK))) | \
             (IntrDeliverConfig[mPseConfig->Adc.SbInterruptEnable].ConfigValue << (S_OWNERSHIP_CTRL * DEVICE_2_INDEX)));
    MmioWrite32 (MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP4_OFFSET, Data);
  }

  if (mPseConfig->Adc.OwnerShip != HOST_OWNED) {
    PsfDisablePseBar1 (PchPseIoIndexAdc);
    PsfHidePseDevice (PchPseIoIndexAdc);
  }

  return;
}

/**
  Program CAN ownership HOST/PSE/NONE based on the setup config.

  @param[in] MmioBase        Address to be used to access MMIO space
**/
VOID
PseControllerCanOwnerShip (
  IN  UINTN   MmioBase
  )
{
  UINT32                Index1;
  UINT32                Data;

  for (Index1 = 0; Index1 < GetPchMaxPseCanControllersNum (); Index1++) {
    //
    // CAN 0-1 GPIO programming
    //
    if (mPseConfig->Can[Index1].OwnerShip != NONE_OWNED) {
      DEBUG ((DEBUG_INFO, "PSE CAN%d pins set to Native Mode\n", Index1));
      GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_CAN_RX (Index1), mPseConfig->Can[Index1].PinMux.Rx);
      GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_CAN_TX (Index1), mPseConfig->Can[Index1].PinMux.Tx);
    }

    //
    // CAN 0-1 Ownership programming
    //
    DEBUG ((DEBUG_INFO, "PSE CAN IP set to %s owned\n", Index1, DevOwnConfig[mPseConfig->Can[Index1].OwnerShip].Name));
    Data = MmioRead32(MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP2_OFFSET);
    Data = ((Data & (~(V_DEV4_OWNERSHIP_MASK << (S_OWNERSHIP_CTRL * Index1)))) | \
            (DevOwnConfig[mPseConfig->Can[Index1].OwnerShip].ConfigValue << (S_OWNERSHIP_CTRL * (DEVICE_4_INDEX + Index1))));
    MmioWrite32 (MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP2_OFFSET, Data);

    //
    // CAN 0-1 Interrupt programming
    //
    if (mPseConfig->Can[Index1].OwnerShip != NONE_OWNED) {
      DEBUG ((DEBUG_INFO, "PSE CAN interrupt set to %s \n", Index1, IntrDeliverConfig[mPseConfig->Can[Index1].SbInterruptEnable].Name));
      Data = MmioRead32(MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP2_OFFSET);
      Data = ((Data & (~(V_DEV4_INTERRUPT_MASK << (S_OWNERSHIP_CTRL * Index1)))) | \
             (IntrDeliverConfig[mPseConfig->Can[Index1].SbInterruptEnable].ConfigValue << (S_OWNERSHIP_CTRL * (DEVICE_4_INDEX+Index1))));
      MmioWrite32 (MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP2_OFFSET, Data);
    }

    if (mPseConfig->Can[Index1].OwnerShip != HOST_OWNED) {
      PsfDisablePseBar1 (PchPseIoIndexCan0 + Index1);
      PsfHidePseDevice (PchPseIoIndexCan0 + Index1);
    }
  }

  return;
}

/**
  Program UART ownership HOST/PSE/NONE based on the setup config.

  @param[in] MmioBase        Address to be used to access MMIO space
**/
VOID
PseControllerUartOwnerShip (
  IN  UINTN   MmioBase
  )
{
  UINT32                Index1;
  UINT32                Data;

  for (Index1 = 0; Index1 < GetPchMaxPseUartControllersNum (); Index1++) {
    //
    // UART 0-5 GPIO programming
    //
    if (mPseConfig->Uart[Index1].OwnerShip != NONE_OWNED) {
      DEBUG ((DEBUG_INFO, "PSE UART%d pins set to Native Mode\n", Index1));
      GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_UART_RX (Index1), mPseConfig->Uart[Index1].PinMux.Rx);
      GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_UART_TX (Index1), mPseConfig->Uart[Index1].PinMux.Tx);
      GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_UART_RTS (Index1), mPseConfig->Uart[Index1].PinMux.Rts);
      GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_UART_CTS (Index1), mPseConfig->Uart[Index1].PinMux.Cts);
    }

    //
    // UART 0-5 Ownership programming
    //
    DEBUG ((DEBUG_INFO, "PSE UART%d IP set to %s owned\n", Index1, DevOwnConfig[mPseConfig->Uart[Index1].OwnerShip].Name));
    Data = MmioRead32(MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP1_OFFSET);
    Data = ((Data & (~(V_DEV0_OWNERSHIP_MASK << (S_OWNERSHIP_CTRL * Index1)))) | \
            (DevOwnConfig[mPseConfig->Uart[Index1].OwnerShip].ConfigValue << (S_OWNERSHIP_CTRL * (DEVICE_0_INDEX + Index1))));
    MmioWrite32 (MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP1_OFFSET, Data);

    //
    // UART 0-5 Interrupt programming
    //
    if (mPseConfig->Uart[Index1].OwnerShip != NONE_OWNED) {
      DEBUG ((DEBUG_INFO, "PSE UART%d interrupt set to %s\n", Index1, IntrDeliverConfig[mPseConfig->Uart[Index1].SbInterruptEnable].Name));
      Data = MmioRead32(MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP1_OFFSET);
      Data = ((Data & (~(V_DEV0_INTERRUPT_MASK << (S_OWNERSHIP_CTRL * Index1)))) | \
             (IntrDeliverConfig[mPseConfig->Uart[Index1].SbInterruptEnable].ConfigValue << (S_OWNERSHIP_CTRL * (DEVICE_0_INDEX+Index1))));
      MmioWrite32 (MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP1_OFFSET, Data);
    }

    if (mPseConfig->Uart[Index1].OwnerShip != HOST_OWNED) {
      PsfDisablePseBar1 (PchPseIoIndexUart0 + Index1);
      PsfHidePseDevice (PchPseIoIndexUart0 + Index1);
    }
  }

  for (Index1 = 0; Index1 < GetPchMaxPseHsuartControllersNum (); Index1++) {
    if (mPseConfig->Hsuart[Index1].OwnerShip != NONE_OWNED) {
      DEBUG ((DEBUG_INFO, "PSE HSUART%d pins set to Native Mode\n", Index1));
      GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_HSUART_DE (Index1), mPseConfig->Hsuart[Index1].PinMux.De);
      GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_HSUART_RE (Index1), mPseConfig->Hsuart[Index1].PinMux.Re);
      GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_HSUART_EN (Index1), mPseConfig->Hsuart[Index1].PinMux.En);
    }
  }

  return;
}

/**
  Program Gbe ownership HOST/PSE/NONE based on the setup config.

  @param[in] MmioBase        Address to be used to access MMIO space
**/
VOID
PseControllerGbeOwnerShip (
  IN  UINTN   MmioBase
  )
{
  UINT32                Index1;
  UINT8                 PinCount = 0;
  UINT32                Data;

  for (Index1 = 0; Index1 < GetPchMaxPseGbeControllersNum (); Index1++) {
    //
    // GBE 0-1 GPIO programming
    //
    if (mPseConfig->Gbe[Index1].OwnerShip != NONE_OWNED) {
      DEBUG ((DEBUG_INFO, "PSE GBE%d pins set to Native Mode\n", Index1));
      if (Index1 == 0) {
        for (PinCount = 0; PinCount < GPIO_PSE_GBE0_RANGE; PinCount++) {
          GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_GBE0 (PinCount), 0);
        }
      } else if (Index1 == 1) {
        for (PinCount = 0; PinCount < GPIO_PSE_GBE1_RANGE; PinCount++) {
          GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_GBE1 (PinCount), 0);
        }
      }
    }

    //
    // GBE 0-1 Ownership programming
    //
    DEBUG ((DEBUG_INFO, "PSE GBE%d IP set to %s owned\n", Index1, DevOwnConfig[mPseConfig->Gbe[Index1].OwnerShip].Name));
    Data = MmioRead32(MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP2_OFFSET);
    Data = ((Data & (~(V_DEV2_OWNERSHIP_MASK << (S_OWNERSHIP_CTRL * Index1)))) | \
            (DevOwnConfig[mPseConfig->Gbe[Index1].OwnerShip].ConfigValue << (S_OWNERSHIP_CTRL * (DEVICE_2_INDEX + Index1))));
    MmioWrite32 (MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP2_OFFSET, Data);

    //
    // GBE 0-1 Interrupt programming
    //
    if (mPseConfig->Gbe[Index1].OwnerShip != NONE_OWNED) {
      DEBUG ((DEBUG_INFO, "PSE GBE%d interrupt set to %s \n", Index1, IntrDeliverConfig[mPseConfig->Gbe[Index1].SbInterruptEnable].Name));
      Data = MmioRead32(MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP2_OFFSET);
      Data = ((Data & (~(V_DEV2_INTERRUPT_MASK << (S_OWNERSHIP_CTRL * Index1)))) | \
             (IntrDeliverConfig[mPseConfig->Uart[Index1].SbInterruptEnable].ConfigValue << (S_OWNERSHIP_CTRL * (DEVICE_2_INDEX+Index1))));
      MmioWrite32 (MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP2_OFFSET, Data);
    }

    if (mPseConfig->Gbe[Index1].OwnerShip != HOST_OWNED) {
      PsfDisablePseBar1 (PchPseIoIndexGbe0 + Index1);
      PsfHidePseDevice (PchPseIoIndexGbe0 + Index1);
    }
  }

  return;
}

/**
  Program LH2PSE ownership HOST/PSE/NONE based on the setup config.

  @param[in] MmioBase        Address to be used to access MMIO space
**/
VOID
PseControllerLH2PseOwnerShip (
  IN  UINTN   MmioBase
  )
{
  UINT32                Data;

  //
  // LH2PSE Interrupt programming
  //
  DEBUG ((DEBUG_INFO, "PSE LH2PSE interrupt set to %s\n", IntrDeliverConfig[mPseConfig->Lh2Pse.SbInterruptEnable].Name));
  Data = MmioRead32(MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP4_OFFSET);
  Data = ((Data & (~V_DEV3_INTERRUPT_MASK)) | \
             (IntrDeliverConfig[mPseConfig->Lh2Pse.SbInterruptEnable].ConfigValue << (S_OWNERSHIP_CTRL * DEVICE_3_INDEX)));
  MmioWrite32 (MmioBase + R_PSE_MMIO_IPC_OFFSET + R_PSE_MMIO_OWNERSHIP4_OFFSET, Data);

  return;
}

/**
  Program Jtag ownership HOST/PSE/NONE based on the setup config.
  GPIO and Interrupt Config

  @param[in] MmioBase        Address to be used to access MMIO space
**/
VOID
PseControllerJtagOwnerShip (
  IN  UINTN   MmioBase
  )
{
  UINT8                 PinCount = 0;

  //
  // PSE JTAG GPIO configuration
  //
  if (mPseConfig->PseJtagPinMux) {
    DEBUG ((DEBUG_INFO, "PSE JTAG pins set to Native Mode\n"));
    for (PinCount = 0; PinCount < GPIO_PSE_JTAG_RANGE; PinCount++) {
      GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_JTAG (PinCount), 0);
    }
  }

  return;
}
/**
  Configures PSE-related GPIO pins to PSE native mode

  @param[in]  SiPolicy            Pointer to SI_POLICY_PPI
**/
VOID
PseSetGpioAndIpOwnership (
  IN  SI_POLICY_PPI    *SiPolicy
  )
{
  UINT64                PchPseBase;
  UINTN                 PchPseBar;
  UINT8                 PseDeviceNumber;
  UINT8                 PseFunctionNumber;

  DEBUG ((DEBUG_INFO, "PseSetGpioAndIpOwnership() Start\n"));

  PseDeviceNumber = PseGetDeviceNumber ();
  PseFunctionNumber = PseGetFunctionNumber ();

  PchPseBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 PseDeviceNumber,
                 PseFunctionNumber,
                 0
                 );

  if (PciSegmentRead16(PchPseBase + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    return;
  }

  PchPseBar = (((UINT64)PciSegmentRead32 (PchPseBase + R_PSE_CFG_BAR0_HIGH)) << 32)
            | PciSegmentRead32 (PchPseBase + R_PSE_CFG_BAR0_LOW)  & ~(B_PSE_CFG_BAR0_MASK);
  DEBUG ((DEBUG_INFO, "\t\tPchPseBar: %x,", PchPseBar));

  PseControllerEnableMmio(PchPseBase, PchPseBar);

  PseControllerTgpioOwnerShip(PchPseBar);
  PseControllerI2sOwnerShip(PchPseBar);
  PseControllerPwmOwnerShip(PchPseBar);
  PseControllerQepOwnerShip(PchPseBar);
  PseControllerI2cOwnerShip(PchPseBar);
  PseControllerSpiOwnerShip(PchPseBar);
  PseControllerDmaOwnerShip(PchPseBar);
  PseControllerAdcOwnerShip(PchPseBar);
  PseControllerCanOwnerShip(PchPseBar);
  PseControllerUartOwnerShip(PchPseBar);
  PseControllerGbeOwnerShip(PchPseBar);
  PseControllerLH2PseOwnerShip(PchPseBar);
  PseControllerJtagOwnerShip(PchPseBar);

  return;
}

/**
  Program temp MmioBase address into BAR register.

  @param[in] PciBaseAddress  Address of the PCI config space
  @param[in] MmioBase        Address to be used to access MMIO space
**/
VOID
PseControllerEnableMmio (
  IN  UINT64  PciBaseAddress,
  IN  UINTN   MmioBase
  )
{
  //
  // Disable MSE
  //
  PciSegmentAnd16 (PciBaseAddress + PCI_COMMAND_OFFSET, (UINT16) ~EFI_PCI_COMMAND_MEMORY_SPACE);
  //
  // Write temp address to lower base address
  //
  PciSegmentWrite32 (PciBaseAddress + PCI_BASE_ADDRESSREG_OFFSET, MmioBase);
  //
  // Clear upper base address
  //
  PciSegmentWrite32 (PciBaseAddress + (PCI_BASE_ADDRESSREG_OFFSET + 4), 0);
  //
  // Enable MSE
  //
  PciSegmentOr16 (PciBaseAddress + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);
}

/**
  Clear BAR address.

  @param[in] PciBaseAddress  Address of PCI config space
**/
VOID
PseControllerDisableMmio (
  IN UINT64  PciBaseAddress
  )
{
  //
  // Disable MSE
  //
  PciSegmentAnd16 (PciBaseAddress + PCI_COMMAND_OFFSET, (UINT16) ~EFI_PCI_COMMAND_MEMORY_SPACE);
  //
  // Clear lower base address
  //
  PciSegmentWrite32 (PciBaseAddress + PCI_BASE_ADDRESSREG_OFFSET, 0);
}

/**
  PCI Enumeratuion is not done till later in DXE
  Initlialize PSE BAR to a default value till enumeration is done
  also enable memory space decoding for PSE
**/
VOID
InitPseBar (
  VOID
  )
{
  UINT64       PchPseBase;
  UINT8        PseDeviceNumber;
  UINT8        PseFunctionNumber;

  PseDeviceNumber = PseGetDeviceNumber ();
  PseFunctionNumber = PseGetFunctionNumber ();

  PchPseBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 PseDeviceNumber,
                 PseFunctionNumber,
                 0
                 );
  PseControllerEnableMmio (PchPseBase, PCH_PSE_BASE_ADDRESS);
}

/**
  Schedules Global Reset required to change PSE static power gating state.
**/
STATIC
VOID
PsePerformGlobalReset (
  VOID
  )
{
  PCH_RESET_DATA             ResetData;

  DEBUG((DEBUG_INFO, "PsePerformGlobalReset()\n"));

  CopyMem (&ResetData.Guid, &gPchGlobalResetGuid, sizeof (EFI_GUID));
  StrCpyS (ResetData.Description, PCH_RESET_DATA_STRING_MAX_LENGTH, PCH_PLATFORM_SPECIFIC_RESET_STRING);
  SiScheduleResetSetType (EfiResetPlatformSpecific, &ResetData);
}

/**
  To enable Functional Safety for PSE GBE.
**/
STATIC
VOID
PseGbeFusaConfig (
  VOID
  )
{
  UINT64    GbePciBase;
  UINT32    MmioBaseTmp;
  UINT32    ConfigValue;

  // There are 2 GBEs so start with GBE0 first
  GbePciBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 PCI_DEVICE_NUMBER_PCH_PSE_GBE0,
                 PCI_FUNCTION_NUMBER_PCH_PSE_GBE0,
                 0
                 );

  MmioBaseTmp = PCH_TEMP_BASE_ADDRESS;

  PseControllerEnableMmio(GbePciBase, (UINTN)MmioBaseTmp);

  ConfigValue = B_PSE_MMIO_MTLTX_ECC_EN | B_PSE_MMIO_MTLRX_ECC_EN |
                B_PSE_MMIO_MTLEST_ECC_EN | B_PSE_MMIO_TSOMEM_ECC_EN |
                B_PSE_MMIO_MTL_ECC_ADROVR;
  MmioWrite32(MmioBaseTmp + R_PSE_MMIO_MTL_ECC_CONTROL, ConfigValue);
  ConfigValue = MmioRead32(MmioBaseTmp + R_PSE_MMIO_MTL_ECC_CONTROL);
  DEBUG((DEBUG_INFO, "GBE0 MTL_ECC_CONTROL = 0x%x\n", ConfigValue));

  ConfigValue = B_PSE_MMIO_TXMEM_INTREN | B_PSE_MMIO_RXMEM_INTREN | B_PSE_MMIO_ESTMEM_INTREN;
  MmioWrite32(MmioBaseTmp + R_PSE_MMIO_MTL_ECC_CONTROL_INTREN, ConfigValue);
  ConfigValue = MmioRead32(MmioBaseTmp + R_PSE_MMIO_MTL_ECC_CONTROL_INTREN);
  DEBUG((DEBUG_INFO, "GBE0 MTL_ECC_CONTROL_INTREN = 0x%x\n", ConfigValue));

  ConfigValue = B_PSE_MMIO_TSOMEM_INTREN;
  MmioWrite32(MmioBaseTmp + R_PSE_MMIO_DMA_ECC_CONTROL_INTREN, ConfigValue);
  ConfigValue = MmioRead32(MmioBaseTmp + R_PSE_MMIO_DMA_ECC_CONTROL_INTREN);
  DEBUG((DEBUG_INFO, "GBE0 DMA_ECC_CONTROL_INTREN = 0x%x\n", ConfigValue));

  // Free up the MMIO for next GBE
  PciSegmentAnd32 (GbePciBase + PCI_COMMAND_OFFSET, (UINT32)(~EFI_PCI_COMMAND_MEMORY_SPACE));

  // Second GBE
  GbePciBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 PCI_DEVICE_NUMBER_PCH_PSE_GBE1,
                 PCI_FUNCTION_NUMBER_PCH_PSE_GBE1,
                 0
                 );

  MmioBaseTmp = PCH_TEMP_BASE_ADDRESS;

  PseControllerEnableMmio(GbePciBase, (UINTN)MmioBaseTmp);

  ConfigValue = B_PSE_MMIO_MTLTX_ECC_EN | B_PSE_MMIO_MTLRX_ECC_EN |
                B_PSE_MMIO_MTLEST_ECC_EN | B_PSE_MMIO_TSOMEM_ECC_EN |
                B_PSE_MMIO_MTL_ECC_ADROVR;
  MmioWrite32(MmioBaseTmp + R_PSE_MMIO_MTL_ECC_CONTROL, ConfigValue);
  ConfigValue = MmioRead32(MmioBaseTmp + R_PSE_MMIO_MTL_ECC_CONTROL);
  DEBUG((DEBUG_INFO, "GBE1 MTL_ECC_CONTROL 0x%x\n", ConfigValue));

  ConfigValue = B_PSE_MMIO_TXMEM_INTREN | B_PSE_MMIO_RXMEM_INTREN | B_PSE_MMIO_ESTMEM_INTREN;
  MmioWrite32(MmioBaseTmp + R_PSE_MMIO_MTL_ECC_CONTROL_INTREN, ConfigValue);
  ConfigValue = MmioRead32(MmioBaseTmp + R_PSE_MMIO_MTL_ECC_CONTROL_INTREN);
  DEBUG((DEBUG_INFO, "GBE1 MTL_ECC_CONTROL_INTREN = 0x%x\n", ConfigValue));

  ConfigValue = B_PSE_MMIO_TSOMEM_INTREN;
  MmioWrite32(MmioBaseTmp + R_PSE_MMIO_DMA_ECC_CONTROL_INTREN, ConfigValue);
  ConfigValue = MmioRead32(MmioBaseTmp + R_PSE_MMIO_DMA_ECC_CONTROL_INTREN);
  DEBUG((DEBUG_INFO, "GBE1 DMA_ECC_CONTROL_INTREN = 0x%x\n", ConfigValue));

  // Free up the MMIO and it is done
  PseControllerDisableMmio(GbePciBase);
}

/**
  Set fixed MMIO address and BME bit for PSE DMA0/DMA1

  @retval EFI_SUCCESS                   Successfully completed.
  @retval EFI_UNSUPPORTED               Pci Config sapce not present.
**/
EFI_STATUS
PseDmaConfigure (
  VOID
  )
{
  UINT8               Index;
  UINT32              PseDmaPciBase;

  // PSE DMA0 is always enabled and owned by PSE
  // Set fixed MMIO base and BME bit for DMA1/DMA2 if enabled and owned by host
  for (Index = 1; Index < GetPchMaxPseDmaControllersNum(); Index++) {
    if (mPseConfig->Dma[Index].OwnerShip == HOST_OWNED) {
      switch (Index) {
        case 1:
          PseDmaPciBase = PCI_SEGMENT_LIB_ADDRESS (
                            DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                            DEFAULT_PCI_BUS_NUMBER_PCH,
                            PCI_DEVICE_NUMBER_PCH_PSE_DMA1,
                            PCI_FUNCTION_NUMBER_PCH_PSE_DMA1,
                            0
                            );
          if (PciSegmentRead16 (PseDmaPciBase) == 0xFFFF) {
            DEBUG ((DEBUG_INFO, "Pse DMA1 not present\n"));
            mPseConfig->Dma[Index].OwnerShip = NONE_OWNED;
            return EFI_UNSUPPORTED;
          }
          DEBUG ((DEBUG_INFO, "Pse DMA1 set fixed MMIO base and BME bit\n"));
          PseControllerEnableMmio (PseDmaPciBase, PCH_PSE_DMA1_BASE_ADDRESS);
          // Set BME bit
          PciSegmentOr16 (PseDmaPciBase + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_BUS_MASTER);
          break;
        case 2:
          PseDmaPciBase = PCI_SEGMENT_LIB_ADDRESS (
                            DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                            DEFAULT_PCI_BUS_NUMBER_PCH,
                            PCI_DEVICE_NUMBER_PCH_PSE_DMA2,
                            PCI_FUNCTION_NUMBER_PCH_PSE_DMA2,
                            0
                            );
          if (PciSegmentRead16 (PseDmaPciBase) == 0xFFFF) {
            DEBUG ((DEBUG_INFO, "Pse DMA2 not present\n"));
            mPseConfig->Dma[Index].OwnerShip = NONE_OWNED;
            return EFI_UNSUPPORTED;
          }
          DEBUG ((DEBUG_INFO, "Pse DMA2 set fixed MMIO base and BME bit\n"));
          PseControllerEnableMmio (PseDmaPciBase, PCH_PSE_DMA2_BASE_ADDRESS);
          // Set BME bit
          PciSegmentOr16 (PseDmaPciBase + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_BUS_MASTER);
          break;
        default:
          break;
      }
    }
  }

  return EFI_SUCCESS;
}

/**
  Configures Programmable Service Engine (PSE) Controller

  @param[in]  SiPolicy            Pointer to SI_POLICY_PPI
**/
STATIC
VOID
PseConfigure (
  IN  SI_POLICY_PPI   *SiPolicy
  )
{
  UINT64              PsePciBase;
  UINT8               PseDeviceNumber;
  UINT8               PseFunctionNumber;
  UINT32              PseIndex;
  UINT8               Controller;
  EFI_STATUS          Status;
  PCH_GENERAL_CONFIG  *PchGeneralConfig;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchGeneralConfigGuid, (VOID *) &PchGeneralConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPseConfigGuid, (VOID *) &mPseConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "PseConfigure() Start\n"));

  //
  // Check if PSE is disabled by static PG
  //
  if (PmcIsPseFunctionDisabled ()) {
    DEBUG ((DEBUG_INFO, "PSE Static PG disabled - Enable and issue reset!\n"));

    //
    // Enable PSE controller by disabling static PG
    //
    PmcEnablePse ();

    PsePerformGlobalReset ();

    return;
  }

  DEBUG ((DEBUG_INFO, "PSE: BAR1 - Shadowed PCI Config Space Disabled\n"));
  //
  // Configure in PCI mode - disable BAR1 (Shadowed PCI)
  // Set PCICFGCTR.BAR1_DISABLE (PCR[PSEBR] + 200h[7] = 1b)
  //
  PchPcrAndThenOr32 (
    PID_PSEBR,
    R_PSE_PCR_PCICFGCTRL,
    (UINT32) ~0,
    B_PSE_PCR_PCICFGCTRL_BAR1DIS
    );

  //
  // Disable PSE BAR1 in PSF
  //
  for (PseIndex = 0; PseIndex < PchPseIoIndexMax; PseIndex++) {
    PsfDisablePseBar1 (PseIndex);
  }

  if (PchGeneralConfig->PchMasterPowerGating != 0) {
    //
    // Power management programming
    // Set PMCTL = 3Fh (PCR[PSEBR] + 1D0h[5:0] = 111111b)
    //
    PchPcrAndThenOr32 (
      PID_PSEBR,
      R_PSE_PCR_PMCTL,
      (UINT32) ~(0),
      (BIT5 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0)
      );
  } else {
    //
    // Power management programming
    // Set PMCTL = 3Fh (PCR[PSEBR] + 1D0h[5:0] = 000000b)
    //
    PchPcrAndThenOr32 (
      PID_PSEBR,
      R_PSE_PCR_PMCTL,
      (UINT32)~(BIT5 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0),
      0
      );
  }

  PseDeviceNumber = PseGetDeviceNumber ();
  PseFunctionNumber = PseGetFunctionNumber ();

  PsePciBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 PseDeviceNumber,
                 PseFunctionNumber,
                 0
                 );

  //
  // Set D0Idle Max Power On Latency register (RWO)
  //
  PciSegmentOr16 (PsePciBase + R_PSE_CFG_D0I3_MAX_PW_ON_LATENCY, 0);

  if (PchGeneralConfig->PchMasterPowerGating != 0) {
    //
    // Set Hardware Autonomous Enable to allow PSE to independently enter/exit IPAPG states
    // Set PCE.HAE (PCI[PSE] + A2h[5] = 1b)
    //
    PciSegmentOr16 (PsePciBase + R_PSE_CFG_PCE, B_PSE_CFG_PCE_HAE);
  } else {
    PciSegmentAnd16 (PsePciBase + R_PSE_CFG_PCE, (UINT16)~(BIT5 | BIT3 | BIT2 | BIT1 | BIT0));
  }

  //
  // The following configurations required for FuSa
  //
  if (IsFusaSupported ()) {
    PseGbeFusaConfig ();
  }
  PseSetGpioAndIpOwnership (SiPolicy);

  ///
  /// Configure PSE interrupt
  ///
  for (Controller = 0; Controller < PchPseIoIndexMax; Controller++) {
    PseIoIntSet (SiPolicy, Controller);
  }

  PseDmaConfigure ();

  DEBUG ((DEBUG_INFO, "PseConfigure() End\n"));
}

/**
  Sets Programmable Service Engine (PSE) PSF Function Disable
**/
STATIC
VOID
PseDisable (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "PseDisable() Start\n"));

  for (UINT32 PseIndex = 0; PseIndex < PchPseIoIndexMax; PseIndex++) {
    PsfDisablePseDevice (PseIndex);
  }

  //
  // Check if PSE is static power gated
  //
  if (PmcIsPseFunctionDisabled ()) {
    DEBUG ((DEBUG_INFO, "PSE found already static power gated\n"));
    return;
  }

  //
  // Before modifying PSE Disable bit, make sure it's not locked.
  //
  if (!PmcIsFunctionDisableConfigLocked ()) {
    //
    // Statically disable PSE Controller
    //
    DEBUG ((DEBUG_INFO, "PSE found enabled and requested to be disabled - set PG bit and issue reset!\n"));
    PmcStaticDisablePse ();

    //
    // Perform reset for disabling to take effect
    //
    PsePerformGlobalReset ();
  } else {
    DEBUG ((DEBUG_ERROR, "PSE function disable bit is locked!\n"));
  }

  DEBUG ((DEBUG_INFO, "PseDisable() End \n"));
}

/**
  Initialize Programmable Service Engine (PSE)

  @param[in]  SiPolicy            Pointer to SI_POLICY_PPI
**/
VOID
PseInit (
  IN  SI_POLICY_PPI    *SiPolicy
  )
{
  UINT8           PseTgpioIndex;

  DEBUG ((DEBUG_INFO, "PseInit() Start\n"));

  if (!PmcIsPseSupported ()) {
    //
    // PSF Function Disable already set in PchEarlyDisabledDeviceHandling()
    //
    return;
  }

  InitPseBar();

  if (IsPseEnabled ()) {
    PseConfigure (SiPolicy);
    for (PseTgpioIndex = 0; PseTgpioIndex < GetPchMaxPseTimedGpioControllersNum (); PseTgpioIndex++) {
      PseTgpioInit (SiPolicy, PseTgpioIndex);
    }
  } else {
    PseDisable ();
  }

  DEBUG ((DEBUG_INFO, "PseInit() End\n"));
}
