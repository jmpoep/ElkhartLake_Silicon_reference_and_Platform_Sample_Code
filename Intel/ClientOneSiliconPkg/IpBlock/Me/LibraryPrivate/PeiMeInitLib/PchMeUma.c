/** @file
  Framework PEIM to PchMeUma

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2019 Intel Corporation.

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

#include <PiPei.h>
#include <Library/DebugLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PerformanceLib.h>
#include <Library/IoLib.h>
#include <Library/TimerLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/PeiMeLib.h>
#include <Library/MeTypeLib.h>
#include <Ppi/SiPolicy.h>
#include <Ppi/Wdt.h>
#include <Register/MeRegs.h>
#include <Register/HeciRegs.h>
#include <MeDataHob.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <PchResetPlatformSpecific.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PostCodeLib.h>
#include <Library/PeiPcieRpLib.h>
#include <Library/PmcPrivateLib.h>
#include <Library/PeiHdaLib.h>
#include <Library/PeiIshLib.h>
#include <Library/PeiPseLib.h>
#include <Library/CnviLib.h>
#include <Library/CpuPcieInfoLib.h>
#include <Library/IpuInitLib.h>
#include <Library/SaPlatformLib.h>

//
// ME FW communication timeout value definitions
//
#define CPURV_TIMEOUT_MULTIPLIER  50         // 50 ms
#define STALL_1_MILLISECOND       1000

EFI_PEI_PPI_DESCRIPTOR mMeDidSendPpi = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gMeDidSentPpiGuid,
  NULL
};
EFI_PEI_PPI_DESCRIPTOR mMeBeforeDidSendPpi = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gMeBeforeDidSentPpiGuid,
  NULL
};

//
// Internal Function Declarations
//

/**
  Init and Install ME Hob
**/
VOID
InstallMeHob (
  VOID
  )
{
  EFI_STATUS                      Status;
  ME_DATA_HOB                     *MeDataHob;

  ///
  /// Create HOB for ME Data
  ///
  Status = PeiServicesCreateHob (
             EFI_HOB_TYPE_GUID_EXTENSION,
             sizeof (ME_DATA_HOB),
             (VOID **) &MeDataHob
             );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Initialize default HOB data
  ///
  MeDataHob->EfiHobGuidType.Name = gMeDataHobGuid;
  MeDataHob->LocalityState = 0;

  DEBUG ((DEBUG_INFO, "ME Data HOB installed\n"));

  return;
}

/**
  This procedure will issue a Non-Power Cycle, Power Cycle, or Global Rest.
  It should not return.

  @param[in] ResetType            Type of reset to be issued.
**/
VOID
PerformReset (
  IN UINT8        ResetType
  )
{
  EFI_STATUS      Status;
  WDT_PPI         *Wdt;
  EFI_RESET_TYPE  Reset;
  PCH_RESET_DATA  ResetData;
  UINTN           ResetDataSize;

  Wdt           = NULL;
  ResetDataSize = 0;

  ///
  /// Locate WDT PPI for access to Wdt->AllowKnownReset()
  ///
  Status = PeiServicesLocatePpi (
             &gWdtPpiGuid,
             0,
             NULL,
             (VOID **) &Wdt
             );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Clear CF9GR of PCH to indicate Host reset
  /// Make sure CF9 Without Resume Well Reset is disabled
  ///
  PmcDisableCf9GlobalReset ();
  PmcDisableCf9ResetWithoutResumeWell ();

  switch (ResetType) {
    case DID_ACK_NON_PCR:
      DEBUG ((DEBUG_INFO, "ME FW DID ACK has requested a Non Power Cycle Reset.\n"));
      Reset = EfiResetWarm;
      break;

    case DID_ACK_PCR:
      DEBUG ((DEBUG_INFO, "ME FW DID ACK has requested a Power Cycle Reset.\n"));
      Reset = EfiResetCold;
      Wdt->ReloadAndStart (2);
      break;

    case DID_ACK_GRST:
      DEBUG ((DEBUG_INFO, "ME FW DID Ack requested a global reset.\n"));
      Reset = EfiResetPlatformSpecific;
      CopyMem (&ResetData.Guid, &gPchGlobalResetGuid, sizeof (EFI_GUID));
      StrCpyS (ResetData.Description, PCH_RESET_DATA_STRING_MAX_LENGTH, PCH_PLATFORM_SPECIFIC_RESET_STRING);
      ResetDataSize = sizeof (PCH_RESET_DATA);
      break;

    default:
      return;
  }

  Wdt->AllowKnownReset ();
  (*GetPeiServicesTablePointer ())->ResetSystem2 (Reset, EFI_SUCCESS, ResetDataSize, &ResetData);
}

/**
  This procedure will enforce the BIOS Action that was requested by ME FW
  as part of the DRAM Init Done message.

  @param[in] BiosAction           CSME requested BIOS Action
**/
VOID
HandleMeBiosAction (
  IN UINT8                        BiosAction
  )
{

  switch (BiosAction) {

    case DID_ACK_NON_PCR:
    case DID_ACK_PCR:
    case DID_ACK_GRST:
      PerformReset (BiosAction);
      ASSERT (FALSE);
      break;

    default:
      DEBUG ((DEBUG_INFO, "BIOS continues to POST.\n"));
      break;
  }
}

//
// RC Private Function Declarations
//

/**
  This procedure will determine whether or not the CPU was replaced
  during system power loss or via dynamic fusing.
  Calling this procedure could result in a warm reset (if ME FW is requesting one).

  @param[in] FfsHeader            Not used.
  @param[out] ForceFullTraining   When set = 0x1, MRC will be forced to perform a full
                                  memory training cycle.

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
CpuReplacementCheck (
  IN VOID                         *FfsHeader,
  OUT UINT8                       *ForceFullTraining
  )
{
  UINT64                          HeciBaseAddress;
  HECI_GS_SHDW_REGISTER           MeFwsts2;
  EFI_STATUS                      Status;
  UINT32                          Timeout;
  SI_PREMEM_POLICY_PPI            *SiPreMemPolicyPpi;
  ME_PEI_PREMEM_CONFIG            *MePeiPreMemConfig;

  if (MeTypeIsSps ()) {
    //
    // SPS firmware does not support CPU replaced detection
    //
    *ForceFullTraining = TRUE;
    return EFI_SUCCESS;
  }
  HeciBaseAddress = PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, 0);


  //
  // Get Policy settings through the SiPreMemPolicyPpi PPI
  //
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);

  Status  = EFI_SUCCESS;
  Timeout = 0x0;
  //
  // Read ME FWS2
  //
  MeFwsts2.ul = PciSegmentRead32 (HeciBaseAddress + R_ME_HFS_2);
  DEBUG ((DEBUG_INFO, "MeFwsts2 = %x.\n", MeFwsts2.r));

  if (MeFwsts2.ul == 0xFFFFFFFF) {
    DEBUG ((DEBUG_INFO, "HECI not present! Skip detection!\n"));
    return EFI_SUCCESS;
  }

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gMePeiPreMemConfigGuid, (VOID *) &MePeiPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  PERF_START_EX (FfsHeader, NULL, NULL, AsmReadTsc (), 0x3050);
  //
  // Poll 50 ms on CPU Replaced Valid bit
  //
  while ((((MeFwsts2.r.CpuReplacedValid == 0) && Timeout < CPURV_TIMEOUT_MULTIPLIER))
      && (MePeiPreMemConfig->DisableCpuReplacedPolling != 1)) {
    MicroSecondDelay (STALL_1_MILLISECOND);
    MeFwsts2.ul = PciSegmentRead32 (HeciBaseAddress + R_ME_HFS_2);
    Timeout++;
  }
  PERF_END_EX (FfsHeader, NULL, NULL, AsmReadTsc (), 0x3051);

  DEBUG ((DEBUG_INFO, "CpuReplacedValid = %x, ", MeFwsts2.r.CpuReplacedValid));
  DEBUG ((DEBUG_INFO, "CpuReplacedStatus = %x, ", MeFwsts2.r.CpuReplacedSts));
  DEBUG ((DEBUG_INFO, "WarmRstReqForDF = %x.\n", MeFwsts2.r.WarmRstReqForDF));

  if (Timeout >= CPURV_TIMEOUT_MULTIPLIER || MeFwsts2.r.CpuReplacedValid == 0x0) {
    DEBUG ((DEBUG_WARN, "Timeout occurred, the CPU Replacement Valid Bit is not set.\n"));
    *ForceFullTraining = 0x1;
  } else {
    if (MeFwsts2.r.CpuReplacedValid == 0x1) {
      if (MeFwsts2.r.WarmRstReqForDF == 0x1) {
        //
        // Clear DISB and Issue a Non-Power Cycle Reset
        //
        PmcClearDramInitScratchpad ();
        PerformReset (DID_ACK_NON_PCR);
        // System should not reach here
      }

      if ((MeFwsts2.r.CpuReplacedSts == 0x1) && (MeFwsts2.r.WarmRstReqForDF == 0x0)) {
        *ForceFullTraining = 0x1;
      }
    }
  }

  return Status;
}

/**
  This procedure will configure the ME Host General Status register,
  indicating that DRAM Initialization is complete and ME FW may
  begin using the allocated ME UMA space.

  @param[in] FfsHeader            Pointer to the FFS file header
  @param[in] InitStat             H_GS[27:24] Status
  @param[in] ImrBaseLow           Base address for IMR region (Low DWORD)
  @param[in] ImrBaseHigh          Base address for IMR region (High DWORD)
  @param[out] PciImrBaseLow       Base address for PCI IMR (Low DWORD)
  @param[out] PciImrBaseHigh      Base address for PCI IMR (High DWORD)

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
MeConfigDidReg (
  IN VOID                         *FfsHeader,
  IN UINT8                        InitStat,
  IN UINT32                       ImrBaseLow,
  IN UINT32                       ImrBaseHigh,
  OUT UINT32                      *PciImrBaseLow,
  OUT UINT32                      *PciImrBaseHigh
  )
{
  HECI_FWS_REGISTER               MeHfs;
  EFI_STATUS                      Status;
  SI_PREMEM_POLICY_PPI            *SiPreMemPolicyPpi;
  UINT8                           MeReturnValue;
  UINT8                           Flags;
  UINT8                           BiosAction;
  ME_PEI_PREMEM_CONFIG            *MePeiPreMemConfig;

  DEBUG ((DEBUG_INFO, "ME-BIOS: DID Entry.\n"));
  PostCode (0xE01);

  BiosAction = 0;

  ///
  /// Get Policy settings through the SiPreMemPolicyPpi PPI
  ///
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ME-BIOS: DID Exit - Error by SiPreMemPolicyPpi not found, Status: %r\n", Status));
    ASSERT_EFI_ERROR (Status);
    PostCode (0xE81);
    return Status;
  }

  MeHfs.ul = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, R_ME_HFS));
  DEBUG ((DEBUG_INFO, "ME status: 0x%08x\n", MeHfs.ul));

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gMePeiPreMemConfigGuid, (VOID *) &MePeiPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  if (MePeiPreMemConfig->SendDidMsg == 0) {
    ///
    /// Do not send End of Post message to ME FW when the DRAM Init Done message is not sent, as ME FW will not be
    /// capable of handling the EOP message.
    ///
    DEBUG ((DEBUG_INFO, "MePeiPreMemConfig->SendDidMsg = 0, do not check for ME UMA. \n"));
    DEBUG ((DEBUG_INFO, "ME-BIOS: DID Exit - Success.\n"));
    PostCode (0xE21);
    return EFI_SUCCESS;
  }

  DEBUG ((DEBUG_INFO, "Entered ME DRAM Init Done procedure.\n"));

  ///
  /// Install ME HOBs
  ///
  InstallMeHob ();

  if (MePeiPreMemConfig->DidInitStat != 0) {
    InitStat = (UINT8) (UINTN) MePeiPreMemConfig->DidInitStat - 1;
  }
  DEBUG ((DEBUG_INFO, "InitStat: %x\n", InitStat));

  Status = PeiServicesInstallPpi (&mMeBeforeDidSendPpi);
  ASSERT_EFI_ERROR (Status);

  PERF_START_EX (FfsHeader, NULL, NULL, AsmReadTsc (), 0x30A0);
  //
  // Send DID using HECI message
  //
  DEBUG ((DEBUG_INFO, " Sending DID as MKHI message\n"));
  Status = PeiHeciSendDid (
             ImrBaseLow,
             ImrBaseHigh,
             InitStat,
             &MeReturnValue,
             &Flags,
             &BiosAction,
             PciImrBaseLow,
             PciImrBaseHigh
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Sending DID failed! Error: %r\n", Status));
  } else {
    DEBUG ((DEBUG_INFO, "ME DRAM Init Done ACK received.\n"));
    DEBUG ((DEBUG_INFO, "HFS read after DID ACK: %x\n", MeHfs.r));
    BuildPciImrHob (*PciImrBaseLow, *PciImrBaseHigh);
  }
  PERF_END_EX (FfsHeader, NULL, NULL, AsmReadTsc (), 0x30A1);

  DEBUG ((DEBUG_INFO, "BiosAction = %x\n", BiosAction));
  HandleMeBiosAction (BiosAction);

  Status = PeiServicesInstallPpi (&mMeDidSendPpi);
  ASSERT_EFI_ERROR (Status);

  //
  // The 'Status' local variable still keeps value of PeiHeciSendDid function.
  // Use it to update POSTCODE.
  //
  if (!EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "ME-BIOS: DID Exit - Success.\n"));
    PostCode (0xE21);
  } else {
    DEBUG ((DEBUG_ERROR, "ME-BIOS: DID Exit - Error by fail to send DID message, Status: %r\n", Status));
    PostCode (0xEA1);
  }

  return EFI_SUCCESS;
}

/**
  This procedure will send the information to CSME about the IMRs which need to be
  enabled and retrieve the information about total size of memory and alignment
  required for IMRs.

  @param[out] ImrsSize            Total IMR size
  @param[out] Alignment           Required address alignment

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
MeImrConfig (
  OUT UINT32     *ImrsSize,
  OUT UINT32     *Alignment
  )
{
  UINT16            PcieImrSize;
  UINT32            BiosImrDisableMask0;
  UINT32            BiosImrDisableMask1;
  UINT8             MeReturnValue;
  HECI_FWS_REGISTER MeHfs;
  UINT8             IpuConfiguration;

  BiosImrDisableMask0 = 0xFFFFFFFF;
  BiosImrDisableMask1 = 0xFFFFFFFF;

  PcieImrSize = 0;

  DEBUG((DEBUG_INFO, "IMR Configuration start\n"));

  MeHfs.ul = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, R_ME_HFS));
  DEBUG ((DEBUG_INFO, "ME status: 0x%08x\n", MeHfs.ul));

  if (IsIshEnabled ()) {
    BiosImrDisableMask0 &= (UINT32)~(BIT0);  // ISH
  }

  BiosImrDisableMask0 &= (UINT32)~(BIT5);    // CSME

  if (IsPcieImrEnabled ()) {
    BiosImrDisableMask0 &= (UINT32)~(BIT7);  // PCIe
    PcieImrSize = GetPcieImrSize ();
  }

  if (IsHdAudioEnabled ()) {
    BiosImrDisableMask0 &= (UINT32)~(BIT10); // Audio
  }

  if (IsIpuEnabled ()) {
    IpuConfiguration = GetIpuImrConfiguration ();
    if (IpuConfiguration == IMR_IPU_CAMERA) {
      BiosImrDisableMask0 &= (UINT32)~(BIT1);  //IPU Camera
    } else {
      BiosImrDisableMask0 &= (UINT32)~(BIT6);  //IPU Gen
    }
  }
#if FixedPcdGetBool(PcdITbtEnable) == 1
  //
  // TCSS IMR need to be always enabled since common b/w iTBT & IOM
  //
  BiosImrDisableMask0 &= (UINT32)~(BIT14);  // TCSS(iTBT+IOM)
#endif
  if (CnviIsPresent ()) {
    BiosImrDisableMask0 &= (UINT32)~(BIT12); // CNVi
  }

  if (IsPseEnabled ()) {
    BiosImrDisableMask0 &= (UINT32)~(BIT16); // PSE
  }

  DEBUG((DEBUG_INFO, "BiosImrDisableMask0 = %x\n", BiosImrDisableMask0));
  DEBUG((DEBUG_INFO, "PCIe IMR Size       = %x\n", PcieImrSize));

  PeiHeciGetImrSizeMsg (
    BiosImrDisableMask0,
    BiosImrDisableMask1,
    PcieImrSize << 20,         // PCIe IMR Size in bytes
    &MeReturnValue,
    ImrsSize,                  // ImrsSize in bytes
    Alignment                  // Alignment in bytes
    );

  return EFI_SUCCESS;
}
