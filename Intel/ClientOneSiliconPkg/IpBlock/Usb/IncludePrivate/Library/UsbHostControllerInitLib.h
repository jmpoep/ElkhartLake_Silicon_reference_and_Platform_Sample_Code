/** @file
  Header file for USB Host Controller initialization library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 - 2020 Intel Corporation.

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
#ifndef _USB_HOST_CONTROLLER_INIT_LIB_H_
#define _USB_HOST_CONTROLLER_INIT_LIB_H_

#include <ConfigBlock.h>
#include <UsbConfig.h>

/**
  Locks xHCI configuration by setting the proper lock bits in controller

  @param[in]  UsbConfig           The USB_CONFIG policy instance
  @param[in]  XhciPciBase         xHCI PCI config space address
**/
VOID
XhciLockConfiguration (
  IN  USB_CONFIG      *UsbConfig,
  IN  UINT64          XhciPciBase
  );

/**
  Common entry point for PCH and CPU xHCI controller

  @param[in]  UsbConfig           The USB_CONFIG policy instance
  @param[in]  XhciPciMmBase       xHCI PCI config space address
**/
VOID
XhciConfigure (
  IN  USB_CONFIG      *UsbConfig,
  IN  UINT64          XhciPciBase
  );

/**
  Configure USB OTG

  @param[in]  UsbConfig           The USB_CONFIG policy instance
**/
VOID
UsbConfigureOtg (
  IN  USB_CONFIG      *UsbConfig
  );
#endif // _USB_INIT_LIB_H_
