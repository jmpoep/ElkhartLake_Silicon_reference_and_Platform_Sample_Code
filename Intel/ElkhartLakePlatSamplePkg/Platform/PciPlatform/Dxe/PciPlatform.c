/** @file
  Registers onboard PCI ROMs with PCI.IO

@copyright
  INTEL CONFIDENTIAL
  Copyright 2004 - 2018 Intel Corporation.

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

#include "PciPlatform.h"
#include <Library/IoLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/ConfigBlockLib.h>
#include <SetupVariable.h>
#include <Library/EcTcssLib.h>
//
// Files PlatformOpRomTable.h and PlatformOpRomTable_Default.inc will be created at runtime
//
#include "MultiPlatform/PlatformOpRomTable.h"
#include "MultiPlatform/PlatformOptionRomTable_Default.h"
#include <Register/PchRegs.h>
#include <Register/PchRegsSmbus.h>
#include <Register/PchRegsLpc.h>
#include <Library/SmbusInfoLib.h>
#include <Register/UsbRegs.h>
#include <Library/PreSiliconEnvDetectLib.h>

GLOBAL_REMOVE_IF_UNREFERENCED EFI_PCI_PLATFORM_PROTOCOL mPciPlatform = {
  PhaseNotify,
  PlatformPrepController,
  GetPlatformPolicy,
  GetPciRom
};

GLOBAL_REMOVE_IF_UNREFERENCED EFI_HANDLE mPciPlatformHandle = NULL;

/**
  Enable the Host DMAx (x=0/1/2) PCI CMD Register bits

**/
VOID
EnableDMAxCommandReg (
  VOID
  )
{
  UINT32  DmaBar;
  UINT16  Command;
  UINT8   Func;
  UINT64  DmaBaseAddress;

  DEBUG((DEBUG_INFO, "Enabling  Host Dma PCI Command Register \n "));
  for (Func = SA_HOST_DMA0_FUN_NUM ; Func <= SA_HOST_DMA1_FUN_NUM; Func++) {

    //
    // Step 1. Make sure the Host DMA device is enabled.
    //
    DmaBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_HOST_DMA_BUS_NUM, SA_HOST_DMA_DEV_NUM, Func, 0);
    if (PciSegmentRead16 (DmaBaseAddress + PCI_DEVICE_ID_OFFSET) == V_SA_DEVICE_ID_INVALID)  {
      continue;
    }

    //
    // Step 2. Make sure the Host DMA BAR is initialized.
    //         Check if the lower 32 bits of the 64-bit BAR are configured.
    //
    DmaBar = PciSegmentRead32 (DmaBaseAddress + R_SA_HOST_DMA_LBAR) & ~(0xF);
    if ((DmaBar & 0xFFFF0000) == 0) {
      //
      // If the lower 32 bits are not configured, check the upper 32 bits.
      //
      DmaBar = PciSegmentRead32 (DmaBaseAddress + R_SA_HOST_DMA_UBAR);
      if (DmaBar == 0) {
        continue;
      }
    }

    //
    // Step 3. If Host DMA MSE (Memory Space Enable) or BME (Bus Master Enable) or IO (IO Space Enable) bits are cleared, set it.
    //
    Command = PciSegmentRead16 (DmaBaseAddress + PCI_COMMAND_OFFSET);
    if ((Command & (EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER | EFI_PCI_COMMAND_IO_SPACE)) != (EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER | EFI_PCI_COMMAND_IO_SPACE)) {
      PciSegmentOr16 (DmaBaseAddress + PCI_COMMAND_OFFSET, (EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER | EFI_PCI_COMMAND_IO_SPACE));
    }
  }
  return;
}

/**
  Attempt to set the XHCI controller's PCI CMD.MSE bit to enable OS kernel debugging over XHCI.

**/
VOID
AttemptToSetXhciMse (
  IN  UINT8   KernelDebugPatch
  )
{
  UINT32  XhciBar;
  UINT16  Command;

  //
  // Step 1. Make sure the XHCI controller is enabled.
  //
// @todo : Replace with XHCI Enable/Disable code
//  if ((MmioRead32 (RC + R_PCH_RCRB_FUNC_DIS) & (UINT32) B_PCH_RCRB_FUNC_DIS_XHCI) != 0) {
//    return;
//  }

  //
  // Step 2. Make sure the XHCI BAR is initialized.
  //         Check if the lower 32 bits of the 64-bit BAR are configured.
  //
  XhciBar = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (
                                DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                                PCI_BUS_NUMBER_PCH_XHCI,
                                PCI_DEVICE_NUMBER_PCH_XHCI,
                                PCI_FUNCTION_NUMBER_PCH_XHCI,
                                R_XHCI_CFG_BAR0
                                ));
  XhciBar &= ~(0xF);
  if ((XhciBar & 0xFFFF0000) == 0) {
    //
    // If the lower 32 bits are not configured, check the upper 32 bits.
    //
    XhciBar = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (
                                  DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                                  PCI_BUS_NUMBER_PCH_XHCI,
                                  PCI_DEVICE_NUMBER_PCH_XHCI,
                                  PCI_FUNCTION_NUMBER_PCH_XHCI,
                                  R_XHCI_CFG_BAR0
                                  ) + 4);
  }
  //
  // Step 3. If XHCI's MSE (Memory Space Enable) or BME (Bus Master Enable) bits are cleared, set it.
  //
  if (XhciBar != 0) {
    Command = PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (
                                  DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                                  PCI_BUS_NUMBER_PCH_XHCI,
                                  PCI_DEVICE_NUMBER_PCH_XHCI,
                                  PCI_FUNCTION_NUMBER_PCH_XHCI,
                                  PCI_COMMAND_OFFSET
                                  ));
    if ((Command & (EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER)) != (EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER)) {
      PciSegmentOr16 (PCI_SEGMENT_LIB_ADDRESS (
                        DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                        PCI_BUS_NUMBER_PCH_XHCI,
                        PCI_DEVICE_NUMBER_PCH_XHCI,
                        PCI_FUNCTION_NUMBER_PCH_XHCI,
                        PCI_COMMAND_OFFSET
                        ),
                      (EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER)
                      );
    }
  }
  return;
}

EFI_STATUS
EFIAPI
PhaseNotify (
  IN  EFI_PCI_PLATFORM_PROTOCOL                      *This,
  IN  EFI_HANDLE                                     HostBridge,
  IN  EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PHASE  Phase,
  IN  EFI_PCI_CHIPSET_EXECUTION_PHASE                ChipsetPhase
  )
{
  EFI_STATUS                    Status;
  UINTN                         DataSize;
  SETUP_DATA                    SetupData;
  UINT8                         EcDataBuffer;
  UINT32                        Timeout;

  //
  // This is the flow to override the PCI resources allocation
  // For Thunderbolt boot Support
  // [1] Enumerate the Thunderbolt boot devices and allocate resources based on standard enumeration algorithm
  // [2] After PCI enumeration is done, invoke Thunderbolt SMI handler to specifically allocate resources, which can't be done by standard PCI enumeration algorithm. This step is performed by here when EfiPciHostBridgeBeginResourceAllocation phase is notified.
  // [3] Update BAR info already initialized by PCI enumeration using the new BAR address overridden by the Thunderbolt SMI handler; otherwise PciIo protocol can't provide the real BAR info.
  //
  if (Phase == EfiPciHostBridgeEndResourceAllocation) {
    DataSize = sizeof (SETUP_DATA);
    Status = gRT->GetVariable (
                    L"Setup",
                    &gSetupVariableGuid,
                    NULL,
                    &DataSize,
                    &SetupData
                    );

    PciSegmentWrite32 (PCI_SEGMENT_LIB_ADDRESS (
                         DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                         DEFAULT_PCI_BUS_NUMBER_PCH,
                         PCI_DEVICE_NUMBER_PCH_SMBUS,
                         PCI_FUNCTION_NUMBER_PCH_SMBUS,
                         R_SMBUS_CFG_BASE
                         ),
                       0xEFA0
                       );

    //
    // Set XHCI's MSE (Memory Space Enable) bit in the PCI command register.
    // This is required to support Windows Kernel Debugger through the USB3 debug cable.
    // Like EHCI, the XHCI bit should always be set (i.e., even if XHCI kernel debugging isn't expected).
    // Set the MSE bit here for 2 reasons:
    // 1. This must be done before the EFI XHCI driver runs.  As a standard PCI device driver, the XHCI driver
    // saves/restores the Command register before/after it runs.
    // 2. The BAR must already be initialized so that we can set the MMIO Enable bit.
    //
    AttemptToSetXhciMse (SetupData.KernelDebugPatch);

    //
    // This must be initialized after HOST DMA device is enumerated
    //
    EnableDMAxCommandReg();
  }
  //
  // Send Get USB Conn Status command to EC
  //
  else if (Phase == EfiPciHostBridgeEndEnumeration && ChipsetPhase == ChipsetEntry) {
    DataSize = sizeof (SETUP_DATA);
    Status = gRT->GetVariable (
                    L"Setup",
                    &gSetupVariableGuid,
                    NULL,
                    &DataSize,
                    &SetupData
                    );
    // Send UsbcGetUsbConnStatus only if EC Handshake is enabled in BIOS setup
    if (!EFI_ERROR(Status) && (SetupData.UsbcBiosTcssHandshake == 1) && (!PcdGetBool(PcdBoardPmcPdEnable))) {
      EcDataBuffer = 0x00;
      Timeout = SetupData.UsbConnStatusTimeout;
      Status = UsbcGetUsbConnStatus(&EcDataBuffer, Timeout);
      // Do some error checking here to handle failure
    }
  }

  return EFI_SUCCESS;
}

/**
  Platform Prep Controller

  This          - GC_TODO: add argument description
  HostBridge    - GC_TODO: add argument description
  RootBridge    - GC_TODO: add argument description
  PciAddress    - GC_TODO: add argument description
  Phase         - GC_TODO: add argument description
  ChipsetPhase  - GC_TODO: add argument description

  EFI_UNSUPPORTED - GC_TODO: Add description for return value
**/
EFI_STATUS
EFIAPI
PlatformPrepController (
  IN  EFI_PCI_PLATFORM_PROTOCOL                      *This,
  IN  EFI_HANDLE                                     HostBridge,
  IN  EFI_HANDLE                                     RootBridge,
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_PCI_ADDRESS    PciAddress,
  IN  EFI_PCI_CONTROLLER_RESOURCE_ALLOCATION_PHASE   Phase,
  IN  EFI_PCI_CHIPSET_EXECUTION_PHASE                ChipsetPhase
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Get Platform Policy

  This      - GC_TODO: add argument description
  PciPolicy - GC_TODO: add argument description

  EFI_UNSUPPORTED - GC_TODO: Add description for return value
**/
EFI_STATUS
EFIAPI
GetPlatformPolicy (
  IN CONST EFI_PCI_PLATFORM_PROTOCOL               *This,
  OUT EFI_PCI_PLATFORM_POLICY                      *PciPolicy
  )
{
  if (IsSimicsEnvironment()) {
    *PciPolicy = EFI_RESERVE_ISA_IO_NO_ALIAS | EFI_RESERVE_VGA_IO_ALIAS;
    return EFI_SUCCESS;
  } else {
    return EFI_UNSUPPORTED;
  }
}

/**
  Return a PCI ROM image for the onboard device represented by PciHandle

  This      - Protocol instance pointer.
  PciHandle - PCI device to return the ROM image for.
  RomImage  - PCI Rom Image for onboard device
  RomSize   - Size of RomImage in bytes

  EFI_SUCCESS   - RomImage is valid
  EFI_NOT_FOUND - No RomImage
**/
EFI_STATUS
EFIAPI
GetPciRom (
  IN  CONST EFI_PCI_PLATFORM_PROTOCOL             *This,
  IN  EFI_HANDLE                                  PciHandle,
  OUT VOID                                        **RomImage,
  OUT UINTN                                       *RomSize
  )
{
  EFI_STATUS                    Status;
  EFI_PCI_IO_PROTOCOL           *PciIo;
  UINTN                         Segment;
  UINTN                         Bus;
  UINTN                         Device;
  UINTN                         Function;
  UINT16                        VendorId;
  UINT16                        DeviceId;
  UINTN                         HandleCount;
  EFI_HANDLE                    *HandleBuffer;
  UINTN                         TableIndex;
  UINTN                         Index;
  EFI_FIRMWARE_VOLUME2_PROTOCOL *FirmwareVolume;
  UINT32                        AuthenticationStatus;
  VOID                          *LocalRomImage;
  UINTN                         LocalRomSize;
  UINT8                         ClassCode[3];
  UINTN                         SaSetupSize;
  SA_SETUP                      SaSetup;

  FirmwareVolume = NULL;

  Status = gBS->HandleProtocol (
                  PciHandle,
                  &gEfiPciIoProtocolGuid,
                  (VOID **) &PciIo
                  );
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  PciIo->GetLocation (
           PciIo,
           &Segment,
           &Bus,
           &Device,
           &Function
           );

  PciIo->Pci.Read (
              PciIo,
              EfiPciIoWidthUint16,
              0,
              1,
              &VendorId
              );

  PciIo->Pci.Read (
              PciIo,
              EfiPciIoWidthUint16,
              2,
              1,
              &DeviceId
              );

  PciIo->Pci.Read (
              PciIo,
              EfiPciIoWidthUint8,
              PCI_CLASSCODE_OFFSET,
              sizeof(ClassCode),
              &ClassCode[0]
              );

  // Work around to skip the dGPU's EFI Option Rom which is getting started by connectcontroller in
  // core code by LegacyBootManagerLib.c.
  if ((ClassCode[2] == PCI_CLASS_DISPLAY) && (VendorId != INTEL_VENDOR_ID)) {
    SaSetupSize = sizeof (SA_SETUP);
    Status = gRT->GetVariable(
                    L"SaSetup",
                    &gSaSetupVariableGuid,
                    NULL,
                    &SaSetupSize,
                    &SaSetup
                    );
    if (!EFI_ERROR(Status)) {
      if (SaSetup.PrimaryDisplay == 0 || SaSetup.PrimaryDisplay == 4) {
        //
        // When Primary Display is HG/IGD we need to skip VGA dGPU option rom, both EFI & Legacy option ROM.
        //
        PciIo->RomImage = NULL;
        PciIo->RomSize = 0;
        DEBUG((DEBUG_INFO, "Skip Discrete Option ROM, Both EFI (GOP) & Legacy option ROM for Device VendorId : %x\n", VendorId));
        return EFI_NOT_FOUND;
      }
    }
  }

  DEBUG ((DEBUG_INFO, "GetRom  Bus  0x%X\n", Bus));
  DEBUG ((DEBUG_INFO, "GetRom  Device  0x%X\n", Device));
  DEBUG ((DEBUG_INFO, "GetRom  Function  0x%X\n", Function));
  DEBUG ((DEBUG_INFO, "GetRom  VID  0x%X\n", VendorId));
  DEBUG ((DEBUG_INFO, "GetRom  DID  0x%X\n", DeviceId));

  OpromPatchPciIo (PciIo);

  //
  // Get the list of available firmware volumes
  //
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiFirmwareVolume2ProtocolGuid,
                  NULL,
                  &HandleCount,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status) || HandleCount == 0) {
    return EFI_NOT_FOUND;
  }
  //
  // Loop through table of video option rom descriptions
  //
  for (TableIndex = 0; mPciOptionRomTable_Default[TableIndex].VendorId != 0xffff; TableIndex++) {
    //
    // See if the PCI device specified by PciHandle matches at device in mPciOptionRomTable_Default
    //
    if (VendorId != mPciOptionRomTable_Default[TableIndex].VendorId) {
      continue;
    }

    if (DeviceId != mPciOptionRomTable_Default[TableIndex].DeviceId) {
      continue;
    }

    if (Segment != mPciOptionRomTable_Default[TableIndex].Segment) {
      continue;
    }

    if (Bus != mPciOptionRomTable_Default[TableIndex].Bus) {
      continue;
    }

    if (Device != mPciOptionRomTable_Default[TableIndex].Device) {
      continue;
    }

    if (Function != mPciOptionRomTable_Default[TableIndex].Function) {
      continue;
    }
    //
    // Loop through the Firmware Volumes looking for the Easton 815 Video ROM image
    //
    for (Index = 0; Index < HandleCount; Index++) {
      //
      // Get the Firmware Volume Protocol
      //
      Status = gBS->HandleProtocol (
                      HandleBuffer[Index],
                      &gEfiFirmwareVolume2ProtocolGuid,
                      (VOID **) &FirmwareVolume
                      );
      if (EFI_ERROR (Status)) {
        continue;
      }
      //
      // Get the 16-bit BIOS code from the same Firmware Volume as this driver
      //
      LocalRomImage = NULL;
      LocalRomSize  = 0;
      Status = FirmwareVolume->ReadSection (
                                 FirmwareVolume,
                                 &mPciOptionRomTable_Default[TableIndex].FileName,
                                 EFI_SECTION_RAW,
                                 0,
                                 &LocalRomImage,
                                 &LocalRomSize,
                                 &AuthenticationStatus
                                 );
      if (EFI_ERROR (Status)) {
        continue;
      }

      *RomImage = LocalRomImage;
      *RomSize  = LocalRomSize;

      FreePool (HandleBuffer);

      return EFI_SUCCESS;
    }
  }

  FreePool (HandleBuffer);

  return EFI_NOT_FOUND;
}


/**
  PciPlatformDriverEntry

  EFI_STATUS
**/
EFI_STATUS
EFIAPI
PciPlatformDriverEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS                                Status;

  //
  // Install on a new handle
  //
  Status = gBS->InstallProtocolInterface (
                  &mPciPlatformHandle,
                  &gEfiPciPlatformProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &mPciPlatform
                  );

  return Status;
}
