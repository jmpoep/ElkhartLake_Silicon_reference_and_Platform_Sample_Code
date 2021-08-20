/** @file
  @todo ADD DESCRIPTION

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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

#ifndef EC_COMMANDS_H_
#define EC_COMMANDS_H_

//
// Timeout if EC command/data fails
//
#define EC_TIME_OUT        0x20000

//
// The EC implements an embedded controller interface at ports 0x60/0x64 and a ACPI compliant
// system management controller at ports 0x62/0x66. Port 0x66 is the command and status port,
// port 0x62 is the data port.
//
#define EC_D_PORT        0x62
#define EC_C_PORT        0x66

//
// Status Port 0x62
//
#define EC_S_OVR_TMP     0x80    // Current CPU temperature exceeds the threshold
#define EC_S_SMI_EVT     0x40    // SMI event is pending
#define EC_S_SCI_EVT     0x20    // SCI event is pending
#define EC_S_BURST       0x10    // EC is in burst mode or normal mode
#define EC_S_CMD         0x08    // Byte in data register is command/data
#define EC_S_IGN         0x04    // Ignored
#define EC_S_IBF         0x02    // Input buffer is full/empty
#define EC_S_OBF         0x01    // Output buffer is full/empty

//
// EC commands that are issued to the EC through the command port (0x66).
// New commands and command parameters should only be written by the host when IBF=0.
// Data read from the EC data port is valid only when OBF=1.
//
#define EC_C_SMI_NOTIFY_ENABLE         0x04    // Enable SMI notifications to the host
#define EC_C_SMI_NOTIFY_DISABLE        0x05    // SMI notifications are disabled and pending notifications cleared
#define EC_C_QUERY_SYS_STATUS          0x06    // Returns 1 byte of information about the system status
#define EC_C_QUERY_BOARD_ID_BIT        0x0A    // Board Id 8 or 16 bit
#define EC_C_SMC_GET_MODE              0x09    // Command to detect EC
#define EC_C_RESET                     0x0B    // EC reset
#define EC_C_FAB_ID                    0x0D    // Get the board fab ID in the lower 3 bits
#define EC_C_SET_CHARGING_METHOD       0x13    // Command to specify charging method. (Normal charging or Fast charging (DFCT))
#define EC_C_GET_PMIC_VENDOR_ID        0x1B    // Command to detect the Vendor ID of the PMIC
#define EC_C_SLP_S0_VOLTAGE            0x1C    // Command to set/reset the bits of register V085ACNT[7:6]
#define EC_C_SYSTEM_POWER_OFF          0x22    // Turn off the system power
#define EC_C_ENABLE_POWER_BTN          0x23    // Disable power button functionality
#define EC_C_DISABLE_POWER_BTN         0x24    // Enable power button functionality
#define EC_C_LOW_POWER_ENTRY           0x2C    // Enter Low Power Mode
#define EC_C_LOW_POWER_EXIT            0x2D    // Exit Low Power Mode
#define EC_C_UPDATE_EC                 0x2E    // Update Device Power
#define EC_C_PMIC_VOLTAGE              0x2F    // Command to set the VCC and VDDQ Voltage Levels
#define EC_C_LAN_ON                    0x46    // Turn on the power to LAN through EC
#define EC_C_LAN_OFF                   0x47    // Turn off the power to LAN through EC
#define EC_C_DIS_PCH_DTS_READ          0x4E    // Disable PCH DTS reading
#define EC_C_SET_CTEMP                 0x58    // The next byte written to the data port will be the shutdown temperature
#define EC_C_EN_DTEMP                  0x5E    // Commands EC to begin reading Thermal Diode and comparing to Critical Temperature
#define EC_C_DIS_DTEMP                 0x5F    // Commands EC to stop reading Thermal Diode
#define EC_C_PCH_SMBUS_EN              0x60    // EC PCH SMBus thermal monitoring Enable cmd
#define EC_C_PCH_SMBUS_DIS             0x61    // EC PCH SMBus thermal monitoring Disable cmd
#define EC_C_PCH_SMBUS_WRITE_EN        0x68    // EC PCH SMBus Write Enable cmd
#define EC_C_PCH_SMBUS_WRITE_DIS       0x69    // EC PCH SMBus Write Disable cmd
#define EC_C_TS_ON_DIMM_EN             0x6B    // TS-on-DIMM thermal monitoring enable command
#define EC_C_TS_ON_DIMM_DIS            0x6C    // TS-on-DIMM thermal monitoring disable command
#define EC_C_PCH_SMBUS_MSG_LENGTH      0x6D    // PCH SMBus block read buffer length
#define EC_C_PCH_SMBUS_PEC_EN          0x6E    // PCH SMBus Packet Error Checking (PEC) Enable command.
#define EC_C_PCH_SMBUS_PEC_DIS         0x76    // PCH SMBus Packet Error Checking (PEC) Disable command.
#define EC_C_SMBUS_HIGH_SPEED          0x75    // EC SMBus high speed mode command
#define EC_C_SMI_QUERY                 0x70    // The host reads the data port to retrieve the notifications
#define EC_C_SMI_TIMER                 0x71    // Commands the EC to generate a periodic SMI to the host
#define EC_C_SMI_HOTKEY                0x72    // Get the scan code of hotkey pressed (CTRL + ALT + SHIFT + key)
#define EC_C_READ_MEM                  0x80    // Read the EC memory
#define EC_C_WRITE_MEM                 0x81    // Write the EC memory
#define EC_C_DOCK_STATUS               0x8A    // Get the dock status
#define EC_C_EC_REVISION               0x90    // Get the revision for the EC
#define EC_C_UPDATE_PWM                0x1A    // Update the FAN Speed
#define EC_C_ACPI_ENABLE               0xAA    // Enable ACPI mode
#define EC_C_ACPI_DISABLE              0xAB    // Disable ACPI mode
#define EC_C_SMI_INJECT                0xBA    // The next byte written to the data port will generate an immediate SMI
#define EC_C_SMI_DISABLE               0xBC    // SMI generation by the EC is disabled
#define EC_C_SMI_ENABLE                0xBD    // SMI generation by the EC is enabled
#define EC_C_USBC_SX_ENTRY_WAIT        0xE2    // Send this command from SMM and wait for response
#define EC_C_USBC_SX_EXIT_WAIT         0xE3    // Send this command during boot and wait for response
#define EC_C_USBC_IOM_READY_NOTIFY     0xE4    // Send this command during boot/resume when IOM is ready
#define EC_C_USBC_GET_USB_CONN_STATUS  0xE5    // Send this command during boot before USB enumeration and wait for response
#define EC_C_SET_G3TOS5                0xF3    // Set KSC Misc Flags BIT0(G3ToS5)
#define EC_C_USBC_PD_STATUS            0xFF    // Get PD status from EC RAM

//
// @todo Those definitions need to be reviewed and cleaned up.
//
#define EC_B_BOARD_ID                  0x0F    // Board ID = [3:0]
#define EC_B_BOARD_ID_BIT_16           0x80    // Bit7 = 1 means 16 bit implementation
#define EC_B_SYS_STATUS_AC             0x10    // AC power status (Bit 4 = 1, AC powered)
#define EC_B_SYS_STATUS_THERMAL        0x0F    // CPU thermal state (0 ~ 9)
#define EC_B_SYS_STATUS_FAN            0x40    // Fan status (Bit 6 = 1, Fan on)
#define EC_B_LID_STATUS_OPEN           0x40    // Lid status (Bit 6 = 1, Lid open)
#define EC_B_SYS_STATUS_DOCK           0x20    // Dock status (Bit 5 = 1, Docked)
#define EC_B_DOCK_STATUS_ATTACH        0x01    // Dock status (Bit 0 = 1, Attach)

#define EC_D_LID_STATE                 0x03    // Get Lid State (EC RAM offset 0x03 bit6)
#define EC_D_FORCE_RESET               0x78    // Enable/Disable ForceResetAfterAcRemoval (EC RAM offset 0x78 bit2)
#define EC_D_TEN_SEC_MODE              0x78    // Enable/Disable 10sec Power button Override (EC RAM offset 0x78 bit1)
#define EC_D_SATA2_POWER               0xC8    // Enable/Disable SATA port2 power (EC RAM offset 0xC8 bit0)
#define EC_D_NORMAL_CHARGING           0x01    // Select normal charging method
#define EC_D_FAST_CHARGING             0x02    // Select fast charging (DFCT) method

//
// EC commands that are only valid if the EC has ACPI mode enabled.
// Note that capacity and voltage are 16 bit values, thus you need to read them from
// ACPI space with two reads (little Endian).
//
#define EC_VIRTUAL_BAT_STATUS                48      // Status of the virtual battery (present)
#define EC_VIRTUAL_BAT_PRESENT_MASK          0x10    // Bit 4 is the indicator

#define EC_REAL_BAT1_STATUS                  50      // Status of the first real battery (present, charging)
#define EC_REAL_BAT1_REMAINING_PERCENT       52      // Remaining capacity in percentage
#define EC_REAL_BAT1_REMAINING_CAPACITY      89      // Remaining capacity in mWh
#define EC_REAL_BAT1_RESOLUTION_VOLTAGE      93      // Full resolution voltage in mV

#define EC_REAL_BAT2_STATUS                  54      // Status of the second real battery (present, charging)
#define EC_REAL_BAT2_REMAINING_PERCENT       56      // Remaining capacity in percentage
#define EC_REAL_BAT2_REMAINING_CAPACITY      99      // Remaining capacity in mWh
#define EC_REAL_BAT2_RESOLUTION_VOLTAGE      103     // Full resolution voltage in mV

#define EC_REAL_BAT_PRESENT_MASK             0x8     // Bit 3 is the indicator
#define EC_REAL_BAT_CHARGING_MASK            0x1     // Bit 1 is the indicator

//
// SMI notification code table, read through command EC_C_SMI_QUERY
//
#define EC_N_SMI_NULL                  0x00    // Null marks the end of the SMI notification queue
#define EC_N_SMI_HOTKEY                0x20    // Hotkey pressed SMI
#define EC_N_SMI_ACINSERTION           0x30    // AC insertion SMI
#define EC_N_SMI_ACREMOVAL             0x31    // AC removal SMI
#define EC_N_SMI_PWRSW                 0x32    // Power switch press SMI
#define EC_N_SMI_LID                   0x33    // Lid switch change SMI
#define EC_N_SMI_VB                    0x34    // Virtual battery switch change SMI
#define EC_N_SMI_THERM_0               0x60    // Thermal state 0 SMI
#define EC_N_SMI_THERM_1               0x61    // Thermal state 1 SMI
#define EC_N_SMI_THERM_2               0x62    // Thermal state 2 SMI
#define EC_N_SMI_THERM_3               0x63    // Thermal state 3 SMI
#define EC_N_SMI_THERM_4               0x64    // Thermal state 4 SMI
#define EC_N_SMI_THERM_5               0x65    // Thermal state 5 SMI
#define EC_N_SMI_THERM_6               0x66    // Thermal state 6 SMI
#define EC_N_SMI_THERM_7               0x67    // Thermal state 7 SMI
#define EC_N_SMI_THERM_8               0x68    // Thermal state 8 SMI
#define EC_N_SMI_DOCKED                0x70    // Dock complete SMI
#define EC_N_SMI_UNDOCKED              0x71    // Undock complete SMI
#define EC_N_SMI_UNDOCKREQUEST         0x72    // Undocking request SMI
#define EC_N_SMI_TIMER                 0x80    // Timer wakeup SMI

//
// Hotkey scan code (CTRL + ALT + SHIFT + key)
//
#define EC_HK_ESC      0x01          // ESC
#define EC_HK_1        0x02          // 1 !
#define EC_HK_2        0x03          // 2 @
#define EC_HK_3        0x04          // 3 #
#define EC_HK_4        0x05          // 4 $
#define EC_HK_5        0x06          // 5 %
#define EC_HK_6        0x07          // 6 ^
#define EC_HK_7        0x08          // 7 &
#define EC_HK_8        0x09          // 8 *
#define EC_HK_9        0x0A          // 9 (
#define EC_HK_0        0x0B          // 0 )
#define EC_HK_MINUS    0x0C          // - _
#define EC_HK_ADD      0x0D          // = +
#define EC_HK_F1       0x3B          // F1
#define EC_HK_F2       0x3C          // F2
#define EC_HK_F3       0x3D          // F3
#define EC_HK_F4       0x3E          // F4
#define EC_HK_F5       0x3F          // F5
#define EC_HK_F6       0x40          // F6
#define EC_HK_F7       0x41          // F7
#define EC_HK_F8       0x42          // F8
#define EC_HK_F9       0x43          // F9
#define EC_HK_F10      0x44          // F10
#define EC_HK_F11      0x57          // F11
#define EC_HK_F12      0x58          // F12

//
// BoardId format definition (Data came from EC_C_FAB_ID command)
//
typedef union {
  UINT16    Raw;
  struct {
    UINT8  BoardId        :6;   // [5:0]   - BOARD_IDx
    UINT8  BomId          :3;   // [8:6]   - BOM_IDx
    UINT8  FabId          :2;   // [10:9]  - REV_FAB_IDx
    UINT8  SpdPresent     :1;   // [11]    - SPD_PRSNT
    UINT8  VirtualBattery :1;   // [12]    - VIRTUAL_BATTERY
    UINT8  VirtualDock    :1;   // [13]    - VIRTUAL_DOCK_DET_N
    UINT8  RetimerBypass  :1;   // [14]    - RETIMER_BYPASS_STRAP
    UINT8  EspiTestCard   :1;   // [15]    - ESPI_TESTCARD_DET
  } EhlRvpFields;
} BOARD_ID_INFO;

#endif // EC_COMMANDS_H_
