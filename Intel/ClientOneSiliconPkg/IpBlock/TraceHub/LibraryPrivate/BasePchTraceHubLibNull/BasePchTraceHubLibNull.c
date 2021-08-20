/** @file
  Base TraceHub Init Lib Null.

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
#include <Uefi/UefiBaseType.h>

/**
  Null instance of Set TraceHub base address.

  @param[in] AddressHi                   High 32-bits for TraceHub base address.
  @param[in] AddressLo                   Low 32-bits for TraceHub base address.

  @retval EFI_UNSUPPORTED                This is a null instance.
**/
EFI_STATUS
TraceHubBaseSet (
  UINT32                                AddressHi,
  UINT32                                AddressLo
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Null instance of basic initialization for TraceHub

  @param[in] EnableMode                 Trace Hub Enable Mode

  @retval FALSE                         No need to power gate trace hub
**/

BOOLEAN
TraceHubInitialize (
  IN  UINT8                             EnableMode
  )
{
  return FALSE;
}

/**
  Null instance of disabling and power gating Pch trace hub

  @retval     EFI_UNSUPPORTED   The device is not supported
**/
EFI_STATUS
PchTraceHubDisable (
  VOID
  )
{
  return EFI_UNSUPPORTED;
}