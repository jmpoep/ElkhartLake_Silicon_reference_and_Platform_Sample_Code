/** @file
  Gbe MDI Library.
  All function in this library is available for PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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

#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/TimerLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/GbeMdiLib.h>
#include <Register/GbeRegs.h>


/**
  Validates both Phy Address and Regster.

  @param [in]  PhyAddress
  @param [in]  PhyRegister

  @retval BOOLEAN   TRUE  Validation passed
                    FALSE If the data is not within its range

**/
BOOLEAN
IsPhyAddressRegisterValid (
  IN      UINT32  PhyAddress,
  IN      UINT32  PhyRegister
  )
{
  if (((PhyAddress & (~B_PHY_MDI_PHY_ADDRESS_MASK)) != 0) || ((PhyRegister & (~B_PHY_MDI_PHY_REGISTER_MASK)) != 0)) {
    DEBUG ((DEBUG_ERROR, "IsPhyAddressRegisterValid validation failed! PhyAddress: 0x%08X PhyRegister: 0x%08X \n", PhyAddress, PhyRegister));
    return FALSE;
  }
  return TRUE;
}

/**
  Change Extended Device Control Register BIT 11 to 1 which
  forces the interface between the MAC and the Phy to be on SMBus.
  Cleared on the assertion of PCI reset.

  @param [in]  GbeBar   GbE MMIO space

**/
VOID
GbeMdiForceMacToSmb (
  IN      UINT32  GbeBar
  )
{
  MmioOr32 (GbeBar + R_GBE_MEM_CSR_CTRL_EXT, B_GBE_MEM_CSR_CTRL_EXT_FORCE_SMB);
}

/**
  Test for MDIO operation complete.

  @param [in]  GbeBar   GbE MMIO space

  @retval EFI_SUCCESS
  @retval EFI_TIMEOUT
**/
EFI_STATUS
GbeMdiWaitReady (
  IN      UINT32  GbeBar
  )
{
  UINT32  Count;

  for (Count = 0; Count < GBE_MAX_LOOP_TIME; ++Count) {
    if (MmioRead32 (GbeBar + R_GBE_MEM_CSR_MDIC) & B_GBE_MEM_CSR_MDIC_RB) {
      return EFI_SUCCESS;
    }
    MicroSecondDelay (GBE_ACQUIRE_MDIO_DELAY);
  }
  DEBUG ((DEBUG_ERROR, "GbeMdiWaitReady Timeout reached. MDIO operation failed to complete in %d micro seconds\n", GBE_MAX_LOOP_TIME * GBE_ACQUIRE_MDIO_DELAY));
  return EFI_TIMEOUT;
}

/**
  Acquire MDIO software semaphore.

  1. Ensure that MBARA offset F00h [5] = 1b
  2. Poll MBARA offset F00h [5] up to 200ms

  @param [in] GbeBar   GbE MMIO space

  @retval EFI_SUCCESS
  @retval EFI_TIMEOUT
**/
EFI_STATUS
GbeMdiAcquireMdio (
  IN      UINT32  GbeBar
  )
{
  UINT32  ExtCnfCtrl;
  UINT32  Count;

  MmioOr32 (GbeBar + R_GBE_MEM_CSR_EXTCNF_CTRL, B_GBE_MEM_CSR_EXTCNF_CTRL_SWFLAG);
  for (Count = 0; Count < GBE_MAX_LOOP_TIME; ++Count) {
    ExtCnfCtrl = MmioRead32 (GbeBar + R_GBE_MEM_CSR_EXTCNF_CTRL);
    if (ExtCnfCtrl & B_GBE_MEM_CSR_EXTCNF_CTRL_SWFLAG) {
      return EFI_SUCCESS;
    }
    MicroSecondDelay (GBE_ACQUIRE_MDIO_DELAY);
  }
  DEBUG ((DEBUG_ERROR, "GbeMdiAcquireMdio Timeout. Unable to acquire MDIO Semaphore in %d micro seconds\n", GBE_MAX_LOOP_TIME * GBE_ACQUIRE_MDIO_DELAY));
  return EFI_TIMEOUT;
}

/**
  Release MDIO software semaphore by clearing MBARA offset F00h [5]

  @param [in]  GbeBar   GbE MMIO space
**/
VOID
GbeMdiReleaseMdio (
  IN      UINT32  GbeBar
  )
{
  ASSERT (MmioRead32 (GbeBar + R_GBE_MEM_CSR_EXTCNF_CTRL) & B_GBE_MEM_CSR_EXTCNF_CTRL_SWFLAG);
  MmioAnd32 (GbeBar + R_GBE_MEM_CSR_EXTCNF_CTRL, (UINT32) ~B_GBE_MEM_CSR_EXTCNF_CTRL_SWFLAG);
  ASSERT ((MmioRead32 (GbeBar + R_GBE_MEM_CSR_EXTCNF_CTRL) & B_GBE_MEM_CSR_EXTCNF_CTRL_SWFLAG) == 0);
}

/**
  Sets page on MDI
  Page setting is attempted twice.
  If first attempt failes MAC and the Phy are force to be on SMBus.

  Waits 4 mSec after page setting

  @param [in]  GbeBar  GbE MMIO space
  @param [in]  Data    Value to write in lower 16bits.

  @retval EFI_SUCCESS       Page setting was successfull
  @retval EFI_DEVICE_ERROR  Returned if both attermps of setting page failed
**/
EFI_STATUS
GbeMdiSetPage (
  IN      UINT32  GbeBar,
  IN      UINT32  Page
  )
{
  EFI_STATUS  Status;

  MmioWrite32 (GbeBar + R_GBE_MEM_CSR_MDIC, (~B_PHY_MDI_READY) & (B_PHY_MDI_WRITE | B_PHY_MDI_PHY_ADDRESS_01 | R_PHY_MDI_PHY_REG_SET_PAGE | ((Page * 32) & 0xFFFF)));

  Status = GbeMdiWaitReady (GbeBar);

  if (Status == EFI_TIMEOUT) {
    DEBUG ((DEBUG_INFO, "GbeMdiSetPage Timeout reached. Forcing the interface between the MAC and the Phy to be on SMBus\n"));
    GbeMdiForceMacToSmb (GbeBar);
    //
    // Retry page setting
    //
    MmioWrite32 (GbeBar + R_GBE_MEM_CSR_MDIC, (~B_PHY_MDI_READY) & (B_PHY_MDI_WRITE | B_PHY_MDI_PHY_ADDRESS_01 | R_PHY_MDI_PHY_REG_SET_PAGE | ((Page * 32) & 0xFFFF)));
    Status = GbeMdiWaitReady (GbeBar);
    if (Status == EFI_TIMEOUT) {
      DEBUG ((DEBUG_ERROR, "GbeMdiSetPage retry page setting failed!\n"));
      return EFI_DEVICE_ERROR;
    }
  }

  //
  // Delay required for page to set properly
  //
  MicroSecondDelay (GBE_MDI_SET_PAGE_DELAY);

  return Status;
}

/**
  Sets Register in current page.

  @param [in]  GbeBar      GbE MMIO space
  @param [in]  register    Register number valid only in lower 16 Bits

  @return EFI_STATUS
**/
EFI_STATUS
GbeMdiSetRegister (
  IN      UINT32  GbeBar,
  IN      UINT32  Register
  )
{
  MmioWrite32 (GbeBar + R_GBE_MEM_CSR_MDIC, (~B_PHY_MDI_READY) & (B_PHY_MDI_WRITE | B_PHY_MDI_PHY_ADDRESS_01 | R_PHY_MDI_PHY_REG_SET_ADDRESS | (Register & 0xFFFF)));
  return GbeMdiWaitReady (GbeBar);
}

/**
  Perform MDI write.

  @param [in]  GbeBar       GbE MMIO space
  @param [in]  PhyAddress   Phy Address General - 02 or Specific - 01
  @param [in]  PhyRegister  Phy Register
  @param [in]  WriteData    Value to write in lower 16bits.

  @retval EFI_SUCCESS            Based on response from GbeMdiWaitReady
  @retval EFI_TIMEOUT            Based on response from GbeMdiWaitReady
  @retval EFI_INVALID_PARAMETER  If Phy Address or Register validaton failed
**/
EFI_STATUS
GbeMdiWrite (
  IN      UINT32  GbeBar,
  IN      UINT32  PhyAddress,
  IN      UINT32  PhyRegister,
  IN      UINT32  WriteData
  )
{
  if(!IsPhyAddressRegisterValid (PhyAddress, PhyRegister)) {
    DEBUG ((DEBUG_ERROR, "GbeMdiWrite PhyAddressRegister validaton failed!\n"));
    return EFI_INVALID_PARAMETER;
  }

  MmioWrite32 (GbeBar + R_GBE_MEM_CSR_MDIC, (~B_PHY_MDI_READY) & (B_PHY_MDI_WRITE | PhyAddress | PhyRegister | (WriteData & 0xFFFF)));
  return GbeMdiWaitReady (GbeBar);
}

/**
  Perform MDI read.

  @param [in]  GbeBar       GbE MMIO space
  @param [in]  PhyAddress   Phy Address General - 02 or Specific - 01
  @param [in]  PhyRegister  Phy Register
  @param [out] ReadData     Return Value

  @retval EFI_SUCCESS            Based on response from GbeMdiWaitReady
  @retval EFI_TIMEOUT            Based on response from GbeMdiWaitReady
  @retval EFI_INVALID_PARAMETER  If Phy Address or Register validaton failed
**/
EFI_STATUS
GbeMdiRead (
  IN      UINT32  GbeBar,
  IN      UINT32  PhyAddress,
  IN      UINT32  PhyRegister,
  OUT     UINT16  *ReadData
  )
{
  EFI_STATUS    Status;

  if(!IsPhyAddressRegisterValid (PhyAddress, PhyRegister)) {
    DEBUG ((DEBUG_ERROR, "GbeMdiRead PhyAddressRegister validaton failed!\n"));
    return EFI_INVALID_PARAMETER;
  }

  MmioWrite32 (GbeBar + R_GBE_MEM_CSR_MDIC, (~B_PHY_MDI_READY) & (B_PHY_MDI_READ | PhyAddress | PhyRegister));
  Status = GbeMdiWaitReady (GbeBar);
  if (EFI_SUCCESS == Status) {
    *ReadData = (UINT16) MmioRead32 (GbeBar + R_GBE_MEM_CSR_MDIC);
  }
  return Status;
}

/**
  Gets Phy Revision and Model Number
  from PHY IDENTIFIER register 2 (offset 3)

  @param [in]  GbeBar           GbE MMIO space
  @param [out] LanPhyRevision   Return Value

  @return EFI_STATUS
  @return EFI_INVALID_PARAMETER When GbeBar is incorrect
                                When Phy register or address is out of bounds
**/
EFI_STATUS
GbeMdiGetLanPhyRevision (
  IN      UINT32  GbeBar,
  OUT     UINT16  *LanPhyRevision
  )
{
  EFI_STATUS    Status;

  if (!((GbeBar & 0xFFFFF000) > 0)) {
    DEBUG ((DEBUG_ERROR, "GbeMdiGetLanPhyRevision GbeBar validation failed! Bar: 0x%08X \n", GbeBar));
    return EFI_INVALID_PARAMETER;
  }

  Status = GbeMdiAcquireMdio (GbeBar);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "GbeMdiGetLanPhyRevision failed to aquire MDIO semaphore. Status: %r\n", Status));
    return Status;
  }

  Status = GbeMdiSetPage (GbeBar, PHY_MDI_PAGE_769_PORT_CONTROL_REGISTERS);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "GbeMdiGetLanPhyRevision failed to Set Page 769. Status: %r\n", Status));
    GbeMdiReleaseMdio (GbeBar);
    return Status;
  }

  //
  //  Set register to: Custom Mode Control
  //   Reduced MDIO frequency access (slow mdio)
  //   BIT 10 set to 1
  //
  Status = GbeMdiWrite (GbeBar, B_PHY_MDI_PHY_ADDRESS_01, MDI_REG_SHIFT (R_PHY_MDI_PAGE_769_REGISETER_16_CMC), BIT13 | B_PHY_MDI_PAGE_769_REGISETER_16_CMC_MDIO_FREQ_ACCESS | BIT8 | BIT7);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "GbeMdiGetLanPhyRevision failed to enable slow MDIO mode. Status: %r\n", Status));
    GbeMdiReleaseMdio (GbeBar);
    return Status;
  }

  //
  // Read register PHY Version from PHY IDENTIFIER 2 (offset 0x3)
  //  Bits [9:4]   - Device Model Number
  //  Bits [3:0]   - Device Revision Number
  //
  Status = GbeMdiRead (GbeBar, B_PHY_MDI_PHY_ADDRESS_02, R_PHY_MDI_GENEREAL_REGISTER_03_PHY_IDENTIFIER_2, LanPhyRevision);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "GbeMdiGetLanPhyRevision failed to read Revision and Model Number from PHY Identifier 2. Status: %r\n", Status));
    GbeMdiReleaseMdio (GbeBar);
    return Status;
  }

  //
  //  Switch back to normal MDIO frequency access
  //
  Status = GbeMdiWrite (GbeBar, B_PHY_MDI_PHY_ADDRESS_01,  MDI_REG_SHIFT (R_PHY_MDI_PAGE_769_REGISETER_16_CMC), (~B_PHY_MDI_PAGE_769_REGISETER_16_CMC_MDIO_FREQ_ACCESS) & (BIT13 | BIT8 | BIT7));
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "GbeMdiGetLanPhyRevision failed to disable slow MDIO mode. Status: %r\n", Status));
  }

  GbeMdiReleaseMdio (GbeBar);

  return Status;
}

