/** @file
  Implementation file for Heci Message functionality

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2019 Intel Corporation.

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

#include "MePeiLibInternals.h"
#include <PchHsio.h>

//
// ME Client - MKHI
//

//
// MKHI_CBM_GROUP_ID = 0x00
//

/**
  Send Core BIOS Reset Request Message through HECI to reset the system.

  @param[in] ResetOrigin         Reset source
  @param[in] ResetType           Global or Host reset

  @retval EFI_UNSUPPORTED        Current ME mode doesn't support this function
  @retval EFI_SUCCESS            Command succeeded
  @retval EFI_NOT_FOUND          No ME present
  @retval EFI_DEVICE_ERROR       HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT            HECI does not return the buffer before timeout
**/
EFI_STATUS
PeiHeciSendCbmResetRequest (
  IN  UINT8                      ResetOrigin,
  IN  UINT8                      ResetType
  )
{
  HECI_PPI                       *HeciPpi;
  EFI_STATUS                     Status;
  UINT32                         HeciLength;
  UINT32                         AckLength;
  CBM_RESET_REQ                  CbmResetRequest;
  UINT32                         MeMode;
  UINT32                         Result;

  DEBUG((DEBUG_INFO, "ME-BIOS: ME: Global Reset Request Entry.\n"));
  PostCode (0xE06);

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ME-BIOS: ME: Global Reset Request Exit - Error by HECI service not found.\n"));
    PostCode (0xEA6);
    return EFI_NOT_FOUND;
  }

  Status = HeciPpi->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    DEBUG ((DEBUG_ERROR, "ME-BIOS: ME: Global Reset Request Exit - Error by message is not allowed.\n"));
    PostCode (0xE86);
    return EFI_UNSUPPORTED;
  }

  CbmResetRequest.MkhiHeader.Data               = 0;
  CbmResetRequest.MkhiHeader.Fields.GroupId     = MKHI_CBM_GROUP_ID;
  CbmResetRequest.MkhiHeader.Fields.Command     = CBM_RESET_CMD;
  CbmResetRequest.Data.RequestOrigin            = ResetOrigin;
  CbmResetRequest.Data.ResetType                = ResetType;

  HeciLength = sizeof (CBM_RESET_REQ);
  AckLength = sizeof (CBM_RESET_ACK);

  Status = HeciPpi->SendwAck (
                      HECI1_DEVICE,
                      (UINT32 *) &CbmResetRequest,
                      HeciLength,
                      &AckLength,
                      BIOS_FIXED_HOST_ADDR,
                      HECI_MKHI_MESSAGE_ADDR
                      );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "PeiHeciSendCbmResetRequest() - Unable to Send Reset Request - %r\n", Status));
    DEBUG ((DEBUG_ERROR, "ME-BIOS: ME: Global Reset Request Exit - Error by message sent fail.\n"));
    PostCode (0xEC6);
    return Status;
  }

  Result = ((CBM_RESET_ACK*)&CbmResetRequest)->MkhiHeader.Fields.Result;
  if (Result != 0) {
    DEBUG ((DEBUG_ERROR, "ME-BIOS: ME: Global Reset Request Exit - Error by message ack error. Result: %x\n", Result));
    Status = EFI_DEVICE_ERROR;
    PostCode (0xEE6);
  } else {
    DEBUG((DEBUG_INFO, "ME-BIOS: ME: Global Reset Request Exit - Success.\n"));
    PostCode (0xE26);
  }

  return Status;
}

//
// MKHI_FWCAPS_GROUP_ID = 0x03
//

/**
  Send Get Rule Data Request to CSME

  @param[in]   RuleId               Identifies the rule which data is requested.
  @param[out]  *RuleData            Pointer to requested rule data.

  @retval EFI_UNSUPPORTED           Current ME mode doesn't support this function
  @retval EFI_SUCCESS               Command succeeded
  @retval EFI_DEVICE_ERROR          HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT               HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL      Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
PeiHeciFwCapsGetRuleData (
  IN  UINT32                      RuleId,
  OUT UINT32                      *RuleData
  )
{
  EFI_STATUS                      Status;
  GET_RULE_BUFFER                 GetRuleMsg;
  UINT32                          Length;
  UINT32                          RecvLength;
  HECI_PPI                        *HeciPpi;
  UINT32                          MeMode;

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  Status = HeciPpi->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  GetRuleMsg.Request.MkhiHeader.Data               = 0;
  GetRuleMsg.Request.MkhiHeader.Fields.GroupId     = MKHI_FWCAPS_GROUP_ID;
  GetRuleMsg.Request.MkhiHeader.Fields.Command     = FWCAPS_GET_RULE_CMD;
  GetRuleMsg.Request.RuleId                        = RuleId;
  Length                                           = sizeof (GET_RULE);
  RecvLength                                       = sizeof (GET_RULE_ACK);

  ///
  /// Send Get Rule Data Request to ME
  ///
  Status = HeciPpi->SendwAck (
                      HECI1_DEVICE,
                      (UINT32 *) &GetRuleMsg,
                      Length,
                      &RecvLength,
                      BIOS_FIXED_HOST_ADDR,
                      HECI_MKHI_MESSAGE_ADDR
                      );

  if (!EFI_ERROR (Status) && ((GetRuleMsg.Response.MkhiHeader.Fields.Command) == FWCAPS_GET_RULE_CMD) &&
      ((GetRuleMsg.Response.MkhiHeader.Fields.IsResponse) == 1) &&
      (GetRuleMsg.Response.MkhiHeader.Fields.Result == 0)
      ) {
    *RuleData = GetRuleMsg.Response.RuleData;
  }

  return Status;
}

/**
  Send Get Firmware SKU Request to ME

  @param[out] FwCapsSku             ME Firmware Capability SKU

  @retval EFI_UNSUPPORTED           Current ME mode doesn't support this function
  @retval EFI_SUCCESS               Command succeeded
  @retval EFI_DEVICE_ERROR          HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT               HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL      Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
PeiHeciGetFwCapsSkuMsg (
  OUT MEFWCAPS_SKU             *RuleData
  )
{
  return PeiHeciFwCapsGetRuleData (FW_CAPS_RULE_ID, (UINT32*)RuleData);
}

/**
  The Get FW Feature Status message is based on MKHI interface.
  This command is used by BIOS/IntelR MEBX to get firmware runtime status.
  The GET FW RUNTIME STATUS message doesn't need to check the HFS.FWInitComplete
  value before sending the command.
  It means this message can be sent regardless of HFS.FWInitComplete.

  @param[out] RuleData              ME Firmware Capability SKU

  @retval EFI_UNSUPPORTED           Current ME mode doesn't support this function
  @retval EFI_SUCCESS               Command succeeded
  @retval EFI_DEVICE_ERROR          HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT               HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL      Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
PeiHeciGetFwFeatureStateMsg (
  OUT MEFWCAPS_SKU                *RuleData
  )
{
  return PeiHeciFwCapsGetRuleData (FW_FEATURE_STATE_RULE_ID, (UINT32*)RuleData);
}

/**
  This message is sent by the BIOS or IntelR MEBX. One of usages is to utilize
  this command to determine if the platform runs in Consumer or Corporate SKU
  size firmware.

  @param[out] RuleData              Including PlatformBrand, IntelMeFwImageType,
                                    SuperSku, and PlatformTargetUsageType

  @retval EFI_UNSUPPORTED           Current ME mode doesn't support this function
  @retval EFI_SUCCESS               Command succeeded
  @retval EFI_DEVICE_ERROR          HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT               HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL      Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
PeiHeciGetPlatformTypeMsg (
  OUT PLATFORM_TYPE_RULE_DATA     *RuleData
  )
{
  return PeiHeciFwCapsGetRuleData (PLATFORM_TYPE_RULE_ID, (UINT32*)RuleData);
}

/**
  This message is sent by the BIOS in PEI phase to query
  ME Unconfig on RTC Clear Disable state.

  @param[out] RuleData            1 - Unconfig on RTC clear is disabled
                                  0 - Unconfig on RTC clear is enabled

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL    Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
PeiHeciGetUnconfigOnRtcClearDisableMsg (
  OUT UINT32                *RuleData
  )
{
  return PeiHeciFwCapsGetRuleData (UNCONFIG_ON_RTC_CLEAR_RULE_ID, RuleData);
}

/**
  Send Set Rule Data Request to CSME

  @param[in]   RuleId             Identifies the rule which data needs to be changed.
  @param[in]   RuleDataLength     Rule Data Length.
  @param[in]   RuleData           Pointer to new rule data.

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL    Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
PeiHeciFwCapsSetRuleData (
  IN  UINT32                      RuleId,
  IN  UINT8                       RuleDataLength,
  IN  UINT32                      RuleData
  )
{
  EFI_STATUS                      Status;
  UINT32                          Length;
  UINT32                          RecvLength;
  HECI_PPI                        *HeciPpi;
  SET_RULE_BUFFER                 SetRuleMsg;
  UINT32                          MeMode;

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  Status = HeciPpi->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  SetRuleMsg.Request.MkhiHeader.Data           = 0;
  SetRuleMsg.Request.MkhiHeader.Fields.GroupId = MKHI_FWCAPS_GROUP_ID;
  SetRuleMsg.Request.MkhiHeader.Fields.Command = FWCAPS_SET_RULE_CMD;
  SetRuleMsg.Request.RuleId                    = RuleId;
  SetRuleMsg.Request.RuleDataLen               = RuleDataLength;
  SetRuleMsg.Request.RuleData                  = RuleData;
  Length                                       = sizeof (SET_RULE);
  RecvLength                                   = sizeof (SET_RULE_ACK);

  ///
  /// Send Set Rule Data Request to ME
  ///
  Status = HeciPpi->SendwAck (
                      HECI1_DEVICE,
                      (UINT32 *) &SetRuleMsg,
                      Length,
                      &RecvLength,
                      BIOS_FIXED_HOST_ADDR,
                      HECI_MKHI_MESSAGE_ADDR
                      );

  return Status;
}


/**
  This message is sent by the BIOS in PEI phase to set
  ME Unconfig on RTC Clear Disable state.

  @param[in] RuleData             1 - Disable Unconfig on RTC clear
                                  0 - Enable Unconfig on RTC clear

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function or EOP was sent
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL    Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
PeiHeciSetUnconfigOnRtcClearDisableMsg (
  IN UINT32                RuleData
  )
{
  return PeiHeciFwCapsSetRuleData (UNCONFIG_ON_RTC_CLEAR_RULE_ID, RULE_DATA_LENGTH, RuleData);
}

//
// BUP_COMMON_GROUP_ID = 0xF0
//

/**
  Send DRAM init done message through HECI to inform ME of memory initialization done.

  @param[in]  ImrBaseLow                Base address for IMR region (Low DWORD)
  @param[in]  ImrBaseHigh               Base address for IMR region (High DWORD)
  @param[in]  MemStatus                 Memory init status
  @param[out] MkhiResult                MKHI Error Code
  @param[out] Flags                     Flags
  @param[out] BiosAction                ME response to DID
  @param[out] PciImrBaseLow             Base address for PCI IMR (Low DWORD)
  @param[out] PciImrBaseHig             Base address for PCI IMR (High DWORD)
  @retval EFI_SUCCESS                   Command succeeded
  @retval EFI_DEVICE_ERROR              HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT                   HECI does not return the buffer before timeout
**/
EFI_STATUS
PeiHeciSendDid (
  IN  UINT32  ImrBaseLow,
  IN  UINT32  ImrBaseHigh,
  IN  UINT8   MemStatus,
  OUT UINT8   *MkhiResult,
  OUT UINT8   *Flags,
  OUT UINT8   *BiosAction,
  OUT UINT32  *PciImrBaseLow,
  OUT UINT32  *PciImrBaseHigh
  )
{
  EFI_STATUS                 Status;
  HECI_PPI                   *HeciPpi;
  DRAM_INIT_DONE_CMD_BUFFER  DidBuffer;
  UINT32                     ReqLength;
  UINT32                     RespLength;

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  ZeroMem (&DidBuffer, sizeof(DRAM_INIT_DONE_CMD_BUFFER));
  DidBuffer.Request.MkhiHeader.Data                = 0;
  DidBuffer.Request.MkhiHeader.Fields.GroupId      = BUP_COMMON_GROUP_ID;
  DidBuffer.Request.MkhiHeader.Fields.Command      = DRAM_INIT_DONE_CMD;
  DidBuffer.Request.ImrData.BiosImrsBaLow          = ImrBaseLow;
  DidBuffer.Request.ImrData.BiosImrsBaHigh         = ImrBaseHigh;
  DidBuffer.Request.MemStatus                      = MemStatus;

  ReqLength  = sizeof (DRAM_INIT_DONE_CMD_REQ);
  RespLength = sizeof (DRAM_INIT_DONE_CMD_RESP);

  Status = HeciPpi->SendwAck (
                      HECI1_DEVICE,
                      (UINT32 *) &DidBuffer,
                      ReqLength,
                      &RespLength,
                      BIOS_FIXED_HOST_ADDR,
                      HECI_MKHI_MESSAGE_ADDR
                      );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  if (DidBuffer.Response.MkhiHeader.Fields.IsResponse == 0) {
    DEBUG ((DEBUG_ERROR, "HeciSend DRAM Init Done unsuccessful - no response\n"));
    return EFI_DEVICE_ERROR;
  }

  *MkhiResult     = (UINT8)DidBuffer.Response.MkhiHeader.Fields.Result;
  *Flags          = DidBuffer.Response.Flags;
  *BiosAction     = DidBuffer.Response.BiosAction;
  *PciImrBaseLow  = DidBuffer.Response.Pci2PrivBase.AdrLow;
  *PciImrBaseHigh = DidBuffer.Response.Pci2PrivBase.AdrHigh;

  if (*MkhiResult != MkhiStatusSuccess) {
    DEBUG ((DEBUG_WARN, "HeciSend DRAM Init Done processed with MKHI Error Code. Response: \n"));
    DEBUG ((DEBUG_WARN, "  MkhiResult = 0x%02x\n",  *MkhiResult));
  } else {
    DEBUG ((DEBUG_INFO, "HeciSend DRAM Init Done successful. Response:\n"));
  }
  DEBUG ((DEBUG_INFO, "  Pci2Priv Base Low = 0x%08x\n",  DidBuffer.Response.Pci2PrivBase.AdrLow));
  DEBUG ((DEBUG_INFO, "  Pci2Priv Base High = 0x%08x\n", DidBuffer.Response.Pci2PrivBase.AdrHigh));
  DEBUG ((DEBUG_INFO, "  Flags = 0x%02x\n",              DidBuffer.Response.Flags));
  DEBUG ((DEBUG_INFO, "  BIOS Action = 0x%02x\n",        DidBuffer.Response.BiosAction));

  return Status;
}

/**
  Send Get MBP from FW

  @param[out]     MbpEntriesNumbe   Number of MBP entries
  @param[in, out] MbpItems          MBP items of the response
  @paran[in]      SkipMbp           Skip MBP

  @retval EFI_UNSUPPORTED           Current ME mode doesn't support this function
  @retval EFI_SUCCESS               Command succeeded
  @retval EFI_DEVICE_ERROR          HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT               HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL      Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
PeiHeciGetMbpMsg (
  OUT UINT32                   *MbpEntriesNumber,
  IN OUT UINT32                *MbpItems,
  IN BOOLEAN                   SkipMbp
  )
{
  EFI_STATUS     Status;
  GET_MBP_BUFFER GetMbp;
  UINT32         Length;
  UINT32         RecvLength;
  HECI_PPI       *HeciPpi;

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  GetMbp.Request.MkhiHeader.Data           = 0;
  GetMbp.Request.MkhiHeader.Fields.GroupId = BUP_COMMON_GROUP_ID;
  GetMbp.Request.MkhiHeader.Fields.Command = MBP_REQUEST_CMD;
  GetMbp.Request.SkipMbp                   = SkipMbp;
  Length                                   = sizeof (GET_MBP_REQ);
  RecvLength                               = sizeof (GET_MBP_RESP);

  ///
  /// Send Get MBP Request to ME
  ///
  Status = HeciPpi->SendwAck (
                      HECI1_DEVICE,
                      (UINT32 *) &GetMbp,
                      Length,
                      &RecvLength,
                      BIOS_FIXED_HOST_ADDR,
                      HECI_MKHI_MESSAGE_ADDR
                      );

  DEBUG ((DEBUG_INFO, "ReadMsg returned %r\n", Status));
  DEBUG ((DEBUG_INFO, "MsgGetMbpAck->MkhiHeader.Fields.Command = %d\n", GetMbp.Response.MkhiHeader.Fields.Command));
  DEBUG ((DEBUG_INFO, "MsgGetMbpAck->MkhiHeader.Fields.IsResponse = %d\n", GetMbp.Response.MkhiHeader.Fields.IsResponse));
  DEBUG ((DEBUG_INFO, "MsgGetMbpAck->MkhiHeader.Fields.Result = %d\n", GetMbp.Response.MkhiHeader.Fields.Result));

  if (!EFI_ERROR (Status) && !SkipMbp &&
      ((GetMbp.Response.MkhiHeader.Fields.Command) == MBP_REQUEST_CMD) &&
      ((GetMbp.Response.MkhiHeader.Fields.IsResponse) == 1) &&
      (GetMbp.Response.MkhiHeader.Fields.Result == 0)
      ) {
    *MbpEntriesNumber = GetMbp.Response.MbpHeader.NumEntries;
    CopyMem (MbpItems, &GetMbp.Response.MbpItems, (GetMbp.Response.MbpHeader.MbpSize * sizeof(UINT32) - sizeof (MBP_HEADER)));
  }

  DEBUG ((DEBUG_INFO, "No. of Mbp Entries: %d\n", GetMbp.Response.MbpHeader.NumEntries));
  //
  // Clear buffers from sensitive data
  //
  ZeroMem (&GetMbp.Response, sizeof (GET_MBP_RESP));
  return Status;
}

/**
  This message is sent by the BIOS to retrieve from CSME total size of IMRs.
  BIOS needs to provide mask of disabled IMRs and requested size for PCIe IMR.

  @param[in]  BiosImrDisableMask0  Low DWORD of BIOS IMR Disable mask
  @param[in]  BiosImrDisableMask1  High DWORD of BIOS IMR Disable mask
  @param[in]  PciImrSize           Requested IMR size for PCI
  @param[out] MkhiResult           MKHI Error Code
  @param[out] ImrsSize             Total IMR size
  @param[out] Alignment            Required address alignment

  @retval EFI_SUCCESS              Command succeeded
  @retval EFI_DEVICE_ERROR         HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT              HECI does not return the buffer before timeout
**/
EFI_STATUS
PeiHeciGetImrSizeMsg (
  IN  UINT32     BiosImrDisableMask0,
  IN  UINT32     BiosImrDisableMask1,
  IN  UINT32     PciImrSize,
  OUT UINT8      *MkhiResult,
  OUT UINT32     *ImrsSize,
  OUT UINT32     *Alignment
  )
{
  EFI_STATUS              Status;
  HECI_PPI                *HeciPpi;
  GET_IMR_CMD_BUFFER      GetImrCmd;
  UINT32                  ReqLength;
  UINT32                  RespLength;

  DEBUG ((DEBUG_INFO, "Heci Get IMR Size Msg\n"));

  *ImrsSize  = 0;
  *Alignment = 0;

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR(Status)) {
    return EFI_NOT_FOUND;
  }

  GetImrCmd.Request.MkhiHeader.Data           = 0;
  GetImrCmd.Request.MkhiHeader.Fields.GroupId = BUP_COMMON_GROUP_ID;
  GetImrCmd.Request.MkhiHeader.Fields.Command = GET_IMR_SIZE_CMD;

  GetImrCmd.Request.Data.BiosImrDisableMask0  = BiosImrDisableMask0;
  GetImrCmd.Request.Data.BiosImrDisableMask1  = BiosImrDisableMask1;
  GetImrCmd.Request.Data.Pci2PrivSize         = (UINT32) PciImrSize;

  ReqLength                                   = sizeof (GET_IMR_CMD_REQ);
  RespLength                                  = sizeof (GET_IMR_CMD_RESP);

  Status = HeciPpi->SendwAck (
                      HECI1_DEVICE,
                      (UINT32 *) &GetImrCmd,
                      ReqLength,
                      &RespLength,
                      BIOS_FIXED_HOST_ADDR,
                      HECI_MKHI_MESSAGE_ADDR
                      );
  if (EFI_ERROR(Status)) {
    DEBUG ((DEBUG_ERROR, "Heci Get IMR Size Msg Fail, Status = %r\n", Status));
    return Status;
  }

  if (GetImrCmd.Response.MkhiHeader.Fields.IsResponse == 0) {
    DEBUG ((DEBUG_ERROR, "Heci Get IMR Size Msg Fail - no response\n"));
    return EFI_DEVICE_ERROR;
  }

  *MkhiResult = (UINT8)GetImrCmd.Response.MkhiHeader.Fields.Result;
  *ImrsSize   = GetImrCmd.Response.Data.ImrsSize;
  *Alignment  = GetImrCmd.Response.Data.Alignment;

  if (*MkhiResult != MkhiStatusSuccess) {
    DEBUG ((DEBUG_WARN, "Heci Get IMR Size processed with MKHI Error Code. Response: \n"));
    DEBUG ((DEBUG_WARN, "  MkhiResult = 0x%02x\n", *MkhiResult));
  } else {
    DEBUG ((DEBUG_INFO, "Heci Get IMR Size Msg successful. Response:\n"));
  }

  DEBUG ((DEBUG_INFO, "  IMR Size = 0x%08x\n",          *ImrsSize));
  DEBUG ((DEBUG_INFO, "  Largest IMR Size = 0x%08x\n",  *Alignment));
  DEBUG ((DEBUG_INFO, "  Flags = 0x%08x\n",             GetImrCmd.Response.Data.Flags));


  return Status;
}

/**
  Send Manufacturing Reset and Halt

  @retval EFI_UNSUPPORTED           Current ME mode doesn't support this function
  @retval EFI_SUCCESS               Command succeeded
  @retval EFI_DEVICE_ERROR          HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT               HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL      Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
PeiHeciBupManufacturingResetAndHalt (
  VOID
  )
{
  EFI_STATUS                  Status;
  MANUF_RESET_AND_HALT_BUFFER ManufResetAndHalt;
  UINT32                      Length;
  UINT32                      RecvLength;
  HECI_PPI                    *HeciPpi;

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  ManufResetAndHalt.Request.MkhiHeader.Data           = 0;
  ManufResetAndHalt.Request.MkhiHeader.Fields.GroupId = BUP_COMMON_GROUP_ID;
  ManufResetAndHalt.Request.MkhiHeader.Fields.Command = MANUF_RESET_AND_HALT_CMD;
  Length                                              = sizeof (MANUF_RESET_AND_HALT_REQ);
  RecvLength                                          = sizeof (MANUF_RESET_AND_HALT_RESP);

  ///
  /// Send Manufacturing Reset and Halt Request to ME
  ///
  Status = HeciPpi->SendwAck (
                      HECI1_DEVICE,
                      (UINT32 *) &ManufResetAndHalt,
                      Length,
                      &RecvLength,
                      BIOS_FIXED_HOST_ADDR,
                      HECI_MKHI_MESSAGE_ADDR
                      );

  if (ManufResetAndHalt.Response.MkhiHeader.Fields.Result != 0) {
    return EFI_DEVICE_ERROR;
  }

  return Status;
}


//
// BUP_ICC_GROUP_ID = 0xF1
//

/**
  Send ICC request through HECI to query if CSME FW requires the warm reset flow from a previous boot.

  @param[out] WarmResetRequired   1 - CSME requires a warm reset to complete BCLK ramp en flow

  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
**/
EFI_STATUS
PeiHeciIccBclkMsg (
  OUT UINT8    *WarmResetRequired
  )
{
  EFI_STATUS        Status;
  HECI_PPI          *HeciPpi;
  ICC_CMD_BUFFER    IccCmdBuffer;
  UINT32            Length;
  UINT32            RespLength;

  DEBUG ((DEBUG_INFO, "(ICC) PeiHeciIccBclkMsg\n"));

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  IccCmdBuffer.Response.Data.FwNeedsWarmResetFlag = 0; //@Todo: remove this after CSME fixes response structure issue.
  IccCmdBuffer.Request.MkhiHeader.Data            = 0;
  IccCmdBuffer.Request.MkhiHeader.Fields.GroupId  = BUP_ICC_GROUP_ID;
  IccCmdBuffer.Request.MkhiHeader.Fields.Command  = ICC_CMD;
  Length                                          = sizeof (ICC_CMD_REQ);
  RespLength                                      = sizeof (ICC_CMD_RESP);

  Status = HeciPpi->SendwAck (
                      HECI1_DEVICE,
                      (UINT32 *) &IccCmdBuffer,
                      Length,
                      &RespLength,
                      BIOS_FIXED_HOST_ADDR,
                      HECI_MKHI_MESSAGE_ADDR
                      );

  if (!EFI_ERROR (Status) && (IccCmdBuffer.Response.MkhiHeader.Fields.Result == 0)) {
    *WarmResetRequired = (UINT8) IccCmdBuffer.Response.Data.FwNeedsWarmResetFlag;
  }

  return Status;
}

//
// BUP_PM_GROUP_ID = 0xF3
//

/**
  Send Host Reset Notification Message to determine if warm reset is required.

  @retval EFI_UNSUPPORTED           Current ME mode doesn't support this function
  @retval EFI_SUCCESS               Command succeeded
  @retval EFI_DEVICE_ERROR          HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT               HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL      Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
PeiHeciSendHostResetNotificationMsg (
  VOID
  )
{
  EFI_STATUS             Status;
  HECI_PPI               *HeciPpi;
  UINT32                 Length;
  UINT32                 RecvLength;
  HR_NOTIFICATION_BUFFER HrNotification;

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  HrNotification.Request.MkhiHeader.Data           = 0;
  HrNotification.Request.MkhiHeader.Fields.GroupId = BUP_PM_GROUP_ID;
  HrNotification.Request.MkhiHeader.Fields.Command = NPCR_NOTIFICATION_CMD;
  Length                                           = sizeof (HR_NOTIFICATION_CMD);
  RecvLength                                       = sizeof (HR_NOTIFICATION_CMD_RESP);

  ///
  /// Send Host Reset Notification Request to ME
  ///
  Status = HeciPpi->SendwAck (
                      HECI1_DEVICE,
                      (UINT32 *) &HrNotification,
                      Length,
                      &RecvLength,
                      BIOS_FIXED_HOST_ADDR,
                      HECI_MKHI_MESSAGE_ADDR
                      );

  if (!EFI_ERROR(Status) && (HrNotification.Response.ResetRequested == 0x1)) {
    (*GetPeiServicesTablePointer ())->ResetSystem2 (EfiResetWarm, EFI_SUCCESS, 0, NULL);
  }

  return Status;
}

//
// ME Client - Integrated Clock Chip (ICC)
//

/**
  Send the required system ChipsetInit Table to ME FW.

  @param[in] ChipsetInitTable     Pointer to the required system ChipsetInit Table
  @param[in] ChipsetInitTableLen  Length of the table in bytes

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_OUT_OF_RESOURCES    HECI Could not allocate Memory
**/
EFI_STATUS
PeiHeciWriteChipsetInitMsg (
  IN  UINT8                       *ChipsetInitTable,
  IN  UINT32                      ChipsetInitTableLen
  )
{
  HECI_PPI                       *HeciPpi;
  EFI_STATUS                     Status;
  UINT32                         ReqSize;
  ICC_SET_MPHY_SETTINGS_REQ      *SetMphySettings;

  DEBUG ((DEBUG_INFO, "%a(): Start\n", __FUNCTION__));
  if (ChipsetInitTableLen > PCH_HSIO_CHIPSETINIT_TBL_MAX_SIZE) {
    return EFI_DEVICE_ERROR;
  }

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  ReqSize = sizeof (ICC_SET_MPHY_SETTINGS_REQ) + ChipsetInitTableLen;
  SetMphySettings = AllocateZeroPool (ReqSize);
  if (SetMphySettings == NULL) {
    DEBUG ((DEBUG_ERROR, "%a() : Could not allocate Memory\n", __FUNCTION__));
    return EFI_OUT_OF_RESOURCES;
  }

  SetMphySettings->Header.ApiVersion   = ICC_API_VERSION;
  SetMphySettings->Header.IccCommand   = ICC_SET_MPHY_SETTINGS_CMD;
  SetMphySettings->Header.BufferLength = ICC_MESSAGE_BUFFER_LENGTH (ReqSize);
  CopyMem (&SetMphySettings->MphyData, ChipsetInitTable, ChipsetInitTableLen);

  Status = HeciPpi->SendwAck (
                      HECI1_DEVICE,
                      (UINT32 *) SetMphySettings,
                      ReqSize,
                      &ReqSize,
                      BIOS_FIXED_HOST_ADDR,
                      HECI_ICC_MESSAGE_ADDR
                      );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "(HSIO) ERROR: Write HSIO Settings Message failed! EFI_STATUS = %r\n", Status));
  } else if (SetMphySettings->Header.IccResponse != ICC_STATUS_SUCCESS) {
    DEBUG ((DEBUG_ERROR, "(HSIO) ERROR: Write HSIO Settings failed!: FW Response=0x%x\n", SetMphySettings->Header.IccResponse));
    Status = EFI_DEVICE_ERROR;
  }

  FreePool (SetMphySettings);

  DEBUG ((DEBUG_INFO, "%a(): End\n", __FUNCTION__));
  return Status;
}

/**
  Read the ChipsetInit table from CSME

  @param[out]     ChipsetInitTable     Pointer to the required system ChipsetInit Table.
  @param[in, out] ChipsetInitTableLen  Pointer to the length of the table in bytes

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
**/
EFI_STATUS
PeiHeciReadChipsetInitMsg (
  OUT UINT8             *ChipsetInitTable,
  IN OUT UINT32         *ChipsetInitTableLen
  )
{
  HECI_PPI                       *HeciPpi;
  EFI_STATUS                     Status;
  UINT32                         Length;
  UINT32                         RecvLength;
  ICC_READ_FROM_MPHY_BUFFER      *HsioReadMphy;


  if ((ChipsetInitTable == NULL) || (ChipsetInitTableLen == 0)) {
    return EFI_INVALID_PARAMETER;
  }

  DEBUG ((DEBUG_INFO, "%a(): Start\n", __FUNCTION__));

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  Length     = sizeof (ICC_READ_FROM_MPHY_REQ);
  RecvLength = sizeof (ICC_READ_FROM_MPHY_ACK) + *ChipsetInitTableLen;

  HsioReadMphy = AllocateZeroPool (RecvLength);
  if (HsioReadMphy == NULL) {
    DEBUG ((DEBUG_ERROR, "(HSIO) PeiHeciReadChipsetInitMsg: Could not allocate Memory\n"));
    return EFI_OUT_OF_RESOURCES;
  }
  HsioReadMphy->Request.Header.ApiVersion   = ICC_API_VERSION;
  HsioReadMphy->Request.Header.IccCommand   = ICC_READ_FROM_MPHY_CMD;
  HsioReadMphy->Request.Header.BufferLength = ICC_MESSAGE_BUFFER_LENGTH (Length);
  HsioReadMphy->Request.Offset              = 0;
  HsioReadMphy->Request.NumOfBytes          = *ChipsetInitTableLen;

  Status = HeciPpi->SendwAck (
                      HECI1_DEVICE,
                      (UINT32 *) HsioReadMphy,
                      Length,
                      &RecvLength,
                      BIOS_FIXED_HOST_ADDR,
                      HECI_ICC_MESSAGE_ADDR
                      );

  if (!EFI_ERROR (Status)) {
    if (HsioReadMphy->Response.Header.IccResponse == ICC_STATUS_SUCCESS) {
      if (HsioReadMphy->Response.ReadSize > PCH_HSIO_CHIPSETINIT_TBL_MAX_SIZE) {
        *ChipsetInitTableLen = 0;
        ASSERT (FALSE);  // ChipsetInit table should not get too large
        Status = EFI_DEVICE_ERROR;
      } else {
        if (*ChipsetInitTableLen < HsioReadMphy->Response.ReadSize) {
          *ChipsetInitTableLen = 0;
          ASSERT (FALSE);  // ChipsetInit buffer size is too small to copy full data
          Status = EFI_BUFFER_TOO_SMALL;
        } else {
          CopyMem (ChipsetInitTable, HsioReadMphy->Response.Payload, HsioReadMphy->Response.ReadSize);
          *ChipsetInitTableLen = HsioReadMphy->Response.ReadSize;
        }
      }
    } else {
      *ChipsetInitTableLen = 0;
      DEBUG ((DEBUG_ERROR, "(HSIO) ERROR: Get HSIO Settings failed!: FW Response=0x%x\n", HsioReadMphy->Response.Header.IccResponse));
      Status = EFI_DEVICE_ERROR;
    }
  }

  FreePool (HsioReadMphy);
  DEBUG ((DEBUG_INFO, "%a(): End\n", __FUNCTION__));

  return Status;
}

/**
  Get MKHI (Management Engine Kernel Host Interface) Version.

  @param[out] MkhiVersion           MKHI Version

  @retval EFI_UNSUPPORTED           Current ME mode doesn't support this function
  @retval EFI_SUCCESS               Command succeeded
  @retval EFI_DEVICE_ERROR          HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT               HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL      Message Buffer is too small for the Acknowledge
**/
STATIC
EFI_STATUS
HeciGetMkhiVersion (
  OUT MKHI_VERSION        *MkhiVersion
  )
{
  GET_MKHI_VERSION_BUFFER GetMkhiVersion;
  UINT32                  Length;
  UINT32                  RecvLength;
  EFI_STATUS              Status;
  HECI_PPI                *HeciPpi;

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  GetMkhiVersion.Request.MkhiHeader.Data           = 0;
  GetMkhiVersion.Request.MkhiHeader.Fields.GroupId = MKHI_GEN_GROUP_ID;
  GetMkhiVersion.Request.MkhiHeader.Fields.Command = GEN_GET_MKHI_VERSION_CMD;

  Length                                           = sizeof (GET_MKHI_VERSION);
  RecvLength                                       = sizeof (GET_MKHI_VERSION_ACK);

  Status = HeciPpi->SendwAck (
                      HECI1_DEVICE,
                      (UINT32*)&GetMkhiVersion,
                      Length,
                      &RecvLength,
                      BIOS_FIXED_HOST_ADDR,
                      HECI_MKHI_MESSAGE_ADDR
                      );

  if (!EFI_ERROR (Status) && (GetMkhiVersion.Response.MkhiHeader.Fields.Command == GEN_GET_MKHI_VERSION_CMD) &&
      (GetMkhiVersion.Response.MkhiHeader.Fields.IsResponse == 1) &&
      (GetMkhiVersion.Response.MkhiHeader.Fields.Result == 0)) {
    *MkhiVersion = GetMkhiVersion.Response.MkhiVersion;
  }
  return Status;
}

/**
  Sends the NVM request device ownership message.

  @retval EFI_UNSUPPORTED           Current ME mode doesn't support this function
  @retval EFI_SUCCESS               Command succeeded
  @retval EFI_DEVICE_ERROR          HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT               HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL      Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
EFIAPI
PeiHeciRequestDeviceOwnership (
  VOID
  )
{
  EFI_STATUS                     Status;
  UINT32                         HeciSendLength;
  UINT32                         HeciRecvLength;
  HECI_PPI                       *HeciPpi;
  REQUEST_OWNERSHIP_BUFFER       RequestOwnershipMsg;

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }
  ZeroMem (&RequestOwnershipMsg, sizeof(REQUEST_OWNERSHIP_BUFFER));
  RequestOwnershipMsg.Request.MkhiHeader.Data    = 0;
  RequestOwnershipMsg.Request.MkhiHeader.Fields.GroupId = MKHI_MCA_GROUP_ID;
  RequestOwnershipMsg.Request.MkhiHeader.Fields.Command = MCA_REQUEST_DEVICE_OWNERSHIP;
  HeciSendLength                                        = sizeof (REQUEST_OWNERSHIP);
  HeciRecvLength                                        = sizeof (REQUEST_OWNERSHIP);

  Status = HeciPpi->SendwAck (
                      HECI1_DEVICE,
                      (UINT32 *) &RequestOwnershipMsg,
                      HeciSendLength,
                      &HeciRecvLength,
                      BIOS_FIXED_HOST_ADDR,
                      HECI_MCHI_MESSAGE_ADDR
                      );

  if (EFI_ERROR(Status)) {
    DEBUG ((DEBUG_ERROR, "Heci Request Device Ownership Msg Fail, Status = %r\n", Status));
    return Status;
  }

  if (RequestOwnershipMsg.Response.MkhiHeader.Fields.IsResponse == 0) {
    DEBUG ((DEBUG_ERROR, "Heci Request Device Ownership unsuccessful - no response\n"));
    return EFI_DEVICE_ERROR;
  }

  if (RequestOwnershipMsg.Response.MkhiHeader.Fields.Result != MkhiStatusSuccess) {
    DEBUG ((DEBUG_WARN, "Heci Request Device Ownership processed with MKHI Error Code. Response: \n"));
    DEBUG ((DEBUG_WARN, "  MkhiResult = 0x%02x\n", RequestOwnershipMsg.Response.MkhiHeader.Fields.Result));
    DEBUG ((DEBUG_WARN, "  Group      = %x\n", RequestOwnershipMsg.Response.MkhiHeader.Fields.GroupId));
    DEBUG ((DEBUG_WARN, "  Command    = %x\n", RequestOwnershipMsg.Response.MkhiHeader.Fields.Command));
    DEBUG ((DEBUG_WARN, "  IsResponse = %x\n", RequestOwnershipMsg.Response.MkhiHeader.Fields.IsResponse));
    return EFI_DEVICE_ERROR;
  } else {
    DEBUG ((DEBUG_INFO, "Heci Request Device Ownership successful.\n"));
  }

  return EFI_SUCCESS;
}

/**
  Send IAFW DNX request set message throught HECI1.

  @param[in] Resp       Buffer to receive the CSE response data..

  @return EFI_SUCCESS   Set request success.
  @return Others        Set request failed.
**/
EFI_STATUS
HeciIafwDnxReqSet (
  IN OUT IAFW_DNX_REQ_SET_RESP_DATA                *Resp
  )
{
  EFI_STATUS                      Status;
  UINT32                          HeciSendLength;
  UINT32                          HeciRecvLength;
  IAFW_DNX_REQ_SET_REQ_DATA       *Req;
  IAFW_DNX_REQ_SET_RESP_DATA      *RespIn;
  UINT32                          DataBuffer[0x70];
  HECI_PPI                       *HeciPpi;
  UINT32                         MeMode;

  DEBUG ((EFI_D_INFO, "BIOS Starts to send HECI Message: HeciIafwDnxReqSet\n"));

  Status = PeiServicesLocatePpi (
             &gHeciPpiGuid,
             0,
             NULL,
             (VOID **) &HeciPpi
             );

  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "HeciPpi Not Found\n"));
    return EFI_NOT_FOUND;
  }

  Status = HeciPpi->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
  ASSERT_EFI_ERROR (Status);
  }
  DEBUG ((EFI_D_INFO, "GetSeCMode successful\n"));

  SetMem(DataBuffer, sizeof(DataBuffer), 0);

  Req = (IAFW_DNX_REQ_SET_REQ_DATA*)DataBuffer;
  Req->MKHIHeader.Fields.GroupId = MKHI_GEN_DNX_GROUP_ID;
  Req->MKHIHeader.Fields.Command = CSE_DNX_REQ_SET;

  DEBUG ((EFI_D_INFO, "IAFW_DNX_REQ_Set_REQ_DATA size is %x\n", sizeof(IAFW_DNX_REQ_SET_REQ_DATA)));
  HeciSendLength              = sizeof(IAFW_DNX_REQ_SET_REQ_DATA);
  HeciRecvLength              = sizeof(DataBuffer);


    Status = HeciPpi->SendwAck (
                      HECI1_DEVICE,
                      (UINT32 *) DataBuffer,
                      HeciSendLength,
                      &HeciRecvLength,
                      BIOS_FIXED_HOST_ADDR,
                      HECI_MKHI_MESSAGE_ADDR
                      );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "PeiHeciSendCbmResetRequest() - Unable to Send Reset Request - %r\n", Status));
    DEBUG ((DEBUG_ERROR, "ME-BIOS: ME: Global Reset Request Exit - Error by message sent fail.\n"));
    PostCode (0xEC6);
    return Status;
  }

  RespIn = (IAFW_DNX_REQ_SET_RESP_DATA*)DataBuffer;
  CopyMem((VOID*)Resp, (VOID*)RespIn, sizeof(IAFW_DNX_REQ_SET_RESP_DATA));

  DEBUG ((EFI_D_INFO, "Group    =%08x\n", Resp->MKHIHeader.Fields.GroupId));
  DEBUG ((EFI_D_INFO, "Command  =%08x\n", Resp->MKHIHeader.Fields.Command));
  DEBUG ((EFI_D_INFO, "IsRespone=%08x\n", Resp->MKHIHeader.Fields.IsResponse));
  DEBUG ((EFI_D_INFO, "Result   =%08x\n", Resp->MKHIHeader.Fields.Result));
  DEBUG ((EFI_D_INFO, "Response ReqBiosAction   =%08x\n", Resp->ReqBiosAction));

  return Status;
}
