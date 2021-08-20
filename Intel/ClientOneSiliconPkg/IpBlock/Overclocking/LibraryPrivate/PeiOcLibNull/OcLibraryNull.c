/** @file
  Overclocking null library implementation.

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

#include <Library/PeiOcLib.h>

/**
  Gets the Voltage and Frequency information for a given CPU domain

  @param[out] *VfSettings
  @param[out] *LibStatus

  @retval EFI_STATUS
**/
EFI_STATUS
EFIAPI
GetVoltageFrequencyItem (
  OUT VOLTAGE_FREQUENCY_ITEM *VfSettings,
  OUT UINT32                 *LibStatus
  )
{
  return EFI_SUCCESS;
}

/**
  Sets the Voltage and Frequency information for a given CPU domain

  @param[in]  *VfSettings
  @param[out] *LibStatus

  @retval EFI_STATUS
**/
EFI_STATUS
EFIAPI
SetVoltageFrequencyItem (
  IN VOLTAGE_FREQUENCY_ITEM VfSettings,
  OUT UINT32                *LibStatus
  )
{
  return EFI_SUCCESS;
}


/**
  Get the overclocking capabilities for a given CPU Domain

  @param[out] *OcCapabilities
  @param[out] *LibStatus

  @retval EFI_STATUS
**/
EFI_STATUS
EFIAPI
GetOcCapabilities (
  OUT OC_CAPABILITIES_ITEM *OcCapabilities,
  OUT UINT32               *LibStatus
  )
{
  return EFI_SUCCESS;
}

/**
  Converts the input voltage target to the fixed point U12.2.10 Volt format or
  the Binary millivolts representation based on the ConversionType

  @param[in]  InputVoltageTarget
  @param[out] *OutputVoltageTarget
  @param[in]  ConversionType - 0:fixed point, 1:Binary millivolts
**/
VOID
ConvertVoltageTarget (
  IN UINT16  InputVoltageTarget,
  OUT UINT16 *OutputVoltageTarget,
  IN UINT8   ConversionType
  )
{
  return;
}

/**
  Converts the input votlage Offset to the fixed point S11.0.10 Volt format or
  to Binary millivolts representation based on the ConversionType.

  @param[in]  InputVoltageOffset
  @param[out] *OutputVoltageOffset
  @param[in]  ConversionType - 0:fixed point, 1:Signed Binary millivolts
**/
VOID
ConvertVoltageOffset (
  IN INT16  InputVoltageOffset,
  OUT INT16 *OutputVoltageOffset,
  IN UINT8  ConversionType
  )
{
  return;
}

/**
  Converts the input data to valid mailbox command format based on CommandID

  @param[in]  InputData
  @param[out] *MailboxData
  @param[in]  CommandId
**/
VOID
ConvertToMailboxFormat (
  IN VOID             *InputData,
  OUT OC_MAILBOX_ITEM *MailboxData,
  IN UINT32           CommandId
  )
{
  return;
}

