/** @file
  MEBx Data Hob

@copyright
  INTEL CONFIDENTIAL
  Copyright 2005 - 2017 Intel Corporation.

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
#ifndef _MEBX_DATA_HOB_H_
#define _MEBX_DATA_HOB_H_

#define MNT_OFF     0x00
#define MNT_ON      0x01
#define SOL_ENABLE  0x01
#define KVM_ENABLE  0x01

#pragma pack (1)
///
/// Data Hob for storing Intel MEBX setting to pass it from PEI to DXE phase.
///
typedef struct {
  UINT8   PlatformMngSel;                      ///< Platform Manageability Selection. 0: Disabled; 1: Enabled
  UINT8   AmtSol;                              ///< Sol State. 0: Disabled; 1: Enabled
  UINT8   RemoteAssistanceTriggerAvailablilty; ///< Cira Feature. 0: Disabled; 1: Enabled
  UINT8   KvmEnable;                           ///< Kvm State. 0: Disabled; 1: Enabled
} MEBX_DATA_HOB;

#pragma pack ()

#endif
