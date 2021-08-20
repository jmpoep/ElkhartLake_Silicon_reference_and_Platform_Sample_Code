/** @file
  Header file for PCI Express helpers library

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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
#ifndef _PCI_EXPRESS_HELPERS_LIB_H_
#define _PCI_EXPRESS_HELPERS_LIB_H_

#include <PchPolicyCommon.h>

#define VC_CAP_ID     0x0002  // Virtual Channel capability ID
#define MFVC_CAP_ID   0x0009  // Optional Multi Functional Virtual Channel capability ID
#define VC_CAP_REG    0x04    // Virtual Channel capability register
#define VC0_CTRL_REG  0x14    // VC0 control register
#define VC1_CTRL_REG  0x20    // VC1 control register - 14h + n*(0Ch) Here n is channel 1

//
// This structure conveniently keeps segment:bus:device:function coordinates of a PCIe device
// in a single variable. PcieCap is offset to PCI Express capabilities. Having it cached together
// with coordinates is an optimization feature, because code in this file uses it a lot
//
typedef struct {
  UINT32 Seg     : 8;
  UINT32 Bus     : 8;
  UINT32 Dev     : 5;
  UINT32 Func    : 3;
  UINT32 PcieCap : 8;
} SBDF;

typedef enum {
  TpoScale2us,
  TpoScale10us,
  TpoScale100us,
  TpoScaleMax
} T_PO_SCALE;

typedef struct {
  UINT32     Value;
  T_PO_SCALE Scale;
} T_POWER_ON;

/**
  This function reads Pci Config register via SBI Access

  @param[in]  RpIndex             Root Port Index (0-based)
  @param[in]  Offset              Offset of Config register
  @param[out] *Data32             Value of Config register

  @retval EFI_SUCCESS             SBI Read successful.
**/
EFI_STATUS
PchSbiRpPciRead32 (
  IN    UINT32  RpIndex,
  IN    UINT32  Offset,
  OUT   UINT32  *Data32
  );

/**
  This function And then Or Pci Config register via SBI Access

  @param[in]  RpIndex             Root Port Index (0-based)
  @param[in]  Offset              Offset of Config register
  @param[in]  Data32And           Value of Config register to be And-ed
  @param[in]  Data32AOr           Value of Config register to be Or-ed

  @retval EFI_SUCCESS             SBI Read and Write successful.
**/
EFI_STATUS
PchSbiRpPciAndThenOr32 (
  IN  UINT32  RpIndex,
  IN  UINT32  Offset,
  IN  UINT32  Data32And,
  IN  UINT32  Data32Or
  );

/**
  This function And then Or Pci Memory register via SBI Access

  @param[in]  RpIndex             Root Port Index (0-based)
  @param[in]  Offset              Offset of Config register
  @param[in]  Data32And           Value of Config register to be And-ed
  @param[in]  Data32AOr           Value of Config register to be Or-ed

  @retval EFI_SUCCESS             SBI Read and Write successful.
**/
EFI_STATUS
PchSbiRpPciMemAndThenOr32 (
  IN  UINT32  RpIndex,
  IN  UINT64  Offset,
  IN  UINT32  Data32And,
  IN  UINT32  Data32Or
  );

/**
  Get PCIe port number for enabled port.
  @param[in] RpBase    Root Port pci segment base address
  @return Root Port number (1 based)
**/
UINT32
PciePortNum (
  IN     UINT64  RpBase
  );

/**
  Get PCIe root port index
  @param[in] RpBase    Root Port pci segment base address
  @return Root Port index (0 based)
**/
UINT32
PciePortIndex (
  IN     UINT64  RpBase
  );

/**
  Translate PCIe Port/Lane pair to 0-based PCIe lane number.

  @param[in] RpIndex    Root Port index
  @param[in] RpLane     Root Port Lane

  @retval PCIe lane number (0-based)
**/
UINT32
PchPciePhysicalLane (
  UINT32 RpIndex,
  UINT32 RpLane
  );

/**
  Get the negotiated link width

  @param[in] RpBase    Root Port base address

  @return negotiated link width
**/
UINT8
PcieGetNegotiatedLinkWidth (
  UINT64  RpBase
  );

/**
  Checks if lane reversal is enabled on a given root port

  @param[in] RpIndex  Root port index (0-based)

  @retval TRUE if lane reversal is enbabled, FALSE otherwise
**/
BOOLEAN
IsPcieLaneReversalEnabled (
  IN     UINT32  RpIndex
  );

/**
  Calculates the index of the first port on the same controller.

  @param[in] RpIndex     Root Port Number (0-based)

  @retval Index of the first port on the first controller.
**/
UINT32
PchGetPcieFirstPortIndex (
  IN     UINT32  RpIndex
  );

/*
  Returns Tpower_on capability of device

  @param[in] DeviceBase       device's PCI segment base address
  @param[in] L1ssCapOffset    offset to L1substates capability in device's extended config space

  @retval                     structure containing Tpoweron scale and value
*/
T_POWER_ON
GetTpoCapability (
  UINT64 DeviceBase,
  UINT32 L1ssCapOffset
  );

/*
  Converts Tpower_on from value:scale notation to microseconds

  @param[in] TpoScale   T power on scale
  @param[in] TpoValue   T power on value

  @retval    number of microseconds
*/
UINT32
TpoToUs (
  UINT32 TpoScale,
  UINT32 TpoValue
  );

/**
PCIe controller Sku.
**/

typedef enum {
  EnumPchPcie = 0,
  EnumiTbtPcie = 1,
  EnumCpuPcie = 2,
  EnumPciSkuMax = 3
} PCI_SKU;

/*
  Initializes the following features in rootport and devices behind it:
  Maximum Payload Size (generic)
  Rootport packet split (proprietary)
  EonOfInterrupt forwarding (proprietary)
  Common Clock Configuration (generic)

  Generic: any code written according to PCIE Express base specification can do that.
  Proprietary: code uses registers and features that are specific to Intel silicon
  and probably only this Reference Code knows how to handle that.

  If OEM implemented generic feature enabling in his platform code or trusts Operating System
  to do it, then those features can be deleted from here.

  CCC requires link retrain, which takes a while. CCC must happen before L0s/L1 programming.
  If there was guarantee no code would access PCI while links retrain, it would be possible to skip this waiting

  @param[in] RpSegment  address of rootport on PCIe
  @param[in] RpBus      address of rootport on PCIe
  @param[in] RpDevice   address of rootport on PCIe
  @param[in] RpFunction address of rootport on PCIe
  @param[in] BusMin     minimum Bus number that can be assigned below this rootport
  @param[in] BusMax     maximum Bus number that can be assigned below this rootport
*/
VOID
RootportDownstreamConfiguration (
  UINT8                     RpSegment,
  UINT8                     RpBus,
  UINT8                     RpDevice,
  UINT8                     RpFunction,
  UINT8                     BusMin,
  UINT8                     BusMax,
  PCI_SKU                   PciSku
  );

/*
  Configures the following power-management related features in rootport and devices behind it:
  LTR limit (generic)
  LTR override (proprietary)
  Clock Power Management (generic)
  L1 substates (generic except for the override table)
  L1.LOW substate (proprietary)
  L0s and L1 (generic)

  Generic: any code written according to PCIE Express base specification can do that.
  Proprietary: code uses registers and features that are specific to Intel silicon
  and probably only this Reference Code knows how to handle that.

  If OEM implemented generic feature enabling in his platform code or trusts Operating System
  to do it, then those features can be deleted from here.

  @param[in] RpSegment                address of rootport on PCIe
  @param[in] RpBus                    address of rootport on PCIe
  @param[in] RpDevice                 address of rootport on PCIe
  @param[in] RpFunction               address of rootport on PCIe
  @param[in] BusLimit                 maximum Bus number that can be assigned below this rootport
  @param[in] AspmOverrideTableSize    size of override array
  @param[in] AspmOverrideTable        array of device that need exceptions in configuration
*/
VOID
RootportDownstreamPmConfiguration (
  UINT8                               RpSegment,
  UINT8                               RpBus,
  UINT8                               RpDevice,
  UINT8                               RpFunction,
  UINT8                               BusMin,
  UINT8                               BusMax,
  PCIE_LTR_CONFIG                     *PcieRpLtrConfig,
  PCIE_ROOT_PORT_COMMON_CONFIG        *PcieRpCommonConfig,
  UINT32                              AspmOverrideTableSize,
  PCH_PCIE_DEVICE_OVERRIDE            *AspmOverrideTable
  );

typedef struct {
  UINT32 MaxSnoopLatencyValue         : 10;
  UINT32 MaxSnoopLatencyScale         : 3;
  UINT32 MaxNoSnoopLatencyValue       : 10;
  UINT32 MaxNoSnoopLatencyScale       : 3;
  UINT32 Reserved                     : 6;
} LTR_LIMIT;

/**
Configures the following power-management related features in rootport and devices behind it:
LTR limit (generic)
L0s and L1 (generic)

Generic: any code written according to PCIE Express base specification can do that.

@param[in] RpSegment                address of rootport on PCIe
@param[in] RpBus                    address of rootport on PCIe
@param[in] RpDevice                 address of rootport on PCIe
@param[in] RpFunction               address of rootport on PCIe
@param[in] PolicyLtr                table with MaxSnoop and MaxNoSnoop Latency values to be programmed
**/
VOID
TcssRootportDownstreamPmConfiguration(
  UINT8                     RpSegment,
  UINT8                     RpBus,
  UINT8                     RpDevice,
  UINT8                     RpFunction,
  LTR_LIMIT                 PolicyLtr
);

/**
  Get current PCIe link speed.

  @param[in] RpBase    Root Port base address
  @return Link speed
**/
UINT32
GetLinkSpeed (
  UINT64  RpBase
  );

/**
  Get max PCIe link speed supported by the root port.

  @param[in] RpBase    Root Port pci segment base address
  @return Max link speed
**/
UINT32
GetMaxLinkSpeed (
  UINT64 RpBase
  );

/**
  PCIe controller configuration.
**/
typedef enum {
  Pcie4x1      = 0,
  Pcie1x2_2x1  = 1,
  Pcie2x2      = 2,
  Pcie1x4      = 3
} PCIE_CONTROLLER_CONFIG;

/**
  Extended Virtual Channel Configuration
**/
typedef struct {
  UINT16 CapOffset;
  UINT8  ExtVcCount;
} MULTI_VC_SUPPORT;

/**
  This function checks if both root port and end point supports MultiVC and enables it only if both supports MultiVc

  @param[in] Segment,Bus,Device,Function    address of currently visited PCIe device

  @return    Multi Virtual channel capability offset and count supported by the Root Port
**/
MULTI_VC_SUPPORT
RecursiveMultiVcConfiguration (
  SBDF       Sbdf
  );

/**
  This function enables MultiVc support

  @param[in] Segment,Bus,Device,Function    address of currently visited PCIe device
  @param[in] MULTI_VC_SUPPORT               Multi Virtual channel capability offset and count
**/
VOID
EnableMultiVc (
  SBDF              Sbfd,
  MULTI_VC_SUPPORT  ExtVc
  );

#endif // _PCI_EXPRESS_HELPERS_LIB_H_
