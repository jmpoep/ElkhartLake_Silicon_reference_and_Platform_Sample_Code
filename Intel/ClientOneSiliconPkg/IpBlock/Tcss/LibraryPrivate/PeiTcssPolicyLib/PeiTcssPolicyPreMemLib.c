/** @file
  This file provides services for TCSS PreMem policy function

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
#include <Library/DebugLib.h>
#include <Library/SiConfigBlockLib.h>
#include <Library/ConfigBlockLib.h>
#include <Ppi/SiPolicy.h>
#include <TcssPeiPreMemConfig.h>
#include <Library/PchInfoLib.h>

/**
  Print TCSS_PEI_PREMEM_CONFIG and serial out.

  @param[in] SiPreMemPolicyPpi            Pointer to a SI_PREMEM_POLICY_PPI
**/
VOID
TcssPrintConfigPreMem (
  IN SI_PREMEM_POLICY_PPI     *SiPreMemPolicyPpi
  )
{
  EFI_STATUS               Status;
  TCSS_PEI_PREMEM_CONFIG   *TcssPeiPreMemConfig;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gTcssPeiPreMemConfigGuid, (VOID *) &TcssPeiPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "----------------------- TCSS_PEI_PREMEM_CONFIG -----------------\n"));
  DEBUG ((DEBUG_INFO, " Revision : %d\n", TcssPeiPreMemConfig->Header.Revision));
  ASSERT (TcssPeiPreMemConfig->Header.Revision == TCSS_PEI_PREMEM_CONFIG_REVISION);
  DEBUG ((DEBUG_INFO, " TCSS Port Enabled Bitmap : %01x\n", TcssPeiPreMemConfig->UsbTcConfig.UsbTcPortEn));
  DEBUG ((DEBUG_INFO, " TcssPeiPreMemConfig->MiscConfig.PcieMultipleSegmentEnabled : 0x%x\n", TcssPeiPreMemConfig->MiscConfig.PcieMultipleSegmentEnabled));
  DEBUG ((DEBUG_INFO, " TCSS ITBT PCIE 0-3 Enable : %01d %01d %01d %01d\n",
                                                      TcssPeiPreMemConfig->DevEnConfig.TcssDevEnBit.TcssItbtPcie0En,
                                                      TcssPeiPreMemConfig->DevEnConfig.TcssDevEnBit.TcssItbtPcie1En,
                                                      TcssPeiPreMemConfig->DevEnConfig.TcssDevEnBit.TcssItbtPcie2En,
                                                      TcssPeiPreMemConfig->DevEnConfig.TcssDevEnBit.TcssItbtPcie3En));
  DEBUG ((DEBUG_INFO, " TCSS xHCI Enable : %01d\n", TcssPeiPreMemConfig->DevEnConfig.TcssDevEnBit.TcssXhciEn));
  DEBUG ((DEBUG_INFO, " TCSS xDCI Enable : %01d\n", TcssPeiPreMemConfig->DevEnConfig.TcssDevEnBit.TcssXdciEn));
  DEBUG ((DEBUG_INFO, " TCSS ITBT DMA 0-1 Enable : %01d %01d\n",
                                                      TcssPeiPreMemConfig->DevEnConfig.TcssDevEnBit.TcssDma0En,
                                                      TcssPeiPreMemConfig->DevEnConfig.TcssDevEnBit.TcssDma1En));
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
TcssLoadConfigPreMemDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  TCSS_PEI_PREMEM_CONFIG      *TcssPreMemConfig;
  UINTN                       Index;

  TcssPreMemConfig = (TCSS_PEI_PREMEM_CONFIG *)ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "TcssPreMemConfig->Header.GuidHob.Name = %g\n", &TcssPreMemConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "TcssPreMemConfig->Header.GuidHob.Header.HobLength = 0x%x\n", TcssPreMemConfig->Header.GuidHob.Header.HobLength));

  // Default for the TCSS IPs device enabling
  TcssPreMemConfig->DevEnConfig.TcssDevEnBit.TcssItbtPcie0En = 1;
  TcssPreMemConfig->DevEnConfig.TcssDevEnBit.TcssItbtPcie1En = 1;
  TcssPreMemConfig->DevEnConfig.TcssDevEnBit.TcssItbtPcie2En = 1;
  TcssPreMemConfig->DevEnConfig.TcssDevEnBit.TcssItbtPcie3En = 1;
  TcssPreMemConfig->DevEnConfig.TcssDevEnBit.TcssXhciEn = 1;
  TcssPreMemConfig->DevEnConfig.TcssDevEnBit.TcssDma0En = 1;
  TcssPreMemConfig->DevEnConfig.TcssDevEnBit.TcssDma1En = 1;

  // Default set all ports are Type C enabled
  for (Index = 0; Index <  GetPchMaxTypeCPortNum(); Index++) {
    TcssPreMemConfig->UsbTcConfig.UsbTcPortEn |= BIT0 << Index;
  }
}

STATIC COMPONENT_BLOCK_ENTRY  mTcssBlocksPreMem = {
  &gTcssPeiPreMemConfigGuid,
  sizeof (TCSS_PEI_PREMEM_CONFIG),
  TCSS_PEI_PREMEM_CONFIG_REVISION,
  TcssLoadConfigPreMemDefault
};

/**
  Get TCSS PreMem config block table size.

  @retval      Size of config block
**/
UINT16
TcssGetConfigBlockTotalSizePreMem (
  VOID
  )
{
  return mTcssBlocksPreMem.Size;
}

/**
  Add TCSS PreMem ConfigBlock.

  @param[in] ConfigBlockTableAddress    The pointer to config block table

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
TcssAddConfigBlockPreMem (
  IN VOID           *ConfigBlockTableAddress
  )
{
  return AddComponentConfigBlocks (ConfigBlockTableAddress, &mTcssBlocksPreMem, 1);
}