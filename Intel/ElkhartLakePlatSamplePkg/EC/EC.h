/**@file

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#ifndef _EC_H_
#define _EC_H_

// Prototypes
// Driver model protocol interface
//

EFI_STATUS
EFIAPI
EcWriteCmd (
  UINT8    cmd
);

EFI_STATUS
EFIAPI
EcReadData (
  UINT8   *data
);

EFI_STATUS
EFIAPI
EcQueryCommand (
  UINT8   *Qdata
);

EFI_STATUS EcIbFree (
  VOID
  );

EFI_STATUS
EFIAPI
EcWriteData (
  UINT8    data
);

EFI_STATUS
EFIAPI
EcReadMem (
  UINT8 Index,
  UINT8 *Data
);

EFI_STATUS
EFIAPI
EcWriteMem (
  UINT8 Index,
  UINT8 Data
);

EFI_STATUS
EFIAPI
ECEnableACPIMode (
  VOID
  );

EFI_STATUS
EFIAPI
ECDisableACPIMode (
  VOID
  );

EFI_STATUS
EFIAPI
ECDisableSMINotify (
  VOID
  );

EFI_STATUS
EFIAPI
ECEnableSMINotify (
  VOID
)  ;

EFI_STATUS
EFIAPI
EcGetSwitchStatus (
  UINT8   *Data
);

#define EcDataPort    0x62
#define EcCommandPort 0x66
#define EC_GPI_SMI_EVENT 0x08

//
// Meaning of Bit for Device Type
//
//  Bit 15  = Pipe B - LFP2
//  Bit 14  = Pipe B - EFP2
//  Bit 13  = Pipe B - TV2
//  Bit 12  = Pipe B - CRT2
//  Bit 11  = Pipe B - LFP
//  Bit 10  = Pipe B - EFP
//  Bit 9 = Pipe B - TV
//  Bit 8 = Pipe B - Reserved (830M), CRT (855MG, Alviso, Calistoga)
//  Bit 7 = Pipe A - LFP2 (830M), Reserved (855MG, Alviso, Calistoga)
//  Bit 6 = Pipe A - EFP2
//  Bit 5 = Pipe A - TV2
//  Bit 4 = Pipe A - CRT2
//  Bit 3 = Pipe A - LFP (830M), Reserved (855MG, Alviso, Calistoga)
//  Bit 2 = Pipe A - EFP
//  Bit 1 = Pipe A - TV
//  Bit 0 = Pipe A - CRT
//
#define DEVICE_PIPEA_CRT                0x0001
#define DEVICE_PIPEA_TV                 0x0002
#define DEVICE_PIPEA_EFP                0x0004
#define DEVICE_PIPEA_LFP                0x0008
#define DEVICE_PIPEA_CRT2               0x0010
#define DEVICE_PIPEA_TV2                0x0020
#define DEVICE_PIPEA_EFP2               0x0040
#define DEVICE_PIPEA_LFP2               0x0080
#define DEVICE_PIPEB_CRT                0x0100
#define DEVICE_PIPEB_TV                 0x0200
#define DEVICE_PIPEB_EFP                0x0400
#define DEVICE_PIPEB_LFP                0x0800
#define DEVICE_PIPEB_CRT2               0x1000
#define DEVICE_PIPEB_TV2                0x2000
#define DEVICE_PIPEB_EFP2               0x4000
#define DEVICE_PIPEB_LFP2               0x8000


//;-----------------------------------------------------------------------;
//;     H8/3334 SMC COMMANDS EQUATES                                      ;
//;-----------------------------------------------------------------------;
//; Command Val Format in byte order/describtion
//; Host commands
#define SMC_READ_BYTE                   0x001  // WR: Cmd,High adr & Low adr >> RD: Data
#define SMC_WRITE_BYTE                  0x002  // WR: Cmd,High adr, Low adr & Data
#define SMC_MODIFY_BYTE                 0x003  // WR: Cmd,High adr, Low adr, AND_mask & OR_mask
#define SMC_ENABLE_SMI_NOTIFY           0x004  // WR: Cmd
#define SMC_DISABLE_SMI_NOTIFY          0x005  // WR: Cmd
#define SMC_QUERY_SYSTEM_STATUS         0x006  // WR: Cmd >> RD:Data
#define SMC_FAN_STS_BIT                 0x080
#define SMC_HWTHTL_STS_BIT              0x040
#define SMC_DOCK_STS_BIT                0x020
#define SMC_AC_STS_BIT                  0x010
#define SMC_THRM_STS_BIT                0x00F
#define SMC_SELF_TEST                   0x007  // SMC Self Test
#define SMC_DISABLE_WRITE               0x008  // Disable Write Byte
#define SMC_GET_MODE                    0x009  // Not documented, returns
                                               // byte0/1/2  'KSC' &
                                               // byte3.6 0 THRM limits not locked yet
                                               // byte3.5 0 THRM limits not locked yet
                                               // byte3.0 0/1 SMC in SMI/ACPI mode
#define SMC_GET_SWITCH_STATUS           0x00A  // Get Switches status.
#define SMC_ENABLE_ACPI_MODE            0x0AA  // Enable ACPI mode
#define SMC_DISABLE_ACPI_MODE           0x0AB  // Disable ACPI mode

// Power Plane control Commands
#define SMC_SUSPEND_EC                  0x020  // Suspend EC ???
#define SMC_RESUME_EC                   0x021  // Resume EC  ???

#define SMC_POWER_OFF_SYSTEM            0x022  // Turn System Power Off
#define SMC_ENABLE_POWER_SWITCH         0x023  // Enable Power Switch
#define SMC_DISABLE_POWER_SWITCH        0x024  // Disable Power Switch
#define SMC_ENABLE_SMRTPOWER_SWITCH     0x025  // Enable Smart Power Switch
#define SMC_DISABLE_SMRTPOWER_SWITCH    0x026  // Disable Smart Power Switch
#define EC_POWER_FEATURES_CMD           0x027  // This is the command for setting EC Power features.
#define EC_LOW_POWER_EXIT_CMD           0x02D  // This is the command for EC Low Power Exit.
#define EC_DEBUG_LOW_POWER_ENABLE       0x01   //     [0] - Low power mode, when set, the EC idles its CPU core and powers down all unnecessary modules to achieve the lowest possible power consumption for CS.
#define EC_DEBUG_LED_DISABLE            0x02   //     [1] - When set all LEDs controlled by the EC are turned off to save power in CS
#define EC_DEBUG_BASE_PCS_PWR_POLICY    0x04   //     [2] - When set the EC turns off role reversal and does not supply power to the base.

#define SMC_ENABLE_DEEP_SLEEP           0x028  // Enable Deep Sleep for SMC   ???

//; Battery control commands
#define SMC_GET_BATT_STATUS             0x030  // Get Battery Status
#define SMC_GET_BATT_CHARGE_STATUS      0x031  // Get Battery State Of Charge
#define SMC_GET_BATT_TIME_EMPTY         0x032  // Get Battery Time To Empty
#define SMC_GET_BATT_TIME_FULL          0x033  // Get Battery Time To Full
#define SMC_GET_BATT_IN_USE             0x034  // Get Battery In Use
#define SMC_GET_BATT_TYPE               0x035  // Get Battery Type
#define SMC_BATT_DISCHARGE              0x036  // Set Battery To Discharge
#define SMC_BATT_CHARGE                 0x037  // Set Battery To Charge
#define SMC_BATT_STOP_CHARGE            0x038  // Set Battery To Stop Charging
#define SMC_SET_BATT_CONDITION          0x039  // Set Battery To Condition
#define SMC_SET_BATT_THRESH             0x03A  // Set Battery Thresholds

//; Peripheral control commands
#define SMC_GET_BACKLIGHT               0x040  // Get Back-light Brightness
#define SMC_SET_BACKLIGHT               0x041  // Set Back-light Brightness
#define SMC_USB_POWER_ON                0x044  // USB Power On
#define SMC_USB_POWER_OFF               0x045  // USB Power Off
#define SMC_LAN_POWER_ON                0x046  // Enable onBoard LAN

//; Extended Thermal Management
#define SMC_SET_ETM_COMMAND             0x4B // Enable Extended Thermal Management

//; PECI Related commands
#define SMC_SET_PECI_INJECTED_TEMP      0x04D  // Set PECI Injected Temp

//; Thermal handling commands
#define SMC_GET_CURRENT_TEMP            0x050  // Read Current CPU temp
#define SMC_SET_TEMP_RANGES             0x051  // Set Thermal table
#define SMC_LOCK_TEMP_RANGES            0x052  // Lock Thermal table
#define SMC_GET_CURRENT_CORE_TEMP       0x053  // Read Current CPU Core temp
#define SMC_SET_THERMAL_THRESH          0x057  // Set Thermal Threshold.
#define SMC_SET_SHUTDOWN_TEMP           0x058  // Set Shutdown Temperature.
#define SMC_SET_THROTTLE_TEMP           0x059  // Set Throttle Temperature.
#define SMC_SET_QC_THERM_OFFSET         0x05D
#define SMC_FAIL_SAFE_FAN_CTRL          0x01C  // Set temp and fan % when OS is hung
//; SMC Dispatcher Commands
#define SMC_QUERY_SMI                   0x070  // Query SMI event
#define SMC_TIMER_SMI                   0x071  // SMI Timer Service

//; ACPI Embedded controller commands
#define SMC_READ_EC                     0x080  // Read EC
#define SMC_WRITE_EC                    0x081  // Write EC
#define SMC_LOCK_EC                     0x082  // Lock EC for burst use
#define SMC_UNLOCK_EC                   0x083  // Unlock EC from burst use
#define SMC_QUERY_EC                    0x084  // Query EC event

//; SMBus commands
#define SMC_WRITE_SMBUS                 0x0A0  // Write SMBus
#define SMC_READ_SMBUS                  0x0A1  // Read SMBus

//;-----------------------------------------------------------------------;
//;   SMI EVENT NOTIFICATIONS EQUATES                                     ;
//;-----------------------------------------------------------------------;
//; KBC Notification
#define SMC_KBC_HOTKEY                  0x020  // KBC hotkey pressed

//; Power Plane events
#define SMC_AC_INSERTED                 0x030  // AC power inserted
#define SMC_AC_REMOVED                  0x031  // AC power removed
#define SMC_POWER_BTN_PRESSED           0x032  // Power switch pressed

//; Battery events
#define SMC_BATT0_INSERTED              0x040  // Battery0 inserted
#define SMC_BATT0_REMOVED               0x042  // Battery0 removed
#define SMC_BATT0_LOW                   0x044  // Battery0 low
#define SMC_BATT0_CRITICAL              0x046  // Battery0 critical
#define SMC_BATT0_FAILED                0x048  // Battery0 failure
#define SMC_BATT1_INSERTED              0x041  // Battery1 inserted
#define SMC_BATT1_REMOVED               0x043  // Battery1 removed
#define SMC_BATT1_LOW                   0x045  // Battery1 low
#define SMC_BATT1_CRITICAL              0x047  // Battery1 critical
#define SMC_BATT1_FAILED                0x049  // Battery1 failure

//; Peripheral device events
#define SMC_USB_DEV_INSERTED            0x050  // USB device inserted
#define SMC_USB_DEV_REMOVED             0x051  // USB device removed
#define SMC_BAY_FLOPPY_INSERTED         0x055  // Floppy inserted into device bay
#define SMC_BAY_CDROM_INSERTED          0x056  // CD-ROM inserted into device bay
#define SMC_BAY_HD_INSERTED             0x057  // Hard disk inserted into device bay
#define SMC_BAY_BATT_INSERTED           0x058  // Battery inserted into device bay

//; Thermal events
#define SMC_THRM_NORMAL                 0x060  // Normal CPU temp. (no STCLK#)
#define SMC_THRM_THTL1                  0x061  // Stage1 CPU temp. (thr. 12.5%)
#define SMC_THRM_THTL2                  0x062  // Stage2 CPU temp. (thr. 25%)
#define SMC_THRM_THTL3                  0x063  // Stage3 CPU temp. (thr. 37.5%)
#define SMC_THRM_THTL4                  0x064  // Stage4 CPU temp. (thr. 50%)
#define SMC_THRM_THTL5                  0x065  // Stage5 CPU temp. (thr. 62.5%)
#define SMC_THRM_THTL6                  0x066  // Stage6 CPU temp. (thr. 75.5%)
#define SMC_THRM_THTL7                  0x067  // Stage7 CPU temp. (thr. 87.5%)
#define SMC_THRM_THTL8                  0x068  // Stage8 CPU temp. (Stop clock)
#define SMC_THRM_THTL9                  0x069  // Stage9 CPU temp. (Stop clock)

//; Docking events
#define SMC_DOCK_COMPLETE               0x070  // Docking completed
#define SMC_UNDOCK_COMPLETE             0x071  // Undocking completed
#define SMC_UNDOCK_REQUEST              0x072  // Undock requested

//; SMC Dispatcher events
#define SMC_TIMER_SMI_WAKE              0x080  // Internal timer Wake-up

//; SMBUS event notification
#define SMC_SMBUS_COMPLETE              0x091  // SMBus transaction done
#define SMC_SMBUS_ERROR                 0x092  // SMBus Error
#define SMC_SMBUS_ALERT                 0x093  // SMBus Alarm

//; SMC Revision & ID
#define SMC_READ_REVISION               0x090  // ReadRevision from EC firmware.
#define SMC_READ_PLATFORMID             0x092  // ReadPlatformID.
#define SMC_5Fh                         0x05F  // Not in the KSCCMFRF.TXT file.
//;-----------------------------------------------------------------------;

#define SMC_DEEPSX_CMD                  0x29
#define SMC_TURBOCTRL_TESTMODE_ENABLE   0x63
#define SMC_TURBOCTRL_TESTMODE_DISABLE  0x64

#define SMC_FAB_ID                      0x0D
#define SMC_SYSTEM_POWER_OFF            0x22
#define SMC_LAN_ON                      0x46
#define SMC_LAN_OFF                     0x47
#define SMC_SET_CTEMP                   0x58
#define SMC_SMI_HOTKEY                  0x72
#define SMC_SMI_INJECT                  0xBA
#define SMC_SMI_DISABLE                 0xBC
#define SMC_SMI_ENABLE                  0xBD
#define SMC_ACPI_ENABLE                 0xAA
#define SMC_ACPI_DISABLE                0xAB
#define SMC_ALS_ENABLE                  0x0E


#define SMC_HK_ESC                      0x01  // ESC
#define SMC_HK_1                        0x02  // 1 !
#define SMC_HK_2                        0x03  // 2 @
#define SMC_HK_3                        0x04  // 3 #
#define SMC_HK_4                        0x05  // 4 $
#define SMC_HK_5                        0x06  // 5 %
#define SMC_HK_6                        0x07  // 6 ^
#define SMC_HK_7                        0x08  // 7 &
#define SMC_HK_8                        0x09  // 8 *
#define SMC_HK_9                        0x0A  // 9 (
#define SMC_HK_0                        0x0B  // 0 )
#define SMC_HK_MINUS                    0x0C  // - _
#define SMC_HK_ADD                      0x0D  // = +
#define SMC_HK_F1                       0x3B  // F1
#define SMC_HK_F2                       0x3C  // F2
#define SMC_HK_F3                       0x3D  // F3
#define SMC_HK_F4                       0x3E  // F4
#define SMC_HK_F5                       0x3F  // F5
#define SMC_HK_F6                       0x40  // F6
#define SMC_HK_F7                       0x41  // F7
#define SMC_HK_F8                       0x42  // F8
#define SMC_HK_F9                       0x43  // F9
#define SMC_HK_F10                      0x44  // F10
#define SMC_HK_F11                      0x57  // F11
#define SMC_HK_F12                      0x58  // F12
#endif

