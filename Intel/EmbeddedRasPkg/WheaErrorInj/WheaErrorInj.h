/** @file

  @copyright
  INTEL CONFIDENTIAL
  Copyright 2009 - 2017 Intel Corporation. <BR>

  The source code contained or described herein and all documents related to the
  source code ("Material") are owned by Intel Corporation or its suppliers or
  licensors. Title to the Material remains with Intel Corporation or its suppliers
  and licensors. The Material may contain trade secrets and proprietary    and
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
**/

#ifndef _WHEA_CORE_EINJ_
#define _WHEA_CORE_EINJ_


#include <Protocol/SmmSwDispatch2.h>
#include <IndustryStandard/Acpi.h>
#include <RasSwSmi.h>

//
// Data & structure definition
//
#define WHEA_EINJ_SET_ERROR_TYPE_WITH_ADDRSS                    0x08
#define WHEA_VENDOR_EXT_TYPE                                    0x80000000  // Intel specified OEM defined errro types
// Error consume types
#define WHEA_NO_CONSUME                 0x00
#define WHEA_MEM_COR_ERROR              0x03
// EINJ - SET_ERROR_TYPE_WITH_ADDRESS Data Structure flags
#define WHEA_SET_ERROR_TYPE_WITH_MEMORY_ADDRESS_VALID 0x02
// BIOS runtime Address range used for error injection
#define WHEA_EINJ_ADDR_RANGE                            0x4000
// Error injection operation definitions
#define EINJ_BEGIN_OPERATION                            0x55AA55AA
#define EINJ_END_OPERATION                              0x00000000

// Error injection operation status
#define WHEA_EINJ_OPERATION_BUSY                        0x01
#define WHEA_EINJ_CMD_SUCCESS                           0x00
#define WHEA_EINJ_CMD_UNKNOWN_FAILURE                   0x01
#define WHEA_EINJ_CMD_INVALID_ACCESS                    0x02
#define WHEA_EINJ_CMD_FAILED                            0x03

// Port for triggering SMI
#define R_APM_CNT                                         0xB2
#define WHEA_EINJ_TRIGGER_ERROR_ACTION                  0xFF
#pragma pack (1)
typedef struct {
  EFI_ACPI_6_0_EINJ_TRIGGER_ACTION_TABLE                   Header;
  EFI_ACPI_6_0_EINJ_INJECTION_INSTRUCTION_ENTRY            Trigger0;
  EFI_ACPI_6_0_EINJ_INJECTION_INSTRUCTION_ENTRY            Trigger1;
  EFI_ACPI_6_0_EINJ_INJECTION_INSTRUCTION_ENTRY            Trigger2;
  EFI_ACPI_6_0_EINJ_INJECTION_INSTRUCTION_ENTRY            Trigger3;
} WHEA_EINJ_TRIGGER_ACTION_TABLE;
typedef struct {
  UINT32    ErrType;
  UINT32    VendorErrTypeExtOffset;
  UINT32    Flags;
  UINT32    ApicId;
  UINT64    MemAddress;
  UINT64    MemAddressRange;
  UINT32    PcieSBDF;
} WHEA_EINJ_SET_ERROR_TYPE_WITH_ADDRESS;

typedef struct {
  UINT32                Length;
  UINT32                SBDF;// This provides a PCIe Segment, Bus, Device and Function number which can be used to read the Vendor ID, Device ID and Rev ID,

  UINT16                VendorId;
  UINT16                DeviceId;
  UINT8                 RevId;
  UINT8                 Resvd[3];
  UINT64                OemDefType1;
  UINT64                OemDefType2;
  UINT64                OemDefType3;
} WHEA_EINJ_VENDOR_EXT;

typedef struct {
  UINT64                OpState;            // opeartion state, begin/end/etc
  UINT64                ErrorToInject[5];
  UINT64                TriggerActionTable;
  UINT64                ErrorInjectCap;    // Qowrd0 -  Eroor injection cap.
  UINT64                OpStatus;
  UINT64                CmdStatus;
  UINT64                EinjAddr;
  UINT64                AddrMask;
  WHEA_EINJ_SET_ERROR_TYPE_WITH_ADDRESS  SetAddressTable;
  WHEA_EINJ_VENDOR_EXT  VendorExt;
  BOOLEAN               PcieErrInjActionTable;
  UINT8                 Skt;
} WHEA_EINJ_PARAM_BUFFER;

#pragma pack ()

#define EINJ_REGISTER_EXECUTE {   \
  EFI_ACPI_3_0_SYSTEM_IO,         \
  0x08,                           \
  0x00,                           \
  EFI_ACPI_3_0_BYTE,              \
  R_APM_CNT                       \
  }

#define EINJ_REGISTER_FILLER {    \
  EFI_ACPI_3_0_SYSTEM_MEMORY,     \
  64,                             \
  0,                              \
  EFI_ACPI_3_0_QWORD,             \
  0                               \
  }

VOID
EFIAPI
InjectMemoryError (
  UINT32   ErrorToInject
  );
#endif  //_WHEA_CORE_EINJ_
