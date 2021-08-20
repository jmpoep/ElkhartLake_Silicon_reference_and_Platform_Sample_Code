/** @file
  PCH private PMC Library.
  All function in this library is available for PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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
#include <Library/PchCycleDecodingLib.h>
#include <Library/S3BootScriptLib.h>
#include <Library/PmcLib.h>
#include <Library/PmcPrivateLib.h>

/**
  This function locks down PMC (DebugModeLock)
**/
VOID
PmcLockWithS3BootScript (
  VOID
  )
{

  UINT32 PchPwrmBase;

  PchPwrmBase = PmcGetPwrmBase ();

  //
  // Set PWRM_CFG[27] prior to OS.
  //
  MmioOr32 (PchPwrmBase + R_PMC_PWRM_CFG, B_PMC_PWRM_CFG_DBG_MODE_LOCK);

  S3BootScriptSaveMemWrite (
    S3BootScriptWidthUint32,
    (UINTN) (PchPwrmBase + R_PMC_PWRM_CFG),
    1,
    (VOID *) (UINTN) (PchPwrmBase + R_PMC_PWRM_CFG)
    );

}

/**
  This S3 BootScript only function disables triggering Global Reset of both
  the Host and the ME partitions after CF9h write of 6h or Eh.
**/
VOID
PmcDisableCf9GlobalResetInS3BootScript (
  VOID
  )
{
  UINT32                          Data;

  UINT32                          PchPwrmBase;
  PchPwrmBase = PmcGetPwrmBase ();

  Data = MmioRead32 (PchPwrmBase + R_PMC_PWRM_ETR3);

  Data &= (UINT32) ~B_PMC_PWRM_ETR3_CF9GR;

  S3BootScriptSaveMemWrite (
    S3BootScriptWidthUint32,
    (UINTN) PchPwrmBase +
    R_PMC_PWRM_ETR3,
    1,
    &Data
    );
}

/**
  This S3 BootScript only function disables triggering Global Reset of both
  the Host and the ME partitions after CF9h write of 6h or Eh.
  Global Reset configuration is locked after programming
**/
VOID
PmcDisableCf9GlobalResetWithLockInS3BootScript (
  VOID
  )
{
  UINT32                          Data;

  UINT32                          PchPwrmBase;
  PchPwrmBase = PmcGetPwrmBase ();

  Data = MmioRead32 (PchPwrmBase + R_PMC_PWRM_ETR3);

  Data &= (UINT32) ~B_PMC_PWRM_ETR3_CF9GR;
  Data |= (UINT32) B_PMC_PWRM_ETR3_CF9LOCK;

  S3BootScriptSaveMemWrite (
    S3BootScriptWidthUint32,
    (UINTN) PchPwrmBase +
    R_PMC_PWRM_ETR3,
    1,
    &Data
    );
}

/**
  This function sets SLP_SX Stretching Policy and adds
  lock setting to S3 Boot Script
**/
VOID
PmcLockSlpSxStretchingPolicyWithS3BootScript (
  VOID
  )
{
  UINT32  PchPwrmBase;

  PchPwrmBase = PmcGetPwrmBase ();

  MmioOr8 (
    (UINTN) (PchPwrmBase + R_PMC_PWRM_GEN_PMCON_B + 2),
    (UINT8) ((B_PMC_PWRM_GEN_PMCON_B_SLPSX_STR_POL_LOCK) >> 16)
    );

  S3BootScriptSaveMemWrite (
    S3BootScriptWidthUint8,
    (UINTN) (PchPwrmBase + R_PMC_PWRM_GEN_PMCON_B + 2),
    1,
    (VOID *) (UINTN) (PchPwrmBase + R_PMC_PWRM_GEN_PMCON_B + 2)
    );
}

/**
  This function sets SMI Lock with S3 Boot Script programming
**/
VOID
PmcLockSmiWithS3BootScript (
  VOID
  )
{
  UINT32  PchPwrmBase;

  PchPwrmBase = PmcGetPwrmBase ();

  MmioOr8 ((UINTN) (PchPwrmBase + R_PMC_PWRM_GEN_PMCON_B), B_PMC_PWRM_GEN_PMCON_B_SMI_LOCK);

  S3BootScriptSaveMemWrite (
    S3BootScriptWidthUint8,
    (UINTN) (PchPwrmBase + R_PMC_PWRM_GEN_PMCON_B),
    1,
    (VOID *) (UINTN) (PchPwrmBase + R_PMC_PWRM_GEN_PMCON_B)
    );
}

/**
  This function locks static power gating configuration with S3 Boot Script programming
**/
VOID
PmcLockFunctionDisableConfigWithS3BootScript (
  VOID
  )
{
  UINT32  PchPwrmBase;

  PchPwrmBase = PmcGetPwrmBase ();

  MmioOr32 (PchPwrmBase + R_PMC_PWRM_ST_PG_FDIS_PMC_1, (UINT32) (B_PMC_PWRM_ST_PG_FDIS_PMC_1_ST_FDIS_LK));

  S3BootScriptSaveMemWrite (
    S3BootScriptWidthUint8,
    (UINTN) (PchPwrmBase + R_PMC_PWRM_ST_PG_FDIS_PMC_1),
    1,
    (VOID *) (UINTN) (PchPwrmBase + R_PMC_PWRM_ST_PG_FDIS_PMC_1)
    );
}

/**
  This function locks PMC Set Strap Message interface with S3 Boot Script programming
**/
VOID
PmcLockSetStrapMsgInterfaceWithS3BootScript (
  VOID
  )
{
  UINT32  PchPwrmBase;

  PchPwrmBase = PmcGetPwrmBase ();

  MmioOr32 ((UINTN) (PchPwrmBase + R_PMC_PWRM_SSML), B_PMC_PWRM_SSML_SSL);

  S3BootScriptSaveMemWrite (
    S3BootScriptWidthUint8,
    (UINTN) (PchPwrmBase + R_PMC_PWRM_SSML),
    1,
    (VOID *) (UINTN) (PchPwrmBase + R_PMC_PWRM_SSML)
    );
}

#define PMC_CRID_UIP_TIMEOUT  0x1000000
/**
  Wait for CRID update ready.
**/
STATIC
VOID
PmcWaitForCridUip (
  VOID
  )
{
  UINT32    PchPwrmBase;
  UINT32    Timeout;

  PchPwrmBase = PmcGetPwrmBase ();
  Timeout     = 0;
  while (MmioRead32 (PchPwrmBase + R_PMC_PWRM_CRID_UIP) & B_PMC_PWRM_CRID_UIP_CRIP_UIP) {
    if (Timeout++ > PMC_CRID_UIP_TIMEOUT) {
      ASSERT (FALSE);
      break;
    }
  }
}

/**
  Select CRID0 mode.
  The silicon Revision ID will be changed. Refer to silicon spec for RID value of CRID0.
**/
VOID
PmcSetCrid0WithS3BootScript (
  VOID
  )
{
  UINT32  PchPwrmBase;
  UINT32  Crid;
  UINT32  Data32And;
  UINT32  Data32;

  PchPwrmBase = PmcGetPwrmBase ();
  Crid = MmioRead32 (PchPwrmBase + R_PMC_PWRM_CRID);
  //
  // If Crid is locked or RID_SEL is changed then skip the detection.
  //
  if ((Crid & B_PMC_PWRM_CRID_CRID_LK) != 0) {
    ASSERT (FALSE);
  }

  PmcWaitForCridUip ();
  MmioWrite32 (PchPwrmBase + R_PMC_PWRM_CRID, V_PMC_PWRM_CRID_RID_SEL_CRID0);
  PmcWaitForCridUip ();

  Data32And = B_PMC_PWRM_CRID_UIP_CRIP_UIP;
  Data32    = 0;
  S3BootScriptSaveMemPoll (
    S3BootScriptWidthUint32,
    PchPwrmBase + R_PMC_PWRM_CRID_UIP,
    &Data32And,
    &Data32,
    1,
    PMC_CRID_UIP_TIMEOUT
    );

  S3BootScriptSaveMemWrite (
    S3BootScriptWidthUint32,
    (UINTN) (PchPwrmBase + R_PMC_PWRM_CRID),
    1,
    (VOID *) (UINTN) (PchPwrmBase + R_PMC_PWRM_CRID)
    );

  S3BootScriptSaveMemPoll (
    S3BootScriptWidthUint32,
    PchPwrmBase + R_PMC_PWRM_CRID_UIP,
    &Data32And,
    &Data32,
    1,
    PMC_CRID_UIP_TIMEOUT
    );
}

/**
  Lock CRID.
**/
VOID
PmcLockCridWithS3BootScript (
  VOID
  )
{
  UINT32  PchPwrmBase;
  PchPwrmBase = PmcGetPwrmBase ();

  MmioOr32 (
    PchPwrmBase + R_PMC_PWRM_CRID,
    B_PMC_PWRM_CRID_CRID_LK
    );

  S3BootScriptSaveMemWrite (
    S3BootScriptWidthUint32,
    (UINTN) (PchPwrmBase + R_PMC_PWRM_CRID),
    1,
    (VOID *) (UINTN) (PchPwrmBase + R_PMC_PWRM_CRID)
    );
}
