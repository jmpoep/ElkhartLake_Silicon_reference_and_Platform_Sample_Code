/** @file
  Overclocking library implementation.

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
#include <Library/CpuMailboxLib.h>

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
  EFI_STATUS      Status;
  UINT32          CommandId;
  UINT16          TempVoltageTarget;
  INT16           TempVoltageOffset;
  OC_MAILBOX_ITEM VfMsg;

  Status = EFI_SUCCESS;

  ZeroMem (&VfMsg,sizeof (VfMsg));
  ///
  /// Convert v/f command to Mailbox command format
  ///
  CommandId = OC_LIB_CMD_GET_VOLTAGE_FREQUENCY;

  ConvertToMailboxFormat ((VOID *) VfSettings, &VfMsg, CommandId);

  ///
  ///  Read From the OC Library
  ///
  Status = MailboxRead (MAILBOX_TYPE_OC, VfMsg.Interface.InterfaceData, &VfMsg.Data, LibStatus);

  ///
  ///  Copy mailbox data to VfSettings
  ///
  if ((Status == EFI_SUCCESS) && (*LibStatus == OC_LIB_COMPLETION_CODE_SUCCESS)) {
    VfSettings->VfSettings.MaxOcRatio = (UINT8) (VfMsg.Data & MAX_RATIO_MASK);
    VfSettings->VfSettings.VoltageTargetMode = (UINT8) ((VfMsg.Data & VOLTAGE_MODE_MASK) >> VOLTAGE_MODE_OFFSET);

    TempVoltageTarget = (UINT16) (VfMsg.Data  & VOLTAGE_TARGET_MASK) >> VOLTAGE_TARGET_OFFSET;
    ConvertVoltageTarget (TempVoltageTarget, &VfSettings->VfSettings.VoltageTarget, CONVERT_TO_BINARY_MILLIVOLT);

    TempVoltageOffset = (INT16) ((VfMsg.Data  & VOLTAGE_OFFSET_MASK) >> VOLTAGE_OFFSET_OFFSET);
    ConvertVoltageOffset (TempVoltageOffset, &VfSettings->VfSettings.VoltageOffset, CONVERT_TO_BINARY_MILLIVOLT);
  }

  return Status;
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
  EFI_STATUS      Status;
  UINT32          CommandId;
  OC_MAILBOX_ITEM VfMsg;

  Status = EFI_SUCCESS;

  ///
  /// Convert v/f Commands to Mailbox command format
  ///
  CommandId = OC_LIB_CMD_SET_VOLTAGE_FREQUENCY;
  ConvertToMailboxFormat ((VOID *)&VfSettings, &VfMsg, CommandId);

  ///
  /// Write the v/f Settings to the OC Mailbox
  ///
  Status = MailboxWrite (MAILBOX_TYPE_OC, VfMsg.Interface.InterfaceData, VfMsg.Data, LibStatus);

  return Status;
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
  EFI_STATUS      Status;
  UINT32          CommandId;
  OC_MAILBOX_ITEM OcCapsMsg;

  Status = EFI_SUCCESS;

  ZeroMem (&OcCapsMsg,sizeof (OC_MAILBOX_ITEM));

  ///
  /// Convert OC capabilties message to Mailbox command format
  ///
  CommandId = OC_LIB_CMD_GET_OC_CAPABILITIES;
  ConvertToMailboxFormat ((VOID *) OcCapabilities, &OcCapsMsg, CommandId);

  ///
  ///  Read From the OC Library
  ///
  Status = MailboxRead (MAILBOX_TYPE_OC, OcCapsMsg.Interface.InterfaceData, &OcCapsMsg.Data, LibStatus);

  ///
  ///  Copy mailbox data to OC Capabilities structure
  ///
  if ((Status == EFI_SUCCESS) && (*LibStatus == OC_LIB_COMPLETION_CODE_SUCCESS)) {
    OcCapabilities->MaxOcRatioLimit =
      (UINT8) OcCapsMsg.Data & OC_CAPS_MAX_RATIO_MASK;

    OcCapabilities->RatioOcSupported =
      (UINT8) ((OcCapsMsg.Data & OC_CAPS_RATIO_SUPPORT_MASK) >> OC_CAPS_RATIO_SUPPORT_OFFSET);

    OcCapabilities->VoltageOverridesSupported =
      (UINT8) ((OcCapsMsg.Data & OC_CAPS_OVERRIDE_SUPPORT_MASK) >> OC_CAPS_OVERRIDE_SUPPORT_OFFSET);

    OcCapabilities->VoltageOffsetSupported =
      (UINT8) ((OcCapsMsg.Data & OC_CAPS_OFFSET_SUPPORT_MASK) >> OC_CAPS_OFFSET_SUPPORT_OFFSET);
  }

  return Status;
}


/**
  Get the fused P0 ratio and voltage

  @param[out] *FusedP0Voltage in millivolt units
  @param[out] *FusedP0Ratio
  @param[out] *LibStatus

  @retval EFI_STATUS
**/
EFI_STATUS
EFIAPI
GetP0RatioVoltage (
  OUT UINT16 *FusedP0Voltage,
  OUT UINT16 *FusedP0Ratio,
  OUT UINT32 *LibStatus
  )
{
  EFI_STATUS      Status;
  OC_MAILBOX_ITEM FusedP0Msg;

  Status = EFI_SUCCESS;

  ZeroMem (&FusedP0Msg,sizeof (OC_MAILBOX_ITEM));

  ///
  /// Convert OC capabilties message to Mailbox command format
  ///
  FusedP0Msg.Interface.Fields.CommandCompletion = OC_LIB_CMD_GET_FUSED_P0_RATIO_VOLTAGE;
  FusedP0Msg.Interface.Fields.Param1 = OC_LIB_DOMAIN_ID_IA_CORE;

  ///
  ///  Read From the OC Library
  ///
  Status = MailboxRead (MAILBOX_TYPE_OC, FusedP0Msg.Interface.InterfaceData, &FusedP0Msg.Data, LibStatus);

  ///
  ///  Copy mailbox data to output variables
  ///
  if ((Status == EFI_SUCCESS) && (*LibStatus == OC_LIB_COMPLETION_CODE_SUCCESS)) {
    ///
    /// Update Fused Ratio value
    ///
    *FusedP0Ratio = (UINT8) FusedP0Msg.Data & OC_CAPS_MAX_RATIO_MASK;

    ///
    /// Update Fused Voltage value in millivolt units
    ///
    ConvertVoltageTarget((UINT16)((FusedP0Msg.Data & FUSED_P0_VOLTAGE_MASK) >> FUSED_P0_VOLTAGE_OFFSET), FusedP0Voltage, CONVERT_TO_BINARY_MILLIVOLT);
  }

  return Status;
}

/**
  Gets the AVX Ratio Offset

  @param[out] *Avx2RatioOffset - The AVX ratio offset value read from OC mailbox.
  @param[out] *LibStatus - OC mailbox library return code


  @retval EFI_STATUS
**/
EFI_STATUS
EFIAPI
GetAvxRatioOffset (
  OUT AVX_RATIO_ITEM    *AvxRatioOffset,
  OUT UINT32            *LibStatus
  )
{
  EFI_STATUS      Status;
  UINT32          CommandId;
  OC_MAILBOX_ITEM GetAvxRatioMsg;


  Status = EFI_SUCCESS;

  ZeroMem (&GetAvxRatioMsg, sizeof (OC_MAILBOX_ITEM));

  ///
  /// Convert Avx Ratio message to Mailbox command format
  ///
  CommandId = OC_LIB_CMD_GET_AVX_RATIO_OFFSET;
  ConvertToMailboxFormat ((VOID *) AvxRatioOffset, &GetAvxRatioMsg, CommandId);

  ///
  ///  Read From the OC Library
  ///
  Status = MailboxRead (MAILBOX_TYPE_OC, GetAvxRatioMsg.Interface.InterfaceData, &GetAvxRatioMsg.Data, LibStatus);

  ///
  ///  Copy mailbox data to Avx Ratio Offset
  ///
  if ((Status == EFI_SUCCESS) && (*LibStatus == OC_LIB_COMPLETION_CODE_SUCCESS)) {
    AvxRatioOffset->Avx2Ratio= (UINT8) ((GetAvxRatioMsg.Data & AVX2_RATIO_OFFSET_MASK) >> AVX2_RATIO_OFFSET_OFFSET);
    AvxRatioOffset->Avx3Ratio= (UINT8) ((GetAvxRatioMsg.Data & AVX3_RATIO_OFFSET_MASK) >> AVX3_RATIO_OFFSET_OFFSET);
  }

  return Status;

}

/**
  Sets the AVX Ratio Offset

  @param[in] Avx2RatioOffset - The AVX ratio offset value to program to OC mailbox.
  @param[out] *LibStatus - OC mailbox library return code


  @retval EFI_STATUS
**/
EFI_STATUS
EFIAPI
SetAvxRatioOffset (
  IN  AVX_RATIO_ITEM    AvxRatioOffset,
  OUT UINT32            *LibStatus
  )
{
  EFI_STATUS      Status;
  UINT32          CommandId;
  OC_MAILBOX_ITEM SetAvxRatioMsg;


  Status = EFI_SUCCESS;

  ZeroMem (&SetAvxRatioMsg, sizeof (OC_MAILBOX_ITEM));

  ///
  /// Convert Avx Ratio message to Mailbox command format
  ///
  CommandId = OC_LIB_CMD_SET_AVX_RATIO_OFFSET;
  ConvertToMailboxFormat ((VOID *)&AvxRatioOffset, &SetAvxRatioMsg, CommandId);

  ///
  ///  Write the OC Library
  ///
  Status = MailboxWrite (MAILBOX_TYPE_OC, SetAvxRatioMsg.Interface.InterfaceData, SetAvxRatioMsg.Data, LibStatus);

  return Status;

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
  UINT32 Remainder;
  UINT64 Voltage;
  ///  Fixed point representation:
  ///
  ///  U12.2.10V format
  ///  | | | |
  ///  | | | v
  ///  | | v Exponent
  ///  | v Significand Size
  ///  v Size
  ///  Signed/Unsigned
  ///
  ///  Float Value = Significand x (Base ^ Exponent)
  ///  (Base ^ Exponent) = 2 ^ 10 = 1024
  ///
  Remainder = 0;

  if (InputVoltageTarget == 0) {
    *OutputVoltageTarget = 0;
    return;
  }

  if (ConversionType == CONVERT_TO_FIXED_POINT_VOLTS) {
    ///
    /// Input Voltage is in number of millivolts. Clip the input Voltage
    /// to the max allowed by the fixed point format
    ///
    if (InputVoltageTarget > MAX_TARGET_MV)
      InputVoltageTarget = MAX_TARGET_MV;

    ///
    /// InputTargetVoltage is the significand in mV. Need to convert to Volts
    ///
    Voltage = MultU64x32 (1024, InputVoltageTarget);
    *OutputVoltageTarget = (UINT16) DivU64x32Remainder (Voltage, MILLIVOLTS_PER_VOLT,&Remainder);

    if (Remainder >= 500) {
      *OutputVoltageTarget += 1;
    }
  } else if (ConversionType == CONVERT_TO_BINARY_MILLIVOLT) {
    ///
    /// InputVoltage is specified in fixed point representation, need to
    /// convert to millivolts
    ///
    Voltage = MultU64x32 (MILLIVOLTS_PER_VOLT, InputVoltageTarget);
    *OutputVoltageTarget = (UINT16) DivU64x32Remainder (Voltage, 1024,&Remainder);

    if (Remainder >= 500) {
      *OutputVoltageTarget += 1;
    }
  }

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
  BOOLEAN NumIsNegative;
  UINT32  Remainder;
  UINT64  Voltage;
  ///  Fixed point representation:
  ///
  ///  S11.0.10V format
  ///  | | | |
  ///  | | | v
  ///  | | v Exponent
  ///  | v Significand Size
  ///  v Size
  ///  Signed/Unsigned
  ///
  ///  Float Value = Significand x (Base ^ Exponent)
  ///  (Base ^ Exponent) = 2 ^ 10 = 1024
  ///
  *OutputVoltageOffset = 0;
  NumIsNegative = FALSE;
  Remainder = 0;

  if (InputVoltageOffset == 0) {
    *OutputVoltageOffset = 0;
    return;
  }

  if (ConversionType == CONVERT_TO_FIXED_POINT_VOLTS) {
    ///
    /// Input Voltage is in INT16 representation. Check if numenr is negative
    ///
    if ((InputVoltageOffset & INT16_SIGN_BIT_MASK) != 0) {
      NumIsNegative = TRUE;
      ///
      /// Need to 2's complement adjust to make this number positive for
      /// voltage calculation
      ///
      InputVoltageOffset = (~InputVoltageOffset+1) & (INT16_SIGN_BIT_MASK -1);
    }

    ///
    /// Clip the input Voltage Offset to 500mv
    ///
    if (InputVoltageOffset > MAX_OFFSET_MV) {
      InputVoltageOffset = MAX_OFFSET_MV;
    }

    ///
    /// Convert to fixed point representation
    ///
    Voltage = MultU64x32 (1024, InputVoltageOffset);
    *OutputVoltageOffset = (UINT16) DivU64x32Remainder (Voltage, MILLIVOLTS_PER_VOLT,&Remainder);

    if (Remainder >= 500) {
      *OutputVoltageOffset += 1;
    }

    if (NumIsNegative) {
      //
      // 2's complement back to a negative number
      //
      *OutputVoltageOffset = ~(*OutputVoltageOffset) + 1;
    }
  } else if (ConversionType == CONVERT_TO_BINARY_MILLIVOLT) {
    ///
    /// Input Voltage is in fixed point representation. Check if number negative
    ///
    if ((InputVoltageOffset & FIXED_POINT_SIGN_BIT_MASK) != 0) {
      NumIsNegative = TRUE;
      ///
      /// Need to 2's complement adjust to make this number positive for
      /// voltage calculation
      ///
      InputVoltageOffset = (~InputVoltageOffset+1) & (FIXED_POINT_SIGN_BIT_MASK -1);
    }

    ///
    ///  Convert to INT16 representation in millivolts
    ///
    Voltage = MultU64x32 (MILLIVOLTS_PER_VOLT, InputVoltageOffset);
    *OutputVoltageOffset = (UINT16) DivU64x32Remainder (Voltage, 1024,&Remainder);

    if (Remainder >= 500) {
      *OutputVoltageOffset += 1;
    }

    if (NumIsNegative) {
      //
      // 2's complement back to a negative number
      //
      *OutputVoltageOffset = ~(*OutputVoltageOffset) + 1;
    }
  }

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
  VOLTAGE_FREQUENCY_ITEM  *VfItem;
  OC_CAPABILITIES_ITEM    *OcCapItem;
  VF_MAILBOX_COMMAND_DATA VfMailboxCommandData;
  CORE_RATIO_LIMITS_ITEM  *CoreRatioItem;
  AVX_RATIO_ITEM          *AvxRatioData;
  UINT16                  TempVoltage;

  ///
  ///  Initialize local varaibles and mailbox data
  ///
  ZeroMem ((UINT32 *) MailboxData, sizeof (OC_MAILBOX_ITEM));

  ///
  /// Then make a decision based on CommandId how to format
  ///
  switch (CommandId) {
    case OC_LIB_CMD_GET_OC_CAPABILITIES:
      OcCapItem = (OC_CAPABILITIES_ITEM *) InputData;
      ///
      /// OC Capabilities are returned on a per domain basis
      ///
      MailboxData->Data = 0;
      MailboxData->Interface.Fields.CommandCompletion = OC_LIB_CMD_GET_OC_CAPABILITIES;
      MailboxData->Interface.Fields.Param1 = OcCapItem->DomainId;
      break;

    case OC_LIB_CMD_GET_PER_CORE_RATIO_LIMIT:
      CoreRatioItem = (CORE_RATIO_LIMITS_ITEM *) InputData;
      ///
      /// Core Ratio Limits are only valid in the IA Core domain
      ///
      MailboxData->Data = 0;
      MailboxData->Interface.Fields.CommandCompletion = OC_LIB_CMD_GET_PER_CORE_RATIO_LIMIT;
      MailboxData->Interface.Fields.Param1 = OC_LIB_DOMAIN_ID_IA_CORE;
      MailboxData->Interface.Fields.Param2 = CoreRatioItem->Index;
      break;

    case OC_LIB_CMD_GET_VOLTAGE_FREQUENCY:
      VfItem = (VOLTAGE_FREQUENCY_ITEM *) InputData;
      ///
      /// Voltage Frequency Settings are on a per domain basis
      ///
      MailboxData->Data = 0;
      MailboxData->Interface.Fields.CommandCompletion = OC_LIB_CMD_GET_VOLTAGE_FREQUENCY;
      MailboxData->Interface.Fields.Param1 = VfItem->DomainId;
      break;

    case OC_LIB_CMD_SET_VOLTAGE_FREQUENCY:
      VfItem = (VOLTAGE_FREQUENCY_ITEM *) InputData;
      ///
      /// Voltages are stored in a fixed point format
      ///
      VfMailboxCommandData.MaxOcRatio = VfItem->VfSettings.MaxOcRatio;

      TempVoltage = 0;
      ConvertVoltageTarget (VfItem->VfSettings.VoltageTarget, &TempVoltage, CONVERT_TO_FIXED_POINT_VOLTS);
      VfMailboxCommandData.VoltageTargetU12 = TempVoltage;

      VfMailboxCommandData.TargetMode = VfItem->VfSettings.VoltageTargetMode;

      TempVoltage = 0;
      ConvertVoltageOffset (VfItem->VfSettings.VoltageOffset, (INT16 *) &TempVoltage, CONVERT_TO_FIXED_POINT_VOLTS);
      VfMailboxCommandData.VoltageOffsetS11 = TempVoltage;

      CopyMem (&MailboxData->Data, &VfMailboxCommandData, sizeof (VfMailboxCommandData));
      MailboxData->Interface.Fields.CommandCompletion = OC_LIB_CMD_SET_VOLTAGE_FREQUENCY;
      MailboxData->Interface.Fields.Param1 = VfItem->DomainId;
      break;

    case OC_LIB_CMD_GET_DDR_CAPABILITIES:
      MailboxData->Data = 0;
      MailboxData->Interface.Fields.CommandCompletion = OC_LIB_CMD_GET_DDR_CAPABILITIES;
      MailboxData->Interface.Fields.Param1 = 0;
      break;

    case OC_LIB_CMD_GET_AVX_RATIO_OFFSET:
      MailboxData->Data = 0;
      MailboxData->Interface.Fields.CommandCompletion = OC_LIB_CMD_GET_AVX_RATIO_OFFSET;
      break;

    case OC_LIB_CMD_SET_AVX_RATIO_OFFSET:
      AvxRatioData = (AVX_RATIO_ITEM *) InputData;
      MailboxData->Data = (((AvxRatioData->Avx2Ratio << AVX2_RATIO_OFFSET_OFFSET) & AVX2_RATIO_OFFSET_MASK)|
        ((AvxRatioData->Avx3Ratio << AVX3_RATIO_OFFSET_OFFSET) & AVX3_RATIO_OFFSET_MASK));
      MailboxData->Interface.Fields.CommandCompletion = OC_LIB_CMD_SET_AVX_RATIO_OFFSET;
      break;

    default:
      DEBUG ((DEBUG_ERROR, "(OC MAILBOX) Unknown Command ID\n"));

      break;

  }
}

