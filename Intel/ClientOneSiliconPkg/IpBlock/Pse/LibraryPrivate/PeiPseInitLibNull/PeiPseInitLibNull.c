/** @file
  Initializes Programmable Service Engine Controller (PSE).

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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

#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PmcLib.h>
#include <Library/PchPcrLib.h>
#include <PchResetPlatformSpecific.h>
#include <Ppi/SiPolicy.h>
#include <Library/GpioPrivateLib.h>
#include <Library/GpioNativePads.h>
#include <Library/PeiPseLib.h>
#include <Library/PeiPseInitLib.h>
#include <Library/PseInfoLib.h>
#include <Library/SiScheduleResetLib.h>
#include <Library/PeiPmcPrivateLib.h>
#include <Library/PmcPrivateLib.h>
#include <Library/PchPseIoLib.h>
#include <Library/PsfLib.h>
#include <Library/PeiItssLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PciLib.h>
#include <Library/PchInfoLib.h>
#include <Library/IoLib.h>
#include <Library/CpuPlatformLib.h>

#include <IndustryStandard/Pci30.h>
#include <Register/PchRegs.h>
#include <Register/PseRegs.h>

/**
  Configures PSE devices interrupt pin and IRQ assignment

  @param[in]  SiPolicy       Pointer to SI_POLICY_PPI
  @param[in] Controller      PSE IO Controller
**/
VOID
PseIoIntSet (
  IN SI_POLICY_PPI               *SiPolicy,
  IN PCH_PSE_IO_CONTROLLER       Controller
  )
{

}



/**
  Program temp MmioBase address into BAR register.

  @param[in] PciBaseAddress  Address of the PCI config space
  @param[in] MmioBase        Address to be used to access MMIO space
**/
VOID
PseControllerEnableMmio (
  IN  UINT64  PciBaseAddress,
  IN  UINTN   MmioBase
  )
{

}

VOID
PseTgpioInit (
  IN  SI_POLICY_PPI   *SiPolicy,
  IN  UINT8           PseTgpioIndex
  );

/**
  Clear BAR address.

  @param[in] PciBaseAddress  Address of PCI config space
**/
VOID
PseControllerDisableMmio (
  IN UINT64  PciBaseAddress
  )
{

}

/**
  Sets Programmable Service Engine (PSE) PSF Function Disable
**/
STATIC
VOID
PseDisable (
  VOID
  )
{

}

/**
  Initialize Programmable Service Engine (PSE)

  @param[in]  SiPolicy            Pointer to SI_POLICY_PPI
**/
VOID
PseInit (
  IN  SI_POLICY_PPI    *SiPolicy
  )
{

}
