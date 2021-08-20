/**@file
  Header file for Touch Panel Driver

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2016 Intel Corporation.

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

#ifndef _EFI_I2C_TOUCH_PANEL_H_
#define _EFI_I2C_TOUCH_PANEL_H_

#include <Uefi.h>

//
// Libraries
//
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/DevicePathLib.h>
#include <Library/I2cDriverLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/IoLib.h>
#include <Library/PerformanceLib.h>
#include <Library/TimerLib.h>

//
// UEFI Driver Model Protocols
//
#include <Protocol/DriverBinding.h>
#include <Protocol/DriverSupportedEfiVersion.h>
#include <Protocol/ComponentName2.h>
#include <Protocol/ComponentName.h>

//
// Consumed Protocols
//
#include <Protocol/I2cIo.h>

//
// Produced Protocols
//
#include <Protocol/AbsolutePointer.h>

#include "Library/HidI2cPlatformSupportLib.h"

//
// Driver Version
//
#define TOUCH_DRIVER_VERSION  0x00000000

//
// Protocol instances
//
extern EFI_DRIVER_BINDING_PROTOCOL  gTouchPanelDriverDriverBinding;
extern EFI_COMPONENT_NAME2_PROTOCOL gTouchPanelDriverComponentName2;
extern EFI_COMPONENT_NAME_PROTOCOL  gTouchPanelDriverComponentName;

//
// Include files with function prototypes
//
//#include "ComponentName.h"
//#include "AbsolutePointer.h"



#define DEBUG_I2C_OPERATION   0x40000000
//#define DEBUG_ENTRY_EXIT      0x20000000
#define DEBUG_INT_OUTPUT      0x01000000
#define DEBUG_ENTRY_EXIT      DEBUG_INFO

#define TOUCH_SIGNATURE  0x544F4348 //"TOCH"
#define TOUCH_CONTEXT_FROM_PROTOCOL(a)   CR (a, ABSOLUTE_POINTER_DEV, AbsolutePointerProtocol, TOUCH_SIGNATURE)
typedef struct _EFI_TOUCH_INIT_TAB EFI_TOUCH_INIT_TABLE;

typedef struct {
  UINT8   HIDDescLengthLsb;
  UINT8   HIDDescLengthMsb;
  UINT8   BcdVersionLsb;
  UINT8   BcdVersionMsb;
  UINT8   ReportDescRegLengthLsb;
  UINT8   ReportDescRegLengthMsb;
  UINT8   ReportDescRegisterLsb;
  UINT8   ReportDescRegisterMsb;
  UINT8   InputRegisterLsb;
  UINT8   InputRegisterMsb;
  UINT8   MaxInputLengthLsb;
  UINT8   MaxInputLengthMsb;
  UINT8   OutputRegisterLsb;
  UINT8   OutputRegisterMsb;
  UINT8   MaxOutputLengthLsb;
  UINT8   MaxOutputLengthMsb;
  UINT8   CommandRegisterLsb;
  UINT8   CommandRegisterMsb;
  UINT8   DataRegisterLsb;
  UINT8   DataRegisterMsb;
  UINT16  VendorId;
  UINT16  ProductId;
  UINT16  VersionId;
  UINT16  Reserved;
  UINT16  Reserved2;
} HID_DESC;

// dictionary for parsing incoming data from touchpanel
typedef struct {
  UINT32  Id;         // ReportID. 0 means panel doesn't send ReportIDs, and it also means there is only 1 format
  UINT32  LogMaxX;    // max and min values for X and Y axes
  UINT32  LogMinX;
  UINT32  LogMaxY;
  UINT32  LogMinY;
  UINT32  BitStartB;  // bit positions of Buttons state /X coordinates / Y coordinates in input stream
  UINT32  BitStopB;   // bit positions are calculated in pure input data (after cutting Length and reportID)
  UINT32  BitStartX;
  UINT32  BitStopX;
  UINT32  BitStartY;
  UINT32  BitStopY;
  UINT32  BitsTotal;  // total number of bits with declared purpose
} INPUT_REPORT_FORMAT;

// set of dictionaries for parsing incoming data from touchpanel
typedef struct {
  UINT32                 Quantity;   // number of different report formats a panel might send
  UINT32                 TouchPanel; // flag to determine if this device is a touchpanel and not e.g. touchpad
  INPUT_REPORT_FORMAT*   Report;     // a pointer to array of dictionaries for report formats
} INPUT_REPORT_TABLE;

typedef struct {
  UINTN                         Signature;               //needed for CONTEXT_FROM_PROTOCOL
  EFI_I2C_IO_PROTOCOL          *I2cIoProtocol;           //needed I2cBus or I2cIo
  EFI_ABSOLUTE_POINTER_PROTOCOL AbsolutePointerProtocol;
  EFI_ABSOLUTE_POINTER_STATE    State;                   //storage space for AbsPtr's State
  EFI_ABSOLUTE_POINTER_MODE     Mode;                    //storage for AbsPtr's Mode
  BOOLEAN                       NewStateAvailable;
  EFI_UNICODE_STRING_TABLE      *ControllerNameTable;
  INPUT_REPORT_TABLE            InputReportTable;        //dictionary for parsing data from panel into x/y coordinates
  HID_DESC                      HidDescriptor;
  EFI_HANDLE                    ControllerHandle;
  HID_I2C_PLATFORM_SUPPORT      HidI2cPlatformSupport;   //platform-specific functions
  EFI_EVENT                     PollingEvent;

} ABSOLUTE_POINTER_DEV;

EFI_STATUS
EFIAPI
TouchPanelDriverDriverBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath OPTIONAL
  );

EFI_STATUS
EFIAPI
TouchPanelDriverDriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath OPTIONAL
  );

EFI_STATUS
EFIAPI
TouchPanelDriverDriverBindingStop (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN  EFI_HANDLE                  ControllerHandle,
  IN  UINTN                       NumberOfChildren,
  IN  EFI_HANDLE                  *ChildHandleBuffer OPTIONAL
  );

VOID
EFIAPI
CheckDataAvailableCallback (
  IN EFI_EVENT Event,
  IN VOID      *Context
  );

EFI_STATUS
EFIAPI
InitDevice (
  IN ABSOLUTE_POINTER_DEV *TouchDev,
  IN EFI_HANDLE ImageHandle
  );

typedef
EFI_STATUS
(EFIAPI *EFI_TOUCH_DEV_RESET) (
  IN ABSOLUTE_POINTER_DEV  *TouchDev
  );

typedef
EFI_STATUS
(EFIAPI *EFI_TOUCH_HID_INIT) (
  IN ABSOLUTE_POINTER_DEV  *TouchDev
  );

typedef
EFI_STATUS
(EFIAPI *EFI_TOUCH_INT) (
  IN     ABSOLUTE_POINTER_DEV  *TouchDev,
  IN OUT UINT16                *X,
  IN OUT UINT16                *Y,
  IN OUT UINT16                *Z,
  IN OUT UINT16                *ActiveButtons
  );

typedef struct {
  UINT32 ID;
  UINT32 Value;
} REPORT_DESCRIPTOR_TOKEN;

typedef struct {
  UINTN ReportId;
  UINTN MaxX;
  UINTN StartX;
  UINTN StopX;
  UINTN MaxY;
  UINTN StartY;
  UINTN StopY;
  UINTN Button;
} REPORT_DESCRIPTOR;

struct _EFI_TOUCH_INIT_TAB {
  EFI_TOUCH_DEV_RESET  Reset;
  EFI_TOUCH_HID_INIT   HidInit;
  EFI_TOUCH_INT        Int;
};

#define DEFAULT_HID_DESCRIPTOR_LENGTH 0x1E

#define USE_PAGE       0x01
#define DIGITIZER      0x0D
#define DESKTOP        0x01
#define USAGE          0x02
#define TOUCHPANEL     0x04
#define TIP_SWITCH     0x42
#define X_AXIS         0x30
#define Y_AXIS         0x31
#define REPORT_ID      0x21
#define LOG_MIN        0x05
#define LOG_MAX        0x09
#define REP_SIZE       0x1d
#define REP_COUNT      0x25
#define INPUT          0x20
#define OUTPUT         0x24
#define FEATURE        0x28
#define COLLECTION     0x2C
#define END_COLLECTION 0x30
#define PUSH           0x29
#define POP            0x2D

#define SET_IDLE 0x05
#define I2C_HID_LENGTH_PREFIX 2


typedef struct {
  UINT32 ID;
  UINT32 Value;
} TOKEN;

typedef struct {
  UINT32               GlobalUsage;
  UINT32               Usages;
  UINT32               UsageB;
  UINT32               UsageX;
  UINT32               UsageY;
  UINT32               LogMax;
  UINT32               LogMin;
  UINT32               ReportSize;
  UINT32               ReportCount;
  UINT32               GlobalUsageOnStack;
  UINT32               ReportSizeOnStack;
  UINT32               ReportCountOnStack;
  UINT32               TouchPanelUsage;
  INPUT_REPORT_FORMAT  TempReport;
} PARSER_STACK;

typedef struct {
  UINT32 B;
  UINT32 X;
  UINT32 Y;
} TOUCH_OUTPUT;

UINT16
GetLength (
  IN UINT8 Lsb,
  IN UINT8 Msb
  );

EFI_STATUS
TouchDevInt (
  IN     ABSOLUTE_POINTER_DEV  *TouchDev,
  IN OUT UINT16                *X,
  IN OUT UINT16                *Y,
  IN OUT UINT16                *Z,
  IN OUT UINT16                *ActiveButtons
  );

EFI_STATUS
EFIAPI
TouchDevInit(
  IN ABSOLUTE_POINTER_DEV  *TouchDev
  );

EFI_STATUS
ReadInputReportDescriptor (
  IN ABSOLUTE_POINTER_DEV *TouchDev
  );

TOUCH_OUTPUT ParseInput (
  INPUT_REPORT_TABLE  ReportTable,
  UINT8*              InputStream
  );

EFI_STATUS
SetInterruptFrequency (
  IN ABSOLUTE_POINTER_DEV *TouchDev
  );

#endif
