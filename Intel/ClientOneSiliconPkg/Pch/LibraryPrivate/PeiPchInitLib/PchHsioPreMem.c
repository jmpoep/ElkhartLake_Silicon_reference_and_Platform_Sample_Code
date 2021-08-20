/** @file
  PCH HSIO Pre-Memory Initialization file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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

#include <Library/PeiMeLib.h>
#include <BupMsgs.h>
#include "PchInitPei.h"
#include <Library/PeiServicesTablePointerLib.h>
#include <PchHsio.h>
#include <ChipsetInfoHob.h>
#include <Library/PeiHsioLib.h>
#include <Library/ConfigBlockLib.h>
#include <SaPolicyCommon.h>
#include <CpuPciePeiPreMemConfig.h>
#include <PcieRegs.h>
#include <Register/PchRegsHsio.h>
#include <Register/PchPcieRpRegs.h>

/**
  The function programs HSIO Rx\Tx Eq policy registers for SATA lanes.

  @param[in]  SiPreMemPolicyPpi  The SI PreMem Policy PPI instance
**/
VOID
PchHsioRxTxEqPolicySataProg (
  IN SI_PREMEM_POLICY_PPI  *SiPreMemPolicyPpi
  )
{
  HSIO_LANE                   HsioLane;
  UINT8                       MaxSataPorts;
  UINT8                       Index;
  UINT8                       LaneNum;
  UINT32                      Data32And;
  UINT32                      Data32Or;
  UINT32                      SataCtrlIndex;
  PCH_HSIO_SATA_PREMEM_CONFIG *HsioSataPreMemConfig;

  for (SataCtrlIndex = 0; SataCtrlIndex < MaxSataControllerNum (); SataCtrlIndex++) {
    HsioSataPreMemConfig = GetPchHsioSataPreMemConfig (SiPreMemPolicyPpi, SataCtrlIndex);
    MaxSataPorts = MaxSataPortNum (SataCtrlIndex);
    for (Index = 0; Index < MaxSataPorts; Index++) {
      if (PchFiaGetSataLaneNum (SataCtrlIndex, Index, &LaneNum)) {
        HsioGetLane (LaneNum, &HsioLane);
        if ((HsioSataPreMemConfig->PortLane[Index].HsioRxGen1EqBoostMagEnable == TRUE) ||
            (HsioSataPreMemConfig->PortLane[Index].HsioRxGen2EqBoostMagEnable == TRUE)) {
          Data32Or  = 0;
          Data32And = 0xFFFFFFFF;
          if (HsioSataPreMemConfig->PortLane[Index].HsioRxGen1EqBoostMagEnable == TRUE) {
            Data32Or |= (UINT32) (HsioSataPreMemConfig->PortLane[Index].HsioRxGen1EqBoostMag << N_HSIO_PCR_RX_DWORD21_ICFGCTLEDATATAP_QUATRATE_5_0);
            Data32And &= (UINT32) ~B_HSIO_PCR_RX_DWORD21_ICFGCTLEDATATAP_QUATRATE_5_0;
          }

          if (HsioSataPreMemConfig->PortLane[Index].HsioRxGen2EqBoostMagEnable == TRUE) {
            Data32Or |= (UINT32) (HsioSataPreMemConfig->PortLane[Index].HsioRxGen2EqBoostMag << N_HSIO_PCR_RX_DWORD21_ICFGCTLEDATATAP_HALFRATE_5_0);
            Data32And &= (UINT32) ~B_HSIO_PCR_RX_DWORD21_ICFGCTLEDATATAP_HALFRATE_5_0;
          }

          HsioLaneAndThenOr32WithSusWrite (&HsioLane, R_HSIO_PCR_RX_DWORD21, Data32And, Data32Or);
          DEBUG ((DEBUG_INFO, "HSIO : PortID = 0x%02x, Offset = 0x%04x,  Value = 0x%08x\n", HsioLane.Pid, HsioLane.Base + R_HSIO_PCR_RX_DWORD21, HsioLaneRead32 (&HsioLane, R_HSIO_PCR_RX_DWORD21)));
        }

        if (HsioSataPreMemConfig->PortLane[Index].HsioRxGen3EqBoostMagEnable == TRUE) {
          HsioLaneAndThenOr32WithSusWrite (
            &HsioLane,
            R_HSIO_PCR_RX_DWORD26,
            (UINT32) ~0,
            (UINT32) B_HSIO_PCR_RX_DWORD26_SATA_EQ_DIS
            );
          DEBUG ((DEBUG_INFO, "HSIO : PortID = 0x%02x, Offset = 0x%04x, Value = 0x%08x\n", HsioLane.Pid, HsioLane.Base + R_HSIO_PCR_RX_DWORD26, HsioLaneRead32 (&HsioLane, R_HSIO_PCR_RX_DWORD26)));

          HsioLaneAndThenOr32WithSusWrite (
            &HsioLane,
            R_HSIO_PCR_RX_DWORD20,
            (UINT32) ~B_HSIO_PCR_RX_DWORD20_ICFGCTLEDATATAP_FULLRATE_5_0,
            (UINT32) (HsioSataPreMemConfig->PortLane[Index].HsioRxGen3EqBoostMag << N_HSIO_PCR_RX_DWORD20_ICFGCTLEDATATAP_FULLRATE_5_0)
            );
          DEBUG ((DEBUG_INFO, "HSIO : PortID = 0x%02x, Offset = 0x%04x, Value = 0x%08x\n", HsioLane.Pid, HsioLane.Base + R_HSIO_PCR_RX_DWORD20, HsioLaneRead32 (&HsioLane, R_HSIO_PCR_RX_DWORD20)));
        }

        if ((HsioSataPreMemConfig->PortLane[Index].HsioTxGen1DownscaleAmpEnable == TRUE) ||
            (HsioSataPreMemConfig->PortLane[Index].HsioTxGen2DownscaleAmpEnable == TRUE) ||
            (HsioSataPreMemConfig->PortLane[Index].HsioTxGen3DownscaleAmpEnable == TRUE)) {

          Data32Or  = 0;
          Data32And = 0xFFFFFFFF;
          if (HsioSataPreMemConfig->PortLane[Index].HsioTxGen1DownscaleAmpEnable == TRUE) {
            Data32Or |= (UINT32) (HsioSataPreMemConfig->PortLane[Index].HsioTxGen1DownscaleAmp << N_HSIO_PCR_TX_DWORD8_ORATE00MARGIN_5_0);
            Data32And &= (UINT32) ~B_HSIO_PCR_TX_DWORD8_ORATE00MARGIN_5_0;
          }

          if (HsioSataPreMemConfig->PortLane[Index].HsioTxGen2DownscaleAmpEnable == TRUE) {
            Data32Or |= (UINT32) (HsioSataPreMemConfig->PortLane[Index].HsioTxGen2DownscaleAmp << N_HSIO_PCR_TX_DWORD8_ORATE01MARGIN_5_0);
            Data32And &= (UINT32) ~B_HSIO_PCR_TX_DWORD8_ORATE01MARGIN_5_0;
          }

          if (HsioSataPreMemConfig->PortLane[Index].HsioTxGen3DownscaleAmpEnable == TRUE) {
            Data32Or |= (UINT32) (HsioSataPreMemConfig->PortLane[Index].HsioTxGen3DownscaleAmp << N_HSIO_PCR_TX_DWORD8_ORATE10MARGIN_5_0);
            Data32And &= (UINT32) ~B_HSIO_PCR_TX_DWORD8_ORATE10MARGIN_5_0;
          }

          HsioLaneAndThenOr32WithSusWrite (&HsioLane, R_HSIO_PCR_TX_DWORD8, Data32And, Data32Or);
          DEBUG ((DEBUG_INFO, "HSIO : PortID = 0x%02x, Offset = 0x%04x, Value = 0x%08x\n", HsioLane.Pid, HsioLane.Base + R_HSIO_PCR_TX_DWORD8, HsioLaneRead32 (&HsioLane, R_HSIO_PCR_TX_DWORD8)));
        }

        if ((HsioSataPreMemConfig->PortLane[Index].HsioTxGen1DeEmphEnable == TRUE) ||
            (HsioSataPreMemConfig->PortLane[Index].HsioTxGen2DeEmphEnable == TRUE) ||
            (HsioSataPreMemConfig->PortLane[Index].HsioTxGen3DeEmphEnable == TRUE)) {
          Data32Or  = 0;
          Data32And = 0xFFFFFFFF;
          if (HsioSataPreMemConfig->PortLane[Index].HsioTxGen1DeEmphEnable == TRUE) {
            Data32Or |= (UINT32) (HsioSataPreMemConfig->PortLane[Index].HsioTxGen1DeEmph);
            Data32And &= (UINT32) ~B_HSIO_PCR_TX_DWORD6_OW2TAPGEN1DEEMPH6P0_5_0;
          }

          if (HsioSataPreMemConfig->PortLane[Index].HsioTxGen2DeEmphEnable == TRUE) {
            Data32Or |= (UINT32) (HsioSataPreMemConfig->PortLane[Index].HsioTxGen2DeEmph << N_HSIO_PCR_TX_DWORD6_OW2TAPGEN2DEEMPH6P0_5_0);
            Data32And &= (UINT32) ~B_HSIO_PCR_TX_DWORD6_OW2TAPGEN2DEEMPH6P0_5_0;
          }

          if (HsioSataPreMemConfig->PortLane[Index].HsioTxGen3DeEmphEnable == TRUE) {
            Data32Or |= (UINT32) (HsioSataPreMemConfig->PortLane[Index].HsioTxGen3DeEmph << N_HSIO_PCR_TX_DWORD6_OW2TAPGEN3DEEMPH6P0_5_0);
            Data32And &= (UINT32) ~B_HSIO_PCR_TX_DWORD6_OW2TAPGEN3DEEMPH6P0_5_0;
          }

          HsioLaneAndThenOr32WithSusWrite (&HsioLane, R_HSIO_PCR_TX_DWORD6, Data32And, Data32Or);
          DEBUG ((DEBUG_INFO, "HSIO : PortID = 0x%02x, Offset = 0x%04x, Value = 0x%08x\n", HsioLane.Pid, HsioLane.Base + R_HSIO_PCR_TX_DWORD6, HsioLaneRead32 (&HsioLane, R_HSIO_PCR_TX_DWORD6)));
        }
      }
    }
  }
}

/**
  The function programs HSIO Rx\Tx Eq policy registers for PCIe lanes.

  @param[in]  SiPreMemPolicyPpi  The SI PreMem Policy PPI instance
**/
VOID
PchHsioRxTxEqPolicyPcieProg (
  IN SI_PREMEM_POLICY_PPI  *SiPreMemPolicyPpi
  )
{
  HSIO_LANE                   HsioLane;
  UINT8                       Index;
  UINT8                       MaxPciePorts;
  UINT8                       LaneNum;
  UINT64                      RpBase;
  UINT32                      Data32And;
  UINT32                      Data32Or;
  UINT32                      RpToRetrain;
  UINT32                      TimeSpent;
  EFI_STATUS                  Status;
  PCH_HSIO_PCIE_PREMEM_CONFIG *HsioPciePreMemConfig;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gHsioPciePreMemConfigGuid, (VOID *) &HsioPciePreMemConfig);
  ASSERT_EFI_ERROR (Status);

  MaxPciePorts = GetPchMaxPciePortNum ();
  RpToRetrain = 0;
  for (Index = 0; Index < MaxPciePorts; Index++) {
    RpBase = PchPcieBase (Index);
    if (PchFiaGetPcieLaneNum (Index, &LaneNum)) {
      HsioGetLane (LaneNum, &HsioLane);
      if (HsioPciePreMemConfig->Lane[Index].HsioRxSetCtleEnable == TRUE) {
        HsioLaneAndThenOr32WithSusWrite (
          &HsioLane,
          R_HSIO_PCR_RX_DWORD25,
          (UINT32) ~B_HSIO_PCR_RX_DWORD25_CTLE_ADAPT_OFFSET_CFG_4_0,
          (UINT32) (HsioPciePreMemConfig->Lane[Index].HsioRxSetCtle << N_HSIO_PCR_RX_DWORD25_CTLE_ADAPT_OFFSET_CFG_4_0)
          );
        DEBUG ((DEBUG_INFO, "HSIO : PortID = 0x%02x, Offset = 0x%04x, Value = 0x%08x\n", HsioLane.Pid, HsioLane.Base + R_HSIO_PCR_RX_DWORD25, HsioLaneRead32 (&HsioLane, R_HSIO_PCR_RX_DWORD25)));
      }

      if ((HsioPciePreMemConfig->Lane[Index].HsioTxGen1DownscaleAmpEnable == TRUE) || (HsioPciePreMemConfig->Lane[Index].HsioTxGen1DeEmphEnable == TRUE)) {
        //
        // Remember which ports were populated before temporarily disabling them
        //
        if ((PciSegmentRead32 (RpBase) != 0xFFFFFFFF) && (PciSegmentRead16 (RpBase + R_PCH_PCIE_CFG_LSTS) & B_PCIE_LSTS_LA)) {
          RpToRetrain |= (BIT0 << Index);
        }
        PciSegmentOr8 (RpBase + R_PCH_PCIE_CFG_LCTL, B_PCIE_LCTL_LD);
      }

      if ((HsioPciePreMemConfig->Lane[Index].HsioTxGen1DownscaleAmpEnable == TRUE) ||
          (HsioPciePreMemConfig->Lane[Index].HsioTxGen2DownscaleAmpEnable == TRUE) ||
          (HsioPciePreMemConfig->Lane[Index].HsioTxGen3DownscaleAmpEnable == TRUE)) {

        Data32Or  = 0;
        Data32And = 0xFFFFFFFF;
        if (HsioPciePreMemConfig->Lane[Index].HsioTxGen1DownscaleAmpEnable == TRUE) {
          Data32Or |= (UINT32) (HsioPciePreMemConfig->Lane[Index].HsioTxGen1DownscaleAmp << N_HSIO_PCR_TX_DWORD8_ORATE00MARGIN_5_0);
          Data32And &= (UINT32) ~B_HSIO_PCR_TX_DWORD8_ORATE00MARGIN_5_0;
        }

        if (HsioPciePreMemConfig->Lane[Index].HsioTxGen2DownscaleAmpEnable == TRUE) {
          Data32Or |= (UINT32) (HsioPciePreMemConfig->Lane[Index].HsioTxGen2DownscaleAmp << N_HSIO_PCR_TX_DWORD8_ORATE01MARGIN_5_0);
          Data32And &= (UINT32) ~B_HSIO_PCR_TX_DWORD8_ORATE01MARGIN_5_0;
        }

        if (HsioPciePreMemConfig->Lane[Index].HsioTxGen3DownscaleAmpEnable == TRUE) {
          Data32Or |= (UINT32) (HsioPciePreMemConfig->Lane[Index].HsioTxGen3DownscaleAmp << N_HSIO_PCR_TX_DWORD8_ORATE10MARGIN_5_0);
          Data32And &= (UINT32) ~B_HSIO_PCR_TX_DWORD8_ORATE10MARGIN_5_0;
        }

        HsioLaneAndThenOr32WithSusWrite (&HsioLane, R_HSIO_PCR_TX_DWORD8, Data32And, Data32Or);
        DEBUG ((DEBUG_INFO, "HSIO : PortID = 0x%02x, Offset = 0x%04x, Value = 0x%08x\n", HsioLane.Pid, HsioLane.Base + R_HSIO_PCR_TX_DWORD8, HsioLaneRead32 (&HsioLane, R_HSIO_PCR_TX_DWORD8)));
      }

      if ((HsioPciePreMemConfig->Lane[Index].HsioTxGen1DeEmphEnable == TRUE) ||
          (HsioPciePreMemConfig->Lane[Index].HsioTxGen2DeEmph3p5Enable == TRUE)) {

        Data32Or  = 0;
        Data32And = 0xFFFFFFFF;
        if (HsioPciePreMemConfig->Lane[Index].HsioTxGen1DeEmphEnable == TRUE) {
          Data32Or |= (UINT32) (HsioPciePreMemConfig->Lane[Index].HsioTxGen1DeEmph << N_HSIO_PCR_TX_DWORD5_OW2TAPGEN1DEEMPH3P5_5_0);
          Data32And &= (UINT32) ~B_HSIO_PCR_TX_DWORD5_OW2TAPGEN1DEEMPH3P5_5_0;
        }

        if (HsioPciePreMemConfig->Lane[Index].HsioTxGen2DeEmph3p5Enable == TRUE) {
          Data32Or |= (UINT32) (HsioPciePreMemConfig->Lane[Index].HsioTxGen2DeEmph3p5 << N_HSIO_PCR_TX_DWORD5_OW2TAPGEN2DEEMPH3P5_5_0);
          Data32And &= (UINT32) ~B_HSIO_PCR_TX_DWORD5_OW2TAPGEN2DEEMPH3P5_5_0;
        }

        HsioLaneAndThenOr32WithSusWrite (&HsioLane, R_HSIO_PCR_TX_DWORD5, Data32And, Data32Or);
        DEBUG ((DEBUG_INFO, "HSIO : PortID = 0x%02x, Offset = 0x%04x, Value = 0x%08x\n", HsioLane.Pid, HsioLane.Base + R_HSIO_PCR_TX_DWORD5, HsioLaneRead32 (&HsioLane, R_HSIO_PCR_TX_DWORD5)));
      }

      if (HsioPciePreMemConfig->Lane[Index].HsioTxGen2DeEmph6p0Enable == TRUE) {
        HsioLaneAndThenOr32WithSusWrite (
          &HsioLane,
          R_HSIO_PCR_TX_DWORD6,
          (UINT32) ~B_HSIO_PCR_TX_DWORD6_OW2TAPGEN2DEEMPH6P0_5_0,
          (UINT32) (HsioPciePreMemConfig->Lane[Index].HsioTxGen2DeEmph6p0 << N_HSIO_PCR_TX_DWORD6_OW2TAPGEN2DEEMPH6P0_5_0)
          );
        DEBUG ((DEBUG_INFO, "HSIO : PortID = 0x%02x, Offset = 0x%04x, Value = 0x%08x\n", HsioLane.Pid, HsioLane.Base + R_HSIO_PCR_TX_DWORD6, HsioLaneRead32 (&HsioLane, R_HSIO_PCR_TX_DWORD6)));
      }

      if ((HsioPciePreMemConfig->Lane[Index].HsioTxGen1DownscaleAmpEnable == TRUE) || (HsioPciePreMemConfig->Lane[Index].HsioTxGen1DeEmphEnable == TRUE)) {
        PciSegmentAnd8 (RpBase + R_PCH_PCIE_CFG_LCTL, (UINT8) ~(B_PCIE_LCTL_LD));
      }
    }
  }
  //
  // According to PCIE spec, following Link Disable PCIE device may take up to 100ms to become operational.
  // Wait until all ports are operational again or until 100ms passed
  //
  TimeSpent = 0;
  while ((TimeSpent < 100) && (RpToRetrain != 0)) {
    for (Index = 0; Index < MaxPciePorts; Index++) {
      if ((RpToRetrain & (BIT0 << Index)) == 0) {
        continue;
      }
      RpBase = PchPcieBase (Index);
      if (PciSegmentRead16 (RpBase + R_PCH_PCIE_CFG_LSTS) & B_PCIE_LSTS_LA) {
        RpToRetrain &= ~(BIT0 << Index);
      }
    }
    MicroSecondDelay (1000);
    TimeSpent++;
  }

}

/**
  The function program HSIO registers.

  @param[in] SiPreMemPolicyPpi         The SI PREMEM Policy PPI instance

  @retval EFI_SUCCESS                   THe HSIO settings have been programmed correctly
**/
VOID
PchHsioBiosProgPreMem (
  IN  SI_PREMEM_POLICY_PPI             *SiPreMemPolicyPpi
  )
{
  DEBUG ((DEBUG_INFO, "PchHsioBiosProgPreMem() Start\n"));
  PchHsioRxTxEqPolicySataProg (SiPreMemPolicyPpi);
  PchHsioRxTxEqPolicyPcieProg (SiPreMemPolicyPpi);
  DEBUG ((DEBUG_INFO, "PchHsioBiosProgPreMem() End\n"));
}
