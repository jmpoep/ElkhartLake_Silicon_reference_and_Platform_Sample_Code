/** @file
  Variable definition for overclocking support

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2017 Intel Corporation.

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
#ifndef _OC_SETUP_VARIABLE_H_
#define _OC_SETUP_VARIABLE_H_

#pragma pack(1)
typedef struct{
  UINT8  OcInterfaceRtUpdated;    // New added, used to indicate OC variable has been updated during RT.
  //
  // Sa setup
  //
  UINT8  tCL;
  UINT8  tRCDtRP;
  UINT16 tRAS;
  UINT8  tWR;
  UINT16 tRFC;
  UINT8  tRRD;
  UINT8  tWTR;
  UINT8  tRTP;
  UINT16 tFAW;
  UINT8  tWRDefault;
  UINT8  NModeSupport;
  UINT8  DdrRatioDefault;
  UINT8  DdrRatio;
  UINT16 MemoryVoltage;
  UINT8  BclkOverride;
  UINT32 BclkFrequency;
  UINT8  GtMaxOcRatio;
  UINT8  SpdProfileSelected;
  UINT8  DdrRefClk;
  UINT8  GtVoltageMode;
  UINT16 GtVoltageOffset;
  UINT8  GtVoltageOffsetPrefix;
  UINT16 GtVoltageOverride;
  UINT16 GtExtraTurboVoltage;
  UINT16 UncoreVoltageOffset;
  UINT8  UncoreVoltageOffsetPrefix;

  //
  // CPU Setup
  //
  UINT8  OverclockingSupport;
  UINT8  EnableGv;
  UINT8  CpuRatio;
  UINT8  CpuRatioOverride;
  UINT8  CoreMaxOcRatio;
  UINT8  CoreVoltageMode;
  UINT16 CoreVoltageOverride;
  UINT16 CoreExtraTurboVoltage;
  UINT16 CoreVoltageOffset;
  UINT8  CoreVoltageOffsetPrefix;
  UINT8  RingMaxOcRatio;
  UINT8  RingVoltageMode;
  UINT16 RingVoltageOverride;
  UINT16 RingExtraTurboVoltage;
  UINT16 RingVoltageOffset;
  UINT8  RingVoltageOffsetPrefix;
  UINT8  PowerLimit1Time;
  UINT8  TurboMode;
  UINT8  RatioLimit1;
  UINT8  RatioLimit2;
  UINT8  RatioLimit3;
  UINT8  RatioLimit4;
  UINT8  RatioLimit5;
  UINT8  RatioLimit6;
  UINT8  RatioLimit7;
  UINT8  RatioLimit8;
  UINT8  TurboPowerLimitLock;
  UINT32 PowerLimit1;
  UINT32 PowerLimit1Default;
  UINT8  PowerLimit2;
  UINT32 PowerLimit2Power;
  UINT32 PowerLimit2Default;
  UINT8  OverclockingLock;
  UINT8  LongDurationPwrLimitOverride;
  UINT8  WDTSupportforNextOSBoot;
  UINT16 TimeforNextOSBoot;

  //
  // Setup
  //
  UINT8  PlatformUnstable;

  //
  // IccMax and AVX Retio Control
  //
  UINT16  IccMax[5];
  UINT8   Avx2RatioOffset;
  UINT8   Avx3RatioOffset;

  //
  // GT Unsliced
  //
  UINT8   GtusMaxOcRatio;
  UINT8   GtusVoltageMode;
  UINT16  GtusVoltageOffset;
  UINT8   GtusVoltageOffsetPrefix;
  UINT16  GtusVoltageOverride;
  UINT16  GtusExtraTurboVoltage;
} OC_SETUP_DATA;

#pragma pack()
#endif
