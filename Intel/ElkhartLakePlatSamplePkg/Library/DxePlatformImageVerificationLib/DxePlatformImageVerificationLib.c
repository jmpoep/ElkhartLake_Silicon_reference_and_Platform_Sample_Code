/** @file
  Dxe Platform Image Verification Library

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2017 Intel Corporation.

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

#include <PiDxe.h>
#include <Protocol/PciIo.h>
#include <IndustryStandard/Pci30.h>

#include <Library/DebugLib.h>
#include <Library/DevicePathLib.h>
#include <Library/SecurityManagementLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

#include <SetupVariable.h>

/**
  Check if it is EFI OpRom image.

  @param[in]   File       This is a pointer to the device path of the file that is
                          being dispatched.

  @retval TRUE            It is EFI OpRom image.
  @retval FALSE           It is not EFI OpRom image.
**/
UINT32
IsEfiOpRomImage (
  IN  CONST EFI_DEVICE_PATH_PROTOCOL   *File
  )
{
  EFI_DEVICE_PATH_PROTOCOL          *TempDevicePath;

  TempDevicePath = (EFI_DEVICE_PATH_PROTOCOL *) File;
  while (!IsDevicePathEndType (TempDevicePath)) {
    if (DevicePathType (TempDevicePath) == MEDIA_DEVICE_PATH &&
          DevicePathSubType (TempDevicePath) == MEDIA_RELATIVE_OFFSET_RANGE_DP) {
      return TRUE;
    }
    TempDevicePath = NextDevicePathNode (TempDevicePath);
  }
  return FALSE;
}


/**
  Provide image verification service for platform policy control.

  @param[in]    AuthenticationStatus
                           This is the authentication status returned from the security
                           measurement services for the input file.
  @param[in]    File       This is a pointer to the device path of the file that is
                           being dispatched. This will optionally be used for logging.
  @param[in]    FileBuffer File buffer matches the input file device path.
  @param[in]    FileSize   Size of File buffer matches the input file device path.
  @param[in]    BootPolicy A boot policy that was used to call LoadImage() UEFI service.

  @retval EFI_SUCCESS            The file is not an EFI OpRom image.
  @retval EFI_ACCESS_DENIED      Prohibits to load the EFI VGA OpRom.

**/
EFI_STATUS
EFIAPI
DxePlatformImageVerificationHandler (
  IN  UINT32                           AuthenticationStatus,
  IN  CONST EFI_DEVICE_PATH_PROTOCOL   *File,
  IN  VOID                             *FileBuffer,
  IN  UINTN                            FileSize,
  IN  BOOLEAN                          BootPolicy
  )
{
  EFI_STATUS                    Status;
  EFI_HANDLE                    DeviceHandle;
  UINTN                         VariableSize;
  SETUP_DATA                    SetupData;
  PCI_TYPE00                    PciData;
  UINTN                         PciSegment;
  UINTN                         PciBusNumber;
  UINTN                         PciDeviceNumber;
  UINTN                         PciFunctionNumber;
  EFI_PCI_IO_PROTOCOL           *PciIo;
  EFI_DEVICE_PATH_PROTOCOL      *TempDevicePath;

  if (IsEfiOpRomImage (File) == FALSE) {
    return EFI_SUCCESS;
  }

  DeviceHandle   = NULL;
  TempDevicePath = (EFI_DEVICE_PATH_PROTOCOL *) File;
  Status = gBS->LocateDevicePath (
                  &gEfiPciIoProtocolGuid,
                  &TempDevicePath,
                  &DeviceHandle
                  );

  if (!EFI_ERROR (Status)) {
    Status = gBS->HandleProtocol (
                    DeviceHandle,
                    &gEfiPciIoProtocolGuid,
                    (VOID **) &PciIo
                    );

    if (!EFI_ERROR (Status)) {
      PciIo->GetLocation (PciIo, &PciSegment, &PciBusNumber, &PciDeviceNumber, &PciFunctionNumber);
      //
      // Skip bus 0, we only check external device.
      //
      if (PciBusNumber == 0) {
        return EFI_SUCCESS;
      }

      PciIo->Pci.Read (PciIo, EfiPciIoWidthUint32, 0, sizeof (PciData) / sizeof (UINT32), &PciData);
      DEBUG ((DEBUG_INFO, "[PlatImageVerification] PCI Bus/Device/Function - (%02x/%02x/%02x)\n", PciBusNumber, PciDeviceNumber, PciFunctionNumber));
      DEBUG ((DEBUG_INFO, "[PlatImageVerification] PCI ClassCode - 0x%02x, 0x%02x, 0x%02x\n", PciData.Hdr.ClassCode [0], PciData.Hdr.ClassCode [1], PciData.Hdr.ClassCode [2]));
      //
      // Check if it's a VGA device.
      //
      if (IS_PCI_VGA (&PciData) || IS_PCI_OLD_VGA (&PciData)) {
        VariableSize = sizeof (SETUP_DATA);
        Status = gRT->GetVariable (
                        L"Setup",
                        &gSetupVariableGuid,
                        NULL,
                        &VariableSize,
                        &SetupData
                        );
        if (!EFI_ERROR (Status) && (SetupData.OpRomPost == OPROM_LEGACY)) {
          DEBUG ((DEBUG_INFO, "[PlatImageVerification] Prohibits to load Efi Vga OpRom if OpRomPost is legacy.\n"));
          return EFI_ACCESS_DENIED;
        }
      }
    }
  }

  return EFI_SUCCESS;
}


/**
  Register platform image verification check handler.

  @param  ImageHandle   ImageHandle of the loaded driver.
  @param  SystemTable   Pointer to the EFI System Table.

  @retval EFI_SUCCESS   The handlers were registered successfully.
**/
EFI_STATUS
EFIAPI
DxePlatformImageVerificationLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  return RegisterSecurity2Handler (
           DxePlatformImageVerificationHandler,
           EFI_AUTH_OPERATION_VERIFY_IMAGE | EFI_AUTH_OPERATION_IMAGE_REQUIRED
           );
}

