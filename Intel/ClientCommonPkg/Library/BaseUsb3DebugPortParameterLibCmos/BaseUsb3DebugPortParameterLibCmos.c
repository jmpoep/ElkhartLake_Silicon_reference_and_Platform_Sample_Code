/** @file
  USB debug Port Parameter library instance based on PCD.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2016 Intel Corporation.

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

#include <Base.h>
#include <Library/DebugLib.h>
#include <Library/CmosAccessLib.h>
#include <Library/PcdLib.h>
#include <Library/Usb3DebugPortParameterLib.h>

/**
  Returns the USB3 debug port controller.
  bit:  0~ 7: Function
  bit:  8~15: Device
  bit: 16~24: Bus
  
  @return  Controller information of USB debug port.

**/
UINT32
EFIAPI
GetUsb3DebugPortController (
  VOID
  )
{
  USB3_DEBUG_PORT_CONTROLLER       UsbDebugPort;

  UsbDebugPort.Controller = 0;
  UsbDebugPort.PciAddress.Bus = CmosRead8 (PcdGet8 (PcdUsb3DebugPortBusIndex));
  UsbDebugPort.PciAddress.Device = CmosRead8 (PcdGet8 (PcdUsb3DebugPortDeviceIndex));
  UsbDebugPort.PciAddress.Function = CmosRead8 (PcdGet8 (PcdUsb3DebugPortFunctionIndex));
  if (UsbDebugPort.Controller == 0) {
    // Just in case CMOS cleared
    UsbDebugPort.PciAddress.Bus = PcdGet8(PcdUsbSerialXhciBus);
    UsbDebugPort.PciAddress.Device = PcdGet8(PcdUsbSerialXhciDev);
    UsbDebugPort.PciAddress.Function = PcdGet8(PcdUsbSerialXhciFunc);
    CmosWrite8 (PcdGet8 (PcdUsb3DebugPortBusIndex), UsbDebugPort.PciAddress.Bus);
    CmosWrite8 (PcdGet8 (PcdUsb3DebugPortDeviceIndex), UsbDebugPort.PciAddress.Device);
    CmosWrite8 (PcdGet8 (PcdUsb3DebugPortFunctionIndex), UsbDebugPort.PciAddress.Function);
  }

  return UsbDebugPort.Controller;
}

/**
  Sets the USB3 debug port controller.
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
  )
{
  USB3_DEBUG_PORT_CONTROLLER       UsbDebugPort;

  UsbDebugPort.Controller = Controller;
  CmosWrite8 (PcdGet8 (PcdUsb3DebugPortBusIndex), UsbDebugPort.PciAddress.Bus);
  CmosWrite8 (PcdGet8 (PcdUsb3DebugPortDeviceIndex), UsbDebugPort.PciAddress.Device);
  CmosWrite8 (PcdGet8 (PcdUsb3DebugPortFunctionIndex), UsbDebugPort.PciAddress.Function);
  return TRUE;
}
