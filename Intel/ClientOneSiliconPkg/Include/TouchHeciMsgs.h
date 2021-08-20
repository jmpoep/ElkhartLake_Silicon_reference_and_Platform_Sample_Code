/** @file
  Touch HECI Message definitions

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2017 Intel Corporation.

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

#ifndef _TOUCH_HECI_MSGS_H_
#define _TOUCH_HECI_MSGS_H_

#include "TouchSensorRegs.h"

#pragma pack(1)


// Initial protocol version
#define TOUCH_HECI_CLIENT_PROTOCOL_VERSION      1

// GUID that identifies the Touch HECI client.
#define TOUCH_HECI_CLIENT_GUID gHeci3IntegratedTouchControllerGuid

/*
The following comment block describes the key messaging flows used to communicate with Integrated Touch running in ME/CSME firmware.

The Touch interface is exposed on the HECI3 device (B:D:F 0:22:4)

Note: Sub-steps (for example 2a, 2b, 2c, all happen in parallel)


******************************************************************************************************************************************************
**
**  Main Init and Touch Flow
**
**  This flow applies to both runtime touch using a HID driver from an OS and to a BIOS Pre-OS Touch environment.
**
******************************************************************************************************************************************************
 1.  System powers on.
 2a. Touch IC (TIC) initializes and fires Reset Interrupt. Sensor will default to HID mode.
 2b. ME FW initializes and arms touch interrupt on an MGPIO line.
 2c. Host boots and initializes BIOS or HID driver on HECI3 PCI device.
 3.  ME processes first TIC interrupt. Loads TIC FW and Data if needed. Reads other info from sensor device registers.
 4.  BIOS or HID driver initiates HECI Link Reset sequence (see HECI HPS or C-Spec).
 5.  BIOS or HID driver sends TOUCH_SENSOR_NOTIFY_DEV_READY_CMD and waits for response. ME will respond with TOUCH_SENSOR_NOTIFY_DEV_READY_RSP as
       early as possible after receiving the first Reset Interrupt from the sensor device in step 3. If the Reset Interrupt has already been
       received, response will be immediate. This command can fail with status TOUCH_STATUS_COMPAT_CHECK_FAIL. If this happens, touch will not work.
       BIOS or HID may still execute step 6 (TOUCH_SENSOR_GET_VENDOR_INFO_CMD) to get the ME and TIC compatibility versions.
 6.  BIOS or HID driver initiates TOUCH_SENSOR_GET_VENDOR_INFO_CMD command and gets response from ME.
 7.  BIOS or HID driver allocates contiguous buffers for TouchData and Feedback based on info from TOUCH_SENSOR_GET_VENDOR_INFO_RSP_DATA. The number
       of each type of buffer can be 1 to TOUCH_SENSOR_MAX_DATA_BUFFERS.
 8.  If sensor is not already in desired mode, BIOS or HID driver sends TOUCH_SENSOR_SET_MODE_CMD command specifying HID or Raw Data mode. BIOS should
       only request HID mode. ME then performs the following sub-flow:
         I.   Disarm sensor if armed
         II.  Disable sensor if the new mode is different from current mode set (clear TE bit)
         III. If there is an outstanding TOUCH_SENSOR_HID_READY_FOR_DATA_CMD, send TOUCH_SENSOR_HID_READY_FOR_DATA_RSP with Status code indicating
              TOUCH_STATUS_SENSOR_DISABLED
         IV.  Clear DataReady and throw away any old data, clear CurrentDataSize
         V.   Set new mode in hardware
         VI.  Enable sensor (set TE bit)
         VII. Send TOUCH_SENSOR_SET_MODE_RSP
 9.  BIOS or HID driver sends TOUCH_SENSOR_SET_MEM_WINDOW_CMD command with address of contiguous DMA buffers. This must always include at least one
       TouchData/Feedback Buffer pair, and Hid2Me Buffer. Tail Offset, DoorbellCookie and WorkQueue sizes are only required for Raw Data mode but not
       HID mode. ME will respond with a status code in TOUCH_SENSOR_SET_MEM_WINDOW_RSP.
10.  ME sends command to TIC to go to Armed state.
11.  BIOS or HID driver sends TOUCH_SENSOR_HID_READY_FOR_DATA_CMD to wait for ME to DMA data.
12a. The TIC will fire a Data Available interrupt causing ME to read a frame from the sensor to internal memory. An internal "Data Available" flag
       will be set. If step 12a is used, step 12b should not be used.
12b. Alternate flow for testing/debug: This can be used for cases where the sensor is not present but we want to simulate flows and/or debug. BIOS or
       HID driver sends TOUCH_SENSOR_DBG_SIMULATE_INT_CMD. The BIOS or HID driver MUST specify the values of the sensor registers to simulate by
       filling in the values in this message. An internal "Data Available" flag will be set. If step 12b is used, step 12a should not be used.
13.  Once ME has received the TOUCH_SENSOR_HID_READY_FOR_DATA_CMD message AND the "Data Available" flag is set, ME will initiate DMA to the host:
       I.  If in Raw Data mode:
             a. ME will DMA the DataBuffer, TailOffset, DoorbellCookie
             b. ME will send TOUCH_SENSOR_HID_READY_FOR_DATA_RSP only in certain error cases.
       II. If in HID mode:
             a. ME will DMA the DataBuffer
             b. ME will send TOUCH_SENSOR_HID_READY_FOR_DATA_RSP immediately after DMA is complete.
14.  Preparing Feedback:
       I.  If in Raw Data mode:
             a. Vendor kernel will fill in the FeedbackHeader (to be sent to ME) and optional payload (to be sent to TIC) in its output buffer.
                In particular, the BufferID must be copied from the RawData header received in step 13 above into the Feedback Header. This
                value is used to track usage and availability of the data buffers.
             b. HID driver will copy that data to the FeedbackBuffer corresponding to the completed DataBuffer. It is expected that the
                FeedbackIndex value will match the BufferID value.
       II. If in HID mode:
             a. BIOS or HID driver will fill in the FeedbackHeader (to be sent to ME). In particular, the BufferID must be copied from the
                RawData header received in step 13 above into the Feedback Header. This value is used to track usage and availability of the
                data buffers.
             b. BIOS or HID driver will copy that data to the FeedbackBuffer corresponding to the completed DataBuffer. It is expected that the
                FeedbackIndex value will match the BufferID value.
15.  BIOS or HID driver will send the TOUCH_SENSOR_FEEDBACK_READY_CMD.
16.  ME DMAs the feedback header and data. Based on the info in the header, ME will write any payload to the sensor and execute any requested command.
       ME will then send TOUCH_SENSOR_FEEDBACK_READY_RSP.
17.  If in Raw Data mode, return to step 12. If in HID mode, return to step 11.
18.  If at any time the HID driver needs to change mode, such as when GFX driver becomes available/unavailable:
       I.   HID driver sends TOUCH_SENSOR_CLEAR_MEM_WINDOW_CMD.
       II.  If there is an outstanding TOUCH_SENSOR_HID_READY_FOR_DATA_CMD, ME will send TOUCH_SENSOR_HID_READY_FOR_DATA_RSP.
       III. HID driver must continue sending TOUCH_SENSOR_FEEDBACK_READY_CMD messages for any processing that was already in progress.
       IV.  ME will send TOUCH_SENSOR_CLEAR_MEM_WINDOW_RSP once it has received all expected feedback or times out (Timeout value TBD).
       V.   Return to step 8.
19a. At any time during this flow, HID driver can be stopped (OS Reset, driver disabled, etc...). During Stop processing, HID driver must send
       TOUCH_SENSOR_CLEAR_MEM_WINDOW_CMD. Return to step 2c.
19b. When BIOS completes any touch operations and before handing off control to the OS, BIOS should send TOUCH_SENSOR_CLEAR_MEM_WINDOW_CMD.
20.  At any time during this flow, HID driver can send TOUCH_SENSOR_QUIESCE_IO_CMD to halt the flow of data. Return to step 11 to continue.
21.  At any time during this flow, BIOS or HID driver can send TOUCH_SENSOR_SET_POLICIES_CMD to configure optional parameters. See
       TOUCH_SENSOR_SET_POLICIES_CMD_DATA for more details on options avialable.
22.  At any time during this flow, BIOS or HID driver can send TOUCH_SENSOR_GET_POLICIES_CMD to check the current policy settings.
23.  At any time during this flow after the sensor device has been detected, BIOS or HID driver can send TOUCH_SENSOR_READ_ALL_REGS_CMD. This command
       will generate a read of all registers to the sensor device and return the results.
*/


//
// Touch Sensor HECI Message Command Codes
// Most significant bit indicates direction of message (0 = H2M, 1 = M2H)
// Bit 15 indicates commands that are only relevant for debug/testing purposes
//
// H2M = Host to ME communication
// M2H = ME to Host communication
//
#define TOUCH_SENSOR_GET_DEVICE_INFO_CMD        0x00000001  // H2M: Host requests ME to report the devicve specific parameters of the touch sensor. No data.
#define TOUCH_SENSOR_GET_DEVICE_INFO_RSP        0x80000001  // M2H: ME will provide structure containing various devicve specific parameters, see TOUCH_SENSOR_GET_DEVICE_INFO_RSP_DATA.


#define TOUCH_SENSOR_SET_MODE_CMD               0x00000002  // H2M: Host requests ME to set TIC operation for HID or Raw Data mode. See TOUCH_SENSOR_SET_MODE_CMD_DATA
#define TOUCH_SENSOR_SET_MODE_RSP               0x80000002  // M2H: Data will indicate success or failure code. See TOUCH_SENSOR_SET_MODE_RSP_DATA.


#define TOUCH_SENSOR_SET_MEM_WINDOW_CMD         0x00000003  // H2M: Before completing init sequence, Host MUST send this command to provide a physical buffer address to ME. This buffer will be used
                                                            //      to GPDMA touch sensor data to the GuK. See TOUCH_SENSOR_SET_MEM_WINDOW_CMD_DATA.
#define TOUCH_SENSOR_SET_MEM_WINDOW_RSP         0x80000003  // M2H: Data will indicate success or failure code. See TOUCH_SENSOR_SET_MEM_WINDOW_RSP_DATA.


#define TOUCH_SENSOR_QUIESCE_IO_CMD             0x00000004  // H2M: This is used by the HID driver any time it needs to stop DMA traffic from ME to Host memory, but the HID driver plans to continue
                                                            //      again without resetting all memory addresses and buffer allocations. This has a similar effect to TOUCH_SENSOR_CLEAR_MEM_WINDOW_CMD
                                                            //      except that the buffer addresses are not cleared. See TOUCH_SENSOR_QUIESCE_IO_CMD_DATA.
#define TOUCH_SENSOR_QUIESCE_IO_RSP             0x80000004  // M2H: The ME will stop sending new raw/HID data to the host and wait for all buffers to be reported as complete via the
                                                            //      TOUCH_SENSOR_FEEDBACK_READY_CMD. Once all buffers are returned, ME will send this response with a stauts code. See
                                                            //      TOUCH_SENSOR_QUIESCE_IO_RSP_DATA.


#define TOUCH_SENSOR_HID_READY_FOR_DATA_CMD     0x00000005  // H2M: Indicates HID driver is ready for DMA transfer (can be outstanding while other messages come in also). HID must not send this
                                                            //      message again until it receives a response from its first request. No data.
#define TOUCH_SENSOR_HID_READY_FOR_DATA_RSP     0x80000005  // M2H: Sent after both of 2 conditions are true: DMA has completed and TOUCH_SENSOR_HID_READY_FOR_DATA_CMD was recevied. Data will include
                                                            //      a status code and size of data, see TOUCH_SENSOR_HID_READY_FOR_DATA_RSP_DATA. Response is only sent for errors or HID mode. If the
                                                            //      ME has placed data in one of the RawData Buffers (configured via TOUCH_SENSOR_SET_MEM_WINDOW_CMD) then the ME will indicate which
                                                            //      buffer was used for that data using the field TOUCH_SENSOR_HID_READY_FOR_DATA_RSP_DATA.TouchDataBufferIndex. The data is defined by
                                                            //      the struct TOUCH_RAW_DATA. Any time data has been transferred in this way, TOUCH_SENSOR_HID_READY_FOR_DATA_RSP_DATA.TouchDataBufferIndex
                                                            //      will contain a valid buffer index. Otherwise (such was when returning an error), it will be set to TOUCH_INVALID_BUFFER_ID. When the
                                                            //      buffer index is valid, it is essential that the HID driver return that buffer to ME using the TOUCH_SENSOR_FEEDBACK_READY_CMD message.


#define TOUCH_SENSOR_FEEDBACK_READY_CMD         0x00000006  // H2M: Indicates that Feedback Data has been supplied by the vendor kernel to pass back to the sensor. Data indicates which buffer to use.
                                                            //      See TOUCH_SENSOR_FEEDBACK_READY_CMD_DATA.
#define TOUCH_SENSOR_FEEDBACK_READY_RSP         0x80000006  // M2H: Data will indicate success or failure code. Success for this message means the Feedback Data has been written to the device. See
                                                            //      TOUCH_SENSOR_FEEDBACK_READY_RSP_DATA. If performance meansurements


#define TOUCH_SENSOR_CLEAR_MEM_WINDOW_CMD       0x00000007  // H2M: Indicates that the memory addresses previously registered via TOUCH_SENSOR_SET_MEM_WINDOW_CMD should no longer be used. This may be
                                                            //      due to a system reset or HID driver being disabled in the OS. This command has an effect similar to TOUCH_SENSOR_QUIESCE_IO_CMD
                                                            //      except that it also clears all memory addresses and deallocates buffers. No data.
#define TOUCH_SENSOR_CLEAR_MEM_WINDOW_RSP       0x80000007  // M2H: Data will indicate success or failure code. See TOUCH_SENSOR_CLEAR_MEM_WINDOW_RSP_DATA.


#define TOUCH_SENSOR_NOTIFY_DEV_READY_CMD       0x00000008  // H2M: HID driver requests to be notified when a touch sensor device has been detected by ME (can be outstanding while other messages come
                                                            //      in also). HID must not send this message again until it receives a response from its first request. No data.
#define TOUCH_SENSOR_NOTIFY_DEV_READY_RSP       0x80000008  // M2H: ME will send this response as early as possible after receiveing the first Reset Interrupt from the sensor device. If the Reset
                                                            //      Interrupt has already been received, response will be immediate. See TOUCH_SENSOR_NOTIFY_DEV_READY_RSP_DATA.


#define TOUCH_SENSOR_SET_POLICIES_CMD           0x00000009  // H2M: Used to configure optional parameters. See TOUCH_SENSOR_SET_POLICIES_CMD_DATA.
#define TOUCH_SENSOR_SET_POLICIES_RSP           0x80000009  // M2H: Data will indicate success or failure code. See TOUCH_SENSOR_SET_POLICIES_RSP_DATA.


#define TOUCH_SENSOR_GET_POLICIES_CMD           0x0000000A  // H2M: Used retrieve the current parameter settings. No data.
#define TOUCH_SENSOR_GET_POLICIES_RSP           0x8000000A  // M2H: Data will indicate the current parameter settings. See TOUCH_SENSOR_GET_POLICIES_RSP_DATA.


#define TOUCH_SENSOR_RESET_CMD                  0x0000000B  // H2M: This command will cause ME to reset the sensor device. Parameter specifies hard or soft reset. See TOUCH_SENSOR_RESET_CMD_DATA.
#define TOUCH_SENSOR_RESET_RSP                  0x8000000B  // H2M: Data will indicate success or failure. See TOUCH_SENSOR_RESET_RSP_DATA.


#define TOUCH_SENSOR_READ_ALL_REGS_CMD          0x0000000C  // H2M: This command will cause a read of all registers to be issued to the sensor device. No data.
#define TOUCH_SENSOR_READ_ALL_REGS_RSP          0x8000000C  // H2M: Data will indicate success or failure, and will also include the register data on success. See TOUCH_SENSOR_READ_ALL_REGS_RSP_DATA.


#define TOUCH_SENSOR_GEN_TEST_PACKETS_CMD       0x0000000D  // H2M: This command will put the sensor into a test mode to generate the specified number of raw data frames or HID reports. See
                                                            //      TOUCH_SENSOR_GEN_TEST_PACKETS_CMD_DATA.
#define TOUCH_SENSOR_GEN_TEST_PACKETS_RSP       0x8000000D  // H2M: Data will indicate success or failure. See TOUCH_SENSOR_GEN_TEST_PACKETS_RSP_DATA.


#define TOUCH_SENSOR_CMD_ERROR_RSP              0x8FFFFFFF  // M2H: ME sends this message to indicate previous command was unrecognized


//
// Debug commands. These commands are intended for debugging purposes only. To make sure they are not exploited in the field, these commands are only allowed under the following conditions:
//    1. If the platform is in Manufacturing Mode, i.e. the End of Manufacturing (EOM) bit has not been set, the commands are allowed.
//    2. If the platform is NOT in Manufacturing Mode (EOM is set), but this BIOS has not yet sent End of POST (EOP), the commands are allowed. This allows for unlocking debug commands on
//       a post-manufacturing system by putting in a debug BIOS that does not send EOP.
//
// TODO: start enforcement of above rules
#define TOUCH_SENSOR_DBG_READ_DEVICE_CMD        0x00008004  // H2M: Host can send commands to read data from the sensor over the SPI bus, see TOUCH_SENSOR_DBG_READ_DEVICE_CMD_DATA.
#define TOUCH_SENSOR_DBG_READ_DEVICE_RSP        0x80008004  // M2H: Data will indicate success or failure code. See TOUCH_SENSOR_DBG_READ_DEVICE_RSP_DATA.


#define TOUCH_SENSOR_DBG_WRITE_DEVICE_CMD       0x00008005  // H2M: Host can send commands to write data to the sensor over the SPI bus, see TOUCH_SENSOR_DBG_WRITE_DEVICE_CMD_DATA.
#define TOUCH_SENSOR_DBG_WRITE_DEVICE_RSP       0x80008005  // M2H: Data will indicate success or failure code. See TOUCH_SENSOR_DBG_WRITE_DEVICE_RSP_DATA.


#define TOUCH_SENSOR_DBG_GET_INT_PIN_VAL_CMD    0x00008006  // H2M: Read the current pin value of the Touch interrupt line. No data.
#define TOUCH_SENSOR_DBG_GET_INT_PIN_VAL_RSP    0x80008006  // M2H: Data will indicate current raw pin value of the interrupt line. See TOUCH_SENSOR_DBG_GET_INT_PIN_VAL_RSP_DATA.


#define TOUCH_SENSOR_DBG_SIMULATE_INT_CMD       0x00008007  // H2M: Force ME FW to behave like an interrupt fired. Optionally can also specify the values of all required registers. If values are not
                                                            //      specified, FW will use values from the real registers. See TOUCH_SENSOR_DBG_SIMULATE_INT_CMD_DATA. There is no HECI response to
                                                            //      this message.


//*******************************************************************
//
// Touch Sensor Status Codes
//
//*******************************************************************
typedef enum {
  TOUCH_STATUS_SUCCESS = 0,               ///<  0 Requested operation was successful
  TOUCH_STATUS_INVALID_PARAMS,            ///<  1 Invalid parameter(s) sent
  TOUCH_STATUS_ACCESS_DENIED,             ///<  2 Unable to validate address range
  TOUCH_STATUS_CMD_SIZE_ERROR,            ///<  3 HECI message incorrect size for specified command
  TOUCH_STATUS_NOT_READY,                 ///<  4 Memory window not set or device is not armed for operation
  TOUCH_STATUS_REQUEST_OUTSTANDING,       ///<  5 There is already an outstanding message of the same type, must wait for response before sending another request of that type
  TOUCH_STATUS_NO_SENSOR_FOUND,           ///<  6 Sensor could not be found. Either no sensor is connected, the sensor has not yet initialized, or the system is improperly configured.
  TOUCH_STATUS_OUT_OF_MEMORY,             ///<  7 Not enough memory/storage for requested operation
  TOUCH_STATUS_INTERNAL_ERROR,            ///<  8 Unexpected error occurred
  TOUCH_STATUS_SENSOR_DISABLED,           ///<  9 Used in TOUCH_SENSOR_HID_READY_FOR_DATA_RSP to indicate sensor has been disabled or reset and must be reinitialized.
  TOUCH_STATUS_COMPAT_CHECK_FAIL,         ///< 10 Used to indicate compatibility revision check between sensor and ME failed, or protocol ver between ME/HID/Kernels failed.
  TOUCH_STATUS_SENSOR_EXPECTED_RESET,     ///< 11 Indicates sensor went through a reset initiated by ME
  TOUCH_STATUS_SENSOR_UNEXPECTED_RESET,   ///< 12 Indicates sensor went through an unexpected reset
  TOUCH_STATUS_RESET_FAILED,              ///< 13 Requested sensor reset failed to complete
  TOUCH_STATUS_TIMEOUT,                   ///< 14 Operation timed out
  TOUCH_STATUS_TEST_MODE_FAIL,            ///< 15 Test mode pattern did not match expected values
  TOUCH_STATUS_SENSOR_FAIL_FATAL,         ///< 16 Indicates sensor reported fatal error during reset sequence. Further progress is not possible.
  TOUCH_STATUS_SENSOR_FAIL_NONFATAL,      ///< 17 Indicates sensor reported non-fatal error during reset sequence. HID/BIOS logs error and attempts to continue.
  TOUCH_STATUS_INVALID_DEVICE_CAPS,       ///< 18 Indicates sensor reported invalid capabilities, such as not supporting required minimum frequency or I/O mode.
  TOUCH_STATUS_QUIESCE_IO_IN_PROGRESS,    ///< 19 Indicates that command cannot be complete until ongoing Quiesce I/O flow has completed.
  TOUCH_STATUS_MAX                        ///< 20 Invalid value, never returned
} TOUCH_STATUS;
C_ASSERT(sizeof(TOUCH_STATUS) == 4);


//*******************************************************************
//
// Defines for message structures used for Host to ME communication
//
//*******************************************************************

///
/// Touch Sensor Mode
///
typedef enum {
  TOUCH_SENSOR_MODE_HID = 0,          ///< Set mode to HID mode
  TOUCH_SENSOR_MODE_RAW_DATA,         ///< Set mode to Raw Data mode
  TOUCH_SENSOR_MODE_SENSOR_DEBUG = 4, ///< Used like TOUCH_SENSOR_MODE_HID but data coming from sensor is not necessarily a HID packet.
  TOUCH_SENSOR_MODE_MAX               ///< Invalid value
} TOUCH_SENSOR_MODE;
C_ASSERT(sizeof(TOUCH_SENSOR_MODE) == 4);

///
/// Command / Data structure to set Touch Sensor
///
typedef struct {
  TOUCH_SENSOR_MODE   SensorMode;     ///< Indicate desired sensor mode
  UINT32              Reserved[3];    ///< For future expansion
} TOUCH_SENSOR_SET_MODE_CMD_DATA;
C_ASSERT(sizeof(TOUCH_SENSOR_SET_MODE_CMD_DATA) == 16);


#define TOUCH_SENSOR_MAX_DATA_BUFFERS   16
#define TOUCH_HID_2_ME_BUFFER_ID        TOUCH_SENSOR_MAX_DATA_BUFFERS
#define TOUCH_HID_2_ME_BUFFER_SIZE_MAX  1024
#define TOUCH_INVALID_BUFFER_ID         0xFF

///
/// Command / Data structure to set Touch Sensor addresses and sizes of memory buffers
///
typedef struct {
  UINT32  TouchDataBufferAddrLower[TOUCH_SENSOR_MAX_DATA_BUFFERS];    ///< Lower 32 bits of Touch Data Buffer physical address. Size of each buffer should be TOUCH_SENSOR_GET_DEVICE_INFO_RSP_DATA.FrameSize
  UINT32  TouchDataBufferAddrUpper[TOUCH_SENSOR_MAX_DATA_BUFFERS];    ///< Upper 32 bits of Touch Data Buffer physical address. Size of each buffer should be TOUCH_SENSOR_GET_DEVICE_INFO_RSP_DATA.FrameSize
  UINT32  TailOffsetAddrLower;                                        ///< Lower 32 bits of Tail Offset physical address
  UINT32  TailOffsetAddrUpper;                                        ///< Upper 32 bits of Tail Offset physical address, always 32 bit, increment by WorkQueueItemSize
  UINT32  DoorbellCookieAddrLower;                                    ///< Lower 32 bits of Doorbell register physical address
  UINT32  DoorbellCookieAddrUpper;                                    ///< Upper 32 bits of Doorbell register physical address, always 32 bit, increment as integer, rollover to 1
  UINT32  FeedbackBufferAddrLower[TOUCH_SENSOR_MAX_DATA_BUFFERS];     ///< Lower 32 bits of Feedback Buffer physical address. Size of each buffer should be TOUCH_SENSOR_GET_DEVICE_INFO_RSP_DATA.FeedbackSize
  UINT32  FeedbackBufferAddrUpper[TOUCH_SENSOR_MAX_DATA_BUFFERS];     ///< Upper 32 bits of Feedback Buffer physical address. Size of each buffer should be TOUCH_SENSOR_GET_DEVICE_INFO_RSP_DATA.FeedbackSize
  UINT32  Hid2MeBufferAddrLower;                                      ///< Lower 32 bits of dedicated HID to ME communication buffer. Size is Hid2MeBufferSize.
  UINT32  Hid2MeBufferAddrUpper;                                      ///< Upper 32 bits of dedicated HID to ME communication buffer. Size is Hid2MeBufferSize.
  UINT32  Hid2MeBufferSize;                                           ///< Size in bytes of Hid2MeBuffer, can be no bigger than TOUCH_HID_2_ME_BUFFER_SIZE_MAX
  UINT8   Reserved1;                                                  ///< For future expansion
  UINT8   WorkQueueItemSize;                                          ///< Size in bytes of the GuC Work Queue Item pointed to by TailOffset
  UINT16  WorkQueueSize;                                              ///< Size in bytes of the entire GuC Work Queue
  UINT32  Reserved[8];                                                ///< For future expansion
} TOUCH_SENSOR_SET_MEM_WINDOW_CMD_DATA;
C_ASSERT(sizeof(TOUCH_SENSOR_SET_MEM_WINDOW_CMD_DATA) == 320);


#define TOUCH_SENSOR_QUIESCE_FLAG_GUC_RESET BIT0   // indicates GuC got reset and ME must re-read Guc data such as tailoffset and doorbell values

typedef struct {
  UINT32  QuiesceFlags;   ///< Optionally set TOUCH_SENSOR_QUIESCE_FLAG_GUC_RESET
  UINT32  Reserved[2];
} TOUCH_SENSOR_QUIESCE_IO_CMD_DATA;
C_ASSERT(sizeof(TOUCH_SENSOR_QUIESCE_IO_CMD_DATA) == 12);


typedef struct {
  UINT8   FeedbackIndex;  ///< Index value from 0 to TOUCH_HID_2_ME_BUFFER_ID used to indicate which Feedback Buffer to use. Using special value TOUCH_HID_2_ME_BUFFER_ID
                          ///< is an indication to ME to get feedback data from the Hid2Me buffer instead of one of the standard Feedback buffers.
  UINT8   Reserved1[3];   ///< For future expansion
  UINT32  TransactionId;  ///< Transaction ID that was originally passed to host in TOUCH_HID_PRIVATE_DATA. Used to track round trip of a given transaction for performance measurements.
  UINT32  Reserved2[2];   ///< For future expansion
} TOUCH_SENSOR_FEEDBACK_READY_CMD_DATA;
C_ASSERT(sizeof(TOUCH_SENSOR_FEEDBACK_READY_CMD_DATA) == 16);


#define TOUCH_DEFAULT_DOZE_TIMER_SECONDS    30

typedef enum {
  TOUCH_FREQ_OVERRIDE_NONE,   ///< Do not apply any override
  TOUCH_FREQ_OVERRIDE_10MHZ,  ///< Force frequency to 10MHz (not currently supported)
  TOUCH_FREQ_OVERRIDE_17MHZ,  ///< Force frequency to 17MHz
  TOUCH_FREQ_OVERRIDE_30MHZ,  ///< Force frequency to 30MHz
  TOUCH_FREQ_OVERRIDE_50MHZ,  ///< Force frequency to 50MHz (not currently supported)
  TOUCH_FREQ_OVERRIDE_MAX     ///< Invalid value
} TOUCH_FREQ_OVERRIDE;
C_ASSERT(sizeof(TOUCH_FREQ_OVERRIDE) == 4);

typedef enum {
  TOUCH_SPI_IO_MODE_OVERRIDE_NONE,    ///< Do not apply any override
  TOUCH_SPI_IO_MODE_OVERRIDE_SINGLE,  ///< Force Single I/O
  TOUCH_SPI_IO_MODE_OVERRIDE_DUAL,    ///< Force Dual I/O
  TOUCH_SPI_IO_MODE_OVERRIDE_QUAD,    ///< Force Quad I/O
  TOUCH_SPI_IO_MODE_OVERRIDE_MAX      ///< Invalid value
} TOUCH_SPI_IO_MODE_OVERRIDE;
C_ASSERT(sizeof(TOUCH_SPI_IO_MODE_OVERRIDE) == 4);

// Debug Policy bits used by TOUCH_POLICY_DATA.DebugOverride
#define TOUCH_DBG_POLICY_OVERRIDE_STARTUP_TIMER_DIS BIT0    // Disable sensor startup timer
#define TOUCH_DBG_POLICY_OVERRIDE_SYNC_BYTE_DIS     BIT1    // Disable Sync Byte check for Status register

typedef struct {
  UINT32                      Reserved0;          ///< For future expansion.
  UINT32                      DozeTimer     :16;  ///< Value in seconds, after which ME will put the sensor into Doze power state if no activity occurs. Set
                                                  ///< to 0 to disable Doze mode (not recommended). Value will be set to TOUCH_DEFAULT_DOZE_TIMER_SECONDS by
                                                  ///< default.
#ifdef __WATCOM__
  UINT32                      FreqOverride  :3;   ///< Override frequency requested by sensor
  UINT32                      SpiIoOverride :3;   ///< Override IO mode requested by sensor
#else
  TOUCH_FREQ_OVERRIDE         FreqOverride  :3;   ///< Override frequency requested by sensor
  TOUCH_SPI_IO_MODE_OVERRIDE  SpiIoOverride :3;   ///< Override IO mode requested by sensor
#endif
  UINT32                      Reserved1     :10;  ///< For future expansion
  UINT32                      Reserved2;          ///< For future expansion
  UINT32                      DebugOverride;      ///< Normally all bits will be zero. Bits will be defined as needed for enabling special debug features
} TOUCH_POLICY_DATA;
C_ASSERT(sizeof(TOUCH_POLICY_DATA) == 16);

typedef struct {
  TOUCH_POLICY_DATA           PolicyData;         ///< Contains the desired policy to be set
} TOUCH_SENSOR_SET_POLICIES_CMD_DATA;
C_ASSERT(sizeof(TOUCH_SENSOR_SET_POLICIES_CMD_DATA) == 16);

typedef enum {
  TOUCH_SENSOR_RESET_TYPE_HARD,   ///< Hardware Reset using dedicated GPIO pin
  TOUCH_SENSOR_RESET_TYPE_SOFT,   ///< Software Reset using command written over SPI interface
  TOUCH_SENSOR_RESET_TYPE_MAX     ///< Invalid value
} TOUCH_SENSOR_RESET_TYPE;
C_ASSERT(sizeof(TOUCH_SENSOR_RESET_TYPE) == 4);

typedef struct {
  TOUCH_SENSOR_RESET_TYPE ResetType;  ///< Indicate desired reset type
  UINT32                  Reserved;   ///< For future expansion
} TOUCH_SENSOR_RESET_CMD_DATA;
C_ASSERT(sizeof(TOUCH_SENSOR_RESET_CMD_DATA) == 8);

typedef struct {
  TOUCH_TEST_CTRL_REG TestCtrlReg;    ///< Control register value to write to sensor
  UINT32              Reserved[3];    ///< For future expansion
} TOUCH_SENSOR_GEN_TEST_PACKETS_CMD_DATA;
C_ASSERT(sizeof(TOUCH_SENSOR_GEN_TEST_PACKETS_CMD_DATA) == 16);


#define TOUCH_SENSOR_MAX_READ_DATA  256     // max number of bytes for TOUCH_SENSOR_DBG_READ_DEVICE_CMD
#define TOUCH_SENSOR_MAX_WRITE_DATA 256     // max number of bytes for TOUCH_SENSOR_DBG_WRITE_DEVICE_CMD

typedef struct {
  UINT32  ReadBytes   :8;     ///< Firmware will read (ReadBytes + 1) from the touch sensor. Valid range is 0 to (TOUCH_SENSOR_MAX_READ_DATA - 1)
  UINT32  ReadOffset  :24;    ///< Device register offset from which to begin reading
  UINT32  Reserved[3];        ///< For future expansion
} TOUCH_SENSOR_DBG_READ_DEVICE_CMD_DATA;
C_ASSERT(sizeof(TOUCH_SENSOR_DBG_READ_DEVICE_CMD_DATA) == 16);

typedef struct {
  UINT32  WriteBytes  :8;     ///< Firmware will write (WriteBytes + 1) from the touch sensor. Valid range is 0 to (TOUCH_SENSOR_MAX_WRITE_DATA - 1)
  UINT32  WriteOffset :24;    ///< Device register offset at which to begin writing
  UINT32  Reserved[3];        ///< For future expansion
} TOUCH_SENSOR_DBG_WRITE_DEVICE_CMD_DATA;
C_ASSERT(sizeof(TOUCH_SENSOR_DBG_WRITE_DEVICE_CMD_DATA) == 16);

typedef struct {
  UINT32                  UseSimulatedRegs;   ///< 0: Use real registers read from SPI, 1: Use simulated register data from this structure
  TOUCH_REG_BLOCK         RegBlock;           ///< 64 byte block of registers from offset 0x00 through 0x3F
  UINT32                  Reserved[4];        ///< For future expansion
} TOUCH_SENSOR_DBG_SIMULATE_INT_CMD_DATA;
C_ASSERT(sizeof(TOUCH_SENSOR_DBG_SIMULATE_INT_CMD_DATA) == 84);


///
/// Structure to use in ME for receiving various incoming data. May not need to share this and move to internal ME header file
///
typedef struct {
  UINT32  CommandCode;
  union {
    TOUCH_SENSOR_SET_MODE_CMD_DATA              SetModeCmdData;
    TOUCH_SENSOR_SET_MEM_WINDOW_CMD_DATA        SetMemWindowCmdData;
    TOUCH_SENSOR_QUIESCE_IO_CMD_DATA            QuiesceIoCmdData;
    TOUCH_SENSOR_FEEDBACK_READY_CMD_DATA        FeedbackReadyCmdData;
    TOUCH_SENSOR_SET_POLICIES_CMD_DATA          SetPoliciesCmdData;
    TOUCH_SENSOR_RESET_CMD_DATA                 ResetCmdData;
    TOUCH_SENSOR_GEN_TEST_PACKETS_CMD_DATA      GenTestPacketsCmdData;
    TOUCH_SENSOR_DBG_READ_DEVICE_CMD_DATA       ReadDeviceCmdData;
    TOUCH_SENSOR_DBG_WRITE_DEVICE_CMD_DATA      WriteDeviceCmdData;
    TOUCH_SENSOR_DBG_SIMULATE_INT_CMD_DATA      SimulateIntCmdData;
  } H2MData;
} TOUCH_SENSOR_MSG_H2M;
C_ASSERT(sizeof(TOUCH_SENSOR_MSG_H2M) == 324);


//*******************************************************************
//
// Defines for message structures used for ME to Host communication
//
//*******************************************************************

///
/// I/O mode values used by TOUCH_SENSOR_GET_DEVICE_INFO_RSP_DATA.
///
typedef enum {
  TOUCH_SPI_IO_MODE_SINGLE = 0,   ///< Sensor set for Single I/O SPI
  TOUCH_SPI_IO_MODE_DUAL,         ///< Sensor set for Dual I/O SPI
  TOUCH_SPI_IO_MODE_QUAD,         ///< Sensor set for Quad I/O SPI
  TOUCH_SPI_IO_MODE_MAX           ///< Invalid value
} TOUCH_SPI_IO_MODE;
C_ASSERT(sizeof(TOUCH_SPI_IO_MODE) == 4);

//
// TOUCH_SENSOR_GET_DEVICE_INFO_RSP code is sent in response to TOUCH_SENSOR_GET_DEVICE_INFO_CMD. This code will be followed
// by TOUCH_SENSOR_GET_DEVICE_INFO_RSP_DATA.
//
// Possible Status values:
//      TOUCH_STATUS_SUCCESS:               Command was proccessed successfully and sensor details are reported.
//      TOUCH_STATUS_CMD_SIZE_ERROR:        Command sent did not match expected size. Other fields will not contain valid data.
//      TOUCH_STATUS_NO_SENSOR_FOUND:       Sensor has not yet been detected. Other fields will not contain valid data.
//      TOUCH_STATUS_INVALID_DEVICE_CAPS:   Indicates sensor does not support minimum required Frequency or I/O Mode. ME firmware will choose best possible option for the errant
//                                          field. Caller should attempt to continue.
//      *TOUCH_STATUS_COMPAT_CHECK_FAIL:    Indicates TouchIC/ME compatibility mismatch. Caller should attempt to continue.
//
typedef struct {
  TOUCH_STATUS        Status;                 ///< See description above for possible Status values
  UINT16              VendorId;               ///< Touch Sensor vendor ID
  UINT16              DeviceId;               ///< Touch Sensor device ID
  UINT32              HwRev;                  ///< Touch Sensor Hardware Revision
  UINT32              FwRev;                  ///< Touch Sensor Firmware Revision
  UINT32              FrameSize;              ///< Max size of one frame returned by Touch IC in bytes. This data will be TOUCH_RAW_DATA_HDR followed
                                              ///< by a payload. The payload can be raw data or a HID structure depending on mode.
  UINT32              FeedbackSize;           ///< Max size of one Feedback structure in bytes
  TOUCH_SENSOR_MODE   SensorMode;             ///< Current operating mode of the sensor
  UINT32              MaxTouchPoints  :8;     ///< Maximum number of simultaneous touch points that can be reported by sensor
#ifdef __WATCOM__
  UINT32              SpiFrequency    :8;     ///< SPI bus Frequency supported by sensor and ME firmware
  UINT32              SpiIoMode       :8;     ///< SPI bus I/O Mode supported by sensor and ME firmware
#else
  TOUCH_FREQ          SpiFrequency    :8;     ///< SPI bus Frequency supported by sensor and ME firmware
  TOUCH_SPI_IO_MODE   SpiIoMode       :8;     ///< SPI bus I/O Mode supported by sensor and ME firmware
#endif
  UINT32              Reserved0       :8;     ///< For future expansion
  UINT8               SensorMinorEdsRev;      ///< Minor version number of EDS spec supported by sensor (from Compat Rev ID Reg)
  UINT8               SensorMajorEdsRev;      ///< Major version number of EDS spec supported by sensor (from Compat Rev ID Reg)
  UINT8               MeMinorEdsRev;          ///< Minor version number of EDS spec supported by ME
  UINT8               MeMajorEdsRev;          ///< Major version number of EDS spec supported by ME
  UINT8               SensorEdsIntfRev;       ///< EDS Interface Revision Number supported by sensor (from Compat Rev ID Reg)
  UINT8               MeEdsIntfRev;           ///< EDS Interface Revision Number supported by ME
  UINT8               KernelCompatVer;        ///< EU Kernel Compatibility Version  (from Compat Rev ID Reg)
  UINT8               Reserved1;              ///< For future expansion
  UINT32              Reserved2[2];           ///< For future expansion
} TOUCH_SENSOR_GET_DEVICE_INFO_RSP_DATA;
C_ASSERT(sizeof(TOUCH_SENSOR_GET_DEVICE_INFO_RSP_DATA) == 48);


//
// TOUCH_SENSOR_SET_MODE_RSP code is sent in response to TOUCH_SENSOR_SET_MODE_CMD. This code will be followed
// by TOUCH_SENSOR_SET_MODE_RSP_DATA.
//
// Possible Status values:
//      TOUCH_STATUS_SUCCESS:           Command was proccessed successfully and mode was set.
//      TOUCH_STATUS_CMD_SIZE_ERROR:    Command sent did not match expected size. Other fields will not contain valid data.
//      TOUCH_STATUS_INVALID_PARAMS:    Input parameters are out of range.
//
typedef struct {
  TOUCH_STATUS    Status;         ///< See description above for possible Status values
  UINT32          Reserved[3];    ///< For future expansion
} TOUCH_SENSOR_SET_MODE_RSP_DATA;
C_ASSERT(sizeof(TOUCH_SENSOR_SET_MODE_RSP_DATA) == 16);


//
// TOUCH_SENSOR_SET_MEM_WINDOW_RSP code is sent in response to TOUCH_SENSOR_SET_MEM_WINDOW_CMD. This code will be followed
// by TOUCH_SENSOR_SET_MEM_WINDOW_RSP_DATA.
//
// Possible Status values:
//      TOUCH_STATUS_SUCCESS:           Command was proccessed successfully and memory window was set.
//      TOUCH_STATUS_CMD_SIZE_ERROR:    Command sent did not match expected size. Other fields will not contain valid data.
//      TOUCH_STATUS_INVALID_PARAMS:    Input parameters are out of range.
//      TOUCH_STATUS_ACCESS_DENIED:     Unable to map host address ranges for DMA.
//      TOUCH_STATUS_OUT_OF_MEMORY:     Unable to allocate enough space for needed buffers.
//
typedef struct {
  TOUCH_STATUS    Status;         ///< See description above for possible Status values
  UINT32          Reserved[3];    ///< For future expansion
} TOUCH_SENSOR_SET_MEM_WINDOW_RSP_DATA;
C_ASSERT(sizeof(TOUCH_SENSOR_SET_MEM_WINDOW_RSP_DATA) == 16);


//
// TOUCH_SENSOR_QUIESCE_IO_RSP code is sent in response to TOUCH_SENSOR_QUIESCE_IO_CMD. This code will be followed
// by TOUCH_SENSOR_QUIESCE_IO_RSP_DATA.
//
// Possible Status values:
//      TOUCH_STATUS_SUCCESS:                   Command was proccessed successfully and touch flow has stopped.
//      TOUCH_STATUS_CMD_SIZE_ERROR:            Command sent did not match expected size. Other fields will not contain valid data.
//      TOUCH_STATUS_QUIESCE_IO_IN_PROGRESS:    Indicates that Quiesce I/O is already in progress and this command cannot be accepted at this time.
//      TOUCH_STATIS_TIMEOUT:                   Indicates ME timed out waiting for Quiesce I/O flow to complete.
//
typedef struct {
  TOUCH_STATUS    Status;         ///< See description above for possible Status values
  UINT32          Reserved[3];    ///< For future expansion
} TOUCH_SENSOR_QUIESCE_IO_RSP_DATA;
C_ASSERT(sizeof(TOUCH_SENSOR_QUIESCE_IO_RSP_DATA) == 16);


// Reset Reason values used in TOUCH_SENSOR_HID_READY_FOR_DATA_RSP_DATA
typedef enum {
  TOUCH_RESET_REASON_UNKNOWN = 0,         ///< Reason for sensor reset is not known
  TOUCH_RESET_REASON_FEEDBACK_REQUEST,    ///< Reset was requested as part of TOUCH_SENSOR_FEEDBACK_READY_CMD
  TOUCH_RESET_REASON_HECI_REQUEST,        ///< Reset was requested via TOUCH_SENSOR_RESET_CMD
  TOUCH_RESET_REASON_MAX
} TOUCH_RESET_REASON;
C_ASSERT(sizeof(TOUCH_RESET_REASON) == 4);

//
// TOUCH_SENSOR_HID_READY_FOR_DATA_RSP code is sent in response to TOUCH_SENSOR_HID_READY_FOR_DATA_CMD. This code will be followed
// by TOUCH_SENSOR_HID_READY_FOR_DATA_RSP_DATA.
//
// Possible Status values:
//      TOUCH_STATUS_SUCCESS:                   Command was proccessed successfully and HID data was sent by DMA. This will only be sent in HID mode.
//      TOUCH_STATUS_CMD_SIZE_ERROR:            Command sent did not match expected size. Other fields will not contain valid data.
//      TOUCH_STATUS_REQUEST_OUTSTANDING:       Previous request is still outstanding, ME FW cannot handle another request for the same command.
//      TOUCH_STATUS_NOT_READY:                 Indicates memory window has not yet been set by BIOS/HID.
//      TOUCH_STATUS_SENSOR_DISABLED:           Indicates that ME to HID communication has been stopped either by TOUCH_SENSOR_QUIESCE_IO_CMD or TOUCH_SENSOR_CLEAR_MEM_WINDOW_CMD.
//      TOUCH_STATUS_SENSOR_UNEXPECTED_RESET:   Sensor signalled a Reset Interrupt. ME did not expect this and has no info about why this occurred.
//      TOUCH_STATUS_SENSOR_EXPECTED_RESET:     Sensor signalled a Reset Interrupt. ME either directly requested this reset, or it was expected as part of a defined flow in the EDS.
//      TOUCH_STATUS_QUIESCE_IO_IN_PROGRESS:    Indicates that Quiesce I/O is already in progress and this command cannot be accepted at this time.
//      TOUCH_STATUS_TIMEOUT:                   Sensor did not generate a reset interrupt in the time allotted. Could indicate sensor is not connected or malfunctioning.
//
typedef struct {
  TOUCH_STATUS    Status;                 ///< See description above for possible Status values
  UINT32          DataSize;               ///< Size of the data the ME DMA'd into a RawDataBuffer. Valid only when Status == TOUCH_STATUS_SUCCESS
  UINT8           TouchDataBufferIndex;   ///< Index to indicate which RawDataBuffer was used. Valid only when Status == TOUCH_STATUS_SUCCESS
  UINT8           ResetReason;            ///< If Status is TOUCH_STATUS_SENSOR_EXPECTED_RESET, ME will provide the casue. See TOUCH_RESET_REASON.
  UINT8           Reserved1[2];           ///< For future expansion
  UINT32          Reserved2[5];           ///< For future expansion
} TOUCH_SENSOR_HID_READY_FOR_DATA_RSP_DATA;
C_ASSERT(sizeof(TOUCH_SENSOR_HID_READY_FOR_DATA_RSP_DATA) == 32);


//
// TOUCH_SENSOR_FEEDBACK_READY_RSP code is sent in response to TOUCH_SENSOR_FEEDBACK_READY_CMD. This code will be followed
// by TOUCH_SENSOR_FEEDBACK_READY_RSP_DATA.
//
// Possible Status values:
//      TOUCH_STATUS_SUCCESS:           Command was proccessed successfully and any feedback or commands were sent to sensor.
//      TOUCH_STATUS_CMD_SIZE_ERROR:    Command sent did not match expected size. Other fields will not contain valid data.
//      TOUCH_STATUS_INVALID_PARAMS:    Input parameters are out of range.
//      TOUCH_STATUS_COMPAT_CHECK_FAIL  Indicates ProtocolVer does not match ME supported version. (non-fatal error)
//      TOUCH_STATUS_INTERNAL_ERROR:    Unexpected error occurred. This should not normally be seen.
//      TOUCH_STATUS_OUT_OF_MEMORY:     Insufficient space to store Calibration Data
//
typedef struct {
  TOUCH_STATUS    Status;         ///< See description above for possible Status values
  UINT8           FeedbackIndex;  ///< Index value from 0 to TOUCH_SENSOR_MAX_DATA_BUFFERS used to indicate which Feedback Buffer to use
  UINT8           Reserved1[3];   ///< For future expansion
  UINT32          Reserved2[6];   ///< For future expansion
} TOUCH_SENSOR_FEEDBACK_READY_RSP_DATA;
C_ASSERT(sizeof(TOUCH_SENSOR_FEEDBACK_READY_RSP_DATA) == 32);


//
// TOUCH_SENSOR_CLEAR_MEM_WINDOW_RSP code is sent in response to TOUCH_SENSOR_CLEAR_MEM_WINDOW_CMD. This code will be followed
// by TOUCH_SENSOR_CLEAR_MEM_WINDOW_RSP_DATA.
//
// Possible Status values:
//      TOUCH_STATUS_SUCCESS:                   Command was proccessed successfully and memory window was set.
//      TOUCH_STATUS_CMD_SIZE_ERROR:            Command sent did not match expected size. Other fields will not contain valid data.
//      TOUCH_STATUS_INVALID_PARAMS:            Input parameters are out of range.
//      TOUCH_STATUS_QUIESCE_IO_IN_PROGRESS:    Indicates that Quiesce I/O is already in progress and this command cannot be accepted at this time.
//
typedef struct {
  TOUCH_STATUS    Status;         ///< See description above for possible Status values
  UINT32          Reserved[3];    ///< For future expansion
} TOUCH_SENSOR_CLEAR_MEM_WINDOW_RSP_DATA;
C_ASSERT(sizeof(TOUCH_SENSOR_CLEAR_MEM_WINDOW_RSP_DATA) == 16);


//
// TOUCH_SENSOR_NOTIFY_DEV_READY_RSP code is sent in response to TOUCH_SENSOR_NOTIFY_DEV_READY_CMD. This code will be followed
// by TOUCH_SENSOR_NOTIFY_DEV_READY_RSP_DATA.
//
// Possible Status values:
//      TOUCH_STATUS_SUCCESS:               Command was proccessed successfully and sensor has been detected by ME FW.
//      TOUCH_STATUS_CMD_SIZE_ERROR:        Command sent did not match expected size.
//      TOUCH_STATUS_REQUEST_OUTSTANDING:   Previous request is still outstanding, ME FW cannot handle another request for the same command.
//      TOUCH_STATUS_TIMEOUT:               Sensor did not generate a reset interrupt in the time allotted. Could indicate sensor is not connected or malfunctioning.
//      TOUCH_STATUS_SENSOR_FAIL_FATAL:    Sensor indicated a fatal error, further operation is not possible. Error details can be found in ErrReg.
//      TOUCH_STATUS_SENSOR_FAIL_NONFATAL: Sensor indicated a non-fatal error. Error should be logged by caller and init flow can continue. Error details can be found in ErrReg.
//
typedef struct {
  TOUCH_STATUS            Status;         ///< See description above for possible Status values
  TOUCH_ERR_REG           ErrReg;         ///< Value of sensor Error Register, field is only valid for Status == TOUCH_STATUS_SENSOR_FAIL_FATAL or TOUCH_STATUS_SENSOR_FAIL_NONFATAL
  UINT32                  Reserved[2];    ///< For future expansion
} TOUCH_SENSOR_NOTIFY_DEV_READY_RSP_DATA;
C_ASSERT(sizeof(TOUCH_SENSOR_NOTIFY_DEV_READY_RSP_DATA) == 16);


//
// TOUCH_SENSOR_SET_POLICIES_RSP code is sent in response to TOUCH_SENSOR_SET_POLICIES_CMD. This code will be followed
// by TOUCH_SENSOR_SET_POLICIES_RSP_DATA.
//
// Possible Status values:
//      TOUCH_STATUS_SUCCESS:           Command was proccessed successfully and new policies were set.
//      TOUCH_STATUS_CMD_SIZE_ERROR:    Command sent did not match expected size. Other fields will not contain valid data.
//      TOUCH_STATUS_INVALID_PARAMS:    Input parameters are out of range.
//
typedef struct {
  TOUCH_STATUS    Status;         ///< See description above for possible Status values
  UINT32          Reserved[3];    ///< For future expansion
} TOUCH_SENSOR_SET_POLICIES_RSP_DATA;
C_ASSERT(sizeof(TOUCH_SENSOR_SET_POLICIES_RSP_DATA) == 16);


//
// TOUCH_SENSOR_GET_POLICIES_RSP code is sent in response to TOUCH_SENSOR_GET_POLICIES_CMD. This code will be followed
// by TOUCH_SENSOR_GET_POLICIES_RSP_DATA.
//
// Possible Status values:
//      TOUCH_STATUS_SUCCESS:           Command was proccessed successfully and new policies were set.
//      TOUCH_STATUS_CMD_SIZE_ERROR:    Command sent did not match expected size. Other fields will not contain valid data.
//
typedef struct {
  TOUCH_STATUS                Status;             ///< See description above for possible Status values
  TOUCH_POLICY_DATA           PolicyData;         ///< Contains the current policy
} TOUCH_SENSOR_GET_POLICIES_RSP_DATA;
C_ASSERT(sizeof(TOUCH_SENSOR_GET_POLICIES_RSP_DATA) == 20);


//
// TOUCH_SENSOR_RESET_RSP code is sent in response to TOUCH_SENSOR_RESET_CMD. This code will be followed
// by TOUCH_SENSOR_RESET_RSP_DATA.
//
// Possible Status values:
//      TOUCH_STATUS_SUCCESS:                   Command was proccessed successfully and sensor reset was completed.
//      TOUCH_STATUS_CMD_SIZE_ERROR:            Command sent did not match expected size. Other fields will not contain valid data.
//      TOUCH_STATUS_INVALID_PARAMS:            Input parameters are out of range.
//      TOUCH_STATUS_TIMEOUT:                   Sensor did not generate a reset interrupt in the time allotted. Could indicate sensor is not connected or malfunctioning.
//      TOUCH_STATUS_RESET_FAILED:              Sensor generated an invalid or unexpected interrupt.
//      TOUCH_STATUS_QUIESCE_IO_IN_PROGRESS:    Indicates that Quiesce I/O is already in progress and this command cannot be accepted at this time.
//
typedef struct {
  TOUCH_STATUS    Status;         ///< See description above for possible Status values
  UINT32          Reserved[3];    ///< For future expansion
} TOUCH_SENSOR_RESET_RSP_DATA;
C_ASSERT(sizeof(TOUCH_SENSOR_RESET_RSP_DATA) == 16);


//
// TOUCH_SENSOR_READ_ALL_REGS_RSP code is sent in response to TOUCH_SENSOR_READ_ALL_REGS_CMD. This code will be followed
// by TOUCH_SENSOR_READ_ALL_REGS_RSP_DATA.
//
// Possible Status values:
//      TOUCH_STATUS_SUCCESS:           Command was proccessed successfully and new policies were set.
//      TOUCH_STATUS_CMD_SIZE_ERROR:    Command sent did not match expected size. Other fields will not contain valid data.
//
typedef struct {
  TOUCH_STATUS                Status;      ///< See description above for possible Status values
  TOUCH_REG_BLOCK             SensorRegs;  ///< Returns first 64 bytes of register space used for normal touch operation. Does not include test mode register.
  UINT32                      Reserved[4]; ///< For future expansion
} TOUCH_SENSOR_READ_ALL_REGS_RSP_DATA;
C_ASSERT(sizeof(TOUCH_SENSOR_READ_ALL_REGS_RSP_DATA) == 84);


//
// TOUCH_SENSOR_GEN_TEST_PACKETS_RSP code is sent in response to TOUCH_SENSOR_GEN_TEST_PACKETS_CMD. This code will be followed
// by TOUCH_SENSOR_GEN_TEST_PACKETS_RSP_DATA.
//
// Possible Status values:
//      TOUCH_STATUS_SUCCESS:                   Command was proccessed successfully and new policies were set.
//      TOUCH_STATUS_CMD_SIZE_ERROR:            Command sent did not match expected size. Other fields will not contain valid data.
//      TOUCH_STATUS_INVALID_PARAMS:            Input parameters are out of range.
//      TOUCH_STATUS_REQUEST_OUTSTANDING:       Previous request is still outstanding, ME FW cannot handle another request for the same command.
//      TOUCH_STATUS_NOT_READY:                 Indicates memory window has not yet been set by BIOS/HID, or a previous test is still in progress.
//      TOUCH_STATUS_NO_SENSOR_FOUND:           Sensor has not yet been detected. Other fields will not contain valid data.
//      TOUCH_STATUS_QUIESCE_IO_IN_PROGRESS:    Indicates that Quiesce I/O is already in progress and this command cannot be accepted at this time.
//
typedef struct {
  TOUCH_STATUS    Status;         ///< See description above for possible Status values
  UINT32          Reserved[3];    ///< For future expansion
} TOUCH_SENSOR_GEN_TEST_PACKETS_RSP_DATA;
C_ASSERT(sizeof(TOUCH_SENSOR_GEN_TEST_PACKETS_RSP_DATA) == 16);


typedef struct {
  TOUCH_STATUS    Status;         ///< See description above for possible Status values
  UINT32          Reserved[3];    ///< For future expansion
} TOUCH_SENSOR_DBG_READ_DEVICE_RSP_DATA;
C_ASSERT(sizeof(TOUCH_SENSOR_DBG_READ_DEVICE_RSP_DATA) == 16);


typedef struct {
  TOUCH_STATUS    Status;         ///< See description above for possible Status values
  UINT32          Reserved[3];    ///< For future expansion
} TOUCH_SENSOR_DBG_WRITE_DEVICE_RSP_DATA;
C_ASSERT(sizeof(TOUCH_SENSOR_DBG_WRITE_DEVICE_RSP_DATA) == 16);


typedef struct {
  UINT32  IntPinVal;
  UINT32  Reserved[3];    ///< For future expansion
} TOUCH_SENSOR_DBG_GET_INT_PIN_VAL_RSP_DATA;
C_ASSERT(sizeof(TOUCH_SENSOR_DBG_GET_INT_PIN_VAL_RSP_DATA) == 16);


///
/// Structure to use in ME for sending various outgoing data. May not need to share this and move to internal ME header file
///
typedef struct {
  UINT32  CommandCode;
  union {
    TOUCH_SENSOR_GET_DEVICE_INFO_RSP_DATA       DeviceInfoRspData;
    TOUCH_SENSOR_SET_MODE_RSP_DATA              SetModeRspData;
    TOUCH_SENSOR_SET_MEM_WINDOW_RSP_DATA        SetMemWindowRspData;
    TOUCH_SENSOR_QUIESCE_IO_RSP_DATA            QuiesceIoRspData;
    TOUCH_SENSOR_HID_READY_FOR_DATA_RSP_DATA    HidReadyForDataRspData;
    TOUCH_SENSOR_FEEDBACK_READY_RSP_DATA        FeedbackReadyRspData;
    TOUCH_SENSOR_CLEAR_MEM_WINDOW_RSP_DATA      ClearMemWindowRspData;
    TOUCH_SENSOR_NOTIFY_DEV_READY_RSP_DATA      NotifyDevReadyRspData;
    TOUCH_SENSOR_SET_POLICIES_RSP_DATA          SetPoliciesRspData;
    TOUCH_SENSOR_GET_POLICIES_RSP_DATA          GetPoliciesRspData;
    TOUCH_SENSOR_RESET_RSP_DATA                 ResetRspData;
    TOUCH_SENSOR_READ_ALL_REGS_RSP_DATA         ReadAllRegsRspData;
    TOUCH_SENSOR_GEN_TEST_PACKETS_RSP_DATA      GenTestPacketsRspData;
    TOUCH_SENSOR_DBG_READ_DEVICE_RSP_DATA       ReadDevRspData;
    TOUCH_SENSOR_DBG_WRITE_DEVICE_RSP_DATA      WriteDevRspData;
    TOUCH_SENSOR_DBG_GET_INT_PIN_VAL_RSP_DATA   GetIntPinValRspData;
  } M2HData;
} TOUCH_SENSOR_MSG_M2H;
C_ASSERT(sizeof(TOUCH_SENSOR_MSG_M2H) == 88);


#define TOUCH_MSG_SIZE_MAX_BYTES    (MAX(sizeof(TOUCH_SENSOR_MSG_M2H), sizeof(TOUCH_SENSOR_MSG_H2M)))

#pragma pack()

#endif //_TOUCH_HECI_MSGS_H_
