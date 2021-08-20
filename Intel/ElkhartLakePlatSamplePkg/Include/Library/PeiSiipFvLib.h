/** @file
  Header file for PeiSiipFvFile

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

#ifndef _PEI_SIIP_FV_LIB_H_
#define _PEI_SIIP_FV_LIB_H_

typedef struct {
  UINTN   Address;
  UINTN   Size;
} SIIP_FV_INFO;

/**
  Install Base and Size Info Ppi for Siip Firmware Volume.

  @retval     EFI_SUCCESS  Always returns success.

**/
EFI_STATUS
InstallSiipFv (
  VOID
  );

/**
  Reads SIIP Sub region.

  Reads SIIP address and size from FV. Returns pointer to data.

  @param[out]  SubRegion Pointer to sub region data.

  @retval     EFI_SUCCESS  Function has completed successfully.
  @retval     Others       SIIP firmware was not found
**/
EFI_STATUS
GetSiipFvInfo (
  OUT SIIP_FV_INFO  *SiipFvInfo
  );

/*
  Verify SIIP manifest

  @retval     EFI_SUCCESS  Function has completed successfully.
  @retval     Others       SIIP manifest was not found
*/
EFI_STATUS
VerifyManifest (
  IN OUT VOID     *ManifestBuffer,
  IN OUT UINTN    ManifestSize
  );

/*
  Verify SIIP firmware

  @retval     EFI_SUCCESS  Function has completed successfully.
  @retval     Others       SIIP firmware/manifest was not found
*/
EFI_STATUS
VerifyFirmware (
  IN OUT VOID     *ManifestBuffer,
  IN OUT UINTN    ManifestSize,
  IN OUT VOID     *FwBuffer,
  IN OUT UINTN    FwSize
  );

#endif
