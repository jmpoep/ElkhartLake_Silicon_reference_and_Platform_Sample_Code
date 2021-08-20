/** @file
  This file initializes PEI policies: MEMORY_CONFIG_NO_CRC and MEMORY_CONFIGURATION

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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
#include <Library/SaPlatformLib.h>
#include <Library/PreSiliconEnvDetectLib.h>
#include <Library/PeiMemPolicyLib.h>
#include <MrcInterface.h>

//
// Need minimum of 48MB during PEI phase for IAG and some buffer for boot.
//
#define  PEI_MIN_MEMORY_SIZE               (10 * 0x800000)    // 80MB

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadMemConfigNoCrcDefault (
  IN VOID    *ConfigBlockPointer
  )
{
  MEMORY_CONFIG_NO_CRC                    *MemConfigNoCrc;

  MemConfigNoCrc = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "%aName = %g\n", "MemConfigNoCrc->Header.GuidHob.", &MemConfigNoCrc->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "%aHeader.HobLength = 0x%x\n", "MemConfigNoCrc->Header.GuidHob.", MemConfigNoCrc->Header.GuidHob.Header.HobLength));
  //
  // Allocating memory space for pointer structures inside MemConfigNoCrc
  //
  MemConfigNoCrc->SpdData = (SPD_DATA_BUFFER *) AllocateZeroPool (sizeof (SPD_DATA_BUFFER));
  ASSERT (MemConfigNoCrc->SpdData != NULL);
  if (MemConfigNoCrc->SpdData == NULL) {
    return;
  }

  MemConfigNoCrc->DqByteMap = (SA_MEMORY_DQ_MAPPING *) AllocateZeroPool (sizeof (SA_MEMORY_DQ_MAPPING));
  ASSERT (MemConfigNoCrc->DqByteMap != NULL);
  if (MemConfigNoCrc->DqByteMap == NULL) {
    return;
  }

  MemConfigNoCrc->DqsMap = (SA_MEMORY_DQS_MAPPING *) AllocateZeroPool (sizeof (SA_MEMORY_DQS_MAPPING));
  ASSERT (MemConfigNoCrc->DqsMap != NULL);
  if (MemConfigNoCrc->DqsMap == NULL) {
    return;
  }

  MemConfigNoCrc->RcompData = (SA_MEMORY_RCOMP *) AllocateZeroPool (sizeof (SA_MEMORY_RCOMP));
  ASSERT (MemConfigNoCrc->RcompData != NULL);
  if (MemConfigNoCrc->RcompData == NULL) {
    return;
  }

  //
  // Set PlatformMemory Size
  //
  MemConfigNoCrc->PlatformMemorySize = PEI_MIN_MEMORY_SIZE;
  MemConfigNoCrc->SerialDebugLevel  = 3;  //< Enable MRC debug message
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadMemConfigDefault (
  IN VOID *ConfigBlockPointer
  )
{
  MEMORY_CONFIGURATION                    *MemConfig;
  UINT16                                  DeviceId;
  DeviceId    = PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, R_SA_MC_DEVICE_ID));

  MemConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "%aName = %g\n", "MemConfig->Header.GuidHob.", &MemConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "%aHeader.HobLength = 0x%x\n", "MemConfig->Header.GuidHob.", MemConfig->Header.GuidHob.Header.HobLength));
  //
  // Initialize the Memory Configuration
  //
  MemConfig->EccSupport         = 1;
  MemConfig->ScramblerSupport   = 1;
  MemConfig->PowerDownMode      = 0xFF;
  MemConfig->RankInterleave     = TRUE;
  MemConfig->EnhancedInterleave = TRUE;
  MemConfig->WeaklockEn         = 1;
  MemConfig->EnCmdRate          = 3;
  MemConfig->AutoSelfRefreshSupport = TRUE;
  MemConfig->ExtTemperatureSupport  = TRUE;
  MemConfig->Ddr4OneDpc         = 3;  // DDR4_1DPC feature is enabled on both DIMMs
  MemConfig->ExitOnFailure      = 1;
  MemConfig->CmdRanksTerminated = 1;

  //
  // Channel Hash Configuration
  //
  MemConfig->ChHashEnable         = TRUE;
  MemConfig->ChHashMask           = 0x30CC;
  MemConfig->ChHashInterleaveBit  = 2;

  MemConfig->ExtendedBankHashing  = TRUE;
  MemConfig->PerBankRefresh       = TRUE;

  //
  // Options for Thermal settings
  //
  MemConfig->EnablePwrDn            = 1;
  MemConfig->EnablePwrDnLpddr       = 1;
  MemConfig->DdrThermalSensor     = 1;

  MemConfig->EnergyScaleFact        = 4;
  MemConfig->WarmThresholdCh0Dimm0  = 0xFF;
  MemConfig->WarmThresholdCh0Dimm1  = 0xFF;
  MemConfig->WarmThresholdCh1Dimm0  = 0xFF;
  MemConfig->WarmThresholdCh1Dimm1  = 0xFF;
  MemConfig->HotThresholdCh0Dimm0   = 0xFF;
  MemConfig->HotThresholdCh0Dimm1   = 0xFF;
  MemConfig->HotThresholdCh1Dimm0   = 0xFF;
  MemConfig->HotThresholdCh1Dimm1   = 0xFF;
  MemConfig->WarmBudgetCh0Dimm0     = 0xFF;
  MemConfig->WarmBudgetCh0Dimm1     = 0xFF;
  MemConfig->WarmBudgetCh1Dimm0     = 0xFF;
  MemConfig->WarmBudgetCh1Dimm1     = 0xFF;
  MemConfig->HotBudgetCh0Dimm0      = 0xFF;
  MemConfig->HotBudgetCh0Dimm1      = 0xFF;
  MemConfig->HotBudgetCh1Dimm0      = 0xFF;
  MemConfig->HotBudgetCh1Dimm1      = 0xFF;

  MemConfig->SrefCfgEna             = 1;
  MemConfig->SrefCfgIdleTmr         = 0x200;
  MemConfig->ThrtCkeMinTmr          = 0x30;
  MemConfig->ThrtCkeMinDefeatLpddr = 1;
  MemConfig->ThrtCkeMinTmrLpddr    = 0x40;

  //
  // CA Vref routing: board-dependent
  // 0 - VREF_CA goes to both CH_A and CH_B (LPDDR3/DDR3L)
  // 1 - VREF_CA to CH_A, VREF_DQ_A to CH_B (should not be used)
  // 2 - VREF_CA to CH_A, VREF_DQ_B to CH_B (DDR4)
  //
  MemConfig->CaVrefConfig       = 2;
  MemConfig->VttTermination     = 0;
  MemConfig->VttCompForVsshi    = 1;


  //
  // MRC training steps
  //
  MemConfig->ECT                  = 1;
  MemConfig->ERDMPRTC2D           = 1;
  MemConfig->SOT                  = 1;
  MemConfig->RDMPRT               = 0;
  MemConfig->RCVET                = 1;
  MemConfig->JWRL                 = 1;
  MemConfig->EWRTC2D              = 1;
  MemConfig->ERDTC2D              = 1;
  MemConfig->WRTC1D               = 1;
  MemConfig->WRVC1D               = 1;
  MemConfig->RDTC1D               = 1;
  MemConfig->DIMMODTT             = 1;
  MemConfig->DIMMRONT             = 1;
  MemConfig->WRSRT                = 1;
  MemConfig->WRDSEQT              = 1;
  MemConfig->RDODTT               = 1;
  MemConfig->RDEQT                = 1;
  MemConfig->RDAPT                = 1;
  MemConfig->WRTC2D               = 1;
  MemConfig->RDTC2D               = 1;
  MemConfig->CMDVC                = 1;
  MemConfig->WRVC2D               = 1;
  MemConfig->RDVC2D               = 1;
  MemConfig->LCT                  = 1;
  MemConfig->RTL                  = 1;
  MemConfig->TAT                  = 0;
  MemConfig->ALIASCHK             = 0;
  MemConfig->RCVENC1D             = 1;
  MemConfig->RMC                  = 0;
  MemConfig->WRDSUDT              = 0;

  // MRC training steps 2
  MemConfig->CMDSR                = 0;
  MemConfig->CMDDSEQ              = 0;
  MemConfig->CMDNORM              = 0;
  MemConfig->EWRDSEQ              = 0;
  MemConfig->RDVC1D               = 1;
  MemConfig->TXTCO                = 0;
  MemConfig->CLKTCO               = 0;
  MemConfig->DIMMODTCA            = 1;
  MemConfig->TXTCODQS             = 0;
  MemConfig->DCC                  = 1;
  MemConfig->DQDFE                = 0;
  MemConfig->SOTC                 = 0;

  MemConfig->MrcFastBoot          = TRUE;
  MemConfig->MrcTrainOnWarm       = FALSE;
  MemConfig->RemapEnable          = TRUE;
  MemConfig->BClkFrequency        = 100 * 1000 * 1000;

#if FixedPcdGet8(PcdEmbeddedEnable) == 1
  MemConfig->Force1Dpc = TRUE;
#endif

  MemConfig->MobilePlatform     = IsMobileSku ();
  MemConfig->PciIndex           = 0xCF8;
  MemConfig->PciData            = 0xCFC;
  MemConfig->CkeRankMapping     = 0xAA;
  //
  // SA GV: 0 - Disabled, 1 - FixedLow, 2 - FixedMid, 3 - FixedHigh, 4 - Enabled
  //
  MemConfig->SaGv               = 4;  // This only affects ULX/ULT; otherwise SA GV is disabled.
  MemConfig->SimicsFlag         = 0;
  MemConfig->Idd3n              = 26;
  MemConfig->Idd3p              = 11;

  MemConfig->RhPrevention       = FALSE;        // Row Hammer prevention. In ICL timeframe all DRAMs are expected to be RH-free.
  MemConfig->RhSolution         = HardwareRhp;  // Type of solution to be used for RHP - 0/1 = HardwareRhp/Refresh2x
  MemConfig->RhActProbability   = OneIn2To11;   // Activation probability for Hardware RHP

  MemConfig->DllBwEn1 = 1;
  MemConfig->DllBwEn2 = 2;
  MemConfig->DllBwEn3 = 2;

  MemConfig->RetrainOnFastFail = 1; // Restart MRC in Cold mode if SW MemTest fails during Fast flow. 0 = Disabled, 1 = Enabled
  MemConfig->Lp4DqsOscEn       = 1; // LPDDR4 Write DQ/DQS Retraining

  MemConfig->IsvtIoPort = 0x99;
}
