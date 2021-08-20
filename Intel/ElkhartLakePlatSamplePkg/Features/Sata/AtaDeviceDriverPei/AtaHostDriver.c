/** @file
  Install ATA host PPI.

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

@par Specification
**/

#include "AtaHostDriver.h"

PEI_ATA_HOST_CONTROLLER_PPI  mAtaControllerPpi = {GetAtaControllerInfo};

EFI_PEI_PPI_DESCRIPTOR   mPpiList = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gPeiAtaHostControllerPpiGuid,
  &mAtaControllerPpi
};

/**
  This function handles AtaHostController task at the end of PEI

  @param[in]  PeiServices  Pointer to PEI Services Table.
  @param[in]  NotifyDesc   Pointer to the descriptor for the Notification event that
                           caused this function to execute.
  @param[in]  Ppi          Pointer to the PPI data associated with this function.

  @retval     EFI_SUCCESS  The function completes successfully
  @retval     others

**/
EFI_STATUS
EFIAPI
AtaHostControllerEndOfPei (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  );

static EFI_PEI_NOTIFY_DESCRIPTOR  mEndOfPeiNotifyList = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiEndOfPeiSignalPpiGuid,
  (EFI_PEIM_NOTIFY_ENTRY_POINT) AtaHostControllerEndOfPei
};

/**
  This function handles AtaHostController task at the end of PEI

  @param[in]  PeiServices  Pointer to PEI Services Table.
  @param[in]  NotifyDesc   Pointer to the descriptor for the Notification event that
                           caused this function to execute.
  @param[in]  Ppi          Pointer to the PPI data associated with this function.

  @retval     EFI_SUCCESS  The function completes successfully
  @retval     others

**/
EFI_STATUS
EFIAPI
AtaHostControllerEndOfPei (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  )
{
  UINT64                PciSataRegBase;

  PciSataRegBase = PCI_SEGMENT_LIB_ADDRESS (
                     DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                     DEFAULT_PCI_BUS_NUMBER_PCH,
                     SataDevNumber (SATA_1_CONTROLLER_INDEX),
                     SataFuncNumber (SATA_1_CONTROLLER_INDEX),
                     0
                     );

  ///
  /// Disable command register memory space decoding
  ///
  PciSegmentAnd16 (PciSataRegBase + PCI_COMMAND_OFFSET, (UINT16) ~(EFI_PCI_COMMAND_MEMORY_SPACE + EFI_PCI_COMMAND_BUS_MASTER));

  ///
  /// Set Ahci Bar to zero
  ///
  PciSegmentWrite32 (PciSataRegBase + R_SATA_CFG_AHCI_BAR, 0);

  return EFI_SUCCESS;
}

/**
  Get the MMIO base address of ATA host controller.

  @param[in]     PeiServices         Describes the list of possible PEI Services.
  @param[in]     This                The protocol instance pointer.
  @param[in]     AtaControllerId     The ID of the ATA host controller.
  @param[out]    BaseAddress         The base address of controller's MMIO space

  @retval EFI_SUCCESS                The operation succeeds.
  @retval EFI_INVALID_PARAMETER      The parameters are invalid.

**/
EFI_STATUS
EFIAPI
GetAtaControllerInfo (
  IN  EFI_PEI_SERVICES                           **PeiServices,
  IN  PEI_ATA_HOST_CONTROLLER_PPI                *This,
  IN  UINT8                                      AtaControllerId,
  OUT UINTN                                      *BaseAddress
  )
{
  PEI_SATA_HC_PRIVATE_DATA  *Private;

  if ((This == NULL) || (BaseAddress == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  Private = PEI_ATA_HC_PEI_PRIVATE_DATA_FROM_THIS (This);
  *BaseAddress = Private->MmioBase;

  return EFI_SUCCESS;
}

/**
  Assign resources and enable controller

  @param[in]  Private              Pointer to SATA controller peim private data.

  @retval  EFI_SUCCESS             Successfully enabled the controller.
  @retval  Others                  Failed to enabled the controller

**/
EFI_STATUS
EFIAPI
InitializeAtaDirectConnect (
  PEI_SATA_HC_PRIVATE_DATA         *Private
  )
{
  PCI_CLASSC                       PciClass;
  UINT16                           VidDid;
  UINTN                            MmioBar;

  DEBUG ((EFI_D_INFO, "(AtaHostDriver) InitializeAtaDirectConnect: entry \n"));

  //
  // Assign resources and enable controller
  //
  Private->HostBase = PCI_SEGMENT_LIB_ADDRESS (
                        DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                        DEFAULT_PCI_BUS_NUMBER_PCH,
                        SataDevNumber (SATA_1_CONTROLLER_INDEX),
                        SataFuncNumber (SATA_1_CONTROLLER_INDEX),
                        0
                        );

  VidDid = PciSegmentRead16 (Private->HostBase + PCI_VENDOR_ID_OFFSET);

  if (VidDid == 0xFFFF) {
    DEBUG ((DEBUG_ERROR, "Vendor id is invalid.\n"));
    return EFI_DEVICE_ERROR;
  }

  PciClass.BaseCode = PciSegmentRead8 (Private->HostBase + PCI_CLASSCODE_OFFSET + 2);
  PciClass.SubClassCode = PciSegmentRead8 (Private->HostBase + PCI_CLASSCODE_OFFSET + 1);

  if ((PciClass.BaseCode != PCI_CLASS_MASS_STORAGE) ||
      (PciClass.SubClassCode != PCI_CLASS_MASS_STORAGE_SATADPA)
      ) {
    DEBUG ((DEBUG_ERROR, "SataHostDriver : BaseCode(0x%x) or ClassCode(0x%x) is not supported\n", PciClass.BaseCode, PciClass.SubClassCode));
    return EFI_UNSUPPORTED;
  }

  MmioBar = PcdGet32 (PcdSataPciHostControllerMmioBase);
  ASSERT (MmioBar != 0xFFFFFFFF);

  PciSegmentAnd16 (Private->HostBase + PCI_COMMAND_OFFSET, (UINT16)~(EFI_PCI_COMMAND_BUS_MASTER | EFI_PCI_COMMAND_MEMORY_SPACE));
  PciSegmentWrite32 (Private->HostBase + R_SATA_CFG_AHCI_BAR,  MmioBar);
  PciSegmentOr16 (Private->HostBase + PCI_COMMAND_OFFSET, (EFI_PCI_COMMAND_BUS_MASTER | EFI_PCI_COMMAND_MEMORY_SPACE));

  Private->MmioBase = PciSegmentRead32 (Private->HostBase + R_SATA_CFG_AHCI_BAR);
  DEBUG ((DEBUG_INFO, "SataHostDriver : MmioBaseAddress = 0x%08x\n", Private->MmioBase));

  return EFI_SUCCESS;
}

/**
  Initialize Ata Controller

  @param[in]  FileHandle           Handle of the file being invoked.
  @param[in]  PeiServices          General purpose services available to every PEIM.

  @retval  EFI_SUCCESS             Successfully initialize the controller.
  @retval  Others                  Failed to initialize the controller

**/
EFI_STATUS
EFIAPI
InitializeAtaController (
  IN EFI_PEI_FILE_HANDLE        FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS                       Status;
  PEI_SATA_HC_PRIVATE_DATA         *Private;

  Private = (PEI_SATA_HC_PRIVATE_DATA *) AllocateZeroPool (sizeof (PEI_SATA_HC_PRIVATE_DATA));
  if (Private == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Private->Signature            = PEI_ATA_HC_PEI_SIGNATURE;
  Private->AtaControllerPpi     = mAtaControllerPpi;
  Private->PpiList              = mPpiList;
  Private->PpiList.Ppi          = &Private->AtaControllerPpi;

  //
  // Assign resources and enable controller
  //
  Status = InitializeAtaDirectConnect (Private);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Disable memory space and BME at EndOfPei
  //
  Status = PeiServicesNotifyPpi (&mEndOfPeiNotifyList);

  //
  // Install Ata host PPI
  //
  Status = PeiServicesInstallPpi (&Private->PpiList);

  return Status;
}
