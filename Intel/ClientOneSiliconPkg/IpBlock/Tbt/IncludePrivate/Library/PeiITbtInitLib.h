/**@file
  PEI ITBT Init Dispatch library Header file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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
#ifndef __PEI_ITBT_INIT_LIB_H__
#define __PEI_ITBT_INIT_LIB_H__

#include <Library/PeiServicesLib.h>
#include <Library/DebugLib.h>
#include <Library/TbtCommonLib.h>
#include <Library/PeiTbtTaskDispatchLib.h>
#include <ITbtInfoHob.h>
#include <TcssDataHob.h>
#include <Library/ItbtPcieRpLib.h>
#include <Library/PcdLib.h>

extern TBT_CALL_TABLE_ENTRY ITbtCallTable[];

/**
  Program iTBT FP Register in order to bring iTBT micro controller up by applying Force Power.

  @param[in]  VOID                PeiTbtConfig

  @retval  EFI_SUCCESS            The function completes successfully
  @retval  EFI_UNSUPPORTED        ITBT is not supported.
**/
EFI_STATUS
EFIAPI
ITbtSetForcePower (
  IN  VOID  *PeiTbtConfig
);

/**
  Send iTBT Connect Topology Command for Integrated Thunderbolt.

  @param[in]  VOID                PeiTbtConfig

  @retval  EFI_SUCCESS            The function completes successfully
  @retval  EFI_DEVICE_ERROR       Connect Topology Command is not executed successfully.
**/
EFI_STATUS
EFIAPI
ITbtSendCnctTpolgyCmd (
  IN  VOID  *PeiTbtConfig
);

/**
  Clear VGA Registers for Integrated Thunderbolt.

  @param[in]  VOID                PeiTbtConfig

  @retval  EFI_SUCCESS            The function completes successfully
  @retval  EFI_UNSUPPORTED        ITBT is not supported.
**/
EFI_STATUS
EFIAPI
ITbtClearVgaRegisters (
  IN  VOID  *PeiTbtConfig
);

/**
  Program LTR Registers for Integrated Thunderbolt.

  @param[in]  VOID                PeiTbtConfig

  @retval  EFI_SUCCESS            The function completes successfully
  @retval  EFI_UNSUPPORTED        ITBT is not supported.
**/
EFI_STATUS
EFIAPI
ITbtSetDmaLtr (
  IN  VOID  *PeiTbtConfig
);

/**
  This function Update UUID number to ITBT DMA Host controller.

  @param[in]  VOID                PeiTbtConfig

  @retval  EFI_SUCCESS            The function completes successfully
  @retval  EFI_INVALID_PARAMETER  gPeiITbtConfig is invalide.
**/
EFI_STATUS
EFIAPI
ITbtSetDmaUuid (
  IN  VOID  *PeiITbtConfig
);

/**
  This function pass PEI ITbt Policy to Hob.

  @param[in]  VOID             PeiTbtConfig

  @retval     EFI_SUCCESS      The function completes successfully
  @retval     EFI_UNSUPPORTED  iTBT is not supported.
**/
EFI_STATUS
EFIAPI
PassITbtPolicyToHob(
  IN  VOID  *PeiTbtConfig
);
#endif
