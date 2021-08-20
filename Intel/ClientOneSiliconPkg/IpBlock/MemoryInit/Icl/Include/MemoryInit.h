/** @file
  Memory Initialization PEIM.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
@todo code cleanup for txt memoryinit overlap
**/
#ifndef _MemoryInit_h_
#define _MemoryInit_h_

#include <Base.h>
#include <PiPei.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <Ppi/SiPolicy.h>
#include <ConfigBlock.h>
#include <MrcInterface.h>
#include <MemInfoHob.h>
#include <SaConfigHob.h>

#include "CpuRegs.h"

///
/// SMRAM range definitions
///
#define MC_ABSEG_HSEG_PHYSICAL_START  0x000A0000
#define MC_ABSEG_HSEG_LENGTH          0x00020000
#define MC_ABSEG_CPU_START            0x000A0000
#define MC_HSEG_CPU_START             0xFEDA0000

///
/// Memory Map definitions
///
#define ADDRESS_SPACE_START           0x0
#define LOWER_MEMORY_START            0x100000

///
/// Maximum number of memory ranges reported by GetMemoryMap()
///
#define MAX_RANGES    (16)

#define MEM_EQU_4GB   0x100000000ULL
#define MB_TO_GB_MUL  0x100000ULL
///
/// TPM Status and Time-out
///
#define TPM_TIME_OUT            750

#define PLATFORM_ID_MOBILE      1

///
/// Memory range types
///
typedef enum {
  DualChannelDdrMainMemory,
  DualChannelDdrSmramCacheable,
  DualChannelDdrSmramNonCacheable,
  DualChannelDdrGraphicsMemoryCacheable,
  DualChannelDdrGraphicsMemoryNonCacheable,
  DualChannelDdrReservedMemory,
  DualChannelDdrReservedWriteBackMemory,
  DualChannelDdrMaxMemoryRangeType
} PEI_DUAL_CHANNEL_DDR_MEMORY_RANGE_TYPE;

///
/// Memory map range information
///
#pragma pack(push, 1)
typedef struct {
  UINT8                                   RowNumber;
  EFI_PHYSICAL_ADDRESS                    PhysicalAddress;
  EFI_PHYSICAL_ADDRESS                    CpuAddress;
  EFI_PHYSICAL_ADDRESS                    RangeLength;
  PEI_DUAL_CHANNEL_DDR_MEMORY_RANGE_TYPE  Type;
} PEI_DUAL_CHANNEL_DDR_MEMORY_MAP_RANGE;
#pragma pack(pop)

#define MRC_INSTANCE_SIGNATURE  SIGNATURE_32 ('M', 'R', 'C', 'I')

typedef struct _MRC_INSTANCE {
  UINT32                       Signature;
  EFI_PEI_NOTIFY_DESCRIPTOR    NotifyDescriptor;
  IN EFI_PEI_FILE_HANDLE       FileHandle;
  BOOLEAN                      MrcExecuted;
} MRC_INSTANCE;

#define MRC_INSTANCE_FROM_NOTIFY_THIS(a) CR (a, MRC_INSTANCE, NotifyDescriptor, MRC_INSTANCE_SIGNATURE)

/**
  A notify callback function to determine if main memory detection function can be executed or not

  @param[in] PeiServices          General purpose services available to every PEIM.
  @param[in] NotifyDescriptor     The notification structure this PEIM registered on install.
  @param[in] Ppi                  The notify callback PPI.  Not used.

  @retval EFI_SUCCESS          - MRC has been executed successfully
  @retval EFI_NOT_READY        - One of the dependency not ready yet for MRC execution.
**/
extern
EFI_STATUS
EFIAPI
PrememoryInitCallBack (
  IN EFI_PEI_SERVICES          **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
  IN VOID                      *Ppi
  );

/**
  Main starting point for system memory initialization.
    1. Get SysBootMode and MrcBootMode
    2. Locate SaPolicy PPI
    3. Locate S3DataPtr from SaPolicy.
    4. SaveDataValid := TRUE if S3DataPtr is not NULL.
    5. If SysBootMode is BOOT_ON_S3_RESUME and S3Data is not valid:
    -> ASSERT.
    6. If MrcBootMode is Warm boot, but S3 data is not valid :
    -> change MrcBootMode to Cold boot.
    7. If MrcBootMode is Cold boot:
    -> Run MRC code
    -> Save S3 Restore Data
    Else
    -> Run MRC_S3Resume
    8. Run MRC_Done().
    9. Install EFI memory HOBs.

  @param[in] FfsHeader (or FileHandle) - Pointer to Firmware File System file header
  @param[in] PeiServices               - General purpose services available to every PEIM.
  @param[in] MrcInstance               - MRC instance structure for callback implementation

  @retval EFI_SUCCESS      - Memory initialization completed successfully.
  @retval EFI_NOT_READY    - Cannot locate SA Policy.
  @retval EFI_NOT_FOUND    - No S3 data in S3 Boot Mode.
  @retval EFI_DEVICE_ERROR - MemoryInit failed or IOSAV Memory test failed.
**/
extern
EFI_STATUS
PeimMemoryInit (
  IN EFI_PEI_FILE_HANDLE       FileHandle,
  IN CONST EFI_PEI_SERVICES    **PeiServices,
  IN MRC_INSTANCE              *MrcInstance
  );

/**
  This function installs memory for all paths.

  @param[in] MrcData                - Mrc data structure
  @param[in] PeiServices            - PEI Services table.
  @param[in] SysBootMode            - The specific boot path that is being followed.
  @param[in] MiscPeiPreMemConfig   - SA_MISC_PEI_PREMEM_CONFIG structure.

  @retval EFI_SUCCESS          The function completed successfully.
  @retval EFI_OUT_OF_RESOURCES Out of Resources.
**/
extern
EFI_STATUS
InstallEfiMemory (
  IN MrcParameters             *CONST  MrcData,
  IN CONST EFI_PEI_SERVICES    **PeiServices,
  IN       EFI_BOOT_MODE       SysBootMode,
  IN SA_MISC_PEI_PREMEM_CONFIG *MiscPeiPreMemConfig
  );

/**
  Determine the memory size desired based on HOB memory information.

  @param[in, out] Size        - The memory size to return.

  @retval Nothing.
**/
extern
void
RetrieveRequiredMemorySize (
  OUT UINTN                   *Size
  );

/**
  Determine the Total DPR memory size needed based on the DPR directory in the SA Data HOB.

  @param[in, out] Size        - The memory size in MB to return.

  @retval Nothing.
**/
extern
void
CalculateTotalDprMemorySize (
  IN OUT   UINT8             *Size
  );

/**
  Calculates the bases for each technology consuming the DPR region
  and updates the SA Data HOB with the appropriate values in the Dpr
  directory

  @param[in] Base           - The memory base to return.
  @param[in] TotalDprSizeMB - The total DPR size in MB

  @retval Nothing.
**/
extern
VOID
UpdateDprHobInfo (
  IN       EFI_PHYSICAL_ADDRESS  Base,
  IN       UINT8                 TotalDprSizeMB
  );

/**
  This function returns the memory ranges to be enabled, along with information
  describing how the range should be used. The MemoryMap buffer will be filled in and
  NumRanges will contain the actual number of memory ranges that are to be enabled.

  @param[in]      MrcData     - Mrc data structure
  @param[in, out] MemoryMap   - Buffer to record details of the memory ranges to be enabled.
  @param[in, out] NumRanges   - On input, this contains the maximum number of memory ranges that
                                can be described in the MemoryMap buffer.

  @retval EFI_SUCCESS          - The function completed successfully.
  @retval EFI_BUFFER_TOO_SMALL - The specified number of ranges is too large.
**/
extern
EFI_STATUS
GetMemoryMap (
  IN MrcParameters  *CONST                        MrcData,
  IN OUT   PEI_DUAL_CHANNEL_DDR_MEMORY_MAP_RANGE  *MemoryMap,
  IN OUT   UINT8                                  *NumRanges
  );

/**
  This function returns a pointer to the allocated hand off buffer.

  @param[in]      PeiServices - A pointer to the EFI PEI services table
  @param[in, out] Hob         - A pointer to where to store the pointer to the allocated data buffer.
  @param[in]      BlockSize   - The size of the buffer to get.
  @param[in]      Guid        - The GUID to assign to the HOB.

  @retval EFI_SUCCESS - Hob is successfully built.
  @retval Others      - Error occured while creating the Hob.
**/
extern
EFI_STATUS
MrcGetHobForDataStorage (
  IN OUT VOID                     **Hob,
  IN     UINT16                   BlockSize,
  IN     EFI_GUID                 *Guid
  );

#ifdef BDAT_SUPPORT
/**
  Finds the BDAT Schema List HOB if it exists.  If it does not exist, creates it

  @param[out] BdatSchemaListHob - Pointer to Schema List Hob, by reference

  @retval EFI_SUCCESS - Hob was successfully found or built.
  @retval Others      - Error occured while creating or finding the Hob.
**/
EFI_STATUS
MrcGetBdatSchemaListHob (
  OUT      MRC_BDAT_SCHEMA_LIST_HOB  **BdatSchemaListHob
  );
#endif


/**
  Determines whether or not the platform has executed a TXT launch by
  examining the TPM Establishment bit.

  @param[in] VOID

  @retval TRUE        - If the TPM establishment bit is asserted.
  @retval FALSE       - If the TPM establishment bit is unasserted.
**/
extern
BOOLEAN
IsEstablishmentBitAsserted (
  VOID
  );

/**
  Unlock memory when security is set and TxT is not enabled.

  @param[in] MrcData     - Mrc global data.

  @retval Nothing
**/
extern
void
UnlockMemory (
  IN CONST MrcParameters    *CONST  MrcData
  );
/**
  Determine whether a cold reset of the platform is required.
  Note that the memory configuration saved data must be valid.

  @param[in] MrcData             - The MRC "global data" area.
  @param[in] MemConfig           - MEMORY CONFIGURATION structure.
  @param[in] MrcBootMode         - Current MRC boot mode.

  @retval TRUE if cold reset is required, otherwise returns FALSE.
**/
extern
BOOLEAN
ColdBootRequired (
  IN CONST MrcParameters          *CONST  MrcData,
  IN MEMORY_CONFIGURATION         *MemConfig,
  IN MRC_BOOT_MODE                MrcBootMode
  );

/**
  Set up the MRC OEM data structure.

  @param[in, out] MrcData            - Pointer to the MRC global data structure.
  @param[in]     MemConfig           - MEMORY CONFIGURATION structure.
  @param[in]     MemConfigNoCrc      - MEMORY CONFIG NO CRC structure.

  @retval Nothing.
**/
extern
void
MrcSetupOem (
  IN OUT MrcParameters          *CONST   MrcData,
  IN    MEMORY_CONFIGURATION    *MemConfig,
  IN    MEMORY_CONFIG_NO_CRC    *MemConfigNoCrc
  );

/**
  Set up the MRC input data structure.

  @param[in]  SysBootMode         - Boot mode of the system.
  @param[in]  BootMode            - Boot mode of the MRC.
  @param[in]  MrcData             - Pointer to the MRC global data structure
  @param[in]  MiscConfig          - SA_MISC_CONFIG structure.
  @param[in]  GtConfig            - GRAPHICS_CONFIG structure.
  @param[in]  MemConfig           - MEMORY_CONFIGURATION structure.
  @param[in]  MemConfigNoCrc      - MEMORY_CONFIG_NO_CRC structure.
  @param[in]  SiCpuPolicyPpi      - The Cpu Policy PPI instance.
  @param[in]  CpuModel            - CPU Type.

  @retval Updated MRC_BOOT_MODE
**/
extern
MRC_BOOT_MODE
MrcSetupMrcData (
  IN CONST EFI_BOOT_MODE              SysBootMode,
  IN CONST MRC_BOOT_MODE              BootMode,
  OUT      MrcParameters              *CONST MrcData,
  IN       SA_MISC_PEI_PREMEM_CONFIG  *MiscPeiPreMemConfig,
  IN       GRAPHICS_PEI_PREMEM_CONFIG *GtConfig,
  IN       MEMORY_CONFIGURATION       *CONST MemConfig,
  IN       MEMORY_CONFIG_NO_CRC       *CONST MemConfigNoCrc,
  IN       SI_PREMEM_POLICY_PPI       *CONST SiPreMemPolicyPpi,
  IN       CPU_FAMILY                  CpuModel
  );

/**
  Check to see if user defined profile is selected and if it is, then copy the
  timing settings for this profile to the timing override structure. If user
  defined profile is not selected, then set the timing override structure to 0.

  Note that even though we set timings on a DIMM by DIMM basis, the controller
  may force DIMM timings to be the same for all DIMMs in a channel.

  @param[in, out] Inputs              - The MRC Input data structure.
  @param[in]      MemConfig           - MEMORY CONFIGURATION structure.

  @retval Nothing.
**/
extern
void
CheckForTimingOverride (
  IN OUT MrcInput               *CONST  Inputs,
  IN     MEMORY_CONFIGURATION   *MemConfig
  );


/**
  Build S3 memory data HOB

  @param[in] MrcData          Pointer to Mrc Parameters
**/
VOID
BuildMemoryS3DataHob (
  IN MrcParameters            *MrcData
  );

/**
  Build SMBIOS and OC memory data HOB

  @param[in] MrcData          Pointer to Mrc Parameters
**/
VOID
BuildMemoryInfoDataHob (
  IN MrcParameters            *MrcData
  );

/**
  Build platform memory data HOB

  @param[in]      MrcData             Pointer to Mrc Parameters
  @param[in, out] MemoryPlatformData  Hob to pass memory data for platform code
**/
VOID
BuildMemoryPlatformDataHob (
  IN     MrcParameters            *MrcData,
  IN OUT MEMORY_PLATFORM_DATA_HOB *MemoryPlatformData
  );

/**
  Check if a number is a power of two

  @param[in]      UINT32           num
  @retval         BOOLEAN          TRUE if is a power of two
**/

BOOLEAN
IsThisPowerOfTwo (
  IN UINT32 num
  );

/**
  Round a number to the next power of two

  @param[in, out] UINT32 num   -  number to be rounded to the next power of two.
  @retval         UINT32 num   -  number rounded to the next power of two.
**/

UINT32
RoundToNextPow2 (
  IN UINT32 num);

#endif
