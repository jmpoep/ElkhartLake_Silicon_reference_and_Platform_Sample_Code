/** @file
  AmtSaveMebxProtocol definitions

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 Intel Corporation.

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
#ifndef _AMT_SAVE_MEBX_PROTOCOL_H_
#define _AMT_SAVE_MEBX_PROTOCOL_H_

///
/// AMT Save Mebx Data Protocol
/// The interface function is to save MEBX setting.
///

#define AMT_SAVE_MEBX_PROTOCOL_REVISION  1
typedef struct _AMT_SAVE_MEBX_PROTOCOL  AMT_SAVE_MEBX_PROTOCOL;

/**
  This function is used to save MEBX setting to NVRAM.

  @param[in]  DataSize           The size in bytes of the Mebx Data buffer.
  @param[in]  Data               The contents for the Mebx Data.

  @retval EFI_SUCCESS            Mebx config saved.
  @retval EFI_OUT_OF_RESOURCES   Not enough storage is available to hold the variable and its data.
  @retval EFI_DEVICE_ERROR       The variable could not be retrieved due to a hardware error.
**/
typedef
EFI_STATUS
(EFIAPI *AMT_SAVE_MEBX_DATA) (
  IN  UINTN                        DataSize,
  IN  VOID                         *Data
  );

/**
  AMT Save Mebx Protocol
  The interface function is to save MEBX setting.
  It is platform vendor's responsibility to implement the function instance.
**/
struct _AMT_SAVE_MEBX_PROTOCOL {
  AMT_SAVE_MEBX_DATA                SaveMebx;
};

extern EFI_GUID gAmtSaveMebxProtocolGuid;

#endif
