/**@file
 SoundWire Devices ACPI

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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

//
// SoundWire Devices definition
//
// Address (_ADR) encoding:
// Bits [63:52] - Reserved (0)
// Bits [51:48]  - Link ID
// Zero-based SoundWire Link number. For single-link controllers, this value shall be 0x0
// Bits [47:0]  - Device ID
// DeviceID Encoding as described in the SoundWire 1.0 specification, Table 80
// For example:
// SNDW.SWD0 (ALC701 on Link#0): _ADR(0x000010025d070100) - LinkID[51:48] = 0, DevID[47:0]: 0x10025D070100
// SNDW.SWD6 (ALC700 on Link#2): _ADR(0x000210025d070000) - LinkID[51:48] = 2, DevID[47:0]: 0x10025D070000
//

#define N_HDA_SNDW_LINK_ID   48
#define V_HDA_SNDW_LINK_ID_0 (0x0000 << N_HDA_SNDW_LINK_ID)
#define V_HDA_SNDW_LINK_ID_1 (0x0001 << N_HDA_SNDW_LINK_ID)
#define V_HDA_SNDW_LINK_ID_2 (0x0002 << N_HDA_SNDW_LINK_ID)
#define V_HDA_SNDW_LINK_ID_3 (0x0003 << N_HDA_SNDW_LINK_ID)

#define V_HDA_SNDW_DID_REALTEK_ALC700 0x10025D070000
#define V_HDA_SNDW_DID_REALTEK_ALC701 0x10025D070100

// SoundWire Controller Scope
Scope(\_SB.PC00.HDAS.SNDW)
{
  // SoundWire Device 0..M

  // SoundWire Device #0 on Controller #0 (Realtek ALC701)
  // _ADR: 0x000010025d070100
  Device(SWD0)
  {
    Name (_ADR, (V_HDA_SNDW_LINK_ID_0 | V_HDA_SNDW_DID_REALTEK_ALC701))
    Include ("HdaSoundWireCodec.asl")
  }

  // SoundWire Device #1 on Controller #1 (Realtek ALC701)
  // _ADR: 0x000110025d070100
  Device(SWD1)
  {
    Name (_ADR, (V_HDA_SNDW_LINK_ID_1 | V_HDA_SNDW_DID_REALTEK_ALC701))
    Include ("HdaSoundWireCodec.asl")
  }

  // SoundWire Device #2 on Controller #2 (Realtek ALC701)
  // _ADR: 0x000210025d070100
  Device(SWD2)
  {
    Name (_ADR, (V_HDA_SNDW_LINK_ID_2 | V_HDA_SNDW_DID_REALTEK_ALC701))
    Include ("HdaSoundWireCodec.asl")
  }

  // SoundWire Device #3 on Controller #3 (Realtek ALC701)
  // _ADR: 0x000310025d070100
  Device(SWD3)
  {
    Name (_ADR, (V_HDA_SNDW_LINK_ID_3 | V_HDA_SNDW_DID_REALTEK_ALC701))
    Include ("HdaSoundWireCodec.asl")
  }

  // SoundWire Device #4 on Controller #0 (Realtek ALC700)
  // _ADR: 0x000010025d070000
  Device(SWD4)
  {
    Name (_ADR, (V_HDA_SNDW_LINK_ID_0 | V_HDA_SNDW_DID_REALTEK_ALC700))
    Include ("HdaSoundWireCodec.asl")
  }

  // SoundWire Device #5 on Controller #1 (Realtek ALC700)
  // _ADR: 0x000110025d070000
  Device(SWD5)
  {
    Name (_ADR, (V_HDA_SNDW_LINK_ID_1 | V_HDA_SNDW_DID_REALTEK_ALC700))
    Include ("HdaSoundWireCodec.asl")
  }

  // SoundWire Device #6 on Controller #2 (Realtek ALC700)
  // _ADR: 0x000210025d070000
  Device(SWD6)
  {
    Name (_ADR, (V_HDA_SNDW_LINK_ID_2 | V_HDA_SNDW_DID_REALTEK_ALC700))
    Include ("HdaSoundWireCodec.asl")
  }

  // SoundWire Device #7 on Controller #3 (Realtek ALC700)
  // _ADR: 0x000310025d070000
  Device(SWD7)
  {
    Name (_ADR, (V_HDA_SNDW_LINK_ID_3 | V_HDA_SNDW_DID_REALTEK_ALC700))
    Include ("HdaSoundWireCodec.asl")
  }

} // END SCOPE SNDW
