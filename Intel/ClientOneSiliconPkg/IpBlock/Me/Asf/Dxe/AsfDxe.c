/** @file
  Alert Standard Format Initialization driver..

@copyright
  INTEL CONFIDENTIAL
  Copyright 2005 - 2019 Intel Corporation.

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

#include <PiDxe.h>
#include <Pi/PiStatusCode.h>
#include <IndustryStandard/AlertStandardFormatTable.h>
#include <Guid/HobList.h>
#include <Library/HobLib.h>
#include <Library/DxeAsfHeciLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/TimerLib.h>
#include <Library/PostCodeLib.h>
#include <Protocol/AsfProtocol.h>
#include <Protocol/HeciProtocol.h>
#include <IndustryStandardAsf.h>
#include <IntelAsfExtensions.h>
#include <CoreBiosMsg.h>
#include <MeBiosPayloadHob.h>

#define FW_INIT_DONE_TIMEOUT_VALUE        15

GLOBAL_REMOVE_IF_UNREFERENCED ALERT_STANDARD_FORMAT_PROTOCOL  mAsfProtocol;

/**
  Return EFI_SUCCESS if Firmware Init Complete is set in HFS[9].

  @param[in] Heci                 EFI_HECI_PROTOCOL
  @param[in] Timeout              Time in second

  @retval EFI_SUCCESS             Firmware Init Complete is set
  @retval EFI_TIMEOUT             Firmware Init Complete is not set in 5 seconds
**/
EFI_STATUS
WaitFirmwareInitDone (
  HECI_PROTOCOL                   *Heci,
  UINT32                          Timeout
  )
{
  UINT32      Index;
  EFI_STATUS  Status;
  UINT32      MeStatus;

  Status  = EFI_SUCCESS;
  Index     = 0;

  Heci->GetMeStatus (&MeStatus);

  while (!ME_STATUS_IS_ME_FW_INIT_COMPLETE (MeStatus)) {
    MicroSecondDelay (100000);
    Index++;
    if (Index > Timeout * 10) {
      Status = EFI_TIMEOUT;
      break;
    }

    Heci->GetMeStatus (&MeStatus);
  }

  return Status;
}

/**
  Return the ASF Boot Options obtained from the controller. If the
  Boot Options parameter is NULL and no boot options have been retrieved,
  Query the ASF controller for its boot options.
  Get ASF Boot Options through HECI.

  @retval EFI_SUCCESS             Boot options copied
  @retval EFI_NOT_READY           No boot options
**/
STATIC
EFI_STATUS
AsfGetBootOptions (
  VOID
  )
{
  EFI_STATUS                          Status;
  UINT32                              MeStatus;
  UINT32                              MeMode;
  EFI_STATUS                          TempStatus;
  HECI_PROTOCOL                       *Heci;

  DEBUG ((DEBUG_INFO, "ME-BIOS: ASF: Get Boot Options Entry.\n"));
  PostCode (0xE09);

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ME-BIOS: ASF: Get Boot Options Exit - Error by HECI service not found, Status: %r\n", Status));
    PostCode (0xE89);
    return Status;
  }

  mAsfProtocol.AsfBootOptions.SubCommand = ASF_BOOT_OPTIONS_NOT_PRESENT;
  mAsfProtocol.AsfBootOptions.Version    = ASF_VERSION;

  ///
  /// Get ME Status
  ///
  TempStatus = Heci->GetMeStatus (&MeStatus);
  ASSERT_EFI_ERROR (TempStatus);

  ///
  /// Get ME Operation Mode
  ///
  TempStatus = Heci->GetMeMode (&MeMode);
  ASSERT_EFI_ERROR (TempStatus);

  ///
  /// Only Send ASF Get Boot Options message when ME is ready and ME FW INIT is completed
  ///
  if (ME_STATUS_IS_ME_FW_BOOT_OPTIONS_PRESENT (MeStatus) && (MeMode == ME_MODE_NORMAL)) {
    if (WaitFirmwareInitDone (Heci, FW_INIT_DONE_TIMEOUT_VALUE) != EFI_TIMEOUT) {
      Status = GetBootOptions (&mAsfProtocol.AsfBootOptions);
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "ME-BIOS: ASF: Get Boot Options Exit - Error by HECI access fail.\n"));
        PostCode (0xEE9);
        return Status;
      }

      ///
      /// ASF Get Boot Options -  Clear Boot Options
      /// Need to do this so don't get caught in an endless loop plus by
      /// definition get boot options is a one time boot situation.
      /// So if server on other end of ASF device wants another back to back
      /// boot it will request it. Do this only if there were boot options
      ///
      if (mAsfProtocol.AsfBootOptions.SubCommand == ASF_BOOT_OPTIONS_PRESENT) {
        if ((mAsfProtocol.AsfBootOptions.SpecialCommand == ASF_INTEL_OEM_CMD) &&
            (mAsfProtocol.AsfBootOptions.SpecialCommandParamLowByte & ENABLE_SECURE_ERASE)) {
          //
          // When secure erase boot option is set, don't clear boot options, but discard
          // any other boot option except secure erase, KVM and SOL
          //
          DEBUG ((DEBUG_INFO, "ASF Clear Boot Options skipped due to secure erase command\n"));
          DEBUG ((DEBUG_INFO, "Dumping SpecialCommandParam, BootOptions and OemParameters before discarding\n"));
          DEBUG ((DEBUG_INFO, "SpecialCommandParamHighByte = 0x%x\n", mAsfProtocol.AsfBootOptions.SpecialCommandParamHighByte));
          DEBUG ((DEBUG_INFO, "SpecialCommandParamLowByte  = 0x%x\n", mAsfProtocol.AsfBootOptions.SpecialCommandParamLowByte));
          DEBUG ((DEBUG_INFO, "BootOptionsMaskByte1        = 0x%x\n", mAsfProtocol.AsfBootOptions.BootOptionsMaskByte1));
          DEBUG ((DEBUG_INFO, "BootOptionsMaskByte2        = 0x%x\n", mAsfProtocol.AsfBootOptions.BootOptionsMaskByte2));
          DEBUG ((DEBUG_INFO, "OemParameterByte1           = 0x%x\n", mAsfProtocol.AsfBootOptions.OemParameterByte1));
          DEBUG ((DEBUG_INFO, "OemParameterByte2           = 0x%x\n", mAsfProtocol.AsfBootOptions.OemParameterByte2));
          DEBUG ((DEBUG_INFO, "End\n\n" ));
          mAsfProtocol.AsfBootOptions.SpecialCommandParamLowByte &= (ENABLE_SECURE_ERASE | USE_KVM);
          mAsfProtocol.AsfBootOptions.OemParameterByte1          &= USE_SOL;
          mAsfProtocol.AsfBootOptions.BootOptionsMaskByte1        = 0;
          mAsfProtocol.AsfBootOptions.BootOptionsMaskByte2        = 0;
        } else {
          Status = ClearBootOptions ();
          if (EFI_ERROR (Status)) {
            DEBUG ((DEBUG_ERROR, "ME-BIOS: ASF: Get Boot Options Exit - Error by ClearBootOptions., Status: %r\n", Status));
            PostCode (0xEC9);
            return Status;
          }
        }
      }
    }
  }

  ///
  /// If we're asking for the options, then resend them to the debug output just encase they've been hosed.
  ///
  DEBUG ((DEBUG_INFO, "AsfBootOptions.SubCommand                  = 0x%x\n", mAsfProtocol.AsfBootOptions.SubCommand));
  DEBUG ((DEBUG_INFO, "AsfBootOptions.Version                     = 0x%x\n", mAsfProtocol.AsfBootOptions.Version));
  DEBUG ((DEBUG_INFO, "AsfBootOptions.IanaId                      = 0x%x\n", mAsfProtocol.AsfBootOptions.IanaId));
  DEBUG ((DEBUG_INFO, "AsfBootOptions.SpecialCommand              = 0x%x\n", mAsfProtocol.AsfBootOptions.SpecialCommand));
  DEBUG ((DEBUG_INFO, "AsfBootOptions.SpecialCommandParamHighByte = 0x%x\n", mAsfProtocol.AsfBootOptions.SpecialCommandParamHighByte));
  DEBUG ((DEBUG_INFO, "AsfBootOptions.SpecialCommandParamLowByte  = 0x%x\n", mAsfProtocol.AsfBootOptions.SpecialCommandParamLowByte));
  DEBUG ((DEBUG_INFO, "AsfBootOptions.BootOptionsMaskByte1        = 0x%x\n", mAsfProtocol.AsfBootOptions.BootOptionsMaskByte1));
  DEBUG ((DEBUG_INFO, "AsfBootOptions.BootOptionsMaskByte2        = 0x%x\n", mAsfProtocol.AsfBootOptions.BootOptionsMaskByte2));
  DEBUG ((DEBUG_INFO, "AsfBootOptions.OemParameterByte1           = 0x%x\n", mAsfProtocol.AsfBootOptions.OemParameterByte1));
  DEBUG ((DEBUG_INFO, "AsfBootOptions.OemParameterByte2           = 0x%x\n", mAsfProtocol.AsfBootOptions.OemParameterByte2));

  DEBUG ((DEBUG_INFO, "ME-BIOS: ASF: Get Boot Options Exit - Success.\n"));
  PostCode (0xE29);
  return EFI_SUCCESS;
}

/**
  The driver entry point - detect ASF support or not, if support, will install relative protocol.

  @param[in] ImageHandle          Handle for this drivers loaded image protocol.
  @param[in] SystemTable          EFI system table.

  @retval EFI_SUCCESS             The driver installed without error.
  @retval EFI_UNSUPPORTED         The chipset is unsupported by this driver.
  @retval EFI_OUT_OF_RESOURCES    Unable to allocate necessary data structures.
**/
EFI_STATUS
EFIAPI
AsfDxeEntryPoint (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
{
  EFI_STATUS                      Status;
  ME_BIOS_PAYLOAD_HOB             *MbpHob;

  DEBUG ((DEBUG_INFO, "AsfDxeEntryPoint start\n"));

  MbpHob = GetFirstGuidHob (&gMeBiosPayloadHobGuid);
  if (MbpHob == NULL) {
    DEBUG ((DEBUG_ERROR, "No MBP Data Protocol available\n"));
    return EFI_UNSUPPORTED;
  }

  if (MbpHob->MeBiosPayload.FwPlatType.RuleData.Fields.IntelMeFwImageType != IntelMeCorporateFw) {
    return EFI_UNSUPPORTED;
  }

  ZeroMem ((VOID *) &mAsfProtocol.AsfBootOptions, sizeof (ASF_BOOT_OPTIONS));

  Status = AsfGetBootOptions ();
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Get Boot Options from CSME fail\n"));
    return EFI_UNSUPPORTED;
  }

  ///
  /// Install the AlertStandardFormat interface
  ///
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gAlertStandardFormatProtocolGuid,
                  &mAsfProtocol,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}

