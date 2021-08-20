/** @file
  This file contains the I/O port related functions.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2017 Intel Corporation.

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
#include "Io.h"

UINT8
IoRead8 (
  const UINT32 ioAddress
  )
/*++

Routine Description:

  read 8 bits Io port.

Arguments:

  ioAddress - Address to read.

Returns:

  N/A

--*/
{
   ASM {
      mov   edx, ioAddress
      in    al, dx
   }
}

UINT16
IoRead16 (
  const UINT32 ioAddress
  )
/*++

Routine Description:

  Read 16-bit I/O port.

Arguments:

  ioAddress - I/O port address to read.

Returns:

  16-bit data from the port.

--*/

{
   ASM {
      mov   edx, ioAddress
      in    ax, dx
   }
}

UINT32
IoRead32 (
  const UINT32 ioAddress
  )
/*++

Routine Description:

  read 32 bits Io port.

Arguments:

  ioAddress - Address to read.

Returns:

  N/A

--*/

{
   ASM {
      mov   edx, ioAddress
      in    eax, dx
   }
}

void
IoWrite32 (
  const UINT32 ioAddress,
  const UINT32 data
  )
/*++

Routine Description:

  write 32 bits Io port.

Arguments:

  ioAddress - Address to read.
  data      - data to write.

Returns:

  N/A

--*/
{
   ASM {
      mov   edx, ioAddress
      mov   eax, data
      out   dx, eax
   }
}

void
IoWrite16 (
  const UINT32 ioAddress,
  const UINT16 data
  )
/*++

Routine Description:

  Write 16-bit I/O port.

Arguments:

  ioAddress - I/O port address.
  data      - data to write.

Returns:

  N/A

--*/
{
   ASM {
      mov   edx, ioAddress
      mov   ax, data
      out   dx, ax
   }
}

void
IoWrite8 (
  const UINT32 ioAddress,
  const UINT8  data
  )
/*++

Routine Description:

  write 8 bits Io port.

Arguments:

  ioAddress - Address to read.
  data      - data to write.

Returns:

  N/A

--*/
{
   ASM {
      mov   edx, ioAddress
      mov   al, data
      out   dx, al
   }
}
