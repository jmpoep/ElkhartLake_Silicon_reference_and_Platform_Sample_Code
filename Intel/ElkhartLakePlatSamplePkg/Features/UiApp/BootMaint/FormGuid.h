/** @file
  Formset guids, form id and VarStore data structure for Boot Maintenance Manager.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2004 - 2017 Intel Corporation.

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
#ifndef _FORM_GUID_H_
#define _FORM_GUID_H_

#include <Guid/GlobalVariable.h>
#include <Setup.h>
#include <OemSetup.h>
#include <Setup/SetupId.h>

#define BOOT_MAINT_FORMSET_GUID \
  { \
  0x642237c7, 0x35d4, 0x472d, {0x83, 0x65, 0x12, 0xe0, 0xcc, 0xf2, 0x7a, 0x22} \
  }

#define FILE_EXPLORE_FORMSET_GUID \
  { \
  0x1f2d63e1, 0xfebd, 0x4dc7, {0x9c, 0xc5, 0xba, 0x2b, 0x1c, 0xef, 0x9c, 0x5b} \
  }

#define FORM_MAIN_ID                         0x1001
#define FORM_BOOT_ADD_ID                     0x1002
#define FORM_BOOT_DEL_ID                     0x1003
#define FORM_BOOT_CHG_ID                     0x1004
#define FORM_DRV_ADD_ID                      0x1005
#define FORM_DRV_DEL_ID                      0x1006
#define FORM_DRV_CHG_ID                      0x1007
#define FORM_CON_MAIN_ID                     0x1008
#define FORM_CON_IN_ID                       0x1009
#define FORM_CON_OUT_ID                      0x100A
#define FORM_CON_ERR_ID                      0x100B
#define FORM_FILE_SEEK_ID                    0x100C
#define FORM_FILE_NEW_SEEK_ID                0x100D
#define FORM_DRV_ADD_FILE_ID                 0x100E
#define FORM_DRV_ADD_HANDLE_ID               0x100F
#define FORM_DRV_ADD_HANDLE_DESC_ID          0x1010
#define FORM_BOOT_NEXT_ID                    0x1011
#define FORM_TIME_OUT_ID                     0x1012
#define FORM_BOOT_SETUP_ID                   0x1014
#define FORM_DRIVER_SETUP_ID                 0x1015
#define FORM_BOOT_LEGACY_DEVICE_ID           0x1016
#define FORM_CON_COM_ID                      0x1017
#define FORM_CON_COM_SETUP_ID                0x1018
#define FORM_SET_FD_ORDER_ID                 0x1019
#define FORM_SET_HD_ORDER_ID                 0x101A
#define FORM_SET_CD_ORDER_ID                 0x101B
#define FORM_SET_NET_ORDER_ID                0x101C
#define FORM_SET_BEV_ORDER_ID                0x101D
#define FORM_FILE_EXPLORER_ID                0x101E
#define FORM_BOOT_ADD_DESCRIPTION_ID         0x101F
#define FORM_DRIVER_ADD_FILE_DESCRIPTION_ID  0x1020
#define FORM_CON_MODE_ID                     0x1021
#define FORM_MEMORY_CHECK_ID                 0x1022

#define MAXIMUM_FORM_ID                      0x10FF

#define KEY_VALUE_COM_SET_BAUD_RATE          0x1101
#define KEY_VALUE_COM_SET_DATA_BITS          0x1102
#define KEY_VALUE_COM_SET_STOP_BITS          0x1103
#define KEY_VALUE_COM_SET_PARITY             0x1104
#define KEY_VALUE_COM_SET_TERMI_TYPE         0x1105
#define KEY_VALUE_MAIN_BOOT_NEXT             0x1106
#define KEY_VALUE_BOOT_ADD_DESC_DATA         0x1107
#define KEY_VALUE_BOOT_ADD_OPT_DATA          0x1108
#define KEY_VALUE_DRIVER_ADD_DESC_DATA       0x1109
#define KEY_VALUE_DRIVER_ADD_OPT_DATA        0x110A
#define KEY_VALUE_SAVE_AND_EXIT              0x110B
#define KEY_VALUE_NO_SAVE_AND_EXIT           0x110C
#define KEY_VALUE_BOOT_FROM_FILE             0x110D

#define MAXIMUM_NORMAL_KEY_VALUE             0x11FF

//
// Varstore ID defined for Buffer Storage
//
#define VARSTORE_ID_BOOT_MAINT               0x1000
#define VARSTORE_ID_FILE_EXPLORER            0x1001

#define LABEL_BOOT_MAINTENANCE_INFORMATION   0x1000
//
// End Label
//
#define LABEL_END   0xffff
#define MAX_MENU_NUMBER 100

//
// Boot Maintenance Manager Menu default values
//
#if FixedPcdGetBool(PcdPerformanceEnable) == 1
#define DEFAULT_BOOT_TIME_OUT  0
#else
#define DEFAULT_BOOT_TIME_OUT  5
#endif

#define PPV_BOOT_TIME_OUT  1
///
/// This is the structure that will be used to store the
/// question's current value. Use it at initialize time to
/// set default value for each question. When using at run
/// time, this map is returned by the callback function,
/// so dynamically changing the question's value will be
/// possible through this mechanism
///
#pragma pack(1)

typedef struct {
  BOOLEAN FastBootEnable;
  //
  // Three questions displayed at the main page
  // for Timeout, BootNext, MemoryCheck Variables respectively
  //
  UINT16  FastBootTimeOut;
  UINT16  BootNext;
  UINT8   MemoryCheck;

  //
  // This is the COM1 Attributes value storage
  //
  UINT8   COM1BaudRate;
  UINT8   COM1DataRate;
  UINT8   COM1StopBits;
  UINT8   COM1Parity;
  UINT8   COM1TerminalType;

  //
  // This is the COM2 Attributes value storage
  //
  UINT8   COM2BaudRate;
  UINT8   COM2DataRate;
  UINT8   COM2StopBits;
  UINT8   COM2Parity;
  UINT8   COM2TerminalType;

  //
  // Driver Option Add Handle page storage
  //
  UINT16  DriverAddHandleDesc[MAX_MENU_NUMBER];
  UINT16  DriverAddHandleOptionalData[MAX_MENU_NUMBER];
  UINT8   DriverAddActive;
  UINT8   DriverAddForceReconnect;

  //
  // Console Input/Output/Errorout using COM port check storage
  //
  UINT8   ConsoleInputCOM1;
  UINT8   ConsoleInputCOM2;
  UINT8   ConsoleOutputCOM1;
  UINT8   ConsoleOutputCOM2;
  UINT8   ConsoleErrorCOM1;
  UINT8   ConsoleErrorCOM2;

  //
  // Console port for Out-Of-Band use.
  //
  UINT16  COMOutOfBandPort;

  //
  // At most 100 input/output/errorout device for console storage
  //
  UINT8   ConsoleInCheck[MAX_MENU_NUMBER];
  UINT8   ConsoleOutCheck[MAX_MENU_NUMBER];
  UINT8   ConsoleErrCheck[MAX_MENU_NUMBER];
  //
  // Boot or Driver Option Order storage
  // The value is the OptionNumber+1 because the order list value cannot be 0
  // Use UINT32 to hold the potential value 0xFFFF+1=0x10000
  //
  UINT32  BootOptionOrder[MAX_MENU_NUMBER];
  UINT32  DriverOptionOrder[MAX_MENU_NUMBER];
  //
  // Boot or Driver Option Delete storage
  //
  BOOLEAN BootOptionDel[MAX_MENU_NUMBER];
  BOOLEAN DriverOptionDel[MAX_MENU_NUMBER];

  //
  // This is the Terminal Attributes value storage
  //
  UINT8   COMBaudRate[MAX_MENU_NUMBER];
  UINT8   COMDataRate[MAX_MENU_NUMBER];
  UINT8   COMStopBits[MAX_MENU_NUMBER];
  UINT8   COMParity[MAX_MENU_NUMBER];
  UINT8   COMTerminalType[MAX_MENU_NUMBER];
  UINT8   COMFlowControl[MAX_MENU_NUMBER];
  UINT8   COMLegacyResolution[MAX_MENU_NUMBER];
  UINT8   COMIsEnabled[MAX_MENU_NUMBER];

  //
  // Legacy Device Order Selection Storage
  //
  UINT8   LegacyFD[MAX_MENU_NUMBER];
  UINT8   LegacyHD[MAX_MENU_NUMBER];
  UINT8   LegacyCD[MAX_MENU_NUMBER];
  UINT8   LegacyNET[MAX_MENU_NUMBER];
  UINT8   LegacyBEV[MAX_MENU_NUMBER];
  UINT8   OldLegacyFD[MAX_MENU_NUMBER];
  UINT8   OldLegacyHD[MAX_MENU_NUMBER];
  UINT8   OldLegacyCD[MAX_MENU_NUMBER];
  UINT8   OldLegacyNET[MAX_MENU_NUMBER];
  UINT8   OldLegacyBEV[MAX_MENU_NUMBER];

  //
  // We use DisableMap array to record the enable/disable state of each boot device
  // It should be taken as a bit array, from left to right there are totally 256 bits
  // the most left one stands for BBS table item 0, and the most right one stands for item 256
  // If the bit is 1, it means the boot device has been disabled.
  //
  UINT8   DisableMap[32];

  //
  // Console Output Text Mode
  //
  UINT16  ConsoleOutMode;

  //
  //  UINT16                    PadArea[10];
  //
} BMM_FAKE_NV_DATA;

//
// Key used by File Explorer forms
//
#define KEY_VALUE_INIT_FORM           0x1000

///
/// This is the data structure used by File Explorer formset
///
typedef struct {
  UINT16  BootDescriptionData[75];
  UINT16  BootOptionalData[127];
  UINT16  DriverDescriptionData[75];
  UINT16  DriverOptionalData[127];
  UINT8   Active;
  UINT8   ForceReconnect;
  BOOLEAN BootOptionAdd[10];
} FILE_EXPLORER_NV_DATA;

#pragma pack()

#endif

