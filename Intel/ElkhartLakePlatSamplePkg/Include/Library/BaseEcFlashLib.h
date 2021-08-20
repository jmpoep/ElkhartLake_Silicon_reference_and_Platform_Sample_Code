/** @file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2016 Intel Corporation.

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

#ifndef _EC_FLASH_H_
#define _EC_FLASH_H_

#define IMAGE_SIGNATURE    0x2202L  // Flash image signature (EC) offset.
#define IMAGE_VERSION_NUM  0x106L   // Flash image version number offset.
#define IMAGE_SIZE_OFFSET  0x140L   // Flash image size is stored here.
#define PLAT_SIG_OFFSET    0x142L   // 8 byte platform signature stored here.
#define IMAGE_ECFW1_OFFSET 0x20000L // Offset of ECFW Image 1
#define IMAGE_ECFW2_OFFSET 0x1000L  // Offset of ECFW Image 2(Recovery)

#define UPDATE_FULL        0x0      // update SPIHeader + ECFW1 + ECFW2
#define UPDATE_ECFW1       0x1      // update ECFW1
#define UPDATE_ECFW1_ECFW2 0x2      // update ECFW1 + ECFW2

#define TOTAL_BLKS         0x448   // Total number of 128 byte blocks.

#define FBLOCK_SIZE        128L    // Flash line size
#define ECCOMMANDPORT      0x66    // Using EC ports for flashing.
#define ECSTATUSPORT       0x66
#define ECDATAPORT         0x62

//
// EC FLASH COMMANDS:
//
#define FLASHLOADER        0x91    // Command for FLASH reprogram mode.
#define NMIDISABLE         0x93    // Command for H8 NMI Disable.

#define INITERASE          0x01    // Load erase code into RAM and initialize
#define SETERASEBLKNUM     0x02    // Set block num for erase.
#define ERASEFLASHBLK      0x03    // Erase flash block.
#define BLANKCHECK         0x04    // Blank check the part.
#define INITPROGCODE       0x05    // Initialize programming code.
#define LOADFLASHBLK       0x06    // Load flash block for programming.
#define SETFLASHWRITEADDR  0x07    // Set starting address for writes.
#define PROGRAMFLASHBLK    0x08    // Program flash block.
#define VERIFYFLASHBLK     0x09    // Verify flash block.
#define ERASEFLASH         0x0A    // Erase entire flash.
#define RESETEC            0x0B    // Controller hard reset.
#define READFLASHBYTE      0x0C    // Read a byte at address
#define READBLOCK          0x0D    // Read a block at address

//
// EC RUNTIME COMMANDS:
//
#define READBYTE           0x01    // Read byte
#define WRITEBYTE          0x02    // Write byte
#define GETSWITCHSTATUS    0x0A    // Get switch status
#define ENABLE_POWER_BTN   0x23    // Disable power button functionality
#define DISABLE_POWER_BTN  0x24    // Enable power button functionality
#define READECREVISION     0x90    // Read EC firmware revision number.
#define READECMEM          0x80    // Read the EC memory
#define QUERYSYSSTATUS     0x06    // Returns 1 byte of information about the system status
#define   SYS_STATUS_FAN   0x40    // Fan status (1 = ON)
#define   SYS_STATUS_DOCK  0x20    // Dock status (1 = Docked)
#define   SYS_STATUS_AC    0x10    // AC power (1 = AC powered)
#define   SYS_STATUS_THER  0x0F    // CPU thermal state (0 ~ 9)

#define PLATFORM_UNKNOWN   0xFF    // Unknown platform

#define m_CR          0x0D
#define m_LF          0x0A

#define PCIINDEX        0xCF8
#define PCIDATA         0xCFC
#define ICH_DEVNUM      0x1F
#define ICH_GPIO_BAR    0x58
#define FN0             0x00
#define NMIGPIO_REG     0x38
#define NMIGPIO_BIT     0x01
#define DEVINQSIZE      0x32
#define RMCMDSTRUCTSIZE 128+32
#define BBLKSIZE_OFFSET 0x50      // Offset of boot block size in image
#define EC_SEGMENT      8*1024L
#define TMKBC_SEGMENT   72*1024L
#define ECSEGSIZE_OFFSET   8768L      // 8*1024 + 240h
#define PORT1 0x3F8
#define EC_TIME_OUT        0x50000
#define EC_STALL_TIME_OUT  100
#define EC_S_OBF           BIT0
#define EC_S_IBF           BIT1

/// Note that capacity and voltage are 16 bit values, thus you need to read them from
/// ACPI space with two reads (little Endian).
#define EC_VIRTUAL_BAT_STATUS             48    ///< Status of the virtual battery (present)
#define EC_VIRTUAL_BAT_PRESENT_MASK       0x10  ///< Bit 4 is the indicator

#define EC_REAL_BAT1_STATUS               50    ///< Status of the first real battery (present, charging)
#define EC_REAL_BAT1_REMAINING_PERCENT    52    ///< Remaining capacity in percentage
#define EC_REAL_BAT1_REMAINING_CAPACITY   89    ///< Remaining capacity in mWh
#define EC_REAL_BAT1_RESOLUTION_VOLTAGE   93    ///< Full resolution voltage in mV

#define EC_REAL_BAT2_STATUS               54    ///< Status of the second real battery (present, charging)
#define EC_REAL_BAT2_REMAINING_PERCENT    56    ///< Remaining capacity in percentage
#define EC_REAL_BAT2_REMAINING_CAPACITY   99    ///< Remaining capacity in mWh
#define EC_REAL_BAT2_RESOLUTION_VOLTAGE   103   ///< Full resolution voltage in mV

#define EC_REAL_BAT_PRESENT_MASK          0x8   ///< Bit 3 is the indicator
#define EC_REAL_BAT_CHARGING_MASK         0x1   ///< Bit 1 is the indicator

//
//  Function prototypes
//
VOID   WaitInputBufferEmpty(VOID);
VOID   WaitOutputBufferFull(VOID);
UINT32 EraseFlashBlock(UINT32 BlkNum);
UINT32 WriteFlashBlock(UINT32 *FBufPtr);
UINT32 ComputeBuffChksum(UINT32 *BufPtr, UINT32 BufSize);
void   SendEcCommand(UINT32 CmdNum);
void   SendEcData(UINT32 Data);
UINT32 ReceiveEcData(void);
UINT32 NmiActive(void);
void   Port80(UINT32);
void   EcReset(void);
VOID   ReadEcRegister(UINT8 Reg, UINT8 *RetValue);

EFI_STATUS EcFlash(UINT8* pFcntrlBin, UINT32 FcntrlBinSize, UINT8* pEcBin, UINT32 EcBinSize);
BOOLEAN    IsEcVersionIdentical (UINT8* pEcBin);

//
//  Globals
//
UINT32  FlashBuf[FBLOCK_SIZE];
UINT32  *FlashBufPtr;
UINT32  FBlkStartAddr;//ulong
UINT32  FlashBlock;
UINT32  ImageLen;
UINT32  ImageVer;
UINT64  FcntrlLen;  //ulong
UINT64  FecSize;
UINT32  FcntrlLenLow;
UINT32  FcntrlLenHigh;
CHAR16  Buff[16];
CHAR16* ptBuff;
CHAR16  PlatformID[9];

UINT32  DevInquirySize;
UINT32  DevInquiryBuff[DEVINQSIZE];
UINT32* DevInqBuffPtr;
UINT32  RMDevCode[4];
CHAR16  RMProdName[10];
UINT32  RMCmdStruct[RMCMDSTRUCTSIZE];

#define EFI_PROPER_VERSION(MajorVer, MinorVer)  (gBS->Hdr.Revision >= (MajorVer << 16 | MinorVer))

#endif
