/** @file
  Me FWSTS Lib implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2017 Intel Corporation.

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

#include <Library/BaseLib.h>
#include <FwStsSmbiosTable.h>
#include <Library/PciSegmentLib.h>

///
/// Global FwSts Device List
///
CONST MEI_DEV_STRING gFwStsDeviceList [] = {
  {HECI1_DEVICE, MEI1_FWSTS_STRING},
  {HECI2_DEVICE, MEI2_FWSTS_STRING},
  {HECI3_DEVICE, MEI3_FWSTS_STRING},
  {HECI4_DEVICE, MEI4_FWSTS_STRING}
};

///
/// Global FwSts Registers Table
///
CONST UINT32 gFwStsOffsetTable [] = {
  R_ME_HFS,
  R_ME_HFS_2,
  R_ME_HFS_3,
  R_ME_HFS_4,
  R_ME_HFS_5,
  R_ME_HFS_6
};

/**
  Find the index of ME FwStsValue in gFwStsOffsetTable.

  @param[in]  FwStsValue   FWSTS register value.

  @retval     UINT32       The index of FwStsValue in gFwStsOffsetTable
  @retval     0xFF         The index of FwStsValue is not found
**/
UINT32
EFIAPI
FindMeFwStsIndex (
  IN UINT32  FwStsValue
  )
{
  UINT32   Index;

  for (Index = 0; Index < (sizeof (gFwStsOffsetTable) / sizeof (UINT32)); Index++) {
    if (FwStsValue == gFwStsOffsetTable [Index]) {
      return Index;
    }
  }
  return 0xFF;
}

/**
  Get ME device count that needs to report FWSTS SMBIOS

  @retval  UINT8      Count of device list.
**/
UINT8
EFIAPI
GetMeFwStsDeviceCount (
  VOID
  )
{
  return (sizeof (gFwStsDeviceList) / sizeof (MEI_DEV_STRING));
}

/**
  Get ME register offset count that needs to report FWSTS SMBIOS

  @retval  UINT8      Count of register offset.
**/
UINT8
EFIAPI
GetMeFwStsOffsetCount (
  VOID
  )
{
  return (sizeof (gFwStsOffsetTable) / sizeof (UINT32));
}

/**
  Check if Debug CPU Disabled (DCD) bit is set from FIT CPU Debugging [Disabled].
  If it is set, CPU probe is disabled.

  @retval TRUE    DCD is set
  @retval FALSE   DCD is clear
**/
BOOLEAN
IsCpuDebugDisabled (
  VOID
  )
{
  UINT32                  MeFwSts6;

  MeFwSts6 = PciSegmentRead32 (
               PCI_SEGMENT_LIB_ADDRESS (
                 ME_SEGMENT,
                 ME_BUS,
                 ME_DEVICE_NUMBER,
                 HECI_FUNCTION_NUMBER,
                 R_ME_HFS_6
                 )
               );
  if (MeFwSts6 & B_ME_HFS_6_DCD) {
    return TRUE;
  }
  return FALSE;
}