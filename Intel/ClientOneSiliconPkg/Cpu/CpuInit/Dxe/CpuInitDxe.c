/** @file
  Cpu driver, which initializes CPU and implements CPU Architecture
  Protocol as defined in Framework specification.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification
**/

#include <Library/BaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiLib.h>
#include <Library/HobLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Protocol/MpService.h>
#include "CpuInitDxe.h"
#include "BiosGuard.h"
#include <Library/BootGuardLib.h>
#include <Library/SoftwareGuardLib.h>
#include <Library/CpuCommonLib.h>
#include <PowerMgmtNvsStruct.h>
#include <Protocol/DxeSmmReadyToLock.h>

//
// Private GUID for BIOS Guard initializes
//
extern EFI_GUID gBiosGuardHobGuid;

///
/// The Cpu Init Data Hob
///
GLOBAL_REMOVE_IF_UNREFERENCED CPU_INIT_DATA_HOB                *mCpuInitDataHob   = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED CPU_CONFIG_DATA                  *mCpuConfigData    = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED FVID_TABLE                       *mFvidTable        = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED CPU_INFO_PROTOCOL                *mCpuInfo;
GLOBAL_REMOVE_IF_UNREFERENCED UINTN                            mCommonFeatures;
GLOBAL_REMOVE_IF_UNREFERENCED UINTN                            mSiliconFeatures;

/**
  Set all APs to deepest C-State before ready to boot for better power saving
**/
VOID
EFIAPI
RequestDeepestCStateForAps (
  IN  EFI_EVENT Event,
  IN  VOID      *Context
)
{
  UINT8                                         MaxCstate;
  MSR_BROADWELL_PKG_CST_CONFIG_CONTROL_REGISTER Msr;
  UINT32                                        SubStates;
  EFI_CPUID_REGISTER                            MwaitInfo;

  ///
  /// APs should be at deepest C-State before ready to boot for better power saving,
  /// if boot to DOS/EFI_SHARE or any operating system that running only single thread.
  ///
  /// BIOS should use CPUID.(EAX=5) Monitor/Mwait Leaf and also check MSR E2h[3:0] Package C-state limit to determine
  /// if the processor supports MONITOR/MWAIT extensions for various C-states and sub C-states.
  ///
  Msr.Uint64 = AsmReadMsr64 (MSR_BROADWELL_PKG_CST_CONFIG_CONTROL);
  AsmCpuid (5, &MwaitInfo.RegEax, &MwaitInfo.RegEbx, &MwaitInfo.RegEcx, &MwaitInfo.RegEdx);
  MaxCstate = 0;
  SubStates = 0;
  if (MwaitInfo.RegEcx & BIT0) {
    switch (Msr.Bits.Limit) {
      case V_CSTATE_LIMIT_C10:
        SubStates = (MwaitInfo.RegEdx >> 28) & 0xf;
        MaxCstate = 0x60;
        break;

      case V_CSTATE_LIMIT_C9:
        SubStates = (MwaitInfo.RegEdx >> 24) & 0xf;
        MaxCstate = 0x50;
        break;

      case V_CSTATE_LIMIT_C8:
        SubStates = (MwaitInfo.RegEdx >> 20) & 0xf;
        MaxCstate = 0x40;
        break;

      case V_CSTATE_LIMIT_C7S:
        SubStates = (MwaitInfo.RegEdx >> 16) & 0xf;
        MaxCstate = 0x30;
        break;

      case V_CSTATE_LIMIT_C7:
        SubStates = (MwaitInfo.RegEdx >> 16) & 0xf;
        MaxCstate = 0x30;
        break;

      case V_CSTATE_LIMIT_C6:
        SubStates = (MwaitInfo.RegEdx >> 12) & 0xf;
        MaxCstate = 0x20;
        break;

      case V_CSTATE_LIMIT_C3:
        SubStates = (MwaitInfo.RegEdx >> 8) & 0xf;
        MaxCstate = 0x10;
        break;

      case V_CSTATE_LIMIT_C1:
        SubStates = (MwaitInfo.RegEdx >> 4) & 0xf;
        MaxCstate = 0x00;
        break;

      default:
        break;
    }
  }

  ///
  /// If Substates opcode is greater than 1 than add that info to the MaxCstate Opcode.
  ///
  if (SubStates > 1) {
    MaxCstate |= (UINT8) SubStates - 1;
  }

  PcdSet8S (PcdCpuApTargetCstate, MaxCstate);
}

/**
  CpuInitOnReadyToLockCallback - Callback will be triggered when OnReadyToLock event is signaled
   - Create SMBIOS Table type - FviSmbiosType
   - Drop into SMM to register IOTRAP for BIOS Guard tools interface

  @param[in] Event     - A pointer to the Event that triggered the callback.
  @param[in] Context   - A pointer to private data registered with the callback function.
**/
VOID
EFIAPI
CpuInitOnReadyToLockCallback (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  BIOSGUARD_HOB        *BiosGuardHobPtr;
  UINT64               MsrValue;
  EFI_STATUS           Status;
  VOID                *DxeSmmReadyToLock;

  ///
  /// Account for the initial call from EfiCreateProtocolNotifyEvent
  ///
  Status = gBS->LocateProtocol (
                  &gEfiDxeSmmReadyToLockProtocolGuid,
                  NULL,
                  &DxeSmmReadyToLock
                  );
  if (EFI_ERROR (Status)) {
    return;
  }

  ///
  /// Close the event
  ///
  gBS->CloseEvent (Event);

  ///
  /// Enable BIOS Guard Flash Wear-Out Protection mitigation.
  ///
  BiosGuardHobPtr = GetFirstGuidHob (&gBiosGuardHobGuid);
  if (BiosGuardHobPtr != NULL) {
    if (BiosGuardHobPtr->Bgpdt.BiosGuardAttr & EnumFlashwearoutProtection) {
      MsrValue = AsmReadMsr64 (MSR_PLAT_BIOS_INFO_FLAGS);
      MsrValue |= BIT0;
      AsmWriteMsr64 (MSR_PLAT_BIOS_INFO_FLAGS, MsrValue);
    }
  }

  return;
}

/**
  Initialize the state information for the CPU Architectural Protocol

  @param[in] ImageHandle - Image handle of the loaded driver
  @param[in] SystemTable - Pointer to the System Table

  @retval EFI_SUCCESS           - Thread was successfully created
  @retval EFI_OUT_OF_RESOURCES  - Can not allocate protocol data structure
  @retval EFI_DEVICE_ERROR      - Can not create the thread
  @retval EFI_NOT_FOUND         - Can not locate CPU Data HOB
**/
EFI_STATUS
EFIAPI
InitializeCpu (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS        Status;
  VOID              *Hob;
  EFI_EVENT         LegacyBootEvent;
  EFI_EVENT         ExitBootServicesEvent;
  VOID              *Registration;
  BOOLEAN           HdcSupported;

  ///
  /// Get CPU Init Data Hob
  ///
  Hob = GetFirstGuidHob (&gCpuInitDataHobGuid);
  if (Hob == NULL) {
    DEBUG ((DEBUG_ERROR, "CPU Data HOB not available\n"));
    return EFI_NOT_FOUND;
  }

  HdcSupported = (AsmReadMsr64(MSR_MISC_PWR_MGMT) & B_MSR_MISC_PWR_MGMT_ENABLE_SDC_MASK) != 0;
  mCpuInitDataHob    = (CPU_INIT_DATA_HOB *) ((UINTN) Hob + sizeof (EFI_HOB_GUID_TYPE));
  mCpuConfigData     = (CPU_CONFIG_DATA *)   (UINTN) mCpuInitDataHob->CpuConfigData;
  mSiliconFeatures   = ((HdcSupported) << N_HDC_SUPPORT) & B_HDC_SUPPORT;
  mFvidTable         = (FVID_TABLE *) (UINTN) mCpuInitDataHob->FvidTable;

  ///
  /// Initialize DxeCpuInfo protocol instance and gather CPU information
  ///
  Status = InitCpuInfo ();
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to initialize DxeCpuInfo\n"));
  }

  ///
  /// Create an OnReadyToLock protocol callback event for BIOS Guard.
  /// This function causes CpuInitOnReadyToLockCallback() to be executed,
  /// Ensure CpuInitOnReadyToLockCallback() accounts for this initial call.
  ///
  EfiCreateProtocolNotifyEvent (
    &gEfiDxeSmmReadyToLockProtocolGuid,
    TPL_CALLBACK,
    CpuInitOnReadyToLockCallback,
    NULL,
    &Registration
    );

  CpuAcpiInit (ImageHandle);
  BiosGuardAcpiInit (ImageHandle);
  UpdateSgxNvs ();

  //
  // Set PCD to request deepest C-states in monitor/mwait right before boot.
  // Use TPL_NOTIFY signal to trigger callback before TPL_CALLBACK signal used by
  // UefiCpuPkg to put APs in deep sleep before giving control to OS.
  //

  Status = gBS->CreateEvent (
                  EVT_SIGNAL_EXIT_BOOT_SERVICES,
                  TPL_NOTIFY,
                  RequestDeepestCStateForAps,
                  NULL,
                  &ExitBootServicesEvent
                  );
  ASSERT_EFI_ERROR (Status);

  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  RequestDeepestCStateForAps,
                  NULL,
                  &gEfiEventLegacyBootGuid,
                  &LegacyBootEvent
                  );
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/**
  Initialize CPU info.

  @retval EFI_SUCCESS          - Successfully prepared.
  @retval EFI_OUT_OF_RESOURCES - Not enough memory to complete the function.
**/
EFI_STATUS
InitCpuInfo (
  VOID
  )
{
  CACHE_DESCRIPTOR_INFO  *CacheInfo;
  CHAR8                  *BrandString;
  EFI_CPUID_REGISTER     CpuidRegs;
  CPUID_CACHE_PARAMS_EAX CacheEax;
  CPUID_CACHE_PARAMS_EBX CacheEbx;
  UINT32                 CacheEcx;
  UINT32                 CpuSignature;
  UINT8                  CacheInfoCount;
  UINT16                 CachePartitions;
  UINT16                 CacheLineSize;
  UINT32                 CacheNumberofSets;
  UINT8                  ThreadsPerCore;
  UINT64                 MsrData;
  UINT8                  Index;
  EFI_HANDLE             Handle;
  UINT16                 EnabledThreadsPerCore;
  UINT16                 EnabledCoresPerDie;

  Handle                = NULL;

  ///
  /// Install CPU info protocol
  ///
  mCpuInfo                             = AllocateZeroPool (sizeof (CPU_INFO_PROTOCOL));
  if (mCpuInfo == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  mCpuInfo->Revision                   = CPU_INFO_PROTOCOL_REVISION;
  mCpuInfo->CpuCommonFeatures          = mCommonFeatures | (mSiliconFeatures << 10);
  mCpuInfo->CpuInfo                    = AllocateZeroPool (sizeof (CPU_INFO));
  if (mCpuInfo->CpuInfo == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  mCpuInfo->CpuInfo->BrandString       = AllocateZeroPool (49 * sizeof (CHAR8));
  if (mCpuInfo->CpuInfo->BrandString == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  mCpuInfo->SmramCpuInfo               = AllocateZeroPool (sizeof (SMRAM_CPU_INFO));
  if (mCpuInfo->SmramCpuInfo == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  mCpuInfo->SgxInfo                    = AllocateZeroPool (sizeof (SGX_INFO));
  if (mCpuInfo->SgxInfo == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  MsrData = AsmReadMsr64 (MSR_BIOS_SE_SVN);
  mCpuInfo->SgxInfo->SgxSinitNvsData = MsrData;

  ///
  /// Get Cache Descriptors.
  ///
  CacheInfoCount = 0;
  do {
    AsmCpuidEx (CPUID_CACHE_PARAMS, CacheInfoCount, &CacheEax.Uint32, NULL, NULL, NULL);
    CacheInfoCount++;
  } while (CacheEax.Bits.CacheType != 0);
  CacheInfoCount--; //Don't count descriptor with CacheType = 0.
  DEBUG ((DEBUG_INFO, "CacheInfoCount = %x\n", CacheInfoCount));

  mCpuInfo->CpuInfo->CacheInfo = AllocateZeroPool (CacheInfoCount * sizeof (CACHE_DESCRIPTOR_INFO));
  if (mCpuInfo->CpuInfo->CacheInfo == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  mCpuInfo->CpuInfo->MaxCacheSupported  = CacheInfoCount - 1; // Subtract 1 because there are 2 counts for L1 (Data and Code).
  mCpuInfo->CpuInfo->NumberOfPStates    = mFvidTable[0].FvidHeader.EistStates;;

  BrandString = mCpuInfo->CpuInfo->BrandString;
  CacheInfo   = mCpuInfo->CpuInfo->CacheInfo;

  ///
  /// Get Brand string
  ///
  AsmCpuid (CPUID_BRAND_STRING1, &CpuidRegs.RegEax, &CpuidRegs.RegEbx, &CpuidRegs.RegEcx, &CpuidRegs.RegEdx);
  *(UINT32*) BrandString = CpuidRegs.RegEax; BrandString +=4;
  *(UINT32*) BrandString = CpuidRegs.RegEbx; BrandString +=4;
  *(UINT32*) BrandString = CpuidRegs.RegEcx; BrandString +=4;
  *(UINT32*) BrandString = CpuidRegs.RegEdx; BrandString +=4;

  AsmCpuid (CPUID_BRAND_STRING2, &CpuidRegs.RegEax, &CpuidRegs.RegEbx, &CpuidRegs.RegEcx, &CpuidRegs.RegEdx);
  *(UINT32*) BrandString = CpuidRegs.RegEax; BrandString +=4;
  *(UINT32*) BrandString = CpuidRegs.RegEbx; BrandString +=4;
  *(UINT32*) BrandString = CpuidRegs.RegEcx; BrandString +=4;
  *(UINT32*) BrandString = CpuidRegs.RegEdx; BrandString +=4;

  AsmCpuid (CPUID_BRAND_STRING3, &CpuidRegs.RegEax, &CpuidRegs.RegEbx, &CpuidRegs.RegEcx, &CpuidRegs.RegEdx);
  *(UINT32*) BrandString = CpuidRegs.RegEax; BrandString +=4;
  *(UINT32*) BrandString = CpuidRegs.RegEbx; BrandString +=4;
  *(UINT32*) BrandString = CpuidRegs.RegEcx; BrandString +=4;
  *(UINT32*) BrandString = CpuidRegs.RegEdx; BrandString +=4;
  *BrandString = '\0';
  ///
  /// Remove leading spaces. After removing leading spaces, the Brand String can not be freed. However, it should never be freed.
  ///
  while (*mCpuInfo->CpuInfo->BrandString == ' ') {
    ++mCpuInfo->CpuInfo->BrandString;
  }

  ///
  /// Get information on enabled threads, cores, dies and package for the CPU(s) on this platform
  ///
  GetEnabledCount (&EnabledThreadsPerCore, &EnabledCoresPerDie, NULL, NULL);

  ///
  /// Gather CPU info
  ///
  AsmCpuid (CPUID_VERSION_INFO, &CpuSignature, NULL, &CpuidRegs.RegEcx, &CpuidRegs.RegEdx);
  mCpuInfo->CpuInfo->CpuSignature               = CpuSignature;
  mCpuInfo->CpuInfo->Features                   = LShiftU64 (CpuidRegs.RegEcx, 32) + CpuidRegs.RegEdx;

  AsmCpuidEx (CPUID_EXTENDED_TOPOLOGY, 0, NULL, &CpuidRegs.RegEbx, NULL, NULL);
  mCpuInfo->CpuInfo->NumSupportedThreadsPerCore = (UINT8) CpuidRegs.RegEbx;
  ThreadsPerCore = (UINT8) CpuidRegs.RegEbx;

  AsmCpuidEx (CPUID_EXTENDED_TOPOLOGY, 1, NULL, &CpuidRegs.RegEbx, NULL, NULL);
  mCpuInfo->CpuInfo->NumSupportedCores          = (UINT8) (CpuidRegs.RegEbx / ThreadsPerCore);

  mCpuInfo->CpuInfo->NumCores                   = (UINT8) EnabledCoresPerDie;
  mCpuInfo->CpuInfo->NumHts                     = (UINT8) EnabledThreadsPerCore;
  mCpuInfo->CpuInfo->NumEnabledThreads          = GetEnabledThreadCount ();
  mCpuInfo->CpuInfo->IntendedFreq               = (10000 * (((UINT32) AsmReadMsr64 (MSR_PLATFORM_INFO) >> 8) & 0xFF)) /100;
  mCpuInfo->CpuInfo->Voltage                    = 0;

  for (Index = 0; Index < CacheInfoCount; Index++) {
    AsmCpuidEx (CPUID_CACHE_PARAMS, Index, &CacheEax.Uint32, &CacheEbx.Uint32, &CacheEcx, NULL);
    CacheInfo[Index].Type = (UINT8) CacheEax.Bits.CacheType;
    CacheInfo[Index].Level = (UINT8) CacheEax.Bits.CacheLevel;
    CacheInfo[Index].Associativity = (UINT16) (CacheEbx.Bits.Ways + 1);
    ///
    /// Determine Cache Size in Bytes = (Associativity) * (Partitions + 1) * (Line_Size + 1) * (Sets + 1)= (EBX[31:22] + 1) * (EBX[21:12] + 1) * (EBX[11:0] + 1) * (ECX + 1)
    ///
    CachePartitions = (UINT16) (CacheEbx.Bits.LinePartitions + 1);
    CacheLineSize = (UINT16) (CacheEbx.Bits.LineSize + 1);
    CacheNumberofSets = CacheEcx + 1;
    CacheInfo[Index].Size = (UINT32) ((CacheInfo[Index].Associativity *  CachePartitions * CacheLineSize * CacheNumberofSets) /1024);
  }

  gBS->InstallMultipleProtocolInterfaces (
         &Handle,
         &gCpuInfoProtocolGuid,
         mCpuInfo,
         NULL
         );

  return EFI_SUCCESS;
}
