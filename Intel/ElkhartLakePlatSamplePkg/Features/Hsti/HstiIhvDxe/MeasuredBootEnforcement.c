/** @file
  This file contains the tests for the MeasuredBootEnforcement BIT

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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

#include "HstiIhvDxe.h"
#include <Register/FlashRegs.h>

TPM2B_AUTH             mNewPlatformAuth;

/**
  Check if buffer is all zero.

  @param[in] Buffer      Buffer to be checked.
  @param[in] BufferSize  Size of buffer to be checked.

  @retval TRUE  Buffer is all zero.
  @retval FALSE Buffer is not all zero.
**/
BOOLEAN
IsZeroBufferLocal (
  IN VOID  *Buffer,
  IN UINTN BufferSize
  )
{
  UINT8 *BufferData;
  UINTN Index;

  BufferData = Buffer;
  for (Index = 0; Index < BufferSize; Index++) {
    if (BufferData[Index] != 0) {
      return FALSE;
    }
  }
  return TRUE;
}

/**
  Run tests for MeasuredBootEnforcement bit
**/
VOID
CheckMeasuredBootEnforcement (
  VOID
  )
{
  EFI_STATUS                Status;
  BOOLEAN                   Result;
  BOOLEAN                   TpmPresent;
  TPML_PCR_SELECTION        PcrSelectionIn;
  UINT32                    PcrUpdateCounter;
  TPML_PCR_SELECTION        PcrSelectionOut;
  TPML_DIGEST               PcrValues;
  TPML_PCR_SELECTION        Pcrs;
  UINT32                    Index;
  BOOLEAN                   Pcr7Initialized;
  UINTN                     Index3;
  EFI_PHYSICAL_ADDRESS      EventLogLocation;
  EFI_PHYSICAL_ADDRESS      EventLogLastEntry;
  BOOLEAN                   EventLogTruncated;
  TPMS_AUTH_COMMAND         LocalAuthSession;
  UINT16                    AuthSize;
  UINT32                    ActivePCRBanks;
  UINT32                    TpmVerFtifFtLocMask;
  UINT8                     ValueAtTpmBaseAddress;
  EFI_TCG2_PROTOCOL         *Tcg2Protocol = NULL;

  ValueAtTpmBaseAddress = *(UINT8 *) (UINTN) TPM_BASE_ADDRESS;

  if ((mFeatureImplemented[0] & HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT) == 0) {
    return;
  }

  Result     = TRUE;
  TpmPresent = TRUE;
  Status     = EFI_SUCCESS;

  DEBUG ((DEBUG_INFO, "      Chipset supports FW TPM or dTPM Test\n"));
  DEBUG ((DEBUG_INFO, "        If chipset supports FW TPM it must be enabled or the platform must have a dTPM\n"));

  TpmVerFtifFtLocMask =  MmioRead32 (TXT_PUBLIC_BASE + 0x800) & TPM_VER_FTIF_FT_LOC_MASK;
  DEBUG ((DEBUG_INFO, "        TPM Location configured (expected values: dTPM = 0x5 or fTPM = 0x7) = 0x%x\n", (TpmVerFtifFtLocMask >> 16)));
  DEBUG ((DEBUG_INFO, "        Value at TPM Base Address (0x%x) = 0x%x\n", TPM_BASE_ADDRESS, ValueAtTpmBaseAddress));
  if ((((TpmVerFtifFtLocMask & DTPM_LOC) != DTPM_LOC) &&
      ((TpmVerFtifFtLocMask & FTPM_LOC) != FTPM_LOC)) ||
       (ValueAtTpmBaseAddress == 0xFF)) {

    DEBUG ((DEBUG_INFO, "        Unexpected Status: FW TPM not configured or no dTPM present on system\n"));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT_UNEXP_STATUS_CODE_1,
      HSTI_MEASURED_BOOT_CONFIGURATION,
      HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT_UNEXP_STATUS_STRING_1
      );
    Result = FALSE;
    TpmPresent = FALSE;
  }

  DEBUG ((DEBUG_INFO, "      PCR[7] Initialization Check Test\n"));

  ZeroMem (&PcrSelectionIn, sizeof (PcrSelectionIn));
  ZeroMem (&PcrUpdateCounter, sizeof (UINT32));
  ZeroMem (&PcrSelectionOut, sizeof (PcrSelectionOut));
  ZeroMem (&PcrValues, sizeof (PcrValues));
  ZeroMem (&Pcrs, sizeof (TPML_PCR_SELECTION));
  Pcr7Initialized = FALSE;

  if (TpmPresent == TRUE) {
    Status = Tpm2GetCapabilityPcrs (&Pcrs);

    for (Index3 = 0; Index3 < Pcrs.count; Index3++) {
      PcrSelectionIn.pcrSelections[PcrSelectionIn.count].hash = Pcrs.pcrSelections[Index3].hash;
      PcrSelectionIn.pcrSelections[PcrSelectionIn.count].sizeofSelect = PCR_SELECT_MAX;
      PcrSelectionIn.pcrSelections[PcrSelectionIn.count].pcrSelect[0] = 0x80;
      PcrSelectionIn.pcrSelections[PcrSelectionIn.count].pcrSelect[1] = 0x00;
      PcrSelectionIn.pcrSelections[PcrSelectionIn.count].pcrSelect[2] = 0x00;
      PcrSelectionIn.count++;
    }

    Tpm2PcrRead (&PcrSelectionIn,&PcrUpdateCounter,&PcrSelectionOut,&PcrValues);

    for (Index = 0; Index < PcrValues.count; Index++) {
      Pcr7Initialized = !IsZeroBufferLocal (PcrValues.digests[Index].buffer,PcrValues.digests[Index].size);
      if (Pcr7Initialized  == FALSE) {
        DEBUG ((DEBUG_INFO, "        Unexpected Status: Pcr[7] not initialized\n"));
        break;
      }
    }
  }

  if ( (Pcr7Initialized == FALSE)  || (TpmPresent != TRUE)) {
    BuildAndAppendHstiStatusString (
      HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT_UNEXP_STATUS_CODE_2,
      HSTI_MEASURED_BOOT_CONFIGURATION,
      HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT_UNEXP_STATUS_STRING_2
      );
    Result = FALSE;
  }

  DEBUG ((DEBUG_INFO, "      Event log published Test\n"));

  EventLogLocation = (EFI_PHYSICAL_ADDRESS) NULL;
  if (TpmPresent == TRUE) {

    Status = gBS->LocateProtocol (
                    &gEfiTcg2ProtocolGuid,
                    NULL,
                    (VOID **)&Tcg2Protocol
                    );

    if (!EFI_ERROR ( Status )) {
      Status = Tcg2Protocol->GetActivePcrBanks (Tcg2Protocol, &ActivePCRBanks);

      if(!EFI_ERROR ( Status )) {
        //
        // If only SHA1 than follow TCG 1.2 event log format
        //
        if(ActivePCRBanks == EFI_TCG2_BOOT_HASH_ALG_SHA1) {
          Status = Tcg2Protocol->GetEventLog (
                                   Tcg2Protocol,
                                   EFI_TCG2_EVENT_LOG_FORMAT_TCG_1_2,
                                   &EventLogLocation,
                                   &EventLogLastEntry,
                                   &EventLogTruncated
                                   );
        } else if(ActivePCRBanks != 0) {
           //
           // All other SHA's follows TCG 2 event log format
           //
          Status = Tcg2Protocol->GetEventLog (
                                   Tcg2Protocol,
                                   EFI_TCG2_EVENT_LOG_FORMAT_TCG_2,
                                   &EventLogLocation,
                                   &EventLogLastEntry,
                                   &EventLogTruncated
                                   );
        }
      }
    }
    DEBUG ((DEBUG_INFO, "        EventLogLocation - EventLogLocation - %x\n", EventLogLocation));

  }

  if (EFI_ERROR (Status) ||
      (EventLogLocation == (EFI_PHYSICAL_ADDRESS) NULL) ||
      (TpmPresent != TRUE)) {
    DEBUG ((DEBUG_INFO, "        Unexpected Status: Event log is not published and must be\n"));

    BuildAndAppendHstiStatusString (
              HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT_UNEXP_STATUS_CODE_3,
              HSTI_MEASURED_BOOT_CONFIGURATION,
              HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT_UNEXP_STATUS_STRING_3
              );
    Result = FALSE;
  }

  DEBUG ((DEBUG_INFO, "      Platform Auth Value All Zero Test\n"));

  if ( TpmPresent == TRUE ) {
    AuthSize = MAX_NEW_AUTHORIZATION_SIZE;
    for (Index = 0; Index < Pcrs.count; Index++) {
      switch (Pcrs.pcrSelections[Index].hash) {
        case TPM_ALG_SHA1:
          AuthSize = SHA1_DIGEST_SIZE;
          break;
        case TPM_ALG_SHA256:
          AuthSize = SHA256_DIGEST_SIZE;
          break;
        case TPM_ALG_SHA384:
          AuthSize = SHA384_DIGEST_SIZE;
          break;
        case TPM_ALG_SHA512:
          AuthSize = SHA512_DIGEST_SIZE;
          break;
        case TPM_ALG_SM3_256:
          AuthSize = SM3_256_DIGEST_SIZE;
          break;
      }
    }

    ZeroMem (mNewPlatformAuth.buffer, AuthSize);
    ZeroMem (&LocalAuthSession, sizeof (LocalAuthSession));
    LocalAuthSession.sessionHandle = TPM_RS_PW;
    LocalAuthSession.hmac.size = AuthSize;
    CopyMem (LocalAuthSession.hmac.buffer, mNewPlatformAuth.buffer, AuthSize);

    Status = Tpm2HierarchyChangeAuth (TPM_RH_PLATFORM, NULL, &mNewPlatformAuth);
    // Negative Test (Expected Status: Device Error)
    DEBUG ((DEBUG_INFO, "        Tpm2HierarchyChangeAuth with NULL auth Result: - %r\n", Status));
  }

  if (!EFI_ERROR (Status) || (TpmPresent != TRUE)) {
    DEBUG ((DEBUG_INFO, "        Unexpected Status: Platform Auth Value is Zero\n"));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT_UNEXP_STATUS_CODE_4,
      HSTI_MEASURED_BOOT_CONFIGURATION,
      HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT_UNEXP_STATUS_STRING_4
      );
    Result = FALSE;
  }

  //
  // ALL PASS
  //
  if (Result) {

    Status = HstiLibSetFeaturesVerified (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               0,
               HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT
               );
    CheckStatusForHstiLibSet (Status);
  }

  return;
}
