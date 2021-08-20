/** @file
Intel Turbo Boost Max Technology 3.0

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

#include <CpuAccess.h>
#include "PowerMgmtSmm.h"
#include <PowerMgmtNvsStruct.h>
#include "CpuDataStruct.h"
#include <Protocol/SmmIoTrapDispatch2.h>
#include <Library/IoLib.h>
#include <Library/SynchronizationLib.h>

#define TIME_8s     80000000  ///< 8s in units of 100 nano seconds.

EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL  *mPeriodicSmmDispatch2Protocol = NULL;

GLOBAL_REMOVE_IF_UNREFERENCED PCH_SMM_PERIODIC_TIMER_CONTROL_PROTOCOL *mPchSmmPeriodicTimerControlProtocol = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED CPU_NVS_AREA *mCpuNvsAreaPtr;
EFI_SMM_PERIODIC_TIMER_REGISTER_CONTEXT mPeriodicSmmContext;
EFI_HANDLE mPeriodicSmmHandle;

UINT8 *mHighestPerfPerCore = NULL; ///< Pointer to Buffer to store highest performance of cores.
UINT8 mPerfCheckEvent = 0; ///< Flag to indicate that the highest performance has changed.

///
/// Spin lock used to serialize the MSR read of IA32_HWP_CAPABILITIES
///
SPIN_LOCK mHwpCapabilitiesMsrSpinLock;


/**
  Checks for changes to max performance ratio in MSR_IA32_HWP_CAPABILITIES.

  @param[in] Buffer    Pointer to Buffer to indicate target CPU number.
**/
VOID
EFIAPI
CheckHwpCapabilities (
  IN VOID *Buffer
  )
{

  //
  // For CNL systems
  //
  MSR_REGISTER HwpCapabilities;
  UINTN Index = 0;
  UINT8 HighestPerf;

  Index = *(UINTN *) Buffer; ///< Cast to enhance readability.

  HwpCapabilities.Qword = AsmReadMsr64 (MSR_IA32_HWP_CAPABILITIES);
  HighestPerf = (UINT8) (HwpCapabilities.Bytes.FirstByte);

  if (HighestPerf != mHighestPerfPerCore[Index]) {
    mPerfCheckEvent = 1; ///< Highest Performance has changed.
    mHighestPerfPerCore[Index] = HighestPerf;
  }

  ///
  /// Release the SpinLock once execution is done
  ///
  ReleaseSpinLock (&mHwpCapabilitiesMsrSpinLock);

  return;
}

/**
  Overclocking systems can change the maximum cpu ratio during OS runtime.
  If the maximum cpu ratio changes, we must notify the OS of the change so that ITBM driver
  will operate using the new maximum ratio. Without the notification, changes to the max ratio are ignored
  and overclocking is broken. A periodic SMM handler (every 8seconds) is implemented to check for
  these changes in IA32_HWP_Capabilities. The OS will indicate the capability to re-read frequency
  by setting _OSC Bit [12] =1. In this case, the BIOS will trigger the SW SMI which will resume this periodic SMM.
  In case of ICL, the Si through p-Code will support new HWP interrupt status bit [3] defined in IA32_HWP_STATUS
  to indicate change in the highest performance.
  If the processor device _OSC bit [14] = 0, that means that the OS doesn't support native handling of interrupts.
  In this case, if OS supports frequency re-read through platform _OSC bit [12] = 1, the BIOS will trigger the SW SMI
  which will resume the periodic SMM.

  @param[in]     DispatchHandle  The unique handle assigned to this handler by SmiHandlerRegister().
  @param[in]     Context         Points to an optional handler context which was specified when the
                                 handler was registered.
  @param[in,out] CommBuffer      A pointer to a collection of data in memory that will
                                 be conveyed from a non-SMM environment into an SMM environment.
  @param[in,out] CommBufferSize  The size of the CommBuffer.

  @retval EFI_SUCCESS            Callback function executed.
**/
EFI_STATUS
EFIAPI
ItbmPeriodicSmmCallback (
  IN EFI_HANDLE   DispatchHandle,
  IN CONST VOID   *DispatchContext      OPTIONAL,
  IN OUT VOID     *CommBuffer           OPTIONAL,
  IN OUT UINTN    *CommBufferSize       OPTIONAL
  )
{
  UINTN CpuIndex;
  EFI_STATUS Status;

  mPerfCheckEvent = 0;
  CpuIndex = gSmst->CurrentlyExecutingCpu;
  Status = EFI_SUCCESS;

  ///
  /// Execute on BSP. The BSP will release the spin lock when it is done executing CheckHwpCapabilities()
  ///
  AcquireSpinLock (&mHwpCapabilitiesMsrSpinLock);
  CheckHwpCapabilities (&CpuIndex);

  for (CpuIndex = 0; CpuIndex < gSmst->NumberOfCpus; CpuIndex++) { ///< Execute on APs
     if (CpuIndex != gSmst->CurrentlyExecutingCpu) {
       ///
       /// Acquire spin lock. The AP will release the spin lock when it done executing CheckHwpCapabilties.
       ///
       AcquireSpinLock (&mHwpCapabilitiesMsrSpinLock);

       Status = gSmst->SmmStartupThisAp (
                         CheckHwpCapabilities,
                         CpuIndex,
                         &CpuIndex
                         );
      ASSERT_EFI_ERROR (Status);

      ///
      /// Wait for the AP to release the spin lock.
      ///
      while (!AcquireSpinLockOrFail (&mHwpCapabilitiesMsrSpinLock)) {
        CpuPause ();
      }

      ///
      /// Release the spin lock.
      ///
      ReleaseSpinLock (&mHwpCapabilitiesMsrSpinLock);
     }
  }

  ///
  /// Check for change in max cpu performance ratio of any one of the cores.
  ///
  if (mPerfCheckEvent == 1) {
    ///
    /// Generate a _GPE _L62 SCI to ACPI OS.
    ///
    if (PmcIsSciEnabled ()) { ///< Check if SCI is enabled.
      ///
      /// Enable SCI assertion by setting SW GPE
      /// This will generate a SW SCI event in PCH
      ///
      PmcTriggerSwGpe ();
      mCpuNvsAreaPtr->ItbmInterruptStatus = 1; ///< Indicate interrupt for ITBM
    }
  }

  return EFI_SUCCESS;
}

/**
  Software SMI callback for resuming the periodic SMM in OC capable systems
  when the OS supports the notifications, platform wide _OSC bit 12 is set.
  In case of ICL, this periodic SMM is resumed when the processor _OSC Bit [14] = 0,
  in addition to platform _OSC Bit [12] = 1 which indicates that the OS
  cannot do native handling of IA32_MSR_HWP_STATUS Bit [3].

  @param[in]      DispatchHandle              The unique handle assigned to this handler by SmiHandlerRegister().
  @param[in]      Context                     Points to an optional handler context which was specified when the
                                              handler was registered.

  @retval EFI_SUCCESS                         The interrupt was handled successfully.
  @retval EFI_INVALID_PARAMETER               The DispatchHandle was not valid.
**/
EFI_STATUS
EFIAPI
ItbmResumePeriodicSmmCallback (
   IN EFI_HANDLE                  DispatchHandle,
   IN EFI_SMM_SW_REGISTER_CONTEXT *DispatchContext
   )
{
  EFI_STATUS                                 Status;

  Status = mPchSmmPeriodicTimerControlProtocol->Resume (
                                                  mPchSmmPeriodicTimerControlProtocol,
                                                  mPeriodicSmmHandle
                                                  );

  return Status;
}

/**
  Initialize all SMI handlers required for Intel Turbo Boost Max Technology 3.0 to function.
  Initialize the Periodic SMM to check for changes in IA32_HWP_Capabilities.
  This is paused after registration.This handler is required for systems that are
  OC capable and for Operating Systems that support updated frequency notification.
  Platform _OSC bit 12 is set to indicate this support in the OS.
  In case of ICL, in addition to frequency notification support, if the OS
  does not support native handling of IA32_MSR_HWP_STATUS Bit [3]
  indicated by processor _OSC bit 14 = 0, then resume the periodic SMM.
  Initalize a SMI handler to resume this periodic SMM if the OS supports it.

  @retval EFI_SUCCESS     The driver installes/initialized correctly.
  @retval EFI_NOT_FOUND   CPU Data HOB not available.
**/
EFI_STATUS
EFIAPI
InitPowerMgmtItbmSmm (
  VOID
  )
{
  CPU_NVS_AREA_PROTOCOL                      *CpuNvsAreaProtocol;
  EFI_HANDLE                                 SwHandle;
  EFI_SMM_SW_DISPATCH2_PROTOCOL              *SwDispatch;
  EFI_SMM_SW_REGISTER_CONTEXT                SwContext;
  EFI_STATUS                                 Status;
  UINTN                                      NumberOfProcessors;

  ///
  /// Locate Cpu Nvs area
  ///
  Status = gBS->LocateProtocol (&gCpuNvsAreaProtocolGuid, NULL, (VOID **) &CpuNvsAreaProtocol);
  ASSERT_EFI_ERROR (Status);
  mCpuNvsAreaPtr = CpuNvsAreaProtocol->Area;

  ///
  /// Allocate global structure to contain the highest performance of individual cores.
  ///
  NumberOfProcessors = gSmst->NumberOfCpus;
  Status = gSmst->SmmAllocatePool (
                    EfiRuntimeServicesData,
                    NumberOfProcessors * sizeof (UINT8),
                    (VOID **) &mHighestPerfPerCore
                    );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR(Status)) {
    return(Status);
  }

  ///
  /// Initialize the spin lock used to serialize the MSR read in BSP and all APs
  ///
  InitializeSpinLock (&mHwpCapabilitiesMsrSpinLock);

  ///
  /// Register handler for periodic SMM polling (8sec) to check for changes in IA32_HWP_Capabilities.
  /// In case of ICL, check for IA32_MSR_HWP_STATUS Bit [3] whcih indicates that change in the highest performance has occurred.
  ///
  Status = gSmst->SmmLocateProtocol (
                    &gEfiSmmPeriodicTimerDispatch2ProtocolGuid,
                    NULL,
                    (VOID **) &mPeriodicSmmDispatch2Protocol
                    );
  ASSERT_EFI_ERROR (Status);

  mPeriodicSmmContext.Period = 1;
  mPeriodicSmmContext.SmiTickInterval = TIME_8s;
  Status = mPeriodicSmmDispatch2Protocol->Register (
                                            mPeriodicSmmDispatch2Protocol,
                                            ItbmPeriodicSmmCallback,
                                            &mPeriodicSmmContext,
                                            &mPeriodicSmmHandle
                                            );

  ///
  /// Pause the periodic timer because of responsiveness impact. This timer will be resumed
  /// through SW SMI only if the OS supports ITBM notifications. This support is indicated through
  /// platform _OSC Bit [12] = 1.
  /// In case of ICL, since HW supports IA32_MSR_HWP_STATUS Bit [3] to indicate change in the highest performance,
  /// check if the OS does not support native handling (processor _OSC Bit [14] = 0 ) in addition to support for ITBM notifications,
  /// before resuming the periodic SMM.
  ///
  Status = gSmst->SmmLocateProtocol (
                    &gPchSmmPeriodicTimerControlGuid,
                    NULL,
                    (VOID **) &mPchSmmPeriodicTimerControlProtocol
                    );
  ASSERT_EFI_ERROR (Status);

  Status = mPchSmmPeriodicTimerControlProtocol->Pause (
                                                  mPchSmmPeriodicTimerControlProtocol,
                                                  mPeriodicSmmHandle
                                                  );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Register SW SMI handler to resume the periodic timer if the OS supports it. Indicated by
  /// _OSC Bit [12] = 1.
  /// In case of ICL, this is done in with an additional check of processor _OSC Bit [14] = 0,
  /// which indicates that the OS does not do native handling of IA32_MSR_HWP_STATUS Bit [3] but can
  /// support frequency re-read.
  ///
  Status = gSmst->SmmLocateProtocol (&gEfiSmmSwDispatch2ProtocolGuid, NULL, (VOID**) &SwDispatch);
  ASSERT_EFI_ERROR (Status);
  SwContext.SwSmiInputValue = (UINTN) PcdGet8 (PcdItbmSmi);
  Status = SwDispatch->Register (
                         SwDispatch,
                         (EFI_SMM_HANDLER_ENTRY_POINT2) ItbmResumePeriodicSmmCallback,
                         &SwContext,
                         &SwHandle
                         );
  ASSERT_EFI_ERROR (Status);

  return Status;
}