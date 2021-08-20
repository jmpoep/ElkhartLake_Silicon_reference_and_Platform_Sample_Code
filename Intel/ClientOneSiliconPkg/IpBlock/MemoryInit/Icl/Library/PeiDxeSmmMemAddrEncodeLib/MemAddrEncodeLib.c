/** @file
  File to support address decoding and encoding

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

#ifdef MRC_MINIBIOS_BUILD
#define DEBUG(Expression)
#include "MrcOemPlatform.h"
#include "MemoryUtils.h"
#include <MrcRegisters/Icelake/Pci000Icl.h>
#include <MrcRegisters/Icelake/MrcMcRegisterIcl.h>
#include <MrcRegisters/Icelake/MrcMcRegisterStructIcl.h>
#else // MRC_MINIBIOS_BUILD
#include <Uefi.h>
#include <SaRegs.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/IoLib.h>
#include <Library/BaseLib.h>
#endif // MRC_MINIBIOS_BUILD
#include <MrcTypes.h>
#include <Library/MemoryAddressEncodeLib.h>
#define MAXFLDSIZE                          51

GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 ConfigArrayConst[MAXFLDSIZE][37] = {
  { 20,  0,  0, 14,  6,  0, 16, 15, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 21, 17,  0, 14,  6,  0, 16, 15, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 22,  0, 15, 14,  6,  0, 17, 16, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 23, 17, 15, 14,  6,  0, 18, 16, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 24, 17, 15, 14,  6,  0, 18, 16, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 25, 17,  0, 14,  6,  0, 16, 15, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 26,  0,  0,  0,  6,  0, 15, 14, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 27, 16,  0,  0,  6,  0, 15, 14, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 28,  0, 14,  0,  6,  0, 16, 15, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 29, 16, 14,  0,  6,  0, 17, 15, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 30, 16, 14,  0,  6,  0, 17, 15, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 31, 16,  0,  0,  6,  0, 15, 14, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 32, 17,  0, 14,  6,  0, 16, 15, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 33, 17,  0,  0,  6,  0, 15, 14, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 16,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 34, 17, 15, 14,  6,  0, 18, 16, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 35, 17, 14,  0,  6,  0, 16, 15, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 36, 17, 15, 14,  6,  0, 18, 16, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 37, 17,  0,  0,  6,  0, 15, 14, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 16,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 38, 17, 14,  0,  6,  0, 16, 15, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 39, 17,  0, 14,  6,  0, 16, 15, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 40,  0,  0, 14,  6,  0, 16, 15, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 41,  0,  0,  0,  6,  0, 15, 14, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 70,  0,  0,  0,  0, 14, 13, 12, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15,  0,  0, 11, 10,  9,  8,  7,  6,  5,  4,  3, 2},
  { 71,  0, 14,  0,  0, 15, 13, 12, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16,  0,  0, 11, 10,  9,  8,  7,  6,  5,  4,  3, 2},
  { 72,  6,  0,  0,  0, 15, 14, 13, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16,  0,  0, 12, 11, 10,  9,  8,  7,  5,  4,  3, 2},
  { 73,  6, 15,  0,  0, 16, 14, 13, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17,  0,  0, 12, 11, 10,  9,  8,  7,  5,  4,  3, 2},
  { 80,  0,  0,  0,  0, 14, 13, 12, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15,  0,  0, 11, 10,  9,  8,  7,  6,  5,  4,  3, 2},
  { 89,  0, 14, 15,  0, 16, 13, 12, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17,  0,  0, 11, 10,  9,  8,  7,  6,  5,  4,  3, 2},
  { 90,  6, 15, 16,  0, 17, 14, 13, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18,  0,  0, 12, 11, 10,  9,  8,  7,  5,  4,  3, 2},
  { 91,  0,  0, 14,  6, 17, 16, 15,  0, 33, 32, 31, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 30,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 92, 17,  0, 14,  6, 18, 16, 15,  0, 34, 33, 32, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 31,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 93,  0, 15, 14,  6, 18, 17, 16,  0, 34, 33, 32, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 31,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 94, 17, 15, 14,  6, 19, 18, 16,  0, 35, 34, 33, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 32,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 95, 17, 15, 14,  6, 19, 18, 16,  0, 35, 34, 33, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 32,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 96, 17,  0, 14,  6, 18, 16, 15,  0, 34, 33, 32, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 31,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 97,  0,  0,  0,  6, 16, 15, 14,  0, 32, 31, 30, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 29,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 98, 16,  0,  0,  6, 17, 15, 14,  0, 33, 32, 31, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 30,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  { 99,  0, 14,  0,  6, 17, 16, 15,  0, 33, 32, 31, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 30,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  {100, 16, 14,  0,  6, 18, 17, 15,  0, 34, 33, 32, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 31,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  {101, 16, 14,  0,  6, 18, 17, 15,  0, 34, 33, 32, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 31,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  {102, 16,  0,  0,  6, 17, 15, 14,  0, 33, 32, 31, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 30,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  {103, 17,  0, 14,  6, 18, 16, 15,  0, 34, 33, 32, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 31,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  {104, 17,  0,  0,  6, 16, 15, 14,  0, 33, 32, 31, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 30,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  {105, 17, 15, 14,  6, 19, 18, 16,  0, 35, 34, 33, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 32,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  {106, 17, 14,  0,  6, 18, 16, 15,  0, 34, 33, 32, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 31,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  {107, 17, 15, 14,  6, 19, 18, 16,  0, 35, 34, 33, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 32,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  {108, 17,  0,  0,  6, 16, 15, 14,  0, 33, 32, 31, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 30,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  {109, 17, 14,  0,  6, 18, 16, 15,  0, 34, 33, 32, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 31,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  {110, 17,  0, 14,  6, 18, 16, 15,  0, 34, 33, 32, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 31,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  {111,  0,  0, 14,  6, 17, 16, 15,  0, 33, 32, 31, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 30,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3},
  {112,  0,  0,  0,  6, 16, 15, 14,  0, 32, 31, 30, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 29,  0,  0, 13, 12, 11, 10,  9,  8,  7,  5,  4, 3}
};

GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 EnhConfigArrayConst[MAXFLDSIZE][9] = {
  { 20,  0,  0, 17, 13,  0, 19, 18,  0},
  { 21, 21,  0, 18, 13,  0, 20, 19,  0},
  { 22,  0, 19, 18, 13,  0, 21, 20,  0},
  { 23, 22, 20, 19, 13,  0, 23, 21,  0},
  { 24, 22, 20, 19, 13,  0, 23, 21,  0},
  { 25, 22,  0, 19, 13,  0, 21, 20,  0},
  { 26,  0,  0,  0, 13,  0, 17, 16,  0},
  { 27, 19,  0,  0, 13,  0, 18, 17,  0},
  { 28,  0, 17,  0, 13,  0, 19, 18,  0},
  { 29, 20, 18,  0, 13,  0, 21, 19,  0},
  { 30, 20, 18,  0, 13,  0, 21, 19,  0},
  { 31, 20,  0,  0, 13,  0, 19, 18,  0},
  { 32, 19,  0, 17, 13,  0,  0, 18,  0},
  { 33, 19,  0,  0, 13,  0, 18, 17,  0},
  { 34, 21, 19, 18, 13,  0, 22, 20,  0},
  { 35, 21, 18,  0, 13,  0, 20, 19,  0},
  { 36, 21, 20, 19, 13,  0, 22,  0,  0},
  { 37, 21,  0,  0, 13,  0, 20, 19,  0},
  { 38, 21, 18,  0, 13,  0, 20, 19,  0},
  { 39, 21,  0, 18, 13,  0, 20, 19,  0},
  { 40,  0,  0, 17, 13,  0, 19, 18,  0},
  { 41,  0,  0,  0, 13,  0, 18, 17,  0},
  { 70,  0,  0,  0,  0, 17, 16, 15,  0},
  { 71,  0, 18,  0,  0, 19, 17, 16,  0},
  { 72,  0,  0,  0,  0, 18, 17, 16,  0},
  { 73,  0, 19,  0,  0, 20, 18, 17,  0},
  { 80,  0,  0,  0,  0, 17, 16, 15,  0},
  { 89,  0, 19, 20,  0, 21, 18, 17,  0},
  { 90,  0, 20, 21,  0, 22, 19, 18,  0},
  { 91,  0,  0, 17, 13,  0, 19, 18,  0},
  { 92, 21,  0, 18, 13,  0, 20, 19,  0},
  { 93,  0, 19, 18, 13,  0, 21, 20,  0},
  { 94, 22, 20, 19, 13,  0, 23, 21,  0},
  { 95, 22, 20, 19, 13,  0, 23, 21,  0},
  { 96, 22,  0, 19, 13,  0, 21, 20,  0},
  { 97,  0,  0,  0, 13,  0, 17, 16,  0},
  { 98, 19,  0,  0, 13,  0, 18, 17,  0},
  { 99,  0, 17,  0, 13,  0, 19, 18,  0},
  {100, 20, 18,  0, 13,  0, 21, 19,  0},
  {101, 20, 18,  0, 13,  0, 21, 19,  0},
  {102, 20,  0,  0, 13,  0, 19, 18,  0},
  {103, 19,  0, 17, 13,  0,  0, 18,  0},
  {104, 19,  0,  0, 13,  0, 18, 17,  0},
  {105, 21, 19, 18, 13,  0, 22, 20,  0},
  {106, 21, 18,  0, 13,  0, 20, 19,  0},
  {107, 21, 20, 19, 13,  0, 22,  0,  0},
  {108, 21,  0,  0, 13,  0, 20, 19,  0},
  {109, 21, 18,  0, 13,  0, 20, 19,  0},
  {110, 21,  0, 18, 13,  0, 20, 19,  0},
  {111,  0,  0, 17, 13,  0, 19, 18,  0},
  {112,  0,  0,  0, 13,  0, 18, 17,  0}
};

typedef UINT32       (*MRC_IO_READ_32)              (UINT32 IoAddress);
typedef void         (*MRC_IO_WRITE_32)             (UINT32 IoAddress, UINT32 Value);
typedef UINT32       (*MRC_MMIO_READ_32)            (UINT32 Address);
typedef UINT64       (*MRC_MMIO_READ_64)            (UINT32 Address);
typedef void *       (*MRC_MEMORY_COPY)             (UINT8 *Destination, UINT8 *Source, UINT32 NumBytes);
typedef void *       (*MRC_MEMORY_SET_BYTE)         (UINT8 *Destination, UINT32 NumBytes, UINT8 Value);
typedef UINT64       (*MRC_LEFT_SHIFT_64)           (UINT64 Data, UINT32 NumBits);
typedef UINT64       (*MRC_RIGHT_SHIFT_64)          (UINT64 Data, UINT32 NumBits);
typedef UINT64       (*MRC_MULT_U64_U32)            (UINT64 Multiplicand, UINT32 Multiplier);
typedef UINT64       (*MRC_DIV_U64_U64)             (UINT64 Dividend, UINT64 Divisor, UINT64 *Remainder);

///
/// Function calls that are called external to the MRC.
///   This structure needs to be aligned with SA_FUNCTION_CALLS.  All functions that are
///   not apart of SA_FUNCTION_CALLS need to be at the end of the structure.
///
typedef struct {
  MRC_IO_READ_32              MrcIoRead32;
  MRC_IO_WRITE_32             MrcIoWrite32;
  MRC_MMIO_READ_32            MrcMmioRead32;
  MRC_MMIO_READ_64            MrcMmioRead64;
  MRC_MEMORY_COPY             MrcCopyMem;
  MRC_MEMORY_SET_BYTE         MrcSetMem;
  MRC_LEFT_SHIFT_64           MrcLeftShift64;
  MRC_RIGHT_SHIFT_64          MrcRightShift64;
  MRC_MULT_U64_U32            MrcMultU64x32;
  MRC_DIV_U64_U64             MrcDivU64x64;
} MRC_ADDR_FUNCTION;

#ifdef MRC_MINIBIOS_BUILD
#define R_HOSTBRIDGE_CFG_MCHBAR_0_0_0_PCI          MCHBAR_0_0_0_PCI_REG
#define R_HOSTBRIDGE_CFG_PCIEXBAR_0_0_0_PCI        PCIEXBAR_0_0_0_PCI_REG
#define R_HOSTBRIDGE_CFG_TOLUD_0_0_0_PCI           TOLUD_0_0_0_PCI_REG
#define R_HOSTBRIDGE_CFG_TOM_0_0_0_PCI             TOM_0_0_0_PCI_REG
#define R_SA_MCHBAR_REMAPBASE_OFFSET               REMAPBASE_REG
#define R_SA_MCHBAR_REMAPLIMIT_OFFSET              REMAPLIMIT_REG

#define R_SA_MCHBAR_MAD_INTER_CHANNEL_OFFSET       MAD_INTER_CHANNEL_REG
#define R_SA_MCHBAR_MAD_INTRA_CH0_OFFSET           MAD_INTRA_CH0_REG
#define R_SA_MCHBAR_MAD_INTRA_CH1_OFFSET           MAD_INTRA_CH1_REG
#define R_SA_MCHBAR_MAD_DIMM_CH0_OFFSET            MAD_DIMM_CH0_REG
#define R_SA_MCHBAR_MAD_DIMM_CH1_OFFSET            MAD_DIMM_CH1_REG
#define R_SA_MCHBAR_CHANNEL_HASH_OFFSET            CHANNEL_HASH_REG
#define R_SA_MCHBAR_CHANNEL_EHASH_OFFSET           CHANNEL_EHASH_REG
#endif


// size of the hash mask field in the channel hash register
#define MC_ADDR_CHANNEL_HASH_MASK_SIZE  14

// Bit-Masks used to remove or test register fields
//
#define MC_ADDR_TOLUD_MASK              0xFFF00000
#define MC_ADDR_REMAP_MASK              0x0000007FFFF00000ULL
#define MC_ADDR_CHAN_HASH_ENABLE_MASK   0x10000000
#define DRAM_ADDR_SIZE                      36

// Mask used to add 1's to lower bits of REMAP_LIMIT register
#define MC_ADDR_REMAP_LIMIT_LOWER_BITS_MASK 0x00000000000FFFFFULL

#define ONE_BIT_MASK                        1
#define TWO_BIT_MASK                        3
#define THREE_BIT_MASK                      7
#define FOUR_BIT_MASK                       15

#define DIMM_NUM_BITS                       1
#define RANK_NUM_BITS                       1
#define BG_NUM_BITS                         2
#define BANK_NUM_BITS                       3
#define ROW_NUM_BITS                        17
#define COL_NUM_BITS                        12
#define ENHANCED_BITS_SIZE                  DIMM_NUM_BITS + RANK_NUM_BITS + BG_NUM_BITS + BANK_NUM_BITS + 1 // "+1" for column[10:10] of 8Gbx8
#define XaB_NUM_OF_BITS                     4
// Useful number constants
#define MC_256MB_AS_CL  (1 << 22)
#define MC_512MB_AS_CL  (1 << 23)
#define MC_1GB_AS_CL    (1 << 24)
#define MC_2GB_AS_CL    (1 << 25)
#define MC_4GB_AS_CL    (1 << 26)
#define MC_8GB_AS_CL    (1 << 27)
#define MC_16GB_AS_CL   (1 << 28)
#define MC_32GB_AS_CL   (1 << 29)
#define MC_64GB_AS_CL   (1 << 30)
#define MC_128GB_AS_CL  (1 << 31)

// EBH - channel Xor bits - XaB[bank] - bits of channel address participating in Xor
GLOBAL_REMOVE_IF_UNREFERENCED const UINT32   XaB[BANK_NUM_BITS][XaB_NUM_OF_BITS] = { {18, 21,24,27},{19,22,25,28},{20,23,26,29} };
GLOBAL_REMOVE_IF_UNREFERENCED const UINT32   XbB_lp4[BANK_NUM_BITS][XaB_NUM_OF_BITS] = { {17,14,0,0},{16,13,0,0},{15,0,0,0} };
GLOBAL_REMOVE_IF_UNREFERENCED const UINT32   XbB_ddr4[2][BANK_NUM_BITS][XaB_NUM_OF_BITS] = { {{17,14,0,0},{16,0,0,0},{15,0,0,0}}, {{15,12,20,26},{14,13,23,29},{0,0,0,0}} };// differecnt Xor for x8 and x16 - HSD 1305305117

// Functions to extract fields from the registers
static
UINT16
get_ddr_type (
  UINT32 MAD_INTER_CHNL
)
{
  return (UINT16)(MAD_INTER_CHNL & 7); // MAD_INTER_CHNL[1:0]; 0=DDR4; 1=DDR3; 2=LPDDR3; 3=LPDDR4; 4=WIO2
}

static
UINT16
get_enhanced_ch_mode (
  UINT32 MAD_INTER_CHNL
)
{
  return (UINT16)((MAD_INTER_CHNL >> 3) & 1); // MAD_INTER_CHNL[3:3]; 0- Enhanced channel mode disabled ; 1- Enhanced channel mode enabled
}

static
UINT64
get_dimm_l_size_as_cl (
  const MRC_ADDR_FUNCTION *MrcCall,
  UINT32 MAD_DIMM
)
{
  return MrcCall->MrcLeftShift64 ((((UINT64)MAD_DIMM) & 0x007FULL), 23); // MAD_DIMM[ 6:0]*0.5GB
}

static
UINT64
get_dimm_s_size_as_cl (
  const MRC_ADDR_FUNCTION *MrcCall,
  UINT32 MAD_DIMM
)
{
  return MrcCall->MrcLeftShift64 ((((UINT64)MAD_DIMM) & 0x007F0000ULL), 7); // MAD_DIMM[22:16]*0.5GB
}

static
BOOLEAN
get_dimm_and_rank_intlv (
  UINT32 MAD_INTRA_CHNL
)
{
  return (BOOLEAN)((MAD_INTRA_CHNL >> 4) & 1); // MAD_INTRA_CHNL[4:4]
}

static
BOOLEAN
get_high_order_intlv_mode (
  UINT32 MAD_INTRA_CHNL
)
{
  return (BOOLEAN)((MAD_INTRA_CHNL >> 24) & 1); // MAD_INTRA_CHNL[24:24]
}

static
BOOLEAN
get_enhanced_intlv_mode (
  UINT32 MAD_INTRA_CHNL
)
{
  return (BOOLEAN)((MAD_INTRA_CHNL >> 8) & 1); // MAD_INTRA_CHNL[8:8]
}

static
UINT16
get_dimm_l_select (
  UINT32 MAD_INTRA_CHNL
)
{
  return (UINT16)(MAD_INTRA_CHNL & 1);
}

static
UINT16
get_dimm_l_number_of_ranks (
  UINT32 MAD_DIMM
)
{
  return 1 + (UINT16)((MAD_DIMM >> 9) & 3);
}

static
UINT16
get_dimm_s_number_of_ranks (
  UINT32 MAD_DIMM
)
{
  return 1 + ((MAD_DIMM >> 26) & 3);
}

// This function determine the device width.
// x8, x16, x32(returns 8, 16, 32)
static
UINT16
get_dimm_l_width (
  UINT32 MAD_DIMM
)
{
  UINT16 width;
  width = (UINT16)((MAD_DIMM >> 7) & 3); // 0-x8, 1-x16, 2-x16

  if (width < 2) {
    return (UINT16)((width + 1) << 3);
  } else {
    return (UINT16)((width + 2) << 3);
  }
}

// x8, x16, x32 (returns 8, 16 or 32)
static
UINT16
get_dimm_s_width (
  UINT32 MAD_DIMM
)
{
  UINT16  width;
  width = (UINT16)((MAD_DIMM >> 24) & 3);
  // 0-x8, 1-x16, 2-x32
  if (width < 2) {
    return (UINT16)((width + 1) << 3);
  } else {
    return (UINT16)((width + 2) << 3);
  }
}

UINT16
get_dimm_l_num_col_bits (
  const MRC_ADDR_FUNCTION *MrcCall,
  UINT16 ddr_type,
  UINT32 MAD_DIMM,
  UINT32 MAD_INTRA_CHNL,
  UINT16 enhanced_ch_mode
) //  8, 9, 10, 11 or 12
{

  if (ddr_type == 0 || ddr_type == 3) return 10; // Supported DDR4/LPDDR4 DRAM organizations all have 10 column bits


  // If we got past the above line, we are LPDDR3/DDR3 - not supported in ICL
  return 0xFFFF;
}

UINT16
get_dimm_s_num_col_bits (
  const MRC_ADDR_FUNCTION *MrcCall,
  UINT16 ddr_type,
  UINT32 MAD_DIMM,
  UINT32 MAD_INTRA_CHNL,
  UINT16 enhanced_ch_mode
) //  9, 10, 11 or 12
{
  //  UINT16 width;
  //  UINT64 dimm_rank_size_as_cl;


  if (ddr_type == 0 || ddr_type == 3) return 10; // Supported DDR4 DRAM organizations all have 10 column bits


  // If we got past the above line, we are LPDDR3/DDR3 - not supported in ICL

  return 0xFFFF;
}

static
UINT16
get_ch_hash_lsb_mask_bit (
  UINT32 CHANNEL_HASH
)
{
  return (CHANNEL_HASH >> 24) & 7;
}

static
UINT16
get_ch_hash_mask (
  UINT32 CHANNEL_HASH
)
{
  return (CHANNEL_HASH >> 6) & 0x0003FFF;
}
static
BOOLEAN  get_stacked_mode (
  UINT32 MAD_INTER_CHNL
)
{
  return (BOOLEAN)((MAD_INTER_CHNL >> 8) & 1);
}

static
BOOLEAN
get_stacked_mode_ch1 (
  UINT32 MAD_INTER_CHNL
)
{
  return (BOOLEAN)((MAD_INTER_CHNL >> 9) & 1);
}

static
UINT16
get_stacked_encoding (
  UINT32 MAD_INTER_CHNL
)
{
  return (UINT16)(MAD_INTER_CHNL >> 24) & 7;
}

static
UINT16
get_ch_l_map (
  UINT32 MAD_INTER_CHNL
)
{
  return (UINT16)(MAD_INTER_CHNL >> 4) & 1;
}
static
UINT64
get_ch_s_size_as_cl (
  const MRC_ADDR_FUNCTION *MrcCall,
  UINT32 MAD_INTER_CHNL
)
{
  return MrcCall->MrcLeftShift64 (((UINT64)MAD_INTER_CHNL) & 0x00FF000ULL, 11);
}

static
UINT16
get_dimm_l_8Gb (
  UINT32 MAD_DIMM
)
{
  return (UINT16)(MAD_DIMM >> 11) & 1;
}

static
UINT16
get_dimm_s_8Gb (
  UINT32 MAD_DIMM
)
{
  return (UINT16)(MAD_DIMM >> 28) & 1;
}

static
UINT16
get_DLS_BG0_on_bit_11 (
  UINT32 MAD_DIMM
)
{
  return (UINT16)(MAD_DIMM >> 29) & 1;
}

static
UINT16
get_ebh_mode (
  UINT16 MCMNTS_SPARE
)
{
  return (UINT16)(MCMNTS_SPARE >> 12) & 3;
}




// Functions to aid in common tasks

// make mask for a certain bits
UINT64
get_x_bit_mask (
  const MRC_ADDR_FUNCTION *MrcCall,
  INT32 num_bit
)
{
  UINT64 x_bit_mask;
  x_bit_mask = 0x00FFFFFFFFULL; // 32 bits mask
  return MrcCall->MrcRightShift64 (x_bit_mask, (INT32)(32 - num_bit));
}

// convert a cache-line address to a system address
static
UINT64
cl_to_sys (
  const MRC_ADDR_FUNCTION *MrcCall,
  UINT64 cache_line
)
{
  return MrcCall->MrcLeftShift64 (cache_line, 6);
}

// get an approxamation in giga-bytes for a system address or size (useful for print statements)
static
UINT64
sys_in_gb (
  const MRC_ADDR_FUNCTION *MrcCall,
  UINT64 sys
)
{
  return MrcCall->MrcDivU64x64 (sys, 1 << 30, NULL);
}

// get an approxamation in giga-bytes for a cache-line address or size (useful for print statements)
static
UINT64
cl_in_gb (
  const MRC_ADDR_FUNCTION *MrcCall,
  UINT64 cache_line
)
{
  return MrcCall->MrcDivU64x64 (MrcCall->MrcLeftShift64 (cache_line, 6), (1 << 30), NULL);
}

// Channel conversion functions. For logical channels: 0=L, 1=S.
static
UINT16
logical_to_physical_chan (
  UINT32 MAD_INTER_CHNL,
  UINT16 logical_chan
)
{
  return ((UINT16)(((MAD_INTER_CHNL >> 4) & 1) ^ (logical_chan)));
}

static
UINT16
physical_to_logical_chan (
  UINT32 MAD_INTER_CHNL,
  UINT16 physical_chan
)
{

  return ((((UINT16)((MAD_INTER_CHNL >> 4) & 1)) == physical_chan) ? 0 : 1); // 0=L, 1=S
}


// Function for decode of stacked channel debug feature
static
UINT64
get_stacked_memory_size (
  const MRC_ADDR_FUNCTION *MrcCall,
  UINT16 i_stacked_encoding
)
{
  return MrcCall->MrcLeftShift64 (0x01000000ULL, i_stacked_encoding); // 1 << 30 + stacked_encoding - 6 for the cachline align
}

// Function for parsing the decode shifters numbers from the decode map
// ------------------------------------------------------------------------------
// config_arr   0           1       2       3       4       5       6       7
//              config_case DIMM0   RANK0   BG1     BG0     BANK1   BANK0   ROW15
//              8           9       10      11      12      13      14      15
//              ROW14       ROW13   ROW12   ROW11   ROW10   ROW9    ROW8    ROW7
//              16          17      18      19      20      21      22      23
//              ROW6        ROW5    ROW4    ROW3    ROW2    ROW1    ROW0    CAS10
//              24          25      26      27      28      29      30      31
//              CAS9        CAS8    CAS7    CAS6    CAS5    CAS4    CAS3    CAS2
//              32          33
//              CAS1        CAS0
// ------------------------------------------------------------------------------
// The config_arr holds all the shifters for the decode function
//
void
addr_decode_map_parse (
  const MRC_ADDR_FUNCTION *MrcCall,
  UINT8* config_arr,
  UINT8 config_case,
  BOOLEAN second_round
)
{
  // gets the configuration case we need from the addr_decode_map.csv file
  UINT16 i;
  UINT8 curr_cfg;
  for (i = 0; i < MAXFLDSIZE; i++) {
    curr_cfg = ConfigArrayConst[i][0];
    if (second_round) {
      if (curr_cfg == config_case) { // if match the configuration case we are lookink for
        break;
      }
    } else {
      if ((curr_cfg >= config_case) && (curr_cfg < (config_case + 1))) { // if almost match the configuration case we are lookink for
        break;
      }
    }
  }
  //Found a configuration - copying it to the config array
  MrcCall->MrcCopyMem ((UINT8 *)config_arr, (UINT8 *)&ConfigArrayConst[i], sizeof (ConfigArrayConst[i]));

}

void
enhanced_mode_map_parse (
  const MRC_ADDR_FUNCTION *MrcCall,
  UINT8* enh_config_arr,
  UINT8 config_case,
  BOOLEAN second_round
)
{
  UINT16 i = 0;

  // gets the configuration case we need
  for (i = 0; i < MAXFLDSIZE; i++) {
    if (second_round) {
      if (EnhConfigArrayConst[i][0] == config_case) { // if match the configuration case we are looking for
        break;
      }
    } else {
      if ((EnhConfigArrayConst[i][0] >= config_case) && (EnhConfigArrayConst[i][0] < (config_case + 1))) { // if almost match the configuration case we are lookink for
        break;
      }
    }
  }
  //Found a configuration - copying it to the config array
  MrcCall->MrcCopyMem ((UINT8 *)enh_config_arr, (UINT8 *)&EnhConfigArrayConst[i], sizeof (EnhConfigArrayConst[i]));

}

// gives back the configuration case
UINT8
get_the_config_case_num (
  const MRC_ADDR_FUNCTION *MrcCall,
  UINT16 ddr_type,
  UINT16 enhanced_ch_mode,
  UINT16 num_of_dimms,
  UINT16 num_of_ranks,
  UINT16 dimm_l_num_of_ranks,
  UINT16 dimm_l_8Gb,
  UINT16 dimm_l_width,
  UINT64 dimm_l_size,
  UINT64 dimm_s_size,
  BOOLEAN same_dimm_width_or_one_dimm,
  BOOLEAN dimm_and_rank_interleaving,
  BOOLEAN zone0
)
{
  UINT8 config_case = 0xFF;

  if (ddr_type == 0)// DDR4
  {
    if (!dimm_and_rank_interleaving)
    {
      return 40;
    }

    if (same_dimm_width_or_one_dimm)
    {
      if (dimm_l_width == 8) // DDR x8
      {
        if (num_of_dimms == 1) {
          switch (num_of_ranks) {
          case 1:
            config_case = 20;
            return config_case;
          case 2:
            config_case = 22;
            return config_case;
          }
        }
        if (num_of_dimms == 2)
        {
          switch (num_of_ranks) {
          case 2:
            config_case = (zone0 ? 21 : 20);
            return config_case;
          case 3:
            config_case = (zone0 ? 24 : ((dimm_l_num_of_ranks == 2) ? 22 : 20));
            return config_case;
          case 4:
            config_case = (zone0 ? 23 : 22);
            return config_case;
          }
        }
      } else // DDR4 x16
      {
        if (num_of_dimms == 1)
        {
          switch (num_of_ranks)
          {
          case 1:
            config_case = 26;
            return config_case;
          case 2:
            config_case = 28;
            return config_case;
          }
        }
        if (num_of_dimms == 2)
        {
          switch (num_of_ranks)
          {
          case 2:
            config_case = (zone0 ? 27 : 26);
            return config_case;
          case 3:
            config_case = (zone0 ? 30 : ((dimm_l_num_of_ranks == 2) ? 28 : 26));
            return config_case;
          case 4:
            config_case = (zone0 ? 29 : 28);
            return config_case;
          }
        }

      }
    } else // DDR4 x8 & x16
    {
      switch (num_of_ranks)
      {
      case 2:
        config_case = (zone0 ? 32 : ((dimm_l_width == 8) ? 20 : 26));
        return config_case;
      case 3:
        if (dimm_l_num_of_ranks == 2) {
          if (dimm_l_width == 16) {
            config_case = (zone0 ? 38 : 28);
          } else {
            config_case = (zone0 ? 36 : 22);
          }
        } else {
          if (dimm_l_width == 16) {
            config_case = (zone0 ? 36 : 26);
          } else {
            config_case = (zone0 ? 38 : 20);
          }
        }
        return config_case;
      case 4:
        config_case = (zone0 ? 34 : ((dimm_l_width == 8) ? 22 : 28));
        return config_case;
      }

    }
  } else if (ddr_type == 3) { // LPDDR4

    if (!dimm_and_rank_interleaving)
    {
      return 80;
    }
    if (num_of_dimms == 1)
    {
      switch (num_of_ranks) {
      case 1:
        config_case = 70;
        return config_case;
      case 2:
        config_case = 71;
        return config_case;
      case 3:
        config_case = 89;
        return config_case;
      case 4:
        config_case = 89;
        return config_case;
      }
    } // End dimms = 1
    if (num_of_dimms == 2)
    {
      switch (num_of_ranks) {
      case 2:
        config_case = zone0 ? 72 : 70;
        return config_case;
      case 4:
        config_case = zone0 ? 73 : 71;
        return config_case;
      case 6:
        config_case = zone0 ? 90 : 89;
        return config_case;
      case 8:
        config_case = zone0 ? 90 : 89;
        return config_case;
      }
    } // end dimms = 2
  } // End LPDDR4

  return config_case;
}


// Function to get the col and row number of bits.
UINT16
get_col_row (
  UINT16 ddr_type,
  UINT8 rank_size,
  UINT16 rank_width
)
{
  UINT16 num_rows;
  UINT16 num_cols;
  INT16 size_4_switch;

  size_4_switch = rank_size;
  num_rows = 0;
  num_cols = 0;

  if (ddr_type == 3) //LPDDR4
  {
    num_cols = 10;
    switch (size_4_switch) {
    case 0:
      num_rows = 0;
      num_cols = 0;
      break;
    case 1:
      num_rows = 14;
      break;
    case 2:
      num_rows = 15;
      break;
    case 4:
      num_rows = 16;
      break;
    case 8:
      num_rows = 16;
      num_cols = 11;
      break;
    }
    if ((rank_width == 16) && (rank_size != 8) && (rank_size != 0)) {
      num_rows = num_rows - 1;
    }
  } else if (ddr_type == 4) { // DDR4
    num_cols = 10;
    switch (size_4_switch) {
    case 0:
      num_rows = 0;
      num_cols = 0;
      break;
    case 2:
      num_rows = 14;
      break;
    case 4:
      num_rows = 15;
      break;
    case 8:
      num_rows = 16;
      break;
    case 16:
      num_rows = 17;
      break;
    }
    if ((rank_width == 16) && (rank_size != 16) && (rank_size != 0)) {
      num_rows = num_rows - 1;
    }
  }
  num_cols = (num_cols * 256);
  return (num_rows + num_cols);
}

/**
  Address decode function
  Converts system address to DRAM address

  @param[in]      MrcCall            - pointer to MRC_ADDR_FUNCTION struct
  @param[in]      sys_addr           - the 39-bit system address to convert
  @param[in, out] p_is_tcm           - is the transaction to sys_addr "traffic class for the manageability engine"
  @param[in]      TOLUD              - memory register
  @param[in]      REMAP_BASE         - memory register
  @param[in]      REMAP_LIMIT        - memory register
  @param[in]      TOM                - memory register
  @param[in]      CHANNEL_HASH       - memory register
  @param[in]      CHANNEL_EHASH      - memory register
  @param[in]      MAD_INTER_CHNL     - memory register
  @param[in]      MAD_INTRA_CHNL_ch0 - memory register
  @param[in]      MAD_INTRA_CHNL_ch1 - memory register
  @param[in]      MAD_DIMM_ch0       - memory register
  @param[in]      MAD_DIMM_ch1       - memory register
  @param[out]     p_chan             - channel sys_addr decodes to
  @param[out]     p_dimm             - DIMM sys_addr decodes to
  @param[out]     p_rank             - rank sys_addr decodes to
  @param[out]     p_bg               - bank group sys_addr decodes to
  @param[out]     p_bank             - bank sys_addr decodes to
  @param[out]     p_row              - row sys_addr decodes to
  @param[out]     p_col              - column sys_addr decodes to.

  @retval TRUE if successful.

**/
BOOLEAN
MrcDecode (
  IN const MRC_ADDR_FUNCTION *MrcCall,
  IN       UINT64       sys_addr,
  IN OUT   BOOLEAN      *p_is_tcm,
  IN       UINT32       TOLUD,
  IN       UINT64       REMAP_BASE,
  IN       UINT64       REMAP_LIMIT,
  IN       UINT64       TOM,
  IN       UINT32       CHANNEL_HASH,
  IN       UINT32       CHANNEL_EHASH,
  IN       UINT32       MAD_INTER_CHNL,
  IN       UINT32       MAD_INTRA_CHNL_ch0,
  IN       UINT32       MAD_INTRA_CHNL_ch1,
  IN       UINT32       MAD_DIMM_ch0,
  IN       UINT32       MAD_DIMM_ch1,
  OUT      UINT16       *p_chan,
  OUT      UINT16       *p_dimm,
  OUT      UINT16       *p_rank,
  OUT      UINT16       *p_bg,
  OUT      UINT16       *p_bank,
  OUT      UINT32       *p_row,
  OUT      UINT16       *p_col
)
{
  UINT64  remap_addr;                     // full address
  UINT64  remap_line;                     // cache-line address
  UINT64  chan_line;                      // channel address space (cache-line)
  UINT64  dimm_l_size;                    // sizes of the DIMMs on the channel in cache-lines
  UINT64  dimm_s_size;
  UINT64  dimm_line;                      // DIMM address space (cache-line)
  UINT64  calculated_tom;
  UINT64  stacked_size;                   // The size of the channels in stacked mode (according to stacked_encoding) (cl address)
  UINT64  ch_s_size;                      // chanel s_size adjusted to cl address
  UINT64  remap_base;                     // REMAP_BASE register after verification and cleanup (system address)
  UINT64  remap_limit;                    // REMAP_LIMIT register after verification and cleanup (system address)
  UINT64  tom;                            // Top Of Memory (system address)
  UINT64  tom_in_cl;                      // Top Of Memory (cl address)
  UINT64  cl_size;
  UINT64  gap_limit;                      // MMIO Gap Limit (system address)
  UINT64  Remainder;
  UINT32  chan_l_mad_dimm;                // channel L's MAD_DIMM register
  UINT32  tolud;                          // TOLUD register after verification and cleanup (system address)
  UINT32  selected_mad_dimm;              // MAD_DIMM for the selected channel
  UINT32  selected_mad_intra_chnl;        // MAD_INTRA_CHNL for the selected channel
  UINT32  rank_size;                      // size of selected DIMM (cache-lines)
  UINT32  dimm_size;                      // size of selected DIMM (cache-lines)
  UINT16  D8Gb;                           // 0-> NOT 8Gb; 1-> 8Gb
  UINT16  hash_lsb_mask_bit;              // LsbMaskBit field from CHANNEL_HASH register
  UINT16  hash_mask;                      // channel hash mask from CHANNEL_HASH register
  UINT16  chnl_num_of_dimms;
  UINT16  chnl_num_of_ranks;
  UINT16  hash_line;                      // lower bits of remap_line with hash_mask applied
  UINT16  i;                              // loop counter
  UINT16  bankBit;
  UINT16  xorBit;
  UINT16  chan_select;                    // 0 = Channel L, 1 = Channel S
  UINT16  dimm_select;                    // 0 = DIMM L, 1 = DIMM S
  UINT16  dual_rank;                      // number of ranks on selected DIMM
  UINT16  dlnor;
  UINT16  dimm_width;
  UINT16  nor_g2;                         // DDR4 EBH
  UINT16  nor_1;                          // DDR4 EBH
  UINT16  xor_ebh[XaB_NUM_OF_BITS];       // storing temporary results for debug printing
  UINT16  MCMNTS_SPARE;

  UINT16  rank_bit_shift;                 // temporary values for bit masking and shifting
  UINT16  config_case_num_int_for_switch;
  UINT16  converter_step;
  // shifters for bit select not from the address decode map
  UINT16  ddr_type;                      // DDR4=0; DDR3=1; LPDDR3=2; LPDDR4=3, WIO2=4;
  UINT16  enhanced_ch_mode;              // Enabled = 0; Disabled = 1;
  UINT16  bg0_on_bit_11;                 // Enabled = 0; Disabled = 1;
  UINT16  stacked_encoding;              // Stacked mode channel hash bits
  UINT16  ch_l_map;                      // Virtual channel L mapping (0 - CH 0; 1 - CH 1)
  INT16   dimm_enhanced_shifter[DIMM_NUM_BITS];
  INT16   rank_enhanced_shifter[RANK_NUM_BITS];
  INT16   bank_enhanced_shifter[BANK_NUM_BITS];
  INT16   col_enhanced_shifter[COL_NUM_BITS];
  INT16   bg_enhanced_shifter[BG_NUM_BITS];
  // shifters for bit select (from chnl_addr) according to the address decode map
  INT16   dimm_shifter[DIMM_NUM_BITS];
  INT16   rank_shifter[RANK_NUM_BITS];
  INT16   bank_shifter[BANK_NUM_BITS];
  INT16   row_shifter[ROW_NUM_BITS];
  INT16   col_shifter[COL_NUM_BITS];
  INT16   bg_shifter[BG_NUM_BITS];
  UINT32  mad_dimm_l[2];                  // Make a MAD_DIMM array for easy access
  UINT32  mad_intra_chnl_l[2];            // Make a MAD_INTRA_CHNL array for easy access
  UINT16  dimm_select_arr[DIMM_NUM_BITS];
  UINT16  rank_select_arr[RANK_NUM_BITS];
  UINT16  bg_select_arr[BG_NUM_BITS];
  UINT16  bank_select_arr[BANK_NUM_BITS];
  UINT16  row_select_arr[ROW_NUM_BITS];
  UINT16  col_select_arr[COL_NUM_BITS];
  UINT8   config_arr[DRAM_ADDR_SIZE + 1];
  UINT8   enh_config_arr[ENHANCED_BITS_SIZE + 1];
  UINT8   config_case_num;
  BOOLEAN dimm_and_rank_interleaving;    // modes for the selected channel
  BOOLEAN high_order_rank_interleave;    // Not supported in SKL for now.
  BOOLEAN enhanced_interleave_mode;
  BOOLEAN same_dimm_width_or_one_dimm;
  BOOLEAN stacked_mode_ch1;              // Stacking channel 0 on top of channel 1
  BOOLEAN stacked_mode;                  // channel stacking enabled
  UINT32  ebh_enable;                     // Enhanced Bank Enable
  UINT32  XaB_enable;                     // xor XaB enable
  UINT32  XbB_enable;                     // xor XbB_lp4 enable

  ebh_enable = 0;                     // Enhanced Bank Enable
  XaB_enable = 0;                     // xor XaB enable
  XbB_enable = 0;                     // xor XbB_lp4 enable

  MrcCall->MrcSetMem ((UINT8 *)mad_dimm_l, sizeof (mad_dimm_l), 0);
  MrcCall->MrcSetMem ((UINT8 *)mad_intra_chnl_l, sizeof (mad_intra_chnl_l), 0);
  MrcCall->MrcSetMem ((UINT8 *)config_arr, sizeof (config_arr), 0);
  MrcCall->MrcSetMem ((UINT8 *)enh_config_arr, sizeof (enh_config_arr), 0);
  MrcCall->MrcSetMem ((UINT8 *)dimm_shifter, sizeof (dimm_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *)rank_shifter, sizeof (rank_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *)bg_shifter, sizeof (bg_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *)bank_shifter, sizeof (bank_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *)row_shifter, sizeof (row_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *)col_shifter, sizeof (col_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *)dimm_enhanced_shifter, sizeof (dimm_enhanced_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *)rank_enhanced_shifter, sizeof (rank_enhanced_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *)bg_enhanced_shifter, sizeof (bg_enhanced_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *)bank_enhanced_shifter, sizeof (bank_enhanced_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *)col_enhanced_shifter, sizeof (col_enhanced_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *)dimm_select_arr, sizeof (dimm_select_arr), 0);
  MrcCall->MrcSetMem ((UINT8 *)rank_select_arr, sizeof (rank_select_arr), 0);
  MrcCall->MrcSetMem ((UINT8 *)bg_select_arr, sizeof (bg_select_arr), 0);
  MrcCall->MrcSetMem ((UINT8 *)bank_select_arr, sizeof (bank_select_arr), 0);
  MrcCall->MrcSetMem ((UINT8 *)row_select_arr, sizeof (row_select_arr), 0);
  MrcCall->MrcSetMem ((UINT8 *)col_select_arr, sizeof (col_select_arr), 0);

  dimm_line = 0;
  dimm_select = 0;
  ddr_type = get_ddr_type (MAD_INTER_CHNL);
  enhanced_ch_mode = get_enhanced_ch_mode (MAD_INTER_CHNL);
  MCMNTS_SPARE = 0;

  // zero out unused register bits
  tolud = TOLUD       & MC_ADDR_TOLUD_MASK;
  remap_base = REMAP_BASE  & MC_ADDR_REMAP_MASK;
  remap_limit = REMAP_LIMIT & MC_ADDR_REMAP_MASK;
  tom = TOM         & MC_ADDR_REMAP_MASK;

  // b4194941 - Assume lower bits of REMAP_LIMIT are all 1's.
  remap_limit |= MC_ADDR_REMAP_LIMIT_LOWER_BITS_MASK;


  mad_dimm_l[0] = MAD_DIMM_ch0;
  mad_dimm_l[1] = MAD_DIMM_ch1;
  mad_intra_chnl_l[0] = MAD_INTRA_CHNL_ch0;
  mad_intra_chnl_l[1] = MAD_INTRA_CHNL_ch1;

  // TOM is not directly available in a register. It will be computed by
  // finding the channel index of channel L, then adding the two DIMM
  // capacities of that channel together. Technically, this is only needed to
  // check that the system address is not beyond the amount of memory
  // available.
  ch_s_size = get_ch_s_size_as_cl (MrcCall, MAD_INTER_CHNL);
  ch_l_map = get_ch_l_map (MAD_INTER_CHNL);
  chan_l_mad_dimm = mad_dimm_l[ch_l_map];


  calculated_tom = cl_to_sys (MrcCall, get_dimm_l_size_as_cl (MrcCall, chan_l_mad_dimm));
  calculated_tom += cl_to_sys (MrcCall, get_dimm_s_size_as_cl (MrcCall, chan_l_mad_dimm));
  calculated_tom += cl_to_sys (MrcCall, ch_s_size);

  tom_in_cl = MrcCall->MrcRightShift64 (tom, 6);


  // determine if we are in stacked mode; and if so, what the stacked size is.
  stacked_mode = get_stacked_mode (MAD_INTER_CHNL);
  if (stacked_mode) {
    stacked_mode_ch1 = get_stacked_mode_ch1 (MAD_INTER_CHNL);
    stacked_encoding = get_stacked_encoding (MAD_INTER_CHNL);
    stacked_size = get_stacked_memory_size (MrcCall, stacked_encoding);
  } else {
    stacked_mode_ch1 = FALSE;
    stacked_encoding = 0;
    stacked_size = 0;
  }
  // determine if we are in EBH mode enable
  ebh_enable = get_ebh_mode (MCMNTS_SPARE);
  if (ebh_enable) {
    XaB_enable = ebh_enable & 1;
    XbB_enable = (ebh_enable >> 1) & 1;
  }

  // remap the address if it is not a TCM transaction and falls inside the remap range
  remap_addr = sys_addr;
  if (remap_limit > remap_base) { // check for remap region being enabled

    gap_limit = ((UINT64)tolud) + remap_limit - remap_base;

    // check for address falling in remap region
    //
    if ((sys_addr >= remap_base) && (sys_addr <= remap_limit))  // b4194941 - REMAP_LIMIT is now inclusive
    {
      // The address hit the remap region, so remap the address from the remap
      // source region (REMAP_BASE to REMAP_LIMIT) to the remap target region
      // (TOLUD to size-of-gap).
      //
      remap_addr -= remap_base;
      remap_addr += ((UINT64)tolud);

    } else if ((sys_addr < tom) && (sys_addr > gap_limit) && (sys_in_gb (MrcCall, tom) <= 4)) { // check for address falling in the ME STOLEN region, when TOM is less than 4GB.
      if (*p_is_tcm) {
        remap_addr = sys_addr;
      } else {
        remap_addr = sys_addr;
        // *p_is_tcm = TRUE;
      }
    } else if ((sys_addr >= (UINT64)tolud) && (sys_addr <= gap_limit)) { // b4194941// check for address falling in MMIO gap created by remap region
      DEBUG ((
        DEBUG_ERROR,
        "The system address was in the MMIO gap created by the remap region. The memory controller cannot process requests to addresses that are not mapped to DRAM.\n(sys_addr >= TOLUD) && (sys_addr <= (TOLUD + REMAP_LIMIT - REMAP_BASE))\nsys_addr = 0x%llX (~%u GB)\nTOLUD = 0x%08x (~%u GB)\n(TOLUD + REMAP_LIMIT - REMAP_BASE) = 0x%llX (~%u GB)\nREMAP_LIMIT = 0x%llX (~%u GB)\n              REMAP_BASE = 0x%llX (~%u GB)\n",
        sys_addr,
        sys_in_gb (MrcCall, sys_addr),
        tolud,
        sys_in_gb (MrcCall, tolud),
        gap_limit,
        sys_in_gb (MrcCall, gap_limit),
        remap_limit,
        sys_in_gb (MrcCall, remap_limit),
        remap_base,
        sys_in_gb (MrcCall, remap_base)
        ));


      // transaction to sys_addr should not have been TCM.
      *p_is_tcm = FALSE;

      return FALSE;
    } else { //no remap
      // transaction to sys_addr should not have been TCM, but the memory
      // controller will process the request anyway without any problems.
      //
      // *p_is_tcm = FALSE;
    }
  } else { //if (REMAP_LIMIT > REMAP_BASE)
    // transaction to sys_addr should not have been TCM, but the memory
    // controller will process the request anyway without any problems.
    //
    // *p_is_tcm = FALSE;
  }

  // from now on we will work on cache-line addresses
  remap_line = MrcCall->MrcRightShift64 (remap_addr, 6); // shift off intra-cache-line bits
  if (stacked_mode) {
    // In stacked mode, check that remapped address is below TOM.
    if (remap_line >= tom_in_cl) {
      DEBUG ((
        DEBUG_ERROR,
        "System address did not map to DRAM memory. It was above TOM after remap.\n(Stacked channel mode enabled.)\nsys_addr = 0x%llX (~%u GB)\nremap_addr = 0x%llX (~%u GB)\nremap_line = 0x%llX\n              tom = 0x%llX (line address)\n              TOM = Top Of Memory (i.e. DRAM memory capacity)= 0x%llX (~%u GB)\n",
        sys_addr,
        sys_in_gb (MrcCall, sys_addr),
        remap_addr,
        sys_in_gb (MrcCall, remap_addr),
        remap_line,
        tom_in_cl,
        tom,
        sys_in_gb (MrcCall, tom)
        ));

      return FALSE;
    }
  } //if (stacked_mode)

  // If we are in stacked channel mode, then the memory from the channels is stacked to create the system memory.
  //
  //  +------0.5 TB------+
  //  |                  |
  //  .                  .
  //  .                  .
  //  .                  .
  //  |                  |
  //  |  unmapped        |
  //  |  space above     |
  //  |  DRAM            |
  //  |                  |
  //  +--2 * Stack size--+  <-- Top Of Memory = L + S
  //  |                  |
  //  |                  |
  //  |                  |
  //  |   Channel S      |
  //  |                  |
  //  |                  |
  //  +--- Stack size ---+  <-- Stack Size = Channel size (channels L and S must be equal)
  //  |                  |
  //  |                  |
  //  |                  |
  //  |   Channel L      |
  //  |                  |
  //  |                  |
  //  +--------0x0-------+
  //
  if (stacked_mode) {
    chan_select = (remap_line < stacked_size) ? 0 : 1;
    chan_line = remap_line;

    // If this is channel 1 in stacked mode, then we need to subtract out the channel size (clear
    // the stacked mode bit)
    //
    if (chan_select == 1) {
      chan_line = chan_line - stacked_size;
    }

    if (stacked_mode_ch1) {
      chan_select ^= 1;
    }
  } else if (remap_line < MrcCall->MrcLeftShift64 (ch_s_size, 1)) { // Zone 0
    // Channel Interleaving Zones
    //
    // Determine which range/zone the remapped system address falls into
    //
    //  +-----0.5 TB-----+
    //  |                |
    //  .                .
    //  .                .
    //  .                .
    //  |                |
    //  |  unmapped      |
    //  |  space above   |
    //  |  DRAM          |
    //  |                |
    //  +--Zone 1 Limit--+  <-- Top Of Memory = L + S
    //  |                |
    //  |  No Interleave |
    //  |    Channel L   |
    //  |                |
    //  +--Zone 0 Limit--+  <-- 2 * S
    //  |                |
    //  |                |
    //  |                |
    //  |  2-Way Intlv   |
    //  | Channels L & S |
    //  |                |
    //  |                |
    //  |                |
    //  |                |
    //  +-------0x0------+
    //

    // Determine if the channel hash feature is being used
    if (CHANNEL_HASH & MC_ADDR_CHAN_HASH_ENABLE_MASK) { // test enable bit
      hash_lsb_mask_bit = get_ch_hash_lsb_mask_bit (CHANNEL_HASH);
      hash_mask = get_ch_hash_mask (CHANNEL_HASH);
      hash_mask = hash_mask | (1 << hash_lsb_mask_bit); // force the selected hash_lsb_mask_bit to be on
      hash_line = ((UINT16)remap_line) & hash_mask; // get the bits to XOR for the hash

      // Produce chan_select by XORing together all of the bits of hash_line.
      chan_select = 0;
      for (i = 0; i < MC_ADDR_CHANNEL_HASH_MASK_SIZE; i++) {
        chan_select = chan_select ^ (hash_line >> i);
      }
      chan_select = chan_select & 1;

      // sys_addr in hash_lsb_mask_bit index, will be remove from sys_addr
      // and the highest bits will shift right in 1 bit.
      chan_line = MrcCall->MrcRightShift64 (remap_line & (MrcCall->MrcLeftShift64 (0xFFFFFFFFFFFFFFFFULL, hash_lsb_mask_bit + 1)), 1);
      chan_line = chan_line | (remap_line & ~(MrcCall->MrcLeftShift64 (0xFFFFFFFFFFFFFFFFULL, hash_lsb_mask_bit)));
    } else {
      chan_select = (UINT16)(remap_line & 1); // remap_addr[6:6]
      chan_line = MrcCall->MrcRightShift64 (remap_line, 1); // right shift by 1 divides by 2
    }

  } else if (remap_line < tom_in_cl) { // Zone 1
    chan_select = 0; // Channel L
    chan_line = remap_line - ch_s_size;
  } else { // address was above memory capacity
    DEBUG ((
      DEBUG_ERROR,
      "System address did not map to DRAM memory. It was above TOM after remap.\nsys_addr = 0x%llX (~%u GB)\nremap_addr = 0x%llX (~%u GB)\nremap_line = 0x%llX\ntom = 0x%llX (line address)\nTOM = Top Of Memory (i.e. DRAM memory capacity)= 0x%llX (~%u GB)\n",
      sys_addr,
      sys_in_gb (MrcCall, sys_addr),
      remap_addr,
      sys_in_gb (MrcCall, remap_addr),
      remap_line,
      tom_in_cl,
      tom,
      sys_in_gb (MrcCall, tom)
      ));

    return FALSE;
  }

  // obtain the physical channel index
  *p_chan = logical_to_physical_chan (MAD_INTER_CHNL, chan_select);


  // get the register for the channel we're using
  selected_mad_dimm = mad_dimm_l[*p_chan];
  selected_mad_intra_chnl = mad_intra_chnl_l[*p_chan];

  // Find the DIMM sizes on our selected channel. adjust to cache-line granularity
  dimm_l_size = get_dimm_l_size_as_cl (MrcCall, selected_mad_dimm);
  dimm_s_size = get_dimm_s_size_as_cl (MrcCall, selected_mad_dimm);

  // Find number of ranks and dimms in the selected channel
  chnl_num_of_dimms = (dimm_l_size) ? ((dimm_s_size) ? 2 : 1) : 0;
  chnl_num_of_ranks = ((dimm_l_size) ? get_dimm_l_number_of_ranks (selected_mad_dimm) : 0) + ((dimm_s_size) ? get_dimm_s_number_of_ranks (selected_mad_dimm) : 0);

  // Find the dimm width chnl configuration
  same_dimm_width_or_one_dimm = (dimm_s_size) ?
    ((get_dimm_l_width (selected_mad_dimm) == get_dimm_s_width (selected_mad_dimm)) ? TRUE : FALSE) : TRUE;


  // determine if we are doing DIMM and Rank interleaving
  dimm_and_rank_interleaving = get_dimm_and_rank_intlv (selected_mad_intra_chnl);

  // determine if we are doing high order rank interleave
  high_order_rank_interleave = get_high_order_intlv_mode (selected_mad_intra_chnl);

  // determine if we are doing Enhanced Interleave Mode (EIM) (XOR rank, bg & bank bits)
  enhanced_interleave_mode = get_enhanced_intlv_mode (selected_mad_intra_chnl);

  // get the configuration case
  config_case_num = get_the_config_case_num (
    MrcCall,
    ddr_type,
    enhanced_ch_mode,
    chnl_num_of_dimms,
    chnl_num_of_ranks,
    get_dimm_l_number_of_ranks (selected_mad_dimm),
    get_dimm_l_8Gb (selected_mad_dimm),
    get_dimm_l_width (selected_mad_dimm),
    get_dimm_l_size_as_cl (MrcCall, selected_mad_dimm),
    get_dimm_s_size_as_cl (MrcCall, selected_mad_dimm),
    same_dimm_width_or_one_dimm,
    dimm_and_rank_interleaving,
    TRUE
  );


  config_case_num_int_for_switch = config_case_num;

  // calling the parsing method, to get the address decode map for the current configuration.
  // This is the first call, just to know the DIMM shifters
  // in the case of no interleave mode, we don't need this call
  if (dimm_and_rank_interleaving) {
    addr_decode_map_parse (MrcCall, config_arr, config_case_num, FALSE);
    if (enhanced_interleave_mode) {
      enhanced_mode_map_parse (MrcCall, enh_config_arr, config_case_num, FALSE);
    }
  }

  //dimm_shifters
  for (i = 0; i < DIMM_NUM_BITS; i++) {
    dimm_shifter[i] = (config_arr[i + 1] - 6);
    if (enhanced_interleave_mode) {
      dimm_enhanced_shifter[i] = (enh_config_arr[i + 1] - 6);
    }
  }
  // DIMM address calculation
  // DIMMs are interleaved for both dimm_and_rank_interleaving and high_order_rank_interleave modes.
  if (dimm_and_rank_interleaving || high_order_rank_interleave) {
    // DIMM and Rank interleaving enabled
    //  +------32 GB------+
    //  |                 |
    //  .                 .
    //  .                 .
    //  .                 .
    //  |                 |
    //  |  unmapped       |
    //  |  space above    |
    //  |  channel        |
    //  |  capacity       |
    //  |                 |
    //  +-- Zone 1 Limit--+  <-- dimm_l_size + dimm_s_size
    //  |                 |
    //  |  No Interleave  |
    //  |     DIMM L      |
    //  |                 |
    //  +-- Zone 0 Limit--+  <-- dimm_s_size * 2
    //  |                 |
    //  | 2-Way Interleave|
    //  |   DIMMs L & S   |
    //  |                 |
    //  +-------0x0-------+
    //


    if (chan_line < MrcCall->MrcLeftShift64 (dimm_s_size, 1)) { // Range 0 limit = 2 * dimm_s_size
      // get the configuration case
      config_case_num = get_the_config_case_num (
        MrcCall,
        ddr_type,
        enhanced_ch_mode,
        chnl_num_of_dimms,
        chnl_num_of_ranks,
        get_dimm_l_number_of_ranks (selected_mad_dimm),
        get_dimm_l_8Gb (selected_mad_dimm),
        get_dimm_l_width (selected_mad_dimm),
        get_dimm_l_size_as_cl (MrcCall, selected_mad_dimm),
        get_dimm_s_size_as_cl (MrcCall, selected_mad_dimm),
        same_dimm_width_or_one_dimm,
        dimm_and_rank_interleaving,
        TRUE
      );


      config_case_num_int_for_switch = config_case_num;

      // calling the parsing method, to get the address decode map for the current configuration.
      // This is the first call, just to know the DIMM shifters
      // in the case of no interleave mode, we don't need this call
      if (dimm_and_rank_interleaving) {
        addr_decode_map_parse (MrcCall, config_arr, config_case_num, FALSE);
        if (enhanced_interleave_mode) {
          enhanced_mode_map_parse (MrcCall, enh_config_arr, config_case_num, FALSE);
        }
      }


      // Determine if the sub channel hash feature is being used
      if (CHANNEL_EHASH & MC_ADDR_CHAN_HASH_ENABLE_MASK) { // test enable bit
        hash_lsb_mask_bit = get_ch_hash_lsb_mask_bit (CHANNEL_EHASH);
        hash_mask = get_ch_hash_mask (CHANNEL_EHASH);
        hash_mask = hash_mask | (1 << hash_lsb_mask_bit); // force the selected hash_lsb_mask_bit to be on

        hash_line = ((UINT16)chan_line) & hash_mask; // get the bits to XOR for the hash

        // Produce chan_select by XORing together all of the bits of hash_line.
        dimm_select = 0;
        for (i = 0; i < MC_ADDR_CHANNEL_HASH_MASK_SIZE; i++) {
          dimm_select = dimm_select ^ (hash_line >> i);
        }
        dimm_select = dimm_select & 1;

        // sys_addr in hash_lsb_mask_bit index, will be remove from sys_addr
        // and the highest bits will shift right in 1 bit.
        dimm_line = chan_line & MrcCall->MrcLeftShift64 (0xFFFFFFFFFFFFFFFFULL, hash_lsb_mask_bit + 1);
        dimm_line = dimm_line | (MrcCall->MrcLeftShift64 (chan_line & (~(MrcCall->MrcLeftShift64 (0xFFFFFFFFFFFFFFFFULL, hash_lsb_mask_bit))), 1) | (UINT16)dimm_select);
      } else {
        // 2-way DIMM interleave. Channel address is used to select DIMM according to the decode map.
        // In SKL DIMM_NUM_BITS==1. all the for loops are for the case there will be mor than 2 dimms.
        for (i = 0; i < DIMM_NUM_BITS; i++) {
          //the dimm shifter can be a negative number
          dimm_select_arr[i] = (UINT16)MrcCall->MrcRightShift64 (chan_line, dimm_shifter[i]) & 1;
          if (enhanced_interleave_mode) {
            if (dimm_enhanced_shifter[i] != -6) {
              dimm_select_arr[i] = dimm_select_arr[i] ^ (MrcCall->MrcRightShift64 (chan_line, dimm_enhanced_shifter[i]) & 1);
            }
          }
        }
        dimm_select = 0;
        for (i = 0; i < DIMM_NUM_BITS; i++) {
          dimm_select += (dimm_select_arr[i] << i);
        }
        dimm_line = chan_line;
      }
    } else if (chan_line < (dimm_l_size + dimm_s_size)) { // Range 1 limit
      // get the configuration case
      config_case_num = get_the_config_case_num (
        MrcCall,
        ddr_type,
        enhanced_ch_mode,
        chnl_num_of_dimms,
        chnl_num_of_ranks,
        get_dimm_l_number_of_ranks (selected_mad_dimm),
        get_dimm_l_8Gb (selected_mad_dimm),
        get_dimm_l_width (selected_mad_dimm),
        get_dimm_l_size_as_cl (MrcCall, selected_mad_dimm),
        get_dimm_s_size_as_cl (MrcCall, selected_mad_dimm),
        same_dimm_width_or_one_dimm,
        dimm_and_rank_interleaving,
        FALSE
      );


      config_case_num_int_for_switch = config_case_num;

      // calling the parsing method, to get the address decode map for the current configuration.
      // This is the first call, just to know the DIMM shifters
      // in the case of no interleave mode, we don't need this call
      if (dimm_and_rank_interleaving) {
        addr_decode_map_parse (MrcCall, config_arr, config_case_num, FALSE);
        if (enhanced_interleave_mode) {
          enhanced_mode_map_parse (MrcCall, enh_config_arr, config_case_num, FALSE);
        }
      }

      // No DIMM interleave. DIMM is the largest DIMM: DIMM L.
      dimm_select = 0;

      // DIMM address is channel address with DIMM S's contribution removed
      dimm_line = chan_line - dimm_s_size;
    } else {
      DEBUG ((
        DEBUG_ERROR,
        "Channel address was greater than memory on channel.\nsys_addr = 0x%llX (~%u GB)\nremap_addr = 0x%llX (~%u GB)\nremap_line = 0x%llX\nchan = %u\nchan_line = 0x%llX\ndimm_l_size = 0x%llX (line address)\ndimm_s_size = 0x%llX (line address)\ndimm_l_size + dimm_s_size = 0x%llX (line address)\ndimm_and_rank_interleaving = %u\n",
        sys_addr,
        sys_in_gb (MrcCall, sys_addr),
        remap_addr,
        sys_in_gb (MrcCall, remap_addr),
        remap_line,
        *p_chan,
        chan_line,
        dimm_l_size,
        dimm_s_size,
        (dimm_l_size + dimm_s_size),
        dimm_and_rank_interleaving
        ));

      return FALSE;
    }
  } else { // no DIMM and Rank interleaving
    //  +------32 GB------+
    //  |                 |
    //  .                 .
    //  .                 .
    //  .                 .
    //  |                 |
    //  |  unmapped       |
    //  |  space above    |
    //  |  channel        |
    //  |  capacity       |
    //  |                 |
    //  +--Range 1 Limit--+  <-- dimm_l_size + dimm_s_size
    //  |                 |
    //  |  No Interleave  |
    //  |     DIMM S      |
    //  |                 |
    //  +--Range 0 Limit--+  <-- dimm_l_size
    //  |                 |
    //  |  No Interleave  |
    //  |     DIMM L      |
    //  |                 |
    //  +-------0x0-------+
    //
    dimm_line = chan_line;
    if (chan_line < dimm_l_size) { // Range 0 limit = dimm_l_size

      // get the configuration case
      config_case_num = get_the_config_case_num (
        MrcCall,
        ddr_type,
        enhanced_ch_mode,
        chnl_num_of_dimms,
        chnl_num_of_ranks,
        get_dimm_l_number_of_ranks (selected_mad_dimm),
        get_dimm_l_8Gb (selected_mad_dimm),
        get_dimm_l_width (selected_mad_dimm),
        get_dimm_l_size_as_cl (MrcCall, selected_mad_dimm),
        get_dimm_s_size_as_cl (MrcCall, selected_mad_dimm),
        same_dimm_width_or_one_dimm,
        dimm_and_rank_interleaving,
        TRUE
      );

      config_case_num_int_for_switch = config_case_num;

      // No DIMM interleave. DIMM is the largest DIMM: DIMM L.
      dimm_select = 0;
      // DIMM address is channel address
    } else if (chan_line < (dimm_l_size + dimm_s_size)) { // Range 1 limit

      // get the configuration case
      config_case_num = get_the_config_case_num (
        MrcCall,
        ddr_type,
        enhanced_ch_mode,
        chnl_num_of_dimms,
        chnl_num_of_ranks,
        get_dimm_l_number_of_ranks (selected_mad_dimm),
        get_dimm_l_8Gb (selected_mad_dimm),
        get_dimm_l_width (selected_mad_dimm),
        get_dimm_l_size_as_cl (MrcCall, selected_mad_dimm),
        get_dimm_s_size_as_cl (MrcCall, selected_mad_dimm),
        same_dimm_width_or_one_dimm,
        dimm_and_rank_interleaving,
        FALSE
      );

      config_case_num_int_for_switch = config_case_num;

      // No DIMM interleave. DIMM is the smallest DIMM: DIMM S.
      dimm_select = 1;
      // DIMM address is channel address with dimm_l_size removed.
      dimm_line -= dimm_l_size;

    } else {
      DEBUG ((
        DEBUG_ERROR,
        "Channel address was greater than memory on channel.\nsys_addr = 0x%llX(~%u GB)\nremap_addr = 0x%llX\nremap_line = 0x%llX\nchan = %u\nchan_line = 0x%llX\ndimm_l_size = 0x%llX (line address)\ndimm_s_size = 0x%llX (line address)\ndimm_l_size + dimm_s_size = 0x%llX (line address)\ndimm_and_rank_interleaving = %u\n",
        sys_addr,
        sys_in_gb (MrcCall, sys_addr),
        remap_addr,
        remap_line,
        *p_chan,
        chan_line,
        dimm_l_size,
        dimm_s_size,
        (dimm_l_size + dimm_s_size),
        dimm_and_rank_interleaving
        ));

      return FALSE;
    }
  }

  // get the physical DIMM index
  *p_dimm = dimm_select ^ get_dimm_l_select (selected_mad_intra_chnl);

  // get DIMM info
  dimm_size = (UINT32)(dimm_select ? dimm_s_size : dimm_l_size);
  dual_rank = dimm_select ? get_dimm_s_number_of_ranks (selected_mad_dimm) : get_dimm_l_number_of_ranks (selected_mad_dimm);
  dlnor = get_dimm_l_number_of_ranks (selected_mad_dimm) - 1;
  D8Gb = dimm_select ? get_dimm_s_8Gb (selected_mad_dimm) : get_dimm_l_8Gb (selected_mad_dimm);
  dimm_width = dimm_select ? get_dimm_s_width (selected_mad_dimm) : get_dimm_l_width (selected_mad_dimm);
  bg0_on_bit_11 = get_DLS_BG0_on_bit_11 (selected_mad_dimm);
  nor_g2 = (dlnor % 2 == 1) & (get_dimm_s_size_as_cl (MrcCall, selected_mad_dimm) != 0) ? 1 : 0;
  nor_1 = (dlnor == 0) & (get_dimm_s_size_as_cl (MrcCall, selected_mad_dimm) == 0) ? 1 : 0;


  // get the exact configuration case
  switch (config_case_num_int_for_switch) {
  case 24: config_case_num = (dual_rank == 2) ? 24 : 25; break;
  case 30: config_case_num = (dual_rank == 2) ? 30 : 31; break;
  case 32: config_case_num = (dimm_width == 8) ? 32 : 33; break;
  case 34: config_case_num = (dimm_width == 8) ? 34 : 35; break;
  case 36: config_case_num = (dimm_width == 8) ? 36 : 37; break;
  case 38: config_case_num = (dimm_width == 8) ? 39 : 38; break;
  case 40: config_case_num = (dimm_width == 8) ? 40 : 41; break;
  case 42: config_case_num = ((D8Gb == 1) && (dimm_width == 8)) ? 43 : 42; break;
  case 95: config_case_num = (dual_rank == 2) ? 95 : 96; break;
  case 101: config_case_num = (dual_rank == 2) ? 101 : 102; break;
  case 103: config_case_num = (dimm_width == 8) ? 103 : 104; break;
  case 105: config_case_num = (dimm_width == 8) ? 105 : 106; break;
  case 107: config_case_num = (dimm_width == 8) ? 107 : 108; break;
  case 109: config_case_num = (dimm_width == 8) ? 109 : 110; break;
  case 111: config_case_num = (dimm_width == 8) ? 111 : 112; break;
    //case 91  : config_case_num = ((D8Gb == 1) && (dimm_width == 8))  ?   113 :  114; break;
  }


  addr_decode_map_parse (MrcCall, config_arr, config_case_num, TRUE);
  if (enhanced_interleave_mode) {
    enhanced_mode_map_parse (MrcCall, enh_config_arr, config_case_num, TRUE);
  }

  converter_step = DIMM_NUM_BITS + 1;
  for (i = 0; i < RANK_NUM_BITS; i++) {
    rank_shifter[(RANK_NUM_BITS - 1) - i] = (config_arr[i + converter_step] - 6);
    rank_enhanced_shifter[(RANK_NUM_BITS - 1) - i] = (enh_config_arr[i + converter_step] - 6);
  }
  converter_step += RANK_NUM_BITS;
  for (i = 0; i < BG_NUM_BITS; i++) {
    bg_shifter[(BG_NUM_BITS - 1) - i] = (config_arr[i + converter_step] - 6);
    bg_enhanced_shifter[(BG_NUM_BITS - 1) - i] = (enh_config_arr[i + converter_step] - 6);
  }
  converter_step += BG_NUM_BITS;
  for (i = 0; i < BANK_NUM_BITS; i++) {
    bank_shifter[(BANK_NUM_BITS - 1) - i] = (config_arr[i + converter_step] - 6);
    bank_enhanced_shifter[(BANK_NUM_BITS - 1) - i] = (enh_config_arr[i + converter_step] - 6);
  }
  converter_step += BANK_NUM_BITS;
  for (i = 0; i < ROW_NUM_BITS; i++) {
    row_shifter[(ROW_NUM_BITS - 1) - i] = (config_arr[i + converter_step] - 6);
  }
  converter_step += ROW_NUM_BITS;
  for (i = 0; i < COL_NUM_BITS; i++) {
    col_shifter[(COL_NUM_BITS - 1) - i] = (config_arr[i + converter_step] - 6);
    col_enhanced_shifter[i] = -6;
  }
  col_enhanced_shifter[10] = (enh_config_arr[8] - 6); // enhanced mode for column[10:10]
  // DRAM address calculation
  // Now compute Rank, Bank Group, Bank, Row and Col
  // high_order_rank_interleave is mutually exclusive with dimm_and_rank_interleaving
  if (dimm_and_rank_interleaving && (dual_rank != 3)) { // rank = from the address map
    for (i = 0; i < RANK_NUM_BITS; i++) {
      if (rank_shifter[i] == -6) {
        rank_select_arr[i] = 0;
      } else {
        rank_select_arr[i] = (UINT16)MrcCall->MrcRightShift64 (dimm_line, rank_shifter[i]) & 1;
      }
      if (enhanced_interleave_mode) {
        if (rank_enhanced_shifter[i] != -6) {
          rank_select_arr[i] = rank_select_arr[i] ^ (MrcCall->MrcRightShift64 (dimm_line, rank_enhanced_shifter[i]) & 1);
        }
      }
    }

    *p_rank = 0;
    for (i = 0; i < RANK_NUM_BITS; i++) {
      *p_rank += (rank_select_arr[i] << i);
    }
  } else { // rank = for the case of no rank interleave
    *p_rank = 0;
    rank_size = dimm_size / dual_rank;

    // support in legacy mode (not ERM)
    if (dual_rank == 2) {
      switch (dimm_size) { // dimm_size is in cache-lines
      case MC_1GB_AS_CL: rank_bit_shift = 23; break; // 1GB
      case MC_2GB_AS_CL: rank_bit_shift = 24; break; // 2GB - 2Gbx16, 2 ranks
      case MC_4GB_AS_CL: rank_bit_shift = 25; break; // 4GB
      case MC_8GB_AS_CL: rank_bit_shift = 26; break; // 8GB
      case MC_16GB_AS_CL: rank_bit_shift = 27; break; // 16GB
      case MC_32GB_AS_CL: rank_bit_shift = 28; break; // 32GB - DDR4 max size (using 16Gb)
      default:
        cl_size = cl_in_gb (MrcCall, dimm_size);
        DEBUG ((
          DEBUG_ERROR,
          "The MAD_DIMM register is incorrectly configured. A DIMM size of 0x%llX (%u GB) is not supported.\nsys_addr = 0x%llX (~%u GB)\n chan = %u\n dimm = %u\n",
          (dimm_size >> 22),
          cl_size,
          sys_addr,
          sys_in_gb (MrcCall, sys_addr),
          *p_chan,
          *p_dimm
          ));
        return FALSE;
      }
      *p_rank = (UINT16)MrcCall->MrcRightShift64 (dimm_line, rank_bit_shift) & ONE_BIT_MASK;
      dimm_line = (UINT16)dimm_line & ~(MrcCall->MrcLeftShift64 (1, rank_bit_shift));
    } else { // support in ERM
      switch (dual_rank) {
      case 3:
        *p_rank = (dimm_line < rank_size) ? 0 : ((dimm_line < 2 * rank_size) ? 1 : 2);
      case 4:
        *p_rank = (dimm_line < rank_size) ? 0 : ((dimm_line < 2 * rank_size) ? 1 : ((dimm_line < 3 * rank_size) ? 2 : 3));
      }
    }
  }

  if ((ddr_type == 0) && bg0_on_bit_11) {
    i = col_shifter[7];
    col_shifter[7] = bg_shifter[0];
    bg_shifter[0] = i;
    i = col_enhanced_shifter[7];
    col_enhanced_shifter[7] = bg_enhanced_shifter[0];
    bg_enhanced_shifter[0] = i;
  }

  // bg = from the address map
  for (i = 0; i < BG_NUM_BITS; i++) {
    if (bg_shifter[i] == -6) {
      bg_select_arr[i] = 0;
    } else {
      bg_select_arr[i] = (UINT16)(MrcCall->MrcRightShift64 (dimm_line, bg_shifter[i]) & 1);
    }
    if (enhanced_interleave_mode) {
      if (bg_enhanced_shifter[i] != -6) {
        bg_select_arr[i] = bg_select_arr[i] ^ (MrcCall->MrcRightShift64 (dimm_line, bg_enhanced_shifter[i]) & 1);
      }
      if (ebh_enable  && ddr_type == 0 && dimm_width == 8 && i == 1) { // EBH on bg1 in DDR4 x8 only
        if (XaB_enable) {
          for (xorBit = 0; xorBit < XaB_NUM_OF_BITS; xorBit++) {
            if (XaB[2][xorBit] == 0) continue;
            xor_ebh[xorBit] = (UINT16)(MrcCall->MrcRightShift64 (chan_line , XaB[2][xorBit]) & 1);
            bg_select_arr[i] = bg_select_arr[i] ^ xor_ebh[xorBit];
          }
        }
        if (XbB_enable) {
          xor_ebh[0] = (UINT16)(MrcCall->MrcRightShift64 (chan_line , XbB_ddr4[dimm_width == 8 ? 0 : 1][2][0])) & nor_1;
          bg_select_arr[i] = bg_select_arr[i] ^ xor_ebh[0];
        }
      }
    }
  }  //for BG_NUM_BITS

  *p_bg = 0;

  for (i = 0; i < BG_NUM_BITS; i++) {
    *p_bg += (bg_select_arr[i] << i);
  }

  // bank = from the address map
  for (bankBit = 0; bankBit < BANK_NUM_BITS; bankBit++) {
    if (bank_shifter[bankBit] == -6) {
      bank_select_arr[bankBit] = 0;
    } else {
      bank_select_arr[bankBit] = (UINT16)(MrcCall->MrcRightShift64 (dimm_line, bank_shifter[bankBit])) & 1;
    }
    if (enhanced_interleave_mode) {
      if (bank_enhanced_shifter[bankBit] != -6) {
        bank_select_arr[bankBit] = bank_select_arr[bankBit] ^ (MrcCall->MrcRightShift64 (dimm_line, bank_enhanced_shifter[bankBit]) & 1);
        if (ebh_enable) {
          if (XaB_enable) {
            // In DDR4 EBH2 xor with bg1 and not bank2
            if ((ddr_type == 0) && (bankBit == BANK_NUM_BITS - 1)) continue;
            for (xorBit = 0; xorBit < XaB_NUM_OF_BITS; xorBit++) {
              if (XaB[bankBit][xorBit] == 0) continue;
              xor_ebh[xorBit] = (UINT16)(MrcCall->MrcRightShift64(chan_line, XaB[bankBit][xorBit])) & 1;
              bank_select_arr[bankBit] = bank_select_arr[bankBit] ^ xor_ebh[xorBit];
            }
          }
          if (XbB_enable) {
            if (ddr_type == 3) { //LP4
              switch (bankBit)
              {
              case 0:
                xor_ebh[0] = (UINT16)(MrcCall->MrcRightShift64(chan_line, XbB_lp4[bankBit][0])) & 1;
                xor_ebh[1] = (UINT16)(MrcCall->MrcRightShift64(chan_line, XbB_lp4[bankBit][1])) & (dlnor == 0 ? 1 : 0);
                bank_select_arr[bankBit] = bank_select_arr[bankBit] ^ xor_ebh[0] ^ xor_ebh[1];
                break;
              case 1:
                xor_ebh[0] = (UINT16)(MrcCall->MrcRightShift64(chan_line, XbB_lp4[bankBit][0])) & (dlnor < 2 ? 1 : 0);
                xor_ebh[1] = (UINT16)(MrcCall->MrcRightShift64(chan_line, XbB_lp4[bankBit][1])) & (dlnor == 0 ? 1 : 0);
                bank_select_arr[bankBit] = bank_select_arr[bankBit] ^ xor_ebh[0] ^ xor_ebh[1];
                break;
              case 2:
                xor_ebh[0] = (UINT16)(MrcCall->MrcRightShift64(chan_line, XbB_lp4[bankBit][0])) & (dlnor < 2 ? 1 : 0);
                bank_select_arr[bankBit] = bank_select_arr[bankBit] ^ xor_ebh[0];
                break;
              }
            } else if (ddr_type == 0) { //DDR4
              switch (bankBit)
              {
              case 0:
                xor_ebh[0] = (UINT16)(MrcCall->MrcRightShift64(chan_line, XbB_ddr4[dimm_width == 8 ? 0 : 1][bankBit][0])) & (nor_g2 == 0) ? 1 : 0;
                xor_ebh[1] = (UINT16)(MrcCall->MrcRightShift64(chan_line, XbB_ddr4[dimm_width == 8 ? 0 : 1][bankBit][1])) & nor_1 & (XbB_ddr4[dimm_width == 8 ? 0 : 1][bankBit][1] != 0);
                xor_ebh[2] = (UINT16)(MrcCall->MrcRightShift64(chan_line, XbB_ddr4[dimm_width == 8 ? 0 : 1][bankBit][2])) & (XbB_ddr4[dimm_width == 8 ? 0 : 1][bankBit][2] != 0);
                xor_ebh[3] = (UINT16)(MrcCall->MrcRightShift64(chan_line, XbB_ddr4[dimm_width == 8 ? 0 : 1][bankBit][3])) & (XbB_ddr4[dimm_width == 8 ? 0 : 1][bankBit][3] != 0);
                bank_select_arr[bankBit] = bank_select_arr[bankBit] ^ xor_ebh[0] ^ xor_ebh[1] ^ xor_ebh[2] ^ xor_ebh[3];
                break;
              case 1:
                xor_ebh[0] = (UINT16)(MrcCall->MrcRightShift64(chan_line, XbB_ddr4[dimm_width == 8 ? 0 : 1][bankBit][0])) & (nor_g2 == 0) ? 1 : 0;
                xor_ebh[1] = (UINT16)(MrcCall->MrcRightShift64(chan_line, XbB_ddr4[dimm_width == 8 ? 0 : 1][bankBit][1])) & nor_1 & (XbB_ddr4[dimm_width == 8 ? 0 : 1][bankBit][1] != 0);
                xor_ebh[2] = (UINT16)(MrcCall->MrcRightShift64(chan_line, XbB_ddr4[dimm_width == 8 ? 0 : 1][bankBit][2])) & (XbB_ddr4[dimm_width == 8 ? 0 : 1][bankBit][2] != 0);
                xor_ebh[3] = (UINT16)(MrcCall->MrcRightShift64(chan_line, XbB_ddr4[dimm_width == 8 ? 0 : 1][bankBit][3])) & (XbB_ddr4[dimm_width == 8 ? 0 : 1][bankBit][3] != 0);
                bank_select_arr[bankBit] = bank_select_arr[bankBit] ^ xor_ebh[0] ^ xor_ebh[1] ^ xor_ebh[2] ^ xor_ebh[3];
                break;
              }
            }
          }
        }
      }
    }
  }

  *p_bank = 0;

  for (i = 0; i < BANK_NUM_BITS; i++) {
    *p_bank += (bank_select_arr[i] << i);
  }

  // row = from the address map, depends on DIMM size.

  for (i = 0; i < ROW_NUM_BITS; i++) {
    if (row_shifter[i] == -6) {
      row_select_arr[i] = 0;
    } else {
      row_select_arr[i] = (UINT16)MrcCall->MrcRightShift64 (dimm_line, row_shifter[i]) & 1;
    }
  }

  *p_row = 0;

  for (i = 0; i < ROW_NUM_BITS; i++) {
    *p_row += (row_select_arr[i] << i);
  }

  // Support in ERM 3 ranks
  // 1 sub channel 3 ranks:
  // Rank_sel_h,Rnk_sel = Modulus3(Zone_address[33:14])
  // Row[16:0], BANK[2] = Div3(Zone_address[33:14])
  // 2 sub channel 3 rank:
  // Rnk_sel_h,Rnk_sel = Modulus3(Zone_address[34:15])
  // Row[16:0], BANK[2] = Div3(Zone_address[34:15])
  if (dual_rank == 3) {
    // replace bg[1] with the calc rank_h
    *p_bg = *p_bg & 1;
    MrcCall->MrcDivU64x64 (MrcCall->MrcRightShift64 (dimm_line, 8 + (chnl_num_of_dimms == 2)), 3, &Remainder);
    *p_bg = *p_bg + ((Remainder) & 2);

    // replace rank[0] with the calc rank_l
    *p_rank = *p_rank & 2;
    MrcCall->MrcDivU64x64 (MrcCall->MrcRightShift64 (dimm_line, 8 + (chnl_num_of_dimms == 2)), 3, &Remainder);
    *p_rank = *p_rank + ((Remainder) & 1);

    // replace row with cacl row
    *p_row = 0;
    *p_row = (UINT32)(MrcCall->MrcRightShift64 (dimm_line, 8 + (chnl_num_of_dimms == 2)) / 3) >> 1;

    // replace bank[2] with calc ba[2]
    *p_bank = *p_bank & 3;
    *p_bank = *p_bank + ((UINT16)((MrcCall->MrcRightShift64 (dimm_line, 8 + (chnl_num_of_dimms == 2)) / 3) & 1) << 2);
  }

  // Mask away any row bits too large for the size of DIMM (only the number of row bits changes with DIMM size).
  if (ddr_type == 0)
  { // DDR4
    i = (dimm_width == 8) ? 11 : 10;
  } else if (ddr_type == 3)
  { // LPDDR4
    i = 10;
  }
  i = i + ((UINT16)(dual_rank / 2)) - ((UINT16)enhanced_ch_mode);

  *p_row = *p_row & ((UINT32)((dimm_size >> i) - 1));
  // col address at the end of the function - it is the same for all the options
// column is the same for all the options
//

  for (i = 0; i < COL_NUM_BITS; i++) {
    if (col_shifter[i] == -6)
    {
      col_select_arr[i] = 0;
    } else if (col_shifter[i] < 0)
    {
      col_shifter[i] += 6;
      col_select_arr[i] = (UINT16)MrcCall->MrcRightShift64 (sys_addr, col_shifter[i]) & 1;
    } else
    {
      col_select_arr[i] = (UINT16)MrcCall->MrcRightShift64 (dimm_line, col_shifter[i]) & 1;
    }

    if (enhanced_interleave_mode)
    {
      if (col_enhanced_shifter[i] != -6)
      {
        col_select_arr[i] = col_select_arr[i] ^ (MrcCall->MrcRightShift64 (dimm_line, col_enhanced_shifter[i]) & 1);
      }
    }
  }

  *p_col = 0;
  for (i = 0; i < COL_NUM_BITS; i++) {
    *p_col += (col_select_arr[i] << i);
  }


  // ERM support: The high bit rank is in bg[1]
  if (dual_rank > 2) {
    *p_rank = *p_rank | (*p_bg & 2);
    *p_bg = 0;
  }


  return TRUE;
}

/**
  Address encode function (reverse address decode)
  DRAM address to system address conversion

  @param[in]      MrcCall            - pointer to MRC_ADDR_FUNCTION struct
  @param[in]      chan               - channel addr to encode
  @param[in]      dimm               - DIMM address to encode
  @param[in]      rank               - rank address to encode
  @param[in]      bg                 - bank group address to encode
  @param[in]      bank               - bank address to encode
  @param[in]      row                - row address to encode
  @param[in]      col                - column address to encode. Note: The architecture is limited to half-cache-line
                                       granularity for burst order. Therefore the last two bits of the column are ignored.
  @param[in]      TOLUD              - memory register
  @param[in]      REMAP_BASE         - memory register
  @param[in]      REMAP_LIMIT        - memory register
  @param[in]      TOM                - memory register
  @param[in]      CHANNEL_HASH       - memory register
  @param[in]      MAD_INTER_CHNL     - memory register
  @param[in]      MAD_INTRA_CHNL_ch0 - memory register
  @param[in]      MAD_INTRA_CHNL_ch1 - memory register
  @param[in]      MAD_DIMM_ch0       - memory register
  @param[in]      MAD_DIMM_ch1       - memory register
  @param[in]      MCMNTS_SPARE       - memory register
  @param[out]     sys_addr           - the 39-bit system address convert to
  @param[in, out] p_is_tcm           - is the transaction to sys_addr "traffic class for the manageability engine"

  @retval         TRUE  - sys_addr decoded without errors and the address outputs are valid.
                  FALSE - An error was encountered while decoding sys_addr.
**/
BOOLEAN
MrcEncode (
  IN const MRC_ADDR_FUNCTION *MrcCall,
  IN       UINT16       chan,
  IN       UINT16       dimm,
  IN       UINT16       rank,
  IN       UINT16       bg,
  IN       UINT16       bank,
  IN       UINT32       row,
  IN       UINT16       col,
  IN       UINT32       TOLUD,
  IN       UINT64       REMAP_BASE,
  IN       UINT64       REMAP_LIMIT,
  IN       UINT64       TOM,
  IN       UINT32       CHANNEL_HASH,
  IN       UINT32       CHANNEL_EHASH,
  IN       UINT32       MAD_INTER_CHNL,
  IN       UINT32       MAD_INTRA_CHNL_ch0,
  IN       UINT32       MAD_INTRA_CHNL_ch1,
  IN       UINT32       MAD_DIMM_ch0,
  IN       UINT32       MAD_DIMM_ch1,
  IN       UINT16       MCMNTS_SPARE,
  OUT      UINT64       *p_sys_addr,
  IN OUT   BOOLEAN      *p_is_tcm
)
{
  // address before reverse decoding the remap region
  UINT64  remap_line;                         // cache-line
  UINT64  remap_addr;                         // full address
  UINT64  dimm_select;                        // DIMM L=0, S=1
  UINT64  rank_size;                          // size of rank in ERM
  UINT64  dimm_size;                          // size of selected DIMM
  UINT64  bit_above_row;                      // one-hot bit to mark the size of the row address
  UINT64  calculated_tom;
  UINT64  dimm_line;                          // DIMM address space (cache-line)
  UINT64  dimm_line_c;
  UINT64  chan_line;                          // Channel address space (cache-line)
  UINT64  dimm_l_size;
  UINT64  dimm_s_size;
  UINT64  remap_base;                         // REMAP_BASE register after verification and cleanup (system address)
  UINT64  remap_limit;                        // REMAP_LIMIT register after verification and cleanup (system address)
  UINT64  tom;                                // Top Of Memory (system address)
  UINT64  ch_s_size;                          // chanel s_size adjusted to cl address
  UINT64  top_of_remaped_mem;                 // used for reverse decode of remap region
  UINT32  chan_l_mad_dimm;                    // channel L's MAD_DIMM register
  UINT32  tolud;                              // TOLUD register after verification and cleanup (system address)
  UINT16  hash_lsb_mask_bit;                  // LsbMaskBit field from CHANNEL_HASH register
  UINT16  hash_mask;                          // channel hash mask from CHANNEL_HASH register
  UINT16  dimm_width;                         // x8=8; x16=16
  UINT16  dual_rank;                          // number of ranks on selected DIMM
  // sizes of the DIMMs on the channel (cache-line)
  UINT16  chnl_num_of_dimms;
  UINT16  chnl_num_of_ranks;
  UINT16  num_col_bits;
  UINT16  chan_select;                        // 0 = Channel L, 1 = Channel S
  UINT16  hash_line;                          // lower bits of remap_line with hash_mask applied
  UINT16  hash_bit;                           // bit that gets destroyed in forward decode
  UINT16  i;                                  // loop counter
  INT16   xorBit;
  INT16   bankBit;
  INT16   ebh_loop;
  UINT16  config_case_num_int_for_switch;
  UINT16  converter_step;                     // virtual var
  UINT16  ddr_type;                           // DDR4=0; DDR3=1; LPDDR3=2; LPDDR4=3, WIO2=4;
  UINT16  dlnor;                              // large number of ranks - EBH purpose
  UINT16  nor_g2;
  UINT16  nor_1;
  INT16   bank_no_ebh[BANK_NUM_BITS] = { 0,0,0 };  // for later assemble no EBH bank
  INT16   bg_no_ebh[BG_NUM_BITS] = { 0,0 };
  INT16   xor_ebh[XaB_NUM_OF_BITS] = { 0,0,0,0 }; //xor_ebh
  UINT16  enhanced_ch_mode;                   // Enabled = 0; Disabled = 1;
  UINT16  bg0_on_bit_11;                      // Enabled = 0; Disabled = 1;
  UINT16  stacked_encoding;                   // Stacked mode channel hash bits
  UINT16  ch_l_map;                           // Virtual channel L mapping (0 - CH 0; 1 - CH 1)
  UINT8   config_arr[DRAM_ADDR_SIZE + 1];
  UINT8   enh_config_arr[ENHANCED_BITS_SIZE + 1];
  UINT8   config_case_num;
  UINT32  mad_dimm_l[2];                      // Make a MAD_DIMM array for easy access
  UINT32  mad_intra_chnl_l[2];                // Make a MAD_INTRA_CHNL array for easy access
  // shifters for bit select (from chnl_addr)according to the address decode map
  INT16   dimm_shifter[DIMM_NUM_BITS];
  INT16   rank_shifter[RANK_NUM_BITS];
  INT16   bg_shifter[BG_NUM_BITS];
  INT16   bank_shifter[BANK_NUM_BITS];
  INT16   row_shifter[ROW_NUM_BITS];
  INT16   col_shifter[COL_NUM_BITS];
  INT16   dimm_enhanced_shifter[DIMM_NUM_BITS];
  INT16   rank_enhanced_shifter[RANK_NUM_BITS];
  INT16   bg_enhanced_shifter[BG_NUM_BITS];
  INT16   bank_enhanced_shifter[BANK_NUM_BITS];
  INT16   col_enhanced_shifter[COL_NUM_BITS];
  BOOLEAN rerun_zone_1;
  BOOLEAN found_the_dimm_zone;
  BOOLEAN stacked_mode;                       // channel stacking enabled
  BOOLEAN stacked_mode_ch1;                   // Stacking channel 0 on top of channel 1
  BOOLEAN same_dimm_width_or_one_dimm;
  BOOLEAN dimm_and_rank_interleaving;         // modes for the selected channel
  BOOLEAN high_order_rank_interleave;
  BOOLEAN enhanced_interleave_mode;
  UINT32  ebh_enable;                     // Enhanced Bank Enable
  UINT32  XaB_enable;                     // xor XaB enable
  UINT32  XbB_enable;                     // xor XbB_lp4 enable

  ebh_enable = 0;                     // Enhanced Bank Enable
  XaB_enable = 0;                     // xor XaB enable
  XbB_enable = 0;                     // xor XbB_lp4 enable

  MrcCall->MrcSetMem ((UINT8 *)mad_dimm_l, sizeof (mad_dimm_l), 0);
  MrcCall->MrcSetMem ((UINT8 *)mad_intra_chnl_l, sizeof (mad_intra_chnl_l), 0);
  MrcCall->MrcSetMem ((UINT8 *)config_arr, sizeof (config_arr), 0);
  MrcCall->MrcSetMem ((UINT8 *)enh_config_arr, sizeof (enh_config_arr), 0);
  MrcCall->MrcSetMem ((UINT8 *)dimm_shifter, sizeof (dimm_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *)rank_shifter, sizeof (rank_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *)bg_shifter, sizeof (bg_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *)bank_shifter, sizeof (bank_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *)row_shifter, sizeof (row_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *)col_shifter, sizeof (col_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *)dimm_enhanced_shifter, sizeof (dimm_enhanced_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *)rank_enhanced_shifter, sizeof (rank_enhanced_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *)bg_enhanced_shifter, sizeof (bg_enhanced_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *)bank_enhanced_shifter, sizeof (bank_enhanced_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *)col_enhanced_shifter, sizeof (col_enhanced_shifter), 0);

  ddr_type = get_ddr_type (MAD_INTER_CHNL);
  //is_ddr4e = does_ddr4e (MAD_INTER_CHNL);
  enhanced_ch_mode = get_enhanced_ch_mode (MAD_INTER_CHNL);
  rerun_zone_1 = FALSE;
  found_the_dimm_zone = FALSE;
  dimm_line = 0;
  chan_line = 0;
  // zero out unused register bits
  tolud = TOLUD       & MC_ADDR_TOLUD_MASK;
  remap_base = REMAP_BASE  & MC_ADDR_REMAP_MASK;
  remap_limit = REMAP_LIMIT & MC_ADDR_REMAP_MASK;
  tom = TOM         & MC_ADDR_REMAP_MASK;

  // b4194941 - Assume lower bits of REMAP_LIMIT are all 1's.
  remap_limit |= MC_ADDR_REMAP_LIMIT_LOWER_BITS_MASK;


  mad_dimm_l[0] = MAD_DIMM_ch0;
  mad_dimm_l[1] = MAD_DIMM_ch1;
  mad_intra_chnl_l[0] = MAD_INTRA_CHNL_ch0;
  mad_intra_chnl_l[1] = MAD_INTRA_CHNL_ch1;

  // TOM is not directly available in a register. It will be computed by
  // finding the channel index of channel L, then adding the two DIMM
  // capacities of that channel together. Technically, this is only needed to
  // check that the system address is not beyond the amount of memory
  // available.
  ch_s_size = get_ch_s_size_as_cl (MrcCall, MAD_INTER_CHNL);
  ch_l_map = get_ch_l_map (MAD_INTER_CHNL);
  chan_l_mad_dimm = mad_dimm_l[ch_l_map];

  calculated_tom = cl_to_sys (MrcCall, get_dimm_l_size_as_cl (MrcCall, chan_l_mad_dimm));
  calculated_tom += cl_to_sys (MrcCall, get_dimm_s_size_as_cl (MrcCall, chan_l_mad_dimm));
  calculated_tom += cl_to_sys (MrcCall, ch_s_size);


  // determine if we are in stacked mode; and if so, what the stacked size is.
  stacked_mode = get_stacked_mode (MAD_INTER_CHNL);

  if (stacked_mode) {
    stacked_mode_ch1 = get_stacked_mode_ch1 (MAD_INTER_CHNL);
    stacked_encoding = get_stacked_encoding (MAD_INTER_CHNL);
  } else {
    stacked_mode_ch1 = FALSE;
    stacked_encoding = 0;
  }
  // determine if we are in EBH mode enable
  ebh_enable = get_ebh_mode (MCMNTS_SPARE);
  if (ebh_enable) {
    XaB_enable = ebh_enable & 1;
    XbB_enable = (ebh_enable >> 1) & 1;
  }
  // perform some checks on the inputs
  // illegal channel check
  if (chan & ~((UINT16)1)) {
    DEBUG ((DEBUG_ERROR, "Only two channels are supported. chan = %u\n", chan));
    return FALSE;
  }

  // check for too high of a DIMM index
  if (dimm & ~((UINT16)1)) {
    DEBUG ((DEBUG_ERROR, "There are only two DIMM slots per channel. DIMM index too high. dimm = %u\n", dimm));
    return FALSE;
  }

  // is it DIMM L or S? L=0, S=1
  dimm_select = (UINT64)(dimm ^ get_dimm_l_select (mad_intra_chnl_l[chan]));

  // get DIMM size
  dimm_size = dimm_select ? get_dimm_s_size_as_cl (MrcCall, mad_dimm_l[chan]) : get_dimm_l_size_as_cl (MrcCall, mad_dimm_l[chan]);

  // check if DIMM slot is populated
  if (dimm_size == 0) {
    DEBUG ((
      DEBUG_ERROR,
      "Specified DIMM slot was not populated\n chan = %u\n dimm = %u\n MAD_DIMM = 0x%08x\n",
      chan,
      dimm,
      mad_dimm_l[chan]
      ));
    return FALSE;
  }

  // check for too high of a rank index
  if (rank & ~((UINT16)3)) {
    DEBUG ((DEBUG_ERROR, "Rank index too high. rank = %u\n", rank));
    return FALSE;
  }

  // get some selected DIMM parameters
  dual_rank = dimm_select ? get_dimm_s_number_of_ranks (mad_dimm_l[chan]) : get_dimm_l_number_of_ranks (mad_dimm_l[chan]);
  dimm_width = dimm_select ? get_dimm_s_width (mad_dimm_l[chan]) : get_dimm_l_width (mad_dimm_l[chan]);
  //D8Gb = dimm_select ? get_dimm_s_8Gb (mad_dimm_l[chan]) : get_dimm_l_8Gb (mad_dimm_l[chan]);
  bg0_on_bit_11 = get_DLS_BG0_on_bit_11 (mad_dimm_l[chan]);
  dlnor = get_dimm_l_number_of_ranks (mad_dimm_l[chan]) - 1;
  nor_g2 = (dlnor % 2 == 1) & (get_dimm_s_size_as_cl (MrcCall, mad_dimm_l[chan]) != 0) ? 1 : 0;
  nor_1 = (dlnor == 0) & (get_dimm_s_size_as_cl (MrcCall, mad_dimm_l[chan]) == 0) ? 1 : 0;
  DEBUG ((DEBUG_INFO, "\nDEBUG:    EBH related parameters, dlnor = %0d,  nor_g2 = %0d, nor_1 = %0d", dlnor, nor_g2, nor_1));

  // check that rank exists on DIMM
  if (rank > dual_rank) {
    DEBUG ((
      DEBUG_ERROR,
      "Specified the second rank of a single-rank DIMM \n  chan = %u \n  dimm = %u \n  rank = %u \n  MAD_DIMM = 0x%08x\n",
      chan,
      dimm,
      rank,
      mad_dimm_l[chan]
      ));
    return FALSE;
  }

  // check for too high of a bg index
  if ((!ddr_type) && (dimm_width == 16)) { // DDR4 (DDR4==0 => FALSE) x16 => bg[1]=0
    if (bg & ~((UINT16)0x1)) {
      DEBUG ((DEBUG_ERROR, "Bank Group address too high. If DDR4x16 => bg[1]=0, bg = %u\n", bg));
      return FALSE;
    }
  }
  if (ddr_type) {
    if (bg & ~((UINT16)0x3)) {
      DEBUG ((DEBUG_ERROR, "Bank Group address too high. bg = %u\n", bg));
      return FALSE;
    }
  }
  // check for too high of a bank index
  if (bank & ~((UINT16)0x7)) {
    DEBUG ((DEBUG_ERROR, "Bank address too high. Has only 3 bank bits. bank = %u\n", bank));
    return FALSE;
  }

  // set a bit in a position that is one bit higher than the highest row bit
  //
  //  Most-Significant-Bits of Supported DRAM Chip Organizations
  //  DDR     Config  Size    Row     Col     Bg  Bank
  //  ---     ------  ------  ---     ---     --  ----
  //  DDR3    x8      2 Gb    14      9       0   1
  //  DDR3    x8      4 Gb    15      9       0   1   (8 GB DIMM, when dual rank) largest DDR3 DIMM when not using 8Gb
  //  DDR3    x8      8 Gb    15      10      0   1   (16 GB DIMM, when dual rank) largest DDR3 DIMM when using 8Gb
  //  DDR3    x16     2 Gb    13      9       0   1   (1 GB DIMM, when single rank) smallest DDR3 DIMM
  //  DDR3    x16     4 Gb    14      9       0   1
  //  DDR3    x16     8 Gb    15      9       0   1
  //  DDR4    x8      2 Gb    13      9       1   1   (2 GB DIMM, when single rank)
  //  DDR4    x8      4 Gb    14      9       1   1
  //  DDR4    x8      8 Gb    15      9       1   1
  //  DDR4    x8      16 Gb   16      9       1   1
  //  DDR4    x16     2 Gb    13      9       0   1   (1 GB DIMM, when single rank)
  //  DDR4    x16     4 Gb    14      9       0   1
  //  DDR4    x16     8 Gb    15      9       0   1
  //  DDR4    x16     16 Gb   16      9       0   1
  //  LPDDR3  x16     2 Gb    13      9       0   1   (1 GB DIMM, when single rank)
  //  LPDDR3  x16     4 Gb    13      10      0   1
  //  LPDDR3  x16     8 Gb    14      10      0   1
  //  LPDDR3  x32     2 Gb    13      8       0   1   (0.5 GB DIMM, when single rank)
  //  LPDDR3  x32     4 Gb    13      9       0   1
  //  LPDDR3  x32     8 Gb    14      9       0   1
  //
  // dimm size (GB) | dimm_size (cache-line)
  // ---------------+-----------------------
  //       32 GB    |     1<<29
  //       16 GB    |     1<<28
  //        8 GB    |     1<<27
  //        4 GB    |     1<<26
  //        2 GB    |     1<<25
  //        1 GB    |     1<<24
  //      0.5 GB    |     1<<23
  //

  num_col_bits = dimm_select ? get_dimm_s_num_col_bits (MrcCall, ddr_type, mad_dimm_l[chan], mad_intra_chnl_l[chan], enhanced_ch_mode) :
    get_dimm_l_num_col_bits (MrcCall, ddr_type, mad_dimm_l[chan], mad_intra_chnl_l[chan], enhanced_ch_mode);

  bit_above_row = MrcCall->MrcRightShift64 (dimm_size, num_col_bits - (UINT16)enhanced_ch_mode);
  bit_above_row = bit_above_row / ((dual_rank == 3) ? (dual_rank + 1) : dual_rank);

  // When DDR4 x8, Bg has two bits and the size can be twice bigger.
  bit_above_row = ((!ddr_type) && (dimm_width == 8)) ? MrcCall->MrcRightShift64 (bit_above_row, 1) : bit_above_row;

  // Check for unexpected high-order row bits
  if (row & ~(((UINT32)bit_above_row) - 1)) {
    DEBUG ((
      DEBUG_ERROR,
      "\nRow address too large for DIMM size.\nchan = %u\n  dimm = %u\n  row = 0x%04x\n  num_col_bits = 0x%04x\n  bit_above_row = 0x%llX\n  MAD_DIMM = 0x%08x\n",
      chan,
      dimm,
      row,
      num_col_bits,
      bit_above_row,
      mad_dimm_l[chan]
      ));
    return FALSE;
  }

  // check for unexpected high-order column bits
  if (col & ~((((UINT16)1) << num_col_bits) - 1)) {
    // check for the special command bits in the column address
    if ((col & (1 << 10)) && (ddr_type == 1) && (num_col_bits < 11)) { // col[10:10] - AP bit
      DEBUG ((DEBUG_ERROR, "Column bit 10 (the Auto-Precharge bit) was set. \ncol = 0x%03x\n", col));
    } else if (col & (1 << 12) && (num_col_bits < 13)) { // col[12:12] - BLOTH bit
      DEBUG ((DEBUG_ERROR, "Column bit 12 (the Burst Length On The Fly bit) was set. \ncol = 0x%03x\n", col));
    } else {
      DEBUG ((DEBUG_ERROR, "Column address is too large for the supported DRAM device sizes.\n  (Bits above col[%d:0] are unexpected)\n  col = 0x%03x\n", (num_col_bits - 1), col));
    }
    return FALSE;
  }

  //////////////////////////////////////////////////////////////////////////////////////
  // Done with checking. Now reverse decode the address.
  //////////////////////////////////////////////////////////////////////////////////////
  // determine if we are doing DIMM and Rank interleaving
  dimm_and_rank_interleaving = get_dimm_and_rank_intlv (mad_intra_chnl_l[chan]);

  // determine if we are doing high order rank interleave
  high_order_rank_interleave = get_high_order_intlv_mode (mad_intra_chnl_l[chan]);

  // determine if we are doing Enhanced Interleave Mode (EIM) (XOR dimm, rank, bg & bank bits)
  enhanced_interleave_mode = get_enhanced_intlv_mode (mad_intra_chnl_l[chan]);

  // Find the DIMM sizes on our selected channel. adjust to cache-line granularity
  dimm_l_size = get_dimm_l_size_as_cl (MrcCall, mad_dimm_l[chan]);
  dimm_s_size = get_dimm_s_size_as_cl (MrcCall, mad_dimm_l[chan]);

  // Find number of ranks and dimms in the selected channel
  chnl_num_of_dimms = (dimm_l_size) ? ((dimm_s_size) ? 2 : 1) : 0;
  chnl_num_of_ranks = ((dimm_l_size) ? get_dimm_l_number_of_ranks (mad_dimm_l[chan]) : 0) + ((dimm_s_size) ? get_dimm_s_number_of_ranks (mad_dimm_l[chan]) : 0);

  //  dimm_s_num_of_ranks = (dimm_s_size) ? get_dimm_s_number_of_ranks (mad_dimm_l[chan]) : 0;
    // Find the dimm width chnl configuration
  same_dimm_width_or_one_dimm = (dimm_s_size) ?
    ((get_dimm_l_width (mad_dimm_l[chan]) == get_dimm_s_width (mad_dimm_l[chan])) ? TRUE : FALSE) : TRUE;

    // get the configuration case
  config_case_num = get_the_config_case_num (
    MrcCall,
    ddr_type,
    enhanced_ch_mode,
    chnl_num_of_dimms,
    chnl_num_of_ranks,
    get_dimm_l_number_of_ranks (mad_dimm_l[chan]),
    get_dimm_l_8Gb (mad_dimm_l[chan]),
    get_dimm_l_width (mad_dimm_l[chan]),
    get_dimm_l_size_as_cl (MrcCall, mad_dimm_l[chan]),
    get_dimm_s_size_as_cl (MrcCall, mad_dimm_l[chan]),
    same_dimm_width_or_one_dimm,
    dimm_and_rank_interleaving,
    !rerun_zone_1);

  while (!found_the_dimm_zone) {
    config_case_num = get_the_config_case_num (
      MrcCall,
      ddr_type,
      enhanced_ch_mode,
      chnl_num_of_dimms,
      chnl_num_of_ranks,
      get_dimm_l_number_of_ranks (mad_dimm_l[chan]),
      get_dimm_l_8Gb (mad_dimm_l[chan]),
      get_dimm_l_width (mad_dimm_l[chan]),
      get_dimm_l_size_as_cl (MrcCall, mad_dimm_l[chan]),
      get_dimm_s_size_as_cl (MrcCall, mad_dimm_l[chan]),
      same_dimm_width_or_one_dimm,
      dimm_and_rank_interleaving,
      !rerun_zone_1
    );

    // get the exact configuration case
    config_case_num_int_for_switch = config_case_num;
    switch (config_case_num_int_for_switch) {
    case 24: config_case_num = (dual_rank == 2) ? 24 : 25; break;
    case 30: config_case_num = (dual_rank == 2) ? 30 : 31; break;
    case 32: config_case_num = (dimm_width == 8) ? 32 : 33; break;
    case 34: config_case_num = (dimm_width == 8) ? 34 : 35; break;
    case 36: config_case_num = (dimm_width == 8) ? 36 : 37; break;
    case 38: config_case_num = (dimm_width == 8) ? 39 : 38; break;
    case 40: config_case_num = (dimm_width == 8) ? 40 : 41; break;
    case 95: config_case_num = (dual_rank == 2) ? 95 : 96; break;
    case 101: config_case_num = (dual_rank == 2) ? 101 : 102; break;
    case 103: config_case_num = (dimm_width == 8) ? 103 : 104; break;
    case 105: config_case_num = (dimm_width == 8) ? 105 : 106; break;
    case 107: config_case_num = (dimm_width == 8) ? 107 : 108; break;
    case 109: config_case_num = (dimm_width == 8) ? 109 : 110; break;
    case 111: config_case_num = (dimm_width == 8) ? 111 : 112; break;
    }


    if (rerun_zone_1) {
      config_case_num_int_for_switch = config_case_num;
      switch (config_case_num_int_for_switch) {
      case 24: config_case_num = (dual_rank == 2) ? 22 : 20; break;
      case 95: config_case_num = (dual_rank == 2) ? 93 : 91; break;
      case 30: config_case_num = (dual_rank == 2) ? 28 : 26; break;
      case 101: config_case_num = (dual_rank == 2) ? 99 : 97; break;
      }
    }


    addr_decode_map_parse (MrcCall, config_arr, config_case_num, TRUE);
    if (enhanced_interleave_mode) {
      enhanced_mode_map_parse (MrcCall, enh_config_arr, config_case_num, TRUE);
    }

    converter_step = 1;
    for (i = 0; i < DIMM_NUM_BITS; i++) {
      dimm_shifter[(DIMM_NUM_BITS - 1) - i] = (config_arr[i + converter_step] - 6);
      dimm_enhanced_shifter[(DIMM_NUM_BITS - 1) - i] = (enh_config_arr[i + converter_step] - 6);
    }
    converter_step += DIMM_NUM_BITS;
    for (i = 0; i < RANK_NUM_BITS; i++) {
      rank_shifter[(RANK_NUM_BITS - 1) - i] = (config_arr[i + converter_step] - 6);
      rank_enhanced_shifter[(RANK_NUM_BITS - 1) - i] = (enh_config_arr[i + converter_step] - 6);
    }
    converter_step += RANK_NUM_BITS;
    for (i = 0; i < BG_NUM_BITS; i++) {
      bg_shifter[(BG_NUM_BITS - 1) - i] = (config_arr[i + converter_step] - 6);
      bg_enhanced_shifter[(BG_NUM_BITS - 1) - i] = (enh_config_arr[i + converter_step] - 6);
    }
    converter_step += BG_NUM_BITS;
    for (i = 0; i < BANK_NUM_BITS; i++) {
      bank_shifter[(BANK_NUM_BITS - 1) - i] = (config_arr[i + converter_step] - 6);
      bank_enhanced_shifter[(BANK_NUM_BITS - 1) - i] = (enh_config_arr[i + converter_step] - 6);
    }
    converter_step += BANK_NUM_BITS;
    for (i = 0; i < ROW_NUM_BITS; i++) {
      row_shifter[(ROW_NUM_BITS - 1) - i] = (config_arr[i + converter_step] - 6);
    }
    converter_step += ROW_NUM_BITS;
    for (i = 0; i < COL_NUM_BITS; i++) {
      col_shifter[(COL_NUM_BITS - 1) - i] = (config_arr[i + converter_step] - 6);
      col_enhanced_shifter[i] = -6;
    }
    col_enhanced_shifter[10] = (enh_config_arr[8] - 6); // enhanced mode for column[10:10]
    // Take care of performance ECO (1303982985)
    if ((ddr_type == 0) && bg0_on_bit_11) {
      i = col_shifter[7];
      col_shifter[7] = bg_shifter[0];
      bg_shifter[0] = i;
      i = col_enhanced_shifter[7];
      col_enhanced_shifter[7] = bg_enhanced_shifter[0];
      bg_enhanced_shifter[0] = i;
    }

    // start building the DIMM Address Space (as a cache-line address)
    // build the rank, bg, bank, and row parts of the DIMM space address

    // the same for rank interleave on/off
    dimm_line = 0;

    // put in the col part of the address:

    for (i = 0; i < (COL_NUM_BITS - 1); i++) {
      if (col_shifter[i] != -6) {
        if (col_shifter[i] < 0) {
          col_shifter[i] += 6;
          *p_sys_addr = *p_sys_addr | (UINT16)(((col >> i) & 1) << col_shifter[i]);
        } else {
          if (enhanced_interleave_mode && (col_enhanced_shifter[i] != -6)) {
            dimm_line = dimm_line | (UINT16)MrcCall->MrcLeftShift64 ((((col >> i) & 1) ^ (MrcCall->MrcRightShift64 (dimm_line, col_enhanced_shifter[i]) & 1)), col_shifter[i]);
          } else
          {
            dimm_line = dimm_line | (UINT16)(((col >> i) & 1) << col_shifter[i]);
          }
        }
      }
    } //for COL_NUM_BITS

    // calculating col[7] after all col bits are builded
    if (ddr_type == 0 && bg0_on_bit_11) {
      // Take care of performance ECO (1303982985)

      if (col_shifter[7] == -6)
      {
      } else if (col_shifter[7] < 0)
      {
        col_shifter[7] += 6;
        *p_sys_addr = *p_sys_addr | (UINT16)(((col >> 7) & 1) << col_shifter[7]);
      } else
      {
        if (enhanced_interleave_mode && (col_enhanced_shifter[7] != -6))
        {
          dimm_line = dimm_line & ((0xFFFFFFFFFFFFFFFFULL) ^ (UINT16)(1 << col_shifter[7])); // putting 0 at the 11 bit
          dimm_line = dimm_line | (UINT16)((((col >> 7) & 1) ^ (UINT16)(MrcCall->MrcRightShift64 (dimm_line, col_enhanced_shifter[7]) & 1)) << col_shifter[7]);
        } else
        {
          dimm_line = dimm_line | (UINT16)(((col >> 7) & 1) << col_shifter[7]);
        }
      }
    }
    // put in the row part of the address
    for (i = 0; i < ROW_NUM_BITS; i++) {
      if (row_shifter[i] != -6) {
        dimm_line = dimm_line | (UINT64)(MrcCall->MrcLeftShift64 ((MrcCall->MrcRightShift64 (row, i) & 1), row_shifter[i]));
      }
    }

    if ((dimm_line < (MrcCall->MrcLeftShift64 (dimm_s_size, 1))) && (rerun_zone_1 == FALSE)) { // Range 0 if DIMM address is less than DIMM S's size.
      // insert dimm_select bit
      for (i = 0; i < DIMM_NUM_BITS; i++) {
        if (dimm_shifter[i] != -6) {
          if (enhanced_interleave_mode){
            if (dimm_enhanced_shifter[i] != -6) {
             dimm_line = dimm_line | (UINT64)((MrcCall->MrcRightShift64 (dimm_select, i) & 1) ^ (MrcCall->MrcRightShift64 (dimm_line, dimm_enhanced_shifter[i]) & 1));
            }
            else {
             dimm_line = dimm_line | (UINT64)((MrcCall->MrcRightShift64 (dimm_select, i) & 1));
            }
          } else {
            dimm_line = dimm_line | (UINT64)(MrcCall->MrcLeftShift64 (MrcCall->MrcRightShift64 (dimm_select, i) & 1, dimm_shifter[i]));
          }
        }
      }
    }

    // Iterating over the dimm line -
    //    1) Build the channel line (but not the BG and BANK) - EBH only
    //    2) Use the channel line in order to build the BG and BANK - EBH only

    dimm_line_c = dimm_line;

    for (ebh_loop = 0; ebh_loop < 2; ebh_loop++)
    {
      dimm_line = dimm_line_c;
      // put in the bank part of the address
      for (bankBit = 0; bankBit < BANK_NUM_BITS; bankBit++) {
        bank_no_ebh[bankBit] = (bank >> bankBit) & 1;
        if (bank_shifter[bankBit] != -6) {
          if (enhanced_interleave_mode) {


            // EBH encoding
            if (ebh_enable && (ebh_loop == 1)) {
              DEBUG ((DEBUG_INFO, "\nDEBUG:   EBH Encoding"));
              if (XaB_enable) {
                // In DDR4 x16 EBH2 xor with bg1 and not bank2, in x8 it has no xor EBH2
                if ((ddr_type == 0) && (bankBit == BANK_NUM_BITS - 1)) continue;
                for (xorBit = 0; xorBit < XaB_NUM_OF_BITS; xorBit++) {
                  xor_ebh[xorBit] = (chan_line >> (XaB[bankBit][xorBit])) & 1;
                  bank_no_ebh[bankBit] = bank_no_ebh[bankBit] ^ xor_ebh[xorBit];

                }
              }
              if (XbB_enable) {
                if (ddr_type == 3) { //LP4
                  switch (bankBit)
                  {
                  case 0:
                    xor_ebh[0] = (chan_line >> (XbB_lp4[bankBit][0])) & 1;
                    xor_ebh[1] = (chan_line >> (XbB_lp4[bankBit][1])) & (dlnor == 0 ? 1 : 0);
                    bank_no_ebh[bankBit] = bank_no_ebh[bankBit] ^ xor_ebh[0] ^ xor_ebh[1];
                    break;
                  case 1:
                    xor_ebh[0] = (chan_line >> (XbB_lp4[bankBit][0])) & (dlnor < 2 ? 1 : 0);
                    xor_ebh[1] = (chan_line >> (XbB_lp4[bankBit][1])) & (dlnor == 0 ? 1 : 0);
                    bank_no_ebh[bankBit] = bank_no_ebh[bankBit] ^ xor_ebh[0] ^ xor_ebh[1];
                    break;
                  case 2:
                    xor_ebh[0] = (chan_line >> (XbB_lp4[bankBit][0])) & (dlnor < 2 ? 1 : 0);
                    bank_no_ebh[bankBit] = bank_no_ebh[bankBit] ^ xor_ebh[0];
                    break;
                  }
                } else if (ddr_type == 0) { //DDR4
                  switch (bankBit)
                  {
                  case 0:
                    xor_ebh[0] = (chan_line >> XbB_ddr4[dimm_width == 8 ? 0 : 1][bankBit][0]) & (nor_g2 == 0) ? 1 : 0;
                    xor_ebh[1] = (chan_line >> XbB_ddr4[dimm_width == 8 ? 0 : 1][bankBit][1]) & nor_1 & (XbB_ddr4[dimm_width == 8 ? 0 : 1][bankBit][1] != 0);
                    xor_ebh[2] = (chan_line >> XbB_ddr4[dimm_width == 8 ? 0 : 1][bankBit][2]) & (XbB_ddr4[dimm_width == 8 ? 0 : 1][bankBit][2] != 0);
                    xor_ebh[3] = (chan_line >> XbB_ddr4[dimm_width == 8 ? 0 : 1][bankBit][3]) & (XbB_ddr4[dimm_width == 8 ? 0 : 1][bankBit][3] != 0);
                    bank_no_ebh[bankBit] = bank_no_ebh[bankBit] ^ xor_ebh[0] ^ xor_ebh[1] ^ xor_ebh[2] ^ xor_ebh[3];
                    break;
                  case 1:
                    xor_ebh[0] = (chan_line >> XbB_ddr4[dimm_width == 8 ? 0 : 1][bankBit][0]) & (nor_g2 == 0) ? 1 : 0;
                    xor_ebh[1] = (chan_line >> XbB_ddr4[dimm_width == 8 ? 0 : 1][bankBit][1]) & nor_1 & (XbB_ddr4[dimm_width == 8 ? 0 : 1][bankBit][1] != 0);
                    xor_ebh[2] = (chan_line >> XbB_ddr4[dimm_width == 8 ? 0 : 1][bankBit][2]) & (XbB_ddr4[dimm_width == 8 ? 0 : 1][bankBit][2] != 0);
                    xor_ebh[3] = (chan_line >> XbB_ddr4[dimm_width == 8 ? 0 : 1][bankBit][3]) & (XbB_ddr4[dimm_width == 8 ? 0 : 1][bankBit][3] != 0);
                    bank_no_ebh[bankBit] = bank_no_ebh[bankBit] ^ xor_ebh[0] ^ xor_ebh[1] ^ xor_ebh[2] ^ xor_ebh[3];
                    break;
                  }
                }
              }
            }
            dimm_line = dimm_line | (UINT16)(MrcCall->MrcLeftShift64 (((bank_no_ebh[bankBit] & 1) ^ (MrcCall->MrcRightShift64 (dimm_line, bank_enhanced_shifter[bankBit]) & 1)), bank_shifter[bankBit]));
          } else
          {
            dimm_line = dimm_line | (UINT16)(MrcCall->MrcLeftShift64 ((bank_no_ebh[bankBit] & 1), bank_shifter[bankBit]));
          }
        }
      }//for bankBit < BANK_NUM_BITS

      // put in the bg part of the address
      if (ddr_type == 0) {
        for (i = 0; i < BG_NUM_BITS; i++)
        {
          if (bg_shifter[i] == -6)
          {
          } else if (enhanced_interleave_mode)
          {
            bg_no_ebh[i] = (bg >> i) & 1;
            if (ebh_enable && (dimm_width == 8) && (ddr_type == 0) && (i == 1) && (ebh_loop == 1)) { // EBH on bg1 in DDR4
              if (XaB_enable) {
                for (xorBit = 0; xorBit < XaB_NUM_OF_BITS; xorBit++) {
                  if (XaB[2][xorBit] == 0) continue;
                  xor_ebh[xorBit] = ((chan_line >> XaB[2][xorBit]) & 1);
                  bg_no_ebh[i] = bg_no_ebh[i] ^ xor_ebh[xorBit];

                }
              }
              if (XbB_enable) {
                xor_ebh[0] = (chan_line >> XbB_ddr4[dimm_width == 8 ? 0 : 1][2][0]) & nor_1;
                bg_no_ebh[i] = bg_no_ebh[i] ^ xor_ebh[0];
              }
            }
            dimm_line = dimm_line | (UINT16)(MrcCall->MrcLeftShift64 (bg_no_ebh[i] ^ (MrcCall->MrcRightShift64 (dimm_line, bg_enhanced_shifter[i]) & 1), bg_shifter[i]));
          } else {
            dimm_line = dimm_line | (UINT16)(MrcCall->MrcLeftShift64 (MrcCall->MrcRightShift64 (bg, i) & 1, bg_shifter[i]));
          }
        }
      }

      // put in the rank part of the address
      if (!dimm_and_rank_interleaving) {
        // support in legacy mode - interleave in dimm with 2 ranks
        if ((dual_rank == 2) & (rank == 1)) {
          dimm_line = dimm_line | MrcCall->MrcRightShift64 (dimm_size, 1);
        } else
        { // support in ERM mode
          rank_size = dimm_size / dual_rank;
          dimm_line = rank * rank_size + dimm_line;
        }
      } else
      {
        for (i = 0; i < RANK_NUM_BITS; i++)
        {
          if (rank_shifter[i] == -6)
          {
          } else if (enhanced_interleave_mode)
          {
            dimm_line = dimm_line | (UINT16)(MrcCall->MrcLeftShift64 (((MrcCall->MrcRightShift64 (rank, i) & 1) ^ (MrcCall->MrcRightShift64 (dimm_line, rank_enhanced_shifter[i]) & 1)), rank_shifter[i]));
          } else
          {
            dimm_line = dimm_line | (UINT16)(MrcCall->MrcLeftShift64 (MrcCall->MrcRightShift64 (rank, i) & 1, rank_shifter[i]));
          }

          // In case of ERM we have to put the high bit of the rank in bg[1]
          if (dual_rank > 2) {
            if (bg_shifter[i + 1] == -6)
            {
            } else if (enhanced_interleave_mode)
            {
              dimm_line = dimm_line | (UINT16)(((MrcCall->MrcRightShift64 (rank, (i + 1)) & 1) ^ MrcCall->MrcLeftShift64 (MrcCall->MrcRightShift64 (dimm_line, bg_enhanced_shifter[i + 1]) & 1, bg_shifter[i + 1])));
            } else
            {
              dimm_line = dimm_line | (UINT16)(MrcCall->MrcLeftShift64 (MrcCall->MrcRightShift64 (rank, (i + 1) & 1), bg_shifter[i + 1]));
            }
          }
        }
      }


      // put in the col[10:10] part of the address:
      for (i = (COL_NUM_BITS - 1); i < COL_NUM_BITS; i++)
      {
        if (col_shifter[i] != -6)
        {
          if (col_shifter[i] < 0)
          {
            col_shifter[i] += 6;
            *p_sys_addr = *p_sys_addr | (UINT16)(MrcCall->MrcRightShift64 (MrcCall->MrcRightShift64 (col, i) & 1, col_shifter[i]));
          } else
          {
            if (enhanced_interleave_mode && (col_enhanced_shifter[i] != -6))
            {
              dimm_line = dimm_line | (UINT16)((MrcCall->MrcRightShift64 (col, i) & 1) ^ MrcCall->MrcLeftShift64 (MrcCall->MrcRightShift64 (dimm_line, col_enhanced_shifter[i]) & 1, col_shifter[i]));
            } else {
              dimm_line = dimm_line | (UINT16)(MrcCall->MrcLeftShift64 (MrcCall->MrcRightShift64 (col, i) & 1, col_shifter[i]));
            }
          }
        }
      }



// Support in ERM 3 ranks
// 1 sub channel 3 ranks:
// Rank_sel_h,Rnk_sel = Modulus3(Zone_address[33:14])
// Row[16:0], BANK[2] = Div3(Zone_address[33:14])
// 2 sub channel 3 rank:
// Rnk_sel_h,Rnk_sel = Modulus3(Zone_address[34:15])
// Row[16:0], BANK[2] = Div3(Zone_address[34:15])
      if (dual_rank == 3) {
        dimm_line = dimm_line & ~MrcCall->MrcLeftShift64 (0xFFFFFFFFFFFFFFFFULL, 8 + (chnl_num_of_dimms == 2));
        dimm_line = dimm_line | ((3 * ((row << 1) | ((bank >> 2) & 1)) + ((bg & 2) | (rank & 1))) << (8 + (chnl_num_of_dimms == 2)));
      }

      //
      // DIMM address to channel address
      //

      // Find the DIMM sizes on our selected channel. adjust to cache-line granularity
      dimm_l_size = get_dimm_l_size_as_cl (MrcCall, mad_dimm_l[chan]);
      dimm_s_size = get_dimm_s_size_as_cl (MrcCall, mad_dimm_l[chan]);



      // Both dimm_and_rank_interleaving and high_order_rank_interleave cause DIMM interleaving.
      //
      if (dimm_and_rank_interleaving || high_order_rank_interleave) {
        // DIMM and Rank interleaving (or HORI) enabled
        //
        //  +------16 GB------+
        //  |                 |
        //  .                 .
        //  .                 .
        //  .                 .
        //  |                 |
        //  |  unmapped       |
        //  |  space above    |
        //  |  channel        |
        //  |  capacity       |
        //  |                 |
        //  +--Range 1 Limit--+  <-- dimm_l_size + dimm_s_size
        //  |                 |
        //  |  No Interleave  |
        //  |     DIMM L      |
        //  |                 |
        //  +--Range 0 Limit--+  <-- dimm_s_size * 2
        //  |                 |
        //  | 2-Way Interleave|
        //  |   DIMMs L & S   |
        //  |                 |
        //  +-------0x0-------+
        //
        if ((dimm_line < MrcCall->MrcRightShift64 (dimm_s_size, 1)) && (rerun_zone_1 == FALSE)) { // Range 0 if DIMM address is less than DIMM S's size.
          // Determine if the channel hash feature is being used
          if (CHANNEL_EHASH & MC_ADDR_CHAN_HASH_ENABLE_MASK) { // test enable bit
            dimm_line = MrcCall->MrcRightShift64 (dimm_line, 1);
            hash_lsb_mask_bit = get_ch_hash_lsb_mask_bit (CHANNEL_EHASH);
            hash_mask = get_ch_hash_mask (CHANNEL_EHASH);

            // placing the chan_select bit in hash_lsb_mask_bit
            chan_line = MrcCall->MrcLeftShift64 (dimm_line & MrcCall->MrcLeftShift64 (0xFFFFFFFFFFFFFFFFULL, hash_lsb_mask_bit), 1);
            chan_line = chan_line | (dimm_line & ~(MrcCall->MrcLeftShift64 (0xFFFFFFFFFFFFFFFFULL, hash_lsb_mask_bit))); // getting the highest and the lowest bits

            // Get the bits used to produce chan_select, sans the bit athash_lsb_mask_bit
            hash_line = ((UINT16)chan_line) & hash_mask;

            // Recreate the value of the bit at hash_lsb_mask_bit by doint the hash
            // XORs.
            hash_bit = 0;
            for (i = 0; i < MC_ADDR_CHANNEL_HASH_MASK_SIZE; i++) {
              hash_bit = hash_bit ^ (hash_line >> i);
            }
            hash_bit = hash_bit & 1;

            // Recreate the missing bit by XORing the chan_select (the result of
            // the forward decode).
            // (If X = A ^ B, then A = X ^ B)
            //
            hash_bit = hash_bit ^ (UINT16)dimm_select;

            // put the missing bit back into the address
            chan_line = chan_line | (hash_bit << hash_lsb_mask_bit);
          } else {
            // insert dimm_select bit and convert to chan_line:
            for (i = 0; i < DIMM_NUM_BITS; i++) {
              if (dimm_shifter[i] == -6) {
                chan_line = dimm_line;
              } else {
                chan_line = dimm_line | (UINT64)enhanced_interleave_mode ?
                  (MrcCall->MrcRightShift64 (dimm_select, i) & 1) ^ (MrcCall->MrcRightShift64 (dimm_line, dimm_enhanced_shifter[i]) & 1)
                  : MrcCall->MrcLeftShift64 ((MrcCall->MrcRightShift64 (dimm_select, i) & 1), dimm_shifter[i]);
              }
            }
          }
          // Avoid the case in which the found_the_dimm_zone turns true in the ebh second run
          if ((ebh_loop == 1) || (ebh_enable == 0))
            found_the_dimm_zone = TRUE;
        } else
        { // not Range 0, must be Range 1, no interleave

          // Channel address is DIMM L address with DIMM S's contribution from Range 0 added in
          chan_line = dimm_line + dimm_s_size;
  // Avoid the case in which the found_the_dimm_zone turns true in the ebh second run
          if ((ebh_loop == 1) || (ebh_enable == 0))
          {
            if (rerun_zone_1 == FALSE) {
              rerun_zone_1 = TRUE;
            } else
            {
              found_the_dimm_zone = TRUE;
            }
          }
        }
      } else { // no DIMM and Rank interleaving (nor HORI).
        //  +------16 GB------+
        //  |                 |
        //  .                 .
        //  .                 .
        //  .                 .
        //  |                 |
        //  |  unmapped       |
        //  |  space above    |
        //  |  channel        |
        //  |  capacity       |
        //  |                 |
        //  +--Range 1 Limit--+  <-- dimm_l_size + dimm_s_size
        //  |                 |
        //  |  No Interleave  |
        //  |     DIMM S      |
        //  |                 |
        //  +--Range 0 Limit--+  <-- dimm_l_size
        //  |                 |
        //  |  No Interleave  |
        //  |     DIMM L      |
        //  |                 |
        //  +-------0x0-------+
        //
        chan_line = dimm_line;
        if (dimm_select) { // DIMM is S
          chan_line += dimm_l_size;
        }
        // Avoid the case in which the found_the_dimm_zone turns true in the ebh second run
        if ((ebh_loop == 1) || (ebh_enable == 0))
          found_the_dimm_zone = TRUE;
      }

      if (ebh_enable == 0) break;
      found_the_dimm_zone = TRUE;
    } // EBH loop
  } // while (!found_the_dimm_zone)

  //
  // Channel address to remaped system address
  //

  // map physical channel to L or S
  //
  chan_select = physical_to_logical_chan (MAD_INTER_CHNL, chan);

  // Stacked channel mode
  //
  //  +------0.5 TB------+
  //  |                  |
  //  .                  .
  //  .                  .
  //  .                  .
  //  |                  |
  //  |  unmapped        |
  //  |  space above     |
  //  |  DRAM            |
  //  |                  |
  //  +--2 * Stack size--+  <-- Top Of Memory = L + S
  //  |                  |
  //  |                  |
  //  |                  |
  //  |   Channel S      |
  //  |                  |
  //  |                  |
  //  +--- Stack size ---+  <-- Stack Size = Channel size (channels L and S must be equal)
  //  |                  |
  //  |                  |
  //  |                  |
  //  |   Channel L      |
  //  |                  |
  //  |                  |
  //  +--------0x0-------+
  //
  if (stacked_mode) {
    remap_line = chan_line;

    if (stacked_mode_ch1) {
      chan_select ^= 1;
    }

    // In stacked mode, the channel is chosen based on the bit corresponding to the
    // size of the stacked register.  Bit-wise 'OR' in the channel selection bit into that
    // position.
    //
    remap_line |= (UINT64)(chan_select) << (24 + stacked_encoding);
  } else if (chan_line < (ch_s_size)) {// Zone 0

    // Determine which range/zone the remapped system address falls into
    //
    //  +-----0.5 TB-----+
    //  |                |
    //  .                .
    //  .                .
    //  .                .
    //  |                |
    //  |  unmapped      |
    //  |  space above   |
    //  |  DRAM          |
    //  |                |
    //  +--Zone 1 Limit--+  <-- Top Of Memory = L + S
    //  |                |
    //  |  No Interleave |
    //  |    Channel L   |
    //  |                |
    //  +--Zone 0 Limit--+  <-- 2 * S
    //  |                |
    //  |  2-Way Intlv   |
    //  | Channels L & S |
    //  |                |
    //  |                |
    //  |                |
    //  |                |
    //  |                |
    //  |                |
    //  +-------0x0------+
    //

    // Determine if the channel hash feature is being used
    if (CHANNEL_HASH & MC_ADDR_CHAN_HASH_ENABLE_MASK) { // test enable bit
      hash_lsb_mask_bit = get_ch_hash_lsb_mask_bit (CHANNEL_HASH);
      hash_mask = get_ch_hash_mask (CHANNEL_HASH);

      // placing the chan_select bit in hash_lsb_mask_bit
      remap_line = MrcCall->MrcLeftShift64 (chan_line & MrcCall->MrcLeftShift64 (0xFFFFFFFFFFFFFFFFULL, hash_lsb_mask_bit), 1); // getting the highest bit
      remap_line = remap_line | (chan_line & ~(MrcCall->MrcLeftShift64 (0xFFFFFFFFFFFFFFFFULL, hash_lsb_mask_bit))); // getting the highest bit

      // Get the bits used to produce chan_select, sans the bit athash_lsb_mask_bit
      hash_line = ((UINT16)remap_line) & hash_mask;

      // Recreate the value of the bit at hash_lsb_mask_bit by doint the hash
      // XORs.
      hash_bit = 0;
      for (i = 0; i < MC_ADDR_CHANNEL_HASH_MASK_SIZE; i++) {
        hash_bit = hash_bit ^ (hash_line >> i);
      }
      hash_bit = hash_bit & 1;

      // Recreate the missing bit by XORing the chan_select (the result of
      // the forward decode).
      // (If X = A ^ B, then A = X ^ B)
      //
      hash_bit = hash_bit ^ chan_select;

      // put the missing bit back into the address
      remap_line = remap_line | (hash_bit << hash_lsb_mask_bit);
    } else {
      // Without the hash, sys_addr[6:6] determines the channel
      remap_line = MrcCall->MrcLeftShift64 (chan_line, 1);
      remap_line |= ((UINT64)chan_select);
    }
  } else { // Zone 1
    remap_line = chan_line + (ch_s_size);
  }


  // work on full address instead of cache-line address;
  remap_addr = MrcCall->MrcLeftShift64 (remap_line, 6);


  // Determine if the address is under the remap zone and therefore must be a
  // TCM.  remap_line can't be at or above TOM (Top Of Memory), so no need to
  // check that.  Simply check if the remap_line is between the base and
  // limit.
  //
  *p_is_tcm = (remap_addr <= remap_limit) && (remap_addr >= remap_base); // b4194941 - REMAP_LIMIT is now inclusive

  //
  // reverse decode the remap region
  //
  *p_sys_addr = remap_addr; // if the remap doesn't apply system address is remap address

  if (!(*p_is_tcm) &&             // remap doesn't apply if address was under remap zone.
    (remap_limit > remap_base))  // remap doesn't apply if remap zone disabled
  {
    top_of_remaped_mem = (UINT64)tolud;
    top_of_remaped_mem += remap_limit;
    top_of_remaped_mem -= remap_base;
    if ((remap_addr <= top_of_remaped_mem) && (remap_addr >= ((UINT64)tolud))) { // b4194941 - REMAP_LIMIT is now inclusive
      // remap applies. move the address to the remap zone
      *p_sys_addr -= ((UINT64)tolud);
      *p_sys_addr += remap_base;
    }
  }



  // restore cache-line chunk order
  if (enhanced_ch_mode) {
    *p_sys_addr = *p_sys_addr | (MrcCall->MrcLeftShift64 ((UINT64)col, 2) & 0x3FULL);
  } else {
    *p_sys_addr = *p_sys_addr | (MrcCall->MrcLeftShift64 ((UINT64)col, 3) & 0x3FULL);
  }
  if (tom < remap_addr) {
    DEBUG ((DEBUG_ERROR, "\nSystem address did not map to DRAM memory. It was above TOM after remap.\n"));
    return FALSE;
  }
  return TRUE;
}

/**
  Address decode function
  Converts memory address to DRAM address

  @param[in]      MemoryAddress  - The 39-bit memory address to decode.
  @param[out]     DramAddress    - The DRAM address struct that the memory address decodes to.

  @retval Returns EFI_SUCCESS if successful, EFI_UNSUPPORTED otherwise.
**/
EFI_STATUS
(EFIAPI MrcMemoryAddressDecode) (
  IN  UINT64           MemoryAddress,
  OUT MRC_DRAM_ADDRESS *DramAddress
  )
{
  MRC_ADDR_FUNCTION CallTable;
  MRC_ADDR_FUNCTION *MrcCall;
  EFI_STATUS    Status;
  UINT32        MchBarBaseAddress;
  UINT32        PciEBaseAddress;
  UINT32        Offset;
  UINT16        TempChannel;
  UINT16        TempDimm;
  UINT16        TempRank;
  UINT16        TempBankGroup;
  UINT16        TempBank;
  UINT32        TempRow;
  UINT16        TempColumn;
  UINT64        Tom;
  UINT64        RemapBase;
  UINT64        RemapLimit;
  UINT32        Tolud;
  UINT32        ChannelHash;
  UINT32        ChannelEHash;
  UINT32        MadInterChannel;
  UINT32        MadIntraCh0;
  UINT32        MadIntraCh1;
  UINT32        MadDimmCh0;
  UINT32        MadDimmCh1;
  BOOLEAN       IsTcm;

  MrcCall = &CallTable;
  Status  = EFI_UNSUPPORTED;

  //
  // Set function pointers
  //
#ifdef MRC_MINIBIOS_BUILD
  MrcCall->MrcIoRead32     = (MRC_IO_READ_32) (&MrcOemInPort32);
  MrcCall->MrcIoWrite32    = (MRC_IO_WRITE_32) (&MrcOemOutPort32);
  MrcCall->MrcMmioRead32   = (MRC_MMIO_READ_32) (&MrcOemMmioRead32);
  MrcCall->MrcMmioRead64   = (MRC_MMIO_READ_64) (&SaMmioRead64);
  MrcCall->MrcCopyMem      = (MRC_MEMORY_COPY) (&MrcOemMemoryCpy);
#else
  MrcCall->MrcIoRead32     = (MRC_IO_READ_32) (&IoRead32);
  MrcCall->MrcIoWrite32    = (MRC_IO_WRITE_32) (&IoWrite32);
  MrcCall->MrcMmioRead32   = (MRC_MMIO_READ_32) (&MmioRead32);
  MrcCall->MrcMmioRead64   = (MRC_MMIO_READ_64) (&MmioRead64);
  MrcCall->MrcCopyMem      = (MRC_MEMORY_COPY) (&CopyMem);
#endif // MRC_MINIBIOS_BUILD
  MrcCall->MrcSetMem       = (MRC_MEMORY_SET_BYTE) (&SetMem);
  MrcCall->MrcMultU64x32   = (MRC_MULT_U64_U32) (&MultU64x32);
  MrcCall->MrcDivU64x64    = (MRC_DIV_U64_U64) (&DivU64x64Remainder);
  MrcCall->MrcLeftShift64  = (MRC_LEFT_SHIFT_64) (&LShiftU64);
  MrcCall->MrcRightShift64 = (MRC_RIGHT_SHIFT_64) (&RShiftU64);

  //
  // Check that MCHBAR is programmed
  //
  MrcCall->MrcIoWrite32 (0xCF8, MRC_BIT31 | R_SA_MCHBAR);
  MchBarBaseAddress = MrcCall->MrcIoRead32 (0xCFC);

  if ((MchBarBaseAddress & MRC_BIT0) == MRC_BIT0) {
    MchBarBaseAddress &= (~MRC_BIT0);
  } else {
    return Status;
  }

  //
  // Check that PCIEXBAR is programmed
  //
  MrcCall->MrcIoWrite32 (0xCF8, MRC_BIT31 | R_SA_PCIEXBAR);
  PciEBaseAddress = MrcCall->MrcIoRead32 (0xCFC);

  if ((PciEBaseAddress & MRC_BIT0) == MRC_BIT0) {
    PciEBaseAddress &= ~(MRC_BIT2 | MRC_BIT1 | MRC_BIT0);
  } else {
    return Status;
  }

  //
  // Collect address configuration from registers
  //
  Offset               = PciEBaseAddress + R_SA_TOLUD;
  Tolud                = MrcCall->MrcMmioRead32 (Offset);
  Offset               = PciEBaseAddress + R_SA_TOM;
  Tom                  = MrcCall->MrcMmioRead64 (Offset);
  RemapBase            = MrcCall->MrcMmioRead64 (MchBarBaseAddress + R_SA_MCHBAR_REMAPBASE_OFFSET);
  RemapLimit           = MrcCall->MrcMmioRead64 (MchBarBaseAddress + R_SA_MCHBAR_REMAPLIMIT_OFFSET);
  ChannelHash          = MrcCall->MrcMmioRead32 (MchBarBaseAddress + R_SA_MCHBAR_CHANNEL_HASH_OFFSET);
  ChannelEHash         = MrcCall->MrcMmioRead32 (MchBarBaseAddress + R_SA_MCHBAR_CHANNEL_EHASH_OFFSET);
  MadInterChannel      = MrcCall->MrcMmioRead32 (MchBarBaseAddress + R_SA_MCHBAR_MAD_INTER_CHANNEL_OFFSET);
  MadIntraCh0          = MrcCall->MrcMmioRead32 (MchBarBaseAddress + R_SA_MCHBAR_MAD_INTRA_CH0_OFFSET);
  MadIntraCh1          = MrcCall->MrcMmioRead32 (MchBarBaseAddress + R_SA_MCHBAR_MAD_INTRA_CH1_OFFSET);
  MadDimmCh0           = MrcCall->MrcMmioRead32 (MchBarBaseAddress + R_SA_MCHBAR_MAD_DIMM_CH0_OFFSET);
  MadDimmCh1           = MrcCall->MrcMmioRead32 (MchBarBaseAddress + R_SA_MCHBAR_MAD_DIMM_CH1_OFFSET);
  IsTcm                = FALSE;

  if (MrcDecode (
    MrcCall,
    MemoryAddress,
    &IsTcm,
    Tolud,
    RemapBase,
    RemapLimit,
    Tom,
    ChannelHash,
    ChannelEHash,
    MadInterChannel,
    MadIntraCh0,
    MadIntraCh1,
    MadDimmCh0,
    MadDimmCh1,
    &TempChannel,
    &TempDimm,
    &TempRank,
    &TempBankGroup,
    &TempBank,
    &TempRow,
    &TempColumn
  )) {
    Status = EFI_SUCCESS;
  }
  DramAddress->Socket = 0;
  DramAddress->Controller = 0;
  DramAddress->ChannelNumber = (UINT8)TempChannel;
  DramAddress->DimmNumber = (UINT8)TempDimm;
  DramAddress->Rank = (UINT8)TempRank;
  DramAddress->BankGroup = (UINT8)TempBankGroup;
  DramAddress->Bank = (UINT8)TempBank;
  DramAddress->Ras = (UINT32)TempRow;
  DramAddress->Cas = (UINT16)TempColumn;

  return Status;
}

/**
  Address encode function (reverse address decode)
  DRAM address to memory address conversion

  @param[in]      DramAddress    - The DRAM address that is to be encoded.
  @param[out]     MemoryAddress  - The 39-bit memory address to convert to.

  @retval Returns EFI_SUCCESS if successful, EFI_UNSUPPORTED otherwise.
**/
EFI_STATUS
(EFIAPI MrcMemoryAddressEncode) (
  IN  MRC_DRAM_ADDRESS *DramAddress,
  OUT UINT64           *MemoryAddress
  )
{
  MRC_ADDR_FUNCTION CallTable;
  MRC_ADDR_FUNCTION *MrcCall;
  EFI_STATUS    Status;
  UINT32        MchBarBaseAddress;
  UINT32        PciEBaseAddress;
  UINT32        Offset;
  BOOLEAN       IsTcm;
  UINT64        Tom;
  UINT64        RemapBase;
  UINT64        RemapLimit;
  UINT32        Tolud;
  UINT32        ChannelHash;
  UINT32        ChannelEHash;
  UINT32        MadInterChannel;
  UINT32        MadIntraCh0;
  UINT32        MadIntraCh1;
  UINT32        MadDimmCh0;
  UINT32        MadDimmCh1;

  MrcCall = &CallTable;
  Status = EFI_UNSUPPORTED;

  //
  // Set function pointers
  //
#ifdef MRC_MINIBIOS_BUILD
  MrcCall->MrcIoRead32     = (MRC_IO_READ_32) (&MrcOemInPort32);
  MrcCall->MrcIoWrite32    = (MRC_IO_WRITE_32) (&MrcOemOutPort32);
  MrcCall->MrcMmioRead32   = (MRC_MMIO_READ_32) (&MrcOemMmioRead32);
  MrcCall->MrcMmioRead64   = (MRC_MMIO_READ_64) (&SaMmioRead64);
  MrcCall->MrcCopyMem      = (MRC_MEMORY_COPY) (&MrcOemMemoryCpy);
#else
  MrcCall->MrcIoRead32     = (MRC_IO_READ_32) (&IoRead32);
  MrcCall->MrcIoWrite32    = (MRC_IO_WRITE_32) (&IoWrite32);
  MrcCall->MrcMmioRead32   = (MRC_MMIO_READ_32) (&MmioRead32);
  MrcCall->MrcMmioRead64   = (MRC_MMIO_READ_64) (&MmioRead64);
  MrcCall->MrcCopyMem      = (MRC_MEMORY_COPY) (&CopyMem);
#endif // MRC_MINIBIOS_BUILD
  MrcCall->MrcSetMem       = (MRC_MEMORY_SET_BYTE) (&SetMem);
  MrcCall->MrcMultU64x32   = (MRC_MULT_U64_U32) (&MultU64x32);
  MrcCall->MrcDivU64x64    = (MRC_DIV_U64_U64) (&DivU64x64Remainder);
  MrcCall->MrcLeftShift64  = (MRC_LEFT_SHIFT_64) (&LShiftU64);
  MrcCall->MrcRightShift64 = (MRC_RIGHT_SHIFT_64) (&RShiftU64);

  //
  // Check that MCHBAR is programmed
  //
  MrcCall->MrcIoWrite32 (0xCF8, MRC_BIT31 | R_SA_MCHBAR);
  MchBarBaseAddress = MrcCall->MrcIoRead32 (0xCFC);

  if ((MchBarBaseAddress & MRC_BIT0) == MRC_BIT0) {
    MchBarBaseAddress &= (~MRC_BIT0);
  } else {
    return Status;
  }

  //
  // Check that PCIEXBAR is programmed
  //
  MrcCall->MrcIoWrite32 (0xCF8, MRC_BIT31 | R_SA_PCIEXBAR);
  PciEBaseAddress = MrcCall->MrcIoRead32 (0xCFC);

  if ((PciEBaseAddress & MRC_BIT0) == MRC_BIT0) {
    PciEBaseAddress &= ~(MRC_BIT2 | MRC_BIT1 | MRC_BIT0);
  } else {
    return Status;
  }

  //
  // Collect address configuration from registers
  //
  Offset               = PciEBaseAddress + R_SA_TOLUD;
  Tolud                = MrcCall->MrcMmioRead32 (Offset);
  Offset               = PciEBaseAddress + R_SA_TOM;
  Tom                  = MrcCall->MrcMmioRead64 (Offset);
  RemapBase            = MrcCall->MrcMmioRead64 (MchBarBaseAddress + R_SA_MCHBAR_REMAPBASE_OFFSET);
  RemapLimit           = MrcCall->MrcMmioRead64 (MchBarBaseAddress + R_SA_MCHBAR_REMAPLIMIT_OFFSET);
  ChannelHash          = MrcCall->MrcMmioRead32 (MchBarBaseAddress + R_SA_MCHBAR_CHANNEL_HASH_OFFSET);
  ChannelEHash         = MrcCall->MrcMmioRead32 (MchBarBaseAddress + R_SA_MCHBAR_CHANNEL_EHASH_OFFSET);
  MadInterChannel      = MrcCall->MrcMmioRead32 (MchBarBaseAddress + R_SA_MCHBAR_MAD_INTER_CHANNEL_OFFSET);
  MadIntraCh0          = MrcCall->MrcMmioRead32 (MchBarBaseAddress + R_SA_MCHBAR_MAD_INTRA_CH0_OFFSET);
  MadIntraCh1          = MrcCall->MrcMmioRead32 (MchBarBaseAddress + R_SA_MCHBAR_MAD_INTRA_CH1_OFFSET);
  MadDimmCh0           = MrcCall->MrcMmioRead32 (MchBarBaseAddress + R_SA_MCHBAR_MAD_DIMM_CH0_OFFSET);
  MadDimmCh1           = MrcCall->MrcMmioRead32 (MchBarBaseAddress + R_SA_MCHBAR_MAD_DIMM_CH1_OFFSET);
  IsTcm                = FALSE;

  if (MrcEncode (
    MrcCall,
    DramAddress->ChannelNumber,
    DramAddress->DimmNumber,
    DramAddress->Rank,
    DramAddress->BankGroup,
    DramAddress->Bank,
    DramAddress->Ras,
    DramAddress->Cas,
    Tolud,
    RemapBase,
    RemapLimit,
    Tom,
    ChannelHash,
    ChannelEHash,
    MadInterChannel,
    MadIntraCh0,
    MadIntraCh1,
    MadDimmCh0,
    MadDimmCh1,
    0,
    MemoryAddress,
    &IsTcm
  )) {
    Status = EFI_SUCCESS;
  }

  return Status;
}
