/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2017 Intel Corporation.

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

//
//
// ----------------------------------------------------------------------------
//
// Name:  DxeOverClockLib.h
//
// Description:  OverClock Library function prototypes are defined here
//
// ----------------------------------------------------------------------------
//
//
#ifndef __DxeOverClockLib__H__
#define __DxeOverClockLib__H__
#ifdef __cplusplus
extern "C"
{
#endif

#define END_OF_TABLE    0xFF

//
// Define function prototypes
//
UINT8
ConvertPowerLimit1TimeMSRtoSeconds (
  IN UINT8 MSRTime
  )
/*++

Routine Description:


Arguments:

  None

Returns:


--*/
;


UINT8
MaxTurboRatio_Factoryvalue (
  VOID
  )
/*++

Routine Description:


Arguments:

  None

Returns:


--*/
;

UINT8
MaxNonTurboRatio_Factoryvalue (
  VOID
  )
/*++

Routine Description:


Arguments:

  None

Returns:


--*/
;

UINT8
MaxEfficiencyRatio_factory (
  VOID
  )
/*++

Routine Description:


Arguments:

  None

Returns:


--*/
;

VOID
ReadTurboValues (
  IN OUT  UINT16          *TurboPower,
  IN OUT  UINT16          *TurboCurrent,
  IN OUT  UINT8           *CoreRatio1,
  IN OUT  UINT8           *CoreRatio2,
  IN OUT  UINT8           *CoreRatio3,
  IN OUT  UINT8           *CoreRatio4,
  IN OUT  UINT8           *CoreRatio5,
  IN OUT  UINT8           *CoreRatio6,
  IN OUT  UINT8           *CoreRatio7,
  IN OUT  UINT8           *CoreRatio8,
  IN OUT  UINT16          *PowerLimit1,
  IN OUT  UINT16          *PowerLimit2,
  IN OUT  UINT8           *PowerLimit1Time
  )
/*++

Routine Description:


Arguments:


Returns:


--*/
;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
