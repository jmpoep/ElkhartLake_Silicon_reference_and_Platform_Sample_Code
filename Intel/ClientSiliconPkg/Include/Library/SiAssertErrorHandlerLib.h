/** @file
  Header file for Si Assert Error Handler Lib

Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef _SI_ASSERT_ERROR_HANDLER_LIB_H_
#define _SI_ASSERT_ERROR_HANDLER_LIB_H_

/**
  Slicon assertion error handling, creating HOB for error status and
  handling erors according to what types of mode.

  @param[in] Status      The return status.
  @param[in] HobGuid     The GUID to build a guid hob.

  @retval None.
**/
VOID
SiAssertErrorHandler (
  IN  CONST CHAR8 *FileName,
  IN  UINTN       LineNumber,
  IN  EFI_STATUS  Status,
  IN  EFI_GUID    *HobGuid
  );

#define SI_ASSERT_EFI_ERROR(Status, HobGuid) SiAssertErrorHandler (__FILE__, __LINE__, Status, HobGuid)

#endif // _SI_ASSERT_ERROR_HANDLER_LIB_H_
