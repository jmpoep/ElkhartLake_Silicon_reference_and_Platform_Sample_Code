/** @file
  This file is PeiSiPolicyLib library creates default settings of RC
  Policy and installs RC Policy PPI.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2020 Intel Corporation.

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
#include "PeiSiPolicyLibrary.h"
#include <Library/PcdLib.h>
#include <Library/PeiRtcPolicyLib.h>
#include <Library/PeiThermalPolicyLib.h>
#include <Library/PeiCnviPolicyLib.h>

/**
  Get Si config block table total size.

  @retval                               Size of PCH config block table
**/
UINT16
EFIAPI
SiGetConfigBlockTotalSize (
  VOID
  )
{
  return (UINT16) sizeof (SI_CONFIG);
}

EFI_STATUS
EFIAPI
LoadSiConfigBlockDefault (
  IN VOID *ConfigBlockPointer
  )
{
  SI_CONFIG                         *SiConfig;

  SiConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "SiConfig->Header.GuidHob.Name = %g\n", &SiConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "SiConfig->Header.GuidHob.Header.HobLength = 0x%x\n", SiConfig->Header.GuidHob.Header.HobLength));

  SiConfig->Header.Revision = SI_CONFIG_REVISION;

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
SiAddConfigBlocks (
  IN     VOID      *ConfigBlockTableAddress
  )
{
  VOID                 *ConfigBlockPointer;
  EFI_STATUS           Status;
  CONFIG_BLOCK_HEADER  SiBlock;

  //
  // Initalize SiBlock
  //
  CopyMem (&(SiBlock.GuidHob.Name), &gSiConfigGuid, sizeof (EFI_GUID));
  SiBlock.GuidHob.Header.HobLength = sizeof (SI_CONFIG);
  SiBlock.Revision                 = SI_CONFIG_REVISION;
  //
  // Initialize ConfigBlockPointer
  //
  ConfigBlockPointer = (VOID *)&SiBlock;
  //
  // Add config block fro SiBlock
  //
  DEBUG ((DEBUG_INFO, "gSiConfigGuid = %g\n", &gSiConfigGuid));
  DEBUG ((DEBUG_INFO, "SiConfig->Header.GuidHob.Name = %g\n", &(SiBlock.GuidHob.Name)));
  Status = AddConfigBlock (ConfigBlockTableAddress, (VOID *) &ConfigBlockPointer);
  ASSERT_EFI_ERROR (Status);

  LoadSiConfigBlockDefault ((VOID *) ConfigBlockPointer);

  return Status;
}

/**
  SiCreateConfigBlocks creates the config blocksg of Silicon Policy.
  It allocates and zero out buffer, and fills in the Intel default settings.

  @param[out] SiPolicyPpi         The pointer to get Silicon Policy PPI instance

  @retval EFI_SUCCESS             The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES    Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
SiCreateConfigBlocks (
  OUT  SI_POLICY_PPI **SiPolicyPpi
  )
{
  UINT16        TotalBlockSize;
  EFI_STATUS    Status;
  SI_POLICY_PPI *SiPolicy;
  UINT16        RequiredSize;

  SiPolicy = NULL;
  //
  // TotalBlockSize = Si, Pch, AMT, ME, SA and CPU config block size.
  //
  TotalBlockSize = SiGetConfigBlockTotalSize () +
                   PchGetConfigBlockTotalSize () +
                   AmtGetConfigBlockTotalSize () +
                   MeGetConfigBlockTotalSize () +
                   SaGetConfigBlockTotalSize () +
                   CpuGetConfigBlockTotalSize ();
  //
  // Add size of IpBlock config blocks
  //
  TotalBlockSize += RtcGetConfigBlockTotalSize ();
  TotalBlockSize += ThermalGetConfigBlockTotalSize ();
  TotalBlockSize += CnviGetConfigBlockTotalSize ();
  TotalBlockSize += EspiGetConfigBlockTotalSize ();
  TotalBlockSize += GbeGetConfigBlockTotalSize ();
  TotalBlockSize += TsnGetConfigBlockTotalSize ();
  TotalBlockSize += TccGetConfigBlockTotalSize ();
  TotalBlockSize += HdaGetConfigBlockTotalSize ();
  TotalBlockSize += IehGetConfigBlockTotalSize ();
  TotalBlockSize += PseGetConfigBlockTotalSize ();
  TotalBlockSize += SiipGetConfigBlockTotalSize ();
  TotalBlockSize += ItssGetConfigBlockTotalSize ();
  TotalBlockSize += P2sbGetConfigBlockTotalSize ();
  TotalBlockSize += PchDmiGetConfigBlockTotalSize ();
  TotalBlockSize += PmcGetConfigBlockTotalSize ();
  TotalBlockSize += SataGetConfigBlockTotalSize ();
  TotalBlockSize += ScsGetConfigBlockTotalSize ();
  TotalBlockSize += UsbGetConfigBlockTotalSize ();
  TotalBlockSize += ThcGetConfigBlockTotalSize ();
  TotalBlockSize += PsfGetConfigBlockTotalSize ();
  TotalBlockSize += FusaGetConfigBlockTotalSize ();
  TotalBlockSize += GraphicsGetConfigBlockTotalSize ();
  TotalBlockSize += GnaGetConfigBlockTotalSize ();
  TotalBlockSize += SerialIoGetConfigBlockTotalSize ();

  DEBUG ((DEBUG_INFO, "TotalBlockSize = 0x%x\n", TotalBlockSize));

  RequiredSize = sizeof (CONFIG_BLOCK_TABLE_HEADER) + TotalBlockSize;

  Status = CreateConfigBlockTable (RequiredSize, (VOID *) &SiPolicy);
  ASSERT_EFI_ERROR (Status);

  //
  // General initialization
  //
  SiPolicy->TableHeader.Header.Revision = SI_POLICY_REVISION;
  //
  // Add config blocks.
  //
  Status = SiAddConfigBlocks ((VOID *) SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = PchAddConfigBlocks ((VOID *) SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = AmtAddConfigBlocks ((VOID *) SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = MeAddConfigBlocks ((VOID *) SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = SaAddConfigBlocks ((VOID *) SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = CpuAddConfigBlocks ((VOID *) SiPolicy);
  ASSERT_EFI_ERROR (Status);

  //
  // IpBlock config blocks
  //
  Status = RtcAddConfigBlock (SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = ThermalAddConfigBlock (SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = CnviAddConfigBlock (SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = EspiAddConfigBlock (SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = GbeAddConfigBlock (SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = TsnAddConfigBlock (SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = TccAddConfigBlock (SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = HdaAddConfigBlock (SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = IehAddConfigBlock (SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = PseAddConfigBlock (SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = SiipAddConfigBlock (SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = ItssAddConfigBlock (SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = P2sbAddConfigBlock (SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = PchDmiAddConfigBlock (SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = PmcAddConfigBlock (SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = SataAddConfigBlock (SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = ScsAddConfigBlock (SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = UsbAddConfigBlock (SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = ThcAddConfigBlock (SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = PsfAddConfigBlock (SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = FusaAddConfigBlock (SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = GraphicsAddConfigBlocks ((VOID *) SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = GnaAddConfigBlocks ((VOID *) SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = SerialIoAddConfigBlock ((VOID *) SiPolicy);
  ASSERT_EFI_ERROR (Status);

  //
  // Assignment for returning SaInitPolicy config block base address
  //
  *SiPolicyPpi = SiPolicy;
  return Status;
}

/**
  Print out all silicon policy information.

  @param[in] SiPolicyPpi         The pointer to Silicon Policy PPI instance

  @retval none
**/
VOID
DumpSiPolicy (
  IN  SI_POLICY_PPI *SiPolicyPpi
  )
{
  //
  // Print SI config blocks and serial out.
  //
  SiPrintPolicyPpi (SiPolicyPpi);

  //
  // Print PCH config blocks and serial out.
  //
  PchPrintPolicyPpi (SiPolicyPpi);
  //
  // Print IpBlocks config.
  //
  RtcPrintConfig (SiPolicyPpi);
  ThermalPrintConfig (SiPolicyPpi);
  CnviPrintConfig (SiPolicyPpi);
  EspiPrintConfig (SiPolicyPpi);
  GbePrintConfig (SiPolicyPpi);
  TsnPrintConfig (SiPolicyPpi);
  HdaPrintConfig (SiPolicyPpi);
  TccPrintConfig (SiPolicyPpi);
  IehPrintConfig (SiPolicyPpi);
  PsePrintConfig (SiPolicyPpi);
  SiipPrintConfig (SiPolicyPpi);
  ItssPrintConfig (SiPolicyPpi);
  P2sbPrintConfig (SiPolicyPpi);
  PchDmiPrintConfig (SiPolicyPpi);
  PmcPrintConfig (SiPolicyPpi);
  SataPrintConfig (SiPolicyPpi);
  ScsPrintConfig (SiPolicyPpi);
  UsbPrintConfig (SiPolicyPpi);
  ThcPrintConfig (SiPolicyPpi);
  PsfPrintConfig (SiPolicyPpi);
  FusaPrintConfig (SiPolicyPpi);
  //
  // Print AMT config blocks and serial out.
  //
  AmtPrintPolicyPpi (SiPolicyPpi);
  //
  // Print ME config blocks and serial out.
  //
  MePrintPolicyPpi (SiPolicyPpi);
  //
  // Print SA config blocks and serial out.
  //
  SaPrintPolicyPpi (SiPolicyPpi);
  //
  // Print SA IpBlocks config.
  //
  GraphicsPrintPolicyPpi (SiPolicyPpi);
  GnaPrintPolicyPpi (SiPolicyPpi);
  SerialIoPrintConfig (SiPolicyPpi);
  //
  // Print CPU config block and serial out.
  //
  CpuPrintPolicy (SiPolicyPpi);
}

/**
  SiInstallPolicyPpi installs SiPolicyPpi.
  While installed, RC assumes the Policy is ready and finalized. So please update and override
  any setting before calling this function.

  @param[in] SiPolicyPpi         The pointer to Silicon Policy PPI instance

  @retval EFI_SUCCESS            The policy is installed.
  @retval EFI_OUT_OF_RESOURCES   Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
SiInstallPolicyPpi (
  IN  SI_POLICY_PPI *SiPolicyPpi
  )
{
  EFI_STATUS             Status;
  EFI_PEI_PPI_DESCRIPTOR *SiPolicyPpiDesc;
  SI_CONFIG              *SiConfig;

  SiPolicyPpiDesc = (EFI_PEI_PPI_DESCRIPTOR *) AllocateZeroPool (sizeof (EFI_PEI_PPI_DESCRIPTOR));
  if (SiPolicyPpiDesc == NULL) {
    ASSERT (FALSE);
    return EFI_OUT_OF_RESOURCES;
  }

  SiPolicyPpiDesc->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
  SiPolicyPpiDesc->Guid  = &gSiPolicyPpiGuid;
  SiPolicyPpiDesc->Ppi   = SiPolicyPpi;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gSiConfigGuid, (VOID *) &SiConfig);
  ASSERT_EFI_ERROR (Status);

  //
  // Install Silicon Policy PPI
  //
  Status = PeiServicesInstallPpi (SiPolicyPpiDesc);
  ASSERT_EFI_ERROR (Status);
  return Status;
}

/**
  SiInstallPolicyReadyPpi installs SiPolicyReadyPpi.
  While installed, RC assumes the Policy is ready and finalized. So please update and override
  any setting before calling this function.

  @retval EFI_SUCCESS            The policy is installed.
  @retval EFI_OUT_OF_RESOURCES   Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
SiInstallPolicyReadyPpi (
  VOID
  )
{
  EFI_STATUS             Status;
  EFI_PEI_PPI_DESCRIPTOR *SiPolicyReadyPpiDesc;
  SI_POLICY_PPI          *SiPolicy;

  SiPolicyReadyPpiDesc = (EFI_PEI_PPI_DESCRIPTOR *) AllocateZeroPool (sizeof (EFI_PEI_PPI_DESCRIPTOR));
  if (SiPolicyReadyPpiDesc == NULL) {
    ASSERT (FALSE);
    return EFI_OUT_OF_RESOURCES;
  }

  SiPolicyReadyPpiDesc->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
  SiPolicyReadyPpiDesc->Guid  = &gSiPolicyReadyPpiGuid;
  SiPolicyReadyPpiDesc->Ppi   = NULL;

  SiPolicy = NULL;
  Status = PeiServicesLocatePpi (
             &gSiPolicyPpiGuid,
             0,
             NULL,
             (VOID **)&SiPolicy
             );
  ASSERT_EFI_ERROR(Status);

  if ((Status == EFI_SUCCESS) && (SiPolicy != NULL)) {
    DEBUG ((DEBUG_INFO, "Dump Silicon Policy update by Platform...\n"));
    DumpSiPolicy (SiPolicy);
  }
  //
  // Install Silicon Policy PPI
  //
  Status = PeiServicesInstallPpi (SiPolicyReadyPpiDesc);
  ASSERT_EFI_ERROR (Status);
  return Status;
}

