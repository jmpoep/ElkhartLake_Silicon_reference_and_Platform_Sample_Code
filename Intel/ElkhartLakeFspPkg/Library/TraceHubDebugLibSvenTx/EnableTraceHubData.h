//
// This file contains 'Framework Code' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may not be modified, except as allowed by
// additional terms of your license agreement.
//
/** @file
  BIOS Debug Message Tracing Catalog

  Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

**/

#ifndef __ENABLE_TRACE_HUB_DATA_H__
#define __ENABLE_TRACE_HUB_DATA_H__

#include <Library/TraceHubDebugLib.h>

typedef enum {
  TraceHubRoutingDisable = 0,
  TraceHubRoutingEnable,
  TraceHubRoutingMax
} TRACE_HUB_ROUTING;

typedef enum {
  TraceHubDebugLevelError = 0,
  TraceHubDebugLevelErrorWarning,
  TraceHubDebugLevelErrorWarningInfo,
  TraceHubDebugLevelErrorWarningInfoVerbose,
  TraceHubDebugLevelMax
} TRACE_HUB_DEBUG_LEVEL;

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
  );

#endif // __TRACE_HUB_DISCARD_DATA_H__
