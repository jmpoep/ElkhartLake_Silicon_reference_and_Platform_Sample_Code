/** @file
  Header file for FSP-M Arch Config PPI

 @copyright
  Copyright (c) 2018 - 2019, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials are licensed and made available under
  the terms and conditions of the BSD License which accompanies this distribution.
  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef _FSPM_ARCH_CONFIG_PPI_H_
#define _FSPM_ARCH_CONFIG_PPI_H_

///
/// Global ID for the FSPM_ARCH_CONFIG_PPI.
///
#define FSPM_ARCH_CONFIG_GUID \
  { \
    0x824d5a3a, 0xaf92, 0x4c0c, { 0x9f, 0x19, 0x19, 0x52, 0x6d, 0xca, 0x4a, 0xbb } \
  }

///
/// This PPI provides FSP-M Arch Config PPI.
///
typedef struct {
  UINT8         Revision;
  UINT8         Reserved[3];
  VOID          *NvsBufferPtr;
  UINT32        BootLoaderTolumSize;
  UINT8         Reserved1[4];
} FSPM_ARCH_CONFIG_PPI;

extern EFI_GUID gFspmArchConfigPpiGuid;

#endif // _FSPM_ARCH_CONFIG_PPI_H_
