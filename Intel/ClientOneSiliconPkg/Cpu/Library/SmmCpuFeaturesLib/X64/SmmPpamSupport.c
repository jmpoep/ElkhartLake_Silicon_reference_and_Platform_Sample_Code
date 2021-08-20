/** @file
  SMM PPAM support functions

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

#include <PiSmm.h>
#include <Library/DebugLib.h>

#include "SmmPpam.h"

///
/// Page Table Entry
///
#define IA32_PG_P                   BIT0
#define IA32_PG_RW                  BIT1
#define IA32_PG_PS                  BIT7

/**

  Create 4G page table for STM.
  2M PAE page table in X64 version.

  @param PageTableBase        The page table base in MSEG

**/
VOID
PpamGen4GPageTable (
  IN UINTN              PageTableBase
  )
{
  UINTN                             Index;
  UINTN                             SubIndex;
  UINT64                            *Pde;
  UINT64                            *Pte;
  UINT64                            *Pml4;

  Pml4 = (UINT64*)(UINTN)PageTableBase;
  PageTableBase += SIZE_4KB;
  *Pml4 = PageTableBase | IA32_PG_RW | IA32_PG_P;

  Pde = (UINT64*)(UINTN)PageTableBase;
  PageTableBase += SIZE_4KB;
  Pte = (UINT64 *)(UINTN)PageTableBase;

  for (Index = 0; Index < 4; Index++) {
    *Pde = PageTableBase | IA32_PG_RW | IA32_PG_P;
    Pde++;
    PageTableBase += SIZE_4KB;

    for (SubIndex = 0; SubIndex < SIZE_4KB / sizeof (*Pte); SubIndex++) {
      *Pte = (((Index << 9) + SubIndex) << 21) | IA32_PG_PS | IA32_PG_RW | IA32_PG_P;
      Pte++;
    }
  }
}
