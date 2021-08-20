/** @file
  PCH SMM IO Trap Control Protocol

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2016 Intel Corporation.

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
#ifndef _PCH_SMM_IO_TRAP_CONTROL_H_
#define _PCH_SMM_IO_TRAP_CONTROL_H_


//
// Extern the GUID for protocol users.
//
extern EFI_GUID                                   gPchSmmIoTrapControlGuid;

//
// Forward reference for ANSI C compatibility
//
typedef struct _PCH_SMM_IO_TRAP_CONTROL_PROTOCOL  PCH_SMM_IO_TRAP_CONTROL_PROTOCOL;

//
// Related Definitions
//

//
// Member functions
//

/**
  The Prototype of Pause and Resume IoTrap callback function.

  @param[in] This                 Pointer to the PCH_SMM_IO_TRAP_CONTROL_PROTOCOL instance.
  @param[in] DispatchHandle       Handle of the child service to change state.

  @retval EFI_SUCCESS             This operation is complete.
  @retval EFI_INVALID_PARAMETER   The DispatchHandle is invalid.
  @retval EFI_ACCESS_DENIED       The SMI status is alrady PAUSED/RESUMED.
**/
typedef
EFI_STATUS
(EFIAPI *PCH_SMM_IO_TRAP_CONTROL_FUNCTION) (
  IN PCH_SMM_IO_TRAP_CONTROL_PROTOCOL           * This,
  IN EFI_HANDLE                                 DispatchHandle
  );

/**
  Interface structure for the SMM IO trap pause and resume protocol
  This protocol provides the functions to runtime control the IoTrap SMI enabled/disable.
  This applys the capability to the DispatchHandle which returned by IoTrap callback
  registration, and the DispatchHandle which must be MergeDisable = TRUE and Address != 0.
  Besides, when S3 resuem, it only restores the state of IoTrap callback registration.
  The Paused/Resume state won't be restored after S3 resume.
**/
struct _PCH_SMM_IO_TRAP_CONTROL_PROTOCOL {
  /**
    This runtime pauses a registered IoTrap handler.
  **/
  PCH_SMM_IO_TRAP_CONTROL_FUNCTION      Pause;
  /**
    This runtime resumes a registered IoTrap handler.
  **/
  PCH_SMM_IO_TRAP_CONTROL_FUNCTION      Resume;
};

#endif
