/** @file
  Header file for Platform Initialization Driver.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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

#ifndef _PLATFORM_SETUP_DRIVER_H_
#define _PLATFORM_SETUP_DRIVER_H_

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Library/HobLib.h>
#include <Protocol/MpService.h>
#include <IndustryStandard/Pci22.h>
#include <Protocol/Ps2Policy.h>
#include <Protocol/MemInfo.h>

#include <Protocol/PciIo.h>
#include <Protocol/DiskInfo.h>
#include <Protocol/DevicePath.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/IdeControllerInit.h>

typedef UINT16  STRING_REF;

#include <Guid/GlobalVariable.h>
#include <Guid/HobList.h>

#include <Protocol/VariableWrite.h>
#include <Library/CpuPlatformLib.h>

#include <Protocol/SaPolicy.h>
#include <Protocol/DxePolicyUpdateProtocol.h>
#include <Register/Cpuid.h>
#include <Register/Msr.h>
#include <CpuAccess.h>
#include <Platform.h>
#include <Configuration.h>
#include <SetupVariable.h>
#include <PlatformBoardId.h>
#include <Library/CpuMailboxLib.h>

//
// Prototypes
//
EFI_STATUS
EFIAPI
PlatformSetupEntry (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  );

EFI_STATUS
EFIAPI
Ps2InitHardware (
  IN  EFI_HANDLE  Handle
  );

EFI_STATUS
GetStringFromToken (
  IN  EFI_GUID     *ProducerGuid,
  IN  STRING_REF   Token,
  OUT CHAR16       **String
  );

CHAR16 *
GetStringById (
  IN  STRING_REF   Id,
  EFI_HII_HANDLE   StringPackHandle
  );

VOID
SwapEntries (
  IN  CHAR8 *Data
  );

VOID
AsciiToUnicode (
  IN    CHAR8     *AsciiString,
  IN    CHAR16    *UnicodeString
  );

VOID
SetupPlatformPolicies (
  IN OUT  MEM_INFO_PROTOCOL    *MemoryInfoProtocol
  );

//
// Global externs
//
extern EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *mPciRootBridgeIo;

#endif
