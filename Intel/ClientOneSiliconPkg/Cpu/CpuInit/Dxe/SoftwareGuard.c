/** @file
  Code which supports Software Guard Extensions DXE component

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#include <Library/BaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/CpuPlatformLib.h>
#include "CpuInitDxe.h"
#include <Protocol/CpuNvsArea.h>
#include <Library/SoftwareGuardLib.h>
#include <Library/CpuCommonLib.h>

/**
 Code to update SGX Global NVS variable in EPC.ASL
**/
VOID
UpdateSgxNvs (
  VOID
  )
{
  EFI_STATUS                                           Status;
  CPU_NVS_AREA_PROTOCOL                                *CpuNvsAreaProtocol;
  CPUID_INTEL_SGX_CAPABILITIES_RESOURCES_SUB_LEAF_EAX  Eax;
  CPUID_INTEL_SGX_CAPABILITIES_RESOURCES_SUB_LEAF_EBX  Ebx;
  CPUID_INTEL_SGX_CAPABILITIES_RESOURCES_SUB_LEAF_ECX  Ecx;
  CPUID_INTEL_SGX_CAPABILITIES_RESOURCES_SUB_LEAF_EDX  Edx;

  DEBUG ((DEBUG_INFO, "\n UpdateSgxNvs started \n"));

  ///
  /// Locate Cpu Nvs
  ///
  Status = gBS->LocateProtocol (&gCpuNvsAreaProtocolGuid, NULL, (VOID **) &CpuNvsAreaProtocol);
  if (Status != EFI_SUCCESS) {
    DEBUG ((DEBUG_ERROR, "\n UpdateSgxNvs: Unable to Locate Cpu Nvs Protocol, EPC device will not be available\n"));
    return;
  }

  CpuNvsAreaProtocol->Area->SgxStatus      = 0;
  CpuNvsAreaProtocol->Area->EpcBaseAddress = 0;
  CpuNvsAreaProtocol->Area->EpcLength      = 1;

  /**
    Check if all of these conditions are met
    - 1: EnableSgx policy was set to enable
    - 2: SGX feature is supported by CPU
    - 3: PRM was successfully allocated and PRMRRs were set
    - 4: SGX IA32_FEATURE_CONTROL MSR(3Ah) [18] == 1
  **/
  if (IsSgxSupported () && IsPrmrrAlreadySet () && IsSgxFeatureCtrlSet ()) {
    //
    // Check if SGX is present
    //
    if (!IsSgxPresent ()) {
      DEBUG ((DEBUG_WARN, "\n SGX is not present\n"));

    } else {
      //
      // Read CPUID.(EAX=0x12, ECX=0x2) to get EPC Base and Size
      //
      AsmCpuidEx (
        CPUID_INTEL_SGX,
        CPUID_INTEL_SGX_CAPABILITIES_RESOURCES_SUB_LEAF,
        &Eax.Uint32,
        &Ebx.Uint32,
        &Ecx.Uint32,
        &Edx.Uint32
        );

      //
      // Check if the first sub-leaf is a valid EPC section
      //
      if ((Eax.Bits.SubLeafType) != 0x1) {
        DEBUG ((DEBUG_WARN, "\n SGX sub-leaf for EPC is invalid\n"));
        return;
      }
      DEBUG ((DEBUG_INFO, "\n SGX is ENABLED\n"));
      CpuNvsAreaProtocol->Area->EpcBaseAddress = LShiftU64 ((UINT64) (Ebx.Bits.HighAddressOfEpcSection), 32) + LShiftU64 ((UINT64) (Eax.Bits.LowAddressOfEpcSection), 12);
      CpuNvsAreaProtocol->Area->EpcLength      = LShiftU64 ((UINT64) (Edx.Bits.HighSizeOfEpcSection), 32) + LShiftU64 ((UINT64) (Ecx.Bits.LowSizeOfEpcSection), 12);
      CpuNvsAreaProtocol->Area->SgxStatus      = TRUE;
    }
  } else {
    DEBUG ((DEBUG_WARN, "\n SGX is not supported\n"));
  }
  DEBUG ((DEBUG_INFO, "CpuNvsAreaProtocol->Area->SgxStatus      = 0x%X\n",      CpuNvsAreaProtocol->Area->SgxStatus));
  DEBUG ((DEBUG_INFO, "CpuNvsAreaProtocol->Area->EpcBaseAddress = 0x%016llX\n", CpuNvsAreaProtocol->Area->EpcBaseAddress));
  DEBUG ((DEBUG_INFO, "CpuNvsAreaProtocol->Area->EpcLength      = 0x%016llX\n", CpuNvsAreaProtocol->Area->EpcLength));
  return;
}
