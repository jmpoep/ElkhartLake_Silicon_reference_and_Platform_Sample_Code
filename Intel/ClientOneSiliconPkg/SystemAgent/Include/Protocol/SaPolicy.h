/** @file
  Interface definition details between System Agent and platform drivers during DXE phase.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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
#ifndef _SA_POLICY_H_
#define _SA_POLICY_H_

#include <SaCommonDefinitions.h>
#include <ConfigBlock.h>
#include <Library/ConfigBlockLib.h>
#include <GraphicsConfig.h>
#include <ConfigBlock/MemoryDxeConfig.h>
#include <ConfigBlock/MiscDxeConfig.h>
#include <ConfigBlock/PcieDxeConfig.h>
#include <ConfigBlock/VbiosDxeConfig.h>

///
/// Extern the GUID for protocol users.
///
extern EFI_GUID gSaPolicyProtocolGuid;
extern EFI_GUID gGraphicsDxeConfigGuid;
extern EFI_GUID gMiscDxeConfigGuid;
extern EFI_GUID gPcieDxeConfigGuid;
extern EFI_GUID gMemoryDxeConfigGuid;
extern EFI_GUID gVbiosDxeConfigGuid;

/**
  Don't change the original SA_POLICY_PROTOCOL_REVISION macro, external
  modules maybe have consumed this macro in their source code.  Directly
  update the SA_POLICY_PROTOCOL_REVISION version number may cause those
  external modules to auto mark themselves wrong version info.
  Always create new version macro for new Policy protocol interface.
**/
#define SA_POLICY_PROTOCOL_REVISION  1

#define CPU_PCIE_DEV_END_OF_TABLE                0xFFFF

#define LTR_MAX_SNOOP_LATENCY_VALUE             0x0846    ///< Intel recommended maximum value for Snoop Latency
#define LTR_MAX_NON_SNOOP_LATENCY_VALUE         0x0846    ///< Intel recommended maximum value for Non-Snoop Latency


/**
  SA DXE Policy

 The SA_POLICY_PROTOCOL producer drvier is recommended to
 set all the SA_POLICY_PROTOCOL size buffer zero before init any member parameter,
 this clear step can make sure no random value for those unknow new version parameters.

 Make sure to update the Revision if any change to the protocol, including the existing
 internal structure definations.\n
  Note: Here revision will be bumped up when adding/removing any config block under this structure.\n
  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_TABLE_HEADER      TableHeader;    ///< Offset 0-31
/*
  Individual Config Block Structures are added here in memory as part of AddConfigBlock()
*/
} SA_POLICY_PROTOCOL;

#endif
