/** @file
  VBIOS DXE policy definitions

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2016 Intel Corporation.

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
#ifndef _VBIOS_DXE_CONFIG_H_
#define _VBIOS_DXE_CONFIG_H_

#pragma pack(push, 1)

#define VBIOS_DXE_CONFIG_REVISION 1

/**
  This data structure includes Hybrid Graphics VBIOS configuration.
  If Hybrid Graphics feature is not supported, all the policies in this configuration block can be ignored.
  The data elements should be initialized by a Platform Module.\n
  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;              ///< Offset 0-27 Config Block Header
  UINT8                 LoadVbios    : 1;    ///< Offset 28:0 :This field is used to describe if the dGPU VBIOS needs to be loaded: <b>0=Not load</b>, 1=Load
  UINT8                 ExecuteVbios : 1;    ///< Offset 28:1 :This field is used to describe if the dGPU VBIOS need to be executed: <b>0=Not execute</b>, 1=Execute
/**
  Offset 28:2 :
  This field is used to identify the source location of dGPU VBIOS\n
  <b>1 = secondary display device VBIOS Source is PCI Card</b>\n
  0 = secondary display device VBIOS Source is FW Volume\n
**/
  UINT8                 VbiosSource  : 1;
  UINT8                 RsvdBits0    : 5;    ///< Offset 28:3 Reserved for future use
  UINT8                 Rsvd[3];             ///< Offset 29 : Reserved for DWORD alignment
} VBIOS_DXE_CONFIG;
#pragma pack(pop)

#endif // _VBIOS_DXE_CONFIG_H_
