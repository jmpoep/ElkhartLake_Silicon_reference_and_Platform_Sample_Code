/** @file
  This header file contains the processor power management definitions.

  Acronyms:
   - PPM   Processor Power Management
   - TM    Thermal Monitor
   - IST   Intel(R) Speedstep technology
   - HT    Hyper-Threading Technology

@copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2018 Intel Corporation.

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

#ifndef _POWER_MGMT_COMMON_H_
#define _POWER_MGMT_COMMON_H_

#include <Library/PeiServicesLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/IoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/TimerLib.h>
#include <Register/Cpuid.h>
#include <Register/Msr.h>
#include <CpuAccess.h>
#include <Ppi/SiPolicy.h>
#include <Library/CpuPlatformLib.h>
#include <Library/SaPlatformLib.h>
#include <PowerMgmtNvsStruct.h>
#include <Library/PciSegmentLib.h>
#include <CpuInitDataHob.h>
#include <Library/PmcLib.h>
#include <Library/CpuCommonLib.h>
#include <Library/CpuMailboxLib.h>
#include <Ppi/MpServices.h>
#include <Library/MmPciLib.h>

#define PM_CST_LVL2                     0x14

#define CTDP_LEVEL_ONE                  1
#define CTDP_LEVEL_TWO                  2

#define EFI_IDIV_ROUND(r, s)  ((r) / (s) + (((2 * ((r) % (s))) < (s)) ? 0 : 1))

#define TDP_35_WATTS          3500
#define TDP_65_WATTS          6500
#define TDP_77_WATTS          7700
#define TDP_91_WATTS          9100

//
// Global variables
//
///
/// Power Managment policy configurations
///
extern CPU_POWER_MGMT_BASIC_CONFIG      *gCpuPowerMgmtBasicConfig;
extern CPU_POWER_MGMT_CUSTOM_CONFIG     *gCpuPowerMgmtCustomConfig;
extern CPU_POWER_MGMT_PSYS_CONFIG       *gCpuPowerMgmtPsysConfig;
extern CPU_POWER_MGMT_TEST_CONFIG       *gCpuPowerMgmtTestConfig;
extern EFI_PEI_MP_SERVICES_PPI          *gMpServicesPpi;
extern CPU_CONFIG                       *mCpuConfig;
extern CPU_INIT_DATA_HOB                *mCpuInitDataHob;
//
// Values for FVID table calculate.
//
extern BOOLEAN mOver16Pstates;
extern UINT32  mPpmFlags;                                  /// PPM Flags Values.
extern UINT16  mTurboBusRatio;
extern UINT16  mMaxBusRatio;                               /// Matches BUS_RATIO_MAX field in PERF_STS_MSR
extern UINT16  mMinBusRatio;
extern UINT16  mProcessorFlavor;
extern UINT16  mPackageTdp;
extern UINT16  mPackageTdpWatt;
extern UINT16  mCpuConfigTdpBootRatio;
extern UINT16  mCustomPowerUnit;
extern UINT16  mCtdpPowerLimit1[TDP_MAX_LEVEL];             /// CTDP Levels Power Limit1
extern UINT16  mCtdpPowerLimit2[TDP_MAX_LEVEL];             /// CTDP Levels Power Limit2
extern UINT8   mCtdpTar[TDP_MAX_LEVEL];                     /// CTDP Levels TAR
extern UINT8   mConfigTdpBootModeIndex;                     /// CTDP Boot Mode Index
extern UINT8   mCtdpPowerLimitWindow[TDP_MAX_LEVEL];        /// CTDP Levels Power Limit1 Time Window
extern UINT8   mCtdpCtc[TDP_MAX_LEVEL];                     /// CTDP Levels CTC
extern UINT8   mCtdpPpc[TDP_MAX_LEVEL];                     /// CTDP Levels PPC
extern UINT8   mCtdpLevelsSupported;                        /// ConfigTdp Number Of Levels.
extern UINT8   mConfigurablePpc;                            /// Boot Mode vlues for _PPC
extern UINT8   mLowestMaxPerf;                              /// Max ratio of the slowest core.

///
/// Fractional part of Processor Power Unit in Watts. (i.e. Unit is 1/mProcessorPowerUnit)
///
extern UINT8 mProcessorPowerUnit;
///
/// Maximum allowed power limit value in TURBO_POWER_LIMIT_MSR and PRIMARY_PLANE_POWER_LIMIT_MSR
/// in units specified by PACKAGE_POWER_SKU_UNIT_MSR
///
extern UINT16 mPackageMaxPower;
///
/// Minimum allowed power limit value in TURBO_POWER_LIMIT_MSR and PRIMARY_PLANE_POWER_LIMIT_MSR
/// in units specified by PACKAGE_POWER_SKU_UNIT_MSR
///
extern UINT16 mPackageMinPower;
extern UINT8  mRatioLimitProgrammble;                        ///< Porgrammable Ratio Limit
extern UINT8  mTdpLimitProgrammble;                          ///< Porgrammable TDP Limit

extern UINT16 mCpuIdentifier;


typedef struct _ENABLE_CSTATE_PARAMS {
  UINT16 C3IoAddress;
} ENABLE_CSTATE_PARAMS;

///
/// Override table structure for cTDP and non-cTDP skus.
/// Non-cTDP parts would have '0' data for TDP level information.
///
typedef struct {
  UINTN  CpuIdentifier;
  UINT16 SkuPackageTdp;
  UINTN  MsrPowerLimit1;
  UINTN  MsrPowerLimit2;
  UINTN  CtdpUpPowerLimit1;
  UINTN  CtdpUpPowerLimit2;
  UINTN  CtdpNominalPowerLimit1;
  UINTN  CtdpNominalPowerLimit2;
  UINTN  CtdpDownPowerLimit1;
  UINTN  CtdpDownPowerLimit2;
  UINTN  MsrPowerLimit4;
} PPM_OVERRIDE_TABLE;

///
/// PL1 Thermal Control structure layout
///
typedef union {
  struct {
   UINT8 Disable:1;      ///< [0] Disable
   UINT8 Reserved:7;     ///< [7:2] Reserved
   UINT8 FloorIa:8;        ///< [15:8] Percent Throttle for IA component 255-0; 255=0%, 0=100%
   UINT8 FloorGt:8;        ///< [23:16] Percent Throttle for GT component 255-0; 255=0%, 0=100%
   UINT8 FloorPch:8;       ///< [31:24] Percent Throttle for PCH component 255-0; 255=0%, 0=100%
  } Bits;
  UINT32 Uint32;
 } PL1_THERMAL_CONTROL;

//
// FVID Table Information
// Default FVID table
// One header field plus states
//
extern FVID_TABLE *mFvidPointer;

//
// Function prototypes
//
/**
  Initializes P States and Turbo Power management features

  @param[in] PeiServices    Pointer to PEI Services Table
**/
VOID
InitPStates (
  IN CONST EFI_PEI_SERVICES   **PeiServices
  );

/**
  Initializes C States Power management features

  @param[in] PeiServices    Pointer to PEI Services Table
**/
VOID
InitCState (
  IN CONST EFI_PEI_SERVICES   **PeiServices
  );

/**
  Disable/Enable the CState Pre-Wake Feature
**/
VOID
InitCstatePreWake (
  VOID
  );

/**
  Enables C-State support as specified by the input flags on all logical
  processors and sets associated timing requirements in the chipset.

  @param[in] PeiServices    Pointer to PEI Services Table
  @param[in] C3IoAddress   IO address to generate C3 states (PM base + 014 usually)
**/
VOID
EnableCStates (
  IN CONST EFI_PEI_SERVICES   **PeiServices,
  IN UINT16                   C3IoAddress
  );

/**
  Enable C-State support as specified by the input flags on a logical processor.
    Configure BIOS C1 Coordination (SMI coordination)
    Enable IO redirection coordination
    Choose proper coordination method
    Configure extended C-States

  This function must be MP safe.

  @param[in out] Buffer    Pointer to a ENABLE_CSTATE_PARAMS containing the necessary
                           information to enable C-States

  @retval EFI_SUCCESS  Processor C-State support configured successfully.
**/
VOID
EFIAPI
ApSafeEnableCStates (
  IN OUT VOID *Buffer
  );

/**
  This will perform Miscellaneous Power Management related programming.

  @param[in] CtdpSupport   Status of InitializeConfigurableTdp funtion
**/
VOID
InitMiscFeatures (
  EFI_STATUS CtdpSupport
  );

/**
  CTDP BIOS settings Initialization(Msr)

  @exception EFI_UNSUPPORTED Ctdp not supported

  @retval EFI_SUCCESS     Ctdp Settings Initialized successfully from MSRs
**/
EFI_STATUS
InitializeConfigurableTdp (
  VOID
  );

/**
  Configures PowerLimits and Config TDP values
**/
VOID
ConfigureCtdp (
  VOID
  );

/**
  This will perform general thermal initialization other then TM1, TM2, or
  PROCHOT# on all logical processors.

  @param[in] PeiServices    Pointer to PEI Services Table
**/
VOID
InitThermal (
  IN CONST EFI_PEI_SERVICES   **PeiServices
  );

/**
  This will perform enable thermal initialization. TM1, TM2 and adaptive thermal
  throttling are enabled/disabled together.

  This function must be MP safe.

  @param[in out] Buffer    Pointer to the function parameters passed in.
**/
VOID
EFIAPI
ApSafeInitThermal (
  IN OUT VOID *Buffer
  );

/**
  Enables the bi-directional PROCHOT# signal.

  @retval EFI_SUCCESS  PROCHOT# configured successfully
**/
EFI_STATUS
EnableProcHot (
  VOID
  );


/**
  Locks down all settings.

  @param[in] PeiServices    Pointer to PEI Services Table
**/
VOID
PpmLockDown (
  IN CONST EFI_PEI_SERVICES   **PeiServices
  );

/**
  Lock MSR_BROADWELL_PKG_CST_CONFIG_CONTROL
  This function must be MP safe.

  @param[in out] Buffer    Pointer to the function parameters passed in.
**/
VOID
EFIAPI
ApSafeLockDown (
  IN OUT VOID *Buffer
  );

/**
  Configures following fields of MSR 0x610 based on user configuration:
    Configures Long duration Turbo Mode (power limit 1) power level and time window
    Configures Short duration Turbo mode (power limit 2)
**/
VOID
ConfigurePowerLimits (
  VOID
  );

/**
  Configures following fields of MSR 0x610 based on user configuration:
    Configures Long duration Turbo Mode (power limit 1) power level and time window
    Configures Short duration Turbo mode (power limit 2)
**/
VOID
ConfigurePowerLimitsNonConfigTdpSkus (
  VOID
  );

/**
  Configures following fields of PL3 MSR 0x615 based on user configuration:
    Configures PL 3 power level and time window
**/
VOID
ConfigurePl3PowerLimits (
  VOID
  );

/**
  Configures following fields of MSR 0x601
    Configures power limit 4 power level and lock
**/
VOID
ConfigurePl4PowerLimits (
  VOID
  );

/**
  Configures following fields of MSR 0x618 based on user configuration:
    Configures Long duration Turbo Mode (power limit 1) power level and time window for DDR domain
    Configures Short duration Turbo mode (power limit 2)
**/
VOID
ConfigureDdrPowerLimits (
  VOID
  );

/**
  Configures MSR 0x65C platform power limits (PSys)
    -Configures Platform Power Limit 1 Enable, power and time window
    -Configures Platform Power Limit 2 Enable, power
**/
VOID
ConfigurePlatformPowerLimits (
  VOID
  );

/**
  Verify and fix Custom Power Limit values

  @param[in] CustomPowerLimit  Custom Power Limit value
  @param[in] CustomPlUnit  Custom Power Limit Unit

  @retval Verified Custom power limit value
**/
UINT16
VerifyAndFixCustomPowerLimit (
  IN UINT32 CustomPowerLimit,
  IN UINT16 CustomPlUnit
  );

/**
  Verify and fix Custom Ratio values
  Custom Ratio should be between MaxTurboFrequency and LFM

  @param[in] CustomPowerLimit  Custom Power Ratio Value

  @retval Verified Custom Ratio value
**/
UINT8
VerifyAndFixCustomRatio (
  IN UINT8 CustomRatio
  );

/**
  Initalizes CTDP BIOS settings from silicon defaults and overrides custom cTDP settings if needed

  @retval EFI_UNSUPPORTED  Ctdp not supported

  @retval EFI_SUCCESS         Ctdp Settings Initialized successfully from MSRs
**/
EFI_STATUS
InitConfigurableTdpSettings (
  VOID
  );

/**
  Get Power Limit2 based on Power Limit1 on Config TDP

  @param[in] PowerLimit1  Power Limit 1 Value

  @retval Calculated Power Limit2 value
**/
UINT16
GetCtdpPowerLimit2 (
  IN UINT16 PowerLimit1
  );

/**
  Configures following fields of MSR 0x610
    Configures Long duration Turbo Mode (power limit 1) power level and time window
    Configures Short duration turbo mode (power limit 2)
**/
VOID
ConfigureCtdpPowerLimits (
  VOID
  );

/**
  Patch Fvid Table with Ctdp Tar ratio and Tar-1 Ratio

  @param[in] FvidPointer  Pointer to Fvid Table
**/
VOID
CtdpPatchFvidTable (
  IN OUT FVID_TABLE *FvidPointer
  );

/**
  Patch Fvid Table with Ctdp Tar ratio and Tar-1 Ratio for Legacy OS

  @param[in] FvidPointer  Pointer to Fvid Table
**/
VOID
CtdpPatchFvidTableforLimitPstate (
  IN OUT FVID_TABLE *FvidPointer
  );

/**
  Replace P state with given ratio

  @param[in out] FvidPointer  Pointer to Fvid Table
  @param[in]     PssIndex     FVID table index of P state to be replaced
  @param[in]     Ratio        Target Ratio to put in
**/
VOID
CtdpReplaceFvidRatio (
  IN OUT FVID_TABLE *FvidPointer,
  UINTN             PssIndex,
  UINTN             Ratio
  );

/**
  Initializes HWP

  @param[in] PeiServices    Pointer to PEI Services Table
**/
VOID
InitializeHwp (
  IN CONST EFI_PEI_SERVICES   **PeiServices
  );

/**
  Initialize Per Core P State OS control mode.
  Initialize HwP Autonomous Per Core P State.
  Initialize HwP Autonomous EPP grouping
  Initialize EPB override over PECI.
  Enable/Disable Fast Msr Support for IA32_HWP_REQUEST.

  @param[in] PeiServices    Pointer to PEI Services Table
**/
VOID
InitializeHwpMiscFeatures (
  IN CONST EFI_PEI_SERVICES   **PeiServices
  );

/**
  Initializes Intel Turbo Boost Max Technology 3.0

  @param[in] PeiServices    Pointer to PEI Services Table
**/
VOID
InitializeItbm (
  IN CONST EFI_PEI_SERVICES   **PeiServices
  );

#endif
