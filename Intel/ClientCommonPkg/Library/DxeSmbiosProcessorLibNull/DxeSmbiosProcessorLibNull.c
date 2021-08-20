/** @file
  Null instance of Smbios Processor Information Library which produces Smbios type 4 and 7 tables.

Copyright (c) 2016, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under 
the terms and conditions of the BSD License that accompanies this distribution.  
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.                                          

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <PiDxe.h>

/**
  Add Smbios Cache information (type 7) table and Processor information (type 4) table
  using the HOB info from Silicon.

  This is a Null instance.

  @retval EFI_SUCCESS       The entry point is executed successfully.

**/
EFI_STATUS
EFIAPI
AddSmbiosProcessorAndCacheTables (
  VOID
  )
{
  return EFI_SUCCESS;
}
