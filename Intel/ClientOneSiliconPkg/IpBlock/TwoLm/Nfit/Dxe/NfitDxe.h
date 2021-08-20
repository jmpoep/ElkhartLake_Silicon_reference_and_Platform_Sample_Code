/** @file
  This file describes the ACPI NVDIMM Firmware Interface Table (NFIT)

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
#ifndef _NFIT_H_
#define _NFIT_H_

///
/// Include standard ACPI table definitions
///
#include <IndustryStandard/Acpi62.h>

#pragma pack(1)

#define EFI_ACPI_NFIT_OEM_TABLE_ID    0x20202020324B4445  // "EDK2"


#define NVDIMM_FW_INTERFACE_TABLE_SIGNATURE EFI_ACPI_6_2_NVDIMM_FIRMWARE_INTERFACE_TABLE_STRUCTURE_SIGNATURE
#define NVDIMM_FW_INTERFACE_TABLE_REVISION  EFI_ACPI_6_2_NVDIMM_FIRMWARE_INTERFACE_TABLE_REVISION

#define NVDIMM_FW_INTERFACE_TABLE_OEMID            ('I', 'N', 'T', 'E', 'L', ' ')
#define NVDIMM_FW_INTERFACE_TABLE_OEM_TABLE_ID     SIGNATURE_64 ('N', 'F', 'I', 'T', 'T', 'a', 'b', 'l')
#define NVDIMM_FW_INTERFACE_TABLE_OEM_RIVISION     0x00
#define NVDIMM_FW_INTERFACE_TABLE_OEM_CREATOR_ID   SIGNATURE_32('I', 'N', 'T', 'L')
#define NVDIMM_FW_INTERFACE_TABLE_CREATOR_RIVISION   0x01

#define EFI_ACPI_6_2_NFIT_PLATFORM_CAPABILITIES_STRUCTURE_TYPE       7  //NFIT Structure Types


typedef struct {
  UINT16                                      Type;
  UINT16                                      Length;
  UINT16                                      NVDIMMControlRegionStructureIndex;
  UINT16                                      VendorID;
  UINT16                                      DeviceID;
  UINT16                                      RevisionID;
  UINT16                                      SubsystemVendorID;
  UINT16                                      SubsystemDeviceID;
  UINT16                                      SubsystemRevisionID;
  UINT8                                       ValidFields;
  UINT8                                       ManufacturingLocation;
  UINT16                                      ManufacturingDate;
  UINT8                                       Reserved_22[2];
  UINT32                                      SerialNumber;
  UINT16                                      RegionFormatInterfaceCode;
  UINT16                                      NumberOfBlockControlWindows;
} EFI_ACPI_6_2_NFIT_NVDIMM_CONTROL_REGION_STRUCTURE_CLIENT;
//
// NFIT PLATFORM CAPABILITIES STRUCTURE
//
typedef struct {
  UINT16                                      Type;
  UINT16                                      Length;
  UINT8                                       HighestValidCapability;
  UINT8                                       Rsvd1;
  UINT16                                      Rsvd2;
  UINT32                                      Capabilities;
  UINT32                                      Rsvd3;
} EFI_ACPI_6_2_NFIT_PLATFORM_CAPABILITIES_STRUCTURE;

//
// NVDIMM Firmware Interface Table struct
//
typedef struct {

  UINT32       Signature;                    // 'NFIT' is the signature for this table
  UINT32       Length;                       // Length in bytes for the entire table
  UINT8        Revision;                     // Revision # of this table, initial is '1'
  UINT8        Checksum;                     // Entire Table Checksum must sum to 0
  UINT8        OemId[6];                     // OemID
  UINT64       OemTblId;                     // Should be Manufacturer's Model #
  UINT32       OemRevision;                  // Oem Revision of for Supplied OEM Table ID
  UINT32       CreatorId;                    // Vendor ID of the utility that is creating this table
  UINT32       CreatorRev;                   // Revision of utility that is creating this table
  UINT32       Reserved;
  EFI_ACPI_6_2_NFIT_SYSTEM_PHYSICAL_ADDRESS_RANGE_STRUCTURE NfitSpa;
  EFI_ACPI_6_2_NFIT_NVDIMM_REGION_MAPPING_STRUCTURE NfitRms;
  EFI_ACPI_6_2_NFIT_NVDIMM_CONTROL_REGION_STRUCTURE_CLIENT NfitNcrs;
  //EFI_ACPI_6_2_NFIT_PLATFORM_CAPABILITIES_STRUCTURE NfitPcs;
} EFI_ACPI_NFIT_TABLE;


#define EFI_ACPI_6_2_NFIT_NVDIMM_PLATFORM_CAPABILITIES_CPU_CACHE_FLUSH_TO_NVDIMM            BIT0
#define EFI_ACPI_6_2_NFIT_NVDIMM_PLATFORM_CAPABILITIES_MEMORY_CONTROLLER_FLUSH_TO_NVDIMM    BIT1
#define EFI_ACPI_6_2_NFIT_NVDIMM_PLATFORM_CAPABILITIES_PMEM_HARDWARE_MIRRORING              BIT2



#pragma pack()


#endif
