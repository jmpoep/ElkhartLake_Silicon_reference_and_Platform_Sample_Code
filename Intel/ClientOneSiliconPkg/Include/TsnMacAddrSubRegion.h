/** @file
  Tsn Mac Address Sub Region Struct

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

#ifndef _TSN_MAC_ADDR_SUB_REGION_H_
#define _TSN_MAC_ADDR_SUB_REGION_H_

#include <TsnConfig.h>

#define MAC_ADDR_SUB_REGION_SIZE_MAX          4096
#ifndef TSN_PORT_MAX
#define TSN_PORT_MAX                          4
#endif
#define MAC_ADDR_SUB_REGION_SIGNATURE_SIZE    256                        // Assume SHA256

#pragma pack(1)

//
// This struct will be consumes by BIOS & PSE FW
//
typedef struct {
  BDF                   Bdf;                                             // Associated PCI (Bus:Dev:Fnc), ECAM format
  union {
    UINT64              U64MacAddr;                                      // MAC address associated with this port
    UINT32              U32MacAddr[2];                                   // MAC address associated with this port
    UINT8               U8MacAddr[6];                                    // MAC address associated with this port
  } MacAddr;
} TSN_MAC_ADDR;

typedef struct {
  UINT32                Version;                                         // Data format version
  UINT32                NumPorts;                                        // Number of valid ia_tsn_mac_addrs in this sturctures
  TSN_MAC_ADDR          Port[TSN_PORT_MAX];                              // TSN MAC address structures
  UINT8                 Signature[MAC_ADDR_SUB_REGION_SIGNATURE_SIZE];   // Signature of the relevant data in this structure
} MAC_CONFIG_DATA;

typedef union {
  UINT8                 Data[MAC_ADDR_SUB_REGION_SIZE_MAX];              // Ensures the data structure consumes SIZE_MAX
  MAC_CONFIG_DATA       Config;
} TSN_MAC_ADDR_SUB_REGION;

#pragma pack()

#endif
