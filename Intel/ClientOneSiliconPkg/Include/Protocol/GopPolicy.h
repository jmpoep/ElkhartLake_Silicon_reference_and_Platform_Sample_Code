/** @file
  Interface definition for GopPolicy Protocol.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2016 Intel Corporation.

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
#ifndef _GOP_POLICY_PROTOCOL_H_
#define _GOP_POLICY_PROTOCOL_H_


#define GOP_POLICY_PROTOCOL_REVISION_01  0x01
#define GOP_POLICY_PROTOCOL_REVISION_03  0x03

typedef enum {
  LidClosed,
  LidOpen,
  LidStatusMax
} LID_STATUS;

typedef enum {
  Docked,
  UnDocked,
  DockStatusMax
} DOCK_STATUS;

///
/// Function to retrieve LID status
///
typedef
EFI_STATUS
(EFIAPI *GET_PLATFORM_LID_STATUS) (
  OUT LID_STATUS * CurrentLidStatus
  );

///
/// Function to retrieve Dock status
///
typedef
EFI_STATUS
(EFIAPI *GET_PLATFORM_DOCK_STATUS) (
 OUT DOCK_STATUS  CurrentDockStatus
);

///
/// Function to retrieve VBT table address and size
///
typedef
EFI_STATUS
(EFIAPI *GET_VBT_DATA) (
  OUT EFI_PHYSICAL_ADDRESS * VbtAddress,
  OUT UINT32               *VbtSize
  );

/**
  System Agent Graphics Output Protocol (GOP) - Policy Protocol\n
  Graphics Output Protocol (GOP) is a UEFI API replacing legacy Video ROMs for EFI boot\n
  When GOP Driver is used this protocol can be consumed by GOP driver or platform code for GOP relevant initialization\n
  All functions in this protocol should be initialized by platform code basing on platform implementation\n
**/
typedef struct {
  UINT32                    Revision;              ///< Protocol revision
  GET_PLATFORM_LID_STATUS   GetPlatformLidStatus;  ///< Protocol function to get Lid Status. Platform code should provide this function basing on design.
  GET_VBT_DATA              GetVbtData;            ///< Protocol function to get Vbt Data address and size. Platform code should provide this function basing on design.
  GET_PLATFORM_DOCK_STATUS  GetPlatformDockStatus;  ///< Function pointer for get platform dock status.
  EFI_GUID                  GopOverrideGuid;        ///< A GUID provided by BIOS in case GOP is to be overridden.
} GOP_POLICY_PROTOCOL;

extern EFI_GUID gGopPolicyProtocolGuid;
extern EFI_GUID gIntelGraphicsVbtGuid;

#endif
