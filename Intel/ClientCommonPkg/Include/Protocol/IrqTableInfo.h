/** @file
 This file contains Protocol definitions for IrqTableInfo.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2016 Intel Corporation.

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

#ifndef _IRQ_TABLE_INFO_H_
#define _IRQ_TABLE_INFO_H_

typedef struct _IRQ_TABLE_INFO_PROTOCOL IRQ_TABLE_INFO_PROTOCOL;

/**
  Initialize legacy IRQ table - MP table, and PIRQ table environment.

  @param  This                 A pointer to the calling context.
  @param  PciAutoDetect        TRUE means BIOS will automatically detect all PCI
                                 devices in system and add IRQ entry to MP table
                                 and PIRQ table. If so, IRQ information of all
                                 PCI devices can be found in final table,
                                 including the one in slot.
                               FALSE means BIOS will just use the IRQ table
                                 created at build phase. If so, only on-board PCI
                                 devices will have IRQ information, because
                                 addin-card IRQ info is not assigned at build time.

  @retval EFI_SUCCESS          The function completed successfully
**/
typedef
EFI_STATUS
(EFIAPI *IRQ_TABLE_INFO_INITIALIZE) (
  IN IRQ_TABLE_INFO_PROTOCOL  *This,
  IN BOOLEAN                  PciAutoDetect
  );

/**
  Return MP table.

  @param  This                 A pointer to the calling context.
  @param  MpTable              Mp table header pointer.

  @retval EFI_SUCCESS          The function completed successfully
  @retval EFI_NOT_FOUND        Table not found
**/
typedef
EFI_STATUS
(EFIAPI *IRQ_TABLE_INFO_GET_MP_TABLE) (
  IN IRQ_TABLE_INFO_PROTOCOL  *This,
  OUT VOID                    **MpTable
  );

/**
  Return PIRQ table.

  @param  This                 A pointer to the calling context.
  @param  PirqTable            Pirq table header pointer.

  @retval EFI_SUCCESS          The function completed successfully
  @retval EFI_NOT_FOUND        Table not found
**/
typedef
EFI_STATUS
(EFIAPI *IRQ_TABLE_INFO_GET_PIRQ_TABLE) (
  IN IRQ_TABLE_INFO_PROTOCOL  *This,
  OUT VOID                    **PirqTable
  );

//
// Definition of IRQ Table Info Protocol.
//
typedef struct _IRQ_TABLE_INFO_PROTOCOL {
  IRQ_TABLE_INFO_INITIALIZE      Initialize;
  IRQ_TABLE_INFO_GET_MP_TABLE    GetMpTable;
  IRQ_TABLE_INFO_GET_PIRQ_TABLE  GetPirqTable;
} IRQ_TABLE_INFO_PROTOCOL;

#endif //IRQ_TABLE_INFO_H_
