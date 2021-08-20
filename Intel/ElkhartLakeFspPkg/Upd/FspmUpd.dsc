## @file
#  Platform description.
#
# @copyright
#  INTEL CONFIDENTIAL
#  Copyright 2017 - 2020 Intel Corporation.
#
#  The source code contained or described herein and all documents related to the
#  source code ("Material") are owned by Intel Corporation or its suppliers or
#  licensors. Title to the Material remains with Intel Corporation or its suppliers
#  and licensors. The Material may contain trade secrets and proprietary and
#  confidential information of Intel Corporation and its suppliers and licensors,
#  and is protected by worldwide copyright and trade secret laws and treaty
#  provisions. No part of the Material may be used, copied, reproduced, modified,
#  published, uploaded, posted, transmitted, distributed, or disclosed in any way
#  without Intel's prior express written permission.
#
#  No license under any patent, copyright, trade secret or other intellectual
#  property right is granted to or conferred upon you by disclosure or delivery
#  of the Materials, either expressly, by implication, inducement, estoppel or
#  otherwise. Any license under such intellectual property rights must be
#  express and approved by Intel in writing.
#
#  Unless otherwise agreed by Intel in writing, you may not remove or alter
#  this notice or any other notice embedded in Materials by Intel or
#  Intel's suppliers or licensors in any way.
#
#  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
#  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
#  the terms of your license agreement with Intel or your vendor. This file may
#  be modified by the user, subject to additional terms of the license agreement.
#
# @par Specification
##

  ################################################################################
  #
  # UPDs consumed in FspMemoryInit Api
  #
  ################################################################################
  # !BSF FIND:{EHLUPD_M}
  # !HDR COMMENT:{FSP_UPD_HEADER:FSP UPD Header}
  # !HDR EMBED:{FSP_UPD_HEADER:FspUpdHeader:START}
  # FspmUpdSignature: {EHLUPD_M}
  gPlatformFspPkgTokenSpaceGuid.Signature                   | * | 0x08 | 0x4D5F4450554C4845
  # !BSF NAME:{FspmUpdRevision}  TYPE:{None}
  gPlatformFspPkgTokenSpaceGuid.Revision                    | * | 0x01 | 0x00
  # !HDR EMBED:{FSP_UPD_HEADER:FspUpdHeader:END}
  gPlatformFspPkgTokenSpaceGuid.Reserved                    | * | 0x17 | {0x00}

  # !HDR COMMENT:{FSPM_ARCH_UPD:Fsp M Architecture UPD}
  # !HDR EMBED:{FSPM_ARCH_UPD:FspmArchUpd:START}
  gPlatformFspPkgTokenSpaceGuid.Revision                    | * | 0x01 | 0x01

  gPlatformFspPkgTokenSpaceGuid.Reserved                    | * | 0x03 | {0x00}

  # !HDR STRUCT:{VOID *}
  gPlatformFspPkgTokenSpaceGuid.NvsBufferPtr                | * | 0x04 | 0x00000000

  # !HDR STRUCT:{VOID *}
  gPlatformFspPkgTokenSpaceGuid.StackBase                   | * | 0x04 | 0xFEF17F00

  gPlatformFspPkgTokenSpaceGuid.StackSize                   | * | 0x04 | 0x28000

  gPlatformFspPkgTokenSpaceGuid.BootLoaderTolumSize         | * | 0x04 | 0x00000000

  gPlatformFspPkgTokenSpaceGuid.BootMode                    | * | 0x04 | 0x00

  # !HDR EMBED:{FSPM_ARCH_UPD:FspmArchUpd:END}
  gPlatformFspPkgTokenSpaceGuid.Reserved1                   | * | 0x08 | {0x00}

  # !HDR COMMENT:{FSP_M_CONFIG:Fsp M Configuration}
  # !HDR EMBED:{FSP_M_CONFIG:FspmConfig:START}
  # !BSF PAGE:{MRC}
  # !BSF NAME:{Platform Reserved Memory Size} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{The minimum platform memory size required to pass control into DXE}
  gPlatformFspPkgTokenSpaceGuid.PlatformMemorySize          | * | 0x08 | 0x400000

  # !BSF NAME:{SPD Data Length} TYPE:{Combo}
  # !BSF OPTION:{0x100:256 Bytes, 0x200:512 Bytes}
  # !BSF HELP:{Length of SPD Data}
  gPlatformFspPkgTokenSpaceGuid.MemorySpdDataLen            | * | 0x02 | 0x200

  # !BSF NAME:{Enable above 4GB MMIO resource support} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable above 4GB MMIO resource support}
  gPlatformFspPkgTokenSpaceGuid.EnableAbove4GBMmio          | * | 0x01 | 0x01

  # !BSF NAME:{Enable/Disable CrashLog Device 10} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable(Default): Enable CPU CrashLog Device 10, Disable: Disable CPU CrashLog}
  gPlatformFspPkgTokenSpaceGuid.CpuCrashLogDevice           | * | 0x01 | 0x1

  # !BSF NAME:{Memory SPD Pointer Channel 0 Dimm 0}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Pointer to SPD data, will be used only when SpdAddressTable SPD Address are marked as 00}
  gPlatformFspPkgTokenSpaceGuid.MemorySpdPtr00              | * | 0x04 | 0x00000000

  # !BSF NAME:{Memory SPD Pointer Channel 0 Dimm 1}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Pointer to SPD data, will be used only when SpdAddressTable SPD Address are marked as 00}
  gPlatformFspPkgTokenSpaceGuid.MemorySpdPtr01              | * | 0x04 | 0x00000000

  # !BSF NAME:{Memory SPD Pointer Channel 1 Dimm 0}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Pointer to SPD data, will be used only when SpdAddressTable SPD Address are marked as 00}
  gPlatformFspPkgTokenSpaceGuid.MemorySpdPtr10              | * | 0x04 | 0x00000000

  # !BSF NAME:{Memory SPD Pointer Channel 1 Dimm 1}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Pointer to SPD data, will be used only when SpdAddressTable SPD Address are marked as 00}
  gPlatformFspPkgTokenSpaceGuid.MemorySpdPtr11              | * | 0x04 | 0x00000000

  # !BSF NAME:{Dq Byte Map CH0} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Dq byte mapping between CPU and DRAM, Channel 0: board-dependent}
  gPlatformFspPkgTokenSpaceGuid.DqByteMapCh0                | * | 0x0C | { 0x0F, 0xF0, 0x0F, 0xF0, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Dq Byte Map CH1} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Dq byte mapping between CPU and DRAM, Channel 1: board-dependent}
  gPlatformFspPkgTokenSpaceGuid.DqByteMapCh1                | * | 0x0C | { 0x0F, 0xF0, 0x0F, 0xF0, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Dqs Map CPU to DRAM CH 0} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Set Dqs mapping relationship between CPU and DRAM, Channel 0: board-dependent}
  gPlatformFspPkgTokenSpaceGuid.DqsMapCpu2DramCh0           | * | 0x08 | { 2, 0, 1, 3, 6, 4, 7, 5 }

  # !BSF NAME:{Dqs Map CPU to DRAM CH 1} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Set Dqs mapping relationship between CPU and DRAM, Channel 1: board-dependent}
  gPlatformFspPkgTokenSpaceGuid.DqsMapCpu2DramCh1           | * | 0x08 | { 1, 3, 2, 0, 5, 7, 6, 4 }

  # !BSF NAME:{RcompResister settings} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{Indicates  RcompReister settings: Board-dependent}
  gPlatformFspPkgTokenSpaceGuid.RcompResistor               | * | 0x06 | { 0x0000, 0x0000, 0x0000 }

  # !BSF NAME:{RcompTarget settings} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{RcompTarget settings: board-dependent}
  gPlatformFspPkgTokenSpaceGuid.RcompTarget                 | * | 0x0A | { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }

  # !BSF NAME:{Dqs Pins Interleaved Setting} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Indicates DqPinsInterleaved setting: board-dependent}
  gPlatformFspPkgTokenSpaceGuid.DqPinsInterleaved           | * | 0x01 | 0x0

  # !BSF NAME:{VREF_CA} TYPE:{Combo}
  # !BSF OPTION:{0:VREF_CA goes to both CH_A and CH_B, 1: VREF_CA to CH_A and VREF_DQ_A to CH_B, 2:VREF_CA to CH_A and VREF_DQ_B to CH_B}
  # !BSF HELP:{CA Vref routing: board-dependent}
  gPlatformFspPkgTokenSpaceGuid.CaVrefConfig                | * | 0x01 | 0x02

  # !BSF NAME:{Smram Mask} TYPE:{Combo}
  # !BSF OPTION:{0: Neither, 1:AB-SEG, 2:H-SEG, 3: Both}
  # !BSF HELP:{The SMM Regions AB-SEG and/or H-SEG reserved}
  gPlatformFspPkgTokenSpaceGuid.SmramMask                   | * | 0x01 | 0x0

  # !BSF NAME:{MRC Fast Boot} TYPE:{Combo}
  # !BSF OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable the MRC fast path thru the MRC}
  gPlatformFspPkgTokenSpaceGuid.MrcFastBoot                 | * | 0x01 | 0x01

  # !BSF NAME:{LPDDR4 Write DQ/DQS Retraining}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable LPDDR4 Write DQ/DQS Retraining}
  gPlatformFspPkgTokenSpaceGuid.Lp4DqsOscEn              | * | 0x01 | 0x01

  # !BSF NAME:{Ibecc} TYPE:{Combo}
  # !BSF OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Ibecc}
  gPlatformFspPkgTokenSpaceGuid.Ibecc                       | * | 0x01 | 0x0

  # !BSF NAME:{IbeccParity}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{In-Band ECC Parity Control}
  gPlatformFspPkgTokenSpaceGuid.IbeccParity              | * | 0x01 | 0x00

  # !BSF NAME:{IbeccOperationMode}
  # !BSF TYPE:{Combo} OPTION:{0:Protect base on address range, 1: Non-protected, 2: All protected}
  # !BSF HELP:{In-Band ECC Operation Mode}
  gPlatformFspPkgTokenSpaceGuid.IbeccOperationMode       | * | 0x01 | 0x01

  # !BSF NAME:{IbeccProtectedRegionEnable}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{In-Band ECC Protected Region Enable }
  gPlatformFspPkgTokenSpaceGuid.IbeccProtectedRegionEnable            | * | 0x8 | { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }

  # !BSF NAME:{IbeccProtectedRegionBases} TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{IBECC Protected Region Bases}
  gPlatformFspPkgTokenSpaceGuid.IbeccProtectedRegionBase          | * | 0x10 | { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }

  # !BSF NAME:{IbeccProtectedRegionMasks} TYPE:{EditNum, HEX, (0x00,0x3FFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{IBECC Protected Region Masks}
  gPlatformFspPkgTokenSpaceGuid.IbeccProtectedRegionMask          | * | 0x10| { 0x3FFF, 0x3FFF, 0x3FFF, 0x3FFF, 0x3FFF, 0x3FFF, 0x3FFF, 0x3FFF }

  # !BSF NAME:{Rank Margin Tool per Task}
  # !BSF TYPE:{Combo}
  # !BSF OPTION:{$EN_DIS}
  # !BSF HELP:{This option enables the user to execute Rank Margin Tool per major training step in the MRC.}
  gPlatformFspPkgTokenSpaceGuid.RmtPerTask                  | * | 0x01 | 0x0

  # !BSF NAME:{Training Trace}
  # !BSF TYPE:{Combo}
  # !BSF OPTION:{$EN_DIS}
  # !BSF HELP:{This option enables the trained state tracing feature in MRC.  This feature will print out the key training parameters state across major training steps.}
  gPlatformFspPkgTokenSpaceGuid.TrainTrace                  | * | 0x01 | 0x0

  # !BSF NAME:{Intel Enhanced Debug} TYPE:{Combo}
  # !BSF OPTION:{0 : Disable, 0x400000 : Enable}
  # !BSF HELP:{Intel Enhanced Debug (IED): 0=Disabled, 0x400000=Enabled and 4MB SMRAM occupied}
  gPlatformFspPkgTokenSpaceGuid.IedSize                     | * | 0x04 | 0x00000000

  # !BSF NAME:{Tseg Size} TYPE:{Combo}
  # !BSF OPTION:{0x0400000:4MB, 0x01000000:16MB}
  # !BSF HELP:{Size of SMRAM memory reserved. 0x400000 for Release build and 0x1000000 for Debug build}
!if $(TARGET) == DEBUG
  gPlatformFspPkgTokenSpaceGuid.TsegSize                    | * | 0x04 | 0x01000000
!else
  gPlatformFspPkgTokenSpaceGuid.TsegSize                    | * | 0x04 | 0x0400000
!endif

  # !BSF NAME:{MMIO Size} TYPE:{EditNum, HEX, (0,0xC00)}
  # !BSF HELP:{Size of MMIO space reserved for devices. 0(Default)=Auto, non-Zero=size in MB}
  gPlatformFspPkgTokenSpaceGuid.MmioSize                    | * | 0x02 | 0x0

  # !BSF NAME:{LowSupplyEnData} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable: Enable Low Supply for LPDDR4 Data, Disable(Default)}
  gPlatformFspPkgTokenSpaceGuid.LowSupplyEnData            | * | 0x01 | 0x00

  # !BSF NAME:{LowSupplyEnCcc} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable: Enable Low Supply for LPDDR4 Clock/Command/Control, Disable(Default)}
  gPlatformFspPkgTokenSpaceGuid.LowSupplyEnCcc             | * | 0x01 | 0x00

  # !BSF NAME:{Memory Test on Warm Boot}
  # !BSF TYPE:{Combo} OPTION:{0:Disable, 1:Enable}
  # !BSF HELP:{Run Base Memory Test on Warm Boot}
  gPlatformFspPkgTokenSpaceGuid.MemTestOnWarmBoot         | * | 0x01 | 0x01

  # !BSF NAME:{Probeless Trace}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Probeless Trace: 0=Disabled, 1=Enable. Enabling Probeless Trace will reserve 128MB. This also requires IED to be enabled.}
  gPlatformFspPkgTokenSpaceGuid.ProbelessTrace              | * | 0x01 | 0x00

  # PCH configuration
  # !BSF PAGE:{PCH1}
  # !BSF NAME:{Enable SMBus} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable SMBus controller.}
  gPlatformFspPkgTokenSpaceGuid.SmbusEnable                  | * | 0x01 | 0x01

  # !BSF PAGE:{SA1}
  # !BSF NAME:{Spd Address Tabl} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{Specify SPD Address table for CH0D0/CH0D1/CH1D0&CH1D1. MemorySpdPtr will be used if SPD Address is 00}
  gPlatformFspPkgTokenSpaceGuid.SpdAddressTable              | * | 0x04 | { 0xA0, 0xA2, 0xA4, 0xA6 }

  # !BSF NAME:{Platform Debug Consent} TYPE:{Combo} OPTION:{0:Disabled, 1:Enabled (DCI OOB+[DbC]), 2:Enabled (DCI OOB), 3:Enabled (USB3 DbC), 4:Enabled (XDP/MIPI60), 5:Enabled (USB2 DbC), 6:Enable (2-wire DCI OOB), 7:Manual}
  # !BSF HELP:{To 'opt-in' for debug, please select 'Enabled' with the desired debug probe type. Enabling this BIOS option may alter the default value of other debug-related BIOS options.\Manual: Do not use Platform Debug Consent to override other debug-relevant policies, but the user must set each debug option manually, aimed at advanced users.\nNote: DCI OOB (aka BSSB) uses CCA probe;[DCI OOB+DbC] and [USB2 DbC] have the same setting.}
  gPlatformFspPkgTokenSpaceGuid.PlatformDebugConsent         | * | 0x01 | 0x00

  # !BSF NAME:{DCI Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Determine if to enable DCI debug from host}
  gPlatformFspPkgTokenSpaceGuid.DciEn                        | * | 0x01 | 0x00

  # !BSF NAME:{DCI DbC Mode} TYPE:{Combo} OPTION:{0:Disabled, 1:USB2 DbC, 2:USB3 DbC, 3:Both, 4:No Change}
  # !BSF HELP:{Disabled: Clear both USB2/3DBCEN; USB2: set USB2DBCEN; USB3: set USB3DBCEN; Both: Set both USB2/3DBCEN; No Change: Comply with HW value}
  gPlatformFspPkgTokenSpaceGuid.DciDbcMode                   | * | 0x01 | 0x04

  # !BSF NAME:{Enable DCI ModPHY Pwoer Gate} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable ModPHY Pwoer Gate when DCI is enabled}
  gPlatformFspPkgTokenSpaceGuid.DciModphyPg                  | * | 0x01 | 0x00

  # !BSF NAME:{USB3 Type-C UFP2DFP Kernel/Platform Debug Support} TYPE:{Combo} OPTION:{0:Disabled, 1:Enabled, 2:No Change}
  # !BSF HELP:{This BIOS option enables kernel and platform debug for USB3 interface over a UFP Type-C receptacle, select 'No Change' will do nothing to UFP2DFP setting.}
  gPlatformFspPkgTokenSpaceGuid.DciUsb3TypecUfpDbg           | * | 0x01 | 0x02

  # !BSF NAME:{PCH Trace Hub Mode} TYPE:{Combo} OPTION:{0: Disable, 1: Target Debugger Mode, 2: Host Debugger Mode}
  # !BSF HELP:{Select 'Host Debugger' if Trace Hub is used with host debugger tool or 'Target Debugger' if Trace Hub is used by target debugger software or 'Disable' trace hub functionality.}
  gPlatformFspPkgTokenSpaceGuid.PchTraceHubMode              | * | 0x01 | 0x00

  # !BSF NAME:{PCH Trace Hub Memory Region 0 buffer Size} TYPE:{Combo} OPTION:{0:0, 1:1MB, 2:8MB, 3:64MB, 4:128MB, 5:256MB, 6:512MB}
  # !BSF HELP:{Specify size of Pch trace memory region 0 buffer, the size can be 0, 1MB, 8MB, 64MB, 128MB, 256MB, 512MB. Note : Limitation of total buffer size (PCH + CPU) is 512MB.}
  gPlatformFspPkgTokenSpaceGuid.PchTraceHubMemReg0Size       | * | 0x01 | 0x03

  # !BSF NAME:{PCH Trace Hub Memory Region 1 buffer Size} TYPE:{Combo} OPTION:{0:0, 1:1MB, 2:8MB, 3:64MB, 4:128MB, 5:256MB, 6:512MB}
  # !BSF HELP:{Specify size of Pch trace memory region 1 buffer, the size can be 0, 1MB, 8MB, 64MB, 128MB, 256MB, 512MB. Note : Limitation of total buffer size (PCH + CPU) is 512MB.}
  gPlatformFspPkgTokenSpaceGuid.PchTraceHubMemReg1Size       | * | 0x01 | 0x03

  # !BSF NAME:{PchPreMemRsvd} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Reserved for PCH Pre-Mem Reserved}
  gPlatformFspPkgTokenSpaceGuid.PchPreMemRsvd                | * | 0x07 | {0x00}

  # !BSF NAME:{State of X2APIC_OPT_OUT bit in the DMAR table} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0=Disable/Clear, 1=Enable/Set}
  gPlatformFspPkgTokenSpaceGuid.X2ApicOptOut                | * | 0x1 | 0x0

  # !BSF NAME:{State of DMA_CONTROL_GUARANTEE bit in the DMAR table} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0=Disable/Clear, 1=Enable/Set}
  gPlatformFspPkgTokenSpaceGuid.DmaControlGuarantee         | * | 0x1 | 0x0

  # !BSF NAME:{Base addresses for VT-d function MMIO access} TYPE:{EditNum, HEX, (0, 0xFFFFFFFF)}
  # !HDR STRUCT:{UINT32}
  # !BSF HELP:{Base addresses for VT-d MMIO access per VT-d engine}
  gPlatformFspPkgTokenSpaceGuid.VtdBaseAddress              | * | 0x24 | {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000}

  # !BSF NAME:{Disable VT-d} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0=Enable/FALSE(VT-d enabled), 1=Disable/TRUE (VT-d disabled)}
  gPlatformFspPkgTokenSpaceGuid.VtdDisable                  | * | 0x1 | 0x1

  # !BSF NAME:{Vtd Programming for Igd} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{1=Enable/TRUE (Igd VT-d Bar programming enabled), 0=Disable/FLASE (Igd VT-d Bar programming disabled)}
  gPlatformFspPkgTokenSpaceGuid.VtdIgdEnable                  | * | 0x1 | 0x1

  # !BSF NAME:{Vtd Programming for Ipu} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{1=Enable/TRUE (Ipu VT-d Bar programming enabled), 0=Disable/FLASE (Ipu VT-d Bar programming disabled)}
  gPlatformFspPkgTokenSpaceGuid.VtdIpuEnable                  | * | 0x1 | 0x0

  # !BSF NAME:{Vtd Programming for Iop} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{1=Enable/TRUE (Iop VT-d Bar programming enabled), 0=Disable/FLASE (Iop VT-d Bar programming disabled)}
  gPlatformFspPkgTokenSpaceGuid.VtdIopEnable                  | * | 0x1 | 0x1

  # !BSF NAME:{Vtd Programming for ITbt} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{1=Enable/TRUE (ITbt VT-d Bar programming enabled), 0=Disable/FLASE (ITbt VT-d Bar programming disabled)}
  gPlatformFspPkgTokenSpaceGuid.VtdItbtEnable                  | * | 0x1 | 0x0


  # !BSF PAGE:{SA1}
  # !BSF NAME:{Internal Graphics Pre-allocated Memory} TYPE:{Combo}
  # !BSF OPTION:{0x00:0MB, 0x01:32MB, 0x02:64MB, 0x03:96MB, 0x04:128MB, 0x05:160MB, 0xF0:4MB, 0xF1:8MB, 0xF2:12MB, 0xF3:16MB, 0xF4:20MB, 0xF5:24MB, 0xF6:28MB, 0xF7:32MB, 0xF8:36MB, 0xF9:40MB, 0xFA:44MB, 0xFB:48MB, 0xFC:52MB, 0xFD:56MB, 0xFE:60MB}
  # !BSF HELP:{Size of memory preallocated for internal graphics.}
  gPlatformFspPkgTokenSpaceGuid.IgdDvmt50PreAlloc           | * | 0x01 | 0xFE

  # !BSF NAME:{Internal Graphics} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable internal graphics.}
  gPlatformFspPkgTokenSpaceGuid.InternalGfx                 | * | 0x01 | 0x01

  # !BSF NAME:{Aperture Size} TYPE:{Combo}
  # !BSF OPTION:{0:128 MB, 1:256 MB, 2:512 MB}
  # !BSF HELP:{Select the Aperture Size.}
  gPlatformFspPkgTokenSpaceGuid.ApertureSize                | * | 0x01 | 0x01

  # !BSF PAGE:{MRC1}
  # !BSF NAME:{Board Type}
  # !BSF TYPE:{Combo} OPTION:{0:Mobile/Mobile Halo, 1:Desktop/DT Halo, 5:ULT/ULX/Mobile Halo, 7:UP Server}
  # !BSF HELP:{MrcBoardType, Options are 0=Mobile/Mobile Halo, 1=Desktop/DT Halo, 5=ULT/ULX/Mobile Halo, 7=UP Server}
  gPlatformFspPkgTokenSpaceGuid.UserBd                      | * | 0x01 | 0x05

  # !BSF NAME:{DDR Frequency Limit}
  # !BSF TYPE:{Combo} OPTION:{1067:1067, 1333:1333, 1600:1600, 1867:1867, 2133:2133, 2400:2400, 2667:2667, 2933:2933, 0:Auto}
  # !BSF HELP:{Maximum Memory Frequency Selections in Mhz. Options are 1067, 1333, 1600, 1867, 2133, 2400, 2667, 2933 and 0 for Auto.}
  gPlatformFspPkgTokenSpaceGuid.DdrFreqLimit                | * | 0x02 | 0

  # !BSF NAME:{SA GV} TYPE:{Combo}
  # !BSF OPTION:{0:Disabled, 1:FixedLow, 2:FixedMid, 3:FixedHigh, 4:Enabled}
  # !BSF HELP:{System Agent dynamic frequency support and when enabled memory will be training at three different frequencies.}
  gPlatformFspPkgTokenSpaceGuid.SaGv                        | * | 0x01 | 0x04

  # !BSF NAME:{DDR Speed Control} TYPE:{Combo}
  # !BSF OPTION:{0:Auto, 1:Manual}
  # !BSF HELP:{DDR Frequency and Gear control for all SAGV points.}
  gPlatformFspPkgTokenSpaceGuid.DdrSpeedControl             | * | 0x01 | 0x00

  # !BSF NAME:{Low Frequency}
  # !BSF TYPE:{Combo} OPTION:{1067:1067, 1333:1333, 1600:1600, 1867:1867, 2133:2133, 2400:2400, 2667:2667, 2933:2933, 0:Auto}
  # !BSF HELP:{SAGV Low Frequency Selections in Mhz. Options are 1067, 1333, 1600, 1867, 2133, 2400, 2667, 2933 and 0 for Auto.}
  gPlatformFspPkgTokenSpaceGuid.FreqSaGvLow                 | * | 0x02 | 0

  # !BSF NAME:{Mid Frequency}
  # !BSF TYPE:{Combo} OPTION:{1067:1067, 1333:1333, 1600:1600, 1867:1867, 2133:2133, 2400:2400, 2667:2667, 2933:2933, 0:Auto}
  # !BSF HELP:{SAGV Mid Frequency Selections in Mhz. Options are 1067, 1333, 1600, 1867, 2133, 2400, 2667, 2933 and 0 for Auto.}
  gPlatformFspPkgTokenSpaceGuid.FreqSaGvMid                 | * | 0x02 | 0

  # !BSF NAME:{Rank Margin Tool}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable Rank Margin Tool.}
  gPlatformFspPkgTokenSpaceGuid.RMT                         | * | 0x01 | 0x00

  # !BSF NAME:{Channel A DIMM Control}
  # !BSF TYPE:{Combo} OPTION:{0:Enable both DIMMs, 1:Disable DIMM0, 2:Disable DIMM1, 3:Disable both DIMMs}
  # !BSF HELP:{Channel A DIMM Control Support - Enable or Disable Dimms on Channel A.}
  gPlatformFspPkgTokenSpaceGuid.DisableDimmChannel0         | * | 0x01 | 0x00

  # !BSF NAME:{Channel B DIMM Control}
  # !BSF TYPE:{Combo} OPTION:{0:Enable both DIMMs, 1:Disable DIMM0, 2:Disable DIMM1, 3:Disable both DIMMs}
  # !BSF HELP:{Channel B DIMM Control Support - Enable or Disable Dimms on Channel B.}
  gPlatformFspPkgTokenSpaceGuid.DisableDimmChannel1         | * | 0x01 | 0x00

  # !BSF NAME:{Scrambler Support}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{This option enables data scrambling in memory.}
  gPlatformFspPkgTokenSpaceGuid.ScramblerSupport            | * | 0x01 | 0x1

  # !BSF NAME:{Ddr4OneDpc} TYPE:{Combo}
  # !BSF OPTION:{0: Disabled, 1: Enabled on DIMM0 only, 2: Enabled on DIMM1 only, 3: Enabled}
  # !BSF HELP:{DDR4 1DPC performance feature for 2R DIMMs. Can be enabled on DIMM0 or DIMM1 only, or on both (default)}
  gPlatformFspPkgTokenSpaceGuid.Ddr4OneDpc                  | * | 0x01 | 0x03

  # !BSF NAME:{MMA Test Content Pointer}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFF)}
  # !BSF HELP:{Pointer to MMA Test Content in Memory}
  gPlatformFspPkgTokenSpaceGuid.MmaTestContentPtr           | * | 0x04 | 0x00000000

  # !BSF NAME:{MMA Test Content Size}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFF)}
  # !BSF HELP:{Size of MMA Test Content in Memory}
  gPlatformFspPkgTokenSpaceGuid.MmaTestContentSize          | * | 0x04 | 0x00000000

  # !BSF NAME:{MMA Test Config Pointer}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFF)}
  # !BSF HELP:{Pointer to MMA Test Config in Memory}
  gPlatformFspPkgTokenSpaceGuid.MmaTestConfigPtr            | * | 0x04 | 0x00000000

  # !BSF NAME:{MMA Test Config Size}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFF)}
  # !BSF HELP:{Size of MMA Test Config in Memory}
  gPlatformFspPkgTokenSpaceGuid.MmaTestConfigSize           | * | 0x04 | 0x00000000

  # !BSF NAME:{SPD Profile Selected}
  # !BSF TYPE:{Combo} OPTION:{0:Default profile, 1:Custom profile, 2:XMP profile 1, 3:XMP profile 2}
  # !BSF HELP:{Select DIMM timing profile. Options are 0=Default profile, 1=Custom profile, 2=XMP Profile 1, 3=XMP Profile 2}
  gPlatformFspPkgTokenSpaceGuid.SpdProfileSelected          | * | 0x01 | 0x00

  # !BSF NAME:{Memory Reference Clock}
  # !BSF TYPE:{Combo} OPTION:{0:133MHz, 1:100MHz}
  # !BSF HELP:{100MHz, 133MHz.}
  gPlatformFspPkgTokenSpaceGuid.RefClk                      | * | 0x01 | 0x00

  # !BSF NAME:{Memory Voltage}
  # !BSF TYPE:{Combo} OPTION:{0:Default, 1200:1.20 Volts, 1250:1.25 Volts, 1300:1.30 Volts, 1350:1.35 Volts, 1400:1.40 Volts, 1450:1.45 Volts, 1500:1.50 Volts, 1550:1.55 Volts, 1600:1.60 Volts, 1650:1.65 Volts}
  # !BSF HELP:{Memory Voltage Override (Vddq). Default = no override}
  gPlatformFspPkgTokenSpaceGuid.VddVoltage                  | * | 0x02 | 0x0000

  # !BSF NAME:{Memory Ratio}
  # !BSF TYPE:{Combo} OPTION:{0:Auto, 4:4, 5:5, 6:6, 7:7, 8:8, 9:9, 10:10, 11:11, 12:12, 13:13, 14:14, 15:15}
  # !BSF HELP:{Automatic or the frequency will equal ratio times reference clock. Set to Auto to recalculate memory timings listed below.}
  gPlatformFspPkgTokenSpaceGuid.Ratio                       | * | 0x01 | 0x00

  # !BSF NAME:{QCLK Odd Ratio}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Adds 133 or 100 MHz to QCLK frequency, depending on RefClk}
  gPlatformFspPkgTokenSpaceGuid.OddRatioMode                | * | 0x01 | 0x00

  # !BSF NAME:{tCL}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x1F)}
  # !BSF HELP:{CAS Latency, 0: AUTO, max: 31}
  gPlatformFspPkgTokenSpaceGuid.tCL                         | * | 0x01 | 0x00

  # !BSF NAME:{tCWL}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x22)}
  # !BSF HELP:{Min CAS Write Latency Delay Time, 0: AUTO, max: 34}
  gPlatformFspPkgTokenSpaceGuid.tCWL                        | * | 0x01 | 0x00

  # !BSF NAME:{tFAW}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x3F)}
  # !BSF HELP:{Min Four Activate Window Delay Time, 0: AUTO, max: 63}
  gPlatformFspPkgTokenSpaceGuid.tFAW                        | * | 0x02 | 0x0000

  # !BSF NAME:{tRAS}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x40)}
  # !BSF HELP:{RAS Active Time, 0: AUTO, max: 64}
  gPlatformFspPkgTokenSpaceGuid.tRAS                        | * | 0x02 | 0x0000

  # !BSF NAME:{tRCD/tRP}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x3F)}
  # !BSF HELP:{RAS to CAS delay time and Row Precharge delay time, 0: AUTO, max: 63}
  gPlatformFspPkgTokenSpaceGuid.tRCDtRP                     | * | 0x01 | 0x00

  # !BSF NAME:{SA GV Low Gear} TYPE:{Combo}
  # !BSF OPTION:{0:Gear1, 1:Gear2}
  # !BSF HELP:{Gear Selection for SAGV Low point}
  gPlatformFspPkgTokenSpaceGuid.SaGvLowGear2                | * | 0x01 | 0x00

  # !BSF NAME:{tREFI}
  # !BSF TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{Refresh Interval, 0: AUTO, max: 65535}
  gPlatformFspPkgTokenSpaceGuid.tREFI                       | * | 0x02 | 0x0000

  # !BSF NAME:{tRFC}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x3FF)}
  # !BSF HELP:{Min Refresh Recovery Delay Time, 0: AUTO, max: 1023}
  gPlatformFspPkgTokenSpaceGuid.tRFC                        | * | 0x02 | 0x0000

  # !BSF NAME:{tRRD}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x0F)}
  # !BSF HELP:{Min Row Active to Row Active Delay Time, 0: AUTO, max: 15}
  gPlatformFspPkgTokenSpaceGuid.tRRD                        | * | 0x01 | 0x00

  # !BSF NAME:{tRTP}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x0F)}
  # !BSF HELP:{Min Internal Read to Precharge Command Delay Time, 0: AUTO, max: 15. DDR4 legal values: 5, 6, 7, 8, 9, 10, 12}
  gPlatformFspPkgTokenSpaceGuid.tRTP                        | * | 0x01 | 0x00

  # !BSF NAME:{tWR}
  # !BSF TYPE:{Combo} OPTION:{0:Auto, 5:5, 6:6, 7:7, 8:8, 10:10, 12:12, 14:14, 16:16, 18:18, 20:20, 24:24, 30:30, 34:34, 40:40}
  # !BSF HELP:{Min Write Recovery Time, 0: AUTO, legal values: 5, 6, 7, 8, 10, 12, 14, 16, 18, 20, 24, 30, 34, 40}
  gPlatformFspPkgTokenSpaceGuid.tWR                         | * | 0x01 | 0x00

  # !BSF NAME:{tWTR}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x1C)}
  # !BSF HELP:{Min Internal Write to Read Command Delay Time, 0: AUTO, max: 28}
  gPlatformFspPkgTokenSpaceGuid.tWTR                        | * | 0x01 | 0x00

  # !BSF NAME:{NMode}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x02)}
  # !BSF HELP:{System command rate, range 0-2, 0 means auto, 1 = 1N, 2 = 2N}
  gPlatformFspPkgTokenSpaceGuid.NModeSupport                | * | 0x01 | 0x00

  # !BSF NAME:{DllBwEn[0]}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x07)}
  # !BSF HELP:{DllBwEn[0], for 1067 (0..7)}
  gPlatformFspPkgTokenSpaceGuid.DllBwEn0                    | * | 0x01 | 0x00

  # !BSF NAME:{DllBwEn[1]}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x07)}
  # !BSF HELP:{DllBwEn[1], for 1333 (0..7)}
  gPlatformFspPkgTokenSpaceGuid.DllBwEn1                    | * | 0x01 | 0x01

  # !BSF NAME:{DllBwEn[2]}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x07)}
  # !BSF HELP:{DllBwEn[2], for 1600 (0..7)}
  gPlatformFspPkgTokenSpaceGuid.DllBwEn2                    | * | 0x01 | 0x02

  # !BSF NAME:{DllBwEn[3]}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x07)}
  # !BSF HELP:{DllBwEn[3], for 1867 and up (0..7)}
  gPlatformFspPkgTokenSpaceGuid.DllBwEn3                    | * | 0x01 | 0x02

  # !BSF NAME:{ISVT IO Port Address} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{ISVT IO Port Address. 0=Minimal, 0xFF=Maximum, 0x99=Default}
  gPlatformFspPkgTokenSpaceGuid.IsvtIoPort                  | * | 0x01 | 0x99

  # !BSF PAGE:{PCH1}
  # !BSF NAME:{Enable Intel HD Audio (Azalia)} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Disable, 1: Enable (Default) Azalia controller}
  gPlatformFspPkgTokenSpaceGuid.PchHdaEnable                | * | 0x01 | 0x01

  # !BSF NAME:{Enable PSE Controller} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Disable; 1: Enable (Default) PSE controller}
  gPlatformFspPkgTokenSpaceGuid.PchPseEnable                | * | 0x01 | 0x01

  # !BSF PAGE:{SA1}
  # !BSF NAME:{CPU Trace Hub Mode} TYPE:{Combo}
  # !BSF OPTION:{0: Disable, 1:Target Debugger Mode, 2:Host Debugger Mode}
  # !BSF HELP:{Select 'Host Debugger' if Trace Hub is used with host debugger tool or 'Target Debugger' if Trace Hub is used by target debugger software or 'Disable' trace hub functionality.}
  gPlatformFspPkgTokenSpaceGuid.CpuTraceHubMode             | * | 0x01 | 0x00

  # !BSF NAME:{CPU Trace Hub Memory Region 0} TYPE:{Combo} OPTION:{0:0, 1:1MB, 2:8MB, 3:64MB, 4:128MB, 5:256MB, 6:512MB}
  # !BSF HELP:{CPU Trace Hub Memory Region 0, The avaliable memory size is : 0MB, 1MB, 8MB, 64MB, 128MB, 256MB, 512MB. Note : Limitation of total buffer size (CPU + PCH) is 512MB.}
  gPlatformFspPkgTokenSpaceGuid.CpuTraceHubMemReg0Size      | * | 0x01 | 0x04

  # !BSF NAME:{CPU Trace Hub Memory Region 1} TYPE:{Combo} OPTION:{0:0, 1:1MB, 2:8MB, 3:64MB, 4:128MB, 5:256MB, 6:512MB}
  # !BSF HELP:{CPU Trace Hub Memory Region 1. The avaliable memory size is : 0MB, 1MB, 8MB, 64MB, 128MB, 256MB, 512MB. Note : Limitation of total buffer size (CPU + PCH) is 512MB.}
  gPlatformFspPkgTokenSpaceGuid.CpuTraceHubMemReg1Size      | * | 0x01 | 0x04

  # !BSF NAME:{SA GV Mid Gear} TYPE:{Combo}
  # !BSF OPTION:{0:Gear1, 1:Gear2}
  # !BSF HELP:{Gear Selection for SAGV Mid point}
  gPlatformFspPkgTokenSpaceGuid.SaGvMidGear2                | * | 0x01 | 0x00

  # !BSF NAME:{SA GV High Gear} TYPE:{Combo}
  # !BSF OPTION:{0:Gear1, 1:Gear2}
  # !BSF HELP:{Gear Selection for SAGV High point, or when SAGV is disabled}
  gPlatformFspPkgTokenSpaceGuid.SaGvHighGear2               | * | 0x01 | 0x00

  # ME configuration

  # !BSF NAME:{HECI Timeouts} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Disable, 1: Enable (Default) timeout check for HECI}
  gPlatformFspPkgTokenSpaceGuid.HeciTimeouts                | * | 0x01 | 0x01

  # !BSF NAME:{HECI1 BAR address}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFF)}
  # !BSF HELP:{BAR address of HECI1}
  gPlatformFspPkgTokenSpaceGuid.Heci1BarAddress             | * | 0x04 | 0xFEDA2000

  # !BSF NAME:{HECI2 BAR address}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFF)}
  # !BSF HELP:{BAR address of HECI2}
  gPlatformFspPkgTokenSpaceGuid.Heci2BarAddress             | * | 0x04 | 0xFEDA3000

  # !BSF NAME:{HECI3 BAR address}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFF)}
  # !BSF HELP:{BAR address of HECI3}
  gPlatformFspPkgTokenSpaceGuid.Heci3BarAddress             | * | 0x04 | 0xFEDA4000

  #
  # SA Pre-Mem Production Block Start
  #
  # !BSF NAME:{HG dGPU Power Delay} TYPE:{EditNum, HEX, (0x00, 0x3E8)}
  # !BSF HELP:{HG dGPU delay interval after power enabling: 0=Minimal, 1000=Maximum, default is 300=300 microseconds}
  gPlatformFspPkgTokenSpaceGuid.HgDelayAfterPwrEn           | * | 0x02 | 300

  # !BSF NAME:{HG dGPU Reset Delay} TYPE:{EditNum, HEX, (0x00, 0x3E8)}
  # !BSF HELP:{HG dGPU delay interval for Reset complete: 0=Minimal, 1000=Maximum, default is 100=100 microseconds}
  gPlatformFspPkgTokenSpaceGuid.HgDelayAfterHoldReset       | * | 0x02 | 100

  # !BSF NAME:{MMIO size adjustment for AUTO mode} TYPE:{EditNum, HEX, (0, 0xFFFF)}
  # !BSF HELP:{Positive number means increasing MMIO size, Negative value means decreasing MMIO size: 0 (Default)=no change to AUTO mode MMIO size}
  gPlatformFspPkgTokenSpaceGuid.MmioSizeAdjustment          | * | 0x02 | 0

  # !BSF NAME:{Enable/Disable DMI GEN3 Static EQ Phase1 programming} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Program DMI Gen3 EQ Phase1 Static Presets. Disabled(0x0): Disable EQ Phase1 Static Presets Programming, Enabled(0x1)(Default): Enable  EQ Phase1 Static Presets Programming}
  gPlatformFspPkgTokenSpaceGuid.DmiGen3ProgramStaticEq      | * | 0x01 | 0x1

  # !BSF NAME:{PCIe ASPM programming will happen in relation to the Oprom} TYPE:{Combo}
  # !BSF OPTION:{0:Before, 1:After}
  # !BSF HELP:{Select when PCIe ASPM programming will happen in relation to the Oprom. Before(0x0)(Default): Do PCIe ASPM programming before Oprom, After(0x1): Do PCIe ASPM programming after Oprom, requires an SMI handler to save/restore ASPM settings during S3 resume}
  gPlatformFspPkgTokenSpaceGuid.InitPcieAspmAfterOprom      | * | 0x01 | 0x0

  # !BSF NAME:{DMI Gen3 Root port preset values per lane} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{Used for programming DMI Gen3 preset values per lane. Range: 0-9, 8 is default for each lane}
  gPlatformFspPkgTokenSpaceGuid.DmiGen3RootPortPreset       | * | 0x8 | {0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4}

  # !BSF NAME:{DMI Gen3 End port preset values per lane} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{Used for programming DMI Gen3 preset values per lane. Range: 0-9, 7 is default for each lane}
  gPlatformFspPkgTokenSpaceGuid.DmiGen3EndPointPreset       | * | 0x8 | {0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7}

  # !BSF NAME:{DMI Gen3 End port Hint values per lane} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{Used for programming DMI Gen3 Hint values per lane. Range: 0-6, 2 is default for each lane}
  gPlatformFspPkgTokenSpaceGuid.DmiGen3EndPointHint         | * | 0x8 | {0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2}

  # !BSF NAME:{DMI Gen3 RxCTLEp per-Bundle control} TYPE:{EditNum, HEX, (0x00, 0xFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{Range: 0-15, 0 is default for each bundle, must be specified based upon platform design}
  gPlatformFspPkgTokenSpaceGuid.DmiGen3RxCtlePeaking        | * | 0x4 | {0x0, 0x0, 0x0, 0x0}

  # !BSF NAME:{DeEmphasis control for DMI} TYPE:{Combo}
  # !BSF OPTION:{0: -6dB, 1: -3.5dB}
  # !BSF HELP:{DeEmphasis control for DMI. 0=-6dB, 1(Default)=-3.5 dB}
  gPlatformFspPkgTokenSpaceGuid.DmiDeEmphasis               | * | 0x01 | 0x1

  # !BSF NAME:{Selection of the primary display device} TYPE:{Combo}
  # !BSF OPTION:{0:iGFX, 1:PEG, 2:PCIe Graphics on PCH, 3:AUTO, 4:Hybrid Graphics}
  # !BSF HELP:{0=iGFX, 1=PEG, 2=PCIe Graphics on PCH, 3(Default)=AUTO, 4=Hybrid Graphics}
  gPlatformFspPkgTokenSpaceGuid.PrimaryDisplay              | * | 0x01 | 0x3

  # !BSF NAME:{Selection of PSMI Region size} TYPE:{Combo}
  # !BSF OPTION:{0:32MB, 1:288MB, 2:544MB, 3:800MB, 4:1024MB}
  # !BSF HELP:{0=32MB, 1=288MB, 2=544MB, 3=800MB, 4=1024MB Default is 0}
  gPlatformFspPkgTokenSpaceGuid.PsmiRegionSize              | * | 0x01 | 0x0

  # !BSF NAME:{Temporary MMIO address for GMADR} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{The reference code will use this as Temporary MMIO address space to access GMADR Registers.Platform should provide conflict free Temporary MMIO Range: GmAdr to (GmAdr + ApertureSize). Default is (PciExpressBaseAddress - ApertureSize) to (PciExpressBaseAddress - 0x1) (Where ApertureSize = 256MB)}
  gPlatformFspPkgTokenSpaceGuid.GmAdr                       | * | 0x4 | 0xB0000000

  # !BSF NAME:{Temporary MMIO address for GTTMMADR} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{The reference code will use this as Temporary MMIO address space to access GTTMMADR Registers.Platform should provide conflict free Temporary MMIO Range: GttMmAdr to (GttMmAdr + 2MB MMIO + 6MB Reserved + GttSize). Default is (GmAdr - (2MB MMIO + 6MB Reserved + GttSize)) to (GmAdr - 0x1) (Where GttSize = 8MB)}
  gPlatformFspPkgTokenSpaceGuid.GttMmAdr                    | * | 0x4 | 0xAF000000

  # !BSF NAME:{Selection of iGFX GTT Memory size} TYPE:{Combo}
  # !BSF OPTION:{1:2MB, 2:4MB, 3:8MB}
  # !BSF HELP:{1=2MB, 2=4MB, 3=8MB, Default is 3}
  gPlatformFspPkgTokenSpaceGuid.GttSize                     | * | 0x02 | 0x3

  # !BSF NAME:{Hybrid Graphics GPIO information for PEG 0} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{Hybrid Graphics GPIO information for PEG 0, for Reset, power and wake GPIOs}
  gPlatformFspPkgTokenSpaceGuid.CpuPcie0Rtd3Gpio             | * | 0x18 | {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}

  # !BSF NAME:{Enable/Disable MRC TXT dependency} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{When enabled MRC execution will wait for TXT initialization to be done first. Disabled(0x0)(Default): MRC will not wait for TXT initialization, Enabled(0x1): MRC will wait for TXT initialization}
  gPlatformFspPkgTokenSpaceGuid.TxtImplemented              | * | 0x01 | 0x1

  # !BSF NAME:{Enable/Disable SA OcSupport} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable: Enable SA OcSupport, Disable(Default): Disable SA OcSupport}
  gPlatformFspPkgTokenSpaceGuid.SaOcSupport                 | * | 0x01 | 0x0

  # !BSF NAME:{GT slice Voltage Mode} TYPE:{Combo}
  # !BSF OPTION:{0: Adaptive, 1: Override}
  # !BSF HELP:{0(Default): Adaptive, 1: Override}
  gPlatformFspPkgTokenSpaceGuid.GtVoltageMode               | * | 0x01 | 0x0

  # !BSF NAME:{Maximum GTs turbo ratio override} TYPE:{EditNum, HEX, (0x00, 0x3C)}
  # !BSF HELP:{0(Default)=Minimal/Auto, 60=Maximum}
  gPlatformFspPkgTokenSpaceGuid.GtMaxOcRatio                | * | 0x1 | 0

  # !BSF NAME:{The voltage offset applied to GT slice} TYPE:{EditNum, HEX, (0x00, 0x3E8)}
  # !BSF HELP:{0(Default)=Minimal, 1000=Maximum}
  gPlatformFspPkgTokenSpaceGuid.GtVoltageOffset             | * | 0x2 | 0

  # !BSF NAME:{The GT slice voltage override which is applied to the entire range of GT frequencies} TYPE:{EditNum, HEX, (0x00, 0x7D0)}
  # !BSF HELP:{0(Default)=Minimal, 2000=Maximum}
  gPlatformFspPkgTokenSpaceGuid.GtVoltageOverride           | * | 0x2 | 0

  # !BSF NAME:{adaptive voltage applied during turbo frequencies} TYPE:{EditNum, HEX, (0x00, 0x7D0)}
  # !BSF HELP:{0(Default)=Minimal, 2000=Maximum}
  gPlatformFspPkgTokenSpaceGuid.GtExtraTurboVoltage         | * | 0x2 | 0

  # !BSF NAME:{voltage offset applied to the SA} TYPE:{EditNum, HEX, (0x00, 0x3E8)}
  # !BSF HELP:{0(Default)=Minimal, 1000=Maximum}
  gPlatformFspPkgTokenSpaceGuid.SaVoltageOffset             | * | 0x2 | 0

  # !BSF NAME:{PCIe root port Function number for Hybrid Graphics dGPU} TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{Root port Index number to indicate which PCIe root port has dGPU}
  gPlatformFspPkgTokenSpaceGuid.RootPortIndex               | * | 0x1 | 0x0

  # !BSF NAME:{Realtime Memory Timing} TYPE:{Combo}
  # !BSF OPTION:{0: Disabled, 1: Enabled}
  # !BSF HELP:{0(Default): Disabled, 1: Enabled. When enabled, it will allow the system to perform realtime memory timing changes after MRC_DONE.}
  gPlatformFspPkgTokenSpaceGuid.RealtimeMemoryTiming        | * | 0x01 | 0x0

  # !BSF NAME:{This is policy to control iTBT PCIe Multiple Segment setting.}
  # !BSF OPTION:{$EN_DIS}
  # !BSF HELP:{When Disabled all the TBT PCIe RP are located at Segment0, When Enabled all the TBT PCIe RP are located at Segment1. <b>0: Disable</b>; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PcieMultipleSegmentEnabled  | * | 0x1 | 0x0

  # !BSF NAME:{Enable/Disable SA IPU} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable(Default): Enable SA IPU, Disable: Disable SA IPU}
  gPlatformFspPkgTokenSpaceGuid.SaIpuEnable                | * | 0x01 | 0x1

  # !BSF NAME:{IPU IMR Configuration} TYPE:{Combo}
  # !BSF OPTION:{0:IPU Camera, 1:IPU Gen}
  # !BSF HELP:{0:IPU Camera, 1:IPU Gen Default is 0}
  gPlatformFspPkgTokenSpaceGuid.SaIpuImrConfiguration       | * | 0x01 | 0x0

  # !BSF NAME:{IMGU CLKOUT Configuration}
  # !BSF OPTION:{$EN_DIS}
  # !BSF HELP:{The configuration of IMGU CLKOUT, 0: Disable;<b>1: Enable</b>.}
  gPlatformFspPkgTokenSpaceGuid.ImguClkOutEn                | * | 0x05 | {0x1, 0x1, 0x1, 0x1, 0x0}

  # !BSF NAME:{IPU FUSA Configuration} TYPE:{Combo}
  # !BSF OPTION:{0:FUSA Disable, 1:FUSA Enable}
  # !BSF HELP:{0:FUSA Disable, 1:FUSA Enable Default is 0}
  gPlatformFspPkgTokenSpaceGuid.SaIpuFusaConfigEnable        | * | 0x01 | 0x0


  # !BSF NAME:{Enable PCIE RP Mask} TYPE:{EditNum, HEX, (0x00,0x00FFFFFF)}
  # !BSF HELP:{Enable/disable PCIE Root Ports. 0: disable, 1: enable. One bit for each port, bit0 for port1, bit1 for port2, and so on.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpEnableMask         | * | 0x04 | 0x00FFFFFF

  # !BSF NAME:{Assertion on Link Down GPIOs} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF OPTION:{0:Disable, 1:Enable}
  # !BSF HELP:{GPIO Assertion on Link Down. Disabled(0x0)(Default): Disable assertion on Link Down GPIOs, Enabled(0x1): Enable assertion on Link Down GPIOs}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpLinkDownGpios      | * | 0x01 | 0x0

  # !BSF NAME:{Enable ClockReq Messaging } TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF OPTION:{0:Disable, 1:Enable}
  # !BSF HELP:{ClockReq Messaging. Disabled(0x0): Disable ClockReq Messaging, Enabled(0x1)(Default): Enable ClockReq Messaging}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpClockReqMsgEnable  | * | 0x01 | 0x1

  # !BSF NAME:{PCIE RP Pcie Speed} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Determines each PCIE Port speed capability. 0: Auto; 1: Gen1; 2: Gen2; 3: Gen3; 4: Gen4 (see: CPU_PCIE_SPEED).}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpPcieSpeed             | * | 0x4 | { 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Selection of PSMI Support On/Off}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0(Default) = FALSE, 1 = TRUE. When TRUE, it will allow the PSMI Support}
  gPlatformFspPkgTokenSpaceGuid.GtPsmiSupport              | * | 0x01 | 0x0

  # !BSF NAME:{Selection of DiSM Region Size} TYPE:{Combo}
  # !BSF OPTION:{0:0GB, 1:1GB, 2:2GB, 3:3GB, 4:4GB, 5:5GB, 6:6GB, 7:7GB}
  # !BSF HELP:{DiSM Size to be allocated for 2LM Sku Default is 0}
  gPlatformFspPkgTokenSpaceGuid.DismSize                   | * | 0x01 | 0x0

  # !BSF NAME:{Pram Size} TYPE:{Combo}
  # !BSF OPTION:{0x30:Disable, 0x31:4MB, 0x32:16MB, 0x33:64MB}
  # !BSF HELP:{Persisted Ram Size. Default is Disabled}
  gPlatformFspPkgTokenSpaceGuid.PramSize                   | * | 0x01 | 0x30

  # !BSF NAME:{SaPreMemProductionRsvd} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Reserved for SA Pre-Mem Production}
  gPlatformFspPkgTokenSpaceGuid.SaPreMemProductionRsvd      | * | 0x8A | {0x00}

  #
  # SA Pre-Mem Production Block End
  #

  #
  # CPU Pre-Mem Production Block Start
  #
  # !BSF NAME:{BIST on Reset} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable BIST on Reset; <b>0: Disable</b>; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.BistOnReset                 | * | 0x01 | 0x00

  # !BSF NAME:{Skip Stop PBET Timer Enable/Disable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Skip Stop PBET Timer; <b>0: Disable</b>; 1: Enable}
  gPlatformFspPkgTokenSpaceGuid.SkipStopPbet                | * | 0x01 | 0x00

  # !BSF NAME:{Over clocking support} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Over clocking support; <b>0: Disable</b>; 1: Enable}
  gPlatformFspPkgTokenSpaceGuid.OcSupport                   | * | 0x01 | 0x00

  # !BSF NAME:{Over clocking Lock} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Over clocking Lock Enable/Disable; <b>0: Disable</b>; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.OcLock                      | * | 0x01 | 0x00

  # !BSF NAME:{Maximum Core Turbo Ratio Override}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x53)}
  # !BSF HELP:{Maximum core turbo ratio override allows to increase CPU core frequency beyond the fused max turbo ratio limit. <b>0: Hardware defaults.</b> Range: 0-85}
  gPlatformFspPkgTokenSpaceGuid.CoreMaxOcRatio              | * | 0x01 | 0x00

  # !BSF NAME:{Core voltage mode} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Core voltage mode; <b>0: Adaptive</b>; 1: Override.}
  gPlatformFspPkgTokenSpaceGuid.CoreVoltageMode             | * | 0x01 | 0x00

  # !BSF NAME:{Maximum clr turbo ratio override}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x53)}
  # !BSF HELP:{Maximum clr turbo ratio override allows to increase CPU clr frequency beyond the fused max turbo ratio limit. <b>0: Hardware defaults.</b>  Range: 0-85}
  gPlatformFspPkgTokenSpaceGuid.RingMaxOcRatio              | * | 0x01 | 0x00

  # !BSF NAME:{Hyper Threading Enable/Disable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Hyper Threading; 0: Disable; <b>1: Enable</b>}
  gPlatformFspPkgTokenSpaceGuid.HyperThreading              | * | 0x01 | 0x00

  # !BSF NAME:{Enable or Disable CPU Ratio Override} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable CPU Ratio Override; <b>0: Disable</b>; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.CpuRatioOverride            | * | 0x01 | 0x00

  # !BSF NAME:{CPU ratio value}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x3F)}
  # !BSF HELP:{CPU ratio value. Valid Range 0 to 63}
  gPlatformFspPkgTokenSpaceGuid.CpuRatio                    | * | 0x01 | 0x1C

  # !BSF NAME:{Boot frequency}
  # !BSF TYPE:{Combo} OPTION:{0:0, 1:1, 2:2}
  # !BSF HELP:{Sets the boot frequency starting from reset vector.- 0: Maximum battery performance.- <b>1: Maximum non-turbo performance</b>.- 2: Turbo performance. @note If Turbo is selected BIOS will start in max non-turbo mode and switch to Turbo mode.}
  gPlatformFspPkgTokenSpaceGuid.BootFrequency               | * | 0x01 | 0x01

  # !BSF NAME:{Number of active cores}
  # !BSF TYPE:{Combo} OPTION:{0:All, 1:1, 2:2, 3:3}
  # !BSF HELP:{Number of active cores(Depends on Number of cores). <b>0: All</b>;<b>1: 1 </b>;<b>2: 2 </b>;<b>3: 3 </b>}
  gPlatformFspPkgTokenSpaceGuid.ActiveCoreCount             | * | 0x01 | 0x00

  # !BSF NAME:{Processor Early Power On Configuration FCLK setting}
  # !BSF TYPE:{Combo} OPTION:{0:800 MHz, 1: 1 GHz, 2: 400 MHz, 3: Reserved }
  # !BSF HELP:{ <b>0: 800 MHz (ULT/ULX)</b>. <b>1: 1 GHz (DT/Halo)</b>. Not supported on ULT/ULX.- 2: 400 MHz. - 3: Reserved}
  gPlatformFspPkgTokenSpaceGuid.FClkFrequency               | * | 0x01 | 0x00

  # !BSF NAME:{Set JTAG power in C10 and deeper power states} TYPE:{Combo} OPTION:{0: False, 1: True}
  # !BSF HELP:{False: JTAG is power gated in C10 state. True: keeps the JTAG power up during C10 and deeper power states for debug purpose. <b>0: False</b>; 1: True.}
  gPlatformFspPkgTokenSpaceGuid.JtagC10PowerGateDisable     | * | 0x01 | 0x00

  # !BSF NAME:{Enable or Disable VMX} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable VMX; 0: Disable; <b>1: Enable</b>.}
  gPlatformFspPkgTokenSpaceGuid.VmxEnable                   | * | 0x01 | 0x01

  # !BSF NAME:{AVX2 Ratio Offset} TYPE:{EditNum, HEX, (0x00, 0x1F)}
  # !BSF HELP:{0(Default)= No Offset. Range 0 - 31. Specifies number of bins to decrease AVX ratio vs. Core Ratio. Uses Mailbox MSR 0x150, cmd 0x1B.}
  gPlatformFspPkgTokenSpaceGuid.Avx2RatioOffset             | * | 0x1 | 0

  # !BSF NAME:{AVX3 Ratio Offset} TYPE:{EditNum, HEX, (0x00, 0x1F)}
  # !BSF HELP:{0(Default)= No Offset. Range 0 - 31. Specifies number of bins to decrease AVX ratio vs. Core Ratio. Uses Mailbox MSR 0x150, cmd 0x1B.}
  gPlatformFspPkgTokenSpaceGuid.Avx3RatioOffset             | * | 0x1 | 0

  # !BSF NAME:{BCLK Adaptive Voltage Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{When enabled, the CPU V/F curves are aware of BCLK frequency when calculated. </b>0: Disable;<b> 1: Enable}
  gPlatformFspPkgTokenSpaceGuid.BclkAdaptiveVoltage     | * | 0x01 | 0x00

  # !BSF NAME:{core voltage override}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x7D0)}
  # !BSF HELP:{The core voltage override which is applied to the entire range of cpu core frequencies. Valid Range 0 to 2000}
  gPlatformFspPkgTokenSpaceGuid.CoreVoltageOverride         | * | 0x02 | 0x00

  # !BSF NAME:{Core Turbo voltage Adaptive}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x7D0)}
  # !BSF HELP:{Extra Turbo voltage applied to the cpu core when the cpu is operating in turbo mode. Valid Range 0 to 2000}
  gPlatformFspPkgTokenSpaceGuid.CoreVoltageAdaptive         | * | 0x02 | 0x00

  # !BSF NAME:{Core Turbo voltage Offset}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x3E8)}
  # !BSF HELP:{The voltage offset applied to the core while operating in turbo mode.Valid Range 0 to 1000}
  gPlatformFspPkgTokenSpaceGuid.CoreVoltageOffset           | * | 0x02 | 0x00

  # !BSF NAME:{Core PLL voltage offset}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x3F)}
  # !BSF HELP:{Core PLL voltage offset. <b>0: No offset</b>. Range 0-63}
  gPlatformFspPkgTokenSpaceGuid.CorePllVoltageOffset        | * | 0x01 | 0x00

  # !BSF NAME:{Ring Downbin} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Ring Downbin enable/disable. When enabled, CPU will ensure the ring ratio is always lower than the core ratio.0: Disable; <b>1: Enable.</b>}
  gPlatformFspPkgTokenSpaceGuid.RingDownBin                 | * | 0x01 | 0x01

  # !BSF NAME:{Ring voltage mode} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Ring voltage mode; <b>0: Adaptive</b>; 1: Override.}
  gPlatformFspPkgTokenSpaceGuid.RingVoltageMode             | * | 0x01 | 0x00

  # !BSF NAME:{TjMax Offset}
  # !BSF TYPE:{EditNum, HEX, (0x0A,0x3F)}
  # !BSF HELP:{TjMax offset.Specified value here is clipped by pCode (125 - TjMax Offset) to support TjMax in the range of 62 to 115 deg Celsius. Valid Range 10 - 63}
  gPlatformFspPkgTokenSpaceGuid.TjMaxOffset                 | * | 0x01 | 0x00

  # !BSF NAME:{Ring voltage override}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x7D0)}
  # !BSF HELP:{The ring voltage override which is applied to the entire range of cpu ring frequencies. Valid Range 0 to 2000}
  gPlatformFspPkgTokenSpaceGuid.RingVoltageOverride         | * | 0x02 | 0x00

  # !BSF NAME:{Ring Turbo voltage Adaptive}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x7D0)}
  # !BSF HELP:{Extra Turbo voltage applied to the cpu ring when the cpu is operating in turbo mode. Valid Range 0 to 2000}
  gPlatformFspPkgTokenSpaceGuid.RingVoltageAdaptive         | * | 0x02 | 0x00

  # !BSF NAME:{Ring Turbo voltage Offset}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x3E8)}
  # !BSF HELP:{The voltage offset applied to the ring while operating in turbo mode. Valid Range 0 to 1000}
  gPlatformFspPkgTokenSpaceGuid.RingVoltageOffset           | * | 0x02 | 0x00


  # !BSF NAME:{ElixirSpringsPatchAddr}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Address of Elixir Springs Patches}
  gPlatformFspPkgTokenSpaceGuid.ElixirSpringsPatchAddr     | * | 0x04  | 0x00

  # !BSF NAME:{ElixirSpringsPatchSize}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Size of Elixir Springs Patches}
  gPlatformFspPkgTokenSpaceGuid.ElixirSpringsPatchSize     | * | 0x04  | 0x00

  # !BSF NAME:{CPU Run Control} TYPE:{Combo} OPTION:{0:Disabled, 1:Enabled, 2:No Change}
  # !BSF HELP:{Enable, Disable or Do not configure CPU Run Control; 0: Disable; 1: Enable ; <b>2: No Change</b>}
  gPlatformFspPkgTokenSpaceGuid.DebugInterfaceEnable        | * | 0x01 | 0x02

  # !BSF NAME:{CPU Run Control Lock} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Lock or Unlock CPU Run Control; 0: Disable; <b>1: Enable</b>.}
  gPlatformFspPkgTokenSpaceGuid.DebugInterfaceLockEnable    | * | 0x01 | 0x01

  #
  # CPU Pre-Mem Production Block End
  #

  #
  #  Security Pre-Mem start
  #

  # !BSF NAME:{BiosGuard} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable. 0: Disable, Enable/Disable BIOS Guard feature, 1: enable}
  gPlatformFspPkgTokenSpaceGuid.BiosGuard                   | * | 0x01 | 0x00

  # !BSF NAME :{BiosGuardToolsInterface} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable. 0: Disable, Enable/Disable BiosGuardToolsInterface feature, 1: enable}
  gPlatformFspPkgTokenSpaceGuid.BiosGuardToolsInterface     | * | 0x01 | 0x00

  # !BSF NAME:{EnableSgx}
  # !BSF TYPE:{Combo} OPTION:{0: Disable, 1: Enable, 2: Software Control}
  # !BSF HELP:{Enable/Disable. 0: Disable, Enable/Disable SGX feature, 1: enable, 2: Software Control}
  gPlatformFspPkgTokenSpaceGuid.EnableSgx                   | * | 0x01 | 0x02

  # !BSF NAME:{Txt} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable. 0: Disable, Enable/Disable Txt feature, 1: enable}
  gPlatformFspPkgTokenSpaceGuid.Txt                         | * | 0x01 | 0x00

  # !BSF NAME:{PrmrrSize}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Enable/Disable. 0: Disable, define default value of PrmrrSize , 1: enable}
  # TODO: change the value according to EnableSgx token
  # Supported values: 32MB: 0x2000000, 64MB: 0x4000000, 128 MB: 0x8000000, 256 MB: 0x10000000, 512 MB: 0x20000000
  gPlatformFspPkgTokenSpaceGuid.PrmrrSize                   | * | 0x04 | 0x00000000

  # !BSF NAME:{SinitMemorySize}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Enable/Disable. 0: Disable, define default value of SinitMemorySize , 1: enable}
  # TODO: Check if default 0 is ok
  gPlatformFspPkgTokenSpaceGuid.SinitMemorySize             | * | 0x04 | 0x00000000

  # !BSF NAME:{TxtDprMemoryBase}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable/Disable. 0: Disable, define default value of TxtDprMemoryBase , 1: enable}
  # TODO: Check if default 0 is ok
  gPlatformFspPkgTokenSpaceGuid.TxtDprMemoryBase            | * | 0x08 | 0x0000000000000000

  # !BSF NAME:{TxtHeapMemorySize}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Enable/Disable. 0: Disable, define default value of TxtHeapMemorySize , 1: enable}
  # TODO: Check if default 0 is ok
  gPlatformFspPkgTokenSpaceGuid.TxtHeapMemorySize           | * | 0x04 | 0x00000000

  # !BSF NAME:{TxtDprMemorySize}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Enable/Disable. 0: Disable, define default value of TxtDprMemorySize , 1: enable}
  # TODO: Check if default 0 is ok
  gPlatformFspPkgTokenSpaceGuid.TxtDprMemorySize            | * | 0x04 | 0x00000000

  # !BSF NAME:{BiosAcmBase}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable/Disable. 0: Disable, define default value of BiosAcmBase , 1: enable}
  #TODO: This value is obtained from flash using GUID - so keeping the default value as 0
  gPlatformFspPkgTokenSpaceGuid.BiosAcmBase                 | * | 0x04 | 0x00000000

  # !BSF NAME:{BiosAcmSize}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Enable/Disable. 0: Disable, define default value of BiosAcmSize , 1: enable}
  gPlatformFspPkgTokenSpaceGuid.BiosAcmSize                 | * | 0x04 | 0x00000000

  # !BSF NAME:{ApStartupBase}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Enable/Disable. 0: Disable, define default value of BiosAcmBase , 1: enable}
  #TODO: This value is obtained from flash using GUID - so keeping the default value as 0
  gPlatformFspPkgTokenSpaceGuid.ApStartupBase               | * | 0x04 | 0x00000000

  # !BSF NAME:{TgaSize}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Enable/Disable. 0: Disable, define default value of TgaSize , 1: enable}
  #TODO: Check if default 0 is ok
  gPlatformFspPkgTokenSpaceGuid.TgaSize                     | * | 0x04 | 0x00000000

  # !BSF NAME:{TxtLcpPdBase}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable/Disable. 0: Disable, define default value of TxtLcpPdBase , 1: enable}
  #TODO: Check if default 0 is ok
  gPlatformFspPkgTokenSpaceGuid.TxtLcpPdBase                | * | 0x08 | 0x0000000000000000

  # !BSF NAME:{TxtLcpPdSize}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable/Disable. 0: Disable, define default value of TxtLcpPdSize , 1: enable}
  #TODO: Check if default 0 is ok
  gPlatformFspPkgTokenSpaceGuid.TxtLcpPdSize                | * | 0x08 | 0x0000000000000000

  # !BSF NAME:{IsTPMPresence} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{IsTPMPresence default values}
  gPlatformFspPkgTokenSpaceGuid.IsTPMPresence               | * | 0x1 | 0x0

  # !BSF NAME:{ReservedSecurityPreMem} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Reserved for Security Pre-Mem}
  gPlatformFspPkgTokenSpaceGuid.ReservedSecurityPreMem      | * | 0x06 | {0x00}

  #
  #  Security Pre-Mem End
  #

  #
  #  PCH Pre-Mem start
  #

  # !BSF NAME:{PCH Master Clock Gating Control} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Provide a master control for clock gating for all PCH devices, 0: Disabled; 1: Default}
  gPlatformFspPkgTokenSpaceGuid.PchMasterClockGating        | * | 0x01 | 0x00

  # !BSF NAME:{PCH Master Power Gating Control} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Provide a master control for pwoer gating for all PCH devices, 0: Disabled; 1: Default}
  gPlatformFspPkgTokenSpaceGuid.PchMasterPowerGating        | * | 0x01 | 0x00

  # !BSF NAME:{Enable PCH HSIO PCIE Rx Set Ctle} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable PCH PCIe Gen 3 Set CTLE Value.}
  gPlatformFspPkgTokenSpaceGuid.PchPcieHsioRxSetCtleEnable          | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO PCIE Rx Set Ctle Value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH PCIe Gen 3 Set CTLE Value.}
  gPlatformFspPkgTokenSpaceGuid.PchPcieHsioRxSetCtle                | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enble PCH HSIO PCIE TX Gen 1 Downscale Amplitude Adjustment value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchPcieHsioTxGen1DownscaleAmpEnable | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO PCIE Gen 2 TX Output Downscale Amplitude Adjustment value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH PCIe Gen 2 TX Output Downscale Amplitude Adjustment value.}
  gPlatformFspPkgTokenSpaceGuid.PchPcieHsioTxGen1DownscaleAmp       | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH HSIO PCIE TX Gen 2 Downscale Amplitude Adjustment value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchPcieHsioTxGen2DownscaleAmpEnable | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO PCIE Gen 2 TX Output Downscale Amplitude Adjustment value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH PCIe Gen 2 TX Output Downscale Amplitude Adjustment value.}
  gPlatformFspPkgTokenSpaceGuid.PchPcieHsioTxGen2DownscaleAmp       | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH HSIO PCIE TX Gen 3 Downscale Amplitude Adjustment value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchPcieHsioTxGen3DownscaleAmpEnable | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO PCIE Gen 3 TX Output Downscale Amplitude Adjustment value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH PCIe Gen 3 TX Output Downscale Amplitude Adjustment value.}
  gPlatformFspPkgTokenSpaceGuid.PchPcieHsioTxGen3DownscaleAmp       | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH HSIO PCIE Gen 1 TX Output De-Emphasis Adjustment Setting value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchPcieHsioTxGen1DeEmphEnable       | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO PCIE Gen 1 TX Output De-Emphasis Adjustment value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH PCIe Gen 1 TX Output De-Emphasis Adjustment Setting.}
  gPlatformFspPkgTokenSpaceGuid.PchPcieHsioTxGen1DeEmph             | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH HSIO PCIE Gen 2 TX Output -3.5dB De-Emphasis Adjustment Setting value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchPcieHsioTxGen2DeEmph3p5Enable    | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO PCIE Gen 2 TX Output -3.5dB De-Emphasis Adjustment value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH PCIe Gen 2 TX Output -3.5dB De-Emphasis Adjustment Setting.}
  gPlatformFspPkgTokenSpaceGuid.PchPcieHsioTxGen2DeEmph3p5          | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH HSIO PCIE Gen 2 TX Output -6.0dB De-Emphasis Adjustment Setting value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchPcieHsioTxGen2DeEmph6p0Enable    | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO PCIE Gen 2 TX Output -6.0dB De-Emphasis Adjustment value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH PCIe Gen 2 TX Output -6.0dB De-Emphasis Adjustment Setting.}
  gPlatformFspPkgTokenSpaceGuid.PchPcieHsioTxGen2DeEmph6p0          | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH HSIO SATA Receiver Equalization Boost Magnitude Adjustment Value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchSataHsioRxGen1EqBoostMagEnable   | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO SATA 1.5 Gb/s Receiver Equalization Boost Magnitude Adjustment value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH HSIO SATA 1.5 Gb/s Receiver Equalization Boost Magnitude Adjustment value.}
  gPlatformFspPkgTokenSpaceGuid.PchSataHsioRxGen1EqBoostMag         | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH HSIO SATA Receiver Equalization Boost Magnitude Adjustment Value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchSataHsioRxGen2EqBoostMagEnable   | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO SATA 3.0 Gb/s Receiver Equalization Boost Magnitude Adjustment value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH HSIO SATA 3.0 Gb/s Receiver Equalization Boost Magnitude Adjustment value.}
  gPlatformFspPkgTokenSpaceGuid.PchSataHsioRxGen2EqBoostMag         | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH HSIO SATA Receiver Equalization Boost Magnitude Adjustment Value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchSataHsioRxGen3EqBoostMagEnable   | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO SATA 6.0 Gb/s Receiver Equalization Boost Magnitude Adjustment value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH HSIO SATA 6.0 Gb/s Receiver Equalization Boost Magnitude Adjustment value.}
  gPlatformFspPkgTokenSpaceGuid.PchSataHsioRxGen3EqBoostMag         | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH HSIO SATA 1.5 Gb/s TX Output Downscale Amplitude Adjustment value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchSataHsioTxGen1DownscaleAmpEnable | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO SATA 1.5 Gb/s TX Output Downscale Amplitude Adjustment value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH HSIO SATA 1.5 Gb/s TX Output Downscale Amplitude Adjustment value.}
  gPlatformFspPkgTokenSpaceGuid.PchSataHsioTxGen1DownscaleAmp       | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH HSIO SATA 3.0 Gb/s TX Output Downscale Amplitude Adjustment value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchSataHsioTxGen2DownscaleAmpEnable | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO SATA 3.0 Gb/s TX Output Downscale Amplitude Adjustment value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH HSIO SATA 3.0 Gb/s TX Output Downscale Amplitude Adjustment value.}
  gPlatformFspPkgTokenSpaceGuid.PchSataHsioTxGen2DownscaleAmp       | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH HSIO SATA 6.0 Gb/s TX Output Downscale Amplitude Adjustment value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchSataHsioTxGen3DownscaleAmpEnable | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO SATA 6.0 Gb/s TX Output Downscale Amplitude Adjustment value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH HSIO SATA 6.0 Gb/s TX Output Downscale Amplitude Adjustment value.}
  gPlatformFspPkgTokenSpaceGuid.PchSataHsioTxGen3DownscaleAmp       | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH HSIO SATA 1.5 Gb/s TX Output De-Emphasis Adjustment Setting value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchSataHsioTxGen1DeEmphEnable       | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO SATA 1.5 Gb/s TX Output De-Emphasis Adjustment Setting} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH HSIO SATA 1.5 Gb/s TX Output De-Emphasis Adjustment Setting.}
  gPlatformFspPkgTokenSpaceGuid.PchSataHsioTxGen1DeEmph             | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH HSIO SATA 3.0 Gb/s TX Output De-Emphasis Adjustment Setting value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchSataHsioTxGen2DeEmphEnable       | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO SATA 3.0 Gb/s TX Output De-Emphasis Adjustment Setting} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH HSIO SATA 3.0 Gb/s TX Output De-Emphasis Adjustment Setting.}
  gPlatformFspPkgTokenSpaceGuid.PchSataHsioTxGen2DeEmph             | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH HSIO SATA 6.0 Gb/s TX Output De-Emphasis Adjustment Setting value override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchSataHsioTxGen3DeEmphEnable       | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH HSIO SATA 6.0 Gb/s TX Output De-Emphasis Adjustment Setting} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCH HSIO SATA 6.0 Gb/s TX Output De-Emphasis Adjustment Setting.}
  gPlatformFspPkgTokenSpaceGuid.PchSataHsioTxGen3DeEmph             | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH LPC Enhance the port 8xh decoding} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Original LPC only decodes one byte of port 80h.}
  gPlatformFspPkgTokenSpaceGuid.PchLpcEnhancePort8xhDecoding        | * | 0x01 | 0x01

  # !BSF NAME:{PCH Port80 Route} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Control where the Port 80h cycles are sent, 0: LPC; 1: PCI.}
  gPlatformFspPkgTokenSpaceGuid.PchPort80Route              | * | 0x01 | 0x00

  # !BSF NAME:{Enable SMBus ARP support} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable SMBus ARP support.}
  gPlatformFspPkgTokenSpaceGuid.SmbusArpEnable              | * | 0x01 | 0x00

  # !BSF NAME:{Number of RsvdSmbusAddressTable.} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{The number of elements in the RsvdSmbusAddressTable.}
  gPlatformFspPkgTokenSpaceGuid.PchNumRsvdSmbusAddresses    | * | 0x01 | 0x00

  # !BSF NAME:{SMBUS Base Address} TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{SMBUS Base Address (IO space).}
  gPlatformFspPkgTokenSpaceGuid.PchSmbusIoBase              | * | 0x02 | 0xEFA0

  # !BSF NAME:{Enable SMBus Alert Pin} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable SMBus Alert Pin.}
  gPlatformFspPkgTokenSpaceGuid.PchSmbAlertEnable           | * | 0x01 | 0x00

  # !BSF NAME:{Usage type for ClkSrc} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0-23: PCH rootport, 0x40-0x43: PEG port, 0x70:LAN, 0x80: unspecified but in use (free running), 0xFF: not used}
  gPlatformFspPkgTokenSpaceGuid.PcieClkSrcUsage             | * | 0x10 | { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }

  # !BSF NAME:{ClkReq-to-ClkSrc mapping} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Number of ClkReq signal assigned to ClkSrc}
  gPlatformFspPkgTokenSpaceGuid.PcieClkSrcClkReq            | * | 0x10 | { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F }

  ## only need 4 bytes to use point for this policy
  # !BSF NAME:{Point of RsvdSmbusAddressTable} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Array of addresses reserved for non-ARP-capable SMBus devices.}
  gPlatformFspPkgTokenSpaceGuid.RsvdSmbusAddressTablePtr    | * | 0x04 | 0x00000000

  # !BSF NAME:{Enable PCIE RP Mask} TYPE:{EditNum, HEX, (0x00,0x00FFFFFF)}
  # !BSF HELP:{Enable/disable PCIE Root Ports. 0: disable, 1: enable. One bit for each port, bit0 for port1, bit1 for port2, and so on.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpEnableMask            | * | 0x04 | 0x00FFFFFF

  #
  #  PCH Pre-Mem End
  #

  # !BSF PAGE:{CNP}
  # !BSF NAME:{Debug Interfaces} TYPE:{EditNum, HEX, (0x00,0x3F)}
  # !BSF HELP:{Debug Interfaces. BIT0-RAM, BIT1-UART, BIT3-USB3, BIT4-Serial IO, BIT5-TraceHub, BIT2 - Not used.}
  gPlatformFspPkgTokenSpaceGuid.PcdDebugInterfaceFlags                  | * | 0x01 | 0x32

  # !BSF NAME:{Serial Io Uart Debug Controller Number} TYPE:{Combo}
  # !BSF OPTION:{0:SerialIoUart0, 1:SerialIoUart1, 2:SerialIoUart2}
  # !BSF HELP:{Select SerialIo Uart Controller for debug. Note: If UART0 is selected as CNVi BT Core interface, it cannot be used for debug purpose.}
  gPlatformFspPkgTokenSpaceGuid.SerialIoUartDebugControllerNumber   | * | 0x01 | 0x2

  # !BSF NAME:{Serial Io Uart Debug Auto Flow} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables UART hardware flow control, CTS and RTS lines.}
  gPlatformFspPkgTokenSpaceGuid.SerialIoUartDebugAutoFlow           | * | 0x01 | 0x0

  # !BSF NAME:{Serial Io Uart Debug BaudRate} TYPE:{EditNum, DEC, (0,6000000)}
  # !BSF HELP:{Set default BaudRate Supported from 0 - default to 6000000. Recommended values 9600, 19200, 57600, 115200, 460800, 921600, 1500000, 1843200, 3000000, 3686400, 6000000}
  gPlatformFspPkgTokenSpaceGuid.SerialIoUartDebugBaudRate           | * | 0x4 | 115200

  # !BSF NAME:{Serial Io Uart Debug Parity} TYPE:{Combo}
  # !BSF OPTION:{0: DefaultParity, 1: NoParity, 2: EvenParity, 3: OddParity}
  # !BSF HELP:{Set default Parity.}
  gPlatformFspPkgTokenSpaceGuid.SerialIoUartDebugParity             | * | 0x01 | 0x1

  # !BSF NAME:{Serial Io Uart Debug Stop Bits} TYPE:{Combo}
  # !BSF OPTION:{0: DefaultStopBits, 1: OneStopBit, 2: OneFiveStopBits, 3: TwoStopBits}
  # !BSF HELP:{Set default stop bits.}
  gPlatformFspPkgTokenSpaceGuid.SerialIoUartDebugStopBits           | * | 0x01 | 0x1

  # !BSF NAME:{Serial Io Uart Debug Data Bits} TYPE:{EditNum, HEX, (0x0,0x08)}
  # !BSF OPTION:{5:5BITS, 6:6BITS, 7:7BITS, 8:8BITS}
  # !BSF HELP:{Set default word length. 0: Default, 5,6,7,8}
  gPlatformFspPkgTokenSpaceGuid.SerialIoUartDebugDataBits           | * | 0x01 | 0x8

  # !BSF NAME:{Serial Io Uart Debug Mmio Base} TYPE:{EditNum, HEX, (0,0xFFFFFFFF)}
  # !BSF HELP:{Select SerialIo Uart default MMIO resource in SEC/PEI phase when PcdSerialIoUartMode = SerialIoUartPci.}
  gPlatformFspPkgTokenSpaceGuid.SerialIoUartDebugMmioBase           | * | 0x04 | 0xFE042000

  # Pch Serial IO Uart Debug Configuration End

  # !BSF NAME:{ISA Serial Base selection} TYPE:{Combo}
  # !BSF OPTION:{0:0x3F8, 1:0x2F8}
  # !BSF HELP:{Select ISA Serial Base address. Default is 0x3F8.}
  gPlatformFspPkgTokenSpaceGuid.PcdIsaSerialUartBase                 | * | 0x01 | 0x00

  # !BSF NAME:{GT PLL voltage offset}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x3F)}
  # !BSF HELP:{Core PLL voltage offset. <b>0: No offset</b>. Range 0-63}
  gPlatformFspPkgTokenSpaceGuid.GtPllVoltageOffset        | * | 0x01 | 0x00

  # !BSF NAME:{Ring PLL voltage offset}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x3F)}
  # !BSF HELP:{Core PLL voltage offset. <b>0: No offset</b>. Range 0-63}
  gPlatformFspPkgTokenSpaceGuid.RingPllVoltageOffset        | * | 0x01 | 0x00

  # !BSF NAME:{System Agent PLL voltage offset}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x3F)}
  # !BSF HELP:{Core PLL voltage offset. <b>0: No offset</b>. Range 0-63}
  gPlatformFspPkgTokenSpaceGuid.SaPllVoltageOffset        | * | 0x01 | 0x00

  # !BSF NAME:{Memory Controller PLL voltage offset}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x3F)}
  # !BSF HELP:{Core PLL voltage offset. <b>0: No offset</b>. Range 0-63}
  gPlatformFspPkgTokenSpaceGuid.McPllVoltageOffset        | * | 0x01 | 0x00

  # !BSF NAME:{MRC Safe Config}
  # !BSF OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable MRC Safe Config}
  gPlatformFspPkgTokenSpaceGuid.MrcSafeConfig             | * | 0x01 | 0x00

  # !BSF NAME:{TCSS Thunderbolt PCIE Root Port 0 Enable}
  # !BSF OPTION:{$EN_DIS}
  # !BSF HELP:{Set TCSS Thunderbolt PCIE Root Port 0. 0:Disabled  1:Enabled}
  gPlatformFspPkgTokenSpaceGuid.TcssItbtPcie0En           | * | 0x01 | 0x01

  # !BSF NAME:{TCSS Thunderbolt PCIE Root Port 1 Enable}}
  # !BSF OPTION:{$EN_DIS}
  # !BSF HELP:{Set TCSS Thunderbolt PCIE Root Port 1. 0:Disabled  1:Enabled}
  gPlatformFspPkgTokenSpaceGuid.TcssItbtPcie1En           | * | 0x01 | 0x01

  # !BSF NAME:{TCSS Thunderbolt PCIE Root Port 2 Enable}}
  # !BSF OPTION:{$EN_DIS}
  # !BSF HELP:{Set TCSS Thunderbolt PCIE Root Port 2. 0:Disabled  1:Enabled}
  gPlatformFspPkgTokenSpaceGuid.TcssItbtPcie2En           | * | 0x01 | 0x01

  # !BSF NAME:{TCSS Thunderbolt PCIE Root Port 3 Enable}}
  # !BSF OPTION:{$EN_DIS}
  # !BSF HELP:{Set TCSS Thunderbolt PCIE Root Port 3. 0:Disabled  1:Enabled}
  gPlatformFspPkgTokenSpaceGuid.TcssItbtPcie3En           | * | 0x01 | 0x01

  # !BSF NAME:{TCSS USB HOST (xHCI) Enable}}
  # !BSF OPTION:{$EN_DIS}
  # !BSF HELP:{Set TCSS XHCI. 0:Disabled  1:Enabled - Must be enabled if xDCI is enabled below}
  gPlatformFspPkgTokenSpaceGuid.TcssXhciEn                | * | 0x01 | 0x01

  # !BSF NAME:{TCSS USB DEVICE (xDCI) Enable}}
  # !BSF OPTION:{$EN_DIS}
  # !BSF HELP:{Set TCSS XDCI. 0:Disabled  1:Enabled - xHCI must be enabled if xDCI is enabled}
  gPlatformFspPkgTokenSpaceGuid.TcssXdciEn                | * | 0x01 | 0x00

  # !BSF NAME:{TCSS DMA0 Enable}}
  # !BSF OPTION:{$EN_DIS}
  # !BSF HELP:{Set TCSS DMA0. 0:Disabled  1:Enabled}
  gPlatformFspPkgTokenSpaceGuid.TcssDma0En                | * | 0x01 | 0x01

  # !BSF NAME:{TCSS DMA1 Enable}}
  # !BSF OPTION:{$EN_DIS}
  # !BSF HELP:{Set TCSS DMA1. 0:Disabled  1:Enabled}
  gPlatformFspPkgTokenSpaceGuid.TcssDma1En                | * | 0x01 | 0x01

  # !BSF NAME:{PcdSerialDebugBaudRate} TYPE:{Combo}
  # !BSF OPTION:{3:9600, 4:19200, 6:56700, 7:115200}
  # !BSF HELP:{Baud Rate for Serial Debug Messages. 3:9600, 4:19200, 6:56700, 7:115200.}
  gPlatformFspPkgTokenSpaceGuid.PcdSerialDebugBaudRate    | * | 0x01 | 0x07

  # !BSF NAME:{HobBufferSize} TYPE:{Combo}
  # !BSF OPTION:{0:Default, 1: 1 Byte, 2: 1 KB, 3: Max value}
  # !BSF HELP:{Size to set HOB Buffer. 0:Default, 1: 1 Byte, 2: 1 KB, 3: Max value(assuming 63KB total HOB size).}
  gPlatformFspPkgTokenSpaceGuid.HobBufferSize             | * | 0x01 | 0x00

  # !BSF NAME:{Early Command Training}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Early Command Training}
  gPlatformFspPkgTokenSpaceGuid.ECT                      | * | 0x01 | 0x01

  # !BSF NAME:{SenseAmp Offset Training}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable SenseAmp Offset Training}
  gPlatformFspPkgTokenSpaceGuid.SOT                      | * | 0x01 | 0x01

  # !BSF NAME:{Early ReadMPR Timing Centering 2D}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Early ReadMPR Timing Centering 2D}
  gPlatformFspPkgTokenSpaceGuid.ERDMPRTC2D               | * | 0x01 | 0x01

  # !BSF NAME:{Read MPR Training}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Read MPR Training}
  gPlatformFspPkgTokenSpaceGuid.RDMPRT                   | * | 0x01 | 0x00

  # !BSF NAME:{Receive Enable Training}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Receive Enable Training}
  gPlatformFspPkgTokenSpaceGuid.RCVET                    | * | 0x01 | 0x01

  # !BSF NAME:{Jedec Write Leveling}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Jedec Write Leveling}
  gPlatformFspPkgTokenSpaceGuid.JWRL                     | * | 0x01 | 0x01

  # !BSF NAME:{Early Write Time Centering 2D}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Early Write Time Centering 2D}
  gPlatformFspPkgTokenSpaceGuid.EWRTC2D                  | * | 0x01 | 0x01

  # !BSF NAME:{Early Read Time Centering 2D}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Early Read Time Centering 2D}
  gPlatformFspPkgTokenSpaceGuid.ERDTC2D                  | * | 0x01 | 0x01

  # !BSF NAME:{Write Timing Centering 1D}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Write Timing Centering 1D}
  gPlatformFspPkgTokenSpaceGuid.WRTC1D                   | * | 0x01 | 0x01

  # !BSF NAME:{Write Voltage Centering 1D}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Write Voltage Centering 1D}
  gPlatformFspPkgTokenSpaceGuid.WRVC1D                   | * | 0x01 | 0x01

  # !BSF NAME:{Read Timing Centering 1D}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Read Timing Centering 1D}
  gPlatformFspPkgTokenSpaceGuid.RDTC1D                   | * | 0x01 | 0x01

  # !BSF NAME:{Dimm ODT Training}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Dimm ODT Training}
  gPlatformFspPkgTokenSpaceGuid.DIMMODTT                 | * | 0x01 | 0x01

  # !BSF NAME:{DIMM RON Training}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable DIMM RON Training}
  gPlatformFspPkgTokenSpaceGuid.DIMMRONT                 | * | 0x01 | 0x01

  # !BSF NAME:{Write Drive Strength/Equalization 2D}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Write Drive Strength/Equalization 2D}
  gPlatformFspPkgTokenSpaceGuid.WRDSEQT                  | * | 0x01 | 0x01

  # !BSF NAME:{Write Slew Rate Training}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Write Slew Rate Training}
  gPlatformFspPkgTokenSpaceGuid.WRSRT                    | * | 0x01 | 0x01

  # !BSF NAME:{Read ODT Training}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Read ODT Training}
  gPlatformFspPkgTokenSpaceGuid.RDODTT                   | * | 0x01 | 0x01

  # !BSF NAME:{Read Equalization Training}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Read Equalization Training}
  gPlatformFspPkgTokenSpaceGuid.RDEQT                    | * | 0x01 | 0x01

  # !BSF NAME:{Read Amplifier Training}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Read Amplifier Training}
  gPlatformFspPkgTokenSpaceGuid.RDAPT                    | * | 0x01 | 0x01

  # !BSF NAME:{Write Timing Centering 2D}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Write Timing Centering 2D}
  gPlatformFspPkgTokenSpaceGuid.WRTC2D                   | * | 0x01 | 0x01

  # !BSF NAME:{Read Timing Centering 2D}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Read Timing Centering 2D}
  gPlatformFspPkgTokenSpaceGuid.RDTC2D                   | * | 0x01 | 0x01

  # !BSF NAME:{Write Voltage Centering 2D}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Write Voltage Centering 2D}
  gPlatformFspPkgTokenSpaceGuid.WRVC2D                   | * | 0x01 | 0x01

  # !BSF NAME:{Read Voltage Centering 2D}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Read Voltage Centering 2D}
  gPlatformFspPkgTokenSpaceGuid.RDVC2D                   | * | 0x01 | 0x01

  # !BSF NAME:{Command Voltage Centering}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Command Voltage Centering}
  gPlatformFspPkgTokenSpaceGuid.CMDVC                    | * | 0x01 | 0x01

  # !BSF NAME:{Late Command Training}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Late Command Training}
  gPlatformFspPkgTokenSpaceGuid.LCT                      | * | 0x01 | 0x01

  # !BSF NAME:{Round Trip Latency Training}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Round Trip Latency Training}
  gPlatformFspPkgTokenSpaceGuid.RTL                      | * | 0x01 | 0x01

  # !BSF NAME:{Turn Around Timing Training}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Turn Around Timing Training}
  gPlatformFspPkgTokenSpaceGuid.TAT                      | * | 0x01 | 0x00

  # !BSF NAME:{Margin Limit Check}
  # !BSF TYPE:{Combo} OPTION:{0:Disable, 1:L1, 2:L2, 3:Both}
  # !BSF HELP:{Margin Limit Check. Choose level of margin check}
  gPlatformFspPkgTokenSpaceGuid.MarginLimitCheck         | * | 0x01 | 0x00

  # !BSF NAME:{Margin Limit L2}
  # !BSF TYPE:{% of L1 Check. 1=Minimal, 300=Maximum, 200=Default}
  # !BSF HELP:{% of L1 check for margin limit check}
  gPlatformFspPkgTokenSpaceGuid.MarginLimitL2            | * | 0x02 | 200

  # !BSF NAME:{Memory Test}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Memory Test}
  gPlatformFspPkgTokenSpaceGuid.MEMTST                   | * | 0x01 | 0x00

  # !BSF NAME:{DIMM SPD Alias Test}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable DIMM SPD Alias Test}
  gPlatformFspPkgTokenSpaceGuid.ALIASCHK                 | * | 0x01 | 0x00

  # !BSF NAME:{Receive Enable Centering 1D}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Receive Enable Centering 1D}
  gPlatformFspPkgTokenSpaceGuid.RCVENC1D                 | * | 0x01 | 0x01

  # !BSF NAME:{Retrain Margin Check}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Retrain Margin Check}
  gPlatformFspPkgTokenSpaceGuid.RMC                      | * | 0x01 | 0x00

  # !BSF NAME:{Write Drive Strength Up/Dn independently}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Write Drive Strength Up/Dn independently}
  gPlatformFspPkgTokenSpaceGuid.WRDSUDT                  | * | 0x01 | 0x00


  # !BSF NAME:{Read Voltage Centering}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Read Voltage Centering}
  gPlatformFspPkgTokenSpaceGuid.RDVC1D                   | * | 0x01 | 0x01

  # !BSF NAME:{Write TCO Comp Training}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Write TCO Comp Training}
  gPlatformFspPkgTokenSpaceGuid.TXTCO                    | * | 0x01 | 0x00

  # !BSF NAME:{Clock TCO Comp Training}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Clock TCO Comp Training}
  gPlatformFspPkgTokenSpaceGuid.CLKTCO                   | * | 0x01 | 0x00

  # !BSF NAME:{Dimm ODT CA Training}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Dimm ODT CA Training}
  gPlatformFspPkgTokenSpaceGuid.DIMMODTCA                | * | 0x01 | 0x01

  # !BSF NAME:{Write TCO Dqs Training}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Write TCO Dqs Training}
  gPlatformFspPkgTokenSpaceGuid.TXTCODQS                 | * | 0x01 | 0x00

  # !BSF NAME:{Duty Cycle Correction}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Duty Cycle Correction}
  gPlatformFspPkgTokenSpaceGuid.DCC                      | * | 0x01 | 0x01

  # !BSF NAME:{DQ DFE Training}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable DQ DFE Training}
  gPlatformFspPkgTokenSpaceGuid.DQDFE                    | * | 0x01 | 0x00

  # !BSF NAME:{Sense Amplifier Correction Training}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable Sense Amplifier Correction Training}
  gPlatformFspPkgTokenSpaceGuid.SOTC                     | * | 0x01 | 0x00

  # !BSF NAME:{ECC Support}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable ECC Support}
  gPlatformFspPkgTokenSpaceGuid.EccSupport               | * | 0x01 | 0x01

  # !BSF NAME:{Memory Remap}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Memory Remap}
  gPlatformFspPkgTokenSpaceGuid.RemapEnable              | * | 0x01 | 0x01

  # !BSF NAME:{MRC Time Measure}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable MRC Time Measure}
  gPlatformFspPkgTokenSpaceGuid.MrcTimeMeasure           | * | 0x01 | 0x00

  # !BSF NAME:{MRC Force Training on Warm}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable the MRC training on warm boot}
  gPlatformFspPkgTokenSpaceGuid.MrcTrainOnWarm           | * | 0x01 | 0x00

  # !BSF NAME:{Rank Interleave support}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Rank Interleave support. NOTE: RI and HORI can not be enabled at the same time.}
  gPlatformFspPkgTokenSpaceGuid.RankInterleave           | * | 0x01 | 0x01

  # !BSF NAME:{Enhanced Interleave support}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Enhanced Interleave support}
  gPlatformFspPkgTokenSpaceGuid.EnhancedInterleave       | * | 0x01 | 0x01

  # !BSF NAME:{Memory Trace}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable Memory Trace of Ch 0 to Ch 1 using Stacked Mode. Both channels must be of equal size. This option may change TOLUD and REMAP values as needed.}
  gPlatformFspPkgTokenSpaceGuid.MemoryTrace              | * | 0x01 | 0x00

  # !BSF NAME:{Ch Hash Support}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable Channel Hash Support. NOTE: ONLY if Memory interleaved Mode}
  gPlatformFspPkgTokenSpaceGuid.ChHashEnable             | * | 0x01 | 0x01

  # !BSF NAME:{Extern Therm Status}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Extern Therm Status}
  gPlatformFspPkgTokenSpaceGuid.EnableExtts              | * | 0x01 | 0x00

  # !BSF NAME:{Closed Loop Therm Manage}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Closed Loop Therm Manage}
  gPlatformFspPkgTokenSpaceGuid.EnableCltm               | * | 0x01 | 0x00

  # !BSF NAME:{Open Loop Therm Manage}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Open Loop Therm Manage}
  gPlatformFspPkgTokenSpaceGuid.EnableOltm               | * | 0x01 | 0x00

  # !BSF NAME:{DDR PowerDown and idle counter}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable DDR PowerDown and idle counter}
  gPlatformFspPkgTokenSpaceGuid.EnablePwrDn              | * | 0x01 | 0x01

  # !BSF NAME:{DDR PowerDown and idle counter - LPDDR}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable DDR PowerDown and idle counter(For LPDDR Only)}
  gPlatformFspPkgTokenSpaceGuid.EnablePwrDnLpddr         | * | 0x01 | 0x01

  # !BSF NAME:{Use user provided power weights, scale factor, and channel power floor values}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Use user provided power weights, scale factor, and channel power floor values}
  gPlatformFspPkgTokenSpaceGuid.UserPowerWeightsEn       | * | 0x01 | 0x00

  # !BSF NAME:{RAPL PL Lock}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable RAPL PL Lock}
  gPlatformFspPkgTokenSpaceGuid.RaplLim2Lock             | * | 0x01 | 0x00

  # !BSF NAME:{RAPL PL 2 enable}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable RAPL PL 2 enable}
  gPlatformFspPkgTokenSpaceGuid.RaplLim2Ena              | * | 0x01 | 0x00

  # !BSF NAME:{RAPL PL 1 enable}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable RAPL PL 1 enable}
  gPlatformFspPkgTokenSpaceGuid.RaplLim1Ena              | * | 0x01 | 0x00

  # !BSF NAME:{SelfRefresh Enable}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable SelfRefresh Enable}
  gPlatformFspPkgTokenSpaceGuid.SrefCfgEna               | * | 0x01 | 0x01

  # !BSF NAME:{Throttler CKEMin Defeature - LPDDR}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Throttler CKEMin Defeature(For LPDDR Only)}
  gPlatformFspPkgTokenSpaceGuid.ThrtCkeMinDefeatLpddr    | * | 0x01 | 0x01

  # !BSF NAME:{Throttler CKEMin Defeature}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Throttler CKEMin Defeature}
  gPlatformFspPkgTokenSpaceGuid.ThrtCkeMinDefeat         | * | 0x01 | 0x00

  # !BSF NAME:{Enable RH Prevention}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable RH Prevention}
  gPlatformFspPkgTokenSpaceGuid.RhPrevention             | * | 0x01 | 0x00

  # !BSF NAME:{Exit On Failure (MRC)}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable Exit On Failure (MRC)}
  gPlatformFspPkgTokenSpaceGuid.ExitOnFailure            | * | 0x01 | 0x01

  # !BSF NAME:{LPDDR Thermal Sensor}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables/Disable LPDDR Thermal Sensor}
  gPlatformFspPkgTokenSpaceGuid.DdrThermalSensor         | * | 0x01 | 0x01
  gPlatformFspPkgTokenSpaceGuid.Reserved2                | * | 0x02 | {0x00}

  # !BSF NAME:{Select if CLK0 is shared between Rank0 and Rank1 in DDR4 DDP}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Select if CLK0 is shared between Rank0 and Rank1 in DDR4 DDP}
  gPlatformFspPkgTokenSpaceGuid.Ddr4DdpSharedClock       | * | 0x01 | 0x00

  # !BSF NAME:{Select if ZQ pin is shared between Rank0 and Rank1 in DDR4 DDP}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{ESelect if ZQ pin is shared between Rank0 and Rank1 in DDR4 DDP}
  gPlatformFspPkgTokenSpaceGuid.Ddr4DdpSharedZq          | * | 0x01 | 0x00

  # !BSF NAME:{Ch Hash Interleaved Bit}
  # !BSF TYPE:{Combo} OPTION:{0:BIT6, 1:BIT7, 2:BIT8, 3:BIT9, 4:BIT10, 5:BIT11, 6:BIT12, 7:BIT13}
  # !BSF HELP:{Select the BIT to be used for Channel Interleaved mode. NOTE: BIT7 will interlave the channels at a 2 cacheline granularity, BIT8 at 4 and BIT9 at 8. Default is BIT8}
  gPlatformFspPkgTokenSpaceGuid.ChHashInterleaveBit     | * | 0x01 | 0x02

  # !BSF NAME:{Ch Hash Mask}
  # !BSF TYPE:{EditNum, HEX, (0x0000, 0x3FFF)}
  # !BSF HELP:{Set the BIT(s) to be included in the XOR function. NOTE BIT mask corresponds to BITS [19:6] Default is 0x30CC}
  gPlatformFspPkgTokenSpaceGuid.ChHashMask              | * | 0x02 | 0x30CC

  # !BSF NAME:{Base reference clock value}
  # !BSF TYPE:{Combo} OPTION:{100000000:100Hz, 125000000:125Hz, 167000000:167Hz, 250000000:250Hz}
  # !BSF HELP:{Base reference clock value, in Hertz(Default is 125Hz)}
  gPlatformFspPkgTokenSpaceGuid.BClkFrequency           | * | 0x04 | 100000000

  # !BSF NAME:{Extended Bank Hashing}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Eanble/Disable ExtendedBankHashing}
  gPlatformFspPkgTokenSpaceGuid.ExtendedBankHashing       | * | 0x01 | 0x01

  # !BSF NAME:{Energy Scale Factor}
  # !BSF TYPE:{EditNum, HEX, (0x01, 0x07)}
  # !BSF HELP:{Energy Scale Factor, Default is 4}
  gPlatformFspPkgTokenSpaceGuid.EnergyScaleFact         | * | 0x01 | 0x04

  # !BSF NAME:{CMD Slew Rate Training}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable CMD Slew Rate Training}
  gPlatformFspPkgTokenSpaceGuid.CMDSR                   | * | 0x01 | 0x00

  # !BSF NAME:{EPG DIMM Idd3N}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x7D0)}
  # !BSF HELP:{Active standby current (Idd3N) in milliamps from datasheet. Must be calculated on a per DIMM basis. Default is 26}
  gPlatformFspPkgTokenSpaceGuid.Idd3n                   | * | 0x02 | 0x1A

  # !BSF NAME:{EPG DIMM Idd3P}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x7D0)}
  # !BSF HELP:{Active power-down current (Idd3P) in milliamps from datasheet. Must be calculated on a per DIMM basis. Default is 11}
  gPlatformFspPkgTokenSpaceGuid.Idd3p                   | * | 0x02 | 0x0B

  # !BSF NAME:{CMD Drive Strength and Tx Equalization}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable CMD Drive Strength and Tx Equalization}
  gPlatformFspPkgTokenSpaceGuid.CMDDSEQ                 | * | 0x01 | 0x00

  # !BSF NAME:{CMD Normalization}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable CMD Normalization}
  gPlatformFspPkgTokenSpaceGuid.CMDNORM                 | * | 0x01 | 0x00

  # !BSF NAME:{Early DQ Write Drive Strength and Equalization Training}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable Early DQ Write Drive Strength and Equalization Training}
  gPlatformFspPkgTokenSpaceGuid.EWRDSEQ                 | * | 0x01 | 0x00

  # !BSF NAME:{RH Activation Probability}
  # !BSF TYPE:{EditNum, HEX, (0x01, 0xF)}
  # !BSF HELP:{RH Activation Probability, Probability value is 1/2^(inputvalue)}
  gPlatformFspPkgTokenSpaceGuid.RhActProbability        | * | 0x01 | 0xB

  # !BSF NAME:{RAPL PL 2 WindowX}
  # !BSF TYPE:{EditNum, HEX, (0x01, 0x03)}
  # !BSF HELP:{Power PL 2 time window X value, (1/1024)*(1+(x/4))*(2^y) (0=Def)}
  gPlatformFspPkgTokenSpaceGuid.RaplLim2WindX           | * | 0x01 | 0x1

  # !BSF NAME:{RAPL PL 2 WindowY}
  # !BSF TYPE:{EditNum, HEX, (0x01, 0x1F)}
  # !BSF HELP:{Power PL 2 time window Y value, (1/1024)*(1+(x/4))*(2^y) (0=Def)}
  gPlatformFspPkgTokenSpaceGuid.RaplLim2WindY           | * | 0x01 | 0x0A

  # !BSF NAME:{RAPL PL 1 WindowX}
  # !BSF TYPE:{EditNum, HEX, (0x01, 0x03)}
  # !BSF HELP:{Power PL 1 time window X value, (1/1024)*(1+(x/4))*(2^y) (0=Def)}
  gPlatformFspPkgTokenSpaceGuid.RaplLim1WindX           | * | 0x01 | 0x00

  # !BSF NAME:{RAPL PL 1 WindowY}
  # !BSF TYPE:{EditNum, HEX, (0x01, 0x1F)}
  # !BSF HELP:{Power PL 1 time window Y value, (1/1024)*(1+(x/4))*(2^y) (0=Def)}
  gPlatformFspPkgTokenSpaceGuid.RaplLim1WindY           | * | 0x01 | 0x00

  # !BSF NAME:{RAPL PL 2 Power}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0x3FFF)}
  # !BSF HELP:{range[0;2^14-1]= [2047.875;0]in W, (224= Def)}
  gPlatformFspPkgTokenSpaceGuid.RaplLim2Pwr             | * | 0x02 | 0xDE

  # !BSF NAME:{RAPL PL 1 Power}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0x3FFF)}
  # !BSF HELP:{range[0;2^14-1]= [2047.875;0]in W, (224= Def)}
  gPlatformFspPkgTokenSpaceGuid.RaplLim1Pwr             | * | 0x02 | 0x00

  # !BSF NAME:{Warm Threshold Ch0 Dimm0}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{range[255;0]=[31.875;0] in W for OLTM, [127.5;0] in C for CLTM. Fefault is 255}
  gPlatformFspPkgTokenSpaceGuid.WarmThresholdCh0Dimm0   | * | 0x01 | 0xFF

  # !BSF NAME:{Warm Threshold Ch0 Dimm1}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{range[255;0]=[31.875;0] in W for OLTM, [127.5;0] in C for CLTM. Fefault is 255}
  gPlatformFspPkgTokenSpaceGuid.WarmThresholdCh0Dimm1   | * | 0x01 | 0xFF

  # !BSF NAME:{Warm Threshold Ch1 Dimm0}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{range[255;0]=[31.875;0] in W for OLTM, [127.5;0] in C for CLTM. Fefault is 255}
  gPlatformFspPkgTokenSpaceGuid.WarmThresholdCh1Dimm0   | * | 0x01 | 0xFF

  # !BSF NAME:{Warm Threshold Ch1 Dimm1}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{range[255;0]=[31.875;0] in W for OLTM, [127.5;0] in C for CLTM. Fefault is 255}
  gPlatformFspPkgTokenSpaceGuid.WarmThresholdCh1Dimm1   | * | 0x01 | 0xFF

  # !BSF NAME:{Hot Threshold Ch0 Dimm0}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{range[255;0]=[31.875;0] in W for OLTM, [127.5;0] in C for CLTM. Fefault is 255}
  gPlatformFspPkgTokenSpaceGuid.HotThresholdCh0Dimm0    | * | 0x01 | 0xFF

  # !BSF NAME:{Hot Threshold Ch0 Dimm1}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{range[255;0]=[31.875;0] in W for OLTM, [127.5;0] in C for CLTM. Fefault is 255}
  gPlatformFspPkgTokenSpaceGuid.HotThresholdCh0Dimm1    | * | 0x01 | 0xFF

  # !BSF NAME:{Hot Threshold Ch1 Dimm0}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{range[255;0]=[31.875;0] in W for OLTM, [127.5;0] in C for CLTM. Fefault is 255}
  gPlatformFspPkgTokenSpaceGuid.HotThresholdCh1Dimm0    | * | 0x01 | 0xFF

  # !BSF NAME:{Hot Threshold Ch1 Dimm1}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{range[255;0]=[31.875;0] in W for OLTM, [127.5;0] in C for CLTM. Fefault is 255}
  gPlatformFspPkgTokenSpaceGuid.HotThresholdCh1Dimm1    | * | 0x01 | 0xFF

  # !BSF NAME:{Warm Budget Ch0 Dimm0}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{range[255;0]=[31.875;0] in W for OLTM, [127.5;0] in C for CLTM}
  gPlatformFspPkgTokenSpaceGuid.WarmBudgetCh0Dimm0      | * | 0x01 | 0xFF

  # !BSF NAME:{Warm Budget Ch0 Dimm1}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{range[255;0]=[31.875;0] in W for OLTM, [127.5;0] in C for CLTM}
  gPlatformFspPkgTokenSpaceGuid.WarmBudgetCh0Dimm1      | * | 0x01 | 0xFF

  # !BSF NAME:{Warm Budget Ch1 Dimm0}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{range[255;0]=[31.875;0] in W for OLTM, [127.5;0] in C for CLTM}
  gPlatformFspPkgTokenSpaceGuid.WarmBudgetCh1Dimm0      | * | 0x01 | 0xFF

  # !BSF NAME:{Warm Budget Ch1 Dimm1}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{range[255;0]=[31.875;0] in W for OLTM, [127.5;0] in C for CLTM}
  gPlatformFspPkgTokenSpaceGuid.WarmBudgetCh1Dimm1      | * | 0x01 | 0xFF

  # !BSF NAME:{Hot Budget Ch0 Dimm0}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{range[255;0]=[31.875;0] in W for OLTM, [127.5;0] in C for CLTM}
  gPlatformFspPkgTokenSpaceGuid.HotBudgetCh0Dimm0       | * | 0x01 | 0xFF

  # !BSF NAME:{Hot Budget Ch0 Dimm1}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{range[255;0]=[31.875;0] in W for OLTM, [127.5;0] in C for CLTM}
  gPlatformFspPkgTokenSpaceGuid.HotBudgetCh0Dimm1       | * | 0x01 | 0xFF

  # !BSF NAME:{Hot Budget Ch1 Dimm0}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{range[255;0]=[31.875;0] in W for OLTM, [127.5;0] in C for CLTM}
  gPlatformFspPkgTokenSpaceGuid.HotBudgetCh1Dimm0       | * | 0x01 | 0xFF

  # !BSF NAME:{Hot Budget Ch1 Dimm1}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{range[255;0]=[31.875;0] in W for OLTM, [127.5;0] in C for CLTM}
  gPlatformFspPkgTokenSpaceGuid.HotBudgetCh1Dimm1       | * | 0x01 | 0xFF

  # !BSF NAME:{Idle Energy Ch0Dimm0}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0x3F)}
  # !BSF HELP:{Idle Energy Consumed for 1 clk w/dimm idle/cke on, range[63;0],(10= Def)}
  gPlatformFspPkgTokenSpaceGuid.IdleEnergyCh0Dimm0      | * | 0x01 | 0x0A

  # !BSF NAME:{Idle Energy Ch0Dimm1}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0x3F)}
  # !BSF HELP:{Idle Energy Consumed for 1 clk w/dimm idle/cke on, range[63;0],(10= Def)}
  gPlatformFspPkgTokenSpaceGuid.IdleEnergyCh0Dimm1      | * | 0x01 | 0x0A

  # !BSF NAME:{Idle Energy Ch1Dimm0}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0x3F)}
  # !BSF HELP:{Idle Energy Consumed for 1 clk w/dimm idle/cke on, range[63;0],(10= Def)}
  gPlatformFspPkgTokenSpaceGuid.IdleEnergyCh1Dimm0      | * | 0x01 | 0x0A

  # !BSF NAME:{Idle Energy Ch1Dimm1}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0x3F)}
  # !BSF HELP:{Idle Energy Consumed for 1 clk w/dimm idle/cke on, range[63;0],(10= Def)}
  gPlatformFspPkgTokenSpaceGuid.IdleEnergyCh1Dimm1      | * | 0x01 | 0x0A

  # !BSF NAME:{PowerDown Energy Ch0Dimm0}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0x3F)}
  # !BSF HELP:{PowerDown Energy Consumed w/dimm idle/cke off, range[63;0],(6= Def)}
  gPlatformFspPkgTokenSpaceGuid.PdEnergyCh0Dimm0         | * | 0x01 | 0x06

  # !BSF NAME:{PowerDown Energy Ch0Dimm1}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0x3F)}
  # !BSF HELP:{PowerDown Energy Consumed w/dimm idle/cke off, range[63;0],(6= Def)}
  gPlatformFspPkgTokenSpaceGuid.PdEnergyCh0Dimm1         | * | 0x01 | 0x06

  # !BSF NAME:{PowerDown Energy Ch1Dimm0}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0x3F)}
  # !BSF HELP:{PowerDown Energy Consumed w/dimm idle/cke off, range[63;0],(6= Def)}
  gPlatformFspPkgTokenSpaceGuid.PdEnergyCh1Dimm0         | * | 0x01 | 0x06

  # !BSF NAME:{PowerDown Energy Ch1Dimm1}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0x3F)}
  # !BSF HELP:{PowerDown Energy Consumed w/dimm idle/cke off, range[63;0],(6= Def)}
  gPlatformFspPkgTokenSpaceGuid.PdEnergyCh1Dimm1         | * | 0x01 | 0x06

  # !BSF NAME:{Activate Energy Ch0Dimm0}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{Activate Energy Contribution, range[255;0],(172= Def)}
  gPlatformFspPkgTokenSpaceGuid.ActEnergyCh0Dimm0         | * | 0x01 | 0xAC

  # !BSF NAME:{Activate Energy Ch0Dimm1}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{Activate Energy Contribution, range[255;0],(172= Def)}
  gPlatformFspPkgTokenSpaceGuid.ActEnergyCh0Dimm1         | * | 0x01 | 0xAC

  # !BSF NAME:{Activate Energy Ch1Dimm0}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{Activate Energy Contribution, range[255;0],(172= Def)}
  gPlatformFspPkgTokenSpaceGuid.ActEnergyCh1Dimm0         | * | 0x01 | 0xAC

  # !BSF NAME:{Activate Energy Ch1Dimm1}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{Activate Energy Contribution, range[255;0],(172= Def)}
  gPlatformFspPkgTokenSpaceGuid.ActEnergyCh1Dimm1         | * | 0x01 | 0xAC

  # !BSF NAME:{Read Energy Ch0Dimm0}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{Read Energy Contribution, range[255;0],(212= Def)}
  gPlatformFspPkgTokenSpaceGuid.RdEnergyCh0Dimm0         | * | 0x01 | 0xD4

  # !BSF NAME:{Read Energy Ch0Dimm1}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{Read Energy Contribution, range[255;0],(212= Def)}
  gPlatformFspPkgTokenSpaceGuid.RdEnergyCh0Dimm1         | * | 0x01 | 0xD4

  # !BSF NAME:{Read Energy Ch1Dimm0}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{Read Energy Contribution, range[255;0],(212= Def)}
  gPlatformFspPkgTokenSpaceGuid.RdEnergyCh1Dimm0         | * | 0x01 | 0xD4

  # !BSF NAME:{Read Energy Ch1Dimm1}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{Read Energy Contribution, range[255;0],(212= Def)}
  gPlatformFspPkgTokenSpaceGuid.RdEnergyCh1Dimm1         | * | 0x01 | 0xD4

  # !BSF NAME:{Write Energy Ch0Dimm0}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{Write Energy Contribution, range[255;0],(221= Def)}
  gPlatformFspPkgTokenSpaceGuid.WrEnergyCh0Dimm0         | * | 0x01 | 0xDD

  # !BSF NAME:{Write Energy Ch0Dimm1}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{Write Energy Contribution, range[255;0],(221= Def)}
  gPlatformFspPkgTokenSpaceGuid.WrEnergyCh0Dimm1         | * | 0x01 | 0xDD

  # !BSF NAME:{Write Energy Ch1Dimm0}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{Write Energy Contribution, range[255;0],(221= Def)}
  gPlatformFspPkgTokenSpaceGuid.WrEnergyCh1Dimm0         | * | 0x01 | 0xDD

  # !BSF NAME:{Write Energy Ch1Dimm1}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{Write Energy Contribution, range[255;0],(221= Def)}
  gPlatformFspPkgTokenSpaceGuid.WrEnergyCh1Dimm1         | * | 0x01 | 0xDD

  # !BSF NAME:{Throttler CKEMin Timer}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{Timer value for CKEMin, range[255;0]. Req'd min of SC_ROUND_T + BYTE_LENGTH (4). Dfault is 0x30}
  gPlatformFspPkgTokenSpaceGuid.ThrtCkeMinTmr         | * | 0x01 | 0x30

  # !BSF NAME:{Cke Rank Mapping}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{Bits [7:4] - Channel 1, bits [3:0] - Channel 0. <b>0xAA=Default</b> Bit [i] specifies which rank CKE[i] goes to.}
  gPlatformFspPkgTokenSpaceGuid.CkeRankMapping         | * | 0x01 | 0xAA

  # !BSF NAME:{Rapl Power Floor Ch0}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{Power budget ,range[255;0],(0= 5.3W Def)}
  gPlatformFspPkgTokenSpaceGuid.RaplPwrFlCh0         | * | 0x01 | 0x00

  # !BSF NAME:{Rapl Power Floor Ch1}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{Power budget ,range[255;0],(0= 5.3W Def)}
  gPlatformFspPkgTokenSpaceGuid.RaplPwrFlCh1         | * | 0x01 | 0x00

  # !BSF NAME:{Command Rate Support}
  # !BSF TYPE:{Combo} OPTION:{0:Disable, 1:1 CMD, 2:2 CMDS, 3:3 CMDS, 4:4 CMDS, 5:5 CMDS, 6:6 CMDS, 7:7 CMDS}
  # !BSF HELP:{CMD Rate and Limit Support Option. NOTE: ONLY supported in 1N Mode, Default is 3 CMDs}
  gPlatformFspPkgTokenSpaceGuid.EnCmdRate         | * | 0x01 | 0x03

  # !BSF NAME:{REFRESH_2X_MODE}
  # !BSF TYPE:{Combo} OPTION:{0:Disable, 1:Enabled for WARM or HOT, 2:Enabled HOT only}
  # !BSF HELP:{0- (Default)Disabled 1-iMC enables 2xRef when Warm and Hot 2- iMC enables 2xRef when Hot}
  gPlatformFspPkgTokenSpaceGuid.Refresh2X         | * | 0x01 | 0x00

  # !BSF NAME:{Energy Performance Gain}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable(default) Energy Performance Gain.}
  gPlatformFspPkgTokenSpaceGuid.EpgEnable         | * | 0x01 | 0x00

  # !BSF NAME:{Row Hammer Solution}
  # !BSF TYPE:{Combo} OPTION:{0:Hardware RHP, 1:2x Refresh}
  # !BSF HELP:{Type of method used to prevent Row Hammer. Default is Hardware RHP}
  gPlatformFspPkgTokenSpaceGuid.RhSolution         | * | 0x01 | 0x00

  # !BSF NAME:{User Manual Threshold}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Disabled: Predefined threshold will be used.\nEnabled: User Input will be used.}
  gPlatformFspPkgTokenSpaceGuid.UserThresholdEnable         | * | 0x01 | 0x00

  # !BSF NAME:{User Manual Budget}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Disabled: Configuration of memories will defined the Budget value.\nEnabled: User Input will be used.}
  gPlatformFspPkgTokenSpaceGuid.UserBudgetEnable         | * | 0x01 | 0x00

  # !BSF NAME:{  TcritMax}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0x7F)}
  # !BSF HELP:{Maximum Critical Temperature in Centigrade of the On-DIMM Thermal Sensor. TCRITMax has to be greater than THIGHMax .\n Critical temperature will be  TcritMax}
  gPlatformFspPkgTokenSpaceGuid.TsodTcritMax         | * | 0x01 | 0x69

  # !BSF NAME:{Event mode}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Disable:Comparator mode.\n Enable:Interrupt mode}
  gPlatformFspPkgTokenSpaceGuid.TsodEventMode         | * | 0x01 | 0x00

  # !BSF NAME:{EVENT polarity}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Disable:Active LOW.\nEnable:Active HIGH}
  gPlatformFspPkgTokenSpaceGuid.TsodEventPolarity     | * | 0x01 | 0x00

  # !BSF NAME:{Critical event only}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Disable:Trips on alarm or critical.\nEnable:Trips only if criticaal temperature is reached}
  gPlatformFspPkgTokenSpaceGuid.TsodCriticalEventOnly     | * | 0x01 | 0x00

  # !BSF NAME:{Event output control}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Disable:Event output disable.\nEnable:Event output enabled}
  gPlatformFspPkgTokenSpaceGuid.TsodEventOutputControl     | * | 0x01 | 0x00

  # !BSF NAME:{Alarm window lock bit}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Disable:Alarm trips are not locked and can be changed.\nEnable:Alarm trips are locked and cannot be changed}
  gPlatformFspPkgTokenSpaceGuid.TsodAlarmwindowLockBit     | * | 0x01 | 0x00

  # !BSF NAME:{Critical trip lock bit}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Disable:Critical trip is not locked and can be changed.\nEnable:Critical trip is locked and cannot be changed}
  gPlatformFspPkgTokenSpaceGuid.TsodCriticaltripLockBit     | * | 0x01 | 0x00

  # !BSF NAME:{Shutdown mode}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Disable:Temperature sensor enable.\nEnable:Temperature sensor disable}
  gPlatformFspPkgTokenSpaceGuid.TsodShutdownMode      | * | 0x01 | 0x00

  # !BSF NAME:{ThighMax}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0x80)}
  # !BSF HELP:{Thigh = ThighMax (Default is 93)}
  gPlatformFspPkgTokenSpaceGuid.TsodThigMax           | * | 0x01 | 0x5D

  # !BSF NAME:{User Manual Thig and Tcrit}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Disabled(Default): Temperature will be given by the configuration of memories and 1x or 2xrefresh rate.\nEnabled: User Input will define for Thigh and Tcrit.}
  gPlatformFspPkgTokenSpaceGuid.TsodManualEnable      | * | 0x01 | 0x00

  # !BSF NAME:{Force OLTM or 2X Refresh when needed}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Disabled(Default): = Force OLTM.\nEnabled: = Force 2x Refresh.}
  gPlatformFspPkgTokenSpaceGuid.ForceOltmOrRefresh2x  | * | 0x01 | 0x00

  # !BSF NAME:{Pwr Down Idle Timer}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{The minimum value should = to the worst case Roundtrip delay + Burst_Length. 0 means AUTO: 64 for ULX/ULT, 128 for DT/Halo}
  gPlatformFspPkgTokenSpaceGuid.PwdwnIdleCounter      | * | 0x01 | 0x00

  # !BSF NAME:{Page Close Idle Timeout}
  # !BSF TYPE:{Combo} OPTION:{0:Enabled, 1:Disabled}
  # !BSF HELP:{This option controls Page Close Idle Timeout}
  gPlatformFspPkgTokenSpaceGuid.DisPgCloseIdleTimeout            | * | 0x01 | 0x0

  # !BSF NAME:{Bitmask of ranks that have CA bus terminated}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{Offset 225 LPDDR4: Bitmask of ranks that have CA bus terminated. <b>0x01=Default, Rank0 is terminating and Rank1 is non-terminating</b>}
  gPlatformFspPkgTokenSpaceGuid.CmdRanksTerminated         | * | 0x01 | 0x01

  # !BSF NAME:{Throttler CKEMin Timer for LPDDR}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFF)}
  # !BSF HELP:{LPDDR Timer value for CKEMin, range[255;0]. Req'd min of SC_ROUND_T + BYTE_LENGTH (4). Dfault is 0x40}
  gPlatformFspPkgTokenSpaceGuid.ThrtCkeMinTmrLpddr    | * | 0x01 | 0x40

  # !BSF NAME:{Retrain on Fast Fail}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Restart MRC in Cold mode if SW MemTest fails during Fast flow. Default = Enabled}
  gPlatformFspPkgTokenSpaceGuid.RetrainOnFastFail     | * | 0x01 | 0x01

  # !BSF NAME:{Rank Margin Tool Per Bit}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable Rank Margin Tool Per Bit.}
  gPlatformFspPkgTokenSpaceGuid.RMTBIT                | * | 0x01 | 0x00

  # !BSF NAME:{PcdSerialDebugLevel} TYPE:{Combo}
  # !BSF OPTION:{0:Disable, 1:Error Only, 2:Error and Warnings, 3:Load Error Warnings and Info, 4:Load Error Warnings and Info, 5:Load Error Warnings Info and Verbose}
  # !BSF HELP:{Serial Debug Message Level. 0:Disable, 1:Error Only, 2:Error & Warnings, 3:Load, Error, Warnings & Info, 4:Load, Error, Warnings, Info & Event, 5:Load, Error, Warnings, Info & Verbose.}
  gPlatformFspPkgTokenSpaceGuid.PcdSerialDebugLevel       | * | 0x01 | 0x03

  # !BSF NAME:{Fivr Faults} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Fivr Faults; 0: Disabled; <b>1: Enabled.</b>}
  gPlatformFspPkgTokenSpaceGuid.FivrFaults                  | * | 0x01 | 0x00

  # !BSF NAME:{Fivr Efficiency} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Fivr Efficiency Management; 0: Disabled; <b>1: Enabled.</b>}
  gPlatformFspPkgTokenSpaceGuid.FivrEfficiency              | * | 0x01 | 0x00

  # !BSF NAME:{Safe Mode Support}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{This option configures the varous items in the IO and MC to be more conservative.(def=Disable)}
  gPlatformFspPkgTokenSpaceGuid.SafeMode          | * | 0x01 | 0x00

  # !BSF NAME:{Ask MRC to clear memory content} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Ask MRC to clear memory content <b>0: Do not Clear Memory;</b> 1: Clear Memory.}
  gPlatformFspPkgTokenSpaceGuid.CleanMemory                 | * | 0x01 | 0x00

  # !BSF NAME:{TCSS USB Port Enable} TYPE:{EditNum, HEX, (0x0,0x000F)}
  # !BSF HELP:{Bitmap for per port enabling}
  gPlatformFspPkgTokenSpaceGuid.UsbTcPortEnPreMem                 | * | 0x01 | 0x00

  # !BSF NAME:{Post Code Output Port}
  # !BSF TYPE:{EditNum, HEX, (0x0, 0xFFFF)}
  # !BSF HELP:{This option configures Post Code Output Port}
  gPlatformFspPkgTokenSpaceGuid.PostCodeOutputPort          | * | 0x02 | 0x80

  # !BSF NAME:{RMTLoopCount} TYPE:{EditNum, HEX, (0, 0x20)}
  # !BSF HELP:{Specifies the Loop Count to be used during Rank Margin Tool Testing. 0 - AUTO}
  gPlatformFspPkgTokenSpaceGuid.RMTLoopCount                | * | 0x01 | 0x00

  # !BSF NAME:{Enable/Disable SA CRID} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable: SA CRID, Disable (Default): SA CRID}
  gPlatformFspPkgTokenSpaceGuid.CridEnable                  | * | 0x01 | 0x0

  # !BSF NAME:{BCLK RFI Frequency} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT32}
  # !BSF HELP:{Bclk RFI Frequency for each SAGV point in Hz units. 98000000Hz = 98MHz <b>0 - No RFI Tuning</b>. Range is 98Mhz-100Mhz.}
  gPlatformFspPkgTokenSpaceGuid.BclkRfiFreq               | * | 0x10 | {0x00000000, 0x00000000, 0x00000000, 0x00000000}

  # !BSF NAME:{Size of PCIe IMR.} TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{Size of PCIe IMR in megabytes}
  gPlatformFspPkgTokenSpaceGuid.PcieImrSize               | * | 0x02 | 0x00

  # !BSF NAME:{Enable PCIe IMR} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Disable(AUTO), 1: Enable}
  gPlatformFspPkgTokenSpaceGuid.PcieImrEnabled            | * | 0x01 | 0x00

  # !BSF NAME:{Enable PCIe IMR} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{1: PCH PCIE, 2: SA PCIE. If PCIeImrEnabled is TRUE then this will use to select the Root port location from PCH PCIe or SA PCIe}
  gPlatformFspPkgTokenSpaceGuid.PcieImrRpLocation         | * | 0x01 | 0x01

  # !BSF NAME:{Root port number for IMR.} TYPE:{EditNum, HEX, (0x00,0x17)}
  # !BSF HELP:{Root port number for IMR.If PCieImrRpLocation is PCH PCIe then select root port from 0 to 23 and if it is SA PCIe then select root port from 0 to 3}
  gPlatformFspPkgTokenSpaceGuid.PcieImrRpSelection            | * | 0x01 | 0x00


  #
  # 2LM: Begin
  #

  # 2LM pre-mem config
  # !BSF NAME:{Mem Boot Mode} TYPE:{Combo}
  # !BSF OPTION:{0: BOOT_MODE_1LM, 1: BOOT_MODE_2LM, 2: BOOT_MODE_PROVISION}
  # !BSF HELP:{0: BOOT_MODE_1LM(Default), 1: BOOT_MODE_2LM, 2: BOOT_MODE_PROVISION}
  gPlatformFspPkgTokenSpaceGuid.MemBootMode                 | * | 0x01 | 0x00

  # !BSF NAME:{PCIe ASPM programming will happen in relation to the Oprom} TYPE:{Combo}
  # !BSF OPTION:{0:Disabled, 1:L0, 2:L1, 3:L0L1, 4:Auto}
  # !BSF HELP:{This option is specifically needed for ASPM configuration in 2LM feature}
  gPlatformFspPkgTokenSpaceGuid.Peg3Aspm                    | * | 0x01 | 0x3

  # !BSF NAME:{MFVC WRR VC Arbitration} TYPE:{Combo}
  # !BSF OPTION:{0: DEFAULT_PHASES, 1: PROGRAM_128PHASES}
  # !BSF HELP:{0: DEFAULT_PHASES(Default), 1: PROGRAM_128PHASES}
  gPlatformFspPkgTokenSpaceGuid.MfvcWrrArb                 | * | 0x01 | 0x00

  # !BSF NAME:{VcId_7_0 values} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{Select VC ID for arbitration}
  gPlatformFspPkgTokenSpaceGuid.VcId_7_0         | * | 0x10 | {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Set Hw Parameters enable/disable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{1: enable, 0: disable, Enable/disable setting of HW parameters}
  gPlatformFspPkgTokenSpaceGuid.SetHwParameters                | * | 0x01 | 0x0

  # !BSF NAME:{LTR L1.2 Threshold Value} TYPE:{EditNum, HEX, (0x0,0x3FF)}
  # !BSF HELP:{LTR L1.2 Threshold Value}
  gPlatformFspPkgTokenSpaceGuid.Ltr_L1D2_ThVal           | * | 0x02 | 0x00

  # !BSF NAME:{LTR L1.2 Threshold Scale} TYPE:{EditNum, HEX, (0x0,0x5)}
  # !BSF HELP:{LTR L1.2 Threshold Scale}
  gPlatformFspPkgTokenSpaceGuid.Ltr_L1D2_ThScale           | * | 0x01 | 0x00

  # !BSF NAME:{system power state}       TYPE:{EditNum, HEX, (0x0,0x3)}
  # !BSF HELP:{system power state indicates the platform power state}
  gPlatformFspPkgTokenSpaceGuid.SysPwrState           | * | 0x01 | 0x00

  # !BSF NAME:{Media Death Notification Enable/Disable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{1: enable, 0: disable, Enable/disable for Media Death Notification}
  gPlatformFspPkgTokenSpaceGuid.MediaDeathNotification                | * | 0x01 | 0x0

  # !BSF NAME:{Health Log Notification Enable/Disable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{1: enable, 0: disable, Enable/disable for Health Log Notification}
  gPlatformFspPkgTokenSpaceGuid.HealthLogNotification                | * | 0x01 | 0x0

  # !BSF NAME:{Temp crosses below TempThrottle Notification Enable/Disable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{1: enable, 0: disable, Enable/disable for Temp crosses below TempThrottle Notification}
  gPlatformFspPkgTokenSpaceGuid.TempBelowThrottleNotification                | * | 0x01 | 0x0

  # !BSF NAME:{Temp crosses above TempThrottle Notification Enable/Disable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{1: enable, 0: disable, Enable/disable for Temp crosses above TempThrottle Notification}
  gPlatformFspPkgTokenSpaceGuid.TempAboveThrottleNotification                | * | 0x01 | 0x0

  # !BSF NAME:{Missing Commit Bit Notification Enable/Disable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{1: enable, 0: disable, Enable/disable for Missing Commit Bit Notification}
  gPlatformFspPkgTokenSpaceGuid.MissingCommitBitNotification                | * | 0x01 | 0x0

  # !BSF NAME:{NVMeHoldDisableBit} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{1: enable, 0: disable, Enable/disable for NVMeHoldDisableBit}
  gPlatformFspPkgTokenSpaceGuid.NVMeHoldDisableBit        | * | 0x01 | 0x0

  #
  # 2LM: End
  #

  # !BSF NAME:{PreMemRsvd} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Reserved for Pre-Mem}
  gPlatformFspPkgTokenSpaceGuid.ReservedFspmUpd           | * | 0x12 | {0x00}

  #
  # SA Pre-Mem Block Start
  #
  # !BSF PAGE:{SA1}
  # !BSF NAME:{Skip external display device scanning} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable: Do not scan for external display device, Disable (Default): Scan external display devices}
  gPlatformFspPkgTokenSpaceGuid.SkipExtGfxScan              | * | 0x01 | 0x1

  # !BSF NAME:{Generate BIOS Data ACPI Table} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable: Generate BDAT for MRC RMT or SA PCIe data. Disable (Default): Do not generate it}
  gPlatformFspPkgTokenSpaceGuid.BdatEnable                  | * | 0x01 | 0x00

  # !BSF NAME:{Detect External Graphics device for LegacyOpROM} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Detect and report if external graphics device only support LegacyOpROM or not (to support CSM auto-enable). Enable(Default)=1, Disable=0}
  gPlatformFspPkgTokenSpaceGuid.ScanExtGfxForLegacyOpRom    | * | 0x01 | 0x00

  # !BSF NAME:{Lock PCU Thermal Management registers} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Lock PCU Thermal Management registers. Enable(Default)=1, Disable=0}
  gPlatformFspPkgTokenSpaceGuid.LockPTMregs                 | * | 0x01 | 0x01

  # !BSF NAME:{DMI Max Link Speed} TYPE:{Combo}
  # !BSF OPTION:{0:Auto, 1:Gen1, 2:Gen2, 3:Gen3}
  # !BSF HELP:{Auto (Default)(0x0): Maximum possible link speed, Gen1(0x1): Limit Link to Gen1 Speed, Gen2(0x2): Limit Link to Gen2 Speed, Gen3(0x3):Limit Link to Gen3 Speed}
  gPlatformFspPkgTokenSpaceGuid.DmiMaxLinkSpeed             | * | 0x01 | 0x00

  # !BSF NAME:{DMI Equalization Phase 2} TYPE:{Combo}
  # !BSF OPTION:{0:Disable phase2, 1:Enable phase2, 2:Auto}
  # !BSF HELP:{DMI Equalization Phase 2. (0x0): Disable phase 2, (0x1): Enable phase 2, (0x2)(Default): AUTO - Use the current default method}
  gPlatformFspPkgTokenSpaceGuid.DmiGen3EqPh2Enable          | * | 0x01 | 0x02

  # !BSF NAME:{DMI Gen3 Equalization Phase3} TYPE:{Combo}
  # !BSF OPTION:{0:Auto, 1:HwEq, 2:SwEq, 3:StaticEq, 4:BypassPhase3}
  # !BSF HELP:{DMI Gen3 Equalization Phase3. Auto(0x0)(Default): Use the current default method, HwEq(0x1): Use Adaptive Hardware Equalization, SwEq(0x2): Use Adaptive Software Equalization (Implemented in BIOS Reference Code), Static(0x3): Use the Static EQs provided in DmiGen3EndPointPreset array for Phase1 AND Phase3 (Instead of just Phase1), Disabled(0x4): Bypass Equalization Phase 3}
  gPlatformFspPkgTokenSpaceGuid.DmiGen3EqPh3Method          | * | 0x01 | 0x0

  # !BSF NAME:{Rsvd} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Disable(0x0)(Default): Normal Operation - RxCTLE adaptive behavior enabled, Enable(0x1): Override RxCTLE - Disable RxCTLE adaptive behavior to keep the configured RxCTLE peak values unmodified}
  gPlatformFspPkgTokenSpaceGuid.PegGen3Rsvd                 | * | 0x01 | 0x00

  # !BSF NAME:{Panel Power Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Control for enabling/disabling VDD force bit (Required only for early enabling of eDP panel). 0=Disable, 1(Default)=Enable}
  gPlatformFspPkgTokenSpaceGuid.PanelPowerEnable            | * | 0x01 | 0x01

  # !BSF NAME:{BdatTestType} TYPE:{Combo}
  # !BSF OPTION:{0:RMT per Rank, 1:RMT per Bit, 2:Margin2D}
  # !BSF HELP:{Indicates the type of Memory Training data to populate into the BDAT ACPI table.}
  gPlatformFspPkgTokenSpaceGuid.BdatTestType                | * | 0x1 | 0x00

  # !BSF NAME:{SaPreMemTestRsvd} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Reserved for SA Pre-Mem Test}
  gPlatformFspPkgTokenSpaceGuid.SaPreMemTestRsvd            | * | 0x62 | {0x00}

  #
  # Security Block Start
  #

  # !BSF NAME:{TotalFlashSize}  TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{Enable/Disable. 0: Disable, define default value of TotalFlashSize , 1: enable}
  #TODO: change the value
  gPlatformFspPkgTokenSpaceGuid.TotalFlashSize               | * | 0x02 | 0x0000

  # !BSF NAME:{BiosSize}  TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{Enable/Disable. 0: Disable, define default value of BiosSize , 1: enable}
  gPlatformFspPkgTokenSpaceGuid.BiosSize                     | * | 0x02 | 0x2800

  # !BSF NAME:{TxtAcheckRequest}  TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable. When Enabled, it will forcing calling TXT Acheck once.}
  gPlatformFspPkgTokenSpaceGuid.TxtAcheckRequest             | * | 0x01 | 0x0

  # !BSF NAME:{SecurityTestRsvd} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Reserved for SA Pre-Mem Test}
  gPlatformFspPkgTokenSpaceGuid.SecurityTestRsvd             | * | 0x0B | {0x00}

  #
  # Security Block End
  #

  #
  # PCH Pre-Mem Block start
  #
  # !BSF PAGE:{PCH1}
  # !BSF NAME:{Smbus dynamic power gating} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Disable or Enable Smbus dynamic power gating.}
  gPlatformFspPkgTokenSpaceGuid.SmbusDynamicPowerGating     | * | 0x01 | 0x01

  # !BSF NAME:{Disable and Lock Watch Dog Register} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Set 1 to clear WDT status, then disable and lock WDT registers.}
  gPlatformFspPkgTokenSpaceGuid.WdtDisableAndLock           | * | 0x01 | 0x00

  # !BSF NAME:{SMBUS SPD Write Disable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Set/Clear Smbus SPD Write Disable. 0: leave SPD Write Disable bit; 1: set SPD Write Disable bit. For security recommendations, SPD write disable bit must be set.}
  gPlatformFspPkgTokenSpaceGuid.SmbusSpdWriteDisable        | * | 0x01 | 0x01

  # !BSF NAME:{VC Type} TYPE:{Combo} OPTION:{0: VC0, 1: VC1}
  # !BSF HELP:{Virtual Channel Type Select: 0: VC0, 1: VC1.}
  gPlatformFspPkgTokenSpaceGuid.PchHdaVcType                | * | 0x01 | 0x00

  # !BSF NAME:{Universal Audio Architecture compliance for DSP enabled system} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Not-UAA Compliant (Intel SST driver supported only), 1: UAA Compliant (HDA Inbox driver or SST driver supported).}
  gPlatformFspPkgTokenSpaceGuid.PchHdaDspUaaCompliance      | * | 0x01 | 0x00

  # !BSF NAME:{Enable HD Audio Link} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable HD Audio Link. Muxed with SSP0/SSP1/SNDW1.}
  gPlatformFspPkgTokenSpaceGuid.PchHdaAudioLinkHdaEnable    | * | 0x01 | 0x01

  # !BSF NAME:{Enable HDA SDI lanes} TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{Enable/disable HDA SDI lanes.}^M
  gPlatformFspPkgTokenSpaceGuid.PchHdaSdiEnable            | * | 0x02 | { 0x01, 0x00}

  # !BSF NAME:{HDA Power/Clock Gating (PGD/CGD)} TYPE:{Combo}
  # !BSF OPTION:{0: POR, 1: Force Enable, 2: Force Disable}
  # !BSF HELP:{Enable/Disable HD Audio Power and Clock Gating(POR: Enable). 0: PLATFORM_POR, 1: FORCE_ENABLE, 2: FORCE_DISABLE.}
  gPlatformFspPkgTokenSpaceGuid.PchHdaTestPowerClockGating  | * | 0x01 | 0x00

  # !BSF NAME:{Enable HD Audio DMIC_N Link} TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{Enable/disable HD Audio DMIC1 link. Muxed with SNDW3.}
  gPlatformFspPkgTokenSpaceGuid.PchHdaAudioLinkDmicEnable  | * | 0x02 | { 0x01, 0x01}

  # !BSF NAME:{DMIC<N> ClkA Pin Muxing (N - DMIC number)} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Determines DMIC<N> ClkA Pin muxing. See  GPIO_*_MUXING_DMIC<N>_CLKA_*}
  # !HDR STRUCT:{UINT32}
  gPlatformFspPkgTokenSpaceGuid.PchHdaAudioLinkDmicClkAPinMux | * | 0x8 | { 0x0, 0x0 }

  # !BSF NAME:{DMIC<N> ClkB Pin Muxing} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Determines DMIC<N> ClkA Pin muxing. See GPIO_*_MUXING_DMIC<N>_CLKB_*}
  # !HDR STRUCT:{UINT32}^M
  gPlatformFspPkgTokenSpaceGuid.PchHdaAudioLinkDmicClkBPinMux | * | 0x8 | { 0x0, 0x0 }

  # !BSF NAME:{Enable HD Audio DSP} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable HD Audio DSP feature.}
  gPlatformFspPkgTokenSpaceGuid.PchHdaDspEnable             | * | 0x01 | 0x01

  # !BSF NAME:{DMIC<N> Data Pin Muxing} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Determines DMIC<N> Data Pin muxing. See GPIO_*_MUXING_DMIC<N>_DATA_*}
  # !HDR STRUCT:{UINT32}
  gPlatformFspPkgTokenSpaceGuid.PchHdaAudioLinkDmicDataPinMux | * | 0x8 | {0x00000000, 0x00000000}

  # !BSF NAME:{Enable HD Audio SSP0 Link} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFFFFFF)}
  # !BSF HELP:{Enable/disable HD Audio SSP_N/I2S link. Muxed with HDA. N-number 0-5}
  gPlatformFspPkgTokenSpaceGuid.PchHdaAudioLinkSspEnable    | * | 0x06 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable HD Audio SoundWire#N Link} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Enable/disable HD Audio SNDW#N link. Muxed with HDA.}
  gPlatformFspPkgTokenSpaceGuid.PchHdaAudioLinkSndwEnable  | * | 0x04 | {0x01, 0x00, 0x00, 0x00}

  # !BSF NAME:{iDisp-Link Frequency} TYPE:{Combo} OPTION:{4: 96MHz, 3: 48MHz}
  # !BSF HELP:{iDisp-Link Freq (PCH_HDAUDIO_LINK_FREQUENCY enum): 4: 96MHz, 3: 48MHz.}
  gPlatformFspPkgTokenSpaceGuid.PchHdaIDispLinkFrequency    | * | 0x01 | 0x04

  # !BSF NAME:{iDisp-Link T-mode} TYPE:{Combo} OPTION:{0: 2T, 2: 4T, 3: 8T, 4: 16T}
  # !BSF HELP:{iDisp-Link T-Mode (PCH_HDAUDIO_IDISP_TMODE enum): 0: 2T, 2: 4T, 3: 8T, 4: 16T}
  gPlatformFspPkgTokenSpaceGuid.PchHdaIDispLinkTmode        | * | 0x01 | 0x02

  # !BSF NAME:{iDisplay Audio Codec disconnection} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Not disconnected, enumerable, 1: Disconnected SDI, not enumerable.}
  gPlatformFspPkgTokenSpaceGuid.PchHdaIDispCodecDisconnect  | * | 0x01 | 0x00

  # !BSF NAME:{Tcc Tuning enable/disable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Tcc (Time Coordinated Computing) Tuning Enabled}
  gPlatformFspPkgTokenSpaceGuid.TccTuningEnable | * | 0x01 | 0x00

  # !BSF NAME:{Tcc Register File Base Address} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Tcc (Time Coordinated Computing) Register File Base Address}
  gPlatformFspPkgTokenSpaceGuid.TccConfigBase | * | 0x04 | 0x00000000

  # !BSF NAME:{Tcc Register File Size} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Tcc (Time Coordinated Computing) Register File Size}
  gPlatformFspPkgTokenSpaceGuid.TccConfigSize | * | 0x04 | 0x00000000

  #
  # PCH Pre-Mem Block End
  #

  #
  # ME Pre-Mem Block start
  #
  # !BSF NAME:{Force ME DID Init Status} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Test, 0: disable, 1: Success, 2: No Memory in Channels, 3: Memory Init Error, Set ME DID init stat value}
  gPlatformFspPkgTokenSpaceGuid.DidInitStat                 | * | 0x01 | 0x0

  # !BSF NAME:{CPU Replaced Polling Disable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Test, 0: disable, 1: enable, Setting this option disables CPU replacement polling loop}
  gPlatformFspPkgTokenSpaceGuid.DisableCpuReplacedPolling   | * | 0x01 | 0x0

  # !BSF NAME:{ME DID Message} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Test, 0: disable, 1: enable, Enable/Disable ME DID Message (disable will prevent the DID message from being sent)}
  gPlatformFspPkgTokenSpaceGuid.SendDidMsg                  | * | 0x01 | 0x1

  # !BSF NAME:{Check HECI message before send} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Test, 0: disable, 1: enable, Enable/Disable message check.}
  gPlatformFspPkgTokenSpaceGuid.DisableMessageCheck         | * | 0x01 | 0x0

  # !BSF NAME:{Skip MBP HOB} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Test, 0: disable, 1: enable, Enable/Disable MOB HOB.}
  gPlatformFspPkgTokenSpaceGuid.SkipMbpHob                  | * | 0x01 | 0x0

  # !BSF NAME:{HECI2 Interface Communication} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Test, 0: disable, 1: enable, Adds or Removes HECI2 Device from PCI space.}
  gPlatformFspPkgTokenSpaceGuid.HeciCommunication2          | * | 0x01 | 0x0

  # !BSF NAME:{Enable KT device} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Test, 0: disable, 1: enable, Enable or Disable KT device.}
  gPlatformFspPkgTokenSpaceGuid.KtDeviceEnable              | * | 0x01 | 0x0

  #
  # ME Pre-Mem Test Block End
  #

  # !HDR EMBED:{FSP_M_CONFIG:FspmConfig:END}
  gPlatformFspPkgTokenSpaceGuid.ReservedFspmUpd2         | * | 0x14 | {0x00}


  # Note please keep "UpdTerminator" at the end of each UPD region.
  # The tool will use this field to determine the actual end of the UPD data
  # structure.

  gPlatformFspPkgTokenSpaceGuid.UpdTerminator               | * | 0x02 | 0x55AA
