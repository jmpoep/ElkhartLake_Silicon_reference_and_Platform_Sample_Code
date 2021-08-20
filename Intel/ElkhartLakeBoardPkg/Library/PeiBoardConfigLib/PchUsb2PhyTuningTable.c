/** @file
  USB2 PHY tuning tables

@copyright
  Copyright (c) 2018 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.
  This file contains an 'Intel Peripheral Driver' and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the
  license agreement.
**/

#include <PlatformBoardConfig.h>

//
// Default USB2 PHY tuning parameters based on EV recommendations
//
USB2_PHY_TABLE mUsb2PhyTuningTable = USB2_PHY_TABLE_INIT (
  { 0x6, 0x0, 0x3, 0x0 },   // Port 1
  { 0x6, 0x0, 0x3, 0x0 },   // Port 2
  { 0x6, 0x0, 0x3, 0x0 },   // Port 3
  { 0x6, 0x0, 0x3, 0x0 },   // Port 4
  { 0x6, 0x0, 0x3, 0x0 },   // Port 5
  { 0x6, 0x0, 0x3, 0x0 },   // Port 6
  { 0x6, 0x0, 0x3, 0x0 },   // Port 7
  { 0x6, 0x0, 0x3, 0x0 },   // Port 8
  { 0x6, 0x0, 0x3, 0x0 },   // Port 9
  { 0x6, 0x0, 0x3, 0x0 },   // Port 10
  { 0x6, 0x0, 0x3, 0x0 },   // Port 11
  { 0x6, 0x0, 0x3, 0x0 },   // Port 12
  { 0x6, 0x0, 0x3, 0x0 },   // Port 13
  { 0x6, 0x0, 0x3, 0x0 },   // Port 14
  { 0x6, 0x0, 0x3, 0x0 },   // Port 15
  { 0x6, 0x0, 0x3, 0x0 }    // Port 16
);
