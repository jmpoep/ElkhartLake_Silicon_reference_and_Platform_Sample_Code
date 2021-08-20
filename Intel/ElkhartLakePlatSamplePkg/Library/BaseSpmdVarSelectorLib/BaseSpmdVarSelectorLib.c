/** @file
  This library contains platform-specific logic to determine whether a given UEFI variable
  should be stored in the Secure Pre-Memory Data area.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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

#include <BootState.h>
#include <SimpleBootFlag.h>
#include <SoftwareGuardSetupData.h>
#include <WdtAppVariable.h>

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/SpmdVarSelectorLib.h>
#include <Library/DebugLib.h>

#include <Guid/CapsuleVendor.h>
#include <Guid/DebugMask.h>
#include <Guid/FirmwarePerformance.h>
#include <Guid/GlobalVariable.h>
#include <Guid/MemoryOverwriteControl.h>
#include <Guid/MemoryTypeInformation.h>
#include <Guid/PhysicalPresenceData.h>
#include <Guid/S3MemoryVariable.h>
#include <Guid/Tcg2PhysicalPresenceData.h>

typedef struct {
  CONST CHAR16       *VariableName;
  EFI_GUID           *VendorGuid;
} VARIABLE_NAME_TABLE_ENTRY;

//
// Any UEFI variable that is accessed in pre-memory on a CSE-assisted variable boot
// must be added to this structure.
//
STATIC VARIABLE_NAME_TABLE_ENTRY mSecurePreMemoryStoredVariables[] = {
  #if FixedPcdGetBool(PcdFspWrapperEnable) == 1
  { L"MemoryConfig",                              &gFspNonVolatileStorageHobGuid      },
#endif
  { L"Setup",                                     &gSetupVariableGuid                 },
  { L"MemoryConfig",                              &gMemoryConfigVariableGuid          },
  { L"SaPegData",                                 &gPegConfigVariableGuid             },
  { L"SaSetup",                                   &gSaSetupVariableGuid               },
  { L"MeSetup",                                   &gMeSetupVariableGuid               },
  { L"CpuSetup",                                  &gCpuSetupVariableGuid              },
  { L"PchSetup",                                  &gPchSetupVariableGuid              },
  { L"SiSetup",                                   &gSiSetupVariableGuid               },
  { L"TcgSetup",                                  &gSetupVariableGuid                 },
  { L"ComAttributes",                             &gSetupVariableGuid                 },
  { L"UsbMassDevNum",                             &gSetupVariableGuid                 },
  { L"UsbSupport",                                &gSetupVariableGuid                 },
  { L"PciBusSetup",                               &gSetupVariableGuid                 },
  { L"SetupCpuFeatures",                          &gSetupVariableGuid                 },
  { L"DebugConfigData",                           &gDebugConfigVariableGuid           },
  { L"OcSetup",                                   &gOcSetupVariableGuid               },
  { L"InitSetupVariable",                         &gSetupVariableGuid                 },
  { L"OsProfile",                                 &gOsProfileGuid                     },
  { BOOT_STATE_VARIABLE_NAME,                     &gBootStateGuid                     },
  { SIMPLE_BOOT_FLAG_VARIABLE_NAME,               &gEfiGlobalVariableGuid             },
  { EFI_SECURE_BOOT_MODE_NAME,                    &gEfiGlobalVariableGuid             },
  { L"ConOut",                                    &gEfiGlobalVariableGuid             },
  { L"PerfDataMemAddr",                           &gPerformanceProtocolGuid           },
  { L"syscg",                                     &gSsaBiosVariablesGuid              },
  { L"SinitSvn",                                  &gSinitSvnGuid                      },
  { L"CpuSetupSgxEpochData",                      &gCpuSetupVariableGuid              },
  { EFI_FIRMWARE_PERFORMANCE_VARIABLE_NAME,       &gEfiFirmwarePerformanceGuid        },
  { MEMORY_OVERWRITE_REQUEST_VARIABLE_NAME,       &gEfiMemoryOverwriteControlDataGuid },
  { TCG2_PHYSICAL_PRESENCE_FLAGS_VARIABLE,        &gEfiTcg2PhysicalPresenceGuid       },
  { PHYSICAL_PRESENCE_VARIABLE,                   &gEfiPhysicalPresenceGuid           },
  { EFI_MEMORY_TYPE_INFORMATION_VARIABLE_NAME,    &gEfiMemoryTypeInformationGuid      },
  { DEBUG_MASK_VARIABLE_NAME,                     &gEfiGenericVariableGuid            },
  { EFI_CAPSULE_VARIABLE_NAME,                    &gEfiCapsuleVendorGuid              },
  { EFI_CAPSULE_LONG_MODE_BUFFER_NAME,            &gEfiCapsuleVendorGuid              },
  { EPC_OS_CTRL,                                  &gEpcOsDataGuid                     },
  { S3_MEMORY_VARIABLE_NAME,                      &gS3MemoryVariableGuid              },
  { WDT_PERSISTENT_DATA_C_NAME,                   &gWdtPersistentDataGuid             }
};

/**
  Returns whether the UEFI variable given should be stored in the secure pre-memory data area.

  @param[in] VariableName         Name of the variable.
  @param[in] VendorGuid           Guid of the variable.

  @return    BOOLEAN              TRUE if the variable should be stored in the secure pre-memory data area. Otherwise FALSE.
**/
BOOLEAN
EFIAPI
IsSecurePreMemoryDataVariable (
  IN  CONST  CHAR16       *VariableName,
  IN  CONST  EFI_GUID     *VendorGuid
  )
{
  UINTN   Index;

  for (Index = 0;
       Index < (sizeof (mSecurePreMemoryStoredVariables) / sizeof (mSecurePreMemoryStoredVariables[0]));
       Index++) {
    if (CompareGuid (VendorGuid, mSecurePreMemoryStoredVariables[Index].VendorGuid) &&
        (StrCmp (VariableName, mSecurePreMemoryStoredVariables[Index].VariableName) == 0)) {
      return TRUE;
    }
  }
  return FALSE;
}
