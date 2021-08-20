/** @file
  Intel Processor Power Management ACPI Code.

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

#include "CpuPowerMgmt.h"

DefinitionBlock (
  "CPU0PSD.aml",
  "SSDT",
  0x02,
  "PmRef",
  "Cpu0Psd",
  0x3000
  )
{
  External(\PF00, IntObj)
  External(\TCNT, FieldUnitObj)
  External(\_SB.CFGD, IntObj)
  External(\_SB.PR00, DeviceObj)

  Scope(\_SB.PR00)
  {
    Name(HPSD,Package() // HW_ALL
    {
      Package() {5,    // NumEntries. Current Value is 5.
                 0,    // Revision. Current Value is 0.
                 0,    // Domain.
                 0xFE, // Coordination type 0xFE = HW_ALL
                 0x80  // Number of processors.
      }
    })

    Name(SPSD,Package() // SW_ALL
    {
      Package() {5,    // NumEntries. Current Value is 5.
                 0,    // Revision. Current Value is 0.
                 0,    // Domain.
                 0xFC, // Coordination type 0xFC = SW_ALL
                 0x80  // Number of processors.
      }
    })

    //
    // The _PSD object provides information to the OSPM related
    // to P-State coordination between processors in a multi-processor
    // configurations.
    //
    Method(_PSD,0)
    {
      If (And(\_SB.CFGD, PPM_TURBO_BOOST_MAX)) // Intel Turbo Boost Max 3.0
      {
        Store (0, Index(DerefOf(Index(HPSD, 0)),2)) // Domain
        Store (1, Index(DerefOf(Index(HPSD, 0)),4)) // Number of processors belonging to the domain.
      } Else {
        Store (TCNT, Index(DerefOf(Index(HPSD, 0)),4))
        Store (TCNT, Index(DerefOf(Index(SPSD, 0)),4))
      }
      If(And(PF00,0x0800)) // If Hardware co-ordination of P states
      {
        Return(HPSD)
      }
      Return(SPSD)
    }
  } // End of Scope(\_SB.PR00)
} // End of Definition Block

