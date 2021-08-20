/** @file
  PCIe Initialization Library High Level Generic Functions

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2018 Intel Corporation.

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

#include <Library/PcieInitLib.h>


/**
Computes the Pre-Cursor, Cursor, and Post-Cursor from a preset

  @param[in]  Preset                      - Preset to compute coefficients for
  @param[in]  FullSwing                   - The full swing of the transmitter
  @param[out] PreCursor                   - Computed Pre-Cursor
  @param[out] Cursor                      - Computed Cursor
  @param[out] PostCursor                  - Computed Post-Cursor
**/
VOID
GetCoefficientsFromPreset (
  IN  UINT8                             Preset,
  IN  UINT8                             FullSwing,
  OUT UINT8                             *PreCursor,
  OUT UINT8                             *Cursor,
  OUT UINT8                             *PostCursor
  )
{
  INT32   PreCursorMilli;
  INT32   PostCursorMilli;

  PreCursorMilli  = 0;
  PostCursorMilli = 0;

  ///
  /// Get starting values from Table 4-16 of the PCIe Base Spec v3.0
  ///
  switch (Preset) {
    case  0:
      PreCursorMilli  =    0;
      PostCursorMilli = -250;
      break;

    case  1:
      PreCursorMilli  =    0;
      PostCursorMilli = -167;
      break;

    case  2:
      PreCursorMilli  =    0;
      PostCursorMilli = -200;
      break;

    case  3:
      PreCursorMilli  =    0;
      PostCursorMilli = -125;
      break;

    case  4:
      PreCursorMilli  =    0;
      PostCursorMilli =    0;
      break;

    case  5:
      PreCursorMilli  = -100;
      PostCursorMilli =    0;
      break;

    case  6:
      PreCursorMilli  = -125;
      PostCursorMilli =    0;
      break;

    case  7:
      PreCursorMilli  = -100;
      PostCursorMilli = -200;
      break;

    case  8:
      PreCursorMilli  = -125;
      PostCursorMilli = -125;
      break;

    case  9:
      PreCursorMilli  = -166;
      PostCursorMilli =    0;
      break;

    case 10:  ///< P10 is unsupported
    default:
      PreCursorMilli  = -100;
      PostCursorMilli = -200;
      DEBUG ((DEBUG_WARN, "GetCoefficientsFromPreset(): Unsupported Preset Requested: P%d. Using P7.\n", Preset));
      break;
  }

  ///
  /// Convert to absolute values
  ///
  if (PreCursorMilli < 0) {
    PreCursorMilli *= -1;
  }
  if (PostCursorMilli < 0) {
    PostCursorMilli *= -1;
  }

  ///
  /// Apply FullSwing
  ///
  PreCursorMilli  *= FullSwing;
  PostCursorMilli *= FullSwing;

  ///
  /// Convert to integers
  ///
  *PreCursor  = (( PreCursorMilli % 1000) >= 500) ? (UINT8) (( PreCursorMilli / 1000) + 1) : (UINT8) ( PreCursorMilli / 1000);
  *PostCursor = ((PostCursorMilli % 1000) >= 500) ? (UINT8) ((PostCursorMilli / 1000) + 1) : (UINT8) (PostCursorMilli / 1000);
  *Cursor     = FullSwing - (*PreCursor) - (*PostCursor);

  return;
}


