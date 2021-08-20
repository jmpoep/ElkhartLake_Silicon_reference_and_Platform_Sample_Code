/** @file
  Header file for GPIO Private Lib Internal functions.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 Intel Corporation.

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
#ifndef _GPIO_NATIVE_PRIVATE_LIB_INTERNAL_H_
#define _GPIO_NATIVE_PRIVATE_LIB_INTERNAL_H_

#include "GpioPrivateLib.h"

#define GPIO_PAD_NONE 0

/**
  This function provides SerialIo I2C controller pins

  @param[in]  SerialIoI2cControllerNumber    I2C controller

  @param[out] NativePinsTable                Table with pins
  @param[out] NoOfNativePins                 Number of pins
**/
VOID
GpioGetSerialIoI2cPins (
  IN  UINT32                      SerialIoI2cControllerNumber,
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable
  );

/**
  This function provides SerialIo UART controller pins

  @param[in]  SerialIoUartControllerNumber   UART controller
  @param[in]  HardwareFlowControl            Hardware Flow control
  @param[in]  PinMuxing                      UART controller pin muxing
                                             CNL: 0:defaut pins, 1:pins muxed with CNV_BRI/RGI
  @param[out] NativePinsTable                Table with pins
  @param[out] NoOfNativePins                 Number of pins
**/
VOID
GpioGetSerialIoUartPins (
  IN  UINT32                      SerialIoUartControllerNumber,
  IN  BOOLEAN                     HardwareFlowControl,
  IN  UINT32                      PinMuxing,
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable,
  OUT UINT32                      *NoOfNativePins
  );

/**
  This function provides SerialIo SPI controller pins

  @param[in]  SerialIoSpiControllerNumber   SPI controller

  @param[out] NativePinsTable               Table with pins
**/
VOID
GpioGetSerialIoSpiPins (
  IN  UINT32                      SerialIoSpiControllerNumber,
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable
  );

/**
  This function provides ISH GP pin data

  @param[in]  IshGpPinNumber        ISH GP pin number

  @param[out] NativePin             ISH GP pin
**/
VOID
GpioGetIshGpPin (
  IN  UINT32                      IshGpPinNumber,
  OUT GPIO_PAD_NATIVE_FUNCTION    *NativePin
  );

/**
  This function provides ISH UART controller pins

  @param[in]  IshUartControllerNumber   ISH UART controller

  @param[out] NativePinsTable           Table with pins
**/
VOID
GpioGetIshUartPins (
  IN  UINT32                      IshUartControllerNumber,
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable
  );

/**
  This function provides ISH I2C controller pins

  @param[in]  IshI2cControllerNumber   ISH I2C controller

  @param[out] NativePinsTable          Table with pins
**/
VOID
GpioGetIshI2cPins (
  IN  UINT32                      IshI2cControllerNumber,
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable
  );

/**
  This function provides ISH SPI controller pins

  @param[out] NativePinsTable          Table with pins
**/
VOID
GpioGetIshSpiPins (
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable
  );

/**
  This function provides SCS SD CARD controller pins

  @param[out] NativePinsTable                Table with pins
  @param[out] NoOfNativePins                 Number of pins
**/
VOID
GpioGetScsSdCardPins (
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable,
  OUT UINT32                      *NoOfNativePins
  );

/**
  This function provides SCS SD CARD detect pin

  @retval GpioPin             SD CARD Detect pin
**/
GPIO_PAD
GpioGetScsSdCardDetectPin (
  VOID
  );

/**
  This function provides SCS eMMC controller pins

  @param[out] NativePinsTable                Table with pins
  @param[out] NoOfNativePins                 Number of pins
**/
VOID
GpioGetScsEmmcPins (
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable,
  OUT UINT32                      *NoOfNativePins
  );

/**
  This function provides HD Audio Link pins

  @param[out] NativePinsTable                Table with pins
  @param[out] NoOfNativePins                 Number of pins
**/
VOID
GpioGetHdAudioLinkPins (
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable,
  OUT UINT32                      *NoOfNativePins
  );

/**
  This function provides DMIC interface pins

  @param[in]  DmicNumber               DMIC interface

  @param[out] NativePinsTable          Table with pins
**/
VOID
GpioGetHdaDmicPins (
  IN  UINT32                      DmicNumber,
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable
  );

/**
  This function provides SSP/I2S interface pins

  @param[in]  SspInterfaceNumber       SSP/I2S interface

  @param[out] NativePinsTable          Table with pins
**/
VOID
GpioGetHdaSspPins (
  IN  UINT32                      SspInterfaceNumber,
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable
  );

/**
  This function provides SNDW interface pins

  @param[in]  SndwInterfaceNumber      SNDWx interface number

  @param[out] NativePinsTable          Table with pins
**/
VOID
GpioGetHdaSndwPins (
  IN  UINT32                      SndwInterfaceNumber,
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable
  );

/**
  This function provides SMBUS interface pins

  @param[out] NativePinsTable          Table with pins
**/
VOID
GpioGetSmbusPins (
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable
  );

/**
  This function provides SATA DevSlp pin data

  @param[in]  SataCtrlIndex       SATA controller index
  @param[in]  SataPort            SATA port number
  @param[out] NativePin           SATA DevSlp pin
**/
VOID
GpioGetSataDevSlpPin (
  IN  UINT32                    SataCtrlIndex,
  IN  UINTN                     SataPort,
  OUT GPIO_PAD_NATIVE_FUNCTION  *NativePin
  );

/**
  This function provides PCIe CLKREQ pin data

  @param[in]  ClkreqIndex        CLKREQ# number
  @param[out] NativePin          Native pin data
**/
VOID
GpioGetPcieClkReqPin (
  IN  UINT32                      ClkreqIndex,
  OUT GPIO_PAD_NATIVE_FUNCTION    *NativePin
  );

/**
  This function provides eDP pins

  @param[out] NativePinsTable                Table with pins
  @param[out] NoOfNativePins                 Number of pins
**/
VOID
GpioGetEdpPins (
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable,
  OUT UINT32                      *NoOfNativePins
  );

/**
  This function provides DDPx interface pins

  @param[in]  DdpInterface   DDPx interface

  @param[out] NativePinsTable          Table with pins
**/
VOID
GpioGetDdpPins (
  IN  GPIO_DDP                    DdpInterface,
  OUT GPIO_PAD_NATIVE_FUNCTION    **NativePinsTable
  );

/**
  This function provides CNVi BT UART pins

  @param[in]  ConnectionType           CNVi BT UART connection type
  @param[out] VCnviBtUartPad           Table with vCNV_BT_UARTx pads
  @param[out] VCnviBtUartPadMode       vCNV_BT_UARTx pad mode
  @param[out] VUartForCnviBtPad        Table with vUART0 pads
  @param[out] VUartForCnviBtPadMode    vUART0 pad mode
**/
VOID
GpioGetCnviBtUartPins (
  IN  VGPIO_CNVI_BT_UART_CONNECTION_TYPE  ConnectionType,
  OUT GPIO_PAD                            **VCnviBtUartPad,
  OUT GPIO_PAD_MODE                       *VCnviBtUartPadMode,
  OUT GPIO_PAD                            **VUartForCnviBtPad,
  OUT GPIO_PAD_MODE                       *VUartForCnviBtPadMode
  );

/**
  This function provides CNVi BT UART external pads

  @param[out] NativePinsTable          Table with pins
**/
VOID
GpioGetCnviBtUartExternalPins (
  OUT GPIO_PAD_NATIVE_FUNCTION **NativePinsTable
  );

/**
  This function provides CNVi BT I2S pins

  @param[in]  ConnectionType          CNVi BT I2S connection type
  @param[out] VCnviBtI2sPad           Table with vCNV_BT_I2Sx pads
  @param[out] VCnviBtI2sPadMode       vCNV_BT_I2Sx pad mode
  @param[out] VSspForCnviBtPad        Table with vSSP2 pads
  @param[out] VSspForCnviBtPadMode    vSSP2 pad mode
**/
VOID
GpioGetCnviBtI2sPins (
  IN  VGPIO_CNVI_BT_I2S_CONNECTION_TYPE  ConnectionType,
  OUT GPIO_PAD                 **VCnviBtI2sPad,
  OUT GPIO_PAD_MODE            *VCnviBtI2sPadMode,
  OUT GPIO_PAD                 **VSspForCnviBtPad,
  OUT GPIO_PAD_MODE            *VSspForCnviBtPadMode
  );

/**
  This function provides CNVi BT I2S external pads

  @param[out] NativePinsTable          Table with pins
**/
VOID
GpioGetCnviBtI2sExternalPins (
  OUT GPIO_PAD_NATIVE_FUNCTION **NativePinsTable
  );

/**
  This function provides CNVi MFUART1 pins

  @param[in]  ConnectionType          CNVi MFUART1 connection type
  @param[out] VCnviBtI2sPad           Table with vCNV_MFUART1x pads
  @param[out] VCnviBtI2sPadMode       vCNV_MFUART1x pad mode
  @param[out] VSspForCnviBtPad        Table with vISH_UART0 pads
  @param[out] VSspForCnviBtPadMode    vISH_UART0 pad mode
**/
VOID
GpioGetCnviMfUart1Pins (
  IN  VGPIO_CNVI_MF_UART1_CONNECTION_TYPE  ConnectionType,
  OUT GPIO_PAD                 **VCnviMfUart1Pad,
  OUT GPIO_PAD_MODE            *VCnviMfUart1PadMode,
  OUT GPIO_PAD                 **VUartForCnviMfUart1Pad,
  OUT GPIO_PAD_MODE            *VUartForCnviMfUart1PadMode
  );

/**
  This function provides CNVi MFUART1 external pads

  @param[out] NativePinsTable          Table with pins
**/
VOID
GpioGetCnviMfUart1ExternalPins (
  OUT GPIO_PAD_NATIVE_FUNCTION **NativePinsTable
  );

/**
  This function provides CNVi Bluetooth Enable pad

  @retval GpioPad           CNVi Bluetooth Enable pad
**/
GPIO_PAD
GpioGetCnviBtEnablePin (
  VOID
  );

/**
  This function provides CNVi BRI RGI GPIO pads

  @param[out] NativePinsTable          Table with pins
**/
VOID
GpioGetCnvBriRgiPins (
  OUT GPIO_PAD_NATIVE_FUNCTION **NativePinsTable
  );

/**
  This function provides CNVi MFUART2 external pins

  @param[out] NativePinsTable          Table with pins
**/
VOID
GpioGetCnvMfUart2ExternalPins (
  OUT GPIO_PAD_NATIVE_FUNCTION **NativePinsTable
  );

/**
  This function provides CNVi BT interface select pin

  @retval GpioPad          GPIO pad for CNVi BT interface select
**/
GPIO_PAD
GpioGetCnviBtIfSelectPin (
  VOID
  );

/**
  This function provides CNVi BT Charging pin

  @retval GpioPad          GPIO pad for CNVi BT Charging select
**/
GPIO_PAD
GpioGetCnviBtChargingPin (
  VOID
  );

/**
  This function provides CNVi A4WP pin

  @param[out] GpioNativePad       GPIO native pad for CNVi A4WP
**/
VOID
GpioGetCnviA4WpPin (
  OUT GPIO_PAD_NATIVE_FUNCTION  *GpioNativePad
  );

/**
  This function provides CNVi BT host wake int pin

  @retval GpioPad          GPIO pad BT host wake int
**/
GPIO_PAD
GpioGetCnviBtHostWakeIntPin (
  VOID
  );

/**
  This function provides IMGCLKOUT pins

  @param[out] NativePinsTable          Table with pins
  @param[out] NoOfNativePins            Number of pins
**/
VOID
GpioGetImgClkOutPins (
  OUT GPIO_PAD_NATIVE_FUNCTION **NativePinsTable,
  OUT UINT32                   *NoOfNativePins
  );

/**
  This function provides PWRBTN pin

  @retval GpioPad          PWRTBTN pin
**/
GPIO_PAD
GpioGetPwrBtnPin (
  VOID
  );

/**
  This procedure will get IRQ field value to be programmed into register

  @param[in]  Irq                 Irq number
  @param[out] Data32And           Value to be AND'ed with MISCCFG reg
  @param[out] Data32Or            Value to be OR'ed with MISCCFG reg
**/
VOID
GpioGetIrqFieldValue (
  IN  UINT8          Irq,
  OUT UINT32         *Data32And,
  OUT UINT32         *Data32Or
  );

/**
  This procedure enables debounce feature on a selected pad configured in input mode
  Debounce time can be specified in microseconds. GPIO HW supports only certain values
  according to below formula:
   DebounceTime = (2 ^ PADCFG_DW2.DEBOUNCE)*(glitch filter clock period).
  RTC clock with f = 32 KHz is used for glitch filter.
   DebounceTime = (2 ^ PADCFG_DW2.DEBOUNCE)*(31.25 us).
  Supported DebounceTime values are following:
   DebounceTime = 0 -> Debounce feature disabled
   DebounceTime > 0 && < 250us -> Not supported
   DebounceTime = 250us - 1024000us -> Supported range (DebounceTime = 250us * 2^n)
  For values not supported by GPIO HW, function will round down
  to closest supported

  @param[in] GpioPad              GPIO pad
  @param[in, out] DebounceTime    Debounce Time in microseconds
                                  If Debounce Time = 0, Debouncer feature will be disabled
                                  Function will set DebounceTime argument to rounded supported value

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_INVALID_PARAMETER   Invalid GpioPad or unsupported DebounceDuration value
  @retval EFI_UNSUPPORTED         GpioPad is not owned by host
**/
EFI_STATUS
GpioSetDebounceTimer (
  IN GPIO_PAD                  GpioPad,
  IN OUT UINT32                *DebounceTime
  );

#endif // _GPIO_NATIVE_PRIVATE_LIB_INTERNAL_H_
