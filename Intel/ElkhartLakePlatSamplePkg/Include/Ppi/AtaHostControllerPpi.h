/** @file
  The PEI_ATA_HOST_CONTROLLER_PPI provides platform information of SATA controller in PEI phase.

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

#ifndef _PEI_ATA_HOST_CONTROLLER_PPI_H_
#define _PEI_ATA_HOST_CONTROLLER_PPI_H_

///
/// Global ID for the _PEI_ATA_HOST_CONTROLLER_PPI.
///
#define PEI_ATA_HOST_CONTROLLER_PPI_GUID \
  { \
    0xb659e3f2, 0xd5ab, 0x4bfb, { 0x90, 0x42, 0xff, 0x52, 0x86, 0x83, 0x41, 0xf1} \
  }

//
// Forward declaration for the EDKII_PEI_NVME_CONTROLLER_PPI.
//
typedef struct _PEI_ATA_HOST_CONTROLLER_PPI  PEI_ATA_HOST_CONTROLLER_PPI;

/**
  Get the MMIO base address of ATA host controller.

  @param[in]     PeiServices         Describes the list of possible PEI Services.
  @param[in]     This                The protocol instance pointer.
  @param[in]     AtaControllerId     The ID of the ATA host controller.
  @param[out]    BaseAddress         The base address of controller's MMIO space

  @retval EFI_SUCCESS                The operation succeeds.
  @retval EFI_INVALID_PARAMETER      The parameters are invalid.

**/
typedef
EFI_STATUS
(EFIAPI *PEI_GET_ATA_CONTROLLER_INFO)(
  IN  EFI_PEI_SERVICES                           **PeiServices,
  IN  PEI_ATA_HOST_CONTROLLER_PPI                *This,
  IN  UINT8                                      AtaControllerId,
  OUT UINTN                                      *BaseAddress
  );

//
// This PPI contains a set of services to interact with the Ata host controller.
//
struct _PEI_ATA_HOST_CONTROLLER_PPI {
  PEI_GET_ATA_CONTROLLER_INFO GetAtaControllerInfo;
};

extern EFI_GUID gPeiAtaHostControllerPpiGuid;

#endif
