/** @file
  The Pcie Common Initialization Library

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
#include <Library/PeiServicesLib.h>
#include <Library/IoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/PcdLib.h>
#include <Library/PciSegmentLib.h>
#include <Uefi/UefiBaseType.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PostCodeLib.h>
#include <Ppi/SiPolicy.h>
#include <SaPolicyCommon.h>
#include <PcieRegs.h>
#include <Register/CpuPcieRegs.h>
#include <Register/ItbtPcieRegs.h>
#include <Library/ItbtPcieRpInitLib.h>
#include <Library/CpuRegbarAccessLib.h>
#include <Library/TimerLib.h>
#include <TcssPeiConfig.h>
#include <Library/PciExpressHelpersLib.h>
#include <Library/PcieHelperLib.h>
#include <Library/HobLib.h>
#include <TcssDataHob.h>
#include <CpuSbInfo.h>

/**
Get max PCIe link speed supported by the root port.

@param[in] RpBase    Root Port base address
@return Max link speed
**/
UINT32
CpuPcieGetMaxLinkSpeed (
  UINT64 RpBase
)
{
  return PciSegmentRead32 (RpBase + R_PCIE_LCAP) & B_PCIE_LCAP_MLS;
}

/**
This function creates Capability and Extended Capability List

@param[in] RpBase           Root Port pci segment base address
@param[in] iTbtPcieConfig    Pointer to a PCH_PCIE_CONFIG that provides the platform setting

**/
VOID
PcieInitCapabilityList(
  IN  UINT64                      RpBase,
  IN  ITBT_PCIE_CONFIG          *iTbtPcieConfig
)
{
  UINT32      Data32;
  UINT32      Data32And;
  UINT32      Data32Or;
  UINT16      Data16;
  UINT8       Data8;
  UINT16      NextCap;

  DEBUG ((DEBUG_INFO, "PcieInitCapabilityList RpBase : %x\n", RpBase));
  ///
  /// If not valid root port configuration space then return
  ///
  if (PciSegmentRead16 (RpBase + PCI_VENDOR_ID_OFFSET) == 0xFFFF){
    DEBUG((DEBUG_INFO, "PcieInitCapabilityList Invalid/Disabled RpBase : %x\n", RpBase));
    return;
  }
  DEBUG((DEBUG_INFO, "PcieInitCapabilityList RpBase : %x - %x \n", RpBase,PciSegmentRead16 (RpBase + PCI_VENDOR_ID_OFFSET)));
  ///
  /// I.Build PCI Capability linked list
  /// 0x40 - CLIST
  /// 0x80 - MID
  /// 0x90 - SVCAP
  /// 0xA0 - PMCAP
  ///
  Data8 = PciSegmentRead8 (RpBase + PCI_CAPBILITY_POINTER_OFFSET);
  PciSegmentWrite8 (RpBase + PCI_CAPBILITY_POINTER_OFFSET, Data8);

  Data16 = PciSegmentRead16 (RpBase + R_PCIE_CLIST);
  PciSegmentWrite16 (RpBase + R_PCIE_CLIST, Data16);

  Data16 = PciSegmentRead16 (RpBase + R_PCIE_MID);
  PciSegmentWrite16 (RpBase + R_PCIE_MID, Data16);

  Data16 = PciSegmentRead16 (RpBase + R_PCIE_SVCAP);
  PciSegmentWrite16 (RpBase + R_PCIE_SVCAP, Data16);

  Data16 = PciSegmentRead16 (RpBase + R_PCIE_PMCAP);
  PciSegmentWrite16 (RpBase + R_PCIE_PMCAP, Data16);

  ///
  /// II.Build PCI Extended Capability linked list
  /// 0xA30 - SPEECH (CAPID:0019h) Secondary PCI Express Extended Capability Header
  /// 0xA00 - DPCECH (CAPID:001Dh)
  /// 0x220 - ACSECH (CAPID:000Dh) ACS Extended Capability
  /// 0x150 - PTMECH (CAPID:001Fh) PTM Extended Capability Register
  /// 0x100 - AECH   (CAPID:0001h) Advanced Error Reporting Capability
  ///

  /*
  a. NEXT_CAP = 0h
  */
  NextCap = V_PCIE_EXCAP_NCO_LISTEND;

  /*
  b. If the RP is GEN3 capable (by fuse and BIOS policy), enable Secondary PCI Express Extended Capability
  1. Set Next Capability Offset,0xA30[31:20] = NEXT_CAP
  2. Set Capability Version, 0xA30[19:16] = 1h
  3. Set Capability ID,  0xA30[15:0] = 0019h
  4. NEXT_CAP = 0xA30
  ELSE, set 0xA30[31:0] = 0
  */
  Data32 = 0;
  if (CpuPcieGetMaxLinkSpeed(RpBase) >= V_PCIE_LCAP_MLS_GEN3) {
    Data32 = (V_PCIE_EX_CV << N_PCIE_EXCAP_CV) | V_PCIE_EX_SPE_CID;
    Data32 |= (NextCap << N_PCIE_EXCAP_NCO);
    NextCap = R_PCIE_SPEECH;
  }
  PciSegmentWrite32 (RpBase + R_PCIE_SPEECH, Data32);

  /*
  c. If Downstream Port Containment is enabled, then
  1. Set Next Capability Offset, 0xA00[31:20] = NEXT_CAP
  2. Set Capability Version, 0xA00[19:16] = 1h
  3. Set Capability ID, 0xA00[15:0] = 01Dh
  4. NEXT_CAP = 0xA00
  ELSE, set 0xA00 [31:0] = 0
  */
  Data32 = 0;
  if (iTbtPcieConfig->DpcEnabled == TRUE) {
    Data32 = (V_PCIE_EX_CV << N_PCIE_EXCAP_CV) | V_PCIE_EX_DPC_CID;
    Data32 |= (NextCap << N_PCIE_EXCAP_NCO);
    NextCap = R_PCIE_DPCECH;
  }
  PciSegmentWrite32 (RpBase + R_PCIE_DPCECH, Data32);

  /*
  d. If support ACS
  1. Set Next Capability Offset,  0x220[31:20] = NEXT_CAP
  2. Set Capability Version, 0x220[19:16] = 1h
  3. Set Capability ID, 0x220[15:0] = 000Dh
  4. Read and write back to  0x220
  5. NEXT_CAP = 0x220
  ELSE, set 0x220 [31:0] = 0, and read and write back to  144h
  */
  Data32 = 0;
  if (iTbtPcieConfig->AcsEnabled == TRUE) {
    Data32 = (V_PCIE_EX_CV << N_PCIE_EXCAP_CV) | V_PCIE_EX_ACS_CID;
    Data32 |= (NextCap << N_PCIE_EXCAP_NCO);
    NextCap = R_PCIE_ACSECH;
  }
  PciSegmentWrite32 (RpBase + R_PCIE_ACSECH, Data32);

  /*
  e. If support PTM
  1. Set Next Capability Offset,  150h[31:20] = NEXT_CAP
  2. Set Capability Version, 140h[19:16] = 1h
  3. Set Capability ID, 140h[15:0] = 001Fh
  4. Read and write back to  144h
  5. NEXT_CAP = 140h
  ELSE, set  150h [31:0] = 0
  In both cases: read  154h, set BIT1 and write it back
  */
  Data32 = 0;
  if (iTbtPcieConfig->PtmEnabled == TRUE) {
    Data32 = (V_PCIE_EX_CV << N_PCIE_EXCAP_CV) | V_PCIE_EX_PTM_CID;
    Data32 |= (NextCap << N_PCIE_EXCAP_NCO);
    NextCap = R_PCIE_PTMECH;
  }
  PciSegmentWrite32 (RpBase + R_PCIE_PTMECH, Data32);

  /*
  g. If support Advanced Error Reporting
  1. Set Next Capability Offset, 100h[31:20] = NEXT_CAP
  2. Set Capability Version, 100h[19:16] = 1h
  3. Set Capability ID, 100h[15:0] = 0001h
  ELSE
  1. Set Next Capability Offset, 100h[31:20] = NEXT_CAP
  2. Set Capability Version, 100h[19:16]  = 0h
  3. Set Capability ID, 100h[15:10]  = 0000h
  */
  Data32 = 0;
  if (iTbtPcieConfig->AdvancedErrorReporting) {
    Data32 = (V_PCIE_EX_CV << N_PCIE_EXCAP_CV) | V_PCIE_EX_AEC_CID;
  }
  Data32 |= (NextCap << N_PCIE_EXCAP_NCO);
  PciSegmentWrite32 (RpBase + R_PCIE_AECH, Data32);

  ///
  /// III. Initalize Capability Registers
  ///

  ///
  /// PCI Express capabilities
  /// Slot Implemented R_PCIE_XCAP 0x42[8]  = 1
  /// Max Payload R_PCIE_DCAP 0x44[0:7] = 0 (128B)
  ///
  PciSegmentOr16 (RpBase + R_PCIE_XCAP, B_PCIE_XCAP_SI);
  PciSegmentAnd16 (RpBase + R_PCIE_DCAP, (UINT16) ~ B_PCIE_DCAP_MPS);
  ///
  /// Aspm Support R_PCIE_LCAP 0x4C[11:10] = 0x2
  /// R_PCIE_LCAP.EL1 0x4C [17:15] = 0x4
  ///
  Data32And = (UINT32)~ (B_PCIE_LCAP_APMS_MASK | B_PCIE_LCAP_EL1_MASK);
  Data32Or = (UINT32) (0x2 << B_PCIE_LCAP_APMS_OFFSET) | (0x4 << B_PCIE_LCAP_EL1_OFFSET) ;
  PciSegmentAndThenOr32(RpBase + R_PCIE_LCAP, Data32And, Data32Or);
  ///
  /// Physical Slot Number R_PCIE_SLCAP 0x54 [31:19] ,SLS/SLV[16:7],HotplugCapable HPC[6] ,HPS[5]
  /// @Todo Slot power SLS/SLV[16:7]
  ///
  Data32 = PciSegmentRead32 (RpBase + R_PCIE_SLCAP);
  Data32 |= (iTbtPcieConfig->SlotNumber << 19);
  Data32 |= (B_PCIE_SLCAP_HPC | B_PCIE_SLCAP_HPS);
  PciSegmentWrite32 (RpBase + R_PCIE_SLCAP, Data32);

  ///
  ///  No Soft Reset R_PCIE_PMCS 0xA4[3] = 0
  ///
  PciSegmentAnd32 (RpBase + R_PCIE_PMCS, ~((UINT32)B_PCIE_PMCS_NSR));

  ///
  /// Set DPC capabilities
  ///
  if (iTbtPcieConfig->DpcEnabled == TRUE) {
    Data16 = PciSegmentRead16 (RpBase + R_PCIE_DPCCAPR);
    Data16 &= BIT5;
    if (iTbtPcieConfig->RpDpcExtensionsEnabled == TRUE) {
      Data16 |= BIT5;
    }
  }
  else {
    Data16 = 0;
  }
  PciSegmentWrite16 (RpBase + R_PCIE_DPCCAPR, Data16);

  ///
  /// Init ACS capabilities & PTM capabilities
  /// Set ACS Upstream Forwarding (U)
  ///
  Data16 = PciSegmentRead16 (RpBase + R_PCIE_ACSCAPR);
  Data16 |= B_PCIE_ACSCAPR_U;
  PciSegmentWrite16(RpBase + R_PCIE_ACSCAPR, Data16);

  if (iTbtPcieConfig->PtmEnabled) {
    Data32 = PciSegmentRead32 (RpBase + R_PCIE_PTMCAPR);
    PciSegmentWrite32 (RpBase + R_PCIE_PTMCAPR, (Data32 | BIT1));
  }

  ///
  /// 0xF0  10:8  IOSF_Max_Payload_Size (IMPS) 111b
  ///
  Data32And = (UINT32) ~ B_PCIE_IPCS_IMPS_MASK;
  Data32Or = (0x07 << B_PCIE_IPCS_IMPS_OFFSET);
  PciSegmentAndThenOr32(RpBase + R_PCIE_IPCS, Data32And, Data32Or);

  ///
  /// 0xD0  24  Upstream Posted Split Disable (UPSD): 0
  /// 0xD0  2:0  Upstream Posted Request Size (UPRS): 111b
  /// 0xD0  6:4  Upstream Non-Posted Request Size (UNRS):111b
  /// 0xD0  13:12 Upstream Non-Posted Request Delay (UNRD):01b
  ///
  Data32And = (UINT32)~(B_PCIE_CCFG_UPSD | B_PCIE_CCFG_UPRS_MASK | B_PCIE_CCFG_UNRS_MASK | B_PCIE_CCFG_UNRD_MASK);
  Data32Or = (0x07 | (0x07 << B_PCIE_CCFG_UNRS_OFFSET) | (1 << B_PCIE_CCFG_UNRD_OFFSET));
  PciSegmentAndThenOr32(RpBase + R_PCIE_CCFG, Data32And, Data32Or);

  ///
  /// Link Speed Training Policy (LSTP) 0xD4 6 1
  /// EOI Forwarding Disable (EOIFD):  0xD4 1 1
  /// Poisoned TLP Non-Fatal Advisory Error Enable (PTNFAE): 0xD4 12 1
  ///
  Data32Or = B_PCIE_MPC2_LSTP | B_PCIE_MPC2_PTNFAE | B_PCIE_MPC2_EOIFD;
  PciSegmentOr32(RpBase + R_PCIE_MPC2, Data32Or);

  ///
  /// Common Clock Exit Latency (CCEL): 0xD8 17:15 0x4
  ///
  Data32And = (UINT32)~(B_PCIE_MPC_CCEL_MASK);
  Data32Or = 0x4 << B_PCIE_MPC_CCEL_OFFSET;
  PciSegmentAndThenOr32(RpBase + R_PCIE_MPC, Data32And, Data32Or);


  DEBUG((DEBUG_INFO, "PcieInitCapabilityList End\n"));

}

/**
This function Initalizes the PCI PowerManagemnet Registres
SIP15 PCI Express Root Port BIOS Requirement Rev 0.9

@param[in] RootPortId       Root Port pci segment base address
**/

VOID
PcieMiscInit(
IN  UINT8                      RootPortId
)
{
  UINT32  Data32And;
  UINT32  Data32Or;

  ///
  /// Gen 2 x1 (G2X1) 0x300  23:20 0xB
  /// Gen 2 x2 (G2X2) 0x300  19:16 0x7
  /// Gen 2 x4 (G2X4) 0x300  15:12 0x5
  /// Gen 1 x1 (G1X1) 0x300  11:8  0xF
  /// Gen 1 x2 (G1X2) 0x300  7:4   0xA
  /// Gen 1 x4 (G1X4) 0x300  3:0   0x9
  ///
  Data32And = (UINT32)~ (B_PCIE_PCIERTP1_G2X1_MASK | B_PCIE_PCIERTP1_G2X2_MASK | B_PCIE_PCIERTP1_G2X4_MASK |
                         B_PCIE_PCIERTP1_G1X1_MASK | B_PCIE_PCIERTP1_G1X2_MASK | B_PCIE_PCIERTP1_G1X4_MASK);
  Data32Or = (0xB << B_PCIE_PCIERTP1_G2X1_OFFSET) | (0x7 << B_PCIE_PCIERTP1_G2X2_OFFSET) | (0x5 << B_PCIE_PCIERTP1_G2X4_OFFSET) |
             (0xF << B_PCIE_PCIERTP1_G1X1_OFFSET) | (0xA << B_PCIE_PCIERTP1_G1X2_OFFSET) | (0x9);
  CpuRegbarAndThenOr32(RootPortId, R_PCIE_PCIERTP1, Data32And, Data32Or);

  ///
  /// Gen 3 x1 (G3X1) 0x304  11:8   0xC
  /// Gen 3 x2 (G3X2) 0x304  7:4    0x9
  /// Gen 3 x4 (G3X4) 0x304  3:0    0x7
  Data32And = (UINT32)~(B_PCIE_PCIERTP2_G3X1_MASK | B_PCIE_PCIERTP2_G3X2_MASK | B_PCIE_PCIERTP2_G3X4_MASK);
  Data32Or = (0xC << B_PCIE_PCIERTP2_G3X1_OFFSET) | (0x9 << B_PCIE_PCIERTP2_G3X2_OFFSET) | (0x7 << B_PCIE_PCIERTP2_G3X4_OFFSET);
  CpuRegbarAndThenOr32(RootPortId, R_PCIE_PCIERTP2, Data32And, Data32Or);

  ///
  ///  Completion Ordering Mode(COM)0xEC1  13 1
  ///
  Data32Or = B_PCIE_DC_COM;
  CpuRegbarOr32(RootPortId, R_PCIE_DC, Data32Or);

  ///
  /// DMA Flush Zero Length Read Address (DMAFZLRA) 0x584 31:0 0xFEE80000h
  ///
  Data32And = (UINT32)~(B_PCIE_IOMMUCTL2_DMAFZLRA_MASK);
  Data32Or = 0xFEE80000;
  CpuRegbarAndThenOr32(RootPortId, R_PCIE_IOMMUCTL2, Data32And, Data32Or);

  ///
  /// Hit2Pend Disable(H2PDIS) 0xC0C 7 1
  ///
  Data32Or = B_PCIE_IOMMUMISCDIS_H2PDIS;
  CpuRegbarOr32(RootPortId, R_PCIE_IOMMUMISCDIS, Data32Or);

  ///
  /// Chain Bit Generation Mode(CBGM) 0x6CC 21 1
  ///
  Data32Or = B_PCIE_ACRG3_CBGM;
  CpuRegbarOr32(RootPortId, R_PCIE_ACRG3, Data32Or);

  ///
  /// Section 3.23 Coalescing
  ///

  ///  Posted Write Chaining Enable (PWCE):0x594  0 1
  ///  Completion Chaining Enable (DDCE):0x594  1 1
  ///  Chain Timer (CT):0x594  9:02 0x8
  ///  Chain Timer Enable (CTE):0x594  10 1
  ///  Relaxed Order Attribute Override Policy (ROAOP):0x594  11 0x0
  ///  Posted Chain Limit Mode (PCLM):0x594  14:13 0x2
  ///  Non-Posted Chain Limit Mode (NPCLM):0x594  16:15 0x2

  Data32And = ~(UINT32)(B_PCIE_COCTL_PCLM | B_PCIE_COCTL_NPCLM_MASK | B_PCIE_COCTL_CT_MASK | B_PCIE_COCTL_ROAOP);
  Data32Or = B_PCIE_COCTL_PWCE | B_PCIE_COCTL_DDCE | 0x8 << B_PCIE_COCTL_CT_OFFSET |
    B_PCIE_COCTL_CTE | (0x2 << B_PCIE_COCTL_PCLM_OFFSET) | (0x2 << B_PCIE_COCTL_NPCLM_OFFSET);
  CpuRegbarAndThenOr32(RootPortId, R_PCIE_COCTL, Data32And, Data32Or);

  ///
  /// Chain Bit Generation Mode (CBGM) 0x6CC 21 1
  ///
  CpuRegbarOr32(RootPortId, R_PCIE_ACRG3, B_PCIE_ACRG3_CBGM);

  ///
  /// Section 3.28  LTR Subtraction
  ///

  ///  LTR Non-Snoop Latency Subtraction Enable (LTRNSLSUBEN) : 0xC54  31 1
  ///  LTR Non-Snoop Latency Scale Subtraction Value (LTRNSLSSUBV):0xC54  28:26 0x2
  ///  LTR Non-Snoop Latency Subtraction Value (LTRNSLSUBV) : 0xC54  25 : 16 0x5
  ///  LTR Snoop Latency Subtraction Enable (LTRSLSUBEN) : 0xC54  15 1
  ///  LTR Snoop Latency Scale Subtraction Value (LTRSLSSUBV) : 0xC54  12 : 10 0x2
  ///  LTR Snoop Latency Subtraction Value (LTRSLSUBV) 0xC54  9:00 0x5

  Data32And = ~(UINT32) (B_PCIE_CLTRSUB_LTRNSLSSUBV_MASK | B_PCIE_CLTRSUB_LTRNSLSUBV_MASK |
                         B_PCIE_CLTRSUB_LTRSLSSUBV_MASK | B_PCIE_CLTRSUB_LTRSLSUBV_MASK);
  Data32Or = (B_PCIE_CLTRSUB_LTRNSLSUBEN | B_PCIE_CLTRSUB_LTRSLSUBEN | 0x2 << B_PCIE_CLTRSUB_LTRNSLSSUBV_OFFSET |
             0x5 << B_PCIE_CLTRSUB_LTRNSLSUBV_OFFSET | 0x2 << B_PCIE_CLTRSUB_LTRSLSSUBV_OFFSET | 0x5);

  CpuRegbarAndThenOr32(RootPortId, R_PCIE_CLTRSUB, Data32And, Data32Or);

}

/**
This function Initalizes the PCI PowerManagemnet Registres
SIP15 PCI Express Root Port BIOS Requirement Rev 0.9

@param[in] RootPortId       Root Port pci segment base address
**/

VOID
PciePtmInit(
IN  UINT8                      RootPortId
)
{
  UINT32  Data32And;
  UINT32  Data32Or;

  ///
  /// Periodic Local TSC Link Fetch Frequency (PLTLFF):0x3B0  20:18  0x1h
  /// PTM Request Number Of Periodic ACK DLLP(PTMRNOPAD) : 0x3B0 5:4 0x1h
  /// PTM Request Periodic ACK Enable (PTMRPAE) : 0x3B0 6 0x1
  ///
  Data32And = (UINT32)~(B_PCIE_PTMECFG_PLTLFF_MASK | B_PCIE_PTMECFG_PTMRNOPAD_MASK);
  Data32Or = (0x1 << B_PCIE_PTMECFG_PLTLFF_OFFSET) | (0x1 << B_PCIE_PTMECFG_PTMRNOPAD_OFFSET) | B_PCIE_PTMECFG_PTMRPAE;
  CpuRegbarAndThenOr32 (RootPortId, R_PCIE_PTMECFG, Data32And, Data32Or);

  ///
  /// PTM Enable (PTME) 0x158 0 1
  /// Root Select (RS) 0x158 1 1
  ///
  Data32Or = B_PCIE_PTMCTLR_PTME | B_PCIE_PTMCTLR_RS;
  CpuRegbarOr32(RootPortId, R_PCIE_PTMCTLR, Data32Or);
  ///
  /// PTM Root Capable (PTMRC) 0x154 2
  /// PTM Responder Capable (PTMRSPC) 0x154 1
  ///
  Data32Or = B_PCIE_PTMCAPR_PTMRC | B_PCIE_PTMCAPR_PTMRSPC;
  CpuRegbarOr32(RootPortId, R_PCIE_PTMCAPR, Data32Or);

  ///
  /// B_PCIE_ACRG3_PPTMTMUCF  0x6cc 17:14 0x2
  /// B_PCIE_ACRG3_PPTMTMUCFE 0x6cc 18    0x1
  ///
  Data32And = (UINT32)~(B_PCIE_ACRG3_PPTMTMUCF_MASK);
  Data32Or = (0x2 << B_PCIE_ACRG3_PPTMTMUCF_OFFSET) | B_PCIE_ACRG3_PPTMTMUCFE;
  CpuRegbarAndThenOr32(RootPortId, R_PCIE_ACRG3, Data32And, Data32Or);
}
/**
This function Initalizes the PCI PowerManagemnet Registres
SIP15 PCI Express Root Port BIOS Requirement Rev 0.9

@param[in] RootPortId       Root Port pci segment base address
**/

VOID
PciePowerManagementInit(
  IN  UINT8                      RootPortId,
  IN  ITBT_PCIE_CONFIG          *iTbtPcieConfig
)
{
  UINT32  Data32And;
  UINT32  Data32Or;
  UINT8   Data8And;
  UINT8   Data8Or;

  ///
  /// Section 3.1.2 ASPM
  ///

  ///
  /// Gen3 Active State L0s Preparation Latency (G3ASL0SPL) 0x478  31:24 0x28
  ///
  Data32And = ~ 0xFF000000;
  Data32Or  = 0x28;
  CpuRegbarAndThenOr32(RootPortId, 0x478, Data32And, Data32Or);

  ///
  /// Gen2 Active State L0s Preparation Latency (G2ASL0SPL) 0x318  31:24 0x14
  /// Gen1 Active State L0s Preparation Latency (G1ASL0SPL) 0x318  23:16 0x14
  ///
  Data32And = ~ (UINT32) (B_PCIE_PCIEL0SC_G2ASL0SPL_MASK | B_PCIE_PCIEL0SC_G1ASL0SPL_MASK);
  Data32Or  = (0x14 << B_PCIE_PCIEL0SC_G2ASL0SPL_OFFSET) | (0x14 << B_PCIE_PCIEL0SC_G1ASL0SPL_OFFSET);
  CpuRegbarAndThenOr32 (RootPortId, R_PCIE_PCIEL0SC, Data32And, Data32Or);

  ///
  /// Section 3.1.3 Clock Gating
  ///

  ///
  /// Dynamic Clock Gating Enable on ISM Active Enable  0xD0  15 1
  ///
  Data32Or  = B_PCIE_CCFG_DCGEISMA;
  CpuRegbarOr32 (RootPortId, R_PCIE_CCFG, Data32Or);

  ///
  /// Partition/Trunk Oscillator Clock Gate Enable (PTOCGE): 0xE1  6 1
  /// PCIe Link CLKREQ Enable(PCIELCLKREQEN) 0xE1  5 1
  /// PCIe Backbone CLKREQ Enable(PCIEBBCLKREQEN) 0xE1  4 1
  /// Shared Resource Dynamic Backbone Clock Gate Enable(SRDBCGEN) 0xE1  2 1
  /// Root Port Dynamic Link Clock Gate Enable(RPDLCGEN) 0xE1  1 1
  /// Root Port Dynamic Backbone Clock Gate Enable (RPDBCGEN) 0xE1  0 1
  /// Root Port Static Clock Gate Enable (RPSCGEN) 0xE1  7 0
  ///
  Data8And = (UINT8) ~ (BIT7);
  Data8Or = (UINT8)(B_PCIE_RPDCGEN_PTOCGE | B_PCIE_RPDCGEN_LCLKREQEN | B_PCIE_RPDCGEN_BBCLKREQEN | B_PCIE_RPDCGEN_SRDBCGEN | B_PCIE_RPDCGEN_RPDLCGEN | B_PCIE_RPDCGEN_RPDBCGEN);
  CpuRegbarAndThenOr8(RootPortId, R_PCIE_RPDCGEN, Data8And, Data8Or);

  ///
  /// Sideband Endpoint Oscillator / Side Clock Gating Enable (SEOSCGE) 0xE2  4 1 - (PTOTOP) 0xE2 6 1
  /// MDLSWPR= 0
  ///
  Data8And = (UINT8)~ B_PCIE_RPPGEN_MDLSWPR;
  Data8Or = (B_PCIE_RPPGEN_SEOSCGE | B_PCIE_RPPGEN_PTOTOP);
  CpuRegbarAndThenOr8(RootPortId, R_PCIE_RPPGEN, Data8And, Data8Or);
  ///
  /// Side Clock Partition/Trunk Clock Gating Enable (SCPTCGE) 0xF7  6 1
  /// IOSF Sideband Interface Idle Counter (SIID):0xF7 3:2 0
  ///
  Data8And = (UINT8) ~ B_PCIE_IOSFSBCS_SIID_MASK;
  Data8Or = B_PCIE_IOSFSBCS_SCPTCGE;
  CpuRegbarAndThenOr8(RootPortId, R_PCIE_IOSFSBCS, Data8And, Data8Or);

  ///
  /// B_PCIE_PCIEDBG_CTONFAE 0x324 14 1
  /// B_PCIE_PCIEDBG_LDSWQRP 0x324 13 0
  /// B_PCIE_PCIEDBG_SPCE    0x324 5  1
  /// B_PCIE_PCIEDBG_LGCLKSQEXITDBTIMERS 0x324 25:24 00
  ///
  Data32And = ~(UINT32) (B_PCIE_PCIEDBG_LDSWQRP | B_PCIE_PCIEDBG_LGCLKSQEXITDBTIMERS_MASK);
  Data32Or  = B_PCIE_PCIEDBG_CTONFAE | B_PCIE_PCIEDBG_SPCE;
  CpuRegbarAndThenOr32(RootPortId, R_PCIE_PCIEDBG, Data32And, Data32Or);

  ///
  /// Low Bandwidth Squelch Settling Timer Enable(LBWSSTE) 0x320  30  1
  /// Reset Link Layer In GEN3 Recovery(RLLG3R) 0x320  27:0
  /// Completion Relaxed Ordering Attribute Override Value(CROAOV) 0x320  24:1
  /// Completion Relaxed Ordering Attribute Override Enable(CROAOE) 0x320  23:1
  /// B_PCIE_PCIECFG2_PMET 0x320  21:20  01
  ///
  Data32And = ~(UINT32) (B_PCIE_PCIECFG2_PMET_MASK | B_PCIE_PCIECFG2_RLLG3R);
  Data32Or = (B_PCIE_PCIECFG2_LBWSSTE | B_PCIE_PCIECFG2_CROAOV | B_PCIE_PCIECFG2_CROAOE | 0x1 << B_PCIE_PCIECFG2_PMET_OFFSET);
  CpuRegbarAndThenOr32(RootPortId, R_PCIE_PCIECFG2, Data32And, Data32Or);

  ///
  /// Section 3.1.5 OBFF and Latency Tolerance Reporting
  ///

  ///
  /// Optimized Buffer Flush/Fill Supported (OBFFS) 0x64  19:18 10b
  /// LTR Mechanism Supported (LTRMS) 0x64  11 1
  ///
  Data32And = ~ (UINT32)(B_PCIE_DCAP2_OBFFS_MASK | B_PCIE_DCAP2_LTRMS);
  Data32Or  = (0x2 << B_PCIE_DCAP2_OBFFS_OFFSET) | B_PCIE_DCAP2_LTRMS;
  if (iTbtPcieConfig->LtrEnable) {
    Data32Or |= B_PCIE_DCAP2_LTRMS;
  }
  CpuRegbarAndThenOr32 (RootPortId, R_PCIE_DCAP2, Data32And, Data32Or);

  if (iTbtPcieConfig->LtrEnable) {
    Data8Or = 0;
    if (iTbtPcieConfig->SnoopLatencyOverrideMode) {
      ///
      /// LTR Snoop Override Enable (LTRSOVREN) 404  0 1
      ///
      Data8Or   = B_PCIE_LTROVR2_LTRSOVREN;
      Data32And = B_PCIE_LTROVR_LTRSROVR | B_PCIE_LTROVR_LTRSLSOVRV_MASK | B_PCIE_LTROVR_LTRSLOVRV_MASK;
      Data32Or  = ((iTbtPcieConfig->SnoopLatencyOverrideMultiplier << B_PCIE_LTROVR_LTRSLSOVRV_OFFSET) & B_PCIE_LTROVR_LTRSLSOVRV_MASK) |
                  (iTbtPcieConfig->SnoopLatencyOverrideValue & B_PCIE_LTROVR_LTRSLOVRV_MASK) | B_PCIE_LTROVR_LTRSROVR;
    }

    if (iTbtPcieConfig->NonSnoopLatencyOverrideMode) {
      ///
      /// LTR Non-Snoop Override Enable (LTRNSOVREN) x404  1 1
      ///
      Data8Or   |= B_PCIE_LTROVR2_LTRNSOVREN;
      Data32And |= B_PCIE_LTROVR_LTRNSROVR | B_PCIE_LTROVR_LTRNSLSOVRV_MASK | B_PCIE_LTROVR_LTRNSLOVRV_MASK;
      Data32Or  |= B_PCIE_LTROVR_LTRNSROVR | ((iTbtPcieConfig->NonSnoopLatencyOverrideMultiplier << B_PCIE_LTROVR_LTRNSLSOVRV_OFFSET) & B_PCIE_LTROVR_LTRNSLSOVRV_MASK) |
                   ((iTbtPcieConfig->NonSnoopLatencyOverrideValue << B_PCIE_LTROVR_LTRNSLOVRV_OFFSET) & B_PCIE_LTROVR_LTRNSLOVRV_MASK) | B_PCIE_LTROVR_LTRNSROVR;
    }

    if (iTbtPcieConfig->ForceLtrOverride) {
      Data8Or |= B_PCIE_LTROVR2_LTROVRPLCY;
    }

    if (iTbtPcieConfig->LtrConfigLock) {
      Data8Or |= B_PCIE_LTROVR2_LTRCFGLOCK;
    }
    CpuRegbarAndThenOr32(RootPortId, R_PCIE_LTROVR, Data32And, Data32Or);
    DEBUG((DEBUG_INFO, " R_PCIE_LTROVR : %x\n", CpuRegbarRead32( RootPortId, R_PCIE_LTROVR)));
    ///
    /// LTR Non-Snoop Override Enable (LTRNSOVREN) x404  1 1 404  3 0
    /// LTR Snoop Override Enable (LTRSOVREN) 404  0 1
    ///
    CpuRegbarOr8(RootPortId, R_PCIE_LTROVR2, Data8Or);
    DEBUG((DEBUG_INFO, " R_PCIE_LTROVR2 : %x\n", CpuRegbarRead8( RootPortId, R_PCIE_LTROVR2)));
  }

  ///
  /// Section 3.1.6 PLL Shutdown
  ///

  ///
  /// PCI Express GEN2 PLL Off Enable (PXPG2PLLOFFEN) 0xF5  0 1
  /// PCI Express GEN3 PLL Off Enable (PXPG3PLLOFFEN) 0xF5  1 1
  /// Transmit Datapath Flush Timer (TDFT) 0xF5 7:6 00
  /// Transmit Configuration Change Wait Time(TXCFGCHGWAIT) 0xF5 5:4 00
  ///
  Data8And = (UINT8)~(B_PCIE_PHYCTL2_TXCFGCHGWAIT_MASK | B_PCIE_PHYCTL2_TDFT_MASK);
  Data8Or = (B_PCIE_PHYCTL2_PXPG3PLLOFFEN | B_PCIE_PHYCTL2_PXPG2PLLOFFEN);
  CpuRegbarAndThenOr8(RootPortId, R_PCIE_PHYCTL2, Data8And, Data8Or);

  ///
  /// Section 3.1.8  L1 Substate
  ///

  ///
  /// L1PM Substates Supported (L1PSS) 0x204  4 0
  /// ASPM L1.1 Supported (AL11S) 0x204  3 0
  /// ASPM L1.2 Supported (AL12S) 0x204  2 0
  /// PCI-PM L1.1 Supported (PPL11S) 0x204  1 0
  /// PCI-PM L1.2 Supported (PPL12S) 0x204  0 0
  ///
  Data32And = ~(UINT32) (BIT0 | BIT1 | BIT2 | BIT3 | BIT4);
  Data32Or = 0;
  CpuRegbarAndThenOr32 (RootPortId, 0x204, Data32And, Data32Or);

  ///
  /// PCIEALC.RTD3PDSP
  ///
  CpuRegbarOr32 (RootPortId, R_PCIE_PCIEALC, B_PCIE_PCIEALC_RTD3PDSP);

  return;
}

/**
This function Initalizes the PCI PowerManagemnet Registres 3.1.10 Power Gating
SIP15 PCI Express Root Port BIOS Requirement Rev 0.9

@param[in] RootPortId       Root Port pci segment base address

**/
VOID
PciePowerGatingRegisterInit(
  IN  UINT8                      RootPortId
)
{
  UINT32  Data32And;
  UINT32  Data32Or;
  UINT8   Data8And;
  UINT8   Data8Or;

  ///
  /// Wake PLL On Detect mod-PHY Power Gating Exit Policy(WPDMPGEP) : 0xE8  17 1
  ///
  CpuRegbarOr32 (RootPortId, R_PCIE_PWRCTL, B_PCIE_PWRCTL_WPDMPGEP);

  ///
  /// Function Disable PHY Power Gating Enable (FDPPGE) :0x420  31 1
  /// L1 Full Squelch OFF Enable (L1FSOE): 420 0 0
  /// Detect and L23_Rdy State PHY Lane Power Gating Enable (DLSULPPGE): 420 30 1
  /// Detect, L23_Rdy State, Un - Configured Lane and Down - Configured Lane Squelch Disable(DLSULDLSD) :420 29 0
  ///
  Data32And = ~(UINT32)(B_PCIE_PCIEPMECTL_L1FSOE | B_PCIE_PCIEPMECTL_DLSULDLSD);
  Data32Or =  B_PCIE_PCIEPMECTL_FDPPGE | B_PCIE_PCIEPMECTL_DLSULPPGE;
  CpuRegbarAndThenOr32(RootPortId, R_PCIE_PCIEPMECTL, Data32And, Data32Or);

  ///
  /// PHY Common Lane Power Gating Enable (PHYCLPGE) : 0x424   11 1
  /// Function Disable Controller Power Gating Enable (FDCPGE) : 0x424   8 1
  /// Detect State Controller Power Gating Enable (DETSCPGE) : 0x424  7 1
  /// L23_Rdy State Controller Power Gating Enable (L23RDYSCPGE) : 0x424  6 1
  /// Disabled State Controller Power Gating Enable   (DISSCPGE) : 0x424  5 1
  /// L1 State Controller Power Gating Enable (L1SCPGE) : 0x424  4 1
  ///
  Data32Or = (B_PCIE_PCIEPMECTL2_PHYCLPGE | B_PCIE_PCIEPMECTL2_FDCPGE | B_PCIE_PCIEPMECTL2_DETSCPGE |
  B_PCIE_PCIEPMECTL2_L23RDYSCPGE | B_PCIE_PCIEPMECTL2_DISSCPGE | B_PCIE_PCIEPMECTL2_L1SCPGE);
  CpuRegbarOr32(RootPortId, R_PCIE_PCIEPMECTL2, Data32Or);

  ///
  /// Hardware Autonomous Enable (HAE):  0x428  5 0
  /// Sleep Enable (SE): 0x428  1 0
  /// PMC Request Enable (PMCRE):0x428  0 1
  ///
  Data8And = (UINT8) ~(B_PCIE_PCE_HAE | B_PCIE_PCE_SE);
  Data8Or = B_PCIE_PCE_PMCRE_OFFSET;
  CpuRegbarAndThenOr8(RootPortId, R_PCIE_PCE, Data8And, Data8Or);

  ///
  /// Bank Enable Pulse Width (BEPW) 0x5F0  3:0 "0101"
  /// Restore Enable Pulse Width (REPW) 0x5F0  7:4 "0001"
  /// Entry and Exit Hysteresis (EEH) 0x5F0  9:8 "10"
  ///
  Data32And = ~ (UINT32) (B_PCIE_HWSNR_EEH_MASK | B_PCIE_HWSNR_REPW_MASK | B_PCIE_HWSNR_BEPW_MASK);
  Data32Or = ((0x02 << B_PCIE_HWSNR_EEH_OFFSET) | (0x01 << B_PCIE_HWSNR_REPW_OFFSET) | 0x05 );
  CpuRegbarAndThenOr32(RootPortId, R_PCIE_HWSNR, Data32And, Data32Or);

  ///
  /// PM_REQ Block Response Time (PMREQBLKRSPT) 0x5F4  2:0 "101"
  ///
  Data32And = ~ (UINT32) B_PCIE_PGCTRL_PMREQBLKRSPT_MASK;
  Data32Or = 0x05 ;
  CpuRegbarAndThenOr32(RootPortId, R_PCIE_PGCTRL, Data32And, Data32Or);

  ///
  /// PM_REQ Block and Power Gate Response Time (PMREQBLKPGRSPT) 0x5BC  7:5 "101"
  /// PM_REQ_Clock Wake Control(PMREQCWC).0x5BC 18:16  "010"
  ///
  Data32And = ~(UINT32) (B_PCIE_ADVMCTRL_PMREQCWC_MASK | B_PCIE_ADVMCTRL_PMREQBLKPGRSPT_MASK);
  Data32Or = ((0x02 << B_PCIE_ADVMCTRL_PMREQCWC_OFFSET) | (0x5 << B_PCIE_ADVMCTRL_PMREQBLKPGRSPT_OFFSET));
  CpuRegbarAndThenOr32(RootPortId, R_PCIE_ADVMCTRL, Data32And, Data32Or);

  ///
  /// L1 Power Gating LTR Enable (L1PGLTREN) 0x5C0  0 1
  /// L1 Power Gating LTR Threshold Latency Scale Value(L1PGLTRTLSV) 0x5C0 31:29 0x2
  /// L1 Power Gating LTR Threshold Latency Value  (L1PGLTRTLV) 0x5C0 25:16 0x32
  ///
  Data32And = ~(UINT32)(B_PCIE_PGTHRES_L1PGLTRTLSV_MASK | B_PCIE_PGTHRES_L1PGLTRTLV_MASK);
  Data32Or = (B_PCIE_PGTHRES_L1PGLTREN | 0x2 << B_PCIE_PGTHRES_L1PGLTRTLSV_OFFSET | 0x32 << B_PCIE_PGTHRES_L1PGLTRTLV_OFFSET);
  CpuRegbarAndThenOr32(RootPortId, R_PCIE_PGTHRES, Data32And, Data32Or);

  return;
}

/**
This function Initalizes the PCI PowerManagemnet Registres 3.1.12 Dynamic Link Throttling
SIP15 PCI Express Root Port BIOS Requirement Rev 0.9

@param[in] RootPortId       Root Port pci segment base address

**/
VOID
PcieDynamicLinkThrottlingInit(
  IN  UINT8                      RootPortId
)
{
  UINT32  Data32And;
  UINT32  Data32Or;
  ///
  /// Throttle Period (TP): 0x418  31:24 0x2
  /// Throttle Time (TT):0x418  23:16 0x00
  /// Dynamic RX Link Throttling Enable (DRXLTE): 0x418  1 0
  /// Dynamic TX Link Throttling Enable (DTXLTE): 0x418  0 0
  ///
  Data32And = ~(UINT32)((0xFF << 24) | (0xFF << 16) | BIT1 | BIT0);
  Data32Or = (0x02 << 24);
  CpuRegbarAndThenOr32(RootPortId, 0x418, Data32And, Data32Or);

  return;
}


/**
This function Initalizes the Chapter 5  TBT Specific Configuration

SIP15 PCI Express Root Port BIOS Requirement Rev 0.9

@param[in] RootPortId       Root Port pci segment base address

**/
VOID
PcieiTbtInit(
  IN  UINT8                      RootPortId
)
{
  UINT32  Data32And;
  UINT32  Data32Or;

  ///
  /// PTM Block Enable (PTMBE) 0xFC  0 1
  /// Periodic Mode Enable (PME) 0xFC  1 0
  /// Filter Increment Enable (FIE) 0xFC  2 1
  /// Filter Strength (FS) 0xFC  7:3 0xC
  /// Calculation Period (CP) 0xFC  15:8 0x0
  /// TMU Sampling Correction(TMUSC) 0xFC  20:16 0x2
  /// Threshold Limit (TL) 0xFC  25:21 0xF
  ///

  Data32And = ~(UINT32)(B_PCIE_TBTPTMBCTRL_PME | B_PCIE_TBTPTMBCTRL_FS_MASK | B_PCIE_TBTPTMBCTRL_CP_MASK |
                        B_PCIE_TBTPTMBCTRL_TMUSC_MASK | B_PCIE_TBTPTMBCTRL_TL_MASK);
  Data32Or = (B_PCIE_TBTPTMBCTRL_PTMBE | B_PCIE_TBTPTMBCTRL_FIE) | (0x0C << B_PCIE_TBTPTMBCTRL_FS_OFFSET) |
             (0x02 << B_PCIE_TBTPTMBCTRL_TMUSC_OFFSET) | (0x0F << B_PCIE_TBTPTMBCTRL_TL_OFFSET);

  CpuRegbarAndThenOr32(RootPortId, R_PCIE_TBTPTMBCTRL, Data32And, Data32Or);

  return;
}

/**
This function Implemnets 3.6  Function Disable Flow

SIP15 PCI Express Root Port BIOS Requirement Rev 0.9

@param[in] RootPortId       Root Port pci segment base address

**/
VOID
PciePortFunctionDisable(
  IN  UINT8                      RootPortId
)
{
  UINT32  Data32;
  UINT8   Data8Or;
  UINT32  Counter;


  ///
  /// 0xE1  7  Root Port Static Clock Gate Enable(RPSCGEN) 1
  ///
  Data8Or = BIT7;
  CpuRegbarOr8 (RootPortId, R_PCIE_RPDCGEN, Data8Or);
  ///
  /// 0x424   8  Function Disable Controller Power Gating Enable   (FDCPGE) 1
  ///
  CpuRegbarOr32 (RootPortId, R_PCIE_PCIEPMECTL2, B_PCIE_PCIEPMECTL2_FDCPGE_OFFSET);

  ///
  /// 0xE2  4  Sideband Endpoint Oscillator/Side Clock Gating Enable (SEOSCGE) 1
  ///
  CpuRegbarOr8 (RootPortId, R_PCIE_RPPGEN, B_PCIE_RPPGEN_SEOSCGE);

  ///
  /// Set B0:Dy:Fn + 338h [26] (PCIEALC.BLKDQDA)= 1b
  ///
  CpuRegbarOr32 (RootPortId, R_PCIE_PCIEALC, B_PCIE_PCIEALC_BLKDQDA_OFFSET);
  ///
  /// Poll B0:Dy:Fn + 328h [31:24]  (PCIESTS1.LTSMSTATE)  until 0xE  or 50ms timeout
  ///
  Counter = 50;
  Data32 = CpuRegbarRead32 (RootPortId, R_PCIE_PCIESTS1);

  while (((Data32 & B_PCIE_PCIESTS1_LTSMSTATE_MASK) != (0x0E << B_PCIE_PCIESTS1_LTSMSTATE_OFFSET)) && Counter > 0 ){
    MicroSecondDelay(1000);
    Data32 = CpuRegbarRead32 (RootPortId, R_PCIE_PCIESTS1);
    Counter--;
  }
  ///
  /// Set B0:Dy:Fn + 408h [27] (PHYCTL4.SQDIS) = 1b.
  ///
  CpuRegbarOr32 (RootPortId, R_PCIE_PHYCTL4, B_PCIE_PHYCTL4_SQDIS_OFFSET);

}


/**
This function Implements Early PCI Port initialization

SIP15 PCI Express Root Port BIOS Requirement Rev 0.9

@param[in] RootPortId       Root Port pci segment base address

**/
VOID
PciePortEarlyinit(
  IN  UINT8                      RootPortId,
  IN  ITBT_PCIE_CONFIG          *iTbtPcieConfig
)
{

  DEBUG((DEBUG_INFO, "PciePortEarlyinit RootPortId = %x : VID:%x \n",RootPortId,CpuRegbarRead32(RootPortId,0)));

  PciePowerManagementInit(RootPortId, iTbtPcieConfig);
  PciePowerGatingRegisterInit(RootPortId);
  if (iTbtPcieConfig->PtmEnabled) {
    DEBUG((DEBUG_INFO, "PtmEnabled on RootPortId = %x : VID:%x \n", RootPortId, CpuRegbarRead32(RootPortId, 0)));
    PciePtmInit(RootPortId);
  }
  PcieMiscInit(RootPortId);
  PcieiTbtInit(RootPortId);

  DEBUG((DEBUG_INFO, "PciePortEarlyinit End \n"));
}


/**
This function Implements iTbt PCI Port initialization.Called at PostMem

SIP15 PCI Express Root Port BIOS Requirement Rev 0.9
  @param[in] TcssConfig           Pointer to config block

**/
VOID
ItbtInitRootPorts(
  IN  TCSS_PEI_CONFIG             *TcssPeiConfig
)
{
  UINT8           Index;
  UINT32          SaMchBar;
  UINT32          SaTcssDeven;

  UINT64          RpBase;
  UINT32          PcieSegMap;
  UINT32          PcieFuncMap;
  UINT8           RootPortFn;
  UINT8           RootPortSeg;
  UINT8           PciePortIdMap[4] = { CPU_SB_PID_PCIE0, CPU_SB_PID_PCIE1, CPU_SB_PID_PCIE2, CPU_SB_PID_PCIE3 };
  UINT8           TempRootPortBusNumMin;
  UINT8           TempRootPortBusNumMax;
  TCSS_DATA_HOB   *TcssHob;
  UINT8           InterruptPin;
  UINT32          Data32Or;
  UINT32          Data32And;

  TcssHob = (TCSS_DATA_HOB *)GetFirstGuidHob(&gTcssHobGuid);

  DEBUG((DEBUG_INFO, "SaPcieInit \n"));


  SaMchBar = PciSegmentRead32(PCI_SEGMENT_LIB_ADDRESS(SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MCHBAR)) & ~BIT0;
  SaTcssDeven = MmioRead32(SaMchBar + R_SA_MCHBAR_TCSS_DEVEN_OFFSET);

  ///
  /// Initiazlize TBT PCI Root Ports
  ///
  PcieFuncMap = PciSegmentRead32(PCI_SEGMENT_LIB_ADDRESS(SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_PCIEFUNCMAP));
  PcieSegMap = PciSegmentRead32(PCI_SEGMENT_LIB_ADDRESS(SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_PCIESEGMAP));

  TempRootPortBusNumMin = PcdGet8(PcdSiliconInitTempPciBusMin);
  TempRootPortBusNumMax = PcdGet8(PcdSiliconInitTempPciBusMax);


  for (Index = 0; Index < MAX_ITBT_PCIE_PORT; Index++) {
    if (SaTcssDeven & (B_SA_MCHBAR_TCSS_DEVEN_PCIE0_MASK << Index)) {
      RootPortFn = (PcieFuncMap >> (Index * S_SA_PCIEFUNCMAP_PCIE0FUNC_WIDTH)) & B_SA_PCIEFUNCMAP_PCIE0FUNC_MASK;
      RootPortSeg = (PcieSegMap >> (Index * S_SA_PCIESEGMAP_PCIE0SEG_WIDTH)) & B_SA_PCIESEGMAP_PCIE0SEG_MASK;
      RpBase = PCI_SEGMENT_LIB_ADDRESS(RootPortSeg, SA_MC_BUS, SA_ITBT_PCIE_DEV_NUM, RootPortFn, 0);

      ///
      /// BIOS shoule set this bit for ICL CPU for PCIe RP
      ///
      PciSegmentOr32 (RpBase + R_PCIE_DC, B_PCIE_DC_DCT1C);
      PciePortEarlyinit(PciePortIdMap[Index], (ITBT_PCIE_CONFIG *)(&TcssPeiConfig->PciePolicy.PciePortPolicy[Index]));
      InterruptPin = Index + 1;
      Data32And = (UINT32) ~B_PCIE_STRPFUSECFG_PXIP;
      Data32Or = (UINT32) (InterruptPin << B_PCIE_STRPFUSECFG_PXIP_OFFSET);
      PciSegmentAndThenOr32 (RpBase + R_PCIE_STRPFUSECFG, Data32And, Data32Or);
      PcieInitCapabilityList(RpBase, (ITBT_PCIE_CONFIG *)(&TcssPeiConfig->PciePolicy.PciePortPolicy[Index]));
      //
      //Program BLKDQDA and BLKDQDASA to 0 as per PCIE BWG r0.9
      //
      PciSegmentAnd32 (RpBase + R_PCIE_PCIEALC, (UINT32) ~(B_PCIE_PCIEALC_BLKDQDA | B_PCIE_PCIEALC_BLKDQDASD));

      RootportDownstreamConfiguration(
        RootPortSeg,
        SA_MC_BUS,
        (UINT8)SA_ITBT_PCIE_DEV_NUM,
        (UINT8)RootPortFn,
        TempRootPortBusNumMin,
        TempRootPortBusNumMax,
        EnumiTbtPcie
        );
      ///
      /// Program SRL bit to lock the PCIe RP at end of PCIe initialization.
      ///
      PciSegmentOr32 (RpBase + R_SA_TCSS_PCIE_CFG_MPC, B_SA_TCSS_PCIE_CFG_MPC_SRL);
      CpuRegbarWrite32 (PciePortIdMap[Index], R_TCSS_PCIEX_SRL, B_TCSS_PCIEX_SRL);


      if (TcssHob != NULL) {
        ///
        /// Update LTR settings to TCSS HOB
        ///
        TcssHob->PcieItbtLtrData[Index].LtrEnable = (UINT8) TcssPeiConfig->PciePolicy.PciePortPolicy[Index].LtrEnable;
        TcssHob->PcieItbtLtrData[Index].LtrMaxSnoopLatency = TcssPeiConfig->PciePolicy.PciePortPolicy[Index].LtrMaxSnoopLatency;
        TcssHob->PcieItbtLtrData[Index].LtrMaxNoSnoopLatency = TcssPeiConfig->PciePolicy.PciePortPolicy[Index].LtrMaxNoSnoopLatency;
        TcssHob->PcieItbtLtrData[Index].SnoopLatencyOverrideMode = TcssPeiConfig->PciePolicy.PciePortPolicy[Index].SnoopLatencyOverrideMode;
        TcssHob->PcieItbtLtrData[Index].SnoopLatencyOverrideMultiplier = TcssPeiConfig->PciePolicy.PciePortPolicy[Index].SnoopLatencyOverrideMultiplier;
        TcssHob->PcieItbtLtrData[Index].SnoopLatencyOverrideValue = TcssPeiConfig->PciePolicy.PciePortPolicy[Index].SnoopLatencyOverrideValue;
        TcssHob->PcieItbtLtrData[Index].NonSnoopLatencyOverrideMode = TcssPeiConfig->PciePolicy.PciePortPolicy[Index].NonSnoopLatencyOverrideMode;
        TcssHob->PcieItbtLtrData[Index].NonSnoopLatencyOverrideMultiplier = TcssPeiConfig->PciePolicy.PciePortPolicy[Index].NonSnoopLatencyOverrideMultiplier;
        TcssHob->PcieItbtLtrData[Index].NonSnoopLatencyOverrideValue = TcssPeiConfig->PciePolicy.PciePortPolicy[Index].NonSnoopLatencyOverrideValue;
        TcssHob->PcieItbtLtrData[Index].ForceLtrOverride = TcssPeiConfig->PciePolicy.PciePortPolicy[Index].ForceLtrOverride;
        TcssHob->PcieItbtLtrData[Index].LtrConfigLock = TcssPeiConfig->PciePolicy.PciePortPolicy[Index].LtrConfigLock;
      }
    }
  }

  DEBUG((DEBUG_INFO, "SaPcieInit End \n"));
}

//
// 2LM: PegPcie APIs using the Sideband Access Mechanism
//
/**
  Reads an 8-bit PCI configuration register.

  Its a wrapper library function. This function uses side band access for PEG60 when 2LM mode is enabled.
  Other calls to this function will be routed to core PciSegmentRead8 function.

  @param  Address   Address that encodes the PCI Segment, Bus, Device, Function, and Register.

  @return The 8-bit PCI configuration register specified by Address.
**/
UINT8
EFIAPI
PegPciSegmentRead8 (
  IN UINT64                    Address
  )
{
  UINT32 Data32;

  Data32 = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MC_CAPID0_B));
  if (Data32 & V_SA_MC_CAPID0_B_2LM_EN) {
    //
    // Use side band access for PEG60 (Bus 0 Dev 6 Fun 0) when 2LM mode is enabled
    //
    if ((((UINT32)Address & 0xFFFF000) >> 12) == 0x30) {
      return CpuRegbarRead8 (CPU_SB_PID_PEG60, (Address & 0xFFF));
    }
  }

  return PciSegmentRead8 (Address);
}

/**
  Writes an 8-bit PCI configuration register.

  Its a wrapper library function. This function uses side band access for PEG60 when 2LM mode is enabled.
  Other calls to this function will be routed to core PciSegmentWrite8 function.

  @param  Address     Address that encodes the PCI Segment, Bus, Device, Function, and Register.
  @param  Value       The value to write.

  @return The value written to the PCI configuration register.
**/
UINT8
EFIAPI
PegPciSegmentWrite8 (
  IN UINT64                    Address,
  IN UINT8                     Value
  )
{
  UINT32 Data32;

  Data32 = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MC_CAPID0_B));
  if (Data32 & V_SA_MC_CAPID0_B_2LM_EN) {
    //
    // Use side band access for PEG60 (Bus 0 Dev 6 Fun 0) when 2LM mode is enabled
    //
    if ((((UINT32)Address & 0xFFFF000) >> 12) == 0x30) {
      return CpuRegbarWrite8 (CPU_SB_PID_PEG60, (Address & 0xFFF), Value);
    }
  }

  return PciSegmentWrite8 (Address, Value);
}

/**
  Reads a 16-bit PCI configuration register.

  Its a wrapper library function. This function uses side band access for PEG60 when 2LM mode is enabled.
  Other calls to this function will be routed to core PciSegmentRead16 function.

  @param  Address   Address that encodes the PCI Segment, Bus, Device, Function, and Register.

  @return The 16-bit PCI configuration register specified by Address.
**/
UINT16
EFIAPI
PegPciSegmentRead16 (
  IN UINT64                    Address
  )
{
  UINT32 Data32;

  Data32 = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MC_CAPID0_B));
  if (Data32 & V_SA_MC_CAPID0_B_2LM_EN) {
    //
    // Use side band access for PEG60 (Bus 0 Dev 6 Fun 0) when 2LM mode is enabled
    //
    if ((((UINT32)Address & 0xFFFF000) >> 12) == 0x30) {
      return CpuRegbarRead16 (CPU_SB_PID_PEG60, (Address & 0xFFF));
    }
  }

  return PciSegmentRead16 (Address);
}

/**
  Writes a 16-bit PCI configuration register.

  Its a wrapper library function. This function uses side band access for PEG60 when 2LM mode is enabled.
  Other calls to this function will be routed to core PciSegmentWrite16 function.

  @param  Address     Address that encodes the PCI Segment, Bus, Device, Function, and Register.
  @param  Value       The value to write.

  @return The parameter of Value.
**/
UINT16
EFIAPI
PegPciSegmentWrite16 (
  IN UINT64                    Address,
  IN UINT16                     Value
  )
{
  UINT32 Data32;

  Data32 = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MC_CAPID0_B));
  if (Data32 & V_SA_MC_CAPID0_B_2LM_EN) {
    //
    // Use side band access for PEG60 (Bus 0 Dev 6 Fun 0) when 2LM mode is enabled
    //
    if ((((UINT32)Address & 0xFFFF000) >> 12) == 0x30) {
      return CpuRegbarWrite16 (CPU_SB_PID_PEG60, (Address & 0xFFF), Value);
    }
  }

  return PciSegmentWrite16 (Address, Value);
}

/**
  Reads a 32-bit PCI configuration register.

  Its a wrapper library function. This function uses side band access for PEG60 when 2LM mode is enabled.
  Other calls to this function will be routed to core PciSegmentRead32 function.

  @param  Address   Address that encodes the PCI Segment, Bus, Device, Function, and Register.

  @return The 32-bit PCI configuration register specified by Address.
**/
UINT32
EFIAPI
PegPciSegmentRead32 (
  IN UINT64                    Address
  )
{
  UINT32 Data32;

  Data32 = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MC_CAPID0_B));
  if (Data32 & V_SA_MC_CAPID0_B_2LM_EN) {
    //
    // Use side band access for PEG60 (Bus 0 Dev 6 Fun 0) when 2LM mode is enabled
    //
    if ((((UINT32)Address & 0xFFFF000) >> 12) == 0x30) {
      return CpuRegbarRead32 (CPU_SB_PID_PEG60, (Address & 0xFFF));
    }
  }

  return PciSegmentRead32 (Address);
}

/**
  Writes a 32-bit PCI configuration register.

  Its a wrapper library function. This function uses side band access for PEG60 when 2LM mode is enabled.
  Other calls to this function will be routed to core PciSegmentWrite32 function.

  @param  Address     Address that encodes the PCI Segment, Bus, Device, Function, and Register.
  @param  Value       The value to write.

  @return The parameter of Value.
**/
UINT32
EFIAPI
PegPciSegmentWrite32 (
  IN UINT64                    Address,
  IN UINT32                     Value
  )
{
  UINT32 Data32;

  Data32 = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MC_CAPID0_B));
  if (Data32 & V_SA_MC_CAPID0_B_2LM_EN) {
    //
    // Use side band access for PEG60 (Bus 0 Dev 6 Fun 0) when 2LM mode is enabled
    //
    if ((((UINT32)Address & 0xFFFF000) >> 12) == 0x30) {
      return CpuRegbarWrite32 (CPU_SB_PID_PEG60, (Address & 0xFFF), Value);
    }
  }

  return PciSegmentWrite32 (Address, Value);
}

/**
  Performs a bitwise OR of a 16-bit PCI configuration register with a 16-bit value.

  Its a wrapper library function. This function uses side band access for PEG60 when 2LM mode is enabled.
  Other calls to this function will be routed to core PciSegmentOr16 function.

  @param  Address   Address that encodes the PCI Segment, Bus, Device, Function, and Register.
  @param  OrData    The value to OR with the PCI configuration register.

  @return The value written to the PCI configuration register.
**/
UINT16
EFIAPI
PegPciSegmentOr16 (
  IN UINT64                    Address,
  IN UINT16                    OrData
  )
{
  UINT32 Data32;

  Data32 = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MC_CAPID0_B));
  if (Data32 & V_SA_MC_CAPID0_B_2LM_EN) {
    //
    // Use side band access for PEG60 (Bus 0 Dev 6 Fun 0) when 2LM mode is enabled
    //
    if ((((UINT32)Address & 0xFFFF000) >> 12) == 0x30) {
      return CpuRegbarOr16 (CPU_SB_PID_PEG60, (Address & 0xFFF), OrData);
    }
  }

  return PciSegmentOr16 (Address, OrData);
}

/**
  Performs a bitwise AND of a 16-bit PCI configuration register with a 16-bit value.

  Its a wrapper library function. This function uses side band access for PEG60 when 2LM mode is enabled.
  Other calls to this function will be routed to core PciSegmentAnd32 function.

  @param  Address   Address that encodes the PCI Segment, Bus, Device, Function, and Register.
  @param  AndData   The value to AND with the PCI configuration register.

  @return The value written to the PCI configuration register.

**/
UINT16
EFIAPI
PegPciSegmentAnd16 (
  IN UINT64                    Address,
  IN UINT16                    AndData
  )
{
  UINT32 Data32;

  Data32 = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MC_CAPID0_B));
  if (Data32 & V_SA_MC_CAPID0_B_2LM_EN) {
    //
    // Use side band access for PEG60 (Bus 0 Dev 6 Fun 0) when 2LM mode is enabled
    //
    if ((((UINT32)Address & 0xFFFF000) >> 12) == 0x30) {
      return CpuRegbarAnd16 (CPU_SB_PID_PEG60, (Address & 0xFFF), AndData);
    }
  }

  return PciSegmentAnd16 (Address, AndData);
}

/**
  Performs a bitwise OR of a 32-bit PCI configuration register with a 32-bit value.

  Its a wrapper library function. This function uses side band access for PEG60 when 2LM mode is enabled.
  Other calls to this function will be routed to core PciSegmentOr32 function.

  @param  Address   Address that encodes the PCI Segment, Bus, Device, Function, and Register.
  @param  OrData    The value to OR with the PCI configuration register.

  @return The value written to the PCI configuration register.
**/
UINT32
EFIAPI
PegPciSegmentOr32 (
  IN UINT64                    Address,
  IN UINT32                    OrData
  )
{
  UINT32 Data32;

  Data32 = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MC_CAPID0_B));
  if (Data32 & V_SA_MC_CAPID0_B_2LM_EN) {
    //
    // Use side band access for PEG60 (Bus 0 Dev 6 Fun 0) when 2LM mode is enabled
    //
    if ((((UINT32)Address & 0xFFFF000) >> 12) == 0x30) {
      return CpuRegbarOr32 (CPU_SB_PID_PEG60, (Address & 0xFFF), OrData);
    }
  }

  return PciSegmentOr32 (Address, OrData);
}

/**
  Performs a bitwise AND of a 32-bit PCI configuration register with a 32-bit value.

  Its a wrapper library function. This function uses side band access for PEG60 when 2LM mode is enabled.
  Other calls to this function will be routed to core PciSegmentAnd32 function.

  @param  Address   Address that encodes the PCI Segment, Bus, Device, Function, and Register.
  @param  AndData   The value to AND with the PCI configuration register.

  @return The value written to the PCI configuration register.

**/
UINT32
EFIAPI
PegPciSegmentAnd32 (
  IN UINT64                    Address,
  IN UINT32                    AndData
  )
{
  UINT32 Data32;

  Data32 = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MC_CAPID0_B));
  if (Data32 & V_SA_MC_CAPID0_B_2LM_EN) {
    //
    // Use side band access for PEG60 (Bus 0 Dev 6 Fun 0) when 2LM mode is enabled
    //
    if ((((UINT32)Address & 0xFFFF000) >> 12) == 0x30) {
      return CpuRegbarAnd32 (CPU_SB_PID_PEG60, (Address & 0xFFF), AndData);
    }
  }

  return PciSegmentAnd32 (Address, AndData);
}

/**
  Performs a bitwise AND of a 32-bit PCI configuration register with a 32-bit value,
  followed a  bitwise OR with another 32-bit value.

  Its a wrapper library function. This function uses side band access for PEG60 when 2LM mode is enabled.
  Other calls to this function will be routed to core PciSegmentAndThenOr32 function.

  @param  Address   Address that encodes the PCI Segment, Bus, Device, Function, and Register.
  @param  AndData   The value to AND with the PCI configuration register.
  @param  OrData    The value to OR with the PCI configuration register.

  @return The value written to the PCI configuration register.
**/
UINT32
EFIAPI
PegPciSegmentAndThenOr32 (
  IN UINT64                    Address,
  IN UINT32                    AndData,
  IN UINT32                    OrData
  )
{
  UINT32 Data32;

  Data32 = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MC_CAPID0_B));
  if (Data32 & V_SA_MC_CAPID0_B_2LM_EN) {
    //
    // Use side band access for PEG60 (Bus 0 Dev 6 Fun 0) when 2LM mode is enabled
    //
    if ((((UINT32)Address & 0xFFFF000) >> 12) == 0x30) {
      return CpuRegbarAndThenOr32 (CPU_SB_PID_PEG60, (Address & 0xFFF), AndData, OrData);
    }
  }

  return PciSegmentAndThenOr32 (Address, AndData, OrData);
}


/**
  Find the Offset to a Capabilities ID
  @param[in] Segment              Pci Segment Number
  @param[in] Bus                  Pci Bus Number
  @param[in] Device               Pci Device Number
  @param[in] Function             Pci Function Number
  @param[in] CapId                CAPID to search for

  @retval 0                       CAPID not found
  @retval Other                   CAPID found, Offset of desired CAPID
**/
UINT8
PegPcieFindCapId (
  IN UINT8   Segment,
  IN UINT8   Bus,
  IN UINT8   Device,
  IN UINT8   Function,
  IN UINT8   CapId
  )
{
  UINT8   CapHeaderOffset;
  UINT8   CapHeaderId;
  UINT64  DeviceBase;
  UINT32  Data32;


  Data32 = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MC_CAPID0_B));
  if (Data32 & V_SA_MC_CAPID0_B_2LM_EN) {

    DeviceBase = PCI_SEGMENT_LIB_ADDRESS (Segment, Bus, Device, Function, 0);
    //
    // Use side band access for PEG60 (Bus 0 Dev 6 Fun 0) when 2LM mode is enabled
    //
    if ((((UINT32)DeviceBase & 0xFFFF000) >> 12) == 0x30) {
      if ((CpuRegbarRead8 (CPU_SB_PID_PEG60, ((DeviceBase + PCI_PRIMARY_STATUS_OFFSET) & 0xFFF)) & EFI_PCI_STATUS_CAPABILITY) == 0x00) {
        ///
        /// Function has no capability pointer
        ///
        return 0;
      }
      ///
      /// Check the header layout to determine the Offset of Capabilities Pointer Register
      ///
      if ((CpuRegbarRead8 (CPU_SB_PID_PEG60, ((DeviceBase + PCI_HEADER_TYPE_OFFSET) & 0xFFF)) & HEADER_LAYOUT_CODE) == (HEADER_TYPE_CARDBUS_BRIDGE)) {
        ///
        /// If CardBus bridge, start at Offset 0x14
        ///
        CapHeaderOffset = 0x14;
      } else {
        ///
        /// Otherwise, start at Offset 0x34
        ///
        CapHeaderOffset = 0x34;
      }
      ///
      /// Get Capability Header, A pointer value of 00h is used to indicate the last capability in the list.
      ///
      CapHeaderId     = 0;
      CapHeaderOffset = CpuRegbarRead8 (CPU_SB_PID_PEG60, ((DeviceBase + CapHeaderOffset) & 0xFFF)) & ((UINT8) ~(BIT0 | BIT1));
      while (CapHeaderOffset != 0 && CapHeaderId != 0xFF) {
        CapHeaderId = CpuRegbarRead8 (CPU_SB_PID_PEG60, ((DeviceBase + CapHeaderOffset) & 0xFFF));
        if (CapHeaderId == CapId) {
          return CapHeaderOffset;
        }
        ///
        /// Each capability must be DWORD aligned.
        /// The bottom two bits of all pointers (including the initial pointer at 34h) are reserved
        /// and must be implemented as 00b although software must mask them to allow for future uses of these bits.
        ///
        CapHeaderOffset = CpuRegbarRead8 (CPU_SB_PID_PEG60, ((DeviceBase + CapHeaderOffset + 1) & 0xFFF)) & ((UINT8) ~(BIT0 | BIT1));
      }
      return 0;
    }
  }
  return PcieFindCapId (Segment, Bus, Device, Function, CapId);
}


/**
  Search and return the offset of desired Pci Express extended Capability ID
  @param[in] Segment              Pci Segment Number
  @param[in] Bus                  Pci Bus Number
  @param[in] Device               Pci Device Number
  @param[in] Function             Pci Function Number
  @param[in] CapId                Extended CAPID to search for

  @retval 0                       CAPID not found
  @retval Other                   CAPID found, Offset of desired CAPID
**/
UINT16
PegPcieFindExtendedCapId (
  IN UINT8   Segment,
  IN UINT8   Bus,
  IN UINT8   Device,
  IN UINT8   Function,
  IN UINT16  CapId
  )
{
  UINT16  CapHeaderOffset;
  UINT16  CapHeaderId;
  UINT64  DeviceBase;
  UINT32  Data32;

  Data32 = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MC_CAPID0_B));
  if (Data32 & V_SA_MC_CAPID0_B_2LM_EN) {

    DeviceBase = PCI_SEGMENT_LIB_ADDRESS (Segment, Bus, Device, Function, 0);
    //
    // Use side band access for PEG60 (Bus 0 Dev 6 Fun 0) when 2LM mode is enabled
    //
    if ((((UINT32)DeviceBase & 0xFFFF000) >> 12) == 0x30) {
      ///
      /// Start to search at Offset 0x100
      /// Get Capability Header, A pointer value of 00h is used to indicate the last capability in the list.
      ///
      CapHeaderId     = 0;
      CapHeaderOffset = 0x100;
      while (CapHeaderOffset != 0 && CapHeaderId != 0xFFFF) {
        CapHeaderId = CpuRegbarRead16 (CPU_SB_PID_PEG60, ((DeviceBase + CapHeaderOffset) & 0xFFF));
        if (CapHeaderId == CapId) {
          return CapHeaderOffset;
        }
        ///
        /// Each capability must be DWORD aligned.
        /// The bottom two bits of all pointers are reserved and must be implemented as 00b
        /// although software must mask them to allow for future uses of these bits.
        ///
        CapHeaderOffset = CpuRegbarRead16 (CPU_SB_PID_PEG60, ((DeviceBase + CapHeaderOffset+2) & 0xFFF)) >> 4 & ((UINT16) ~(BIT0 | BIT1));
      }
      return 0;
    }
  }
  return PcieFindExtendedCapId (Segment, Bus, Device, Function, CapId);
}
