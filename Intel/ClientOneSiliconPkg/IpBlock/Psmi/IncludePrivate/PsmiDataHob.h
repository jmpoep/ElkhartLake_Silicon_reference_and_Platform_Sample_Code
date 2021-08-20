/** @file
  The GUID definition for PsmiDataHob

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

@par Specification Reference:
**/
#ifndef _PSMI_DATA_HOB_H_
#define _PSMI_DATA_HOB_H_

#include <Base.h>
#include <PsmiConfig.h>

extern EFI_GUID gPsmiDataHobGuid;
#pragma pack (push,1)

/**
  This structure contains the PSMI Trace Region Info
**/
typedef struct {
  UINT64   TraceRegionBase;
  UINT32   Size;
  UINT8    CacheType;
  UINT8    ErrCode;
} PSMI_TRACE_REGION_INFO;

/**
  This structure will be used for passing PSMI trace Info to MRC
**/
typedef struct {
  UINT64   TotalSize;
  UINT8    CacheType;
} PSMI_MRC_INPUTS;

/**
  This structure contains the PSMI Handler Info
**/
typedef struct {
  UINT8    HandlerSize;
} PSMI_HANDLER_INFO;
//
// This HOB structure contains Handler , Trace Region Info , PSMI MRC Input Info.
//
typedef struct {
  PSMI_HANDLER_INFO          HandlerInfo;                        ///< Handler Info
  PSMI_TRACE_REGION_INFO     TraceRegionInfo[MAX_TRACE_REGION];  ///< Trace Region Info
  PSMI_MRC_INPUTS            PsmiMrcParam[MAX_TRACE_CACHE_TYPE]; ///< PSMI Trace MRC Input
  UINT32                     PsmiInputRegValue;                  ///< PSMI Scratchpad Input value
} PSMI_CONFIG;

///
/// PSMI Data Hob
///
typedef struct {
  EFI_HOB_GUID_TYPE        EfiHobGuidType;    ///< GUID Hob type structure for gSaDataHobGuid
  PSMI_CONFIG              PsmiConfig;        ///< PSMI Handler/Trace/PSMI MRC Info
  UINT8                    Rsvd1[4];          ///< Reserved for future use.
} PSMI_DATA_HOB;
#pragma pack (pop)
#endif
