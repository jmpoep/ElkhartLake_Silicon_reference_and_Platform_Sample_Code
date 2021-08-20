/** @file
  Intel ACPI Reference Code for Intel Dynamic Power Performance Management

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2018 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

Scope(\_SB.IETM)
{

  // PTTL (Participant Temperature Tolerance Level)
  // This object evaluates to an integer representing the temperature range within which any change
  // in participant temperature is considered acceptable and no policy actions will be taken by the
  // policy. The temperature tolerance level is expressed in the units of 10s of Kelvin.
  //
  Name (PTTL, 20) // ToleranceLevel

  Name (PSV2, Package()
  {
    2,
#ifdef EC_SUPPORT
    Package(){\_SB.PC00.TCPU, \_SB.PC00.LPCB.H_EC.SEN5, 2, 300, 3732, 9, 0x00010000, 7000, 250, 10, 10, 0}
#endif
#ifdef ECLITE_PSE_SUPPORT
    Package(){\_SB.PC00.TCPU, \_SB.SEN5, 2, 300, 3732, 9, 0x00010000, 7000, 250, 10, 10, 0}
#endif //ECLITE_PSE_SUPPORT
  })

  // Used by passive policy 2.0
  //
  //  Name (PSVT, Package()
  //  {
  //    0x80000000,     // Revision: 1 = true proportional limit, 2 = depth limit
  //    Package() {
  //      "Source",     // Source device: String
  //      "Target",     // Target device: String
  //      0x80000000,   // Priority: for use by passive policy 2.0
  //      0x80000000,   // Sampling Period: in 1/10 of seconds unit
  //      0x80000000,   // Passive Temp: Threshold(1/10 of K) at which Passive Policy 2.0 will take action
  //      0x80000000,   // Domain: type under the source that is controlled
  //      0x80000000,   // Control Knob: type of control knob that need to be exercised
  //      0x80000000,   // Control Value: Depth Limit or Target State which policy will jump to on a thermal condition(based on revision).
  //      0x80000000,   // Step size for this specific control knob
  //      0x80000000,   // Limit Coefficient: 1/10 of units, used with StepSize to control limiting action
  //      0x80000000,   // UnLimit Coefficient: 1/10 of units, used with StepSize to control unlimiting action
  //      0x80000000    // Reserved1
  //    }
  //  })
  Method(PSVT,,,,PkgObj)
  {
    Return(PSV2) // default
  }

} // end Scope(\_SB.IETM)
