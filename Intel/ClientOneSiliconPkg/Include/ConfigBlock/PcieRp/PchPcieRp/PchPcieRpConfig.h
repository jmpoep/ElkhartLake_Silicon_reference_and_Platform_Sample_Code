/** @file
  PCH Pcie root port policy

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
#ifndef _PCH_PCIERP_CONFIG_H_
#define _PCH_PCIERP_CONFIG_H_

#include <PchLimits.h>
#include <PcieConfig.h>
#include <ConfigBlock.h>

#define PCIE_RP_CONFIG_REVISION 1
#define PCIE_RP_PREMEM_CONFIG_REVISION 1
#define PCIE_RP_DXE_CONFIG_REVISION 1

extern EFI_GUID gPchPcieRpConfigGuid;
extern EFI_GUID gPcieRpPreMemConfigGuid;

#pragma pack (push,1)

#define PCIE_LINK_EQ_COEFFICIENTS_MAX 10
#define PCIE_LINK_EQ_PRESETS_MAX 11

typedef enum {
  PchPcieOverrideDisabled             = 0,
  PchPcieL1L2Override                 = 0x01,
  PchPcieL1SubstatesOverride          = 0x02,
  PchPcieL1L2AndL1SubstatesOverride   = 0x03,
  PchPcieLtrOverride                  = 0x04
} PCH_PCIE_OVERRIDE_CONFIG;

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
  UINT8   EndPointAspm;                ///< Override device ASPM (see: PCH_PCIE_ASPM_CONTROL)
                                       ///< Bit 1 must be set in OverrideConfig for this field to take effect
  UINT16  OverrideConfig;              ///< The override config bitmap (see: PCH_PCIE_OVERRIDE_CONFIG).
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
} PCH_PCIE_DEVICE_OVERRIDE;

enum PCH_PCIE_SPEED {
  PchPcieAuto,
  PchPcieGen1,
  PchPcieGen2,
  PchPcieGen3
};

///
/// The values before AutoConfig match the setting of PCI Express Base Specification 1.1, please be careful for adding new feature
///
typedef enum {
  PchPcieAspmDisabled,
  PchPcieAspmL0s,
  PchPcieAspmL1,
  PchPcieAspmL0sL1,
  PchPcieAspmAutoConfig,
  PchPcieAspmMax
} PCH_PCIE_ASPM_CONTROL;

/**
  Refer to PCH EDS for the PCH implementation values corresponding
  to below PCI-E spec defined ranges
**/
typedef enum {
  PchPcieL1SubstatesDisabled,
  PchPcieL1SubstatesL1_1,
  PchPcieL1SubstatesL1_1_2,
  PchPcieL1SubstatesMax
} PCH_PCIE_L1SUBSTATES_CONTROL;

enum PCH_PCIE_MAX_PAYLOAD {
  PchPcieMaxPayload128 = 0,
  PchPcieMaxPayload256,
  PchPcieMaxPayloadMax
};

enum PCH_PCIE_COMPLETION_TIMEOUT {
  PchPcieCompletionTO_Default,
  PchPcieCompletionTO_50_100us,
  PchPcieCompletionTO_1_10ms,
  PchPcieCompletionTO_16_55ms,
  PchPcieCompletionTO_65_210ms,
  PchPcieCompletionTO_260_900ms,
  PchPcieCompletionTO_1_3P5s,
  PchPcieCompletionTO_4_13s,
  PchPcieCompletionTO_17_64s,
  PchPcieCompletionTO_Disabled
};

typedef enum {
  PcieLinkHardwareEq = 0,  ///< Hardware is responsible for performing coefficient/preset search.
  PcieLinkFixedEq          ///< No coefficient/preset search is performed. Fixed values are used.
} PCIE_LINK_EQ_METHOD;

typedef enum {
  PcieLinkEqPresetMode = 0,   ///< Use presets during PCIe link equalization
  PcieLinkEqCoefficientMode   ///< Use coefficients during PCIe link equalization
} PCIE_LINK_EQ_MODE;

typedef struct {
  UINT32  PreCursor;    ///< Pre-cursor coefficient
  UINT32  PostCursor;   ///< Post-cursor coefficient
} PCIE_LINK_EQ_COEFFICIENTS;

typedef struct {
  UINT8                      PcieLinkEqMethod;               ///< Tells BIOS which link EQ method should be used for this port. Please refer to PCIE_LINK_EQ_METHOD for details of supported methods. Default: PcieLinkHardwareEq
  UINT8                      PcieLinkEqMode;                 ///< Tells BIOS which mode should be used for PCIe link EQ. Please refer to PCIE_LINK_EQ_MODE for details of supported modes. Default: depends on SoC
  /**
    Specifies if BIOS should perform local transmitter override during phase 2 of EQ process.
    If enabled value in Ph2LocalTransmitterOverridePreset must be valid.
    <b>0: Disabled</b>; 1: Enabled
  **/
  UINT8                      LocalTransmitterOverrideEnable;
  /**
    Tells BIOS how many presets/coefficients should be used during link EQ.
    Entries in the Ph3CoefficientsList or Ph3PresetList(depending on chosen mode) need to be valid up to the number specified in this field.
  **/
  UINT8                      Ph3NumberOfPresetsOrCoefficients;

  PCIE_LINK_EQ_COEFFICIENTS  Ph3CoefficientsList[PCIE_LINK_EQ_COEFFICIENTS_MAX];  ///< List of the PCIe coefficients to be used during equalization process. Only valid if PcieLinkEqMode is PcieLinkEqCoefficientMode
  UINT32                     Ph3PresetList[PCIE_LINK_EQ_PRESETS_MAX];             ///< List of the PCIe preset values to be used during equalization process. Only valid if PcieLinkEqMode is PcieLinkEqPresetMode
  UINT32                     Ph1DownstreamPortTransmitterPreset;  ///< Specifies the value of the downstream port transmitter preset to be used during phase 1 of the equalization process. Will be applied to all lanes
  UINT32                     Ph1UpstreamPortTransmitterPreset;    ///< Specifies the value of the upstream port transmitter preset to be used during phase 1 of the equalization process. Will be applied to all lanes
  /**
    Specifies the preset that should be used during local transmitter override during phase 2 of EQ process.
    Used only if LocalTransmitterOverrideEnable is TRUE. Will be applied to all PCIe lanes of the root port.
    Valid up to the PCIE_LINK_EQ_PRESET_MAX value. <b>Default: 0<\b>
  **/
  UINT32                     Ph2LocalTransmitterOverridePreset;
} PCIE_LINK_EQ_PLATFORM_SETTINGS;

#define PCH_PCIE_NO_SUCH_CLOCK 0xFF

typedef enum {
  PchClockUsagePchPcie0      = 0,
  PchClockUsagePchPcie1      = 1,
  PchClockUsagePchPcie2      = 2,
  PchClockUsagePchPcie3      = 3,
  PchClockUsagePchPcie4      = 4,
  PchClockUsagePchPcie5      = 5,
  PchClockUsagePchPcie6      = 6,
  PchClockUsagePchPcie7      = 7,
  PchClockUsagePchPcie8      = 8,
  PchClockUsagePchPcie9      = 9,
  PchClockUsagePchPcie10     = 10,
  PchClockUsagePchPcie11     = 11,
  PchClockUsagePchPcie12     = 12,
  PchClockUsagePchPcie13     = 13,
  PchClockUsagePchPcie14     = 14,
  PchClockUsagePchPcie15     = 15,
  PchClockUsagePchPcie16     = 16,
  PchClockUsagePchPcie17     = 17,
  PchClockUsagePchPcie18     = 18,
  PchClockUsagePchPcie19     = 19,
  PchClockUsagePchPcie20     = 20,
  PchClockUsagePchPcie21     = 21,
  PchClockUsagePchPcie22     = 22,
  PchClockUsagePchPcie23     = 23,
  /**
    Quantity of PCH and CPU PCIe ports, as well as their encoding in this enum, may change between
    silicon generations and series. Do not assume that PCH port 0 will be always encoded by 0.
    Instead, it is recommended to use (PchClockUsagePchPcie0 + PchPortIndex) style to be forward-compatible
  **/
  PchClockUsageCpuPcie0      = 0x40,
  PchClockUsageCpuPcie1      = 0x41,
  PchClockUsageCpuPcie2      = 0x42,
  PchClockUsageCpuPcie3      = 0x43,

  PchClockUsageLan           = 0x70,
  PchClockUsageUnspecified   = 0x80, ///< In use for a purpose not listed above
  PchClockUsageNotUsed       = 0xFF
} PCH_PCIE_CLOCK_USAGE;

/**
  PCH_PCIE_CLOCK describes PCIe source clock generated by PCH.
**/
typedef struct {
  UINT8   Usage;        ///< Purpose of given clock (see PCH_PCIE_CLOCK_USAGE). Default: Unused, 0xFF
  UINT8   ClkReq;       ///< ClkSrc - ClkReq mapping. Default: 1:1 mapping with Clock numbers
  UINT8   RsvdBytes[2]; ///< Reserved byte
} PCH_PCIE_CLOCK;

/**
  The PCH_PCI_EXPRESS_ROOT_PORT_CONFIG describe the feature and capability of each PCH PCIe root port.
**/
typedef struct {
  UINT32  HotPlug                         :  1;   ///< Indicate whether the root port is hot plug available. <b>0: Disable</b>; 1: Enable.
  UINT32  PmSci                           :  1;   ///< Indicate whether the root port power manager SCI is enabled. 0: Disable; <b>1: Enable</b>.
  UINT32  ExtSync                         :  1;   ///< Indicate whether the extended synch is enabled. <b>0: Disable</b>; 1: Enable.
  UINT32  TransmitterHalfSwing            :  1;   ///< Indicate whether the Transmitter Half Swing is enabled. <b>0: Disable</b>; 1: Enable.
  UINT32  AcsEnabled                      :  1;   ///< Indicate whether the ACS is enabled. 0: Disable; <b>1: Enable</b>.
  UINT32  RsvdBits0                       : 10;   ///< Reserved bits.

  /**
    Probe CLKREQ# signal before enabling CLKREQ# based power management.
    Conforming device shall hold CLKREQ# low until CPM is enabled. This feature attempts
    to verify CLKREQ# signal is connected by testing pad state before enabling CPM.
    In particular this helps to avoid issues with open-ended PCIe slots.
    This is only applicable to non hot-plug ports.
    <b>0: Disable</b>; 1: Enable.
  **/
  UINT32  ClkReqDetect                    :  1;
  //
  // Error handlings
  //
  UINT32  AdvancedErrorReporting          :  1;   ///< Indicate whether the Advanced Error Reporting is enabled. <b>0: Disable</b>; 1: Enable.
  UINT32  SystemErrorEnable               :  1;   ///< Indicate whether the System Error is enabled. <b>0: Disable</b>; 1: Enable.
  UINT32  UnsupportedRequestReport        :  1;   ///< Indicate whether the Unsupported Request Report is enabled. <b>0: Disable</b>; 1: Enable.
  UINT32  FatalErrorReport                :  1;   ///< Indicate whether the Fatal Error Report is enabled. <b>0: Disable</b>; 1: Enable.
  UINT32  NoFatalErrorReport              :  1;   ///< Indicate whether the No Fatal Error Report is enabled. <b>0: Disable</b>; 1: Enable.
  UINT32  CorrectableErrorReport          :  1;   ///< Indicate whether the Correctable Error Report is enabled. <b>0: Disable</b>; 1: Enable.
  UINT32  SystemErrorOnFatalError         :  1;   ///< Indicate whether the System Error on Fatal Error is enabled. <b>0: Disable</b>; 1: Enable.
  UINT32  SystemErrorOnNonFatalError      :  1;   ///< Indicate whether the System Error on Non Fatal Error is enabled. <b>0: Disable</b>; 1: Enable.
  UINT32  SystemErrorOnCorrectableError   :  1;   ///< Indicate whether the System Error on Correctable Error is enabled. <b>0: Disable</b>; 1: Enable.
  /**
    Max Payload Size supported, Default <b>128B</b>, see enum PCH_PCIE_MAX_PAYLOAD
    Changes Max Payload Size Supported field in Device Capabilities of the root port.
  **/
  UINT32  MaxPayload                      :  2;
  UINT32  RsvdBits1                       :  1;   ///< Reserved fields for future expansion w/o protocol change
  UINT32  DpcEnabled                      :  1;   ///< Downstream Port Containment. 0: Disable; <b>1: Enable</b>
  UINT32  RpDpcExtensionsEnabled          :  1;   ///< RP Extensions for Downstream Port Containment. 0: Disable; <b>1: Enable</b>
  /**
    Indicates how this root port is connected to endpoint. 0: built-in device; <b>1: slot</b>
    Built-in is incompatible with hotplug-capable ports.
  **/
  UINT32  SlotImplemented                 :  1;
  /**
    The Multiple VC (MVC) supports hardware to avoid HoQ block for latency sensitive TC.
    Currently it is only applicable to Root Ports with 2pX4 port configuration with 2 VCs,or
    DMI port configuration with 3 VCs. For Root Ports 2pX4 configuration, two RPs (RP0,
    RP2) shall support two PCIe VCs (VC0 & VC1) and the other RPs (RP1, RP3) shall be
    disabled.
    <b>0: Disable</b>; 1: Enable
  **/
  UINT32  MvcEnabled                      :  1;
  /**
    Virtual Pin Port is industry standard introduced to PCIe Hot Plug support in systems
    when GPIO pins expansion is needed. It is server specific feature.
    <b>0x00: Default</b>; 0xFF: Disabled
  **/
  UINT8   VppPort;
  UINT8   VppAddress;                             ///< PCIe Hot Plug VPP SMBus Address. Default is zero.
  UINT8   RsvdBytes0[2];                          ///< Reserved bytes

  /**
    Determines each PCIE Port speed capability.
    <b>0: Auto</b>; 1: Gen1; 2: Gen2; 3: Gen3 (see: PCH_PCIE_SPEED)
  **/
  UINT8   PcieSpeed;

  UINT8   PhysicalSlotNumber;                     ///< Indicates the slot number for the root port. Default is the value as root port index.
  UINT8   CompletionTimeout;                      ///< The completion timeout configuration of the root port (see: PCH_PCIE_COMPLETION_TIMEOUT). Default is <b>PchPcieCompletionTO_Default</b>.
  UINT8   RsvdBytes1;                             ///< Reserved bytes
  //
  // Power Management
  //
  UINT8   Aspm;                                             ///< The ASPM configuration of the root port (see: PCH_PCIE_ASPM_CONTROL). Default is <b>PchPcieAspmAutoConfig</b>.
  UINT8   L1Substates;                                      ///< The L1 Substates configuration of the root port (see: PCH_PCIE_L1SUBSTATES_CONTROL). Default is <b>PchPcieL1SubstatesL1_1_2</b>.
  UINT8   LtrEnable;                                        ///< Latency Tolerance Reporting Mechanism. <b>0: Disable</b>; 1: Enable.
  PCIE_LTR_CONFIG               PcieRpLtrConfig;            ///< <b>(Test)</b> Latency Tolerance Reporting Policies including LTR limit and Override
  PCIE_ROOT_PORT_COMMON_CONFIG  PcieRpCommonConfig;         ///< <b>(Test)</b> Includes policies which are common to both SA and PCH PCIe
  UINT32  SlotPowerLimitScale :  2;                         ///< <b>(Test)</b> Specifies scale used for slot power limit value. Leave as 0 to set to default. Default is <b>zero</b>.
  UINT32  SlotPowerLimitValue : 12;                         ///< <b>(Test)</b> Specifies upper limit on power supplies by slot. Leave as 0 to set to default. Default is <b>zero</b>.
  UINT32  PtmEnabled          :  1;               ///< Enables PTM capability
  UINT32  MultiVcEnabled      :  1;               ///< Enables Multiple Virtual Channel on root port for Multi VC capable controllers.
  UINT32  RsvdBits2           : 16;               ///< Reserved Bits
  /**
    The number of milliseconds reference code will wait for link to exit Detect state for enabled ports
    before assuming there is no device and potentially disabling the port.
    It's assumed that the link will exit detect state before root port initialization (sufficient time
    elapsed since PLTRST de-assertion) therefore default timeout is zero. However this might be useful
    if device power-up seqence is controlled by BIOS or a specific device requires more time to detect.
    In case of non-common clock enabled the default timout is 15ms.
    <b>Default: 0</b>
  **/
  UINT16  DetectTimeoutMs;
  UINT16  RsvdBytes2[3];                          ///< Reserved bytes
} PCH_PCIE_ROOT_PORT_CONFIG;

/**
  The PCH_PCIE_CONFIG block describes the expected configuration of the PCH PCI Express controllers
  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                   ///< Config Block Header
  ///
  /// These members describe the configuration of each PCH PCIe root port.
  ///
  PCH_PCIE_ROOT_PORT_CONFIG         RootPort[PCH_MAX_PCIE_ROOT_PORTS];
  PCIE_LINK_EQ_PLATFORM_SETTINGS    PcieLinkEqPlatformSettings;  ///< Global PCIe link EQ settings that BIOS will use during PCIe link EQ for every port.

  UINT32  OverrideEqualizationDefaults     : 1; ///< <b>0: Use project default equalization settings</b>; 1: Use equalization settings from PcieLinkEqPlatformSettings
  ///
  /// <b>(Test)</b> This member describes whether PCIE root port Port 8xh Decode is enabled. <b>0: Disable</b>; 1: Enable.
  ///
  UINT32  EnablePort8xhDecode              :  1;
  ///
  /// <b>(Test)</b> The Index of PCIe Port that is selected for Port8xh Decode (0 Based)
  ///
  UINT32  PchPciePort8xhDecodePortIndex    :  5;
  ///
  /// This member describes whether Peer Memory Writes are enabled on the platform. <b>0: Disable</b>; 1: Enable.
  ///
  UINT32  EnablePeerMemoryWrite            :  1;
  /**
    Compliance Test Mode shall be enabled when using Compliance Load Board.
    <b>0: Disable</b>, 1: Enable
  **/
  UINT32  ComplianceTestMode               :  1;
  /**
    RpFunctionSwap allows BIOS to use root port function number swapping when root port of function 0 is disabled.
    A PCIE device can have higher functions only when Function0 exists. To satisfy this requirement,
    BIOS will always enable Function0 of a device that contains more than 0 enabled root ports.
    - <b>Enabled: One of enabled root ports get assigned to Function0.</b>
      This offers no guarantee that any particular root port will be available at a specific DevNr:FuncNr location
    - Disabled: Root port that corresponds to Function0 will be kept visible even though it might be not used.
      That way rootport - to - DevNr:FuncNr assignment is constant. This option will impact ports 1, 9, 17.
      NOTE: This option will not work if ports 1, 9, 17 are fused or configured for RST PCIe storage or disabled through policy
            In other words, it only affects ports that would become hidden because they have no device connected.
      NOTE: Disabling function swap may have adverse impact on power management. This option should ONLY
            be used when each one of root ports 1, 9, 17:
        - is configured as PCIe and has correctly configured ClkReq signal, or
        - does not own any mPhy lanes (they are configured as SATA or USB)
  **/
  UINT32  RpFunctionSwap                   :  1;
  ///
  /// This member describes whether the PCI Express Clock Gating for each root port
  /// is enabled by platform modules. <b>O: POR</b>; 1: Enable; 2: Disable
  ///
  UINT32  TestPcieClockGating              :  2;
  UINT32  RsvdBits0                        : 20;

} PCH_PCIE_CONFIG;

/**
  The PCH_PCIE_RP_PREMEM_CONFIG block describes early configuration of the PCH PCI Express controllers
  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                                ///< Config Block Header
  /**
    Root Port enabling mask.
    Bit0 presents RP1, Bit1 presents RP2, and so on.
    0: Disable; <b>1: Enable</b>.
  **/
  UINT32                RpEnabledMask;
  /// Configuration of PCIe source clocks
  ///
  PCH_PCIE_CLOCK                    PcieClock[PCH_MAX_PCIE_CLOCKS];
} PCH_PCIE_RP_PREMEM_CONFIG;

/**
  The PCIE_RP_DXE_CONFIG block describes the expected configuration of the PCH PCI Express controllers in DXE phase

  <b>Revision 1</b>:
  - Init version
**/
typedef struct {
  CONFIG_BLOCK_HEADER      Header;                     ///< Config Block Header

  /**
    PCIe device override table
    The PCIe device table is being used to override PCIe device ASPM settings.
    And it's only used in DXE phase.
    Please refer to PCH_PCIE_DEVICE_OVERRIDE structure for the table.
    Last entry VendorId must be 0.
  **/
  PCH_PCIE_DEVICE_OVERRIDE    *PcieDeviceOverrideTablePtr;
} PCIE_RP_DXE_CONFIG;

#pragma pack (pop)

#endif // _PCH_PCIERP_CONFIG_H_
