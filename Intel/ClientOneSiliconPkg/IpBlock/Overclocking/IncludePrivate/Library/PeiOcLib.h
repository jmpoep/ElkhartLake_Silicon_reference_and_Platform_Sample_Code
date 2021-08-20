/** @file
  Header file for overclocking initializations.

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
#ifndef _PEI_OC_LIB_H_
#define _PEI_OC_LIB_H_

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/BaseMemoryLib.h>
#include <Ppi/SiPolicy.h>
#include <CpuAccess.h>
#include <Ppi/Wdt.h>
#include <SaPolicyCommon.h>

//
//  OC Mailbox MSR
//
#define MSR_OC_MAILBOX        0x00000150
#define OC_LIB_WAIT_TIMEOUT   5000  ///< 5 milliseconds

//
//  OC Mailbox commands
//
#define OC_LIB_CMD_GET_OC_CAPABILITIES              0x01
#define OC_LIB_CMD_GET_PER_CORE_RATIO_LIMIT         0x02
#define OC_LIB_CMD_GET_VOLTAGE_FREQUENCY            0x10
#define OC_LIB_CMD_SET_VOLTAGE_FREQUENCY            0x11
#define OC_LIB_CMD_GET_MISC_GLOBAL_CONFIG           0x14
#define OC_LIB_CMD_SET_MISC_GLOBAL_CONFIG           0x15
#define OC_LIB_CMD_GET_DDR_CAPABILITIES             0x03
#define OC_LIB_CMD_GET_MISC_TURBO_CONTROL           0x18
#define OC_LIB_CMD_SET_MISC_TURBO_CONTROL           0x19
#define OC_LIB_CMD_GET_AVX_RATIO_OFFSET             0x1A
#define OC_LIB_CMD_SET_AVX_RATIO_OFFSET             0x1B
#define OC_LIB_CMD_SET_REALTIME_MEMORY_STATUS       0x0A
#define OC_LIB_CMD_GET_REALTIME_MEMORY_STATUS       0x0B
#define OC_LIB_CMD_GET_FUSED_P0_RATIO_VOLTAGE       0x07

//
//  OC Mailbox completion codes
//
#define OC_LIB_COMPLETION_CODE_SUCCESS              0x00
#define OC_LIB_COMPLETION_CODE_OC_LOCKED            0x01
#define OC_LIB_COMPLETION_CODE_INVALID_DOMAIN       0x02
#define OC_LIB_COMPLETION_CODE_MAX_RATIO_EXCEEDED   0x03
#define OC_LIB_COMPLETION_CODE_MAX_VOLTAGE_EXCEEDED 0x04
#define OC_LIB_COMPLETION_CODE_OC_NOT_SUPPORTED     0x05
#define OC_LIB_COMPLETION_CODE_WRITE_FAILED         0x06
#define OC_LIB_COMPLETION_CODE_READ_FAILED          0x07

//
// Domain ID definitions
//
#define OC_LIB_DOMAIN_ID_DDR                0x00
#define OC_LIB_DOMAIN_ID_IA_CORE            0x00
#define OC_LIB_DOMAIN_ID_GT                 0x01
#define OC_LIB_DOMAIN_ID_RING               0x02
#define OC_LIB_DOMAIN_ID_SYSTEM_AGENT       0x04
#define OC_LIB_DOMAIN_ID_MEMORY_CONTROLLER  0x06

//
// Bit 10 is the S11.0.10V sign bit
//
#define FIXED_POINT_SIGN_BIT_MASK 0x0400
#define INT16_SIGN_BIT_MASK       0x8000

//
//  Voltage Conversion defines
//
#define MILLIVOLTS_PER_VOLT  1000
#define MAX_TARGET_MV      4095
#define MAX_OFFSET_MV      500

#define CONVERT_TO_FIXED_POINT_VOLTS  0
#define CONVERT_TO_BINARY_MILLIVOLT   1

//
// Masks and offsets
//
#define BIT0_MASK             0x1
#define MAX_RATIO_MASK        0x0000007F
#define VOLTAGE_TARGET_MASK   0x0007FF80
#define VOLTAGE_TARGET_OFFSET 7
#define VOLTAGE_MODE_MASK     0x00080000
#define VOLTAGE_MODE_OFFSET   19
#define VOLTAGE_OFFSET_MASK   0x7FF00000
#define VOLTAGE_OFFSET_OFFSET 20
#define QCLK_RATIO_MASK         0x000000FF
#define MC_REF_CLK_MASK         0x00000100
#define MC_REF_CLK_OFFSET       8
#define NUM_DDR_CHANNELS_MASK   0x00000C00
#define NUM_DDR_CHANNELS_OFFSET 10

#define OC_CAPS_MAX_RATIO_MASK              0x000000FF
#define OC_CAPS_RATIO_SUPPORT_MASK          0x00000100
#define OC_CAPS_RATIO_SUPPORT_OFFSET        8
#define OC_CAPS_OVERRIDE_SUPPORT_MASK       0x00000200
#define OC_CAPS_OVERRIDE_SUPPORT_OFFSET     9
#define OC_CAPS_OFFSET_SUPPORT_MASK         0x00000400
#define OC_CAPS_OFFSET_SUPPORT_OFFSET       10
#define AVX2_RATIO_OFFSET_MASK              0x000003E0
#define AVX2_RATIO_OFFSET_OFFSET            5
#define AVX3_RATIO_OFFSET_MASK              0x00007C00
#define AVX3_RATIO_OFFSET_OFFSET            10
#define MISC_TURBO_RING_DOWNBIN_MASK        0x00000002
#define MISC_TURBO_RING_DOWNBIN_OFFSET      1
#define FUSED_P0_RATIO_MASK                 0x000000FF
#define FUSED_P0_VOLTAGE_MASK               0x000FFF00
#define FUSED_P0_VOLTAGE_OFFSET             8
#define MISC_GLOBAL_BCLK_ADAPTIVE_OFFSET    2
#define MISC_GLOBAL_FIVR_EFFICIENCY_OFFSET  1
#define MISC_GLOBAL_CFG_COMMAND_MASK        0x00000007

//
// Voltage offset definitions
//
#define OC_LIB_VOLTAGE_DO_NOT_UPDATE  0xFFFF

///
///  Expanded Overclocking Mailbox interface defintion, contains command id/completion code,
///  input parameters and the run/busy bit
///
typedef union _OC_MAILBOX_COMMAND {
  UINT32 InterfaceData;
  struct {
    UINT8 CommandCompletion : 8; ///< Command ID and completion code
    UINT8 Param1            : 8; ///< Parameter 1, generally used to specify the CPU Domain ID
    UINT8 Param2            : 8; ///< Parameter 2, only current usage is as a core index for ratio limits message
    UINT8 Reserved          : 7; ///< Reserved for future use
    UINT8 RunBusy           : 1; ///< Run/Busy bit. This bit is set by BIOS to indicate the mailbox buffer is ready. pcode will clear this bit after the message is consumed.
  } Fields;
} OC_MAILBOX_COMMAND;

///
/// Consolidated OC mailbox command structure containing both data and interface information
///
typedef struct _OC_MAILBOX_ITEM {
  UINT32             Data; ///< OC Mailbox read/write data
  OC_MAILBOX_COMMAND Interface; ///< OC mailbox interface
} OC_MAILBOX_ITEM;

///
///  High Level Voltage/Frequency data required for setting v/f requests on all CPU domains
///
typedef struct {
  UINT8  MaxOcRatio; ///< Max overclocking ratio limit for given CPU domain id
  UINT8  VoltageTargetMode; ///< Voltage Mode selection; <b>0: Adaptive</b>, 1: Override
  UINT16 VoltageTarget; ///< Voltage target specified in millivolts
  INT16  VoltageOffset; ///< Voltage offset specified in millivolts. Can be positive or negative offset.
} VOLTAGE_FREQUENCY_SETTINGS;

///
///  Expanded Voltage Frequency mailbox information in the mailbox command format
///
typedef struct {
  UINT32 MaxOcRatio       : 8;  ///< Max overclocking ratio limit for given CPU domain id
  UINT32 VoltageTargetU12 : 12; ///< Voltage target represented in unsigned fixed point U12.2.10V format
  UINT32 TargetMode       : 1;  ///< Voltage mode selection; <b>0: Adaptive</b>, 1: Override
  UINT32 VoltageOffsetS11 : 11; ///< Voltage offset represented in signed fixed point S11.0.10V format
} VF_MAILBOX_COMMAND_DATA;

///
///  High Level DDR capabilities data used to pass into the overclocking library for final
///  mailbox message creation.
///
typedef struct {
  UINT8   QclkRatio; ///< Qclk Ratio
  BOOLEAN McReferenceClk; ///< Memory Controller Reference Clock 0: 133 MHz, 1: 100 MHz
  UINT8   NumDdrChannels; ///< Number of DDR Channels
} DDR_CAPABILITIES_ITEM;


///
///  High level Voltage/Frequency information used to pass into the overclocking library
///  for the final mailbox message creation.
///
typedef struct {
  VOLTAGE_FREQUENCY_SETTINGS VfSettings; ///< Structure containing the voltage/frequency information
  UINT8                      DomainId; ///< CPU Domain ID
} VOLTAGE_FREQUENCY_ITEM;

///
///  High level OC Capabilities information used to pass into the overclocking library
///  for the final mailbox message creation.
///
typedef struct {
  UINT8   MaxOcRatioLimit;  ///< Max overclocking ratio limit of specified CPU domain
  BOOLEAN RatioOcSupported; ///< Ratio based overclocking support; 0: Not Supported, 1: Supported
  BOOLEAN VoltageOverridesSupported; ///< Voltage override support; 0: Not Supported, 1: Supported
  BOOLEAN VoltageOffsetSupported;    ///< Voltage offset support; 0: Not Supported, 1: Supported
  UINT8   DomainId; ///< CPU Domain ID
} OC_CAPABILITIES_ITEM;

///
/// High level per core ratio limit information used to pass into the overclocking library
/// for the final mailbox message creation.
///
typedef struct {
  UINT8 MaxOcRatioLimit1C; ///< Max 1-Core overclocking ratio limit
  UINT8 MaxOcRatioLimit2C; ///< Max 2-Core overclocking ratio limit
  UINT8 MaxOcRatioLimit3C; ///< Max 3-Core overclocking ratio limit
  UINT8 MaxOcRatioLimit4C; ///< Max 4-Core overclocking ratio limit
  UINT8 MaxOcRatioLimit5C; ///< Max 5-Core overclocking ratio limit
  UINT8 MaxOcRatioLimit6C; ///< Max 6-Core overclocking ratio limit
  UINT8 MaxOcRatioLimit7C; ///< Max 7-Core overclocking ratio limit
  UINT8 MaxOcRatioLimit8C; ///< Max 8-Core overclocking ratio limit
  UINT8 Index; ///< Index selector; 0: 1C to 4C, 1: 5C to 8C
} CORE_RATIO_LIMITS_ITEM;

///
///  High level AVX Ratio Offset information used to pass into the overclocking library
///  for the final mailbox message creation.
///
typedef struct {
  UINT8                      Avx2Ratio; ///< Avx 2 ratio
  UINT8                      Avx3Ratio; ///< Avx 3 ratio
} AVX_RATIO_ITEM;


///
/// OC Library Function Prototypes
///
/**
  Gets the Voltage and Frequency information for a given CPU domain

  @param[out] *VfSettings
  @param[out] *LibStatus

  @retval EFI_STATUS
**/
EFI_STATUS
EFIAPI GetVoltageFrequencyItem (
  OUT VOLTAGE_FREQUENCY_ITEM *VfSettings,
  OUT UINT32                 *LibStatus
  );

/**
  Sets the Voltage and Frequency information for a given CPU domain

  @param[in]  *VfSettings
  @param[out] *LibStatus

  @retval EFI_STATUS
**/
EFI_STATUS
EFIAPI SetVoltageFrequencyItem (
  IN VOLTAGE_FREQUENCY_ITEM VfSettings,
  OUT UINT32                *LibStatus
  );

/**
  Get the fused P0 ratio and voltage

  @param[out] *FusedP0Voltage in millivolt units
  @param[out] *FusedP0Ratio
  @param[out] *LibStatus

  @retval EFI_STATUS
**/
EFI_STATUS
EFIAPI
GetP0RatioVoltage (
  OUT UINT16 *FusedP0Voltage,
  OUT UINT16 *FusedP0Ratio,
  OUT UINT32 *LibStatus
  );

/**
  Get the overclocking capabilities for a given CPU Domain

  @param[out] *OcCapabilities
  @param[out] *LibStatus

  @retval EFI_STATUS
**/
EFI_STATUS
EFIAPI GetOcCapabilities (
  OUT OC_CAPABILITIES_ITEM *OcCapabilities,
  OUT UINT32               *LibStatus
  );

/**
  Converts the input voltage target to the fixed point U12.2.10 Volt format or
  the Binary millivolts representation based on the ConversionType

@param[in]  InputVoltageTarget
@param[out] *OutputVoltageTarget
@param[in]  ConversionType - 0:fixed point, 1:Binary millivolts
**/
VOID
ConvertVoltageTarget (
  IN UINT16  InputVoltageTarget,
  OUT UINT16 *OutputVoltageTarget,
  IN UINT8   ConversionType
  );

/**
  Converts the input votlage Offset to the fixed point S11.0.10 Volt format or
  to Binary millivolts representation based on the ConversionType.

  @param[in]  InputVoltageOffset
  @param[out] *OutputVoltageOffset
  @param[in]  ConversionType - 0:fixed point, 1:Signed Binary millivolts
**/
VOID
ConvertVoltageOffset (
  IN INT16  InputVoltageOffset,
  OUT INT16 *OutputVoltageOffset,
  IN UINT8  ConversionType
  );

/**
  Converts the input data to valid mailbox command format based on CommandID

@param[in]  InputData
@param[out] *MailboxData
@param[in]  CommandId
**/
VOID
ConvertToMailboxFormat (
  IN VOID             *InputData,
  OUT OC_MAILBOX_ITEM *MailboxData,
  IN UINT32           CommandId
  );

/**
  Gets the AVX Ratio Offset

  @param[out] *AvxRatioOffset - The AVX ratio offset value read from OC mailbox.
  @param[out] *LibStatus - OC mailbox library return code

  @retval EFI_STATUS
**/
EFI_STATUS
EFIAPI
GetAvxRatioOffset (
  OUT AVX_RATIO_ITEM   *AvxRatioOffset,
  OUT UINT32           *LibStatus
  );

/**
  Sets the AVX Ratio Offset

  @param[in] AvxRatioOffset - The AVX ratio offset value to program to OC mailbox.
  @param[out] *LibStatus - OC mailbox library return code

  @retval EFI_STATUS
**/
EFI_STATUS
EFIAPI
SetAvxRatioOffset (
  OUT AVX_RATIO_ITEM   AvxRatioOffset,
  OUT UINT32           *LibStatus
  );

/**
  Initializes pre-memory Overclocking settings in the processor.

  @param[in] *SiPreMemPolicyPpi - SiPreMemPolicyPpi Pointer to Si Policy Ppi instance

  @retval EFI_SUCCESS
**/
EFI_STATUS
EFIAPI
CpuOcInitPreMem (
  IN SI_PREMEM_POLICY_PPI *SiPreMemPolicyPpi
  );

/**
  Initializes Overclocking settings in the processor.

  @param[in] *OcConfig - OcConfig Instance of OVERCLOCKING_PREMEM_CONFIG

  @retval EFI_SUCCESS
**/
EFI_STATUS
SaOcInit (
  IN OVERCLOCKING_PREMEM_CONFIG *OcConfig
  );

#endif
