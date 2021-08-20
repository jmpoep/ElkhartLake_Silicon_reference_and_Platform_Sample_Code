/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2017 Intel Corporation.

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
#ifndef _SMM_TBT_COMMON_LIB_H_
#define _SMM_TBT_COMMON_LIB_H_

#include <Library/BaseLib.h>
#include <Library/TbtCommonLib.h>
#include <IndustryStandard/Pci.h>
#include <Library/BaseMemoryLib.h>

#define MAX_TBT_DEPTH         6

#define P2P_BRIDGE            (((PCI_CLASS_BRIDGE) << 8) | (PCI_CLASS_BRIDGE_P2P))

#define BAR_ALIGN(v, a)       ((((v) - 1) | (a)) + 1)

#define CMD_BUS_MASTER        BIT2
#define CMD_BM_IO             (CMD_BUS_MASTER | BIT0)
#define CMD_BM_MEM            (CMD_BUS_MASTER | BIT1)
#define CMD_BM_MEM_IO         (CMD_BUS_MASTER | BIT1 | BIT0)

#define DOCK_BUSSES           8

#define DISBL_IO_REG1C        0x01F1
#define DISBL_MEM32_REG20     0x0000FFF0
#define DISBL_PMEM_REG24      0x0001FFF1

#define DEF_CACHE_LINE_SIZE   0x20
#define DEF_RES_IO_PER_DEV    4
#define DEF_RES_MEM_PER_DEV   32
#define DEF_RES_PMEM_PER_DEV  32

#define PCIE_CAP_ID_SSID_SSVID 0x0D
#define INVALID_PCI_DEVICE    0xFFFFFFFF
#define PCI_TBT_VESC_REG2     0x510

typedef struct _PortInfo {
  UINT8   IoBase;
  UINT8   IoLimit;
  UINT16  MemBase;
  UINT16  MemLimit;
  UINT64  PMemBase64;
  UINT64  PMemLimit64;
  UINT8   BusNumLimit;
  UINT8   ConfedEP;
} PORT_INFO;

typedef struct _MEM_REGS {
  UINT32  Base;
  UINT32  Limit;
} MEM_REGS;

typedef struct _PMEM_REGS {
  UINT64  Base64;
  UINT64  Limit64;
} PMEM_REGS;

typedef struct _IO_REGS {
  UINT16  Base;
  UINT16  Limit;
} IO_REGS;

typedef struct _BRDG_RES_CONFIG {
  UINT8   Cmd;
  UINT8   Cls;
  UINT8   IoBase;
  UINT8   IoLimit;
  UINT16  MemBase;
  UINT16  MemLimit;
  UINT64  PMemBase64;
  UINT64  PMemLimit64;
} BRDG_RES_CONFIG;

typedef struct _BRDG_CONFIG {
  DEV_ID          DevId;
  UINT8           PBus;
  UINT8           SBus;
  UINT8           SubBus;
  BOOLEAN         IsDSBridge;
  BRDG_RES_CONFIG Res;
} BRDG_CONFIG;

STATIC const BRDG_RES_CONFIG  NOT_IN_USE_BRIDGE = {
  CMD_BUS_MASTER,
  0,
  DISBL_IO_REG1C & 0xFF,
  DISBL_IO_REG1C >> 8,
  DISBL_MEM32_REG20 & 0xFFFF,
  DISBL_MEM32_REG20 >> 16,
  DISBL_PMEM_REG24 & 0xFFFF,
  DISBL_PMEM_REG24 >> 16
};

typedef union _BRDG_CIO_MAP_REG {
  UINT32  AB_REG;
  struct {
    UINT32  NumOfDSPorts : 5;
    UINT32  CioPortMap : 27;
  } Bits;
} BRDG_CIO_MAP_REG;

VOID
PortInfoInit (
  IN  OUT PORT_INFO *PortInfo
  );

VOID
UnsetVesc (
  IN       UINT8     Bus,
  IN       UINT8     Dev,
  IN       UINT8     Fun
  );

VOID
ConfigurePort (
  IN       UINT8      Bus,
  IN       UINT8      Dev,
  IN       UINT8      Fun,
  IN  OUT  PORT_INFO  *PortInfo
  );

VOID
DisablePCIDevicesAndBridges (
  IN UINT8 MinBus,
  IN UINT8 MaxBus
  );

#endif
