/** @file
  CPU Security PreMemory Config Block.

@copyright
  INTEL CONFIDENTIAL
  Copyright (c) 2015 - 2020 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by the
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.
  This file contains an 'Intel Peripheral Driver' and is uniquely
  identified as "Intel Reference Module" and is licensed for Intel
  CPUs and chipsets under the terms of your license agreement with
  Intel or your vendor. This file may be modified by the user, subject
  to additional terms of the license agreement.

@par Specification Reference:
**/
#ifndef _CPU_CONFIG_LIB_PREMEM_CONFIG_H_
#define _CPU_CONFIG_LIB_PREMEM_CONFIG_H_

#define CPU_CONFIG_LIB_PREMEM_CONFIG_REVISION 2

extern EFI_GUID gCpuConfigLibPreMemConfigGuid;

#pragma pack (push,1)

/**
  CPU Config Library PreMemory Configuration Structure.

  <b>Revision 1</b>:
  - Initial version.
  <b>Revision 2</b>:
  - Expand the supported number of processor cores (ActiveCoreCount1).
**/
typedef struct {
  CONFIG_BLOCK_HEADER Header;            ///< Config Block Header
  UINT32 HyperThreading             : 1; ///< Enable or Disable Hyper Threading; 0: Disable; <b>1: Enable</b>.
  /**
  Sets the boot frequency starting from reset vector.
   - 0: Maximum battery performance.
   - <b>1: Maximum non-turbo performance</b>.
   - 2: Turbo performance.
  @note If Turbo is selected BIOS will start in max non-turbo mode and switch to Turbo mode.
  **/
  UINT32 BootFrequency              : 2;
  /**
    Number of processor cores to enable.
    - <b> 0: All cores</b>
    -     1: 1 core
    -     2: 2 cores
    -     3: 3 cores
  **/
  UINT32 ActiveCoreCount            : 3; ///< @deprecated due to core active number limitaion.
  UINT32 JtagC10PowerGateDisable    : 1; ///< False: JTAG is power gated in C10 state. True: keeps the JTAG power up during C10 and deeper power states for debug purpose. <b>0: False<\b>; 1: True.
  UINT32 BistOnReset                : 1; ///< <b>(Test)</b> Enable or Disable BIST on Reset; <b>0: Disable</b>; 1: Enable.
  /**
    Enable or Disable Virtual Machine Extensions (VMX) feature.
    -    0: Disable
    - <b>1: Enable</b>
  **/
  UINT32 VmxEnable                  : 1;
  /**
  Processor Early Power On Configuration FCLK setting.
   - <b>0: 800 MHz (ULT/ULX)</b>.
   - <b>1: 1 GHz (DT/Halo)</b>. Not supported on ULT/ULX.
   - 2: 400 MHz.
   - 3: Reserved.
  **/
  UINT32 FClkFrequency              : 2;
  /**
    Enable or Disable Total Memory Encryption (TME) feature.
    - <b>0: Disable</b>
    -    1: Enable
  **/
  UINT32 TmeEnable                  : 1;
  UINT32 DebugInterfaceEnable       : 2; ///< Enable or Disable processor debug features; 0: Disable; 1: Enable; <b>2: No Change</b>.
  UINT32 DebugInterfaceLockEnable   : 1; ///< Lock or Unlock debug interface features; 0: Disable; <b>1: Enable</b>.

  /**
    Number of processor cores to enable. And support up to 16 cores.
    - <b> 0: All cores</b>
    -     1: 1 core
    -     2: 2 cores
    -     3: 3 cores
  **/
  UINT32 ActiveCoreCount1           : 4;
  UINT32 RsvdBits                   : 13;

  /**
    CpuRatio - Max non-turbo ratio (Flexible Ratio Boot) is set to CpuRatio. <b>0: Disabled</b> If disabled, doesn't override max-non turbo ratio.
  **/
  UINT8  CpuRatio;
  UINT8  Reserved[3];                    ///< Reserved for alignment
  UINT32 ElixirSpringsPatchAddr;         ///< Address of Elixir Springs Patch(es)
  UINT32 ElixirSpringsPatchSize;         ///< Elixir Springs Patch(es) Size.
} CPU_CONFIG_LIB_PREMEM_CONFIG;

#pragma pack (pop)

#endif // _CPU_CONFIG_LIB_PREMEM_CONFIG_H_
