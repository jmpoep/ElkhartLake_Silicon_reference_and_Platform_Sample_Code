/** @file
  This file defines the Silicon Temp Ram Exit PPI which implements the MTRR values initialization.

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
#ifndef _FSP_TEMP_RAM_EXIT_PPI_H_
#define _FSP_TEMP_RAM_EXIT_PPI_H_

///
/// Global ID for the FSP_TEMP_RAM_EXIT_PPI.
///
#define FSP_TEMP_RAM_EXIT_GUID \
  { \
    0xbc1cfbdb, 0x7e50, 0x42be, { 0xb4, 0x87, 0x22, 0xe0, 0xa9, 0x0c, 0xb0, 0x52 } \
  }

//
// Forward declaration for the FSP_TEMP_RAM_EXIT_PPI.
//
typedef struct _FSP_TEMP_RAM_EXIT_PPI FSP_TEMP_RAM_EXIT_PPI;

/**
  Program MTRR values and print MTRRs.
**/
typedef
EFI_STATUS
(EFIAPI *FSP_TEMP_RAM_EXIT) (
  IN  VOID    *TempRamExitParamPtr
  );

///
/// This PPI provides function to program MTRR values
///
struct _FSP_TEMP_RAM_EXIT_PPI {
  FSP_TEMP_RAM_EXIT   TempRamExit;
};

extern EFI_GUID gFspTempRamExitPpiGuid;

#endif // _FSP_TEMP_RAM_EXIT_PPI_H_
