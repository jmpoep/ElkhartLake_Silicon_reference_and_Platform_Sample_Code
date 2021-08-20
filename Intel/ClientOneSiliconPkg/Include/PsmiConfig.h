/** @file
  Header file for PSMI  Config

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
#ifndef _PSMI_CONFIG_H_
#define _PSMI_CONFIG_H_

#pragma pack (push,1)

//
// PSMI Error codes
//
#define PSMI_ALLOCATION_SUCCESS      1
#define ERROR_OUT_OF_RESOURCES       2
#define ERROR_CACHE_TYPE             3
#define ERROR_MTRR_SHORTAGE          4
#define ERROR_NO_ABOVE_4G_MEMORY     5
//
// PSMI Trace Memory cache types
//
typedef enum {
  RegionDonotCare      = 0,
  RegionUncacheable    = 1,
  RegionWriteCombine   = 2,
} PSMI_TRACE_CACHE_TYPE;

#define PSMI_HANDLER_MEMORY_OFFSET_1000  0x1000
//
// PSMI Max Trace/Cache Type
//
#define MAX_TRACE_REGION             5
#define MAX_TRACE_CACHE_TYPE         3
//
// PSMI Input Scratchpad Register
//
typedef union {
  UINT32 RegValue;
  struct {
    UINT32 PsmiHandler:2;           /// 1:0   - PSMI Handler Size
    UINT32 TraceRegion0Size:4;      /// 5:2   - Trace Region 0 Size
    UINT32 TraceRegion0CacheType:2; /// 7:6   - Trace Region 0 Cache Type
    UINT32 TraceRegion1Size:4;      /// 11:8  - Trace Region 1 Size
    UINT32 TraceRegion1CacheType:2; /// 13:12 - Trace Region 1 Cache Type
    UINT32 TraceRegion2Size:4;      /// 17:14 - Trace Region 2 Size
    UINT32 TraceRegion2CacheType:2; /// 19:18 - Trace Region 2 Cache Type
    UINT32 TraceRegion3Size:4;      /// 23:20 - Trace Region 3 Size
    UINT32 TraceRegion3CacheType:2; /// 25:24 - Trace Region 3 Cache Type
    UINT32 TraceRegion4Size:4;      /// 29:26 - Trace Region 4 Size
    UINT32 TraceRegion4CacheType:2; /// 31:30 - Trace Region 5 Cache Type
  } Bits;
} PSMI_INPUT_SCRPD1_REGISTER;

//
// PSMI Output Scratchpad Register
//
typedef union {
  UINT32 RegValue;
  struct {
    UINT32 PsmiHandlerResultCode:3;  /// 2:0   - Handler Error Code
    UINT32 TraceRegion0ResultCode:3; /// 5:3   - Trace Region 0 Error Code
    UINT32 TraceRegion1ResultCode:3; /// 8:6   - Trace Region 1 Error Code
    UINT32 TraceRegion2ResultCode:3; /// 11:9  - Trace Region 2 Error Code
    UINT32 TraceRegion3ResultCode:3; /// 14:12 - Trace Region 3 Error Code
    UINT32 TraceRegion4ResultCode:3; /// 17:15 - Trace Region 4 Error Code
    UINT32 PsmiHandlerBase:14;       /// 31:18 - PSMI Handler Base
  } Bits;
} PSMI_OUTPUT_SCRPD1_REGISTER;

//
// PSMI Handler Space Offset 0x1000 Decode
//
typedef struct {
  UINT64 PsmiHandlerBaseAddress;  /// PSMI Handler BaseAddress
  UINT64 TraceRegion0BaseAddress; /// Trace Region 0 BaseAddress
  UINT64 TraceRegion1BaseAddress; /// Trace Region 1 BaseAddress
  UINT64 TraceRegion2BaseAddress; /// Trace Region 2 BaseAddress
  UINT64 TraceRegion3BaseAddress; /// Trace Region 3 BaseAddress
  UINT64 TraceRegion4BaseAddress; /// Trace Region 4 BaseAddress
  UINT32 PsmiInputRegValue;       /// PSMI Request Data
} PSMI_HANDLER_SPACE_OFFSET;

#pragma pack (pop)

#endif
