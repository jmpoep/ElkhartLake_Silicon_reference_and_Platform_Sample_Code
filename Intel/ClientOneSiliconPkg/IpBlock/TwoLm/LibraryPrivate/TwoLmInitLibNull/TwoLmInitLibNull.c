/** @file
  Source file for 2LM feature initialization.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/
#include <Library/TwoLmInitLib.h>
#include <TwoLmConfig.h>
#include <Library/DebugLib.h>


/**
This function performs any early configuration of 2LM if needed.

**/
VOID
EFIAPI
TwoLmEarlyConfig (
) {
  return;
}

/**
This function does the basic configurations of IPs and issues the Mailbox commands
to find out the Far Memory region and its size which would be used by the MRC phase
in creating the memory map.

@param[in]      TwoLmConfig              2LM Config block.

@retval EFI_SUCCESS            Successfully initialized Pre-Mem configurations.
@retval EFI_UNSUPPORTED        in case if all the requirements to support 2LM boot mode are not met.
**/

EFI_STATUS
EFIAPI
TwoLmPreMemInit (
   IN TWOLM_PREMEM_CONFIG      *TwoLmPreMemConfig
) {
  return EFI_SUCCESS;
}

/**
This function does the basic configurations of Astro controller
This function will be called only if the 2LM mode is enabled in the policy.

@param[in]      MemoryMapData            MRC Memory map data structure to pass DDR Size, TOLUD, Remap values etc.
@param[in]      MemBootMode              Mem boot mode value as a result of detected near mem size

@retval EFI_SUCCESS            Successfully initialized Post-Mem configurations.
**/
EFI_STATUS
EFIAPI
TwoLmPostDdrInit (
  IN UINT32 NearMemorySize,
  IN UINT32 ToludBase,
  IN UINT32 RemapBase,
  IN UINT32 RemapLimit,
  IN UINT8 MemBootMode
) {
  return EFI_SUCCESS;
}


/**
This function hanldes all post mem activities for 2LM feature.

@retval EFI_SUCCESS      Successfully initialized Post-Mem configurations.
**/
EFI_STATUS
EFIAPI
TwoLmPostMemInit (
) {
  return EFI_SUCCESS;
}
