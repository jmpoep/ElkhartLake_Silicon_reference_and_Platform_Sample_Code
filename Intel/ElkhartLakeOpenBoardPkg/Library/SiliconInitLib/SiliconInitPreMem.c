/** @file
  Source code file for Silicon Init Pre-Memory PEI module

Copyright (c) 2017 - 2018, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <PiPei.h>

#include <Library/BaseLib.h>
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PostCodeLib.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PeiServicesLib.h>
#include <Register/PchRegsLpc.h>
#include <Register/PchRegs.h>

/**
  Early Platform PCH initialization
**/
VOID
EarlySiliconInit (
  VOID
  )
{
  UINT16                            LpcIoe;
  UINT16                            LpcIoeOrg;
  UINT64                            LpcBaseAddress;

  ///
  /// LPC I/O Configuration
  ///
  PchLpcIoDecodeRangesSet (
    (V_LPC_CFG_IOD_LPT_378  << N_LPC_CFG_IOD_LPT)  |
    (V_LPC_CFG_IOD_COMB_3E8 << N_LPC_CFG_IOD_COMB) |
    (V_LPC_CFG_IOD_COMA_3F8 << N_LPC_CFG_IOD_COMA)
    );

  PchLpcIoEnableDecodingSet (
    B_LPC_CFG_IOE_ME2  |
    B_LPC_CFG_IOE_SE   |
    B_LPC_CFG_IOE_ME1  |
    B_LPC_CFG_IOE_KE   |
    B_LPC_CFG_IOE_HGE  |
    B_LPC_CFG_IOE_LGE  |
    B_LPC_CFG_IOE_FDE  |
    B_LPC_CFG_IOE_PPE  |
    B_LPC_CFG_IOE_CBE  |
    B_LPC_CFG_IOE_CAE
    );

  ///
  /// Enable LPC IO decode for EC access
  ///
  LpcBaseAddress = PCI_SEGMENT_LIB_ADDRESS (
                     DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                     DEFAULT_PCI_BUS_NUMBER_PCH,
                     PCI_DEVICE_NUMBER_PCH_LPC,
                     PCI_FUNCTION_NUMBER_PCH_LPC,
                     0
                     );
  LpcIoeOrg = PciSegmentRead16 (LpcBaseAddress + R_LPC_CFG_IOE);
  LpcIoe = LpcIoeOrg | B_LPC_CFG_IOE_ME1;
#if FixedPcdGet8(PcdEmbeddedEnable) == 1
  // Enable LPC IO decode for SIO (0x2e) access.
  LpcIoe = LpcIoeOrg | B_LPC_CFG_IOE_SE;
  LpcIoeOrg |= B_LPC_CFG_IOE_SE;
#endif

  PchLpcIoEnableDecodingSet (LpcIoe);
  // if EC not presetn PchLpcIoEnableDecodingSet (LpcIoeOrg);

}

// @todo: It should be moved Policy Init.
/**
  Initialize the GPIO IO selection, GPIO USE selection, and GPIO signal inversion registers

**/
VOID
SiliconInit (
  VOID
  )
{
}

