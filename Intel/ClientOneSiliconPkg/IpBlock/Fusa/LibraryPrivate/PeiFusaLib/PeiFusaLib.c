/** @file
  Initilize FUSA device in PEI

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
#include <Register/SaRegsHostBridge.h>
#include <Ppi/SiPolicy.h>
#include <FusaConfig.h>
#include <Register/FusaRegs.h>
#include <Register/IgdRegs.h>
#include <Library/PciSegmentLib.h>
#include <Library/PchPcrLib.h>
#include <Library/IoLib.h>
#include <Library/PsfLib.h>

typedef union {
  struct {
    UINT32  Low;
    UINT32  High;
  } Data32;
  UINT64 Data;
} UINT64_STRUCT;

/**
  Lock FUSA Registers After BIOS_DONE.
**/
VOID
FusaRegisterLock (
  VOID
  )
{
#if FixedPcdGet8(PcdEmbeddedEnable) == 0x1
  UINT32      Data32H;
  UINT64                  McD2BaseAddress;
  UINTN                   GttMmAdr;

  McD2BaseAddress   = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, 0);
  GttMmAdr = (PciSegmentRead32 (McD2BaseAddress + R_SA_IGD_GTTMMADR)) & 0xFFFFFFF0;
  //lock the FUSA lock bit
  Data32H = Data32H | 0x00000001;
  MmioWrite32 (GttMmAdr + R_SA_GTMMADR_DE_FUSA_PARITY_CTRL_OFFSET, Data32H);
  Data32H = MmioRead32(GttMmAdr + R_SA_GTMMADR_DE_FUSA_PARITY_CTRL_OFFSET);
  DEBUG ((DEBUG_INFO, "Lock FUSA Display Lock Bit 0x%x\n", Data32H));

  Data32H = Data32H | 0x00000001;
  MmioWrite32 (GttMmAdr + R_SA_GTMMADR_SF_CTL_0, Data32H);
  Data32H = MmioRead32(GttMmAdr + R_SA_GTMMADR_SF_CTL_0);
  DEBUG ((DEBUG_INFO, "Lock FUSA Graphics Lock Bit 0x%x\n", Data32H));
#endif
}

/**
  FusaOverrideProgramming: Override the Display FUSA register for enabling/disabling FUSA features

  @param[in] SiPolicyPpi        The SI Policy PPI instance
  @retval     EFI_SUCCESS     - Display workarounds done
**/
EFI_STATUS
DisplayFusaOverrideProgramming (
   IN  SI_POLICY_PPI    *SiPolicy
  )
{
#if FixedPcdGet8(PcdEmbeddedEnable) == 0x1
  UINT64                  McD0BaseAddress;
  UINT64                  McD2BaseAddress;
  UINTN                   GttMmAdr;
  UINT32                  Data64;
  UINT32                  Data32H;
  FUSA_CONFIG             *FusaConfig;
  EFI_STATUS              Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gFusaConfigGuid, (VOID *) &FusaConfig);
  ASSERT_EFI_ERROR (Status);

  McD0BaseAddress   = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, 0);
  McD2BaseAddress   = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, 0);
  GttMmAdr = (PciSegmentRead32 (McD2BaseAddress + R_SA_IGD_GTTMMADR)) & 0xFFFFFFF0;

  DEBUG ((DEBUG_INFO, "Display FUSA override Function \n"));
  ///
  /// unlock the FUSA lock bit
  ///
  Data32H = MmioRead32(GttMmAdr + R_SA_GTMMADR_DE_FUSA_PARITY_CTRL_OFFSET);
  if (Data32H && 0x00000001) {
    Data32H = Data32H| B_SA_GTMMADR_DE_FUSA_IOSF_PARITY_CTL_LOCK_BIT;
    MmioWrite32 (GttMmAdr + R_SA_GTMMADR_DE_FUSA_PARITY_CTRL_OFFSET, Data32H);
  }
  if (FusaConfig->DisplayFusaConfigEnable == 1){
    DEBUG ((DEBUG_INFO, "Enable Fusa on Display\n"));
    Data64 = PciSegmentRead32(McD0BaseAddress + R_SA_PCI_DEVICECTL_OFFSET);
    Data64 = Data64 | ( BIT2 | BIT1 | BIT0);
    PciSegmentWrite32(McD0BaseAddress + R_SA_PCI_DEVICECTL_OFFSET, Data64 );

    Data32H = MmioRead32(GttMmAdr + R_SA_GTMMADR_DE_FUSA_PARITY_CTRL_OFFSET )| ( B_SA_GTMMADR_DE_FUSA_IOSF_PARITY_CMD_BIT | B_SA_GTMMADR_DE_FUSA_IOSF_PARITY_DATA_BIT | B_SA_GTMMADR_DE_FUSA_DIP_PARITY_CMD_BIT | B_SA_GTMMADR_DE_FUSA_DIP_PARITY_DATA_BIT);
    MmioWrite32 (GttMmAdr + R_SA_GTMMADR_DE_FUSA_PARITY_CTRL_OFFSET, Data32H);
    Data32H = MmioRead32(GttMmAdr + R_SA_GTMMADR_DISPLAY_ERR_COR_OFFSET )| 0xFFFF0000;
    MmioWrite32 (GttMmAdr + R_SA_GTMMADR_DISPLAY_ERR_COR_OFFSET, Data32H);
    Data32H = MmioRead32(GttMmAdr + R_SA_GTMMADR_DISPLAY_ERR_NONFATAL_OFFSET )| 0xFFFF0000;
    MmioWrite32 (GttMmAdr + R_SA_GTMMADR_DISPLAY_ERR_NONFATAL_OFFSET, Data32H);
    Data32H = MmioRead32(GttMmAdr + R_SA_GTMMADR_DISPLAY_ERR_FATAL_OFFSET )| 0xFFFF0000;
    MmioWrite32 (GttMmAdr + R_SA_GTMMADR_DISPLAY_ERR_FATAL_OFFSET, Data32H);
  } else {
    DEBUG ((DEBUG_INFO, "Disable Fusa on Display\n"));
    Data64 = PciSegmentRead32(McD0BaseAddress + R_SA_PCI_DEVICECTL_OFFSET);
    Data64 = Data64 & ~( BIT2 | BIT1 | BIT0);
    PciSegmentWrite32(McD0BaseAddress + R_SA_PCI_DEVICECTL_OFFSET, Data64 );

    Data32H = MmioRead32(GttMmAdr + R_SA_GTMMADR_DE_FUSA_PARITY_CTRL_OFFSET )& ~( B_SA_GTMMADR_DE_FUSA_IOSF_PARITY_CMD_BIT | B_SA_GTMMADR_DE_FUSA_IOSF_PARITY_DATA_BIT | B_SA_GTMMADR_DE_FUSA_DIP_PARITY_CMD_BIT | B_SA_GTMMADR_DE_FUSA_DIP_PARITY_DATA_BIT);
    MmioWrite32 (GttMmAdr + R_SA_GTMMADR_DE_FUSA_PARITY_CTRL_OFFSET, Data32H);
    Data32H = MmioRead32(GttMmAdr + R_SA_GTMMADR_DISPLAY_ERR_COR_OFFSET )& 0x00001111;
    MmioWrite32 (GttMmAdr + R_SA_GTMMADR_DISPLAY_ERR_COR_OFFSET, Data32H);
    Data32H = MmioRead32(GttMmAdr + R_SA_GTMMADR_DISPLAY_ERR_NONFATAL_OFFSET )& 0x00001111;
    MmioWrite32 (GttMmAdr + R_SA_GTMMADR_DISPLAY_ERR_NONFATAL_OFFSET, Data32H);
    Data32H = MmioRead32(GttMmAdr + R_SA_GTMMADR_DISPLAY_ERR_FATAL_OFFSET )& 0x00001111;
    MmioWrite32 (GttMmAdr + R_SA_GTMMADR_DISPLAY_ERR_FATAL_OFFSET, Data32H);
  }
#endif
  return EFI_SUCCESS;
}

/**
  FusaOverrideProgramming: Override the Graphics FUSA register for enabling/disabling FUSA features

  @param[in] SiPolicyPpi        The SI Policy PPI instance
  @retval     EFI_SUCCESS     - Display workarounds done
**/
EFI_STATUS
GraphicsFusaOverrideProgramming (
   IN  SI_POLICY_PPI    *SiPolicy
  )
{
#if FixedPcdGet8(PcdEmbeddedEnable) == 0x1
  UINT64                  McD0BaseAddress;
  UINT64                  McD2BaseAddress;
  UINTN                   GttMmAdr;
  UINT32                  Data64;
  UINT32                  Data32H;
  FUSA_CONFIG             *FusaConfig;
  EFI_STATUS              Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gFusaConfigGuid, (VOID *) &FusaConfig);
  ASSERT_EFI_ERROR (Status);

  McD0BaseAddress   = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, 0);
  McD2BaseAddress   = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, 0);
  GttMmAdr = (PciSegmentRead32 (McD2BaseAddress + R_SA_IGD_GTTMMADR)) & 0xFFFFFFF0;

  DEBUG ((DEBUG_INFO, "Graphics FUSA override Function \n"));
  ///
  /// unlock the FUSA lock bit
  ///
  Data32H = MmioRead32(GttMmAdr + R_SA_GTMMADR_SF_CTL_0);
  if (Data32H && 0x00000001) {
    Data32H = Data32H| B_SA_GTMMADR_DE_FUSA_SF_CTL_LOCK_BIT ;
    MmioWrite32 (GttMmAdr + R_SA_GTMMADR_SF_CTL_0, Data32H);
  }
  if (FusaConfig->GraphicFusaConfigEnable == 1){
    DEBUG ((DEBUG_INFO, "Enable Fusa on Graphics\n"));
    Data64 = PciSegmentRead32(McD0BaseAddress + R_SA_PCI_DEVICECTL_OFFSET);
    Data64 = Data64 | ( BIT2 | BIT1 | BIT0);
    PciSegmentWrite32(McD0BaseAddress + R_SA_PCI_DEVICECTL_OFFSET, Data64 );

    Data32H = MmioRead32(GttMmAdr + R_SA_GTMMADR_GT_ERR_COR_OFFSET )| 0xFFFF0000;
    MmioWrite32 (GttMmAdr + R_SA_GTMMADR_GT_ERR_COR_OFFSET, Data32H);
    Data32H = MmioRead32(GttMmAdr + R_SA_GTMMADR_GT_ERR_NONFATAL_OFFSET )| 0xFFFF0000;
    MmioWrite32 (GttMmAdr + R_SA_GTMMADR_GT_ERR_NONFATAL_OFFSET, Data32H);
    Data32H = MmioRead32(GttMmAdr + R_SA_GTMMADR_GT_ERR_FATAL_OFFSET )| 0xFFFF0000;
    MmioWrite32 (GttMmAdr + R_SA_GTMMADR_GT_ERR_FATAL_OFFSET, Data32H);
  }
  else{
    DEBUG ((DEBUG_INFO, "Disable Fusa on Graphics\n"));
    Data64 = PciSegmentRead32(McD0BaseAddress + R_SA_PCI_DEVICECTL_OFFSET);
    Data64 = Data64 & ~( BIT2 | BIT1 | BIT0);
    PciSegmentWrite32(McD0BaseAddress + R_SA_PCI_DEVICECTL_OFFSET, Data64 );

    Data32H = MmioRead32(GttMmAdr + R_SA_GTMMADR_GT_ERR_COR_OFFSET )& 0x00001111;
    MmioWrite32 (GttMmAdr + R_SA_GTMMADR_GT_ERR_COR_OFFSET, Data32H);
    Data32H = MmioRead32(GttMmAdr + R_SA_GTMMADR_GT_ERR_NONFATAL_OFFSET )& 0x00001111;
    MmioWrite32 (GttMmAdr + R_SA_GTMMADR_GT_ERR_NONFATAL_OFFSET, Data32H);
    Data32H = MmioRead32(GttMmAdr + R_SA_GTMMADR_GT_ERR_FATAL_OFFSET )& 0x00001111;
    MmioWrite32 (GttMmAdr + R_SA_GTMMADR_GT_ERR_FATAL_OFFSET, Data32H);
  }
#endif
  return EFI_SUCCESS;
}

/**
  FusaOverrideProgramming: Override the Opio FUSA register for enabling/disabling FUSA features

  @param[in] SiPolicyPpi        The SI Policy PPI instance
  @retval     EFI_SUCCESS     - Display workarounds done
**/
EFI_STATUS
OpioFusaOverrideProgramming (
   IN  SI_POLICY_PPI    *SiPolicy
  )
{
#if FixedPcdGet8(PcdEmbeddedEnable) == 0x1
  UINT32                      Data32;
  UINT64_STRUCT               DmiBar;
  UINT64                      McD0BaseAddress;
  FUSA_CONFIG                 *FusaConfig;
  EFI_STATUS                  Status;
  UINTN                       DmiBarAddress;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gFusaConfigGuid, (VOID *) &FusaConfig);
  ASSERT_EFI_ERROR (Status);

  McD0BaseAddress    = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, 0);
  DmiBar.Data32.High = PciSegmentRead32 (McD0BaseAddress + R_SA_DMIBAR + 4);
  DmiBar.Data32.Low  =  PciSegmentRead32 (McD0BaseAddress + R_SA_DMIBAR);
  DmiBar.Data       &= (UINT64) ~BIT0;

  DmiBarAddress = (UINTN)DmiBar.Data;

  DEBUG ((DEBUG_INFO, "OPIO FUSA override Fuction \n"));
  Data32 = MmioRead32(DmiBarAddress + R_SA_DMIBAR_FUSA_E2EPARITY_CTL_OFFSET );
  if (FusaConfig-> OpioFusaConfigEnable == 1){
    DEBUG ((DEBUG_INFO, "Enable Fusa on Opio\n"));
    Data32 = Data32 | ( B_SA_DMIBAR_PARITY_GEN_EN | B_SA_DMIBAR_DATA_PARITY_FATAL_CFG | B_SA_DMIBAR_DATA_PARITY_FATAL_OPI_CFG);
    MmioWrite32 (DmiBarAddress+ R_SA_DMIBAR_FUSA_E2EPARITY_CTL_OFFSET, Data32);
  }
  else{
    DEBUG ((DEBUG_INFO, "Disable Fusa on Opio\n"));
    Data32 = Data32 & ~( B_SA_DMIBAR_PARITY_GEN_EN | B_SA_DMIBAR_DATA_PARITY_FATAL_CFG | B_SA_DMIBAR_DATA_PARITY_FATAL_OPI_CFG);
    MmioWrite32 ((DmiBarAddress + R_SA_DMIBAR_FUSA_E2EPARITY_CTL_OFFSET), Data32);
  }
#endif
  return EFI_SUCCESS;
}


/**
  Enable Fusa support in PSF.
**/
VOID
PchPsfEnableFusa (
  VOID
  )
{
#if FixedPcdGet8(PcdEmbeddedEnable) == 0x1
  UINT32          PsfTableIndex;
  PSF_SEGMENT     *PsfTable;
  UINT32          PsfTableSize;
  UINT32          Data32;

  PsfSegments (&PsfTable, &PsfTableSize);
  DEBUG ((DEBUG_INFO, "Enable Fusa on PSF \n"));
  for (PsfTableIndex = 0; PsfTableIndex < PsfTableSize; PsfTableIndex++) {
    Data32 = PchPcrRead32 (PsfTable[PsfTableIndex].SbPid, R_PCH_PSF_PCR_GLOBAL_CONFIG);
    PchPcrAndThenOr32 (
      PsfTable[PsfTableIndex].SbPid,
      R_PCH_PSF_PCR_GLOBAL_CONFIG,
      ~0u,
      B_PCH_PSF_PCR_GLOBAL_CONFIG_ENCMPADET1
      );

   PchPcrAndThenOr32 (
      PsfTable[PsfTableIndex].SbPid,
      R_PCH_PSF_PCR_GLOBAL_CONFIG,
      ~0u,
      B_PCH_PSF_PCR_GLOBAL_CONFIG_ENCMPADET2
      );

   Data32 = PchPcrRead32 (PsfTable[PsfTableIndex].SbPid, R_PCH_PSF_PCR_GLOBAL_CONFIG);
  }
#endif
}

/**
  Disable Fusa support in PSF.
**/
VOID
PchPsfDisableFusa (
  VOID
  )
{
#if FixedPcdGet8(PcdEmbeddedEnable) == 0x1
  UINT32          PsfTableIndex;
  PSF_SEGMENT     *PsfTable;
  UINT32          PsfTableSize;
  UINT32          Data32;

  PsfSegments (&PsfTable, &PsfTableSize);
  DEBUG ((DEBUG_INFO, "Disable Fusa on PSF\n" ));
  for (PsfTableIndex = 0; PsfTableIndex < PsfTableSize; PsfTableIndex++) {
    Data32 = PchPcrRead32 (PsfTable[PsfTableIndex].SbPid, R_PCH_PSF_PCR_GLOBAL_CONFIG);
    PchPcrAndThenOr32 (
      PsfTable[PsfTableIndex].SbPid,
      R_PCH_PSF_PCR_GLOBAL_CONFIG,
      (UINT32)~B_PCH_PSF_PCR_GLOBAL_CONFIG_ENCMPADET1,
      0
      );
    PchPcrAndThenOr32 (
      PsfTable[PsfTableIndex].SbPid,
      R_PCH_PSF_PCR_GLOBAL_CONFIG,
      (UINT32)~B_PCH_PSF_PCR_GLOBAL_CONFIG_ENCMPADET2,
      0
      );

   Data32 = PchPcrRead32 (PsfTable[PsfTableIndex].SbPid, R_PCH_PSF_PCR_GLOBAL_CONFIG);
  }
#endif
}

/**
  FusaOverrideProgramming: Override the Psf FUSA register for enabling/disabling FUSA features

  @param[in] SiPolicyPpi        The SI Policy PPI instance
  @retval     EFI_SUCCESS     - Display workarounds done
**/
EFI_STATUS
PsfFusaOverrideProgramming (
  IN  SI_POLICY_PPI    *SiPolicy
  )
{
#if FixedPcdGet8(PcdEmbeddedEnable) == 0x1
  FUSA_CONFIG                 *FusaConfig;
  EFI_STATUS                  Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gFusaConfigGuid, (VOID *) &FusaConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "PSF FUSA override Function \n"));

  if (FusaConfig-> PsfFusaConfigEnable == 1){
    PchPsfEnableFusa();
  } else {
    PchPsfDisableFusa();
  }
#endif
  return EFI_SUCCESS;
}