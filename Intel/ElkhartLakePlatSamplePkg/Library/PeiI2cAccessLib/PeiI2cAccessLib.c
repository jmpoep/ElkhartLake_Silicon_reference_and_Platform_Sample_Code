/** @file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2018 Intel Corporation.

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

#include <Library/I2cAccessLib.h>
#include <Register/SerialIoI2cRegs.h>

EFI_STATUS
I2cWriteRead (
  IN UINTN  MmioBase,
  IN UINT8  SlaveAddress,
  IN UINT8  WriteLength,
  IN UINT8  *WriteBuffer,
  IN UINT8  ReadLength,
  IN UINT8  *ReadBuffer,
  IN UINT64  TimeBudget
  //TODO: add Speed parameter
  )
{
  UINT8 ReadsNeeded = ReadLength;
  UINT64 CutOffTime;

  if ((WriteLength == 0 && ReadLength == 0) ||
      (WriteLength != 0 && WriteBuffer == NULL) ||
      (ReadLength != 0 && ReadBuffer == NULL) ) {
    DEBUG ((DEBUG_ERROR, "I2cWR Invalid Parameters\n"));
    return EFI_INVALID_PARAMETER;
  }

  //
  // Sanity checks to verify the I2C controller is alive
  // Conveniently, ICON register's values of 0 or FFFFFFFF indicate
  // I2c controller is out-of-order: either disabled, in D3 or in reset.
  //
  if (MmioRead32(MmioBase+R_I2C_MEM_CON) == 0xFFFFFFFF || MmioRead32(MmioBase+R_I2C_MEM_CON) == 0x0) {
    DEBUG ((DEBUG_ERROR, "I2cWR Device Error\n"));
    return EFI_DEVICE_ERROR;
  }

  MmioWrite32(MmioBase+R_I2C_MEM_ENABLE, 0x0);
  MmioRead32(MmioBase+0x40);
  MmioRead32(MmioBase+R_I2C_MEM_CLR_TX_ABRT);
  MmioWrite32(MmioBase+R_SERIAL_IO_I2C_MEM_SDA_HOLD, 0x001C001C);
  //
  // Set I2C Bus Speed at 400 kHz for GPIO Expander
  //
  MmioWrite32(MmioBase + R_I2C_MEM_FS_SCL_HCNT, 110);
  MmioWrite32(MmioBase + R_I2C_MEM_FS_SCL_LCNT, 207);
  MmioWrite32(MmioBase + R_I2C_MEM_TAR, SlaveAddress);
  MmioWrite32(MmioBase + R_I2C_MEM_CON, B_I2C_MEM_MASTER_MODE | V_I2C_MEM_SPEED_FAST | B_I2C_MEM_RESTART_EN | B_I2C_MEM_SLAVE_DISABLE );
  MmioWrite32(MmioBase+R_I2C_MEM_ENABLE, 0x1);
  CutOffTime = AsmReadTsc() + TimeBudget;

  while ( (MmioRead32(MmioBase+R_I2C_MEM_ENABLE_STATUS) & 1)==0 ) {
    if (AsmReadTsc() > CutOffTime) {
      DEBUG ((DEBUG_ERROR, "I2cWR timeout\n"));
      return EFI_TIMEOUT;
    }
  }

  while(1) {
    if(MmioRead32(MmioBase+R_I2C_MEM_INTR_STAT) & B_I2C_MEM_INTR_TX_ABRT) {
      DEBUG ((DEBUG_ERROR, "I2cWR Transfer aborted, reason = 0x%08x\n",MmioRead32(MmioBase+R_I2C_MEM_TX_ABRT_SOURCE)));
      MmioRead32(MmioBase+R_I2C_MEM_CLR_TX_ABRT);
      MmioAnd32(MmioBase+R_I2C_MEM_ENABLE, 0xFFFFFFFE);
      while ( (MmioRead32(MmioBase+R_I2C_MEM_ENABLE_STATUS) & 1)==1 ) {}
      return EFI_DEVICE_ERROR;
    }
    if (MmioRead32(MmioBase+R_I2C_MEM_STATUS) & B_I2C_MEM_STATUS_TFNF) {
      if (WriteLength > 1) {
        MmioWrite32(MmioBase+R_I2C_MEM_DATA_CMD, *WriteBuffer);
        WriteBuffer++;
        WriteLength--;
      } else if (WriteLength==1 && ReadLength != 0) {
        MmioWrite32(MmioBase+R_I2C_MEM_DATA_CMD, *WriteBuffer);
        WriteBuffer++;
        WriteLength--;
      } else if (WriteLength==1 && ReadLength == 0) {
        MmioWrite32(MmioBase+R_I2C_MEM_DATA_CMD, *WriteBuffer | B_I2C_MEM_CMD_STOP);
        WriteBuffer++;
        WriteLength--;
      } else if (ReadLength > 1) {
        MmioWrite32(MmioBase+R_I2C_MEM_DATA_CMD, B_I2C_MEM_CMD_READ);
        ReadLength--;
      } else if (ReadLength == 1) {
        MmioWrite32(MmioBase+R_I2C_MEM_DATA_CMD, B_I2C_MEM_CMD_READ|B_I2C_MEM_CMD_STOP);
        ReadLength--;
      }
    }

    if (ReadsNeeded) {
      if (MmioRead32(MmioBase+R_I2C_MEM_STATUS) & B_I2C_MEM_STATUS_RFNE) {
        *ReadBuffer = (UINT8)MmioRead32(MmioBase+R_I2C_MEM_DATA_CMD);
        ReadBuffer++;
        ReadsNeeded--;
      }
    }
    if (WriteLength==0 && ReadsNeeded==0 && !(MmioRead32(MmioBase+R_I2C_MEM_STATUS)&B_I2C_MEM_STATUS_ACTIVITY)) {
      MmioAnd32(MmioBase+R_I2C_MEM_ENABLE, 0xFFFFFFFE);
      while ( (MmioRead32(MmioBase+R_I2C_MEM_ENABLE_STATUS) & 1)==1 ) {}
      DEBUG ((DEBUG_INFO, "I2cWR success\n"));
      return EFI_SUCCESS;
    }
    if (AsmReadTsc() > CutOffTime) {
      MmioAnd32(MmioBase+R_I2C_MEM_ENABLE, 0xFFFFFFFE);
      while ( (MmioRead32(MmioBase+R_I2C_MEM_ENABLE_STATUS) & 1)==1 ) {}
      DEBUG ((DEBUG_ERROR, "I2cWR wrong ENST value\n"));
      return EFI_TIMEOUT;
    }

  }
}

/**
  Executes a block of I2C read/write and wait commands. This is intended to enable or configure devices that require multiple data transactions through a I2C bus.
  The command structure consists of entries with a command id, data count, and payload if applicable. The following is an example of a command block:

  static UINT8 SampleCommandBlock[] = {
    BLOCK_COMMAND_I2C_WRITE, 3, 0x01, 0x02, 0x03,    //Write data. The maximum payload is defined by MAX_DATA_COUNT
    BLOCK_COMMAND_WAIT, 10,                          //Wait for 10ms.
    BLOCK_COMMSND_I2C_READ, 1                        //Read 1 byte. This is also limited by MAX_DATA_COUNT
  }

  @param[in] I2cNumber               the serial controller to be used
  @param[in] SlaveAddress            the address for the device
  @param[in] I2cCommandBlock         pointer to a byte structure with all commands and data
  @param[in] BlockSize               total size of the command structure

  @retval    EFI_INVALID_PARAMETER   signals that a command or data count was invalid
  @retval    EFI_BUFFER_TOO_SMALL    the last command could not be executed since the buffer ended before reading all parameters
  @retval    EFI_SUCCESS             the command were executed without incident
**/

EFI_STATUS
I2cBlockWriteRead (
  IN UINT8  I2cNumber,
  IN UINT8  SlaveAddress,
  IN UINT8 *I2cCommandBlock,
  IN UINT32 BlockSize
)
{
  UINTN                   Bar0;
  UINT8                   DataBuffer[MAX_DATA_COUNT];
  UINT32                  BlockBufferIndex;
  UINT32                  Index;
  UINT8                   CommandId;
  UINT8                   CommandDataCount;
  EFI_STATUS              Status;
  UINT64                  PciCfgBase;

  DEBUG((DEBUG_INFO, "I2C Block Write-Read Start:\n"));
  PciCfgBase  = GetSerialIoI2cPciCfg (I2cNumber);
  Bar0        = (UINTN) GetSerialIoBar (PciCfgBase);
  if ((Bar0 == 0xFFFFFFFFFFFFF000ULL) || (Bar0 == 0xFFFFF000ULL) || (Bar0 == 0x0)) {
    DEBUG ((DEBUG_ERROR, "I2cBlockWriteRead () - Invalid Bar0\r\n"));
    return EFI_UNSUPPORTED;
  }
  DEBUG((DEBUG_INFO, "Bar0 id = 0x%x \r\n", Bar0));

  Status = EFI_SUCCESS;
  BlockBufferIndex = 0;

  while (BlockBufferIndex + 2 <= BlockSize) {
    ///
    /// Process a command by reading the command and data count
    ///
    CommandId = I2cCommandBlock[BlockBufferIndex++];
    CommandDataCount = I2cCommandBlock[BlockBufferIndex++];
    switch (CommandId) {
    case BLOCK_COMMAND_I2C_WRITE:
      if (CommandDataCount > MAX_DATA_COUNT) {
        DEBUG((DEBUG_ERROR, "Invalid WRITE data count: %d\n", CommandDataCount));
        return EFI_INVALID_PARAMETER;
      }
      if (BlockBufferIndex + CommandDataCount >= BlockSize) {
        DEBUG((DEBUG_ERROR, "WRITE buffer overrun: %d\n", CommandDataCount));
        return EFI_BUFFER_TOO_SMALL;
      }
      DEBUG((DEBUG_INFO, "I2C Write %d: ", CommandDataCount));
      for (Index = 0; Index < CommandDataCount; Index++) {
        DataBuffer[Index] = I2cCommandBlock[BlockBufferIndex++];
        DEBUG((DEBUG_INFO, "%x ", DataBuffer[Index]));
      }
      DEBUG((DEBUG_INFO, "\n"));
      Status = I2cWriteRead(Bar0, SlaveAddress, CommandDataCount, DataBuffer, 0, NULL, WAIT_1_SECOND);
      if (Status != EFI_SUCCESS) {
        return Status;
      }
      break;

    case BLOCK_COMMAND_I2C_READ:
      if (CommandDataCount > MAX_DATA_COUNT) {
        DEBUG((DEBUG_ERROR, "Invalid READ data count: %d\n", CommandDataCount));
        return EFI_INVALID_PARAMETER;
      }
      Status = I2cWriteRead(Bar0, SlaveAddress, 0, NULL, CommandDataCount, DataBuffer, WAIT_1_SECOND);
      if (Status != EFI_SUCCESS) {
        return Status;
      }
      DEBUG((DEBUG_INFO, "I2C Read %d: ", CommandDataCount));
      for (Index = 0; Index < CommandDataCount; Index++) {
        DEBUG((DEBUG_INFO, "%x ", DataBuffer[Index]));
      }
      DEBUG((DEBUG_INFO, "\n"));
      break;

    case BLOCK_COMMAND_WAIT:
      DEBUG((DEBUG_INFO, "Wait %dms\n", CommandDataCount));
      MicroSecondDelay((UINTN)CommandDataCount * 1000);
      break;

    default:
      DEBUG((DEBUG_ERROR, "Invalid command.\n"));
      return EFI_INVALID_PARAMETER;
    }
  }
  ///
  /// If the buffer index is not at the end of the buffer defined by size, there was a mismatch and potentially an error.
  ///
  if (BlockBufferIndex != BlockSize) {
    DEBUG((DEBUG_ERROR, "There was an error executing the I2C command block. Buffer length mismatch.\n"));
    return EFI_BAD_BUFFER_SIZE;
  }
  DEBUG((DEBUG_INFO, "I2C Block Write-Read Done.\n"));
  return EFI_SUCCESS;
}

