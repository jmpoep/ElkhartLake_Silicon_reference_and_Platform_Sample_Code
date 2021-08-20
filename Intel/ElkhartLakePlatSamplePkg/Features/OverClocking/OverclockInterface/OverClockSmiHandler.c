/** @file
  Implements SW SMI communication interface for OS Application Iron city

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2018 Intel Corporation.

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

//
// External include files do NOT need to be explicitly specified in real EDKII
// environment
//
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/SmmMemLib.h>
#include <Protocol/SmmVariable.h>
#include <Protocol/SmmSwDispatch2.h>
#include <Protocol/SmmBase2.h>
#include <Protocol/SmmCpuSaveState.h>
#include "OverClockSmiHandler.h"
#include <CpuDataStruct.h>
#include <SetupVariable.h>
#include <OcSetupVariable.h>

#define MSR_CORE_THREAD_COUNT               0x35
#define MSR_IA32_MISC_ENABLE                0x1a0
#define TURBO_DISABLE_MASK                  ((UINT64) 1 << 38)
#define TURBO_MODE_DISABLE_BIT              38
#define MSR_PLATFORM_INFO                   0xce
#define XE_TDP_TDC_PROGRAMMABLE_BIT         29
#define XE_CORE_RATIO_PROGRAMMABLE_BIT      28
#define MAX_NON_TURBO_RATIO_OFFSET          8
#define MAX_EFFICIENCY_RATIO_OFFSET         40
#define MAX_NON_TURBO_RATIO_MASK            0xff
#define MAX_EFFICIENCY_RATIO_MASK           0xff
#define PROG_TDP_LIMITS                         (1 << 29)
#define PROG_RATIO_LIMITS                       (1 << 28)
#define PROG_TCC_ACTIVATION_OFFSET              (1 << 30)

#define SYNC_SMI_BIT  (1 << 0)

//
// Global variables
//
GLOBAL_REMOVE_IF_UNREFERENCED UINT16                    mNumberOfActiveCores = 0;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_SMM_VARIABLE_PROTOCOL *mSmmVariable;

/**
  Determine if CPU supports Turbo mode.

**/
BOOLEAN isTurboModeSupported (
  VOID
  )
{
  BOOLEAN ret;
  EFI_CPUID_REGISTER            Cpuid = { 0, 0, 0, 0 };
  MSR_REGISTER MsrData;

  MsrData.Qword = AsmReadMsr64 (MSR_IA32_MISC_ENABLE);

  AsmCpuid (6, &Cpuid.RegEax, &Cpuid.RegEbx, &Cpuid.RegEcx, &Cpuid.RegEdx);
  ret = (BOOLEAN)((((Cpuid.RegEax) & 2) != 0) ||
                 (((MsrData.Qword & TURBO_DISABLE_MASK)) != 0)
                );
  return ret;
}

/**
  Determine if CPU supports Programmable TDC/TDP Limit for the Turbo mode.

**/
BOOLEAN isXETdcTdpLimitSupported (
  VOID
  )
{
  BOOLEAN ret;
  UINT64 MsrData = AsmReadMsr64(MSR_PLATFORM_INFO);
  ret = (UINT32) (MsrData & (PROG_TDP_LIMITS)) ? 1:0;
  return ret;
}

/**
  Determine if CPU supports Programmable Core Ratio Limit for the Turbo mode.

**/
BOOLEAN isCoreRatioLimitSupported (
  VOID
  )
{
  BOOLEAN ret;
  UINT64 MsrData = AsmReadMsr64 (MSR_PLATFORM_INFO);
  ret = (UINT32) (MsrData & (PROG_RATIO_LIMITS)) ? 1:0;
  return ret;
}

/**
  This function is the SMM handler. It reads or write BIOS settings
  data with respect to BIOS settings command.

  @param[in] DispatchHandle      The handle of the dispatch
  @param[in] DispatchContext     A Pointer to EFI_SMM_SW_REGISTER_CONTEXT
  @param[in] CommBuffer          A Pointer to
  @param[in] CommBufferSize      A Pointer to

**/
EFI_STATUS
EFIAPI
SMIFlashSMIHandler (
  IN         EFI_HANDLE                 DispatchHandle,
  IN  CONST  VOID                       *DispatchContext,
  IN  OUT    VOID                       *CommBuffer,
  IN  OUT    UINTN                      *CommBufferSize
  )
{
  EFI_STATUS                  Status;
  UINT32                      ReadWrite;
  UINT32                      TimerValue;
  UINTN                       OcVariableSize;
  UINTN                       Cpu;
  BIOS_SETTINGS_DATA_HEADER   *MemoryDataLocation;
  OC_SETUP_DATA               OcSetupData;
  UINT32                      Length;
  BOOLEAN                     TurboModeSupported;
  BOOLEAN                     TurboTdpLimitProgrammable;
  BOOLEAN                     CoreRatioLimitAvailable;
  UINTN                       HeaderLength;
  UINT8                       Index;
  UINT32                      Count;
  UINT32                      BiosSettingValue;
  BIOS_SETTING_ENTRY          *BiosSettingEntries;
  UINT32                      Smbase;
  UINT32                      SmmIoMiscInfo;
  EFI_SMM_CPU_STATE           *pCpuSaveState;
  EFI_SMM_CPU_STATE           *CpuSaveState;
  UINTN                       CpuIndex;
  UINT32                      OcVariableAttributes;

  OcVariableSize = sizeof (OC_SETUP_DATA);
  Length = 0;
  Index = 0;
  Count = 0;

  Status = mSmmVariable->SmmGetVariable (
                            L"OcSetup",
                            &gOcSetupVariableGuid,
                            &OcVariableAttributes,
                            &OcVariableSize,
                            &OcSetupData
                           );
  if (EFI_ERROR (Status)) {
    //
    // If the variable is not found...
    //
    DEBUG ((DEBUG_ERROR, "[OC SMI Handler] Get OcSetup Status = %r\n", Status));
    return Status;
  }
  // Do not process XTU SMI requests if overclocking support is disabled
  if (EFI_ERROR (Status) || OcSetupData.OverclockingSupport == 0) {
    DEBUG ((DEBUG_INFO, "OC SMI: Overclocking is disabled.\n"));
    return Status;
  }

  CpuSaveState = NULL;
  for (CpuIndex = 0; CpuIndex < gSmst->NumberOfCpus; CpuIndex++) {
    //
    // Find which CPU caused the SW SMI
    //
    Smbase = ((EFI_SMM_CPU_STATE *)(gSmst->CpuSaveState[CpuIndex]))->x64.SMBASE;

    SmmIoMiscInfo = *(UINT32 *) (((UINT8 *) (UINTN) Smbase) + 0x8000 + 0x7FA4);

    if (((SmmIoMiscInfo >> 16) == 0xB2) && (SmmIoMiscInfo & SYNC_SMI_BIT)) {
      CpuSaveState = (EFI_SMM_CPU_STATE *)(&(gSmst->CpuSaveState[CpuIndex]));
      break;
    }
  }
  ASSERT (CpuSaveState != NULL);

  Cpu = CpuIndex;

  //
  // Get the BIOS Settings command (ECX) and 32-bit Physical Memory Data Location (EBX)
  // of the Setting Data structure from the CPU save state.
  //
  pCpuSaveState              = (EFI_SMM_CPU_STATE *)(gSmst->CpuSaveState[Cpu]);
  ReadWrite                  = (UINT32) (pCpuSaveState->x64)._RCX;
  TimerValue                 = (UINT32) (pCpuSaveState->x64)._RBX;
  MemoryDataLocation         = (BIOS_SETTINGS_DATA_HEADER*) (UINTN) (pCpuSaveState->x64)._RBX;
  BiosSettingEntries = (BIOS_SETTING_ENTRY*)((UINTN)MemoryDataLocation + sizeof(BIOS_SETTINGS_DATA_HEADER));

  if (!SmmIsBufferOutsideSmmValid ((UINTN) MemoryDataLocation, MemoryDataLocation->Length)) {
    return EFI_SECURITY_VIOLATION;
  }

  TurboModeSupported         = isTurboModeSupported();
  TurboTdpLimitProgrammable  = isXETdcTdpLimitSupported();
  CoreRatioLimitAvailable    = isCoreRatioLimitSupported();

  if ((ReadWrite != OVERCLOCK_SMI_READ_COMMAND) && (ReadWrite != OVERCLOCK_SMI_WRITE_COMMAND) &&
     (ReadWrite != OVERCLOCK_SMI_WDT_CONFIRM_REQUEST_COMMAND)) {
    (pCpuSaveState->x64)._RBX = (UINT32)0x00008004;  //Command not valid in ECX
    return Status;
  }

  //
  // Read BIOS settings data from Setup and pass it to OS Application through MemoryDataLocation
  //
  if (ReadWrite == OVERCLOCK_SMI_READ_COMMAND) {
    UINT16 XtuCoreVoltageOffset;
    UINT8  XtuOcEnable;
    UINT16 XtuGtVoltageOffset;
    UINT16 XtuUncoreVoltageOffset;

    // HeaderLength = Signature + Length + MajorRev + MinorRev
    HeaderLength = sizeof(BIOS_SETTINGS_DATA_HEADER) - sizeof(UINT32);

    // Total size of BIOS Setting Data Structure = Header + Size of Static Entries + Size of Dynamic Entries
    // Static entries = entries added without condtional logic.
    // Dynamic etries = entries added based on conditional logic.
    Length = sizeof(BIOS_SETTINGS_DATA_HEADER) + (NO_OF_BIOS_SETTING_STATIC_ENTRIES*sizeof(BIOS_SETTING_ENTRY));
    Count = NO_OF_BIOS_SETTING_STATIC_ENTRIES;

    //
    // Now add the sizes of the conditional control ID's
    //
    if ( TurboModeSupported ) {
      // one entry for Turbo Mode Enable/Disable
      Length += sizeof(BIOS_SETTING_ENTRY);
      Count++;
      // entries for Long ,Short Duration Power Limit Enable/Disable, Short Duration Turbo Power Limit and Turbo Power Limit Lock
      if( TurboTdpLimitProgrammable ) {
        Length += (4*sizeof(BIOS_SETTING_ENTRY));
        Count += 4;
      }
      // 4 entries for Turbo Core Ratio's
      if ( CoreRatioLimitAvailable ) {
        //
        // Entries for 1C and 2C
        //
        Length += (2*sizeof(BIOS_SETTING_ENTRY));
        Count += 2;
        //
        // Entries for 3C and 4C
        //
        if( mNumberOfActiveCores > 2 ) {
          Length += (2*sizeof(BIOS_SETTING_ENTRY));
          Count += 2;
        }
      }
    }

    if (MemoryDataLocation->Signature != BIOSSETTINGS_SIG_REV4) {
      if (MemoryDataLocation->Signature != BIOSSETTINGS_SIG_REV3) {
        //return error code EBX
        (pCpuSaveState->x64)._RBX = (UINT32)0x00008001;  //signature wrong
        return Status;
      } else {
        //update Sign, length, MajorRev, MinorRev.
        MemoryDataLocation->Signature = BIOSSETTINGS_SIG_REV4;
        MemoryDataLocation->Length = Length;
        MemoryDataLocation->MajorRev = 2;
        MemoryDataLocation->MinorRev = 0;
        (pCpuSaveState->x64)._RBX = (UINT32)0x00000001;  // Warning Old Signature $BD$
        return Status;
      }
    } else if(MemoryDataLocation->Length > Length) {
      MemoryDataLocation->Length = Length;
      MemoryDataLocation->MajorRev = 2;
      MemoryDataLocation->MinorRev = 0;
      (pCpuSaveState->x64)._RBX = (UINT32)0x00000002;  // length larger than expected
    } else if(MemoryDataLocation->Length < HeaderLength) {
      (pCpuSaveState->x64)._RBX = (UINT32)0x00008003;  // Table length too small, no header data returned.
      return Status;
    } else if(MemoryDataLocation->Length < Length) {
      MemoryDataLocation->Length = Length;
      MemoryDataLocation->MajorRev = 2;
      MemoryDataLocation->MinorRev = 0;
      (pCpuSaveState->x64)._RBX = (UINT32)0x00008002;  // Table length too small, valid header data returned.
      return Status;
    } else {
      (pCpuSaveState->x64)._RBX = (UINT32)0x0;  //successful
      MemoryDataLocation->MajorRev = 2;
      MemoryDataLocation->MinorRev = 0;
    }
    DEBUG ((DEBUG_INFO, "OC SMI: SMI entry Count = %X\n", Count));
    MemoryDataLocation->Count = Count;

    //
    // EIST
    //
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index, OcSetupData.EnableGv, BIOS_DEVICE_EIST);

    //
    // Flex ratio
    //
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index, OcSetupData.CpuRatio, BIOS_DEVICE_FLEX_RATIO);

    //
    // CAS Latency
    //
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index, OcSetupData.tCL, BIOS_DEVICE_tCL);

    //
    // tRCD / tRP
    //
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index, OcSetupData.tRCDtRP, BIOS_DEVICE_tRCD_tRP);

    //
    // tRAS
    //
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index, OcSetupData.tRAS, BIOS_DEVICE_tRAS);

    //
    // tWR
    //
    ADD_ENTRY_TO_BIOS_SETTING_TABLE_AUTOMATIC (BiosSettingEntries, Index, OcSetupData.tWR, BIOS_DEVICE_tWR, 0);

    //
    // tRFC
    //
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index, OcSetupData.tRFC, BIOS_DEVICE_tRFC);

    //
    // tRRD
    //
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index, OcSetupData.tRRD, BIOS_DEVICE_tRRD);

    //
    // tWTR
    //
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index, OcSetupData.tWTR, BIOS_DEVICE_tWTR);

    //
    // tRTP
    //
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index, OcSetupData.tRTP, BIOS_DEVICE_tRTP);

    //
    // tFAW
    //
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index, OcSetupData.tFAW, BIOS_DEVICE_tFAW);

    //
    // System Command Rate (NMode)
    //
    ADD_ENTRY_TO_BIOS_SETTING_TABLE_AUTOMATIC (BiosSettingEntries, Index, OcSetupData.NModeSupport, BIOS_DEVICE_SYSTEM_CMD_RATE, 0);

    //
    // DDR Multiplier
    //
    ADD_ENTRY_TO_BIOS_SETTING_TABLE_AUTOMATIC (BiosSettingEntries, Index, OcSetupData.DdrRatio, BIOS_DEVICE_DDR_MULTIPLIER, OcSetupData.DdrRatioDefault);

    //
    // Memory Voltage
    //
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index, OcSetupData.MemoryVoltage, BIOS_DEVICE_MEMORY_VOLTAGE);

    //
    // Host Clock Frequency entry
    //
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index, OcSetupData.BclkFrequency, BIOS_DEVICE_HOST_CLK_FREQ);

    //
    // Internal Graphics Freq
    //
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index, OcSetupData.GtMaxOcRatio, BIOS_DEVICE_IGFX_FREQUENCY);

    //
    // Internal Graphics UNSLICE Freq
    //
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index, OcSetupData.GtusMaxOcRatio, BIOS_DEVICE_IGFX_UNSLICE_FREQUENCY);

    //
    // Core Voltage Mode
    //
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index, OcSetupData.CoreVoltageMode, BIOS_DEVICE_IA_CORE_VOLTAGE_MODE);

    //
    // ICC MAX
    //
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , OcSetupData.IccMax[0], BIOS_DEVICE_SA_CURRENT_LIMIT_MAX);
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , OcSetupData.IccMax[1], BIOS_DEVICE_IA_CURRENT_LIMIT_MAX);
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , OcSetupData.IccMax[2], BIOS_DEVICE_GTUS_CURRENT_LIMIT_MAX);
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , OcSetupData.IccMax[3], BIOS_DEVICE_GTS_CURRENT_LIMIT_MAX);
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , OcSetupData.IccMax[4], BIOS_DEVICE_RING_CURRENT_LIMIT_MAX);

    //
    // Core AVX Ratio
    //
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , OcSetupData.Avx2RatioOffset, BIOS_DEVICE_IA_AVX2_CORE_RATIO_OFFSET);
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , OcSetupData.Avx3RatioOffset, BIOS_DEVICE_IA_AVX3_CORE_RATIO_OFFSET);

    //
    // Core Voltage
    //
    if (OcSetupData.CoreVoltageMode == VOLTAGE_MODE_ADAPTIVE) {
      ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index, OcSetupData.CoreExtraTurboVoltage, BIOS_DEVICE_CPU_VOLTAGE);
    }
    else if (OcSetupData.CoreVoltageMode == VOLTAGE_MODE_OVERRIDE) {
      ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index, OcSetupData.CoreVoltageOverride, BIOS_DEVICE_CPU_VOLTAGE);
    }
    else {
      DEBUG ((DEBUG_INFO, "OC SMI: Core Voltage Mode invalid: %X\n", OcSetupData.CoreVoltageMode));
    }

    //
    // Core Voltage Offset
    //
    //
    // Need to translate to voltage offset representation for XTU
    //
    if (OcSetupData.CoreVoltageOffsetPrefix == 1) {
      //
      // Offset is negative, convert to XTU representation where -1000 to 0 is 0 to 1000
      //
      XtuCoreVoltageOffset = 1000 - OcSetupData.CoreVoltageOffset;
      ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , XtuCoreVoltageOffset, BIOS_DEVICE_IA_CORE_VOLTAGE_OFFSET);
    }
    else {
      //
      // Number is postive, convert to XTU representation where 1 to 1000 is 1001 to 2000
      //
      XtuCoreVoltageOffset = OcSetupData.CoreVoltageOffset + 1000;
      ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , XtuCoreVoltageOffset, BIOS_DEVICE_IA_CORE_VOLTAGE_OFFSET);
    }

    //
    // Turbo Boost Power Time Window
    //
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , OcSetupData.PowerLimit1Time, BIOS_DEVICE_TURBO_BOOST_POWER_TIME_WINDOWS);

    //
    // XMP Profile
    //
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , OcSetupData.SpdProfileSelected, BIOS_DEVICE_XMP_PROFILE);

    //
    // Memory Clock Multiplier
    //
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , OcSetupData.DdrRefClk, BIOS_DEVICE_MEMORY_CLOCK_FREQUENCY);

    //
    // Turbo Mode
    //
    if ( TurboModeSupported ) {
      ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , OcSetupData.TurboMode, BIOS_DEVICE_TURBO_MODE);

       if ( CoreRatioLimitAvailable ) {
         ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , OcSetupData.RatioLimit1, BIOS_DEVICE_1_CORE_RATIO_LIMIT);

         ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , OcSetupData.RatioLimit2, BIOS_DEVICE_2_CORE_RATIO_LIMIT);

         if ( mNumberOfActiveCores > 2 ) {
           ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , OcSetupData.RatioLimit3, BIOS_DEVICE_3_CORE_RATIO_LIMIT);

           ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , OcSetupData.RatioLimit4, BIOS_DEVICE_4_CORE_RATIO_LIMIT);

           if ( mNumberOfActiveCores > 4 ) {
             ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , OcSetupData.RatioLimit5, BIOS_DEVICE_5_CORE_RATIO_LIMIT);

             ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , OcSetupData.RatioLimit6, BIOS_DEVICE_6_CORE_RATIO_LIMIT);

             if ( mNumberOfActiveCores > 6 ) {
               ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , OcSetupData.RatioLimit7, BIOS_DEVICE_7_CORE_RATIO_LIMIT);

               ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , OcSetupData.RatioLimit8, BIOS_DEVICE_8_CORE_RATIO_LIMIT);
             }
           }
         }
       }

      if ( TurboTdpLimitProgrammable ) {
        DEBUG ((DEBUG_INFO, "OC SMI: TurboTdpLimitProgrammable, creating bios setting table\n"));

        ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , OcSetupData.TurboPowerLimitLock, BIOS_DEVICE_TURBO_POWER_LIMIT_LOCK);

        ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , OcSetupData.PowerLimit2, BIOS_DEVICE_SHORT_WINDOW_POWER_ENABLE);

        ADD_ENTRY_TO_BIOS_SETTING_TABLE_AUTOMATIC (BiosSettingEntries, Index , OcSetupData.PowerLimit2Power, BIOS_DEVICE_SHORT_WINDOW_TDP_LIMIT, OcSetupData.PowerLimit2Default);

        ADD_ENTRY_TO_BIOS_SETTING_TABLE_AUTOMATIC (BiosSettingEntries, Index , OcSetupData.PowerLimit1, BIOS_DEVICE_EXTENDED_TDP_LIMIT, OcSetupData.PowerLimit1Default);
      }
    }

    //
    // Ring Ratio
    //
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , OcSetupData.RingMaxOcRatio, BIOS_DEVICE_RING_RATIO);

    //
    // Overclocking Enable
    //

    //
    // XTU definition of OC Enable is inverted from BIOS defintion of OC Lock.
    // For Read commands, we need to populate this value correctly. Write command
    // is don't care since we will do the write handling further down in the function.
    //
    XtuOcEnable = (UINT8) ~OcSetupData.OverclockingLock & BIT0;
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , XtuOcEnable, BIOS_DEVICE_OC_ENABLE);

    //
    // GT Voltage Mode
    //
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , OcSetupData.GtVoltageMode, BIOS_DEVICE_IGFX_VOLTAGE_MODE);

    //
    // GT Voltage Override
    //
    if (OcSetupData.GtVoltageMode == VOLTAGE_MODE_ADAPTIVE) {
      ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , OcSetupData.GtExtraTurboVoltage, BIOS_DEVICE_IGFX_VOLTAGE_OVERRIDE);
    }
    else if (OcSetupData.GtVoltageMode == VOLTAGE_MODE_OVERRIDE) {
      ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , OcSetupData.GtVoltageOverride, BIOS_DEVICE_IGFX_VOLTAGE_OVERRIDE);
    }
    else {
      DEBUG ((DEBUG_INFO, "OC SMI: GT Voltage Mode invalid: %X\n", OcSetupData.GtVoltageMode));
    }

    //
    // GT Voltage Offset
    //

    //
    // Need to translate to voltage offset representation for XTU
    //
    if (OcSetupData.GtVoltageOffsetPrefix == 1) {
      //
      // Offset is negative, convert to XTU representation where -1000 to 0 is 0 to 1000
      //
      XtuGtVoltageOffset = 1000 - OcSetupData.GtVoltageOffset;
      ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , XtuGtVoltageOffset, BIOS_DEVICE_IGFX_VOLTAGE_OFFSET);
    }
    else {
      //
      // Number is postive, convert to XTU representation where 1 to 1000 is 1001 to 2000
      //
      XtuGtVoltageOffset = OcSetupData.GtVoltageOffset + 1000;
      ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , XtuGtVoltageOffset, BIOS_DEVICE_IGFX_VOLTAGE_OFFSET);
    }

    ///
    /// GT UNSLICE
    ///
    //
    // GT Voltage Mode
    //
    ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , OcSetupData.GtusVoltageMode, BIOS_DEVICE_IGFX_UNSLICE_VOLTAGE_MODE);

    //
    // GT Voltage Override
    //
    if (OcSetupData.GtusVoltageMode == VOLTAGE_MODE_ADAPTIVE) {
      ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , OcSetupData.GtusExtraTurboVoltage, BIOS_DEVICE_IGFX_UNSLICE_VOLTAGE_OVERRIDE);
    }
    else if (OcSetupData.GtusVoltageMode == VOLTAGE_MODE_OVERRIDE) {
      ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , OcSetupData.GtusVoltageOverride, BIOS_DEVICE_IGFX_UNSLICE_VOLTAGE_OVERRIDE);
    }
    else {
      DEBUG ((DEBUG_INFO, "OC SMI: GT UNSLICE Voltage Mode invalid: %X\n", OcSetupData.GtusVoltageMode));
    }

    //
    // GT Voltage Offset
    //

    //
    // Need to translate to voltage offset representation for XTU
    //
    if (OcSetupData.GtusVoltageOffsetPrefix == 1) {
      //
      // Offset is negative, convert to XTU representation where -1000 to 0 is 0 to 1000
      //
      XtuGtVoltageOffset = 1000 - OcSetupData.GtusVoltageOffset;
      ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , XtuGtVoltageOffset, BIOS_DEVICE_IGFX_UNSLICE_VOLTAGE_OFFSET);
    }
    else {
      //
      // Number is postive, convert to XTU representation where 1 to 1000 is 1001 to 2000
      //
      XtuGtVoltageOffset = OcSetupData.GtusVoltageOffset + 1000;
      ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , XtuGtVoltageOffset, BIOS_DEVICE_IGFX_UNSLICE_VOLTAGE_OFFSET);
    }

    //
    // SA Voltage Offset
    //

    //
    // Need to translate to voltage offset representation for XTU
    //
    if (OcSetupData.UncoreVoltageOffsetPrefix == 1) {
      //
      // Offset is negative, convert to XTU representation where -1000 to 0 is 0 to 1000
      //
      XtuUncoreVoltageOffset = 1000 - OcSetupData.UncoreVoltageOffset;
      ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , XtuUncoreVoltageOffset, BIOS_DEVICE_SA_VOLTAGE_OFFSET);
    }
    else {
      //
      // Number is postive, convert to XTU representation where 1 to 1000 is 1001 to 2000
      //
      XtuUncoreVoltageOffset = OcSetupData.UncoreVoltageOffset + 1000;
      ADD_ENTRY_TO_BIOS_SETTING_TABLE (BiosSettingEntries, Index , XtuUncoreVoltageOffset, BIOS_DEVICE_SA_VOLTAGE_OFFSET);
    }

    DEBUG ((DEBUG_INFO, "OC SMI: BIOS Settings Index = %X\n", Index));
  }

  //
  // Write BIOS settings data from MemoryDataLocation to BIOS Setup data
  //
  if (ReadWrite == OVERCLOCK_SMI_WRITE_COMMAND) {
    OcSetupData.OverclockingSupport = ENABLE_SUPPRORT;

    Count = MemoryDataLocation->Count;

    for ( Index = 0; Index < Count; Index++ ) {
      BiosSettingValue = BiosSettingEntries[Index].SettingValue;

      switch ( BiosSettingEntries[Index].BiosImplementationType ) {

        case BIOS_DEVICE_FLEX_RATIO:
           if (OcSetupData.CpuRatio != (UINT8) BiosSettingValue) {
             //
             // Enable Flex Overclock Support, if Non Turbo Flex Ratio input parameters are
             // changed from Setup data.
             //
             OcSetupData.CpuRatioOverride = ENABLE_SUPPRORT;
             OcSetupData.CpuRatio  = (UINT8) BiosSettingValue;
           }
           break;

        case BIOS_DEVICE_HOST_CLK_FREQ:
           if (OcSetupData.BclkFrequency != (UINT32) BiosSettingValue) {
             OcSetupData.BclkFrequency  = (UINT32) BiosSettingValue;
             OcSetupData.BclkOverride   = 1;
           }
           break;

        case BIOS_DEVICE_tCL:
           if (OcSetupData.tCL != (UINT8) BiosSettingValue) {
             OcSetupData.tCL = (UINT8) BiosSettingValue;
             OcSetupData.SpdProfileSelected = SPD_PROFILE_CUSTOM;
           }
           break;

        case BIOS_DEVICE_tRCD_tRP:
           if (OcSetupData.tRCDtRP != (UINT8) BiosSettingValue) {
             OcSetupData.tRCDtRP = (UINT8) BiosSettingValue;
             OcSetupData.SpdProfileSelected = SPD_PROFILE_CUSTOM;
           }
           break;

        case BIOS_DEVICE_tRAS:
           if (OcSetupData.tRAS != (UINT16) BiosSettingValue) {
             OcSetupData.tRAS  = (UINT16) BiosSettingValue;
             OcSetupData.SpdProfileSelected = SPD_PROFILE_CUSTOM;
           }
           break;

        case BIOS_DEVICE_tWR:
           if (BiosSettingValue == AUTOMATIC_MODE) {
             OcSetupData.tWR = OcSetupData.tWRDefault;
           } else if (OcSetupData.tWR != (UINT8) BiosSettingValue) {
             OcSetupData.tWR = (UINT8) BiosSettingValue;
             OcSetupData.SpdProfileSelected = SPD_PROFILE_CUSTOM;
           }
           break;

        case BIOS_DEVICE_tRFC:
           if (OcSetupData.tRFC != (UINT16) BiosSettingValue) {
             OcSetupData.tRFC = (UINT16) BiosSettingValue;
             OcSetupData.SpdProfileSelected = SPD_PROFILE_CUSTOM;
           }
           break;

        case BIOS_DEVICE_tRRD:
           if (OcSetupData.tRRD != (UINT8) BiosSettingValue) {
             OcSetupData.tRRD = (UINT8) BiosSettingValue;
             OcSetupData.SpdProfileSelected = SPD_PROFILE_CUSTOM;
           }
           break;

        case BIOS_DEVICE_tWTR:
           if (OcSetupData.tWTR != (UINT8) BiosSettingValue) {
             OcSetupData.tWTR = (UINT8) BiosSettingValue;
             OcSetupData.SpdProfileSelected = SPD_PROFILE_CUSTOM;
           }
           break;

        case BIOS_DEVICE_tRTP:
           if (OcSetupData.tRTP != (UINT8) BiosSettingValue) {
             OcSetupData.tRTP = (UINT8) BiosSettingValue;
             OcSetupData.SpdProfileSelected = SPD_PROFILE_CUSTOM;
           }
           break;

        case BIOS_DEVICE_tFAW:
           if (OcSetupData.tFAW != (UINT16) BiosSettingValue) {
             OcSetupData.tFAW  = (UINT16) BiosSettingValue;
             OcSetupData.SpdProfileSelected = SPD_PROFILE_CUSTOM;
           }
           break;

        case BIOS_DEVICE_SYSTEM_CMD_RATE:
           if (BiosSettingValue == AUTOMATIC_MODE) {
             OcSetupData.NModeSupport = 0;
           } else if (OcSetupData.NModeSupport != (UINT8) BiosSettingValue) {
             OcSetupData.NModeSupport = (UINT8) BiosSettingValue;
             OcSetupData.SpdProfileSelected = SPD_PROFILE_CUSTOM;
           }
           break;

        case BIOS_DEVICE_MEMORY_VOLTAGE:
           if (OcSetupData.MemoryVoltage != (UINT16) BiosSettingValue) {
             OcSetupData.MemoryVoltage = (UINT16) BiosSettingValue;
           }
           break;

        case BIOS_DEVICE_DDR_MULTIPLIER:
           if (BiosSettingValue == AUTOMATIC_MODE) {
             OcSetupData.DdrRatio = DISABLE_SUPPRORT;
           } else if (OcSetupData.DdrRatio != (UINT8) BiosSettingValue) {
             OcSetupData.DdrRatio = (UINT8) BiosSettingValue;
           }
           break;

        case BIOS_DEVICE_TURBO_MODE:
           if (OcSetupData.TurboMode != (UINT8) BiosSettingValue ) {
             OcSetupData.TurboMode = (UINT8)BiosSettingValue;
           }
           break;

        case BIOS_DEVICE_EIST:
           if (OcSetupData.EnableGv != (UINT8) BiosSettingValue ) {
             OcSetupData.EnableGv = (UINT8)BiosSettingValue;
           }
           break;

        case BIOS_DEVICE_1_CORE_RATIO_LIMIT:
           if (OcSetupData.RatioLimit1  != (UINT8) BiosSettingValue) {
             OcSetupData.RatioLimit1     = (UINT8) BiosSettingValue;
             OcSetupData.OverclockingSupport = 1;
             // We need to sync the 1 Core ratio limit with the OC mailbox
             // core ratio limit since the mailbox interface will also limit
             // the core CPU frequency. Without this sync, the core ratios
             // may not achieve the desired frequency.
             OcSetupData.CoreMaxOcRatio  = (UINT8) BiosSettingValue;
           }
           break;

        case BIOS_DEVICE_2_CORE_RATIO_LIMIT:
           if (OcSetupData.RatioLimit2  != (UINT8) BiosSettingValue) {
             OcSetupData.RatioLimit2 = (UINT8) BiosSettingValue;
             OcSetupData.OverclockingSupport = 1;
           }
           break;

        case BIOS_DEVICE_3_CORE_RATIO_LIMIT:
           if (OcSetupData.RatioLimit3 != (UINT8) BiosSettingValue) {
             OcSetupData.RatioLimit3 = (UINT8) BiosSettingValue;
             OcSetupData.OverclockingSupport = 1;
           }
           break;

        case BIOS_DEVICE_4_CORE_RATIO_LIMIT:
           if (OcSetupData.RatioLimit4  != (UINT8) BiosSettingValue) {
             OcSetupData.RatioLimit4 = (UINT8) BiosSettingValue;
             OcSetupData.OverclockingSupport = 1;
           }
           break;

        case BIOS_DEVICE_5_CORE_RATIO_LIMIT:
           if (OcSetupData.RatioLimit5  != (UINT8) BiosSettingValue) {
             OcSetupData.RatioLimit5 = (UINT8) BiosSettingValue;
             OcSetupData.OverclockingSupport = 1;
           }
           break;

        case BIOS_DEVICE_6_CORE_RATIO_LIMIT:
           if (OcSetupData.RatioLimit6 != (UINT8) BiosSettingValue) {
             OcSetupData.RatioLimit6 = (UINT8) BiosSettingValue;
             OcSetupData.OverclockingSupport = 1;
           }
           break;

        case BIOS_DEVICE_7_CORE_RATIO_LIMIT:
           if (OcSetupData.RatioLimit7  != (UINT8) BiosSettingValue) {
             OcSetupData.RatioLimit7 = (UINT8) BiosSettingValue;
             OcSetupData.OverclockingSupport = 1;
           }
           break;

        case BIOS_DEVICE_8_CORE_RATIO_LIMIT:
           if (OcSetupData.RatioLimit8  != (UINT8) BiosSettingValue) {
             OcSetupData.RatioLimit8 = (UINT8) BiosSettingValue;
             OcSetupData.OverclockingSupport = 1;
           }
           break;

        case BIOS_DEVICE_SHORT_WINDOW_POWER_ENABLE:
           if (OcSetupData.PowerLimit2 != (UINT8) BiosSettingValue) {
             OcSetupData.PowerLimit2 = (UINT8) BiosSettingValue;
           }
           break;

        case BIOS_DEVICE_SHORT_WINDOW_TDP_LIMIT:
           //
           //  XTU has power limits defined as Watts, whereas BIOS stores as milliwatts.
           //  Need to convert XTU value to milliwatts before updating SetupSa
           //
           if (BiosSettingValue == AUTOMATIC_MODE) {
             OcSetupData.PowerLimit2Power = OcSetupData.PowerLimit2Default;
           } else if (OcSetupData.PowerLimit2Power != ((UINT32) BiosSettingValue)) {
           OcSetupData.PowerLimit2Power  = ((UINT32) BiosSettingValue);
           }
           break;

        case BIOS_DEVICE_EXTENDED_TDP_LIMIT:
           //
           //  XTU has power limits defined as Watts, whereas BIOS stores as milliwatts.
           //  Need to convert XTU value to milliwatts before updating SetupSa
           //
           if (BiosSettingValue == AUTOMATIC_MODE) {
             OcSetupData.LongDurationPwrLimitOverride = 0;
           } else if (OcSetupData.PowerLimit1 != ((UINT32) BiosSettingValue)) {
             OcSetupData.PowerLimit1 = ((UINT32) BiosSettingValue);
             OcSetupData.LongDurationPwrLimitOverride = 1;
           }
           break;

        case BIOS_DEVICE_TURBO_POWER_LIMIT_LOCK:
           if (BiosSettingValue == AUTOMATIC_MODE) {
             OcSetupData.TurboPowerLimitLock = DISABLE_SUPPRORT;
           } else if (OcSetupData.TurboPowerLimitLock != (UINT8) BiosSettingValue) {
             OcSetupData.TurboPowerLimitLock = (UINT8) BiosSettingValue;
           }
           break;

        case BIOS_DEVICE_OC_ENABLE:
           //
           // OC Enable in the XTU Spec, but OC Lock in BIOS, so BiosSettingValue is inverted
           // BiosSettingValue = 0 means OC disabled, so OC Lock = 1
           // BiosSettingValue = 1 means OC enabled, so OC Lock = 0
           //
           if (OcSetupData.OverclockingLock != (UINT8) (~BiosSettingValue)) {
             OcSetupData.OverclockingLock = (UINT8) (~BiosSettingValue & BIT0);
             OcSetupData.OverclockingSupport = 1;
           }
           break;

        case BIOS_DEVICE_IGFX_FREQUENCY:
           if (OcSetupData.GtMaxOcRatio != (UINT8) BiosSettingValue) {
             OcSetupData.GtMaxOcRatio = (UINT8) BiosSettingValue;
           }
           break;

        case BIOS_DEVICE_IGFX_UNSLICE_FREQUENCY:
           if (OcSetupData.GtusMaxOcRatio != (UINT8) BiosSettingValue) {
             OcSetupData.GtusMaxOcRatio = (UINT8) BiosSettingValue;
           }
           break;

        case BIOS_DEVICE_IA_CORE_VOLTAGE_MODE:
           if (OcSetupData.CoreVoltageMode != (UINT8) BiosSettingValue) {
             OcSetupData.CoreVoltageMode = (UINT8) BiosSettingValue;
           }
           break;

        case BIOS_DEVICE_CPU_VOLTAGE:
           //
           // Only 1 voltage target control ID. Voltage Mode will determine which value is applied to FIVR.
           // Need to keep both voltage targets in sync.
           //
           OcSetupData.CoreVoltageOverride = (UINT16)BiosSettingValue;
           OcSetupData.CoreExtraTurboVoltage = (UINT16)BiosSettingValue;
           break;

        case BIOS_DEVICE_IA_CORE_VOLTAGE_OFFSET:
           if (OcSetupData.CoreVoltageOffset != (UINT16) BiosSettingValue) {
             //
             // Need to determine if the requested number is negative
             // Voltage offset has a range of -1000 to 1000.
             // XTU passes in 0 to 2000 where 0 to 1000 maps to -1000 to 0
             // and 1001 to 2000 maps to 1 to 1000.
             //
             if (BiosSettingValue <= 1000) {
               //
               // This is a negative offset
               //
               OcSetupData.CoreVoltageOffset = 1000 - (UINT16)BiosSettingValue;
               OcSetupData.CoreVoltageOffsetPrefix = 1;
             }
             else if ((BiosSettingValue > 1000) && (BiosSettingValue <= 2000)) {
               //
               // This is a positive offset, and within range
               //
               OcSetupData.CoreVoltageOffset = (UINT16)BiosSettingValue - 1000;
               OcSetupData.CoreVoltageOffsetPrefix = 0;
             }
           }
           break;

        case BIOS_DEVICE_TURBO_BOOST_POWER_TIME_WINDOWS:
           if (OcSetupData.PowerLimit1Time != (UINT8) BiosSettingValue) {
             OcSetupData.PowerLimit1Time = (UINT8) BiosSettingValue;
           }
           break;

        //
        // ICC MAX
        //
        case BIOS_DEVICE_SA_CURRENT_LIMIT_MAX:
           if (OcSetupData.IccMax[0]!= (UINT8) BiosSettingValue) {
             OcSetupData.IccMax[0] = (UINT8) BiosSettingValue;
           }
           break;

        case BIOS_DEVICE_IA_CURRENT_LIMIT_MAX:
           if (OcSetupData.IccMax[1]!= (UINT8) BiosSettingValue) {
             OcSetupData.IccMax[1] = (UINT8) BiosSettingValue;
           }
           break;

        case BIOS_DEVICE_GTUS_CURRENT_LIMIT_MAX:
           if (OcSetupData.IccMax[2]!= (UINT8) BiosSettingValue) {
             OcSetupData.IccMax[2] = (UINT8) BiosSettingValue;
           }
           break;

        case BIOS_DEVICE_GTS_CURRENT_LIMIT_MAX:
           if (OcSetupData.IccMax[3]!= (UINT8) BiosSettingValue) {
             OcSetupData.IccMax[3] = (UINT8) BiosSettingValue;
           }
           break;

        case BIOS_DEVICE_RING_CURRENT_LIMIT_MAX:
           if (OcSetupData.IccMax[4]!= (UINT8) BiosSettingValue) {
             OcSetupData.IccMax[4] = (UINT8) BiosSettingValue;
           }
           break;

        //
        // Core AVX Ratio
        //
        case BIOS_DEVICE_IA_AVX2_CORE_RATIO_OFFSET:
           if (OcSetupData.Avx2RatioOffset!= (UINT8) BiosSettingValue) {
             OcSetupData.Avx2RatioOffset = (UINT8) BiosSettingValue;
           }
           break;

        case BIOS_DEVICE_IA_AVX3_CORE_RATIO_OFFSET:
           if (OcSetupData.Avx3RatioOffset!= (UINT8) BiosSettingValue) {
             OcSetupData.Avx3RatioOffset = (UINT8) BiosSettingValue;
           }
           break;

        case BIOS_DEVICE_XMP_PROFILE:
           if (OcSetupData.SpdProfileSelected != (UINT8) BiosSettingValue) {
             OcSetupData.SpdProfileSelected = (UINT8) BiosSettingValue;
           }
           break;

        case BIOS_DEVICE_MEMORY_CLOCK_FREQUENCY:
           if (OcSetupData.DdrRefClk != (UINT8) BiosSettingValue) {
             OcSetupData.DdrRefClk = (UINT8) BiosSettingValue;
           }
           break;

        case BIOS_DEVICE_RING_RATIO:
           if (OcSetupData.RingMaxOcRatio != (UINT8) BiosSettingValue) {
             OcSetupData.RingMaxOcRatio = (UINT8) BiosSettingValue;
             OcSetupData.OverclockingSupport = 1;
           }
           break;

        case BIOS_DEVICE_IGFX_VOLTAGE_MODE:
           if (OcSetupData.GtVoltageMode != (UINT8) BiosSettingValue) {
             OcSetupData.GtVoltageMode = (UINT8) BiosSettingValue;
           }
           break;

        case BIOS_DEVICE_IGFX_VOLTAGE_OVERRIDE:
           //
           // Only 1 voltage target control ID. Voltage Mode will determine which value is applied to FIVR.
           // Need to keep both voltage targets in sync.
           //
           OcSetupData.GtVoltageOverride = (UINT16)BiosSettingValue;
           OcSetupData.GtExtraTurboVoltage = (UINT16)BiosSettingValue;
           break;

        case BIOS_DEVICE_IGFX_VOLTAGE_OFFSET:
           if (OcSetupData.GtVoltageOffset != (UINT16) BiosSettingValue) {
             //
             // Need to determine if the requested number is negative
             // Voltage offset has a range of -1000 to 1000.
             // XTU passes in 0 to 2000 where 0 to 1000 maps to -1000 to 0
             // and 1001 to 2000 maps to 1 to 1000.
             //
             if (BiosSettingValue <= 1000) {
               //
               // This is a negative offset
               //
               OcSetupData.GtVoltageOffset = 1000 - (UINT16)BiosSettingValue;
               OcSetupData.GtVoltageOffsetPrefix = 1;
             }
             else if ((BiosSettingValue > 1000) && (BiosSettingValue <= 2000)) {
               //
               // This is a positive offset, and within range
               //
               OcSetupData.GtVoltageOffset = (UINT16)BiosSettingValue - 1000;
               OcSetupData.GtVoltageOffsetPrefix = 0;
             }
           }
           break;

        case BIOS_DEVICE_IGFX_UNSLICE_VOLTAGE_MODE:
           if (OcSetupData.GtVoltageMode != (UINT8) BiosSettingValue) {
             OcSetupData.GtVoltageMode = (UINT8) BiosSettingValue;
           }
           break;

        case BIOS_DEVICE_IGFX_UNSLICE_VOLTAGE_OVERRIDE:
           //
           // Only 1 voltage target control ID. Voltage Mode will determine which value is applied to FIVR.
           // Need to keep both voltage targets in sync.
           //
           OcSetupData.GtVoltageOverride = (UINT16)BiosSettingValue;
           OcSetupData.GtExtraTurboVoltage = (UINT16)BiosSettingValue;
           break;

        case BIOS_DEVICE_IGFX_UNSLICE_VOLTAGE_OFFSET:
           if (OcSetupData.GtVoltageOffset != (UINT16) BiosSettingValue) {
             //
             // Need to determine if the requested number is negative
             // Voltage offset has a range of -1000 to 1000.
             // XTU passes in 0 to 2000 where 0 to 1000 maps to -1000 to 0
             // and 1001 to 2000 maps to 1 to 1000.
             //
             if (BiosSettingValue <= 1000) {
               //
               // This is a negative offset
               //
               OcSetupData.GtVoltageOffset = 1000 - (UINT16)BiosSettingValue;
               OcSetupData.GtVoltageOffsetPrefix = 1;
             }
             else if ((BiosSettingValue > 1000) && (BiosSettingValue <= 2000)) {
               //
               // This is a positive offset, and within range
               //
               OcSetupData.GtVoltageOffset = (UINT16)BiosSettingValue - 1000;
               OcSetupData.GtVoltageOffsetPrefix = 0;
             }
           }
           break;

        case BIOS_DEVICE_SA_VOLTAGE_OFFSET:
           if (OcSetupData.UncoreVoltageOffset != (UINT16) BiosSettingValue) {
             //
             // Need to determine if the requested number is negative
             // Voltage offset has a range of -1000 to 1000.
             // XTU passes in 0 to 2000 where 0 to 1000 maps to -1000 to 0
             // and 1001 to 2000 maps to 1 to 1000.
             //
             if (BiosSettingValue <= 1000) {
               //
               // This is a negative offset
               //
               OcSetupData.UncoreVoltageOffset = 1000 - (UINT16)BiosSettingValue;
               OcSetupData.UncoreVoltageOffsetPrefix = 1;
             }
             else if ((BiosSettingValue > 1000) && (BiosSettingValue <= 2000)) {
               //
               // This is a positive offset, and within range
               //
               OcSetupData.UncoreVoltageOffset = (UINT16)BiosSettingValue - 1000;
               OcSetupData.UncoreVoltageOffsetPrefix = 0;
             }
           }
           break;
      }
    }

    OcSetupData.OcInterfaceRtUpdated = 1;
    Status = mSmmVariable->SmmSetVariable (
                                L"OcSetup",
                                &gOcSetupVariableGuid,
                                OcVariableAttributes,
                                OcVariableSize,
                                &OcSetupData
                                );

    if(EFI_ERROR (Status)){
      (pCpuSaveState->x64)._RBX = (UINT32)0x0000FFFF;  // Internal BIOS Error
      (pCpuSaveState->x64)._RCX = (UINT32)Status;      // Error Code status
    }
    ASSERT_EFI_ERROR (Status);
  }

  if (ReadWrite == OVERCLOCK_SMI_WDT_CONFIRM_REQUEST_COMMAND) {
    OcSetupData.WDTSupportforNextOSBoot = 1;
    OcSetupData.OverclockingSupport     = ENABLE_SUPPRORT;

    switch (TimerValue) {
      case MAX_TIME_OUT:
        OcSetupData.TimeforNextOSBoot = 0xFFFF;
        break;

      case SUCCESSFUL_BOOT:
        OcSetupData.WDTSupportforNextOSBoot = 0;
        OcSetupData.TimeforNextOSBoot = 0;
        OcSetupData.PlatformUnstable = 0;
        break;

      default:
        OcSetupData.TimeforNextOSBoot = (UINT16)TimerValue;
        break;
    }
    OcSetupData.OcInterfaceRtUpdated = 1;
    Status = mSmmVariable->SmmSetVariable (
                                L"OcSetup",
                                &gOcSetupVariableGuid,
                                OcVariableAttributes,
                                OcVariableSize,
                                &OcSetupData
                                );
    if (EFI_ERROR (Status)) {
      (pCpuSaveState->x64)._RBX = (UINT32)0x0000FFFF;  //Internal BIOS Error
      (pCpuSaveState->x64)._RCX = (UINT32)Status;  //Error Code status
    }
    ASSERT_EFI_ERROR (Status);
  }

  return Status;
}

/**
  This function is called from SMM during SMM registration.

  @param[in] ImageHandle     Image handle of this driver.
  @param[in] SystemTable     Global system service table.

**/
EFI_STATUS
InSmmFunction (
  IN  EFI_HANDLE        ImageHandle,
  IN  EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_SMM_SW_DISPATCH2_PROTOCOL *pSwDispatch;
  EFI_SMM_SW_REGISTER_CONTEXT   SwContext;
  EFI_HANDLE                    Handle;
  EFI_STATUS                    Status;

  Status = gSmst->SmmLocateProtocol (&gEfiSmmSwDispatch2ProtocolGuid, NULL, (VOID**)&pSwDispatch);
  ASSERT_EFI_ERROR (Status);

  //
  // Register SMIBiosSettings handler for SW SMI 0x72
  //
  SwContext.SwSmiInputValue = PcdGet8 (PcdOverClockingInterfaceSwSmi);
  Status = pSwDispatch->Register (pSwDispatch, SMIFlashSMIHandler, &SwContext, &Handle);
  ASSERT_EFI_ERROR (Status);

  Status = gSmst->SmmLocateProtocol (&gEfiSmmVariableProtocolGuid, NULL, (VOID**)&mSmmVariable);
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/**
  This is the entrypoint of the SMIBiosSettings driver

  @param[in] ImageHandle     Image handle of this driver.
  @param[in] SystemTable     Global system service table.

**/
EFI_STATUS
EFIAPI
OverClockSmiHandlerEntryPoint (
  IN  EFI_HANDLE       ImageHandle,
  IN  EFI_SYSTEM_TABLE *SystemTable
  )
{
  UINT32 Data32;

  //
  // Read MSR for Active Core and Thread Count.
  //
  Data32 = (UINT32) AsmReadMsr64 (MSR_CORE_THREAD_COUNT);
  mNumberOfActiveCores  = (UINT16) ((Data32 >> 16) & 0xFFFF);

  return InSmmFunction (ImageHandle, SystemTable);
}
