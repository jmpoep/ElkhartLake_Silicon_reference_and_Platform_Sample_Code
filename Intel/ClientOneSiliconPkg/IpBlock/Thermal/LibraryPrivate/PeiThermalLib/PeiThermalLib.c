/** @file
  Initializes PCH thermal controller for ICL.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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

#include <Uefi/UefiBaseType.h>
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/PmcLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PeiThermalLib.h>
#include <Library/GpioPrivateLib.h>
#include <Library/CpuInitLib.h>
#include <Register/ThermalRegs.h>
#include <Register/PmcRegs.h>

/**
  Perform Thermal Management Support initialization

  @param[in] SiPolicy                   SI policy PPI instance.

**/
VOID
ThermalInit (
  IN  SI_POLICY_PPI                     *SiPolicy
  )
{
  EFI_STATUS                    Status;
  UINT32                        PwrmBase;
  THERMAL_CONFIG                *ThermalConfig;
  UINT32                        PchTTLevels;
  UINT32                        Temperature;

  PwrmBase = PmcGetPwrmBase ();

  DEBUG ((DEBUG_INFO, "PchThermalInit () Start\n"));

  Status = GetConfigBlock ((VOID *) SiPolicy, &gThermalConfigGuid, (VOID *) &ThermalConfig);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Thermal SubSystem Device Initialization
  ///
  /// 1.
  /// Starting from CDF and ICL, Thermal Management is not a PCI device in itself,
  /// but all Thermal features related registers are part of the PMC.
  /// System BIOS shall use PMC BAR for Thermal subsystem initialization
  ///
  /// 2.
  /// Enabling/Disabling of Thermal Management features is through Soft Strap.
  /// Make sure the THERMAL_MGMT_DIS strap is tied low.
  ///
  /// 3.
  /// System BISO should initialize relevant Thermal subsystems for the desired features
  /// 3a.
  /// Ensure CTEN.CPDEN is set high for enabling Catastrophic Trip point assertion into S5
  /// and lockdown CTEN.CTENLOCK to prevent overriding of this feature
  /// 3b.
  /// Program the Temperature reporting frequency to Punit (TRPTFRQ.PUNIT)
  /// and other endpoints (TRPTFRQ.NON_PUNIT) based on Platform requirements.
  /// Default is set to 10mS.
  /// 3c.
  /// Enable Temperature reporting to EC (via SMBus or eSPI). Set ECRPTEN.Enable (bit 0) to 1.
  /// This bit should also be set if ME needs access to the PCH temperature.
  /// Once enabled, lock the ECRPTEN.ECRPTENLOCK bit to prevent disabling this feature.
  ///

  ///
  /// Thermal Sensor Initialization
  ///
  /// The System BIOS must perform the following steps to initialize the thermal subsystem device.
  /// The System BIOS is required to repeat this process on a resume from Sx.
  /// BIOS may enable any or all of the registers below based on OEM's platform configuration.
  /// Intel does not recommend a value on some of the registers, since each platform
  /// has different temperature trip points and one may enable a trip to cause an SMI
  /// while another platform would cause an interrupt instead.
  ///
  /// The DTSs and their corresponding thermal sensors are brought out of reset by the PMC
  /// as part of the PMC boot flow. The DTS is part of the SOC reset group.
  /// As such it is brought out of reset before the Host group and before the System enters S0.
  /// Therefore all default register values are such that there will be no SMI/SCI generated
  /// until the BIOS programs the corresponding temperature values to their intended values.
  ///
  /// The PCH_HOT# has a associated enable bit PHLC.PHLE.
  /// The BIOS should first program the desired temperature threshold for PCH_HOT#
  /// in the PHLC.PHLL[8:0] filed and then set the enable.
  ///

  ///
  /// Following are some steps that the BIOS may take to program the various temperature thresholds:
  ///
  /// 1.
  /// Note that in the new Thermal Architecture the Catastrophic Trip point (which is supposed to generate a global reset)
  /// is not being set by BIOS. This trip point is being directly programmed into the Temperature Sensors
  /// via fuses being pulled by the corresponding DTS block.
  ///
  MmioWrite32 (PwrmBase + R_PMC_PWRM_THERMAL_CTEN, B_PMC_PWRM_THERMAL_CTEN_CPDEN);
  MmioOr32 (PwrmBase + R_PMC_PWRM_THERMAL_CTEN, B_PMC_PWRM_THERMAL_CTEN_CTENLOCK);
  ///
  /// 2.
  /// Note that the Temperature Sensors do not get "disabled".
  /// Once PMC brings the DTSs out of reset the corresponding Temperature Sensors will also come out of reset.
  /// There are no "enables" to the Temperature Sensors.
  /// 3.
  /// The TSAHV and TSALV threshold levels are used to generate SMI/SCI.
  /// These threshold levels may be programmed by the BIOS or driver to force a SW notification for PCH temperature.
  /// Note that the default value of these threshold levels is such that
  /// there will be no possibility to cause an unexpected SMI/SCI.
  /// 4.
  /// Clear trip status bits TAS.ALHE and TAS.ALHE.
  /// BIOS should write 1 to clear any bit that was inadvertently set
  /// while programming the Thermal Reporting Registers.
  /// 5.
  /// Enable the desired thermal trip alert methods by setting the corresponding ACPI register bits.
  /// SMI (SMI_EN.THERM_SMI_EN) or SCI (GPE0_EN_127_96.THERM_EN).
  /// Only one of the methods should be enabled and the method will be depending on the platform implementation.
  /// THERM_SMI_EN: BIOS should leave this as default 0h, unless the SMI handler is loaded
  /// and it's safe to enable SMI for these events.
  /// THERM_EN: BIOS should leave this as default 0h, so that a driver can enable later.
  /// 6.
  /// Enable thermal reporting to an EC over SMBus or eSPI and PMC.
  /// Set bit[0] of ECRPTEN register to 1.
  ///
  MmioWrite32 (PwrmBase + R_PMC_PWRM_THERMAL_ECRPTEN, B_PMC_PWRM_THERMAL_ECRPTEN_EN_RPT);
  MmioOr32 (PwrmBase + R_PMC_PWRM_THERMAL_ECRPTEN, B_PMC_PWRM_THERMAL_ECRPTEN_ECRPTENLOCK);
  ///
  /// 7.
  /// If the PCH_Hot pin reporting is supported, then write the temperature value in PHLC.PHLL[8:0]
  /// and set the enablebit PHLC.PHLE to 1.
  /// Note: For PCHHOT# support, we need to make sure if GPP_B_23 is set to PCHHOTB mode (pad mode == 2)
  /// and flash descriptor PCH Strap 9 Bit 22is set to 1.
  ///
  if ((ThermalConfig->PchHotEnable) &&
      (ThermalConfig->PchHotLevel < 0x0200)) {
    //
    // Enable PCHHOT# pin
    //
    GpioEnablePchHot ();
    //
    // Program PHL register according to PchHotLevel setting.
    //
    MmioWrite32 (PwrmBase + R_PMC_PWRM_THERMAL_PHLC, ThermalConfig->PchHotLevel | B_PMC_PWRM_THERMAL_PHLC_PHLE);
  }
  ///
  /// 8.
  /// If thermal throttling is supported, then set the desired throttle values in
  /// TL.T2L[28:20], TL.T1L[18:10] and TL.T0l[8:0].
  /// Once the throttle levels are programmed then write 1 to the TL.TTEN bit.
  /// TL [31] locks the thermal throttling register.
  ///
  if (ThermalConfig->TTLevels.SuggestedSetting == FALSE) {
    ///
    /// Trip Point Temperature = Resolution of 1'C in S9.8.0 2s complement format of Trip Point Register [8:0]
    /// If Trip Point Temperature <= T0Level, the system will be in T0 state.
    /// If T1Level >= Trip Point Temperature > T0Level, the system will be in T1 state.
    /// If T2Level >= Trip Point Temperature > T1Level, the system will be in T2 state.
    /// If Trip Point Temperature > T2Level, the system will be in T3 state.
    ///
    PchTTLevels =
      (UINT32) (ThermalConfig->TTLevels.T2Level << 20) |
      (UINT32) (ThermalConfig->TTLevels.T1Level << 10) |
      (UINT32) (ThermalConfig->TTLevels.T0Level);
    MmioWrite32 (PwrmBase + R_PMC_PWRM_THERMAL_TL, PchTTLevels);

    MmioOr32 (
      PwrmBase + R_PMC_PWRM_THERMAL_TL,
      (UINT32) (ThermalConfig->TTLevels.TTLock << 31) |
      (UINT32) (ThermalConfig->TTLevels.TTState13Enable << 30) |
      (UINT32) (ThermalConfig->TTLevels.TTEnable << 29)
      );
  } else {
    //
    // Check if PCH LP, it also indicates the ULT.
    //
    if (IsPchLp () && (ThermalConfig->TTLevels.PchCrossThrottling == TRUE)) {
      ///
      /// If processor is capable of cross throttling and it is enabled
      ///   T0L = cross throttling trip point
      ///   T1L = T0L + 5'C
      ///   T2L = T1L + 5'C
      ///   Set TL   1520h[31:29] = 101b
      ///   Set TLEN 1528h[14] = 1b
      ///   Set PWRMBASE + 18C4h[26:24] = 101b
      ///
      Temperature = CpuGetCrossThrottlingTripPoint ();
      PchTTLevels =
        (UINT32) ((Temperature + 10) << 20) |
        (UINT32) ((Temperature +  5) << 10) |
        (UINT32) ((Temperature));
      //
      // Program TL + 1520h[28:0]
      //
      MmioWrite32 (PwrmBase + R_PMC_PWRM_THERMAL_TL, PchTTLevels);
      //
      // Program TL + 1520h[31:29]
      // TL [31] locks the thermal throttling registers
      //
      MmioOr32 (PwrmBase + R_PMC_PWRM_THERMAL_TL, B_PMC_PWRM_THERMAL_TL_TLLOCK | B_PMC_PWRM_THERMAL_TL_TTEN);
      //
      // Set PWRMBASE + 18C4h[26:24] = 101b
      //
      MmioAndThenOr32 (PwrmBase + R_PMC_PWRM_PMSYNC_TPR_CONFIG,
        (UINT32) ~(B_PMC_PWRM_PMSYNC_PCH2CPU_TT_STATE),
        (B_PMC_PWRM_PMSYNC_PCH2CPU_TT_EN | (V_PMC_PWRM_PMSYNC_PCH2CPU_TT_STATE_1 << N_PMC_PWRM_PMSYNC_PCH2CPU_TT_STATE))
        );
    } else {
      ///
      /// Set TL + 1520h[28:20] = 114
      /// Set TL + 1520h[18:10] = 111
      /// Set TL + 1520h[8:0] = 108
      /// Set TL + 1520h[31:29] = 101b in separate write
      ///
      PchTTLevels = ((114 << 20) | (111 << 10) | (108));
      MmioWrite32 (PwrmBase + R_PMC_PWRM_THERMAL_TL, PchTTLevels);
      MmioOr32 (PwrmBase + R_PMC_PWRM_THERMAL_TL, B_PMC_PWRM_THERMAL_TL_TLLOCK | B_PMC_PWRM_THERMAL_TL_TTEN);
    }
  }
  ///
  /// 9.
  /// Lock down the thermal reporting to prevent outside agents from changing the values.
  ///   a. PHLC [31] locks the PHLC register for PCH_Hot#
  ///
  MmioOr32 (PwrmBase + R_PMC_PWRM_THERMAL_PHLC, B_PMC_PWRM_THERMAL_PHLC_PHLCLOCK);

  ///
  /// Set TLEN lock.
  ///
  MmioOr32 (PwrmBase + R_PMC_PWRM_THERMAL_TLEN, B_PMC_PWRM_THERMAL_TLEN_TLENLOCK);
}

/**
  Inititalize Memory Throttling.

  @param[in] SiPolicy                   SI policy PPI instance.
**/
VOID
MemoryThrottlingInit (
  IN  SI_POLICY_PPI                     *SiPolicy
  )
{
}
