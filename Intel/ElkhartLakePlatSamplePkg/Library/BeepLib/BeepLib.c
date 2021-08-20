/** @file
  Beep Library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2016 Intel Corporation.

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

#include <Base.h>
#include <Library/BeepLib.h>
#include <Library/IoLib.h>
#include <Library/TimerLib.h>

#define NOTE(x) ((119318200 + (x) / 2) / (x))

//
// beep tones
//
GLOBAL_REMOVE_IF_UNREFERENCED UINT16  mBeepTones[8] = {
    NOTE (26163),
    NOTE (29366),
    NOTE (32963),
    NOTE (34923),
    NOTE (39200),
    NOTE (44000),
    NOTE (49388),
    NOTE (26163 * 2)
};


/**
  Switch on Beep.

  @param[in]  Note         The note of beep.
  @param[in]  Octave       The octave of beep.
**/
VOID
BeepOn (
  IN UINT8 Note,
  IN UINT8 Octave
  )
{
  UINT16  Frequency;

  Frequency = mBeepTones[(Note % 8)];

  if (Octave - 1 >= 0) {
    Frequency >>= Octave - 1;
  } else {
    Frequency <<= 1 - Octave;
  }

  //
  // set up channel 2 (used by speaker)
  //
  IoWrite8 (0x43, 0xb6);
  IoWrite8 (0x42, (UINT8) Frequency);
  IoWrite8 (0x42, (UINT8) (Frequency >> 8));
  //
  // turn the speaker on
  //
  IoWrite8 (0x61, IoRead8 (0x61) | 3);
}


/**
  Switch off Beep.

**/
VOID
BeepOff (
  VOID
  )
{
  IoWrite8 (0x61, IoRead8 (0x61) & 0xfc);
}


/**
  Produces Beep.

  @param[in]  Note         The note of beep.
  @param[in]  Octave       The octave of beep.
  @param[in]  Duration     The duration of beep.
**/
VOID
SendBeep (
  IN UINT8            Note,
  IN UINT8            Octave,
  IN UINT32           Duration
  )
{
  BeepOn (Note, Octave);
  MicroSecondDelay (Duration);
  BeepOff ();
}


/**
  Sends a 32-bit value to Beep device.

  Sends the 32-bit value specified by Value to Beep device, and returns Value.
  Some implementations of this library function may perform I/O operations
  directly to Beep device.  Other implementations may send Value to
  ReportStatusCode(), and the status code reporting mechanism will eventually
  display the 32-bit value on the status reporting device.

  Beep() must actively prevent recursion.  If Beep() is called while
  processing another Post Code Library function, then
  Beep() must return Value immediately.

  @param  Value  Beep count.
**/
VOID
EFIAPI
Beep (
  IN UINT32  Value
  )
{
  UINTN  Index;

  for (Index = 0; Index < Value; Index++) {
    SendBeep (1, 2, 400000);
    MicroSecondDelay (100000);
  }

  return ;
}
