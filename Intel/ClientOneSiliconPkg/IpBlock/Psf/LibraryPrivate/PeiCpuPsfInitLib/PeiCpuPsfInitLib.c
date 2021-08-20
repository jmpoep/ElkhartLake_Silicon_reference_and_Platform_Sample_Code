/** @file
  Intialize Cpu PSF in PEI

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
#include <Library/CpuPlatformLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/CpuRegbarAccessLib.h>
#include <CpuSbInfo.h>
#include <Library/SaPcieInitLib.h>
#include <SaRegs.h>
#include <Register/CpuPsfRegs.h>

/**
  Cpu Psf programming.

  @param[in] void
**/
VOID
CpuPsfInit (
  VOID
)
{
  UINT32                        PSf1RcOwnerRegister32;
  CPU_SKU                       CpuSku;

  CpuSku = GetCpuSku();

  ///
  /// Root complex destination for MCTP Route to Rootcomplex messages need to be programmed in PSF1.
  ///
  ///
  ///
  if ((PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MC_CAPID0_B)) & BIT3) == BIT3) {
    PSf1RcOwnerRegister32 = 0x40000; ///< OPI
  } else {
    PSf1RcOwnerRegister32 = 0x18300; ///< DMI
  }
  CpuRegbarWrite32 (CPU_SB_PID_PSF1, R_SA_PSF1_RC_OWNER_RS0, PSf1RcOwnerRegister32);

  ///
  /// Program IMR transactions through VC1, TC0 for enabling Audio path to memory skus (U/Y).
  ///
  ///
  ///
  if (CpuSku == EnumCpuUlx || CpuSku == EnumCpuUlt) {
    CpuRegbarAndThenOr16 (CPU_SB_PID_PSFOPIO, R_SA_PSF_4_CHANMAP_SC_PG0_PORT0_CHAN1_RS3_CHMAP1, 0xFF00, 0x80);
    CpuRegbarAndThenOr16 (CPU_SB_PID_PSFOPIO, R_SA_PSF_4_CHANMAP_SC_PG1_PORT0_CHAN1_RS3_CHMAP1, 0xFFF0, 0x02);
    CpuRegbarWrite16 (CPU_SB_PID_PSF1, R_SA_PSF_1_CHANMAP_SC_PG0_PORT0_CHAN1_RS3_CHMAP1, 0x2000);
    CpuRegbarAndThenOr16 (CPU_SB_PID_PSF1, R_SA_PSF_1_CHANMAP_SC_PG1_PORT0_CHAN1_RS3_CHMAP1, 0xFFF0, 0x02);
    CpuRegbarWrite32 (CPU_SB_PID_PSF0, R_SA_PSF_0_CHANMAP_SC_PG0_PORT0_CHAN5_RS3_CHMAP2, 0x20000000);
    CpuRegbarAndThenOr16 (CPU_SB_PID_PSF0, R_SA_PSF_0_CHANMAP_SC_PG1_PORT0_CHAN1_RS3_CHMAP1, 0xFF00, 0x20);
  }
}