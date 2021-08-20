/** @file
  Platform VTd Sample driver.

  Note: This module should only be used for dev/debug purposes.
        It MUST never be used for production builds.

  Copyright (c) 2018 - 2019, Intel Corporation. All rights reserved.<BR>

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

**/

#include <PiDxe.h>

#include <IndustryStandard/Vtd.h>
#include <Protocol/PlatformVtdPolicy.h>
#include <Protocol/PciIo.h>
#include <Protocol/DevicePath.h>

#include <Library/IoLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DevicePathLib.h>
#include <Library/PcdLib.h>

#include <IndustryStandard/DmaRemappingReportingTable.h>


#pragma pack(1)

typedef struct {
  EDKII_PLATFORM_VTD_EXCEPTION_DEVICE_INFO     ExceptionDeviceInfo;
  EDKII_PLATFORM_VTD_DEVICE_SCOPE              DeviceScope;
  EFI_ACPI_DMAR_PCI_PATH                       PciBridge;
} PLATFORM_EXCEPTION_DEVICE_SCOPE_STRUCT;

typedef struct {
  EDKII_PLATFORM_VTD_EXCEPTION_DEVICE_INFO     ExceptionDeviceInfo;
  EDKII_PLATFORM_VTD_PCI_DEVICE_ID             PciDeviceId;
} PLATFORM_EXCEPTION_PCI_DEVICE_ID_STRUCT;

#pragma pack()


/**
  Get the VTD SourceId from the device handler.
  This function is required for non PCI device handler.

  Pseudo-algo in Intel VTd driver:
    Status = PlatformGetVTdDeviceId ();
    if (EFI_ERROR(Status)) {
      if (DeviceHandle is PCI) {
        Get SourceId from Bus/Device/Function
      } else {
        return EFI_UNSUPPORTED
      }
    }
    Get VTd engine by Segment/Bus/Device/Function.

  @param[in]  This                  The protocol instance pointer.
  @param[in]  DeviceHandle          Device Identifier in UEFI.
  @param[out] DeviceInfo            DeviceInfo for indentify the VTd engine in ACPI Table
                                    and the VTd page entry.

  @retval EFI_SUCCESS           The VtdIndex and SourceId are returned.
  @retval EFI_INVALID_PARAMETER DeviceHandle is not a valid handler.
  @retval EFI_INVALID_PARAMETER DeviceInfo is NULL.
  @retval EFI_NOT_FOUND         The Segment or SourceId information is NOT found.
  @retval EFI_UNSUPPORTED       This function is not supported.

**/
EFI_STATUS
EFIAPI
PlatformVTdGetDeviceId (
  IN  EDKII_PLATFORM_VTD_POLICY_PROTOCOL       *This,
  IN  EFI_HANDLE                               DeviceHandle,
  OUT EDKII_PLATFORM_VTD_DEVICE_INFO           *DeviceInfo
  )
{
  EFI_PCI_IO_PROTOCOL       *PciIo;
  UINTN                     Seg;
  UINTN                     Bus;
  UINTN                     Dev;
  UINTN                     Func;
  EFI_STATUS                Status;

  DEBUG ((DEBUG_VERBOSE, "PlatformVTdGetDeviceId\n"));

  if (DeviceInfo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (DeviceHandle == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Handle PCI device
  //
  Status = gBS->HandleProtocol (DeviceHandle, &gEfiPciIoProtocolGuid, (VOID **)&PciIo);
  if (!EFI_ERROR(Status)) {
    Status = PciIo->GetLocation (PciIo, &Seg, &Bus, &Dev, &Func);
    if (EFI_ERROR(Status)) {
      return EFI_UNSUPPORTED;
    }
    DeviceInfo->Segment = (UINT16)Seg;
    DeviceInfo->SourceId.Bits.Bus = (UINT8)Bus;
    DeviceInfo->SourceId.Bits.Device = (UINT8)Dev;
    DeviceInfo->SourceId.Bits.Function = (UINT8)Func;

    return EFI_SUCCESS;
  }

  return EFI_NOT_FOUND;
}

/**
  Get a list of the exception devices.

  The VTd driver should always set ALLOW for the device in this list.

  @param[in]  This                  The protocol instance pointer.
  @param[out] DeviceInfoCount       The count of the list of DeviceInfo.
  @param[out] DeviceInfo            A callee allocated buffer to hold a list of DeviceInfo.
                                    Each DeviceInfo pointer points to EDKII_PLATFORM_VTD_EXCEPTION_DEVICE_INFO.

  @retval EFI_SUCCESS           The DeviceInfoCount and DeviceInfo are returned.
  @retval EFI_INVALID_PARAMETER DeviceInfoCount is NULL, or DeviceInfo is NULL.
  @retval EFI_UNSUPPORTED       This function is not supported.

**/
EFI_STATUS
EFIAPI
PlatformVTdGetExceptionDeviceList (
  IN  EDKII_PLATFORM_VTD_POLICY_PROTOCOL       *This,
  OUT UINTN                                    *DeviceInfoCount,
  OUT VOID                                     **DeviceInfo
  )
{
  DEBUG ((DEBUG_VERBOSE, "PlatformVTdGetExceptionDeviceList\n"));

  if (DeviceInfoCount == NULL || DeviceInfo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Sample codes for device scope based exception list.
  // Uncomment to take affect and comment the sample codes for PCI vendor id
  // based exception list.
  //
  /*
  *DeviceInfo = AllocateZeroPool (sizeof(mExceptionDeviceScopeList));
  if (*DeviceInfo == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  CopyMem (*DeviceInfo, mExceptionDeviceScopeList, sizeof(mExceptionDeviceScopeList));

  *DeviceInfoCount = ARRAY_SIZE(mExceptionDeviceScopeList);
  */

  //
  // Sample codes for PCI vendor id based exception list.
  // Uncomment to take affect and comment the sample codes for device scope
  // based exception list.
  //
  /*
  *DeviceInfo = AllocateZeroPool (sizeof(mExceptionPciDeviceIdList));
  if (*DeviceInfo == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  CopyMem (*DeviceInfo, mExceptionPciDeviceIdList, sizeof(mExceptionPciDeviceIdList));

  *DeviceInfoCount = ARRAY_SIZE(mExceptionPciDeviceIdList);
  */
  return EFI_UNSUPPORTED;
}

EDKII_PLATFORM_VTD_POLICY_PROTOCOL  mPlatformVTdSample = {
  EDKII_PLATFORM_VTD_POLICY_PROTOCOL_REVISION,
  PlatformVTdGetDeviceId,
  PlatformVTdGetExceptionDeviceList,
};

/**
  Platform VTd sample driver.

  @param[in]  ImageHandle  ImageHandle of the loaded driver
  @param[in]  SystemTable  Pointer to the System Table

  @retval  EFI_SUCCESS           The Protocol is installed.
  @retval  EFI_OUT_OF_RESOURCES  Not enough resources available to initialize driver.
  @retval  EFI_DEVICE_ERROR      A device error occurred attempting to initialize the driver.

**/
EFI_STATUS
EFIAPI
PlatformVTdSampleInitialize (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  //
  // ElkhartLake doesn't support exception list, this driver is mainly for debuging purpose
  // It could be removed after we make sure all Intel IPs support DMAr
  // Plus, since all the Intel IPs are PCI base, we don't use GetDeviceId() to return
  // the segment and the source-id information as well
  //
  EFI_STATUS  Status = EFI_UNSUPPORTED;
  return Status;
}
