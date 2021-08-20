/** @file
  BaseEcHw library implementation.

  This library provides basic Embedded Controller Hardware interface.
  It is keeped simple enough and used by other BaseEc libraries to abstacrt the usage

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:
**/
#include <Library/EcHwLib.h>
#include <Library/EcLib.h>
#include <Library/DebugLib.h>

typedef struct {
  UINT8   CommandNumber;
  UINT8   NumberOfSendData;
  UINT8   NumberOfReceiveData;
  BOOLEAN CommandImplemented;
} EC_COMMAND_TABLE;

EC_COMMAND_TABLE mEcCommand[] = {
  {EC_C_SMI_NOTIFY_ENABLE        , 0, 0, FALSE}, // Enable SMI notifications to the host
  {EC_C_SMI_NOTIFY_DISABLE       , 0, 0, FALSE}, // SMI notifications are disabled and pending notifications cleared
  {EC_C_QUERY_SYS_STATUS         , 0, 1, TRUE},  // Returns 1 byte of information about the system status
  {EC_C_SMC_GET_MODE             , 0, 2, TRUE},  // Command to detect EC
  {EC_C_QUERY_BOARD_ID_BIT       , 0, 1, TRUE},  // Board Id 8 or 16 bit
  {EC_C_FAB_ID                   , 0, 2, TRUE},  // Get the board fab ID in the lower 3 bits
  {EC_C_SET_CHARGING_METHOD      , 1, 0, TRUE},  // Command to specify charging method. (Normal charging or Fast charging (DFCT))
  {EC_C_GET_PMIC_VENDOR_ID       , 0, 1, TRUE}, // Command to detect the Vendor ID of the PMIC
  {EC_C_SLP_S0_VOLTAGE           , 1, 0, TRUE}, // Command to set/reset the bits of register V085ACNT[7:6]
  {EC_C_RESET                    , 0, 0, TRUE},  // EC Reset in Firmware Update Mode
  {EC_C_SYSTEM_POWER_OFF         , 0, 0, TRUE},  // Turn off the system power
  {EC_C_LOW_POWER_ENTRY          , 0, 0, FALSE}, // Enter Low Power Mode
  {EC_C_LOW_POWER_EXIT           , 0, 0, TRUE},  // Exit Low Power Mode
  {EC_C_UPDATE_EC                , 0, 0, TRUE},  // Update Device Power
  {EC_C_PMIC_VOLTAGE             , 2, 0, TRUE},  // Command to set the VCC and VDDQ Voltage Levels
  {EC_C_LAN_ON                   , 0, 0, TRUE},  // Turn on the power to LAN through EC
  {EC_C_LAN_OFF                  , 0, 0, TRUE},  // Turn off the power to LAN through EC
  {EC_C_DIS_PCH_DTS_READ         , 1, 0, TRUE},  // Disable PCH DTS reading
  {EC_C_SET_CTEMP                , 1, 0, TRUE},  // The next byte written to the data port will be the shutdown temperature
  {EC_C_EN_DTEMP                 , 0, 0, FALSE}, // Commands EC to begin reading Thermal Diode and comparing to Critical Temperature
  {EC_C_DIS_DTEMP                , 0, 0, FALSE}, // Commands EC to stop reading Thermal Diode
  {EC_C_PCH_SMBUS_EN             , 0, 0, FALSE}, // EC PCH SMBus thermal monitoring Enable cmd
  {EC_C_PCH_SMBUS_DIS            , 0, 0, FALSE}, // EC PCH SMBus thermal monitoring Disable cmd
  {EC_C_PCH_SMBUS_WRITE_EN       , 0, 0, FALSE}, // EC PCH SMBus Write Enable cmd
  {EC_C_PCH_SMBUS_WRITE_DIS      , 0, 0, FALSE}, // EC PCH SMBus Write Disable cmd
  {EC_C_TS_ON_DIMM_EN            , 0, 0, FALSE}, // TS-on-DIMM thermal monitoring enable command
  {EC_C_TS_ON_DIMM_DIS           , 0, 0, FALSE}, // TS-on-DIMM thermal monitoring disable command
  {EC_C_PCH_SMBUS_MSG_LENGTH     , 0, 0, FALSE}, // PCH SMBus block read buffer length
  {EC_C_PCH_SMBUS_PEC_EN         , 0, 0, FALSE}, // PCH SMBus Packet Error Checking (PEC) Enable command.
  {EC_C_SMI_QUERY                , 0, 1, TRUE},  // The host reads the data port to retrieve the notifications
  {EC_C_SMI_TIMER                , 0, 0, FALSE}, // Commands the EC to generate a periodic SMI to the host
  {EC_C_SMI_HOTKEY               , 0, 1, TRUE},  // Get the scan code of hotkey pressed (CTRL + ALT + SHIFT + key)
  {EC_C_SMBUS_HIGH_SPEED         , 0, 0, FALSE}, // EC SMBus high speed mode command
  {EC_C_PCH_SMBUS_PEC_DIS        , 0, 0, FALSE}, // PCH SMBus Packet Error Checking (PEC) Disable command.
  {EC_C_READ_MEM                 , 1, 1, TRUE},  // Read the EC memory
  {EC_C_WRITE_MEM                , 2, 0, TRUE},  // Write the EC memory
  {EC_C_DOCK_STATUS              , 0, 1, TRUE},  // Get the dock status
  {EC_C_EC_REVISION              , 0, 2, TRUE},  // Get the revision for the EC
  {EC_C_UPDATE_PWM               , 0, 0, TRUE},  // Update the FAN Speed (Update PWM)
  {EC_C_ACPI_ENABLE              , 0, 0, TRUE},  // Enable ACPI mode
  {EC_C_ACPI_DISABLE             , 0, 0, TRUE},  // Disable ACPI mode
  {EC_C_SMI_INJECT               , 0, 0, FALSE}, // The next byte written to the data port will generate an immediate SMI
  {EC_C_SMI_DISABLE              , 0, 0, TRUE},  // SMI generation by the EC is disabled
  {EC_C_SMI_ENABLE               , 0, 0, TRUE},  // SMI generation by the EC is enabled
  {EC_C_USBC_SX_ENTRY_WAIT       , 1, 1, TRUE},  // Send this command from SMM and wait for response
  {EC_C_USBC_SX_EXIT_WAIT        , 0, 1, TRUE},  // Send this command during boot and wait for response
  {EC_C_USBC_IOM_READY_NOTIFY    , 1, 0, TRUE},  // Send this command during boot/resume when IOM is ready
  {EC_C_USBC_GET_USB_CONN_STATUS , 0, 1, TRUE}   // Send this command during boot before USB enumeration and wait for response
};


/**
  Detect EC through LPC interface

  @param[in][out] DataSize    Size of data to send to the EC.
                              If the command retuned data - size of buffer returned by the EC.
                              Be aware of the DataSize must euqal to size of DataBuffer and cannot smaller
                              than number of send data or number of receive data, whichever is the grater.
  @param[in][out] DataBuffer  Pointer to the data buffer including data to be sent to the EC.
                              If the command returned data - pointer to the buffer including the data.
                              The buffer size should be the max of receive and transmit data.

  @retval  EFI_SUCCESS
  @retval  EFI_NOT_FOUND
**/
EFI_STATUS
LpcEcGetModeCommand (
  IN OUT UINT8                 *DataSize,
  IN OUT UINT8                 *DataBuffer
  )
{
  EFI_STATUS Status;
  BOOLEAN    EcPresent;
  UINT8      EcMajorRevision;
  UINT8      EcMinorRevision;

  EcMajorRevision = 0;
  EcMinorRevision = 0;

  EcPresent = DetectEc (&EcMajorRevision, &EcMinorRevision);
  if (EcPresent == TRUE) {
    Status = EFI_SUCCESS;
    *DataSize = 2;
    DataBuffer[0] = EcMajorRevision;
    DataBuffer[1] = EcMinorRevision;
  } else {
    Status = EFI_NOT_FOUND;
    *DataSize = 0;
  }
  return Status;
}


/**
  Send data and command to EcId0

  @param[in]      Command     Command value to send to the EcId0
  @param[in][out] DataSize    Size of data to send to the EcId0.
                              If the command retuned data - size of buffer returned by the EcId0.
                              Be aware of the DataSize must euqal to size of DataBuffer and cannot smaller
                              than number of send data or number of receive data, whichever is the grater.
  @param[in][out] DataBuffer  Pointer to the data buffer including data to be sent to the EcId0.
                              If the command returned data - pointer to the buffer including the data.
                              The buffer size should be the max of receive and transmit data.

  @retval         EFI_SUCCESS Success
  @retval         Other       Failed - EFI_TIMEOUT, EFI_INVALID_PARAMETER, EFI_UNSUPPORTED,
                                       EFI_BUFFER_TOO_SMALL, etc.
**/
EFI_STATUS
EcId0Interface (
  IN UINT8                     Command,
  IN OUT UINT8                 *DataSize,
  IN OUT UINT8                 *DataBuffer
  )
{
  EFI_STATUS Status;
  UINT8      NumberOfEcCommands;
  UINT8      Index;
  UINT8      TxDataIndex;
  UINT8      RxDataIndex;
  UINT8      MaxValue;

  Status = EFI_SUCCESS;

  NumberOfEcCommands = sizeof (mEcCommand) / sizeof (EC_COMMAND_TABLE);

  for (Index = 0; Index < NumberOfEcCommands; Index++) {
    if (Command != mEcCommand[Index].CommandNumber) {
      continue;
    }
    if (mEcCommand[Index].CommandImplemented != TRUE) {
      Status = EFI_UNSUPPORTED;
      break;
    }

    if ((mEcCommand[Index].NumberOfSendData != 0) || (mEcCommand[Index].NumberOfReceiveData != 0)) {
      if (DataSize == NULL || DataBuffer == NULL) {
        Status = EFI_INVALID_PARAMETER;
        break;
      } else {
        MaxValue = MAX (mEcCommand[Index].NumberOfSendData, mEcCommand[Index].NumberOfReceiveData);
        if (*DataSize < MaxValue) {
          Status = EFI_BUFFER_TOO_SMALL;
          *DataSize = MaxValue;
          break;
        }
      }
    }
    if (Command == EC_C_SMC_GET_MODE) {
      ///
      /// Special case
      ///
      Status = LpcEcGetModeCommand (DataSize, DataBuffer);
      break;
    } else {
      Status = SendEcCommand (Command);
      if (EFI_ERROR (Status)) {
        break;
      }
      if (mEcCommand[Index].NumberOfSendData != 0) {
       for (TxDataIndex = 0; TxDataIndex < mEcCommand[Index].NumberOfSendData; TxDataIndex++) {
          Status = SendEcData (DataBuffer[TxDataIndex]);
          if (EFI_ERROR (Status)) {
            break;
          }
        }
      }
      if (mEcCommand[Index].NumberOfReceiveData != 0) {
        for (RxDataIndex = 0; RxDataIndex < mEcCommand[Index].NumberOfReceiveData; RxDataIndex++) {
          Status = ReceiveEcData (&DataBuffer[RxDataIndex]);
          if (EFI_ERROR (Status)) {
            break;
          }
          *DataSize = RxDataIndex + 1;
        }
      }
    }
    break;
  }
  return Status;
}
