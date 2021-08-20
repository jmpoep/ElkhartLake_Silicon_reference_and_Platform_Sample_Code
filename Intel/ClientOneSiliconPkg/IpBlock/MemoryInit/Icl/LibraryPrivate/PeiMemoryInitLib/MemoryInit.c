/** @file
  Memory Initialization PEIM.

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

#include <PiPei.h>
#include <Library/DebugLib.h>
#include <Library/ReportStatusCodeLib.h>
#include <Library/HobLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/IoLib.h>
#include <Library/TimerLib.h>
#include <SmramMemoryReserve.h>
#include <Guid/MemoryTypeInformation.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Guid/AcpiS3Context.h>
#include <Library/PeiSaPolicyLib.h>
#include <Library/CpuCommonLib.h>
#include <Library/PchInfoLib.h>
#include <PsmiDataHob.h>
#include <PsmiConfig.h>
#include <Library/PeiGraphicsInitLib.h>

//
// Definition in EDK Foundation, used in this driver
//
#define BOOT_IN_RECOVERY_MODE_MASK                    0x40
#define BOOT_SPECIAL_MASK                             0x80

#include <Library/PciSegmentLib.h>
#include <Register/Cpuid.h>
#include <Register/Msr.h>
#include <CpuAccess.h>
#include <Library/CpuPlatformLib.h>
#include <SaPolicyCommon.h>
#include "MemoryInit.h"
#include "MrcGlobal.h"
#include "MrcGeneral.h"
#include "MrcDebugHook.h"
#include "MrcDebugPrint.h"
#include "MrcMalloc.h"
#include "MrcMemoryMap.h"
#include <Library/PcdLib.h>
#include <Library/PerformanceLib.h>
#include <Library/TxtLib.h>
#include <MemoryTest.h>
#include <IndustryStandard/SmBios.h>

//
// Driver Dependent PPI Prototypes
//
#include <Ppi/Capsule.h>
#include <TxtInfoHob.h>
#include <Ppi/Wdt.h>
#include <Ppi/MasterBootMode.h>

#ifdef FSP_FLAG
#include <FspEas.h>
#include <FspmUpd.h>
#include <HobUsageDataHob.h>
#include <Library/FspCommonLib.h>
#include <Library/FspSwitchStackLib.h>
#endif // FSP_FLAG
#include <Ppi/FspmArchConfigPpi.h>

//
// Driver PPI Definitions
//

#include <Library/PeiMeLib.h>

//
// Private Library Definitions
//
#include <Library/TxtPeiLib.h>
#include <Library/MeInitLib.h>


#ifdef FSP_FLAG
//
// Support 64 K IO space
// Moving RES_IO_BASE due to new ACPI Base address 0x1800
//
#define RES_IO_BASE   0x2000
#define RES_IO_LIMIT  0xFFFF
//
// Support 4G address space
//
#define RES_MEM_LIMIT_1 ((UINTN) PcdGet64 (PcdSiPciExpressBaseAddress) - 1)
#endif // FSP_FLAG

//
// Driver GUID Definitions
//
extern EFI_GUID  gEfiSmmPeiSmramMemoryReserveGuid;


#ifndef MDEPKG_NDEBUG
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 BootStringFc[]  = "WITH_FULL_CONFIGURATION";
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 BootStringMc[]  = "WITH_MINIMAL_CONFIGURATION";
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 BootStringNc[]  = "ASSUMING_NO_CONFIGURATION_CHANGES";
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 BootStringFcd[] = "WITH_FULL_CONFIGURATION_PLUS_DIAGNOSTICS";
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 BootStringDs[]  = "WITH_DEFAULT_SETTINGS";
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 BootStringS4[]  = "ON_S4_RESUME";
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 BootStringS5[]  = "ON_S5_RESUME";
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 BootStringS2[]  = "ON_S2_RESUME";
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 BootStringS3[]  = "ON_S3_RESUME";
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 BootStringFu[]  = "ON_FLASH_UPDATE";
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 BootStringRm[]  = "IN_RECOVERY_MODE";
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 BootStringRmm[] = "IN_RECOVERY_MODE_MASK";
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 BootStringSm[]  = "SPECIAL_MASK";
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 BootStringUnk[] = "MODE_UNKNOWN";
#endif

#ifdef FSP_FLAG
EFI_STATUS
BuildHobUsageDataHob (
  VOID
  );
#endif // FSP_FLAG

extern MrcDimmSts DimmPresence (IN MrcDebug *const Debug, IN const MrcSpd *const Spd);

GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 MrcDataStringConst[] = "MRCD";
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 MrcSpdStringConst[]  = "SPD ";

/**
  Entry point of MemoryInit library
  This function will invoke main memory detection code after the following dependencies
  have been satisfied at right timing.
  - gSiPreMemPolicyPpiGuid
  - gSiPolicyPpiGuid
  - gWdtPpiGuid
  - gSaPeiInitPpiGuid
  - gEfiPeiMasterBootModePpiGuid
  Note:\n
  If TXT is not implemented(_SA_MISC_PEI_PREMEM_CONFIG->TxtImplemented == 0), gEfiPeiMasterBootModePpiGuid will be the last dependency of the notify PPI registration to perform MemoryInit.\n
  If TXT is implemented(_SA_MISC_PEI_PREMEM_CONFIG->TxtImplemented == 1), gPeiTxtReadyToRunMemoryInitPpiGuid will be the PPI that invokes MemoryInit. (gEfiPeiMasterBootModePpiGuid should be installed earlier than gPeiTxtReadyToRunMemoryInitPpiGuid)\n

  @retval EFI_SUCCESS          - MRC callback has been registered successfully
  @retval EFI_OUT_OF_RESOURCES - Fail to allocate required buffer for MRC callback control.
**/
EFI_STATUS
EFIAPI
InstallMrcCallback (
  VOID
  )
{
  EFI_STATUS                    Status;
  MRC_INSTANCE                  *MrcInstance;
  SI_PREMEM_POLICY_PPI          *SiPreMemPolicyPpi;
  SA_MISC_PEI_PREMEM_CONFIG     *MiscPeiPreMemConfig;

  DEBUG ((DEBUG_INFO, "[InstallMrcCallback] MRC Entry...\n"));
  //
  // Obtain policy settings.
  //
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gSaMiscPeiPreMemConfigGuid, (VOID *) &MiscPeiPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  //
  // Initialize MRC Instance for callbacks
  //
  MrcInstance = AllocateZeroPool (sizeof (MRC_INSTANCE));
  ASSERT (MrcInstance != NULL);
  if (MrcInstance == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  MrcInstance->Signature                = MRC_INSTANCE_SIGNATURE;
  MrcInstance->NotifyDescriptor.Flags   = (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST);
  MrcInstance->NotifyDescriptor.Notify  = PrememoryInitCallBack;
  MrcInstance->FileHandle               = NULL;
  MrcInstance->MrcExecuted              = FALSE;
  if (MiscPeiPreMemConfig->TxtImplemented == 1) {
    MrcInstance->NotifyDescriptor.Guid    = &gPeiTxtReadyToRunMemoryInitPpiGuid;
    DEBUG ((DEBUG_INFO, "[InstallMrcCallback] Register gPeiTxtReadyToRunMemoryInitPpiGuid Notify Status = %r\n", Status));
  } else {
    MrcInstance->NotifyDescriptor.Guid    = &gEfiPeiMasterBootModePpiGuid;
    DEBUG ((DEBUG_INFO, "[InstallMrcCallback] Register PeiMasterBootModePpi Notify Status = %r\n", Status));
  }
  Status = PeiServicesNotifyPpi (&MrcInstance->NotifyDescriptor);
  ASSERT_EFI_ERROR (Status);
  return Status;
}

/**
  A notify callback function to determine if main memory detection function can be executed or not

  @param[in] PeiServices          General purpose services available to every PEIM.
  @param[in] NotifyDescriptor     The notification structure this PEIM registered on install.
  @param[in] Ppi                  The notify callback PPI.  Not used.

  @retval EFI_SUCCESS          - MRC has been executed successfully
  @retval EFI_NOT_READY        - One of the dependency not ready yet for MRC execution.
**/
EFI_STATUS
EFIAPI
PrememoryInitCallBack (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  )
{
  EFI_STATUS                    Status;
  MRC_INSTANCE                  *MrcInstance;

  DEBUG ((DEBUG_INFO, "[PrememoryInitCallBack]\n"));
  MrcInstance = MRC_INSTANCE_FROM_NOTIFY_THIS (NotifyDescriptor);

  //
  // If MRC has been executed, rest of callbacks should return directly.
  //
  if (MrcInstance->MrcExecuted == TRUE) {
    return EFI_SUCCESS;
  }

  Status = PeiServicesLocatePpi (
             &gEfiPeiMasterBootModePpiGuid,
             0,
             NULL,
             NULL
             );
  if (Status != EFI_SUCCESS) {
    DEBUG ((DEBUG_ERROR, "[PrememoryInitCallBack] PeiMasterBootModePpi is not installed yet.\n"));
    return EFI_NOT_READY;
  }

  //
  // Here we will execute MemoryInit and set MrcExecuted to TRUE
  //
  MrcInstance->MrcExecuted = TRUE;
  Status = PeimMemoryInit (MrcInstance->FileHandle, (CONST EFI_PEI_SERVICES **) PeiServices, MrcInstance);

#ifdef FSP_FLAG
  if (Status != EFI_SUCCESS) {
    DEBUG ((DEBUG_ERROR, "FspMemoryInitApi() - Error Initialization Failure - 0x%x\n", Status));
    //
    // Return after converting to API return status as per FSP EAS
    //
    if ((Status != EFI_INVALID_PARAMETER) && (Status != EFI_UNSUPPORTED) &&
        (Status != EFI_DEVICE_ERROR) && (Status != EFI_OUT_OF_RESOURCES)) {
      Status = EFI_DEVICE_ERROR;  // Remap to API return status as per FSP EAS
    }
    ASSERT_EFI_ERROR (Status);
  }
#endif

  return Status;
}

/**
  Main starting point for system memory initialization.
    - 1. Get SysBootMode and MrcBootMode
    - 2. Locate SiPreMemPolicyPpi
    - 3. Locate S3DataPtr from MiscPeiPreMemConfig.
    - 4. SaveDataValid := TRUE if S3DataPtr is not NULL.
    - 5. If SysBootMode is BOOT_ON_S3_RESUME and S3Data is not valid:
      -> ASSERT.
    - 6. If MrcBootMode is Warm boot, but S3 data is not valid :
        -> change MrcBootMode to Cold boot.
    - 7. If MrcBootMode is Cold boot:
        -> Run MRC code
        -> Save S3 Restore Data
      Else
        -> Run MRC_S3Resume
    - 8. Run MRC_Done().
    - 9. Install EFI memory HOBs.

  @param[in] FfsHeader (or FileHandle) - Pointer to Firmware File System file header
  @param[in] PeiServices               - General purpose services available to every PEIM.
  @param[in] MrcInstance               - MRC instance structure for callback implementation

  @retval EFI_SUCCESS      - Memory initialization completed successfully.
  @retval EFI_NOT_READY    - Cannot locate SA Policy.
  @retval EFI_NOT_FOUND    - No S3 data in S3 Boot Mode.
  @retval EFI_DEVICE_ERROR - MemoryInit failed or IOSAV Memory test failed.
**/
EFI_STATUS
PeimMemoryInit (
  IN EFI_PEI_FILE_HANDLE       FileHandle,
  IN CONST EFI_PEI_SERVICES    **PeiServices,
  MRC_INSTANCE                 *MrcInstance
  )
{
  SI_PREMEM_POLICY_PPI        *SiPreMemPolicyPpi;
  MEMORY_CONFIGURATION        *MemConfig;
  SA_MISC_PEI_PREMEM_CONFIG   *MiscPeiPreMemConfig;
  GRAPHICS_PEI_PREMEM_CONFIG  *GtConfig;
  MEMORY_CONFIG_NO_CRC        *MemConfigNoCrc;
  MEMORY_PLATFORM_DATA_HOB    *Hob;
  MrcParameters               *MrcData;
  MrcInput                    *Inputs;
  MrcOutput                   *Outputs;
  MrcSave                     *SaveSys;
  MrcSave                     *Save;
  MRC_FUNCTION                CallTable;
  MRC_FUNCTION                *MrcCall;
  MrcIntOutput                *MrcIntData;
  EFI_STATUS                  Status;
  EFI_BOOT_MODE               SysBootMode;
  MrcStatus                   MrcStatus;
  MRC_BOOT_MODE               MrcBootMode;
  BOOLEAN                     SaveDataValid;
  UINT32                      Crc32;
  MrcDebug                    *Debug;
#ifndef MDEPKG_NDEBUG
  const UINT8                 *Str;
#endif
  UINT8                       InitStat;
  UINT8                       ForceFullTraining;
  UINT8                       TotalDprSizeMB;
  UINT16                      HobTotalSize;
  UINT16                      HobBufferSize;
  MrcIntOutput                MrcIntGlobalData;
  MrcParameters               MrcGlobalData;
  BOOLEAN                     InterpeterTrainingDone;
  FSPM_ARCH_CONFIG_PPI        *FspmArchConfigPpi;
  VOID                        *S3DataPtr;

  UINT32 PciImrBaseLow;
  UINT32 PciImrBaseHigh;
  UINT32 ImrsSize;
  UINT32 Alignment;
  UINT64 MsrData;

  DEBUG ((DEBUG_INFO, "[PeimMemoryInit]\n"));

  ZeroMem (&MrcGlobalData, sizeof (MrcParameters));
  ZeroMem (&MrcIntGlobalData, sizeof (MrcIntOutput));
  MrcData                                  = &MrcGlobalData;
  Inputs                                   = &MrcData->Inputs;
  Inputs->Call.Func                        = &CallTable;
  MrcCall                                  = Inputs->Call.Func;
  Outputs                                  = &MrcData->Outputs;
  MrcIntData                               = &MrcIntGlobalData;
  MrcData->IntOutputs.Internal             = (void *) MrcIntData;
  MrcIntData->Size                         = sizeof (MrcIntOutput);
  MrcData->MrcDataSize                     = sizeof (MrcParameters);
  MrcData->Save.Size                       = sizeof (MrcSave);
//  Inputs->Size                             = sizeof (MrcInput);
  Outputs->Size                            = sizeof (MrcOutput);
  *((UINT32 *) &MrcData->MrcDataString[0]) = *((UINT32 *) MrcDataStringConst);
  MrcIntData->PeiServices                  = (UINT32) PeiServices;
  HobBufferSize                            = 0;
  InterpeterTrainingDone                   = FALSE;
  //
  // Obtain policy settings.
  //
  SiPreMemPolicyPpi = NULL;
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (SiPreMemPolicyPpi == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  MemConfig = NULL;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gMemoryConfigGuid, (VOID *) &MemConfig);
  ASSERT_EFI_ERROR (Status);
  if (MemConfig == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  MiscPeiPreMemConfig = NULL;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gSaMiscPeiPreMemConfigGuid, (VOID *) &MiscPeiPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  if (MiscPeiPreMemConfig == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  MemConfigNoCrc = NULL;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gMemoryConfigNoCrcGuid, (VOID *) &MemConfigNoCrc);
  ASSERT_EFI_ERROR (Status);
  if (MemConfigNoCrc == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  GtConfig = NULL;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gGraphicsPeiPreMemConfigGuid, (VOID *) &GtConfig);
  ASSERT_EFI_ERROR (Status);
  if (GtConfig == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  SiPreMemPolicyPpi = NULL;
  Status = PeiServicesLocatePpi (&gSiPreMemPolicyPpiGuid, 0, NULL, (VOID **) &SiPreMemPolicyPpi);
  ASSERT_EFI_ERROR (Status);
  if (SiPreMemPolicyPpi == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Inputs->PciEBaseAddress = (UINT32) PcdGet64 (PcdSiPciExpressBaseAddress);

  MrcSetupOem (MrcData, MemConfig, MemConfigNoCrc);

  //
  // Obtain boot mode.
  //
  Status = PeiServicesGetBootMode (&SysBootMode);
  ASSERT_EFI_ERROR (Status);

  //
  // Locate FSP-M Arch Config PPI for Memory Configuration Save Data,
  // if FspmArchConfigPpi not present, then use MiscPeiPreMemConfig
  //
  FspmArchConfigPpi = NULL;
  S3DataPtr         = NULL;
  Status = PeiServicesLocatePpi (
             &gFspmArchConfigPpiGuid,
             0,
             NULL,
             (VOID **) &FspmArchConfigPpi
             );
  if (!EFI_ERROR (Status)) {
    S3DataPtr = FspmArchConfigPpi->NvsBufferPtr;
  } else {
    S3DataPtr = MiscPeiPreMemConfig->S3DataPtr;
  }

  if (SysBootMode != BOOT_ON_S3_RESUME) {
    //
    // Calculate total HOB size needed for MRC
    //
    switch (MemConfig->HobBufferSize) {
      case 1:
        HobBufferSize = 1;
        break;

      case 2:
        HobBufferSize = 1 * 1024;
        break;

      case 3:
        HobBufferSize = (63 * 1024) - sizeof (EFI_HOB_GUID_TYPE) - sizeof (MEMORY_PLATFORM_DATA);
        break;

      case 0:
      default:
#ifdef MRC_DEBUG_PRINT
        HobBufferSize = 1 * 1024;
#else
        HobBufferSize = 1;
#endif
        break;
    }
    HobTotalSize = sizeof (EFI_HOB_GUID_TYPE) + sizeof (MEMORY_PLATFORM_DATA) + HobBufferSize;
    Status = MrcGetHobForDataStorage ((VOID **) &Hob, HobTotalSize, &gSiMemoryPlatformDataGuid);
    ASSERT_EFI_ERROR (Status);
    MrcHeapInitialize (MrcData, (void *) &Hob->Buffer, HobBufferSize);
    DEBUG ((DEBUG_INFO, "MRC heap. Base = %Xh, Size = %d\n", Inputs->HeapBase.DataN, Inputs->HeapSize));
#ifdef BDAT_SUPPORT
    Status = MrcGetHobForDataStorage ((VOID **) &Outputs->BdatMemoryHob[0], sizeof (BDAT_MEMORY_DATA_HOB), &gEfiMemorySchemaGuid);
    if (EFI_SUCCESS != Status) {
      Outputs->BdatMemoryHob[0].Pointer = NULL;
    }
    Status = MrcGetBdatSchemaListHob (&Outputs->BdatSchemasHob.Pointer);
    if (EFI_ERROR (Status)) {
      Outputs->BdatSchemasHob.Pointer = NULL;
    }
#endif
  } else {
    Hob = NULL;
#ifdef BDAT_SUPPORT
    Outputs->BdatMemoryHob[0].Pointer = NULL;
#endif
  }

  Debug = &Outputs->Debug;

  Inputs->DebugLevel  = (MemConfig->MrcTimeMeasure > 0) ? MSG_LEVEL_TIME : MemConfigNoCrc->SerialDebugLevel;
  Inputs->DebugStream = (UINT32) PeiServices;
  //
  // Top of stack at the beginning of MRC - for stack usage calculations.
  //
  Inputs->MrcStackTop.Ptr = &FileHandle;

  MrcCall->MrcDebugHook (MrcData, MRC_INITIALIZATION_START);
  InitStat = 0;
  ForceFullTraining = 0;
  MRC_DEBUG_MSG_OPEN (MrcData, Inputs->DebugLevel, Inputs->DebugStream, Inputs->SerialBuffer.DataN, Inputs->SerialBufferSize);
  MrcStatus = mrcSuccess;

  //
  // Unlock memory if it is necessary.
  //
  UnlockMemory (MrcData);

  //
  // Get MRC BootMode
  //
  Inputs->MchBarBaseAddress  = MiscPeiPreMemConfig->MchBar;
  MrcBootMode = (SysBootMode == BOOT_ON_S3_RESUME) ? bmS3 : MrcGetBootMode (MrcData);

DEBUG_CODE_BEGIN();
  if ((SysBootMode == BOOT_ON_S3_RESUME) && (bmCold == MrcGetBootMode (MrcData))) {
    DEBUG ((
      DEBUG_ERROR,
      "ERROR: SysBootMode = %Xh and MrcBootMode = %d - Check PCH MEM_SR bit\n",
      SysBootMode,
      MrcBootMode
      ));
  }
DEBUG_CODE_END();

  //
  // Get Cpu Information
  //
  if (MrcSetCpuInformation (MrcData, Inputs->CpuidModel, Inputs->CpuidStepping) != mrcSuccess) {
    DEBUG ((DEBUG_ERROR, "%a CPU Family/Model/Step %Xh is not supported\n", gErrString, Inputs->CpuidModel | Inputs->CpuidStepping));
    ASSERT_EFI_ERROR (EFI_DEVICE_ERROR);
  }

#ifndef MDEPKG_NDEBUG
  switch (SysBootMode) {
    case BOOT_WITH_FULL_CONFIGURATION:                  Str = BootStringFc;   break;
    case BOOT_WITH_MINIMAL_CONFIGURATION:               Str = BootStringMc;   break;
    case BOOT_ASSUMING_NO_CONFIGURATION_CHANGES:        Str = BootStringNc;   break;
    case BOOT_WITH_FULL_CONFIGURATION_PLUS_DIAGNOSTICS: Str = BootStringFcd;  break;
    case BOOT_WITH_DEFAULT_SETTINGS:                    Str = BootStringDs;   break;
    case BOOT_ON_S4_RESUME:                             Str = BootStringS4;   break;
    case BOOT_ON_S5_RESUME:                             Str = BootStringS5;   break;
    case BOOT_ON_S2_RESUME:                             Str = BootStringS2;   break;
    case BOOT_ON_S3_RESUME:                             Str = BootStringS3;   break;
    case BOOT_ON_FLASH_UPDATE:                          Str = BootStringFu;   break;
    case BOOT_IN_RECOVERY_MODE:                         Str = BootStringRm;   break;
    case BOOT_IN_RECOVERY_MODE_MASK:                    Str = BootStringRmm;  break;
    case BOOT_SPECIAL_MASK:                             Str = BootStringSm;   break;
    default:                                            Str = BootStringUnk;  break;
  }
  DEBUG ((DEBUG_INFO, "System boot mode: %Xh - BOOT_%a\n", SysBootMode, Str));
#endif

  //
  // Locate and determine if memory configuration save data is valid.
  //
  SaveDataValid = FALSE;
  DEBUG ((
           DEBUG_INFO,
           "Restore data of size %d from 0x%X\nGlobal data of size %d is at 0x%X\n",
           (S3DataPtr == NULL) ? 0 : ((MrcSave *) S3DataPtr)->Size,
           S3DataPtr,
           sizeof (MrcParameters),
           &MrcData
           ));

  if ((S3DataPtr != NULL) && (SysBootMode != BOOT_WITH_DEFAULT_SETTINGS)) {
    SaveSys = (MrcSave *) S3DataPtr;
    Save    = SaveSys;
    Crc32 = MrcCalculateCrc32 ((UINT8 *) (&Save->Data), sizeof (MrcSaveData));
    DEBUG ((DEBUG_INFO, "Calc. crc = 0x%x, Header crc = 0x%x\n", Crc32, Save->Header.Crc));
    if (Crc32 == Save->Header.Crc) {
      DEBUG ((DEBUG_INFO, "Saved memory configuration data is valid\n"));
      ((*PeiServices)->CopyMem) ((VOID *) &MrcData->Save, (VOID *) SaveSys, sizeof (MrcSave));
      SaveDataValid = TRUE;
    }
  }

  //
  // We must have memory configuration save data in order to resume from S3.
  //
  if ((SysBootMode == BOOT_ON_S3_RESUME) && (!SaveDataValid)) {
    DEBUG ((DEBUG_ERROR, "Unable to resume from S3 without valid saved memory configuration data\n"));
    ASSERT (FALSE);
    return EFI_NOT_FOUND;
  }

  if (!(MrcBootMode == bmS3 || MrcBootMode == bmWarm)) {
    //
    // Check CPU Replaced Status, if so a system non-power cycle reset will be required.
    //
    DEBUG ((DEBUG_INFO, "Calling CpuReplacementCheck\n"));
    Status = CpuReplacementCheck(FileHandle, &ForceFullTraining);

    if (ForceFullTraining == 0x1) {
      SaveDataValid = FALSE;
    }
  }

  //
  // MrcBootMode can ONLY be bmCold, bmWarm or bmS3 at this point.
  //
  switch (MrcBootMode) {
    case bmCold:
      // Advance the MRC boot mode to fast boot if the following condition is met.
      // If sticky scratchpad is set, there was a failure during previous Fast flow, so use Cold.
      if ((SaveDataValid == TRUE) &&
          (MemConfig->MrcFastBoot > 0) &&
          (MrcWmRegGet (MrcData) == 0) &&
          (ColdBootRequired (MrcData, MemConfig, MrcBootMode) == FALSE)
          ) {
        MrcBootMode = bmFast;
        DEBUG ((DEBUG_INFO, "Fast boot is possible, so forcing it\n"));
      } else {
        DEBUG ((DEBUG_INFO, "Cold boot\n"));
        SaveDataValid = FALSE;
      }
      break;

    case bmWarm:
    case bmS3:
      if ((MemConfig->MrcTrainOnWarm) && (MrcBootMode == bmWarm)) {
          DEBUG ((
            DEBUG_INFO,
            "Force cold Boot Requested on Warm reset\n"
            ));
          MrcBootMode = bmCold;
          break;
        } else {
          if (SaveDataValid == FALSE) {
            DEBUG ((DEBUG_WARN, "Saved memory configuration data is not valid, forcing a cold boot\n"));
            MrcBootMode = bmCold;
            break;
          } else {
            if ((ColdBootRequired (MrcData, MemConfig, MrcBootMode) == TRUE) ||
                (((MrcWmRegGet(MrcData) & SSKPD_PCU_SKPD_MEM_TEST_DONE) == 0) && (MrcBootMode == bmWarm)))  {
              DEBUG ((
                DEBUG_WARN,
                "Platform settings or configuration have changed, forcing a cold boot\n"
                ));
              MrcBootMode = bmCold;
              SaveDataValid = FALSE;
              break;
            }
            if ((MemConfigNoCrc->CleanMemory == TRUE) && (MrcBootMode == bmWarm)) {
              DEBUG ((
                DEBUG_WARN,
                "TCG MOR request, forcing fast boot flow to scrub memory\n"
                ));
              MrcBootMode = bmFast;
              break;
            }
            //
            // Do not force cold boot when BOOT_ON_FLASH_UPDATE since the memory content should be retained.
            //
            if (SysBootMode != BOOT_ON_FLASH_UPDATE) {
              /*
                Check SSKPD register to determine if Warm Reset occurred before MRC was reached during a cold boot.
                If so, we need to choose Fast or Cold boot path.
              */
              if ((MrcBootMode == bmWarm) && (MrcWmRegGet (MrcData) == 0)) {
                DEBUG ((
                  DEBUG_WARN,
                  "Reset occurred in the cold boot path before reaching MRC.\n"
                  ));
                if (MemConfig->MrcFastBoot > 0) {
                  DEBUG ((DEBUG_INFO, "Fast boot is possible, so forcing it\n"));
                  MrcBootMode = bmFast;
                } else {
                  DEBUG ((DEBUG_INFO, "Cold boot\n"));
                  MrcBootMode = bmCold;
                  SaveDataValid = FALSE;
                }
                break;
              }
            }
          }
          DEBUG ((DEBUG_INFO, (MrcBootMode == bmS3) ? "Resume from S3\n" : "Warm reset\n"));
        }
      break;

    default:
      DEBUG ((DEBUG_INFO, "Cold boot\n"));
      MrcBootMode = bmCold;
      SaveDataValid = FALSE;
      break;
  }

  //
  // Clear MrcSave if not valid saved data. We don't want to end up with Ghost DIMMs
  //
  if (SaveDataValid == FALSE) {
    ZeroMem (&MrcData->Save, sizeof (MrcSave));
  }

  //
  // Calculate Total DPR Size
  //
  CalculateTotalDprMemorySize (&TotalDprSizeMB);
  if (TotalDprSizeMB != 0) {
    Inputs->DprSize = (UINT32) TotalDprSizeMB;
  }

  //
  // Set up the MRC input data structure.
  //
  PERF_START_EX (FileHandle, NULL, NULL, AsmReadTsc (), 0x3060);
  Inputs->BootMode = MrcSetupMrcData (
                       SysBootMode,
                       MrcBootMode,
                       MrcData,
                       MiscPeiPreMemConfig,
                       GtConfig,
                       MemConfig,
                       MemConfigNoCrc,
                       SiPreMemPolicyPpi,
                       Inputs->CpuidModel
                       );
  PERF_END_EX (FileHandle, NULL, NULL, AsmReadTsc (), 0x3061);

  //
  // Initialize MeStolenSize to 0 before we retrieving from ME FW.
  //
  Inputs->MeStolenSize = 0;

  if (MrcBootMode != bmS3) {
    ImrsSize       = 0;
    Alignment      = 0;

    MeImrConfig (&ImrsSize, &Alignment);

    DEBUG ((DEBUG_INFO, "Requested CSE IMR size = %d Bytes\nLargest CSE IMR size = %d Bytes\n", ImrsSize, Alignment));

    //
    // If ImrsSize is not a power of two, adjust ImrsSize by rounding it to the next power of 2
    //
    if ((ImrsSize > 0) && (IsThisPowerOfTwo(ImrsSize) == FALSE)) {
      ImrsSize = RoundToNextPow2(ImrsSize);
    }

    Inputs->MeStolenSize = ImrsSize >> 20;       // Value in MB
    Inputs->ImrAlignment = Alignment >> 20;      // Value in MB

    DEBUG ((
            DEBUG_INFO,
            "Requested CSE IMR size (rounded up) = %d MB\nLargest CSE IMR size = %d MB\n",
            Inputs->MeStolenSize,
            Inputs->ImrAlignment
            ));
  }

  do {
    if (Inputs->BootMode == bmCold) {
      //
      // Clear DRAM Init Bit if we are doing a cold boot, to prevent hang if a warm reset occurs in the training flow
      // where an old memory config is saved.
      //
      MrcResetDISB (MrcData);
    }
    MrcStatus = mrcSuccess;
    if ((mrcSuccess == MrcStatus) && (!InterpeterTrainingDone)) {
      DEBUG ((DEBUG_INFO, "MRC Start Memory Configuration\n"));
      PERF_START_EX (FileHandle, NULL, NULL, AsmReadTsc (), 0x3080);
      MrcStatus = MrcStartMemoryConfiguration (MrcData, 0, NULL, TRUE);
      PERF_END_EX (FileHandle, NULL, NULL, AsmReadTsc (), 0x3081);
    }
    switch (MrcStatus) {
      case mrcSuccess:
        break;

      case mrcColdBootRequired:
        if (Inputs->BootMode == bmFast) {
          // If XMP Profile is selected, switch to Default Memory Profile.
          if (Inputs->MemoryProfile != STD_PROFILE) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Switching from XMP profile to Default\n");
            MemConfig->SpdProfileSelected = Default;
            MemConfig->tCL                = 0;
            MemConfig->tRCDtRP            = 0;
            MemConfig->tRAS               = 0;
            MemConfig->tWR                = 0;
            MemConfig->tRFC               = 0;
            MemConfig->tRRD               = 0;
            MemConfig->tWTR               = 0;
            MemConfig->tRTP               = 0;
            MemConfig->tFAW               = 0;
            MemConfig->tCWL               = 0;
            MemConfig->tREFI              = 0;
            MemConfig->NModeSupport       = 0;
            MemConfig->Ratio              = 0;
            MemConfig->RefClk             = 0;
            MemConfig->VddVoltage         = VDD_INVALID;
          }
          // At this point, input structure has limited data.
          // We need to initialize the input structure for the cold boot.
          MrcBootMode = bmCold;
          Inputs->BootMode = MrcSetupMrcData (
                               SysBootMode,
                               MrcBootMode,
                               MrcData,
                               MiscPeiPreMemConfig,
                               GtConfig,
                               MemConfig,
                               MemConfigNoCrc,
                               SiPreMemPolicyPpi,
                               Inputs->CpuidModel
                               );
        } else {
          Inputs->BootMode = bmCold;
        }
        break;

      case mrcDimmNotExist:
        //
        // Set memory init status = 0x1 and send DRAM Init Done to ME FW,
        // indicating that no memory exists in the system.
        //
        InitStat = 0x1;
        Status = MeConfigDidReg (
                   FileHandle,
                   InitStat,
                   (Outputs->MemoryMapData.MeStolenBase & 0xFFF) << 20, // Low DWORD
                   Outputs->MemoryMapData.MeStolenBase >> 12, // High DWORD
                   &PciImrBaseLow,
                   &PciImrBaseHigh
                   );
        DEBUG ((DEBUG_INFO, "CSE IMR Base Low  = 0x%08X\n", (Outputs->MemoryMapData.MeStolenBase & 0xFFF) << 20));
        DEBUG ((DEBUG_INFO, "CSE IMR Base High = 0x%08X\n", Outputs->MemoryMapData.MeStolenBase >> 12));

        MrcCall->MrcDebugHook (MrcData, MRC_NO_MEMORY_DETECTED);
        DEBUG ((DEBUG_ERROR, "There are no DIMMs present in the system\n"));
        //
        //Indicate to the caller that memory has not been detected.
        //
        (*PeiServices)->ReportStatusCode (
          PeiServices,
          EFI_ERROR_CODE,
          EFI_COMPUTING_UNIT_MEMORY | EFI_CU_MEMORY_EC_NONE_DETECTED,
          0,    // Instance
          NULL, // *CallerId OPTIONAL
          NULL  // *Data OPTIONAL
          );
        // no break;

      default:
        DEBUG ((DEBUG_ERROR, "Memory initialization has failed\n"));
        REPORT_STATUS_CODE (EFI_ERROR_CODE, EFI_COMPUTING_UNIT_MEMORY | EFI_CU_EC_NON_SPECIFIC);
        //
        // Get lower byte and set the error bit
        //
        // MrcCall->MrcIoWrite16 (0x80, Debug->PostCode[MRC_POST_CODE] | MRC_FAILURE_INDICATION);
        ASSERT_EFI_ERROR (EFI_DEVICE_ERROR);
        return EFI_DEVICE_ERROR;
    } // switch MrcStatus
  } while (MrcStatus == mrcColdBootRequired);

  // Set the MSR bit VIRTUAL_MSR_CR_POWER_CTL.SAPM_iMC_C2_POLICY(bit2) to 0 if.serialize_zq is 1.
  if (Inputs->SharedZqPin == 1) {
    MsrData = MrcCall->MrcReadMsr64 (MSR_POWER_CTL);
    MsrData &= ~(UINT64)MRC_BIT2;
    MrcCall->MrcWriteMsr64 (MSR_POWER_CTL, MsrData);
  }

  DEBUG ((
    DEBUG_INFO,
    "Lowest StackAddr: 0x%x\tTop StackAddr: 0x%x\tDepth: %d\n",
    Debug->LowestStackAddr.DataN,
    Debug->TopStackAddr.DataN,
    Debug->TopStackAddr.DataN - Debug->LowestStackAddr.DataN
    ));
  //
  // Intel Silicon View Technology (ISVT) IO Reading port with AH = 0x10 for End of MRC
  //
  MrcCall->MrcReturnFromSmc(MrcData, MrcStatus);

  PERF_START_EX (FileHandle, NULL, NULL, AsmReadTsc (), 0x3090);
  if ((MrcBootMode == bmCold) || (MrcBootMode == bmFast)) {
    //
    // Perform simple memory test.
    //
    if (mrcFail == BasicMemoryTest (MrcData)) {
      if (MrcBootMode == bmFast) {
        if (Inputs->RetrainOnFastFail) {
          //
          // BasicMemoryTest failed in Fast flow - fall back to Cold boot flow.
          //
          DEBUG ((DEBUG_ERROR, "BasicMemoryTest failed in Fast flow - reset to run MRC in Cold flow !!\n\n\n"));
          MrcWmRegClrBits(MrcData, SSKPD_PCU_SKPD_MEM_TEST_DONE);
          REPORT_STATUS_CODE (EFI_ERROR_CODE, EFI_COMPUTING_UNIT_MEMORY | EFI_CU_EC_NON_SPECIFIC);
          IoWrite16 (0x80, 0);  // Clear 16-bit port80
          (*PeiServices)->ResetSystem2 (EfiResetWarm, EFI_SUCCESS, 0, NULL);
        }
      }
      MrcCall->MrcDebugHook (MrcData, MRC_MEM_INIT_DONE_WITH_ERRORS);
      ASSERT_EFI_ERROR (EFI_DEVICE_ERROR);
      PERF_END_EX (FileHandle, NULL, NULL, AsmReadTsc (), 0x3091);
      return EFI_DEVICE_ERROR;
    }
    MrcWmRegSetBits(MrcData, SSKPD_PCU_SKPD_MEM_TEST_DONE);
  } else {
    //
    // Perform simple non-destructive memory test for Warm / S3 resume.
    // On S3 Resume run this test only for Debug builds, to avoid S3 exit latency increase for Release builds.
    //
#ifdef MDEPKG_NDEBUG
    if (MrcBootMode != bmS3) {
#endif // MDEPKG_NDEBUG
      if (mrcFail == BasicMemoryTestS3 (MrcData)) {
        MrcCall->MrcDebugHook (MrcData, MRC_MEM_INIT_DONE_WITH_ERRORS);
        ASSERT_EFI_ERROR (EFI_DEVICE_ERROR);
        PERF_END_EX (FileHandle, NULL, NULL, AsmReadTsc (), 0x3091);
        return EFI_DEVICE_ERROR;
      }
#ifdef MDEPKG_NDEBUG
    }
#endif // MDEPKG_NDEBUG
  MrcWmRegSetBits(MrcData, SSKPD_PCU_SKPD_MEM_TEST_DONE);
  }
  PERF_END_EX (FileHandle, NULL, NULL, AsmReadTsc (), 0x3091);

  //
  // Configure "ME DRAM Init Done Register"
  // ME UMA Size outside of a 0MB-128MB range is not defined or if BDF 0:22:0 is not present, exit.
  //
  // MRC:RestricteContent - ME No longer preserves memory contents in IMR's over Warm Reset.  We will always send success.
  DEBUG ((DEBUG_INFO, "ME UMA Size requested: %d MB\n", Inputs->MeStolenSize));
  if ((Inputs->MeStolenSize > 0x80) || (PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, 0, 22, 0, 0x10)) == 0xffffffff)) {
    DEBUG ((DEBUG_ERROR, "Invalid ME UMA Size requested.\n"));
    //
    // Per CSME requirements; since an invalid size was requested, set memory init status = 0x1 and send DRAM Init Done to ME FW,
    // indicating that no memory exists in the system (InitStat = 0x1), MeStolenBase = 0x0.
    //
    InitStat = 0x1;
    Outputs->MemoryMapData.MeStolenBase = 0x0;
  }
  DEBUG ((DEBUG_INFO, "Calling MeConfigDidReg\n"));
  Status = MeConfigDidReg (
             FileHandle,
             InitStat,
             (Outputs->MemoryMapData.MeStolenBase & 0xFFF) << 20, // Low DWORD
             Outputs->MemoryMapData.MeStolenBase >> 12, // High DWORD
             &PciImrBaseLow,
             &PciImrBaseHigh
             );
  DEBUG ((DEBUG_INFO, "CSE IMR Base Low  = 0x%08X\n", (Outputs->MemoryMapData.MeStolenBase & 0xFFF) << 20));
  DEBUG ((DEBUG_INFO, "CSE IMR Base High = 0x%08X\n", Outputs->MemoryMapData.MeStolenBase >> 12));
  DEBUG ((DEBUG_INFO, "MeDramInitDone Complete.\n"));

  //
  // If memory is not preserved across reset then proceed through normal boot instead of Boot on flash update
  //
  if (((MrcBootMode == bmCold) || (MrcBootMode == bmFast)) && (SysBootMode == BOOT_ON_FLASH_UPDATE)) {
    if (PcdGetBool (PcdNvVariableEmulationMode)) {
      //
      // Emulated variables must load defaults each boot
      //
      SysBootMode = BOOT_WITH_DEFAULT_SETTINGS;
    } else {
      SysBootMode = BOOT_WITH_FULL_CONFIGURATION;
    }
    Status = PeiServicesSetBootMode(SysBootMode);
  }

  //
  // Install EFI memory HOBs
  //
  if (SysBootMode != BOOT_ON_S3_RESUME) {
#ifdef MRC_DEBUG_PRINT
    Debug->Current.DataN = 0;
#endif // MRC_DEBUG_PRINT
    BuildMemoryS3DataHob (MrcData);
    BuildMemoryInfoDataHob (MrcData);
    BuildMemoryPlatformDataHob (MrcData, Hob);
    ZeroMem ((VOID *) &Hob->Buffer, HobBufferSize);
  }

  Status = InstallEfiMemory(MrcData, PeiServices, SysBootMode, MiscPeiPreMemConfig
    );
  ASSERT_EFI_ERROR(Status);

  DEBUG ((DEBUG_INFO, "MemoryInit Complete.\n"));
  MrcCall->MrcDebugHook (MrcData, MRC_MEM_INIT_DONE);

  return Status;
}

/**
  Retrieves the data structure associated with the GUIDed HOB of type gEfiSmmPeiSmramMemoryReserveGuid

  @retval NULL   A HOB of type gEfiSmmPeiSmramMemoryReserveGuid could not be found.
  @retval !NULL  A pointer to the GUID data from a HIB of type gEfiSmmPeiSmramMemoryReserveGuid

**/
EFI_SMRAM_HOB_DESCRIPTOR_BLOCK *
GetSrmamHobData (
  VOID
  )
{
  VOID  *GuidHob;

  //
  // Search SmramMemoryReserve HOB that describes SMRAM region
  //
  GuidHob = GetFirstGuidHob (&gEfiSmmPeiSmramMemoryReserveGuid);
  if (GuidHob == NULL) {
    return NULL;
  }
  return (EFI_SMRAM_HOB_DESCRIPTOR_BLOCK *)GET_GUID_HOB_DATA (GuidHob);
}

/**
  This routine will split SmramReserve hob to reserve 1 page for SMRAM content in S3 phase
  for R9 SMM core.

  @retval EFI_SUCCESS           The gEfiSmmPeiSmramMemoryReserveGuid is split successfully.
  @retval EFI_NOT_FOUND         The gEfiSmmPeiSmramMemoryReserveGuid is not found.

**/
EFI_STATUS
EFIAPI
SplitSmramReserveHob (
  VOID
  )
{
  EFI_HOB_GUID_TYPE                *GuidHob;
  EFI_PEI_HOB_POINTERS             Hob;
  EFI_SMRAM_HOB_DESCRIPTOR_BLOCK   *DescriptorBlock;
  EFI_SMRAM_HOB_DESCRIPTOR_BLOCK   *NewDescriptorBlock;
  UINTN                            BufferSize;
  UINTN                            SmramRanges;
  UINTN                            Index;
  UINTN                            SubIndex;

  //
  // Retrieve the GUID HOB data that contains the set of SMRAM descriptors
  //
  GuidHob = GetFirstGuidHob (&gEfiSmmPeiSmramMemoryReserveGuid);
  if (GuidHob == NULL) {
    return EFI_NOT_FOUND;
  }

  DescriptorBlock = (EFI_SMRAM_HOB_DESCRIPTOR_BLOCK *)GET_GUID_HOB_DATA (GuidHob);

  //
  // Allocate one extra EFI_SMRAM_DESCRIPTOR to describe a page of SMRAM memory that contains a pointer
  // to the SMM Services Table that is required on the S3 resume path
  //
  SmramRanges = DescriptorBlock->NumberOfSmmReservedRegions;
  BufferSize = sizeof (EFI_SMRAM_HOB_DESCRIPTOR_BLOCK) + (SmramRanges * sizeof (EFI_SMRAM_DESCRIPTOR));

  Hob.Raw = BuildGuidHob (
              &gEfiSmmPeiSmramMemoryReserveGuid,
              BufferSize
              );
  ASSERT (Hob.Raw);
  NewDescriptorBlock = (EFI_SMRAM_HOB_DESCRIPTOR_BLOCK *)Hob.Raw;

  //
  // Copy old EFI_SMRAM_HOB_DESCRIPTOR_BLOCK to new allocated region
  //
  CopyMem ((VOID *)Hob.Raw, DescriptorBlock, BufferSize - sizeof(EFI_SMRAM_DESCRIPTOR));

  //
  // Increase the number of SMRAM descriptors by 1 to make room for the ALLOCATED descriptor of size EFI_PAGE_SIZE
  //
  NewDescriptorBlock->NumberOfSmmReservedRegions = (UINT32)(SmramRanges + 1);

  ASSERT (SmramRanges >= 1);
  //
  // Copy last entry to the end - we assume TSEG is last entry, which is same assumption as R8 CPU/SMM driver
  //
  CopyMem (&NewDescriptorBlock->Descriptor[SmramRanges], &NewDescriptorBlock->Descriptor[SmramRanges - 1], sizeof(EFI_SMRAM_DESCRIPTOR));

  //
  // Update the last but 1 entry in the array with a size of EFI_PAGE_SIZE and put into the ALLOCATED state
  //
  NewDescriptorBlock->Descriptor[SmramRanges - 1].PhysicalSize    = EFI_PAGE_SIZE;
  NewDescriptorBlock->Descriptor[SmramRanges - 1].RegionState    |= EFI_ALLOCATED;

  //
  // Reduce the size of the last SMRAM descriptor by EFI_PAGE_SIZE
  //
  NewDescriptorBlock->Descriptor[SmramRanges].PhysicalStart += EFI_PAGE_SIZE;
  NewDescriptorBlock->Descriptor[SmramRanges].CpuStart      += EFI_PAGE_SIZE;
  NewDescriptorBlock->Descriptor[SmramRanges].PhysicalSize  -= EFI_PAGE_SIZE;

  //
  // Now, we have created SmramReserve Hob for SmmAccess drive. But the issue is that, R8 SmmAccess will assume there is 2 SmramReserve region only.
  // Reporting 3 SmramReserve region will cause buffer overflow. Moreover, we would like to filter AB-SEG or H-SEG to avoid SMM cache-poisoning issue.
  // So we uses scan SmmReserve Hob to remove AB-SEG or H-SEG.
  //
  for (Index = 0; Index <= SmramRanges; Index++) {
    if (NewDescriptorBlock->Descriptor[Index].PhysicalSize == 0) {
      //
      // Skip zero entry
      //
      continue;
    }
    if (NewDescriptorBlock->Descriptor[Index].PhysicalStart < BASE_1MB) {
      //
      // Find AB-SEG or H-SEG
      // remove this region
      //
      for (SubIndex = Index; SubIndex < NewDescriptorBlock->NumberOfSmmReservedRegions - 1; SubIndex++) {
        CopyMem (&NewDescriptorBlock->Descriptor[SubIndex], &NewDescriptorBlock->Descriptor[SubIndex + 1], sizeof (EFI_SMRAM_DESCRIPTOR));
      }
      //
      // Zero last one
      //
      ZeroMem (&NewDescriptorBlock->Descriptor[SubIndex], sizeof(EFI_SMRAM_DESCRIPTOR));
      //
      // Decrease Number
      //
      NewDescriptorBlock->NumberOfSmmReservedRegions --;
      //
      // Decrease Index to let it test mew entry
      //
      Index --;
    }
  }

  //
  // Last step, we can scrub old one
  //
  ZeroMem (&GuidHob->Name, sizeof(GuidHob->Name));

  return EFI_SUCCESS;
}

/**
  This routine will create AcpiVariable hob to point the reserved smram in S3 phase
  for R9 SMM core.

  @retval EFI_SUCCESS           The variable hob with gEfiAcpiVariableGuid is created successfully.
  @retval EFI_NOT_FOUND         The gEfiSmmPeiSmramMemoryReserveGuid is not found.

**/
EFI_STATUS
CreateAcpiVariableHob (
  VOID
  )
{
  EFI_PEI_HOB_POINTERS             Hob;
  EFI_SMRAM_HOB_DESCRIPTOR_BLOCK   *DescriptorBlock;
  UINTN                            SmramRanges;

  //
  // Retrieve the GUID HOB data that contains the set of SMRAM descriptors
  //
  DescriptorBlock = GetSrmamHobData ();
  if (DescriptorBlock == NULL) {
    return EFI_NOT_FOUND;
  }

  Hob.Raw = BuildGuidHob (
              &gEfiAcpiVariableGuid,
              sizeof (EFI_SMRAM_DESCRIPTOR)
              );
  ASSERT (Hob.Raw);

  //
  // It should be already patch, so just copy last but 1 region directly.
  //
  SmramRanges = DescriptorBlock->NumberOfSmmReservedRegions;
  ASSERT (SmramRanges >= 2);
  if (SmramRanges >= 2) {
    CopyMem ((VOID *)Hob.Raw, &DescriptorBlock->Descriptor[SmramRanges - 2], sizeof (EFI_SMRAM_DESCRIPTOR));
  }

  return EFI_SUCCESS;
}

/**
  Driver Entry for AcpiVariableHobOnSmramReservHob PEIM

  @param   FileHandle       Handle of the file being invoked.
  @param   PeiServices      Describes the list of possible PEI Services.

  @retval EFI_SUCCESS      Success create variable hob with gEfiAcpiVariableGuid and
                           split gEfiSmmPeiSmramMemoryReserveGuid.
  @retval EFI_NOT_FOUND    Can not get gEfiSmmPeiSmramMemoryReserveGuid hob

**/
EFI_STATUS
CreateS3AcpiVariableHob (
  VOID
  )
{
  EFI_STATUS              Status;

  //
  // Split SmramReserve hob, which is required for R9 SMM Core for S3.
  //
  Status = SplitSmramReserveHob ();
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Create AcpiVariable hob, which is required for R9 SMM Core for S3.
  //
  Status = CreateAcpiVariableHob ();

  return Status;
}

/**
  This function installs memory for all paths except S3 resume.

  @param[in] MrcData     - Mrc data structure
  @param[in] PeiServices - PEI Services table.
  @param[in] SysBootMode - The specific boot path that is being followed.

  @retval EFI_SUCCESS          The function completed successfully.
  @retval EFI_OUT_OF_RESOURCES Out of Resources.
**/
EFI_STATUS
InstallEfiMemory (
  IN MrcParameters *CONST      MrcData,
  IN CONST EFI_PEI_SERVICES    **PeiServices,
  IN EFI_BOOT_MODE             SysBootMode,
  IN SA_MISC_PEI_PREMEM_CONFIG *MiscPeiPreMemConfig
  )
{
  IN CONST MrcInput                     *Inputs;
  MrcOutput                             *Outputs;
  MrcMemoryMap                          *MemoryMap2;
  EFI_STATUS                            Status;
  UINT8                                 Index;
  UINT8                                 NumRanges;
  UINT8                                 SmramIndex;
  UINT8                                 SmramRanges;
  UINT64                                PeiMemoryLength;
  UINT64                                InstalledPeiMemoryLength;
  UINT64                                RangeLength;
  UINTN                                 BufferSize;
  UINTN                                 PeiMemoryIndex;
  UINT64                                McD0BaseAddress;
  BOOLEAN                               PsmiMemoryRequired;
  UINT64                                PsmiMemSize;
  UINT32                                Alignment;
  EFI_PHYSICAL_ADDRESS                  PsmiMemBaseAddr;
  EFI_PEI_HOB_POINTERS                  Hob;
  EFI_PHYSICAL_ADDRESS                  PeiMemoryBaseAddress;
  EFI_PHYSICAL_ADDRESS                  InstalledPeiMemoryBaseAddress;
  UINT32                                RequiredMemSize;
  EFI_PHYSICAL_ADDRESS                  TopUseableMemAddr;
  UINT64_STRUCT                         TopUseableMemSize;
  UINT64_STRUCT                         Tom;
  MEMORY_TEST_LEVEL                     MemoryTestLevel;
  EFI_SMRAM_HOB_DESCRIPTOR_BLOCK        *SmramHobDescriptorBlock;
  EFI_SMRAM_DESCRIPTOR                  *SmramDescriptor;
  PEI_DUAL_CHANNEL_DDR_MEMORY_MAP_RANGE MemoryMap[MAX_RANGES];
  EFI_PHYSICAL_ADDRESS                  BadMemoryAddress;
  EFI_RESOURCE_TYPE                     ResourceType;
  EFI_RESOURCE_ATTRIBUTE_TYPE           ResourceAttribute;
  SI_PREMEM_POLICY_PPI                  *SiPreMemPolicyPpi;
  MEMORY_CONFIG_NO_CRC                  *MemConfigNoCrc;
  EFI_RESOURCE_ATTRIBUTE_TYPE           ResourceAttributeTested;
  UINT64                                TopMemSize;
  PEI_CAPSULE_PPI                       *Capsule;
  VOID                                  *CapsuleBuffer;
  UINTN                                 CapsuleBufferLength;
  BOOLEAN                               CoalesceCapsule;
#ifndef FSP_FLAG
#else
  FSPM_ARCH_CONFIG_PPI                  *FspmArchConfigPpi;
  UINT32                                BootLoaderTolumSize;
  BOOLEAN                               IsTsegRegion;
  BOOLEAN                               FspApiMode;
#endif
  PSMI_DATA_HOB                         *PsmiDataHob;
  MEMORY_PLATFORM_DATA_HOB              *MemoryPlatformData;

  PsmiDataHob = NULL;
  Inputs = &MrcData->Inputs;
  PsmiMemoryRequired = FALSE;
  Outputs   = &MrcData->Outputs;
  MemoryMap2 = &Outputs->MemoryMapData;
#ifdef FSP_FLAG
  FspApiMode = FALSE;
  if (GetFspGlobalDataPointer()->FspMode == FSP_IN_API_MODE) {
    FspApiMode = TRUE;
  }
#endif

  DEBUG ((DEBUG_INFO, "Install EFI memory.\n"));
  //
  // Get the Memory Map
  //
  NumRanges = MAX_RANGES;
  ZeroMem (MemoryMap, sizeof (PEI_DUAL_CHANNEL_DDR_MEMORY_MAP_RANGE) * NumRanges);
  Status = GetMemoryMap (MrcData, (PEI_DUAL_CHANNEL_DDR_MEMORY_MAP_RANGE *) MemoryMap, &NumRanges);
  ASSERT_EFI_ERROR (Status);

  //
  // Find the highest memory range in processor native address space to give to
  // PEI. Then take the top.
  // If this algorithm changes, then we need to fix the capsule memory
  // selection algorithm below.
  //
  PeiMemoryBaseAddress = 0;
  InstalledPeiMemoryBaseAddress = 0;
  InstalledPeiMemoryLength = 0;
  ResourceAttributeTested = 0;
  //
  // Query the platform for the minimum memory size.
  //
  PeiMemoryLength = 0;
  RequiredMemSize = 0;
  SiPreMemPolicyPpi = NULL;
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  MemConfigNoCrc = NULL;
  if (SiPreMemPolicyPpi != NULL) {
    Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gMemoryConfigNoCrcGuid, (VOID *) &MemConfigNoCrc);
    if (MemConfigNoCrc != NULL) {
      PeiMemoryLength = MemConfigNoCrc->PlatformMemorySize;
    }
  }

  //
  // Locate the Hob structures
  //
  PsmiDataHob = (PSMI_DATA_HOB *)GetFirstGuidHob (&gPsmiDataHobGuid);
  ASSERT (PsmiDataHob != NULL);
  MemoryPlatformData = (MEMORY_PLATFORM_DATA_HOB *) GetFirstGuidHob (&gSiMemoryPlatformDataGuid);
  if (MemoryPlatformData == NULL) { // Skip PSMI allocation if output hob not present
    PsmiMemoryRequired = FALSE;
    DEBUG ((DEBUG_INFO, "MemoryPlatformData hob not found, skipping PSMI allocation \n"));
  }

#ifndef FSP_FLAG
  //
  // Get required memory size for ACPI use. This helps to put ACPI memory on the top.
  //
  RetrieveRequiredMemorySize (&RequiredMemSize);
#else
  if (FspApiMode) {
    RequiredMemSize = PcdGet32 (PcdFspReservedMemoryLength);
    FspmArchConfigPpi = NULL;
    BootLoaderTolumSize = 0;
    Status = PeiServicesLocatePpi (
               &gFspmArchConfigPpiGuid,
               0,
               NULL,
               (VOID **) &FspmArchConfigPpi
               );
    if (!EFI_ERROR (Status)) {
      BootLoaderTolumSize = FspmArchConfigPpi->BootLoaderTolumSize;
    }
    if ((RequiredMemSize + BootLoaderTolumSize) > PeiMemoryLength) {
      DEBUG ((DEBUG_ERROR, "Error: BootLoaderTolumSize Greater than available memory.\n"));
      DEBUG ((DEBUG_ERROR, "Force BootLoaderTolumSize to zero.\n"));
      BootLoaderTolumSize = 0;
    }
  } else {
    RetrieveRequiredMemorySize (&RequiredMemSize);
    BootLoaderTolumSize = 0;
  }
#endif
  DEBUG ((DEBUG_INFO, "Required memory size = 0x%x bytes\n", RequiredMemSize));
  PeiMemoryIndex = 0;
  for (Index = 0; Index < NumRanges; Index++) {
    DEBUG ((DEBUG_INFO, "Found %016Xh bytes at ", MemoryMap[Index].RangeLength));
    DEBUG ((DEBUG_INFO, "%016Xh\n", MemoryMap[Index].PhysicalAddress));
    if ((MemoryMap[Index].Type == DualChannelDdrMainMemory) &&
        (MemoryMap[Index].PhysicalAddress + MemoryMap[Index].RangeLength < MAX_ADDRESS) &&
        (MemoryMap[Index].PhysicalAddress >= PeiMemoryBaseAddress) &&
        (MemoryMap[Index].RangeLength >= PeiMemoryLength)) {
      PeiMemoryBaseAddress = MemoryMap[Index].PhysicalAddress + MemoryMap[Index].RangeLength - PeiMemoryLength;
      PeiMemoryIndex       = Index;
    }
  }

  //
  // Test only the PEI memory if necessary. Some platforms do not require the
  // Base Memory PEIM to be present.
  //
  switch (SysBootMode) {

  case BOOT_WITH_FULL_CONFIGURATION:
    MemoryTestLevel = Quick;
    break;

  case BOOT_WITH_FULL_CONFIGURATION_PLUS_DIAGNOSTICS:
    MemoryTestLevel = Extensive;
    break;

  default:
    MemoryTestLevel = Ignore;
    break;
  }
  if (SysBootMode != BOOT_ON_S3_RESUME) {
    ResourceAttributeTested = EFI_RESOURCE_ATTRIBUTE_TESTED;

   (*PeiServices)->ReportStatusCode (
             PeiServices,
             EFI_PROGRESS_CODE,                                  // Type
             EFI_COMPUTING_UNIT_MEMORY | EFI_CU_MEMORY_PC_TEST,  // Value
             0,    // Instance
             NULL, // *CallerId OPTIONAL
             NULL  // *Data OPTIONAL
             );
  }

  if (MemConfigNoCrc != NULL) {
    if ((MrcGetBootMode(MrcData) == bmWarm) && (MemConfigNoCrc->MemTestOnWarmBoot == 0)) {
      MemoryTestLevel = Ignore;
    }
  }
  Status = BaseMemoryTest (
             MrcData,
             PeiMemoryBaseAddress,
             PeiMemoryLength,
             MemoryTestLevel,
             &BadMemoryAddress
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Memory test failure at %lXh.\n", BadMemoryAddress));
    REPORT_STATUS_CODE (EFI_ERROR_CODE, EFI_COMPUTING_UNIT_MEMORY | EFI_CU_EC_NON_SPECIFIC);
  }

  ASSERT_EFI_ERROR (Status);

//@todo - Move EDKII non-FSP capsule outside of FSP code.
  CoalesceCapsule = TRUE;
#ifdef FSP_FLAG
  if (FspApiMode) {
    //
    // In FspApi mode, CapsulePpi->Coalesce and CreateState is executed outside of FSP.
    //
    CoalesceCapsule = FALSE;
  }
#endif
  Capsule             = NULL;
  CapsuleBuffer       = NULL;
  CapsuleBufferLength = 0;

  if ((SysBootMode == BOOT_ON_FLASH_UPDATE) && (CoalesceCapsule)) {
    Status = PeiServicesLocatePpi (
               &gPeiCapsulePpiGuid,
               0,
               NULL,
               (VOID **) &Capsule
               );
    ASSERT_EFI_ERROR (Status);

    if (Status == EFI_SUCCESS) {
      //
      // Find the largest memory range excluding that given to PEI.
      //
      for (Index = 0; Index < NumRanges; Index++) {
        if ((MemoryMap[Index].Type == DualChannelDdrMainMemory) &&
            (MemoryMap[Index].PhysicalAddress + MemoryMap[Index].RangeLength < MAX_ADDRESS)) {
          if (Index != PeiMemoryIndex) {
            if (MemoryMap[Index].RangeLength > CapsuleBufferLength) {
              CapsuleBuffer       = (VOID *) ((UINTN) MemoryMap[Index].PhysicalAddress);
              CapsuleBufferLength = (UINTN) MemoryMap[Index].RangeLength;
            }
          } else {
            if ((MemoryMap[Index].RangeLength - PeiMemoryLength) >= CapsuleBufferLength) {
              CapsuleBuffer       = (VOID *) ((UINTN) MemoryMap[Index].PhysicalAddress);
              CapsuleBufferLength = (UINTN) (MemoryMap[Index].RangeLength - PeiMemoryLength);
            }
          }
        }
      }
      //
      // Call the Capsule PPI Coalesce function to coalesce the capsule data.
      //
      Status = Capsule->Coalesce ((EFI_PEI_SERVICES **) PeiServices, &CapsuleBuffer, &CapsuleBufferLength);
    }
    //
    // If it failed, then NULL out our capsule PPI pointer so that the capsule
    // HOB does not get created below.
    //
    if (Status != EFI_SUCCESS) {
      Capsule = NULL;
    }
  }

#ifndef FSP_FLAG
  if (SysBootMode != BOOT_ON_S3_RESUME) {
    InstalledPeiMemoryBaseAddress = PeiMemoryBaseAddress;
    //
    // Carve out the top memory reserved for ACPI.
    //
    InstalledPeiMemoryLength = PeiMemoryLength - RequiredMemSize;
  } else {
    InstalledPeiMemoryBaseAddress = MiscPeiPreMemConfig->AcpiReservedMemoryBase;
    InstalledPeiMemoryLength = MiscPeiPreMemConfig->AcpiReservedMemorySize;
  }
#else
  if (FspApiMode) {
    InstalledPeiMemoryBaseAddress = PeiMemoryBaseAddress + PeiMemoryLength - BootLoaderTolumSize - RequiredMemSize;
    InstalledPeiMemoryLength = RequiredMemSize;
  } else {
    InstalledPeiMemoryBaseAddress = PeiMemoryBaseAddress;
    InstalledPeiMemoryLength = PeiMemoryLength - RequiredMemSize;
    if (SysBootMode == BOOT_ON_S3_RESUME) {
      InstalledPeiMemoryBaseAddress = MiscPeiPreMemConfig->AcpiReservedMemoryBase;
      InstalledPeiMemoryLength = MiscPeiPreMemConfig->AcpiReservedMemorySize;
    }
  }
#endif

  Status = PeiServicesInstallPeiMemory (InstalledPeiMemoryBaseAddress, InstalledPeiMemoryLength);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "Building RESOURCE_SYSTEM_MEMORY Hob: \n"));
  DEBUG ((DEBUG_INFO, "PeiMemoryBaseAddress = %lXh, PeiMemoryLength = %lXh\n", InstalledPeiMemoryBaseAddress, InstalledPeiMemoryLength));

#ifndef FSP_FLAG
  if (SysBootMode != BOOT_ON_S3_RESUME) {
    BuildResourceDescriptorHob (
      EFI_RESOURCE_SYSTEM_MEMORY,
      (
        EFI_RESOURCE_ATTRIBUTE_PRESENT |
        EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
        ResourceAttributeTested |
        EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |
        EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE |
        EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE |
        EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE
        ),
     PeiMemoryBaseAddress,
     PeiMemoryLength
     );
  }
#else
  if (FspApiMode) {
    DEBUG ((DEBUG_INFO, "FSP_RESERVED_MEMORY_RESOURCE_HOB\n"));
    // Build HOB that describes at BootLoader TOLUM Resource reserved at top of main memory below 4GB.
    if (BootLoaderTolumSize > 0) {
      DEBUG ((DEBUG_INFO, "FSP_BOOT_LOADER_TOLUM_HOB\n"));
      DEBUG ((DEBUG_INFO, "FspBootLoaderTolum Base : %x\n", PeiMemoryBaseAddress + PeiMemoryLength - BootLoaderTolumSize));
      DEBUG ((DEBUG_INFO, "FspBootLoaderTolum Size : %x\n", BootLoaderTolumSize));
      BuildResourceDescriptorWithOwnerHob (
        EFI_RESOURCE_MEMORY_RESERVED,             // MemoryType,
        (
          EFI_RESOURCE_ATTRIBUTE_PRESENT |
          EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
          ResourceAttributeTested |
          EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |
          EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE |
          EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE |
          EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE
          ),
        PeiMemoryBaseAddress + PeiMemoryLength - BootLoaderTolumSize,
        BootLoaderTolumSize,
        &gFspBootLoaderTolumHobGuid
        );
    }
    // HOB that describes FSP reserved memory below BootLoader TOLUM.
    DEBUG ((DEBUG_INFO, "FspReservedMemoryResource Base : %x\n", PeiMemoryBaseAddress + PeiMemoryLength - BootLoaderTolumSize - RequiredMemSize));
    DEBUG ((DEBUG_INFO, "FspReservedMemoryResource Size : %x\n", RequiredMemSize));
    BuildResourceDescriptorWithOwnerHob (
      EFI_RESOURCE_MEMORY_RESERVED,             // MemoryType,
      (
        EFI_RESOURCE_ATTRIBUTE_PRESENT |
        EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
        ResourceAttributeTested |
        EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |
        EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE |
        EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE |
        EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE
        ),
      InstalledPeiMemoryBaseAddress,
      InstalledPeiMemoryLength,
      &gFspReservedMemoryResourceHobGuid
      );
  } else {
    if (SysBootMode != BOOT_ON_S3_RESUME) {
      BuildResourceDescriptorHob (
        EFI_RESOURCE_SYSTEM_MEMORY,
        (
          EFI_RESOURCE_ATTRIBUTE_PRESENT |
          EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
          ResourceAttributeTested |
          EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |
          EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE |
          EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE |
          EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE
          ),
       PeiMemoryBaseAddress,
       PeiMemoryLength
       );
    }
  }
#endif

  //
  // Install physical memory descriptor hobs for each memory range.
  //
  SmramRanges = 0;
  for (Index = 0; Index < NumRanges; Index++) {
#ifdef FSP_FLAG
    IsTsegRegion = FALSE;
#endif
    if (MemoryMap[Index].Type == DualChannelDdrMainMemory) {
      if (Index == PeiMemoryIndex) {
        //
        // This is a partially tested Main Memory range, give it to EFI
        //
#ifndef FSP_FLAG
        if (SysBootMode != BOOT_ON_S3_RESUME){
          RangeLength = MemoryMap[Index].RangeLength - PeiMemoryLength;
        } else {
          RangeLength = MemoryMap[Index].RangeLength;
        }
#else
        //
        // In this RangeLength remove RequiredMemSize and BootLoaderTolumSize as it is described in
        // the gFspBootLoaderTolumHobGuid and gFspReservedMemoryResourceHobGuid Resource HOBs.
        //
        if (FspApiMode) {
          RangeLength = MemoryMap[Index].RangeLength - RequiredMemSize - BootLoaderTolumSize;
        } else {
          RangeLength = MemoryMap[Index].RangeLength - PeiMemoryLength;
          if (SysBootMode == BOOT_ON_S3_RESUME) {
            RangeLength = MemoryMap[Index].RangeLength;
          }
        }
#endif
      } else {
        //
        // This is an untested Main Memory range, give it to EFI.
        //
        RangeLength = MemoryMap[Index].RangeLength;
      }
      BuildResourceDescriptorHob (
        EFI_RESOURCE_SYSTEM_MEMORY,
        (
          EFI_RESOURCE_ATTRIBUTE_PRESENT |
          EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
          //
          // RC Override: mark <4G available memory as tested to give DXE enough memory space, so that default
          // memory allocations won't occupy the bins for specific memory types.
          //
          ResourceAttributeTested |
          EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |
          EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE |
          EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE |
          EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE
          ),
        MemoryMap[Index].PhysicalAddress,
        RangeLength
        );

      //
      // Test this memory range
      //
      Status = BaseMemoryTest (
                 MrcData,
                 MemoryMap[Index].PhysicalAddress,
                 RangeLength,
                 MemoryTestLevel,
                 &BadMemoryAddress
                 );
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "Memory test failure at %lXh.\n", BadMemoryAddress));
        REPORT_STATUS_CODE (EFI_ERROR_CODE, EFI_COMPUTING_UNIT_MEMORY | EFI_CU_EC_NON_SPECIFIC);
        ASSERT_EFI_ERROR (Status);
      }
    } else {
      ResourceAttribute = 0;
      if ((
            (MemoryMap[Index].Type == DualChannelDdrSmramCacheable) ||
            (MemoryMap[Index].Type == DualChannelDdrSmramNonCacheable)
            ) &&
          (MemoryMap[Index].PhysicalAddress != MC_ABSEG_HSEG_PHYSICAL_START)) {
        //
        // Only count and report TSEG.
        //
#ifdef FSP_FLAG
        IsTsegRegion = TRUE;
#endif
        SmramRanges++;
      } else if (MemoryMap[Index].Type == DualChannelDdrReservedWriteBackMemory) {
        ResourceAttribute = EFI_RESOURCE_ATTRIBUTE_PRESENT |
                            EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
                            ResourceAttributeTested |
                            EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |
                            EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE |
                            EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE |
                            EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE;
      }
      //
      // Make sure non-system memory is marked as reserved.
      //
#ifdef FSP_FLAG
      if (IsTsegRegion){
        //
        // Build an Tseg resource Hob for Fsp
        //
        BuildResourceDescriptorWithOwnerHob (
          EFI_RESOURCE_MEMORY_RESERVED,          // MemoryType,
          ResourceAttribute,                     // MemoryAttribute
          MemoryMap[Index].PhysicalAddress,      // MemoryBegin
          MemoryMap[Index].RangeLength,          // MemoryLength
          &gFspReservedMemoryResourceHobTsegGuid // OwnerGUID
        );
      } else {
#endif
        BuildResourceDescriptorHob (
          EFI_RESOURCE_MEMORY_RESERVED,     // MemoryType,
          ResourceAttribute,                // MemoryAttribute
          MemoryMap[Index].PhysicalAddress, // MemoryBegin
          MemoryMap[Index].RangeLength      // MemoryLength
        );
#ifdef FSP_FLAG
      }
#endif
    }
  }

  BufferSize = sizeof (EFI_SMRAM_HOB_DESCRIPTOR_BLOCK);
  if (SmramRanges > 0) {
    BufferSize += ((SmramRanges - 1) * sizeof (EFI_SMRAM_DESCRIPTOR));
  }

  Hob.Raw = BuildGuidHob (&gEfiSmmPeiSmramMemoryReserveGuid, BufferSize);
  if (Hob.Raw == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  SmramHobDescriptorBlock = (void *) (Hob.Raw);
  SmramHobDescriptorBlock->NumberOfSmmReservedRegions = SmramRanges;

  SmramIndex = 0;
  for (Index = 0; Index < NumRanges; Index++) {
  ResourceAttribute = 0;
    if ((
          (MemoryMap[Index].Type == DualChannelDdrSmramCacheable) ||
          (MemoryMap[Index].Type == DualChannelDdrSmramNonCacheable)
          ) &&
        (MemoryMap[Index].PhysicalAddress != MC_ABSEG_HSEG_PHYSICAL_START)) {
      //
      // This is an SMRAM range (not reporting AB_SEG or H_SEG), create an SMRAM descriptor.
      //
      SmramDescriptor = &SmramHobDescriptorBlock->Descriptor[SmramIndex];
      SmramDescriptor->PhysicalStart = MemoryMap[Index].PhysicalAddress;
      SmramDescriptor->CpuStart      = MemoryMap[Index].CpuAddress;

      //
      // RangeLength includes alignment adjustment.
      //
      if (SmramDescriptor->PhysicalStart < 0x100000) {
        SmramDescriptor->PhysicalSize  = MemoryMap[Index].RangeLength;
      } else {
        SmramDescriptor->PhysicalSize  = (Inputs->TsegSize) * 0x100000;
      }
      DEBUG ((DEBUG_INFO, "TSeg base is %Xh\n", SmramDescriptor->PhysicalStart));
      DEBUG ((DEBUG_INFO, "TSeg SMRAM size is %Xh\n", SmramDescriptor->PhysicalSize));

      if (MemoryMap[Index].Type == DualChannelDdrSmramCacheable) {
        SmramDescriptor->RegionState = EFI_SMRAM_CLOSED | EFI_CACHEABLE;
      } else {
        SmramDescriptor->RegionState = EFI_SMRAM_CLOSED;
      }
      SmramIndex++;
    }
  }
  //
  // Get the current "Top of Upper Usable Memory" address from TOUUD.
  // If TOUUD > 4G, it means memory is re-mapped.
  //
  McD0BaseAddress               = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, 0);
  TopUseableMemSize.Data32.High = PciSegmentRead32 (McD0BaseAddress + R_SA_TOUUD + 4);
  TopUseableMemSize.Data32.Low  = PciSegmentRead32 (McD0BaseAddress + R_SA_TOUUD);
  TopUseableMemSize.Data        = TopUseableMemSize.Data & B_SA_TOUUD_TOUUD_MASK;
  TopUseableMemAddr             = MEM_EQU_4GB;
  Tom.Data32.High               = PciSegmentRead32 (McD0BaseAddress + R_SA_TOM + 4);
  Tom.Data32.Low                = PciSegmentRead32 (McD0BaseAddress + R_SA_TOM);
  Tom.Data                      = Tom.Data & B_SA_TOM_TOM_MASK;

  if (NULL != MemoryPlatformData) {
    // MemoryPlatformData hob is present so find out if PSMI memory is required.
    for (Index = 0; Index < MAX_TRACE_CACHE_TYPE; Index++) {
      if (PsmiDataHob->PsmiConfig.PsmiMrcParam[Index].TotalSize) {
        PsmiMemoryRequired = TRUE;
        break;
      }
    }
  }
  //
  // No Memory Available above 4GB, add the error code
  //
  if (PsmiMemoryRequired && (TopUseableMemSize.Data <= MEM_EQU_4GB)) {
    for (Index = 0; Index < MAX_TRACE_CACHE_TYPE; Index++) {
      MemoryPlatformData->Data.PsmiInfo[Index].ErrorCode = ERROR_NO_ABOVE_4G_MEMORY;
    }
  }

  //
  // Align at 512 MB boundary in end since FSP later reserves MTRR for High Memory at 512 MB alignment upwards which overlaps with PSMIU memory
  //
  Alignment = 0x20000000;
  if (TopUseableMemSize.Data > MEM_EQU_4GB) {
    UINT64 PrmrrBase;
    UINT32 PrmrrSize;

    PrmrrBase = LShiftU64 (MrcData->Outputs.MemoryMapData.PrmrrBase, 20);
    PrmrrSize = Inputs->PrmrrSize << 20;
    TopUseableMemAddr = MEM_EQU_4GB;

    if (PrmrrBase == TopUseableMemAddr) {
      TopUseableMemAddr += PrmrrSize;
      TopUseableMemSize.Data -= PrmrrSize;
    }

    if (PsmiMemoryRequired) {
      for (Index = 0; Index < MAX_TRACE_CACHE_TYPE; Index++) {
        //
        // Check if any of PSMI memory Type needed
        //
        PsmiMemSize = PsmiDataHob->PsmiConfig.PsmiMrcParam[Index].TotalSize;
        if (PsmiMemSize == 0) {
          continue;
        }

        if ((TopUseableMemSize.Data <= MEM_EQU_4GB) || (PsmiMemSize > (TopUseableMemSize.Data - MEM_EQU_4GB))) {
          //
          // Not sufficient memory above 4G
          //
          MemoryPlatformData->Data.PsmiInfo[Index].ErrorCode = ERROR_OUT_OF_RESOURCES;
          break;
        }
        ResourceType         = EFI_RESOURCE_MEMORY_RESERVED;
        ResourceAttribute    = 0;

        PsmiMemBaseAddr      = TopUseableMemSize.Data - PsmiMemSize;
        if (PsmiDataHob->PsmiConfig.PsmiMrcParam[Index].CacheType == RegionUncacheable) { // PSMI memory Uncacheable
          ResourceAttribute = EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE;
          MemoryPlatformData->Data.PsmiInfo[Index].CacheType = RegionUncacheable;
        } else if (PsmiDataHob->PsmiConfig.PsmiMrcParam[Index].CacheType == RegionWriteCombine) { // Write-Combine
          ResourceAttribute = EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE;
          MemoryPlatformData->Data.PsmiInfo[Index].CacheType = RegionWriteCombine;
        }
        BuildResourceDescriptorHob (
          ResourceType,       // MemoryType,
          ResourceAttribute,  // MemoryAttribute
          PsmiMemBaseAddr,    // MemoryBegin
          PsmiMemSize         // MemoryLength
          );
        TopUseableMemSize.Data = TopUseableMemSize.Data - PsmiMemSize;
        MemoryPlatformData->Data.PsmiInfo[Index].BaseAddress = PsmiMemBaseAddr;
        DEBUG ((DEBUG_INFO, "Found 0x%lx bytes PSMI reserved at 0x%lx\n", PsmiMemSize, PsmiMemBaseAddr));
      }
      //
      // Reserve 512 MB below PSMI memory for alignment, capture error Out of Resources if No/less above 4G memory for alignment
      //
      if ((TopUseableMemSize.Data - Alignment) < MEM_EQU_4GB) {
        for (Index = 0; Index < MAX_TRACE_CACHE_TYPE; Index++) {
          MemoryPlatformData->Data.PsmiInfo[Index].ErrorCode = ERROR_OUT_OF_RESOURCES;
        }
      } else {
        ResourceType      = EFI_RESOURCE_MEMORY_RESERVED;
        ResourceAttribute = 0;

        BuildResourceDescriptorHob (
          ResourceType,                        // MemoryType,
          ResourceAttribute,                   // MemoryAttribute
          TopUseableMemSize.Data - Alignment,  // MemoryBegin
          Alignment                            // MemoryLength
          );
        TopUseableMemSize.Data = TopUseableMemSize.Data - Alignment;
        DEBUG ((DEBUG_INFO, "Found 0x%x bytes for PSMI alignment reserved at 0x%lx\n", Alignment, TopUseableMemSize.Data));
      }
    } // if(PsmiMemoryRequired == TRUE)

    //
    // This is above 4G memory address, give it to EFI.
    //
    TopMemSize = TopUseableMemSize.Data - MEM_EQU_4GB;

    // Ibecc
    if ((Inputs->Ibecc == TRUE) && ((Inputs->IbeccOperationMode == 0) || (Inputs->IbeccOperationMode == 2))) {
      TopMemSize -=  (UINT64) Outputs->IbeccEdsrSize << 20;
    }

    DEBUG ((DEBUG_INFO, "Found 0x%016lX bytes at 0x%016lX\n", TopMemSize, TopUseableMemAddr));
    if (Inputs->MemoryTrace && (TopUseableMemAddr + TopMemSize > RShiftU64 (Tom.Data, 1))) {
      //
      // Mark memory above 4GB as reserved if it's used for Memory Trace
      //
      ResourceType      = EFI_RESOURCE_MEMORY_RESERVED;
      ResourceAttribute = 0;
    } else {
      ResourceType      = EFI_RESOURCE_SYSTEM_MEMORY;
      ResourceAttribute = EFI_RESOURCE_ATTRIBUTE_PRESENT |
                          EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
                          EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |
                          EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE |
                          EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE |
                          EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE;
    }
    BuildResourceDescriptorHob (
      ResourceType,       // MemoryType,
      ResourceAttribute,  // MemoryAttribute
      TopUseableMemAddr,  // MemoryBegin
      TopMemSize          // MemoryLength
      );
  }

  // Ibecc
  if ((Inputs->Ibecc == TRUE) && ((Inputs->IbeccOperationMode == 0) || (Inputs->IbeccOperationMode == 2))) {
    BuildResourceDescriptorHob (
      EFI_RESOURCE_MEMORY_RESERVED,                                             // MemoryType,
      0,                                                                        // MemoryAttribute
      ((UINT64) MemoryMap2->TouudBase - (UINT64) Outputs->IbeccEdsrSize) << 20, // Memory Begin
      (UINT64) Outputs->IbeccEdsrSize << 20                                     // MemoryLength
      );
  }

#ifdef FSP_FLAG
  // @todo: Is allocation needed.

  //
  // Allocate I/O space resource
  //
  BuildResourceDescriptorHob (
    EFI_RESOURCE_IO,
    (
      EFI_RESOURCE_ATTRIBUTE_PRESENT     |
      EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
      EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE
    ),
    RES_IO_BASE,
    RES_IO_LIMIT - RES_IO_BASE + 1
  );
  DEBUG ((DEBUG_INFO, " Providing I/O space resource from 0x%X to 0x%X\n", RES_IO_BASE, RES_IO_LIMIT - RES_IO_BASE + 1));
#endif

#ifdef FSP_FLAG
{
// @todo: Is allocation needed.

  //
  // Allocate PCI memory space.
  // First read memory map registers to calculate available MMIO resource
  //
  EFI_PHYSICAL_ADDRESS  Tolud;
  EFI_PHYSICAL_ADDRESS  PciBaseAddress;
  UINT64                Length;

  Tolud                 = (EFI_PHYSICAL_ADDRESS) PciSegmentRead32 (McD0BaseAddress + R_SA_TOLUD) & B_SA_TOLUD_TOLUD_MASK;
  PciBaseAddress        = Tolud;

  Length = RES_MEM_LIMIT_1 - PciBaseAddress + 1;

  if (Length != 0) {
    DEBUG ((DEBUG_INFO, " Providing PCI space from 0x%X to 0x%X\n", (UINT32) PciBaseAddress, (UINT32)(PciBaseAddress + Length - 1)));
    BuildResourceDescriptorHob (
      EFI_RESOURCE_MEMORY_MAPPED_IO,
      (
        EFI_RESOURCE_ATTRIBUTE_PRESENT     |
        EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
        EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE
      ),
      PciBaseAddress,
      Length
    );
  }
}
#endif


  if (SysBootMode != BOOT_ON_S3_RESUME) {

    //
    // If we found the capsule PPI (and we didn't have errors), then
    // call the capsule PEIM to allocate memory for the capsule.
    //
    if (Capsule != NULL) {
      Status = Capsule->CreateState ((EFI_PEI_SERVICES **) PeiServices, CapsuleBuffer, CapsuleBufferLength);
    }
  }

  //
  // Create SMRAM ACPI Variable Hob
  //
  CreateS3AcpiVariableHob ();

#ifdef FSP_FLAG
  //
  // Build Hob for Hob memory usage information.
  //
  BuildHobUsageDataHob ();
#endif // FSP_FLAG

  return EFI_SUCCESS;
}

/**
  Determine the memory size desired based on HOB memory information.

  @param[in, out] Size        - The memory size to return.
**/
void
RetrieveRequiredMemorySize (
  IN OUT    UINTN             *Size
  )
{
  EFI_STATUS                  Status;
  EFI_PEI_HOB_POINTERS        Hob;
  EFI_MEMORY_TYPE_INFORMATION *MemoryData;
  UINT8                       Index;
  UINTN                       TempPageNum;

  *Size      = 0;
  MemoryData = NULL;
  Status     = PeiServicesGetHobList ((VOID **) &Hob.Raw);
  ASSERT_EFI_ERROR (Status);

  while (!END_OF_HOB_LIST (Hob)) {
    if (Hob.Header->HobType == EFI_HOB_TYPE_GUID_EXTENSION &&
      CompareGuid (&Hob.Guid->Name, &gEfiMemoryTypeInformationGuid)) {
      MemoryData = (EFI_MEMORY_TYPE_INFORMATION *) (Hob.Raw + sizeof (EFI_HOB_GENERIC_HEADER) + sizeof (EFI_GUID));
      break;
    }

    Hob.Raw = GET_NEXT_HOB (Hob);
  }
  //
  // Platform PEIM should supply the information. Generic PEIM doesn't assume any default value.
  //
  if (MemoryData == NULL) {
    return;
  }

  TempPageNum = 0;
  for (Index = 0; MemoryData[Index].Type != EfiMaxMemoryType; Index++) {
    //
    // Accumulate default memory size requirements
    //
    TempPageNum += MemoryData[Index].NumberOfPages;
  }

  if (TempPageNum == 0) {
    return;
  }
  //
  // 16 additional pages are used by DXE memory manager.
  //
  *Size = (TempPageNum + 16) * EFI_PAGE_SIZE;

  return;
}

/**
  Determine the Total DPR memory size needed based on the DPR directory in the SA Data HOB.

  @param[in, out] Size        - The memory size in MB to return.
**/
void
CalculateTotalDprMemorySize (
  IN OUT   UINT8             *Size
  )
{
  UINT8                DprEntryIndex;
  SA_CONFIG_HOB        *SaConfigHob;
  DPR_DIRECTORY_ENTRY  *DirectoryEntry;

  *Size           = 0;
  DprEntryIndex   = 0;
  DirectoryEntry  = NULL;
  SaConfigHob       = NULL;

  SaConfigHob = GetFirstGuidHob (&gSaConfigHobGuid);
  if (SaConfigHob != NULL) {
    DirectoryEntry = SaConfigHob->DprDirectory;
    while (DprEntryIndex < DPR_DIRECTORY_MAX) {
      *Size += DirectoryEntry->Size;
      DirectoryEntry++;
      DprEntryIndex++;
    }
  }
  return;
}

/**
  Calculates the bases for each technology consuming the DPR region
  and updates the SA Data HOB with the appropriate values in the Dpr
  directory

  @param[in] Base           - The memory base to return.
  @param[in] TotalDprSizeMB - The total DPR size in MB
**/
void
UpdateDprHobInfo (
  IN       EFI_PHYSICAL_ADDRESS  Base,
  IN       UINT8                 TotalDprSizeMB
  )
{
  UINT32               TopOfDpr;
  UINT8                DprEntryIndex;
  SA_CONFIG_HOB        *SaConfigHob;
  DPR_DIRECTORY_ENTRY  *DirectoryEntry;

  DprEntryIndex   = 0;
  DirectoryEntry  = NULL;
  SaConfigHob       = NULL;
  TopOfDpr        = (UINT32) Base + (UINT32) LShiftU64 (TotalDprSizeMB, 20);

  SaConfigHob = GetFirstGuidHob (&gSaConfigHobGuid);
  if (SaConfigHob != NULL) {
    DirectoryEntry = SaConfigHob->DprDirectory;
    while (DprEntryIndex < DPR_DIRECTORY_MAX) {
      switch (DirectoryEntry->Type) {
        case DPR_DIRECTORY_TYPE_TXT:
          DirectoryEntry->PhysBase = (UINT32) TopOfDpr - (UINT32) LShiftU64(DirectoryEntry->Size, 20);
          break;
        case DPR_DIRECTORY_TYPE_BIOSGUARD:
          DirectoryEntry->PhysBase = (UINT32) Base;
          break;
        default:
          break;
      }
      DirectoryEntry++;
      DprEntryIndex++;
    }
  }
  return;
}

/**
  This function returns the memory ranges to be enabled, along with information
  describing how the range should be used. The MemoryMap buffer will be filled in and
  NumRanges will contain the actual number of memory ranges that are to be enabled.

  @param[in]      MrcData     - Mrc data structure
  @param[in, out] MemoryMap   - Buffer to record details of the memory ranges to be enabled.
  @param[in, out] NumRanges   - On input, this contains the maximum number of memory ranges that
                                can be described in the MemoryMap buffer.

  @retval EFI_SUCCESS          - The function completed successfully.
  @retval EFI_BUFFER_TOO_SMALL - The specified number of ranges is too large.
**/
EFI_STATUS
GetMemoryMap (
  IN MrcParameters  *CONST                        MrcData,
  IN OUT   PEI_DUAL_CHANNEL_DDR_MEMORY_MAP_RANGE  *MemoryMap,
  IN OUT   UINT8                                  *NumRanges
  )
{
  const MrcInput          *Inputs;
  MrcOutput               *Outputs;
  MrcMemoryMap            *MemoryMapData;
  EFI_STATUS              Status;
  UINT32                  SmramMask;
  UINT8                   Index;
  SI_PREMEM_POLICY_PPI    *SiPreMemPolicyPpi;
  MEMORY_CONFIGURATION    *MemConfig;

  if ((*NumRanges) < MAX_RANGES) {
    return EFI_BUFFER_TOO_SMALL;
  }

  *NumRanges  = 0;

  Inputs    = &MrcData->Inputs;
  Outputs   = &MrcData->Outputs;
  MemoryMapData = &Outputs->MemoryMapData;

  //
  // Get platform memory range service
  //
  SmramMask = 0;
  SiPreMemPolicyPpi = NULL;
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);

  if (SiPreMemPolicyPpi != NULL) {
    MemConfig = NULL;
    Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gMemoryConfigGuid, (VOID *) &MemConfig);
    ASSERT_EFI_ERROR (Status);

    if (MemConfig != NULL) {
      //
      // Find out which memory ranges to reserve on this platform
      //
      SmramMask = MemConfig->SmramMask;
    }
  }

  //
  // Generate memory ranges for the memory map.
  //
  Index           = 0;

  //
  // Get the current "max usable memory" address from TOLUD because we will not
  // support any memory above 4Gig.  Will ignore the memory between 4G and TOUUD.
  //

  //
  // System is very unlikely to work with less than 32MB
  //
  ASSERT ((MemoryMapData->ToludBase << 20) >= (32 * 1024 * 1024));

  //
  // Add memory below 640KB to the memory map. Make sure memory between
  // 640KB and 1MB are reserved, even if not used for SMRAM
  //
  MemoryMap[*NumRanges].RowNumber       = Index;
  MemoryMap[*NumRanges].PhysicalAddress = ADDRESS_SPACE_START;
  MemoryMap[*NumRanges].CpuAddress      = ADDRESS_SPACE_START;
  MemoryMap[*NumRanges].RangeLength     = 0xA0000;
  MemoryMap[*NumRanges].Type            = DualChannelDdrMainMemory;
  (*NumRanges)++;

  //
  // Reserve ABSEG or HSEG SMRAM if needed
  //
  if (SmramMask & (PEI_MR_SMRAM_ABSEG_MASK | PEI_MR_SMRAM_HSEG_MASK)) {
    MemoryMap[*NumRanges].PhysicalAddress = MC_ABSEG_HSEG_PHYSICAL_START;
    MemoryMap[*NumRanges].RangeLength     = MC_ABSEG_HSEG_LENGTH;
    MemoryMap[*NumRanges].CpuAddress      = (SmramMask & PEI_MR_SMRAM_ABSEG_MASK) ?
      MC_ABSEG_CPU_START :
      MC_HSEG_CPU_START;
    //
    // Chipset only supports cacheable SMRAM.
    //
    MemoryMap[*NumRanges].Type = DualChannelDdrSmramNonCacheable;
  } else {
    //
    // Just mark this range reserved.
    //
    MemoryMap[*NumRanges].PhysicalAddress = MC_ABSEG_HSEG_PHYSICAL_START;
    MemoryMap[*NumRanges].CpuAddress      = MC_ABSEG_CPU_START;
    MemoryMap[*NumRanges].RangeLength     = 0x60000;
    MemoryMap[*NumRanges].Type            = DualChannelDdrReservedMemory;
  }
  MemoryMap[*NumRanges].RowNumber = Index;
  (*NumRanges)++;

  //
  // Add remaining memory to the memory map.
  //
  MemoryMap[*NumRanges].RowNumber       = Index;
  MemoryMap[*NumRanges].PhysicalAddress = LOWER_MEMORY_START;
  MemoryMap[*NumRanges].CpuAddress      = LOWER_MEMORY_START;
  MemoryMap[*NumRanges].RangeLength     = MemoryMapData->LowestBase - LOWER_MEMORY_START;
  MemoryMap[*NumRanges].Type            = DualChannelDdrMainMemory;
  (*NumRanges)++;

  //
  // IMR
  //
  if (MemoryMapData->MeStolenSize > 0) {
    MemoryMap[*NumRanges].RowNumber       = Index;
    MemoryMap[*NumRanges].PhysicalAddress = (MemoryMapData->MeStolenBase << 20);
    MemoryMap[*NumRanges].CpuAddress      = (MemoryMapData->MeStolenBase << 20);
    MemoryMap[*NumRanges].RangeLength     = (MemoryMapData->MeStolenSize << 20);
    MemoryMap[*NumRanges].Type            = DualChannelDdrReservedWriteBackMemory;
    (*NumRanges)++;
  }

  //
  // PRAM
  //
  if (Inputs->PramSize > 0) {
    MemoryMap[*NumRanges].RowNumber       = Index;
    MemoryMap[*NumRanges].PhysicalAddress = (MemoryMapData->PramBase << 20);
    MemoryMap[*NumRanges].CpuAddress      = (MemoryMapData->PramBase << 20);
    MemoryMap[*NumRanges].RangeLength     = (Inputs->PramSize << 20);
    MemoryMap[*NumRanges].Type            = DualChannelDdrReservedWriteBackMemory;
    (*NumRanges)++;
  }

  //
  // PRMRR
  //
  if (Inputs->PrmrrSize > 0) {
    MemoryMap[*NumRanges].RowNumber       = Index;
    MemoryMap[*NumRanges].PhysicalAddress = (MemoryMapData->PrmrrBase << 20);
    MemoryMap[*NumRanges].CpuAddress      = (MemoryMapData->PrmrrBase << 20);
    MemoryMap[*NumRanges].RangeLength     = (Inputs->PrmrrSize << 20);
    MemoryMap[*NumRanges].Type            = DualChannelDdrReservedWriteBackMemory;
    (*NumRanges)++;
  }

  //
  // DPR
  //
  if (Inputs->DprSize > 0) {
    MemoryMap[*NumRanges].RowNumber       = Index;
    MemoryMap[*NumRanges].PhysicalAddress = ((MemoryMapData->TsegBase - Inputs->DprSize) << 20);
    MemoryMap[*NumRanges].CpuAddress      = ((MemoryMapData->TsegBase - Inputs->DprSize) << 20);
    MemoryMap[*NumRanges].RangeLength     = (Inputs->DprSize << 20);
    MemoryMap[*NumRanges].Type            = DualChannelDdrReservedMemory;

    UpdateDprHobInfo (MemoryMap[*NumRanges].PhysicalAddress, (UINT8)Inputs->DprSize);

    (*NumRanges)++;
  }

  //
  // TSEG
  //
  if (Inputs->TsegSize > 0) {
    MemoryMap[*NumRanges].RowNumber       = Index;
    MemoryMap[*NumRanges].PhysicalAddress = (MemoryMapData->TsegBase << 20);
    MemoryMap[*NumRanges].CpuAddress      = (MemoryMapData->TsegBase << 20);
    MemoryMap[*NumRanges].RangeLength     = (Inputs->TsegSize << 20);
    MemoryMap[*NumRanges].Type            = DualChannelDdrSmramCacheable;
    (*NumRanges)++;
  }

  //
  // BGSM (GFX GTT)
  //
  if (Outputs->GraphicsGttSize > 0) {
    MemoryMap[*NumRanges].RowNumber       = Index;
    MemoryMap[*NumRanges].PhysicalAddress = (MemoryMapData->GttBase << 20);
    MemoryMap[*NumRanges].CpuAddress      = (MemoryMapData->GttBase << 20);
    MemoryMap[*NumRanges].RangeLength     = (Outputs->GraphicsGttSize << 20);
    MemoryMap[*NumRanges].Type            = DualChannelDdrReservedMemory;
    (*NumRanges)++;
  }

  //
  // BDSM (GFX UMA)
  //
  if (Outputs->GraphicsStolenSize > 0) {
    MemoryMap[*NumRanges].RowNumber       = Index;
    MemoryMap[*NumRanges].PhysicalAddress = (MemoryMapData->BdsmBase << 20);
    MemoryMap[*NumRanges].CpuAddress      = (MemoryMapData->BdsmBase << 20);
    MemoryMap[*NumRanges].RangeLength     = (Outputs->GraphicsStolenSize << 20);
    MemoryMap[*NumRanges].Type            = DualChannelDdrReservedMemory;
    (*NumRanges)++;
  }

  //
  // TXT space (Private / Public / TPM / DbC TraceHub / other)
  //
  MemoryMap[*NumRanges].RowNumber       = Index;
  MemoryMap[*NumRanges].PhysicalAddress = TXT_PRIVATE_BASE;
  MemoryMap[*NumRanges].CpuAddress      = TXT_PRIVATE_BASE;
  MemoryMap[*NumRanges].RangeLength     = TXT_CONFIG_SPACE_LENGTH;
  MemoryMap[*NumRanges].Type            = DualChannelDdrReservedMemory;
  (*NumRanges)++;

  return EFI_SUCCESS;
}

/**
  This function returns a pointer to the allocated hand off buffer.

  @param[in, out] Hob         - A pointer to where to store the pointer to the allocated data buffer.
  @param[in]      BlockSize   - The size of the buffer to get.
  @param[in]      Guid        - The GUID to assign to the HOB.

  @retval EFI_SUCCESS - Hob is successfully built.
  @retval Others      - Error occurred while creating the Hob.
**/
EFI_STATUS
MrcGetHobForDataStorage (
  IN OUT VOID                     **Hob,
  IN     UINT16                   BlockSize,
  IN     EFI_GUID                 *Guid
  )
{
  EFI_HOB_GUID_TYPE *Buffer;
  EFI_STATUS        Status;

  Status = PeiServicesCreateHob (EFI_HOB_TYPE_GUID_EXTENSION, BlockSize, Hob);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  Buffer = (EFI_HOB_GUID_TYPE *) *Hob;
  CopyMem (&(Buffer->Name), Guid, sizeof (EFI_GUID));
  ZeroMem ((VOID *) ((UINT32) Buffer + sizeof (EFI_HOB_GUID_TYPE)), BlockSize - sizeof (EFI_HOB_GUID_TYPE));
  return EFI_SUCCESS;
}

#ifdef BDAT_SUPPORT
/**
  Finds the BDAT Schema List HOB if it exists.  If it does not exist, creates it

  @param[in]  Inputs            - Pointer to the MRC Input data structure
  @param[out] BdatSchemaListHob - Pointer to Schema List Hob, by reference

  @retval EFI_SUCCESS - Hob was successfully found or built.
  @retval Others      - Error occurred while creating or finding the Hob.
**/
EFI_STATUS
MrcGetBdatSchemaListHob (
  OUT      MRC_BDAT_SCHEMA_LIST_HOB  **BdatSchemaListHob
  )
{
  CONST EFI_GUID           SchemaListGuid = gMrcSchemaListHobGuid;
  EFI_STATUS               Status;
  MRC_BDAT_SCHEMA_LIST_HOB *Buffer;

  Status = EFI_SUCCESS;
  Buffer = (MRC_BDAT_SCHEMA_LIST_HOB *) GetFirstGuidHob (&SchemaListGuid);

  if (Buffer != NULL) {
    DEBUG ((DEBUG_INFO, "BDAT Schema List HOB already exists\n"));
    *BdatSchemaListHob = Buffer;
  } else {
    DEBUG ((DEBUG_INFO, "Creating BDAT Schema List HOB: "));
    Status = MrcGetHobForDataStorage (
               (VOID **) &Buffer,
               sizeof (MRC_BDAT_SCHEMA_LIST_HOB),
               (EFI_GUID*)&SchemaListGuid
               );
    DEBUG ((DEBUG_INFO, "%r\n", Status));
    if (!EFI_ERROR (Status)) {
      *BdatSchemaListHob = Buffer;
    }
  }

  return Status;
}
#endif


/**
  Determines whether or not the platform has executed a TXT launch by
  examining the TPM Establishment bit.

  @param[in] VOID

  @retval TRUE        - If the TPM establishment bit is asserted.
  @retval FALSE       - If the TPM establishment bit is unasserted.
**/
BOOLEAN
IsEstablishmentBitAsserted (
  VOID
  )
{
  UINT8             Access;
  UINT16            TimeOutCount;

  //
  // Set TPM.ACCESS polling timeout about 750ms.
  //
  TimeOutCount = TPM_TIME_OUT;
  do {
    //
    // Read TPM status register
    //
    Access = MmioRead8 (TPM_STATUS_REG_ADDRESS);

    //
    // if TPM.Access == 0xFF, TPM is not present.
    //
    if (Access == 0xFF) {
      return FALSE;
    }
    //
    // Check tpmRegValidSts bit before checking establishment bit.
    //
    if ((Access & 0x80) == 0x80) {
      //
      // tpmRegValidSts set, we can check establishment bit now.
      //
      break;
    } else {
      //
      // Delay 1ms
      //
      MicroSecondDelay (1000);
    }

    TimeOutCount--;
  } while (TimeOutCount != 0);

  //
  // ValidSts is not set.
  //
  if ((Access & 0x80) != 0x80) {
    return FALSE;
  }
  //
  // The bit we're interested in uses negative logic:
  // If bit 0 == 1 then return False,
  // Else return True.
  //
  return (BOOLEAN) ((Access & 0x1) ? FALSE : TRUE);
}

/**
  Unlock memory when security is set and TxT is not enabled.

  @param[in] MrcData     - Mrc global data.
**/
void
UnlockMemory (
  IN CONST MrcParameters    *CONST  MrcData
  )
{
  EFI_CPUID_REGISTER Reg;
  UINT32             Data32;
  const MrcInput     *Inputs;
  MRC_FUNCTION       *MrcCall;
  UINT64             LtLockSts;

  Inputs = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;

  Data32 = 0;

  AsmCpuid (
      CPUID_VERSION_INFO,
      &Reg.RegEax,
      &Reg.RegEbx,
      &Reg.RegEcx,
      &Reg.RegEdx
      );
  if ((Reg.RegEcx & BIT6)) {
    DEBUG ((DEBUG_INFO, "Processor supports TXT\n"));

    Data32 = CheckSmxCapabilities();

    if (Data32 & BIT0) {
      DEBUG ((DEBUG_INFO, "Platform / PCH supports TXT\n"));
      LtLockSts = MrcCall->MrcReadMsr64 (MSR_LT_LOCK_MEMORY);
      if ((LtLockSts & (B_MSR_LT_LOCK_MEMORY_MEM_LOCK_DEV | B_MSR_LT_LOCK_MEMORY_MEM_LOCK_CPU)) == 0) {
        return;
      }

      if (!(IsEstablishmentBitAsserted ())) {
        DEBUG ((DEBUG_INFO, "Unlock memory\n"));
        MrcCall->MrcWriteMsr64 (MSR_LT_UNLOCK_MEMORY, 0);
      }
    } else {
      DEBUG ((DEBUG_INFO, "Platform / PCH does not support TxT\n"));
    }
  } else {
    DEBUG ((DEBUG_INFO, "Processor does not support TxT\n"));
  }

  // Detect if we are running under Simics - Inputs->SimicsFlag is not ready yet at this point
  Data32 = MmioRead32 ((UINT32) PcdGet64 (PcdSiPciExpressBaseAddress) + 0xFC);
  if ((Data32 & 0xFF) != 0x04) {
    LtLockSts = MrcCall->MrcReadMsr64 (MSR_LT_LOCK_MEMORY);
    if ((LtLockSts & (B_MSR_LT_LOCK_MEMORY_MEM_LOCK_DEV | B_MSR_LT_LOCK_MEMORY_MEM_LOCK_CPU)) != 0) {
      DEBUG ((DEBUG_ERROR, "%a Memory is still locked!\n", gErrString));
      ASSERT (FALSE);
    }
  }
}

/**
  This function calls into TxT ACHECK if platform is TxT enabled.
**/
void
MrcTxtAcheck (
  VOID
  )
{
  AliasCheck ();
}

/**
  Determine whether a cold reset of the platform is required.
  Note that the memory configuration saved data must be valid.

  @param[in] MrcData             - The MRC "global data" area.
  @param[in] MemConfig           - MEMORY_CONFIGURATION structure.
  @param[in] MrcBootMode         - Current MRC boot mode.

  @retval TRUE if cold reset is required, otherwise returns FALSE.
**/
BOOLEAN
ColdBootRequired (
  IN const MrcParameters *const MrcData,
  IN MEMORY_CONFIGURATION       *MemConfig,
  IN MRC_BOOT_MODE              MrcBootMode
  )
{
  const MrcInput       *Inputs;
  const MrcSaveData    *SaveData;
  MrcVersion           Version;
  UINT32               CurrentCrc;

  Inputs    = &MrcData->Inputs;
  SaveData  = &MrcData->Save.Data;

  MrcVersionGet (MrcData, &Version);
  if ((Version.Major != SaveData->Version.Major) ||
      (Version.Minor != SaveData->Version.Minor) ||
      (Version.Rev   != SaveData->Version.Rev)   ||
      (Version.Build != SaveData->Version.Build)) {
    DEBUG ((
      DEBUG_INFO,
      "MRC change detected, prev. ver. %d.%d.%d.%d, curr. ver. %d.%d.%d.%d\n",
      SaveData->Version.Major,
      SaveData->Version.Minor,
      SaveData->Version.Rev,
      SaveData->Version.Build,
      Version.Major,
      Version.Minor,
      Version.Rev,
      Version.Build
      ));
    return TRUE;
  }
  if ((Inputs->CpuModel != SaveData->CpuModel) || (Inputs->CpuStepping != SaveData->CpuStepping)) {
    DEBUG ((
      DEBUG_INFO,
      "CPU change detected, prev. CPU %x.%x, curr. CPU %x.%x\n",
      SaveData->CpuModel,
      SaveData->CpuStepping,
      Inputs->CpuModel,
      Inputs->CpuStepping
      ));
    return TRUE;
  }
  if (MrcBootMode != bmS3) {
    CurrentCrc   = MrcCalculateCrc32 ((UINT8 *) MemConfig, sizeof (MEMORY_CONFIGURATION));
    if (CurrentCrc != SaveData->SaMemCfgCrc) {
      DEBUG ((
        DEBUG_INFO,
        "System Agent input parameter change detected, prev. CRC %xh, curr. CRC %xh.\n",
        SaveData->SaMemCfgCrc,
        CurrentCrc
        ));

      CurrentCrc = MrcCalculateCrc32 ((UINT8 *) MemConfig, sizeof (MEMORY_CONFIGURATION));
      if (CurrentCrc == SaveData->SaMemCfgCrc) {
        DEBUG ((DEBUG_INFO, "Only SerialDebug option changed, no need to retrain\n"));
        return FALSE;
      }
      return TRUE;
    }
  }
  return FALSE;
}

/**
  Set up the MRC OEM data structure.

  @param[in, out] MrcData             - Pointer to the MRC global data structure.
  @param[in]      MemConfig           - MEMORY_CONFIGURATION structure.
  @param[in]      MemConfigNoCrc      - MEMORY_CONFIG_NO_CRC  structure.
**/
void
MrcSetupOem (
  IN OUT MrcParameters          *CONST MrcData,
  IN    MEMORY_CONFIGURATION    *MemConfig,
  IN    MEMORY_CONFIG_NO_CRC    *MemConfigNoCrc
  )
{
  SA_FUNCTION_CALLS    *SaCall;
  SA_MEMORY_FUNCTIONS  *MemCall;
  MrcInput             *Inputs;
  MRC_FUNCTION         *MrcCall;

  SaCall         = &MemConfigNoCrc->SaCall;
  MemCall        = &MemConfigNoCrc->MrcCall;
  Inputs         = &MrcData->Inputs;
  MrcCall        = Inputs->Call.Func;

  MrcGetCoreFunction (
    MrcData,
    (UINT32 *) &MemCall->MrcChannelExist,
    (UINT32 *) &MemCall->MrcPrintf,
    (UINT32 *) &MemCall->MrcChangeMargin,
    (UINT32 *) &MemCall->MrcSignExtend,
    (UINT32 *) &MemCall->ShiftPiCommandTrain,
    (UINT32 *) &MemCall->MrcUpdateVref
  );


  Inputs->PciIndex               = MemConfig->PciIndex;
  Inputs->PciData                = MemConfig->PciData;
  Inputs->CpuidModel             = GetCpuFamily();
  Inputs->CpuidStepping          = GetCpuStepping();

#if 1
  ((MRC_MEMORY_COPY) (SaCall->CopyMem)) ((UINT8 *) MrcCall, (UINT8 *) SaCall, sizeof (SA_FUNCTION_CALLS));
  MrcCall->MrcSetLockPrmrr         = (MRC_SET_LOCK_PRMRR) (&SetCorePrmrr);
  MrcCall->MrcSetGfxMemMap         = (MRC_SET_GFX_MEM_MAP) (&SetGfxMemMap);
#else
  MrcCall->MrcIoRead8              = (MRC_IO_READ_8) (SaCall->IoRead8);
  MrcCall->MrcIoRead16             = (MRC_IO_READ_16) (SaCall->IoRead16);
  MrcCall->MrcIoRead32             = (MRC_IO_READ_32) (SaCall->IoRead32);
  MrcCall->MrcIoWrite8             = (MRC_IO_WRITE_8) (SaCall->IoWrite8);
  MrcCall->MrcIoWrite16            = (MRC_IO_WRITE_16) (SaCall->IoWrite16);
  MrcCall->MrcIoWrite32            = (MRC_IO_WRITE_32) (SaCall->IoWrite32);
  MrcCall->MrcMmioRead8            = (MRC_MMIO_READ_8) (SaCall->MmioRead8);
  MrcCall->MrcMmioRead16           = (MRC_MMIO_READ_16) (SaCall->MmioRead16);
  MrcCall->MrcMmioRead32           = (MRC_MMIO_READ_32) (SaCall->MmioRead32);
  MrcCall->MrcMmioRead64           = (MRC_MMIO_READ_64) (SaCall->MmioRead64);
  MrcCall->MrcMmioWrite8           = (MRC_MMIO_WRITE_8) (SaCall->MmioWrite8);
  MrcCall->MrcMmioWrite16          = (MRC_MMIO_WRITE_16) (SaCall->MmioWrite16);
  MrcCall->MrcMmioWrite32          = (MRC_MMIO_WRITE_32) (SaCall->MmioWrite32);
  MrcCall->MrcMmioWrite64          = (MRC_MMIO_WRITE_64) (SaCall->MmioWrite64);
  MrcCall->MrcSmbusRead8           = (MRC_SMBUS_READ_8) (SaCall->SmbusRead8);
  MrcCall->MrcSmbusRead16          = (MRC_SMBUS_READ_16) (SaCall->SmbusRead16);
  MrcCall->MrcSmbusWrite8          = (MRC_SMBUS_WRITE_8) (SaCall->SmbusWrite8);
  MrcCall->MrcSmbusWrite16         = (MRC_SMBUS_WRITE_16) (SaCall->SmbusWrite16);
  MrcCall->MrcGetPciDeviceAddress  = (MRC_GET_PCI_DEVICE_ADDRESS) (SaCall->GetPciDeviceAddress);
  MrcCall->MrcGetPcieDeviceAddress = (MRC_GET_PCIE_DEVICE_ADDRESS) (SaCall->GetPcieDeviceAddress);
  MrcCall->MrcGetRtcTime           = (MRC_GET_RTC_TIME) (SaCall->GetRtcTime);
  MrcCall->MrcGetCpuTime           = (MRC_GET_CPU_TIME) (SaCall->GetCpuTime);
  MrcCall->MrcCopyMem              = (MRC_MEMORY_COPY) (SaCall->CopyMem);
  MrcCall->MrcSetMem               = (MRC_MEMORY_SET_BYTE) (SaCall->SetMem);
  MrcCall->MrcSetMemWord           = (MRC_MEMORY_SET_WORD) (SaCall->SetMemWord);
  MrcCall->MrcSetMemDword          = (MRC_MEMORY_SET_DWORD) (SaCall->SetMemDword);
  MrcCall->MrcLeftShift64          = (MRC_LEFT_SHIFT_64) (SaCall->LeftShift64);
  MrcCall->MrcRightShift64         = (MRC_RIGHT_SHIFT_64) (SaCall->RightShift64);
  MrcCall->MrcMultU64x32           = (MRC_MULT_U64_U32) (SaCall->MultU64x32);
  MrcCall->MrcDivU64x64            = (MRC_DIV_U64_U64) (SaCall->DivU64x64);
  MrcCall->MrcGetSpdData           = (MRC_GET_SPD_DATA) (SaCall->GetSpdData);
  MrcCall->MrcGetRandomNumber      = (MRC_GET_RANDOM_NUMBER) (SaCall->GetRandomNumber);
  MrcCall->MrcCpuMailboxRead       = (MRC_CPU_MAILBOX_READ) (SaCall->CpuMailboxRead);
  MrcCall->MrcCpuMailboxWrite      = (MRC_CPU_MAILBOX_WRITE) (SaCall->CpuMailboxWrite);
  MrcCall->MrcGetMemoryVdd         = (MRC_GET_MEMORY_VDD) (SaCall->GetMemoryVdd);
  MrcCall->MrcSetMemoryVdd         = (MRC_SET_MEMORY_VDD) (SaCall->SetMemoryVdd);
  MrcCall->MrcCheckpoint           = (MRC_CHECKPOINT) (SaCall->CheckPoint);
  MrcCall->MrcDebugHook            = (MRC_DEBUG_HOOK) (SaCall->DebugHook);
  MrcCall->MrcPrintString          = (MRC_PRINT_STRING) (SaCall->DebugPrint);
  MrcCall->MrcMsrRead64            = (MRC_MSR_READ_64) (SaCall->ReadMsr64);
  MrcCall->MrcMsrWrite64           = (MRC_MSR_WRITE_64) (SaCall->WriteMsr64);
#endif

  MrcCall->MrcTxtAcheck            = (MRC_TXT_ACHECK) MrcTxtAcheck;
  MrcCall->MrcClearSecretsBit      = (MRC_TXT_CLEAR_SECRETS_BIT) (&ClearSecretsBit);
  MrcCall->MrcSetPowerDownRequest  = (MRC_TXT_SET_POWER_DOWN_REQUEST) (&SetPowerDownRequest);

  return;
}

/**
  Set up the MRC input data structure.

  @param[in]  SysBootMode         - Boot mode of the system.
  @param[in]  BootMode            - Boot mode of the MRC.
  @param[in]  MrcData             - Pointer to the MRC global data structure
  @param[in]  MiscPeiPreMemConfig - SA_MISC_PEI_PREMEM_CONFIG structure.
  @param[in]  GtConfig            - GRAPHICS_PEI_PREMEM_CONFIG structure.
  @param[in]  MemConfig           - MEMORY_CONFIGURATION structure.
  @param[in]  MemConfigNoCrc      - MEMORY_CONFIG_NO_CRC structure.
  @param[in]  SiPreMemPolicyPpi   - The SI Pre-Mem Policy PPI instance.
  @param[in]  CpuModel            - CPU Type.

  @retval  Updated MRC_BOOT_MODE
**/
MRC_BOOT_MODE
MrcSetupMrcData (
  IN CONST EFI_BOOT_MODE              SysBootMode,
  IN CONST MRC_BOOT_MODE              BootMode,
  OUT      MrcParameters              *CONST MrcData,
  IN       SA_MISC_PEI_PREMEM_CONFIG  *MiscPeiPreMemConfig,
  IN       GRAPHICS_PEI_PREMEM_CONFIG *GtConfig,
  IN       MEMORY_CONFIGURATION       *CONST MemConfig,
  IN       MEMORY_CONFIG_NO_CRC       *CONST MemConfigNoCrc,
  IN       SI_PREMEM_POLICY_PPI       *CONST SiPreMemPolicyPpi,
  IN       CPU_FAMILY                 CpuModel
  )
{
  MrcInput                            *Inputs;
  MRC_FUNCTION                        *MrcCall;
  MrcControllerIn                     *ControllerIn;
  MrcChannelIn                        *ChannelIn;
  MrcDimmSts                          Status;
  UINT8                               Dimm;
  MrcDimmIn                           *DimmIn;
  UINT8                               Index;
  BOOLEAN                             UlxUlt;
  BOOLEAN                             Ddr4;
  UINT8                               Controller;
  UINT8                               Channel;
  UINT32                              DmiBar;
  UINT32                              PsmiRegionSize;
  PCIE_CR_OPIO_RX_DLL_GLOBAL3_STRUCT  RxDllGlobal3;
  PCU_CR_PLATFORM_INFO_STRUCT         PlatformInfoMsr;
  CPU_SECURITY_PREMEM_CONFIG          *CpuSecurityPreMemConfig;
  PRAM_PREMEM_CONFIG                  *PramPreMemConfig;
  UINT32                              Data32;
  UINT32                              Offset;
  CAPID0_C_0_0_0_PCI_STRUCT           Capid0C;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Status  = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuSecurityPreMemConfigGuid, (VOID *) &CpuSecurityPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status  = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gPramPreMemConfigGuid, (VOID *) &PramPreMemConfig);
  ASSERT_EFI_ERROR (Status);



  //
  // Synchronize the MRC input policies to the SA MEMORY_CONFIGURATION structure.
  //
  MrcCall->MrcCopyMem ((UINT8 *) Inputs, (UINT8 *) MemConfig, sizeof (MEMORY_CONFIGURATION));

  Inputs->SaMemCfgAddress.Ptr = MemConfig;
  Inputs->SaMemCfgSize        = sizeof (MEMORY_CONFIGURATION);
  Status                      = DIMM_NOT_PRESENT;
  UlxUlt                      = (Inputs->CpuModel == cmICL_ULX_ULT);

  //
  // Force standard profile when system boot mode indicates. Usually means some has cleared CMOS.
  //
  if (SysBootMode == BOOT_WITH_DEFAULT_SETTINGS) {
    Inputs->MemoryProfile  = STD_PROFILE;
    Inputs->RefClk         = 0;
    Inputs->Ratio          = 0;
    Inputs->VddVoltage     = VDD_INVALID;
  }

  //
  // Setup the base addresses.
  //
  Inputs->MchBarBaseAddress = MiscPeiPreMemConfig->MchBar;
  Inputs->SmbusBaseAddress  = MiscPeiPreMemConfig->SmbusBar;

  //
  // MMIO size in MB units (below 4GB)
  //
  Inputs->MmioSize = MiscPeiPreMemConfig->MmioSize;

  //
  // DDR maximum frequency
  //
  Inputs->FreqMax = MemConfig->DdrFreqLimit;

  //
  // TSEG Size in MB units and size must be power of 2, ex., 4MB, 8MB, 16M, 32MB.
  //
  Inputs->TsegSize = GetPowerOfTwo32 (MiscPeiPreMemConfig->TsegSize) >> 20;

  //
  // Prmrr size is in MB units
  //
  if (CpuSecurityPreMemConfig != NULL) {
    Inputs->PrmrrSize = (CpuSecurityPreMemConfig->PrmrrSize) >> 20;
  }

  //
  // Pram size is in MB units
  //
  if (PramPreMemConfig != NULL) {
    switch (PramPreMemConfig->PramSize) {
      case 0x31: //4MB
        Inputs->PramSize = 0x400000 >> 20;
        break;

      case 0x32: //16MB
        Inputs->PramSize = 0x1000000 >> 20;
        break;

      case 0x33: //64MB
        Inputs->PramSize = 0x4000000 >> 20;
        break;

      default:
        Inputs->PramSize = 0;
        break;
    }
  }


  //
  // Psmi region size in MB units
  //
  if (GtConfig->GtPsmiSupport == 1) {
    PsmiRegionSize = 32 + 256 * GtConfig->PsmiRegionSize;
    Inputs->GtPsmiRegionSize = MIN (PsmiRegionSize, 1024);
  }

  //
  // Graphics Stolen Size
  // Graphics Stolen size above 64MB has a granularity of 32MB increments
  // GMS values below 240 correspond to Sizes 32 * GSMValue
  // Graphics Stolen size below 64MB has a higher granularity and can be set in 4MB increments
  // GMS values ranging from 240-254 correspond to sizes 4MB to 60MB (excluding 32MB) which is 4*(GSMValue-239)
  //
  Inputs->GraphicsGttSize            = (1 << GtConfig->GttSize);

  if (GtConfig->IgdDvmt50PreAlloc < 240) {
    Inputs->GraphicsStolenSize           = 32 * GtConfig->IgdDvmt50PreAlloc;
  } else {
    Inputs->GraphicsStolenSize           = 4 * (GtConfig->IgdDvmt50PreAlloc - 239);
  }
  Inputs->GfxIsVersatileAcceleration = FALSE;

  // Get BoardType (see MrcBoardType enum)
  Inputs->BoardType = MiscPeiPreMemConfig->UserBd;

  //
  // Get VccIO value:
  // SKL ULT/ULX: 0.85v/0.95v, according to PCIE_CR_OPIO_RX_DLL_GLOBAL3[31:30]
  // SKL DT/Halo: 0.95v always
  //
  Inputs->VccIomV = 950;
  if (UlxUlt) {
    DmiBar = (MmioRead32 (Inputs->PciEBaseAddress + DMIBAR_0_0_0_PCI_REG)) & ~BIT0;
    RxDllGlobal3.Data = MmioRead32 (DmiBar + PCIE_CR_OPIO_RX_DLL_GLOBAL3_DMIBAR_REG);
    if (RxDllGlobal3.Bits.select_vccio_level == 0) {
      Inputs->VccIomV = 850;
    }
  }

  //
  // Options for training steps
  //
  Inputs->TrainingEnables.WRDSUDT     = (UlxUlt) ? 0 : 1;
  // Inputs->MrcSafeConfig = FALSE;             // Relax turnaround value, disable power down, weaklock, scrambler etc.
DEBUG_CODE_BEGIN();
  Inputs->TrainingEnables.RMT         = 1;      // Enable RMT in debug build regardless of the setup option
  //Inputs->RmtPerTask                  = FALSE;  // Run RMT after major training steps
  //Inputs->TrainTrace                  = FALSE;  // Prints the trained state after major training steps
DEBUG_CODE_END();
  Inputs->TrainingEnables2.PERIODICDCC = 0;

  Inputs->BClkFrequency = (MemConfig->BClkFrequency < (BCLK_DEFAULT - (10 * 1000 * 1000))) ?
    BCLK_DEFAULT : ((MemConfig->BClkFrequency / 1000000) * 1000000);

  PlatformInfoMsr.Data = MrcCall->MrcReadMsr64 (PCU_CR_PLATFORM_INFO);
  Inputs->TscTimeBase       = (Inputs->BClkFrequency / 1000 / 1000) * PlatformInfoMsr.Bits.MAX_NON_TURBO_LIM_RATIO; // In microsec

  Inputs->LockPTMregs       = (MiscPeiPreMemConfig->LockPTMregs == 0) ? 0 : 1;
  Inputs->BdatEnable        = (BOOLEAN) (MiscPeiPreMemConfig->BdatEnable);
  Inputs->BdatTestType      = MiscPeiPreMemConfig->BdatTestType;
  Inputs->VttCompForVsshi   = 1;
  Inputs->PchStepping       = PchStepping();

  // Select which pin is connected to CKE[1] for DDR4
  // 0 - xxDDR0_CKE_D4r1_LPechAr1 (CKE0/1 have shared delay)
  // 1 - xxDDR0_CKE_D4r1_LPechBr1 (CKE0/1 have separate delay)
  Inputs->SeparateCkeDelayDdr4 = 1;

  // LPDDR4: Bitmask of ranks that have CA bus terminated. Rank0 is terminating and Rank1 is non-terminating
  Inputs->CmdRanksTerminated = 0x01;

  Inputs->CleanMemory = MemConfigNoCrc->CleanMemory;
  Inputs->SerialDebugLevel = MemConfigNoCrc->SerialDebugLevel;

  // Detect if we are running under Simics
  Data32 = MrcCall->MrcMmioRead32 (Inputs->PciEBaseAddress + 0xFC);
  if ((Data32 & 0xFF) == 0x04) {
    DEBUG ((DEBUG_INFO, "Simics detected (0x%08X)\n", Data32));
    Inputs->SimicsFlag = 1;
  }

  if (!Inputs->SimicsFlag) {
    Inputs->SaGv = (UlxUlt && (Inputs->CpuStepping == csIclA0))  ? MrcSaGvDisabled : MemConfig->SaGv;
  } else {
    Inputs->SaGv =  MrcSaGvDisabled;
  }

  if (!UlxUlt && (Inputs->CpuStepping >= csIclG0)) {
  Offset       = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, CAPID0_C_0_0_0_PCI_REG);
  Capid0C.Data = MrcCall->MrcMmioRead32 (Offset);
    if (Capid0C.Bits.SPARE_14) {
      Inputs->SaGv  = MrcSaGvDisabled;
    }
  }

/*
  Inputs->DdrSpeedControl     = 1;     // 0 = Auto, 1 = Manual control over DDR frequency and Gear
  Inputs->FreqSaGvLow         = 2133;  // SA GV: 0 is Auto, otherwise holds the frequency value.
  Inputs->FreqSaGvMid         = 2400;  // SA GV: 0 is Auto, otherwise holds the frequency value.
  Inputs->FreqMax             = 1867;
  Inputs->SaGvLowGear2  = 1;
  Inputs->SaGvMidGear2  = 1;
  Inputs->SaGvHighGear2 = 0;
*/
  Inputs->Lp4Npath  = FALSE;
  Inputs->LpFreqSwitch    = TRUE;
  Inputs->Mars            = TRUE;
  Inputs->DqBitDccRerunInWrTPbd   = TRUE;
  Inputs->TxtClean                = IsTxtSecretsSet();
  Inputs->Ibecc              = MemConfig->Ibecc;
  Inputs->IbeccParity        = MemConfig->IbeccParity;
  Inputs->IbeccOperationMode = MemConfig->IbeccOperationMode;
  for (Index = 0; Index < MAX_IBECC_REGIONS; Index++) {
    Inputs->IbeccProtectedRegionEnable[Index]    = MemConfig->IbeccProtectedRegionEnable[Index];
    Inputs->IbeccProtectedRegionBase[Index]      = MemConfig->IbeccProtectedRegionBase[Index];
    Inputs->IbeccProtectedRegionMask[Index]      = MemConfig->IbeccProtectedRegionMask[Index];
  }

  if (UlxUlt && (Inputs->CpuStepping == csIclA0)) {
    Inputs->PerBankRefresh  = FALSE;
  }

  //
  // Initialize the board-specific RCOMP values
  //
  MrcCall->MrcCopyMem ((UINT8 *) Inputs->RcompResistor, (UINT8 *) MemConfigNoCrc->RcompData->RcompResistor, sizeof (Inputs->RcompResistor));
  MrcCall->MrcCopyMem ((UINT8 *) Inputs->RcompTarget,   (UINT8 *) MemConfigNoCrc->RcompData->RcompTarget,   sizeof (Inputs->RcompTarget));

  Ddr4 = FALSE;
  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerIn = &Inputs->Controller[Controller];
    ControllerIn->ChannelCount = 0;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelIn = &ControllerIn->Channel[Channel];
      {
        //
        // Decide which channels and DIMMs are enabled.
        //
        switch (MemConfig->DisableDimmChannel[Channel]) {
          case 1:
            ChannelIn->Dimm[0].Status = DIMM_DISABLED;
            ChannelIn->Dimm[1].Status = DIMM_ENABLED;
            ChannelIn->Status         = CHANNEL_PRESENT;
            ControllerIn->ChannelCount++;
            ChannelIn->DimmCount      = 1;
            break;
          case 2:
            ChannelIn->Dimm[0].Status = DIMM_ENABLED;
            ChannelIn->Dimm[1].Status = DIMM_DISABLED;
            ChannelIn->Status         = CHANNEL_PRESENT;
            ControllerIn->ChannelCount++;
            ChannelIn->DimmCount      = 1;
            break;
          case 3:
            ChannelIn->Dimm[0].Status = DIMM_DISABLED;
            ChannelIn->Dimm[1].Status = DIMM_DISABLED;
            ChannelIn->Status         = CHANNEL_DISABLED;
            ChannelIn->DimmCount      = 0;
            break;
          default:
            ChannelIn->Dimm[0].Status = DIMM_ENABLED;
            ChannelIn->Dimm[1].Status = DIMM_ENABLED;
            ChannelIn->Status         = CHANNEL_PRESENT;
            ControllerIn->ChannelCount++;
            ChannelIn->DimmCount      = 2;
            break;
        }
      }
      //
      // DQ byte mapping to CMD/CTL/CLK
      //
      MrcCall->MrcCopyMem ((UINT8 *) ChannelIn->DQByteMap, (UINT8 *) MemConfigNoCrc->DqByteMap->DqByteMap[Channel], sizeof (ChannelIn->DQByteMap));
      MrcCall->MrcCopyMem ((UINT8 *) ChannelIn->DqsMapCpu2Dram, (UINT8 *) MemConfigNoCrc->DqsMap->DqsMapCpu2Dram[Channel], sizeof (ChannelIn->DqsMapCpu2Dram));
      //
      // Get DIMM SpdBaseAddresses.
      //
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        DimmIn = &ChannelIn->Dimm[Dimm];
        Index  = (Channel * MAX_DIMMS_IN_CHANNEL) + Dimm;
        DimmIn->SpdAddress = MiscPeiPreMemConfig->SpdAddressTable[Index];
        MrcCall->MrcCopyMem ((UINT8 *) &DimmIn->Spd.MrcSpdString[0], (UINT8 *) MrcSpdStringConst, sizeof (DimmIn->Spd.MrcSpdString));
        ZeroMem (&DimmIn->Spd.Data, sizeof (MrcSpd));
        DimmIn->Spd.Flag.Bit.DimmNumber    = Dimm;
        DimmIn->Spd.Flag.Bit.ChannelNumber = Channel;
        DimmIn->Spd.Flag.Bit.MdSocket      = (DimmIn->SpdAddress > 0) ? 1 : 0;
        DEBUG ((DEBUG_INFO, "Spd Address for Channel %d Dimm %d: %x\n", Channel, Dimm, DimmIn->SpdAddress));
        if ((DIMM_ENABLED == DimmIn->Status) || (DIMM_DISABLED == DimmIn->Status)) {
          if (DimmIn->SpdAddress > 0) {
            if ((bmCold == BootMode) || (bmFast == BootMode)) {
              MrcCall->MrcGetSpdData (BootMode, DimmIn->SpdAddress, (UINT8 *) &DimmIn->Spd.Data,(UINT8 *) NULL, 0, (UINT8 *) &MrcSpdDdr4Table, sizeof (MrcSpdDdr4Table), (UINT8 *) &MrcSpdLpddrTable, sizeof (MrcSpdLpddrTable));
            }
          } else {
            MrcCall->MrcCopyMem ((UINT8 *) &DimmIn->Spd.Data, (UINT8 *) &MemConfigNoCrc->SpdData->SpdData[Channel][Dimm][0], sizeof (MrcSpd));
          }
        }
        if ((BootMode == bmCold) || (BootMode == bmFast)) {
          // The dram device type is at the same SPD offset for all types, and we read this offset on both Cold and Fast flows
          if (DimmIn->Spd.Data.Ddr4.Base.DramDeviceType.Bits.Type == MRC_SPD_DDR4_SDRAM_TYPE_NUMBER) {
            Ddr4 = TRUE;
          }
        } else { // Warm or S3 Resume - we don't read SPD, get DDR typa from MrcSave
          Ddr4 = (MrcData->Save.Data.DdrType == MRC_DDR_TYPE_DDR4);
        }
      } // for Dimm
    } // for Channel
  } // for Controller

  // Disable SAGV on DDR4, if DdrSpeedControl is Auto
  if (Ddr4 && (Inputs->DdrSpeedControl == 0) && UlxUlt && (Inputs->CpuStepping == csIclC0)) {
    DEBUG ((DEBUG_ERROR, "DDR4 detected on C-step: disable SAGV\n"));
    Inputs->SaGv = MrcSaGvDisabled;
  }

  CheckForTimingOverride (Inputs, MemConfig);

  switch (BootMode) {
    case bmWarm:
    case bmS3:
    case bmFast:
      return BootMode;

    default:
      DEBUG ((DEBUG_ERROR, "ERROR: Invalid flow specified, defaulting to cold flow\n"));
      // No break. Note that the boot mode changes to bmCold.
    case bmCold:
      break;
  }
  return bmCold;
}

/**
  Check to see if user defined profile is selected and if it is, then copy the
  timing settings for this profile to the timing override structure. If user
  defined profile is not selected, then set the timing override structure to 0.

  @note Even though we set timings on a DIMM by DIMM basis, the controller
  may force DIMM timings to be the same for all DIMMs in a channel.

  @param[in, out] Inputs              - The MRC Input data structure.
  @param[in]      MemConfig           - MEMORY_CONFIGURATION structure.
**/
void
CheckForTimingOverride (
  IN OUT MrcInput *const          Inputs,
  IN     MEMORY_CONFIGURATION     *MemConfig
  )
{
  MrcControllerIn             *ControllerIn;
  MrcChannelIn                *ChannelIn;
  MrcTiming                   *Timing;
  UINT8                       Controller;
  UINT8                       Channel;
  UINT8                       Dimm;

  //
  // Override DIMM timing settings for customer profile setting.
  //
  if (Inputs->MemoryProfile == USER_PROFILE) {
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn = &Inputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn = &ControllerIn->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          Timing = &ChannelIn->Dimm[Dimm].Timing;
          Timing->NMode   = MemConfig->NModeSupport;
          Timing->tCL     = MemConfig->tCL;
          Timing->tCWL    = MemConfig->tCWL;
          Timing->tFAW    = MemConfig->tFAW;
          Timing->tRAS    = MemConfig->tRAS;
          Timing->tRCDtRP = MemConfig->tRCDtRP;
          Timing->tREFI   = MemConfig->tREFI;
          Timing->tRFC    = MemConfig->tRFC;
          Timing->tRRD    = MemConfig->tRRD;
          Timing->tRTP    = MemConfig->tRTP;
          Timing->tWR     = MemConfig->tWR;
          Timing->tWTR    = MemConfig->tWTR;
        }
      }
    }
  }

  return;
}


/**
  Build S3 memory data HOB

  @param[in] MrcData          Pointer to Mrc Parameters
**/
VOID
BuildMemoryS3DataHob (
  IN MrcParameters            *MrcData
  )
{
  VOID *HobPtr;

  HobPtr = NULL;

  DEBUG ((
          DEBUG_INFO,
          "BuildMemoryS3DataHob.\nMemoryS3DataHob Base : %x\nMemoryS3DataHob Size : %x\n",
          &MrcData->Save,
          (UINTN) MrcData->Save.Size
          ));

  HobPtr = BuildGuidDataHob (
             &gSiMemoryS3DataGuid,
             (VOID *)&(MrcData->Save),
             (UINTN) MrcData->Save.Size
           );
  ASSERT (HobPtr != NULL);
}

/**
  Build SMBIOS and OC memory data HOB

  @param[in] MrcData          Pointer to Mrc Parameters
**/
VOID
BuildMemoryInfoDataHob (
  IN MrcParameters            *MrcData
  )
{
  MEMORY_INFO_DATA_HOB *MemoryInfo;
  CONTROLLER_INFO      *ControllerInfo;
  CHANNEL_INFO         *ChannelInfo;
  DIMM_INFO            *DimmInfo;
  MRC_FUNCTION         *MrcCall;
  MrcInput             *Inputs;
  MrcSaveData          *SaveData;
  MrcContSave          *ControllerSave;
  MrcChannelSave       *ChannelSave;
  MrcDimmSave          *DimmSave;
  MrcOutput            *Outputs;
  MrcControllerOut     *ControllerOut;
  MrcChannelOut        *ChannelOut;
  MrcDimmOut           *DimmOut;
  MrcProfile           Profile;
  UINT8                Controller;
  UINT8                Channel;
  UINT8                Dimm;
  UINT8                PartNumberOffset;
  UINT8                ModulePartLength;

  SaveData = &MrcData->Save.Data;
  Outputs  = &MrcData->Outputs;
  Inputs   = &MrcData->Inputs;
  MrcCall  = Inputs->Call.Func;

  DEBUG ((DEBUG_INFO, "BuildMemoryInfoDataHob.\n"));

  //
  // Build HOB for MemoryInfoData
  //
  MemoryInfo = BuildGuidHob (
                 &gSiMemoryInfoDataGuid,
                 sizeof (MEMORY_INFO_DATA_HOB)
                 );
  ASSERT (MemoryInfo != NULL);
  if (MemoryInfo == NULL) {
    return;
  }
  ZeroMem ((VOID *) MemoryInfo, sizeof (MEMORY_INFO_DATA_HOB));

  MrcVersionGet (MrcData, (MrcVersion *) &MemoryInfo->Version);
  MemoryInfo->Revision                   = 0x02;
  MemoryInfo->MemoryType                 = Outputs->DdrType;
  MemoryInfo->ConfiguredMemoryClockSpeed = (UINT16) MAX (SaveData->Frequency, SaveData->FreqSaGvMid);
  MemoryInfo->ConfiguredMemoryClockSpeed = (UINT16) MAX (MemoryInfo->ConfiguredMemoryClockSpeed, SaveData->FreqSaGvLow);
  MemoryInfo->MaximumMemoryClockSpeed    = (UINT16) Outputs->FreqMax;
  if (Outputs->EccSupport) {
    MemoryInfo->ErrorCorrectionType = MemoryErrorCorrectionSingleBitEcc;
  } else {
    MemoryInfo->ErrorCorrectionType = MemoryErrorCorrectionNone;
  }
  MemoryInfo->EccSupport              = Outputs->EccSupport;
  MemoryInfo->TotalPhysicalMemorySize = Outputs->MemoryMapData.TotalPhysicalMemorySize;

  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    MemoryInfo->VddVoltage[Profile]   = Outputs->VddVoltage[Profile];
  }

  MemoryInfo->MemoryProfile = Inputs->MemoryProfile;

  MemoryInfo->XmpProfileEnable = SaveData->XmpProfileEnable;
  MemoryInfo->Ratio            = SaveData->Ratio;
  MemoryInfo->RefClk           = SaveData->RefClk;

  PartNumberOffset = sizeof (SPD_MANUFACTURER_ID_CODE) + sizeof (SPD_MANUFACTURING_LOCATION) + sizeof (SPD_MANUFACTURING_DATE) + sizeof (SPD_MANUFACTURER_SERIAL_NUMBER);
  if (MrcData->Outputs.DdrType != MRC_DDR_TYPE_DDR4) {
    PartNumberOffset +=2; //Skip 2 bytes (CRC) to align the PartNumberOffset for DDR3
  }

  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerSave               = &SaveData->Controller[Controller];
    ControllerOut                = &Outputs->Controller[Controller];
    ControllerInfo               = &MemoryInfo->Controller[Controller];
    ControllerInfo->Status       = ControllerSave->Status;
    ControllerInfo->DeviceId     = ControllerOut->DeviceId;
    ControllerInfo->RevisionId   = ControllerOut->RevisionId;
    ControllerInfo->ChannelCount = ControllerSave->ChannelCount;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelSave                   = &ControllerSave->Channel[Channel];
      ChannelOut                    = &ControllerOut->Channel[Channel];
      ChannelInfo                   = &ControllerInfo->ChannelInfo[Channel];
      ChannelInfo->Status           = ChannelSave->Status;
      ChannelInfo->ChannelId        = Channel;
      ChannelInfo->DimmCount        = (UINT8) ChannelSave->DimmCount;
      for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
        MrcCall->MrcCopyMem ((UINT8 *) &ChannelInfo->Timing[Profile], (UINT8 *) &ChannelSave->Timing[Profile], sizeof (MrcTiming));
      }
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        DimmSave = &ChannelSave->DimmSave[Dimm];
        DimmOut  = &ChannelOut->Dimm[Dimm];
        DimmInfo = &ChannelInfo->DimmInfo[Dimm];
        DimmInfo->Status = DimmOut->Status;
        DimmInfo->DimmId = Dimm;
        DimmInfo->DimmCapacity = DimmOut->DimmCapacity;
        // Copy the SPD before DIMM_PRESENT check, to show Vendor ID in Setup also for disabled DIMMs
        MrcCall->MrcCopyMem (&DimmInfo->SpdSave[0], &DimmSave->SpdSave[0], sizeof (DimmInfo->SpdSave));
        if ((DimmInfo->Status == DIMM_PRESENT) && (DimmInfo->DimmCapacity > 0)) {
          DimmInfo->RankInDimm = DimmOut->RankInDimm;
          DimmInfo->MfgId = ((DimmSave->SpdSave[1] << 8) |
                             (DimmSave->SpdSave[0]));
          MrcCall->MrcCopyMem ((UINT8 *) &DimmInfo->ModulePartNum[0],
                               (UINT8 *) &DimmSave->SpdSave[PartNumberOffset],
                               sizeof (SPD4_MODULE_PART_NUMBER));
          DimmInfo->SpdDramDeviceType       = DimmSave->SpdDramDeviceType;
          DimmInfo->SpdModuleType           = DimmSave->SpdModuleType;
          DimmInfo->SpdModuleMemoryBusWidth = DimmSave->SpdModuleMemoryBusWidth;
          DimmInfo->Speed = (UINT16) DimmOut->Speed;
          ///
          /// Dimm is present in slot
          /// Get the Memory DataWidth info
          /// SPD Offset 8 Bits [2:0] DataWidth aka Primary Bus Width
          ///
          MemoryInfo->DataWidth = 8 * (1 << (DimmInfo->SpdModuleMemoryBusWidth & 0x07));
          DEBUG ((DEBUG_INFO, "Manufacturer Id of Channel %x Dimm %x is : 0x%x \n", Channel, Dimm, DimmInfo->MfgId));
          DEBUG ((DEBUG_INFO, "Module Part Number of Channel %x Dimm %x is : ", Channel, Dimm));
          for (ModulePartLength = 0; ModulePartLength < sizeof (SPD4_MODULE_PART_NUMBER); ModulePartLength++) {
            DEBUG ((DEBUG_INFO, "%x ", DimmInfo->ModulePartNum[ModulePartLength]));
          }
          DEBUG ((DEBUG_INFO, "\n"));
        }
      }
    }
  }
}

/**
  Build platform memory data HOB

  @param[in]      MrcData             Pointer to Mrc Parameters
  @param[in, out] MemoryPlatformData  Hob to pass memory data for platform code
**/
VOID
BuildMemoryPlatformDataHob (
  IN     MrcParameters            *MrcData,
  IN OUT MEMORY_PLATFORM_DATA_HOB *MemoryPlatformData
  )
{
  MrcInput      *Inputs;
  MrcOutput     *Outputs;
  MrcMemoryMap  *MemoryMapData;

  Outputs = &MrcData->Outputs;
  Inputs  = &MrcData->Inputs;
  MemoryMapData = &Outputs->MemoryMapData;

  DEBUG ((DEBUG_INFO, "BuildMemoryPlatformDataHob.\n"));
  MemoryPlatformData->Data.Revision        = 0x02;
  MemoryPlatformData->Data.BootMode        = Inputs->BootMode;
  MemoryPlatformData->Data.TsegSize        = Inputs->TsegSize;
  MemoryPlatformData->Data.TsegBase        = MemoryMapData->TsegBase;
  MemoryPlatformData->Data.PrmrrSize       = Inputs->PrmrrSize;
  MemoryPlatformData->Data.PrmrrBase       = MemoryMapData->PrmrrBase;
  MemoryPlatformData->Data.PramSize        = Inputs->PramSize;
  MemoryPlatformData->Data.PramBase        = MemoryMapData->PramBase;
  MemoryPlatformData->Data.GttBase         = MemoryMapData->GttBase;
  MemoryPlatformData->Data.MmioSize        = Inputs->MmioSize;
  MemoryPlatformData->Data.PciEBaseAddress = Inputs->PciEBaseAddress;
}

#ifdef FSP_FLAG
/**
  Build a Hob for storaging memory usage information, including
  EfiMemoryTop, EfiMemoryBottom, EfiFreeMemoryTop, EfiFreeMemoryBottom
  and FreeMemory.

  @retval  EFI_SUCCESS           The Hob created successfully.
  @retval  EFI_OUT_OF_RESOURCES  There are not enough resources to build Hob.
**/
EFI_STATUS
BuildHobUsageDataHob (
  VOID
  )
{
  EFI_PEI_HOB_POINTERS   HobPtr;
  HOB_USAGE_DATA_HOB     *HobUsageDataHobPtr;

  HobUsageDataHobPtr = NULL;

  DEBUG ((DEBUG_INFO, "BuildHobUsageDataHob.\n"));

  HobPtr.Raw = GetHobList ();
  //
  // Build Hob for storaging memory usage information
  //
  HobUsageDataHobPtr = (HOB_USAGE_DATA_HOB *) BuildGuidHob (&gHobUsageDataGuid, sizeof (HOB_USAGE_DATA_HOB));
  ASSERT (HobUsageDataHobPtr != NULL);
  if (HobUsageDataHobPtr == NULL) {
    DEBUG ((DEBUG_ERROR, "Build HobUsageDataHob failed!\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  HobUsageDataHobPtr->EfiMemoryTop        = HobPtr.HandoffInformationTable->EfiMemoryTop;
  HobUsageDataHobPtr->EfiMemoryBottom     = HobPtr.HandoffInformationTable->EfiMemoryBottom;
  HobUsageDataHobPtr->EfiFreeMemoryTop    = HobPtr.HandoffInformationTable->EfiFreeMemoryTop;
  HobUsageDataHobPtr->EfiFreeMemoryBottom = HobPtr.HandoffInformationTable->EfiFreeMemoryBottom;
  HobUsageDataHobPtr->FreeMemory          = (UINTN)(HobPtr.HandoffInformationTable->EfiFreeMemoryTop -
                                                    HobPtr.HandoffInformationTable->EfiFreeMemoryBottom);

  return EFI_SUCCESS;
}
#endif // FSP_FLAG


BOOLEAN
IsThisPowerOfTwo (
  UINT32 num
  )
{
  return (num != 0) && ((num & (num - 1)) == 0);
}

UINT32
RoundToNextPow2 (
  UINT32 num) {
  num--;
  num |= num >> 1;
  num |= num >> 2;
  num |= num >> 4;
  num |= num >> 8;
  num |= num >> 16;
  num++;

  return num;
}

