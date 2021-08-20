/** @file
  Advanced ACPI Driver

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2020 Intel Corporation.

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
#include <Base.h>
#include <Uefi.h>
#include <Library/HobLib.h>
#include <Guid/HobList.h>
#include <Protocol/FirmwareVolume2.h>
#include <PlatformBoardId.h>
#include <IndustryStandard/AcpiAml.h>
#include <IndustryStandard/Pci30.h>
#include "AcpiPlatform.h"
#include <Library/PciSegmentLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PchPcieRpLib.h>
#include <Library/SerialIoAccessLib.h>
#include <Library/GpioLib.h>
#include <Library/EspiLib.h>
#include <Library/GbeLib.h>
#include <Library/HdaLib.h>
#include <Library/TccLib.h>
#include <Library/DxeInstallNhltTableLib.h>
#include <MeBiosPayloadHob.h>
#include <PlatformBoardConfig.h>
#include <Library/CpuPlatformLib.h>
#include <PlatformBoardType.h>
#include <PlatformInfo.h>
#include <Guid/S3MemoryVariable.h>
#include <Protocol/VariableLock.h>
#include <Mcfg.h>
#if FixedPcdGetBool(PcdITbtEnable) == 1
#include <TcssDataHob.h>
#endif
#include <Library/IpuLib.h>
#include <Library/SataLib.h>
#include <Register/IgdRegs.h>
#include "GenSsdtLib.h"


#include <Acpi/AcpiTables/Pram/Pram.h>
#include <MemInfoHob.h>

#if (FixedPcdGetBool(PcdS5ChargingEnable) == 1)
#include "PupdrDxe.h"
#endif

#include <Library/TsnLib.h>
#include <Library/PchPseIoLib.h>
#include <Library/PreSiliconEnvDetectLib.h>

//
// Global variables
//
GLOBAL_REMOVE_IF_UNREFERENCED VOID                                      *mGfxNvsAddress;
GLOBAL_REMOVE_IF_UNREFERENCED ME_SETUP                                  mMeSetup;
GLOBAL_REMOVE_IF_UNREFERENCED PCH_SETUP                                 mPchSetup;
GLOBAL_REMOVE_IF_UNREFERENCED SETUP_DATA                                mSystemConfiguration;
GLOBAL_REMOVE_IF_UNREFERENCED PLATFORM_NVS_AREA_PROTOCOL                mPlatformNvsAreaProtocol;

GLOBAL_REMOVE_IF_UNREFERENCED EFI_CPU_IO2_PROTOCOL                      *mCpuIo;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_CPU_ID_ORDER_MAP                      mCpuApicIdOrderTable[MAX_CPU_NUM];
GLOBAL_REMOVE_IF_UNREFERENCED EFI_CPU_APIC_ID_REORDER_MAP               mCpuApicIdReorderTable[MAX_CPU_NUM];

GLOBAL_REMOVE_IF_UNREFERENCED EFI_CPU_PACKAGE_INFO                      mSbspPackageInfo;
#if FixedPcdGetBool(PcdITbtEnable) == 1
GLOBAL_REMOVE_IF_UNREFERENCED TCSS_DATA_HOB                             *mTcssHob;
#endif

EFI_ACPI_PTCT_TABLE            *mPtct;

//
// Function implementations
//

/**
  Install NHLT ACPI Table
**/
VOID
InstallNhltAcpiTable (
  VOID
  )
{
  EFI_STATUS              Status;
  HDA_NHLT_CONFIG         NhltConfig;

  if (mPchSetup.PchHdAudioDmicLinkEnable[0] || mPchSetup.PchHdAudioDmicLinkEnable[1]) {
    NhltConfig.DspEndpointDmic      = mPchSetup.PchHdAudioNhltEndpointDmic;
  } else {
    NhltConfig.DspEndpointDmic      = 0;
  }

  if (mPchSetup.PchHdAudioLinkMode == HDAUDIO_LINK_MODE_I2S_SSP ||
      mPchSetup.PchHdAudioSspLinkEnable[0] ||
      mPchSetup.PchHdAudioSspLinkEnable[1] ||
      mPchSetup.PchHdAudioSspLinkEnable[2] ||
      mPchSetup.PchHdAudioSspLinkEnable[3] ||
      mPchSetup.PchHdAudioSspLinkEnable[4] ||
      mPchSetup.PchHdAudioSspLinkEnable[5]) {
    NhltConfig.DspEndpointI2s       = mPchSetup.PchHdAudioNhltEndpointI2s;
  } else {
    NhltConfig.DspEndpointI2s       = 0;
  }

  NhltConfig.DspEndpointBluetooth = mPchSetup.PchHdAudioNhltEndpointBluetooth;
  NhltConfig.DspExternalTable     = mPchSetup.PchHdAudioNhltExternalTable;

  Status = NhltPublishAcpiTable (&NhltConfig);
  ASSERT_EFI_ERROR (Status);
}

/**
  Install Xhci ACPI Table
**/
VOID
InstallXhciAcpiTable (
  VOID
  )
{
  EFI_STATUS                    Status;
  EFI_FIRMWARE_VOLUME2_PROTOCOL *FwVol;
  EFI_ACPI_COMMON_HEADER        *CurrentTable;
  UINT32                        FvStatus;
  UINTN                         Size;
  UINTN                         TableHandle;
  INTN                          Instance;
  EFI_ACPI_TABLE_PROTOCOL       *AcpiTable;
  EFI_ACPI_DESCRIPTION_HEADER   *TableHeader;
  EFI_GUID                      EfiAcpiMultiTableStorageGuid;

  EfiAcpiMultiTableStorageGuid = gEfiAcpiTableStorageGuid;
  Instance      = 0;
  TableHandle   = 0;
  CurrentTable  = NULL;
  FwVol         = NULL;

  DEBUG ((DEBUG_INFO, "InstallXhciAcpiTable\n"));
  //
  // Update OEM table ID
  //
  if (PcdGet64 (PcdXhciAcpiTableSignature) == 0) {
    DEBUG ((DEBUG_INFO, "InstallXhciAcpiTable: Cannot find PcdXhciAcpiTableSignature\n"));
    return;
  }

  //
  // Find the AcpiSupport protocol
  //
  Status = LocateSupportProtocol (
            &gEfiAcpiTableProtocolGuid,
            EfiAcpiMultiTableStorageGuid,
            (VOID **) &AcpiTable,
            FALSE
            );
  ASSERT_EFI_ERROR (Status);

  //
  // Locate the firmware volume protocol
  //
  Status = LocateSupportProtocol (
            &gEfiFirmwareVolume2ProtocolGuid,
            EfiAcpiMultiTableStorageGuid,
            (VOID **) &FwVol,
            TRUE
            );

  //
  // Read tables from the storage file.
  //
  while (Status == EFI_SUCCESS) {
    Status = FwVol->ReadSection (
                      FwVol,
                      &EfiAcpiMultiTableStorageGuid,
                      EFI_SECTION_RAW,
                      Instance,
                      (VOID **) &CurrentTable,
                      &Size,
                      &FvStatus
                      );

    if (!EFI_ERROR (Status)) {

      TableHeader = (EFI_ACPI_DESCRIPTION_HEADER *) CurrentTable;

      if (TableHeader->OemTableId == PcdGet64 (PcdXhciAcpiTableSignature)) {
        DEBUG ((DEBUG_INFO, "Install xhci table: %x\n", TableHeader->OemTableId));
        //
        // Add the table
        //
        TableHandle = 0;

        Status = AcpiTable->InstallAcpiTable (
                              AcpiTable,
                              CurrentTable,
                              CurrentTable->Length,
                              &TableHandle
                              );

        break;
      }

      //
      // Increment the instance
      //
      Instance++;
      gBS->FreePool (CurrentTable);
      CurrentTable = NULL;
    }
  }

  if (CurrentTable != NULL) {
    gBS->FreePool (CurrentTable);
    CurrentTable = NULL;
  }
}

VOID
PublishOverClockingAcpiTable (
  VOID
  )
{
  EFI_STATUS                    Status;
  EFI_HANDLE                    *HandleBuffer;
  UINTN                         NumberOfHandles;
  UINTN                         Index;
  EFI_FIRMWARE_VOLUME2_PROTOCOL *FwVol;
  EFI_ACPI_TABLE_PROTOCOL       *AcpiTable;
  EFI_ACPI_COMMON_HEADER        *Table;
  UINTN                         Size;
  UINT32                        FvStatus;
  EFI_ACPI_DESCRIPTION_HEADER   *TableHeader;
  UINTN                         TableHandle;

  FwVol = NULL;
  Table = NULL;

  DEBUG ((DEBUG_INFO, "PublishOverClockingAcpiTable\n"));

  //
  // Locate FV protocol.
  //
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiFirmwareVolume2ProtocolGuid,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Look for FV with ACPI storage file
  //
  for (Index = 0; Index < NumberOfHandles; Index++) {

    //
    // Get the protocol on this handle
    // This should not fail because of LocateHandleBuffer
    //
    Status = gBS->HandleProtocol (
                  HandleBuffer[Index],
                  &gEfiFirmwareVolume2ProtocolGuid,
                  (VOID **) &FwVol
                  );
    ASSERT_EFI_ERROR (Status);

    //
    // See if it has the OverClocking Acpi Table file
    //
    Status = FwVol->ReadSection (
                      FwVol,
                      &gOcAcpiTableStorageGuid,
                      EFI_SECTION_RAW,
                      0,
                      (VOID **) &Table,
                      &Size,
                      &FvStatus
                      );
    if (!EFI_ERROR (Status)) {
      break;
    }
  }
  //
  // Free any allocated buffers
  //
  FreePool (HandleBuffer);

  //
  // Not find the table, it's fine the over clocking support is not enabled
  //
  if (Table == NULL) {
    return;
  }

  Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, (VOID **) &AcpiTable);

  TableHeader = (EFI_ACPI_DESCRIPTION_HEADER *) Table;
  if (CompareMem (&TableHeader->OemTableId, "PerfTune", 8) == 0) {
    TableHandle = 0;
    Status = AcpiTable->InstallAcpiTable (
                          AcpiTable,
                          Table,
                          Table->Length,
                          &TableHandle
                          );
  }

  if (Table != NULL) {
    gBS->FreePool (Table);
    Table = NULL;
  }

}

/**
  Locate the first instance of a protocol.  If the protocol requested is an
  FV protocol, then it will return the first FV that contains the ACPI table
  storage file.

  @param[in] Protocol           The protocol to find.
  @param[in] Instance           Return pointer to the first instance of the protocol.
  @param[in] Type               TRUE if the desired protocol is a FV protocol.

  @retval EFI_SUCCESS           The function completed successfully.
  @retval EFI_NOT_FOUND         The protocol could not be located.
  @retval EFI_OUT_OF_RESOURCES  There are not enough resources to find the protocol.
**/
EFI_STATUS
LocateSupportProtocol (
  IN     EFI_GUID                      *Protocol,
  IN     EFI_GUID                      gEfiAcpiMultiTableStorageGuid,
     OUT VOID                          **Instance,
  IN     BOOLEAN                       Type
  )
{
  EFI_STATUS              Status;
  EFI_HANDLE              *HandleBuffer;
  UINTN                   NumberOfHandles;
  EFI_FV_FILETYPE         FileType;
  UINT32                  FvStatus;
  EFI_FV_FILE_ATTRIBUTES  Attributes;
  UINTN                   Size;
  UINTN                   Index;

  //
  // Locate protocol.
  //
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  Protocol,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status)) {
    //
    // Defined errors at this time are not found and out of resources.
    //
    return Status;
  }

  //
  // Looking for FV with ACPI storage file
  //
  for (Index = 0; Index < NumberOfHandles; Index++) {

    //
    // Get the protocol on this handle
    // This should not fail because of LocateHandleBuffer
    //
    Status = gBS->HandleProtocol (
                    HandleBuffer[Index],
                    Protocol,
                    Instance
                    );
    ASSERT_EFI_ERROR (Status);

    if (!Type) {

      //
      // Not looking for the FV protocol, so find the first instance of the
      // protocol.  There should not be any errors because our handle buffer
      // should always contain at least one or LocateHandleBuffer would have
      // returned not found.
      //
      break;
    }

    //
    // See if it has the ACPI storage file
    //
    Size      = 0;
    FvStatus  = 0;
    Status = ((EFI_FIRMWARE_VOLUME2_PROTOCOL *) (*Instance))->ReadFile (
                                                              *Instance,
                                                              &gEfiAcpiMultiTableStorageGuid,
                                                              NULL,
                                                              &Size,
                                                              &FileType,
                                                              &Attributes,
                                                              &FvStatus
                                                              );

    //
    // If we found it, then we are done
    //
    if (Status == EFI_SUCCESS) {
      break;
    }
  }

  //
  // Our exit status is determined by the success of the previous operations
  // If the protocol was found, Instance already points to it.
  //
  //
  // Free any allocated buffers
  //
  FreePool (HandleBuffer);

  return Status;
}

/*
  This function will determine whether Native ASPM is supported on the platform.

  @param[in] SystemConfiguration     System configuration data

  @return TRUE if Native ASPM is supported, FALSE otherwise
*/
BOOLEAN
IsNativeAspmSupported (
  CONST SETUP_DATA* SystemConfiguration
  )
{
  if (SystemConfiguration->PciExpNative == 0) {
    return FALSE;
  }
  switch (SystemConfiguration->NativeAspmEnable) {
  case 0:
    return FALSE;
  case 1:
    return TRUE;
  case 2: /* AUTO */
    return PchIsPcieNativeAspmSupported ();
  default:
    ASSERT (0);
  }
  return TRUE;
}

/**
  This function will provide the EC GPE number for ECDT update according to platform design

  @retval EcGpeNumber     EC GPE number to be reported in ECDT
**/
UINT32
GetEcGpeNumber (
  VOID
  )
{
  UINT32                                EcGpeNumber;

  //
  // EC GPE number assignment should be same as Method _GPE under ACPI EC Device which is used for OS without ECDT support
  //
  if (IsEspiEnabled ()) {
    EcGpeNumber = 0x6E;
  } else {
    EcGpeNumber = 23;
    if (mPlatformNvsAreaProtocol.Area->PcdSmcRuntimeSciPin != 0) {
      GpioGetGpeNumber ((GPIO_PAD) mPlatformNvsAreaProtocol.Area->PcdSmcRuntimeSciPin, &EcGpeNumber);
    }
  }

  DEBUG((DEBUG_INFO, "ACPI EcGpeNumber = 0x%x\n ", EcGpeNumber));

  return EcGpeNumber;
}

/**
  This function will update any runtime platform specific information.
  This currently includes:
    Setting OEM table values, ID, table ID, creator ID and creator revision.
    Enabling the proper processor entries in the APIC tables
  It also indicates with which ACPI table version the table belongs.

  @param[in] Table        The table to update
  @param[in] Version      Where to install this table

  @retval EFI_SUCCESS     Updated tables commplete.
**/
EFI_STATUS
PlatformUpdateTables (
  IN OUT EFI_ACPI_COMMON_HEADER       *Table,
  IN OUT EFI_ACPI_TABLE_VERSION       *Version
  )
{
  EFI_ACPI_DESCRIPTION_HEADER                 *TableHeader;
  UINT8                                       *CurrPtr;
  UINT8                                       *TmpDsdtPointer;
  UINT8                                       *EndPtr;
  EFI_ACPI_1_0_PROCESSOR_LOCAL_APIC_STRUCTURE *ApicPtr;
  EFI_STATUS                                  Status;
  EFI_MP_SERVICES_PROTOCOL                    *MpService;
  UINTN                                       NumberOfCPUs;
  UINT8                                       MaximumDsdtPointLength;
  UINTN                                       NumberOfEnabledCPUs;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL             *PciRootBridgeIo;
  UINT32                                      HpetBaseAdress;
  UINT8                                       LocalApicCounter;
  //UINT32                                      GcsRegister;
  UINT32                                      VariableAttributes;
  SA_SETUP                                    SaSetup;
  SA_SETUP                                    SaSetupVarBuffer;
  UINTN                                       VariableSize;
  UINT64                                      PramBaseAddress = 0;
  UINT32                                      PramSize = 0;
  UINT8                                       PramConfigVariable;
  MEMORY_PLATFORM_DATA_HOB                    *MemoryPlatformData;

  CurrPtr                = NULL;
  EndPtr                 = NULL;
  ApicPtr                = NULL;
  MemoryPlatformData     = NULL;
  NumberOfCPUs           = 1;
  LocalApicCounter       = 0;
  MaximumDsdtPointLength = 20;

  //
  // This will be accurate except for FACS structure
  //
  TableHeader = (EFI_ACPI_DESCRIPTION_HEADER *) Table;

  //
  // Update the OEM and creator information for every table except FACS.
  //
  if (Table->Signature != EFI_ACPI_1_0_FIRMWARE_ACPI_CONTROL_STRUCTURE_SIGNATURE) {
    CopyMem (TableHeader->OemId, PcdGetPtr (PcdAcpiDefaultOemId), sizeof (TableHeader->OemId));

    //
    // Skip OEM table ID and creator information for SSDT tables, since these are
    // created by an ASL compiler and the creator information is useful.
    //
    if (Table->Signature != EFI_ACPI_1_0_SECONDARY_SYSTEM_DESCRIPTION_TABLE_SIGNATURE) {
      //
      // Set through patchable PCD value
      //
      TableHeader->OemTableId = PcdGet64 (PcdAcpiDefaultOemTableId);
      TableHeader->OemRevision = PcdGet32(PcdAcpiDefaultOemRevision);

      //
      // Update creator information
      //
       TableHeader->CreatorId        = PcdGet32 (PcdAcpiDefaultCreatorId);
       TableHeader->CreatorRevision  = PcdGet32 (PcdAcpiDefaultCreatorRevision) ;
    }
  }

  //
  // Locate the PCI IO protocol
  //
  Status = gBS->LocateProtocol (
                  &gEfiPciRootBridgeIoProtocolGuid,
                  NULL,
                  (VOID **) &PciRootBridgeIo
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Locate the MP services protocol
  // Find the MP Protocol. This is an MP platform, so MP protocol must be there.
  //
  Status = gBS->LocateProtocol (
                  &gEfiMpServiceProtocolGuid,
                  NULL,
                  (VOID **) &MpService
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Determine the number of processors
  //
  MpService->GetNumberOfProcessors (
               MpService,
               &NumberOfCPUs,
               &NumberOfEnabledCPUs
               );

  //
  // By default, a table belongs in all ACPI table versions published.
  // Some tables will override this because they have different versions of the table.
  //
  *Version = EFI_ACPI_TABLE_VERSION_1_0B | EFI_ACPI_TABLE_VERSION_2_0 | EFI_ACPI_TABLE_VERSION_3_0;

  //
  // Update the various table types with the necessary updates
  //
  switch (Table->Signature) {

  case EFI_ACPI_1_0_APIC_SIGNATURE:
    //
    // if not MP and not APIC then don't publish the APIC tables.
    //
      //@todo mSystemConfiguration.ApicEnabled default value is 1. So, the following logic is not executed.
      //if (mSystemConfiguration.ApicEnabled == 0) {
      //  *Version = EFI_ACPI_TABLE_VERSION_NONE;
      //  break;
      //}
    //
    // Call for Local APIC ID Reorder
    //
    SortCpuLocalApicInTable (
      MpService,
      NumberOfCPUs,
      NumberOfEnabledCPUs
      );

    CurrPtr = (UINT8 *) &((EFI_ACPI_DESCRIPTION_HEADER *) Table)[1];
    CurrPtr = CurrPtr + 8;
    //
    // Size of Local APIC Address & Flag
    //
    EndPtr  = (UINT8 *) Table;
    EndPtr  = EndPtr + Table->Length;

    while (CurrPtr < EndPtr) {
      ApicPtr = (EFI_ACPI_1_0_PROCESSOR_LOCAL_APIC_STRUCTURE *) CurrPtr;

      //
      // Check table entry type
      //
      if (ApicPtr->Type == EFI_ACPI_1_0_PROCESSOR_LOCAL_APIC) {
        AppendCpuMapTableEntry (
          ApicPtr,
          NumberOfCPUs,
          NumberOfEnabledCPUs,
          LocalApicCounter
          );
        LocalApicCounter++;
      }

      //
      // Go to the next structure in the APIC table
      //
      CurrPtr = CurrPtr + ApicPtr->Length;
    }
    break;

  case EFI_ACPI_6_1_FIXED_ACPI_DESCRIPTION_TABLE_SIGNATURE:
    //
    // Fix up all FACP Table values if configuration requires it.
    // This code fixes up the following Table values:
    // (1) C2/C3/CST Enable FACP values
    // (2) RTC S4 Flag
    //
    {
      EFI_ACPI_6_1_FIXED_ACPI_DESCRIPTION_TABLE *FadtPointer;

      FadtPointer = (EFI_ACPI_6_1_FIXED_ACPI_DESCRIPTION_TABLE *) Table;

      //
      // Check the version of the table
      //
      *Version = EFI_ACPI_TABLE_VERSION_NONE;
      if (FadtPointer->Header.Revision == EFI_ACPI_1_0_FIXED_ACPI_DESCRIPTION_TABLE_REVISION) {
        *Version = EFI_ACPI_TABLE_VERSION_NONE;
      } else if (FadtPointer->Header.Revision == EFI_ACPI_2_0_FIXED_ACPI_DESCRIPTION_TABLE_REVISION) {
        *Version = EFI_ACPI_TABLE_VERSION_1_0B | EFI_ACPI_TABLE_VERSION_2_0;
      } else if (FadtPointer->Header.Revision == EFI_ACPI_3_0_FIXED_ACPI_DESCRIPTION_TABLE_REVISION) {
        *Version = EFI_ACPI_TABLE_VERSION_1_0B | EFI_ACPI_TABLE_VERSION_3_0;
      } else if (FadtPointer->Header.Revision == EFI_ACPI_5_0_FIXED_ACPI_DESCRIPTION_TABLE_REVISION) {
        *Version = EFI_ACPI_TABLE_VERSION_1_0B | EFI_ACPI_TABLE_VERSION_5_0;
      } else if (FadtPointer->Header.Revision == EFI_ACPI_6_1_FIXED_ACPI_DESCRIPTION_TABLE_REVISION) {
        *Version = EFI_ACPI_TABLE_VERSION_5_0;
      }

      //
      // Modify MSI capability based on setup
      //
      if (mSystemConfiguration.EnableMsiInFadt == 0) {
        FadtPointer->IaPcBootArch |= (1 << 3);
      }

      //
      // Modify Preferred_PM_Profile field based on Board SKU's. Default is set to Mobile
      //
      FadtPointer->PreferredPmProfile = PcdGet8 (PcdPreferredPmProfile);

      //
      // if Native ASPM is disabled, set FACP table to skip Native ASPM
      //
      if (!IsNativeAspmSupported (&mSystemConfiguration)) {
        FadtPointer->IaPcBootArch |= 0x10;
      }

      //
      // PME WAKE supported, set PCI_EXP_WAK, BIT14 of Fixed feature flags.
      //
      FadtPointer->Flags |= (EFI_ACPI_6_0_PCI_EXP_WAK);
      if (mSystemConfiguration.LowPowerS0Idle) {
        //
        // The Flags field within the FADT (offset 112)
        //   1) will have a new Low Power S0 Idle Capable ACPI flag (bit offset 21).
        //
        FadtPointer->Flags = (BIT21 | FadtPointer->Flags);
        //
        //Only passive docking available in Conected Standby mode. Clear Docking capability Bit
        //
        FadtPointer->Flags &= ~BIT9;
        //
        // set indicates the power button is handled as a control method device.
        //
        FadtPointer->Flags |= EFI_ACPI_2_0_PWR_BUTTON;
      } else {
        FadtPointer->Flags &= ~(EFI_ACPI_2_0_PWR_BUTTON); // clear indicates the power button is handled as a fixed feature programming model
      }

      //
      // 1. set header revision.
      //
      FadtPointer->Header.Revision = EFI_ACPI_6_1_FIXED_ACPI_DESCRIPTION_TABLE_REVISION;

      //
      // 2. set all GAR register AccessSize to valid value.
      //
      ((EFI_ACPI_6_1_FIXED_ACPI_DESCRIPTION_TABLE *)FadtPointer)->ResetReg.AccessSize    = EFI_ACPI_6_1_BYTE;
      ((EFI_ACPI_6_1_FIXED_ACPI_DESCRIPTION_TABLE *)FadtPointer)->XPm1aEvtBlk.AccessSize = EFI_ACPI_6_1_WORD;
      ((EFI_ACPI_6_1_FIXED_ACPI_DESCRIPTION_TABLE *)FadtPointer)->XPm1bEvtBlk.AccessSize = EFI_ACPI_6_1_WORD;
      ((EFI_ACPI_6_1_FIXED_ACPI_DESCRIPTION_TABLE *)FadtPointer)->XPm1aCntBlk.AccessSize = EFI_ACPI_6_1_WORD;
      ((EFI_ACPI_6_1_FIXED_ACPI_DESCRIPTION_TABLE *)FadtPointer)->XPm1bCntBlk.AccessSize = EFI_ACPI_6_1_WORD;
      ((EFI_ACPI_6_1_FIXED_ACPI_DESCRIPTION_TABLE *)FadtPointer)->XPm2CntBlk.AccessSize  = EFI_ACPI_6_1_BYTE;
      ((EFI_ACPI_6_1_FIXED_ACPI_DESCRIPTION_TABLE *)FadtPointer)->XPmTmrBlk.AccessSize   = EFI_ACPI_6_1_DWORD;
      ((EFI_ACPI_6_1_FIXED_ACPI_DESCRIPTION_TABLE *)FadtPointer)->XGpe0Blk.AccessSize    = EFI_ACPI_6_1_BYTE;
      ((EFI_ACPI_6_1_FIXED_ACPI_DESCRIPTION_TABLE *)FadtPointer)->XGpe1Blk.AccessSize    = EFI_ACPI_6_1_BYTE;

      ((EFI_ACPI_6_1_FIXED_ACPI_DESCRIPTION_TABLE *)FadtPointer)->SleepControlReg.AddressSpaceId    = 0x1;
      ((EFI_ACPI_6_1_FIXED_ACPI_DESCRIPTION_TABLE *)FadtPointer)->SleepControlReg.RegisterBitWidth  = 0x8;
      ((EFI_ACPI_6_1_FIXED_ACPI_DESCRIPTION_TABLE *)FadtPointer)->SleepControlReg.RegisterBitOffset = 0;
      ((EFI_ACPI_6_1_FIXED_ACPI_DESCRIPTION_TABLE *)FadtPointer)->SleepControlReg.AccessSize        = EFI_ACPI_6_1_DWORD;
      ((EFI_ACPI_6_1_FIXED_ACPI_DESCRIPTION_TABLE *)FadtPointer)->SleepControlReg.Address           = EFI_ACPI_PM1A_EVT_BLK_ADDRESS + 4;

      ((EFI_ACPI_6_1_FIXED_ACPI_DESCRIPTION_TABLE *)FadtPointer)->SleepStatusReg.AddressSpaceId     = 0x1;
      ((EFI_ACPI_6_1_FIXED_ACPI_DESCRIPTION_TABLE *)FadtPointer)->SleepStatusReg.RegisterBitWidth   = 0x8;
      ((EFI_ACPI_6_1_FIXED_ACPI_DESCRIPTION_TABLE *)FadtPointer)->SleepStatusReg.RegisterBitOffset  = 0;
      ((EFI_ACPI_6_1_FIXED_ACPI_DESCRIPTION_TABLE *)FadtPointer)->SleepStatusReg.AccessSize         = EFI_ACPI_6_1_DWORD;
      ((EFI_ACPI_6_1_FIXED_ACPI_DESCRIPTION_TABLE *)FadtPointer)->SleepStatusReg.Address            = EFI_ACPI_PM1A_EVT_BLK_ADDRESS;

      //
      // Set the S4BiosReq to 0 as we don't support it in the FACS for EHL.
      //
      FadtPointer->S4BiosReq = 0;

      //
      //BIOS should expose either 64 bits or 32 bits address, not both.
      //
      if (FadtPointer->XPm1aEvtBlk.Address != 0) {
        FadtPointer->Pm1aEvtBlk = 0;
        FadtPointer->Pm1aCntBlk = 0;
      }

      if (FadtPointer->XPm2CntBlk.Address != 0) {
        FadtPointer->Pm2CntBlk = 0;
      }

        //@todo RtcS4WakeEnable and PmTimerEnable default value is 1. So, the following logic is not executed.
        ////
        //// Check if RTC S4 is enabled
        ////
        //if (!mSystemConfiguration.RtcS4WakeEnable) {

        //  //
        //  // Clear the S4 RTC flag
        //  //
        //  FadtPointer->Flags &= ~EFI_ACPI_2_0_RTC_S4;
        //}

        ////
        //// Check if PM timer is enabled
        ////
        //if (!mSystemConfiguration.PmTimerEnable) {

        //  //
        //  // Clear the PM timer flag
        //  //
        //  FadtPointer->Flags &= ~EFI_ACPI_3_0_USE_PLATFORM_CLOCK;
        //}
    }
    break;

  case EFI_ACPI_1_0_PERSISTENT_SYSTEM_DESCRIPTION_TABLE_SIGNATURE:
    //
    // These items only belong in the 1.0 tables.
    //
    *Version = EFI_ACPI_TABLE_VERSION_1_0B;
    break;

  case EFI_ACPI_2_0_DIFFERENTIATED_SYSTEM_DESCRIPTION_TABLE_SIGNATURE:
    //
    // Fix up the AML code in the DSDT affected by end user options.
    // Fix up the following ASL Code:
    // (1)  ACPI Global NVS Memory Base and Size.
    // (2)  ACPI Graphics NVS Memory Base and Size.
    // (3)  SMBus I/O Base.
    // (4)  Thermal Management Methods.
    //
    {
      UINT8   *DsdtPointer;
      UINT32  *Signature;
      UINT8   *Operation;
      UINT32  *Address;
      UINT8   *Value;
      UINT16  *Size;
      BOOLEAN EnterDock = FALSE;
      //
      // Loop through the ASL looking for values that we must fix up.
      //
      CurrPtr = (UINT8 *) Table;
      for (DsdtPointer = CurrPtr;
           DsdtPointer < (CurrPtr + ((EFI_ACPI_COMMON_HEADER *) CurrPtr)->Length - sizeof (UINT32));
           DsdtPointer++
          ) {
        Signature = (UINT32 *) DsdtPointer;
        switch (*Signature) {
        //
        // GNVS operation region
        //
        case (SIGNATURE_32 ('G', 'N', 'V', 'S')):
          //
          // Conditional match.  For Region Objects, the Operator will always be the
          // byte immediately before the specific name.  Therefore, subtract 1 to check
          // the Operator.
          //
          Operation = DsdtPointer - 1;
          if (*Operation == AML_EXT_REGION_OP) {
            Address   = (UINT32 *) (DsdtPointer + 6);
            *Address  = (UINT32) (UINTN) mPlatformNvsAreaProtocol.Area;
            Size      = (UINT16 *) (DsdtPointer + 11);
            *Size     = sizeof (PLATFORM_NVS_AREA);
          }
          break;

        //
        // _AC0 method
        //
        case (SIGNATURE_32 ('_', 'A', 'C', '0')):
          //
          // Conditional match.  _AC0 is >63 and <4095 bytes, so the package length is 2 bytes.
          // Therefore, subtract 3 to check the Operator.
          //
          Operation = DsdtPointer - 3;
          if (*Operation == AML_METHOD_OP) {
            //
            // Check if we want _AC0 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'C', '0');
            }
          }
          break;

        //
        // _AL0 method
        //
        case (SIGNATURE_32 ('_', 'A', 'L', '0')):
          //
          // Conditional match.  For Name Objects, the Operator will always be the byte
          // immediately before the specific name. Therefore, subtract 1 to check the
          // Operator.
          //
          Operation = DsdtPointer - 1;
          if (*Operation == AML_NAME_OP) {

            //
            // Check if we want _AL0 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'L', '0');
            }
          }
          break;

        //
        // _AC1 method
        //
        case (SIGNATURE_32 ('_', 'A', 'C', '1')):
          //
          // Conditional match.  _AC1 is < 63 bytes, so the package length is 1 byte.
          // Therefore, subtract 2 to check the Operator.
          //
          Operation = DsdtPointer - 2;
          if (*Operation == AML_METHOD_OP) {

            //
            // Check if we want _AC1 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'C', '1');
            }
          }
          break;

        //
        // _AL1 method
        //
        case (SIGNATURE_32 ('_', 'A', 'L', '1')):
          //
          // Conditional match.  For Name Objects, the Operator will always be the byte
          // immediately before the specific name. Therefore, subtract 1 to check the
          // Operator.
          //
          Operation = DsdtPointer - 1;
          if (*Operation == AML_NAME_OP) {

            //
            // Check if we want _AL1 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'L', '1');
            }
          }
          break;

        //
        // _AC2 method
        //
        case (SIGNATURE_32 ('_', 'A', 'C', '2')):
          //
          // Conditional match.  _AC2 is < 63 bytes, so the package length is 1 byte.
          // Therefore, subtract 2 to check the Operator.
          //
          Operation = DsdtPointer - 2;
          if (*Operation == AML_METHOD_OP) {

            //
            // Check if we want _AC2 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'C', '2');
            }
          }
          break;

        //
        // _AL2 method
        //
        case (SIGNATURE_32 ('_', 'A', 'L', '2')):
          //
          // Conditional match.  For Name Objects, the Operator will always be the byte
          // immediately before the specific name. Therefore, subtract 1 to check the
          // Operator.
          //
          Operation = DsdtPointer - 1;
          if (*Operation == AML_NAME_OP) {

            //
            // Check if we want _AL2 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'L', '2');
            }
          }
          break;

        //
        // _AC3 method
        //
        case (SIGNATURE_32 ('_', 'A', 'C', '3')):
          //
          // Conditional match.  _AC3 is < 63 bytes, so the package length is 1 byte.
          // Therefore, subtract 2 to check the Operator.
          //
          Operation = DsdtPointer - 2;
          if (*Operation == AML_METHOD_OP) {

            //
            // Check if we want _AC3 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'C', '3');
            }
          }
          break;

        //
        // _AL3 method
        //
        case (SIGNATURE_32 ('_', 'A', 'L', '3')):
          //
          // Conditional match.  For Name Objects, the Operator will always be the byte
          // immediately before the specific name. Therefore, subtract 1 to check the
          // Operator.
          //
          Operation = DsdtPointer - 1;
          if (*Operation == AML_NAME_OP) {

            //
            // Check if we want _AL3 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'L', '3');
            }
          }
          break;

        //
        // _AC4 method
        //
        case (SIGNATURE_32 ('_', 'A', 'C', '4')):
          //
          // Conditional match.  _AC4 is < 63 bytes, so the package length is 1 byte.
          // Therefore, subtract 2 to check the Operator.
          //
          Operation = DsdtPointer - 2;
          if (*Operation == AML_METHOD_OP) {

            //
            // Check if we want _AC4 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'C', '4');
            }
          }
          break;

        //
        // _AL4 method
        //
        case (SIGNATURE_32 ('_', 'A', 'L', '4')):
          //
          // Conditional match.  For Name Objects, the Operator will always be the byte
          // immediately before the specific name. Therefore, subtract 1 to check the
          // Operator.
          //
          Operation = DsdtPointer - 1;
          if (*Operation == AML_NAME_OP) {

            //
            // Check if we want _AL4 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'L', '4');
            }
          }
          break;

        //
        // _AC5 method
        //
        case (SIGNATURE_32 ('_', 'A', 'C', '5')):
          //
          // Conditional match.  _AC5 is < 63 bytes, so the package length is 1 byte.
          // Therefore, subtract 2 to check the Operator.
          //
          Operation = DsdtPointer - 2;
          if (*Operation == AML_METHOD_OP) {

            //
            // Check if we want _AC5 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'C', '5');
            }
          }
          break;

        //
        // _AL5 method
        //
        case (SIGNATURE_32 ('_', 'A', 'L', '5')):
          //
          // Conditional match.  For Name Objects, the Operator will always be the byte
          // immediately before the specific name. Therefore, subtract 1 to check the
          // Operator.
          //
          Operation = DsdtPointer - 1;
          if (*Operation == AML_NAME_OP) {

            //
            // Check if we want _AL5 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'L', '5');
            }
          }
          break;

        //
        // _AC6 method
        //
        case (SIGNATURE_32 ('_', 'A', 'C', '6')):
          //
          // Conditional match.  _AC6 is < 63 bytes, so the package length is 1 byte.
          // Therefore, subtract 2 to check the Operator.
          //
          Operation = DsdtPointer - 2;
          if (*Operation == AML_METHOD_OP) {

            //
            // Check if we want _AC6 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'C', '6');
            }
          }
          break;

        //
        // _AL6 method
        //
        case (SIGNATURE_32 ('_', 'A', 'L', '6')):
          //
          // Conditional match.  For Name Objects, the Operator will always be the byte
          // immediately before the specific name. Therefore, subtract 1 to check the
          // Operator.
          //
          Operation = DsdtPointer - 1;
          if (*Operation == AML_NAME_OP) {

            //
            // Check if we want _AL6 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'L', '6');
            }
          }
          break;

        //
        // _AC7 method
        //
        case (SIGNATURE_32 ('_', 'A', 'C', '7')):
          //
          // Conditional match.  _AC7 is < 63 bytes, so the package length is 1 byte.
          // Therefore, subtract 2 to check the Operator.
          //
          Operation = DsdtPointer - 2;
          if (*Operation == AML_METHOD_OP) {

            //
            // Check if we want _AC7 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'C', '7');
            }
          }
          break;

        //
        // _AL7 method
        //
        case (SIGNATURE_32 ('_', 'A', 'L', '7')):
          //
          // Conditional match.  For Name Objects, the Operator will always be the byte
          // immediately before the specific name. Therefore, subtract 1 to check the
          // Operator.
          //
          Operation = DsdtPointer - 1;
          if (*Operation == AML_NAME_OP) {

            //
            // Check if we want _AL7 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'L', '7');
            }
          }
          break;

        //
        // _AC8 method
        //
        case (SIGNATURE_32 ('_', 'A', 'C', '8')):
          //
          // Conditional match.  _AC8 is < 63 bytes, so the package length is 1 byte.
          // Therefore, subtract 2 to check the Operator.
          //
          Operation = DsdtPointer - 2;
          if (*Operation == AML_METHOD_OP) {

            //
            // Check if we want _AC8 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'C', '8');
            }
          }
          break;

        //
        // _AL8 method
        //
        case (SIGNATURE_32 ('_', 'A', 'L', '8')):
          //
          // Conditional match.  For Name Objects, the Operator will always be the byte
          // immediately before the specific name. Therefore, subtract 1 to check the
          // Operator.
          //
          Operation = DsdtPointer - 1;
          if (*Operation == AML_NAME_OP) {

            //
            // Check if we want _AL8 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'L', '8');
            }
          }
          break;

        //
        // _AC9 method
        //
        case (SIGNATURE_32 ('_', 'A', 'C', '9')):
          //
          // Conditional match.  _AC9 is < 63 bytes, so the package length is 1 byte.
          // Therefore, subtract 2 to check the Operator.
          //
          Operation = DsdtPointer - 2;
          if (*Operation == AML_METHOD_OP) {

            //
            // Check if we want _AC9 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'C', '9');
            }
          }
          break;

        //
        // _AL9 method
        //
        case (SIGNATURE_32 ('_', 'A', 'L', '9')):
          //
          // Conditional match.  For Name Objects, the Operator will always be the byte
          // immediately before the specific name. Therefore, subtract 1 to check the
          // Operator.
          //
          Operation = DsdtPointer - 1;
          if (*Operation == AML_NAME_OP) {

            //
            // Check if we want _AL9 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'L', '9');
            }
          }
          break;

        //
        // _PSL method
        //
        case (SIGNATURE_32 ('_', 'P', 'S', 'L')):
          //
          // Conditional match.  _PSL is < 256 bytes, so the package length is 1 byte.
          // Therefore, subtract 2 to check the Operator.
          //
          Operation = DsdtPointer - 3;
          if (*Operation == AML_METHOD_OP) {

            //
            // Check if we want _PSL enabled
            //
            if (mSystemConfiguration.DisablePassiveTripPoints == 0) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'P', 'S', 'L');
            }
          }
          break;

        //
        // _PSV method
        //
        case (SIGNATURE_32 ('_', 'P', 'S', 'V')):
          //
          // Conditional match.  _PSV is < 256 bytes, so the package length is 1 byte.
          // Therefore, subtract 2 to check the Operator.
          //
          Operation = DsdtPointer - 3;
          if (*Operation == AML_METHOD_OP) {

            //
            // Check if we want _PSV enabled
            //
            if (mSystemConfiguration.DisablePassiveTripPoints == 0) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'P', 'S', 'V');
            }
          }
          break;

        //
        // _CRT method
        //
        case (SIGNATURE_32 ('_', 'C', 'R', 'T')):
          //
          // Conditional match.  _CRT is < 256 bytes, so the package length is 1 byte.
          // Subtract 3 to check the Operator for CRB, subract 2 for Harris Beach.
          //
          Operation = DsdtPointer - 3;
          if (*Operation == AML_METHOD_OP) {

            //
            // Check if we want _CRT enabled
            //
            if (mSystemConfiguration.DisableCriticalTripPoints == 0) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'C', 'R', 'T');
            }
          }
          break;

        //
        // _TC1 method
        //
        case (SIGNATURE_32 ('_', 'T', 'C', '1')):
          //
          // Conditional match.  _TC1 is < 256 bytes, so the package length is 1 byte.
          // Therefore, subtract 2 to check the Operator.
          //
          Operation = DsdtPointer - 2;
          if (*Operation == AML_METHOD_OP) {

            //
            // Check if we want _TC1 enabled
            //
            if (mSystemConfiguration.DisablePassiveTripPoints == 0) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'T', 'C', '1');
            }
          }
          break;

        //
        // _TC2 method
        //
        case (SIGNATURE_32 ('_', 'T', 'C', '2')):
          //
          // Conditional match.  _TC2 is < 256 bytes, so the package length is 1 byte.
          // Therefore, subtract 2 to check the Operator.
          //
          Operation = DsdtPointer - 2;
          if (*Operation == AML_METHOD_OP) {

            //
            // Check if we want _TC2 enabled
            //
            if (mSystemConfiguration.DisablePassiveTripPoints == 0) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'T', 'C', '2');
            }
          }
          break;

        //
        // _TSP method
        //
        case (SIGNATURE_32 ('_', 'T', 'S', 'P')):
          //
          // Conditional match.  _TSP is < 256 bytes, so the package length is 1 byte.
          // Therefore, subtract 2 to check the Operator.
          //
          Operation = DsdtPointer - 2;
          if (*Operation == AML_METHOD_OP) {

            //
            // Check if we want _TSP enabled
            //
            if (mSystemConfiguration.DisablePassiveTripPoints == 0) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'T', 'S', 'P');
            }
          }
          break;

        //
        // Update SS3 Name with Setup value
        //
        case (SIGNATURE_32 ('S', 'S', '3', '_')):
          Operation = DsdtPointer - 1;
          if (*Operation == AML_NAME_OP) {
            Value   = (UINT8 *) DsdtPointer + 5;
            *Value  = (UINT8)mSystemConfiguration.AcpiSleepState;
          }
          break;
        //
        // Update SS4 Name with Setup value
        //
        case (SIGNATURE_32 ('S', 'S', '4', '_')):
          Operation = DsdtPointer - 1;
          if (*Operation == AML_NAME_OP) {
            Value   = (UINT8 *) DsdtPointer + 5;
            *Value  = mSystemConfiguration.AcpiHibernate;
          }
          break;
        //
        // _EJ0 method
        //
        case (SIGNATURE_32 ('_', 'E', 'J', '0')):
          if (mSystemConfiguration.LowPowerS0Idle) {
            //
            // Remove _EJ0 for SOC
            //
            if (*(DsdtPointer-3) == AML_METHOD_OP) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'E', 'J', '0');
              EnterDock = TRUE;
            }
          }
          break;
        //
        // _STA method for Device (\_SB.PC00.DOCK)
        //
        case (SIGNATURE_32 ('_', 'S', 'T', 'A')):
          if (mSystemConfiguration.LowPowerS0Idle) {
            //
            // Remove _STA in (\_SB.PC00.DOCK) for SOC
            //
            if ((*(DsdtPointer-3) == AML_METHOD_OP) && (EnterDock)) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'S', 'T', 'A');
              EnterDock = FALSE;
            }
          }
          break;
        //
        // _UPC method for Device (\_SB.PC00.XHCI.RHUB)
        //
        case (SIGNATURE_32('H', 'S', '1', '3')):
          for (TmpDsdtPointer = DsdtPointer;
               TmpDsdtPointer <= DsdtPointer + MaximumDsdtPointLength;
               TmpDsdtPointer++){
            Signature = (UINT32 *) TmpDsdtPointer;
            switch (*Signature) {
              case(SIGNATURE_32('U', 'P', 'C', 'P')):
                Value   = (UINT8 *)((UINT32 *)TmpDsdtPointer + 2);
                break;
              default:
                //
                // Do nothing.
                //
                break;
            }
          }
        break;


        //
        // _DCK method
        //
        case (SIGNATURE_32 ('_', 'D', 'C', 'K')):
          if (mSystemConfiguration.LowPowerS0Idle) {
            //
            // Remove _DCK for SOC
            //
            if (*(DsdtPointer-3) == AML_METHOD_OP) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'D', 'C', 'K');
            }
          }
          break;

        //
        // mask _DEP from CPU's scope if CS disabled.
        //
        case (SIGNATURE_32 ('P', 'R', '0', '0')):
        case (SIGNATURE_32 ('P', 'R', '0', '1')):
        case (SIGNATURE_32 ('P', 'R', '0', '2')):
        case (SIGNATURE_32 ('P', 'R', '0', '3')):
        case (SIGNATURE_32 ('P', 'R', '0', '4')):
        case (SIGNATURE_32 ('P', 'R', '0', '5')):
        case (SIGNATURE_32 ('P', 'R', '0', '6')):
        case (SIGNATURE_32 ('P', 'R', '0', '7')):
        case (SIGNATURE_32 ('P', 'R', '0', '8')):
        case (SIGNATURE_32 ('P', 'R', '0', '9')):
        case (SIGNATURE_32 ('P', 'R', '1', '0')):
        case (SIGNATURE_32 ('P', 'R', '1', '1')):
        case (SIGNATURE_32 ('P', 'R', '1', '2')):
        case (SIGNATURE_32 ('P', 'R', '1', '3')):
        case (SIGNATURE_32 ('P', 'R', '1', '4')):
        case (SIGNATURE_32 ('P', 'R', '1', '5')):
          if (mSystemConfiguration.LowPowerS0Idle == 0) {
            for (TmpDsdtPointer = DsdtPointer; TmpDsdtPointer <= DsdtPointer + MaximumDsdtPointLength; TmpDsdtPointer++){
              Signature = (UINT32 *) TmpDsdtPointer;
              switch (*Signature) {
                case(SIGNATURE_32('_', 'D', 'E', 'P')):
                  *(UINT8 *) TmpDsdtPointer = 'X';
                  break;
                default:
                  //
                  // Do nothing.
                  //
                  break;
              }
            }
          }
          break;

        //
        // _EDL name
        //
        case (SIGNATURE_32 ('_', 'E', 'D', 'L')):
          if (mSystemConfiguration.LowPowerS0Idle) {
            //
            // Remove _EDL for SOC
            //
            if (*(DsdtPointer-1) == AML_NAME_OP) {
              Signature   = (UINT32 *) DsdtPointer;
              *Signature  = SIGNATURE_32 ('X', 'E', 'D', 'L');
            }
          }
          break;

        default:
          //
          // Do nothing.
          //
          break;
        }
      }
    }
    break;

  case EFI_ACPI_3_0_HIGH_PRECISION_EVENT_TIMER_TABLE_SIGNATURE:
    //
    // If HPET is disabled in setup, don't publish the table.
    //
    if (mPchSetup.Hpet == FALSE) {
      *Version = EFI_ACPI_TABLE_VERSION_NONE;
    } else {
      //
      // Get HPET base address
      //
      PchHpetBaseGet (&HpetBaseAdress);
      //
      // Adjust HPET Table to correct the Base Address
      //
      ((EFI_ACPI_HIGH_PRECISION_EVENT_TIMER_TABLE_HEADER*) Table)->BaseAddressLower32Bit.Address = HpetBaseAdress;
    }
    break;

  case EFI_ACPI_3_0_PCI_EXPRESS_MEMORY_MAPPED_CONFIGURATION_SPACE_BASE_ADDRESS_DESCRIPTION_TABLE_SIGNATURE:
    //
    // Update MCFG base and end bus number
    //
    ((EFI_ACPI_MEMORY_MAPPED_CONFIGURATION_SPACE_ACCESS_DESCRIPTION_TABLE *) Table)->AllocationStructure[0].BaseAddress
      = PcdGet64 (PcdPciExpressBaseAddress);

    ((EFI_ACPI_MEMORY_MAPPED_CONFIGURATION_SPACE_ACCESS_DESCRIPTION_TABLE *) Table)->AllocationStructure[0].EndBusNumber
      = (UINT8)(PcdGet32 (PcdPciExpressRegionLength) / 0x100000) - 1;
#if FixedPcdGetBool(PcdITbtEnable) == 1
    if (mTcssHob->TcssData.PcieMultipleSegmentEnabled) {
      ((EFI_ACPI_MEMORY_MAPPED_CONFIGURATION_SPACE_ACCESS_DESCRIPTION_TABLE *) Table)->AllocationStructure[1].BaseAddress
      = PcdGet64 (PcdPciExpressBaseAddress) + SIZE_256MB;
    } else
#endif
    {
      ((EFI_ACPI_MEMORY_MAPPED_CONFIGURATION_SPACE_ACCESS_DESCRIPTION_TABLE *) Table)->Header.Length -= sizeof (EFI_ACPI_MEMORY_MAPPED_ENHANCED_CONFIGURATION_SPACE_BASE_ADDRESS_ALLOCATION_STRUCTURE);
    }
    break;

  case EFI_ACPI_5_0_EMBEDDED_CONTROLLER_BOOT_RESOURCES_TABLE_SIGNATURE:
    //
    // If EC is not present, don't publish the table.
    //
    if (mPlatformNvsAreaProtocol.Area->EcAvailable == PLATFORM_NVS_DEVICE_DISABLE) {
      *Version = EFI_ACPI_TABLE_VERSION_NONE;
    } else {
      //
      // Update GPE Number
      //
      ((EFI_ACPI_5_0_EMBEDDED_CONTROLLER_BOOT_RESOURCES_TABLE *) Table)->GpeBit = (UINT8) GetEcGpeNumber ();
    }
    break;

/* @todo Need to uncomment once MSFT fully implements uPEP
  case SIGNATURE_32 ('L', 'P', 'I', 'T'):
    //
    // If L0s is disabled in setup, don't publish the table.
    //
    if (mSystemConfiguration.LowPowerS0Idle == 0) {
      *Version = EFI_ACPI_TABLE_VERSION_NONE;
    }
    break;
*/
  case EFI_ACPI_1_0_SECONDARY_SYSTEM_DESCRIPTION_TABLE_SIGNATURE:
  {
    UINT8   *TablePointer;
    UINT32  *Signature;
    UINT8   *Operation;

    //
    // Do not load the xHCI table. It is handled by separate function.
    //
    if (CompareMem (&TableHeader->OemTableId, "xh_", 3) == 0) {
      DEBUG((DEBUG_INFO,"TableHeader->OemTableId = %x\n ", TableHeader->OemTableId));
      *Version = EFI_ACPI_TABLE_VERSION_NONE;
    }

    //
    // Load SSDT tables for the platforms based on boardID; default to RVP tables.
    // Load Ther_Sds for SDS platform.
    // Load Ther_Rvp for all others.
    //
    if (CompareMem (&TableHeader->OemTableId, "Ther_Sds", 8) == 0) {
      *Version = EFI_ACPI_TABLE_VERSION_NONE;
    }

    if (CompareMem (&TableHeader->OemTableId, "Ther_Rvp", 8) == 0) {
      CurrPtr = (UINT8 *) Table;
      for (TablePointer = CurrPtr;TablePointer < (CurrPtr + ((EFI_ACPI_COMMON_HEADER *) CurrPtr)->Length - sizeof (UINT32));TablePointer++)
      {
        Signature = (UINT32 *) TablePointer;
        switch (*Signature) {
        //
        // _AC0 method
        //
        case (SIGNATURE_32 ('_', 'A', 'C', '0')):
          //
          // Conditional match.  _AC0 is >63 and <4095 bytes, so the package length is 2 bytes.
          // Therefore, subtract 3 to check the Operator.
          //
          Operation = TablePointer - 3;
          if (*Operation == AML_METHOD_OP) {
            //
            // Check if we want _AC0 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) TablePointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'C', '0');
            }
          }
          break;
        //
        // _AL0 method
        //
        case (SIGNATURE_32 ('_', 'A', 'L', '0')):
          //
          // Conditional match.  For Name Objects, the Operator will always be the byte
          // immediately before the specific name. Therefore, subtract 1 to check the
          // Operator.
          //
          Operation = TablePointer - 1;
          if (*Operation == AML_NAME_OP) {
            //
            // Check if we want _AL0 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) TablePointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'L', '0');
            }
          }
          break;
        //
        // _AC1 method
        //
        case (SIGNATURE_32 ('_', 'A', 'C', '1')):
          //
          // Conditional match.  _AC1 is < 63 bytes, so the package length is 1 byte.
          // Therefore, subtract 2 to check the Operator.
          //
          Operation = TablePointer - 2;
          if (*Operation == AML_METHOD_OP) {
            //
            // Check if we want _AC1 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) TablePointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'C', '1');
            }
          }
          break;
        //
        // _AL1 method
        //
        case (SIGNATURE_32 ('_', 'A', 'L', '1')):
          //
          // Conditional match.  For Name Objects, the Operator will always be the byte
          // immediately before the specific name. Therefore, subtract 1 to check the
          // Operator.
          //
          Operation = TablePointer - 1;
          if (*Operation == AML_NAME_OP) {
            //
            // Check if we want _AL1 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) TablePointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'L', '1');
            }
          }
          break;
        //
        // _AC2 method
        //
        case (SIGNATURE_32 ('_', 'A', 'C', '2')):
          //
          // Conditional match.  _AC2 is < 63 bytes, so the package length is 1 byte.
          // Therefore, subtract 2 to check the Operator.
          //
          Operation = TablePointer - 2;
          if (*Operation == AML_METHOD_OP) {
            //
            // Check if we want _AC2 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) TablePointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'C', '2');
            }
          }
          break;
        //
        // _AL2 method
        //
        case (SIGNATURE_32 ('_', 'A', 'L', '2')):
          //
          // Conditional match.  For Name Objects, the Operator will always be the byte
          // immediately before the specific name. Therefore, subtract 1 to check the
          // Operator.
          //
          Operation = TablePointer - 1;
          if (*Operation == AML_NAME_OP) {
            //
            // Check if we want _AL2 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) TablePointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'L', '2');
            }
          }
          break;
        //
        // _AC3 method
        //
        case (SIGNATURE_32 ('_', 'A', 'C', '3')):
          //
          // Conditional match.  _AC3 is < 63 bytes, so the package length is 1 byte.
          // Therefore, subtract 2 to check the Operator.
          //
          Operation = TablePointer - 2;
          if (*Operation == AML_METHOD_OP) {
            //
            // Check if we want _AC3 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) TablePointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'C', '3');
            }
          }
          break;
        //
        // _AL3 method
        //
        case (SIGNATURE_32 ('_', 'A', 'L', '3')):
          //
          // Conditional match.  For Name Objects, the Operator will always be the byte
          // immediately before the specific name. Therefore, subtract 1 to check the
          // Operator.
          //
          Operation = TablePointer - 1;
          if (*Operation == AML_NAME_OP) {
            //
            // Check if we want _AL3 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) TablePointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'L', '3');
            }
          }
          break;
        //
        // _AC4 method
        //
        case (SIGNATURE_32 ('_', 'A', 'C', '4')):
          //
          // Conditional match.  _AC4 is < 63 bytes, so the package length is 1 byte.
          // Therefore, subtract 2 to check the Operator.
          //
          Operation = TablePointer - 2;
          if (*Operation == AML_METHOD_OP) {
            //
            // Check if we want _AC4 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) TablePointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'C', '4');
            }
          }
          break;
        //
        // _AL4 method
        //
        case (SIGNATURE_32 ('_', 'A', 'L', '4')):
          //
          // Conditional match.  For Name Objects, the Operator will always be the byte
          // immediately before the specific name. Therefore, subtract 1 to check the
          // Operator.
          //
          Operation = TablePointer - 1;
          if (*Operation == AML_NAME_OP) {
            //
            // Check if we want _AL4 enabled
            //
            if (mSystemConfiguration.DisableActiveTripPoints == 0) {
              Signature   = (UINT32 *) TablePointer;
              *Signature  = SIGNATURE_32 ('X', 'A', 'L', '4');
            }
          }
          break;
        // _PSL method
        //
        case (SIGNATURE_32 ('_', 'P', 'S', 'L')):
          //
          // Conditional match.  _PSL is < 256 bytes, so the package length is 1 byte.
          // Therefore, subtract 2 to check the Operator.
          //
          Operation = TablePointer - 3;
          if (*Operation == AML_METHOD_OP) {
            //
            // Check if we want _PSL enabled
            //
            if (mSystemConfiguration.DisablePassiveTripPoints == 0) {
              Signature   = (UINT32 *) TablePointer;
              *Signature  = SIGNATURE_32 ('X', 'P', 'S', 'L');
            }
          }
          break;
        //
        // _PSV method
        //
        case (SIGNATURE_32 ('_', 'P', 'S', 'V')):
          //
          // Conditional match.  _PSV is < 256 bytes, so the package length is 1 byte.
          // Therefore, subtract 2 to check the Operator.
          //
          Operation = TablePointer - 3;
          if (*Operation == AML_METHOD_OP) {
            //
            // Check if we want _PSV enabled
            //
            if (mSystemConfiguration.DisablePassiveTripPoints == 0) {
              Signature   = (UINT32 *) TablePointer;
              *Signature  = SIGNATURE_32 ('X', 'P', 'S', 'V');
            }
          }
          break;
        //
        // _CRT method
        //
        case (SIGNATURE_32 ('_', 'C', 'R', 'T')):
          //
          // Conditional match.  _CRT is < 256 bytes, so the package length is 1 byte.
          // Subtract 3 to check the Operator for CRB, subract 2 for Harris Beach.
          //
          Operation = TablePointer - 3;
          if (*Operation == AML_METHOD_OP) {
            //
            // Check if we want _CRT enabled
            //
            if (mSystemConfiguration.DisableCriticalTripPoints == 0) {
              Signature   = (UINT32 *) TablePointer;
              *Signature  = SIGNATURE_32 ('X', 'C', 'R', 'T');
            }
          }
          break;
        //
        // _TC1 method
        //
        case (SIGNATURE_32 ('_', 'T', 'C', '1')):
          //
          // Conditional match.  _TC1 is < 256 bytes, so the package length is 1 byte.
          // Therefore, subtract 2 to check the Operator.
          //
          Operation = TablePointer - 2;
          if (*Operation == AML_METHOD_OP) {
            //
            // Check if we want _TC1 enabled
            //
            if (mSystemConfiguration.DisablePassiveTripPoints == 0) {
              Signature   = (UINT32 *) TablePointer;
              *Signature  = SIGNATURE_32 ('X', 'T', 'C', '1');
            }
          }
          break;
        //
        // _TC2 method
        //
        case (SIGNATURE_32 ('_', 'T', 'C', '2')):
          //
          // Conditional match.  _TC2 is < 256 bytes, so the package length is 1 byte.
          // Therefore, subtract 2 to check the Operator.
          //
          Operation = TablePointer - 2;
          if (*Operation == AML_METHOD_OP) {
            //
            // Check if we want _TC2 enabled
            //
            if (mSystemConfiguration.DisablePassiveTripPoints == 0) {
              Signature   = (UINT32 *) TablePointer;
              *Signature  = SIGNATURE_32 ('X', 'T', 'C', '2');
            }
          }
          break;
        //
        // _TSP method
        //
        case (SIGNATURE_32 ('_', 'T', 'S', 'P')):
          //
          // Conditional match.  _TSP is < 256 bytes, so the package length is 1 byte.
          // Therefore, subtract 2 to check the Operator.
          //
          Operation = TablePointer - 2;
          if (*Operation == AML_METHOD_OP) {
            //
            // Check if we want _TSP enabled
            //
            if (mSystemConfiguration.DisablePassiveTripPoints == 0) {
              Signature   = (UINT32 *) TablePointer;
              *Signature  = SIGNATURE_32 ('X', 'T', 'S', 'P');
            }
          }
          break;
        }
      }
    }

    //
    // Load RTD3 SSDT table for EHL RVP SKUs
    //
    if ((CompareMem (&TableHeader->OemTableId, "Ehl_Rvp", 8) == 0) ||
        (CompareMem (&TableHeader->OemTableId, "Ehl_Crb", 8) == 0)) {
      //
      // set default = none
      //
      *Version = EFI_ACPI_TABLE_VERSION_NONE;

      //
      // check RTD3 enabled in setup
      //
      if (mSystemConfiguration.Rtd3Support == 1) {
        //
        // match table ID and BoardId
        //

        // load RTD3 table for EHL U RVP
        if (CompareMem(&TableHeader->OemTableId, "Ehl_Rvp", 8) == 0) {
          if (PcdGetBool(PcdEhlRvpRtd3TableEnable)) {
            *Version = EFI_ACPI_TABLE_VERSION_1_0B | EFI_ACPI_TABLE_VERSION_2_0 | EFI_ACPI_TABLE_VERSION_3_0;
          }
        }

        // load RTD3 table for EHL U ERB
        if (CompareMem(&TableHeader->OemTableId, "Ehl_Crb", 8) == 0) {
          if (PcdGetBool(PcdEhlCrbRtd3TableEnable)) {
            *Version = EFI_ACPI_TABLE_VERSION_1_0B | EFI_ACPI_TABLE_VERSION_2_0 | EFI_ACPI_TABLE_VERSION_3_0;
          }
        }

      } // Rtd3Support
    } // Load RTD3 SSDT table
  }
    break;

  case EFI_ACPI_PRAM_BASE_ADDRESS_TABLE_SIGNATURE:
    VariableSize = sizeof (SA_SETUP);
    Status = gRT->GetVariable (
                    L"SaSetup",
                    &gSaSetupVariableGuid,
                    NULL,
                    &VariableSize,
                    &SaSetup
                    );
    ASSERT_EFI_ERROR (Status);

    VariableSize = sizeof(UINTN);
    Status = gRT->GetVariable (
                    L"PRAM_Conf",
                    &gEfiPramConfGuid,
                    NULL,
                    &VariableSize,
                    &PramConfigVariable
                    );

    if ((Status == EFI_SUCCESS) && (PramConfigVariable != SaSetup.PramSize)) {
      DEBUG ((DEBUG_INFO, "PramConfigVariable =  0x%x\n", PramConfigVariable));
      VariableSize = sizeof (SA_SETUP);
      Status = gRT->GetVariable (
                      L"SaSetup",
                      &gSaSetupVariableGuid,
                      &VariableAttributes,
                      &VariableSize,
                      &SaSetupVarBuffer
                      );
      ASSERT_EFI_ERROR (Status);
      SaSetupVarBuffer.PramSize = PramConfigVariable;
      Status = gRT->SetVariable (
                      L"SaSetup",
                      &gSaSetupVariableGuid,
                      VariableAttributes,
                      VariableSize,
                      &SaSetupVarBuffer
                      );
      ASSERT_EFI_ERROR (Status);
      //
      // WA for variable cannot be accessed before memory init
      //
      DEBUG ((DEBUG_INFO, "EfiResetWarm for Pram\n"));
      gRT->ResetSystem (EfiResetWarm, EFI_SUCCESS, 0, NULL);
      CpuDeadLoop ();
    } else {
      PramConfigVariable = SaSetup.PramSize;
      Status = gRT->SetVariable (
                      L"PRAM_Conf",
                      &gEfiPramConfGuid,
                      EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
                      sizeof (PramConfigVariable),
                      &PramConfigVariable
                      );
      ASSERT_EFI_ERROR (Status);
      DEBUG ((DEBUG_INFO, "PramConfigVariable =  0x%x\n", PramConfigVariable));
    }
    if (PramConfigVariable !=  0x0) {
      switch (PramConfigVariable) {
        case 0x31:  // 4MB
            PramSize = 0x400000;
            break;
        case 0x32: // 16MB
            PramSize = 0x1000000;
            break;
        case 0x33: // 64MB
            PramSize = 0x4000000;
            break;
        default:
            PramSize = 0;
            break;
      }
      MemoryPlatformData = GetFirstGuidHob (&gSiMemoryPlatformDataGuid);
      ASSERT (MemoryPlatformData != NULL);
      if (MemoryPlatformData != NULL) {
        PramBaseAddress = LShiftU64 (MemoryPlatformData->Data.PramBase, 20);
      }
      DEBUG ((DEBUG_INFO, "PramBaseAddress =  0x%lx\n", PramBaseAddress));
      DEBUG ((DEBUG_INFO, "PramSize =  0x%lx\n", PramSize));
      ((EFI_ACPI_PRAM_BASE_ADDRESS_TABLE *) Table)->PramBaseAddress = PramBaseAddress;
      ((EFI_ACPI_PRAM_BASE_ADDRESS_TABLE *) Table)->PramSize = PramSize;
    }
    break;
  default:
    break;
  }
  return EFI_SUCCESS;
}

/**
  This function calculates RCR based on PCI Device ID and Vendor ID from the devices
  available on the platform.
  It also includes other instances of BIOS change to calculate CRC and provides as
  HWSignature filed in FADT table.
**/
VOID
IsHardwareChange (
  VOID
  )
{
  EFI_STATUS                    Status;
  UINTN                         Index;
  UINTN                         HandleCount;
  EFI_HANDLE                    *HandleBuffer;
  EFI_PCI_IO_PROTOCOL           *PciIo;
  UINT32                        CRC;
  UINT32                        *HWChange;
  UINTN                         HWChangeSize;
  UINT32                        PciId;
  UINTN                         Handle;
  EFI_ACPI_2_0_FIRMWARE_ACPI_CONTROL_STRUCTURE *FacsPtr;
  EFI_ACPI_3_0_FIXED_ACPI_DESCRIPTION_TABLE    *pFADT;

  HandleCount  = 0;
  HandleBuffer = NULL;

  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiPciIoProtocolGuid,
                  NULL,
                  &HandleCount,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status)) {
    return; // PciIO protocol not installed yet!
  }

  if (HandleCount > 0x1FFF) { // PCI config space max limit
    return;
  }

  //
  // Allocate memory for HWChange and add additional entrie for
  // pFADT->XDsdt
  //
  HWChangeSize = HandleCount + 1;
  HWChange = AllocateZeroPool( sizeof(UINT32) * HWChangeSize );
  ASSERT( HWChange != NULL );

  if (HWChange == NULL) return;

  //
  // add HWChange inputs: PCI devices
  //
  for (Index = 0; HandleCount > 0; HandleCount--) {
    PciId = 0;
    Status = gBS->HandleProtocol (HandleBuffer[Index], &gEfiPciIoProtocolGuid, (VOID **) &PciIo);
    if (!EFI_ERROR (Status)) {
      Status = PciIo->Pci.Read (PciIo, EfiPciIoWidthUint32, 0, 1, &PciId);
      if (EFI_ERROR (Status)) {
        continue;
      }
      HWChange[Index++] = PciId;
    }
  }

  //
  // Locate FACP Table
  //
  Handle = 0;
  Status = LocateAcpiTableBySignature (
              EFI_ACPI_1_0_FIXED_ACPI_DESCRIPTION_TABLE_SIGNATURE,
              (EFI_ACPI_DESCRIPTION_HEADER **) &pFADT,
              &Handle
              );
  if (EFI_ERROR (Status) || (pFADT == NULL)) {
    return;  //Table not found or out of memory resource for pFADT table
  }

  //
  // add HWChange inputs: others
  //
  HWChange[Index++] = (UINT32)pFADT->XDsdt;

  //
  // Calculate CRC value with HWChange data.
  //
  Status = gBS->CalculateCrc32(HWChange, sizeof(UINT32) * HWChangeSize, &CRC);
  DEBUG((DEBUG_INFO,"CRC = %x and Status = %r\n", CRC, Status));

  //
  // Set HardwareSignature value based on CRC value.
  //
  FacsPtr = (EFI_ACPI_2_0_FIRMWARE_ACPI_CONTROL_STRUCTURE *)(UINTN)pFADT->FirmwareCtrl;
  FacsPtr->HardwareSignature = CRC;
  FreePool( HWChange );
}

EFI_STATUS
PublishAcpiTablesFromFv (
  IN EFI_GUID gEfiAcpiMultiTableStorageGuid
  )
{
  EFI_STATUS                    Status;
  EFI_FIRMWARE_VOLUME2_PROTOCOL *FwVol;
  EFI_ACPI_COMMON_HEADER        *CurrentTable;
  UINT32                        FvStatus;
  UINTN                         Size;
  EFI_ACPI_TABLE_VERSION        Version;
  UINTN                         TableHandle;
  INTN                          Instance;
  EFI_ACPI_TABLE_PROTOCOL       *AcpiTable;

  Instance      = 0;
  TableHandle   = 0;
  CurrentTable  = NULL;
  FwVol         = NULL;

  //
  // Find the AcpiSupport protocol
  //
  Status = LocateSupportProtocol (
            &gEfiAcpiTableProtocolGuid,
            gEfiAcpiMultiTableStorageGuid,
            (VOID **) &AcpiTable,
            FALSE
            );
  ASSERT_EFI_ERROR (Status);

  //
  // Locate the firmware volume protocol
  //
  Status = LocateSupportProtocol (
            &gEfiFirmwareVolume2ProtocolGuid,
            gEfiAcpiMultiTableStorageGuid,
            (VOID **) &FwVol,
            TRUE
            );

  /* TODO: Hang at native mode. Need to find the cause
   * when the related drivers are finished for native support. */
  //ASSERT_EFI_ERROR (Status);

  //
  // Read tables from the storage file.
  //
  while (Status == EFI_SUCCESS) {
    Status = FwVol->ReadSection (
                      FwVol,
                      &gEfiAcpiMultiTableStorageGuid,
                      EFI_SECTION_RAW,
                      Instance,
                      (VOID **) &CurrentTable,
                      &Size,
                      &FvStatus
                      );

    if (!EFI_ERROR (Status)) {

      DEBUG((DEBUG_INFO, "[Advanced ACPI] Installing table: %x : %x\n", CurrentTable->Signature, CurrentTable));

      //
      // Perform any table specific updates.
      //
      PlatformUpdateTables (CurrentTable, &Version);
#if (FixedPcdGetBool(PcdS5ChargingEnable) == 1)
      PupdrUpdateTables (CurrentTable);
#endif
      //
      // Add the table
      //
      TableHandle = 0;

      if (Version != EFI_ACPI_TABLE_VERSION_NONE) {
        Status = AcpiTable->InstallAcpiTable (
                              AcpiTable,
                              CurrentTable,
                              CurrentTable->Length,
                              &TableHandle
                              );
      }

      ASSERT_EFI_ERROR (Status);

      //
      // Increment the instance
      //
      Instance++;
      gBS->FreePool (CurrentTable);
      CurrentTable = NULL;
    }

    if (CurrentTable != NULL) {
      gBS->FreePool (CurrentTable);
      CurrentTable = NULL;
    }
  }

  //
  // Finished
  //
  return EFI_SUCCESS;
}


/**
  Allocate MemoryType below 4G memory address.

  @param[in] Size     - Size of memory to allocate.
  @param[in] Buffer   - Allocated address for output.

  @retval EFI_SUCCESS - Memory successfully allocated.
  @retval Other       - Other errors occur.

**/
EFI_STATUS
AllocateMemoryBelow4G (
  IN   EFI_MEMORY_TYPE MemoryType,
  IN   UINTN           Size,
  OUT  VOID           **Buffer
  )
{
  UINTN                 Pages;
  EFI_PHYSICAL_ADDRESS  Address;
  EFI_STATUS            Status;

  Pages = EFI_SIZE_TO_PAGES (Size);
  Address = 0xffffffff;

  Status  = (gBS->AllocatePages) (
                   AllocateMaxAddress,
                   MemoryType,
                   Pages,
                   &Address
                   );

  *Buffer = (VOID *) (UINTN) Address;

  return Status;
}

EFI_STATUS
ReserveS3Memory (
  VOID
  )
{
  VOID                                          *AcpiMemoryBase;
  UINT32                                        AcpiMemorySize;
  EFI_PEI_HOB_POINTERS                          Hob;
  UINT64                                        MemoryLength;
  S3_MEMORY_VARIABLE                            S3MemVariable;
  VOID                                          *VariableData;
  UINTN                                         VarSize;
  EFI_STATUS                                    Status;
  EDKII_VARIABLE_LOCK_PROTOCOL                  *VariableLock;

  DEBUG ((DEBUG_INFO, "ReserveS3Memory\n"));

  //
  // Allocate ACPI reserved memory under 4G
  //
  Status = AllocateMemoryBelow4G (EfiReservedMemoryType, PcdGet32 (PcdS3AcpiReservedMemorySize), &AcpiMemoryBase);
  ASSERT (AcpiMemoryBase != 0);
  AcpiMemorySize = PcdGet32 (PcdS3AcpiReservedMemorySize);

  //
  // Calculate the system memory length by memory hobs
  //
  MemoryLength  = 0x100000;
  Hob.Raw = GetFirstHob (EFI_HOB_TYPE_RESOURCE_DESCRIPTOR);
  ASSERT (Hob.Raw != NULL);
  while ((Hob.Raw != NULL) && (!END_OF_HOB_LIST (Hob))) {
    if (Hob.ResourceDescriptor->ResourceType == EFI_RESOURCE_SYSTEM_MEMORY) {
      //
      // Skip the memory region below 1MB
      //
      if (Hob.ResourceDescriptor->PhysicalStart >= 0x100000) {
        MemoryLength += Hob.ResourceDescriptor->ResourceLength;
      }
    }
    Hob.Raw = GET_NEXT_HOB (Hob);
    Hob.Raw = GetNextHob (EFI_HOB_TYPE_RESOURCE_DESCRIPTOR, Hob.Raw);
  }

  S3MemVariable.AcpiReservedMemoryBase = (EFI_PHYSICAL_ADDRESS)(UINTN) AcpiMemoryBase;
  S3MemVariable.AcpiReservedMemorySize = AcpiMemorySize;
  S3MemVariable.SystemMemoryLength = MemoryLength;

  DEBUG((DEBUG_INFO, "ReserveS3Memory: AcpiMemoryBase is 0x%8x\n", S3MemVariable.AcpiReservedMemoryBase));
  DEBUG((DEBUG_INFO, "ReserveS3Memory: AcpiMemorySize is 0x%8x\n", S3MemVariable.AcpiReservedMemorySize));
  DEBUG((DEBUG_INFO, "ReserveS3Memory: SystemMemoryLength is 0x%8x\n", S3MemVariable.SystemMemoryLength));

  VarSize = sizeof(S3_MEMORY_VARIABLE);
  Status = gBS->AllocatePool(
                  EfiBootServicesData,
                  VarSize,
                  (VOID **) &VariableData
                  );
  ASSERT_EFI_ERROR(Status);
  if (EFI_ERROR(Status)){
    return Status;
  }
  Status = gRT->GetVariable (
                    S3_MEMORY_VARIABLE_NAME,
                    &gS3MemoryVariableGuid,
                    NULL,
                    &VarSize,
                    VariableData
                    );
  if (EFI_ERROR (Status) || (0 != CompareMem (&S3MemVariable, VariableData, VarSize))) {
    DEBUG((DEBUG_INFO, "Update S3MemVariable.\n"));
    Status = gRT->SetVariable (
                    S3_MEMORY_VARIABLE_NAME,
                    &gS3MemoryVariableGuid,
                    EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                    VarSize,
                    &S3MemVariable
                    );
  }
  gBS->FreePool(VariableData);

  Status = gBS->LocateProtocol (&gEdkiiVariableLockProtocolGuid, NULL, (VOID **) &VariableLock);
  if (!EFI_ERROR (Status)) {
    Status = VariableLock->RequestToLock (VariableLock, S3_MEMORY_VARIABLE_NAME, &gS3MemoryVariableGuid);
    ASSERT_EFI_ERROR (Status);
  }

  return EFI_SUCCESS;
}

VOID
EFIAPI
AcpiEndOfDxeEvent (
  EFI_EVENT           Event,
  VOID                *ParentImageHandle
  )
{

  if (Event != NULL) {
    gBS->CloseEvent(Event);
  }


  //
  // Calculate Hardware Signature value based on current platform configurations
  //
  IsHardwareChange();

  //
  // Reserve memory for S3 resume
  //
  ReserveS3Memory ();
}

/**
  Convert string containing GUID in the canonical form:
  "aabbccdd-eeff-gghh-iijj-kkllmmnnoopp"
  where aa - pp are unicode hexadecimal digits
  to the buffer format to be used in ACPI, byte ordering:
  [Byte 0] gg, hh, ee, ff, aa, bb, cc, dd [Byte 7]
  [Byte 8] pp, oo, nn, mm, ll, kk, jj, ii [Byte 16]

  @param[in]  GuidString    - GUID String null terminated (aligned on a 16-bit boundary)
  @param[out] AcpiGuidPart1 - First half of buffer  (bytes 0 - 7)
  @param[out] AcpiGuidPart2 - Second half of buffer (bytes 8 - 16)

  @retval EFI_SUCCESS     - String converted successfully.
  @retval EFI_UNSUPPORTED - Wrong input string format.

**/
EFI_STATUS
GuidStringToAcpiBuffer (
  IN  CHAR16 *GuidString,
  OUT UINT64 *AcpiGuidPart1,
  OUT UINT64 *AcpiGuidPart2
  )
{
  UINT32 GuidTempPart32 = 0;
  UINT16 GuidTempPart16 = 0;
  UINT8  GuidPartIndex;

  DEBUG((DEBUG_INFO,"GuidStringToAcpiBuffer() - GUID = %s\n", GuidString));

  for (GuidPartIndex = 0; GuidPartIndex < 4; GuidPartIndex++) {
    switch (GuidPartIndex){
      case 0:
        GuidTempPart32 = SwapBytes32((UINT32)StrHexToUint64(GuidString));
        *AcpiGuidPart1 = ((UINT64)GuidTempPart32 << 0x20);
        break;
      case 1:
        GuidTempPart16 = SwapBytes16((UINT16)StrHexToUint64(GuidString));
        *AcpiGuidPart1 += ((UINT64)GuidTempPart16 << 0x10);
        break;
      case 2:
        GuidTempPart16 = SwapBytes16((UINT16)StrHexToUint64(GuidString));
        *AcpiGuidPart1 += ((UINT64)GuidTempPart16);
        break;
      case 3:
        GuidTempPart16 = (UINT16)StrHexToUint64(GuidString);
        break;
      default:
        return EFI_UNSUPPORTED;
    }

    while ((*GuidString != L'-') && (*GuidString != L'\0')) {
      GuidString++;
    }

    if (*GuidString == L'-') {
      GuidString++;
    } else {
      return EFI_UNSUPPORTED;
    }
  }

  *AcpiGuidPart2 = ((UINT64)GuidTempPart16 << 0x30) + StrHexToUint64(GuidString);

  // Switch endianess because it will be swapped again in ACPI Buffer object
  *AcpiGuidPart1 = SwapBytes64(*AcpiGuidPart1);
  *AcpiGuidPart2 = SwapBytes64(*AcpiGuidPart2);

  return EFI_SUCCESS;
}

/**
  Save Acpi Setup relatived variables.
**/
EFI_STATUS
SetAcpiSetupVariables (
  VOID
  )
{
  EFI_STATUS                   Status;
  UINTN                        Handle;
  SETUP_DATA                   SetupData;
  UINTN                        VariableSize;
  UINT32                       VariableAttributes;
  EFI_ACPI_DESCRIPTION_HEADER  *Table;

  VariableSize = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  &VariableAttributes,
                  &VariableSize,
                  &SetupData
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  ///
  /// Locate table with matching ID
  ///
  Handle = 0;
  Table  = NULL;
  Status = LocateAcpiTableBySignature (
             EFI_ACPI_2_0_FIXED_ACPI_DESCRIPTION_TABLE_SIGNATURE,
             (EFI_ACPI_DESCRIPTION_HEADER **) &Table,
             &Handle
             );
  if (EFI_ERROR (Status) || (Table == NULL)) {
    return Status;
  }

  SetupData.AcpiTableRevision = Table->Revision;
  Status = gRT->SetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  VariableAttributes,
                  VariableSize,
                  &SetupData
                  );
  ASSERT_EFI_ERROR(Status);
  DEBUG ((DEBUG_INFO, "Acpi table revision: 0x%x, saved successfully.\n", Table->Revision));

  return Status;
}

/**
  Reserves memory region for optimal for LLC QoS.

  @return Status                 On Success, memory was allocated for LLC QoS

  @retval EFI_SUCCESS            TCC Initialization successful. Error otherwise.
  @retval EFI_NOT_FOUND          Could not allocate pages match the requirement.
  @retval EFI_OUT_OF_RESOURCES   No enough pages to allocate.
**/
EFI_STATUS
ReserveLlcQosRegion (
  UINT8  Index
  )
{
  UINTN       RegionAddress;
  UINTN       RegionSize;
  EFI_STATUS  Status;

  Status = EFI_SUCCESS;

  GetLlcQosRegion (Index, &RegionAddress, &RegionSize);

  Status = gBS->AllocatePages (
                  AllocateAddress,
                  EfiReservedMemoryType,
                  EFI_SIZE_TO_PAGES (RegionSize),
                  &RegionAddress
                );

  return Status;
}

/**
  Installs the address of the Platform Time Coordinated Compute
  Configuration Table (PTCT) ACPI Table.

  @retval EFI_SUCCESS        Installed PTCT ACPI Table successfully

**/
EFI_STATUS
EFIAPI
InstallAcpiPtct (
  VOID
  )
{
  EFI_STATUS                     Status;
  UINT8                          Index;
  UINTN                          LlcQosBase;
  UINTN                          LlcQosSize;
  UINT8                          NumLlcQosRecords;

  DEBUG((DEBUG_INFO, "InstallAcpiPtct() start\n"));

   Status = gBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ACPI_PTCT_TABLE),
                  (VOID **) &mPtct
                  );
  ASSERT_EFI_ERROR (Status);

  SetMem (mPtct, sizeof (EFI_ACPI_PTCT_TABLE), 0);

  // Fill in PTCT table
  mPtct->Header.Signature       = EFI_ACPI_PTCT_SIGNATURE;
  mPtct->Header.Length          = sizeof(EFI_ACPI_PTCT_TABLE);
  mPtct->Header.Revision        = EFI_ACPI_PTCT_TABLE_REVISION;
  mPtct->Header.Checksum        = 0;
  CopyMem(&mPtct->Header.OemId, EFI_ACPI_OEM_ID, 6);
  mPtct->Header.OemTableId      = EFI_ACPI_OEM_TABLE_ID;
  mPtct->Header.OemRevision     = EFI_ACPI_OEM_REVISION;
  mPtct->Header.CreatorId       = EFI_ACPI_CREATOR_ID;
  mPtct->Header.CreatorRevision = 0x00000000;

  NumLlcQosRecords = GetNumLlcQosRecords ();

  ASSERT (NumLlcQosRecords <= MAX_NUM_LLC_QOS_RECORDS);
  if (NumLlcQosRecords > MAX_NUM_LLC_QOS_RECORDS) {
    DEBUG ((DEBUG_ERROR, "InstallAcpiPtct: Failed to install LLC QoS Records. Too many records found.\n"));
    NumLlcQosRecords = 0;
  }

  for (Index = 0; Index < NumLlcQosRecords; Index++) {
    Status = ReserveLlcQosRegion (Index);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "InstallAcpiPtct: Failed to reserve region for LLC QoS Records.\n"));
      continue;
    }

    GetLlcQosRegion (Index, &LlcQosBase, &LlcQosSize);

    mPtct->RecordStructures[Index].Type       = 0x01;
    mPtct->RecordStructures[Index].Length     = 24;
    mPtct->RecordStructures[Index].Flags      = 0x0;
    mPtct->RecordStructures[Index].ApicId     = 0xFFFFFFFF;
    mPtct->RecordStructures[Index].RegionBase = LlcQosBase;
    mPtct->RecordStructures[Index].RegionSize = LlcQosSize;
    DEBUG ((DEBUG_INFO, "Installed LLC QoS record. Base: 0x%08x, Size: 0x%08x\n", LlcQosBase, LlcQosSize));
  }

  mPlatformNvsAreaProtocol.Area->TBAS = (UINTN) mPtct;

  DEBUG ((DEBUG_INFO, "InstallAcpiPtct() end PTCT Address: %x\n", (UINTN) mPtct));

  return Status;
}

/**
  ACPI Platform driver installation function.

  @param[in] ImageHandle     Handle for this drivers loaded image protocol.
  @param[in] SystemTable     EFI system table.

  @retval EFI_SUCCESS        The driver installed without error.
  @retval EFI_ABORTED        The driver encountered an error and could not complete installation of
                             the ACPI tables.

**/
EFI_STATUS
EFIAPI
InstallAcpiPlatform (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                    Status;
  UINTN                         VarDataSize;
  EFI_HANDLE                    Handle;
  UINT8                         PortData;
  //UINT8                         BatteryNum;
  EFI_CPUID_REGISTER            CpuidRegs;
  EFI_MP_SERVICES_PROTOCOL      *MpService;
  UINTN                         NumberOfCPUs;
  UINTN                         NumberOfEnabledCPUs;
  UINTN                         Index;
  UINT8                         CtdpLevels;
  EFI_EVENT                     EndOfDxeEvent;
  SA_SETUP                      SaSetup;
  CPU_SETUP                     CpuSetup;
  GPIO_INIT_CONFIG              *UcmcGpioTable;
  UINT16                        UcmcGpioTableSize = 0;


  UINT16                        ModuleName[MIPICAM_MODULE_NAME_LENGTH];
  UINT64                        AcpiGuidPart1;
  UINT64                        AcpiGuidPart2;
  CHAR16                        LocalGuidString[GUID_CHARS_NUMBER];
  UINT8                         SerialIoIndex;
  UINT8                         PepSerialIoI2c[PCH_MAX_SERIALIO_I2C_CONTROLLERS];
  UINT8                         PepSerialIoSpi[PCH_MAX_SERIALIO_SPI_CONTROLLERS];
  UINT8                         PepSerialIoUart[PCH_MAX_SERIALIO_UART_CONTROLLERS];

  Handle        = NULL;

  AsmCpuid (
    1,
    &CpuidRegs.RegEax,
    &CpuidRegs.RegEbx,
    &CpuidRegs.RegEcx,
    &CpuidRegs.RegEdx
    );
  //
  // Locate the setup configuration data
  // We assert if it is not found because we have a dependency on PlatformCpu,
  // published by the platform setup driver.
  // This should ensure that we only get called after the setup has updated the
  // variable.
  //
  VarDataSize = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  NULL,
                  &VarDataSize,
                  &mSystemConfiguration
                  );

  VarDataSize = sizeof (SA_SETUP);
  Status = gRT->GetVariable (
                  L"SaSetup",
                  &gSaSetupVariableGuid,
                  NULL,
                  &VarDataSize,
                  &SaSetup
                  );

  VarDataSize = sizeof (ME_SETUP);
  Status = gRT->GetVariable (
                  L"MeSetup",
                  &gMeSetupVariableGuid,
                  NULL,
                  &VarDataSize,
                  &mMeSetup
                  );

  VarDataSize = sizeof (CPU_SETUP);
  Status = gRT->GetVariable (
                  L"CpuSetup",
                  &gCpuSetupVariableGuid,
                  NULL,
                  &VarDataSize,
                  &CpuSetup
                  );

  VarDataSize = sizeof (PCH_SETUP);
  Status = gRT->GetVariable (
                  L"PchSetup",
                  &gPchSetupVariableGuid,
                  NULL,
                  &VarDataSize,
                  &mPchSetup
                  );
  //
  // Locate the MP services protocol
  // Find the MP Protocol. This is an MP platform, so MP protocol must be there.
  //
  Status = gBS->LocateProtocol (
                  &gEfiMpServiceProtocolGuid,
                  NULL,
                  (VOID **) &MpService
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Determine the number of processors
  //
  MpService->GetNumberOfProcessors (
              MpService,
              &NumberOfCPUs,
              &NumberOfEnabledCPUs
              );

  //
  // Allocate and initialize the NVS area for SMM and ASL communication.
  //
  AcpiGnvsInit((VOID **) &mPlatformNvsAreaProtocol.Area);

  //
  // Allocate and initialize NVS area for pointer to PTCT table
  //
  if (IsRtSku ()) {
    InstallAcpiPtct ();
  }

  //
  // Update global NVS area for ASL and SMM init code to use
  //
  //mPlatformNvsAreaProtocol.Area->EnableThermalOffset        = mSystemConfiguration.EnableThermalOffset;
  mPlatformNvsAreaProtocol.Area->Ac1TripPoint                 = mSystemConfiguration.Ac1TripPoint;
  mPlatformNvsAreaProtocol.Area->Ac0TripPoint                 = mSystemConfiguration.Ac0TripPoint;
  mPlatformNvsAreaProtocol.Area->Ac1FanSpeed                  = mSystemConfiguration.Ac1FanSpeed;
  mPlatformNvsAreaProtocol.Area->Ac0FanSpeed                  = mSystemConfiguration.Ac0FanSpeed;
  mPlatformNvsAreaProtocol.Area->PassiveThermalTripPoint      = mSystemConfiguration.PassiveThermalTripPoint;
  mPlatformNvsAreaProtocol.Area->PassiveTc1Value              = mSystemConfiguration.PassiveTc1Value;
  mPlatformNvsAreaProtocol.Area->PassiveTc2Value              = mSystemConfiguration.PassiveTc2Value;
  mPlatformNvsAreaProtocol.Area->PassiveTspValue              = mSystemConfiguration.PassiveTspValue;
  mPlatformNvsAreaProtocol.Area->CriticalThermalTripPoint     = mSystemConfiguration.CriticalThermalTripPoint;
  mPlatformNvsAreaProtocol.Area->EmaEnable                    = 0; //mSystemConfiguration.EmaEnable; //todo
  mPlatformNvsAreaProtocol.Area->ThreadCount                  = (UINT8) NumberOfEnabledCPUs;
  mPlatformNvsAreaProtocol.Area->MefEnable                    = 0; //mSystemConfiguration.MefEnable; //todo

  //
  // DPTF Devices and trip points
  //
  mPlatformNvsAreaProtocol.Area->EnableDptf                   = mSystemConfiguration.EnableDptf;

  if (mSystemConfiguration.EnableDptf == 1) {

    mPlatformNvsAreaProtocol.Area->EnableDCFG                   = mSystemConfiguration.EnableDCFG;
    mPlatformNvsAreaProtocol.Area->EnableSaDevice               = mSystemConfiguration.EnableSaDevice;
    mPlatformNvsAreaProtocol.Area->ActiveThermalTripPointSA     = mSystemConfiguration.ActiveThermalTripPointSA;
    mPlatformNvsAreaProtocol.Area->PassiveThermalTripPointSA    = mSystemConfiguration.PassiveThermalTripPointSA;
    mPlatformNvsAreaProtocol.Area->CriticalThermalTripPointSA   = mSystemConfiguration.CriticalThermalTripPointSA;
    mPlatformNvsAreaProtocol.Area->CriticalThermalTripPointSaS3 = mSystemConfiguration.CriticalThermalTripPointSaS3;
    mPlatformNvsAreaProtocol.Area->HotThermalTripPointSA        = mSystemConfiguration.HotThermalTripPointSA;
    mPlatformNvsAreaProtocol.Area->ThermalSamplingPeriodSA      = mSystemConfiguration.ThermalSamplingPeriodSA;
    mPlatformNvsAreaProtocol.Area->PpccStepSize                 = mSystemConfiguration.PpccStepSize;
    mPlatformNvsAreaProtocol.Area->MinPowerLimit0               = mSystemConfiguration.MinPowerLimit0;
    mPlatformNvsAreaProtocol.Area->MinPowerLimit1               = mSystemConfiguration.MinPowerLimit1;
    mPlatformNvsAreaProtocol.Area->MinPowerLimit2               = mSystemConfiguration.MinPowerLimit2;

    //
    // DPTF Policies
    //
    CtdpLevels = (UINT8) (RShiftU64(AsmReadMsr64(MSR_PLATFORM_INFO),33) & 0x03);
    if ((CtdpLevels == 1) || (CtdpLevels == 2)) {
      mPlatformNvsAreaProtocol.Area->EnableCtdpPolicy             = mSystemConfiguration.EnableCtdpPolicy;
    } else {
      mPlatformNvsAreaProtocol.Area->EnableCtdpPolicy             = 0;
    }

    //
    // DPTF Devices and trip points
    //
    mPlatformNvsAreaProtocol.Area->EnableFan1Device             = mSystemConfiguration.EnableFan1Device;

    //
    // DPTF Policies
    //
    mPlatformNvsAreaProtocol.Area->EnableActivePolicy           = mSystemConfiguration.EnableActivePolicy;
    mPlatformNvsAreaProtocol.Area->EnablePassivePolicy          = mSystemConfiguration.EnablePassivePolicy;
    mPlatformNvsAreaProtocol.Area->EnableCriticalPolicy         = mSystemConfiguration.EnableCriticalPolicy;
    mPlatformNvsAreaProtocol.Area->TrtRevision                  = mSystemConfiguration.TrtRevision;
    mPlatformNvsAreaProtocol.Area->EnableAPPolicy               = mSystemConfiguration.EnableAPPolicy;
    mPlatformNvsAreaProtocol.Area->EnablePIDPolicy              = mSystemConfiguration.EnablePIDPolicy;

    mPlatformNvsAreaProtocol.Area->OemDesignVariable0           = mSystemConfiguration.OemDesignVariable0;
    mPlatformNvsAreaProtocol.Area->OemDesignVariable1           = mSystemConfiguration.OemDesignVariable1;
    mPlatformNvsAreaProtocol.Area->OemDesignVariable2           = mSystemConfiguration.OemDesignVariable2;
    mPlatformNvsAreaProtocol.Area->OemDesignVariable3           = mSystemConfiguration.OemDesignVariable3;
    mPlatformNvsAreaProtocol.Area->OemDesignVariable4           = mSystemConfiguration.OemDesignVariable4;
    mPlatformNvsAreaProtocol.Area->OemDesignVariable5           = mSystemConfiguration.OemDesignVariable5;

    //
    // CLPO (Current Logical Processor Off lining Setting)
    //
    mPlatformNvsAreaProtocol.Area->LPOEnable                    = mSystemConfiguration.LPOEnable;
    mPlatformNvsAreaProtocol.Area->LPOStartPState               = mSystemConfiguration.LPOStartPState;
    mPlatformNvsAreaProtocol.Area->LPOStepSize                  = mSystemConfiguration.LPOStepSize;
    mPlatformNvsAreaProtocol.Area->LPOPowerControlSetting       = mSystemConfiguration.LPOPowerControlSetting;
    mPlatformNvsAreaProtocol.Area->LPOPerformanceControlSetting = mSystemConfiguration.LPOPerformanceControlSetting;

    mPlatformNvsAreaProtocol.Area->EnableDisplayParticipant     = mSystemConfiguration.EnableDisplayParticipant;
    mPlatformNvsAreaProtocol.Area->DisplayDepthLowerLimit       = mSystemConfiguration.DisplayDepthLowerLimit;
    mPlatformNvsAreaProtocol.Area->DisplayDepthUpperLimit       = mSystemConfiguration.DisplayDepthUpperLimit;

    mPlatformNvsAreaProtocol.Area->EnableChargerParticipant     = mSystemConfiguration.EnableChargerParticipant;
    mPlatformNvsAreaProtocol.Area->EnablePowerParticipant       = mSystemConfiguration.EnablePowerParticipant;
    mPlatformNvsAreaProtocol.Area->PowerParticipantPollingRate  = mSystemConfiguration.PowerParticipantPollingRate;
    mPlatformNvsAreaProtocol.Area->EnablePowerBossPolicy        = mSystemConfiguration.EnablePowerBossPolicy;

    mPlatformNvsAreaProtocol.Area->Enable2DCameraParticipant      = mSystemConfiguration.Enable2DCameraParticipant;

    mPlatformNvsAreaProtocol.Area->EnableBatteryParticipant      = mSystemConfiguration.EnableBatteryParticipant;

    mPlatformNvsAreaProtocol.Area->EnableVSPolicy               = mSystemConfiguration.EnableVSPolicy;

    mPlatformNvsAreaProtocol.Area->EnableVS1Participant          = mSystemConfiguration.EnableVS1Participant;
    mPlatformNvsAreaProtocol.Area->ActiveThermalTripPointVS1     = mSystemConfiguration.ActiveThermalTripPointVS1;
    mPlatformNvsAreaProtocol.Area->PassiveThermalTripPointVS1    = mSystemConfiguration.PassiveThermalTripPointVS1;
    mPlatformNvsAreaProtocol.Area->CriticalThermalTripPointVS1   = mSystemConfiguration.CriticalThermalTripPointVS1;
    mPlatformNvsAreaProtocol.Area->CriticalThermalTripPointVS1S3 = mSystemConfiguration.CriticalThermalTripPointVS1S3;
    mPlatformNvsAreaProtocol.Area->HotThermalTripPointVS1        = mSystemConfiguration.HotThermalTripPointVS1;

    mPlatformNvsAreaProtocol.Area->EnableVS2Participant          = mSystemConfiguration.EnableVS2Participant;
    mPlatformNvsAreaProtocol.Area->ActiveThermalTripPointVS2     = mSystemConfiguration.ActiveThermalTripPointVS2;
    mPlatformNvsAreaProtocol.Area->PassiveThermalTripPointVS2    = mSystemConfiguration.PassiveThermalTripPointVS2;
    mPlatformNvsAreaProtocol.Area->CriticalThermalTripPointVS2   = mSystemConfiguration.CriticalThermalTripPointVS2;
    mPlatformNvsAreaProtocol.Area->CriticalThermalTripPointVS2S3 = mSystemConfiguration.CriticalThermalTripPointVS2S3;
    mPlatformNvsAreaProtocol.Area->HotThermalTripPointVS2        = mSystemConfiguration.HotThermalTripPointVS2;

    mPlatformNvsAreaProtocol.Area->EnableStorageParticipantST1   = mSystemConfiguration.EnableStorageParticipantST1;
    mPlatformNvsAreaProtocol.Area->ActiveThermalTripPointST1     = mSystemConfiguration.ActiveThermalTripPointST1;
    mPlatformNvsAreaProtocol.Area->PassiveThermalTripPointST1    = mSystemConfiguration.PassiveThermalTripPointST1;
    mPlatformNvsAreaProtocol.Area->CriticalThermalTripPointST1   = mSystemConfiguration.CriticalThermalTripPointST1;
    mPlatformNvsAreaProtocol.Area->CriticalThermalTripPointS3ST1 = mSystemConfiguration.CriticalThermalTripPointS3ST1;
    mPlatformNvsAreaProtocol.Area->HotThermalTripPointST1        = mSystemConfiguration.HotThermalTripPointST1;
    mPlatformNvsAreaProtocol.Area->EnableStorageParticipantST2   = mSystemConfiguration.EnableStorageParticipantST2;
    mPlatformNvsAreaProtocol.Area->ActiveThermalTripPointST2     = mSystemConfiguration.ActiveThermalTripPointST2;
    mPlatformNvsAreaProtocol.Area->PassiveThermalTripPointST2    = mSystemConfiguration.PassiveThermalTripPointST2;
    mPlatformNvsAreaProtocol.Area->CriticalThermalTripPointST2   = mSystemConfiguration.CriticalThermalTripPointST2;
    mPlatformNvsAreaProtocol.Area->CriticalThermalTripPointS3ST2 = mSystemConfiguration.CriticalThermalTripPointS3ST2;
    mPlatformNvsAreaProtocol.Area->HotThermalTripPointST2        = mSystemConfiguration.HotThermalTripPointST2;

    mPlatformNvsAreaProtocol.Area->EnableRFIMPolicy              = mSystemConfiguration.EnableRFIMPolicy;

    mPlatformNvsAreaProtocol.Area->EnableWWANParticipant        = mSystemConfiguration.EnableWWANParticipant;
    mPlatformNvsAreaProtocol.Area->ActiveThermalTripPointWWAN   = mSystemConfiguration.ActiveThermalTripPointWWAN;
    mPlatformNvsAreaProtocol.Area->PassiveThermalTripPointWWAN  = mSystemConfiguration.PassiveThermalTripPointWWAN;
    mPlatformNvsAreaProtocol.Area->CriticalThermalTripPointWWAN = mSystemConfiguration.CriticalThermalTripPointWWAN;
    mPlatformNvsAreaProtocol.Area->CriticalThermalTripPointWwanS3 = mSystemConfiguration.CriticalThermalTripPointWwanS3;
    mPlatformNvsAreaProtocol.Area->HotThermalTripPointWWAN      = mSystemConfiguration.HotThermalTripPointWWAN;

    mPlatformNvsAreaProtocol.Area->EnableWrlsParticipant        = mSystemConfiguration.EnableWrlsParticipant;
    mPlatformNvsAreaProtocol.Area->ActiveThermalTripPointWrls   = mSystemConfiguration.ActiveThermalTripPointWrls;
    mPlatformNvsAreaProtocol.Area->PassiveThermalTripPointWrls  = mSystemConfiguration.PassiveThermalTripPointWrls;
    mPlatformNvsAreaProtocol.Area->CriticalThermalTripPointWrls = mSystemConfiguration.CriticalThermalTripPointWrls;
    mPlatformNvsAreaProtocol.Area->CriticalThermalTripPointWrlsS3 = mSystemConfiguration.CriticalThermalTripPointWrlsS3;
    mPlatformNvsAreaProtocol.Area->HotThermalTripPointWrls      = mSystemConfiguration.HotThermalTripPointWrls;
    mPlatformNvsAreaProtocol.Area->ThermalSamplingPeriodWrls    = mSystemConfiguration.ThermalSamplingPeriodWrls;

    mPlatformNvsAreaProtocol.Area->EnableSen1Participant        = mSystemConfiguration.EnableSen1Participant;
    mPlatformNvsAreaProtocol.Area->ActiveThermalTripPointSen1   = mSystemConfiguration.ActiveThermalTripPointSen1;
    mPlatformNvsAreaProtocol.Area->PassiveThermalTripPointSen1  = mSystemConfiguration.PassiveThermalTripPointSen1;
    mPlatformNvsAreaProtocol.Area->CriticalThermalTripPointSen1 = mSystemConfiguration.CriticalThermalTripPointSen1;
    mPlatformNvsAreaProtocol.Area->CriticalThermalTripPointSen1S3 = mSystemConfiguration.CriticalThermalTripPointSen1S3;
    mPlatformNvsAreaProtocol.Area->HotThermalTripPointSen1      = mSystemConfiguration.HotThermalTripPointSen1;
    mPlatformNvsAreaProtocol.Area->SensorSamplingPeriodSen1     = mSystemConfiguration.SensorSamplingPeriodSen1;

    mPlatformNvsAreaProtocol.Area->EnableSen2Participant        = mSystemConfiguration.EnableSen2Participant;
    mPlatformNvsAreaProtocol.Area->ActiveThermalTripPointSen2   = mSystemConfiguration.ActiveThermalTripPointSen2;
    mPlatformNvsAreaProtocol.Area->PassiveThermalTripPointSen2  = mSystemConfiguration.PassiveThermalTripPointSen2;
    mPlatformNvsAreaProtocol.Area->CriticalThermalTripPointSen2 = mSystemConfiguration.CriticalThermalTripPointSen2;
    mPlatformNvsAreaProtocol.Area->CriticalThermalTripPointSen2S3 = mSystemConfiguration.CriticalThermalTripPointSen2S3;
    mPlatformNvsAreaProtocol.Area->HotThermalTripPointSen2      = mSystemConfiguration.HotThermalTripPointSen2;
    mPlatformNvsAreaProtocol.Area->SensorSamplingPeriodSen2     = mSystemConfiguration.SensorSamplingPeriodSen2;

    mPlatformNvsAreaProtocol.Area->EnableSen3Participant        = mSystemConfiguration.EnableSen3Participant;
    mPlatformNvsAreaProtocol.Area->ActiveThermalTripPointSen3   = mSystemConfiguration.ActiveThermalTripPointSen3;
    mPlatformNvsAreaProtocol.Area->PassiveThermalTripPointSen3  = mSystemConfiguration.PassiveThermalTripPointSen3;
    mPlatformNvsAreaProtocol.Area->CriticalThermalTripPointSen3 = mSystemConfiguration.CriticalThermalTripPointSen3;
    mPlatformNvsAreaProtocol.Area->CriticalThermalTripPointSen3S3 = mSystemConfiguration.CriticalThermalTripPointSen3S3;
    mPlatformNvsAreaProtocol.Area->HotThermalTripPointSen3      = mSystemConfiguration.HotThermalTripPointSen3;
    mPlatformNvsAreaProtocol.Area->SensorSamplingPeriodSen3     = mSystemConfiguration.SensorSamplingPeriodSen3;

    mPlatformNvsAreaProtocol.Area->EnableSen4Participant        = mSystemConfiguration.EnableSen4Participant;
    mPlatformNvsAreaProtocol.Area->ActiveThermalTripPointSen4   = mSystemConfiguration.ActiveThermalTripPointSen4;
    mPlatformNvsAreaProtocol.Area->PassiveThermalTripPointSen4  = mSystemConfiguration.PassiveThermalTripPointSen4;
    mPlatformNvsAreaProtocol.Area->CriticalThermalTripPointSen4 = mSystemConfiguration.CriticalThermalTripPointSen4;
    mPlatformNvsAreaProtocol.Area->CriticalThermalTripPointSen4S3 = mSystemConfiguration.CriticalThermalTripPointSen4S3;
    mPlatformNvsAreaProtocol.Area->HotThermalTripPointSen4      = mSystemConfiguration.HotThermalTripPointSen4;
    mPlatformNvsAreaProtocol.Area->SensorSamplingPeriodSen4     = mSystemConfiguration.SensorSamplingPeriodSen4;

    mPlatformNvsAreaProtocol.Area->EnableSen5Participant        = mSystemConfiguration.EnableSen5Participant;
    mPlatformNvsAreaProtocol.Area->ActiveThermalTripPointSen5   = mSystemConfiguration.ActiveThermalTripPointSen5;
    mPlatformNvsAreaProtocol.Area->PassiveThermalTripPointSen5  = mSystemConfiguration.PassiveThermalTripPointSen5;
    mPlatformNvsAreaProtocol.Area->CriticalThermalTripPointSen5 = mSystemConfiguration.CriticalThermalTripPointSen5;
    mPlatformNvsAreaProtocol.Area->CriticalThermalTripPointSen5S3 = mSystemConfiguration.CriticalThermalTripPointSen5S3;
    mPlatformNvsAreaProtocol.Area->HotThermalTripPointSen5      = mSystemConfiguration.HotThermalTripPointSen5;
    mPlatformNvsAreaProtocol.Area->SensorSamplingPeriodSen5     = mSystemConfiguration.SensorSamplingPeriodSen5;

  }

  mPlatformNvsAreaProtocol.Area->HebcValue               = mSystemConfiguration.HebcValue;

  //
  // BIOS only version of CTDP. (CTDP without using DPTF)
  //
  if (CpuSetup.ConfigTdpLock == 1 || mSystemConfiguration.EnableDptf == 1) {
    mPlatformNvsAreaProtocol.Area->ConfigTdpBios      = 0;
  } else {
    mPlatformNvsAreaProtocol.Area->ConfigTdpBios      = CpuSetup.ConfigTdpBios;
  }

  //
  // PECI Access Method
  //
  mPlatformNvsAreaProtocol.Area->PeciAccessMethod     = mSystemConfiguration.PeciAccessMethod;

  //
  // Wireless support
  //
  mPlatformNvsAreaProtocol.Area->PowerSharingManagerEnable  = mSystemConfiguration.PowerSharingManagerEnable;
  mPlatformNvsAreaProtocol.Area->PsmSplcDomainType1         = mSystemConfiguration.PsmSplcDomainType1;
  mPlatformNvsAreaProtocol.Area->PsmSplcPowerLimit1         = mSystemConfiguration.PsmSplcPowerLimit1;
  mPlatformNvsAreaProtocol.Area->PsmSplcTimeWindow1         = mSystemConfiguration.PsmSplcTimeWindow1;

  mPlatformNvsAreaProtocol.Area->PsmDplcDomainType1         = mSystemConfiguration.PsmDplcDomainType1;
  mPlatformNvsAreaProtocol.Area->PsmDplcDomainPreference1   = mSystemConfiguration.PsmDplcDomainPreference1;
  mPlatformNvsAreaProtocol.Area->PsmDplcPowerLimitIndex1    = mSystemConfiguration.PsmDplcPowerLimitIndex1;
  mPlatformNvsAreaProtocol.Area->PsmDplcDefaultPowerLimit1  = mSystemConfiguration.PsmDplcDefaultPowerLimit1;
  mPlatformNvsAreaProtocol.Area->PsmDplcDefaultTimeWindow1  = mSystemConfiguration.PsmDplcDefaultTimeWindow1;
  mPlatformNvsAreaProtocol.Area->PsmDplcMinimumPowerLimit1  = mSystemConfiguration.PsmDplcMinimumPowerLimit1;
  mPlatformNvsAreaProtocol.Area->PsmDplcMaximumPowerLimit1  = mSystemConfiguration.PsmDplcMaximumPowerLimit1;
  mPlatformNvsAreaProtocol.Area->PsmDplcMaximumTimeWindow1  = mSystemConfiguration.PsmDplcMaximumTimeWindow1;

  mPlatformNvsAreaProtocol.Area->WifiEnable                = mSystemConfiguration.WifiEnable;
  if (mSystemConfiguration.WifiEnable == 1) {
    mPlatformNvsAreaProtocol.Area->WifiDomainType1         = mSystemConfiguration.WifiDomainType1;
    mPlatformNvsAreaProtocol.Area->WifiPowerLimit1         = mSystemConfiguration.WifiPowerLimit1;
    mPlatformNvsAreaProtocol.Area->WifiTimeWindow1         = mSystemConfiguration.WifiTimeWindow1;
    mPlatformNvsAreaProtocol.Area->TRxDelay0               = mSystemConfiguration.TRxDelay0;
    mPlatformNvsAreaProtocol.Area->TRxCableLength0         = mSystemConfiguration.TRxCableLength0;
    mPlatformNvsAreaProtocol.Area->TRxDelay1               = mSystemConfiguration.TRxDelay1;
    mPlatformNvsAreaProtocol.Area->TRxCableLength1         = mSystemConfiguration.TRxCableLength1;
    mPlatformNvsAreaProtocol.Area->WrddDomainType1         = mSystemConfiguration.WrddDomainType1;
    mPlatformNvsAreaProtocol.Area->WrddCountryIndentifier1 = mSystemConfiguration.WrddCountryIndentifier1;
    mPlatformNvsAreaProtocol.Area->WrdsWiFiSarEnable       = mSystemConfiguration.WrdsWiFiSarEnable;
    mPlatformNvsAreaProtocol.Area->AntennaDiversity        = mSystemConfiguration.AntennaDiversity;

    if (mPlatformNvsAreaProtocol.Area->WrdsWiFiSarEnable == 1) {
      mPlatformNvsAreaProtocol.Area->WrdsWiFiSarTxPowerSet1Limit1  = mSystemConfiguration.WrdsWiFiSarTxPowerSet1Limit1;
      mPlatformNvsAreaProtocol.Area->WrdsWiFiSarTxPowerSet1Limit2  = mSystemConfiguration.WrdsWiFiSarTxPowerSet1Limit2;
      mPlatformNvsAreaProtocol.Area->WrdsWiFiSarTxPowerSet1Limit3  = mSystemConfiguration.WrdsWiFiSarTxPowerSet1Limit3;
      mPlatformNvsAreaProtocol.Area->WrdsWiFiSarTxPowerSet1Limit4  = mSystemConfiguration.WrdsWiFiSarTxPowerSet1Limit4;
      mPlatformNvsAreaProtocol.Area->WrdsWiFiSarTxPowerSet1Limit5  = mSystemConfiguration.WrdsWiFiSarTxPowerSet1Limit5;
      mPlatformNvsAreaProtocol.Area->WrdsWiFiSarTxPowerSet1Limit6  = mSystemConfiguration.WrdsWiFiSarTxPowerSet1Limit6;
      mPlatformNvsAreaProtocol.Area->WrdsWiFiSarTxPowerSet1Limit7  = mSystemConfiguration.WrdsWiFiSarTxPowerSet1Limit7;
      mPlatformNvsAreaProtocol.Area->WrdsWiFiSarTxPowerSet1Limit8  = mSystemConfiguration.WrdsWiFiSarTxPowerSet1Limit8;
      mPlatformNvsAreaProtocol.Area->WrdsWiFiSarTxPowerSet1Limit9  = mSystemConfiguration.WrdsWiFiSarTxPowerSet1Limit9;
      mPlatformNvsAreaProtocol.Area->WrdsWiFiSarTxPowerSet1Limit10 = mSystemConfiguration.WrdsWiFiSarTxPowerSet1Limit10;
    } else {
      mPlatformNvsAreaProtocol.Area->WrdsWiFiSarTxPowerSet1Limit1  = 0x0;
      mPlatformNvsAreaProtocol.Area->WrdsWiFiSarTxPowerSet1Limit2  = 0x0;
      mPlatformNvsAreaProtocol.Area->WrdsWiFiSarTxPowerSet1Limit3  = 0x0;
      mPlatformNvsAreaProtocol.Area->WrdsWiFiSarTxPowerSet1Limit4  = 0x0;
      mPlatformNvsAreaProtocol.Area->WrdsWiFiSarTxPowerSet1Limit5  = 0x0;
      mPlatformNvsAreaProtocol.Area->WrdsWiFiSarTxPowerSet1Limit6  = 0x0;
      mPlatformNvsAreaProtocol.Area->WrdsWiFiSarTxPowerSet1Limit7  = 0x0;
      mPlatformNvsAreaProtocol.Area->WrdsWiFiSarTxPowerSet1Limit8  = 0x0;
      mPlatformNvsAreaProtocol.Area->WrdsWiFiSarTxPowerSet1Limit9  = 0x0;
      mPlatformNvsAreaProtocol.Area->WrdsWiFiSarTxPowerSet1Limit10 = 0x0;
    }

    mPlatformNvsAreaProtocol.Area->EwrdWiFiDynamicSarEnable = mSystemConfiguration.EwrdWiFiDynamicSarEnable;
    mPlatformNvsAreaProtocol.Area->EwrdWiFiDynamicSarRangeSets = mSystemConfiguration.EwrdWiFiDynamicSarRangeSets;
    if (mPlatformNvsAreaProtocol.Area->EwrdWiFiDynamicSarEnable == 1) {
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet2Limit1  = mSystemConfiguration.EwrdWiFiSarTxPowerSet2Limit1;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet2Limit2  = mSystemConfiguration.EwrdWiFiSarTxPowerSet2Limit2;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet2Limit3  = mSystemConfiguration.EwrdWiFiSarTxPowerSet2Limit3;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet2Limit4  = mSystemConfiguration.EwrdWiFiSarTxPowerSet2Limit4;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet2Limit5  = mSystemConfiguration.EwrdWiFiSarTxPowerSet2Limit5;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet2Limit6  = mSystemConfiguration.EwrdWiFiSarTxPowerSet2Limit6;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet2Limit7  = mSystemConfiguration.EwrdWiFiSarTxPowerSet2Limit7;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet2Limit8  = mSystemConfiguration.EwrdWiFiSarTxPowerSet2Limit8;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet2Limit9  = mSystemConfiguration.EwrdWiFiSarTxPowerSet2Limit9;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet2Limit10 = mSystemConfiguration.EwrdWiFiSarTxPowerSet2Limit10;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet3Limit1  = mSystemConfiguration.EwrdWiFiSarTxPowerSet3Limit1;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet3Limit2  = mSystemConfiguration.EwrdWiFiSarTxPowerSet3Limit2;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet3Limit3  = mSystemConfiguration.EwrdWiFiSarTxPowerSet3Limit3;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet3Limit4  = mSystemConfiguration.EwrdWiFiSarTxPowerSet3Limit4;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet3Limit5  = mSystemConfiguration.EwrdWiFiSarTxPowerSet3Limit5;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet3Limit6  = mSystemConfiguration.EwrdWiFiSarTxPowerSet3Limit6;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet3Limit7  = mSystemConfiguration.EwrdWiFiSarTxPowerSet3Limit7;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet3Limit8  = mSystemConfiguration.EwrdWiFiSarTxPowerSet3Limit8;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet3Limit9  = mSystemConfiguration.EwrdWiFiSarTxPowerSet3Limit9;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet3Limit10 = mSystemConfiguration.EwrdWiFiSarTxPowerSet3Limit10;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet4Limit1  = mSystemConfiguration.EwrdWiFiSarTxPowerSet4Limit1;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet4Limit2  = mSystemConfiguration.EwrdWiFiSarTxPowerSet4Limit2;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet4Limit3  = mSystemConfiguration.EwrdWiFiSarTxPowerSet4Limit3;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet4Limit4  = mSystemConfiguration.EwrdWiFiSarTxPowerSet4Limit4;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet4Limit5  = mSystemConfiguration.EwrdWiFiSarTxPowerSet4Limit5;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet4Limit6  = mSystemConfiguration.EwrdWiFiSarTxPowerSet4Limit6;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet4Limit7  = mSystemConfiguration.EwrdWiFiSarTxPowerSet4Limit7;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet4Limit8  = mSystemConfiguration.EwrdWiFiSarTxPowerSet4Limit8;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet4Limit9  = mSystemConfiguration.EwrdWiFiSarTxPowerSet4Limit9;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet4Limit10 = mSystemConfiguration.EwrdWiFiSarTxPowerSet4Limit10;
    } else {
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet2Limit1  = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet2Limit2  = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet2Limit3  = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet2Limit4  = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet2Limit5  = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet2Limit6  = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet2Limit7  = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet2Limit8  = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet2Limit9  = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet2Limit10 = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet3Limit1  = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet3Limit2  = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet3Limit3  = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet3Limit4  = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet3Limit5  = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet3Limit6  = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet3Limit7  = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet3Limit8  = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet3Limit9  = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet3Limit10 = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet4Limit1  = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet4Limit2  = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet4Limit3  = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet4Limit4  = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet4Limit5  = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet4Limit6  = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet4Limit7  = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet4Limit8  = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet4Limit9  = 0x0;
        mPlatformNvsAreaProtocol.Area->EwrdWiFiSarTxPowerSet4Limit10 = 0x0;
    }
    mPlatformNvsAreaProtocol.Area->WiFiDynamicSarAntennaACurrentSet = mSystemConfiguration.WiFiDynamicSarAntennaACurrentSet;
    mPlatformNvsAreaProtocol.Area->WiFiDynamicSarAntennaBCurrentSet = mSystemConfiguration.WiFiDynamicSarAntennaBCurrentSet;
    mPlatformNvsAreaProtocol.Area->WgdsWiFiSarDeltaGroup1PowerMax1    = mSystemConfiguration.WgdsWiFiSarDeltaGroup1PowerMax1;
    mPlatformNvsAreaProtocol.Area->WgdsWiFiSarDeltaGroup1PowerChainA1 = mSystemConfiguration.WgdsWiFiSarDeltaGroup1PowerChainA1;
    mPlatformNvsAreaProtocol.Area->WgdsWiFiSarDeltaGroup1PowerChainB1 = mSystemConfiguration.WgdsWiFiSarDeltaGroup1PowerChainB1;
    mPlatformNvsAreaProtocol.Area->WgdsWiFiSarDeltaGroup1PowerMax2    = mSystemConfiguration.WgdsWiFiSarDeltaGroup1PowerMax2;
    mPlatformNvsAreaProtocol.Area->WgdsWiFiSarDeltaGroup1PowerChainA2 = mSystemConfiguration.WgdsWiFiSarDeltaGroup1PowerChainA2;
    mPlatformNvsAreaProtocol.Area->WgdsWiFiSarDeltaGroup1PowerChainB2 = mSystemConfiguration.WgdsWiFiSarDeltaGroup1PowerChainB2;
    mPlatformNvsAreaProtocol.Area->WgdsWiFiSarDeltaGroup2PowerMax1    = mSystemConfiguration.WgdsWiFiSarDeltaGroup2PowerMax1;
    mPlatformNvsAreaProtocol.Area->WgdsWiFiSarDeltaGroup2PowerChainA1 = mSystemConfiguration.WgdsWiFiSarDeltaGroup2PowerChainA1;
    mPlatformNvsAreaProtocol.Area->WgdsWiFiSarDeltaGroup2PowerChainB1 = mSystemConfiguration.WgdsWiFiSarDeltaGroup2PowerChainB1;
    mPlatformNvsAreaProtocol.Area->WgdsWiFiSarDeltaGroup2PowerMax2    = mSystemConfiguration.WgdsWiFiSarDeltaGroup2PowerMax2;
    mPlatformNvsAreaProtocol.Area->WgdsWiFiSarDeltaGroup2PowerChainA2 = mSystemConfiguration.WgdsWiFiSarDeltaGroup2PowerChainA2;
    mPlatformNvsAreaProtocol.Area->WgdsWiFiSarDeltaGroup2PowerChainB2 = mSystemConfiguration.WgdsWiFiSarDeltaGroup2PowerChainB2;
    mPlatformNvsAreaProtocol.Area->WgdsWiFiSarDeltaGroup3PowerMax1    = mSystemConfiguration.WgdsWiFiSarDeltaGroup3PowerMax1;
    mPlatformNvsAreaProtocol.Area->WgdsWiFiSarDeltaGroup3PowerChainA1 = mSystemConfiguration.WgdsWiFiSarDeltaGroup3PowerChainA1;
    mPlatformNvsAreaProtocol.Area->WgdsWiFiSarDeltaGroup3PowerChainB1 = mSystemConfiguration.WgdsWiFiSarDeltaGroup3PowerChainB1;
    mPlatformNvsAreaProtocol.Area->WgdsWiFiSarDeltaGroup3PowerMax2    = mSystemConfiguration.WgdsWiFiSarDeltaGroup3PowerMax2;
    mPlatformNvsAreaProtocol.Area->WgdsWiFiSarDeltaGroup3PowerChainA2 = mSystemConfiguration.WgdsWiFiSarDeltaGroup3PowerChainA2;
    mPlatformNvsAreaProtocol.Area->WgdsWiFiSarDeltaGroup3PowerChainB2 = mSystemConfiguration.WgdsWiFiSarDeltaGroup3PowerChainB2;

    mPlatformNvsAreaProtocol.Area->BluetoothSar = mSystemConfiguration.BluetoothSar;
    if (mPlatformNvsAreaProtocol.Area->BluetoothSar == 1) {
      mPlatformNvsAreaProtocol.Area->BluetoothSarBr     = mSystemConfiguration.BluetoothSarBr;
      mPlatformNvsAreaProtocol.Area->BluetoothSarEdr2   = mSystemConfiguration.BluetoothSarEdr2;
      mPlatformNvsAreaProtocol.Area->BluetoothSarEdr3   = mSystemConfiguration.BluetoothSarEdr3;
      mPlatformNvsAreaProtocol.Area->BluetoothSarLe     = mSystemConfiguration.BluetoothSarLe;
      mPlatformNvsAreaProtocol.Area->BluetoothSarLe2Mhz = mSystemConfiguration.BluetoothSarLe2Mhz;
      mPlatformNvsAreaProtocol.Area->BluetoothSarLeLr   = mSystemConfiguration.BluetoothSarLeLr;
    } else {
      mPlatformNvsAreaProtocol.Area->BluetoothSarBr     = 0x0;
      mPlatformNvsAreaProtocol.Area->BluetoothSarEdr2   = 0x0;
      mPlatformNvsAreaProtocol.Area->BluetoothSarEdr3   = 0x0;
      mPlatformNvsAreaProtocol.Area->BluetoothSarLe     = 0x0;
      mPlatformNvsAreaProtocol.Area->BluetoothSarLe2Mhz = 0x0;
      mPlatformNvsAreaProtocol.Area->BluetoothSarLeLr   = 0x0;
    }
  }

  mPlatformNvsAreaProtocol.Area->SystemTimeAndAlarmSource = mSystemConfiguration.SystemTimeAndAlarmSource;
  mPlatformNvsAreaProtocol.Area->CoExistenceManager = mSystemConfiguration.CoExistenceManager;
  mPlatformNvsAreaProtocol.Area->XdciFnEnable       = mPchSetup.PchXdciSupport;
  //
  // Initilize platform ID in Global NVS Area
  //
  mPlatformNvsAreaProtocol.Area->GenerationId   = PcdGet8 (PcdPlatformGeneration);
  mPlatformNvsAreaProtocol.Area->PlatformFlavor = PcdGet8 (PcdPlatformFlavor);
  mPlatformNvsAreaProtocol.Area->BoardRev       = PcdGet16 (PcdBoardRev);
  mPlatformNvsAreaProtocol.Area->BoardType      = PcdGet8 (PcdBoardType);


  mPlatformNvsAreaProtocol.Area->Rtd3Support                = mSystemConfiguration.Rtd3Support;
  mPlatformNvsAreaProtocol.Area->Rtd3P0dl                   = mSystemConfiguration.Rtd3P0dl;
  mPlatformNvsAreaProtocol.Area->Rtd3AudioDelay             = mSystemConfiguration.Rtd3AudioDelay;
  mPlatformNvsAreaProtocol.Area->Rtd3SensorHub              = mSystemConfiguration.Rtd3SensorHub;
  mPlatformNvsAreaProtocol.Area->Rtd3TouchPanelDelay        = mSystemConfiguration.Rtd3TouchPanelDelay;
  mPlatformNvsAreaProtocol.Area->Rtd3TouchPadDelay          = mSystemConfiguration.Rtd3TouchPadDelay;
  mPlatformNvsAreaProtocol.Area->VRRampUpDelay              = mSystemConfiguration.VRRampUpDelay;
  mPlatformNvsAreaProtocol.Area->PstateCapping              = mSystemConfiguration.PstateCapping;
  mPlatformNvsAreaProtocol.Area->UsbPowerResourceTest       = (mSystemConfiguration.Rtd3UsbPt2 << 4)
                                                              | mSystemConfiguration.Rtd3UsbPt1;
  mPlatformNvsAreaProtocol.Area->SensorStandby              = mSystemConfiguration.SensorStandby;
  mPlatformNvsAreaProtocol.Area->Rtd3Config0                = ((mSystemConfiguration.WwanEnable && (mSystemConfiguration.Rtd3WWAN != 0) ? 1:0) << 7)
                                                              | (mSystemConfiguration.Rtd3I2CTouchPanel << 4); // Applicable for SKL SDS RTD3 SIP only
  mPlatformNvsAreaProtocol.Area->Rtd3Config1                =   (mSystemConfiguration.Rtd3RemapCR3  << 8)
                                                              | (mSystemConfiguration.Rtd3RemapCR2  << 7)
                                                              | (mSystemConfiguration.Rtd3RemapCR1  << 6)
                                                              | (mSystemConfiguration.Rtd3SataPort5 << 5)
                                                              | (mSystemConfiguration.Rtd3SataPort4 << 4)
                                                              | (mSystemConfiguration.Rtd3SataPort3 << 3)
                                                              | (mSystemConfiguration.Rtd3SataPort2 << 2)
                                                              | (mSystemConfiguration.Rtd3SataPort1 << 1)
                                                              |  mSystemConfiguration.Rtd3SataPort0;

  //
  // Enable PowerState
  //
  mPlatformNvsAreaProtocol.Area->PowerState = 1; // AC =1; for mobile platform, will update this value in SmmPlatform.c

  //
  // These don't have setup controls yet
  //
  mPlatformNvsAreaProtocol.Area->IdeMode = 0;

  if (PcdGetBool (PcdEcPresent) == TRUE) {
    //
    // Call EC lib to get PCIe dock status
    //
    PortData = 0;
    Status = GetPcieDockStatus (&PortData);

    //
    // the bit0 is PCIe Dock Status, 1 = docked
    //
    mPlatformNvsAreaProtocol.Area->PcieDockStatus = (PortData & 1);
  }

  mPlatformNvsAreaProtocol.Area->NativePCIESupport        = mSystemConfiguration.PciExpNative;
  mPlatformNvsAreaProtocol.Area->PlatformCpuId            = (CpuidRegs.RegEax & 0x0FFFFF);

  //
  // Create an End of DXE event.
  //
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  AcpiEndOfDxeEvent,
                  NULL,
                  &gEfiEndOfDxeEventGroupGuid,
                  &EndOfDxeEvent
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // SIO related option
  //
  Status = gBS->LocateProtocol (&gEfiCpuIo2ProtocolGuid, NULL, (VOID **) &mCpuIo);
  ASSERT_EFI_ERROR (Status);

  mPlatformNvsAreaProtocol.Area->WPCN381U = PLATFORM_NVS_DEVICE_DISABLE;

  mPlatformNvsAreaProtocol.Area->DockedSioPresent = PLATFORM_NVS_DEVICE_DISABLE;
  mPlatformNvsAreaProtocol.Area->DockComA = PLATFORM_NVS_DEVICE_DISABLE;
  mPlatformNvsAreaProtocol.Area->DockComB = PLATFORM_NVS_DEVICE_DISABLE;
  mPlatformNvsAreaProtocol.Area->DockLpt = PLATFORM_NVS_DEVICE_DISABLE;
  mPlatformNvsAreaProtocol.Area->DockFdc = PLATFORM_NVS_DEVICE_DISABLE;

  //
  // Check ID for NS87393 SIO, which is connected to Thimble Peak.
  //
  PortData = 0x20;
  Status = mCpuIo->Io.Write (
                        mCpuIo,
                        EfiCpuIoWidthUint8,
                        NAT_CONFIG_INDEX,
                        1,
                        &PortData
                        );
  ASSERT_EFI_ERROR (Status);

  Status = mCpuIo->Io.Read (
                        mCpuIo,
                        EfiCpuIoWidthUint8,
                        NAT_CONFIG_DATA,
                        1,
                        &PortData
                        );
  ASSERT_EFI_ERROR (Status);

  if (PortData == 0xEA) {
    mPlatformNvsAreaProtocol.Area->DockedSioPresent = PLATFORM_NVS_DEVICE_ENABLE;
    mPlatformNvsAreaProtocol.Area->DockComA         = PLATFORM_NVS_DEVICE_ENABLE;
    mPlatformNvsAreaProtocol.Area->DockComB         = PLATFORM_NVS_DEVICE_ENABLE;
  }

  if (mPlatformNvsAreaProtocol.Area->DockedSioPresent != PLATFORM_NVS_DEVICE_ENABLE) {
    //
    // Check ID for SIO WPCN381U
    //
    Status = mCpuIo->Io.Read (
                          mCpuIo,
                          EfiCpuIoWidthUint8,
                          WPCN381U_CONFIG_INDEX,
                          1,
                          &PortData
                          );
    ASSERT_EFI_ERROR (Status);
    if (PortData != 0xFF) {
      PortData = 0x20;
      Status = mCpuIo->Io.Write (
                            mCpuIo,
                            EfiCpuIoWidthUint8,
                            WPCN381U_CONFIG_INDEX,
                            1,
                            &PortData
                            );
      ASSERT_EFI_ERROR (Status);
      Status = mCpuIo->Io.Read (
                            mCpuIo,
                            EfiCpuIoWidthUint8,
                            WPCN381U_CONFIG_DATA,
                            1,
                            &PortData
                            );
      ASSERT_EFI_ERROR (Status);
      if ((PortData == WPCN381U_CHIP_ID) || (PortData == WDCP376_CHIP_ID)) {
        mPlatformNvsAreaProtocol.Area->WPCN381U = PLATFORM_NVS_DEVICE_ENABLE;
      }
    }
  }

  //
  // Enable APIC
  //
  mPlatformNvsAreaProtocol.Area->ApicEnable = PLATFORM_NVS_DEVICE_ENABLE;
#ifdef EC_SUPPORT
  //
  // EC function
  //
  if (PcdGetBool (PcdEcPresent) == TRUE) {
    mPlatformNvsAreaProtocol.Area->EcAvailable     = TRUE;
    mPlatformNvsAreaProtocol.Area->EcLowPowerMode  = mSystemConfiguration.EcLowPowerMode;
    mPlatformNvsAreaProtocol.Area->EcSmiGpioPin    = PcdGet32(PcdEcSmiGpio);
    mPlatformNvsAreaProtocol.Area->EcLowPowerModeGpioPin  = PcdGet32(PcdEcLowPowerExitGpio);
  } else {
    mPlatformNvsAreaProtocol.Area->EcAvailable     = FALSE;
    mPlatformNvsAreaProtocol.Area->EcLowPowerMode  = 0;
    mPlatformNvsAreaProtocol.Area->EcSmiGpioPin    = 0;
    mPlatformNvsAreaProtocol.Area->EcLowPowerModeGpioPin  = 0;
  }
#endif
  mPlatformNvsAreaProtocol.Area->EnableVoltageMargining = PcdGetBool (PcdEnableVoltageMargining);

  //
  // Comms Hub Support Enable/Disable
  //
  mPlatformNvsAreaProtocol.Area->CommsHubEnable  = mMeSetup.CommsHubEnable;

  mPlatformNvsAreaProtocol.Area->IuerButtonEnable = SaSetup.IuerButtonEnable;

  //
  // Enable 10sec Power Button Override only if CS is enabled.
  //
  if (mSystemConfiguration.LowPowerS0Idle == 1) {
    mPlatformNvsAreaProtocol.Area->TenSecondPowerButtonEnable |= BIT0; // Enable 10sec Power Button OVR.
    if (mSystemConfiguration.HidEventFilterDriverEnable) {
      mPlatformNvsAreaProtocol.Area->HidEventFilterEnable = 0x01;        // Enable Hid Event Filter Driver
    } else {
      mPlatformNvsAreaProtocol.Area->HidEventFilterEnable = 0x00;        // Disable Hid Event Filter Driver
    }
  } else {
    mPlatformNvsAreaProtocol.Area->TenSecondPowerButtonEnable &= ~(BIT0); // Disable 10sec Power Button OVR.
    //
    // HID Event Filter Enable/Disable
    //
    mPlatformNvsAreaProtocol.Area->HidEventFilterEnable = mSystemConfiguration.HidEventFilterDriverEnable;
  }
  mPlatformNvsAreaProtocol.Area->TenSecondPowerButtonEnable |= (SaSetup.SlateIndicatorRT << 3);
  mPlatformNvsAreaProtocol.Area->TenSecondPowerButtonEnable |= (SaSetup.DockIndicatorRT << 4);
  mPlatformNvsAreaProtocol.Area->IuerConvertibleEnable = SaSetup.IuerConvertibleEnable;
  mPlatformNvsAreaProtocol.Area->IuerDockEnable = SaSetup.IuerDockEnable;

  mPlatformNvsAreaProtocol.Area->VirtualGpioButtonSxBitmask  = 0x00;
  mPlatformNvsAreaProtocol.Area->VirtualGpioButtonSxBitmask |=  SaSetup.SlateIndicatorSx << 6;
  mPlatformNvsAreaProtocol.Area->VirtualGpioButtonSxBitmask |=  SaSetup.DockIndicatorSx << 7;

  //
  // Low Power S0 Idle - Enabled/Disabled
  //
  mPlatformNvsAreaProtocol.Area->LowPowerS0Idle = mSystemConfiguration.LowPowerS0Idle;

  //
  // WWAN GPIO pin configuration
  //
  mPlatformNvsAreaProtocol.Area->WwanRtd3Option = mSystemConfiguration.Rtd3WWAN;
  mPlatformNvsAreaProtocol.Area->WwanPerstGpio  = PcdGet32 (PcdWwanPerstGpio);
  mPlatformNvsAreaProtocol.Area->WwanPerstGpioPolarity = PcdGet8 (PcdWwanPerstGpioPolarity);
  mPlatformNvsAreaProtocol.Area->WwanBbrstGpio = PcdGet32(PcdWwanBbrstGpio);
  mPlatformNvsAreaProtocol.Area->WwanBbrstGpioPolarity = PcdGetBool(PcdWwanBbrstGpioPolarity);
  mPlatformNvsAreaProtocol.Area->WwanWakeGpio = PcdGet32(PcdWwanWakeGpio);
  mPlatformNvsAreaProtocol.Area->WwanFullCardPowerOffGpio = PcdGet32(PcdWwanFullCardPowerOffGpio);
  mPlatformNvsAreaProtocol.Area->WwanFullCardPowerOffGpioPolarity = PcdGetBool(PcdWwanFullCardPowerOffGpioPolarity);

  //
  // PCH/CPU PCIe x4 Slot 1 GPIO pin configuration
  //
  mPlatformNvsAreaProtocol.Area->PcieSlot1WakeGpio = PcdGet32 (PcdPcieSlot1WakeGpioPin);
  mPlatformNvsAreaProtocol.Area->PcieSlot1PowerEnableGpio = PcdGet32(PcdPcieSlot1PwrEnableGpioNo);
  mPlatformNvsAreaProtocol.Area->PcieSlot1PowerEnableGpioPolarity = PcdGetBool(PcdPcieSlot1PwrEnableGpioPolarity);
  mPlatformNvsAreaProtocol.Area->PcieSlot1RstGpio = PcdGet32(PcdPcieSlot1HoldRstGpioNo);
  mPlatformNvsAreaProtocol.Area->PcieSlot1RstGpioPolarity = PcdGetBool(PcdPcieSlot1HoldRstGpioPolarity);
  mPlatformNvsAreaProtocol.Area->PcieSlot1RpNumber = PcdGet8 (PcdPcieSlot1RootPort);
  //
  // PCH PCIe x1 Slot 2 GPIO pin configuration
  //
  mPlatformNvsAreaProtocol.Area->PcieSlot2WakeGpio = PcdGet32(PcdPcieSlot2WakeGpioPin);
  mPlatformNvsAreaProtocol.Area->PcieSlot2PowerEnableGpio = PcdGet32(PcdPchPCIeSlot2PwrEnableGpioNo);
  mPlatformNvsAreaProtocol.Area->PcieSlot2PowerEnableGpioPolarity = PcdGetBool(PcdPchPCIeSlot2PwrEnableGpioPolarity);
  mPlatformNvsAreaProtocol.Area->PcieSlot2RstGpio = PcdGet32(PcdPchPCIeSlot2RstGpioNo);
  mPlatformNvsAreaProtocol.Area->PcieSlot2RstGpioPolarity = PcdGetBool(PcdPchPCIeSlot2RstGpioPolarity);
  mPlatformNvsAreaProtocol.Area->PcieSlot2RpNumber = PcdGet8(PcdPcieSlot2RootPort);

  //
  // CPU M.2 SSD GPIO pin configuration
  //
  mPlatformNvsAreaProtocol.Area->M2Ssd2PowerEnableGpio = PcdGet32(PcdPcieSsd2PwrEnableGpioNo);
  mPlatformNvsAreaProtocol.Area->M2Ssd2PowerEnableGpioPolarity = PcdGetBool(PcdPcieSsd2PwrEnableGpioPolarity);
  mPlatformNvsAreaProtocol.Area->M2Ssd2RstGpio = PcdGet32(PcdPcieSsd2RstGpioNo);
  mPlatformNvsAreaProtocol.Area->M2Ssd2RstGpioPolarity = PcdGetBool(PcdPcieSsd2RstGpioPolarity);

  //
  // PCH M.2 SSD GPIO pin configuration
  //
  mPlatformNvsAreaProtocol.Area->PchM2SsdPowerEnableGpio = PcdGet32(PcdPchSsdPwrEnableGpioNo);
  mPlatformNvsAreaProtocol.Area->PchM2SsdPowerEnableGpioPolarity = PcdGetBool(PcdPchSsdPwrEnableGpioPolarity);
  mPlatformNvsAreaProtocol.Area->PchM2SsdRstGpio = PcdGet32(PcdPchSsdRstGpioNo);
  mPlatformNvsAreaProtocol.Area->PchM2SsdRstGpioPolarity = PcdGetBool(PcdPchSsdRstGpioPolarity);

  //
  // PCH Sata ports GPIO pin configuration
  //
  mPlatformNvsAreaProtocol.Area->SataPortPowerEnableGpio = PcdGet32(PcdPchSataPortPwrEnableGpioNo);
  mPlatformNvsAreaProtocol.Area->SataPortPowerEnableGpioPolarity = PcdGetBool(PcdPchSataPortPwrEnableGpioPolarity);

  //
  // Touch Pad and Panel GPIO pin configuration
  //
  mPlatformNvsAreaProtocol.Area->TouchpadIrqGpio = PcdGet32(PcdTouchpadIrqGpio);
  mPlatformNvsAreaProtocol.Area->TouchpadIrqGpioPolarity = PcdGetBool(PcdTouchpadIrqGpioPolarity);
  mPlatformNvsAreaProtocol.Area->TouchpanelIrqGpio = PcdGet32(PcdTouchpanelIrqGpio);
  mPlatformNvsAreaProtocol.Area->TouchpanelPowerEnableGpio = PcdGet32(PcdTouchpanelPwrEnableGpio);
  mPlatformNvsAreaProtocol.Area->TouchpanelPowerRstGpio = PcdGet32(PcdTouchpanelRstGpio);
  mPlatformNvsAreaProtocol.Area->TouchpanelIrqGpioPolarity = PcdGetBool(PcdTouchpanelIrqGpioPolarity);
  mPlatformNvsAreaProtocol.Area->TouchpanelPowerEnableGpioPolarity = PcdGetBool(PcdTouchpanelPwrEnableGpioPolarity);
  mPlatformNvsAreaProtocol.Area->TouchpanelPowerRstGpioPolarity = PcdGetBool(PcdTouchpanelRstGpioPolarity);
  mPlatformNvsAreaProtocol.Area->Touchpanel1IrqGpio = PcdGet32(PcdTouchpanel1IrqGpio);
  mPlatformNvsAreaProtocol.Area->Touchpanel1PowerEnableGpio = PcdGet32(PcdTouchpanel1PwrEnableGpio);
  mPlatformNvsAreaProtocol.Area->Touchpanel1PowerRstGpio = PcdGet32(PcdTouchpanel1RstGpio);
  mPlatformNvsAreaProtocol.Area->Touchpanel1IrqGpioPolarity = PcdGetBool(PcdTouchpanel1IrqGpioPolarity);
  mPlatformNvsAreaProtocol.Area->Touchpanel1PowerEnableGpioPolarity = PcdGetBool(PcdTouchpanel1PwrEnableGpioPolarity);
  mPlatformNvsAreaProtocol.Area->Touchpanel1PowerRstGpioPolarity = PcdGetBool(PcdTouchpanel1RstGpioPolarity);

  //
  // WLAN GPIO pin configuration
  //
  mPlatformNvsAreaProtocol.Area->WlanWakeGpio = PcdGet32(PcdWlanWakeGpio);

  //
  //Disable PEP constarints for devices which are not present in CNL-H platform
  //
  if ((PchGeneration () == CNL_PCH) && IsPchH ()) {
    mSystemConfiguration.PepEmmc = 0;
    mSystemConfiguration.PepI2c4 = 0;
  }
  //
  // Disable PEP constraint if IPU B0:D5:F0 device is not preset
  //
  if (PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, GetIpuBusNumber (), GetIpuDevNumber (), GetIpuFuncNumber (), PCI_VENDOR_ID_OFFSET)) == 0xFFFF) {
    mSystemConfiguration.PepIpu = 0;
  }
  //
  // Disable PEP constraint if PEG B0:D1:F0 device is not preset
  //
  if (PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_PEG_BUS_NUM, SA_PEG0_DEV_NUM, SA_PEG0_FUN_NUM, PCI_VENDOR_ID_OFFSET)) == 0xFFFF) {
    mSystemConfiguration.PepPeg0 = 0;
  }
  //
  // Disable PEP constraint if IGD B0:D2:F0 device is not preset
  //
  if (PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, PCI_VENDOR_ID_OFFSET)) == 0xFFFF) {
    mSystemConfiguration.PepGfx = 0;
  }
  //
  //Disable Gbe PEP constarints if it's not presented.
  //
  if (!IsGbePresent()) {
    mSystemConfiguration.PepGbe = 0;
  }
  //
  // Disable PEP constraint if PCH SATA B0:D23:F0 device is not preset
  //
  if (PciSegmentRead16 (SataRegBase (SATA_1_CONTROLLER_INDEX) + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    mSystemConfiguration.PepSataContraints = 0;
  }

  //
  // Disable PEP Constrains for THC
  //
  if (mPchSetup.ThcPort0Assignment == ThcAssignmentNone) {
    // Disable PEP for both THC
    mSystemConfiguration.PepThc0 = 0;
    mSystemConfiguration.PepThc1 = 0;
  } else if (mPchSetup.ThcPort1Assignment != ThcAssignmentThc1) {
    mSystemConfiguration.PepThc1 = 0; //THC1 is not used
  }

  //
  // Disable PEP constraint if PCH HDA B0:D31:F3 device is not preset
  //
  if (PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (DEFAULT_PCI_SEGMENT_NUMBER_PCH, DEFAULT_PCI_BUS_NUMBER_PCH, HdaDevNumber (), HdaFuncNumber (), PCI_VENDOR_ID_OFFSET)) == 0xFFFF) {
    mSystemConfiguration.PepAudio = 0;
  }

  //
  // Enable PEP constraints for Serial Io devices
  // Override Function 0 Enabled devices
  //
  for (SerialIoIndex = 0; SerialIoIndex < GetPchMaxSerialIoSpiControllersNum (); SerialIoIndex++) {
    PepSerialIoSpi[SerialIoIndex] = mPchSetup.PchSerialIoSpi[SerialIoIndex];
    if ((PepSerialIoSpi[SerialIoIndex] == 0) && IsSerialIoSpiFunction0Enabled (SerialIoIndex)) {
      PepSerialIoSpi[SerialIoIndex] = 1;
    }
  }
  for (SerialIoIndex = 0; SerialIoIndex < GetPchMaxSerialIoI2cControllersNum (); SerialIoIndex++) {
    PepSerialIoI2c[SerialIoIndex] = mPchSetup.PchSerialIoI2c[SerialIoIndex];
    if ((PepSerialIoI2c[SerialIoIndex] == 0) && IsSerialIoI2cFunction0Enabled (SerialIoIndex)) {
      PepSerialIoI2c[SerialIoIndex] = 1;
    }
  }
  for (SerialIoIndex = 0; SerialIoIndex < GetPchMaxSerialIoUartControllersNum (); SerialIoIndex++) {
    PepSerialIoUart[SerialIoIndex] = mPchSetup.PchSerialIoUart[SerialIoIndex];
    if ((PepSerialIoUart[SerialIoIndex] == 0) && IsSerialIoUartFunction0Enabled (SerialIoIndex)) {
      PepSerialIoUart[SerialIoIndex] = 1;
    }
  }

  //
  // Micro-PEP constraint list
  //
  mPlatformNvsAreaProtocol.Area->LowPowerS0IdleConstraint = (((mPchSetup.PchSata == 1 ? 0x3:0) & mSystemConfiguration.PepSataContraints)  <<  0) | // Bit[1:0] - Storage (0:None, 1:Adapter D0/F1, 2:Raid, 3:Adapter D3)
                                                            ((PepSerialIoUart[0] && mSystemConfiguration.PepUart0)                        <<  2) | // Bit[2]   - En/Dis UART0
                                                            ((PepSerialIoUart[1] && mSystemConfiguration.PepUart1)                        <<  3) | // Bit[3]   - En/Dis UART1
                                                            ( mSystemConfiguration.PepPcieStorage                                         <<  4) | // Bit[4]   - En/Dis PCIe NVMe/AHCI
                                                            ((PepSerialIoI2c[0] && mSystemConfiguration.PepI2c0)                          <<  5) | // Bit[5]   - En/Dis I2C0
                                                            ((PepSerialIoI2c[1] && mSystemConfiguration.PepI2c1)                          <<  6) | // Bit[6]   - En/Dis I2C1
                                                            ( mSystemConfiguration.PepXhci                                                <<  7) | // Bit[7]   - En/Dis XHCI
                                                            ((mPchSetup.PchHdAudio && mSystemConfiguration.PepAudio)                      <<  8) | // Bit[8]   - En/Dis HD Audio (includes ADSP)
                                                            ( mSystemConfiguration.PepGfx                                                 <<  9) | // Bit[9]   - En/Dis GFX
                                                            ( mSystemConfiguration.PepCpu                                                 << 10) | // Bit[10]  - En/Dis CPU
                                                            ((mPchSetup.PchScsEmmcEnabled && mSystemConfiguration.PepEmmc)                << 11) | // Bit[11]  - En/Dis EMMC
                                                            ((mPchSetup.PchScsSdCardEnabled && mSystemConfiguration.PepSdxc)              << 12) | // Bit[12]  - En/Dis SDXC
                                                            ((PepSerialIoI2c[2] && mSystemConfiguration.PepI2c2)                          << 13) | // Bit[13]  - En/Dis I2C2
                                                            ((PepSerialIoI2c[3] && mSystemConfiguration.PepI2c3)                          << 14) | // Bit[14]  - En/Dis I2C3
                                                            ((PepSerialIoI2c[4] && mSystemConfiguration.PepI2c4)                          << 15) | // Bit[15]  - En/Dis I2C4
                                                            ((PepSerialIoI2c[5] && mSystemConfiguration.PepI2c5)                          << 16) | // Bit[16]  - En/Dis I2C5
                                                            ((PepSerialIoUart[2] && mSystemConfiguration.PepUart2)                        << 17) | // Bit[17]  - En/Dis UART2
                                                            ((PepSerialIoSpi[0] && mSystemConfiguration.PepSpi0)                          << 18) | // Bit[18]  - En/Dis SPI0
                                                            ((PepSerialIoSpi[1] && mSystemConfiguration.PepSpi1)                          << 19) | // Bit[19]  - En/Dis SPI1
                                                            ((PepSerialIoSpi[2] && mSystemConfiguration.PepSpi2)                          << 20) | // Bit[20]  - En/Dis SPI2
                                                            (((!mPchSetup.PchHdaIDisplayCodecDisconnect) && mSystemConfiguration.PepAudio)<< 21) | // Bit[21]  - En/Dis IDA
                                                            ( mSystemConfiguration.PepCsme                                                << 22) | // Bit[22]  - En/Dis CSME
                                                            ((PepSerialIoI2c[6] && mSystemConfiguration.PepI2c6)                          << 23) | // Bit[23]   -En/Dis I2C6
                                                            ((PepSerialIoI2c[7] && mSystemConfiguration.PepI2c7)                          << 24) | // Bit[24]  - En/Dis I2C7
                                                            (mSystemConfiguration.PepThc0                                                 << 25) | // Bit[25]  - En/Dis THC0
                                                            (mSystemConfiguration.PepThc1                                                 << 26) | // Bit[26]  - En/Dis THC1
                                                            (mSystemConfiguration.PepIsi                                                  << 27) | // Bit[27]  - En/Dis ISI
                                                            (mSystemConfiguration.PepGbeTsn                                               << 28) | // Bit[28]  - En/Dis GBETSN
                                                            (mSystemConfiguration.PepPse                                                  << 29);  // Bit[29]  - En/Dis PSE

  DEBUG((DEBUG_INFO, "ACPI NVS, LowPowerS0IdleConstraint(Micro-pep constraints) = 0x%X \n", mPlatformNvsAreaProtocol.Area->LowPowerS0IdleConstraint ));

  if(mSystemConfiguration.PepPse == 0) {
    mPlatformNvsAreaProtocol.Area->LowPowerS0IdleConstraint2 = ((mSystemConfiguration.PepPseTsn)                                                          <<  0) | // Bit[0]   - En/Dis PSE TSN 0
                                                               ((mSystemConfiguration.PepPseDma)                                                          <<  1) | // Bit[1]   - En/Dis PSE DMA
                                                               ((mSystemConfiguration.PepPsePwm)                                                          <<  2) | // Bit[2]   - En/Dis PSE PWM
                                                               ((mSystemConfiguration.PepPseAdc)                                                          <<  3) | // Bit[3]   - En/Dis PSE Adc
                                                               (((mPchSetup.PchPseSpiEnable[0] == 2 ? 1:0) && mSystemConfiguration.PepPseSpi)             <<  4) | // Bit[4]   - En/Dis PSE SPI 0
                                                               (((mPchSetup.PchPseSpiEnable[1] == 2 ? 1:0) && mSystemConfiguration.PepPseSpi)             <<  5) | // Bit[5]   - En/Dis PSE SPI 1
                                                               (((mPchSetup.PchPseSpiEnable[2] == 2 ? 1:0) && mSystemConfiguration.PepPseSpi)             <<  6) | // Bit[6]   - En/Dis PSE SPI 2
                                                               (((mPchSetup.PchPseSpiEnable[3] == 2 ? 1:0) && mSystemConfiguration.PepPseSpi)             <<  7) | // Bit[7]   - En/Dis PSE SPI 3
                                                               (((mPchSetup.PchPseI2cEnable[0] == 2 ? 1:0) && mSystemConfiguration.PepPseI2c)             <<  8) | // Bit[8]   - En/Dis PSE I2C 0
                                                               (((mPchSetup.PchPseI2cEnable[1] == 2 ? 1:0) && mSystemConfiguration.PepPseI2c)             <<  9) | // Bit[9]   - En/Dis PSE I2C 1
                                                               (((mPchSetup.PchPseI2cEnable[2] == 2 ? 1:0) && mSystemConfiguration.PepPseI2c)             << 10) | // Bit[10]  - En/Dis PSE I2C 2
                                                               (((mPchSetup.PchPseI2cEnable[3] == 2 ? 1:0) && mSystemConfiguration.PepPseI2c)             << 11) | // Bit[11]  - En/Dis PSE I2C 3
                                                               (((mPchSetup.PchPseI2cEnable[4] == 2 ? 1:0) && mSystemConfiguration.PepPseI2c)             << 12) | // Bit[12]  - En/Dis PSE I2C 4
                                                               (((mPchSetup.PchPseI2cEnable[5] == 2 ? 1:0) && mSystemConfiguration.PepPseI2c)             << 13) | // Bit[13]  - En/Dis PSE I2C 5
                                                               (((mPchSetup.PchPseI2cEnable[6] == 2 ? 1:0) && mSystemConfiguration.PepPseI2c)             << 14) | // Bit[14]  - En/Dis PSE I2C 6
                                                               (((mPchSetup.PchPseI2cEnable[7] == 2 ? 1:0) && mSystemConfiguration.PepPseI2c)             << 15) | // Bit[15]  - En/Dis PSE I2C 7
                                                               (((mPchSetup.PchPseUartEnable[0] == 2 ? 1:0) && mSystemConfiguration.PepPseUart)           << 16) | // Bit[16]  - En/Dis PSE UART 0
                                                               (((mPchSetup.PchPseUartEnable[1] == 2 ? 1:0) && mSystemConfiguration.PepPseUart)           << 17) | // Bit[17]  - En/Dis PSE UART 1
                                                               (((mPchSetup.PchPseUartEnable[2] == 2 ? 1:0) && mSystemConfiguration.PepPseUart)           << 18) | // Bit[18]  - En/Dis PSE UART 2
                                                               (((mPchSetup.PchPseUartEnable[3] == 2 ? 1:0) && mSystemConfiguration.PepPseUart)           << 19) | // Bit[19]  - En/Dis PSE UART 3
                                                               (((mPchSetup.PchPseUartEnable[4] == 2 ? 1:0) && mSystemConfiguration.PepPseUart)           << 20) | // Bit[20]  - En/Dis PSE UART 4
                                                               (((mPchSetup.PchPseUartEnable[5] == 2 ? 1:0) && mSystemConfiguration.PepPseUart)           << 21) | // Bit[21]  - En/Dis PSE UART 5
                                                               (((mPchSetup.PchPseI2sEnable[0] == 2 ? 1:0) && mSystemConfiguration.PepPseI2s)             << 22) | // Bit[22]  - En/Dis PSE I2S 0
                                                               (((mPchSetup.PchPseI2sEnable[1] == 2 ? 1:0) && mSystemConfiguration.PepPseI2s)             << 23) | // Bit[23]   -En/Dis PSE I2S 1
                                                               (((mPchSetup.PchPseTgpioEnable[0] == 2 ? 1:0) && mSystemConfiguration.PepPseGpio)          << 24) | // Bit[24]  - En/Dis PSE GPIO 0
                                                               (((mPchSetup.PchPseTgpioEnable[1] == 2 ? 1:0) && mSystemConfiguration.PepPseGpio)          << 25) | // Bit[25]  - En/Dis PSE GPIO 1
                                                               (((mPchSetup.PchPseCanEnable[0] == 2 ? 1:0) && mSystemConfiguration.PepPseCan)             << 26) | // Bit[26]  - En/Dis PSE CAN 0
                                                               (((mPchSetup.PchPseCanEnable[1] == 2 ? 1:0) && mSystemConfiguration.PepPseCan)             << 27) | // Bit[27]  - En/Dis PSE CAN 0
                                                               (((mPchSetup.PchPseQepEnable[0] == 2 ? 1:0) && mSystemConfiguration.PepPseQep)             << 28) | // Bit[28]  - En/Dis PSE QEP 0
                                                               (((mPchSetup.PchPseQepEnable[1] == 2 ? 1:0) && mSystemConfiguration.PepPseQep)             << 29) | // Bit[29]  - En/Dis PSE QEP 1
                                                               (((mPchSetup.PchPseQepEnable[2] == 2 ? 1:0) && mSystemConfiguration.PepPseQep)             << 30) | // Bit[30]  - En/Dis PSE QEP 2
                                                               (((mPchSetup.PchPseQepEnable[3] == 2 ? 1:0) && mSystemConfiguration.PepPseQep)             << 31);  // Bit[31]  - En/Dis PSE QEP 3
  } else {
    mPlatformNvsAreaProtocol.Area->LowPowerS0IdleConstraint2 = 0;
  }
  DEBUG((DEBUG_INFO, "ACPI NVS, LowPowerS0IdleConstraint(Micro-pep constraints 2) = 0x%X \n", mPlatformNvsAreaProtocol.Area->LowPowerS0IdleConstraint2 ));
  //
  // Assign EPI device interrupt pin and Enable/Disable Device by using PCD and pass through NVS
  //

  //
  // Disable / Enable Power meter device based on user settings
  //
  mPlatformNvsAreaProtocol.Area->PowermeterDeviceEnable = mSystemConfiguration.PowermeterDeviceEnable;

  //
  //
  // Update SATA port connect status for PEPD.  This needs to be done only when CS is enabled.
  // Note: We cannot do this inside ASL code since SATA device has a dependency to PEPD device and PEPD device
  // needs to know SATA device connect status. Deadlock situation between SATA and PEPD.
  //
  if (mSystemConfiguration.LowPowerS0Idle == 1) {
    //
    // Read SATA device PCS field for SATA Port Present status bits if SATA Controller is present.
    //
    if (PciSegmentRead16 (SataRegBase (SATA_1_CONTROLLER_INDEX) + PCI_VENDOR_ID_OFFSET) != 0xFFFF) {
      mPlatformNvsAreaProtocol.Area->SataPortState = GetSataPortPresentStatus (SATA_1_CONTROLLER_INDEX);
    }
  }
#ifdef EC_SUPPORT
  mPlatformNvsAreaProtocol.Area->CSNotifyEC      = mSystemConfiguration.CSNotifyEC;
  mPlatformNvsAreaProtocol.Area->CSDebugLightEC  = mSystemConfiguration.CSDebugLightEC;
#endif
  mPlatformNvsAreaProtocol.Area->PL1LimitCS      = mSystemConfiguration.PL1LimitCS;
  mPlatformNvsAreaProtocol.Area->PL1LimitCSValue = mSystemConfiguration.PL1LimitCSValue;

  //
  // I2C Touch Pad Data Update to I2cTouchPad.asl
  //
  mPlatformNvsAreaProtocol.Area->TPDT           = mSystemConfiguration.PchI2cTouchPadType;
  mPlatformNvsAreaProtocol.Area->TPDM           = mSystemConfiguration.PchI2cTouchPadIrqMode;
  mPlatformNvsAreaProtocol.Area->TPDB           = mSystemConfiguration.PchI2cTouchPadBusAddress;
  mPlatformNvsAreaProtocol.Area->TPDH           = mSystemConfiguration.PchI2cTouchPadHidAddress;
  mPlatformNvsAreaProtocol.Area->TPDS           = mSystemConfiguration.PchI2cTouchPadSpeed;

  //
  // I2C Touch Panel Data Update to I2cTouchPanel.asl
  //
  mPlatformNvsAreaProtocol.Area->TPLT           = mSystemConfiguration.PchI2cTouchPanelType;
  mPlatformNvsAreaProtocol.Area->TPLM           = mSystemConfiguration.PchI2cTouchPanelIrqMode;
  mPlatformNvsAreaProtocol.Area->TPLB           = mSystemConfiguration.PchI2cTouchPanelBusAddress;
  mPlatformNvsAreaProtocol.Area->TPLH           = mSystemConfiguration.PchI2cTouchPanelHidAddress;
  mPlatformNvsAreaProtocol.Area->TPLS           = mSystemConfiguration.PchI2cTouchPanelSpeed;

  //
  // SPI Finger Print Data Update to SerialIoFingerPrint.asl
  //
  mPlatformNvsAreaProtocol.Area->FPTT           = mSystemConfiguration.PchSpiFingerPrintType;
  mPlatformNvsAreaProtocol.Area->FPTM           = mSystemConfiguration.PchSpiSensorIrqMode;

  mPlatformNvsAreaProtocol.Area->SCS0           = mSystemConfiguration.SerialIoSpiCsDeviceEnable[0];
  mPlatformNvsAreaProtocol.Area->SCS1           = mSystemConfiguration.SerialIoSpiCsDeviceEnable[1];
  mPlatformNvsAreaProtocol.Area->SCS2           = mSystemConfiguration.SerialIoSpiCsDeviceEnable[2];

  mPlatformNvsAreaProtocol.Area->SDS0           = mSystemConfiguration.PchI2cSensorDevicePort[SERIAL_IO_I2C0];
  mPlatformNvsAreaProtocol.Area->SDS1           = mSystemConfiguration.PchI2cSensorDevicePort[SERIAL_IO_I2C1];
  mPlatformNvsAreaProtocol.Area->SDS2           = mSystemConfiguration.PchI2cSensorDevicePort[SERIAL_IO_I2C2];
  mPlatformNvsAreaProtocol.Area->SDS3           = mSystemConfiguration.PchI2cSensorDevicePort[SERIAL_IO_I2C3];
  mPlatformNvsAreaProtocol.Area->SDS4           = mSystemConfiguration.PchI2cSensorDevicePort[SERIAL_IO_I2C4];
  mPlatformNvsAreaProtocol.Area->SDS5           = mSystemConfiguration.PchI2cSensorDevicePort[SERIAL_IO_I2C5];
  //mPlatformNvsAreaProtocol.Area->SDS6           = mSystemConfiguration.PchSpi0SensorDevice;
  //mPlatformNvsAreaProtocol.Area->SDM6           = mSystemConfiguration.PchI2c0SensorIrqMode;
  mPlatformNvsAreaProtocol.Area->SDS7           = mSystemConfiguration.PchSpiSensorDevicePort[SERIAL_IO_SPI1];
  mPlatformNvsAreaProtocol.Area->SDS8           = mSystemConfiguration.PchSpiSensorDevicePort[SERIAL_IO_SPI2];

  mPlatformNvsAreaProtocol.Area->SDS9           = mSystemConfiguration.DiscreteBtModule;
  mPlatformNvsAreaProtocol.Area->SDM9           = mSystemConfiguration.DiscreteBtModuleIrqMode;

  mPlatformNvsAreaProtocol.Area->WTVX           = mSystemConfiguration.PchI2cWittVersion;
  mPlatformNvsAreaProtocol.Area->WITX           = mSystemConfiguration.PchI2cWittDevice;
  mPlatformNvsAreaProtocol.Area->UTKX           = mSystemConfiguration.PchUartUtkDevice;
  mPlatformNvsAreaProtocol.Area->GDBT           = mPchSetup.PchGpioDebounce;
  mPlatformNvsAreaProtocol.Area->GPTD           = mPchSetup.PchGpioTestDevices;
  mPlatformNvsAreaProtocol.Area->SPTD           = mPchSetup.PchAdditionalSerialIoDevices;
  mPlatformNvsAreaProtocol.Area->DMTX           = mPchSetup.PchPseDmaTestEnable;

  mPlatformNvsAreaProtocol.Area->TsnEnabled     = IsTsnPresent();
  mPlatformNvsAreaProtocol.Area->PseTsn0Enabled = IsPseGbe0Enabled();
  mPlatformNvsAreaProtocol.Area->PseTsn0Enabled = IsPseGbe1Enabled();
  mPlatformNvsAreaProtocol.Area->PseUart0Rs485Enabled = mPchSetup.PchPseHsuartEnable[0];
  mPlatformNvsAreaProtocol.Area->PseUart1Rs485Enabled = mPchSetup.PchPseHsuartEnable[1];
  mPlatformNvsAreaProtocol.Area->PseUart2Rs485Enabled = mPchSetup.PchPseHsuartEnable[2];
  mPlatformNvsAreaProtocol.Area->PseUart3Rs485Enabled = mPchSetup.PchPseHsuartEnable[3];

  //
  // UCMC support
  //
  UcmcGpioTable = (GPIO_INIT_CONFIG *)(UINTN)PcdGet32(PcdBoardUcmcGpioTable);
  UcmcGpioTableSize = (UINT16)PcdGet16(PcdBoardUcmcGpioTableSize);
  mPlatformNvsAreaProtocol.Area->UCMS           = mSystemConfiguration.TcssUcmDevice;

  if (UcmcGpioTableSize) {
    ASSERT(UcmcGpioTableSize == 2);

    mPlatformNvsAreaProtocol.Area->UcmcPort1Gpio = UcmcGpioTable[0].GpioPad;
    mPlatformNvsAreaProtocol.Area->UcmcPort2Gpio = UcmcGpioTable[1].GpioPad;
  }

  //
  // Serial IO timing parameters
  //
  if(mSystemConfiguration.PchI2cSpeed[0] == 0) {
    mPlatformNvsAreaProtocol.Area->IC0S = 100000;
  } else if(mSystemConfiguration.PchI2cSpeed[0] == 1) {
    mPlatformNvsAreaProtocol.Area->IC0S = 400000;
  } else if(mSystemConfiguration.PchI2cSpeed[0] == 2) {
    mPlatformNvsAreaProtocol.Area->IC0S = 1000000;
  } else {
    mPlatformNvsAreaProtocol.Area->IC0S = 3400000;
  }

  if(mSystemConfiguration.PchI2cSpeed[1] == 0) {
    mPlatformNvsAreaProtocol.Area->IC1S = 100000;
  } else if(mSystemConfiguration.PchI2cSpeed[1] == 1) {
    mPlatformNvsAreaProtocol.Area->IC1S = 400000;
  } else if(mSystemConfiguration.PchI2cSpeed[1] == 2) {
    mPlatformNvsAreaProtocol.Area->IC1S = 1000000;
  } else {
    mPlatformNvsAreaProtocol.Area->IC1S = 3400000;
  }

  if(mSystemConfiguration.PchI2cSpeed[2] == 0) {
    mPlatformNvsAreaProtocol.Area->IC2S = 100000;
  } else if(mSystemConfiguration.PchI2cSpeed[2] == 1) {
    mPlatformNvsAreaProtocol.Area->IC2S = 400000;
  } else if(mSystemConfiguration.PchI2cSpeed[2] == 2) {
    mPlatformNvsAreaProtocol.Area->IC2S = 1000000;
  } else {
    mPlatformNvsAreaProtocol.Area->IC2S = 3400000;
  }

  if(mSystemConfiguration.PchI2cSpeed[3] == 0) {
    mPlatformNvsAreaProtocol.Area->IC3S = 100000;
  } else if(mSystemConfiguration.PchI2cSpeed[3] == 1) {
    mPlatformNvsAreaProtocol.Area->IC3S = 400000;
  } else if(mSystemConfiguration.PchI2cSpeed[3] == 2) {
    mPlatformNvsAreaProtocol.Area->IC3S = 1000000;
  } else {
    mPlatformNvsAreaProtocol.Area->IC3S = 3400000;
  }

  if(mSystemConfiguration.PchI2cSpeed[4] == 0) {
    mPlatformNvsAreaProtocol.Area->IC4S = 100000;
  } else if(mSystemConfiguration.PchI2cSpeed[4] == 1) {
    mPlatformNvsAreaProtocol.Area->IC4S = 400000;
  } else if(mSystemConfiguration.PchI2cSpeed[4] == 2) {
    mPlatformNvsAreaProtocol.Area->IC4S = 1000000;
  } else {
    mPlatformNvsAreaProtocol.Area->IC4S = 3400000;
  }

  if(mSystemConfiguration.PchI2cSpeed[5] == 0) {
    mPlatformNvsAreaProtocol.Area->IC5S = 100000;
  } else if(mSystemConfiguration.PchI2cSpeed[5] == 1) {
    mPlatformNvsAreaProtocol.Area->IC5S = 400000;
  } else if(mSystemConfiguration.PchI2cSpeed[5] == 2) {
    mPlatformNvsAreaProtocol.Area->IC5S = 1000000;
  } else {
    mPlatformNvsAreaProtocol.Area->IC5S = 3400000;
  }

  if(mSystemConfiguration.PchI2cSpeed[6] == 0) {
    mPlatformNvsAreaProtocol.Area->IC6S = 100000;
  } else if(mSystemConfiguration.PchI2cSpeed[6] == 1) {
    mPlatformNvsAreaProtocol.Area->IC6S = 400000;
  } else if(mSystemConfiguration.PchI2cSpeed[6] == 2) {
    mPlatformNvsAreaProtocol.Area->IC6S = 1000000;
  } else {
    mPlatformNvsAreaProtocol.Area->IC6S = 3400000;
  }

  if(mSystemConfiguration.PchI2cSpeed[7] == 0) {
    mPlatformNvsAreaProtocol.Area->IC7S = 100000;
  } else if(mSystemConfiguration.PchI2cSpeed[7] == 1) {
    mPlatformNvsAreaProtocol.Area->IC7S = 400000;
  } else if(mSystemConfiguration.PchI2cSpeed[7] == 2) {
    mPlatformNvsAreaProtocol.Area->IC7S = 1000000;
  } else {
    mPlatformNvsAreaProtocol.Area->IC7S = 3400000;
  }
  mPlatformNvsAreaProtocol.Area->USTP = mSystemConfiguration.PchSerialIoUseTimingParameters;

  mPlatformNvsAreaProtocol.Area->SSH0 = mSystemConfiguration.PchSerialIoTimingSSH0;  // [SSH0] SSCN-HIGH for I2C0
  mPlatformNvsAreaProtocol.Area->SSL0 = mSystemConfiguration.PchSerialIoTimingSSL0;  // [SSL0] SSCN-LOW  for I2C0
  mPlatformNvsAreaProtocol.Area->SSD0 = mSystemConfiguration.PchSerialIoTimingSSD0;  // [SSD0] SSCN-HOLD for I2C0
  mPlatformNvsAreaProtocol.Area->FMH0 = mSystemConfiguration.PchSerialIoTimingFMH0;  // [FMH0] FMCN-HIGH for I2C0
  mPlatformNvsAreaProtocol.Area->FML0 = mSystemConfiguration.PchSerialIoTimingFML0;  // [FML0] FMCN-LOW  for I2C0
  mPlatformNvsAreaProtocol.Area->FMD0 = mSystemConfiguration.PchSerialIoTimingFMD0;  // [FMD0] FMCN-HOLD for I2C0
  mPlatformNvsAreaProtocol.Area->FPH0 = mSystemConfiguration.PchSerialIoTimingFPH0;  // [FPH0] FPCN-HIGH for I2C0
  mPlatformNvsAreaProtocol.Area->FPL0 = mSystemConfiguration.PchSerialIoTimingFPL0;  // [FPL0] FPCN-LOW  for I2C0
  mPlatformNvsAreaProtocol.Area->FPD0 = mSystemConfiguration.PchSerialIoTimingFPD0;  // [FPD0] FPCN-HOLD for I2C0
  mPlatformNvsAreaProtocol.Area->HSH0 = mSystemConfiguration.PchSerialIoTimingHSH0;  // [HSH0] HSCN-HIGH for I2C0
  mPlatformNvsAreaProtocol.Area->HSL0 = mSystemConfiguration.PchSerialIoTimingHSL0;  // [HSL0] HSCN-LOW  for I2C0
  mPlatformNvsAreaProtocol.Area->HSD0 = mSystemConfiguration.PchSerialIoTimingHSD0;  // [HSD0] HSCN-HOLD for I2C0

  mPlatformNvsAreaProtocol.Area->SSH1 = mSystemConfiguration.PchSerialIoTimingSSH1;  // [SSH1] SSCN-HIGH for I2C1
  mPlatformNvsAreaProtocol.Area->SSL1 = mSystemConfiguration.PchSerialIoTimingSSL1;  // [SSL1] SSCN-LOW  for I2C1
  mPlatformNvsAreaProtocol.Area->SSD1 = mSystemConfiguration.PchSerialIoTimingSSD1;  // [SSD1] SSCN-HOLD for I2C1
  mPlatformNvsAreaProtocol.Area->FMH1 = mSystemConfiguration.PchSerialIoTimingFMH1;  // [FMH1] FMCN-HIGH for I2C1
  mPlatformNvsAreaProtocol.Area->FML1 = mSystemConfiguration.PchSerialIoTimingFML1;  // [FML1] FMCN-LOW  for I2C1
  mPlatformNvsAreaProtocol.Area->FMD1 = mSystemConfiguration.PchSerialIoTimingFMD1;  // [FMD1] FMCN-HOLD for I2C1
  mPlatformNvsAreaProtocol.Area->FPH1 = mSystemConfiguration.PchSerialIoTimingFPH1;  // [FPH1] FPCN-HIGH for I2C1
  mPlatformNvsAreaProtocol.Area->FPL1 = mSystemConfiguration.PchSerialIoTimingFPL1;  // [FPL1] FPCN-LOW  for I2C1
  mPlatformNvsAreaProtocol.Area->FPD1 = mSystemConfiguration.PchSerialIoTimingFPD1;  // [FPD1] FPCN-HOLD for I2C1
  mPlatformNvsAreaProtocol.Area->HSH1 = mSystemConfiguration.PchSerialIoTimingHSH1;  // [HSH1] HSCN-HIGH for I2C1
  mPlatformNvsAreaProtocol.Area->HSL1 = mSystemConfiguration.PchSerialIoTimingHSL1;  // [HSL1] HSCN-LOW  for I2C1
  mPlatformNvsAreaProtocol.Area->HSD1 = mSystemConfiguration.PchSerialIoTimingHSD1;  // [HSD1] HSCN-HOLD for I2C1

  mPlatformNvsAreaProtocol.Area->SSH2 = mSystemConfiguration.PchSerialIoTimingSSH2;  // [SSH2] SSCN-HIGH for I2C2
  mPlatformNvsAreaProtocol.Area->SSL2 = mSystemConfiguration.PchSerialIoTimingSSL2;  // [SSL2] SSCN-LOW  for I2C2
  mPlatformNvsAreaProtocol.Area->SSD2 = mSystemConfiguration.PchSerialIoTimingSSD2;  // [SSD2] SSCN-HOLD for I2C2
  mPlatformNvsAreaProtocol.Area->FMH2 = mSystemConfiguration.PchSerialIoTimingFMH2;  // [FMH2] FMCN-HIGH for I2C2
  mPlatformNvsAreaProtocol.Area->FML2 = mSystemConfiguration.PchSerialIoTimingFML2;  // [FML2] FMCN-LOW  for I2C2
  mPlatformNvsAreaProtocol.Area->FMD2 = mSystemConfiguration.PchSerialIoTimingFMD2;  // [FMD2] FMCN-HOLD for I2C2
  mPlatformNvsAreaProtocol.Area->FPH2 = mSystemConfiguration.PchSerialIoTimingFPH2;  // [FPH2] FPCN-HIGH for I2C2
  mPlatformNvsAreaProtocol.Area->FPL2 = mSystemConfiguration.PchSerialIoTimingFPL2;  // [FPL2] FPCN-LOW  for I2C2
  mPlatformNvsAreaProtocol.Area->FPD2 = mSystemConfiguration.PchSerialIoTimingFPD2;  // [FPD2] FPCN-HOLD for I2C2
  mPlatformNvsAreaProtocol.Area->HSH2 = mSystemConfiguration.PchSerialIoTimingHSH2;  // [HSH2] HSCN-HIGH for I2C2
  mPlatformNvsAreaProtocol.Area->HSL2 = mSystemConfiguration.PchSerialIoTimingHSL2;  // [HSL2] HSCN-LOW  for I2C2
  mPlatformNvsAreaProtocol.Area->HSD2 = mSystemConfiguration.PchSerialIoTimingHSD2;  // [HSD2] HSCN-HOLD for I2C2

  mPlatformNvsAreaProtocol.Area->SSH3 = mSystemConfiguration.PchSerialIoTimingSSH3;  // [SSH3] SSCN-HIGH for I2C3
  mPlatformNvsAreaProtocol.Area->SSL3 = mSystemConfiguration.PchSerialIoTimingSSL3;  // [SSL3] SSCN-LOW  for I2C3
  mPlatformNvsAreaProtocol.Area->SSD3 = mSystemConfiguration.PchSerialIoTimingSSD3;  // [SSD3] SSCN-HOLD for I2C3
  mPlatformNvsAreaProtocol.Area->FMH3 = mSystemConfiguration.PchSerialIoTimingFMH3;  // [FMH3] FMCN-HIGH for I2C3
  mPlatformNvsAreaProtocol.Area->FML3 = mSystemConfiguration.PchSerialIoTimingFML3;  // [FML3] FMCN-LOW  for I2C3
  mPlatformNvsAreaProtocol.Area->FMD3 = mSystemConfiguration.PchSerialIoTimingFMD3;  // [FMD3] FMCN-HOLD for I2C3
  mPlatformNvsAreaProtocol.Area->FPH3 = mSystemConfiguration.PchSerialIoTimingFPH3;  // [FPH3] FPCN-HIGH for I2C3
  mPlatformNvsAreaProtocol.Area->FPL3 = mSystemConfiguration.PchSerialIoTimingFPL3;  // [FPL3] FPCN-LOW  for I2C3
  mPlatformNvsAreaProtocol.Area->FPD3 = mSystemConfiguration.PchSerialIoTimingFPD3;  // [FPD3] FPCN-HOLD for I2C3
  mPlatformNvsAreaProtocol.Area->HSH3 = mSystemConfiguration.PchSerialIoTimingHSH3;  // [HSH3] HSCN-HIGH for I2C3
  mPlatformNvsAreaProtocol.Area->HSL3 = mSystemConfiguration.PchSerialIoTimingHSL3;  // [HSL3] HSCN-LOW  for I2C3
  mPlatformNvsAreaProtocol.Area->HSD3 = mSystemConfiguration.PchSerialIoTimingHSD3;  // [HSD3] HSCN-HOLD for I2C3

  mPlatformNvsAreaProtocol.Area->SSH4 = mSystemConfiguration.PchSerialIoTimingSSH4;  // [SSH4] SSCN-HIGH for I2C4
  mPlatformNvsAreaProtocol.Area->SSL4 = mSystemConfiguration.PchSerialIoTimingSSL4;  // [SSL4] SSCN-LOW  for I2C4
  mPlatformNvsAreaProtocol.Area->SSD4 = mSystemConfiguration.PchSerialIoTimingSSD4;  // [SSD4] SSCN-HOLD for I2C4
  mPlatformNvsAreaProtocol.Area->FMH4 = mSystemConfiguration.PchSerialIoTimingFMH4;  // [FMH4] FMCN-HIGH for I2C4
  mPlatformNvsAreaProtocol.Area->FML4 = mSystemConfiguration.PchSerialIoTimingFML4;  // [FML4] FMCN-LOW  for I2C4
  mPlatformNvsAreaProtocol.Area->FMD4 = mSystemConfiguration.PchSerialIoTimingFMD4;  // [FMD4] FMCN-HOLD for I2C4
  mPlatformNvsAreaProtocol.Area->FPH4 = mSystemConfiguration.PchSerialIoTimingFPH4;  // [FPH4] FPCN-HIGH for I2C4
  mPlatformNvsAreaProtocol.Area->FPL4 = mSystemConfiguration.PchSerialIoTimingFPL4;  // [FPL4] FPCN-LOW  for I2C4
  mPlatformNvsAreaProtocol.Area->FPD4 = mSystemConfiguration.PchSerialIoTimingFPD4;  // [FPD4] FPCN-HOLD for I2C4
  mPlatformNvsAreaProtocol.Area->HSH4 = mSystemConfiguration.PchSerialIoTimingHSH4;  // [HSH4] HSCN-HIGH for I2C4
  mPlatformNvsAreaProtocol.Area->HSL4 = mSystemConfiguration.PchSerialIoTimingHSL4;  // [HSL4] HSCN-LOW  for I2C4
  mPlatformNvsAreaProtocol.Area->HSD4 = mSystemConfiguration.PchSerialIoTimingHSD4;  // [HSD4] HSCN-HOLD for I2C4

  mPlatformNvsAreaProtocol.Area->SSH5 = mSystemConfiguration.PchSerialIoTimingSSH5;  // [SSH5] SSCN-HIGH for I2C5
  mPlatformNvsAreaProtocol.Area->SSL5 = mSystemConfiguration.PchSerialIoTimingSSL5;  // [SSL5] SSCN-LOW  for I2C5
  mPlatformNvsAreaProtocol.Area->SSD5 = mSystemConfiguration.PchSerialIoTimingSSD5;  // [SSD5] SSCN-HOLD for I2C5
  mPlatformNvsAreaProtocol.Area->FMH5 = mSystemConfiguration.PchSerialIoTimingFMH5;  // [FMH5] FMCN-HIGH for I2C5
  mPlatformNvsAreaProtocol.Area->FML5 = mSystemConfiguration.PchSerialIoTimingFML5;  // [FML5] FMCN-LOW  for I2C5
  mPlatformNvsAreaProtocol.Area->FMD5 = mSystemConfiguration.PchSerialIoTimingFMD5;  // [FMD5] FMCN-HOLD for I2C5
  mPlatformNvsAreaProtocol.Area->FPH5 = mSystemConfiguration.PchSerialIoTimingFPH5;  // [FPH5] FPCN-HIGH for I2C5
  mPlatformNvsAreaProtocol.Area->FPL5 = mSystemConfiguration.PchSerialIoTimingFPL5;  // [FPL5] FPCN-LOW  for I2C5
  mPlatformNvsAreaProtocol.Area->FPD5 = mSystemConfiguration.PchSerialIoTimingFPD5;  // [FPD5] FPCN-HOLD for I2C5
  mPlatformNvsAreaProtocol.Area->HSH5 = mSystemConfiguration.PchSerialIoTimingHSH5;  // [HSH5] HSCN-HIGH for I2C5
  mPlatformNvsAreaProtocol.Area->HSL5 = mSystemConfiguration.PchSerialIoTimingHSL5;  // [HSL5] HSCN-LOW  for I2C5
  mPlatformNvsAreaProtocol.Area->HSD5 = mSystemConfiguration.PchSerialIoTimingHSD5;  // [HSD5] HSCN-HOLD for I2C5
  mPlatformNvsAreaProtocol.Area->SSH6 = mSystemConfiguration.PchSerialIoTimingSSH6;  // [SSH6] SSCN-HIGH for I2C6
  mPlatformNvsAreaProtocol.Area->SSL6 = mSystemConfiguration.PchSerialIoTimingSSL6;  // [SSL6] SSCN-LOW  for I2C6
  mPlatformNvsAreaProtocol.Area->SSD6 = mSystemConfiguration.PchSerialIoTimingSSD6;  // [SSD6] SSCN-HOLD for I2C6
  mPlatformNvsAreaProtocol.Area->FMH6 = mSystemConfiguration.PchSerialIoTimingFMH6;  // [FMH6] FMCN-HIGH for I2C6
  mPlatformNvsAreaProtocol.Area->FML6 = mSystemConfiguration.PchSerialIoTimingFML6;  // [FML6] FMCN-LOW  for I2C6
  mPlatformNvsAreaProtocol.Area->FMD6 = mSystemConfiguration.PchSerialIoTimingFMD6;  // [FMD6] FMCN-HOLD for I2C6
  mPlatformNvsAreaProtocol.Area->FPH6 = mSystemConfiguration.PchSerialIoTimingFPH6;  // [FPH6] FPCN-HIGH for I2C6
  mPlatformNvsAreaProtocol.Area->FPL6 = mSystemConfiguration.PchSerialIoTimingFPL6;  // [FPL6] FPCN-LOW  for I2C6
  mPlatformNvsAreaProtocol.Area->FPD6 = mSystemConfiguration.PchSerialIoTimingFPD6;  // [FPD6] FPCN-HOLD for I2C6
  mPlatformNvsAreaProtocol.Area->HSH6 = mSystemConfiguration.PchSerialIoTimingHSH6;  // [HSH6] HSCN-HIGH for I2C6
  mPlatformNvsAreaProtocol.Area->HSL6 = mSystemConfiguration.PchSerialIoTimingHSL6;  // [HSL6] HSCN-LOW  for I2C6
  mPlatformNvsAreaProtocol.Area->HSD6 = mSystemConfiguration.PchSerialIoTimingHSD6;  // [HSD6] HSCN-HOLD for I2C6

  mPlatformNvsAreaProtocol.Area->SSH7 = mSystemConfiguration.PchSerialIoTimingSSH7;  // [SSH7] SSCN-HIGH for I2C7
  mPlatformNvsAreaProtocol.Area->SSL7 = mSystemConfiguration.PchSerialIoTimingSSL7;  // [SSL7] SSCN-LOW  for I2C7
  mPlatformNvsAreaProtocol.Area->SSD7 = mSystemConfiguration.PchSerialIoTimingSSD7;  // [SSD7] SSCN-HOLD for I2C7
  mPlatformNvsAreaProtocol.Area->FMH7 = mSystemConfiguration.PchSerialIoTimingFMH7;  // [FMH7] FMCN-HIGH for I2C7
  mPlatformNvsAreaProtocol.Area->FML7 = mSystemConfiguration.PchSerialIoTimingFML7;  // [FML7] FMCN-LOW  for I2C7
  mPlatformNvsAreaProtocol.Area->FMD7 = mSystemConfiguration.PchSerialIoTimingFMD7;  // [FMD7] FMCN-HOLD for I2C7
  mPlatformNvsAreaProtocol.Area->FPH7 = mSystemConfiguration.PchSerialIoTimingFPH7;  // [FPH7] FPCN-HIGH for I2C7
  mPlatformNvsAreaProtocol.Area->FPL7 = mSystemConfiguration.PchSerialIoTimingFPL7;  // [FPL7] FPCN-LOW  for I2C7
  mPlatformNvsAreaProtocol.Area->FPD7 = mSystemConfiguration.PchSerialIoTimingFPD7;  // [FPD7] FPCN-HOLD for I2C7
  mPlatformNvsAreaProtocol.Area->HSH7 = mSystemConfiguration.PchSerialIoTimingHSH7;  // [HSH7] HSCN-HIGH for I2C7
  mPlatformNvsAreaProtocol.Area->HSL7 = mSystemConfiguration.PchSerialIoTimingHSL7;  // [HSL7] HSCN-LOW  for I2C7
  mPlatformNvsAreaProtocol.Area->HSD7 = mSystemConfiguration.PchSerialIoTimingHSD7;  // [HSD7] HSCN-HOLD for I2C7

  mPlatformNvsAreaProtocol.Area->M0C0 = mSystemConfiguration.PchSerialIoTimingM0C0;  // [M0C0] M0D3 for I2C0
  mPlatformNvsAreaProtocol.Area->M1C0 = mSystemConfiguration.PchSerialIoTimingM1C0;  // [M1C0] M1D3 for I2C0
  mPlatformNvsAreaProtocol.Area->M0C1 = mSystemConfiguration.PchSerialIoTimingM0C1;  // [M0C1] M0D3 for I2C1
  mPlatformNvsAreaProtocol.Area->M1C1 = mSystemConfiguration.PchSerialIoTimingM1C1;  // [M1C1] M1D3 for I2C1
  mPlatformNvsAreaProtocol.Area->M0C2 = mSystemConfiguration.PchSerialIoTimingM0C2;  // [M0C2] M0D3 for I2C2
  mPlatformNvsAreaProtocol.Area->M1C2 = mSystemConfiguration.PchSerialIoTimingM1C2;  // [M1C2] M1D3 for I2C2
  mPlatformNvsAreaProtocol.Area->M0C3 = mSystemConfiguration.PchSerialIoTimingM0C3;  // [M0C3] M0D3 for I2C3
  mPlatformNvsAreaProtocol.Area->M1C3 = mSystemConfiguration.PchSerialIoTimingM1C3;  // [M1C3] M1D3 for I2C3
  mPlatformNvsAreaProtocol.Area->M0C4 = mSystemConfiguration.PchSerialIoTimingM0C4;  // [M0C4] M0D3 for I2C4
  mPlatformNvsAreaProtocol.Area->M1C4 = mSystemConfiguration.PchSerialIoTimingM1C4;  // [M1C4] M1D3 for I2C4
  mPlatformNvsAreaProtocol.Area->M0C5 = mSystemConfiguration.PchSerialIoTimingM0C5;  // [M0C5] M0D3 for I2C5
  mPlatformNvsAreaProtocol.Area->M1C5 = mSystemConfiguration.PchSerialIoTimingM1C5;  // [M1C5] M1D3 for I2C5
  mPlatformNvsAreaProtocol.Area->M0CC = mSystemConfiguration.PchSerialIoTimingM0CC;  // [M0CC] M0D3 for I2C6
  mPlatformNvsAreaProtocol.Area->M1CC = mSystemConfiguration.PchSerialIoTimingM1CC;  // [M1CC] M1D3 for I2C6
  mPlatformNvsAreaProtocol.Area->M0CD = mSystemConfiguration.PchSerialIoTimingM0CD;  // [M0CD] M0D3 for I2C7
  mPlatformNvsAreaProtocol.Area->M1CD = mSystemConfiguration.PchSerialIoTimingM1CD;  // [M1CD] M1D3 for I2C7

  mPlatformNvsAreaProtocol.Area->M0C6 = mSystemConfiguration.PchSerialIoTimingM0C6;  // [M0C6] M0D3 for SPI0
  mPlatformNvsAreaProtocol.Area->M1C6 = mSystemConfiguration.PchSerialIoTimingM1C6;  // [M1C6] M1D3 for SPI0
  mPlatformNvsAreaProtocol.Area->M0C7 = mSystemConfiguration.PchSerialIoTimingM0C7;  // [M0C7] M0D3 for SPI1
  mPlatformNvsAreaProtocol.Area->M1C7 = mSystemConfiguration.PchSerialIoTimingM1C7;  // [M1C7] M1D3 for SPI1
  mPlatformNvsAreaProtocol.Area->M0C8 = mSystemConfiguration.PchSerialIoTimingM0C8;  // [M0C8] M0D3 for SPI2
  mPlatformNvsAreaProtocol.Area->M1C8 = mSystemConfiguration.PchSerialIoTimingM1C8;  // [M1C8] M1D3 for SPI2
  mPlatformNvsAreaProtocol.Area->M0C9 = mSystemConfiguration.PchSerialIoTimingM0C9;  // [M0C9] M0D3 for UART0
  mPlatformNvsAreaProtocol.Area->M1C9 = mSystemConfiguration.PchSerialIoTimingM1C9;  // [M1C9] M1D3 for UART0
  mPlatformNvsAreaProtocol.Area->M0CA = mSystemConfiguration.PchSerialIoTimingM0CA;  // [M0CA] M0D3 for UART1
  mPlatformNvsAreaProtocol.Area->M1CA = mSystemConfiguration.PchSerialIoTimingM1CA;  // [M1CA] M1D3 for UART1
  mPlatformNvsAreaProtocol.Area->M0CB = mSystemConfiguration.PchSerialIoTimingM0CB;  // [M0CB] M0D3 for UART2
  mPlatformNvsAreaProtocol.Area->M1CB = mSystemConfiguration.PchSerialIoTimingM1CB;  // [M1CB] M1D3 for UART2

  mPlatformNvsAreaProtocol.Area->FingerPrintSleepGpio        = PcdGet32 (PcdFingerPrintSleepGpio);
  mPlatformNvsAreaProtocol.Area->FingerPrintIrqGpio          = PcdGet32 (PcdFingerPrintIrqGpio);
  mPlatformNvsAreaProtocol.Area->WwanModemBaseBandResetGpio  = PcdGet32(PcdWwanModemBaseBandResetGpio);
  mPlatformNvsAreaProtocol.Area->DiscreteBtModuleRfKillGpio  = PcdGet32 (PcdBtRfKillGpio);
  mPlatformNvsAreaProtocol.Area->DiscreteBtModuleIrqGpio     = PcdGet32 (PcdBtIrqGpio);
  mPlatformNvsAreaProtocol.Area->TouchpadIrqGpio             = PcdGet32 (PcdTouchpadIrqGpio);
  mPlatformNvsAreaProtocol.Area->TouchpanelIrqGpio           = PcdGet32 (PcdTouchpanelIrqGpio);

  mPlatformNvsAreaProtocol.Area->HomeButtonInterrupt         = PcdGet32 (PcdHomeButtonInterrupt);
  mPlatformNvsAreaProtocol.Area->VolumeUpButtonInterrupt     = PcdGet32 (PcdVolumeUpButtonInterrupt);
  mPlatformNvsAreaProtocol.Area->VolumeDownButtonInterrupt   = PcdGet32 (PcdVolumeDownButtonInterrupt);

  mPlatformNvsAreaProtocol.Area->Revision       = PLATFORM_NVS_AREA_REVISION_1; // for TPM related fields
  if (IsSimicsEnvironment ()) {
    mPlatformNvsAreaProtocol.Area->Ps2MouseEnable = IsPs2MouseConnected ();
    mPlatformNvsAreaProtocol.Area->Ps2KbMsEnable  = mSystemConfiguration.Ps2KbMsEnable;
  } else {
    mPlatformNvsAreaProtocol.Area->Ps2MouseEnable = FALSE;
    mPlatformNvsAreaProtocol.Area->Ps2KbMsEnable  = FALSE;
  }

  //
  // Feature Specific RVP Details
  //
  mPlatformNvsAreaProtocol.Area->UsbTypeCSupport                      = PcdGetBool (PcdUsbTypeCSupport);
  mPlatformNvsAreaProtocol.Area->PcdTsOnDimmTemperature               = PcdGetBool (PcdTsOnDimmTemperature);
  mPlatformNvsAreaProtocol.Area->PcdRealBattery1Control               = PcdGet8 (PcdRealBattery1Control);
  mPlatformNvsAreaProtocol.Area->PcdRealBattery2Control               = PcdGet8 (PcdRealBattery2Control);
  mPlatformNvsAreaProtocol.Area->PcdMipiCamSensor                     = PcdGetBool (PcdMipiCamSensor);
  if (IsSimicsEnvironment ()) {
    mPlatformNvsAreaProtocol.Area->PcdNCT6776FCOM                       = PcdGetBool (PcdNCT6776FCOM);
    mPlatformNvsAreaProtocol.Area->PcdNCT6776FSIO                       = PcdGetBool (PcdNCT6776FSIO);
    mPlatformNvsAreaProtocol.Area->PcdNCT6776FHWMON                     = PcdGetBool (PcdNCT6776FHWMON);
    mPlatformNvsAreaProtocol.Area->PcdH8S2113SIO                        = PcdGetBool (PcdH8S2113SIO);
  } else {
    mPlatformNvsAreaProtocol.Area->PcdNCT6776FCOM                       = FALSE;
    mPlatformNvsAreaProtocol.Area->PcdNCT6776FSIO                       = FALSE;
    mPlatformNvsAreaProtocol.Area->PcdNCT6776FHWMON                     = FALSE;
    mPlatformNvsAreaProtocol.Area->PcdH8S2113SIO                        = FALSE;
  }
  mPlatformNvsAreaProtocol.Area->PcdSmcRuntimeSciPin                  = PcdGet32 (PcdSmcRuntimeSciPin);
  mPlatformNvsAreaProtocol.Area->PcdConvertableDockSupport            = PcdGetBool (PcdConvertableDockSupport);
  mPlatformNvsAreaProtocol.Area->PcdEcHotKeyF3Support                 = PcdGet8 (PcdEcHotKeyF3Support);
  mPlatformNvsAreaProtocol.Area->PcdEcHotKeyF4Support                 = PcdGet8 (PcdEcHotKeyF4Support);
  mPlatformNvsAreaProtocol.Area->PcdEcHotKeyF5Support                 = PcdGet8 (PcdEcHotKeyF5Support);
  mPlatformNvsAreaProtocol.Area->PcdEcHotKeyF6Support                 = PcdGet8 (PcdEcHotKeyF6Support);
  mPlatformNvsAreaProtocol.Area->PcdEcHotKeyF7Support                 = PcdGet8 (PcdEcHotKeyF7Support);
  mPlatformNvsAreaProtocol.Area->PcdEcHotKeyF8Support                 = PcdGet8 (PcdEcHotKeyF8Support);
  mPlatformNvsAreaProtocol.Area->PcdVirtualButtonVolumeUpSupport      = PcdGetBool (PcdVirtualButtonVolumeUpSupport);
  mPlatformNvsAreaProtocol.Area->PcdVirtualButtonVolumeDownSupport    = PcdGetBool (PcdVirtualButtonVolumeDownSupport);
  mPlatformNvsAreaProtocol.Area->PcdVirtualButtonHomeButtonSupport    = PcdGetBool (PcdVirtualButtonHomeButtonSupport);
  mPlatformNvsAreaProtocol.Area->PcdVirtualButtonRotationLockSupport  = PcdGetBool (PcdVirtualButtonRotationLockSupport);
  mPlatformNvsAreaProtocol.Area->PcdSlateModeSwitchSupport            = PcdGetBool (PcdSlateModeSwitchSupport);
  mPlatformNvsAreaProtocol.Area->PcdAcDcAutoSwitchSupport             = PcdGetBool (PcdAcDcAutoSwitchSupport);
  mPlatformNvsAreaProtocol.Area->PcdPmPowerButtonGpioPin              = PcdGet32 (PcdPmPowerButtonGpioPin);
  mPlatformNvsAreaProtocol.Area->PcdAcpiEnableAllButtonSupport        = PcdGetBool (PcdAcpiEnableAllButtonSupport);
  mPlatformNvsAreaProtocol.Area->PcdAcpiHidDriverButtonSupport        = PcdGetBool (PcdAcpiHidDriverButtonSupport);
  mPlatformNvsAreaProtocol.Area->PcdBatteryPresent                    = PcdGet8 (PcdBatteryPresent);

  //
  // Always report PS2MouseEnable for non-EC board
  //
  if (IsSimicsEnvironment ()) {
    if (mPlatformNvsAreaProtocol.Area->EcAvailable == PLATFORM_NVS_DEVICE_DISABLE) {
      mPlatformNvsAreaProtocol.Area->Ps2MouseEnable = 1;
    }
  }

  mPlatformNvsAreaProtocol.Area->UsbSensorHub    = mSystemConfiguration.UsbSensorHub;

  //
  // MipiCam sensor configuration
  //
  mPlatformNvsAreaProtocol.Area->MipiCamControlLogic0 = mSystemConfiguration.MipiCam_ControlLogic0;
  mPlatformNvsAreaProtocol.Area->MipiCamControlLogic1 = mSystemConfiguration.MipiCam_ControlLogic1;
  mPlatformNvsAreaProtocol.Area->MipiCamControlLogic2 = mSystemConfiguration.MipiCam_ControlLogic2;
  mPlatformNvsAreaProtocol.Area->MipiCamControlLogic3 = mSystemConfiguration.MipiCam_ControlLogic3;
  mPlatformNvsAreaProtocol.Area->MipiCamControlLogic4 = mSystemConfiguration.MipiCam_ControlLogic4;
  mPlatformNvsAreaProtocol.Area->MipiCamControlLogic5 = mSystemConfiguration.MipiCam_ControlLogic5;
  mPlatformNvsAreaProtocol.Area->MipiCamLink0Enabled = mSystemConfiguration.MipiCam_Link0;
  mPlatformNvsAreaProtocol.Area->MipiCamLink1Enabled = mSystemConfiguration.MipiCam_Link1;
  mPlatformNvsAreaProtocol.Area->MipiCamLink2Enabled = mSystemConfiguration.MipiCam_Link2;
  mPlatformNvsAreaProtocol.Area->MipiCamLink3Enabled = mSystemConfiguration.MipiCam_Link3;
  mPlatformNvsAreaProtocol.Area->MipiCamLink3Enabled = mSystemConfiguration.MipiCam_Link4;
  mPlatformNvsAreaProtocol.Area->MipiCamLink3Enabled = mSystemConfiguration.MipiCam_Link5;

  mPlatformNvsAreaProtocol.Area->MipiCamLanesClkDiv = mSystemConfiguration.MipiCam_LanesClkDiv;

  // MipiCam Control Logic 0 specific
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic0_Version = 1;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic0_Type = mSystemConfiguration.MipiCam_ControlLogic0_Type;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic0_CrdVersion = mSystemConfiguration.MipiCam_ControlLogic0_CrdVersion;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic0_InputClock = mSystemConfiguration.MipiCam_ControlLogic0_InputClock;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic0_GpioPinsEnabled = mSystemConfiguration.MipiCam_ControlLogic0_GpioPinsEnabled;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic0_I2cBus = mSystemConfiguration.MipiCam_ControlLogic0_I2cChannel;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic0_I2cAddress = mSystemConfiguration.MipiCam_ControlLogic0_I2cAddress;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic0_Pld = mSystemConfiguration.MipiCam_ControlLogic0_Pld;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic0_Wled1FlashMaxCurrent = mSystemConfiguration.MipiCam_ControlLogic0_Wled1FlashMaxCurrent;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic0_Wled1TorchMaxCurrent = mSystemConfiguration.MipiCam_ControlLogic0_Wled1TorchMaxCurrent;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic0_Wled2FlashMaxCurrent = mSystemConfiguration.MipiCam_ControlLogic0_Wled2FlashMaxCurrent;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic0_Wled2TorchMaxCurrent = mSystemConfiguration.MipiCam_ControlLogic0_Wled2TorchMaxCurrent;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic0_SubPlatformId = mSystemConfiguration.MipiCam_ControlLogic0_SubPlatformId;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic0_Wled1Type = mSystemConfiguration.MipiCam_ControlLogic0_Wled1Type;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic0_Wled2Type = mSystemConfiguration.MipiCam_ControlLogic0_Wled2Type;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic0_PchClockSource = mSystemConfiguration.MipiCam_ControlLogic0_PchClockSource;

  for (Index = 0; Index < MIPICAM_GPIO_COUNT; Index++) {
    if (Index < mSystemConfiguration.MipiCam_ControlLogic0_GpioPinsEnabled) {
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic0_GpioGroupPadNumber[Index] = mSystemConfiguration.MipiCam_ControlLogic0_GpioGroupPadNumber[Index];
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic0_GpioGroupNumber[Index] = mSystemConfiguration.MipiCam_ControlLogic0_GpioGroupNumber[Index];
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic0_GpioFunction[Index] = mSystemConfiguration.MipiCam_ControlLogic0_GpioFunction[Index];
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic0_GpioActiveValue[Index] = mSystemConfiguration.MipiCam_ControlLogic0_GpioActiveValue[Index];
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic0_GpioInitialValue[Index] = mSystemConfiguration.MipiCam_ControlLogic0_GpioInitialValue[Index];
    } else {
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic0_GpioGroupPadNumber[Index] = 0;
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic0_GpioGroupNumber[Index] = 0;
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic0_GpioFunction[Index] = 0;
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic0_GpioActiveValue[Index] = 1;
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic0_GpioInitialValue[Index] = 0;
    }
  }

  // MipiCam Control Logic 1 specific
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic1_Version = 1;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic1_Type = mSystemConfiguration.MipiCam_ControlLogic1_Type;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic1_CrdVersion = mSystemConfiguration.MipiCam_ControlLogic1_CrdVersion;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic1_InputClock = mSystemConfiguration.MipiCam_ControlLogic1_InputClock;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic1_GpioPinsEnabled = mSystemConfiguration.MipiCam_ControlLogic1_GpioPinsEnabled;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic1_I2cBus = mSystemConfiguration.MipiCam_ControlLogic1_I2cChannel;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic1_I2cAddress = mSystemConfiguration.MipiCam_ControlLogic1_I2cAddress;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic1_Pld = mSystemConfiguration.MipiCam_ControlLogic1_Pld;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic1_Wled1FlashMaxCurrent = mSystemConfiguration.MipiCam_ControlLogic1_Wled1FlashMaxCurrent;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic1_Wled1TorchMaxCurrent = mSystemConfiguration.MipiCam_ControlLogic1_Wled1TorchMaxCurrent;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic1_Wled2FlashMaxCurrent = mSystemConfiguration.MipiCam_ControlLogic1_Wled2FlashMaxCurrent;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic1_Wled2TorchMaxCurrent = mSystemConfiguration.MipiCam_ControlLogic1_Wled2TorchMaxCurrent;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic1_SubPlatformId = mSystemConfiguration.MipiCam_ControlLogic1_SubPlatformId;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic1_Wled1Type = mSystemConfiguration.MipiCam_ControlLogic1_Wled1Type;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic1_Wled2Type = mSystemConfiguration.MipiCam_ControlLogic1_Wled2Type;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic1_PchClockSource = mSystemConfiguration.MipiCam_ControlLogic1_PchClockSource;

  for (Index = 0; Index < MIPICAM_GPIO_COUNT; Index++) {
    if (Index < mSystemConfiguration.MipiCam_ControlLogic1_GpioPinsEnabled) {
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic1_GpioGroupPadNumber[Index] = mSystemConfiguration.MipiCam_ControlLogic1_GpioGroupPadNumber[Index];
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic1_GpioGroupNumber[Index] = mSystemConfiguration.MipiCam_ControlLogic1_GpioGroupNumber[Index];
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic1_GpioFunction[Index] = mSystemConfiguration.MipiCam_ControlLogic1_GpioFunction[Index];
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic1_GpioActiveValue[Index] = mSystemConfiguration.MipiCam_ControlLogic1_GpioActiveValue[Index];
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic1_GpioInitialValue[Index] = mSystemConfiguration.MipiCam_ControlLogic1_GpioInitialValue[Index];
    } else {
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic1_GpioGroupPadNumber[Index] = 0;
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic1_GpioGroupNumber[Index] = 0;
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic1_GpioFunction[Index] = 0;
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic1_GpioActiveValue[Index] = 1;
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic1_GpioInitialValue[Index] = 0;
    }
  }

  // MipiCam Control Logic 2 specific
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic2_Version = 1;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic2_Type = mSystemConfiguration.MipiCam_ControlLogic2_Type;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic2_CrdVersion = mSystemConfiguration.MipiCam_ControlLogic2_CrdVersion;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic2_InputClock = mSystemConfiguration.MipiCam_ControlLogic2_InputClock;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic2_GpioPinsEnabled = mSystemConfiguration.MipiCam_ControlLogic2_GpioPinsEnabled;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic2_I2cBus = mSystemConfiguration.MipiCam_ControlLogic2_I2cChannel;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic2_I2cAddress = mSystemConfiguration.MipiCam_ControlLogic2_I2cAddress;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic2_Pld = mSystemConfiguration.MipiCam_ControlLogic2_Pld;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic2_Wled1FlashMaxCurrent = mSystemConfiguration.MipiCam_ControlLogic2_Wled1FlashMaxCurrent;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic2_Wled1TorchMaxCurrent = mSystemConfiguration.MipiCam_ControlLogic2_Wled1TorchMaxCurrent;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic2_Wled2FlashMaxCurrent = mSystemConfiguration.MipiCam_ControlLogic2_Wled2FlashMaxCurrent;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic2_Wled2TorchMaxCurrent = mSystemConfiguration.MipiCam_ControlLogic2_Wled2TorchMaxCurrent;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic2_SubPlatformId = mSystemConfiguration.MipiCam_ControlLogic2_SubPlatformId;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic2_Wled1Type = mSystemConfiguration.MipiCam_ControlLogic2_Wled1Type;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic2_Wled2Type = mSystemConfiguration.MipiCam_ControlLogic2_Wled2Type;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic2_PchClockSource = mSystemConfiguration.MipiCam_ControlLogic2_PchClockSource;

  for (Index = 0; Index < MIPICAM_GPIO_COUNT; Index++) {
    if (Index < mSystemConfiguration.MipiCam_ControlLogic2_GpioPinsEnabled) {
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic2_GpioGroupPadNumber[Index] = mSystemConfiguration.MipiCam_ControlLogic2_GpioGroupPadNumber[Index];
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic2_GpioGroupNumber[Index] = mSystemConfiguration.MipiCam_ControlLogic2_GpioGroupNumber[Index];
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic2_GpioFunction[Index] = mSystemConfiguration.MipiCam_ControlLogic2_GpioFunction[Index];
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic2_GpioActiveValue[Index] = mSystemConfiguration.MipiCam_ControlLogic2_GpioActiveValue[Index];
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic2_GpioInitialValue[Index] = mSystemConfiguration.MipiCam_ControlLogic2_GpioInitialValue[Index];
    } else {
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic2_GpioGroupPadNumber[Index] = 0;
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic2_GpioGroupNumber[Index] = 0;
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic2_GpioFunction[Index] = 0;
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic2_GpioActiveValue[Index] = 1;
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic2_GpioInitialValue[Index] = 0;
    }
  }

  // MipiCam Control Logic 3 specific
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic3_Version = 1;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic3_Type = mSystemConfiguration.MipiCam_ControlLogic3_Type;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic3_CrdVersion = mSystemConfiguration.MipiCam_ControlLogic3_CrdVersion;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic3_InputClock = mSystemConfiguration.MipiCam_ControlLogic3_InputClock;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic3_GpioPinsEnabled = mSystemConfiguration.MipiCam_ControlLogic3_GpioPinsEnabled;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic3_I2cBus = mSystemConfiguration.MipiCam_ControlLogic3_I2cChannel;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic3_I2cAddress = mSystemConfiguration.MipiCam_ControlLogic3_I2cAddress;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic3_Pld = mSystemConfiguration.MipiCam_ControlLogic3_Pld;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic3_Wled1FlashMaxCurrent = mSystemConfiguration.MipiCam_ControlLogic3_Wled1FlashMaxCurrent;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic3_Wled1TorchMaxCurrent = mSystemConfiguration.MipiCam_ControlLogic3_Wled1TorchMaxCurrent;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic3_Wled2FlashMaxCurrent = mSystemConfiguration.MipiCam_ControlLogic3_Wled2FlashMaxCurrent;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic3_Wled2TorchMaxCurrent = mSystemConfiguration.MipiCam_ControlLogic3_Wled2TorchMaxCurrent;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic3_SubPlatformId = mSystemConfiguration.MipiCam_ControlLogic3_SubPlatformId;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic3_Wled1Type = mSystemConfiguration.MipiCam_ControlLogic3_Wled1Type;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic3_Wled2Type = mSystemConfiguration.MipiCam_ControlLogic3_Wled2Type;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic3_PchClockSource = mSystemConfiguration.MipiCam_ControlLogic3_PchClockSource;

  for (Index = 0; Index < MIPICAM_GPIO_COUNT; Index++) {
    if (Index < mSystemConfiguration.MipiCam_ControlLogic3_GpioPinsEnabled) {
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic3_GpioGroupPadNumber[Index] = mSystemConfiguration.MipiCam_ControlLogic3_GpioGroupPadNumber[Index];
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic3_GpioGroupNumber[Index] = mSystemConfiguration.MipiCam_ControlLogic3_GpioGroupNumber[Index];
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic3_GpioFunction[Index] = mSystemConfiguration.MipiCam_ControlLogic3_GpioFunction[Index];
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic3_GpioActiveValue[Index] = mSystemConfiguration.MipiCam_ControlLogic3_GpioActiveValue[Index];
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic3_GpioInitialValue[Index] = mSystemConfiguration.MipiCam_ControlLogic3_GpioInitialValue[Index];
    } else {
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic3_GpioGroupPadNumber[Index] = 0;
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic3_GpioGroupNumber[Index] = 0;
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic3_GpioFunction[Index] = 0;
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic3_GpioActiveValue[Index] = 1;
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic3_GpioInitialValue[Index] = 0;
    }
  }

  // MipiCam Control Logic 4 specific
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic4_Version = 1;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic4_Type = mSystemConfiguration.MipiCam_ControlLogic4_Type;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic4_CrdVersion = mSystemConfiguration.MipiCam_ControlLogic4_CrdVersion;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic4_InputClock = mSystemConfiguration.MipiCam_ControlLogic4_InputClock;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic4_GpioPinsEnabled = mSystemConfiguration.MipiCam_ControlLogic4_GpioPinsEnabled;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic4_I2cBus = mSystemConfiguration.MipiCam_ControlLogic4_I2cChannel;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic4_I2cAddress = mSystemConfiguration.MipiCam_ControlLogic4_I2cAddress;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic4_Pld = mSystemConfiguration.MipiCam_ControlLogic4_Pld;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic4_Wled1FlashMaxCurrent = mSystemConfiguration.MipiCam_ControlLogic4_Wled1FlashMaxCurrent;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic4_Wled1TorchMaxCurrent = mSystemConfiguration.MipiCam_ControlLogic4_Wled1TorchMaxCurrent;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic4_Wled2FlashMaxCurrent = mSystemConfiguration.MipiCam_ControlLogic4_Wled2FlashMaxCurrent;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic4_Wled2TorchMaxCurrent = mSystemConfiguration.MipiCam_ControlLogic4_Wled2TorchMaxCurrent;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic4_SubPlatformId = mSystemConfiguration.MipiCam_ControlLogic4_SubPlatformId;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic4_Wled1Type = mSystemConfiguration.MipiCam_ControlLogic4_Wled1Type;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic4_Wled2Type = mSystemConfiguration.MipiCam_ControlLogic4_Wled2Type;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic4_PchClockSource = mSystemConfiguration.MipiCam_ControlLogic4_PchClockSource;

  for (Index = 0; Index < MIPICAM_GPIO_COUNT; Index++) {
    if (Index < mSystemConfiguration.MipiCam_ControlLogic4_GpioPinsEnabled) {
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic4_GpioGroupPadNumber[Index] = mSystemConfiguration.MipiCam_ControlLogic4_GpioGroupPadNumber[Index];
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic4_GpioGroupNumber[Index] = mSystemConfiguration.MipiCam_ControlLogic4_GpioGroupNumber[Index];
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic4_GpioFunction[Index] = mSystemConfiguration.MipiCam_ControlLogic4_GpioFunction[Index];
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic4_GpioActiveValue[Index] = mSystemConfiguration.MipiCam_ControlLogic4_GpioActiveValue[Index];
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic4_GpioInitialValue[Index] = mSystemConfiguration.MipiCam_ControlLogic4_GpioInitialValue[Index];
    } else {
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic4_GpioGroupPadNumber[Index] = 0;
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic4_GpioGroupNumber[Index] = 0;
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic4_GpioFunction[Index] = 0;
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic4_GpioActiveValue[Index] = 1;
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic4_GpioInitialValue[Index] = 0;
    }
  }

  // MipiCam Control Logic 5 specific
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic5_Version = 1;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic5_Type = mSystemConfiguration.MipiCam_ControlLogic5_Type;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic5_CrdVersion = mSystemConfiguration.MipiCam_ControlLogic5_CrdVersion;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic5_InputClock = mSystemConfiguration.MipiCam_ControlLogic5_InputClock;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic5_GpioPinsEnabled = mSystemConfiguration.MipiCam_ControlLogic5_GpioPinsEnabled;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic5_I2cBus = mSystemConfiguration.MipiCam_ControlLogic5_I2cChannel;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic5_I2cAddress = mSystemConfiguration.MipiCam_ControlLogic5_I2cAddress;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic5_Pld = mSystemConfiguration.MipiCam_ControlLogic5_Pld;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic5_Wled1FlashMaxCurrent = mSystemConfiguration.MipiCam_ControlLogic5_Wled1FlashMaxCurrent;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic5_Wled1TorchMaxCurrent = mSystemConfiguration.MipiCam_ControlLogic5_Wled1TorchMaxCurrent;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic5_Wled2FlashMaxCurrent = mSystemConfiguration.MipiCam_ControlLogic5_Wled2FlashMaxCurrent;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic5_Wled2TorchMaxCurrent = mSystemConfiguration.MipiCam_ControlLogic5_Wled2TorchMaxCurrent;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic5_SubPlatformId = mSystemConfiguration.MipiCam_ControlLogic5_SubPlatformId;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic5_Wled1Type = mSystemConfiguration.MipiCam_ControlLogic5_Wled1Type;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic5_Wled2Type = mSystemConfiguration.MipiCam_ControlLogic5_Wled2Type;
  mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic5_PchClockSource = mSystemConfiguration.MipiCam_ControlLogic5_PchClockSource;

  for (Index = 0; Index < MIPICAM_GPIO_COUNT; Index++) {
    if (Index < mSystemConfiguration.MipiCam_ControlLogic5_GpioPinsEnabled) {
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic5_GpioGroupPadNumber[Index] = mSystemConfiguration.MipiCam_ControlLogic5_GpioGroupPadNumber[Index];
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic5_GpioGroupNumber[Index] = mSystemConfiguration.MipiCam_ControlLogic5_GpioGroupNumber[Index];
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic5_GpioFunction[Index] = mSystemConfiguration.MipiCam_ControlLogic5_GpioFunction[Index];
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic5_GpioActiveValue[Index] = mSystemConfiguration.MipiCam_ControlLogic5_GpioActiveValue[Index];
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic5_GpioInitialValue[Index] = mSystemConfiguration.MipiCam_ControlLogic5_GpioInitialValue[Index];
    } else {
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic5_GpioGroupPadNumber[Index] = 0;
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic5_GpioGroupNumber[Index] = 0;
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic5_GpioFunction[Index] = 0;
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic5_GpioActiveValue[Index] = 1;
      mPlatformNvsAreaProtocol.Area->MipiCamCtrlLogic5_GpioInitialValue[Index] = 0;
    }
  }

  // MipiCam Link0 specific
  mPlatformNvsAreaProtocol.Area->MipiCamLink0SensorModel = mSystemConfiguration.MipiCam_Link0_SensorModel;
  mPlatformNvsAreaProtocol.Area->MipiCamLink0Pld = mSystemConfiguration.MipiCam_Link0_CameraPhysicalLocation;
  ZeroMem(ModuleName, sizeof(UINT16) * MIPICAM_MODULE_NAME_LENGTH);
  // Need to copy to temporary alligned buffer due to pack(1) in SetupVariables.h
  CopyMem(ModuleName,mSystemConfiguration.MipiCam_Link0_ModuleName, sizeof(UINT16) * MIPICAM_MODULE_NAME_LENGTH);
  UnicodeStrToAsciiStrS (ModuleName, (CHAR8 *) mPlatformNvsAreaProtocol.Area->MipiCamLink0ModuleName, sizeof(mPlatformNvsAreaProtocol.Area->MipiCamLink0ModuleName));
  ZeroMem(ModuleName, sizeof(UINT16) * MIPICAM_MODULE_NAME_LENGTH);
  CopyMem(ModuleName,mSystemConfiguration.MipiCam_Link0_UserHid, sizeof(UINT16) * MIPICAM_HID_LENGTH);
  UnicodeStrToAsciiStrS (ModuleName, (CHAR8 *) mPlatformNvsAreaProtocol.Area->MipiCamLink0UserHid, sizeof(mPlatformNvsAreaProtocol.Area->MipiCamLink0UserHid));
  mPlatformNvsAreaProtocol.Area->MipiCamLink0I2cDevicesEnabled = mSystemConfiguration.MipiCam_Link0_I2cDevicesEnabled;
  mPlatformNvsAreaProtocol.Area->MipiCamLink0I2cBus = mSystemConfiguration.MipiCam_Link0_I2cChannel;

  // MipiCam Link0 I2C Devices
  for (Index = 0; Index < MIPICAM_I2C_DEVICES_COUNT; Index++) {
    mPlatformNvsAreaProtocol.Area->MipiCamLink0I2cAddrDev[Index] = mSystemConfiguration.MipiCam_Link0_I2cAddress[Index];
    mPlatformNvsAreaProtocol.Area->MipiCamLink0I2cDeviceType[Index] = mSystemConfiguration.MipiCam_Link0_I2cDeviceType[Index];
  }

  mPlatformNvsAreaProtocol.Area->MipiCamLink0DD_Version = 1;
  mPlatformNvsAreaProtocol.Area->MipiCamLink0DD_CrdVersion = mSystemConfiguration.MipiCam_Link0_DriverData_CrdVersion;
  mPlatformNvsAreaProtocol.Area->MipiCamLink0DD_LinkUsed = 3;
  mPlatformNvsAreaProtocol.Area->MipiCamLink0DD_LaneUsed = mSystemConfiguration.MipiCam_Link0_DriverData_LaneUsed;
  mPlatformNvsAreaProtocol.Area->MipiCamLink0DD_EepromType = mSystemConfiguration.MipiCam_Link0_DriverData_EepromType;
  mPlatformNvsAreaProtocol.Area->MipiCamLink0DD_VcmType = mSystemConfiguration.MipiCam_Link0_DriverData_VcmType;
  mPlatformNvsAreaProtocol.Area->MipiCamLink0DD_Mclk = mSystemConfiguration.MipiCam_Link0_DriverData_Mclk;
  mPlatformNvsAreaProtocol.Area->MipiCamLink0DD_ControlLogic = mSystemConfiguration.MipiCam_Link0_DriverData_ControlLogic;
  mPlatformNvsAreaProtocol.Area->MipiCamLink0DD_FlashSupport = mSystemConfiguration.MipiCam_Link0_DriverData_FlashSupport;
  mPlatformNvsAreaProtocol.Area->MipiCamLink0DD_PrivacyLed = mSystemConfiguration.MipiCam_Link0_DriverData_PrivacyLed;
  mPlatformNvsAreaProtocol.Area->MipiCamLink0DD_Degree = mSystemConfiguration.MipiCam_Link0_DriverData_Degree;
  mPlatformNvsAreaProtocol.Area->MipiCamLink0DD_PmicPosition = mSystemConfiguration.MipiCam_Link0_DriverData_PmicPosition;
  mPlatformNvsAreaProtocol.Area->MipiCamLink0DD_VoltageRail = mSystemConfiguration.MipiCam_Link0_DriverData_VoltageRail;
  mPlatformNvsAreaProtocol.Area->MipiCamLink0DD_PprValue    = mSystemConfiguration.MipiCam_Link0_DriverData_PprValue;
  mPlatformNvsAreaProtocol.Area->MipiCamLink0DD_PprUnit     = mSystemConfiguration.MipiCam_Link0_DriverData_PprUnit;

  // MipiCam Link1 specific
  mPlatformNvsAreaProtocol.Area->MipiCamLink1SensorModel = mSystemConfiguration.MipiCam_Link1_SensorModel;
  mPlatformNvsAreaProtocol.Area->MipiCamLink1Pld = mSystemConfiguration.MipiCam_Link1_CameraPhysicalLocation;
  ZeroMem(ModuleName, sizeof(UINT16) * MIPICAM_MODULE_NAME_LENGTH);
  // Need to copy to temporary alligned buffer due to pack(1) in SetupVariables.h
  CopyMem(ModuleName,mSystemConfiguration.MipiCam_Link1_ModuleName, sizeof(UINT16) * MIPICAM_MODULE_NAME_LENGTH);
  UnicodeStrToAsciiStrS (ModuleName, (CHAR8 *) mPlatformNvsAreaProtocol.Area->MipiCamLink1ModuleName, sizeof(mPlatformNvsAreaProtocol.Area->MipiCamLink1ModuleName));
  ZeroMem(ModuleName, sizeof(UINT16) * MIPICAM_MODULE_NAME_LENGTH);
  CopyMem(ModuleName,mSystemConfiguration.MipiCam_Link1_UserHid, sizeof(UINT16) * MIPICAM_HID_LENGTH);
  UnicodeStrToAsciiStrS (ModuleName, (CHAR8 *) mPlatformNvsAreaProtocol.Area->MipiCamLink1UserHid, sizeof(mPlatformNvsAreaProtocol.Area->MipiCamLink1UserHid));
  mPlatformNvsAreaProtocol.Area->MipiCamLink1I2cDevicesEnabled = mSystemConfiguration.MipiCam_Link1_I2cDevicesEnabled;
  mPlatformNvsAreaProtocol.Area->MipiCamLink1I2cBus = mSystemConfiguration.MipiCam_Link1_I2cChannel;

  // MipiCam Link1 I2C Devices
  for (Index = 0; Index < MIPICAM_I2C_DEVICES_COUNT; Index++) {
    mPlatformNvsAreaProtocol.Area->MipiCamLink1I2cAddrDev[Index] = mSystemConfiguration.MipiCam_Link1_I2cAddress[Index];
    mPlatformNvsAreaProtocol.Area->MipiCamLink1I2cDeviceType[Index] = mSystemConfiguration.MipiCam_Link1_I2cDeviceType[Index];
  }
  mPlatformNvsAreaProtocol.Area->MipiCamLink1DD_Version = 1;
  mPlatformNvsAreaProtocol.Area->MipiCamLink1DD_CrdVersion = mSystemConfiguration.MipiCam_Link1_DriverData_CrdVersion;
  mPlatformNvsAreaProtocol.Area->MipiCamLink1DD_LinkUsed = 6;
  mPlatformNvsAreaProtocol.Area->MipiCamLink1DD_LaneUsed = mSystemConfiguration.MipiCam_Link1_DriverData_LaneUsed;
  mPlatformNvsAreaProtocol.Area->MipiCamLink1DD_EepromType = mSystemConfiguration.MipiCam_Link1_DriverData_EepromType;
  mPlatformNvsAreaProtocol.Area->MipiCamLink1DD_VcmType = mSystemConfiguration.MipiCam_Link1_DriverData_VcmType;
  mPlatformNvsAreaProtocol.Area->MipiCamLink1DD_Mclk = mSystemConfiguration.MipiCam_Link1_DriverData_Mclk;
  mPlatformNvsAreaProtocol.Area->MipiCamLink1DD_ControlLogic = mSystemConfiguration.MipiCam_Link1_DriverData_ControlLogic;
  mPlatformNvsAreaProtocol.Area->MipiCamLink1DD_FlashSupport = mSystemConfiguration.MipiCam_Link1_DriverData_FlashSupport;
  mPlatformNvsAreaProtocol.Area->MipiCamLink1DD_PrivacyLed = mSystemConfiguration.MipiCam_Link1_DriverData_PrivacyLed;
  mPlatformNvsAreaProtocol.Area->MipiCamLink1DD_Degree = mSystemConfiguration.MipiCam_Link1_DriverData_Degree;
  mPlatformNvsAreaProtocol.Area->MipiCamLink1DD_PmicPosition = mSystemConfiguration.MipiCam_Link1_DriverData_PmicPosition;
  mPlatformNvsAreaProtocol.Area->MipiCamLink1DD_VoltageRail = mSystemConfiguration.MipiCam_Link1_DriverData_VoltageRail;
  mPlatformNvsAreaProtocol.Area->MipiCamLink1DD_PprValue    = mSystemConfiguration.MipiCam_Link1_DriverData_PprValue;
  mPlatformNvsAreaProtocol.Area->MipiCamLink1DD_PprUnit     = mSystemConfiguration.MipiCam_Link1_DriverData_PprUnit;

  // MipiCam Link2 specific
  mPlatformNvsAreaProtocol.Area->MipiCamLink2SensorModel = mSystemConfiguration.MipiCam_Link2_SensorModel;
  mPlatformNvsAreaProtocol.Area->MipiCamLink2Pld = mSystemConfiguration.MipiCam_Link2_CameraPhysicalLocation;
  ZeroMem(ModuleName, sizeof(UINT16) * MIPICAM_MODULE_NAME_LENGTH);
  // Need to copy to temporary alligned buffer due to pack(1) in SetupVariables.h
  CopyMem(ModuleName,mSystemConfiguration.MipiCam_Link2_ModuleName, sizeof(UINT16) * MIPICAM_MODULE_NAME_LENGTH);
  UnicodeStrToAsciiStrS (ModuleName, (CHAR8 *) mPlatformNvsAreaProtocol.Area->MipiCamLink2ModuleName, sizeof(mPlatformNvsAreaProtocol.Area->MipiCamLink2ModuleName));
  ZeroMem(ModuleName, sizeof(UINT16) * MIPICAM_MODULE_NAME_LENGTH);
  CopyMem(ModuleName,mSystemConfiguration.MipiCam_Link2_UserHid, sizeof(UINT16) * MIPICAM_HID_LENGTH);
  UnicodeStrToAsciiStrS (ModuleName, (CHAR8 *) mPlatformNvsAreaProtocol.Area->MipiCamLink2UserHid, sizeof(mPlatformNvsAreaProtocol.Area->MipiCamLink2UserHid));
  mPlatformNvsAreaProtocol.Area->MipiCamLink2I2cDevicesEnabled = mSystemConfiguration.MipiCam_Link2_I2cDevicesEnabled;
  mPlatformNvsAreaProtocol.Area->MipiCamLink2I2cBus = mSystemConfiguration.MipiCam_Link2_I2cChannel;

  // MipiCam Link2 I2C Devices
  for (Index = 0; Index < MIPICAM_I2C_DEVICES_COUNT; Index++) {
    mPlatformNvsAreaProtocol.Area->MipiCamLink2I2cAddrDev[Index] = mSystemConfiguration.MipiCam_Link2_I2cAddress[Index];
    mPlatformNvsAreaProtocol.Area->MipiCamLink2I2cDeviceType[Index] = mSystemConfiguration.MipiCam_Link2_I2cDeviceType[Index];
  }
  mPlatformNvsAreaProtocol.Area->MipiCamLink2DD_Version = 1;
  mPlatformNvsAreaProtocol.Area->MipiCamLink2DD_CrdVersion = mSystemConfiguration.MipiCam_Link2_DriverData_CrdVersion;
  mPlatformNvsAreaProtocol.Area->MipiCamLink2DD_LinkUsed = 9;
  mPlatformNvsAreaProtocol.Area->MipiCamLink2DD_LaneUsed = mSystemConfiguration.MipiCam_Link2_DriverData_LaneUsed;
  mPlatformNvsAreaProtocol.Area->MipiCamLink2DD_EepromType = mSystemConfiguration.MipiCam_Link2_DriverData_EepromType;
  mPlatformNvsAreaProtocol.Area->MipiCamLink2DD_VcmType = mSystemConfiguration.MipiCam_Link2_DriverData_VcmType;
  mPlatformNvsAreaProtocol.Area->MipiCamLink2DD_Mclk = mSystemConfiguration.MipiCam_Link2_DriverData_Mclk;
  mPlatformNvsAreaProtocol.Area->MipiCamLink2DD_ControlLogic = mSystemConfiguration.MipiCam_Link2_DriverData_ControlLogic;
  mPlatformNvsAreaProtocol.Area->MipiCamLink2DD_FlashSupport = mSystemConfiguration.MipiCam_Link2_DriverData_FlashSupport;
  mPlatformNvsAreaProtocol.Area->MipiCamLink2DD_PrivacyLed = mSystemConfiguration.MipiCam_Link2_DriverData_PrivacyLed;
  mPlatformNvsAreaProtocol.Area->MipiCamLink2DD_Degree = mSystemConfiguration.MipiCam_Link2_DriverData_Degree;
  mPlatformNvsAreaProtocol.Area->MipiCamLink2DD_PmicPosition = mSystemConfiguration.MipiCam_Link2_DriverData_PmicPosition;
  mPlatformNvsAreaProtocol.Area->MipiCamLink2DD_VoltageRail = mSystemConfiguration.MipiCam_Link2_DriverData_VoltageRail;
  mPlatformNvsAreaProtocol.Area->MipiCamLink2DD_PprValue    = mSystemConfiguration.MipiCam_Link2_DriverData_PprValue;
  mPlatformNvsAreaProtocol.Area->MipiCamLink2DD_PprUnit     = mSystemConfiguration.MipiCam_Link2_DriverData_PprUnit;

  // MipiCam Link3 specific
  mPlatformNvsAreaProtocol.Area->MipiCamLink3SensorModel = mSystemConfiguration.MipiCam_Link3_SensorModel;
  mPlatformNvsAreaProtocol.Area->MipiCamLink3Pld = mSystemConfiguration.MipiCam_Link3_CameraPhysicalLocation;
  ZeroMem(ModuleName, sizeof(UINT16) * MIPICAM_MODULE_NAME_LENGTH);
  // Need to copy to temporary alligned buffer due to pack(1) in SetupVariables.h
  CopyMem(ModuleName,mSystemConfiguration.MipiCam_Link3_ModuleName, sizeof(UINT16) * MIPICAM_MODULE_NAME_LENGTH);
  UnicodeStrToAsciiStrS (ModuleName, (CHAR8 *) mPlatformNvsAreaProtocol.Area->MipiCamLink3ModuleName, sizeof(mPlatformNvsAreaProtocol.Area->MipiCamLink3ModuleName));
  ZeroMem(ModuleName, sizeof(UINT16) * MIPICAM_MODULE_NAME_LENGTH);
  CopyMem(ModuleName,mSystemConfiguration.MipiCam_Link3_UserHid, sizeof(UINT16) * MIPICAM_HID_LENGTH);
  UnicodeStrToAsciiStrS (ModuleName, (CHAR8 *) mPlatformNvsAreaProtocol.Area->MipiCamLink3UserHid, sizeof(mPlatformNvsAreaProtocol.Area->MipiCamLink3UserHid));
  mPlatformNvsAreaProtocol.Area->MipiCamLink3I2cDevicesEnabled = mSystemConfiguration.MipiCam_Link3_I2cDevicesEnabled;
  mPlatformNvsAreaProtocol.Area->MipiCamLink3I2cBus = mSystemConfiguration.MipiCam_Link3_I2cChannel;

  // MipiCam Link3 I2C Devices
  for (Index = 0; Index < MIPICAM_I2C_DEVICES_COUNT; Index++) {
    mPlatformNvsAreaProtocol.Area->MipiCamLink3I2cAddrDev[Index] = mSystemConfiguration.MipiCam_Link3_I2cAddress[Index];
    mPlatformNvsAreaProtocol.Area->MipiCamLink3I2cDeviceType[Index] = mSystemConfiguration.MipiCam_Link3_I2cDeviceType[Index];
  }
  mPlatformNvsAreaProtocol.Area->MipiCamLink3DD_Version = 1;
  mPlatformNvsAreaProtocol.Area->MipiCamLink3DD_CrdVersion = mSystemConfiguration.MipiCam_Link3_DriverData_CrdVersion;
  mPlatformNvsAreaProtocol.Area->MipiCamLink3DD_LinkUsed = 7;
  mPlatformNvsAreaProtocol.Area->MipiCamLink3DD_LaneUsed = mSystemConfiguration.MipiCam_Link3_DriverData_LaneUsed;
  mPlatformNvsAreaProtocol.Area->MipiCamLink3DD_EepromType = mSystemConfiguration.MipiCam_Link3_DriverData_EepromType;
  mPlatformNvsAreaProtocol.Area->MipiCamLink3DD_VcmType = mSystemConfiguration.MipiCam_Link3_DriverData_VcmType;
  mPlatformNvsAreaProtocol.Area->MipiCamLink3DD_Mclk = mSystemConfiguration.MipiCam_Link3_DriverData_Mclk;
  mPlatformNvsAreaProtocol.Area->MipiCamLink3DD_ControlLogic = mSystemConfiguration.MipiCam_Link3_DriverData_ControlLogic;
  mPlatformNvsAreaProtocol.Area->MipiCamLink3DD_FlashSupport = mSystemConfiguration.MipiCam_Link3_DriverData_FlashSupport;
  mPlatformNvsAreaProtocol.Area->MipiCamLink3DD_PrivacyLed = mSystemConfiguration.MipiCam_Link3_DriverData_PrivacyLed;
  mPlatformNvsAreaProtocol.Area->MipiCamLink3DD_Degree = mSystemConfiguration.MipiCam_Link3_DriverData_Degree;
  mPlatformNvsAreaProtocol.Area->MipiCamLink3DD_PmicPosition = mSystemConfiguration.MipiCam_Link3_DriverData_PmicPosition;
  mPlatformNvsAreaProtocol.Area->MipiCamLink3DD_VoltageRail = mSystemConfiguration.MipiCam_Link3_DriverData_VoltageRail;
  mPlatformNvsAreaProtocol.Area->MipiCamLink3DD_PprValue    = mSystemConfiguration.MipiCam_Link3_DriverData_PprValue;
  mPlatformNvsAreaProtocol.Area->MipiCamLink3DD_PprUnit     = mSystemConfiguration.MipiCam_Link3_DriverData_PprUnit;

  // MipiCam Link4 specific
  mPlatformNvsAreaProtocol.Area->MipiCamLink4SensorModel = mSystemConfiguration.MipiCam_Link4_SensorModel;
  mPlatformNvsAreaProtocol.Area->MipiCamLink4Pld = mSystemConfiguration.MipiCam_Link4_CameraPhysicalLocation;
  ZeroMem(ModuleName, sizeof(UINT16) * MIPICAM_MODULE_NAME_LENGTH);
  // Need to copy to temporary alligned buffer due to pack(1) in SetupVariables.h
  CopyMem(ModuleName,mSystemConfiguration.MipiCam_Link4_ModuleName, sizeof(UINT16) * MIPICAM_MODULE_NAME_LENGTH);
  UnicodeStrToAsciiStrS (ModuleName, (CHAR8 *) mPlatformNvsAreaProtocol.Area->MipiCamLink4ModuleName, sizeof(mPlatformNvsAreaProtocol.Area->MipiCamLink4ModuleName));
  ZeroMem(ModuleName, sizeof(UINT16) * MIPICAM_MODULE_NAME_LENGTH);
  CopyMem(ModuleName,mSystemConfiguration.MipiCam_Link4_UserHid, sizeof(UINT16) * MIPICAM_HID_LENGTH);
  UnicodeStrToAsciiStrS (ModuleName, (CHAR8 *) mPlatformNvsAreaProtocol.Area->MipiCamLink4UserHid, sizeof(mPlatformNvsAreaProtocol.Area->MipiCamLink4UserHid));
  mPlatformNvsAreaProtocol.Area->MipiCamLink4I2cDevicesEnabled = mSystemConfiguration.MipiCam_Link4_I2cDevicesEnabled;
  mPlatformNvsAreaProtocol.Area->MipiCamLink4I2cBus = mSystemConfiguration.MipiCam_Link4_I2cChannel;

  // MipiCam Link4 I2C Devices
  for (Index = 0; Index < MIPICAM_I2C_DEVICES_COUNT; Index++) {
    mPlatformNvsAreaProtocol.Area->MipiCamLink4I2cAddrDev[Index] = mSystemConfiguration.MipiCam_Link4_I2cAddress[Index];
    mPlatformNvsAreaProtocol.Area->MipiCamLink4I2cDeviceType[Index] = mSystemConfiguration.MipiCam_Link4_I2cDeviceType[Index];
  }
  mPlatformNvsAreaProtocol.Area->MipiCamLink4DD_Version = 1;
  mPlatformNvsAreaProtocol.Area->MipiCamLink4DD_CrdVersion = mSystemConfiguration.MipiCam_Link4_DriverData_CrdVersion;
  mPlatformNvsAreaProtocol.Area->MipiCamLink4DD_LinkUsed = 7;
  mPlatformNvsAreaProtocol.Area->MipiCamLink4DD_LaneUsed = mSystemConfiguration.MipiCam_Link4_DriverData_LaneUsed;
  mPlatformNvsAreaProtocol.Area->MipiCamLink4DD_EepromType = mSystemConfiguration.MipiCam_Link4_DriverData_EepromType;
  mPlatformNvsAreaProtocol.Area->MipiCamLink4DD_VcmType = mSystemConfiguration.MipiCam_Link4_DriverData_VcmType;
  mPlatformNvsAreaProtocol.Area->MipiCamLink4DD_Mclk = mSystemConfiguration.MipiCam_Link4_DriverData_Mclk;
  mPlatformNvsAreaProtocol.Area->MipiCamLink4DD_ControlLogic = mSystemConfiguration.MipiCam_Link4_DriverData_ControlLogic;
  mPlatformNvsAreaProtocol.Area->MipiCamLink4DD_FlashSupport = mSystemConfiguration.MipiCam_Link4_DriverData_FlashSupport;
  mPlatformNvsAreaProtocol.Area->MipiCamLink4DD_PrivacyLed = mSystemConfiguration.MipiCam_Link4_DriverData_PrivacyLed;
  mPlatformNvsAreaProtocol.Area->MipiCamLink4DD_Degree = mSystemConfiguration.MipiCam_Link4_DriverData_Degree;
  mPlatformNvsAreaProtocol.Area->MipiCamLink4DD_PmicPosition = mSystemConfiguration.MipiCam_Link4_DriverData_PmicPosition;
  mPlatformNvsAreaProtocol.Area->MipiCamLink4DD_VoltageRail = mSystemConfiguration.MipiCam_Link4_DriverData_VoltageRail;
  mPlatformNvsAreaProtocol.Area->MipiCamLink4DD_PprValue    = mSystemConfiguration.MipiCam_Link4_DriverData_PprValue;
  mPlatformNvsAreaProtocol.Area->MipiCamLink4DD_PprUnit     = mSystemConfiguration.MipiCam_Link4_DriverData_PprUnit;

  // MipiCam Link5 specific
  mPlatformNvsAreaProtocol.Area->MipiCamLink5SensorModel = mSystemConfiguration.MipiCam_Link5_SensorModel;
  mPlatformNvsAreaProtocol.Area->MipiCamLink5Pld = mSystemConfiguration.MipiCam_Link5_CameraPhysicalLocation;
  ZeroMem(ModuleName, sizeof(UINT16) * MIPICAM_MODULE_NAME_LENGTH);
  // Need to copy to temporary alligned buffer due to pack(1) in SetupVariables.h
  CopyMem(ModuleName,mSystemConfiguration.MipiCam_Link5_ModuleName, sizeof(UINT16) * MIPICAM_MODULE_NAME_LENGTH);
  UnicodeStrToAsciiStrS (ModuleName, (CHAR8 *) mPlatformNvsAreaProtocol.Area->MipiCamLink5ModuleName, sizeof(mPlatformNvsAreaProtocol.Area->MipiCamLink5ModuleName));
  ZeroMem(ModuleName, sizeof(UINT16) * MIPICAM_MODULE_NAME_LENGTH);
  CopyMem(ModuleName,mSystemConfiguration.MipiCam_Link5_UserHid, sizeof(UINT16) * MIPICAM_HID_LENGTH);
  UnicodeStrToAsciiStrS (ModuleName, (CHAR8 *) mPlatformNvsAreaProtocol.Area->MipiCamLink5UserHid, sizeof(mPlatformNvsAreaProtocol.Area->MipiCamLink5UserHid));
  mPlatformNvsAreaProtocol.Area->MipiCamLink5I2cDevicesEnabled = mSystemConfiguration.MipiCam_Link5_I2cDevicesEnabled;
  mPlatformNvsAreaProtocol.Area->MipiCamLink5I2cBus = mSystemConfiguration.MipiCam_Link5_I2cChannel;

  // MipiCam Link5 I2C Devices
  for (Index = 0; Index < MIPICAM_I2C_DEVICES_COUNT; Index++) {
    mPlatformNvsAreaProtocol.Area->MipiCamLink5I2cAddrDev[Index] = mSystemConfiguration.MipiCam_Link5_I2cAddress[Index];
    mPlatformNvsAreaProtocol.Area->MipiCamLink5I2cDeviceType[Index] = mSystemConfiguration.MipiCam_Link5_I2cDeviceType[Index];
  }
  mPlatformNvsAreaProtocol.Area->MipiCamLink5DD_Version = 1;
  mPlatformNvsAreaProtocol.Area->MipiCamLink5DD_CrdVersion = mSystemConfiguration.MipiCam_Link5_DriverData_CrdVersion;
  mPlatformNvsAreaProtocol.Area->MipiCamLink5DD_LinkUsed = 7;
  mPlatformNvsAreaProtocol.Area->MipiCamLink5DD_LaneUsed = mSystemConfiguration.MipiCam_Link5_DriverData_LaneUsed;
  mPlatformNvsAreaProtocol.Area->MipiCamLink5DD_EepromType = mSystemConfiguration.MipiCam_Link5_DriverData_EepromType;
  mPlatformNvsAreaProtocol.Area->MipiCamLink5DD_VcmType = mSystemConfiguration.MipiCam_Link5_DriverData_VcmType;
  mPlatformNvsAreaProtocol.Area->MipiCamLink5DD_Mclk = mSystemConfiguration.MipiCam_Link5_DriverData_Mclk;
  mPlatformNvsAreaProtocol.Area->MipiCamLink5DD_ControlLogic = mSystemConfiguration.MipiCam_Link5_DriverData_ControlLogic;
  mPlatformNvsAreaProtocol.Area->MipiCamLink5DD_FlashSupport = mSystemConfiguration.MipiCam_Link5_DriverData_FlashSupport;
  mPlatformNvsAreaProtocol.Area->MipiCamLink5DD_PrivacyLed = mSystemConfiguration.MipiCam_Link5_DriverData_PrivacyLed;
  mPlatformNvsAreaProtocol.Area->MipiCamLink5DD_Degree = mSystemConfiguration.MipiCam_Link5_DriverData_Degree;
  mPlatformNvsAreaProtocol.Area->MipiCamLink5DD_PmicPosition = mSystemConfiguration.MipiCam_Link5_DriverData_PmicPosition;
  mPlatformNvsAreaProtocol.Area->MipiCamLink5DD_VoltageRail = mSystemConfiguration.MipiCam_Link5_DriverData_VoltageRail;
  mPlatformNvsAreaProtocol.Area->MipiCamLink5DD_PprValue    = mSystemConfiguration.MipiCam_Link5_DriverData_PprValue;
  mPlatformNvsAreaProtocol.Area->MipiCamLink5DD_PprUnit     = mSystemConfiguration.MipiCam_Link5_DriverData_PprUnit;

  //
  // HDAudio Configuration
  //
  mPlatformNvsAreaProtocol.Area->I2SC = mPchSetup.PchHdAudioI2sCodecSelect;
  mPlatformNvsAreaProtocol.Area->I2SI = PcdGet32 (PcdHdaI2sCodecIrqGpio);
  mPlatformNvsAreaProtocol.Area->I2SB = PcdGet8 (PcdHdaI2sCodecI2cBusNumber);

  DEBUG((DEBUG_INFO,"HDA: I2S Codec Select [I2SC] = 0x%02x\n", mPlatformNvsAreaProtocol.Area->I2SC));
  DEBUG((DEBUG_INFO,"HDA: I2S Codec JD Int pin [I2SI] = 0x%08x\n", mPlatformNvsAreaProtocol.Area->I2SI));
  DEBUG((DEBUG_INFO,"HDA: I2S Codec I2C Bus Number [I2SB] = 0x%02x\n", mPlatformNvsAreaProtocol.Area->I2SB));

  for (Index = 0; Index < HDAUDIO_PP_MODULES; Index++) {
    mPlatformNvsAreaProtocol.Area->HdaDspPpModuleMask |= (UINT32)(mPchSetup.PchHdAudioPostProcessingMod[Index] ? (1 << Index) : 0);
  }
  DEBUG((DEBUG_INFO,"HDA: HdaDspPpModuleMask [ADPM] = 0x%08x\n", mPlatformNvsAreaProtocol.Area->HdaDspPpModuleMask));

  if (mPchSetup.PchHdAudioPostProcessingMod[29]){
    DEBUG((DEBUG_INFO,"HDA: AudioDSP Pre/Post-Processing custom module 'Alpha' enabled (BIT29)\n"));

    CopyMem(LocalGuidString, mPchSetup.PchHdAudioPostProcessingModCustomGuid1, GUID_CHARS_NUMBER * sizeof(CHAR16));
    GuidStringToAcpiBuffer (LocalGuidString, &AcpiGuidPart1, &AcpiGuidPart2);
    mPlatformNvsAreaProtocol.Area->HdaDspPpModCustomGuid1Low  = AcpiGuidPart1;
    mPlatformNvsAreaProtocol.Area->HdaDspPpModCustomGuid1High = AcpiGuidPart2;
    DEBUG((DEBUG_INFO,"HdaDspPpModCustomGuid1Low  = 0x%016Lx\nHdaDspPpModCustomGuid2High = 0x%016Lx\n",
            mPlatformNvsAreaProtocol.Area->HdaDspPpModCustomGuid1Low, mPlatformNvsAreaProtocol.Area->HdaDspPpModCustomGuid1High));
  }

  if (mPchSetup.PchHdAudioPostProcessingMod[30]){
    DEBUG((DEBUG_INFO,"HDA: AudioDSP Pre/Post-Processing custom module 'Beta' enabled (BIT30)\n"));

    CopyMem(LocalGuidString, mPchSetup.PchHdAudioPostProcessingModCustomGuid2, GUID_CHARS_NUMBER * sizeof(CHAR16));
    GuidStringToAcpiBuffer (LocalGuidString, &AcpiGuidPart1, &AcpiGuidPart2);
    mPlatformNvsAreaProtocol.Area->HdaDspPpModCustomGuid2Low  = AcpiGuidPart1;
    mPlatformNvsAreaProtocol.Area->HdaDspPpModCustomGuid2High = AcpiGuidPart2;
    DEBUG((DEBUG_INFO,"HdaDspPpModCustomGuid2Low  = 0x%016Lx\nHdaDspPpModCustomGuid2High = 0x%016Lx\n",
            mPlatformNvsAreaProtocol.Area->HdaDspPpModCustomGuid2Low, mPlatformNvsAreaProtocol.Area->HdaDspPpModCustomGuid2High));
  }

  if (mPchSetup.PchHdAudioPostProcessingMod[31]){
    DEBUG((DEBUG_INFO,"HDA: AudioDSP Pre/Post-Processing custom module 'Gamma' enabled (BIT31)\n"));

    CopyMem(LocalGuidString, mPchSetup.PchHdAudioPostProcessingModCustomGuid3, GUID_CHARS_NUMBER * sizeof(CHAR16));
    GuidStringToAcpiBuffer (LocalGuidString, &AcpiGuidPart1, &AcpiGuidPart2);
    mPlatformNvsAreaProtocol.Area->HdaDspPpModCustomGuid3Low  = AcpiGuidPart1;
    mPlatformNvsAreaProtocol.Area->HdaDspPpModCustomGuid3High = AcpiGuidPart2;
    DEBUG((DEBUG_INFO,"HdaDspPpModCustomGuid3Low  = 0x%016Lx\nHdaDspPpModCustomGuid3High = 0x%016Lx\n",
            mPlatformNvsAreaProtocol.Area->HdaDspPpModCustomGuid3Low, mPlatformNvsAreaProtocol.Area->HdaDspPpModCustomGuid3High));
  }

  ///
  /// Get TcssHob HOB
  ///
#if FixedPcdGetBool(PcdITbtEnable) == 1
  mTcssHob = (TCSS_DATA_HOB *) GetFirstGuidHob (&gTcssHobGuid);
#endif
  mPlatformNvsAreaProtocol.Area->PciDelayOptimizationEcr = mSystemConfiguration.PciDelayOptimizationEcr;

  if ((mSystemConfiguration.SdevXhciEntry == TRUE) && (mSystemConfiguration.SdevXhciNumberOfDevices > 0)) {
    mPlatformNvsAreaProtocol.Area->SdevXhciInterfaceNumber1 = mSystemConfiguration.SdevXhciInterfaceNumber[0];
    mPlatformNvsAreaProtocol.Area->SdevXhciRootPortNumber1  = mSystemConfiguration.SdevXhciRootPortNumber[0];
    if (mSystemConfiguration.SdevXhciNumberOfDevices > 1) {
      mPlatformNvsAreaProtocol.Area->SdevXhciInterfaceNumber2 = mSystemConfiguration.SdevXhciInterfaceNumber[1];
      mPlatformNvsAreaProtocol.Area->SdevXhciRootPortNumber2  = mSystemConfiguration.SdevXhciRootPortNumber[1];
    }
  }


  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gPlatformNvsAreaProtocolGuid,
                  &mPlatformNvsAreaProtocol,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Allocate NVS area for VBIOS. This is not currently used.
  //
  Status = AllocateMemoryBelow4G (
             EfiACPIMemoryNVS,
             0x10000,
             &mGfxNvsAddress
             );
  ASSERT_EFI_ERROR (Status);

  //
  // Generate ACPI tables from configuration data
  //
  Status = GenerateSsdtFromConfigFile();
  ASSERT_EFI_ERROR (Status);

  //
  // Platform ACPI Tables
  //
  PublishAcpiTablesFromFv(gEfiAcpiTableStorageGuid);

  //
  // Reference Code ACPI Tables
  //
  PublishAcpiTablesFromFv(gRcAcpiTableStorageGuid);

  //
  // Install xHCI ACPI Table
  //
  InstallXhciAcpiTable ();

  //
  // Install NHLT ACPI Table
  //
  InstallNhltAcpiTable ();

  //
  // Save Acpi Setup Variables
  //
  Status = SetAcpiSetupVariables ();
  ASSERT_EFI_ERROR (Status);

  //
  // Finished
  //
  return EFI_SUCCESS;
}

/**
  Sort ordering of CPUs according to the priorities of cores and threads.
  ** ASSUMPTION: 1) single CPU package systsem wide; 2) two threads per core

  @param[in] MpService             The MP servicde protocol (used to retrievel MP info)
  @param[in] NumberOfCPUs          Number of CPUs
  @param[in] NumberOfEnabledCPUs   Number of Enabled CPUs.

  @retval EFI_SUCCESS              The driver installed without error.

**/
EFI_STATUS
SortCpuLocalApicInTable (
  IN  EFI_MP_SERVICES_PROTOCOL          *MpService,
  IN  UINTN                             NumberOfCPUs,
  IN  UINTN                             NumberOfEnabledCPUs
  )
{
  EFI_PROCESSOR_INFORMATION                 *MpContext;
  UINT8                                     Index1;
  UINT8                                     Index;
  UINT8                                     CpuThreadIndex;
  UINTN                                     BspIndex;
  UINT8                                     CurrProcessor;
  EFI_STATUS                                Status;
  UINT8                                     MaxCpuCore;
  UINT8                                     MaxCpuThread;

  MpContext                     = NULL;
  MaxCpuCore                    = 0;
  MaxCpuThread                  = 0;

  Status = MpService->WhoAmI (
                        MpService,
                        &BspIndex
                        );

  //
  // Fill mCpuApicIdOrderTable
  //
  for (CurrProcessor = 0; CurrProcessor < NumberOfCPUs; CurrProcessor++) {

    MpContext = AllocatePool (sizeof(EFI_PROCESSOR_INFORMATION));
    ASSERT (MpContext != NULL);
    Status = MpService->GetProcessorInfo (
                          MpService,
                          CurrProcessor,
                          MpContext
                          );
    ASSERT_EFI_ERROR (Status);

    if (MpContext == NULL) {
      return Status;
    }
    mCpuApicIdOrderTable[CurrProcessor].ApicId  = (UINT8) MpContext->ProcessorId;
    DEBUG((DEBUG_INFO, "The CurrProcessor 0x%x ApicId is 0x%x\n", CurrProcessor, mCpuApicIdOrderTable[CurrProcessor].ApicId));
    mCpuApicIdOrderTable[CurrProcessor].Flags   = (MpContext->StatusFlag | PROCESSOR_ENABLED_BIT)? 1: 0;
    mCpuApicIdOrderTable[CurrProcessor].Package = (UINT8) MpContext->Location.Package;
    mCpuApicIdOrderTable[CurrProcessor].Die     = (UINT8) 0;
    mCpuApicIdOrderTable[CurrProcessor].Core    = (UINT8) MpContext->Location.Core;
    mCpuApicIdOrderTable[CurrProcessor].Thread  = (UINT8) MpContext->Location.Thread;

    if (MaxCpuThread < (UINT8) MpContext->Location.Thread) {
      MaxCpuThread = (UINT8) MpContext->Location.Thread;
    }

    if (MaxCpuCore < (UINT8) MpContext->Location.Core) {
      MaxCpuCore = (UINT8) MpContext->Location.Core;
    }
  }

  //
  // Do some statistics about the SBSP package
  //
  for (CurrProcessor = 0; CurrProcessor < NumberOfCPUs; CurrProcessor++) {
    if (CurrProcessor == BspIndex) {
      mSbspPackageInfo.BspApicId = mCpuApicIdOrderTable[CurrProcessor].ApicId;
      mSbspPackageInfo.PackageNo   = mCpuApicIdOrderTable[CurrProcessor].Package;
      mSbspPackageInfo.TotalThreads = 0;
      mSbspPackageInfo.CoreNo = 0;
      mSbspPackageInfo.LogicalThreadNo = 0;
    }
  }

  for (CurrProcessor = 0; CurrProcessor < NumberOfCPUs; CurrProcessor++) {
    if (mCpuApicIdOrderTable[CurrProcessor].Package == mSbspPackageInfo.PackageNo) {
      mSbspPackageInfo.TotalThreads++;
      if (mCpuApicIdOrderTable[CurrProcessor].Thread == 0) {
        mSbspPackageInfo.CoreNo++;
      } else {
        mSbspPackageInfo.LogicalThreadNo++;
      }
    }
  }

  //
  // Output debug info
  //
  for (Index = 0; Index < NumberOfCPUs; Index++) {
    DEBUG((DEBUG_INFO, "Package = %x,  Die = %x,  Core = %x,  Thread = %x,  ApicId = %x\n", \
      mCpuApicIdOrderTable[Index].Package, \
      mCpuApicIdOrderTable[Index].Die, \
      mCpuApicIdOrderTable[Index].Core, \
      mCpuApicIdOrderTable[Index].Thread, \
      mCpuApicIdOrderTable[Index].ApicId));
  }

  DEBUG((DEBUG_INFO, "MaxCpuCore    = %x\n", MaxCpuCore));
  DEBUG((DEBUG_INFO, "MaxCpuThread    = %x\n\n", MaxCpuThread));
  DEBUG((DEBUG_INFO, "mSbspPackageInfo.BspApicId        = %x\n", mSbspPackageInfo.BspApicId));
  DEBUG((DEBUG_INFO, "mSbspPackageInfo.TotalThreads     = %x\n", mSbspPackageInfo.TotalThreads));
  DEBUG((DEBUG_INFO, "mSbspPackageInfo.PackageNo        = %x\n", mSbspPackageInfo.PackageNo));
  DEBUG((DEBUG_INFO, "mSbspPackageInfo.CoreNo           = %x\n", mSbspPackageInfo.CoreNo));
  DEBUG((DEBUG_INFO, "mSbspPackageInfo.LogicalThreadNo  = %x\n", mSbspPackageInfo.LogicalThreadNo));

  //
  // First entry is always SBSP
  //
  CurrProcessor = 0;
  mCpuApicIdReorderTable[CurrProcessor].ApicId = mSbspPackageInfo.BspApicId;
  mCpuApicIdReorderTable[CurrProcessor].Package = mSbspPackageInfo.PackageNo;
  mCpuApicIdReorderTable[CurrProcessor].Flags = 1;
  CurrProcessor++;

  //
  // Reorder Core and threads
  //
  for (Index1 = 0; Index1 <= MaxCpuThread; Index1 ++) {
    for (Index = 0; Index <= MaxCpuCore; Index++) {
      for (CpuThreadIndex = 0; CpuThreadIndex < NumberOfCPUs; CpuThreadIndex++) {
        if ((mCpuApicIdOrderTable[CpuThreadIndex].Package == mSbspPackageInfo.PackageNo) &&
            (mCpuApicIdOrderTable[CpuThreadIndex].Thread == Index1) &&
            (mCpuApicIdOrderTable[CpuThreadIndex].Core == Index) &&
            (mCpuApicIdOrderTable[CpuThreadIndex].ApicId != mCpuApicIdReorderTable[0].ApicId)) {
          mCpuApicIdReorderTable[CurrProcessor].ApicId = mCpuApicIdOrderTable[CpuThreadIndex].ApicId;
          mCpuApicIdReorderTable[CurrProcessor].Package = mSbspPackageInfo.PackageNo;
          mCpuApicIdReorderTable[CurrProcessor].Flags = mCpuApicIdOrderTable[CpuThreadIndex].Flags;
          CurrProcessor++;
          break;
        }
      }
    }
  }

  //
  // Output debug info
  //
  for (Index = 0; Index < NumberOfCPUs; Index++) {
    DEBUG((DEBUG_INFO, "Index = %x,  ApicId = %x,  Package = %x\n", \
      Index, \
      mCpuApicIdReorderTable[Index].ApicId, \
      mCpuApicIdReorderTable[Index].Package));
  }

  FreePool (MpContext);

  return  EFI_SUCCESS;
}


EFI_STATUS
AppendCpuMapTableEntry (
  IN  EFI_ACPI_1_0_PROCESSOR_LOCAL_APIC_STRUCTURE   *AcpiLocalApic,
  IN  UINTN                                         NumberOfCPUs,
  IN  UINTN                                         NumberOfEnabledCPUs,
  IN  UINT8                                         LocalApicCounter
  )
{
  if (LocalApicCounter < NumberOfCPUs) {
    AcpiLocalApic->Flags           = mCpuApicIdReorderTable[LocalApicCounter].Flags;
    AcpiLocalApic->ApicId          = mCpuApicIdReorderTable[LocalApicCounter].ApicId;
    //
    // Make AcpiProcessorIds 1-based, matching the ones in Processor() definitions
    //
    AcpiLocalApic->AcpiProcessorId = LocalApicCounter + 1;
  } else {
    AcpiLocalApic->Flags           = 0;
    AcpiLocalApic->ApicId          = 0xFF;
    //
    // Make AcpiProcessorIds 1-based, matching the ones in Processor() definitions
    //
    AcpiLocalApic->AcpiProcessorId = LocalApicCounter + 1;
  }

  //
  // Display the results
  //
  DEBUG((DEBUG_INFO, "AcpiLocalApic: AcpiProcessorId=%x, ApicId=%x, Flags=%x\n", \
  AcpiLocalApic->AcpiProcessorId, \
  AcpiLocalApic->ApicId, \
  AcpiLocalApic->Flags));

  return EFI_SUCCESS;
}

/**
  I/O work flow to wait input buffer empty in given time.

  @param[in] Timeout       Wating time.

  @retval EFI_TIMEOUT      if input is still not empty in given time.
  @retval EFI_SUCCESS      input is empty.
**/
EFI_STATUS
WaitInputEmpty (
  IN UINTN Timeout
  )
{
  UINTN Delay;
  UINT8 Data;

  Delay = Timeout / 50;

  do {
    Data = IoRead8 (KBC_CMD_STS_PORT);

    //
    // Check keyboard controller status bit 0 and 1 (Output Buffer and Input Buffer status)
    //
    if ((Data & KBC_OUTB) != 0) {
      IoRead8 (KBC_DATA_PORT);
    } else if ((Data & KBC_INPB) == 0) {
      break;
    }

    gBS->Stall (50);
    Delay--;
  } while (Delay != 0);

  if (Delay == 0) {
    return EFI_TIMEOUT;
  }

  return EFI_SUCCESS;
}

/**
  I/O work flow to wait output buffer full in given time.

  @param[in] Timeout       given time

  @retval EFI_TIMEOUT      output is not full in given time
  @retval EFI_SUCCESS      output is full in given time.
**/
EFI_STATUS
WaitOutputFull (
  IN UINTN Timeout
  )
{
  UINTN Delay;
  UINT8 Data;

  Delay = Timeout / 50;

  do {
    Data = IoRead8 (KBC_CMD_STS_PORT);

    //
    // Check keyboard controller status bit 0(output buffer status)
    //  & bit5(output buffer for auxiliary device)
    //
    if ((Data & (KBC_OUTB | KBC_AUXB)) == (KBC_OUTB | KBC_AUXB)) {
      break;
    }

    gBS->Stall (50);
    Delay--;
  } while (Delay != 0);

  if (Delay == 0) {
    return EFI_TIMEOUT;
  }

  return EFI_SUCCESS;
}

/**
  I/O work flow of in 8042 Aux data.

  @param Data    Buffer holding return value.

  @retval EFI_SUCCESS Success to excute I/O work flow
  @retval EFI_TIMEOUT Keyboard controller time out.
**/
EFI_STATUS
In8042AuxData (
  IN OUT UINT8 *Data
  )
{
  EFI_STATUS Status;

  //
  // wait for output data
  //
  Status = WaitOutputFull (BAT_TIMEOUT);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  *Data = IoRead8 (KBC_DATA_PORT);

  return EFI_SUCCESS;
}

/**
  I/O work flow of outing 8042 Aux command.

  @param Command Aux I/O command

  @retval EFI_SUCCESS Success to excute I/O work flow
  @retval EFI_TIMEOUT Keyboard controller time out.
**/
EFI_STATUS
Out8042AuxCommand (
  IN UINT8 Command
  )
{
  EFI_STATUS  Status;
  UINT8       Data;

  //
  // Wait keyboard controller input buffer empty
  //
  Status = WaitInputEmpty (TIMEOUT);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  //
  // Send write to auxiliary device command
  //
  Data = WRITE_AUX_DEV;
  IoWrite8 (KBC_CMD_STS_PORT, Data);

  Status = WaitInputEmpty (TIMEOUT);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  //
  // Send auxiliary device command
  //
  IoWrite8 (KBC_DATA_PORT, Command);

  //
  // Read return code
  //
  Status = In8042AuxData (&Data);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (Data == PS2_ACK) {
    //
    // Receive mouse acknowledge, command send success
    //
    return EFI_SUCCESS;

  } else if (Data == PS2_RESEND) {
    //
    // Resend command
    //
    Status = Out8042AuxCommand (Command);
    if (EFI_ERROR (Status)) {
      return Status;
    }

  } else {
    //
    // Invalid return code
    //
    return EFI_DEVICE_ERROR;

  }

  return EFI_SUCCESS;
}

/**
  Issue command to enable Ps2 mouse.

  @return Status of command issuing.
**/
EFI_STATUS
PS2MouseEnable (
  VOID
  )
{
  //
  // Send auxiliary command to enable mouse
  //
  return Out8042AuxCommand (ENABLE_CMD);
}

/**
  Check whether there is Ps/2 mouse device in system

  @retval TRUE      - Keyboard in System.
  @retval FALSE     - Keyboard not in System.

**/
BOOLEAN
IsPs2MouseConnected (
  VOID
  )
{
  EFI_STATUS Status;

  Status = PS2MouseEnable ();

  if (!EFI_ERROR (Status)) {
    return TRUE;
  }

  return FALSE;
}
