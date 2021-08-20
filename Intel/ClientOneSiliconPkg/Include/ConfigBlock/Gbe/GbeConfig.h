/** @file
  Gigabit Ethernet policy

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2018 Intel Corporation.

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
#ifndef _GBE_CONFIG_H_
#define _GBE_CONFIG_H_

#define GBE_CONFIG_REVISION 1
extern EFI_GUID gGbeConfigGuid;

#pragma pack (push,1)

/**
  PCH intergrated GBE controller configuration settings.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;  ///< Config Block Header
  /**
    Determines if enable PCH internal GBE, 0: Disable; <b>1: Enable</b>.
    When Enable is changed (from disabled to enabled or from enabled to disabled),
    it needs to set LAN Disable regsiter, which might be locked by FDSWL register.
    So it's recommendated to issue a global reset when changing the status for PCH Internal LAN.
  **/
  UINT32  Enable          :  1;
  UINT32  LtrEnable       :  1;  ///< <b>0: Disable</b>; 1: Enable LTR capabilty of PCH internal LAN.
  UINT32  RsvdBits0       : 30;  ///< Reserved bits
} GBE_CONFIG;

#pragma pack (pop)

#endif // _GBE_CONFIG_H_
