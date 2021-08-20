/** @file
  TCSS PEI policy

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2019 Intel Corporation.

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
#ifndef _TCSS_PEI_CONFIG_H_
#define _TCSS_PEI_CONFIG_H_

#include <ConfigBlock.h>
#include <UsbConfig.h>

#define TCSS_MAX_USB3_PORTS      4

#ifndef MAX_ITBT_PCIE_PORT
#define MAX_ITBT_PCIE_PORT                   0x4
#endif

#define TCSS_PEI_CONFIG_REVISION 1
extern EFI_GUID gTcssPeiConfigGuid;

#pragma pack (push,1)


#define MAX_IOM_AUX_BIAS_COUNT 4

///
/// The IOM_AUX_ORI_PAD_CONFIG describes IOM TypeC port map GPIO pin.
/// Those GPIO setting for DP Aux Orientation Bias Control when the TypeC port didn't have re-timer.
/// IOM needs know Pull-Up and Pull-Down pin for Bias control
///
typedef struct {
  UINT32     GpioPullN; ///< GPIO Pull Up Ping number that is for IOM indecate the pull up pin from TypeC port.
  UINT32     GpioPullP; ///< GPIO Pull Down Ping number that is for IOM indecate the pull down pin from TypeC port.
} IOM_AUX_ORI_PAD_CONFIG;

///
/// The IOM_EC_INTERFACE_CONFIG block describes interaction between BIOS and IOM-EC.
///

typedef struct {
  UINT32     VccSt;         ///< IOM VCCST request. (Not equal to actual VCCST value)
  UINT32     UsbOverride;   ///< IOM to override USB connection.
  UINT32     D3ColdEnable;  ///< Enable/disable D3 Cold support in TCSS
  UINT32     D3HotEnable;   ///< Enable/disable D3 Hot support in TCSS
} IOM_INTERFACE_CONFIG;

///
/// The PMC_INTERFACE_CONFIG block describes interaction between BIOS and PMC
///
typedef struct {
  UINT8      PmcPdEnable;    ///< PMC PD Solution Enable
  UINT8      Rsvd[3];
} PMC_INTERFACE_CONFIG;

///
/// The SA XDCI INT Pin and IRQ number
///
typedef struct {
  UINT8      IntPing;  ///< Int Pin Number
  UINT8      Irq;      ///< Irq Number
  UINT16     Rsvd;
} SA_XDCI_IRQ_INT_CONFIG;

///
/// The TCSS_PCIE_PORT_POLICY block describes PCIe settings for TCSS.
///
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
} TCSS_PCIE_PORT_POLICY;

typedef struct {
  TCSS_PCIE_PORT_POLICY  PciePortPolicy[MAX_ITBT_PCIE_PORT];
} TCSS_PCIE_PEI_POLICY;

///
/// The TCSS_IOM_PEI_CONFIG block describes IOM Aux/HSL override settings for TCSS.
///
typedef struct {
  UINT16    AuxOri;     ///< Bits defining value for IOM Aux Orientation Register
  UINT16    HslOri;     ///< Bits defining value for IOM HSL Orientation Register
} TCSS_IOM_ORI_OVERRIDE;

///
/// The TCSS_IOM_PEI_CONFIG block describes IOM settings for TCSS.
///
typedef struct {
  IOM_AUX_ORI_PAD_CONFIG    IomAuxPortPad[MAX_IOM_AUX_BIAS_COUNT]; ///< The IOM_AUX_ORI_BIAS_CTRL port config setting.
  TCSS_IOM_ORI_OVERRIDE     IomOverrides;
  IOM_INTERFACE_CONFIG      IomInterface;                          ///< Config settings are BIOS <-> IOM interface.
  PMC_INTERFACE_CONFIG      PmcInterface;                          ///< Config settings for BIOS <-> PMC interface
  UINT32                    Rsvd;                                  ///< Reserved bytes for future use
} TCSS_IOM_PEI_CONFIG;

///
/// The TCSS_MISC_PEI_CONFIG block describes MISC settings for TCSS.
///
typedef struct {
  SA_XDCI_IRQ_INT_CONFIG    SaXdci;   ///< System Agent Xdci Int Pin and Irq setting
  UINT32                    Rsvd;     ///< Reserved bytes for future use, align to multiple 4
} TCSS_MISC_PEI_CONFIG;

///
/// The TCSS_PEI_CONFIG block describes TCSS settings for SA.
///
typedef struct {
  CONFIG_BLOCK_HEADER     Header;     ///< Offset 0-27 Config Block Header
  TCSS_PCIE_PEI_POLICY    PciePolicy; ///< The PCIe Config
  USB_CONFIG              UsbConfig;  ///< USB config is shared between PCH and SA.
  TCSS_IOM_PEI_CONFIG     IomConfig;  ///< The Iom Config
  TCSS_MISC_PEI_CONFIG    MiscConfig; ///< The MISC Config
} TCSS_PEI_CONFIG;

#pragma pack (pop)

#endif /* _TCSS_PEI_CONFIG_H_ */
