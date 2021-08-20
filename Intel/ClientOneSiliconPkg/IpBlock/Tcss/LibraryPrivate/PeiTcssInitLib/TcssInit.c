/** @file
  The PEI TCSS Init Library Implements After Memory PEIM

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2019 Intel Corporation.

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
#include <PcieRegs.h>
#include <Register/HostDmaRegs.h>
#include <Register/IomRegs.h>
#include <Register/CpuUsbRegs.h>
#include <Register/PchPcrRegs.h>
#include <Register/UsbRegs.h>
#include <Library/PchPcieRpLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PostCodeLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/TcssInitLib.h>
#include <SaConfigHob.h>
#include <TcssDataHob.h>
#include <SaPolicyCommon.h>
#include <Library/TimerLib.h>
#include <Library/GpioPrivateLib.h>
#include <Library/DciPrivateLib.h>
#include <Library/CpuRegbarAccessLib.h>
#include <Library/ItbtPcieRpInitLib.h>
#include <Library/UsbHostControllerInitLib.h>
#include <Library/UsbDeviceControllerInitLib.h>
#include <Library/PeiTbtTaskDispatchLib.h>
#include <Library/PeiITbtInitLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/TcssPmcLib.h>
#include <Library/ItbtPcieRpLib.h>
#include <PeiITbtConfig.h>
#include <Library/PreSiliconEnvDetectLib.h>
#include <CpuSbInfo.h>

EFI_STATUS
EFIAPI
TcssInitEndOfPei (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  );

static EFI_PEI_NOTIFY_DESCRIPTOR  mEndOfPeiNotifyList = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiEndOfPeiSignalPpiGuid,
  (EFI_PEIM_NOTIFY_ENTRY_POINT) TcssInitEndOfPei
};

/**
  Installs TCSS Data Hob

  @retval EFI_SUCCESS           The HOB was successfully created.
  @retval EFI_OUT_OF_RESOURCES  There is no additional space for HOB creation.
**/
EFI_STATUS
InstallTcssDataHob (
  VOID
  )
{

  EFI_STATUS                  Status;
  TCSS_DATA_HOB               *TcssHob;

  ///
  /// Create HOB for TCSS Data
  ///
  Status = PeiServicesCreateHob (
             EFI_HOB_TYPE_GUID_EXTENSION,
             sizeof (TCSS_DATA_HOB),
             (VOID **) &TcssHob
             );
  ASSERT_EFI_ERROR (Status);
  ///
  /// Initialize default HOB data
  ///
  TcssHob->EfiHobGuidType.Name = gTcssHobGuid;
  DEBUG ((DEBUG_INFO, "TcssHob->EfiHobGuidType.Name: %g\n", &TcssHob->EfiHobGuidType.Name));
  ZeroMem (&(TcssHob->TcssData), sizeof (TCSS_DATA));

  DEBUG ((DEBUG_INFO, "TcssHob @ %X\n", TcssHob));
  DEBUG ((DEBUG_INFO, "&(TcssHob->TcssData) @ %X\n", &(TcssHob->TcssData)));
  DEBUG ((DEBUG_INFO, "TcssHob - HobHeader: %X\n", sizeof (TCSS_DATA_HOB) - sizeof (EFI_HOB_GUID_TYPE)));
  DEBUG ((DEBUG_INFO, "TcssData: %X\n", sizeof (TCSS_DATA)));

  return Status;
}

/**
  This function performs read MG IMR status to HOB

**/
VOID
UpdateMgImrStatus (
  VOID
  )
{
  MG_IMR_STATUS               MgImr;
  TCSS_DATA_HOB               *TcssHob;

  DEBUG ((DEBUG_INFO, "[TCSS] UpdateMgImrStatus Entry\n"));

  TcssHob = NULL;
  TcssHob = (TCSS_DATA_HOB *) GetFirstGuidHob (&gTcssHobGuid);
  if (TcssHob == NULL) {
    ASSERT (FALSE);
    return;
  }

  //
  // Read MG IMR status
  //
  MgImr.RegValue = CpuRegbarRead32 (CPU_SB_PID_IOM, R_SA_IOM_CSME_IMR_MG_STATUS);
  DEBUG ((DEBUG_INFO, "R_SA_IOM_CSME_IMR_MG_STATUS: 0x%08X\n", MgImr.RegValue));
  DEBUG ((DEBUG_INFO, "MG FW version: 0x%04X\n", (UINT16) MgImr.Bits.MgFwVersion));

  if (MgImr.Bits.Done) {
    if (MgImr.Bits.Valid) {
      TcssHob->TcssData.MgImrStatus.RegValue = MgImr.RegValue;
      DEBUG ((DEBUG_ERROR, "Load MG FW success\n"));
    } else {
      DEBUG ((DEBUG_ERROR, "untrusted MG FW\n"));
      ASSERT (FALSE);
    }
  } else {
    DEBUG ((DEBUG_ERROR, "MG FW has not yet downloaded to IMR\n"));
    if (!IsSimicsEnvironment ()) {
      ASSERT (FALSE);
    }
  }

  DEBUG ((DEBUG_INFO, "[TCSS] UpdateMgImrStatus End\n"));

  return;
}

/**
  This function handles TcssInit task at the end of PEI

  @param[in]  PeiServices  Pointer to PEI Services Table.
  @param[in]  NotifyDesc   Pointer to the descriptor for the Notification event that
                           caused this function to execute.
  @param[in]  Ppi          Pointer to the PPI data associated with this function.

  @retval     EFI_SUCCESS      The function completes successfully
  @retval     EFI_UNSUPPORTED  The TBT FW not ready
  @retval     others
**/
EFI_STATUS
EFIAPI
TcssInitEndOfPei (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  )
{
  EFI_STATUS                    Status;
  UINT8                         Index;
  BOOLEAN                       ITbtExisted;
  SI_POLICY_PPI                 *SiPolicyPpi;
  PEI_ITBT_CONFIG               *PeiITbtConfig;
  TCSS_DATA_HOB                 *TcssHob;
  TBT_IMR_STATUS                TbtImr;
  UINT64                        McD0BaseAddress;
  UINT32                        MchBar;

  DEBUG ((DEBUG_INFO, "[TCSS] TcssInitEndOfPei Entry\n"));

  Status                = EFI_SUCCESS;
  SiPolicyPpi           = NULL;
  PeiITbtConfig         = NULL;
  Index                 = 0;
  ITbtExisted           = FALSE;
  McD0BaseAddress       = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, 0);
  MchBar                = PciSegmentRead32 (McD0BaseAddress + R_SA_MCHBAR) & ~B_SA_MCHBAR_MCHBAREN_MASK;

  UpdateMgImrStatus ();

  Status = PeiServicesLocatePpi (
             &gSiPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gPeiITbtConfigGuid, (VOID *) &PeiITbtConfig);
  ASSERT_EFI_ERROR (Status);

  TcssHob = (TCSS_DATA_HOB *) GetFirstGuidHob (&gTcssHobGuid);
  if (TcssHob == NULL) {
    DEBUG ((DEBUG_ERROR, "TcssHob is NULL\n"));
    if (!IsSimicsEnvironment ()) {
      ASSERT(FALSE);
    }
    return EFI_UNSUPPORTED;
  }

  for (Index = 0; Index < MAX_ITBT_PCIE_PORT; Index++) {
    if (TcssHob->TcssData.ItbtPcieRpEn[Index] == 1) {
      ITbtExisted = TRUE;
      break;
    }
  }

  for (Index = 0; Index < SA_MAX_HOST_ITBT_DMA_NUMBER; Index++) {
    if (TcssHob->TcssData.ItbtDmaEn[Index] == 1) {
      ITbtExisted = TRUE;
      break;
    }
  }

  ///
  /// Save TBT FW state/version.
  /// Assumption - All TBT DMA controllers have the same FW loading status.
  ///
  TbtImr.RegValue = CpuRegbarRead32 (CPU_SB_PID_IOM, R_SA_IOM_CSME_IMR_TBT_STATUS);
  DEBUG ((DEBUG_INFO, "R_SA_IOM_CSME_IMR_TBT_STATUS: 0x%08X\n", TbtImr.RegValue));
  DEBUG ((DEBUG_INFO, "TBT FW version: 0x%04X\n", (UINT16) TbtImr.Bits.TbtFwVersion));

  //
  // Update information to hob
  //
  if (TbtImr.Bits.Done && TbtImr.Bits.Valid) {
    TcssHob->TcssData.TbtImrStatus.RegValue = TbtImr.RegValue;
    DEBUG ((DEBUG_INFO, "TBT FW IMR info is updated to TCSS HOB, value is %x\n", TcssHob->TcssData.TbtImrStatus.RegValue));
  } else {
    DEBUG ((DEBUG_ERROR, "TBT FW has not yet downloaded to IMR\n"));
    if ((!IsSimicsEnvironment ()) && (ITbtExisted == TRUE)) {
      ASSERT(FALSE);
    }
    //
    // Disable TBT IPs of the TCSS DEVEN register when TBT FW is not downloaded to IMR
    //
    MmioAnd32 (MchBar + R_SA_MCHBAR_TCSS_DEVEN_OFFSET,
      (UINT32) ~(B_SA_MCHBAR_TCSS_DEVEN_PCIE0_MASK |
      B_SA_MCHBAR_TCSS_DEVEN_PCIE1_MASK |
      B_SA_MCHBAR_TCSS_DEVEN_PCIE2_MASK |
      B_SA_MCHBAR_TCSS_DEVEN_PCIE3_MASK |
      B_SA_MCHBAR_TCSS_DEVEN_DMA0_MASK |
      B_SA_MCHBAR_TCSS_DEVEN_DMA1_MASK)
    );
    return EFI_UNSUPPORTED;
  }

  if (ITbtExisted == TRUE) {
    //
    // Dispatch ITBT task table
    //
    TbtTaskDistpach (ITbtCallTable, (VOID *) PeiITbtConfig);
  }

  return EFI_SUCCESS;
}

/**
  This function performs set ITBT function disable register status to HOB

  @param[in] TcssDeven          ITBT function disable register value
**/
VOID
UpdateTcssDevenToHob(
  IN UINT32                       TcssDeven
  )
{
  TCSS_DATA_HOB                   *TcssHob;
  UINT32                          Data;
  UINT32                          Index;

  ///
  /// Update TCSS Device Enable status to TCSS HOB
  ///
  TcssHob = (TCSS_DATA_HOB *) GetFirstGuidHob (&gTcssHobGuid);
  if (TcssHob == NULL) {
    ASSERT (FALSE);
    return;
  }

  //
  // iTBT PCIE
  //
  for (Index = 0; Index < MAX_ITBT_PCIE_PORT; Index++) {
    TcssHob->TcssData.ItbtPcieRpEn[Index] = (UINT8)((TcssDeven >> Index) & BIT0);
  }

  //
  // USB
  //
  TcssHob->TcssData.ItbtXhciEn = (TcssDeven & B_SA_MCHBAR_TCSS_DEVEN_XHCI_MASK) ? 1 : 0;
  TcssHob->TcssData.ItbtXdciEn = (TcssDeven & B_SA_MCHBAR_TCSS_DEVEN_XDCI_MASK) ? 1 : 0;

  //
  // TBT DMA
  //
  Data = (TcssDeven & (B_SA_MCHBAR_TCSS_DEVEN_DMA0_MASK | B_SA_MCHBAR_TCSS_DEVEN_DMA1_MASK |\
            B_SA_MCHBAR_TCSS_DEVEN_DMA2_MASK)) >> N_SA_MCHBAR_TCSS_DEVEN_DMA0_OFFSET;
  for (Index = 0; Index < SA_MAX_HOST_ITBT_DMA_NUMBER; Index++) {
    TcssHob->TcssData.ItbtDmaEn[Index] = (UINT8)((Data >> Index) & BIT0);
  }

  DEBUG ((DEBUG_INFO, "[TCSS] Updated TCSS_DEVEN to TCSS HOB\n"));
  return;
}

/**
  TcssDevEnInitPreMem - Initializes the register TCSS_DEVEN_0_0_0_MCHBAR_IMPH

  Before DID, BIOS performs TCSS DEVEN disabling/enabling -
   (1).BIOS fills TCSS DEVEN value to TCSS_DEVEN_0_0_0_MCHBAR_IMPH based on BIOS policy accordingly,
       BIOS can only disables/enables supported TCSS DEV IP by SKU/Fuse accordingly.
   (2) BIOS reads TCSS DEVEN register back into local stack,
       the value reflects the exact TCSS DEV IP which can be enabled currently based on fuse info and BIOS policy.
       (Failsafe to ensure IOM can get the exactly DEV map used by Punit)
   (3).BIOS writes the TCSS DEVEN to IOM BIOS mailbox
   (4).BIOS guarantees the value write to TCSS DEVEN is as same as the one sent to IOM WB inside SoC BIOS reference code.

  @param[in]                      Pointer to TCSS pre-mem configuration policy
**/
VOID
TcssDevEnInitPreMem (
  IN  TCSS_PEI_PREMEM_CONFIG      *TcssPeiPreMemConfig
  )
{
  UINT32                          Cmd;
  UINT32                          TcssDeven;
  UINT32                          MchBar;

  DEBUG ((DEBUG_INFO, "[TCSS] TcssDevEnInitPreMem - Start\n"));

  ///
  /// 1.BIOS fills TCSS DEVEN value to IOP based on BIOS policy accordingly,
  ///   BIOS can only disables/enables supported TCSS DEV IP by SKU/Fuse accordingly.
  ///
  MchBar = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MCHBAR)) & ~BIT0;
  MmioWrite32(MchBar + R_SA_MCHBAR_TCSS_DEVEN_OFFSET, TcssPeiPreMemConfig->DevEnConfig.TcssDevEn);

  ///
  /// 2.BIOS reads TCSS DEVEN register back into local stack,
  ///   the value reflects the exact TCSS DEV IP which can be enabled currently based on fuse info and BIOS policy.
  ///   (Failsafe to ensure IOM can get the exactly DEV map used by Punit)
  ///
  TcssDeven = MmioRead32 (MchBar + R_SA_MCHBAR_TCSS_DEVEN_OFFSET);

  DEBUG ((DEBUG_INFO, "TCSS DEVEN = 0x%08X\n", TcssDeven));

  ///
  /// 3.BIOS writes the TCSS DEVEN data to IOM-BIOS mailbox
  ///

  //
  // BIOS updates TCSS DEVEN in IOP and read the register back to understand what the end result of its configuration.
  //
  CpuRegbarWrite32 (CPU_SB_PID_IOM, R_SA_IOM_BIOS_MAIL_BOX_DATA, TcssDeven | B_SA_IOM_BIOS_MAIL_BOX_IOM_EN);
  DEBUG ((DEBUG_INFO, "IOM mailbox data = 0x%08X\n", TcssDeven));

  //
  // BIOS writes the UPDATE_DEVEN command to IOM-BIOS MAILBOX command register
  //
  Cmd = V_SA_IOM_BIOS_UPDATE_DEVEN_CMD;
  CpuRegbarWrite32 (CPU_SB_PID_IOM, R_SA_IOM_BIOS_MAIL_BOX_CMD, Cmd);
  DEBUG ((DEBUG_INFO, "IOM mailbox command = 0x%08X\n", Cmd));

  //
  // Set the Run/Busy bit to signal mailbox data is ready to process. IOM FW is not yet
  // out of reset at this point, so don't wait for response.
  //
  Cmd |= B_SA_IOM_BIOS_SET_TO_RUN;
  CpuRegbarWrite32 (CPU_SB_PID_IOM, R_SA_IOM_BIOS_MAIL_BOX_CMD, Cmd);

  //
  // Update TcssDeven status via HOB
  //
  UpdateTcssDevenToHob (TcssDeven);

  DEBUG ((DEBUG_INFO, "[TCSS] TcssDevEnInitPreMem - End\n"));
}

/**
  This function program the PCIESEGMAP and PCIEFUNCMAP registers for assigning Segment and Function number to TBT PCIe port
**/
VOID
ConfigureTbtPcieSegFuncMap (
  IN  TCSS_PEI_PREMEM_CONFIG      *TcssPeiPreMemConfig
  )
{
  UINT64                          McD0BaseAddress;
  UINT8                           Index;
  INTN                            FirstEnabledItbtPortNumber;
  UINT32                          TcssDevEn;
  UINT8                           PciePortIdMap[4] = { CPU_SB_PID_PCIE0, CPU_SB_PID_PCIE1, CPU_SB_PID_PCIE2, CPU_SB_PID_PCIE3 };
  UINT32                          MchBar;
  BOOLEAN                         ItbtPcieRootPortExisted;
  BOOLEAN                         ItbtPcieRootPortEnabled[MAX_ITBT_PCIE_PORT];
  UINT8                           ItbtPcieFunctionNumber[MAX_ITBT_PCIE_PORT];
  UINT32                          PcieSegMap;
  UINT32                          PcieFuncMap;
#if FixedPcdGetBool(PcdFspBinaryEnable) == 0
  UINT32                          PciexBarReg;
#endif
  TCSS_DATA_HOB                   *TcssHob;

  DEBUG ((DEBUG_INFO, "[TCSS] ConfigureTbtPcieSegFuncMap() - Start\n"));
  ItbtPcieRootPortExisted = FALSE;
  PcieSegMap = 0;
  PcieFuncMap = 0;
  FirstEnabledItbtPortNumber = 0;
  McD0BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, 0);
  MchBar = PciSegmentRead32 (McD0BaseAddress + R_SA_MCHBAR) & ~BIT0;
  TcssDevEn = MmioRead32(MchBar + R_SA_MCHBAR_TCSS_DEVEN_OFFSET);

  //
  // Get the first enabled iTBT PCIe port number
  //
  FirstEnabledItbtPortNumber = LowBitSet32 (TcssDevEn & 0xFF);
  //
  // Check each iTBT PCIe RP is enabled or not.
  //
  for (Index = 0; Index < MAX_ITBT_PCIE_PORT; Index++) {
    if (TcssDevEn & (B_SA_MCHBAR_TCSS_DEVEN_PCIE0_MASK << Index)) {
      ItbtPcieRootPortEnabled[Index] = TRUE;
      ItbtPcieRootPortExisted = TRUE;
    } else {
      ItbtPcieRootPortEnabled[Index] = FALSE;
    }
  }

  if (!ItbtPcieRootPortExisted) {
    ///
    /// Force disable the PcieMultipleSegmentEnabled when no ItbtPcieRootPort Existed
    ///
    TcssPeiPreMemConfig->MiscConfig.PcieMultipleSegmentEnabled = 0;
  }
#if FixedPcdGetBool(PcdFspBinaryEnable) == 0
  //
  // Update PCIEXBAR and PcdPciExpressRegionLength to 512MB when PcieMultipleSegmentEnabled is enabled and any of ItbtPcieRp is enabled.
  //
  if ((ItbtPcieRootPortExisted == TRUE) && (TcssPeiPreMemConfig->MiscConfig.PcieMultipleSegmentEnabled == 1)) {
    PciexBarReg = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_PCIEXBAR));
    PciexBarReg = ((PciexBarReg & ~(B_SA_PCIEXBAR_LENGTH_MASK)) | (V_SA_PCIEXBAR_LENGTH_512MB << N_SA_PCIEXBAR_LENGTH_OFFSET));
    PciSegmentWrite32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_PCIEXBAR), PciexBarReg);
    PcdSet32S (PcdPciExpressRegionLength, SIZE_512MB);
  }
#endif
  ///
  /// According to TcssPeiPreMemConfig and each iTBT PCIe RP enable status to update Segment Map.
  ///
  if (TcssPeiPreMemConfig->MiscConfig.PcieMultipleSegmentEnabled) {
    ///
    /// Program all enabled iTBT PCIe RP to Segment1
    ///
    PcieSegMap = (ItbtPcieRootPortEnabled[0] << N_SA_PCIESEGMAP_PCIE0SEG_OFFSET |
                  ItbtPcieRootPortEnabled[1] << N_SA_PCIESEGMAP_PCIE1SEG_OFFSET |
                  ItbtPcieRootPortEnabled[2] << N_SA_PCIESEGMAP_PCIE2SEG_OFFSET |
                  ItbtPcieRootPortEnabled[3] << N_SA_PCIESEGMAP_PCIE3SEG_OFFSET);
  }
  ///
  /// According to each iTBT PCIe RP enable status to update Function Map.
  ///
  for (Index = 0; Index < MAX_ITBT_PCIE_PORT; Index++) {
    ItbtPcieFunctionNumber[Index] = Index;
    //
    // Swap the function number if the first enabled iTBT PCIe RP is not port0.
    //
    if ((Index != 0) && (FirstEnabledItbtPortNumber == Index)) {
      ItbtPcieFunctionNumber[Index] = 0;
      ItbtPcieFunctionNumber[0] = Index;
    }
  }
  for (Index = 0; Index < MAX_ITBT_PCIE_PORT; Index++) {
    ///
    /// Program RP0FN for each iTBT PCIE Root Port if it is enabled then lock the register.
    /// Since currently we only defined PortId for PCIe0 ~ PCIe3, so we only program it for these 4 ports.
    ///
    CpuRegbarWrite32 (PciePortIdMap[Index], R_TCSS_PCIEX_PCD, ItbtPcieFunctionNumber[Index]);
  }
  PcieFuncMap = (ItbtPcieFunctionNumber[0] << N_SA_PCIEFUNCMAP_PCIE0FUNC_OFFSET |
                 ItbtPcieFunctionNumber[1] << N_SA_PCIEFUNCMAP_PCIE1FUNC_OFFSET |
                 ItbtPcieFunctionNumber[2] << N_SA_PCIEFUNCMAP_PCIE2FUNC_OFFSET |
                 ItbtPcieFunctionNumber[3] << N_SA_PCIEFUNCMAP_PCIE3FUNC_OFFSET);

  PciSegmentWrite32 (McD0BaseAddress + R_SA_PCIESEGMAP, PcieSegMap);
  PciSegmentWrite32 (McD0BaseAddress + R_SA_PCIEFUNCMAP, PcieFuncMap);

  ///
  /// Update SA HOB's TCSS data TBT variables for Segment and function
  ///
  TcssHob = NULL;
  TcssHob = (TCSS_DATA_HOB *) GetFirstGuidHob (&gTcssHobGuid);

  if (TcssHob != NULL) {
    if ((ItbtPcieRootPortExisted == TRUE) && (TcssPeiPreMemConfig->MiscConfig.PcieMultipleSegmentEnabled == 1)) {
      TcssHob->TcssData.PcieMultipleSegmentEnabled = 1;
    } else {
      TcssHob->TcssData.PcieMultipleSegmentEnabled = 0;
    }
    TcssHob->TcssData.ItbtPcieSegMap  = PcieSegMap;
    TcssHob->TcssData.ItbtPcieFuncMap = PcieFuncMap;
    DEBUG ((DEBUG_INFO, "TcssHob->TcssData.PcieMultipleSegmentEnabled = %x\n", TcssHob->TcssData.PcieMultipleSegmentEnabled));
  }

  DEBUG ((DEBUG_INFO, "R_SA_PCIESEGMAP = %x, R_SA_PCIEFUNCMAP = %x\n", PciSegmentRead32 (McD0BaseAddress + R_SA_PCIESEGMAP), PciSegmentRead32 (McD0BaseAddress + R_SA_PCIEFUNCMAP)));
  DEBUG ((DEBUG_INFO, "[TCSS] ConfigureTbtPcieSegFuncMap() - End\n"));
}

/**
  This function initializes Aux and HSL Orientation registers in IOM.

  @param[in] IomConfig            Pointer to TCSS_IOM_PEI_CONFIG struct containing IOM configuration.
**/
VOID
TcssInitAuxHslOri (
  IN TCSS_IOM_PEI_CONFIG          *IomConfig
  )
{
  UINT32                          AuxOriReg;
  UINT32                          HslOriReg;

  ///
  /// Set IOM Aux Orientation per configuration.
  ///
  DEBUG ((DEBUG_INFO, "[TCSS] TcssInitAuxHslOri() - Start\n"));

  AuxOriReg = CpuRegbarRead32 (CPU_SB_PID_IOM, R_SA_IOM_AUX_ORI_OFFSET);
  DEBUG ((DEBUG_INFO, "Origional AuxOriReg: 0x%08X\n", AuxOriReg));
  DEBUG ((DEBUG_INFO, "IomConfig->IomOverrides.AuxOri: 0x%08X\n", (UINT32)IomConfig->IomOverrides.AuxOri));
  CpuRegbarWrite32(CPU_SB_PID_IOM, R_SA_IOM_AUX_ORI_OFFSET, (UINT32)IomConfig->IomOverrides.AuxOri);
  AuxOriReg = CpuRegbarRead32 (CPU_SB_PID_IOM, R_SA_IOM_AUX_ORI_OFFSET);
  CpuRegbarWrite32(CPU_SB_PID_IOM, R_SA_IOM_AUX_ORI_OFFSET, AuxOriReg | B_SA_IOM_AUX_ORI_LOCK);
  DEBUG ((DEBUG_INFO, "Update AuxOri: 0x%08X\n", CpuRegbarRead32 (CPU_SB_PID_IOM, R_SA_IOM_AUX_ORI_OFFSET)));

  ///
  /// Set IOM HSL Orientation per configuration.
  ///
  HslOriReg = CpuRegbarRead32 (CPU_SB_PID_IOM, R_SA_IOM_HSL_ORI_OFFSET);
  DEBUG ((DEBUG_INFO, "Origional HslOriReg: 0x%08X\n", HslOriReg));
  DEBUG ((DEBUG_INFO, "IomConfig->IomOverrides.HslOri: 0x%08X\n", (UINT32)IomConfig->IomOverrides.HslOri));
  CpuRegbarWrite32(CPU_SB_PID_IOM, R_SA_IOM_HSL_ORI_OFFSET, (UINT32)IomConfig->IomOverrides.HslOri);
  HslOriReg = CpuRegbarRead32 (CPU_SB_PID_IOM, R_SA_IOM_HSL_ORI_OFFSET);
  CpuRegbarWrite32(CPU_SB_PID_IOM, R_SA_IOM_HSL_ORI_OFFSET, HslOriReg | B_SA_IOM_AUX_ORI_LOCK);
  DEBUG ((DEBUG_INFO, "Update HslOri: 0x%08X\n", CpuRegbarRead32 (CPU_SB_PID_IOM, R_SA_IOM_HSL_ORI_OFFSET)));

  DEBUG ((DEBUG_INFO, "[TCSS] TcssInitAuxHslOri() - End\n"));

}


/**
  This function performs basic initialization IOM for AUX Layout in PEI phase after Policy produced at Post-Mem phase.

  For those GPIO pins used for DP Aux orientation control and enabled, BIOS is responsible to -
  1. Configure Pad Mode (PMode) to function# associated with IOM_GPP*_*
     The Pad Mode here could be various per PCH design. For ICL-LP, N and H, it is Native Function 6.
  2. BIOS Provide the following information for the DP Aux orientation bias control for all supported Type-C ports
     to IOM FW
     I. GPIO endpoint IOSF-SB port ID (CPU local port ID)
     II. VW index and data bit position

  @param[in] ConfigTablePtr - Instance pointer of IOM_AUX_ORI_PAD_CONFIG_HEAD

**/
EFI_STATUS
IomAuxOriSetting (
  IN TCSS_IOM_PEI_CONFIG      *ConfigTablePtr
  )
{
  UINT8                       Index;
  UINT8                       PadIndex;
  IOM_AUX_ORI_BIAS_STRUCTURE  RegSetting;
  UINT32                      PadRegAddr[2];
  UINT32                      PadRegValue;
  UINT16                      RegAddr;
  UINT8                       PchPid;
  GPIO_CONFIG                 PadConfig;

  ///
  /// BIOS communicate the PCH AUX layout with IOM
  ///
  for (Index = 0; Index < MAX_IOM_AUX_BIAS_COUNT; Index++) {

    PadRegAddr[0] = ConfigTablePtr->IomAuxPortPad[Index].GpioPullN;
    PadRegAddr[1] = ConfigTablePtr->IomAuxPortPad[Index].GpioPullP;
    RegSetting.RegValue = 0;

    //
    // GPIO setting is NULL go to check next port config
    //
    if ((PadRegAddr[0] == 0) || (PadRegAddr[1] == 0)) {
      continue;
    }

    ZeroMem (&PadConfig, sizeof (GPIO_CONFIG));

    ///
    /// Up Ping and down ping loop start
    ///
    for (PadIndex = 0; PadIndex < 2; PadIndex++) {

      ///
      /// Configure Pad Mode (PMode) to function# associated with IOM_GPP*_*
      /// The Pad Mode here could be various per PCH design. For ICL-LP, N and H, it is Native Function 6
      ///
      PadConfig.PadMode = GpioPadModeNative6;                // Set to IOM mode
      GpioSetPadConfig ((GPIO_PAD) PadRegAddr[PadIndex], &PadConfig);

      ///
      /// 0 is up and 1 is down
      ///
      PadRegValue =  PadRegAddr[PadIndex];

      ///
      /// Update GPIO Family portID bit[7:0]
      ///
      PchPid = GpioGetGpioCommunityPortIdFromGpioPad(PadRegValue);

      //
      //  GPIO PID Translation table
      //         PCH PID  CPU PID
      //  GPCOM0 0x6E     0xB7
      //  GPCOM1 0x6D     0xB8
      //  GPCOM4 0x6A     0xB9
      //  GPCOM5 0x69     0xBA
      //  GPCOM3 0x6B     0xBB
      //
      ///
      /// Translated PCH PID to CPU PID
      ///
      switch (PchPid) {
        case PID_GPIOCOM0:
          RegSetting.Bits.GpioPortId = 0xB7;
          break;
        case PID_GPIOCOM1:
          RegSetting.Bits.GpioPortId = 0xB8;
          break;
        case PID_GPIOCOM4:
          RegSetting.Bits.GpioPortId = 0xB9;
          break;
        case PID_GPIOCOM5:
          RegSetting.Bits.GpioPortId = 0xBA;
          break;
        case PID_GPIOCOM3:
          RegSetting.Bits.GpioPortId = 0xBB;
          break;
        default:
          RegSetting.Bits.GpioPortId = PchPid;
      }

      ///
      /// Update Bit Position bit[10:8]
      ///
      RegSetting.Bits.Bit = (PadRegValue & 0xff) % 8;

      ///
      /// Vw Index update bit[23:16]
      ///
      RegSetting.Bits.VwIndex = (PadRegValue >> 16) & 0x0f;
      switch (RegSetting.Bits.VwIndex) {
        //
        // VW Index 10h - 12h
        //
        case 0: // GPP_A
        case 3: // GPP_D
        case 2: // GPP_C
           RegSetting.Bits.VwIndex = ((PadRegValue & 0xff) / 8) + 0x10;
          break;
        //
        // VW Index 13h - 15h
        //
        case 1: // GPP_B
        case 5: // GPP_F
        case 4: // GPP_E
           RegSetting.Bits.VwIndex = ((PadRegValue & 0xff) / 8) + 0x13;
          break;
        //
        // VW Index 16h - 18h
        //
        case 6: // GPP_G
        case 7: // GPP_H
           RegSetting.Bits.VwIndex = ((PadRegValue & 0xff) / 8) + 0x16;
          break;

        default:
           RegSetting.Bits.VwIndex = 0xFF;
      }

      //
      // Get correspond AUX BIAS CTRL offset
      //
      if (PadIndex == 0) {
        RegAddr = R_SA_IOM_AUX_ORI_BIAS_CTRL_PUP_MMOFFSET_1 + (Index*4);  // Up Pin
      } else {
        RegAddr = R_SA_IOM_AUX_ORI_BIAS_CTRL_PDN_MMOFFSET_1 + (Index*4);  // Down Pin
      }

      //
      // Set register
      //
      CpuRegbarWrite32 (CPU_SB_PID_IOM, RegAddr, RegSetting.RegValue);

      DEBUG ((DEBUG_INFO, "[TCSS] IomAuxOriConfig : Regaddr %08x, RegValue %08x\n",RegAddr, RegSetting.RegValue));

    }
    // Up pin and Down pin Loop End

  }

  return EFI_SUCCESS;
}

/**
  IomReadyCheck - This function performs IOM ready state

  This function does the following steps:
  (1) Examines IOM_READY (Register IOM_TYPEC_STATUS_1, bit 30)
  (2) If 0, retry in IOM_READY_TIMEOUT ms (1ms timeout)
  (3) Save success/failure in Tcss HOB
  (4) Print success/failure
**/
EFI_STATUS
EFIAPI
IomReadyCheck (
  VOID
  )
{
  BOOLEAN                         IomReady;
  TCSS_DATA_HOB                   *TcssHob;

  TcssHob = NULL;
  DEBUG ((DEBUG_INFO, "[TCSS] IomReadyCheck - Start\n"));

  IomReady = ((CpuRegbarRead32 (CPU_SB_PID_IOM,R_SA_IOM_TYPEC_STATUS_1)) & B_SA_IOM_IOM_READY) ? TRUE: FALSE;

  if (!IomReady) {
    //
    // Try again after 1ms if failed
    //
    DEBUG ((DEBUG_INFO, "IOM is not ready. Trying again ..\n"));
    MicroSecondDelay (1000);
    IomReady = ((CpuRegbarRead32 (CPU_SB_PID_IOM,R_SA_IOM_TYPEC_STATUS_1)) & B_SA_IOM_IOM_READY) ? TRUE: FALSE;
  }

  DEBUG ((DEBUG_INFO, "IOMReady bit = %d\n", (int)IomReady));

  ///
  /// Locate HOB for TCSS Data and save IOM ready state/version
  ///
  TcssHob = (TCSS_DATA_HOB *) GetFirstGuidHob (&gTcssHobGuid);
  if (TcssHob != NULL) {
    TcssHob->TcssData.IOMReady = IomReady;
    if (IomReady) {   ///< Pull the version if IOM is detected and save
      TcssHob->TcssData.IomFwVersion = CpuRegbarRead32 (CPU_SB_PID_IOM, R_SA_IOM_FW_INFO);
      TcssHob->TcssData.IomFwEngrVersion = CpuRegbarRead32 (CPU_SB_PID_IOM, R_SA_IOM_FW_INFO_ENGR);
      DEBUG ((DEBUG_INFO, "IomReady bit updated to TCSS HOB\n"));
      DEBUG ((DEBUG_INFO, "\tIOM version: 0x%08X; Engr version: 0x%08X\n", TcssHob->TcssData.IomFwVersion, TcssHob->TcssData.IomFwEngrVersion));
    }
    DEBUG ((DEBUG_INFO, "\tTCSS HOB updated\n"));
  }

  if (!IomReady){
    DEBUG ((DEBUG_INFO, "\tIomReadyCheck Failed!\n"));
    return EFI_UNSUPPORTED;
  }
  DEBUG ((DEBUG_INFO, "[TCSS] IomReadyCheck - End\n"));
  return EFI_SUCCESS;

}

/**
  SaXdciIrq - This function program SA Xdci Irq

  @param[in] InterruptPin - SA XDCI Interrup Pin Number
  @param[in] IrqNumber - SA XDCI IRQ number
**/
VOID
SaXdciIrq (
  IN UINT8 InterruptPin,
  IN UINT8 IrqNumber
  )
{
  TCSS_DATA_HOB    *TcssHob;
  UINT32           SaIomMailBoxData;
  UINT32           Cmd;
  UINT32           CmdCount;

  TcssHob = NULL;
  CmdCount = 0;
  DEBUG ((DEBUG_INFO, "[TCSS] SaXdciIrq - Start\n"));

  //
  // Set Interrupt Pin and IRQ number
  //
  SaIomMailBoxData = (UINT32) ((InterruptPin << N_OTG_PCR_PCICFGCTRL_INT_PIN) |
                        (IrqNumber << N_OTG_PCR_PCICFGCTRL_PCI_IRQ));

  //
  // BIOS updates SA XDCI IRQ setting via IOM mail box.
  //
  CpuRegbarWrite32 (CPU_SB_PID_IOM, R_SA_IOM_BIOS_MAIL_BOX_DATA, SaIomMailBoxData);
  DEBUG ((DEBUG_INFO, "IOM mailbox SaXdci Irq data = 0x%08X\n", SaIomMailBoxData));

  Cmd = V_SA_IOM_BIOS_GEM_SB_TRAN_CMD | (V_SA_IOM_BIOS_CMD_TYPE_XDCI_INT << 8);
  CpuRegbarWrite32 (CPU_SB_PID_IOM, R_SA_IOM_BIOS_MAIL_BOX_CMD, Cmd);
  DEBUG ((DEBUG_INFO, "IOM mailbox command = 0x%08X\n", Cmd));

  //
  // Set the Run/Busy bit to signal mailbox data is ready to process. IOM FW is not yet
  // out of reset at this point, so don't wait for response.
  //
  Cmd |= B_SA_IOM_BIOS_SET_TO_RUN;
  CpuRegbarWrite32 (CPU_SB_PID_IOM, R_SA_IOM_BIOS_MAIL_BOX_CMD, Cmd);

  //
  // Waiting IOM complete V_SA_IOM_BIOS_GEM_SB_TRAN_CMD.
  // Time out is 1sec
  //
  while ((CmdCount < 10000) && \
     ((CpuRegbarRead32(CPU_SB_PID_IOM, R_SA_IOM_BIOS_MAIL_BOX_CMD) & B_SA_IOM_BIOS_SET_TO_RUN) != 0)) {
    CmdCount++;
    MicroSecondDelay (100);
  }

  TcssHob = (TCSS_DATA_HOB *) GetFirstGuidHob (&gTcssHobGuid);
  if (TcssHob != NULL) {
    TcssHob->TcssData.TcssxDCIInt = InterruptPin;
    TcssHob->TcssData.TcssxDCIIrq = IrqNumber;
    DEBUG ((DEBUG_INFO, "SA xDCI Int pin: 0x%02X\n", TcssHob->TcssData.TcssxDCIInt));
    DEBUG ((DEBUG_INFO, "SA xDCI Irq: 0x%02X\n", TcssHob->TcssData.TcssxDCIIrq));
  }
  DEBUG ((DEBUG_INFO, "[TCSS] SaXdciIrq - End\n"));
}

/**
  This function configs IOM_TYPEC_SW_CONFIGURATION_1 register crid bit
**/
VOID
TcssCridEnable (
  VOID
  )
{
  UINT32         IomTypecConfigValue;
  UINT16         IomTypecSwConfig1Reg;
  UINT32         Status;

  DEBUG ((DEBUG_INFO, "[TCSS] TcssCridEnable() - Start\n"));

  IomTypecSwConfig1Reg = (UINT16)R_SA_IOM_TYPEC_SW_CONFIGURATION_1;


  //
  // Read IOM_TYPEC_SW_CONFIGURATION_1
  // Set BIT 18 if Crid enable
  //
  IomTypecConfigValue = CpuRegbarRead32 (CPU_SB_PID_IOM, IomTypecSwConfig1Reg);
  IomTypecConfigValue |= B_SA_IOM_TYPEC_SW_CONFIGURATION_1_CRID_EN;

  //
  // Write to IOM_TYPEC_SW_CONFIGURATION_1
  //
  Status = CpuRegbarWrite32 (CPU_SB_PID_IOM, IomTypecSwConfig1Reg, IomTypecConfigValue);
  if (Status == INVALID_DATA_32) {
    DEBUG ((DEBUG_INFO, "CpuRegbarWrite32 Fail\n"));
  } else {
    DEBUG ((DEBUG_INFO, "TCSS CRID is enable\n"));
  }

  DEBUG ((DEBUG_INFO, "[TCSS] TcssCridEnable() - End\n"));
}

/**
  TcssRtd3InfoUpdate - This function update TCSS RTD3 information into Hob

  @param[in] TcssConfig           Pointer to config block
**/
VOID
TcssRtd3InfoUpdate (
  IN  TCSS_PEI_CONFIG             *TcssPeiConfig
  )
{
  TCSS_DATA_HOB      *TcssHob;

  TcssHob = NULL;
  DEBUG ((DEBUG_INFO, "[TCSS] TcssRtd3Update - Start\n"));

  TcssHob = (TCSS_DATA_HOB *) GetFirstGuidHob (&gTcssHobGuid);
  if (TcssHob != NULL) {
    if (TcssPeiConfig->IomConfig.IomInterface.D3ColdEnable == 1) {
      TcssHob->TcssData.TcssRtd3 = TRUE;
    }
    DEBUG ((DEBUG_INFO, "TCSS RTD3: 0x%X\n", TcssHob->TcssData.TcssRtd3));
  }
  DEBUG ((DEBUG_INFO, "[TCSS] TcssRtd3Update - End\n"));
}

/**
  TcssIomVccStInfoUpdate - This function update TCSS IOM VccSt information into Hob

  @param[in] TcssConfig           Pointer to config block
**/
VOID
TcssIomVccStInfoUpdate (
  IN  TCSS_PEI_CONFIG             *TcssPeiConfig
  )
{
  TCSS_DATA_HOB      *TcssHob;

  TcssHob = NULL;
  DEBUG ((DEBUG_INFO, "[TCSS] TcssIomVccStInfoUpdate - Start\n"));

  TcssHob = (TCSS_DATA_HOB *) GetFirstGuidHob (&gTcssHobGuid);
  if (TcssHob != NULL) {
    TcssHob->TcssData.TcssIomVccSt = (UINT8) TcssPeiConfig->IomConfig.IomInterface.VccSt;
    DEBUG ((DEBUG_INFO, "TCSS IOM VccSt: 0x%X\n", TcssHob->TcssData.TcssIomVccSt));
  }
  DEBUG ((DEBUG_INFO, "[TCSS] TcssIomVccStInfoUpdate - End\n"));
}

/**
  This function performs basic initialization for TCSS in PEI phase after Policy produced at Pre-Mem phase.

  @param[in]  TcssConfig              Pointer to TCSS config block
  @param[in]  MiscSaPeiPreMemConfig   Pointer to SA miscellaneous config block
**/
VOID
EFIAPI
TcssPreMemInit (
  IN TCSS_PEI_PREMEM_CONFIG      *TcssPeiPreMemConfig,
  IN SA_MISC_PEI_PREMEM_CONFIG   *MiscSaPeiPreMemConfig
  )
{
  EFI_STATUS                      Status;
  EFI_BOOT_MODE                   BootMode;

  DEBUG ((DEBUG_INFO, "[TCSS] TcssPreMemInit() - Start\n"));

  //
  // Performing Tcss PreMem initialization from here.
  //
  PeiServicesGetBootMode (&BootMode);
  //
  // Install TCSS Data Hob
  //
  DEBUG ((DEBUG_INFO, "Install TCSS DATA HOB\n"));
  InstallTcssDataHob();

  ///
  /// Configure hardware register TCSS_DEVEN_0_0_0_MCHBAR_IMPH
  ///
  TcssDevEnInitPreMem(TcssPeiPreMemConfig);

  ///
  /// Per USB-C spec, the SBU pins are required to be in high-Z/Open circuit in unused state
  /// (e.g.USB mode or SAFE mode) if debug is disabled for the correspodning Type-C port. As the
  /// BIOS has the ultimate information of the USB-C ports that are enabled on the platform, BIOS
  /// is required to initialize the PCH USB-C pins to high-Z/Open circuite prior to IOM CRRd to PMC
  /// only if
  /// 1.ExI.ECTRL.DEBUG.ENABLED = 0
  /// 2.After Platform Reset de-assertion
  ///

  if ((BootMode != BOOT_ON_S3_RESUME) && (BootMode != BOOT_ON_S4_RESUME) && (!IsDciDebugEnabled())) {
    //
    // When debug is disabled
    //
    DEBUG((DEBUG_INFO, "Configure PCH SBU pins\n"));
    Status = GpioDisableTypeCSbuDebug((UINT8)TcssPeiPreMemConfig->UsbTcConfig.UsbTcPortEn);
    if (EFI_ERROR(Status)) {
      DEBUG((DEBUG_ERROR, "Fail to configure PCH SBU pins, Status = %r\n", Status));
    }
  }

  //
  // Enable Crid if it's needed
  //
  if (MiscSaPeiPreMemConfig->CridEnable == TRUE) {
    TcssCridEnable();
  }

  DEBUG ((DEBUG_INFO, "[TCSS] TcssPreMemInit() - End\n"));
}

/**
  Entrypoint to perform basic initialization for TCSS in PEI phase after Policy produced at Post-Mem phase.

  This function does the following steps:
  (1) Check IOM Ready bit.
  (2) If IOM is ready, then programs VCCST, REPLAY and CONNECTION_OVERRIDE setting.
  (3) If IOM is ready, then programs AUX/HSL orientation support per platform design
  (4) Do iTBT PCIE RP programming
  (5) Start iTBT specific BIOS support
  (6) Init TCSS USB controllers (xHCI and xDCI)
  (7) Handshake with PMC if PMC handshaking support is enabled

  @param[in] SiPolicy             The SI Policy PPI instance
  @param[in] TcssPeiPreMemConfig  Pointer to config block
  @param[in] TcssConfig           Pointer to config block
**/
VOID
EFIAPI
TcssInit (
  IN  SI_POLICY_PPI               *SiPolicy,
  IN  TCSS_PEI_PREMEM_CONFIG      *TcssPeiPreMemConfig,
  IN  TCSS_PEI_CONFIG             *TcssPeiConfig
  )
{
  UINT64                          McD0BaseAddress;
  UINT32                          MchBar;
  UINT32                          IomTypecConfigValue;
  UINT16                          IomTypecSwConfig1Reg;
  EFI_STATUS                      IomReadyStatus;
  UINT64                          XhciPciBase;
  UINT64                          XdciPciBase;
  UINT8                           PmcReplay;
  EFI_BOOT_MODE                   BootMode;
  TCSS_DATA_HOB                   *TcssHob;

  //
  // Performing Tcss initialization from here.
  //
  DEBUG ((DEBUG_INFO, "[TCSS] TcssInit() - Start\n"));

  TcssHob = NULL;
  McD0BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, 0);
  MchBar = PciSegmentRead32 (McD0BaseAddress + R_SA_MCHBAR) & ~B_SA_MCHBAR_MCHBAREN_MASK;

  TcssHob = (TCSS_DATA_HOB *) GetFirstGuidHob (&gTcssHobGuid);
  if (TcssHob == NULL) {
    ASSERT (FALSE);
    return;
  }

  ///
  /// BIOS <-> IOM Handshake
  ///

  ///
  /// Step 1 - Perform IOM/USBC ready check
  ///
  IomReadyStatus = IomReadyCheck ();
  if (!IsSimicsEnvironment ()) {
    ASSERT_EFI_ERROR (IomReadyStatus);
    if (EFI_ERROR (IomReadyStatus)) {
      //
      // Clear the TCSS DEVEN register when IOM is corrupted
      //
      MmioWrite32 (MchBar + R_SA_MCHBAR_TCSS_DEVEN_OFFSET, 0);
      return;
    }
  }
  if (TcssHob->TcssData.ItbtXhciEn == 0) {
    DEBUG ((DEBUG_INFO, "[TCSS] CPU XHCI is disabled, skip whole TCSS initialization\n"));
    return;
  }

  ///
  /// Step 2 - If IOM is ready, then programs VCCST, REPLAY and CONNECTION_OVERRIDE setting
  ///

  if (IomReadyStatus == EFI_SUCCESS) {
    IomTypecSwConfig1Reg = (UINT16)R_SA_IOM_TYPEC_SW_CONFIGURATION_1;

    //
    // Read IOM_TYPEC_SW_CONFIGURATION_1
    //
    IomTypecConfigValue = CpuRegbarRead32 (CPU_SB_PID_IOM,IomTypecSwConfig1Reg);

    //
    // CLEAR BITS of IOM_TYPEC_SW_CONFIGURATION_1
    //
    IomTypecConfigValue &= ~(B_SA_IOM_UNWAKEBLE_SX | BIOS_EC_REPLAY_CONNECTION_S4S5 | BIOS_EC_REPLAY_CONNECTION_S3 | B_SA_IOM_D3_HOT_ENABLE | B_SA_IOM_D3_COLD_ENABLE | B_SA_IOM_USB_CONNECT_OVERRIDE);

    if (TcssPeiConfig->IomConfig.IomInterface.VccSt == 0) {
      //
      // SET BIT 13 of IOM_TYPEC_SW_CONFIGURATION_1
      //
      IomTypecConfigValue |= (B_SA_IOM_UNWAKEBLE_SX | BIOS_EC_REPLAY_CONNECTION_S4S5);
    }

    //
    // Enable D3 Hot based on policy.
    //
    if (TcssPeiConfig->IomConfig.IomInterface.D3HotEnable == 1) {
      //
      // SET BIT 8 of IOM_TYPEC_SW_CONFIGURATION_1
      //
      IomTypecConfigValue |= B_SA_IOM_D3_HOT_ENABLE;
    }

    //
    // Enable D3 Cold based on policy.
    //
    if (TcssPeiConfig->IomConfig.IomInterface.D3ColdEnable == 1) {
      //
      // SET BIT 9 of IOM_TYPEC_SW_CONFIGURATION_1
      //
      IomTypecConfigValue |= B_SA_IOM_D3_COLD_ENABLE;
    }

    TcssRtd3InfoUpdate (TcssPeiConfig);

    //
    // Set USB Override based on policy.
    //
    if (TcssPeiConfig->IomConfig.IomInterface.UsbOverride == 1) {
      //
      // SET BIT 13 of IOM_TYPEC_SW_CONFIGURATION_1
      //
      IomTypecConfigValue |= B_SA_IOM_USB_CONNECT_OVERRIDE;
    }

    //
    // Write to IOM_TYPEC_SW_CONFIGURATION_1
    //
    CpuRegbarWrite32 (CPU_SB_PID_IOM, IomTypecSwConfig1Reg, IomTypecConfigValue);

    //
    // Configure SA xDCI Interrupt
    //
    SaXdciIrq(TcssPeiConfig->MiscConfig.SaXdci.IntPing, TcssPeiConfig->MiscConfig.SaXdci.Irq);

  }


  ///
  /// Step3 - Configuring AUX orientation to IOM
  ///
  IomAuxOriSetting (&TcssPeiConfig->IomConfig);
  TcssInitAuxHslOri (&TcssPeiConfig->IomConfig);

  ///
  /// Step 4 & 5- Configuring TBT PCIe Segment and Function number
  ///
  ConfigureTbtPcieSegFuncMap (TcssPeiPreMemConfig);

  ///
  /// Initiazlize TBT PCI Root Ports
  ///
  ItbtInitRootPorts(TcssPeiConfig);

  ///
  /// Step 6 - Init TCSS USB controllers (xHCI and xDCI)
  ///
  //
  // Configure Tcss xHCI
  //
  XhciPciBase = PCI_SEGMENT_LIB_ADDRESS (
                  SA_SEG_NUM,
                  SA_XHCI_NORTH_BUS_NUM,
                  SA_XHCI_NORTH_DEV_NUM,
                  SA_XHCI_NORTH_FUNC_NUM,
                  0
                  );
  XhciConfigure (&(TcssPeiConfig->UsbConfig), XhciPciBase);

  //
  // Set all necessary lock bits in xHCI controller
  //
  XhciLockConfiguration (&(TcssPeiConfig->UsbConfig), XhciPciBase);

  //
  // Configure Tcss xDCI
  //
  XdciPciBase = PCI_SEGMENT_LIB_ADDRESS (
                  SA_SEG_NUM,
                  SA_XDCI_NORTH_BUS_NUM,
                  SA_XDCI_NORTH_DEV_NUM,
                  SA_XDCI_NORTH_FUNC_NUM,
                  0
                  );
  XdciConfigure (&(TcssPeiConfig->UsbConfig), XdciPciBase);

  ///
  /// Step 7 - Handshake with PMC if PMC handshaking support is enabled
  ///          BIOS sends TCSS_BIOS_INIT Done (aka.USBC connection replay)
  ///          message along with USBC connctions replay setting to PMC.
  ///          All TCSS initialization is expected to be done before PMC
  ///          do any port negotiation. The indicator sent from BIOS to
  ///          PMC should be treated as TCSS BIOS initialization done
  ///          semaphore.


  ///
  /// BIOS <-> PMC Handshake
  ///
  if (TcssPeiConfig->IomConfig.PmcInterface.PmcPdEnable) {
    PeiServicesGetBootMode (&BootMode);
    PmcReplay = 1;
    if (BootMode == BOOT_ON_S3_RESUME) {
      PmcReplay = 0;
    }
    if (((BootMode == BOOT_ON_S4_RESUME) || (BootMode == BOOT_ON_S5_RESUME)) &&
      (TcssPeiConfig->IomConfig.IomInterface.VccSt != 0)) {
        PmcReplay = 0;
    }
    PmcTcssBiosInitDone (IomReadyStatus, PmcReplay);
  }

  TcssIomVccStInfoUpdate (TcssPeiConfig);

  //
  // Performing TcssInitEndOfPei after EndOfPei PPI produced
  //
  PeiServicesNotifyPpi (&mEndOfPeiNotifyList);

  DEBUG ((DEBUG_INFO, "[TCSS] TcssInit() - End\n"));
}

