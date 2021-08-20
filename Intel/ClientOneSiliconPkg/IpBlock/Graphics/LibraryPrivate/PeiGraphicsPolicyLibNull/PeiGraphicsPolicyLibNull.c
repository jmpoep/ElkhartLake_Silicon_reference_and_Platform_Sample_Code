/** @file
  Null Library for PEI Graphics policy default initialization

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#include <Library/DebugLib.h>
#include <Library/PeiGraphicsPolicyLib.h>
#include <Library/SiConfigBlockLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PeiServicesLib.h>
#include <Ppi/SiPolicy.h>
#include <SiPolicyStruct.h>
#include <Register/IgdRegs.h>

/**
  Get Graphics PEI config block table total size.

  @retval     Size of Graphics PEI config block table
**/
UINT16
EFIAPI
GraphicsGetConfigBlockTotalSize (
  VOID
  )
{
  return 0;
}

/**
  Get Graphics PEI Pre-Mem config block table total size.

  @retval      Size of Graphics PEI Pre-Mem config block table
**/
UINT16
EFIAPI
GraphicsGetConfigBlockTotalSizePreMem (
  VOID
  )
{
  return 0;
}

/**
  GraphicsAddConfigBlocksPreMem add all Graphics PEI PreMem config block.

  @param[in] ConfigBlockTableAddress    The pointer to add SA config blocks

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
GraphicsAddConfigBlocksPreMem (
  IN VOID           *ConfigBlockTableAddress
  )
{
  return EFI_SUCCESS;
}

/**
  GraphicsAddConfigBlocks add all Graphics PEI config block.

  @param[in] ConfigBlockTableAddress    The pointer to add SA config blocks

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
GraphicsAddConfigBlocks (
  IN VOID           *ConfigBlockTableAddress
  )
{
  return EFI_SUCCESS;
}


/**
  This function prints the PEI phase Graphics PreMem policy.

  @param[in] SiPolicyPreMemPpi - Instance of SI_PREMEM_POLICY_PPI
**/
VOID
EFIAPI
GraphicsPrintPolicyPpiPreMem (
  IN  SI_PREMEM_POLICY_PPI *SiPolicyPreMemPpi
  )
{
  return;
}

/**
  This function prints the Graphics PEI phase policy.

  @param[in] SiPolicyPpi - Instance of SI_POLICY_PPI
**/
VOID
EFIAPI
GraphicsPrintPolicyPpi (
  IN  SI_POLICY_PPI     *SiPolicyPpi
  )
{
  return;
}