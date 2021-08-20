/** @file
  Machine check register initialization

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2016 Intel Corporation.

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

@par Specification
**/
#include <Library/BaseLib.h>
#include <Library/HobLib.h>
#include <Library/DebugLib.h>
#include <Library/CpuPlatformLib.h>
#include <Library/CpuCommonLib.h>
#include <Guid/HobList.h>
#include "MachineCheck.h"
#include "Features.h"


/**
  Initialize all the Machine-Check registers.

  @param[in] Buffer      - Pointer to private data. Not Used.
  @param[in] MchkEnable  - Enable or disable Mchk.
**/
VOID
InitializeMachineCheckRegisters (
  IN VOID    *Buffer,
  IN BOOLEAN MchkEnable
  , IN BOOLEAN IsFusaSupported
  )
{
  EFI_CPUID_REGISTER            CpuidRegisters;
  CPU_FEATURE                   Feature;
  CPU_IA32_MCG_CAP_LOW_REGISTER *MCGCap;
  UINT64                        MCGCapValue;
  UINT8                         Count;
  UINT8                         Index;
  UINT8                         StartIndex;
  UINT64                        Value;
  MSR_IA32_MC_CTL2_REGISTER     McCtl2Reg;

  if (!MchkEnable) {
    ///
    /// Do not enable MCHK
    ///
    return;
  }

  XmmInit ();

  AsmCpuid (
    CPUID_VERSION_INFO,
    &CpuidRegisters.RegEax,
    &CpuidRegisters.RegEbx,
    &CpuidRegisters.RegEcx,
    &CpuidRegisters.RegEdx
    );
  *(UINT32 *) (&Feature) = CpuidRegisters.RegEdx;

  if (Feature.MCE && Feature.MCA) {

    MCGCapValue = AsmReadMsr64 (MSR_IA32_MCG_CAP);
    MCGCap      = (CPU_IA32_MCG_CAP_LOW_REGISTER *) &MCGCapValue;
    Count       = (UINT8) MCGCap->Count;
    StartIndex  = 0;
    for (Index = StartIndex; Index < Count; Index++) {
      Value = (UINT64) -1;
      AsmWriteMsr64 (MSR_IA32_MC0_CTL + Index * 4, Value);
    }
    if (IsFusaSupported) {
      McCtl2Reg.Uint64 = AsmReadMsr64 (MSR_IA32_MC1_CTL2);
      McCtl2Reg.Bits.CorrectedErrorCountThreshold = 1;
      McCtl2Reg.Bits.CMCI_EN = 1;
      AsmWriteMsr64 (MSR_IA32_MC1_CTL2, McCtl2Reg.Uint64);

      McCtl2Reg.Uint64 = AsmReadMsr64 (MSR_IA32_MC2_CTL2);
      McCtl2Reg.Bits.CorrectedErrorCountThreshold = 1;
      McCtl2Reg.Bits.CMCI_EN = 1;
      AsmWriteMsr64 (MSR_IA32_MC2_CTL2, McCtl2Reg.Uint64);

      McCtl2Reg.Uint64 = AsmReadMsr64 (MSR_IA32_MC3_CTL2);
      McCtl2Reg.Bits.CorrectedErrorCountThreshold = 1;
      McCtl2Reg.Bits.CMCI_EN = 1;
      AsmWriteMsr64 (MSR_IA32_MC3_CTL2, McCtl2Reg.Uint64);
    }
    EnableMce ();
  }

  return;
}
