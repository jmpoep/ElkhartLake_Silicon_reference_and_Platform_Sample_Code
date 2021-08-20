/** @file
  This file contains code that performs PCIe link equalization procedure.

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
#include <Library/IoLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/TimerLib.h>
#include <Library/PciExpressHelpersLib.h>
#include <IndustryStandard/Pci30.h>
#include <PchLimits.h>
#include <Library/PciSegmentLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PchSbiAccessLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PchPcieRpLib.h>
#include <Uefi/UefiBaseType.h>
#include <Library/PeiPcieRpLib.h>
#include <PcieRegs.h>
#include <Register/PchPcieRpRegs.h>
#include <Library/PcieHelperLib.h>

#include "PcieRpInitInternal.h"

/**
  Reads out internal signal state from the PCIe RP hardware.
  This is accomplished with monitor mux register in RP.

  @param[in] RpBase       PCI base of the RP
  @param[in] SignalIndex  Index of the signal to read

  @return Value of the signal state.
**/
STATIC
UINT32
PcieGetInternalSignalState (
  IN UINT64 RpBase,
  IN UINT32 SignalIndex
  )
{
  ASSERT (SignalIndex < 0x100);

  PciSegmentWrite32 (RpBase + R_PCH_PCIE_CFG_MM, SignalIndex);
  return PciSegmentRead32 (RpBase + R_PCH_PCIE_CFG_MM) >> N_PCH_PCIE_CFG_MM_MSST;
}

/**
  Dumps best EQ coefficients values that were selected during EQ.

  @param[in]  RpBase       PCI base of the RP
  @param[in]  RpLaneIndex  Lane index of the RP
**/
STATIC
VOID
PcieDumpBestEqCoefficients (
  IN UINT64  RpBase,
  IN UINT32  RpLaneIndex
  )
{
  UINT32 Index;
  UINT32 SignalState;

  DEBUG ((DEBUG_INFO, "  ranks "));
  for (Index = 0; Index < 4; ++Index) {
    // Lane0: 0x0F 0x10 0x11 0x12
    // Lane1: 0x4F 0x50 0x51 0x52
    // Lane2: 0x8F 0x90 0x91 0x92
    // Lane3: 0xCF 0xD0 0xD1 0xD2
    SignalState = PcieGetInternalSignalState (RpBase, RpLaneIndex * 0x40 + 0x0F + Index);
    DEBUG ((DEBUG_INFO, " 0x%08x", SignalState));
  }
  DEBUG ((DEBUG_INFO, "\n"));
}

/**
  Dump Figure of merit scoreboard(FOMS) for each of the root port lanes.

  @param[in] RpBase       PCI base of the RP
  @param[in] RpLaneIndex  Index of the root port lane
**/
STATIC
VOID
PcieDumpFoms (
  IN UINT64  RpBase,
  IN UINT32  RpLaneIndex
  )
{
  UINT32 ListEntryIndex;
  UINT32 Foms;

  DEBUG ((DEBUG_INFO, "%d.%d FOM Scoreboard:\n", PciePortNum (RpBase), RpLaneIndex));
  for (ListEntryIndex = 0; ListEntryIndex < 10; ListEntryIndex += 3) {
    //
    // FOMV field holds FOM values for 3 list entires. To select correct triplet
    // we use Index field.
    //
    PciSegmentAndThenOr32 (
      RpBase + R_PCH_PCIE_CFG_FOMS,
      (UINT32) ~(B_PCH_PCIE_CFG_FOMS_I | B_PCH_PCIE_CFG_FOMS_LN),
      ((ListEntryIndex/3)  << N_PCH_PCIE_CFG_FOMS_I) | (RpLaneIndex << N_PCH_PCIE_CFG_FOMS_LN)
      );
    Foms = PciSegmentRead32 (RpBase + R_PCH_PCIE_CFG_FOMS);
    DEBUG ((DEBUG_INFO, "%d:%03d  ", ListEntryIndex,     (Foms & B_PCH_PCIE_CFG_FOMS_FOMSV0) >> N_PCH_PCIE_CFG_FOMS_FOMSV0));
    DEBUG ((DEBUG_INFO, "%d:%03d  ", ListEntryIndex + 1, (Foms & B_PCH_PCIE_CFG_FOMS_FOMSV1) >> N_PCH_PCIE_CFG_FOMS_FOMSV1));
    DEBUG ((DEBUG_INFO, "%d:%03d\n", ListEntryIndex + 2, (Foms & B_PCH_PCIE_CFG_FOMS_FOMSV2) >> N_PCH_PCIE_CFG_FOMS_FOMSV2));
  }
}

/**
  Dump PCIe HW EQ results. For internal use only.

  @param[in] RpBase  PCI base of the RP
**/
STATIC
VOID
PcieDumpHwEqResults (
  IN UINT64  RpBase
  )
{
  UINT32  RpLaneIndex;
  UINT32  MaxLinkWidth;
  UINT32  TimeoutUs;

  MaxLinkWidth = GetMaxLinkWidth (RpBase);

 if ((PciSegmentRead16 (RpBase + R_PCH_PCIE_CFG_LSTS) & B_PCIE_LSTS_LA) == 0) {
    DEBUG ((DEBUG_ERROR, "No link after EQ!\n"));
    return;
  }

  //
  // Wait for link training to complete
  //
  for (TimeoutUs = 0; TimeoutUs < 5000000; TimeoutUs += 10) {
    if ((PciSegmentRead16 (RpBase + R_PCH_PCIE_CFG_LSTS) & B_PCIE_LSTS_LT) == 0) {
      break;
    }
    MicroSecondDelay (10);
  }
  DEBUG ((DEBUG_INFO, "HW EQ finished, results:\n"));
  DEBUG ((DEBUG_INFO, "EQCFG1: 0x%08x\n", PciSegmentRead32 (RpBase + R_PCH_PCIE_CFG_EQCFG1)));
  DEBUG ((DEBUG_INFO, "LSTS2:  0x%04x\n", PciSegmentRead16 (RpBase + R_PCH_PCIE_CFG_LSTS2)));
  DEBUG ((DEBUG_INFO, "Training time = %dus\n", TimeoutUs));

  for (RpLaneIndex = 0; RpLaneIndex < MaxLinkWidth; RpLaneIndex++) {
    PcieDumpFoms (RpBase, RpLaneIndex);
    PcieDumpBestEqCoefficients (RpBase, RpLaneIndex);
  }
}

/**
  Set the preset/coefficient list entry to the desired value.

  @param[in] RpBase          PCI base of the root port
  @param[in] ListEntryIndex  Index of the entry
  @param[in] ListEntryValue  Value of the entry
**/
STATIC
VOID
PcieSetPresetCoefficientListEntry (
  IN UINT64  RpBase,
  IN UINT32  ListEntryIndex,
  IN UINT32  ListEntryValue
  )
{
  UINT32  ListEntryRegisterIndex;
  UINT32  ListEntryFieldIndex;

  ASSERT (ListEntryIndex < 20);
  ASSERT ((ListEntryValue & ~0x3F) == 0);

  //
  // Preset/Coefficient list is kept in hardware in a set
  // of continous registers each of which contains 5 list entries.
  //
  ListEntryRegisterIndex = ListEntryIndex / 5;
  ListEntryFieldIndex = ListEntryIndex % 5;

  PciSegmentAndThenOr32 (
    RpBase + R_PCH_PCIE_CFG_RTPCL1 + (4 * ListEntryRegisterIndex),
    (UINT32) ~(0x3F << (6 * ListEntryFieldIndex)),
    (ListEntryValue << (6 * ListEntryFieldIndex))
    );
}

/**
  Sets the EQ mode that will be used by root port.

  @param[in] RpBase          PCI base of the root port
  @param[in] PcieLinkEqMode  Choosen mode of the EQ
**/
STATIC
VOID
PcieSetEqMode (
  IN UINT64             RpBase,
  IN PCIE_LINK_EQ_MODE  PcieLinkEqMode
  )
{
  switch (PcieLinkEqMode) {
    case PcieLinkEqPresetMode:
      PciSegmentAnd32 (RpBase + R_PCH_PCIE_CFG_RTPCL1, (UINT32) ~B_PCH_PCIE_CFG_RTPCL1_PCM);
      break;
    case PcieLinkEqCoefficientMode:
      PciSegmentOr32 (RpBase + R_PCH_PCIE_CFG_RTPCL1, B_PCH_PCIE_CFG_RTPCL1_PCM);
      break;
    default:
      ASSERT (FALSE);
      break;
  }
}

/**
  Sets transmitter lane presets for both upstream and downstream port.

  @param[in] RpBase                PCI base of the RP
  @param[in] LaneIndex             Index of the transmitter lane
  @param[in] DownstreamPortPreset  Preset value for the downstream port
  @param[in] UpstreamPortPreset    Preset value for the upstream port
**/
STATIC
VOID
PcieSetTransmitterLanePreset (
  IN UINT64  RpBase,
  IN UINT32  LaneIndex,
  IN UINT32  DownstreamPortPreset,
  IN UINT32  UpstreamPortPreset
  )
{
  UINT32  PresetRegisterIndex;
  UINT32  DownstreamPortPresetFieldIndex;
  UINT32  UpstreamPortPresetFieldIndex;

  //
  // Each register holds preset values for 2 lanes.
  //
  PresetRegisterIndex = LaneIndex / 2;

  //
  // Each of the lanes configuration spaces contains fields
  // for downstream and upstream preset. To select correct preset
  // we calculate the lane index inside the register by doing %2 operation
  // on global lane index and then multiply it by 2 to get downstream preset
  // index field. The layout of the register is as follows:
  // -Downstream port lane 0 preset configration - preset config 0
  // -Upstream port lane 0 preset configuration - preset config 1
  // -Downstream port lane 1 preset configuration - preset config 2
  // -Upstream port lane 1 preste configuration - preset config 3
  //
  DownstreamPortPresetFieldIndex = (LaneIndex % 2) * 2;
  UpstreamPortPresetFieldIndex = DownstreamPortPresetFieldIndex + 1;

  PciSegmentAndThenOr32 (
    RpBase + R_PCH_PCIE_CFG_EX_L01EC + (4 * PresetRegisterIndex),
    ~(UINT32)((B_PCH_PCIE_CFG_EX_L01EC_TP << (DownstreamPortPresetFieldIndex * S_PCH_PCIE_CFG_EX_L01EC_TP)) |
              (B_PCH_PCIE_CFG_EX_L01EC_TP << (UpstreamPortPresetFieldIndex * S_PCH_PCIE_CFG_EX_L01EC_TP))),
    (DownstreamPortPreset << (DownstreamPortPresetFieldIndex * S_PCH_PCIE_CFG_EX_L01EC_TP)) |
    (UpstreamPortPreset << (UpstreamPortPresetFieldIndex * S_PCH_PCIE_CFG_EX_L01EC_TP))
    );
}

/**
  Sets required transmitter presets for the root port.
  Those presets will be used during phase 1 of the equalization process
  to establish initial communication at higher speed.

  @param[in] RpBase              PCI base of the RP
  @param[in] PcieLinkEqSettings  PCIe link EQ settings
**/
STATIC
VOID
PcieSetTransmitterPresets (
  IN UINT64                 RpBase,
  IN PCIE_LINK_EQ_SETTINGS  *PcieLinkEqSettings
  )
{
  UINT32  LaneIndex;

  // This code only supports PCIe root ports with up
  // to 4 PCIe lanes.
  //
  for (LaneIndex = 0; LaneIndex < 4; LaneIndex++) {
    PcieSetTransmitterLanePreset (
      RpBase,
      LaneIndex,
      PcieLinkEqSettings->PlatformSettings.Ph1DownstreamPortTransmitterPreset,
      PcieLinkEqSettings->PlatformSettings.Ph1UpstreamPortTransmitterPreset
      );
  }
}

/**
  Starts the EQ process.

  @param[in] RpBase  PCI base of the RP
**/
STATIC
VOID
PcieStartEqualization (
  IN UINT64  RpBase
  )
{
  DEBUG ((DEBUG_INFO, "Starting Equalization with following settings:\n"));
  DEBUG ((DEBUG_INFO, "EQCFG1: 0x%08x\n", PciSegmentRead32 (RpBase + R_PCH_PCIE_CFG_EQCFG1)));
  DEBUG ((DEBUG_INFO, "EQCFG2: 0x%08x\n", PciSegmentRead32 (RpBase + R_PCH_PCIE_CFG_EQCFG2)));
  DEBUG ((DEBUG_INFO, "HAEQ:   0x%08x\n", PciSegmentRead32 (RpBase + R_PCH_PCIE_CFG_HAEQ)));

  //
  // Set target link speed to gen3
  //
  PciSegmentAndThenOr16 (RpBase + R_PCH_PCIE_CFG_LCTL2, (UINT16) ~B_PCIE_LCTL2_TLS, 3);
  //
  // Set the perform equalization bit and start the link retrain.
  //
  PciSegmentOr32 (RpBase + R_PCH_PCIE_CFG_EX_LCTL3, B_PCIE_EX_LCTL3_PE);
  PciSegmentOr32 (RpBase + R_PCH_PCIE_CFG_LCTL, B_PCIE_LCTL_RL);
}

/**
  Reset and enable Recovery Entry and Idle Framing Error Count

  @param[in] RpBase    Root Port base address
**/
STATIC
VOID
PcieResetErrorCounts (
  UINT64 RpBase
  )
{
  PciSegmentAnd32 (RpBase + R_PCH_PCIE_CFG_EQCFG1, (UINT32) ~B_PCH_PCIE_CFG_EQCFG1_REIFECE);
  PciSegmentOr32 (RpBase + R_PCH_PCIE_CFG_EQCFG1, B_PCH_PCIE_CFG_EQCFG1_REIFECE);
}

/**
  Initializes preset list that will be used during EQ

  @param[in] RpBase       PCI base of the RP
  @param[in] PresetList   Pointer to the preset list
  @param[in] PresetCount  Number of presets in the list
**/
STATIC
VOID
PcieInitializePresetList (
  IN UINT64  RpBase,
  IN UINT32  *PresetList,
  IN UINT32  PresetCount
  )
{
  UINT32  PresetIndex;

  if (PresetCount >= 11) {
    ASSERT (FALSE);
    return;
  }

  for (PresetIndex = 0; PresetIndex < PresetCount; PresetIndex++) {
    DEBUG ((DEBUG_INFO, "PCIe EQ: Setting preset %d, preset value = %d\n", PresetIndex, PresetList[PresetIndex]));

    PcieSetPresetCoefficientListEntry (RpBase, PresetIndex, PresetList[PresetIndex]);
  }
}

/**
  Initializes coefficient list that will be used during EQ.

  @param[in] RpBase            PCI base of the RP
  @param[in] CoefficientsList  Pointer on the coefficients list
  @param[in] CoefficientCount  Number of coefficients in the list
**/
STATIC
VOID
PcieInitializeCoefficientsList (
  IN UINT64                     RpBase,
  IN PCIE_LINK_EQ_COEFFICIENTS  *CoefficientsList,
  IN UINT32                     CoefficientCount
  )
{
  UINT32  CoefficientIndex;
  UINT32  PreCursorListIndex;
  UINT32  PostCursorListIndex;

  if (CoefficientCount >= 10) {
    ASSERT (FALSE);
    return;
  }

  for (CoefficientIndex = 0; CoefficientIndex < CoefficientCount; CoefficientIndex++) {
    DEBUG ((DEBUG_INFO, "PCIe EQ: Setting coefficient %d, pre-cursor = %d, post-cursor = %d\n",
            CoefficientIndex,
            CoefficientsList[CoefficientIndex].PreCursor,
            CoefficientsList[CoefficientIndex].PostCursor));
    //
    // Coefficient list in the hardware is kept as a list of alternating pre and post cursor coefficients.
    // The layout of the hardware list is as follows:
    // pre-cursor coefficient 0 - index 0
    // post-cursor coefficient 0 - index 1
    // pre-cursor coefficient 1 - index 2
    // ...
    //
    PreCursorListIndex = CoefficientIndex * 2;
    PostCursorListIndex = PreCursorListIndex + 1;

    PcieSetPresetCoefficientListEntry (RpBase, PreCursorListIndex, CoefficientsList[CoefficientIndex].PreCursor);
    PcieSetPresetCoefficientListEntry (RpBase, PostCursorListIndex, CoefficientsList[CoefficientIndex].PostCursor);
  }
}

/**
  Sets up the hardware for autonomus equalization.

  @param[in] RpBase              PCI base of the RP
  @param[in] PcieLinkEqSettings  PCIe link EQ settings
**/
STATIC
VOID
PcieSetupHardwareEq (
  IN UINT64                 RpBase,
  IN PCIE_LINK_EQ_SETTINGS  *PcieLinkEqSettings
  )
{
  UINT32  PresetCoefficientEvaluationTimeMs;

  PcieSetEqMode (RpBase, PcieLinkEqSettings->PlatformSettings.PcieLinkEqMode);
  switch (PcieLinkEqSettings->PlatformSettings.PcieLinkEqMode) {
    case PcieLinkEqPresetMode:
      PcieInitializePresetList (RpBase, PcieLinkEqSettings->PlatformSettings.Ph3PresetList, PcieLinkEqSettings->PlatformSettings.Ph3NumberOfPresetsOrCoefficients);
      break;
    case PcieLinkEqCoefficientMode:
      PcieInitializeCoefficientsList (RpBase, PcieLinkEqSettings->PlatformSettings.Ph3CoefficientsList, PcieLinkEqSettings->PlatformSettings.Ph3NumberOfPresetsOrCoefficients);
      break;
    default:
     DEBUG ((DEBUG_ERROR, "Incorrect equalization mode\n"));
     ASSERT (FALSE);
  }

  //
  // This programing tells hardware to perform preset/coefficient search only up to the given preset/coefficient. We want hardware to search
  // all presets/coefficients that were passed in the list to BIOS. This register is 0 based, meaning that value of 0 will cause hardware to
  // terminate search after preset/coefficient 0.
  //
  PciSegmentAndThenOr32 (
    RpBase + R_PCH_PCIE_CFG_EQCFG2,
    (UINT32) ~B_PCH_PCIE_CFG_EQCFG2_HAPCSB,
    (PcieLinkEqSettings->PlatformSettings.Ph3NumberOfPresetsOrCoefficients - 1) << N_PCH_PCIE_CFG_EQCFG2_HAPCSB
    );

  //
  // Program the preset/coefficient evaluation time depending on the number of presets/coefficients used in EQ.
  // HW EQ has to be finished within 24ms so the more coefficient/presets we have to evaluate the less time we can
  // spend on each.
  // NOTE: Encoding of the register is not 1:1 with time in ms. Please see register description for details.
  //
  if (PcieLinkEqSettings->PlatformSettings.Ph3NumberOfPresetsOrCoefficients <= 5) {
    PresetCoefficientEvaluationTimeMs = 4; // 4 = 4ms
  } else if (PcieLinkEqSettings->PlatformSettings.Ph3NumberOfPresetsOrCoefficients <= 7) {
    PresetCoefficientEvaluationTimeMs = 0; // 0 = 2ms
  } else {
    //
    // Need more time for 8 list entries.
    // [1807268382]
    //
    PresetCoefficientEvaluationTimeMs = 2; // 2 = 3ms
  }

  PciSegmentAndThenOr32 (
    RpBase + R_PCH_PCIE_CFG_EQCFG2,
    (UINT32) ~B_PCH_PCIE_CFG_EQCFG2_PCET,
    PresetCoefficientEvaluationTimeMs << N_PCH_PCIE_CFG_EQCFG2_PCET
    );

  //
  // Set Receiver wait time for EQ evaluation to 1us.
  //
  PciSegmentAndThenOr32 (
    RpBase + R_PCH_PCIE_CFG_EQCFG1,
    (UINT32) ~(V_PCH_PCIE_CFG_EQCFG1_RWTNEVE << N_PCH_PCIE_CFG_EQCFG1_RWTNEVE),
    1 << N_PCH_PCIE_CFG_EQCFG1_RWTNEVE
    );

  //
  // Set the receiver eye width margin error threshold to 2 errors.
  // The value of the error threshold is calculated in hardware by
  // multiplying value from REWMET with multiplier from REWMETM. Value
  // of 0 in REWMETM means no multiplier.
  //
  PciSegmentAndThenOr32 (
    RpBase + R_PCH_PCIE_CFG_EQCFG2,
    (UINT32) ~(B_PCH_PCIE_CFG_EQCFG2_REWMET | B_PCH_PCIE_CFG_EQCFG2_REWMETM),
    2
    );

  //
  // Set HAEQ.DL to 0xE
  //
  PciSegmentOr32 (
    RpBase + R_PCH_PCIE_CFG_HAEQ,
    0xE << N_PCH_PCIE_CFG_HAEQ_DL
    );
  //
  // Set HAEQ.HAPCCPI to 0x2
  //
  PciSegmentAndThenOr32 (
    RpBase + R_PCH_PCIE_CFG_HAEQ,
    (UINT32)~(B_PCH_PCIE_CFG_HAEQ_HAPCCPI),
    (UINT32) (0x2 << N_PCH_PCIE_CFG_HAEQ_HAPCCPI)
    );
}

/**
  Sets up hardware for fixed EQ method.

  @param[in] RpBase              PCI base of the RP
  @param[in] PcieLinkEqSettings  PCIe link EQ settings
**/
STATIC
VOID
PcieSetupFixedEq (
  IN UINT64                 RpBase,
  IN PCIE_LINK_EQ_SETTINGS  *PcieLinkEqSettings
  )
{
  UINT32  LinkWidth;

  LinkWidth = GetMaxLinkWidth (RpBase);
  if (PcieLinkEqSettings->PlatformSettings.Ph3NumberOfPresetsOrCoefficients < LinkWidth) {
    DEBUG ((DEBUG_ERROR, "Fixed EQ requested with insufficient number of presets or coefficients\n"));
    ASSERT (FALSE);
    return;
  }

  //
  // Set preset/coefficient evaluation bypass and override enable. This will cause the root port
  // to unconditionally accept remote transmiter values.
  //
  PciSegmentOr32 (RpBase + R_PCH_PCIE_CFG_EQCFG1, B_PCH_PCIE_CFG_EQCFG1_RTPCOE | B_PCH_PCIE_CFG_EQCFG1_RTLEPCEB);
  PcieSetEqMode (RpBase, PcieLinkEqSettings->PlatformSettings.PcieLinkEqMode);

  //
  // Fixed equalization algorithm performs remote transmitter override instead of searching for best values.
  // In remote transmitter override mode the meaning of preset list and coefficient list is changed and instead
  // of containing the list of values that should be searched it contains fixed values of the presets or coefficients
  // for each PCIe lane that will be used to override.
  //
  switch (PcieLinkEqSettings->PlatformSettings.PcieLinkEqMode) {
    case PcieLinkEqPresetMode:
      PcieInitializePresetList (RpBase, PcieLinkEqSettings->PlatformSettings.Ph3PresetList, LinkWidth);
      break;
    case PcieLinkEqCoefficientMode:
      PcieInitializeCoefficientsList (RpBase, PcieLinkEqSettings->PlatformSettings.Ph3CoefficientsList, LinkWidth);
      break;
    default:
     DEBUG ((DEBUG_ERROR, "Incorrect equalization mode\n"));
     ASSERT (FALSE);
  }
}

/**
  Clears EQ related registers to guard against EQ reruns and bad defaults.

  @param[in] RpBase  PCI base of the root port
**/
STATIC
VOID
PcieClearEqRegisters (
  IN UINT64  RpBase
  )
{
  PciSegmentWrite32 (RpBase + R_PCH_PCIE_CFG_EQCFG1, 0);
  PciSegmentWrite32 (RpBase + R_PCH_PCIE_CFG_EQCFG2, 0);
  PciSegmentWrite32 (RpBase + R_PCH_PCIE_CFG_HAEQ, 0);
}

typedef struct {
  UINT32  CursorRegisterOffset;
  UINT32  CursorFieldOffset;
  UINT32  PreCursorRegisterOffset;
  UINT32  PreCursorFieldOffset;
  UINT32  PostCursorRegisterOffset;
  UINT32  PostCursorFieldOffset;
} PRESET_TO_COEFFICIENT_REGISTER_LAYOUT;

/**
  Get the preset registers and fields offsets.

  @param[in]  PresetIndex    Index of the preset
  @param[out] RegisterLayout At return a structure that describes preset layout in memory.
**/
VOID
GetPresetToCoefficientRegisterLayout (
  IN  UINT32                                PresetIndex,
  OUT PRESET_TO_COEFFICIENT_REGISTER_LAYOUT *RegisterLayout
  )
{
  //
  // Each dword register contains 5 fields, each preset uses 3 fields
  // where:
  // 1st field is cursor value
  // 2nd field is pre cursor value
  // 3rd field is post cursor value
  // Each field is 6-bit wide
  //
  RegisterLayout->CursorRegisterOffset = ((PresetIndex * 3) / 5) * 4;
  RegisterLayout->PreCursorRegisterOffset = (((PresetIndex * 3) + 1) / 5) * 4;
  RegisterLayout->PostCursorRegisterOffset = (((PresetIndex * 3) + 2) / 5) * 4;
  RegisterLayout->CursorFieldOffset = ((PresetIndex * 3) % 5) * 6;
  RegisterLayout->PreCursorFieldOffset = (((PresetIndex * 3) + 1) % 5) * 6;
  RegisterLayout->PostCursorFieldOffset = (((PresetIndex * 3) + 2) % 5) * 6;
}

/**
  Set preset coefficients.

  @param[in] RpBase               PCIe root port base
  @param[in] LaneIndex            PCIe lane for which to set coefficients
  @param[in] PresetIndex          Preset index for the given lane
  @param[in] LowFrequencyValue    Low frequency value for the given lane
  @param[in] FullSwingValue       Full swing value for the given lane
  @param[in] PresetToCoefficient  Structure with information about coefficients for the preset
**/
STATIC
VOID
SetPresetToCoefficientMapping (
  IN UINT64                              RpBase,
  IN UINT32                              LaneIndex,
  IN UINT32                              PresetIndex,
  IN UINT32                              LowFrequencyValue,
  IN UINT32                              FullSwingValue,
  IN PCIE_PRESET_TO_COEFFICIENT_MAPPING  PresetToCoefficient
  )
{
  UINT64                                 LaneBase;
  PRESET_TO_COEFFICIENT_REGISTER_LAYOUT  RegisterLayout;

  LaneBase = RpBase + R_PCH_PCIE_CFG_LANE0_PRESETS + (LaneIndex * S_PCH_PCIE_CFG_SINGLE_LANE_PRESETS);
  GetPresetToCoefficientRegisterLayout (PresetIndex, &RegisterLayout);

  PciSegmentAndThenOr32 (
    LaneBase + RegisterLayout.CursorRegisterOffset,
    ~(0x3F << RegisterLayout.CursorFieldOffset),
    (PresetToCoefficient.CursorCoefficient & 0x3F) << RegisterLayout.CursorFieldOffset
    );
  PciSegmentAndThenOr32 (
    LaneBase + RegisterLayout.PreCursorRegisterOffset,
    ~(0x3F << RegisterLayout.PreCursorFieldOffset),
    (PresetToCoefficient.PreCursorCoefficient & 0x3F) << RegisterLayout.PreCursorFieldOffset
    );
  PciSegmentAndThenOr32 (
    LaneBase + RegisterLayout.PostCursorRegisterOffset,
    ~(0x3F << RegisterLayout.PostCursorFieldOffset),
    (PresetToCoefficient.PostCursorCoefficient & 0x3F) << RegisterLayout.PostCursorFieldOffset
    );
  PciSegmentAndThenOr32 (
    LaneBase + R_PCH_PCIE_CFG_LFFS_OFFSET_FROM_LANE_BASE,
    ~(UINT32)((0x3F << N_PCH_PCIE_CFG_LFFS_FS) | 0x3F),
    ((FullSwingValue & 0x3F) << N_PCH_PCIE_CFG_LFFS_FS) | (LowFrequencyValue & 0x3F)
    );
}

/**
  Get coefficients values corresponding to given preset.
  This function will return valid values only after
  PcieConfigurePresetToCoefficientMapping has been called.

  @param[in]  RpBase        PCI base of the RP
  @param[in]  LaneIndex     PCIe lane for which to get coefficients
  @param[in]  PresetIndex   Preset index for given lane
  @param[out] Coefficients  Value of the coefficients extracted from RP HW
**/
STATIC
VOID
GetPresetToCoefficientMapping (
  IN  UINT64                     RpBase,
  IN  UINT32                     LaneIndex,
  IN  UINT32                     PresetIndex,
  OUT PCIE_LINK_EQ_COEFFICIENTS  *Coefficients
  )
{
  UINT64                                 LaneBase;
  PRESET_TO_COEFFICIENT_REGISTER_LAYOUT  RegisterLayout;

  LaneBase = RpBase + R_PCH_PCIE_CFG_LANE0_PRESETS + (LaneIndex * S_PCH_PCIE_CFG_SINGLE_LANE_PRESETS);
  GetPresetToCoefficientRegisterLayout (PresetIndex, &RegisterLayout);

  Coefficients->PreCursor = (PciSegmentRead32 (LaneBase + RegisterLayout.PreCursorRegisterOffset) >> RegisterLayout.PreCursorFieldOffset) & 0x3F;
  Coefficients->PostCursor = (PciSegmentRead32 (LaneBase + RegisterLayout.PostCursorRegisterOffset) >> RegisterLayout.PostCursorFieldOffset) & 0x3F;
}

/**
  Programs presets-to-coefficients mapping for hardware equalization.
  It should not be performed for ports without Gen3 capability

  @param[in] RpBase             PCI base of the RP
  @param[in] PcieLinkEqSettings Pointer to PCIe link EQ settings
**/
STATIC
VOID
PcieConfigurePresetToCoefficientMapping (
  IN UINT64                 RpBase,
  IN PCIE_LINK_EQ_SETTINGS  *PcieLinkEqSettings
  )
{
  UINT32  LaneIndex;
  UINT32  PresetIndex;
  UINT32  TimeoutUs;

  if (!PcieLinkEqSettings->ProjectSettings.PipePresetToCoefficientQuerySupported) {
    //
    // If query to PIPE is unsupported we need to program project's recommendation from IP
    //
    for (LaneIndex = 0; LaneIndex < GetMaxLinkWidth (RpBase); LaneIndex++) {
      for (PresetIndex = 0; PresetIndex < ARRAY_SIZE (PcieLinkEqSettings->ProjectSettings.PresetToCoefficient); PresetIndex++) {
        SetPresetToCoefficientMapping (
          RpBase,
          LaneIndex,
          PresetIndex,
          PcieLinkEqSettings->ProjectSettings.LowFrequencyValue,
          PcieLinkEqSettings->ProjectSettings.FullSwingValue,
          PcieLinkEqSettings->ProjectSettings.PresetToCoefficient[PresetIndex]
        );
      }
    }
  } else {
    //
    // If supported send a query to PIPE
    //
    PciSegmentOr32 (RpBase + R_PCH_PCIE_CFG_EQCFG1, B_PCH_PCIE_CFG_EQCFG1_HPCMQE);
    TimeoutUs = 1000;
    while (TimeoutUs-- > 0) {
      if ((PciSegmentRead32 (RpBase + R_PCH_PCIE_CFG_EQCFG1) & B_PCH_PCIE_CFG_EQCFG1_HPCMQE) == 0) {
        return;
      }
      MicroSecondDelay (1);
    }
    ASSERT (FALSE);
  }
}

/**
  Sets local transmitter override coefficients for a
  given lane.

  @param[in] RpBase            PCI base of the RP
  @param[in] LaneIndex         Index of the PCI lane
  @param[in] LaneCoefficients  Coefficients to be programed
**/
STATIC
VOID
PcieSetLocalTransmitterOverrideCoefficients (
  IN UINT64                     RpBase,
  IN UINT32                     LaneIndex,
  IN PCIE_LINK_EQ_COEFFICIENTS  *LaneCoefficients
  )
{
  UINT32  LaneRegisterIndex;
  UINT32  LaneIndexInsideRegister;

  ASSERT ((LaneCoefficients->PreCursor & ~0x3F) == 0);
  ASSERT ((LaneCoefficients->PostCursor & ~0x3F) == 0);

  //
  // Each of the local transmitter override registers
  // holds configuration fields for 2 PCIe lanes.
  // The layout of the register is as follows
  // lower lane pre-cursor value
  // lower lane post-cursor value
  // upper lane pre-cursor value
  // upper lane post-cursor value
  // lower lane local transmitter override enable
  // upper lane local transmitter override enable
  // Cursor values fields are 6 bits wide.
  //
  LaneRegisterIndex = LaneIndex / 2;
  LaneIndexInsideRegister = LaneIndex % 2;

  //
  // We program the LTCXX register in 2 writes since according to PCIe BWG
  // the pre and post cursor values must be valid at the time of setting the
  // override enable bits.
  //
  PciSegmentAndThenOr32 (
    RpBase + R_PCH_PCIE_CFG_LTCO1 + (4 * LaneRegisterIndex),
    (UINT32) ~((0x3F << (6 * LaneIndexInsideRegister)) | (0x3F << (12 * LaneIndexInsideRegister))),
    (LaneCoefficients->PreCursor << (6 * LaneIndexInsideRegister) | (LaneCoefficients->PostCursor << (12 * LaneIndexInsideRegister)))
    );

  PciSegmentOr32 (
    RpBase + R_PCH_PCIE_CFG_LTCO1 + (4 * LaneRegisterIndex),
    B_PCH_PCIE_CFG_LTCO1_L0TCOE << LaneIndexInsideRegister
    );
}

/**
  If local transmitter override is enabled this function will
  program all of the required coefficients overrides.

  @param[in] RpBase              PCI base of the RP
  @param[in] PcieLinkEqSettings  PCIe link EQ settings
**/
STATIC
VOID
PcieSetupEqPh2 (
  IN UINT64                 RpBase,
  IN PCIE_LINK_EQ_SETTINGS  *PcieLinkEqSettings
  )
{
  UINT32                     LaneIndex;
  UINT8                      LinkWidth;
  PCIE_LINK_EQ_COEFFICIENTS  LaneCoefficients;

  if (!PcieLinkEqSettings->PlatformSettings.LocalTransmitterOverrideEnable) {
    return;
  }

  LinkWidth = PcieGetNegotiatedLinkWidth (RpBase);
  for (LaneIndex = 0; LaneIndex < LinkWidth; LaneIndex++) {
    //
    // Even though hardware supports override only
    // with coefficients due to user convenience BIOS API
    // allows to choose override preset instead. We translate the
    // preset to the appropriate coefficient values as set in
    // preset to coefficient mapping register and use those coefficient
    // values during override. This is done so that user can choose from well
    // defined presets instead of the phy specific coefficients.
    //
    GetPresetToCoefficientMapping (
      RpBase,
      LaneIndex,
      PcieLinkEqSettings->PlatformSettings.Ph2LocalTransmitterOverridePreset,
      &LaneCoefficients
      );

    PcieSetLocalTransmitterOverrideCoefficients (
      RpBase,
      LaneIndex,
      &LaneCoefficients
      );
  }
}

/**
  Prints PCIe equalization settings

  @param[in] PcieLinkEqSettings  Pointer to PCIe link EQ settings
**/
STATIC
VOID
PciePrintEqConfig (
  IN PCIE_LINK_EQ_SETTINGS  *PcieLinkEqSettings
  )
{
  UINT8  Index;

  DEBUG ((DEBUG_INFO, "Printing PCIe equalization settings\n"));
  DEBUG ((DEBUG_INFO, "PcieLinkEqMethod = %d\n", PcieLinkEqSettings->PlatformSettings.PcieLinkEqMethod));
  DEBUG ((DEBUG_INFO, "PcieLinkEqMode = %d\n", PcieLinkEqSettings->PlatformSettings.PcieLinkEqMode));
  DEBUG ((DEBUG_INFO, "Ph1DownstreamPortTransmitterPreset = %d\n", PcieLinkEqSettings->PlatformSettings.Ph1DownstreamPortTransmitterPreset));
  DEBUG ((DEBUG_INFO, "Ph1UpstreamPortTransmitterPreset = %d\n", PcieLinkEqSettings->PlatformSettings.Ph1UpstreamPortTransmitterPreset));
  DEBUG ((DEBUG_INFO, "Ph3NumberOfPresetsOrCoefficients = %d\n", PcieLinkEqSettings->PlatformSettings.Ph3NumberOfPresetsOrCoefficients));
  if (PcieLinkEqSettings->PlatformSettings.PcieLinkEqMode == PcieLinkEqPresetMode) {
    for (Index = 0; Index < PcieLinkEqSettings->PlatformSettings.Ph3NumberOfPresetsOrCoefficients && Index < PCIE_LINK_EQ_PRESETS_MAX; Index++) {
      DEBUG ((DEBUG_INFO, "Phase 3 Preset %d = %d\n", Index, PcieLinkEqSettings->PlatformSettings.Ph3PresetList[Index]));
    }
  } else {
    for (Index = 0; Index < PcieLinkEqSettings->PlatformSettings.Ph3NumberOfPresetsOrCoefficients && Index < PCIE_LINK_EQ_COEFFICIENTS_MAX; Index++) {
      DEBUG ((DEBUG_INFO, "Phase 3 Coefficient %d, pre-cursor = %d, post-cursor = %d\n",
                            Index,
                            PcieLinkEqSettings->PlatformSettings.Ph3CoefficientsList[Index].PreCursor,
                            PcieLinkEqSettings->PlatformSettings.Ph3CoefficientsList[Index].PostCursor));
    }
  }
  DEBUG ((DEBUG_INFO, "Phase 2 local transmitter override enable = %d\n", PcieLinkEqSettings->PlatformSettings.LocalTransmitterOverrideEnable));
  DEBUG ((DEBUG_INFO, "Phase 2 local transmitter override preset = %d\n", PcieLinkEqSettings->PlatformSettings.Ph2LocalTransmitterOverridePreset));
  DEBUG ((DEBUG_INFO, "PipePresetToCoefficientQuerySupported = %d\n", PcieLinkEqSettings->ProjectSettings.PipePresetToCoefficientQuerySupported));
  if (!PcieLinkEqSettings->ProjectSettings.PipePresetToCoefficientQuerySupported) {
    DEBUG ((DEBUG_INFO, "LowFrequencyValue = %d\n", PcieLinkEqSettings->ProjectSettings.LowFrequencyValue));
    DEBUG ((DEBUG_INFO, "FullSwingValue = %d\n", PcieLinkEqSettings->ProjectSettings.FullSwingValue));
    for (Index = 0; Index < PCIE_LINK_EQ_PRESETS_MAX; Index++) {
      DEBUG ((DEBUG_INFO, "Preset %d, pre-cursror = %d, cursor = %d, post-cursor = %d\n",
                            Index,
                            PcieLinkEqSettings->ProjectSettings.PresetToCoefficient[Index].PreCursorCoefficient,
                            PcieLinkEqSettings->ProjectSettings.PresetToCoefficient[Index].CursorCoefficient,
                            PcieLinkEqSettings->ProjectSettings.PresetToCoefficient[Index].PostCursorCoefficient));
    }
  }
}

/**
  Performs PCIe link equalization according to platform settings.
  Please make sure that link is in gen1 or gen2 before calling this
  procedure.

  @param[in] RpBase              PCI base of the RP
  @param[in] Gen3DeviceAttached  Gen3 capable device is attached to the root port
  @param[in] PcieLinkEqSettings  PCIe link equalization settings to be used during EQ
**/
VOID
PcieLinkEqualize (
  IN UINT64                         RpBase,
  IN BOOLEAN                        Gen3DeviceAttached,
  IN PCIE_LINK_EQ_SETTINGS          *PcieLinkEqSettings
  )
{
  PciePrintEqConfig (PcieLinkEqSettings);
  PcieClearEqRegisters (RpBase);
  PcieConfigurePresetToCoefficientMapping (RpBase, PcieLinkEqSettings);
  PcieSetTransmitterPresets (RpBase, PcieLinkEqSettings);
  PcieSetupEqPh2 (RpBase, PcieLinkEqSettings);

  switch (PcieLinkEqSettings->PlatformSettings.PcieLinkEqMethod) {
    case PcieLinkHardwareEq:
      PcieSetupHardwareEq (RpBase, PcieLinkEqSettings);
      break;
    case PcieLinkFixedEq:
      PcieSetupFixedEq (RpBase, PcieLinkEqSettings);
      break;
    default:
      DEBUG ((DEBUG_ERROR, "Invalid PCIe link EQ method\n"));
      ASSERT (FALSE);
      break;
  }

  //
  // Setup EQ when there is gen3 capable endpoint attached.
  // [1807268382]-2
  //
  if (Gen3DeviceAttached) {
    PcieStartEqualization (RpBase);
    DEBUG_CODE_BEGIN ();
    if (PcieLinkEqSettings->PlatformSettings.PcieLinkEqMethod == PcieLinkHardwareEq) {
      PcieDumpHwEqResults (RpBase);
    }
    DEBUG_CODE_END ();
  }

  PcieResetErrorCounts (RpBase);
}

