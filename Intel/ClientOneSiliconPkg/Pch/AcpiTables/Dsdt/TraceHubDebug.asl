/**@file
 Trace Hub debug library for ASL code.

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

#include <PchReservedResources.h>

//
// Master number should align with gEfiBpCommonPkgTokenSpaceGuid.PcdTraceHubDebugLibMaster
// Channel number should align with gEfiBpCommonPkgTokenSpaceGuid.PcdTraceHubDebugLibChannel
//
#define TRACE_HUB_MASTER_NUM_ASL        72
#define TRACE_HUB_CHANNEL_NUM_ASL       14
#define V_TRACE_HUB_MEM_MTB_CHLCNT      0x80
#define V_TRACE_HUB_MEM_MTB_FTHMSTR     0x10

Scope(\){
  // Check if Trace Hub is enabled
  Method (THEN, 0, Serialized) {
    OperationRegion (THBA, SystemMemory, PCH_TRACE_HUB_FW_BASE_ADDRESS, 0x10)
    Field (THBA, DWordAcc, NoLock, Preserve) {
      Offset (0x00),
      DO00, 32,
    }
    Return (LNotEqual(DO00, 0xFFFFFFFF))
  }

  // Trace Hub debug address
  // This is internal helper runtine of THDS
  // Arg0 : Master number
  // Arg1 : Channel number
  Method (THDA, 2, Serialized) {
    // Local0 = PCH_TRACE_HUB_FW_BASE_ADDRESS + 0x40 * (V_TRACE_HUB_MEM_MTB_CHLCNT * (Master - V_TRACE_HUB_MEM_MTB_FTHMSTR)) + 0x40 * Channel;
    Store (PCH_TRACE_HUB_FW_BASE_ADDRESS, Local0)
    Add (Local0, Multiply (0x40, Multiply (V_TRACE_HUB_MEM_MTB_CHLCNT, Subtract (Arg0, V_TRACE_HUB_MEM_MTB_FTHMSTR))), Local0)
    Add (Local0, Multiply (0x40, Arg1), Local0)
    Return (Local0)
  }

  // String to raw data
  // This is internal helper runtine of THDS
  // Arg0 : string
  // Arg1 : Index
  // Arg2 : size
  Method (STRD, 3, Serialized) {
    If (LGreater (Add (Arg1, Arg2), SizeOf (Arg0))) {
      Return (0)
    }
    // Local0 is return value
    // Lccal1 is loop index
    // Local2 is char of string
    // Local3 is buffer of string
    ToBuffer (Arg0, Local3)
    Store (0, Local0)
    Store (0, Local1)
    While (LLess (Local1, Arg2)) {
      Store (DeRefOf (Index (Local3, Add (Arg1, Local1))), Local2)
      Add (Local0, ShiftLeft (Local2, Multiply (8, Local1)), Local0)
      Increment (Local1)
    }
    Return (Local0)
  }

  // Trace Hub debug string
  // Arg0 : debug string
  Method (THDS, 1, Serialized) {
    // TH check if enabled.
    If (LNot (THEN())) {
      Return
    }
    // Adding newline at the end of the string
    Concatenate (Arg0, "\n", local2)
    // Local0 is the length of string
    // Local1 is the debug base address
    // Local2 is the debug string with "\n"
    Store (Sizeof (local2), Local0)
    Store (THDA (TRACE_HUB_MASTER_NUM_ASL, TRACE_HUB_CHANNEL_NUM_ASL), Local1)
    OperationRegion (THBA, SystemMemory, local1, 0x40)
    Field (THBA, QWordAcc, NoLock, Preserve) {
      Offset (0x00),
      QO00, 64,
    }
    Field (THBA, DWordAcc, NoLock, Preserve) {
      Offset (0x00),
      DO00, 32,
      Offset (0x10),
      DO10, 32,
      offset (0x30),
      DO30, 32,
    }
    Field (THBA, WordAcc, NoLock, Preserve) {
      Offset (0x00),
      WO00, 16,
    }
    Field (THBA, ByteAcc, NoLock, Preserve) {
      Offset (0x00),
      BO00, 8,
    }

    // time stamp
    Store (0x01000242, DO10)
    // length of string
    Store (Local0, WO00)
    // string
    Store (0, Local6)
    Store (Local0, Local7)
    while (LGreaterEqual(Local7, 8)) {
      Store (STRD (local2, Local6, 8), QO00)
      Add (Local6, 8, Local6)
      Subtract (Local7, 8, Local7)
    }
    If (LGreaterEqual(Local7, 4)) {
      Store (STRD (local2, Local6, 4), DO00)
      Add (Local6, 4, Local6)
      Subtract (Local7, 4, Local7)
    }
    If (LGreaterEqual(Local7, 2)) {
      Store (STRD (local2, Local6, 2), WO00)
      Add (Local6, 2, Local6)
      Subtract (Local7, 2, Local7)
    }
    If (LGreaterEqual(Local7, 1)) {
      Store (STRD (local2, Local6, 1), BO00)
      Add (Local6, 1, Local6)
      Subtract (Local7, 1, Local7)
    }
    // flag
    Store (0, DO30)
  }

  // Trace Hub debug Hex string
  // Arg0 : Integer, buffer
  Method (THDH, 1, Serialized) {
    THDS (ToHexString (Arg0))
  }

  // Trace Hub debug decimal string
  // Arg0 : Integer, buffer
  Method (THDD, 1, Serialized) {
    THDS (ToDecimalString (Arg0))
  }
}
