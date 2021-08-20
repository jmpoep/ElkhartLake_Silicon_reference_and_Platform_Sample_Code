/** @file
  Policy details for miscellaneous configuration in System Agent

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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
#ifndef _SA_MISC_PEI_CONFIG_H_
#define _SA_MISC_PEI_CONFIG_H_

#pragma pack(push, 1)

#define SA_MISC_PEI_CONFIG_REVISION 1

///
/// Subsystem Vendor ID / Subsystem ID
///
typedef struct _SA_DEFAULT_SVID_SID{
  UINT16         SubSystemVendorId;
  UINT16         SubSystemId;
} SA_DEFAULT_SVID_SID;

/**
  This configuration block is to configure SA Miscellaneous variables during PEI Post-Mem.\n
  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER  Header;               ///< Offset 0-27 Config Block Header
  /**
  Offset 28:0
  This policy is used to control enable or disable System Agent Thermal device (0,4,0).
  <b>0=FALSE</b>,
  1=TRUE.
  **/
  UINT32  Device4Enable:1;

  UINT32  RsvdBits3 : 1;                     ///< Offset 28:1 Reserved for future use
  UINT32  RsvdBits0:1;                       ///< Offset 28:2 Reserved for future use
  UINT32  SkipPamLock:1;                     ///< Offset 28:3 :To skip PAM register locking. @note It is still recommended to set PCI Config space B0: D0: F0: Offset 80h[0]=1 in platform code even Silicon code skipped this.\n <b>0=All PAM registers will be locked in Silicon code</b>, 1=Skip lock PAM registers in Silicon code.
  UINT32  EdramTestMode:2;                   ///< Offset 28:4 :EDRAM Test Mode. For EDRAM stepping - 0- EDRAM SW Disable, 1- EDRAM SW Enable, <b> 2- EDRAM HW Mode</b>
  UINT32  RsvdBits1          :26;            ///< Offset 28:6 :Reserved for future use
} SA_MISC_PEI_CONFIG;
#pragma pack(pop)

#endif // _SA_MISC_PEI_CONFIG_H_
