/** @file
  This file contains CPU Gnvs Struct specific to processor

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
#ifndef _POWER_MGMT_NVS_STRUCT_H_
#define _POWER_MGMT_NVS_STRUCT_H_

#include <CpuNvsAreaDef.h>
//
// Processor Power Management GlobalNvs Revisions
//
#define CPU_NVS_AREA_REVISION 1


typedef struct _CPU_NVS_AREA_CONFIG {
  CPU_NVS_AREA *Area;
} CPU_NVS_AREA_CONFIG;

typedef struct _FVID_HEADER {
  UINT32 Stepping;    ///< Matches value returned by CPUID function 1
  UINT16 MaxBusRatio; ///< Matches BUS_RATIO_MAX field in PERF_STS_MSR
  UINT16 EistStates;  ///< Number of states of FVID (N)
} FVID_HEADER;

typedef struct _FVID_STATE {
  UINT32 State;           ///< State Number (0 - N-1)
  UINT16 BusRatio;        ///< BUS_RATIO_SEL value to be written to PERF_CTL
  UINT32 Power;           ///< Typical power consumed by CPU in this state
  UINT32 Limit16State;    ///< State Number (0 - N-1) with limit 16 P-states
  UINT16 Limit16BusRatio; ///< BUS_RATIO_SEL value to be written to PERF_CTL with limit 16 P-states
  UINT32 Limit16Power;    ///< Typical power consumed by CPU in this state with limit 16 P-states
} FVID_STATE;

typedef union _FVID_TABLE {
  FVID_HEADER FvidHeader;
  FVID_STATE  FvidState;
  UINT64      FvidData;
} FVID_TABLE;

#endif
