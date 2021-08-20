/** @file
TBT Policy Common definition.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 Intel Corporation.

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

#ifndef _DTBT_POLICY_GENERIC_H_
#define _DTBT_POLICY_GENERIC_H_

#include <Library/GpioLib.h>
#include <IndustryStandard/Pci22.h>

#pragma pack(push, 1)

//
// dTBT Force Power GPIO Data Structure
//
typedef struct _DTBT_FORCE_POWER_GPIO_CONFIG {
  GPIO_PAD       GpioPad;                 ///< GPIO Pad Number
  BOOLEAN        GpioLevel;               ///< 0 = Active Low; 1 = Active High
  UINT8          Reserved[3];             ///< Reserved for DWORD alignment
} DTBT_FORCE_POWER_GPIO_CONFIG;

//
// dTBT CIO Plug Event GPIO Data Structure
//
typedef struct _DTBT_CIO_PLUG_EVENT_GPIO_CONFIG {
  GPIO_PAD       GpioPad;                 ///< GPIO Pad Number
  UINT32         AcpiGpeSignature;        ///< AcpiPlatform driver will change the XTBT method to the _Lxx or _Exx that we assign in this item.
  BOOLEAN        AcpiGpeSignaturePorting; ///< 0 = No porting required(for 2-tier GPI GPE event architecture), 1 = Porting required(for 1-tier GPI GPE event architecture)
  UINT8          Reserved[3];             ///< Reserved for DWORD alignment
} DTBT_CIO_PLUG_EVENT_GPIO_CONFIG;

//
// dTBT PCIE Reset GPIO Data Structure
//
typedef struct _DTBT_PCIE_RESET_GPIO_CONFIG {
  GPIO_PAD       GpioPad;                 ///< GPIO Pad Number
  BOOLEAN        GpioLevel;               ///< 0 = Active Low; 1 = Active High
  UINT8          Reserved[3];             ///< Reserved for DWORD alignment
} DTBT_PCIE_RESET_GPIO_CONFIG;

//
// dTBT Controller Data Structure
//
typedef struct _DTBT_CONTROLLER_CONFIG{
  UINT8                           DTbtControllerEn; ///< Enable/Disable DTbtController.
  UINT8                           Type;             ///< 01-Pcie RP, 02- PEG,Reserved. <Specific according to Board Design>
  UINT8                           PcieRpNumber;     ///< RP Number/ PEG Port (0,1,2) that connecet to dTBT controller. <Specific according to Board Design>
  DTBT_FORCE_POWER_GPIO_CONFIG    ForcePwrGpio;     ///< The GPIO pin that can force dTBT Power On. <Specific according to Board Design>
  DTBT_CIO_PLUG_EVENT_GPIO_CONFIG CioPlugEventGpio; ///< The GPIO pin that can generate Hot-Plug event. <Specific according to Board Design>
  DTBT_PCIE_RESET_GPIO_CONFIG     PcieRstGpio;      ///< The GPIO pin that is use to perform Reset when platform enters to Sx, it is required for platforms where PCI_RST pin connected to Tbt is controlled with GPIO <Specific according to Board Design>
  UINT8                           Reserved[1];      ///< Reserved for DWORD alignment
} DTBT_CONTROLLER_CONFIG;

//
// dTBT Controller Data Structure
//
typedef struct _DTBT_GENERIC_CONFIG{
  UINT8            TbtBootOn;                    ///< Send BootOn Mailbox command when TbtBootOn is enabled.
  UINT8            TbtUsbOn;                     ///< Send UsbOn Mailbox command when TbtBootOn is enabled.
  UINT8            Gpio3ForcePwr;                ///< Force GPIO to power on or not
  UINT16           Gpio3ForcePwrDly;             ///< The delay time after do ForcePwr
  BOOLEAN          DTbtSharedGpioConfiguration;  ///< Multiple DTBT controllers share the same GPIO pin <Specific according to Board Design>
  BOOLEAN          PcieRstSupport;               ///< 0 = Not Support, 1 = Supported. it is required for platforms where PCI_RST pin connected to Tbt is controlled with GPIO
  UINT8            Reserved[1];                  ///< Reserved for DWORD alignment
} DTBT_GENERIC_CONFIG;

#pragma pack(pop)

#endif
