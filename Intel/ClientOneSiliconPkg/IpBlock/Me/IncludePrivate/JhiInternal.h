/** @file
  Header file for JHI core (it used for internal library).

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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

#ifndef __JHI_INTERNAL_H__
#define __JHI_INTERNAL_H__

///
/// Version definition of JHI DXE driver
///
#define JHIDXE_VER_MAJOR                      1
#define JHIDXE_VER_MINOR                      2       ///< 0: Initial version [2015.02]
                                                      ///< 1: Support for ME1107, sync on [2015.03.02]
                                                      ///< 2: Support for ME1125, sync on [2015.05.11]
#define JHIDXE_VER_HOTFIX                     0
#define JHIDXE_VER_BUILD                      0

#define FILENAME_MAX                          256

#define JHI_CSS_HEADER_SIZE                   648

#ifndef ON
#define ON                                    1
#endif
#ifndef OFF
#define OFF                                   0
#endif

///
/// Debug flags
///
#define EN_DEBUG_JHI_DRIVER                   ON       ///< Enable/Disable debug message in JHI driver
#define EN_DEBUG_JHI_DRIVER_VERBOSE           OFF      ///< Enable/Disable verbose debug message in JHI driver
#define EN_DEBUG_BEIHAI_LIB                   ON       ///< Enable/Disable debug message in Beihai library
#define EN_DEBUG_BEIHAI_LIB_VERBOSE           OFF      ///< Enable/Disable verbose debug message in Beihai library
#define EN_DEBUG_JHIHLP_LIB                   OFF      ///< Enable/Disable debug message in JHI support library
#define EN_DEBUG_JHIHLP_LIB_VERBOSE           OFF      ///< Enable/Disable verbose debug message in JHI support library
#define EN_DEBUG_JHI_PERF_LOG                 OFF      ///< Using FPDT to get performance log for each JHI API
#define EN_DEBUG_JHI_PORT80                   OFF      ///< Using port 80 to indicate stages of execution

///
/// Software switch to change behavior of JHI (change only for debug)
///
#define EN_JHI_CHECK_POLICY                   ON       ///< Using ME policy to enable/disable JHI protocol
#define EN_JHI_TEARDOWN                       OFF      ///< Clean up all while uninitialized
#define EN_JHI_REINSTALL                      OFF      ///< Reinstall applet if it already exist
#define GET_APPLET_PROPERTY_OPEN_SESSION_W_A           ///< W/A only for CSE (ME11) for OpenSession routine (JHI DXE driver supports both for ME10 and ME11.)


#define DEBUG_JHI_DRIVER(s)
#define DEBUG_JHI_DRIVER_VERBOSE(s)
#define DEBUG_BEIHAI_LIB(s)
#define DEBUG_BEIHAI_LIB_VERBOSE(s)
#define DEBUG_JHIHLP_LIB(s)
#define DEBUG_JHIHLP_LIB_VERBOSE(s)

#if (EN_DEBUG_JHI_DRIVER == ON)
#undef  DEBUG_JHI_DRIVER
#define DEBUG_JHI_DRIVER                      DEBUG
#endif
#if (EN_DEBUG_JHI_DRIVER_VERBOSE == ON)
#undef  DEBUG_JHI_DRIVER_VERBOSE
#define DEBUG_JHI_DRIVER_VERBOSE              DEBUG
#endif
#if (EN_DEBUG_BEIHAI_LIB == ON)
#undef  DEBUG_BEIHAI_LIB
#define DEBUG_BEIHAI_LIB                      DEBUG
#endif
#if (EN_DEBUG_BEIHAI_LIB_VERBOSE == ON)
#undef  DEBUG_BEIHAI_LIB_VERBOSE
#define DEBUG_BEIHAI_LIB_VERBOSE              DEBUG
#endif
#if (EN_DEBUG_JHIHLP_LIB == ON)
#undef  DEBUG_JHIHLP_LIB
#define DEBUG_JHIHLP_LIB                      DEBUG
#endif
#if (EN_DEBUG_JHIHLP_LIB_VERBOSE == ON)
#undef  DEBUG_JHIHLP_LIB_VERBOSE
#define DEBUG_JHIHLP_LIB_VERBOSE              DEBUG
#endif


///
/// IDs for performance log by SysScope
///
#define JHI_PERFID_BASE                       (0x8800)
#define JHI_PERFID_INITIALIZE                 (JHI_PERFID_BASE + 0x00)    ///< JHI_Initialize
#define JHI_PERFID_DEINIT                     (JHI_PERFID_BASE + 0x10)    ///< JHI_Deinit
#define JHI_PERFID_INSTALL2                   (JHI_PERFID_BASE + 0x20)    ///< JHI_Install2
#define JHI_PERFID_UNINSTALL                  (JHI_PERFID_BASE + 0x30)    ///< JHI_Uninstall
#define JHI_PERFID_GET_APPLET_PROPERTY        (JHI_PERFID_BASE + 0x40)    ///< JHI_GetAppletProperty
#define JHI_PERFID_CREATE_SESSION             (JHI_PERFID_BASE + 0x50)    ///< JHI_CreateSession
#define JHI_PERFID_CLOSE_SESSION              (JHI_PERFID_BASE + 0x60)    ///< JHI_CloseSession
#define JHI_PERFID_GET_SESSION_COUNT          (JHI_PERFID_BASE + 0x70)    ///< JHI_GetSessionsCount
#define JHI_PERFID_GET_SESSION_INFO           (JHI_PERFID_BASE + 0x80)    ///< JHI_GetSessionInfo
#define JHI_PERFID_GET_VERSION_INFO           (JHI_PERFID_BASE + 0x90)    ///< JHI_GetVersionInfo
#define JHI_PERFID_SENDRECV                   (JHI_PERFID_BASE + 0xa0)    ///< JHI_SendAndRecv2
#define JHI_PERFID_INSTALL3                   (JHI_PERFID_BASE + 0xb0)    ///< JHI_Install3


#if EN_DEBUG_JHI_PORT80
#define JHI_DEBUG_PORT80_PAUSE(number, ms) \
  do {  \
    IoWrite16(0x80, (UINT16)(number));  \
    if ((ms) != 0) {  \
      PchPmTimerStall (1000 * (ms)); \
    } \
  } while (0)
#define JHI_DEBUG_PORT80(number)  JHI_DEBUG_PORT80_PAUSE (number, 0)
#else
#define JHI_DEBUG_PORT80_PAUSE(number, ms)
#define JHI_DEBUG_PORT80(number)
#endif


#if EN_DEBUG_JHI_PERF_LOG

#if EN_DEBUG_JHI_PORT80
#define PREF_PROBE_BLOCK(number, expr) \
  do {  \
    UINT16 Port80; \
    Port80 = IoRead16 (0x80); \
    IoWrite16 (0x80, (UINT16) (number)); \
    PERF_START_EX (NULL, "EventRec", NULL, AsmReadTsc (), (UINTN)(number)); \
    expr  \
    PERF_END_EX (NULL, "EventRec", NULL, AsmReadTsc (), (UINTN)((number)+1)); \
    IoWrite16 (0x80, Port80); \
  } while (0)
#else
#define PREF_PROBE_BLOCK(number, expr) \
  do {  \
    PERF_START_EX (NULL, "EventRec", NULL, AsmReadTsc (), (UINTN)(number)); \
    expr  \
    PERF_END_EX (NULL, "EventRec", NULL, AsmReadTsc (), (UINTN)((number)+1)); \
  } while (0)
#endif

#else // EN_DEBUG_JHI_PERF_LOG == OFF
#define PREF_PROBE_BLOCK(number, expr)        expr
#endif


#endif  // __JHI_INTERNAL_H__
