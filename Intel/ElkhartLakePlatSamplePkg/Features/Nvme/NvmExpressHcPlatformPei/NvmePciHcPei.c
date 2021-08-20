/** @file
  NvmePciHcPei driver is used to provide platform-dependent info, mainly NvmExpress host controller MMIO base.
  This PEIM produces NvmeHostControllerPpi instance which would be consumed by NvmExpressPei.

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

#include "NvmePciHcPei.h"
#include <Library/PchInfoLib.h>
#include <Library/PchPcieRpLib.h>
#include <PcieRegs.h>
#include <Register/PchRegs.h>
#include <Register/PchPcieRpRegs.h>

PEI_NVME_CONTROLLER_PPI  mNvmExpressControllerPpi = { GetNvmeHcMmioBar };

EFI_PEI_PPI_DESCRIPTOR   mPpiList = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gPeiNvmExpressControllerPpiGuid,
  &mNvmExpressControllerPpi
};

/**
  This function handles NVME HostController task at the end of PEI

  @param[in]  PeiServices  Pointer to PEI Services Table.
  @param[in]  NotifyDesc   Pointer to the descriptor for the Notification event that
                           caused this function to execute.
  @param[in]  Ppi          Pointer to the PPI data associated with this function.

  @retval     EFI_SUCCESS  The function completes successfully
  @retval     others

**/
EFI_STATUS
EFIAPI
NvmeHostControllerEndOfPei (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  );

static EFI_PEI_NOTIFY_DESCRIPTOR  mEndOfPeiNotifyList = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiEndOfPeiSignalPpiGuid,
  (EFI_PEIM_NOTIFY_ENTRY_POINT) NvmeHostControllerEndOfPei
};

/**
  This function assigns temporary bus number to PCIe bus .

  @param[in] RpBase      PCIe root port baseaddress.
  @param[in] TempPciBus  PciBus number to be assigned.

**/
VOID
NvmePeiHcAssignTempBus (
  IN UINT64 RpBase,
  IN UINT8  TempPciBus
  )
{
  UINT64 EpBase;
  //
  // Assign bus numbers to the root port
  //
  PciSegmentAndThenOr32 (
    RpBase + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET,
    (UINT32) ~B_PCI_BRIDGE_BNUM_SBBN_SCBN,
    ((UINT32) (TempPciBus << 8)) | ((UINT32) (TempPciBus << 16))
    );
  //
  // A config write is required in order for the device to re-capture the Bus number,
  // according to PCI Express Base Specification, 2.2.6.2
  // Write to a read-only register VendorID to not cause any side effects.
  //
  EpBase = PCI_SEGMENT_LIB_ADDRESS (DEFAULT_PCI_SEGMENT_NUMBER_PCH, TempPciBus, 0, 0, 0);
  PciSegmentWrite16 (EpBase + PCI_VENDOR_ID_OFFSET, 0);
}

/**
  Clear temporary bus usage.

  @param[in] RpBase     PCIe root port baseaddress.

**/
VOID
NvmePeiHcClearTempBus (
  IN UINT64 RpBase
  )
{
  PciSegmentAnd32 (
    RpBase + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET,
    (UINT32) ~B_PCI_BRIDGE_BNUM_SBBN_SCBN
    );
}

/**
  Get the address of endpoint (NVME) BAR 0.

  @param[in] EpBase     Endpoint (NVME) baseaddress.

  @retval    UINT64     BAR 0 of the endpoint device

**/
UINT64
GetNvmeBar0MmioSize (
  IN UINT64 EpBase
  )
{
  UINT32         Size;
  UINT64         MmioSize;

  Size     = 0;
  MmioSize = 0;

  PciSegmentAnd16 (EpBase + PCI_COMMAND_OFFSET, (UINT16)~(EFI_PCI_COMMAND_BUS_MASTER | EFI_PCI_COMMAND_MEMORY_SPACE));
  if ((PciSegmentRead32 (EpBase + PCI_BASE_ADDRESSREG_OFFSET) & 0xFFFFFFF0) != 0) {
    //
    // There should be no other driver to control this device at the same time.
    // Assume BAR0 should be 0. So if not, assert the system.
    //
    DEBUG ((DEBUG_ERROR, "Nvme BAR 0 has been assigned as 0x%x.\n", PciSegmentRead32 (EpBase + PCI_BASE_ADDRESSREG_OFFSET)));
    ASSERT (FALSE);
  }

  PciSegmentWrite32 ((EpBase + PCI_BASE_ADDRESSREG_OFFSET), 0xFFFFFFFF);
  Size = PciSegmentRead32 (EpBase + PCI_BASE_ADDRESSREG_OFFSET);
  PciSegmentWrite32 ((EpBase + PCI_BASE_ADDRESSREG_OFFSET), 0); // Clear BAR0 to 0

  if ((Size & BIT0) != 0) {
    DEBUG ((DEBUG_ERROR, "Nvme BAR 0 should not be an I/O space\n"));
    ASSERT (FALSE);
    return 0;
  }

  switch (Size & 0x07) {
    case 0x0:
      //
      // Memory space: anywhere in 32 bit address space
      //
      MmioSize = (~(Size & 0xFFFFFFF0)) + 1;
      break;
    case 0x4:
      //
      // Memory space: anywhere in 64 bit address space
      //
      if (PciSegmentRead32 (EpBase + PCI_BASE_ADDRESSREG_OFFSET + 4) != 0) {
        //
        // There should be no other driver to control this device at the same time.
        // Assume BAR0 should be 0. So if not, assert the system.
        //
        DEBUG ((DEBUG_ERROR, "Nvme BAR 0 (upper 32 bit) has been assigned as 0x%x.\n", PciSegmentRead32 (EpBase + PCI_BASE_ADDRESSREG_OFFSET + 4)));
        ASSERT (FALSE);
      }

      MmioSize = Size & 0xFFFFFFF0;
      PciSegmentWrite32 ((EpBase + PCI_BASE_ADDRESSREG_OFFSET + 4), 0xFFFFFFFF);
      Size = PciSegmentRead32 (EpBase + PCI_BASE_ADDRESSREG_OFFSET + 4);
      //
      // Fix the length to support some spefic 64 bit BAR
      //
      Size |= ((UINT32)(-1) << HighBitSet32 (Size));
      //
      // Calculate the size of 64bit bar
      //
      MmioSize  |= LShiftU64 ((UINT64) Size, 32);
      MmioSize  = (~(MmioSize)) + 1;
      //
      // Clean the high 32bits of this 64bit BAR to 0 as we only allow a 32bit BAR.
      //
      PciSegmentWrite32 (EpBase + PCI_BASE_ADDRESSREG_OFFSET + 4, 0);

      break;
    default:
      //
      // Unknown BAR type
      //
      ASSERT (FALSE);
      break;
  }

  return MmioSize;
}

/**
  This function handles NVME HostController task at the end of PEI

  @param[in]  PeiServices  Pointer to PEI Services Table.
  @param[in]  NotifyDesc   Pointer to the descriptor for the Notification event that
                           caused this function to execute.
  @param[in]  Ppi          Pointer to the PPI data associated with this function.

  @retval     EFI_SUCCESS  The function completes successfully
  @retval     others

**/
EFI_STATUS
EFIAPI
NvmeHostControllerEndOfPei (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  )
{
  NVM_EXPRESS_HC_PEI_PRIVATE_DATA  *Private;
  UINTN                            Index;
  UINT32                           Data32;
  UINT8                            SecondaryBus;
  UINT64                           RpBase;
  UINT64                           EpBase;

  Private = NVM_EXPRESS_HC_PEI_PRIVATE_DATA_FROM_THIS_NOTIFY (NotifyDescriptor);

  for (Index = 0; Index < Private->TotalNvmeHcs; Index++) {
    ASSERT (Private->RpBase[Index] > 0);
    RpBase = Private->RpBase[Index];
    //
    // Get endpoint base
    //
    Data32 = PciSegmentRead32 (RpBase + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET);
    SecondaryBus = (UINT8)((Data32 & B_PCI_BRIDGE_BNUM_SCBN) >> 8);
    ASSERT (SecondaryBus > 0);
    EpBase = PCI_SEGMENT_LIB_ADDRESS (DEFAULT_PCI_SEGMENT_NUMBER_PCH, SecondaryBus, 0, 0, 0);

    //
    // Disable endpoint memory space and BME
    //
    PciSegmentAnd16 (EpBase + PCI_COMMAND_OFFSET, (UINT16) ~(EFI_PCI_COMMAND_MEMORY_SPACE + EFI_PCI_COMMAND_BUS_MASTER));
    PciSegmentWrite32 (EpBase + PCI_BASE_ADDRESSREG_OFFSET, 0);

    //
    // Disable root port memory space and BME
    //
    PciSegmentAnd16 (RpBase + PCI_COMMAND_OFFSET, (UINT16) ~(EFI_PCI_COMMAND_MEMORY_SPACE + EFI_PCI_COMMAND_BUS_MASTER));
    PciSegmentWrite32 (RpBase + 0x20, 0);

    //
    // Clear temporary bus
    //
    NvmePeiHcClearTempBus (Private->RpBase[Index]);
  }

  return EFI_SUCCESS;
}

/**
  Get the MMIO base address of NvmExpress host controller.

  @param[in]     PeiServices         Describes the list of possible PEI Services.
  @param[in]     This                The protocol instance pointer.
  @param[in]     NvmeControllerId    The ID of the NvmExpress host controller.
  @param[out]    BaseAddress         The base address of Nvme's MMIO

  @retval EFI_SUCCESS                The operation succeeds.
  @retval EFI_INVALID_PARAMETER      The parameters are invalid.

**/
EFI_STATUS
EFIAPI
GetNvmeHcMmioBar (
  IN  EFI_PEI_SERVICES                           **PeiServices,
  IN  PEI_NVME_CONTROLLER_PPI                   *This,
  IN  UINT8                                      NvmeControllerId,
  OUT UINTN                                      *BaseAddress
  )
{
  NVM_EXPRESS_HC_PEI_PRIVATE_DATA  *Private;

  if ((This == NULL) || (BaseAddress == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  Private = NVM_EXPRESS_HC_PEI_PRIVATE_DATA_FROM_THIS (This);

  if (NvmeControllerId >= Private->TotalNvmeHcs) {
    return EFI_INVALID_PARAMETER;
  }

  *BaseAddress = Private->MmioBar[NvmeControllerId];

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
InitializeNvmeHcPeim (
  IN EFI_PEI_FILE_HANDLE       FileHandle,
  IN CONST EFI_PEI_SERVICES    **PeiServices
  )
{
  EFI_STATUS                        Status;
  EFI_BOOT_MODE                     BootMode;
  NVM_EXPRESS_HC_PEI_PRIVATE_DATA   *Private;
  UINT8                             RpIndex;
  UINTN                             RpDev;
  UINTN                             RpFun;
  UINT8                             BaseClassCode;
  UINT8                             SubClassCode;
  UINT8                             ProgInt;
  UINT64                            RpBase;
  UINT64                            EpBase;
  UINTN                             MmioBaseAddress;
  UINTN                             MmioLimitAddress;
  UINT64                            MmioSize;
  UINT8                             TempPciBus;
  UINT8                             TempPciBusLimit;

  DEBUG ((DEBUG_INFO, "NvmePciHcPei Entry.\n"));

  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR (Status);
  if (BootMode == BOOT_ON_S3_RESUME) {
    return EFI_UNSUPPORTED;
  }

  //
  // Shadow this PEIM to run from memory
  //
  if (!EFI_ERROR (PeiServicesRegisterForShadow (FileHandle))) {
    return EFI_SUCCESS;
  }

  DEBUG ((DEBUG_INFO, "NvmePciHcPei in shadow.\n"));

  Private = (NVM_EXPRESS_HC_PEI_PRIVATE_DATA *) AllocateZeroPool (sizeof (NVM_EXPRESS_HC_PEI_PRIVATE_DATA));
  if (Private == NULL) {
    DEBUG ((DEBUG_ERROR, "Failed to allocate memory for NVM_EXPRESS_HC_PEI_PRIVATE_DATA! \n"));
    return EFI_OUT_OF_RESOURCES;
  }

  Private->Signature             = NVM_EXPRESS_HC_PEI_SIGNATURE;
  Private->NvmeHostControllerPpi = mNvmExpressControllerPpi;
  Private->PpiList               = mPpiList;
  Private->PpiList.Ppi           = &Private->NvmeHostControllerPpi;
  Private->EndOfPeiNotifyList    = mEndOfPeiNotifyList;

  TempPciBus       = PcdGet8 (PcdNvmePciHostControllerPciBusMin);
  TempPciBusLimit  = PcdGet8 (PcdNvmePciHostControllerPciBusMax);
  MmioBaseAddress  = PcdGet32 (PcdNvmePciHostControllerMmioBase);
  MmioLimitAddress = PcdGet32 (PcdNvmePciHostControllerMmioLimit);

  ASSERT (TempPciBus       != 0xFF);
  ASSERT (TempPciBusLimit  != 0xFF);
  ASSERT (MmioBaseAddress  != 0xFFFFFFFF);
  ASSERT (MmioLimitAddress != 0xFFFFFFFF);

  for (RpIndex = 0; RpIndex < GetPchMaxPciePortNum (); RpIndex++) {
    Status = GetPchPcieRpDevFun (RpIndex, &RpDev, &RpFun);
    ASSERT_EFI_ERROR (Status);

    RpBase = PCI_SEGMENT_LIB_ADDRESS (DEFAULT_PCI_SEGMENT_NUMBER_PCH, DEFAULT_PCI_BUS_NUMBER_PCH, (UINT32) RpDev, (UINT32) RpFun, 0);

    //
    // 1. Check if root port exists and endpoint device is present
    //
    if ((PciSegmentRead16 (RpBase + PCI_VENDOR_ID_OFFSET) == 0xFFFF) ||
        ((PciSegmentRead16 (RpBase + R_PCH_PCIE_CFG_SLSTS) & B_PCIE_SLSTS_PDS) == 0)) {
      continue;
    }

    ASSERT ((PciSegmentRead8 (RpBase + PCI_HEADER_TYPE_OFFSET) & HEADER_LAYOUT_CODE) == HEADER_TYPE_PCI_TO_PCI_BRIDGE);

    //
    // 2. Assign temprary bus to access endpoint
    //
    NvmePeiHcAssignTempBus (RpBase, TempPciBus);

    EpBase = PCI_SEGMENT_LIB_ADDRESS (DEFAULT_PCI_SEGMENT_NUMBER_PCH, TempPciBus, 0, 0, 0);

    //
    // 3. Check endpoint device type
    //
    BaseClassCode = PciSegmentRead8 (EpBase + PCI_CLASSCODE_OFFSET + 2);
    SubClassCode  = PciSegmentRead8 (EpBase + PCI_CLASSCODE_OFFSET + 1);
    ProgInt       = PciSegmentRead8 (EpBase + PCI_CLASSCODE_OFFSET);

    if ((BaseClassCode != PCI_CLASS_MASS_STORAGE) ||
        (SubClassCode != PCI_CLASS_MASS_STORAGE_SOLID_STATE) ||
        (ProgInt != PCI_IF_MASS_STORAGE_SOLID_STATE_ENTERPRISE_NVMHCI)) {
      //
      // This is not a NVME device.
      //
      NvmePeiHcClearTempBus (RpBase);
      continue;
    }

    DEBUG ((DEBUG_INFO, "Nvme device found:\n"));
    DEBUG ((DEBUG_INFO, " Root port Dev=0x%x, Fun=0x%x.\n",RpDev, RpFun));
    DEBUG ((DEBUG_INFO, " Endpoint Bus=0x%x\n", TempPciBus));

    //
    // 4. Get MMIO size required for endpoint device
    //
    MmioSize = GetNvmeBar0MmioSize (EpBase);
    //
    // 5. Align MMIO size to a 1 MB boundary for PCI bridge
    //
    MmioSize = ALIGN_VALUE (MmioSize, SIZE_1MB);
    if ((MmioBaseAddress + MmioSize) > MmioLimitAddress) {
      //
      // Required resource execeeds the limitation.
      //
      DEBUG ((DEBUG_ERROR, "There no enough MMIO space reserved for the endpoint device (%x, 0, 0)\n", TempPciBus));
      NvmePeiHcClearTempBus (RpBase);
      continue;
    }

    //
    // 6. Assign memory base and limit on root port and enable memory decode
    //
    DEBUG ((DEBUG_INFO, "Assign MMIO baseaddres: 0x%x\n", MmioBaseAddress));

    PciSegmentAnd16 (RpBase + PCI_COMMAND_OFFSET, (UINT16) ~(EFI_PCI_COMMAND_BUS_MASTER | EFI_PCI_COMMAND_MEMORY_SPACE));
    PciSegmentWrite16 (RpBase + 0x20, (MmioBaseAddress >> 16));
    PciSegmentWrite16 (RpBase + 0x22, (UINT16)((MmioBaseAddress + MmioSize - 1) >> 16));

    PciSegmentWrite16 (RpBase + 0x24,  0xFFFF);
    PciSegmentWrite16 (RpBase + 0x26,  0);

    PciSegmentWrite32 (RpBase + 0x28,  0xFFFFFFFF);
    PciSegmentWrite32 (RpBase + 0x2C,  0);

    PciSegmentOr16 (RpBase + PCI_COMMAND_OFFSET, (EFI_PCI_COMMAND_BUS_MASTER | EFI_PCI_COMMAND_MEMORY_SPACE));

    //
    // 7. Assign memory resource on endpoint and enable memory decode
    //
    PciSegmentAnd16 (EpBase + PCI_COMMAND_OFFSET, (UINT16) ~(EFI_PCI_COMMAND_BUS_MASTER | EFI_PCI_COMMAND_MEMORY_SPACE));
    PciSegmentWrite32 (EpBase + PCI_BASE_ADDRESSREG_OFFSET, MmioBaseAddress);
    PciSegmentOr16 (EpBase + PCI_COMMAND_OFFSET, (EFI_PCI_COMMAND_BUS_MASTER | EFI_PCI_COMMAND_MEMORY_SPACE));

    Private->RpBase[Private->TotalNvmeHcs] = RpBase;
    Private->MmioBar[Private->TotalNvmeHcs] = MmioBaseAddress;
    Private->TotalNvmeHcs++;
    TempPciBus++;
    MmioBaseAddress = MmioBaseAddress + (UINTN) MmioSize;

    if ((Private->TotalNvmeHcs >= MAX_NVM_EXPRESS_HCS) || (TempPciBus > TempPciBusLimit) || (MmioBaseAddress >= MmioLimitAddress)) {
      DEBUG ((DEBUG_INFO, "There's no enough resource reserved for other NVME devices.\n"));
      break;
    }
  }

  //
  // Disable memory space and BME at EndOfPei
  //
  Status = PeiServicesNotifyPpi (&Private->EndOfPeiNotifyList);
  ASSERT_EFI_ERROR (Status);

  //
  // Install NvmExpress Host Controller PPI
  //
  Status = PeiServicesInstallPpi (&Private->PpiList);
  ASSERT_EFI_ERROR (Status);

  return Status;
}
