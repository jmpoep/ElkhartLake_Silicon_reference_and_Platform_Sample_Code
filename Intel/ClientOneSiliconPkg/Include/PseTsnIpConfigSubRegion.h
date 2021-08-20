/** @file
  Pse Tsn Ip Config Sub Region Struct

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

#ifndef _PSE_TSN_IP_CONFIG_SUB_REGION_H_
#define _PSE_TSN_IP_CONFIG_SUB_REGION_H_

#include <TsnConfig.h>

#define IP_SUB_REGION_SIZE_MAX                4096
#define PSE_GBE_PORT_MAX                      4
#define DNS_SERVER_ENTRY_MAX                  4
#define IP_SUB_REGION_SIGNATURE_SIZE          256                        // Assume SHA256

#pragma pack(1)

//
// This struct will be consumed by PSE FW only
//
typedef struct {
  BDF                   Bdf;                                             // Associated PCI (Bus:Dev:Fnc), ECAM format
  UINT32                Valid;                                           // 0 = not valid, else = valid
  UINT32                StaticIp;                                        // 0 = Dynamic IP from DHCPv4, else = Static IP
  UINT8                 Ipv4Addr[4];                                     // 32bit ipv4 address associated with this port
  UINT8                 Ipv6Addr[16];                                    // 128bit ipv6 address associated with this port
  UINT8                 SubnetMask[4];                                   // 32bit ipv4 subnet address associated with this port
  UINT8                 Gateway[4];                                      // 32bit ipv4 gateway address associated with this port
  UINT32                DnsSrvNum;
  UINT8                 DnsSrvAddr[DNS_SERVER_ENTRY_MAX][4];             // 32bit ipv4 dns server address associated with this port
  UINT8                 ProxyAddr[4];                                    // 32bit ipv4 proxy server address associated with this port
  UINT32                ProxyPort;
} PSE_TSN_IP_CONFIG;

typedef struct {
  UINT32                Version;                                         // Data format version
  UINT32                NumPorts;                                        // Number of valid pse_tsn_ip_addrs in this structure
  PSE_TSN_IP_CONFIG     Port[PSE_GBE_PORT_MAX];                          // IP addresses structures
  UINT8                 Signature[IP_SUB_REGION_SIGNATURE_SIZE];         // Signature of the relevant data in this structure
} IP_CONFIG_DATA;

typedef union {
  UINT8                 Data[IP_SUB_REGION_SIZE_MAX];                    // Ensures the data structure consumes SIZE_MAX
  IP_CONFIG_DATA        Config;
} PSE_IP_CONFIG_SUB_REGION;

#pragma pack()

#endif
