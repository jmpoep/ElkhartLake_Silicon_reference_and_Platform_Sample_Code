/** @file
  CpuPowerOnConfig PEI Library

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2020 Intel Corporation.

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

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/CpuCommonLib.h>
#include <Library/CpuPowerOnConfigLib.h>
#include <Library/DebugLib.h>
#include <Library/CpuPlatformLib.h>
#include <Library/CpuCommonLib.h>
#include <Ppi/MasterBootMode.h>
#include <Register/Cpuid.h>
#include <Register/Msr.h>
#include <CpuAccess.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PostCodeLib.h>
#include <Library/PmcPrivateLib.h>
#include <Ppi/BlockIo.h>
#include <Ppi/Spi.h>
#include <Library/BootMediaLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/SpiCommonLib.h>
#include <Ppi/UfsWritePpi.h>

#define UFS_BOOT_LUN          1
#define UFS_CPU_STRAP_OFFSET  0xC6C
#define DESCRIPTOR_SIZE       4096
UINT32  UfsStrapAddress     = 0;

///
/// Structure for CPU Strap settings
///
typedef struct {
  UINT32 HtDisabled              :  1; ///< Intel HT Technology Disable.
  UINT32 NumberOfActiveCores     :  4; ///< Number of Active Cores.
  UINT32 Bist                    :  1; ///< Built In Self Test (BIST) initiation.
  UINT32 FlexRatio               :  6; ///< Flex Ratio.
  UINT32 BootRatio               :  1; ///< Processor boot ratio; When set allows the processor to power up in maximum non-turbo ratio from the following boot.
  UINT32 JtagC10PowerGateDisable :  1; ///< JTAG Power gate disable.
  UINT32 Reserved2               : 18;
} CPU_STRAP_SET;

/**
  Check if VT is fused and disabled by Setup Option so reset is needed.

  @param[in] VmxEnable - VmxEnable CPU policy.

  @retval NO_RESET          - No reset is needed.
  @retval COLD_RESET        - Update requires a cold reset.
**/
CPU_RESET_TYPE
CheckVmxIfNeedReset (
  IN UINT8         VmxEnable
  )
{
  MSR_IA32_FEATURE_CONTROL_REGISTER Msr;
  CPUID_VERSION_INFO_ECX            Ecx;

  AsmCpuid (CPUID_VERSION_INFO, &Ecx.Uint32, NULL, NULL, NULL);

  ///
  /// Check if VMX is supported
  ///
  if (Ecx.Bits.VMX == 0) {
    return NO_RESET;
  }

  Msr.Uint64 = AsmReadMsr64 (MSR_IA32_FEATURE_CONTROL);

  ///
  /// Need to reset only if locked and VMX state has to be changed.
  ///
  if ((Msr.Bits.Lock == 1) && (Msr.Bits.EnableVmxOutsideSmx != VmxEnable)) {
    return COLD_RESET;
  }

  return NO_RESET;
}

/**
  Compare the flex multiplier setup options against the CPU strap settings
  and in case of mismatch request a reset.

  @param[in] CpuStrapSet    - The current strap setting.
  @param[in] CpuRatio - CpuRatio CPU policy.

  @retval NO_RESET          - No reset is needed.
  @retval WARM_RESET        - Update requires a warm reset.
**/
CPU_RESET_TYPE
ProgramProcessorFlexMultiplier (
  IN CPU_STRAP_SET               *CpuStrapSet,
  IN UINT8                       CpuRatio
  )
{
  UINT64              FlexRatioData;
  UINT64              CurrentClockFlexRatio;
  UINT64              MsrData;
  CPU_RESET_TYPE      ResetType;

  ResetType         = NO_RESET;

  FlexRatioData = (UINT64) CpuRatio;

  DEBUG ((DEBUG_INFO, "Ratio from Policy is 0x%X\n", FlexRatioData));

  ///
  /// Read and save current Flex Ratio data; disregard enable bit (MSR 194h [15:8])
  ///
  MsrData               = AsmReadMsr64 (MSR_FLEX_RATIO);
  CurrentClockFlexRatio = ((RShiftU64 (MsrData, N_MSR_FLEX_RATIO_FLEX_RATIO_OFFSET)) & 0xFF);
  DEBUG ((DEBUG_INFO, "Current Flex Ratio from MSR is 0x%X\n", CurrentClockFlexRatio));
  DEBUG ((DEBUG_INFO, "Current Flex Ratio from CPU Strap: 0x%X\n", CpuStrapSet->FlexRatio));
  ///
  /// Check and set Flex Ratio to requested ratio if possible
  ///
  if (FlexRatioData == CpuStrapSet->FlexRatio) {
    ///
    /// Do nothing, ratio is already set to requested value and enabled
    ///
    DEBUG ((DEBUG_INFO, "No need to set Flex Ratio.\n"));
  } else {
    ///
    /// Set Flex Ratio to user selected value
    ///
    /// Write new data to Flex Ratio register
    /// First clear MSR of any previous value
    ///
    MsrData &= ~(UINT64)B_MSR_FLEX_RATIO_FLEX_RATIO_MASK;

    ///
    /// Enter the new data
    ///
    MsrData |= (LShiftU64 ((FlexRatioData & 0xFF), N_MSR_FLEX_RATIO_FLEX_RATIO_OFFSET));
    MsrData |= B_MSR_FLEX_RATIO_ENABLE_MASK;
    AsmWriteMsr64 (MSR_FLEX_RATIO, MsrData);

    ///
    /// Set Soft Reset Data for Flex Ratio
    ///
    CpuStrapSet->FlexRatio = (UINT32) FlexRatioData;

    ///
    /// Set RESET flag
    ///
    DEBUG ((DEBUG_INFO, "Setting Flex Ratio to 0x%X\n", CpuStrapSet->FlexRatio));
    ResetType |= WARM_RESET;
  }

  return ResetType;
}

/**
  Compare the BIST setup option against the CPU strap setting
  and in case of mismatch request a reset.

  @param[in] CpuStrapSet    - The current strap setting.
  @param[in] BistOnResetPostMem - BistOnResetPostMem CPU Test Config Policy.

  @retval NO_RESET          - No reset is needed.
  @retval WARM_RESET        - Update requires a warm reset.
**/
CPU_RESET_TYPE
BistEnableDisable (
  IN CPU_STRAP_SET     *CpuStrapSet,
  IN UINT8             BistOnReset
  )
{
  if (CpuStrapSet->Bist == BistOnReset) {
    return NO_RESET;
  } else {
    CpuStrapSet->Bist = BistOnReset;
    DEBUG ((DEBUG_INFO, "BIST configuration doesn't match the setup value\n"));
    return WARM_RESET;
  }
}


/**
  Compare the number of active cores setup option against the CPU strap setting
  and in case of mismatch request a reset.

  @param[in] CpuStrapSet    - The current strap setting.
  @param[in] ActiveCoreCount - ActiveCoreCount CPU policy.

  @retval NO_RESET          - No reset is needed.
  @retval WARM_RESET        - Update requires a warm reset.
  @retval COLD_RESET        - Update requires a cold reset.
**/
CPU_RESET_TYPE
SetActiveCores (
  IN CPU_STRAP_SET     *CpuStrapSet,
  IN UINT8             ActiveCoreCount
  )
{
  CPU_RESET_TYPE     ResetType;
  UINT32             Data32;
  UINT32             NumberOfActiveCores;

  ResetType = NO_RESET;

  /* CORE_THREAD_COUNT - msr 0x35
     Symbol      Name        MSB:LSB  Description
     CoreCount   CoreCount   31:16    The Core Count reflects the enabled cores based
                                      on the above thread count and the value of threads_
                                      available (to determine if HT is on) at reset time.

     ThreadCount ThreadCount 15:0     The Thread Count reflects the enabled threads based
                                      on the factory-configured thread count and the value
                                      of the PCH Soft Reset Data register for Client processors
                                      at reset time.

  Read MSR for Active Core and Thread Count.
  */
  Data32                = (UINT32) AsmReadMsr64 (MSR_CORE_THREAD_COUNT);
  NumberOfActiveCores   = (UINT32) ((Data32 >> 16) & 0xFFFF);
  DEBUG ((DEBUG_INFO, "Number of Active Cores = %x\n", NumberOfActiveCores));

  ///
  /// Check if the configuration of "Active Core" matches the BIOS Setup option.
  ///
  if (CpuStrapSet->NumberOfActiveCores != ActiveCoreCount) {
    DEBUG (
            (DEBUG_INFO,
             "NumberOfActiveCores doesn't match the value from Setup = %x / %x\n",
             CpuStrapSet->NumberOfActiveCores,
             ActiveCoreCount)
            );
    CpuStrapSet->NumberOfActiveCores = ActiveCoreCount;
    ResetType |= COLD_RESET;
  }

  return ResetType;
}

/**
  Compare the boot frequency setup option against the boot ratio strap setting
  and in case of mismatch request a reset.

  @param[in] CpuStrapSet    - The current strap setting.
  @param[in] BootFrequency  - BootFrequency CPU policy.

  @retval NO_RESET          - No reset is needed.
  @retval WARM_RESET        - Update requires a warm reset.
**/
CPU_RESET_TYPE
BootRatioEnableDisable (
  IN CPU_STRAP_SET       *CpuStrapSet,
  IN UINT8               BootFrequency
  )
{
  CPU_RESET_TYPE ResetType;
  ResetType = NO_RESET;

  ///
  /// Check if the configuration of BootRatio from Bit12 of strap setting is not aligned with the BootFrequency setup option.
  ///
  if (((CpuStrapSet->BootRatio == 1) && (BootFrequency == 0)) ||
      ((CpuStrapSet->BootRatio == 0) && (BootFrequency > 0))) {
      DEBUG (
              (DEBUG_INFO,
               "Boot Ratio strap setting of %x does not match the BootFrequency policy %x\n",
               CpuStrapSet->BootRatio,
               BootFrequency)
              );
      if (BootFrequency > 0) {
        CpuStrapSet->BootRatio = 1;
      } else {
        CpuStrapSet->BootRatio = 0;
      }
      ResetType |= WARM_RESET;
  }

  return ResetType;
}

/**
  Compare the JTAG power gate setup option against the CPU strap setting
  and in case of mismatch request a reset.

  @param[in] CpuStrapSet    - The current strap setting.
  @param[in] JtagC10PowerGateDisable - JtagC10PowerGateDisable CPU policy.

  @retval NO_RESET          - No reset is needed.
  @retval WARM_RESET        - Update requires a warm reset.
**/
CPU_RESET_TYPE
JtagPowerGateEnableDisable (
  IN CPU_STRAP_SET           *CpuStrapSet,
  IN UINT8                   JtagC10PowerGateDisable
  )
{
  CPU_RESET_TYPE ResetType;

  ResetType = NO_RESET;

  ///
  /// Check if the configuration of "JtagC10PowerGateDisable" from Bit13 of strap setting matches the BIOS Setup option.
  ///
  if (CpuStrapSet->JtagC10PowerGateDisable != JtagC10PowerGateDisable) {
      DEBUG (
              (DEBUG_INFO,
               "JtagC10PowerGateDisable strap setting doesn't match the value from Setup = %x / %x\n",
               CpuStrapSet->JtagC10PowerGateDisable,
               JtagC10PowerGateDisable)
              );
      CpuStrapSet->JtagC10PowerGateDisable = JtagC10PowerGateDisable;
      ResetType |= WARM_RESET;
  }

  return ResetType;
}

/**
  Get strap data from SPI.

  @param[out] CpuStrapData  CPU strap data from SPI

  @return EFI_SUCCESS if data has been fetched successfully
**/
STATIC
EFI_STATUS
GetCpuStrapDataFromSpi (
  OUT UINT16  *CpuStrapData
  )
{
  PCH_SPI_PPI  *SpiPpi;
  EFI_STATUS   Status;
  UINT8        TempBuffer[2];

  Status = PeiServicesLocatePpi (
             &gPchSpiPpiGuid,
             0,
             NULL,
             (VOID**) &SpiPpi
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to locate SPI PPI\n"));
    return FALSE;
  }

  Status = SpiPpi->ReadCpuSoftStrap (SpiPpi, 0, sizeof (UINT16), TempBuffer);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to read image descriptor\n"));
    return FALSE;
  }

  *CpuStrapData = TempBuffer[0] + (TempBuffer[1] << 8);
  return TRUE;
}

/**
Write CPU strap data to SPI.

@param[in] CpuStrapData  Write CPU strap data to SPI

@return EFI_SUCCESS CPU strap data has been Written successfully
@return EFI_ERROR   Unable to write the CPU strap data to Descriptor
**/
STATIC
EFI_STATUS
WriteCpuStrapDataToSpi (
  IN UINT16  CpuStrapData
  )
{
  PCH_SPI_PPI       *SpiPpi;
  EFI_STATUS        Status;
  UINT8             *Buffer;
  SPI_INSTANCE      *SpiInstance;

  Status = PeiServicesLocatePpi (
             &gPchSpiPpiGuid,
             0,
             NULL,
             (VOID**)&SpiPpi
           );

  SpiInstance = SPI_INSTANCE_FROM_SPIPROTOCOL (SpiPpi);
  if (EFI_ERROR(Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to locate SPI PPI\n"));
    return Status;
  }
  Buffer = AllocateZeroPool (sizeof (DESCRIPTOR_SIZE));
  if (Buffer == NULL) {
    DEBUG ((DEBUG_ERROR, "Can't allocate enough memory for Buffer\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  Status = SpiPpi->FlashRead (SpiPpi, FlashRegionDescriptor, 0, DESCRIPTOR_SIZE, Buffer);
  if (EFI_ERROR(Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Read Descriptor from Flash\n"));
    return Status;
  }
  //
  // Updating the CPU Strap data in corresponding offset.
  //
  if (Buffer != NULL) {
    Buffer[SpiInstance->CpuStrapBaseAddr] = CpuStrapData & 0x00FF;
    Buffer[SpiInstance->CpuStrapBaseAddr+1] = (CpuStrapData & 0xFF00) >> 8;
  }

  Status = SpiPpi->FlashErase (SpiPpi, FlashRegionDescriptor, 0, DESCRIPTOR_SIZE);
  if (EFI_ERROR(Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Erase Descriptor from Flash\n"));
    return Status;
  }

  Status = SpiPpi->FlashWrite (SpiPpi, FlashRegionDescriptor, 0, DESCRIPTOR_SIZE, Buffer);
  if (EFI_ERROR(Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Write CPU Strap Data to Flash\n"));
    return Status;
  }

  return Status;
}

/**
  Search through BlockIo PPIs to find UFS BlockIo PPI.

  @param[in]  PeiServices  Pointer to PEI_SERVICES
  @param[out] BlockIoPpi   Instance of UFS BLOCK_IO_PPI
**/
STATIC
BOOLEAN
FindBootUfsBlockIo (
  IN  EFI_PEI_SERVICES               **PeiServices,
  OUT EFI_PEI_RECOVERY_BLOCK_IO_PPI  **BlockIoPpi
  )
{
  EFI_PEI_BLOCK_IO_MEDIA  MediaInfo;
  EFI_STATUS              Status;
  UINTN                   BlockIoInstanceIndex;
  UINTN                   DeviceIndex;

  DeviceIndex = UFS_BOOT_LUN + 1;

  BlockIoInstanceIndex = 0;
  while (TRUE) {
    Status = PeiServicesLocatePpi (
               &gEfiPeiVirtualBlockIoPpiGuid,
               BlockIoInstanceIndex,
               NULL,
               (VOID **) BlockIoPpi
               );
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO, "Failed to find UFS Block IO: %r\n", Status));
      return FALSE;
    }

    ZeroMem (&MediaInfo, sizeof (EFI_PEI_BLOCK_IO_MEDIA));
    Status = (*BlockIoPpi)->GetBlockDeviceMediaInfo (
                              PeiServices,
                              *BlockIoPpi,
                              DeviceIndex,
                              &MediaInfo
                              );
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO, "Failed to read media info from block device: %r\n", Status));
      return FALSE;
    }
    if ((MediaInfo.DeviceType != UfsDevice) || (!MediaInfo.MediaPresent)) {
      BlockIoInstanceIndex++;
    } else {
      break;
    }

  }

  return TRUE;
}

/**
  Write CPU strap data to  UFS.

  @param[in] CpuStrapData  Write CPU strap data to UFS

  @return EFI_SUCCESS CPU strap data has been Written successfully
  @return EFI_ERROR   Unable to write CPU strap data in Descriptor
**/
STATIC
EFI_STATUS
WriteCpuStrapDataToUfs (
  OUT UINT16  CpuStrapData
  )
{
  EFI_PEI_RECOVERY_BLOCK_IO_PPI  *BlockIoPpi;
  EFI_PEI_UFS_WRITE_PPI          *UfsWritePpi;
  EFI_STATUS                     Status;
  EFI_PEI_LBA                    CpuStrapLba;
  UINTN                          UfsBlockBufferSize;
  UINT8                          *UfsBlockBuffer;
  EFI_PEI_SERVICES               **PeiServices;
  EFI_PEI_BLOCK_IO_MEDIA         MediaInfo;
  UINTN                          DeviceIndex;

  UfsWritePpi = NULL;
  DeviceIndex = UFS_BOOT_LUN + 1;
  PeiServices = (EFI_PEI_SERVICES**) GetPeiServicesTablePointer ();

  if (!FindBootUfsBlockIo (PeiServices, &BlockIoPpi)) {
    DEBUG ((DEBUG_INFO, "Boot UFS BlockIo not found\n"));
    return EFI_NOT_FOUND;
  }

  ZeroMem (&MediaInfo, sizeof (EFI_PEI_BLOCK_IO_MEDIA));
  Status = BlockIoPpi->GetBlockDeviceMediaInfo (
                         PeiServices,
                         BlockIoPpi,
                         DeviceIndex,
                         &MediaInfo
                         );

  CpuStrapLba        = (EFI_PEI_LBA) EFI_SIZE_TO_PAGES (UfsStrapAddress);
  UfsBlockBufferSize = EFI_PAGES_TO_SIZE (EFI_SIZE_TO_PAGES (MediaInfo.BlockSize));
  UfsBlockBuffer     = AllocatePages (EFI_SIZE_TO_PAGES (UfsBlockBufferSize));
  if (UfsBlockBuffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  ZeroMem (UfsBlockBuffer, UfsBlockBufferSize);

  Status = BlockIoPpi->ReadBlocks (
                         PeiServices,
                         BlockIoPpi,
                         DeviceIndex,
                         CpuStrapLba,
                         UfsBlockBufferSize,
                         (VOID*) UfsBlockBuffer
                         );
  //
  // updating CPU Strap data to buffer
  //
  UfsBlockBuffer[UFS_CPU_STRAP_OFFSET] = (CpuStrapData & 0x00FF);
  UfsBlockBuffer[UFS_CPU_STRAP_OFFSET + 1] = (CpuStrapData & 0xFF00) >> 8;

  Status = PeiServicesLocatePpi (
               &gEfiPeiUfsWritePpiGuid,
               0,
               NULL,
               (VOID**) &UfsWritePpi
               );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to find Write UFS Block IO PPI\n"));
    return Status;
  }

  Status = UfsWritePpi->WriteUfs (
                         PeiServices,
                         UfsWritePpi,
                         DeviceIndex,
                         CpuStrapLba,
                         UfsBlockBufferSize,
                         (VOID*) UfsBlockBuffer
                         );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Write block UFS\n"));
    return Status;
  }

  return Status;
}

/**
  Get strap data from UFS.

  @param[out] CpuStrapData  CPU strap data from UFS

  @return EFI_SUCCESS if data has been fetched successfuly
**/
STATIC
EFI_STATUS
GetCpuStrapDataFromUfs (
  OUT UINT16  *CpuStrapData
  )
{
  EFI_PEI_RECOVERY_BLOCK_IO_PPI  *BlockIoPpi;
  EFI_STATUS                     Status;
  EFI_PEI_LBA                    CpuStrapLba;
  UINTN                          UfsBlockBufferSize;
  UINT8                          *UfsBlockBuffer;
  EFI_PEI_SERVICES               **PeiServices;
  EFI_PEI_BLOCK_IO_MEDIA         MediaInfo;
  UINTN                          DeviceIndex;

  DeviceIndex = UFS_BOOT_LUN + 1;
  PeiServices = (EFI_PEI_SERVICES**) GetPeiServicesTablePointer ();

  if (!FindBootUfsBlockIo (PeiServices, &BlockIoPpi)) {
    DEBUG ((DEBUG_INFO, "Boot UFS BlockIo not found\n"));
    return EFI_NOT_FOUND;
  }

  ZeroMem (&MediaInfo, sizeof (EFI_PEI_BLOCK_IO_MEDIA));
  Status = BlockIoPpi->GetBlockDeviceMediaInfo (
                         PeiServices,
                         BlockIoPpi,
                         DeviceIndex,
                         &MediaInfo
                         );

  CpuStrapLba        = (EFI_PEI_LBA) EFI_SIZE_TO_PAGES (UfsStrapAddress);
  UfsBlockBufferSize = EFI_PAGES_TO_SIZE (EFI_SIZE_TO_PAGES (MediaInfo.BlockSize));
  UfsBlockBuffer     = AllocatePages (EFI_SIZE_TO_PAGES (UfsBlockBufferSize));
  if (UfsBlockBuffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  ZeroMem (UfsBlockBuffer, UfsBlockBufferSize);

  Status = BlockIoPpi->ReadBlocks (
                         PeiServices,
                         BlockIoPpi,
                         DeviceIndex,
                         CpuStrapLba,
                         UfsBlockBufferSize,
                         (VOID*) UfsBlockBuffer
                         );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to read block from UFS\n"));
    return Status;
  }

  ///
  /// CPU strap location is at offset 0x1C5C6C. BLOCKIO read reads one full block 0x1C5000 to 0x1C6000. Use value only at offset 0xC6C and 0xC6D.
  ///
  *CpuStrapData = UfsBlockBuffer[UFS_CPU_STRAP_OFFSET] + (UfsBlockBuffer[UFS_CPU_STRAP_OFFSET + 1] << 8);
  return Status;
}

/**
  Get CPU strap data from descriptor.

  @param[out] CpuStrapData  CPU strap value from descriptor

  @return EFI_SUCCESS if data has been fetched successfully
**/
STATIC
EFI_STATUS
GetCpuStrapDataFromDescriptor (
  OUT UINT16  *CpuStrapData
  )
{
  if (BootMediaIsUfs ()) {
    return GetCpuStrapDataFromUfs (CpuStrapData);
  } else {
    return GetCpuStrapDataFromSpi (CpuStrapData);
  }
}

/**
  Get CPU strap data.

  @param[out] CpuStrapData  CPU strap value

  @retval TRUE   Fetched data is valid
  @retval FALSE  Fetched data is not valid
**/
STATIC
BOOLEAN
GetCpuStrapData (
  OUT UINT16  *CpuStrapData
  )
{
  EFI_STATUS  Status;

  if (PmcIsSetStrapMsgInterfaceEnabled ()) {
    *CpuStrapData = PmcGetStrapMsgData ();
  } else {
    Status = EFI_SUCCESS;
    *CpuStrapData = 0;
    Status = GetCpuStrapDataFromDescriptor (CpuStrapData);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Failed to get CPU strap data\n"));
      return FALSE;
    } else {
      return TRUE;
    }
  }
  return TRUE;
}

/**
Write CPU strap data to Descriptor.

@param[in] CpuStrapData  CPU strap value

@retval EFI_SUCCESS   data written successfully
@retval EFI_ERROR     Not able to write CPU Strap data
**/
STATIC
EFI_STATUS
WriteCpuStrapDataToDescriptor (
  IN UINT16 CpuStrapData
  )
{
  if (BootMediaIsUfs ()) {
    return WriteCpuStrapDataToUfs (CpuStrapData);
  } else {
    return WriteCpuStrapDataToSpi (CpuStrapData);
  }
}

/**
  Set Cpu Strap and Set Early Power On Configuration setting for feature change.

  @param[in] SiPreMemPolicyPpi    - Address of the SI_PREMEM_POLICY_PPI.
**/
VOID
SetCpuStrapAndEarlyPowerOnConfig (
  IN SI_PREMEM_POLICY_PPI       *SiPreMemPolicyPpi
#if FixedPcdGetBool(PcdBfxEnable) == 1
  , IN SI_POLICY_PPI            *SiPolicyPpi
#endif
  )
{
  EFI_STATUS                  Status;
  CPU_RESET_TYPE              ResetType;
  CPU_STRAP_SET               CpuStrapSet = { 0 };
  UINT16                      CpuStrapSetData;
  EFI_BOOT_MODE               BootMode;
  CPU_CONFIG_LIB_PREMEM_CONFIG  *CpuConfigLibPreMemConfig;
#if FixedPcdGetBool(PcdBfxEnable) == 1
  CPU_CONFIG                    *CpuConfig;
#endif

  ResetType         = NO_RESET;
  CpuStrapSetData   = 0;

  DEBUG ((DEBUG_INFO, "SetCpuStrapAndEarlyPowerOnConfig Start \n"));
  PostCode (0xC0A);

  Status = PeiServicesGetBootMode (&BootMode);
  DEBUG ((DEBUG_INFO, "SetCpuStrapAndEarlyPowerOnConfig: BootMode = %X\n", BootMode));
  if ((Status == EFI_SUCCESS) && (BootMode == BOOT_ON_S3_RESUME)) {
    PmcLockSetStrapMsgInterface ();
    return;
  }
  DEBUG ((DEBUG_INFO, "Set CPU Soft Straps Entry Point\n"));

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuConfigLibPreMemConfigGuid, (VOID *) &CpuConfigLibPreMemConfig);
  ASSERT_EFI_ERROR (Status);
#if FixedPcdGetBool(PcdBfxEnable) == 1
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuConfigGuid, (VOID *) &CpuConfig);
  ASSERT_EFI_ERROR(Status);

  UfsStrapAddress = CpuConfig->UfsStrapAddress;
  DEBUG ((DEBUG_INFO, "UfsStrapAddress: 0x%X\n", UfsStrapAddress));
#endif
  if (GetCpuStrapData (&CpuStrapSetData)) {
    *((UINT16 *) (&CpuStrapSet))  = CpuStrapSetData;
    DEBUG ((DEBUG_INFO, "Current CPU Strap Data = 0x%04X\n", CpuStrapSetData));
    ResetType |= SetActiveCores (&CpuStrapSet, (UINT8) CpuConfigLibPreMemConfig->ActiveCoreCount1);
    ResetType |= BistEnableDisable (&CpuStrapSet, (UINT8) CpuConfigLibPreMemConfig->BistOnReset);

    ///
    /// Perform Flex Ratio if processor is fused to perform Flex Ratio
    ///
    if ((AsmReadMsr64 (MSR_FLEX_RATIO) & B_MSR_FLEX_RATIO_ENABLE_MASK) == B_MSR_FLEX_RATIO_ENABLE_MASK) {
      ResetType |= ProgramProcessorFlexMultiplier (&CpuStrapSet, (UINT8) CpuConfigLibPreMemConfig->CpuRatio);
    }
    ResetType |= BootRatioEnableDisable (&CpuStrapSet, (UINT8) CpuConfigLibPreMemConfig->BootFrequency);
    ResetType |= JtagPowerGateEnableDisable (&CpuStrapSet, (UINT8) CpuConfigLibPreMemConfig->JtagC10PowerGateDisable);

    if (ResetType != NO_RESET) {
      CpuStrapSetData = *((UINT16 *) (&CpuStrapSet));
      DEBUG ((DEBUG_INFO, "New CPU Strap Data = 0x%04X\n", CpuStrapSetData));
      PmcSetStrapMsgData (CpuStrapSetData);
      Status = WriteCpuStrapDataToDescriptor (CpuStrapSetData);
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "Failed to Write CPU strap data flash\n"));
      }
    }
  }
  PmcLockSetStrapMsgInterface ();

  ResetType |= CheckVmxIfNeedReset ((UINT8) CpuConfigLibPreMemConfig->VmxEnable);
  if (ResetType != NO_RESET) {
    DEBUG ((DEBUG_INFO, "Cpu straps changed, performing reset - ResetType = %x\n", ResetType));
    PostCode (0xC13);
    PerformWarmOrColdReset (ResetType);
  }
  DEBUG ((DEBUG_INFO, "SetCpuStrapAndEarlyPowerOnConfig Done \n"));
  PostCode (0xC14);
}

