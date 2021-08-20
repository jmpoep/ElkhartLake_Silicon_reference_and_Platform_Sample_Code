/** @file
  This file has SMM wrapper callback which passes FIS command from NVDIMM ASL code.

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

#include "NfitSmm.h"



NVDIMM_NVS            *gNfitNvs;
UINT32                Offset;
UINT32                TransferLength;
UINT64                PMemBase;
UINT64                PMemSize;
UINT16                CmdEffectOpcodeCnt;
UINT16                SupportedModes;
UINT32                FwContext;
UINT8                 InitFwUpdate;
UINT32                Index;
UINT8                 RegionIdPMem;
UpdateFwPacket        FwPacket;

EFI_STATUS
EFIAPI
FisCommandCallback (
  IN EFI_HANDLE                  DispatchHandle,
  IN CONST VOID                  *Context,
  IN OUT VOID                    *CommBuffer,
  IN OUT UINTN                   *CommBufferSize
  )
{
  UINT8       FisFunction;
  EFI_STATUS  Status;
  MAILBOX_CMD MbCmd;
  UINT32      OutputData[3];
  UINT8       DeviceReturnStatus;
  UINT8       OutputPayloadSizeDw;
  UINT8       InputPayloadSizeDw;
  UINT16      PacketNo;
  UINT8       PageOffset;
  UINT16      Type;
  UINT8       Flags;
  UINT64      ArsAddr;
  UINT64      ArsLen;
  UINT32      ArsU32Output[7];
  ARS_OUTPUT_DATA *ArsOutputData;
  UINT16        i;

  DEBUG ((DEBUG_INFO, "FisCommandCallback Entry\n"));

  FisFunction = gNfitNvs->FisFuntionNumber;
  DeviceReturnStatus  = 0;
  PacketNo            = 0;
  PageOffset          = 0;
  ArsAddr             = 0;
  ArsLen              = 0;

  switch (FisFunction) {

    case 1: //Get SMART and Health Info
      OutputPayloadSizeDw = 32; // 128 Bytes
      DEBUG ((DEBUG_INFO, "2LM: Issuing GetSmartAndHealthInfoCommand\n"));
      Status = GetSmartAndHealthInfoCommand (&DeviceReturnStatus, (UINT32 *)gNfitNvs->Buffer, OutputPayloadSizeDw);
      if(Status == EFI_SUCCESS && DeviceReturnStatus == MB_SUCCESS) {
        gNfitNvs->Data1 = 0;
        gNfitNvs->Data2 = 128; //length
        for (i = 0; i < 32; ++i)
        {
          DEBUG ((DEBUG_INFO, "Index %x Output value %x\n", i, gNfitNvs->Buffer[i]));
        }
      } else {
        gNfitNvs->Data1 = 1;
      }
      break;

    case 2: // Get Smart Threshold
      OutputPayloadSizeDw = 2; // 7 Bytes
      DEBUG ((DEBUG_INFO, "2LM: Issuing GetSmartThresholdCommand\n"));
      Status = GetSmartThresholdCommand (&DeviceReturnStatus, (UINT32 *)gNfitNvs->Buffer, OutputPayloadSizeDw);
      if(Status == EFI_SUCCESS ) {// && DeviceReturnStatus == MB_SUCCESS) {
        gNfitNvs->Data1 = 0;
        gNfitNvs->Data2 = 8; //8 bytes length
        for (i = 0; i < 2; ++i)
        {
          DEBUG ((DEBUG_INFO, "Index %x Output value %x\n", i, gNfitNvs->Buffer[i]));
        }
        DEBUG ((DEBUG_INFO, "2LM: Error: DeviceReturnStatus %d\n", DeviceReturnStatus));
      } else {
        gNfitNvs->Data1 = 1;
        DEBUG ((DEBUG_INFO, "2LM: Error: DeviceReturnStatus %d\n", DeviceReturnStatus));
      }
      break;

    case 31: // Get Label Info / _LSI
      OutputPayloadSizeDw = 3; // 12 Bytes
      DEBUG ((DEBUG_INFO, "2LM: Issuing GetLabelInfoCommand\n"));
      Status = GetLabelInfoCommand (&DeviceReturnStatus, (UINT32 *)OutputData, OutputPayloadSizeDw, RegionIdPMem);
      if(Status == EFI_SUCCESS && DeviceReturnStatus == MB_SUCCESS) {
        DEBUG ((DEBUG_INFO, "DWord0: %x\n", OutputData[0]));
        DEBUG ((DEBUG_INFO, "DWord1: %x\n", OutputData[1]));
        DEBUG ((DEBUG_INFO, "DWord2: %x\n", OutputData[2]));
        gNfitNvs->Data1 = 0;
        gNfitNvs->Data2 = OutputData[1];
        gNfitNvs->Data3 = OutputData[2];
      }
      break;

    case 32: // Get Label Data / _LSR
      DEBUG ((DEBUG_INFO, "SMI LabelRead\n"));
      gNfitNvs->Buffer[0]= gNfitNvs->Data1;
      gNfitNvs->Buffer[1]= gNfitNvs->Data2;
      DEBUG ((DEBUG_INFO, "SMI Label Read. Offset = %x, Size in bytes = %x\n", gNfitNvs->Data1, gNfitNvs->Data2));
      Offset = gNfitNvs->Data1;
      TransferLength = (gNfitNvs->Data2); // In bytes
      OutputPayloadSizeDw = (UINT8)(gNfitNvs->Data2/4);
      DEBUG ((DEBUG_INFO, "TransferLength: %x  And OutputPayloadSizeDw: %x \n", TransferLength, OutputPayloadSizeDw));
      DEBUG ((DEBUG_INFO, "2LM: Issuing GetLabelDataCommand\n"));
      Status = GetLabelDataCommand (&DeviceReturnStatus, (UINT32 *)gNfitNvs->Buffer, OutputPayloadSizeDw, RegionIdPMem);
      if (EFI_ERROR(Status)) {
        gNfitNvs->Data1 = 1;
      }
      else if(Status == EFI_SUCCESS && DeviceReturnStatus == MB_SUCCESS) {
        for (i = 0; i < OutputPayloadSizeDw; ++i)
        {
          DEBUG ((DEBUG_INFO, "Index %x value %x\n", i, gNfitNvs->Buffer[i]));
        }
        gNfitNvs->Data1 = 0;
      }
      break;

    case 33: // Set Label Data / _LSW
      DEBUG ((DEBUG_INFO, "SMI LabelWrite\n"));
      for (i = 0; i < 0x40; i++) {
        gNfitNvs->Buffer[i + 0x40] = gNfitNvs->Buffer[i];
      }
      gNfitNvs->Buffer[0]= gNfitNvs->Data1;
      gNfitNvs->Buffer[1]= gNfitNvs->Data2;
      DEBUG ((DEBUG_INFO, "SMI Label Write. Offset = %x, Size in bytes = %x\n", gNfitNvs->Data1, gNfitNvs->Data2));
      for (i = 0; i < (gNfitNvs->Data2/4); ++i)
      {
        DEBUG ((DEBUG_INFO, "Index %x value %x\n", i, gNfitNvs->Buffer[i+0x40]));
      }
      InputPayloadSizeDw = (UINT8)((256 + gNfitNvs->Data2)/4);
      DEBUG ((DEBUG_INFO, "2LM: Issuing SetLabelDataCommand\n"));
      Status = SetLabelDataCommand (&DeviceReturnStatus, (UINT32 *)gNfitNvs->Buffer, InputPayloadSizeDw, RegionIdPMem);
      if (EFI_ERROR(Status)) {
         gNfitNvs->Data1 = 1;
       }
       else {
         gNfitNvs->Data1 = 0;
       }
      break;

    case 7: // Get Command Effect Log Info
      OutputPayloadSizeDw = 1; // 4 Bytes
      DEBUG ((DEBUG_INFO, "2LM: Issuing GetCommandEffectInfoCommand\n"));
      Status = GetCommandEffectInfoCommand (&DeviceReturnStatus, (UINT32 *)gNfitNvs->Buffer, OutputPayloadSizeDw);
      if(Status == EFI_SUCCESS && DeviceReturnStatus == MB_SUCCESS) {
        gNfitNvs->Data1 = 0;
        gNfitNvs->Data2 = 4; //length in bytes
        CmdEffectOpcodeCnt = (UINT16)*(UINT32 *)gNfitNvs->Buffer; //cmd count
        gNfitNvs->Buffer[0] = CmdEffectOpcodeCnt << 3; //converting to bytes
        DEBUG ((DEBUG_INFO, "Data length %d CmdEffectOpcodeCnt %d\n", gNfitNvs->Buffer[0], CmdEffectOpcodeCnt));
      } else {
        gNfitNvs->Data1 = 1;
      }
      break;

    case 8: // Command Effect Log
      DEBUG ((DEBUG_INFO, "CmdEffectOpcodeCnt %d\n", CmdEffectOpcodeCnt));
      if (CmdEffectOpcodeCnt < 64) {
        OutputPayloadSizeDw = (UINT8)CmdEffectOpcodeCnt << 1 ; // Each cmd is 8 bytes (CmdEffectOpcodeCnt*8/4)
        DEBUG ((DEBUG_INFO, "OutputPayloadSizeDw %d CmdEffectOpcodeCnt %d\n", OutputPayloadSizeDw, CmdEffectOpcodeCnt));
        DEBUG ((DEBUG_INFO, "2LM: Issuing GetCommandEffectLogCommand\n"));
        Status = GetCommandEffectLogCommand (&DeviceReturnStatus, (UINT32 *)gNfitNvs->Buffer, OutputPayloadSizeDw, PageOffset);
        if(Status == EFI_SUCCESS && DeviceReturnStatus == MB_SUCCESS) {
          gNfitNvs->Data1 = 0;
          gNfitNvs->Data2 = OutputPayloadSizeDw << 2; //length
          gNfitNvs->Data3 = CmdEffectOpcodeCnt;
          DEBUG ((DEBUG_INFO, "payload size  %d CmdEffectOpcodeCnt %d\n", gNfitNvs->Data2, gNfitNvs->Data3));
          for (i = 0; i < OutputPayloadSizeDw; ++i)
          {
            DEBUG ((DEBUG_INFO, "Index %x Output value %x\n", i, gNfitNvs->Buffer[i]));
          }
        } else {
          gNfitNvs->Data1 = 1;
        }
      } else {
        DEBUG ((DEBUG_INFO, "2LM: GetCommandEffectLogCommand command count is more than 64\n"));
        OutputPayloadSizeDw = 128; // 512 byes
        DEBUG ((DEBUG_INFO, "2LM: Issuing first GetCommandEffectLogCommand\n"));
        Status = GetCommandEffectLogCommand (&DeviceReturnStatus, (UINT32 *)gNfitNvs->Buffer, OutputPayloadSizeDw, PageOffset);
        if(Status == EFI_SUCCESS && DeviceReturnStatus == MB_SUCCESS) {
          PageOffset = 1; // Only if Cmd Opcode exceeds 64
          DEBUG ((DEBUG_INFO, "2LM: Issuing Second GetCommandEffectLogCommand\n"));
          Status = GetCommandEffectLogCommand (&DeviceReturnStatus, (UINT32 *)gNfitNvs->Buffer + 124, OutputPayloadSizeDw, PageOffset);
        }
      }
      break;

    case 9: // Pass Through Command
      MbCmd.BiosNonceValue = 0; // Nonce value is not required for this cmd
      MbCmd.MbCmd0Reg.Data = 2; // Region id
      MbCmd.MbCmd1Reg.Data = 0;
      MbCmd.MbCmd1Reg.Bits.FwMbOpcode = (gNfitNvs->Data1 & 0xFF);
      MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode = (gNfitNvs->Data1 >> 8 & 0xFF);
      MbCmd.MbCmd1Reg.Bits.DB = SET_BIT_HIGH;
      //MbCmd.MbCmd1Reg.Bits.BH_MB_Type = BIOS_FW;
      MbCmd.OutputPayloadPtr = (UINT32 *)gNfitNvs->Buffer;
      MbCmd.OutputPayloadSizeDw = 128; // by default read 512 bytes
      MbCmd.InputPayloadPtr = (UINT32 *)gNfitNvs->Buffer;
      MbCmd.InputPayloadSizeDw = (UINT8)(gNfitNvs->Data2/4);
      MbCmd.DeviceReturnStatus = &DeviceReturnStatus;
      DEBUG ((DEBUG_INFO, "2LM: FwMbOpcode %d FwMbSubOpcode%d\n", MbCmd.MbCmd1Reg.Bits.FwMbOpcode, MbCmd.MbCmd1Reg.Bits.FwMbSubOpcode));
      DEBUG ((DEBUG_INFO, "2LM: InputPayloadSizeDw %d\n", MbCmd.InputPayloadSizeDw));
      for (i = 0; i < MbCmd.InputPayloadSizeDw; ++i)
      {
        DEBUG ((DEBUG_INFO, "Input Index %x value %x\n", i, gNfitNvs->Buffer[i]));
      }
      DEBUG ((DEBUG_INFO, "2LM: Issuing Pass Through Command\n"));
      Status = IssueMailboxCommand(MbCmd);
      DEBUG ((DEBUG_INFO, "Status: %r\n", Status));
      if (EFI_ERROR(Status)) {
        gNfitNvs->Data1 = 1;
      }
      else {
        gNfitNvs->Data1 = 0;
      }
      break;

    case 10: // Enable Latch System Shutdown Status
      DEBUG ((DEBUG_INFO, "2LM:  Enable Latch System Shutdown Status input %d \n", gNfitNvs->Buffer[0]));
      InputPayloadSizeDw = 1; // 1 Byte
      DEBUG ((DEBUG_INFO, "2LM: Issuing SetLatchSystemShutdownStateCommand \n"));
      Status = SetLatchSystemShutdownStateCommand (&DeviceReturnStatus, (UINT32 *)gNfitNvs->Buffer, InputPayloadSizeDw);
      if(Status == EFI_SUCCESS && DeviceReturnStatus == MB_SUCCESS) {
        gNfitNvs->Data1 = 0;
      } else {
        DEBUG ((DEBUG_INFO, "2LM: Error: DeviceReturnStatus is %d \n",DeviceReturnStatus));
        gNfitNvs->Data1 = 1;
      }
      break;

    case 11: // Get Supported Modes
      DEBUG ((DEBUG_INFO, "2LM: Providing supported modes from Identify Cmd\n"));
      gNfitNvs->Buffer[0] = SupportedModes;
      DEBUG ((DEBUG_INFO, "2LM: SupportedModes %d \n", SupportedModes));
      gNfitNvs->Data1 = 0;
      break;

    case 12: // Get Firmware Info
      OutputPayloadSizeDw = 22; // 88 Bytes
      DEBUG ((DEBUG_INFO, "2LM: Issuing GetFirmwareImageInfoCommand\n"));
      Status = GetFirmwareImageInfoCommand (&DeviceReturnStatus, (UINT32 *)gNfitNvs->Buffer, OutputPayloadSizeDw);
      DEBUG ((DEBUG_INFO, "2LM: Hard coded values for GetFirmwareImageInfoCommand\n"));
      gNfitNvs->Buffer[0] = 1572864; //1.5MB
      gNfitNvs->Buffer[1] = 512; //512
      gNfitNvs->Buffer[2] = 1; //us
      gNfitNvs->Buffer[3] = 5;
      gNfitNvs->Buffer[4] = 1;
      gNfitNvs->Buffer[5] = 1;
      gNfitNvs->Buffer[6] = 1;
      gNfitNvs->Buffer[7] = 0;
      gNfitNvs->Buffer[8] = 1;
      gNfitNvs->Buffer[9] = 0;
      gNfitNvs->Buffer[10] = 0;
      for (i = 0; i < 10; ++i)
      {
        DEBUG ((DEBUG_INFO, "Index %x output value %x\n", i, gNfitNvs->Buffer[i]));
      }
      if (EFI_ERROR(Status)) {
         gNfitNvs->Data1 = 1;
       }
       else {
         gNfitNvs->Data1 = 0;
         gNfitNvs->Data2 = 40; //bytes
       }
      break;

    case 17: // Set Smart Threshold Command
      DEBUG ((DEBUG_INFO, "2LM: Inside SetSmartThreshold\n"));
      InputPayloadSizeDw = 2; // 7 Bytes
      DEBUG ((DEBUG_INFO, "SetSmartThreshold input\n"));
      for (i = 0; i < 2; ++i)
      {
        DEBUG ((DEBUG_INFO, "Index %x value %x\n", i, gNfitNvs->Buffer[i]));
      }
      DEBUG ((DEBUG_INFO, "2LM: Issuing SetSmartThresholdCommand\n"));
      Status = SetSmartThresholdCommand (&DeviceReturnStatus, (UINT32 *)gNfitNvs->Buffer, InputPayloadSizeDw);
      //if(Status == EFI_SUCCESS && DeviceReturnStatus == MB_SUCCESS) { }
      //03:Invalid Input ParametersReturned If any threshold value requested to be enabled is invalid.
      if (EFI_ERROR(Status)) {
         gNfitNvs->Data1 = 3;
       } else {
         gNfitNvs->Data1 = 0;
       }
      break;

    case 18: // Inject Error Command
      InputPayloadSizeDw = 2; // 7 Bytes
      DEBUG ((DEBUG_INFO, "2LM: Issuing Inject Error Command\n"));
      //TBD
      break;


    case 21: // Query Address Range Scrub (ARS) Capabilities
      // BIOS doesn't need to issue any FIS command. Client 2LM supports ARS for Persistent Memory and not for Volatile memory region
      DEBUG ((DEBUG_INFO, "2LM: Query ARS Capabilities\n"));
      for (i = 0; i < 16; ++i)
      {
        DEBUG ((DEBUG_INFO, "Input Index %x value %x\n", i, gNfitNvs->Buffer[i]));
      }
      ArsAddr = *(UINT64*)gNfitNvs->Buffer;
      ArsLen  = *(UINT64*)(gNfitNvs->Buffer + 2);
      DEBUG ((DEBUG_INFO, "ARSA = 0x%lx  ARSL = 0x%lx \n", ArsAddr,ArsLen));
      DEBUG ((DEBUG_INFO, "PMemBase = 0x%lx  PMemSize = 0x%lx \n", PMemBase, PMemSize));
      // Check if ARS range falls within PMem region
      if ((ArsAddr >= PMemBase) && ((ArsAddr+ArsLen) <= (PMemBase + PMemSize))) {
        gNfitNvs->Data1 = 0x20000; // Status=0 and Ext Status=0x2
        gNfitNvs->Buffer[0] = 384; // Max Query ARS Status Output Buffer Size is 384 bytes
        gNfitNvs->Buffer[1] = 512; // Clear Uncorrectable Error Range Length Unit Size
        gNfitNvs->Buffer[2] = 0;   // Flags left as 0
      } else {
        gNfitNvs->Data1 = 0x2; // Status = 2 (Invalid parameters) and Ext status= 0
      }
      break;

    case 22: // Set Address Range Scrub
      DEBUG ((DEBUG_INFO, "2LM: Start ARS\n"));
      for (i = 0; i < 16; ++i)
      {
        DEBUG ((DEBUG_INFO, "Input Index %x value %x\n", i, gNfitNvs->Buffer[i]));
      }
      ArsAddr = *(UINT64*)gNfitNvs->Buffer; //[0];
      ArsLen  = *(UINT64*)(gNfitNvs->Buffer+2);//[2];
      Type    = *(UINT16*)(gNfitNvs->Buffer+4);//[4];;
      Flags   = (UINT8)(gNfitNvs->Buffer[4] & 0x0F00);//[4] one byte from offset 18
      DEBUG ((DEBUG_INFO, "ARSA = 0x%lx  ARSL = 0x%lx \t Type = 0x%x  Flags = 0x%x \n", ArsAddr,ArsLen, Type, Flags));
      // Check if ARS range falls within PMem region
      DEBUG ((DEBUG_INFO, "2LM: (ArsAddr+ArsLen) 0x%lx \n", (ArsAddr+ArsLen)));
      DEBUG ((DEBUG_INFO, "2LM: (PMemBase + PMemSize) 0x%lx \n", (PMemBase + PMemSize)));
      if (!((Type == 0x2) && (ArsAddr >= PMemBase) && ((ArsAddr+ArsLen) <= (PMemBase + PMemSize)))) {
        DEBUG ((DEBUG_INFO, "2LM: InValid inputs for start ARS\n"));
        gNfitNvs->Data1 = 2;
        break;
      }
      DEBUG ((DEBUG_INFO, "2LM: Valid inputs for start ARS\n"));
      InputPayloadSizeDw = 5; // 20 Bytes
      // Populate input buffer required by FIS
      gNfitNvs->Buffer[0] = (RegionIdPMem << 8) | 0x1 ; // byte0: enable: 0x1, byte1: RegionId: for Pmem
      *(UINT64*)(gNfitNvs->Buffer +1) = (ArsAddr - PMemBase); //send the region offset to Willard
      *(UINT64*)(gNfitNvs->Buffer +3) = (ArsAddr+ArsLen- PMemBase);
      for (i = 0; i < InputPayloadSizeDw; ++i)
      {
        DEBUG ((DEBUG_INFO, "Input Index %x value %x\n", i, gNfitNvs->Buffer[i]));
      }
      DEBUG ((DEBUG_INFO, "2LM: Issuing SetAddressRangeScrubCommand for startAddr 0x%lx and Length 0x%lx\n", *(UINT64*)(gNfitNvs->Buffer +1), *(UINT64*)(gNfitNvs->Buffer +3)));
      Status = SetAddressRangeScrubCommand (&DeviceReturnStatus, (UINT32*)gNfitNvs->Buffer, InputPayloadSizeDw);
      if (EFI_ERROR(Status)) {
        gNfitNvs->Data1 = 5; //5 : Error, Unknown Reason
        gNfitNvs->Data2 = 0;
        DEBUG ((DEBUG_INFO, "2LM: Error in SetAddressRangeScrubCommand\n"));
        break;
      }
      if ((DeviceReturnStatus != MB_SUCCESS) && (DeviceReturnStatus != DeviceBusy)) {
        DEBUG ((DEBUG_INFO, "2LM: Error in FIS command \n"));
        gNfitNvs->Data1 = 3; //hardware error  if Start ARS FIS commands returns so
        gNfitNvs->Data2 = 0;
        break;
      }
      if ((DeviceReturnStatus != MB_SUCCESS) && (DeviceReturnStatus == DeviceBusy)) {
        // If Device status is DeviceBusy then issue long operation and check if ARS is alreday in progress
        DEBUG ((DEBUG_INFO, "2LM: Issue long operation status cmd to see if ARS already in progress\n"));
        OutputPayloadSizeDw = 31; // 124 bytes
        Status = GetLongOperationStatusCommand (&DeviceReturnStatus, (UINT32*)gNfitNvs->Buffer, OutputPayloadSizeDw);
        if (EFI_ERROR(Status)) {
          gNfitNvs->Data1 = 5; //5  Error  Unknown Reason
          gNfitNvs->Data2 = 0;
          DEBUG ((DEBUG_INFO, "2LM: Error in MB Cmd get long operation status\n"));
          break;
        }
        if (DeviceReturnStatus != MB_SUCCESS) {
            DEBUG ((DEBUG_INFO, "2LM: Error in FIS command get long operation status \n"));
            gNfitNvs->Data1 = 3; //hardware error  if Start ARS FIS commands returns so
            gNfitNvs->Data2 = 0;
            break;
        }
        //check the opcode for long operation
        DEBUG ((DEBUG_INFO, "2LM: Got the long operartion status for cmd opcode 0x%x\n", *(UINT16*)gNfitNvs->Buffer));
        DEBUG ((DEBUG_INFO, "2LM: Percent Complete %d\n", (gNfitNvs->Buffer[0] & 0xFFFF0000)));
        DEBUG ((DEBUG_INFO, "2LM: Estimated Time to Completion %d\n", gNfitNvs->Buffer[1]));
        if (*(UINT16*)gNfitNvs->Buffer == 0x405) {
          DEBUG ((DEBUG_INFO, "2LM: ARS already in progress \n"));
          gNfitNvs->Data1 = 6; //6  ARS already in progress
          gNfitNvs->Data2 = gNfitNvs->Buffer[1]; //Estimated time
          break;
        }
        gNfitNvs->Data1 = 3; //hardware error
        gNfitNvs->Data2 = 0;
        break;
      } // End of device busy condition

      // Now at this point MB Status and DeviceReturnStatus both are successful
      // Issue long operation status cmd to get the estimated time for ARS
      DEBUG ((DEBUG_INFO, "2LM: Issue long operation status cmd to get the estimated time for ARS\n"));
      OutputPayloadSizeDw = 128; // 9 bytes
      Status = GetLongOperationStatusCommand (&DeviceReturnStatus, (UINT32*)gNfitNvs->Buffer, OutputPayloadSizeDw);
      if (EFI_ERROR(Status)) {
        gNfitNvs->Data1 = 5; //5  Error  Unknown Reason
        gNfitNvs->Data2 = 0;
        DEBUG ((DEBUG_INFO, "2LM: Error in get long operation status\n"));
        break;
      }
      if (DeviceReturnStatus != MB_SUCCESS) {
        DEBUG ((DEBUG_INFO, "2LM: Error in FIS command \n"));
        gNfitNvs->Data1 = 3; //hardware error  if Start ARS FIS commands returns so
        gNfitNvs->Data2 = 0;
        break;
      }
      DEBUG ((DEBUG_INFO, "2LM: Got the long operartion status for cmd opcode 0x%x\n", *(UINT16*)gNfitNvs->Buffer));
      DEBUG ((DEBUG_INFO, "2LM: Percent Complete %d\n", (gNfitNvs->Buffer[0] & 0xFFFF0000)));
      DEBUG ((DEBUG_INFO, "2LM: Estimated Time to Completion %d\n", gNfitNvs->Buffer[1]));
      gNfitNvs->Data1 = 0;
      gNfitNvs->Data2 = gNfitNvs->Buffer[1];
    break;

    case 23: // Get Address Range Scrub (Query ARS Status)
      //Condition chk -> addresses should be part of PMem address range
      ArsOutputData = (ARS_OUTPUT_DATA *)ArsU32Output;
      OutputPayloadSizeDw = 7; // 28 Bytes
      DEBUG ((DEBUG_INFO, "2LM: Issuing GetAddressRangeScrubCommand\n"));
      Status = GetAddressRangeScrubCommand (&DeviceReturnStatus, (UINT32*) ArsU32Output, OutputPayloadSizeDw);
      if (EFI_ERROR(Status)) {
         gNfitNvs->Data1 = 5; // Unknown reason
         gNfitNvs->Data2 = 0;
         break;
       }
       if (DeviceReturnStatus != MB_SUCCESS) {
         DEBUG ((DEBUG_INFO, "2LM: DeviceReturnStatus is %d\n", DeviceReturnStatus));
         if (DeviceReturnStatus == DataNotSet) {
           DEBUG ((DEBUG_INFO, "2LM: ARS Data Not Set\n"));
           gNfitNvs->Data1 = 0x020006; // status: 6  Function-Specific Error Code Ext Status 2  No ARS performed for current boot.
           gNfitNvs->Data2 = 0;
         }

         DEBUG ((DEBUG_INFO, "2LM: Error in FIS command \n"));
         gNfitNvs->Data1 = 3; //hardware error  if Start ARS FIS commands returns so
         gNfitNvs->Data2 = 0;
         break;
       }
       // Check if ARS is in progress
       //If Enable field is 1, Fill extended status with ARS in progress. Fill zero for rest of the fields
       if (ArsOutputData->Enable) {
         DEBUG ((DEBUG_INFO, "ARS is still in progress for RegionID 0x%x\n",ArsOutputData->RegionId));
         OutputPayloadSizeDw = 31; // 124 bytes for ARS
         ZeroMem ((VOID *)(UINTN)gNfitNvs->Buffer, (OutputPayloadSizeDw*4));
         gNfitNvs->Data1 = 0x10000; // Return Ex status:1  ARS in progress.
         gNfitNvs->Data2 = 0; // Length
         break;
       }
       // ARS is complete
       DEBUG ((DEBUG_INFO, "2LM: ARS is complete \n"));
       DEBUG ((DEBUG_INFO, "DpaStartAddr = 0x%lx\n", ArsOutputData->DpaStartAddr));
       DEBUG ((DEBUG_INFO, "DpaCurrAddr = 0x%lx\n", ArsOutputData->DpaCurrAddr));
       DEBUG ((DEBUG_INFO, "DpaEndAddr = 0x%lx\n", ArsOutputData->DpaEndAddr));

       // Issue long operation status cmd to get the Error status
       DEBUG ((DEBUG_INFO, "2LM: Issue long operation status cmd to get the details for ARS\n"));
       OutputPayloadSizeDw = 31; // 124 bytes for ARS
       UINT8 TempBuff[124]; //temp buff for long op status
       Status = GetLongOperationStatusCommand (&DeviceReturnStatus, (UINT32*)TempBuff, OutputPayloadSizeDw);
       if (EFI_ERROR(Status)) {
         gNfitNvs->Data1 = 5; //5  Error  Unknown Reason
         gNfitNvs->Data2 = 0;
         DEBUG ((DEBUG_INFO, "2LM: Error in get long operation status\n"));
         break;
       }
       DEBUG ((DEBUG_INFO, "2LM: Got the long operartion status for cmd opcode 0x%x\n", *(UINT16*)TempBuff));
       DEBUG ((DEBUG_INFO, "2LM: Estimated Time to Completion 0x%x\n", *(UINT32*)(TempBuff+4)));
       DEBUG ((DEBUG_INFO, "2LM: Output of long operation\n"));
       for (i = 0; i < 124; ++i)
       {
          DEBUG ((DEBUG_INFO, "output Index %x value %x\n", i, TempBuff[i]));
       }
       // check if long operation was ARS (opcode 5, Sub opcode 4)
       if ((TempBuff[0] == 5) && (TempBuff[1] == 4)) {
          DEBUG ((DEBUG_INFO, "Long operation was ARS\n"));
          // Status Code: The completed mailbox status code of the long operation.
          // Once the long operation is complete, the status code will be located here instead of the status register
          DeviceReturnStatus = TempBuff[8];

          if (DeviceReturnStatus != MB_SUCCESS) {
            DEBUG ((DEBUG_INFO, "2LM: Error in FIS command DeviceReturnStatus 0x%x\n", DeviceReturnStatus));
            gNfitNvs->Data1 = 3; //hardware error  if Start ARS FIS commands returns so
            gNfitNvs->Data2 = 0;
            break;
          }

          UINT8 ErrCnt = TempBuff[9];  //Byte 9
          if (TempBuff[10]) {
            DEBUG ((DEBUG_INFO, "ARS Ended early \n"));
          }
          DEBUG ((DEBUG_INFO, "ARS was done for RegionId 0x%x\n", TempBuff[11] & 0x1F));
          DEBUG ((DEBUG_INFO, "All region indicator bit is 0x%x\n", TempBuff[11] & 0x80));

          DEBUG ((DEBUG_INFO, "ErrCnt = 0x%x\n", ErrCnt));
          DEBUG ((DEBUG_INFO, "DpaStartAddr = 0x%lx\n", ArsOutputData->DpaStartAddr));
          DEBUG ((DEBUG_INFO, "DpaCurrAddr = 0x%lx\n", ArsOutputData->DpaCurrAddr));
          DEBUG ((DEBUG_INFO, "DpaEndAddr = 0x%lx\n", ArsOutputData->DpaEndAddr));

          ArsOutputData->DpaStartAddr = ArsOutputData->DpaStartAddr + PMemBase;
          ArsOutputData->DpaCurrAddr = ArsOutputData->DpaCurrAddr + PMemBase;
          ArsOutputData->DpaEndAddr = ArsOutputData->DpaEndAddr + PMemBase;

          DEBUG ((DEBUG_INFO, "DpaStartAddr = 0x%lx\n", ArsOutputData->DpaStartAddr));
          DEBUG ((DEBUG_INFO, "DpaCurrAddr = 0x%lx\n", ArsOutputData->DpaCurrAddr));
          DEBUG ((DEBUG_INFO, "DpaEndAddr = 0x%lx\n", ArsOutputData->DpaEndAddr));

          // Populating ARS status o/p data
          gNfitNvs->Buffer[0] = 44 + (ErrCnt*24) ; // Size of Output Buffer in bytes, including this field.   44 + Number of error records * 24
          *(UINT64*)(gNfitNvs->Buffer+1) = ArsOutputData->DpaStartAddr; //Start SPA 8 4 In bytes  DPA start address from FIS command
          *(UINT64*)(gNfitNvs->Buffer+3) = ArsOutputData->DpaCurrAddr - ArsOutputData->DpaStartAddr; //DPA Current address  DPA Start address from FIS command
          if (ArsOutputData->DpaCurrAddr != ArsOutputData->DpaEndAddr) {
            *(UINT64*)(gNfitNvs->Buffer+5) = ArsOutputData->DpaCurrAddr;
          } else {
            *(UINT64*)(gNfitNvs->Buffer+5) = 0;
          }
          *(UINT64*)(gNfitNvs->Buffer+7) = ArsOutputData->DpaEndAddr - ArsOutputData->DpaCurrAddr; //Restart ARS Length
          gNfitNvs->Buffer[9] = 0x2;  //Flags = 0, Type = 0x2
          gNfitNvs->Buffer[10] = ErrCnt;  //Num Errors found  from Long operation command
          //populating ARS Error Records
          gNfitNvs->Buffer[11] = 1;     //NFIT Handle
          gNfitNvs->Buffer[12] = 0;     //Reserved
          *(UINT64*)(gNfitNvs->Buffer+13) = *(UINT64*)(TempBuff+12); //DPA error address from Long operation command
          *(UINT64*)(gNfitNvs->Buffer+15) = 512; //bytes

          //Fill in return status
          // Ext Status: 0  ARS complete
          // 1  ARS in progress. Any returned ARS data shall be all zeros.
          // 2  No ARS performed for current boot. Any returned ARS data shall be all zeros.
          // 3  ARS Stopped Prematurely  This may occur when the implementation reaches the maximum number of errors that can be reported.
          // 4 ..0xFFFF Reserved. Any returned ARS Data shall be all zeros.
          if (TempBuff[10] == 0x1) { //Ended early
            gNfitNvs->Data1 = 0x30000; //status:00, Ext Status: 3  ARS Stopped Prematurely
            gNfitNvs->Data2 = 0;
          } else {
            gNfitNvs->Data1 = 0x0; //status:00, Ext Status:  0  ARS complete
            gNfitNvs->Data2 = 44;
          }
       } else { ////2  No ARS performed for current boot. Any returned ARS data shall be all zeros??
         gNfitNvs->Data1 = 5; //5  Error  Unknown Reason
         gNfitNvs->Data2 = 0;
       }
       gNfitNvs->Data1 = 0;
       gNfitNvs->Data2 = 44;
      break;

    case 24: // Clear Uncorrectable Error
      /***
       * There is no corresponding FIS command. Bios to write value 0 to the address range
       * specified by input. BIOS should return error if the input range doesn't fall within PMEM range.
       *
       * Status
       * 0  Success
       * 2  If the input range doesn't fall with in PMEM
       * If the input SPA is not 512byte aligned.
       * If the input SPA length is not in the units of 512bytes
       */
      DEBUG ((DEBUG_INFO, "2LM: Inside Clear Uncorrectable Errors\n"));
      // Check if the input range doesn't fall with in PMEM
      ArsAddr = *(UINT64*)gNfitNvs->Buffer; //[0];
      ArsLen  = *(UINT64*)(gNfitNvs->Buffer+2);//[2];
      DEBUG ((DEBUG_INFO, "ARSA = 0x%lx  ARSL = 0x%lx\n", ArsAddr,ArsLen));
      // Check if ARS range falls within PMem region
      if ((ArsAddr >= PMemBase) && ((ArsAddr+ArsLen) <= (PMemBase + PMemSize))) {
        DEBUG ((DEBUG_INFO, "2LM:  Clear Uncorrectable Error is within PMem range\n"));
        gNfitNvs->Data1 = 0;
      }
      else {
        gNfitNvs->Data1 = 2; //2  Invalid Input Parameters
      }

      break;
  }
  return EFI_SUCCESS;
}

/**
  Find the operation region in NVDIMM ACPI table by given Name and Size,
  and initialize it if the region is found.

  @param[in, out] Table          The NVDIMM item in ACPI table.
  @param[in]      Name           The name string to find in TPM table.
  @param[in]      Size           The size of the region to find.

  @return                        The allocated address for the found region.

**/
VOID *
AssignOpRegion (
  EFI_ACPI_DESCRIPTION_HEADER    *Table,
  UINT32                         Name,
  UINT16                         Size
  )
{
  EFI_STATUS                     Status;
  AML_OP_REGION_32_8             *OpRegion;
  EFI_PHYSICAL_ADDRESS           MemoryAddress;

  MemoryAddress = SIZE_4GB - 1;

  //
  // Patch some pointers for the ASL code before loading the SSDT.
  //
  for (OpRegion  = (AML_OP_REGION_32_8 *) (Table + 1);
       OpRegion <= (AML_OP_REGION_32_8 *) ((UINT8 *) Table + Table->Length);
       OpRegion  = (AML_OP_REGION_32_8 *) ((UINT8 *) OpRegion + 1)) {
    if ((OpRegion->OpRegionOp  == AML_EXT_REGION_OP) &&
        (OpRegion->NameString  == Name) &&
        (OpRegion->DWordPrefix == AML_DWORD_PREFIX) &&
        (OpRegion->BytePrefix  == AML_WORD_PREFIX)) {

      Status = gBS->AllocatePages(AllocateMaxAddress, EfiACPIMemoryNVS, EFI_SIZE_TO_PAGES (Size), &MemoryAddress);
      ASSERT_EFI_ERROR (Status);
      ZeroMem ((VOID *)(UINTN)MemoryAddress, Size);
      OpRegion->RegionOffset = (UINT32) (UINTN) MemoryAddress;
      OpRegion->RegionLen    = (UINT8) Size;
      break;
    }
  }

  return (VOID *) (UINTN) MemoryAddress;
}

/**
  The driver's entry point.

  It install callbacks for NVDIMM FIS commands

  @param[in] ImageHandle  The firmware allocated handle for the EFI image.
  @param[in] SystemTable  A pointer to the EFI System Table.

  @retval EFI_SUCCESS     The entry point is executed successfully.
  @retval Others          Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
InitializeNfitSmm (
  IN EFI_HANDLE                  ImageHandle,
  IN EFI_SYSTEM_TABLE            *SystemTable
  )
{
  EFI_STATUS                     Status;
  EFI_SMM_SW_DISPATCH2_PROTOCOL  *SwDispatch;
  EFI_SMM_SW_REGISTER_CONTEXT    SwContext;
  EFI_HANDLE                     SwHandle;
  EFI_ACPI_DESCRIPTION_HEADER    *Table;
  UINTN                          TableSize;
  EFI_ACPI_TABLE_PROTOCOL        *AcpiTable;
  UINTN                          TableKey;
  TWOLM_INFO_HOB                 *TwoLmInfoHob;

  DEBUG((DEBUG_INFO, "InitializeNfitSmm \n"));
  TwoLmInfoHob = (TWOLM_INFO_HOB *) GetFirstGuidHob (&gTwoLmInfoHobGuid);
  if (TwoLmInfoHob == NULL) {
    DEBUG ((DEBUG_INFO, "2LM: TwoLmInfoHob not found\n"));
    return EFI_UNSUPPORTED;
  }

  if (TwoLmInfoHob->TwoLmInfo.PMemSize == 0) {
    DEBUG ((DEBUG_INFO, "PMEM Disabled, skip NVDIMM ACPI table installation\n"));
    return EFI_SUCCESS;
  }
  DEBUG((DEBUG_INFO, "PMemModeSupported %d MemoryModeSupported %d \n", TwoLmInfoHob->TwoLmInfo.PMemModeSupported,TwoLmInfoHob->TwoLmInfo.MemoryModeSupported));
  SupportedModes |= (TwoLmInfoHob->TwoLmInfo.PMemModeSupported << 1) |
                    (TwoLmInfoHob->TwoLmInfo.MemoryModeSupported);
  DEBUG((DEBUG_INFO, "SupportedModes 0x%x \n", SupportedModes));

  PMemBase = TwoLmInfoHob->TwoLmInfo.PMemBase;
  PMemSize = LShiftU64(TwoLmInfoHob->TwoLmInfo.PMemSize, 20); // In bytes
  RegionIdPMem = TwoLmInfoHob->TwoLmInfo.RegionIdPMem;
  DEBUG((DEBUG_INFO, "PMemBase = 0x%lx \t PMemSize 0x%lx RegionIdPMem = %x\n", PMemBase, PMemSize, RegionIdPMem));

  Status = GetSectionFromFv (
             &gEfiCallerIdGuid,
             EFI_SECTION_RAW,
             0,
             (VOID **) &Table,
             &TableSize
             );
  ASSERT_EFI_ERROR (Status);
  gNfitNvs = AssignOpRegion (Table, SIGNATURE_32 ('N', 'V', 'D', 'M'), (UINT16) sizeof (NVDIMM_NVS));
  DEBUG((DEBUG_INFO, "gNfitNvs Address  %x\n", gNfitNvs));
  ASSERT (gNfitNvs != NULL);

  //
  // Get the Sw dispatch protocol and register SMI callback functions.
  //
  Status = gSmst->SmmLocateProtocol (&gEfiSmmSwDispatch2ProtocolGuid, NULL, (VOID**)&SwDispatch);
  ASSERT_EFI_ERROR (Status);
  SwContext.SwSmiInputValue = (UINTN) -1;
  Status = SwDispatch->Register (SwDispatch, FisCommandCallback, &SwContext, &SwHandle);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  gNfitNvs->FisSwSmiNumber = (UINT8) SwContext.SwSmiInputValue;
  DEBUG((DEBUG_INFO, "Nfit SMM SW SMI number = %x\n", gNfitNvs->FisSwSmiNumber));

  //
  // Publish the NVDIMM ACPI table. Table is re-checksumed.
  //
  Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, (VOID **) &AcpiTable);
  ASSERT_EFI_ERROR (Status);

  TableKey = 0;
  Status = AcpiTable->InstallAcpiTable (
                        AcpiTable,
                        Table,
                        TableSize,
                        &TableKey
                        );
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}
