/** @file
  Framework PEIM to HECI.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2008 - 2018 Intel Corporation.

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

#include <Ppi/HeciPpi.h>
#include <Ppi/SiPolicy.h>
#include <Library/PeiServicesLib.h>
#include <Library/DebugLib.h>
#include <Library/PeiMeLib.h>
#include <Library/PostCodeLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PmcLib.h>
#include <Library/HeciInitLib.h>
#include <Library/MeTypeLib.h>
#include <Library/BootMediaLib.h>
#if FixedPcdGetBool(PcdBfxEnable) == 1
#include <Library/HobLib.h>
#include <HeciContextLib.h>
#endif

//
// Function Declarations
//
static HECI_PPI               mHeciPpi = {
  HeciSendwAck,
  HeciReceive,
  HeciSend,
  HeciInitialize,
  HeciGetMeStatus,
  HeciGetMeMode
};

static EFI_PEI_PPI_DESCRIPTOR mInstallHeciPpi = {
  EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
  &gHeciPpiGuid,
  &mHeciPpi
};

//
// Function Implementations
//

/**
  Initialize MMIO BAR address for HECI devices

  @retval EFI_SUCCESS             HECI devices initialize successfully
  @retval others                  Error occur
**/
EFI_STATUS
PeiHeciDevicesInit (
  VOID
  )
{
  SI_PREMEM_POLICY_PPI *SiPreMemPolicyPpi;
  EFI_STATUS           Status;
  ME_PEI_PREMEM_CONFIG *MePeiPreMemConfig;
  BOOLEAN              HeciCommunication2;
#if FixedPcdGetBool(PcdBfxEnable) == 1
  HECI_CONTEXT_HOB     *HeciContextHob;
  UINT16               DeviceIndex;
#endif
  BOOLEAN              HeciCommunication;
  BOOLEAN              HeciCommunication4;

  HeciCommunication   = TRUE;
  HeciCommunication4  = TRUE;

#if FixedPcdGetBool(PcdBfxEnable) == 1
  HeciContextHob = GetFirstGuidHob (&gHeciContextHobGuid);
  if (HeciContextHob == NULL) {
    ///
    /// Create HOB for HECI Context
    ///
    Status = PeiServicesCreateHob (
               EFI_HOB_TYPE_GUID_EXTENSION,
               sizeof (HECI_CONTEXT_HOB),
               (VOID **) &HeciContextHob
               );
    if (Status == EFI_SUCCESS) {
      ///
      /// Initialize default HOB data
      ///
      HeciContextHob->EfiHobGuidType.Name = gHeciContextHobGuid;
      for (DeviceIndex = Heci1; DeviceIndex < HeciMax; DeviceIndex++) {
        HeciContextHob->HeciDeviceContext[DeviceIndex].Bar0Address = 0;
        HeciContextHob->HeciDeviceContext[DeviceIndex].ContextInitialized = FALSE;
        HeciContextHob->HeciDeviceContext[DeviceIndex].IsHeciHidden = FALSE;
      }

      DEBUG ((DEBUG_INFO, "HECI Context installed\n"));
    } else {
      DEBUG ((DEBUG_ERROR, "PeiServicesCreateHob () - %r\n", Status));
    }
  }
#endif
  ///
  /// Get Policy settings through the SiPreMemPolicy PPI
  ///
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  if (!EFI_ERROR (Status)) {
    Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gMePeiPreMemConfigGuid, (VOID *) &MePeiPreMemConfig);
    ASSERT_EFI_ERROR (Status);

    MeDeviceInit (HECI1, MePeiPreMemConfig->Heci1BarAddress, 0);
    MeDeviceInit (HECI2, MePeiPreMemConfig->Heci2BarAddress, 0);
    MeDeviceInit (HECI3, MePeiPreMemConfig->Heci3BarAddress, 0);
    MeDeviceInit (HECI4, MePeiPreMemConfig->Heci4BarAddress, 0);

    ///
    /// Determine if ME devices should be Enabled/Disable and Program Subsystem IDs if Enabled
    /// Zero in Bit x enables the device
    ///
    HeciCommunication2 = MeHeci2Enabled ();

    //
    // HECI4 is required for supporting BIOS proxy in the boot from UFS path
    //
    if (BootMediaIsUfs ()) {
      MePeiPreMemConfig->HeciCommunication4 = FORCE_ENABLE;
    } else {
      MePeiPreMemConfig->HeciCommunication4 = FORCE_DISABLE;
      HeciCommunication4 = FALSE;
    }

    //
    // HECI2 is required for supporting variable services in the boot from UFS path
    //
    if (BootMediaIsUfs () && !PcdGetBool (PcdNvVariableEmulationMode)) {
      MePeiPreMemConfig->HeciCommunication2 = FORCE_ENABLE;
    } else {
      HeciCommunication2 = FALSE;
      MePeiPreMemConfig->HeciCommunication2 = FORCE_DISABLE;
    }
    if (HeciCommunication == FALSE) {
      HeciCommunication2 = FALSE;
    }

      DEBUG ((DEBUG_INFO, "HeciEnable\n"));
      HeciEnable ();
      HeciInitialize (HECI1_DEVICE);

    if (HeciCommunication2) {
      DEBUG ((DEBUG_INFO, "Heci2Enable\n"));
      Heci2Enable ();
    } else {
      DEBUG ((DEBUG_INFO, "Heci2Disable\n"));
      Heci2Disable ();
    }

      DEBUG ((DEBUG_INFO, "Heci3Enable\n"));
      Heci3Enable ();
    if (HeciCommunication4 && HeciCommunication) {
      DEBUG ((DEBUG_INFO, "Heci4Enable\n"));
      Heci4Enable ();
    } else {
      DEBUG ((DEBUG_INFO, "Heci4Disable\n"));
      Heci4Disable ();
    }
  }

#if FixedPcdGetBool(PcdBfxEnable) == 1
  //
  // Update the initial HECI context
  //
  for (DeviceIndex = Heci1; DeviceIndex < HeciMax; DeviceIndex++) {
    CheckAndFixHeciForAccess (HECI_CONTEXT_TO_DEV_MAP (DeviceIndex));
  }
#endif

  return Status;
}

/**
  Internal function performing Heci PPIs init needed in PEI phase

  @retval EFI_SUCCESS             The function completed successfully.
  @retval EFI_DEVICE_ERROR        ME FPT is bad
**/
EFI_STATUS
InstallHeciPpi (
  VOID
  )
{
  EFI_STATUS  Status;

  DEBUG((DEBUG_INFO, "ME-BIOS: HECI PPI Entry.\n"));
  PostCode (0xE03);

  ///
  /// Check for HECI device present and ME FPT Bad
  ///
  if ((PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, PCI_VENDOR_ID_OFFSET)) == 0x0) ||
      (PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, PCI_VENDOR_ID_OFFSET)) == 0xFFFFFFFF) ||
      (((PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, R_ME_HFS)) & 0x0020) != 0) && !MeTypeIsSps())) {
    DEBUG((DEBUG_ERROR, "ME-BIOS: HECI PPI Exit - Error by HECI device error.\n"));
    PostCode (0xE83);
    return EFI_DEVICE_ERROR;
  }

  ///
  /// Heci Ppi should be installed always due to DID message might be required still.
  /// Unsupported messages requested will be blocked when utilize Heci Ppi
  ///
  Status = PeiServicesInstallPpi (&mInstallHeciPpi);

  if (!EFI_ERROR (Status)) {
    DEBUG((DEBUG_INFO, "ME-BIOS: HECI PPI Exit - Success.\n"));
    PostCode (0xE23);
#if FixedPcdGetBool (PcdFspBinaryEnable) == 0
    RegisterMeReset ();
#endif
  } else {
    DEBUG((DEBUG_ERROR, "ME-BIOS: HECI PPI Exit - Error by install HeciPpi fail, Status: %r\n", Status));
    ASSERT_EFI_ERROR (Status);
    PostCode (0xEA3);
  }

  return Status;
}

/**
  Internal function performing PM register initialization for Me
**/
VOID
MePmInit (
  VOID
  )
{
  ///
  /// Before system memory initialization, BIOS should check the wake status to determine if Intel Management Engine
  /// has reset the system while the host was in a sleep state. If platform was not in a sleep state
  /// BIOS should ensure a non-sleep exit path is taken. One way to accomplish this is by forcing
  /// an S5 exit path by the BIOS.
  ///
  if (PmcGetSleepTypeAfterWake () == PmcNotASleepState) {
    PmcSetSleepState (PmcS5SleepState);
    DEBUG ((DEBUG_INFO, "MePmInit () - Force an S5 exit path.\n"));
  }
}

