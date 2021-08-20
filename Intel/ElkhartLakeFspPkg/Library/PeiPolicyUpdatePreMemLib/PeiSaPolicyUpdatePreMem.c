/** @file
  Do Platform Stage System Agent initialization.

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

#include <FspEas.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PeiSaPolicyLib.h>
#include <Library/FspCommonLib.h>
#include <Library/DebugLib.h>
#include <FspmUpd.h>
#include <Library/PreSiliconEnvDetectLib.h>
#include <Library/CpuPcieInfoLib.h>

/**
  UpdatePeiSaPolicy performs SA PEI Policy initialization in pre-memory

  @param[in, out] SiPreMemPolicyPpi       SI_PREMEM_POLICY_PPI
  @param[in]      FspmUpd                 The pointer of FspmUpd

  @retval EFI_SUCCESS              The policy is installed and initialized.
**/
EFI_STATUS
FspUpdatePeiSaPolicyPreMem (
  IN OUT SI_PREMEM_POLICY_PPI       *SiPreMemPolicyPpi,
  IN     FSPM_UPD                   *FspmUpd
  )
{
  EFI_STATUS                    Status;
  SA_MISC_PEI_PREMEM_CONFIG     *MiscPeiPreMemConfig;
  MEMORY_CONFIG_NO_CRC          *MemConfigNoCrc;
  GRAPHICS_PEI_PREMEM_CONFIG    *GtPreMemConfig;
  VTD_CONFIG                    *Vtd;
  MEMORY_CONFIGURATION          *MemConfig;
#if FixedPcdGetBool(PcdCpuPcieEnable) == 1
  PCIE_PEI_PREMEM_CONFIG        *PciePeiPreMemConfig;
#endif
  PRAM_PREMEM_CONFIG            *PramPreMemConfig;
#if FixedPcdGetBool(PcdHgEnable) == 1
  HYBRID_GRAPHICS_CONFIG        *HgGpioData;
#endif
#if FixedPcdGetBool(PcdCpuPcieEnable) == 1
  CPU_PCIE_RP_PREMEM_CONFIG     *CpuPcieRpPreMemConfig;
#endif
  CPU_TRACE_HUB_PREMEM_CONFIG   *CpuTraceHubPreMemConfig;
  FSPM_UPD                      *FspmUpdDataPtr;
  UINT8                         Index;
  DEBUG ((DEBUG_INFO | DEBUG_INIT, "FSP UpdatePeiSaPolicyPreMem\n"));

  FspmUpdDataPtr = (FSPM_UPD *) GetFspMemoryInitUpdDataPointer ();
  MiscPeiPreMemConfig = NULL;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gSaMiscPeiPreMemConfigGuid, (VOID *) &MiscPeiPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  GtPreMemConfig = NULL;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gGraphicsPeiPreMemConfigGuid, (VOID *) &GtPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  MemConfig = NULL;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gMemoryConfigGuid, (VOID *) &MemConfig);
  ASSERT_EFI_ERROR (Status);

  Vtd = NULL;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gVtdConfigGuid, (VOID *)&Vtd);
  ASSERT_EFI_ERROR (Status);

  MemConfigNoCrc = NULL;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gMemoryConfigNoCrcGuid, (VOID *) &MemConfigNoCrc);
  ASSERT_EFI_ERROR (Status);

#if FixedPcdGetBool(PcdCpuPcieEnable) == 1
  PciePeiPreMemConfig = NULL;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuPciePeiPreMemConfigGuid, (VOID *) &PciePeiPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  CpuPcieRpPreMemConfig = NULL;
  Status = GetConfigBlock ((VOID *)SiPreMemPolicyPpi, &gCpuPcieRpPrememConfigGuid, (VOID *)&CpuPcieRpPreMemConfig);
  ASSERT_EFI_ERROR(Status);
#endif
#if FixedPcdGetBool(PcdHgEnable) == 1
  HgGpioData = NULL;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gHybridGraphicsConfigGuid, (VOID *) &HgGpioData);
  ASSERT_EFI_ERROR (Status);
#endif
  CpuTraceHubPreMemConfig = NULL;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuTraceHubPreMemConfigGuid, (VOID *) &CpuTraceHubPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  PramPreMemConfig = NULL;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gPramPreMemConfigGuid, (VOID *) &PramPreMemConfig);
  ASSERT_EFI_ERROR (Status);


  //
  // Update ConfigBlock: MemConfigNoCrc
  //

  //
  // Update SpdData only if SpdAddressTable is zero for each DIMM slot
  //
  if (((VOID *)FspmUpd->FspmConfig.MemorySpdPtr00 != NULL) && (FspmUpd->FspmConfig.SpdAddressTable[0] == 0)) {
    CopyMem ((VOID *) MemConfigNoCrc->SpdData->SpdData[0][0], (VOID *)FspmUpd->FspmConfig.MemorySpdPtr00, FspmUpd->FspmConfig.MemorySpdDataLen);
  } else {
    ZeroMem ((VOID *)MemConfigNoCrc->SpdData->SpdData[0][0], sizeof(MEM_CFG_MAX_SPD_SIZE));
  }

  if (((VOID *)FspmUpd->FspmConfig.MemorySpdPtr01 != NULL) && (FspmUpd->FspmConfig.SpdAddressTable[1] == 0)) {
    CopyMem ((VOID *) MemConfigNoCrc->SpdData->SpdData[0][1], (VOID*)FspmUpd->FspmConfig.MemorySpdPtr01, FspmUpd->FspmConfig.MemorySpdDataLen);
  } else {
    ZeroMem ((VOID *)MemConfigNoCrc->SpdData->SpdData[0][1], sizeof(MEM_CFG_MAX_SPD_SIZE));
  }

  if (((VOID *)FspmUpd->FspmConfig.MemorySpdPtr10 != NULL) && (FspmUpd->FspmConfig.SpdAddressTable[2] == 0)) {
    CopyMem ((VOID *) MemConfigNoCrc->SpdData->SpdData[1][0], (VOID*)FspmUpd->FspmConfig.MemorySpdPtr10, FspmUpd->FspmConfig.MemorySpdDataLen);
  } else {
    ZeroMem ((VOID *)MemConfigNoCrc->SpdData->SpdData[1][0], sizeof(MEM_CFG_MAX_SPD_SIZE));
  }

  if (((VOID *)FspmUpd->FspmConfig.MemorySpdPtr11 != NULL) && (FspmUpd->FspmConfig.SpdAddressTable[3] == 0)) {
    CopyMem ((VOID *) MemConfigNoCrc->SpdData->SpdData[1][1], (VOID*)FspmUpd->FspmConfig.MemorySpdPtr11, FspmUpd->FspmConfig.MemorySpdDataLen);
  } else {
    ZeroMem ((VOID *) MemConfigNoCrc->SpdData->SpdData[1][1], sizeof(MEM_CFG_MAX_SPD_SIZE));
  }

  if (FspmUpd->FspmConfig.DqByteMapCh0 != NULL) {
    CopyMem ((VOID *) MemConfigNoCrc->DqByteMap->DqByteMap[0], &FspmUpd->FspmConfig.DqByteMapCh0[0], 12);
  }

  if (FspmUpd->FspmConfig.DqByteMapCh1 != NULL) {
    CopyMem ((VOID *) MemConfigNoCrc->DqByteMap->DqByteMap[1] , &FspmUpd->FspmConfig.DqByteMapCh1[0], 12);
  }

  if (FspmUpd->FspmConfig.DqsMapCpu2DramCh0 != NULL) {
    CopyMem ((VOID *) MemConfigNoCrc->DqsMap->DqsMapCpu2Dram[0], &FspmUpd->FspmConfig.DqsMapCpu2DramCh0[0], 8);
  }

  if (FspmUpd->FspmConfig.DqsMapCpu2DramCh1 != NULL) {
    CopyMem ((VOID *) MemConfigNoCrc->DqsMap->DqsMapCpu2Dram[1], &FspmUpd->FspmConfig.DqsMapCpu2DramCh1[0], 8);
  }

  if (FspmUpd->FspmConfig.RcompResistor != NULL) {
    CopyMem ((VOID *) &(MemConfigNoCrc->RcompData->RcompResistor[0]), (VOID *) &FspmUpd->FspmConfig.RcompResistor[0], 6);
  }

  if (FspmUpd->FspmConfig.RcompTarget != NULL) {
    CopyMem ((VOID *) &(MemConfigNoCrc->RcompData->RcompTarget[0]), (VOID *) &FspmUpd->FspmConfig.RcompTarget[0], 10);
  }

  MemConfigNoCrc->PlatformMemorySize = FspmUpd->FspmConfig.PlatformMemorySize;
  MemConfigNoCrc->SerialDebugLevel   = FspmUpd->FspmConfig.PcdSerialDebugLevel;
  MemConfigNoCrc->CleanMemory        = FspmUpd->FspmConfig.CleanMemory;
  MemConfigNoCrc->MemTestOnWarmBoot  = FspmUpd->FspmConfig.MemTestOnWarmBoot;

  //
  // Update ConfigBlock: MemConfig
  //
  MemConfig->MrcTrainOnWarm         = FspmUpd->FspmConfig.MrcTrainOnWarm;
  MemConfig->SmramMask              = FspmUpd->FspmConfig.SmramMask;
  MemConfig->DqPinsInterleaved      = FspmUpd->FspmConfig.DqPinsInterleaved;
  MemConfig->MrcTimeMeasure         = FspmUpd->FspmConfig.MrcTimeMeasure;
  MemConfig->MrcFastBoot            = FspmUpd->FspmConfig.MrcFastBoot;
  MemConfig->SaGv                   = FspmUpd->FspmConfig.SaGv;
  MemConfig->DdrFreqLimit           = FspmUpd->FspmConfig.DdrFreqLimit;

  MemConfig->DisableDimmChannel[0]  = FspmUpd->FspmConfig.DisableDimmChannel0;
  MemConfig->DisableDimmChannel[1]  = FspmUpd->FspmConfig.DisableDimmChannel1;

  MemConfig->MrcSafeConfig          = FspmUpd->FspmConfig.MrcSafeConfig;
  MemConfig->Lp4DqsOscEn            = FspmUpd->FspmConfig.Lp4DqsOscEn;
  MemConfig->TrainTrace             = FspmUpd->FspmConfig.TrainTrace;
  MemConfig->RmtPerTask             = FspmUpd->FspmConfig.RmtPerTask;
  MemConfig->FreqSaGvLow            = FspmUpd->FspmConfig.FreqSaGvLow;
  MemConfig->FreqSaGvMid            = FspmUpd->FspmConfig.FreqSaGvMid;
  MemConfig->DdrSpeedControl        = FspmUpd->FspmConfig.DdrSpeedControl;
  MemConfig->SaGvLowGear2           = FspmUpd->FspmConfig.SaGvLowGear2;
  MemConfig->SaGvMidGear2           = FspmUpd->FspmConfig.SaGvMidGear2;
  MemConfig->SaGvHighGear2          = FspmUpd->FspmConfig.SaGvHighGear2;
  MemConfig->ScramblerSupport       = FspmUpd->FspmConfig.ScramblerSupport;
  MemConfig->SafeMode               = FspmUpd->FspmConfig.SafeMode;
  MemConfig->Ddr4OneDpc             = FspmUpd->FspmConfig.Ddr4OneDpc;
  MemConfig->LowSupplyEnData        = FspmUpd->FspmConfig.LowSupplyEnData;
  MemConfig->LowSupplyEnCcc         = FspmUpd->FspmConfig.LowSupplyEnCcc;
  //
  // Enabling Probeless Trace will need to enable IED together
  //
  MemConfig->ProbelessTrace = FspmUpd->FspmConfig.ProbelessTrace;
  MemConfig->CaVrefConfig = FspmUpd->FspmConfig.CaVrefConfig;

  if (MiscPeiPreMemConfig != NULL) {
    MiscPeiPreMemConfig->IedSize = FspmUpd->FspmConfig.IedSize;
    MiscPeiPreMemConfig->UserBd = FspmUpd->FspmConfig.UserBd;
    MiscPeiPreMemConfig->EnableAbove4GBMmio = FspmUpd->FspmConfig.EnableAbove4GBMmio;
  }

  MemConfig->SpdProfileSelected      = FspmUpd->FspmConfig.SpdProfileSelected;
  MemConfig->VddVoltage              = FspmUpd->FspmConfig.VddVoltage;
  MemConfig->RefClk                  = FspmUpd->FspmConfig.RefClk;
  MemConfig->Ratio                   = FspmUpd->FspmConfig.Ratio;
  MemConfig->tCL                     = FspmUpd->FspmConfig.tCL;
  MemConfig->tCWL                    = FspmUpd->FspmConfig.tCWL;
  MemConfig->tFAW                    = FspmUpd->FspmConfig.tFAW;
  MemConfig->tRAS                    = FspmUpd->FspmConfig.tRAS;
  MemConfig->tRCDtRP                 = FspmUpd->FspmConfig.tRCDtRP;
  MemConfig->tREFI                   = FspmUpd->FspmConfig.tREFI;
  MemConfig->tRFC                    = FspmUpd->FspmConfig.tRFC;
  MemConfig->tRRD                    = FspmUpd->FspmConfig.tRRD;
  MemConfig->tRTP                    = FspmUpd->FspmConfig.tRTP;
  MemConfig->tWR                     = FspmUpd->FspmConfig.tWR;
  MemConfig->tWTR                    = FspmUpd->FspmConfig.tWTR;
  MemConfig->NModeSupport            = FspmUpd->FspmConfig.NModeSupport;
  MemConfig->DllBwEn0                = FspmUpd->FspmConfig.DllBwEn0;
  MemConfig->DllBwEn1                = FspmUpd->FspmConfig.DllBwEn1;
  MemConfig->DllBwEn2                = FspmUpd->FspmConfig.DllBwEn2;
  MemConfig->DllBwEn3                = FspmUpd->FspmConfig.DllBwEn3;
  if (IsSimicsEnvironment ()) {
    MemConfig->SimicsFlag = 1;
  } else {
    MemConfig->SimicsFlag = 0;
  }
  MemConfig->HobBufferSize           = FspmUpd->FspmConfig.HobBufferSize;

  MemConfig->ECT                     = FspmUpd->FspmConfig.ECT;
  MemConfig->SOT                     = FspmUpd->FspmConfig.SOT;
  MemConfig->ERDMPRTC2D              = FspmUpd->FspmConfig.ERDMPRTC2D;
  MemConfig->RDMPRT                  = FspmUpd->FspmConfig.RDMPRT;
  MemConfig->RCVET                   = FspmUpd->FspmConfig.RCVET;
  MemConfig->JWRL                    = FspmUpd->FspmConfig.JWRL;
  MemConfig->EWRTC2D                 = FspmUpd->FspmConfig.EWRTC2D;
  MemConfig->ERDTC2D                 = FspmUpd->FspmConfig.ERDTC2D;
  MemConfig->WRTC1D                  = FspmUpd->FspmConfig.WRTC1D;
  MemConfig->WRVC1D                  = FspmUpd->FspmConfig.WRVC1D;
  MemConfig->RDTC1D                  = FspmUpd->FspmConfig.RDTC1D;
  MemConfig->DIMMODTT                = FspmUpd->FspmConfig.DIMMODTT;
  MemConfig->DIMMRONT                = FspmUpd->FspmConfig.DIMMRONT;
  MemConfig->WRSRT                   = FspmUpd->FspmConfig.WRSRT;
  MemConfig->RDODTT                  = FspmUpd->FspmConfig.RDODTT;
  MemConfig->RDEQT                   = FspmUpd->FspmConfig.RDEQT;
  MemConfig->RDAPT                   = FspmUpd->FspmConfig.RDAPT;
  MemConfig->WRTC2D                  = FspmUpd->FspmConfig.WRTC2D;
  MemConfig->RDTC2D                  = FspmUpd->FspmConfig.RDTC2D;
  MemConfig->WRVC2D                  = FspmUpd->FspmConfig.WRVC2D;
  MemConfig->RDVC2D                  = FspmUpd->FspmConfig.RDVC2D;
  MemConfig->CMDVC                   = FspmUpd->FspmConfig.CMDVC;
  MemConfig->LCT                     = FspmUpd->FspmConfig.LCT;
  MemConfig->RTL                     = FspmUpd->FspmConfig.RTL;
  MemConfig->TAT                     = FspmUpd->FspmConfig.TAT;
  MemConfig->RCVENC1D                = FspmUpd->FspmConfig.RCVENC1D;
  MemConfig->RMT                     = FspmUpd->FspmConfig.RMT;
  MemConfig->RMTBIT                  = FspmUpd->FspmConfig.RMTBIT;
  MemConfig->MarginLimitCheck        = FspmUpd->FspmConfig.MarginLimitCheck;
  MemConfig->MarginLimitL2           = FspmUpd->FspmConfig.MarginLimitL2;
  MemConfig->MEMTST                  = FspmUpd->FspmConfig.MEMTST;
  MemConfig->ALIASCHK                = FspmUpd->FspmConfig.ALIASCHK;
  MemConfig->RMC                     = FspmUpd->FspmConfig.RMC;
  MemConfig->WRDSUDT                 = FspmUpd->FspmConfig.WRDSUDT;
  MemConfig->WRDSEQT                 = FspmUpd->FspmConfig.WRDSEQT;
  MemConfig->CMDSR                   = FspmUpd->FspmConfig.CMDSR;
  MemConfig->CMDDSEQ                 = FspmUpd->FspmConfig.CMDDSEQ;
  MemConfig->CMDNORM                 = FspmUpd->FspmConfig.CMDNORM;
  MemConfig->EWRDSEQ                 = FspmUpd->FspmConfig.EWRDSEQ;
  MemConfig->RDVC1D                  = FspmUpd->FspmConfig.RDVC1D;
  MemConfig->TXTCO                   = FspmUpd->FspmConfig.TXTCO;
  MemConfig->CLKTCO                  = FspmUpd->FspmConfig.CLKTCO;
  MemConfig->DIMMODTCA               = FspmUpd->FspmConfig.DIMMODTCA;
  MemConfig->TXTCODQS                = FspmUpd->FspmConfig.TXTCODQS;
  MemConfig->DCC                     = FspmUpd->FspmConfig.DCC;
  MemConfig->DQDFE                   = FspmUpd->FspmConfig.DQDFE;
  MemConfig->SOTC                    = FspmUpd->FspmConfig.SOTC;

  MemConfig->EccSupport              = FspmUpd->FspmConfig.EccSupport;
  MemConfig->RemapEnable             = FspmUpd->FspmConfig.RemapEnable;
  MemConfig->RankInterleave          = FspmUpd->FspmConfig.RankInterleave;
  MemConfig->EnhancedInterleave      = FspmUpd->FspmConfig.EnhancedInterleave;
  MemConfig->MemoryTrace             = FspmUpd->FspmConfig.MemoryTrace;
  MemConfig->ChHashEnable            = FspmUpd->FspmConfig.ChHashEnable;
  MemConfig->EnableExtts             = FspmUpd->FspmConfig.EnableExtts;
  MemConfig->EnableCltm              = FspmUpd->FspmConfig.EnableCltm;
  MemConfig->EnableOltm              = FspmUpd->FspmConfig.EnableOltm;
  MemConfig->EnablePwrDn             = FspmUpd->FspmConfig.EnablePwrDn;
  MemConfig->EnablePwrDnLpddr        = FspmUpd->FspmConfig.EnablePwrDnLpddr;
  MemConfig->UserPowerWeightsEn      = FspmUpd->FspmConfig.UserPowerWeightsEn;
  MemConfig->RaplLim2Lock            = FspmUpd->FspmConfig.RaplLim2Lock;
  MemConfig->RaplLim2Ena             = FspmUpd->FspmConfig.RaplLim2Ena;
  MemConfig->RaplLim1Ena             = FspmUpd->FspmConfig.RaplLim1Ena;
  MemConfig->SrefCfgEna              = FspmUpd->FspmConfig.SrefCfgEna;
  MemConfig->ThrtCkeMinDefeatLpddr   = FspmUpd->FspmConfig.ThrtCkeMinDefeatLpddr;
  MemConfig->ThrtCkeMinDefeat        = FspmUpd->FspmConfig.ThrtCkeMinDefeat;
  MemConfig->RhPrevention            = FspmUpd->FspmConfig.RhPrevention;
  MemConfig->ExitOnFailure           = FspmUpd->FspmConfig.ExitOnFailure;
  MemConfig->DdrThermalSensor        = FspmUpd->FspmConfig.DdrThermalSensor;
  MemConfig->Ddr4DdpSharedClock      = FspmUpd->FspmConfig.Ddr4DdpSharedClock;
  MemConfig->SharedZqPin             = FspmUpd->FspmConfig.Ddr4DdpSharedZq;
  MemConfig->BClkFrequency           = FspmUpd->FspmConfig.BClkFrequency;
  MemConfig->ChHashInterleaveBit     = FspmUpd->FspmConfig.ChHashInterleaveBit;
  MemConfig->ChHashMask              = FspmUpd->FspmConfig.ChHashMask;
  MemConfig->ExtendedBankHashing     = FspmUpd->FspmConfig.ExtendedBankHashing;
  MemConfig->EnergyScaleFact         = FspmUpd->FspmConfig.EnergyScaleFact;
  MemConfig->Idd3n                   = FspmUpd->FspmConfig.Idd3n;
  MemConfig->Idd3p                   = FspmUpd->FspmConfig.Idd3p;
  MemConfig->RhActProbability        = FspmUpd->FspmConfig.RhActProbability;
  MemConfig->RaplLim2WindX           = FspmUpd->FspmConfig.RaplLim2WindX;
  MemConfig->RaplLim2WindY           = FspmUpd->FspmConfig.RaplLim2WindY;
  MemConfig->RaplLim1WindX           = FspmUpd->FspmConfig.RaplLim1WindX;
  MemConfig->RaplLim1WindY           = FspmUpd->FspmConfig.RaplLim1WindY;
  MemConfig->RaplLim2Pwr             = FspmUpd->FspmConfig.RaplLim2Pwr;
  MemConfig->RaplLim1Pwr             = FspmUpd->FspmConfig.RaplLim1Pwr;
  MemConfig->WarmThresholdCh0Dimm0   = FspmUpd->FspmConfig.WarmThresholdCh0Dimm0;
  MemConfig->WarmThresholdCh0Dimm1   = FspmUpd->FspmConfig.WarmThresholdCh0Dimm1;
  MemConfig->WarmThresholdCh1Dimm0   = FspmUpd->FspmConfig.WarmThresholdCh1Dimm0;
  MemConfig->WarmThresholdCh1Dimm1   = FspmUpd->FspmConfig.WarmThresholdCh1Dimm1;
  MemConfig->HotThresholdCh0Dimm0    = FspmUpd->FspmConfig.HotThresholdCh0Dimm0;
  MemConfig->HotThresholdCh0Dimm1    = FspmUpd->FspmConfig.HotThresholdCh0Dimm1;
  MemConfig->HotThresholdCh1Dimm0    = FspmUpd->FspmConfig.HotThresholdCh1Dimm0;
  MemConfig->HotThresholdCh1Dimm1    = FspmUpd->FspmConfig.HotThresholdCh1Dimm1;
  MemConfig->WarmBudgetCh0Dimm0      = FspmUpd->FspmConfig.WarmBudgetCh0Dimm0;
  MemConfig->WarmBudgetCh0Dimm1      = FspmUpd->FspmConfig.WarmBudgetCh0Dimm1;
  MemConfig->WarmBudgetCh1Dimm0      = FspmUpd->FspmConfig.WarmBudgetCh1Dimm0;
  MemConfig->WarmBudgetCh1Dimm1      = FspmUpd->FspmConfig.WarmBudgetCh1Dimm1;
  MemConfig->HotBudgetCh0Dimm0       = FspmUpd->FspmConfig.HotBudgetCh0Dimm0;
  MemConfig->HotBudgetCh0Dimm1       = FspmUpd->FspmConfig.HotBudgetCh0Dimm1;
  MemConfig->HotBudgetCh1Dimm0       = FspmUpd->FspmConfig.HotBudgetCh1Dimm0;
  MemConfig->HotBudgetCh1Dimm1       = FspmUpd->FspmConfig.HotBudgetCh1Dimm1;
  MemConfig->IdleEnergyCh0Dimm0      = FspmUpd->FspmConfig.IdleEnergyCh0Dimm0;
  MemConfig->IdleEnergyCh0Dimm1      = FspmUpd->FspmConfig.IdleEnergyCh0Dimm1;
  MemConfig->IdleEnergyCh1Dimm0      = FspmUpd->FspmConfig.IdleEnergyCh1Dimm0;
  MemConfig->IdleEnergyCh1Dimm1      = FspmUpd->FspmConfig.IdleEnergyCh1Dimm1;
  MemConfig->PdEnergyCh0Dimm0        = FspmUpd->FspmConfig.PdEnergyCh0Dimm0;
  MemConfig->PdEnergyCh0Dimm1        = FspmUpd->FspmConfig.PdEnergyCh0Dimm1;
  MemConfig->PdEnergyCh1Dimm0        = FspmUpd->FspmConfig.PdEnergyCh1Dimm0;
  MemConfig->PdEnergyCh1Dimm1        = FspmUpd->FspmConfig.PdEnergyCh1Dimm1;
  MemConfig->ActEnergyCh0Dimm0       = FspmUpd->FspmConfig.ActEnergyCh0Dimm0;
  MemConfig->ActEnergyCh0Dimm1       = FspmUpd->FspmConfig.ActEnergyCh0Dimm1;
  MemConfig->ActEnergyCh1Dimm0       = FspmUpd->FspmConfig.ActEnergyCh1Dimm0;
  MemConfig->ActEnergyCh1Dimm1       = FspmUpd->FspmConfig.ActEnergyCh1Dimm1;
  MemConfig->RdEnergyCh0Dimm0        = FspmUpd->FspmConfig.RdEnergyCh0Dimm0;
  MemConfig->RdEnergyCh0Dimm1        = FspmUpd->FspmConfig.RdEnergyCh0Dimm1;
  MemConfig->RdEnergyCh1Dimm0        = FspmUpd->FspmConfig.RdEnergyCh1Dimm0;
  MemConfig->RdEnergyCh1Dimm1        = FspmUpd->FspmConfig.RdEnergyCh1Dimm1;
  MemConfig->WrEnergyCh0Dimm0        = FspmUpd->FspmConfig.WrEnergyCh0Dimm0;
  MemConfig->WrEnergyCh0Dimm1        = FspmUpd->FspmConfig.WrEnergyCh0Dimm1;
  MemConfig->WrEnergyCh1Dimm0        = FspmUpd->FspmConfig.WrEnergyCh1Dimm0;
  MemConfig->WrEnergyCh1Dimm1        = FspmUpd->FspmConfig.WrEnergyCh1Dimm1;
  MemConfig->ThrtCkeMinTmr           = FspmUpd->FspmConfig.ThrtCkeMinTmr;
  MemConfig->CkeRankMapping          = FspmUpd->FspmConfig.CkeRankMapping;
  MemConfig->RaplPwrFlCh0            = FspmUpd->FspmConfig.RaplPwrFlCh0;
  MemConfig->RaplPwrFlCh1            = FspmUpd->FspmConfig.RaplPwrFlCh1;
  MemConfig->EnCmdRate               = FspmUpd->FspmConfig.EnCmdRate;
  MemConfig->Refresh2X               = FspmUpd->FspmConfig.Refresh2X;
  MemConfig->EpgEnable               = FspmUpd->FspmConfig.EpgEnable;
  MemConfig->RhSolution              = FspmUpd->FspmConfig.RhSolution;
  MemConfig->UserThresholdEnable     = FspmUpd->FspmConfig.UserThresholdEnable;
  MemConfig->UserBudgetEnable        = FspmUpd->FspmConfig.UserBudgetEnable;
  MemConfig->TsodTcritMax            = FspmUpd->FspmConfig.TsodTcritMax;
  MemConfig->TsodEventMode           = FspmUpd->FspmConfig.TsodEventMode;
  MemConfig->TsodEventPolarity       = FspmUpd->FspmConfig.TsodEventPolarity;
  MemConfig->TsodCriticalEventOnly   = FspmUpd->FspmConfig.TsodCriticalEventOnly;
  MemConfig->TsodEventOutputControl  = FspmUpd->FspmConfig.TsodEventOutputControl;
  MemConfig->TsodAlarmwindowLockBit  = FspmUpd->FspmConfig.TsodAlarmwindowLockBit;
  MemConfig->TsodCriticaltripLockBit = FspmUpd->FspmConfig.TsodCriticaltripLockBit;
  MemConfig->TsodShutdownMode        = FspmUpd->FspmConfig.TsodShutdownMode;
  MemConfig->TsodThigMax             = FspmUpd->FspmConfig.TsodThigMax;
  MemConfig->TsodManualEnable        = FspmUpd->FspmConfig.TsodManualEnable;
  MemConfig->IsvtIoPort              = FspmUpd->FspmConfig.IsvtIoPort;
  MemConfig->ForceOltmOrRefresh2x    = FspmUpd->FspmConfig.ForceOltmOrRefresh2x;
  MemConfig->PwdwnIdleCounter        = FspmUpd->FspmConfig.PwdwnIdleCounter;
  MemConfig->DisPgCloseIdleTimeout   = FspmUpd->FspmConfig.DisPgCloseIdleTimeout;
  MemConfig->CmdRanksTerminated      = FspmUpd->FspmConfig.CmdRanksTerminated;
  MemConfig->RMTLoopCount            = FspmUpd->FspmConfig.RMTLoopCount;
  MemConfig->Ibecc                   = FspmUpd->FspmConfig.Ibecc;

  MemConfig->CaVrefConfig     = FspmUpd->FspmConfig.CaVrefConfig;
  MemConfig->DllBwEn0         = FspmUpd->FspmConfig.DllBwEn0;
  MemConfig->DllBwEn1         = FspmUpd->FspmConfig.DllBwEn1;
  MemConfig->DllBwEn2         = FspmUpd->FspmConfig.DllBwEn2;
  MemConfig->DllBwEn3         = FspmUpd->FspmConfig.DllBwEn3;
  MemConfig->RhPrevention     = FspmUpd->FspmConfig.RhPrevention;
  MemConfig->RhSolution       = FspmUpd->FspmConfig.RhSolution;
  MemConfig->RhActProbability = FspmUpd->FspmConfig.RhActProbability;
  MemConfig->Ibecc            = FspmUpd->FspmConfig.Ibecc;
  MemConfig->IbeccParity            = FspmUpd->FspmConfig.IbeccParity;
  MemConfig->IbeccOperationMode     = FspmUpd->FspmConfig.IbeccOperationMode;
  for (Index = 0; Index < MEM_MAX_IBECC_REGIONS; Index++) {
    MemConfig->IbeccProtectedRegionEnable[Index] = FspmUpd->FspmConfig.IbeccProtectedRegionEnable[Index];
    MemConfig->IbeccProtectedRegionBase[Index] = FspmUpd->FspmConfig.IbeccProtectedRegionBase[Index];
    MemConfig->IbeccProtectedRegionMask[Index] = FspmUpd->FspmConfig.IbeccProtectedRegionMask[Index];
  }

  if (Vtd != NULL) {
    Vtd->X2ApicOptOut = FspmUpd->FspmConfig.X2ApicOptOut;
    Vtd->DmaControlGuarantee = FspmUpd->FspmConfig.DmaControlGuarantee;
    for (Index = 0; Index < VTD_ENGINE_NUMBER; Index++) {
      Vtd->BaseAddress[Index] = FspmUpd->FspmConfig.VtdBaseAddress[Index];
    }
    Vtd->VtdDisable    = FspmUpd->FspmConfig.VtdDisable;
    Vtd->VtdIgdEnable  = FspmUpd->FspmConfig.VtdIgdEnable;
    Vtd->VtdIpuEnable  = FspmUpd->FspmConfig.VtdIpuEnable;
    Vtd->VtdIopEnable  = FspmUpd->FspmConfig.VtdIopEnable;
    Vtd->VtdItbtEnable = FspmUpd->FspmConfig.VtdItbtEnable;
  }

  //
  // Update ConfigBlock:GtPreMemConfig
  //
  if (GtPreMemConfig != NULL) {
    GtPreMemConfig->IgdDvmt50PreAlloc = FspmUpd->FspmConfig.IgdDvmt50PreAlloc;
    GtPreMemConfig->InternalGraphics  = FspmUpd->FspmConfig.InternalGfx;
    GtPreMemConfig->ApertureSize      = FspmUpd->FspmConfig.ApertureSize;
    GtPreMemConfig->PrimaryDisplay    = FspmUpd->FspmConfig.PrimaryDisplay;
    GtPreMemConfig->GttMmAdr          = FspmUpd->FspmConfig.GttMmAdr;
    GtPreMemConfig->GmAdr             = FspmUpd->FspmConfig.GmAdr;
    GtPreMemConfig->GttSize           = FspmUpd->FspmConfig.GttSize;
    GtPreMemConfig->PsmiRegionSize    = FspmUpd->FspmConfig.PsmiRegionSize;
    GtPreMemConfig->DismSize          = FspmUpd->FspmConfig.DismSize;
    GtPreMemConfig->GtPsmiSupport     = FspmUpd->FspmConfig.GtPsmiSupport;
    GtPreMemConfig->PanelPowerEnable  = FspmUpd->FspmConfig.PanelPowerEnable;
  }


#if FixedPcdGetBool(PcdHgEnable) == 1
  if (HgGpioData != NULL) {
    CopyMem(&HgGpioData->CpuPcie0Rtd3Gpio, (VOID *)FspmUpd->FspmConfig.CpuPcie0Rtd3Gpio, sizeof (CPU_PCIE_RTD3_GPIO));
    HgGpioData->RootPortIndex = FspmUpd->FspmConfig.RootPortIndex;
    HgGpioData->HgDelayAfterPwrEn = FspmUpd->FspmConfig.HgDelayAfterPwrEn;
    HgGpioData->HgDelayAfterHoldReset = FspmUpd->FspmConfig.HgDelayAfterHoldReset;
    //
    // Initialize the Hybrid Graphics Configuration
    //
    if (GtPreMemConfig != NULL) {
      if (GtPreMemConfig->PrimaryDisplay == 4) {
        ///
        /// In Hybrid Gfx mode PCIe needs to be always enabled and IGFX must be set as Primary Display.
        ///
        HgGpioData->HgMode = 2;
        HgGpioData->HgSubSystemId = 0x2112;
        GtPreMemConfig->PrimaryDisplay = 0;
      } else if (GtPreMemConfig->PrimaryDisplay == 0) {
        ///
        /// In IGFX only mode mode set Hybrid Gfx mode as Disabled
        ///
        HgGpioData->HgMode = 0;
        HgGpioData->HgSubSystemId = 0x2212;
      } else {
        ///
        /// In PEG/PCI/Auto mode set Hybrid Gfx mode as dGPU
        ///
        HgGpioData->HgMode = 3;
        HgGpioData->HgSubSystemId = 0x2212;
      }
    }
  }
#endif

  if (PramPreMemConfig != NULL) {
    PramPreMemConfig->PramSize = FspmUpd->FspmConfig.PramSize;
  }

  //
  // Update ConfigBlock: MiscPeiPreMemConfig
  //
  if (MiscPeiPreMemConfig != NULL) {
    ZeroMem((VOID *)MiscPeiPreMemConfig->SpdAddressTable, sizeof(MiscPeiPreMemConfig->SpdAddressTable));
    MiscPeiPreMemConfig->MmioSizeAdjustment = FspmUpd->FspmConfig.MmioSizeAdjustment;
    MiscPeiPreMemConfig->MmioSize = FspmUpd->FspmConfig.MmioSize;
    MiscPeiPreMemConfig->TsegSize = FspmUpd->FspmConfig.TsegSize;
    MiscPeiPreMemConfig->S3DataPtr = FspmUpdDataPtr->FspmArchUpd.NvsBufferPtr;
    MiscPeiPreMemConfig->TxtImplemented = 0; // Currently TXT is not ready for FSP Wrapper. MiscPeiPreMemConfig->TxtImplemented = FspmUpd->TxtImplemented;
    MiscPeiPreMemConfig->CridEnable = FspmUpd->FspmConfig.CridEnable;
    MiscPeiPreMemConfig->SkipExtGfxScan = FspmUpd->FspmConfig.SkipExtGfxScan;
    MiscPeiPreMemConfig->BdatEnable = FspmUpd->FspmConfig.BdatEnable;
    MiscPeiPreMemConfig->BdatTestType = FspmUpd->FspmConfig.BdatTestType;
    MiscPeiPreMemConfig->ScanExtGfxForLegacyOpRom = FspmUpd->FspmConfig.ScanExtGfxForLegacyOpRom;
    MiscPeiPreMemConfig->LockPTMregs = FspmUpd->FspmConfig.LockPTMregs;

    for (Index = 0; Index < MEM_CFG_MAX_SOCKETS; Index++) {
      if (FspmUpd->FspmConfig.SpdAddressTable[Index] != 0) {
        MiscPeiPreMemConfig->SpdAddressTable[Index] = FspmUpd->FspmConfig.SpdAddressTable[Index];
      }
    }

  }

#if FixedPcdGetBool(PcdCpuPcieEnable) == 1
  if (PciePeiPreMemConfig != NULL) {
    PciePeiPreMemConfig->DmiGen3ProgramStaticEq = FspmUpd->FspmConfig.DmiGen3ProgramStaticEq;
    PciePeiPreMemConfig->InitPcieAspmAfterOprom = FspmUpd->FspmConfig.InitPcieAspmAfterOprom;
    for (Index = 0; Index < SA_DMI_MAX_LANE; Index++) {
      PciePeiPreMemConfig->DmiGen3RootPortPreset[Index] = FspmUpd->FspmConfig.DmiGen3RootPortPreset[Index];
      PciePeiPreMemConfig->DmiGen3EndPointPreset[Index] = FspmUpd->FspmConfig.DmiGen3EndPointPreset[Index];
      PciePeiPreMemConfig->DmiGen3EndPointHint[Index] = FspmUpd->FspmConfig.DmiGen3EndPointHint[Index];
    }
    for (Index = 0; Index < SA_DMI_MAX_BUNDLE; Index++) {
      PciePeiPreMemConfig->DmiGen3RxCtlePeaking[Index] = FspmUpd->FspmConfig.DmiGen3RxCtlePeaking[Index];
    }

    PciePeiPreMemConfig->DmiDeEmphasis = FspmUpd->FspmConfig.DmiDeEmphasis;

    PciePeiPreMemConfig->DmiMaxLinkSpeed = FspmUpd->FspmConfig.DmiMaxLinkSpeed;
    PciePeiPreMemConfig->DmiGen3EqPh2Enable = FspmUpd->FspmConfig.DmiGen3EqPh2Enable;
    PciePeiPreMemConfig->DmiGen3EqPh3Method = FspmUpd->FspmConfig.DmiGen3EqPh3Method;

  }
#endif


  if (CpuTraceHubPreMemConfig != NULL) {
    CpuTraceHubPreMemConfig->TraceHub.EnableMode = FspmUpd->FspmConfig.CpuTraceHubMode;
    CpuTraceHubPreMemConfig->TraceHub.MemReg0Size = FspmUpd->FspmConfig.CpuTraceHubMemReg0Size;
    CpuTraceHubPreMemConfig->TraceHub.MemReg1Size = FspmUpd->FspmConfig.CpuTraceHubMemReg1Size;
  }
#if FixedPcdGetBool(PcdCpuPcieEnable) == 1
  if (CpuPcieRpPreMemConfig != NULL) {
    CpuPcieRpPreMemConfig->RpEnabledMask                                          = FspmUpd->FspmConfig.CpuPcieRpEnableMask;
    CpuPcieRpPreMemConfig->LinkDownGpios                                          = FspmUpd->FspmConfig.CpuPcieRpLinkDownGpios;
    CpuPcieRpPreMemConfig->ClkReqMsgEnable                                        = FspmUpd->FspmConfig.CpuPcieRpClockReqMsgEnable;
    for (Index = 0; Index < GetMaxCpuPciePortNum (); Index ++) {
      CpuPcieRpPreMemConfig->PcieSpeed[Index] = FspmUpd->FspmConfig.CpuPcieRpPcieSpeed[Index];
    }
  }
#endif
  return EFI_SUCCESS;
}
