/**@file

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2016 Intel Corporation.

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


//
// _DSM : Device Specific Method supporting USB Sideband Deferring function
//
// Arg0: UUID Unique function identifier
// Arg1: Integer Revision Level
// Arg2: Integer Function Index
// Arg3: Package Parameters
//
Method (_DSM, 4, Serialized, 0, UnknownObj, {BuffObj, IntObj, IntObj, PkgObj})
{

  If (LEqual(Arg0, ToUUID ("A5FC708F-8775-4BA6-BD0C-BA90A1EC72F8")))
  {
    //
    // Switch by function index
    //
    Switch (ToInteger(Arg2))
    {
      //
      // Standard query - A bitmask of functions supported
      // Supports function 0-2
      //
      Case (0)
      {
        if (LEqual(Arg1, 1)){ // test Arg1 for the revision
          Return (Buffer () {0x07})
        } else {
          Return (Buffer () {0})
        }
      }
      //
      // USB Sideband Deferring Support
      //   0: USB Sideband Deferring not supported on this device
      //   1: USB Sideband Deferring supported
      //
      Case (1)
      {
        if (LEqual(SDGV,0xFF)){ // check for valid GPE vector
          Return (0)
        } else {
          Return (1)
        }
      }
      //
      // GPE Vector
      //  Return the bit offset within the GPE block of the GPIO (HOST_ALERT) driven by this device
      //
      Case (2)
      {
        Return (SDGV)
      }
    }
  }

  Return(Buffer() {0})
}
