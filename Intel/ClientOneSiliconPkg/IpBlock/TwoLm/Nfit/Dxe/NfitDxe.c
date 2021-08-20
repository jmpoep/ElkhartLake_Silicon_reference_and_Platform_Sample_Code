/** @file
  This code provides Initialization of Nfit tables for 2LM/PMem.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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

#include "NfitDxe.h"

#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/AcpiTable.h>
#include <Protocol/AcpiSystemDescriptionTable.h>
#include <Uefi/UefiSpec.h>
#include <Pi/PiFirmwareFile.h>
#include <Protocol/FirmwareVolume2.h>
#include <Library/PeiDxeSmmTwoLmLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseLib.h>
#include <Library/HobLib.h>


extern EFI_GUID               gSaAcpiTableStorageGuid;
extern EFI_GUID               gTwoLmAcpiNfitTableGuid;
extern EFI_GUID               gTwoLmInfoHobGuid;

EFI_ACPI_NFIT_TABLE NfitTable = {

    NVDIMM_FW_INTERFACE_TABLE_SIGNATURE,      // Signature
    sizeof (EFI_ACPI_NFIT_TABLE),             // Length
    NVDIMM_FW_INTERFACE_TABLE_REVISION,       // Revision  [01]
    0,                                        // Checksum
    { 'I', 'N', 'T', 'E', 'L', ' ' },
    NVDIMM_FW_INTERFACE_TABLE_OEM_TABLE_ID,     // OemTblId
    NVDIMM_FW_INTERFACE_TABLE_OEM_RIVISION,     // OemRevision
    NVDIMM_FW_INTERFACE_TABLE_OEM_CREATOR_ID,   // CreatorId
    NVDIMM_FW_INTERFACE_TABLE_CREATOR_RIVISION, // CreatorRev
    0,                                          // Reserved
    {
      EFI_ACPI_6_1_NFIT_SYSTEM_PHYSICAL_ADDRESS_RANGE_STRUCTURE_TYPE,     // Type
      sizeof (EFI_ACPI_6_1_NFIT_SYSTEM_PHYSICAL_ADDRESS_RANGE_STRUCTURE), // Length
      1,                                                                  // SPARangeStructureIndex
      0x0,                                                                // Flags
      0,                                                                  // Reserved
      0,                                                                  // ProximityDomain
      EFI_ACPI_6_2_NFIT_GUID_BYTE_ADDRESSABLE_PERSISTENT_MEMORY_REGION,   // AddressRangeTypeGUID
      0,                                                                  // SystemPhysicalAddressRangeBase
      0,                                                                  // SystemPhysicalAddressRangeLength
      0                                                                   // AddressRangeMemoryMappingAttribute
  },

  {
    EFI_ACPI_6_2_NFIT_NVDIMM_REGION_MAPPING_STRUCTURE_TYPE,         // Type
    sizeof (EFI_ACPI_6_2_NFIT_NVDIMM_REGION_MAPPING_STRUCTURE),     // Length
    {0x1},                                                          // NFITDeviceHandle
    17,                                                             // Type17 handle from BIOS boot
    1,                                                              // NVDIMMRegionID
    1,                                                              // SPARangeStructureIndex
    1,                                                              // NVDIMMControlRegionStructureIndex
    0,                                                              // NVDIMMRegionSize
    0,                                                              // RegionOffset
    0,                                                              // NVDIMMPhysicalAddressRegionBase
    0,                                                              // InterleaveStructureIndex
    0x1,                                                            // InterleaveWays
    0x20,                                                           // NVDIMMStateFlags
    0                                                               // Reserved
  },

  {
    EFI_ACPI_6_2_NFIT_NVDIMM_CONTROL_REGION_STRUCTURE_TYPE,                   // Type
    32,                                     // Length
    1,                                    // NVDIMMControlRegionStructureIndex
    0x8086,                                    // VendorID
    0x41c0,                                    // DeviceID
    0x0,                                    // RevisionID
    0x8086,                                    // SubsystemVendorID
    0,                                    // SubsystemDeviceID
    0,                                    // SubsystemRevisionID
    0x1,                                    // ValidFields
    0xa2,                                    // ManufacturingLocation
    0x18,                                    // ManufacturingDate
    {0,0},                                    //  Reserved_22[2]
    0,                                    //  SerialNumber
    0,                                    //  RegionFormatInterfaceCode
    0                                    //  NumberOfBlockControlWindows
  }

  /*{
    EFI_ACPI_6_2_NFIT_PLATFORM_CAPABILITIES_STRUCTURE_TYPE,      // Type
    sizeof (EFI_ACPI_6_2_NFIT_PLATFORM_CAPABILITIES_STRUCTURE),  // Length
    0,                                                           // HighestValidCapability
    0,                                                           //  Rsvd1
    0,                                                           // Rsvd2
    0,                                                           //  Capabilities
    0                                                            //  Rsvd3
  }*/

};

/**
  Update the NFIT table

  @param[in, out] TableHeader         - The table to be set
  @param[in]      TwoLmInfoHob        - Version to publish
**/
VOID
NfitTableUpdate (
  IN       TWOLM_INFO_HOB        *TwoLmInfoHob
  )
{
  EFI_ACPI_NFIT_TABLE *NfitTablePtr;

  NfitTablePtr   = (EFI_ACPI_NFIT_TABLE *) &NfitTable;

  DEBUG ((DEBUG_INFO, "2LM: NfitTableUpdate...Start\n"));

  //
  // Update the dynamic fields
  //
  NfitTablePtr->NfitSpa.SystemPhysicalAddressRangeBase   = TwoLmInfoHob->TwoLmInfo.PMemBase;
  NfitTablePtr->NfitSpa.SystemPhysicalAddressRangeLength = LShiftU64(TwoLmInfoHob->TwoLmInfo.PMemSize, 20); // In bytes
  NfitTablePtr->NfitSpa.AddressRangeMemoryMappingAttribute = (EFI_MEMORY_NV | EFI_MEMORY_WB);

  NfitTablePtr->NfitRms.NVDIMMRegionSize           =  LShiftU64(TwoLmInfoHob->TwoLmInfo.PMemSize, 20); // In bytes

  NfitTablePtr->NfitNcrs.VendorID                  =  TwoLmInfoHob->TwoLmInfo.VendorId;
  NfitTablePtr->NfitNcrs.DeviceID                  =  TwoLmInfoHob->TwoLmInfo.DevId;
  NfitTablePtr->NfitNcrs.RevisionID                =  TwoLmInfoHob->TwoLmInfo.RevisionId;
  NfitTablePtr->NfitNcrs.RegionFormatInterfaceCode =  TwoLmInfoHob->TwoLmInfo.Ifc;
  NfitTablePtr->NfitNcrs.SerialNumber              =  TwoLmInfoHob->TwoLmInfo.SerialNum;

  DEBUG ((DEBUG_INFO, "2LM: NfitSpa.SystemPhysicalAddressRangeBase 0x%lx\n", NfitTablePtr->NfitSpa.SystemPhysicalAddressRangeBase));
  DEBUG ((DEBUG_INFO, "2LM: NfitSpa.SystemPhysicalAddressRangeLength 0x%lx\n", NfitTablePtr->NfitSpa.SystemPhysicalAddressRangeLength));
  DEBUG ((DEBUG_INFO, "2LM: NfitSpa.AddressRangeMemoryMappingAttribute 0x%x\n", NfitTablePtr->NfitSpa.AddressRangeMemoryMappingAttribute));

  DEBUG ((DEBUG_INFO, "2LM: NfitRms.NVDIMMRegionSize 0x%lx\n", NfitTablePtr->NfitRms.NVDIMMRegionSize));

  DEBUG ((DEBUG_INFO, "2LM: NfitNcrs.VendorID 0x%x\n", NfitTablePtr->NfitNcrs.VendorID));
  DEBUG ((DEBUG_INFO, "2LM: NfitNcrs.DeviceID 0x%x\n", NfitTablePtr->NfitNcrs.DeviceID));
  DEBUG ((DEBUG_INFO, "2LM: NfitNcrs.RevisionID 0x%x\n", NfitTablePtr->NfitNcrs.RevisionID));
  DEBUG ((DEBUG_INFO, "2LM: NfitNcrs.RegionFormatInterfaceCode 0x%x\n", NfitTablePtr->NfitNcrs.RegionFormatInterfaceCode));
  DEBUG ((DEBUG_INFO, "2LM: NfitNcrs.SerialNumber 0x%x\n", NfitTablePtr->NfitNcrs.SerialNumber));

  DEBUG ((DEBUG_INFO, "2LM: NfitTableUpdate...End\n"));
}


/**
  This function installs Nfit ACPI table

  @param[in] ImageHandle             Handle for the image of this driver
  @param[in] SystemTable             Pointer to the EFI System Table

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_OUT_OF_RESOURCES    No enough buffer to allocate
**/
EFI_STATUS
EFIAPI
NfitEntryPoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                      Status;
  UINTN                           AcpiTableHandle;
  EFI_ACPI_TABLE_PROTOCOL         *AcpiTable;
  TWOLM_INFO_HOB                  *TwoLmInfoHob;

  AcpiTable     = NULL;

  DEBUG ((DEBUG_INFO, "NfitEntryPoint \n"));

  TwoLmInfoHob = (TWOLM_INFO_HOB *) GetFirstGuidHob (&gTwoLmInfoHobGuid);
  if (TwoLmInfoHob == NULL) {
    DEBUG ((DEBUG_INFO, "2LM: TwoLmInfoHob not found\n"));
    return EFI_UNSUPPORTED;
  }

  ///
  /// Fix Nfit Table always created, skip install when PMem is not enabled
  ///
  if (TwoLmInfoHob->TwoLmInfo.PMemSize == 0) {
    DEBUG ((DEBUG_INFO, "PMEM Disabled, skip Nfit Table install\n"));
    return EFI_SUCCESS;
  }
  ///
  /// Locate ACPI support protocol
  ///
  Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, (VOID **) &AcpiTable);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  NfitTableUpdate (TwoLmInfoHob);
  ///
  /// Update the Nfit table in the ACPI tables.
  ///
  AcpiTableHandle = 0;
  if (&NfitTable != NULL) {
    Status = AcpiTable->InstallAcpiTable (
                          AcpiTable,
                          &NfitTable,
                          NfitTable.Length,
                          &AcpiTableHandle
                          );
    DEBUG ((DEBUG_INFO, "2LM: Nfit Table installed\n"));
  }

  return EFI_SUCCESS;
}
