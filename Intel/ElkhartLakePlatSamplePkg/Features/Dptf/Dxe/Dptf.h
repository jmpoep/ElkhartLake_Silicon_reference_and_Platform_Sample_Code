/** @file
  Header file for the Dptf driver.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2017 Intel Corporation.

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

#ifndef _DPTF_H_
#define _DPTF_H_

#include <Uefi.h>
#include <Base.h>
#include <IndustryStandard/Acpi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Protocol/AcpiTable.h>
#include <Protocol/AcpiSystemDescriptionTable.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/FirmwareVolume2.h>
#include <PlatformBoardId.h>
#include <SetupVariable.h>
#include <PlatformBoardType.h>

#ifndef DPTF_BASE_ADDRESS
#define DPTF_BASE_ADDRESS   0xFED98000
#endif
#ifndef DPTF_LENGTH
#define DPTF_LENGTH         0x8000
#endif

///
/// AML parsing definitions
///
#define AML_METHOD_OP       0x14

///
/// MSR definitions
///
#define MSR_PLATFORM_INFO                              0xCE
  #define CONFIG_TDP_NUM_LEVELS_OFFSET                   33
  #define CONFIG_TDP_NUM_LEVELS_MASK                     (0x3 << 1) // Bits 34:33
  #define LOW_POWER_MODE_OFFSET                          32
  #define LOW_POWER_MODE_MASK                            0x1

///
/// UINT64 workaround
///
/// The MS compiler doesn't handle QWORDs very well.  I'm breaking
/// them into DWORDs to circumvent the problems.  Converting back
/// shouldn't be a big deal.
///
#pragma pack(1)
typedef union _MSR_REGISTER {
  UINT64  Qword;

  struct _DWORDS {
    UINT32  Low;
    UINT32  High;
  } Dwords;

  struct _BYTES {
    UINT8 FirstByte;
    UINT8 SecondByte;
    UINT8 ThirdByte;
    UINT8 FouthByte;
    UINT8 FifthByte;
    UINT8 SixthByte;
    UINT8 SeventhByte;
    UINT8 EighthByte;
  } Bytes;

} MSR_REGISTER;
#pragma pack()

///
/// register definitions
///
#define MCHBAR                                         (0x48)
#define MCHBAR_MCHBAR_MASK                             0x7fffff8000

#define TMBAR                                          (0x10)

#ifndef BIT63
#define BIT0                     0x0001
#define BIT1                     0x0002
#define BIT2                     0x0004
#define BIT3                     0x0008
#define BIT4                     0x0010
#define BIT5                     0x0020
#define BIT6                     0x0040
#define BIT7                     0x0080
#define BIT8                     0x0100
#define BIT9                     0x0200
#define BIT10                    0x0400
#define BIT11                    0x0800
#define BIT12                    0x1000
#define BIT13                    0x2000
#define BIT14                    0x4000
#define BIT15                    0x8000
#define BIT16                0x00010000
#define BIT17                0x00020000
#define BIT18                0x00040000
#define BIT19                0x00080000
#define BIT20                0x00100000
#define BIT21                0x00200000
#define BIT22                0x00400000
#define BIT23                0x00800000
#define BIT24                0x01000000
#define BIT25                0x02000000
#define BIT26                0x04000000
#define BIT27                0x08000000
#define BIT28                0x10000000
#define BIT29                0x20000000
#define BIT30                0x40000000
#define BIT31                0x80000000
#define BIT32               0x100000000
#define BIT33               0x200000000
#define BIT34               0x400000000
#define BIT35               0x800000000
#define BIT36              0x1000000000
#define BIT37              0x2000000000
#define BIT38              0x4000000000
#define BIT39              0x8000000000
#define BIT40             0x10000000000
#define BIT41             0x20000000000
#define BIT42             0x40000000000
#define BIT43             0x80000000000
#define BIT44            0x100000000000
#define BIT45            0x200000000000
#define BIT46            0x400000000000
#define BIT47            0x800000000000
#define BIT48           0x1000000000000
#define BIT49           0x2000000000000
#define BIT50           0x4000000000000
#define BIT51           0x8000000000000
#define BIT52          0x10000000000000
#define BIT53          0x20000000000000
#define BIT54          0x40000000000000
#define BIT55          0x80000000000000
#define BIT56         0x100000000000000
#define BIT57         0x200000000000000
#define BIT58         0x400000000000000
#define BIT59         0x800000000000000
#define BIT60        0x1000000000000000
#define BIT61        0x2000000000000000
#define BIT62        0x4000000000000000
#define BIT63        0x8000000000000000
#endif

EFI_STATUS
EFIAPI
InitializeDptf (
  IN EFI_HANDLE               ImageHandle,
  IN EFI_SYSTEM_TABLE         *SystemTable
  );

EFI_STATUS
EFIAPI
LoadAcpiTables(
  VOID
  );

EFI_STATUS
EFIAPI
LoadAcpiTablesSds(
  VOID
  );


#endif
