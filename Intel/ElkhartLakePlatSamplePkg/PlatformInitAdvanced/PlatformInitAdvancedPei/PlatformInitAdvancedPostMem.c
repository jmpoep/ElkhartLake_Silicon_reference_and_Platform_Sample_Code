/** @file
  Source code file for Platform Init PEI module

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2020 Intel Corporation.

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

#include <Register/Msr.h>
#include <CpuRegs.h>
#include <SetupVariable.h>
#include <Library/IoLib.h>
#include <Library/HobLib.h>
#include <Library/BootMediaLib.h>
#include <Library/DebugLib.h>
#include <Library/PchInfoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/PmcLib.h>
#include <Library/GpioLib.h>
#include <Library/GpioNativeLib.h>
#include <Library/PeiPolicyInitLib.h>
#include <Ppi/EndOfPeiPhase.h>
#include <Library/MtrrLib.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <SmramMemoryReserve.h>
#include <Library/ConfigBlockLib.h>
#include <Ppi/SiPolicy.h>
#include <SaPolicyCommon.h>
#include <PchPolicyCommon.h>
#include <Library/SiPolicyLib.h>

#include <Guid/FirmwareFileSystem2.h>
#include <Protocol/FirmwareVolumeBlock.h>
#include <Guid/SystemNvDataGuid.h>

#include <Library/CnviLib.h>
#include <Library/EcLib.h>
#include <Library/EcMiscLib.h>
#include <Library/HdaLib.h>
#include <Library/PostCodeLib.h>
#include <PlatformPostCode.h>
#include <Library/EcTcssLib.h>
#if FixedPcdGetBool(PcdITbtEnable) == 1
#include <TcssDataHob.h>
#endif
#include <Library/ItbtPcieRpLib.h>
#include <Ppi/Spi.h>
#include <Register/MeRegs.h>
#include <Register/HeciRegs.h>

#if FixedPcdGet8(PcdFspModeSelection) == 1
#include <FspmUpd.h>
#include <FspsUpd.h>
#include <Library/FspCommonLib.h>
#endif
#include <Library/MtrrLib.h>
#include <Ppi/PeiDTbtPolicy.h>
#include <Library/PeiTbtTaskDispatchLib.h>
#include <Private/Library/PeiDTbtInitLib.h>
#include <Register/PchRegs.h>
#include <Register/PmcRegs.h>
#include <Register/TelemetryRegs.h>
#include <Library/TelemetryLib.h>
#include <Guid/CrashLog.h>
#include <Library/PeiSubRegionLib.h>
#include <AttemptUsbFirst.h>
#include <PlatformBoardId.h>
#include <Library/PeiPseLib.h>
#include <Core/Pei/PeiMain.h>

EFI_STATUS
EFIAPI
PlatformInitAdvancedEndOfPei (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  );

static EFI_PEI_NOTIFY_DESCRIPTOR  mEndOfPeiNotifyList = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiEndOfPeiSignalPpiGuid,
  (EFI_PEIM_NOTIFY_ENTRY_POINT) PlatformInitAdvancedEndOfPei
};

/**
  This function handles TbtInit task at the end of PEI

  @param[in]  PeiServices  Pointer to PEI Services Table.
  @param[in]  NotifyDesc   Pointer to the descriptor for the Notification event that
                           caused this function to execute.
  @param[in]  Ppi          Pointer to the PPI data associated with this function.

  @retval     EFI_SUCCESS        The function completes successfully
  @retval     RETURN_UNSUPPORTED DTBT is not supported
**/
EFI_STATUS
EFIAPI
DTbtInitEndOfPei (
  VOID
  )
{
  EFI_STATUS      Status;
  UINT8           Index;
  BOOLEAN         DTbtExisted;
  PEI_DTBT_POLICY *PeiDTbtConfig;

  DEBUG ((DEBUG_INFO, "DTbtInitEndOfPei Entry\n"));

  Status       = EFI_SUCCESS;
  PeiDTbtConfig = NULL;
  Index        = 0;
  DTbtExisted  = FALSE;

  Status = PeiServicesLocatePpi (
             &gPeiDTbtPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &PeiDTbtConfig
             );
  if (EFI_ERROR(Status)) {
    DEBUG ((DEBUG_ERROR, " gPeiDTbtPolicyPpiGuid Not installed!!!\n"));
    return RETURN_UNSUPPORTED;
  }

  if (PeiDTbtConfig != NULL) {
    for (Index = 0; Index < MAX_DTBT_CONTROLLER_NUMBER; Index++) {
      if (PeiDTbtConfig->DTbtControllerConfig[Index].DTbtControllerEn == 1) {
        DTbtExisted = TRUE;
        break;
      }
    }

    if (DTbtExisted == TRUE) {
      //
      // Dispatch DTBT task table
      //
      TbtTaskDistpach (DTbtCallTable, (VOID *) PeiDTbtConfig);
    }
  }

  return EFI_SUCCESS;
}

/**
  Update MTRR setting and set write back as default memory attribute.

  @retval  EFI_SUCCESS  The function completes successfully.
  @retval  Others       Some error occurs.
**/
EFI_STATUS
EFIAPI
SetCacheMtrrForTraceHubAfterEndOfPei (
  VOID
  )
{
  EFI_STATUS                            Status;
  EFI_PEI_HOB_POINTERS                  Hob;
  UINTN                                 Index;
  UINT64                                SmramSize;
  UINT64                                SmramBase;
  EFI_SMRAM_HOB_DESCRIPTOR_BLOCK        *SmramHobDescriptorBlock;
#if FixedPcdGetBool(PcdFspWrapperEnable) == 0
  MTRR_SETTINGS                         MtrrSetting;
  UINT64                                MemoryBase;
  UINT64                                MemoryLength;
  UINT64                                ExtraMemoryLength;
  UINT64                                Power2Length;
  EFI_BOOT_MODE                         BootMode;
  UINT32                                TraceHubMemSize;
  SI_CONFIG                             *SiConfig;
  SI_POLICY_PPI                         *SiPolicy;
  SI_PREMEM_POLICY_PPI                  *SiPreMemPolicyPpi;
  SI_PREMEM_CONFIG                      *SiPreMemConfig;
  SA_MISC_PEI_PREMEM_CONFIG             *MiscPeiPreMemConfig;
  PCH_TRACE_HUB_PREMEM_CONFIG           *PchTraceHubConfig;
  CPU_TRACE_HUB_PREMEM_CONFIG           *CpuTraceHubConfig;

  DEBUG ((DEBUG_INFO, "SetCacheMtrrForTraceHubAfterEndOfPei Entry\n"));

  ExtraMemoryLength = 0;
  SiConfig = NULL;
  SiPolicy = NULL;
  SiPreMemPolicyPpi = NULL;
  PchTraceHubConfig = NULL;
  MiscPeiPreMemConfig = NULL;
  CpuTraceHubConfig = NULL;

  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR (Status);

  if (BootMode == BOOT_ON_S3_RESUME) {
    return EFI_SUCCESS;
  }

  Status = PeiServicesLocatePpi (&gSiPreMemPolicyPpiGuid, 0, NULL, (VOID **) &SiPreMemPolicyPpi);
  ASSERT_EFI_ERROR (Status);

  Status = PeiServicesLocatePpi (&gSiPolicyPpiGuid, 0, NULL, (VOID **) &SiPolicy);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicy, &gSiConfigGuid, (VOID *) &SiConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gSiPreMemConfigGuid, (VOID *) &SiPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gPchTraceHubPreMemConfigGuid, (VOID *) &PchTraceHubConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuTraceHubPreMemConfigGuid, (VOID *) &CpuTraceHubConfig);
  ASSERT_EFI_ERROR(Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gSaMiscPeiPreMemConfigGuid, (VOID *) &MiscPeiPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  //
  // Clear the CAR Settings
  //
  ZeroMem (&MtrrSetting, sizeof (MTRR_SETTINGS));

  //
  // Default Cachable attribute will be set to WB to support large memory size/hot plug memory
  //
  MtrrSetting.MtrrDefType &= ~((UINT64)(0xFF));
  MtrrSetting.MtrrDefType |= (UINT64) CacheWriteBack;

  //
  // Set fixed cache for memory range below 1MB
  //
  Status = MtrrSetMemoryAttributeInMtrrSettings (
             &MtrrSetting,
             0x0,
             0xA0000,
             CacheWriteBack
             );
  ASSERT_EFI_ERROR (Status);

  Status = MtrrSetMemoryAttributeInMtrrSettings (
             &MtrrSetting,
             0xA0000,
             0x20000,
             CacheUncacheable
             );
  ASSERT_EFI_ERROR (Status);

  Status = MtrrSetMemoryAttributeInMtrrSettings (
             &MtrrSetting,
             0xC0000,
             0x40000,
             CacheWriteProtected
             );
  ASSERT_EFI_ERROR ( Status);
#endif

  //
  // PI SMM IPL can't set SMRAM to WB because at that time CPU ARCH protocol is not available.
  // Set cacheability of SMRAM to WB here to improve SMRAM initialization performance.
  //
  SmramSize = 0;
  SmramBase = 0;
  Status = PeiServicesGetHobList ((VOID **) &Hob.Raw);
  while (!END_OF_HOB_LIST (Hob)) {
    if (Hob.Header->HobType == EFI_HOB_TYPE_GUID_EXTENSION) {
      if (CompareGuid (&Hob.Guid->Name, &gEfiSmmPeiSmramMemoryReserveGuid)) {
        SmramHobDescriptorBlock = (EFI_SMRAM_HOB_DESCRIPTOR_BLOCK *) (Hob.Guid + 1);
        for (Index = 0; Index < SmramHobDescriptorBlock->NumberOfSmmReservedRegions; Index++) {
          if (SmramHobDescriptorBlock->Descriptor[Index].PhysicalStart > 0x100000) {
            SmramSize += SmramHobDescriptorBlock->Descriptor[Index].PhysicalSize;
            if (SmramBase == 0 || SmramBase > SmramHobDescriptorBlock->Descriptor[Index].CpuStart) {
              SmramBase = SmramHobDescriptorBlock->Descriptor[Index].CpuStart;
            }
          }
        }
        break;
      }
    }
    Hob.Raw = GET_NEXT_HOB (Hob);
  }

#if FixedPcdGetBool(PcdFspWrapperEnable) == 1
  Status = MtrrSetMemoryAttribute (SmramBase, SmramSize, CacheWriteBack);
  ASSERT_EFI_ERROR (Status);
#else
  //
  // Set non system memory as UC
  //
  MemoryBase = 0x100000000;

  MemoryLength = MemoryBase - (SmramBase + SmramSize);
  //
  // Check if both the lowest bit and left of the lowest bit of MemoryLength are set
  // AND the size of lowest position is less than 32MB
  // then add the size of lowest position to MemoryLength for reducing the MTRR usage.
  //
  DEBUG ((DEBUG_INFO, "MemoryBase = %lx\n", MemoryBase));
  DEBUG ((DEBUG_INFO, "MemoryLength = %x\n", MemoryLength));
  if ((LShiftU64 (1, (UINTN) LowBitSet64 (MemoryLength))) <= SIZE_32MB) {
    if ((MemoryLength & (LShiftU64 (1, (UINTN) LowBitSet64 (MemoryLength) + 1))) != 0) {
      ExtraMemoryLength = (LShiftU64 (1, (UINTN) LowBitSet64 (MemoryLength)));
      MemoryLength += ExtraMemoryLength;
      DEBUG ((DEBUG_INFO, "Adjusted MemoryLength = %x\n", MemoryLength));

      BuildResourceDescriptorHob (
        EFI_RESOURCE_MEMORY_RESERVED,
        EFI_RESOURCE_ATTRIBUTE_PRESENT | EFI_RESOURCE_ATTRIBUTE_INITIALIZED | EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
        MemoryBase - MemoryLength,
        ExtraMemoryLength
      );
    }
  }

  while (MemoryLength != 0) {
    Power2Length = GetPowerOfTwo64 (MemoryLength);
    MemoryBase -= Power2Length;
    Status = MtrrSetMemoryAttributeInMtrrSettings (
               &MtrrSetting,
               MemoryBase,
               Power2Length,
               CacheUncacheable
               );
    ASSERT_EFI_ERROR (Status);
    MemoryLength -= Power2Length;
  }

  //
  // Get Trace Hub memory base and size
  //
  TraceHubMemSize = TraceHubCalculateTotalBufferSize (
                      (UINT8) SiPreMemConfig->PlatformDebugConsent,
                      (UINT8) CpuTraceHubConfig->TraceHub.EnableMode,
                      (UINT8) CpuTraceHubConfig->TraceHub.MemReg0Size,
                      (UINT8) CpuTraceHubConfig->TraceHub.MemReg1Size,
                      (UINT8) PchTraceHubConfig->TraceHub.EnableMode,
                      (UINT8) PchTraceHubConfig->TraceHub.MemReg0Size,
                      (UINT8) PchTraceHubConfig->TraceHub.MemReg1Size
                      );

  if (TraceHubMemSize > 0) {
    DEBUG ((DEBUG_INFO, "PlatformInit Set MTRR UC for Trace hub\n"));
    DEBUG ((DEBUG_INFO, "Trace Hub Mem Size = 0x%08x\n", TraceHubMemSize));
    DEBUG ((DEBUG_INFO, "Trace Hub Mem Base = 0x%08x\n", SiConfig->TraceHubMemBase));

    Status = MtrrSetMemoryAttributeInMtrrSettings (
               &MtrrSetting,
               SiConfig->TraceHubMemBase,
               TraceHubMemSize,
               CacheUncacheable
               );
    ASSERT_EFI_ERROR (Status);
  }

  //
  // Update MTRR setting from MTRR buffer
  //
  MtrrSetAllMtrrs (&MtrrSetting);
#endif
  return Status;
}

/**
  This function sends IOM Ready Notify message to EC

  @retval  EFI_SUCCESS   The function completed successfully
  @retval  EFI_NOT_READY IomReady bit is not set
  @retval  others        Some error occurred
**/
EFI_STATUS
IOMReadyNotifyToEC (
  VOID
)
{
  EFI_STATUS                       Status;
#if FixedPcdGetBool(PcdITbtEnable) == 1
  SA_SETUP                         SaSetup;
  SETUP_DATA                       SystemConfiguration;
  UINTN                            VariableSize;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI  *VariableServices;
  UINT8                            EcDataBuffer;
  UINT8                            ReplayMsgBitMask;
  UINT8                            VccstBitMask;
  EFI_BOOT_MODE                    BootMode;
  TCSS_DATA_HOB                    *TcssHob;

  TcssHob = NULL;
  VccstBitMask = 0;
  ///
  /// Locate HOB for TCSS Data and read IOM ready state
  ///
  TcssHob = (TCSS_DATA_HOB *) GetFirstGuidHob (&gTcssHobGuid);
  if (TcssHob == NULL) {
    return EFI_NOT_READY;
  }
  if (!TcssHob->TcssData.IOMReady) {
     DEBUG ((DEBUG_ERROR, "IOMReadyNotifyToEC: IOMReady bit not set in TcssHob.\n"));
    return EFI_NOT_READY;
  }

  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,  // GUID
             0,                                 // INSTANCE
             NULL,                              // EFI_PEI_PPI_DESCRIPTOR
             (VOID **) &VariableServices        // PPI
             );
  if (EFI_ERROR(Status)) {
    DEBUG ((DEBUG_ERROR, "IOMReadyNotifyToEC: Failed to find PEI Read Variable support. Status = %r\n", Status));
  }
  else {
    VariableSize = sizeof (SETUP_DATA);
    Status = VariableServices->GetVariable (
                                 VariableServices,
                                 PLATFORM_SETUP_VARIABLE_NAME,
                                 &gSetupVariableGuid,
                                 NULL,
                                 &VariableSize,
                                 &SystemConfiguration
                                 );
    ASSERT_EFI_ERROR (Status);
    //
    // Send IOMReadyNotify only if EC Handshake is enabled
    //
    if ((!EFI_ERROR(Status)) && (SystemConfiguration.UsbcBiosTcssHandshake == 1) && (!PcdGetBool(PcdBoardPmcPdEnable))) {
      PeiServicesGetBootMode (&BootMode);
      VariableSize = sizeof (SA_SETUP);
      Status = VariableServices->GetVariable (
                                   VariableServices,
                                   L"SaSetup",
                                   &gSetupVariableGuid,
                                   NULL,
                                   &VariableSize,
                                   &SaSetup
                                   );
      // Todo: add other condition (boot mode) checks here.

      EcDataBuffer = 0x00;
      ReplayMsgBitMask = EC_TCSS_BITMASK_REPLAY_MESSAGES;

      if (!EFI_ERROR (Status)) {
        VccstBitMask = SaSetup.TcssVccstStatus;
        //
        // S4 and S5 flow
        //
        if ((BootMode == BOOT_ON_S4_RESUME) || (BootMode == BOOT_ON_S5_RESUME)) {
          if (SaSetup.TcssVccstStatus == 1) {
            //
            // Clear ReplayMsgBitMask after checking VccstStatus policy.
            //
            ReplayMsgBitMask = 0x00;
          }
        } else if (BootMode == BOOT_ON_S3_RESUME) {
          //
          // For S3 resume, clear replay bit always as Platform EC doesn't support replay in S3
          //
          ReplayMsgBitMask = 0x00;
        }
      }
      EcDataBuffer = ReplayMsgBitMask | VccstBitMask;
      Status = UsbcIomReadyNotify(&EcDataBuffer);
      // Todo: Add error condition check if Status is not success
    }
  }
#else
  Status = EFI_SUCCESS;
#endif

  return Status;
}

/**
  Checks if Premium PMIC present (VendorID == 1Fh)

  @retval  TRUE  if present
  @retval  FALSE it discrete/other PMIC
**/
BOOLEAN
IsPremiumPmicPresent (
  VOID
  )
{
  UINT8                           PmicVendorID;

  PmicVendorID = 0;
  //Send KSC Command to detect vendor ID of PMIC is present on the system(Applicable only for ULT/ULX Platforms)
  DetectPmicVendorID (&PmicVendorID);
  DEBUG((DEBUG_INFO, "Vendor ID of the Pmic Present on the system is: %x\n", PmicVendorID));

  if (PmicVendorID == 0x1F) {
    return TRUE;
  }

  return FALSE;
}

/**
Pmic Programming to Enable Voltage Margining
**/
VOID
PremiumPmicEnableSlpS0Voltage (
  VOID
  )
{
  EFI_STATUS                      Status;
  UINT8                           EcDataV085ACNT;
  UINT64                          HdaPciBase;
  BOOLEAN                         PremiumPmicPresent;

  HdaPciBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 HdaDevNumber (),
                 HdaFuncNumber (),
                 0
                 );
  PremiumPmicPresent = IsPremiumPmicPresent();
  if ((PciSegmentRead16(HdaPciBase + PCI_VENDOR_ID_OFFSET) == 0xFFFF) && (PremiumPmicPresent == TRUE)) { // If HDA Device is not detected & Premium PMIC is present
    DEBUG((DEBUG_INFO, "Enable VM in case Premium PMIC is Detected and HDA Disabled\n"));
    EcDataV085ACNT = 0x7A; //Enable Voltage Margining in case HDA is disabled
    Status = SetSlpS0Voltage(EcDataV085ACNT);
    ASSERT_EFI_ERROR(Status);
  }
}

/**
  Configure PciHostBridge related PCDs
**/
VOID
ConfigurePciHostBridgePcds (
  VOID
  )
{
  EFI_STATUS                       Status;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI  *VariableServices;
  EFI_PHYSICAL_ADDRESS             PciBaseAddress;
  UINT32                           Tolud;
  UINT64                           Length;
  UINT64                           McD0BaseAddress;
  UINTN                            ResMemLimit1;
  UINTN                            SaSetupSize;
  SA_SETUP                         SaSetup;
#if FixedPcdGetBool(PcdITbtEnable) == 1
  TCSS_DATA_HOB                    *TcssHob;

  TcssHob                   = NULL;
#endif
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,  // GUID
             0,                                 // INSTANCE
             NULL,                              // EFI_PEI_PPI_DESCRIPTOR
             (VOID **) &VariableServices        // PPI
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ConfigurePciHostBridgePcds: PeiServicesLocatePpi failed\n"));
    return;
  }
#if FixedPcdGetBool(PcdITbtEnable) == 1
  //
  // Get Tcss Data HOB
  //
  TcssHob = (TCSS_DATA_HOB *) GetFirstGuidHob (&gTcssHobGuid);
  if (TcssHob != NULL) {
    if (TcssHob->TcssData.PcieMultipleSegmentEnabled) {
      PcdSet8 (PcdPciSegmentCount, 2);
    }
  }
#endif
  //
  // Allocate 56 KB of I/O space [0x2000..0xFFFF]
  //
  DEBUG ((DEBUG_INFO, " Assign IO resource for PCI_ROOT_BRIDGE from 0x%X to 0x%X\n", PcdGet16 (PcdPciReservedIobase) ,PcdGet16 (PcdPciReservedIoLimit)));

  //
  // Read memory map registers
  //
  McD0BaseAddress        = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, 0);
  Tolud                  = PciSegmentRead32 (McD0BaseAddress + R_SA_TOLUD) & B_SA_TOLUD_TOLUD_MASK;
  PciBaseAddress         = Tolud;

  ResMemLimit1 = PcdGet32 (PcdPciReservedMemLimit);
  if (ResMemLimit1 == 0) {
    ResMemLimit1 = (UINTN) PcdGet64 (PcdPciExpressBaseAddress);
  }

  Length = ResMemLimit1 - PciBaseAddress;

  if (Length != 0) {
    PcdSet32 (PcdPciReservedMemBase, (UINT32) PciBaseAddress);
    PcdSet32 (PcdPciReservedMemLimit, (UINT32) (PciBaseAddress + Length - 1));
    DEBUG ((DEBUG_INFO, " Assign Memory Resource for PCI_ROOT_BRIDGE from 0x%X", PcdGet32 (PcdPciReservedMemBase)));
    DEBUG ((DEBUG_INFO, " to 0x%X\n", PcdGet32 (PcdPciReservedMemLimit)));
  }

  //
  // Check Enable Above 4GB MMIO or not
  //
  SaSetupSize = sizeof (SA_SETUP);
  Status = VariableServices->GetVariable (
                                VariableServices,
                                L"SaSetup",
                                &gSaSetupVariableGuid,
                                NULL,
                                &SaSetupSize,
                                &SaSetup
                                );
  if (!EFI_ERROR(Status)) {
    if (SaSetup.EnableAbove4GBMmio == 1 || SaSetup.ApertureSize == 15) {
      //
      // Provide 256GB available above 4GB MMIO resource
      // limited to use single variable MTRR to cover this above 4GB MMIO region.
      //
      PcdSet64 (PcdPciReservedMemAbove4GBBase, BASE_256GB);
      PcdSet64 (PcdPciReservedMemAbove4GBLimit, BASE_256GB + SIZE_256GB - 1);
      if (PcdGet64 (PcdPciReservedMemAbove4GBBase) < PcdGet64 (PcdPciReservedMemAbove4GBLimit)) {
        DEBUG ((DEBUG_INFO, " PCI space that above 4GB MMIO is from 0x%lX", PcdGet64 (PcdPciReservedMemAbove4GBBase)));
        DEBUG ((DEBUG_INFO, " to 0x%lX\n", PcdGet64 (PcdPciReservedMemAbove4GBLimit)));
      }
    }
  }
}

/**
  This function handles PlatformInit task at the end of PEI

  @param[in]  PeiServices  Pointer to PEI Services Table.
  @param[in]  NotifyDesc   Pointer to the descriptor for the Notification event that
                           caused this function to execute.
  @param[in]  Ppi          Pointer to the PPI data associated with this function.

  @retval     EFI_SUCCESS  The function completes successfully
  @retval     others
**/
EFI_STATUS
EFIAPI
PlatformInitAdvancedEndOfPei (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  )
{
  EFI_STATUS     Status;

  Status = SetCacheMtrrForTraceHubAfterEndOfPei ();
  ASSERT_EFI_ERROR (Status);
  //
  // Configure PciHostBridge related PCDs before DXE phase
  //
  ConfigurePciHostBridgePcds ();

  return Status;
}

//@todo Review this functionality and if it is required for SKL SDS
/**
  Create the HOB for hotkey status for 'Attempt USB First' feature

  @retval  EFI_SUCCESS  HOB Creating successful.
  @retval  Others       HOB Creating failed.
**/
EFI_STATUS
CreateAttemptUsbFirstHotkeyInfoHob (
  VOID
  )
{
  EFI_STATUS                     Status;
  ATTEMPT_USB_FIRST_HOTKEY_INFO  AttemptUsbFirstHotkeyInfo;

  Status = EFI_SUCCESS;

  ZeroMem (
    &AttemptUsbFirstHotkeyInfo,
    sizeof (AttemptUsbFirstHotkeyInfo)
    );

  AttemptUsbFirstHotkeyInfo.RevisonId = 0;
  AttemptUsbFirstHotkeyInfo.HotkeyTriggered = FALSE;

  ///
  /// Build HOB for Attempt USB First feature
  ///
  BuildGuidDataHob (
    &gAttemptUsbFirstHotkeyInfoHobGuid,
    &(AttemptUsbFirstHotkeyInfo),
    sizeof (ATTEMPT_USB_FIRST_HOTKEY_INFO)
    );

  return Status;
}

/**
  Collect PCH CrashLog data from Pmc SSRAM and store in HOB .

**/
VOID
CrashLogCollectDataFromPmcSSRAM (
  VOID
  )
{
  EFI_STATUS                  Status;
  PMC_IPC_DISCOVERY_BUF       DiscoveryBuffer;
  UINT64                      PmcSsramBaseAddress;
  UINT32                      PmcSsramBar0;
  UINT32                      CrashLogAddr;
  EFI_PHYSICAL_ADDRESS        AllocateAddress;
  UINT32                      *Destination = NULL;
  UINT32                      CrashLogSize = 0;
  UINT32                      CopiedSize = 0;

  DEBUG ((DEBUG_INFO, "CrashLogCollectDataFromPmcSSRAM - start\n"));

  //
  // Check for the availability of CrashLog feature
  //
  ZeroMem (&DiscoveryBuffer, sizeof (PMC_IPC_DISCOVERY_BUF));

  Status = PmcCrashLogDiscovery (&DiscoveryBuffer);

  if (EFI_ERROR (Status) || (DiscoveryBuffer.Bits.Avail != 1) || (DiscoveryBuffer.Bits.Dis == 1)) {
    DEBUG ((DEBUG_INFO, "PCH CrashLog feature is not supported\n"));
    return;
  }

  //
  // Start to access PMC SSARM MMIO
  //
  PmcSsramBaseAddress = PCI_SEGMENT_LIB_ADDRESS (
                          DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                          DEFAULT_PCI_BUS_NUMBER_PCH,
                          PCI_DEVICE_NUMBER_PCH_PMC_SSRAM,
                          PCI_FUNCTION_NUMBER_PCH_PMC_SSRAM,
                          0
                          );

  if (PciSegmentRead16 (PmcSsramBaseAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    DEBUG ((DEBUG_ERROR, "PMC SSRAM PCI device is disabled\n"));
    return;
  }

  //
  // Program BAR 0 and enable command register memory space decoding
  //
  PmcSsramBar0 = PcdGet32 (PcdSiliconInitTempMemBaseAddr);
  PciSegmentWrite32 (PmcSsramBaseAddress + PCI_BASE_ADDRESSREG_OFFSET, PmcSsramBar0);
  PciSegmentOr16 (PmcSsramBaseAddress + PCI_COMMAND_OFFSET, (UINT16) (EFI_PCI_COMMAND_MEMORY_SPACE));

  //
  // Check for the presence of CrashLog data
  //
  CrashLogAddr = PmcSsramBar0 + DiscoveryBuffer.Bits.BaseOffset;
  DEBUG ((DEBUG_INFO, "Value at CrashLogAddress 0x%x = 0x%x \n ", CrashLogAddr, MmioRead32 (CrashLogAddr)));
  DEBUG ((DEBUG_INFO, "Value at CrashLogAddress 0x%x = 0x%x \n ", CrashLogAddr + 4, MmioRead32 (CrashLogAddr + 4)));
  //
  // Allocate memory buffer for CrashLog data
  // PEI phase memory allocation must be consistent for S4 support.
  //
  CrashLogSize = (DiscoveryBuffer.Bits.Size != 0) ? DiscoveryBuffer.Bits.Size : 0xC00;
  DEBUG ((DEBUG_INFO, "CrashLogSize in discovery buffer is = 0x%x \n ", DiscoveryBuffer.Bits.Size));
  DEBUG ((DEBUG_INFO, "Use CrashLogSize as 0x%x \n ", CrashLogSize));

  Status = PeiServicesAllocatePages (
             EfiBootServicesData,
             EFI_SIZE_TO_PAGES (CrashLogSize),
             &AllocateAddress
             );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Memory out of resource\n"));
    goto Exit;
  }

  if ((MmioRead32 (CrashLogAddr) != 0) && ((MmioRead32 (CrashLogAddr + 4) & 0x0F) != 0)) {
    DEBUG ((DEBUG_INFO, "Pmc CrashLog is present\n"));
  } else {
    DEBUG ((DEBUG_INFO, "Pmc CrashLog is not present\n"));
    goto Exit;
  }

  //
  // Build of location for Crash log in Hob
  //
  BuildGuidDataHob (
    &gPmcCrashLogDataBufferHobGuid,
    (VOID *) &AllocateAddress,
    sizeof (UINT64)
    );
  DEBUG ((DEBUG_INFO, "CrashLogDataBuffer = 0x%x\n", AllocateAddress));

  ZeroMem ((VOID *) (UINTN) AllocateAddress, EFI_SIZE_TO_PAGES (CrashLogSize) * EFI_PAGE_SIZE);

  //
  // Copy CrashLog data from SSRAM to allocated memory buffer
  //
  Destination = (UINT32 *)(UINTN) AllocateAddress;
  CopiedSize = 0;
  while (CopiedSize < CrashLogSize) {
    *Destination = MmioRead32 (CrashLogAddr); // Byte access is not allowed to PMC SSRAM, hence copying DW by DW
    Destination++;
    CrashLogAddr += 4;
    CopiedSize   += 4;
  }

  //
  // Clear the SSRAM region after copying the error log
  //
  Status = PmcCrashLogClear ();
  DEBUG ((DEBUG_INFO, " Clear CrashLog Status = %r\n", Status));

Exit:
  //
  // Disable PMC SSRAM MMIO
  //
  PciSegmentAnd16 (PmcSsramBaseAddress + PCI_COMMAND_OFFSET, (UINT16) ~(EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_IO_SPACE));
  PciSegmentWrite32 (PmcSsramBaseAddress + PCI_BASE_ADDRESSREG_OFFSET, 0);
  DEBUG ((DEBUG_INFO, "CrashLogCollectDataFromPmcSSRAM - end\n"));

  return;
}

/**
  Collect CPU CrashLog data from Telemetry SRAM and store in HOB .

**/
VOID
CpuCrashLogCollectDataFromTelemetrySRAM (
  VOID
  )
{
  EFI_STATUS                  Status;
  TEL_CRASHLOG_DEVSC_CAP      CrashLogDevscCap;
  UINT64                      TelemetryBaseAddress;
  UINT32                      TempBarAddr;
  EFI_PHYSICAL_ADDRESS        AllocateAddress;
  UINT8                       *Destination = NULL;
  UINT32                      CrashLogSize = 0;
  CPU_CRASHLOG_STRUCT         CpuCrashLogStruct;
  CPU_CRASHLOG_HOB            CpuCrashLogHob;

  DEBUG ((DEBUG_INFO, "CpuCrashLogCollectDataFromTelemetrySRAM - start\n"));

  //
  // Check for the availability of CPU CrashLog feature
  //
  ZeroMem (&CrashLogDevscCap, sizeof (TEL_CRASHLOG_DEVSC_CAP));

  Status = GetCpuCrashLogCapability (&CrashLogDevscCap);

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "CPU CrashLog feature is not supported\n"));
    return;
  }

  //
  // Start to access Telemetry MMIO
  //
  TelemetryBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, TEL_BUS_NUM, TEL_DEV_NUM, TEL_FUN_NUM, 0);

  //
  // Program BAR address and enable command register memory space decoding
  //
  TempBarAddr = PcdGet32 (PcdSiliconInitTempMemBaseAddr);

  if (CrashLogDevscCap.DiscoveryData.Fields.TBir == V_TEL_DVSEC_TBIR_BAR0) {
    PciSegmentWrite32 (TelemetryBaseAddress + R_TEL_CFG_BAR0, TempBarAddr);
  } else if (CrashLogDevscCap.DiscoveryData.Fields.TBir == V_TEL_DVSEC_TBIR_BAR1) {
    PciSegmentWrite32 (TelemetryBaseAddress + R_TEL_CFG_BAR1, TempBarAddr);
  }
  PciSegmentOr16 (TelemetryBaseAddress + PCI_COMMAND_OFFSET, (UINT16) (EFI_PCI_COMMAND_MEMORY_SPACE));

  ZeroMem (&CpuCrashLogStruct, sizeof (CPU_CRASHLOG_STRUCT));

  Status = CpuCrashLogDiscovery (&CpuCrashLogStruct);

  CrashLogSize = (CpuCrashLogStruct.MainBuffer.Fields.DataBuffSize +
                  CpuCrashLogStruct.TelemetryBuffer.Fields.DataBuffSize +
                  CpuCrashLogStruct.TraceBuffer.Fields.DataBuffSize) * 4;

  if (CrashLogSize == 0) {
    DEBUG ((DEBUG_INFO, "CPU CrashLog is not present \n "));
    goto Exit;
  }

  DEBUG ((DEBUG_INFO, "Use CrashLogSize as 0x%x \n ", CrashLogSize));

  //
  // Allocate memory buffer for CrashLog data
  //
  Status = PeiServicesAllocatePages (
             EfiBootServicesData,
             EFI_SIZE_TO_PAGES (CrashLogSize),
             &AllocateAddress
             );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Memory out of resource\n"));
    goto Exit;
  }

  CpuCrashLogHob.AllocateAddress = (UINTN) AllocateAddress;
  CpuCrashLogHob.Size = CrashLogSize;

  DEBUG ((DEBUG_INFO, "CpuCrashLogHob.AllocateAddress = 0x%X, CpuCrashLogHob.Size = 0x%X \n", CpuCrashLogHob.AllocateAddress, CpuCrashLogHob.Size));
  //
  // Build of location for Crash log in Hob
  //
  BuildGuidDataHob (
    &gCpuCrashLogDataBufferHobGuid,
    &CpuCrashLogHob,
    sizeof (CPU_CRASHLOG_HOB)
    );

  ZeroMem ((VOID *) (UINTN) AllocateAddress, EFI_SIZE_TO_PAGES (CrashLogSize) * EFI_PAGE_SIZE);

  //
  // Copy CrashLog data to allocated memory buffer
  //
  Destination = (UINT8 *)(UINTN) AllocateAddress;

  //
  // copy Main pointer crashlog data
  //
  CopyMem (Destination, &(CpuCrashLogStruct.MainBuffer.Fields.DataBuffAddress), (CpuCrashLogStruct.MainBuffer.Fields.DataBuffSize) * 4);
  Destination += (CpuCrashLogStruct.MainBuffer.Fields.DataBuffSize * 4);
  //
  // copy Telemetry pointer crashlog data
  //
  CopyMem (Destination, &(CpuCrashLogStruct.TelemetryBuffer.Fields.DataBuffAddress), (CpuCrashLogStruct.TelemetryBuffer.Fields.DataBuffSize) * 4);
  Destination += (CpuCrashLogStruct.TelemetryBuffer.Fields.DataBuffSize * 4);
  //
  // copy Trace pointer crashlog data
  //
  CopyMem (Destination, &(CpuCrashLogStruct.TraceBuffer.Fields.DataBuffAddress), (CpuCrashLogStruct.TraceBuffer.Fields.DataBuffSize) * 4);
  //
  // Clear the Telemetry SRAM region after copying the error log
  //
  CpuCrashLogClear ();

Exit:
  //
  // Disable Telemetry SRAM MMIO
  //
  PciSegmentAnd16 (TelemetryBaseAddress + PCI_COMMAND_OFFSET, (UINT16) ~(EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_IO_SPACE));
  if (CrashLogDevscCap.DiscoveryData.Fields.TBir == V_TEL_DVSEC_TBIR_BAR0) {
    PciSegmentWrite32 (TelemetryBaseAddress + R_TEL_CFG_BAR0, 0);
  } else if (CrashLogDevscCap.DiscoveryData.Fields.TBir == V_TEL_DVSEC_TBIR_BAR1) {
    PciSegmentWrite32 (TelemetryBaseAddress + R_TEL_CFG_BAR1, 0);
  }
  DEBUG ((DEBUG_INFO, "CpuCrashLogCollectDataFromTelemetrySRAM - end\n"));

  return;
}

/**
  Callback to consume DefaultPolicyInit PPI to install and update policy.

  @param[in]  PeiServices  Pointer to PEI Services Table.
  @param[in]  NotifyDesc   Pointer to the descriptor for the Notification event that
                           caused this function to execute.
  @param[in]  Ppi          Pointer to the PPI data associated with this function.

  @retval     EFI_SUCCESS   The function completes successfully
  @retval     EFI_NOT_FOUND Either variable service or required variable not found.
**/
EFI_STATUS
EFIAPI
SiDefaultPolicyInitPpiNotifyCallback (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  )
{

  EFI_STATUS                        Status;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI   *VariableServices;
  SETUP_DATA                        SystemConfiguration;
  UINTN                             VariableSize;
  UINT8                             FwConfig;

  VariableServices = NULL;
  Status = PeiServicesLocatePpi (
              &gEfiPeiReadOnlyVariable2PpiGuid,
              0,
              NULL,
              (VOID **) &VariableServices
              );
  if (VariableServices != NULL) {
    VariableSize = sizeof (SETUP_DATA);
    Status = VariableServices->GetVariable (
                                 VariableServices,
                                 L"Setup",
                                 &gSetupVariableGuid,
                                 NULL,
                                 &VariableSize,
                                 &SystemConfiguration
                                 );
    if (!EFI_ERROR (Status)) {
      FwConfig = SystemConfiguration.FirmwareConfiguration;
      PeiPolicyInit (PeiServices, FwConfig);
      return EFI_SUCCESS;
    }
  }
  return EFI_NOT_FOUND;

}

static EFI_PEI_NOTIFY_DESCRIPTOR mSiDefaultPolicyInitNotifyList = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gSiDefaultPolicyInitPpiGuid,
  (EFI_PEIM_NOTIFY_ENTRY_POINT) SiDefaultPolicyInitPpiNotifyCallback
};

/**
  Checks whether the platform is a sample part; or in manufacturing mode or debug mode.

  @retval  TRUE    Platform is a sample part; or in manufacturing mode or debug mode.
  @retval  FALSE   Platfomr is not a sample part; or in manufacturing mode or debug mode.
**/
BOOLEAN
PlatformDebugStateEnabled (
  VOID
  )
{
  HECI_FW_STS6_REGISTER             MeFirmwareStatus;
  MSR_IA32_FEATURE_CONTROL_REGISTER Ia32FeatureControlMsr;

  //
  // Check for Sample part
  //
  if ((AsmReadMsr64 (MSR_PLATFORM_INFO) & B_MSR_PLATFORM_INFO_SAMPLE_PART_MASK) != 0) {
    return TRUE;
  }

  Ia32FeatureControlMsr.Uint64 = AsmReadMsr64 (MSR_IA32_FEATURE_CONTROL);
  if (Ia32FeatureControlMsr.Bits.Lock == 0) {
    return TRUE;
  }

  //
  // Check for Manufacturing Mode
  //
  MeFirmwareStatus.ul = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, R_ME_HFS_6));
  if (MeFirmwareStatus.r.FpfSocConfigLock == 0) {
    return TRUE;
  }

  //
  // Check for Debug mode
  //
  if ((AsmReadMsr64 (MSR_IA32_DEBUG_INTERFACE) & MSR_IA32_DEBUG_INTERFACE) != 0) {
    return TRUE;
  }

  return FALSE;
}

/**
  Configures GPIO

  @param[in]  GpioTable       Point to Platform Gpio table
  @param[in]  GpioTableCount  Number of Gpio table entries

**/
VOID
ConfigureGpio (
  IN GPIO_INIT_CONFIG                 *GpioDefinition,
  IN UINT16                           GpioTableCount
  )
{
  EFI_STATUS          Status;

  DEBUG ((DEBUG_INFO, "ConfigureGpio() Start\n"));

  Status = GpioConfigurePads (GpioTableCount, GpioDefinition);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "ConfigureGpio() End\n"));
}

/**
  Configure GPIO pads for TouchPanels use
**/
VOID
TouchPanelGpioInit (
  VOID
  )
{
  EFI_STATUS                      Status;
  PCH_SETUP                       PchSetup;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices;
  UINTN                           VarSize;
  UINT16                          BoardId;

  DEBUG ((DEBUG_INFO, "TouchPanelGpioInit Start\n"));

  //
  // Locate Setup variables
  //
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &VariableServices
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "TouchPanelGpioInit: PeiServicesLocatePpi failed\n"));
    return;
  }

  VarSize = sizeof (PCH_SETUP);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"PchSetup",
                               &gPchSetupVariableGuid,
                               NULL,
                               &VarSize,
                               &PchSetup
                               );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "TouchPanelGpioInit: GetVariable (PchSetup) failed\n"));
    return;
  }
  BoardId = PcdGet16(PcdBoardId);

  switch (BoardId) {
    case BoardIdEhlLp4xType4Erb:
    case BoardIdEhlLp4xType4Rvp1:
    case BoardIdEhlDdr4Type3Rvp2:
    case BoardIdEhlLp4xType3Crb:
    case BoardIdJslLp4xErb:
    case BoardIdJslLp4xType4Rvp1:
      //
      // Verify if THC0 or THC1 panels are enabled before changing GPIO configuration
      //
      if (PchSetup.ThcPort0Assignment == ThcAssignmentNone) {
        DEBUG ((DEBUG_INFO, "THC0 Disabled. Configuring GPIO Touch Panel 1 set for other controller use\n"));
        ConfigureGpio ((VOID *) (UINTN) PcdGet32 (PcdBoardGpioTableTouchPanel1), PcdGet16 (PcdBoardGpioTableTouchPanel1Size));
      }

      if (PchSetup.ThcPort1Assignment == ThcAssignmentNone) {
        DEBUG ((DEBUG_INFO, "THC1 Disabled. Configuring GPIO Touch Panel 2 set for other controller use\n"));
        ConfigureGpio ((VOID *) (UINTN) PcdGet32 (PcdBoardGpioTableTouchPanel2), PcdGet16 (PcdBoardGpioTableTouchPanel2Size));
      }
      break;
  }
  DEBUG ((DEBUG_INFO, "TouchPanelGpioInit End\n"));
}

VOID
ConnectivityGpioInit (
  VOID
  )
{
  EFI_STATUS                      Status;
  PCH_SETUP                       PchSetup;
  SETUP_DATA                      SetupData;
  UINTN                           VarSize;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices;

  //
  // Locate Setup variables
  //
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &VariableServices
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ConnectivityGpioInit: PeiServicesLocatePpi failed\n"));
    return;
  }

  VarSize = sizeof (PCH_SETUP);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"PchSetup",
                               &gPchSetupVariableGuid,
                               NULL,
                               &VarSize,
                               &PchSetup
                               );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ConnectivityGpioInit: GetVariable (PchSetup) failed\n"));
    return;
  }

  VarSize = sizeof (SETUP_DATA);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"Setup",
                               &gSetupVariableGuid,
                               NULL,
                               &VarSize,
                               &SetupData
                               );
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_ERROR, "ConnectivityGpioInit: GetVariable (SetupData) failed\n"));
    return;
  }
  if (!CnviIsPresent () || (PchSetup.CnviMode == CnviModeDisabled)) {
    //
    // Discrete BT Module Selection as Disabled, Over USB or UART
    //
    PcdSet8S (PcdDiscreteBtModule, SetupData.DiscreteBtModule);
  }

}

VOID
MipiCamConfigureGpio (
  IN GPIO_CONFIG *GpioConfig
  )
{
  ZeroMem(GpioConfig, sizeof(GPIO_CONFIG));
  GpioConfig->PadMode = GpioPadModeGpio;
  GpioConfig->HostSoftPadOwn = GpioHostOwnGpio;
  GpioConfig->Direction = GpioDirOut;
  GpioConfig->OutputState = GpioOutDefault;
  GpioConfig->InterruptConfig = GpioIntDis;
  GpioConfig->PowerConfig = GpioPlatformReset;
  GpioConfig->ElectricalConfig = GpioTermNone;
}

VOID
MipiCamGpioInit (
  VOID
  )
{
  PCH_SETUP                       PchSetup;
  SETUP_DATA                      SetupData;
  UINTN                           VarSize;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices;
  EFI_STATUS                      Status;
  GPIO_CONFIG                     GpioConfig;
  GPIO_PAD                        GpioPad;
  UINT8                           GpioPin;

  //
  // Locate Setup variables
  //
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &VariableServices
             );
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_ERROR, "MipiCamGpioInit: PeiServicesLocatePpi failed\n"));
    return;
  }

  VarSize = sizeof (PCH_SETUP);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"PchSetup",
                               &gPchSetupVariableGuid,
                               NULL,
                               &VarSize,
                               &PchSetup
                               );
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_ERROR, "MipiCamGpioInit: GetVariable (PchSetup) failed\n"));
    return;
  }

  VarSize = sizeof (SETUP_DATA);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"Setup",
                               &gSetupVariableGuid,
                               NULL,
                               &VarSize,
                               &SetupData
                               );
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_ERROR, "MipiCamGpioInit: GetVariable (SetupData) failed\n"));
    return;
  }

  MipiCamConfigureGpio (&GpioConfig);
  if ((SetupData.MipiCam_ControlLogic0) && (SetupData.MipiCam_ControlLogic0_Type == (UINT8)1) && (SetupData.MipiCam_ControlLogic0_GpioPinsEnabled)) {
    DEBUG((DEBUG_INFO, "MipiCamGpioInit ControlLogic0\n"));
    for (GpioPin = 0; GpioPin < SetupData.MipiCam_ControlLogic0_GpioPinsEnabled; GpioPin ++) {
      GpioPad = GpioGetGpioPadFromGroupIndexAndPadNumber (
                                   (UINT32)SetupData.MipiCam_ControlLogic0_GpioGroupNumber[GpioPin],
                                   (UINT32)SetupData.MipiCam_ControlLogic0_GpioGroupPadNumber[GpioPin]);
      DEBUG((DEBUG_INFO, "MipiCamGpioInit GpioPad 0x%x\n", GpioPad));
      GpioSetPadConfig (GpioPad, &GpioConfig);
    }
  }
  if ((SetupData.MipiCam_ControlLogic1) && (SetupData.MipiCam_ControlLogic1_Type == (UINT8)1) && (SetupData.MipiCam_ControlLogic1_GpioPinsEnabled)) {
    DEBUG((DEBUG_INFO, "MipiCamGpioInit ControlLogic1\n"));
    for (GpioPin = 0; GpioPin < SetupData.MipiCam_ControlLogic1_GpioPinsEnabled; GpioPin ++) {
      GpioPad = GpioGetGpioPadFromGroupIndexAndPadNumber (
                                   (UINT32)SetupData.MipiCam_ControlLogic1_GpioGroupNumber[GpioPin],
                                   (UINT32)SetupData.MipiCam_ControlLogic1_GpioGroupPadNumber[GpioPin]);
      DEBUG((DEBUG_INFO, "MipiCamGpioInit GpioPad 0x%x\n", GpioPad));
      GpioSetPadConfig (GpioPad, &GpioConfig);
    }
  }
  if ((SetupData.MipiCam_ControlLogic2) && (SetupData.MipiCam_ControlLogic2_Type == (UINT8)1) && (SetupData.MipiCam_ControlLogic2_GpioPinsEnabled)) {
    DEBUG((DEBUG_INFO, "MipiCamGpioInit ControlLogic2\n"));
    for (GpioPin = 0; GpioPin < SetupData.MipiCam_ControlLogic2_GpioPinsEnabled; GpioPin ++) {
      GpioPad = GpioGetGpioPadFromGroupIndexAndPadNumber (
                                   (UINT32)SetupData.MipiCam_ControlLogic2_GpioGroupNumber[GpioPin],
                                   (UINT32)SetupData.MipiCam_ControlLogic2_GpioGroupPadNumber[GpioPin]);
      DEBUG((DEBUG_INFO, "MipiCamGpioInit GpioPad 0x%x\n", GpioPad));
      GpioSetPadConfig (GpioPad, &GpioConfig);
    }
  }
  if ((SetupData.MipiCam_ControlLogic3) && (SetupData.MipiCam_ControlLogic3_Type == (UINT8)1) && (SetupData.MipiCam_ControlLogic3_GpioPinsEnabled)) {
    DEBUG((DEBUG_INFO, "MipiCamGpioInit ControlLogic3\n"));
    for (GpioPin = 0; GpioPin < SetupData.MipiCam_ControlLogic3_GpioPinsEnabled; GpioPin ++) {
      GpioPad = GpioGetGpioPadFromGroupIndexAndPadNumber (
                                   (UINT32)SetupData.MipiCam_ControlLogic3_GpioGroupNumber[GpioPin],
                                   (UINT32)SetupData.MipiCam_ControlLogic3_GpioGroupPadNumber[GpioPin]);
      DEBUG((DEBUG_INFO, "MipiCamGpioInit GpioPad 0x%x\n", GpioPad));
      GpioSetPadConfig (GpioPad, &GpioConfig);
    }
  }
  return;
}


/**
  Configure GPIO pads for Pch Tsn device
**/
VOID
TsnDeviceGpioInit (
  VOID
  )
{
  EFI_STATUS                      Status;
  PCH_SETUP                       PchSetup;
  UINTN                           VarSize;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices;

  DEBUG ((DEBUG_INFO, "TsnDeviceGpioInit() Start\n"));

  //
  // Locate Setup variables
  //
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &VariableServices
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "TsnGpioInit: PeiServicesLocatePpi failed\n"));
    return;
  }

  VarSize = sizeof (PCH_SETUP);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"PchSetup",
                               &gPchSetupVariableGuid,
                               NULL,
                               &VarSize,
                               &PchSetup
                               );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "TsnGpioInit: GetVariable (PchSetup) failed\n"));
    return;
  }

  if (PchSetup.PchTsnEnable) {
    DEBUG ((DEBUG_INFO, "PCH TSN Device GpioInit\n"));
    ConfigureGpio ((VOID *) (UINTN) PcdGet32 (PcdBoardGpioTablePchTsnDevice), (UINTN) PcdGet16 (PcdBoardGpioTablePchTsnDeviceSize));
  }

  if (PchSetup.PchPseEnable) {
    if (PchSetup.PchPseGbeEnable[0]) {
      DEBUG ((DEBUG_INFO, "PSE TSN0 Device GpioInit\n"));
      ConfigureGpio ((VOID *) (UINTN) PcdGet32 (PcdBoardGpioTablePseTsn0Device), (UINTN) PcdGet16 (PcdBoardGpioTablePseTsn0DeviceSize));
    }
    if (PchSetup.PchPseGbeEnable[1]) {
      DEBUG ((DEBUG_INFO, "PSE TSN1 Device GpioInit\n"));
      ConfigureGpio ((VOID *) (UINTN) PcdGet32 (PcdBoardGpioTablePseTsn1Device), (UINTN) PcdGet16 (PcdBoardGpioTablePseTsn1DeviceSize));
    }
  }
    DEBUG ((DEBUG_INFO, "TsnDeviceGpioInit() End\n"));
}

/**
  Configure advanced GPIO

**/
VOID
GpioInitAdvanced (
  VOID
  )
{

  TouchPanelGpioInit ();

  // Configure Connectivity options
  ConnectivityGpioInit();
  if (PcdGetBool (PcdMipiCamGpioEnable)) {
    MipiCamGpioInit();
  }


  TsnDeviceGpioInit ();

  //
  // Lock pads after initializing platform GPIO.
  // Pads which were requested to be unlocked during configuration
  // will not be locked.
  //
  GpioLockPads ();

  return;
}
/**
  Platform Init PEI module entry point

  @param[in]  FileHandle           Not used.
  @param[in]  PeiServices          General purpose services available to every PEIM.

  @retval     EFI_SUCCESS          The function completes successfully
  @retval     EFI_OUT_OF_RESOURCES Insufficient resources to create database
**/
EFI_STATUS
EFIAPI
PlatformInitAdvancedPostMemEntryPoint (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS                       Status;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI  *VariableServices;
  SETUP_DATA                       SetupData;
  UINTN                            VariableSize;
  UINT8                            FwConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 1
  VOID                             *FspmUpd;
#else
  SI_PREMEM_POLICY_PPI             *SiPreMemPolicyPpi;
  CPU_SECURITY_PREMEM_CONFIG       *CpuSecurityPreMemConfig;
#endif
  PEI_CORE_INSTANCE                *PrivateData;
  UINTN                            CurrentFv;
  PEI_CORE_FV_HANDLE               *CoreFvHandle;
  VOID                             *HobData;

  PostCode (PLATFORM_INIT_POSTMEM_ENTRY);

#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspmUpd = NULL;
#else
  SiPreMemPolicyPpi = NULL;
  CpuSecurityPreMemConfig = NULL;
#endif

#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspmUpd = (FSPM_UPD *) GetFspMemoryInitUpdDataPointer ();
  ASSERT (FspmUpd != NULL);
#else
  Status = PeiServicesLocatePpi (&gSiPreMemPolicyPpiGuid, 0, NULL, (VOID **) &SiPreMemPolicyPpi);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuSecurityPreMemConfigGuid, (VOID *) &CpuSecurityPreMemConfig);
  ASSERT_EFI_ERROR (Status);
#endif

  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,  // GUID
             0,                                 // INSTANCE
             NULL,                              // EFI_PEI_PPI_DESCRIPTOR
             (VOID **) &VariableServices        // PPI
             );
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (SETUP_DATA);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               PLATFORM_SETUP_VARIABLE_NAME,
                               &gSetupVariableGuid,
                               NULL,
                               &VariableSize,
                               &SetupData
                               );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Fail to get System Configuration and set the configuration to production mode!\n"));
    FwConfig = 0;
  } else {
    FwConfig = SetupData.FirmwareConfiguration;
  }

  GpioInitAdvanced();

  //
  // Build a HOB to show current FV location for SA policy update code to consume.
  //
  PrivateData = PEI_CORE_INSTANCE_FROM_PS_THIS(PeiServices);
  CurrentFv = PrivateData->CurrentPeimFvCount;
  CoreFvHandle = &(PrivateData->Fv[CurrentFv]);

  HobData = BuildGuidHob (
             &gPlatformInitFvLocationGuid,
             sizeof (VOID *)
             );
  ASSERT (HobData != NULL);
  CopyMem (HobData, (VOID *) &CoreFvHandle, sizeof (VOID *));

  //
  // Initialize Intel PEI Pos-Mem Platform Policy //move to board /change name
  //
#if (FixedPcdGet8(PcdFspModeSelection) == 1)
  //
  // FSP API mode call the function directly.
  //
  PeiPolicyInit (PeiServices, FwConfig);
#else
  //
  // FSP Dispatch mode or non-FSP build will depend on DefaultPolicyInit PPI.
  //
  Status = PeiServicesNotifyPpi (&mSiDefaultPolicyInitNotifyList);
  ASSERT_EFI_ERROR (Status);
#endif

  //
  // BIOS shall extract Crash records from PMC SSRAM after memory init
  // and before enabling the Energy Reporting feature
  //
  CrashLogCollectDataFromPmcSSRAM ();
  //
  // Create USB Boot First hotkey information HOB
  //
  CreateAttemptUsbFirstHotkeyInfoHob ();


  //
  // Check Platform debug state
  //
  if (PlatformDebugStateEnabled ()) {
    //
    // Extend platform state into TPM PCR[7]
    //
    PcdSetBoolS (PcdFirmwareDebuggerInitialized, TRUE);
  }

  //
  // Performing PlatformInitEndOfPei after EndOfPei PPI produced
  //
  Status = PeiServicesNotifyPpi (&mEndOfPeiNotifyList);

  PostCode (PLATFORM_INIT_POSTMEM_EXIT);

  return Status;
}
