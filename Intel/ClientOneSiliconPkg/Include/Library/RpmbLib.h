/** @file
  Header file for the RPMB library.

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

@par Specification
**/

#ifndef _RPMB_LIB_H_
#define _RPMB_LIB_H_

#define RPMB_STUFF_SIZE     196
#define RPMB_MAC_SIZE       32
#define RPMB_KEY_SIZE       RPMB_MAC_SIZE
#define RPMB_DATA_SIZE      256
#define RPMB_NONCE_SIZE     16

#define RPMB_KEY_PROGRAM    0x01
#define RPMB_COUNTER_READ   0x02
#define RPMB_DATA_WRITE     0x03
#define RPMB_DATA_READ      0x04
#define RPMB_RESULT_READ    0x05

typedef enum {
  RpmbResultOk                    = 0,
  RpmbResultGeneralFailure        = 1,
  RpmbResultAuthenticationFailure = 2,
  RpmbResultCounterFailure        = 3,
  RpmbResultAddressFailure        = 4,
  RpmbResultWriteFailue           = 5,
  RpmbResultReadFailure           = 6,
  RpmbResultKeyNotYetProgrammed   = 7
} RPMB_RESULT;

#pragma pack(push, 1)

typedef struct {
  UINT8     Stuff[RPMB_STUFF_SIZE];
  UINT8     Mac[RPMB_MAC_SIZE];
  UINT8     Data[RPMB_DATA_SIZE];
  UINT8     Nonce[RPMB_NONCE_SIZE];
  UINT32    WriteCounter;
  UINT16    Address;
  UINT16    BlockCount;
  UINT8     Reserved;
  UINT8     Result;
  UINT8     Response;
  UINT8     Request;
} RPMB_FRAME;

#pragma pack(pop)

#define RPMB_FRAME_SIZE           sizeof (RPMB_FRAME)
#define RPMB_FRAME_CONTENT_SIZE   (sizeof (RPMB_FRAME) - OFFSET_OF (RPMB_FRAME, Data))

/**
  Issues a Result Register Read Request and returns the Result Frame.

  @param [out]  Frame         A pointer to an RPMB Frame Buffer.

  @retval     EFI_SUCCESS             Result Register Read Request transaction was successful.
  @retval     EFI_INVALID_PARAMETER   Frame is NULL.

**/
EFI_STATUS
EFIAPI
RpmbRequestResult (
    OUT RPMB_FRAME          *Frame
  );

/**
  Test the RPMB functionality.

  @param      None.

  @retval     EFI_SUCCESS         RPMB test success.
  @retval     Other               RPMB test failure.

**/
EFI_STATUS
EFIAPI
RpmbTest (
  VOID
  );

#endif
