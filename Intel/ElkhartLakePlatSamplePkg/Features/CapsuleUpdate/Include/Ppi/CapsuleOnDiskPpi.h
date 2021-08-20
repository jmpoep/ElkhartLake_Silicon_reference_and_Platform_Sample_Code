/** @file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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

#ifndef _CAPSULE_ON_DISK_H_
#define _CAPSULE_ON_DISK_H_

///
/// Global ID for the PEI_CAPSULE_ON_DISK_PPI.
///
#define PEI_CAPSULE_ON_DISK_PPI_GUID \
  { \
    0x9a289000, 0x09e2, 0x425c, {0xbe, 0xf4, 0x5f, 0x58, 0xea, 0x99, 0x2d, 0x4c } \
  }

//
// Forward declaration for the CAPSULE_ON_DISK_PPI.
//
typedef struct PEI_CAPSULE_ON_DISK_PPI  PEI_CAPSULE_ON_DISK_PPI;

/**
  Get the Capsule binary from storage like UFS/NVME.

  @param[in]     PeiServices         Describes the list of possible PEI Services.
  @param[in]     This                The protocol instance pointer.

  @retval EFI_SUCCESS                The operation succeeds.
  @retval EFI_INVALID_PARAMETER      The parameters are invalid.

**/
typedef
EFI_STATUS
(EFIAPI *PEI_GET_CAPSULE_ON_DISK)(
  IN  EFI_PEI_SERVICES                           **PeiServices,
  IN  PEI_CAPSULE_ON_DISK_PPI                    *This
  );

//
// This PPI contains a set of services to read capsule bibary from storage.
//
struct PEI_CAPSULE_ON_DISK_PPI {
  PEI_GET_CAPSULE_ON_DISK  GetCapsuleFromDisk;
};

extern EFI_GUID gEfiPeiCapsuleOnDiskPpiGuid;

#endif
