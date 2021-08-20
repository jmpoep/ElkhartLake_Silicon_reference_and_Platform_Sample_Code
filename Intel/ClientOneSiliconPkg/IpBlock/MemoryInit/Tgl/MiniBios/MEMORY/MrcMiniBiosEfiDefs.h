/** @file
  Header file for the Mini BIOS EFI definitions

@copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2017 Intel Corporation.

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
#ifndef _MRC_MINI_BIOS_EFI_DEFS_H_
#define _MRC_MINI_BIOS_EFI_DEFS_H_


#ifndef __GNUC__
 /// Disable warning for benign redefinition of type
 #pragma warning(disable : 4142)
 #define MRC_SPRINTF(Str, Format, ...) sprintf_s (Str, sizeof (Str), Format, ##__VA_ARGS__)
#else
 typedef char TCHAR;
 typedef char _TCHAR;
 #define _SH_DENYNO 0
 #define InetPton   inet_pton
 #define sscanf_s   sscanf
 #define MRC_SPRINTF(Str, Format, ...) sprintf (Str, Format, ##__VA_ARGS__)
#endif

///
/// Basic Data typedefs.
///
#ifndef MRC_MINIBIOS_BASIC_TYPES
#define MRC_MINIBIOS_BASIC_TYPES ///< Used to guard redifintion in MiniBIOS CPU init.
// Check for 64-bit enviroment
#if _WIN64 || __x86_64__
#define MRC_X86_64_ENV
#else
#define MRC_X86_ENV
#endif

#ifdef MRC_X86_64_ENV
typedef unsigned char       UINT8;
typedef unsigned short      UINT16;
typedef unsigned int        UINT32;
typedef unsigned long long  UINT64;
typedef char                INT8;
typedef short               INT16;
typedef int                 INT32;
typedef long long           INT64;
typedef char                CHAR8;
typedef unsigned char       BOOLEAN;
typedef UINT64 EFI_PHYSICAL_ADDRESS;
typedef UINT64              UINTN;
typedef INT64               INTN;
#else
//MRC_X86_ENV
typedef unsigned char       UINT8;
typedef unsigned short      UINT16;
typedef unsigned long       UINT32;
typedef unsigned long long  UINT64;
typedef char                INT8;
typedef short               INT16;
typedef long                INT32;
typedef long long           INT64;
typedef char                CHAR8;
typedef unsigned char       BOOLEAN;
typedef UINT64 EFI_PHYSICAL_ADDRESS;
typedef UINT32              UINTN;
typedef INT32               INTN;
#endif // MRC_X86_64_ENV
#endif // MRC_MINIBIOS_BASIC_TYPES

///
/// EFI Compile Definitions
///
#define CONST           const
#define STATIC          static
#define FALSE           0
#define TRUE            1
#define DEBUG_WARN      (2)
#define DEBUG_LOAD      (4)
#define DEBUG_INFO      (0x40)
#define DEBUG_EVENT     (0x80000)
#define DEBUG_ERROR     (0x80000000)
#define EFI_SUCCESS     (0)
#define EFI_UNSUPPORTED (3)
#define RETURN_SUCCESS  (0)
#define EFI_STATUS      INT32
#define EFI_INVALID_PARAMETER   0x80000002
#define EFI_ERROR(x) (((x) & 0x80000000) != 0)
#define EFIAPI
#define GLOBAL_REMOVE_IF_UNREFERENCED
#define IN
#define OUT
#define OPTIONAL
#define ASSERT
#define DEBUG
#define DEBUG_CODE_BEGIN()
#define DEBUG_CODE_END()
#define ASSERT_EFI_ERROR
#define ARRAY_SIZE  ARRAY_COUNT

#define EFI_PCI_COMMAND_MEMORY_SPACE   0x0002
#define EFI_PCI_COMMAND_BUS_MASTER     0x0004

#define PCI_BASE_ADDRESSREG_OFFSET     0x10
#define PCI_COMMAND_OFFSET             0x04

#define PCI_VENDOR_ID_OFFSET            0x0

#define B_PCI_BAR_MEMORY_TYPE_MASK                (MRC_BIT1 | MRC_BIT2)
#define B_PCI_BAR_MEMORY_TYPE_64                  MRC_BIT2

#define PCH_PCIE_CONTROLLER_PORTS                 4u
#ifndef VOID
typedef void VOID;
#endif
#ifndef NULL
#define NULL  ((void *) 0)
#endif

#ifndef EFI_STRUCT
#define EFI_STRUCT
#pragma pack (push, 1)
typedef struct {
  UINT32 Data1;
  UINT16 Data2;
  UINT16 Data3;
  UINT8  Data4[8];
} EFI_GUID;
typedef struct {
  UINT8 Data;
} EFI_PEI_SERVICES;
typedef struct {
  UINT8 Register;
  UINT8 Function;
  UINT8 Device;
  UINT8 Bus;
  UINT32 ExtendedRegister;
} EFI_PEI_PCI_CFG_PPI_PCI_ADDRESS;
#pragma pack (pop)
#endif // EFI_STRUCT

#endif  // _MRC_MINI_BIOS_EFI_DEFS_H_

