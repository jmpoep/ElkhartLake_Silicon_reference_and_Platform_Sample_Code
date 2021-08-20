/** @file
  Library producing LegacyBiosPlatformLib functionality.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2004 - 2017 Intel Corporation.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:
**/

#include <Base.h>
#include <Uefi.h>
#include <Guid/Acpi.h>
#include <IndustryStandard/Pci22.h>
#include <IndustryStandard/Acpi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/PciIo.h>
#include <Protocol/LegacyRegion2.h>
#include <Protocol/ScsiPassThruExt.h>
#include <Protocol/LegacyInterrupt.h>
#include <Library/LegacyBiosPlatformLib.h>
#include "VesaBiosExtensions.h"

#define FIRST_INSTANCE      1
#define NOT_FIRST_INSTANCE  0
#define EFI_FIELD_OFFSET(TYPE,Field) ((UINTN)(&(((TYPE *) 0)->Field)))

#ifndef ROM_MAX_ENTRIES
#define ROM_MAX_ENTRIES           24
#endif


//
// Structure comes from IntelFrameworkModulePkg/Csm/LegacyBiosDxe/LegacyBiosInterface.h
// PnP Expansion Header
//

#pragma pack(1)

typedef struct {
  UINT32  PnpSignature;
  UINT8   Revision;
  UINT8   Length;
  UINT16  NextHeader;
  UINT8   Reserved1;
  UINT8   Checksum;
  UINT32  DeviceId;
  UINT16  MfgPointer;
  UINT16  ProductNamePointer;
  UINT8   Class;
  UINT8   SubClass;
  UINT8   Interface;
  UINT8   DeviceIndicators;
  UINT16  Bcv;
  UINT16  DisconnectVector;
  UINT16  Bev;
  UINT16  Reserved2;
  UINT16  StaticResourceVector;
} LEGACY_PNP_EXPANSION_HEADER;

#pragma pack()

////////////////////////////////
// This section is generic function
////////////////////////////////

EFI_COMPATIBILITY16_TABLE *
EFIAPI
GetCompatibility16Table (
  VOID
  )
/*++

Routine Description:

  Search legacy region for compatibility16 table.

Arguments:

  None

Returns:

  EFI_COMPATIBILITY16_TABLE   - EFI_COMPATIBILITY16_TABLE is found
  NULL                        - EFI_COMPATIBILITY16_TABLE is not found

--*/
{
  UINT8                             *Ptr;
  EFI_COMPATIBILITY16_TABLE         *Table;

  //
  // Scan legacy region
  //
  for (Ptr = (UINT8 *)(UINTN)0xE0000; Ptr < (UINT8 *)(UINTN)(0x100000); Ptr += 0x10) {
    if (*(UINT32 *) Ptr == SIGNATURE_32 ('I', 'F', 'E', '$')) {
      Table   = (EFI_COMPATIBILITY16_TABLE *) Ptr;
      return Table;
    }
  }

  return NULL;
}

VOID *
EFIAPI
Compatibility16GetTableAddressFunc (
  IN UINT16  AllocationRegion,
  IN UINT16  Length,
  IN UINT16  Allignment,
  OUT UINT16 *Segment,
  OUT UINT16 *Offset
  )
{
  EFI_LEGACY_BIOS_PROTOCOL        *LegacyBios;
  EFI_COMPATIBILITY16_TABLE       *Compatibility16Table;
  EFI_STATUS                      Status;
  EFI_IA32_REGISTER_SET           Regs;

  Status = gBS->LocateProtocol (
                  &gEfiLegacyBiosProtocolGuid,
                  NULL,
                  (VOID **) &LegacyBios
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Locate Compatibility16 Table
  //
  Compatibility16Table = GetCompatibility16Table ();
  ASSERT (Compatibility16Table != NULL);

  if (Compatibility16Table == NULL) {
    return NULL;
  }

  ZeroMem (&Regs, sizeof (EFI_IA32_REGISTER_SET));
  Regs.X.AX = (UINT16) Legacy16GetTableAddress;
  Regs.X.BX = (UINT16) AllocationRegion;
  Regs.X.CX = (UINT16) Length;
  Regs.X.DX = (UINT16) Allignment;
  Status = LegacyBios->FarCall86 (
                         LegacyBios,
                         Compatibility16Table->Compatibility16CallSegment,
                         Compatibility16Table->Compatibility16CallOffset,
                         &Regs,
                         NULL,
                         0
                         );
  ASSERT_EFI_ERROR (Status);
  if (Regs.X.AX != 0) {
    DEBUG ((DEBUG_ERROR, "Compatibility16GetTableAddressFunc failed\n"));
    *Segment = 0;
    *Offset  = 0;
    return NULL;
  }
  *Segment = Regs.X.DS;
  *Offset  = Regs.X.BX;

  return (VOID *)(UINTN)((Regs.X.DS << 4) + Regs.X.BX);
}

EFI_STATUS
EFIAPI
FindAllDeviceTypes (
  IN  UINT8                 BaseCodeValue,
  IN  UINT8                 SubClassCodeValue,
  IN OUT DEVICE_STRUCTURE   *DeviceTable,
  IN OUT UINT16             *DeviceIndex,
  IN BOOLEAN                DeviceFlags
  )
/*++

  Routine Description:
    Return the handles and assorted information for the specified PCI
   Class code

  Arguments:
    BaseCodeValue - Base part of class code
    SubClassCodeValue - SubClass part of class code
    InterfaceCodeValue - Interface part of class code
    DeviceTable - Table to place handles etc in.
    DeviceIndex - Number of devices found
    DeviceFlags - Flags for ROM need. 0 require a valid legacy ROM; 1 require either no ROM or a valid legacy ROM

  Returns:
    EFI_SUCCESS   - One or more devices found
    EFI_NOT_FOUND - No device found

--*/
{
  UINTN                     HandleCount;
  EFI_HANDLE                *HandleBuffer;
  UINTN                     Index;
  UINTN                     StartIndex;
  PCI_TYPE00                PciConfigHeader;
  EFI_PCI_IO_PROTOCOL       *PciIo;
  EFI_LEGACY_BIOS_PROTOCOL  *LegacyBios;
  UINTN                     Flags;
  EFI_STATUS                Status;

  StartIndex = *DeviceIndex;
  Status = gBS->LocateProtocol (
                  &gEfiLegacyBiosProtocolGuid,
                  NULL,
                  (VOID **) &LegacyBios
                  );
  ASSERT_EFI_ERROR (Status);

  gBS->LocateHandleBuffer (
        ByProtocol,
        &gEfiPciIoProtocolGuid,
        NULL,
        &HandleCount,
        &HandleBuffer
        );
  for (Index = 0; Index < HandleCount; Index++) {
    gBS->HandleProtocol (
          HandleBuffer[Index],
          &gEfiPciIoProtocolGuid,
          (VOID **) &PciIo
          );
    PciIo->Pci.Read (
                PciIo,
                EfiPciIoWidthUint32,
                0,
                sizeof (PciConfigHeader) / sizeof (UINT32),
                &PciConfigHeader
                );
    if ((PciConfigHeader.Hdr.ClassCode[2] == BaseCodeValue) && (PciConfigHeader.Hdr.ClassCode[1] == SubClassCodeValue)) {
      DeviceTable->Handle = HandleBuffer[Index];
      LegacyBios->CheckPciRom (
                    LegacyBios,
                    HandleBuffer[Index],
                    NULL,
                    NULL,
                    &Flags
                    );
      //
      // Verify that results of OPROM check match request.
      // The two valid requests are:
      //   DeviceFlags = 0 require a valid legacy ROM
      //   DeviceFlags = 1 require either no ROM or a valid legacy ROM
      //
      if (((DeviceFlags != 0) && (Flags != ROM_FOUND)) ||
          ((DeviceFlags == 0) && (Flags == (ROM_FOUND | VALID_LEGACY_ROM)))
          ) {
        DeviceTable->Vid    = PciConfigHeader.Hdr.VendorId;
        DeviceTable->Did    = PciConfigHeader.Hdr.DeviceId;
        DeviceTable->SvId   = PciConfigHeader.Device.SubsystemVendorID;
        DeviceTable->SysId  = PciConfigHeader.Device.SubsystemID;
        ++ *DeviceIndex;
        DeviceTable++;
      }
    }
  }
  //
  // Free any allocated buffers
  //
  (gBS->FreePool) (HandleBuffer);

  if (*DeviceIndex != StartIndex) {
    return EFI_SUCCESS;
  } else {
    return EFI_NOT_FOUND;
  }
}

////////////////////////////////
// This section is for ACPI table in legacy region
////////////////////////////////

EFI_STATUS
AcpiPlatformChecksum (
  IN VOID       *Buffer,
  IN UINTN      Size,
  IN UINTN      ChecksumOffset
  )
/*++

Routine Description:

  This function calculates and updates an UINT8 checksum.

Arguments:

  Buffer          Pointer to buffer to checksum
  Size            Number of bytes to checksum
  ChecksumOffset  Offset to place the checksum result in

Returns:

  EFI_SUCCESS             The function completed successfully.

--*/
{
  UINT8 Sum;
  UINT8 *Ptr;

  Sum = 0;
  //
  // Initialize pointer
  //
  Ptr = Buffer;

  //
  // set checksum to 0 first
  //
  Ptr[ChecksumOffset] = 0;

  //
  // add all content of buffer
  //
  while (Size--) {
    Sum = (UINT8) (Sum + (*Ptr++));
  }
  //
  // set checksum
  //
  Ptr                 = Buffer;
  Ptr[ChecksumOffset] = (UINT8) (0xff - Sum + 1);

  return EFI_SUCCESS;
}

VOID
EFIAPI
PrepareAcpiInLegacyRegion (
  VOID
  )
{
  EFI_LEGACY_BIOS_PROTOCOL     *LegacyBios;
  EFI_LEGACY_REGION2_PROTOCOL  *LegacyRegion;
  UINT16                       *CopyBuffer;
  VOID                         *AcpiTable;
  EFI_STATUS                   Status;
  UINTN                        CopySize;
  EFI_COMPATIBILITY16_TABLE    *Compatibility16Table;
  UINT32                       *Granularity;

  AcpiTable = NULL;
  Status = EfiGetSystemConfigurationTable (
             &gEfiAcpi20TableGuid,
             &AcpiTable
             );
  if (EFI_ERROR (Status)) {
    Status = EfiGetSystemConfigurationTable (
               &gEfiAcpiTableGuid,
               &AcpiTable
               );
  }
  if (AcpiTable == NULL) {
    return;
  }

  Status = gBS->LocateProtocol (
                  &gEfiLegacyBiosProtocolGuid,
                  NULL,
                  (VOID **) &LegacyBios
                  );
  if (EFI_ERROR (Status)) {
    //
    // No CSM, do not need to handle it.
    //
    return;
  }

  Status = gBS->LocateProtocol (
                  &gEfiLegacyRegion2ProtocolGuid,
                  NULL,
                  (VOID **) &LegacyRegion
                  );
  if (EFI_ERROR (Status)) {
    return;
  }
  Compatibility16Table = GetCompatibility16Table ();
  ASSERT (Compatibility16Table != NULL);

  if (Compatibility16Table == NULL) {
    return;
  }
  gBS->AllocatePool (EfiBootServicesData, sizeof(UINT32), (VOID **) &Granularity);

  LegacyRegion->UnLock (
                  LegacyRegion,
                  0xE0000,
                  0x20000,
                  Granularity
                  );

  //
  // Copy to legacy region
  //
  CopyBuffer = (VOID *)(UINTN) Compatibility16Table->AcpiRsdPtrPointer;

  if (*((UINT8 *) AcpiTable + 15) == 0) {
    CopySize = 20;
    AcpiPlatformChecksum (
        AcpiTable,
        sizeof (EFI_ACPI_1_0_ROOT_SYSTEM_DESCRIPTION_POINTER),
        EFI_FIELD_OFFSET (EFI_ACPI_1_0_ROOT_SYSTEM_DESCRIPTION_POINTER, Checksum)
        );
  } else {
    CopySize  = (*(UINT32 *) ((UINT8 *) AcpiTable + 20));
    AcpiPlatformChecksum (
        AcpiTable,
        sizeof (EFI_ACPI_1_0_ROOT_SYSTEM_DESCRIPTION_POINTER),
        EFI_FIELD_OFFSET (EFI_ACPI_1_0_ROOT_SYSTEM_DESCRIPTION_POINTER, Checksum)
        );
    AcpiPlatformChecksum (
        AcpiTable,
        sizeof (EFI_ACPI_3_0_ROOT_SYSTEM_DESCRIPTION_POINTER),
        EFI_FIELD_OFFSET (EFI_ACPI_3_0_ROOT_SYSTEM_DESCRIPTION_POINTER, ExtendedChecksum)
        );
  }

  CopyMem (
      (VOID *)(UINTN)CopyBuffer,
      (VOID *)(UINTN)AcpiTable,
      CopySize
      );

  LegacyRegion->Lock (
                  LegacyRegion,
                  0xE0000,
                  0x20000,
                  Granularity
                  );

  gBS->FreePool (Granularity);

}

////////////////////////////////
// This section is for Set video text mode
////////////////////////////////

VOID
EFIAPI
PrepareToScanRomHookSetTextMode (
  VOID
  )
{
  EFI_IA32_REGISTER_SET         Regs;
  EFI_LEGACY_BIOS_PROTOCOL      *LegacyBios;
  EFI_STATUS                    Status;

  Status = gBS->LocateProtocol (
                  &gEfiLegacyBiosProtocolGuid,
                  NULL,
                  (VOID **) &LegacyBios
                  );
  ASSERT_EFI_ERROR (Status);

  ZeroMem (&Regs, sizeof (EFI_IA32_REGISTER_SET));

  //
  // Set the 80x25 Text VGA Mode
  //
  Regs.H.AH = 0x00;
  Regs.H.AL = 0x03;
  Status    = LegacyBios->Int86 (LegacyBios, 0x10, &Regs);

  return;
}

////////////////////////////////
// This section is for Video work-around
////////////////////////////////

BOOLEAN               mVideoModeSave = FALSE;
UINT16                mVideoMode    = 0xFFFF;

BOOLEAN
CheckVbeSupport (
  EFI_LEGACY_BIOS_PROTOCOL      *LegacyBios
  )
{
  EFI_IA32_REGISTER_SET                   Regs;
  EFI_STATUS                              Status;
  EFI_PHYSICAL_ADDRESS                    AddressBelow1MB;
  static BOOLEAN                          HasExecute    = FALSE;
  static BOOLEAN                          mVbeSupport   = FALSE;
  VESA_BIOS_EXTENSIONS_INFORMATION_BLOCK  *VbeInformationBlock;

  if (HasExecute) {
    return mVbeSupport;
  }

  //
  // Test to see if the Video Adapter is compliant with VBE 3.0
  //
  AddressBelow1MB = 0x00100000 - 1;
  Status = (gBS->AllocatePages) (
                  AllocateMaxAddress,
                  EfiBootServicesData,
                  EFI_SIZE_TO_PAGES (sizeof (VESA_BIOS_EXTENSIONS_INFORMATION_BLOCK)),
                  &AddressBelow1MB
                  );
  ASSERT_EFI_ERROR (Status);

  ZeroMem (&Regs, sizeof (EFI_IA32_REGISTER_SET));
  Regs.X.AX = VESA_BIOS_EXTENSIONS_RETURN_CONTROLLER_INFORMATION;
  VbeInformationBlock = (VESA_BIOS_EXTENSIONS_INFORMATION_BLOCK *)(UINTN)AddressBelow1MB;
  VbeInformationBlock->VESASignature  = VESA_BIOS_EXTENSIONS_VBE2_SIGNATURE;
  Regs.X.ES = EFI_SEGMENT ((UINTN) VbeInformationBlock);
  Regs.X.DI = EFI_OFFSET ((UINTN) VbeInformationBlock);

  LegacyBios->Int86 (LegacyBios, 0x10, &Regs);

  //
  // See if the VESA call succeeded
  //
  HasExecute = TRUE;
  if ((Regs.X.AX != VESA_BIOS_EXTENSIONS_STATUS_SUCCESS) ||
      (VbeInformationBlock->VESASignature != VESA_BIOS_EXTENSIONS_VESA_SIGNATURE) ||
      (VbeInformationBlock->VESAVersion < VESA_BIOS_EXTENSIONS_VERSION_2_0)) {
    mVbeSupport = FALSE;
  } else {
    mVbeSupport = TRUE;
  }

  (gBS->FreePages) (AddressBelow1MB, EFI_SIZE_TO_PAGES (sizeof (VESA_BIOS_EXTENSIONS_INFORMATION_BLOCK)));
  return mVbeSupport;
}

VOID
EFIAPI
PrepareToScanRomHookVideo (
  IN EFI_HANDLE  DeviceHandle,
  IN EFI_HANDLE  VgaHandle
  )
{
  EFI_IA32_REGISTER_SET         Regs;
  EFI_LEGACY_BIOS_PROTOCOL      *LegacyBios;
  EFI_STATUS                    Status;

  //
  // Save current VBE video mode before Oprom starts
  //
  mVideoModeSave = FALSE;
  if ((VgaHandle != NULL) && (DeviceHandle != VgaHandle)) {
    //
    // Get mode settings since PrepareToScanRom may change mode
    //
    Status = gBS->LocateProtocol (
                    &gEfiLegacyBiosProtocolGuid,
                    NULL,
                    (VOID **) &LegacyBios
                    );
    ASSERT_EFI_ERROR (Status);

    if (!CheckVbeSupport (LegacyBios)) {
      return;
    }

    ZeroMem (&Regs, sizeof (EFI_IA32_REGISTER_SET));

    Regs.X.AX = 0x4F03;
    LegacyBios->Int86 (LegacyBios, 0x10, &Regs);
    mVideoMode = (Regs.X.BX & 0x0CFFF);
    mVideoModeSave = TRUE;
  }
}

VOID
EFIAPI
AfterRomInitHookVideo (
  IN EFI_HANDLE  DeviceHandle,
  IN EFI_HANDLE  VgaHandle
  )
{
  EFI_IA32_REGISTER_SET         Regs;
  EFI_LEGACY_BIOS_PROTOCOL      *LegacyBios;
  EFI_STATUS                    Status;

  if (!mVideoModeSave) {
    return;
  }
  Status = gBS->LocateProtocol (
                  &gEfiLegacyBiosProtocolGuid,
                  NULL,
                  (VOID **) &LegacyBios
                  );
  ASSERT_EFI_ERROR (Status);

  ZeroMem (&Regs, sizeof (EFI_IA32_REGISTER_SET));

  //
  // Restore video mode after Oprom starts
  //
  Regs.X.AX = 0x4F02;
  Regs.X.BX = (mVideoMode & 0x01FF);
  LegacyBios->Int86 (LegacyBios, 0x10, &Regs);

  //
  // Indicate video mode has been restored.
  //
  mVideoModeSave = FALSE;
}

////////////////////////////////
// This section is for AHCI OPROM
////////////////////////////////

#define    EFI_AHCI_BAR_INDEX       5

typedef union {
  struct {
    UINT32  Lower32;
    UINT32  Upper32;
  } Uint32;
  UINT64    Uint64;
} DATA_64;

BOOLEAN  mNativeAhciDriver = FALSE;
EFI_PCI_IO_PROTOCOL                 *mAhciPciIo;
UINT64                              mAhciRFisOfNative[0x20];
UINT64                              mAhciCmdListOfNative[0x20];
UINT64                              mAhciRFisOfLegacyRom[0x20];
UINT64                              mAhciCmdListOfLegacyRom[0x20];

UINT32
EFIAPI
AhciReadReg (
  IN EFI_PCI_IO_PROTOCOL  *PciIo,
  IN  UINT32              Offset
  )
{
  UINT32                  Data;

  ASSERT (PciIo != NULL);

  Data = 0;
  PciIo->Mem.Read (
                   PciIo,
                   EfiPciIoWidthUint32,
                   EFI_AHCI_BAR_INDEX,
                   (UINT64) Offset,
                   1,
                   &Data
                   );

  return Data;
}

VOID
EFIAPI
AhciWriteReg (
  IN EFI_PCI_IO_PROTOCOL  *PciIo,
  IN UINT32               Offset,
  IN UINT32               Data
  )
{
  ASSERT (PciIo != NULL);

  PciIo->Mem.Write (
                    PciIo,
                    EfiPciIoWidthUint32,
                    EFI_AHCI_BAR_INDEX,
                    (UINT64) Offset,
                    1,
                    &Data
                    );

  return;
}

VOID
EFIAPI
PlatformHookInitAhciOprom (
  IN EFI_HANDLE  DeviceHandle
  )
{
  gBS->HandleProtocol (
         DeviceHandle,
         &gEfiPciIoProtocolGuid,
         (VOID **) &mAhciPciIo
         );
}

VOID
EFIAPI
PrepareToScanRomHookAhciOprom (
  IN EFI_HANDLE  DeviceHandle
  )
{
  EFI_STATUS                      Status;
  EFI_EXT_SCSI_PASS_THRU_PROTOCOL *PassThru;
  UINT32                          PortsImplemented;
  UINT8                           Port;
  UINT32                          Offset;
  DATA_64                         Data64;

  //
  // judge if there is a native ahci driver,
  // if yes, then save old setting of native ahci driver before loading the legacy ahci rom.
  //
  // The step is used to make native ahci and legacy ahci oprom can cowork
  // to support legacy & efi boot.
  //
  Status = gBS->HandleProtocol (
                  DeviceHandle,
                  &gEfiExtScsiPassThruProtocolGuid,
                  (VOID **) &PassThru
                  );
  if (!EFI_ERROR (Status)) {
    //
    // it means native ahci driver is existing. save the setting of command list and recevied fis.
    //
    mNativeAhciDriver = TRUE;
    PortsImplemented  = AhciReadReg (mAhciPciIo, 0xc);
    for (Port = 0; Port < 32; Port ++) {
      if ((PortsImplemented & (1 << Port)) == 0) {
        continue;
      }
      Offset = 0x100 + Port * 0x80 + 0x8;
      Data64.Uint32.Lower32 = AhciReadReg(mAhciPciIo, Offset);
      Offset = 0x100 + Port * 0x80 + 0xc;
      Data64.Uint32.Upper32 = AhciReadReg(mAhciPciIo, Offset);
      mAhciRFisOfNative[Port] = Data64.Uint64;
      Offset = 0x100 + Port * 0x80 + 0x0;
      Data64.Uint32.Lower32 = AhciReadReg(mAhciPciIo, Offset);
      Offset = 0x100 + Port * 0x80 + 0x4;
      Data64.Uint32.Upper32 = AhciReadReg(mAhciPciIo, Offset);
      mAhciCmdListOfNative[Port] = Data64.Uint64;
    }
  }
}

VOID
EFIAPI
AfterRomInitHookAhciOprom (
  IN EFI_HANDLE  DeviceHandle
  )
{
  UINT32                          PortsImplemented;
  UINT8                           Port;
  UINT32                          Offset;
  DATA_64                         Data64;

  //
  // After legacy ahci rom is loaded, saving legay ahci rom setting and
  // if a native ahci driver is existing, then should restore native setting
  // of commandlist and received fis.
  //
  // The step is used to make native ahci and legacy ahci oprom can cowork
  // to support legacy & efi boot.
  //
  PortsImplemented = AhciReadReg (mAhciPciIo, 0xc);
  for (Port = 0; Port < 32; Port ++) {
    if ((PortsImplemented & (1 << Port)) == 0) {
      continue;
    }
    Offset = 0x100 + Port * 0x80 + 0x8;
    Data64.Uint32.Lower32 = AhciReadReg(mAhciPciIo, Offset);
    Offset = 0x100 + Port * 0x80 + 0xc;
    Data64.Uint32.Upper32 = AhciReadReg(mAhciPciIo, Offset);
    mAhciRFisOfLegacyRom[Port] = Data64.Uint64;

    if (mNativeAhciDriver) {
      Data64.Uint64 = mAhciRFisOfNative[Port];
      AhciWriteReg (mAhciPciIo, Offset - 4, Data64.Uint32.Lower32);
      AhciWriteReg (mAhciPciIo, Offset, Data64.Uint32.Upper32);
    }

    Offset = 0x100 + Port * 0x80 + 0x0;
    Data64.Uint32.Lower32 = AhciReadReg(mAhciPciIo, Offset);
    Offset = 0x100 + Port * 0x80 + 0x4;
    Data64.Uint32.Upper32 = AhciReadReg(mAhciPciIo, Offset);
    mAhciCmdListOfLegacyRom[Port] = Data64.Uint64;

    if (mNativeAhciDriver) {
      Data64.Uint64 = mAhciCmdListOfNative[Port];
      AhciWriteReg (mAhciPciIo, Offset - 4, Data64.Uint32.Lower32);
      AhciWriteReg (mAhciPciIo, Offset, Data64.Uint32.Upper32);
    }
  }
}

VOID
EFIAPI
LegacyBootAhciOpromRestore (
  VOID
  )
{
  UINT32                 PortsImplemented;
  UINT8                  Port;
  UINT32                 Offset;
  DATA_64                Data64;

  //
  // restore legacy ahci rom setting before booting to legacy os.
  // it's because native ahci driver can not provide int13 service.
  // so we should restore to legacy ahci oprom setting.
  //
  PortsImplemented = AhciReadReg (mAhciPciIo, 0xc);
  for (Port = 0; Port < 32; Port ++) {
    if ((PortsImplemented & (1 << Port)) == 0) {
      continue;
    }
    Offset = 0x100 + Port * 0x80 + 0xc;

    Data64.Uint64 = mAhciRFisOfLegacyRom[Port];
    AhciWriteReg (mAhciPciIo, Offset - 4, Data64.Uint32.Lower32);
    AhciWriteReg (mAhciPciIo, Offset, Data64.Uint32.Upper32);

    Offset = 0x100 + Port * 0x80 + 0x4;
    Data64.Uint64 = mAhciCmdListOfLegacyRom[Port];
    AhciWriteReg (mAhciPciIo, Offset - 4, Data64.Uint32.Lower32);
    AhciWriteReg (mAhciPciIo, Offset, Data64.Uint32.Upper32);
  }
}

////////////////////////////////
// This section is for EBDA and BCV
////////////////////////////////

#define BDA_HDD_COUNT  0x75

typedef struct {
    UINT8   *Address;
    UINT8   *Data;
    UINT8   *RtData;
    UINT8   *RtDataAddr;
    UINT16  RtDataSize;
} SAVED_PCI_ROM;

typedef struct {
  UINT8   VectorNumber;
  UINT32  VectorBase;
} INTERRUPT_VECTOR_SAVE;

UINT16                              mEbdaSegOrg;
UINT8                               mEbdaSizeOrg;
UINT16                              mMemSizeOrg;
UINT8                               *mEbdaBackupAddress;

LEGACY_PNP_EXPANSION_HEADER         *mBasePnpPtr;
BOOLEAN                             mIsBcvDevice = FALSE;
UINT16                              mBbsRomSegment;

//
// The data below must be saved before calling any BCV and restored before real legacy boot happening.
//

//
// When Option ROM BCV is called. INT13, INT40, INT18, INT19, INT15, INT1A, INT8 vectors may be changed,
// so save them before calling BCV and restore them when PrepareToBoot happens.
//
INTERRUPT_VECTOR_SAVE               mInterruptVectorSave[] = {{0x13}, {0x40}, {0x18}, {0x19}, {0x15}, {0x1a}, {0x8}};
UINTN                               mTotalSavedInterrupt = sizeof (mInterruptVectorSave) / sizeof (INTERRUPT_VECTOR_SAVE);
//
// For OpROM, saved environment before calling BCV includes OPROM space and EBDA.
//
SAVED_PCI_ROM                       mSaveRomEntry[ROM_MAX_ENTRIES];
UINTN                               mSavedCount = 0;
//
// The flag indicates the original environment before calling BCV is saved only once,
// this original environment will be restored before real legacy boot happening.
//
BOOLEAN                             mEnvironmentSaved = FALSE;

EFI_STATUS
FindNextPnpExpansionHeader (
  IN BOOLEAN                           FirstHeader,
  IN OUT LEGACY_PNP_EXPANSION_HEADER   **PnpPtr
  )
{
  UINTN                       TempData;
  LEGACY_PNP_EXPANSION_HEADER *LocalPnpPtr;

  LocalPnpPtr = *PnpPtr;
  if (FirstHeader == FIRST_INSTANCE) {
    mBasePnpPtr     = LocalPnpPtr;
    mBbsRomSegment  = (UINT16) ((UINTN) mBasePnpPtr >> 4);
    //
    // Offset 0x1a gives offset to PnP expansion header for the first
    // instance, there after the structure gives the offset to the next
    // structure
    //
    LocalPnpPtr = (LEGACY_PNP_EXPANSION_HEADER *) ((UINT8 *) LocalPnpPtr + 0x1a);
    TempData    = (*((UINT16 *) LocalPnpPtr));
  } else {
    TempData = (UINT16) LocalPnpPtr->NextHeader;
  }

  LocalPnpPtr = (LEGACY_PNP_EXPANSION_HEADER *) (((UINT8 *) mBasePnpPtr + TempData));

  //
  // Search for PnP table in Shadowed ROM
  //
  *PnpPtr = LocalPnpPtr;
  if (*(UINT32 *) LocalPnpPtr == SIGNATURE_32 ('$', 'P', 'n', 'P')) {
    return EFI_SUCCESS;
  } else {
    return EFI_NOT_FOUND;
  }
}

VOID
SaveOprom (
  IN UINT8   *Rom,
  IN UINT8   *RtDataAddr,
  IN UINT16  RtDataSize
  )
{
  UINTN  RomSize;

  RomSize = ((EFI_LEGACY_EXPANSION_ROM_HEADER*)Rom)->Size512 << 9;

  if (RomSize == 0) {
    DEBUG ((DEBUG_ERROR, "SaveOprom - RomSize 0!\n"));
    return;
  }

  mSaveRomEntry[mSavedCount].Data = AllocateZeroPool(RomSize);
  CopyMem(mSaveRomEntry[mSavedCount].Data, Rom, RomSize);
  mSaveRomEntry[mSavedCount].Address = Rom;

  if (RtDataAddr == NULL || RtDataSize == 0) {
    DEBUG ((DEBUG_ERROR, "SaveOprom - RtDataAddr NULL or RtDataSize 0!\n"));
    return;
  }

  //
  // Save runtime data associated with this ROM
  //
  if (RtDataSize) {
    ASSERT(RtDataAddr); // if size is not zero, address must not be zero
    mSaveRomEntry[mSavedCount].RtDataAddr = RtDataAddr;
    mSaveRomEntry[mSavedCount].RtDataSize = RtDataSize;
    mSaveRomEntry[mSavedCount].RtData = AllocateZeroPool(RtDataSize);
    CopyMem(mSaveRomEntry[mSavedCount].RtData, RtDataAddr, RtDataSize);
  }

  mSavedCount++;  // Points to zero address/data now.

  return;
}

VOID
PrintForCallingBcv (
  VOID
)
{
  UINT32      *IvtAddress;
  UINTN       Index;

  //
  // Dump the interrupt vector and BDA which may be changed after calling BCV
  //
  IvtAddress = (UINT32 *) 0;
  for (Index = 0; Index < mTotalSavedInterrupt; Index++) {
    DEBUG ((DEBUG_INFO, "Interrupt[%02x] - 0x%x\n",
            mInterruptVectorSave[Index].VectorNumber, IvtAddress[mInterruptVectorSave[Index].VectorNumber]));
  }
  DEBUG ((DEBUG_INFO, "HddCount at BDA 0x475 = 0x%x\n", *(UINT8 *)(UINTN)(0x400 + BDA_HDD_COUNT)));
}

EFI_STATUS
CallBcvHookInt13 (
  IN  EFI_LEGACY_EXPANSION_ROM_HEADER   *RomStart,
  IN  UINT8                             *RtData,
  IN  UINT32                            RtDataSize
  )
{
  EFI_LEGACY_BIOS_PROTOCOL        *LegacyBios;
  EFI_COMPATIBILITY16_TABLE       *Compatibility16Table;
  VOID                            *RomEnd;
  EFI_LEGACY_EXPANSION_ROM_HEADER *PciPtr;
  LEGACY_PNP_EXPANSION_HEADER     *PnpPtr;
  BOOLEAN                         Instance;
  EFI_STATUS                      Status;
  EFI_IA32_REGISTER_SET           Regs;
  UINT32                          *IvtAddress;
  UINTN                           Index;

  Status = gBS->LocateProtocol (
                  &gEfiLegacyBiosProtocolGuid,
                  NULL,
                  (VOID **) &LegacyBios
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Locate Compatibility16 Table
  //
  Compatibility16Table = GetCompatibility16Table ();
  ASSERT (Compatibility16Table != NULL);

  if (Compatibility16Table == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  PnpPtr    = (LEGACY_PNP_EXPANSION_HEADER *) RomStart;
  PciPtr    = (EFI_LEGACY_EXPANSION_ROM_HEADER *) RomStart;

  RomEnd    = (VOID *) (PciPtr->Size512 * 512 + (UINTN) PciPtr);
  Instance  = FIRST_INSTANCE;

  //
  // Save the context before calling BCV in order to restore it during legacy boot
  //
  SaveOprom ((UINT8 *)RomStart, RtData, (UINT16)RtDataSize);

  while (TRUE) {
    Status    = FindNextPnpExpansionHeader (Instance, &PnpPtr);
    Instance  = NOT_FIRST_INSTANCE;
    if (EFI_ERROR (Status)) {
      break;
    }

    //
    // Have seen case where PXE base code have PnP expansion ROM
    // header but no Bcv or Bev vectors.
    //
    if (PnpPtr->Bcv != 0) {
      if (!mEnvironmentSaved) {
        //
        // Before calling BCV, we need save some environment for legacy boot later.
        //
        DEBUG ((DEBUG_INFO, "Before calling BCV...\n"));
        PrintForCallingBcv ();

        IvtAddress = (UINT32 *) 0;
        for (Index = 0; Index < mTotalSavedInterrupt; Index++) {
          mInterruptVectorSave[Index].VectorBase   = IvtAddress[mInterruptVectorSave[Index].VectorNumber];
        }

        //
        // Indicate environment has been saved.
        //
        mEnvironmentSaved = TRUE;
      }
      ZeroMem (&Regs, sizeof(Regs));
      Regs.X.ES = Compatibility16Table->PnPInstallationCheckSegment;
      Regs.X.DI = Compatibility16Table->PnPInstallationCheckOffset;
      Status = LegacyBios->FarCall86 (
                             LegacyBios,
                             mBbsRomSegment,
                             PnpPtr->Bcv,
                             &Regs,
                             NULL,
                             0
                             );
      if (EFI_ERROR (Status)) {
        return Status;
      }
    }

    if ((PnpPtr == (LEGACY_PNP_EXPANSION_HEADER *) PciPtr) || (PnpPtr > (LEGACY_PNP_EXPANSION_HEADER *) RomEnd)) {
      break;
    }
  }

  return EFI_SUCCESS;
}

VOID
UpdateEbdaMap (
  IN UINT32 AddrChange
  )
{
  UINTN         Index;

  DEBUG ((DEBUG_INFO, "UpdateEbdaMap!\n"));

  //
  // for every SAVED_PCI_ROM update ebdaAddr
  //
  for (Index = 0; Index < mSavedCount; Index++) {
    if (mSaveRomEntry[Index].RtDataAddr != NULL) {
      DEBUG ((DEBUG_INFO, "Original RtDataAddr = 0x%x\n", mSaveRomEntry[Index].RtDataAddr));
      mSaveRomEntry[Index].RtDataAddr -= AddrChange;
      DEBUG ((DEBUG_INFO, "New RtDataAddr = 0x%x\n", mSaveRomEntry[Index].RtDataAddr));
    }
  }
}

VOID
EFIAPI
PrepareToScanRomHookEbdaBcv (
  IN EFI_HANDLE  DeviceHandle
  )
{
  //
  // Save the current EBDA location to check if OpROM modifies it
  //
  mEbdaSegOrg = *(UINT16 *)(UINTN)0x40e;
  DEBUG ((DEBUG_INFO, "mEbdaSegOrg = 0x%x\n", mEbdaSegOrg));
  mEbdaSizeOrg = *(UINT8 *)((UINTN)mEbdaSegOrg << 4);
  DEBUG ((DEBUG_INFO, "mEbdaSizeOrg = 0x%x\n", mEbdaSizeOrg));
  ASSERT(mEbdaSizeOrg);

  //
  // Save the current base memory size (BDA offset 0x13) and EBDA data
  //
  mMemSizeOrg = *(UINT16 *)(UINTN)0x413;
  DEBUG ((DEBUG_INFO, "mMemSizeOrg = 0x%x\n", mMemSizeOrg));
  mEbdaBackupAddress = AllocateZeroPool(mEbdaSizeOrg * 0x400);
  CopyMem((VOID *)mEbdaBackupAddress, (VOID *)(UINTN)(mEbdaSegOrg << 4), mEbdaSizeOrg * 0x400);
}

VOID
EFIAPI
AfterRomInitHookEbdaBcv (
  IN EFI_HANDLE  DeviceHandle,
  IN OUT UINTN   *Shadowaddress
  )
{
  UINT16                        EbdaSegNew;
  UINT32                        RtDataSize;
  UINT8                         *RtData;
  UINTN                         RuntimeAddress;

  //
  // Validate runtime image of Option ROM
  //
  RuntimeAddress = *Shadowaddress;

  //
  // Update EBDA map
  //
  EbdaSegNew = *(UINT16*)(UINTN)0x40e;
  DEBUG ((DEBUG_INFO, "EbdaSegNew = 0x%x\n", EbdaSegNew));
  DEBUG ((DEBUG_INFO, "EbdaSegNew size = 0x%x\n", *(UINT8*)((UINTN)EbdaSegNew << 4)));
  ASSERT(EbdaSegNew <= mEbdaSegOrg);

  //
  // Reallocate EBDA memory if OpROM only modifies base memory size (BDA offset 0x13)
  //
  if ((mMemSizeOrg != *(UINT16 *)(UINTN)0x413) && (mEbdaSegOrg == EbdaSegNew)) {
    *(UINT16 *)(UINTN)0x413 -= mEbdaSizeOrg;
    *(UINT16 *)(UINTN)0x40e = (*(UINT16 *)(UINTN)0x413) << 6;
    EbdaSegNew = *(UINT16 *)(UINTN)0x40e;
    CopyMem((VOID *)(UINTN)(EbdaSegNew << 4), (VOID *)mEbdaBackupAddress, mEbdaSizeOrg * 0x400);
  }
    (gBS->FreePool) (mEbdaBackupAddress);

  RtDataSize = (UINT32)(mEbdaSegOrg - EbdaSegNew) << 4;  // #of bytes taken by this OpROM
  DEBUG ((DEBUG_INFO, "RtDataSize = 0x%x\n", RtDataSize));

  //
  // EBDA was allocated and used by new OPROM, update the EBDA address
  //
  RtData = NULL;
  if (RtDataSize) {
    UpdateEbdaMap (RtDataSize);
    RtData = (UINT8 *)(((UINTN)EbdaSegNew << 4) + ((UINTN)mEbdaSizeOrg << 10));
    DEBUG ((DEBUG_INFO, "RtData = 0x%x\n", RtData));
  }

  if ((((EFI_LEGACY_EXPANSION_ROM_HEADER*) RuntimeAddress)->Signature != 0xAA55) ||
      (((EFI_LEGACY_EXPANSION_ROM_HEADER*) RuntimeAddress)->Size512 == 0x00)) {
    //
    // If runtime image's signature and size is 0, it is not a valid runtime image.
    // Then we do not call BCV address.
    //
    return;
  }

  //
  // Call BCV to hook INT13 by OPROM
  //
  RuntimeAddress = *Shadowaddress;
  CallBcvHookInt13 (
    (EFI_LEGACY_EXPANSION_ROM_HEADER *) RuntimeAddress,
    RtData,
    RtDataSize
    );

  DEBUG ((DEBUG_INFO, "After calling BCV...\n"));
  PrintForCallingBcv ();
}

VOID
EFIAPI
PrepareToBootEbdaBcv (
  VOID
  )
{
  UINTN  Index;
  UINT32 *IvtAddress;

  //
  // Restore ENV (ROM space and EBDA) for RAID boot, move to legacy boot callback later
  //
  for (Index = 0; Index < mSavedCount; Index++) {
    CopyMem (
      mSaveRomEntry[Index].Address,
      mSaveRomEntry[Index].Data,
      ((EFI_LEGACY_EXPANSION_ROM_HEADER*)mSaveRomEntry[Index].Data)->Size512 * 0x200
      );

      if (mSaveRomEntry[Index].RtDataAddr) {
        CopyMem (
          mSaveRomEntry[Index].RtDataAddr,
          mSaveRomEntry[Index].RtData,
          mSaveRomEntry[Index].RtDataSize
          );
      }
  }

  //
  // Reset number of ATA drives to let CSM16 PrepareToBoot function connect the drives
  //
  *(UINT8 *)(UINTN)(0x400 + BDA_HDD_COUNT) = 0;

  //
  // Restore interrupt vector before legacy boot
  //
  IvtAddress = (UINT32 *) 0;
  if (mEnvironmentSaved) {
    for (Index = 0; Index < mTotalSavedInterrupt; Index++) {
      IvtAddress[mInterruptVectorSave[Index].VectorNumber] = mInterruptVectorSave[Index].VectorBase;
    }
  }

  DEBUG ((DEBUG_INFO, "After restore the environment...\n"));
  PrintForCallingBcv ();
}

////////////////////////////////
// This section is for TranslatePirq
////////////////////////////////

EFI_STATUS
EFIAPI
PlatformTranslatePirq (
  IN VOID                                         *PirqTable,
  IN EFI_LEGACY_IRQ_PRIORITY_TABLE_ENTRY          *IrqPriorityTable,
  IN UINTN                                        IrqPriorityEntryCount,
  IN UINTN                                        PciBus,
  IN UINTN                                        PciDevice,
  IN UINTN                                        PciFunction,
  IN OUT UINT8                                    *Pirq,
  OUT UINT8                                       *PciIrq
  )
{
  EFI_LEGACY_INTERRUPT_PROTOCOL *LegacyInterrupt;
  EFI_STATUS                    Status;
  UINTN                         Index;
  UINTN                         SubIndex;
  UINT8                         LocalPirq;
  UINT8                         PirqData;
  UINT8                         MatchData;
  UINTN                         RoutingTableEntries;
  EFI_LEGACY_IRQ_ROUTING_ENTRY  *IrqRoutingEntry;
  UINTN                         TableSize;

  Status = gBS->LocateProtocol (
                  &gEfiLegacyInterruptProtocolGuid,
                  NULL,
                  (VOID **) &LegacyInterrupt
                  );
  ASSERT_EFI_ERROR (Status);

  TableSize = ((EFI_LEGACY_PIRQ_TABLE_HEADER *)PirqTable)->TableSize;

  RoutingTableEntries = (TableSize - sizeof (EFI_LEGACY_PIRQ_TABLE_HEADER)) / sizeof (EFI_LEGACY_IRQ_ROUTING_ENTRY);
  IrqRoutingEntry = (EFI_LEGACY_IRQ_ROUTING_ENTRY *)((UINTN)PirqTable + sizeof(EFI_LEGACY_PIRQ_TABLE_HEADER));

  LocalPirq = (UINT8) (*Pirq);

  for (Index = 0; Index < RoutingTableEntries; Index++) {
    if ((IrqRoutingEntry[Index].Bus == PciBus) &&
        (IrqRoutingEntry[Index].Device == PciDevice)
        ) {
      LocalPirq = (UINT8) (IrqRoutingEntry[Index].PirqEntry[LocalPirq].Pirq & 0x0f);
      if (LocalPirq > 4) {
        LocalPirq -= 4;
      }

      LegacyInterrupt->ReadPirq (LegacyInterrupt, LocalPirq, &PirqData);
      MatchData = PCI_UNUSED;
      while (PirqData == 0) {
        for (SubIndex = 0; SubIndex < IrqPriorityEntryCount; SubIndex++) {
          if ((IrqPriorityTable[SubIndex].Used == MatchData) && (IrqPriorityTable[SubIndex].Irq != 0)) {
            PirqData                        = IrqPriorityTable[SubIndex].Irq;
            IrqPriorityTable[SubIndex].Used = PCI_USED;
            LegacyInterrupt->WritePirq (
                               LegacyInterrupt,
                               LocalPirq,
                               PirqData
                               );
            break;
          }
        }

        if (PirqData == 0) {
          //
          // No unused interrpts, so start reusing them.
          //
          MatchData = (UINT8) (~MatchData);
        }
      }

      *PciIrq = PirqData;
      *Pirq   = LocalPirq;
      return EFI_SUCCESS;
    }
  }
  return EFI_NOT_FOUND;
}
