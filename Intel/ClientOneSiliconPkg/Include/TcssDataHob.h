/** @file
  This file contains definitions of TCSS Data.

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
#ifndef _TCSS_DATA_HOB_H_
#define _TCSS_DATA_HOB_H_

#include <Base.h>
#include <Register/HostDmaRegs.h>
#include <Register/ItbtPcieRegs.h>

extern EFI_GUID gTcssHobGuid;
#pragma pack (push,1)

///
/// Structure for Tbt firmware status from IMR.
///
typedef union {
  UINT32 RegValue;
  struct {
    UINT32 TbtFwVersion:16; ///< Bits 15:0
    UINT32 Reserved:6;      ///< Bits 21:16
    UINT32 ErrorCode:8;     ///< Bits 29:22
    UINT32 Valid:1;         ///< Bits 30    - 00 = untrusted FW, 01 = successful authentication
    UINT32 Done:1;          ///< Bits 31    - 01 = FW download to IMR is done
  } Bits;
} TBT_IMR_STATUS;

///
/// Structure for MG image status from IMR.
///
typedef union {
  UINT32 RegValue;
  struct {
    UINT32 MgFwVersion:16; ///< Bits 15:0
    UINT32 Reserved:6;     ///< Bits 21:16
    UINT32 ErrorCode:8;    ///< Bits 29:22
    UINT32 Valid:1;        ///< Bits 30    - 00 = untrusted FW, 01 = successful authentication
    UINT32 Done:1;         ///< Bits 31    - 01 = FW download to IMR is done
  } Bits;
} MG_IMR_STATUS;

/**
  TCSS data definition
**/
typedef struct {
  UINT32            IOMReady:1;                             ///< Indicate the IOM ready.
  UINT32            PcieMultipleSegmentEnabled:1;           ///< Indicate the extra segment of iTBT PCIe is enabled or not.
  UINT32            Rsvd:30;                                ///< Reserved for future use.
  UINT32            IomFwVersion;                           ///< IOM FW version.
  UINT32            IomFwEngrVersion;                       ///< IOM FW Engineer version. Non-zero value used to identify engineering versions / hotfixes. Shall be zero for official releases.
  TBT_IMR_STATUS    TbtImrStatus;                           ///< Tbt FW IMR Status.
  UINT32            ItbtPcieSegMap;                         ///< iTBT PCIE RP 0-3 Segment Map
  UINT32            ItbtPcieFuncMap;                        ///< iTBT PCIE RP 0-3 Function Map
  UINT8             ItbtPcieRpEn[MAX_ITBT_PCIE_PORT];       ///< ItbtPcieRpEn PCIE RP Device Enable
  UINT8             ItbtXhciEn;                             ///< ItbtPcieRpEn XHCI Device Enable
  UINT8             ItbtXdciEn;                             ///< ItbtPcieRpEn XDCI Device Enable
  UINT8             ItbtDmaEn[SA_MAX_HOST_ITBT_DMA_NUMBER]; ///< ItbtPcieRpEn DMA Device Enable
  UINT8             TcssxDCIInt;                            ///< iTBT xDCI Int Pin number
  UINT8             TcssxDCIIrq;                            ///< iTBT xDCI APIC IRQ number
  UINT8             TcssRtd3;                               ///< TCSS RTD3
  UINT8             ItbtForcePower;                         ///< iTBT Force Power status
  MG_IMR_STATUS     MgImrStatus;                            ///< MG IMR Status
  UINT8             TcssIomVccSt;                           ///< IOM VCCST request.
} TCSS_DATA;

typedef struct {
  UINT8   LtrEnable;                              ///< Latency Tolerance Reporting Mechanism. <b>0: Disable</b>; 1: Enable.
  UINT16  LtrMaxSnoopLatency;                     ///< Latency Tolerance Reporting, Max Snoop Latency.
  UINT16  LtrMaxNoSnoopLatency;                   ///< Latency Tolerance Reporting, Max Non-Snoop Latency.
  UINT8   SnoopLatencyOverrideMode;               ///< Latency Tolerance Reporting, Snoop Latency Override Mode.
  UINT8   SnoopLatencyOverrideMultiplier;         ///< Latency Tolerance Reporting, Snoop Latency Override Multiplier.
  UINT16  SnoopLatencyOverrideValue;              ///< Latency Tolerance Reporting, Snoop Latency Override Value.
  UINT8   NonSnoopLatencyOverrideMode;            ///< Latency Tolerance Reporting, Non-Snoop Latency Override Mode.
  UINT8   NonSnoopLatencyOverrideMultiplier;      ///< Latency Tolerance Reporting, Non-Snoop Latency Override Multiplier.
  UINT16  NonSnoopLatencyOverrideValue;           ///< Latency Tolerance Reporting, Non-Snoop Latency Override Value.
  UINT8   ForceLtrOverride;                       ///< <b>0: Disable</b>; 1: Enable.
  UINT8   LtrConfigLock;                          ///< <b>0: Disable</b>; 1: Enable.
} ITBT_PCILTR_DATA;

///
/// TCSS Data Hob
///
typedef struct {
  EFI_HOB_GUID_TYPE        EfiHobGuidType;                    ///< Offset 0 - 23: GUID Hob type structure for gTcssHobGuid
  TCSS_DATA                TcssData;                          ///< Offset 24 TCSS data definition.
  ITBT_PCILTR_DATA         PcieItbtLtrData[MAX_ITBT_PCIE_PORT];
} TCSS_DATA_HOB;
#pragma pack (pop)
#endif
