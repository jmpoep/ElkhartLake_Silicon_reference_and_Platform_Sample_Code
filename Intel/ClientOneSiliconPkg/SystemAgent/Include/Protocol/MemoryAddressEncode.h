/** @file
  This protocol provides the API to decode and encode memory addresses.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2017 Intel Corporation.

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
#ifndef _MEMORY_ADDRESS_ENCODE_H_
#define _MEMORY_ADDRESS_ENCODE_H_

//
// Extern the GUID for protocol users.
//
extern EFI_GUID gMemoryAddressEncodeDecodeProtocolGuid;

//
// The detail information of DramAddress
//
typedef struct {
  UINT8  Controller;    ///< Zero based Controller number.
  UINT8  ChannelNumber; ///< Zero based Channel number.
  UINT8  DimmNumber;    ///< Zero based DIMM number.
  UINT8  Rank;          ///< Zero based Rank number.
  UINT8  BankGroup;     ///< Zero based Bank group number.
  UINT8  Bank;          ///< Zero based Bank number.
  UINT16 Cas;           ///< Zero based CAS number.
  UINT32 Ras;           ///< Zero based RAS number.
} DRAM_ADDRESS;

/**
  Address decode function
  Converts memory address to DRAM address

  @param[in]      MemoryAddress  - The 39-bit memory address to decode.
  @param[out]     DramAddress    - The DRAM address struct that the memory address decodes to.

  @retval Returns EFI_SUCCESS if successful, EFI_UNSUPPORTED otherwise.
**/
typedef
EFI_STATUS
(EFIAPI *MEMORY_ADDRESS_DECODE) (
  IN  UINT64       MemoryAddress,
  OUT DRAM_ADDRESS *DramAddress
  );

/**
  Address encode function (reverse address decode)
  DRAM address to memory address conversion

  @param[in]      DramAddress    - The DRAM address that is to be encoded.
  @param[out]     MemoryAddress  - The 39-bit memory address to convert to.

  @retval Returns EFI_SUCCESS if successful, EFI_UNSUPPORTED otherwise.
**/
typedef
EFI_STATUS
(EFIAPI *MEMORY_ADDRESS_ENCODE) (
  IN  DRAM_ADDRESS *DramAddress,
  OUT UINT64       *MemoryAddress
  );

///
/// Memory Encode/Decode Protocol definition
///
typedef struct _MEMORY_ADDRESS_ENCODE_DECODE_PROTOCOL {
  MEMORY_ADDRESS_ENCODE  MemoryAddressEncode; ///< Memory Encode Function. Converts Memory Address to DRAM Address
  MEMORY_ADDRESS_DECODE  MemoryAddressDecode; ///< Memory Decode Function. Converts DRAM Address to Memory Address
} MEMORY_ADDRESS_ENCODE_DECODE_PROTOCOL;

#endif
