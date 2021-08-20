/** @file
  This file provides Tsn public library

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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
#ifndef _TSN_LIB_H_
#define _TSN_LIB_H_

/**
  Check whether TSN controller is enabled in the platform.

  @retval TRUE                    GbE is enabled
  @retval FALSE                   GbE is disabled
**/
BOOLEAN
IsTsnPresent (
  VOID
  );

/**
  Get Tsn PCI device number

  @retval PCI dev number
**/
UINT8
PchTsnDevNumber (
  VOID
  );

/**
  Get Pch Tsn PCI function number

  @retval PCI fun number
**/
UINT8
PchTsnFuncNumber (
  VOID
  );

/**
  Get PSE Tsn PCI device number

  @retval PCI dev number
**/
UINT8
PseTsnDevNumber (
  IN UINT8       PseTsnIndex
  );

/**
  Get PSE Tsn PCI function number

  @retval PCI fun number
**/
UINT8
PseTsnFuncNumber (
  IN UINT8       PseTsnIndex
  );

/**
  Check whether PSE TSN controller is present in the platform.

  @retval TRUE                    TSN is enabled
  @retval FALSE                   TSN is disabled
**/
BOOLEAN
IsPseTsnPresent (
  IN UINT8       PseTsnIndex
  );
#endif // _TSN_LIB_H_
