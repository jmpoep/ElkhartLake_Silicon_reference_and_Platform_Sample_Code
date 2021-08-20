/** @file
This driver supports the board rework complaicne module.

@copyright
INTEL CONFIDENTIAL
Copyright 2017 - 2018 Intel Corporation.

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

#include "BoardReworkCompliance.h"
#include "Library/SerialIoAccessLib.h"
#include <Library/UefiRuntimeServicesTableLib.h>
#include <SetupVariable.h>
#include <Library/PssLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/HobLib.h>

extern EFI_GUID gSetupVariableGuid;

#define  PSS_CHIP_INTEL_REQUIRED_REWORK_OFFSET      0x150

/**
Entry point of the Board Rework Compliance driver.

ImageHandle   EFI_HANDLE: A handle for the image that is initializing this driver
SystemTable   EFI_SYSTEM_TABLE: A pointer to the EFI system table

@retval  EFI_SUCCESS:           Driver initialized successfully
EFI_LOAD_ERROR:                 Failed to Initialize or has been loaded
EFI_OUT_OF_RESOURCES:           Could not allocate needed resources
**/

EFI_STATUS
EFIAPI
BiosReworkComplianceEntryPoint (
IN EFI_HANDLE           ImageHandle,
IN EFI_SYSTEM_TABLE     *SystemTable
)
{
  EFI_STATUS      Status = EFI_SUCCESS;
  UINT32          Value32;
  UINT8           ReBuf[4] ={0};
  UINT32          Reg1 =PSS_BASE_ADDR_CLASSID;
  UINTN           VariableSize;
  SETUP_DATA      mSetupData;
  EFI_BOOT_MODE   BootMode;
  VariableSize = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (
                 L"Setup",
                 &gSetupVariableGuid,
                 NULL,
                 &VariableSize,
                 &mSetupData
                 );
  //
  // Update the rework matrix PCD based on the PSS chip data on RVP
  //
  Status = PssDetect (); // Check for PSS Detection
  if (! EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "PSS Chip Detected\n"));
    Reg1 = PSS_CHIP_INTEL_REQUIRED_REWORK_OFFSET;
    Status = ReadPssData (ReBuf, Reg1, 4);
    //=============value32===================
    //31       |23        |15         |7        0
    //      reg3       reg2        reg1      reg0
    Value32 = ((UINT32)ReBuf[3] << 24) | ((UINT32)ReBuf[2] << 16) | ((UINT32)ReBuf[1] << 8) | ((UINT32)ReBuf[0]);
    //================value32===================
    //31       |23        |15         |7        0
    //      reg3       reg2        reg1      reg0
    PcdSet32S (PcdBoardReworkCompliancePssChip, Value32);
    } else { //End of PSS check
      DEBUG ((DEBUG_INFO, "Pss Chip not Detected\n"));
    } //end of else for PSS Check

  //
  // Get current Boot Mode
  //
  BootMode = GetBootModeHob ();

  //
  // Verify board rework compliance only if:
  // 1. Feature is enabled in the setup menu and
  // 2. It is the first system boot ( COLD BOOT).
  //
  if (EFI_ERROR (Status) || (mSetupData.BoardReworkComplainceEnable == 0) || ((BootMode != BOOT_WITH_DEFAULT_SETTINGS) && (BootMode != BOOT_WITH_FULL_CONFIGURATION))) {
    return EFI_SUCCESS;
  } else {
    BiosReworkComplianceCheck ();
    return EFI_SUCCESS;
  } // end of else for setupdata.BoardReworkComplainceEnable
}

/**
  BiosReworkComplianceCheck fucntion validates if all the required reworks
  are present on the board, if not user is alerted with a popup message.
**/
VOID
BiosReworkComplianceCheck (
  VOID
  )
{
  UINT8   BitCount;
  UINT8   ReworkStart;
  UINT8   ReworkEnd;

  ReworkStart = 0;
  ReworkEnd = 32;
  for (BitCount = ReworkStart; BitCount < ReworkEnd; BitCount++) {
    if (((PcdGet32 (PcdBoardReworkComplianceBios)) >> BitCount)  & 1) { //Verify if the rework number is valid for the respective board
      if (((PcdGet32 (PcdBoardReworkCompliancePssChip)) >> BitCount)  & 1) { // Verify is the rework is present on the respective board
        continue;
      } else { // Means some required rework is missing
        gST->ConOut->ClearScreen(gST->ConOut);
        CreatePopUp (EFI_LIGHTGRAY | EFI_BACKGROUND_RED, NULL, L"Few of the Mandatory Reworks are Missing. Refer to Bios Setup for further Details!",
                                                               L"",
                                                               L"Intel Advacned Menu->Rework Configuration", NULL, NULL);
        gBS->Stall (5000000);  //Five second delay for the popup message
        break;
      }
    }
  }
  gST->ConOut->ClearScreen(gST->ConOut);
}
