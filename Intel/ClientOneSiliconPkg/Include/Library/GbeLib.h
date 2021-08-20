/** @file
  Header file for GbeLib.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2018 Intel Corporation.

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
#ifndef _GBE_LIB_H_
#define _GBE_LIB_H_

/**
  Check whether GbE region is valid
  Check SPI region directly since GbE might be disabled in SW.

  @retval TRUE                    Gbe Region is valid
  @retval FALSE                   Gbe Region is invalid
**/
BOOLEAN
IsGbeRegionValid (
  VOID
  );

/**
  Check whether GBE controller is enabled in the platform.

  @retval TRUE                    GbE is enabled
  @retval FALSE                   GbE is disabled
**/
BOOLEAN
IsGbePresent (
  VOID
  );

/**
  Checks if Gbe is Enabled or Disabled

  @retval  BOOLEAN    TRUE if device is enabled, FALSE otherwise.
**/
BOOLEAN
IsGbeEnabled (
  VOID
  );

/**
  Returns Gigabit Ethernet PCI Device Number

  @retval  GbE device number
**/
UINT8
GbeDevNumber (
  VOID
  );

/**
  Returns Gigabit Ethernet PCI Function Number

  @retval  GbE function number
**/
UINT8
GbeFuncNumber (
  VOID
  );

/**
  Gets Phy Revision and Model Number

  @param [out] LanPhyRevision   Return Value

  @return EFI_SUCCESS           Phy Revision was obtained
          EFI_NOT_FOUND         Gbe is disabled or not present
          EFI_DEVICE_ERROR      Gbe class code check failed
          EFI_INVALID_PARAMETER When GbeBar is incorrect
                                When Phy register or address is out of bounds
**/
EFI_STATUS
GbeGetLanPhyRevision (
  OUT  UINT16  *LanPhyRevision
  );

#endif // _GBE_LIB_H_
