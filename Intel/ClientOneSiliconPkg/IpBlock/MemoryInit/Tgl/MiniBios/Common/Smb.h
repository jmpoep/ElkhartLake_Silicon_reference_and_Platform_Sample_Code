/** @file
  This file contains the Smbus related definitions.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2017 Intel Corporation.

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
#ifndef _Smb_h_
#define _Smb_h_

#define HSTS  (0x00)       // Host Status
#define HCTL  (0x02)       // Host Control
#define HCMD  (0x03)       // Host Command
#define TSA   (0x04)       // Transmit Slave Address
#define HD0   (0x05)       // Host Data
#define HD1   (0x06)       // Host Data
#define HBD   (0x07)       // Host Block Data
#define PEC   (0x08)       // Packet Error Check
#define RSA   (0x09)       // Receive Slave Address
#define SD    (0x0A)       // Slave Data
#define AUXS  (0x0C)       // Auxiliary Status
#define AUXC  (0x0D)       // Auxiliary Control
#define SLPC  (0x0E)       // SM Link Pin Contro
#define SMPC  (0x0F)       // SM Bus Pin Control
#define SSTS  (0x10)       // Slave Status
#define SCMD  (0x11)       // Slave Command
#define NDA   (0x14)       // Notify Device Address
#define NDLB  (0x16)       // Notify Data Low Byte
#define NDHB  (0x17)       // Notify Data High Byte

//
// Host Status bits
//
#define B_PCH_SMBUS_HBSY                  0x01
#define B_PCH_SMBUS_INTR                  0x02
#define B_PCH_SMBUS_DERR                  0x04
#define B_PCH_SMBUS_BERR                  0x08
#define B_PCH_SMBUS_FAIL                  0x10
#define B_PCH_SMBUS_SMBALERT_STS          0x20
#define B_PCH_SMBUS_IUS                   0x40
#define B_PCH_SMBUS_BYTE_DONE_STS         0x80
#define B_PCH_SMBUS_ERROR                 (B_PCH_SMBUS_DERR | B_PCH_SMBUS_BERR | B_PCH_SMBUS_FAIL)
#define B_PCH_SMBUS_HSTS_ALL              0xFF

//
// Host Control bits
//
#define B_PCH_SMBUS_INTREN                0x01
#define B_PCH_SMBUS_KILL                  0x02
#define B_PCH_SMBUS_SMB_CMD               0x1C
#define V_PCH_SMBUS_SMB_CMD_QUICK         0x00
#define V_PCH_SMBUS_SMB_CMD_BYTE          0x04
#define V_PCH_SMBUS_SMB_CMD_BYTE_DATA     0x08
#define V_PCH_SMBUS_SMB_CMD_WORD_DATA     0x0C
#define V_PCH_SMBUS_SMB_CMD_PROCESS_CALL  0x10
#define V_PCH_SMBUS_SMB_CMD_BLOCK         0x14
#define V_PCH_SMBUS_SMB_CMD_IIC_READ      0x18
#define V_PCH_SMBUS_SMB_CMD_BLOCK_PROCESS 0x1C
#define B_PCH_SMBUS_LAST_BYTE             0x20
#define B_PCH_SMBUS_START                 0x40
#define B_PCH_SMBUS_PEC_EN                0x80

//
// Define the Smbus device address.
//
#define SMBUS_PCI_ADDRESS     (0x20)        // SMBUS Base Address Register


//
// Define the Smbus command types.
//

typedef enum {
  sctBYTE      = 0x4,  // 00100 This command uses the transmit slave address and command registers. Bit 0 of the slave address register determines if this is a read or write command.
  sctBYTE_DATA = 0x8,  // 01000 This command uses the transmit slave address, command,and DATA0 registers. Bit 0 of the slave address register determines if this is a read or write command. If it is a read, the DATA0 register will contain the read data.
  sctWORD_DATA = 0xC,  // 01100 This command uses the transmit slave address, command,DATA0 and DATA1 registers. Bit 0 of the slave address register determines if this is a read or write command. If it is a read, after the command completes the DATA0 and DATA1 registers will contain the read data.
} TSmbCommandType;


typedef int RETURN_STATUS;
#define RETURN_SUCCESS (0)
#define RETURN_FAIL    (1)


extern
MrcStatus
SendSmbCmd (
  IN const UINT32           SmbusBaseAddress,
  IN const TSmbCommandType  CmdType,
  IN UINT8                  SlaveAddress,
  IN const UINT8            Command,
  IN OUT UINT8              *Data0,
  IN OUT UINT8              *Data1,
  IN const BOOLEAN          Read
  );

extern
UINT32
GetSmBusBaseAddress (
  void
  );

extern
UINT8
SmBusReadDataByte (
  const UINT32          SmBusAddress,
  RETURN_STATUS * const Status
  );

extern
UINT8
SmBusWriteDataByte (
  const UINT32          SmBusAddress,
  UINT8                 Value,
  RETURN_STATUS * const Status
  );

extern
UINT16
SmBusReadDataWord (
  const UINT32          SmBusAddress,
  RETURN_STATUS * const Status
  );

extern
UINT16
SmBusWriteDataWord (
  const UINT32          SmBusAddress,
  const UINT16          Value,
  RETURN_STATUS * const Status
  );


#endif // _Smb_h_
