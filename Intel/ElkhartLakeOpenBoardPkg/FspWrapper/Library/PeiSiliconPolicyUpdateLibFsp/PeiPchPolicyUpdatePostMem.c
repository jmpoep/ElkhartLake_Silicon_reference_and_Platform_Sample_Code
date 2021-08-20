/** @file
  This file is SampleCode of the library for Intel PCH PEI Policy initialization in post-memory.

Copyright (c) 2017 - 2018, Intel Corporation. All rights reserved.<BR>
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
#include <Pins/GpioPinsVer3Lp.h>
#include <Library/PchInfoLib.h>

#ifndef TCSS_MAX_USB3_PORTS
#define TCSS_MAX_USB3_PORTS      6
#endif

#ifndef MAX_IOM_AUX_BIAS_COUNT
#define MAX_IOM_AUX_BIAS_COUNT 6 // This define by SKU 4/6
#endif


IOM_AUX_ORI_PAD_CONFIG mIomAuxNullTable[MAX_IOM_AUX_BIAS_COUNT] = {
  // Pull UP GPIO Pin, Pull Down GPIO pin
  {0,                  0}, // Port 0
  {0,                  0}, // Port 1
  {0,                  0}, // Port 2
  {0,                  0}, // Port 3
  {0,                  0}, // Port 4
  {0,                  0}, // Port 5
};

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
  UINT32                             PortIndex;

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

  FspsUpd->FspsConfig.Usb3OverCurrentPin[0] = PcdGet8 (PcdUsb30OverCurrentPinPort0);
  FspsUpd->FspsConfig.Usb3OverCurrentPin[1] = PcdGet8 (PcdUsb30OverCurrentPinPort1);
  FspsUpd->FspsConfig.Usb3OverCurrentPin[2] = PcdGet8 (PcdUsb30OverCurrentPinPort2);
  FspsUpd->FspsConfig.Usb3OverCurrentPin[3] = PcdGet8 (PcdUsb30OverCurrentPinPort3);
  FspsUpd->FspsConfig.Usb3OverCurrentPin[4] = PcdGet8 (PcdUsb30OverCurrentPinPort4);
  FspsUpd->FspsConfig.Usb3OverCurrentPin[5] = PcdGet8 (PcdUsb30OverCurrentPinPort5);
  FspsUpd->FspsConfig.Usb3OverCurrentPin[6] = PcdGet8 (PcdUsb30OverCurrentPinPort6);
  FspsUpd->FspsConfig.Usb3OverCurrentPin[7] = PcdGet8 (PcdUsb30OverCurrentPinPort7);
  FspsUpd->FspsConfig.Usb3OverCurrentPin[8] = PcdGet8 (PcdUsb30OverCurrentPinPort8);
  FspsUpd->FspsConfig.Usb3OverCurrentPin[9] = PcdGet8 (PcdUsb30OverCurrentPinPort9);

  for (PortIndex = 0; PortIndex < GetPchXhciMaxUsb3PortNum (); PortIndex++) {
    FspsUpd->FspsConfig.PortUsb30Enable[PortIndex] = PcdGet8 (PcdCpuUsb30PortEnable);
  }

  FspsUpd->FspsConfig.SerialIoUartRxPinMuxPolicy[0] = GPIO_VER3_MUXING_SERIALIO_UART0_RXD_GPP_F1;
  FspsUpd->FspsConfig.SerialIoUartTxPinMuxPolicy[0] = GPIO_VER3_MUXING_SERIALIO_UART0_TXD_GPP_F2;
  FspsUpd->FspsConfig.SerialIoUartRtsPinMuxPolicy[0] = GPIO_VER3_MUXING_SERIALIO_UART0_RTS_GPP_F0;
  FspsUpd->FspsConfig.SerialIoUartCtsPinMuxPolicy[0] = GPIO_VER3_MUXING_SERIALIO_UART0_CTS_GPP_F3;

  FspsUpd->FspsConfig.PchSerialIoI2cSdaPinMux[4] = GPIO_VER3_MUXING_SERIALIO_I2C4_SDA_GPP_H8;
  FspsUpd->FspsConfig.PchSerialIoI2cSclPinMux[4] = GPIO_VER3_MUXING_SERIALIO_I2C4_SCL_GPP_H9;

  FspsUpd->FspsConfig.PchHdaAudioLinkDmic0ClkAPinMux = GPIO_VER3_MUXING_DMIC0_CLKA_GPP_S6;
  FspsUpd->FspsConfig.PchHdaAudioLinkDmic0ClkBPinMux = GPIO_VER3_MUXING_DMIC0_CLKB_GPP_S2;
  FspsUpd->FspsConfig.PchHdaAudioLinkDmic0DataPinMux = GPIO_VER3_MUXING_DMIC0_DATA_GPP_S7;
  FspsUpd->FspsConfig.PchHdaAudioLinkDmic1ClkAPinMux = GPIO_VER3_MUXING_DMIC1_CLKA_GPP_S4;
  FspsUpd->FspsConfig.PchHdaAudioLinkDmic1ClkBPinMux = GPIO_VER3_MUXING_DMIC1_CLKB_GPP_S3;
  FspsUpd->FspsConfig.PchHdaAudioLinkDmic1DataPinMux = GPIO_VER3_MUXING_DMIC1_DATA_GPP_S5;

  for (PortIndex = 0; PortIndex < TCSS_MAX_USB3_PORTS; PortIndex++) {
    FspsUpd->FspsConfig.IomTypeCPortPadCfg[(PortIndex * 2)] = mIomAuxNullTable[PortIndex].GpioPullN;
    FspsUpd->FspsConfig.IomTypeCPortPadCfg[(PortIndex * 2) + 1] = mIomAuxNullTable[PortIndex].GpioPullP;
  }

  return EFI_SUCCESS;
}

