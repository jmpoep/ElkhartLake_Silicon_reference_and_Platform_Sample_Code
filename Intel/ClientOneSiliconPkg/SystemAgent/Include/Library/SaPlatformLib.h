/** @file
  Header file for SaPlatformLib.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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

#ifndef _SA_PLATFORM_LIB_H_
#define _SA_PLATFORM_LIB_H_

#include <CpuAccess.h>

/**
  Determine if PCH Link is DMI/OPI

  @param[in] CpuModel             CPU model

  @retval TRUE                    DMI
  @retval FALSE                   OPI
**/
BOOLEAN
IsPchLinkDmi (
  IN CPU_FAMILY  CpuModel
  );

/**
  Returns the number of DMI lanes for current CPU

  @retval UINT8
**/
UINT8
GetMaxDmiLanes (
  );


/**
  Returns the number of DMI bundles for current CPU

  @retval UINT8
**/
UINT8
GetMaxDmiBundles (
  );


/**
  Returns the function numbers for current CPU

  @retval UINT8
**/
UINT8
GetMaxPegFuncs (
  );


/**
  Returns the number of DMI lanes for current CPU

  @retval UINT8
**/
UINT8
GetMaxPegLanes (
  );


/**
  Returns the number of DMI bundles for current CPU

  @retval UINT8
**/
UINT8
GetMaxPegBundles (
  );

/**
  Checks if PEG port is present

  @retval TRUE     PEG is presented
  @retval FALSE    PEG is not presented
**/
BOOLEAN
IsPegPresent (
  VOID
  );

/**
  Checks if SKU is DisplayOnly

  @retval FALSE  SKU is not DisplayOnly
  @retval TRUE   SKU is DisplayOnly
**/
BOOLEAN
EFIAPI
IsDisplayOnlySku (
  VOID
  );

/**
  Checks if SKU is Mobile

  @retval FALSE  SKU is not Mobile
  @retval TRUE   SKU is Mobile
**/
BOOLEAN
EFIAPI
IsMobileSku (
  VOID
  );

/**
  Checks if SKU is Desktop

  @retval FALSE  SKU is not Desktop
  @retval TRUE   SKU is Desktop
**/
BOOLEAN
EFIAPI
IsDesktopSku (
  VOID
  );

/**
  Checks if SKU is Halo

  @retval FALSE  SKU is not Halo
  @retval TRUE   SKU is Halo
**/
BOOLEAN
EFIAPI
IsHaloSku (
  VOID
  );

/**
  Checks if SKU is Server

  @retval FALSE  SKU is not Server
  @retval TRUE   SKU is Server
**/
BOOLEAN
EFIAPI
IsServerSku (
  VOID
  );

/**
  Checks if SAM is enabled or not.

  @retval FALSE  SAM is disabled
  @retval TRUE   SAM is enabled
**/
BOOLEAN
EFIAPI
IsSamEnabled (
  VOID
  );

#endif
