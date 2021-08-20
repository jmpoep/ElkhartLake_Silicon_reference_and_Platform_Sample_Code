/** @file
  DCI private library.
  All functions from this library are available in PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2019 Intel Corporation.

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
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/PchPcrLib.h>
#include <Register/PchPcrRegs.h>
#include <Register/DciRegs.h>

/**
  Return HDCI Debug Enabled status.

  @retval TRUE   HDCI/HEEN Debug is enabled
  @retval FALSE  HDCI/HEEN Debug is disabled
**/
BOOLEAN
IsHdciDebugEnabled (
  VOID
  )
{
  UINT16 Data;

  Data = PchPcrRead16 (PID_DCI, R_DCI_PCR_ECTRL);

  if (Data & B_DCI_PCR_ECTRL_HDCIEN) {
    DEBUG ((DEBUG_INFO, "HDCI Debug Enabled\n"));
    return TRUE;
  }

  DEBUG ((DEBUG_INFO, "HDCI Debug Disabled\n"));
  return FALSE;
}

/**
  Return DCI Debug Enabled status.

  @retval TRUE   DCI Debug is enabled
  @retval FALSE  DCI Debug is disabled
**/
BOOLEAN
IsDciDebugEnabled (
  VOID
  )
{
  UINT16 Data;

  Data = PchPcrRead16 (PID_DCI, R_DCI_PCR_ECTRL);

  if (Data & B_DCI_PCR_ECTRL_DBG_EN) {
    DEBUG ((DEBUG_INFO, "DCI Debug Enabled\n"));
    return TRUE;
  }

  DEBUG ((DEBUG_INFO, "DCI Debug Disabled\n"));
  return FALSE;
}

/**
  Return USB2 DbC enable status.

  @retval TRUE   USB2 DbC is enabled
  @retval FALSE  USB2 DbC is disabled
**/
BOOLEAN
IsUsb2DbcDebugEnabled (
  VOID
  )
{
  UINT16 Data;

  Data  = PchPcrRead16 (PID_DCI, R_DCI_PCR_ECTRL);
  Data &= (B_DCI_PCR_ECTRL_DBG_EN | B_DCI_PCR_ECTRL_USB3DBCEN | B_DCI_PCR_ECTRL_USB2DBCEN);

  // If ECTRL[8, 6, 5] = 1b, 1b, 1b, then USB2 DbC is enabled.
  if (Data == (UINT16)(B_DCI_PCR_ECTRL_DBG_EN | B_DCI_PCR_ECTRL_USB3DBCEN | B_DCI_PCR_ECTRL_USB2DBCEN)) {
    DEBUG ((DEBUG_INFO, "USB2 DbC is enabled\n"));
    return TRUE;
  }

  DEBUG ((DEBUG_INFO, "USB2 DbC is disabled\n"));
  return FALSE;
}

/**
  Return PCH USB DbC connection status

  @retval TRUE   PCH USB DbC is connected
  @retval FALSE  PCH USB DbC is not connected
**/
BOOLEAN
IsPchUsbDbcConnected (
  VOID
  )
{
  if (PchPcrRead32 (PID_DCI, R_DCI_PCR_EARBCTRL) & B_DCI_PCR_EARBCTRL_ARB_GNT_S_DBC) {
    DEBUG ((DEBUG_INFO, "PCH USB DbC is connected.\n"));
    return TRUE;
  }
  return FALSE;
}

/**
  Return DCI host connection status

  @retval TRUE   DCI host is connected
  @retval FALSE  DCI host is not connected
**/
BOOLEAN
IsDciHostConnected (
  VOID
  )
{
  if (PchPcrRead16 (PID_DCI, R_DCI_PCR_ECTRL) & B_DCI_PCR_ECTRL_EGRANT) {
    DEBUG ((DEBUG_INFO, "DCI Host is connected\n"));
    return TRUE;
  } else {
    DEBUG ((DEBUG_INFO, "DCI host is not connected\n"));
    return FALSE;
  }
}

/**
  Return 4-wire DCI OOB connection status

  @retval TRUE   4-wire DCI OOB is connected
  @retval FALSE  4-wire DCI OOB is not connected
**/
BOOLEAN
Is4wireDciOobConnected (
  VOID
  )
{
  if (PchPcrRead32 (PID_DCI, R_DCI_PCR_EARBCTRL) & B_DCI_PCR_EARBCTRL_ARB_GNT_DCI_OOB) {
    if ((PchPcrRead32 (PID_DCI, R_DCI_PCR_PORT_ID) & V_DCI_PCR_PORT_ID_MASK) <= V_DCI_PCR_PORT_ID_MISC) {
      DEBUG ((DEBUG_INFO, "DCI OOB 4-wire is connected.\n"));
      return TRUE;
    }
  }
  return FALSE;
}

