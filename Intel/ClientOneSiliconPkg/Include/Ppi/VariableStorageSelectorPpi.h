/** @file
  This file declares the Variable Storage PPI

  The Variable Storage PPI is used to acquire the variable storage
  instance ID (GUID) for a particular variable name and vendor GUID. This ID
  is used to find the appropriate variable storage PPI.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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
#ifndef _PEI_VARIABLE_STORAGE_SELECTOR_PPI_H_
#define _PEI_VARIABLE_STORAGE_SELECTOR_PPI_H_

extern EFI_GUID gEdkiiVariableStorageSelectorPpiGuid;

///
/// Revision
///
#define PEI_VARIABLE_STORAGE_PPI_REVISION  1

typedef struct _EDKII_VARIABLE_STORAGE_SELECTOR_PPI  EDKII_VARIABLE_STORAGE_SELECTOR_PPI;

/**
  Gets the ID (GUID) for the variable storage instance that is used to store a given variable.

  @param[in]  VariableName       A pointer to a null-terminated string that is
                                 the variable's name.
  @param[in]  VariableGuid       A pointer to an EFI_GUID that is the variable's
                                 GUID. The combination of VariableGuid and
                                 VariableName must be unique.
  @param[out] VariableStorageId  The ID for the variable storage instance that
                                 stores a given variable

  @retval     EFI_SUCCESS        Variable storage instance ID that was retrieved
**/
typedef
EFI_STATUS
(EFIAPI *PEI_EDKII_VARIABLE_STORAGE_SELECTOR_GET_ID)(
  IN  CONST  CHAR16       *VariableName,
  IN  CONST  EFI_GUID     *VendorGuid,
  OUT        EFI_GUID     *VariableStorageId
  );

///
/// Variable Storage PPI
///
struct _EDKII_VARIABLE_STORAGE_SELECTOR_PPI {
  PEI_EDKII_VARIABLE_STORAGE_SELECTOR_GET_ID    GetId;      ///< Retrieves an instance-specific variable storage ID
};

#endif
