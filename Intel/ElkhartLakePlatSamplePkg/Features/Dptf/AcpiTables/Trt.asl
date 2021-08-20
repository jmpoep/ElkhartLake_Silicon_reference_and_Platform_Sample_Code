/** @file
  Intel ACPI Reference Code for Intel Dynamic Power Performance Management

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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

   Name(TRT0, Package()    // TRT package when TFN1 is at 100% speed
   {
      // Source                           Target                    Influence  Period    Reserved
#ifdef EC_SUPPORT
      Package(){\_SB.PC00.TCPU,           \_SB.PC00.LPCB.H_EC.SEN2, 40,        100,      0, 0, 0, 0},
      Package(){\_SB.PC00.DPLY,           \_SB.PC00.LPCB.H_EC.SEN3, 30,        150,      0, 0, 0, 0},
      Package(){\_SB.PC00.LPCB.H_EC.CHRG, \_SB.PC00.LPCB.H_EC.SEN4, 20,        200,      0, 0, 0, 0}
#endif
#ifdef ECLITE_PSE_SUPPORT
      Package(){\_SB.PC00.TCPU,           \_SB.SEN2                 , 40,        100,      0, 0, 0, 0},
      Package(){\_SB.PC00.DPLY,           \_SB.SEN3                 , 30,        150,      0, 0, 0, 0},
      Package(){\_SB.CHRG,                \_SB.SEN4                 , 20,        200,      0, 0, 0, 0}
#endif //ECLITE_PSE_SUPPORT
    })

    // TRTR (Thermal Relationship Table Revision)
    //
    // This object evaluates to an integer value that defines the revision of the _TRT object.
    //
    // Arguments: (0)
    //   None
    // Return Value:
    // 0: Traditional TRT as defined by the ACPI Specification.
    // 1: Priority based TRT
    //
    Method(TRTR)
    {
      Return(\TRTV)
    }

    // _TRT (Thermal Relationship Table)
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   A variable-length Package containing a list of Thermal Relationship Packages as described below.
    //
    // Return Value Information
    //   Package {
    //   ThermalRelationship[0] // Package
    //    ...
    //   ThermalRelationship[n] // Package
    //   }
    //
    Method(_TRT,,,,PkgObj)
    {
      Return(TRT0)

    } // End _TRT
}
