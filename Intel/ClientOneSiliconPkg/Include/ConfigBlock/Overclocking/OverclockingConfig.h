/** @file
  Overclocking Config Block.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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
#ifndef _OVERCLOCKING_PREMEM_CONFIG_H_
#define _OVERCLOCKING_PREMEM_CONFIG_H_

#define OVERCLOCKING_CONFIG_REVISION 1

extern EFI_GUID gOverclockingPreMemConfigGuid;

#pragma pack (push,1)

/**
  Overclocking Configuration Structure.

  <b>Revision 1</b>:
  - Initial version.

**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                   ///< Config Block Header
  /**
  Overclocking support. This controls whether OC mailbox transactions are sent.
  If disabled, all policies in this config block besides OcSupport and OcLock will be ignored.
  <b>0: Disable</b>;
  1: Enable.
  @note If PcdOverclockEnable is disabled, this should also be disabled.
  **/
  UINT32 OcSupport            :  1;
  UINT32 OcLock               :  1;               ///< If enabled, sets OC lock bit in MSR 0x194[20], locking the OC mailbox and other OC configuration settings.; <b>0: Disable</b>; 1: Enable (Lock).
  /**
  Core voltage mode, specifies which voltage mode the processor will be operating.
  <b>0: Adaptive Mode</b> allows the processor to interpolate a voltage curve when beyond fused P0 range;
  1: Override, sets one voltage for for the entire frequency range, Pn-P0.
  **/
  UINT32 CoreVoltageMode      :  1;
  UINT32 CorePllVoltageOffset :  6;               ///< Core PLL voltage offset. <b>0: No offset</b>. Range 0-63 in 17.5mv units.
  UINT32 Avx2RatioOffset      :  5;               ///< AVX2 Ratio Offset. <b>0: No offset</b>. Range is 0-31. Used to lower the AVX ratio to maximize possible ratio for SSE workload.
  UINT32 Avx3RatioOffset      :  5;               ///< AVX3 Ratio Offset. <b>0: No offset</b>. Range is 0-31. Used to lower the AVX3 ratio to maximize possible ratio for SSE workload.
  UINT32 BclkAdaptiveVoltage  :  1;               ///< Bclk Adaptive Voltage enable/disable. <b>0: Disabled</b>, 1: Enabled. When enabled, the CPU V/F curves are aware of BCLK frequency when calculated.
  /**
  Ring Downbin enable/disable.
  When enabled, the CPU will force the ring ratio to be lower than the core ratio.
  Disabling will allow the ring and core ratios to run at the same frequency.
  Uses OC Mailbox command 0x19.
  0: Disables Ring Downbin feature. <b>1: Enables Ring downbin feature.</b>
  **/
  UINT32 RingDownBin          :  1;
  /**
  Ring voltage mode, specifies which voltage mode the processor will be operating.
  <b>0: Adaptive Mode</b> allows the processor to interpolate a voltage curve when beyond fused P0 range;
  1: Override, sets one voltage for for the entire frequency range, Pn-P0.
  **/
  UINT32 RingVoltageMode      :  1;
  UINT32 GtVoltageMode        :  1;    ///< Specifies whether GT voltage is operating in Adaptive or Override mode: <b>0=Adaptive</b>, 1=Override
  UINT32 RealtimeMemoryTiming :  1;    ///< Enable/Disable the message sent to the CPU to allow realtime memory timing changes after MRC_DONE. <b>0=Disable</b>, 1=Enable
  UINT32 FivrFaults           :  1;    ///< Fivr Faults. Enable or Disable FIVR Faults. 0: Disabled, <b>1: Enabled.</b>
  UINT32 FivrEfficiency       :  1;    ///< Fivr Efficiency Management. 0: Disabled, <b>1: Enabled.</b>
  UINT32 RsvdBits             :  6;    ///< Reserved for future use

  /**
  Maximum core turbo ratio override allows to increase CPU core frequency beyond the fused max turbo ratio limit (P0).
  <b>0. no override/HW defaults.</b>. Range 0-85.
  **/
  UINT8  CoreMaxOcRatio;
  UINT8  GtMaxOcRatio;                 ///< Maximum GT turbo ratio override: 0=Minimal, 60=Maximum, <b>0=AUTO</b>
  /**
  Maximum ring ratio override allows to increase CPU ring frequency beyond the fused max ring ratio limit.
  <b>0. no override/HW defaults.</b>. Range 0-85.
  **/
  UINT8  RingMaxOcRatio;
  UINT8  RsvdByte1;
  /**
  The core voltage override which is applied to the entire range of cpu core frequencies.
  Used when CoreVoltageMode = Override.
  <b>0. no override</b>. Range 0-2000 mV.
  **/
  UINT16 CoreVoltageOverride;
  /**
  Adaptive Turbo voltage target used to define the interpolation voltage point when the cpu is operating in turbo mode range.
  Used when CoreVoltageMode = Adaptive.
  <b>0. no override</b>. Range 0-2000mV.
  **/
  UINT16 CoreVoltageAdaptive;
  /**
  The core voltage offset applied on top of all other voltage modes. This offset is applied over the entire frequency range.
  This is a 2's complement number in mV units. <b>Default: 0</b> Range: -1000 to 1000.
  **/
  INT16  CoreVoltageOffset;
  /**
  The ring voltage override which is applied to the entire range of cpu ring frequencies.
  Used when RingVoltageMode = Override.
  <b>0. no override</b>. Range 0-2000 mV.
  **/
  UINT16 RingVoltageOverride;
  /**
  Adaptive Turbo voltage target used to define the interpolation voltage point when the ring is operating in turbo mode range.
  Used when RingVoltageMode = Adaptive.
  <b>0. no override</b>. Range 0-2000mV.
  **/
  UINT16 RingVoltageAdaptive;
  /**
  The ring voltage offset applied on top of all other voltage modes. This offset is applied over the entire frequency range.
  This is a 2's complement number in mV units. <b>Default: 0</b> Range: -1000 to 1000.
  **/
  INT16  RingVoltageOffset;

  INT16  GtVoltageOffset;                         ///< The voltage offset applied to GT slice. Valid range from -1000mv to 1000mv: <b>0=Minimal</b>, 1000=Maximum
  UINT16 GtVoltageOverride;                       ///< The GT voltage override which is applied to the entire range of GT frequencies <b>0=Default</b>
  UINT16 GtExtraTurboVoltage;                     ///< The adaptive voltage applied during turbo frequencies. Valid range from 0 to 2000mV: <b>0=Minimal</b>, 2000=Maximum
  INT16  SaVoltageOffset;                         ///< The voltage offset applied to the SA. Valid range from -1000mv to 1000mv: <b>0=Default</b>
  UINT32 GtPllVoltageOffset     :  6;             ///< GT PLL voltage offset. <b>0: No offset</b>. Range 0-63 in 17.5mv units.
  UINT32 RingPllVoltageOffset   :  6;             ///< Ring PLL voltage offset. <b>0: No offset</b>. Range 0-63 in 17.5mv units.
  UINT32 SaPllVoltageOffset     :  6;             ///< System Agent PLL voltage offset. <b>0: No offset</b>. Range 0-63 in 17.5mv units.
  UINT32 McPllVoltageOffset     :  6;             ///< Memory Controller PLL voltage offset. <b>0: No offset</b>. Range 0-63 in 17.5mv units.
  UINT32 RsvdBits1              :  8;
  /**
  TjMax Offset. Specified value here is clipped by pCode (125 - TjMax Offset) to support TjMax in the range of 62 to 115 deg Celsius.
  <b> Default: 0 Hardware Defaults </b> Range 10 to 63. 0 = No offset / Keep HW default.
  **/
  UINT8  TjMaxOffset;
  UINT8  RsvdByte2[3];                           //< Reserved for dword alignment
} OVERCLOCKING_PREMEM_CONFIG;

#pragma pack (pop)

#endif // _CPU_OVERCLOCKING_CONFIG_H_
