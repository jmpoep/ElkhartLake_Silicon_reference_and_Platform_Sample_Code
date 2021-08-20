/** @file

Platform Nv RAM Hook Library Header Definition which will oprovide the absraction
to the different NVRAM types like eMMC, ECRAM, secondary SPI part etc.

@copyright
INTEL CONFIDENTIAL
Copyright (c) 2017 - 2019 Intel Corporation. All rights reserved

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

#ifndef _PLATFORM_NVRAM_HOOK_LIB_H_
#define _PLATFORM_NVRAM_HOOK_LIB_H_

#ifndef DEFAULT_VALUE
#define DEFAULT_VALUE         0
#endif

/**
  Test to see if Checksum is bad.

  @retval   TRUE  - Checksum content is bad
            FALSE - Checksum content is good
**/
BOOLEAN
IsChecksumBad (
  VOID
  );

/**
  Clear Diagnostic Status.
**/
VOID
ClearDiagnosticStatus (
  VOID
  );

/**
  Check to reset setup variable and Clear CMOS 0E when CMOS content is bad

  @retval Flag to Reset Setup variable :  TRUE  - When CMOS content is bad
                                          FALSE - Otherwise
**/
BOOLEAN
NeedResetBoardDefaultVariableHob(
  VOID
  );

/**
  Load CMOS default on RTC battery failure.
**/
VOID
SecondaryNvRamInit(
  VOID
  );

/**
  Get Boot Flag Status.

  @retval Value of current boot status
**/
UINT8
GetBootFlagStatus(
  VOID
  );

/**
  Update Boot Flag Status.

  @param [in] BootStatus   Current Boot value which to be updated.
**/
VOID
UpdateBootFlagStatus(
  UINT8  BootStatus
  );

/**
  Get RTC 3 Address.

  @retval Current value of RTC 3 Address
**/
UINT8
GetRtc3Address(
  VOID
  );
/**
  Get Post Code Break for Port 80 and 81

  @param [out] *Port80   Pointer to return value of post code 80

  @param [out] *Port81   Pointer to return value of post code 81
**/
VOID
GetPostCodeBreak(
  UINT8 *Port80,
  UINT8 *Port81
);

/**
  Get TXT Alias Check Request and Reset it.

  @retval TXT Alias Check Request
**/
UINT8
GetTxtAliasCheckAndReset(
  VOID
  );

/**
  Save the TXT Alias Check Request.

  @param [in] ACheckRequest   Request of TXT Alias Check.
**/
VOID
SaveTxtAliasCheck(
  UINT8  ACheckRequest
  );

/**
  Save the CPU Ratio.

  @param [in] CpuRatio   The Cpu ratio value to be saved.
**/
VOID
SaveCpuRatio(
  UINT8  CpuRatio
  );

/**
  Set the BCLK Ramp Flag.

  @param [in] BclkRampFlag   The BCLK Ramp Flag to be set.
**/
VOID
SetBclkRampFlag(
  UINT8  BclkRampFlag
  );


/**
  Get TBT Host Router Status.

  CMOS_TBTHR_PRESENT_ON_RESUME: Bits 0-3 is for DTBT and Bits 4-7 is for ITBT (HIA0/1/2/Reserved)

  @retval Current value of TBT Host Router Status
**/
UINT8
GetTbtHostRouterStatus(
  VOID
  );

/**
  Save TBT Host Router Status.

  CMOS_TBTHR_PRESENT_ON_RESUME: Bits 0-3 is for DTBT and Bits 4-7 is for ITBT (HIA0/1/2/Reserved)

  @param [in] TbtHrStatus   The TBT Host Router Status to be udpated.
**/
VOID
SaveTbtHostRouterStatus(
  UINT8  TbtHrStatus
  );
#endif // _PLATFORM_NVRAM_HOOK_LIB_H_
