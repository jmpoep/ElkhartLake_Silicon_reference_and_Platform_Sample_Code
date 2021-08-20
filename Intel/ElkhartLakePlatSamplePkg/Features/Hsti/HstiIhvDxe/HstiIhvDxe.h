/** @file
  This file contains the required header files for the HSTI Silicon DXE driver

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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

@par Specification
**/

#ifndef _HSTI_IHV_DXE_H_
#define _HSTI_IHV_DXE_H_

#include <PiDxe.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/MpService.h>
#include <Library/TimerLib.h>
#include <Library/IoLib.h>
#include <Guid/EventGroup.h>
#include <Library/UefiLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Protocol/Tcg2Protocol.h>
#include <IndustryStandard/Hsti.h>
#include <Protocol/AdapterInformation.h>
#include <Library/HstiLib.h>
#include <HstiFeatureBit_1_1a.h>
#include <IndustryStandard/FirmwareInterfaceTable.h>
#include <Library/HobLib.h>
#include <Register/VtdRegs.h>

#ifndef TPM_BASE
#define TPM_BASE                  0
#endif
#include <Library/Tpm2CommandLib.h>

#define TPM_BASE_ADDRESS                 0xfed40000
#define DTPM_LOC                         (BIT18 | BIT16)
#define FTPM_LOC                         (BIT18 | BIT17 | BIT16)
#define TPM_VER_FTIF_FT_LOC_MASK         (BIT18 | BIT17 | BIT16)

//
// Silicon
//
#include <Protocol/SiPolicyProtocol.h>
#include <Protocol/Spi.h>
#include <Protocol/HeciProtocol.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/PmcLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/SmbusInfoLib.h>
#include <Library/SpiAccessLib.h>
#include <Library/PchDmiAccessLib.h>
#include <Library/RtcAccessLib.h>
#include <Library/PmcLib.h>
#include <Library/ThermalAccessLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PchPcieRpLib.h>
#include <Include/PcieRegs.h>
#include <Register/Cpuid.h>
#include <Register/Msr.h>
#include <Register/MeRegs.h>
#include <Register/PchRegs.h>
#include <Register/PchDmiRegs.h>
#include <Register/PchRegsLpc.h>
#include <Register/PchPcieRpRegs.h>
#include <Register/VirtualMsrcommon.h>
#include <Library/SaPlatformLib.h>
#include <Library/IpuLib.h>
#include <Library/CpuPlatformLib.h>
#include <Library/ItbtPcieRpLib.h>
#include <CpuRegs.h>
#include <MemInfoHob.h>
#include <Library/P2sbLib.h>


#include <SaCommonDefinitions.h>
#include <Register/SaRegsHostBridge.h>
#include <Register/ItbtPcieRegs.h>
#include <Fru/EhlCpu/Include/Register/IgdRegs.h>

#include <Library/SmbusInfoLib.h>
#include <Library/SataLib.h>

#define  SIZE_4KB    0x00001000
#define  SIZE_16KB   0x00004000
#define  SIZE_32KB   0x00008000
#define  SIZE_1MB    0x00100000
#define  SIZE_2MB    0x00200000
#define  SIZE_4MB    0x00400000
#define  SIZE_8MB    0x00800000
#define  SIZE_16MB   0x01000000
#define  SIZE_32MB   0x02000000
#define  SIZE_128MB  0x08000000
#define  SIZE_4GB    0x0000000100000000ULL
#define  BASE_4GB    0x0000000100000000ULL

#define MAX_NEW_AUTHORIZATION_SIZE        SHA512_DIGEST_SIZE

#define HSTI_PLATFORM_NAME  L"Intel"
#define HSTI_BUILD_STRING_ERROR     L"Invalid Input Parameter <Null String>: Unable to build Status String\r\n"
#define HSTI_OUT_OF_RESOURCES_ERROR L"Out of Resources: Unable to Save Status String in HSTI Status Structure\r\n"

#define   B_IGD_VENDOR_DID_MASK           (0xFFFFFFFF)

// Max debug message length for DEBUG call is char[128],
// Workaround for printing 128 characters to Serial Comm port
// instead of one by one character
#define MAX_DEBUG_HSTI_MESSAGE_LENGTH     128

#pragma pack(1)
typedef struct {
  UINT32  Version;
  UINT32  Role;
  CHAR16  ImplementationID[256];
  UINT32  SecurityFeaturesSize;
  UINT8   SecurityFeaturesRequired[HSTI_SECURITY_FEATURE_SIZE];
  UINT8   SecurityFeaturesImplemented[HSTI_SECURITY_FEATURE_SIZE];
  UINT8   SecurityFeaturesVerified[HSTI_SECURITY_FEATURE_SIZE];
  CHAR16  End;
} ADAPTER_INFO_PLATFORM_SECURITY_STRUCT;
#pragma pack()

extern UINT8  mFeatureImplemented[HSTI_SECURITY_FEATURE_SIZE];

/**
  Check HSTI Library Set was Successful
**/
VOID
CheckStatusForHstiLibSet (
  IN EFI_STATUS   Status
  );

/**
  Check HSTI Library Set was Successful
**/
VOID
CheckStatusForHstiLibAppend (
  IN EFI_STATUS   Status
  );

/**
  Concatenate Status string.

  @param[in] StatusCodeString     - Status Code
  @param[in] StatusCategoryString - Status Category
  @param[in] StatusString         - Status Text
  @param[out] StringSizeOut       - Return String size for memory deallocation

  @retval CHAR16 - Concatenated string.
  Note: This function will always return a string. In case of error while
         trying to create the Concatenated String, it will as well return
         a string for Invalid output Parameter or out of resources error.
**/
CHAR16 *
EFIAPI
BuildHstiStatusStringAndSize (
  IN  CHAR16                   *StatusCodeString,
  IN  CHAR16                   *StatusCategoryString,
  IN  CHAR16                   *StatusString,
  OUT UINTN                    StringSizeOut
  );

/**
  Concatenate Status string and Append HSTI Status String.

  @param[in] StatusCodeString     - Status Code
  @param[in] StatusCategoryString - Status Category
  @param[in] StatusString         - Status Text

  @retval EFI_SUCCESS            The Status String was successfully build and saved in HSTI Status Structure.
**/
EFI_STATUS
EFIAPI
BuildAndAppendHstiStatusString (
  IN  CHAR16                   *StatusCodeString,
  IN  CHAR16                   *StatusCategoryString,
  IN  CHAR16                   *StatusString
  );

/**
  Run tests for HardwareRootedBootIntegrity bit
**/
VOID
CheckHardwareRootedBootIntegrity (
  VOID
  );

/**
  Run tests for BootFirmwareMediaProtection bit
**/
VOID
CheckBootFirmwareMediaProtection (
  VOID
  );
/**
  Run tests for MeasuredBootEnforcement bit
**/
VOID
CheckMeasuredBootEnforcement (
  VOID
  );

/**
  Run tests for IntegratedDeviceDMAProtection bit
**/
VOID
CheckIntegratedDeviceDmaProtection (
  VOID
  );

/**
  Run tests for SecureDebugInterfaceConfiguration
**/
VOID
CheckSecureDebugInterfaceConfiguration (
  VOID
  );

/**
  Run tests for SecureCPUConfiguration bit
**/
VOID
CheckSecureCpuConfiguration (
  VOID
  );

/**
  Run tests for SecureMemoryMapConfiguration bit
**/
VOID
CheckSecureMemoryMapConfiguration (
  VOID
  );

/**
  Run tests for SecureIntegratedGraphicsConfiguration bit
**/
VOID
CheckSecureIntegratedGraphicsConfiguration (
  VOID
  );

/**
  Run tests for SecurePCHConfiguration bit
**/
VOID
CheckSecurePchConfiguration (
  VOID
  );

//
// Help function
//

/**
  Initialize MP Helper
**/
VOID
InitMp (
  VOID
  );

/**
  Concatenate error string.

  @retval UINTN - CpuNumber.
**/
UINTN
GetCpuNumber (
  VOID
  );


/**
  Read each processor MSR value.

  @param[in] ProcessorNumber     - Processor ID
  @param[in] Index               - Index

  @retval UINT64 - Msr Value.
**/
UINT64
ProcessorReadMsr64 (
  IN UINTN   ProcessorNumber,
  IN UINT32  Index
  );

/**
  Write value to each processor MSR.

  @param[in] ProcessorNumber     - Processor ID
  @param[in] Index               - Index
  @param[in] Value               - Value

**/
VOID
ProcessorWriteMsr64 (
  IN UINTN   ProcessorNumber,
  IN UINT32  Index,
  IN UINTN   Value
  );

/**
  Concatenate error string.

  @param[in]  ProcessorNumber     - Processor ID
  @param[in]  Index               - Index
  @param[out] Eax                 - Eax
  @param[out] Ebx                 - Ebx
  @param[out] Ecx                 - Ecx
  @param[out] Edx                 - Edx
**/
VOID
ProcessorCpuid (
  IN  UINTN   ProcessorNumber,
  IN  UINT32  Index,
  OUT UINT32  *Eax,  OPTIONAL
  OUT UINT32  *Ebx,  OPTIONAL
  OUT UINT32  *Ecx,  OPTIONAL
  OUT UINT32  *Edx   OPTIONAL
  );

/**
  Concatenate error string.

  @param[in] Address     - Address

  @retval UINT64 - Value.
**/
UINT64
EFIAPI
PciRead64 (
  IN  UINTN                   Address
  );

#endif
