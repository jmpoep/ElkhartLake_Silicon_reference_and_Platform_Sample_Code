/** @file
 Platform Serial GOP Debug DXE UART Driver.

 @copyright
 INTEL CONFIDENTIAL
 Copyright 2016 - 2017 Intel Corporation.

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

#include <GopDebugDxe.h>


EFI_DEBUGPORT_PROTOCOL    mDebugPortInterface =
    {
    DebugPortReset,
    DebugPortWrite,
    DebugPortRead,
    DebugPortPoll
  };

EFI_STATUS
EFIAPI
DebugPortReset (
  IN EFI_DEBUGPORT_PROTOCOL   *This
  )
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
DebugPortWrite (
  IN EFI_DEBUGPORT_PROTOCOL   *This,
  IN UINT32                   Timeout,
  IN OUT UINTN                *BufferSize,
  OUT VOID                    *Buffer
  )
{
  SerialPortWrite (Buffer,*BufferSize);
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
DebugPortRead (
  IN EFI_DEBUGPORT_PROTOCOL   *This,
  IN UINT32                   Timeout,
  IN OUT UINTN                *BufferSize,
  IN VOID                     *Buffer
  )
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
DebugPortPoll (
  IN EFI_DEBUGPORT_PROTOCOL   *This
  )
{
  return EFI_SUCCESS;
}

/*++

  Routine Description:

  This is the standard EFI driver point for the Driver. This
    driver is responsible for setting up any platform specific policy or
    initialization information.

  Arguments:

  ImageHandle  -  Handle for the image of this driver.
  SystemTable  -  Pointer to the EFI System Table.

  Returns:

  EFI_SUCCESS  -  Policy decisions set.

--*/
EFI_STATUS
EFIAPI
InitializeGopDebug (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{

  EFI_STATUS    Status;

  Status = gBS->InstallProtocolInterface (
                &ImageHandle,
                &gEfiDebugPortProtocolGuid,
                EFI_NATIVE_INTERFACE,
                &mDebugPortInterface
                );
  return Status;
}
