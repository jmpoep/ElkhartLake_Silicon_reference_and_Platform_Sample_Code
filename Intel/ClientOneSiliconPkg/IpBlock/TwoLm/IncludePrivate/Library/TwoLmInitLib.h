/** @file
  Header file for 2LM initialization library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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
#ifndef TWOLM_INIT_LIB_H_
#define TWOLM_INIT_LIB_H_

#include <Uefi.h>
#include <Library/CpuRegbarAccessLib.h>
#include <Library/PciSegmentLib.h>
#include <TwoLmConfig.h>
#include <Register/TwoLmRegs.h>
#include <Register/SaRegsHostBridge.h>
#include <Library/FmssMbLib.h>
#include <Library/PeiDxeSmmTwoLmLib.h>

#define MEM_EQU_1GB        0x40000000ULL

#define SA_2LM_DEV_NUM     0x03
#define SA_2LM_FUN0_NUM    0x00
#define SA_2LM_FUN7_NUM    0x07

///
/// PCIe Capability IDs
///
#define PCIE_CAPID                    0x10
#define PM_CAPID                      0x01
#define MFVC_CAPID                    0x08
#define L1PM_CAPID                    0x1E
#define SEC_PCIE_CAPID                0x19
#define DATA_LINK_FEATURE_CAPID       0x25
#define PHY_LAYER_16_CAPID            0x26
#define PHY_LAYER_16_MARGINING_CAPID  0x27

#define PCIE_CAP_SIZE                     0x34
#define MFVC_CAP_SIZE                     0x28
#define L1PM_CAP_SIZE                     0x10
#define SEC_PCIE_CAP_SIZE                 0x14
#define DATA_LINK_FEATURE_CAP_SIZE        0x10
#define PHY_LAYER_16_CAP_SIZE             0x30
#define PHY_LAYER_16_MARGINING_CAP_SIZE   0x18

#define ASTRO_OFFSET       0x3800

//
// Structure for Early Power on Configuration (EPOC) for 2LM.
//
typedef union {
  struct {
    UINT32 TwoLm     : 1;  ///< Bit 0 - 0 = 1LM mode 1 = 2LM mode
    UINT32 Reserved  : 31; ///< Bits 31:1 - Reserved
  } Bits;
  UINT32 Uint32;
} TWOLM_EPOC_SET;

/**
This function performs any early configuration of 2LM if needed.

**/
VOID
EFIAPI
TwoLmEarlyConfig (
  );

/**
This function does the basic configurations of IPs and issues the Mailbox commands
to find out the Far Memory region and its size which would be used by the MRC phase
in creating the memory map.

@param[in]      TwoLmConfig              2LM Config block.

@retval EFI_SUCCESS            Successfully initialized Pre-Mem configurations.
**/
EFI_STATUS
EFIAPI
TwoLmPreMemInit (
   IN TWOLM_PREMEM_CONFIG      *TwoLmPreMemConfig
  );


/**
This function does the basic configurations of FMHC and Astro controller
This function will be called only if the 2LM mode is enabled in the policy.

@param[in]      MemoryMapData            MRC Memory map data structure to pass DDR Size, TOLUD, Remap values etc.
@param[in]      MemBootMode              Mem boot mode value as a result of detected near mem size

@retval EFI_SUCCESS            Successfully initialized Post-Mem configurations.
**/
EFI_STATUS
EFIAPI
TwoLmPostDdrInit (
  IN UINT32 NearMemorySize,
  IN UINT32 ToludBase,
  IN UINT32 RemapBase,
  IN UINT32 RemapLimit,
  IN UINT8 MemBootMode
  );


/**
This function handles all post mem activities for 2LM feature.

@retval EFI_SUCCESS      Successfully initialized Post-Mem configurations.
**/
EFI_STATUS
EFIAPI
TwoLmPostMemInit (
  );


/**
This function would issue Identify2lmModuleInfo  Mailbox Command
And parse the output payload to store the required information in 2lm info HOB
to be used by the other boot stages.

@param[in]      TwoLmInfo      2LM HOB which will have necessary values to initialize FMHC.

@retval EFI_SUCCESS            Successfully retrieve 2LM module info
**/
EFI_STATUS
EFIAPI
GetTwoLmModuleInfo (
  IN TWOLM_INFO_HOB *TwoLmInfoHob
  );


/**
This function would issue QueryRegion  Mailbox Command
And parse the output payload to store the required information in 2lm info HOB
to be used by the other boot stages.

@param[in]      TwoLmInfo      2LM HOB which will have necessary values to initialize FMHC.

@retval EFI_SUCCESS            Successfully retrieve region info
**/
EFI_STATUS
EFIAPI
GetQueryRegionInfo (
  IN TWOLM_INFO_HOB *TwoLmInfoHob
  );


/**
This function would issue SetHwParametersCommand  Mailbox Command to set the HW parameters
of far memory device as per internal/external user selection.
HW Parameter must be sent for every PERST cycle (cold or warm boot).
The value is only stick over low power state but not PERST

@param[in]      TwoLmConfig            2LM Config block.

@retval         EFI_SUCCESS            Successful completion of command
**/
EFI_STATUS
EFIAPI
SetHardwareParameters (
   IN TWOLM_PREMEM_CONFIG  *TwoLmPreMemConfig
  );

#endif /* TWOLM_INIT_LIB_H_ */
