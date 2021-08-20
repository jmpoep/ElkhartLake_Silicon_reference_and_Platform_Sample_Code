/** @file
  This module defines functions that perform communication
  with eMMC card. Functions defined here should only be used
  in the context of integrated eMMC controller.

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

#include "EmmcSoftwareTuning.h"

//
// Command Definitions
//
#define WRITE_BYTE_MODE                       3
#define HS_TIMING_INDEX                       185
#define BUS_WIDTH_INDEX                       183

#define CARD_STATUS_ERROR_BITMASK             0xFFF9A080

#define EMMC_BASE_CLOCK_MHZ                   200

typedef enum {
  ResponseNo = 0,
  ResponseR1,
  ResponseR1b,
  ResponseR2,
  ResponseR3,
  ResponseR4,
  ResponseR5,
  ResponseR5b,
  ResponseR6,
  ResponseR7
} RESPONSE_TYPE;

typedef enum {
  NoData = 0,
  InData,
  OutData
} TRANSFER_TYPE;

/**
  Print error reason of the command error.

  @param[in] ErrorCode  Error interrupt register.

  @return Error status
**/
STATIC
EFI_STATUS
EmmcGetErrorReason (
  IN UINT16  ErrorCode
  )
{
  EFI_STATUS    Status;

  Status = EFI_DEVICE_ERROR;

  if (ErrorCode & BIT0) {
    Status = EFI_TIMEOUT;
    DEBUG ((DEBUG_INFO, "Command Timeout Error"));
  }

  if (ErrorCode & BIT1) {
    Status = EFI_CRC_ERROR;
    DEBUG ((DEBUG_INFO, "Command CRC Error"));
  }

  if (ErrorCode & BIT2) {
    DEBUG ((DEBUG_INFO, "Command End Bit Error"));
  }

  if (ErrorCode & BIT3) {
    DEBUG ((DEBUG_INFO, "Command Index Error"));
  }
  if (ErrorCode & BIT4) {
    Status = EFI_TIMEOUT;
    DEBUG ((DEBUG_INFO, "Data Timeout Error"));
  }

  if (ErrorCode & BIT5) {
    Status = EFI_CRC_ERROR;
    DEBUG ((DEBUG_INFO, "Data CRC Error"));
  }

  if (ErrorCode & BIT6) {
    Status = EFI_CRC_ERROR;
    DEBUG ((DEBUG_INFO, "Data End Bit Error"));
  }

  if (ErrorCode & BIT7) {
    DEBUG ((DEBUG_INFO, "Current Limit Error"));
  }

  if (ErrorCode & BIT8) {
    DEBUG ((DEBUG_INFO, "Auto CMD12 Error"));
  }

  if (ErrorCode & BIT9) {
    DEBUG ((DEBUG_INFO, "ADMA Error"));
  }

  return Status;
}

/**
  Reset eMMC.

  @param[in] EmmcMmio  eMMC MMIO address

  @return Status of the reset
**/
STATIC
EFI_STATUS
EmmcReset (
  IN UINT32  EmmcMmio
  )
{
  UINT8   Data8;
  UINT8   ResetType;
  UINT16  SaveClkCtl;
  UINT32  TimeOutCount;

  ResetType = (B_SCS_MEM_SWRST_CMDLINE | B_SCS_MEM_SWRST_DATALINE);

  //
  // To improve eMMC stability, we zero the R_SCS_MEM_CLKCTL register and
  // stall for 50 microsecond before reseting the controller. We
  // restore the register setting following the reset operation.
  //
  SaveClkCtl = MmioRead16 (EmmcMmio + R_SCS_MEM_CLKCTL);
  MmioWrite16 (EmmcMmio + R_SCS_MEM_CLKCTL, 0);
  MicroSecondDelay (50);
  //
  // Reset the SD host controller
  //
  MmioWrite8 (EmmcMmio + R_SCS_MEM_SWRST, ResetType);

  TimeOutCount  = 1000; // 1 second timeout
  do {
    MicroSecondDelay (1 * 1000);

    TimeOutCount --;

    Data8 = MmioRead8 (EmmcMmio + R_SCS_MEM_SWRST);
    if ((Data8 & ResetType) == 0) {
      break;
    }
  } while (TimeOutCount > 0);

  //
  // We now restore the R_SCS_MEM_CLKCTL register which we set to 0 above.
  //
  MmioWrite16 (EmmcMmio + R_SCS_MEM_CLKCTL, SaveClkCtl);

  if (TimeOutCount == 0) {
    DEBUG ((DEBUG_ERROR, "EmmcReset: Time out \n"));
    return EFI_TIMEOUT;
  }

  return EFI_SUCCESS;
}

/**
  Check eMMc card status.

  @param[in] CardStatus  Card status register value

  @return Status of the card.
**/
STATIC
BOOLEAN
EmmcIsCardInErrorState (
  IN UINT32  CardStatus
  )
{
  if (CardStatus & CARD_STATUS_ERROR_BITMASK) {
    return TRUE;
  }
  return FALSE;
}

/**
  Wait for link idle.

  @param[in] EmmcMmio  eMMC MMIO address

  @return Status of the polling
**/
STATIC
BOOLEAN
EmmcWaitForLinkIdle (
  IN UINT32  EmmcMmio
  )
{
  UINT32  Timeout;

  Timeout = 1000;
  //
  // Check both CMD and DAT inhibit.
  // For our purposes we may assume that both CMD and DAT line must be free
  // to transmit command.
  //
  while (MmioRead32 (EmmcMmio + R_SCS_MEM_PSTATE) & (BIT0 | BIT1)) {
    MicroSecondDelay (100);
    Timeout--;
    if (Timeout == 0) {
      return FALSE;
    }
  }

  return TRUE;
}

/**
  Wait for command complete interrupt

  @param[in] EmmcMmio  eMMC MMIO address

  @return Status of the polling
**/
STATIC
EFI_STATUS
EmmcWaitForCommandComplete (
  IN UINT32  EmmcMmio
  )
{
  UINT16  InterruptStatus;
  UINT32  Timeout;

  Timeout = 1000;

  do {
    InterruptStatus = MmioRead16 (EmmcMmio + R_SCS_MEM_ERINTSTS);
    if (InterruptStatus & B_SCS_MEM_ERINTSTS_MASK) {
      DEBUG ((DEBUG_ERROR, "Error during command execution, error_int = %X\n", InterruptStatus));
      return EmmcGetErrorReason (InterruptStatus);
    }

    InterruptStatus = MmioRead16 (EmmcMmio + R_SCS_MEM_NINTSTS);
    if (InterruptStatus & B_SCS_MEM_NINTSTS_CMD_COMPLETE) {
      // Clear CMD_COMPLETE interrupt. This bit is W1C.
      MmioWrite16 (EmmcMmio + R_SCS_MEM_NINTSTS, B_SCS_MEM_NINTSTS_CMD_COMPLETE);
      return EFI_SUCCESS;
    }
    MicroSecondDelay (100);
    Timeout--;
  } while (Timeout > 0);

  return EFI_TIMEOUT;
}

/**
  Read response data from eMMC controller internal buffer.

  @param[in]  EmmcMmio        eMMC MMIO address
  @param[in]  ResponseType    Type of the response
  @param[out] ResponseBuffer  Buffer for the response data
**/
STATIC
VOID
EmmcReadResponseData (
  IN UINT32         EmmcMmio,
  IN RESPONSE_TYPE  ResponseType,
  OUT UINT32        *ResponseBuffer
  )
{
  UINT32  ResponseDataCount;
  UINT32  Index;
  UINT32  Data32;
  UINT64  Data64;
  UINT32  *ResDataPtr;

  if (ResponseType == ResponseNo) {
    return;
  }

  if (ResponseType == ResponseR2) {
    ResponseDataCount = 4;
  } else {
    ResponseDataCount = 1;
  }

  ResDataPtr = ResponseBuffer;
  for (Index = 0; Index < ResponseDataCount; Index++) {
    *ResDataPtr = MmioRead32 (EmmcMmio + R_SCS_MEM_RESP + Index * 4);
    ResDataPtr++;
  }

  //
  // R2 response is shifted by a byte to the right in response register. To compensate
  // for that we shift all 4 dwords to the left by a byte
  //
  if (ResponseType == ResponseR2) {
    Data32 = 1;
    for (Index = 0; Index < ResponseDataCount; Index++) {
      Data64 = LShiftU64 (*ResponseBuffer, 8);
      *ResponseBuffer = (UINT32) ((Data64 & 0xFFFFFFFF) | Data32);
      Data32 =  (UINT32) RShiftU64 (Data64, 32);
      ResponseBuffer++;
    }
  }
}

/**
  Poll for transfer complete interrupt.

  @param[in] EmmcMmio  eMMC MMIO address

  @return Status of the polling
**/
STATIC
EFI_STATUS
EmmcWaitForTransferComplete (
  IN UINT32  EmmcMmio
  )
{
  UINT16  InterruptStatus;
  UINT32  Timeout;

  Timeout = 1000;
  do {
    InterruptStatus = MmioRead16 (EmmcMmio + R_SCS_MEM_ERINTSTS);
    if (InterruptStatus & B_SCS_MEM_ERINTSTS_MASK) {
      return EmmcGetErrorReason (InterruptStatus);
    }

    InterruptStatus = MmioRead16 (EmmcMmio + R_SCS_MEM_NINTSTS);
    if (InterruptStatus & B_SCS_MEM_NINTSTS_TRANSFER_COMPLETE) {
      MmioWrite16 (EmmcMmio + R_SCS_MEM_NINTSTS, B_SCS_MEM_NINTSTS_TRANSFER_COMPLETE);
      return EFI_SUCCESS;
    }

    MicroSecondDelay (100);
    Timeout--;
  } while (Timeout > 0);

  return EFI_TIMEOUT;
}

/**
  Clear all interrupts status.

  @param[in] EmmcMmio  eMMC MMIO address
**/
STATIC
VOID
EmmcClearInterrupts (
  IN UINT32  EmmcMmio
  )
{
  MmioWrite16 (EmmcMmio + R_SCS_MEM_NINTSTS, 0xffff);
  MmioWrite16 (EmmcMmio + R_SCS_MEM_ERINTSTS, 0xffff);
}

/**
  Send command to eMMC card.

  @param[in]       EmmcMmio      eMMC MMIO address
  @param[in]       CommandIndex  eMMC command index
  @param[in]       Argument      Command argument
  @param[in]       DataType      Transfer direction
  @param[in, out]  Buffer        Transfer buffer
  @param[in]       BufferSize    Size of the transfer buffer
  @param[in]       ResponseType  Type of the response
  @param[out]      ResponseData  Response data buffer

  @return Status of the command
**/
STATIC
EFI_STATUS
SendCommand (
  IN     UINT32         EmmcMmio,
  IN     UINT16         CommandIndex,
  IN     UINT32         Argument,
  IN     TRANSFER_TYPE  DataType,
  IN OUT UINT8          *Buffer, OPTIONAL
  IN     UINT32         BufferSize,
  IN     RESPONSE_TYPE  ResponseType,
  OUT    UINT32         *ResponseData
  )
{
  EFI_STATUS  Status;
  UINT16      Data16;
  UINT16      BlockCount;
  UINT32      BlockLength;

  Status             = EFI_SUCCESS;
  BlockLength        = BLOCK_LENGTH;

  if (!EmmcWaitForLinkIdle (EmmcMmio)) {
    DEBUG ((DEBUG_ERROR, "EmmcTune: Link not ready for commands!\n"));
    return EFI_DEVICE_ERROR;
  }

  EmmcClearInterrupts (EmmcMmio);

  Data16 = 0;
  BlockCount = 0;
  if (Buffer != NULL) {
    MmioWrite32 (EmmcMmio + R_SCS_MEM_DMAADR, (UINT32)(UINTN)Buffer);

    if (BufferSize <= BlockLength) {
      Data16 |= BufferSize;
      BlockCount = 1;
    } else {
      Data16 |= BlockLength;
      BlockCount = (UINT16) (BufferSize / BlockLength);
    }
    Data16 |= 0x7000; // set buffer boundary to 512KB

    MmioWrite16 (EmmcMmio + R_SCS_MEM_BLKSZ, Data16);
    MmioWrite16 (EmmcMmio + R_SCS_MEM_BLKCNT, BlockCount);
  }

  //
  // Argument
  //
  MmioWrite32 (EmmcMmio + R_SCS_MEM_CMDARG, Argument);

  //
  // Transfer Mode
  //
  Data16 = MmioRead16 (EmmcMmio + R_SCS_MEM_XFRMODE);

  //
  // Data Transfer Direction Select
  //
  Data16 = 0;
  if (DataType == InData) {
    Data16 |= B_SCS_MEM_XFRMODE_DATA_TRANS_DIR;
  }

  if (DataType != NoData) {
    Data16 |= BIT0; // DMA enable
  }

  if (BlockCount > 1 || CommandIndex == EMMC_SEND_EXT_CSD) {
    Data16 |= B_SCS_MEM_XFRMODE_BLKCNT_EN;
  }

  MmioWrite16 (EmmcMmio + R_SCS_MEM_XFRMODE, Data16);

  switch (ResponseType) {
    case ResponseNo:
      Data16 = (CommandIndex << 8);
      break;

    case ResponseR1:
    case ResponseR5:
    case ResponseR6:
    case ResponseR7:
      Data16 = (CommandIndex << 8) | V_SCS_MEM_SDCMD_RESP_TYPE_SEL_RESP48 |
        B_SCS_MEM_SDCMD_CMD_INDEX_CHECK_EN | B_SCS_MEM_SDCMD_CMD_CRC_CHECK_EN;
      break;

    case ResponseR1b:
    case ResponseR5b:
      Data16 = (CommandIndex << 8) | V_SCS_MEM_SDCMD_RESP_TYPE_SEL_RESP48_CHK |
        B_SCS_MEM_SDCMD_CMD_INDEX_CHECK_EN | B_SCS_MEM_SDCMD_CMD_CRC_CHECK_EN;
      break;

    case ResponseR2:
      Data16 = (CommandIndex << 8) | V_SCS_MEM_SDCMD_RESP_TYPE_SEL_RESP136 |
        B_SCS_MEM_SDCMD_CMD_CRC_CHECK_EN;
      break;

    case ResponseR3:
    case ResponseR4:
      Data16 = (CommandIndex << 8) | V_SCS_MEM_SDCMD_RESP_TYPE_SEL_RESP48;
      break;

    default:
      ASSERT (FALSE);
      return EFI_INVALID_PARAMETER;
  }

  if (DataType != NoData) {
    Data16 |= B_SCS_MEM_SDCMD_DATA_PRESENT_SEL;
  }

  DEBUG ((DEBUG_VERBOSE, "EmmcTune: Start CMD [%d]\n", CommandIndex));
  MmioWrite16 (EmmcMmio + R_SCS_MEM_SDCMD, Data16);

  Status = EmmcWaitForCommandComplete (EmmcMmio);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  EmmcReadResponseData (EmmcMmio, ResponseType, ResponseData);

  if (ResponseType == ResponseR1b || ResponseType == ResponseR5b) {
    Status = EmmcWaitForTransferComplete (EmmcMmio);
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  if (Buffer != NULL) {
    Status = EmmcWaitForTransferComplete (EmmcMmio);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Transfer not complete!\n"));
      return Status;
    }
  }
  return Status;
}

/**
  Send command to eMMC card.

  @param[in]       EmmcMmio      eMMC MMIO address
  @param[in]       CommandIndex  eMMC command index
  @param[in]       Argument      Command argument
  @param[in]       DataType      Transfer direction
  @param[in, out]  Buffer        Transfer buffer
  @param[in]       BufferSize    Size of the transfer buffer
  @param[in]       ResponseType  Type of the response
  @param[out]      ResponseData  Response data buffer

  @return Status of the command
**/
STATIC
EFI_STATUS
EmmcSendCommand (
  IN     UINT32          EmmcMmio,
  IN     UINT16          CommandIndex,
  IN     UINT32          Argument,
  IN     TRANSFER_TYPE   DataType,
  IN OUT UINT8           *Buffer, OPTIONAL
  IN     UINT32          BufferSize,
  IN     RESPONSE_TYPE   ResponseType,
  OUT    UINT32          *ResponseData
  )
{
  EFI_STATUS    Status;

  Status = SendCommand (
             EmmcMmio,
             CommandIndex,
             Argument,
             DataType,
             Buffer,
             BufferSize,
             ResponseType,
             ResponseData
             );

  if (!EFI_ERROR (Status)) {
    if (ResponseType == ResponseR1 || ResponseType == ResponseR1b) {
      ASSERT (ResponseData != NULL);
      if (EmmcIsCardInErrorState (*ResponseData)) {
        EmmcReset (EmmcMmio);
      }
    }
  } else {
    //
    // Reset Host Controller CMD and DATA
    //
    EmmcReset (EmmcMmio);
  }

  return Status;
}

/**
  Reads single block from eMMC card.

  @param[in]  EmmcMmio    eMMC MMIO address
  @param[in]  Lba         Block address
  @param[in]  BufferSize  Size of the buffer
  @param[out] Buffer      Caller allocated read buffer

  @return Status of the block read operation
**/
EFI_STATUS
EmmcReadSingleBlock (
  IN  UINT32   EmmcMmio,
  IN  EFI_LBA  Lba,
  IN  UINT32   BufferSize,
  OUT VOID     *Buffer
  )
{
  EFI_STATUS  Status;
  UINT32      Response;

  ASSERT (BufferSize == BLOCK_LENGTH);

  Status = EmmcSendCommand (
             EmmcMmio,
             EMMC_READ_SINGLE_BLOCK,
             (UINT32) Lba,
             InData,
             Buffer,
             BufferSize,
             ResponseR1,
             &Response
             );
  return Status;
}

/**
  Writes single block to eMMC card.

  @param[in] EmmcMmio    eMMC MMIO address
  @param[in] Lba         Block address
  @param[in] BufferSize  Size of the buffer
  @param[in] Buffer      Caller allocated block buffer

  @return Status of the write operation
**/
EFI_STATUS
EmmcWriteSingleBlock (
  IN UINT32   EmmcMmio,
  IN EFI_LBA  Lba,
  IN UINT32   BufferSize,
  IN VOID     *Buffer
  )
{
  EFI_STATUS  Status;
  UINT32      Response;

  ASSERT (BufferSize == BLOCK_LENGTH);

  Status = EmmcSendCommand (
             EmmcMmio,
             EMMC_WRITE_BLOCK,
             (UINT32) Lba,
             OutData,
             Buffer,
             BufferSize,
             ResponseR1,
             &Response
             );
  return Status;
}

/**
  Check if block is write protected.

  @param[in] EmmcMmio  eMMC MMIO address
  @param[in] Lba       Block address

  @retval TRUE   Block is write protected or test failed
  @retval FALSE  Block is not write protected
**/
BOOLEAN
EmmcIsBlockWriteProtected (
  IN UINT32   EmmcMmio,
  IN EFI_LBA  Lba
  )
{
  EFI_STATUS      Status;
  UINT32          CardStatus;
  UINT8           Buffer[8];

  ZeroMem (&Buffer, sizeof (Buffer));

  Status = EmmcSendCommand (
             EmmcMmio,
             EMMC_SEND_WRITE_PROT_TYPE,
             (UINT32) Lba,
             InData,
             Buffer,
             ARRAY_SIZE (Buffer),
             ResponseR1,
             &CardStatus
             );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "EmmcTune: Failed to send write protect check\n"));
    return TRUE;
  }

  if ((Buffer[7] & (BIT0 | BIT1)) !=0) {
    DEBUG ((DEBUG_INFO, "EmmcTune: Tuning block is write protected\n"));
    return TRUE;
  }

  return FALSE;
}

#pragma pack(1)
typedef struct {
  UINT8   CRC;
  UINT8   MDT;
  UINT32  PSN;
  UINT8   PRV;
  UINT8   PNM[6];
  UINT16  OID;
  UINT8   MID;
} CID;
#pragma pack()

/**
  Send ALL_SEND_CID command to eMMC card

  @param[in] EmmcMmio  eMMC MMIO address

  @return Status of the command
**/
STATIC
EFI_STATUS
EmmcSendGetAllCid (
  IN UINT32  EmmcMmio
  )
{
  EFI_STATUS  Status;
  CID         Cid;

  Status = EmmcSendCommand (
             EmmcMmio,
             EMMC_ALL_SEND_CID,
             0,
             NoData,
             NULL,
             0,
             ResponseR2,
             (UINT32*)&Cid
             );
  return Status;
}

/**
  Set eMMC relative card address.

  @param[in] EmmcMmio  eMMC MMIO address
  @param[in] Rca       Relative card address

  @return Status of the SET_RELATIVE_CARD_ADDR command
**/
STATIC
EFI_STATUS
EmmcSetRca (
  IN UINT32  EmmcMmio,
  IN UINT16  Rca
  )
{
  EFI_STATUS  Status;
  UINT32      CardStatus;

  Status = EmmcSendCommand (
             EmmcMmio,
             EMMC_SET_RELATIVE_ADDR,
             (Rca << 16),
             NoData,
             NULL,
             0,
             ResponseR1,
             &CardStatus
             );
  return Status;
}

/**
  Get OCR from the eMMC card.

  @param[in] EmmcMmio  eMMC MMIO address

  @return Status of the SEND_OP_COND command
**/
STATIC
EFI_STATUS
EmmcSendGetOcr (
  IN UINT32  EmmcMmio
  )
{
  EFI_STATUS  Status;
  UINT32      TimeOut;
  UINT32      OcrRegister;

  TimeOut = 5000;

  //
  // Go idle to reset state machine on card side.
  //
  Status = EmmcSendCommand (
             EmmcMmio,
             EMMC_GO_IDLE_STATE,
             0,
             NoData,
             NULL,
             0,
             ResponseNo,
             NULL
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = EmmcSendCommand (
             EmmcMmio,
             EMMC_SEND_OP_COND,
             0x40FF8080,
             NoData,
             NULL,
             0,
             ResponseR3,
             &OcrRegister
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "EmmcTune: failed to get first OCR\n"));
    return Status;
  }

  while (!(OcrRegister & BIT31)) {
    Status = EmmcSendCommand (
               EmmcMmio,
               EMMC_SEND_OP_COND,
               OcrRegister,
               NoData,
               NULL,
               0,
               ResponseR3,
               &OcrRegister
               );
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "EmmcTune: Failed to get OCR"));
      return Status;
    }

    MicroSecondDelay (1000);
    TimeOut--;
    if (TimeOut == 0) {
      DEBUG ((DEBUG_ERROR, "EmmcTune: card didn't power up in expected time\n"));
      return EFI_TIMEOUT;
    }
  }

  return EFI_SUCCESS;
}

/**
  Get CSD from the eMMC card.

  @param[in] EmmcMmio  eMMC MMIO address
  @param[in] Rca       Relative card address
  @param[in] Csd       Output CSD value

  @return Status of the operation
**/
STATIC
EFI_STATUS
EmmcSendGetCsd (
  IN  UINT32    EmmcMmio,
  IN  UINT16    Rca,
  OUT EMMC_CSD  *Csd
  )
{
  EFI_STATUS  Status;

  Status = EmmcSendCommand (
             EmmcMmio,
             EMMC_SEND_CSD,
             (Rca << 16),
             NoData,
             NULL,
             0,
             ResponseR2,
             (UINT32*)Csd
             );
  return Status;
}

/**
  Select eMMC card.

  @param[in] EmmcMmio  eMMC MMIO address
  @param[in] Rca       Relative card address

  @return Status of the select operation
**/
STATIC
EFI_STATUS
EmmcSelect (
  IN UINT32  EmmcMmio,
  IN UINT16  Rca
  )
{
  EFI_STATUS  Status;
  UINT32      CardStatus;

  Status = EmmcSendCommand (
             EmmcMmio,
             EMMC_SELECT_DESELECT_CARD,
             (Rca << 16),
             NoData,
             NULL,
             0,
             ResponseR1,
             &CardStatus
             );
  return Status;
}

/**
  Get extended CSD from eMMC card.

  @param[in] EmmcMmio  eMMC MMIO address
  @param[in] ExtCsd    Output value of the ext csd

  @return Status of the operation
**/
STATIC
EFI_STATUS
EmmcSendGetExtCsd (
  IN  UINT32        EmmcMmio,
  OUT EMMC_EXT_CSD  *ExtCsd
  )
{
  EFI_STATUS  Status;
  UINT32      CardStatus;

  Status = EmmcSendCommand (
             EmmcMmio,
             EMMC_SEND_EXT_CSD,
             0,
             InData,
             (UINT8*) ExtCsd,
             sizeof (EMMC_EXT_CSD),
             ResponseR1,
             &CardStatus
             );

  return Status;
}

typedef struct {
  UINT32  CmdSet:              3;
  UINT32  Reserved0:           5;
  UINT32  Value:               8;
  UINT32  Index:               8;
  UINT32  Access:              2;
  UINT32  Reserved1:           6;
} SWITCH_ARGUMENT;

/**
  Send eMMC switch command.

  @param[in] EmmcMmio        eMMC MMIO address
  @param[in] SwitchArgument  Switch argument value

  @return Status of the switch command
**/
STATIC
EFI_STATUS
EmmcSwitch (
  IN  UINT32           EmmcMmio,
  OUT SWITCH_ARGUMENT  *SwitchArgument
  )
{
  EFI_STATUS  Status;
  UINT32      CardStatus;

   Status  = EmmcSendCommand (
               EmmcMmio,
               EMMC_SWITCH,
               *(UINT32*)SwitchArgument,
               NoData,
               NULL,
               0,
               ResponseR1b,
               &CardStatus
               );
  return Status;
}

typedef enum {
  BackwardCompatible,
  HighSpeed,
  Hs200,
  Hs400
} EMMC_BUS_TIMING;

/**
  Switch eMMC bus timing.

  @param[in] EmmcMmio        eMMC MMIO address
  @param[in] DriverStrength  Driver strength
  @param[in] BusTiming       Target Bus timing

  @return Bus timing switch status
**/
STATIC
EFI_STATUS
EmmcSwitchBusTiming (
  IN UINT32                    EmmcMmio,
  IN SCS_EMMC_DRIVER_STRENGTH  DriverStrength,
  IN EMMC_BUS_TIMING           BusTiming
  )
{
  SWITCH_ARGUMENT  SwitchArgument;

  if (BusTiming == BackwardCompatible) {
    SwitchArgument.Value = 0;
  } else if (BusTiming == HighSpeed) {
    SwitchArgument.Value = 0x1;
  } else if (BusTiming == Hs200) {
    SwitchArgument.Value = 0x2;
  } else if (BusTiming == Hs400) {
    SwitchArgument.Value = 0x3;
  } else {
     ASSERT (FALSE);
     return EFI_INVALID_PARAMETER;
  }

  switch (DriverStrength) {
    case DriverStrength40Ohm:
      SwitchArgument.Value += 0x40;
      break;
    case DriverStrength50Ohm:
      break;
    case DriverStrength33Ohm:
    default:
      SwitchArgument.Value += 0x10;
  }

  SwitchArgument.CmdSet = 0;
  SwitchArgument.Index = HS_TIMING_INDEX;
  SwitchArgument.Access = WRITE_BYTE_MODE;
  return EmmcSwitch (EmmcMmio, &SwitchArgument);
}

/**
  Switch eMMC bus width.

  @param[in] EmmcMmio  eMMC MMIO address
  @param[in] UseDdr    TRUE if DDR is to be used
  @param[in] BusWidth  Bus width in bits

  @return Status of the switch
**/
STATIC
EFI_STATUS
EmmcSwitchBusWidth (
  IN UINT32   EmmcMmio,
  IN BOOLEAN  UseDdr,
  IN UINT32   BusWidth
  )
{
  SWITCH_ARGUMENT  SwitchArgument;
  EFI_STATUS       Status;
  UINT32           HostControlAnd;
  UINT32           HostControlOr;

  switch (BusWidth) {
    case 4:
      SwitchArgument.Value = 1;
      break;
    case 8:
      SwitchArgument.Value = 2;
      break;
    case 1:
    default:
      SwitchArgument.Value = 0;
      break;
  }

  if (UseDdr) {
    SwitchArgument.Value += 4;
  }

  SwitchArgument.CmdSet = 0;
  SwitchArgument.Index = BUS_WIDTH_INDEX;
  SwitchArgument.Access = WRITE_BYTE_MODE;

  Status = EmmcSwitch (EmmcMmio, &SwitchArgument);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Change BUS width in host controller.
  //
  if (BusWidth == 8) {
    HostControlAnd = BIT1;
    HostControlOr = BIT5;
  } else if (BusWidth == 4) {
    HostControlAnd = BIT5;
    HostControlOr = BIT1;
  } else {
    HostControlAnd = (BIT1 | BIT5);
    HostControlOr = 0;
  }
  MmioAndThenOr32 (EmmcMmio + R_SCS_MEM_HOST_CTL, ~HostControlAnd, HostControlOr);
  return EFI_SUCCESS;
}

/**
  Set SD clock frequency.

  @param[in] EmmcMmio        eMMc MMIO address
  @param[in] DriverStrength  Driver strength

  @return Status of the frequency switch
**/
STATIC
EFI_STATUS
SetClockFrequency (
  IN UINT32  EmmcMmio,
  IN UINT32  MaxFrequency
  )
{
  UINT16  Data16;
  UINT32  Frequency;
  UINT32  Divider = 0;
  UINT32  TimeOutCount;
  UINT32  CurrentClockInKHz;

  DEBUG ((DEBUG_INFO, "SetClockFrequency: BaseClockInMHz = %d \n", EMMC_BASE_CLOCK_MHZ));

  Frequency = (EMMC_BASE_CLOCK_MHZ * 1000 * 1000) / MaxFrequency;
  DEBUG ((DEBUG_INFO, "SetClockFrequency: FrequencyInHz = %d \n", Frequency));

  if ((EMMC_BASE_CLOCK_MHZ * 1000 * 1000 % MaxFrequency) != 0) {
    Frequency += 1;
  }

  Divider = 1;
  while (Frequency > Divider) {
    Divider = Divider * 2;
  }
  if (Divider >= 0x400) {
    Divider = 0x200;
  }
  Divider = Divider >> 1;

  DEBUG ((DEBUG_INFO, "SetClockFrequency: after shift: Base Clock Divider = 0x%x \n", Divider));

  CurrentClockInKHz = (EMMC_BASE_CLOCK_MHZ * 1000);
  if (Divider != 0) {
    CurrentClockInKHz = CurrentClockInKHz / (Divider * 2);
  }
  //
  //Set frequency
  //  Bit[15:8] SDCLK Frequency Select at offset 2Ch
  //    80h - base clock divided by 256
  //    40h - base clock divided by 128
  //    20h - base clock divided by 64
  //    10h - base clock divided by 32
  //    08h - base clock divided by 16
  //    04h - base clock divided by 8
  //    02h - base clock divided by 4
  //    01h - base clock divided by 2
  //    00h - Highest Frequency the target support (10MHz-63MHz)
  //
  //  Bit [07:06] are assigned to bit 09-08 of clock divider in SDCLK Frequency Select on SD controller 3.0
  //

  Data16 = (UINT16) ((Divider & 0xFF) << 8 | (((Divider & 0xFF00) >> 8) << 6));

  DEBUG ((DEBUG_INFO,
          "SetClockFrequency: base=%dMHz, clkctl=0x%04x, f=%dKHz\n",
          EMMC_BASE_CLOCK_MHZ,
          Data16,
          CurrentClockInKHz
          ));
  DEBUG ((DEBUG_INFO, "SetClockFrequency: set MMIO_CLKCTL value = 0x%x \n", Data16));

  MmioWrite16 (EmmcMmio + R_SCS_MEM_CLKCTL, Data16);
  Data16 |= BIT0;

  MmioWrite16 (EmmcMmio + R_SCS_MEM_CLKCTL, Data16);
  TimeOutCount = 1000;
  do {
    Data16 = MmioRead16 (EmmcMmio + R_SCS_MEM_CLKCTL);
    MicroSecondDelay (100);
    TimeOutCount--;
    if (TimeOutCount == 0) {
      DEBUG ((DEBUG_INFO, "SetClockFrequency: Timeout\n"));
      return EFI_TIMEOUT;
    }
  } while (!(Data16 & BIT1));

  Data16 |= BIT2;
  MmioWrite16 (EmmcMmio + R_SCS_MEM_CLKCTL, Data16);
  return EFI_SUCCESS;
}

/**
  Switch link speed to HS200.

  @param[in] EmmcMmio        eMMC MMIO address
  @param[in] DriverStrength  Driver strength

  @return Status of the switch
**/
STATIC
EFI_STATUS
EmmcSwitchToHs200 (
  IN UINT32                    EmmcMmio,
  IN SCS_EMMC_DRIVER_STRENGTH  DriverStrength
  )
{
  EFI_STATUS  Status;

  Status = EmmcSwitchBusWidth (EmmcMmio, FALSE, 8);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = EmmcSwitchBusTiming (EmmcMmio, DriverStrength, Hs200);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  MmioAndThenOr16 (EmmcMmio + R_SCS_MEM_HOST_CTL2, (UINT16)~0x7, 0x3);

  return SetClockFrequency (EmmcMmio, 200000000);
}

/**
  Switch link speed to HS400.

  @param[in] EmmcMmio        eMMC MMIO address
  @param[in] DriverStrength  Driver strength

  @return Status of the switch
**/
STATIC
EFI_STATUS
EmmcSwitchToHs400 (
  IN UINT32                    EmmcMmio,
  IN SCS_EMMC_DRIVER_STRENGTH  DriverStrength
  )
{
  EFI_STATUS  Status;

  Status = EmmcSwitchToHs200 (EmmcMmio, DriverStrength);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "EmmcTune: Failed to switch to HS200\n"));
    return Status;
  }

  Status = EmmcSwitchBusTiming (EmmcMmio, DriverStrength, HighSpeed);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = SetClockFrequency (EmmcMmio, 50000000);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  MmioAndThenOr16 (EmmcMmio + R_SCS_MEM_HOST_CTL2, (UINT16)~0x7, 0x2);

  Status = EmmcSwitchBusWidth (EmmcMmio, TRUE, 8);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = EmmcSwitchBusTiming (EmmcMmio, DriverStrength, Hs400);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  MmioAndThenOr16 (EmmcMmio + R_SCS_MEM_HOST_CTL2, (UINT16)~0x7, 0x5);

  return SetClockFrequency (EmmcMmio, 200000000);
}

/**
  Initialize eMMC card.

  @param[in] EmmcMmio        eMMC MMIO address
  @param[in] DriverStrength  Driver strength to be used in HS400

  @return Card initialization status
**/
EFI_STATUS
EmmcInitializeCard (
  IN UINT32                    EmmcMmio,
  IN SCS_EMMC_DRIVER_STRENGTH  DriverStrength
  )
{
  EFI_STATUS                 Status;
  EMMC_EXT_CSD               ExtCsd;
  EMMC_CSD                   Csd;

  ZeroMem (&ExtCsd, sizeof (EMMC_EXT_CSD));
  ZeroMem (&Csd, sizeof (EMMC_CSD));

  Status = EmmcSendGetOcr (EmmcMmio);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "EmmcTune: Failed to power up the card\n"));
    return Status;
  }

  //
  // We don't use any information from CID but we still have to
  // perform this step as it is required by eMMC specification.
  //
  Status = EmmcSendGetAllCid (EmmcMmio);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "EmmcTune: Fail card init at get CID\n"));
    return Status;
  }

  //
  // eMMC doesn't share SD bus with other slots so we address card as slot 0.
  // Indexing is 1-based.
  //
  Status = EmmcSetRca (EmmcMmio, 1);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "EmmcTune: Fail on set RCA\n"));
    return Status;
  }

  Status = EmmcSendGetCsd (EmmcMmio, 1, &Csd);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "EmmcTune: Failed to get CSD\n"));
    return Status;
  }

  if (Csd.SpecVers < 4) {
    DEBUG ((DEBUG_INFO, "EmmcTune: Card version unsupported\n"));
    return EFI_UNSUPPORTED;
  }

  Status = EmmcSelect (EmmcMmio, 1);
  if (EFI_ERROR (Status)) {
    DEBUG((DEBUG_ERROR, "EmmcTune: Failed to select card\n"));
    return Status;
  }

  Status = EmmcSendGetExtCsd (EmmcMmio, &ExtCsd);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "EmmcTune: Failed to get extended CSD register\n"));
    return Status;
  }

  if (!(ExtCsd.DeviceType & BIT6)) {
    DEBUG ((DEBUG_INFO, "EmmcTune: card doesn't support HS400 exit tuning\n"));
    return EFI_UNSUPPORTED;
  }

  return EmmcSwitchToHs400 (EmmcMmio, DriverStrength);
}

/**
  Check if eMMC card is connected to controller.

  @param[in] EmmcMmio  eMMC MMIO address

  @retval TRUE   Card is connected to controller
  @retval FALSE  Card is not connected to controller
**/
STATIC
BOOLEAN
EmmcIsCardConnected (
  IN UINT32  EmmcMmio
  )
{
  if ((MmioRead32 (EmmcMmio + R_SCS_MEM_PSTATE) & BIT16)) {
    return TRUE;
  }
  return FALSE;
}

/**
  Enable eMMC interrupts required for correct block io operation

  @param[in] EmmcMmio  eMMC MMIO address
**/
STATIC
VOID
EmmcEnableInterrupts (
  IN UINT32  EmmcMmio
  )
{
  MmioWrite16 (EmmcMmio + R_SCS_MEM_NINTEN, BIT1 | BIT0);
  MmioWrite16 (EmmcMmio + R_SCS_MEM_ERINTEN, 0xFFFF);
}

/**
  Enable access to integrated eMMC MMIO.

  @param[in] EmmcPciConfig  eMMC PCI config space
  @param[in] EmmcMmio       eMMC MMIO address
**/
VOID
EmmcEnableMmio (
  IN UINT64  EmmcPciConfig,
  IN UINT32  EmmcMmio
  )
{
  //
  // Disable MSE
  //
  PciSegmentAnd16 (EmmcPciConfig + PCI_COMMAND_OFFSET, (UINT16) ~EFI_PCI_COMMAND_MEMORY_SPACE);
  //
  // Write temp address to lower base address
  //
  PciSegmentWrite32 (EmmcPciConfig + PCI_BASE_ADDRESSREG_OFFSET, EmmcMmio);
  //
  // Clear upper base address
  //
  PciSegmentWrite32 (EmmcPciConfig + (PCI_BASE_ADDRESSREG_OFFSET + 4), 0);
  //
  // Enable MSE
  //
  PciSegmentOr16 (EmmcPciConfig + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);
}

/**
  Disable MMIO access to integrated eMMC.

  @param[in] EmmcPciConfig  eMMC PCI config space
**/
VOID
EmmcDisableMmio (
  IN UINT64  EmmcPciConfig
  )
{
  //
  // Disable MSE
  //
  PciSegmentAnd16 (EmmcPciConfig + PCI_COMMAND_OFFSET, (UINT16) ~EFI_PCI_COMMAND_MEMORY_SPACE);
  //
  // Clear lower base address
  //
  PciSegmentWrite32 (EmmcPciConfig + PCI_BASE_ADDRESSREG_OFFSET, 0);
}

/**
  Initializes SD bus of the eMMC controller.

  @param[in] EmmcMmio  eMMC MMIO address

  @return Status of the bus initialization
**/
EFI_STATUS
EmmcInitializeBus (
  IN UINT32  EmmcMmio
  )
{
  EFI_STATUS  Status;

  if (!EmmcIsCardConnected (EmmcMmio)) {
    DEBUG ((DEBUG_INFO, "EmmcTune: No card attached\n"));
    return EFI_NOT_FOUND;
  }

  EmmcEnableInterrupts (EmmcMmio);

  //
  // Set data transfer timeout control. This value is arbitrary.
  //
  MmioWrite8 (EmmcMmio + R_SCS_MEM_TIMEOUT_CTL, 0x0E);

  Status = SetClockFrequency (EmmcMmio, 400000);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "EmmcTune: Failed to set 40KHz clock\n"));
    return Status;
  }

  //
  // Set 1.8V signaling
  //
  MmioWrite8 (EmmcMmio + R_SCS_MEM_PWRCTL, (BIT3 | BIT1 | BIT0));

  return EFI_SUCCESS;
}

