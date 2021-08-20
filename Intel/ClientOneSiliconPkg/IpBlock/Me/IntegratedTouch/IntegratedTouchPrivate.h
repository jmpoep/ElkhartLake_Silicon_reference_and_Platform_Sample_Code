/**@file
  Private Header file for Touch Panel Driver

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2017 Intel Corporation.

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

#ifndef _INTEGRATED_TOUCH_DRIVER_PRIVATE_H_
#define _INTEGRATED_TOUCH_DRIVER_PRIVATE_H_

#include <Uefi.h>

//
// Libraries
//
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

//
// UEFI Driver Model Protocols
//
#include <Protocol/DriverBinding.h>
#include <Protocol/DriverSupportedEfiVersion.h>
#include <Protocol/ComponentName2.h>
#include <Protocol/ComponentName.h>
#include <Protocol/PciIo.h>

//
// Produced Protocols
//
#include <Protocol/AbsolutePointer.h>
#include <Protocol/IntegratedTouch.h>
#include <Protocol/IntegratedTouchHid.h>
#include <Protocol/HeciProtocol.h>

#define TOUCH_DRIVER_VERSION  0x00000000

//
// Protocol instances
//
extern EFI_DRIVER_BINDING_PROTOCOL  gIntegratedTouchDriverBinding;
extern EFI_COMPONENT_NAME2_PROTOCOL gIntegratedTouchDriverComponentName2;
extern EFI_COMPONENT_NAME_PROTOCOL  gIntegratedTouchDriverComponentName;
extern EFI_GUID                     gEfiTouchPanelGuid;

#define INTEGRATED_TOUCH_SIGNATURE  0x48544348 //"HTCH"
#define INTEGRATED_TOUCH_CONTEXT_FROM_ABSPTR_PROTOCOL(a)   CR (a, INTEGRATED_TOUCH_DEV, AbsPtrProtocol, INTEGRATED_TOUCH_SIGNATURE)
#define INTEGRATED_TOUCH_CONTEXT_FROM_HID_PROTOCOL(a)   CR (a, INTEGRATED_TOUCH_DEV, HidProtocol, INTEGRATED_TOUCH_SIGNATURE)
#define INTEGRATED_TOUCH_CONTEXT_FROM_PROTOCOL(a)   CR (a, INTEGRATED_TOUCH_DEV, IntegratedTouchProtocol, INTEGRATED_TOUCH_SIGNATURE)

typedef enum {
  FRAME_DATA = 0,
  ERROR_DATA = 1,
  FRAME_DATA_W_DEBUG = 2,
  HID_REPORT = 3,
  GET_FEATURES_DATA = 4,
  MAX_RAW_DATA_TYPES = 5
} RAW_DATA_TYPES;

typedef struct  {
  RAW_DATA_TYPES DataType;
  UINT32 RawDataSz;
  UINT32 BufferId;
  UINT32 ProtocolVer;
  UINT8 Reserved[48];
} RAW_DATA_HEADER;

typedef struct {
  RAW_DATA_HEADER Header;
  UINT8 ReportId;
  UINT8 TouchSts;
  UINT8 LowerXbyte;
  UINT8 HigherXbyte;
  UINT8 LowerYbyte;
  UINT8 HigherYbyte;
} SINGLE_FINGER_REPORT;

typedef struct {
  UINTN                          Signature;
  EFI_HANDLE                     ControllerHandle;
  EFI_DEVICE_PATH_PROTOCOL       *DevicePath;
  EFI_ABSOLUTE_POINTER_PROTOCOL  AbsPtrProtocol;
  EFI_ABSOLUTE_POINTER_MODE      Mode;
  UINT32                         TouchBufferSize;
  UINT32                         FeedbackBufferSize;
  UINT8                          *Me2HidBuffer;
  UINT8                          *FeedbackBuffer;
  UINT8                          *Hid2MeBuffer;
  BOOLEAN                        TouchDataAvailable;
  EFI_ABSOLUTE_POINTER_STATE     TouchData;
  EFI_UNICODE_STRING_TABLE       *ControllerNameTable;
  ITOUCH_HID_PROTOCOL            HidProtocol;
  BOOLEAN                        HidProtocolActive;
  BOOLEAN                        Me2HidBufferFull;
  BOOLEAN                        Hid2MeBufferFull;
  EFI_EVENT                      HeciPollingEvent;
  UINTN                          WaitReadyCount;
  EFI_EVENT                      WaitReadyEvent;
  EFI_EVENT                      ExitEvent;
  BOOLEAN                        Initialized;
  INTEGRATED_TOUCH_PROTOCOL      IntegratedTouchProtocol;
  EFI_PCI_IO_PROTOCOL            *PciIo;
  EFI_PHYSICAL_ADDRESS           Me2HidBufferDevAddr;
  EFI_PHYSICAL_ADDRESS           FeedbackBufferDevAddr;
  EFI_PHYSICAL_ADDRESS           Hid2MeBufferDevAddr;
  VOID                           *Me2HidBufferMapping;
  VOID                           *FeedbackBufferMapping;
  VOID                           *Hid2MeBufferMapping;
  UINT64                         PciAttributes;
} INTEGRATED_TOUCH_DEV;

EFI_STATUS
EFIAPI
IntegratedTouchDriverBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath OPTIONAL
  );

EFI_STATUS
EFIAPI
IntegratedTouchDriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath OPTIONAL
  );

EFI_STATUS
EFIAPI
IntegratedTouchDriverBindingStop (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN  EFI_HANDLE                  ControllerHandle,
  IN  UINTN                       NumberOfChildren,
  IN  EFI_HANDLE                  *ChildHandleBuffer OPTIONAL
  );

/**
  Function to unload Integrated Touch Driver when
  gBS->ExitBootServices() called or LegacyBoot event.

  @param  Event                   Pointer to this event
  @param  Context                 Event handler private data

**/
VOID
EFIAPI
IntegratedTouchExitEvent (
  IN EFI_EVENT     Event,
  IN VOID          *Context
  );


/**
  Event designated to start Integrated Touch Initialization after CSME reports
  that it is ready.
  Gets invoked for the first time by signal notify, later on called by Timer after TriggerTime expires.

  @param  EFI_EVENT             Handle to an event structure
  @param  VOID                  Pointer to the notification functions context,
                                iTouchDevice

  @retval EFI_SUCCESS           The operation completed successfully.
  @retval Others                An unexpected error occurred.
**/
VOID
EFIAPI
IntegratedTouchWaitReadyEvent (
  IN EFI_EVENT   Event,
  IN VOID        *Context
  );

/**
  Free IntegratedTouch structure allocated in Start()
  Close all Events except exit event
  Free allocated Unicode Strings
  Calls TouchSensorClearMemWindow

  @param[in]  iTouchDev       context of iTouch device

**/
VOID
EFIAPI
IntegratedTouchCleanUp (
  IN INTEGRATED_TOUCH_DEV             *iTouchDev
  );

/**
  Creates WaitReadyEvent responsible for iTouch Initialization
  and ExitEvent responsible for ExitBootServices clean up

  @param[in]  iTouchDev       context of iTouch device

  @retval EFI_SUCCESS           The operation completed successfully.
  @retval Others                An unexpected error occurred.
**/
EFI_STATUS
EFIAPI
IntegratedTouchCreateStartAndExitEvents (
  IN INTEGRATED_TOUCH_DEV             *iTouchDev
  );

/**
  Starts Heci and Pointer polling on Integrated Touch

  @param  iTouchDev       context of iTouch device

  @retval EFI_SUCCESS     iTouch initialized successfully
  @retval other           error during initialization
**/
EFI_STATUS
IntegratedTouchStartPolling (
  INTEGRATED_TOUCH_DEV                *iTouchDev
  );

/**
  Initialize integrated touch according to procedure described in EDS

  @param  iTouchDev       context of iTouch device

  @retval EFI_SUCCESS     iTouch initialized successfully
  @retval other           error during initialization
**/
EFI_STATUS
IntegratedTouchInitialize (
  INTEGRATED_TOUCH_DEV                *iTouchDev
  );

/**
  Installs AbsolutePointerProtocol and IntegratedTouchHidProtocol
  Assigns TouchPanel Guid for Virtual Keyboard support

  @param[in]  iTouchDev       context of iTouch device

  @retval EFI_SUCCESS           The operation completed successfully.
  @retval Others                An unexpected error occurred.
**/
EFI_STATUS
EFIAPI
IntegratedTouchInstallProtocols (
  IN INTEGRATED_TOUCH_DEV                *iTouchDev
  );

/**
  Parses data stream from touch device and decodes it into X/Y/Z coordinates + button

  @param[in, out]  Output                Pointer to memory buffer containing output pointer state
  @param[in]       InputStream           Pointer to memory buffer containing HID data

**/
VOID
IntegratedTouchParseInput (
  IN OUT EFI_ABSOLUTE_POINTER_STATE *Output,
  IN     SINGLE_FINGER_REPORT*      InputStream
  );

#endif


