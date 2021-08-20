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

//
// Need minimum of 48MB during PEI phase for IAG and some buffer for boot.
//
#define  PEI_MIN_MEMORY_SIZE               (10 * 0x800000 + 0x10000000)    // 80MB + 256MB

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

  MemConfigNoCrc->DqDqsMap = (SA_MEMORY_DQDQS_MAPPING *) AllocateZeroPool (sizeof (SA_MEMORY_DQDQS_MAPPING));
  ASSERT (MemConfigNoCrc->DqDqsMap != NULL);
  if (MemConfigNoCrc->DqDqsMap == NULL) {
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

  MemConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "%aName = %g\n", "MemConfig->Header.GuidHob.", &MemConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "%aHeader.HobLength = 0x%x\n", "MemConfig->Header.GuidHob.", MemConfig->Header.GuidHob.Header.HobLength));
  //
  // Initialize the Memory Configuration
  //
  MemConfig->EccSupport             = 1;
  MemConfig->ScramblerSupport       = 1;
  MemConfig->PowerDownMode          = 0xFF;
  MemConfig->DisPgCloseIdleTimeout  = 0;
  MemConfig->RankInterleave         = TRUE;
  MemConfig->EnhancedInterleave     = TRUE;
  MemConfig->EnCmdRate              = 7;
  MemConfig->AutoSelfRefreshSupport = TRUE;
  MemConfig->ExtTemperatureSupport  = TRUE;

  //
  // Channel Hash Configuration
  //
  MemConfig->ChHashEnable           = TRUE;
  MemConfig->ChHashMask             = 0x30CC;
  MemConfig->ChHashInterleaveBit    = 2;

  MemConfig->PerBankRefresh         = 1;

  //
  // Options for Thermal settings
  //
  MemConfig->EnablePwrDn            = 1;
  MemConfig->EnablePwrDnLpddr       = 1;
  MemConfig->SrefCfgEna             = 1;
  MemConfig->SrefCfgIdleTmr         = 0x200;
  MemConfig->ThrtCkeMinTmr          = 0x30;
  MemConfig->ThrtCkeMinDefeatLpddr  = 1;
  MemConfig->ThrtCkeMinTmrLpddr     = 0x40;

  MemConfig->VttTermination         = IsMobileSku ();
  MemConfig->VttCompForVsshi        = 1;


  //
  // MRC training steps
  //
  MemConfig->ECT                  = 1;
  MemConfig->ERDMPRTC2D           = 1;
  MemConfig->SOT                  = 1;
  MemConfig->RDMPRT               = 1;
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
  MemConfig->TAT                  = 1;
  MemConfig->ALIASCHK             = 1;
  MemConfig->RCVENC1D             = 1;
  MemConfig->RMC                  = 1;

  MemConfig->MrcFastBoot          = TRUE;
  MemConfig->RemapEnable          = TRUE;
  MemConfig->BClkFrequency        = 100 * 1000 * 1000;

#if FixedPcdGet8(PcdEmbeddedEnable) == 1
  MemConfig->Force1Dpc = TRUE;
#endif
  MemConfig->Vc1ReadMeter         = TRUE;

  MemConfig->MobilePlatform       = IsMobileSku ();
  MemConfig->PciIndex             = 0xCF8;
  MemConfig->PciData              = 0xCFC;
  //
  // SA GV: 0 - Disabled, 1 - FixedLow, 2 - FixedMid, 3 - FixedHigh, 4 - Enabled
  //
  if (IsSimicsEnvironment()) {
    MemConfig->SimicsFlag         = 1;
    // Current Simics will fail in MRC training when SAGV enabled so need to by default disable SAGV.
    MemConfig->SaGv               = 0;  // This only affects ULX/ULT; otherwise SA GV is disabled.
  } else {
    MemConfig->SaGv               = 4;  // This only affects ULX/ULT; otherwise SA GV is disabled.
    MemConfig->SimicsFlag         = 0;
  }
  MemConfig->Idd3n                = 26;
  MemConfig->Idd3p                = 11;

  MemConfig->RetrainOnFastFail    = 1; // Restart MRC in Cold mode if SW MemTest fails during Fast flow. 0 = Disabled, 1 = Enabled
  MemConfig->LpDqsOscEn           = 1; // LPDDR Write DQ/DQS Retraining
}
