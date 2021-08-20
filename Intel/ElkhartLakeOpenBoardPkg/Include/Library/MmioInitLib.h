/** @file

Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Uefi.h>

#ifndef __MMIO_INIT_LIB_H__
#define __MMIO_INIT_LIB_H__

/**
  Initialize MMIO ranges

  @retval EFI_SUCCESS    The function completed successfully
**/
EFI_STATUS
MmioInit (
  VOID
  );

#endif
