/** @file
  Header file for Board Information boot time changes.

  @par Revision Reference:
  Intel Framework Specifications, all available at: http://www.intel.com/technology/framework/spec.htm
  Unified Extensible Firmware Interface (UEFI) Specifications: http://www.uefi.org/specs/

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2018 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#ifndef _BOARDIDS_LIB_H_
#define _BOARDIDS_LIB_H_

extern CHAR16 *mBoardIdIndex[];
extern UINT8 mSizeOfmBoardIndex;

typedef union {
  UINT8    InputPort0Raw;
  struct {
    UINT8  BomId          :1;   // [0]    - BOM_ID[4]
    UINT8  FabId          :2;   // [2:1]  - Fab_IDx
    UINT8  SpdPresent     :1;   // [3]    - SPD_PRSNT
    UINT8  VirtualBattery :1;   // [4]    - VIRTUAL_BATTERY
    UINT8  VirtualDock    :1;   // [5]    - VIRTUAL_DOCK_DET_N
    UINT8  MemId          :2;   // [7:6]  - MEM_ID
  } InputPort0Fields;
} SMBUS_INPUT_PORT0;

typedef union {
  UINT8    InputPort1Raw;
  struct {
    UINT8  BoardId        :4;   // [3:0]   - BOARD_IDx
    UINT8  BomId          :4;   // [7:4]   - BOM_ID[3:0]
  } InputPort1Fields;
} SMBUS_INPUT_PORT1;

//
// PCA9555 device slave address
//
#define SMBUS_IO_EXPANDER_SLAVE_ADDRESS    0x22

//
// PCA9555 command byte
// -------   ------------
// Command     Register
// -------   ------------
//   0x0     Input Port 0
//   0x1     Input Port 1
#define SMBUS_IO_EXPANDER_INPUT_PORT0_CMD   0x0
#define SMBUS_IO_EXPANDER_INPUT_PORT1_CMD   0x1

#endif