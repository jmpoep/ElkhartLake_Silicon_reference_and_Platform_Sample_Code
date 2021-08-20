/** @file
  This file is SampleCode of the library for Intel PCH PEI Policy initialization in post-memory.

Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Base.h>
#include <FspEas.h>
#include <FspsUpd.h>
#include <Library/PcdLib.h>
#include <GpioPinsVer3.h>

/**
  Performs FSP PCH PEI Policy initialization.

  @param[in][out]  FspsUpd             Pointer to FSP UPD Data.

  @retval          EFI_SUCCESS         FSP UPD Data is updated.
  @retval          EFI_NOT_FOUND       Fail to locate required PPI.
  @retval          Other               FSP UPD Data update process fail.
**/
EFI_STATUS
EFIAPI
PeiFspPchPolicyUpdatePostMem (
  IN OUT FSPS_UPD    *FspsUpd
  )
{
  FspsUpd->FspsConfig.Usb2OverCurrentPin[0] = PcdGet8 (PcdUsb20OverCurrentPinPort0);
  FspsUpd->FspsConfig.Usb2OverCurrentPin[1] = PcdGet8 (PcdUsb20OverCurrentPinPort1);
  FspsUpd->FspsConfig.Usb2OverCurrentPin[2] = PcdGet8 (PcdUsb20OverCurrentPinPort2);
  FspsUpd->FspsConfig.Usb2OverCurrentPin[3] = PcdGet8 (PcdUsb20OverCurrentPinPort3);
  FspsUpd->FspsConfig.Usb2OverCurrentPin[4] = PcdGet8 (PcdUsb20OverCurrentPinPort4);
  FspsUpd->FspsConfig.Usb2OverCurrentPin[5] = PcdGet8 (PcdUsb20OverCurrentPinPort5);
  FspsUpd->FspsConfig.Usb2OverCurrentPin[6] = PcdGet8 (PcdUsb20OverCurrentPinPort6);
  FspsUpd->FspsConfig.Usb2OverCurrentPin[7] = PcdGet8 (PcdUsb20OverCurrentPinPort7);
  FspsUpd->FspsConfig.Usb2OverCurrentPin[8] = PcdGet8 (PcdUsb20OverCurrentPinPort8);
  FspsUpd->FspsConfig.Usb2OverCurrentPin[9] = PcdGet8 (PcdUsb20OverCurrentPinPort9);
  FspsUpd->FspsConfig.Usb2OverCurrentPin[10] = PcdGet8 (PcdUsb20OverCurrentPinPort10);
  FspsUpd->FspsConfig.Usb2OverCurrentPin[11] = PcdGet8 (PcdUsb20OverCurrentPinPort11);
  FspsUpd->FspsConfig.Usb2OverCurrentPin[12] = PcdGet8 (PcdUsb20OverCurrentPinPort12);
  FspsUpd->FspsConfig.Usb2OverCurrentPin[13] = PcdGet8 (PcdUsb20OverCurrentPinPort13);
  FspsUpd->FspsConfig.Usb2OverCurrentPin[14] = PcdGet8 (PcdUsb20OverCurrentPinPort14);
  FspsUpd->FspsConfig.Usb2OverCurrentPin[15] = PcdGet8 (PcdUsb20OverCurrentPinPort15);
  FspsUpd->FspsConfig.SataPortsEnable[0] = PcdGet8 (PcdSataPortsEnable0);
  FspsUpd->FspsConfig.SerialIoUartRxPinMux[0] = GPIO_VER3_MUXING_SERIALIO_UART0_RXD_GPP_C8;
  FspsUpd->FspsConfig.SerialIoUartTxPinMux[0] = GPIO_VER3_MUXING_SERIALIO_UART0_TXD_GPP_C9;
  FspsUpd->FspsConfig.SerialIoUartRtsPinMux[0] = GPIO_VER3_MUXING_SERIALIO_UART0_RTS_GPP_C10;
  FspsUpd->FspsConfig.SerialIoUartCtsPinMux[0] = GPIO_VER3_MUXING_SERIALIO_UART0_CTS_GPP_C11;

  FspsUpd->FspsConfig.PchSerialIoI2cSdaPinMux[4] =GPIO_VER3_MUXING_SERIALIO_I2C4_SDA_GPP_H8;
  FspsUpd->FspsConfig.PchSerialIoI2cSclPinMux[4] =GPIO_VER3_MUXING_SERIALIO_I2C4_SCL_GPP_H9;

  return EFI_SUCCESS;
}

