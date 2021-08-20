/** @file
  SIO chip specific implementation.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2017 Intel Corporation.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be 
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:
**/


#include "SioDriver.h"
#include <Library/S3IoLib.h>
#include <Library/DebugLib.h>

LOCAL_IO_WRITE8    mIoWrite8         = IoWrite8;
//
// System configuration (setup) information
//
// SYSTEM_CONFIGURATION                mSystemConfiguration;

typedef struct {
  UINT8 Register;
  UINT8 Value;
} EFI_SIO_TABLE;

typedef struct {
  UINT8 Register;
  UINT8 LogiCheck;
  UINT8 Value;
} EFI_SIO_DISABLE_TABLE;

//
// COM 1 UART Controller
//
ACPI_SIO_RESOURCES_IO_IRQ      mCom1Resources = {
  {
    { ACPI_FIXED_LOCATION_IO_PORT_DESCRIPTOR },
    0x3f8,
    8
  },
  {
    { ACPI_IRQ_NOFLAG_DESCRIPTOR },
    BIT4    // IRQ4
  },
  {
    ACPI_END_TAG_DESCRIPTOR,
    0
  }
};

//
// COM 2 UART Controller
//
ACPI_SIO_RESOURCES_IO_IRQ      mCom2Resources = {
  {
    { ACPI_FIXED_LOCATION_IO_PORT_DESCRIPTOR },
    0x2f8,
    8
  },
  {
    { ACPI_IRQ_NOFLAG_DESCRIPTOR },
    BIT3    // IRQ3
  },
  {
    ACPI_END_TAG_DESCRIPTOR,
    0
  }
};

//
// PS/2 Keyboard Controller
//
ACPI_SIO_RESOURCES_IO_IRQ      mKeyboardResources = {
  {
    { ACPI_FIXED_LOCATION_IO_PORT_DESCRIPTOR },
    0x60,
    5
  },
  {
    { ACPI_IRQ_NOFLAG_DESCRIPTOR },
    BIT1
  },
  {
    ACPI_END_TAG_DESCRIPTOR,
    0
  }
};

//
// PS/2 Mouse Controller
//
ACPI_SIO_RESOURCES_IO_IRQ      mMouseResources = {
  {
    { ACPI_FIXED_LOCATION_IO_PORT_DESCRIPTOR },
    0x60,
    5
  },
  {
    { ACPI_IRQ_NOFLAG_DESCRIPTOR },
    BIT12
  },
  {
    ACPI_END_TAG_DESCRIPTOR,
    0
  }
};


EFI_SIO_TABLE mSioTable[] = {
  //
  // Init serial port 1,2
  //
  {
    REG_UARTS_POWER_CONTROL,
    0x88
  },  // Power On UARTs
  {
    REG_UART1_BASE_ADDRESS,
    LPC_SERIAL_PORT1_BASE >> 2
  },
  {
    REG_UART2_BASE_ADDRESS,
    LPC_SERIAL_PORT2_BASE >> 2
  },
  {
    REG_UART_MODE,
    0x008
  },  // Set UART mode
  {
    REG_UART_IRQ_SELECT,
    0x043
  },  // IRQ of UARTs, UART2 IRQ=3,UART1 IRQ=4,
  {
    REG_IRQIN1_HPMODE_SIRQ_CLKRUN_EN,
    0x080
  },  // SIRQ_CLKRUN_EN
  {
    REG_IRQIN2,
    0x000
  },  // Disabled
  {
    REG_IR_MUX,
    0x04
  },  //IR MUX set to COM port
  {
    REG_SCE_BASE_ADDRESS,
    LPC_SCE_PORT_BASE >> 3
  },
  {
    REG_SCE_DMA_SELECT,
    0x003
  },  // DMA3
  //
  // Init GPIO
  //
  {
    REG_RUNTIME_REGISTER_BLOCK_ADDRESS,
    LPC_RUNTIME_REGISTER_BLOCK_BASE >> 4
  },
  {
    REG_GPIO_DIRECTION_REG1,
    0x004
  },  // GP10,11,13-17:in; GP12:Out
  {
    REG_GPIO_POLARITY_REG1,
    0x000
  },  // Non Inverted
  {
    REG_GPIO_OUTPUT_TYPE_REG1,
    0x000
  },
  {
    REG_GPIO_PULLUP_REG1,
    0x000
  },
  {
    REG_GPIO_DIRECTION_REG3,
    0x0FE
  },
  {
    REG_GPIO_POLARITY_REG3,
    0x000
  },
  {
    REG_GPIO_PULLUP_REG3,
    0x000
  },
  {
    REG_GPIO_OUTPUT_TYPE_REG3,
    0x000
  },
  {
    REG_ALTERNATE_FUNCTION_REG,
    0x001
  },  // set GP12-14 to GPIO
  //
  // Init LPC Docking
  //
  {
    REG_LPC_ACTIVATE_POWER,
    0x000
  },  // LPC Docking Disabling
  {
    REG_LPC_DOCKING_BASE_ADDR_HIGH,
    LPC_RUNTIME_REGISTER_BLOCK_BASE >> 8
  },
  {
    REG_LPC_DOCKING_BASE_ADDR_LOW,
    (LPC_RUNTIME_REGISTER_BLOCK_BASE & 0xFF) + 0x010
  },
  {
    REG_LPC_ACTIVATE_POWER,
    0x00B
  },  // LPC Docking Enabling
};

EFI_SIO_DISABLE_TABLE mCom1DisableTable[] = {
  //
  // Disable serial port 1,2
  //
  {
    REG_UARTS_POWER_CONTROL,  // UART1 Power Reg02 bit3
    EFI_SIO_AND,  // Is 1
    0xF7
  },
  {
    REG_UART1_BASE_ADDRESS,  // UART1 Base Reg24
    EFI_SIO_AND,  // Is 1
    0x00
  },
  {
    REG_UART_IRQ_SELECT,  // UART1 IRQ Reg28 bit0~3
    EFI_SIO_AND,
    0x0f  // clear bit 0~3
  },
};

EFI_SIO_DISABLE_TABLE mCom2DisableTable[] = {
  //
  // Disable serial port 2
  //
  {
    REG_UARTS_POWER_CONTROL,  // UART2 Power Reg02 bit7
    EFI_SIO_AND,
    0x7F
  },
  {
    REG_UART2_BASE_ADDRESS,  //UART2 Base Reg25
    EFI_SIO_AND,
    0x00
  },
  {
    REG_UART_MODE,  //UART2 Mode Reg0c
    EFI_SIO_AND,
    0x00
  },	// Set UART mode to com mode not ir mode
  {
    REG_IR_MUX,  //IR MUX set to COM port
    1,  //And
    0x00
  },    // Set UART mode
  {
    REG_UART_IRQ_SELECT,  // UART2 IRQ Reg28 bit4~7
    EFI_SIO_AND,
    0xf0  // clear bit 4~7
  },
  {
    REG_SCE_BASE_ADDRESS, //IR Base Reg2B
    EFI_SIO_AND,
    0x00
    },
  {
    REG_SCE_DMA_SELECT,  // UART2 DMA Reg2C bit 0~3
    EFI_SIO_OR,
    0x0f
  },
};

//
// Table of SIO Controllers
//
DEVICE_INFO    mDeviceInfo[] = {
  {
    {
      EISA_PNP_ID(0x501),
      0
    },
    0,
    RESOURCE_IO | RESOURCE_IRQ,
    { (ACPI_SMALL_RESOURCE_HEADER *) &mCom1Resources },
    { (ACPI_SMALL_RESOURCE_HEADER *) &mCom1Resources }
  },  // COM 1 UART Controller
  {
    {
      EISA_PNP_ID(0x501),
      1
    },
    0,
    RESOURCE_IO | RESOURCE_IRQ,
    { (ACPI_SMALL_RESOURCE_HEADER *) &mCom2Resources },
    { (ACPI_SMALL_RESOURCE_HEADER *) &mCom2Resources }
  },  // COM 2 UART Controller
  {
    {
      EISA_PNP_ID(0x303),
      0
    },
    0,
    0,  // Cannot change resource
    { (ACPI_SMALL_RESOURCE_HEADER *) &mKeyboardResources },
    { (ACPI_SMALL_RESOURCE_HEADER *) &mKeyboardResources }
  },  // PS/2 Keyboard Controller
  {
    {
      EISA_PNP_ID(0xF03),
      0
    },
    0,
    0,  // Cannot change resource
    { (ACPI_SMALL_RESOURCE_HEADER *) &mMouseResources },
    { (ACPI_SMALL_RESOURCE_HEADER *) &mMouseResources }
  }  // PS/2 Mouse Controller
};

EFI_SIO_TABLE SioPMInitTable[] = {
//;  Index  Data

    { 000,  000 },  // ;PME_STS
    { 001,  001 },  // ;PME_EN
    { 002,  0xDB},  // ;PME_STS1
    { 003,  000 },  // ;PME_STS2
    { 004,  0xFF},  // ;PME_STS3
    { 005,  0x20},  // ;PME_EN1
    { 006,  001},   // ;PME_EN2
    { 007,  000},   // ;PME_EN3
    { 0x08, 0xDB},  // ;SMI_STS1
    { 0x09, 000},   // ;SMI_STS2
    { 0x0A, 000},   // ;SMI_EN1
    { 0x0B, 000},   // ;SMI_EN2
    { 0x0C, 0x24},  // ;GP1
    { 0x0D, 0x00},  // ;GP2
    { 0x0E, 0x00},  // ;GP3
    { 0x0F, 0x00}
};


/**
  Return the supported devices.

  @param[out] Devices         Pointer to pointer of EFI_SIO_ACPI_DEVICE_ID.
                              Caller is responsible to free the buffer.
  @param[out] Count           Pointer to UINTN holding the device count.
**/
VOID
DeviceGetList (
  OUT EFI_SIO_ACPI_DEVICE_ID **Devices,
  OUT UINTN                  *Count
  )
{
  EFI_SIO_ACPI_DEVICE_ID       *LocalDevices;
  UINTN                        LocalCount;

  //
  // Allocate enough memory for simplicity
  //
  LocalDevices = AllocatePool (sizeof (EFI_SIO_ACPI_DEVICE_ID) * 4);
  ASSERT (LocalDevices != NULL);
  if (LocalDevices == NULL) {
    return;
  }
  LocalCount   = 0;

  if (PcdGet8 (PcdSmscLpc100xCom1Enable) != 0) {
    CopyMem (&LocalDevices[LocalCount], &mDeviceInfo[0].Device, sizeof (EFI_SIO_ACPI_DEVICE_ID));
    LocalCount++;
  }

  if (PcdGet8 (PcdSmscLpc100xCom2Enable) != 0) {
    CopyMem (&LocalDevices[LocalCount], &mDeviceInfo[1].Device, sizeof (EFI_SIO_ACPI_DEVICE_ID));
    LocalCount++;
  }

  if (PcdGetBool (PcdSmscLpc100xPs2KeyboardEnable)) {
    CopyMem (&LocalDevices[LocalCount], &mDeviceInfo[2].Device, sizeof (EFI_SIO_ACPI_DEVICE_ID));
    LocalCount ++;
  }

  if (PcdGetBool (PcdSmscLpc100xPs2MouseEnable)) {
    CopyMem (&LocalDevices[LocalCount], &mDeviceInfo[3].Device, sizeof (EFI_SIO_ACPI_DEVICE_ID));
    LocalCount ++;
  }

  *Devices = LocalDevices;
  *Count   = LocalCount;
}


/**
  Program the SIO chip to enter the configure mode.
**/
VOID
EnterConfigMode (
  VOID
  )
{
  mIoWrite8 (SIO_CONFIG_PORT, 0x55);
}


/**
  Program the SIO chip to exit the configure mode.
**/
VOID
ExitConfigMode (
  VOID
  )
{
  mIoWrite8 (SIO_CONFIG_PORT, 0xAA);
}


/**
  Perform a 8-bit I/O write to SIO register.

  @param[in]  Index  The register index.
  @param[in]  Data   The value to write to register.
**/
VOID
WriteRegister (
  IN  UINT8            Index,
  IN  UINT8            Data
  )
{
  mIoWrite8 (SIO_INDEX_PORT, Index);
  mIoWrite8 (SIO_DATA_PORT, Data);
}


/**
  Perform a 8-bit I/O read from SIO register.

  @param[in]  Index  The register index.

  @retval     Value  The value written to the register.
**/
UINT8
ReadRegister (
  IN  UINT8            Index
  )
{
  IoWrite8 (SIO_INDEX_PORT, Index);
  return IoRead8 (SIO_DATA_PORT);
}


/**

  @param[in]  Index
  @param[in]  LogiCheck
  @param[in]  RegMask
**/
VOID
ReadThenWriteRegister (
  IN  UINT8   Index,
  IN  UINT8   LogiCheck,
  IN  UINT8   RegMask
)
{
  switch (LogiCheck) {
    case EFI_SIO_OR:
      WriteRegister (
        Index,
        ReadRegister (Index) | RegMask
        );
      break;
    case EFI_SIO_AND:
      WriteRegister (
        Index,
        ReadRegister (Index) & RegMask
        );
  }
}


/**
  Super I/O controller initialization.

  @retval     EFI_SUCCESS       The super I/O controller is found and initialized.
  @retval     EFI_UNSUPPORTED   The super I/O controller is not found.
**/
EFI_STATUS
SioInit (
  VOID
  )
{
  UINT8                        Index;
  UINT8                        Data8;
  UINT8                        Com1ParsId;
  UINT8                        Com2ParsId;
  UINT8                        DeviceMode;

  mIoWrite8 = IoWrite8;
  EnterConfigMode ();
  IoWrite8 (SIO_INDEX_PORT, REG_DEVICE_ID);   // SMSC SIO1007 Device ID register is 0x0D
  Data8 = IoRead8 (SIO_DATA_PORT);
  ExitConfigMode();
  if (Data8 != 0x20) {   // SMSC SIO1007 Device ID is 0x20
    return EFI_UNSUPPORTED;
  }

  if (((PcdGet8 (PcdSmscLpc100xCom1Enable) == 0) && (PcdGet8 (PcdSmscLpc100xCom2Enable) == 0))) {
    return EFI_UNSUPPORTED;
  }

  Com1ParsId = PcdGet8 (PcdSmscLpc100xCom1ComPrsId);
  Com2ParsId = PcdGet8 (PcdSmscLpc100xCom2ComPrsId);
  if (Com1ParsId != 0 || Com2ParsId != 0) {
    switch (Com1ParsId) {

    case 1:
      mCom1Resources.Io.BaseAddress = 0x3F8;
      break;

    case 2:
      mCom1Resources.Io.BaseAddress = 0x3F8;
      break;

    case 3:
      mCom1Resources.Io.BaseAddress = 0x2F8;
      break;

    case 4:
      mCom1Resources.Io.BaseAddress = 0x3E8;
      break;

    case 5:
      mCom1Resources.Io.BaseAddress = 0x2E8;
      break;

    default:
      mCom1Resources.Io.BaseAddress = 0x3F8;
      break;
    }

    switch (Com2ParsId) {

    case 1:
      mCom2Resources.Io.BaseAddress = 0x3E8;
      break;

    case 2:
      mCom2Resources.Io.BaseAddress = 0x3F8;
      break;

    case 3:
      mCom2Resources.Io.BaseAddress = 0x2F8;
      break;

    case 4:
      mCom2Resources.Io.BaseAddress = 0x3E8;
      break;

    case 5:
      mCom2Resources.Io.BaseAddress = 0x2E8;
      break;

    default:
      mCom2Resources.Io.BaseAddress = 0x2F8;
      break;
    }
    //
    // check COM resource is whether conflict
    //
    if (mCom1Resources.Io.BaseAddress == mCom2Resources.Io.BaseAddress) {
      if (Com1ParsId != 0 && Com2ParsId != 0) {
        mCom2Resources.Io.BaseAddress = (mCom2Resources.Io.BaseAddress == LPC_SERIAL_PORT1_BASE) ? LPC_SERIAL_PORT2_BASE: LPC_SERIAL_PORT1_BASE;
        //
        // Adjust Com2 resource and change the setting to auto
        //
        PcdSet8S (PcdSmscLpc100xCom2ComPrsId, 0);
      }
      if (Com1ParsId == 0 && Com2ParsId != 0) {
        mCom1Resources.Io.BaseAddress = (mCom1Resources.Io.BaseAddress == LPC_SERIAL_PORT1_BASE) ? LPC_SERIAL_PORT2_BASE : LPC_SERIAL_PORT1_BASE;
      }
      if (Com1ParsId != 0 && Com2ParsId == 0) {
        mCom2Resources.Io.BaseAddress = (mCom2Resources.Io.BaseAddress == LPC_SERIAL_PORT1_BASE) ? LPC_SERIAL_PORT2_BASE : LPC_SERIAL_PORT1_BASE;
      }
    }
  }
  PcdSet16S (PcdSmscLpc100xCom1ComBase1, mCom1Resources.Io.BaseAddress);
  PcdSet16S (PcdSmscLpc100xCom2ComBase1, mCom2Resources.Io.BaseAddress);
  PcdSet16S (PcdSmscLpc100xCom2ComBase2, LPC_SCE_PORT_BASE);
  PcdSet8S (PcdSmscLpc100xCom1ComIrq1, 0x04);
  PcdSet8S (PcdSmscLpc100xCom2ComIrq1, 0x03);
  PcdSet8S (PcdSmscLpc100xCom2ComDma1, 0x03);
  //
  // According to PCD to update uart mode
  //
  DeviceMode = 0;
  if (PcdGet8 (PcdSmscLpc100xCom1ComMode) != 0) {
    DeviceMode |= 0x40;
  }
  if (PcdGet8 (PcdSmscLpc100xCom2ComMode) != 0) {
    DeviceMode |= 0x80;
  }
  for (Index = 0; Index < sizeof (mSioTable) / sizeof (EFI_SIO_TABLE); Index++) {
    if (mSioTable[Index].Register == REG_UART_MODE) {
      mSioTable[Index].Register |= DeviceMode;
    }
    if (mSioTable[Index].Register == REG_UART1_BASE_ADDRESS) {
      mSioTable[Index].Value = (UINT8) (mCom1Resources.Io.BaseAddress >> 2);
    }
    if (mSioTable[Index].Register == REG_UART2_BASE_ADDRESS) {
      mSioTable[Index].Value = (UINT8) (mCom2Resources.Io.BaseAddress >> 2);
    }
  }
  mIoWrite8 = S3IoWrite8;
  EnterConfigMode ();

  for (Index = 0; Index < sizeof (mSioTable) / sizeof (EFI_SIO_TABLE); Index++) {
    WriteRegister (mSioTable[Index].Register, mSioTable[Index].Value);
  }  // All devices enabled initialize

  for (Index = 0; Index < sizeof (SioPMInitTable) / sizeof (EFI_SIO_TABLE); Index++) {
    IoWrite8 (SioPMInitTable[Index].Register + LPC_RUNTIME_REGISTER_BLOCK_BASE, (UINT8) SioPMInitTable[Index].Value);
  }

  if (PcdGet8 (PcdSmscLpc100xCom1Enable) == 0) {
    // Disable Com1 if setup item disable it.
    for (Index = 0; Index < sizeof (mCom1DisableTable) / sizeof (EFI_SIO_DISABLE_TABLE); Index++) {
      ReadThenWriteRegister (mCom1DisableTable[Index].Register, mCom1DisableTable[Index].LogiCheck, mCom1DisableTable[Index].Value);
    }
  } else{
      // Set PCD to platform layer knows SMSC 100x SIO COM1 has been implemented
      PcdSet8S (PcdSmscLpc100xCom1Implemented, 1);
  }
  if (PcdGet8 (PcdSmscLpc100xCom2Enable) == 0) {
    // Disable Com2 (IR) if setup item disable it.
    for (Index = 0; Index < sizeof (mCom2DisableTable) / sizeof (EFI_SIO_DISABLE_TABLE); Index++) {
      ReadThenWriteRegister (mCom2DisableTable[Index].Register, mCom2DisableTable[Index].LogiCheck, mCom2DisableTable[Index].Value);
    }
  }else {
     // Set PCD to platform layer knows SMSC 100x SIO COM2 has been implemented
     PcdSet8S (PcdSmscLpc100xCom2Implemented, 1);
  }

  ExitConfigMode ();
  mIoWrite8 = IoWrite8;

  return EFI_SUCCESS;
}


/**
  Find the DEVICE_INFO for specified Device.

  @param[in]  Device        Pointer to the EFI_SIO_ACPI_DEVICE_ID.

  @return     DEVICE_INFO*  Pointer to the DEVICE_INFO.
**/
DEVICE_INFO *
DeviceSearch (
  IN EFI_SIO_ACPI_DEVICE_ID *Device
  )
{
  UINTN       Index;

  for (Index = 0; Index < sizeof (mDeviceInfo) / sizeof (mDeviceInfo[0]); Index++) {
    if (CompareMem (Device, &mDeviceInfo[Index].Device, sizeof (*Device)) == 0) {
      return &mDeviceInfo[Index];
    }
  }

  ASSERT (FALSE);
  return NULL;
}

/**
  Program the SIO chip to enable the specified device using the default resource.

  @param[in]  Device          Pointer to EFI_SIO_ACPI_DEVICE_ID.
**/
VOID
DeviceEnable (
  IN EFI_SIO_ACPI_DEVICE_ID   *Device
  )
{
}


/**
  Get the ACPI resources for specified device.

  @param[in]  Device          Pointer to EFI_SIO_ACPI_DEVICE_ID.
  @param[out] Resources       Pointer to ACPI_RESOURCE_HEADER_PTR.

  @retval     EFI_SUCCESS     The resources are returned successfully.
**/
EFI_STATUS
DeviceGetResources (
  IN  EFI_SIO_ACPI_DEVICE_ID   *Device,
  OUT ACPI_RESOURCE_HEADER_PTR *Resources
  )
{
  DEVICE_INFO               *DeviceInfo;

  DeviceInfo = DeviceSearch (Device);

  *Resources = DeviceInfo->Resources;

  return EFI_SUCCESS;
}


/**
  Set the ACPI resources for specified device.

  The SIO chip is programmed to use the new resources and the
  resources setting are saved. The function assumes the resources
  are valid.

  @param[in] Device          Pointer to EFI_SIO_ACPI_DEVICE_ID.
  @param[in] Resources       ACPI_RESOURCE_HEADER_PTR.

  @retval    EFI_SUCCESS     The resources are set successfully.
**/
EFI_STATUS
DeviceSetResources (
  IN EFI_SIO_ACPI_DEVICE_ID   *Device,
  IN ACPI_RESOURCE_HEADER_PTR Resources
  )
{
  return EFI_UNSUPPORTED;
}


/**
  Get the possible ACPI resources for specified device.

  @param[in]  Device          Pointer to EFI_SIO_ACPI_DEVICE_ID.
  @param[out] Resources       Pointer to ACPI_RESOURCE_HEADER_PTR.

  @retval     EFI_SUCCESS     The resources are returned successfully.
**/
EFI_STATUS
DevicePossibleResources (
  IN  EFI_SIO_ACPI_DEVICE_ID   *Device,
  OUT ACPI_RESOURCE_HEADER_PTR *Resources
  )
{
  DEVICE_INFO               *DeviceInfo;

  DeviceInfo = DeviceSearch (Device);

  *Resources = DeviceInfo->PossibleResources;

  return EFI_SUCCESS;
}
