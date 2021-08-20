/** @file

  Source file for FMHC Mailbox Interface implementation.

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
#include <Library/FmssMbLib.h>
#include <Register/TwoLmRegs.h>
#include <Library/CpuRegbarAccessLib.h>
#include <Uefi/UefiBaseType.h>
#include <Library/TimerLib.h>
#include <CpuSbInfo.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
/*
 * @todo:
 * 1. Check the read/write access control policy register values to make sure
 * that BIOS has the required SAI access.
 * 2. Check support for 64bit CPU RegBar access else need to break it in 32bit accesses
 */

/**
This function reads VDM register value from 2LM device.

@param[in]      RegOffset         FMHC Mailbox Register offset.
@param[out]     Data              VDM read data.

@retval EFI_SUCCESS            Successful completion of RegReadVdm.
**/
EFI_STATUS
EFIAPI
RegReadVdm (
  IN  UINT16      RegOffset,
  OUT UINT32      *Data
)
{
  FRPA_FMHC_MAILBOX_STRUCT Frpa;
  FHD_FMHC_MAILBOX_STRUCT  Fhd;
  FRQC_FMHC_MAILBOX_STRUCT Frqc;
  FDD_FMHC_MAILBOX_STRUCT  Fdd;
  FRSP_FMHC_MAILBOX_STRUCT Frsp;
  UINT32                   WaitTime;

  DEBUG ((DEBUG_INFO, "2LM: Reg Read VDM ... START\n"));

  // First check if Far memory device is busy or available
  Frqc.Data = CpuRegbarRead32 (CPU_SB_PID_FMHC, R_SA_FMHC_BIOS_MAIL_BOX_FRQC);
  if (Frqc.Bits.RunBusy) {
    DEBUG((DEBUG_INFO, "Far Memory Device is busy...trying again \n"));
    // Try again after 100us in a loop up to 1ms (timeout value)
    for (WaitTime = 0; WaitTime < MB_TIMEOUT; WaitTime += MB_TIMEINTERVAL) {
      MicroSecondDelay (MB_TIMEINTERVAL);
      Frqc.Data = CpuRegbarRead32 (CPU_SB_PID_FMHC, R_SA_FMHC_BIOS_MAIL_BOX_FRQC);
      if (!Frqc.Bits.RunBusy) { // Device is available
        break;
      }
      if (WaitTime >= MB_TIMEOUT){
        DEBUG ((DEBUG_INFO, "RegReadVdm timeout error...\n"));
        return EFI_TIMEOUT;
      }
    }
  }

  // FRPA config
  // 1. Write to FRPA [63:0] register with content as per below.
  //  a. Bit [43:40] = DW BE[03:00] (byte enable)
  //  b. Bit [39:32] = Vendor Message[7:0]
  //  c. All others = 0's
  Frpa.Data = 0x00200FD4001F8086; //default value
  Frpa.Bits.FRP_DW_BE = 0xF; //4 bytes--confirm
  Frpa.Bits.FRP_VendorMessage = 0xD4;  //1101_0100b for reg read
  CpuRegbarWrite64 (CPU_SB_PID_FMHC, R_SA_FMHC_BIOS_MAIL_BOX_FRPA, Frpa.Data);
  DEBUG ((DEBUG_INFO, "Fmhc mailbox FRPA = 0x%lX\n",Frpa.Data));

  // FHD config 64bit
  // 2. Write to FHD with register offset.
  //  a. FHD[11:02] = Offset[11:02]
  //  b. All others = 0's
  Fhd.Data = 0x0; //Initialize all 64bits to zero
  Fhd.Bits.RegOffsetLow = RegOffset & 0xFC; // DW aligned Reg offset of FM CSR VDM Reg (like DID, VID etc.)
  Fhd.Bits.RegOffsetHigh = (RegOffset & 0x7F00) >> 8;
  CpuRegbarWrite64 (CPU_SB_PID_FMHC, R_SA_FMHC_BIOS_MAIL_BOX_FHD, Fhd.Data);
  DEBUG ((DEBUG_INFO, "Fmhc mailbox FHD = 0x%lX\n",Fhd.Data));

  // FRQC config 32bit
  //  3. Write to FRQC register with content = 8000 0204h
  //    a. Bit[31] RUN_BSY = 1b
  //    b. Bit[03:00] Command = 4h (register read request VDM) 04h = register read request VDM, 05h = register write request VDM
  //    c. All others = 0's
  //or
  // Frqc.Bits.Command = 0x0204;
  // Frqc.Bits.Rsvd = 0x0;
  // Frqc.Bits.RunBusy = 0x1;
  Frqc.Data = 0x80000004; //04h = register read request VDM
  CpuRegbarWrite32 (CPU_SB_PID_FMHC, R_SA_FMHC_BIOS_MAIL_BOX_FRQC, Frqc.Data);
  DEBUG ((DEBUG_INFO, "Fmhc mailbox FRQC = 0x%X\n",Frqc.Data));

  // Poll register FRQC.RUN_BSY='0'
  Frqc.Data = CpuRegbarRead32 (CPU_SB_PID_FMHC, R_SA_FMHC_BIOS_MAIL_BOX_FRQC);
  if (Frqc.Bits.RunBusy) {
    DEBUG((DEBUG_INFO, "Far Memory Device is busy...trying again \n"));
    // Try again after 100us in a loop up to 1ms (timeout value)
    for (WaitTime = 0; WaitTime < MB_TIMEOUT; WaitTime += MB_TIMEINTERVAL) {
      MicroSecondDelay (MB_TIMEINTERVAL);
      Frqc.Data = CpuRegbarRead32 (CPU_SB_PID_FMHC, R_SA_FMHC_BIOS_MAIL_BOX_FRQC);
      if (!Frqc.Bits.RunBusy) { // Device is available
        break;
      }
      if (WaitTime >= MB_TIMEOUT){
        DEBUG ((DEBUG_INFO, "RegReadVdm timeout error...\n"));
        return EFI_TIMEOUT;
      }
    }
  }

  // Read the transaction completion status from the FRSP register
  // In the event of error, BIOS may read response status from FRSP.
  Frsp.Data = CpuRegbarRead32 (CPU_SB_PID_FMHC, R_SA_FMHC_BIOS_MAIL_BOX_FRSP);
  if (Frsp.Bits.FmTransactionStatus != Successful) {
    DEBUG((DEBUG_INFO, "Device error\n"));
    return EFI_DEVICE_ERROR;
  }

  // BIOS to read a DWord of Device's FM CSR VDM register data from the FDD register
  // for register response with data VDM (for register read)
  Fdd.Data = CpuRegbarRead32 (CPU_SB_PID_FMHC, R_SA_FMHC_BIOS_MAIL_BOX_FDD);
  *Data = Fdd.Data; //return the reg read data

  DEBUG((DEBUG_INFO, "Success Data = %x\n", *Data));
  return EFI_SUCCESS;

}



/**
This function writes to VDM register in 2LM device.

@param[in]      RegOffset         FMHC Mailbox Register offset.
@param[in]      Data              VDM write data.

@retval EFI_SUCCESS            Successful completion of RegWriteVdm.
**/
EFI_STATUS
EFIAPI
RegWriteVdm (
  IN UINT16     RegOffset,
  IN UINT32     Data
)
{
  FRPA_FMHC_MAILBOX_STRUCT Frpa;
  FHD_FMHC_MAILBOX_STRUCT  Fhd;
  FRQC_FMHC_MAILBOX_STRUCT Frqc;
  FRSP_FMHC_MAILBOX_STRUCT Frsp;
  UINT32                   WaitTime;

  DEBUG ((DEBUG_INFO, "2LM: Reg Write VDM ... START\n"));
  // First check if Far memory device is busy or available
  Frqc.Data = CpuRegbarRead32 (CPU_SB_PID_FMHC, R_SA_FMHC_BIOS_MAIL_BOX_FRQC);
  if (Frqc.Bits.RunBusy) {
    DEBUG((DEBUG_INFO, "Far Memory Device is busy...trying again \n"));
    // Try again after 100us in a loop up to 1ms (timeout value)
    for (WaitTime = 0; WaitTime < MB_TIMEOUT; WaitTime += MB_TIMEINTERVAL) {
      MicroSecondDelay (MB_TIMEINTERVAL);
      Frqc.Data = CpuRegbarRead32 (CPU_SB_PID_FMHC, R_SA_FMHC_BIOS_MAIL_BOX_FRQC);
      if (!Frqc.Bits.RunBusy) { // Device is available
        break;
      }
      if (WaitTime >= MB_TIMEOUT){
        DEBUG ((DEBUG_INFO, "RegReadVdm timeout error...\n"));
        return EFI_TIMEOUT;
      }
    }
  }

  // FRPA config
  // 1. Write to FRPA [63:0] register with content as per below.
  //  a. Bit [43:40] = DW BE[03:00] (byte enable)
  //  b. Bit [39:32] = Vendor Message[7:0]
  //  c. All others = 0's
  Frpa.Data = 0x00200FD4001F8086; //default value
  Frpa.Bits.FRP_DW_BE = 0xF; //4 bytes--confirm
  Frpa.Bits.FRP_VendorMessage = 0xD3;  //1101_0011b for reg write
  Frpa.Bits.FRP_VDMRW = 1;
  CpuRegbarWrite64 (CPU_SB_PID_FMHC, R_SA_FMHC_BIOS_MAIL_BOX_FRPA, Frpa.Data);
  DEBUG ((DEBUG_INFO, "Fmhc mailbox FRPA = 0x%lX\n",Frpa.Data));

  // FHD config 64bit
  // 2. Write to FHD with register offset and Data.
  //    a. FHD[11:02] = Offset[11:02]
  //    b. All others = 0's
  Fhd.Data = 0x0; //Initialize all 64bits to zero
  Fhd.Bits.RegOffsetLow = RegOffset & 0xFC; // DW aligned Reg offset of FM CSR VDM Reg (like DID, VID etc.)
  Fhd.Bits.RegOffsetHigh = (RegOffset & 0x7F00) >> 8;
  Fhd.Bits.RegisterWritePayload = Data; //FHDIDX[63:32] = register write payload[31:00]
  CpuRegbarWrite64 (CPU_SB_PID_FMHC, R_SA_FMHC_BIOS_MAIL_BOX_FHD, Fhd.Data);
  DEBUG ((DEBUG_INFO, "Fmhc mailbox FHD = 0x%lX\n",Fhd.Data));

  // FRQC config 32bit
  // 3. Write to FRQC register with content = 8000 0204h
  //   a. Bit[31] RUN_BSY = 1b
  //   b. Bit[03:00] Command = 4h (register read request VDM) 04h = register read request VDM, 05h = register write request VDM
  //   c. All others = 0's
  //or
  // Frqc.Bits.Command = 0x0204;
  // Frqc.Bits.Rsvd = 0x0;
  // Frqc.Bits.RunBusy = 0x1;
  Frqc.Data = 0x80000005; //05h = register write request VDM
  CpuRegbarWrite32 (CPU_SB_PID_FMHC, R_SA_FMHC_BIOS_MAIL_BOX_FRQC, Frqc.Data);
  DEBUG ((DEBUG_INFO, "Fmhc mailbox Frqc = 0x%X\n",Frqc.Data));


  // Poll register FRQC.RUN_BSY='0'
  Frqc.Data = CpuRegbarRead32 (CPU_SB_PID_FMHC, R_SA_FMHC_BIOS_MAIL_BOX_FRQC);
  if (Frqc.Bits.RunBusy) {
    DEBUG((DEBUG_INFO, "Far Memory Device is busy...trying again \n"));
    // Try again after 100us in a loop up to 1ms (timeout value)
    for (WaitTime = 0; WaitTime < MB_TIMEOUT; WaitTime += MB_TIMEINTERVAL) {
      MicroSecondDelay (MB_TIMEINTERVAL);
      Frqc.Data = CpuRegbarRead32 (CPU_SB_PID_FMHC, R_SA_FMHC_BIOS_MAIL_BOX_FRQC);
      if (!Frqc.Bits.RunBusy) { // Device is available
        break;
      }
      if (WaitTime >= MB_TIMEOUT){
        DEBUG ((DEBUG_INFO, "RegReadVdm MB_TIMEOUT error...\n"));
        return EFI_TIMEOUT;
      }
    }
  }

  // Read the transaction completion status from the FRSP register
  // In the event of error, BIOS may read response status from FRSP.
  Frsp.Data = CpuRegbarRead32 (CPU_SB_PID_FMHC, R_SA_FMHC_BIOS_MAIL_BOX_FRSP);
  if (Frsp.Bits.FmTransactionStatus != Successful) {
    DEBUG((DEBUG_INFO, "Device error\n"));
    return EFI_DEVICE_ERROR;
  }
  DEBUG((DEBUG_INFO, "Success\n"));
  return EFI_SUCCESS;

}


/**
This function issues Mailbox command to 2LM device.

@param[in]      MbCmd        Structure with all the required parameters.

@retval EFI_SUCCESS            Successful completion of Mailbox communication.
**/
EFI_STATUS
EFIAPI
IssueMailboxCommand (
  IN MAILBOX_CMD    MbCmd
)
{
  MBNCE0_FMSS_MAILBOX_STRUCT  Mbnce0;
  MBNCE1_FMSS_MAILBOX_STRUCT  Mbnce1;
  MBSTS0_FMSS_MAILBOX_STRUCT  Mbsts0;
  UINT32                      Data;
  UINT32                      WaitTime;
  UINT32                      i;
  EFI_STATUS                  Status;

  DEBUG ((DEBUG_INFO, "2LM: Issuing Mailbox command to the Far memory device...START\n"));
  // Check if nonce is set and if so first send the nonce value
  // Non-zero nonce value indicate that the nonce value is set
  if (MbCmd.BiosNonceValue) {
    // Write the lower 32bit value
    Mbnce0.Bits.Lower = (UINT32)MbCmd.BiosNonceValue;
    Status = RegWriteVdm(R_SA_FMSS_VDM_MAIL_BOX_MBNCE0,Mbnce0.Data);
    // Write the upper 32bit value
    Mbnce1.Bits.Upper =  (UINT32)(RShiftU64 (MbCmd.BiosNonceValue, 32));
    Status = RegWriteVdm(R_SA_FMSS_VDM_MAIL_BOX_MBNCE1,Mbnce1.Data);
  }


  // Check if command require inbox payload (opcode specific 512 byte input buffer to 2LM Module)
  // Check if input size is non-zero and input ptr is not Null for valid input payload
  if (MbCmd.InputPayloadSizeDw && MbCmd.InputPayloadPtr) {
    //write to Mailbox Inbox registers DW0/1/...127, DW at a time
    for (i=0; i < MbCmd.InputPayloadSizeDw; ++i) {
      Status = RegWriteVdm((UINT16)(R_SA_FMSS_VDM_MAIL_BOX_INBOXDW0+ i*4), *(UINT32 *)(MbCmd.InputPayloadPtr + i));
      if(Status != EFI_SUCCESS) {
        return Status;
      }
    }
  }

  // Issue command
  // Write to reg MBCMD0 using Reg Write VDM
  Status = RegWriteVdm(R_SA_FMSS_VDM_MAIL_BOX_MBCMD0,MbCmd.MbCmd0Reg.Data);
  // Write to reg MBCMD1 using Reg Write VDM
  //Status = RegWriteVdm(R_SA_FMSS_VDM_MAIL_BOX_MBCMD1,Mbcmd1.Data);
  Status = RegWriteVdm(R_SA_FMSS_VDM_MAIL_BOX_MBCMD1, MbCmd.MbCmd1Reg.Data);

  // Phase2
  // Read back command reg to check DB bit
  // Read Lower Command VDM and Upper Command VDM
/* @todo enable if its a requirement from hw to read lower cmd reg before reading upper cmd reg.
  Data = 0; // Reset Data value to 0
  Status = RegReadVdm(R_SA_FMSS_VDM_MAIL_BOX_MBCMD0, &Data);
  if (Status != EFI_SUCCESS) {
    return Status;
  }
  Mbcmd0.Data = Data;
*/

  Data = 0; // Reset Data value to 0
  Status = RegReadVdm(R_SA_FMSS_VDM_MAIL_BOX_MBCMD1, &Data);
  if (Status != EFI_SUCCESS) {
    return Status;
  }
  MbCmd.MbCmd1Reg.Data = Data;
  // Check if DB bit is clear
  if (MbCmd.MbCmd1Reg.Bits.DB){
    DEBUG ((DEBUG_INFO, "Command issue is not complete. Trying again ..\n"));
    // Try again after 100us in a loop up to 1ms (timeout value)
    for (WaitTime = 0; WaitTime < MB_TIMEOUT; WaitTime += MB_TIMEINTERVAL) {
      MicroSecondDelay (MB_TIMEINTERVAL);
      Data = 0; // Reset Data value to 0
      Status = RegReadVdm(R_SA_FMSS_VDM_MAIL_BOX_MBCMD1, &Data);
      if (Status != EFI_SUCCESS) {
        return Status;
      }
      MbCmd.MbCmd1Reg.Data = Data;
      if (!MbCmd.MbCmd1Reg.Bits.DB) { // Command issue is complete
        break;
      }
      if (WaitTime >= MB_TIMEOUT){
        DEBUG ((DEBUG_INFO, "Command issue completion timeout error...\n"));
        return EFI_TIMEOUT;
      }
    }
  }

  Data = 0; // Reset Data value to 0
  // Now read the status register
  Status = RegReadVdm(R_SA_FMSS_VDM_MAIL_BOX_MBSTS0, &Data);
  Mbsts0.Data = Data;
  // Check if MB Comp bit is set
  if (!Mbsts0.Bits.MbComp){
    DEBUG ((DEBUG_INFO, "Command processing is not complete. Trying again ..\n"));
    // Try again after 100us in a loop up to 1ms (timeout value)
    for (WaitTime = 0; WaitTime < MB_TIMEOUT; WaitTime += MB_TIMEINTERVAL) {
      MicroSecondDelay (MB_TIMEINTERVAL);
      Data = 0; // Reset Data value to 0
      Status = RegReadVdm(R_SA_FMSS_VDM_MAIL_BOX_MBSTS0, &Data);
      if (Status != EFI_SUCCESS) {
        return Status;
      }
      Mbsts0.Data = Data;
      if (Mbsts0.Bits.MbComp) { // Command processing is complete
        break;
      }
    }
    if (WaitTime >= MB_TIMEOUT) {
      DEBUG ((DEBUG_INFO, "Command processing completion timeout error... Timeout value = %d\n", MB_TIMEOUT));
      ASSERT_EFI_ERROR (EFI_TIMEOUT);
      return EFI_TIMEOUT;
    }
  }

  // Now store the MB return status code
  *(MbCmd.DeviceReturnStatus) = (UINT8)Mbsts0.Bits.FwMbStatusCode;

  // Check if command sends outbox payload (opcode specific upto 512 byte output payload)
  // Check if output size is non-zero and output ptr is not Null for valid output payload
  if (MbCmd.OutputPayloadSizeDw && MbCmd.OutputPayloadPtr) {
    //read from Mailbox Outbox registers DW0/1/...127, DW at a time
    for (i=0; i < MbCmd.OutputPayloadSizeDw; ++i) {
      Status = RegReadVdm((UINT16)(R_SA_FMSS_VDM_MAIL_BOX_OUTBOXDW0+ i*4), (MbCmd.OutputPayloadPtr + i));
      if(Status != EFI_SUCCESS) {
        return Status;
      }
    }
  }

  return EFI_SUCCESS;

}
