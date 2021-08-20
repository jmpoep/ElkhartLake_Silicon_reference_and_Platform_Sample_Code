/** @file
  Platform specific TPM2 component.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2017 Intel Corporation.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be 
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:

**/

#include <PiDxe.h>

#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseLib.h>
#include <Library/Tpm2CommandLib.h>
#include <Library/PcdLib.h>
#include <Library/BaseCryptLib.h>
#include <Library/UefiLib.h>
#include <Library/PlatformSecureLib.h>
#include <Protocol/DxeSmmReadyToLock.h>
#include <Guid/EventGroup.h>

typedef enum {
  Tpm2NvAux,
  Tpm2NvPs,
  Tpm2NvPo,
  Tpm2NvTypeMax
} TPM2_PROVISION_NV_TYPE;

#define NV_INDEX_AUX  0x01800003
#define NV_INDEX_PS   0x01800001
#define NV_INDEX_PO   0x01400001

TPMI_RH_NV_INDEX   mTpm2ProvisionNvIndex[] = {
  NV_INDEX_AUX,
  NV_INDEX_PS,
  NV_INDEX_PO,
};

// The authorization value may be no larger than the digest produced by the hash algorithm used for context integrity.
#define MAX_NEW_AUTHORIZATION_SIZE        SHA512_DIGEST_SIZE
UINT16       mAuthSize;
TPM2B_AUTH   mNewPlatformAuth;
TPM2B_AUTH   mNewLockoutAuth;
TPM2B_AUTH   mNewOwnerAuth;

// Requested feature:
//1. Platform BIOS shall set PH's platformPolicy using TPM 2.0 command TPM2_SetPrimaryPolicy()
//2. It shall use HashAlg == SHA256
//3. authPolicy digest to be set must be the digest of the following negotiated policy command: TPM2_PolicyOR (0, SHA256 ("IntelTXT"))
//This digest is selected to match value used by server platform BIOS which creates consistency of support between TXT tools and provisioning scripts.
//4. Important note - the fixed selected passphrase "IntelTXT" is used to enable Intel reference BIOS and internal and external testing. It is assumed that each of the OEMs will select own passphrase and / or own set of TPM2.0 EA policy commands.
TPM2B_DIGEST mNewPlatformPolicy = {0x20,
{0x22, 0x03, 0x0B, 0x7E, 0x0B, 0xB1, 0xf9, 0xD5, 0x06, 0x57, 0x57, 0x1E, 0xE2, 0xF7, 0xFC, 0xE1,
 0xEB, 0x91, 0x99, 0x0C, 0x8B, 0x8A, 0xE9, 0x77, 0xFC, 0xB3, 0xF1, 0x58, 0xB0, 0x3E, 0xBA, 0x96}
};

/**
  This service returns the platform auth value.

  @param[in]  This                     Indicates the calling context
  @param[out] AuthSize                 Tpm2 Auth size

  @retval EFI_SUCCESS            Auth size returned.
  @retval EFI_SECURITY_VIOLATION Can not return platform auth due to security reason.
**/
EFI_STATUS
EFIAPI
GetAuthSize (
  OUT UINT16                    *AuthSize
  )
{
  EFI_STATUS                        Status;
  TPML_PCR_SELECTION                Pcrs;
  UINTN                             Index;
  UINT16                            DigestSize;

  if (mAuthSize == 0) {
    Status = Tpm2GetCapabilityPcrs (&Pcrs);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Tpm2GetCapabilityPcrs fail!\n"));
      mAuthSize = SHA1_DIGEST_SIZE;
    } else {
      mAuthSize = MAX_NEW_AUTHORIZATION_SIZE;
      DEBUG ((DEBUG_ERROR, "Tpm2GetCapabilityPcrs - %08x\n", Pcrs.count));
      DigestSize = SHA1_DIGEST_SIZE;
      for (Index = 0; Index < Pcrs.count; Index++) {
        DEBUG ((DEBUG_ERROR, "alg - %x\n", Pcrs.pcrSelections[Index].hash));
        switch (Pcrs.pcrSelections[Index].hash) {
        case TPM_ALG_SHA1:
          DigestSize = SHA1_DIGEST_SIZE;
          break;
        case TPM_ALG_SHA256:
          DigestSize = SHA256_DIGEST_SIZE;
          break;
        case TPM_ALG_SHA384:
          DigestSize = SHA384_DIGEST_SIZE;
          break;
        case TPM_ALG_SHA512:
          DigestSize = SHA512_DIGEST_SIZE;
          break;
        case TPM_ALG_SM3_256:
          DigestSize = SM3_256_DIGEST_SIZE;
          break;
        }
        if (DigestSize < mAuthSize) {
          mAuthSize = DigestSize;
        }
      }
    }
  }

  *AuthSize = mAuthSize;

  return EFI_SUCCESS;
}

/**

  This function dump raw data.

  @param  Data  raw data
  @param  Size  raw data size

**/
VOID
InternalDumpData (
  IN UINT8  *Data,
  IN UINTN  Size
  )
{
  UINTN  Index;
  for (Index = 0; Index < Size; Index++) {
    DEBUG ((DEBUG_ERROR, "%02x", (UINTN)Data[Index]));
  }
}

/**

  This function dump raw data with colume format.

  @param  Data  raw data
  @param  Size  raw data size

**/
VOID
InternalDumpHex (
  IN UINT8  *Data,
  IN UINTN  Size
  )
{
  UINTN   Index;
  UINTN   Count;
  UINTN   Left;

#define COLUME_SIZE  (16 * 2)

  Count = Size / COLUME_SIZE;
  Left  = Size % COLUME_SIZE;
  for (Index = 0; Index < Count; Index++) {
    DEBUG ((DEBUG_ERROR, "%04x: ", Index * COLUME_SIZE));
    InternalDumpData (Data + Index * COLUME_SIZE, COLUME_SIZE);
    DEBUG ((DEBUG_ERROR, "\n"));
  }

  if (Left != 0) {
    DEBUG ((DEBUG_ERROR, "%04x: ", Index * COLUME_SIZE));
    InternalDumpData (Data + Index * COLUME_SIZE, Left);
    DEBUG ((DEBUG_ERROR, "\n"));
  }
}

/**
  Read the public area and Name of an NV Index.

  @param[in]  NvType             NV type.

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_DEVICE_ERROR       The command was unsuccessful.
  @retval EFI_NOT_FOUND          The command was returned successfully, but NvIndex is not found.
**/
EFI_STATUS
ReadPublic (
  IN TPM2_PROVISION_NV_TYPE  NvType
  )
{
  EFI_STATUS                Status;
  TPMI_RH_NV_INDEX          NvIndex;
  TPM2B_NV_PUBLIC           NvPublic;
  TPM2B_NAME                NvName;

  ZeroMem (&NvPublic, sizeof(NvPublic));
  ZeroMem (&NvName, sizeof(NvName));

  NvIndex = mTpm2ProvisionNvIndex[NvType];

  Status = Tpm2NvReadPublic (NvIndex, &NvPublic, &NvName);
  if (EFI_ERROR (Status) && (Status != EFI_NOT_FOUND)) {
    DEBUG ((DEBUG_ERROR, "ReadPublic - TPM NvIndex(0x%08x) device error\n", NvIndex));
    return Status;
  }
  if (Status == EFI_NOT_FOUND) {
    // TPM NvIndex not found
    DEBUG ((DEBUG_ERROR, "ReadPublic - TPM NvIndex(0x%08x) not found\n", NvIndex));
  } else {
    // TPM NvIndex found
    DEBUG ((DEBUG_ERROR, "ReadPublic - TPM NvIndex(0x%08x) found\n", NvIndex));

    // DumpData
    DEBUG ((DEBUG_ERROR, "NvPublicSize        - 0x%04x\n", NvPublic.size));
    DEBUG ((DEBUG_ERROR, "  nvIndex           - 0x%08x\n", NvPublic.nvPublic.nvIndex));
    DEBUG ((DEBUG_ERROR, "  nameAlg           - 0x%04x\n", NvPublic.nvPublic.nameAlg));
    DEBUG ((DEBUG_ERROR, "  attributes        - 0x%08x\n", ReadUnaligned32 ((UINT32 *)&NvPublic.nvPublic.attributes)));
    DEBUG ((DEBUG_ERROR, "  authPolicy.size   - 0x%04x\n", NvPublic.nvPublic.authPolicy.size));
    DEBUG ((DEBUG_ERROR, "  authPolicy.buffer - "));
    InternalDumpData (NvPublic.nvPublic.authPolicy.buffer, NvPublic.nvPublic.authPolicy.size);
    DEBUG ((DEBUG_ERROR, "\n"));
    DEBUG ((DEBUG_ERROR, "  dataSize          - 0x%04x\n", NvPublic.nvPublic.dataSize));
    DEBUG ((DEBUG_ERROR, "NvNameSize          - 0x%04x\n", NvName.size));
    DEBUG ((DEBUG_ERROR, "  NvName.buffer - "));
    InternalDumpData (NvName.name, NvName.size);
    DEBUG ((DEBUG_ERROR, "\n"));
  }
  return Status;
}

/**
  Return if we have TXT provision.

  @retval TRUE  TXT provision detected.
  @retval FALSE TXT provision not detected.
**/
BOOLEAN
HasTxtProvision (
  VOID
  )
{
  EFI_STATUS  AuxStatus;

  AuxStatus = ReadPublic (Tpm2NvAux);
  ReadPublic (Tpm2NvPs);
  ReadPublic (Tpm2NvPo);

  //
  // Use AuxStatus as final result
  //
  if (!EFI_ERROR (AuxStatus)) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
  Set new platform auth.

  @param[in]  AuthHandle               TPM_RH_LOCKOUT, TPM_RH_ENDORSEMENT, TPM_RH_OWNER or TPM_RH_PLATFORM+{PP}

**/
VOID
SetNewAuthInfo (
  IN TPMI_RH_HIERARCHY_AUTH     AuthHandle
  )
{
  UINT16   AuthSize;

  GetAuthSize (&AuthSize);

  switch (AuthHandle) {
  case TPM_RH_PLATFORM:
    mNewPlatformAuth.size = AuthSize;
    RandomSeed (NULL, 0);
    RandomBytes (mNewPlatformAuth.buffer, mNewPlatformAuth.size);
    break;
  case TPM_RH_LOCKOUT:
    mNewLockoutAuth.size = AuthSize;
    RandomSeed (NULL, 0);
    RandomBytes (mNewLockoutAuth.buffer, mNewLockoutAuth.size);
    break;
  case TPM_RH_OWNER:
    mNewOwnerAuth.size = AuthSize;
    RandomSeed (NULL, 0);
    RandomBytes (mNewOwnerAuth.buffer, mNewOwnerAuth.size);
    break;
  default:
    ASSERT (FALSE);
    break;
  }

  return ;
}

/**
  Send platform hierarchy change auth, with reprovision Endorsement/Platform/Storage Hierarchy, based on request.
**/
VOID
HierarchyChangeAuthPlatform (
  VOID
  )
{
  EFI_STATUS                Status;
  TPMS_AUTH_COMMAND         LocalAuthSession;

  DEBUG ((DEBUG_ERROR, "HierarchyChangeAuthPlatform\n"));
  if (PcdGetBool (PcdTpm2HierarchyChangeAuthPlatform)) {
    SetNewAuthInfo (TPM_RH_PLATFORM);

    ZeroMem (&LocalAuthSession, sizeof(LocalAuthSession));
    LocalAuthSession.sessionHandle = TPM_RS_PW;
    LocalAuthSession.hmac.size = mNewPlatformAuth.size;
    CopyMem (LocalAuthSession.hmac.buffer, mNewPlatformAuth.buffer, mNewPlatformAuth.size);

    // Program Primary Policy, need localAuthSession to be NULL, response 9A2 if set
    if (PcdGetBool (PcdTpm2TxtProvisionSupport)) {
      Status = Tpm2SetPrimaryPolicy (TPM_RH_PLATFORM, NULL, &mNewPlatformPolicy, TPM_ALG_SHA256);
      DEBUG ((DEBUG_INFO, "Tpm2SetPrimaryPolicy - %r\n", Status));
      if (EFI_ERROR (Status)) {
        goto Done;
      }
    }

    Status = Tpm2HierarchyChangeAuth (TPM_RH_PLATFORM, NULL, &mNewPlatformAuth);
    DEBUG((DEBUG_INFO, "Tpm2HierarchyChangeAuth - %r\n", Status));
    if (EFI_ERROR (Status)) {
      ZeroMem (&mNewPlatformAuth, sizeof(mNewPlatformAuth));
      goto Done;
    }

    //
    // reprovision Endorsement Hierarchy
    //
    if (PcdGetBool (PcdTpm2ChangeEps)) {
      Status = Tpm2ChangeEPS (TPM_RH_PLATFORM, &LocalAuthSession);
      DEBUG((DEBUG_INFO, "Tpm2ChangeEPS - %r\n", Status));
      if (!EFI_ERROR (Status)) {
        PcdSetBoolS (PcdTpm2ChangeEps, FALSE);
      }
    }
    //
    // reprovision Platform Hierarchy
    //
    if (PcdGetBool (PcdTpm2ChangePps)) {
      Status = Tpm2ChangePPS (TPM_RH_PLATFORM, &LocalAuthSession);
      DEBUG((DEBUG_INFO, "Tpm2ChangePPS - %r\n", Status));
      if (!EFI_ERROR (Status)) {
        PcdSetBoolS (PcdTpm2ChangePps, FALSE);
      }
    }
    //
    // reprovision Storage Hierarchy
    //
    if (PcdGetBool (PcdTpm2Clear)) {
      Status = Tpm2ClearControl (TPM_RH_PLATFORM, &LocalAuthSession, NO);
      DEBUG((DEBUG_INFO, "Tpm2ClearControl - %r\n", Status));
      if (!EFI_ERROR (Status)) {
        Status = Tpm2Clear (TPM_RH_PLATFORM, &LocalAuthSession);
        DEBUG((DEBUG_INFO, "Tpm2Clear - %r\n", Status));
        if (!EFI_ERROR (Status)) {
          PcdSetBoolS (PcdTpm2Clear, FALSE);
        }
      }
    }

    //
    // enable or disable Endorsement Hierarchy
    //
    if (PcdGetBool (PcdTpm2HierarchyControlEndorsement)) {
      Status = Tpm2HierarchyControl (TPM_RH_PLATFORM, &LocalAuthSession, TPM_RH_ENDORSEMENT, YES);
      DEBUG((DEBUG_INFO, "Tpm2HierarchyControl (0x%08x, %02x)- %r\n", TPM_RH_ENDORSEMENT, YES, Status));
    } else {
      Status = Tpm2HierarchyControl (TPM_RH_PLATFORM, &LocalAuthSession, TPM_RH_ENDORSEMENT, NO);
      DEBUG((DEBUG_INFO, "Tpm2HierarchyControl (0x%08x, %02x)- %r\n", TPM_RH_ENDORSEMENT, NO, Status));
    }
    //
    // enable or disable Storage Hierarchy
    //
    if (PcdGetBool (PcdTpm2HierarchyControlOwner)) {
      Status = Tpm2HierarchyControl (TPM_RH_PLATFORM, &LocalAuthSession, TPM_RH_OWNER, YES);
      DEBUG((DEBUG_INFO, "Tpm2HierarchyControl (0x%08x, %02x)- %r\n", TPM_RH_OWNER, YES, Status));
    } else {
      Status = Tpm2HierarchyControl (TPM_RH_PLATFORM, &LocalAuthSession, TPM_RH_OWNER, NO);
      DEBUG((DEBUG_INFO, "Tpm2HierarchyControl (0x%08x, %02x)- %r\n", TPM_RH_OWNER, NO, Status));
    }
  }

Done:
  ZeroMem (&LocalAuthSession.hmac, sizeof(LocalAuthSession.hmac));
  return ;
}

/**
  This is the Event call back function to notify the Library the system is entering
  run time phase.

  @param  Event   Pointer to this event
  @param  Context Event hanlder private data
 **/
VOID
EFIAPI
ReadyToLockEventCallBack (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  EFI_STATUS             Status;
  VOID                   *Interface;
  TPMS_AUTH_COMMAND      LocalAuthSession;

  //
  // Try to locate it because EfiCreateProtocolNotifyEvent will trigger it once when registration.
  // Just return if it is not found.
  //
  Status = gBS->LocateProtocol (
                  &gEfiDxeSmmReadyToLockProtocolGuid,
                  NULL,
                  &Interface
                  );
  if (EFI_ERROR (Status)) {
    return ;
  }

  HierarchyChangeAuthPlatform ();

  ZeroMem (&LocalAuthSession, sizeof(LocalAuthSession));
  LocalAuthSession.sessionHandle = TPM_RS_PW;
  LocalAuthSession.hmac.size = mNewPlatformAuth.size;
  CopyMem (LocalAuthSession.hmac.buffer, mNewPlatformAuth.buffer, mNewPlatformAuth.size);

  if (PcdGetBool (PcdTpm2HierarchyChangeAuthPlatform)) {
    //
    // enable or disable Platform Hierarchy
    //
    if (PcdGetBool (PcdTpm2HierarchyControlPlatform)) {
      Status = Tpm2HierarchyControl (TPM_RH_PLATFORM, &LocalAuthSession, TPM_RH_PLATFORM, YES);
      DEBUG((DEBUG_INFO, "Tpm2HierarchyControl (0x%08x, %02x)- %r\n", TPM_RH_PLATFORM, YES, Status));
    } else {
      Status = Tpm2HierarchyControl (TPM_RH_PLATFORM, &LocalAuthSession, TPM_RH_PLATFORM, NO);
      DEBUG((DEBUG_INFO, "Tpm2HierarchyControl (0x%08x, %02x)- %r\n", TPM_RH_PLATFORM, NO, Status));
    }
  }

  //
  // Clear Secrets
  //
  ZeroMem (&mNewPlatformAuth, sizeof(mNewPlatformAuth));
  ZeroMem (&mNewLockoutAuth, sizeof(mNewLockoutAuth));
  ZeroMem (&mNewOwnerAuth, sizeof(mNewOwnerAuth));
  ZeroMem (&LocalAuthSession.hmac, sizeof(LocalAuthSession.hmac));

  gBS->CloseEvent (Event);
}

/**
  The driver's entry point.

  @param[in] ImageHandle  The firmware allocated handle for the EFI image.
  @param[in] SystemTable  A pointer to the EFI System Table.

  @retval EFI_SUCCESS     The entry point is executed successfully.
  @retval other           Some error occurs when executing this entry point.
**/
EFI_STATUS
EFIAPI
DriverEntry (
  IN    EFI_HANDLE                  ImageHandle,
  IN    EFI_SYSTEM_TABLE            *SystemTable
  )
{
  VOID                      *Registration;
  EFI_EVENT                 Event;

  Event = EfiCreateProtocolNotifyEvent  (
            &gEfiDxeSmmReadyToLockProtocolGuid,
            TPL_CALLBACK,
            ReadyToLockEventCallBack,
            NULL,
            &Registration
            );
  ASSERT (Event != NULL);

  return EFI_SUCCESS;
}
