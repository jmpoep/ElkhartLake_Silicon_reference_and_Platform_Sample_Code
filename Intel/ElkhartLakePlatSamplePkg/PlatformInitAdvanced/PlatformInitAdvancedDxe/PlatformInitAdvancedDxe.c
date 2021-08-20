/** @file
  Source code file for the Platform Init Advanced DXE module

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/
#include "PlatformInitAdvancedDxe.h"
#include <CpuRegs.h>
#include <Guid/EventGroup.h>
#include <Library/BootGuardLib.h>
#include <Protocol/CpuInfo.h>
#include <Protocol/PlatformNvsArea.h>
#include <Protocol/VariableLock.h>
#include <SoftwareGuardSetupData.h>
#include <Library/CpuPlatformLib.h>
#include <Library/SmbiosProcessorLib.h>
#include <Guid/TpmInstance.h>
#include <Library/Tpm2CommandLib.h>
#include <Library/DxeSmbiosFirmwareVersionInfoLib.h>
#include <Library/PostCodeLib.h>
#include <PlatformPostCode.h>
#include <Register/Cpuid.h>
#include <Protocol/Tcg2Protocol.h>
#include <Library/TpmMeasurementLib.h>
#include <Library/UefiLib.h>
#include <Protocol/ResetNotification.h>
#if FixedPcdGetBool(PcdFspWrapperEnable) == 1
#include <Library/MtrrLib.h>
#include <Library/SiMtrrLib.h>
#include <Protocol/MpService.h>
#endif
#if FixedPcdGetBool (PcdBfxEnable) == 1
#include <Bus/Ufs/UfsPassThruDxe/UfsPassThruHci.h>
#include <Protocol/UfsDeviceConfig.h>
#endif

GLOBAL_REMOVE_IF_UNREFERENCED EFI_EVENT                         EndOfDxeEvent;
GLOBAL_REMOVE_IF_UNREFERENCED PLATFORM_NVS_AREA_PROTOCOL        mPlatformNvsAreaProtocol;

#define TBT_SECURITY_EVENT_STRING      "DMA Protection Disabled"
#define TBT_SECURITY_EVENT_STRING_LEN  (sizeof(TBT_SECURITY_EVENT_STRING) - 1)

///
/// SGX EPC definitions
///
#define EPC_FRACTION_NUMERATOR    381
#define EPC_FRACTION_DENOMINATOR  512
#define EPC_SUBTRACT_MB           SIZE_2MB
#define PRM_BOTTOM_LIMIT          4

#define SINIT_SVN_VARIABLE_NAME   (L"SinitSvn")
///
/// A NV-RAM variable for storing SINIT SVN value.
///
typedef struct _SINIT_SVN {
  ///
  /// Non-zero version indicates the variable is being initialized or valid
  ///
  UINT8  SvnNumber;
} SINIT_SVN;

VOID
EFIAPI
PlatformResetNotificationCallback (
  IN EFI_RESET_TYPE           ResetType,
  IN EFI_STATUS               ResetStatus,
  IN UINTN                    DataSize,
  IN VOID                     *ResetData OPTIONAL
  );

/**
  This function handles PlatformInit task at the end of DXE

  @param[in]  Event     The Event this notify function registered to.
  @param[in]  Context   Pointer to the context data registered to the
                        Event.
**/
VOID
EFIAPI
EndofDxeCallback (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
#if FixedPcdGetBool (PcdBfxEnable) == 1
  EFI_UFS_DEVICE_CONFIG_PROTOCOL   *UfsDeviceConfig;
  UFS_UNIT_DESC                    UnitDescriptor;
  UINT32                           UnitDescriptorSize;
  EFI_STATUS                       Status;
  UINT8                            Value;
#endif
  static BOOLEAN                S3DataSaved = FALSE;
  UINT16                        ABase;
  UINT32                        SmiEn;
  UINT16                        Pm1Sts;

  gBS->CloseEvent (Event);

  if (S3DataSaved) {
    return ;
  }

  ABase = PmcGetAcpiBase ();
  SmiEn = IoRead32 (ABase + R_ACPI_IO_SMI_EN);
  //
  // Disabled Legacy USB Logic that generates SMI, during S3 Resume.
  //
  SmiEn &= ~(B_ACPI_IO_SMI_EN_LEGACY_USB | B_ACPI_IO_SMI_EN_LEGACY_USB2 | B_ACPI_IO_SMI_EN_PERIODIC | B_ACPI_IO_SMI_EN_SWSMI_TMR);

  S3BootScriptSaveIoWrite (
    S3BootScriptWidthUint32,
    (UINTN) (ABase + R_ACPI_IO_SMI_EN),
    1,
    &SmiEn
    );
  //
  // Clear bust master status bit on S3 resume
  //
  Pm1Sts = B_ACPI_IO_PM1_STS_BM;

  S3BootScriptSaveIoWrite (
    S3BootScriptWidthUint16,
    (UINTN) (ABase + R_ACPI_IO_PM1_STS),
    1,
    &Pm1Sts
    );

  S3DataSaved = TRUE;


#if FixedPcdGetBool (PcdBfxEnable) == 1
  ///
  /// UFS 2.1 spec Section 14.2 Enable fPowerOnWPEn flag  if we're not in capsule update mode,
  ///
  Value = 1;
  Status = gBS->LocateProtocol (&gEfiUfsDeviceConfigProtocolGuid, NULL, (VOID **)&UfsDeviceConfig);
  UnitDescriptorSize = sizeof (UFS_UNIT_DESC);

  if (!EFI_ERROR (Status)) {
    Status = UfsDeviceConfig->RwUfsDescriptor (
                                UfsDeviceConfig,
                                TRUE,
                                0x02,
                                1,
                                0,
                                (UINT8*)&UnitDescriptor, &UnitDescriptorSize
                                );

    if ((UnitDescriptor.LunWriteProt && 0x01) && (GetBootModeHob () != BOOT_ON_FLASH_UPDATE)) {
      DEBUG ((DEBUG_INFO, "Not booting from capsule update. So enable UFS boot partition write-protection.\n"));

      Status = UfsDeviceConfig->RwUfsFlag (UfsDeviceConfig, FALSE, 3, &Value);  // Index value of flag "fPowerOnWPEn" is 3
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "RwUfsFlag() Failed, Status = %r\n", Status));
      }
    }
  }
#endif

  ///
  /// Verify if Boot Guard is supported
  ///
  if (IsBootGuardSupported ()) {
    ///
    /// Identify if Revocation is requested by Boot Guard ACM
    ///
    if (AsmReadMsr64 (MSR_BOOT_GUARD_SACM_INFO) & BIT7) {
      BootGuardOemRevocationHook ();
    }
  }

}

/**
  Registers callback for.PlatformInitEndOfDxe

**/
VOID
RegisterEndOfDxeCallbacks (
  VOID
  )
{
  EFI_STATUS                     Status;

  ///
  /// Performing PlatformInitEndOfDxe after the gEfiEndOfDxeEventGroup is signaled.
  ///
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  EndofDxeCallback,
                  NULL,
                  &gEfiEndOfDxeEventGroupGuid,
                  &EndOfDxeEvent
                  );
  ASSERT_EFI_ERROR (Status);

}

#if FixedPcdGetBool(PcdFspWrapperEnable) == 1
/**
  A minimal wrapper function that allows MtrrSetAllMtrrs() to be passed to
  EFI_MP_SERVICES_PROTOCOL.StartupAllAPs() as Procedure.

  @param[in] Buffer  Pointer to an MTRR_SETTINGS object, to be passed to
                     MtrrSetAllMtrrs().
**/
VOID
EFIAPI
SetMtrrsFromBuffer (
  IN VOID *Buffer
  )
{
  MtrrSetAllMtrrs (Buffer);
}
#endif

/**
  This function handles PlatformInitDxe task at the ready to boot

  @param[in]  Event     The Event this notify function registered to.
  @param[in]  Context   Pointer to the context data registered to the Event.
**/
VOID
EFIAPI
PlatformDxeReadyToBootCallback (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
#if FixedPcdGetBool(PcdFspWrapperEnable) == 1
  EFI_STATUS                Status;
  MTRR_SETTINGS             MtrrSetting;
  EFI_MP_SERVICES_PROTOCOL  *MpService;

  DEBUG ((DEBUG_INFO, "PlatformDxeReadyToBootCallback start\n"));

  Status = MtrrTransfer2DefaultWB (&MtrrSetting);
  if (EFI_ERROR (Status)) {
    return;
  }

  //
  // Synchronize the update with all APs
  //
  Status = gBS->LocateProtocol (
                  &gEfiMpServiceProtocolGuid,
                  NULL,
                  (VOID **)&MpService
                  );
  if (!EFI_ERROR (Status)) {
    MtrrGetAllMtrrs (&MtrrSetting);
    MpService->StartupAllAPs (
                 MpService,          // This
                 SetMtrrsFromBuffer, // Procedure
                 FALSE,              // SingleThread
                 NULL,               // WaitEvent
                 0,                  // TimeoutInMicrosecsond
                 &MtrrSetting,       // ProcedureArgument
                 NULL                // FailedCpuList
                 );
  }

  DEBUG ((DEBUG_INFO, "PlatformDxeReadyToBootCallback end\n"));
#endif
  gBS->CloseEvent (Event);

  return;
}

/**
  Registers callback for PlatformDxeReadyToBoot

**/
VOID
RegisterReadyToBootCallback (
  VOID
  )
{
  EFI_STATUS                     Status;
  EFI_EVENT                      Event;

  Status = EfiCreateEventReadyToBootEx (
             TPL_CALLBACK,
             PlatformDxeReadyToBootCallback,
             NULL,
             &Event
             );

  ASSERT_EFI_ERROR (Status);
}

/**
  Call back function for reset notification.

  @param[in] ResetType            UEFI defined reset type.
  @param[in] ResetStatus          The status code for the reset.
  @param[in] DataSize             The size of ResetData in bytes.
  @param[in] ResetData            Optional element used to introduce a platform specific reset.
                                  The exact type of the reset is defined by the EFI_GUID that follows
                                  the Null-terminated Unicode string.
**/
VOID
EFIAPI
PlatformResetNotificationCallback (
  IN EFI_RESET_TYPE           ResetType,
  IN EFI_STATUS               ResetStatus,
  IN UINTN                    DataSize,
  IN VOID                     *ResetData OPTIONAL
  )
{
  EFI_STATUS                  Status;

  DEBUG ((DEBUG_INFO, "PlatformResetNotificationCallback\n"));

  Status = Tpm2Shutdown (TPM_SU_CLEAR);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Tpm2Shutdown (TPM_SU_CLEAR) failed: %r\n", Status));
  }
}


/**
  Hook to reset notification protocol to properly reset function with TPM.
  @param[in]  Event     Event whose notification function is being invoked
  @param[in]  Context   Pointer to the notification function's context
**/
VOID
EFIAPI
OnResetNotifyInstall (
  IN EFI_EVENT                      Event,
  IN VOID                           *Context
  )
{

  EFI_STATUS  Status;
  EFI_RESET_NOTIFICATION_PROTOCOL   *ResetNotify;

  Status = gBS->LocateProtocol (&gEfiResetNotificationProtocolGuid, NULL, (VOID **) &ResetNotify);
  if (!EFI_ERROR (Status)) {
    ResetNotify->RegisterResetNotify (ResetNotify, PlatformResetNotificationCallback);
    if(Event) gBS->CloseEvent (Event);
  }
}

/**
  Creates a UEFI variable for OS with all data regarding SGX EPC

  @retval EPC_BIOS_CONFIG   Pointer to BIOS EPC variable structure
**/
EPC_BIOS_CONFIG *
CreateSgxInfoForOs (
  VOID
  )
{
  EFI_STATUS                                           Status;
  UINT64                                               SupportedPrmBins;
  UINT64                                               PrmSize;
  UINT8                                                Index;
  UINT8                                                BinVal;
  UINT64                                               C6DramSub;
  EPC_BIOS_CONFIG                                      *EpcBios;
  CPUID_INTEL_SGX_CAPABILITIES_0_SUB_LEAF_EAX          SgxCapabilitiesEax;
  UINT32                                               SgxCapabilitiesEbx;
  CPUID_INTEL_SGX_CAPABILITIES_0_SUB_LEAF_EDX          SgxCapabilitiesEdx;
  CPUID_INTEL_SGX_CAPABILITIES_RESOURCES_SUB_LEAF_EAX  SgxResourcesEax;
  CPUID_INTEL_SGX_CAPABILITIES_RESOURCES_SUB_LEAF_EBX  SgxResourcesEbx;
  CPUID_INTEL_SGX_CAPABILITIES_RESOURCES_SUB_LEAF_ECX  SgxResourcesEcx;
  CPUID_INTEL_SGX_CAPABILITIES_RESOURCES_SUB_LEAF_EDX  SgxResourcesEdx;
  UINT32                                               VariableAttr;
  UINTN                                                VariableSize;
  CPU_SETUP                                            CpuSetup;

  VariableSize = sizeof (CPU_SETUP);
  Status = gRT->GetVariable (
                  L"CpuSetup",
                  &gCpuSetupVariableGuid,
                  &VariableAttr,
                  &VariableSize,
                  &CpuSetup
                  );
  ASSERT_EFI_ERROR (Status);

  if (EFI_ERROR (Status)) {
    return NULL;
  }

  EpcBios      = (EPC_BIOS_CONFIG*) AllocateRuntimePool (sizeof (EPC_BIOS_CONFIG));
  C6DramSub    = 0;

  if (EpcBios == NULL) {
    DEBUG ((DEBUG_ERROR, "CreateSgxInfoForOs: Memory allocation for EPC structure failed"));
    return NULL;
  }

  ///
  /// Presence of SGX feature is detectable by reading CPUID.(EAX=0x12, ECX=0x0):EAX[0]
  ///
  AsmCpuidEx (
    CPUID_INTEL_SGX,
    CPUID_INTEL_SGX_CAPABILITIES_0_SUB_LEAF,
    &SgxCapabilitiesEax.Uint32,
    &SgxCapabilitiesEbx,
    NULL,
    &SgxCapabilitiesEdx.Uint32
    );

  ///
  /// If SGX was not activated
  ///
  if (SgxCapabilitiesEax.Bits.SGX1 == 0) {
    DEBUG ((DEBUG_INFO, "CreateSgxInfoForOs: SGX feature is not present, setting AllocatedEpcSize = 0\n"));
    EpcBios->AllocatedEpcSize = 0;
  } else {
    //
    // Read CPUID.(EAX=0x12, ECX=0x2) to get EPC Base and Size
    //
    AsmCpuidEx (
      CPUID_INTEL_SGX, CPUID_INTEL_SGX_CAPABILITIES_RESOURCES_SUB_LEAF,
      &SgxResourcesEax.Uint32,
      &SgxResourcesEbx.Uint32,
      &SgxResourcesEcx.Uint32,
      &SgxResourcesEdx.Uint32
      );

    //
    // Check if the first sub-leaf is a valid EPC section
    //
    if ((SgxResourcesEax.Bits.SubLeafType) != 0x1) {
      EpcBios->AllocatedEpcSize = 0;
    } else {
      ///
      /// If SGX was enabled, this variable will hold the EPC length as it was read from CPUID SGX sub-leaf
      /// Else this variable will hold the value 0
      ///
      EpcBios->AllocatedEpcSize = (UINT32) (UINTN) (LShiftU64 ((UINT64) (SgxResourcesEdx.Bits.HighSizeOfEpcSection), 32) + LShiftU64 ((UINT64) (SgxResourcesEcx.Bits.LowSizeOfEpcSection), 12));
    }
  }

  ///
  /// If C6DRAM is supported, then PRMRR size of 2 MB will be supported. Reduce 0.5 MB from reported EPC size
  ///
  SupportedPrmBins = AsmReadMsr64 (MSR_PRMRR_VALID_CONFIG);

  C6DramSub = 0;

  EpcBios->SupportedPrmBins = (UINT32) (UINTN) SupportedPrmBins;
  DEBUG ((DEBUG_INFO, "CreateSgxInfoForOs: SupportedPrmBins = 0x%ll016X\n", SupportedPrmBins));

  ///
  /// Traverse over all SupportedPrmBins, skip the ones, that are lower or equal to 2 MB
  ///
  for (Index = 0, PrmSize = 1; Index < sizeof (EpcBios->EpcMap) / sizeof (EpcBios->EpcMap[0]); Index++) {

    EpcBios->EpcMap[Index] = 0;

    ///
    /// No More supported PRM size
    ///
    if (SupportedPrmBins == 0) {
      continue;
    }
    BinVal = SupportedPrmBins & BIT0;
    if (Index != 0) {

      ///
      /// Current PRM size in MB
      ///
      PrmSize = LShiftU64 (PrmSize,1);
    }
    SupportedPrmBins = RShiftU64 (SupportedPrmBins, 1);

    ///
    /// Don't include PRM sizes that are lower than 4MB
    ///
    if (BinVal == 0 || PrmSize < PRM_BOTTOM_LIMIT) {
      continue;
    } else {

      ///
      /// Calculate the supported EPC size: PRM_SIZE * (191/256) - 2MB - (0.5MB, if C6 DRAM is supported)
      ///
      DEBUG ((DEBUG_INFO, "CreateSgxInfoForOs: Supported PRM size = %d MB\n", PrmSize));
      EpcBios->EpcMap[Index] = (UINT32)(DivU64x32 (MultU64x32 (PrmSize * SIZE_1MB, EPC_FRACTION_NUMERATOR), EPC_FRACTION_DENOMINATOR) - EPC_SUBTRACT_MB - C6DramSub);
      DEBUG ((DEBUG_INFO, "CreateSgxInfoForOs: EpcBios->EpcMap[%d] = 0x%ll016X MB\n", Index, EpcBios->EpcMap[Index]));
      EpcBios->MaxEpcSize = EpcBios->EpcMap[Index];
    }
  }

  DEBUG ((DEBUG_INFO, "CreateSgxInfoForOs: Final MaxEpcSize = 0x%ll016X MB\n", EpcBios->MaxEpcSize));
  DEBUG ((DEBUG_INFO, "CreateSgxInfoForOs end\n"));

  return EpcBios;
}

/**
 Update BIOS and OS EPC UEFI variables
**/
VOID
UpdateEpcVariables (
  VOID
  )
{
  EFI_STATUS                    Status;
  EFI_STATUS                    EpcBiosStatus;
  EFI_STATUS                    EpcOsStatus;
  UINTN                         EpcBiosConfigurationSize;
  EPC_BIOS_CONFIG               EpcBiosConfiguration;
  UINTN                         EpcOsConfigurationSize;
  EPC_OS_CONFIG                 EpcOsConfiguration;
  CPU_INFO_PROTOCOL             *CpuInfo;
  EPC_BIOS_CONFIG               *EpcBios;
  EDKII_VARIABLE_LOCK_PROTOCOL  *VariableLock;
  UINTN                         VariableSize;
  UINT32                        VariableAttr;
  CPU_SETUP                     CpuSetup;

  VariableSize = sizeof (CPU_SETUP);
  Status = gRT->GetVariable (
                  L"CpuSetup",
                  &gCpuSetupVariableGuid,
                  &VariableAttr,
                  &VariableSize,
                  &CpuSetup
                  );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Reading EPC_BIOS UEFI variable
  ///
  EpcBiosConfigurationSize = sizeof (EPC_BIOS_CONFIG);
  EpcBiosStatus = gRT->GetVariable (
                         EPC_BIOS,
                         &gEpcBiosDataGuid,
                         NULL,
                         &EpcBiosConfigurationSize,
                         &EpcBiosConfiguration
                         );
  ///
  /// Reading EPC_OS_CTRL UEFI variable
  ///
  EpcOsConfigurationSize = sizeof (EPC_OS_CONFIG);
  EpcOsStatus = gRT->GetVariable (
                         EPC_OS_CTRL,
                         &gEpcOsDataGuid,
                         NULL,
                         &EpcOsConfigurationSize,
                         &EpcOsConfiguration
                         );

  if (!EFI_ERROR(EpcBiosStatus)) {
    DEBUG ((DEBUG_INFO, "Old MaxEpcSize from GetVariable = 0x%X\n", EpcBiosConfiguration.MaxEpcSize));
    DEBUG ((DEBUG_INFO, "Old SupportedPrmBins from GetVariable = 0x%X\n", EpcBiosConfiguration.SupportedPrmBins));
    DEBUG ((DEBUG_INFO, "Old EpcSize from GetVariable = 0x%X\n", EpcBiosConfiguration.AllocatedEpcSize));
  }

  if (!EFI_ERROR(EpcOsStatus)) {
    DEBUG ((DEBUG_INFO, "Old RequestedEpcSize from GetVariable = 0x%X\n", EpcOsConfiguration.RequestedEpcSize));
  }

  ///
  /// If SGX is not in 'Software Control' mode, delete EPC_BIOS (if found) & delete EPC_OS_CTRL variable (if found).
  ///
  if (CpuSetup.EnableSgx != SGX_SOFTWARE_CONTROL) {

    if (EpcBiosStatus != EFI_NOT_FOUND) {
      ///
      /// SGX is not in 'Software Control' mode and EPC_BIOS variable is found. Hence, deleting EPC_BIOS variable.
      ///
      DEBUG ((DEBUG_INFO, "SGX is not in 'Software Control' mode and EPC_BIOS variable is found, deleting EPC_BIOS variable \n"));
      ZeroMem (&EpcBiosConfiguration, EpcBiosConfigurationSize);

      Status = gRT->SetVariable (
                    EPC_BIOS,
                    &gEpcBiosDataGuid,
                    0,
                    0,
                    NULL
                    );
    }

    if (EpcOsStatus != EFI_NOT_FOUND) {
      ///
      /// SGX is not in 'Software Control' mode and EPC_OS_CTRL variable is found. Hence, deleting EPC_OS_CTRL variable.
      ///
      DEBUG ((DEBUG_INFO, "SGX is not in 'Software Control' mode and EPC_OS_CTRL variable is found, deleting EPC_OS_CTRL variable \n"));
      ZeroMem (&EpcOsConfiguration, EpcOsConfigurationSize);

      Status = gRT->SetVariable (
                    EPC_OS_CTRL,
                    &gEpcOsDataGuid,
                    0,
                    0,
                    NULL
                    );
    }
    return;
  }

  ///
  /// Get the CPU platform setup policy.
  ///
  Status = gBS->LocateProtocol (&gCpuInfoProtocolGuid, NULL, (VOID **) &CpuInfo);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Located CpuInfo Protocol Status = %r\n", Status));
    return;
  }
  EpcBios = CreateSgxInfoForOs ();

  ///
  /// If BIOS EPC UEFI variable initialization fails
  ///
  if (EpcBios == NULL) {
    return;
  }

  DEBUG ((DEBUG_INFO, "Saving UEFI variable EPC_BIOS\n"));
  DEBUG ((DEBUG_INFO, "New MaxEpcSize from HOB = 0x%X\n", EpcBios->MaxEpcSize));
  DEBUG ((DEBUG_INFO, "New SupportedPrmBins from HOB = 0x%X\n", EpcBios->SupportedPrmBins));
  DEBUG ((DEBUG_INFO, "New AllocatedEpcSize from HOB = 0x%X\n", EpcBios->AllocatedEpcSize));

  ///
  /// SGX is in 'Software Control' mode, need to update EPC_BIOS variable
  ///
  DEBUG ((DEBUG_INFO, "SGX is in 'Software Control' mode, updating EPC_BIOS variable \n"));
  Status = gRT->SetVariable (
                  EPC_BIOS,
                  &gEpcBiosDataGuid,
                  EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
                  sizeof (EPC_BIOS_CONFIG),
                  EpcBios
                  );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Locking EPC_BIOS variable, setting it to be read only
  ///
  Status = gBS->LocateProtocol (&gEdkiiVariableLockProtocolGuid, NULL, (VOID **) &VariableLock);
  if (!EFI_ERROR (Status)) {
    Status = VariableLock->RequestToLock (VariableLock, EPC_BIOS, &gEpcBiosDataGuid);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO, "BIOS was unable to lock EpcBios Variable\n"));
    }
  }

  ///
  /// If SGX was enabled and SGX setup option is set to auto
  ///
  if ((EpcBios->AllocatedEpcSize != 0) && (CpuSetup.EnableSgx == SGX_SOFTWARE_CONTROL)) {

    ///
    /// Updating PRMRR size setup option, to be compatible with current PRMRR size
    ///
    CpuSetup.PrmrrSize = SIZE_32MB;
    if (EpcBios->AllocatedEpcSize > SIZE_32MB) {
      CpuSetup.PrmrrSize = SIZE_64MB;
    }
    if (EpcBios->AllocatedEpcSize > SIZE_64MB) {
      CpuSetup.PrmrrSize = SIZE_128MB;
    }
    if (EpcBios->AllocatedEpcSize > SIZE_128MB) {
      CpuSetup.PrmrrSize = SIZE_256MB;
    }
    if (EpcBios->AllocatedEpcSize > SIZE_256MB) {
      CpuSetup.PrmrrSize = SIZE_512MB;
    }
    DEBUG ((DEBUG_INFO, "PRMRR size in setup options was changed to 0x%ll016X \n", CpuSetup.PrmrrSize));
  }

  Status = gRT->SetVariable (
                  L"CpuSetup",
                  &gCpuSetupVariableGuid,
                  VariableAttr,
                  sizeof (CPU_SETUP),
                  &CpuSetup
                  );
  ASSERT_EFI_ERROR (Status);
}

VOID
UpdateSgxSvnVariable(
 VOID
 )
{
  EFI_STATUS                    Status;
  CPU_INFO_PROTOCOL             *CpuInfo;
  EDKII_VARIABLE_LOCK_PROTOCOL  *VariableLock;
  UINT64                        MaskValue;
  UINT64                        Svn;
  MaskValue = BIT23 | BIT22 | BIT21 | BIT20 | BIT19 | BIT18 | BIT17 | BIT16;
  ///
  /// Locate CPU Info Protocol.
  ///
  Status = gBS->LocateProtocol (&gCpuInfoProtocolGuid, NULL, (VOID **) &CpuInfo);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Located CpuInfo Protocol Status = %r\n", Status));
    return;
  }

  Svn = CpuInfo->SgxInfo->SgxSinitNvsData;
  Svn &= MaskValue;
  Svn >>= 16;
  DEBUG ((DEBUG_INFO, "SINIT SE SVN:: Read the SgxSinitNvsData value =  0x%X \n", CpuInfo->SgxInfo->SgxSinitNvsData));
  DEBUG ((DEBUG_INFO, "SINIT SE SVN:: Programming NV Variable with the Svn value =  0x%X \n", Svn));
  Status = gRT->SetVariable (
                  SINIT_SVN_VARIABLE_NAME,
                  &gSinitSvnGuid,
                  EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                  sizeof (SINIT_SVN),
                  &Svn
                  );

  ASSERT_EFI_ERROR (Status);

  ///
  /// Locking SINIT_SVN_VARIABLE_NAME variable, setting it to be read only
  ///
  Status = gBS->LocateProtocol (&gEdkiiVariableLockProtocolGuid, NULL, (VOID **) &VariableLock);
  if (!EFI_ERROR (Status)) {
    Status = VariableLock->RequestToLock (VariableLock, SINIT_SVN_VARIABLE_NAME, &gSinitSvnGuid);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO, "BIOS was unable to lock SinitSvn Variable\n"));
    }
  }
}

/**
  Creates a UEFI variable for reporting platform SGX status information
**/
VOID
UpdateSgxPolicyStatusVariable (
  VOID
  )
{
  EFI_STATUS                    Status;
  EDKII_VARIABLE_LOCK_PROTOCOL  *VariableLock;
  UINTN                         VariableSize;
  UINT32                        VariableAttr;
  CPU_SETUP                     CpuSetup;
  SOFTWARE_GUARD_STATUS         SgxPolicyStatus;

  VariableSize = sizeof (CPU_SETUP);
  Status = gRT->GetVariable (
                  L"CpuSetup",
                  &gCpuSetupVariableGuid,
                  &VariableAttr,
                  &VariableSize,
                  &CpuSetup
                  );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Update SGX Status variables
  /// Initialize variables if CPU Setup data not found
  ///
  if (EFI_ERROR(Status)){
    DEBUG ((DEBUG_ERROR, "CPU Setup data was not found. Initalizing SGX variables.\n"));
    SgxPolicyStatus.SgxStatus = 0;
  } else {
    SgxPolicyStatus.SgxStatus = CpuSetup.EnableSgx;
  }

  ///
  /// Set SGX Status UEFI variable with updated values
  ///
  Status = gRT->SetVariable (
                SGX_POLICY,
                &gSgxPolicyStatusGuid,
                EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
                sizeof (SOFTWARE_GUARD_STATUS),
                &SgxPolicyStatus
                );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Locking SOFTWARE_GUARD_STATUS variable, setting it to be read only
  ///
  Status = gBS->LocateProtocol (&gEdkiiVariableLockProtocolGuid, NULL, (VOID **) &VariableLock);
  if (!EFI_ERROR (Status)) {
    Status = VariableLock->RequestToLock (VariableLock, SGX_POLICY, &gSgxPolicyStatusGuid);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO, "BIOS was unable to lock SgxPolicyStatus variable.\n"));
    } else {
      DEBUG ((DEBUG_INFO, "BIOS locked SgxPolicyStatus variable.\n"));
    }
  }
  ASSERT_EFI_ERROR (Status);
}

/**
  Security EndOfDxe CallBack Function
  If the firmware/BIOS has an option to enable and disable DMA protections via a VT-d switch in BIOS options, then the shipping configuration must be with VT-d protection enabled.
  On every boot where VT-d/DMA protection is disabled, or will be disabled, or configured to a lower security state, and a platform has a TPM enabled, then the platform SHALL
  extend an EV_EFI_ACTION event into PCR[7] before enabling external DMA
  The event string SHALL be "DMA Protection Disabled". The platform firmware MUST log this measurement in the event log using the string "DMA Protection Disabled" for the Event Data.
  Measure and log launch of TBT Security, and extend the measurement result into a specific PCR.
  Extend an EV_EFI_ACTION event into PCR[7] before enabling external DMA. The event string SHALL be "DMA Protection Disabled". The platform firmware MUST log this measurement
  in the event log using the string "DMA Protection Disabled" for the Event Data.

  @param[in] Event     - A pointer to the Event that triggered the callback.
  @param[in] Context   - A pointer to private data registered with the callback function.
**/
VOID
EFIAPI
ExtendPCR7CallBack (
  IN EFI_EVENT          Event,
  IN VOID               *Context
  )
{
  UINTN                 Status;
  UINT64                HashDataLen;

  DEBUG ((DEBUG_INFO, "ExtendPCR7CallBack START\n"));

  //
  // When VT-d/DMA protection is disabled and a platform has a TPM enabled,
  // the platform SHALL extend an EV_EFI_ACTION event into PCR[7]
  //
  HashDataLen = TBT_SECURITY_EVENT_STRING_LEN;

  Status = TpmMeasureAndLogData (
             7,
             EV_EFI_ACTION,
             TBT_SECURITY_EVENT_STRING,
             (UINT32) HashDataLen,
             TBT_SECURITY_EVENT_STRING,
             HashDataLen
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "TpmMeasureAndLogData Status: %d\n", Status));
  } else {
    DEBUG ((DEBUG_INFO, "TpmMeasureAndLogData Successfully\n"));
  }

  DEBUG ((DEBUG_INFO, "ExtendPCR7CallBack END\n"));
}

/**
  Register an End of DXE event for extended a TPM log to PCR[7] when vtd is diable
  This feature is introduced by TBT Security requirment
**/
VOID
RegisterExtendPCR7CallBack (
  VOID
  )
{
  EFI_STATUS                Status;
  UINTN                     DataSize;
  SA_SETUP                  *SaSetup;

  Status                    = EFI_SUCCESS;
  SaSetup                   = NULL;
  DataSize                  = 0;


  DataSize = sizeof (SA_SETUP);
  SaSetup = AllocateZeroPool (DataSize);
  if (SaSetup == NULL) {
    DEBUG ((DEBUG_ERROR, "Failed to allocate SaSetup size\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  Status = gRT->GetVariable (
                  L"SaSetup",
                  &gSaSetupVariableGuid,
                  NULL,
                  &DataSize,
                  SaSetup
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Get SaSetup Status: %d\n", Status));
    goto Exit;
  }

  if (SaSetup->EnableVtd == FALSE) {
    //
    // Register an End of DXE event for extended a TPM log to PCR[7]
    //
    DEBUG ((DEBUG_ERROR, "Rgister an End of DXE event for extended a TPM log to PCR[7] when Vtd is disable\n"));
    Status = gBS->CreateEventEx (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    ExtendPCR7CallBack,
                    NULL,
                    &gEfiEndOfDxeEventGroupGuid,
                    &EndOfDxeEvent
                    );
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Failed to Register an End of DXE event for extended a TPM log to PCR[7], Status: %d\n", Status));
      gBS->CloseEvent (EndOfDxeEvent);
      goto Exit;
    }
  }

Exit:
  if (SaSetup != NULL) {
    FreePool (SaSetup);
  }

}

/**
  Entry point for the driver.

  @param[in]  ImageHandle  Image Handle.
  @param[in]  SystemTable  EFI System Table.

  @retval     EFI_SUCCESS  Function has completed successfully.
  @retval     Others       All other error conditions encountered result in an ASSERT.
**/
EFI_STATUS
EFIAPI
PlatformInitAdvancedDxeEntryPoint (
  IN EFI_HANDLE               ImageHandle,
  IN EFI_SYSTEM_TABLE         *SystemTable
  )
{
  EFI_STATUS                  Status;
  SETUP_DATA                  SetupData;
  UINTN                       VariableSize;
  UINT32                      VariableAttr;
  UINT8                       *SecureBootState;
  VOID                        *Registration;

  PostCode (PLATFORM_INIT_DXE_ENTRY);
  Status = EFI_SUCCESS;

#if FixedPcdGetBool (PcdSinitAcmBinEnable) == 1
  Status = TxtSinitAcmLoad ();
  if (Status == EFI_SUCCESS) {
    DEBUG ((DEBUG_INFO, "TXTDXE: Found SINIT ACM In FV\n"));
  } else {
      DEBUG ((DEBUG_INFO, "TXTDXE: Error finding SINIT binary in FVs\n"));
  }
#endif

  Status = InstallSmbiosFviOemType (); // todo: remove it once Bios Guard convert the HOB generation.
  ASSERT_EFI_ERROR (Status);

  if (IsSgxSupported () && PcdGetBool (PcdSoftwareGuardEnable)) {
    UpdateEpcVariables ();
    UpdateSgxSvnVariable ();
    UpdateSgxPolicyStatusVariable ();
  }

  SecureBootState = NULL;
  GetVariable2 (L"SecureBootEnable", &gEfiSecureBootEnableDisableGuid, (VOID**)&SecureBootState, NULL);

  //
  // Set CsmControl Setup variable reflecting Secure boot status. Whenever Secure boot is enabled, CSM must be turned off.
  //
  VariableSize = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  &VariableAttr,
                  &VariableSize,
                  &SetupData
                  );
  ASSERT_EFI_ERROR (Status);

  SetupData.CsmControl = EFI_CSM_CONTROL_ALWAYS_OFF;
  SetupData.OpRomPost  = OPROM_EFI;

  if ((SecureBootState != NULL) && (*SecureBootState)) {
    if (!EFI_ERROR (Status)) {
      SetupData.CsmControl = EFI_CSM_CONTROL_ALWAYS_OFF;
      SetupData.OpRomPost  = OPROM_EFI;
    }
  }

  Status = gRT->SetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  VariableAttr,
                  VariableSize,
                  &SetupData
                  );
  ASSERT_EFI_ERROR (Status);

  if (SecureBootState != NULL) {
    FreePool (SecureBootState);
  }


  //
  // Initialize System Agent platform settings
  //
  SaPlatformInitDxe ();


  //
  // Update DIMM funtionalities for desktop and server boards
  //
  UpdateDimmPopulation();

  RegisterEndOfDxeCallbacks ();
  RegisterReadyToBootCallback ();

  //
  // Add Smbios type 4 and type 7 table.
  //
  AddSmbiosProcessorAndCacheTables ();

  //
  // Check if TPM2.0 exist.
  //
  if (CompareGuid (PcdGetPtr(PcdTpmInstanceGuid), &gEfiTpmDeviceInstanceNoneGuid)) {
  } else if (CompareGuid (PcdGetPtr(PcdTpmInstanceGuid), &gEfiTpmDeviceInstanceTpm12Guid)) {
  } else {
    //
    // Register Pch reset callback to shutdown TPM
    //
    EfiCreateProtocolNotifyEvent (
      &gEfiResetNotificationProtocolGuid,
      TPL_CALLBACK,
      OnResetNotifyInstall,
      NULL,
      &Registration
      );

  }

  //
  // Inform OS by TPM PCR7 when Vtd is disable
  //
  RegisterExtendPCR7CallBack();

  PostCode(PLATFORM_INIT_DXE_EXIT);

  return Status;
}

#if FixedPcdGetBool(PcdSinitAcmBinEnable) == 1
/**

  This function looks for SINIT ACM in FVs and updates TXT HOB
  with SINIT ACM Base and Size.

  @retval EFI_SUCCESS     - SINIT ACM found and copied.
  @retval EFI_NOT_FOUND   - If TxtInfoHob is not found
  @retval EFI_UNSUPPORTED - TXT Device memory not available.

**/
EFI_STATUS
TxtSinitAcmLoad (
  VOID
  )
{
  EFI_STATUS                    Status;
  TXT_INFO_HOB                  *HobList;
  TXT_INFO_DATA                 *TxtInfoData;
  EFI_HANDLE                    *HandleBuffer;
  UINTN                         NumberOfHandles;
  EFI_FIRMWARE_VOLUME2_PROTOCOL *FwVol;
  UINTN                         Size;
  EFI_FV_FILETYPE               FileType;
  UINT32                        FvStatus;
  EFI_FV_FILE_ATTRIBUTES        Attributes;
  UINT64                        TxtHeapMemoryBase;
  UINT64                        TxtSinitMemoryBase;
  UINT64                        *Ptr64;
  EFI_PHYSICAL_ADDRESS          TopAddr;
  BIOS_OS_DATA_REGION           *BiosOsDataRegion;

  HandleBuffer = NULL;
  NumberOfHandles = 0;
  FwVol = NULL;
  FileType = 0;
  Attributes = 0;
  BiosOsDataRegion = NULL;

  ///
  /// Find TXT HOB
  ///
  HobList = (TXT_INFO_HOB *) GetFirstGuidHob (&gTxtInfoHobGuid);
  if (HobList == NULL) {
    return EFI_NOT_FOUND;
  }

  TxtInfoData = &HobList->Data;
  ///
  /// Check TXT mode
  ///
  if (TxtInfoData->TxtMode == 0) {
    return EFI_UNSUPPORTED;
  }

  if ((TxtInfoData == 0) ||
      (TxtInfoData->TxtDprMemoryBase == 0) ||
      (TxtInfoData->TxtDprMemorySize == 0) ||
      (TxtInfoData->TxtHeapMemorySize == 0) ||
      (TxtInfoData->SinitMemorySize == 0)
      ) {
    return EFI_UNSUPPORTED;
  } else {
    ///
    /// Use address passed from PEI
    ///
    TopAddr             = TxtInfoData->TxtDprMemoryBase + TxtInfoData->TxtDprMemorySize;

    TxtHeapMemoryBase   = (UINT64) (TopAddr - TxtInfoData->TxtHeapMemorySize);

    TxtSinitMemoryBase  = TxtHeapMemoryBase - TxtInfoData->SinitMemorySize;
  }
  ///
  /// Start looking for SINIT ACM in FVs
  ///
  DEBUG ((DEBUG_INFO, "TXTDXE: Looking for SINIT ACM in FVs\n"));

  Status = gBS->LocateHandleBuffer (
    ByProtocol,
    &gEfiFirmwareVolume2ProtocolGuid,
    NULL,
    &NumberOfHandles,
    &HandleBuffer
    );
  ASSERT_EFI_ERROR (Status);
  ///
  /// Looking for FV with SinitAC binary
  ///
  for (UINTN i = 0; i < NumberOfHandles; i++) {
    ///
    /// Get the protocol on this handle
    ///
    Status = gBS->HandleProtocol (
      HandleBuffer[i],
      &gEfiFirmwareVolume2ProtocolGuid,
      &FwVol
      );
    ASSERT_EFI_ERROR (Status);
    ///
    /// See if it has the SinitACM file
    ///
    Size = 0;
    FvStatus = 0;
    Status = FwVol->ReadFile (
      FwVol,
      &gSinitModuleGuid,
      NULL,
      &Size,
      &FileType,
      &Attributes,
      &FvStatus
      );
    ///
    /// If the binary was located, then break
    ///
    if (Status == EFI_SUCCESS) {
      DEBUG((DEBUG_INFO, "TXTDXE: Found SINIT ACM In FV\n"));
      break;
    }
  }
  FreePool (HandleBuffer);
  ///
  /// Sanity check
  ///
  if ( !(FwVol == NULL || Status != EFI_SUCCESS || Size >= TxtInfoData->SinitMemorySize ) ) {
    ///
    /// Read Sinit ACM from the storage file.
    ///
    Ptr64 = (UINT64 *)TxtSinitMemoryBase;
    Status = FwVol->ReadFile (
      FwVol,
      &gSinitModuleGuid,
      &Ptr64,
      &Size,
      &FileType,
      &Attributes,
      &FvStatus
    );
    ASSERT_EFI_ERROR (Status);
    TxtInfoData->SinitAcmSize = (UINT64) Size;

    Ptr64 = (UINT64 *) TxtHeapMemoryBase;
    ///
    /// BiosOsDataSize plus size of data size field itself
    ///
    BiosOsDataRegion                = (BIOS_OS_DATA_REGION *) (Ptr64 + 1);
    BiosOsDataRegion->BiosSinitSize = (UINT32) TxtInfoData->SinitAcmSize;
  DEBUG ((DEBUG_INFO, "TXTDXE: Copy SINIT ACM Done\n"));
  }
  return Status;
}
#endif
