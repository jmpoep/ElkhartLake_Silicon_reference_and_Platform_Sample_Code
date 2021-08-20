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

    Name(ART1, Package()    // ART package when in Quiet Mode / Passive Cooling Mode
    {
      0, // Revision
      // Source                           Target                    Weight, AC0MaxLevel, AC1MaxLevel, AC21MaxLevel, AC31MaxLevel, AC41MaxLevel, AC51MaxLevel, AC61MaxLevel, AC71MaxLevel, AC81MaxLevel, AC91MaxLevel
#ifdef EC_SUPPORT
      Package(){\_SB.PC00.LPCB.H_EC.TFN1, \_SB.PC00.TCPU,           100,             80,          60,           40,           30,           20,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF},
      Package(){\_SB.PC00.LPCB.H_EC.TFN1, \_SB.PC00.LPCB.H_EC.SEN2, 100,             80,          60,           30,    0xFFFFFFFF,  0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF},
      Package(){\_SB.PC00.LPCB.H_EC.TFN1, \_SB.PC00.LPCB.H_EC.SEN3, 100,     0xFFFFFFFF,  0xFFFFFFFF,   0xFFFFFFFF,           80,           60,           30,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF},
      Package(){\_SB.PC00.LPCB.H_EC.TFN1, \_SB.PC00.LPCB.H_EC.SEN4, 100,             80,          60,           30,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF},
      Package(){\_SB.PC00.LPCB.H_EC.TFN1, \_SB.PC00.LPCB.H_EC.SEN5, 100,             80,          60,           30,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF},
#endif
#ifdef ECLITE_PSE_SUPPORT
      Package(){\_SB.TFN1, \_SB.PC00.TCPU,           100,             80,          60,           40,           30,           20,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF},
      Package(){\_SB.TFN1, \_SB.SEN2, 100,             80,          60,           30,    0xFFFFFFFF,  0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF},
      Package(){\_SB.TFN1, \_SB.SEN3, 100,     0xFFFFFFFF,  0xFFFFFFFF,   0xFFFFFFFF,           80,           60,           30,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF},
      Package(){\_SB.TFN1, \_SB.SEN4, 100,             80,          60,           30,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF},
      Package(){\_SB.TFN1, \_SB.SEN5, 100,             80,          60,           30,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF},
#endif //ECLITE_PSE_SUPPORT
    })

    Name(ART0, Package()    // ART package when in Performance Mode / Active Cooling Mode
    {
      0,    // Revision
      // Source                           Target                    Weight, AC0MaxLevel, AC1MaxLevel, AC21MaxLevel, AC31MaxLevel, AC41MaxLevel, AC51MaxLevel, AC61MaxLevel, AC71MaxLevel, AC81MaxLevel, AC91MaxLevel
#ifdef EC_SUPPORT
      Package(){\_SB.PC00.LPCB.H_EC.TFN1, \_SB.PC00.TCPU,           100,            100,          80,           50,           40,           30,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF},
      Package(){\_SB.PC00.LPCB.H_EC.TFN1, \_SB.PC00.LPCB.H_EC.SEN2, 100,             80,          50,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF},
      Package(){\_SB.PC00.LPCB.H_EC.TFN1, \_SB.PC00.LPCB.H_EC.SEN3, 100,     0xFFFFFFFF,  0xFFFFFFFF,   0xFFFFFFFF,          100,           80,           50,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF},
      Package(){\_SB.PC00.LPCB.H_EC.TFN1, \_SB.PC00.LPCB.H_EC.SEN4, 100,            100,          80,           50,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF},
      Package(){\_SB.PC00.LPCB.H_EC.TFN1, \_SB.PC00.LPCB.H_EC.SEN5, 100,            100,          80,           50,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF}
#endif
#ifdef ECLITE_PSE_SUPPORT
      Package(){\_SB.TFN1, \_SB.PC00.TCPU,           100,            100,          80,           50,           40,           30,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF},
      Package(){\_SB.TFN1, \_SB.SEN2, 100,             80,          50,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF},
      Package(){\_SB.TFN1, \_SB.SEN3, 100,     0xFFFFFFFF,  0xFFFFFFFF,   0xFFFFFFFF,          100,           80,           50,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF},
      Package(){\_SB.TFN1, \_SB.SEN4, 100,            100,          80,           50,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF},
      Package(){\_SB.TFN1, \_SB.SEN5, 100,            100,          80,           50,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF,   0xFFFFFFFF}
#endif //ECLITE_PSE_SUPPORT
    })

    // _ART (Active Cooling Relationship Table)
    //
    // Arguments:
    //   None
    // Return Value:
    //   A variable-length Package containing a Revision ID and a list of Active Relationship Packages as described below:
    //
    // Return Value Information
    //   Package {
    //   Revision, // Integer - Current revision is: 0
    //   ActiveRelationship[0] // Package
    //   ...
    //   ActiveRelationship[n] // Package
    //   }
    //
    Method(_ART,,,,PkgObj)
    {
#ifdef EC_SUPPORT
      If(\_SB.PC00.LPCB.H_EC.SEN3.CTYP)
      {
        Return(ART1)
      } Else {
        Return(ART0)
      }
#endif
#ifdef ECLITE_PSE_SUPPORT
      If(\_SB.SEN3.CTYP)
      {
        Return(ART1)
      } Else {
        Return(ART0)
      }
#endif //ECLITE_PSE_SUPPORT
    } // End _ART
}
