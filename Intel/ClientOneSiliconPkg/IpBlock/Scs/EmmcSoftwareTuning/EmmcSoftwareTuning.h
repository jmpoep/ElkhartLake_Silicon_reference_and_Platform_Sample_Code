/** @file
  Internal header file for EmmcSoftwareTuning module

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

#ifndef _EMMC_SOFTWARE_TUNING_H_
#define _EMMC_SOFTWARE_TUNING_H_

#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/TimerLib.h>
#include <ScsConfig.h>
#include <Register/ScsSdRegs.h>
#include <Register/PchRegs.h>

#include <IndustryStandard/Emmc.h>
#include <IndustryStandard/Pci30.h>

#define BLOCK_LENGTH                          512

/**
  Enable access to integrated eMMC MMIO.

  @param[in] EmmcPciConfig  eMMC PCI config space
  @param[in] EmmcMmio       eMMC MMIO address
**/
VOID
EmmcEnableMmio (
  IN UINT64  EmmcPciConfig,
  IN UINT32  EmmcMmio
  );

/**
  Disable MMIO access to integrated eMMC.

  @param[in] EmmcPciConfig  eMMC PCI config space
**/
VOID
EmmcDisableMmio (
  IN UINT64  EmmcPciConfig
  );

/**
  Initializes SD bus of the eMMC controller.

  @param[in] EmmcMmio  eMMC MMIO address

  @return Status of the bus initialization
**/
EFI_STATUS
EmmcInitializeBus (
  IN UINT32  EmmcMmio
  );

/**
  Reads single block from eMMC card.

  @param[in]  EmmcMmio    eMMC MMIO address
  @param[in]  Lba         Block address
  @param[in]  BufferSize  Size of the buffer
  @param[out] Buffer      Caller allocated read buffer

  @return Status of the block read operation
**/
EFI_STATUS
EmmcReadSingleBlock (
  IN  UINT32    EmmcMmio,
  IN  EFI_LBA  Lba,
  IN  UINT32   BufferSize,
  OUT VOID     *Buffer
  );

/**
  Writes single block to eMMC card.

  @param[in] EmmcMmio    eMMC MMIO address
  @param[in] Lba         Block address
  @param[in] BufferSize  Size of the buffer
  @param[in] Buffer      Caller allocated block buffer

  @return Status of the write operation
**/
EFI_STATUS
EmmcWriteSingleBlock (
  IN UINT32    EmmcMmio,
  IN EFI_LBA  Lba,
  IN UINT32   BufferSize,
  IN VOID     *Buffer
  );

/**
  Check if block is write protected.

  @param[in] EmmcMmio  eMMC MMIO address
  @param[in] Lba       Block address

  @retval TRUE   Block is write protected or test failed
  @retval FALSE  Block is not write protected
**/
BOOLEAN
EmmcIsBlockWriteProtected (
  IN UINT32    EmmcMmio,
  IN EFI_LBA  Lba
  );

/**
  Initialize eMMC card.

  @param[in] EmmcMmio        eMMC MMIO address
  @param[in] DriverStrength  Driver strength to be used in HS400

  @return Card initialization status
**/
EFI_STATUS
EmmcInitializeCard (
  IN UINT32                     EmmcMmio,
  IN SCS_EMMC_DRIVER_STRENGTH   DriverStrength
  );

#endif
