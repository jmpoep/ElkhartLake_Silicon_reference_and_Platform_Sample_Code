/** @file

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Protocol/SerialIo.h>
#include <Library/HobLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/SerialIoUartDebugPropertyPcdLib.h>
#include <Setup.h>


/**
  Returns UART's attributes

  @param[in,out]  UartAttributes   Uart Attributes
**/
VOID
SerialIoUartDebugGetAttributes (
  IN OUT SERIAL_IO_UART_ATTRIBUTES *UartAttributes
  )
{
  EFI_PEI_HOB_POINTERS         Hob;
  EFI_HOB_GUID_TYPE            *GuidHob;
  DEBUG_CONFIG_DATA_HOB        *DebugConfigData;

  //
  // Use PeiServicesGetHobList() to check HobList is ready or not.
  //
  PeiServicesGetHobList ((VOID **) &Hob.Raw);

  if (Hob.Raw != NULL) {
    GuidHob = NULL;
    DebugConfigData = NULL;
    GuidHob = GetFirstGuidHob (&gDebugConfigHobGuid);
    if (GuidHob != NULL) {
      DebugConfigData = (DEBUG_CONFIG_DATA_HOB *) GET_GUID_HOB_DATA (GuidHob);
      if (DebugConfigData != NULL) {
        UartAttributes->BaudRate = DebugConfigData->SerialIoUartDebugBaudRate;
        UartAttributes->DataBits = DebugConfigData->SerialIoUartDebugDataBits;
        UartAttributes->StopBits = DebugConfigData->SerialIoUartDebugStopBits;
        UartAttributes->Parity   = DebugConfigData->SerialIoUartDebugParity;
        UartAttributes->AutoFlow = DebugConfigData->SerialIoUartDebugFlowControl;
        return;
      }
    }
  }
  //
  // Unable to obtain data from the HOB, returning data from Pcd
  //
  SerialIoUartDebugPcdGetAttributes (UartAttributes);
}

/**
  Returns Serial Io UART Controller Number used in Debug mode

  @retval  ControllerNumber   UART Controller Number
**/
UINT8
SerialIoUartDebugGetControllerNumber (
  VOID
  )
{
  EFI_PEI_HOB_POINTERS         Hob;
  EFI_HOB_GUID_TYPE            *GuidHob;
  DEBUG_CONFIG_DATA_HOB        *DebugConfigData;
  STATIC UINT8                 ControllerNumber = 0xFF;

  if (ControllerNumber != 0xFF) {
    return ControllerNumber;
  }

  //
  // Use PeiServicesGetHobList() to check HobList is ready or not.
  //
  PeiServicesGetHobList ((VOID **) &Hob.Raw);

  if (Hob.Raw != NULL) {
    GuidHob = NULL;
    DebugConfigData = NULL;
    GuidHob = GetFirstGuidHob (&gDebugConfigHobGuid);
    if (GuidHob != NULL) {
      DebugConfigData = (DEBUG_CONFIG_DATA_HOB *) GET_GUID_HOB_DATA (GuidHob);
      if (DebugConfigData != NULL) {
        ControllerNumber = DebugConfigData->SerialIoUartDebugControllerNumber;
      }
    }
  }

  //
  // Unable to obtain data from the HOB, returning data from PcdLib
  //
  if (ControllerNumber == 0xFF) {
    return SerialIoUartDebugPcdGetControllerNumber ();
  }

  return ControllerNumber;
}

/**
  Returns Serial Io UART MMIO Base Address

  @retval  MMIO Base Address by default in PCI Mode
**/
UINT32
SerialIoUartDebugGetPciDefaultMmioBase (
  VOID
  )
{
  return SerialIoUartDebugPcdGetPciDefaultMmioBase ();
}

