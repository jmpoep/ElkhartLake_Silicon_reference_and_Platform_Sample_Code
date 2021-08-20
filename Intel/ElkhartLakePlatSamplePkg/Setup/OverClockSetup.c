/** @file
  This file implements a Setup callback funtion to update the
  Expected CPU frequency with respect to BusRatio and BusSpeed.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2018 Intel Corporation.

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

#include <OverClockSetup.h>
#include <Protocol/SmbusHc.h>
#include <Library/HiiLib.h>
#include <Library/BaseLib.h>
#include <Library/CpuPlatformLib.h>

#define MAX_EFFICIENCY_RATIO_MASK           0xff
#define MAX_EFFICIENCY_RATIO_OFFSET         40
#define MAX_NON_TURBO_RATIO_OFFSET          8
#define MAX_NON_TURBO_RATIO_MASK            0xff


GLOBAL_REMOVE_IF_UNREFERENCED CHAR16 Timing5cString[] = L"  % 5d   % 5d   % 5d   % 5d";
GLOBAL_REMOVE_IF_UNREFERENCED CHAR16 Timing7cString[] = L"% 7d % 7d % 7d % 7d";

                                                                   // Ratio | Ratio
GLOBAL_REMOVE_IF_UNREFERENCED const TRangeTable FreqTable[] = {    // 133   | 100
  { 0xFFFFFFFF,            fInvalid, MRC_FREQ_INVALID           }, //----------------
  { MRC_DDR_800_TCK_MIN,  f800,     MRC_FREQ_133 | MRC_FREQ_100 }, //   6   |   8
  { MRC_DDR_1000_TCK_MIN, f1000,                   MRC_FREQ_100 }, //       |  10
  { MRC_DDR_1067_TCK_MIN, f1067,    MRC_FREQ_133                }, //   8   |
  { MRC_DDR_1100_TCK_MIN, f1100,                   MRC_FREQ_100 }, //       |  11
  { MRC_DDR_1200_TCK_MIN, f1200,    MRC_FREQ_133 | MRC_FREQ_100 }, //   9   |  12
  { MRC_DDR_1300_TCK_MIN, f1300,                   MRC_FREQ_100 }, //       |  13
  { MRC_DDR_1333_TCK_MIN, f1333,    MRC_FREQ_133                }, //  10   |
  { MRC_DDR_1400_TCK_MIN, f1400,                   MRC_FREQ_100 }, //       |  14
  { MRC_DDR_1467_TCK_MIN, f1467,    MRC_FREQ_133                }, //  11   |
  { MRC_DDR_1500_TCK_MIN, f1500,                   MRC_FREQ_100 }, //       |  15
  { MRC_DDR_1600_TCK_MIN, f1600,    MRC_FREQ_133 | MRC_FREQ_100 }, //  12   |  16
  { MRC_DDR_1700_TCK_MIN, f1700,                   MRC_FREQ_100 }, //       |  17
  { MRC_DDR_1733_TCK_MIN, f1733,    MRC_FREQ_133                }, //  13   |
  { MRC_DDR_1800_TCK_MIN, f1800,                   MRC_FREQ_100 }, //       |  18
  { MRC_DDR_1867_TCK_MIN, f1867,    MRC_FREQ_133                }, //  14   |
  { MRC_DDR_1900_TCK_MIN, f1900,                   MRC_FREQ_100 }, //       |  19
  { MRC_DDR_2000_TCK_MIN, f2000,    MRC_FREQ_133 | MRC_FREQ_100 }, //  15   |  20
  { MRC_DDR_2100_TCK_MIN, f2100,                   MRC_FREQ_100 }, //       |  21
  { MRC_DDR_2133_TCK_MIN, f2133,    MRC_FREQ_133                }, //  16   |
  { MRC_DDR_2200_TCK_MIN, f2200,                   MRC_FREQ_100 }, //       |  22
  { MRC_DDR_2267_TCK_MIN, f2267,    MRC_FREQ_133                }, //  17   |
  { MRC_DDR_2300_TCK_MIN, f2300,                   MRC_FREQ_100 }, //       |  23
  { MRC_DDR_2400_TCK_MIN, f2400,    MRC_FREQ_133 | MRC_FREQ_100 }, //  18   |  24
  { MRC_DDR_2500_TCK_MIN, f2500,                   MRC_FREQ_100 }, //       |  25
  { MRC_DDR_2533_TCK_MIN, f2533,    MRC_FREQ_133                }, //  19   |
  { MRC_DDR_2600_TCK_MIN, f2600,                   MRC_FREQ_100 }, //       |  26
  { MRC_DDR_2667_TCK_MIN, f2667,    MRC_FREQ_133                }, //  20   |
  { MRC_DDR_2700_TCK_MIN, f2700,                   MRC_FREQ_100 }, //       |  27
  { MRC_DDR_2800_TCK_MIN, f2800,    MRC_FREQ_133 | MRC_FREQ_100 }, //  21   |  28
  { MRC_DDR_2900_TCK_MIN, f2900,                   MRC_FREQ_100 }, //       |  29
  { MRC_DDR_2933_TCK_MIN, f2933,    MRC_FREQ_133                }, //  22   |
  { MRC_DDR_3000_TCK_MIN, f3000,                   MRC_FREQ_100 }, //       |  30
  { MRC_DDR_3067_TCK_MIN, f3067,    MRC_FREQ_133                }, //  23   |
  { MRC_DDR_3100_TCK_MIN, f3100,                   MRC_FREQ_100 }, //       |  31
  { MRC_DDR_3200_TCK_MIN, f3200,    MRC_FREQ_133 | MRC_FREQ_100 }, //  24   |  32
  { MRC_DDR_3333_TCK_MIN, f3333,    MRC_FREQ_133                }, //  25   |
  { MRC_DDR_3467_TCK_MIN, f3467,    MRC_FREQ_133                }, //  26   |
  { MRC_DDR_3600_TCK_MIN, f3600,    MRC_FREQ_133 | MRC_FREQ_100 }, //  27   |  36
  { MRC_DDR_3733_TCK_MIN, f3733,    MRC_FREQ_133                }, //  28   |
  { MRC_DDR_3867_TCK_MIN, f3867,    MRC_FREQ_133                }, //  29   |
  { MRC_DDR_4000_TCK_MIN, f4000,    MRC_FREQ_133 | MRC_FREQ_100 }, //  30   |  40
  { MRC_DDR_4133_TCK_MIN, f4133,    MRC_FREQ_133                }, //  31   |
  { MRC_DDR_4267_TCK_MIN, f4267,    MRC_FREQ_133                }, //  32   |
  { 0,                    fNoInit,  MRC_FREQ_INVALID            }
};

#if FixedPcdGetBool(PcdOverclockEnable) == 1
/**
  This funciton converts the tCK value in femtoseconds to MHz.

  @param[in]      tCKvalue       - The tCK value to be converted to MHz.

  @retval tCkvalue in MHz
**/
UINT32
ConvertFs2Mhz (
  UINT32        tCKvalue
  )
{
  UINT32    tCKMhz;

  tCKMhz = (tCKvalue == 0) ? 0 : (2000000000 + (tCKvalue >> 1)) / tCKvalue;

  return tCKMhz;
}
#endif

/**
  Installs OverClock Callback function.

  @param[in]  HiiHandle      Handle to HII database
  @param[in]  Class          Indicates the setup class
**/
VOID
InitOverClockStrings (
  EFI_HII_HANDLE        HiiHandle,
  UINT16                Class
  )
{
#if FixedPcdGetBool(PcdOverclockEnable) == 1
  EFI_STATUS            Status;
  UINT32                MailboxStatus;
  SA_SETUP              SaSetup;
  SETUP_DATA            SetupData;
  MEM_INFO_PROTOCOL     *MemInfoHobProtocol;
  UINTN                 VariableSize;
  MEMORY_INFO_DATA      *MemInfoData;
  MEMORY_TIMING         *MemoryTiming;
  UINT32                VariableAttr;
  UINT32                PcodeBclkFrequency;
  CPU_SKU               CpuSku;
  UINT32                tCKvalues[MEMORY_PROFILE_MAX];
  UINT8                 Index;

  if (Class != ADVANCED_FORM_SET_CLASS) {
    return;
  }

  DEBUG ((DEBUG_INFO, "<InitOverClockStrings>"));

  //
  // Get the pcode derived BCLK frequency in kHz. Message is only valid on DT/Halo skus.
  //
  CpuSku = GetCpuSku ();
  if ((CpuSku == EnumCpuHalo) || (CpuSku == EnumCpuTrad)) {

    MailboxRead (MAILBOX_TYPE_OC, MAILBOX_BCLK_FREQUENCY_CMD, &PcodeBclkFrequency, &MailboxStatus);
    DEBUG ((DEBUG_INFO, "(OC) Pcode BCLK frequency = %X", PcodeBclkFrequency));

    //
    // Initialize BCLK Frequency String in MHz
    //
    InitString (HiiHandle, STRING_TOKEN (STR_PCODE_BCLK_FREQUENCY_VALUE), L"%d.%02d MHz",
      PcodeBclkFrequency / 1000, PcodeBclkFrequency % 1000);
  }

  //
  // Get the Memory Info HOB Protocol if it exists.
  //
  Status = gBS->LocateProtocol (&gMemInfoProtocolGuid, NULL, (VOID **) &MemInfoHobProtocol);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  MemInfoData  = &MemInfoHobProtocol->MemInfoData;
  MemoryTiming = MemInfoData->Timing;

  for (Index = 0; Index < MEMORY_PROFILE_MAX; Index++) {
    tCKvalues[Index] = ConvertFs2Mhz (MemoryTiming[Index].tCK);
  }

  InitString (
    HiiHandle,
    STRING_TOKEN (STR_MEMORY_TIMING_TCK_VALUE),
    Timing7cString,
    tCKvalues[DEFAULT_SPD_PROFILE],
    tCKvalues[CUSTOM_PROFILE],
    tCKvalues[XMP_PROFILE_1],
    tCKvalues[XMP_PROFILE_2]
    );

  InitString (
    HiiHandle,
    STRING_TOKEN (STR_MEMORY_TIMING_TCL_VALUE),
    Timing5cString,
    MemoryTiming[DEFAULT_SPD_PROFILE].tCL,
    MemoryTiming[CUSTOM_PROFILE].tCL,
    MemoryTiming[XMP_PROFILE_1].tCL,
    MemoryTiming[XMP_PROFILE_2].tCL
    );

  InitString (
    HiiHandle,
    STRING_TOKEN (STR_MEMORY_TIMING_TRCD_TRP_VALUE),
    Timing5cString,
    MemoryTiming[DEFAULT_SPD_PROFILE].tRCDtRP,
    MemoryTiming[CUSTOM_PROFILE].tRCDtRP,
    MemoryTiming[XMP_PROFILE_1].tRCDtRP,
    MemoryTiming[XMP_PROFILE_2].tRCDtRP
    );

  InitString (
    HiiHandle,
    STRING_TOKEN (STR_MEMORY_TIMING_TRAS_VALUE),
    Timing5cString,
    MemoryTiming[DEFAULT_SPD_PROFILE].tRAS,
    MemoryTiming[CUSTOM_PROFILE].tRAS,
    MemoryTiming[XMP_PROFILE_1].tRAS,
    MemoryTiming[XMP_PROFILE_2].tRAS
    );

  InitString (
    HiiHandle,
    STRING_TOKEN (STR_MEMORY_TIMING_TCWL_VALUE),
    Timing5cString,
    MemoryTiming[DEFAULT_SPD_PROFILE].tCWL,
    MemoryTiming[CUSTOM_PROFILE].tCWL,
    MemoryTiming[XMP_PROFILE_1].tCWL,
    MemoryTiming[XMP_PROFILE_2].tCWL
    );

  InitString (
    HiiHandle,
    STRING_TOKEN (STR_MEMORY_TIMING_TFAW_VALUE),
    Timing5cString,
    MemoryTiming[DEFAULT_SPD_PROFILE].tFAW,
    MemoryTiming[CUSTOM_PROFILE].tFAW,
    MemoryTiming[XMP_PROFILE_1].tFAW,
    MemoryTiming[XMP_PROFILE_2].tFAW
    );

  InitString (
    HiiHandle,
    STRING_TOKEN (STR_MEMORY_TIMING_TREFI_VALUE),
    Timing5cString,
    MemoryTiming[DEFAULT_SPD_PROFILE].tREFI,
    MemoryTiming[CUSTOM_PROFILE].tREFI,
    MemoryTiming[XMP_PROFILE_1].tREFI,
    MemoryTiming[XMP_PROFILE_2].tREFI
    );

  InitString (
    HiiHandle,
    STRING_TOKEN (STR_MEMORY_TIMING_TRFC_VALUE),
    Timing5cString,
    MemoryTiming[DEFAULT_SPD_PROFILE].tRFC,
    MemoryTiming[CUSTOM_PROFILE].tRFC,
    MemoryTiming[XMP_PROFILE_1].tRFC,
    MemoryTiming[XMP_PROFILE_2].tRFC
    );

  InitString (
    HiiHandle,
    STRING_TOKEN (STR_MEMORY_TIMING_TRRD_VALUE),
    Timing5cString,
    MemoryTiming[DEFAULT_SPD_PROFILE].tRRD,
    MemoryTiming[CUSTOM_PROFILE].tRRD,
    MemoryTiming[XMP_PROFILE_1].tRRD,
    MemoryTiming[XMP_PROFILE_2].tRRD
    );

  InitString (
    HiiHandle,
    STRING_TOKEN (STR_MEMORY_TIMING_TRTP_VALUE),
    Timing5cString,
    MemoryTiming[DEFAULT_SPD_PROFILE].tRTP,
    MemoryTiming[CUSTOM_PROFILE].tRTP,
    MemoryTiming[XMP_PROFILE_1].tRTP,
    MemoryTiming[XMP_PROFILE_2].tRTP
    );

  InitString (
    HiiHandle,
    STRING_TOKEN (STR_MEMORY_TIMING_TWR_VALUE),
    Timing5cString,
    MemoryTiming[DEFAULT_SPD_PROFILE].tWR,
    MemoryTiming[CUSTOM_PROFILE].tWR,
    MemoryTiming[XMP_PROFILE_1].tWR,
    MemoryTiming[XMP_PROFILE_2].tWR
    );

  InitString (
    HiiHandle,
    STRING_TOKEN (STR_MEMORY_TIMING_TWTR_VALUE),
    Timing5cString,
    MemoryTiming[DEFAULT_SPD_PROFILE].tWTR,
    MemoryTiming[CUSTOM_PROFILE].tWTR,
    MemoryTiming[XMP_PROFILE_1].tWTR,
    MemoryTiming[XMP_PROFILE_2].tWTR
    );

  InitString (
    HiiHandle,
    STRING_TOKEN (STR_MEMORY_TIMING_NMODE_VALUE),
    Timing5cString,
    MemoryTiming[DEFAULT_SPD_PROFILE].NMode,
    MemoryTiming[CUSTOM_PROFILE].NMode,
    MemoryTiming[XMP_PROFILE_1].NMode,
    MemoryTiming[XMP_PROFILE_2].NMode
    );

  InitString (
    HiiHandle,
    STRING_TOKEN (STR_MEMORY_VOLTAGE_VDD_VALUE),
    Timing5cString,
    MemInfoData->VddVoltage[DEFAULT_SPD_PROFILE],
    MemInfoData->VddVoltage[CUSTOM_PROFILE],
    MemInfoData->VddVoltage[XMP_PROFILE_1],
    MemInfoData->VddVoltage[XMP_PROFILE_2]
    );

  VariableSize = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  &VariableAttr,
                  &VariableSize,
                  &SetupData
                  );
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (SA_SETUP);
  Status = gRT->GetVariable (
                  L"SaSetup",
                  &gSaSetupVariableGuid,
                  &VariableAttr,
                  &VariableSize,
                  &SaSetup
                  );
  ASSERT_EFI_ERROR (Status);
  //
  // Store the Factory configured values if IsOcDefaultsInitalized == 0.
  // IsOcDefaultsInitalized will be 0 :
  //    1. During first boot
  //    2. If User goes into BIOS setup and selects: Restore Defaults
  //
  if (SetupData.IsOcDefaultsInitalized == 0) {
    //
    // Loading the default values from the MemInfoHobProtocol, using the currently running profile
    //
    MemoryTiming         = &MemInfoData->Timing[MemInfoData->Profile];
    if (!EFI_ERROR (Status)) {
      SaSetup.tCL          = (UINT8) MemoryTiming->tCL;
      SaSetup.tCWL         = (UINT8) MemoryTiming->tCWL;
      SaSetup.tFAW         = MemoryTiming->tFAW;
      SaSetup.tRAS         = MemoryTiming->tRAS;
      SaSetup.tRCDtRP      = (UINT8) MemoryTiming->tRCDtRP;
      SaSetup.tREFI        = MemoryTiming->tREFI;
      SaSetup.tRFC         = MemoryTiming->tRFC;
      SaSetup.tRRD         = (UINT8) MemoryTiming->tRRD;
      SaSetup.tRTP         = (UINT8) MemoryTiming->tRTP;
      SaSetup.tWR          = (UINT8) MemoryTiming->tWR;
      SaSetup.tWTR         = (UINT8) MemoryTiming->tWTR;
      SaSetup.NModeSupport = (UINT8) MemoryTiming->NMode;
      SaSetup.DdrRatio     = MemInfoData->Ratio;
      SaSetup.DdrRefClk    = MemInfoData->RefClk;

      SaSetup.MemoryVoltage = MemInfoData->VddVoltage[MemInfoData->Profile];

      SaSetup.tCLDefault      = SaSetup.tCL;
      SaSetup.tCWLDefault     = SaSetup.tCWL;
      SaSetup.tFAWDefault     = SaSetup.tFAW;
      SaSetup.tRASDefault     = SaSetup.tRAS;
      SaSetup.tRCDtRPDefault  = SaSetup.tRCDtRP;
      SaSetup.tREFIDefault    = SaSetup.tREFI;
      SaSetup.tRFCDefault     = SaSetup.tRFC;
      SaSetup.tRRDDefault     = SaSetup.tRRD;
      SaSetup.tRTPDefault     = SaSetup.tRTP;
      SaSetup.tWRDefault      = SaSetup.tWR;
      SaSetup.tWTRDefault     = SaSetup.tWTR;
      SaSetup.NModeDefault    = SaSetup.NModeSupport;

      Status = gRT->SetVariable (
                      L"SaSetup",
                      &gSaSetupVariableGuid,
                      VariableAttr,
                      sizeof (SA_SETUP),
                      &SaSetup
                      );
      ASSERT_EFI_ERROR (Status);
    }
  }
#endif
}

/**
  This funciton uses the tCK value to choose a reference clock to a clock ratio.

  @param[in]      tCKvalue       - The tCK value to be converted to frequency ratio.
  @param[in]      BclkFrequency  - The current Bclk Frequency.
  @param[in,out]  RefClk         - Used as return value for chosen Reference Clock.
  @param[in,out]  Ratio          - Used as return value for chosen Ratio.
  @param[in,out]  OddRatioMode   - Used as return value for Odd Ratio Mode if applicable

  @retval Nothing
**/
VOID
ConvertClock2FreqRatio (
  IN     UINT32               tCKvalue,
  IN     UINT32               BclkFrequency,
  IN OUT MrcFreqFlag          *RefClk,
  IN OUT MrcClockRatio        *Ratio,
  IN OUT UINT8                *OddRatioMode
  )
{
  MrcFrequency  Frequency;
  UINT32        Index;
  UINT8         FreqFlag;
  UINT64        RatioValue;
  UINT64        FreqValue;
  UINT32        RefClkValue;
  UINT32        BClkValue;

  // Set RefClk and Ratio to 0 (Auto) and OddRatioMode to 0 (Disabled)
  *RefClk       = 0;
  *Ratio        = 0;
  *OddRatioMode = 0;

  // Convert tCK value to the nearest frequency value.
  // Then find slowest valid frequency for the given reference clock.
  Frequency = fNoInit;
  for (Index = 0; Index < ARRAY_COUNT (FreqTable) - 1; Index++) {
    if ((tCKvalue <= FreqTable[Index].tCK) && (tCKvalue > FreqTable[Index + 1].tCK)) {
      Frequency = FreqTable[Index].Frequency;
      break;
    }
  }
  FreqFlag = FreqTable[Index].FreqFlag;

  // If the Frequency is not found in the table, return without changing RefClk, Ratio and OddRatioMode values.
  if (FreqFlag == MRC_FREQ_INVALID) {
    return;
  }

  for (Index = 0; Index < MRC_REF_CLOCK_MAXIMUM; Index++) {
    if ((FreqFlag & (MRC_BIT0 << Index)) != 0) {
      *RefClk = (Index == MRC_REF_CLOCK_133) ? MRC_FREQ_133 : MRC_FREQ_100;
      *OddRatioMode = 0;
      break; // We can have this frequency at the given refclk
    }
    if ((FreqFlag & (MRC_BIT2 << Index)) != 0) {
      *RefClk = (Index == MRC_REF_CLOCK_133) ? MRC_FREQ_133 : MRC_FREQ_100;
      *OddRatioMode = 1;
      break; // We can have this frequency at the given refclk using Odd Ratio mode
    }
  }

  if (BclkFrequency < BCLK_DEFAULT) {
    BclkFrequency = BCLK_DEFAULT;
  }
  BClkValue = BclkFrequency / 100000;
  RefClkValue = (*RefClk == MRC_FREQ_100) ? 200000 : 266667;
  FreqValue   = MultU64x32 (Frequency, 1000000000ULL);
  RatioValue  = DivU64x64Remainder (FreqValue, (RefClkValue * BClkValue), NULL);
  RatioValue  = ((UINT32) RatioValue + 500) / 1000;

  if ((MEMORY_RATIO_MIN <= RatioValue) && (MEMORY_RATIO_MAX >= RatioValue)) {
    *Ratio = (MrcClockRatio) RatioValue;
  }
  return;
}

/**
  This function displays the range checked value for OC TjMax Offset.

  @param This            Points to the EFI_HII_CONFIG_ACCESS_PROTOCOL.
  @param Action          Specifies the type of action taken by the browser.
  @param QuestionId      A unique value which is sent to the original exporting driver
                         so that it can identify the type of data to expect.
  @param Type            The type of value for the question.
  @param Value           A pointer to the data being sent to the original exporting driver.
  @param ActionRequest   On return, points to the action requested by the callback function.

  @retval EFI_SUCCESS       The function completed successfully.
**/
EFI_STATUS
EFIAPI
OcFormCallBackFunction (
  IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
  IN EFI_BROWSER_ACTION                   Action,
  IN EFI_QUESTION_ID                      KeyValue,
  IN UINT8                                Type,
  IN EFI_IFR_TYPE_VALUE                   *Value,
  OUT EFI_BROWSER_ACTION_REQUEST          *ActionRequest
  )
{
  CPU_SETUP               *CpuSetup;
  UINT8                   LfmRatio;
  UINT8                   HfmRatio;
  MSR_REGISTER            MsrPlatformInfo;
  UINTN                   VarSize;
  UINTN                   VariableSize;
  EFI_STATUS              Status;
  EFI_STRING              RequestString;

  if (Action != EFI_BROWSER_ACTION_CHANGING && Action != EFI_BROWSER_ACTION_CHANGED) {
    return EFI_UNSUPPORTED;
  }

  Status = EFI_SUCCESS;
  RequestString = NULL;
  VarSize = sizeof (CPU_SETUP);
  CpuSetup = AllocatePool (VarSize);
  ASSERT (CpuSetup != NULL);
  if (CpuSetup == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  // GetBrowserData by VarStore Name (Setup)
  if (!HiiGetBrowserData (&gCpuSetupVariableGuid, L"CpuSetup", VarSize, (UINT8 *) CpuSetup)) {
    Status = EFI_NOT_FOUND;
  }
  ASSERT_EFI_ERROR (Status);

  MsrPlatformInfo.Qword    = AsmReadMsr64 (MSR_PLATFORM_INFO);
  LfmRatio                 = (UINT8) (RShiftU64 (MsrPlatformInfo.Qword, MAX_EFFICIENCY_RATIO_OFFSET)) & MAX_EFFICIENCY_RATIO_MASK;
  HfmRatio                 = (UINT8) (RShiftU64 (MsrPlatformInfo.Qword, MAX_NON_TURBO_RATIO_OFFSET)) & MAX_NON_TURBO_RATIO_MASK;

  VariableSize = sizeof (CPU_SETUP);
  Status = gRT->GetVariable (
                  L"CpuSetup",
                  &gCpuSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &mCpuSetup
                  );
  ASSERT_EFI_ERROR (Status);

  switch (KeyValue) {
    case  KEY_TjMaxOffset:
      if ((CpuSetup->TjMaxOffset < 10) || (CpuSetup->TjMaxOffset > 63)) {
        CpuSetup->TjMaxOffset = 0;
      }
      RequestString = HiiConstructRequestString(RequestString, OFFSET_OF(CPU_SETUP, TjMaxOffset), sizeof (CpuSetup->TjMaxOffset));
      break;

    case KEY_CORE_MAX_OC_RATIO_LIMIT:
      //
      // Ensure that max oc ratio limit does not go below the LFM ratio
      //
      if ((CpuSetup->CoreMaxOcRatio < LfmRatio) && (CpuSetup->CoreMaxOcRatio != 0)) {
        CpuSetup->CoreMaxOcRatio = LfmRatio;
      }
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (CPU_SETUP, CoreMaxOcRatio), sizeof (CpuSetup->CoreMaxOcRatio));
      break;

    case KEY_RING_MIN_RATIO_LIMIT:
      //
      // Ensure that min ring ratio limit does not go below the LFM ratio
      //
      if ((CpuSetup->MinRingRatioLimit < LfmRatio) && (CpuSetup->MinRingRatioLimit != 0)) {
        CpuSetup->MinRingRatioLimit = LfmRatio;
      }
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (CPU_SETUP, MinRingRatioLimit), sizeof (CpuSetup->MinRingRatioLimit));
      break;

    case KEY_RING_MAX_RATIO_LIMIT:
      //
      // Ensure that max ring ratio limit does not go below the LFM ratio
      //
      if ((CpuSetup->MaxRingRatioLimit < LfmRatio) && (CpuSetup->MaxRingRatioLimit != 0)) {
        CpuSetup->MaxRingRatioLimit = LfmRatio;
      }
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (CPU_SETUP, MaxRingRatioLimit), sizeof (CpuSetup->MaxRingRatioLimit));
      break;

    case KEY_RING_MAX_OC_RATIO_LIMIT:
      //
      // Ensure that max ring OC ratio limit does not go below the HFM ratio. Max ring OC ratio only applies to the OC range.
      //
      if ((CpuSetup->RingMaxOcRatio < HfmRatio) && (CpuSetup->RingMaxOcRatio != 0)) {
        CpuSetup->RingMaxOcRatio = HfmRatio;
      }
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (CPU_SETUP, RingMaxOcRatio), sizeof (CpuSetup->RingMaxOcRatio));
      break;

    default:
      ASSERT(FALSE);
  }

  if (RequestString != NULL) {
    VarSize = sizeof (CPU_SETUP);
    if (!HiiSetBrowserData (&gCpuSetupVariableGuid, L"CpuSetup", VarSize, (UINT8 *)CpuSetup, RequestString)) {
      Status = EFI_NOT_FOUND;
    }
    ASSERT_EFI_ERROR (Status);
    FreePool (RequestString);
  }

  FreePool(CpuSetup);

  return EFI_SUCCESS;
}

/**
  This function displays the Memory Timing values in the OC Setup Menu when Memory Profile is changed.

  @param This            Points to the EFI_HII_CONFIG_ACCESS_PROTOCOL.
  @param Action          Specifies the type of action taken by the browser.
  @param QuestionId      A unique value which is sent to the original exporting driver
                         so that it can identify the type of data to expect.
  @param Type            The type of value for the question.
  @param Value           A pointer to the data being sent to the original exporting driver.
  @param ActionRequest   On return, points to the action requested by the callback function.

  @retval EFI_SUCCESS - The function completed successfully
  @retval EFI_UNSUPPORTED - The Setup Menu was not updated
  @retval EFI_NOT_FOUND - There is an error in Locating protocols or retrieving browser data
**/
EFI_STATUS
EFIAPI
OcFormMemoryTimingCallBackFunction (
  IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
  IN EFI_BROWSER_ACTION                   Action,
  IN EFI_QUESTION_ID                      KeyValue,
  IN UINT8                                Type,
  IN EFI_IFR_TYPE_VALUE                   *Value,
  OUT EFI_BROWSER_ACTION_REQUEST          *ActionRequest
  )
{
  EFI_STATUS                      Status;
  SA_SETUP                        SaSetup;
  UINTN                           VariableSize;
  EFI_STRING                      RequestString;
  MEMORY_TIMING                   *MemoryTiming;
  UINT8                           MemoryProfile;
  MEM_INFO_PROTOCOL               *MemInfoHobProtocol;
  MEMORY_INFO_DATA                *MemInfoData;
  MrcRefClkSelect                 RefClk;
  UINT8                           OddRatioMode;
  MrcClockRatio                   Ratio;

  RequestString = NULL;

  if (Action != EFI_BROWSER_ACTION_CHANGING && Action != EFI_BROWSER_ACTION_CHANGED) {
    return EFI_UNSUPPORTED;
  }

  // Get the Memory Info HOB Protocol if it exists.
  Status = gBS->LocateProtocol (&gMemInfoProtocolGuid, NULL, (VOID **) &MemInfoHobProtocol);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  VariableSize = sizeof (SA_SETUP);
  if (!HiiGetBrowserData (&gSaSetupVariableGuid, L"SaSetup", VariableSize, (UINT8 *) &SaSetup)) {
    return EFI_NOT_FOUND;
  }

  MemoryProfile = SaSetup.SpdProfileSelected;

  // If the MemoryProfile is changed to Custom, do display updated timing values
  if (MemoryProfile == CUSTOM_PROFILE) {
    return EFI_UNSUPPORTED;
  }

  MemInfoData  = &MemInfoHobProtocol->MemInfoData;
  MemoryTiming = &MemInfoData->Timing[MemoryProfile];

  SaSetup.tCL           = (UINT8) MemoryTiming->tCL;
  SaSetup.tCWL          = (UINT8) MemoryTiming->tCWL;
  SaSetup.tFAW          = MemoryTiming->tFAW;
  SaSetup.tRAS          = MemoryTiming->tRAS;
  SaSetup.tRCDtRP       = (UINT8) MemoryTiming->tRCDtRP;
  SaSetup.tREFI         = MemoryTiming->tREFI;
  SaSetup.tRFC          = MemoryTiming->tRFC;
  SaSetup.tRRD          = (UINT8) MemoryTiming->tRRD;
  SaSetup.tRTP          = (UINT8) MemoryTiming->tRTP;
  SaSetup.tWR           = (UINT8) MemoryTiming->tWR;
  SaSetup.tWTR          = (UINT8) MemoryTiming->tWTR;
  SaSetup.NModeSupport  = (UINT8) MemoryTiming->NMode;
  SaSetup.MemoryVoltage = MemInfoData->VddVoltage[MemoryProfile];
  ConvertClock2FreqRatio (MemoryTiming->tCK, SaSetup.BclkFrequency, (MrcFreqFlag *) &RefClk, &Ratio, &OddRatioMode);
  SaSetup.DdrRefClk     = RefClk;
  SaSetup.DdrRatio      = Ratio;
  SaSetup.DdrOddRatioMode = OddRatioMode;

  RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SA_SETUP, tCL), sizeof (SaSetup.tCL));
  RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SA_SETUP, tCWL), sizeof (SaSetup.tCWL));
  RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SA_SETUP, tFAW), sizeof (SaSetup.tFAW));
  RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SA_SETUP, tRAS), sizeof (SaSetup.tRAS));
  RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SA_SETUP, tRCDtRP), sizeof (SaSetup.tRCDtRP));
  RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SA_SETUP, tREFI), sizeof (SaSetup.tREFI));
  RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SA_SETUP, tRFC), sizeof (SaSetup.tRFC));
  RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SA_SETUP, tRRD), sizeof (SaSetup.tRRD));
  RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SA_SETUP, tRTP), sizeof (SaSetup.tRTP));
  RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SA_SETUP, tWR), sizeof (SaSetup.tWR));
  RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SA_SETUP, tWTR), sizeof (SaSetup.tWTR));
  RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SA_SETUP, NModeSupport), sizeof (SaSetup.NModeSupport));
  RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SA_SETUP, MemoryVoltage), sizeof (SaSetup.MemoryVoltage));
  RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SA_SETUP, DdrRefClk), sizeof (SaSetup.DdrRefClk));
  RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SA_SETUP, DdrRatio), sizeof (SaSetup.DdrRatio));
  RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SA_SETUP, DdrOddRatioMode), sizeof (SaSetup.DdrOddRatioMode));

  if (RequestString != NULL) {
    if (!HiiSetBrowserData (&gSaSetupVariableGuid, L"SaSetup", VariableSize, (UINT8 *) &SaSetup, RequestString)) {
      return EFI_NOT_FOUND;
    }
    FreePool (RequestString);
  }

  return EFI_SUCCESS;
}

