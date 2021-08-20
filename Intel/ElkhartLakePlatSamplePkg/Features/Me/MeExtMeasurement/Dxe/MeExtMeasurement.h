/** @file
  Header file for CSME Extended Measurement library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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
#ifndef _DXE_ME_EXT_MEASUREMENT_LIB_H_
#define _DXE_ME_EXT_MEASUREMENT_LIB_H_

#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PciLib.h>
#include <Protocol/MePolicy.h>
#include <Protocol/Tcg2Protocol.h>
#include <Library/HobLib.h>
#include <ConfigBlock.h>
#include <Library/ConfigBlockLib.h>
#include <Library/SiConfigBlockLib.h>
#include <Library/TpmMeasurementLib.h>
#include <Library/DxeMeLib.h>
#include <Library/MbpDataLib.h>
#include <Library/MeChipsetLib.h>
#include <MkhiMsgs.h>
#include <Register/MeRegs.h>
#include <Register/HeciRegs.h>
#include <MeBiosPayloadData.h>
#include <MeBiosPayloadHob.h>
#include <AmtConfig.h>

//
// Standard event type
// @TODO: Below definitions of EV_NONHOST_CONFIG & EV_NONHOST_INFO should be removed after adding these definitions into Edk2\MdePkg\Include\IndustryStandard\UefiTcgPlatform.h file.
//
#define EV_NONHOST_CONFIG              ((TCG_EVENTTYPE) 0x00000010)
#define EV_NONHOST_INFO                ((TCG_EVENTTYPE) 0x00000011)

#define MAX_EVENTLOG_SIZE              1024
#define SIG_LENGTH                     20
#define HER_REG_COUNT_SHA384           12   // HER1-HER12
#define HER_REG_COUNT_SHA256           8    // HER1-HER8

///
/// CSME Measurement Event in TPM Log
///
typedef struct {
  UINT8                    Signature [SIG_LENGTH];
  UINT32                   ERHashAlgorithm;
  UINT8                    Events [MAX_EVENTLOG_SIZE];
} CSME_MEASUREMENT_EVENT;

/**
  Ready To Boot Event call back function performs getting AMT Config data from CSME and extending to TPM-PCR[1]

  @param[in] Event         The event that triggered this notification function
  @param[in] Context       Pointer to the notification functions context
**/
VOID
EFIAPI
AmtConfigReadyToBootEvent (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  );

/**
  End of DXE CallBack event to extend CSME Measurment to TPM-PCR[0] & AMT Config data to TPM-PCR[1]

  @param[in] Event                The event that triggered this notification function
  @param[in] Context    Pointer to the notification functions context

**/
VOID
EFIAPI
ExtendCsmeMeasurementToTpmPcr (
  IN EFI_EVENT Event,
  IN VOID      *Context
  );

#endif // _DXE_ME_EXT_MEASUREMENT_LIB_H_
