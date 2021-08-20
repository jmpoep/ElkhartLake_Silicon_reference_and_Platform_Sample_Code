/** @file
  This file provides services for SerialIo policy function

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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
#include <Library/PchInfoLib.h>
#include <Library/SerialIoUartDebugPropertyPcdLib.h>
#include <Ppi/SiPolicy.h>
#include <SerialIoConfig.h>

/**
  Print SERIAL_IO_CONFIG and serial out.

  @param[in] SiPolicyPpi            Pointer to a SI_POLICY_PPI
**/
VOID
SerialIoPrintConfig (
  IN SI_POLICY_PPI     *SiPolicyPpi
  )
{
  EFI_STATUS        Status;
  SERIAL_IO_CONFIG  *SerialIoConfig;
  UINT8             Index;
  UINT8             CsIndex;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gSerialIoConfigGuid, (VOID *) &SerialIoConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------ Serial IO Config ------------------\n"));

  for (Index = 0; Index < GetPchMaxSerialIoSpiControllersNum (); Index++) {
    DEBUG ((DEBUG_INFO, " SPI[%d].Mode                 = %d\n", Index, SerialIoConfig->SpiDeviceConfig[Index].Mode));
    DEBUG ((DEBUG_INFO, " SPI[%d].DefaultCsOutput      = %d\n", Index, SerialIoConfig->SpiDeviceConfig[Index].DefaultCsOutput));
    DEBUG ((DEBUG_INFO, " SPI[%d].CsMode               = %d\n", Index, SerialIoConfig->SpiDeviceConfig[Index].CsMode));
    DEBUG ((DEBUG_INFO, " SPI[%d].CsState              = %d\n", Index, SerialIoConfig->SpiDeviceConfig[Index].CsState));
    for (CsIndex = 0; CsIndex < GetPchMaxSerialIoSpiChipSelectsNum (); CsIndex++) {
      DEBUG ((DEBUG_INFO, " SPI[%d].CsEnable[%d]          = %d\n", Index, CsIndex, SerialIoConfig->SpiDeviceConfig[Index].CsEnable[CsIndex]));
      DEBUG ((DEBUG_INFO, " SPI[%d].CsPolarity[%d]        = %d\n", Index, CsIndex, SerialIoConfig->SpiDeviceConfig[Index].CsPolarity[CsIndex]));
    }
  }

  for (Index = 0; Index < GetPchMaxSerialIoUartControllersNum (); Index++) {
    DEBUG ((DEBUG_INFO, " UART[%d].Mode                = %d\n", Index, SerialIoConfig->UartDeviceConfig[Index].Mode));
    DEBUG ((DEBUG_INFO, " UART[%d].Attributes.BaudRate = %d\n", Index, SerialIoConfig->UartDeviceConfig[Index].Attributes.BaudRate));
    DEBUG ((DEBUG_INFO, " UART[%d].Attributes.Parity   = %d\n", Index, SerialIoConfig->UartDeviceConfig[Index].Attributes.Parity));
    DEBUG ((DEBUG_INFO, " UART[%d].Attributes.DataBits = %d\n", Index, SerialIoConfig->UartDeviceConfig[Index].Attributes.DataBits));
    DEBUG ((DEBUG_INFO, " UART[%d].Attributes.StopBits = %d\n", Index, SerialIoConfig->UartDeviceConfig[Index].Attributes.StopBits));
    DEBUG ((DEBUG_INFO, " UART[%d].Attributes.AutoFlow = %d\n", Index, SerialIoConfig->UartDeviceConfig[Index].Attributes.AutoFlow));
    DEBUG ((DEBUG_INFO, " UART[%d].PinMux.Rx           = 0x%x\n", Index, SerialIoConfig->UartDeviceConfig[Index].PinMux.Rx));
    DEBUG ((DEBUG_INFO, " UART[%d].PinMux.Tx           = 0x%x\n", Index, SerialIoConfig->UartDeviceConfig[Index].PinMux.Tx));
    DEBUG ((DEBUG_INFO, " UART[%d].PinMux.Rts          = 0x%x\n", Index, SerialIoConfig->UartDeviceConfig[Index].PinMux.Rts));
    DEBUG ((DEBUG_INFO, " UART[%d].PinMux.Cts          = 0x%x\n", Index, SerialIoConfig->UartDeviceConfig[Index].PinMux.Cts));
    DEBUG ((DEBUG_INFO, " UART[%d].DBG2                = %d\n", Index, SerialIoConfig->UartDeviceConfig[Index].DBG2));
    DEBUG ((DEBUG_INFO, " UART[%d].PowerGating         = %d\n", Index, SerialIoConfig->UartDeviceConfig[Index].PowerGating));
    DEBUG ((DEBUG_INFO, " UART[%d].DmaEnable           = %d\n", Index, SerialIoConfig->UartDeviceConfig[Index].DmaEnable));
  }

  for (Index = 0; Index < GetPchMaxSerialIoI2cControllersNum (); Index++) {
    DEBUG ((DEBUG_INFO, " I2C[%d].Mode                 = %d\n", Index, SerialIoConfig->I2cDeviceConfig[Index].Mode));
    DEBUG ((DEBUG_INFO, " I2C[%d].PinMux.Sda           = 0x%x\n", Index, SerialIoConfig->I2cDeviceConfig[Index].PinMux.Sda));
    DEBUG ((DEBUG_INFO, " I2C[%d].PinMux.Scl           = 0x%x\n", Index, SerialIoConfig->I2cDeviceConfig[Index].PinMux.Scl));
    DEBUG ((DEBUG_INFO, " I2C[%d].PadTermination       = %d\n", Index, SerialIoConfig->I2cDeviceConfig[Index].PadTermination));
  }
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
SerialIoLoadConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  UINT8                  Index;
  SERIAL_IO_CONFIG       *SerialIoConfig;
  SERIAL_IO_UART_CONFIG  UartDeviceConfig;
  UINT8                  SerialIoUartNumber;

  SerialIoConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "SerialIoConfig->Header.GuidHob.Name = %g\n", &SerialIoConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "SerialIoConfig->Header.GuidHob.Header.HobLength = 0x%x\n", SerialIoConfig->Header.GuidHob.Header.HobLength));

  for (Index = 0; Index < GetPchMaxSerialIoSpiControllersNum (); Index++) {
    SerialIoConfig->SpiDeviceConfig[Index].Mode        = SerialIoSpiDisabled;
    SerialIoConfig->SpiDeviceConfig[Index].CsEnable[0] = 1;
  }

  for (Index = 0; Index < GetPchMaxSerialIoI2cControllersNum (); Index++) {
    SerialIoConfig->I2cDeviceConfig[Index].Mode = SerialIoI2cPci;
  }

  for (Index = 0; Index < GetPchMaxSerialIoUartControllersNum (); Index++) {
    SerialIoConfig->UartDeviceConfig[Index].Mode                = SerialIoUartDisabled;
    SerialIoConfig->UartDeviceConfig[Index].DBG2                = FALSE;
    SerialIoConfig->UartDeviceConfig[Index].DmaEnable           = TRUE;
    SerialIoConfig->UartDeviceConfig[Index].Attributes.BaudRate = 115200;
    SerialIoConfig->UartDeviceConfig[Index].Attributes.Parity   = 1;
    SerialIoConfig->UartDeviceConfig[Index].Attributes.DataBits = 8;
    SerialIoConfig->UartDeviceConfig[Index].Attributes.StopBits = 1;
    SerialIoConfig->UartDeviceConfig[Index].Attributes.AutoFlow = 0;
  }

  if (SerialIoUartDebugPcdGetDebugEnable () > 0) {
    SerialIoUartDebugPcdGetDeviceConfig (&UartDeviceConfig, &SerialIoUartNumber);
    SerialIoConfig->UartDeviceConfig[SerialIoUartNumber].Mode                = UartDeviceConfig.Mode;
    SerialIoConfig->UartDeviceConfig[SerialIoUartNumber].Attributes.BaudRate = UartDeviceConfig.Attributes.BaudRate;
    SerialIoConfig->UartDeviceConfig[SerialIoUartNumber].Attributes.Parity   = UartDeviceConfig.Attributes.Parity;
    SerialIoConfig->UartDeviceConfig[SerialIoUartNumber].Attributes.DataBits = UartDeviceConfig.Attributes.DataBits;
    SerialIoConfig->UartDeviceConfig[SerialIoUartNumber].Attributes.StopBits = UartDeviceConfig.Attributes.StopBits;
    SerialIoConfig->UartDeviceConfig[SerialIoUartNumber].Attributes.AutoFlow = UartDeviceConfig.Attributes.AutoFlow;
  }
}

STATIC COMPONENT_BLOCK_ENTRY  mSerialIoBlocks = {
  &gSerialIoConfigGuid,
  sizeof (SERIAL_IO_CONFIG),
  SERIAL_IO_CONFIG_REVISION,
  SerialIoLoadConfigDefault
};

/**
  Get SerialIo config block table size.

  @retval      Size of config block
**/
UINT16
SerialIoGetConfigBlockTotalSize (
  VOID
  )
{
  return mSerialIoBlocks.Size;
}

/**
  Add SerialIo ConfigBlock.

  @param[in] ConfigBlockTableAddress    The pointer to config block table

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
SerialIoAddConfigBlock (
  IN VOID           *ConfigBlockTableAddress
  )
{
  return AddComponentConfigBlocks (ConfigBlockTableAddress, &mSerialIoBlocks, 1);
}
