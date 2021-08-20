/** @file
  RPMB Library.

  Provides RPMB abstractions.

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
#include <Base.h>

#include <Library/RpmbLib.h>

#include <Library/BaseCryptLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BlockIoWrapperLib.h>
#include <Library/DebugLib.h>
#include <Library/DevicePathLib.h>
#include <Library/IoLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>

UINT8   *mKey = NULL;
UINT8   mKeyValue[RPMB_KEY_SIZE];
CHAR8   mFixedKey[] = "1234567890ABCDEFFEDCBA0987654321";

/**
  Print Bytes.

  @param [in] Signature     The Error Level to use for the debug print.
  @param [in] Data          The data buffer to print.
  @param [in] DataSize      The size in bytes of data in the data buffer.


  @return     Index   The number of bytes printed.
**/
UINTN
EFIAPI
PrintBytes (
  IN  UINTN   ErrorLevel,
  IN  UINT8   *Data,
  IN  UINTN   DataSize
  )
{
  UINTN   Index = 0;

  DEBUG_CODE_BEGIN ();
  DEBUG ((ErrorLevel, "0x"));
  for (Index = 0; Index < DataSize; Index++) {
    DEBUG ((ErrorLevel, "%02X", Data[Index]));
  }
  DEBUG ((ErrorLevel, "\n"));
  DEBUG_CODE_END ();

  return Index;
}

/**
  Computes an HMAC SHA256 signature for a data message.

  @param[in]  Data             The data buffer to verify.
  @param[in]  DataSize         The size in bytes of data in the data buffer.
  @param[in out] Signature     The HMAC SHA256 signature computed.


  @return     EFI_SUCCESS      The signature was computed successfully.
  @return     Others           Failed to compute the signature.
**/
EFI_STATUS
EFIAPI
ComputeHmacSha256Signature (
  IN CONST UINT8  *HmacSha256Key,
  IN       UINTN   KeySize,
  IN CONST UINT8   *Data,
  IN       UINTN   DataSize,
  IN OUT   UINT8   *Signature
  )
{
  UINTN      ContextSize;
  VOID       *HmacContext;
  UINT8      Digest[64];
  BOOLEAN    Status;

  if (Data == NULL || Signature == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // HMAC-SHA Digest Validation
  //
  ZeroMem (Digest, 64);

  ContextSize = HmacSha256GetContextSize ();
  HmacContext = AllocatePool (ContextSize);

  DEBUG ((DEBUG_VERBOSE, "Init... "));

  Status  = HmacSha256Init (HmacContext, HmacSha256Key, KeySize);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_VERBOSE, "[Fail]"));
    return EFI_ABORTED;
  }

  DEBUG ((DEBUG_VERBOSE, "Update... "));

  Status  = HmacSha256Update (HmacContext, Data, DataSize);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_VERBOSE, "[Fail]"));
    return EFI_ABORTED;
  }

  DEBUG ((DEBUG_VERBOSE, "Finalize...\n"));

  Status  = HmacSha256Final (HmacContext, Digest);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_VERBOSE, "[Fail]"));
    return EFI_ABORTED;
  }

  CopyMem (Signature, Digest, SHA256_DIGEST_SIZE);
  FreePool (HmacContext);

  return EFI_SUCCESS;
}

/**
  Processes the Result code of an RPMB transaction.

  @param [in] Result      An RPMB transaction Result value.

  @retval   Various       Return value representation of the Result code.

**/
EFI_STATUS
EFIAPI
RpmbProcessResult (
    IN  RPMB_RESULT         Result
  )
{
  EFI_STATUS                Status;

  if (Result & BIT7) {
    DEBUG ((DEBUG_ERROR, "RPMB Result: Write Counter Expired\n"));
  }

  switch (Result & 0x7F) {
    case RpmbResultOk:
      Status = EFI_SUCCESS;
      break;

    case RpmbResultGeneralFailure:
      DEBUG ((DEBUG_ERROR, "RPMB Result: General Failure\n"));
      Status = EFI_DEVICE_ERROR;
      break;

    case RpmbResultAuthenticationFailure:
      DEBUG ((DEBUG_ERROR, "RPMB Result: General Failure\n"));
      Status = EFI_SECURITY_VIOLATION;
      break;

    case RpmbResultCounterFailure:
      DEBUG ((DEBUG_ERROR, "RPMB Result: Counter Failure\n"));
      Status = EFI_DEVICE_ERROR;
      break;

    case RpmbResultAddressFailure:
      DEBUG ((DEBUG_ERROR, "RPMB Result: Address Failure\n"));
      Status = EFI_INVALID_PARAMETER;
      break;

    case RpmbResultWriteFailue:
      DEBUG ((DEBUG_ERROR, "RPMB Result: Write Failure\n"));
      Status = EFI_DEVICE_ERROR;
      break;

    case RpmbResultReadFailure:
      DEBUG ((DEBUG_ERROR, "RPMB Result: Read Failure\n"));
      Status = EFI_DEVICE_ERROR;
      break;

    case RpmbResultKeyNotYetProgrammed:
      DEBUG ((DEBUG_WARN, "RPMB Result: Authentication key not yet programmed\n"));
      Status = EFI_NOT_STARTED;
      break;

    default:
      DEBUG ((DEBUG_ERROR, "RPMB Result: Unknown result code\n"));
      Status = EFI_INVALID_PARAMETER;
      break;
  }

  return Status;
}

/**
  Verify an RPMB frame.

  @param [in] Frame         A pointer to a signed RPMB Frame.

  @retval     EFI_SUCCESS             Frame verification succeeded.
  @retval     EFI_SECURITY_VIOLATION  Frame verification failed.
  @retval     EFI_NOT_STARTED         RPMB Key is not known locally.
  @retval     EFI_ABORTED             HMAC calculation failed.
  @retval     EFI_INVALID_PARAMETER   Frame is NULL.

**/
EFI_STATUS
EFIAPI
RpmbVerifyFrame (
    IN  RPMB_FRAME          *Frame
  )
{
  EFI_STATUS                Status;
  UINT8                     LocalMac[RPMB_MAC_SIZE];

  if (Frame == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (mKey == NULL) {
    return EFI_NOT_STARTED;
  }

  Status = ComputeHmacSha256Signature (
    mKey,
    RPMB_KEY_SIZE,
    Frame->Data,
    RPMB_FRAME_CONTENT_SIZE,
    LocalMac
    );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "RPMB: Verify: Failed to calculate HMAC.\n"));
    return Status;
  }

  if (CompareMem (LocalMac, Frame->Mac, RPMB_MAC_SIZE) != 0) {
    DEBUG ((DEBUG_ERROR, "RPMB: HMAC mismatch.\n"));

    DEBUG ((DEBUG_INFO, "RPMB: LocalMac:    "));
    PrintBytes (DEBUG_INFO, LocalMac, RPMB_MAC_SIZE);
    DEBUG ((DEBUG_INFO, "RPMB: Frame->Mac:  "));
    PrintBytes (DEBUG_INFO, Frame->Mac, RPMB_MAC_SIZE);

    Status = EFI_SECURITY_VIOLATION;
    ASSERT_EFI_ERROR (Status);
  }

  return Status;
}

/**
  Sign an RPMB frame.

  @param [in, out]  Frame       A pointer to an unsigned RPMB Frame.

  @retval     EFI_SUCCESS             Frame signed succeeded.
  @retval     EFI_NOT_STARTED         RPMB Key is not known locally.
  @retval     EFI_ABORTED             HMAC calculation failed.
  @retval     EFI_INVALID_PARAMETER   Frame is NULL.

**/
EFI_STATUS
EFIAPI
RpmbSignFrame (
    IN OUT  RPMB_FRAME      *Frame
  )
{
  EFI_STATUS                Status;

  if (Frame == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (mKey == NULL) {
    return EFI_NOT_STARTED;
  }

  Status = ComputeHmacSha256Signature (
    mKey,
    RPMB_KEY_SIZE,
    Frame->Data,
    RPMB_FRAME_CONTENT_SIZE,
    Frame->Mac
    );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "RPMB: Sign: Failed to calculate HMAC.\n"));
  }

  return Status;
}

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
  )
{
  EFI_STATUS                Status;

  if (Frame == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  ZeroMem (Frame, RPMB_FRAME_SIZE);

  Frame->Request = RPMB_RESULT_READ;

  Status = SecurityProtocolTransaction (
            RPMB_FRAME_SIZE,
            Frame,
            TRUE
          );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "RPMB: Failed to send Result Register Read Request.\n"));
  }

  return Status;
}

/**
  Programs the RPMB Authentication Key.

  @param [in] Key            A pointer to an RPMB_KEY_SIZE buffer containing the key to program.

  @retval     EFI_SUCCESS             RPMB Key was programmed successfully.
  @retval     EFI_INVALID_PARAMETER   Key is NULL.
  @retval     EFI_ALREADY_STARTED     The RPMB Key is already programmed.

**/
EFI_STATUS
EFIAPI
RpmbProgramKey (
    IN  UINT8               *Key
  )
{
  EFI_STATUS                Status;
  RPMB_FRAME                Frame;
  UINTN                     Index;

  if (Key == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  ZeroMem (&Frame, RPMB_FRAME_SIZE);

  Frame.Request = RPMB_KEY_PROGRAM;
  for (Index = 0; Index < RPMB_KEY_SIZE; Index++) {
    Frame.Mac[Index] = Key[Index];
    mKeyValue[Index] = Key[Index];
  }
  mKey = mKeyValue;

  Status = SecurityProtocolTransaction (
            RPMB_FRAME_SIZE,
            &Frame,
            FALSE
          );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "RPMB: An error occurred provisioning the RPMB key.\n"));
    return Status;
  }

  Status = RpmbRequestResult (&Frame);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  ASSERT (Frame.Response == RPMB_KEY_PROGRAM);

  if (Frame.Result == RpmbResultWriteFailue) {
    DEBUG ((DEBUG_WARN, "RPMB: Authentication Key programming failed (already programmed?)\n"));
    return EFI_ALREADY_STARTED;
  }

  Status = RpmbProcessResult (Frame.Result);

  return Status;
}

/**
  Retrieves the RPMB Write Counter.

  @param [out]  WriteCounter      A pointer to a UINT32 to store the Write Counter.

  @retval     EFI_SUCCESS             Write Counter retrieved successfully.
  @retval     EFI_INVALID_PARAMETER   WriteCounter is NULL.
  @retval     EFI_SECURITY_VIOLATION  The Nonce returned does not match the Nonce sent.

**/
EFI_STATUS
EFIAPI
RpmbGetCounter (
    OUT UINT32              *WriteCounter
  )
{
  EFI_STATUS                Status;
  RPMB_FRAME                Frame;
  UINT8                     LocalNonce[RPMB_NONCE_SIZE];

  if (WriteCounter == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  *WriteCounter = 0x0;

  RandomBytes (LocalNonce, RPMB_NONCE_SIZE);

  ZeroMem (&Frame, RPMB_FRAME_SIZE);

  Frame.Request = RPMB_COUNTER_READ;
  CopyMem (Frame.Nonce, LocalNonce, RPMB_NONCE_SIZE);

  Status = SecurityProtocolTransaction (
            RPMB_FRAME_SIZE,
            &Frame,
            TRUE
          );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "RPMB: Failed to send Write Counter Read Request.\n"));
    return Status;
  }

  Status = RpmbVerifyFrame (&Frame);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "RPMB: Failed to verify Write Counter Response.\n"));
    return Status;
  }

  ASSERT (Frame.Response == RPMB_COUNTER_READ);

  Status = RpmbProcessResult (Frame.Result);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (CompareMem (LocalNonce, Frame.Nonce, RPMB_NONCE_SIZE) == 0) {
    *WriteCounter = SwapBytes32 (Frame.WriteCounter);
  } else {
    DEBUG ((DEBUG_ERROR, "RPMB: Nonce mismatch.\n"));

    DEBUG ((DEBUG_INFO, "RPMB: LocalNonce:  "));
    PrintBytes (DEBUG_INFO, LocalNonce, RPMB_NONCE_SIZE);
    DEBUG ((DEBUG_INFO, "RPMB: Frame.Nonce: "));
    PrintBytes (DEBUG_INFO, Frame.Nonce, RPMB_NONCE_SIZE);

    Status = EFI_SECURITY_VIOLATION;
    ASSERT_EFI_ERROR (Status);
  }

  return Status;
}

/**
  Read data from RPMB.

  @param [in]   Address             The starting block for the RPMB read operation.
  @param [in]   BlockCount          The number of blocks to read.
  @param [out]  Data                A data buffer of size BlockCount * RPMB_DATA_SIZE bytes.

  @retval     EFI_SUCCESS             The data was read successfully.
  @retval     EFI_INVALID_PARAMETER   Data is NULL.
  @retval     EFI_UNSUPPORTED         BlockCount > 1.
  @retval     EFI_SECURITY_VIOLATION  The Nonce returned does not match the Nonce sent.

**/
EFI_STATUS
EFIAPI
RpmbReadData (
    IN  UINT16              Address,
    IN  UINT16              BlockCount,
    OUT UINT8               *Data
  )
{
  EFI_STATUS                Status;
  RPMB_FRAME                Frame;
  UINT8                     LocalNonce[RPMB_NONCE_SIZE];

  if (Data == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Multi-block transfers are not currently supported here
  //
  if (BlockCount > 1) {
    return EFI_UNSUPPORTED;
  }

  ZeroMem (&Frame, RPMB_FRAME_SIZE);

  Frame.Request = RPMB_DATA_READ;
  Frame.BlockCount = SwapBytes16 (BlockCount);
  Frame.Address = SwapBytes16 (Address);
  RandomBytes (LocalNonce, RPMB_NONCE_SIZE);
  CopyMem (Frame.Nonce, LocalNonce, RPMB_NONCE_SIZE);

  Status = SecurityProtocolTransaction (
            RPMB_FRAME_SIZE,
            &Frame,
            TRUE
            );

  Status = RpmbVerifyFrame (&Frame);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  ASSERT (Frame.Response == RPMB_DATA_READ);

  Status = RpmbProcessResult (Frame.Result);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (CompareMem (LocalNonce, Frame.Nonce, RPMB_NONCE_SIZE) != 0) {
    DEBUG ((DEBUG_ERROR, "RPMB: Nonce mismatch.\n"));
    Status = EFI_SECURITY_VIOLATION;
    ASSERT_EFI_ERROR (Status);
  } else {
    CopyMem (Data, Frame.Data, RPMB_DATA_SIZE);
  }

  return Status;
}

/**
  Write data to RPMB.

  @param [in]   Address             The starting block for the RPMB write operation.
  @param [in]   BlockCount          The number of blocks to write.
  @param [in]   Data                A data buffer of size BlockCount * RPMB_DATA_SIZE bytes.

  @retval     EFI_SUCCESS             The data was written successfully.
  @retval     EFI_INVALID_PARAMETER   Data is NULL.
  @retval     EFI_UNSUPPORTED         BlockCount > 1.

**/
EFI_STATUS
EFIAPI
RpmbWriteData (
    IN  UINT16              Address,
    IN  UINT16              BlockCount,
    IN  UINT8               *Data
  )
{
  EFI_STATUS                Status;
  RPMB_FRAME                Frame;
  UINT32                    WriteCounter;

  Status = RpmbGetCounter (&WriteCounter);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Multi-block transfers are not currently supported here
  //
  if (BlockCount > 1) {
    return EFI_UNSUPPORTED;
  }

  ZeroMem (&Frame, RPMB_FRAME_SIZE);

  Frame.Request = RPMB_DATA_WRITE;
  Frame.BlockCount = SwapBytes16 (BlockCount);
  Frame.Address = SwapBytes16 (Address);
  Frame.WriteCounter = SwapBytes32 (WriteCounter);
  CopyMem (Frame.Data, Data, RPMB_DATA_SIZE);

  Status = RpmbSignFrame (&Frame);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = SecurityProtocolTransaction (
            RPMB_FRAME_SIZE,
            &Frame,
            FALSE
            );

  Status = RpmbRequestResult (&Frame);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = RpmbVerifyFrame (&Frame);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  ASSERT (Frame.Response == RPMB_DATA_WRITE);

  Status = RpmbProcessResult (Frame.Result);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (SwapBytes32 (Frame.WriteCounter) != WriteCounter + 1) {
    DEBUG ((DEBUG_ERROR, "RPMB: Write Failure.\n"));
    return EFI_DEVICE_ERROR;
  }

  return Status;
}

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
  )
{
  EFI_STATUS                Status;
  UINTN                     Index;
  UINT8                     TestData[RPMB_DATA_SIZE];
  UINT8                     ReadData[RPMB_DATA_SIZE];

  for (Index = 0; Index < RPMB_DATA_SIZE; Index++) {
    TestData[Index] = (UINT8) Index;
  }

  //
  // Program Key
  //
  Status = RpmbProgramKey (mFixedKey);
  if (EFI_ERROR (Status) && (Status != EFI_ALREADY_STARTED)) {
    return Status;
  }

  //
  // Test WRITE
  //
  DEBUG ((DEBUG_ERROR, "RPMB: Test Write.\n"));
  Status = RpmbWriteData (0x0, 1, TestData);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Test READ
  //
  DEBUG ((DEBUG_ERROR, "RPMB: Test Read.\n"));
  Status = RpmbReadData (0x0, 1, ReadData);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (CompareMem (TestData, ReadData, RPMB_DATA_SIZE) == 0) {
    DEBUG ((DEBUG_ERROR, "RPMB: Test Success.\n"));
  } else {
    DEBUG ((DEBUG_ERROR, "RPMB: Test Failure.\n"));
    Status = EFI_DEVICE_ERROR;
  }

  return Status;
}
