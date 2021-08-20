/** @file
  This is an implementation of the PUPDR include file.

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
#ifndef _PUPDR_DXE_H_
#define _PUPDR_DXE_H_

#include <Uefi.h>
#include <Library/IoLib.h>
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Protocol/AcpiTable.h>
#include <IndustryStandard/Acpi.h>
#include <SetupVariable.h>
#include <Rsci.h>
#include <Emt1.h>
#include <Register/PmcRegs.h>
#include <Library/PmcLib.h>
#include <Library/PchCycleDecodingLib.h>

VOID
PupdrUpdateTables (
  IN OUT EFI_ACPI_COMMON_HEADER  *Table
  );

VOID
PupdrGetWakeSource (
  OUT UINT8 *WakeSource
  );

VOID
PupdrGetResetSource (
  OUT UINT8 *ResetSource,
  OUT UINT8 *ResetType
  );

VOID
PupdrGetShutdownSource (
  OUT UINT8 *ShutdownSource
  );

#endif
