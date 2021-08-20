/** @file
  UEFI Null Stall service implementation

Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

EFI_STATUS
EFIAPI
NullStall (
  IN UINTN            Microseconds
  );

/**
  Introduces a Null stall function to override bootservice stall function.

  @param  Microseconds           The number of microseconds to stall execution.

  @retval EFI_SUCCESS            Execution was stalled for NULL Seconds.
**/
EFI_STATUS
EFIAPI
NullStall (
  IN UINTN            Microseconds
  )
{
  return EFI_SUCCESS;
}

/**
Entry point of the NULL STALL DXE driver.

@param ImageHandle    ImageHandle
@param SystemTable    Pointer to System Table

@return EFI_STATUS

**/
EFI_STATUS
EFIAPI
NullStallEntryPoint(
  IN EFI_HANDLE               ImageHandle,
  IN EFI_SYSTEM_TABLE         *SystemTable
  )
{

  ///
  /// Hook the BootTime service table Stall Function with Dummy Stall
  ///
    SystemTable->BootServices->Stall = NullStall;
  return EFI_SUCCESS;
}
