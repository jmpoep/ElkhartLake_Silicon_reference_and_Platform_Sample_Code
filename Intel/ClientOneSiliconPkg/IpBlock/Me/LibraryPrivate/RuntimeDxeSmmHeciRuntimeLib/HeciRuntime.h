/** @file
  Internal header file for the HECI Runtime library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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
#ifndef _HECI_RUNTIME_H_
#define _HECI_RUNTIME_H_

#include <Register/HeciRegs.h>
#include <Register/MeRegs.h>
#include <PcieRegs.h>

#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/PciLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/TimerLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/CseVariableStorageStatusLib.h>
#include <Library/HeciRuntimeLib.h>

#include <Protocol/HeciProtocol.h>

///
/// Timeout values
///
#define STALL_1_MILLISECOND               1000
#define HECI_INIT_TIMEOUT_MS              15000
#define HECI_RECEIVE_TIMEOUT_MS           30000
#define HECI_SEND_TIMEOUT_MS              30000

#define HECI_BAR_LENGTH                   SIZE_4KB
#define HECI_BASE_LENGTH                  SIZE_4KB

#pragma pack(push, 1)

typedef struct {
  EFI_PHYSICAL_ADDRESS  BaseAddress;
  EFI_PHYSICAL_ADDRESS  Bar0Address;
  EFI_PHYSICAL_ADDRESS  SegmentBaseAddress;
  BOOLEAN               RuntimeAccessible;
} HECI_RUNTIME_DEVICE_CONTEXT;

#pragma pack(pop)

///
/// Header for all HECI message message placed in an Intel MEI circular buffer
///
typedef union {
  UINT32  Data;
  struct {
    /**
      This is the logical address of the Intel ME client of the message. This address is assigned
      during ME firmware initialization.
    **/
    UINT32  MeAddress       : 8;
    /**
      This is the logical address of the Host client of the message. This address is assigned
      when the host client registers itself with the Host MEI driver.
    **/
    UINT32  HostAddress     : 8;
    /**
      This is the message length in bytes, not including the MEI_MESSAGE_HEADER. A value of 0
      indicates no additional bytes are part of the message.
    **/
    UINT32  Length          : 9;
    UINT32  Reserved        : 6;
    UINT32  MessageComplete : 1; ///< Indicates the last message of the list
  } Fields;
} HECI_MESSAGE_HEADER;

/**
  This function provides a standard way to verify the HECI cmd and MBAR regs
  in its PCI cfg space are setup properly and that the local mHeciContext
  variable matches this info.

  @param[in] HeciDev              HECI device to be accessed.

  @retval HeciMemBar              HECI Memory BAR.
                                  0 - invalid BAR value returned.
**/
EFI_PHYSICAL_ADDRESS
EFIAPI
CheckAndFixHeciForAccess (
  IN HECI_CONTEXT_DEVICE HeciDev
  );

/**
  Initialize's HECI device context that may be used through OS runtime.

**/
VOID
EFIAPI
InitializeHeciDeviceContext (
  VOID
  );

#endif
