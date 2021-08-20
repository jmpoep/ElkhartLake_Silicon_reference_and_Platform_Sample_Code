/** @file
  CPU Test Config Block.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/
#ifndef _CPU_TEST_CONFIG_H_
#define _CPU_TEST_CONFIG_H_

#define CPU_TEST_CONFIG_REVISION 1

extern EFI_GUID gCpuTestConfigGuid;

#pragma pack (push,1)

/**
  CPU Test Configuration Structure.

  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                   ///< Config Block Header
  UINT32                MlcStreamerPrefetcher           : 1;     ///< Enable or Disable MLC Streamer Prefetcher; 0: Disable; <b>1: Enable</b>.
  UINT32                MlcSpatialPrefetcher            : 1;     ///< Enable or Disable MLC Spatial Prefetcher; 0: Disable; <b>1: Enable</b>.
  UINT32                MonitorMwaitEnable              : 1;     ///< Enable or Disable Monitor /MWAIT instructions; 0: Disable; <b>1: Enable</b>.
  UINT32                MachineCheckEnable              : 1;     ///< Enable or Disable initialization of machine check registers; 0: Disable; <b>1: Enable</b>.
  UINT32                ProcessorTraceOutputScheme      : 1;     ///< Control on Processor Trace output scheme; <b>0: Single Range Output</b>; 1: ToPA Output.
  UINT32                ProcessorTraceEnable            : 1;     ///< Enable or Disable Processor Trace feature; <b>0: Disable</b>; 1: Enable.
  UINT32                ThreeStrikeCounterDisable       : 1;     ///< Disable Three strike counter; <b>0: FALSE</b>; 1: TRUE.
  /**
    This policy should be used to enable or disable Voltage Optimization feature.
    Recommended defaults:
     Enable  - For Mobile SKUs(U/Y)
     Disable - Rest of all SKUs other than Mobile.
  **/
  UINT32                VoltageOptimization             : 1;
  UINT32                IsFusaSupported                 : 1;
  UINT32                RsvdBits                        : 23;     ///< Reserved for future use
  /**
     Base address of memory region allocated for Processor Trace.
     Processor Trace requires 2^N alignment and size in bytes per thread, from 4KB to 128MB.
     - <b>NULL: Disable</b>
  **/
  EFI_PHYSICAL_ADDRESS  ProcessorTraceMemBase;
  /**
     Length in bytes of memory region allocated for Processor Trace.
     Processor Trace requires 2^N alignment and size in bytes per thread, from 4KB to 128MB.
     - <b>0: Disable</b>
  **/
  UINT32                ProcessorTraceMemLength;

} CPU_TEST_CONFIG;

#pragma pack (pop)

#endif // _CPU_TEST_CONFIG_H_
