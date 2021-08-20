/** @file
TBT DXE Policy

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#ifndef _DXE_DTBT_POLICY_PROTOCOL_H_
#define _DXE_DTBT_POLICY_PROTOCOL_H_

#include <DxeTbtCommonDefinition.h>
#include <DTbtDefinition.h>

#pragma pack(push, 1)

#define DXE_DTBT_POLICY_REVISION 1

//
// DTBT Generic Data Structure
//
typedef struct _DXE_DTBT_GENERIC_CONFIG{
  /**
    TBT Security Level
    <b>0: SL0 No Security</b>, 1: SL1 User Authorization, 2: SL2 Secure Connect, 3: SL3 Display Port and USB
  **/
  UINT32   SecurityMode      : 3;
  /**
    BIOS W/A for Hot plug of 12V USB devices cause electrical noise on PCH GPIOs
    <b>0: Disabled</b>, 1: Enabled
  **/
  UINT32   Gpio5Filter       : 1;
  /**
     WA for TR A0 OS_UP Command, it is only needed for TR A0 stepping
    <b>0: Disabled</b>, 1: Enabled
  **/
  UINT32   TrA0OsupWa        : 1;
  /**
    TBT Dynamic AC/DC L1.
    <b>0: Disabled</b>, 1: Enabled
  **/
  UINT32   TbtAcDcSwitch     : 1;
  /**
  Send Go2SxNoWake or GoSxWake according to TbtWakeupSupport before entering Sx (x= 3,4) state
  <b>0: Disabled, send Go2SxNoWake </b>, 1: Enabled, send Go2SxWake
  **/
  UINT32   TbtWakeupSupport : 1;
} DXE_DTBT_GENERIC_CONFIG;

/**
 DTBT DXE configuration\n
  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct _DXE_DTBT_POLICY_PROTOCOL {
  TBT_COMMON_CONFIG       TbtCommonConfig;                                  ///< Tbt Common Information
  DXE_DTBT_GENERIC_CONFIG DTbtGenericConfig;                                ///< dTbt Generic Information
  TBT_RESOURCE_CONFIG     DTbtResourceConfig[MAX_DTBT_CONTROLLER_NUMBER];   ///< dTbt Resource Configuration
} DXE_DTBT_POLICY_PROTOCOL;

#pragma pack(pop)

#endif
