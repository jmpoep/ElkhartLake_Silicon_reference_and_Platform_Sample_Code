/** @file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2017 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#include <PiDxe.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseEcFlashLib.h>
#include <Library/DebugLib.h>

////
//
// InByte()
//
// Description: Read a byte from an I/O Port
//
////
#ifdef _MSC_VER
static
UINT32
InByte (
  UINT16 Port
  )
{
  return _inp (Port);
}
#else
#ifdef __GNUC__
static
inline
UINT32
InByte (
  UINT16 Port
  )
{
  UINT8   Data;
  __asm__ __volatile__ ( "inb %1, %0;" : "=a"(Data) : "d"(Port) );
  return (UINT32) Data;
}
#else
#error Unsupported Compiler
#endif
#endif

////
//
// OutByte()
//
// Description: Write a byte to an I/O Port
//
////
#ifdef _MSC_VER
static
VOID
OutByte (
  UINT16 Port,
  UINT32 Value
  )
{
  _outp (Port, Value);
}
#else
#ifdef __GNUC__
static
inline
VOID
OutByte (
  UINT16 Port,
  UINT32 Value
  )
{
  __asm__ __volatile__ ( "outb %%al, %1;" : : "a"(Value), "d"(Port) );
}
#else
#error Unsupported Compiler
#endif
#endif

BOOLEAN
IsEcVersionIdentical (
  UINT8* pEcBin
  )
{
  UINT32   ch1, ch2, ch3, ch4;


  SendEcCommand(READECREVISION);
  ch1 = ReceiveEcData();
  ch2 = ReceiveEcData();

  DEBUG ((DEBUG_INFO, "\nEC Current Version %X.%02X\n", ch1, ch2));
  ch3 = (*(pEcBin+IMAGE_SIGNATURE + 4));  // Ec Major Ver
  ch4 = (*(pEcBin+IMAGE_SIGNATURE + 5));  // Ec Minor Ver
  DEBUG ((DEBUG_INFO, "\nUpdate to ver %X.%02X\n", ch3, ch4));
  // Disallow flasing EC with the same version
  if ((ch1 == ch3) && (ch2 == ch4)) {
    DEBUG ((DEBUG_INFO, "Same firmware version found!\n"));
    return TRUE;
  }

  return FALSE;
}

EFI_STATUS
EcFlash (
  UINT8* pFcntrlBin, UINT32 FcntrlBinSize, UINT8* pEcBin, UINT32 EcBinSize
  )
{
  UINT32  ch, csum;
  UINT32  i, j;
  BOOLEAN f = FALSE;
  BOOLEAN FlashUpdateComplete;  //FcntrlBytes,
  VOID *pBuffer = NULL;
  UINT64 fSize;
  UINT32 Status;

  fSize = FcntrlBinSize;
  FcntrlLen = fSize;
  FcntrlLenLow = (fSize & 0xFF);
  FcntrlLenHigh = ((fSize & 0xFF00) >> 8);

  // Display the current version
  SendEcCommand(READECREVISION);

  // Disallow flashing EC with the same version
  if (IsEcVersionIdentical(pEcBin)) {
    DEBUG ((DEBUG_ERROR, "Skip EC update - same firmware version found!\n"));
    return EFI_UNSUPPORTED;
  }

  //
  //  Send the "NMI Disable" command to the Ec
  //
  SendEcCommand(NMIDISABLE);
  gBS->Stall (1000); // 1msec

  //
  // Check if NMI still active
  //
  if (NmiActive()) {
    DEBUG ((DEBUG_ERROR, "\nNMI Detected! Abort flash update."));
    return EFI_SUCCESS;
  }

  //
  // Send the "Flash Loader" command to the Ec
  //
  DEBUG ((DEBUG_INFO, "\nCmd FLASHLOADER"));
  SendEcCommand(FLASHLOADER);

  //
  // Send the size of the flash control file FCNTRL.BIN to the Ec; low byte followed by high byte.
  //
  DEBUG ((DEBUG_INFO, "\nFcntrlLenLow %x",FcntrlLenLow));
  SendEcData(FcntrlLenLow);

  DEBUG ((DEBUG_INFO, "\nFcntrlLenHigh %x",FcntrlLenHigh));
  SendEcData(FcntrlLenHigh);

  //
  // Send the flash control file to the Ec.
  //
  DEBUG ((DEBUG_INFO, "\nSend flash control code"));
  gBS->Stall (1000);         // ???
  csum = 0;                  // Clear checksum byte
  pBuffer = pFcntrlBin;

  for (i = 0; i < FcntrlLen; i++) {
    //ch = (CHAR16)getc(FcHandle);
    ch = (UINT32)(*((UINT8 *)pBuffer + i));
    //Print(L"%x", ch);
    csum += ch;
    ch = ch & 0xFF;
    SendEcData(ch);
  };

  csum = csum & 0xFF;

  DEBUG ((DEBUG_INFO, "\nFCNTRL chksm is %X", csum));
  ch = ReceiveEcData();

  ch = ch & 0xFF;
  DEBUG ((DEBUG_INFO, "\nEc computed chksm is %X", ch));

  if (ch != csum) {
    DEBUG ((DEBUG_ERROR, "\nErr FCNTRL transfer failed SKIP!!!"));
    return EFI_SUCCESS;   // Check and return error cases.
  }
  gBS->Stall (100000);    // 100ms

  DEBUG ((DEBUG_INFO, "\nInit Flash Erase Code"));
  SendEcCommand(INITERASE);
  ch = ReceiveEcData();
  if (ch != 0) {
    DEBUG ((DEBUG_ERROR, "\nInit Flash Erase Code FAILED!!! %X", ch));
    return EFI_SUCCESS;
  }

  DEBUG ((DEBUG_INFO, "\nErase flash blk 0 (64K) [00000-0FFFF]..."));
  gBS->Stall (100000);    // 100ms

  EraseFlashBlock(0);
  gBS->Stall (500000);    // 500ms

  DEBUG ((DEBUG_INFO, "\nErase flash blk 1 (64K) [10000-1FFFF]..."));

  EraseFlashBlock(1);
  gBS->Stall (500000);    // 500ms

  //
  // Load programming and verify code into RAM and check the result
  //
  DEBUG ((DEBUG_INFO, "\nSend Cmd INITPROGCODE - "));
  SendEcCommand(INITPROGCODE);
  Status = ReceiveEcData();
  if (!(Status & 0xFF)) {
    DEBUG ((DEBUG_INFO, "Pass"));
  } else {
    DEBUG ((DEBUG_INFO, "FAIL!!!"));
    return EFI_DEVICE_ERROR;
  }

  // First program untrusted flash segment. Read the size of the Ec segment
  // stored in the image and compute the number of flash blocks to be written.
  DEBUG ((DEBUG_INFO, "Calculating EC Bin size\n"));
  gBS->Stall (100000);    // 100ms
  ImageLen = (*((UINT8*)(pEcBin+ECSEGSIZE_OFFSET+2)) << 8) + *((UINT8*)(pEcBin+ECSEGSIZE_OFFSET+3));
  DEBUG ((DEBUG_INFO, "Ec bin size: 0x%x\n", ImageLen));
  ImageLen = ImageLen/FBLOCK_SIZE + 2;
  DEBUG ((DEBUG_INFO, "Blks of Ec bin file: 0x%x\n", ImageLen));

  FlashBlock = 0;
  //
  // Read 128 byte blocks from the input file and program the Ec segment
  //
  FlashUpdateComplete = FALSE;

  pBuffer = pEcBin + EC_SEGMENT;
  FecSize = EcBinSize;

  i = 0;

  while((FlashUpdateComplete == FALSE)&&(FlashBlock < ImageLen )) {
    if((i % 128) == 0) {
      f = TRUE;
    }
    FlashBufPtr = FlashBuf;      // Point to buffer start.

    for (j = 0; j < 128; j++)    // Prepad unused buffer locations
      *FlashBufPtr++ = 0xFF;     // with blank byte.

    FlashBufPtr = FlashBuf;      // Point to buffer start.

    while (((i % 128) != 0) || f) { //(i = 0; i < 128; i++)    // Fill buffer from file
      f = FALSE;
      // until EOF is reached
      if(i < FecSize) {
        *FlashBufPtr++ = (UINT32)(*((UINT8 *)pBuffer + i));//(CHAR16)getc(InHandle);
        i++;
      } else {
        FlashUpdateComplete = TRUE;
        break;
      }
    }//for

    FlashBufPtr = FlashBuf;        // Point to buffer starting address.
    WriteFlashBlock(FlashBufPtr);  // Program buffer into flash.
    gBS->Stall (10000);            // 10ms
    FlashBlock++;                  // Repeat for all blocks.
  }//while

  DEBUG ((DEBUG_INFO, "\nFlash programming complete!"));

  return EFI_SUCCESS;   //exit(0);
}

VOID EcReset (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "\nSend Ec Reset Cmd!"));
  SendEcCommand(RESETEC);
  gBS->Stall (2000000); // 2sec
  DEBUG ((DEBUG_INFO, "\nPending Reset after 2Sec Ec Reset! "));
  return;
}

////
//
// ComputeBuffChksum()
//
// Description: Computes the byte checksum of a binary buffer
//
////
UINT32 ComputeBuffChksum(UINT32 *BufPtr, UINT32 BufSize)
{
  UINT32 i;
  UINT32 sum = 0;

  for (i = 0; i < BufSize; i++)
    sum += *BufPtr++;

  return (0 - sum);
}

////
//
// WaitInputBufferEmpty()
//
// Description: Waits forever for IBF flag to clear.
//
////
void   WaitInputBufferEmpty(void) {
  UINT32 Status;
  UINTN Count;

  Count = 0;
  Status = 0;

  DEBUG ((DEBUG_INFO, "\nWaitInputBufferEmpty"));

  Status = InByte (ECSTATUSPORT);
  while (((Status & EC_S_IBF) != 0)) { // && (Count < EC_TIME_OUT)) {
    //gBS->Stall (EC_STALL_TIME_OUT);
    Status = InByte (ECSTATUSPORT);
    Count++;
  }
  DEBUG ((DEBUG_INFO, "- Exit; Counter=0x%x", Count));
}

////
//
// WaitOutputBufferFull()
//
//  Description: Waits forever for OBF flag to set.
//
////
void   WaitOutputBufferFull(void)
{
  UINT32 Status;
  UINTN Count;

  Count = 0;
  Status = 0;
  DEBUG ((DEBUG_INFO, "\nWaitOutputBufferFull"));
  Status = InByte (ECSTATUSPORT);
  while (((Status & EC_S_OBF) == 0)){ // && (Count < EC_TIME_OUT)) {
    //gBS->Stall (EC_STALL_TIME_OUT);
    Status = InByte (ECSTATUSPORT);
    Count++;
  }
  DEBUG ((DEBUG_ERROR, "-Exit; Counter=0x%x",Count));
}

////
//
// SendEcCommand()
//
//  Description: Send a command to the Ec
//
////
void SendEcCommand(UINT32 CmdNum) {
  DEBUG ((DEBUG_INFO, "\nSend Ec Cmd %x", CmdNum));
  WaitInputBufferEmpty();
  OutByte (ECCOMMANDPORT, CmdNum);
}

////
//
// SendEcData()
//
//  Description: Send a Data to the Ec
//
////
void  SendEcData(UINT32 CmdNum)
{
  DEBUG ((DEBUG_INFO, "\nSend Ec Data %x",CmdNum));
  WaitInputBufferEmpty();
  OutByte (ECDATAPORT, CmdNum);
}

////
//
// ReceiveEcData()
//
//  Description: Get the data returned by the Ec
//
////
UINT32 ReceiveEcData (
  VOID
  )
{
  UINT32 Data;
  WaitOutputBufferFull();
  Data = InByte (ECDATAPORT);
  DEBUG ((DEBUG_INFO, "\nReceive Ec Data 0x%x", Data));
  return (Data & 0xFF);
}

////
//
// ReadEcRegister
//
//  Description: Returns the Ec register content
//
////
VOID
ReadEcRegister(
    IN  UINT8  Reg,
    OUT UINT8  *RetValue
)
{

  SendEcCommand((UINT32) READECMEM);
  SendEcData(Reg);
  *RetValue = (UINT8) ReceiveEcData ();

}

////
//
// NmiActive()
//
//  Description: Returns true if NMI is active.
//
////
UINT32 NmiActive(void)
{
  SendEcCommand(GETSWITCHSTATUS);
  return (ReceiveEcData() & BIT2);
}

////
//
// EraseFlashBlock()
//
////
UINT32 EraseFlashBlock(UINT32 BlkNum)
{
  UINT32 Status;

  DEBUG ((DEBUG_INFO, "\nErasing Ec Blk %x - ", BlkNum));
  SendEcCommand(SETERASEBLKNUM);

  SendEcData(BlkNum);

  SendEcCommand(ERASEFLASHBLK);

  Status = ReceiveEcData();
  if (Status & 0xFF) {
    DEBUG ((DEBUG_INFO, "Fail"));
    return EFI_SUCCESS;
  } else {
    DEBUG ((DEBUG_INFO, "Pass"));
  }

  return EFI_SUCCESS;

}//EraseFlashBlock

////
//
// WriteFlashBlock()
//
//  Description:   Writes a 128 byte block of data to the flash.
//  Input:      FBufPtr -> Data buffer to flash
//
////
UINT32 WriteFlashBlock(UINT32 *FBufPtr)
{
  UINT32 i;
  UINT32 ch, csum = 0;
  UINT32 Data;

  DEBUG ((DEBUG_INFO, "\nWriting Ec Flash Block"));
  SendEcCommand(LOADFLASHBLK);

  DEBUG ((DEBUG_INFO, "\n"));
  for (i = 0; i < FBLOCK_SIZE; i++) {
    ch = *FBufPtr++;
    csum += ch;
    ch = ch & 0xFF;
    DEBUG ((DEBUG_INFO, "%X", ch));
    SendEcData(ch);
  }
  DEBUG ((DEBUG_INFO, "\n"));
  csum = csum & 0xFF;
  Data = ReceiveEcData() & 0xFF;
  if (Data != csum) {
    DEBUG ((DEBUG_INFO, "\nChecksum Calculated/Received is = %X / %X", csum, Data));
    return EFI_SUCCESS;
  }

  FlashBufPtr = FlashBuf;             // Point to buffer start.
  DEBUG ((DEBUG_INFO, "\nSet Flash Addr"));
  SendEcCommand(SETFLASHWRITEADDR);

  FBlkStartAddr = FBLOCK_SIZE * FlashBlock;

  SendEcData((FBlkStartAddr & 0xFF));
  SendEcData(((FBlkStartAddr >> 8 ) & 0xFF));
  SendEcData(((FBlkStartAddr >> 16 ) & 0xFF));

  DEBUG ((DEBUG_INFO, "\nProgram Flash"));
  SendEcCommand(PROGRAMFLASHBLK);

  Data = ReceiveEcData();
  if (Data) {
    DEBUG ((DEBUG_INFO, " - FAIL"));
    return EFI_SUCCESS;
  } else {
    DEBUG ((DEBUG_INFO, " - PASS"));
    return EFI_SUCCESS;
  }
}//WriteFlashBlock

////
//
// IsBlankBlock()
//
//  Description:   Returns TRUE if a 128 byte block of data is all FFs
//  Input:      FBufPtr -> Data buffer to check
//
//
////
CHAR16 IsBlankBlock(CHAR16 *FBPtr)
{
  CHAR16 i, ch;
  CHAR16 *BPtr;

  BPtr = FBPtr;

  for (i = 0; i < FBLOCK_SIZE; i++) {
    ch = *BPtr++;
    if (ch != 0xFF)
      return (0x0);
  }
  return ((!0x0));  // RETURN TRUE;
}
