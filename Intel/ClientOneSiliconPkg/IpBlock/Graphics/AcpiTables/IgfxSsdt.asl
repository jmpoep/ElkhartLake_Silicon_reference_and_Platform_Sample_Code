/** @file
  This file contains the Intel Graphics SSDT Table ASL code.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2019 Intel Corporation.

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
  "IgfxSsdt.aml",
  "SSDT",
  2,
  "INTEL ",
  "IgfxSsdt",
  0x3000
  )
{
  External(\_SB.PC00, DeviceObj)
  External(\_SB.PC00.GFX0, DeviceObj)
  External(\NDID)
  External(\DID1)
  External(\DID2)
  External(\DID3)
  External(\DID4)
  External(\DID5)
  External(\DID6)
  External(\DID7)
  External(\DID8)
  External(\DID9)
  External(\DIDA)
  External(\DIDB)
  External(\DIDC)
  External(\DIDD)
  External(\DIDE)
  External(\DIDF)
  External(\DIDX)
  External(\DIDY)

  External(\NXD1)
  External(\NXD2)
  External(\NXD3)
  External(\NXD4)
  External(\NXD5)
  External(\NXD6)
  External(\NXD7)
  External(\NXD8)
  External(\NXDY)

  External(\IPTP)
  External(\EDPV)
  External(\NXDX)
  External(\HGMD)
  External(\LIDS)
  External(\BRTL)
  External(\NSTE)
  External(\CSTE)
  External(\ASLB)
  External(\IBTT)
  External(\IPSC)
  External(\IPAT)
  External(\IBIA)
  External(\IDMS)
  External(\HVCO)
  External(\ISSC)
  External(\KSV0)
  External(\KSV1)
  External(\IF1E)
  External(\PAVP)

  Scope (\_SB.PC00.GFX0)
  {
    include("Igfx.asl")
  }
}
