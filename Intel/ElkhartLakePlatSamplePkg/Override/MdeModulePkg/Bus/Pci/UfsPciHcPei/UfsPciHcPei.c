/** @file
  UfsPciHcPei driver is used to provide platform-dependent info, mainly UFS host controller
  MMIO base, to upper layer UFS drivers.

  Copyright (c) 2014 - 2018, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php.

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "UfsPciHcPei.h"

EDKII_UFS_HOST_CONTROLLER_PPI  mUfsHostControllerPpi = { GetUfsHcMmioBar };

EFI_PEI_PPI_DESCRIPTOR   mPpiList = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEdkiiPeiUfsHostControllerPpiGuid,
  &mUfsHostControllerPpi
};

/**
  Get the MMIO base address of UFS host controller.

  @param[in]  This               The protocol instance pointer.
  @param[in]  ControllerId       The ID of the UFS host controller.
  @param[out] MmioBar            Pointer to the UFS host controller MMIO base address.

  @retval EFI_SUCCESS            The operation succeeds.
  @retval EFI_INVALID_PARAMETER  The parameters are invalid.

**/
EFI_STATUS
EFIAPI
GetUfsHcMmioBar (
  IN     EDKII_UFS_HOST_CONTROLLER_PPI *This,
  IN     UINT8                         ControllerId,
     OUT UINTN                         *MmioBar
  )
{
  UFS_HC_PEI_PRIVATE_DATA  *Private;

  if ((This == NULL) || (MmioBar == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  Private = UFS_HC_PEI_PRIVATE_DATA_FROM_THIS (This);

  if (ControllerId >= Private->TotalUfsHcs) {
    return EFI_INVALID_PARAMETER;
  }

  *MmioBar = (UINTN)Private->UfsHcPciAddr[ControllerId];

  return EFI_SUCCESS;
}

/**
  The user code starts with this function.

  @param  FileHandle             Handle of the file being invoked.
  @param  PeiServices            Describes the list of possible PEI Services.

  @retval EFI_SUCCESS            The driver is successfully initialized.
  @retval Others                 Can't initialize the driver.

**/
EFI_STATUS
EFIAPI
InitializeUfsHcPeim (
  IN EFI_PEI_FILE_HANDLE       FileHandle,
  IN CONST EFI_PEI_SERVICES    **PeiServices
  )
{
  EFI_STATUS               Status;
  UINT16                   Bus;
  UINT16                   Device;
  UINT16                   Function;
  UINT32                   Size;
  UINT8                    SubClass;
  UINT8                    BaseClass;
  UFS_HC_PEI_PRIVATE_DATA  *Private;
  UINT32                   MmioBase;

  //
  // Shadow this PEIM to run from memory
  //
  if (!EFI_ERROR (PeiServicesRegisterForShadow (FileHandle))) {
    return EFI_SUCCESS;
  }

  Private = (UFS_HC_PEI_PRIVATE_DATA *) AllocateZeroPool (sizeof (UFS_HC_PEI_PRIVATE_DATA));
  if (Private == NULL) {
    DEBUG ((EFI_D_ERROR, "Failed to allocate memory for UFS_HC_PEI_PRIVATE_DATA! \n"));
    return EFI_OUT_OF_RESOURCES;
  }

  Private->Signature            = UFS_HC_PEI_SIGNATURE;
  Private->UfsHostControllerPpi = mUfsHostControllerPpi;
  Private->PpiList              = mPpiList;
  Private->PpiList.Ppi          = &Private->UfsHostControllerPpi;

  Bus    = PcdGet16 (PcdUfsPciHostControllerBus);
  Device = PcdGet16 (PcdUfsPciHostControllerDevice);
  for (Function = 6; Function < 8; Function++) {
    SubClass  = PciRead8 (PCI_LIB_ADDRESS (Bus, Device, Function, 0x0A));
    BaseClass = PciRead8 (PCI_LIB_ADDRESS (Bus, Device, Function, 0x0B));

    if ((SubClass == 0x09) && (BaseClass == PCI_CLASS_MASS_STORAGE)) {
      //
      // Get the Ufs Pci host controller's MMIO region size.
      //
      PciAnd16 (PCI_LIB_ADDRESS (Bus, Device, Function, PCI_COMMAND_OFFSET), (UINT16)~(EFI_PCI_COMMAND_BUS_MASTER | EFI_PCI_COMMAND_MEMORY_SPACE));
      PciWrite32 (PCI_LIB_ADDRESS (Bus, Device, Function, PCI_BASE_ADDRESSREG_OFFSET), 0xFFFFFFFF);
      Size = PciRead32 (PCI_LIB_ADDRESS (Bus, Device, Function, PCI_BASE_ADDRESSREG_OFFSET));
      Size = (UINT32) (((UINT32)~(Size & 0xFFFFFFF0)) + 1);
      //
      // Assign resource to the Ufs Pci host controller's MMIO BAR.
      // Enable the Ufs Pci host controller by setting BME and MSE bits of PCI_CMD register.
      //
      PciWrite32 (PCI_LIB_ADDRESS (Bus, Device, Function, PCI_BASE_ADDRESSREG_OFFSET), (UINT32)(PcdGet32 (PcdUfsPciHostControllerMmioBase) + Size * Private->TotalUfsHcs));
      PciOr16 (PCI_LIB_ADDRESS (Bus, Device, Function, PCI_COMMAND_OFFSET), (EFI_PCI_COMMAND_BUS_MASTER | EFI_PCI_COMMAND_MEMORY_SPACE));
      MmioBase = PciRead32 (PCI_LIB_ADDRESS (Bus, Device, Function, PCI_BASE_ADDRESSREG_OFFSET));
      //
      // Check if BAR is 64-bit
      //
      if ((MmioBase & 0x06) == 0x04) {
        //
        // Program upper BAR to zero
        //
        PciWrite32 (PCI_LIB_ADDRESS (Bus, Device, Function, (PCI_BASE_ADDRESSREG_OFFSET + 0x04)), (UINT32)(0x00000000));
      }
      MmioBase = MmioBase & 0xFFFFF000;
      DEBUG ((EFI_D_INFO, "UFS Controller %d @ B%d/D%d/F%d, Bar: 0x%X, Size: 0x%X\n", Private->TotalUfsHcs, Bus, Device, Function, MmioBase, Size));
      //
      // Record the allocated Mmio base address.
      //
      Private->UfsHcPciAddr[Private->TotalUfsHcs] = MmioBase + Size * Private->TotalUfsHcs;
      Private->TotalUfsHcs++;
      ASSERT (Private->TotalUfsHcs < MAX_UFS_HCS);
    }
  }

  ///
  /// Install Ufs Host Controller PPI
  ///
  Status = PeiServicesInstallPpi (&Private->PpiList);

  ASSERT_EFI_ERROR (Status);
  return Status;
}
