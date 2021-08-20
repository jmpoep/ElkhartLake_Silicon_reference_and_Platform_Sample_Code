//
// This file contains 'Framework Code' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may not be modified, except as allowed by
// additional terms of your license agreement.
//
/** @file
  Null instance of TraceHub Hook Lib.

  Copyright (c) 2014 - 2017, Intel Corporation. All rights reserved.<BR>
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

**/

#include <Base.h>

/**
  Calculate TraceHub Trace Address.
  Dummy function call, should be implemented by Platform

  @param  Master         Master is being used.
  @param  Channel        Channel is being used.
  @param  TraceAddress   TraceHub Address for the Master/Channel is being used.

  @retval                RETURN_UNSUPPORTED  Not implemented.

**/
RETURN_STATUS
EFIAPI
TraceHubMmioTraceAddress (
  IN  UINT16    Master,
  IN  UINT16    Channel,
  OUT UINT32    *TraceAddress
  )
{
  return RETURN_UNSUPPORTED;
}

/**
  Return Scratch Pad2 Register Value.

  @param [out] ScratchPad2RegValue Scratch Pad2 Register Value.

  @retval RETURN_SUCCESS      Retrieve Scratch Pad2 Register Value.
  @retval RETURN_UNSUPPORTED  Not implemented.
  @retval Other               Fail to Retrieve Scratch Pad2 Register Value.

**/
RETURN_STATUS
EFIAPI
TraceHubScratchPad2RegValue (
  OUT UINT8    *ScratchPad2RegValue
  )
{
  return RETURN_UNSUPPORTED;
}
