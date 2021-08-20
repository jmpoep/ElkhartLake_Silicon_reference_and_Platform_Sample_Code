/** @file
  This file contains definitions and structures necessary for Command Queue interoperability
  between CSE Variable Storage Runtime DXE and SMM modules.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2019 Intel Corporation.

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

#ifndef _CSE_VARIABLE_STORAGE_COMMAND_QUEUE_H_
#define _CSE_VARIABLE_STORAGE_COMMAND_QUEUE_H_

#include <Base.h>
#include <CseVariableStorage.h>
#include <DataServicesMsg.h>
#include <TrustedChannel.h>

//
// Set the bit below the upper bit to indicate an OEM defined status value
//
#define ENCODE_OEM_WARNING(a)                                   ((MAX_BIT >> 1) | (a))

//
// Define a warning to indicate a required Host OS driver is not present
//
#define EFI_WARN_OS_DRIVER_NOT_PRESENT                          ENCODE_OEM_WARNING (0x2B3E53BA)

#define IS_ALIGNED(addr, size)                                  !((UINT32) (addr) & (size - 1))

//
// The maximum UEFI variable data size allowed is specified by PcdMaxVariableSize and that limit is enforced
// in the EDKII UEFI variable driver. The CSE_VARIABLE_MAX_DATA_SIZE value is the maximum size of variable data
// writes allowed in the CSE variable storage layer. This must be equal to or greater than PcdMaxVariableSize. It
// is greater if a write may exceed the size of PcdMaxVariableSize. For example, this is the case if a variable index
// area update is greater in size than PcdMaxVariableSize.
//
#define CSE_VARIABLE_MAX_DATA_SIZE                              CSE_VARIABLE_MAX_DMA_SIZE

// Add an extra page to hold a header above the data area
#define CSE_VARIABLE_MAX_DATA_SIZE_WITH_HEADER                  (CSE_VARIABLE_MAX_DATA_SIZE + EFI_PAGES_TO_SIZE (1))

#define PERIODIC_TIMER_TICKS_PER_MS                             10000
#define PERIODIC_TIMER_CALL_PERIOD                              2
#define CSE_VARIABLE_MAX_PROXY_WAIT_SECS                        5
#define CSE_VARIABLE_CMD_QUEUE_POLL_DELAY_MS                    5
#ifdef HFPGA_FLAG
#define CSE_VARIABLE_CMD_QUEUE_WAIT_SECS                        4000
#else
#define CSE_VARIABLE_CMD_QUEUE_WAIT_SECS                        4
#endif
#define CSE_VARIABLE_STORAGE_GET_PROXY_HECI_DEVICE              HECI1_DEVICE
#define CSE_VARIABLE_STORAGE_CMD_QUEUE_UNTRUSTED_HECI_DEVICE    HECI1_DEVICE
#define CSE_VARIABLE_STORAGE_CMD_QUEUE_TRUSTED_HECI_DEVICE      HECI2_DEVICE

#define CSE_VARIABLE_CMD_QUEUE_MAX_WAIT_ITERATIONS              ( \
                                                                  (CSE_VARIABLE_CMD_QUEUE_WAIT_SECS * 1000) / \
                                                                  CSE_VARIABLE_CMD_QUEUE_POLL_DELAY_MS \
                                                                  )

//
// In a DMA model, the messages placed in the queue are only request messages.
// The data is directly read/written from the buffer specified in the message
// therefore the size reserved for each entry in the queue is the maximum
// request message size.
//
// Note: The value of MAX_REQUEST_MESSAGES must be at least 2. It should be set to the max number of writes
//       that may internally be issued by the EDKII variable driver. The queue should
//       expect 2 writes per request one to the index area and the other to the data area.
#define CSE_VAR_STORAGE_MAX_WRITES_PER_REQUEST                  2
#define CSE_VAR_STORAGE_CMD_QUEUE_MAX_REQUEST_MESSAGES          8
#define CSE_VAR_STORAGE_CMD_QUEUE_MAX_TOTAL_REQUESTS            (CSE_VAR_STORAGE_CMD_QUEUE_MAX_REQUEST_MESSAGES * \
                                                                  CSE_VAR_STORAGE_MAX_WRITES_PER_REQUEST \
                                                                  )
#if CSE_VAR_STORAGE_CMD_QUEUE_MAX_REQUEST_MESSAGES < 2
#error CSE_VAR_STORAGE_CMD_QUEUE_MAX_REQUEST_MESSAGES must at least be 2
#endif

#define CSE_VAR_STORAGE_CMD_QUEUE_ALIGNMENT                     sizeof (UINT32)
#define CSE_VAR_STORAGE_CMD_QUEUE_GET_PAD_SIZE(a) (((~a) + 1) & (CSE_VAR_STORAGE_CMD_QUEUE_ALIGNMENT - 1))

typedef enum {
  BiosStorageUntrusted,
  BiosStorageTrusted
} BIOS_STORAGE_TYPE;

typedef union {
  BIOS_STORAGE_REQUEST                  Message;
  BIOS_STORAGE_TRUSTED_CHANNEL_REQUEST  TrustedChannelMessage;
} BIOS_STORAGE_REQUEST_BUFFER;

typedef union {
  BIOS_STORAGE_RESPONSE                 Message;
  BIOS_STORAGE_TRUSTED_CHANNEL_RESPONSE TrustedChannelMessage;
} BIOS_STORAGE_RESPONSE_BUFFER;

typedef struct {
  BIOS_STORAGE_REQUEST_BUFFER     Buffer;
  BIOS_STORAGE_TYPE               Type;
} CSE_VAR_BIOS_STORAGE_REQUEST;

typedef struct {
  BIOS_STORAGE_RESPONSE_BUFFER    Buffer;
  BIOS_STORAGE_TYPE               Type;
} CSE_VAR_BIOS_STORAGE_RESPONSE;

#define CSE_VAR_STORAGE_CMD_QUEUE_TOTAL_BUFFER_SIZE ( \
                                                      CSE_VAR_STORAGE_CMD_QUEUE_MAX_TOTAL_REQUESTS * \
                                                      ALIGN_VALUE ( \
                                                        sizeof (CSE_VAR_BIOS_STORAGE_REQUEST), \
                                                        CSE_VAR_STORAGE_CMD_QUEUE_ALIGNMENT \
                                                        ) \
                                                      )

#pragma pack(push, 1)

//
// State of the OS Proxy Interface
//
// Initial state: HeciProxyStateUnknown
// Valid state:   HeciProxyStatePresent
// Invalid state: HeciProxyStateNotPresent
//
typedef enum {
  HeciProxyStateUnknown     = 0,
  HeciProxyStatePresent     = 1,
  HeciProxyStateNotPresent  = 2
} HECI_PROXY_STATE;

//
// SMM communicate structures
//

//
// Common SMM communicate header for communication with CSE Variable Storage SMIs.
//
typedef struct {
  UINTN       Function;
  EFI_STATUS  ReturnStatus;
  UINT8       Data[1];
} SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_HEADER;

//
// Used in an SMI to get the next buffer of write data from SMM.
//
typedef struct {
  UINTN       DataSize;
  UINT8       Data[1];
} SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_GET_NEXT_WRITE_BUFFER;

//
// Used in an SMI to give the Runtime DXE data buffer address to SMM.
//
typedef struct {
  UINT32      DataBufferAddressLow;
  UINT32      DataBufferAddressHigh;
  UINTN       BufferLength;
} SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_SET_DATA_BUFFER;

//
// Used in an SMI to send read data to the EDKII variable driver to be cached.
// Note: Trusted Channel messages must be cached within the VERIFY_RESPONSE handler.
//
typedef struct {
  UINTN                   DataSize;
  UINT8                   Data[1];
} SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_CACHE_DATA_BUFFER;

//
// Used in an SMI to get the variable storage command queue from SMM.
//
typedef struct {
  UINTN       CommandQueueCount;
  UINT8       CommandQueueDataBuffer[1];
} SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_GET_COMMAND_QUEUE;

//
// Used in an SMI to send the trusted channel device information to SMM.
// Note: This information must be sent before SmmReadyToLock is broadcast.
//
typedef struct {
  UINTN       HeciTrustedDeviceBar;
} SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_TRUSTED_CHANNEL_DEVICE_INFO;

//
// Used in an SMI to send the OS proxy HECI device information to SMM.
// Note: This information must be sent before SmmReadyToLock is broadcast.
//
typedef struct {
  UINTN       OsProxyHeciBaseAddress;
  UINTN       OsProxyHeciBar;
} SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_OS_PROXY_DEVICE_INFO;

//
// Used in an SMI to send the number of remaining messages when communication failed.
//
typedef struct {
  UINTN       MessagesRemaining;
} SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_TRUSTED_CHANNEL_COMM_FAILURE;

//
// Used in an SMI to send HMAC response data to SMM for verification.
//
typedef struct {
  BOOLEAN                                IsLastCommand;
  UINTN                                  DataSize;
  BIOS_STORAGE_TRUSTED_CHANNEL_RESPONSE  ResponseMessage;
  UINT8                                  Data[1];
} SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_VERIFY_RESPONSE;

//
// Used in an SMI to output debug messages from within Runtime DXE
//
typedef struct {
  CHAR8       DebugMsg[100];
  UINT8       Length;
  UINT8       Datalength;
  UINT8       Data[4096];
} SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_DEBUG_MSG;

///
/// To avoid confusion in interpreting frames, the communication buffer should always
/// begin with EFI_SMM_COMMUNICATE_HEADER
///
typedef struct {
  ///
  /// Allows for disambiguation of the message format.
  ///
  EFI_GUID  HeaderGuid;
  ///
  /// Describes the size of Data (in bytes) and does not include the size of the header.
  ///
  UINTN     MessageLength;
  ///
  /// Designates an array of bytes that is MessageLength in size.
  ///
  UINT8     Data[1];
} EFI_SMM_COMMUNICATE_HEADER_DATA;

#pragma pack(pop)

//
// Size of the SMM communicate header excluding the payload.
//
#define SMM_COMMUNICATE_HEADER_SIZE  (OFFSET_OF (EFI_SMM_COMMUNICATE_HEADER_DATA, Data))

//
// Size of SMM CSE variable storage communicate header excluding the payload.
//
#define SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_HEADER_SIZE  (OFFSET_OF (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_HEADER, Data))

//
// The payload for this function is SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_GET_NEXT_WRITE_BUFFER.
//
#define SMM_CSE_VARIABLE_STORAGE_FUNCTION_GET_NEXT_WRITE_BUFFER         1

//
// The payload for this function is SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_SET_DATA_BUFFER.
//
#define SMM_CSE_VARIABLE_STORAGE_FUNCTION_SET_DATA_BUFFER               2

//
// The payload for this function is SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_GET_COMMAND_QUEUE.
//
#define SMM_CSE_VARIABLE_STORAGE_FUNCTION_GET_COMMAND_QUEUE             3

//
// The payload for this function is SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_VERIFY_RESPONSE.
//
#define SMM_CSE_VARIABLE_STORAGE_FUNCTION_VERIFY_RESPONSE               4

//
// There is no payload for this function
//
#define SMM_CSE_VARIABLE_STORAGE_FUNCTION_RESET_COMMAND_QUEUE           5

//
// There is no payload for this function
//
#define SMM_CSE_VARIABLE_STORAGE_FUNCTION_TRUSTED_CHANNEL_ENABLE        6

//
// The payload for this function is SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_DEBUG_MSG.
//
#define SMM_CSE_VARIABLE_STORAGE_FUNCTION_DEBUG_MESSAGE                 7

//
// There is no payload for this function
//
#define SMM_CSE_VARIABLE_STORAGE_FUNCTION_RESET_WRITE_COMMAND_QUEUE     8

//
// There is no payload for this function
//
#define SMM_CSE_VARIABLE_STORAGE_FUNCTION_REQUIRE_READ_COMMAND_QUEUE    9

//
// There is no payload for this function
//
#define SMM_CSE_VARIABLE_STORAGE_FUNCTION_REQUIRE_WRITE_COMMAND_QUEUE   10

//
// The payload for this function is SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_CACHE_DATA_BUFFER
//
#define SMM_CSE_VARIABLE_STORAGE_FUNCTION_READ_COMPLETION_IO_DONE       11

//
// There is no payload for this function
//
#define SMM_CSE_VARIABLE_STORAGE_FUNCTION_WRITE_COMPLETION_IO_DONE      12

//
// The payload for this function is SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_TRUSTED_CHANNEL_DEVICE_INFO
//
#define SMM_CSE_VARIABLE_STORAGE_FUNCTION_TRUSTED_CHANNEL_DEVICE_INFO   13

//
// The payload for this function is SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_OS_PROXY_DEVICE_INFO
//
#define SMM_CSE_VARIABLE_STORAGE_FUNCTION_OS_PROXY_DEVICE_INFO          14

//
// The payload for this function is SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_TRUSTED_CHANNEL_COMM_FAILURE
//
#define SMM_CSE_VARIABLE_STORAGE_FUNCTION_TRUSTED_CHANNEL_COMM_FAILURE  15

//
// Returns the total SMM communicate buffer size including the caller passed data size.
//
#define SMM_CSE_VAR_STORAGE_GET_TOTAL_COMM_BUFFER_SIZE(DataSize)\
  ((DataSize) + SMM_COMMUNICATE_HEADER_SIZE + SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_HEADER_SIZE)

#endif
