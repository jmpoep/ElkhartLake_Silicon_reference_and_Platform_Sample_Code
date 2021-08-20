/** @file

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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

#ifndef _DXE_SMM_INTEL_GRAPHICS_DEVICE_LIB_H_
#define _DXE_SMM_INTEL_GRAPHICS_DEVICE_LIB_H_


#define VBIOS_SUCCESS       0x05F
#define VBIOS_FAILED        0x15F
#define NOT_NEED_ATTACHED   0x01
#define DEVICE_DEFAULT_ALL_BYTE   0x0F
#define DEVICE_DEFAULT_ALL_WORD   0x0F0F
#define DEVICE_SECOND_ALL_BYTE    0xF0
#define DEVICE_SECOND_ALL_WORD    0xF0F0

//
// Meaning of Bit for Device Type
//
//  Bit 15  = Pipe B - LFP2
//  Bit 14  = Pipe B - EFP2
//  Bit 13  = Pipe B - TV2
//  Bit 12  = Pipe B - CRT2
//  Bit 11  = Pipe B - LFP
//  Bit 10  = Pipe B - EFP
//  Bit 9 = Pipe B - TV
//  Bit 8 = Pipe B - Reserved (830M), CRT (855MG, Alviso, Calistoga)
//  Bit 7 = Pipe A - LFP2 (830M), Reserved (855MG, Alviso, Calistoga)
//  Bit 6 = Pipe A - EFP2
//  Bit 5 = Pipe A - TV2
//  Bit 4 = Pipe A - CRT2
//  Bit 3 = Pipe A - LFP (830M), Reserved (855MG, Alviso, Calistoga)
//  Bit 2 = Pipe A - EFP
//  Bit 1 = Pipe A - TV
//  Bit 0 = Pipe A - CRT
//
#define DEVICE_PIPEA_CRT          0x0001
#define DEVICE_PIPEA_TV           0x0002
#define DEVICE_PIPEA_EFP          0x0004
#define DEVICE_PIPEA_LFP          0x0008
#define DEVICE_PIPEA_CRT2         0x0010
#define DEVICE_PIPEA_TV2          0x0020
#define DEVICE_PIPEA_EFP2         0x0040
#define DEVICE_PIPEA_LFP2         0x0080
#define DEVICE_PIPEB_CRT          0x0100
#define DEVICE_PIPEB_TV           0x0200
#define DEVICE_PIPEB_EFP          0x0400
#define DEVICE_PIPEB_LFP          0x0800
#define DEVICE_PIPEB_CRT2         0x1000
#define DEVICE_PIPEB_TV2          0x2000
#define DEVICE_PIPEB_EFP2         0x4000
#define DEVICE_PIPEB_LFP2         0x8000

//
// Pop-Up states and modes
//
#define POP_UP_WINDOW_OPENED      0x01
#define POP_UP_WINDOW_LOADED      0x10

//
// Mode1 : 100b, 64 x 64 2bpp 3-color + Transparency mode
// Mode2 : 101b, 64 x 64 2bpp AND / XOR mode
// Mode3 : 110b, 64 x 64 2bpp 4-color mode
//
#define POP_UP_WINDOW_MODE_1      4
#define POP_UP_WINDOW_MODE_2      5
#define POP_UP_WINDOW_MODE_3      6

//
// Panel Fitting states
//
#define PANEL_FITTING_CENTERING   0x1
#define PANEL_FITTING_STRETCHING  0x6
//
// Global variables used in this module
//
extern EFI_PHYSICAL_ADDRESS         mPopupData;
extern EFI_PHYSICAL_ADDRESS         mPopupColor;
extern UINTN                        mPopupDataSize;

EFI_STATUS
LoadPopUpToVbios (
  VOID
  );
/*++

Routine Description:

  Locate the pop-up buffer and pass it to the video BIOS.
  This must call the legacy BIOS protocol, which is only available to BS code.
  It is not SMM safe.

Arguments:

  None

Returns:

  EFI_SUCCESS       The function completed successfully
  EFI_UNSUPPORTED   Could not locate a pop up bitmap to load

--*/

EFI_STATUS
GetFvImage (
  IN EFI_GUID   *NameGuid,
  IN OUT VOID   **Buffer,
  IN OUT UINTN  *Size
  );
/*++

Routine Description:

  This routine will take a GUIDed file name and provide a buffer of the data.

Arguments:

  NameGuid  Pointer to a GUID of the file name.
  Buffer    Pointer to a buffer for the file contents.
  Size      Size of the buffer, in bytes

Returns:

  EFI_SUCCESS     The wanted image has been found and loaded.
  EFI_NOT_FOUND   The wanted image has not been found.

--*/

EFI_STATUS
InitializeInternalGraphicDeviceLib (
  VOID
  );

VOID
GraphicsInt (
  IN EFI_IA32_REGISTER_SET   *Registers
  );

VOID
GetCadl (
  IN OUT EFI_IA32_REGISTER_SET   *Registers
  );

EFI_STATUS
GetNextState (
  IN OUT EFI_IA32_REGISTER_SET   *Registers
  );

#endif
