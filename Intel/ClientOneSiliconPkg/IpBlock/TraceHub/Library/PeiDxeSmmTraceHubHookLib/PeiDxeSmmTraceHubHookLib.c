/** @file
  Pei/Dxe/Smm TraceHub Hook Lib.
  The Library implements hook lib for trace hub for SvenTx message.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2018 Intel Corporation.

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
#include <Uefi/UefiBaseType.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/PmcPrivateLib.h>
#include <PchReservedResources.h>
#include <Register/TraceHubRegs.h>
#include <Library/PreSiliconEnvDetectLib.h>

#define R_TRACE_HUB_MEM_MTB_SCRPD_2           0xE8

/**
  Calculate TraceHub Trace Address.
  For CNL PCH, BIOS trace output to FW_BAR, Master number is 72. (73 is BIOS reserved), channel number ranges from 1~127.

  @param [in] Master                    Master is being used.
  @param [in] Channel                   Channel is being used.
  @param [out] TraceAddress             TraceHub Address for the Master/Channel is being used.

  @retval EFI_SUCCESS                   Retrieve correct Address.
          EFI_DEVICE_ERROR              TraceHub device is power gated
          Other                         Failed to retrieve correct TraceHub Address.
**/
EFI_STATUS
EFIAPI
TraceHubMmioTraceAddress (
  IN  UINT16                            Master,
  IN  UINT16                            Channel,
  OUT UINT32                            *TraceAddress
  )
{
  if (MmioRead32 (PCH_TRACE_HUB_MTB_BASE_ADDRESS) == 0xFFFFFFFF) {
    return EFI_DEVICE_ERROR;
  }

  *TraceAddress = PCH_TRACE_HUB_FW_BASE_ADDRESS + 0x40 * (V_TRACE_HUB_MEM_MTB_CHLCNT * (Master - V_TRACE_HUB_MEM_MTB_FTHMSTR) + Channel);

  return EFI_SUCCESS;
}

/**
  Return Scratch Pad2 Register Value.

  @param [out] ScratchPad2RegValue Scratch Pad2 Register Value.

  @retval RETURN_SUCCESS      Retrieve Scratch Pad2 Register Value.
  @retval RETURN_UNSUPPORTED  Not implemented.
  @retval Other               Fail to Retrieve Scratch Pad2 Register Value.

**/
RETURN_STATUS
EFIAPI
TraceHubScratchPad2RegValue (
  OUT UINT8    *ScratchPad2RegValue
  )
{
  if (MmioRead32 (PCH_TRACE_HUB_MTB_BASE_ADDRESS) == 0xFFFFFFFF || IsSimicsEnvironment()) {
    return EFI_DEVICE_ERROR;
  }

  *ScratchPad2RegValue = MmioRead8 (PCH_TRACE_HUB_MTB_BASE_ADDRESS + R_TRACE_HUB_MEM_MTB_SCRPD_2);

  return EFI_SUCCESS;
}
