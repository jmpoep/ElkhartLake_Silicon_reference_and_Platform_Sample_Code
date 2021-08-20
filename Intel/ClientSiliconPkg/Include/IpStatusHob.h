/** @file
  Header file for IP Status Hob

 @copyright
  Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials are licensed and made available under
  the terms and conditions of the BSD License which accompanies this distribution.
  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef _IP_STATUS_HOB_H_
#define _IP_STATUS_HOB_H_

#include <Pi/PiHob.h>

#pragma pack(1)
///
/// IP Status Hob Structure
///
typedef struct {
  EFI_HOB_GUID_TYPE  EfiHobGuidType; // offset  0: Guid for IP_STATUS_HOB for all IPs
  EFI_GUID           Guid;           // offset 24: Guid for specific IP
  UINT32             Status;         // offset 40: IP status
} IP_STATUS_HOB;                     // total size = 44 bytes per IP

#pragma pack()

#endif // _IP_STATUS_HOB_H_
