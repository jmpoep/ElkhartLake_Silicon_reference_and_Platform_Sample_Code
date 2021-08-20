/** @file
  ITBT Policy definition to be referred in both PEI and DXE phase.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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

#ifndef _ITBT_POLICY_GENERIC_H_
#define _ITBT_POLICY_GENERIC_H_

#pragma pack(push, 1)

//
// iTBT RootPort Data Structure
//
typedef struct _ITBT_ROOTPORT_CONFIG{
  UINT8  ITbtPcieRootPortEn;            ///< Disable/Enable iTBT PCIe Root Port
  UINT8  Reserved[3];                   ///< Reserved for DWORD alignment
} ITBT_ROOTPORT_CONFIG;

//
// ITBT Controller Data Structure to be used cross to RP and controller to be shared by CONFIG_BLOCK and HOB
//
typedef struct _ITBT_GENERIC_CONFIG{
  /**
    Timeout value for forcing power iTBT controller on every boot/reboot/Sx exit as a precondition for execution of following
    mailbox communication.
    After applying Force Power Thunderbolt BIOS shall poll for iTBT readiness for mailbox communication
    If TBT cable is disconnected, iTBT microcontrollers are in lower power state.
    To ensure successful mailbox execution, independently on presence of TBT cable, TBT BIOS shall bring iTBT
    microcontrollers up by applying Force Power. iTBT microcontrollers will wake up either due to TBT cable presence or
    Force Power event.
    <b>(Test)</b>
    <b> default is 500 ms </b>
  **/
  UINT16  ITbtForcePowerOnTimeoutInMs;
  /**
    Timeout value while sending connect topology mailbox command in order to bring all connected TBT devices are available
    on PCIe before BIOS will enumerate them in BDS
    <b>(Test)</b>
    <b> default is 5000 ms </b>
  **/
  UINT16  ITbtConnectTopologyTimeoutInMs;
  /**
    By default the iTBT controller is configured to "No Security" (SL0). Platform may change appropriate security level via
    policy
    0: SL0 - No Security Allow legacy Thunderbolt devices auto connect - at this mode the connection manager auto
    connects to a new device plugged in
    1: SL1 - User Authorization Allow User Notification devices at minimum - at this mode the
    connection manager requests connection approval from the host SW, auto approval may be given based on the Unique ID of
    the connecting device
    2: SL2 - Secure Connect Allow One time saved key devices at minimum -  at this mode the
    connection manager requests connection approval from the host SW, auto approval is only given if the host challenge
    to the device is acceptable
    3: SL3 - Display Port and USB only Allow only DP sinks to be connected (re-driver or DP tunnel, no
    PCIe tunneling) on TBT hierarchy -  at this mode no tunneling is done for PCIe devices
    <b> default is 0 </b>
  **/
  UINT8   ITbtSecurityLevel;            ///< iTbt Security Level
  UINT8   Reserved[3];                  ///< Reserved for DWORD alignment
} ITBT_GENERIC_CONFIG;

#pragma pack(pop)

#endif
