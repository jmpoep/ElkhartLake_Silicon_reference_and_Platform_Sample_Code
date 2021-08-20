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
#include <Base.h>
#include <Library/PeiTraceHubLib.h>
#include <PciePreMemConfig.h>
#include <Library/PeiPcieRpPolicyLib.h>
#include <TccConfig.h>

/**
  Get Si PreMem config block table total size.

  @retval                               Size of SI PreMem config block table
**/
UINT16
SiGetConfigBlockTotalSizePreMem (
  VOID
  )
{
  return (UINT16) sizeof (SI_PREMEM_CONFIG);
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
EFI_STATUS
LoadSiPreMemConfigBlockDefault (
  IN VOID              *ConfigBlockPointer
  )
{
  SI_PREMEM_CONFIG     *SiPreMemConfig;

  SiPreMemConfig     = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "SiPreMemConfig->Header.GuidHob.Name = %g\n", &SiPreMemConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "SiPreMemConfig->Header.GuidHob.Header.HobLength = 0x%x\n", SiPreMemConfig->Header.GuidHob.Header.HobLength));

  return EFI_SUCCESS;
}

/**
  Add the Si PreMem config block.

  @param[in] ConfigBlockTableAddress    The pointer to add config blocks

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
SiAddConfigBlocksPreMem (
  IN     VOID          *ConfigBlockTableAddress
  )
{
  VOID                 *ConfigBlockPointer;
  EFI_STATUS           Status;
  CONFIG_BLOCK_HEADER  SiPreMemBlock;

  //
  // Initalize SiPreMemBlock
  //
  CopyMem (&(SiPreMemBlock.GuidHob.Name), &gSiPreMemConfigGuid, sizeof (EFI_GUID));
  SiPreMemBlock.GuidHob.Header.HobLength = sizeof (SI_PREMEM_CONFIG);
  SiPreMemBlock.Revision                 = SI_PREMEM_CONFIG_REVISION;
  //
  // Initialize ConfigBlockPointer
  //
  ConfigBlockPointer = (VOID *)&SiPreMemBlock;
  //
  // Add SiPreMemBlock
  //
  DEBUG ((DEBUG_INFO, "gSiPreMemConfigGuid = %g\n", &gSiPreMemConfigGuid));
  DEBUG ((DEBUG_INFO, "SiPreMemBlock->Header.GuidHob.Name = %g\n", &(SiPreMemBlock.GuidHob.Name)));
  Status = AddConfigBlock (ConfigBlockTableAddress, (VOID *) &ConfigBlockPointer);
  ASSERT_EFI_ERROR (Status);

  LoadSiPreMemConfigBlockDefault ((VOID *) ConfigBlockPointer);

  return Status;
}

/**
  SiCreatePreMemConfigBlocks creates the config blocks of Silicon PREMEM Policy.
  It allocates and zero out buffer, and fills in the Intel default settings.

  @param[out] SiPreMemPolicyPpi   The pointer to get Silicon Policy PreMem PPI instance

  @retval EFI_SUCCESS             The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES    Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
SiCreatePreMemConfigBlocks (
  OUT  SI_PREMEM_POLICY_PPI **SiPreMemPolicyPpi
  )
{
  UINT16               TotalBlockSize;
  EFI_STATUS           Status;
  SI_PREMEM_POLICY_PPI *SiPreMemPolicy;
  UINT16               RequiredSize;

  SiPreMemPolicy = NULL;
  //
  // TotalBlockSize = SI, Pch , SA, ME, CPU + individual IPs' config block size
  //
  TotalBlockSize = SiGetConfigBlockTotalSizePreMem () +
                   PcieGetConfigBlockTotalSizePreMem () +
                   PchGetPreMemConfigBlockTotalSize () +
                   MeGetConfigBlockTotalSizePreMem () +
                   SaGetConfigBlockTotalSizePreMem () +
                   CpuGetPreMemConfigBlockTotalSize ();
  // IPs'
  TotalBlockSize += DciPreMemGetConfigBlockTotalSize ();
  TotalBlockSize += HdaPreMemGetConfigBlockTotalSize ();
  TotalBlockSize += PsePreMemGetConfigBlockTotalSize ();
  TotalBlockSize += CpuTraceHubPreMemGetConfigBlockTotalSize ();
  TotalBlockSize += PchTraceHubPreMemGetConfigBlockTotalSize ();
  TotalBlockSize += SmbusPreMemGetConfigBlockTotalSize ();
  TotalBlockSize += WdtPreMemGetConfigBlockTotalSize ();
  TotalBlockSize += GraphicsGetConfigBlockTotalSizePreMem ();
  TotalBlockSize += VtdGetConfigBlockTotalSize ();
  TotalBlockSize += TccGetConfigBlockTotalSize ();

  DEBUG ((DEBUG_INFO, "TotalBlockSize = 0x%x\n", TotalBlockSize));

  RequiredSize = sizeof (CONFIG_BLOCK_TABLE_HEADER) + TotalBlockSize;

  Status = CreateConfigBlockTable (RequiredSize, (VOID *)&SiPreMemPolicy);
  ASSERT_EFI_ERROR (Status);

  //
  // General initialization
  //
  SiPreMemPolicy->TableHeader.Header.Revision = SI_PREMEM_POLICY_REVISION;
  //
  // Add config blocks.
  //
  Status = SiAddConfigBlocksPreMem ((VOID *) SiPreMemPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = PcieAddConfigBlocksPreMem ((VOID *)SiPreMemPolicy);
  ASSERT_EFI_ERROR(Status);
  Status = PchAddPreMemConfigBlocks ((VOID *) SiPreMemPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = MeAddConfigBlocksPreMem ((VOID *) SiPreMemPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = SaAddConfigBlocksPreMem ((VOID *) SiPreMemPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = CpuAddPreMemConfigBlocks ((VOID *) SiPreMemPolicy);
  ASSERT_EFI_ERROR (Status);

  // IpBlock config blocks
  // DCI
  Status = DciPreMemAddConfigBlock ((VOID *) SiPreMemPolicy);
  ASSERT_EFI_ERROR (Status);
  // CPU Trace Hub
  Status = CpuTraceHubPreMemAddConfigBlock ((VOID *) SiPreMemPolicy);
  ASSERT_EFI_ERROR (Status);
  // PCH Trace Hub
  Status = PchTraceHubPreMemAddConfigBlock ((VOID *) SiPreMemPolicy);
  ASSERT_EFI_ERROR (Status);
  // HDA
  Status = HdaPreMemAddConfigBlock ((VOID *) SiPreMemPolicy);
  ASSERT_EFI_ERROR (Status);
  // TCC
  Status = TccPreMemAddConfigBlock ((VOID *) SiPreMemPolicy);
  ASSERT_EFI_ERROR (Status);
  // PSE
  Status = PsePreMemAddConfigBlock ((VOID *) SiPreMemPolicy);
  ASSERT_EFI_ERROR (Status);
  // SMBUS
  Status = SmbusPreMemAddConfigBlock ((VOID *) SiPreMemPolicy);
  ASSERT_EFI_ERROR (Status);
  // WDT
  Status = WdtPreMemAddConfigBlock ((VOID *) SiPreMemPolicy);
  ASSERT_EFI_ERROR (Status);
  // Gfx
  Status = GraphicsAddConfigBlocksPreMem ((VOID *) SiPreMemPolicy);
  ASSERT_EFI_ERROR (Status);
  // VT-D
  Status = VtdAddConfigBlocks ((VOID *) SiPreMemPolicy);
  ASSERT_EFI_ERROR (Status);

  //
  // Assignment for returning SaInitPolicy config block base address
  //
  *SiPreMemPolicyPpi = SiPreMemPolicy;
  return Status;
}

/**
  Print SI PreMem Config block

  @param[in] SiPreMemPolicyPpi          The RC PREMEM Policy PPI instance
**/
VOID
SiPreMemPrintPolicyPpi (
  IN  SI_PREMEM_POLICY_PPI          *SiPreMemPolicyPpi
  )
{
  DEBUG_CODE_BEGIN ();
  EFI_STATUS                        Status;
  SI_PREMEM_CONFIG                  *SiPreMemConfig;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gSiPreMemConfigGuid, (VOID *) &SiPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "---------------------- Si Pre-Mem Config Block Print Begin -----------------\n"));
  DEBUG ((DEBUG_INFO, "PlatformDebugConsent = %x\n", SiPreMemConfig->PlatformDebugConsent));
  DEBUG ((DEBUG_INFO, "---------------------- Si Pre-Mem Config Block Print End -------------------\n"));
  DEBUG_CODE_END ();
}

/**
  SiPreMemInstallPolicyPpi installs SiPreMemPolicyPpi.
  While installed, RC assumes the Policy is ready and finalized. So please update and override
  any setting before calling this function.

  @param[in] SiPreMemPolicyPpi   The pointer to Silicon Policy PPI instance

  @retval EFI_SUCCESS            The policy is installed.
  @retval EFI_OUT_OF_RESOURCES   Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
SiPreMemInstallPolicyPpi (
  IN  SI_PREMEM_POLICY_PPI *SiPolicyPreMemPpi
  )
{
  EFI_STATUS             Status;
  EFI_PEI_PPI_DESCRIPTOR *SiPolicyPreMemPpiDesc;

  SiPolicyPreMemPpiDesc = (EFI_PEI_PPI_DESCRIPTOR *) AllocateZeroPool (sizeof (EFI_PEI_PPI_DESCRIPTOR));
  if (SiPolicyPreMemPpiDesc == NULL) {
    ASSERT (FALSE);
    return EFI_OUT_OF_RESOURCES;
  }

  SiPolicyPreMemPpiDesc->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
  SiPolicyPreMemPpiDesc->Guid  = &gSiPreMemPolicyPpiGuid;
  SiPolicyPreMemPpiDesc->Ppi   = SiPolicyPreMemPpi;

  //
  // Install Silicon Policy PPI
  //
  Status = PeiServicesInstallPpi (SiPolicyPreMemPpiDesc);
  ASSERT_EFI_ERROR (Status);
  return Status;
}

/**
  SiPreMemInstallPolicyReadyPpi installs SiPreMemPolicyReadyPpi.
  While installed, RC assumes the Policy is ready and finalized. So please update and override
  any setting before calling this function.

  @retval EFI_SUCCESS            The policy is installed.
  @retval EFI_OUT_OF_RESOURCES   Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
SiPreMemInstallPolicyReadyPpi (
  VOID
  )
{
  EFI_STATUS             Status;
  EFI_PEI_PPI_DESCRIPTOR *SiPolicyReadyPreMemPpiDesc;
  SI_PREMEM_POLICY_PPI    *SiPreMemPolicyPpi;

  SiPolicyReadyPreMemPpiDesc = (EFI_PEI_PPI_DESCRIPTOR *) AllocateZeroPool (sizeof (EFI_PEI_PPI_DESCRIPTOR));
  if (SiPolicyReadyPreMemPpiDesc == NULL) {
    ASSERT (FALSE);
    return EFI_OUT_OF_RESOURCES;
  }

  SiPolicyReadyPreMemPpiDesc->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
  SiPolicyReadyPreMemPpiDesc->Guid  = &gSiPreMemPolicyReadyPpiGuid;
  SiPolicyReadyPreMemPpiDesc->Ppi   = NULL;

  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **)&SiPreMemPolicyPpi
             );

  if (Status == EFI_SUCCESS) {
    //
    // Print SI PreMem config block
    //
    SiPreMemPrintPolicyPpi (SiPreMemPolicyPpi);
    //
    // Print PCIe PreMem config block
    //
    PciePreMemPrintPolicyPpi (SiPreMemPolicyPpi);
    //
    // Print PCH PreMem config blocks
    //
    PchPreMemPrintPolicyPpi (SiPreMemPolicyPpi);
    //
    // Print ME PreMem config blocks
    //
    MePrintPolicyPpiPreMem (SiPreMemPolicyPpi);
    //
    // Print SA PreMem config blocks
    //
    SaPrintPolicyPpiPreMem (SiPreMemPolicyPpi);
    //
    // Print SA IPs' PreMem config blocks
    //
    TccPreMemPrintConfig (SiPreMemPolicyPpi);
    GraphicsPrintPolicyPpiPreMem (SiPreMemPolicyPpi);
    VtdPrintPolicyPpi (SiPreMemPolicyPpi);
    //
    // Print CPU PreMem config blocks
    //
    CpuPreMemPrintPolicy (SiPreMemPolicyPpi);
    DciPreMemPrintConfig (SiPreMemPolicyPpi);
    HdaPreMemPrintConfig (SiPreMemPolicyPpi);
    PsePreMemPrintConfig (SiPreMemPolicyPpi);
    CpuTraceHubPreMemPrintConfig (SiPreMemPolicyPpi);
    PchTraceHubPreMemPrintConfig (SiPreMemPolicyPpi);
    SmbusPreMemPrintConfig (SiPreMemPolicyPpi);
    WdtPreMemPrintConfig (SiPreMemPolicyPpi);
  }
  //
  // Install PreMem Silicon Policy Ready PPI
  //
  Status = PeiServicesInstallPpi (SiPolicyReadyPreMemPpiDesc);
  ASSERT_EFI_ERROR (Status);
  return Status;
}

/**
  Calculate total trace buffer size and make it power of two, eliminate the total size within 512MB
  Please ensure CPU and PCH trace hub policies are configured before calling.

  @param[in] PlatformDebugConsent            Platform Debug Consent
  @param[in] CpuTraceHubMode                 CPU Trace Hub Mode
  @param[in] CpuTraceHubMemReg0Size          CPU Trace Hub Memory Region 0
  @param[in] CpuTraceHubMemReg1Size          CPU Trace Hub Memory Region 1
  @param[in] PchTraceHubMode                 PCH Trace Hub Mode
  @param[in] PchTraceHubMemReg0Size          PCH Trace Hub Memory Region 0
  @param[in] PchTraceHubMemReg1Size          PCH Trace Hub Memory Region 1

  @retval UINT32                             Total size of trace buffers
**/
UINT32
EFIAPI
TraceHubCalculateTotalBufferSize (
  IN UINT8         PlatformDebugConsent,
  IN UINT8         CpuTraceHubMode,
  IN UINT8         CpuTraceHubMemReg0Size,
  IN UINT8         CpuTraceHubMemReg1Size,
  IN UINT8         PchTraceHubMode,
  IN UINT8         PchTraceHubMemReg0Size,
  IN UINT8         PchTraceHubMemReg1Size
  )
{
  UINT32           TotalTraceBufferSize;
  UINT32           TraceHubBufferSizeTab[8] = {0, SIZE_1MB, SIZE_8MB, SIZE_64MB, SIZE_128MB, SIZE_256MB, SIZE_512MB, SIZE_1GB};

  TotalTraceBufferSize = 0;

  if ((CpuTraceHubMemReg0Size >= TraceBufferMax) || (CpuTraceHubMemReg1Size >= TraceBufferMax) ||
      (PchTraceHubMemReg0Size >= TraceBufferMax) || (PchTraceHubMemReg1Size >= TraceBufferMax)
      ) {
    DEBUG ((DEBUG_ERROR, "Illegal Trace Hub size policy input, should be within the range 0~6, skip allocate trace buffers\n"));
    return 0;
  }
  //
  // If Platform Debug Consent is enabled, assign sum of default buffer size for CPU and PCH trace hubs.
  // PCH and CPU TH default size per mem region is 8MB, and there are 2 memory regions per each. It totally consumes 32 MB with default size.
  //
  if ((PlatformDebugConsent != ProbeTypeDisabled) && (PlatformDebugConsent != ProbeTypeManual)) {
    TotalTraceBufferSize = SIZE_8MB * 4;
  } else {
    //
    // Trace Hub mode is not disabled or SCRPD0[24] is set, reserve trace hub memory
    //
    if ((CpuTraceHubMode != TraceHubModeDisabled) || (IsDebuggerInUse (CpuTraceHub))) {
      TotalTraceBufferSize += TraceHubBufferSizeTab[CpuTraceHubMemReg0Size] + TraceHubBufferSizeTab[CpuTraceHubMemReg1Size];
    }
    if ((PchTraceHubMode != TraceHubModeDisabled) || (IsDebuggerInUse (PchTraceHub))) {
      TotalTraceBufferSize += TraceHubBufferSizeTab[PchTraceHubMemReg0Size] + TraceHubBufferSizeTab[PchTraceHubMemReg1Size];
    }
  }
  if (TotalTraceBufferSize > SIZE_512MB) {
    DEBUG ((DEBUG_ERROR, "Total Trace Hub Memory size over limited 512MB, reset trace hub memory region size to default\n"));
    TotalTraceBufferSize = SIZE_8MB * 4;
  }
  //
  // make the total size to be powoer of 2, to ensure use least MTRR when set cache
  //
  if (TotalTraceBufferSize > GetPowerOfTwo32 (TotalTraceBufferSize)) {
    TotalTraceBufferSize = 2 * GetPowerOfTwo32 (TotalTraceBufferSize);
  }
  return TotalTraceBufferSize;
}
