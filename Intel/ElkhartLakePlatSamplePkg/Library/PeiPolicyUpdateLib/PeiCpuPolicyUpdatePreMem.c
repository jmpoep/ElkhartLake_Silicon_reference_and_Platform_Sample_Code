/** @file
  This file is SampleCode of the library for Intel CPU PEI Policy initialization.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2009 - 2020 Intel Corporation.

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
#include <Library/PeiCpuPolicyUpdate.h>
#include <Library/SiPolicyLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PmcLib.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/PciSegmentLib.h>
#include <Register/PchRegs.h>
#include <Library/SpiLib.h>
#include <Library/SpiAccessLib.h>
#if FixedPcdGet8(PcdFspModeSelection) == 1
#include <FspmUpd.h>
#endif
#include <Ppi/Spi.h>
#include <Library/HobLib.h>
#include <Library/BootMediaLib.h>

#define GET_OCCUPIED_SIZE(ActualSize, Alignment) \
  ((ActualSize) + (((Alignment) - ((ActualSize) & ((Alignment) - 1))) & ((Alignment) - 1)))

/**
  Check on the processor if SGX is supported.

  @retval True if SGX supported or FALSE if not
**/
BOOLEAN
IsSgxCapSupported (
  VOID
  )
{
  EFI_CPUID_REGISTER CpuidRegs;

  ///
  /// Processor support SGX feature by reading CPUID.(EAX=7,ECX=0):EBX[2]
  ///
  AsmCpuidEx (CPUID_STRUCTURED_EXTENDED_FEATURE_FLAGS, 0, &CpuidRegs.RegEax,&CpuidRegs.RegEbx,&CpuidRegs.RegEcx,&CpuidRegs.RegEdx);

  ///
  /// SGX feature is supported only on SKL and later,
  /// with CPUID.(EAX=7,ECX=0):EBX[2]=1
  /// PRMRR configuration enabled, MSR IA32_MTRRCAP (FEh) [12] == 1
  ///
  if ((CpuidRegs.RegEbx & BIT2) && (AsmReadMsr64 (MSR_IA32_MTRRCAP) & BIT12)) {
    return TRUE;
  }

  return FALSE;
}

/**
  Calculate the smallest supported PRMRR size that will be
  reported in response to a given EPC size request from OS

  @param[in] EpcSize           - EPC size

  @retval    UINT32            - PRMRR size that is just bigger than the requested EPC
**/
UINT32
ConvertEpcToPrmrr (
  UINT32 EpcSize
  )
{
  UINT32 EpcAlignedPowerOfTwo;
  UINT32 SupportedPrmrr;

  if (EpcSize == 0) {
    return 0;
  }

  ///
  /// Round EPC size to the nearest power of two
  ///
  EpcAlignedPowerOfTwo = GetPowerOfTwo32(EpcSize);

  ///
  /// If given EpcSize is not power of two
  ///
  if (EpcAlignedPowerOfTwo < EpcSize) {
    EpcAlignedPowerOfTwo = (UINT32) (UINTN) LShiftU64(EpcAlignedPowerOfTwo,1);
  }

  /*
    Bits 0 through 31 indicate which sizes are supported. Each bit
    represents one size. A bit at position n indicates whether
    size 2^(n+20) bytes is supported
  */
  SupportedPrmrr = (UINT32) (UINTN) LShiftU64 (AsmReadMsr64 (MSR_PRMRR_VALID_CONFIG),20);

  ///
  /// Removing sizes that are lower then EPC round size
  ///
  SupportedPrmrr = SupportedPrmrr & ~(EpcAlignedPowerOfTwo - 1);

  ///
  /// If EPC rounding is bigger than highest supported PRMRR size,
  /// then EPC size that was set by OS is not supported
  ///
  if (SupportedPrmrr < EpcAlignedPowerOfTwo) {
    DEBUG ((DEBUG_INFO, "ConvertEpcToPrmrr: Requested EPC size (rounded up to be aligned to power of two) by OS 0x%016llX, is bigger than supported PRMRRs size 0x%016llX\n" ,EpcAlignedPowerOfTwo ,SupportedPrmrr));
    return 0;
  }

  ///
  /// If PRMRR supported size is bigger then EPC size rounded to two
  /// then return the next lowest PRMRR size supported
  ///
  if ((SupportedPrmrr & EpcAlignedPowerOfTwo) == 0) {
    return (UINT32) (UINTN) (LShiftU64(BIT0, LowBitSet32(SupportedPrmrr)));
  }
  return (SupportedPrmrr & EpcAlignedPowerOfTwo);
}

/**
  Function will update the policy for PRMRR size and enable SGX
  (In case PRMRR size is not zero), by reading the setup option
  value, SGX UEFI variable if exist and if SGX enabling is
  software controlled.

  Function may initiate a cold reset upon the occurring of the
  next scenarios

  1.SGX need to be enabled(PRMRR size is bigger than 0) but MSR
    FEATURE_CONTROL[0x3a] is already locked[0] and SGX bit[18]
    was not set.

  2.PRMRR size need to bigger than it was in previous boot and
    MSR FEATURE_CONTROL[0x3a] is locked[0]

  3.SGX need to be disabled(PRMRR size is 0), but MSR
    FEATURE_CONTROL[0x3a] is already locked[0] and SGX bit[18]
    was set.

  @param[in]  VariableServices     Variable Service Ppi
  @param[in]  CpuSetup             The pointer of CPU_SETUP
  @param[in]  FspmUpd              A VOID pointer
  @param[in, out]  CpuSecurityPreMemConfig - will update
                   CpuSecurityPreMemConfig->EnableSgx and
                   CpuSecurityPreMemConfig->PrmrrSize
**/
VOID
UpdatePrmrrSize (
  IN     EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices,
  IN     CPU_SETUP                       *CpuSetup,
  IN OUT VOID                            *FspmUpd,
  IN OUT CPU_SECURITY_PREMEM_CONFIG      *CpuSecurityPreMemConfig
  )
{
  EFI_STATUS                        Status;
  MSR_IA32_FEATURE_CONTROL_REGISTER Msr;
  EPC_OS_CONFIG                     mEpcOsConfiguration;
  UINTN                             mEpcOsConfigurationSize;
  BOOLEAN                           SgxFeatureEnabled;
  BOOLEAN                           FeatureMsrLocked;
  EFI_BOOT_MODE                     BootMode;

  mEpcOsConfigurationSize = sizeof(EPC_OS_CONFIG);

  Msr.Uint64 = AsmReadMsr64 (MSR_IA32_FEATURE_CONTROL);
  SgxFeatureEnabled = (BOOLEAN) (Msr.Bits.SgxEnable == 1);
  FeatureMsrLocked  = (BOOLEAN) (Msr.Bits.Lock == 1);

  if (CpuSetup->EnableSgx == SGX_SOFTWARE_CONTROL) {
    Status = VariableServices->GetVariable (
                                 VariableServices,
                                 EPC_OS_CTRL,
                                 &gEpcOsDataGuid,
                                 NULL,
                                 &mEpcOsConfigurationSize,
                                 &mEpcOsConfiguration
                                 );

    ///
    /// OS SGX variable was found
    ///
    if (Status == EFI_SUCCESS) {
      ///
      /// BIOS will enable SGX by OS request only if the EPC size that was asked is a valid one
      ///
      mEpcOsConfiguration.RequestedEpcSize = ConvertEpcToPrmrr(mEpcOsConfiguration.RequestedEpcSize);

      Status = PeiServicesGetBootMode (&BootMode);
      ASSERT_EFI_ERROR (Status);

      ///
      /// If EPC size is supported and Boot Mode is valid for SGX Configuration
      ///
      if ((mEpcOsConfiguration.RequestedEpcSize != 0) && (BootMode != BOOT_ON_S3_RESUME) && (BootMode != BOOT_ON_S4_RESUME)) {
        DEBUG ((DEBUG_INFO, "SGX is enabled by OS\n"));

        ///
        /// If feature MSR(0x3a) is locked and SGX feature is not set, the cold reset
        /// need to be done, in order to remove feature control lock and to enable SGX
        /// This scenario may occur if in the previous boot
        /// - SGX was set to software control but there were no UEFI OS variable, so SGX was disabled.
        /// - Previous power cycle was a warm reset, so lock bits were not cleaned.
        /// Now there is such variable, but, so we need to perform a cold reset
        ///
        if (FeatureMsrLocked && (SgxFeatureEnabled == FALSE)) {
          DEBUG ((DEBUG_INFO, "In order to enable SGX, system will perform a cold reset now\n"));
          (*GetPeiServicesTablePointer())->ResetSystem2 (EfiResetCold, EFI_SUCCESS, 0, NULL);
        }

        UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.EnableSgx, CpuSecurityPreMemConfig->EnableSgx, CPU_FEATURE_ENABLE);

        DEBUG ((DEBUG_INFO, "PRMRR size that was defined by OS: 0x%X\n", mEpcOsConfiguration.RequestedEpcSize));
        DEBUG ((DEBUG_INFO, "PRMRR size that was defined by setup: 0x%X\n", CpuSetup->PrmrrSize));

        ///
        /// BIOS is setting PRMRR to be the be MAX(EPC that been asked by OS (and converted to PRMRR),PRMRR size in setup options)
        ///
        if (CpuSetup->PrmrrSize < mEpcOsConfiguration.RequestedEpcSize) {
          CpuSetup->PrmrrSize = mEpcOsConfiguration.RequestedEpcSize;
          ///
          /// If PRMRR size need to be changed from what it was in the previous boot
          /// but previous power cycle was a warm one, so need to initiate a cold reset.
          ///
          if (FeatureMsrLocked && SgxFeatureEnabled) {
            DEBUG ((DEBUG_INFO, "In order to change PRMRR size, system will perform a cold reset now\n"));
            (*GetPeiServicesTablePointer())->ResetSystem2 (EfiResetCold, EFI_SUCCESS, 0, NULL);
          }
        }
      } else if (BootMode == BOOT_ON_S3_RESUME) {
        DEBUG ((DEBUG_ERROR, "SGX Configuration changes cannot be made on a S3 flow\n"));
      } else if (BootMode == BOOT_ON_S4_RESUME) {
        DEBUG ((DEBUG_ERROR, "SGX Configuration changes cannot be made on a S4 flow\n"));
      } else {
        DEBUG ((DEBUG_ERROR, "EpcSize of 0x%X is not supported\n", mEpcOsConfiguration.RequestedEpcSize));
      }
    } else {
      DEBUG ((DEBUG_ERROR, "OS SGX variable was not found\n"));
    }

    ///
    /// if OS variable was not found or EPC request size was not valid
    ///
#if FixedPcdGet8(PcdFspModeSelection) == 1
    if (((FSPM_UPD *) FspmUpd)->FspmConfig.EnableSgx == CPU_FEATURE_DISABLE) {
#else
    if (CpuSecurityPreMemConfig->EnableSgx == CPU_FEATURE_DISABLE) {
#endif
      ///
      /// If SGX was enabled in previous boot, then PRMRR setup option will have a valid size
      ///
      if (CpuSetup->PrmrrSize != 0) {
        UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.EnableSgx, CpuSecurityPreMemConfig->EnableSgx, CPU_FEATURE_ENABLE);
      } else {
        UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.EnableSgx, CpuSecurityPreMemConfig->EnableSgx, CPU_FEATURE_DISABLE);
      }
    }
  } else {
    DEBUG ((DEBUG_INFO, "SGX is setup controlled\n"));
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.EnableSgx, CpuSecurityPreMemConfig->EnableSgx, CpuSetup->EnableSgx);
  }

#if FixedPcdGet8(PcdFspModeSelection) == 1
  if (((FSPM_UPD *) FspmUpd)->FspmConfig.EnableSgx != CPU_FEATURE_ENABLE) {
#else
  if (CpuSecurityPreMemConfig->EnableSgx != CPU_FEATURE_ENABLE) {
#endif

    ///
    /// If feature MSR(0x3a) is locked and SGX feature is set, then a cold reset
    /// need to be done in order to remove feature control lock and to disable SGX
    /// This Scenario may occur if:
    /// - In Previous boot SGX was enabled
    /// - SGX is software controlled
    /// - Software asked for unsupported EPC size
    /// Need to remove SGX bit, and lock bit, so need to initiate a cold reset
    ///
    if (FeatureMsrLocked && SgxFeatureEnabled) {
      DEBUG ((DEBUG_INFO, "In order to disable SGX, system will perform a cold reset now\n"));
      (*GetPeiServicesTablePointer())->ResetSystem2 (EfiResetCold, EFI_SUCCESS, 0, NULL);
    }
  }

  ///
  /// If PRMRR is supported
  /// PRMRR configuration enabled, MSR IA32_MTRRCAP (FEh) [12] == 1
  ///
  if ((AsmReadMsr64(MSR_IA32_MTRRCAP) & BIT12) != 0) {
#if FixedPcdGet8(PcdFspModeSelection) == 1
    if (((FSPM_UPD *) FspmUpd)->FspmConfig.EnableSgx == CPU_FEATURE_ENABLE) {
#else
    if (CpuSecurityPreMemConfig->EnableSgx == CPU_FEATURE_ENABLE) {
#endif
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PrmrrSize, CpuSecurityPreMemConfig->PrmrrSize, CpuSetup->PrmrrSize);
    }
  }

  ///
  /// Check if PRMRR size is not supported.
  /// Bits 0 through 31 indicate which sizes are supported. Each bit represents one size.
  /// A bit at position n indicates whether size 2^(n+20) bytes is supported
  ///
#if FixedPcdGet8(PcdFspModeSelection) == 1
  if ((LShiftU64 (AsmReadMsr64 (MSR_PRMRR_VALID_CONFIG), 20) & ((FSPM_UPD *) FspmUpd)->FspmConfig.PrmrrSize) == 0x0) {
    DEBUG ((DEBUG_INFO, "InitializePrm: PRMRR setup size 0x%X\n", ((FSPM_UPD *) FspmUpd)->FspmConfig.PrmrrSize));
#else
  if ((LShiftU64 (AsmReadMsr64 (MSR_PRMRR_VALID_CONFIG), 20) & CpuSecurityPreMemConfig->PrmrrSize) == 0x0) {
    DEBUG ((DEBUG_INFO, "InitializePrm: PRMRR setup size 0x%X\n", CpuSecurityPreMemConfig->PrmrrSize));
#endif
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PrmrrSize, CpuSecurityPreMemConfig->PrmrrSize, 0);
  }
}


/**
  This function performs CPU PEI Policy initialization in Pre-memory.

  @retval EFI_SUCCESS              The PPI is installed and initialized.
  @retval EFI ERRORS               The PPI is not successfully installed.
  @retval EFI_OUT_OF_RESOURCES     Do not have enough resources to initialize the driver
**/
EFI_STATUS
EFIAPI
UpdatePeiCpuPolicyPreMem (
  VOID
  )
{
  EFI_STATUS                      Status;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices;
  UINTN                           VariableSize;
  SETUP_DATA                      SetupData;
  CPU_SETUP                       CpuSetup;
  EFI_BOOT_MODE                   BootMode;
  VOID                            *FspmUpd;
  SI_PREMEM_POLICY_PPI            *SiPreMemPolicyPpi;
  CPU_SECURITY_PREMEM_CONFIG      *CpuSecurityPreMemConfig;
#if FixedPcdGetBool(PcdTxtEnable) == 1
  CPU_TXT_PREMEM_CONFIG           *CpuTxtPreMemConfig;
#endif
  CPU_CONFIG_LIB_PREMEM_CONFIG    *CpuConfigLibPreMemConfig;
  UINT32                          MaxLogicProcessors;

  DEBUG ((DEBUG_INFO, "Update PeiCpuPolicyUpdate Pre-Mem Start\n"));

  FspmUpd                     = NULL;
  SiPreMemPolicyPpi           = NULL;
#if FixedPcdGetBool(PcdTxtEnable) == 1
  CpuTxtPreMemConfig          = NULL;
#endif
  CpuSecurityPreMemConfig     = NULL;
  CpuConfigLibPreMemConfig    = NULL;

#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspmUpd = (FSPM_UPD *) PcdGet32 (PcdFspmUpdDataAddress);
  ASSERT (FspmUpd != NULL);
#else
  Status = PeiServicesLocatePpi (&gSiPreMemPolicyPpiGuid, 0, NULL, (VOID **) &SiPreMemPolicyPpi);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuSecurityPreMemConfigGuid, (VOID *) &CpuSecurityPreMemConfig);
  ASSERT_EFI_ERROR (Status);
#if FixedPcdGetBool(PcdTxtEnable) == 1
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuTxtPreMemConfigGuid, (VOID *) &CpuTxtPreMemConfig);
  ASSERT_EFI_ERROR (Status);
#endif
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuConfigLibPreMemConfigGuid, (VOID *) &CpuConfigLibPreMemConfig);
  ASSERT_EFI_ERROR (Status);
#endif

  //
  // Make sure ReadOnlyVariablePpi is available
  //
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &VariableServices
             );
  ASSERT_EFI_ERROR (Status);

  //
  // Get Setup Variable
  //
  VariableSize = sizeof (CPU_SETUP);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"CpuSetup",
                               &gCpuSetupVariableGuid,
                               NULL,
                               &VariableSize,
                               &CpuSetup
                               );
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (SETUP_DATA);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"Setup",
                               &gSetupVariableGuid,
                               NULL,
                               &VariableSize,
                               &SetupData
                               );
  ASSERT_EFI_ERROR (Status);

  //
  // Get current boot mode
  //
  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Function will update PrmrrSize
  /// If Runtime Memory interface is enabled and OS variable exist, the PRMRR size will be defined by OS
  /// If Runtime Memory interface is not enabled or OS asked for not supported PRMRR size, PRMRR size will be updated by
  /// PRMRR size from setup options
  /// Function will issue a cold reset if such is needed, in order to enable/disable SGX
  ///
  UpdatePrmrrSize (
    VariableServices,
    &CpuSetup,
    (VOID *) FspmUpd,
    CpuSecurityPreMemConfig
    );

#if FixedPcdGetBool(PcdTxtEnable) == 1
  //
  // Update TXT Platform Policy
  //
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.Txt,              CpuSecurityPreMemConfig->Txt,         CpuSetup.Txt);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.TxtDprMemorySize, CpuTxtPreMemConfig->TxtDprMemorySize, CpuSetup.DprSize * 0x100000);
#endif
  //
  // Check PWR FLR
  //
  if (PmcIsPowerFailureDetected ()) {
    PmcClearPowerFailureStatus ();
  }

  //
  // When the SUS_PWR_FLR bit is set, it indicates VRMPWRGD signal from the CPU VRM went low.
  // Software must clear this bit if set.
  //
  if (PmcIsSusPowerFailureDetected ()) {
    PmcClearSusPowerFailureStatus ();
  }

  if (CpuSetup.SkipStopPbet == 1) {
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.SkipStopPbet, CpuSecurityPreMemConfig->SkipStopPbet, TRUE);
  } else {
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.SkipStopPbet, CpuSecurityPreMemConfig->SkipStopPbet, FALSE);
  }
#if FixedPcdGetBool(PcdFspWrapperEnable) == 0
  CpuSecurityPreMemConfig->ResetAux = CpuSetup.ResetAux;
#endif

  //
  // Update CpuConfigLibPreMem Config Block data
  //
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.HyperThreading,          CpuConfigLibPreMemConfig->HyperThreading,          CpuSetup.HyperThreading);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.BootFrequency,           CpuConfigLibPreMemConfig->BootFrequency,           CpuSetup.BootFrequency);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.ActiveCoreCount,         CpuConfigLibPreMemConfig->ActiveCoreCount1,        CpuSetup.ActiveCoreCount);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.FClkFrequency,           CpuConfigLibPreMemConfig->FClkFrequency,           CpuSetup.EpocFclkFreq);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.JtagC10PowerGateDisable, CpuConfigLibPreMemConfig->JtagC10PowerGateDisable, CpuSetup.JtagC10PowerGateDisable);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.BistOnReset,             CpuConfigLibPreMemConfig->BistOnReset,             CpuSetup.BistOnReset);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.VmxEnable,               CpuConfigLibPreMemConfig->VmxEnable,               CpuSetup.VT);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.DebugInterfaceEnable,    CpuConfigLibPreMemConfig->DebugInterfaceEnable,    CpuSetup.DebugInterfaceEnable);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.DebugInterfaceLockEnable, CpuConfigLibPreMemConfig->DebugInterfaceLockEnable, CpuSetup.DebugInterfaceLockEnable);
  if (CpuSetup.CpuRatioOverride) {
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.CpuRatio, CpuConfigLibPreMemConfig->CpuRatio, CpuSetup.CpuRatio);
  } else {
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.CpuRatio, CpuConfigLibPreMemConfig->CpuRatio, 0);
  }
  ///
  /// Set PcdCpuMaxLogicalProcessorNumber to max number of logical processors enabled
  /// Read MSR_CORE_THREAD_COUNT (0x35) to check the total active Threads
  ///
  MaxLogicProcessors = (UINT32) (AsmReadMsr64 (MSR_CORE_THREAD_COUNT) & B_MSR_CORE_THREAD_COUNT_THREADCOUNT_MASK);
  DEBUG ((DEBUG_INFO, "MaxLogicProcessors = %d\n", MaxLogicProcessors));

#if (FixedPcdGetBool(PcdFspWrapperEnable) == 0) || (FixedPcdGet8(PcdFspModeSelection) == 1)
  PcdSet32S (PcdCpuMaxLogicalProcessorNumber, MaxLogicProcessors);
#else
  PcdSetEx32S (&gUefiCpuPkgTokenSpaceGuid, PcdCpuMaxLogicalProcessorNumber, MaxLogicProcessors);
#endif

  return EFI_SUCCESS;
}
