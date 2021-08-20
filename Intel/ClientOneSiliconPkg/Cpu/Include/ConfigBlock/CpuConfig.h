/** @file
  CPU Config Block.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2020 Intel Corporation.

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
#ifndef _CPU_CONFIG_H_
#define _CPU_CONFIG_H_

#define CPU_CONFIG_REVISION 1

extern EFI_GUID gCpuConfigGuid;

#pragma pack (push,1)

/**
  CPU Configuration Structure.

  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                   ///< Config Block Header
  /**
    Enable or Disable Advanced Encryption Standard (AES) feature.
    For some countries, this should be disabled for legal reasons.
    -    0: Disable
    - <b>1: Enable</b>
  **/
  UINT32 AesEnable           : 1;
  /**
    Enable or Disable Trusted Execution Technology (TXT) feature.
    -    0: Disable
    - <b>1: Enable</b>
  **/
  UINT32 TxtEnable           : 1;
  UINT32 SkipMpInit          : 1;                 ///< For Fsp only, Silicon Initialization will skip MP Initialization (including BSP) if enabled. For non-FSP, this should always be 0.
  /**
    Enable or Disable or Auto for PPIN Support to view Protected Processor Inventory Number.
    - <b>0: Disable</b>
    -    1: Enable
    -    2: Auto : Feature is based on End Of Manufacturing (EOM) flag. If EOM is set, it is disabled.
  **/
  UINT32 PpinSupport         : 2;
  /**
    Enable or Disable #AC machine check on split lock.
    - <b>0: Disable</b>
    -    1: Enable
  **/
  UINT32 AcSplitLock         : 1;
  UINT32 RsvdBits            : 26;                ///< Reserved for future use
  UINT32 MicrocodePatchRegionSize;
  EFI_PHYSICAL_ADDRESS MicrocodePatchAddress;     ///< Pointer to microcode patch that is suitable for this processor.
  UINT32               UfsStrapAddress;
} CPU_CONFIG;

#pragma pack (pop)

#endif // _CPU_CONFIG_H_
