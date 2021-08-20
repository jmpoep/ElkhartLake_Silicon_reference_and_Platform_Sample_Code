/*++

Copyright (c) 2017 Intel Corporation. All rights reserved
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  MonoStatusCodeNull.c

Abstract:

  Contains Platform specific implementations required to use status codes.

--*/

#include <Library/PeiServicesLib.h>

EFI_STATUS
EFIAPI
InstallMonoStatusCode (
  IN EFI_FFS_FILE_HEADER       *FfsHeader,
  IN CONST EFI_PEI_SERVICES    **PeiServices
  )
/*++

Routine Description:

  Install the PEIM.  Initialize listeners, publish the PPI and HOB for PEI and
  DXE use respectively.

Arguments:

  FfsHeader    -  FV this PEIM was loaded from.
  PeiServices  -  General purpose services available to every PEIM.

Returns:

  EFI_SUCCESS  -  The function always returns success.

--*/
{
  return EFI_SUCCESS;
}