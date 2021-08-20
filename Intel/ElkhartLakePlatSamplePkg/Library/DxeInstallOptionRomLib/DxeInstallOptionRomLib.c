/** @file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2018 Intel Corporation.

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

#include <Library/InstallOptionRomLib.h>

#include <Pi/PiFirmwareFile.h>

#include <Protocol/PciIo.h>
#include <Protocol/DiskInfo.h>
#include <Protocol/LegacyBios.h>

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DxeServicesLib.h>
#include <Library/PerformanceLib.h>
#include <Library/PchInfoLib.h>
#include <Library/SataLib.h>
#include <Library/GbeLib.h>

#include <Register/PchRegs.h>

#include <IndustryStandard/Atapi.h>
#include <IndustryStandard/Pci30.h>

#include <SetupVariable.h>

#define EFI_PCI_DEVICE_BUS_MASTER_DISABLE         (EFI_PCI_IO_ATTRIBUTE_BUS_MASTER)

//
// The structure for the light version of AHCI ROM
//
#define SATA_CONTROLLER_STRUC_SIGNATURE       0x41325324
#define SATA_CONTROLLER_STRUC_FIELDS_VALID    0xF

typedef enum {
  EfiAhciHdd,                  // HDD
  EfiAhciCdDvd,                // CDROM or DVD ROM
  EfiAhciOtherDevice           // Other device is unsupported yet
} EFI_AHCI_DEVICE_DETECT_TYPE;

#define  ATA_ATAPI_DEVICE_TYPE_MASK                 0x1F00
#define  ATA_ATAPI_DEVICE_ATAPI_REMOVEABLE_MASK     0x8080
#define  ATA_ATAPI_DEVICE_TYPE_CDR                  5
#define  ATA_ATAPI_DEVICE_TYPE(Sig) \
  (((UINT16) ((Sig) & ATA_ATAPI_DEVICE_TYPE_MASK)) >> 8)

//
// @note: Please be careful when you remove or insert any item from below struct.
//        Need to align the offset with AHCIOptionROM-Ver0.03.doc
//
#pragma pack(1)
typedef struct  {
  UINT32    Signature;            // Signature, ASCII string
  UINT8     Length;               // Structure length in bytes
  UINT8     Checksum;             // Checksum
  UINT8     Version;              // Version Number
  UINT8     bReserved;            // Reserved for future use
  UINT32    PtrSataController;    // SATA_CONTROLLER_STRUC address
  UINT32    Reserved;             // Reserved for future use
} S2A_INSTALLATION_STRUC;

typedef struct  {
  UINT32    PtrSataController;    // Next SATA_CONTROLLER_STRUC address
  UINT8     Attribute;            // Attribute
  UINT8     Bus;                  // Bus# of SATA controller
  UINT8     Device;               // Device# of SATA controller
  UINT8     Function;             // Function# of SATA controller
  UINT32    ImplementedPort;      // Implemented SATA Ports
  UINT32    DevicePresentOnPort;  // Device present on SATA Ports
  UINT32    DeviceTypeOnPort;     // Device Type on SATA Ports
  UINT32    PtrSataDevice;        // SATA_DEVICE_STRUC address
} SATA_CONTROLLER_STRUC;

typedef struct  {
  UINT32    PtrSataDevice;              // Next SATA_DEVICE_STRUC address
  UINT8     Attribute;                  // Attribute
  UINT8     Port;                       // SATA Port# (0-based) where device is present
  UINT8     IdentifyDeviceData[0x200];  // 512-bytes of identify device data
} SATA_DEVICE_STRUC;
#pragma pack()

typedef struct {
  BOOLEAN   Install;
  EFI_GUID  RomImageGuid;
} ADDITIONAL_ROM_TABLE;

typedef struct {
  UINT8                     ProgInterface;
  UINT8                     SubClassCode;
  UINT8                     BaseCode;
} SKIP_BUSMASTER_ENABLE_TABLE;

extern SETUP_DATA                    mSystemConfiguration;

GLOBAL_REMOVE_IF_UNREFERENCED ADDITIONAL_ROM_TABLE  mAdditionalRomTable[] = {
  {TRUE, {0}},   // PXEUNDI rom for both onboard NIC and external PCIE NIC
  {TRUE, {0}},   // AHCI rom for both SATA AHCI mode and RAID mode.
};

//
// ProgramInterface, Sub-Class Code, BaseClass.
//
GLOBAL_REMOVE_IF_UNREFERENCED SKIP_BUSMASTER_ENABLE_TABLE  mSkipBusMasterEnable[] = {
  {0x00, 0x00, 0x0C },   // IEEE 1394 (FireWire).
  {0x10, 0x00, 0x0C },   // IEEE 1394 following the 1394 OpenHCI Specification.
  {0x00, 0x05, 0x06 },   // PCMCIA Bridge.
  {0x00, 0x07, 0x06 },   // CardBus Bridge.
};


GLOBAL_REMOVE_IF_UNREFERENCED UINT32      mSataControllerAddress = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINTN       mDiskInfoHandleCount   = 0;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_HANDLE  *mDiskInfoHandleBuffer = NULL;

BOOLEAN
IsDeviceIdSupportedInOprom (
  IN VOID                          *Rom,
  IN UINTN                         RomSize,
  IN UINT16                        DeviceId
  )
{
  UINT16                  *DeviceIdList;
  EFI_PCI_ROM_HEADER      RomHeader;
  PCI_3_0_DATA_STRUCTURE  *Pcir;

  RomHeader.Raw = Rom;
  if (RomHeader.Generic->Signature != PCI_EXPANSION_ROM_HEADER_SIGNATURE) {
    return FALSE;
  }
  Pcir = (PCI_3_0_DATA_STRUCTURE *) (RomHeader.Raw + RomHeader.Generic->PcirOffset);
  if (Pcir->CodeType != PCI_CODE_TYPE_PCAT_IMAGE) {
    return FALSE;
  }
  if (Pcir->DeviceId == DeviceId) {
    // Match
    return TRUE;
  }
  if ((Pcir->Revision >= 3) && (Pcir->DeviceListOffset != 0)) {
    DeviceIdList = (UINT16 *)(((UINT8 *) Pcir) + Pcir->DeviceListOffset);
    //
    // Checking the device list
    //
    while (*DeviceIdList != 0) {
      if (*DeviceIdList == DeviceId) {
        // Match
        return TRUE;
      }
      DeviceIdList ++;
    }
  }

  return FALSE;
}

UINT8
AhciDetectDeviceType (
  IN UINT16 GeneralConfigData
  )
{
  if ((GeneralConfigData & ATA_ATAPI_DEVICE_ATAPI_REMOVEABLE_MASK) == 0) {
    return EfiAhciHdd;
  }
  if ((GeneralConfigData & ATA_ATAPI_DEVICE_ATAPI_REMOVEABLE_MASK) == ATA_ATAPI_DEVICE_ATAPI_REMOVEABLE_MASK) {
    if (ATA_ATAPI_DEVICE_TYPE (GeneralConfigData) == ATA_ATAPI_DEVICE_TYPE_CDR) {
      return EfiAhciCdDvd;
    }
  }
  return EfiAhciOtherDevice;
}

/**
  Allocate memory below 4G memory address.

  @param[in]  MemoryType   Memory type of memory to allocate.
  @param[in]  Size         Size of memory to allocate.
  @param[out] Buffer       Allocated address for output.

  @retval     EFI_SUCCESS  Memory successfully allocated.
  @retval     Other        Other errors occur.

**/
EFI_STATUS
AllocateMemoryBelow4G (
  IN   EFI_MEMORY_TYPE MemoryType,
  IN   UINTN           Size,
  OUT  VOID            **Buffer
  )
{
  UINTN                 Pages;
  EFI_PHYSICAL_ADDRESS  Address;
  EFI_STATUS            Status;

  Pages = EFI_SIZE_TO_PAGES (Size);

  Address = 0xffffffff;
  Status  = gBS->AllocatePages (
                   AllocateMaxAddress,
                   MemoryType,
                   Pages,
                   &Address
                   );
  if (Status != EFI_SUCCESS) {
    return Status;
  }

  *Buffer = (VOID *) (UINTN) Address;

  if (Address != 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_OUT_OF_RESOURCES;
  }
}

//
// SATA controller and device drivers have started fully
// We can collect the information of controller and devices and pass it to light version of AHCI ROM
//
EFI_STATUS
FillSataControllerInfo (
  VOID
  )
{
  SATA_CONTROLLER_STRUC     *SataControllerAddress;
  SATA_DEVICE_STRUC         *SataDeviceAddress;
  EFI_DISK_INFO_PROTOCOL    *DiskInfo;
  UINT32                    BufferSize;
  ATA_IDENTIFY_DATA         *IdentifyDriveInfo;
  UINT32                    IdeChannel;
  UINT32                    IdeDevice;
  UINTN                     Index;
  UINTN                     DeviceCount;
  UINT8                     DeviceType;
  UINT32                    DeviceAddress;
  EFI_STATUS                Status;
  UINTN                     Step;

  DEBUG ((DEBUG_INFO, "Fill Sata ControllerInfo for light version of AHCI ROM!\n"));

  SataControllerAddress = NULL;
  SataDeviceAddress     = NULL;
  IdentifyDriveInfo     = NULL;
  DeviceCount           = 0;

  if (mDiskInfoHandleCount == 0) {
    return EFI_UNSUPPORTED;
  }

  DEBUG ((DEBUG_INFO, "There is %d devices managed by AHCI ROM on SATA controller\n", mDiskInfoHandleCount));

  //
  // Per light version of AHCI ROM spec, SATA_CONTROLLER_STRUC should be below 4GB
  //
  Status = AllocateMemoryBelow4G (EfiReservedMemoryType, sizeof (SATA_CONTROLLER_STRUC), (VOID **) &SataControllerAddress);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  ZeroMem (SataControllerAddress, sizeof (SATA_CONTROLLER_STRUC));

  SataControllerAddress->PtrSataController   = 0x0;
  SataControllerAddress->Attribute           = SATA_CONTROLLER_STRUC_FIELDS_VALID;
  SataControllerAddress->Bus                 = DEFAULT_PCI_BUS_NUMBER_PCH;
  SataControllerAddress->Device              = SataDevNumber (SATA_1_CONTROLLER_INDEX);
  SataControllerAddress->Function            = SataFuncNumber (SATA_1_CONTROLLER_INDEX);
  SataControllerAddress->ImplementedPort     = ((1 << MaxSataPortNum (SATA_1_CONTROLLER_INDEX)) -1);

  //
  // Fill device information from DiskInfo to the AHCI structure
  //
  for (Index = 0; Index < mDiskInfoHandleCount; Index++) {
    Status = gBS->HandleProtocol (mDiskInfoHandleBuffer[Index], &gEfiDiskInfoProtocolGuid, (VOID **) &DiskInfo);
    ASSERT_EFI_ERROR (Status);

    BufferSize = sizeof (ATA_IDENTIFY_DATA);
    IdentifyDriveInfo = AllocateZeroPool (BufferSize);
    ASSERT (IdentifyDriveInfo != NULL);
    if (IdentifyDriveInfo == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    Status = DiskInfo->Identify (
                        DiskInfo,
                        IdentifyDriveInfo,
                        &BufferSize
                        );
    if (EFI_ERROR (Status) || ((IdentifyDriveInfo->security_status & BIT2) != 0)) {
      continue;
    }

    Status = DiskInfo->WhichIde (
                        DiskInfo,
                        &IdeChannel,
                        &IdeDevice
                        );
    if (EFI_ERROR (Status)) {
      continue;
    }

    //
    //  The Port Number of device
    //
    SataControllerAddress->DevicePresentOnPort |= 1 << IdeChannel;
    DEBUG ((DEBUG_INFO, "SataControllerAddress->DevicePresentOnPort = %d\n", SataControllerAddress->DevicePresentOnPort));

    //
    // Device type on Port: 0: ATA 1: ATAPI
    //
    DeviceType = AhciDetectDeviceType (IdentifyDriveInfo->config);
    if (DeviceType == EfiAhciHdd || DeviceType == EfiAhciCdDvd) {
      SataControllerAddress->DeviceTypeOnPort |= DeviceType << IdeChannel;
      DEBUG ((DEBUG_INFO, "SataControllerAddress->DeviceTypeOnPort = %d\n", SataControllerAddress->DeviceTypeOnPort));
    } else {
      //
      // This device can not be handled by AHCI ROM, skip
      //
      DEBUG ((DEBUG_ERROR, "WARNING: This device can not be handled by AHCI ROM, skip!\n"));
      continue;
    }

    //
    // Per light version of AHCI ROM spec, SATA_DEVICE_STRUC should be below 4GB
    //
    Status = AllocateMemoryBelow4G (EfiReservedMemoryType, sizeof (SATA_DEVICE_STRUC), (VOID **) &SataDeviceAddress);
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status)) {
      FreePages (SataDeviceAddress, EFI_SIZE_TO_PAGES (sizeof (SATA_DEVICE_STRUC)));
      FreePool(IdentifyDriveInfo);
      return Status;
    }

    ZeroMem (SataDeviceAddress, sizeof (SATA_DEVICE_STRUC));

    if (DeviceCount == 0) {
      SataControllerAddress->PtrSataDevice = (UINT32)(UINTN)SataDeviceAddress; // Device address
    } else {
      //
      // Find the last filled SATA device
      //
      Step = 0;
      DeviceAddress = SataControllerAddress->PtrSataDevice;
      while (Step < DeviceCount - 1) {
        DeviceAddress = ((SATA_DEVICE_STRUC *) (UINTN) DeviceAddress)->PtrSataDevice;
        Step++;
      }
      ASSERT (((SATA_DEVICE_STRUC *) (UINTN)DeviceAddress)->PtrSataDevice == 0x0);
      ((SATA_DEVICE_STRUC *) (UINTN) DeviceAddress)->PtrSataDevice = (UINT32)(UINTN)SataDeviceAddress;
    }

    //
    // Fill in controller and device information
    //
    SataDeviceAddress->PtrSataDevice      = 0x0;                 // Next device address
    SataDeviceAddress->Attribute          = 0x3;                 // 1. valid bit fields. 2. Reset not required before accessing the device
    SataDeviceAddress->Port               = (UINT8) IdeChannel;  // Port number
    CopyMem (SataDeviceAddress->IdentifyDeviceData, IdentifyDriveInfo, 0x200); // 512-bytes of identify Index

    DeviceCount++;
    FreePool(IdentifyDriveInfo);
  }

  //
  // Prepare Sata controller structure address for the light version of AHCI ROM
  //
  mSataControllerAddress = (UINT32)(UINTN)SataControllerAddress;
  return EFI_SUCCESS;
}

/**
  Install Additional Option Rom

  @param[in]  InstallPxeRom       If FALSE, Disable PXE ROM dispatch

**/
VOID
InstallAdditionalOpRom (
  BOOLEAN InstallPxeRom
  )
{
  EFI_LEGACY_BIOS_PROTOCOL      *LegacyBios;
  EFI_STATUS                    Status;
  UINTN                         PciIoHandleCount;
  EFI_HANDLE                    *PciIoHandleBuffer;
  UINTN                         Index;
  UINTN                         TableIndex;
  UINTN                         Flags;
  VOID                          *LocalRomImage;
  UINTN                         LocalRomSize;
  EFI_PCI_IO_PROTOCOL           *PciIo;
  UINT16                        VendorId;
  UINT16                        DeviceId;
  EFI_HANDLE                    PciHandle;
  UINT8                         *Rom;
  UINTN                         PciSegment;
  UINTN                         PciBusNumber;
  UINTN                         PciDeviceNumber;
  UINTN                         PciFunctionNumber;
  UINTN                         AhciRomIndex;
  BOOLEAN                       AhciRomExist;
  UINT8                         ClassCode[3];
  PCH_SETUP                     PchSetup;
  UINTN                         VariableSize;

  PciHandle = NULL;
  LocalRomImage = NULL;
  LocalRomSize  = 0;
  PciIoHandleCount = 0;

  Status = gBS->LocateProtocol (
                   &gEfiLegacyBiosProtocolGuid,
                   NULL,
                   (VOID **) &LegacyBios
                   );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "Legacy Bios Not found! Skip InstallAdditionalOpRom\n"));
    return ;
  }
  //
  // Initlize Additional RomTable
  //
  mAdditionalRomTable[0].RomImageGuid = gPxeOptionRomFileGuid;
  mAdditionalRomTable[1].RomImageGuid = gAhciOptionRomFileGuid;
  //
  // When PXE is disabled, we will not install PXE ROM for onboard NIC.
  //
  if (!InstallPxeRom) {
    for (TableIndex = 0; TableIndex < sizeof (mAdditionalRomTable) / sizeof (mAdditionalRomTable[0]); TableIndex++) {
      if (CompareGuid (&(mAdditionalRomTable[TableIndex].RomImageGuid), &gPxeOptionRomFileGuid)) {
        //
        // Set PXE ROM to be not install state
        //
        DEBUG ((DEBUG_ERROR, "Disable PXE ROM dispatch!\n"));
        mAdditionalRomTable[TableIndex].Install = FALSE;
        break;
      }
    }
  }

  //
  // Find AHCI OpROM
  //
  AhciRomIndex = 0;
  AhciRomExist = FALSE;
  for (TableIndex = 0; TableIndex < sizeof (mAdditionalRomTable) / sizeof (mAdditionalRomTable[0]); TableIndex++) {
    if (CompareGuid (&(mAdditionalRomTable[TableIndex].RomImageGuid), &gAhciOptionRomFileGuid)) {
      AhciRomIndex = TableIndex;
      AhciRomExist = TRUE;
      break;
    }
  }

  //
  // By locating DiskInfo protocol to identify whether there are HDDs or CDROMs inserted,
  // if there is no DiskInfo protocol found, skip dispatching AHCI OPROM.
  // Note: The code can't control thunk driver to dispatch OPROM
  // for RAID HDD and external mass storage card.
  //
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiDiskInfoProtocolGuid,
                  NULL,
                  &mDiskInfoHandleCount,
                  &mDiskInfoHandleBuffer
                  );
  if ((AhciRomExist) && (Status == EFI_NOT_FOUND)) {
    DEBUG ((DEBUG_INFO, "No DiskInfo protocol is found, do not install AHCI ROM.\n"));
    mAdditionalRomTable[AhciRomIndex].Install = FALSE;
  }

  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiPciIoProtocolGuid,
                  NULL,
                  &PciIoHandleCount,
                  &PciIoHandleBuffer
                  );
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (PCH_SETUP);
  Status = gRT->GetVariable (
                  L"PchSetup",
                  &gPchSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &PchSetup
                  );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return ;
  }

  for (Index = 0; Index < PciIoHandleCount; Index++) {
    Status = gBS->HandleProtocol (
                    PciIoHandleBuffer[Index],
                    &gEfiPciIoProtocolGuid,
                    (VOID **) &PciIo
                    );
    if (EFI_ERROR (Status)) {
      continue;
    }

    PciIo->GetLocation (PciIo, &PciSegment, &PciBusNumber, &PciDeviceNumber, &PciFunctionNumber);

    PciIo->Pci.Read (PciIo, EfiPciIoWidthUint16, PCI_VENDOR_ID_OFFSET, 1, &VendorId);
    PciIo->Pci.Read (PciIo, EfiPciIoWidthUint16, PCI_DEVICE_ID_OFFSET, 1, &DeviceId);
    PciIo->Pci.Read (PciIo, EfiPciIoWidthUint8,  PCI_CLASSCODE_OFFSET, sizeof(ClassCode), &ClassCode[0]);

    PciHandle = NULL;
    LocalRomImage = NULL;
    LocalRomSize  = 0;

    if(!PchSetup.ExternalDma) {
      for (TableIndex = 0; TableIndex < sizeof(mSkipBusMasterEnable)/sizeof(mSkipBusMasterEnable[0]); TableIndex++) {
        if (ClassCode[0] == mSkipBusMasterEnable[TableIndex].ProgInterface &&
            ClassCode[1] == mSkipBusMasterEnable[TableIndex].SubClassCode &&
            ClassCode[2] == mSkipBusMasterEnable[TableIndex].BaseCode) {

          Status = PciIo->Attributes (
                            PciIo,
                            EfiPciIoAttributeOperationDisable,
                            EFI_PCI_DEVICE_BUS_MASTER_DISABLE,
                            NULL
                            );
          DEBUG ((DEBUG_INFO, "\nDMA Disabled on the Device: B%x: D%x: F%x: \t", PciBusNumber, PciDeviceNumber, PciFunctionNumber));
        }
      }
    }

    for (TableIndex = 0; TableIndex < sizeof(mAdditionalRomTable)/sizeof(mAdditionalRomTable[0]); TableIndex++) {
      //
      // Check the supported SATA device on this platform.
      //
      if ((VendorId == V_PCH_INTEL_VENDOR_ID) &&
          (IsSataAhciDid (DeviceId) ||
           IsSataRaidDid (DeviceId))) {

          //
          // Find and load AHCI OpROM
          //
          if ((AhciRomExist) && (mAdditionalRomTable[AhciRomIndex].Install)) {
            Status = GetSectionFromAnyFv (
                       &mAdditionalRomTable[AhciRomIndex].RomImageGuid,
                       EFI_SECTION_RAW,
                       0,
                       &LocalRomImage,
                       &LocalRomSize
                       );
            if (!EFI_ERROR (Status)) {
              PciHandle = PciIoHandleBuffer[Index];
              break;
            }
          }
      } else {

        if (ClassCode[2] == PCI_CLASS_NETWORK) {
          //
          // Check if the external PCIE NIC has OPROM or no. If has, will prioritize to use it.
          //
          if ((PciIo->RomImage != NULL) && (PciIo->RomSize != 0)) {
            LocalRomImage = PciIo->RomImage;
            LocalRomSize  = (UINTN) PciIo->RomSize;
            PciHandle     = PciIoHandleBuffer[Index];
            break;
          }
          //
          // If has no, we don't load OPROM from BIOS.
          //
          PciIo->GetLocation (PciIo, &PciSegment, &PciBusNumber, &PciDeviceNumber, &PciFunctionNumber);
          if ((PciBusNumber != DEFAULT_PCI_BUS_NUMBER_PCH) ||
              (PciDeviceNumber != GbeDevNumber ()) ||
              (PciFunctionNumber != GbeFuncNumber ())) {
            break;
          }
        }

        //
        // Need read OPROM and check DeviceId in image.
        //
        if (mAdditionalRomTable[TableIndex].Install) {
          Status = GetSectionFromAnyFv (
                     &mAdditionalRomTable[TableIndex].RomImageGuid,
                     EFI_SECTION_RAW,
                     0,
                     &LocalRomImage,
                     &LocalRomSize
                     );
          if ((!EFI_ERROR (Status)) && (LocalRomImage != NULL) && (LocalRomSize != 0)) {
            if (IsDeviceIdSupportedInOprom(LocalRomImage, LocalRomSize, DeviceId)) {
              PciHandle = PciIoHandleBuffer[Index];
              break;
            } else {
              FreePool (LocalRomImage);
              LocalRomImage = NULL;
              LocalRomSize  = 0;
            }
          }
        }
      }
    }

    //
    // Device not match with OpROM, go to next PCI device
    //
    if (PciHandle == NULL) {
      continue;
    }

    ASSERT ((LocalRomImage != NULL) && (LocalRomSize != 0));

    //
    // Find and patch the light version of AHCI ROM
    //
    if ((PciBusNumber == DEFAULT_PCI_BUS_NUMBER_PCH) &&
        (PciDeviceNumber == SataDevNumber (0)) &&
        (PciFunctionNumber == SataFuncNumber (0))) {
      //
      // Search $S2A signature
      //
      for (Rom = (UINT8 *)(UINTN)LocalRomImage; Rom < (UINT8 *)(UINTN)LocalRomImage + LocalRomSize; Rom++) {
        if (*(UINT32 *)Rom == SATA_CONTROLLER_STRUC_SIGNATURE) {
          DEBUG ((DEBUG_INFO, "Find the light version of AHCI ROM!\n"));
          Status = FillSataControllerInfo ();
          if (!EFI_ERROR (Status)) {
            //
            // Update SATA controller address
            //
            ((S2A_INSTALLATION_STRUC *)Rom)->PtrSataController = mSataControllerAddress;

            //
            // First clear default checksum value in AHCI OpROM and recalculate next
            //
            ((S2A_INSTALLATION_STRUC *)Rom)->Checksum = 0;
            //
            // Update new checksum to AHCI OpROM
            //
            ((S2A_INSTALLATION_STRUC *)Rom)->Checksum = CalculateCheckSum8 (Rom, ((S2A_INSTALLATION_STRUC *)Rom)->Length);
            break;
          }
        }
      }
    }

    if (LocalRomImage != NULL && LocalRomSize != 0) {
      DEBUG ((DEBUG_INFO,"OPROM will be installed, TableIndex = 0x%x, VendorId = 0x%04x, DeviceId = 0x%04x, (0x%x-0x%x)\n",
              TableIndex,  (UINTN)VendorId, (UINTN)DeviceId,
              LocalRomImage, LocalRomSize));

      if ((VendorId == V_PCH_INTEL_VENDOR_ID) &&
          (IsSataAhciDid (DeviceId) ||
           IsSataRaidDid (DeviceId))) {

        PERF_START (NULL, "PlatformBds", "Install AHCI OpRom", 0);
      }
      Status = LegacyBios->InstallPciRom (
                             LegacyBios,
                             PciHandle,
                             &LocalRomImage,
                             &Flags,
                             NULL,
                             NULL,
                             NULL,
                             NULL
                             );

      if ((VendorId == V_PCH_INTEL_VENDOR_ID) &&
          (IsSataAhciDid (DeviceId) ||
           IsSataRaidDid (DeviceId))) {

        PERF_END (NULL, "PlatformBds", "Install AHCI OpRom", 0);
        gBS->InstallProtocolInterface (
               &PciHandle,
               &gEfiHddPasswordNotifyProtocolGuid,
               EFI_NATIVE_INTERFACE,
               NULL
               );
      }
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "OPROM is failed to be installed\n"));
        continue;
      }
    }
  }

  if (mDiskInfoHandleCount != 0) {
    FreePool (mDiskInfoHandleBuffer);
  }
  FreePool (PciIoHandleBuffer);

  return;
}

/**
  Install Additional External Option Rom

  @param[in]  InstallStorageRom     If FALSE, Do not dispatch it
  @param[in]  InstallOtherRom       If FALSE, Do not dispatch it

**/
VOID
InstallAdditionalExternalOpRom (
  IN BOOLEAN InstallStorageRom,
  IN BOOLEAN InstallOtherRom
  )
{
  EFI_STATUS                       Status;
  UINTN                            HandleCount;
  EFI_HANDLE                       *HandleBuffer;
  UINTN                            Index;
  UINT16                           VendorId;
  UINT16                           DeviceId;
  UINTN                            Flags;
  UINT8                            ClassCode[3];
  EFI_PCI_IO_PROTOCOL              *PciIo;
  UINTN                            Seg;
  UINTN                            Bus;
  UINTN                            Dev;
  UINTN                            Func;
  EFI_LEGACY_BIOS_PROTOCOL         *LegacyBios;
  UINT8                            DiskStart;
  UINT8                            DiskEnd;
  BOOLEAN                          IsStorageOrom;

  DEBUG ((DEBUG_INFO, "InstallAdditionalExternalOpRom ...\n"));
  if((mSystemConfiguration.DiscreteTbtSupport || mSystemConfiguration.IntegratedTbtSupport)
     && mSystemConfiguration.TbtSkipPciOprom) {
    DEBUG ((DEBUG_ERROR, "Skip Any AdditionalExternalOpRoms for Thunderbolt(TM) Devices.\n"));
    return ;
  }

  Status = gBS->LocateProtocol (
                  &gEfiLegacyBiosProtocolGuid,
                  NULL,
                  (VOID **) &LegacyBios
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "Legacy Bios Not found! Skip\n"));
    return ;
  }

  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiPciIoProtocolGuid,
                  NULL,
                  &HandleCount,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status)) {
    return ;
  }

  for (Index = 0; Index < HandleCount; Index++) {
    Status = gBS->HandleProtocol (
                    HandleBuffer[Index],
                    &gEfiPciIoProtocolGuid,
                    (VOID **) &PciIo
                    );
    if (EFI_ERROR (Status)) {
      continue;
    }

    //
    // Check if we have oprom
    //
    if ((PciIo->RomImage == NULL) || (PciIo->RomSize == 0)) {
      continue;
    }

    //
    // Check if it is external device, because we should already dispatched on board device before.
    //
    PciIo->GetLocation (PciIo, &Seg, &Bus, &Dev, &Func);
    if (Bus == 0) {
      continue;
    }

    IsStorageOrom = FALSE;
    //
    // Check storage device
    //
    PciIo->Pci.Read (
                 PciIo,
                 EfiPciIoWidthUint8,
                 PCI_CLASSCODE_OFFSET,
                 sizeof(ClassCode),
                 &ClassCode[0]
                 );
    DEBUG ((DEBUG_INFO,"PCI ClassCode - 0x%02x, 0x%02x, 0x%02x\n", (UINTN)ClassCode[0], (UINTN)ClassCode[1], (UINTN)ClassCode[2]));

    if (((ClassCode[2] == PCI_CLASS_DISPLAY) && (ClassCode[1] == PCI_CLASS_DISPLAY_VGA)) ||
        ((ClassCode[2] == PCI_CLASS_OLD) && (ClassCode[1] == PCI_CLASS_OLD_VGA))) {
      //
      // Filter Video rom, it should be dispatched by VideoThunk
      //
      continue;
    }

    PciIo->Pci.Read (
                 PciIo,
                 EfiPciIoWidthUint16,
                 PCI_VENDOR_ID_OFFSET,
                 1,
                 &VendorId
                 );

    if ((ClassCode[2] == PCI_CLASS_NETWORK) && (VendorId == V_PCH_INTEL_VENDOR_ID)) {
      //
      // Filter Intel NIC rom, it should be dispatched by InstallAdditionalOpRom (InstallPxeRom);
      //
      continue;
    }

    if ((ClassCode[2] == PCI_CLASS_MASS_STORAGE) ||
        ((ClassCode[2] == PCI_CLASS_INTELLIGENT_IO) && (ClassCode[1] == 0x00))) {
      IsStorageOrom = TRUE;
    }

    if (!((IsStorageOrom && InstallStorageRom) ||
          ((!IsStorageOrom) && InstallOtherRom))) {
      //
      // Do not dispatch it
      //
      continue;
    }

    PciIo->Pci.Read (PciIo, EfiPciIoWidthUint16, PCI_VENDOR_ID_OFFSET, 1, &VendorId);
    PciIo->Pci.Read (PciIo, EfiPciIoWidthUint16, PCI_DEVICE_ID_OFFSET, 1, &DeviceId);

    //
    // Dispatch it
    //
    DEBUG ((DEBUG_INFO,"OPROM will be installed - VendorId = 0x%04x, DeviceId = 0x%04x, (0x%x-0x%x)\n",
            (UINTN)VendorId, (UINTN)DeviceId,
            (UINTN)PciIo->RomImage, (UINTN)PciIo->RomSize));
    DEBUG ((DEBUG_INFO,"PCI device - Bus: 0x%02x, Device: 0x%02x, Function: 0x%02x\n", Bus, Dev, Func));

    Status = PciIo->Attributes (
                      PciIo,
                      EfiPciIoAttributeOperationEnable,
                      EFI_PCI_DEVICE_ENABLE,
                      NULL
                      );
    DEBUG ((DEBUG_INFO,"PciIo->Attributes - %r\n", Status));

    Status = LegacyBios->CheckPciRom (
                           LegacyBios,
                           HandleBuffer[Index],
                           NULL,
                           NULL,
                           &Flags
                           );
    DEBUG ((DEBUG_INFO,"CheckPciRom - %r %x\n", Status, Flags));

    Status = LegacyBios->InstallPciRom (
                           LegacyBios,
                           HandleBuffer[Index],
                           NULL,
                           &Flags,
                           &DiskStart,
                           &DiskEnd,
                           NULL,
                           NULL
                           );
    DEBUG ((DEBUG_INFO,"InstallPciRom - %r %x %x\n", Status, (UINTN)DiskStart, (UINTN)DiskEnd));

    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR,"OPROM is failed to be installed\n"));
      continue;
    }
  }

  FreePool (HandleBuffer);
  return ;
}
