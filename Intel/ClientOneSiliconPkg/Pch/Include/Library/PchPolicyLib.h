/** @file
  Prototype of the PeiPchPolicy library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2017 Intel Corporation.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification
**/
#ifndef _PEI_PCH_POLICY_LIB_H_
#define _PEI_PCH_POLICY_LIB_H_

#include <Ppi/SiPolicy.h>

/**
  Print whole PCH_PREMEM_POLICY_PPI and serial out.

  @param[in] SiPreMemPolicyPpi       The RC PREMEM Policy PPI instance
**/
VOID
EFIAPI
PchPreMemPrintPolicyPpi (
  IN  SI_PREMEM_POLICY_PPI          *SiPreMemPolicyPpi
  );

/**
  Print whole SI_POLICY_PPI and serial out.

  @param[in] SiPolicyPpi               The RC Policy PPI instance
**/
VOID
EFIAPI
PchPrintPolicyPpi (
  IN  SI_POLICY_PPI           *SiPolicyPpi
  );

/**
  Get PCH PREMEM config block table total size.

  @retval                               Size of PCH PREMEM config block table
**/
UINT16
EFIAPI
PchGetPreMemConfigBlockTotalSize (
  VOID
  );

/**
  Get PCH config block table total size.

  @retval                               Size of PCH config block table
**/
UINT16
EFIAPI
PchGetConfigBlockTotalSize (
  VOID
  );

/**
  PchAddPreMemConfigBlocks add all PCH config blocks.

  @param[in] ConfigBlockTableAddress    The pointer to add PCH config blocks

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
PchAddPreMemConfigBlocks (
  IN     VOID      *ConfigBlockTableAddress
  );

/**
  PchAddConfigBlocks add all PCH config blocks.

  @param[in] ConfigBlockTableAddress    The pointer to add PCH config blocks

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
PchAddConfigBlocks (
  IN     VOID      *ConfigBlockTableAddress
  );

/**
  Get Sata Config Policy

  @param[in]  SiPolicy            The RC Policy PPI instance
  @param[in]  SataCtrlIndex       SATA controller index

  @retval     SataConfig          Pointer to Sata Config Policy
**/
SATA_CONFIG *
GetPchSataConfig (
  IN SI_POLICY_PPI      *SiPolicy,
  IN UINT32             SataCtrlIndex
  );

/**
  Get Hsio Sata Pre Mem Config Policy

  @param[in]  SiPolicy            The RC Policy PPI instance
  @param[in]  SataCtrlIndex       SATA controller index

  @retval     Pointer to Hsio Sata Pre Mem Config Policy
**/
PCH_HSIO_SATA_PREMEM_CONFIG *
GetPchHsioSataPreMemConfig (
  IN SI_PREMEM_POLICY_PPI *SiPreMemPolicy,
  IN UINT32               SataCtrlIndex
  );

#endif // _PEI_PCH_POLICY_LIB_H_
