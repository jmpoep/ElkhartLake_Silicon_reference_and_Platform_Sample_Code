/** @file
  Platform Hook Library instance for SandyBridge Mobile/Desktop CRB.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2018 Intel Corporation.

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

@par Specification
**/

#include "PlatformInitLib.h"
#include <Library/PchCycleDecodingLib.h>

#define EFI_MSR_IA32_PLATFORM_ID                  0x17
#define COM1_BASE                                 0x3f8
#define COM1_BASE                                 0x3f8
#define COM2_BASE                                 0x2f8
#define SIO_DOCKING_LPC_SWITCH_REGISTER_ADDRESS   0x0690

#define LPC_SIO_INDEX_DEFAULT_PORT_2              0x2E
#define LPC_SIO_DATA_DEFAULT_PORT_2               0x2F
#define LPC_SIO_GPIO_REGISTER_ADDRESS_2           0x0A20

#define MOBILE_LPC_CARD_SIO_CONFIG_DEFAULT_PORT   0x164E
#define MOBILE_LPC_CARD_SIO_INDEX_DEFAULT_PORT    0x164E
#define MOBILE_LPC_CARD_SIO_DATA_DEFAULT_PORT     0x164F

#define LEGACY_DAUGHTER_CARD_SIO_INDEX_PORT       0x2E
#define LEGACY_DAUGHTER_CARD_SIO_DATA_PORT        0x2F
#define LEGACY_DAUGHTER_CARD_2_SIO_INDEX_PORT     0x4E
#define LEGACY_DAUGHTER_CARD_2_SIO_DATA_PORT      0x4F

#define CHECKNCT6776_LOOP_COUNT                   2000

typedef struct {
  UINT8 Register;
  UINT8 Value;
} EFI_SIO_TABLE;

#if FixedPcdGetBool(PcdNct677FPresent) == 1
//
// This table is specifically tailored for the Lava Canyon board. It'll
// enable UART A to COM1, disable LPT, UART B and PS2.
//
EFI_SIO_TABLE mSioTableNct6776f[] = {
  // Initialize pin selection for pins in GPIO8 group to COM A functionality.
  {0x2A, 0x40},

  // Initialize COM A itself. These are the default values, but they could
  // have changed from a previous boot.
  {0x07, 0x02},                   // Select UART0
  {0x60, 0x03},                   // Program HI base addr (0x03f8)
  {0x61, 0xf8},                   // Program LO base addr
  {0x70, 0x04},                   // Program interrupt (IRQ 4)
  {0x30, 0x01},                   // Activate Device

  // Early disable of unused devices.
  {0x07, 0x01},                   // disable device 01 (LPT).
  {0x30, 0x00},

  {0x07, 0x03},                   // disable device 03 (UART B).
  {0x30, 0x00},

  {0x07, 0x05},                   // disable device 05 (PS2).
  {0x30, 0x00},
};

STATIC
VOID
CheckNct6776fSio (
  VOID
  )
/*++
Routine Description:
  Detect if a Nuvoton NCT6776F is present. If detected, set COM A to 0x3f8,
  IRQ 4, enable it and disable any unused device (early disable). This code
  assumes that LPC is already programmed to enable adresses 0x2e-0x2f and
  0x03f8-0x03ff (SIO and COM1 IO addresses).

Arguments:
  None.

Returns:
  None.
--*/
{
  UINT16  Index;
  UINT8   SioId[2] = {0};
  UINT8   Value;
  UINT32  Loop;

  Loop = 0;

  do {
    //
    // Try to open SIO configuration space by writing 0x87 twice to port 0x2e.
    //
    IoWrite8 (0x2e, 0x87);
    IoWrite8 (0x2e, 0x87);

    //
    // Read SioID (registers 0x20 and 0x21 upper nibble)
    //
    IoWrite8 (0x2e, 0x20);
    SioId[0] = IoRead8 (0x2f);

    IoWrite8 (0x2e, 0x21);
    SioId[1] = 0xf0 & IoRead8 (0x2f);

    //
    // Now verify if there's a match with NCT6776F id.
    //

    //
    // NCT6776F found, load initialization table. The table is made such
    // that its last register setting will actualy close the config. space.
    //
    for (Index = 0; Index < sizeof(mSioTableNct6776f) / sizeof(EFI_SIO_TABLE); Index++) {
      IoWrite8 (0x2e, mSioTableNct6776f[Index].Register);
      IoWrite8 (0x2f, mSioTableNct6776f[Index].Value);
    }

    IoWrite8 (0x2e, mSioTableNct6776f[0].Register);

    //
    // Try to close the SIO. If there's no SIO or if it was not opened by
    // writting 0x87 twice to port 0x2e then this code will do nothing and
    // is harmless.
    //
    IoWrite8 (0x2e, 0xaa);

    //
    // Check to see if it is initialized properly
    //
    IoWrite8 (0x2e, 0x87);
    IoWrite8 (0x2e, 0x87);
    IoWrite8 (0x2e, 0x2A);
    Value = IoRead8 (0x2f);
    IoWrite8 (0x2e, 0xaa);

    if (Loop++ > CHECKNCT6776_LOOP_COUNT)
      break;

  } while (Value != mSioTableNct6776f[0].Value);


}
#endif


/**
  Performs platform specific initialization required for the CPU to access
  the hardware associated with a SerialPortLib instance.  This function does
  not initialize the serial port hardware itself.  Instead, it initializes
  hardware devices that are required for the CPU to access the serial port
  hardware.  This function may be called more than once.

  @retval RETURN_SUCCESS       The platform specific initialization succeeded.
  @retval RETURN_DEVICE_ERROR  The platform specific initialization could not be completed.

**/
VOID
InitSerialPort (
  VOID
  )
{
  //
  // Enable I/O decoding for COM1(3F8h-3FFh), COM2(2F8h-2FFh), I/O port 2Eh/2Fh, 4Eh/4Fh, 60h/64Fh and 62h/66h.
  //
  PchLpcIoDecodeRangesSet (PcdGet16 (PcdLpcIoDecodeRange));
  PchLpcIoEnableDecodingSet (PcdGet16 (PchLpcIoEnableDecoding));
#if FixedPcdGetBool(PcdNct677FPresent) == 1
  //
  // EC is not exist, test for Lava Canyon. If it's Lava Canyon, skip
  // mobile board detection for SV board (SIO COM1 will be active).
  //
  CheckNct6776fSio ();
#endif
}
