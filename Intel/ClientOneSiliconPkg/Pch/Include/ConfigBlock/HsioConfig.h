/** @file
  HSIO policy

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
#ifndef _HSIO_CONFIG_H_
#define _HSIO_CONFIG_H_

#define HSIO_CONFIG_REVISION 1
extern EFI_GUID gHsioConfigGuid;

#pragma pack (push,1)

/**
  The PCH_HSIO_CONFIG block provides HSIO message related settings.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;         ///< Config Block Header
  /**
    Policy used to point to the Base (+ OEM) ChipsetInit binary used to sync between BIOS and CSME
  **/
  UINT32    ChipsetInitBinPtr;
  /**
    Policy used to indicate the size of the Base (+ OEM) ChipsetInit binary used to sync between BIOS and CSME
  **/
  UINT32    ChipsetInitBinLen;
} PCH_HSIO_CONFIG;

#pragma pack (pop)

#endif // _HSIO_CONFIG_H_
