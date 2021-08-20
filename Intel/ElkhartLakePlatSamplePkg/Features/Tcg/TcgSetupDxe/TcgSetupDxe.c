/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2019 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Protocol/TcgService.h>
#include <SetupVariable.h>
#include <TcgSetup.h>
#include <Library/PcdLib.h>
#include <Tcg2ConfigNvData.h>
#include <Library/BaseMemoryLib.h>
#include <Library/IoLib.h>
#include <Register/PttPtpRegs.h>

#define H2NS(x) ((((x) << 8) | ((x) >> 8)) & 0xffff)
#define H2NL(x) (H2NS ((x) >> 16) | (H2NS ((x) & 0xffff) << 16))

//
// Nv Data structure referenced by IFR
//
typedef struct {
  UINT8   TpmOperation;
  BOOLEAN TpmEnable;
  BOOLEAN TpmActivate;
} TCG_CONFIGURATION;

EFI_STATUS
GetTpmState (
  OUT BOOLEAN                   *TpmEnable, OPTIONAL
  OUT BOOLEAN                   *TpmActivated, OPTIONAL
  OUT BOOLEAN                   *PhysicalPresenceLock, OPTIONAL
  OUT BOOLEAN                   *LifetimeLock, OPTIONAL
  OUT BOOLEAN                   *CmdEnable OPTIONAL
  )
{
  EFI_STATUS                       Status;
  TPM_RSP_COMMAND_HDR              *TpmRsp;
  UINT32                           TpmSendSize;
  TPM_PERMANENT_FLAGS              *TpmPermanentFlags;
  TPM_STCLEAR_FLAGS                *VFlags;
  UINT8                            CmdBuf[64];
  EFI_TCG_PROTOCOL                 *TcgProtocol;

  Status = gBS->LocateProtocol (&gEfiTcgProtocolGuid, NULL, (VOID **) &TcgProtocol);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Get TPM Permanent flags (TpmEnable, TpmActivated, LifetimeLock, CmdEnable)
  //
  if ((TpmEnable != NULL) || (TpmActivated != NULL) || (LifetimeLock != NULL) || (CmdEnable != NULL)) {
    TpmSendSize           = sizeof (TPM_RQU_COMMAND_HDR) + sizeof (UINT32) * 3;
    *(UINT16*)&CmdBuf[0]  = H2NS (TPM_TAG_RQU_COMMAND);
    *(UINT32*)&CmdBuf[2]  = H2NL (TpmSendSize);
    *(UINT32*)&CmdBuf[6]  = H2NL (TPM_ORD_GetCapability);

    *(UINT32*)&CmdBuf[10] = H2NL (TPM_CAP_FLAG);
    *(UINT32*)&CmdBuf[14] = H2NL (sizeof (TPM_CAPABILITY_AREA));
    *(UINT32*)&CmdBuf[18] = H2NL (TPM_CAP_FLAG_PERMANENT);

    Status = TcgProtocol->PassThroughToTpm (
                            TcgProtocol,
                            TpmSendSize,
                            CmdBuf,
                            sizeof (CmdBuf),
                            CmdBuf
                            );
    TpmRsp = (TPM_RSP_COMMAND_HDR*)&CmdBuf[0];
    if (EFI_ERROR (Status) || (TpmRsp->tag != H2NS (TPM_TAG_RSP_COMMAND)) || (TpmRsp->returnCode != 0)) {
      return EFI_DEVICE_ERROR;
    }

    TpmPermanentFlags = (TPM_PERMANENT_FLAGS *)&CmdBuf[sizeof (TPM_RSP_COMMAND_HDR) + sizeof (UINT32)];

    if (TpmEnable != NULL) {
      *TpmEnable = !TpmPermanentFlags->disable;
    }

    if (TpmActivated != NULL) {
      *TpmActivated = !TpmPermanentFlags->deactivated;
    }
    if (LifetimeLock != NULL) {
      *LifetimeLock = TpmPermanentFlags->physicalPresenceLifetimeLock;
    }

    if (CmdEnable != NULL) {
      *CmdEnable = TpmPermanentFlags->physicalPresenceCMDEnable;
    }
  }

  //
  // Get TPM Volatile flags (PhysicalPresenceLock)
  //
  if (PhysicalPresenceLock != NULL) {
    TpmSendSize           = sizeof (TPM_RQU_COMMAND_HDR) + sizeof (UINT32) * 3;
    *(UINT16*)&CmdBuf[0]  = H2NS (TPM_TAG_RQU_COMMAND);
    *(UINT32*)&CmdBuf[2]  = H2NL (TpmSendSize);
    *(UINT32*)&CmdBuf[6]  = H2NL (TPM_ORD_GetCapability);

    *(UINT32*)&CmdBuf[10] = H2NL (TPM_CAP_FLAG);
    *(UINT32*)&CmdBuf[14] = H2NL (sizeof (TPM_CAPABILITY_AREA));
    *(UINT32*)&CmdBuf[18] = H2NL (TPM_CAP_FLAG_VOLATILE);

    Status = TcgProtocol->PassThroughToTpm (
                            TcgProtocol,
                            TpmSendSize,
                            CmdBuf,
                            sizeof (CmdBuf),
                            CmdBuf
                            );
    TpmRsp = (TPM_RSP_COMMAND_HDR*)&CmdBuf[0];
    if (EFI_ERROR (Status) || (TpmRsp->tag != H2NS (TPM_TAG_RSP_COMMAND)) || (TpmRsp->returnCode != 0)) {
      return EFI_DEVICE_ERROR;
    }

    VFlags = (TPM_STCLEAR_FLAGS *)&CmdBuf[sizeof (TPM_RSP_COMMAND_HDR) + sizeof (UINT32)];

    if (PhysicalPresenceLock != NULL) {
      *PhysicalPresenceLock = VFlags->physicalPresenceLock;
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
InitializeTcgSetup (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  TCG_SETUP                TcgSetup;
  EFI_STATUS               Status;
  TCG2_CONFIGURATION       Tcg2Configuration;
  TCG_CONFIGURATION        TcgConfiguration;
  UINTN                    TcgSetpSize;
  UINTN                    Tcg2Size;
  UINTN                    TcgSize;
  BOOLEAN                  TpmEnable;
  BOOLEAN                  TpmState;
  UINT32                   TcgSetupAttr;
  UINT32                   Tcg2Attr;
  UINT32                   TcgAttr;
  UINT32                   TpmStsFtif;

  TcgSize = sizeof(TcgConfiguration);
  Status = gRT->GetVariable(
    L"TCG_CONFIGURATION",
    &gTcgConfigFormSetGuid,
    &TcgAttr,
    &TcgSize,
    &TcgConfiguration
    );
  if (EFI_ERROR(Status)) {
    TcgConfiguration.TpmOperation = 0; // PHYSICAL_PRESENCE_NO_ACTION
  }

  Tcg2Size = sizeof(Tcg2Configuration);
  Status = gRT->GetVariable (
                    TCG2_STORAGE_NAME,
                    &gTcg2ConfigFormSetGuid,
          &Tcg2Attr,
          &Tcg2Size,
                    &Tcg2Configuration
                    );
  if (EFI_ERROR (Status)) {
    Tcg2Configuration.TpmDevice           = TPM_DEVICE_NULL;
  }

  if (CompareGuid(PcdGetPtr(PcdTpmInstanceGuid), &gEfiTpmDeviceInstanceNoneGuid)){
    //
    // No TPM available
    //
    Tcg2Configuration.TpmDevice           = TPM_DEVICE_NULL;
  } else if (CompareGuid(PcdGetPtr(PcdTpmInstanceGuid), &gEfiTpmDeviceInstanceTpm12Guid)) {
    Tcg2Configuration.TpmDevice = TPM_DEVICE_1_2;
  }

  TcgSetpSize = sizeof (TCG_SETUP);
  Status = gRT->GetVariable(
                  TCG_SETUP_NAME,
                  &gSetupVariableGuid,
          &TcgSetupAttr,
          &TcgSetpSize,
                  &TcgSetup
                  );
  if (EFI_ERROR (Status)) {
    //
    // if TcgSetup Variable doesn't exist
    //
    TcgSetup.dTpm12Present   = 0;
    TcgSetup.TpmCurrentState = 0;
    TcgSetup.HideTpm         = 0;
    TcgSetup.MorState        = 0;
    TcgSetup.dTpm20Present   = 0;
    TcgSetup.PttPresent      = 0;
    TcgSetupAttr = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS;
  }

  if (TcgSetup.HideTpm) {
    TcgSetup.TpmCurrentState = 0;
  } else {

    if (CompareGuid(PcdGetPtr(PcdTpmInstanceGuid), &gEfiTpmDeviceInstanceTpm12Guid)) {
      TcgSetup.dTpm12Present = 1;
    }

    if (CompareGuid(PcdGetPtr(PcdTpmInstanceGuid), &gEfiTpmDeviceInstanceTpm20DtpmGuid)) {
      TpmStsFtif = MmioRead32 (R_PTT_TXT_STS_FTIF);

      if ((TpmStsFtif & V_FTIF_FTPM_PRESENT) == ((UINT32) V_FTIF_FTPM_PRESENT)) {
        DEBUG ((DEBUG_INFO, "PTT (fTPM) present\n"));
        TcgSetup.PttPresent = 1;
        Tcg2Configuration.TpmDevice = TPM_DEVICE_PTT;
      } else {
        DEBUG ((DEBUG_INFO, "dTPM present\n"));
        TcgSetup.dTpm20Present = 1;
        Tcg2Configuration.TpmDevice = TPM_DEVICE_2_0_DTPM;
      }
    }

    Status = GetTpmState (&TpmEnable, &TpmState, NULL, NULL, NULL);
    if (!EFI_ERROR (Status)) {
      if (TpmEnable) {
        if (TpmState) {
          TcgSetup.TpmCurrentState = 2;
        } else {
          TcgSetup.TpmCurrentState = 1;
        }
      } else {
        TcgSetup.TpmCurrentState = 0;
      }
    } else {
      TcgSetup.TpmCurrentState = 0;
    }

    if ( TcgConfiguration.TpmOperation == 1 && // PHYSICAL_PRESENCE_ENABLE, default value in VFR
      TpmEnable == FALSE) {
      DEBUG ((DEBUG_INFO, "Sync up TpmOperation value of TPM between EfiVariable and real status," "this should be necessary and only happend at first boot.\n"));
      if (TpmState) { // Active
        TcgConfiguration.TpmOperation = 2;  // PHYSICAL_PRESENCE_DISABLE
      } else {        // Deactive
        TcgConfiguration.TpmOperation = 7;  // PHYSICAL_PRESENCE_DEACTIVATE_DISABLE;
      }
    }

    DEBUG((DEBUG_INFO, "[TcgConfiguration]: TpmOperation:%d\n", (UINTN)TcgConfiguration.TpmOperation));
  }

  DEBUG ((DEBUG_INFO, "[TcgSetup]: HideTpm:%d, dTpm12Present:%d, TpmCurrentState:%d\n", (UINTN) TcgSetup.HideTpm, (UINTN) TcgSetup.dTpm12Present, (UINTN) TcgSetup.TpmCurrentState));
  Status = gRT->SetVariable (
                  TCG_SETUP_NAME,
                  &gSetupVariableGuid,
          TcgSetupAttr,
          TcgSetpSize,
                  &TcgSetup
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Save to variable so platform driver can get it.
  //
  Status = gRT->SetVariable(
                    TCG2_STORAGE_NAME,
                    &gTcg2ConfigFormSetGuid,
          Tcg2Attr,
                    sizeof(Tcg2Configuration),
                    &Tcg2Configuration
                    );
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "TcgConfigDriver: Fail to set TCG2_STORAGE_NAME\n"));
  }

  Status = gRT->SetVariable(
    L"TCG_CONFIGURATION",
    &gTcgConfigFormSetGuid,
    TcgAttr,
    sizeof(TcgConfiguration),
    &TcgConfiguration
    );

  return Status;
}
