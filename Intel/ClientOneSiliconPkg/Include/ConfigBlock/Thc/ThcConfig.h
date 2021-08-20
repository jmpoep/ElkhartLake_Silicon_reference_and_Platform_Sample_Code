/** @file
  Touch Host Controller policy.

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

#ifndef _THC_CONFIG_H_
#define _THC_CONFIG_H_

#define THC_CONFIG_REVISION 1
extern EFI_GUID gThcConfigGuid;

#pragma pack (push,1)

/**
  Available Port Assignments

**/
typedef enum {
  ThcAssignmentNone, ///< None of the avaialbe controllers assigned
  ThcAssignmentThc0, ///< Port assigned to THC0
  ThcAssignmentThc1  ///< Port assigned to THC1
} THC_PORT_ASSIGNMENT;


/**
  Port Configuration structure required for each Port that THC might use.

**/
typedef struct {
  UINT32 Assignment;         ///< Sets THCx assignment see THC_PORT_ASSIGNMENT
  UINT32 InterruptPinMuxing; ///< Each GPIO PORTx/SPIx INTB Pin has different muxing options refer to GPIO_*_MUXING_THC_SPIx_*
} THC_PORT;

/**
  THC_CONFIG block provides the configurations forTouch Host Controllers

  Assignment field in each THC port controlls the THC behavior.

  Available scenarios:
  1: Single Port 0 used by THC0
      - THC0 Enabled
      - Port0 assigned to THC0
      - Port1 unassigned
      - THC1 will be automatically Disabled.
  2: Both ports used by THC0
      - THC0 Enabled
      - Port0 assigned to THC0
      - Port1 assigned to THC0
      - THC1 will be automatically Disabled.
  3: Port 0 used by THC0 and Port 1 used by THC1
      - THC0 Enabled
      - Port0 assigned to THC0
      - THC1 Enabled
      - Port1 assigned to THC1.
<b>4: Both Ports unassigned.</b>
      Both THC Controllers will be disabled in that case.

  @note
  Invalid scenario that will cause ASSERT.
  1. Same port Number assigned to THC0 or THC1.
  2. Two Ports assigned to THC1.

**/
typedef struct {
  CONFIG_BLOCK_HEADER  Header;           ///< Config Block Header
  THC_PORT             ThcPort[2];       ///< Port Configuration
} THC_CONFIG;

#pragma pack (pop)

#endif // _THC_CONFIG_H_
