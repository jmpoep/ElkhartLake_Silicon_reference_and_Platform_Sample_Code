/** @file
  Definitions for DisableBmeProtocol

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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
#ifndef _DISABLE_TBT_BME_PROTOCOL_H_
#define _DISABLE_TBT_BME_PROTOCOL_H_

//
// Forward reference for pure ANSI compatability
//
typedef struct _EFI_DISABLE_TBT_BME_PROTOCOL EFI_DISABLE_TBT_BME_PROTOCOL;

/**
  Disabling TBT BME bit under UEFI Shell environment

  @param[in] Event     - A pointer to the Event that triggered the callback.
  @param[in] Context   - A pointer to private data registered with the callback function.
**/
typedef
VOID
(EFIAPI *DISABLE_BUS_MASTER_ENABLE) (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  );

//
// Disable TBT BME  Protocol structure.
//
struct _EFI_DISABLE_TBT_BME_PROTOCOL {
  DISABLE_BUS_MASTER_ENABLE DisableBme;
};

//
// Disable iTBT BME Protocol GUID variable.
//
extern EFI_GUID gDxeDisableITbtBmeProtocolGuid;

#endif
