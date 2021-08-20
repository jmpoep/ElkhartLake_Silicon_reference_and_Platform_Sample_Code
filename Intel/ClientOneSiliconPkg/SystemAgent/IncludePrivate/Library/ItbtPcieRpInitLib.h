/** @file
  Header file for TCSS North Lib.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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
#ifndef _SA_PEI_PCIE_COMMON_LIB_LIB_H_
#define _SA_PEI_PCIE_COMMON_LIB_LIB_H_

#include <SaPolicyCommon.h>
#include <TcssPeiConfig.h>

#define V_PCIE_EX_CV                   0x1     /// PCI Extended capability Version

/**
ASPM Settings
**/
typedef enum {
  PcieL1SubstatesDisabled,
  PcieL1SubstatesL1_1,
  PcieL1SubstatesL1_2,
  PcieL1SubstatesL1_1_2,
  PcieL1SubstatesMax
} PCIE_L1SUBSTATES_CONTROL;

/**
PCIe Max Payload
**/
typedef enum {
  PcieMaxPayload_128B,
  PcieMaxPayload_256B,
} PCIE_MAX_PAYLOAD;

typedef struct {
  UINT8   AcsEnabled;                         ///< Indicate whether the ACS is enabled. 0: Disable; <b>1: Enable</b>.
  UINT8   DpcEnabled;                         ///< Downstream Port Containment. 0: Disable; <b>1: Enable</b>
  UINT8   RpDpcExtensionsEnabled;             ///< RP Extensions for Downstream Port Containment. 0: Disable; <b>1: Enable</b>
  UINT8   LtrEnable;                          ///< Latency Tolerance Reporting Mechanism. <b>0: Disable</b>; 1: Enable.
  UINT8   PtmEnabled;                         ///< Enables PTM capability

  UINT8   Aspm;                               ///< The ASPM configuration of the root port (see: PCH_PCIE_ASPM_CONTROL). Default is <b>
  UINT8   SlotNumber;                         ///< Indicates the slot number for the root port. Default is the value as root port index.
  UINT8   SlotPowerLimitScale;                ///< <b>(Test)</b> Specifies scale used for slot power limit value. Leave as 0 to set to default. Default is <b>zero</b>.
  UINT16  SlotPowerLimitValue;                ///< <b>(Test)</b> Specifies upper limit on power supplies by slot. Leave as 0 to set to default. Default is <b>zero</b>.

  UINT8   AdvancedErrorReporting;             ///< Indicate whether the Advanced Error Reporting is enabled. <b>0: Disable</b>; 1: Enable.
  UINT8   UnsupportedRequestReport;           ///< Indicate whether the Unsupported Request Report is enabled. <b>0: Disable</b>; 1: Enable.
  UINT8   FatalErrorReport;                   ///< Indicate whether the Fatal Error Report is enabled. <b>0: Disable</b>; 1: Enable.
  UINT8   NoFatalErrorReport;                 ///< Indicate whether the No Fatal Error Report is enabled. <b>0: Disable</b>; 1: Enable.
  UINT8   CorrectableErrorReport;             ///< Indicate whether the Correctable Error Report is enabled. <b>0: Disable</b>; 1: Enable.
  UINT8   SystemErrorOnFatalError;            ///< Indicate whether the System Error on Fatal Error is enabled. <b>0: Disable</b>; 1: Enable.
  UINT8   SystemErrorOnNonFatalError;         ///< Indicate whether the System Error on Non Fatal Error is enabled. <b>0: Disable</b>; 1: Enable.
  UINT8   SystemErrorOnCorrectableError;      ///< Indicate whether the System Error on Correctable Error is enabled. <b>0: Disable</b>; 1: Enable.

  UINT16  LtrMaxSnoopLatency;                 ///< Latency Tolerance Reporting, Max Snoop Latency.
  UINT16  LtrMaxNoSnoopLatency;               ///< Latency Tolerance Reporting, Max Non-Snoop Latency.
  UINT8   SnoopLatencyOverrideMode;           ///< Latency Tolerance Reporting, Snoop Latency Override Mode.
  UINT8   SnoopLatencyOverrideMultiplier;     ///< Latency Tolerance Reporting, Snoop Latency Override Multiplier.
  UINT16  SnoopLatencyOverrideValue;          ///< Latency Tolerance Reporting, Snoop Latency Override Value.
  UINT8   NonSnoopLatencyOverrideMode;        ///< Latency Tolerance Reporting, Non-Snoop Latency Override Mode.
  UINT8   NonSnoopLatencyOverrideMultiplier;  ///< Latency Tolerance Reporting, Non-Snoop Latency Override Multiplier.
  UINT16  NonSnoopLatencyOverrideValue;       ///< Latency Tolerance Reporting, Non-Snoop Latency Override Value.
  UINT8   ForceLtrOverride;                   ///< <b>0: Disable</b>; 1: Enable.
  UINT8   LtrConfigLock;                      ///< <b>0: Disable</b>; 1: Enable.
} ITBT_PCIE_CONFIG;

/**
This function Implements iTbt PCI Port initialization

SIP15 PCI Express Root Port BIOS Requirement Rev 0.9
@param[in] TcssConfig           Pointer to config block

**/
VOID
ItbtInitRootPorts(
  IN  TCSS_PEI_CONFIG             *TcssPeiConfig
);

//
// 2LM: PegPcie APIs for Sideband Access Mechanism in 2LM mode
//
/**
  Reads an 8-bit PCI configuration register.

  Its a wrapper library function. This function uses side band access for PEG60 when 2LM mode is enabled.
  Other calls to this function will be routed to core PciSegmentRead8 function.

  @param  Address   Address that encodes the PCI Segment, Bus, Device, Function, and Register.

  @return The 8-bit PCI configuration register specified by Address.

**/
UINT8
EFIAPI
PegPciSegmentRead8 (
  IN UINT64                    Address
  );

/**
  Writes an 8-bit PCI configuration register.

  Its a wrapper library function. This function uses side band access for PEG60 when 2LM mode is enabled.
  Other calls to this function will be routed to core PciSegmentWrite8 function.

  @param  Address     Address that encodes the PCI Segment, Bus, Device, Function, and Register.
  @param  Value       The value to write.

  @return The value written to the PCI configuration register.

**/
UINT8
EFIAPI
PegPciSegmentWrite8 (
  IN UINT64                    Address,
  IN UINT8                     Value
  );

/**
  Reads a 16-bit PCI configuration register.

  Its a wrapper library function. This function uses side band access for PEG60 when 2LM mode is enabled.
  Other calls to this function will be routed to core PciSegmentRead16 function.

  @param  Address   Address that encodes the PCI Segment, Bus, Device, Function, and Register.

  @return The 16-bit PCI configuration register specified by Address.

**/
UINT16
EFIAPI
PegPciSegmentRead16 (
  IN UINT64                    Address
  );

/**
  Writes a 16-bit PCI configuration register.

  Its a wrapper library function. This function uses side band access for PEG60 when 2LM mode is enabled.
  Other calls to this function will be routed to core PciSegmentWrite16 function.

  @param  Address     Address that encodes the PCI Segment, Bus, Device, Function, and Register.
  @param  Value       The value to write.

  @return The parameter of Value.

**/
UINT16
EFIAPI
PegPciSegmentWrite16 (
  IN UINT64                    Address,
  IN UINT16                    Value
  );

/**
  Reads a 32-bit PCI configuration register.

  Its a wrapper library function. This function uses side band access for PEG60 when 2LM mode is enabled.
  Other calls to this function will be routed to core PciSegmentRead32 function.

  @param  Address   Address that encodes the PCI Segment, Bus, Device, Function, and Register.

  @return The 32-bit PCI configuration register specified by Address.

**/
UINT32
EFIAPI
PegPciSegmentRead32 (
  IN UINT64                    Address
  );

/**
  Writes a 32-bit PCI configuration register.

  Its a wrapper library function. This function uses side band access for PEG60 when 2LM mode is enabled.
  Other calls to this function will be routed to core PciSegmentWrite32 function.

  @param  Address     Address that encodes the PCI Segment, Bus, Device, Function, and Register.
  @param  Value       The value to write.

  @return The parameter of Value.

**/
UINT32
EFIAPI
PegPciSegmentWrite32 (
  IN UINT64                    Address,
  IN UINT32                    Value
  );

/**
  Performs a bitwise OR of a 16-bit PCI configuration register with a 16-bit value.

  Its a wrapper library function. This function uses side band access for PEG60 when 2LM mode is enabled.
  Other calls to this function will be routed to core PciSegmentOr16 function.

  @param  Address   Address that encodes the PCI Segment, Bus, Device, Function, and Register.
  @param  OrData    The value to OR with the PCI configuration register.

  @return The value written to the PCI configuration register.
**/
UINT16
EFIAPI
PegPciSegmentOr16(
  IN UINT64                    Address,
  IN UINT16                    OrData
  );

/**
  Performs a bitwise AND of a 16-bit PCI configuration register with a 16-bit value.

  Its a wrapper library function. This function uses side band access for PEG60 when 2LM mode is enabled.
  Other calls to this function will be routed to core PciSegmentAnd32 function.

  @param  Address   Address that encodes the PCI Segment, Bus, Device, Function, and Register.
  @param  AndData   The value to AND with the PCI configuration register.

  @return The value written to the PCI configuration register.

**/
UINT16
EFIAPI
PegPciSegmentAnd16(
  IN UINT64                    Address,
  IN UINT16                    AndData
  );

/**
  Performs a bitwise OR of a 32-bit PCI configuration register with a 32-bit value.

  Its a wrapper library function. This function uses side band access for PEG60 when 2LM mode is enabled.
  Other calls to this function will be routed to core PciSegmentOr32 function.

  @param  Address   Address that encodes the PCI Segment, Bus, Device, Function, and Register.
  @param  OrData    The value to OR with the PCI configuration register.

  @return The value written to the PCI configuration register.

**/
UINT32
EFIAPI
PegPciSegmentOr32 (
  IN UINT64                    Address,
  IN UINT32                    OrData
  );

/**
  Performs a bitwise AND of a 32-bit PCI configuration register with a 32-bit value.

  Its a wrapper library function. This function uses side band access for PEG60 when 2LM mode is enabled.
  Other calls to this function will be routed to core PciSegmentAnd32 function.

  @param  Address   Address that encodes the PCI Segment, Bus, Device, Function, and Register.
  @param  AndData   The value to AND with the PCI configuration register.

  @return The value written to the PCI configuration register.

**/
UINT32
EFIAPI
PegPciSegmentAnd32(
  IN UINT64                    Address,
  IN UINT32                    AndData
);

/**
  Performs a bitwise AND of a 32-bit PCI configuration register with a 32-bit value,
  followed a  bitwise OR with another 32-bit value.

  Its a wrapper library function. This function uses side band access for PEG60 when 2LM mode is enabled.
  Other calls to this function will be routed to core PciSegmentAndThenOr32 function.

  @param  Address   Address that encodes the PCI Segment, Bus, Device, Function, and Register.
  @param  AndData   The value to AND with the PCI configuration register.
  @param  OrData    The value to OR with the PCI configuration register.

  @return The value written to the PCI configuration register.

**/
UINT32
EFIAPI
PegPciSegmentAndThenOr32 (
  IN UINT64                    Address,
  IN UINT32                    AndData,
  IN UINT32                    OrData
  );

/**
  Find the Offset to a Capabilities ID
  @param[in] Segment              Pci Segment Number
  @param[in] Bus                  Pci Bus Number
  @param[in] Device               Pci Device Number
  @param[in] Function             Pci Function Number
  @param[in] CapId                CAPID to search for

  @retval 0                       CAPID not found
  @retval Other                   CAPID found, Offset of desired CAPID
**/
UINT8
PegPcieFindCapId (
  IN UINT8   Segment,
  IN UINT8   Bus,
  IN UINT8   Device,
  IN UINT8   Function,
  IN UINT8   CapId
  );

/**
  Search and return the offset of desired Pci Express extended Capability ID
  @param[in] Segment              Pci Segment Number
  @param[in] Bus                  Pci Bus Number
  @param[in] Device               Pci Device Number
  @param[in] Function             Pci Function Number
  @param[in] CapId                Extended CAPID to search for

  @retval 0                       CAPID not found
  @retval Other                   CAPID found, Offset of desired CAPID
**/
UINT16
PegPcieFindExtendedCapId (
  IN UINT8   Segment,
  IN UINT8   Bus,
  IN UINT8   Device,
  IN UINT8   Function,
  IN UINT16  CapId
  );

#endif
