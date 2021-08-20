/** @file
  Header file for Platform Boards Configurations.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2018 Intel Corporation.

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

#ifndef _PLATFORM_BOARD_CONFIG_H
#define _PLATFORM_BOARD_CONFIG_H

#include <ConfigBlock.h>
#include <PchPolicyCommon.h>
#include <MemoryConfig.h>
#include <Library/GpioConfig.h>

#define MAX_GPIO_PINS             100
#define MAX_PRE_MEM_GPIO_PINS     20

#define IS_ALIGNED(addr, size) (((addr) & (size - 1)) ? 0 : 1)
#define ALIGN16(size)          (IS_ALIGNED(size, 16) ? size : ((size + 16) & 0xFFF0))

#define BOARD_CONFIG_BLOCK_PEI_PREMEM_VERSION  0x00000001
#define BOARD_CONFIG_BLOCK_PEI_POSTMEM_VERSION 0x00000001
#define BOARD_CONFIG_BLOCK_DXE_VERSION 0x00000001
#define BOARD_NO_BATTERY_SUPPORT 0
#define BOARD_REAL_BATTERY_SUPPORTED BIT0
#define BOARD_VIRTUAL_BATTERY_SUPPORTED BIT1

//
// ACPI table information used to update tables thru PCD
//
#define ACPI_OEM_TABLE_ID_EHL             0x544C552D4C4845   // EHL-ULT

//
// GPIO states mapping
//
#define PIN_GPIO_ACTIVE_LOW 0
#define PIN_GPIO_ACTIVE_HIGH 1

#pragma pack(1)

typedef struct {
  CONFIG_BLOCK_HEADER  Header;               ///< Offset 0-27 Config Block Header
} BOARD_CONFIG_BLOCK;

typedef struct {
  UINT8 GpioSupport;
  UINT32 WakeGpioNo;
  UINT8 HoldRstExpanderNo;
  UINT32 HoldRstGpioNo;
  BOOLEAN HoldRstActive;
  UINT8 PwrEnableExpanderNo;
  UINT32 PwrEnableGpioNo;
  BOOLEAN PwrEnableActive;
} SWITCH_GRAPHIC_GPIO;

typedef struct {
  UINT8 ClkReqNumber : 4;
  UINT8 ClkReqSupported : 1;
  UINT8 DeviceResetPadActiveHigh : 1;
  UINT32 DeviceResetPad;
} ROOT_PORT_CLK_INFO;

typedef struct {
  UINT8 Section;
  UINT8 Pin;
} EXPANDER_GPIO_CONFIG;

typedef enum {
  BoardGpioTypePch,
  BoardGpioTypeExpander,
  BoardGpioTypeNotSupported = 0xFF
} BOARD_GPIO_TYPE;

typedef struct {
  UINT8 Type;
  UINT8 Reserved[3];  // alignment for COMMON_GPIO_CONFIG
  union {
    UINT32 Pin;
    EXPANDER_GPIO_CONFIG Expander;
  } u;
} BOARD_GPIO_CONFIG;

// Do not change the encoding. It must correspond with PCH_PCIE_CLOCK_USAGE from PCH RC.
#define NOT_USED     0xFF
#define FREE_RUNNING 0x80
#define LAN_CLOCK    0x70
#define PCIE_PEG     0x40
#define PCIE_PCH     0x00

typedef struct {
  UINT32 ClockUsage;
  UINT32 ClkReqSupported;
} PCIE_CLOCK_CONFIG;

typedef union {
  UINT64 Blob;
  BOARD_GPIO_CONFIG  BoardGpioConfig;
  ROOT_PORT_CLK_INFO Info;
  PCIE_CLOCK_CONFIG  PcieClock;
} PCD64_BLOB;

#ifndef IO_EXPANDER_DISABLED
#define IO_EXPANDER_DISABLED      0xFF
#endif

#define SPD_DATA_SIZE 512

///
/// Use this macro to create USB_OC_MAP_TABLE and populate size automatically
///
#define USB_OC_MAP_TABLE_INIT(...) \
{ \
  (sizeof((USB_OVERCURRENT_PIN[]){__VA_ARGS__})/sizeof(USB_OVERCURRENT_PIN)), \
  { __VA_ARGS__ } \
}

/**
  This is a helper structure that's used to updating Config Block data according to board design
**/
typedef struct  {
  UINT8                 Size;
  USB_OVERCURRENT_PIN   Data[];
} USB_OC_MAP_TABLE;

///
/// Use this macro to create USB2_PHY_TABLE and populate size automatically
///
#define USB2_PHY_TABLE_INIT(...) \
{ \
  (sizeof((USB2_PHY_PARAMETERS[]){__VA_ARGS__})/sizeof(USB2_PHY_PARAMETERS)), \
  { __VA_ARGS__ } \
}

/**
  This is a helper structure that's used to updating Config Block data according to board design
**/
typedef struct  {
  UINT8                 Size;
  USB2_PHY_PARAMETERS   Data[];
} USB2_PHY_TABLE;

#pragma pack()

#endif // _PLATFORM_BOARD_CONFIG_H
