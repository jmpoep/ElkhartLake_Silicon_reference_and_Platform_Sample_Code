//
// This file contains 'Framework Code' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may not be modified, except as allowed by
// additional terms of your license agreement.
//
/** @file
  Implementation of TraceHub Filter.

  Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

**/

#include <Base.h>
#include <Library/DebugLib.h>
#include <Library/TraceHubHookLib.h>
#include "EnableTraceHubData.h"

/**
  Determine whether to enable BIOS Debug Message tracing to Trace Hub.

  @param  SeverityType    The severity level of data.

  @retval TRUE            Enable trace hub data.
  @retval FALSE           Disable trace hub data.

**/
BOOLEAN
EFIAPI
EnableTraceHubData (
  IN TRACE_HUB_SEVERITY_TYPE    SeverityType
  )
{
  UINT8         RegValue;
  RETURN_STATUS Status;
  UINT8         Routing;
  UINT8         DebugLevel;
  BOOLEAN       Enable;

  //
  // ScratchPad2 Register is not found. The message will always be enabled.
  //
  RegValue = 0;
  Status   = TraceHubScratchPad2RegValue (&RegValue);
  if (RETURN_ERROR (Status)) {
    return TRUE;
  }

  Routing = RegValue & BIT0;
  if (Routing == TraceHubRoutingDisable) {
    return FALSE;
  }

  Enable = FALSE;
  DebugLevel = (RegValue & (BIT1 | BIT2)) >> 1;
  if (DebugLevel == TraceHubDebugLevelError) {
    if ((SeverityType == SeverityFatal || SeverityType == SeverityError)) {
      Enable = TRUE;
    }
  } else if (DebugLevel == TraceHubDebugLevelErrorWarning) {
    if ((SeverityType == SeverityFatal ||
          SeverityType == SeverityError ||
          SeverityType == SeverityWarning)) {
      Enable = TRUE;
    }
  } else if (DebugLevel == TraceHubDebugLevelErrorWarningInfo) {
    if ((SeverityType == SeverityFatal ||
          SeverityType == SeverityError ||
          SeverityType == SeverityWarning ||
          SeverityType == SeverityNormal)) {
      Enable = TRUE;
    }
  } else if (DebugLevel == TraceHubDebugLevelErrorWarningInfoVerbose) {
    Enable = TRUE;
  }

  return Enable;
}
