/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2018 Intel Corporation.

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

@par Specification
**/

#include "SataController.h"

///
///  EFI_DRIVER_BINDING_PROTOCOL instance
///
GLOBAL_REMOVE_IF_UNREFERENCED EFI_DRIVER_BINDING_PROTOCOL mSataControllerDriverBinding = {
  SataControllerSupported,
  SataControllerStart,
  SataControllerStop,
  0x10,
  NULL,
  NULL
};

///
///  EFI_ATA_COLLECTIVE_MODE Template
///
GLOBAL_REMOVE_IF_UNREFERENCED EFI_ATA_COLLECTIVE_MODE  gEfiAtaCollectiveModeTemplate = {
  {
    TRUE,                   ///< PioMode.Valid
    0                       ///< PioMode.Mode
  },
  {
    TRUE,                   ///< SingleWordDmaMode.Valid
    0
  },
  {
    FALSE,                  ///< MultiWordDmaMode.Valid
    0
  },
  {
    TRUE,                   ///< UdmaMode.Valid
    0                       ///< UdmaMode.Mode
  }
};

/**
  <b>SataController  DXE Module Entry Point</b>\n
  - <b>Introduction</b>\n
    The SataController module is a DXE EFI 1.1 Driver Model driver which abstracts
    the IDE timings calculation and algorithms of the SATA controller. These algorithms
    are described in PCH <I>BIOS specification or EDS</I>. It is consumed by the IDE bus
    driver to configure IDE devices.
    It's called by StartImage() of DXE Core.

  - @pre
    - <b>EFI_DEVICE_PATH_PROTOCOL</b>\n
      - Documented in UEFI 2.0 Specification.
    - <b>EFI_PCI_IO_PROTOCOL</b>\n
      - Documented in UEFI 2.0 Specification.
    - @link PchPlatformLib.h PchPlatformLib @endlink library

  - @result
    The SataController driver produces EFI_IDE_CONTROLLER_INIT_PROTOCOL
      - Documented in the IDE Controller Initialization Protocol Specification

  - <b>Porting Recommendations</b>\n
    This module does not load legacy Option ROM in RAID or AHCI mode. If needed, platform
    code needs to perform legacy Option ROM loading.
    This module supports Framework IDE driver (in IDE mode) and Framework native AHCI driver (in AHCI mode).

  @param[in] ImageHandle          While the driver image loaded be the ImageLoader(),
                                  an image handle is assigned to this driver binary,
                                  all activities of the driver is tied to this ImageHandle
  @param[in] SystemTable          A pointer to the system table, for all BS(Boo Services) and
                                  RT(Runtime Services)

  @retval EFI_SUCCESS             Function completes successfully
**/
EFI_STATUS
EFIAPI
InitializeSataControllerDriver (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS              Status;

  Status = EfiLibInstallDriverBindingComponentName2 (
             ImageHandle,
             SystemTable,
             &mSataControllerDriverBinding,
             ImageHandle,
             &mSataControllerComponentName,
             &mSataControllerComponentName2
             );
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/**
  This function checks to see if the driver supports a device specified by
  "Controller handle" parameter. It is called by DXE Core StartImage() or
  ConnectController() routines. The driver uses 'device path' and/or
  'services' from the Bus I/O abstraction attached to the controller handle
  to determine if the driver support this controller handle.
  Note: In the BDS (Boot Device Selection) phase, the DXE core enumerate all
  devices (or, controller) and assigns GUIDs to them.

  @param[in] This                 A pointer points to the Binding Protocol instance
  @param[in] Controller           The handle of controller to be tested.
  @param[in] RemainingDevicePath  A pointer to the device path. Ignored by device
                                  driver but used by bus driver

  @retval EFI_SUCCESS             The device is supported
  @exception EFI_UNSUPPORTED      The device is not supported
**/
EFI_STATUS
EFIAPI
SataControllerSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL *This,
  IN EFI_HANDLE                  Controller,
  IN EFI_DEVICE_PATH_PROTOCOL    *RemainingDevicePath
  )
{
  EFI_STATUS                Status;
  UINT32                    SataDeviceIdFound;
  EFI_DEVICE_PATH_PROTOCOL  *ParentDevicePath;
  EFI_PCI_IO_PROTOCOL       *PciIo;
  PCI_TYPE00                PciData;
  UINTN                     SegNum;
  UINTN                     BusNum;
  UINTN                     DevNum;
  UINTN                     FuncNum;

  ///
  /// SATA Controller is a device driver, and should ingore the
  /// "RemainingDevicePath" according to EFI spec
  ///
  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiDevicePathProtocolGuid,
                  (VOID *) &ParentDevicePath,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status)) {
    ///
    /// EFI_ALREADY_STARTED is also an error
    ///
    return Status;
  }
  ///
  /// Close the protocol because we don't use it here
  ///
  gBS->CloseProtocol (
        Controller,
        &gEfiDevicePathProtocolGuid,
        This->DriverBindingHandle,
        Controller
        );

  ///
  /// Now test the EfiPciIoProtocol
  ///
  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiPciIoProtocolGuid,
                  (VOID **) &PciIo,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  ///
  /// Now further check the PCI header: Base class (offset 0x0B) and
  /// Sub Class (offset 0x0A). This controller should be an SATA controller
  ///
  Status = PciIo->Pci.Read (
                        PciIo,
                        EfiPciIoWidthUint8,
                        0,
                        sizeof (PciData),
                        &PciData
                        );
  if (EFI_ERROR (Status)) {
    gBS->CloseProtocol (
           Controller,
           &gEfiPciIoProtocolGuid,
           This->DriverBindingHandle,
           Controller
           );
    return EFI_UNSUPPORTED;
  }

  ///
  /// Get device location
  ///
  Status = PciIo->GetLocation (
                    PciIo,
                    &SegNum,
                    &BusNum,
                    &DevNum,
                    &FuncNum
                    );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Since we already got the PciData, we can close protocol to avoid to carry it on for multiple exit points.
  ///
  gBS->CloseProtocol (
         Controller,
         &gEfiPciIoProtocolGuid,
         This->DriverBindingHandle,
         Controller
         );

  ///
  /// Check if we have oprom
  /// TODO: In case we need to support PCIe AHCI card with OROM, add a policy to bypass this check and a setup option to disable the card OROM
  ///

  ///
  /// Examine SATA PCI Configuration table fields
  ///
  SataDeviceIdFound = FALSE;

  ///
  /// When found is storage device and provided by Intel then detect for right device Ids
  ///
  if (PciData.Hdr.ClassCode[2] == PCI_CLASS_MASS_STORAGE) {
    if ((PciData.Hdr.ClassCode[1] == SATA_SUB_CLASS_CODE_AHCI) || (PciData.Hdr.ClassCode[1] == PCI_CLASS_MASS_STORAGE_RAID)) {
      SataDeviceIdFound = TRUE;
    }
  }

  if (!SataDeviceIdFound) {
    return EFI_UNSUPPORTED;
  }

  return Status;
}

/**
  This routine is called right after the .Supported() is called and returns
  EFI_SUCCESS. Notes: The supported protocols are checked but the Protocols
  are closed.

  @param[in] This                 A pointer points to the Binding Protocol instance
  @param[in] Controller           The handle of controller to be tested. Parameter
                                  passed by the caller
  @param[in] RemainingDevicePath  A pointer to the device path. Should be ignored by
                                  device driver

  @retval EFI_SUCCESS             The device is started
  @retval Other values            Something error happened
**/
EFI_STATUS
EFIAPI
SataControllerStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                        Status;
  EFI_IDE_CONTROLLER_INIT_PROTOCOL  *IdeInit;
  EFI_PCI_IO_PROTOCOL               *PciIo;
  UINT64                            CommandVal;
  UINT32                            PortsImplemented;
  UINT8                             MaxPortNumber;

  DEBUG ((DEBUG_INFO, "SataControllerStart() Start\n"));

  ///
  /// Now test and open the EfiPciIoProtocol
  ///
  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiPciIoProtocolGuid,
                  (VOID **) &PciIo,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  ///
  /// Status == 0 - A normal execution flow, SUCCESS and the program proceeds.
  /// Status == ALREADY_STARTED - A non-zero Status code returned. It indicates
  ///           that the protocol has been opened and should be treated as a
  ///           normal condition and the program proceeds. The Protocol will not
  ///           opened 'again' by this call.
  /// Status != ALREADY_STARTED - Error status, terminate program execution
  ///
  if (EFI_ERROR (Status)) {
    ///
    /// EFI_ALREADY_STARTED is also an error
    ///
    return Status;
  }

  ///
  /// Get device capabilities
  ///
  Status = PciIo->Attributes (
                    PciIo,
                    EfiPciIoAttributeOperationSupported,
                    0,
                    &CommandVal
                    );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Enable Command Register
  ///
  Status = PciIo->Attributes (
                    PciIo,
                    EfiPciIoAttributeOperationEnable,
                    CommandVal & EFI_PCI_DEVICE_ENABLE,
                    NULL
                    );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Get Ports Implemented
  ///
  PortsImplemented = 0;
  PciIo->Mem.Read (
               PciIo,
               EfiPciIoWidthUint32,
               EFI_AHCI_BAR_INDEX,
               (UINT64) R_AHCI_PI,
               1,
               &PortsImplemented
               );
  if (PortsImplemented == 0) {
    Status = EFI_UNSUPPORTED;
    goto SataControllerStartEnd;
  }
  MaxPortNumber = 31;
  while (MaxPortNumber > 0) {
    if (PortsImplemented & (1 << MaxPortNumber)) {
      break;
    }
    MaxPortNumber --;
  }

  IdeInit = AllocatePool (sizeof (EFI_IDE_CONTROLLER_INIT_PROTOCOL));
  if (IdeInit == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto SataControllerStartEnd;
  }
  IdeInit->GetChannelInfo = IdeInitGetChannelInfo;
  IdeInit->NotifyPhase    = IdeInitNotifyPhase;
  IdeInit->SubmitData     = IdeInitSubmitData;
  IdeInit->DisqualifyMode = IdeInitDisqualifyMode;
  IdeInit->CalculateMode  = IdeInitCalculateMode;
  IdeInit->SetTiming      = IdeInitSetTiming;
  IdeInit->EnumAll        = SATA_ENUMER_ALL;
  //
  // For AHCI support, make the ChannelCount equal to the max enabled port number plus 1.
  //
  IdeInit->ChannelCount   = MaxPortNumber + 1;

  ///
  /// Install IDE_CONTROLLER_INIT protocol & private data to this instance
  ///
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Controller,
                  &gEfiIdeControllerInitProtocolGuid,
                  IdeInit,
                  NULL
                  );

SataControllerStartEnd:
  if (EFI_ERROR (Status)) {
    ///
    /// Close protocols opened by SATA controller driver
    ///
    gBS->CloseProtocol (
          Controller,
          &gEfiPciIoProtocolGuid,
          This->DriverBindingHandle,
          Controller
          );
  }

  DEBUG ((DEBUG_INFO, "SataControllerStart() End\n"));

  return Status;
}

/**
  Stop managing the target device

  @param[in] This                 A pointer pointing to the Binding Protocol instance
  @param[in] Controller           The handle of controller to be stopped
  @param[in] NumberOfChildren     Number of child devices
  @param[in] ChildHandleBuffer    Buffer holding child device handles

  @retval EFI_SUCCESS             The target device is stopped
**/
EFI_STATUS
EFIAPI
SataControllerStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL     *This,
  IN  EFI_HANDLE                      Controller,
  IN  UINTN                           NumberOfChildren,
  IN  EFI_HANDLE                      *ChildHandleBuffer
  )
{
  EFI_STATUS                        Status;
  EFI_IDE_CONTROLLER_INIT_PROTOCOL  *IdeControllerInit;

  DEBUG ((DEBUG_INFO, "SataControllerStop() Start\n"));

  ///
  /// Open the produced protocol
  ///
  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiIdeControllerInitProtocolGuid,
                  (VOID **) &IdeControllerInit,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );

  if (!EFI_ERROR (Status)) {
    ///
    /// Uninstall the produced protocol
    ///
    Status = gBS->UninstallMultipleProtocolInterfaces (
                    Controller,
                    &gEfiIdeControllerInitProtocolGuid, IdeControllerInit,
                    NULL
                    );
    ASSERT_EFI_ERROR (Status);
    FreePool (IdeControllerInit);

    //
    // Close protocols opened by Sata Controller driver
    //
    Status = gBS->CloseProtocol (
                    Controller,
                    &gEfiPciIoProtocolGuid,
                    This->DriverBindingHandle,
                    Controller
                    );
  }

  DEBUG ((DEBUG_INFO, "SataControllerStop() End\n"));
  return Status;
}

//
// Interface functions of IDE_CONTROLLER_INIT protocol
//

/**
  This function can be used to obtain information about a specified channel.
  It's usually used by IDE Bus driver during enumeration process.

  @param[in] This                 the EFI_IDE_CONTROLLER_INIT_PROTOCOL instance.
  @param[in] Channel              For IDE, Channel number (0 based, either 0 or 1)
                                  For AHCI, it's port number.
  @param[out] Enabled             TRUE if the channel is enabled. If the channel is disabled,
                                  then it will no be enumerated.
  @param[out] MaxDevices          The Max number of IDE devices that the bus driver can expect
                                  on this channel. For ATA/ATAPI, this number is either 1 or 2.

  @retval EFI_SUCCESS             Function completes successfully
  @retval Other Values            Something error happened
  @retval EFI_INVALID_PARAMETER   The Channel parameter is invalid
**/
EFI_STATUS
EFIAPI
IdeInitGetChannelInfo (
  IN   EFI_IDE_CONTROLLER_INIT_PROTOCOL    *This,
  IN   UINT8                               Channel,
  OUT  BOOLEAN                             *Enabled,
  OUT  UINT8                               *MaxDevices
  )
{
  ///
  /// Channel number (0 based, either 0 or 1)
  ///
  if (Channel < This->ChannelCount) {
    *Enabled    = TRUE;
    *MaxDevices = AHCI_MAX_DEVICES;
    return EFI_SUCCESS;
  } else {
    *Enabled = FALSE;
    return EFI_INVALID_PARAMETER;
  }
}

/**
  This function is called by IdeBus driver before executing certain actions.
  This allows IDE Controller Init to prepare for each action.

  @param[in] This                 the EFI_IDE_CONTROLLER_INIT_PROTOCOL instance.
  @param[in] Phase                phase indicator defined by IDE_CONTROLLER_INIT protocol
  @param[in] Channel              For IDE, Channel number (0 based, either 0 or 1)
                                  For AHCI, it's port number.

  @retval EFI_SUCCESS             Function completes successfully
  @retval EFI_INVALID_PARAMETER   Channel parameter is out of range
  @exception EFI_UNSUPPORTED      Phase is not supported
**/
EFI_STATUS
EFIAPI
IdeInitNotifyPhase (
  IN  EFI_IDE_CONTROLLER_INIT_PROTOCOL  *This,
  IN  EFI_IDE_CONTROLLER_ENUM_PHASE     Phase,
  IN  UINT8                             Channel
  )
{
  return EFI_SUCCESS;
}

/**
  This function is called by IdeBus driver to submit EFI_IDENTIFY_DATA data structure
  obtained from IDE deivce. This structure is used to set IDE timing

  @param[in] This                 the EFI_IDE_CONTROLLER_INIT_PROTOCOL instance.
  @param[in] Channel              IDE channel number (0 based, either 0 or 1)
                                  For AHCI, it's port number.
  @param[in] Device               IDE device number
  @param[in] IdentifyData         A pointer to EFI_IDENTIFY_DATA data structure

  @retval EFI_SUCCESS             Function completes successfully
  @retval EFI_INVALID_PARAMETER   Channel or Device parameter is out of range
**/
EFI_STATUS
EFIAPI
IdeInitSubmitData (
  IN  EFI_IDE_CONTROLLER_INIT_PROTOCOL    *This,
  IN  UINT8                               Channel,
  IN  UINT8                               Device,
  IN  EFI_IDENTIFY_DATA                   *IdentifyData
  )
{
  return EFI_SUCCESS;
}

/**
  This function is called by IdeBus driver to disqualify unsupported operation
  mode on specfic IDE device

  @param[in] This                 The EFI_IDE_CONTROLLER_INIT_PROTOCOL instance.
  @param[in] Channel              IDE channel number (0 based, either 0 or 1)
                                  For AHCI, it's port number.
  @param[in] Device               IDE device number
  @param[in] BadModes             Operation mode indicator

  @retval EFI_SUCCESS             Function completes successfully
  @retval EFI_INVALID_PARAMETER   Channel parameter or Devicde parameter is out of range,
                                  or BadModes is NULL
**/
EFI_STATUS
EFIAPI
IdeInitDisqualifyMode (
  IN  EFI_IDE_CONTROLLER_INIT_PROTOCOL    *This,
  IN  UINT8                               Channel,
  IN  UINT8                               Device,
  IN  EFI_ATA_COLLECTIVE_MODE             *BadModes
  )
{
  return EFI_SUCCESS;
}

/**
  This function is called by IdeBus driver to calculate the best operation mode
  supported by specific IDE device

  @param[in] This                 The EFI_IDE_CONTROLLER_INIT_PROTOCOL instance.
  @param[in] Channel              IDE channel number (0 based, either 0 or 1)
                                  For AHCI, it's port number.
  @param[in] Device               IDE device number
  @param[in, out] SupportedModes  Modes collection supported by IDE device

  @retval EFI_SUCCESS             Function completes successfully
  @retval EFI_INVALID_PARAMETER   Channel parameter or Device parameter is out of range;
                                  Or SupportedModes is NULL
  @retval EFI_NOT_READY           Identify data is not valid
  @retval EFI_OUT_OF_RESOURCES    SupportedModes is out of range
**/
EFI_STATUS
EFIAPI
IdeInitCalculateMode (
  IN  EFI_IDE_CONTROLLER_INIT_PROTOCOL       *This,
  IN  UINT8                                  Channel,
  IN  UINT8                                  Device,
  IN OUT EFI_ATA_COLLECTIVE_MODE             **SupportedModes
  )
{
  if ((Channel >= This->ChannelCount) || (Device >= AHCI_MAX_DEVICES)) {
    return EFI_INVALID_PARAMETER;
  }

  *SupportedModes = AllocateCopyPool (sizeof (EFI_ATA_COLLECTIVE_MODE), &gEfiAtaCollectiveModeTemplate);
  if (*SupportedModes == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  return EFI_SUCCESS;
}

/**
  This function is called by IdeBus driver to set appropriate timing on IDE
  controller according supported operation mode

  @param[in] This                 The EFI_IDE_CONTROLLER_INIT_PROTOCOL instance.
  @param[in] Channel              IDE channel number (0 based, either 0 or 1)
                                  For AHCI, it's port number.
  @param[in] Device               IDE device number
  @param[in] Modes                Operation modes

  @retval EFI_SUCCESS             This function always returns EFI_SUCCESS
**/
EFI_STATUS
EFIAPI
IdeInitSetTiming (
  IN  EFI_IDE_CONTROLLER_INIT_PROTOCOL    *This,
  IN  UINT8                               Channel,
  IN  UINT8                               Device,
  IN  EFI_ATA_COLLECTIVE_MODE             *Modes
  )
{
  return EFI_SUCCESS;
}
