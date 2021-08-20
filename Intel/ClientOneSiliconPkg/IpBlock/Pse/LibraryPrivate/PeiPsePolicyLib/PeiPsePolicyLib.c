/** @file
  This file provides services for Pse policy function

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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
#include <Library/SiConfigBlockLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/GpioPrivateLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PeiPseLib.h>
#include <Ppi/SiPolicy.h>
#include <PseConfig.h>

/**
  Print PSE_CONFIG and serial out.

  @param[in] SiPolicyPpi            Pointer to a SI_POLICY_PPI
**/
VOID
PsePrintConfig (
  IN SI_POLICY_PPI     *SiPolicyPpi
  )
{
  EFI_STATUS    Status;
  PSE_CONFIG    *PseConfig;
  UINT32        CtrlIndex;
  UINT32        CsIndex;
  UINT32        PinIndex;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gPseConfigGuid, (VOID *) &PseConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------ PSE Config ------------------\n"));
  DEBUG ((DEBUG_INFO, " PseLogOutputChannel   = %x\n", PseConfig->PseLogOutputChannel));
  DEBUG ((DEBUG_INFO, " PseLogOutputSize      = %x\n", PseConfig->PseLogOutputSize));
  DEBUG ((DEBUG_INFO, " PseLogOutputOffset    = %x\n", PseConfig->PseLogOutputOffset));

  DEBUG ((DEBUG_INFO, " PseJtagEnabled        = %x\n", PseConfig->PseJtagEnabled));
  DEBUG ((DEBUG_INFO, " PseJtagPinMux         = %x\n", PseConfig->PseJtagPinMux));

  for (CtrlIndex = 0; CtrlIndex < GetPchMaxPseI2sControllersNum (); CtrlIndex++) {
    DEBUG ((DEBUG_INFO, " I2S%d Enable     = %x\n", CtrlIndex, PseConfig->I2s[CtrlIndex].OwnerShip));
    DEBUG ((DEBUG_INFO, " Pin muxing:\n"));
    DEBUG ((DEBUG_INFO, "  Rx = %a\n",   GpioPinMuxName (PseConfig->I2s[CtrlIndex].PinMux.Rx)));
    DEBUG ((DEBUG_INFO, "  Tx = %a\n",   GpioPinMuxName (PseConfig->I2s[CtrlIndex].PinMux.Tx)));
    DEBUG ((DEBUG_INFO, "  Clk = %a\n",  GpioPinMuxName (PseConfig->I2s[CtrlIndex].PinMux.Clk)));
    DEBUG ((DEBUG_INFO, "  Sfrm = %a\n",  GpioPinMuxName (PseConfig->I2s[CtrlIndex].PinMux.Sfrm)));
  }

  DEBUG ((DEBUG_INFO, " PWM Enable     = %x\n", PseConfig->Pwm.OwnerShip));
  DEBUG ((DEBUG_INFO, " Pin Enable:\n"));
  for (PinIndex = 0; PinIndex < GetPchMaxPsePwmControllerPinsNum (); PinIndex++) {
    DEBUG ((DEBUG_INFO, "  Gpio PWM_%d Enable = %x\n", PinIndex, PseConfig->Pwm.PinEnable[PinIndex]));
  }
  DEBUG ((DEBUG_INFO, " Pin muxing:\n"));
  for (PinIndex = 0; PinIndex < GetPchMaxPsePwmControllerPinsNum (); PinIndex++) {
    DEBUG ((DEBUG_INFO, "  Gpio PWM_%d = %a\n", PinIndex, GpioPinMuxName (PseConfig->Pwm.PinMux.Pin[PinIndex])));
  }

  for (CtrlIndex = 0; CtrlIndex < GetPchMaxPseUartControllersNum (); CtrlIndex++) {
    DEBUG ((DEBUG_INFO, " UART%d Enable     = %x\n", CtrlIndex, PseConfig->Uart[CtrlIndex].OwnerShip));
    DEBUG ((DEBUG_INFO, " Pin muxing:\n"));
    DEBUG ((DEBUG_INFO, "  Rx = %a\n",   GpioPinMuxName (PseConfig->Uart[CtrlIndex].PinMux.Rx)));
    DEBUG ((DEBUG_INFO, "  Tx = %a\n",   GpioPinMuxName (PseConfig->Uart[CtrlIndex].PinMux.Tx)));
    DEBUG ((DEBUG_INFO, "  Rts = %a\n",  GpioPinMuxName (PseConfig->Uart[CtrlIndex].PinMux.Rts)));
    DEBUG ((DEBUG_INFO, "  Cts = %a\n",  GpioPinMuxName (PseConfig->Uart[CtrlIndex].PinMux.Cts)));
  }

  for (CtrlIndex = 0; CtrlIndex < GetPchMaxPseHsuartControllersNum (); CtrlIndex++) {
    DEBUG ((DEBUG_INFO, " HSUART%d Enable     = %x\n", CtrlIndex, PseConfig->Hsuart[CtrlIndex].OwnerShip));
    DEBUG ((DEBUG_INFO, " Pin muxing:\n"));
    DEBUG ((DEBUG_INFO, "  De = %a\n",   GpioPinMuxName (PseConfig->Hsuart[CtrlIndex].PinMux.De)));
    DEBUG ((DEBUG_INFO, "  Re = %a\n",   GpioPinMuxName (PseConfig->Hsuart[CtrlIndex].PinMux.Re)));
    DEBUG ((DEBUG_INFO, "  En = %a\n",   GpioPinMuxName (PseConfig->Hsuart[CtrlIndex].PinMux.En)));
  }

  for (CtrlIndex = 0; CtrlIndex < GetPchMaxPseQepControllersNum (); CtrlIndex++) {
    DEBUG ((DEBUG_INFO, " QEP%d Enable     = %x\n", CtrlIndex, PseConfig->Qep[CtrlIndex].OwnerShip));
    DEBUG ((DEBUG_INFO, " Pin muxing:\n"));
    DEBUG ((DEBUG_INFO, "  QepA = %a\n",   GpioPinMuxName (PseConfig->Qep[CtrlIndex].PinMux.QepA)));
    DEBUG ((DEBUG_INFO, "  QepB = %a\n",   GpioPinMuxName (PseConfig->Qep[CtrlIndex].PinMux.QepB)));
    DEBUG ((DEBUG_INFO, "  QepI = %a\n",   GpioPinMuxName (PseConfig->Qep[CtrlIndex].PinMux.QepI)));
  }

  for (CtrlIndex = 0; CtrlIndex < GetPchMaxPseI2cControllersNum (); CtrlIndex++) {
    DEBUG ((DEBUG_INFO, " I2C%d Enable     = %x\n", CtrlIndex, PseConfig->I2c[CtrlIndex].OwnerShip));
    DEBUG ((DEBUG_INFO, " Pin muxing:\n"));
    DEBUG ((DEBUG_INFO, "  Sda = %a\n",   GpioPinMuxName (PseConfig->I2c[CtrlIndex].PinMux.Sda)));
    DEBUG ((DEBUG_INFO, "  Scl = %a\n",   GpioPinMuxName (PseConfig->I2c[CtrlIndex].PinMux.Scl)));
  }

  for (CtrlIndex = 0; CtrlIndex < GetPchMaxPseSpiControllersNum (); CtrlIndex++) {
    DEBUG ((DEBUG_INFO, " SPI%d Enable      = %x\n", CtrlIndex, PseConfig->Spi[CtrlIndex].OwnerShip));
    for (CsIndex =0; CsIndex < GetPchMaxPseSpiControllerCsPinsNum (); CsIndex++) {
      DEBUG ((DEBUG_INFO, " SPI%d Cs#%d Enable = %x\n", CtrlIndex, CsIndex, PseConfig->Spi[CtrlIndex].CsEnable[CsIndex]));
    }
    DEBUG ((DEBUG_INFO, " Pin muxing:\n"));
    DEBUG ((DEBUG_INFO, "  Mosi = %a\n", GpioPinMuxName (PseConfig->Spi[CtrlIndex].PinMux.Mosi)));
    DEBUG ((DEBUG_INFO, "  Miso = %a\n", GpioPinMuxName (PseConfig->Spi[CtrlIndex].PinMux.Miso)));
    DEBUG ((DEBUG_INFO, "  Clk  = %a\n", GpioPinMuxName (PseConfig->Spi[CtrlIndex].PinMux.Clk)));
    for (CsIndex =0; CsIndex < GetPchMaxPseSpiControllerCsPinsNum (); CsIndex++) {
      DEBUG ((DEBUG_INFO, "  Cs#%d = %a\n", CsIndex, GpioPinMuxName (PseConfig->Spi[CtrlIndex].PinMux.Cs[CsIndex])));
    }
  }

  DEBUG ((DEBUG_INFO, " ADC Enable     = %x\n", PseConfig->Adc.OwnerShip));

  for (CtrlIndex = 0; CtrlIndex < GetPchMaxPseCanControllersNum (); CtrlIndex++) {
    DEBUG ((DEBUG_INFO, " CAN%d Enable     = %x\n", CtrlIndex, PseConfig->Can[CtrlIndex].OwnerShip));
    DEBUG ((DEBUG_INFO, " Pin muxing:\n"));
    DEBUG ((DEBUG_INFO, "  Rx = %a\n",   GpioPinMuxName (PseConfig->Can[CtrlIndex].PinMux.Rx)));
    DEBUG ((DEBUG_INFO, "  Tx = %a\n",   GpioPinMuxName (PseConfig->Can[CtrlIndex].PinMux.Tx)));
  }

  for (CtrlIndex = 0; CtrlIndex < GetPchMaxPseTimedGpioControllersNum(); CtrlIndex++) {
    DEBUG ((DEBUG_INFO, " TimedGpio%d Enable     = %x\n", CtrlIndex, PseConfig->TimedGpio[CtrlIndex].OwnerShip));
    DEBUG ((DEBUG_INFO, " TimedGpio%d Pin Allocation     = ", CtrlIndex));
    switch (PseConfig->TimedGpio[CtrlIndex].PinAllocation) {
      case LOWER20:
        DEBUG ((DEBUG_INFO, "Lower 20\n"));
        break;
      case MID20:
        DEBUG ((DEBUG_INFO, "Mid 20\n"));
        break;
      case TOP20:
        DEBUG ((DEBUG_INFO, "Top 20\n"));
        break;
      default:
        DEBUG ((DEBUG_INFO, "No pin allocated\n"));
    }
  }
  DEBUG ((DEBUG_INFO, "  Pin Enable:\n"));
  for (PinIndex = 0; PinIndex < GetPchMaxPseTimdedGpioPinsNum(); PinIndex++) {
    DEBUG ((DEBUG_INFO, "   TGpio_%d Enable = %x\n", PinIndex, PseConfig->TimedGpioPinEnable[PinIndex]));
  }
  DEBUG ((DEBUG_INFO, "  Pin muxing:\n"));
  for (PinIndex = 0; PinIndex < GetPchMaxPseTimdedGpioPinsNum(); PinIndex++) {
    DEBUG ((DEBUG_INFO, "   TGpio_%d = %a\n", PinIndex, GpioPinMuxName (PseConfig->TimedGpioPinMux.Pin[PinIndex])));
  }
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
PseLoadConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  PSE_CONFIG  *PseConfig;
  PseConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "PseConfig->Header.GuidHob.Name = %g\n", &PseConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "PseConfig->Header.GuidHob.Header.HobLength = 0x%x\n", PseConfig->Header.GuidHob.Header.HobLength));
}

STATIC COMPONENT_BLOCK_ENTRY  mPseBlocks = {
  &gPseConfigGuid,
  sizeof (PSE_CONFIG),
  PSE_CONFIG_REVISION,
  PseLoadConfigDefault
};

/**
  Get Pse config block table size.

  @retval      Size of config block
**/
UINT16
PseGetConfigBlockTotalSize (
  VOID
  )
{
  return mPseBlocks.Size;
}

/**
  Add Pse ConfigBlock.

  @param[in] ConfigBlockTableAddress    The pointer to config block table

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
PseAddConfigBlock (
  IN VOID           *ConfigBlockTableAddress
  )
{
  return AddComponentConfigBlocks (ConfigBlockTableAddress, &mPseBlocks, 1);
}
