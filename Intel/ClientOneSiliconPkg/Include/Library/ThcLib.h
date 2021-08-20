/** @file
  Touch Host Controller Library.
  All functions from this library are available in PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

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

#ifndef _THC_LIB_H_
#define _THC_LIB_H_
/**
  Returns Pci Config Base for THC

  @param[in] ThcNumber            THC0/THC1 0 or 1

  @retval    THC Pci base address
**/
UINT64
ThcGetPciConfigSpace (
  IN UINT8          ThcNumber
  );

/**
  Checks if the Intel Touch Host Controller is Enabled

  @param[in] ThcNumber            THC0/THC1 0 or 1

  @retval TRUE                    THC is enabled
  @retval FALSE                   THC PCI device not found
**/
BOOLEAN
ThcIsEnabled (
  IN UINT8          ThcNumber
  );

/**
  Checks if it is possible to enable Intel Touch Host Controller

  Thc Port 0 could be used by THC or Integrated Touch.
  If Integrated Touch is enabled, CSME will take over its GPIO.
  Based on the pad ownership BIOS decides if it is possible to enable THC

  @retval TRUE                    BIOS is capable of enabling THC
  @retval FALSE                   THC pins are taken over by some other IP. BIOS is unable to configure THC
**/
BOOLEAN
ThcIsSupported (
  VOID
  );

/**
  Returns Thc Device Number

  @param[in] ThcNumber            THC0/THC1 0 or 1

  @retval    Device Number
**/
UINT8
ThcGetDeviceNumber (
  IN UINT8          ThcNumber
  );

/**
  Returns Thc Function Number

  @param[in] ThcNumber            THC0/THC1 0 or 1

  @retval    Function Number
**/
UINT8
ThcGetFunctionNumber (
  IN UINT8          ThcNumber
  );
#endif //_THC_LIB_H_
