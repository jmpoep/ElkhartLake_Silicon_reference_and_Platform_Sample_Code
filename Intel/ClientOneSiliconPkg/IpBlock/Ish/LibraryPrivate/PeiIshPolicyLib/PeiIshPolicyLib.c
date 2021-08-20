/** @file
  This file provides services for Ish policy function

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
#include <Library/PeiIshLib.h>
#include <Ppi/SiPolicy.h>
#include <IshConfig.h>

/**
  Print ISH_CONFIG and serial out.

  @param[in] SiPolicyPpi            Pointer to a SI_POLICY_PPI
**/
VOID
IshPrintConfig (
  IN SI_POLICY_PPI     *SiPolicyPpi
  )
{
  EFI_STATUS    Status;
  ISH_CONFIG    *IshConfig;
  UINT32        CtrlIndex;
  UINT32        CsIndex;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gIshConfigGuid, (VOID *) &IshConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------ ISH Config ------------------\n"));

  for (CtrlIndex = 0; CtrlIndex < GetPchMaxIshSpiControllersNum (); CtrlIndex++) {
    DEBUG ((DEBUG_INFO, " SPI%d Enable      = %x\n", CtrlIndex, IshConfig->Spi[CtrlIndex].Enable));
    for (CsIndex =0; CsIndex < GetPchMaxIshSpiControllerCsPinsNum (); CsIndex++) {
      DEBUG ((DEBUG_INFO, " SPI%d Cs#%d Enable = %x\n", CtrlIndex, CsIndex, IshConfig->Spi[CtrlIndex].CsEnable[CsIndex]));
    }
    DEBUG ((DEBUG_INFO, " Pin muxing:\n"));
    DEBUG ((DEBUG_INFO, "  Mosi = %a\n", GpioPinMuxName (IshConfig->Spi[CtrlIndex].PinConfig.Mosi.PinMux)));
    DEBUG ((DEBUG_INFO, "  Miso = %a\n", GpioPinMuxName (IshConfig->Spi[CtrlIndex].PinConfig.Miso.PinMux)));
    DEBUG ((DEBUG_INFO, "  Clk  = %a\n", GpioPinMuxName (IshConfig->Spi[CtrlIndex].PinConfig.Clk.PinMux)));
    for (CsIndex = 0; CsIndex < GetPchMaxIshSpiControllerCsPinsNum (); CsIndex++) {
      DEBUG ((DEBUG_INFO, "  Cs#%d = %a\n", CsIndex, GpioPinMuxName (IshConfig->Spi[CtrlIndex].PinConfig.Cs[CsIndex].PinMux)));
    }

    DEBUG ((DEBUG_INFO, " Pad termination:\n"));
    DEBUG ((DEBUG_INFO, "  Mosi = %a\n", GpioGetPadTerminationString (IshConfig->Spi[CtrlIndex].PinConfig.Mosi.PadTermination)));
    DEBUG ((DEBUG_INFO, "  Miso = %a\n", GpioGetPadTerminationString (IshConfig->Spi[CtrlIndex].PinConfig.Miso.PadTermination)));
    DEBUG ((DEBUG_INFO, "  Clk  = %a\n", GpioGetPadTerminationString (IshConfig->Spi[CtrlIndex].PinConfig.Clk.PadTermination)));
    for (CsIndex = 0; CsIndex < GetPchMaxIshSpiControllerCsPinsNum (); CsIndex++) {
      DEBUG ((DEBUG_INFO, "  Cs#%d = %a\n", CsIndex, GpioGetPadTerminationString (IshConfig->Spi[CtrlIndex].PinConfig.Cs[CsIndex].PadTermination)));
    }
  }
  for (CtrlIndex = 0; CtrlIndex < GetPchMaxIshUartControllersNum (); CtrlIndex++) {
    DEBUG ((DEBUG_INFO, " UART%d Enable     = %x\n", CtrlIndex, IshConfig->Uart[CtrlIndex].Enable));
    DEBUG ((DEBUG_INFO, " Pin muxing:\n"));
    DEBUG ((DEBUG_INFO, "  Rx = %a\n",   GpioPinMuxName (IshConfig->Uart[CtrlIndex].PinConfig.Rx.PinMux)));
    DEBUG ((DEBUG_INFO, "  Tx = %a\n",   GpioPinMuxName (IshConfig->Uart[CtrlIndex].PinConfig.Tx.PinMux)));
    DEBUG ((DEBUG_INFO, "  Rts = %a\n",  GpioPinMuxName (IshConfig->Uart[CtrlIndex].PinConfig.Rts.PinMux)));
    DEBUG ((DEBUG_INFO, "  Cts = %a\n",  GpioPinMuxName (IshConfig->Uart[CtrlIndex].PinConfig.Cts.PinMux)));

    DEBUG ((DEBUG_INFO, " Pad termination:\n"));
    DEBUG ((DEBUG_INFO, "  Rx = %a\n",   GpioGetPadTerminationString (IshConfig->Uart[CtrlIndex].PinConfig.Rx.PadTermination)));
    DEBUG ((DEBUG_INFO, "  Tx = %a\n",   GpioGetPadTerminationString (IshConfig->Uart[CtrlIndex].PinConfig.Tx.PadTermination)));
    DEBUG ((DEBUG_INFO, "  Rts = %a\n",  GpioGetPadTerminationString (IshConfig->Uart[CtrlIndex].PinConfig.Rts.PadTermination)));
    DEBUG ((DEBUG_INFO, "  Cts = %a\n",  GpioGetPadTerminationString (IshConfig->Uart[CtrlIndex].PinConfig.Cts.PadTermination)));
  }
  for (CtrlIndex = 0; CtrlIndex < GetPchMaxIshI2cControllersNum (); CtrlIndex++) {
    DEBUG ((DEBUG_INFO, " I2C%d Enable      = %x\n", CtrlIndex, IshConfig->I2c[CtrlIndex].Enable));
    DEBUG ((DEBUG_INFO, " Pin muxing:\n"));
    DEBUG ((DEBUG_INFO, "  Sda = %a\n",  GpioPinMuxName (IshConfig->I2c[CtrlIndex].PinConfig.Sda.PinMux)));
    DEBUG ((DEBUG_INFO, "  Scl = %a\n",  GpioPinMuxName (IshConfig->I2c[CtrlIndex].PinConfig.Scl.PinMux)));

    DEBUG ((DEBUG_INFO, " Pad termination:\n"));
    DEBUG ((DEBUG_INFO, "  Sda = %a\n",  GpioGetPadTerminationString (IshConfig->I2c[CtrlIndex].PinConfig.Sda.PadTermination)));
    DEBUG ((DEBUG_INFO, "  Scl = %a\n",  GpioGetPadTerminationString (IshConfig->I2c[CtrlIndex].PinConfig.Scl.PadTermination)));
  }
  for (CtrlIndex = 0; CtrlIndex < GetPchMaxIshGpNum (); CtrlIndex++) {
    DEBUG ((DEBUG_INFO, " GP_%d Enable      = %x\n", IshGetGpNumber (CtrlIndex), IshConfig->Gp[CtrlIndex].Enable));
    DEBUG ((DEBUG_INFO, " Pin muxing:\n"));
    DEBUG ((DEBUG_INFO, "  Gpio = %a\n", GpioPinMuxName (IshConfig->Gp[CtrlIndex].PinConfig.PinMux)));

    DEBUG ((DEBUG_INFO, " Pad termination:\n"));
    DEBUG ((DEBUG_INFO, "  Gpio = %a\n", GpioGetPadTerminationString (IshConfig->Gp[CtrlIndex].PinConfig.PadTermination)));
  }
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
IshLoadConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  ISH_CONFIG  *IshConfig;
  IshConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "IshConfig->Header.GuidHob.Name = %g\n", &IshConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "IshConfig->Header.GuidHob.Header.HobLength = 0x%x\n", IshConfig->Header.GuidHob.Header.HobLength));
}

STATIC COMPONENT_BLOCK_ENTRY  mIshBlocks = {
  &gIshConfigGuid,
  sizeof (ISH_CONFIG),
  ISH_CONFIG_REVISION,
  IshLoadConfigDefault
};

/**
  Get Ish config block table size.

  @retval      Size of config block
**/
UINT16
IshGetConfigBlockTotalSize (
  VOID
  )
{
  return mIshBlocks.Size;
}

/**
  Add Ish ConfigBlock.

  @param[in] ConfigBlockTableAddress    The pointer to config block table

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
IshAddConfigBlock (
  IN VOID           *ConfigBlockTableAddress
  )
{
  return AddComponentConfigBlocks (ConfigBlockTableAddress, &mIshBlocks, 1);
}
