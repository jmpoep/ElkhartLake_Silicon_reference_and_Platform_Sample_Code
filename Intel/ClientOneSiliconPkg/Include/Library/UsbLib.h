/** @file
  Header file of available functions in general USB Library

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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

#ifndef _USB_LIB_H_
#define _USB_LIB_H_

#include <Uefi/UefiBaseType.h>

/*
  Disables requested ports through Port Disable Override register programming

  @param[in]  XhciMmioBase        xHCI Memory BAR0 address
  @param[in]  Usb2DisabledPorts   Disabled ports bitmask with a bit for each USB2 port
                                  i.e. BIT0 is Port 0, BIT1 is Port 1 etc
  @param[in]  Usb3DisabledPorts   Disabled ports bitmask with a bit for each USB3 port
                                  i.e. BIT0 is Port 0, BIT1 is Port 1 etc

  @retval EFI_SUCCESS             Programming ended successfully and no errors occured
          EFI_ACCESS_DENIED       Port Disable Override register was locked and write
                                  didn't go through. Platform may require restart to unlock.
*/
EFI_STATUS
UsbDisablePorts (
  IN  UINTN   XhciMmioBase,
  IN  UINT32  Usb2DisabledPorts,
  IN  UINT32  Usb3DisabledPorts
  );

#endif // _USB_LIB_H
