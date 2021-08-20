/** @file
  This file provides services to configure CPU Trace Hub PreMem policy

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
#include <Library/DebugLib.h>
#include <Library/SiConfigBlockLib.h>
#include <Library/ConfigBlockLib.h>
#include <Ppi/SiPolicy.h>

/**
  Print CPU Trace Hub Config

  @param[in] SiPreMemPolicyPpi            Pointer to a SI_PREMEM_POLICY_PPI
**/
VOID
CpuTraceHubPreMemPrintConfig (
  IN SI_PREMEM_POLICY_PPI         *SiPreMemPolicyPpi
  )
{
  EFI_STATUS                      Status;
  CPU_TRACE_HUB_PREMEM_CONFIG     *CpuTraceHubPreMemConfig;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuTraceHubPreMemConfigGuid, (VOID *) &CpuTraceHubPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  DEBUG ((DEBUG_INFO, "------------------ CPU Trace Hub PreMem Config ------------------\n"));
  DEBUG ((DEBUG_INFO, " EnableMode  : 0x%x\n", CpuTraceHubPreMemConfig->TraceHub.EnableMode));
  DEBUG ((DEBUG_INFO, " MemReg0Size : 0x%x\n", CpuTraceHubPreMemConfig->TraceHub.MemReg0Size));
  DEBUG ((DEBUG_INFO, " MemReg1Size : 0x%x\n", CpuTraceHubPreMemConfig->TraceHub.MemReg1Size));
  DEBUG ((DEBUG_INFO, " AetEnabled  : 0x%x\n", CpuTraceHubPreMemConfig->TraceHub.AetEnabled));

}

/**
  Load CPU Trace Hub Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
CpuTraceHubPreMemLoadConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  CPU_TRACE_HUB_PREMEM_CONFIG  *CpuTraceHubPreMemConfig;
  CpuTraceHubPreMemConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "CpuTraceHubPreMemConfig->Header.GuidHob.Name = %g\n", &CpuTraceHubPreMemConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "CpuTraceHubPreMemConfig->Header.GuidHob.Header.HobLength = 0x%x\n", CpuTraceHubPreMemConfig->Header.GuidHob.Header.HobLength));

  CpuTraceHubPreMemConfig->TraceHub.MemReg0Size = TraceBuffer8M;
  CpuTraceHubPreMemConfig->TraceHub.MemReg1Size = TraceBuffer8M;
}

STATIC COMPONENT_BLOCK_ENTRY  mCpuTraceHubPreMemBlocks = {
  &gCpuTraceHubPreMemConfigGuid,
  sizeof (CPU_TRACE_HUB_PREMEM_CONFIG),
  CPU_TRACEHUB_PREMEM_CONFIG_REVISION,
  CpuTraceHubPreMemLoadConfigDefault
};

/**
  Get CPU Trace Hub config block table size.

  @retval      Size of config block
**/
UINT16
CpuTraceHubPreMemGetConfigBlockTotalSize (
  VOID
  )
{
  return mCpuTraceHubPreMemBlocks.Size;
}

/**
  Add CPU Trace Hub ConfigBlock.

  @param[in] ConfigBlockTableAddress    The pointer to config block table

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
CpuTraceHubPreMemAddConfigBlock (
  IN VOID           *ConfigBlockTableAddress
  )
{
  return AddComponentConfigBlocks (ConfigBlockTableAddress, &mCpuTraceHubPreMemBlocks, 1);
}
