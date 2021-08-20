/** @file
  Private Header file for NvmExpress PCI host controller PEIM

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

#ifndef _NVME_PCI_HC_PEI_H_
#define _NVME_PCI_HC_PEI_H_

#include <PiPei.h>

#include <Ppi/NvmExpressController.h>

#include <IndustryStandard/Pci.h>

#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PciSegmentLib.h>

#define NVM_EXPRESS_HC_PEI_SIGNATURE    SIGNATURE_32 ('N', 'V', 'M', 'E')

#define MAX_NVM_EXPRESS_HCS        8

typedef struct {
  UINTN                            Signature;
  PEI_NVME_CONTROLLER_PPI          NvmeHostControllerPpi;
  EFI_PEI_PPI_DESCRIPTOR           PpiList;
  EFI_PEI_NOTIFY_DESCRIPTOR        EndOfPeiNotifyList;
  UINTN                            TotalNvmeHcs;
  UINTN                            MmioBar[MAX_NVM_EXPRESS_HCS];
  UINT64                           RpBase[MAX_NVM_EXPRESS_HCS];
} NVM_EXPRESS_HC_PEI_PRIVATE_DATA;

#define NVM_EXPRESS_HC_PEI_PRIVATE_DATA_FROM_THIS(a)  CR (a, NVM_EXPRESS_HC_PEI_PRIVATE_DATA, NvmeHostControllerPpi, NVM_EXPRESS_HC_PEI_SIGNATURE)
#define NVM_EXPRESS_HC_PEI_PRIVATE_DATA_FROM_THIS_NOTIFY(a)  CR (a, NVM_EXPRESS_HC_PEI_PRIVATE_DATA, EndOfPeiNotifyList, NVM_EXPRESS_HC_PEI_SIGNATURE)

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
  IN  PEI_NVME_CONTROLLER_PPI                    *This,
  IN  UINT8                                      NvmeControllerId,
  OUT UINTN                                      *BaseAddress
  );
#endif
