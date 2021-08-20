/**@file
This file defines EDK FPDT Performance protocols.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2016 Intel Corporation.

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

#ifndef __FPDT_FIRMWARE_PERFORMANCE_PROTOCOL_H__
#define __FPDT_FIRMWARE_PERFORMANCE_PROTOCOL_H__

typedef struct _FIRMWARE_PERFORMANCE_PROTOCOL FIRMWARE_PERFORMANCE_PROTOCOL;

//
// Firmware Performance Protocol definition
//
/** 
  Logs performance data according to record type.
  
  @param  This                    Calling context
  @param  Handle                  Pointer to environment specific context used
                                  to identify the component being measured.
  @param  RecordType              Type of FPDT record
  @param  Ticker                  TSC value or Address to the pointer record
  @param  Identifier              Identifier for FPDT records

  @retval EFI_SUCCESS             The data was read correctly from the device.
  @retval EFI_UNSUPPORTED         Record is not supported. 
  @retval EFI_ABORTED             Type of record is not defined
  
**/
typedef
EFI_STATUS
(EFIAPI *FIRMWARE_PERFORMANCE_PROTOCOL_INSERT_MEASUREMENT) (
  IN FIRMWARE_PERFORMANCE_PROTOCOL            *This,
  IN EFI_HANDLE                               Handle,
  IN UINT16                                   RecordType,
  IN UINT64                                   Ticker,
  IN UINT16                                   Identifier
  );

/** 
  Logs performance data according to record type into pre-allocated buffer
  
  @param[in]  This                    Calling context
  @param[out] PerformanceBuffer       Pointer to to pre-allocated memory buffer.

  @retval EFI_SUCCESS                 Located protocol successfully.
  @retval EFI_NOT_FOUND               Fail to locate protocol or invalide returned pointer
  
**/
typedef
EFI_STATUS
(EFIAPI *FIRMWARE_PERFORMANCE_PROTOCOL_GET_PERFBUFFER_ADDR) (
  IN  FIRMWARE_PERFORMANCE_PROTOCOL *This,
  OUT UINT32                        *PerformanceBuffer
  );

/** 
  Retrieves length of performance buffer
  
  @param[in]  This                    Calling context

  @retval mPerformanceLength          length of pre-allocated memory buffer
  
**/
typedef
UINT32
(EFIAPI *FIRMWARE_PERFORMANCE_PROTOCOL_GET_PERFBUFFER_LEN) (
  IN FIRMWARE_PERFORMANCE_PROTOCOL *This
  );

struct _FIRMWARE_PERFORMANCE_PROTOCOL {
  FIRMWARE_PERFORMANCE_PROTOCOL_INSERT_MEASUREMENT  InsertMeasurement;
  FIRMWARE_PERFORMANCE_PROTOCOL_GET_PERFBUFFER_ADDR GetPerfBufferAddr;
  FIRMWARE_PERFORMANCE_PROTOCOL_GET_PERFBUFFER_LEN  GetPerfBufferLength;
};

typedef struct _FPDT_PERFORMANCE_PROTOCOL FPDT_PERFORMANCE_PROTOCOL;

/**
  Returns FPDT ACPI table address

  @param [in]  This        Pointer to the FPDT Performance Protocol Interface
  @param [out] FpdtAddress Pointer to the got FPDT table.

  @retval EFI_UNSUPPORTED FPDT table is not installed or supported.
  @retval EFI_SUCCESS     Valid pointer to FPDT
**/
typedef
EFI_STATUS
(EFIAPI *FPDT_PERFORMANCE_PROTOCOL_GET_FPDT_ADDRESS) (
  IN FPDT_PERFORMANCE_PROTOCOL   *This,
  OUT UINT32                     *FpdtAddress
  );

/**
  Update FPDT table to log table pointer records for future integration into FPDT

  @param[in] This        Pointer to the FPDT Performance Protocol Interface
  @param[in] Handle      Handle of the calling image
  @param[in] RecordType  Record type to indicate what record is being modified
  @param[in] Data        TSC value or Address to the pointer record
  @param[in] Identifier  Progress Id. 

  @retval EFI_SUCCESS           Table/record successfully updated
  @retval EFI_UNSUPPORTED       Table record/data not defined
**/
typedef
EFI_STATUS
(EFIAPI *FPDT_PERFORMANCE_PROTOCOL_UPDATE_RECORD) (
  IN FPDT_PERFORMANCE_PROTOCOL              *This,
  IN EFI_HANDLE                             Handle,
  IN UINT16                                 Recordtype,
  IN UINT64                                 Data,
  IN UINT16                                 Identifier
  );

typedef struct _FPDT_PERFORMANCE_PROTOCOL {
  FPDT_PERFORMANCE_PROTOCOL_GET_FPDT_ADDRESS  GetFpdtAddress;
  FPDT_PERFORMANCE_PROTOCOL_UPDATE_RECORD     UpdateRecord;
} FPDT_PERFORMANCE_PROTOCOL;

#endif
