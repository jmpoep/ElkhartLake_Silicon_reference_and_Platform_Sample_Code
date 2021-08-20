/** @file
  PEIM to initialize the cache and program for unlock processor

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

@par Specification
**/

#include <Ppi/MasterBootMode.h>
#include <Library/DebugLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/HobLib.h>
#include <Ppi/SecPlatformInformation.h>
#include <Ppi/SmmAccess.h>
#include <Library/ReportStatusCodeLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include "CpuAccess.h"
#include "CpuInitPeim.h"
#include <Library/CpuPlatformLib.h>
#include <Library/TxtPeiLib.h>
#include <Library/CpuCommonLib.h>
#include <Library/CpuInitLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PeiOcLib.h>
#include <Library/CpuPowerOnConfigLib.h>
#include <Library/PostCodeLib.h>
#include <Library/PcdLib.h>
#include <Register/Cpuid.h>

extern EFI_GUID gHtBistHobGuid;

#if FixedPcdGetBool(PcdFspBinaryEnable) == 0
STATIC EFI_PEI_NOTIFY_DESCRIPTOR mNotifyList[] = {
  {
    (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gEfiPeiMasterBootModePpiGuid,
    BuildBistHob
  }
};
#endif

/**
  Perform Total Memory Encryption initialization.

  @param[in] TmeEnable      - TME policy enable
  @param[in] TmeExcludeBase - Base physical address to be excluded for TME encryption
  @param[in] TmeExcludeSize - Size of range to be excluded from TME encryption

  @retval VOID - No value to return
**/
VOID
TmeInit (
    IN UINT32 TmeEnable,
    IN UINT64 TmeExcludeBase,
    IN UINT64 TmeExcludeSize
  )
{
  return;
}

/**
  Check some CPU policies are valid for debugging unexpected problem if these
  values are not initialized or assigned incorrect resource.

  @param[in] SiPreMemPolicy    The Si PreMem Policy protocol instance
**/
VOID
CpuValidatePolicy (
  IN  SI_PREMEM_POLICY_PPI   *SiPreMemPolicy
  )
{
  ASSERT (SiPreMemPolicy->TableHeader.Header.Revision == SI_PREMEM_POLICY_REVISION);
}

/**
  This function performs basic initialization for CPU in PEI phase after Policy produced.
  Enable/Disable CPU Debug as per Setup and locks it.

  @param[in] SiPreMemPolicyPpi The Si Pre-Mem Policy PPI instance
**/
EFI_STATUS
CpuOnPolicyInstalled (
  IN  SI_PREMEM_POLICY_PPI *SiPreMemPolicyPpi
  )
{
  EFI_STATUS Status;
  CPU_CONFIG_LIB_PREMEM_CONFIG *CpuConfigLibPreMemConfig;
  CPU_SECURITY_PREMEM_CONFIG *CpuSecurityPreMemConfig;

  DEBUG ((DEBUG_INFO, "CpuOnPolicyInstalled Start \n"));
  PostCode (0xC20);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuConfigLibPreMemConfigGuid, (VOID *) &CpuConfigLibPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuSecurityPreMemConfigGuid, (VOID *) &CpuSecurityPreMemConfig);
  ASSERT_EFI_ERROR (Status);

#if FixedPcdGetBool(PcdFspBinaryEnable) == 0
  ///
  /// Install Notify
  ///
  Status = PeiServicesNotifyPpi (&mNotifyList[0]);
  ASSERT_EFI_ERROR (Status);
#endif

  DEBUG ((DEBUG_INFO, "XmmInit Start \n"));
  PostCode (0xC2F);
  ///
  /// Init XMM support
  ///
  XmmInit ();
  if (CpuSecurityPreMemConfig->SkipStopPbet != TRUE) {
    ///
    /// Disable PBET
    ///
    StopPbeTimer ();
  }
  ///
  /// Init CPU Straps
  ///
  PostCode (0xC4F);


#if FixedPcdGetBool(PcdBfxEnable) == 0
  SetCpuStrapAndEarlyPowerOnConfig (SiPreMemPolicyPpi);
#endif


  if (CpuConfigLibPreMemConfig->ElixirSpringsPatchAddr != 0 && CpuConfigLibPreMemConfig->ElixirSpringsPatchSize != 0) {
    ElixirSpringsPatchInit ((VOID*)CpuConfigLibPreMemConfig->ElixirSpringsPatchAddr, CpuConfigLibPreMemConfig->ElixirSpringsPatchSize);
  }

  //
  // Enable/Disable CPU Debug MSR as per setup and Lock Before Enabling TME (TME is being activated in Memory Init - MrcDone function)
  // If TME is enabled and not in Debug mode, then CPU Debug must be disabled and Locked.
  //
  DEBUG((DEBUG_INFO, "Invoking LockEnableDisableCpuDebug \n"));
  LockEnableDisableCpuDebug ();

  DEBUG((DEBUG_INFO, "CPU Pre-Mem Exit \n"));
  PostCode (0xC6F);

  return EFI_SUCCESS;
}

#if FixedPcdGetBool(PcdFspBinaryEnable) == 0
/**
  Build BIST HOB

  @param[in] PeiServices       - Indirect reference to the PEI Services Table.
  @param[in] NotifyDescriptor  - Address of the notification descriptor data structure. Type
                      EFI_PEI_NOTIFY_DESCRIPTOR is defined above.
  @param[in] Ppi               - Address of the PPI that was installed.

  @retval EFI_SUCCESS - Hob built or not necessary
**/
EFI_STATUS
EFIAPI
BuildBistHob (
  IN EFI_PEI_SERVICES          **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
  IN VOID                      *Ppi
  )
{
  EFI_STATUS                           Status;
  EFI_BOOT_MODE                        BootMode;
  EFI_SEC_PLATFORM_INFORMATION_PPI     *SecPlatformInformationPpi;
  UINT64                               InformationSize;
  EFI_SEC_PLATFORM_INFORMATION_RECORD  *SecPlatformInformation;
  BIST_HOB_DATA                        *BspBistData;
  VOID                                 *Hob;
  SI_PREMEM_POLICY_PPI                 *SiPreMemPolicyPpi;
  UINT32                               BistStatus;
  CPU_CONFIG_LIB_PREMEM_CONFIG         *CpuConfigLibPreMemConfig;

  Status = PeiServicesGetBootMode (&BootMode);
  if (!EFI_ERROR (Status) && (BootMode == BOOT_ON_S3_RESUME)) {
    return EFI_SUCCESS;
  }

  Status = PeiServicesLocatePpi (
             &gEfiSecPlatformInformationPpiGuid,   // GUID
             0,                                    // Instance
             NULL,                                 // EFI_PEI_PPI_DESCRIPTOR
             (VOID ** ) &SecPlatformInformationPpi // PPI
             );

  if (Status == EFI_NOT_FOUND) {
    return EFI_SUCCESS;
  }

  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuConfigLibPreMemConfigGuid, (VOID *) &CpuConfigLibPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Obtain BIST information for BSP. Information for APs will obtained in DXE phase during MP initialization.
  ///
  BspBistData = (BIST_HOB_DATA *) AllocateZeroPool (sizeof (BIST_HOB_DATA));
  if (BspBistData == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  SecPlatformInformation = (EFI_SEC_PLATFORM_INFORMATION_RECORD *) (&(BspBistData->Health));
  InformationSize        = sizeof (BspBistData->Health);
  Status = SecPlatformInformationPpi->PlatformInformation (
                                        (CONST EFI_PEI_SERVICES  **) PeiServices,
                                        &InformationSize,
                                        SecPlatformInformation
                                        );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  ///
  /// Dump BIST information to serial log
  ///
  BistStatus = SecPlatformInformation->x64HealthFlags.Uint32;
  DEBUG ((DEBUG_INFO, "BistStatus = 0x%x\n", BistStatus));

  if (BistStatus != 0) {
    DEBUG ((DEBUG_ERROR, "BIST for BSP failed\n"));
    ReportStatusCode (
      EFI_ERROR_MAJOR | EFI_ERROR_CODE,
      EFI_COMPUTING_UNIT_HOST_PROCESSOR | EFI_CU_HP_EC_SELF_TEST
      );
    ASSERT (FALSE);
  } else if (CpuConfigLibPreMemConfig->BistOnReset == 1) {
    DEBUG ((DEBUG_INFO, "BIST for BSP passed\n"));
  }

  BspBistData->ApicId = GetCpuApicId ();
  Hob = BuildGuidDataHob (
          &gHtBistHobGuid,
          BspBistData,
          sizeof (BIST_HOB_DATA)
          );
  ASSERT (Hob != NULL);

  return Status;
}
#endif

