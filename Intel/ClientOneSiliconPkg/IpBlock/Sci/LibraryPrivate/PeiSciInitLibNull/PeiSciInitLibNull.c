/** @file
  Initializes SCI Device in PEI

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
#include <Library/PciSegmentLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PmcPrivateLib.h>
#include <Ppi/SiPolicy.h>
#include <IndustryStandard/Pci30.h>
#include <Register/PchRegs.h>
#include <Register/PchPcrRegs.h>
#include <Register/PsfRegsVer3.h>
#include <Register/PchRegsPsf.h>
#include <Register/SciRegs.h>
#include <Register/PchRegsSciEhl.h>
#include <IndustryStandard/Pci30.h>
#include <Library/IoLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PeiSciInitLib.h>
#include <Library/TimerLib.h>


/**
  Calculate CRC 16.

  @param[in] CrcData      Pointer to the data to calculate CRC
  @param[in] CrcSize      Length of the CRC data size

  @retval    UINT16       CRC value of given data
**/
UINT16
CalculateCrc16 (
  IN UINT8   *CrcData,
  IN UINT16  CrcSize
  )
{

}

/**
  Configure SCI device registers
**/
STATIC
VOID
ConfigureSciRegisters (
  VOID
  )
{

}

/**
  Enable SCI MMIO space.

  @param[in] PciBaseAddress  Address of the controller's PCI space
  @param[in] MmioBase        MMIO address to use during initialization
**/
STATIC
VOID
SciEnableMmio (
  IN UINT64  PciBaseAddress,
  IN UINT32  MmioBase
  )
{

}

/**
  Disable SCI MMIO space.

  @param[in] PciBaseAddress  Address of the controller's PCI space
**/
STATIC
VOID
SciDisableMmio (
  IN UINT64  PciBaseAddress
  )
{

}

/**
  Check the bit of doorbell in for mailbox readiness.

  @param[in] MmioBase  MMIO address to use during initialization

  @retval    BOOLEAN   TRUE if doorbell is ready, else FALSE
**/
STATIC
BOOLEAN
SciDoorbellInCheck (
  IN UINT32  MmioBase
  )
{
  return TRUE;
}

/**
  Check the bit of doorbell out for mailbox readiness.

  @param[in] MmioBase  MMIO address to use during initialization

  @retval    BOOLEAN   TRUE if doorbell is ready, else FALSE
**/
STATIC
BOOLEAN
SciDoorbellOutCheck (
  IN UINT32  MmioBase
  )
{
  return TRUE;
}

/**
  Check the bit of doorbell in for mailbox readiness.

  @param[in] MbCommand    Mailbox command message
  @param[in] MbResponse   Mailbox response message

  @retval    BOOLEAN      TRUE if nothing is wrong, else FALSE
**/
STATIC
BOOLEAN
SciVerifyResponse (
  IN SCI_BOOT_CMPL_COMMAND    *MbCommand,
  IN SCI_BOOT_CMPL_RESPONSE   *MbResponse
  )
{
  return TRUE;
}

/**
  Query SCI boot status.

  @retval    BOOLEAN   TRUE if SCI boot successful, else FALSE
**/
BOOLEAN
SciBootCheck (
  VOID
  )
{
  return TRUE;
}

/**
  Notify SCI with BIOS boot complete message.

  @retval     BOOLEAN   TRUE if communication successful, else FALSE
**/
BOOLEAN
SciBiosBootComplete (
  VOID
  )
{
  return TRUE;
}

/**
  Initialize SCI device.

  @param[in] SiPolicy             The SI Policy PPI instance

**/
VOID
SciInit (
  IN  SI_POLICY_PPI               *SiPolicy
  )
{

}

