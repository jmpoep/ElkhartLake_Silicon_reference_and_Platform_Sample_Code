/** @file
  APIs of PCH TCO SMI Dispatch Protocol.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2016 Intel Corporation.

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
#ifndef _PCH_TCO_SMI_DISPATCH_PROTOCOL_H_
#define _PCH_TCO_SMI_DISPATCH_PROTOCOL_H_

//
// Extern the GUID for protocol users.
//
extern EFI_GUID                         gPchTcoSmiDispatchProtocolGuid;

//
// Forward reference for ANSI C compatibility
//
typedef struct _PCH_TCO_SMI_DISPATCH_PROTOCOL     PCH_TCO_SMI_DISPATCH_PROTOCOL;

//
// Member functions
//

/**
  Callback function for an PCH TCO SMI handler dispatch.

  @param[in] DispatchHandle             The unique handle assigned to this handler by register function.

**/
typedef
VOID
(EFIAPI *PCH_TCO_SMI_DISPATCH_CALLBACK) (
  IN EFI_HANDLE                         DispatchHandle
  );

/**
  Register a child SMI source dispatch function for PCH TCO SMI events.

  @param[in] This                       Protocol instance pointer.
  @param[in] DispatchFunction           Pointer to dispatch function to be invoked for
                                        this SMI source
  @param[out] DispatchHandle            Handle of dispatch function, for when interfacing
                                        with the parent SMM driver.

  @retval EFI_SUCCESS                   The dispatch function has been successfully
                                        registered and the SMI source has been enabled.
  @retval EFI_DEVICE_ERROR              The driver was unable to enable the SMI source.
  @retval EFI_OUT_OF_RESOURCES          Not enough memory (system or SMM) to manage this child.
  @retval EFI_ACCESS_DENIED             Return access denied if the EndOfDxe event has been triggered
**/
typedef
EFI_STATUS
(EFIAPI *PCH_TCO_SMI_DISPATCH_REGISTER) (
  IN  PCH_TCO_SMI_DISPATCH_PROTOCOL     *This,
  IN  PCH_TCO_SMI_DISPATCH_CALLBACK     DispatchFunction,
  OUT EFI_HANDLE                        *DispatchHandle
  );

/**
  Unregister a child SMI source dispatch function with a parent TCO SMM driver

  @param[in] This                       Protocol instance pointer.
  @param[in] DispatchHandle             Handle of dispatch function to deregister.

  @retval EFI_SUCCESS                   The dispatch function has been successfully
                                        unregistered and the SMI source has been disabled
                                        if there are no other registered child dispatch
                                        functions for this SMI source.
  @retval EFI_INVALID_PARAMETER         Handle is invalid.
  @retval EFI_ACCESS_DENIED             Return access denied if the EndOfDxe event has been triggered
**/
typedef
EFI_STATUS
(EFIAPI *PCH_TCO_SMI_DISPATCH_UNREGISTER) (
  IN  PCH_TCO_SMI_DISPATCH_PROTOCOL     *This,
  IN  EFI_HANDLE                        DispatchHandle
  );

/**
  Interface structure for PCH TCO SMIs Dispatch Protocol
  The PCH TCO SMI DISPATCH PROTOCOL provides the ability to dispatch function for PCH TCO related SMIs.
  It contains SMI types of Mch, TcoTimeout, OsTco, Nmi, IntruderDectect, and BiowWp.
**/
struct _PCH_TCO_SMI_DISPATCH_PROTOCOL {
  /**
    This member specifies the revision of this structure. This field is used to
    indicate backwards compatible changes to the protocol.
  **/
  UINT8                                 Revision;
  /**
    Smi unregister function for PCH TCO SMI DISPATCH PROTOCOL.
  **/
  PCH_TCO_SMI_DISPATCH_UNREGISTER       UnRegister;
  /**
    Mch
    The event is triggered when PCH received a DMI special cycle message using DMI indicating that
    it wants to cause an SMI.
    The software must read the processor to determine the reason for the SMI.
  **/
  PCH_TCO_SMI_DISPATCH_REGISTER         MchRegister;
  /**
    TcoTimeout
    The event is triggered by PCH to indicate that the SMI was caused by the TCO timer reaching 0.
  **/
  PCH_TCO_SMI_DISPATCH_REGISTER         TcoTimeoutRegister;
  /**
    OsTco
    The event is triggered when software caused an SMI# by writing to the TCO_DAT_IN register (TCOBASE + 02h).
  **/
  PCH_TCO_SMI_DISPATCH_REGISTER         OsTcoRegister;
  /**
    Nmi
    The event is triggered by the PCH when an SMI# occurs because an event occurred that would otherwise have
    caused an NMI (because NMI2SMI_EN is set)
  **/
  PCH_TCO_SMI_DISPATCH_REGISTER         NmiRegister;
  /**
    IntruderDectect
    The event is triggered by PCH to indicate that an intrusion was detected.
  **/
  PCH_TCO_SMI_DISPATCH_REGISTER         IntruderDetRegister;
  /**
    SpiBiosWp
    This event is triggered when SMI# was caused by the TCO logic and
    SPI flash controller asserted Synchronous SMI by BIOS lock enable set.
  **/
  PCH_TCO_SMI_DISPATCH_REGISTER         SpiBiosWpRegister;
  /**
    LpcBiosWp
    This event is triggered when SMI# was caused by the TCO logic and
    LPC/eSPI BIOS lock enable set.
  **/
  PCH_TCO_SMI_DISPATCH_REGISTER         LpcBiosWpRegister;
  /**
    NewCentury
    This event is triggered when SMI# was caused by the TCO logic and
    year of RTC date rolls over a century (99 to 00).
  **/
  PCH_TCO_SMI_DISPATCH_REGISTER         NewCenturyRegister;
};

/**
  PCH TCO SMI dispatch revision number

  Revision 1:   Initial version
  Revision 2:   Add NEWCENTURY support
**/
#define PCH_TCO_SMI_DISPATCH_REVISION             2

#endif
