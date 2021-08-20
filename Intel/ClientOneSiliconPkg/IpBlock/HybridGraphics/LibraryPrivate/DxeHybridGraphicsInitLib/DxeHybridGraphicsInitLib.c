/** @file
  HybridGraphics Dxe driver.
  This DXE driver loads HybridGraphics acpi tables
  for the platform.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2019   Intel Corporation.

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
#include <Library/DxeHybridGraphicsInitLib.h>

extern EFI_GUID gHgAcpiTableStorageGuid;
extern EFI_GUID gHgAcpiTablePchStorageGuid;

///
/// Global Variables
///
GLOBAL_REMOVE_IF_UNREFERENCED VOID                  *VbiosAddress = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN               DgpuOpRomCopied;
GLOBAL_REMOVE_IF_UNREFERENCED UINT32                VbiosSize;
GLOBAL_REMOVE_IF_UNREFERENCED UINT8                 EndpointBus;
GLOBAL_REMOVE_IF_UNREFERENCED UINT8                 RootPortDev;
GLOBAL_REMOVE_IF_UNREFERENCED UINT8                 RootPortFun;
GLOBAL_REMOVE_IF_UNREFERENCED SA_POLICY_PROTOCOL    *mSaPolicy;
GLOBAL_REMOVE_IF_UNREFERENCED HG_INFO_HOB           *mHgInfoHob;


/**
  Initialize the HybridGraphics support (DXE).

  @retval EFI_SUCCESS          - HybridGraphics initialization complete
  @retval EFI_OUT_OF_RESOURCES - Unable to allocated memory
  @retval EFI_NOT_FOUND        - HG InfoHob not found
  @retval EFI_DEVICE_ERROR     - Error Accessing HG GPIO
**/
EFI_STATUS
DxeHybridGraphicsInit (
  VOID
  )
{
  EFI_STATUS  Status;
  EFI_EVENT   EndOfDxeEvent;
  UINTN       RpDev;
  UINTN       RpFun;
  CPU_FAMILY  CpuFamilyId;

  CpuFamilyId = GetCpuFamily();

  mHgInfoHob = NULL;
  mHgInfoHob = (HG_INFO_HOB *)GetFirstGuidHob(&gHybridGraphicsInfoHobGuid);
  if (mHgInfoHob == NULL) {
    return EFI_NOT_FOUND;
  }

  if (IsPchLinkDmi (CpuFamilyId)) {
    RootPortDev = SA_PEG0_DEV_NUM;
    RootPortFun = SA_PEG0_FUN_NUM;
  } else {
    Status = GetPchPcieRpDevFun((UINTN)mHgInfoHob->HgInfo.RootPortIndex, &RpDev, &RpFun);
    ASSERT_EFI_ERROR(Status);
    RootPortDev = (UINT8)RpDev;
    RootPortFun = (UINT8)RpFun;
  }

  DEBUG ((DEBUG_INFO, "dGPU Rootport info[B/D/F] : [0x00/0x%x/0x%x]\n", RootPortDev, RootPortFun));


  ///
  /// Register an end of DXE event for SG to do tasks before invoking any UEFI drivers,
  /// applications, or connecting consoles,...
  ///
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  HgEndOfDxeCallback,
                  NULL,
                  &gEfiEndOfDxeEventGroupGuid,
                  &EndOfDxeEvent
                  );

  return Status;
}

/**
  Initialize the runtime HybridGraphics support data for ACPI tables in GlobalNvs.

  @retval EFI_SUCCESS    - The data updated successfully.
**/
EFI_STATUS
UpdateGlobalNvsData (
  VOID
  )
{
  SYSTEM_AGENT_NVS_AREA_PROTOCOL  *SaNvsAreaProtocol;
  EFI_STATUS                      Status;

  ///
  ///  Locate the SA Global NVS Protocol.
  ///
  Status = gBS->LocateProtocol (
                  &gSaNvsAreaProtocolGuid,
                  NULL,
                  (VOID **) &SaNvsAreaProtocol
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  ///
  /// HG Mode for ASL usage
  ///
  SaNvsAreaProtocol->Area->HgMode                  |= mHgInfoHob->HgInfo.HgMode;
  SaNvsAreaProtocol->Area->Pcie0GpioSupport         = mHgInfoHob->HgInfo.Rtd3Pcie0Gpio.GpioSupport;
  SaNvsAreaProtocol->Area->DelayAfterPwrEn          = mHgInfoHob->HgInfo.DelayAfterPwrEn;
  SaNvsAreaProtocol->Area->DelayAfterHoldReset      = mHgInfoHob->HgInfo.DelayAfterHoldReset;
  SaNvsAreaProtocol->Area->RootPortIndex            = mHgInfoHob->HgInfo.RootPortIndex;
  SaNvsAreaProtocol->Area->RootPortAddress          = (UINT32)MmPciBase(SA_MC_BUS, RootPortDev, RootPortFun);


  DEBUG ((DEBUG_INFO, "HG:: Hybrid Graphics Mode : 0x%x\n", mHgInfoHob->HgInfo.HgMode));

  if (mHgInfoHob->HgInfo.Rtd3Pcie0Gpio.GpioSupport != 0) {
    ///
    /// GPIO Assignment for ASL usage
    ///
    SaNvsAreaProtocol->Area->Pcie0HoldRstExpanderNo  = mHgInfoHob->HgInfo.Rtd3Pcie0Gpio.HoldRst.ExpanderNo;
    SaNvsAreaProtocol->Area->Pcie0HoldRstGpioNo      = mHgInfoHob->HgInfo.Rtd3Pcie0Gpio.HoldRst.GpioNo;
    SaNvsAreaProtocol->Area->Pcie0HoldRstActiveInfo  = mHgInfoHob->HgInfo.Rtd3Pcie0Gpio.HoldRst.Active;
    SaNvsAreaProtocol->Area->Pcie0PwrEnExpanderNo    = mHgInfoHob->HgInfo.Rtd3Pcie0Gpio.PwrEnable.ExpanderNo;
    SaNvsAreaProtocol->Area->Pcie0PwrEnGpioNo        = mHgInfoHob->HgInfo.Rtd3Pcie0Gpio.PwrEnable.GpioNo;
    SaNvsAreaProtocol->Area->Pcie0PwrEnActiveInfo    = mHgInfoHob->HgInfo.Rtd3Pcie0Gpio.PwrEnable.Active;

    ///
    /// Find capability ID for Endpoint on PCIe Port 0
    ///
    Status = FindPcieEpCapId (RootPortDev, RootPortFun);
  }


  return Status;
}

/**
  Load and execute the dGPU VBIOS.

  @param[in] SaPolicy    - SA DXE Policy protocol
      LoadVbios    - 0 = Do Not Load   ; 1 = Load VBIOS
      ExecuteVbios - 0 = Do Not Execute; 1 = Execute VBIOS
      VbiosSource  - 0 = PCIE Device   ; 1 = FirmwareVolume => TBD

  @retval EFI_SUCCESS     - Load and execute successful.
  @exception EFI_UNSUPPORTED - Secondary VBIOS not loaded.
**/
EFI_STATUS
LoadAndExecuteDgpuVbios (
  IN   SA_POLICY_PROTOCOL       *SaPolicy
  )
{
  EFI_HANDLE                *HandleBuffer;
  UINT64                    RootBaseAddress;
  EFI_STATUS                Status;
  VBIOS_DXE_CONFIG          *VbiosDxeConfig;


  Status = GetConfigBlock ((VOID *) SaPolicy, &gVbiosDxeConfigGuid, (VOID *)&VbiosDxeConfig);
  ASSERT_EFI_ERROR (Status);

  HandleBuffer = NULL;
  DgpuOpRomCopied = FALSE;

  DEBUG ((DEBUG_INFO, "HG:: LoadAndExecuteDgpuVbios\n"));

  ///
  /// Endpoint Device Bus#
  ///

  RootBaseAddress  = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, RootPortDev, RootPortFun, 0);
  EndpointBus      = PciSegmentRead8 (RootBaseAddress + PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET);

  ///
  ///  Endpoint Device Not found
  ///
  if (EndpointBus == 0xFF) {
    DEBUG ((DEBUG_WARN, "SG:: 0x00/0x%x/0x%x Rootport's Endpoint Device Not found\n", RootPortDev, RootPortFun));
    return EFI_UNSUPPORTED;
  }



  if (VbiosAddress!=NULL) {
    FreePool (VbiosAddress);
  }

  if (HandleBuffer!=NULL) {
    FreePool (HandleBuffer);
  }

  return EFI_SUCCESS;
}

/**
  Do an AllocatePages () of type AllocateMaxAddress for EfiBootServicesCode
  memory.

  @param[in] AllocateType     - Allocated Legacy Memory Type
  @param[in] StartPageAddress - Start address of range
  @param[in] Pages            - Number of pages to allocate
  @param[in, out] Result      - Result of allocation

  @retval EFI_SUCCESS - Legacy16 code loaded
  @retval Other       - No protocol installed, unload driver.
**/
EFI_STATUS
AllocateLegacyMemory (
  IN  EFI_ALLOCATE_TYPE         AllocateType,
  IN  EFI_PHYSICAL_ADDRESS      StartPageAddress,
  IN  UINTN                     Pages,
  IN OUT  EFI_PHYSICAL_ADDRESS  *Result
  )
{
  EFI_STATUS            Status;
  EFI_PHYSICAL_ADDRESS  MemPage;

  ///
  /// Allocate Pages of memory less <= StartPageAddress
  ///
  MemPage = (EFI_PHYSICAL_ADDRESS) (UINTN) StartPageAddress;
  Status  = gBS->AllocatePages (AllocateType, EfiBootServicesCode, Pages, &MemPage);
  ///
  /// Do not ASSERT on Status error but let caller decide since some cases
  /// memory is already taken but that is ok.
  ///
  if (!EFI_ERROR (Status)) {
    *Result = (EFI_PHYSICAL_ADDRESS) (UINTN) MemPage;
  }

  return Status;
}

/**
  Load Intel HG SSDT Tables

  @retval EFI_SUCCESS - HG SSDT Table load successful.
**/
EFI_STATUS
LoadAcpiTables (
  VOID
  )
{
  EFI_STATUS                    Status;
  EFI_HANDLE                    *HandleBuffer;
  BOOLEAN                       LoadTable;
  UINTN                         NumberOfHandles;
  UINTN                         Index;
  INTN                          Instance;
  UINTN                         Size;
  UINT32                        FvStatus;
  UINTN                         TableHandle;
  EFI_GUID                      AcpiTableGuid;
  EFI_FV_FILETYPE               FileType;
  EFI_FV_FILE_ATTRIBUTES        Attributes;
  EFI_FIRMWARE_VOLUME2_PROTOCOL *FwVol;
  EFI_ACPI_TABLE_PROTOCOL       *AcpiTable;
  EFI_ACPI_DESCRIPTION_HEADER   *TableHeader;
  EFI_ACPI_COMMON_HEADER        *Table;

  FwVol         = NULL;
  Table         = NULL;

  AcpiTableGuid = gHgAcpiTableStorageGuid;
  if (IsPchLp ()) {
    AcpiTableGuid = gHgAcpiTablePchStorageGuid;
  }

  DEBUG ((DEBUG_INFO, "HG:: Loading ACPI Tables...\n"));

  ///
  /// Locate FV protocol.
  ///
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiFirmwareVolume2ProtocolGuid,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Look for FV with ACPI storage file
  ///
  for (Index = 0; Index < NumberOfHandles; Index++) {
    ///
    /// Get the protocol on this handle
    /// This should not fail because of LocateHandleBuffer
    ///
    Status = gBS->HandleProtocol (
                    HandleBuffer[Index],
                    &gEfiFirmwareVolume2ProtocolGuid,
                    (VOID **) &FwVol
                    );
    ASSERT_EFI_ERROR (Status);
    if (FwVol == NULL) {
      return EFI_NOT_FOUND;
    }
    ///
    /// See if it has the ACPI storage file
    ///
    Size      = 0;
    FvStatus  = 0;
    Status = FwVol->ReadFile (
                      FwVol,
                      &AcpiTableGuid,
                      NULL,
                      &Size,
                      &FileType,
                      &Attributes,
                      &FvStatus
                      );

    ///
    /// If we found it, then we are done
    ///
    if (!EFI_ERROR (Status)) {
      break;
    }
  }
  ///
  /// Our exit status is determined by the success of the previous operations
  /// If the protocol was found, Instance already points to it.
  ///
  ///
  /// Free any allocated buffers
  ///
  FreePool (HandleBuffer);

  ///
  /// Sanity check that we found our data file
  ///
  ASSERT (FwVol);

  ///
  /// Locate ACPI tables
  ///
  Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, (VOID **) &AcpiTable);

  ///
  /// Read tables from the storage file.
  ///
  if (FwVol == NULL) {
    ASSERT_EFI_ERROR (EFI_NOT_FOUND);
    return EFI_NOT_FOUND;
  }
  Instance = 0;

  while (Status == EFI_SUCCESS) {
    ///
    /// Read the ACPI tables
    ///
    Status = FwVol->ReadSection (
                      FwVol,
                      &AcpiTableGuid,
                      EFI_SECTION_RAW,
                      Instance,
                      (VOID **) &Table,
                      &Size,
                      &FvStatus
                      );
    if (!EFI_ERROR (Status)) {
      ///
      /// check and load HybridGraphics SSDT table
      ///
      LoadTable   = FALSE;
      TableHeader = (EFI_ACPI_DESCRIPTION_HEADER *) Table;

      if (CompareGuid (&gHgAcpiTableStorageGuid, &AcpiTableGuid)) {
        if (((EFI_ACPI_DESCRIPTION_HEADER *) TableHeader)->OemTableId == SIGNATURE_64 ('H', 'g', 'P', 'e', 'g', 0, 0, 0)) {
          ///
          /// This is HG SSDT [dGPU is present on PEG RootPort]
          ///
          DEBUG ((DEBUG_INFO, "HG:: ---- HG SSDT ----\n"));
          DEBUG ((DEBUG_INFO, "HG:: Found out SSDT:HgPeg [HgSsdt.asl]. dGPU is present on PEG RootPort.\n"));
          LoadTable = TRUE;
        }
      }
      if (CompareGuid (&gHgAcpiTablePchStorageGuid, &AcpiTableGuid)) {
        if (((EFI_ACPI_DESCRIPTION_HEADER *) TableHeader)->OemTableId == SIGNATURE_64 ('H', 'g', 'R', 'p', 'S', 's', 'd', 't')) {
          ///
          /// This is HG SSDT [dGPU is present on PCH RootPort]
          ///
          DEBUG ((DEBUG_INFO, "HG:: ---- HG SSDT ----\n"));
          DEBUG ((DEBUG_INFO, "HG:: Found out SSDT:HgRpSsdt [HgRpSsdt.asl]. dGPU is present on PCH RootPort.\n"));
          LoadTable = TRUE;
        }


      }

      ///
      /// Add the table
      ///
      if (LoadTable) {
        TableHandle = 0;
        Status = AcpiTable->InstallAcpiTable (
                              AcpiTable,
                              TableHeader,
                              TableHeader->Length,
                              &TableHandle
                              );
      }
      ///
      /// Increment the instance
      ///
      Instance++;
      Table = NULL;
    }
  }

  return EFI_SUCCESS;
}


/**
  This function gets registered as a EndOfDxe callback to perform HG initialization

  @param[in] Event     - A pointer to the Event that triggered the callback.
  @param[in] Context   - A pointer to private data registered with the callback function.
**/
VOID
EFIAPI
HgEndOfDxeCallback (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  EFI_STATUS  Status;


  DEBUG ((DEBUG_INFO, "HG:: EndOfDxe Callback\n"));



  ///
  /// Update GlobalNvs data for runtime usage
  ///
  Status = UpdateGlobalNvsData ();
  if (EFI_ERROR (Status)) {
    ASSERT_EFI_ERROR (Status);
  }

  if ((mHgInfoHob->HgInfo.HgMode == HgModeMuxless) &&
      (mHgInfoHob->HgInfo.Rtd3Pcie0Gpio.GpioSupport != 0)) {
    ///
    /// Load Intel HG SSDT tables
    ///

    Status = LoadAcpiTables ();
    if (EFI_ERROR (Status)) {
        ASSERT_EFI_ERROR (Status);
    }



    ///
    /// Load and Execute dGPU VBIOS
    ///
    Status = LoadAndExecuteDgpuVbios (mSaPolicy);
    if (EFI_ERROR (Status)) {
      ASSERT_EFI_ERROR (Status);
    }
  }
}

/**
  Find the Pcie Capability ID for PCIe Ports.

  @param[in] PciePortDev       - Pcie Port Device Number
  @param[in] PciePortFun       - Pcie Port Function Number

  @retval EFI_SUCCESS - Found  out the Cap Id.
**/
EFI_STATUS
FindPcieEpCapId (
  IN UINT8 PciePortDev,
  IN UINT8 PciePortFun
  )
{
  SYSTEM_AGENT_NVS_AREA_PROTOCOL  *SaNvsAreaProtocol;
  UINT64                          PciePortAddress;
  UINT8                           PciePortBus;
  UINT8                           PcieCapOffset;
  EFI_STATUS                      Status;

  ///
  ///  Locate the SA Global NVS Protocol.
  ///
  Status = gBS->LocateProtocol (
                  &gSaNvsAreaProtocolGuid,
                  NULL,
                  (VOID **) &SaNvsAreaProtocol
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  ///
  /// Get the PCIe Port Base Address to find Secondary bus number & sub-ordinate bus number
  ///
  PciePortAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, 0, PciePortDev, PciePortFun, 0);

  ///
  /// Check if Pcie device is present or not.
  ///
  if (PciSegmentRead16 (PciePortAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    return EFI_UNSUPPORTED;
  }
  ///
  /// Get the Endpoint PCIe Port Bus number by reading secondary bus offset.
  ///
  PciePortBus = PciSegmentRead8 (PciePortAddress + PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET);

  ///
  /// Check if End Point is prensent or not on Pcie device..
  ///
  if (PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, PciePortBus, SA_TEMP_DGPU_DEV, SA_TEMP_DGPU_FUN, PCI_VENDOR_ID_OFFSET)) == 0xFFFF) {
    return EFI_UNSUPPORTED;
  }

  PcieCapOffset = (UINT8)PcieFindCapId (SA_SEG_NUM, PciePortBus, SA_TEMP_DGPU_DEV, SA_TEMP_DGPU_FUN, PCIE_CAP_ID);

  if (PciePortDev == 1) {
    switch (PciePortFun) {

      case 0:
        SaNvsAreaProtocol->Area->Pcie0EpCapOffset = PcieCapOffset;
        break;
    }
  }

  return Status;
}

