/** @file
  PEIM to initialize IGFX.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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

@par Specification Reference:
**/
#include <Library/PeiServicesLib.h>
#include <Library/IoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/PciSegmentLib.h>
#include <IndustryStandard/Pci.h>
#include <Library/PeiGraphicsInitLib.h>
#include <Library/SaInitLib.h>
#include <Library/TimerLib.h>
#include <CpuRegs.h>
#include <Library/CpuPlatformLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/PchInfoLib.h>
#include <Library/PeiSaPolicyLib.h>
#include <Ppi/Spi.h>
#include <Library/PciExpressLib.h>
#include <Register/IgdRegs.h>
/**
  Check and Force Vdd On based on the H/W Status

  @param[in] GRAPHICS_PEI_PREMEM_CONFIG   GtPreMemConfig

  @retval EFI_NOT_READY                   H/W Power Cycle sequence in progress, Vdd on not enabled
  @retval EFI_SUCCESS                     Vdd On already enabled or enabled successfully

**/
STATIC EFI_STATUS
CheckAndForceVddOn (
  IN   GRAPHICS_PEI_PREMEM_CONFIG      *GtPreMemConfig
  )
{
  UINTN                   GttMmAdr;
  UINTN                   GmAdr;
  UINT64                  McD2BaseAddress;
  UINT32                  Msac;
  EFI_STATUS              Status;

  Status = EFI_SUCCESS;
  McD2BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, 0);
  Msac = PciSegmentRead32(McD2BaseAddress + R_SA_IGD_MSAC_OFFSET);
  ///
  /// Check if GttMmAdr has been already assigned, initialize if not
  ///
  GttMmAdr = (PciSegmentRead32(McD2BaseAddress + R_SA_IGD_GTTMMADR)) & 0xFFFFFFF0;
  if (GttMmAdr == 0) {
    GttMmAdr = GtPreMemConfig->GttMmAdr;
    GmAdr    = GtPreMemConfig->GmAdr;

    PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR, (UINT32) (GttMmAdr & 0xFF000000));
    GttMmAdr = (PciSegmentRead32(McD2BaseAddress + R_SA_IGD_GTTMMADR)) & 0xFFFFFFF0;
    PciSegmentAndThenOr32(McD2BaseAddress + R_SA_IGD_MSAC_OFFSET, (UINT32)~(BIT20 + BIT19 + BIT18 + BIT17 + BIT16), SA_GT_APERTURE_SIZE_256MB << 16);
    PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_GMADR, GmAdr);
  }

  if (!IgfxCmdRegEnabled()) {
    ///
    /// Enable Bus Master and Memory access on 0:2:0
    ///
    PciSegmentOr16(McD2BaseAddress + R_SA_IGD_CMD, (BIT2 | BIT1));
  }

  ///
  /// Skip if VDD Bit is already set
  ///
  if ((MmioRead32 (GttMmAdr + R_SA_GTTMMADR_PP_CONTROL) & BIT3) == 0 ) {
    if ((MmioRead32(GttMmAdr + R_SA_GTTMMADR_PP_STATUS) & (BIT29|BIT28|BIT27)) == 0 ) {
      ///
      /// Panel Power Enable - VDD bit, as H/W Power cycle sequence completed
      ///
      MmioOr32 (GttMmAdr + R_SA_GTTMMADR_PP_CONTROL, (UINT32) BIT3);
    } else {
      Status = EFI_NOT_READY;
    }
  }

  ///
  /// Program Aperture Size MSAC register based on policy
  ///
  PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_MSAC_OFFSET, Msac);

  return Status;
}

/**
  Check and Force Vdd On in End Of PEI

  @retval EFI_NOT_READY                   H/W Power Cycle sequence in progress, Vdd on not enabled or Policy not found
  @retval EFI_SUCCESS                     Vdd On already enabled or enabled successfully

**/
EFI_STATUS
EndOfPeiCheckAndForceVddOn (
  VOID
  )
{
  SI_PREMEM_POLICY_PPI        *SiPreMemPolicyPpi;
  SI_POLICY_PPI               *SiPolicyPpi;
  GRAPHICS_PEI_PREMEM_CONFIG  *GtPreMemConfig;
  GRAPHICS_PEI_CONFIG         *GtConfig;
  EFI_STATUS                   Status;
  EFI_BOOT_MODE                BootMode;

  Status = EFI_SUCCESS;

  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR (Status);

  if (BootMode != BOOT_ON_S3_RESUME) {
    DEBUG ((DEBUG_INFO, "EndOfPeiCheckAndForceVddOn start\n"));
    ///
    /// Get SA Policy settings through the SaInitConfigBlock PPI
    ///
    Status = PeiServicesLocatePpi (
               &gSiPreMemPolicyPpiGuid,
               0,
               NULL,
               (VOID **) &SiPreMemPolicyPpi
               );
    if (EFI_ERROR (Status) || (SiPreMemPolicyPpi == NULL)) {
      return EFI_NOT_FOUND;
    }
    Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gGraphicsPeiPreMemConfigGuid, (VOID *) &GtPreMemConfig);
    ASSERT_EFI_ERROR (Status);

    if (GtPreMemConfig->PanelPowerEnable == 1) {
      ///
      /// Get policy settings through the SiSaPolicyPpi
      ///
      Status = PeiServicesLocatePpi (
                 &gSiPolicyPpiGuid,
                 0,
                 NULL,
                 (VOID **) &SiPolicyPpi
                 );
      if ((EFI_ERROR (Status)) || (SiPolicyPpi == NULL)) {
        return EFI_NOT_FOUND;
      }
      Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gGraphicsPeiConfigGuid, (VOID *) &GtConfig);
      ASSERT_EFI_ERROR (Status);

      ///
      /// Enable Panel Power (VDD bit), only when PEIM Graphics init is disabled
      ///
      if (GtConfig->PeiGraphicsPeimInit == 0) {
        Status = CheckAndForceVddOn (GtPreMemConfig);
      }
    }
    DEBUG ((DEBUG_INFO, "EndOfPeiCheckAndForceVddOn end status - 0x%x\n", Status));
  }

  return Status;
}

/**
  Check and Force Vdd On in PostMem Phase

  @param[in] GRAPHICS_PEI_PREMEM_CONFIG      GtPreMemConfig
  @param[in] GRAPHICS_PEI_CONFIG             GtConfig

**/
VOID
PostMemCheckAndForceVddOn (
  IN   GRAPHICS_PEI_PREMEM_CONFIG      *GtPreMemConfig,
  IN   GRAPHICS_PEI_CONFIG             *GtConfig
  )
{
  EFI_STATUS              Status;
  EFI_BOOT_MODE           BootMode;

  Status = EFI_SUCCESS;

  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR (Status);

  if ((GtPreMemConfig->PanelPowerEnable == 1) && (BootMode != BOOT_ON_S3_RESUME)) {
    DEBUG ((DEBUG_INFO, "PostMemCheckAndForceVddOn start\n"));
    Status = CheckAndForceVddOn(GtPreMemConfig);
    DEBUG ((DEBUG_INFO, "PostMemCheckAndForceVddOn end status - 0x%x\n", Status));
  }
}


/**
  InitializeDisplayAudio: Initialize display engine for iDisplay Audio programming.

  This function is called by PCH Init Pre-mem code to program CD clock freq.
  CD clock program steps involve enable PG1 & PG2 and P-code notification.

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_ABORTED             S3 boot - display already initialized
  @retval EFI_UNSUPPORTED         iGfx disabled, iDisplay Audio not present
  @retval EFI_NOT_FOUND           SaPolicy or temporary GTT base address not found
**/
EFI_STATUS
InitializeDisplayAudio (
  VOID
  )
{
  UINT64                      McD2BaseAddress;
  SI_PREMEM_POLICY_PPI        *SiPreMemPolicyPpi;
  GRAPHICS_PEI_PREMEM_CONFIG  *GtPreMemConfig;
  UINTN                        GttMmAdr;
  UINTN                        GmAdr;
  EFI_STATUS                   Status;
  UINT32                       Msac;

  DEBUG ((DEBUG_INFO, "InitializeDisplayAudio() Start\n"));

  McD2BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, 0);
  Msac = PciSegmentRead32(McD2BaseAddress + R_SA_IGD_MSAC_OFFSET);

  if (PciSegmentRead16 (McD2BaseAddress + R_SA_IGD_VID) == 0xFFFF) {
    DEBUG ((DEBUG_INFO, "iGFX not enabled - iDisplayAudio not supported - Exit!\n"));
    return EFI_UNSUPPORTED;
  }

  ///
  /// Check if GttMmAdr has been already assigned, initialize if not
  ///
  GttMmAdr = (PciSegmentRead32 (McD2BaseAddress + R_SA_IGD_GTTMMADR)) & 0xFFFFFFF0;
  if (GttMmAdr == 0) {
    ///
    /// Get SA Policy settings through the SaInitConfigBlock PPI
    ///
    Status = PeiServicesLocatePpi (
               &gSiPreMemPolicyPpiGuid,
               0,
               NULL,
               (VOID **) &SiPreMemPolicyPpi
               );
    if (EFI_ERROR (Status) || (SiPreMemPolicyPpi == NULL)) {
      DEBUG ((DEBUG_WARN, "SaPolicy PPI not found - Exit!\n"));
      return EFI_NOT_FOUND;
    }

    Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gGraphicsPeiPreMemConfigGuid, (VOID *) &GtPreMemConfig);
    ASSERT_EFI_ERROR (Status);

    GttMmAdr = GtPreMemConfig->GttMmAdr;
    GmAdr    = GtPreMemConfig->GmAdr;

    if (GttMmAdr == 0) {
      DEBUG ((DEBUG_WARN, "Temporary GttMmAdr Bar is not initialized - Exit!\n"));
      return EFI_NOT_FOUND;
    }

    ///
    /// Program and read back GTT Memory Mapped BAR
    ///
    PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR, (UINT32) (GttMmAdr & 0xFF000000));
    GttMmAdr = (PciSegmentRead32 (McD2BaseAddress + R_SA_IGD_GTTMMADR)) & 0xFFFFFFF0;

    PciSegmentAndThenOr32(McD2BaseAddress + R_SA_IGD_MSAC_OFFSET, (UINT32)~(BIT20 + BIT19 + BIT18 + BIT17 + BIT16), SA_GT_APERTURE_SIZE_256MB << 16);
    PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_GMADR, GmAdr);
  }

  if (!IgfxCmdRegEnabled()) {
    ///
    /// Enable Bus Master and Memory access on 0:2:0 if not enabled
    ///
    PciSegmentOr16 (McD2BaseAddress + R_SA_IGD_CMD, (BIT2 | BIT1));
  }
  //
  // Enable PCH Reset Handshake
  //
  MmioOr32 ((GttMmAdr + R_SA_GTTMMADR_NDE_RSTWRN_OPT_OFFSET), BIT4);
  //
  // Enable Display Power Well
  //
  EnablePowerWell (GttMmAdr);
  //
  // Enable Audio Buffer
  //
  MmioOr32 (GttMmAdr + R_SA_GTTMMADR_AUDIO_PIN_BUF_CTL_OFFSET, B_SA_GTTMMADR_AUDIO_PIN_BUF_CTL_ENABLE);
  ///
  /// Program Aperture Size MSAC register based on policy
  ///
  PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_MSAC_OFFSET, Msac);

  DEBUG ((DEBUG_INFO, "InitializeDisplayAudio() End\n"));
  return EFI_SUCCESS;
}

/**
  ConfigureIDispAudioFrequency: Configures iDisplay Audio BCLK frequency and T-Mode

  @param[in] RequestedBclkFrequency     IDisplay Link clock frequency to be set
  @param[in] RequestedTmode             IDisplay Link T-Mode to be set

  @retval EFI_NOT_FOUND                 SA Policy PPI or GT config block not found, cannot initialize GttMmAdr
  @retval EFI_UNSUPPORTED               iDisp link unsupported frequency
  @retval EFI_SUCCESS                   The function completed successfully
**/
EFI_STATUS
ConfigureIDispAudioFrequency (
  IN       HDAUDIO_LINK_FREQUENCY   RequestedBclkFrequency,
  IN       HDAUDIO_IDISP_TMODE      RequestedTmode
  )
{
  UINT64                     McD2BaseAddress;
  SI_POLICY_PPI             *SiPreMemPolicyPpi;
  GRAPHICS_PEI_PREMEM_CONFIG *GtPreMemConfig;
  UINTN                      GttMmAdr;
  UINTN                      GmAdr;
  UINT32                     Data32And;
  UINT32                     Data32Or;
  EFI_STATUS                 Status;
  UINT32                     Msac;

  DEBUG ((DEBUG_INFO, "ConfigureIDispAudioFrequency() Start\n"));
  McD2BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, 0);
  Msac = PciSegmentRead32 (McD2BaseAddress + R_SA_IGD_MSAC_OFFSET);

  if (PciSegmentRead16 (McD2BaseAddress + R_SA_IGD_VID) == 0xFFFF) {
    DEBUG ((DEBUG_INFO, "iGFX not enabled - frequency switching for iDisplay link not supported - Exit!\n"));
    return EFI_UNSUPPORTED;
  }

  ///
  /// Check if GttMmAdr has been already assigned, initialize if not
  ///
  GttMmAdr = (PciSegmentRead32 (McD2BaseAddress + R_SA_IGD_GTTMMADR)) & 0xFFFFFFF0;
  if (GttMmAdr == 0) {
    ///
    /// Get SA Policy settings through the SaInitConfigBlock PPI
    ///
    Status = PeiServicesLocatePpi (
               &gSiPreMemPolicyPpiGuid,
               0,
               NULL,
               (VOID **) &SiPreMemPolicyPpi
               );
    if (EFI_ERROR (Status) || (SiPreMemPolicyPpi == NULL)) {
      DEBUG ((DEBUG_WARN, "SaPolicy PPI not found - Exit!\n"));
      return EFI_NOT_FOUND;
    }

    Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gGraphicsPeiPreMemConfigGuid, (VOID *) &GtPreMemConfig);
    ASSERT_EFI_ERROR (Status);

    GttMmAdr = GtPreMemConfig->GttMmAdr;
    GmAdr    = GtPreMemConfig->GmAdr;

    if (GttMmAdr == 0) {
      DEBUG ((DEBUG_WARN, "Temporary GttMmAdr Bar is not initialized - Exit!\n"));
      return EFI_NOT_FOUND;
    }

    ///
    /// Program and read back GTT Memory Mapped BAR
    ///
    PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR, (UINT32) (GttMmAdr & 0xFF000000));
    GttMmAdr = (PciSegmentRead32 (McD2BaseAddress + R_SA_IGD_GTTMMADR)) & 0xFFFFFFF0;
    PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_GMADR, GmAdr);
    PciSegmentAndThenOr32(McD2BaseAddress + R_SA_IGD_MSAC_OFFSET, (UINT32)~(BIT20 + BIT19 + BIT18 + BIT17 + BIT16), SA_GT_APERTURE_SIZE_256MB << 16);
  }

  switch (RequestedBclkFrequency) {
    case HdaLinkFreq96MHz:
      //
      // SA IGD: GttMmAdr + 0x65900[4:3] = 10b (96MHz)
      //
      Data32And = (UINT32) ~(B_SA_IGD_AUD_FREQ_CNTRL_48MHZ);
      Data32Or  = (UINT32) B_SA_IGD_AUD_FREQ_CNTRL_96MHZ;
      break;
    case HdaLinkFreq48MHz:
      //
      // SA IGD: GttMmAdr + 0x65900[4:3] = 01b (48MHz)
      //
      Data32And = (UINT32) ~(B_SA_IGD_AUD_FREQ_CNTRL_96MHZ);
      Data32Or  = (UINT32) B_SA_IGD_AUD_FREQ_CNTRL_48MHZ;
      break;
    default:
      DEBUG ((DEBUG_WARN, "SA iGFX: Unsupported iDisplay Audio link frequency - Exit!\n"));
      return EFI_UNSUPPORTED;
  }

  Data32And &= (UINT32) ~(B_SA_IGD_AUD_FREQ_CNTRL_TMODE);
  switch (RequestedTmode) {
    case HdaIDispMode2T:
      //
      // SA IGD: GttMmAdr + 0x65900[15:14] = 01b (2T)
      //
      Data32Or |= (UINT32) (V_SA_IGD_AUD_FREQ_CNTRL_TMODE_2T << N_SA_IGD_AUD_FREQ_CNTRL_TMODE);
      break;
    case HdaIDispMode4T:
      //
      // SA IGD: GttMmAdr + 0x65900[15:14] = 00b (4T)
      //
      Data32Or |= (UINT32) (V_SA_IGD_AUD_FREQ_CNTRL_TMODE_4T << N_SA_IGD_AUD_FREQ_CNTRL_TMODE);
      break;
    case HdaIDispMode8T:
      //
      // SA IGD: GttMmAdr + 0x65900[15:14] = 10b (8T)
      //
      Data32Or |= (UINT32) (V_SA_IGD_AUD_FREQ_CNTRL_TMODE_8T << N_SA_IGD_AUD_FREQ_CNTRL_TMODE);
      break;
    case HdaIDispMode16T:
      //
      // SA IGD: GttMmAdr + 0x65900[15:14] = 11b (16T)
      //
      Data32Or |= (UINT32) (V_SA_IGD_AUD_FREQ_CNTRL_TMODE_16T << N_SA_IGD_AUD_FREQ_CNTRL_TMODE);
      break;
    default:
      DEBUG ((DEBUG_WARN, "SA iGFX: Unsupported iDisplay Audio T-mode - Exit!\n"));
      return EFI_UNSUPPORTED;
  }

  if (!IgfxCmdRegEnabled()) {
    ///
    /// Enable Bus Master and Memory access on 0:2:0
    ///
    PciSegmentOr16 (McD2BaseAddress + R_SA_IGD_CMD, (BIT2 | BIT1));
  }

  ///
  /// Program iDisplay Audio link frequency and T-mode
  ///
  MmioAndThenOr32 ((UINTN) (GttMmAdr + R_SA_IGD_AUD_FREQ_CNTRL_OFFSET), Data32And, Data32Or);

  ///
  /// Program iDisplay Audio detect Frame sync early
  ///
  MmioAndThenOr32 ((UINTN) (GttMmAdr + R_SA_IGD_AUD_FREQ_CNTRL_OFFSET),
    (UINT32) ~B_SA_IGD_AUD_FREQ_CNTRL_BCLKS,
    V_SA_IGD_AUD_FREQ_CNTRL_1BCLKS << N_SA_IGD_AUD_FREQ_CNTRL_BCLKS);

  DEBUG ((DEBUG_INFO, "SA iGFX: iDisplay Audio link frequency setting: 0x%X\n", MmioRead32 ((UINTN) (GttMmAdr + R_SA_IGD_AUD_FREQ_CNTRL_OFFSET))));

  ///
  /// Program Aperture Size MSAC register based on policy
  ///
  PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_MSAC_OFFSET, Msac);

  DEBUG ((DEBUG_INFO, "ConfigureIDispAudioFrequency() End\n"));
  return EFI_SUCCESS;
}

/**
  GraphicsInit: Initialize the IGD if no other external graphics is present

  @param[in] GtPreMemConfig       - GtPreMemConfig to access the GtPreMemConfig related information
  @param[in] PrimaryDisplay       - Primary Display - default is IGD
  @param[in, out] PegMmioLength   - Total IGFX MMIO length

**/
VOID
GraphicsInit (
  IN       GRAPHICS_PEI_PREMEM_CONFIG   *GtPreMemConfig,
  IN       DISPLAY_DEVICE               *PrimaryDisplay,
  IN       UINT32                       *IGfxMmioLength
  )
{
  UINT8                   GMSData;
  BOOLEAN                 IGfxSupported;
  EFI_STATUS              Status;
  UINTN                   GttMmAdr;
  UINTN                   GmAdr;
  UINT64                  McD0BaseAddress;
  UINT64                  McD2BaseAddress;
  UINT32                  Data32H;
  EFI_BOOT_MODE           BootMode;
  BOOLEAN                 IsMmioLengthInfoRequired;
  UINT32                  Data32;
  UINT32                  Data32Mask;

  DEBUG ((DEBUG_INFO, "iGFX initialization start\n"));

  IsMmioLengthInfoRequired = FALSE;
  *IGfxMmioLength   = 0;
  GttMmAdr          = 0;
  McD0BaseAddress   = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, 0);
  McD2BaseAddress   = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, 0);

  ///
  /// Get the boot mode
  ///
  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Check if IGfx is supported
  ///
  IGfxSupported = (BOOLEAN) (PciSegmentRead16 (McD2BaseAddress + R_SA_IGD_VID) != 0xFFFF);
  if (!IGfxSupported) {
    DEBUG ((DEBUG_INFO, "iGFX is unsupported or disabled!\n"));
    AdditionalStepsForDisablingIgfx (GtPreMemConfig);
    return;
  }

  ///
  /// Temporarily program GttMmAdr
  ///
  GttMmAdr = GtPreMemConfig->GttMmAdr;
  GmAdr    = GtPreMemConfig->GmAdr;

  if (GttMmAdr == 0) {
    DEBUG ((DEBUG_INFO, "Temporary GttMmAdr Bar is not initialized. Returning from GraphicsInit().\n"));
    return;
  }

  ///
  /// Program GttMmAdr
  /// set [23:0] = 0
  ///
  GttMmAdr = (UINT32) (GttMmAdr & 0xFF000000);
  PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR, GttMmAdr);
  PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_GMADR, GmAdr);
  DEBUG ((DEBUG_INFO, "GTBaseAddress 0X%x:\n", GttMmAdr));
  ///
  /// Read back the programmed GttMmAdr
  ///
  GttMmAdr = (PciSegmentRead32 (McD2BaseAddress + R_SA_IGD_GTTMMADR)) & 0xFFFFFFF0;

  ///
  /// Enable Bus Master and Memory access on 0:2:0
  ///
  PciSegmentOr16 (McD2BaseAddress + R_SA_IGD_CMD, (BIT2 | BIT1));

  ///
  /// If primary display device is IGD or no other display detected then enable IGD
  ///
  if (IGfxSupported &&
      (
        (
          ((*PrimaryDisplay == IGD) || (GtPreMemConfig->PrimaryDisplay == IGD)) &&
          (GtPreMemConfig->InternalGraphics != DISABLED)
          ) || (GtPreMemConfig->InternalGraphics == ENABLED)
        )
      ) {

    DEBUG ((DEBUG_INFO, "IGD enabled.\n"));


    ///
    /// Program GFX Memory
    ///
    GMSData = (UINT8) (GtPreMemConfig->IgdDvmt50PreAlloc);
    ///
    /// Description of GMS D0:F0:R50h[15:8]
    ///
    PciSegmentAnd16 (McD0BaseAddress + R_SA_GGC, (UINT16) ~(B_SA_GGC_GMS_MASK));
    PciSegmentOr16 (McD0BaseAddress + R_SA_GGC, (GMSData & 0xFF) << N_SA_GGC_GMS_OFFSET);
    ///
    /// Program Graphics GTT Memory D0:F0:R50h[7:6]
    ///   00b => 0MB of GTT
    ///   01b => 2MB of GTT
    ///   10b => 4MB of GTT
    ///   11b => 8MB of GTT
    ///
    if (GtPreMemConfig->GttSize != V_SA_GGC_GGMS_DIS) {
      ASSERT (GtPreMemConfig->GttSize <= 3);
      PciSegmentAndThenOr16 (McD0BaseAddress + R_SA_GGC, (UINT16) ~(B_SA_GGC_GGMS_MASK), (GtPreMemConfig->GttSize << N_SA_GGC_GGMS_OFFSET) & B_SA_GGC_GGMS_MASK);
    }
    ///
    /// Set register D2.F0.R 062h [4:0] = `00001b' to set a 256MByte aperture.
    /// This must be done before Device 2 registers are enumerated.
    ///
    ///
    /// Set register D2.F0.R 060h [20:16] = `00001b' to set a 256MByte aperture.
    /// This must be done before Device 2 registers are enumerated.
    ///
    PciSegmentAndThenOr32 (McD2BaseAddress + R_SA_IGD_MSAC_OFFSET, (UINT32)~(BIT20 + BIT19 + BIT18 + BIT17 + BIT16), SA_GT_APERTURE_SIZE_256MB << 16);

    ///
    /// Enable IGD VGA Decode.  This is needed so the Class Code will
    /// be correct for the IGD Device when determining which device
    /// should be primary.  If disabled, IGD will show up as a non VGA device.
    ///
    if ((GtPreMemConfig->PrimaryDisplay != IGD) && (*PrimaryDisplay != IGD)) {
      ///
      /// If IGD is forced to be enabled, but is a secondary display, disable IGD VGA Decode
      ///
      PciSegmentOr16 (McD0BaseAddress + R_SA_GGC, B_SA_GGC_IVD_MASK);
      DEBUG ((DEBUG_INFO, "IGD VGA Decode is disabled because it's not a primary display.\n"));
    } else {
      PciSegmentAnd16 (McD0BaseAddress + R_SA_GGC, (UINT16) ~(B_SA_GGC_IVD_MASK));
    }
    if ((GtPreMemConfig->PanelPowerEnable == 1) && (BootMode != BOOT_ON_S3_RESUME)) {
      ///
      /// Enable Panel Power(VDD bit) if there is no H/W Power sequence restriction.
      /// Will check and enable it in Post Mem (SaInit()) and at End Of PEI, if H/W Power sequence is not done here.
      ///
      if ( (MmioRead32(GttMmAdr + R_SA_GTTMMADR_PP_STATUS) & (BIT29|BIT28|BIT27)) == 0 ) {
        ///
        /// Panel Power Enable - VDD bit
        ///
        MmioOr32 (GttMmAdr + R_SA_GTTMMADR_PP_CONTROL, (UINT32) BIT3);
      }
    }

    ///
    /// Get Mmio length of iGFX later for dynamic TOLUD support
    ///
    IsMmioLengthInfoRequired = TRUE;
    ///
    /// Copy MSR_PLATFORM_INFO.SAMPLE_PART(FUSE_PROD_PART) bit to CONFIG0 Address D00h, bit 30.
    ///
    Data32 = ((UINT32) AsmReadMsr64 (MSR_PLATFORM_INFO) & B_MSR_PLATFORM_INFO_SAMPLE_PART_MASK) << 3;
    Data32Mask = BIT30;
    MmioAndThenOr32 (GttMmAdr + 0xD00, Data32Mask,Data32);
    DEBUG ((DEBUG_INFO, "Update CONFIG0 Address D00 : %x\n",MmioRead32 (GttMmAdr + 0xD00)));

    DEBUG ((DEBUG_INFO, "Configuring iTouch Source Registers Doorbell and GSA_Touch \n"));
    ///
    /// Configure Doorbell Register 0x10c008 BDF bits[15:0] with Bus Device Function of DoorBell Source HECI Device 0/22/4.
    /// Configure GSA_Touch Register 0x101078 BDF bits[31:16] with Bus Device Function of DoorBell Source HECI Device 0/22/4.
    ///
    Data32H = MmioRead32 (GttMmAdr + R_SA_GTTMMADR_GTDOORBELL_OFFSET);
    Data32H = ((Data32H & 0xFFFF0000) | (PCI_EXPRESS_LIB_ADDRESS (GSA_TOUCH_BUS, GSA_TOUCH_DEV, GSA_TOUCH_FUN, 0) >> 12)); // Program Bus 0, Device 22, Func 4

    Data32 = MmioRead32 (GttMmAdr + R_SA_GTTMMADR_GSA_TOUCH_OFFSET);
    Data32 = ((Data32 & 0x0000FFFF) | (PCI_EXPRESS_LIB_ADDRESS (GSA_TOUCH_BUS, GSA_TOUCH_DEV, GSA_TOUCH_FUN, 0) << 4)); // Program Bus 0, Device 22, Func 4

    MmioWrite32 (GttMmAdr + R_SA_GTTMMADR_GTDOORBELL_OFFSET, Data32H);
    MmioWrite32 (GttMmAdr + R_SA_GTTMMADR_GSA_TOUCH_OFFSET, Data32);

    ///
    /// Configure GSA_Audio Register 0x101074 BDF bits[31:16] with Bus Device Function 0/31/3.
    ///
    Data32 = MmioRead32 (GttMmAdr + R_SA_GTTMMADR_GSA_AUDIO_OFFSET);
    Data32 = ((Data32 & 0x0000FFFF) | (PCI_EXPRESS_LIB_ADDRESS (GSA_AUDIO_BUS, GSA_AUDIO_DEV, GSA_AUDIO_FUN, 0) << 4)); // Program Bus 0, Device 31, Func 3

    MmioWrite32 (GttMmAdr + R_SA_GTTMMADR_GSA_AUDIO_OFFSET, Data32);
  } else {
    AdditionalStepsForDisablingIgfx (GtPreMemConfig);
  }

  ///
  /// Program Aperture Size MSAC register based on policy
  ///
  PciSegmentAndThenOr32 (McD2BaseAddress + R_SA_IGD_MSAC_OFFSET, (UINT32)~(BIT20 + BIT19 + BIT18 + BIT17 + BIT16), (UINT32)GtPreMemConfig->ApertureSize << 16);

  ///
  /// Get Mmio length of iGFX for dynamic TOLUD support
  ///
  if (IsMmioLengthInfoRequired) {
    FindPciDeviceMmioLength (SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, IGfxMmioLength);
  }
  DEBUG ((DEBUG_INFO, "iGFX initialization end\n"));
}

/**
  "Poll Status" for GT Readiness

  @param[in] Base            - Base address of MMIO
  @param[in] Offset          - MMIO Offset
  @param[in] Mask            - Mask
  @param[in] Result          - Value to wait for

  @retval EFI_SUCCESS          Wait Bit Successfully set
  @retval EFI_TIMEOUT          Timed out
**/
EFI_STATUS
PollGtReady (
  IN       UINT64                       Base,
  IN       UINT32                       Offset,
  IN       UINT32                       Mask,
  IN       UINT32                       Result
  )
{
  UINT32  GtStatus;
  UINT32  StallCount;

  StallCount = 0;

  ///
  /// Register read
  ///
  GtStatus = MmioRead32 ((UINTN) Base + Offset);

  while (((GtStatus & Mask) != Result) && (StallCount < GT_WAIT_TIMEOUT)) {
    ///
    /// 10 microSec wait
    ///
    MicroSecondDelay (10);
    StallCount += 10;

    GtStatus = MmioRead32 ((UINTN) Base + Offset);
  }

  if (StallCount < GT_WAIT_TIMEOUT) {
    return EFI_SUCCESS;
  } else {
    ASSERT ((StallCount < GT_WAIT_TIMEOUT));
    return EFI_TIMEOUT;
  }
}

/**
  This function will check if Bus Master and Memory access on 0:2:0 is enabled or not

  @retval TRUE          Enabled
  @retval FALSE         Disable
**/
BOOLEAN
IgfxCmdRegEnabled (
  VOID
)
{
  return (((PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS(SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, 0) + R_SA_IGD_CMD)) & (UINT16)(BIT2 | BIT1)) ? TRUE : FALSE);
}

/**
  This function is to set Gfx Memory map (RC6 base, Doorbell base etc)

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_NOT_FOUND           SiPreMemPolicyPpi not found
**/
EFI_STATUS
SetGfxMemMap (
  VOID
  )
{
  UINT32            Data32;
  UINT32            GMSSizeSelector;
  UINT32            GMSSize;
  UINT32            GMSBase;
  UINT32            DoorbellCtxBase;
  UINT64            RC6CxtBase;
  UINT64            Data64;
  UINT64            McD0BaseAddress;
  UINT64            McD2BaseAddress;
  UINT32            GttMmAdr;
  EFI_STATUS        Status;
  SI_PREMEM_POLICY_PPI        *SiPreMemPolicyPpi;
  GRAPHICS_PEI_PREMEM_CONFIG  *GtPreMemConfig;

  DEBUG ((DEBUG_INFO, "Set Gfx Memory Map\n"));

  McD0BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, 0);
  McD2BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, 0);

  if (PciSegmentRead16 (McD2BaseAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    DEBUG ((DEBUG_INFO, "\nSkip SetGtMemMap when iGFX is disabled \n"));
    return EFI_SUCCESS;
  }

  Status = PeiServicesLocatePpi (&gSiPreMemPolicyPpiGuid, 0, NULL, (VOID **) &SiPreMemPolicyPpi);
  ASSERT_EFI_ERROR (Status);
  if ((Status != EFI_SUCCESS) || (SiPreMemPolicyPpi == NULL)) {
    return EFI_NOT_FOUND;
  }

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gGraphicsPeiPreMemConfigGuid, (VOID *) &GtPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  GttMmAdr = (PciSegmentRead32 (McD2BaseAddress + R_SA_IGD_GTTMMADR)) & 0xFFFFFFF0;

  if (GttMmAdr == 0) {
    GttMmAdr = GtPreMemConfig->GttMmAdr;
    PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR, (UINT32) (GttMmAdr & 0xFFFFFFFF));
    PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR + 4, 0);
  }

  if (!IgfxCmdRegEnabled()) {
    ///
    /// Enable Bus Master and Memory access on 0:2:0
    ///
    PciSegmentOr16 (McD2BaseAddress + PCI_COMMAND_OFFSET, (BIT2 | BIT1));
  }

  ///
  /// Calculate Context Base
  ///
  ///
  /// Must set to a physical address within GT stolen Memory WOPCM, at least 32KB from the top.
  /// This range must be coordinated with other uses (like GuC and PAVP);
  /// It is expected that the upper 24KB of stolen memory is the proper location
  /// Also set bit 2:0 to 111b
  ///
  GMSSizeSelector = PciSegmentRead32 (McD0BaseAddress + R_SA_GGC);
  GMSSizeSelector = (GMSSizeSelector & B_SA_GGC_GMS_MASK) >> N_SA_GGC_GMS_OFFSET;
  ///
  /// Graphics Stolen Size
  /// Graphics Stolen size above 64MB has a granularity of 32MB increments
  /// GMS values below 240 correspond to Sizes 32 * GSMValue
  /// Graphics Stolen size below 64MB has a higher granularity and can be set in 4MB increments
  /// GMS values ranging from 240-254 correspond to sizes 4MB to 60MB (excluding 32MB) which is 4*(GSMValue-239)
  ///
  if (GMSSizeSelector < 240 ) {
    GMSSize = (UINT32) GMSSizeSelector * 32;
  } else {
    GMSSize = 4 * (GMSSizeSelector - 239);
  }
  DEBUG ((DEBUG_INFO, "GMSSize: %dMB\n",GMSSize));
  GMSBase = PciSegmentRead32 (McD0BaseAddress + R_SA_BDSM) & B_SA_BDSM_BDSM_MASK;
  DEBUG ((DEBUG_INFO, "GMSBase read from R_SA_BDSM: 0x%x\n",GMSBase));

  ///
  /// The Doorbell Power Context Image lives in WOPCM.
  /// DoorbellCtxBase = DSM top - 4k
  /// RC6CXTBASE =  MDRBCTXBASE (DoorbellCtxBase) - 32KB
  ///
  DoorbellCtxBase =  (UINT32) (GMSBase + GMSSize * 0x100000 -  0x1000);
  RC6CxtBase = DoorbellCtxBase - RC6CTXBASE_SIZE;

  DEBUG ((DEBUG_INFO, "RC6CXTBASE: 0x%x\n",RC6CxtBase));
  DEBUG ((DEBUG_INFO, "DoorbellCtxBase: 0x%x\n",DoorbellCtxBase));


  ///
  /// Programming Doorbell Context base Low and High
  ///
  DEBUG ((DEBUG_INFO, "DoorbellCtxBase: 0x%x\n", DoorbellCtxBase));
  Data32 = DoorbellCtxBase | BIT0;
  MmioWrite32 (GttMmAdr + 0xDC8, Data32);
  MmioWrite32 (GttMmAdr + 0xDCC, 0);


  ///
  /// Programming RC6 Context Base
  ///
  Data64 = RC6CxtBase | BIT0;
  DEBUG ((DEBUG_INFO, "RC6 Context Base: 0x%x\n", RC6CxtBase));
  MmioWrite64 (GttMmAdr + 0xD48, Data64);
  DEBUG ((DEBUG_INFO, "RC6 Context Base Programming done \n"));

  return EFI_SUCCESS;
}

