/** @file
  PEI Pch Trace Hub policy library.

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
#ifndef _PEI_PCH_TRACE_HUB_POLICY_LIB_H_
#define _PEI_PCH_TRACE_HUB_POLICY_LIB_H_

#include <Ppi/SiPolicy.h>

/**
  Add PCH Trace Hub ConfigBlock.

  @param[in] ConfigBlockTableAddress    The pointer to config block table

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
PchTraceHubPreMemAddConfigBlock (
  IN VOID           *ConfigBlockTableAddress
  );

/**
  Load PCH Trace Hub Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
PchTraceHubPreMemLoadConfigDefault (
  IN VOID          *ConfigBlockPointer
  );

/**
  Print PCH Trace Hub Config

  @param[in] SiPreMemPolicyPpi            Pointer to a SI_PREMEM_POLICY_PPI
**/
VOID
PchTraceHubPreMemPrintConfig (
  IN SI_PREMEM_POLICY_PPI     *SiPreMemPolicyPpi
  );

/**
  Get PCH Trace Hub config block table size.

  @retval      Size of config block
**/
UINT16
PchTraceHubPreMemGetConfigBlockTotalSize (
  VOID
  );

#endif // _PEI_PCH_TRACE_HUB_POLICY_LIB_H_
