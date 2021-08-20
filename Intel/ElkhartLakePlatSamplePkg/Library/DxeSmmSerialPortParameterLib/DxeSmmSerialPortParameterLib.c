/** @file
  Dxe/Smm Serial Port Parameter library instance.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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

#include <PiDxe.h>
#include <Library/UefiLib.h>
#include <Library/HobLib.h>
#include <Library/PcdLib.h>
#include <Library/SerialPortParameterLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Setup.h>

GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN    mSerialPortBaudRateInited = FALSE;
GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN    mDebugInterfacesInited = FALSE;
GLOBAL_REMOVE_IF_UNREFERENCED UINT32     mSerialPortBaudRate = 0xffffffff;
GLOBAL_REMOVE_IF_UNREFERENCED UINT8      mDebugInterfaces = 0xff;

/**
  The constructor function initializes the Serial Port Parameter Library

  @param[in]  ImageHandle  The firmware allocated handle for the EFI image.
  @param[in]  SystemTable  A pointer to the EFI System Table.

  @retval EFI_SUCCESS      The constructor always returns EFI_SUCCESS.
**/
EFI_STATUS
EFIAPI
DxeSmmSerialPortParameterLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_PEI_HOB_POINTERS         Hob;
  DEBUG_CONFIG_DATA_HOB        *DebugConfigData;
  UINT8                        DebugInterfaces;
  UINT32                       SerialPortBaudRate;

  DebugInterfaces = 0;

  if (gST != NULL) {
    Hob.Guid = GetFirstGuidHob (&gDebugConfigHobGuid);
    if (Hob.Guid != NULL) {
      DebugConfigData = (DEBUG_CONFIG_DATA_HOB *) GET_GUID_HOB_DATA (Hob.Guid);
      if (DebugConfigData != NULL) {
        switch (DebugConfigData->SerialDebugBaudRate) {
        case 3:
          SerialPortBaudRate = 9600;
          break;
        case 4:
          SerialPortBaudRate = 19200;
          break;
        case 6:
          SerialPortBaudRate = 57600;
          break;
        default:
          SerialPortBaudRate = 115200;
        }
        mSerialPortBaudRate = SerialPortBaudRate;
        mSerialPortBaudRateInited = TRUE;

        if (DebugConfigData->RamDebugInterface)      { DebugInterfaces |= STATUS_CODE_USE_RAM; }
        if (DebugConfigData->UartDebugInterface)     { DebugInterfaces |= STATUS_CODE_USE_ISA_SERIAL; }
        if (DebugConfigData->Usb3DebugInterface)     { DebugInterfaces |= STATUS_CODE_USE_USB3; }
        if (DebugConfigData->SerialIoDebugInterface) { DebugInterfaces |= STATUS_CODE_USE_SERIALIO; }
        if (DebugConfigData->TraceHubDebugInterface) { DebugInterfaces |= STATUS_CODE_USE_TRACEHUB; }
        mDebugInterfaces = DebugInterfaces;
        mDebugInterfacesInited = TRUE;
      }
    }
  }

  return EFI_SUCCESS;
}

/**
  Returns the serial port baud rate.

  @return  Baud rate of serial port.

**/
UINT32
EFIAPI
GetSerialPortBaudRate (
  VOID
  )
{
  if (mSerialPortBaudRateInited) {
    return mSerialPortBaudRate;
  }

  return PcdGet32 (PcdSerialBaudRate);
}

/**
  Sets the serial port baud rate value.

  @param[in] BaudRate     Baud rate value to be set.

  @retval  TRUE           The baud rate of serial port was sucessfully set.
  @retval  FALSE          The baud rate of serial port could not be set.

**/
BOOLEAN
EFIAPI
SetSerialPortBaudRate (
  IN UINT32        BaudRate
  )
{
  return FALSE;
}

/**
  Returns enabled debug interfaces.

  @retval  Enabled debug interfaces bitmask.
**/
UINT8
GetDebugInterface (
  VOID
  )
{
  if (mDebugInterfacesInited) {
    return mDebugInterfaces;
  }

  return PcdGet8 (PcdStatusCodeFlags);
}

/**
  Sets debug interfaces.

  @param[in] DebugInterface  Debug interfaces to be set.
**/
VOID
SetDebugInterface (
  IN UINT8 DebugInterface
  )
{
  return;
}
