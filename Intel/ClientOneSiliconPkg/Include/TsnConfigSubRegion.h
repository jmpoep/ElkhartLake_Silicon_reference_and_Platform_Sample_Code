/** @file
  Tsn Config Sub Region Struct

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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

@par Specification
**/

#ifndef _TSN_CONFIG_SUB_REGION_H_
#define _TSN_CONFIG_SUB_REGION_H_

#include <TsnConfig.h>

#define TSN_SUB_REGION_SIZE_MAX          4096
#ifndef TSN_PORT_MAX
#define TSN_PORT_MAX                     4
#endif
#define TSN_SUB_REGION_SIGNATURE_SIZE    256                      // Assume SHA256
#define TSN_CBS_QUEUE_MAX                8
#define TSN_EST_GC_LIST_MAX              20

#pragma pack(1)

typedef struct {
  UINT32                Bandwidth;
} TSN_CBS_QUEUE;

typedef struct {
  UINT32                Valid;                                    // 0 = not valid, else = valid
  UINT32                NumQueues;
  TSN_CBS_QUEUE         Queue[TSN_CBS_QUEUE_MAX];
} TSN_CBS;

typedef enum {
  TsnEstGcHold          = 0x00000000,
  TsnEstGcRelease       = 0x00000001,
  TsnEstGcSet           = 0x00000002,
  TsnEstGcOpModeMax     = 0xFFFFFFFF                              // Ensure 4 bytes allocated
} TSN_EST_GC_OP_MODES;

typedef struct {
  UINT32                GateControl;
  UINT32                TimeIntervalNsec;
  TSN_EST_GC_OP_MODES   OperationMode;
} TSN_EST_GC;

typedef struct {
  UINT32                Valid;                                    // 0 = not valid, else = valid
  UINT32                BaseTimeNsec;
  UINT32                BaseTimeSec;
  UINT32                CycleTimeNsec;
  UINT32                CycleTimeSec;
  UINT32                TimeExtensionNsec;
  UINT32                NumQcLists;
  TSN_EST_GC            GcList[TSN_EST_GC_LIST_MAX];
} TSN_EST;

typedef struct {
  UINT32                Valid;                                    // 0 = not valid, else = valid
  UINT32                HoldAdvanceNsec;
  UINT32                ReleaseAdvanceNsec;
  UINT32                AdditionalFragment;
  UINT32                FramePreemptionStatusTable;
} TSN_FPE;

typedef struct {
  UINT32                Valid;                                    // 0 = not valid, else = valid
  UINT32                TbsQueues;                                // Corresponding bits refer to queue number and set/unset represent that queue uses tbs or not
} TSN_TBS;

//
// This struct will be consumed by PSE FW only as tsn config only valid when PSE owned
//
typedef struct {
  UINT32                Valid;                                    // 0 = not valid, else = valid
  TSN_CBS               Cbs;                                      // CBS 802.1Qav configuration data
  TSN_EST               Est;                                      // EST 802.1Qbv configuration data
  TSN_FPE               Fpe;                                      // FPE 802.1Qbu configuration data
  TSN_TBS               Tbs;                                      // TBS configuration data
} PSE_TSN_MAC_CONFIG;

typedef union {
  UINT32  Data;
  struct {
  UINT32  RxCh0         : 1;                                      // [0] Map to Rx DMA Channel 0
  UINT32  TxCh0         : 1;                                      // [1] Map to Tx DMA Channel 0
  UINT32  RxCh1         : 1;                                      // [2] Map to Rx DMA Channel 1
  UINT32  TxCh1         : 1;                                      // [3] Map to Tx DMA Channel 1
  UINT32  RxCh2         : 1;                                      // [4] Map to Rx DMA Channel 2
  UINT32  TxCh2         : 1;                                      // [5] Map to Tx DMA Channel 2
  UINT32  RxCh3         : 1;                                      // [6] Map to Rx DMA Channel 3
  UINT32  TxCh3         : 1;                                      // [7] Map to Tx DMA Channel 3
  UINT32  RxCh4         : 1;                                      // [8] Map to Rx DMA Channel 4
  UINT32  TxCh4         : 1;                                      // [9] Map to Tx DMA Channel 4
  UINT32  RxCh5         : 1;                                      // [10] Map to Rx DMA Channel 5
  UINT32  TxCh5         : 1;                                      // [11] Map to Tx DMA Channel 5
  UINT32  RxCh6         : 1;                                      // [12] Map to Rx DMA Channel 6
  UINT32  TxCh6         : 1;                                      // [13] Map to Tx DMA Channel 6
  UINT32  RxCh7         : 1;                                      // [14] Map to Rx DMA Channel 7
  UINT32  TxCh7         : 1;                                      // [15] Map to Tx DMA Channel 7
  UINT32  RxCh8         : 1;                                      // [16] Map to Rx DMA Channel 8
  UINT32  TxCh8         : 1;                                      // [17] Map to Tx DMA Channel 8
  UINT32  RxCh9         : 1;                                      // [18] Map to Rx DMA Channel 9
  UINT32  TxCh9         : 1;                                      // [19] Map to Tx DMA Channel 9
  UINT32  RxCh10        : 1;                                      // [20] Map to Rx DMA Channel 10
  UINT32  TxCh10        : 1;                                      // [21] Map to Tx DMA Channel 10
  UINT32  RxCh11        : 1;                                      // [22] Map to Rx DMA Channel 11
  UINT32  TxCh11        : 1;                                      // [23] Map to Tx DMA Channel 11
  UINT32  RxCh12        : 1;                                      // [24] Map to Rx DMA Channel 12
  UINT32  TxCh12        : 1;                                      // [25] Map to Tx DMA Channel 12
  UINT32  RxCh13        : 1;                                      // [26] Map to Rx DMA Channel 13
  UINT32  TxCh13        : 1;                                      // [27] Map to Tx DMA Channel 13
  UINT32  RxCh14        : 1;                                      // [28] Map to Rx DMA Channel 14
  UINT32  TxCh14        : 1;                                      // [29] Map to Tx DMA Channel 14
  UINT32  RxCh15        : 1;                                      // [30] Map to Rx DMA Channel 15
  UINT32  TxCh15        : 1;                                      // [31] Map to Tx DMA Channel 15
  } Fields;
} DMA_VC_TC_BIT;

//
// This struct will be consumed by BIOS only as VC/TC config only valid when host owned
//
typedef struct {
  UINT32                Valid;                                    // 0 = not valid, else = valid
  /**
    Assumption: TC0 always map to VC0, TC1 always map to VC1

    Bit value 0 = VC0/TC0, Bit value 1 = VC1/TC1
    Bit[1, 3, 5, 7, 9, 11, 13, 15] map to TX DMA channel 0 - 7
    Bit[0, 2, 4, 6, 8, 10, 12, 14] map to RX DMA channel 0 - 7
  **/
  DMA_VC_TC_BIT         DmaVcTcMap;                               // EHL default value = 0xFF00, TGL/ICL default value = 0x05E0
  UINT32                MsiVcTcMap;                               // The bit mapping is following MSI vector sequence
} VC_TC_MAC_CONFIG;

typedef struct {
  BDF                   Bdf;                                      // Associated PCI (Bus:Dev:Fnc), ECAM format
  PSE_TSN_MAC_CONFIG    TsnPort;                                  // TSN port configuration structures
  VC_TC_MAC_CONFIG      VcTcPort;                                 // VC/TC port configuration structures
} TSN_VC_TC_CONFIG;

typedef struct {
  UINT32                Version;                                  // Data format version
  UINT32                NumPorts;                                 // Number of valid ose_tsn_mac_configs in this structure
  TSN_VC_TC_CONFIG      Port[TSN_PORT_MAX];                       // TSN or VC/TC port configuration structures
  UINT8                 Signature[TSN_SUB_REGION_SIGNATURE_SIZE]; // Signature of the relevant data in this structure
} TSN_CONFIG_DATA;

typedef union {
  UINT8                 Data[TSN_SUB_REGION_SIZE_MAX];            // Enusres the data structure consumes SIZE_MAX
  TSN_CONFIG_DATA       Config;
} PSE_TSN_CONFIG_SUB_REGION;

#pragma pack()

#endif
