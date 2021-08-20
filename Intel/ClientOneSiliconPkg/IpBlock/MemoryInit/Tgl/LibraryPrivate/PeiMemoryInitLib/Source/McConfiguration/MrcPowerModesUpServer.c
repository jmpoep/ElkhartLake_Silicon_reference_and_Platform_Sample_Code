/** @file
  This module configures the memory controller power modes.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2017 Intel Corporation.

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

///
/// Include files
///
#ifdef UP_SERVER_FLAG
#include "MrcTypes.h"
#include "MrcApi.h"
#include "MrcPowerModes.h"
#include "MrcDebugPrint.h"
#include "MrcSpdProcessing.h"

GLOBAL_REMOVE_IF_UNREFERENCED const DdrUpPwEntry UpPowerLookUpTable[] = {
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_1, DPC_1, FREQ_2133, DENSITY_2,  0}}, 4, 138, 154, 169, 10,  6, 0x0, 0x2F, 0x13, 12},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_1, DPC_2, FREQ_2133, DENSITY_2,  0}}, 4, 169, 151, 168,  9,  6, 0x0, 0x20, 0x12, 8},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_2, DPC_2, FREQ_2133, DENSITY_2,  0}}, 4, 169, 151, 168,  9,  6, 0x0, 0x20, 0x12, 8},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_1, DPC_1, FREQ_2133, DENSITY_2,  0}}, 4,  91, 106, 188,  5,  2, 0x0, 0x25, 0x0D, 10},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_1, DPC_2, FREQ_2133, DENSITY_2,  0}}, 4, 116, 115, 188,  4,  2, 0x0, 0x18, 0x0B, 6},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_2, DPC_2, FREQ_2133, DENSITY_2,  0}}, 4, 116, 115, 188,  4,  2, 0x0, 0x18, 0x0B, 5},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_16,  RANKS_2, DIMM_POSITION_1, DPC_1, FREQ_2133, DENSITY_2,  0}}, 4,  79,  96, 142,  3,  1, 0x0, 0x14, 0x05, 5},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_16,  RANKS_2, DIMM_POSITION_1, DPC_2, FREQ_2133, DENSITY_2,  0}}, 4, 105, 104, 141,  3,  1, 0x0, 0x0D, 0x04, 3},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_16,  RANKS_2, DIMM_POSITION_2, DPC_2, FREQ_2133, DENSITY_2,  0}}, 4, 105, 104, 141,  3,  1, 0x0, 0x0D, 0x04, 3},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_1, DPC_1, FREQ_2133, DENSITY_4,  0}}, 3,  67,  70, 145,  6,  4, 0x0, 0x3D, 0x17, 5},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_1, DPC_2, FREQ_2133, DENSITY_4,  0}}, 3,  82,  73, 145,  6,  4, 0x0, 0x2A, 0x17, 4},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_2, DPC_2, FREQ_2133, DENSITY_4,  0}}, 3,  82,  73, 145,  6,  4, 0x0, 0x2A, 0x17, 3},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_1, DPC_1, FREQ_2133, DENSITY_4,  0}}, 4,  92, 100, 129,  7,  5, 0x0, 0x23, 0x0E, 9},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_1, DPC_2, FREQ_2133, DENSITY_4,  0}}, 4, 118, 108, 129,  7,  5, 0x0, 0x18, 0x0D, 6},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_2, DPC_2, FREQ_2133, DENSITY_4,  0}}, 4, 118, 108, 129,  7,  5, 0x0, 0x18, 0x0D, 5},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_16,  RANKS_2, DIMM_POSITION_1, DPC_1, FREQ_2133, DENSITY_4,  0}}, 5, 166, 187, 196,  9,  5, 0x0, 0x1A, 0x0F, 5},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_16,  RANKS_2, DIMM_POSITION_1, DPC_2, FREQ_2133, DENSITY_4,  0}}, 5, 217, 204, 196,  9,  5, 0x0, 0x0C, 0x04, 3},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_16,  RANKS_2, DIMM_POSITION_2, DPC_2, FREQ_2133, DENSITY_4,  0}}, 5, 217, 204, 196,  9,  5, 0x0, 0x0C, 0x04, 3},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_1, DPC_1, FREQ_2133, DENSITY_8,  0}}, 4, 137, 137,  85, 18, 11, 0x0, 0x2F, 0x1C, 12},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_1, DPC_2, FREQ_2133, DENSITY_8,  0}}, 4, 168, 142,  85, 17, 11, 0x0, 0x26, 0x1C, 10},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_2, DPC_2, FREQ_2133, DENSITY_8,  0}}, 4, 168, 142,  85, 17, 11, 0x0, 0x26, 0x1C, 10},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_1, DPC_1, FREQ_2133, DENSITY_8,  0}}, 5, 197, 210, 142, 19, 12, 0x0, 0x20, 0x12, 8},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_1, DPC_2, FREQ_2133, DENSITY_8,  0}}, 4, 124, 114,  71,  9,  6, 0x0, 0x19, 0x10, 6},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_2, DPC_2, FREQ_2133, DENSITY_8,  0}}, 4, 124, 114,  71,  9,  6, 0x0, 0x19, 0x10, 6},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_1, DPC_1, FREQ_2133, DENSITY_2,  0}}, 4, 125, 143, 169, 10,  6, 0x0, 0x27, 0x0D, 12},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_1, DPC_2, FREQ_2133, DENSITY_2,  0}}, 4, 160, 151, 169, 10,  6, 0x0, 0x1A, 0x0C, 8},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_2, DPC_2, FREQ_2133, DENSITY_2,  0}}, 4, 160, 151, 169, 10,  6, 0x0, 0x1A, 0x0C, 8},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_1, DPC_1, FREQ_2133, DENSITY_2,  0}}, 4,  80, 104, 189,  5,  2, 0x0, 0x22, 0x0A, 11},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_1, DPC_2, FREQ_2133, DENSITY_2,  0}}, 4, 109, 115, 188,  5,  2, 0x0, 0x16, 0x08, 6},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_2, DPC_2, FREQ_2133, DENSITY_2,  0}}, 4, 109, 115, 188,  5,  2, 0x0, 0x16, 0x08, 6},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_16,  RANKS_1, DIMM_POSITION_1, DPC_1, FREQ_2133, DENSITY_2,  0}}, 4,  68,  94, 142,  4,  1, 0x0, 0x14, 0x05, 5},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_16,  RANKS_1, DIMM_POSITION_1, DPC_2, FREQ_2133, DENSITY_2,  0}}, 4,  97, 105, 142,  3,  1, 0x0, 0x0D, 0x04, 3},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_16,  RANKS_1, DIMM_POSITION_2, DPC_2, FREQ_2133, DENSITY_2,  0}}, 4,  97, 105, 142,  3,  1, 0x0, 0x0D, 0x04, 3},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_1, DPC_1, FREQ_2133, DENSITY_4,  0}}, 3,  60,  69, 146,  7,  4, 0x0, 0x34, 0x10, 15},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_1, DPC_2, FREQ_2133, DENSITY_4,  0}}, 3,  77,  73, 145,  6,  4, 0x0, 0x21, 0x0F, 9},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_2, DPC_2, FREQ_2133, DENSITY_4,  0}}, 3,  77,  73, 145,  6,  4, 0x0, 0x21, 0x0F, 9},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_1, DPC_1, FREQ_2133, DENSITY_4,  0}}, 4,  81,  98, 130,  8,  5, 0x0, 0x1D, 0x0B, 9},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_1, DPC_2, FREQ_2133, DENSITY_4,  0}}, 4, 110, 108, 129,  7,  5, 0x0, 0x14, 0x09, 6},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_2, DPC_2, FREQ_2133, DENSITY_4,  0}}, 4, 110, 108, 129,  7,  5, 0x0, 0x14, 0x09, 5},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_16,  RANKS_1, DIMM_POSITION_1, DPC_1, FREQ_2133, DENSITY_4,  0}}, 5, 145, 183, 198, 11,  5, 0x0, 0x12, 0x05, 5},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_16,  RANKS_1, DIMM_POSITION_1, DPC_2, FREQ_2133, DENSITY_4,  0}}, 5, 202, 205, 196,  9,  5, 0x0, 0x0C, 0x04, 3},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_16,  RANKS_1, DIMM_POSITION_2, DPC_2, FREQ_2133, DENSITY_4,  0}}, 5, 202, 205, 196,  9,  5, 0x0, 0x0C, 0x04, 3},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_1, DPC_1, FREQ_2133, DENSITY_8,  0}}, 4, 124, 135,  86, 18, 11, 0x0, 0x23, 0x12, 11},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_1, DPC_2, FREQ_2133, DENSITY_8,  0}}, 4, 159, 142,  85, 18, 11, 0x0, 0x1B, 0x11, 8},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_2, DPC_2, FREQ_2133, DENSITY_8,  0}}, 4, 159, 142,  85, 18, 11, 0x0, 0x1B, 0x11, 8},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_1, DPC_1, FREQ_2133, DENSITY_8,  0}}, 5, 176, 206, 144, 21, 12, 0x0, 0x1A, 0x0C, 7},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_1, DPC_2, FREQ_2133, DENSITY_8,  0}}, 5, 233, 227, 142, 19, 12, 0x0, 0x14, 0x0B, 5},
    { { {  VDD_120, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_2, DPC_2, FREQ_2133, DENSITY_8,  0}}, 5, 233, 227, 142, 19, 12, 0x0, 0x14, 0x0B, 5},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_1, DPC_1, FREQ_1600, DENSITY_2,  0}}, 3,  81, 110, 128,  8,  5, 0x0, 0x37, 0x1A, 5},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_1, DPC_2, FREQ_1600, DENSITY_2,  0}}, 3, 154, 178, 127,  8,  5, 0x0, 0x2C, 0x17, 6},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_2, DPC_2, FREQ_1600, DENSITY_2,  0}}, 3, 154, 178, 127,  8,  5, 0x0, 0x2C, 0x17, 6},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_1, DPC_1, FREQ_1600, DENSITY_2,  0}}, 4,  98, 147, 128,  9,  5, 0x0, 0x20, 0x10, 2},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_1, DPC_2, FREQ_1600, DENSITY_2,  0}}, 3, 119, 144,  64,  4,  3, 0x0, 0x1D, 0x0F, 3},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_2, DPC_2, FREQ_1600, DENSITY_2,  0}}, 3, 119, 144,  64,  4,  3, 0x0, 0x1D, 0x0F, 3},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_1, DPC_1, FREQ_1600, DENSITY_4,  0}}, 3,  91, 119, 130, 10,  6, 0x0, 0x3B, 0x1C, 6},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_1, DPC_2, FREQ_1600, DENSITY_4,  0}}, 3, 164, 187, 129,  9,  6, 0x0, 0x2F, 0x1B, 7},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_2, DPC_2, FREQ_1600, DENSITY_4,  0}}, 3, 164, 187, 129,  9,  6, 0x0, 0x2F, 0x1B, 7},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_1, DPC_1, FREQ_1600, DENSITY_4,  0}}, 4, 110, 157, 130, 10,  6, 0x0, 0x23, 0x12, 3},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_1, DPC_2, FREQ_1600, DENSITY_4,  0}}, 3, 125, 149,  65,  5,  3, 0x0, 0x1F, 0x11, 4},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_2, DPC_2, FREQ_1600, DENSITY_4,  0}}, 3, 125, 149,  65,  5,  3, 0x0, 0x1F, 0x11, 4},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_1, DPC_1, FREQ_1600, DENSITY_2,  0}}, 3,  81, 111, 128,  9,  5, 0x0, 0x2D, 0x11, 5},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_1, DPC_2, FREQ_1600, DENSITY_2,  0}}, 3, 131, 157, 128,  9,  5, 0x0, 0x21, 0x10, 5},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_2, DPC_2, FREQ_1600, DENSITY_2,  0}}, 3, 131, 157, 128,  9,  5, 0x0, 0x21, 0x10, 4},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_1, DPC_1, FREQ_1600, DENSITY_2,  0}}, 4,  99, 148, 130, 10,  5, 0x0, 0x1C, 0x0C, 2},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_1, DPC_2, FREQ_1600, DENSITY_2,  0}}, 4, 194, 247, 129,  9,  5, 0x0, 0x17, 0x0C, 2},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_2, DPC_2, FREQ_1600, DENSITY_2,  0}}, 4, 194, 247, 129,  9,  5, 0x0, 0x17, 0x0C, 2},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_1, DPC_1, FREQ_1600, DENSITY_4,  0}}, 3,  92, 120, 130, 10,  6, 0x0, 0x30, 0x12, 6},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_1, DPC_2, FREQ_1600, DENSITY_4,  0}}, 3, 142, 166, 130, 10,  6, 0x0, 0x24, 0x11, 5},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_2, DPC_2, FREQ_1600, DENSITY_4,  0}}, 3, 142, 166, 130, 10,  6, 0x0, 0x24, 0x11, 5},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_1, DPC_1, FREQ_1600, DENSITY_4,  0}}, 3, 103, 128,  65,  5,  3, 0x0, 0x19, 0x0D, 2},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_1, DPC_2, FREQ_1600, DENSITY_4,  0}}, 4, 111, 158, 132, 12,  6, 0x0, 0x16, 0x0D, 3},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_2, DPC_2, FREQ_1600, DENSITY_4,  0}}, 4, 111, 158, 132, 12,  6, 0x0, 0x16, 0x0D, 2},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_1, DPC_1, FREQ_1867, DENSITY_2,  0}}, 3,  81, 110, 128,  8,  5, 0x0, 0x37, 0x1A, 5},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_1, DPC_2, FREQ_1867, DENSITY_2,  0}}, 3, 154, 178, 127,  8,  5, 0x0, 0x2C, 0x17, 6},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_2, DPC_2, FREQ_1867, DENSITY_2,  0}}, 3, 154, 178, 127,  8,  5, 0x0, 0x2C, 0x17, 6},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_1, DPC_1, FREQ_1867, DENSITY_2,  0}}, 4,  98, 147, 128,  9,  5, 0x0, 0x20, 0x10, 2},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_1, DPC_2, FREQ_1867, DENSITY_2,  0}}, 3, 119, 144,  64,  4,  3, 0x0, 0x1D, 0x0F, 3},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_2, DPC_2, FREQ_1867, DENSITY_2,  0}}, 3, 119, 144,  64,  4,  3, 0x0, 0x1D, 0x0F, 3},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_1, DPC_1, FREQ_1867, DENSITY_4,  0}}, 3,  91, 119, 130, 10,  6, 0x0, 0x3B, 0x1C, 6},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_1, DPC_2, FREQ_1867, DENSITY_4,  0}}, 3, 164, 187, 129,  9,  6, 0x0, 0x2F, 0x1B, 7},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_2, DPC_2, FREQ_1867, DENSITY_4,  0}}, 3, 164, 187, 129,  9,  6, 0x0, 0x2F, 0x1B, 7},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_1, DPC_1, FREQ_1867, DENSITY_4,  0}}, 4, 110, 157, 130, 10,  6, 0x0, 0x23, 0x12, 3},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_1, DPC_2, FREQ_1867, DENSITY_4,  0}}, 3, 125, 149,  65,  5,  3, 0x0, 0x1F, 0x11, 4},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_2, DPC_2, FREQ_1867, DENSITY_4,  0}}, 3, 125, 149,  65,  5,  3, 0x0, 0x1F, 0x11, 4},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_1, DPC_1, FREQ_1867, DENSITY_2,  0}}, 3,  81, 111, 128,  9,  5, 0x0, 0x2D, 0x11, 5},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_1, DPC_2, FREQ_1867, DENSITY_2,  0}}, 3, 131, 157, 128,  9,  5, 0x0, 0x21, 0x10, 5},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_2, DPC_2, FREQ_1867, DENSITY_2,  0}}, 3, 131, 157, 128,  9,  5, 0x0, 0x21, 0x10, 4},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_1, DPC_1, FREQ_1867, DENSITY_2,  0}}, 4,  99, 148, 130, 10,  5, 0x0, 0x1C, 0x0C, 2},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_1, DPC_2, FREQ_1867, DENSITY_2,  0}}, 4, 194, 247, 129,  9,  5, 0x0, 0x17, 0x0C, 2},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_2, DPC_2, FREQ_1867, DENSITY_2,  0}}, 4, 194, 247, 129,  9,  5, 0x0, 0x17, 0x0C, 2},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_1, DPC_1, FREQ_1867, DENSITY_4,  0}}, 3,  92, 120, 130, 10,  6, 0x0, 0x30, 0x12, 6},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_1, DPC_2, FREQ_1867, DENSITY_4,  0}}, 3, 142, 166, 130, 10,  6, 0x0, 0x24, 0x11, 5},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_2, DPC_2, FREQ_1867, DENSITY_4,  0}}, 3, 142, 166, 130, 10,  6, 0x0, 0x24, 0x11, 5},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_1, DPC_1, FREQ_1867, DENSITY_4,  0}}, 3, 103, 128,  65,  5,  3, 0x0, 0x19, 0x0D, 2},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_1, DPC_2, FREQ_1867, DENSITY_4,  0}}, 4, 111, 158, 132, 12,  6, 0x0, 0x16, 0x0D, 3},
    { { {  VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_2, DPC_2, FREQ_1867, DENSITY_4,  0}}, 4, 111, 158, 132, 12,  6, 0x0, 0x16, 0x0D, 2},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_1, DPC_1, FREQ_1600, DENSITY_2,  0}}, 3,  81, 110, 128,  8,  5, 0x0, 0x37, 0x1A, 5},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_1, DPC_2, FREQ_1600, DENSITY_2,  0}}, 3, 154, 178, 127,  8,  5, 0x0, 0x2C, 0x17, 6},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_2, DPC_2, FREQ_1600, DENSITY_2,  0}}, 3, 154, 178, 127,  8,  5, 0x0, 0x2C, 0x17, 6},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_1, DPC_1, FREQ_1600, DENSITY_2,  0}}, 4,  98, 147, 128,  9,  5, 0x0, 0x20, 0x10, 2},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_1, DPC_2, FREQ_1600, DENSITY_2,  0}}, 3, 119, 144,  64,  4,  3, 0x0, 0x1D, 0x0F, 3},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_2, DPC_2, FREQ_1600, DENSITY_2,  0}}, 3, 119, 144,  64,  4,  3, 0x0, 0x1D, 0x0F, 3},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_1, DPC_1, FREQ_1600, DENSITY_4,  0}}, 3,  91, 119, 130, 10,  6, 0x0, 0x3B, 0x1C, 6},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_1, DPC_2, FREQ_1600, DENSITY_4,  0}}, 3, 164, 187, 129,  9,  6, 0x0, 0x2F, 0x1B, 7},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_2, DPC_2, FREQ_1600, DENSITY_4,  0}}, 3, 164, 187, 129,  9,  6, 0x0, 0x2F, 0x1B, 7},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_1, DPC_1, FREQ_1600, DENSITY_4,  0}}, 4, 110, 157, 130, 10,  6, 0x0, 0x23, 0x12, 3},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_1, DPC_2, FREQ_1600, DENSITY_4,  0}}, 3, 125, 149,  65,  5,  3, 0x0, 0x1F, 0x11, 4},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_2, DPC_2, FREQ_1600, DENSITY_4,  0}}, 3, 125, 149,  65,  5,  3, 0x0, 0x1F, 0x11, 4},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_1, DPC_1, FREQ_1600, DENSITY_2,  0}}, 3,  81, 111, 128,  9,  5, 0x0, 0x2D, 0x11, 5},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_1, DPC_2, FREQ_1600, DENSITY_2,  0}}, 3, 131, 157, 128,  9,  5, 0x0, 0x21, 0x10, 5},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_2, DPC_2, FREQ_1600, DENSITY_2,  0}}, 3, 131, 157, 128,  9,  5, 0x0, 0x21, 0x10, 4},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_1, DPC_1, FREQ_1600, DENSITY_2,  0}}, 4,  99, 148, 130, 10,  5, 0x0, 0x1C, 0x0C, 2},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_1, DPC_2, FREQ_1600, DENSITY_2,  0}}, 4, 194, 247, 129,  9,  5, 0x0, 0x17, 0x0C, 2},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_2, DPC_2, FREQ_1600, DENSITY_2,  0}}, 4, 194, 247, 129,  9,  5, 0x0, 0x17, 0x0C, 2},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_1, DPC_1, FREQ_1600, DENSITY_4,  0}}, 3,  92, 120, 130, 10,  6, 0x0, 0x30, 0x12, 6},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_1, DPC_2, FREQ_1600, DENSITY_4,  0}}, 3, 142, 166, 130, 10,  6, 0x0, 0x24, 0x11, 5},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_2, DPC_2, FREQ_1600, DENSITY_4,  0}}, 3, 142, 166, 130, 10,  6, 0x0, 0x24, 0x11, 5},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_1, DPC_1, FREQ_1600, DENSITY_4,  0}}, 3, 103, 128,  65,  5,  3, 0x0, 0x19, 0x0D, 2},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_1, DPC_2, FREQ_1600, DENSITY_4,  0}}, 4, 111, 158, 132, 12,  6, 0x0, 0x16, 0x0D, 3},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_2, DPC_2, FREQ_1600, DENSITY_4,  0}}, 4, 111, 158, 132, 12,  6, 0x0, 0x16, 0x0D, 2},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_1, DPC_1, FREQ_1867, DENSITY_2,  0}}, 3,  81, 110, 128,  8,  5, 0x0, 0x37, 0x1A, 5},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_1, DPC_2, FREQ_1867, DENSITY_2,  0}}, 3, 154, 178, 127,  8,  5, 0x0, 0x2C, 0x17, 6},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_2, DPC_2, FREQ_1867, DENSITY_2,  0}}, 3, 154, 178, 127,  8,  5, 0x0, 0x2C, 0x17, 6},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_1, DPC_1, FREQ_1867, DENSITY_2,  0}}, 4,  98, 147, 128,  9,  5, 0x0, 0x20, 0x10, 2},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_1, DPC_2, FREQ_1867, DENSITY_2,  0}}, 3, 119, 144,  64,  4,  3, 0x0, 0x1D, 0x0F, 3},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_2, DPC_2, FREQ_1867, DENSITY_2,  0}}, 3, 119, 144,  64,  4,  3, 0x0, 0x1D, 0x0F, 3},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_1, DPC_1, FREQ_1867, DENSITY_4,  0}}, 3,  91, 119, 130, 10,  6, 0x0, 0x3B, 0x1C, 6},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_1, DPC_2, FREQ_1867, DENSITY_4,  0}}, 3, 164, 187, 129,  9,  6, 0x0, 0x2F, 0x1B, 7},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_2, DIMM_POSITION_2, DPC_2, FREQ_1867, DENSITY_4,  0}}, 3, 164, 187, 129,  9,  6, 0x0, 0x2F, 0x1B, 7},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_1, DPC_1, FREQ_1867, DENSITY_4,  0}}, 4, 110, 157, 130, 10,  6, 0x0, 0x23, 0x12, 3},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_1, DPC_2, FREQ_1867, DENSITY_4,  0}}, 3, 125, 149,  65,  5,  3, 0x0, 0x1F, 0x11, 4},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_2, DIMM_POSITION_2, DPC_2, FREQ_1867, DENSITY_4,  0}}, 3, 125, 149,  65,  5,  3, 0x0, 0x1F, 0x11, 4},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_1, DPC_1, FREQ_1867, DENSITY_2,  0}}, 3,  81, 111, 128,  9,  5, 0x0, 0x2D, 0x11, 5},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_1, DPC_2, FREQ_1867, DENSITY_2,  0}}, 3, 131, 157, 128,  9,  5, 0x0, 0x21, 0x10, 5},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_2, DPC_2, FREQ_1867, DENSITY_2,  0}}, 3, 131, 157, 128,  9,  5, 0x0, 0x21, 0x10, 4},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_1, DPC_1, FREQ_1867, DENSITY_2,  0}}, 4,  99, 148, 130, 10,  5, 0x0, 0x1C, 0x0C, 2},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_1, DPC_2, FREQ_1867, DENSITY_2,  0}}, 4, 194, 247, 129,  9,  5, 0x0, 0x17, 0x0C, 2},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_2, DPC_2, FREQ_1867, DENSITY_2,  0}}, 4, 194, 247, 129,  9,  5, 0x0, 0x17, 0x0C, 2},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_1, DPC_1, FREQ_1867, DENSITY_4,  0}}, 3,  92, 120, 130, 10,  6, 0x0, 0x30, 0x12, 6},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_1, DPC_2, FREQ_1867, DENSITY_4,  0}}, 3, 142, 166, 130, 10,  6, 0x0, 0x24, 0x11, 5},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_4 ,  RANKS_1, DIMM_POSITION_2, DPC_2, FREQ_1867, DENSITY_4,  0}}, 3, 142, 166, 130, 10,  6, 0x0, 0x24, 0x11, 5},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_1, DPC_1, FREQ_1867, DENSITY_4,  0}}, 3, 103, 128,  65,  5,  3, 0x0, 0x19, 0x0D, 2},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_1, DPC_2, FREQ_1867, DENSITY_4,  0}}, 4, 111, 158, 132, 12,  6, 0x0, 0x16, 0x0D, 3},
    { { {  VDD_150, ECC_T, TYPE_UDIMM,  WIDTH_8 ,  RANKS_1, DIMM_POSITION_2, DPC_2, FREQ_1867, DENSITY_4,  0}}, 4, 111, 158, 132, 12,  6, 0x0, 0x16, 0x0D, 2}
};

GLOBAL_REMOVE_IF_UNREFERENCED const DdrUpPwEntry UpWcPowerLookUpTable[] = {
    { { { VDD_120, ECC_T, TYPE_UDIMM,   0,  0,  0, 0, 0, 0, 0}},3, 217, 241,  62, 6,  4, 0x0, 0x1B, 0x09, 6},
    { { { VDD_135, ECC_T, TYPE_UDIMM,   0,  0,  0, 0, 0, 0, 0}},4,  99, 147, 129, 10, 6, 0x0, 0x18, 0x0C, 6},
    { { { VDD_150, ECC_T, TYPE_UDIMM,   0,  0,  0, 0, 0, 0, 0}},4,  99, 147, 129, 10, 6, 0x0, 0x18, 0x0C, 6},
    { { { 0, 0, 0,  0,  0,  0, 0, 0, 0, 0}}                     ,3, 182, 203,  64, 5,  3, 0x0, 0x1B, 0x09, 7}
};


/**
  This functions applies power weight values  and TSOD values according to DIMM configuration
  DdrPtmCtl.Bits.CLTM_ENABLE will be disable if not UDIMM type, or if TSOD is not present in any DIMM.
  If CLTM is enable then power weights, power Budgets, Thresholds will be configure according to DIMM inputs
  ThermalEnables->TsodManualEnable = 0 will Configure TSOD Registers according to DIMMs Input
  If Freq different than FREQ_1600 or FREQ_1333 ,it will be taken as FREQ_1600
  If all dimms equal 2GB , density index = DENSITY_2,  DENSITY_4 if different.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcSuccess or reason for failure.
**/
MrcStatus
MrcUpPowerWeightAndTsod (
  IN     MrcParameters *const MrcData
  )
{
  const MrcInput               *Inputs;
  const MrcControllerIn        *ControllerIn;
  const MrcDimmIn              *DimmIn;
  MrcDebug                     *Debug;
  const MRC_FUNCTION           *MrcCall;
  MrcOutput                    *Outputs;
  MrcControllerOut             *ControllerOut;
  MrcDimmOut                   *DimmOut;
  const ThermalMngmtEn         *ThermalEnables;
  UINT8                        Controller;
  UINT8                        Channel;
  UINT8                        Dimm;
  const DdrUpPwEntry           *Ddr3Pwt[2];
  UINT16                       PwtSize[2];
  PowerUpWeightInputs          DimmPwt;
  UINT8                        i;
  UINT16                       j;
  BOOLEAN                      DimmEntryFound;
  BOOLEAN                      EnterWc;
  UINT8                        MinScaleFactor;
  UINT8                        ScaleFactor[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL];
  UINT8                        ChPwrFloor[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL];
  UINT32                       Offset;
  BOOLEAN                      Refresh2xThermalEnabled;
  MCHBAR_CH0_CR_PM_DIMM_RD_ENERGY_STRUCT         PmDimmRdEnergy[MAX_CHANNEL];
  MCHBAR_CH0_CR_PM_DIMM_WR_ENERGY_STRUCT         PmDimmWrEnergy[MAX_CHANNEL];
  MCHBAR_CH0_CR_PM_DIMM_ACT_ENERGY_STRUCT        PmDimmActEnergy[MAX_CHANNEL];
  MCHBAR_CH0_CR_PM_DIMM_PD_ENERGY_STRUCT         PmDimmPdEnergy[MAX_CHANNEL];
  MCHBAR_CH0_CR_PM_DIMM_IDLE_ENERGY_STRUCT       PmDimmIdleEnergy[MAX_CHANNEL];
  PCU_CR_DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_STRUCT DdrRaplChannelPowerFloor;
  PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_STRUCT       PmDimmWarmThreshold[MAX_CHANNEL];
  PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_STRUCT        PmDimmHotThreshold[MAX_CHANNEL];
  PCU_CR_DDR_WARM_BUDGET_CH0_PCU_STRUCT          PmDimmWarmBudget[MAX_CHANNEL];
  PCU_CR_DDR_HOT_BUDGET_CH0_PCU_STRUCT           PmDimmHotBudget[MAX_CHANNEL];
  PCU_CR_DDR_PTM_CTL_PCU_STRUCT                  DdrPtmCtl;
  Inputs                        = &MrcData->Inputs;
  MrcCall                       = Inputs->Call.Func;
  Outputs                       = &MrcData->Outputs;
  Debug                         = &Outputs->Debug;
  ThermalEnables                = &Inputs->ThermalEnables;
  MinScaleFactor                = (UINT8) ~0;
  Ddr3Pwt[0]                    = UpPowerLookUpTable;
  Ddr3Pwt[1]                    = UpWcPowerLookUpTable;
  DdrRaplChannelPowerFloor.Data = 0;
  DdrPtmCtl.Data                = MrcReadCR (MrcData, PCU_CR_DDR_PTM_CTL_PCU_REG);
  PwtSize[0] = sizeof (UpPowerLookUpTable) / sizeof (DdrUpPwEntry);
  PwtSize[1] = sizeof (UpWcPowerLookUpTable) / sizeof (DdrUpPwEntry);
  MrcCall->MrcSetMem ((UINT8 *) PmDimmRdEnergy, sizeof (PmDimmRdEnergy), 0);
  MrcCall->MrcSetMem ((UINT8 *) PmDimmWrEnergy, sizeof (PmDimmWrEnergy), 0);
  MrcCall->MrcSetMem ((UINT8 *) PmDimmActEnergy, sizeof (PmDimmActEnergy), 0);
  MrcCall->MrcSetMem ((UINT8 *) PmDimmPdEnergy, sizeof (PmDimmPdEnergy), 0);
  MrcCall->MrcSetMem ((UINT8 *) PmDimmIdleEnergy, sizeof (PmDimmIdleEnergy), 0);
  MrcCall->MrcSetMem ((UINT8 *) ScaleFactor, sizeof (ScaleFactor), 0xFF);
  MrcCall->MrcSetMem ((UINT8 *) ChPwrFloor, sizeof (ChPwrFloor), 0);
  MrcCall->MrcSetMem ((UINT8 *) PmDimmWarmThreshold, sizeof (PmDimmWarmThreshold), 0xFF);
  MrcCall->MrcSetMem ((UINT8 *) PmDimmHotThreshold, sizeof (PmDimmHotThreshold), 0xFF);
  MrcCall->MrcSetMem ((UINT8 *) PmDimmWarmBudget, sizeof (PmDimmWarmBudget), 0xFF);
  MrcCall->MrcSetMem ((UINT8 *) PmDimmHotBudget, sizeof (PmDimmHotBudget), 0xFF);

  MRC_DEBUG_MSG (Debug,MSG_LEVEL_NOTE,"UP Power Weights Inputs:\n");
  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerOut = &Outputs->Controller[Controller];
    ControllerIn  = &Inputs->Controller[Controller];
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (MrcData, 0, Channel)) {
        //
        // Collect Channel level data for lookup
        //
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ControllerOut->Channel[Channel].Dimm[Dimm];
          DimmIn  = &ControllerIn->Channel[Channel].Dimm[Dimm];
          if (DimmOut->Status == DIMM_PRESENT) {
            EnterWc = FALSE;
            DimmPwt.Data = 0;
            //
            // Collect DIMM level data for lookup
            //
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%dD%d:\n", Channel, Dimm);
            MRC_DEBUG_MSG (Debug,MSG_LEVEL_NOTE,"Original Vddq:%d\n", Outputs->VddVoltage[Inputs->MemoryProfile]);
            if( (DdrPtmCtl.Bits.REFRESH_2X_MODE) && (DimmOut->ExtendedTemperRange != 0) && (DimmOut->ExtendedTemperRefresh!= 1) ){
              Refresh2xThermalEnabled           = TRUE;
            } else {
              Refresh2xThermalEnabled           = FALSE;
            }
            MRC_DEBUG_MSG (Debug,MSG_LEVEL_NOTE,"Refresh2xThermalEnabled:0\n",Refresh2xThermalEnabled);
            switch (Outputs->VddVoltage[Inputs->MemoryProfile]) {
              case VDD_1_20:
                DimmPwt.Bits.Vddq = VDD_120;
                break;

              case VDD_1_35:
                DimmPwt.Bits.Vddq = VDD_135;
                break;

            case VDD_1_50:
              DimmPwt.Bits.Vddq = VDD_150;
              break;

            default:
              DimmPwt.Bits.Vddq = VDD_OTHER;
              EnterWc = TRUE;
              //DimmPwt.Bits.Vddq = VDD_120;
              break;
            }
            DimmPwt.Bits.Ecc         = DimmOut->EccSupport;
            DimmPwt.Bits.DimmType    = DimmOut->ModuleType;
            DimmPwt.Bits.NumOfRanks  = DimmOut->RankInDimm;
            DimmPwt.Bits.Dpc = ControllerOut->Channel[Channel].DimmCount;
            DimmPwt.Bits.DimmPos     = Dimm;
            //1DPC position will be assume as DIMM_POSITION_1
            if(DimmPwt.Bits.Dpc == 1){
              DimmPwt.Bits.DimmPos = DIMM_POSITION_1;
            }
            //DDR3: width: 4bit, 8 bits  all others assume x8
            //DDR4: width: 4bit, 8 bits or 16bits  all others assume x8
            DimmPwt.Bits.DeviceWidth = DimmOut->SdramWidthIndex;
            switch (DimmOut->SdramWidthIndex) {
              case WIDTH_4:
                DimmPwt.Bits.DeviceWidth = DimmOut->SdramWidthIndex;
                break;

              case WIDTH_8:
                DimmPwt.Bits.DeviceWidth = DimmOut->SdramWidthIndex;
                break;

              case WIDTH_16 :
                if ( (DimmPwt.Bits.Vddq == VDD_150) || (DimmPwt.Bits.Vddq == VDD_135) ) {
                  DimmPwt.Bits.DeviceWidth = WIDTH_8;
                } else {
                  DimmPwt.Bits.DeviceWidth = WIDTH_16;
                }
                break;

              default:
                DimmPwt.Bits.DeviceWidth = WIDTH_8;
                break;
            }
            //DDR3: freq 1600 or 1867 all others assume 1867
            //DDR4: freq 2133 all others assume 2133
            switch (Outputs->Frequency) {
              case f1600:
                if ( (DimmPwt.Bits.Vddq == VDD_150) || (DimmPwt.Bits.Vddq == VDD_135) ) {
                  DimmPwt.Bits.Frequency = FREQ_1600;
                } else {
                  DimmPwt.Bits.Frequency = FREQ_2133;
                }
                break;

              case f1867:
                if ( (DimmPwt.Bits.Vddq == VDD_150) || (DimmPwt.Bits.Vddq == VDD_135) ) {
                  DimmPwt.Bits.Frequency = FREQ_1867;
                } else {
                  DimmPwt.Bits.Frequency = FREQ_2133;
                }
                break;

              case f2133:
                DimmPwt.Bits.Frequency = FREQ_2133;
                break;

              default:
                if ( (DimmPwt.Bits.Vddq == VDD_150) || (DimmPwt.Bits.Vddq == VDD_135) ) {
                  DimmPwt.Bits.Frequency = FREQ_1867;
                } else {
                  DimmPwt.Bits.Frequency = FREQ_2133;
                }
                break;
            }
            //DDR3: Density_2 or Density_4 , All others assume 4GB
            //DDR4: Density_2 or Density_4 , Desnsity_8,  All others assume 4GB
            switch (DimmOut->DensityIndex) {
              case DENSITY_2:
                DimmPwt.Bits.DramDensity = DimmOut->DensityIndex;
                break;

              case DENSITY_4:
                DimmPwt.Bits.DramDensity = DimmOut->DensityIndex;
                break;

              case DENSITY_8:
                if ( (DimmPwt.Bits.Vddq == VDD_150) || (DimmPwt.Bits.Vddq == VDD_135) )
                {
                  DimmPwt.Bits.DramDensity = DENSITY_4;
                } else {
                  DimmPwt.Bits.DramDensity = DimmOut->DensityIndex;
                }
                break;

              default:
                DimmPwt.Bits.DramDensity = DENSITY_4;
                break;
            }

            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "\tVoltage\tECC\tDType\tWidth\tRank\tDPos\tDpC\tFreq\tDensity\n"
              );
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
              DimmPwt.Bits.Vddq,
              DimmPwt.Bits.Ecc,
              DimmPwt.Bits.DimmType,
              DimmPwt.Bits.DeviceWidth,
              DimmPwt.Bits.NumOfRanks,
              DimmPwt.Bits.DimmPos,
              DimmPwt.Bits.Dpc,
              DimmPwt.Bits.Frequency,
              DimmPwt.Bits.DramDensity
            );
            //
            // Search lookup table for DIMM entry
            //
            DimmEntryFound = FALSE;
            for (i = 0; i < sizeof (PwtSize) / sizeof (PwtSize[0]); i++) {
              if (i == 0) {
                if (EnterWc) {
                  continue;
                }
              } else if (i == 1) {
                if (!DimmEntryFound) {
                  DimmPwt.Bits.DeviceWidth = 0;
                  DimmPwt.Bits.NumOfRanks  = 0;
                  DimmPwt.Bits.Dpc         = 0;
                  DimmPwt.Bits.Frequency   = 0;
                  DimmPwt.Bits.DramDensity = 0;
                } else {
                  continue;
                }
              }
              for (j = 0; j < PwtSize[i]; j++) {
                if ( (DimmPwt.Data == Ddr3Pwt[i][j].PwInput.Data) ||
                     (i == 1 && j == PwtSize[i] - 1) )              {
                  if (Inputs->UserPowerWeightsEn == 0){
                    PmDimmRdEnergy[Channel].Data8[Dimm]   = Ddr3Pwt[i][j].RdCr;
                    PmDimmWrEnergy[Channel].Data8[Dimm]   = Ddr3Pwt[i][j].WrCr;
                    PmDimmActEnergy[Channel].Data8[Dimm]  = Ddr3Pwt[i][j].ActCr;
                    PmDimmPdEnergy[Channel].Data8[Dimm]   = Ddr3Pwt[i][j].CkeL;
                    PmDimmIdleEnergy[Channel].Data8[Dimm] = Ddr3Pwt[i][j].CkeH;
                    ChPwrFloor[Channel][Dimm]             = Ddr3Pwt[i][j].ChPwrFloor;
                    ScaleFactor[Channel][Dimm]            = Ddr3Pwt[i][j].ScaleFactor;
                    MinScaleFactor                        = MIN (MinScaleFactor, ScaleFactor[Channel][Dimm]);
                  }
                  if (Inputs->UserBudgetEnable == 0){
                    PmDimmWarmBudget[Channel].Data8[Dimm] = Ddr3Pwt[i][j].WarmB;
                    PmDimmHotBudget[Channel].Data8[Dimm]  = Ddr3Pwt[i][j].HotB;
                  }
                  if (Inputs->UserThresholdEnable == 0){
                    if(Refresh2xThermalEnabled) {
                        PmDimmWarmThreshold[Channel].Data8[Dimm] = (UINT8)( (WarmThreshold_2X_MAX_TEMP << 1)  | WarmThreshold_2X_MAX_TEMP_DECIMAL  );
                        PmDimmHotThreshold[Channel].Data8[Dimm]  = (UINT8)( (HotThreshold_2X_MAX_TEMP << 1)  | HotThreshold_2X_MAX_TEMP_DECIMAL  );
                    } else {
                        PmDimmWarmThreshold[Channel].Data8[Dimm]  = (UINT8)( (WarmThreshold_1X_MAX_TEMP << 1)  | WarmThreshold_1X_MAX_TEMP_DECIMAL  );
                        PmDimmHotThreshold[Channel].Data8[Dimm] = (UINT8)( (HotThreshold_1X_MAX_TEMP << 1)  | HotThreshold_1X_MAX_TEMP_DECIMAL  );
                      }
                  }
                  if (Inputs->TsodManualEnable == 0){
                    Outputs->ThermOffset[Channel][Dimm] = Ddr3Pwt[i][j].ThermOffset;                        ///Update TSOD Thermal Offset
                  }
                  DimmEntryFound                        = TRUE;
                  break;
                }
              }
            }
          }
        }
      }
    }
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (MrcData, 0, Channel)) {
      if (Inputs->UserPowerWeightsEn == 0){
        //
        // Set RAPL Channel Power Floor to average of DIMMs rounded up to nearest integer multiple of 0.125W (which is
        // going to be a multiple of 8 for Channel Power Floor Register).
        //
        if (Outputs->Controller->Channel[Channel].DimmCount > 1) {
          if (ChPwrFloor[Channel][0] != ChPwrFloor[Channel][1]) {
            ChPwrFloor[Channel][0] = (ChPwrFloor[Channel][0] + ChPwrFloor[Channel][1] + 1) / 2;
            if (ChPwrFloor[Channel][0] < 0xF8) {
              if ((ChPwrFloor[Channel][0] % 8) != 0) {
                ChPwrFloor[Channel][0] = ChPwrFloor[Channel][0] + (8 - (ChPwrFloor[Channel][0] % 8));
              }
            } else { // No more 8-bit mulitples of 8 after 0xF8, must round down.
              ChPwrFloor[Channel][0] = 0xF8;
            }
          }
        } else {
          for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
            ChPwrFloor[Channel][0] = MAX (ChPwrFloor[Channel][0], ChPwrFloor[Channel][Dimm]);
          }
        }
        //Apply power weights
        Offset = MCHBAR_CH0_CR_PM_DIMM_RD_ENERGY_REG +
          (MCHBAR_CH1_CR_PM_DIMM_RD_ENERGY_REG - MCHBAR_CH0_CR_PM_DIMM_RD_ENERGY_REG) * Channel;
        MrcWriteCR (MrcData, Offset, PmDimmRdEnergy[Channel].Data);
        Offset = MCHBAR_CH0_CR_PM_DIMM_WR_ENERGY_REG +
          (MCHBAR_CH1_CR_PM_DIMM_WR_ENERGY_REG - MCHBAR_CH0_CR_PM_DIMM_WR_ENERGY_REG) * Channel;
        MrcWriteCR (MrcData, Offset, PmDimmWrEnergy[Channel].Data);
        Offset = MCHBAR_CH0_CR_PM_DIMM_ACT_ENERGY_REG +
          (MCHBAR_CH1_CR_PM_DIMM_ACT_ENERGY_REG - MCHBAR_CH0_CR_PM_DIMM_ACT_ENERGY_REG) * Channel;
        MrcWriteCR (MrcData, Offset, PmDimmActEnergy[Channel].Data);
        Offset = MCHBAR_CH0_CR_PM_DIMM_PD_ENERGY_REG +
          (MCHBAR_CH1_CR_PM_DIMM_PD_ENERGY_REG - MCHBAR_CH0_CR_PM_DIMM_PD_ENERGY_REG) * Channel;
        MrcWriteCR (MrcData, Offset, PmDimmPdEnergy[Channel].Data);
        Offset = MCHBAR_CH0_CR_PM_DIMM_IDLE_ENERGY_REG +
          (MCHBAR_CH1_CR_PM_DIMM_IDLE_ENERGY_REG - MCHBAR_CH0_CR_PM_DIMM_IDLE_ENERGY_REG) * Channel;
        MrcWriteCR (MrcData, Offset, PmDimmIdleEnergy[Channel].Data);
      }
      if ( (Inputs->UserBudgetEnable == 0) && (DdrPtmCtl.Bits.CLTM_ENABLE) ){
        //Apply Power Budgets
        Offset = PCU_CR_DDR_WARM_BUDGET_CH0_PCU_REG +
          (PCU_CR_DDR_WARM_BUDGET_CH1_PCU_REG - PCU_CR_DDR_WARM_BUDGET_CH0_PCU_REG) * Channel;
        MrcWriteCR (MrcData, Offset, PmDimmWarmBudget[Channel].Data);
        Offset = PCU_CR_DDR_HOT_BUDGET_CH0_PCU_REG +
          (PCU_CR_DDR_HOT_BUDGET_CH1_PCU_REG - PCU_CR_DDR_HOT_BUDGET_CH0_PCU_REG) * Channel;
        MrcWriteCR (MrcData, Offset, PmDimmHotBudget[Channel].Data);
      }
      if (Inputs->UserThresholdEnable == 0){
        //Apply Thresholds
        Offset = PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_REG +
          (PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_REG - PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_REG) * Channel;
        MrcWriteCR (MrcData, Offset, PmDimmWarmThreshold[Channel].Data);
        Offset = PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_REG +
          (PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_REG - PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_REG) * Channel;
        MrcWriteCR (MrcData, Offset, PmDimmHotThreshold[Channel].Data);
      }
    }
  }

  if (Inputs->UserPowerWeightsEn == 0){
    //RAPL update values will not depend of CLTM
    DdrRaplChannelPowerFloor.Bits.CH0 = ChPwrFloor[0][0];
    DdrRaplChannelPowerFloor.Bits.CH1 = ChPwrFloor[1][0];
    MrcWriteCR (MrcData, PCU_CR_DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_REG, DdrRaplChannelPowerFloor.Data);
    MrcWriteCR (MrcData, PCU_CR_DDR_ENERGY_SCALEFACTOR_PCU_REG, (UINT32) MinScaleFactor);
  }
  if ((Inputs->TsodManualEnable == 0) && (DdrPtmCtl.Bits.CLTM_ENABLE) ) {
    //Configure TSOD registers
    CltmTsodConfiguration(MrcData);
  }
#ifdef MRC_DEBUG_PRINT
    MRC_DEBUG_MSG (Debug,MSG_LEVEL_NOTE,"Applied UP Overwrites Power Weights:\n");
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
    "\tSclFctr\tRdCr\tWrCr\tActCr\tCkeL\tCkeH\tChPwrFl\tWarmB\tHotB\tWarmTh\tHotTh\tTermOff\n"
    );

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (MrcData, 0, Channel)) {
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        DimmOut = &Outputs->Controller->Channel[Channel].Dimm[Dimm];
        if (DimmOut->Status == DIMM_PRESENT) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%dD%d:\t", Channel, Dimm);
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
          "%d\t%d\t%d\t%d\t%d\t%d\t%2Xh\t%2Xh\t%2Xh\t%2Xh\t%2Xh\t%d\n",
            MinScaleFactor,
            PmDimmRdEnergy[Channel].Data8[Dimm],
            PmDimmWrEnergy[Channel].Data8[Dimm],
            PmDimmActEnergy[Channel].Data8[Dimm],
            PmDimmPdEnergy[Channel].Data8[Dimm],
            PmDimmIdleEnergy[Channel].Data8[Dimm],
            ChPwrFloor[Channel][Dimm],
            PmDimmWarmBudget[Channel].Data8[Dimm],
            PmDimmHotBudget[Channel].Data8[Dimm],
            PmDimmWarmThreshold[Channel].Data8[Dimm],
            PmDimmHotThreshold[Channel].Data8[Dimm],
            Outputs->ThermOffset[Channel][Dimm]
          );
        }
      }
    }
  }
#endif //MRC_DEBUG_PRINT
  return mrcSuccess;
}

/**
  This functions disable CLTM configuration register and it is used if Outputs->CLTM_SPD_Conf = PROCESS_FAILED.

  @param[in] MrcData - include all the MRC data.

  @retval None
**/
void
MrcCltmDisable (
  IN     MrcParameters *const MrcData
  )
{
  MrcDebug                      *Debug;
  PCU_CR_DDR_PTM_CTL_PCU_STRUCT DdrPtmCtl;
  const MrcInput                *Inputs;
  MrcOutput                     *Outputs;
  Inputs                            = &MrcData->Inputs;
  Outputs                           = &MrcData->Outputs;
  Debug                             = &Outputs->Debug;
  DdrPtmCtl.Data                    = MrcReadCR (MrcData, PCU_CR_DDR_PTM_CTL_PCU_REG);
  DdrPtmCtl.Bits.OLTM_ENABLE        = Inputs->EnableOltm;//Disable , 0,  Not available for UP Platforms
  DdrPtmCtl.Bits.CLTM_ENABLE        = CLTM_DISABLE;//0, Disable.
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CLTM is Disabled - Exiting.\n");
  MrcWriteCR (MrcData, PCU_CR_DDR_PTM_CTL_PCU_REG, DdrPtmCtl.Data);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_PTM_CTL %Xh: %Xh \n", PCU_CR_DDR_PTM_CTL_PCU_REG, MrcReadCR (MrcData, PCU_CR_DDR_PTM_CTL_PCU_REG) );
}

/**
CLTM TSOD Configuration

  @param[in] MrcData - Include all MRC global data.

**/
void
CltmTsodConfiguration (
  IN     MrcParameters *const MrcData

  )
{
  const MrcInput                *Inputs;
  const MRC_FUNCTION            *MrcCall;
  const MrcControllerIn         *ControllerIn;
  const MrcDimmIn               *DimmIn;
  MrcDebug                      *Debug;
  MrcOutput                     *Outputs;
  MrcControllerOut              *ControllerOut;
  MrcDimmOut                    *DimmOut;
  UINT8                         Controller;
  UINT8                         Channel;
  UINT8                         Dimm;
  UINT16                        MtsData;
  UINT16                        Thigh;
  UINT16                        Tcrit;
  UINT16                        Temp;
  TSOD_THIGH_STRUCT             PmTsodThigh[MAX_CHANNEL];
  TSOD_TCRIT_STRUCT             PmTsodTcrit[MAX_CHANNEL];
  PCU_CR_DDR_PTM_CTL_PCU_STRUCT DdrPtmCtl;
  TSOD_CONF_REGISTER_STRUCT     TsodConfReg;
  UINT8                         Address;
  UINT32                        Status;
  Inputs      = &MrcData->Inputs;
  MrcCall     = Inputs->Call.Func;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  DdrPtmCtl.Data                = MrcReadCR (MrcData, PCU_CR_DDR_PTM_CTL_PCU_REG);
  MtsData                       = 0;
  Thigh                         = 0;
  Tcrit                         = 0;
  Temp                          = 0;
  TsodConfReg.Data              = 0;
  if(DdrPtmCtl.Bits.CLTM_ENABLE) {
    MrcCall->MrcSetMemDword ((UINT32 *) PmTsodThigh, sizeof (PmTsodThigh)/sizeof(PmTsodThigh[0]), 0xFFFFFFFF);
    MrcCall->MrcSetMemDword ((UINT32 *) PmTsodTcrit, sizeof (PmTsodTcrit)/sizeof(PmTsodTcrit[0]), 0xFFFFFFFF);
    //Configuration Register of TSOD
    TsodConfReg.Bits.EventMode              = Inputs->TsodEventMode;//Default 1, Interrupt
    TsodConfReg.Bits.EventPolarity          = Inputs->TsodEventPolarity;//Default 0, Low
    TsodConfReg.Bits.CriticalEventOnly      = Inputs->TsodCriticalEventOnly;//Default 1, Enable
    TsodConfReg.Bits.EventOutputControl     = Inputs->TsodEventOutputControl; //Default 1, Enable
    TsodConfReg.Bits.AlarmWindowLock        = Inputs->TsodAlarmwindowLockBit; //Default 0, Unlock
    TsodConfReg.Bits.CriticalLock           = Inputs->TsodCriticaltripLockBit; //Default 0, Unlock
    TsodConfReg.Bits.ShutdownMode           = Inputs->TsodShutdownMode; // Default 0, TSOD Enable
    TsodConfReg.Bits.HystEnable             = HYST_DISABLE;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      ControllerIn  = &Inputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (MrcChannelExist (MrcData, 0, Channel)) {
          // Collect Channel level data for lookup
          for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
            DimmOut = &ControllerOut->Channel[Channel].Dimm[Dimm];
            DimmIn  = &ControllerIn->Channel[Channel].Dimm[Dimm];
            if (DimmOut->Status == DIMM_PRESENT) {
              if (Inputs->TsodManualEnable == 0) {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TSOD Thig Tcrit values according to DIMM configuration.\n");
                PmTsodTcrit[Channel].Data16[Dimm] = (( (CRITICAL_TEMP) - Outputs->ThermOffset[Channel][Dimm]) << 4);
                if( (DdrPtmCtl.Bits.REFRESH_2X_MODE) && (DimmOut->ExtendedTemperRange != 0) && (DimmOut->ExtendedTemperRefresh!= 1) ) {
                  PmTsodThigh[Channel].Data16[Dimm] = (( (THOT_2X_MAX_TEMP) - Outputs->ThermOffset[Channel][Dimm]) << 4);
                } else {
                  PmTsodThigh[Channel].Data16[Dimm] = (( (THOT_1X_MAX_TEMP) - Outputs->ThermOffset[Channel][Dimm]) << 4);
                }
              } else {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TSOD Thig Tcrit values according to Manual Selected Inputs.\n");
                PmTsodTcrit[Channel].Data16[Dimm] = ((Inputs->TsodTcritMax) << 4);
                PmTsodThigh[Channel].Data16[Dimm] = ((Inputs->TsodThigMax) << 4);
              }
              Address = THERMAL_MODULE_MASK | (DimmIn->SpdAddress & 0x0F);
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CLTM Configuration for Channel %d Dimm %d\n", Channel, Dimm);
              Thigh = PmTsodThigh[Channel].Data16[Dimm];
              Tcrit = PmTsodTcrit[Channel].Data16[Dimm];
              // SPD Thermal sensor registers Configurations Begin
              //((SpdDeviceAddress & 0x0F) | THERMAL_MODULE_MASK )
              //  MFG ID
              MtsData = MrcCall->MrcSmbusRead16 (((UINT32) MTS_MFGID << 8) | Address, &Status);
              if ( Status == mrcFail) {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Error - Channel %d Dimm %d Temp Sensor NACK\n", Channel, Dimm);
              } else {
                Temp = (((MtsData & 0xFF00) >> 8) | ((MtsData & 0x00FF) << 8));
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d Dimm %d Temp Sensor Mfg Id = 0x%04X\n", Channel, Dimm, Temp);
              }
              // SPD thermal sensor DEV ID
              MtsData = MrcCall->MrcSmbusRead16 (((UINT32) MTS_DID << 8) | Address, &Status);
              if ( Status == mrcFail) {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Error - Channel %d Dimm %d Temp Sensor NACK\n", Channel, Dimm);
              } else {
                Temp = (((MtsData & 0xFF00) >> 8) | ((MtsData & 0x00FF) << 8));
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d Dimm %d Temp Sensor Dev/Rev Id = 0x%04X\n", Channel, Dimm, Temp);
              }
              // Configuration Register // Disabling Configuration Register
              MtsData = 0;
              Temp = (((MtsData & 0xFF00) >> 8) | ((MtsData & 0x00FF) << 8));
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Thermal Sensor Configuration value to be programmed into TS2002 is 0x%X\n", Temp);
              MrcCall->MrcSmbusWrite16 (((UINT32) MTS_CFG << 8) | Address, Temp, &Status);
              MtsData = MrcCall->MrcSmbusRead16 (((UINT32) MTS_CFG << 8) | Address, &Status);
              Temp = (((MtsData & 0xFF00) >> 8) | ((MtsData & 0x00FF) << 8));
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Thermal Sensor Configuration value read from TS2002 is 0x%X\n", MtsData);
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Thermal Sensor Configuration value is 0x%X\n", Temp);
              // THigh 0x02
              Temp = (((Thigh & 0xFF00) >> 8) | ((Thigh & 0x00FF) << 8));
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "High Temp value is 0x%X = %d degreeC\n", Thigh, (Thigh >> 4));
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "High Temp value to be programmed into TS2002 is 0x%X\n", Temp);
              MrcCall->MrcSmbusWrite16 (((UINT32) MTS_THIGH << 8) | Address, Temp, &Status);
              Thigh = MrcCall->MrcSmbusRead16 (((UINT32) MTS_THIGH << 8) | Address, &Status );
              Temp = (((Thigh & 0xFF00) >> 8) | ((Thigh & 0x00FF) << 8));
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "High Temp value read from TS2002 is 0x%X\n", Thigh);
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "High Temp value is 0x%X = %d degreeC\n", Temp, (Temp >> 4));
              // TCrit 0x04
              Temp = (((Tcrit & 0xFF00) >> 8) | ((Tcrit & 0x00FF) << 8));
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Critical Temp value is 0x%X = %d degreeC\n", Tcrit, (Tcrit >> 4));
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Critical Temp value to be programmed into TS2002 is 0x%X\n", Temp);
              MrcCall->MrcSmbusWrite16 (((UINT32) MTS_TCRIT << 8) | Address, Temp, &Status);
              Tcrit = MrcCall->MrcSmbusRead16 (((UINT32) MTS_TCRIT << 8) | Address, &Status);
              Temp = (((Tcrit & 0xFF00) >> 8) | ((Tcrit & 0x00FF) << 8));
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Critical Temp value read from TS2002 is 0x%X\n", Tcrit);
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Critical Temp value is 0x%X = %d degreeC\n", Temp, (Temp >> 4));
              // Configuration Register
              MtsData = TsodConfReg.Data;
              Temp = (((MtsData & 0xFF00) >> 8) | ((MtsData & 0x00FF) << 8));
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Thermal Sensor Configuration value is 0x%X\n", MtsData);
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Thermal Sensor Configuration value to be programmed into TS2002 is 0x%X\n", Temp);
              MrcCall->MrcSmbusWrite16 (((UINT32) MTS_CFG << 8) | Address, Temp, &Status);
#ifdef MRC_DEBUG_PRINT
              MtsData = MrcCall->MrcSmbusRead16 (((UINT32) MTS_CFG << 8) | Address, &Status);
              Temp = (((MtsData & 0xFF00) >> 8) | ((MtsData & 0x00FF) << 8));
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Thermal Sensor Configuration value read from TS2002 is 0x%X\n", MtsData);
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Thermal Sensor Configuration value is 0x%X\n", Temp);
              //Read current temperature of the TSOD 0x05
              MtsData = MrcCall->MrcSmbusRead16 (((UINT32) TEMPERATURE_REGISTER << 8) | Address, &Status);
              Temp = (((MtsData & 0xFF00) >> 8) | ((MtsData & 0x001F) << 8));//This will get rid of the firt three bits of the register and hold only the themperatur value
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SMBUS base Address is 0x%X\n", Inputs->SmbusBaseAddress);
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SPD address offset 0x%X of Channel:%d  DIMM:%d \n", (DimmIn->SpdAddress & 0x0F), Channel, Dimm);
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Module thermal SPD address 0x%X of Channel:%d  DIMM:%d\n", Address , Channel, Dimm);
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Offset to temperature register 0x%X\n", TEMPERATURE_REGISTER );
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Temperature register value read from TS2002 is 0x%X\n", MtsData);
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Current TSOD Temperatur value is 0x%X = %d degreeC\n", Temp, (Temp >> 4));
#endif //MRC_DEBUG_PRINT
            }
          }
        }
      }
    }
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CLTM is Disabled No TSOD Registers to be Configure Exiting.\n");
  }
}

/**
  CLTM TSOD Initialization

  @param[in] MrcData - include all the MRC data.

  @retval None
**/
void
MrcCltmTsodInitChecking (
  IN     MrcParameters *const MrcData
  )
{
  const MRC_FUNCTION                              *MrcCall;
  const MrcInput                                  *Inputs;
  MrcOutput                                       *Outputs;
  MrcDebug                                        *Debug;
  UINT8                                           Controller;
  UINT8                                           Channel;
  UINT8                                           Dimm;
  Outputs                                                 = &MrcData->Outputs;
  Inputs                                                  = &MrcData->Inputs;
  Debug                                                   = &Outputs->Debug;
  MrcCall                                                 = Inputs->Call.Func;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "UP CLTM TSOD Checking Start.\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "EnableCltm %d EccSupport %d - \n", Inputs->EnableCltm, Outputs->EccSupport);
  if (Inputs->EnableCltm  && (Outputs->EccSupport == TRUE)) {
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      // Check in every DIMM for CLTM capabilities
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (Outputs->Controller[Controller].Channel[Channel].Status != CHANNEL_PRESENT){
          continue;
        }
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          if (Outputs->Controller[Controller].Channel[Channel].Dimm[Dimm].Status != DIMM_PRESENT){
            continue;
          }
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d Dimm %d - Check for CLTM Capabilities\n", Channel, Dimm);
          // CHECK CLTM RESTRICTIONS
          // Check ECC support. Do not enable CLTM if not supported.
          if (Outputs->Controller[Controller].Channel[Channel].Dimm[Dimm].EccSupport == FALSE) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CLTM is Disable - Channel %d Dimm %d is non ECC - Exiting.\n", Channel, Dimm);
            MrcCltmDisable(MrcData);
            return;
          }
          // Check thermal sensor presence. Do not enable CLTM if no sensor.
          if  (Outputs->Controller[Controller].Channel[Channel].Dimm[Dimm].DdrType== MRC_DDR_TYPE_DDR4){
            if (Inputs->Controller[Controller].Channel[Channel].Dimm[Dimm].Spd.Data.Ddr4.Base.ModuleThermalSensor.Bits.ThermalSensorPresence == 0) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CLTM is Disable DDR4 - Channel %d Dimm %d do not have Thermal Sensor Incorporated - Exiting.\n", Channel, Dimm);
              MrcCltmDisable(MrcData);
              return;
            }
          } else {
            if (Outputs->Controller[Controller].Channel[Channel].Dimm[Dimm].OnDieThermalSensor == 0) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CLTM is Disable - Channel %d Dimm %d do not have Thermal Sensor Incorporated - Exiting.\n", Channel, Dimm);
              MrcCltmDisable(MrcData);
              return;
            }
          }
          //All dimms will be taken as Raw Card E
          //Check if UDIMM. Do not enable CLTM if not UDIM
          if (Outputs->Controller[Controller].Channel[Channel].Dimm[Dimm].ModuleType != TYPE_UDIMM) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d Dimm %d Module Type is not UDIMM - CLTM disable.\n", Channel, Dimm);
            MrcCltmDisable(MrcData);
            return;
          }
        } //for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++)
      } //for (Channel = 0; Channel < MAX_CHANNEL; Channel++)
    }// for Controller
  } else {
    MrcCltmDisable(MrcData);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "UP CLTM TSOD Checking End.\n");
    return;
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "UP CLTM TSOD Checking End.\n");
}
#endif
