/** @file
  Internal header file for PCH FIA library

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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
#ifndef __PCH_FIA_LIB_INTERNAL_H__
#define __PCH_FIA_LIB_INTERNAL_H__

#include <Uefi/UefiBaseType.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PchFiaLib.h>
#include <Library/PciExpressHelpersLib.h>
#include <Register/PchRegsFia.h>

typedef enum {
  PchFiaOwnerUsb3 = 0,
  PchFiaOwnerDmi,
  PchFiaOwnerPcie,
  PchFiaOwnerSata,
  PchFiaOwnerGbe,
  PchFiaOwnerUfs,
  PchFiaOwnerTsn,
  PchFiaOwnerPcie2nd,
  PchFiaOwnerInvalid
} PCH_FIA_LANE_OWNER;

typedef struct {
  PCH_SBI_PID  SbPortId;
} FIA_INSTANCE;

/**
  Return FIA lane owner.

  @param[in] FiaInst  FIA Instance
  @param[in] LaneNum  FIA lane number

  @return  Code of the FIA lane owner, PchFiaOwnerInvalid if lane number wasn't valid
**/
PCH_FIA_LANE_OWNER
PchFiaGetLaneOwner (
  IN  FIA_INSTANCE FiaInst,
  IN  UINT8        LaneNum
  );

/**
  Returns number of FIA lanes

  @return Number of FIA lanes
**/
UINT8
PchFiaGetMaxLaneNum (
  VOID
  );

/**
  Checks if given lane is DMI

  @param[in]  FiaLaneNum  Fia lane num

  @return TRUE if given lane is DMI, FALSE otherwise
**/
BOOLEAN
PchFiaIsLaneDmi (
  IN UINT8  FiaLaneNum
  );

/**
  Converts FIA 14.0/15.0 lane owner encoding to version independent encoding.

  @param[in] LaneOwner  Lane owner value corresponding to the FIA 14.0/15.0 lane owner encoding
  @param[in] LaneNum    Fia lane number

  @retval PCH_FIA_LANE_OWNER  FIA lane owner in version independent format.
**/
PCH_FIA_LANE_OWNER
PchFiaDecodeOwner (
  IN UINT32  LaneOwner,
  IN UINT8   LaneNum
  );

/**
  Returns a FIA lane number for a given UFS lane.

  @param[in]  UfsControllerIndex  Index of the UFS controller
  @param[in]  UfsLaneIndex        Index of the UFS lane on given controller
  @param[out] LaneNum             Optional. Pointer to the variable that stores lane number.
                                  The output value is only valid if this function returns TRUE.

  @return TRUE if given UFS lane owns FIA lane, FALSE otherwise
**/
BOOLEAN
PchFiaGetUfsLaneNum (
  IN  UINT32  UfsControllerIndex,
  IN  UINT32  UfsLaneIndex,
  OUT UINT8   *LaneNum
  );
#endif
