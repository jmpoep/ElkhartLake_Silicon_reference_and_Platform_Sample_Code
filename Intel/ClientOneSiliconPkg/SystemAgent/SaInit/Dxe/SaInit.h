/** @file
  Header file for SA Common Initialization Driver.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/
#ifndef _SA_INITIALIZATION_DRIVER_H_
#define _SA_INITIALIZATION_DRIVER_H_

#include <Uefi.h>
#include <IndustryStandard/Acpi.h>
#include <IndustryStandard/Pci.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/UefiLib.h>
#include <Library/IoLib.h>
#include <Library/PciCf8Lib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/S3BootScriptLib.h>
#include <Library/SaPlatformLib.h>
#include <Guid/EventGroup.h>
#include <CpuRegs.h>
#include <Library/CpuPlatformLib.h>
#include <Protocol/SaPolicy.h>
#include <SaConfigHob.h>
#if FixedPcdGetBool(PcdITbtEnable) == 1
#include <TcssDataHob.h>
#endif

extern SA_POLICY_PROTOCOL              *mSaPolicy;
extern SA_CONFIG_HOB                   *SaConfigHob;

typedef struct {
  UINT64  BaseAddr;
  UINT32  Offset;
  UINT32  AndMask;
  UINT32  OrMask;
} BOOT_SCRIPT_REGISTER_SETTING;

/**
  SystemAgent Initialization Common Function.

  @retval EFI_SUCCESS   - Always.
**/
VOID
SaInitEntryPoint (
  VOID
  );

/**
  Common function locks the PAM register as part of the SA Security requirements.

  @retval EFI_SUCCESS   - Always.
**/
VOID
SaPamLock (
  VOID
  );
#endif
