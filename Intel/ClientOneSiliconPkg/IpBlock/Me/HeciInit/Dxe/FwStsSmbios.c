/** @file
  Firmware Status Smbios Interface implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2020 Intel Corporation.

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
#include <Library/IoLib.h>
#include <Library/HobLib.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/Smbios.h>
#include <IndustryStandard/Pci22.h>
#include <MeFwHob.h>
#include <FwStsSmbiosTable.h>
#include <Library/PciSegmentLib.h>
#include <Library/MeShowBufferLib.h>
#include <Library/MeFwStsLib.h>

/**
  Create the FWSTS info to the SMBIOS table using the SMBIOS protocol
  Invoke this routine to add the table entry when all the FWSTS data is finalized.

  @param[in]  Event               - A pointer to the Event that triggered the callback.
                                    If the Event is not NULL, invoke DisableAllMeDevices () before exit
                                    because it is the event registered when failed to install HeciProtocol
                                    and locate SmbiosProtocol early
  @param[in]  Context             - A pointer to private data registered with the callback

  @retval EFI_SUCCESS             - if the data is successfully reported.
  @retval EFI_OUT_OF_RESOURCES    - if not able to get resources.
  @retval EFI_UNSUPPORTED         - if required DataHub or SMBIOS protocol is not available.
**/
VOID
EFIAPI
AddFwStsSmbiosEntry (
  IN  EFI_EVENT                   Event,
  IN  VOID                        *Context
  )
{
  EFI_STATUS                      Status;
  UINTN                           Size;
  FWSTS_SMBIOS_RECORD             *Record;
  UINT8                           Count;
  CHAR8                           *StringPtr;
  EFI_SMBIOS_PROTOCOL             *Smbios;
  ME_FW_HOB                       *MeFwHob;
  ME_FW_HOB                       *MeFwHobPool;
  UINT8                           Index;
  SMBIOS_TABLE_TYPE14             *SmbiosTableType14;
  static CHAR8                    T14String[sizeof (T14_FWSTS_STRING)] = T14_FWSTS_STRING;
  UINT32                          Function;
  UINT64                          DevicePciCfgBase;
  BOOLEAN                         *DisMeDevReq;

  DEBUG ((DEBUG_INFO, "%a () Start\n", __FUNCTION__));

  Record            = NULL;
  SmbiosTableType14 = NULL;
  MeFwHobPool       = NULL;
  DisMeDevReq       = (BOOLEAN *) Context;

  ///
  /// gSiPkgTokenSpaceGuid.PcdFwStsSmbiosType determines the SMBIOS OEM type (0x80 to 0xFF) defined
  /// in SMBIOS, values 0-0x7F will be treated as disable FWSTS SMBIOS reporting. OEM structure type
  /// is dynamic type extracted from the "Type 14 - Group Associations Structure" to avoid conflicts
  /// introduced by hardcode OEM type.
  /// FWSTS structure uses it as SMBIOS OEM type to provide FWSTS information.
  ///
  if (PcdGet8 (PcdFwStsSmbiosType) <= 0x7F) {
    DEBUG ((DEBUG_WARN, "FwStsSmbiosType value is 0x%x, it isn't defined as SMBIOS OEM type range(0x80 to 0xFF).\n", PcdGet8 (PcdFwStsSmbiosType)));
    DEBUG ((DEBUG_WARN, "FWSTS SMBIOS support is disabled now.\n"));
    goto ErrExit;
  }

  Status = gBS->LocateProtocol (&gEfiSmbiosProtocolGuid, NULL, (VOID **)&Smbios);
  if (Smbios == NULL) {
    goto ErrExit;
  }

  //
  // Get Mbp FW HOB
  //
  MeFwHob = GetFirstGuidHob (&gMeFwHobGuid);
  if (MeFwHob == NULL) {
    DEBUG ((DEBUG_WARN, "MeFwHob is not available\n"));
    MeFwHob = AllocateZeroPool (sizeof (ME_FW_HOB));
    if (MeFwHob != NULL) {
      for (Count = 0; Count < GetMeFwStsDeviceCount (); Count++) {
        MeFwHob->Group[Count].FunNumber = gFwStsDeviceList[Count].HeciDev;
      }
      MeFwHob->Count = Count;
      MeFwHobPool = MeFwHob;      // Free the temp pool before exit
    }
  }

  if (MeFwHob == NULL) {
    goto ErrExit;
  }

  ///
  /// Install SMBIOS Type14 - Group Associations Indicator structure
  /// Computed as 5 + (3 bytes for each item in the group).
  /// The user of this structure determines the number of items as (Length -5)/3.
  /// Add 1 bytes as table terminator.
  ///
  Size = sizeof (SMBIOS_TABLE_TYPE14) + AsciiStrSize (T14_FWSTS_STRING) + 1;

  SmbiosTableType14 = AllocateZeroPool (Size);
  if (SmbiosTableType14 == NULL) {
    goto ErrExit;
  }
  SmbiosTableType14->Hdr.Type = EFI_SMBIOS_TYPE_GROUP_ASSOCIATIONS;
  SmbiosTableType14->Hdr.Length = (UINT8) sizeof (SMBIOS_TABLE_TYPE14);
  SmbiosTableType14->Hdr.Handle = SMBIOS_HANDLE_PI_RESERVED;                // Assign an unused handle.
  SmbiosTableType14->GroupName  = 1;
  SmbiosTableType14->Group->ItemType = PcdGet8 (PcdFwStsSmbiosType);
  StringPtr = ((CHAR8 *) SmbiosTableType14) + SmbiosTableType14->Hdr.Length;
  AsciiStrCpyS (StringPtr, Size - SmbiosTableType14->Hdr.Length, T14String);

  DEBUG_CODE_BEGIN ();
  DEBUG ((DEBUG_INFO, "SmbiosTableType14 data printed for FWSTS SMBIOS support -\n"));
  ShowBuffer ((UINT8 *) SmbiosTableType14, (UINT32) Size);
  DEBUG_CODE_END ();

  Status = Smbios->Add (
                     Smbios,
                     NULL,
                     &SmbiosTableType14->Hdr.Handle,
                     (EFI_SMBIOS_TABLE_HEADER *) SmbiosTableType14
                     );

  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    goto ErrExit;
  }

  ///
  /// Install SMBIOS Type (PcdFwStsSmbiosType)
  /// Create full FWSTS SMBIOS record.
  /// Adjust size to include variable length strings,
  /// and set string numbers to point to the correct string.
  /// Add 1 bytes as table terminator.
  ///
  Size = sizeof (FWSTS_SMBIOS_RECORD) + (sizeof (FWSTS_SET_RECORD) * (MeFwHob->Count - 1)) +
         (AsciiStrSize (MEI1_FWSTS_STRING) * MeFwHob->Count) + 1;

  Record = AllocateZeroPool (Size);
  if (Record == NULL) {
    goto ErrExit;
  }
  Record->SmbiosHeader.Type   = PcdGet8 (PcdFwStsSmbiosType);
  Record->SmbiosHeader.Length = sizeof (FWSTS_SMBIOS_RECORD) + (sizeof (FWSTS_SET_RECORD) * (MeFwHob->Count - 1));
  Record->SmbiosHeader.Handle = SMBIOS_HANDLE_PI_RESERVED;                  // Assign an unused handle.
  Record->Version             = 1;
  Record->Count               = MeFwHob->Count;

  ///
  /// Copy the data from MeFwHob and update current FWSTS if the device is not disabled.
  /// If the device is disabled, report the FWSTS saved by MeFwHob directly
  ///
  StringPtr = ((CHAR8 *) Record) + Record->SmbiosHeader.Length;

  for (Count = 0; Count < MeFwHob->Count; Count++) {
    Record->Group[Count].ComponentName = (Count + 1);
    Function = MeFwHob->Group[Count].FunNumber;
    DevicePciCfgBase = PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, Function, 0);

    if (PciSegmentRead16 (DevicePciCfgBase + PCI_DEVICE_ID_OFFSET) != 0xFFFF) {
      //
      // Read current FWSTS and report to SMBIOS directly
      //
      for (Index = 0; Index < GetMeFwStsOffsetCount (); Index++) {
        Record->Group[Count].Reg[Index] = PciSegmentRead32 (DevicePciCfgBase + gFwStsOffsetTable[Index]);
      }
    } else {
      //
      // The device is disabled, report the FWSTS saved by MeFwHob directly
      //
      CopyMem (
        &(Record->Group[Count].Reg),
        &(MeFwHob->Group[Count].Reg),
        (sizeof (FWSTS_SET_RECORD) - 1));
    }

    DEBUG_CODE (
      ShowBuffer ((UINT8 *)&(Record->Group[Count]), sizeof (FWSTS_SET_RECORD));
      );

    ///
    /// Fill in corresponding string context for componentName
    ///
    for (Index = 0; Index < GetMeFwStsDeviceCount (); Index++) {
      if ((UINT32) gFwStsDeviceList[Index].HeciDev == Function) {
        AsciiStrCpyS (StringPtr, Size - Record->SmbiosHeader.Length, gFwStsDeviceList[Index].String);
        StringPtr += AsciiStrSize (gFwStsDeviceList[Index].String);
        Size -= AsciiStrSize (gFwStsDeviceList[Index].String);
        break;
      }
    }
  }

  DEBUG_CODE_BEGIN ();
  DEBUG ((DEBUG_INFO, "FWSTS SMBIOS table OEM type 0x%x data printed - \n", Record->SmbiosHeader.Type));
  ShowBuffer ((UINT8 *) Record, (UINT32) Size);
  DEBUG_CODE_END ();
  Status = Smbios->Add (
                     Smbios,
                     NULL,
                     &Record->SmbiosHeader.Handle,
                     (EFI_SMBIOS_TABLE_HEADER *) Record
                     );
  ASSERT_EFI_ERROR (Status);

ErrExit:
  if (Event != NULL) {
    gBS->CloseEvent (Event);
  }

  if ((DisMeDevReq != NULL) && (*DisMeDevReq == TRUE)) {
    DEBUG ((DEBUG_WARN, "[HECI1] Removing ME devices from config space!\n"));
    DisableAllMeDevices ();
  }

  //
  // Free all temp pools
  //
  if (MeFwHobPool != NULL) {
    FreePool (MeFwHobPool);
  }
  if (Record != NULL) {
    FreePool (Record);
  }
  if (SmbiosTableType14 != NULL) {
    FreePool (SmbiosTableType14);
  }
}
