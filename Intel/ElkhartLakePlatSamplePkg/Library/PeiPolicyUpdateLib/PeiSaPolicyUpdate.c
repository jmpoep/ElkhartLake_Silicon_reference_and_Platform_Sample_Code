/** @file
Do Platform Stage System Agent initialization.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2020 Intel Corporation.

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

#include <Library/PeiSaPolicyUpdate.h>
#include <Library/SiPolicyLib.h>
#include <Protocol/GraphicsOutput.h>
#include <IndustryStandard/Bmp.h>
#include <Guid/MemoryTypeInformation.h>
#include <Library/HobLib.h>
#include <CpuPcieHob.h>
#include <Platform.h>
#include <Ppi/FirmwareVolume.h>
#include <Pi/PiFirmwareFile.h>
#include <Pi/PiPeiCis.h>
#include <Core/Pei/PeiMain.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PeiSaPolicyLib.h>
#include <CpuPcieRpConfig.h>
#include <Library/CpuPcieInfoLib.h>
#if FixedPcdGet8(PcdFspModeSelection) == 1
#include <FspsUpd.h>
#endif

//@todo Port this table for CPU PCIE
GLOBAL_REMOVE_IF_UNREFERENCED CPU_PCIE_DEVICE_OVERRIDE mCpuPcieDeviceTable[] = {
  { 0 }
};

/**
  UpdatePeiSaPolicy performs SA PEI Policy initialization

  @retval EFI_SUCCESS              The policy is installed and initialized.
**/
EFI_STATUS
EFIAPI
UpdatePeiSaPolicy (
  VOID
  )
{
  EFI_GUID                        BmpImageGuid;
  EFI_STATUS                      Status;
  EFI_STATUS                      Status2;
  SETUP_DATA                      SetupData;
  EFI_GUID                        FileGuid;
  SA_SETUP                        SaSetup;
  UINTN                           VarSize;
  VOID                            *Buffer;
  UINT32                          Size;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices;
  EFI_BOOT_MODE                   BootMode;
  PCH_SETUP                       PchSetup;
  UINT8                           SaDisplayConfigTable[13] = {0};
#if FixedPcdGet8(PcdFspModeSelection) == 1
  VOID                            *MemBuffer;
  VOID                            *FspsUpd;
  BMP_IMAGE_HEADER                *BmpHeader;
  UINT64                          BltBufferSize;
#else
  SI_POLICY_PPI                   *SiPolicyPpi;
  GRAPHICS_PEI_CONFIG             *GtConfig;
  GNA_CONFIG                      *GnaConfig;
  SA_MISC_PEI_CONFIG              *MiscPeiConfig;

#endif

  EFI_PEI_PPI_DESCRIPTOR           *ReadyForGopConfigPpiDesc;
  VOID                             *VbtPtr;

  DEBUG ((DEBUG_INFO, "Update PeiSaPolicyUpdate Pos-Mem Start\n"));

  Size = 0;
#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspsUpd = NULL;
  MemBuffer = NULL;
  BmpHeader = NULL;
  BltBufferSize = 0;
#else
  GtConfig              = NULL;
  SiPolicyPpi           = NULL;
  GnaConfig             = NULL;

#endif


#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspsUpd = (FSPS_UPD *) PcdGet32 (PcdFspsUpdDataAddress);
  ASSERT (FspsUpd != NULL);
#else
  Status = PeiServicesLocatePpi (&gSiPolicyPpiGuid, 0, NULL, (VOID **) &SiPolicyPpi);
  ASSERT_EFI_ERROR (Status);


  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gGraphicsPeiConfigGuid, (VOID *) &GtConfig);
  ASSERT_EFI_ERROR(Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gGnaConfigGuid, (VOID *) &GnaConfig);
  ASSERT_EFI_ERROR(Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gSaMiscPeiConfigGuid, (VOID *) &MiscPeiConfig);
  ASSERT_EFI_ERROR (Status);


#endif

  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR (Status);

  //
  // Locate system configuration variable
  //
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid, // GUID
             0,                                // INSTANCE
             NULL,                             // EFI_PEI_PPI_DESCRIPTOR
             (VOID **) &VariableServices       // PPI
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
  ASSERT_EFI_ERROR (Status);

  VarSize = sizeof (SETUP_DATA);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               PLATFORM_SETUP_VARIABLE_NAME,
                               &gSetupVariableGuid,
                               NULL,
                               &VarSize,
                               &SetupData
                               );

  VarSize = sizeof (SA_SETUP);
  Status2 = VariableServices->GetVariable(
                                VariableServices,
                                L"SaSetup",
                                &gSaSetupVariableGuid,
                                NULL,
                                &VarSize,
                                &SaSetup
                                );
  ASSERT_EFI_ERROR(Status2);

  if (SaSetup.VbtSelect == VBT_SELECT_MIPI) {
    //CopyMem(&BmpImageGuid, PcdGetPtr(PcdVbtMipiGuid), sizeof(BmpImageGuid));
  } else {
    CopyMem(&BmpImageGuid, PcdGetPtr(PcdIntelGraphicsVbtFileGuid), sizeof(BmpImageGuid));
  }

  if (!EFI_ERROR (Status)) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PavpEnable,             GtConfig->PavpEnable,          SaSetup.PavpEnable);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.CdClock,                GtConfig->CdClock,             SaSetup.CdClock);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PeiGraphicsPeimInit,    GtConfig->PeiGraphicsPeimInit, SaSetup.PeiGraphicsPeimInit);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.GtFreqMax,              GtConfig->GtFreqMax,           SaSetup.GtFreqMax);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.DisableTurboGt,         GtConfig->DisableTurboGt,      SaSetup.DisableTurboGt);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.CdynmaxClampEnable,     GtConfig->CdynmaxClampEnable,  SaSetup.CdynmaxClampEnable);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SkipCdClockInit,        GtConfig->SkipCdClockInit,     SaSetup.SkipCdClockInit);

    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.RenderStandby,          GtConfig->RenderStandby,       SaSetup.EnableRenderStandby);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PmSupport,              GtConfig->PmSupport,           SaSetup.PmSupport);

    if (SaSetup.PeiGraphicsPeimInit == 1) {
      Buffer = NULL;

      CopyMem(&FileGuid, &BmpImageGuid, sizeof(FileGuid));
      PeiGetSectionFromFv(FileGuid, &Buffer, &Size);
      if (Buffer == NULL) {
        DEBUG((DEBUG_ERROR, "Could not locate VBT\n"));
      }

      if (BootMode == BOOT_ON_S3_RESUME) {
#if FixedPcdGet8(PcdFspModeSelection) == 1
        UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.GraphicsConfigPtr, GtConfig->GraphicsConfigPtr, 0);
#else
        UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.GraphicsConfigPtr, GtConfig->GraphicsConfigPtr, NULL);
#endif
      } else {
#if FixedPcdGet8(PcdFspModeSelection) == 1
        if (Buffer != NULL) {
          MemBuffer = (VOID *) AllocatePages (EFI_SIZE_TO_PAGES ((UINTN)Size));
          if (MemBuffer != NULL) {
            CopyMem (MemBuffer, (VOID *)Buffer, (UINTN)Size);
            ((FSPS_UPD *) FspsUpd)->FspsConfig.GraphicsConfigPtr = (UINT32) MemBuffer;
          } else {
            DEBUG ((DEBUG_WARN, "Error in locating / copying VBT.\n"));
            ((FSPS_UPD *) FspsUpd)->FspsConfig.GraphicsConfigPtr = (UINT32) NULL;
          }
          DEBUG ((DEBUG_INFO, "Vbt Pointer from PeiGetSectionFromFv is 0x%x\n", ((FSPS_UPD *) FspsUpd)->FspsConfig.GraphicsConfigPtr));
        }
#else
        GtConfig->GraphicsConfigPtr = Buffer;
        DEBUG ((DEBUG_INFO, "Vbt Pointer from PeiGetSectionFromFv is 0x%x\n", GtConfig->GraphicsConfigPtr));
#endif
      }
    DEBUG ((DEBUG_INFO, "Vbt Size from PeiGetSectionFromFv is 0x%x\n", Size));
    GET_POLICY ((VOID *) ((FSPS_UPD *) FspsUpd)->FspsConfig.GraphicsConfigPtr, GtConfig->GraphicsConfigPtr, VbtPtr);

      Buffer = NULL;
      PeiGetSectionFromFv (gTianoLogoGuid, &Buffer, &Size);
      if (Buffer == NULL) {
        DEBUG ((DEBUG_WARN, "Could not locate Logo\n"));
      }
#if FixedPcdGet8(PcdFspModeSelection) == 1
      if (Buffer != NULL) {
        MemBuffer = (VOID *) AllocatePages (EFI_SIZE_TO_PAGES ((UINTN) Size));
        if (MemBuffer != NULL) {
          CopyMem (MemBuffer, (VOID *)Buffer, (UINTN)Size);
          ((FSPS_UPD *) FspsUpd)->FspsConfig.LogoPtr  = (UINT32) MemBuffer;
          ((FSPS_UPD *) FspsUpd)->FspsConfig.LogoSize = Size;

          //
          // Calculate the BltBuffer needed size.
          //
          BmpHeader = (BMP_IMAGE_HEADER *) ((FSPS_UPD *) FspsUpd)->FspsConfig.LogoPtr;

          if (BmpHeader->CharB == 'B' && BmpHeader->CharM == 'M') {
            BltBufferSize = MultU64x32 ((UINT64) BmpHeader->PixelWidth, BmpHeader->PixelHeight);
            if (BltBufferSize < DivU64x32 ((UINTN) ~0, sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL))) {
              BltBufferSize = MultU64x32 (BltBufferSize, sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
              ((FSPS_UPD *) FspsUpd)->FspsConfig.BltBufferSize    = (UINT32) BltBufferSize;
              ((FSPS_UPD *) FspsUpd)->FspsConfig.BltBufferAddress = (UINT32) AllocatePages (EFI_SIZE_TO_PAGES ((UINTN)BltBufferSize));
            } else {
              DEBUG ((DEBUG_ERROR, "Blt Buffer Size overflow.\n"));
              ASSERT (FALSE);
            }
          } else {
            DEBUG ((DEBUG_ERROR, "Wrong Bmp Image Header.\n"));
            ASSERT (FALSE);
          }
        }
      } else {
        DEBUG ((DEBUG_WARN, "Error in locating / copying LogoPtr.\n"));
        ((FSPS_UPD *) FspsUpd)->FspsConfig.LogoPtr  = (UINT32) NULL;
        ((FSPS_UPD *) FspsUpd)->FspsConfig.LogoSize = 0;
      }
      DEBUG ((DEBUG_INFO, "LogoPtr from PeiGetSectionFromFv is 0x%x\n", ((FSPS_UPD *) FspsUpd)->FspsConfig.LogoPtr));
      DEBUG ((DEBUG_INFO, "LogoSize from PeiGetSectionFromFv is 0x%x\n", ((FSPS_UPD *) FspsUpd)->FspsConfig.LogoSize));
#else
      GtConfig->LogoPtr  = Buffer;
      GtConfig->LogoSize = Size;
      DEBUG ((DEBUG_INFO, "LogoPtr from PeiGetSectionFromFv is 0x%x\n", GtConfig->LogoPtr));
      DEBUG ((DEBUG_INFO, "LogoSize from PeiGetSectionFromFv is 0x%x\n", GtConfig->LogoSize));
#endif

    //
    // Display DDI Initialization ( default Native GPIO as per board during AUTO case)
    //
    CopyMem (SaDisplayConfigTable, (VOID *) (UINTN) PcdGet32 (PcdSaDisplayConfigTable), (UINTN)PcdGet16 (PcdSaDisplayConfigTableSize));
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.DdiPortAConfig,          GtConfig->DdiConfiguration.DdiPortAConfig,       SaDisplayConfigTable[0]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.DdiPortBConfig,          GtConfig->DdiConfiguration.DdiPortBConfig,       SaDisplayConfigTable[1]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.DdiPortCConfig,          GtConfig->DdiConfiguration.DdiPortCConfig,       SaDisplayConfigTable[2]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.DdiPortAHpd,             GtConfig->DdiConfiguration.DdiPortAHpd,          SaDisplayConfigTable[3]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.DdiPortBHpd,             GtConfig->DdiConfiguration.DdiPortBHpd,          SaDisplayConfigTable[4]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.DdiPortCHpd,             GtConfig->DdiConfiguration.DdiPortCHpd,          SaDisplayConfigTable[5]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.DdiPort1Hpd,             GtConfig->DdiConfiguration.DdiPort1Hpd,          SaDisplayConfigTable[6]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.DdiPort2Hpd,             GtConfig->DdiConfiguration.DdiPort2Hpd,          SaDisplayConfigTable[7]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.DdiPort3Hpd,             GtConfig->DdiConfiguration.DdiPort3Hpd,          SaDisplayConfigTable[8]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.DdiPort4Hpd,             GtConfig->DdiConfiguration.DdiPort4Hpd,          SaDisplayConfigTable[9]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.DdiPortADdc,             GtConfig->DdiConfiguration.DdiPortADdc,          SaDisplayConfigTable[10]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.DdiPortBDdc,             GtConfig->DdiConfiguration.DdiPortBDdc,          SaDisplayConfigTable[11]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.DdiPortCDdc,             GtConfig->DdiConfiguration.DdiPortCDdc,          SaDisplayConfigTable[12]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.DdiPort1Ddc,             GtConfig->DdiConfiguration.DdiPort1Ddc,          SaDisplayConfigTable[13]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.DdiPort2Ddc,             GtConfig->DdiConfiguration.DdiPort2Ddc,          SaDisplayConfigTable[14]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.DdiPort3Ddc,             GtConfig->DdiConfiguration.DdiPort3Ddc,          SaDisplayConfigTable[15]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.DdiPort4Ddc,             GtConfig->DdiConfiguration.DdiPort4Ddc,          SaDisplayConfigTable[16]);

      //
      // Install ReadyForGopConfig PPI to trigger PEI phase GopConfig callback.
      //
      ReadyForGopConfigPpiDesc = (EFI_PEI_PPI_DESCRIPTOR *) AllocateZeroPool (sizeof (EFI_PEI_PPI_DESCRIPTOR));
      if (ReadyForGopConfigPpiDesc == NULL) {
        ASSERT (FALSE);
        return EFI_OUT_OF_RESOURCES;
      }
      ReadyForGopConfigPpiDesc->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
      ReadyForGopConfigPpiDesc->Guid  = &gReadyForGopConfigPpiGuid;
      ReadyForGopConfigPpiDesc->Ppi   = VbtPtr;
      Status = PeiServicesInstallPpi (ReadyForGopConfigPpiDesc);
    }

    //
    // Initialize GNA Configuration
    //
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.GnaEnable, GnaConfig->GnaEnable,   SaSetup.GnaEnable);
    //
    // Initialize Misc SA Configuration
    //
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.EdramTestMode, MiscPeiConfig->EdramTestMode, SaSetup.EdramTestMode);
  }
  return EFI_SUCCESS;
}

/**
  PeiGetSectionFromFv finds the file in FV and gets file Address and Size

  @param[in] NameGuid              - File GUID
  @param[out] Address              - Pointer to the File Address
  @param[out] Size                 - Pointer to File Size

  @retval EFI_SUCCESS                Successfull in reading the section from FV
  @retval EFI_NOT_FOUND              File not found
**/
EFI_STATUS
EFIAPI
PeiGetSectionFromFv (
  IN CONST  EFI_GUID        NameGuid,
  OUT VOID                  **Address,
  OUT UINT32                *Size
  )
{
  EFI_STATUS                           Status;
  EFI_PEI_FIRMWARE_VOLUME_PPI          *FvPpi;
  EFI_FV_FILE_INFO                     FvFileInfo;
  PEI_CORE_FV_HANDLE                   *CoreFvHandle;
  EFI_PEI_FILE_HANDLE                  VbtFileHandle;
  EFI_GUID                             *VbtGuid;
  EFI_COMMON_SECTION_HEADER            *Section;
  EFI_HOB_GUID_TYPE                    *GuidHob;
  VOID                                 *HobData;

  Status = PeiServicesLocatePpi(
             &gEfiFirmwareFileSystem2Guid,
             0,
             NULL,
             (VOID **)&FvPpi
             );
  ASSERT_EFI_ERROR(Status);

  GuidHob = GetFirstGuidHob (&gPlatformInitFvLocationGuid);
  if (GuidHob != NULL) {
    HobData = *(VOID **)GET_GUID_HOB_DATA(GuidHob);
    CoreFvHandle = (PEI_CORE_FV_HANDLE *) HobData;

    //
    // VBT typically resides in current FV or previous FV, so searching both of them.
    //
    Status = FvPpi->FindFileByName (FvPpi, &NameGuid, &CoreFvHandle->FvHandle, &VbtFileHandle);

    if (!EFI_ERROR(Status) && VbtFileHandle != NULL) {

      DEBUG((DEBUG_INFO, "Find SectionByType \n"));

      Status = FvPpi->FindSectionByType(FvPpi, EFI_SECTION_RAW, VbtFileHandle, (VOID **)&VbtGuid);
      if (!EFI_ERROR(Status)) {

        DEBUG((DEBUG_INFO, "GetFileInfo \n"));

        Status = FvPpi->GetFileInfo(FvPpi, VbtFileHandle, &FvFileInfo);
        Section = (EFI_COMMON_SECTION_HEADER *)FvFileInfo.Buffer;

        if (IS_SECTION2(Section)) {
          ASSERT(SECTION2_SIZE(Section) > 0x00FFFFFF);
          *Size = SECTION2_SIZE(Section) - sizeof (EFI_COMMON_SECTION_HEADER2);
          *Address = ((UINT8 *)Section + sizeof (EFI_COMMON_SECTION_HEADER2));
        } else {
          *Size = SECTION_SIZE(Section) - sizeof (EFI_COMMON_SECTION_HEADER);
          *Address = ((UINT8 *)Section + sizeof (EFI_COMMON_SECTION_HEADER));
        }
        return EFI_SUCCESS;
      }
    }
  }
  return EFI_NOT_FOUND;
}
