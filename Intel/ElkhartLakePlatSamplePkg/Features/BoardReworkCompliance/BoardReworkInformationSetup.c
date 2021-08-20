/** @file

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
#include <Base.h>
#include <Library/AslUpdateLib.h>
#include <Protocol/AcpiSystemDescriptionTable.h>
#include <SetupPrivate.h>

/**
  This function initializes the Board Rework related setup option values

  @param[in] HiiHandle  HiiHandle Handle to HII database
  @param[in] Class      Indicates the setup class

**/

//
// PSS rework tracker string processing
//
EFI_STATUS InitReworkStrings (EFI_HII_HANDLE HiiHandle, UINT16 Class)
{
  UINT8 i,j,PssReworkCount;
  UINT8 MandatoryBitCount = 0;
  UINT8 MandatoryBitPosition[32];
  CHAR16 MandatoryBoardRework[100];
  CHAR16 PssReworkPresent[100];
  CHAR16 PssReworkRequired[100];
  CHAR16 PssNoReworkRequired[18];

  if (Class != ADVANCED_FORM_SET_CLASS) {
    return EFI_SUCCESS;
  }

  //
  //List the Required Board Rework Information from Bios
  //
  InitString (
    HiiHandle, STRING_TOKEN(STR_BIOS_REWORK_VALUE),
    L"%0d",
    PcdGet32 (PcdBoardReworkComplianceBios)
  );
  //
  //Get the list of Required Reworks Present on the board
  //
 InitString (
    HiiHandle, STRING_TOKEN(STR_PSS_REWORK_VALUE),
    L"%0d",
    PcdGet32 (PcdBoardReworkCompliancePssChip)
  );
  //MANDATORY BIT POSITION
  for (i = 0,j = 0; i < 32; i++) {
    if ((PcdGet32 (PcdBoardReworkComplianceBios)) >> i & 1 ) {
      MandatoryBitPosition[j] = i;
      j++;
    }
  }
  //MANDATORY BIT COUNT
  MandatoryBitCount = j;
  // Listing the mandatory reworks required
  if (0 == MandatoryBitCount) {
    //
    //MandatoryBoardRework[]= "None" ;
    //
    MandatoryBoardRework[0] = 'N';
    MandatoryBoardRework[1] = 'o';
    MandatoryBoardRework[2] = 'n';
    MandatoryBoardRework[3] = 'e';
    MandatoryBoardRework[4] = '\0';

    InitString (
      HiiHandle, STRING_TOKEN (STR_BIOS_REWORK_NEEDED_VALUE),
      L"Rework %s", MandatoryBoardRework
    );
  } else {
    for (i = 0,j = 0; i < 32; i++) {
      if ( (PcdGet32 (PcdBoardReworkComplianceBios)) >> i & 1) {
        if (i < 9) {
          MandatoryBoardRework[j++] = '0';
        }
        if (i >= 9 && i < 19) {
          MandatoryBoardRework[j++] = '1';
        }
        if (i >= 19 && i < 29) {
          MandatoryBoardRework[j++] = '2';
        }
        if (i >= 29 && i < 32) {
          MandatoryBoardRework[j++] = '3';
        }
        MandatoryBoardRework[j] = ((i + 1) % 10) + '0';
        j++;
        MandatoryBoardRework[j] = ' ';
        j++;
      } //end of if
    }//end of for
    MandatoryBoardRework[j] = '\0';
    InitString (
      HiiHandle, STRING_TOKEN (STR_BIOS_REWORK_NEEDED_VALUE),
      L"Rework %s", MandatoryBoardRework
    );
  } //end of else for MandatoryBitCount

  //
  //Reworks present on the board
  //
  for (i = 0, j = 0, PssReworkCount = 0; i < MandatoryBitCount; i++) {
    if ((PcdGet32 (PcdBoardReworkCompliancePssChip) >> (MandatoryBitPosition[i])) & 1) { //Data obtained from pss chip has the same value as the data retreived from bios table
      PssReworkCount++;
      if (MandatoryBitPosition[i] < 9) {
        PssReworkPresent[j++] = '0';
      }
      if (MandatoryBitPosition[i] >= 9 && MandatoryBitPosition[i] < 19) {
        PssReworkPresent[j++] = '1';
      }
      if (MandatoryBitPosition [i] >= 19 && MandatoryBitPosition[i] < 29) {
      PssReworkPresent[j++] = '2';
      }
      if (MandatoryBitPosition[i] >= 29 && MandatoryBitPosition[i] < 32) {
        PssReworkPresent[j++] = '3';
      }
      PssReworkPresent[j] = ((MandatoryBitPosition[i] + 1) % 10) + '0';
      j++;
      PssReworkPresent[j] = ' ';
      j++;
    } // end of if
  } //end of for
  PssReworkPresent[j] = '\0';
  InitString (
     HiiHandle, STRING_TOKEN (STR_BIOS_REWORK_PRESENT_VALUE),
     L"Rework %s", PssReworkPresent
  );
  DEBUG ((DEBUG_INFO, " MandatoryBitCount = %x\n",MandatoryBitCount));
  DEBUG ((DEBUG_INFO, " PssReworkCount = %x\n",PssReworkCount));
  //
  //Reworks missing on the baord
  //
  if(PssReworkCount == MandatoryBitCount) {
    //
    //PssReworkRequired[]= "No rework Required" ;
    //
    PssNoReworkRequired[0] = 'N';
    PssNoReworkRequired[1] = 'o';
    PssNoReworkRequired[2] = ' ';
    PssNoReworkRequired[3] = 'R';
    PssNoReworkRequired[4] = 'e';
    PssNoReworkRequired[5] = 'w';
    PssNoReworkRequired[6] = 'o';
    PssNoReworkRequired[7] = 'r';
    PssNoReworkRequired[8] = 'k';
    PssNoReworkRequired[9] = ' ';
    PssNoReworkRequired[10] = 'N';
    PssNoReworkRequired[11] = 'e';
    PssNoReworkRequired[12] = 'e';
    PssNoReworkRequired[13] = 'd';
    PssNoReworkRequired[14] = 'e';
    PssNoReworkRequired[15] = 'd';
    PssNoReworkRequired[16] = '\0';
    InitString(
      HiiHandle, STRING_TOKEN (STR_BIOS_REWORK_REQUIRED_VALUE),
      L"%s", PssNoReworkRequired
    );
  } else { //end of if for PssReworkCount
    for (i = 0, j = 0; i < MandatoryBitCount; i++) {
      if (((PcdGet32 (PcdBoardReworkCompliancePssChip) >> (MandatoryBitPosition[i]) ) & 1 ) !=1) { //Data obtained from pss chip has the same value same as data retreived from bios table
        if (MandatoryBitPosition[i] < 9) {
          PssReworkRequired[j++] = '0';
        }
        if(MandatoryBitPosition[i] >= 9 && MandatoryBitPosition[i] < 19) {
          PssReworkRequired[j++] = '1';
        }
        if(MandatoryBitPosition[i] >= 19 && MandatoryBitPosition[i] < 29) {
          PssReworkRequired[j++] = '2';
        }
        if(MandatoryBitPosition[i] >= 29 && MandatoryBitPosition[i] < 32) {
          PssReworkRequired[j++]='3';
        }
        PssReworkRequired[j] = ((MandatoryBitPosition[i] + 1) % 10) + '0';
        j++;
        PssReworkRequired[j] = ' ';
        j++;
      } //end of if
    } //end of for
    PssReworkRequired[j] = '\0';
    DEBUG ((DEBUG_INFO, " PssReworkRequired = %s\n", PssReworkRequired));
    InitString(
      HiiHandle,STRING_TOKEN(STR_BIOS_REWORK_REQUIRED_VALUE),
      L"Rework %s", PssReworkRequired
    );
  } //end of else for PssReworkCount
  return EFI_SUCCESS;
}