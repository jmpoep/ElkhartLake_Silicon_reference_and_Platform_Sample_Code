/** @file
  Pcie root port policy

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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
#ifndef _CPU_PCIE_CONFIG_H_
#define _CPU_PCIE_CONFIG_H_

#include <Register/CpuPcieRegs.h>
#include <PcieConfig.h>
#include <ConfigBlock.h>

#define CPU_PCIE_RP_CONFIG_REVISION 1

#pragma pack (push,1)

typedef enum {
  CpuPcieOverrideDisabled             = 0,
  CpuPcieL1L2Override                 = 0x01,
  CpuPcieL1SubstatesOverride          = 0x02,
  CpuPcieL1L2AndL1SubstatesOverride   = 0x03,
  CpuPcieLtrOverride                  = 0x04
} CPU_PCIE_OVERRIDE_CONFIG;

/**
  PCIe device table entry entry

  The PCIe device table is being used to override PCIe device ASPM settings.
  To take effect table consisting of such entries must be instelled as PPI
  on gPchPcieDeviceTablePpiGuid.
  Last entry VendorId must be 0.
**/
typedef struct {
  UINT16  VendorId;                    ///< The vendor Id of Pci Express card ASPM setting override, 0xFFFF means any Vendor ID
  UINT16  DeviceId;                    ///< The Device Id of Pci Express card ASPM setting override, 0xFFFF means any Device ID
  UINT8   RevId;                       ///< The Rev Id of Pci Express card ASPM setting override, 0xFF means all steppings
  UINT8   BaseClassCode;               ///< The Base Class Code of Pci Express card ASPM setting override, 0xFF means all base class
  UINT8   SubClassCode;                ///< The Sub Class Code of Pci Express card ASPM setting override, 0xFF means all sub class
  UINT8   EndPointAspm;                ///< Override device ASPM (see: CPU_PCIE_ASPM_CONTROL)
                                       ///< Bit 1 must be set in OverrideConfig for this field to take effect
  UINT16  OverrideConfig;              ///< The override config bitmap (see: CPU_PCIE_OVERRIDE_CONFIG).
  /**
    The L1Substates Capability Offset Override. (applicable if bit 2 is set in OverrideConfig)
    This field can be zero if only the L1 Substate value is going to be override.
  **/
  UINT16  L1SubstatesCapOffset;
  /**
    L1 Substate Capability Mask. (applicable if bit 2 is set in OverrideConfig)
    Set to zero then the L1 Substate Capability [3:0] is ignored, and only L1s values are override.
    Only bit [3:0] are applicable. Other bits are ignored.
  **/
  UINT8   L1SubstatesCapMask;
  /**
    L1 Substate Port Common Mode Restore Time Override. (applicable if bit 2 is set in OverrideConfig)
    L1sCommonModeRestoreTime and L1sTpowerOnScale can have a valid value of 0, but not the L1sTpowerOnValue.
    If L1sTpowerOnValue is zero, all L1sCommonModeRestoreTime, L1sTpowerOnScale, and L1sTpowerOnValue are ignored,
    and only L1SubstatesCapOffset is override.
  **/
  UINT8   L1sCommonModeRestoreTime;
  /**
    L1 Substate Port Tpower_on Scale Override. (applicable if bit 2 is set in OverrideConfig)
    L1sCommonModeRestoreTime and L1sTpowerOnScale can have a valid value of 0, but not the L1sTpowerOnValue.
    If L1sTpowerOnValue is zero, all L1sCommonModeRestoreTime, L1sTpowerOnScale, and L1sTpowerOnValue are ignored,
    and only L1SubstatesCapOffset is override.
  **/
  UINT8   L1sTpowerOnScale;
  /**
    L1 Substate Port Tpower_on Value Override. (applicable if bit 2 is set in OverrideConfig)
    L1sCommonModeRestoreTime and L1sTpowerOnScale can have a valid value of 0, but not the L1sTpowerOnValue.
    If L1sTpowerOnValue is zero, all L1sCommonModeRestoreTime, L1sTpowerOnScale, and L1sTpowerOnValue are ignored,
    and only L1SubstatesCapOffset is override.
  **/
  UINT8   L1sTpowerOnValue;

  /**
    SnoopLatency bit definition
    Note: All Reserved bits must be set to 0

    BIT[15]     - When set to 1b, indicates that the values in bits 9:0 are valid
                  When clear values in bits 9:0 will be ignored
    BITS[14:13] - Reserved
    BITS[12:10] - Value in bits 9:0 will be multiplied with the scale in these bits
                  000b - 1 ns
                  001b - 32 ns
                  010b - 1024 ns
                  011b - 32,768 ns
                  100b - 1,048,576 ns
                  101b - 33,554,432 ns
                  110b - Reserved
                  111b - Reserved
    BITS[9:0]   - Snoop Latency Value. The value in these bits will be multiplied with
                  the scale in bits 12:10

    This field takes effect only if bit 3 is set in OverrideConfig.
  **/
  UINT16  SnoopLatency;
  /**
    NonSnoopLatency bit definition
    Note: All Reserved bits must be set to 0

    BIT[15]     - When set to 1b, indicates that the values in bits 9:0 are valid
                  When clear values in bits 9:0 will be ignored
    BITS[14:13] - Reserved
    BITS[12:10] - Value in bits 9:0 will be multiplied with the scale in these bits
                  000b - 1 ns
                  001b - 32 ns
                  010b - 1024 ns
                  011b - 32,768 ns
                  100b - 1,048,576 ns
                  101b - 33,554,432 ns
                  110b - Reserved
                  111b - Reserved
    BITS[9:0]   - Non Snoop Latency Value. The value in these bits will be multiplied with
                  the scale in bits 12:10

    This field takes effect only if bit 3 is set in OverrideConfig.
  **/
  UINT16  NonSnoopLatency;

  /**
    Forces LTR override to be permanent
    The default way LTR override works is:
      rootport uses LTR override values provided by BIOS until connected device sends an LTR message, then it will use values from the message
    This settings allows force override of LTR mechanism. If it's enabled, then:
      rootport will use LTR override values provided by BIOS forever; LTR messages sent from connected device will be ignored
  **/
  UINT8  ForceLtrOverride;
  UINT8  Reserved[3];
} CPU_PCIE_DEVICE_OVERRIDE;

enum CPU_PCIE_SPEED {
  CpuPcieAuto,
  CpuPcieGen1,
  CpuPcieGen2,
  CpuPcieGen3,
  CpuPcieGen4
};

///
/// The values before AutoConfig match the setting of PCI Express Base Specification 1.1, please be careful for adding new feature
///
typedef enum {
  CpuPcieAspmDisabled,
  CpuPcieAspmL0s,
  CpuPcieAspmL1,
  CpuPcieAspmL0sL1,
  CpuPcieAspmAutoConfig,
  CpuPcieAspmMax
} CPU_PCIE_ASPM_CONTROL;

/**
  Refer to SA EDS for the SA implementation values corresponding
  to below PCI-E spec defined ranges
**/
typedef enum {
  CpuPcieL1SubstatesDisabled,
  CpuPcieL1SubstatesL1_1,
  CpuPcieL1SubstatesL1_1_2,
  CpuPcieL1SubstatesMax
} CPU_PCIE_L1SUBSTATES_CONTROL;

enum CPU_PCIE_MAX_PAYLOAD {
  CpuPcieMaxPayload128 = 0,
  CpuPcieMaxPayload256,
  CpuPcieMaxPayloadMax
};

enum CPU_PCIE_COMPLETION_TIMEOUT {
  CpuPcieCompletionTO_Default,
  CpuPcieCompletionTO_50_100us,
  CpuPcieCompletionTO_1_10ms,
  CpuPcieCompletionTO_16_55ms,
  CpuPcieCompletionTO_65_210ms,
  CpuPcieCompletionTO_260_900ms,
  CpuPcieCompletionTO_1_3P5s,
  CpuPcieCompletionTO_4_13s,
  CpuPcieCompletionTO_17_64s,
  CpuPcieCompletionTO_Disabled
};

enum CPU_PCIE_PCET {
  CpuPciePcet2ms,
  CpuPciePcet3ms,
  CpuPciePcet4ms,
  CpuPciePcet5ms,
  CpuPciePcet6ms,
  CpuPciePcet7ms,
  CpuPciePcet8ms,
  CpuPciePcet9ms,
  CpuPciePcet10ms,
  CpuPciePcet11ms,
  CpuPciePcet21ms,
  CpuPciePcet22ms,
  CpuPciePcet23ms
};

enum CPU_PCIE_PRESETCOEFF_LIST {
  CpuPciePresetCoeffList0,
  CpuPciePresetCoeffList1,
  CpuPciePresetCoeffList2,
  CpuPciePresetCoeffList3,
  CpuPciePresetCoeffList4,
  CpuPciePresetCoeffList5,
  CpuPciePresetCoeffList6,
  CpuPciePresetCoeffList7,
  CpuPciePresetCoeffList8,
  CpuPciePresetCoeffList9,
  CpuPciePresetCoeffList10
};

typedef enum {
  CpuPcieEqDefault      = 0,  ///< @deprecated since revision 3. Behaves as PchPcieEqHardware.
  CpuPcieEqHardware     = 1,  ///< Hardware equalization
  CpuPcieEqStaticCoeff  = 4   ///< Fixed equalization (requires Coefficient settings per lane)
} CPU_PCIE_EQ_METHOD;

enum CPU_PCIE_PX8GTSWLPCE {
  CpuPciePx8gtswlpce1us,
  CpuPciePx8gtswlpce2us,
  CpuPciePx8gtswlpce3us,
  CpuPciePx8gtswlpce4us,
  CpuPciePx8gtswlpce10us,
  CpuPciePx8gtswlpce12us,
  CpuPciePx8gtswlpce14us,
  CpuPciePx8gtswlpce16us
};

enum CPU_PCIE_PX16GTSWLPCE {
  CpuPciePx16gtswlpce500ns,
  CpuPciePx16gtswlpce1us,
  CpuPciePx16gtswlpce1_5us,
  CpuPciePx16gtswlpce2us,
  CpuPciePx16gtswlpce5us,
  CpuPciePx16gtswlpce6us,
  CpuPciePx16gtswlpce7us,
  CpuPciePx16gtswlpce8us
};

/**
  Represent lane specific PCIe Gen3 equalization parameters.
**/
typedef struct {
  UINT8                  Cm;                 ///< Coefficient C-1
  UINT8                  Cp;                 ///< Coefficient C+1
  UINT8                  PegGen3RootPortPreset;      ///< <b>(Test)</b> Used for programming PEG Gen3 preset values per lane. Range: 0-9, 8 is default for each lane
  UINT8                  PegGen3EndPointPreset;      ///< <b>(Test)</b> Used for programming PEG Gen3 preset values per lane. Range: 0-9, 7 is default for each lane
  UINT8                  PegGen3EndPointHint;        ///< <b>(Test)</b> Hint value per lane for the PEG Gen3 End Point. Range: 0-6, 2 is default for each lane
  UINT8                  PegGen4RootPortPreset;      ///< <b>(Test)</b> Used for programming PEG Gen4 preset values per lane. Range: 0-9, 8 is default for each lane
  UINT8                  PegGen4EndPointPreset;      ///< <b>(Test)</b> Used for programming PEG Gen4 preset values per lane. Range: 0-9, 7 is default for each lane
  UINT8                  PegGen4EndPointHint;        ///< <b>(Test)</b> Hint value per lane for the PEG Gen4 End Point. Range: 0-6, 2 is default for each lane
} CPU_PCIE_EQ_LANE_PARAM;

/**
  The SA_PCI_ROOT_PORT_CONFIG describe the feature and capability of each SA PCIe root port.
**/
typedef struct {

  UINT32  ExtSync                         :  1;   ///< Indicate whether the extended synch is enabled. <b>0: Disable</b>; 1: Enable.
  UINT32  VcEnabled                       :  1;   ///< Virtual Channel. 0: Disable; <b>1: Enable</b>
  UINT32  RsvdBits0                       : 30;   ///< Reserved bits
  /**
  PCIe Gen4 Equalization Method
  - HwEq           (0x1) : Hardware Equalization (Default)
  - StaticEq       (0x2) : Static Equalization
  **/
  UINT8   Gen4EqPh3Method;
  /**
   PCIe Equalization Phase 3 Enable Control
  - Disabled       (0x0) : Disable phase 3
  - Enabled        (0x1) : Enable phase 3
  - <b>Auto</b>    (0x2) : Use the current default method (Default)
**/
  UINT8   Gen3EqPh3Enable;
  UINT8   Gen4EqPh3Enable;
  /**
  Gen3 PCIe Equalization Phase 2-3 Enable Control
  - Disabled       (0x0) : Disable Phase 2 - Phase 3
  - Enabled        (0x1) : Enable Phase 2 - Phase 3
  - <b>Auto</b>    (0x2) : Use the current default method (Default)
  **/
  UINT8   Gen3EqPh23Enable;
  /**
  Gen4 PCIe Equalization Phase 2-3 Enable Control
  - Disabled       (0x0) : Disable Phase 2 - Phase 3
  - Enabled        (0x1) : Enable Phase 2 - Phase 3
  - <b>Auto</b>    (0x2) : Use the current default method (Default)
  **/
  UINT8   Gen4EqPh23Enable;
  UINT8   PcetTimer;                              ///< Preset/Coefficient Evaluation Timeout  Default is set to 4ms <b>2</b>
  UINT8   Gen3PresetCoeffList;                    ///< Max preset list count for Gen3  Default is set to <b>4</b>
  UINT8   Gen4PresetCoeffList;                    ///< Max preset list count for Gen4  Default is set to <b>3</b>
  UINT8   Px8gtswlpce;                            ///< 8.0GT/s Training Sequence Wait Latency For Presets / Coefficients Evaluation
  UINT8   Px16gtswlpce;                           ///< 16.0GT/s Training Sequence Wait Latency For Presets / Coefficients Evaluation
  UINT8   RsvdBytes0[2];                          ///< Reserved bytes

  //
  // Gen3 Equalization settings
  //
  UINT32  Gen3Uptp            :  4;               ///< <b>(Test)</b> Upstream Port Transmitter Preset used during Gen3 Link Equalization. Used for all lanes.  Default is <b>7</b>.
  UINT32  Gen3Dptp            :  4;               ///< <b>(Test)</b> Downstream Port Transmiter Preset used during Gen3 Link Equalization. Used for all lanes.  Default is <b>7</b>.
  //
  // Gen4 Equalization settings
  //
  UINT32  Gen4Uptp            :  4;               ///< <b>(Test)</b> Upstream Port Transmitter Preset used during Gen4 Link Equalization. Used for all lanes.  Default is <b>7</b>.
  UINT32  Gen4Dptp            :  4;               ///< <b>(Test)</b> Downstream Port Transmiter Preset used during Gen4 Link Equalization. Used for all lanes.  Default is <b>7</b>.
  UINT32  RsvdBits1           : 16;               ///< Reserved Bits

  PCIE_ROOT_PORT_COMMON_CONFIG                    PcieRpCommonConfig;                       ///< <b>(Test)</b> Includes policies which are common to both SA and PCH RootPort

} CPU_PCIE_ROOT_PORT_CONFIG;

/**
  The CPU_PCIE_CONFIG block describes the expected configuration of the SA PCI Express controllers
**/
typedef struct {
  CONFIG_BLOCK_HEADER               Header;                   ///< Config Block Header
  ///
  /// These members describe the configuration of each SA PCIe root port.
  ///
  CPU_PCIE_ROOT_PORT_CONFIG         RootPort[CPU_PCIE_MAX_ROOT_PORTS];
  ///
  /// Gen3 Equalization settings for physical PCIe lane, index 0 represents PCIe lane 1, etc.
  /// Corresponding entries are used when root port EqPh3Method is PchPcieEqStaticCoeff (default).
  ///
  CPU_PCIE_EQ_LANE_PARAM            EqPh3LaneParam[SA_PEG_MAX_LANE];
  ///
  /// List of coefficients used during equalization (applicable to both software and hardware EQ)
  ///
  PCIE_EQ_PARAM                     HwEqGen4CoeffList[PCIE_HWEQ_COEFFS_MAX];

  PCIE_COMMON_CONFIG                PcieCommonConfig;   /// < <b>(Test)</b> Includes policies which are common to both SA and PCH PCIe

  UINT32  SkipCpuFiaProgramming            :  1;        /// < Skip Fia Configuration and lock if enable
  ///
  /// This member describes whether the PCI Express Clock Gating for each root port
  /// is enabled by platform modules. <b>0: Disable</b>; 1: Enable.
  ///
  UINT32  DisableRootPortClockGating       :  1;
  ///
  /// This member describes whether the PCI Express Power Gating for each root port
  /// is enabled by platform modules. <b>0: Disable</b>; 1: Enable.
  ///
  UINT32  DisableRootPortPowerGating      :  1;
  /**
    <b>(Test)</b> Program PEG Gen3 EQ Phase1 Static Presets
  - Disabled        (0x0)  : Disable EQ Phase1 Static Presets Programming
  - <b>Enabled</b>  (0x1)  : Enable  EQ Phase1 Static Presets Programming (Default)
  **/
  UINT32  PegGen3ProgramStaticEq          :  1;
  /**
  <b>(Test)</b> Program PEG Gen4 EQ Phase1 Static Presets
  - Disabled        (0x0)  : Disable EQ Phase1 Static Presets Programming
  - <b>Enabled</b>  (0x1)  : Enable  EQ Phase1 Static Presets Programming (Default)
  **/
  UINT32  PegGen4ProgramStaticEq          :  1;
  /**
  <b>(Test)</b> Cpu Pcie Secure Register Lock
  **/
  UINT32  SetSecuredRegisterLock          :  1;
  UINT32  RsvdBits0                       : 26;
  /**
    PCIe device override table
    The PCIe device table is being used to override PCIe device ASPM settings.
    This is a pointer points to a 32bit address. And it's only used in PostMem phase.
    Please refer to PCH_PCIE_DEVICE_OVERRIDE structure for the table.
    Last entry VendorId must be 0.
    The prototype of this policy is:
    CPU_PCIE_DEVICE_OVERRIDE *PcieDeviceOverrideTablePtr;
  **/
  UINT32  PcieDeviceOverrideTablePtr;
} CPU_PCIE_CONFIG;

#pragma pack (pop)

#endif // _CPU_PCIE_CONFIG_H_
