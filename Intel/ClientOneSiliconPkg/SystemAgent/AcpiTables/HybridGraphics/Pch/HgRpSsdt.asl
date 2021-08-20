/** @file
  This file contains the system BIOS Hybrid graphics code for
  ULT.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2018 Intel Corporation.

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

DefinitionBlock (
    "HgRpSsdt.aml",
    "SSDT",
    2,
    "HgRef",
    "HgRpSsdt",
    0x1000
    )
{
External(OSYS)
External(RPIN)
External(GPRW, MethodObj)
External(\_SB.PC00.RP05, DeviceObj)
External(\_SB.PC00.RP01, DeviceObj)
External(P8XH, MethodObj)
External(\_SB.PC00, DeviceObj)
External(\_SB.SGOV, MethodObj)
External(\_SB.GGOV, MethodObj)
External(\RPA5)
External(\RPBA)
External(\EECP)
External(\XBAS)
External(\GBAS)
External(HGMD)
External(\SGGP)
External(\DLPW)
External(\DLHR)
External(\HRE0)
External(\HRG0)
External(\HRA0)
External(\PWE0)
External(\PWG0)
External(\PWA0)


Scope(\_SB.PC00)
{
  If(LEqual(RPIN,0)) {
    Scope(\_SB.PC00.RP01)
    {
      Include("HgRpCommon.asl")
    }

    Scope(\_SB.PC00.RP01.PEGP)
    {

      Method (_INI)
      {
          Store (0x0, \_SB.PC00.RP01.PEGP._ADR)
      }

      Method(_ON,0,Serialized)
      {
        \_SB.PC00.HGON()

        //Ask OS to do a PnP rescan
        Notify(\_SB.PC00.RP01,0)

        Return ()
      }

      Method(_OFF,0,Serialized)
      {
        \_SB.PC00.HGOF()

        //Ask OS to do a PnP rescan
        Notify(\_SB.PC00.RP01,0)

        Return ()
      }
    }
  }

  ElseIf(LEqual(RPIN,4)) {

    Scope(\_SB.PC00.RP05)
    {
      Include("HgRpCommon.asl")
    }

    Scope(\_SB.PC00.RP05.PEGP)
    {

      Method (_INI)
      {
          Store (0x0, \_SB.PC00.RP05.PEGP._ADR)
      }

      Method(_ON,0,Serialized)
      {
        \_SB.PC00.HGON()

        //Ask OS to do a PnP rescan
        Notify(\_SB.PC00.RP05,0)

        Return ()
      }

      Method(_OFF,0,Serialized)
      {
        \_SB.PC00.HGOF()

        //Ask OS to do a PnP rescan
        Notify(\_SB.PC00.RP05,0)

        Return ()
      }
    }
  }
  Include("HgDgpuPch.asl")

}// End of Scope(\_SB.PC00)
}// End of Definition Block
