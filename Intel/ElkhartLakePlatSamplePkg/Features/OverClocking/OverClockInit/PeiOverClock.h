/** @file
  PEI Header for Overclocking

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2018 Intel Corporation.

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
#ifndef __PeiOverClock__H__
#define __PeiOverClock__H__
#ifdef __cplusplus
extern "C"
{
#endif

#include "Platform.h"
#include <PlatformClock.h>
#include <PlatformBoardId.h>
#include <SetupVariable.h>
#include <Ppi/Smbus2.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <Uefi/UefiBaseType.h>
#include <Library/PeiServicesLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/TimerLib.h>
#include <Ppi/Wdt.h>
#include <SaRegs.h>
#include <Ppi/OverClockPpi.h>

#define MSR_CORE_THREAD_COUNT               0x35
#define MSR_PLATFORM_INFO                   0xCE
#define MAX_NON_TURBO_RATIO_OFFSET          8
#define MAX_NON_TURBO_RATIO_MASK            0xff
#define MAX_EFFICIENCY_RATIO_MASK           0xff
#define MAX_EFFICIENCY_RATIO_OFFSET         40

#define MSR_FLEX_RATIO                      0x194
  #define FLEX_RATIO                        (0xFF << 8)
  #define ENABLE_FLEX                       (1 << 16)
  #define MAX_EXTRA_VOLTAGE                 0xFF
  #define OVERCLOCKING_BINS                 (0x7 << 17)
#define MSR_TURBO_RATIO_LIMIT               0x1ad
#define MAX_RATIO_LIMIT_4C_OFFSET           24
#define MAX_RATIO_LIMIT_3C_OFFSET           16
#define MAX_RATIO_LIMIT_2C_OFFSET           8
#define MAX_RATIO_LIMIT_1C_OFFSET           0
#define MAX_RATIO_LIMIT_1C_MASK             0x000000ff
#define MAX_RATIO_LIMIT_2C_MASK             0x0000ff00
#define MAX_RATIO_LIMIT_3C_MASK             0x00ff0000
#define MAX_RATIO_LIMIT_4C_MASK             0xff000000

#define MSR_PACKAGE_POWER_SKU_UNIT          0x606
#define PACKAGE_POWER_UNIT_MASK             0xF
#define PACKAGE_MAX_POWER_MASK              ((UINT64) 0x7FFF << 32)
#define PACKAGE_MAX_POWER_OFFSET            32
#define PACKAGE_MIN_POWER_MASK              (0x7FFF << 16)
#define PACKAGE_MIN_POWER_OFFSET            16
#define PACKAGE_TDP_POWER_MASK              (0x7FFF)

#define MSR_TURBO_POWER_LIMIT                   0x610
#define POWER_LIMIT_MASK                    (0x7FFF)    // Bits 14:0 and 46:32
#define POWER_LIMIT_1_MASK                  (0x7FFF)    // Bits 14:0
#define POWER_LIMIT_2_MASK                  ((UINT64) 0x7FFF << 32) // Bits 46:32
#define POWER_LIMIT_2_OFFSET                32

#define MSR_PACKAGE_POWER_SKU               0x614
#define MSR_PCIE_PLLGEN3                    0x61E

#define PEG_DMI_RATIO_MASK                  0x3
#define PCIE_PLL_MASK                       (1 << 2)
#define PCIE_PLL_OFFSET                     2
#define FW_DMI_RATIO_MASK                   0x7
#define LONG_RESET_BIT                      BIT3

#define SIO_GPIO_DATA_REG3                  0x0E

#define CK505_VENDOR_ID                     0x06

#define H2M_MSG1_OFFSET                     0x4C         // Host to ME register in HECI controller
#define H2M_ICC_MESSAGE                     0x60000000   // In H2M register, bits[31..28] indicates message type. 6- ICC message
#define H2M_BCLK_RAMP_EN_BIT                BIT0         // Bits[27..0]  indicate message. Bit 0 enable ramp programming
#define M2H_MSG_ACK_MASK                    0xF0000000   // In FWSTS register, bit[31..28] indicate ack type.
#define M2H_ICC_MSG_ACK                     0x60000000   // ICC message Ack reports 6(ICC Ack) in the type
#define R_ME_FWSTS3_CORE_RESET_MASK         0x00000010
#define CPU_FILTER_PLL_MASK                 0x0020
#define CPU_FILTER_PLL_OFFSET               5
#define CPU_OCS_GPIO_MASK                   0x00000100
#define CPU_OCS_GPIO_OFFSET                 8
#define PCIE_RATIO_DIS_MASK                 0x00040000
#define PCIE_RATIO_DIS_OFFSET               18

// Masks for the combined GEN_PMCON_1 & GEN_PMCON_2 registers (PCICfgSpace at B=0:D=1F:F=0:Off=A0)
#define GEN_PMCON_12_DISB_MASK (1<<(16+7)) // DISB actually in GEN_PMCON_2 bit 7 (but code expects 32 DWORD)
#define GEN_PMCON_12_SR_MASK   (1<<(16+5)) // SR   actually in GEN_PMCON_2 bit 5 (but code expects 32 DWORD)

//
// Define function prototypes
//

/**
  This function will perform the BCLK overclocking flow which
  handles FilterPll, PciePll, and DMI/PEG ratio programming.

  @param[in] VOID

  @retval EFI_SUCCESS          Function successfully executed.

  Appropiate failure code on error.
**/
EFI_STATUS
PerformBclkOcFlow (
  VOID
  );

/**
  Programs CPU Bus speed based on Setup variable.

  @param[in] CpuSetup          Pointer to the CPU_SETUP buffer
  @param[in] SmBusPpi          Pointer to the EFI_PEI_SMBUS2_PPI

  @retval EFI_SUCCESS          Function successfully executed.
**/
EFI_STATUS
ProgramBusSpeed (
  IN  CPU_SETUP                *CpuSetup,
  IN  EFI_PEI_SMBUS2_PPI       *SmbusPpi
  );

/**
  Disables Bus Speed override.

  @param[in] SmBusPpi         Pointer to the EFI_PEI_SMBUS2_PPI

  @retval EFI_SUCCESS         Function successfully executed.

**/
EFI_STATUS
DisableBusSpeedOverride (
  IN  EFI_PEI_SMBUS2_PPI       *SmbusPpi
  );

/**
  Programs Processor Multiplier using FLEX_RATIO MSR(0x194).
  This ProgramProcessorMultiplier Override needs a CPU Only Reset.
  Flex Override in Flex Ratio MSR assuming the OverclockPei Driver will
  always get called before Memroy.

  @param[in] SetupData        Pointer to the SETUP_DATA
**/
VOID
ProgramProcessorMultiplier (
  IN  CPU_SETUP              *CpuSetup
  );

/**
  This function implements the Recovery logic.

  @param[in] SetupData         Pointer to the SETUP_DATA buffer
  @param[in] SaSetup           Pointer to the SA_SETUP buffer
  @param[in] CpuSetup          Pointer to the CPU_SETUP buffer
  @param[in] WdtTimeOut        Wdt Time Out Status
  @param[in] Ck505Present      Ck505 Present Status

  @retval EFI_SUCCESS          Function successfully executed.
**/
EFI_STATUS
ConfigFailedBootRecovery (
  IN SETUP_DATA               *SetupData,
  IN SA_SETUP                 *SaSetup,
  IN CPU_SETUP                *CpuSetup,
  IN BOOLEAN                  WdtTimeOut,
  IN BOOLEAN                  Ck505Present
  );

/**
  This function will start the Watchdog Timer.

  @param[in] TimeoutValue       Time out value in seconds

  @retval EFI_SUCCESS           Function successfully executed.

  Appropiate failure code on error.
**/
EFI_STATUS
StartTimer (
  IN UINT32                   TimeoutValue
  );

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
