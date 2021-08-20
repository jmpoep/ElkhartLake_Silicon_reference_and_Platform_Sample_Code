/** @file
  Overclocking early post initializations.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

#include <Uefi.h>
#include <Library/CpuCommonLib.h>
#include <Library/PeiOcLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/CpuMailboxLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PostCodeLib.h>
#include <Library/CpuPlatformLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/PeiMeLib.h>
#include <Ppi/SiPolicy.h>
#include <Ppi/Wdt.h>
#include <CpuAccess.h>

/**
  Initializes Ring related overclocking settings.

  @param[in] OverClockingConfig      Pointer to CPU Overclocking Policy instance

  @retval EFI_SUCCESS
**/
EFI_STATUS
EFIAPI
CpuOcInitRingSettings (
  IN OVERCLOCKING_PREMEM_CONFIG *OverClockingConfig
  )
{
  EFI_STATUS              Status;
  UINT32                  LibStatus;
  UINT32                  MailboxData;
  UINT32                  CurrentRingDownBin;

  ///
  /// Program Ring Downbin feature if needed
  ///
  Status = MailboxRead(MAILBOX_TYPE_OC, OC_LIB_CMD_GET_MISC_TURBO_CONTROL, &MailboxData, &LibStatus);
  if ((Status == EFI_SUCCESS) && (LibStatus == PCODE_MAILBOX_CC_SUCCESS)) {
    ///
    /// Ring Downbin mailbox command uses reverse encoding. 0 - Enable Ring Downbin, 1 - Disable Ring Downbin
    ///
    CurrentRingDownBin = (~MailboxData & MISC_TURBO_RING_DOWNBIN_MASK) >> MISC_TURBO_RING_DOWNBIN_OFFSET;
    if (OverClockingConfig->RingDownBin != CurrentRingDownBin) {
      DEBUG ((DEBUG_INFO, "(OC) Updating Ring Downbin = %X\n", OverClockingConfig->RingDownBin));
      MailboxData = (~OverClockingConfig->RingDownBin << MISC_TURBO_RING_DOWNBIN_OFFSET) & MISC_TURBO_RING_DOWNBIN_MASK;
      MailboxWrite(MAILBOX_TYPE_OC, OC_LIB_CMD_SET_MISC_TURBO_CONTROL, MailboxData, &LibStatus);
      if (LibStatus != EFI_SUCCESS) {
        DEBUG ((DEBUG_INFO, "(OC) Ring Downbin message failed, mailbox status = %X\n", LibStatus));
      }
    }
  }

  return Status;
}

/**
  Initializes IA/Core related overclocking settings.

  @param[in] OverClockingConfig      Pointer to CPU Overclocking Policy instance

  @retval EFI_SUCCESS
**/
EFI_STATUS
EFIAPI
CpuOcInitCoreSettings(
IN OVERCLOCKING_PREMEM_CONFIG *OverClockingConfig,
OUT BOOLEAN *ResetRequired
  )
{
  EFI_STATUS          Status;
  UINT32              LibStatus;
  AVX_RATIO_ITEM      CurrentAvxRatioOffset;
  AVX_RATIO_ITEM      RequestedAvxRatioOffset;
  UINT32              CurrentPllOffset;
  UINT32              RequestedPllOffset;
  UINT32              MailboxReadCommand;
  UINT32              MailboxWriteCommand;
  UINT32              CurrentTjMaxOffset;
  UINT32              RequestedTjMaxOffset;
  UINT32              MiscGlobalConfigData;
  UINT8               DomainId;

  ///
  /// Configure the Pll Voltage offsets for each CPU domain
  ///

  //
  // Initialize
  //
  RequestedPllOffset  = 0x00;
  MailboxReadCommand  = 0x00;
  MailboxWriteCommand = 0x00;

  for (DomainId = OC_LIB_DOMAIN_ID_IA_CORE; DomainId <= OC_LIB_DOMAIN_ID_MEMORY_CONTROLLER; DomainId++ ) {

    switch (DomainId) {
      case OC_LIB_DOMAIN_ID_IA_CORE:
        RequestedPllOffset = OverClockingConfig->CorePllVoltageOffset;
        MailboxReadCommand = READ_PLL_VOLTAGE_OFFSET_CMD | (OC_LIB_DOMAIN_ID_IA_CORE << 8);
        MailboxWriteCommand = WRITE_PLL_VOLTAGE_OFFSET_CMD | (OC_LIB_DOMAIN_ID_IA_CORE << 8);
      break;

      case OC_LIB_DOMAIN_ID_GT:
        RequestedPllOffset = OverClockingConfig->GtPllVoltageOffset;
        MailboxReadCommand = READ_PLL_VOLTAGE_OFFSET_CMD | (OC_LIB_DOMAIN_ID_GT << 8);
        MailboxWriteCommand = WRITE_PLL_VOLTAGE_OFFSET_CMD | (OC_LIB_DOMAIN_ID_GT << 8);
      break;

      case OC_LIB_DOMAIN_ID_RING:
        RequestedPllOffset = OverClockingConfig->RingPllVoltageOffset;
        MailboxReadCommand = READ_PLL_VOLTAGE_OFFSET_CMD | (OC_LIB_DOMAIN_ID_RING << 8);
        MailboxWriteCommand = WRITE_PLL_VOLTAGE_OFFSET_CMD | (OC_LIB_DOMAIN_ID_RING << 8);
      break;

      case OC_LIB_DOMAIN_ID_SYSTEM_AGENT:
        RequestedPllOffset = OverClockingConfig->SaPllVoltageOffset;
        MailboxReadCommand = READ_PLL_VOLTAGE_OFFSET_CMD | (OC_LIB_DOMAIN_ID_SYSTEM_AGENT << 8);
        MailboxWriteCommand = WRITE_PLL_VOLTAGE_OFFSET_CMD | (OC_LIB_DOMAIN_ID_SYSTEM_AGENT << 8);
      break;

      case OC_LIB_DOMAIN_ID_MEMORY_CONTROLLER:
        RequestedPllOffset = OverClockingConfig->McPllVoltageOffset;
        MailboxReadCommand = READ_PLL_VOLTAGE_OFFSET_CMD | (OC_LIB_DOMAIN_ID_MEMORY_CONTROLLER << 8);
        MailboxWriteCommand = WRITE_PLL_VOLTAGE_OFFSET_CMD | (OC_LIB_DOMAIN_ID_MEMORY_CONTROLLER << 8);
      break;

      default:
      break;
    }

    ///
    /// Read the current PLL voltage offset
    ///
    MailboxRead(MAILBOX_TYPE_PCODE, MailboxReadCommand, &CurrentPllOffset, &LibStatus);
    if (LibStatus == PCODE_MAILBOX_CC_SUCCESS) {
      ///
      /// If needed, write the new PLL voltage offset
      ///
      if (RequestedPllOffset != CurrentPllOffset) {
        DEBUG ((DEBUG_INFO, "(OC) Current Pll offset for domain %d  = %X\n", DomainId, CurrentPllOffset));
        DEBUG ((DEBUG_INFO, "(OC) Requested Pll offset for domain %d = %X\n",DomainId, RequestedPllOffset));
        MailboxWrite(MAILBOX_TYPE_PCODE, MailboxWriteCommand, RequestedPllOffset, &LibStatus);
        if (LibStatus != EFI_SUCCESS) {
          DEBUG ((DEBUG_INFO, "(OC) Pll message failed for Domain %d, mailbox status = %X\n", DomainId, LibStatus));
        } else {
          *ResetRequired = TRUE;
        }
      }
    }
  }

  ///
  /// Get the current AVX ratio from OC mailbox
  ///
  Status = GetAvxRatioOffset(&CurrentAvxRatioOffset, &LibStatus);
  if (LibStatus == OC_LIB_COMPLETION_CODE_SUCCESS) {
    DEBUG ((DEBUG_INFO, "(OC) Current AVX2 Ratio Offset   = %X\n", CurrentAvxRatioOffset.Avx2Ratio));
    DEBUG ((DEBUG_INFO, "(OC) Current AVX3 Ratio Offset   = %X\n", CurrentAvxRatioOffset.Avx3Ratio));
    DEBUG ((DEBUG_INFO, "(OC) Requested AVX2 Ratio Offset = %X\n", OverClockingConfig->Avx2RatioOffset));
    DEBUG ((DEBUG_INFO, "(OC) Requested AVX3 Ratio Offset = %X\n", OverClockingConfig->Avx3RatioOffset));
    RequestedAvxRatioOffset.Avx2Ratio = (UINT8)OverClockingConfig->Avx2RatioOffset;
    RequestedAvxRatioOffset.Avx3Ratio = (UINT8)OverClockingConfig->Avx3RatioOffset;

    if (CompareMem ((VOID *)&RequestedAvxRatioOffset,(VOID *)&CurrentAvxRatioOffset,sizeof (AVX_RATIO_ITEM))) {
      ///
      /// Set the requested AVX ratio to OC mailbox
      ///
      Status = SetAvxRatioOffset(RequestedAvxRatioOffset, &LibStatus);
      if ((Status != EFI_SUCCESS) || (LibStatus != OC_LIB_COMPLETION_CODE_SUCCESS)) {
        DEBUG ((DEBUG_ERROR, "(OC) Set AVX ratio offset failed. EFI Status = %X, Library Status = %X\n", Status, LibStatus));
      }
    }
  } else {
    DEBUG ((DEBUG_INFO, "(OC) Get AVX Ratio offset failed. EFI Status = %X, Library Status = %X\n", Status, LibStatus));
  }

  ///
  /// Read the current TjMax Offset
  ///

  MailboxRead(MAILBOX_TYPE_PCODE, MAILBOX_READ_OC_TJ_MAX_OFFSET_CMD, &CurrentTjMaxOffset, &LibStatus);
  if (LibStatus == PCODE_MAILBOX_CC_SUCCESS) {
    RequestedTjMaxOffset = (UINT8)OverClockingConfig->TjMaxOffset;
    //
    // If needed, write the new TjMax Offset. 0 indicates no offset / keep hardware defaults.
    //
    if ((RequestedTjMaxOffset) && (RequestedTjMaxOffset != CurrentTjMaxOffset)) {
      DEBUG((DEBUG_INFO, "(OC) Current TjMax Offset  = %X\n", CurrentTjMaxOffset));
      DEBUG((DEBUG_INFO, "(OC) Requested TjMax Offset  = %X\n", RequestedTjMaxOffset));

      //
      // Check if TjMax Offset is within acceptable range of 10 to 63.
      //
      if ((RequestedTjMaxOffset >= 10) && (RequestedTjMaxOffset <= 63)) {
        MailboxWrite(MAILBOX_TYPE_PCODE, MAILBOX_WRITE_OC_TJ_MAX_OFFSET_CMD, RequestedTjMaxOffset, &LibStatus);
        if (LibStatus != EFI_SUCCESS) {
          DEBUG((DEBUG_ERROR, "(OC) Failed to change TjMax Offset to %X, mailbox status = %X\n", RequestedTjMaxOffset, LibStatus));
        } else {
          *ResetRequired = TRUE;
        }
      } else {
        DEBUG((DEBUG_INFO, "(OC) Requested TjMax Offset is out of range and will not be applied. Valid Range 10 to 63.\n"));
      }
    }
  }

  ///
  /// Misc Global Config programming
  ///
  ///
  /// Fivr options are reverse encoded in the config block defintion
  /// We need to convert to the mailbox format before writing
  ///
  MiscGlobalConfigData = (UINT32)(((OverClockingConfig->BclkAdaptiveVoltage << MISC_GLOBAL_BCLK_ADAPTIVE_OFFSET) |
                                 ((~OverClockingConfig->FivrEfficiency & BIT0) << MISC_GLOBAL_FIVR_EFFICIENCY_OFFSET) |
                                 (~OverClockingConfig->FivrFaults & BIT0)) & MISC_GLOBAL_CFG_COMMAND_MASK);
  DEBUG ((DEBUG_INFO, "(OC) Set Misc Global Config = %X\n", MiscGlobalConfigData));
  Status = MailboxWrite(MAILBOX_TYPE_OC, OC_LIB_CMD_SET_MISC_GLOBAL_CONFIG, MiscGlobalConfigData, &LibStatus);
  if ((Status != EFI_SUCCESS) || (LibStatus != OC_LIB_COMPLETION_CODE_SUCCESS)) {
    DEBUG ((DEBUG_ERROR, "(OC) Set Misc Global Config Failed. EFI Status = %X, Library Status = %X\n", Status, LibStatus));
  }

  return Status;
}

/**
  Initializes CPU domain voltage settings for overclocking.

  @param[in] OverClockingConfig      Pointer to CPU Overclocking Policy instance

  @retval EFI_SUCCESS
**/
EFI_STATUS
EFIAPI
CpuOcInitVoltageSettings (
  IN OVERCLOCKING_PREMEM_CONFIG *OverClockingConfig
  )
{
  EFI_STATUS              Status;
  OC_CAPABILITIES_ITEM    OcCaps;
  VOLTAGE_FREQUENCY_ITEM  CurrentVfItem;
  VOLTAGE_FREQUENCY_ITEM  RequestedVfItem;
  UINT32                  LibStatus;
  UINT8                   DomainId;
  UINT8                   MinDomainId;
  UINT8                   MaxDomainId;
  WDT_PPI                 *gWdtPei;

  MinDomainId = OC_LIB_DOMAIN_ID_DDR;
  MaxDomainId = OC_LIB_DOMAIN_ID_SYSTEM_AGENT;
  Status = EFI_SUCCESS;

  //
  // Locate WDT_PPI (ICC WDT PPI)
  //
  Status = PeiServicesLocatePpi (
             &gWdtPpiGuid,
             0,
             NULL,
             (VOID **) &gWdtPei
             );
  ASSERT_EFI_ERROR (Status);

  ///
  /// We will loop on the CPU domains to manage the voltage/frequency settings
  ///
  for (DomainId = MinDomainId; DomainId < MaxDomainId; DomainId++) {
    ///
    /// Only IA_CORE and RING is valid for CPU Core
    ///
    if ((DomainId == OC_LIB_DOMAIN_ID_IA_CORE) || (DomainId == OC_LIB_DOMAIN_ID_RING)) {
      ///
      /// Get OC Capabilities of the domain
      ///
      ZeroMem (&OcCaps,sizeof (OcCaps));
      OcCaps.DomainId = DomainId;
      Status = GetOcCapabilities (&OcCaps,&LibStatus);

      if (LibStatus == OC_LIB_COMPLETION_CODE_SUCCESS) {
        ///
        /// If any OC is supported on this domain, then proceed
        ///
        if (OcCaps.RatioOcSupported || OcCaps.VoltageOverridesSupported || OcCaps.VoltageOffsetSupported) {
          ///
          /// Need to populate the user requested settings from the Policy
          /// to determine if OC changes are desired.
          ///
          ZeroMem (&CurrentVfItem,sizeof (CurrentVfItem));
          CurrentVfItem.DomainId = DomainId;

          ///
          /// Get a copy of the current domain VfSettings from the Mailbox Library
          ///
          Status = GetVoltageFrequencyItem (&CurrentVfItem,&LibStatus);
          if ((Status != EFI_SUCCESS) || (LibStatus != OC_LIB_COMPLETION_CODE_SUCCESS)) {
            continue;
          }

          ///
          /// Populate the user requested VfSettings struct
          ///
          ZeroMem (&RequestedVfItem,sizeof (RequestedVfItem));
          RequestedVfItem.DomainId = DomainId;
          if (DomainId == OC_LIB_DOMAIN_ID_IA_CORE) {
            RequestedVfItem.VfSettings.MaxOcRatio = (UINT8) OverClockingConfig->CoreMaxOcRatio;
          } else if (DomainId == OC_LIB_DOMAIN_ID_RING) {
            RequestedVfItem.VfSettings.MaxOcRatio = (UINT8) OverClockingConfig->RingMaxOcRatio;
          }

          ///
          /// VoltageTarget has 2 uses and we need to update the target based
          /// on the voltagemode requested
          ///
          if (DomainId == OC_LIB_DOMAIN_ID_IA_CORE) {
            RequestedVfItem.VfSettings.VoltageTargetMode = (UINT8) OverClockingConfig->CoreVoltageMode;
            if (RequestedVfItem.VfSettings.VoltageTargetMode == OC_LIB_OFFSET_ADAPTIVE) {
              RequestedVfItem.VfSettings.VoltageTarget = OverClockingConfig->CoreVoltageAdaptive;
            } else {
              RequestedVfItem.VfSettings.VoltageTarget = OverClockingConfig->CoreVoltageOverride;
            }
            RequestedVfItem.VfSettings.VoltageOffset = OverClockingConfig->CoreVoltageOffset;
          } else if (DomainId == OC_LIB_DOMAIN_ID_RING) {
            RequestedVfItem.VfSettings.VoltageTargetMode = (UINT8) OverClockingConfig->RingVoltageMode;
            if (RequestedVfItem.VfSettings.VoltageTargetMode == OC_LIB_OFFSET_ADAPTIVE) {
              RequestedVfItem.VfSettings.VoltageTarget = OverClockingConfig->RingVoltageAdaptive;
            } else {
              RequestedVfItem.VfSettings.VoltageTarget = OverClockingConfig->RingVoltageOverride;
            }
            RequestedVfItem.VfSettings.VoltageOffset = OverClockingConfig->RingVoltageOffset;
          }

          ///
          /// Compare current settings with user requested settings to see if changes are needed
          ///
          if (CompareMem ((VOID *)&RequestedVfItem,(VOID *)&CurrentVfItem,sizeof (VOLTAGE_FREQUENCY_ITEM))) {
            ///
            /// Arm watchdog timer for OC changes
            ///
            Status = gWdtPei->ReloadAndStart (WDT_TIMEOUT_BETWEEN_PEI_DXE);

            ///
            /// Need to update the requested voltage/frequency values
            ///
            DEBUG ((DEBUG_INFO, "(OC) Set Voltage Frequency for Domain = %X\n", DomainId));
            DEBUG ((DEBUG_INFO, "(OC) RequestedVfItem.VfSettings.MaxOcRatio     = %X\n", RequestedVfItem.VfSettings.MaxOcRatio));
            DEBUG ((DEBUG_INFO, "(OC) RequestedVfItem.VfSettings.TargetMode     = %X\n", RequestedVfItem.VfSettings.VoltageTargetMode));
            DEBUG ((DEBUG_INFO, "(OC) RequestedVfItem.VfSettings.VoltageTarget  = %X\n", RequestedVfItem.VfSettings.VoltageTarget));
            DEBUG ((DEBUG_INFO, "(OC) RequestedVfItem.VfSettings.VoltageOffset  = %X\n", RequestedVfItem.VfSettings.VoltageOffset));
            DEBUG ((DEBUG_INFO, "(OC) CurrentVfItem.VfSettings.MaxOcRatio       = %X\n", CurrentVfItem.VfSettings.MaxOcRatio));
            DEBUG ((DEBUG_INFO, "(OC) CurrentVfItem.VfSettings.TargetMode       = %X\n", CurrentVfItem.VfSettings.VoltageTargetMode));
            DEBUG ((DEBUG_INFO, "(OC) CurrentVfItem.VfSettings.VoltageTarget    = %X\n", CurrentVfItem.VfSettings.VoltageTarget));
            DEBUG ((DEBUG_INFO, "(OC) CurrentVfItem.VfSettings.VoltageOffset    = %X\n", CurrentVfItem.VfSettings.VoltageOffset));

            Status = SetVoltageFrequencyItem (RequestedVfItem,&LibStatus);
            if ((Status != EFI_SUCCESS) || (LibStatus != OC_LIB_COMPLETION_CODE_SUCCESS)) {
              DEBUG ((DEBUG_ERROR, "(OC) Set Core Voltage Frequency failed. EFI Status = %X, Library Status = %X\n", Status, LibStatus));
            }
          }
        }
      } else {
        DEBUG ((DEBUG_ERROR, "(OC) GetOcCapabilities message failed. Library Status = %X, Domain = %X\n", LibStatus, DomainId));
      }
    }
  }

  return Status;
}

/**
  Initializes pre-memory Overclocking settings in the processor.

  @param[in] OverclockingtConfig      Pointer to Policy protocol instance

  @retval EFI_SUCCESS
**/
EFI_STATUS
EFIAPI
CpuOcInitPreMem (
  IN SI_PREMEM_POLICY_PPI *SiPreMemPolicyPpi
  )
{
  EFI_STATUS    Status;
  OVERCLOCKING_PREMEM_CONFIG *OverClockingConfig;
  BOOLEAN ResetRequired;

  DEBUG((DEBUG_INFO, "CpuOcInitPreMem Start \n"));
  PostCode (0xC26);

  ResetRequired = FALSE;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gOverclockingPreMemConfigGuid, (VOID *) &OverClockingConfig);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Check for Overclocking support
  ///
  if (OverClockingConfig->OcSupport == 0) {
    DEBUG ((DEBUG_INFO, "(OC) Overclocking is disabled. Bypassing CPU core overclocking flow.\n"));
    return EFI_SUCCESS;
  }

  ///
  /// Configure Ring related settings
  ///
  Status = CpuOcInitRingSettings(OverClockingConfig);

  ///
  /// Configure Core related settings
  ///
  Status = CpuOcInitCoreSettings(OverClockingConfig, &ResetRequired);

  ///
  /// Configure OC voltage settings
  ///
  Status = CpuOcInitVoltageSettings(OverClockingConfig);


  ///
  /// Perform Cold Reset if required by Core Pll voltage offset changes
  ///
  if (ResetRequired == TRUE) {
    DEBUG ((DEBUG_INFO, "(OC) Perform Warm Reset\n"));
    DEBUG((DEBUG_INFO, "CpuOcInit Reset \n"));
    PostCode (0xC27);
    PerformWarmOrColdReset (WARM_RESET);
  }

  DEBUG((DEBUG_INFO, "CpuOcInitPreMem End\n"));
  return Status;
}

/**
  This function will perform the BCLK warm reset overclocking flow.

  @param[in] VOID

  @retval EFI_SUCCESS          Function successfully executed.

  Appropriate failure code on error.
**/
EFI_STATUS
EFIAPI
PerformBclkOcFlow (
  VOID
  )
{
  EFI_STATUS        Status;
  WDT_PPI           *WdtPei;
  UINT8             WarmResetRequired;
  UINT8             WdtTimeout;

  Status = EFI_SUCCESS;
  WarmResetRequired = FALSE;
  WdtTimeout = FALSE;

  //
  // Locate WDT_PPI (ICC WDT PPI)
  //
  Status = PeiServicesLocatePpi (
             &gWdtPpiGuid,
             0,
             NULL,
             (VOID **) &WdtPei
             );
  ASSERT_EFI_ERROR (Status);

  //
  // Check for WDT timeout on previous boot
  //
  WdtTimeout = WdtPei->CheckStatus();

  //
  // If no WDT timeout, ramp BCLK, otherwise, continue boot to recover.
  //
  if (WdtTimeout == FALSE) {

    Status = PeiHeciIccBclkMsg (&WarmResetRequired);
    if (EFI_ERROR (Status)) {
      DEBUG((DEBUG_WARN, "(ICC) PeiHeciIccBclkMsg failed with Status = %X\n", Status));
      return Status;
    }
    DEBUG((DEBUG_INFO, "(ICC) PerformBclkOcFlow start.\n"));

    if (WarmResetRequired == 1) {
      DEBUG((DEBUG_INFO, "(ICC) ME FW acknowledged BCLK Ramp reset is required.\n"));

      //
      // Start the Watchdog Timer
      //
      Status = WdtPei->ReloadAndStart (60);
      ASSERT_EFI_ERROR (Status);

      //
      // Warm reset is required for BCLK frequency changes. The BCLK frequency
      // is ramped while the CPU is in reset.
      //
      DEBUG ((DEBUG_INFO, "(ICC) Performing Warm Reset for BCLK frequency change.\n"));
      WdtPei->AllowKnownReset ();
      (*GetPeiServicesTablePointer ())->ResetSystem2 (EfiResetWarm, EFI_SUCCESS, 0, NULL);
    }
  }

  DEBUG((DEBUG_INFO, "(ICC) No BCLK warm reset required.\n"));
  return Status;
}

/**
  Initializes Overclocking settings in the processor.

  @param[in]  OVERCLOCKING_PREMEM_CONFIG  OcConfig

  @retval EFI_SUCCESS
**/
EFI_STATUS
SaOcInit (
  IN   OVERCLOCKING_PREMEM_CONFIG  *OcConfig
  )
{
  EFI_STATUS    Status;
  OC_CAPABILITIES_ITEM OcCaps;
  VOLTAGE_FREQUENCY_ITEM CurrentVfItem;
  VOLTAGE_FREQUENCY_ITEM RequestedVfItem;
  UINT32      LibStatus;
  UINT8       DomainId;
  BOOLEAN     VfUpdateNeeded;
  WDT_PPI     *gWdtPei;
  UINT32      CurrentRealtimeMemory;

  LibStatus = 0;
  VfUpdateNeeded = FALSE;

  DEBUG((DEBUG_INFO, "SaOcInit Start \n"));

  if (OcConfig->OcSupport == FALSE) {
    ///
    /// Overclocking is disabled
    ///
    DEBUG ((DEBUG_INFO, "(OC) Overclocking is disabled. Bypassing SA overclocking flow.\n"));
    return EFI_SUCCESS;
  }

  Status = EFI_SUCCESS;
  ZeroMem (&CurrentVfItem,sizeof (CurrentVfItem));
  ZeroMem (&RequestedVfItem,sizeof (RequestedVfItem));

  //
  // Locate WDT_PPI (ICC WDT PPI)
  //
  Status = PeiServicesLocatePpi (
             &gWdtPpiGuid,
             0,
             NULL,
             (VOID **) &gWdtPei
             );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Update Realtime Memory Timings if needed
  ///
  MailboxRead(MAILBOX_TYPE_OC, OC_LIB_CMD_GET_REALTIME_MEMORY_STATUS, &CurrentRealtimeMemory, &LibStatus);
  if (OcConfig->RealtimeMemoryTiming != CurrentRealtimeMemory) {
    DEBUG ((DEBUG_INFO, "(OC) Current Realtime Memory Timing = %X\n", CurrentRealtimeMemory));
    DEBUG ((DEBUG_INFO, "(OC) Requested Realtime Memory Timing = %X\n", OcConfig->RealtimeMemoryTiming));
    MailboxWrite(MAILBOX_TYPE_OC, OC_LIB_CMD_SET_REALTIME_MEMORY_STATUS, OcConfig->RealtimeMemoryTiming, &LibStatus);
    if (LibStatus != EFI_SUCCESS) {
      DEBUG ((DEBUG_INFO, "(OC) Set Realtime Memory Timing Status failed, mailbox status = %X\n", LibStatus));
    }
  }

  ///
  /// We will loop on the CPU domains to manage the voltage/frequency settings
  ///
  for (DomainId = OC_LIB_DOMAIN_ID_GT; DomainId <= OC_LIB_DOMAIN_ID_SYSTEM_AGENT; DomainId++) {
    ///
    /// Only GT, Uncore, IOA, and IOD are valid for System Agent
    ///
    if (DomainId != OC_LIB_DOMAIN_ID_RING) {
      ///
      /// Get OC Capabilities of the domain
      ///
      ZeroMem (&OcCaps,sizeof (OcCaps));
      OcCaps.DomainId = DomainId;
      Status = GetOcCapabilities (&OcCaps,&LibStatus);

      if (LibStatus == OC_LIB_COMPLETION_CODE_SUCCESS) {
        ///
        /// If any OC is supported on this domain, then proceed
        ///
        if (OcCaps.RatioOcSupported || OcCaps.VoltageOverridesSupported || OcCaps.VoltageOffsetSupported) {
          ///
          /// Need to populate the user requested settings from the policy
          /// to determine if OC changes are desired.
          ///
          ZeroMem (&CurrentVfItem,sizeof (CurrentVfItem));
          CurrentVfItem.DomainId = DomainId;

          ///
          /// Get a copy of the current domain VfSettings from the Mailbox Library
          ///
          Status = GetVoltageFrequencyItem (&CurrentVfItem,&LibStatus);
          if ((Status != EFI_SUCCESS) || (LibStatus != OC_LIB_COMPLETION_CODE_SUCCESS)) {
            continue;
          }

          ///
          /// Populate the user requested VfSettings struct
          ///
          ZeroMem (&RequestedVfItem,sizeof (RequestedVfItem));
          RequestedVfItem.DomainId = DomainId;
          switch (DomainId) {
            case OC_LIB_DOMAIN_ID_GT:
              RequestedVfItem.VfSettings.MaxOcRatio = (UINT8) OcConfig->GtMaxOcRatio;

              ///
              /// VoltageTarget has 2 uses and we need to update the target based
              /// on the voltagemode requested
              ///
              RequestedVfItem.VfSettings.VoltageTargetMode = (UINT8) OcConfig->GtVoltageMode;
              if (RequestedVfItem.VfSettings.VoltageTargetMode == OC_LIB_OFFSET_ADAPTIVE) {
                RequestedVfItem.VfSettings.VoltageTarget = OcConfig->GtExtraTurboVoltage;
              }
              else {
                RequestedVfItem.VfSettings.VoltageTarget = OcConfig->GtVoltageOverride;
              }
              RequestedVfItem.VfSettings.VoltageOffset = OcConfig->GtVoltageOffset;
              break;

            case OC_LIB_DOMAIN_ID_SYSTEM_AGENT:
              RequestedVfItem.VfSettings.VoltageOffset = OcConfig->SaVoltageOffset;
              break;
          }
          VfUpdateNeeded = (BOOLEAN) CompareMem ((VOID*)&RequestedVfItem,(VOID*)&CurrentVfItem,sizeof (VOLTAGE_FREQUENCY_ITEM));

          if (VfUpdateNeeded) {
            VfUpdateNeeded = FALSE;

            ///
            /// Arm watchdog timer for OC changes
            ///
            Status = gWdtPei->ReloadAndStart (WDT_TIMEOUT_BETWEEN_PEI_DXE);

            ///
            /// Need to update the requested voltage/frequency values
            ///
            DEBUG ((DEBUG_INFO, "(OC) Set Voltage Frequency for Domain = %X\n", DomainId));
            DEBUG ((DEBUG_INFO, "(OC) RequestedVfItem.VfSettings.MaxOcRatio     = %X\n", RequestedVfItem.VfSettings.MaxOcRatio));
            DEBUG ((DEBUG_INFO, "(OC) RequestedVfItem.VfSettings.TargetMode     = %X\n", RequestedVfItem.VfSettings.VoltageTargetMode));
            DEBUG ((DEBUG_INFO, "(OC) RequestedVfItem.VfSettings.VoltageTarget  = %X\n", RequestedVfItem.VfSettings.VoltageTarget));
            DEBUG ((DEBUG_INFO, "(OC) RequestedVfItem.VfSettings.VoltageOffset  = %X\n", RequestedVfItem.VfSettings.VoltageOffset));
            DEBUG ((DEBUG_INFO, "(OC) CurrentVfItem.VfSettings.MaxOcRatio       = %X\n", CurrentVfItem.VfSettings.MaxOcRatio));
            DEBUG ((DEBUG_INFO, "(OC) CurrentVfItem.VfSettings.TargetMode       = %X\n", CurrentVfItem.VfSettings.VoltageTargetMode));
            DEBUG ((DEBUG_INFO, "(OC) CurrentVfItem.VfSettings.VoltageTarget    = %X\n", CurrentVfItem.VfSettings.VoltageTarget));
            DEBUG ((DEBUG_INFO, "(OC) CurrentVfItem.VfSettings.VoltageOffset    = %X\n", CurrentVfItem.VfSettings.VoltageOffset));

            Status = SetVoltageFrequencyItem (RequestedVfItem,&LibStatus);
            if ((Status != EFI_SUCCESS) || (LibStatus != OC_LIB_COMPLETION_CODE_SUCCESS)) {
              DEBUG ((DEBUG_WARN, "(OC) Set Voltage Frequency failed. EFI Status = %X, Library Status = %X\n", Status, LibStatus));
            }
          }
        }
        else {
          DEBUG ((DEBUG_INFO, "(OC) No OC support for this Domain = %X\n", DomainId));
        }
      }
      else {
        DEBUG ((DEBUG_WARN, "(OC) GetOcCapabilities message failed. Library Status = %X, Domain = %X\n", LibStatus, DomainId));
      }
    }
  }

  Status = PerformBclkOcFlow();
  DEBUG((DEBUG_INFO, "(ICC) PerformBclkOcFlow status = %X.\n", Status));

  return Status;
}
