/** @file
  This file contains the Intel Turbo Boost Max Technology 3.0 ASL SCI handler.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2017 Intel Corporation.

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
  "ItbmSci.aml",
  "SSDT",
  0x02,
  "PmRef",
  "ItbmSci",
  0x3000
  )
{
External(\_SB.PR00, DeviceObj)
External(\_SB.PR01, ProcessorObj)
External(\_SB.PR02, ProcessorObj)
External(\_SB.PR03, ProcessorObj)
External(\_SB.PR04, ProcessorObj)
External(\_SB.PR05, ProcessorObj)
External(\_SB.PR06, ProcessorObj)
External(\_SB.PR07, ProcessorObj)
External(\_SB.PR08, ProcessorObj)
External(\_SB.PR09, ProcessorObj)
External(\_SB.PR10, ProcessorObj)
External(\_SB.PR11, ProcessorObj)
External(\_SB.PR12, ProcessorObj)
External(\_SB.PR13, ProcessorObj)
External(\_SB.PR14, ProcessorObj)
External(\_SB.PR15, ProcessorObj)
External(\TCNT, FieldUnitObj)

Scope (\_GPE)
{
  //
  // ITBH: Intel Turbo Boost Max Technology 3.0 Handler for SCI _L62
  //

  Method(ITBH, 0, Serialized)
  {
    Switch (ToInteger(TCNT)) {
      Case(16) {
        Notify(\_SB.PR00, 0x85)
        Notify(\_SB.PR01, 0x85)
        Notify(\_SB.PR02, 0x85)
        Notify(\_SB.PR03, 0x85)
        Notify(\_SB.PR04, 0x85)
        Notify(\_SB.PR05, 0x85)
        Notify(\_SB.PR06, 0x85)
        Notify(\_SB.PR07, 0x85)
        Notify(\_SB.PR08, 0x85)
        Notify(\_SB.PR09, 0x85)
        Notify(\_SB.PR10, 0x85)
        Notify(\_SB.PR11, 0x85)
        Notify(\_SB.PR12, 0x85)
        Notify(\_SB.PR13, 0x85)
        Notify(\_SB.PR14, 0x85)
        Notify(\_SB.PR15, 0x85)
      }
      Case(14) {
        Notify(\_SB.PR00, 0x85)
        Notify(\_SB.PR01, 0x85)
        Notify(\_SB.PR02, 0x85)
        Notify(\_SB.PR03, 0x85)
        Notify(\_SB.PR04, 0x85)
        Notify(\_SB.PR05, 0x85)
        Notify(\_SB.PR06, 0x85)
        Notify(\_SB.PR07, 0x85)
        Notify(\_SB.PR08, 0x85)
        Notify(\_SB.PR09, 0x85)
        Notify(\_SB.PR10, 0x85)
        Notify(\_SB.PR11, 0x85)
        Notify(\_SB.PR12, 0x85)
        Notify(\_SB.PR13, 0x85)
      }
      Case(12) {
        Notify(\_SB.PR00, 0x85)
        Notify(\_SB.PR01, 0x85)
        Notify(\_SB.PR02, 0x85)
        Notify(\_SB.PR03, 0x85)
        Notify(\_SB.PR04, 0x85)
        Notify(\_SB.PR05, 0x85)
        Notify(\_SB.PR06, 0x85)
        Notify(\_SB.PR07, 0x85)
        Notify(\_SB.PR08, 0x85)
        Notify(\_SB.PR09, 0x85)
        Notify(\_SB.PR10, 0x85)
        Notify(\_SB.PR11, 0x85)
      }
      Case(10) {
        Notify(\_SB.PR00, 0x85)
        Notify(\_SB.PR01, 0x85)
        Notify(\_SB.PR02, 0x85)
        Notify(\_SB.PR03, 0x85)
        Notify(\_SB.PR04, 0x85)
        Notify(\_SB.PR05, 0x85)
        Notify(\_SB.PR06, 0x85)
        Notify(\_SB.PR07, 0x85)
        Notify(\_SB.PR08, 0x85)
        Notify(\_SB.PR09, 0x85)
      }
      Case(8) {
        Notify(\_SB.PR00, 0x85)
        Notify(\_SB.PR01, 0x85)
        Notify(\_SB.PR02, 0x85)
        Notify(\_SB.PR03, 0x85)
        Notify(\_SB.PR04, 0x85)
        Notify(\_SB.PR05, 0x85)
        Notify(\_SB.PR06, 0x85)
        Notify(\_SB.PR07, 0x85)
      }
      Case(7) {
        Notify(\_SB.PR00, 0x85)
        Notify(\_SB.PR01, 0x85)
        Notify(\_SB.PR02, 0x85)
        Notify(\_SB.PR03, 0x85)
        Notify(\_SB.PR04, 0x85)
        Notify(\_SB.PR05, 0x85)
        Notify(\_SB.PR06, 0x85)
      }
      Case(6) {
        Notify(\_SB.PR00, 0x85)
        Notify(\_SB.PR01, 0x85)
        Notify(\_SB.PR02, 0x85)
        Notify(\_SB.PR03, 0x85)
        Notify(\_SB.PR04, 0x85)
        Notify(\_SB.PR05, 0x85)
      }
      Case(5) {
        Notify(\_SB.PR00, 0x85)
        Notify(\_SB.PR01, 0x85)
        Notify(\_SB.PR02, 0x85)
        Notify(\_SB.PR03, 0x85)
        Notify(\_SB.PR04, 0x85)
      }
      Case(4) {
        Notify(\_SB.PR00, 0x85)
        Notify(\_SB.PR01, 0x85)
        Notify(\_SB.PR02, 0x85)
        Notify(\_SB.PR03, 0x85)
      }
      Case(3) {
        Notify(\_SB.PR00, 0x85)
        Notify(\_SB.PR01, 0x85)
        Notify(\_SB.PR02, 0x85)
      }
      Case(2) {
        Notify(\_SB.PR00, 0x85)
        Notify(\_SB.PR01, 0x85)
      }
      Default {
        Notify(\_SB.PR00, 0x85)
      }
    }
  }

} // end of Scope (\_GPE)
} // end of definition block