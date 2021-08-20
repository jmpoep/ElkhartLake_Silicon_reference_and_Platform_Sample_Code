/** @file
  Fsp Silicon Common library

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

@par Specification
**/

#include <Base.h>
#include <FspEas.h>
#include <FsptUpd.h>
#include <FspmUpd.h>
#include <FspsUpd.h>
#include <Library/PrintLib.h>
#include <Library/FspHelperLib.h>
#include <Library/FspCommonLib.h>
#include <Library/GetFsptApiParameter.h>
#include <Library/SerialIoUartDebugPropertyPcdLib.h>
#include <SerialIoDevices.h>

/**
  Serial Io Uart Debug Configuration Wrapper

  @param[out] UartDeviceConfig           A pointer to the SERIAL_IO_UART_CONFIG.
  @param[out] SerialIoUartDebugEnable    Serial Io Uart Debug Enable/Disable.
  @param[out] SerialIoUartNumber         The Number of Serial Io Uart.
  @param[out] SerialIoUartPciMmioBase    MMIO Base Address by default in PCI Mode
**/
VOID
SerialIoUartDebugConfigurationWrapper (
  OUT SERIAL_IO_UART_CONFIG  *UartDeviceConfig,
  OUT UINT8                  *SerialIoUartDebugEnable,
  OUT UINT8                  *SerialIoUartNumber,
  OUT UINT32                 *SerialIoUartPciMmioBase
  )
{
  FSP_INFO_HEADER        *FspInfoHeader;
  FSPT_UPD               *FsptUpd;

  FsptUpd = (FSPT_UPD *) *((UINT32 *) (SecGetFsptApiParameter () + 0x4));
  if (FsptUpd->FspUpdHeader.Signature != FSPT_UPD_SIGNATURE) {
    FspInfoHeader                         = (FSP_INFO_HEADER *) SiAsmGetFspInfoHeader ();
    FsptUpd                               = (FSPT_UPD *) (FspInfoHeader->ImageBase + FspInfoHeader->CfgRegionOffset);
  }
  if (FsptUpd != NULL) {
    *SerialIoUartDebugEnable              = FsptUpd->FsptConfig.PcdSerialIoUartDebugEnable;
    *SerialIoUartNumber                   = FsptUpd->FsptConfig.PcdSerialIoUartNumber;
    *SerialIoUartPciMmioBase              = FsptUpd->FsptConfig.PcdSerialIoUartDebugMmioBase;
    UartDeviceConfig->Mode                = FsptUpd->FsptConfig.PcdSerialIoUartMode;
    UartDeviceConfig->Attributes.BaudRate = FsptUpd->FsptConfig.PcdSerialIoUartBaudRate;
    UartDeviceConfig->Attributes.Parity   = FsptUpd->FsptConfig.PcdSerialIoUartParity;
    UartDeviceConfig->Attributes.DataBits = FsptUpd->FsptConfig.PcdSerialIoUartDataBits;
    UartDeviceConfig->Attributes.StopBits = FsptUpd->FsptConfig.PcdSerialIoUartStopBits;
    UartDeviceConfig->Attributes.AutoFlow = FsptUpd->FsptConfig.PcdSerialIoUartAutoFlow;
    UartDeviceConfig->PinMux.Rx           = FsptUpd->FsptConfig.PcdSerialIoUartRxPinMux;
    UartDeviceConfig->PinMux.Tx           = FsptUpd->FsptConfig.PcdSerialIoUartTxPinMux;
    UartDeviceConfig->PinMux.Rts          = FsptUpd->FsptConfig.PcdSerialIoUartRtsPinMux;
    UartDeviceConfig->PinMux.Cts          = FsptUpd->FsptConfig.PcdSerialIoUartCtsPinMux;
    return;
  }
  *SerialIoUartDebugEnable = SerialIoUartDebugPcdGetDebugEnable ();
  *SerialIoUartPciMmioBase = SerialIoUartDebugPcdGetPciDefaultMmioBase ();
  SerialIoUartDebugPcdGetDeviceConfig (UartDeviceConfig, SerialIoUartNumber);
}

/**
  This function check the signture of UPD

  @param[in] ApiIdx           Internal index of the FSP API.
  @param[in] ApiParam         Parameter of the FSP API.
**/
EFI_STATUS
EFIAPI
FspUpdSignatureCheck (
  IN UINT32   ApiIdx,
  IN VOID     *ApiParam
  )
{
  EFI_STATUS    Status;
  FSPM_UPD      *FspmUpd;
  FSPS_UPD      *FspsUpd;

  Status = EFI_SUCCESS;
  FspmUpd = NULL;
  FspsUpd = NULL;

  if (ApiIdx == 3) {
    //
    // FspMemoryInit check
    //
    FspmUpd = (FSPM_UPD *)ApiParam;
    if (FspmUpd != NULL) {
      if ((FspmUpd->FspUpdHeader.Signature != FSPM_UPD_SIGNATURE)
        || ((UINTN)FspmUpd->FspmArchUpd.StackBase == 0 )
        || (FspmUpd->FspmArchUpd.StackSize < PcdGet32(PcdFspTemporaryRamSize))
        || (((UINTN)FspmUpd->FspmArchUpd.StackBase + FspmUpd->FspmArchUpd.StackSize) > BASE_4GB)
        || ((FspmUpd->FspmArchUpd.BootLoaderTolumSize % EFI_PAGE_SIZE) != 0)) {
        Status = EFI_INVALID_PARAMETER;
      }
    }
  } else if (ApiIdx == 5) {
    //
    // FspSiliconInit check
    //
    FspsUpd = (FSPS_UPD *)ApiParam;
    if (FspsUpd != NULL) {
      if (FspsUpd->FspUpdHeader.Signature != FSPS_UPD_SIGNATURE) {
        Status = EFI_INVALID_PARAMETER;
      }
    }
  }

  return Status;
}
