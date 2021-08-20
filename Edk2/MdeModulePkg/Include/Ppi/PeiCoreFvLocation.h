/** @file

  Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/


#ifndef _EFI_PEI_CORE_FV_LOCATION_H_
#define _EFI_PEI_CORE_FV_LOCATION_H_
//
// This file is created for CCEO-0007: RoyalParkOverrideContent
//
typedef struct _EFI_PEI_CORE_FV_LOCATION_PPI EFI_PEI_CORE_FV_LOCATION_PPI;

///
/// This PPI provides location of EFI PeiCoreFv.
///
struct _EFI_PEI_CORE_FV_LOCATION_PPI {
  UINT32         PeiCoreFvLocation;
};

extern EFI_GUID gEfiPeiCoreFvLocationPpiGuid;

#endif // _EFI_PEI_CORE_FV_LOCATION_H_