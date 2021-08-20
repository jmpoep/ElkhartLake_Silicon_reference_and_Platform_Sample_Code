/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2017 Intel Corporation.

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

//
//
// ----------------------------------------------------------------------------
//
// Name:  DxeOverClockLib.c
//
// Description:  This file contains library functions
//
// ----------------------------------------------------------------------------
//
//

#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>
#include <Library/CpuMailboxLib.h>
#include "DxeOverClockLib.h"
#define MSR_PLATFORM_INFO                   0xCE
#define MAX_NON_TURBO_RATIO_OFFSET          8
#define MAX_NON_TURBO_RATIO_MASK            0xff
#define MAX_EFFICIENCY_RATIO_MASK           0xff
#define MAX_EFFICIENCY_RATIO_OFFSET         40

#define MSR_TURBO_RATIO_LIMIT               0x1ad
#define MAX_RATIO_LIMIT_8C_OFFSET           56
#define MAX_RATIO_LIMIT_7C_OFFSET           48
#define MAX_RATIO_LIMIT_6C_OFFSET           40
#define MAX_RATIO_LIMIT_5C_OFFSET           32
#define MAX_RATIO_LIMIT_4C_OFFSET           24
#define MAX_RATIO_LIMIT_3C_OFFSET           16
#define MAX_RATIO_LIMIT_2C_OFFSET           8
#define MAX_RATIO_LIMIT_1C_OFFSET           0
#define MAX_RATIO_LIMIT_1C_MASK             0x00000000000000ff
#define MAX_RATIO_LIMIT_2C_MASK             0x000000000000ff00
#define MAX_RATIO_LIMIT_3C_MASK             0x0000000000ff0000
#define MAX_RATIO_LIMIT_4C_MASK             0x00000000ff000000
#define MAX_RATIO_LIMIT_5C_MASK             0x000000ff00000000
#define MAX_RATIO_LIMIT_6C_MASK             0x0000ff0000000000
#define MAX_RATIO_LIMIT_7C_MASK             0x00ff000000000000
#define MAX_RATIO_LIMIT_8C_MASK             0xff00000000000000

#define MSR_PACKAGE_POWER_SKU_UNIT              0x606
#define PACKAGE_POWER_UNIT_MASK     0xF
#define PACKAGE_MAX_POWER_MASK              ((UINT64) 0x7FFF << 32)
#define PACKAGE_MAX_POWER_OFFSET            32
#define PACKAGE_MIN_POWER_MASK              (0x7FFF << 16)
#define PACKAGE_MIN_POWER_OFFSET            16
#define PACKAGE_TDP_POWER_MASK              (0x7FFF)

#define MSR_TURBO_POWER_LIMIT                   0x610
#define POWER_LIMIT_MASK                    (0x7FFF)    // Bits 14:0 and 46:32
#define POWER_LIMIT_1_MASK                  (0x7FFF)    // Bits 14:0
#define POWER_LIMIT_2_MASK                  ((UINT64) 0x7FFF << 32) // Bits 46:32
#define POWER_LIMIT_2_OFFSET                32
#define POWER_LIMIT_1_TIME_MASK             0xFE0000    // Bits 23:17
#define POWER_LIMIT_1_TIME_OFFSET           17

#define MSR_PACKAGE_POWER_SKU                 0x614
#define MAILBOX_TYPE_OC                       0x00000002
#define OC_LIB_CMD_GET_FUSED_P0_RATIO_VOLTAGE 0x07

///
/// Table to convert Seconds into equivalent MSR values
/// This table is used for TDP Time Window programming
///
GLOBAL_REMOVE_IF_UNREFERENCED UINT8 mSecondsToMsrValueMapTable[][2] = {
  ///
  ///  Seconds,    MSR Value
  ///
  {        1,         0x0A     },
  {        2,         0x0B     },
  {        3,         0x4B     },
  {        4,         0x0C     },
  {        5,         0x2C     },
  {        6,         0x4C     },
  {        7,         0x6C     },
  {        8,         0x0D     },
  {       10,         0x2D     },
  {       12,         0x4D     },
  {       14,         0x6D     },
  {       16,         0x0E     },
  {       20,         0x2E     },
  {       24,         0x4E     },
  {       28,         0x6E     },
  {       32,         0x0F     },
  {       40,         0x2F     },
  {       48,         0x4F     },
  {       56,         0x6F     },
  {       64,         0x10     },
  {       80,         0x30     },
  {       96,         0x50     },
  {      112,         0x70     },
  {      128,         0x11     },
  { END_OF_TABLE, END_OF_TABLE }
};

//
//
// ----------------------------------------------------------------------------
// Procedure: ConvertPowerLimit1TimeMSRtoSeconds
//
// Description: Converts from CPU units to seconds
//
// Input: UINT8
//
// Output: UINT8
//
// ----------------------------------------------------------------------------
//
//
UINT8 ConvertPowerLimit1TimeMSRtoSeconds (
  IN UINT8 MSRTime
  )
  /*++

  Routine Description:


  Arguments:

    None

  Returns:


  --*/
{
  UINT8 Seconds;
  UINT8 Index;

  Seconds = mSecondsToMsrValueMapTable[0][0];
  for (Index = 0; mSecondsToMsrValueMapTable[Index][0] != END_OF_TABLE; Index++) {
    if (MSRTime == mSecondsToMsrValueMapTable[Index][1]) {
      Seconds = mSecondsToMsrValueMapTable[Index][0];
      break;
    }
  }
  return Seconds;
}

//
//
// ----------------------------------------------------------------------------
// Procedure: MaxTurboRatio_Factoryvalue
//
// Description: Read the Factory Configured Turbo Ratio.
//
// Input:
//
// Output: UINT8
//
//
// ----------------------------------------------------------------------------
//
//
UINT8
MaxTurboRatio_Factoryvalue (
  VOID
  )
/*++

Routine Description:


Arguments:

  None

Returns:


--*/
{
  EFI_STATUS Status;
  UINT32 Data;
  UINT32 MailboxStatus;
  UINT8 Ratio;
  ///
  /// Read the Fused P0 ratio from OC mailbox
  ///
  Status = MailboxRead(MAILBOX_TYPE_OC, OC_LIB_CMD_GET_FUSED_P0_RATIO_VOLTAGE, &Data , &MailboxStatus);
  if (EFI_ERROR(Status) || (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS)) {
    DEBUG ((DEBUG_ERROR, "OC: Error in Fused P0 Ratio Voltage command. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
    Ratio = 0;
  } else {
    Ratio = (UINT8)(Data & 0xFF);
    DEBUG ((DEBUG_INFO, "OC: Fused P0 Ratio = 0x%X\n", Ratio));
  }
  return Ratio;
}

//
//
// ----------------------------------------------------------------------------
// Procedure: MaxNonTurboRatio_Factoryvalue
//
// Description: Read the Factory Configured Default Non Turbo Ratio.
//
// Input:
//
// Output: UINT8
//
//
// ----------------------------------------------------------------------------
//
//
UINT8
MaxNonTurboRatio_Factoryvalue (
  VOID
  )
/*++

Routine Description:


Arguments:

  None

Returns:


--*/
{
  //
  // MSR 0CE Bit[8-15]
  //
  UINT8   MaxNonTurboRatio;
  UINT64  PlatformInfo;

  PlatformInfo = AsmReadMsr64 (MSR_PLATFORM_INFO);
  MaxNonTurboRatio = (UINT8) (((UINT32) (UINTN) RShiftU64 (PlatformInfo, MAX_NON_TURBO_RATIO_OFFSET)) & MAX_NON_TURBO_RATIO_MASK);
  return MaxNonTurboRatio;
}
//
//
// ----------------------------------------------------------------------------
// Procedure: MaxEfficiencyRatio_factory
//
// Description: Read the Factory Configured Default MaxEfficiencyRatio (Minimum Ratio)
//
// Input:
//
// Output: UINT8
//
// ----------------------------------------------------------------------------
//
//
UINT8
MaxEfficiencyRatio_factory (
  VOID
  )
/*++

Routine Description:


Arguments:

  None

Returns:


--*/
{
  //
  // MSR 0CE Bit[40-47]
  //
  UINT8   MaxEfficiencyRatio;
  UINT64  PlatformInfo;

  PlatformInfo        = AsmReadMsr64 (MSR_PLATFORM_INFO);
  MaxEfficiencyRatio  = (UINT8) RShiftU64 (PlatformInfo, MAX_EFFICIENCY_RATIO_OFFSET) & MAX_EFFICIENCY_RATIO_MASK;
  return MaxEfficiencyRatio;
}

//
//
// ----------------------------------------------------------------------------
// Procedure: ReadTurboValues
//
// Description: Read the Factory Configured Default Turbo Related Ratios
//         (TDC, TDP, CoreRatio1, CoreRatio2, CoreRatio3, CoreRatio4)
//
// Input:
//
// Output:
//
// ----------------------------------------------------------------------------
//
//
VOID
ReadTurboValues (
  IN OUT  UINT16          *TurboPower,
  IN OUT  UINT16          *TurboCurrent,
  IN OUT  UINT8           *CoreRatio1,
  IN OUT  UINT8           *CoreRatio2,
  IN OUT  UINT8           *CoreRatio3,
  IN OUT  UINT8           *CoreRatio4,
  IN OUT  UINT8           *CoreRatio5,
  IN OUT  UINT8           *CoreRatio6,
  IN OUT  UINT8           *CoreRatio7,
  IN OUT  UINT8           *CoreRatio8,
  IN OUT  UINT16          *PowerLimit1,
  IN OUT  UINT16          *PowerLimit2,
  IN OUT  UINT8           *PowerLimit1Time
  )
/*++

Routine Description:


Arguments:


Returns:


--*/
{
  UINT64  TurboPowerCurrentLimit;
  UINT64  TurboPowerSKU;
  UINT64  CoreRatioLimit;
  UINT8   PowerUnit;
  UINT16  TDPLimit;

  TurboPowerCurrentLimit  = AsmReadMsr64 (MSR_TURBO_POWER_LIMIT);
  TurboPowerSKU           = AsmReadMsr64 (MSR_PACKAGE_POWER_SKU_UNIT);

  PowerUnit               = (UINT8)(TurboPowerSKU & PACKAGE_POWER_UNIT_MASK);
  PowerUnit               = (UINT8) LShiftU64 (2, (PowerUnit - 1));
  TDPLimit                = (UINT16) DivU64x32 ((TurboPowerCurrentLimit & POWER_LIMIT_MASK), PowerUnit);

  *PowerLimit1            = (UINT16) (TurboPowerCurrentLimit & POWER_LIMIT_1_MASK);
  *PowerLimit2            = (UINT16) (RShiftU64((TurboPowerCurrentLimit & POWER_LIMIT_2_MASK), POWER_LIMIT_2_OFFSET));

  *PowerLimit1            = (UINT16) DivU64x32 (*PowerLimit1, PowerUnit);
  *PowerLimit2            = (UINT16) DivU64x32 (*PowerLimit2, PowerUnit);

  CoreRatioLimit          = AsmReadMsr64 (MSR_TURBO_RATIO_LIMIT);

  *TurboPower             = TDPLimit;
  *TurboCurrent           = 0;

  *CoreRatio1             = (UINT8) (CoreRatioLimit & MAX_RATIO_LIMIT_1C_MASK);
  *CoreRatio2             = (UINT8) (RShiftU64((CoreRatioLimit & MAX_RATIO_LIMIT_2C_MASK), MAX_RATIO_LIMIT_2C_OFFSET));
  *CoreRatio3             = (UINT8) (RShiftU64((CoreRatioLimit & MAX_RATIO_LIMIT_3C_MASK), MAX_RATIO_LIMIT_3C_OFFSET));
  *CoreRatio4             = (UINT8) (RShiftU64((CoreRatioLimit & MAX_RATIO_LIMIT_4C_MASK), MAX_RATIO_LIMIT_4C_OFFSET));
  *CoreRatio5             = (UINT8) (RShiftU64((CoreRatioLimit & MAX_RATIO_LIMIT_5C_MASK), MAX_RATIO_LIMIT_5C_OFFSET));
  *CoreRatio6             = (UINT8) (RShiftU64((CoreRatioLimit & MAX_RATIO_LIMIT_6C_MASK), MAX_RATIO_LIMIT_6C_OFFSET));
  *CoreRatio7             = (UINT8) (RShiftU64((CoreRatioLimit & MAX_RATIO_LIMIT_7C_MASK), MAX_RATIO_LIMIT_7C_OFFSET));
  *CoreRatio8             = (UINT8) (RShiftU64((CoreRatioLimit & MAX_RATIO_LIMIT_8C_MASK), MAX_RATIO_LIMIT_8C_OFFSET));

  *PowerLimit1Time        = ConvertPowerLimit1TimeMSRtoSeconds(
                                (UINT8) (RShiftU64(((UINT32) TurboPowerCurrentLimit & POWER_LIMIT_1_TIME_MASK), POWER_LIMIT_1_TIME_OFFSET))
                               );
}
