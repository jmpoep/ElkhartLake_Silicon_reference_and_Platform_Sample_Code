/** @file
  PCH PMC Private Library implementation for Ver3.
  All function in this library is available for PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

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

#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PmcPrivateLib.h>
#include <Library/DciPrivateLib.h>
#include <Library/PchInfoLib.h>
#include <Register/PmcRegs.h>
#include <Register/PmcRegsVer3.h>
#include <ConfigBlock.h>
#include <ConfigBlock/SiPreMemConfig.h>

#include "PmcPrivateLibInternal.h"

/**
  This function returns PMC, PUNIT and CPU Crashlog Size allocated on PMC SSRAM
  specific for a given generation

  @param[out] PmcLogSize        Pointer to PMC CrashLog Size
  @param[out] PunitLogSize      Pointer to PUNIT CrashLog Size
  @param[out] CpuLogSize        Pointer to CPU CrashLog Size

**/
VOID
PmcSsramSocCrashLogSize (
  OUT UINT32     *PmcLogSize,
  OUT UINT32     *PunitLogSize,
  OUT UINT32     *CpuLogSize
  )
{
  *PmcLogSize   = 0x240; // 576 Bytes
  *PunitLogSize = 0x420; // 1056 Bytes
  *CpuLogSize   = 0x5A0; // 1440 Bytes
}

/**
  This function enables all SerailIo devices.
  Static power gating disabling takes place after Global Reset, G3 or DeepSx transition.
**/
VOID
PmcEnableSerialIo (
  VOID
  )
{
  //
  // Set PWRMBASE + ST_PG_FDIS_PMC_2
  //
  MmioAnd32 (PmcGetPwrmBase () + R_PMC_PWRM_ST_PG_FDIS_PMC_2, (UINT32)~B_PMC_PWRM_ST_PG_FDIS_PMC_2_SERIALIO);
}

/**
  This function disables (static power gating) all SerailIo devices.
  For SerialIo controllers they can be power gated only if all of them are to be disabled.
  They cannot be statically power gated separately.
  For static power gating to take place Global Reset, G3 or DeepSx transition must happen.
**/
VOID
PmcStaticDisableSerialIo (
  VOID
  )
{
  //
  // Set PWRMBASE + ST_PG_FDIS_PMC_2
  //
  MmioOr32 (PmcGetPwrmBase () + R_PMC_PWRM_ST_PG_FDIS_PMC_2, B_PMC_PWRM_ST_PG_FDIS_PMC_2_SERIALIO);
}

/**
  This function checks if all SerialIo devices are statically disabled (static power gating)

  @retval SerialIo disable state
**/
BOOLEAN
PmcIsSerialIoStaticallyDisabled (
  VOID
  )
{
  //
  // Check if all SerialIo controllers are statically disabled in PMC
  //
  return ((MmioRead32 (PmcGetPwrmBase () + R_PMC_PWRM_ST_PG_FDIS_PMC_2) & B_PMC_PWRM_ST_PG_FDIS_PMC_2_SERIALIO) == B_PMC_PWRM_ST_PG_FDIS_PMC_2_SERIALIO);
}

/**
  This function checks if SerialIo device is supported (not disabled by fuse)

  @retval SerialIo support state
**/
BOOLEAN
PmcIsSerialIoSupported (
  VOID
  )
{
  //
  // Get fuse info from PWRMBASE + FUSE_SS_DIS_RD_2
  //
  return ((MmioRead32 (PmcGetPwrmBase () + R_PMC_PWRM_FUSE_DIS_RD_2) & B_PMC_PWRM_FUSE_DIS_RD_2_SERIALIO_FUSE_SS_DIS) == 0);
}

/**
  This function disables (non-static power gating) SCS eMMC controller and enables ModPHY SPD gating (PCH-LP only).
**/
VOID
PmcDisableScsEmmc (
  VOID
  )
{
  //
  // Set PWRMBASE + NST_PG_FDIS_1 to disable SCS Controller in PMC
  //
  MmioOr32 (PmcGetPwrmBase () + R_PMC_PWRM_NST_PG_FDIS_1, B_PCH_LP_PMC_PWRM_NST_PG_FDIS_1_EMMC_FDIS_PMC);
}

/**
  This function disables (non-static power gating) SCS SD Card controller and enables ModPHY SPD gating (PCH-LP only).
**/
VOID
PmcDisableScsSdCard (
  VOID
  )
{
  //
  // Set PWRMBASE + NST_PG_FDIS_1 to disable SCS Controller in PMC
  //
  MmioOr32 (PmcGetPwrmBase () + R_PMC_PWRM_NST_PG_FDIS_1, B_PCH_LP_PMC_PWRM_NST_PG_FDIS_1_SDCARD_FDIS_PMC);
}

/**
  This function disables (non-static power gating) SCS UFS controller and enables ModPHY SPD gating (PCH-LP only).

  @param[in] UfsNum     SCS UFS Device
**/
VOID
PmcDisableScsUfs (
  IN UINT32   UfsNum
  )
{
  UINT32        PchPwrmBase;

  PchPwrmBase = PmcGetPwrmBase ();
  switch (UfsNum) {
    case 0:
      //
      // Set PWRMBASE + NST_PG_FDIS_1 to disable SCS Controller in PMC
      //
      MmioOr32 (PchPwrmBase + R_PMC_PWRM_NST_PG_FDIS_1, B_PCH_LP_PMC_PWRM_NST_PG_FDIS_1_UFS_FDIS_PMC);

      if (PmcIsModPhySusPgSupported ()) {
        //
        // Set MSPDRTREQ:
        // PchPwrmBase + R_PWRM_MODPHY_PM_CFG5[16] = 1 to enable ASL code trigger request for ModPHY SPD gating.
        //
        MmioOr32 (PchPwrmBase + R_PMC_PWRM_MODPHY_PM_CFG5, B_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_UFS2);
      }
      break;
    case 1:
      //
      // @todo: Update PMC programming once the has been updated.
      //
      break;
    default:
      ASSERT (FALSE);
  }
}

/**
  This function checks if SCS eMMC device is supported (not disabled by fuse)

  @retval SCS device support state
**/
BOOLEAN
PmcIsScsEmmcSupported (
  VOID
  )
{
  //
  // Get fuse info from PWRMBASE + FUSE_SS_DIS_RD_2
  //
  return ((MmioRead32 (PmcGetPwrmBase () + R_PMC_PWRM_FUSE_DIS_RD_2) & B_PMC_PWRM_FUSE_DIS_RD_2_EMMC_FUSE_SS_DIS) == 0);
}

/**
  This function checks if SCS SD Card device is supported (not disabled by fuse)

  @retval SCS device support state
**/
BOOLEAN
PmcIsScsSdCardSupported (
  VOID
  )
{
  //
  // Get fuse info from PWRMBASE + FUSE_SS_DIS_RD_2
  //
  return ((MmioRead32 (PmcGetPwrmBase () + R_PMC_PWRM_FUSE_DIS_RD_2) & B_PMC_PWRM_FUSE_DIS_RD_2_SDX_FUSE_SS_DIS) == 0);
}

/**
  This function checks if SCS UFS device is supported (not disabled by fuse)

  @param[in] UfsNum     SCS UFS Device

  @retval SCS device support state
**/
BOOLEAN
PmcIsScsUfsSupported (
  IN UINT32   UfsNum
  )
{
  //
  // Get fuse info from PWRMBASE + FUSE_SS_DIS_RD_2
  //
  return ((MmioRead32 (PmcGetPwrmBase () + R_PMC_PWRM_FUSE_DIS_RD_2) & B_PMC_PWRM_FUSE_DIS_RD_2_UFSX2_FUSE_SS_DIS) == 0);
}

/**
  This function checks if SCI device is supported (not disabled by fuse)

  @retval Sci support state
**/
BOOLEAN
PmcIsSciSupported (
  VOID
  )
{
  //
  // Get fuse info from PWRMBASE + FUSE_SS_DIS_RD_2
  //
  return ((MmioRead32 (PmcGetPwrmBase () + R_PMC_PWRM_FUSE_DIS_RD_2) & B_PMC_PWRM_FUSE_DIS_RD_2_SCI_FUSE_SS_DIS) == 0);
}

/**
  Enable OS IDLE Mode
**/
VOID
PmcEnableOsIdleMode (
  VOID
)
{
  MmioOr32 (PmcGetPwrmBase () + R_PMC_PWRM_WINIDLE_BIOS_ENABLE, B_PMC_PWRM_WINIDLE_BIOS_ENABLE_WI_ENABLE);
}

/**
  Lock OS IDLE Mode register
**/
VOID
PmcLockOsIdleMode (
  VOID
)
{
  MmioOr32 (PmcGetPwrmBase () + R_PMC_PWRM_WINIDLE_BIOS_ENABLE, B_PMC_PWRM_WINIDLE_BIOS_ENABLE_WI_LOCK);
}

/**
  Check if OS IDLE Mode is supported by PCH

  @retval OS IDLE Mode support state
**/
BOOLEAN
PmcIsOsIdleModeSupported (
  VOID
)
{
  return IsPchLp ();
}

/**
  This function enables GBE ModPHY SPD gating.
**/
VOID
PmcTsnModPhyPowerGating (
  VOID
  )
{
  if (PmcIsModPhySusPgSupported ()) {
    //
    // Set B_PCH_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_GBE ModPHY SPD RT Request
    //
    MmioOr32 (PmcGetPwrmBase () + R_PMC_PWRM_MODPHY_PM_CFG5, B_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_TSN);
  }
}

/**
  This function disables GbE TSN device by static power gating and enables ModPHY SPD gating (PCH-LP only).
  For static power gating to take place Global Reset, G3 or DeepSx transition must happen.
**/
VOID
PmcStaticDisableTsn (
  VOID
  )
{
  UINT32 PchPwrmBase;
  PchPwrmBase = PmcGetPwrmBase ();
  //
  // Set PWRMBASE + ST_PG_FDIS_PMC_1[0] = 1b to statically disable TSN mGbE Controller
  //
  MmioOr32 (PchPwrmBase + R_PMC_PWRM_ST_PG_FDIS_PMC_1, B_PMC_PWRM_ST_PG_FDIS_PMC_1_TSN_FDIS_PMC);
  PmcTsnModPhyPowerGating ();
}

/**
  Disable ME devices. This function can be called only once during
  boot. Calling this function with DisableMe = FALSE will only tell PMC
  that we wish to keep ME enabled and to disallow any further attempts at disabling ME.

  @param[in] DisableMe  TRUE if this function should disable ME.
**/
VOID
PmcDisableMeDevices (
  IN BOOLEAN  DisableMe
  )
{
  return;
}
