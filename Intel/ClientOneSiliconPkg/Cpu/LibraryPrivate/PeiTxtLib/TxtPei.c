/** @file
  This is the main PEIM file for TXT. It represents an abstract outline of the
  steps required during PEI for enabling TXT. Each individual step is further
  abstracted behind a function call interface. This is intended to minimize
  the need to modify this file when porting TXT to future platforms.

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

@par Specification
**/

#include <Ppi/EndOfPeiPhase.h>
#include <SaConfigHob.h>
#include <Library/TxtPeiLib.h>
#include <TxtInfoHob.h>
#include <Library/PciSegmentLib.h>
#include <Library/PcdLib.h>
#include <CpuRegs.h>
#include <Ppi/MpServices.h>
#include <Library/MpInitLib.h>
#include <Register/PchRegs.h>
#include <Register/PmcRegs.h>

STATIC EFI_PEI_PPI_DESCRIPTOR mPpiList = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gPeiTxtMemoryUnlockedPpiGuid,
  NULL
};

STATIC EFI_PEI_PPI_DESCRIPTOR mPpiList1 = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gPeiTxtReadyToRunMemoryInitPpiGuid,
  NULL
};

EFI_STATUS
EFIAPI
ConfigureTxtEndOfPei (
  IN  EFI_PEI_SERVICES      **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR   *NotifyDescriptor,
  IN  VOID                        *Ppi
  );
STATIC EFI_PEI_NOTIFY_DESCRIPTOR mNotifyDesc = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiEndOfPeiSignalPpiGuid,
  ConfigureTxtEndOfPei
};

extern EFI_GUID gSaConfigHobGuid;


/**
  TPM detected callback module, must have TPM hardware initialized of detected none

  gPeiTxtMemoryUnlockedPpiGuid will tell memoryinit code if memory is unlocked and good to run.
  gPeiTxtReadyToRunMemoryInitPpiGuid will notify memoryinit code that we are done with unlock and
  should start to do memory init

  @param[in] PeiServices          General purpose services available to every PEIM.
  @param[in] NotifyDescriptor     The notification structure this PEIM registered on install.
  @param[in] Ppi                  The memory discovered PPI.  Not used.

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
TxtInit (
  VOID
  )
{
  EFI_STATUS          Status;
  TXT_INFO_HOB        *TxtInfoHob;
  BOOLEAN             TxtEnvInitFail;
  UINT32              Data32;

  Data32         = 0;
  TxtEnvInitFail = FALSE;

  ///
  /// Install PPI to tell memory code that it can run.
  /// Do it always.
  ///
  Status = PeiServicesInstallPpi (&mPpiList);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Initialize the TXT PEI Lib functions
  ///
  Status = InitializeTxtPeiLib (
             &TxtInfoHob
             );

  if (EFI_ERROR (Status)) {
    TxtEnvInitFail = TRUE;
    DEBUG ((DEBUG_WARN, "TXTPEI::PEI Lib initialization failure\n"));
  }

  /**
  Determine TPM presence. If TPM is not present - disabling TXT through TxtInfoHob by setting TxtMode=0
  In case TXT had been enabled but TPM was removed suddenly. Although TPM presence is precondition of this module
  since all commands executed by BIOS ACM don't depend on TPM state.
  TPM_NV_read will be successfully executed even if TPM is disabled
  and/or deactivated because all indices defined for BIOS ACM
  usage don't require authorization. TPM_ResetEstablishmentBit
  doesn't depend on TPM state at all and can
  be executed with disabled/deactivated TPM always.
  Case when TPM is completely not functional is not considered.
  **/
  Status = IsTpmPresent (TxtInfoHob);
  if (EFI_ERROR (Status)) {
    ///
    /// If TPM is not present / not supported, set TxtMode=0 in case TPM was removed after TXT enabled
    ///
    if (Status == EFI_UNSUPPORTED) {
      DEBUG ((DEBUG_WARN, "TXTPEI::TPM Support is Disabled in BIOS! Disabling TXT! TxtMode=%x\n", TxtInfoHob->Data.TxtMode));
    } else {
      DEBUG ((DEBUG_WARN, "TXTPEI::TPM is not present! Disabling TXT! TxtMode=%x\n", TxtInfoHob->Data.TxtMode));
    }

    TxtEnvInitFail = TRUE;
  }
  ///
  /// Detect TXT capable Processor & PCH
  ///
  if (!IsTxtChipset ()) {
    DEBUG ((DEBUG_WARN, "TXTPEI::Platform or PCH is not TXT capable\n"));
    goto Done;
  } else if (!IsTxtProcessor ()) {
    DEBUG ((DEBUG_WARN, "TXTPEI::Processor is not TXT capable\n"));
    goto Done;
  } else {
    DEBUG ((DEBUG_INFO, "TXTPEI::Processor, PCH & Platform is TXT capable\n"));

    ///
    /// If TXT Lib or TPM is initiated successful, disable TXT support.
    ///
    if (TxtEnvInitFail) {
      TxtUnlockMemory (TxtInfoHob);
      TxtInfoHob->Data.TxtMode = 0;
      ASSERT (TRUE);
      goto Done;
    }
  }

  Data32 = MmioRead32 (TXT_PUBLIC_BASE + TXT_CRASHCODE_REG_OFF);
  DEBUG ((DEBUG_INFO, "TXTPEI::Crash Code Register=%x\n", Data32));

  ///
  /// Memory is supposed to lock if system is TXT capable.
  /// Check if we need to run SCLEAN. TXT BIOS spec Section 6.2.5
  ///
  if (TxtIsEstablishmentBitAsserted (TxtInfoHob) && IsTxtWakeError ()) {

    DEBUG ((DEBUG_INFO, "TXTPEI::EstablishmentBit is set\n"));
    ///
    /// If TXTRESET is set , we must clean TXTRESET bit otherwise SCLEAN
    /// will fail
    ///
    if (IsTxtResetSet ()) {
      IssueGlobalReset ();
    }
    ///
    /// Setup and Launch SCLEAN
    ///
    DEBUG ((DEBUG_INFO, "TXTPEI::Entering SCLEAN\n"));

  } else {
    ///
    /// Unlock memory, and then continue running
    ///
    DEBUG ((DEBUG_INFO, "TXTPEI::EstablishmentBit not asserted - Unlock Memory\n"));
    AsmWriteMsr64 (MSR_LT_UNLOCK_MEMORY, 0);
  }

  Status = PeiServicesNotifyPpi (&mNotifyDesc);
  ASSERT_EFI_ERROR (Status);
Done:
  ///
  /// Install PPI to tell memory code that it can run.
  /// Do it always.
  ///
  Status = PeiServicesInstallPpi (&mPpiList1);
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}


/**
  This is AliasCheck entry point for MRC call.  The routine checks for an TXT
  capable platform and determines whether ACHECK should be run.  If so,
  it launches the BIOS ACM to run ACHECK (which will reset the platform).
  The AliasCheck routine is in peitxtlib.

  @exception EFI_UNSUPPORTED  - If the platform is not TXT capable.
  @retval EFI_SUCCESS         - In all other cases not listed above.
**/

EFI_STATUS
EFIAPI
AliasCheck (
  VOID
  )
{
  EFI_STATUS          Status = EFI_SUCCESS;
  TXT_INFO_HOB        *TxtInfoHob = NULL;

  DEBUG ((DEBUG_INFO, "TXTPEI::New Alias Check Begin\n"));

  TxtInfoHob = GetFirstGuidHob (&gTxtInfoHobGuid);
  if (TxtInfoHob == NULL) {
  //

    DEBUG ((DEBUG_ERROR, "TXTPEI::TxtInfoHob not found\n"));
    return EFI_NOT_FOUND;
  }

  if (IsTxtEnabled (TxtInfoHob)) {
    Status = IsTpmPresent (TxtInfoHob);
    if (!EFI_ERROR (Status)) {
      if (IsTxtChipset ()) {
        if (IsTxtProcessor ()) {
          DEBUG ((DEBUG_INFO, "TXTPEI::TXT enabled platform\n"));
          if (((MmioRead32 (TXT_PUBLIC_BASE + TXT_CRASHCODE_REG_OFF) & 0xFE007FF0) == 0xC00040B0)
              || (IsAcheckRequested (TxtInfoHob))
              ) {
            DEBUG ((DEBUG_INFO, "TXTPEI::DoAlias\n"));

            DoAcmLaunch (TxtInfoHob, TXT_LAUNCH_ACHECK);
            ///
            /// Reset platform - performed by DoAcheck, should not return to execute the following dead looping
            ///
            CpuDeadLoop ();
          }  // if special pattern
        } // IsTxtProcessor
      } // IsTxtChipset
    } // IsTpmPresent
  } // IsTxtEnabled
  DEBUG ((DEBUG_INFO, "TXTPEI::New Alias Check End\n"));

  return EFI_UNSUPPORTED;
}

/**
  This function gets registered as a callback to run the SCHECK function
  from the TXT BIOS ACM as a result of Boot Events.

  @param[in]  Event    A pointer to the Event that triggered the callback.
  @param[in]  Context  A pointer to private data registered with the callback function.
  **/
EFI_STATUS
EFIAPI
ScheckCallback (
    IN EFI_PEI_SERVICES          **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
    IN VOID                      *Ppi
  )
{
  TXT_INFO_HOB        *TxtInfoHob = NULL;
  EFI_STATUS           Status=EFI_SUCCESS;
  EFI_BOOT_MODE       BootMode;
  UINT64              TxtBootMode = 0;

  DEBUG ((DEBUG_INFO, "TXTPEI::Running of ScheckCallback\n"));

  TxtInfoHob = GetFirstGuidHob (&gTxtInfoHobGuid);
  if (TxtInfoHob == NULL) {
    DEBUG ((DEBUG_ERROR, "TXTPEI::TxtInfoHob not found.... Unloading\n"));
    return EFI_NOT_FOUND;
  }
  Status = PeiServicesGetBootMode (&BootMode);
  if ((Status == EFI_SUCCESS) && (BootMode == BOOT_ON_S3_RESUME)) {
    TxtBootMode = S3_RESUME_PATH;
  }
  Status = DoPeiLaunchAcm (PeiServices,TxtInfoHob,TXT_LAUNCH_SCHECK,TxtBootMode);
  return Status;
}

/**
  Fix up pointers since they are located in real memory now.

  @param[in] PeiServices          General purpose services available to every PEIM.
  @param[in] NotifyDescriptor     The notification structure this PEIM registered on install.
  @param[in] Ppi                  The memory discovered PPI.  Not used.

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
EFIAPI
ConfigureTxtEndOfPei (
  IN EFI_PEI_SERVICES    **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
  IN VOID                      *Ppi
  )
{
  EFI_STATUS          Status = EFI_SUCCESS;
  TXT_INFO_HOB        *TxtInfoHob;
  EFI_BOOT_MODE       BootMode;
  UINTN               NumberOfProcessors;
  UINTN               NumberOfEnabledProcessors;
  EFI_PEI_MP_SERVICES_PPI      *MpServicesPpi             = NULL;
  TxtInfoHob   = NULL;

  DEBUG ((DEBUG_INFO, "TXTPEI::ConfigureTxtEndOfPei\n"));

  TxtInfoHob = (TXT_INFO_HOB *) GetFirstGuidHob (&gTxtInfoHobGuid);
  if (TxtInfoHob == NULL) {
    return EFI_NOT_FOUND;
  }

  ///
  /// If ESTS.TXTRESET bit is set, skip all other functions since
  /// attempt to execute GETSEC will hang system. Skipping allows to
  /// boot to OS and let MLE assess situation.
  ///
  if (IsTxtResetSet ()) {
    DEBUG ((DEBUG_ERROR, "TXTPEI::TXT_RESET bit is set.... Unloading\n"));
    return EFI_UNSUPPORTED;
  }

  ///
  /// If TXT is enabled, configure platform appropriately.
  /// Code assumes that if TXT is enabled by CPU driver than all checks
  /// are passed, i.e. TPM is present, CPU and CS are TXT capable.
  ///
  ///
  /// Add to check CPU TXT capable in case CPU drivers do not check additional requirements
  ///
  if ((TxtInfoHob->Data.ChipsetIsTxtCapable) && (TxtInfoHob->Data.ProcessorIsTxtCapable) && (IsTxtEnabled (TxtInfoHob))) {
    DEBUG ((DEBUG_INFO, "TXTPEI::TXT Enabled\n"));

    Status = PeiServicesLocatePpi (
               &gEfiPeiMpServicesPpiGuid,
               0,
               NULL,
               (VOID **) &MpServicesPpi);
    ASSERT_EFI_ERROR (Status);
    ///
    /// Fill Cpu MP system data
    ///
    MpServicesPpi->GetNumberOfProcessors ((const EFI_PEI_SERVICES **)PeiServices, MpServicesPpi, (UINTN *)&NumberOfProcessors, (UINTN *)&NumberOfEnabledProcessors);

    //
    // Update DPR Memory
    //
    Status = DprUpdate (TxtInfoHob);
    if (EFI_ERROR(Status)) {
      TxtInfoHob->Data.TxtMode = 0;
      return Status;
    }

    ///
    /// Mark TXT Config Space as System Reserved in Memory Map - this is taken care of in MRC
    ///

    ///
    /// Allocate and Initialize TXT Device Memory
    ///
    Status = SetupTxtDeviceMemory (TxtInfoHob,NumberOfProcessors);
    if (EFI_ERROR (Status)) {
      TxtInfoHob->Data.TxtMode = 0;
      DEBUG ((DEBUG_ERROR, "TXTPEI::SetupTxtDeviceMemory failed.... Unloading\n"));
      return EFI_UNSUPPORTED;
    }

    Status = PeiServicesGetBootMode (&BootMode);
    if ((Status == EFI_SUCCESS) && (BootMode == BOOT_ON_S3_RESUME)) {
      Status = ScheckCallback(NULL,NULL,NULL);
      if (EFI_ERROR (Status)) {
        return Status;
      }
    }

  } else {
    ///
    /// TXT is not enabled, so make sure TPM Establishment
    /// bit is de-asserted
    ///
    DEBUG ((DEBUG_INFO, "TXTPEI::TXT Disabled\n"));

    if (TxtIsEstablishmentBitAsserted (TxtInfoHob)) {
      ///
      /// We can invoke BIOS ACM function only if CS and CPU are TXT
      /// capable
      ///
      if ((TxtInfoHob->Data.ChipsetIsTxtCapable) &&
          (IsTxtProcessor ()) &&
          !(TxtInfoHob->Data.Flags & TPM_INIT_FAILED)
          ) {
        DEBUG ((DEBUG_INFO, "TXTPEI::Resetting TPM Establishment bit\n"));
        Status = DoPeiLaunchAcm (PeiServices,TxtInfoHob,TXT_RESET_EST_BIT,COLD_BOOT_PATH);

      }
    }
    ///
    /// Reset AUX
    ///
    if (TxtInfoHob->Data.ResetAux == 1) {
      Status = DoPeiLaunchAcm (PeiServices,TxtInfoHob,TXT_RESET_AUX,COLD_BOOT_PATH);
      ASSERT_EFI_ERROR (Status);
    }
  }

  return Status;
}

/**
  Fix up pointers since they are located in real memory now.

  @param[in] PeiServices          General purpose services available to every PEIM.
  @param[in] NotifyDescriptor     The notification structure this PEIM registered on install.
  @param[in] Ppi                  The memory discovered PPI.  Not used.

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
EFIAPI
DprUpdate (
  TXT_INFO_HOB        *TxtInfoHob
  )
{
  SA_CONFIG_HOB       *SaConfigHob;
  DPR_DIRECTORY_ENTRY *DprDirectory;
  UINT16              Index;

  SaConfigHob    = NULL;
  DprDirectory = NULL;
  Index        = 0;

  DEBUG ((DEBUG_INFO, "TXTPEI::DprUpdate\n"));

  //
  // Get TxtInfoHob
  //
  if (TxtInfoHob == NULL) {
    return EFI_NOT_FOUND;
  }
  TxtInfoHob->Data.TxtDprMemoryBase = 0;

  //
  // Get SaConfigHob
  //
  SaConfigHob = (SA_CONFIG_HOB *) GetFirstGuidHob (&gSaConfigHobGuid);
  if (SaConfigHob == NULL) {
    return EFI_NOT_FOUND;
  }
  DprDirectory = (DPR_DIRECTORY_ENTRY *)&(SaConfigHob->DprDirectory[0]);

  //
  // Find TXT DPR Directory
  //
  for (Index = 0; Index < DPR_DIRECTORY_MAX; Index++) {
    if (DprDirectory[Index].Type == DPR_DIRECTORY_TYPE_TXT) {
      TxtInfoHob->Data.TxtDprMemoryBase = (EFI_PHYSICAL_ADDRESS) DprDirectory[Index].PhysBase;
      break;
    }
  }

  return EFI_SUCCESS;
}


/**
  This is ClearSecretsBit entry point for MRC call.

  @exception EFI_UNSUPPORTED  - If the platform is not TXT capable.
  @retval EFI_SUCCESS         - In all other cases not listed above.
**/
EFI_STATUS
EFIAPI
ClearSecretsBit (
  VOID
  )
{
  EFI_STATUS          Status = EFI_SUCCESS;
  TXT_INFO_HOB        *TxtInfoHob = NULL;

  DEBUG ((DEBUG_INFO, "TXTPEI::ClearSecretsBit\n"));

  TxtInfoHob = GetFirstGuidHob (&gTxtInfoHobGuid);
  if (TxtInfoHob == NULL) {
    DEBUG ((DEBUG_ERROR, "TXTPEI::TxtInfoHob not found\n"));
    return EFI_NOT_FOUND;
  }

  ///
  /// Invoke ACM
  ///
  DoAcmLaunch (TxtInfoHob, TXT_LAUNCH_CLEAR_SECRETS);

  ///
  /// Reset platform
  ///
  IssueGlobalReset();

  return Status;
}

/**
  This is SetPowerDownRequest entry point for MRC call.

  @exception EFI_UNSUPPORTED  - If the platform is not TXT capable.
  @retval EFI_SUCCESS         - In all other cases not listed above.
**/
EFI_STATUS
EFIAPI
SetPowerDownRequest (
  VOID
  )
{
  EFI_STATUS          Status = EFI_SUCCESS;
  TXT_INFO_HOB        *TxtInfoHob = NULL;

  DEBUG ((DEBUG_INFO, "TXTPEI::SetPowerDownRequest\n"));

  TxtInfoHob = GetFirstGuidHob (&gTxtInfoHobGuid);
  if (TxtInfoHob == NULL) {
    DEBUG ((DEBUG_ERROR, "TXTPEI::TxtInfoHob not found\n"));
    return EFI_NOT_FOUND;
  }

  ///
  /// TODO:  Create PD_Request, to communicate with Startup ACM
  ///

  ///
  /// Reset platform
  ///
  ///IssueGlobalReset();

  return Status;
}
