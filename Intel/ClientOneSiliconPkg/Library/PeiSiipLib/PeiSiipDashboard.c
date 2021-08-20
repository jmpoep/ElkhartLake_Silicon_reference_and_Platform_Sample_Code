/**@file
  Siip Dashboard implementation

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2020 Intel Corporation.

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

@par Specification
**/

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/TimerLib.h>
#include <SiipCommon.h>
#include <Library/PeiSiipPse.h>
#include <Library/DebugLib.h>
#include <Ppi/SiPolicy.h>

#include <Library/PciSegmentLib.h>
#include <Library/PseInfoLib.h>
#include <Library/PchInfoLib.h>
#include <Library/IoLib.h>
#include <Library/PeiPseLib.h>
#include <Register/PseRegs.h>
#include <Register/PchRegs.h>
#include <PchReservedResources.h>
#include <IndustryStandard/Pci30.h>
#include <Library/TsnLib.h>
#include <TsnMacAddrSubRegion.h>
#include <PseTsnIpConfigSubRegion.h>
#include <TsnConfigSubRegion.h>
#include <PseFwStruct.h>
#include <Library/GpioPrivateLib.h>
#include <Library/GpioNativePads.h>

GLOBAL_REMOVE_IF_UNREFERENCED PSE_CONFIG               *mPseConfig = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED TSN_CONFIG               *mTsnConfig = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED CONST CHAR8              PseGbeSubRegionCompName[] = PSE_GBE_SUB_REGION_COMP_NAME;
GLOBAL_REMOVE_IF_UNREFERENCED CONST CHAR8              PseGbeSubRegionVendorName[] = PSE_GBE_SUB_REGION_VENDOR_NAME;

#define IMRIAEXCBASE_MCHBAR_CBO_INGRESS_REG                            (0x00006A40)
#define IMRIAEXCLIMIT_MCHBAR_CBO_INGRESS_REG                           (0x00006A48)
#define IMRGTEXCBASE_MCHBAR_CBO_INGRESS_REG                            (0x00006A50)
#define IMRGTEXCLIMIT_MCHBAR_CBO_INGRESS_REG                           (0x00006A58)

typedef union {
  struct {
    UINT32 lock                                    :  1;  // Bits 0:0
    UINT32                                         :  9;  // Bits 9:1
    UINT32 imriaexcbaseLow                         :  22;  // Bits 31:10
    UINT32 imriaexcbaseHigh                        :  7;  // Bits 38:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IMRIAEXCBASE_MCHBAR_CBO_INGRESS_STRUCT;

typedef union {
  struct {
    UINT32 lock                                    :  1;  // Bits 0:0
    UINT32                                         :  9;  // Bits 9:1
    UINT32 imriaexclimitLow                        :  22;  // Bits 31:10
    UINT32 imriaexclimitHigh                       :  7;  // Bits 38:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IMRIAEXCLIMIT_MCHBAR_CBO_INGRESS_STRUCT;

/**
  Send IP specific dashboard Read/Write command

  @param[in]     OperationType    Read/Write command (0: Read operation, 1: Write operation)
  @param[in]     IpName           Which IP interface the command needs to be issued
  @param[in]     RegisterType     Loader/Verifier type (0: Loader, 1: Verifier)
  @param[in]     RegisterOffset   Dashboard register offset to be accessed
  @param[in]     NumberOfBytes    Number of byes to be read or written
  @param[in out] DataBuffer       For read operation it is of output type, for write operation it is of input type

  @retval EFI_SUCCESS             Command was executed successfully
  @retval EFI_INVALID_PARAMETER   Invalid command size
  @retval EFI_DEVICE_ERROR        Command failed with an error
  @retval EFI_TIMEOUT             Command did not complete in given timing requirements
**/
EFI_STATUS
DashboardSendCommand (
  IN     SIIP_OP_TYPE             OperationType,
  IN     SIIP_IP_NAME             IpName,
  IN     SIIP_REG_TYPE            RegisterType,
  IN     UINT16                   RegisterOffset,
  IN     SIIP_NUM_BYTES           NumberOfBytes,
  IN OUT VOID                     *DataBuffer
  )
{
  EFI_STATUS             Status;

  Status = EFI_SUCCESS;

  switch (IpName) {
    case PSE_IP:
      PseSendCommand(OperationType, RegisterType, RegisterOffset,
                    NumberOfBytes, DataBuffer);
      break;
    case ACE_IP:
      break;
    default:
      break;
  }

  return Status;
}

/**
  Get the list of entities who has loader capabilities

  @param[in]     IpName             Which IP interface the command needs to be issued
  @param[out]    LoaderCapBuffer    Data which describes the loader capable entities

  @retval EFI_SUCCESS               Command was executed successfully
  @retval EFI_INVALID_PARAMETER     Invalid command size
  @retval EFI_DEVICE_ERROR          Command failed with an error
  @retval EFI_OUT_OF_RESOURCES      Unable to allocate memory resource
  @retval EFI_TIMEOUT               Command did not complete in given timing requirements
**/
EFI_STATUS
GetLoaderCapabilityInfo (
  IN     SIIP_IP_NAME             IpName,
  OUT    UINT32                   *LoaderCapBuffer
  )
{
  EFI_STATUS             Status;
  UINT64                 Data64;
  VOID                   *DataBufferLow;
  VOID                   *DataBufferHigh;
  UINT32                 *Data32Ptr;

  Status = EFI_SUCCESS;
  DataBufferLow = (VOID *) AllocateZeroPool (sizeof (UINT32 *) * 2);
  DataBufferHigh = (VOID *) AllocateZeroPool (sizeof (UINT32 *) * 2);
  Data32Ptr = AllocateZeroPool (sizeof (UINT32 *) * 2);
  Data64 = 0;
  *LoaderCapBuffer = 0;

  if ((DataBufferLow == NULL) || (DataBufferHigh == NULL) || (Data32Ptr == NULL)) {
    DEBUG ((DEBUG_ERROR, "AllocatePool failed.\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  switch (IpName) {
    case PSE_IP:
      Status = DashboardSendCommand(READ, PSE_IP, LOADER,
                                    SIIP_IP_CAP, FOUR_BYTES, DataBufferLow);
      Status = DashboardSendCommand(READ, PSE_IP, LOADER,
                                    SIIP_IP_CAP + 4, FOUR_BYTES, DataBufferHigh);
      break;
    case ACE_IP:
      break;
    default:
      break;
  }

  // Concatenate 2 UINT32 buffers to a single UINT64 data
  Data32Ptr = (UINT32*)DataBufferHigh;
  Data64 = (UINT64)*Data32Ptr;
  Data64 <<= 32;
  Data32Ptr = (UINT32*)DataBufferLow;
  Data64 |= ((UINT64)*Data32Ptr);

  //Loader Capabilities is built within IP itself
  if((Data64 >> IP_LOAD_OFFSET) & LOAD_CAP_MASK) {
    *LoaderCapBuffer |= IP_IS_CAPABLE;
  }

  //Loader Capabilities expected in BIOS
  if((Data64 >> BIOS_LOAD_OFFSET) & LOAD_CAP_MASK) {
    *LoaderCapBuffer |= BIOS_IS_CAPABLE;
  }

  //Loader Capabilities expected in IA SW/TEE
  if((Data64 >> IASW_LOAD_OFFSET) & LOAD_CAP_MASK) {
    *LoaderCapBuffer |= IASW_TEE_IS_CAPABLE;
  }

  //Loader Capabilities expected in SOC IP
  if((Data64 >> SOCIP_LOAD_OFFSET) & LOAD_CAP_MASK) {
    *LoaderCapBuffer |= SOCIP_IS_CAPABLE;
  }

  return Status;
}

/**
  Get the list of entities who has verifier capabilities

  @param[in]     IpName             Which IP interface the command needs to be issued
  @param[out]    VerifierCapBuffer  Data which describes the verifier capable entities

  @retval EFI_SUCCESS               Command was executed successfully
  @retval EFI_INVALID_PARAMETER     Invalid command size
  @retval EFI_DEVICE_ERROR          Command failed with an error
  @retval EFI_OUT_OF_RESOURCES      Unable to allocate memory resource
  @retval EFI_TIMEOUT               Command did not complete in given timing requirements
**/
EFI_STATUS
GetVerifierCapabilityInfo (
  IN     SIIP_IP_NAME             IpName,
  OUT    UINT32                   *VerifierCapBuffer
  )
{
  EFI_STATUS             Status;
  UINT64                 Data64;
  VOID                   *DataBufferLow;
  VOID                   *DataBufferHigh;
  UINT32                 *Data32Ptr;

  Status = EFI_SUCCESS;
  DataBufferLow = (VOID *) AllocateZeroPool (sizeof (UINT32 *) * 2);
  DataBufferHigh = (VOID *) AllocateZeroPool (sizeof (UINT32 *) * 2);
  Data32Ptr = AllocateZeroPool (sizeof (UINT32 *) * 2);
  Data64 = 0;
  *VerifierCapBuffer = 0;

  if ((DataBufferLow == NULL) || (DataBufferHigh == NULL) || (Data32Ptr == NULL)) {
    DEBUG ((DEBUG_ERROR, "AllocatePool failed.\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  switch (IpName) {
    case PSE_IP:
      Status = DashboardSendCommand(READ, PSE_IP, VERIFIER,
                                    SIIP_IP_CAP, FOUR_BYTES, DataBufferLow);
      Status = DashboardSendCommand(READ, PSE_IP, VERIFIER,
                                    SIIP_IP_CAP + 4, FOUR_BYTES, DataBufferHigh);
      break;
    case ACE_IP:
      break;
    default:
      break;
  }

  // Concatenate 2 UINT32 buffers to a single UINT64 data
  Data32Ptr = (UINT32*)DataBufferHigh;
  Data64 = (UINT64)*Data32Ptr;
  Data64 <<= 32;
  Data32Ptr = (UINT32*)DataBufferLow;
  Data64 |= ((UINT64)*Data32Ptr);

  //Verifier Capabilities is built within IP itself
  if((Data64 >> IP_VERIFIER_OFFSET) & VERIFY_CAP_MASK) {
    *VerifierCapBuffer |= IP_IS_CAPABLE;
  }

  //Verifier Capabilities expected in BIOS
  if((Data64 >> BIOS_VERIFIER_OFFSET) & VERIFY_CAP_MASK) {
    *VerifierCapBuffer |= BIOS_IS_CAPABLE;
  }

  //Verifier Capabilities expected in IA SW/TEE
  if((Data64 >> IASW_VERIFIER_OFFSET) & VERIFY_CAP_MASK) {
    *VerifierCapBuffer |= IASW_TEE_IS_CAPABLE;
  }

  //Verifier Capabilities expected in SOC IP
  if((Data64 >> SOCIP_VERIFIER_OFFSET) & VERIFY_CAP_MASK) {
    *VerifierCapBuffer |= SOCIP_IS_CAPABLE;
  }

  return Status;
}

/**
  Set the error code in dashboard for loading failed scenario

  @param[in]     IpName             Which IP interface the command needs to be issued
  @param[in]     ImageNumber        Failed image number
  @param[in]     ErrorCode          Failed reason

  @retval EFI_SUCCESS               Command was executed successfully
  @retval EFI_INVALID_PARAMETER     Invalid command size
  @retval EFI_DEVICE_ERROR          Command failed with an error
  @retval EFI_TIMEOUT               Command did not complete in given timing requirements
**/
EFI_STATUS
SetLoaderErrorInfo (
  IN     SIIP_IP_NAME             IpName,
  IN     SIIP_LOADER_INDEX        ImageNumber,
  IN     SIIP_ERROR_CODE          ErrorCode
  )
{
  EFI_STATUS             Status;
  UINT32                 Data32;
  UINT32                 *Data32Ptr;
  VOID                   *DataBuffer;

  Status = EFI_SUCCESS;
  DataBuffer = NULL;
  Data32Ptr = NULL;
  Data32 = 0;

  switch (IpName) {
    case PSE_IP:
      Status = DashboardSendCommand(READ, PSE_IP, LOADER,
                                    SIIP_LOAD_ERROR, FOUR_BYTES, DataBuffer);
      break;
    case ACE_IP:
      break;
    default:
      break;
  }

  // Set the loader error code with its image number
  Data32Ptr = DataBuffer;
  Data32 = *Data32Ptr;
  Data32 |= (ErrorCode << LOAD_ERR_BIT);
  Data32 |= ImageNumber;
  *Data32Ptr = Data32;

  switch (IpName) {
    case PSE_IP:
      Status = DashboardSendCommand(WRITE, PSE_IP, LOADER,
                                    SIIP_LOAD_ERROR, FOUR_BYTES, DataBuffer);
      break;
    case ACE_IP:
      break;
    default:
      break;
  }

  return Status;
}

/**
  Set the error code in dashboard for verifier failed scenario

  @param[in]     IpName             Which IP interface the command needs to be issued
  @param[in]     ImageNumber        Failed image number
  @param[in]     ErrorCode          Failed reason

  @retval EFI_SUCCESS               Command was executed successfully
  @retval EFI_INVALID_PARAMETER     Invalid command size
  @retval EFI_DEVICE_ERROR          Command failed with an error
  @retval EFI_TIMEOUT               Command did not complete in given timing requirements
**/
EFI_STATUS
SetVerifierErrorInfo (
  IN     SIIP_IP_NAME             IpName,
  IN     SIIP_VERIFIER_INDEX      ImageNumber,
  IN     SIIP_ERROR_CODE          ErrorCode
  )
{
  EFI_STATUS             Status;
  UINT32                 Data32;
  UINT32                 *Data32Ptr;
  VOID                   *DataBuffer;

  Status = EFI_SUCCESS;
  DataBuffer = NULL;
  Data32Ptr = NULL;
  Data32 = 0;

  switch (IpName) {
    case PSE_IP:
      Status = DashboardSendCommand(READ, PSE_IP, VERIFIER,
                                    SIIP_VERIFY_ERROR, FOUR_BYTES, DataBuffer);
      break;
    case ACE_IP:
      break;
    default:
      break;
  }

  // Set the verifier error code with its image number
  Data32Ptr = DataBuffer;
  Data32 = *Data32Ptr;
  Data32 |= (ErrorCode << VERIFY_ERR_BIT);
  Data32 |= ImageNumber;
  *Data32Ptr = Data32;

  switch (IpName) {
    case PSE_IP:
      Status = DashboardSendCommand(WRITE, PSE_IP, VERIFIER,
                                    SIIP_VERIFY_ERROR, FOUR_BYTES, DataBuffer);
      break;
    case ACE_IP:
      break;
    default:
      break;
  }

  return Status;
}

/**
  Set the base address/size/loading done for loader

  @param[in]     IpName              Which IP interface the command needs to be issued
  @param[in]     LoaderIndex         Data which describes the loader register index
  @param[in]     LoadedMemoryAddress Physical address of the image for the verifier to verify
  @param[in]     SizeOfImage         Size of the image

  @retval EFI_SUCCESS                Command was executed successfully
  @retval EFI_INVALID_PARAMETER      Invalid command size
  @retval EFI_DEVICE_ERROR           Command failed with an error
  @retval EFI_OUT_OF_RESOURCES       Unable to allocate memory resource
  @retval EFI_TIMEOUT                Command did not complete in given timing requirements
**/
EFI_STATUS
SetLoaderAddressSizeIndicatorInfo (
  IN     SIIP_IP_NAME             IpName,
  IN     SIIP_LOADER_INDEX        LoaderIndex,
  IN     UINT64                   LoadedMemoryAddress,
  IN     UINT32                   SizeOfImage
  )
{
  EFI_STATUS             Status;
  VOID                   *DataBufferLow;
  VOID                   *DataBufferHigh;
  UINT16                 RegisterOffset;

  Status = EFI_SUCCESS;
  DataBufferLow = (VOID *) AllocateZeroPool (sizeof (UINT32 *) * 2);
  DataBufferHigh = (VOID *) AllocateZeroPool (sizeof (UINT32 *) * 2);

  if ((DataBufferLow == NULL) || (DataBufferHigh == NULL)) {
    DEBUG ((DEBUG_ERROR, "AllocatePool failed.\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  switch (LoaderIndex) {
    case LOADER_1:
      RegisterOffset = LOADER_1_OFFSET;
      break;
    case LOADER_2:
      RegisterOffset = LOADER_2_OFFSET;
      break;
    case LOADER_3:
      RegisterOffset = LOADER_3_OFFSET;
      break;
    case LOADER_4:
      RegisterOffset = LOADER_4_OFFSET;
      break;
    default:
      RegisterOffset = LOADER_1_OFFSET; // Defaulted to Loading Address Register 1
      break;
  }

  *(UINT32 *)DataBufferHigh = 0;
  *(UINT32 *)DataBufferLow = 0;

  //Write the address register
  *(UINT32 *) DataBufferHigh = (UINT32) ((LoadedMemoryAddress >> 32) & LOAD_ADDRESS_MASK);
  *(UINT32 *) DataBufferLow = (UINT32) (LoadedMemoryAddress & LOAD_ADDRESS_MASK);

  switch (IpName) {
    case PSE_IP:
      Status = DashboardSendCommand(WRITE, PSE_IP, LOADER,
                                    RegisterOffset + 4, FOUR_BYTES, DataBufferHigh);
      Status = DashboardSendCommand(WRITE, PSE_IP, LOADER,
                                    RegisterOffset, FOUR_BYTES, DataBufferLow);
      break;
    case ACE_IP:
      break;
    default:
      break;
  }

  //Write the size and loading done register
  RegisterOffset += LOAD_DONE_OFFSET;

  *(UINT32 *)DataBufferHigh = 0;
  *(UINT32 *)DataBufferLow = 0;

  switch (IpName) {
    case PSE_IP:
      Status = DashboardSendCommand(READ, PSE_IP, LOADER,
                                    RegisterOffset, FOUR_BYTES, DataBufferLow);
      break;
    case ACE_IP:
      break;
    default:
      break;
  }

  *(UINT32 *) DataBufferHigh = SizeOfImage;
  *(UINT32 *) DataBufferLow = (*(UINT32 *) DataBufferLow & (~(BIT3+BIT2+BIT1))) | BIT0;

  switch (IpName) {
    case PSE_IP:
      Status = DashboardSendCommand(WRITE, PSE_IP, LOADER,
                                    RegisterOffset + 4, FOUR_BYTES, DataBufferHigh);
      Status = DashboardSendCommand(WRITE, PSE_IP, LOADER,
                                    RegisterOffset, FOUR_BYTES, DataBufferLow);
      break;
    case ACE_IP:
      break;
    default:
      break;
  }

  return Status;
}

/**
  Set the Imr Address and Size Info for PSE

  @param[in]     LoadViaImr          To know if this is loaded via IMR, if IMR, need to program last 3 bits.
  @param[in]     IpName              Which IP interface the command needs to be issued
  @param[in]     VerifierIndex       Data which describes the verifier register index
  @param[in]     LoadedMemoryAddress Physical address of the image after the verifier has integrity verified the image
  @param[in]     SizeOfRegion        Size of the IMR region

  @retval EFI_SUCCESS                Command was executed successfully
  @retval EFI_INVALID_PARAMETER      Invalid command size
  @retval EFI_DEVICE_ERROR           Command failed with an error
  @retval EFI_OUT_OF_RESOURCES       Unable to allocate memory resource
  @retval EFI_TIMEOUT                Command did not complete in given timing requirements
**/
EFI_STATUS
SetImrAddressSizeIndicatorInfo (
  IN     BOOLEAN                  LoadViaImr,
  IN     SIIP_IP_NAME             IpName,
  IN     SIIP_IP_IMR_INDEX        ImrIndex,
  IN     UINT64                   LoadedMemoryAddress,
  IN     UINT64                   SizeOfRegion
  )
{
  EFI_STATUS             Status;
  VOID                   *DataBufferLow;
  VOID                   *DataBufferHigh;
  UINT16                 RegisterOffset;

  Status = EFI_SUCCESS;
  DataBufferLow = (VOID *) AllocateZeroPool (sizeof (UINT32 *) * 2);
  DataBufferHigh = (VOID *) AllocateZeroPool (sizeof (UINT32 *) * 2);

  if ((DataBufferLow == NULL) || (DataBufferHigh == NULL)) {
    DEBUG ((DEBUG_ERROR, "AllocatePool failed.\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  switch (ImrIndex) {
    case IMR_1:
      RegisterOffset = IMR_1_ADDRESS_OFFSET;
      break;
    case IMR_2:
      RegisterOffset = IMR_2_ADDRESS_OFFSET;
      break;
    default:
      RegisterOffset = IMR_1_ADDRESS_OFFSET; // Default to IMR Address Register 1
      break;
  }

  *(UINT32 *)DataBufferHigh = 0;
  *(UINT32 *)DataBufferLow = 0;

  //Write the address register
  *(UINT32 *)DataBufferHigh = (UINT32) ((LoadedMemoryAddress >> 32) & VERIFY_ADDRESS_MASK);
  *(UINT32 *)DataBufferLow = (UINT32) (LoadedMemoryAddress & VERIFY_ADDRESS_MASK);

  DEBUG ((DEBUG_INFO, "Setting IMR info to this address: high bytes 0x%x low bytes 0x%x\n",*(UINT32 *)DataBufferHigh,*(UINT32 *)DataBufferLow));
  switch (IpName) {
    case PSE_IP:
      Status = DashboardSendCommand(WRITE, PSE_IP, VERIFIER,
                                    RegisterOffset + 4, FOUR_BYTES, DataBufferHigh);
      Status = DashboardSendCommand(WRITE, PSE_IP, VERIFIER,
                                    RegisterOffset, FOUR_BYTES, DataBufferLow);
      break;
    case ACE_IP:
      break;
    default:
      break;
  }

  //Write the IMR size register
  switch (ImrIndex) {
    case IMR_1:
      RegisterOffset = IMR_1_SIZE_OFFSET;
      break;
    case IMR_2:
      RegisterOffset = IMR_2_SIZE_OFFSET;
      break;
    default:
      RegisterOffset = IMR_1_SIZE_OFFSET; // Default to IMR Size Register 1
      break;
  }

  *(UINT32 *)DataBufferHigh = 0;
  *(UINT32 *)DataBufferLow = 0;

  switch (IpName) {
    case PSE_IP:
      Status = DashboardSendCommand(READ, PSE_IP, VERIFIER,
                                    RegisterOffset, FOUR_BYTES, DataBufferLow);
      break;
    case ACE_IP:
      break;
    default:
      break;
  }

  // Due to the size now represents by kB instead of B, the last 4 bits are used for IMR information.
  // Thus, shifting upper bits by 28, and lower bits by 4, to make space for the IMR mask.
  *(UINT32 *)DataBufferHigh = (UINT32) (SizeOfRegion >> IMR_SIZE_HIGH_OFFSET);

  if (LoadViaImr) {
    *(UINT32 *)DataBufferLow = (UINT32) ((SizeOfRegion << IMR_SIZE_LOW_OFFSET) & IMR_SIZE_MASK) | RS_IMR_MASK;
  } else {
    *(UINT32 *)DataBufferLow = (UINT32) ((SizeOfRegion << IMR_SIZE_LOW_OFFSET) & IMR_SIZE_MASK);
  }

  DEBUG ((DEBUG_INFO, "Setting IMR info to this size: high bytes 0x%x low bytes 0x%x\n",*(UINT32 *)DataBufferHigh,*(UINT32 *)DataBufferLow));
  switch (IpName) {
    case PSE_IP:
      Status = DashboardSendCommand(WRITE, PSE_IP, VERIFIER,
                                    RegisterOffset + 4, FOUR_BYTES, DataBufferHigh);
      Status = DashboardSendCommand(WRITE, PSE_IP, VERIFIER,
                                    RegisterOffset, FOUR_BYTES, DataBufferLow);
      break;
    case ACE_IP:
      break;
    default:
      break;
  }

  return Status;
}

/**
  Set the base address/size/loading done for verifier

  @param[in]     IpName              Which IP interface the command needs to be issued
  @param[in]     VerifierIndex       Data which describes the verifier register index
  @param[in]     LoadedMemoryAddress Physical address of the image after the verifier has integrity verified the image
  @param[in]     SizeOfImage         Size of the image

  @retval EFI_SUCCESS                Command was executed successfully
  @retval EFI_INVALID_PARAMETER      Invalid command size
  @retval EFI_DEVICE_ERROR           Command failed with an error
  @retval EFI_OUT_OF_RESOURCES       Unable to allocate memory resource
  @retval EFI_TIMEOUT                Command did not complete in given timing requirements
**/
EFI_STATUS
SetVerifierAddressSizeIndicatorInfo (
  IN     BOOLEAN                  LoadViaImr,
  IN     SIIP_IP_NAME             IpName,
  IN     SIIP_VERIFIER_INDEX      VerifierIndex,
  IN     UINT64                   LoadedMemoryAddress,
  IN     UINT32                   SizeOfImage
  )
{
  EFI_STATUS             Status;
  VOID                   *DataBufferLow;
  VOID                   *DataBufferHigh;
  UINT16                 RegisterOffset;

  Status = EFI_SUCCESS;
  DataBufferLow = (VOID *) AllocateZeroPool (sizeof (UINT32 *) * 2);
  DataBufferHigh = (VOID *) AllocateZeroPool (sizeof (UINT32 *) * 2);

  if ((DataBufferLow == NULL) || (DataBufferHigh == NULL)) {
    DEBUG ((DEBUG_ERROR, "AllocatePool failed.\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  switch (VerifierIndex) {
    case VERIFIER_1:
      RegisterOffset = VERIFIER_1_OFFSET;
      break;
    case VERIFIER_2:
      RegisterOffset = VERIFIER_2_OFFSET;
      break;
    case VERIFIER_3:
      RegisterOffset = VERIFIER_3_OFFSET;
      break;
    case VERIFIER_4:
      RegisterOffset = VERIFIER_4_OFFSET;
      break;
    default:
      RegisterOffset = VERIFIER_1_OFFSET; // Default to Verification Address Register 1
      break;
  }

  *(UINT32 *)DataBufferHigh = 0;
  *(UINT32 *)DataBufferLow = 0;

  //Write the address register
  *(UINT32 *)DataBufferHigh = (UINT32) ((LoadedMemoryAddress >> 32) & VERIFY_ADDRESS_MASK);
  *(UINT32 *)DataBufferLow = (UINT32) (LoadedMemoryAddress & VERIFY_ADDRESS_MASK);

  DEBUG ((DEBUG_INFO, "Setting verifier info to this address: high bytes 0x%x low bytes 0x%x\n",*(UINT32 *)DataBufferHigh,*(UINT32 *)DataBufferLow));
  switch (IpName) {
    case PSE_IP:
      Status = DashboardSendCommand(WRITE, PSE_IP, VERIFIER,
                                    RegisterOffset + 4, FOUR_BYTES, DataBufferHigh);
      Status = DashboardSendCommand(WRITE, PSE_IP, VERIFIER,
                                    RegisterOffset, FOUR_BYTES, DataBufferLow);
      break;
    case ACE_IP:
      break;
    default:
      break;
  }

  //Write the size and verification done register
  RegisterOffset += VERIFY_DONE_OFFSET;
  *(UINT32 *)DataBufferHigh = 0;
  *(UINT32 *)DataBufferLow = 0;

  switch (IpName) {
    case PSE_IP:
      Status = DashboardSendCommand(READ, PSE_IP, VERIFIER,
                                    RegisterOffset, FOUR_BYTES, DataBufferLow);
      break;
    case ACE_IP:
      break;
    default:
      break;
  }

  *(UINT32 *)DataBufferHigh = SizeOfImage;

  if (LoadViaImr) {
    *(UINT32 *)DataBufferLow = (*(UINT32 *) DataBufferLow & (~(BIT16+BIT3+BIT2+BIT1))) | RS_IMR_MASK | BIT0;
  } else {
    *(UINT32 *)DataBufferLow = (*(UINT32 *) DataBufferLow & (~(BIT16+BIT3+BIT2+BIT1))) | BIT0;
  }

  DEBUG ((DEBUG_INFO, "Setting verifier info to this size: high bytes 0x%x low bytes 0x%x\n",*(UINT32 *)DataBufferHigh,*(UINT32 *)DataBufferLow));
  switch (IpName) {
    case PSE_IP:
      Status = DashboardSendCommand(WRITE, PSE_IP, VERIFIER,
                                    RegisterOffset + 4, FOUR_BYTES, DataBufferHigh);
      Status = DashboardSendCommand(WRITE, PSE_IP, VERIFIER,
                                    RegisterOffset, FOUR_BYTES, DataBufferLow);
      break;
    case ACE_IP:
      break;
    default:
      break;
  }

  return Status;
}

/**
  Get firmware consumed status (Firmware push or pull completed)

  @param[in]     IpName              Which IP interface the command needs to be issued
  @param[in]     VerifierIndex       Data which describes the verifier register index

  @retval EFI_SUCCESS                Success
  @retval EFI_OUT_OF_RESOURCES       Unable to allocate memory resource
  @retval EFI_DEVICE_ERROR           Failure
**/
EFI_STATUS
GetVerifierConsumeStatusInfo (
  IN     SIIP_IP_NAME             IpName,
  IN     SIIP_VERIFIER_INDEX      VerifierIndex
  )
{
  EFI_STATUS             Status;
  VOID                   *DataBuffer;
  UINT32                 Data32;
  UINT32                 *Data32Ptr;
  UINT16                 RegisterOffset;
  UINT32                 Timer;

  DataBuffer = (VOID *) AllocateZeroPool (sizeof (UINT32 *) * 2);
  Data32Ptr = AllocateZeroPool (sizeof (UINT32 *) * 2);
  Data32 = 0;
  Status = EFI_DEVICE_ERROR;

  if ((DataBuffer == NULL) || (Data32Ptr == NULL)) {
    DEBUG ((DEBUG_ERROR, "AllocatePool failed.\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  switch (VerifierIndex) {
    case VERIFIER_1:
      RegisterOffset = VERIFIER_1_OFFSET;
      break;
    case VERIFIER_2:
      RegisterOffset = VERIFIER_2_OFFSET;
      break;
    case VERIFIER_3:
      RegisterOffset = VERIFIER_3_OFFSET;
      break;
    case VERIFIER_4:
      RegisterOffset = VERIFIER_4_OFFSET;
      break;
    default:
      RegisterOffset = VERIFIER_1_OFFSET; // Default to Verification Address Register 1
      break;
  }

  //Read the size and verification done register
  RegisterOffset += VERIFY_DONE_OFFSET;

  DEBUG ((DEBUG_INFO, "Waiting for verifier done bit to be set by IP"));
  Timer = 0;
  while (Timer < VERIFIER_DONE_WAIT_TIME) {
    switch (IpName) {
      case PSE_IP:
        Status = DashboardSendCommand(READ, PSE_IP, VERIFIER, RegisterOffset,
                                      FOUR_BYTES, DataBuffer);
        break;
      case ACE_IP:
        break;
      default:
        break;
    }

    Data32Ptr = DataBuffer;
    Data32 = *Data32Ptr;
    if ((Data32 & BIT16) == BIT16) {
      DEBUG ((DEBUG_INFO, "\tBIT 16 is set. Verifier done is acknowledged by ROM.\n"));
      Status = EFI_SUCCESS;
      return Status;
    }
    MicroSecondDelay (VERIFIER_DONE_PERIOD);
    Timer += VERIFIER_DONE_PERIOD;

    DEBUG ((DEBUG_INFO, "."));
  }
  DEBUG ((DEBUG_INFO, "\tVerifier done bit read timed out and it is NOT acknowledged by ROM.\n"));
  return Status;
}

/*
  Append Tsn Mac Addr sub region data to Pse Fw

  @param[in]       PseFw           Pointer to PSE FW
  @param[in, out]  PseFwSize       Size of PSE FW before and after appending

  @retval EFI_SUCCESS              Success
*/
EFI_STATUS
AppendTsnMacAddrData (
  IN     VOID              *PseFw,
  IN OUT UINT32            *PseFwSize
  )
{
  TSN_MAC_ADDR_SUB_REGION         *TsnMacAddr;
  MAC_CONFIG_DATA                 *TsnMacAddrBuffer;
  UINT8                           Index;
  UINT8                           TsnPortIndex;
  UINT8                           BufferIndex;

  TsnMacAddr = (TSN_MAC_ADDR_SUB_REGION*) mTsnConfig->TsnSubRegion[0].BaseAddress;

  TsnMacAddrBuffer = NULL;
  TsnMacAddrBuffer = (MAC_CONFIG_DATA *) AllocateZeroPool (sizeof (MAC_CONFIG_DATA));
  if (TsnMacAddrBuffer == NULL) {
    DEBUG ((DEBUG_ERROR, "No available memory resource for TsnMacAddrBuffer\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  TsnMacAddrBuffer->Version = TsnMacAddr->Config.Version;
  TsnMacAddrBuffer->NumPorts = 0; // Set PSE owned Tsn port number to 0 by default
  CopyMem (TsnMacAddrBuffer->Signature, TsnMacAddr->Config.Signature, MAC_ADDR_SUB_REGION_SIGNATURE_SIZE);

  BufferIndex = 0;
  for (Index = 0; Index < GetPchMaxPseGbeControllersNum (); Index++) {
    if (mPseConfig->Gbe[Index].OwnerShip == PSE_OWNED) {
      DEBUG ((DEBUG_INFO, "PSE GBE%d is PSE Owned. Load TSN MAC address to IMR\n", Index));
      for (TsnPortIndex = 0; TsnPortIndex < TSN_PORT_MAX; TsnPortIndex++) {
        if ((PseTsnDevNumber (Index) == TsnMacAddr->Config.Port[TsnPortIndex].Bdf.Dev) &&
          (PseTsnFuncNumber (Index) == TsnMacAddr->Config.Port[TsnPortIndex].Bdf.Func)) {
            DEBUG ((DEBUG_INFO, "Loading TSN MAC Address for D:%x,F:%x\n",
                                TsnMacAddr->Config.Port[TsnPortIndex].Bdf.Dev,
                                TsnMacAddr->Config.Port[TsnPortIndex].Bdf.Func));
            TsnMacAddrBuffer->NumPorts++;
            TsnMacAddrBuffer->Port[BufferIndex] = TsnMacAddr->Config.Port[TsnPortIndex];
            BufferIndex++;
            break;
        } else {
          DEBUG ((DEBUG_INFO, "Device not PSE GBE%d, skipping (D:%x,F:%x)\n",
                              Index,
                              TsnMacAddr->Config.Port[TsnPortIndex].Bdf.Dev,
                              TsnMacAddr->Config.Port[TsnPortIndex].Bdf.Func));
        }
      }
    }
  }

  CopyMem (((UINT8 *) PseFw + *PseFwSize), ((UINT8 *) TsnMacAddrBuffer), sizeof (MAC_CONFIG_DATA));
  *PseFwSize += sizeof (MAC_CONFIG_DATA);

  return EFI_SUCCESS;
}

/*
  Append Pse Ip Config sub region data to Pse Fw

  @param[in]       PseFw           Pointer to PSE FW
  @param[in, out]  PseFwSize       Size of PSE FW before and after appending

  @retval EFI_SUCCESS              Success
*/
EFI_STATUS
AppendPseTsnIpConfigData (
  IN     VOID              *PseFw,
  IN OUT UINT32            *PseFwSize
  )
{
  PSE_IP_CONFIG_SUB_REGION        *PseTsnIpConfig;
  IP_CONFIG_DATA                  *PseTsnIpConfigBuffer;
  UINT8                           Index;
  UINT8                           TsnPortIndex;
  UINT8                           BufferIndex;

  PseTsnIpConfig = (PSE_IP_CONFIG_SUB_REGION*) mTsnConfig->TsnSubRegion[1].BaseAddress;

  PseTsnIpConfigBuffer = NULL;
  PseTsnIpConfigBuffer = (IP_CONFIG_DATA *) AllocateZeroPool (sizeof (IP_CONFIG_DATA));
  if (PseTsnIpConfigBuffer == NULL) {
    DEBUG ((DEBUG_ERROR, "No available memory resource for PseTsnIpConfigBuffer\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  PseTsnIpConfigBuffer->Version = PseTsnIpConfig->Config.Version;
  PseTsnIpConfigBuffer->NumPorts = 0; // Set PSE owned Tsn port number to 0 by default
  CopyMem (PseTsnIpConfigBuffer->Signature, PseTsnIpConfig->Config.Signature, IP_SUB_REGION_SIGNATURE_SIZE);

  BufferIndex = 0;
  for (Index = 0; Index < GetPchMaxPseGbeControllersNum (); Index++) {
    if (!mPseConfig->Gbe[Index].OwnerShip == PSE_OWNED) {
      DEBUG ((DEBUG_INFO, "PSE GBE%d is PSE Owned. Load IP data to IMR\n", Index));
      for (TsnPortIndex = 0; TsnPortIndex < TSN_PORT_MAX; TsnPortIndex++) {
        if ((PseTsnDevNumber (Index) == PseTsnIpConfig->Config.Port[TsnPortIndex].Bdf.Dev) &&
          (PseTsnFuncNumber (Index) == PseTsnIpConfig->Config.Port[TsnPortIndex].Bdf.Func)) {
            DEBUG ((DEBUG_INFO, "Loading TSN IP Config for D:%x,F:%x\n",
                                PseTsnIpConfig->Config.Port[TsnPortIndex].Bdf.Dev,
                                PseTsnIpConfig->Config.Port[TsnPortIndex].Bdf.Func));
            PseTsnIpConfigBuffer->NumPorts++;
            PseTsnIpConfigBuffer->Port[BufferIndex] = PseTsnIpConfig->Config.Port[TsnPortIndex];
            BufferIndex++;
            break;
        } else {
          DEBUG ((DEBUG_INFO, "Device not PSE GBE%d, skipping (D:%x,F:%x)\n",
                              Index,
                              PseTsnIpConfig->Config.Port[TsnPortIndex].Bdf.Dev,
                              PseTsnIpConfig->Config.Port[TsnPortIndex].Bdf.Func));
        }
      }
    }
  }

  CopyMem (((UINT8 *) PseFw + *PseFwSize), ((UINT8 *) PseTsnIpConfigBuffer), sizeof (IP_CONFIG_DATA));
  *PseFwSize += sizeof (IP_CONFIG_DATA);

  return EFI_SUCCESS;
}

/*
  Append Tsn Config sub region data to Pse Fw

  @param[in]       PseFw           Pointer to PSE FW
  @param[in, out]  PseFwSize       Size of PSE FW before and after appending

  @retval EFI_SUCCESS              Success
*/
EFI_STATUS
AppendTsnConfigData (
  IN     VOID              *PseFw,
  IN OUT UINT32            *PseFwSize
  )
{
  PSE_TSN_CONFIG_SUB_REGION       *TsnConfigData;
  TSN_CONFIG_DATA                 *TsnConfigDataBuffer;
  UINT8                           TsnPortIndex;
  UINT8                           BufferIndex;
  UINT8                           Index;

  TsnConfigData = (PSE_TSN_CONFIG_SUB_REGION*) mTsnConfig->TsnSubRegion[2].BaseAddress;

  TsnConfigDataBuffer = NULL;
  TsnConfigDataBuffer = (TSN_CONFIG_DATA *) AllocateZeroPool (sizeof (TSN_CONFIG_DATA));
  if (TsnConfigDataBuffer == NULL) {
    DEBUG ((DEBUG_ERROR, "No available memory resource for TsnConfigDataBuffer\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  TsnConfigDataBuffer->Version = TsnConfigData->Config.Version;
  TsnConfigDataBuffer->NumPorts = 0; // Set PSE owned Tsn port number to 0 by default
  CopyMem (TsnConfigDataBuffer->Signature, TsnConfigData->Config.Signature, TSN_SUB_REGION_SIGNATURE_SIZE);

  BufferIndex = 0;
  for (Index = 0; Index < GetPchMaxPseGbeControllersNum (); Index++) {
    if (!mPseConfig->Gbe[Index].OwnerShip == PSE_OWNED) {
      DEBUG ((DEBUG_INFO, "PSE GBE%d is PSE Owned. Load TSN data to IMR\n", Index));
      for (TsnPortIndex = 0; TsnPortIndex < TSN_PORT_MAX; TsnPortIndex++) {
        if ((PseTsnDevNumber (Index) == TsnConfigData->Config.Port[TsnPortIndex].Bdf.Dev) &&
          (PseTsnFuncNumber (Index) == TsnConfigData->Config.Port[TsnPortIndex].Bdf.Func)) {
          if (TsnConfigData->Config.Port[TsnPortIndex].TsnPort.Valid) {
            DEBUG ((DEBUG_INFO, "Loading TSN Config for D:%x,F:%x\n",
                                TsnConfigData->Config.Port[TsnPortIndex].Bdf.Dev,
                                TsnConfigData->Config.Port[TsnPortIndex].Bdf.Func));
            TsnConfigDataBuffer->NumPorts++;
            TsnConfigDataBuffer->Port[BufferIndex].Bdf = TsnConfigData->Config.Port[TsnPortIndex].Bdf;
            TsnConfigDataBuffer->Port[BufferIndex].TsnPort = TsnConfigData->Config.Port[TsnPortIndex].TsnPort;
            BufferIndex++;
            break;
          }
        } else {
          DEBUG ((DEBUG_INFO, "Device not PSE GBE%d, skipping (D:%x,F:%x)\n",
                              Index,
                              TsnConfigData->Config.Port[TsnPortIndex].Bdf.Dev,
                              TsnConfigData->Config.Port[TsnPortIndex].Bdf.Func));
        }
      }
    }
  }

  CopyMem (((UINT8 *) PseFw + *PseFwSize), ((UINT8 *) TsnConfigDataBuffer), sizeof (TSN_CONFIG_DATA));
  *PseFwSize += sizeof (TSN_CONFIG_DATA);

  return EFI_SUCCESS;
}

/*
  Append Tsn data structures to the end of PSE FW in following sequence:
    1) PSE MAC address regtion structure
    2) PSE IP region structure
    3) PSE TSN region structure

  @param[in]       SiPolicy           Pointer to SI_POLICY_PPI
  @param[in]       PseFw              Pointer to PSE FW
  @param[in, out]  PseFwSize          Size of PSE FW before and after appending
  @param[out]      AppendedDataSize   Total size of the data appended to PSE FW

  @retval EFI_SUCCESS              Success
*/
EFI_STATUS
AppendTsnData (
  IN     SI_POLICY_PPI     *SiPolicy,
  IN     VOID              *PseFw,
  IN OUT UINT32            *PseFwSize,
  OUT    UINT32            *AppendedDataSize
  )
{
  EFI_STATUS                      Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gTsnConfigGuid, (VOID *) &mTsnConfig);
  ASSERT_EFI_ERROR (Status);

  AppendTsnMacAddrData (PseFw, PseFwSize);
  AppendPseTsnIpConfigData (PseFw, PseFwSize);
  AppendTsnConfigData (PseFw, PseFwSize);

  *AppendedDataSize = sizeof (MAC_CONFIG_DATA) + sizeof (IP_CONFIG_DATA) + sizeof (TSN_CONFIG_DATA);
  return EFI_SUCCESS;
}

/*
  Add a manifest entry for the data appended to PSE FW

  1. Read count of valid entries in PSE firmware header
  2. Point to the next available manifest entry (valid entry #)
  3. Update manifest structure (comp_name, vendor_name, code_offset, module_size, load_addr)

  @param[in]       PseFw             Pointer to PSE FW
  @param[in]       PseFwSizeOrig     Original size of PSE FW before appending
  @param[in]       AppendedDataSize  Total size of the data to be appended

  @retval EFI_SUCCESS                Success
  @retval EFI_UNSUPPORTED            Manifest table is full
*/
EFI_STATUS
AddManifestEntry (
  IN VOID                  *PseFw,
  IN UINT32                PseFwSizeOrig,
  IN UINT32                AppendedDataSize
)
{
  UINT8                           ValidEntryCount = 0;
  PSE_FW                          *PseFwPtr;

  PseFwPtr = (PSE_FW *) PseFw;
  ValidEntryCount = PseFwPtr->PseHeader.ValidEntryNum;
  if (ValidEntryCount < MAX_VALID_MANIFEST_ENTRIES) {
    CopyMem ((VOID *) PseFwPtr->PseManifest.ManifestEntry[ValidEntryCount].CompName, (VOID *) &PseGbeSubRegionCompName, MAX_COMP_NAME_STRING_SIZE);
    CopyMem ((VOID *) PseFwPtr->PseManifest.ManifestEntry[ValidEntryCount].VendorName, (VOID *) &PseGbeSubRegionVendorName, MAX_VENDOR_NAME_STRING_SIZE);
    PseFwPtr->PseManifest.ManifestEntry[ValidEntryCount].CodeOffset = PseFwSizeOrig;
    PseFwPtr->PseManifest.ManifestEntry[ValidEntryCount].ModuleSize = AppendedDataSize;
    PseFwPtr->PseManifest.ManifestEntry[ValidEntryCount].LoadAddr = PSE_MEM_TSN_DATA_LOAD_ADDR;
    PseFwPtr->PseHeader.ValidEntryNum++;
  } else {
    DEBUG ((DEBUG_INFO, "PSE manifest entries are full\n"));
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}

/*
  Update checksum in PSE FW header

  Calculate the checksum for header + manifest + BUP (excluding 32-bit checksum field)

  @param[in]       PseFw             Pointer to PSE FW

  @retval EFI_SUCCESS                Success
*/
EFI_STATUS
UpdateChecksum (
  IN VOID                  *PseFw
)
{
  VOID                            *CheckSumRegionStart;
  UINT32                          CheckSumRegionSize;
  PSE_FW                          *PseFwPtr;
  UINT32                          CRC32 = 0;

  PseFwPtr = (PSE_FW *) PseFw;
  CheckSumRegionStart = (VOID *) ((UINT8 *) PseFw + sizeof (PseFwPtr->PseHeader.Checksum));
  if (PseFwPtr->PseHeader.BupSize < MAX_BUP_SIZE_FOR_CHECKSUM) {
    CheckSumRegionSize = PseFwPtr->PseHeader.HeaderSize + sizeof (PSE_MANIFEST) + PseFwPtr->PseHeader.BupSize - sizeof (PseFwPtr->PseHeader.Checksum);
  } else {
    CheckSumRegionSize = PseFwPtr->PseHeader.HeaderSize + sizeof (PSE_MANIFEST) + MAX_BUP_SIZE_FOR_CHECKSUM - sizeof (PseFwPtr->PseHeader.Checksum);
  }
  CRC32 = CalculateCrc32 (CheckSumRegionStart, CheckSumRegionSize);
  PseFwPtr->PseHeader.Checksum = CRC32;

  return EFI_SUCCESS;
}

/**
  SIIP Firmware Loading implementation

  Load PSE firmware to IMR region. The flow goes as below steps:
  1. Initialize PSE BAR
  2. Check if BIOS is the loader/verifier
  3. Locate PSE firmware from FV
  4. Initialize MEM Bar
  5. Check and verify PSE IMR allocation
  6. Copy the content of PSE firmware to IMR
  7. Set dashboard registers to reflect PSE IMR address and size

  @param[in]  SiPolicy        Pointer to SI_POLICY_PPI
  @param[in]  SIIP_IP_NAME    The SIIP IP name

  @retval EFI_SUCCESS                Success
  @retval EFI_DEVICE_ERROR           Failure
  @retval EFI_NOT_FOUND              Can't find IP device or misconfigurations
**/
EFI_STATUS
SiipFwLoading (
  IN  SI_POLICY_PPI     *SiPolicy,
  IN  SIIP_IP_NAME      IpName
  )
{
  EFI_STATUS           Status;
  SIIP_CONFIG          *SiipConfig;
  UINT32               PseVerifierCap;
  UINT32               FwSize;
  UINT32               FwSizeOrig;
  UINT32               FwSizeInKb;
  VOID                 *FwBuffer;
  UINT32               *FwBufferDst;
  UINT64               PchPseBase;
  UINT8                PseDeviceNumber;
  UINT8                PseFunctionNumber;
  UINTN                MchBar;
  UINTN                PseBar;
  UINT32               PseFwStatus;
  UINT64               McD0BaseAddress;
  UINT32               PseImrBaseAddressFromIop;
  UINT32               PseImrBaseSizeFromIop;
  UINT32               PseImrBaseAddress;
  UINT64               PseImrBaseSize;
  UINT32               PseImrBaseSizeInKb;
  VOID                 *PseImrPtr;
  UINT32               PseLogData;
  UINT32               AppendedDataSize;
  IMRIAEXCBASE_MCHBAR_CBO_INGRESS_STRUCT         ImrExcBase;
  IMRIAEXCLIMIT_MCHBAR_CBO_INGRESS_STRUCT        ImrExcLimit;

  Status                    = EFI_SUCCESS;
  SiipConfig                = NULL;
  PseVerifierCap            = 0;
  FwSize                    = 0;
  FwSizeOrig                = 0;
  FwSizeInKb                = 0;
  FwBuffer                  = NULL;
  FwBufferDst               = NULL;
  PchPseBase                = 0;
  PseDeviceNumber           = 0;
  PseFunctionNumber         = 0;
  MchBar                    = 0;
  PseBar                    = 0;
  PseFwStatus               = 0;
  McD0BaseAddress           = 0;
  PseImrBaseAddressFromIop  = 0;
  PseImrBaseSizeFromIop     = 0;
  PseImrBaseAddress         = 0;
  PseImrBaseSize            = 0;
  PseImrBaseSizeInKb        = 0;
  PseImrPtr                 = NULL;
  PseLogData                = 0;
  AppendedDataSize          = 0;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPseConfigGuid, (VOID *) &mPseConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicy, &gSiipConfigGuid, (VOID *) &SiipConfig);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "Error, unable to locate SIIP Config\n"));
  } else {
    if (!IsPseEnabled()) {
      DEBUG ((DEBUG_INFO, "PSE controller is diabled\n"));
      return EFI_UNSUPPORTED;
    }

    DEBUG ((EFI_D_INFO, "[PSE] Firmware loading begins.\n"));
    DEBUG ((DEBUG_INFO, "Found SIIP base address at 0x%x, size is 0x%x\n", SiipConfig->BaseAddress, SiipConfig->Size));

    PseDeviceNumber = PseGetDeviceNumber ();
    PseFunctionNumber = PseGetFunctionNumber ();
    //
    // Init PSE BAR
    //
    PchPseBase = PCI_SEGMENT_LIB_ADDRESS (
                   DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                   DEFAULT_PCI_BUS_NUMBER_PCH,
                   PseDeviceNumber,
                   PseFunctionNumber,
                   0
                   );
    if (PciSegmentRead16 (PchPseBase + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
      DEBUG ((EFI_D_INFO, "PseBaseAddress: 0xFFFF.\n"));
      return EFI_NOT_READY;
    } else {
      PciSegmentAnd8 (PchPseBase + PCI_COMMAND_OFFSET, (UINT8)~(EFI_PCI_COMMAND_MEMORY_SPACE));
      PciSegmentWrite32 (PchPseBase + R_PSE_CFG_BAR0_LOW, PCH_PSE_BASE_ADDRESS);
      PciSegmentWrite32 (PchPseBase + R_PSE_CFG_BAR0_HIGH, 0);
      PciSegmentOr32 (PchPseBase + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_BUS_MASTER | EFI_PCI_COMMAND_MEMORY_SPACE);
    }


    Status = GetVerifierCapabilityInfo (PSE_IP, &PseVerifierCap);
    if (Status != EFI_SUCCESS) {
      DEBUG ((EFI_D_INFO, "GetVerifierCapabilityInfo failed. Status: %x!\n", Status));
      return EFI_INVALID_PARAMETER;
    } else {
      DEBUG ((EFI_D_INFO, "PseVerifierCap : %x\n", PseVerifierCap));
      DEBUG ((EFI_D_INFO, "Is BIOS the verifier? : %x\n", ((PseVerifierCap & BIOS_IS_CAPABLE) != 0)));
    }

    // WA, set pinmux for UART2 to be OSE owned for logs
    //GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_UART_RX (2), mPseConfig->Uart[2].PinMux.Rx);
    //GpioSetNativePadByFunction (GPIO_FUNCTION_PSE_UART_TX (2), mPseConfig->Uart[2].PinMux.Tx);


  //  if ((PseVerifierCap & BIOS_IS_CAPABLE) != 0) {
      FwBuffer = (VOID *) SiipConfig->BaseAddress;
      FwSize = SiipConfig->Size;
      DEBUG ((EFI_D_INFO, "\tPSE FwSize: %x \n", FwSize));

      if (FwBuffer == NULL) {
        DEBUG ((EFI_D_INFO, "Firmware buffer not found\n"));
        SetVerifierErrorInfo (PSE_IP, VERIFIER_1, NOT_FOUND);
        return EFI_NOT_FOUND;
      }

      if (FwSize == 0) {
        DEBUG ((EFI_D_INFO, "Firmware size is 0\n"));
        SetVerifierErrorInfo (PSE_IP, VERIFIER_1, NOT_FOUND);
        return EFI_INVALID_PARAMETER;
      }

      FwSizeOrig = FwSize;
      AppendTsnData (SiPolicy, FwBuffer, &FwSize, &AppendedDataSize);
      if ((FwSize & 0x3FF) != 0) {
        FwSizeInKb = (UINT32) ((FwSize >> 10) + 1);
      } else {
        FwSizeInKb = (UINT32) (FwSize >> 10);
      }
      DEBUG ((EFI_D_INFO, "\tAfter TSN data appended: PSE FwSize: %x, FwSizeInKb: %x \n", FwSize, FwSizeInKb));

      AddManifestEntry (FwBuffer, FwSizeOrig, AppendedDataSize);
      UpdateChecksum (FwBuffer);

      //
      // Identify MEM BAR for IMR address, if valid, copy the PSE firmware to IMR address
      //
      McD0BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, 0);
      if (PciSegmentRead16 (McD0BaseAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
        DEBUG ((EFI_D_INFO, "McD0BaseAddress: 0xFFFF.\n"));
        return EFI_DEVICE_ERROR;
      } else {
        MchBar = PciSegmentRead32 (McD0BaseAddress + R_SA_MCHBAR) & ~BIT0;
        PseImrBaseAddressFromIop = MmioRead32 (MchBar + R_IOP_IMR10_ADDRESS_OFFSET);
        PseImrBaseAddress = PseImrBaseAddressFromIop << 10;
        PseImrPtr = (VOID *) PseImrBaseAddress;

        PseImrBaseSizeFromIop = MmioRead32 (MchBar + R_IOP_IMR10_SIZE_OFFSET);
        PseImrBaseSize = (UINT64) (((~(PseImrBaseSizeFromIop << 10)) + 1) & 0x0000007FFFFFFFFFULL);
        PseImrBaseSizeInKb = (UINT32) (PseImrBaseSize >> 10);
        DEBUG ((EFI_D_INFO, "\tIMR10 at 0x%X has size 0x%08llX in b, 0x%X in Kb\n", PseImrPtr, PseImrBaseSize, PseImrBaseSizeInKb));
        DEBUG ((EFI_D_INFO, "\tIMR10 offset 0x7A40 is 0x%x\n", MmioRead32 (MchBar + 0x7a40)));
        DEBUG ((EFI_D_INFO, "\tIMR10 offset 0x7A44 is 0x%x\n", MmioRead32 (MchBar + 0x7a44)));
        DEBUG ((EFI_D_INFO, "\tIMR10 offset 0x7A48 is 0x%x\n", MmioRead32 (MchBar + 0x7a48)));
        DEBUG ((EFI_D_INFO, "\tIMR10 offset 0x7A50 is 0x%x\n", MmioRead32 (MchBar + 0x7a50)));
        DEBUG ((EFI_D_INFO, "\tIMR10 offset 0x7A58 is 0x%x\n", MmioRead32 (MchBar + 0x7a58)));
      }

      //
      // if IMR10 is allocated for PSE, PSE will be loaded through IMR.
      //
      if (PseImrBaseSizeInKb > 0) {
        DEBUG ((EFI_D_INFO, "Loading firmware through IMR.\n"));

        // Dump out IMR IOP register values for debug purpose
        // for (UINT32 Count = 0; Count < 166; Count++) {
        //   PseImrBaseSizeFromIop = MmioRead32(MchBar + 0x7900 + (Count*4));
        //   DEBUG ((EFI_D_INFO, "\tOffset %x : %x\n", 0x7900 + (Count*4), PseImrBaseSizeFromIop));
        // }

        //
        // Simple read write to test IMR access
        //
        FwBufferDst = (UINT32 *) PseImrPtr;
        *FwBufferDst = 0xDEADBEEF;
        if (*FwBufferDst != 0xDEADBEEF) {
          DEBUG ((EFI_D_INFO, "Failed to r/w to IMR region. Expecting 0xDEADBEEF, getting 0x%x\n", *FwBufferDst));
          return EFI_DEVICE_ERROR;
        }
        if (PseImrBaseSizeInKb < FwSizeInKb) {
          DEBUG ((EFI_D_INFO, "\tERROR! IMR region allocated is less than PSE firmware size!"));
          return EFI_INVALID_PARAMETER;
        } else {
          CopyMem (PseImrPtr, FwBuffer, FwSize);
          DEBUG ((EFI_D_INFO, "\tCopied from FwBuffer 0x%x to IMR address 0x%x with size 0x%x\n", FwBuffer, PseImrPtr, FwSize));

          // Debug: read and compare PSE fw contents before and after the memory copy.
          DEBUG_CODE_BEGIN ();
            FwBufferDst = (UINT32 *) FwBuffer;
            DEBUG ((EFI_D_INFO, "\n\n (DDR) Pse zephyr firmware dump: from %x\n", FwBufferDst));
            for (UINT32 fw_i = 0; fw_i < 30; fw_i++) {
              if ((fw_i % 10) == 0){
                DEBUG ((EFI_D_INFO, "\n"));
              }
              DEBUG ((EFI_D_INFO, "0x%08x ",*(FwBufferDst + fw_i)));
            }
            FwBufferDst = (UINT32 *) PseImrPtr;
            DEBUG ((EFI_D_INFO, "\n\n (IMR) Pse zephyr firmware dump: from %x\n", FwBufferDst));
            for (UINT32 fw_i = 0; fw_i < 30; fw_i++) {
              if ((fw_i % 10) == 0){
                DEBUG ((EFI_D_INFO, "\n"));
              }
              DEBUG ((EFI_D_INFO, "0x%08x ",*(FwBufferDst + fw_i)));
            }
          if ((*(UINT32 *) FwBuffer) != (*(UINT32 *) PseImrPtr)) {
            DEBUG ((EFI_D_INFO, "IMR copy failed! Proceed to DRAM path\n"));
            goto LOAD_VIA_DRAM;
          }
          DEBUG_CODE_END ();
          //
          // PSE specific general purpose register programming
          //
          if (IpName == PSE_IP) {
            //
            // This needs to be set before PSE FW loading
            // GP3_0 is used for log output channel for PSE
            // GP3_1 is used for log regions information in the memory
            //
            PseLogData = mPseConfig->PseLogOutputChannel;

            // RCR for JTAG switch
            // https://hsdes.intel.com/appstore/article/#/1507342993
            if (mPseConfig->PseJtagEnabled){
              DEBUG ((EFI_D_INFO, "Set JTAG debug bit - BIT13\n"));
              PseLogData = PseLogData | BIT13;
            } else {
              DEBUG ((EFI_D_INFO, "Clear JTAG debug bit - BIT13\n"));
              PseLogData = PseLogData & ~BIT13;
            }

            DEBUG ((EFI_D_INFO, "Writing PSE Log Output Channel to %x\n", PseLogData));
            Status = DashboardSendCommand(WRITE, PSE_IP, VERIFIER,
                    SIIP_GP3_0, FOUR_BYTES, &PseLogData);
            PseLogData = mPseConfig->PseLogOutputSize << 16 | mPseConfig->PseLogOutputOffset;
            DEBUG ((EFI_D_INFO, "Writing PSE Log Region Information to %x\n", PseLogData));
            Status = DashboardSendCommand(WRITE, PSE_IP, VERIFIER,
                    SIIP_GP3_1, FOUR_BYTES, &PseLogData);
          }
          //
          // Write IMR region and size to dashboard IMR registers.
          //
          SetImrAddressSizeIndicatorInfo (TRUE, PSE_IP, IMR_1, (UINT64) PseImrPtr, (UINT64) PseImrBaseSizeInKb);
          SetVerifierAddressSizeIndicatorInfo (TRUE, PSE_IP, VERIFIER_1, (UINT64) PseImrPtr, FwSizeInKb);
        }
      } else {
LOAD_VIA_DRAM:
        DEBUG ((EFI_D_INFO, "Loading firmware through DRAM.\n"));

        // Debug: read and compare PSE fw contents before and after the memory copy.
        FwBufferDst = (UINT32 *) FwBuffer;
        DEBUG ((EFI_D_INFO, "\n\n (DDR) Pse zephyr firmware dump: from %x\n", FwBufferDst));
        for (UINT32 fw_i = 0; fw_i < 30; fw_i++) {
          if ((fw_i % 10) == 0){
            DEBUG ((EFI_D_INFO, "\n"));
          }
          DEBUG ((EFI_D_INFO, "0x%08x ",*(FwBufferDst + fw_i)));
        }
        //
        // PSE specific general purpose register programming
        //
        if (IpName == PSE_IP) {
          //
          // This needs to be set before PSE FW loading
          // GP3_0 is used for log output channel for PSE
          // GP3_1 is used for log regions information in the memory
          //
          PseLogData = mPseConfig->PseLogOutputChannel;
          DEBUG ((EFI_D_INFO, "Writing PSE Log Output Channel to %x\n", PseLogData));
          Status = DashboardSendCommand(WRITE, PSE_IP, VERIFIER,
                  SIIP_GP3_0, FOUR_BYTES, &PseLogData);
          PseLogData = mPseConfig->PseLogOutputSize << 16 | mPseConfig->PseLogOutputOffset;
          DEBUG ((EFI_D_INFO, "Writing PSE Log Region Information to %x\n", PseLogData));
          Status = DashboardSendCommand(WRITE, PSE_IP, VERIFIER,
                  SIIP_GP3_1, FOUR_BYTES, &PseLogData);
        }
        //
        // Write pse region and size to dashboard registers.
        //
        SetImrAddressSizeIndicatorInfo (FALSE, PSE_IP, IMR_1, (UINT64) FwBuffer, (UINT64) FwSizeInKb);
        SetVerifierAddressSizeIndicatorInfo (FALSE, PSE_IP, VERIFIER_1, (UINT64) FwBuffer, FwSizeInKb);
      }
      Status = GetVerifierConsumeStatusInfo (PSE_IP, VERIFIER_1);
      if (Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_INFO, "Loading done not set by ROM.\n"));
      }
      PseBar = AcquirePseBar ();
      PseFwStatus = MmioRead32 (PseBar + R_PSE_MMIO_FWSTS_OFFSET);
      DEBUG ((EFI_D_INFO, "PSE Firmware Status is %x read from address %x\n", PseFwStatus, PseBar + R_PSE_MMIO_FWSTS_OFFSET));
      if (((PseFwStatus & B_FW_STATUS_MASK) >> R_FW_STATUS_OFFSET) >= 6) {
        DEBUG ((EFI_D_INFO, "BIOS WA: PSE FW is loaded and running\n"));
      } else {
        DEBUG ((EFI_D_INFO, "BIOS WA: PSE FW is NOT loaded\n"));
      }
   // } else {
   //   DEBUG ((EFI_D_INFO, "\tSince BIOS is not the PSE loader/verifier, the firmware is not loaded.\n"));
   // }
  }

  //
  //  MRC needs to configure IA and GT exclusion range to cover the IMR region.
  //    IMRIAEXCLBASE (MCHBAR + 0x6A40h[38:10]) and IMRGTEXCLBASE (MCHBAR + 0x6A48h[38:10]) should be programmed to the lowest address (base) of the IMR region.
  //    IMRIAEXCLIMIT (MCHBAR + 0x6A50h[38:10]) should be programmed to the highest address (base + IMR Size) of the IMR region.
  //    IMRGTEXCLIMIT (MCHBAR + 0x6A58h[38:10]) should be programmed to the highest address (base + Size) of the combined (IMR / DPR / PRMRR / TSEG) stolen region.
  //    Note: the programming of "base + size" here as opposed to "base + size - 1" is intended.
  //
  ImrExcBase.Data                     = 0;
  ImrExcLimit.Data                    = 0;
  ImrExcBase.Bits.imriaexcbaseLow     = 0x7A0 << 10;
  ImrExcBase.Bits.imriaexcbaseHigh    = 0x7A0 >> 12;
  ImrExcLimit.Bits.imriaexclimitLow   = (0x7A0 + 0x40) << 10;
  ImrExcLimit.Bits.imriaexclimitHigh  = (0x7A0 + 0x40) >> 12;

  MchBar = PciSegmentRead32 (McD0BaseAddress + R_SA_MCHBAR) & ~BIT0;
  MmioWrite64 (MchBar + IMRIAEXCBASE_MCHBAR_CBO_INGRESS_REG, ImrExcBase.Data);
  MmioWrite64 (MchBar + IMRIAEXCLIMIT_MCHBAR_CBO_INGRESS_REG, ImrExcBase.Data);

  ImrExcLimit.Bits.imriaexclimitLow  = (0x7F0 + 0x10) << 10;
  ImrExcLimit.Bits.imriaexclimitHigh = (0x7F0 + 0x10) >> 12;

  MmioWrite64 (MchBar + IMRGTEXCBASE_MCHBAR_CBO_INGRESS_REG, ImrExcBase.Data);
  MmioWrite64 (MchBar + IMRGTEXCLIMIT_MCHBAR_CBO_INGRESS_REG, ImrExcBase.Data);

  return Status;
}
