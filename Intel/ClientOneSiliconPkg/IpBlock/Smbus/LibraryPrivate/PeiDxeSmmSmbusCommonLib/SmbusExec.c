/** @file
  PCH Smbus Executive Code (common PEI/DXE/SMM code)

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
#include <Uefi/UefiBaseType.h>
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <IndustryStandard/SmBus.h>
#include <Library/PciSegmentLib.h>
#include <Library/SmbusLib.h>
#include <IndustryStandard/Pci30.h>
#include <Register/PchRegs.h>
#include <Register/SmbusRegs.h>

/**
  Get SMBUS IO Base address

  @retval UINT32                  The SMBUS IO Base Address
**/
static
UINT16
SmbusGetIoBase (
  VOID
  )
{
  UINT16  SmbusIoBase;

  SmbusIoBase = (UINT16)PciSegmentRead32 (
                          PCI_SEGMENT_LIB_ADDRESS (
                            DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                            DEFAULT_PCI_BUS_NUMBER_PCH,
                            PCI_DEVICE_NUMBER_PCH_SMBUS,
                            PCI_FUNCTION_NUMBER_PCH_SMBUS,
                            R_SMBUS_CFG_BASE
                            )
                          ) & B_SMBUS_CFG_BASE_BAR;

  ASSERT (SmbusIoBase != B_SMBUS_CFG_BASE_BAR && SmbusIoBase != 0);

  return SmbusIoBase;
}

/**
  This function provides a standard way to read PCH Smbus IO registers.

  @param[in] Offset               Register offset from Smbus base IO address.

  @retval UINT8                   Returns data read from IO.
**/
UINT8
SmbusIoRead (
  IN      UINT8           Offset
  )
{
  return IoRead8 (SmbusGetIoBase () + Offset);
}

/**
  This function provides a standard way to write PCH Smbus IO registers.

  @param[in] Offset               Register offset from Smbus base IO address.
  @param[in] Data                 Data to write to register.

**/
VOID
SmbusIoWrite (
  IN      UINT8           Offset,
  IN      UINT8           Data
  )
{
  //
  // Write New Value
  //
  IoWrite8 (SmbusGetIoBase () + Offset, Data);
  return;
}

/**
  This function provides a standard way to execute Smbus protocols
  as defined in the SMBus Specification. The data can either be of
  the Length byte, word, or a block of data. The resulting transaction will be
  either the SMBus Slave Device accepts this transaction or this function
  returns with an error

  @param[in] SlaveAddress         Smbus Slave device the command is directed at
  @param[in] Command              Slave Device dependent
  @param[in] Operation            Which SMBus protocol will be used
  @param[in] PecCheck             Defines if Packet Error Code Checking is to be used
  @param[in, out] Length          How many bytes to read. Must be 0 <= Length <= 32 depending on Operation
                                  It will contain the actual number of bytes read/written.
  @param[in, out] Buffer          Contain the data read/written.

  @retval EFI_SUCCESS             The operation completed successfully.
  @exception EFI_UNSUPPORTED      The operation is unsupported.

  @retval EFI_INVALID_PARAMETER   Length or Buffer is NULL for any operation besides
                                  quick read or quick write.
  @retval EFI_TIMEOUT             The transaction did not complete within an internally
                                  specified timeout period, or the controller is not
                                  available for use.
  @retval EFI_DEVICE_ERROR        There was an Smbus error (NACK) during the operation.
                                  This could indicate the slave device is not present
                                  or is in a hung condition.
**/
EFI_STATUS
SmbusExec (
  IN      EFI_SMBUS_DEVICE_ADDRESS  SlaveAddress,
  IN      EFI_SMBUS_DEVICE_COMMAND  Command,
  IN      EFI_SMBUS_OPERATION       Operation,
  IN      BOOLEAN                   PecCheck,
  IN OUT  UINTN                     *Length,
  IN OUT  VOID                      *Buffer
  )
{
  RETURN_STATUS ReturnStatus;
  UINT8         *ByteBuffer;
  UINT16        *WordBuffer;

  ReturnStatus = RETURN_SUCCESS;
  ByteBuffer   = (UINT8 *)Buffer;
  WordBuffer   = (UINT16 *)Buffer;

  //
  // For any operations besides quick read & write, the pointers to
  // Length and Buffer must not be NULL.
  //
  if ((Operation != EfiSmbusQuickRead) && (Operation != EfiSmbusQuickWrite)) {
    if ((Length == NULL) || (Buffer == NULL)) {
      return EFI_INVALID_PARAMETER;
    }
  }

  switch (Operation) {
    case EfiSmbusQuickRead:
      SmBusQuickRead (
        SMBUS_LIB_ADDRESS (SlaveAddress.SmbusDeviceAddress, Command, 0, PecCheck),
        &ReturnStatus
        );
      break;
    case EfiSmbusQuickWrite:
      SmBusQuickWrite (
        SMBUS_LIB_ADDRESS (SlaveAddress.SmbusDeviceAddress, Command, 0, PecCheck),
        &ReturnStatus
        );
      break;
    case EfiSmbusReceiveByte:
      if (*Length < 1) {
        return EFI_BUFFER_TOO_SMALL;
      }
      *Length = 1;
      ByteBuffer[0] = SmBusReceiveByte (
                        SMBUS_LIB_ADDRESS (SlaveAddress.SmbusDeviceAddress, Command, 0, PecCheck),
                        &ReturnStatus
                        );
      break;
    case EfiSmbusSendByte:
      if (*Length < 1) {
        return EFI_BUFFER_TOO_SMALL;
      }
      *Length = 1;
      ByteBuffer[0] = SmBusSendByte (
                        SMBUS_LIB_ADDRESS (SlaveAddress.SmbusDeviceAddress, Command, 0, PecCheck),
                        ByteBuffer[0],
                        &ReturnStatus
                        );
      break;
    case EfiSmbusReadByte:
      if (*Length < 1) {
        return EFI_BUFFER_TOO_SMALL;
      }
      *Length = 1;
      ByteBuffer[0] = SmBusReadDataByte (
                        SMBUS_LIB_ADDRESS (SlaveAddress.SmbusDeviceAddress, Command, 0, PecCheck),
                        &ReturnStatus
                        );
      break;
    case EfiSmbusWriteByte:
      if (*Length < 1) {
        return EFI_BUFFER_TOO_SMALL;
      }
      *Length = 1;
      ByteBuffer[0] = SmBusWriteDataByte (
                        SMBUS_LIB_ADDRESS (SlaveAddress.SmbusDeviceAddress, Command, 0, PecCheck),
                        ByteBuffer[0],
                        &ReturnStatus
                        );
      break;
    case EfiSmbusReadWord:
      if (*Length < 2) {
        return EFI_BUFFER_TOO_SMALL;
      }
      *Length = 2;
      WordBuffer[0] = SmBusReadDataWord (
                        SMBUS_LIB_ADDRESS (SlaveAddress.SmbusDeviceAddress, Command, 0, PecCheck),
                        &ReturnStatus
                        );
      break;
    case EfiSmbusWriteWord:
      if (*Length < 2) {
        return EFI_BUFFER_TOO_SMALL;
      }
      *Length = 2;
      WordBuffer[0] = SmBusWriteDataWord (
                        SMBUS_LIB_ADDRESS (SlaveAddress.SmbusDeviceAddress, Command, 0, PecCheck),
                        WordBuffer[0],
                        &ReturnStatus
                        );
      break;
    case EfiSmbusReadBlock:
      *Length = SmBusReadBlock (
                  SMBUS_LIB_ADDRESS (SlaveAddress.SmbusDeviceAddress, Command, 0, PecCheck),
                  Buffer,
                  &ReturnStatus
                  );
      break;
    case EfiSmbusWriteBlock:
      *Length = SmBusWriteBlock (
                  SMBUS_LIB_ADDRESS (SlaveAddress.SmbusDeviceAddress, Command, *Length, PecCheck),
                  Buffer,
                  &ReturnStatus
                  );
      break;
    case EfiSmbusProcessCall:
      if (*Length < 2) {
        return EFI_BUFFER_TOO_SMALL;
      }
      *Length = 2;
      WordBuffer[0] = SmBusProcessCall (
                        SMBUS_LIB_ADDRESS (SlaveAddress.SmbusDeviceAddress, Command, 0, PecCheck),
                        WordBuffer[0],
                        &ReturnStatus
                        );
      break;
    case EfiSmbusBWBRProcessCall:
      *Length = SmBusBlockProcessCall (
                  SMBUS_LIB_ADDRESS (SlaveAddress.SmbusDeviceAddress, Command, *Length, PecCheck),
                  Buffer,
                  Buffer,
                  &ReturnStatus
                  );
      break;
    default:
      return EFI_INVALID_PARAMETER;
      break;
  }

  return (EFI_STATUS) ReturnStatus;
}

/**
  This function initializes the Smbus Registers.

**/
VOID
InitializeSmbusRegisters (
  VOID
  )
{
  UINT64 SmbusRegBase;

  SmbusRegBase = PCI_SEGMENT_LIB_ADDRESS (
                   DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                   DEFAULT_PCI_BUS_NUMBER_PCH,
                   PCI_DEVICE_NUMBER_PCH_SMBUS,
                   PCI_FUNCTION_NUMBER_PCH_SMBUS,
                   0
                   );
  //
  // Enable the Smbus I/O Enable
  //
  PciSegmentOr8 (SmbusRegBase + PCI_COMMAND_OFFSET, (UINT8) EFI_PCI_COMMAND_IO_SPACE);

  //
  // Enable the Smbus host controller
  //
  PciSegmentAndThenOr8 (
    SmbusRegBase + R_SMBUS_CFG_HOSTC,
    (UINT8) (~(B_SMBUS_CFG_HOSTC_SMI_EN | B_SMBUS_CFG_HOSTC_I2C_EN)),
    B_SMBUS_CFG_HOSTC_HST_EN
    );

  SmbusIoWrite (R_SMBUS_IO_HSTS, B_SMBUS_IO_HSTS_ALL);
}