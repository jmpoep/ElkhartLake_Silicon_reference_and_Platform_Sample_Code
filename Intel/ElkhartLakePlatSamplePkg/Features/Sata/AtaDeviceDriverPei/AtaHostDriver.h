/** @file
  Install Pei phase ATA host contoller PPI.

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

#ifndef _ATA_HOST_DRIVER_H
#define _ATA_HOST_DRIVER_H

#include <Uefi.h>

#include <Library/DebugLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PciSegmentLib.h>
#include <IndustryStandard/Pci.h>
#include <Ppi/AtaHostControllerPpi.h>
#include <Register/PchRegs.h>
#include <Register/SataRegs.h>
#include <Library/SataLib.h>

#define PEI_ATA_HC_PEI_SIGNATURE  SIGNATURE_32 ('p', 'a', 't', 'h')

typedef struct {
  UINTN                           Signature;
  PEI_ATA_HOST_CONTROLLER_PPI     AtaControllerPpi;
  EFI_PEI_PPI_DESCRIPTOR          PpiList;
  UINTN                           HostBase;
  UINTN                           MmioBase;
} PEI_SATA_HC_PRIVATE_DATA;

#define PEI_ATA_HC_PEI_PRIVATE_DATA_FROM_THIS(a)  \
    CR (a, PEI_SATA_HC_PRIVATE_DATA, AtaControllerPpi, PEI_ATA_HC_PEI_SIGNATURE)


//
// PCI Class Code structure
//
typedef struct {
  UINT8 PI;
  UINT8 SubClassCode;
  UINT8 BaseCode;
} PCI_CLASSC;

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
  );

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
  );

#endif
