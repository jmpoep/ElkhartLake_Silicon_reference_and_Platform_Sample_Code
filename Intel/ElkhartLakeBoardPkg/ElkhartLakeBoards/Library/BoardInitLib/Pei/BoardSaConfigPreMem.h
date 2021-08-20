/** @file
  PEI Boards Configurations for PreMem phase.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#ifndef _BOARD_SA_CONFIG_PRE_MEM_H_
#define _BOARD_SA_CONFIG_PRE_MEM_H_

#include <Ppi/SiPolicy.h>
#include <Library/BoardConfigLib.h>

//
// LPDDR3 / LPDDR4 RVP boards (memory soldered down)
// Single SPD EEPROM at 0xA2 serves both C0D0 and C1D0 (LPDDR3/4 is 1DPC only)
//
#define DIMM_SMB_SPD_P0C0D0_STP 0xA2
#define DIMM_SMB_SPD_P0C0D1_STP 0xA0
#define DIMM_SMB_SPD_P0C1D0_STP 0xA2
#define DIMM_SMB_SPD_P0C1D1_STP 0xA0
#define SA_MRC_MAX_RCOMP_TARGETS  (5)

GLOBAL_REMOVE_IF_UNREFERENCED const UINT16 EhlRcompTargetZeroes[SA_MRC_MAX_RCOMP_TARGETS] = { 0, 0, 0, 0, 0 };

//
// Reference RCOMP resistors on motherboard
//
GLOBAL_REMOVE_IF_UNREFERENCED const UINT16 EhlRcompResistorZero = 0;

//
// EHL-U SDS ERB board RCOMP target values for RdOdt, WrDS, WrDSCmd, WrDSCtl, WrDSClk - MRC will set automatically
//
GLOBAL_REMOVE_IF_UNREFERENCED const UINT16 RcompTargetEhl[SA_MRC_MAX_RCOMP_TARGETS] = { 0, 0, 0, 0, 0 };

//
// EHL LPDDR4 Type-4 RVP DQS byte swizzling between CPU and DRAM
//
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 DqsMapCpu2DramEhlLp4Type4Rvp[2][8] = {
  { 3, 0, 1, 2, 7, 4, 5, 6 }, // Channel 0
  { 3, 0, 1, 2, 7, 4, 5, 6 }  // Channel 1
};

//
// JSL LPDDR4 Type-4 RVP DQS byte swizzling between CPU and DRAM
//
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 DqsMapCpu2DramJslLp4Type4Rvp[2][8] = {
  { 3, 0, 1, 2, 7, 4, 5, 6 }, // Channel 0
  { 3, 0, 1, 2, 7, 4, 5, 6 }  // Channel 1
};

//
// JSL LPDDR4x ERB DQS byte swizzling between CPU and DRAM
//
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 DqsMapCpu2DramJslLp4xErb[2][8] = {
  { 0, 3, 2, 1, 7, 5, 4, 6 }, // Channel 0
  { 3, 1, 2, 0, 4, 7, 6, 5 }  // Channel 1
};

//
// DQ byte mapping to CMD/CTL/CLK, from the CPU side
// Used for EHL-U LPDDR4 SDS, EHL-U LPDDR4 Type-4 RVP
//
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 DqByteMapEhl[2][6][2] = {
  // Channel 0:
  {
    { 0x0F, 0xF0 }, // CLK0 goes to package 0 - Bytes[3:0], CLK1 goes to package 1 - Bytes[7:4]
    { 0x0F, 0xF0 }, // Cmd CAA goes to Bytes[3:0], Cmd CAB goes to Byte[7:4]
    { 0xFF, 0x00 }, // CTL (CS) goes to all bytes
    { 0x00, 0x00 }, // Unused in EHL MRC
    { 0x00, 0x00 }, // Unused in EHL MRC
    { 0x00, 0x00 }, // Unused in EHL MRC
  },
  // Channel 1:
  {
    { 0x0F, 0xF0 }, // CLK0 goes to package 0 - Bytes[3:0], CLK1 goes to package 1 - Bytes[7:4]
    { 0x0F, 0xF0 }, // Cmd CAA goes to Bytes[3:0], Cmd CAB goes to Byte[7:4]
    { 0xFF, 0x00 }, // CTL (CS) goes to all bytes
    { 0x00, 0x00 }, // Unused in EHL MRC
    { 0x00, 0x00 }, // Unused in EHL MRC
    { 0x00, 0x00 }, // Unused in EHL MRC
  }
};

//
// DQ byte mapping to CMD/CTL/CLK, from the CPU side
// Used for JSL LPDDR4 RVP
//
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 DqByteMapJsl[2][6][2] = {
  // Channel 0:
  {
    { 0x0F, 0xF0 }, // CLK0 goes to package 0 - Bytes[3:0], CLK1 goes to package 1 - Bytes[7:4]
    { 0x0F, 0xF0 }, // Cmd CAA goes to Bytes[3:0], Cmd CAB goes to Byte[7:4]
    { 0xFF, 0x00 }, // CTL (CS) goes to all bytes
    { 0x00, 0x00 }, // Unused in JSL MRC
    { 0x00, 0x00 }, // Unused in JSL MRC
    { 0x00, 0x00 }, // Unused in JSL MRC
  },
  // Channel 1:
  {
    { 0x0F, 0xF0 }, // CLK0 goes to package 0 - Bytes[3:0], CLK1 goes to package 1 - Bytes[7:4]
    { 0x0F, 0xF0 }, // Cmd CAA goes to Bytes[3:0], Cmd CAB goes to Byte[7:4]
    { 0xFF, 0x00 }, // CTL (CS) goes to all bytes
    { 0x00, 0x00 }, // Unused in JSL MRC
    { 0x00, 0x00 }, // Unused in JSL MRC
    { 0x00, 0x00 }, // Unused in JSL MRC
  }
};

#endif // _BOARD_SA_CONFIG_PRE_MEM_H_
