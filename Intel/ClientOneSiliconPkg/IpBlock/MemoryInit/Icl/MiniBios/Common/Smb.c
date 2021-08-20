/** @file
  This file contains the Smbus related functions.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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
#include "MrcApi.h"
#include "MrcOemPlatform.h"
#include "Smb.h"
#include "Register\PchRegsSmbus.h"

MrcStatus
SendSmbCmd (
  IN const UINT32           SmbusBaseAddress,
  IN const TSmbCommandType  CmdType,
  IN UINT8                  SlaveAddress,
  IN const UINT8            Command,
  IN OUT UINT8              *Data0,
  IN OUT UINT8              *Data1,
  IN const BOOLEAN          Read
  )
/**

Routine Description:

  This function performs a Smbus command.

Arguments:

  SmbusBaseAddress    - include smbus device address.
  CmdType             - command type
  SlaveAddress        - slave address
  Command             - command register value.
  Data0               - Data0 register value. this register include the read value in case or read command.
  Data1               - Data1 register value. this register include the read value in case or read command.
  Read                - if true the command is read.

Returns:

  mrcSuccess or failure indication.

**/
{
  MrcStatus Status;
  UINT8     HostStatus;
  UINT8     Control;

  Status  = mrcSuccess;
  Control =  (UINT8) (CmdType | MRC_BIT6); // prepare command register value.
  do {

    // Wait for HSTS.HBSY to be clear
    do {
      HostStatus = MrcOemInPort8 ((UINT16) (SmbusBaseAddress + HSTS));
    } while ((HostStatus & MRC_BIT0) != 0);

    // Clear all status bits
    MrcOemOutPort8 ((UINT16) (SmbusBaseAddress + HSTS), 0xFE);

    // Set the slave command
    MrcOemOutPort8 ((UINT16) (SmbusBaseAddress + HCMD), Command);

    // Set the slave address
    if (Read == TRUE) {
      SlaveAddress |= MRC_BIT0;
    }
    MrcOemOutPort8 ((UINT16) (SmbusBaseAddress + TSA), SlaveAddress);
    // Set the data 0
    if (Data0 != NULL) {
      MrcOemOutPort8 ((UINT16) (SmbusBaseAddress + HD0), *Data0);
    }
    // Set the data 1
    if (Data1 != NULL) {
      MrcOemOutPort8 ((UINT16) (SmbusBaseAddress + HD1), *Data1);
    }

    // Set "Read Byte" protocol and start bit
    MrcOemOutPort8 ((UINT16) (SmbusBaseAddress + HCTL), Control);

    // Poll until any of FAIL, BERR, DERR, INTR
    do {
      HostStatus = MrcOemInPort8 ((UINT16) (SmbusBaseAddress + HSTS));
    } while ((HostStatus & (MRC_BIT4 | MRC_BIT3 | MRC_BIT2 | MRC_BIT1)) == 0);

  } while ((HostStatus & MRC_BIT3) != 0); // SMBus collision? Try again

  if ((HostStatus & (MRC_BIT4 | MRC_BIT2)) != 0) {
      Status = mrcFail;
  } else {
    if (Read == TRUE) {
      if (Data0 == NULL) { // Avoiding NULL pointer
        return mrcFail;
      }
      // Host Data Register read
      *Data0 = MrcOemInPort8 ((UINT16) (SmbusBaseAddress + HD0));
      // if 16 bits command read the data1 also.
      if (CmdType == sctWORD_DATA) {
        if(Data1 == NULL) { // Avoiding NULL pointer
          return mrcFail;
        }
        *Data1 = MrcOemInPort8 ((UINT16) (SmbusBaseAddress + HD1));
      }
    }
  }

  // Clear all status bits
  MrcOemOutPort8 ((UINT16) (SmbusBaseAddress + HSTS), 0xFE);
  return Status;
}

UINT32
GetSmBusBaseAddress (
  void
  )
/**

Routine Description:

  This function gets the Smbus controller base address.

Arguments:
  None.

Returns:

  The Smbus controller base address.

**/
{
  UINT32 SmbusBaseAddress;

  MrcOemOutPort32 (MrcOemPciIndex (), GetPciDeviceAddress (0, PCI_DEVICE_NUMBER_PCH_SMBUS, PCI_FUNCTION_NUMBER_PCH_SMBUS, SMBUS_PCI_ADDRESS));
  SmbusBaseAddress = MrcOemInPort32 (MrcOemPciData ());
  if ((SmbusBaseAddress & MRC_BIT0) == MRC_BIT0) {
    SmbusBaseAddress &= (~MRC_BIT0);
  } else {
    SmbusBaseAddress = 0;
  }
  return SmbusBaseAddress;
}

UINT8
SmBusReadDataByte (
  const UINT32          SmBusAddress,
  RETURN_STATUS * const Status
  )
/**

Routine Description:

  This function gets the Smbus's device data byte.

Arguments:
  SmBusAddress - The Smbus device address and command.
  Status       - Return status.

Returns:

  The Smbus's device data byte.

**/
{
  MrcStatus RetVal;
  UINT32    SmbusBaseAddress;
  UINT8     Value;
  UINT8     SlaveAddress;
  UINT8     Command;

  SmbusBaseAddress = GetSmBusBaseAddress ();
  SlaveAddress     = (UINT8) SmBusAddress;
  Command          = (UINT8) (SmBusAddress >> 8);
  RetVal           = SendSmbCmd (SmbusBaseAddress, sctBYTE_DATA, SlaveAddress, Command, &Value, NULL, TRUE);
  *Status          = ((mrcSuccess == RetVal) ? RETURN_SUCCESS : RETURN_FAIL);
  return Value;
}

UINT8
SmBusWriteDataByte (
  const UINT32          SmBusAddress,
  UINT8                 Value,
  RETURN_STATUS * const Status
  )
/**

Routine Description:

  This function writes the Smbus's device data word.

Arguments:
  SmBusAddress - The Smbus device address and command.
  Status       - Return status.

Returns:

  The Smbus's device data word.

**/
{
  MrcStatus RetVal;
  UINT32    SmbusBaseAddress;
  UINT8     SlaveAddress;
  UINT8     Command;

  SmbusBaseAddress = GetSmBusBaseAddress ();
  SlaveAddress     = (UINT8) SmBusAddress;
  Command          = (UINT8) (SmBusAddress >> 8);
  RetVal           = SendSmbCmd (SmbusBaseAddress, sctBYTE_DATA, SlaveAddress, Command, &Value, NULL, FALSE);
  *Status          = ((mrcSuccess == RetVal) ? RETURN_SUCCESS : RETURN_FAIL);
  return Value;
}

UINT16
SmBusReadDataWord (
  const UINT32          SmBusAddress,
  RETURN_STATUS * const Status
  )
/**

Routine Description:

  This function gets the Smbus's device data word.

Arguments:
  SmBusAddress - The Smbus device address and command.
  Status       - Return status.

Returns:

  The Smbus's device data word.

**/
{
  MrcStatus RetVal;
  UINT32    SmbusBaseAddress;
  UINT8     SlaveAddress;
  UINT8     Command;
  union {
    UINT16 Word;
    struct {
      UINT8  Low;
      UINT8  High;
    } Byte;
  } Value;

  SmbusBaseAddress = GetSmBusBaseAddress ();
  SlaveAddress     = (UINT8) SmBusAddress;
  Command          = (UINT8) (SmBusAddress >> 8);
  RetVal           = SendSmbCmd (SmbusBaseAddress, sctWORD_DATA, SlaveAddress, Command, &Value.Byte.Low, &Value.Byte.High, TRUE);
  *Status          = ((mrcSuccess == RetVal) ? RETURN_SUCCESS : RETURN_FAIL);
  return Value.Word;
}

UINT16
SmBusWriteDataWord (
  const UINT32          SmBusAddress,
  const UINT16          Value,
  RETURN_STATUS * const Status
  )
/**

Routine Description:

  This function writes the Smbus's device data word.

Arguments:
  SmBusAddress - The Smbus device address and command.
  Status       - Return status.

Returns:

  The Smbus's device data word.

**/
{
  MrcStatus RetVal;
  UINT32    SmbusBaseAddress;
  UINT8     SlaveAddress;
  UINT8     Command;

  SmbusBaseAddress = GetSmBusBaseAddress ();
  SlaveAddress     = (UINT8) SmBusAddress;
  Command          = (UINT8) (SmBusAddress >> 8);
  RetVal           = SendSmbCmd (SmbusBaseAddress, sctWORD_DATA, SlaveAddress, Command, (UINT8 *) &Value, (((UINT8 *) &Value) + 1), FALSE);
  *Status          = ((mrcSuccess == RetVal) ? RETURN_SUCCESS : RETURN_FAIL);
  return Value;
}

