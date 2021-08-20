/** @file
  Platform Policy Initialization Driver

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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

#include <Library/S3BootScriptLib.h>
#include <Library/PchInfoLib.h>
#include <PlatformSetup.h>
#include <OemSetup.h>
#include <Library/GpioLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/CpuInfo.h>
#include <PlatformBoardConfig.h>
#include <SystemConfigVariable.h>
#include <Library/SataLib.h>

//
// Global variables
//

GLOBAL_REMOVE_IF_UNREFERENCED CPU_SETUP                       mCpuSetup;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *mPciRootBridgeIo;
GLOBAL_REMOVE_IF_UNREFERENCED CHAR16                          HexDigit[17] = L"0123456789ABCDEF";

GLOBAL_REMOVE_IF_UNREFERENCED EFI_PS2_POLICY_PROTOCOL         mPs2PolicyData = {
  EFI_KEYBOARD_NUMLOCK,
  (EFI_PS2_INIT_HARDWARE) Ps2InitHardware
};

GLOBAL_REMOVE_IF_UNREFERENCED SA_POLICY_PROTOCOL             *mSaPolicy;

typedef struct {
  EFI_CPUID_REGISTER        FeaturesCpuidRegs;
  EFI_CPUID_REGISTER        ExtFeaturesCpuidRegs;
} CPU_FEATURES;

// CPU Definitions
#define C1_SUB_STATES_MASK        0x000f0
#define C3_SUB_STATES_MASK        0x00f00
#define C6_SUB_STATES_MASK        0x0f000
#define C7_SUB_STATES_MASK        0xf0000
#define C8_SUB_STATES_MASK        0xf00000
#define C9_SUB_STATES_MASK        0xf000000
#define C10_SUB_STATES_MASK       0xf0000000

GLOBAL_REMOVE_IF_UNREFERENCED SETUP_VOLATILE_DATA   mSetupVolatileData = {0};
GLOBAL_REMOVE_IF_UNREFERENCED UINTN                 mNumberOfCPUs;

//
// Functions
//
/**
  Get the cpu signature.

  @retval Cpu Signature

  @todo remove and use CpuPlatformLib
**/
UINT32 GetCpuSignature (
  VOID
  )
{
  EFI_CPUID_REGISTER  CpuidRegs;
  AsmCpuid (
          1,
          &CpuidRegs.RegEax,
          &CpuidRegs.RegEbx,
          &CpuidRegs.RegEcx,
          &CpuidRegs.RegEdx
          );

  return CpuidRegs.RegEax;
}

/**
  Determine if CPU supports Execute Disable.

  @param[in] Features   Pointer to CPU_FEATURES buffer

  @retval True          if supported.

  @todo remove and use CPU Info protocol or CpuPlatformLib
**/
BOOLEAN
isXDSupported (
  CPU_FEATURES *Features
  )
{
  UINT32 CpuSignature = GetCpuSignature() & 0xff0;    //Clear extended signature.
  return (BOOLEAN)(
      (CpuSignature >= 0xf41 || CpuSignature < 0xf00) && //conroe, woodcrest CpuSignature = 6fx
      Features->ExtFeaturesCpuidRegs.RegEdx & (1 << 20)
  );
}

/**
  Determine if CPU supports Turbo mode.

  @retval True           if supported.

  @todo remove and use CPU Info protocol or CpuPlatformLib
**/
BOOLEAN
isTurboModeSupported (
  VOID
  )
{
  BOOLEAN ret;
  EFI_CPUID_REGISTER            Cpuid = { 0, 0, 0, 0 };
  MSR_REGISTER MsrData;

  MsrData.Qword = AsmReadMsr64(MSR_IA32_MISC_ENABLE);

  AsmCpuid (
          6,
          &Cpuid.RegEax,
          &Cpuid.RegEbx,
          &Cpuid.RegEcx,
          &Cpuid.RegEdx
          );

  ret = (BOOLEAN)((((Cpuid.RegEax) & 2) != 0) ||
                 (((MsrData.Qword & B_MSR_IA32_MISC_DISABLE_TURBO)) != 0)
                );
  return ret;
}

/**
  Determine if CPU supports Programmable TDC/TDP Limit for the Turbo mode.

  @retval True            if supported.

  @todo remove and use CPU Info protocol or CpuPlatformLib
**/
BOOLEAN
isXETdcTdpLimitSupported (
  VOID
  )
{
  BOOLEAN ret;
  UINT64 MsrData = AsmReadMsr64(MSR_PLATFORM_INFO);
  ret = (UINT32) (MsrData & (B_MSR_PLATFORM_INFO_PRG_TDP_LIM_EN_MASK)) ? 1:0;
  return ret;
}

/**
  Determine if CPU supports Programmable Core Ratio Limit for the Turbo mode.

  @retval True           if supported.

  @todo remove and use CPU Info protocol or CpuPlatformLib
**/
BOOLEAN
isCoreRatioLimitSupported (
  VOID
  )
{
  BOOLEAN ret;
  UINT64 MsrData = AsmReadMsr64(MSR_PLATFORM_INFO);
  ret = (UINT32) (MsrData & (B_MSR_PLATFORM_INFO_PRG_TURBO_RATIO_EN_MASK)) ? 1:0;
  return ret;
}


/**
  Determine if CPU supports VT extensions Vmx.

  @param[in] Features   Pointer to CPU_FEATURES buffer

  @retval True          if Vmx supported.

  @todo remove and use CPU Info protocol or CpuPlatformLib
**/
BOOLEAN
IsVmxSupported (
  CPU_FEATURES *Features
  )
{
  return (BOOLEAN) ((Features->FeaturesCpuidRegs.RegEcx & (1 << 5)) != 0);
}

/**
  Determine if CPU supports AES

  @param[in] Features   Pointer to CPU_FEATURES buffer

  @retval True          if Aes supported.

  @todo remove and use CPU Info protocol or CpuPlatformLib
**/
BOOLEAN
IsAesSupported (
  CPU_FEATURES *Features
  )
{
  CPUID_VERSION_INFO_ECX Ecx;

  Ecx.Uint32 = Features->FeaturesCpuidRegs.RegEcx;
  return (BOOLEAN) (Ecx.Bits.AESNI == 1);
}

/**
  Determine if CPU supports Hyper-Threading

  @retval True          if HT supported.

  @todo remove and use CPU Info protocol or CpuPlatformLib
**/
BOOLEAN
IsHTSupported (
  VOID
  )
{
  EFI_CPUID_REGISTER Cpuid= { 0, 0, 0, 0 };

  AsmCpuidEx (
    0xB,
    0,
    &Cpuid.RegEax,
    &Cpuid.RegEbx,
    &Cpuid.RegEcx,
    &Cpuid.RegEdx
    );

  return (BOOLEAN) ((Cpuid.RegEbx & 0x00FF) == 2);
}

UINT32
NumberOfCpuSocketsPopulated (
  VOID
  )
{
  return 1;
}

/**
  Determine if CPU supports Turbo mode.

  @retval True        if supported.

  @todo remove and use CPU Info protocol or CpuPlatformLib
**/
BOOLEAN
IsEnergyEfficientTurboSupported (
  VOID
  )
{
  BOOLEAN ret;
  EFI_CPUID_REGISTER Cpuid = { 0, 0, 0, 0 };
  AsmCpuid (
          6,
          &Cpuid.RegEax,
          &Cpuid.RegEbx,
          &Cpuid.RegEcx,
          &Cpuid.RegEdx
          );

  ret = (BOOLEAN)((Cpuid.RegEcx >> 3) & 1);
  return ret;
}

/**
  Reads from VR status mailbox to clear any alarms that may be present.
  Only reads the status from address 0x10.

**/
VOID
ClearVrAlarm (
  VOID
  )
{
  UINT32                  MailboxStatus;
  PCODE_MAILBOX_INTERFACE MailboxCommand;
  UINT32                  GetStatus;

  MailboxCommand.InterfaceData  = 0;
  MailboxCommand.Fields.Command = 4;
  MailboxCommand.Fields.RunBusy = 1;
  // Data for command code 0x4 MAILBOX_BIOS_CMD_VR_INTERFACE
  // [3:0]   VR ID:      2
  // [8:4]   VR Command: 0x7 SVID_COMMAND_GET_REG
  // [23:16] Address:    0x10
  // [31:31] Lock Bit:   0
  GetStatus                     = 0x100072;

  MailboxWrite (MAILBOX_TYPE_PCODE, MailboxCommand.InterfaceData, GetStatus, &MailboxStatus);
  if (MailboxStatus != EFI_SUCCESS) {
    DEBUG ((DEBUG_ERROR, "Failed to read VR status.\n"));
  }
}

/**
  Determine if CPU supports VT extensions Smx.

  @param[in] Features   Pointer to CPU_FEATURES buffer

  @retval True          if Smx supported.

  @todo remove and use CPU Info protocol or CpuPlatformLib
**/
BOOLEAN
IsSmxSupported (
  CPU_FEATURES *Features
  )
{
  return (BOOLEAN) ((Features->FeaturesCpuidRegs.RegEcx & (1 << 6)) != 0);
}

/**
  Determine if CPU supports ConfigTdp.

  @retval True          if supported.

  @todo remove and use CPU Info protocol or CpuPlatformLib
**/
UINT8
isConfigTdpSupported (
  VOID
  )
{
  UINT8 CtdpLevels;

  CtdpLevels = (UINT8)(RShiftU64(AsmReadMsr64(MSR_PLATFORM_INFO),33) & 0x03);

  if ((CtdpLevels == 1) || (CtdpLevels == 2)) {
    return 1;
  }
  return 0;
}

/**
  Determines what Ctdp levels are supported on the silicon.

  @param[in] CtdpDownSupported   - Pointer to CtdpDownSupported
  @param[in] CtdpUpSupported     - Pointer to CtdpUpSupported

  @retval VOID
**/
VOID GetConfigTdpLevelsSupported (
  IN UINT8     *CtdpDownSupported,
  IN UINT8     *CtdpUpSupported
  )
{
  MSR_REGISTER TempMsr;
  UINT8 CtdpLevels;
  UINT8 CtdpLevel0Ratio;
  UINT8 CtdpTempRatio;

  *CtdpDownSupported = FALSE;
  *CtdpUpSupported = FALSE;

  CtdpLevels = (UINT8)(RShiftU64(AsmReadMsr64(MSR_PLATFORM_INFO),33) & 0x03);

  //
  // Check the known cases of 0 and 2 additional cTDP levels supported first
  //
  if (CtdpLevels == 0) {
    //
    // No additional cTdp Levels are supported
    //
    *CtdpDownSupported = FALSE;
    *CtdpUpSupported = FALSE;
    return;
  } else if (CtdpLevels == 2) {
    //
    // All additional cTDP levels are supported
    //
    *CtdpDownSupported = TRUE;
    *CtdpUpSupported = TRUE;
    return;
  }

  //
  // Now we read the cTDP ratios from each level
  //
  TempMsr.Qword = AsmReadMsr64 (MSR_CONFIG_TDP_NOMINAL);
  CtdpLevel0Ratio = (UINT8)(TempMsr.Qword & B_MSR_CONFIG_TDP_NOMINAL_TDP_RATIO_MASK);

  TempMsr.Qword = AsmReadMsr64 (MSR_CONFIG_TDP_LEVEL1);
  CtdpTempRatio = (UINT8) RShiftU64 ( TempMsr.Qword & B_MSR_CONFIG_TDP_LEVEL1_TDP_RATIO_MASK,
                    N_MSR_CONFIG_TDP_LEVEL1_TDP_RATIO_OFFSET);

  //
  // If there is no ratio value in LVL1 MSR, check LVL2 MSR
  //
  if (CtdpTempRatio == 0) {
    TempMsr.Qword = AsmReadMsr64 (MSR_CONFIG_TDP_LEVEL2);
    CtdpTempRatio = (UINT8) RShiftU64 (TempMsr.Qword & B_MSR_CONFIG_TDP_LEVEL2_TDP_RATIO_MASK,
                    N_MSR_CONFIG_TDP_LEVEL2_TDP_RATIO_OFFSET);

  }

  //
  //  Check if additional cTDP level is Up or Down
  //
  if (CtdpTempRatio > CtdpLevel0Ratio) {
    *CtdpUpSupported = TRUE;
  } else if (CtdpTempRatio <= CtdpLevel0Ratio) {
    *CtdpDownSupported = TRUE;
  }

  DEBUG ((DEBUG_INFO, "CTDP: CtdpDownSupported = %d, CtdpUpSupported = %d\n", CtdpDownSupported, CtdpUpSupported));

  return;
}

/**
  Determine Number of cores

  @retval Number of cores

  @todo remove and use CPU Info protocol or CpuPlatformLib
**/
UINT8
GetCpuNumberofCores (
  VOID
  )
{
  UINT8 Threads;
  EFI_CPUID_REGISTER Cpuid = { 0, 0, 0, 0 };

  AsmCpuidEx (
    0xB,
    0,
    &Cpuid.RegEax,
    &Cpuid.RegEbx,
    &Cpuid.RegEcx,
    &Cpuid.RegEdx
    );

  Threads = (UINT8)(Cpuid.RegEbx);

  AsmCpuidEx (
    0xB,
    1,
    &Cpuid.RegEax,
    &Cpuid.RegEbx,
    &Cpuid.RegEcx,
    &Cpuid.RegEdx
    );

  return ((UINT8)(Cpuid.RegEbx)/Threads);
}

/**
  Determine if CPU supports LPM.

  @retval True if supported.

  @todo remove and use CPU Info protocol or CpuPlatformLib
**/
UINT8
isLpmSupported (
  VOID
  )
{
  UINT8 LpmSupport;

  LpmSupport = (UINT8) (RShiftU64(AsmReadMsr64(MSR_PLATFORM_INFO),32) & 0x01);

  if (LpmSupport == 1) {
    return 1;
  }
  return 0;
}

/**
  Determine if CPU supports Mwait.

  @retval True if supported.

  @todo remove and use CPU Info protocol or CpuPlatformLib
**/
UINT8
isTimedMwaitSupported (
  VOID
  )
{
  UINT8 MwaitSupportFlag;
  MwaitSupportFlag = (UINT8)(RShiftU64(AsmReadMsr64(MSR_PLATFORM_INFO),37) & 0x01);
  return MwaitSupportFlag;
}

/**
  Determine if CPU supports Hardware P-States.

  @retval True if supported.

  @todo remove and use CPU Info protocol or CpuPlatformLib
**/
BOOLEAN
IsHwpSupported (
  VOID
  )
{
  return (BOOLEAN)(RShiftU64(AsmReadMsr64(MSR_MISC_PWR_MGMT),6) & 0x01);
}

/**
Determine if CPU supports Intel Turbo Boost Max Technology 3.0.

@retval True if supported.

**/
BOOLEAN
IsItbmSupported (
  VOID
  )
{
  EFI_CPUID_REGISTER    Cpuid = { 0, 0, 0, 0 };

  AsmCpuidEx (
    0x6,
    0,
    &Cpuid.RegEax,
    &Cpuid.RegEbx,
    &Cpuid.RegEcx,
    &Cpuid.RegEdx
    );
  return (BOOLEAN)((Cpuid.RegEax & BIT14) == BIT14);
}

/**
Determine if CPU supports PPIN (Protected Processor Inventory Number)

@retval True if supported.

**/
BOOLEAN
IsPpinFeatureAvailable (
  VOID
  )
{
  BOOLEAN                   IsPpinFeaturePresent;

  IsPpinFeaturePresent = (((AsmReadMsr64 (MSR_PLATFORM_INFO) & BIT23) != 0) ? TRUE : FALSE);
  return (IsPpinFeaturePresent);
}

VOID
HexToString (
  CHAR16  *String,
  UINTN   Value,
  UINTN   Digits
  )
{
  for (; Digits > 0; Digits--, String++) {
    *String = HexDigit[((Value >> (4*(Digits-1))) & 0x0f)];
  }
}

/**
  Displays BIST result on Console.

  @param[in] Core         Number of Code
  @param[in] Thread       Number of Code
  @param[in] Eax          Value of Register Eax
**/
VOID
DisplaySelfTestBistResult (
  IN UINT32 Core,
  IN UINT32 Thread,
  IN UINT32 Eax
  )
{
  CHAR16                    String[20];
  CHAR16                    StrBuffer[10];

  gST->ConOut->OutputString (gST->ConOut, L"*******************BIST FAILED*****************\r\n");

  //
  // Display  Core detail
  //
  StrCpyS (String, sizeof (String) / sizeof (CHAR16), L"CORE = 0x");
  HexToString(StrBuffer, Core, 2);
  StrCpyS (String + StrLen(String), sizeof (String) / sizeof (CHAR16) - StrLen (String), StrBuffer);
  gST->ConOut->OutputString (gST->ConOut,String);

  //
  // Display  Thread detail
  //
  StrCpyS (String, sizeof (String) / sizeof (CHAR16), L" Thread = 0x");
  HexToString(StrBuffer, Thread, 2);
  StrCpyS (String + StrLen(String), sizeof (String) / sizeof (CHAR16) - StrLen (String), StrBuffer);
  gST->ConOut->OutputString (gST->ConOut,String);

  //
  // Display  Eax detail
  //
  StrCpyS (String, sizeof (String) / sizeof (CHAR16), L" EAX = 0x");
  HexToString(StrBuffer, Eax, 4);
  StrCpyS (String + StrLen(String), sizeof (String) / sizeof (CHAR16) - StrLen (String), StrBuffer);
  gST->ConOut->OutputString (gST->ConOut,String);
  gST->ConOut->OutputString (gST->ConOut,L"\r\n");
}

/**
  Self Test BIST result computed.

  @param[in] Event    Event whose notification function is being invoked.
  @param[in] Context  Pointer to the notification function's context.
**/
VOID
EFIAPI
SelfTestBistErrMsg (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  EFI_STATUS                          Status;
  EFI_PROCESSOR_INFORMATION           MpContext;
  EFI_MP_SERVICES_PROTOCOL            *MpServices;
  UINT32                              Index;
  BOOLEAN                             BistFailed = FALSE;

  Status = gBS->LocateProtocol (
                  &gEfiMpServiceProtocolGuid,
                  NULL,
                  (VOID **) &MpServices
                  );
  ASSERT_EFI_ERROR (Status);

  gST->ConOut->ClearScreen (gST->ConOut);

  for (Index = 0; Index < mNumberOfCPUs; Index++) {
    Status = MpServices->GetProcessorInfo (MpServices, Index, &MpContext);
    ASSERT_EFI_ERROR (Status);
    if (MpContext.ProcessorId > 255) {
      break;
    }
    if ((MpContext.StatusFlag & PROCESSOR_HEALTH_STATUS_BIT) == 0) {
      BistFailed = TRUE;
      DEBUG ((DEBUG_ERROR, "BIST FAILED CORE=%x THREAD=%x EAX=%x\n", (UINT32)MpContext.Location.Core, (UINT32)MpContext.Location.Thread, MpContext.StatusFlag));
      DisplaySelfTestBistResult(
                   (UINT32)MpContext.Location.Core,
                   (UINT32)MpContext.Location.Thread,
                   MpContext.StatusFlag
                   );
    }
  }

  if (BistFailed) {
    DEBUG ((DEBUG_ERROR, "BIST Failed!!\n"));
    CpuDeadLoop();
  } else {
    DEBUG ((DEBUG_INFO, "BIST passed\n"));
  }
  gBS->CloseEvent(Event);

}

VOID
EFIAPI
CpuSetupInitCallback (
  IN EFI_EVENT     Event,
  IN VOID          *Context
  )
{
  EFI_STATUS                                   Status;
  SETUP_CPU_FEATURES                           SetupCpuFeatures;
  UINTN                                        Index;
  EFI_PROCESSOR_INFORMATION                    MpContext;
  VOID                                         *VariableWrite;
  EFI_CPUID_REGISTER                           CpuidRegs;
  EFI_EVENT                                    ReadyToBootEvent;
  EFI_MP_SERVICES_PROTOCOL                     *MpServices;
  UINTN                                        NumberOfEnabledCPUs;
  UINT32                                       SetupCpuFeaturesAttr;
  UINT8                                        *SetupCpuVar;
  UINTN                                        SetupCpuFeaturesSize;
  CPU_INFO_PROTOCOL                            *CpuInfo;
  CPU_FEATURES                                 CpuFeatures;
  CPU_SKU                                      CpuSku;
  CPU_GENERATION                               CpuGeneration;
  CPUID_STRUCTURED_EXTENDED_FEATURE_FLAGS_EBX  ExtFeatureFlagEbx;
  CPUID_STRUCTURED_EXTENDED_FEATURE_FLAGS_ECX  ExtFeatureFlagEcx;


  SetupCpuFeaturesAttr = 0;
  SetupCpuVar = NULL;
  SetupCpuFeaturesSize = 0;
  Status = gBS->LocateProtocol (
                  &gEfiMpServiceProtocolGuid,
                  NULL,
                  (VOID **) &MpServices
                  );
  if (EFI_ERROR(Status)) {
    return;
  }

  Status = gBS->LocateProtocol (
                  &gEfiVariableWriteArchProtocolGuid,
                  NULL,
                  &VariableWrite
                  );
  if (EFI_ERROR(Status)) {
    return;
  }

  DEBUG ((DEBUG_INFO, "Running CpuSetupInitCallback...\n"));

  AsmCpuid (
    CPUID_VERSION_INFO,
    &CpuFeatures.FeaturesCpuidRegs.RegEax,
    &CpuFeatures.FeaturesCpuidRegs.RegEbx,
    &CpuFeatures.FeaturesCpuidRegs.RegEcx,
    &CpuFeatures.FeaturesCpuidRegs.RegEdx
    );

  AsmCpuid (
    CPUID_SIGNATURE,
    &CpuidRegs.RegEax,
    &CpuidRegs.RegEbx,
    &CpuidRegs.RegEcx,
    &CpuidRegs.RegEdx
    );

  if(CpuidRegs.RegEax > 3) {    //Check for largest CpuId
    AsmCpuid (
      CPUID_EXTENDED_CPU_SIG,
      &CpuFeatures.ExtFeaturesCpuidRegs.RegEax,
      &CpuFeatures.ExtFeaturesCpuidRegs.RegEbx,
      &CpuFeatures.ExtFeaturesCpuidRegs.RegEcx,
      &CpuFeatures.ExtFeaturesCpuidRegs.RegEdx
      );
  }

  //
  // Only show as supported if all are supported.
  //
  ZeroMem(&SetupCpuFeatures, sizeof(SetupCpuFeatures));
  SetupCpuFeatures.XDBitAvailable = isXDSupported(&CpuFeatures);
  SetupCpuFeatures.TurboModeAvailable = isTurboModeSupported();
  SetupCpuFeatures.XETdcTdpLimitAvailable = isXETdcTdpLimitSupported();
  SetupCpuFeatures.CoreRatioLimitAvailable = isCoreRatioLimitSupported();
  SetupCpuFeatures.ConfigTdpAvailable = isConfigTdpSupported();
  SetupCpuFeatures.LpmAvailable = isLpmSupported();
  SetupCpuFeatures.VTAvailable = IsVmxSupported(&CpuFeatures);
  SetupCpuFeatures.AESAvailable = IsAesSupported(&CpuFeatures);
  SetupCpuFeatures.HTAvailable = IsHTSupported();
  SetupCpuFeatures.MultiCoreAvailable = 1;
  SetupCpuFeatures.MultiSocketAvailable = 0;
  SetupCpuFeatures.MultiSocketPopulated = (UINT8)(NumberOfCpuSocketsPopulated() > 1);
  SetupCpuFeatures.LocalX2ApicAvailable = (UINT8)(!!(CpuFeatures.FeaturesCpuidRegs.RegEcx & LShiftU64(1 ,21)));
  SetupCpuFeatures.EnergyEfficientTurboAvailable = IsEnergyEfficientTurboSupported();
  SetupCpuFeatures.TimedMwaitSupported = isTimedMwaitSupported();
  SetupCpuFeatures.HwpAvailable = IsHwpSupported();
  GetConfigTdpLevelsSupported(&SetupCpuFeatures.CtdpDownSupported, &SetupCpuFeatures.CtdpUpSupported);

  SetupCpuFeatures.ItbmAvailable = IsItbmSupported();
  DEBUG((DEBUG_INFO, "Itbm: SetupCpuFeatures.ItbmAvailable = 0x%x \n", SetupCpuFeatures.ItbmAvailable));

  SetupCpuFeatures.PpinFeatureAvailable = IsPpinFeatureAvailable ();
  DEBUG((DEBUG_INFO, "SetupCpuFeatures.PpinFeatureAvailable = 0x%x \n", SetupCpuFeatures.PpinFeatureAvailable));

  //
  // Check CPU SKU to determine FIVR support
  //
  CpuSku = GetCpuSku();
  CpuSku = EnumCpuTrad;
  if ((CpuSku == EnumCpuTrad) || (CpuSku == EnumCpuHalo)) {
    SetupCpuFeatures.FivrSupported = 1;
  }

  CpuGeneration = GetCpuGeneration();
  if (CpuGeneration == EnumCflCpu) {
    SetupCpuFeatures.FclkSupported = 1;
  } else {
    SetupCpuFeatures.FclkSupported = 0;
  }

  SetupCpuFeatures.ApicIdFlag = 0;

  Status = MpServices->GetNumberOfProcessors (MpServices, &mNumberOfCPUs, &NumberOfEnabledCPUs);
  ASSERT_EFI_ERROR (Status);

  for (Index = 0; Index < mNumberOfCPUs; Index++) {
    Status = MpServices->GetProcessorInfo (MpServices, Index, &MpContext);
    ASSERT_EFI_ERROR (Status);
    if (MpContext.ProcessorId > 255) {
      SetupCpuFeatures.ApicIdFlag = 1;
      break;
    }
  }

  //
  // Setup For CPU PPM
  //
  SetupCpuFeatures.CxAvailable = 0;
  SetupCpuFeatures.C1Available = 0;
  SetupCpuFeatures.C1EAvailable = 0;
  SetupCpuFeatures.C3Available = 0;
  SetupCpuFeatures.C6Available = 0;
  SetupCpuFeatures.C7Available = 0;
  SetupCpuFeatures.C8Available = 0;
  SetupCpuFeatures.C9Available = 0;
  SetupCpuFeatures.C10Available = 0;

  if (CpuFeatures.FeaturesCpuidRegs.RegEcx & LShiftU64(1, 3)) {
    AsmCpuid (
      5,
      &CpuidRegs.RegEax,
      &CpuidRegs.RegEbx,
      &CpuidRegs.RegEcx,
      &CpuidRegs.RegEdx
      );

    //
    // Don't use mwait for now to halt CPU in BIOS.
    //
    //if (RegEcx & 0x01) {
    //  UseMwait = TRUE;
    //}
    if ((CpuidRegs.RegEdx & C1_SUB_STATES_MASK)) {
      SetupCpuFeatures.C1Available = 1;
      if ((RShiftU64 ((CpuidRegs.RegEdx & C1_SUB_STATES_MASK), 4)) >= ENHANCED_CSTATE_SUPPORTED) {
        SetupCpuFeatures.C1EAvailable = 1;
      }
    }
    if (CpuidRegs.RegEdx & C3_SUB_STATES_MASK) {
      SetupCpuFeatures.C3Available = 1;
    }
    if (CpuidRegs.RegEdx & C6_SUB_STATES_MASK) {
      SetupCpuFeatures.C6Available = 1;
    }
    if (CpuidRegs.RegEdx & C7_SUB_STATES_MASK) {
      SetupCpuFeatures.C7Available = 1;
    }
     if (PcdGet8 (PcdPlatformType) == TypeUltUlx) {
      if (CpuidRegs.RegEdx & C8_SUB_STATES_MASK) {
        SetupCpuFeatures.C8Available = 1;
      }
      if (CpuidRegs.RegEdx & C9_SUB_STATES_MASK) {
        SetupCpuFeatures.C9Available = 1;
      }
      if (CpuidRegs.RegEdx & C10_SUB_STATES_MASK) {
        SetupCpuFeatures.C10Available = 1;
      }
    }
  }

  //
  // This allows the setup question to limit package C-states.
  // Enable after further testing.
  //
  SetupCpuFeatures.CxAvailable =
      SetupCpuFeatures.C1Available |
      SetupCpuFeatures.C3Available |
      SetupCpuFeatures.C6Available |
      SetupCpuFeatures.C7Available;

  //
  // Checking TXT capability after all CPU initialized
  //
  SetupCpuFeatures.TXTAvailable = IsSmxSupported(&CpuFeatures);

  SetupCpuFeatures.EISTAvailable = TRUE;
  if (!(CpuFeatures.FeaturesCpuidRegs.RegEcx & 0x80)) {
    SetupCpuFeatures.EISTAvailable = FALSE;
  }
  //
  // Getting Number of Cores
  //
  SetupCpuFeatures.NumCores = GetCpuNumberofCores();
  ///
  /// Debug interface is supported if CPUID (EAX=1): ECX[11] = 1
  ///
  SetupCpuFeatures.DebugInterfaceSupported = 0;
  if (CpuFeatures.FeaturesCpuidRegs.RegEcx & BIT11) {
    SetupCpuFeatures.DebugInterfaceSupported = 1;
  }

  ///
  /// Processor supports HDC feature if silicon info indicates it
  ///
  SetupCpuFeatures.HdcSupported = 0;
  Status = gBS->LocateProtocol (&gCpuInfoProtocolGuid, NULL, (VOID **) &CpuInfo);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Located CpuInfo Protocol Status = %r\n", Status));
  } else {
    DEBUG ((DEBUG_INFO, "CpuInfo->CpuCommonFeatures = %016X\n", CpuInfo->CpuCommonFeatures));
    if (CpuInfo->CpuCommonFeatures & HDC_SUPPORT) {
      SetupCpuFeatures.HdcSupported = 1;
    }
  }

  SetupCpuFeatures.SgxSupported   = 0;
  ///
  /// PRMRR configuration enabled, MSR IA32_MTRRCAP (FEh) [12] == 1
  ///
  if (AsmReadMsr64(MSR_IA32_MTRRCAP) & BIT12) {
    ///
    /// Processor supports SGX feature if CPUID.(EAX=0x7, ECX=0x0):EBX[2] is set
    ///
    AsmCpuidEx (
      CPUID_STRUCTURED_EXTENDED_FEATURE_FLAGS,
      CPUID_STRUCTURED_EXTENDED_FEATURE_FLAGS_SUB_LEAF_INFO,
      NULL,
      &ExtFeatureFlagEbx.Uint32,
      &ExtFeatureFlagEcx.Uint32,
      NULL
      );

    if (ExtFeatureFlagEbx.Bits.SGX) {
      SetupCpuFeatures.SgxSupported = 1;
    }
  }

  ///
  /// set C6DRAM support
  ///
  ///
  /// Clear any VR alarms
  ///
  ClearVrAlarm();

  ///
  /// Processor Trace feature is supported only on BDW and later,
  /// with CPUID.(EAX=7):EBX[25] = 1
  ///
  SetupCpuFeatures.ProcTraceSupported = 0;
  AsmCpuidEx (
    0x7,
    0,
    &CpuidRegs.RegEax,
    &CpuidRegs.RegEbx,
    &CpuidRegs.RegEcx,
    &CpuidRegs.RegEdx
    );

  if (CpuidRegs.RegEbx & BIT25) {
    SetupCpuFeatures.ProcTraceSupported = 1;
  }

  SetupCpuVar = AllocateZeroPool (sizeof (SETUP_CPU_FEATURES));
  SetupCpuFeaturesSize = sizeof (SETUP_CPU_FEATURES);
  Status = gRT->GetVariable (
                  L"SetupCpuFeatures",
                  &gSetupVariableGuid,
                  &SetupCpuFeaturesAttr,
                  &SetupCpuFeaturesSize,
                  SetupCpuVar
                  );
  FreePool (SetupCpuVar);
  if (EFI_ERROR (Status)) {
    SetupCpuFeaturesAttr = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS;
  }

  Status = gRT->SetVariable(
                  L"SetupCpuFeatures",
                  &gSetupVariableGuid,
                  SetupCpuFeaturesAttr,
                  sizeof(SETUP_CPU_FEATURES),
                  &SetupCpuFeatures
                  );
  ASSERT_EFI_ERROR(Status);

  //
  // Display Bist information to the user if Bist is enabled in Setup
  //
  if (mCpuSetup.BistOnReset) {
    //
    // Create an Ready to Boot event.
    //
    Status = EfiCreateEventReadyToBootEx (
               TPL_CALLBACK,
               SelfTestBistErrMsg,
               NULL,
               &ReadyToBootEvent
               );
    ASSERT_EFI_ERROR (Status);
  }

  gBS->CloseEvent (Event);
}

EFI_STATUS
CpuSetupInit (
  VOID
  )
{
  VOID                    *Registration1;
  VOID                    *Registration2;

  EfiCreateProtocolNotifyEvent (
    &gEfiMpServiceProtocolGuid,
    TPL_CALLBACK,
    CpuSetupInitCallback,
    NULL,
    &Registration1
    );

  EfiCreateProtocolNotifyEvent (
    &gEfiVariableWriteArchProtocolGuid,
    TPL_CALLBACK,
    CpuSetupInitCallback,
    NULL,
    &Registration2
    );

  return EFI_SUCCESS;
}

VOID
EFIAPI
PlatformPcdInit (
  VOID
  )
{
  UINTN                 VarSize;
  EFI_STATUS            Status;
  CPU_SETUP             CpuSetup;
  SETUP_DATA            SetupData;

  VarSize = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  NULL,
                  &VarSize,
                  &SetupData
                  );
  if (EFI_ERROR (Status)) {
    DEBUG((DEBUG_ERROR, "Failed to get setup variable\n"));
    return;
  }

  VarSize = sizeof (CPU_SETUP);
  Status = gRT->GetVariable (
                  L"CpuSetup",
                  &gCpuSetupVariableGuid,
                  NULL,
                  &VarSize,
                  &CpuSetup
                  );
  if (EFI_ERROR (Status)) {
    DEBUG((DEBUG_ERROR, "Failed to get CPU Setup variable\n"));
    return;
  }

  if (SetupData.FastBoot) {
    //
    // Disable MdeModulePkg core PcdAtaSmartEnable to skip HDD SMART enabling
    //
    PcdSetBoolS (PcdAtaSmartEnable, FALSE);
    //
    // Enable gEfiMdeModulePkgTokenSpaceGuid PcdFastPS2Detection to enable quick PS2 device detection
    //
    PcdSetBoolS (PcdFastPS2Detection, TRUE);
  }

  //
  // Change PcdAcpiDebugEnable PCD to TRUE if ACPI DEBUG is enabled in Setup menu
  //
  if (SetupData.AcpiDebug) {
    PcdSetBoolS (PcdAcpiDebugEnable, TRUE);
  } else {
    PcdSetBoolS (PcdAcpiDebugEnable, FALSE);
  }

  //
  // Change PcdRuntimeOverclockEnable PCD to TRUE if Over-clocking Support is enabled in Setup menu
  //
  if (CpuSetup.OverclockingSupport) {
    PcdSetBoolS (PcdRuntimeOverclockEnable, TRUE);
  } else {
    PcdSetBoolS (PcdRuntimeOverclockEnable, FALSE);
  }

  //
  // Update AHCI max ports
  //
  if (MaxSataControllerNum () != 0) {
    PcdSet8S (PcdAhciMaxPorts, MaxSataPortNum (SATA_1_CONTROLLER_INDEX));
  }

  return;
}


/**
  This is the standard  driver entry point for the Platform Setup Driver.
  This driver is responsible for setting up any platform specific policy or
  initialization information.

  @param[in] ImageHandle     - Handle for the image of this driver
  @param[in] SystemTable     - Pointer to the EFI System Table

  @retval EFI_SUCCESS        - Policy decisions are set successfully
**/
EFI_STATUS
EFIAPI
PlatformSetupEntry (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                         Status;
  EFI_HANDLE                         Handle;
  UINTN                              VariableSize;
  UINT32                             SetupVolAttributes;
  BOOLEAN                            HiiDataExport;
  MEM_INFO_PROTOCOL                  *MemoryInfoProtocol;

  Handle        = NULL;
  HiiDataExport = FALSE;

  Status = gBS->LocateProtocol (&gEfiPciRootBridgeIoProtocolGuid, NULL, (VOID **) &mPciRootBridgeIo);
  ASSERT_EFI_ERROR (Status);

  Status = gBS->LocateProtocol (&gSaPolicyProtocolGuid, NULL, (VOID **) &mSaPolicy);
  ASSERT_EFI_ERROR (Status);

  //
  // Change PCD's value that depend on xxxSetup variable
  //
  PlatformPcdInit();

  //
  // Get platform Setup setting.
  //
  // @todo missing SETUP_DATA.MicrocodeUpdateSignature and SETUP_DATA.InterruptFilteringEnable
  //
  VariableSize = sizeof (CPU_SETUP);
  ZeroMem (&mCpuSetup, VariableSize);
  gRT->GetVariable (L"CpuSetup", &gCpuSetupVariableGuid, NULL, &VariableSize, &mCpuSetup);

  //
  // Create and zero initialize SetupVolatileData variable.
  //
  VariableSize = sizeof(SETUP_VOLATILE_DATA);
  Status = gRT->GetVariable (
                  L"SetupVolatileData",
                  &gSetupVariableGuid,
                  &SetupVolAttributes,
                  &VariableSize,
                  &mSetupVolatileData
                  );
  ASSERT (Status == EFI_NOT_FOUND);
  mSetupVolatileData.PlatformFlavor = PcdGet8 (PcdPlatformFlavor); // Platform Reset will check this data for SusPwrDnAck setting
  if(HiiDataExport) {
    SetupVolAttributes = EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS;
  } else {
    SetupVolAttributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;
  }
  Status = gRT->SetVariable (
                  L"SetupVolatileData",
                  &gSetupVariableGuid,
                  SetupVolAttributes,
                  sizeof(SETUP_VOLATILE_DATA),
                  &mSetupVolatileData
                  );
  ASSERT_EFI_ERROR(Status);

  //
  // Initialize some variables for CPU Setup Page
  //
  CpuSetupInit();

  //
  // Initialize the MEM_INFO_PROTOCOL structure
  //
  MemoryInfoProtocol = AllocateZeroPool (sizeof (MEM_INFO_PROTOCOL));
  if (MemoryInfoProtocol == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  //
  // Set up the policy protocols
  //
  SetupPlatformPolicies (
    MemoryInfoProtocol
    );
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gMemInfoProtocolGuid,
                  MemoryInfoProtocol,
                  &gDxePolicyProtocolGuid,
                  NULL,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  if (PcdGetBool (PcdEcPresent) == TRUE) {
    Status = gBS->InstallProtocolInterface (
                    &Handle,
                    &gEfiPs2PolicyProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &mPs2PolicyData
                    );
    ASSERT_EFI_ERROR (Status);
  }

  return EFI_SUCCESS;
}
