/** @file
  PCH SPI Runtime Driver implements the SPI Host Controller Compatibility Interface.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2004 - 2018 Intel Corporation.

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
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiRuntimeLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Guid/EventGroup.h>
#include <Library/PciSegmentLib.h>
#include <Protocol/Spi.h>
#include <Library/SpiCommonLib.h>
#include <PchReservedResources.h>
#include <IndustryStandard/Pci30.h>
#include <Register/SpiRegs.h>
#include <Library/BootMediaLib.h>

///
/// Global variables
///
GLOBAL_REMOVE_IF_UNREFERENCED SPI_INSTANCE                  *mSpiInstance;
///
/// PchSpiBar0PhysicalAddr keeps the reserved MMIO range assiged to SPI from PEI.
/// It won't be updated no matter the SPI MMIO is reallocated by BIOS PCI enum.
/// And it's used to override the SPI BAR0 register in runtime environment,
///
GLOBAL_REMOVE_IF_UNREFERENCED UINT32                        mPchSpiBar0PhysicalAddr;
///
/// PchSpiBar0VirtualAddr keeps the virtual address of PchSpiBar0PhysicalAddr.
/// And it's used to provide the SPI BAR0 virtual address mapping to PchSpiBar0PhysicalAddr
/// in runtime environment. Bit address could be over 4G in 64bit OS.
///
GLOBAL_REMOVE_IF_UNREFERENCED UINTN                         mPchSpiBar0VirtualAddr;
GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN                       mRuntimeFlag;

//
// Function implementations
//

/**
  Fixup internal data pointers so that the services can be called in virtual mode.

  @param[in] Event                The event registered.
  @param[in] Context              Event context. Not used in this event handler.

**/
VOID
EFIAPI
PchSpiVirtualAddressChangeEvent (
  IN EFI_EVENT        Event,
  IN VOID             *Context
  )
{
  mRuntimeFlag = TRUE;

  gRT->ConvertPointer (0, (VOID *) &mPchSpiBar0VirtualAddr);
  gRT->ConvertPointer (0, (VOID *) &(mSpiInstance->SpiProtocol.FlashRead));
  gRT->ConvertPointer (0, (VOID *) &(mSpiInstance->SpiProtocol.FlashWrite));
  gRT->ConvertPointer (0, (VOID *) &(mSpiInstance->SpiProtocol.FlashErase));
  gRT->ConvertPointer (0, (VOID *) &(mSpiInstance->SpiProtocol.FlashReadSfdp));
  gRT->ConvertPointer (0, (VOID *) &(mSpiInstance->SpiProtocol.FlashReadJedecId));
  gRT->ConvertPointer (0, (VOID *) &(mSpiInstance->SpiProtocol.FlashWriteStatus));
  gRT->ConvertPointer (0, (VOID *) &(mSpiInstance->SpiProtocol.FlashReadStatus));
  gRT->ConvertPointer (0, (VOID *) &(mSpiInstance->SpiProtocol.ReadPchSoftStrap));
  gRT->ConvertPointer (0, (VOID *) &mSpiInstance);
}

/**
  <b>SPI Runtime DXE Module Entry Point</b>\n
  - <b>Introduction</b>\n
    The SPI Runtime DXE module provide a standard way for other modules to use the PCH SPI Interface in DXE/Runtime.

  - @pre
    - If SPI Runtime DXE driver is run before Status Code Runtime Protocol is installed
      and there is the need to use Status code in the driver, it will be necessary
      to add EFI_STATUS_CODE_RUNTIME_PROTOCOL_GUID to the dependency file.

  - @result
    The SPI Runtime DXE driver produces @link _PCH_SPI_PROTOCOL PCH_SPI_PROTOCOL @endlink

  - <b>Integration Check List</b>\n
    - This driver supports Descriptor Mode only.
    - This driver supports Hardware Sequence only.

  @param[in] ImageHandle          Image handle of this driver.
  @param[in] SystemTable          Global system service table.

  @retval EFI_SUCCESS             Initialization complete.
  @exception EFI_UNSUPPORTED      The chipset is unsupported by this driver.
  @retval EFI_OUT_OF_RESOURCES    Do not have enough resources to initialize the driver.
  @retval EFI_DEVICE_ERROR        Device error, driver exits abnormally.
**/
EFI_STATUS
EFIAPI
InstallPchSpi (
  IN EFI_HANDLE            ImageHandle,
  IN EFI_SYSTEM_TABLE      *SystemTable
  )
{
  EFI_STATUS                      Status;
  UINT64                          BaseAddress;
  UINT64                          Length;
  EFI_GCD_MEMORY_SPACE_DESCRIPTOR SpiBar0MemorySpaceDescriptor;
  UINT64                          Attributes;
  EFI_EVENT                       AddressChangeEvent;

  if (!BootMediaIsSpi ()) {
    return EFI_SUCCESS;
  }

  DEBUG ((DEBUG_INFO, "InstallPchSpi() Start\n"));

  ///
  /// Allocate Runtime memory for the SPI protocol instance.
  ///
  mSpiInstance = AllocateRuntimeZeroPool (sizeof (SPI_INSTANCE));
  if (mSpiInstance == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  ///
  /// Initialize the SPI protocol instance
  ///
  mPchSpiBar0PhysicalAddr     = PCH_SPI_BASE_ADDRESS;
  mPchSpiBar0VirtualAddr      = mPchSpiBar0PhysicalAddr;
  Status = SpiProtocolConstructor (mSpiInstance);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  PciSegmentRegisterForRuntimeAccess (mSpiInstance->PchSpiBase);
  ///
  /// Install the PCH_SPI_PROTOCOL interface
  ///
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &(mSpiInstance->Handle),
                  &gPchSpiProtocolGuid,
                  &(mSpiInstance->SpiProtocol),
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    FreePool (mSpiInstance);
    return EFI_DEVICE_ERROR;
  }

  ///
  /// Create Address Change event
  ///
  ///
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  PchSpiVirtualAddressChangeEvent,
                  NULL,
                  &gEfiEventVirtualAddressChangeGuid,
                  &AddressChangeEvent
                  );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Set SPI space in GCD to be RUNTIME so that the range will be supported in
  /// virtual address mode in EFI aware OS runtime.
  /// It will assert if SPI Memory Space is not allocated
  /// The caller is responsible for the existence and allocation of the SPi Memory Spaces
  ///

  //
  //  SPI MMIO memory space
  //
  BaseAddress = (EFI_PHYSICAL_ADDRESS) mPchSpiBar0PhysicalAddr;
  Length      = 0x1000;

  Status      = gDS->GetMemorySpaceDescriptor (BaseAddress, &SpiBar0MemorySpaceDescriptor);
  ASSERT_EFI_ERROR (Status);

  Attributes  = SpiBar0MemorySpaceDescriptor.Attributes | EFI_MEMORY_RUNTIME;

  Status      = gDS->SetMemorySpaceAttributes (
                       BaseAddress,
                       Length,
                       Attributes
                       );
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "InstallPchSpi() End\n"));

  return EFI_SUCCESS;
}

/**
  Acquire pch spi mmio address.
  If it is ever different from the preallocated address, reassign it back.
  The SpiBar0 could be 64bit in virtual address.

  @param[in] SpiInstance          Pointer to SpiInstance to initialize

  @retval PchSpiBar0              return SPI MMIO address
**/
UINTN
AcquireSpiBar0 (
  IN  SPI_INSTANCE                *SpiInstance
  )
{
  UINT32                          SpiBar0;
  //
  // Save original SPI physical MMIO address
  //
  SpiBar0 = PciSegmentRead32 (SpiInstance->PchSpiBase + R_SPI_CFG_BAR0) & ~(B_SPI_CFG_BAR0_MASK);

  if (SpiBar0 != mPchSpiBar0PhysicalAddr) {
    //
    // Temporary disable MSE, and override with SPI reserved MMIO address, then enable MSE.
    //
    PciSegmentAnd8 (SpiInstance->PchSpiBase + PCI_COMMAND_OFFSET, (UINT8) ~EFI_PCI_COMMAND_MEMORY_SPACE);
    PciSegmentWrite32 (SpiInstance->PchSpiBase + R_SPI_CFG_BAR0, mPchSpiBar0PhysicalAddr);
    PciSegmentOr8 (SpiInstance->PchSpiBase + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);
  }

  if (mRuntimeFlag) {
    return mPchSpiBar0VirtualAddr;
  } else {
    return mPchSpiBar0PhysicalAddr;
  }
}

/**
  Release pch spi mmio address. Do nothing.

  @param[in] SpiInstance          Pointer to SpiInstance to initialize

  @retval None
**/
VOID
ReleaseSpiBar0 (
  IN     SPI_INSTANCE       *SpiInstance
  )
{
}

/**
  This function is a hook for Spi to disable BIOS Write Protect

  @retval EFI_SUCCESS             The protocol instance was properly initialized
  @retval EFI_ACCESS_DENIED       The BIOS Region can only be updated in SMM phase

**/
EFI_STATUS
EFIAPI
DisableBiosWriteProtect (
  VOID
  )
{
  UINT64                          SpiBaseAddress;

  SpiBaseAddress = mSpiInstance->PchSpiBase;
  if ((PciSegmentRead8 (SpiBaseAddress + R_SPI_CFG_BC) & B_SPI_CFG_BC_EISS) != 0) {
    return EFI_ACCESS_DENIED;
  }
  ///
  /// Enable the access to the BIOS space for both read and write cycles
  ///
  PciSegmentOr8 (
    SpiBaseAddress + R_SPI_CFG_BC,
    (UINT8) (B_SPI_CFG_BC_WPD)
    );

  return EFI_SUCCESS;
}

/**
  This function is a hook for Spi to enable BIOS Write Protect
**/
VOID
EFIAPI
EnableBiosWriteProtect (
  VOID
  )
{
  UINT64           SpiBaseAddress;

  SpiBaseAddress = mSpiInstance->PchSpiBase;
  ///
  /// Disable the access to the BIOS space for write cycles
  ///
  PciSegmentAnd8 (
    SpiBaseAddress + R_SPI_CFG_BC,
    (UINT8) (~B_SPI_CFG_BC_WPD)
    );
}

/**
  Check if it's granted to do flash write.

  @retval TRUE    It's secure to do flash write.
  @retval FALSE   It's not secure to do flash write.
**/
BOOLEAN
IsSpiFlashWriteGranted (
  VOID
  )
{
  return TRUE;
}
