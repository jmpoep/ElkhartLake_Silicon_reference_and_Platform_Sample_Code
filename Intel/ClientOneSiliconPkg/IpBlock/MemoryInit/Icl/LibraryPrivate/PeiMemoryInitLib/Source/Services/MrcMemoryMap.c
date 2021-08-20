/** @file
  The functions in this file initializes the physical memory map.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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
//
// Include files
//
#include "MrcMemoryMap.h"

/**
  After BIOS determines the total physical memory size.
  Determines TOM which is defined by the total physical memory size.
  Determines TOM minus the ME memory size. The ME memory size is calculated from MESEG_BASE and MESEG_MASK.
  Determines MMIO allocation, which is system configuration dependent.

  Determines TOLUD which is the minimum value by comparing between "4GB minus MMIO size" and "TOM minus ME size".
  Determines Graphics Stolen Base, BDSM by subtracting the graphics data stolen memory size from TOLUD.
  Graphics Data Stolen Memory size is given by GMS field in GGC register.  It must be define before this stage.
  Determines Graphics GTT Stolen Base, BGSM by subtracting the GTT graphics stolen memory size from BDSM.
  GTT Stolen Memory size is given by GGMS field in GGC register.  It must be define before this stage.
  Determines TSEG Base, TSEGMB by subtracting TSEG size from BGSM.
  TSEG should be defined.
  Remove the memory hole caused by aligning TSEG to a 8MB boundary.
  Determine whether Memory Reclaim is available.  If "TOM minus ME Stolem Memory Size" is greater than the value of TOLUD, then memory reclaim is available to enable.
  Determine REMAPBASE if reclaim is enabled.  This is the maximum value by comparing between 4GB and "TOM minus ME size".
  Determine REMAPLIMIT () if reclaim is enabled.  This is the value of REMAPBASE plus "the difference between the value in TOLUD register and the lower of either 4GB or 'TOM minus ME Stolen memory size", and then minus 1 boundary.
  Determine TOUUD. TOUUD indicates the address one byte above the maximum DRAM.  If relcaim is disabled, this value is calculated by "TOM minus ME stolen size".  Otherwise, this value is set to REMAPLIMIT plus 1MB.

  @param[in, out] MrcData - Include all MRC global data. include also the memory map data.

  @retval MrcStatus -  if the reset is succeded.
**/
MrcStatus
MrcSetMemoryMap (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcDebug                *Debug;
  MrcInput                *Inputs;
  const MRC_FUNCTION      *MrcCall;
  MrcOutput               *Outputs;
  MrcMemoryMap            *MemoryMap;
  MrcGfxDataSize          GraphicsStolenSize;
  GGC_0_0_0_PCI_STRUCT    Ggc;
  UINT32                  Gms;
  UINT32                  Offset;
  UINT32                  TsegBaseOrg;
  UINT32                  PrmrrBaseOrg;
  UINT32                  PrmrrAlign;
  INT32                   TsegAlignment;
  UINT32                  MmioSize;
  UINT32                  PsmiRegionSize;
  UINT32                  LowestBase;
  UINT32                  ImrBaseOrg;

  Inputs    = &MrcData->Inputs;
  MrcCall   = Inputs->Call.Func;
  Outputs   = &MrcData->Outputs;
  Debug     = &Outputs->Debug;
  MemoryMap = &Outputs->MemoryMapData;

  //
  // Find the total memory size
  //
  MrcTotalMemory (MrcData);

  //
  // Set TOM register
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TOM (Total physical memory size) = %u MB\n", MemoryMap->TotalPhysicalMemorySize);

  //
  // Find the TOM minus ME size only for internal calculations
  //
  //
  // @todo: KBL temporary solution
  //
  MemoryMap->TomMinusMe = MemoryMap->TotalPhysicalMemorySize;

  MmioSize = Inputs->MmioSize;
  if (Inputs->MemoryTrace) {
    if (MemoryMap->TotalPhysicalMemorySize <= MEM_4GB) {
      MmioSize = MAX (MmioSize, MEM_4GB - MemoryMap->TotalPhysicalMemorySize / 2);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Adjusted MmioSize = %Xh\n", MmioSize);
    }
  }

  //
  // Find and set TOLUD.
  // TOLUD which is the minimum value by comparing between "4GB minus MMIO size" and "TOM minus ME size"
  //
  MemoryMap->ToludBase = MIN (MemoryMap->TomMinusMe, MEM_4GB - MmioSize);

  //
  // Find PsmiRegionSize
  //
  PsmiRegionSize = Outputs->GtPsmiRegionSize;

  //
  // Find and set BDSM Graphics Stolen Base.
  // Graphics Stolen Base, BDSM by subtracting the graphics data stolen memory size and PSMI region size from TOLUD.
  //
  GraphicsStolenSize = Outputs->GraphicsStolenSize;
  MemoryMap->BdsmBase = MemoryMap->ToludBase - GraphicsStolenSize - PsmiRegionSize;

  //
  // Graphics GTT Stolen Base
  // Graphics GTT Stolen Base, BGSM by subtracting the GTT graphics stolen memory size from BDSM.
  //
  MemoryMap->GttBase = MemoryMap->BdsmBase - Outputs->GraphicsGttSize;

  //
  // Graphics size register init.
  //
  Offset   = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, GGC_0_0_0_PCI_REG);
  Ggc.Data = (UINT16) MrcCall->MrcMmioRead32 (Offset);

  Ggc.Bits.VAMEN= (Inputs->GfxIsVersatileAcceleration == TRUE) ? 1 : 0;
  if (Outputs->GraphicsGttSize > 0) {
    Ggc.Bits.GGMS = MIN (GGC_0_0_0_PCI_GGMS_MAX, MrcLog2 (Outputs->GraphicsGttSize) - 1);
  } else {
    Ggc.Bits.GGMS = 0;
  }

  //
  // Graphics Stolen Size below 64MB has a higher granularity and can be set in 4MB increments
  // For Sizes 4MB to 60MB sizes (excluding 32MB), GMS values range from 240-254 (240 + Size/4 - 1)
  // Graphics Stolen Size above 64MB has a granularity of 32MB increments
  // For Sizes 0, 32MB and above 64MB GMS values are Size/32
  //
  if ((GraphicsStolenSize == 32) || (GraphicsStolenSize == 0) || (GraphicsStolenSize >= 64)) {
    Gms = GraphicsStolenSize / 32;
  } else {
    Gms = 240 + (GraphicsStolenSize / 4 - 1);
  }
  Ggc.Bits.GMS = (UINT16) MIN (GGC_0_0_0_PCI_GMS_MAX, Gms);

  MemoryMap->GraphicsControlRegister = Ggc.Data;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "GGC value = %Xh\n", MemoryMap->GraphicsControlRegister);

  //
  // TSEG Base
  //
  MemoryMap->TsegBase = MemoryMap->GttBase - Inputs->TsegSize;
  LowestBase = MemoryMap->TsegBase;

  //
  // DPR is after TSEG.
  //
  MemoryMap->DprSize  = Inputs->DprSize;
  LowestBase         -= Inputs->DprSize;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Unaligned TSEG base = %Xh\n", MemoryMap->TsegBase);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Unaligned GTT base = %Xh\n", MemoryMap->GttBase);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Unaligned BDSM base = %Xh\n", MemoryMap->BdsmBase);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Unaligned TOLUD base = %Xh\n", MemoryMap->ToludBase);

  //
  // Reserve PRAM region after the DPR region.
  //
  if (Inputs->PramSize > 0) {
    LowestBase          -= Inputs->PramSize;
    MemoryMap->PramBase  = LowestBase;
  }


  //
  // Reserve PRMRR region after the DPR region.
  //
  if (Inputs->PrmrrSize > 0) {
    PrmrrBaseOrg  = LowestBase - Inputs->PrmrrSize;

    //
    // Size aligned
    //
    MemoryMap->PrmrrBase = PrmrrBaseOrg & ~(Inputs->PrmrrSize - 1);

    //
    // Used to align other regions
    //
    PrmrrAlign = PrmrrBaseOrg - MemoryMap->PrmrrBase;
    LowestBase = MemoryMap->PrmrrBase;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "PRMRR base = %Xh\n", MemoryMap->PrmrrBase);
  } else {
    //
    // No shift for no PRMRR
    //
    PrmrrAlign = 0;
  }

  //
  //  Align TSEG to PRMRR.
  //
  MemoryMap->TsegBase = MemoryMap->TsegBase - PrmrrAlign;

  //
  //  Align TSEG to natural alignment.
  //
  if (MemoryMap->TsegBase != (MemoryMap->TsegBase & ~(Inputs->TsegSize - 1))) {
    TsegBaseOrg = MemoryMap->TsegBase;
    if (Inputs->PrmrrSize > 0) {

      //
      // If PRMRR is present, naturally align TSEG up.
      //
      MemoryMap->TsegBase = (MemoryMap->TsegBase & ~(Inputs->TsegSize - 1)) + Inputs->TsegSize;
    } else {

      //
      // No PRMRR so naturally align TSEG down.
      //
      MemoryMap->TsegBase = (MemoryMap->TsegBase & ~(Inputs->TsegSize - 1));
    }

    //
    // Calculate the delta to shift BDSM, GTT, and TOLUD with TSEG.
    // DPR is always right below TSEG so it's shift is implied.
    //
    TsegAlignment = ((INT32) MemoryMap->TsegBase) - ((INT32) TsegBaseOrg);
  } else {

    //
    // TSEG is already aligned
    //
    TsegAlignment = 0;
  }

  //
  // Shift everything up through TOLUD.
  //
  MemoryMap->GttBase   = ((UINT32) (((INT32) (MemoryMap->GttBase - PrmrrAlign)) + TsegAlignment));
  MemoryMap->BdsmBase  = ((UINT32) (((INT32) (MemoryMap->BdsmBase - PrmrrAlign)) + TsegAlignment));
  MemoryMap->ToludBase = ((UINT32) (((INT32) (MemoryMap->ToludBase - PrmrrAlign)) + TsegAlignment));

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TSEG base = %Xh\n", MemoryMap->TsegBase);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "GTT base = %Xh\n", MemoryMap->GttBase);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "BDSM base = %Xh\n", MemoryMap->BdsmBase);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TOLUD base = %Xh\n", MemoryMap->ToludBase);

  //
  // In order to avoid memory hole, assign LowestBase to new aligned DPRBASE when PRMRR is absent.
  //

  if (Inputs->PrmrrSize == 0) {
    LowestBase = MemoryMap->TsegBase - Inputs->DprSize;
    if (Inputs->PramSize > 0) {
      LowestBase -= Inputs->PramSize;
    }
  }


  // Ibecc: Keep Remap disabled when 2GB Physical Memory or less
  if ((Inputs->Ibecc == TRUE) && ((Inputs->IbeccOperationMode == 0) || (Inputs->IbeccOperationMode == 2)) && (MemoryMap->TomMinusMe <= 0x800)) {
    Inputs->RemapEnable = 0;
  }

  //
  // test if Reclaim is available
  // If "TOM minus ME Stolem Memory Size" is greater than the value of TOLUD, then memory reclaim is available to enable
  //
  if (Inputs->RemapEnable && (MemoryMap->TomMinusMe > MemoryMap->ToludBase)) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Reclaim Enable\n");
    MemoryMap->ReclaimEnable = TRUE;
    //
    // Remap Base
    // This is the maximum value by comparing between 4GB and "TOM minus ME size".
    //
    MemoryMap->RemapBase = MAX (MEM_4GB, MemoryMap->TomMinusMe);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Remap Base %Xh\n", MemoryMap->RemapBase);
    //
    // Remap Limit
    // This is the value of REMAPBASE plus "the difference between the value in TOLUD
    // register and the lower of either 4GB or 'TOM minus ME Stolen memory size", and
    // then minus 1MB boundary.
    //
    MemoryMap->RemapLimit = MemoryMap->RemapBase + (MIN (MEM_4GB, MemoryMap->TomMinusMe) - MemoryMap->ToludBase);

    MemoryMap->TouudBase = MemoryMap->RemapLimit;

    MemoryMap->RemapLimit -= 0x1;

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Remap Limit %Xh\n", MemoryMap->RemapLimit);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TOUUD Base %Xh\n", MemoryMap->TouudBase);
  } else {
    MemoryMap->ReclaimEnable = FALSE;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Reclaim disable \n");
    //
    // TOUUD Base
    // If relcaim is disabled, this value is calculated by "TOM minus ME stolen size".
    //
    MemoryMap->TouudBase = MemoryMap->TomMinusMe;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TOUUD Base %Xh\n", MemoryMap->TouudBase);
  }

  // Ibecc
  Outputs->IbeccEdsrSize = 0;
  if ((Inputs->Ibecc == TRUE) && ((Inputs->IbeccOperationMode == 0) || (Inputs->IbeccOperationMode == 2))) {
    UINT32 IbeccEdsr;
    IbeccEdsr = MemoryMap->TouudBase - (MemoryMap->TouudBase / 32);
    // Specifies the start Address of ECC data storage. Corresponds to CMI address [38:24] at the input of IBECC
    IbeccEdsr >>= 24 - 20;
    IbeccEdsr <<= 24 - 20;
    Outputs->IbeccEdsrSize = MemoryMap->TouudBase - IbeccEdsr;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "IbeccEdsr = %Xh\n IbeccEdsrSize = %u MB\n", IbeccEdsr, Outputs->IbeccEdsrSize);
  }

  //
  // Reserve IMR region.
  // Must be aligned to largest IMR Size
  //
  if (Inputs->MeStolenSize > 0) {
    ImrBaseOrg  = LowestBase - Inputs->MeStolenSize;
    //
    // Largest IMR size alignment
    //
    MemoryMap->MeStolenBase = ImrBaseOrg & ~(Inputs->ImrAlignment - 1);
    LowestBase = MemoryMap->MeStolenBase;
  }
  MemoryMap->MeStolenSize = Inputs->MeStolenSize;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ME stolen base %Xh\nME stolen size %Xh\n", MemoryMap->MeStolenBase, MemoryMap->MeStolenSize);

  //
  // Shift from MB's to actual address.
  //
  LowestBase = LowestBase << 20;

  MemoryMap->LowestBase = LowestBase;

  UpdateMemoryMapRegisters (MrcData, Inputs->PciEBaseAddress, MemoryMap);

  // Print the relevant registers for the address decode/encode tool
  // TOLUD=0xec00000 REMAP_BASE=0x00000003ffb00000 REMAP_LIMIT=0x00000003ffa00000 TOM=0x200000000 CHANNEL_HASH=0x11026a80 CHANNEL_EHASH=0x11026a80 MAD_INTER_CHNL=0x3004000 MAD_INTRA_CHNL_ch0=0x70003000 MAD_INTRA_CHNL_ch1=0x70003000 MAD_DIMM_ch0=0x9040008 MAD_DIMM_ch1=0x20102
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TOLUD=0x%x REMAP_BASE=0x%llx REMAP_LIMIT=0x%llx ",
    MemoryMap->ToludBase << 20,
    MrcCall->MrcLeftShift64 (MemoryMap->RemapBase, REMAPBASE_REMAPBASE_OFF),
    MrcCall->MrcLeftShift64 (MemoryMap->RemapLimit, REMAPLIMIT_REMAPLMT_OFF)
    );
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TOM=0x%llx CHANNEL_HASH=0x%x CHANNEL_EHASH=0x%x ",
    MrcCall->MrcLeftShift64 (MemoryMap->TotalPhysicalMemorySize, TOM_0_0_0_PCI_TOM_OFF),
    MrcReadCR (MrcData, CHANNEL_HASH_REG),
    MrcReadCR (MrcData, CHANNEL_EHASH_REG)
    );
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MAD_INTER_CHNL=0x%x MAD_INTRA_CHNL_ch0=0x%x MAD_INTRA_CHNL_ch1=0x%x ",
    MrcReadCR (MrcData, MAD_INTER_CHANNEL_REG),
    MrcReadCR (MrcData, MAD_INTRA_CH0_REG),
    MrcReadCR (MrcData, MAD_INTRA_CH1_REG)
    );
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MAD_DIMM_ch0=0x%x MAD_DIMM_ch1=0x%x MCMNTS_SPARE=0x%x\n",
    MrcReadCR (MrcData, MAD_DIMM_CH0_REG),
    MrcReadCR (MrcData, MAD_DIMM_CH1_REG),
    MrcReadCR (MrcData, CH0_CR_MCMNTS_SPARE_REG)  // @todo read from first populated channel; also move this to end of MRC
    );

  // Set Gfx Mem Map
  MrcCall->MrcSetGfxMemMap();

  return mrcSuccess;
}

/**
  This function find the total memory in the system.
  and write it to TotalPhysicalMemorySize in MrcData structure.

  @param[in, out] MrcData - Include all MRC global data.

  @retval Nothing
**/
void
MrcTotalMemory (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  MrcDimmOut        *DimmOut;
  UINT8             Controller;
  UINT8             Channel;
  UINT8             Dimm;
  MrcMemoryMap      *MemoryMapData;

  Outputs = &MrcData->Outputs;
  MemoryMapData = &Outputs->MemoryMapData;

  MemoryMapData->TotalPhysicalMemorySize = 0;
  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerOut = &Outputs->Controller[Controller];
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut           = &ControllerOut->Channel[Channel];
      ChannelOut->Capacity = 0;
      if (MrcChannelExist (Outputs, Channel)) {
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DimmOut->Status == DIMM_PRESENT) {
            ChannelOut->Capacity += DimmOut->DimmCapacity;
          }
        }
        ChannelOut->Capacity = MIN (ChannelOut->Capacity, Outputs->MrcTotalChannelLimit);
        MemoryMapData->TotalPhysicalMemorySize += ChannelOut->Capacity;
      }
    }
  }

  return;
}

/**
  This function write the memory map registers.

  @param[in] PciEBaseAddress - Address of the PCI Express BAR
  @param[in] MemoryMap       - Include all the memory map definitions

  @retval Nothing
**/
void
UpdateMemoryMapRegisters (
  IN OUT MrcParameters  *const MrcData,
  IN const UINT32              PciEBaseAddress,
  IN const MrcMemoryMap *const MemoryMap
  )
{
  const MRC_FUNCTION                             *MrcCall;
  TOM_0_0_0_PCI_STRUCT                           Tom;
  TOLUD_0_0_0_PCI_STRUCT                         Tolud;
  TOUUD_0_0_0_PCI_STRUCT                         Touud;
  REMAPBASE_STRUCT                               RemapBase;
  REMAPLIMIT_STRUCT                              RemapLimit;
  TSEGMB_0_0_0_PCI_STRUCT                        Tsegmb;
  BDSM_0_0_0_PCI_STRUCT                          Bdsm;
  BGSM_0_0_0_PCI_STRUCT                          Bgsm;
  DPR_0_0_0_PCI_STRUCT                           Dpr;
  UINT32                                         Offset;
#if 0
  IMRIAEXCBASE_MCHBAR_CBO_INGRESS_STRUCT         ImrExcBase;
  IMRIAEXCLIMIT_MCHBAR_CBO_INGRESS_STRUCT        ImrExcLimit;
#endif

  MrcCall = MrcData->Inputs.Call.Func;

  //
  // Write TOM register
  //
  Tom.Data     = MrcCall->MrcLeftShift64 (MemoryMap->TotalPhysicalMemorySize, TOM_0_0_0_PCI_TOM_OFF);
  Offset       = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, TOM_0_0_0_PCI_REG);
  MrcCall->MrcMmioWrite32 (Offset, Tom.Data32[0]);
  MrcCall->MrcMmioWrite32 (Offset  + 4, Tom.Data32[1]);

  //
  // Write TOLUD register
  //
  Tolud.Data       = 0;
  Tolud.Bits.TOLUD = MemoryMap->ToludBase;
  Offset           = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, TOLUD_0_0_0_PCI_REG);
  MrcCall->MrcMmioWrite32 (Offset, Tolud.Data);

  //
  // Write TOUUD register
  //
  Touud.Data       = MrcCall->MrcLeftShift64 (MemoryMap->TouudBase, TOUUD_0_0_0_PCI_TOUUD_OFF);
  Offset           = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, TOUUD_0_0_0_PCI_REG);
  MrcCall->MrcMmioWrite32 (Offset, Touud.Data32[0]);
  MrcCall->MrcMmioWrite32 (Offset + 4, Touud.Data32[1]);

  if (MemoryMap->ReclaimEnable) {
    RemapBase.Data           = MrcCall->MrcLeftShift64 (MemoryMap->RemapBase, REMAPBASE_REMAPBASE_OFF);
    RemapLimit.Data          = MrcCall->MrcLeftShift64 (MemoryMap->RemapLimit, REMAPLIMIT_REMAPLMT_OFF);
  } else {
    // Program default values for Remap Disabled
    RemapLimit.Data = 0;
    RemapBase.Data  = MrcCall->MrcLeftShift64 (REMAPBASE_REMAPBASE_DEF, REMAPBASE_REMAPBASE_OFF);
  }
  //
  // CNL must have a shadow copy of TOLUD, REMAPBASE, and REMAPLIMIT in the MC domain.
  // This assumes the lock bits haven't been set in the PCI writes, reuses the PCI variable data.
  //
  MrcWriteCR (MrcData, TOLUD_REG, Tolud.Data);
  MrcWriteCR64 (MrcData, REMAPBASE_REG, RemapBase.Data);
  MrcWriteCR64 (MrcData, REMAPLIMIT_REG, RemapLimit.Data);

  //
  // Write TSEGMB register
  //
  Offset             = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, TSEGMB_0_0_0_PCI_REG);
  Tsegmb.Data        = 0;
  Tsegmb.Bits.TSEGMB = MemoryMap->TsegBase;
  MrcCall->MrcMmioWrite32 (Offset, Tsegmb.Data);

  //
  // Program DPR Register with DPR size & DMA Protection Enabled
  //
  if (MemoryMap->DprSize != 0) {
    Offset           = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, DPR_0_0_0_PCI_REG);
    Dpr.Data         = MrcCall->MrcMmioRead32 (Offset);
    Dpr.Bits.DPRSIZE = MemoryMap->DprSize;
    Dpr.Bits.EPM     = 1;
    MrcCall->MrcMmioWrite32 (Offset, Dpr.Data);
  }
  //
  // Write BDSM register
  //
  Offset          = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, BDSM_0_0_0_PCI_REG);
  Bdsm.Data       = 0;
  Bdsm.Bits.BDSM  = MemoryMap->BdsmBase;
  MrcCall->MrcMmioWrite32 (Offset, Bdsm.Data);

  //
  // Write BGSM register
  //
  Offset          = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, BGSM_0_0_0_PCI_REG);
  Bgsm.Data       = 0;
  Bgsm.Bits.BGSM  = MemoryMap->GttBase;
  MrcCall->MrcMmioWrite32 (Offset, Bgsm.Data);
#if 0
  //
  //  MRC needs to configure IA and GT exclusion range to cover the IMR region.
  //    IMRIAEXCLBASE (MCHBAR + 0x6A40h[38:10]) and IMRGTEXCLBASE (MCHBAR + 0x6A48h[38:10]) should be programmed to the lowest address (base) of the IMR region.
  //    IMRIAEXCLIMIT (MCHBAR + 0x6A50h[38:10]) should be programmed to the highest address (base + IMR Size) of the IMR region.
  //    IMRGTEXCLIMIT (MCHBAR + 0x6A58h[38:10]) should be programmed to the highest address (base + Size) of the combined (IMR / DPR / PRMRR / TSEG) stolen region.
  //    Note: the programming of "base + size" here as opposed to "base + size - 1" is intended.
  //
  ImrExcBase.Data                     = 0;
  ImrExcLimit.Data                    = 0;
  ImrExcBase.Bits.imriaexcbaseLow     = MemoryMap->MeStolenBase << 10;
  ImrExcBase.Bits.imriaexcbaseHigh    = MemoryMap->MeStolenBase >> 12;
  ImrExcLimit.Bits.imriaexclimitLow   = (MemoryMap->MeStolenBase + MrcData->Inputs.MeStolenSize) << 10;
  ImrExcLimit.Bits.imriaexclimitHigh  = (MemoryMap->MeStolenBase + MrcData->Inputs.MeStolenSize) >> 12;

  MrcWriteCR64 (MrcData, IMRIAEXCBASE_MCHBAR_CBO_INGRESS_REG, ImrExcBase.Data);
  MrcWriteCR64 (MrcData, IMRIAEXCLIMIT_MCHBAR_CBO_INGRESS_REG, ImrExcLimit.Data);

  ImrExcLimit.Bits.imriaexclimitLow  = (MemoryMap->TsegBase + MrcData->Inputs.TsegSize) << 10;
  ImrExcLimit.Bits.imriaexclimitHigh = (MemoryMap->TsegBase + MrcData->Inputs.TsegSize) >> 12;

  MrcWriteCR64 (MrcData, IMRGTEXCBASE_MCHBAR_CBO_INGRESS_REG, ImrExcBase.Data);
  MrcWriteCR64 (MrcData, IMRGTEXCLIMIT_MCHBAR_CBO_INGRESS_REG, ImrExcLimit.Data);
#endif
  //
  // Write graphics control register
  //
  Offset = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, GGC_0_0_0_PCI_REG);
  MrcCall->MrcMmioWrite32 (Offset, MemoryMap->GraphicsControlRegister);

  return;
}
