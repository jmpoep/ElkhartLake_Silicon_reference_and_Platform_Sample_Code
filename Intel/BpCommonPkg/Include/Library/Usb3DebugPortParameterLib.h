//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  This library class provides capability to get/set usb3 debug port parameter.

  Copyright (c) 2013, Intel Corporation. All rights reserved.<BR>
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

**/

#ifndef __USB3_DEBUG_PORT_PARAMETER_LIB__
#define __USB3_DEBUG_PORT_PARAMETER_LIB__

typedef struct {
  UINT8  Function;
  UINT8  Device;
  UINT8  Bus;
} PCI_ADDRESS;

typedef union {
  UINT32       Controller;
  PCI_ADDRESS  PciAddress;
} USB3_DEBUG_PORT_CONTROLLER;

/**
  Returns the USB debug port controller.
  bit:  0~ 7: Function
  bit:  8~15: Device
  bit: 16~24: Bus

  @return  Controller information of USB debug port.

**/
UINT32
EFIAPI
GetUsb3DebugPortController (
  VOID
  );

/**
  Sets the USB debug port controller.
  bit:  0~ 7: Function
  bit:  8~15: Device
  bit: 16~24: Bus

  @param[in]    Controller information of USB debug port value to be set.

  @retval  TRUE           The controller of USB debug port was sucessfully set.
  @retval  FALSE          The controller of USB debug port could not be set.

**/
BOOLEAN
EFIAPI
SetUsb3DebugPortController (
  UINT32        Controller
  );

#endif
