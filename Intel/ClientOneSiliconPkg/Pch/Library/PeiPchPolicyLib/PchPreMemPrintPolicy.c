/** @file
  Print whole PCH_PREMEM_POLICY_PPI

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2018 Intel Corporation.

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
#include "PeiPchPolicyLibrary.h"

/**
  Print PCH_GENERAL_PREMEM_CONFIG and serial out.

  @param[in] PchGeneralPreMemConfig     Pointer to a PCH_GENERAL_PREMEM_CONFIG that provides the platform setting

**/
VOID
PchPrintGeneralPreMemConfig (
  IN CONST PCH_GENERAL_PREMEM_CONFIG    *PchGeneralPreMemConfig
  )
{
  DEBUG ((DEBUG_INFO, "------------------ PCH General PreMem Config ------------------\n"));
  DEBUG ((DEBUG_INFO, " Port80Route= %x\n", PchGeneralPreMemConfig->Port80Route));
  DEBUG ((DEBUG_INFO, " PchMasterClockGating= %x\n", PchGeneralPreMemConfig->PchMasterClockGating));
  DEBUG ((DEBUG_INFO, " PchMasterPowerGating= %x\n", PchGeneralPreMemConfig->PchMasterPowerGating));
}


/**
  Print PCH_LPC_PREMEM_CONFIG and serial out.

  @param[in] LpcPreMemConfig                  Pointer to a PCH_LPC_PREMEM_CONFIG that provides the platform setting

**/
VOID
PchPrintLpcPreMemConfig (
  IN CONST PCH_LPC_PREMEM_CONFIG              *LpcPreMemConfig
  )
{
  DEBUG ((DEBUG_INFO, "------------------ PCH LPC PreMem Config ------------------\n"));
  DEBUG ((DEBUG_INFO, "EnhancePort8xhDecoding= %x\n", LpcPreMemConfig->EnhancePort8xhDecoding));
}

/**
  Print PCH_HSIO_PCIE_PREMEM_CONFIG and serial out.

  @param[in] HsioPciePreMemConfig     Pointer to a PCH_HSIO_PCIE_PREMEM_CONFIG that provides the platform setting

**/
VOID
PchPrintHsioPciePreMemConfig (
  IN CONST PCH_HSIO_PCIE_PREMEM_CONFIG *HsioPciePreMemConfig
  )
{
  UINT32 Index;

  DEBUG ((DEBUG_INFO, "------------------ HSIO PCIE PreMem Config ------------------\n"));
  for (Index = 0; Index < GetPchMaxPciePortNum (); Index++) {
    DEBUG ((DEBUG_INFO, " RootPort[%d] HsioRxSetCtleEnable= %x\n", Index, HsioPciePreMemConfig->Lane[Index].HsioRxSetCtleEnable));
    DEBUG ((DEBUG_INFO, " RootPort[%d] HsioRxSetCtle= %x\n", Index, HsioPciePreMemConfig->Lane[Index].HsioRxSetCtle));
    DEBUG ((DEBUG_INFO, " RootPort[%d] HsioTxGen1DownscaleAmpEnable= %x\n", Index, HsioPciePreMemConfig->Lane[Index].HsioTxGen1DownscaleAmpEnable));
    DEBUG ((DEBUG_INFO, " RootPort[%d] HsioTxGen1DownscaleAmp= %x\n", Index, HsioPciePreMemConfig->Lane[Index].HsioTxGen1DownscaleAmp));
    DEBUG ((DEBUG_INFO, " RootPort[%d] HsioTxGen2DownscaleAmpEnable= %x\n", Index, HsioPciePreMemConfig->Lane[Index].HsioTxGen2DownscaleAmpEnable));
    DEBUG ((DEBUG_INFO, " RootPort[%d] HsioTxGen2DownscaleAmp= %x\n", Index, HsioPciePreMemConfig->Lane[Index].HsioTxGen2DownscaleAmp));
    DEBUG ((DEBUG_INFO, " RootPort[%d] HsioTxGen3DownscaleAmpEnable= %x\n", Index, HsioPciePreMemConfig->Lane[Index].HsioTxGen3DownscaleAmpEnable));
    DEBUG ((DEBUG_INFO, " RootPort[%d] HsioTxGen3DownscaleAmp= %x\n", Index, HsioPciePreMemConfig->Lane[Index].HsioTxGen3DownscaleAmp));
    DEBUG ((DEBUG_INFO, " RootPort[%d] HsioTxGen1DeEmphEnable= %x\n", Index, HsioPciePreMemConfig->Lane[Index].HsioTxGen1DeEmphEnable));
    DEBUG ((DEBUG_INFO, " RootPort[%d] HsioTxGen1DeEmph= %x\n", Index, HsioPciePreMemConfig->Lane[Index].HsioTxGen1DeEmph));
    DEBUG ((DEBUG_INFO, " RootPort[%d] HsioTxGen2DeEmph3p5Enable= %x\n", Index, HsioPciePreMemConfig->Lane[Index].HsioTxGen2DeEmph3p5Enable));
    DEBUG ((DEBUG_INFO, " RootPort[%d] HsioTxGen2DeEmph3p5= %x\n", Index, HsioPciePreMemConfig->Lane[Index].HsioTxGen2DeEmph3p5));
    DEBUG ((DEBUG_INFO, " RootPort[%d] HsioTxGen2DeEmph6p0Enable= %x\n", Index, HsioPciePreMemConfig->Lane[Index].HsioTxGen2DeEmph6p0Enable));
    DEBUG ((DEBUG_INFO, " RootPort[%d] HsioTxGen2DeEmph6p0= %x\n", Index, HsioPciePreMemConfig->Lane[Index].HsioTxGen2DeEmph6p0));
  }
}

/**
  Print PCH_HSIO_SATA_PREMEM_CONFIG and serial out.

  @param[in] SataCtrlIndex            SATA controller index
  @param[in] HsioSataPreMemConfig     Pointer to a PCH_HSIO_SATA_PREMEM_CONFIG that provides the platform setting
**/
VOID
PchPrintHsioSataPreMemConfig (
  IN UINT8                             SataCtrlIndex,
  IN CONST PCH_HSIO_SATA_PREMEM_CONFIG *HsioSataPreMemConfig
  )
{
  UINT32 Index;

  DEBUG ((DEBUG_INFO, "---------------- HSIO SATA PreMem Config for controller %d ----------------\n", SataCtrlIndex));
  for (Index = 0; Index < MaxSataPortNum (SataCtrlIndex); Index++) {
    DEBUG ((DEBUG_INFO, " PortSettings[%d] HsioRxGen1EqBoostMagEnable= %x\n", Index, HsioSataPreMemConfig->PortLane[Index].HsioRxGen1EqBoostMagEnable));
    DEBUG ((DEBUG_INFO, " PortSettings[%d] HsioRxGen1EqBoostMag= %x\n", Index, HsioSataPreMemConfig->PortLane[Index].HsioRxGen1EqBoostMag));
    DEBUG ((DEBUG_INFO, " PortSettings[%d] HsioRxGen2EqBoostMagEnable= %x\n", Index, HsioSataPreMemConfig->PortLane[Index].HsioRxGen2EqBoostMagEnable));
    DEBUG ((DEBUG_INFO, " PortSettings[%d] HsioRxGen2EqBoostMag= %x\n", Index, HsioSataPreMemConfig->PortLane[Index].HsioRxGen2EqBoostMag));
    DEBUG ((DEBUG_INFO, " PortSettings[%d] HsioRxGen3EqBoostMagEnable= %x\n", Index, HsioSataPreMemConfig->PortLane[Index].HsioRxGen3EqBoostMagEnable));
    DEBUG ((DEBUG_INFO, " PortSettings[%d] HsioRxGen3EqBoostMag= %x\n", Index, HsioSataPreMemConfig->PortLane[Index].HsioRxGen3EqBoostMag));
    DEBUG ((DEBUG_INFO, " PortSettings[%d] HsioTxGen1DownscaleAmpEnable= %x\n", Index, HsioSataPreMemConfig->PortLane[Index].HsioTxGen1DownscaleAmpEnable));
    DEBUG ((DEBUG_INFO, " PortSettings[%d] HsioTxGen1DownscaleAmp= %x\n", Index, HsioSataPreMemConfig->PortLane[Index].HsioTxGen1DownscaleAmp));
    DEBUG ((DEBUG_INFO, " PortSettings[%d] HsioTxGen2DownscaleAmpEnable= %x\n", Index, HsioSataPreMemConfig->PortLane[Index].HsioTxGen2DownscaleAmpEnable));
    DEBUG ((DEBUG_INFO, " PortSettings[%d] HsioTxGen2DownscaleAmp= %x\n", Index, HsioSataPreMemConfig->PortLane[Index].HsioTxGen2DownscaleAmp));
    DEBUG ((DEBUG_INFO, " PortSettings[%d] HsioTxGen3DownscaleAmpEnable= %x\n", Index, HsioSataPreMemConfig->PortLane[Index].HsioTxGen3DownscaleAmpEnable));
    DEBUG ((DEBUG_INFO, " PortSettings[%d] HsioTxGen3DownscaleAmp= %x\n", Index, HsioSataPreMemConfig->PortLane[Index].HsioTxGen3DownscaleAmp));
    DEBUG ((DEBUG_INFO, " PortSettings[%d] HsioTxGen1DeEmphEnable= %x\n", Index, HsioSataPreMemConfig->PortLane[Index].HsioTxGen1DeEmphEnable));
    DEBUG ((DEBUG_INFO, " PortSettings[%d] HsioTxGen1DeEmph= %x\n", Index, HsioSataPreMemConfig->PortLane[Index].HsioTxGen1DeEmph));
    DEBUG ((DEBUG_INFO, " PortSettings[%d] HsioTxGen2DeEmphEnable= %x\n", Index, HsioSataPreMemConfig->PortLane[Index].HsioTxGen2DeEmphEnable));
    DEBUG ((DEBUG_INFO, " PortSettings[%d] HsioTxGen2DeEmph= %x\n", Index, HsioSataPreMemConfig->PortLane[Index].HsioTxGen2DeEmph));
    DEBUG ((DEBUG_INFO, " PortSettings[%d] HsioTxGen3DeEmphEnable= %x\n", Index, HsioSataPreMemConfig->PortLane[Index].HsioTxGen3DeEmphEnable));
    DEBUG ((DEBUG_INFO, " PortSettings[%d] HsioTxGen3DeEmph= %x\n", Index, HsioSataPreMemConfig->PortLane[Index].HsioTxGen3DeEmph));
  }
}

/**
  Print PCH_PCIE_RP_PREMEM_CONFIG and serial out.

  @param[in] PcieRpPreMemConfig        Pointer to a PCH_PCIE_RP_PREMEM_CONFIG that provides the platform setting

**/
VOID
PchPrintPcieRpPreMemConfig (
  IN CONST PCH_PCIE_RP_PREMEM_CONFIG    *PcieRpPreMemConfig
  )
{
  UINT32 Index;
  DEBUG ((DEBUG_INFO, "------------------ PCH PCIe RP PreMem Config ------------------\n"));

  for (Index = 0; Index < GetPchMaxPciePortNum (); Index++) {
    DEBUG ((DEBUG_INFO, " Port[%d] RpEnabled= %x\n", Index, (PcieRpPreMemConfig->RpEnabledMask & (UINT32) (1 << Index)) != 0 ));
  }
  for (Index = 0; Index < GetPchMaxPcieClockNum (); Index++) {
    DEBUG ((DEBUG_INFO, " Clock[%d] Usage= %x\n", Index, PcieRpPreMemConfig->PcieClock[Index].Usage));
    DEBUG ((DEBUG_INFO, " Clock[%d] ClkReq= %x\n", Index, PcieRpPreMemConfig->PcieClock[Index].ClkReq));
  }
}

/**
  Print whole PCH_POLICY_PPI and serial out.

  @param[in] SiPreMemPolicyPpi    The RC PREMEM Policy PPI instance

**/
VOID
EFIAPI
PchPreMemPrintPolicyPpi (
  IN  SI_PREMEM_POLICY_PPI     *SiPreMemPolicyPpi
  )
{
  DEBUG_CODE_BEGIN ();
  EFI_STATUS                      Status;
  PCH_GENERAL_PREMEM_CONFIG       *PchGeneralPreMemConfig;
  PCH_LPC_PREMEM_CONFIG           *LpcPreMemConfig;
  PCH_HSIO_PCIE_PREMEM_CONFIG     *HsioPciePreMemConfig;
  PCH_HSIO_SATA_PREMEM_CONFIG     *HsioSataPreMemConfig;
  PCH_PCIE_RP_PREMEM_CONFIG       *PcieRpPreMemConfig;
  UINT8                           SataCtrlIndex;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gPchGeneralPreMemConfigGuid, (VOID *) &PchGeneralPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gLpcPreMemConfigGuid, (VOID *) &LpcPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gHsioPciePreMemConfigGuid, (VOID *) &HsioPciePreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gPcieRpPreMemConfigGuid, (VOID *) &PcieRpPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------------ PCH Print PreMemPolicy Start ------------------------\n"));
  DEBUG ((DEBUG_INFO, " Revision= %x\n", SiPreMemPolicyPpi->TableHeader.Header.Revision));

  PchPrintGeneralPreMemConfig (PchGeneralPreMemConfig);
  PchPrintLpcPreMemConfig (LpcPreMemConfig);
  PchPrintHsioPciePreMemConfig (HsioPciePreMemConfig);
  for (SataCtrlIndex = 0; SataCtrlIndex < MaxSataControllerNum (); SataCtrlIndex++) {
    HsioSataPreMemConfig = GetPchHsioSataPreMemConfig (SiPreMemPolicyPpi, SataCtrlIndex);
    PchPrintHsioSataPreMemConfig (SataCtrlIndex, HsioSataPreMemConfig);
  }
  PchPrintPcieRpPreMemConfig (PcieRpPreMemConfig);

  DEBUG ((DEBUG_INFO, "------------------------ PCH Print PreMemPolicy End --------------------------\n"));
  DEBUG_CODE_END ();
}

