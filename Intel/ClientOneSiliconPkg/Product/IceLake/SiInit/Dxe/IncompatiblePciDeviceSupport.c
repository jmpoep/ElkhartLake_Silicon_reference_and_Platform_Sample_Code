/** @file
  Incompatible PCI Device Support protocol allows the PCI bus driver to support
  resource allocation for some PCI devices that do not comply with the PCI Specification.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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

#include <PiDxe.h>
#include <Protocol/IncompatiblePciDeviceSupport.h>

#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/PciSegmentLib.h>

#include <IndustryStandard/Pci.h>
#include <IndustryStandard/Acpi.h>
#include <SiConfigHob.h>
#include <SaCommonDefinitions.h>
#include <Register/IpuRegs.h>
#include <Protocol/SaPolicy.h>
#include <Register/IgdRegs.h>
#include <SaDataHob.h>

#define OLD_ALIGN   0xFFFFFFFFFFFFFFFFULL

/**
  Returns a list of ACPI resource descriptors that detail the special
  resource configuration requirements for an incompatible PCI device.

  @param  This                  Pointer to the EFI_INCOMPATIBLE_PCI_DEVICE_SUPPORT_PROTOCOL instance.
  @param  VendorId              A unique ID to identify the manufacturer of the PCI device.
  @param  DeviceId              A unique ID to identify the particular PCI device.
  @param  RevisionId            A PCI device-specific revision identifier.
  @param  SubsystemVendorId     Specifies the subsystem vendor ID.
  @param  SubsystemDeviceId     Specifies the subsystem device ID.
  @param  Configuration         A list of ACPI resource descriptors returned that detail
                                the configuration requirement.

  @retval EFI_SUCCESS           Successfully got ACPI resource for specified PCI device.
  @retval EFI_INVALID_PARAMETER Configuration is NULL.
  @retval EFI_OUT_OF_RESOURCES  No memory available.
  @retval EFI_UNSUPPORTED       The specified PCI device wasn't supported.

**/
EFI_STATUS
EFIAPI
PCheckDevice (
  IN  EFI_INCOMPATIBLE_PCI_DEVICE_SUPPORT_PROTOCOL  *This,
  IN  UINTN                                         VendorId,
  IN  UINTN                                         DeviceId,
  IN  UINTN                                         RevisionId,
  IN  UINTN                                         SubsystemVendorId,
  IN  UINTN                                         SubsystemDeviceId,
  OUT VOID                                          **Configuration
  );

//
// Handle onto which the Incompatible PCI Device List is installed
//
EFI_HANDLE                                    mIncompatiblePciDeviceSupportHandle = NULL;

//
// The Incompatible PCI Device Support Protocol instance produced by this driver
//
EFI_INCOMPATIBLE_PCI_DEVICE_SUPPORT_PROTOCOL  mIncompatiblePciDeviceSupport = {
  PCheckDevice
};

/**
  Entry point of the incompatible pci device support code. Setup an incompatible device list template
  and install EFI Incompatible PCI Device Support protocol.

  @param ImageHandle             A handle for the image that is initializing this driver.
  @param SystemTable             A pointer to the EFI system table.

  @retval EFI_SUCCESS            Installed EFI Incompatible PCI Device Support Protocol successfully.
  @retval others                 Failed to install protocol.

**/
EFI_STATUS
EFIAPI
IncompatiblePciDeviceSupport (
  VOID
  )
{
  EFI_STATUS                         Status;

  //
  // Install EFI Incompatible PCI Device Support Protocol on a new handle
  //
  Status = gBS->InstallProtocolInterface (
                  &mIncompatiblePciDeviceSupportHandle,
                  &gEfiIncompatiblePciDeviceSupportProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &mIncompatiblePciDeviceSupport
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/**
  Returns a list of ACPI resource descriptors that detail the special
  resource configuration requirements for an incompatible PCI device.

  @param  This                  Pointer to the EFI_INCOMPATIBLE_PCI_DEVICE_SUPPORT_PROTOCOL instance.
  @param  VendorId              A unique ID to identify the manufacturer of the PCI device.
  @param  DeviceId              A unique ID to identify the particular PCI device.
  @param  RevisionId            A PCI device-specific revision identifier.
  @param  SubsystemVendorId     Specifies the subsystem vendor ID.
  @param  SubsystemDeviceId     Specifies the subsystem device ID.
  @param  Configuration         A list of ACPI resource descriptors returned that detail
                                the configuration requirement.

  @retval EFI_SUCCESS           Successfully got ACPI resource for specified PCI device.
  @retval EFI_INVALID_PARAMETER Configuration is NULL.
  @retval EFI_OUT_OF_RESOURCES  No memory available.
  @retval EFI_UNSUPPORTED       The specified PCI device wasn't supported.

**/
EFI_STATUS
EFIAPI
PCheckDevice (
  IN  EFI_INCOMPATIBLE_PCI_DEVICE_SUPPORT_PROTOCOL  *This,
  IN  UINTN                                         VendorId,
  IN  UINTN                                         DeviceId,
  IN  UINTN                                         RevisionId,
  IN  UINTN                                         SubsystemVendorId,
  IN  UINTN                                         SubsystemDeviceId,
  OUT VOID                                          **Configuration
  )
{
  EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *AcpiPtr;
  EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *OldAcpiPtr;
  EFI_ACPI_END_TAG_DESCRIPTOR       *PtrEnd;
  EFI_PEI_HOB_POINTERS              HobPtr;
  SI_CONFIG_HOB_DATA                *SiConfigHobData;
  BOOLEAN                           ResourceChanged;
  SA_DATA_HOB                       *SaDataHob;

  AcpiPtr = NULL;
  OldAcpiPtr = NULL;
  ResourceChanged = FALSE;

  //
  // Validate the parameters
  //
  if (Configuration == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  //
  // Initialize the return value to NULL
  //
  * (VOID **) Configuration = NULL;

  //
  // Fill the EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR structure
  // according to the EFI_PCI_RESOUCE_DESCRIPTOR structure
  //


  //
  // When CSM enabled, the second BAR of IGFX has to be overridden to 32bits BAR even register indicates 64bits support
  // This is because legacy VBIOS execution environment doesn't support 64bit MMIO access
  //
  if ((UINT16) DeviceId == PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS(SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, PCI_DEVICE_ID_OFFSET))) {
    HobPtr.Guid   = GetFirstGuidHob (&gSiConfigHobGuid);
    SiConfigHobData = (SI_CONFIG_HOB_DATA *)GET_GUID_HOB_DATA (HobPtr.Guid);

    if (SiConfigHobData->CsmFlag == 1) {
      AcpiPtr = AllocateZeroPool (sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR) + sizeof (EFI_ACPI_END_TAG_DESCRIPTOR));
      if (AcpiPtr == NULL) {
        return EFI_OUT_OF_RESOURCES;
      }

      ResourceChanged = TRUE;
      OldAcpiPtr = AcpiPtr;

      AcpiPtr->Desc = ACPI_ADDRESS_SPACE_DESCRIPTOR;
      AcpiPtr->Len = (UINT16) sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR);
      AcpiPtr->ResType = ACPI_ADDRESS_SPACE_TYPE_MEM;
      AcpiPtr->GenFlag = 0;
      AcpiPtr->SpecificFlag = EFI_ACPI_MEMORY_RESOURCE_SPECIFIC_FLAG_CACHEABLE_PREFETCHABLE;
      AcpiPtr->AddrSpaceGranularity = 32;
      AcpiPtr->AddrRangeMin = 0;
      AcpiPtr->AddrRangeMax = OLD_ALIGN;
      AcpiPtr->AddrTranslationOffset = PCI_BAR_IDX1;
      AcpiPtr->AddrLen = 0;
      AcpiPtr++;
    } else {
      //
      // Assign GMADR resource
      //
      SaDataHob = NULL;
      SaDataHob = (SA_DATA_HOB *) GetFirstGuidHob (&gSaDataHobGuid);
      if (SaDataHob == NULL) {
        return EFI_OUT_OF_RESOURCES;
      }

      if (SaDataHob->EnableAbove4GBMmio == 1) {
        AcpiPtr = AllocateZeroPool (sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR) + sizeof (EFI_ACPI_END_TAG_DESCRIPTOR));
        if (AcpiPtr == NULL) {
          return EFI_OUT_OF_RESOURCES;
        }
        OldAcpiPtr = AcpiPtr;
        ResourceChanged = TRUE;
        AcpiPtr->Desc = ACPI_ADDRESS_SPACE_DESCRIPTOR;
        AcpiPtr->Len = (UINT16) sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR);
        AcpiPtr->ResType = ACPI_ADDRESS_SPACE_TYPE_MEM;
        AcpiPtr->GenFlag = 0;
        AcpiPtr->SpecificFlag = EFI_ACPI_MEMORY_RESOURCE_SPECIFIC_FLAG_CACHEABLE_PREFETCHABLE;
        AcpiPtr->AddrSpaceGranularity = 64;
        AcpiPtr->AddrRangeMin = 0;
        AcpiPtr->AddrRangeMax = SIZE_128GB - 1;
        AcpiPtr->AddrTranslationOffset = PCI_BAR_IDX1;
        AcpiPtr->AddrLen = SIZE_128GB;
        AcpiPtr++;
      }
    }
  }

  if (!ResourceChanged) {
    return EFI_UNSUPPORTED;
  }

  //
  // Put the checksum
  //
  PtrEnd                    = (EFI_ACPI_END_TAG_DESCRIPTOR *) (AcpiPtr);
  PtrEnd->Desc              = ACPI_END_TAG_DESCRIPTOR;
  PtrEnd->Checksum          = 0;

  *(VOID **) Configuration  = OldAcpiPtr;

  return EFI_SUCCESS;
}

