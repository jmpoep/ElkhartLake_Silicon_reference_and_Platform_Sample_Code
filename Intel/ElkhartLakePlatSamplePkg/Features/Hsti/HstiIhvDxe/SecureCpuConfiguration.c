/** @file
  This file contains the tests for the SecureCPUConfiguration bit

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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

#include "HstiIhvDxe.h"
#include <Register/VmdRegs.h>

#define   FIT_POINTER_MAX_LIMIT             (0xFFFFFFB0)
#define   FIT_POINTER_MIN_LIMIT             (0xFF000000)
#define   FIT_POINTER                       (0xFFFFFFC0)
#define   B_FIT_ENTRY_MASK                  (0xFFFFFF)
#define   B_PATCH_HEADER_VERSION_MASK       (0xFFFFFFFF)
#define   V_PATCH_HEADER_VERSION            (0x00000001)
#define   B_SMRR_MASK_MASK                  (0xFFFFF000)
#define   B_SMRR_WORK_MASK                  (0xFFFFFFFF)
#define   B_PRMRR_WORK_MASK                 (0xFFFFFFFF)
#define   B_VMD_DID_MASK                    (0xFFFF)

/**
  Run tests for SecureCPUConfiguration bit
**/
VOID
CheckSecureCpuConfiguration (
  VOID
  )
{
  EFI_STATUS                        Status;
  BOOLEAN                           Result;
  UINTN                             CpuNumber;
  UINTN                             CpuIndex;
  CPUID_VERSION_INFO_ECX            Ecx;
  UINT32                            TsegMB;
  UINT32                            Bgsm;
  UINT64                            SmrrBase;
  UINT64                            SmrrMask;
  UINT64                            MasterSmrrBase;
  UINT64                            MasterSmrrMask;
  UINT64                            PrmrrBase;
  UINT64                            PrmrrMask;
  BOOLEAN                           PrmrrEnabled;
  BOOLEAN                           PrmrrsConsistent;
  UINT64                            MasterPrmrrBase;
  UINT64                            MasterPrmrrMask;
  UINT64                            ConfigLock;
  MEMORY_PLATFORM_DATA_HOB          *MemInfo;
  UINT64                            SmmFeatureControl;
  MSR_IA32_FEATURE_CONTROL_REGISTER Ia32FeatureControlMsr;
  MSR_IA32_MTRRCAP_REGISTER         MtrrCapMsr;
  MSR_IA32_BIOS_SIGN_ID_REGISTER    Ia32BiosSignIdMsr;
  UINT64                            BiosDoneMsr;

  if ((mFeatureImplemented[0] & HSTI_BYTE0_SECURE_CPU_CONFIGURATION) == 0) {
    return;
  }

  Result = TRUE;
  TsegMB = PciSegmentRead32 (
             PCI_SEGMENT_LIB_ADDRESS (
               SA_SEG_NUM,
               SA_MC_BUS,
               SA_MC_DEV,
               SA_MC_FUN,
               R_SA_TSEGMB)
             );

  DEBUG ((DEBUG_INFO, "  CPU Security Configuration per CPU Number Tests\n"));

  CpuNumber = GetCpuNumber ();
  for (CpuIndex = 0; CpuIndex < CpuNumber; CpuIndex++) {
    DEBUG ((DEBUG_INFO, "    [CPU - 0x%x]\n", CpuIndex));

    DEBUG ((DEBUG_INFO, "      Microcode Update Revision Test\n"));
    ProcessorWriteMsr64 (CpuIndex, MSR_IA32_BIOS_SIGN_ID, 0);
    ProcessorCpuid (CpuIndex, CPUID_VERSION_INFO, NULL, NULL, NULL, NULL);
    Ia32BiosSignIdMsr.Uint64 = ProcessorReadMsr64 (CpuIndex, MSR_IA32_BIOS_SIGN_ID);
    if (Ia32BiosSignIdMsr.Bits.MicrocodeUpdateSignature == 0) {
      DEBUG ((DEBUG_INFO, "        Unexpected Status: Invalid Microcode Update Revision\n"));
      BuildAndAppendHstiStatusString (
        HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_1,
        HSTI_CPU_SECURITY_CONFIGURATION,
        HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_1
        );
      Result = FALSE;
    }

    DEBUG ((DEBUG_INFO, "      Sample Part Test\n"));

    if ((ProcessorReadMsr64 (CpuIndex, MSR_PLATFORM_INFO) & BIT27) != 0) {
      DEBUG ((DEBUG_INFO, "        Unexpected Status: This is a sample part\n"));

      BuildAndAppendHstiStatusString (
        HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_2,
        HSTI_CPU_SECURITY_CONFIGURATION,
        HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_2
        );
      Result = FALSE;
    }

    DEBUG ((DEBUG_INFO, "      IA32_FEATURE_CONTROL MSR Lock Test\n"));

    Ia32FeatureControlMsr.Uint64 = ProcessorReadMsr64 (CpuIndex, MSR_IA32_FEATURE_CONTROL);
    if (Ia32FeatureControlMsr.Bits.Lock == 0) {
      DEBUG ((DEBUG_INFO, "        Unexpected Status: This is a sample part\n"));

      BuildAndAppendHstiStatusString (
        HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_3,
        HSTI_CPU_SECURITY_CONFIGURATION,
        HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_3
        );
      Result = FALSE;
    }

    SmmFeatureControl = ProcessorReadMsr64 (CpuIndex, MSR_SMM_FEATURE_CONTROL);

    DEBUG ((DEBUG_INFO, "      SMM_CODE_CHK_EN Test\n"));

    if ((SmmFeatureControl & B_SMM_CODE_CHK_EN) == 0) {

      DEBUG ((DEBUG_INFO, "        Unexpected Status: SMM Code Fetch outside SMRAM detect feature disabled\n"));

      BuildAndAppendHstiStatusString (
        HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_4,
        HSTI_CPU_SECURITY_CONFIGURATION,
        HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_B
        );
      Result = FALSE;
    }

    DEBUG ((DEBUG_INFO, "      SMM_FEATURE_CONTROL MSR Lock Test\n"));

    if ((SmmFeatureControl & B_SMM_FEATURE_CONTROL_LOCK) == 0) {

      DEBUG ((DEBUG_INFO, "        Unexpected Status: SMM feature control MSR not locked\n"));

      BuildAndAppendHstiStatusString (
        HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_4,
        HSTI_CPU_SECURITY_CONFIGURATION,
        HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_4
        );
      Result = FALSE;
    }

    DEBUG ((DEBUG_INFO, "      FEATURE_CONFIG MSR  Lock Test\n"));

    ProcessorCpuid (CpuIndex, CPUID_VERSION_INFO, NULL, NULL, &Ecx.Uint32, NULL);
    if (Ecx.Bits.AESNI == 1) {
      if ((ProcessorReadMsr64 (CpuIndex, MSR_FEATURE_CONFIG) & B_MSR_FEATURE_CONFIG_LOCK_MASK) == 0) {
        DEBUG ((DEBUG_INFO, "        Unexpected Status: Feature control MSR not locked\n"));

        BuildAndAppendHstiStatusString (
          HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_5,
          HSTI_CPU_SECURITY_CONFIGURATION,
          HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_5
          );
        Result = FALSE;
      }
    }


    DEBUG ((DEBUG_INFO, "      BIOS DONE MSR set Test\n"));

    BiosDoneMsr = ProcessorReadMsr64 (CpuIndex, MSR_BIOS_DONE);

    if ((BiosDoneMsr & B_MSR_BIOS_DONE_ENABLE_IA_UNTRUSTED_MASK) == 0) {

      DEBUG ((DEBUG_INFO, "        Unexpected Status: BIOS Done MSR is not set\n"));

      BuildAndAppendHstiStatusString (
        HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_C,
        HSTI_CPU_SECURITY_CONFIGURATION,
        HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_C
        );
      Result = FALSE;
    }

    DEBUG((DEBUG_INFO, "      ConfigLock Test\n"));

    ConfigLock = ProcessorReadMsr64 (CpuIndex, MSR_LT_LOCK_MEMORY);
    if ((ConfigLock & BIT0) == 0) {
      DEBUG((DEBUG_INFO, "        Unexpected Status: ConfigLock not set\n"));

      BuildAndAppendHstiStatusString (
        HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_D,
        HSTI_CPU_SECURITY_CONFIGURATION,
        HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_D
        );
      Result = FALSE;
    }

  }

  DEBUG ((DEBUG_INFO, "      FIT Patch Support Test\n"));

  if (!IsValiduCodeEntry ()) {
    BuildAndAppendHstiStatusString (
      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_6,
      HSTI_CPU_SECURITY_CONFIGURATION,
      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_6
      );
    Result = FALSE;
  }

  DEBUG ((DEBUG_INFO, "    SMM Security Configuration Tests\n"));

  DEBUG ((DEBUG_INFO, "      TSEGMB Alignment Test\n"));

  MemInfo = NULL;
  MemInfo = GetFirstGuidHob (&gSiMemoryPlatformDataGuid);
  ASSERT (MemInfo != NULL);
  if (MemInfo == NULL) {
    return;
  }

  if (((TsegMB & B_SA_TSEGMB_TSEGMB_MASK) & (LShiftU64 (MemInfo->Data.TsegSize,20) - 1)) != 0) {
    DEBUG ((DEBUG_INFO, "        Unexpected Status: TSEGMB not size aligned, TSEG size: 0x%x\n",(LShiftU64 (MemInfo->Data.TsegSize,20) - 1)));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_9,
      HSTI_CPU_SECURITY_CONFIGURATION,
      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_9
      );
    Result = FALSE;
  }

  MasterSmrrBase = 0;
  MasterSmrrMask = 0;
  for (CpuIndex = 0; CpuIndex < CpuNumber; CpuIndex++) {
      DEBUG((DEBUG_INFO, "      SMRR1 Configuration per CPU Number Test\n"));
      DEBUG ((DEBUG_INFO, "    [CPU - 0x%x]\n", CpuIndex));

    DEBUG ((DEBUG_INFO, "      SMRR1 are supported Test\n"));

    MtrrCapMsr.Uint64 = ProcessorReadMsr64 (CpuIndex, MSR_IA32_MTRRCAP);
    if (MtrrCapMsr.Bits.SMRR == 0) {
      DEBUG ((DEBUG_INFO, "        Unexpected Status: SMRR1 not supported\n"));

      BuildAndAppendHstiStatusString (
        HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_A,
        HSTI_CPU_SECURITY_CONFIGURATION,
        HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_A
        );
      Result = FALSE;
    } else {
      DEBUG ((DEBUG_INFO, "      SMRR1 programmed consistently on all cores Test\n"));

      SmrrBase = ProcessorReadMsr64 (CpuIndex, MSR_IA32_SMRR_PHYSBASE);
      SmrrMask = ProcessorReadMsr64 (CpuIndex, MSR_IA32_SMRR_PHYSMASK);

      if (CpuIndex == 0) {
        MasterSmrrBase = SmrrBase;
        MasterSmrrMask = SmrrMask;
      } else {
        if ((SmrrBase != MasterSmrrBase) || (SmrrMask != MasterSmrrMask)) {
          DEBUG ((DEBUG_INFO, "        Unexpected Status: SMRR1 not programmed consistently across all cores\n"));

          BuildAndAppendHstiStatusString (
            HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_A,
            HSTI_CPU_SECURITY_CONFIGURATION,
            HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_A
            );
          Result = FALSE;
        }
      }

      DEBUG ((DEBUG_INFO, "      SMRR1 enabled/correct Test\n"));

      if (((SmrrMask & BIT11) == 0x0) ||
          ((SmrrMask & BIT9) != 0x0) ||
          ((SmrrBase & (BIT2 | BIT1 | BIT0)) != 0x6)) {
        DEBUG ((DEBUG_INFO, "        Unexpected Status: SMRR1 not enabled/correct\n"));

        BuildAndAppendHstiStatusString (
          HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_A,
          HSTI_CPU_SECURITY_CONFIGURATION,
          HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_A
          );
        Result = FALSE;
      }

      DEBUG ((DEBUG_INFO, "      SMRR1 and TSEGMB match Test\n"));

      DEBUG ((DEBUG_INFO, "        INFO: SMRR1:   0x%08x - 0x%08x\n", SmrrBase & (SmrrMask & B_SMRR_MASK_MASK), (UINT32) (~(SmrrMask & B_SMRR_MASK_MASK) + 1)));
      DEBUG ((DEBUG_INFO, "        INFO: TSEGMB: 0x%08x\n", TsegMB & B_SA_TSEGMB_TSEGMB_MASK));

      if ((SmrrBase & (SmrrMask & B_SMRR_MASK_MASK)) != (TsegMB & B_SA_TSEGMB_TSEGMB_MASK)) {

        DEBUG ((DEBUG_INFO, "        Unexpected Status: SMRR1 != TSEGMB\n"));

        BuildAndAppendHstiStatusString (
          HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_A,
          HSTI_CPU_SECURITY_CONFIGURATION,
          HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_A
          );
        Result = FALSE;
      }

      DEBUG ((DEBUG_INFO, "      SMRR1 size Test\n"));
      Bgsm = PciSegmentRead32 (
               PCI_SEGMENT_LIB_ADDRESS (
                 SA_SEG_NUM,
                 SA_MC_BUS,
                 SA_MC_DEV,
                 SA_MC_FUN,
                 R_SA_BGSM)
               );

      if ((UINT32) (~(SmrrMask & B_SMRR_MASK_MASK) + 1) !=
          ((Bgsm & B_SA_BGSM_BGSM_MASK) - (TsegMB & B_SA_TSEGMB_TSEGMB_MASK))) {
        DEBUG ((DEBUG_INFO, "        Unexpected Status: SMRR1 size != BGSM-TSEGMB\n"));

        BuildAndAppendHstiStatusString (
          HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_A,
          HSTI_CPU_SECURITY_CONFIGURATION,
          HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_A
          );
        Result = FALSE;
  }

      DEBUG ((DEBUG_INFO, "      SMRR1 Work Test\n"));

      if (MmioRead32 (SmrrBase & SmrrMask) != B_SMRR_WORK_MASK) {
        DEBUG ((DEBUG_INFO, "        Unexpected Status: SMRR1 not working, read succeeded\n"));


        BuildAndAppendHstiStatusString (
          HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_A,
          HSTI_CPU_SECURITY_CONFIGURATION,
          HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_A
          );
        Result = FALSE;
      }
    }
  }

  DEBUG ((DEBUG_INFO, "    Protected Range Microcode Range Register (PRMRR) Security Configuration per CPU Number Tests\n"));

  MasterPrmrrBase = 0;
  MasterPrmrrMask = 0;

  for (CpuIndex = 0; CpuIndex < CpuNumber; CpuIndex++) {
    DEBUG ((DEBUG_INFO, "    [CPU - 0x%x]\n", CpuIndex));

    DEBUG ((DEBUG_INFO, "      PRMRR supported Test\n"));

    if ((ProcessorReadMsr64 (CpuIndex, MSR_IA32_MTRRCAP) & B_IA32_MTRR_CAP_PRMRR_SUPPORT) == 0) {
      DEBUG ((DEBUG_INFO, "        Unexpected Status: PRMRR not supported by CPU skipping PRMRR tests\n"));
    } else{
      PrmrrBase = ProcessorReadMsr64 (CpuIndex, MSR_PRMRR_BASE_0);
      PrmrrMask = ProcessorReadMsr64 (CpuIndex, MSR_PRMRR_MASK);
      PrmrrEnabled = FALSE;

      if ((PrmrrMask & B_MSR_PRMRR_MASK_VLD_MASK) != 0) {
        PrmrrEnabled = TRUE;
      }

      if (PrmrrEnabled) {
        DEBUG ((DEBUG_INFO, "      PRMRR programmed consistently on all cores Test\n"));

        PrmrrsConsistent = TRUE;
        if (CpuIndex == 0) {
          MasterPrmrrBase = PrmrrBase;
          MasterPrmrrMask = PrmrrMask;
        } else {
          if ((PrmrrBase != MasterPrmrrBase) || (PrmrrMask != MasterPrmrrMask)) {
            PrmrrsConsistent = FALSE;
            DEBUG ((DEBUG_INFO, "        Unexpected Status: PRMRR's not programmed consistently\n"));

            BuildAndAppendHstiStatusString (
              HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_7,
              HSTI_CPU_SECURITY_CONFIGURATION,
              HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_7
              );
            Result = FALSE;
          }
        }

        DEBUG ((DEBUG_INFO, "      PRMRR correctly programmed & Memory Type initialized Tests\n"));
        if (PrmrrsConsistent) {
          if (((PrmrrMask & BIT9) != 0x0) ||
              ((PrmrrMask & B_MSR_PRMRR_PHYS_MASK_LOCK) == 0x0) ||
              ((PrmrrBase & (BIT2 | BIT1 | BIT0)) != 0x6)) {
            DEBUG ((DEBUG_INFO, "        Unexpected Status: PRMRR's not programmed correctly or  Memory Type not initialized\n"));

            BuildAndAppendHstiStatusString (
              HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_7,
              HSTI_CPU_SECURITY_CONFIGURATION,
              HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_7
              );
            Result = FALSE;
          }

          DEBUG ((DEBUG_INFO, "      PRMRR working Test\n"));

          if (MmioRead32 (PrmrrBase & PrmrrMask) != B_PRMRR_WORK_MASK) {
            DEBUG ((DEBUG_INFO, "        Unexpected Status: PRMRR's not working, able to read from range\n"));

            BuildAndAppendHstiStatusString (
              HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_7,
              HSTI_CPU_SECURITY_CONFIGURATION,
              HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_7
              );
            Result = FALSE;
          }
        }
      } else {
        DEBUG ((DEBUG_INFO, "        Unexpected Status: Processor Reserved Memory Range Register is Supported but Disabled\n"));

        BuildAndAppendHstiStatusString (
          HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_E,
          HSTI_CPU_SECURITY_CONFIGURATION,
          HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_E
          );
        Result = FALSE;
      }
    }
  }
  //
  // ALL PASS
  //
  if (Result) {
    Status = HstiLibSetFeaturesVerified (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               0,
               HSTI_BYTE0_SECURE_CPU_CONFIGURATION
               );
    CheckStatusForHstiLibSet (Status);
  }

  return;
}
