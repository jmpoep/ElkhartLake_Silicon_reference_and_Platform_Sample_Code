/** @file
  Source file for Far Memory Mailbox Commands implementation.

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
#include <Library/CpuRegbarAccessLib.h>
#include <Library/FmssMbLib.h>
#include <Register/TwoLmRegs.h>
#include <Library/DebugLib.h>



EFI_STATUS
EFIAPI
QueryRegionLayoutCommand (
  UINT8 *DeviceReturnStatus, UINT32 *OutputPayloadPtr, UINT8 OutputPayloadSizeDw, UINT8 RegionId
  ) {

  MAILBOX_CMD MbCmd;
  EFI_STATUS status;
  REGION_LAYOUT_INFORMATION * RegionInfo;
  int i;
  //
  // Basic sanity check for parameters
  //
  if (!DeviceReturnStatus || !OutputPayloadPtr || !OutputPayloadSizeDw || (OutputPayloadSizeDw > 128)) {
    DEBUG ((DEBUG_INFO, "Invalid parameters\n"));
    return EFI_INVALID_PARAMETER;
  }


  MbCmd.BiosNonceValue = 0; // Nonce value is not required for this cmd
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = RegionProvision;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = QueryRegionLayout;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  MbCmd.MbCmd1Reg.Bits.BH_MB_Type = BIOS_FW;
  MbCmd.OutputPayloadPtr = OutputPayloadPtr;
  MbCmd.OutputPayloadSizeDw = OutputPayloadSizeDw ;
  MbCmd.InputPayloadPtr = NULL;
  MbCmd.InputPayloadSizeDw = 0;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  if (RegionId == 0xFF){
    MbCmd.MbCmd1Reg.Bits.AllRegions = 1;
  }
  else {
    MbCmd.MbCmd1Reg.Bits.RegionId = RegionId;
  }

  DEBUG ((DEBUG_INFO, "Getting 2LM region details from 3dxp device\n"));
  status = IssueMailboxCommand(MbCmd);
  if (status != EFI_SUCCESS){
    return status;
  }

  DEBUG ((DEBUG_INFO, "3DXP region details are as below\n"));
  RegionInfo = (REGION_LAYOUT_INFORMATION *)OutputPayloadPtr;

  for (i=0; i < MAX_REGIONS; ++i) {
    DEBUG ((DEBUG_INFO, "RegionId is %d \t",RegionInfo[i].DW0Data_Union.DW0Bits.RegionId));
    DEBUG ((DEBUG_INFO, "Last Region Indicator %d \t",RegionInfo[i].DW0Data_Union.DW0Bits.LastRegionIndicator));
    DEBUG ((DEBUG_INFO, "Region Valid Indicator %d \t",RegionInfo[i].DW0Data_Union.DW0Bits.RegionValidindicator));
    DEBUG ((DEBUG_INFO, "Last Region Indicator %d \n",RegionInfo[i].DW0Data_Union.DW0Bits.LastRegionIndicator));
    if (RegionInfo[i].DW0Data_Union.DW0Bits.LastRegionIndicator) {
      return EFI_SUCCESS;
    }
    // Print other required details if necessary
  }
  return EFI_SUCCESS;
} // end of fun


//
// Region Create
// @todo - BIOS to set config lock only when last region bit is set
// Region ID used in creation shall start from Region ID 0 and be packed sequentially for subsequent regions.
// For Region Create, 8 bytes of region data is required in the inbox buffer.
//
EFI_STATUS
EFIAPI
RegionCreateCommand (
  UINT8 *DeviceReturnStatus, UINT32 *InputPayloadPtr, UINT8 InputPayloadSizeDw
  ) {

  MAILBOX_CMD MbCmd;
  EFI_STATUS status;

  //
  // Basic sanity check for parameters
  //
  if (!InputPayloadPtr || !(InputPayloadSizeDw)) {
    DEBUG ((DEBUG_INFO, "Invalid parameters\n"));
    return EFI_INVALID_PARAMETER;
  }

  MbCmd.BiosNonceValue = 0; // Nonce value is not required for this cmd
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = RegionProvision;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = RegionCreate;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  MbCmd.MbCmd1Reg.Bits.BH_MB_Type = BIOS_FW;
  MbCmd.OutputPayloadPtr = NULL;
  MbCmd.OutputPayloadSizeDw = 0;
  MbCmd.InputPayloadPtr = InputPayloadPtr;
  MbCmd.InputPayloadSizeDw = InputPayloadSizeDw;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  DEBUG ((DEBUG_INFO, "Creating region in 3DXP Far memory device\n"));
  status = IssueMailboxCommand (MbCmd);
  return status;
}



//
// Region Delete
// Once a region is deleted, the associated region data shall be removed from the
// regions table and the total number of region shall be decremented by 1.
// Only Command register is required for Region Delete, no additional data is required in the inbox buffer
//
EFI_STATUS
EFIAPI
RegionDeleteCommand (
  UINT8 *DeviceReturnStatus, UINT8 RegionId
  ) {

  MAILBOX_CMD MbCmd;
  EFI_STATUS status;

  MbCmd.BiosNonceValue = 0; // Nonce value is not required for this cmd
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = RegionProvision;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = RegionDelete;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  MbCmd.MbCmd1Reg.Bits.BH_MB_Type = BIOS_FW;
  MbCmd.OutputPayloadPtr = NULL;
  MbCmd.OutputPayloadSizeDw = 0;
  MbCmd.InputPayloadPtr = NULL;
  MbCmd.InputPayloadSizeDw = 0;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  if (RegionId == 0xFF) {
    MbCmd.MbCmd1Reg.Bits.AllRegions = 1; // When set, all the regions that have been created shall be deleted.
  }
  else {
    MbCmd.MbCmd1Reg.Bits.RegionId = RegionId; // region id of specific region
  }

  DEBUG ((DEBUG_INFO, "Deleting region from 3DXP Far memory device\n"));
  status = IssueMailboxCommand(MbCmd);
  return status;
}


//
// Clear Region
// Once a region is cleared, all the data returned will be 0, but actual data on the device may not be 0.
// Device FW shall increment the device's boot counter after clearing the region.
// Only Command register is required for Region Clear, no additional data is required in the inbox buffer
//
EFI_STATUS
EFIAPI
ClearRegionCommand (
  UINT8 *DeviceReturnStatus, UINT8 RegionId
  ) {

  MAILBOX_CMD MbCmd;
  EFI_STATUS status;

  MbCmd.BiosNonceValue = 0; // Nonce value is not required for this cmd
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = RegionProvision;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = ClearRegion;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  MbCmd.MbCmd1Reg.Bits.BH_MB_Type = BIOS_FW;
  MbCmd.OutputPayloadPtr = NULL;
  MbCmd.OutputPayloadSizeDw = 0;
  MbCmd.InputPayloadPtr = NULL;
  MbCmd.InputPayloadSizeDw = 0;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  if (RegionId == 0xFF) {
    MbCmd.MbCmd1Reg.Bits.AllRegions = 1; // When set, all the regions that have been created shall be cleared.
  }
  else {
    MbCmd.MbCmd1Reg.Bits.RegionId = RegionId; // region id of specific region
  }

  DEBUG ((DEBUG_INFO, "Clearing regions in 3DXP Far memory device\n"));
  status = IssueMailboxCommand (MbCmd);
  return status;
}



//
// Format Region
// once a region is formatted, the actual data on the device shall be cleared to 0.
// Device FW shall not increment the device's boot counter.
// Only Command register is required for Region format, no additional data is required in the inbox buffer
//
EFI_STATUS
EFIAPI
FormatRegionCommand (
  UINT8 *DeviceReturnStatus, UINT8 RegionId, UINT8 SecureErase
  ) {

  MAILBOX_CMD MbCmd;
  EFI_STATUS status;

  MbCmd.BiosNonceValue = 0; // Nonce value is not required for this cmd
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = RegionProvision;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = FormatRegion;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  MbCmd.MbCmd1Reg.Bits.BH_MB_Type = BIOS_FW;
  MbCmd.MbCmd1Reg.Bits.SecureErase = SecureErase; // when 1 Device to write all zeros in this formated region
  MbCmd.OutputPayloadPtr = NULL;
  MbCmd.OutputPayloadSizeDw = 0;
  MbCmd.InputPayloadPtr = NULL;
  MbCmd.InputPayloadSizeDw = 0;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  if (RegionId == 0xFF) {
    MbCmd.MbCmd1Reg.Bits.AllRegions = 1;  // when 1, format all regions
  }
  else {
    MbCmd.MbCmd1Reg.Bits.RegionId = RegionId; // region id of specific region
  }

  DEBUG ((DEBUG_INFO, "Clearing regions in 3DXP Far memory device\n"));
  status = IssueMailboxCommand (MbCmd);
  return status;
}


//
// Update Firmware
// BIOS would not validate the FW version to be updated, it would just pass through the data from tool to the device using Mailbox.
//
EFI_STATUS
EFIAPI
InitiateUpdateFirmwareCommand (
  UINT8 *DeviceReturnStatus, UINT32 *InputPayloadPtr, UINT8 InputPayloadSizeDw, UINT16 PacketNo
  ) {

  MAILBOX_CMD MbCmd;
  EFI_STATUS status;

  //
  // Basic sanity check for parameters
  //
  if (!InputPayloadPtr || !(InputPayloadSizeDw)) {
    DEBUG ((DEBUG_INFO, "Invalid parameters\n"));
    return EFI_INVALID_PARAMETER;
  }

  MbCmd.BiosNonceValue = 0; // Nonce value is not required for this cmd
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = UpdateFirmware;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = UpdateFwWithOffsets;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  //MbCmd.MbCmd1Reg.Bits.BH_MB_Type = BIOS_FW;
  MbCmd.OutputPayloadPtr = NULL;
  MbCmd.OutputPayloadSizeDw = 0;
  MbCmd.InputPayloadPtr = InputPayloadPtr;
  MbCmd.InputPayloadSizeDw = InputPayloadSizeDw;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  //MbCmd.MbCmd0Reg.Bits_Type1.TT = 0;
  MbCmd.MbCmd0Reg.Bits_Type1.Packet = PacketNo; // Set the current Packet number

  // Initial transfer bit TT is already initialized as 00
  // Issuing command for first/Initial transfer
  DEBUG ((DEBUG_INFO, "Initiating Update Firmware of 3DXP Far memory device\n"));
  status = IssueMailboxCommand (MbCmd);
  return status;
}



EFI_STATUS
EFIAPI
ContinueUpdateFirmwareCommand (
  UINT8 *DeviceReturnStatus, UINT32 *InputPayloadPtr, UINT8 InputPayloadSizeDw, UINT16 PacketNo
  ) {

  MAILBOX_CMD MbCmd;
  EFI_STATUS status;

  //
  // Basic sanity check for parameters
  //
  if (!InputPayloadPtr || !(InputPayloadSizeDw) || PacketNo) {
    DEBUG ((DEBUG_INFO, "Invalid parameters\n"));
    return EFI_INVALID_PARAMETER;
  }

  MbCmd.BiosNonceValue = 0; // Nonce value is not required for this cmd
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = UpdateFirmware;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = UpdateFwWithOffsets;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  //MbCmd.MbCmd1Reg.Bits.BH_MB_Type = BIOS_FW;
  MbCmd.OutputPayloadPtr = NULL;
  MbCmd.OutputPayloadSizeDw = 0;
  MbCmd.InputPayloadPtr = InputPayloadPtr;
  MbCmd.InputPayloadSizeDw = InputPayloadSizeDw;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  MbCmd.MbCmd0Reg.Bits_Type1.TT = 01; // For the Continue Transfer
  MbCmd.MbCmd0Reg.Bits_Type1.Packet = PacketNo; // Set the current Packet number

  // Issuing command for Continue transfer
  DEBUG ((DEBUG_INFO, "Continuing Update Firmware : Sending Packet number %d\n", MbCmd.MbCmd0Reg.Bits_Type1.Packet));
  status = IssueMailboxCommand (MbCmd);
  return status;
}


// TBD check if Packet no field is required by the device fw
EFI_STATUS
EFIAPI
EndUpdateFirmwareCommand (
  UINT8 *DeviceReturnStatus, UINT32 *InputPayloadPtr, UINT8 InputPayloadSizeDw, UINT16 PacketNo
  ) {

  MAILBOX_CMD MbCmd;
  EFI_STATUS status;

  //
  // Basic sanity check for parameters
  //
  if (!InputPayloadPtr || !(InputPayloadSizeDw) || PacketNo) {
    DEBUG ((DEBUG_INFO, "Invalid parameters\n"));
    return EFI_INVALID_PARAMETER;
  }

  MbCmd.BiosNonceValue = 0; // Nonce value is not required for this cmd
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = UpdateFirmware;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = UpdateFwWithOffsets;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  //MbCmd.MbCmd1Reg.Bits.BH_MB_Type = BIOS_FW;
  MbCmd.OutputPayloadPtr = NULL;
  MbCmd.OutputPayloadSizeDw = 0;
  MbCmd.InputPayloadPtr = InputPayloadPtr;
  MbCmd.InputPayloadSizeDw = InputPayloadSizeDw;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  MbCmd.MbCmd0Reg.Bits_Type1.TT = 2; // For End Transfer 10b
  MbCmd.MbCmd0Reg.Bits_Type1.Packet = PacketNo; // Set the current Packet number

  // Issuing End of transfer command
  DEBUG ((DEBUG_INFO, "Issuing End of Update Firmware command : Sending Packet number %d\n", MbCmd.MbCmd0Reg.Bits_Type1.Packet));
  status = IssueMailboxCommand (MbCmd);
  return status;
}



//
// Activate Firmware
// Used to force the execution of a newly updated FW image once the FW image has been downloaded in the same boot cycle.
// This command is only available thru the BIOS mailbox and only after a successful Update FW command has executed.
//
EFI_STATUS EFIAPI ActivateFwCommand (UINT8 *DeviceReturnStatus) {

  MAILBOX_CMD MbCmd;
  EFI_STATUS status;

  MbCmd.BiosNonceValue = 0; // Nonce value is not required for this cmd
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = UpdateFirmware;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = ActivateFw;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  MbCmd.MbCmd1Reg.Bits.BH_MB_Type = BIOS_FW;
  MbCmd.OutputPayloadPtr = NULL;
  MbCmd.OutputPayloadSizeDw = 0;
  MbCmd.InputPayloadPtr = NULL;
  MbCmd.InputPayloadSizeDw = 0;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  DEBUG ((DEBUG_INFO, "Issuing Activate Firmware Command to 3DXP Far memory device\n"));
  status = IssueMailboxCommand(MbCmd);
  return status;
}



//
// Identify 2LM MODULE Device
// There are no input parameters
// These commands return device specific information and various device characteristics
//
EFI_STATUS EFIAPI Identify2lmModuleCommand (UINT8 *DeviceReturnStatus, UINT32 *OutputPayloadPtr, UINT8 OutputPayloadSizeDw) {

  MAILBOX_CMD MbCmd;
  EFI_STATUS status;

  //
  // Basic sanity check for parameters
  //
  if (!OutputPayloadPtr || !(OutputPayloadSizeDw)) {
    DEBUG ((DEBUG_INFO, "Invalid parameters\n"));
    return EFI_INVALID_PARAMETER;
  }

  if (OutputPayloadSizeDw < 36) { // 144 bytes
    DEBUG ((DEBUG_INFO, "Payload size is not enough to hold complete output of this command\n"));
  }

  MbCmd.BiosNonceValue = 0; // Nonce value is not required for this cmd
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = Identify2lmModule;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = Identify;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  MbCmd.MbCmd1Reg.Bits.BH_MB_Type = BIOS_FW;
  MbCmd.OutputPayloadPtr = OutputPayloadPtr;
  MbCmd.OutputPayloadSizeDw = OutputPayloadSizeDw ;
  MbCmd.InputPayloadPtr = NULL;
  MbCmd.InputPayloadSizeDw = 0;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  DEBUG ((DEBUG_INFO, "Getting 2LM Module details from 3DXP Far Memory Device\n"));
  status = IssueMailboxCommand(MbCmd);
  return status;
}



//
// Device Characteristics (01h)
// There are no input parameters
// This command returns various device characteristics, these are typically vendor specific characteristics
//
EFI_STATUS EFIAPI IdentifyDeviceCharacteristicsCommand (UINT8 *DeviceReturnStatus, UINT32 *OutputPayloadPtr, UINT8 OutputPayloadSizeDw) {

  MAILBOX_CMD MbCmd;
  EFI_STATUS status;

  //
  // Basic sanity check for parameters
  //
  if (!OutputPayloadPtr || !(OutputPayloadSizeDw)) {
    DEBUG ((DEBUG_INFO, "Invalid parameters\n"));
    return EFI_INVALID_PARAMETER;
  }
  if (OutputPayloadSizeDw < 2) { // 8 bytes
    DEBUG ((DEBUG_INFO, "Payload size is not enough to hold complete output of this command\n"));
  }

  MbCmd.BiosNonceValue = 0; // Nonce value is not required for this cmd
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = Identify2lmModule;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = DeviceCharacteristics;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  MbCmd.MbCmd1Reg.Bits.BH_MB_Type = BIOS_FW;
  MbCmd.OutputPayloadPtr = OutputPayloadPtr;
  MbCmd.OutputPayloadSizeDw = OutputPayloadSizeDw ;
  MbCmd.InputPayloadPtr = NULL;
  MbCmd.InputPayloadSizeDw = 0;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  DEBUG ((DEBUG_INFO, "Getting 2LM Module Characteristics from 3DXP Far Memory Device\n"));
  status = IssueMailboxCommand(MbCmd);
  return status;
}




/*
 * Following Commands are BIOS only Commands (allowed to be )
 * */

// Set Security BIOS Nonce command
// This command should only be utilized by the platform FW. No other SW should be allowed to set the BIOS Security Nonce.
// Once the security nonce is set, every mailbox command must receive the correct security nonce with the command to be executed.
// Until the nonce is set, it is ignored for all incoming mailbox commands.

// BIOS will set and forget this nonce value
// No need to store the nonce value for the boot cycle as BIOS won't be issuing any BIOS only commands after setting the nonce value for that boot cycle
// Nonce can NOT be set to all 0's
//

EFI_STATUS
EFIAPI
SetSecurityBiosNonceCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT64    NonceValue
  ) {

  MAILBOX_CMD MbCmd;
  EFI_STATUS status;

  // Generate 64bit random value for BIOS Nonce -> this would be done by the upper layer function
  // NonceValue = GetRandomNumber64();
  if (!NonceValue) {
    DEBUG ((DEBUG_INFO, "Invalid Nonce value\n"));
    return EFI_INVALID_PARAMETER;
  }

  MbCmd.BiosNonceValue = 0; // Nonce value is not required for this cmd
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = SetSecurityInfo;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = SetBiosSecurityNonce;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  MbCmd.MbCmd1Reg.Bits.BH_MB_Type = BIOS_FW;
  MbCmd.OutputPayloadPtr = NULL;
  MbCmd.OutputPayloadSizeDw = 0 ;
  MbCmd.InputPayloadPtr = (UINT32 *)&NonceValue;
  MbCmd.InputPayloadSizeDw = 2; //Nonce value is 64bit
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  DEBUG ((DEBUG_INFO, "Setting Security BIOS Nonce\n"));
  status = IssueMailboxCommand(MbCmd);
  NonceValue = 0;   // Clearing the Nonce variable
  return status;
}




//05h Set Features  Modifies settings for a 2LM MODULE.
//00h Reset All Thresholds
/************ Details are not mentioned in FIS 0.6***************/




// This command is used to set the date/time of the 2LM Module. BIOS is required to set this at every boot.
// Since the FFW does not have access to an RTC, the BIOS is needed to set the time so that logging and other time-sensitive features can be used appropriately.
EFI_STATUS
EFIAPI
SetSystemTimeCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT64     SystemTimeInput
) {

  MAILBOX_CMD MbCmd;
  EFI_STATUS status;

  if (!SystemTime) {
    DEBUG ((DEBUG_INFO, "Invalid System time value\n"));
    return EFI_INVALID_PARAMETER;
  }

  MbCmd.BiosNonceValue = 0; // Nonce value is not required for this cmd
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = SetAdminFeatures;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = SystemTime;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  MbCmd.MbCmd1Reg.Bits.BH_MB_Type = BIOS_FW;
  MbCmd.OutputPayloadPtr = NULL;
  MbCmd.OutputPayloadSizeDw = 0 ;
  MbCmd.InputPayloadPtr = (UINT32 *)(&SystemTimeInput);
  MbCmd.InputPayloadSizeDw = 2; //systemtimeinput value is 64bit
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  DEBUG ((DEBUG_INFO, "Setting Security BIOS Nonce\n"));
  status = IssueMailboxCommand(MbCmd);
  return status;
}



// This command is a BIOS only command that performs a configuration lock for the current boot cycle.
// BIOS will make this call prior to transitioning to the OS. This call is only available to BIOS.
// There are no input payload values for this command.
// Nonce value is set before the config lock cmd and since config lock is Bios only cmd, Bios need to send proper nonce value for this cmd
// Note: On a Warm Reset, FW will receive an interrupt and undo the Config Lockdown so BIOS will regain access in order to update/change settings
// and MUST call this command again before transitioning forward.
EFI_STATUS
EFIAPI
SetConfigLockdownCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT64    BiosNonceValue
  ) {

  MAILBOX_CMD MbCmd;
  EFI_STATUS status;

  if (!BiosNonceValue) {
    DEBUG ((DEBUG_INFO, "Invalid BIOS Nonce value\n"));
    return EFI_INVALID_PARAMETER;
  }

  MbCmd.BiosNonceValue = BiosNonceValue;
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = SetAdminFeatures;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = ConfigLockdown;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  MbCmd.MbCmd1Reg.Bits.BH_MB_Type = BIOS_FW;
  MbCmd.OutputPayloadPtr = NULL;
  MbCmd.OutputPayloadSizeDw = 0;
  MbCmd.InputPayloadPtr = NULL;
  MbCmd.InputPayloadSizeDw = 0;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  DEBUG ((DEBUG_INFO, "Setting Config Lock\n"));
  status = IssueMailboxCommand(MbCmd);
  BiosNonceValue = 0;   // Clearing the BIOS Nonce value
  return status;
}




// This command returns BIOS stored boot information in outbox.
EFI_STATUS
EFIAPI
GetBiosBootInfoCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN OUT  UINT8     OutputPayloadSizeDw
  ){

  MAILBOX_CMD MbCmd;
  EFI_STATUS status;

  //
  // Basic sanity check for parameters
  //
  if (!OutputPayloadPtr || !(OutputPayloadSizeDw)) {
    DEBUG ((DEBUG_INFO, "Invalid parameters\n"));
    return EFI_INVALID_PARAMETER;
  }
//  if (OutputPayloadSizeDw < x) { // @todo fill-in the size based on the bios boot info size
//    DEBUG ((DEBUG_INFO, "Payload size is not enough to hold complete output of this command\n"));
//  }

  MbCmd.BiosNonceValue = 0;
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = GetLogPage;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = BiosBootInfo;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  MbCmd.MbCmd1Reg.Bits.BH_MB_Type = BIOS_FW;
  MbCmd.OutputPayloadPtr = OutputPayloadPtr;
  MbCmd.OutputPayloadSizeDw = OutputPayloadSizeDw;
  MbCmd.InputPayloadPtr = NULL;
  MbCmd.InputPayloadSizeDw = 0;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  DEBUG ((DEBUG_INFO, "Getting Bios Boot Info\n"));
  status = IssueMailboxCommand(MbCmd);
  return status;
}



// This command is used to enable injection within the part. This command is only accessible over the BIOS mailbox.
EFI_STATUS
EFIAPI
EnableInjectionCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT8     InjectionStatus
  ){

  MAILBOX_CMD MbCmd;
  EFI_STATUS status;
  UINT32 Input = InjectionStatus; // As VDM write need to be DW aligned

  MbCmd.BiosNonceValue = 0;
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = InjectError;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = EnableInjection;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  MbCmd.MbCmd1Reg.Bits.BH_MB_Type = BIOS_FW;
  MbCmd.OutputPayloadPtr = NULL;
  MbCmd.OutputPayloadSizeDw = 0;
  MbCmd.InputPayloadPtr = &Input;
  MbCmd.InputPayloadSizeDw = 1;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  DEBUG ((DEBUG_INFO, "Setting injection functionality\n"));
  status = IssueMailboxCommand(MbCmd);
  return status;
}



// This command allows storing the BIOS boot information.
EFI_STATUS
EFIAPI
SetBiosBootInfoCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT32    *InputPayloadPtr,
  IN      UINT8     InputPayloadSizeDw
  ){

  MAILBOX_CMD MbCmd;
  EFI_STATUS status;

  //
  // Basic sanity check for parameters
  //
  if (!InputPayloadPtr || !(InputPayloadSizeDw)) {
    DEBUG ((DEBUG_INFO, "Invalid parameters\n"));
    return EFI_INVALID_PARAMETER;
  }

  MbCmd.BiosNonceValue = 0;
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = SetLogPage;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = BiosBootInfo;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  MbCmd.MbCmd1Reg.Bits.BH_MB_Type = BIOS_FW;
  MbCmd.OutputPayloadPtr = NULL;
  MbCmd.OutputPayloadSizeDw = 0;
  MbCmd.InputPayloadPtr = InputPayloadPtr;
  MbCmd.InputPayloadSizeDw = InputPayloadSizeDw;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  DEBUG ((DEBUG_INFO, "Setting Bios Boot Info\n"));
  status = IssueMailboxCommand(MbCmd);
  return status;
}


// This command allows the setting of the various fields.
EFI_STATUS
EFIAPI
SetTempAndPowerSettingsCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT32    *InputPayloadPtr,
  IN      UINT8     InputPayloadSizeDw
  ){

  MAILBOX_CMD MbCmd;
  EFI_STATUS status;

  //
  // Basic sanity check for parameters
  //
  if (!InputPayloadPtr || !(InputPayloadSizeDw)) {
    DEBUG ((DEBUG_INFO, "Invalid parameters\n"));
    return EFI_INVALID_PARAMETER;
  }

  MbCmd.BiosNonceValue = 0;
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = SetLogPage;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = TempAndPowerSettings;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  MbCmd.MbCmd1Reg.Bits.BH_MB_Type = BIOS_FW;
  MbCmd.OutputPayloadPtr = NULL;
  MbCmd.OutputPayloadSizeDw = 0;
  MbCmd.InputPayloadPtr = InputPayloadPtr;
  MbCmd.InputPayloadSizeDw = InputPayloadSizeDw;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  DEBUG ((DEBUG_INFO, "Setting Temp And Power Settings\n"));
  status = IssueMailboxCommand(MbCmd);
  return status;
}


// This command allows the setting of the various HW parameters.
EFI_STATUS
EFIAPI
SetHwParametersCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT32    *InputPayloadPtr,
  IN      UINT8     InputPayloadSizeDw
  ){

  MAILBOX_CMD MbCmd;
  EFI_STATUS status;

  //
  // Basic sanity check for parameters
  //
  if (!InputPayloadPtr || !(InputPayloadSizeDw)) {
    DEBUG ((DEBUG_INFO, "Invalid parameters\n"));
    return EFI_INVALID_PARAMETER;
  }

  MbCmd.BiosNonceValue = 0;
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = SetLogPage;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = HwParameters;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  MbCmd.MbCmd1Reg.Bits.BH_MB_Type = BIOS_FW;
  MbCmd.OutputPayloadPtr = NULL;
  MbCmd.OutputPayloadSizeDw = 0;
  MbCmd.InputPayloadPtr = InputPayloadPtr;
  MbCmd.InputPayloadSizeDw = InputPayloadSizeDw;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  DEBUG ((DEBUG_INFO, "Setting Hw Parameters\n"));
  status = IssueMailboxCommand(MbCmd);
  return status;
}


// This command retrieves the current health of the system, including SMART information.
EFI_STATUS
EFIAPI
GetSmartAndHealthInfoCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw
  ){

  MAILBOX_CMD MbCmd;
  EFI_STATUS Status;

  //
  // Basic sanity check for parameters
  //
  if (!OutputPayloadPtr || !(OutputPayloadSizeDw)) {
    DEBUG ((DEBUG_INFO, "Invalid parameters\n"));
    return EFI_INVALID_PARAMETER;
  }

  MbCmd.BiosNonceValue = 0;
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = GetLogPage;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = SmartAndHealthInfo;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  //MbCmd.MbCmd1Reg.Bits.BH_MB_Type = HOST_OS;
  MbCmd.OutputPayloadPtr = OutputPayloadPtr;
  MbCmd.OutputPayloadSizeDw = OutputPayloadSizeDw;
  MbCmd.InputPayloadPtr = NULL;
  MbCmd.InputPayloadSizeDw = 0;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  DEBUG ((DEBUG_INFO, "Getting Smart and Health Info\n"));
  Status = IssueMailboxCommand(MbCmd);
  DEBUG ((DEBUG_INFO, "Status: %r\n", Status));
  return Status;
}


// This command retrieves the Smart threshold information.
EFI_STATUS
EFIAPI
GetSmartThresholdCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw
  ){

  MAILBOX_CMD MbCmd;
  EFI_STATUS Status;

  //
  // Basic sanity check for parameters
  //
  if (!OutputPayloadPtr || !(OutputPayloadSizeDw)) {
    DEBUG ((DEBUG_INFO, "Invalid parameters\n"));
    return EFI_INVALID_PARAMETER;
  }

  MbCmd.BiosNonceValue = 0;
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = GetLogPage;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = SmartThresholds;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  //MbCmd.MbCmd1Reg.Bits.BH_MB_Type = HOST_OS;
  MbCmd.OutputPayloadPtr = OutputPayloadPtr;
  MbCmd.OutputPayloadSizeDw = OutputPayloadSizeDw;
  MbCmd.InputPayloadPtr = NULL;
  MbCmd.InputPayloadSizeDw = 0;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  DEBUG ((DEBUG_INFO, "Getting Smart and Health Info\n"));
  Status = IssueMailboxCommand(MbCmd);
  DEBUG ((DEBUG_INFO, "Status: %r\n", Status));
  return Status;
}


// This command allows the setting of Smart Threshold
EFI_STATUS
EFIAPI
SetSmartThresholdCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT32    *InputPayloadPtr,
  IN      UINT8     InputPayloadSizeDw
  ){
  MAILBOX_CMD MbCmd;
  EFI_STATUS status;
  //
  // Basic sanity check for parameters
  //
  if (!InputPayloadPtr || !(InputPayloadSizeDw)) {
    DEBUG ((DEBUG_INFO, "Invalid parameters\n"));
    return EFI_INVALID_PARAMETER;
  }
  MbCmd.BiosNonceValue = 0;
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = SetLogPage;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = SmartThresholds;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  //MbCmd.MbCmd1Reg.Bits.BH_MB_Type = HOST_OS;
  MbCmd.OutputPayloadPtr = NULL;
  MbCmd.OutputPayloadSizeDw = 0;
  MbCmd.InputPayloadPtr = InputPayloadPtr;
  MbCmd.InputPayloadSizeDw = InputPayloadSizeDw;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;
  DEBUG ((DEBUG_INFO, "Setting Smart Threshold\n"));
  status = IssueMailboxCommand(MbCmd);
  return status;
}


// This command identifies the running firmware version.
EFI_STATUS
EFIAPI
GetFirmwareImageInfoCommand (
  OUT     UINT8      *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw
  ) {

  MAILBOX_CMD MbCmd;
  EFI_STATUS Status;
  //
  // Basic sanity check for parameters
  //
  if (!OutputPayloadPtr || !(OutputPayloadSizeDw)) {
    DEBUG ((DEBUG_INFO, "Invalid parameters\n"));
    return EFI_INVALID_PARAMETER;
  }
  MbCmd.BiosNonceValue = 0;
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = GetLogPage;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = FirmwareImageInfo;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  //MbCmd.MbCmd1Reg.Bits.BH_MB_Type = HOST_OS;
  MbCmd.OutputPayloadPtr = OutputPayloadPtr;
  MbCmd.OutputPayloadSizeDw = OutputPayloadSizeDw;
  MbCmd.InputPayloadPtr = NULL;
  MbCmd.InputPayloadSizeDw = 0;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  DEBUG ((DEBUG_INFO, "Getting Firmware Image Info\n"));
  Status = IssueMailboxCommand(MbCmd);
  DEBUG ((DEBUG_INFO, "Status: %r\n", Status));
  return Status;
}


// The Command Effect Info reports the size via number of Command Effect Entry count.
// This allows the host to pre-allocate the appropriate size buffer to satisfy a call to  Command Effect Log.
EFI_STATUS
EFIAPI
GetCommandEffectInfoCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw
  ) {
  MAILBOX_CMD MbCmd;
  EFI_STATUS Status;
  //
  // Basic sanity check for parameters
  //
  if (!OutputPayloadPtr || !(OutputPayloadSizeDw)) {
    DEBUG ((DEBUG_INFO, "Invalid parameters\n"));
    return EFI_INVALID_PARAMETER;
  }
  MbCmd.BiosNonceValue = 0;
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = GetLogPage;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = CommandEffectInfo;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  //MbCmd.MbCmd1Reg.Bits.BH_MB_Type = HOST_OS;
  MbCmd.OutputPayloadPtr = OutputPayloadPtr;
  MbCmd.OutputPayloadSizeDw = OutputPayloadSizeDw;
  MbCmd.InputPayloadPtr = NULL;
  MbCmd.InputPayloadSizeDw = 0;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  DEBUG ((DEBUG_INFO, "Getting Command Effect Info\n"));
  Status = IssueMailboxCommand(MbCmd);
  DEBUG ((DEBUG_INFO, "Status: %r\n", Status));
  return Status;
}


// The Command Effect Log is a variable length log page that reports the support for each NVM 2LM MODULE FW Command
// and the effect each command will have on the NV2LM MODULE subsystem.
// more details TBD
EFI_STATUS
EFIAPI
GetCommandEffectLogCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw,
  IN      UINT8     PageOffset
  ) {
  MAILBOX_CMD MbCmd;
  EFI_STATUS Status;
  //
  // Basic sanity check for parameters
  //
  if (!OutputPayloadPtr || !(OutputPayloadSizeDw)) {
    DEBUG ((DEBUG_INFO, "Invalid parameters\n"));
    return EFI_INVALID_PARAMETER;
  }
  MbCmd.BiosNonceValue = 0;
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd0Reg.Bits_Type3.PageOffset = PageOffset;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = GetLogPage;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = CommandEffectLog;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  //MbCmd.MbCmd1Reg.Bits.BH_MB_Type = HOST_OS;
  MbCmd.OutputPayloadPtr = OutputPayloadPtr;
  MbCmd.OutputPayloadSizeDw = OutputPayloadSizeDw;
  MbCmd.InputPayloadPtr = NULL;
  MbCmd.InputPayloadSizeDw = 0;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  DEBUG ((DEBUG_INFO, "Getting Command Effect Log\n"));
  Status = IssueMailboxCommand(MbCmd);
  DEBUG ((DEBUG_INFO, "Status: %r\n", Status));
  return Status;
}


// This command returns the Label information storage are characteristics of the persistent memory region of the 2LM module.
EFI_STATUS
EFIAPI
GetLabelInfoCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw,
  IN      UINT8     RegionId
  ) {
  MAILBOX_CMD MbCmd;
  EFI_STATUS Status;
  //
  // Basic sanity check for parameters
  //
  if (!OutputPayloadPtr || !(OutputPayloadSizeDw)) {
    DEBUG ((DEBUG_INFO, "Invalid parameters\n"));
    return EFI_INVALID_PARAMETER;
  }
  MbCmd.BiosNonceValue = 0;
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd0Reg.Bits_Type2.LabelCmdRegionId = RegionId;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = LabelData;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = GetLabelInfo;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  //MbCmd.MbCmd1Reg.Bits.BH_MB_Type = HOST_OS;
  MbCmd.OutputPayloadPtr = OutputPayloadPtr;
  MbCmd.OutputPayloadSizeDw = OutputPayloadSizeDw;
  MbCmd.InputPayloadPtr = NULL;
  MbCmd.InputPayloadSizeDw = 0;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  DEBUG ((DEBUG_INFO, "Getting Label Info\n"));
  Status = IssueMailboxCommand(MbCmd);
  DEBUG ((DEBUG_INFO, "Status: %r\n", Status));
  return Status;
}



// This command returns the label information data at a given offset.
EFI_STATUS
EFIAPI
GetLabelDataCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw,
  IN      UINT8     RegionId
//  IN      UINT32     Offset,
//  IN      UINT32     TransferLength
  ) {
  MAILBOX_CMD MbCmd;
  EFI_STATUS Status;
//  UINT32 Input[2];
//  Input[0] = Offset;
//  Input[1] = TransferLength;
  //
  // Basic sanity check for parameters
  //
  if (!OutputPayloadPtr || !(OutputPayloadSizeDw)) {
    DEBUG ((DEBUG_INFO, "Invalid parameters\n"));
    return EFI_INVALID_PARAMETER;
  }
  MbCmd.BiosNonceValue = 0;
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd0Reg.Bits_Type2.LabelCmdRegionId = RegionId;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = LabelData;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = GetLabelData;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  //MbCmd.MbCmd1Reg.Bits.BH_MB_Type = HOST_OS;
  MbCmd.OutputPayloadPtr = OutputPayloadPtr;
  MbCmd.OutputPayloadSizeDw = OutputPayloadSizeDw;
  //MbCmd.InputPayloadPtr = Input;
  MbCmd.InputPayloadPtr = OutputPayloadPtr;
  MbCmd.InputPayloadSizeDw = 2;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  DEBUG ((DEBUG_INFO, "Getting Label Data\n"));
  Status = IssueMailboxCommand(MbCmd);
  DEBUG ((DEBUG_INFO, "Status: %r\n", Status));
  return Status;
}


// This command sets the label data for at a given offset of the label storage area.
EFI_STATUS
EFIAPI
SetLabelDataCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT32    *InputPayloadPtr,
  IN      UINT8     InputPayloadSizeDw,
  IN      UINT8     RegionId
//  IN      UINT8     Offset,
//  IN      UINT8     TransferLength
  ) {
  MAILBOX_CMD MbCmd;
  EFI_STATUS Status;
/*
  UINT32 Input[2];
  Input[0] = Offset;
  Input[1] = TransferLength;
*/
  //
  // Basic sanity check for parameters
  //
  if (!InputPayloadPtr || !(InputPayloadSizeDw)) {
    DEBUG ((DEBUG_INFO, "Invalid parameters\n"));
    return EFI_INVALID_PARAMETER;
  }
  MbCmd.BiosNonceValue = 0;
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd0Reg.Bits_Type2.LabelCmdRegionId = RegionId;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = LabelData;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = SetLabelData;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  //MbCmd.MbCmd1Reg.Bits.BH_MB_Type = HOST_OS;
  MbCmd.OutputPayloadPtr = NULL;
  MbCmd.OutputPayloadSizeDw = 0;
  MbCmd.InputPayloadPtr = InputPayloadPtr;
  MbCmd.InputPayloadSizeDw = InputPayloadSizeDw;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  DEBUG ((DEBUG_INFO, "Setting Label Data\n"));
  Status = IssueMailboxCommand(MbCmd);
  DEBUG ((DEBUG_INFO, "Status: %r\n", Status));
  return Status;
}

// This command is used to scrub for errors on the 2LM Module's PM Region only (scrubs can NOT be done on 2LM memory).
EFI_STATUS
EFIAPI
SetAddressRangeScrubCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT32    *InputPayloadPtr,
  IN      UINT8     InputPayloadSizeDw
  ) {
  MAILBOX_CMD MbCmd;
  EFI_STATUS Status;
  //
  // Basic sanity check for parameters
  //
  if (!InputPayloadPtr || !(InputPayloadSizeDw)) {
    DEBUG ((DEBUG_INFO, "Invalid parameters\n"));
    return EFI_INVALID_PARAMETER;
  }
  MbCmd.BiosNonceValue = 0;
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = SetFeatures;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = AddressRangeScrub;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  //MbCmd.MbCmd1Reg.Bits.BH_MB_Type = HOST_OS;
  MbCmd.OutputPayloadPtr = NULL;
  MbCmd.OutputPayloadSizeDw = 0;
  MbCmd.InputPayloadPtr = InputPayloadPtr;
  MbCmd.InputPayloadSizeDw = InputPayloadSizeDw;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  DEBUG ((DEBUG_INFO, "Setting Address Range Scrub\n"));
  Status = IssueMailboxCommand(MbCmd);
  DEBUG ((DEBUG_INFO, "Status: %r\n", Status));
  return Status;
}

// This command is used to retrieve the values for the Address Range Scrub.
EFI_STATUS
EFIAPI
GetAddressRangeScrubCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw
  ) {
  MAILBOX_CMD MbCmd;
  EFI_STATUS Status;
  //
  // Basic sanity check for parameters
  //
  if (!OutputPayloadPtr || !(OutputPayloadSizeDw)) {
    DEBUG ((DEBUG_INFO, "Invalid parameters\n"));
    return EFI_INVALID_PARAMETER;
  }
  MbCmd.BiosNonceValue = 0;
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = GetFeatures;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = AddressRangeScrub;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  //MbCmd.MbCmd1Reg.Bits.BH_MB_Type = HOST_OS;
  MbCmd.OutputPayloadPtr = OutputPayloadPtr;
  MbCmd.OutputPayloadSizeDw = OutputPayloadSizeDw;
  MbCmd.InputPayloadPtr = NULL;
  MbCmd.InputPayloadSizeDw = 0;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  DEBUG ((DEBUG_INFO, "Getting Address Range Scrub data\n"));
  Status = IssueMailboxCommand(MbCmd);
  DEBUG ((DEBUG_INFO, "Status: %r\n", Status));
  return Status;
}

// This command is used to get the long operation status.
EFI_STATUS
EFIAPI
GetLongOperationStatusCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw
  ) {
  MAILBOX_CMD MbCmd;
  EFI_STATUS Status;
  //
  // Basic sanity check for parameters
  //
  if (!OutputPayloadPtr || !(OutputPayloadSizeDw)) {
    DEBUG ((DEBUG_INFO, "Invalid parameters\n"));
    return EFI_INVALID_PARAMETER;
  }
  MbCmd.BiosNonceValue = 0;
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = GetLogPage;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = LongOperationStatus;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  //MbCmd.MbCmd1Reg.Bits.BH_MB_Type = HOST_OS;
  MbCmd.OutputPayloadPtr = OutputPayloadPtr;
  MbCmd.OutputPayloadSizeDw = OutputPayloadSizeDw;
  MbCmd.InputPayloadPtr = NULL;
  MbCmd.InputPayloadSizeDw = 0;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  DEBUG ((DEBUG_INFO, "Getting Long Opeartion Status\n"));
  Status = IssueMailboxCommand(MbCmd);
  DEBUG ((DEBUG_INFO, "Status: %r\n", Status));
  return Status;
}


// This command instructs the 2LM Module whether to latch the SMART Last Shutdown Status and SMART Unsafe Shutdown Count.
// If the latch is enabled, on the next power-down, power-up sequence the SMART LSS & SMART Unsafe Shutdown Count will be latched.
// This is a single shot setting, after latching it gets disabled until this command enables it again.
// The latched values will persist on the 2LM Module and they can be only be overwritten if the latch is enabled again
// and a powerdown, power-up sequence occurs.
EFI_STATUS
EFIAPI
SetLatchSystemShutdownStateCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT32    *InputPayloadPtr,
  IN      UINT8     InputPayloadSizeDw
//  IN      UINT8     ShutdownStatus    // though i/p payload size is 1 byte,Mailbox r/w granularity is 1 DW
  ) {
  MAILBOX_CMD MbCmd;
  EFI_STATUS Status;
//  UINT32 Input;

//  Input = (UINT32)ShutdownStatus;
  MbCmd.BiosNonceValue = 0;
  MbCmd.MbCmd0Reg.Data = 0;
  MbCmd.MbCmd1Reg.Data = 0;
  MbCmd.MbCmd1Reg.Bits.FwMbOpcode = SetAdminFeatures;
  MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = LatchSystemShutdownState;
  MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
  MbCmd.MbCmd1Reg.Bits.BH_MB_Type = BIOS_FW;
  MbCmd.OutputPayloadPtr = NULL;
  MbCmd.OutputPayloadSizeDw = 0;
  MbCmd.InputPayloadPtr = InputPayloadPtr;
  MbCmd.InputPayloadSizeDw = InputPayloadSizeDw;
  MbCmd.DeviceReturnStatus = DeviceReturnStatus;

  DEBUG ((DEBUG_INFO, "Setting Latch System Shutdown State\n"));
  Status = IssueMailboxCommand(MbCmd);
  DEBUG ((DEBUG_INFO, "Status: %r\n", Status));
  return Status;
}
