/** @file
  DXE PSS Operation Library File

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#include <Uefi.h>
#include <PiDxe.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <IndustryStandard/Pci.h>
#include <Protocol/PciIo.h>
#include <Library/SerialIoAccessLib.h>
#include <Protocol/I2cMaster.h>
#include <Pi/PiI2c.h>
#include <Library/PssLib.h>
#include <Library/I2cAccessLib.h>
#include <Library/PciSegmentLib.h>
#include <Register/PchRegs.h>
#include <Register/SerialIoRegs.h>
#include <Register/SerialIoI2cRegs.h>

/**
  Read data from PSS chip.

  @param[out]  Buffer
  @param[in]   Address
  @param[in]   Size

  @retval  EFI_STATUS
**/
EFI_STATUS
EFIAPI
ReadPssData (
  UINT8     *Buffer,
  UINT32    Address,
  UINT32    Size
  )
{
  EFI_STATUS      Status;
  UINT8           WriBuf [2] ={0, 0};
  UINT64          MmioBase;
  UINT64          PciRegisterAddress;
  UINT8           PciPmeCtrlSts;
  UINT8           PciCommand;
  UINT32          MemResetState;

  if (Size == 0) {
    return EFI_SUCCESS;
  }

  if (Buffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  DEBUG((DEBUG_INFO, "ReadPssData ()\n"));

  PciRegisterAddress   = GetSerialIoI2cPciCfg (PcdGet8 (PcdPssI2cBusNumber));
  if (PciSegmentRead16 (PciRegisterAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    return EFI_UNSUPPORTED;
  }
  MmioBase      = GetSerialIoBar (PciRegisterAddress);
  if ((MmioBase == 0xFFFFFFFFFFFFF000ULL) || (MmioBase == 0xFFFFF000ULL) || (MmioBase == 0x0)) {
    DEBUG ((DEBUG_ERROR, "ReadPssData () - Invalid MmioBase\n"));
    return EFI_UNSUPPORTED;
  }
  //
  // Enable the PCI memory resource if it's disabled.
  //
  PciCommand    = PciSegmentRead8 (PciRegisterAddress + PCI_COMMAND_OFFSET);
  PciPmeCtrlSts = PciSegmentRead8 (PciRegisterAddress + R_SERIAL_IO_CFG_PME_CTRL_STS);

  if ((PciCommand & EFI_PCI_COMMAND_MEMORY_SPACE) == 0) {
    PciSegmentOr8 (PciRegisterAddress + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);
  }

  if ((PciPmeCtrlSts & (B_SERIAL_IO_CFG_PME_CTRL_STS_PWR_ST)) == (B_SERIAL_IO_CFG_PME_CTRL_STS_PWR_ST)) {
    PciSegmentAnd8 (PciRegisterAddress + R_SERIAL_IO_CFG_PME_CTRL_STS, (UINT8) (~B_SERIAL_IO_CFG_PME_CTRL_STS_PWR_ST));
  }

  MemResetState = MmioRead32 (MmioBase + R_SERIAL_IO_MEM_PPR_RESETS);
  if (MemResetState == 0) {
    MmioOr32 (MmioBase + R_SERIAL_IO_MEM_PPR_RESETS,
      B_SERIAL_IO_MEM_PPR_RESETS_FUNC | B_SERIAL_IO_MEM_PPR_RESETS_APB | B_SERIAL_IO_MEM_PPR_RESETS_IDMA);
  }

  WriBuf [0] = (UINT8) (Address >> 8);
  WriBuf [1] = (UINT8) (Address & 0xFF);
  Status = I2cWriteRead (MmioBase, PcdGet8 (PcdPssI2cSlaveAddress), 2, WriBuf, (UINT8) Size, Buffer, WAIT_1_SECOND);

  //
  // Restore Device Settings
  //
  MmioWrite32 (MmioBase + R_SERIAL_IO_MEM_PPR_RESETS, MemResetState);
  PciSegmentWrite8 (PciRegisterAddress + PCI_COMMAND_OFFSET, PciCommand);
  PciSegmentWrite8 (PciRegisterAddress + B_SERIAL_IO_CFG_PME_CTRL_STS_PWR_ST, PciPmeCtrlSts);

  return Status;
}

/**
  Write data to PSS chip.

  @param[in]  Buffer
  @param[in]  Address
  @param[in]  Size

  @retval  EFI_STATUS
**/
EFI_STATUS
EFIAPI
WritePssData (
  UINT8     *Buffer,
  UINT32    Address,
  UINTN     Size
  )
{
  EFI_STATUS      Status;
  UINT8           WriBuf [2] ={0, 0};
  UINT64          MmioBase;
  UINT64          PciRegisterAddress;
  UINT8           PciPmeCtrlSts;
  UINT8           PciCommand;
  UINT32          MemResetState;

  if (Size == 0) {
    return EFI_SUCCESS;
  }

  if (Buffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  DEBUG ((DEBUG_INFO, "WritePssData()\n"));

  PciRegisterAddress   = GetSerialIoI2cPciCfg (PcdGet8 (PcdPssI2cBusNumber));
  if (PciSegmentRead16 (PciRegisterAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    return EFI_UNSUPPORTED;
  }
  MmioBase      = GetSerialIoBar (PciRegisterAddress);
  if ((MmioBase == 0xFFFFFFFFFFFFF000ULL) || (MmioBase == 0xFFFFF000ULL) || (MmioBase == 0x0)) {
    DEBUG ((DEBUG_ERROR, "WritePssData () - Invalid MmioBase\n"));
    return EFI_UNSUPPORTED;
  }
  //
  // Enable the PCI memory resource if it's disabled.
  //
  PciCommand    = PciSegmentRead8 (PciRegisterAddress + PCI_COMMAND_OFFSET);
  PciPmeCtrlSts = PciSegmentRead8 (PciRegisterAddress + R_SERIAL_IO_CFG_PME_CTRL_STS);

  if ((PciCommand & EFI_PCI_COMMAND_MEMORY_SPACE) == 0) {
    PciSegmentOr8 (PciRegisterAddress + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);
  }

  if ((PciPmeCtrlSts & (B_SERIAL_IO_CFG_PME_CTRL_STS_PWR_ST)) == (B_SERIAL_IO_CFG_PME_CTRL_STS_PWR_ST)) {
    PciSegmentAnd8 (PciRegisterAddress + R_SERIAL_IO_CFG_PME_CTRL_STS, (UINT8) (~B_SERIAL_IO_CFG_PME_CTRL_STS_PWR_ST));
  }

  MemResetState = MmioRead32 (MmioBase + R_SERIAL_IO_MEM_PPR_RESETS);
  if (MemResetState == 0) {
    MmioOr32 (MmioBase + R_SERIAL_IO_MEM_PPR_RESETS,
      B_SERIAL_IO_MEM_PPR_RESETS_FUNC | B_SERIAL_IO_MEM_PPR_RESETS_APB | B_SERIAL_IO_MEM_PPR_RESETS_IDMA);
  }

  WriBuf [0] = (UINT8) (Address >> 8);
  WriBuf [1] = (UINT8) (Address & 0xFF);
  Status = I2cWriteRead (MmioBase, PcdGet8 (PcdPssI2cSlaveAddress), 2, WriBuf, (UINT8) Size, Buffer, WAIT_1_SECOND);

  //
  // Restore Device Settings
  //
  MmioWrite32 (MmioBase + R_SERIAL_IO_MEM_PPR_RESETS, MemResetState);
  PciSegmentWrite8 (PciRegisterAddress + PCI_COMMAND_OFFSET, PciCommand);
  PciSegmentWrite8 (PciRegisterAddress + B_SERIAL_IO_CFG_PME_CTRL_STS_PWR_ST, PciPmeCtrlSts);

  return Status;
}

/**
  Check PSS chip status.

  @param[in]  none

  @retval  EFI_STATUS
**/
EFI_STATUS
EFIAPI
PssDetect (
  VOID
  )
{
  EFI_STATUS    Status;
  UINT8         PssData[4];

  //
  // Read the chip's Class ID from the TID bank, it should be 0xE2 (Gen2)
  // Check whether the PSS IC is Monza X-8K
  //
  ZeroMem (PssData, sizeof(PssData));
  Status = ReadPssData(&PssData[0], PSS_BASE_ADDR_CLASSID, 4);
  DEBUG((EFI_D_INFO, "Get PSS Class ID: %2X-%2X-%2X-%2X\n",\
         PssData[0], PssData[1], PssData[2], PssData[3]));
  if (!EFI_ERROR(Status)) {
    if ((PssData[0] == PSS_CHIP_CLASS_ID) &&
        ((PssData [2] & 0x0F) == PSS_CHIP_TID_MODEL_HIGH) &&
        (PssData [3] == PSS_CHIP_TID_MODEL_LOW)
     ) {
    return EFI_SUCCESS;  //Monza X-8K
  } else {
      return EFI_NOT_FOUND; // Other device, handled as not found.
    }
  } else {
    return Status;
  }
}
