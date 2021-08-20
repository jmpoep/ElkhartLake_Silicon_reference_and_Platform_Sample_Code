/** @file
  Install Base and Size Info Ppi for Firmware Volume Recovery.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2016 Intel Corporation.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be 
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:
**/


#include "Recovery.h"

EFI_PEI_DEVICE_RECOVERY_MODULE_PPI SerialRecoveryModule = {
  GetNumberRecoveryCapsules, GetRecoveryCapsuleInfo, SerialLoadRecoveryCapsule
};

//
// PPI to be installed
//
EFI_PEI_PPI_DESCRIPTOR SerialRecoveryPpiList[] = { 
  {
    EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gEfiPeiDeviceRecoveryModulePpiGuid, &SerialRecoveryModule
  }
};

//
// Global variable to hold current buffer index
//
UINT32   mCurrentIndex = 0;
  
/**
  @param[in]  FileHandle  Handle of the file being invoked.
  @param[in]  PeiServices Describes the list of possible PEI Services.

  @retval     EFI_SUCCESS PPI successfully installed.

**/  
EFI_STATUS
EFIAPI
SerialRecoveryPeimEntry (
  IN EFI_PEI_FILE_HANDLE     FileHandle,
  IN CONST EFI_PEI_SERVICES  **PeiServices
  )
{
  EFI_STATUS        Status;

  Status = PeiServicesInstallPpi (SerialRecoveryPpiList);
  
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/**
  Returns the number of DXE capsules residing on the device.

  This function searches for DXE capsules from the associated device and returns
  the number and maximum size in bytes of the capsules discovered. Entry 1 is 
  assumed to be the highest load priority and entry N is assumed to be the lowest 
  priority.

  @param[in]  PeiServices              General-purpose services that are available 
                                       to every PEIM
  @param[in]  This                     Indicates the EFI_PEI_DEVICE_RECOVERY_MODULE_PPI
                                       instance.
  @param[out] NumberRecoveryCapsules   Pointer to a caller-allocated UINTN. On 
                                       output, *NumberRecoveryCapsules contains 
                                       the number of recovery capsule images 
                                       available for retrieval from this PEIM 
                                       instance.

  @retval     EFI_SUCCESS              One or more capsules were discovered.
  @retval     EFI_DEVICE_ERROR         A device error occurred.
  @retval     EFI_NOT_FOUND            A recovery DXE capsule cannot be found.

**/
EFI_STATUS
EFIAPI
GetNumberRecoveryCapsules (
  IN  EFI_PEI_SERVICES                        **PeiServices,
  IN  EFI_PEI_DEVICE_RECOVERY_MODULE_PPI      *This,
  OUT UINTN                                   *NumberRecoveryCapsules
  )
{
  if (PcdGet32 (PcdSerialRecoveryImageSize) == 0) {
    DEBUG((DEBUG_ERROR, "\nSerial recovery not support. Set PcdSerialRecoveryImageSize to correct value.\n"));
    return EFI_NOT_FOUND;
  }
  
  *NumberRecoveryCapsules = 1;
  return EFI_SUCCESS;
}

/**
  Returns the size and type of the requested recovery capsule.

  This function gets the size and type of the capsule specified by CapsuleInstance.

  @param[in]  PeiServices       General-purpose services that are available to every PEIM
  @param[in]  This              Indicates the EFI_PEI_DEVICE_RECOVERY_MODULE_PPI 
                                instance.
  @param[in]  CapsuleInstance   Specifies for which capsule instance to retrieve 
                                the information.  This parameter must be between 
                                one and the value returned by GetNumberRecoveryCapsules() 
                                in NumberRecoveryCapsules.
  @param[out] Size              A pointer to a caller-allocated UINTN in which 
                                the size of the requested recovery module is 
                                returned.
  @param[out] CapsuleType       A pointer to a caller-allocated EFI_GUID in which 
                                the type of the requested recovery capsule is 
                                returned.  The semantic meaning of the value 
                                returned is defined by the implementation.

  @retval     EFI_SUCCESS       One or more capsules were discovered.
  @retval     EFI_DEVICE_ERROR  A device error occurred.
  @retval     EFI_NOT_FOUND     A recovery DXE capsule cannot be found.

**/
EFI_STATUS
EFIAPI
GetRecoveryCapsuleInfo (
  IN  EFI_PEI_SERVICES                      **PeiServices,
  IN  EFI_PEI_DEVICE_RECOVERY_MODULE_PPI    *This,
  IN  UINTN                                 CapsuleInstance,
  OUT UINTN                                 *Size,
  OUT EFI_GUID                              *CapsuleType
  )
{
  if (PcdGet32 (PcdSerialRecoveryImageSize) == 0) {
    DEBUG((DEBUG_ERROR, "\nSerial recovery not support. Set PcdSerialRecoveryImageSize to correct value.\n"));
    return EFI_NOT_FOUND;    
  }
  *Size = PcdGet32 (PcdSerialRecoveryImageSize);
  *CapsuleType  = gRecoveryOnSerialGuid;
  return EFI_SUCCESS;
}

/**
  Loads a DXE capsule from some media into memory.

  This function, by whatever mechanism, retrieves a DXE capsule from some device
  and loads it into memory. Note that the published interface is device neutral.

  @param[in]     PeiServices       General-purpose services that are available 
                                   to every PEIM
  @param[in]     This              Indicates the EFI_PEI_DEVICE_RECOVERY_MODULE_PPI
                                   instance.
  @param[in]     CapsuleInstance   Specifies which capsule instance to retrieve.
  @param[out]    Buffer            Specifies a caller-allocated buffer in which 
                                   the requested recovery capsule will be returned.

  @retval       EFI_SUCCESS        The capsule was loaded correctly.
  @retval       EFI_DEVICE_ERROR   A device error occurred.
  @retval       EFI_NOT_FOUND      A requested recovery DXE capsule cannot be found.

**/
EFI_STATUS
EFIAPI
SerialLoadRecoveryCapsule (
  IN  EFI_PEI_SERVICES                      **PeiServices,
  IN  EFI_PEI_DEVICE_RECOVERY_MODULE_PPI    *This,
  IN  UINTN                                 CapsuleInstance,
  OUT VOID                                  *Buffer
  )
{
  CHAR8     *Buff;
  UINT32    FileSize;
  UINT8     Result;
  CHAR8     *Message;
  UINTN     Number;
  CHAR8     Char;
  CHAR8     *ReadChar; 
  UINT32    WaitCount;
  BOOLEAN   Recovery;
  
  FileSize = 0;
  Result   = 0xFF;
  Char     = 0;
  ReadChar = &Char;
  Recovery = FALSE;

  GetNumberRecoveryCapsules (PeiServices, This, &Number);
  if (Number == 0) {
    return EFI_UNSUPPORTED;
  }

  InitSerialPort ();

  *ReadChar ='\n';
  SendSerialChar (*ReadChar);
  PrintCopyRightMessage();

  Message = "Press space to start recovery or 'Q' to quit\n\r";
  SendSerialString (Message);
  do {
    WaitCount = 0xF;    // EKCheck
    while (WaitCount--)
    {
      if (GetSerialChar (ReadChar) == TRUE)
      {
        Recovery = TRUE;
        break;
      }
    }

    if (*ReadChar == ' ') {
      break;
    }

    if (*ReadChar == 'Q' || *ReadChar == 'q') {
      Message = "Serial Recovery is aborted by user.\n\r";
      SendSerialString (Message);
      return EFI_ABORTED;
    }

  } while (Recovery == TRUE);

  Message = "Send BIOS image using XMODEM protocol\n\r";
  SendSerialString (Message);
  
  //
  //Wait for 3-5 Seconds before User Sends a file
  //
  MicroSecondDelay (20000000); 
  
  Buff = Buffer;
  if (!ReadFileFromSerial (Buff,&FileSize,&Result)) {
    DEBUG ((DEBUG_ERROR, "\nRead File Failed Capsule Size= %d, FileRead Result=%d\n",FileSize,Result));
    if (Result == 1) {
      DEBUG((DEBUG_ERROR, "\nNo Responce from Terminal\n"));
    }
    if (Result == 3) {
      DEBUG((DEBUG_ERROR, "\nFile Size over Run\n"));
    }
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}

/**
  Do necessary initialization for COM port.

**/
VOID
InitSerialPort(
  )
{
  //
  // Disable all interrupts
  //
  IoWrite8 (INTERRUPT_ENABLE_REG, 0x00);
  MicroSecondDelay (1000);
  //
  // Enable Baud Rate Programming
  //
  IoWrite8 (LINE_CONTROL_REG, 0x80);
  MicroSecondDelay (1000);
  //
  // Program Baud Rate LSB
  //  
  IoWrite8 (DIVISOR_LATCH_LSB_REG, BAUD_DIVISOR_LSB);
  MicroSecondDelay (1000);
  //
  // Program Baud Rate MSB
  //
  IoWrite8 (DIVISOR_LATCH_MSB_REG, BAUD_DIVISOR_MSB);
  MicroSecondDelay (1000); 
  //
  // Set to 8 bits, 1 Stop, No Parity
  //
  IoWrite8 (LINE_CONTROL_REG, 0x03);
  MicroSecondDelay (1000);
  //
  // Clear and enable FIFOs 
  //
  IoWrite8 (FIFO_CONTROL_REG, 0x01);
  MicroSecondDelay (1000);
  //
  // Disable all interrupts
  //
  IoWrite8 (INTERRUPT_ENABLE_REG, 0x00);
  MicroSecondDelay (1000); 
  //
  // Clear and enable FIFOs 
  //
  IoWrite8 (FIFO_CONTROL_REG, 0xC7);
  MicroSecondDelay (1000); 
  //
  // Activate DTR and RTS
  //
  IoWrite8 (MODEM_CONTROL_REG, 0x03);
  MicroSecondDelay (1000); 

  //
  // Discard any garbage that may be in the receive FIFO
  // Check if receive data ready, else read data and discard
  //
  while (IoRead8 (LINE_STATUS_REG) & 01) {
    IoRead8 (SERIAL_DATA_REG);
  }  
}

/**
  Read file from serial port.

  @param[in]     Buffer       The buffer to read into.
  @param[out]    Size         The file size of reading.
  @param[out]    Result       The result of reading.

  @retval        TRUE         Read file successfully.
  @retval        FALSE        Fail to read file from serial port.

**/

BOOLEAN
ReadFileFromSerial (
  CHAR8*    Buffer,
  UINT32*   Size,
  UINT8*    Result
  )
{  
  BOOLEAN     Status;
  UINT32      NumBlocks;
  UINT32      Count;
  UINT32      BlockID;  
  UINT8       BlockNum;
  UINT8       Command;
  UINT8       Data;  

  Count     = 10;
  BlockID   = 1;
  BlockNum  = 1;
  Data      = 0;
  Command   = XMODEM_NAK;  
  NumBlocks = PcdGet32 (PcdSerialRecoveryImageSize) / 128;

  //
  // Read recovery file through serial port, check checksum, signature etc.,
  // and copy it to the buffer ImageStart.
  //
  NumBlocks++;
  while (NumBlocks) {
    //
    //Send NAK
    //
    if (!SendNakAck (&Data, Command)) {
      *Result = 1;
      return FALSE;
    }
    //
    // If end of transfer, exit with success
    //
    if (Data == XMODEM_EOT) {
      Command = XMODEM_ACK;
      SendSerialData (Command);
      BlockID--;
      *Size = BlockID*128;
      *Result = 0;
      return TRUE;
    }
    if (Data == XMODEM_SOH) {
      //
      //Start header received, get rest of the packet
      //
      
      //
      // Read block#
      //
      Status = GetSerialData (&Data);
      //
      // If block number doesn't match, retry
      //
      if ((Status) && (Data == BlockNum)) {
        //
        // Read FF-Block#, one's compliment
        //
        Status = GetSerialData (&Data);
        //
        // If FF-block number doesn't match, retry
        //
        if (Status) {
          //
          // Read 128 byte packet
          //
          if (ReadSerialBlock (Buffer)) {   
            BlockNum++;
            BlockID++;
            NumBlocks--;
            Command = XMODEM_ACK;
            continue;
          }
        }
      }
      while (GetSerialData (&Data));
    }
  }
  
  //
  // No more block to read, No EOT byte received, terminate xfer and exit with error
  //
  *Result = 3;
  //
  // If abort, read and discard
  //
  while (GetSerialData(&Data));

  Command = XMODEM_CAN;
  while (Count--) {
    //
    // Send CANCEL Command
    //
    SendSerialData (Command);
  }
  return FALSE;
}

/**
  Read block from serial port.

  @param[out]  Buffer       The buffer to read into.

  @retval      TRUE         Read block successfully.
  @retval      FALSE        Read error, bad checksum or no checksum.

**/
BOOLEAN ReadSerialBlock(UINT8* Buffer)
{
  UINT8   CheckSum = 0;
  UINT8   DataByte = 0;
  UINT8*  DataBuffer = Buffer;
  UINT32  TempIndex  = mCurrentIndex;
  UINT8   bytecount;

  for(bytecount=1; bytecount <= 128; bytecount++) { //read 128 byte packet
    if(!(GetSerialData(DataBuffer + mCurrentIndex))) //if error  reading serial port, retry packet
    {
      mCurrentIndex = TempIndex;
      return FALSE;
    }
      CheckSum = CheckSum + *(DataBuffer + mCurrentIndex++);
  }

  //
  // Get Checksum byte
  //
  if (!(GetSerialData(&DataByte))) {
    mCurrentIndex = TempIndex;
    return FALSE;
  }
  
  //
  // If byte checksum doesn't match, retry
  //
  if (DataByte != CheckSum) {
    mCurrentIndex = TempIndex;
    return FALSE;
  }
  return TRUE;
}

/**
  Read character from serial port.

  @param[out]     ReadData       The buffer to read into.

  @retval         TRUE           Read char successfully.
  @retval         FALSE          Fail to read char from serial port.

**/
BOOLEAN
SendNakAck (
  UINT8* Data, UINT8 XCommand
  )
{
  UINT8  AbortCount;
  UINT8  Count;
  CHAR8* SerialMsg;

  //
  // Number of NAKs or ACKs to send before abort
  //
  AbortCount = 12;
  Count      = 24;

  while (Count--) {
    SendSerialData(XCommand);
    if (GetSerialData1(Data)) {
        return TRUE;
    }
  }

  //
  // If timeout, cancel the transfer and
  // return false, with abort Message
  //
  while (GetSerialData(Data));    //If abort, read and discard

  XCommand = XMODEM_CAN;
  while (AbortCount--) {
    SendSerialData(XCommand); // Send CANCEL Command
  }
  SerialMsg = "\n\rAborting Serial Recovery";
  SendSerialString (SerialMsg);
  return FALSE;
}

/**
  Send a character to Serial Port.

  @param[in]  Char        The character to send.

**/
VOID
SendSerialChar (
  CHAR8 Char
)
{
  //
  // Send a character to Serial Port
  //
  while (!(IoRead8(LINE_STATUS_REG) & 0x20));
  IoWrite8 (SERIAL_DATA_REG, Char);
}

/**
  Read character from serial port.

  @param[out]     ReadData       The buffer to read into.

  @retval TRUE               Read char successfully.
  @retval FALSE              Fail to read char from serial port.

**/
BOOLEAN
GetSerialData1 (
  UINT8*  ReadData
  )
{
  INT32 MaxDelay = MAX_DATA1_DELAY;

  //
  // Wait for upto 1 second for the data byte to be ready
  //
  while (MaxDelay--) {
    if (IoRead8 (LINE_STATUS_REG) & 0x0A) {
      //
      // Exit if overrun/framing error
      //
      return FALSE;
    }
    if (IoRead8 (LINE_STATUS_REG) & 0x01) {
      //
      // Exit loop if character ready in Reveive buffer
      //      
      break;
    }
  }

  if (MaxDelay <= 0) {
    return FALSE;
  }

  //
  // Read data byte from receive biffer
  //
  *ReadData = IoRead8 (SERIAL_DATA_REG);

  return TRUE;
}

/**
  Read character from serial port.

  @param[out]     ReadData       The buffer to read into.

  @retval         TRUE           Read char successfully.
  @retval         FALSE          Fail to read char from serial port.

**/

BOOLEAN
GetSerialData (
  UINT8*  ReadData
  )
{

  INT32    MaxDelay = MAX_DATA_DELAY;
  //
  // Wait for upto 1 second for the data byte to be ready
  //
  while (MaxDelay--) {         
    if (IoRead8(LINE_STATUS_REG) & 0x0A) {
      //
      // Exit if overrun/framing error
      //
      return FALSE;
    }
    if (IoRead8 (LINE_STATUS_REG) & 0x01) {
      //
      // Exit loop if character ready in Reveive buffer
      //
      break;
    }
  }
  if (MaxDelay <= 0) {
    return FALSE;
  }
  
  //
  // Read data byte from receive biffer
  //
  *ReadData=IoRead8 (SERIAL_DATA_REG);

  return TRUE;
}

/**
  Send a character to Serial Port.

  @param[in]    Data    Char to send.

**/
VOID
SendSerialData (
  UINT8 Data
  )
{
  while (!(IoRead8(LINE_STATUS_REG) & 0x20));
  IoWrite8( SERIAL_DATA_REG, Data);
}

VOID SendSerialString (
  CHAR8* Str
  )
{
  while (*Str) {
    SendSerialChar(*Str++);
  }
}

/**
  Get a character from Serial Port.

  @param[out]   Data    Char buffer.

  @retval       TRUE    Read char successfully.
  @retval       FALSE   Timed out or bad status.

**/
BOOLEAN GetSerialChar (
  CHAR8* ReadChar
  )  // ReadChar is the output character
{
  INT32 MaxDelay=MAX_USER_DELAY;
  //
  // Wait for up to 30s for the user to enter Response
  //
  while (MaxDelay--)         
  {
    if (IoRead8(LINE_STATUS_REG) & 0x0A) {
      return  FALSE;
    }
    if (IoRead8(LINE_STATUS_REG) & 0x01) {
      //
      // Exit loop if character ready in Receive buffer
      //
      break;
    }
  }

  if (MaxDelay <= 0) {
    return FALSE;
  }
  
  //
  // Read character from receive buffer
  //
  *ReadChar = IoRead8 (SERIAL_DATA_REG);
  return TRUE;
}

/**
  Print a serial string.

**/
VOID
PrintCopyRightMessage (
  )
{
  CHAR8  *Message =  "\n\r*********************************************************\n\r"
            "               Serial Recovery start...\n\r"
            "*********************************************************\n\r";
  SendSerialString (Message);
}

