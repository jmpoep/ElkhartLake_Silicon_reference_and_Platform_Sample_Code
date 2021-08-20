/** @file
  This file contains the entry code to the Seed Protocol DXE.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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

#include <Uefi.h>
#include <Guid/EventGroup.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BaseCryptLib.h>
#include <Library/RngLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiLib.h>
#include <Library/DxeMeLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/BootloaderSeedProtocol.h>
#include <Library/ObbSeedProtocol.h>
#include "PersistentStorage.h"
#include "SeedProtocolCrypto.h"
#include "EmmcSnDxe.h"
#include "Library/PcdLib.h"

#if (BOOTLOADER_SEED_LEN != CSE_SEED_LEN)
#error "Seed lengths are different!"
#endif
#if (BOOTLOADER_SEED_INFO_LIST_MAX_ENTRIES < CSE_SEED_MAX_ENTRIES)
#error "Bootloader list is smaller than CSE list!"
#endif

/* Constant data */
#if FixedPcdGetBool(PcdTrustyEnabled) == 1
STATIC CONST UINT8                  TrustyInfo[]          = "trusty";
STATIC CONST UINTN                  TrustyInfoSize        = sizeof(TrustyInfo) - 1; /* Adjust for NULL */
STATIC CONST CHAR16                 TrustySeedSaltName[]  = L"TrustySeedSalt";
STATIC CONST UINT8                  AttKBInfo[]           = "Attestation Keybox Encryption Key";
STATIC CONST UINTN                  AttKBInfoSize         = sizeof(AttKBInfo) - 1;
#endif
#if FixedPcdGetBool(PcdPseEnabled) == 1
STATIC CONST UINT8                  ObbSeedInfo[]         = "PseSeed";
STATIC CONST UINTN                  ObbSeedInfoSize       = sizeof(ObbSeedInfo) - 1;
STATIC CONST CHAR16                 ObbSeedSaltName[]     = L"PseSeedSalt";
#endif
#if FixedPcdGetBool(PcdTrustyEnabled) == 1
STATIC CONST CHAR16                 DeviceIvVarName[]     = L"DeviceIv";
#endif

EFI_HANDLE                          mHandle                        = NULL;
#if FixedPcdGetBool(PcdTrustyEnabled) == 1
EFI_EVENT                           EfiReadyToBootEvent            = NULL;
EFI_EVENT                           EfiExitBootServicesEvent       = NULL;
STATIC BOOLEAN                      CachedIvValid                  = FALSE;
#endif
STATIC BOOTLOADER_FIXED_SEED_IV     CachedIv                       = {0};
#if FixedPcdGetBool(PcdTrustyEnabled) == 1
STATIC BOOTLOADER_ATTKB_ENC_KEY     AttestationKeyboxEncryptionKey = {0};
STATIC BOOTLOADER_RPMB_KEY          RpmbKey                        = {0};
STATIC BOOTLOADER_SEED_INFO_LIST    BLSInfo                        = {0};
#endif
#if FixedPcdGetBool(PcdPseEnabled) == 1
STATIC OBB_SEED_INFO_LIST           ObbInfo                        = {0};
#endif

/**
  Set debug (known constant) seeds.

  @param[in, out]   CseList  CSE bootloader seeds.

**/
STATIC
VOID
SetDebugCseSeeds (
BOOTLOADER_SEED_INFO_EX_LIST *CseList
)
{
  UINT8 SeedIndex;
  if (CseList->NumOfSvnSeeds == 0) {
    CseList->NumOfSvnSeeds = 1;
  }
  SetDebugSeed (CseList->FixedSeed.Seed, CSE_SEED_LEN);
  for (SeedIndex = 0; SeedIndex < CseList->NumOfSvnSeeds; SeedIndex++) {
    SetDebugSeed (&CseList->SVNSeedList[SeedIndex].Seed, CSE_SEED_LEN);
  }
}

/**
  Get default CSE fixed IV.

  @param[out]   FixedIv          CSE device IV.

**/
STATIC
VOID
GetDefaultCseFixedIv (
  BOOTLOADER_FIXED_SEED_IV *FixedIv
)
{
  UINT8 Idx;
  FixedIv->FixedSeedIvSize = sizeof(FixedIv->FixedSeedIv);
  for (Idx = 0; Idx < FixedIv->FixedSeedIvSize; Idx++) {
      FixedIv->FixedSeedIv[Idx] = Idx;
  }
}

#if FixedPcdGetBool(PcdTrustyEnabled) == 1
/**
  Expand CSE SVN seeds to generate Trusty seeds.

  @param[in]      CseList  CSE bootloader seeds.

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_DEVICE_ERROR       The command was unsuccessful.

**/
STATIC
EFI_STATUS
ExpandTrustySeeds (
  CONST BOOTLOADER_SEED_INFO_EX_LIST *CseList
)
{
  EFI_STATUS Status;
  UINT8 SeedIndex;
  UINT8 SeedSalt[SEED_SALT_SIZE] = {0x0};
  UINTN SeedSaltSize = sizeof (SeedSalt);

  /* Get seed salt from flash. */
  Status = GetSeedSalt (TrustySeedSaltName, SeedSalt,  &SeedSaltSize);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = EFI_SUCCESS;

  /* Generate trusty seeds. */
  BLSInfo.NumOfSeeds = CseList->NumOfSvnSeeds;
  for (SeedIndex = 0; SeedIndex < CseList->NumOfSvnSeeds; SeedIndex++) {
    BOOLEAN ReturnCode;

    BLSInfo.SeedList[SeedIndex].cse_svn     = CseList->SVNSeedList[SeedIndex].CseSvn;
    BLSInfo.SeedList[SeedIndex].bios_svn    = CseList->SVNSeedList[SeedIndex].BiosSvn;
    BLSInfo.SeedList[SeedIndex].Reserved[0] = 0;
    BLSInfo.SeedList[SeedIndex].Reserved[1] = 0;

    if (IsDebugSeed (CseList->SVNSeedList[SeedIndex].Seed,
              sizeof(CseList->SVNSeedList[SeedIndex].Seed))) {
      CopyMem (BLSInfo.SeedList[SeedIndex].seed,
          CseList->SVNSeedList[SeedIndex].Seed,
          sizeof(BLSInfo.SeedList[SeedIndex].seed)
          );
    } else {
      ReturnCode = HkdfSha256ExtractAndExpand (
          CseList->SVNSeedList[SeedIndex].Seed,
          sizeof(CseList->SVNSeedList[SeedIndex].Seed),
          SeedSalt,
          sizeof(SeedSalt),
          TrustyInfo,
          TrustyInfoSize,
          BLSInfo.SeedList[SeedIndex].seed,
          sizeof(BLSInfo.SeedList[SeedIndex].seed)
          );
      if (ReturnCode != TRUE) {
        ZeroMem(&BLSInfo.SeedList[SeedIndex], sizeof(BLSInfo.SeedList[SeedIndex]));
        Status = EFI_DEVICE_ERROR;
      }
    }
  }

  ZeroMem (&SeedSalt, sizeof(SeedSalt));
  return Status;
}

/**
  ValidateCachedIv

  Validate cached device IV used by CSE is correct.

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_NOT_FOUND          The cached IV was not found.
  @retval EFI_NOT_READY          Reboot operation did not succeed.
  @retval Others                 Operation was unsuccessful.

**/
STATIC
EFI_STATUS
ValidateCachedIv (VOID)
{
  EFI_STATUS                 Status = EFI_SUCCESS;
  BOOTLOADER_FIXED_SEED_IV   DeviceIv;

  DeviceIv.FixedSeedIvSize = sizeof(DeviceIv.FixedSeedIv);
  Status = GetFirstEmmcSerialNumber (&DeviceIv.FixedSeedIvSize, DeviceIv.FixedSeedIv);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (CompareMem (&DeviceIv, &CachedIv, sizeof (DeviceIv)) == 0) {
    /* Cached IV matches actual (device) IV. Return success. */
    CachedIvValid = TRUE;
    return EFI_SUCCESS;
  }

  /*
    The cached IV did not match the actual value or is missing (first boot).
    Update the cached value and reboot the platform.
    The cached IV does not need to be updated. The platform is being rebooted.
    It will be loaded on the next reboot.
  */
  Status = SavePersistentData (DeviceIvVarName, DeviceIv.FixedSeedIv, DeviceIv.FixedSeedIvSize);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "SeedProtocolDxe: SavePersistentData: %r\n", Status));
    return Status;
  }

  DEBUG ((DEBUG_INFO, "SeedProtocolDxe: eMMC serial number saved. System reboot needed.\n"));
  return EFI_NOT_READY;
}
#endif

/**
  Get CSE seeds

  @param[out]   CseList  CSE bootloader seeds.

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_DEVICE_ERROR       The command was unsuccessful.

**/
STATIC
EFI_STATUS
GetCseSeeds (
  BOOTLOADER_SEED_INFO_EX_LIST *CseList
)
{
  EFI_STATUS                 Status;
#if FixedPcdGetBool(PcdTrustyEnabled) == 1
  UINTN                      FixedSeedIvSize;

  /* Determine if the cached device specific IV if available. */
  /* If it is not, it will be saved at boot services ready    */
  /* and the platform is rebooted.                            */
  FixedSeedIvSize = sizeof (CachedIv.FixedSeedIv);
  Status = LoadPersistentData (DeviceIvVarName, CachedIv.FixedSeedIv, &FixedSeedIvSize);
  CachedIv.FixedSeedIvSize = (UINT8)FixedSeedIvSize;
  if (EFI_ERROR (Status)) {

    DEBUG ((DEBUG_INFO, "SeedProtocolDxe: Load cached IV - %r\n", Status));
#endif

    /* Don't return an error. Call CSE with a fixed IV       */
    /* to prevent an attacker from getting seeds from CSE.   */
    GetDefaultCseFixedIv (&CachedIv);

#if FixedPcdGetBool(PcdTrustyEnabled) == 1
    /* RPMB key is not valid */
    CachedIvValid = FALSE;
  }
#endif

  /* Get seeds from CSE */
  Status = HeciGetBootloaderSeedList (&CachedIv, CseList);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (!IsUEFISecureBootEnabled ()) {
    SetDebugCseSeeds (CseList);
  }

  return Status;
}

#if FixedPcdGetBool(PcdTrustyEnabled) == 1
/**
  Generate attestion keybox encryption key

  @param[in]      CseList  CSE bootloader seeds.
  @param[out]     Attestation keybox key

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_DEVICE_ERROR       The command was unsuccessful.

**/
EFI_STATUS
GenerateAttKb (
  CONST BOOTLOADER_SEED_INFO_EX_LIST *CseList,
  UINT8                              *AttKBKey
)
{
  EFI_STATUS Status;
  UINT8 SeedIndex;
  UINT8 MaxCseSvnIndex;

  /*
      Determine which seed has the highest CSE SVN.
      This seed is used for the attestion keybox encryption key.
  */
  MaxCseSvnIndex = 0;
  for (SeedIndex = 1; SeedIndex < CseList->NumOfSvnSeeds; SeedIndex++) {
    if (CseList->SVNSeedList[SeedIndex].CseSvn > CseList->SVNSeedList[MaxCseSvnIndex].CseSvn) {
      MaxCseSvnIndex = SeedIndex;
    }
  }

  /* Generate Attestion keybox encryption key. */
  Status = HmacSha256 (
              CseList->SVNSeedList[MaxCseSvnIndex].Seed,
              sizeof (CseList->SVNSeedList[MaxCseSvnIndex].Seed),
              AttKBInfo,
              AttKBInfoSize,
              AttKBKey
  );

  return Status;
}
#endif

#if FixedPcdGetBool(PcdPseEnabled) == 1
EFI_STATUS
ExpandObbSeeds (
  CONST BOOTLOADER_SEED_INFO_EX_LIST *CseList
)
{
  EFI_STATUS Status;
  UINT8 SeedIndex;
  UINT8 SeedSalt[SEED_SALT_SIZE] = {0x0};
  UINTN SeedSaltSize = sizeof (SeedSalt);

  /* Get seed salt from flash. */
  Status = GetSeedSalt (ObbSeedSaltName, SeedSalt,  &SeedSaltSize);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = EFI_SUCCESS;

  /* Generate OBB seeds. */
  ObbInfo.NumOfSeeds = CseList->NumOfSvnSeeds;
  for (SeedIndex = 0; SeedIndex < CseList->NumOfSvnSeeds; SeedIndex++) {
    BOOLEAN ReturnCode;

    ObbInfo.SeedList[SeedIndex].cse_svn     = CseList->SVNSeedList[SeedIndex].CseSvn;
    ObbInfo.SeedList[SeedIndex].bios_svn    = CseList->SVNSeedList[SeedIndex].BiosSvn;
    ObbInfo.SeedList[SeedIndex].Reserved[0] = 0;
    ObbInfo.SeedList[SeedIndex].Reserved[1] = 0;

    if (IsDebugSeed (CseList->SVNSeedList[SeedIndex].Seed,
              sizeof(CseList->SVNSeedList[SeedIndex].Seed))) {
      CopyMem (ObbInfo.SeedList[SeedIndex].seed,
          CseList->SVNSeedList[SeedIndex].Seed,
          sizeof(ObbInfo.SeedList[SeedIndex].seed)
          );
    } else {
      ReturnCode = HkdfSha256ExtractAndExpand (
          CseList->SVNSeedList[SeedIndex].Seed,
          sizeof(CseList->SVNSeedList[SeedIndex].Seed),
          SeedSalt,
          sizeof(SeedSalt),
          ObbSeedInfo,
          ObbSeedInfoSize,
          ObbInfo.SeedList[SeedIndex].seed,
          sizeof(ObbInfo.SeedList[SeedIndex].seed)
          );
      if (ReturnCode != TRUE) {
        ZeroMem(&ObbInfo.SeedList[SeedIndex], sizeof(ObbInfo.SeedList[SeedIndex]));
        Status = EFI_DEVICE_ERROR;
      }
    }
  }

  ZeroMem (&SeedSalt, sizeof(SeedSalt));
  return Status;
}
#endif

/**
  Generate Trusty seeds from CSE bootloader seeds.

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_DEVICE_ERROR       The command was unsuccessful.

**/
STATIC
EFI_STATUS
GenerateTrustySeeds ()
{
  EFI_STATUS Status;
  BOOTLOADER_SEED_INFO_EX_LIST  CseList = {0x0};

  /* Use do/while loop to exit block early on errors without using goto. */
  do {
    Status = GetCseSeeds (&CseList);
    if (EFI_ERROR (Status)) {
      break;
    }

#if FixedPcdGetBool(PcdTrustyEnabled) == 1
    /* RPMB Key */
    if (CachedIvValid) {
      RpmbKey.rpmb_key_size = sizeof(RpmbKey.rpmb_key);
      RpmbKey.rpmb_partition_no = 0;
      CopyMem (&RpmbKey.rpmb_key, CseList.FixedSeed.Seed, sizeof(RpmbKey.rpmb_key));
    } else {
      SetDebugSeed (&RpmbKey, sizeof (RpmbKey));
    }

    /* Attistation keybox */
    Status = GenerateAttKb (&CseList, AttestationKeyboxEncryptionKey.attkb_enc_key);
    if (EFI_ERROR (Status)) {
      break;
    }

    /* Bootloader seeds */
    Status = ExpandTrustySeeds (&CseList);
    if (EFI_ERROR (Status)) {
      break;
    }
#endif

#if FixedPcdGetBool(PcdPseEnabled) == 1
    /* PSE */
    Status = ExpandObbSeeds (&CseList);
    if (EFI_ERROR (Status)) {
      break;
    }
#endif

    Status = EFI_SUCCESS;

  } while (0);

  /* Clear CSE sensitive information no longer needed. */
  ZeroMem (&CseList, sizeof(CseList));

  return Status;
}

#if FixedPcdGetBool(PcdTrustyEnabled) == 1
/**
  Clear all trusty key material.

**/
STATIC
VOID
ClearTrustySeeds (
  VOID
)
{
  ZeroMem (&AttestationKeyboxEncryptionKey, sizeof(AttestationKeyboxEncryptionKey));
  ZeroMem (&RpmbKey, sizeof(RpmbKey));
  ZeroMem (&BLSInfo, sizeof(BLSInfo));
}

/* Bootloader Seed Protocol API function implementation */

/**
  Get the symmetric encryption key for Android Attestation Keybox.
  Kernelflinger will prepare for the data buffer, and the BIOS will copy the data to this buffer.

  @param[in, out]       buf      Buffer to fill with att kb key

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_DEVICE_ERROR       The command was unsuccessful.
  @retval EFI_INVALID_PARAMETER  One or more of the parameters are incorrect.

**/
STATIC
EFI_STATUS
GetAttKBEncKey (
  IN OUT BOOTLOADER_ATTKB_ENC_KEY *buf
  )
{
  // EFI_STATUS Status;

  DEBUG ((DEBUG_INFO,"SeedProtocolDxe: GetAttKBEncKey\n"));

  if (buf == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  /* Check to see if EndOfService has been called. */
  if (BLSInfo.NumOfSeeds == 0) {
    return EFI_DEVICE_ERROR;
  }

  CopyMem(buf, AttestationKeyboxEncryptionKey.attkb_enc_key, sizeof(BOOTLOADER_ATTKB_ENC_KEY_LEN));

  return EFI_SUCCESS;
}

/**
  Get the seed info list used by Trusty.
  Kernelflinger will prepare for the data buffer, and the BIOS will copy the data to this buffer.

  @param[in, out]       OutBLSList      Buffer to fill with Seed info list

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_DEVICE_ERROR       The command was unsuccessful.
  @retval EFI_INVALID_PARAMETER  One or more of the parameters are incorrect.

**/
STATIC
EFI_STATUS
GetSeedInfoList (
  IN OUT BOOTLOADER_SEED_INFO_LIST *OutBLSList
)
{
  // EFI_STATUS Status;
  UINT8 SeedIndex;

  DEBUG ((DEBUG_INFO,"SeedProtocolDxe: GetSeedInfoList\n"));

  if (OutBLSList == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  /* Check to see if EndOfService has been called. */
  if (BLSInfo.NumOfSeeds == 0) {
    return EFI_DEVICE_ERROR;
  }

  OutBLSList->NumOfSeeds = BLSInfo.NumOfSeeds;
  for (SeedIndex = 0; SeedIndex < OutBLSList->NumOfSeeds; SeedIndex++) {
    OutBLSList->SeedList[SeedIndex] = BLSInfo.SeedList[SeedIndex];
  }

  return EFI_SUCCESS;
}

/**
  Get the RPMB key. This key is derived from CSE Fixed seed.
  Kernelflinger will prepare for the data buffer, and the BIOS will copy the data to this buffer.

  @param[in, out]       num_keys   Number of RPMB keys
  @param[in, out]       buf        Buffer to fill with Seed info list

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_DEVICE_ERROR       The command was unsuccessful.
  @retval EFI_INVALID_PARAMETER  One or more of the parameters are incorrect.

**/
STATIC
EFI_STATUS
GetRpmbKey (
  IN OUT UINT8               *num_keys,
  IN OUT BOOTLOADER_RPMB_KEY *buf
  )
{
  EFI_STATUS    Status;

  DEBUG ((DEBUG_INFO,"SeedProtocolDxe: GetRpmbKey\n"));
  if (num_keys == NULL || buf == NULL || *num_keys == 0) {
    return EFI_INVALID_PARAMETER;
  }

  /* Check to see if EndOfService has been called. */
  if (BLSInfo.NumOfSeeds == 0) {
    return EFI_DEVICE_ERROR;
  }

  CopyMem (buf, RpmbKey.rpmb_key, RpmbKey.rpmb_key_size);
  *num_keys = 1;

  Status = EFI_SUCCESS;
  return Status;
}

/**
  This API can be invoked by OS loader application after it has consumed seeds.

  @retval EFI_SUCCESS            Operation completed successfully.

**/
STATIC
EFI_STATUS
EndOfService ()
{
  DEBUG ((DEBUG_INFO,"SeedProtocolDxe: EndOfService\n"));
  ClearTrustySeeds ();
  return EFI_SUCCESS;
}
#endif

#if FixedPcdGetBool(PcdPseEnabled) == 1
STATIC
EFI_STATUS
GetObbSeed (
  OUT OBB_SEED_INFO_LIST *buf
  )
{
  DEBUG ((DEBUG_INFO,"SeedProtocolDxe: GetObbSeed\n"));
  if (buf == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  CopyMem(buf, &ObbInfo, sizeof(ObbInfo));
  return EFI_SUCCESS;
}

/* OBB Protocol API vtable */

OBB_SEED_PROTOCOL mObbProtocol = {
  GetObbSeed,
};
#endif

#if FixedPcdGetBool(PcdTrustyEnabled) == 1
/* Bootloader Seed Protocol API vtable */
BOOTLOADER_SEED_PROTOCOL mCseProtocol = {
  EndOfService,
  GetSeedInfoList,
  GetRpmbKey,
  GetAttKBEncKey
};

/* Bootloader Seed Protocol API registration */

/**
  UnregisterSeedProtocolHandlers.

  Unregister trusty seed protocol.
  Trusty seed protocol is not available after boot services exit.

  @param  Event         Event whose notification function is being invoked.
  @param  Context       Pointer to the notification function's context, which is
                        always zero in current implementation.

**/
STATIC
VOID
EFIAPI
UnregisterSeedProtocolHandlers (
  IN EFI_EVENT        Event,
  IN VOID             *Context
  )
{
  DEBUG ((DEBUG_INFO,"SeedProtocolDxe: UnregisterSeedProtocol\n"));
  gBS->CloseEvent(Event);
  ClearTrustySeeds ();
  if (mHandle != NULL) {
    gBS->UninstallMultipleProtocolInterfaces (mHandle,
          &gEfiBootloaderSeedProtocolGuid,
          &mCseProtocol,
          NULL);
  }
}

/**
  ReadyToBoot.
  Validate the cached IV is valid and register Trusty protocol.
  The eMMC serial number is available but the CSE has been locked
  since core BIOS done (end of DXE).

  @param  Event         Event whose notification function is being invoked.
  @param  Context       Pointer to the notification function's context, which is
                        always zero in current implementation.

**/
STATIC
VOID
EFIAPI
ReadyToBoot (
  IN EFI_EVENT        Event,
  IN VOID             *Context
  )
{
  EFI_STATUS Status = EFI_SUCCESS;

  DEBUG ((DEBUG_INFO,"SeedProtocolDxe: ReadyToBoot\n"));

  gBS->CloseEvent(Event);

  /* Validate the cached vaule passed to the CSE was correct */
  Status = ValidateCachedIv ();
  if (EFI_ERROR (Status)) {
    return;
  }

  /* Cached IV is valid and Trusty seeds have been generated. */
  /* Register the trusy protocol.                             */
  gBS->InstallMultipleProtocolInterfaces (
    &mHandle,
    &gEfiBootloaderSeedProtocolGuid,
    &mCseProtocol,
    NULL
    );
}
#endif

/**
  Seed Protocol Entry
  @retval  status

**/
EFI_STATUS
SeedProtocolEntry (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS Status;

  Status = EFI_SUCCESS;

  /* CSE is not locked                       */
  /* eMMC serial number is not available     */
  /* Use cached serial number                */
  Status = GenerateTrustySeeds ();
  if (EFI_ERROR (Status)) {
    if (Status == EFI_NOT_FOUND) {
      Status = EFI_SUCCESS;
    } else {
      DEBUG ((DEBUG_INFO, "SeedProtocolDxe: GenerateSeeds %r\n", Status));
    }
  }

#if FixedPcdGetBool(PcdPseEnabled) == 1
  if (!EFI_ERROR (Status)) {
    gBS->InstallMultipleProtocolInterfaces (
      &mHandle,
      &gEfiObbSeedProtocolGuid,
      &mObbProtocol,
      NULL
      );
  }
#endif

#if FixedPcdGetBool(PcdTrustyEnabled) == 1
  if (!EFI_ERROR (Status)) {
    /* Callback when ReadyToBoot event is called by OS loader. */
    Status = gBS->CreateEventEx (
                    EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    ReadyToBoot,
                    NULL,
                    &gEfiEventReadyToBootGuid,
                    &EfiReadyToBootEvent
                    );
    ASSERT_EFI_ERROR (Status);
  }

  if (!EFI_ERROR (Status)) {
    /* Callback when exit event services is called by OS loader. */
    Status = gBS->CreateEventEx (
                    EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    UnregisterSeedProtocolHandlers,
                    NULL,
                    &gEfiEventExitBootServicesGuid,
                    &EfiExitBootServicesEvent
                    );
    ASSERT_EFI_ERROR (Status);
  }
#endif

  return Status;
}
