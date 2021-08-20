/** @file
  Source code file for Platform Init Advanced Pre-Memory PEI module

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2020 Intel Corporation.

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

#include <PiPei.h>
#include <Ppi/Reset.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <Guid/GlobalVariable.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PostCodeLib.h>
#include <Library/TimerLib.h>

#include <Ppi/Wdt.h>
#include <Guid/TcoWdtHob.h>
#include <Library/PmcLib.h>
#include <Library/PchCycleDecodingLib.h>
#include <PlatformNvRamHookLib.h>
#include <Library/PeiPlatformRecoveryLib.h>
#include <Library/BiosIdLib.h>
#include <Library/EcMiscLib.h>
#include <Library/PeiWdtAppLib.h>
#include <Library/PeiDTbtPolicyLib.h>
#include <Library/PeiPolicyInitLib.h>
#include <SaCommonDefinitions.h>
#include <Register/PmcRegs.h>
#include <SetupVariable.h>
#include <FastBootFunctionEnabledHob.h>
#include <FastBootExceptionInfoHob.h>
#include <CustomOptionControl.h>
#include <Setup.h>
#include <PlatformPostCode.h>
#include <FirwmareConfigurations.h>
#include <Library/SetupDataCacheLib.h>
#include <Library/GpioLib.h>
#include <Library/PeiPlatformLib.h>
#include <Guid/SysFwUpdateProgress.h>
#include <Ppi/RecoveryModule.h>
#include <Library/PlatformFvAddressLib.h>
#include <PlatformBoardId.h>
#include <Library/PeiMeLib.h>
#include <Library/SpiAccessLib.h>

#include <LibraryPrivate/PeiMeInitLib/HeciInit.h>
#include <PchResetPlatformSpecific.h>
#include <Library/BaseCryptLib.h>
#include <Library/MemoryAllocationLib.h>


#if FixedPcdGetBool(PcdBfxEnable) == 1
#include <FvCallback.h>
#include <Library/BootMediaLib.h>
#include <Library/NemMapLib.h>
#include <Library/SecPpiReinstallLib.h>
#include <Library/PeiFspWrapperTempRamExitLib.h>
#include <Library/StallPpiLib.h>
#if (FixedPcdGetBool(PcdFspWrapperEnable) == 0 || FixedPcdGet8(PcdFspModeSelection) == 0)
#include <Ppi/TempRamExitPpi.h>
#include <Library/PeiServicesTablePointerLib.h>
#endif
#endif

///
/// Reset Generator I/O Port
///
#define RESET_GENERATOR_PORT           0xCF9


EFI_STATUS
EFIAPI
PlatformInitPreMem (
  IN CONST EFI_PEI_SERVICES      **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR   *NotifyDescriptor,
  IN VOID                        *Ppi
  );

EFI_STATUS
EFIAPI
MemoryDiscoveredPpiNotifyCallback (
  IN CONST EFI_PEI_SERVICES      **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR   *NotifyDescriptor,
  IN VOID                        *Ppi
  );

EFI_STATUS
EFIAPI
SiPreMemPolicyPpiNotifyCallback (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  );

EFI_STATUS
EFIAPI
WdtAppPpiNotifyCallback (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  );

#if FixedPcdGetBool(PcdBfxEnable) == 1
VOID
MigrateGdtPointer (
  VOID
  );
#endif

EFI_STATUS
LocateAndVerifyObbHash (
  VOID
  );

EFI_STATUS
EFIAPI
CheckforIfwiDnx (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
);

EFI_STATUS
EFIAPI
PchReset (
  IN CONST EFI_PEI_SERVICES    **PeiServices
  );

/**
  Load recovery module from external storage (such as SATA or NVMe).

  @param[in]  PeiServices       General purpose services available to every PEIM.

  @param[in]  NotifyDescriptor  The typedef structure of the notification
                                descriptor. Not used in this function.

  @param[in]  Ppi               The typedef structure of the PPI descriptor.
                                Not used in this function.

  @retval EFI_SUCCESS           The function completed successfully

**/
EFI_STATUS
EFIAPI
LoadRecoveryModule (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  );

BOOLEAN
IsBiosUpdateInProgress (
  VOID
  );

static EFI_PEI_NOTIFY_DESCRIPTOR mPreMemNotifyList = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiReadOnlyVariable2PpiGuid,
  (EFI_PEIM_NOTIFY_ENTRY_POINT) PlatformInitPreMem
};

static EFI_PEI_NOTIFY_DESCRIPTOR mMemDiscoveredNotifyList = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiMemoryDiscoveredPpiGuid,
  (EFI_PEIM_NOTIFY_ENTRY_POINT) MemoryDiscoveredPpiNotifyCallback
};

#if FixedPcdGetBool(PcdBfxEnable) == 1
static EFI_PEI_NOTIFY_DESCRIPTOR mGetFvNotifyList = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_DISPATCH | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiVirtualBlockIoPpiGuid,
  (EFI_PEIM_NOTIFY_ENTRY_POINT) GetFvNotifyCallback
};
#endif

static EFI_PEI_NOTIFY_DESCRIPTOR mIfwiDnxNotifyList = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiEndOfPeiSignalPpiGuid,
  (EFI_PEIM_NOTIFY_ENTRY_POINT)CheckforIfwiDnx
};

static EFI_PEI_NOTIFY_DESCRIPTOR mSiPreMemPolicyNotifyList = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gSiPreMemPolicyReadyPpiGuid,
  (EFI_PEIM_NOTIFY_ENTRY_POINT) SiPreMemPolicyPpiNotifyCallback
};

static EFI_PEI_NOTIFY_DESCRIPTOR mWdtPpiNotifyList = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gWdtPpiGuid,
  (EFI_PEIM_NOTIFY_ENTRY_POINT) WdtAppPpiNotifyCallback
};

GLOBAL_REMOVE_IF_UNREFERENCED EFI_PEI_PPI_DESCRIPTOR mPpiListRecoveryBootMode = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiBootInRecoveryModePpiGuid,
  NULL
};

GLOBAL_REMOVE_IF_UNREFERENCED EFI_PEI_PPI_DESCRIPTOR mPpiBootMode = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiMasterBootModePpiGuid,
  NULL
};

static EFI_PEI_RESET_PPI mResetPpi = {
  PchReset
};

static EFI_PEI_PPI_DESCRIPTOR mPreMemPpiList[] = {
  {
    (EFI_PEI_PPI_DESCRIPTOR_PPI| EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gEfiPeiResetPpiGuid,
    &mResetPpi
  }
};

static EFI_PEI_PPI_DESCRIPTOR mPatchConfigurationDataPreMemPpi[] = {
  {
  EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
  &gPatchConfigurationDataPreMemPpiGuid,
  NULL
  }
};

static EFI_PEI_NOTIFY_DESCRIPTOR  mBlockIoNotifyList[] = {
  //
  // Use EFI_PEI_PPI_DESCRIPTOR_NOTIFY_DISPATCH flag rather than EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK
  // to ensure all VirtualBlockIoPpi notify callbacks (especially the one in FatLite) are executed
  // before invoking LoadRecoveryModule().
  //
  {
    EFI_PEI_PPI_DESCRIPTOR_NOTIFY_DISPATCH,
    &gEfiPeiDeviceRecoveryModulePpiGuid,//gEfiPeiVirtualBlockIoPpiGuid,
    LoadRecoveryModule
  },
  {
    EFI_PEI_PPI_DESCRIPTOR_NOTIFY_DISPATCH | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gEfiPeiDeviceRecoveryModulePpiGuid,//gEfiPeiVirtualBlockIo2PpiGuid,
    LoadRecoveryModule
  }
};

#if FixedPcdGetBool(PcdBfxEnable) == 1
static EFI_PEI_PPI_DESCRIPTOR  mNvmOwnershipAcquiredPpi = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gSiNvmOwnershipAcquiredPpiGuid,
  NULL
};
#endif
EFI_STATUS
EFIAPI
PeiGuidForward (
  VOID
  );

/**
  Configures GPIO

  @param[in]  GpioTable       Point to Platform Gpio table
  @param[in]  GpioTableCount  Number of Gpio table entries

**/
VOID
ConfigureGpio (
  IN GPIO_INIT_CONFIG                 *GpioDefinition,
  IN UINT16                           GpioTableCount
  )
{
  DEBUG ((DEBUG_INFO, "ConfigureGpio() Start\n"));

  GpioConfigurePads (GpioTableCount, GpioDefinition);

  DEBUG ((DEBUG_INFO, "ConfigureGpio() End\n"));
}

/**
  Install Firmware Volume Hob's once there is main memory

  @param[in]  PeiServices       General purpose services available to every PEIM.
  @param[in]  NotifyDescriptor  Notify that this module published.
  @param[in]  Ppi               PPI that was installed.

  @retval     EFI_SUCCESS       The function completed successfully.
**/
EFI_STATUS
EFIAPI
MemoryDiscoveredPpiNotifyCallback (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  )
{
  EFI_STATUS                      Status;
  EFI_BOOT_MODE                   BootMode;
  DEBUG_CONFIG_DATA_HOB           *DebugConfigDataHob;
  EFI_PEI_HOB_POINTERS            Hob;
  DEBUG_CONFIG_DATA               DebugConfigData;
  UINTN                           DebugConfigDataSize;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VarPpi;

  DEBUG ((DEBUG_INFO, "MemoryDiscoveredPpiNotifyCallback() - Start\n"));

  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR (Status);

  Hob.Guid = GetFirstGuidHob (&gDebugConfigHobGuid);
  if (Hob.Guid != NULL) {
    Status = PeiServicesLocatePpi (
               &gEfiPeiReadOnlyVariable2PpiGuid,
               0,
               NULL,
               (VOID **) &VarPpi
               );
    ASSERT_EFI_ERROR (Status);
    DebugConfigDataSize = sizeof (DEBUG_CONFIG_DATA);
    Status = VarPpi->GetVariable (
                       VarPpi,
                       L"DebugConfigData",
                       &gDebugConfigVariableGuid,
                       NULL,
                       &DebugConfigDataSize,
                       &DebugConfigData
                       );
    ASSERT_EFI_ERROR (Status);
    DebugConfigDataHob = (DEBUG_CONFIG_DATA_HOB *) GET_GUID_HOB_DATA (Hob.Guid);
    DebugConfigDataHob->RamDebugInterface = (DebugConfigData.RamDebugInterface == 1 && FeaturePcdGet (PcdRamDebugEnable)) ? 1 : 0;
  }

  ///
  /// If S3 resume, then we are done
  ///
  if (BootMode == BOOT_ON_S3_RESUME) {
    return EFI_SUCCESS;
  }
  ///
  /// Build HOB for DXE
  ///
  if (BootMode == BOOT_IN_RECOVERY_MODE) {
    ///
    /// Prepare the recovery service
    ///
    Status = InitializeRecovery ();
    ASSERT_EFI_ERROR (Status);
  } else {
    if (GetFirstGuidHob (&gSysFwUpdateProgressGuid) != NULL || SpiIsTopSwapEnabled ()) {
      InitializeRecovery ();
      ASSERT_EFI_ERROR (Status);
      Status = PeiServicesNotifyPpi (mBlockIoNotifyList);
    }
  }
#if FixedPcdGetBool(PcdBfxEnable) == 1
#if FixedPcdGetBool(PcdFspWrapperEnable) == 0
  //
  // Request NVM handoff
  //
  if (BootMediaIsUfs ()) {
    Status = PeiHeciRequestDeviceOwnership ();
    if (EFI_ERROR(Status)) {
      ASSERT_EFI_ERROR (Status);
      CpuDeadLoop ();
    }
  }
#endif
#endif
  //
  // Ifwi Dnx Flow
  //
  Status = PeiServicesNotifyPpi (&mIfwiDnxNotifyList);
  DEBUG ((EFI_D_ERROR, "mIfwiDnxNotifyList, Status = %r\n", Status));
  ASSERT_EFI_ERROR (Status);

#if FixedPcdGetBool(PcdBfxEnable) == 1
  if (BootMediaIsSpi ()) {
#endif
    BuildFvHob (
      (UINTN) FixedPcdGet32 (PcdBiosAreaBaseAddress),
      (UINTN) FixedPcdGet32 (PcdBiosSize)
      );
#if FixedPcdGetBool(PcdBfxEnable) == 1
  }
#endif

  DEBUG ((DEBUG_INFO, "MemoryDiscoveredPpiNotifyCallback() - End\n"));

  return Status;
}

/**
  Check to see the overclocking is enabled or not

  @retval  OverclockingEnabledStatus  TRUE means overclocking is enabled
                                      FALSE means overclocking is disabled
**/
BOOLEAN
EFIAPI
IsOverclockingEnabled (
  VOID
  )
{
  EFI_STATUS                      Status;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *PeiReadOnlyVarPpi;
  UINTN                           VarSize;
  CPU_SETUP                       CpuSetup;
  BOOLEAN                         OverclockingEnabledStatus;

  OverclockingEnabledStatus = FALSE;

  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &PeiReadOnlyVarPpi
             );
  if (Status == EFI_SUCCESS) {
    VarSize = sizeof (CPU_SETUP);
    Status = PeiReadOnlyVarPpi->GetVariable (
                                  PeiReadOnlyVarPpi,
                                  L"CpuSetup",
                                  &gCpuSetupVariableGuid,
                                  NULL,
                                  &VarSize,
                                  &CpuSetup
                                  );
    if (Status == EFI_SUCCESS) {
      if (CpuSetup.OverclockingSupport != 0) {
        OverclockingEnabledStatus = TRUE;
      }
    }
  }

  return OverclockingEnabledStatus;
}

/**
API to check whether to take Ifwi Dnx Path or not.

@param[in]  PeiServices       General purpose services available to every PEIM.
@param[in]  NotifyDescriptor  Notify that this module published.
@param[in]  Ppi               PPI that was installed.

@retval     EFI_SUCCESS       The function completed successfully.
**/
EFI_STATUS
EFIAPI
CheckforIfwiDnx (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  )
{
  EFI_STATUS                      Status;
  IAFW_DNX_REQ_SET_RESP_DATA      CseResponse;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *PeiReadOnlyVarPpi;
  UINTN                           VarSize;
  SETUP_DATA                      SystemConfiguration;
  PCH_RESET_DATA                  ResetData;

  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **)&PeiReadOnlyVarPpi
             );
  ASSERT_EFI_ERROR (Status);

  VarSize = sizeof(SETUP_DATA);
  Status = PeiReadOnlyVarPpi->GetVariable (
                                PeiReadOnlyVarPpi,
                                L"Setup",
                                &gSetupVariableGuid,
                                NULL,
                                &VarSize,
                                &SystemConfiguration
                                );
  ASSERT_EFI_ERROR (Status);

  //
  // IBB hash verification is done by BootGuard module. The below call is for
  // OBB (FvAdvanced, FvPostMemory, FvFspS) HASH Verification using SHA256 algorithm
  //
    Status = LocateAndVerifyObbHash ();
    if (EFI_ERROR(Status) || (SystemConfiguration.IfwiDnx != 0)) {
      DEBUG ((EFI_D_ERROR, "Verify OBB failed, Status = %r\n", Status));
      //
      // Send HECI DNX COMMAND
      //
      DEBUG ((EFI_D_INFO, "Sending HECI DNX COMMAND\n"));
      Status = HeciIafwDnxReqSet (&CseResponse);
      if (Status == EFI_NOT_FOUND) {
        DEBUG ((EFI_D_INFO, "Install Heci PPI Again\n"));
        InstallHeciPpi ();
        Status = HeciIafwDnxReqSet (&CseResponse);
      }
      DEBUG ((EFI_D_INFO, "Sending HECI DNX COMMAND Status = %r\n", Status));
      if (CseResponse.MKHIHeader.Fields.Result != 0) {
        DEBUG ((DEBUG_ERROR, "Unable to set RBE breadcrumb for DnX. Cannot continue.\n"));
        ASSERT (FALSE);
      }
      DEBUG ((EFI_D_INFO, "Issue Global Reset after sending the HECI DNX command.\n"));
      CopyMem (&ResetData.Guid, &gPchGlobalResetGuid, sizeof(EFI_GUID));
      StrCpyS (ResetData.Description, PCH_RESET_DATA_STRING_MAX_LENGTH, PCH_PLATFORM_SPECIFIC_RESET_STRING);
      (*PeiServices)->ResetSystem2 (EfiResetPlatformSpecific, EFI_SUCCESS, sizeof(PCH_RESET_DATA), &ResetData);
      ASSERT (FALSE);
    }
  return Status;
}

/**
  Locates and Verify OBB against SHA256 HASH algorithm

  @retval  EFI_SUCCESS  HASH verification Successful
**/
EFI_STATUS
LocateAndVerifyObbHash (
  VOID
  )
{
  EFI_STATUS                      Status;
  UINT8                           Digest[SHA256_DIGEST_SIZE];
  UINTN                           CtxSize;
  VOID                            *HashCtx;
  BOOLEAN                         HashResult;
  EFI_FIRMWARE_VOLUME_HEADER      *FvHeader;
  EFI_FFS_FILE_HEADER             *FfsFile;
  EFI_GUID                        *ObbSha256HashFilePtr;
  UINT8                           *HashFileBuffer;
  UINT8                           *ObbBuffer;
  UINTN                           ObbSize;
  UINTN                           FvInstance;
  EFI_FIRMWARE_VOLUME_EXT_HEADER  *FvExtHeader;
  EFI_FFS_FILE_HEADER             *FileHeader;
  EFI_GUID                        *FvName;
  EFI_FIRMWARE_VOLUME_HEADER      *ObbDigestBase;
  EFI_FIRMWARE_VOLUME_HEADER      *ObbBase;

  ObbSha256HashFilePtr = &gObbSha256HashFileGuid;
  FfsFile              = NULL;
  ObbDigestBase        = NULL;
  ObbBase              = NULL;
  Status               = EFI_SUCCESS;
  FvInstance           = 0;

  DEBUG ((DEBUG_ERROR, "LocateAndVerifyObbHash () - Start\n"));

#if FixedPcdGetBool(PcdFspWrapperEnable) == 1
  ObbSize = (UINTN) (FixedPcdGet32 (PcdFlashFvAdvancedSize) + FixedPcdGet32 (PcdFlashFvPostMemorySize) + FixedPcdGet32 (PcdFlashFvFspSSize));
#else
  ObbSize = (UINTN) (FixedPcdGet32 (PcdFlashFvAdvancedSize) + FixedPcdGet32 (PcdFlashFvPostMemorySize));
#endif

  ZeroMem (Digest, SHA256_DIGEST_SIZE);

  ///
  /// Locate Firmware Binary Firmware Volume header
  ///
  while (TRUE) {
    Status = PeiServicesFfsFindNextVolume (FvInstance, (VOID **) &FvHeader);
    if (EFI_ERROR(Status)) {
      DEBUG ((DEBUG_ERROR, "FvInstance: %d Status: %r\n", FvInstance, Status));
      break;
    }
    if (FvHeader->ExtHeaderOffset) {
      FvExtHeader = (EFI_FIRMWARE_VOLUME_EXT_HEADER *) ((UINTN) FvHeader + FvHeader->ExtHeaderOffset);
      FvName = &FvExtHeader->FvName;
    } else {
      FileHeader = (EFI_FFS_FILE_HEADER *) ((UINTN) FvHeader + FvHeader->HeaderLength);
      FvName = &FileHeader->Name;
    }
    if (CompareGuid (FvName, &gFvPreMemoryGuid)) {
      ObbDigestBase = FvHeader;
    } else if (CompareGuid (FvName, &gFvAdvancedGuid)) {
      ObbBase = FvHeader;
    }
    if ((ObbDigestBase != 0) && (ObbBase != 0)) {
      break;
    }
    FvInstance++;
  }

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Unable to find Firmware Volume Info\n"));
    return EFI_NOT_FOUND;
  }
  DEBUG ((DEBUG_ERROR, "Firmware Voume address: ObbDigestBase %x, ObbBase %x\n", (UINT32) ObbDigestBase, (UINT32) ObbBase));

  ///
  /// Locate Firmware File System file within Firmware Volume
  ///
  Status = PeiServicesFfsFindFileByName (ObbSha256HashFilePtr, ObbDigestBase, (VOID **) &FfsFile);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }
  HashFileBuffer = (UINT8 *) ((UINT8 *) FfsFile + sizeof (EFI_FFS_FILE_HEADER) + sizeof (EFI_COMMON_SECTION_HEADER));
  DEBUG ((DEBUG_ERROR, "First Dword content of the OBB Hash value: %x\n", *(UINT32 *)HashFileBuffer));

  CtxSize = Sha256GetContextSize ();
  HashCtx = AllocatePool (CtxSize);
  ASSERT (HashCtx != NULL);

  Sha256Init (HashCtx);
  ObbBuffer = (UINT8 *) (UINT32) ObbBase;
  Sha256Update (HashCtx, (VOID*) ObbBuffer, ObbSize);
  HashResult = Sha256Final (HashCtx, Digest);
  if (!HashResult) {
    DEBUG ((EFI_D_ERROR, "HASH calculation [Fail]\n"));
    return EFI_DEVICE_ERROR;
  }
  DEBUG (( DEBUG_ERROR, "First Dword content of the OBB Digest: %x\n", *(UINT32 *)Digest));
  if (CompareMem (Digest, HashFileBuffer, SHA256_DIGEST_SIZE) != 0) {
    DEBUG ((EFI_D_ERROR, "HASH Mismatch\n"));
    return EFI_COMPROMISED_DATA;
  }
  DEBUG ((DEBUG_ERROR, "LocateAndVerifyObbHash () - End\n"));
  return EFI_SUCCESS;
}


/**
  Check fast boot is enabled or not

  @retval  FastBootEnabledStatus  TRUE means fast boot is enabled
                                  FALSE means fast boot is disabled
**/
BOOLEAN
EFIAPI
IsFastBootEnabled (
  VOID
  )
{
  EFI_STATUS                      Status;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *PeiReadOnlyVarPpi;
  UINTN                           VarSize;
  SETUP_DATA                      SystemConfiguration;
  BOOLEAN                         FastBootEnabledStatus;

  FastBootEnabledStatus = FALSE;
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &PeiReadOnlyVarPpi
             );
  if (Status == EFI_SUCCESS) {
    VarSize = sizeof (SETUP_DATA);
    Status = PeiReadOnlyVarPpi->GetVariable (
                                  PeiReadOnlyVarPpi,
                                  L"Setup",
                                  &gSetupVariableGuid,
                                  NULL,
                                  &VarSize,
                                  &SystemConfiguration
                                  );
    if (Status == EFI_SUCCESS) {
      if (SystemConfiguration.FastBoot != 0) {
        FastBootEnabledStatus = TRUE;
      }
    }
  }

  return FastBootEnabledStatus;
}

/**
  Detect if there was an incompleted BIOS update which got interrupted.

  @retval  TRUE   Incompleted BiosUpdate is detected.
  @retavl  FALSE  Not detected.

**/
BOOLEAN
IsBiosUpdateInProgress (
  VOID
  )
{
  EFI_STATUS                        Status;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI   *PeiReadOnlyVarPpi;
  UINTN                             VarSize;
  SYSTEM_FIRMWARE_UPDATE_PROGRESS   UpdatePorgress;
  VOID                              *HobPtr;

  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &PeiReadOnlyVarPpi
             );

  ASSERT_EFI_ERROR (Status);

  if (Status == EFI_SUCCESS) {
    VarSize = sizeof (SYSTEM_FIRMWARE_UPDATE_PROGRESS);
    Status = PeiReadOnlyVarPpi->GetVariable (
                                  PeiReadOnlyVarPpi,
                                  SYSFW_UPDATE_PROGRESS_VARIABLE_NAME,
                                  &gSysFwUpdateProgressGuid,
                                  NULL,
                                  &VarSize,
                                  &UpdatePorgress
                                  );
    if (Status == EFI_SUCCESS) {
      DEBUG ((
        DEBUG_INFO,
        "Detected system firmware update is in progress: Component 0x%x, Progress 0x%x\n",
        UpdatePorgress.Component,
        UpdatePorgress.Progress
        ));

      HobPtr = BuildGuidDataHob (&gSysFwUpdateProgressGuid, &UpdatePorgress, sizeof (UpdatePorgress));
      ASSERT (HobPtr != 0);
      return TRUE;
    }
  }

  return FALSE;
}

/**
  Create Fast Boot HOB

  @param[in]  VariableServices  A pointer to this instance of the EFI_PEI_READ_ONLY_VARIABLE2_PPI.

  @retval     EFI_SUCCESS  The function completes successfully
  @retval     others
**/
EFI_STATUS
EFIAPI
CreateFastBootHob (
  IN EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices
  )
{
  EFI_STATUS                      Status;
  UINTN                           VarSize;
  FAST_BOOT_FUNCTION_ENABLED_HOB  *FastBootFunctionEnabledHob;
  FAST_BOOT_EXCEPTION_INFO_HOB    *FastBootExceptionInfoHob;

  if (IsFastBootEnabled ()) {
    ///
    /// If Fast Boot is enabled, create the FAST_BOOT_FUNCTION_ENABLED_HOB for other modules' reference.
    ///
    Status = PeiServicesCreateHob (
               EFI_HOB_TYPE_GUID_EXTENSION,
               sizeof (FAST_BOOT_FUNCTION_ENABLED_HOB),
               (VOID **) &FastBootFunctionEnabledHob
               );
    if (!EFI_ERROR (Status)) {
      FastBootFunctionEnabledHob->Header.Name = gFastBootFunctionEnabledHobGuid;
      FastBootFunctionEnabledHob->FastBootEnabled = TRUE;
    } else {
      return Status;
    }
    ///
    /// When RTC battery is drained (RTC power loss) or Secondary NvRam content is cleared (via jumper short), this bit will get set.
    /// This is the Fast Boot Exception Type 2.
    ///
    if (!PmcIsRtcBatteryGood ()) {
      Status = PeiServicesCreateHob (
                 EFI_HOB_TYPE_GUID_EXTENSION,
                 sizeof (FAST_BOOT_EXCEPTION_INFO_HOB),
                 (VOID **) &FastBootExceptionInfoHob
                 );
      if (!EFI_ERROR (Status)) {
        FastBootExceptionInfoHob->Header.Name = gFastBootExceptionInfoHobGuid;
        FastBootExceptionInfoHob->FbExceptionType = ExceptionType2;
        FastBootExceptionInfoHob->FbExceptionCategory = ContentLost;
      } else {
        return Status;
      }
    }
    ///
    /// Check the EFI Globally-Defined variable which is nonexistent right after updating BIOS, to determine if BIOS was just updated.
    ///
    Status = VariableServices->GetVariable (
                                 VariableServices,
                                 L"ConOut",
                                 &gEfiGlobalVariableGuid,
                                 NULL,
                                 &VarSize,
                                 NULL
                                 );
    if (Status == EFI_NOT_FOUND) {
      Status = PeiServicesCreateHob (
                 EFI_HOB_TYPE_GUID_EXTENSION,
                 sizeof (FAST_BOOT_EXCEPTION_INFO_HOB),
                 (VOID **) &FastBootExceptionInfoHob
                 );
      if (!EFI_ERROR (Status)) {
        FastBootExceptionInfoHob->Header.Name = gFastBootExceptionInfoHobGuid;
        FastBootExceptionInfoHob->FbExceptionType = ExceptionType2;
        FastBootExceptionInfoHob->FbExceptionCategory = FirmwareUpdate;
      } else {
        return Status;
      }
    }
    ///
    /// If overclocking is enabled, then BIOS shall switch back to Full Boot mode
    ///
    if (IsOverclockingEnabled ()) {
      Status = PeiServicesCreateHob (
                 EFI_HOB_TYPE_GUID_EXTENSION,
                 sizeof (FAST_BOOT_EXCEPTION_INFO_HOB),
                 (VOID **) &FastBootExceptionInfoHob
                 );
      if (!EFI_ERROR (Status)) {
        FastBootExceptionInfoHob->Header.Name = gFastBootExceptionInfoHobGuid;
        FastBootExceptionInfoHob->FbExceptionType = ExceptionType2;
        FastBootExceptionInfoHob->FbExceptionCategory = SpecialBoot;
      } else {
        return Status;
      }
    }
  }
  return EFI_SUCCESS;
}

//@todo it should be performed in Si Pkg.
/**
  Provide hard reset PPI service.
  To generate full hard reset, write 0x0E to PCH RESET_GENERATOR_PORT (0xCF9).

  @param[in]  PeiServices       General purpose services available to every PEIM.

  @retval     Not return        System reset occured.
  @retval     EFI_DEVICE_ERROR  Device error, could not reset the system.
**/
EFI_STATUS
EFIAPI
PchReset (
  IN CONST EFI_PEI_SERVICES    **PeiServices
  )
{
  DEBUG ((DEBUG_INFO, "Perform Cold Reset\n"));
  IoWrite8 (RESET_GENERATOR_PORT, 0x0E);

  CpuDeadLoop ();

  ///
  /// System reset occured, should never reach at this line.
  ///
  ASSERT_EFI_ERROR (EFI_DEVICE_ERROR);

  return EFI_DEVICE_ERROR;
}

/**
  Early Platform PCH initialization
**/
VOID
EFIAPI
EarlyPlatformPchInit (
  VOID
  )
{
  UINT8        TcoRebootHappened;
  TCO_WDT_HOB  *TcoWdtHobPtr;
  EFI_STATUS   Status;

  if (TcoSecondToHappened ()) {
    TcoRebootHappened = 1;
    DEBUG ((DEBUG_INFO, "PlatformInitPreMem - TCO Second TO status bit is set. This might be a TCO reboot\n"));
  } else {
    TcoRebootHappened = 0;
  }

  ///
  /// Create HOB
  ///
  Status = PeiServicesCreateHob (EFI_HOB_TYPE_GUID_EXTENSION, sizeof (TCO_WDT_HOB), (VOID **) &TcoWdtHobPtr);
  if (!EFI_ERROR (Status)) {
    TcoWdtHobPtr->Header.Name  = gTcoWdtHobGuid;
    TcoWdtHobPtr->TcoRebootHappened = TcoRebootHappened;
  }

  TcoClearSecondToStatus ();
}

/**
  Set the state to go after G3

  @dot
    digraph G {
      subgraph cluster_c0 {
        node [shape = box];
          b1[label="EcForceResetAfterAcRemoval ()" fontsize=12 style=filled color=lightblue];
          b2[label="Force S5" fontsize=12 style=filled color=lightblue];
          b3[label="Force S0" fontsize=12 style=filled color=lightblue];

        node [shape = ellipse];
          e1[label="Start" fontsize=12 style=filled color=lightblue];
          e2[label="End" fontsize=12 style=filled color=lightblue];

        node [shape = diamond,style=filled,color=lightblue];
          d1[label="GetVariable\nFroceResetAfterAcRemoval" fontsize=12];
          d2[label="EcPresent" fontsize=12];
          d3[label="ForceResetAfterAcRemoval" fontsize=12];
          d4[label="GetVariable\nStateAfterG3" fontsize=12];
          d5[label="StateAfterG3" fontsize=12];

        label = "SetTheStateToGoAfterG3 Flow"; fontsize=15; fontcolor=black; color=lightblue;
        e1 -> d1
        d1 -> d2 [label="Success" fontsize=9]
        d1 -> d4 [label="Fail" fontsize=9]
        d2 -> b1 [label="Yes" fontsize=9]
        b1 -> d3
        d2 -> d3 [label="No" fontsize=9]
        d3 -> b3 [label="Yes" fontsize=9]
        d3 -> d4 [label="No" fontsize=9]
        d4 -> d5 [label="Success" fontsize=9]
        d4 -> b3 [label="Fail" fontsize=9]
        d5 -> b2 [label="Set" fontsize=9]
        d5 -> b3 [label="Clear" fontsize=9]
        b3 -> e2
      }
    }
  @enddot

  @param[in]  VariableServices  A pointer to this instance of the EFI_PEI_READ_ONLY_VARIABLE2_PPI.
**/
VOID
EFIAPI
SetTheStateToGoAfterG3 (
  IN EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices
  )
{
  EFI_STATUS            Status;
  UINTN                 VariableSize;
  UINT8                 ForceResetAfterAcRemovalVar;
  UINT8                 StateAfterG3;
  PCH_SETUP             PchSetup;

  ForceResetAfterAcRemovalVar = 0;
  StateAfterG3 = 0;


  VariableSize = sizeof (PCH_SETUP);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"PchSetup",
                               &gPchSetupVariableGuid,
                               NULL,
                               &VariableSize,
                               &PchSetup
                               );
  if (!EFI_ERROR(Status)) {
    StateAfterG3 = PchSetup.StateAfterG3;
  }

  if ((StateAfterG3 == 1) && (ForceResetAfterAcRemovalVar == 0)) {
    PmcSetPlatformStateAfterPowerFailure (1); // AfterG3 = S5
  } else {
    PmcSetPlatformStateAfterPowerFailure (0); // AfterG3 = S0
  }
}


// @todo: It should be moved Policy Init.
/**
  Initialize the GPIO IO selection, GPIO USE selection, and GPIO signal inversion registers

  @param[in] VariableServices  A pointer to this instance of the EFI_PEI_READ_ONLY_VARIABLE2_PPI.
**/
VOID
EFIAPI
PlatformPchInit (
  IN EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices
  )
{

  ///
  /// Enable the LPC I/O decoding for 0x6A0~0x6A7 as EC's extra I/O port, where 0x6A0 is the Data port
  /// and 0x6A4 is the Command/Status port.
  ///
  if (PcdGetBool (PcdEcPresent)) {
    PchLpcGenIoRangeSet (PcdGet16 (PcdEcExtraIoBase), 0x10); //PTLMOD+
  }
#if FixedPcdGetBool(PcdNct677FPresent) == 1
  else {
    /// Added Nuvoton HW monitor IO address.
    PchLpcGenIoRangeSet (PcdGet16 (PcdNct6776fHwMonBase), 0x10);
  }
#endif

}

/**
  Configure EC for specific devices

  @param[in] PchLan       - The PchLan of PCH_SETUP variable.
  @param[in] BootMode     - The current boot mode.
**/
VOID
EcInit (
  IN UINT8                PchLan,
  IN EFI_BOOT_MODE        BootMode
  )
{
  EFI_STATUS              Status;

  Status = EFI_SUCCESS;
  if (PchLan != PEI_DEVICE_DISABLED) {
    Status = EnableLanPower (TRUE);
  } else {
    Status = EnableLanPower (FALSE);
  }
  ASSERT_EFI_ERROR (Status);

  //
  // Clear 10sec PB Override mode in EC so that Power button is always available during POST.
  //
  ClearTenSecPwrButtonMode ();
}

/**
  Do platform specific programming. For example, EC init, Chipset programming

  @retval  EFI_SUCCESS       The function completed successfully.
**/
EFI_STATUS
PlatformSpecificInitPreMem (
  VOID
  )
{
  EFI_STATUS                      Status;
  EFI_BOOT_MODE                   BootMode;
  SA_SETUP                        SaSetup;
  PCH_SETUP                       PchSetup;
  SETUP_DATA                      SystemConfiguration;
  UINTN                           VarSize;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices;

  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR (Status);

  //
  // Locate Setup variables
  //
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &VariableServices
             );
  ASSERT_EFI_ERROR (Status);

  VarSize = sizeof (PCH_SETUP);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"PchSetup",
                               &gPchSetupVariableGuid,
                               NULL,
                               &VarSize,
                               &PchSetup
                               );

  if (!EFI_ERROR(Status) && PcdGetBool (PcdEcPresent)) {
    EcInit (PchSetup.PchLan, BootMode);
  }

  VarSize = sizeof (SETUP_DATA);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"Setup",
                               &gSetupVariableGuid,
                               NULL,
                               &VarSize,
                               &SystemConfiguration
                               );
  if (!EFI_ERROR(Status)) {
#if FixedPcdGetBool(PcdEcEnable) == 1
    //
    // Selecting charging method
    //
    if (PcdGetBool (PcdEcPresent)) {
      if (SystemConfiguration.EcChargingMethod == 1) {
        //
        // Fast charging
        //
        DfctFastChargingMode (TRUE);
      } else {
        //
        // Normal charging
        //
        DfctFastChargingMode (FALSE);
      }
    }
#endif
    VarSize = sizeof (SA_SETUP);
    Status = VariableServices->GetVariable (
                                 VariableServices,
                                 L"SaSetup",
                                 &gSaSetupVariableGuid,
                                 NULL,
                                 &VarSize,
                                 &SaSetup
                                 );
    if (!EFI_ERROR(Status)) {
      if (PcdGet8 (PcdPlatformType) == TypeUltUlx) {
        // Force Valid Sensor Settings depending on the Option selected in Sensor Hub Type Setup Option.
        if(SystemConfiguration.SensorHubType == 0) {
          SystemConfiguration.UsbSensorHub = 0;
        } else if (SystemConfiguration.SensorHubType == 1) {
          SaSetup.AlsEnable = 0;
          SystemConfiguration.UsbSensorHub = 0;
        } else {
          SaSetup.AlsEnable = 0;
          SystemConfiguration.UsbSensorHub = 1;
        }
      }
    }
  }
  return EFI_SUCCESS;
}

/**
  Run this function after SaPolicy PPI to be installed.

  @param[in]  PeiServices       General purpose services available to every PEIM.
  @param[in]  NotifyDescriptor  Notify that this module published.
  @param[in]  Ppi               PPI that was installed.

  @retval     EFI_SUCCESS       The function completed successfully.
**/
EFI_STATUS
EFIAPI
SiPreMemPolicyPpiNotifyCallback (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  )
{
  EFI_STATUS Status;

  ///
  /// Platform specific programming. It may have Chipset, EC or some platform specific
  /// programming here.
  ///
  Status = PlatformSpecificInitPreMem ();
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/**
  Run this function after Wdt PPI to be installed.

  @param[in]  PeiServices       General purpose services available to every PEIM.
  @param[in]  NotifyDescriptor  Notify that this module published.
  @param[in]  Ppi               PPI that was installed.

  @retval     EFI_SUCCESS       The function completed successfully.
**/
EFI_STATUS
EFIAPI
WdtAppPpiNotifyCallback (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  )
{
  EFI_STATUS Status;
  WDT_PPI    *WdtPei;

  WdtPei = (WDT_PPI *) Ppi;

  Status = PeiWdtApp (WdtPei);
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/**
  Build a HOB for debug configure data.

  The DebugConfigHob is built by platform code and consumed by PeiDxeSmmDebugPrintErrorLevelLib and
  PeiDxeSmmSerialPortParameterLib library instances.

  @param[in] DebugConfigData     A pointer to the DEBUG_CONFIG_DATA.

**/
VOID
EFIAPI
BuildDebugConfigDataHob (
  IN DEBUG_CONFIG_DATA     *DebugConfigData
  )
{
  DEBUG_CONFIG_DATA_HOB    *DebugConfigDataHob;

  DebugConfigDataHob = BuildGuidHob (&gDebugConfigHobGuid, sizeof (DEBUG_CONFIG_DATA_HOB));
  ASSERT (DebugConfigDataHob != NULL);
  if (DebugConfigDataHob == NULL) {
    DEBUG ((DEBUG_ERROR, "Build Debug Config Hob failed!\n"));
    return;
  }

  DebugConfigDataHob->SerialDebug = DebugConfigData->SerialDebug;
  DebugConfigDataHob->SerialDebugBaudRate = DebugConfigData->SerialDebugBaudRate;
  DebugConfigDataHob->RamDebugInterface = 0;
  DebugConfigDataHob->UartDebugInterface = (DebugConfigData->UartDebugInterface == 1 && FeaturePcdGet (PcdSerialPortEnable)) ? 1 : 0;
  DebugConfigDataHob->Usb3DebugInterface = (DebugConfigData->Usb3DebugInterface == 1 && FeaturePcdGet (PcdUsb3SerialStatusCodeEnable)) ? 1 : 0;
  DebugConfigDataHob->TraceHubDebugInterface = (DebugConfigData->TraceHubDebugInterface == 1 && FeaturePcdGet (PcdTraceHubEnable)) ? 1 : 0;

  DebugConfigDataHob->SerialIoDebugInterface            = (DebugConfigData->SerialIoDebugInterface == 1 && FeaturePcdGet (PcdSerialIoUartEnable)) ? 1 : 0;
  DebugConfigDataHob->SerialIoUartDebugControllerNumber = DebugConfigData->SerialIoUartDebugControllerNumber;
  DebugConfigDataHob->SerialIoUartDebugBaudRate       = DebugConfigData->SerialIoUartDebugBaudRate;
  DebugConfigDataHob->SerialIoUartDebugStopBits         = DebugConfigData->SerialIoUartDebugStopBits;
  DebugConfigDataHob->SerialIoUartDebugParity           = DebugConfigData->SerialIoUartDebugParity;
  DebugConfigDataHob->SerialIoUartDebugFlowControl      = DebugConfigData->SerialIoUartDebugFlowControl;
  DebugConfigDataHob->SerialIoUartDebugDataBits         = DebugConfigData->SerialIoUartDebugDataBits;
}

/**
  Load recovery module from external storage (such as SATA or NVMe).

  @param[in]  PeiServices       General purpose services available to every PEIM.

  @param[in]  NotifyDescriptor  The typedef structure of the notification
                                descriptor. Not used in this function.

  @param[in]  Ppi               The typedef structure of the PPI descriptor.
                                Not used in this function.

  @retval EFI_SUCCESS           The function completed successfully

**/
EFI_STATUS
EFIAPI
LoadRecoveryModule (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  )
{
  EFI_STATUS                                  Status;
  EFI_PEI_RECOVERY_MODULE_PPI                *PeiRecovery;

  DEBUG ((DEBUG_INFO, "LoadRecoveryModule Entry\n"));

  //
  // load recovery file and install FV (original done in DXEIPL, but we copy it here)
  //
  Status = PeiServicesLocatePpi (
             &gEfiPeiRecoveryModulePpiGuid,
             0,
             NULL,
             (VOID **) &PeiRecovery
             );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Locate Pei Recovery Module Ppi Failed.(Status = %r)\n", Status));
    return Status;
  }

  Status = PeiRecovery->LoadRecoveryCapsule ((EFI_PEI_SERVICES **)PeiServices, PeiRecovery);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Load Recovery Capsule Failed.(Status = %r)\n", Status));
  }

  return Status;
}

/**
  Basic GPIO configuration before memory is ready

**/
VOID
GpioInitEarlyWwanPreMem (
  VOID
  )
{
  GPIO_CONFIG                     BbrstConfig;
  UINT32                          WwanBbrstGpio;

  WwanBbrstGpio = PcdGet32 (PcdWwanBbrstGpio);

  if (WwanBbrstGpio) {
    //
    // BIOS needs to reset modem if modem RESET# is not asserted via PLTRST# in the previous sleep state
    //
    GpioGetPadConfig (WwanBbrstGpio, &BbrstConfig);
    if ((PcdGetBool (PcdPcieWwanEnable) == FALSE) ||
        (PcdGetBool (PcdWwanResetWorkaround) == TRUE &&
        BbrstConfig.Direction == GpioDirOut &&
        BbrstConfig.OutputState == GpioOutHigh)) {
      //
      // Assert FULL_CARD_POWER_OFF#, RESET# and PERST# GPIOs
      //
      if (PcdGet32 (PcdBoardGpioTableWwanOffEarlyPreMem) != 0 && PcdGet16 (PcdBoardGpioTableWwanOffEarlyPreMemSize) != 0) {
        ConfigureGpio ((VOID *) (UINTN) PcdGet32 (PcdBoardGpioTableWwanOffEarlyPreMem), PcdGet16 (PcdBoardGpioTableWwanOffEarlyPreMemSize));
      }
      MicroSecondDelay (1 * 1000); // Delay by 1ms
    }

    if (PcdGetBool (PcdPcieWwanEnable) == TRUE) {
      if (PcdGet32 (PcdBoardGpioTableWwanOnEarlyPreMem) != 0 && PcdGet16 (PcdBoardGpioTableWwanOnEarlyPreMemSize) != 0) {
        ConfigureGpio ((VOID *) (UINTN) PcdGet32 (PcdBoardGpioTableWwanOnEarlyPreMem), PcdGet16 (PcdBoardGpioTableWwanOnEarlyPreMemSize));
      }
    }
  }
}

/**
  Callback to consume DefaultPolicyInit PPI to install and update policy.

  @param[in]  PeiServices  Pointer to PEI Services Table.
  @param[in]  NotifyDesc   Pointer to the descriptor for the Notification event that
                           caused this function to execute.
  @param[in]  Ppi          Pointer to the PPI data associated with this function.

  @retval     EFI_SUCCESS   The function completes successfully
  @retval     EFI_NOT_FOUND Either variable service or required variable not found.
**/
EFI_STATUS
EFIAPI
SiPreMemDefaultPolicyInitPpiNotifyCallback (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  )
{
  EFI_STATUS                        Status;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI   *VariableServices;
  SETUP_DATA                        SystemConfiguration;
  UINTN                             VariableSize;
  UINT8                             FwConfig;

  VariableServices = NULL;
  Status = PeiServicesLocatePpi (
              &gEfiPeiReadOnlyVariable2PpiGuid,
              0,
              NULL,
              (VOID **) &VariableServices
              );
  if (VariableServices != NULL) {
    VariableSize = sizeof (SETUP_DATA);
    Status = VariableServices->GetVariable (
                                 VariableServices,
                                 L"Setup",
                                 &gSetupVariableGuid,
                                 NULL,
                                 &VariableSize,
                                 &SystemConfiguration
                                 );
    if (!EFI_ERROR (Status)) {
      FwConfig = SystemConfiguration.FirmwareConfiguration;
      PeiPolicyInitPreMem (FwConfig);
      return EFI_SUCCESS;
    }
  }
  return EFI_NOT_FOUND;
}

static EFI_PEI_NOTIFY_DESCRIPTOR mSiPreMemDefaultPolicyInitNotifyList = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gSiPreMemDefaultPolicyInitPpiGuid,
  (EFI_PEIM_NOTIFY_ENTRY_POINT) SiPreMemDefaultPolicyInitPpiNotifyCallback
};

/**
  This function handles PlatformInit task after PeiReadOnlyVariable2 PPI produced

  @param[in]  PeiServices  Pointer to PEI Services Table.
  @param[in]  NotifyDesc   Pointer to the descriptor for the Notification event that
                           caused this function to execute.
  @param[in]  Ppi          Pointer to the PPI data associated with this function.

  @retval     EFI_SUCCESS  The function completes successfully
  @retval     others
**/
EFI_STATUS
EFIAPI
PlatformInitPreMem (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  )
{
  EFI_STATUS                        Status;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI   *VariableServices;
  EFI_BOOT_MODE                     BootMode;
  UINT64                            McD0BaseAddress;
  UINT16                            ABase;
  SETUP_DATA                        SystemConfiguration;
  UINTN                             VariableSize;
  UINT8                             FwConfig;
  CHAR16                            BiosVersion[40];
  CHAR16                            ReleaseDate[20];
  CHAR16                            ReleaseTime[20];
  UINTN                             Size;
  DEBUG_CONFIG_DATA                 DebugConfigData;
  BOOLEAN                           IsFirstBoot = FALSE;
  UINT32                            InitSetupVolVarAttr;
  UINT8                             InitSetupFlag;

  PostCode(PLATFORM_INIT_PREMEM_ENTRY);

  if (PcdGetBool (PcdPlatformInitPreMem)) {
    return EFI_SUCCESS;
  } else {
    Status = PcdSetBoolS (PcdPlatformInitPreMem, TRUE);
    ASSERT_EFI_ERROR (Status);
  }

  VariableServices = (EFI_PEI_READ_ONLY_VARIABLE2_PPI *) Ppi;

  Status = GetBiosVersionDateTime (BiosVersion, ReleaseDate, ReleaseTime);
  Size = sizeof (BiosVersion);
  PcdSetPtrS (PcdBiosVersion, &Size, &BiosVersion);
  Size = sizeof (ReleaseDate);
  PcdSetPtrS (PcdReleaseDate, &Size, &ReleaseDate);
  Size = sizeof (ReleaseTime);
  PcdSetPtrS (PcdReleaseTime, &Size, &ReleaseTime);

  PeiServicesGetBootMode (&BootMode);

  if (IsBiosUpdateInProgress () && (BootMode != BOOT_IN_RECOVERY_MODE)) {
    PeiServicesSetBootMode (BOOT_ON_FLASH_UPDATE);
    //
    // For recovery module to be dispatched.
    //
    PeiServicesInstallPpi (&mPpiListRecoveryBootMode);
  }

  //
  // PatchConfigurationDataPreMem
  //
  VariableSize = sizeof (InitSetupFlag);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"InitSetupVariable",
                               &gSetupVariableGuid,
                               &InitSetupVolVarAttr,
                               &VariableSize,
                               &InitSetupFlag
                               );
  if (Status == EFI_NOT_FOUND) {
    IsFirstBoot = TRUE;
  }

  if ((IsFirstBoot) || (BootMode == BOOT_WITH_DEFAULT_SETTINGS)) {
    Status = PeiServicesInstallPpi (mPatchConfigurationDataPreMemPpi);
    ASSERT_EFI_ERROR (Status);
  }

  if (IsBiosUpdateInProgress () && (BootMode != BOOT_IN_RECOVERY_MODE)) {
    PeiServicesSetBootMode (BOOT_ON_FLASH_UPDATE);
    //
    // For recovery module to be dispatched.
    //
    PeiServicesInstallPpi (&mPpiListRecoveryBootMode);
  }

  // Cache the Setup variable
  DEBUG ((DEBUG_INFO, "Caching Setup Data.\n"));
  Status = SetupDataCacheInit ();
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (SETUP_DATA);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"Setup",
                               &gSetupVariableGuid,
                               NULL,
                               &VariableSize,
                               &SystemConfiguration
                               );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Fail to get System Configuration and set the configuration to production mode!\n"));
    FwConfig = 0;
    PcdSetBoolS (PcdPcieWwanEnable, FALSE);
    PcdSetBoolS (PcdWwanResetWorkaround, FALSE);
  } else {
    FwConfig = SystemConfiguration.FirmwareConfiguration;
    PcdSetBoolS (PcdPcieWwanEnable, SystemConfiguration.WwanEnable);
    PcdSetBoolS (PcdWwanResetWorkaround, SystemConfiguration.WwanResetWorkaround);
  }
  GpioInitEarlyWwanPreMem();
  if (PcdGetBool (PcdDTbtEnable) && SystemConfiguration.DiscreteTbtSupport) {
    InstallPeiDTbtPolicy ();
  }


DEBUG_CODE_BEGIN();
  VariableSize = sizeof (DEBUG_CONFIG_DATA);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"DebugConfigData",
                               &gDebugConfigVariableGuid,
                               NULL,
                               &VariableSize,
                               &DebugConfigData
                               );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to get Debug Configuration data variable!\n"));
  } else {
    BuildDebugConfigDataHob (&DebugConfigData);
  }
DEBUG_CODE_END();

  ///
  ///
  ///
  ///

  //
  // Initialize Intel PEI Platform Policy
  //
#if FixedPcdGet8(PcdFspModeSelection) == 1
  //
  // FSP API mode call the function directly.
  //
  PeiPolicyInitPreMem (FwConfig);
#else
  //
  // FSP Dispatch mode or non-FSP build will depend on DefaultPolicyInit PPI.
  //
  Status = PeiServicesNotifyPpi (&mSiPreMemDefaultPolicyInitNotifyList);
  ASSERT_EFI_ERROR (Status);
#endif

  Status = CreateFastBootHob (VariableServices);
  ASSERT_EFI_ERROR (Status);

  Status = PeiServicesNotifyPpi (&mWdtPpiNotifyList);
  ASSERT_EFI_ERROR (Status);

  Status = PeiServicesNotifyPpi (&mSiPreMemPolicyNotifyList);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Do basic PCH init
  ///
  PlatformPchInit (VariableServices);

  ///
  /// Set what state (S0/S5) to go to when power is re-applied after a power failure (G3 state)
  ///
  SetTheStateToGoAfterG3 (VariableServices);

  ABase = PmcGetAcpiBase ();

  ///
  /// Clear all pending SMI. On S3 clear power button enable so it will not generate an SMI.
  ///
  IoWrite16 (ABase + R_ACPI_IO_PM1_EN, 0);
  IoWrite32 (ABase + R_ACPI_IO_GPE0_EN_127_96, 0);
  ///----------------------------------------------------------------------------------
  ///
  /// BIOS should check the wake status before memory initialization to determine
  /// if ME has reset the system while the host was in a sleep state. If platform was not in a sleep state,
  /// BIOS should ensure a non-sleep exit path is taken by forcing an s5 exit.
  ///
  if (PmcGetSleepTypeAfterWake () == PmcNotASleepState) {
    PmcSetSleepState (PmcS5SleepState);
  }

  if (BootMode == BOOT_ON_S3_RESUME) {
    //
    // A platform PEIM should enable R/W access to E/F segment in the S3 boot path
    // otherwise, this AP wakeup buffer can't be accessed during CPU S3 operation.
    //
    McD0BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, 0);
    PciSegmentWrite8 (McD0BaseAddress + R_SA_PAM0, 0x30);
    PciSegmentWrite8 (McD0BaseAddress + R_SA_PAM5, 0x33);
    PciSegmentWrite8 (McD0BaseAddress + R_SA_PAM6, 0x33);
  }

  if (BootMode == BOOT_ON_S3_RESUME) {
    PcdSet8S (PcdCRBIdleByPass, 0x0);
  }

  ///
  /// Install Pre Memory PPIs
  ///
  Status = PeiServicesInstallPpi (&mPreMemPpiList[0]);
  ASSERT_EFI_ERROR (Status);

  PostCode(PLATFORM_INIT_PREMEM_EXIT);

  return Status;
}

#if FixedPcdGetBool(PcdBfxEnable) == 1
/**
  Prints NEM map information.
**/
VOID
EFIAPI
ReportNemInformation (
  VOID
  )
{
  EFI_STATUS  Status;
  UINTN       IbbBase;
  UINTN       NemBase;
  UINTN       TempRamBase;
  UINTN       FitBase;
  UINT32      IbbSize;
  UINT32      NemSize;
  UINT32      TempRamSize;

  //
  // Report the NEM map information
  //
  Status = GetIbbBaseAndSize (&IbbBase, &IbbSize);
  ASSERT_EFI_ERROR (Status);
  Status = GetNemBaseAndSize (&NemBase, &NemSize);
  ASSERT_EFI_ERROR (Status);
  Status = GetTempRamBaseAndSize (&TempRamBase, &TempRamSize);
  ASSERT_EFI_ERROR (Status);
  Status = GetFitBase (&FitBase);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "IBB Base = 0x%x. IBB Size = 0x%x\n", IbbBase, IbbSize));
  DEBUG ((DEBUG_INFO, "NEM Base = 0x%x. NEM Size = 0x%x\n", NemBase, NemSize));
  DEBUG ((DEBUG_INFO, "T-RAM Base = 0x%x. T-RAM Size = 0x%x\n", TempRamBase, TempRamSize));
  DEBUG ((DEBUG_INFO, "FIT Base 0x%x\n", FitBase));
}
#endif


/**
  Platform Init before memory PEI module entry point

  @param[in]  FileHandle           Not used.
  @param[in]  PeiServices          General purpose services available to every PEIM.

  @retval     EFI_SUCCESS          The function completes successfully
  @retval     EFI_OUT_OF_RESOURCES Insufficient resources to create database
**/
EFI_STATUS
EFIAPI
PlatformInitAdvancedPreMemEntryPoint (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS              Status;
  BIOS_ID_IMAGE           BiosIdImage;
#if FixedPcdGetBool(PcdBfxEnable) == 1
  BOOLEAN                 FirstEntry;
  UINTN                   FitBase;
  EFI_PEI_PPI_DESCRIPTOR  *PeiPpiDescriptor;
  VOID                    *PeiPpi;
#if (FixedPcdGetBool(PcdFspWrapperEnable) == 0 || FixedPcdGet8(PcdFspModeSelection) == 0)
  FSP_TEMP_RAM_EXIT_PPI   *TempRamExitPpi;
#endif

  FirstEntry = TRUE;

  DEBUG ((DEBUG_INFO, "PlatformInitAdvancedPreMemEntryPoint() - Start\n"));

  Status = PeiServicesRegisterForShadow (FileHandle);

  if (Status == EFI_NOT_FOUND) {
    ASSERT_EFI_ERROR (Status);
  } else if (Status == EFI_ALREADY_STARTED) {
    FirstEntry = FALSE;
  }
  ///
  /// Do Early PCH init
  ///
  EarlyPlatformPchInit ();

  if (FirstEntry) {
#endif
    Status = GetBiosId (&BiosIdImage);
    if (Status == EFI_SUCCESS) {
      DEBUG ((DEBUG_INFO, "+==================================================+\n"));
      DEBUG ((DEBUG_INFO, "| BIOS version [%s]  |\n", &BiosIdImage.BiosIdString));
      DEBUG ((DEBUG_INFO, "+==================================================+\n"));
    }
#if FixedPcdGetBool(PcdBfxEnable) == 1
    ///
    /// Print NEM map information
    ///
    ReportNemInformation ();
#endif
    ///
    /// Initialize Nvram to default when checksum computation is failed
    ///
    SecondaryNvRamInit ();

    ///@todo it should be moved to Si Pkg.
    ///
    /// Do Early PCH init
    ///
    EarlyPlatformPchInit ();

#if FixedPcdGet8(PcdFspModeSelection) == 1
    //
    // Install ME reset call back function.
    //
    RegisterMeReset ();

#endif

    ///
    /// Performing PlatformInitPreMem after PeiReadOnlyVariable2 PPI produced
    ///
    Status = PeiServicesNotifyPpi (&mPreMemNotifyList);
#if FixedPcdGetBool(PcdBfxEnable) == 1
  }

  if (!FirstEntry) {
    ///
    /// Install Stall PPI
    ///
    Status = InstallStallPpi ();
    ASSERT_EFI_ERROR (Status);

    if (BootMediaIsUfs ()) {
      //
      // Install NVM Ownership PPI
      //
      Status = PeiServicesInstallPpi (&mNvmOwnershipAcquiredPpi);
      ASSERT_EFI_ERROR (Status);

      //
      // Install GetFv Callback
      //
      Status = PeiServicesNotifyPpi (&mGetFvNotifyList);
      ASSERT_EFI_ERROR (Status);
    }

    //
    // Reinstall the Master Boot Mode PPI
    //
    Status = PeiServicesLocatePpi (
               &gEfiPeiMasterBootModePpiGuid,
               0,
               &PeiPpiDescriptor,
               (VOID **) &PeiPpi
               );
    if (Status == EFI_SUCCESS) {

      Status = PeiServicesReInstallPpi (
                 PeiPpiDescriptor,
                 &mPpiBootMode
                 );
      ASSERT_EFI_ERROR (Status);
    }

    //
    // Reinstall Intel platform policies
    //
#if FixedPcdGetBool(PcdFspWrapperEnable) == 0
    Status = PeiPolicyReinstall ();
    ASSERT_EFI_ERROR (Status);
#endif
#endif

    ///
    /// After code reorangized, memorycallback will run because the PPI is already
    /// installed when code run to here, it is supposed that the InstallEfiMemory is
    /// done before.
    ///
    Status = PeiServicesNotifyPpi (&mMemDiscoveredNotifyList);
#if FixedPcdGetBool(PcdBfxEnable) == 1
    ///
    /// Migrate FIT
    ///
    if (BootMediaIsUfs ()) {
      //
      // Copy FIT to a HOB so it is available in post-memory
      //
      Status = GetFitBase (&FitBase);
      if (!EFI_ERROR (Status)) {
        Status = ProduceFitHob (FitBase);
        ASSERT_EFI_ERROR (Status);
      }

      //
      // Migrate GDT Pointer
      //
      MigrateGdtPointer ();
    }
#endif
#if FixedPcdGetBool(PcdBfxEnable) == 1
    ///
    /// Reinstall SecCore PPIs in permanent memory
    ///
    Status = ReinstallSecCorePpis ();
    ASSERT_EFI_ERROR (Status);

#if (FixedPcdGetBool(PcdFspWrapperEnable) == 0 || FixedPcdGet8(PcdFspModeSelection) == 0)
    PeiServices = GetPeiServicesTablePointer ();
    Status = (*PeiServices)->LocatePpi (
                               PeiServices,
                               &gFspTempRamExitPpiGuid,
                               0,
                               NULL,
                               (VOID **) &TempRamExitPpi
                               );
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status)) {
      return Status;
    }
    TempRamExitPpi->TempRamExit (NULL);
#else
    FspWrapperTempRamExit ();
#endif
  }
#endif

  DEBUG ((DEBUG_INFO, "PlatformInitAdvancedPreMemEntryPoint() - End\n"));

  return Status;
}

#if FixedPcdGetBool(PcdBfxEnable) == 1
/**
  Migrate the GDT pointer from temporary RAM to permanent RAM.

**/
VOID
MigrateGdtPointer (
  VOID
  )
{
  EFI_STATUS             Status;
  IA32_DESCRIPTOR        Gdtr;
  EFI_PHYSICAL_ADDRESS   GdtBase;

  DEBUG ((DEBUG_INFO, "Migrate GDT Pointer to Permanent Memory\n"));

  AsmReadGdtr (&Gdtr);
  //
  // Allocate the permanent memory.
  //
  Status = PeiServicesAllocatePages (
             EfiBootServicesCode,
             EFI_SIZE_TO_PAGES (Gdtr.Limit + 1),
             &GdtBase
             );
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "GdtBase = 0x%x\n", (UINTN) GdtBase));

  //
  // Gdt table needs to be migrated into memory.
  //
  CopyMem ((VOID *) (UINTN) GdtBase, (VOID *) Gdtr.Base, Gdtr.Limit + 1);
  Gdtr.Base = (UINT32) GdtBase;
  DEBUG ((DEBUG_INFO, "Write GDT back with permanent memory\n"));
  AsmWriteGdtr (&Gdtr);
  return;
}
#endif
