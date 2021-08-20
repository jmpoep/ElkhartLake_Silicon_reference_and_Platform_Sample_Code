/** @file
  Install CSRT Table Library

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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
#include <Uefi.h>
#include <Uefi/UefiBaseType.h>
#include <Protocol/AcpiTable.h>
#include <Protocol/PchPolicy.h>
#include <Pi/PiFirmwareFile.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DxeServicesLib.h>
#include <Library/IoLib.h>
#include <Library/PciSegmentLib.h>
#include <Register/PseRegs.h>
#include <Library/PsfLib.h>
#include <Library/PchPseIoLib.h>
#include <Library/PchInfoLib.h>
#include <PseConfig.h>
#include "PchInit.h"

///
/// CSRT Definitions
///
#define EFI_ACPI_CSRT_TABLE_REVISION 0x00
#define MAX_NO_CHANNEL_SUPPORTED    9
#define EFI_ACPI_OEM_ID              "INTEL "  // OEMID 6 bytes long
#define EFI_ACPI_OEM_TABLE_ID        SIGNATURE_64('E','D','K','2',' ',' ',' ',' ') // OEM table id 8 bytes long
#define EFI_ACPI_OEM_REVISION        0x00000005
#define EFI_ACPI_CREATOR_ID          SIGNATURE_32('I','N','T','L')
#define EFI_ACPI_CREATOR_REVISION    0x20181210

///
/// Ensure proper structure formats for CSRT
///
#pragma pack (1)
///
/// Resource  Share Info
///
typedef struct _SHARED_INFO_SECTION {
  UINT16 MajVersion;
  UINT16 MinVersion;
  UINT32 MMIOLowPart;
  UINT32 MMIOHighPart;
  UINT32 IntGSI;
  UINT8  IntPol;
  UINT8  IntMode;
  UINT8  NoOfCh;
  UINT8  DMAAddressWidth;
  UINT16 BaseReqLine;
  UINT16 NoOfHandSig;
  UINT32 MaxBlockTransferSize;
  } SHARED_INFO_SECTION;
///
/// Resource Group Header
///
typedef struct _RESOURCE_GROUP_HEADER {
  UINT32 Length;
  UINT32 VendorId;
  UINT32 SubVendorId;
  UINT16 DeviceId;
  UINT16 SubDeviceId;
  UINT16 Revision;
  UINT16 Reserved;
  UINT32 SharedInfoLength;
  SHARED_INFO_SECTION SharedInfoSection;
} RESOURCE_GROUP_HEADER;
///
/// Resource Descriptor Header
///
typedef struct _RESOURCE_DESCRIPTOR {
  UINT32 Length;
  UINT16 ResourceType;
  UINT16 ResourceSubType;
  UINT32 UUID;
} RESOURCE_DESCRIPTOR;

typedef struct {
  RESOURCE_GROUP_HEADER          ResourceGroupHeaderInfo;
  RESOURCE_DESCRIPTOR            ResourceDescriptorInfo[MAX_NO_CHANNEL_SUPPORTED];
 } RESOURCE_GROUP_INFO;

///
/// Core System Resources Table Structure (CSRT)
///
typedef struct {
  EFI_ACPI_DESCRIPTION_HEADER    Header;
  RESOURCE_GROUP_INFO            ResourceGroupInfo[];
} EFI_ACPI_CSRT_TABLE;

#pragma pack ()

/**
  Initialize and publish CSRT ACPI table.

  @retval   EFI_SUCCESS     The CSRT ACPI table is published successfully.
  @retval   EFI_NOT_FOUND   The CSRT ACPI table does not exist.
  @retval   EFI_LOAD_ERROR  The CSRT ACPI table has bad signature.
  @retval   EFI_UNSUPPORTED The ACPI table cannot be located.
**/
EFI_STATUS
UpdateCsrtAcpiData (
  VOID
  )
{
  EFI_STATUS                      Status;
  EFI_ACPI_CSRT_TABLE             *mCsrt;
  EFI_ACPI_TABLE_PROTOCOL         *AcpiTableProtocol;
  UINT8                           GroupIndex;
  UINT8                           Index;
  UINTN                           AcpiTableKey = 0;
  UINT8                           ResourceGroupCount;
  RESOURCE_GROUP_INFO             ResourceGroupInfo;

  DEBUG ((DEBUG_INFO, "UpdateCsrtAcpiData () - Start\n"));

  if (mPchConfigHob->Pse.PseDmaEnable[1] == PSE_OWNED && mPchConfigHob->Pse.PseDmaEnable[2] == PSE_OWNED) {
    DEBUG ((DEBUG_INFO, "PSE DMA1 and PSE DMA2 are owned by PSE, skip installing CSRT ACPI table\n"));
    return EFI_UNSUPPORTED;
  }

  ResourceGroupCount = 0;
  for (Index = 1; Index < GetPchMaxPseDmaControllersNum (); Index++) {
    if (mPchConfigHob->Pse.PseDmaEnable[Index] == HOST_OWNED) {
      ResourceGroupCount++;
    }
  }
  //
  // Skip CSRT generation if no resource group available
  //
  if (ResourceGroupCount == 0) {
    return EFI_UNSUPPORTED;
  }
  //
  // Locate ACPI support protocol
  //
  Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, (VOID **) &AcpiTableProtocol);
  if ( EFI_ERROR (Status) || AcpiTableProtocol == NULL) {
    return EFI_UNSUPPORTED;
  }
  ///
  /// Allocate Memory for Core System Resources Table
  ///
  mCsrt = AllocateZeroPool (ResourceGroupCount * sizeof (RESOURCE_GROUP_INFO) + sizeof (EFI_ACPI_DESCRIPTION_HEADER));
  if (mCsrt == NULL) {
    DEBUG ((EFI_D_INFO, "CSRT = null\n"));
    return EFI_NOT_FOUND;
  }

  ///
  /// Constructing CSRT
  ///
  mCsrt->Header.Signature        = EFI_ACPI_5_0_CORE_SYSTEM_RESOURCE_TABLE_SIGNATURE;
  mCsrt->Header.Length           = ResourceGroupCount * sizeof (RESOURCE_GROUP_INFO) + sizeof (EFI_ACPI_DESCRIPTION_HEADER);
  mCsrt->Header.Revision         = EFI_ACPI_CSRT_TABLE_REVISION;
  mCsrt->Header.Checksum         = 0;
  CopyMem(&mCsrt->Header.OemId, EFI_ACPI_OEM_ID, 6);
  mCsrt->Header.OemTableId       = EFI_ACPI_OEM_TABLE_ID;
  mCsrt->Header.OemRevision      = EFI_ACPI_OEM_REVISION;
  mCsrt->Header.CreatorId        = EFI_ACPI_CREATOR_ID;
  mCsrt->Header.CreatorRevision  = EFI_ACPI_CREATOR_REVISION;

  GroupIndex = 0;
  if (mPchConfigHob->Pse.PseDmaEnable[1] == HOST_OWNED && GroupIndex < ResourceGroupCount) {
    ResourceGroupInfo.ResourceGroupHeaderInfo.Length                                  = sizeof (RESOURCE_GROUP_INFO);
    ResourceGroupInfo.ResourceGroupHeaderInfo.VendorId                                = SIGNATURE_32('I','N','T','L');
    ResourceGroupInfo.ResourceGroupHeaderInfo.SubVendorId                             = 0x00000000;
    ResourceGroupInfo.ResourceGroupHeaderInfo.DeviceId                                = PSE_CFG_DMA1_DEVICE_ID;
    ResourceGroupInfo.ResourceGroupHeaderInfo.SubDeviceId                             = 0x0000;
    ResourceGroupInfo.ResourceGroupHeaderInfo.Revision                                = 0x0002;
    ResourceGroupInfo.ResourceGroupHeaderInfo.Reserved                                = 0x0000;
    ResourceGroupInfo.ResourceGroupHeaderInfo.SharedInfoLength                        = sizeof (SHARED_INFO_SECTION);
    ResourceGroupInfo.ResourceGroupHeaderInfo.SharedInfoSection.MajVersion            = 0x0001;
    ResourceGroupInfo.ResourceGroupHeaderInfo.SharedInfoSection.MinVersion            = 0x0000;
    ResourceGroupInfo.ResourceGroupHeaderInfo.SharedInfoSection.MMIOLowPart           = PCH_PSE_DMA1_BASE_ADDRESS;
    ResourceGroupInfo.ResourceGroupHeaderInfo.SharedInfoSection.MMIOHighPart          = 0x00000000;
    ResourceGroupInfo.ResourceGroupHeaderInfo.SharedInfoSection.IntGSI                = 0x00000023;
    ResourceGroupInfo.ResourceGroupHeaderInfo.SharedInfoSection.IntPol                = 0x02;
    ResourceGroupInfo.ResourceGroupHeaderInfo.SharedInfoSection.IntMode               = 0x00;
    ResourceGroupInfo.ResourceGroupHeaderInfo.SharedInfoSection.NoOfCh                = MAX_NO_CHANNEL_SUPPORTED - 1;
    ResourceGroupInfo.ResourceGroupHeaderInfo.SharedInfoSection.DMAAddressWidth       = 0x20;
    ResourceGroupInfo.ResourceGroupHeaderInfo.SharedInfoSection.BaseReqLine           = 0x0040;
    ResourceGroupInfo.ResourceGroupHeaderInfo.SharedInfoSection.NoOfHandSig           = 0x0040;
    ResourceGroupInfo.ResourceGroupHeaderInfo.SharedInfoSection.MaxBlockTransferSize  = 0x0001FFFF;

    ResourceGroupInfo.ResourceDescriptorInfo[0].Length           = 0x0000000C;
    ResourceGroupInfo.ResourceDescriptorInfo[0].ResourceType     = 0x0003;
    ResourceGroupInfo.ResourceDescriptorInfo[0].ResourceSubType  = 0x0001;
    ResourceGroupInfo.ResourceDescriptorInfo[0].UUID             = 0x30455350; //PSE0

    for(Index = 1; Index < MAX_NO_CHANNEL_SUPPORTED; Index++) {
      ResourceGroupInfo.ResourceDescriptorInfo[Index].Length           = 0x0000000C;
      ResourceGroupInfo.ResourceDescriptorInfo[Index].ResourceType     = 0x0003;
      ResourceGroupInfo.ResourceDescriptorInfo[Index].ResourceSubType  = 0x0000;
      ResourceGroupInfo.ResourceDescriptorInfo[Index].UUID             = 0x30414843 + ((Index - 1) << 24); //CHAn
    }
    CopyMem (&mCsrt->ResourceGroupInfo[GroupIndex], &ResourceGroupInfo, sizeof (RESOURCE_GROUP_INFO));
    GroupIndex++;
  }

  if (mPchConfigHob->Pse.PseDmaEnable[2] == HOST_OWNED && GroupIndex < ResourceGroupCount) {
    ResourceGroupInfo.ResourceGroupHeaderInfo.Length                                  = sizeof (RESOURCE_GROUP_INFO);
    ResourceGroupInfo.ResourceGroupHeaderInfo.VendorId                                = SIGNATURE_32('I','N','T','L');
    ResourceGroupInfo.ResourceGroupHeaderInfo.SubVendorId                             = 0x00000000;
    ResourceGroupInfo.ResourceGroupHeaderInfo.DeviceId                                = PSE_CFG_DMA2_DEVICE_ID;
    ResourceGroupInfo.ResourceGroupHeaderInfo.SubDeviceId                             = 0x0000;
    ResourceGroupInfo.ResourceGroupHeaderInfo.Revision                                = 0x0003;
    ResourceGroupInfo.ResourceGroupHeaderInfo.Reserved                                = 0x0000;
    ResourceGroupInfo.ResourceGroupHeaderInfo.SharedInfoLength                        = sizeof (SHARED_INFO_SECTION);
    ResourceGroupInfo.ResourceGroupHeaderInfo.SharedInfoSection.MajVersion            = 0x0001;
    ResourceGroupInfo.ResourceGroupHeaderInfo.SharedInfoSection.MinVersion            = 0x0000;
    ResourceGroupInfo.ResourceGroupHeaderInfo.SharedInfoSection.MMIOLowPart           = PCH_PSE_DMA2_BASE_ADDRESS;
    ResourceGroupInfo.ResourceGroupHeaderInfo.SharedInfoSection.MMIOHighPart          = 0x00000000;
    ResourceGroupInfo.ResourceGroupHeaderInfo.SharedInfoSection.IntGSI                = 0x00000024;
    ResourceGroupInfo.ResourceGroupHeaderInfo.SharedInfoSection.IntPol                = 0x02;
    ResourceGroupInfo.ResourceGroupHeaderInfo.SharedInfoSection.IntMode               = 0x00;
    ResourceGroupInfo.ResourceGroupHeaderInfo.SharedInfoSection.NoOfCh                = MAX_NO_CHANNEL_SUPPORTED - 1;
    ResourceGroupInfo.ResourceGroupHeaderInfo.SharedInfoSection.DMAAddressWidth       = 0x20;
    ResourceGroupInfo.ResourceGroupHeaderInfo.SharedInfoSection.BaseReqLine           = 0x0080;
    ResourceGroupInfo.ResourceGroupHeaderInfo.SharedInfoSection.NoOfHandSig           = 0x0040;
    ResourceGroupInfo.ResourceGroupHeaderInfo.SharedInfoSection.MaxBlockTransferSize  = 0x0001FFFF;

    ResourceGroupInfo.ResourceDescriptorInfo[0].Length           = 0x0000000C;
    ResourceGroupInfo.ResourceDescriptorInfo[0].ResourceType     = 0x0003;
    ResourceGroupInfo.ResourceDescriptorInfo[0].ResourceSubType  = 0x0001;
    ResourceGroupInfo.ResourceDescriptorInfo[0].UUID             = 0x31455350; //PSE1

    for (Index = 1; Index < MAX_NO_CHANNEL_SUPPORTED; Index++) {
      ResourceGroupInfo.ResourceDescriptorInfo[Index].Length           = 0x0000000C;
      ResourceGroupInfo.ResourceDescriptorInfo[Index].ResourceType     = 0x0003;
      ResourceGroupInfo.ResourceDescriptorInfo[Index].ResourceSubType  = 0x0000;
      ResourceGroupInfo.ResourceDescriptorInfo[Index].UUID             = 0x30414843 + ((Index - 1) << 24); //CHAn
    }
    CopyMem (&mCsrt->ResourceGroupInfo[GroupIndex], &ResourceGroupInfo, sizeof (RESOURCE_GROUP_INFO));
  }

  Status = AcpiTableProtocol->InstallAcpiTable (AcpiTableProtocol, mCsrt, mCsrt->Header.Length, &AcpiTableKey);

  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_INFO, "Installing CSRT to ACPI fail!\n"));
  }

  DEBUG ((DEBUG_INFO, "UpdateCsrtAcpiData () - End Status = %r\n", Status));
  return Status;
}

