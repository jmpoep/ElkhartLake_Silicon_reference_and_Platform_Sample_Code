/** @file
  Header file for the Smm platform driver.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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

#ifndef _SMM_PLATFORM_H_
#define _SMM_PLATFORM_H_

#include "Platform.h"
#include "SetupVariable.h"
#include <Uefi/UefiBaseType.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>
#include <Library/S3BootScriptLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/DxeSmmScriptLib/DxeSmmScriptLib.h>
#include <Library/ReportStatusCodeLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Protocol/EcAccess.h>
#include <PlatformBoardType.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/SmmBase2.h>
#include <Protocol/SmmPowerButtonDispatch2.h>
#include <Protocol/SmmSxDispatch2.h>
#include <Protocol/SmmSwDispatch2.h>
#include <Protocol/SmmIoTrapDispatch2.h>
#include <Protocol/SmmUsbDispatch2.h>
#if FixedPcdGetBool(PcdCapsuleEnable) == 1
#include <Protocol/SmmEndOfDxe.h>
#endif
#include <SetupVariable.h>
#include <Library/EcMiscLib.h>
#include "Library/DxeSmmAcpiCustomLib.h"
#include <Protocol/PlatformNvsArea.h>
#include <IndustryStandard/Pci30.h>
#include <Protocol/PchEspiSmiDispatch.h>
#include <Library/EcTcssLib.h>

//
// Related data structures definition
//
typedef struct _EFI_ACPI_SMM_DEV {
  EFI_PHYSICAL_ADDRESS   RuntimeScriptTableBase;
  UINT32                 BootScriptSaved;
} EFI_ACPI_SMM_DEV;


//
// Callback function prototypes
//
EFI_STATUS
EFIAPI
EnableAcpiCallback (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  CONST VOID                    *DispatchContext,
  IN  OUT VOID                      *CommBuffer  OPTIONAL,
  IN  UINTN                         *CommBufferSize  OPTIONAL
  );

EFI_STATUS
EFIAPI
DisableAcpiCallback (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  CONST VOID                    *DispatchContext,
  IN  OUT VOID                      *CommBuffer  OPTIONAL,
  IN  UINTN                         *CommBufferSize  OPTIONAL
  );

EFI_STATUS
EFIAPI
PowerButtonCallback (
  IN  EFI_HANDLE                              DispatchHandle,
  IN  CONST VOID                              *DispatchContext,
  IN  OUT VOID                                *CommBuffer  OPTIONAL,
  IN  UINTN                                   *CommBufferSize  OPTIONAL
  );

EFI_STATUS
EFIAPI
S3SleepEntryCallBack (
  IN  EFI_HANDLE                              DispatchHandle,
  IN  CONST VOID                              *DispatchContext,
  IN  OUT VOID                                *CommBuffer  OPTIONAL,
  IN  UINTN                                   *CommBufferSize  OPTIONAL
  );

EFI_STATUS
EFIAPI
S4SleepEntryCallBack (
  IN  EFI_HANDLE                              DispatchHandle,
  IN  CONST VOID                              *DispatchContext,
  IN  OUT VOID                                *CommBuffer  OPTIONAL,
  IN  UINTN                                   *CommBufferSize  OPTIONAL
  );

EFI_STATUS
EFIAPI
S5SleepEntryCallBack (
  IN  EFI_HANDLE                              DispatchHandle,
  IN  CONST VOID                              *DispatchContext,
  IN  OUT VOID                                *CommBuffer  OPTIONAL,
  IN  UINTN                                   *CommBufferSize  OPTIONAL
  );

EFI_STATUS
IntelUsb20SmiHandler (
  IN  EFI_HANDLE                              DispatchHandle,
  IN  EFI_SMM_USB_REGISTER_CONTEXT            *DispatchContext
);

VOID
EFIAPI
eSpiEcSmiCallback (
  IN  EFI_HANDLE                              DispatchHandle
  );
#endif

