/** @file
  Lock down policy

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
#ifndef _LOCK_DOWN_CONFIG_H_
#define _LOCK_DOWN_CONFIG_H_

#define LOCK_DOWN_CONFIG_REVISION 1
extern EFI_GUID gLockDownConfigGuid;

#pragma pack (push,1)

/**
  The PCH_LOCK_DOWN_CONFIG block describes the expected configuration of the PCH
  for security requirement.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                   ///< Config Block Header
  /**
    <b>(Test)</b> Enable SMI_LOCK bit to prevent writes to the Global SMI Enable bit. 0: Disable; <b>1: Enable</b>.
  **/
  UINT32  GlobalSmi      :  1;
  /**
    <b>(Test)</b> Enable BIOS Interface Lock Down bit to prevent writes to the Backup Control Register
    Top Swap bit and the General Control and Status Registers Boot BIOS Straps.
    Intel strongly recommends that BIOS sets the BIOS Interface Lock Down bit. Enabling this bit
    will mitigate malicious software attempts to replace the system BIOS with its own code.
    0: Disable; <b>1: Enable</b>.
  **/
  UINT32  BiosInterface  :  1;
  /**
    Enable the BIOS Lock Enable (BLE) feature and set EISS bit (D31:F5:RegDCh[5])
    for the BIOS region protection. When it is enabled, the BIOS Region can only be
    modified from SMM.
    If this EISS bit is set, then WPD must be a '1' and InSMM.STS must be '1' also
    in order to write to BIOS regions of SPI Flash. If this EISS bit is clear,
    then the InSMM.STS is a don't care.
    The BIOS must set the EISS bit while BIOS Guard support is enabled.
    In recovery path, platform can temporary disable EISS for SPI programming in
    PEI phase or early DXE phase.
    When PcdSmmVariableEnable is FALSE, to support BIOS regions update outside of SMM,
    the BiosLock must be set to Disabled by platform.
    0: Disable; <b>1: Enable.</b>
  **/
  UINT32  BiosLock       :  1;
  /**
    <b>(Test)</b> This test option when set will force all GPIO pads to be unlocked
    before BIOS transitions to POSTBOOT_SAI. This option should not be enabled in production
    configuration and used only for debug purpose when free runtime reconfiguration of
    GPIO pads is needed.
    <b>0: Disable</b>; 1: Enable.
  **/
  UINT32  UnlockGpioPads :  1;
  UINT32  RsvdBits0      : 28;             ///< Reserved bits
} PCH_LOCK_DOWN_CONFIG;

#pragma pack (pop)

#endif // _LOCK_DOWN_CONFIG_H_
