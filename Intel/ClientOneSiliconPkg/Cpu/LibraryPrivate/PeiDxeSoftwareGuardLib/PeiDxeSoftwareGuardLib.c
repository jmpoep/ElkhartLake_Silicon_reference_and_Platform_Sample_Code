/** @file
  Software Guard Extensions Library for PEI and DXE modules

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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

#include <Uefi.h>
#include <PiPei.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/HobLib.h>
#include <Library/SoftwareGuardLib.h>
#include <Library/CpuPlatformLib.h>
#include <Library/CpuMailboxLib.h>
#include <Register/Msr.h>
#include "CpuDataStruct.h"
#include <CpuRegs.h>
#include <CpuInitDataHob.h>
#include <Library/CpuCommonLib.h>
#include <TxtInfoHob.h>
#include <Library/TxtPeiLib.h>
#include <Library/ConfigBlockLib.h>
#include <Register/Cpuid.h>
//
// @todo Add workaround for GCC build, Will remove it when GCC build done
//
#ifdef __GNUC__
extern CPU_INIT_DATA_HOB            *mCpuInitDataHob;
#else
GLOBAL_REMOVE_IF_UNREFERENCED CPU_INIT_DATA_HOB            *mCpuInitDataHob;
#endif

GLOBAL_REMOVE_IF_UNREFERENCED CPU_SGX_CONFIG               *mCpuSgxConfig              = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED CPU_SECURITY_PREMEM_CONFIG   *mCpuSecurityPreMemConfig   = NULL;

///
/// Function declarations
///

/**
  Check if SGX patch can be loaded. Patch can be loaded if all
  of these conditions are met
  - 1: EnableSgx policy was set to enable
  - 2: SGX feature is supported by CPU
  - 3: PRM was successfully allocated and PRMRRs were set

  @dot
    digraph G {
      subgraph cluster_c0 {
        node [shape = box];
          b1[label="Return TRUE" fontsize=12 style=filled color=lightblue];
          b2[label="Return FALSE" fontsize=12 style=filled color=lightblue];

        node [shape = ellipse];
          e1[label="Start" fontsize=12 style=filled color=lightblue];
          e2[label="End" fontsize=12 style=filled color=lightblue];

        node [shape = diamond,style=filled,color=lightblue];
          d1[label="Are the conditions \n mCpuSecurityPreMemConfig->EnableSgx,\n IsSgxSupported (),\n and IsPrmrrAlreadySet ()\n all equal to TRUE" fontsize=12];

        label = "IsSgxPreconditionsMet Flow"; fontsize=15; fontcolor=black; color=lightblue;
        e1 -> d1
        d1 -> b1 [label="Yes" fontsize=9]
        d1 -> b2 [label="No" fontsize=9]
        b1 -> e2
        b2 -> e2

      }
    }
  @enddot

  @retval TRUE  if all conditions are met
  @retval FALSE if at least one of the conditions is not met
**/
BOOLEAN
IsSgxPreconditionsMet (
  VOID
  )
{
  return (mCpuSecurityPreMemConfig->EnableSgx && IsSgxSupported () && IsPrmrrAlreadySet ());
}

/**
  Return TRUE if SGX in Feature Control MSR was set
  IA32_FEATURE_CONTROL MSR(3Ah) [18] == 1

  @retval TRUE if SGX in Feature Control MSR was set.
  @retval FALSE if SGX in Feature Control MSR was not set.
**/
BOOLEAN
IsSgxFeatureCtrlSet (
  VOID
  )
{
  MSR_IA32_FEATURE_CONTROL_REGISTER Msr;

  Msr.Uint64 = AsmReadMsr64 (MSR_IA32_FEATURE_CONTROL);

  return (BOOLEAN) (Msr.Bits.SgxEnable == 1);
}

/**
  Update Software Guard Epochs

  @dot
    digraph G {
      subgraph cluster_c0 {
        node [shape = box];
          b1[label="[Debug] EpochUpdate: EPOCH0 and EPOCH1" fontsize=12 style=filled color=lightblue];
          b2[label="Update the value of SgxEpoch0 to MSR_SKYLAKE_SGXOWNER0" fontsize=12 style=filled color=lightblue];
          b3[label="Update the value of SgxEpoch1 to MSR_SKYLAKE_SGXOWNER1" fontsize=12 style=filled color=lightblue];

        node [shape = ellipse];
          e1[label="Start" fontsize=12 style=filled color=lightblue];
          e2[label="End" fontsize=12 style=filled color=lightblue];

        node [shape = diamond,style=filled,color=lightblue];
          d1[label="IsSgxPresent" fontsize=12];

        label = "EpochUpdate Flow"; fontsize=15; fontcolor=black; color=lightblue;
        e1 -> d1
        d1 -> e2 [label="Yes" fontsize=9]
        d1 -> b1 [label="No" fontsize=9]
        b1 -> b2
        b2 -> b3
        b3 -> e2

      }
    }
  @enddot

 **/
VOID
EpochUpdate (
  VOID
  )
{
  DEBUG((DEBUG_INFO, "EpochUpdate Start\n"));

  //
  // Check if SGX wasn't already enabled by reading CPUID.(EAX=12,ECX=0):EAX[0]
  // If SGX wasn't enabled yet EAX==0, otherwise EAX==1
  //
  if (!IsSgxPresent ()) {
    DEBUG ((DEBUG_INFO, "EpochUpdate: Updating SgxEpoch0: %016llx\n",mCpuSgxConfig->SgxEpoch0));
    DEBUG ((DEBUG_INFO, "EpochUpdate: Updating SgxEpoch1: %016llx\n",mCpuSgxConfig->SgxEpoch1));
    AsmWriteMsr64 (MSR_SKYLAKE_SGXOWNER0, mCpuSgxConfig->SgxEpoch0);
    AsmWriteMsr64 (MSR_SKYLAKE_SGXOWNER1, mCpuSgxConfig->SgxEpoch1);
  }
}

/**
  Activation of SGX feature after patch load via BIOS_UPGD_TRIG (MSR 0x7a)
**/
VOID
ActivateSgxFeature (
  VOID
  )
{
  BOOLEAN  IsBspInt;

  IsBspInt = IsBsp ();
  ///
  /// If BIT0 in MSR_BIOS_UPGD_TRIG is set then SGX is pending activation
  ///
  if (AsmReadMsr64 (MSR_BIOS_UPGD_TRIG ) & B_MSR_BIOS_UPGD_TRIG_SE_MASK) {
    if (IsBspInt) {
      DEBUG ((DEBUG_INFO, "ActivateSgxFeature: Enabling SGX feature\n"));
    }
    ///
    /// If SGX is pending activation, attempts to activate SGX, otherwise ignored.
    /// As part of the activation, the processor may perform certain checks.
    ///
    AsmWriteMsr64 (MSR_BIOS_UPGD_TRIG, B_MSR_BIOS_UPGD_TRIG_SE_MASK);
    ///
    /// In case of a successful activation, clear the SGX_Pending_Activation bit,
    /// otherwise the bit doesn't change
    ///
    if (AsmReadMsr64 (MSR_BIOS_UPGD_TRIG ) & B_MSR_BIOS_UPGD_TRIG_SE_MASK) {
      if (IsBspInt) {
        DEBUG ((DEBUG_ERROR, "ActivateSgxFeature: SGX activation failed\n"));
      }
    } else {
      if (IsBspInt) {
        DEBUG ((DEBUG_INFO, "ActivateSgxFeature: SGX activation was successful\n"));
      }
    }
  }
  ///
  /// If BIT0 in MSR_BIOS_UPGD_TRIG is 0, SGX is not pending activation
  ///
  else {
    if (IsBspInt) {
      DEBUG ((DEBUG_INFO, "ActivateSgxFeature: SGX feature is deactivated on this thread\n"));
    }
  }

  if (IsBspInt && IsSgxPresent ()) {
    DEBUG ((DEBUG_INFO, "ActivateSgxFeature:: SGX feature was successfully loaded and activated\n"));
  }
}

/**
  Check if SGX present.
  Presence of feature is detectable by reading CPUID.(EAX=0x12, ECX=0x0):EAX[0]

  @retval TRUE  - SGX is present on the system
  @retval FALSE - SGX is not present on the system
**/
BOOLEAN
IsSgxPresent (
  VOID
  )
{
  CPUID_INTEL_SGX_CAPABILITIES_0_SUB_LEAF_EAX  Eax;
  UINT32                                       Ebx;
  CPUID_INTEL_SGX_CAPABILITIES_0_SUB_LEAF_EDX  Edx;

  ///
  /// Presence of SGX feature is detectable by reading CPUID.(EAX=0x12, ECX=0x0):EAX[0]
  ///

  AsmCpuidEx (
    CPUID_INTEL_SGX,
    CPUID_INTEL_SGX_CAPABILITIES_0_SUB_LEAF,
    &Eax.Uint32,
    &Ebx,
    NULL,
    &Edx.Uint32
    );

  if (Eax.Bits.SGX1 == 0) {
    return FALSE;
  }
  return TRUE;
}

/**
  Check if PRM configuration for SGX was approved by MCHECK.

  @retval TRUE  - PRM configuration was approved by MCHECK
  @retval FALSE - PRM configuration was not approved by MCHECK
**/
BOOLEAN
IsPrmApproved (
  VOID
  )
{
  ///
  /// Check if PRM configuration was approved by MCHECK
  ///
  if (!(AsmReadMsr64 (MSR_PRMRR_MASK) & B_MSR_PRMRR_MASK_VLD_MASK)) {
    if (IsBsp ()) {
      DEBUG ((DEBUG_ERROR, "PrmApproved: PRM configuration was rejected by MCHECK, SGX is not enabled\n"));
    }
    return FALSE;
  }
  return TRUE;
}

/**
  Enable/Disable SGX in the processor.
  To enable the SGX, System BIOS must set bit 18 in
  IA32_FEATURE_CONTROL MSR. This function will assert if
  IA32_FEATURE_CONTROL MSR is locked and bit 18 wasn't set
**/
VOID
EnableSgxFeature (
  VOID
  )
{
  MSR_IA32_FEATURE_CONTROL_REGISTER Msr;

  if (IsBsp ()) {
    DEBUG ((DEBUG_INFO, "EnableSgxFeature\n"));
  }

/**
  Check if all of these conditions are met
  - EnableSgx policy was set to enable
  - SGX feature is supported by CPU
  - PRM was successfully allocated and PRMRRs were set
**/
  if (IsSgxPreconditionsMet ()) {
    Msr.Uint64 = AsmReadMsr64 (MSR_IA32_FEATURE_CONTROL);
    Msr.Bits.SgxEnable = 1;

    ///
    /// Check the Feature Lock Bit.
    /// If it is already set, which indicates we are executing POST
    /// due to a warm RESET (i.e., PWRGOOD was not de-asserted).
    ///
    if (Msr.Bits.Lock == 0) {
      AsmWriteMsr64 (MSR_IA32_FEATURE_CONTROL, Msr.Uint64);
    }
  }
}


/**
  Enable SGX Flexible Launch Control.
  Sets BIT 17 of IA32_FEATURE_CONTROL MSR to unlock runtime reconfiguration of
  SGX Flexible Launch Control via IA32_SGXLEPUBKEYHASHn MSR.
**/
VOID
EnableSgxFlexibleLaunchControl (
  VOID
  )
{
  MSR_IA32_FEATURE_CONTROL_REGISTER Msr;
  EFI_CPUID_REGISTER                Cpuid = { 0, 0, 0, 0 };
  BOOLEAN                           IsBspInt;

  IsBspInt = IsBsp ();

  if (IsBspInt) {
    DEBUG ((DEBUG_INFO, "EnableSgxFlexibleLaunchControl\n"));
  }

  ///
  /// Verify processor supports SGX Flexible Launch Control
  ///
  AsmCpuidEx (
    CPUID_STRUCTURED_EXTENDED_FEATURE_FLAGS,
    0,
    &Cpuid.RegEax,
    &Cpuid.RegEbx,
    &Cpuid.RegEcx,
    &Cpuid.RegEdx
    );

  if (Cpuid.RegEcx & BIT30) {
      Msr.Uint64 = AsmReadMsr64 (MSR_IA32_FEATURE_CONTROL);
      Msr.Bits.SgxLaunchControlEnable = 1;

      ///
      /// Check the Feature Lock Bit.
      /// If it is already set, which indicates we are executing POST
      /// due to a warm RESET (i.e., PWRGOOD was not de-asserted).
      ///
      if (Msr.Bits.Lock == 0) {
        AsmWriteMsr64 (MSR_IA32_FEATURE_CONTROL, Msr.Uint64);
      }
  } else {
    if (IsBspInt) {
      DEBUG ((DEBUG_INFO, "SGX Flexible Launch Control is not supported.\n"));
    }
  }
}

/**
  Program TXT SGX SE SVN values in MSR (MSR_UCODE_CR_BIOS_SE_SVN)
  @param[in] CPU_TXT_PREMEM_CONFIG
**/
VOID
ProgramTxtSvnsForSgx (
  IN CPU_TXT_PREMEM_CONFIG *CpuTxtPreMemConfig
  )
{
  UINT64        MsrValue;
  UINT64        SvnMask;
  UINT64        SvnValue;
  UINT8         SInitSvn;
  TXT_INFO_HOB  *TxtInfoHob;
  ACM_HEADER    *BiosAcmBase;

  //
  // Mask for SCLEAN_SE_SVN [31:24] and SINIT_SE_SVN [23:16]
  //
  SvnMask       = 0x00000000FFFF0000;
  TxtInfoHob    = NULL;

  //
  // Get TxtInfoHob
  //
  TxtInfoHob = (TXT_INFO_HOB *)GetFirstGuidHob (&gTxtInfoHobGuid);
  if (TxtInfoHob == NULL) {
    DEBUG ((DEBUG_INFO, "TXT Info HOB not found.\n"));
    return;
  }

  if (IsSgxSupported ()) {
    ///
    /// If BIOS ACM is not present in the flash or if silicon doesn't support TXT, skip SINIT/SCLEAN SE SVN routine
    ///
    if (TxtInfoHob->Data.BiosAcmBase != 0 && TxtInfoHob->Data.ChipsetIsTxtCapable != 0 && TxtInfoHob->Data.ProcessorIsTxtCapable != 0) {
      if (mCpuSgxConfig->SgxSinitDataFromTpm != 0) {
        DEBUG ((DEBUG_INFO, "SINIT SE SVN from TPM: %4x\n", mCpuSgxConfig->SgxSinitDataFromTpm));
        SInitSvn = (UINT8)mCpuSgxConfig->SgxSinitDataFromTpm;
      } else if (mCpuSgxConfig->SgxSinitNvsData != 0) {
        DEBUG ((DEBUG_INFO, "SINIT SE SVN from TPM is 0. Using SGX NVS Data: %4x\n", mCpuSgxConfig->SgxSinitNvsData));
        SInitSvn = (UINT8)mCpuSgxConfig->SgxSinitNvsData;
      } else {
        SInitSvn = SINIT_SE_SVN_VALUE;
        DEBUG ((DEBUG_INFO, "SINIT SE SVN from TPM is 0. SGX NVS Data is 0. Using default SINIT SE SVN: %4x\n", SInitSvn));
      }

      BiosAcmBase = (ACM_HEADER *)(UINTN)TxtInfoHob->Data.BiosAcmBase;
      DEBUG ((DEBUG_INFO, "SCLEAN SE SVN : %4x\n", BiosAcmBase->SeSvn));

      SvnValue = (SInitSvn << 16) | (((UINT8)BiosAcmBase->SeSvn) << 24);
      DEBUG ((DEBUG_INFO, "SCLEAN [31:24] and SINIT [23:16] value to be programmed %016ll\n", SvnValue));

      MsrValue = AsmReadMsr64 (MSR_BIOS_SE_SVN);
      MsrValue &= ~SvnMask;
      MsrValue = MsrValue | SvnValue;
      AsmWriteMsr64 (MSR_BIOS_SE_SVN, MsrValue);
    }

    MsrValue = AsmReadMsr64 (MSR_BIOS_SE_SVN);
    DEBUG ((DEBUG_INFO, "SE SVN MSR value = %0l6llx\n", MsrValue));
  }
}

/**
  Perform SGX Pre Patch Load initialization.

  @param[in] SiPreMemPolicyPpi  - SI PreMem Policy PPI
  @param[in] SiPolicyPpi        - SI Policy PPI
**/
VOID
SgxInitializationPrePatchLoad (
  IN SI_PREMEM_POLICY_PPI    *SiPreMemPolicyPpi,
  IN SI_POLICY_PPI           *SiPolicyPpi
  )
{
  EFI_STATUS                 Status;
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuSgxConfigGuid, (VOID *) &mCpuSgxConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuSecurityPreMemConfigGuid, (VOID *) &mCpuSecurityPreMemConfig);
  ASSERT_EFI_ERROR (Status);
}

/**
  Perform SGX initialization by logical processor.
**/
VOID
SgxInitializationByLogicalProcessorPrePatchLoad (
  VOID
  )
{
  UINT8 IsBspInt;

  IsBspInt = IsBsp ();

  if (IsBspInt) {
    DEBUG ((DEBUG_INFO, "SgxInitializationByLogicalProcessorPrePatchLoad\n"));
  }

  ///
  /// 1) If supported, Enable SGX feature
  /// 2) Lock feature control MSR
  ///
  if (IsSgxSupported ()) {
    EnableSgxFeature ();
    EnableSgxFlexibleLaunchControl ();
  }

  if (IsBspInt && IsSgxPreconditionsMet ()) {
    ///
    /// Set the new EPOCHs value for BSP
    ///
    EpochUpdate ();
  }
}

/**
  Perform SGX Post Patch Load initialization.
**/
VOID
SgxInitializationPostPatchLoad (
  VOID
  )
{
  BOOLEAN                             IsBspInt;

  IsBspInt    = IsBsp ();

  if (IsBspInt) {
    DEBUG ((DEBUG_INFO, "SgxInitializationPostPatchLoad\n"));
  }

  ///
  /// Verify SGX preconditions are met and PRM configuration was approved by MCHECK
  ///
  if (IsSgxPreconditionsMet () && IsPrmApproved ()) {
    ///
    /// Activation of SGX feature
    ///
    ActivateSgxFeature ();
  }
}
