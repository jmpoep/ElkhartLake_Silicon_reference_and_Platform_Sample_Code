/** @file
  Internal header file for PCH SMBUS library

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
#ifndef __PEI_SMBUS_LIB_INTERNAL_H__
#define __PEI_SMBUS_LIB_INTERNAL_H__

#include <Uefi/UefiBaseType.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/HobLib.h>
#include <Library/PchPcrLib.h>
#include <PiPei.h>
#include <Ppi/Smbus2.h>
#include <Ppi/MemoryDiscovered.h>
#include <Ppi/SiPolicy.h>
#include <Library/PciSegmentLib.h>
#include <IndustryStandard/Pci30.h>
#include <Library/GpioPrivateLib.h>
#include <Library/PsfLib.h>
#include <Library/PeiItssLib.h>
#include <Library/SmbusCommonLib.h>

extern EFI_GUID gEfiSmbusArpMapGuid;

///
/// Max number of SMBus devices
/// (7 bit address yields 128 combinations but 21 of those are reserved)
/// Due to limited resources, we only allow 8 in PEI.
///
#define MAX_SMBUS_DEVICES       8

#define MAX_SMBUS_NOTIFICATION  8

///
/// Private Data Structures
///
typedef struct _PEI_SMBUS_NOTIFY_FUNCTION_LIST_NODE {
  EFI_SMBUS_DEVICE_ADDRESS       SlaveAddress;
  UINTN                          Data;
  EFI_PEI_SMBUS_NOTIFY2_FUNCTION NotifyFunction;
} PEI_SMBUS_NOTIFY_FUNCTION_LIST_NODE;

///
/// Declare a local instance structure for this PEIM
///
typedef struct _SMBUS_INSTANCE {
  UINTN                               Signature;
  EFI_PEI_PPI_DESCRIPTOR              PpiDescriptor;
  EFI_PEI_SMBUS2_PPI                  SmbusPpi;
  UINT8                               DeviceMapEntries;
  EFI_SMBUS_DEVICE_MAP                DeviceMap[MAX_SMBUS_DEVICES];
  UINT8                               PlatformNumRsvd;
  UINT8                               PlatformRsvdAddr[PCH_MAX_SMBUS_RESERVED_ADDRESS];
  BOOLEAN                             ArpEnable;

  UINT8                               NotifyFunctionNum;
  PEI_SMBUS_NOTIFY_FUNCTION_LIST_NODE NotifyFunctionList[MAX_SMBUS_NOTIFICATION];
} SMBUS_INSTANCE;


#define SMBUS_PRIVATE_DATA_FROM_PPI_THIS(a) CR (a, SMBUS_INSTANCE, SmbusPpi, PCH_SMBUS_PRIVATE_DATA_SIGNATURE)

#define SMBUS_PRIVATE_DATA_FROM_DESCRIPTOR_THIS(a) \
  CR ( \
  a, \
  SMBUS_INSTANCE, \
  PpiDescriptor, \
  PCH_SMBUS_PRIVATE_DATA_SIGNATURE \
  )

#define SMBUS_PRIVATE_DATA_FROM_NOTIFY_THIS(a) \
  CR ( \
  a, \
  SMBUS_INSTANCE, \
  NotifyDescriptor, \
  PCH_SMBUS_PRIVATE_DATA_SIGNATURE \
  )

/**
  This function provides a standard way to execute an SMBUS command
  PPI as defined in the SMBus Specification. The data can either be of
  the length byte, word, or a block of data (1 to 32 bytes long).
  The resulting transaction will be either the SMBus Slave Device accepts
  this transaction or this function returns with an error

  @param[in] This                 PEI_SMBUS_PPI instance
  @param[in] SlaveAddress         Smbus Slave device address
  @param[in] Command              Command to be sent
  @param[in] Operation            Which SMBus PPI will be used
  @param[in] PecCheck             Defines if Packet Error Code Checking is to be used
  @param[in, out] Length          How many bytes to read/write. Must be 1 <= Length <= 32 depending on the Operation
  @param[in, out] Buffer          Data buffer

  @retval EFI_SUCCESS             Operation success.
                                  Length will contain the actual number of bytes read.
                                  Buffer will contain the data read.
  @retval Otherwise               Operation failed.
**/
EFI_STATUS
EFIAPI
SmbusExecute (
  IN CONST EFI_PEI_SMBUS2_PPI       *This,
  IN      EFI_SMBUS_DEVICE_ADDRESS  SlaveAddress,
  IN      EFI_SMBUS_DEVICE_COMMAND  Command,
  IN      EFI_SMBUS_OPERATION       Operation,
  IN      BOOLEAN                   PecCheck,
  IN OUT  UINTN                     *Length,
  IN OUT  VOID                      *Buffer
  );

/**
  Set Slave address for an Smbus device with a known UDID or perform a general
  ARP of all devices.

  @param[in] This                 Pointer to the instance of the PEI_SMBUS_PPI.
  @param[in] ArpAll               If TRUE, do a full ARP. Otherwise, just ARP the specified UDID.
  @param[in] SmbusUdid            When doing a directed ARP, ARP the device with this UDID.
  @param[in, out] SlaveAddress    Buffer to store new Slave Address during directed ARP.

  @exception EFI_UNSUPPORTED      This functionality is not supported
  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
EFIAPI
SmbusArpDevice (
  IN CONST EFI_PEI_SMBUS2_PPI           *This,
  IN       BOOLEAN                      ArpAll,
  IN       EFI_SMBUS_UDID               *SmbusUdid OPTIONAL,
  IN OUT   EFI_SMBUS_DEVICE_ADDRESS     *SlaveAddress OPTIONAL
  );

/**
  Get a pointer to the assigned mappings of UDID's to Slave Addresses.

  @param[in] This                 Pointer to the instance of the PEI_SMBUS_PPI.
  @param[in, out] Length          Buffer to contain the lenght of the Device Map.
  @param[in, out] SmbusDeviceMap  Buffer to contian a pointer to the Device Map.

  @exception EFI_UNSUPPORTED      This functionality is not supported
  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
EFIAPI
SmbusGetArpMap (
  IN CONST EFI_PEI_SMBUS2_PPI           *This,
  IN OUT   UINTN                        *Length,
  IN OUT   EFI_SMBUS_DEVICE_MAP         **SmbusDeviceMap
  );

/**
  Register a callback in the event of a Host Notify command being sent by a
  specified Slave Device.

  @param[in] This                 The PPI instance
  @param[in] SlaveAddress         Address of the device whose Host Notify command we want to trap.
  @param[in] Data                 Data of the Host Notify command we want to trap.
  @param[in] NotifyFunction       Function to be called in the event the desired Host Notify command occurs.

  @exception EFI_UNSUPPORTED      This functionality is not supported
  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
EFIAPI
SmbusNotify (
  IN CONST EFI_PEI_SMBUS2_PPI             *This,
  IN       EFI_SMBUS_DEVICE_ADDRESS       SlaveAddress,
  IN       UINTN                          Data,
  IN       EFI_PEI_SMBUS_NOTIFY2_FUNCTION NotifyFunction
  );

/**
  Issue a prepare ARP command to informs all devices that the ARP Master is starting the ARP process

  @param[in] Private              Pointer to the SMBUS_INSTANCE

  @retval EFI_SUCCESS             The function completed successfully
**/
EFI_STATUS
SmbusPrepareToArp (
  IN      SMBUS_INSTANCE                *Private
  );

/**
  Do a fully (general) Arp procress to assign the slave address of all ARP-capable device.
  This function will issue issue the "Prepare to ARP", "Get UDID" and "Assign Address" commands.

  @param[in] Private              Pointer to the SMBUS_INSTANCE

  @retval EFI_OUT_OF_RESOURCES    No available address to assign
  @retval EFI_SUCCESS             The function completed successfully
**/
EFI_STATUS
SmbusFullArp (
  IN SMBUS_INSTANCE *Private
  );

/**
  Do a directed Arp procress to assign the slave address of a single ARP-capable device.

  @param[in] Private              Pointer to the SMBUS_INSTANCE
  @param[in] SmbusUdid            When doing a directed ARP, ARP the device with this UDID.
  @param[in, out] SlaveAddress    Buffer to store new Slave Address during directed ARP.

  @retval EFI_OUT_OF_RESOURCES    DeviceMapEntries is more than Max number of SMBus devices.
                                  Or there is no available address to assign
  @retval EFI_SUCCESS             The function completed successfully
**/
EFI_STATUS
SmbusDirectedArp (
  IN     SMBUS_INSTANCE           *Private,
  IN     EFI_SMBUS_UDID           *SmbusUdid,
  IN OUT EFI_SMBUS_DEVICE_ADDRESS *SlaveAddress
  );

#endif //__PEI_SMBUS_LIB_INTERNAL_H__
