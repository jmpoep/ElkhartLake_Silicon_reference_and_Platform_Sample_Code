/** @file
  Power state and boot mode save and restore data functions.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2018 Intel Corporation.

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
#ifndef _MrcSaveRestore_h_
#define _MrcSaveRestore_h_
#pragma pack(push, 1)


#include "MrcTypes.h"
#include "MrcApi.h"
#include "MrcGlobal.h"

typedef struct {
  UINT16 StartMchbarOffset;
  UINT16 EndMchbarOffset;
} SaveDataControl;

/**
  This function verifies that neither CPU fuses or DIMMs have changed.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess if fast boot is allowed, otherwise mrcColdBootRequired.
**/
extern
MrcStatus
MrcFastBootPermitted (
  IN     MrcParameters *const MrcData
  );

/**
  This function saves any values that need to be used during non-cold boots.

  @param[in, out] MrcData - Include all the MRC global data.

  @retval mrcSuccess if the save occurred with no errors, otherwise returns an error code.
**/
extern
MrcStatus
MrcSaveMCValues (
  IN OUT MrcParameters *const MrcData
  );

/**
  This function saves any values that need to be used during non-cold boots which may have changed

  @param[in, out] MrcData - Include all the MRC global data.

  @retval mrcSuccess if the save occurred with no errors, otherwise returns an error code.
**/
extern
MrcStatus
MrcUpdateSavedMCValues (
  IN OUT MrcParameters *const MrcData
  );

/**
  This function saves any remaining values that need to be used during non-cold boots.

  @param[in, out] MrcData - Include all the MRC global data.

  @retval mrcSuccess if the save occurred with no errors, otherwise returns an error code.
**/
extern
MrcStatus
MrcSaveMCValuesFinal (
  IN OUT MrcParameters *const MrcData
  );

/**
  This function copies the non-training information that needs to be restored
  from the 'save' data structure to the 'Output' data structure.

  @param[in, out] MrcData - include all the MRC global data.

  @retval mrcSuccess if the copy completed with no errors, otherwise returns an error code.
**/
extern
MrcStatus
MrcRestoreNonTrainingValues (
  IN OUT MrcParameters *const MrcData
  );

/**
  This function writes the previously determined training values back to the memory controller.

  @param[in] MrcData - Include all the MRC global data.

  @retval mrcSuccess if the memory controller write back completed with no errors, otherwise returns an error code.
**/
extern
MrcStatus
MrcRestoreTrainingValues (
  IN     MrcParameters *const MrcData
  );


#ifdef UP_SERVER_FLAG
/**
  This function Print the CLTM related registers.

  @param MrcData - Include all the MRC global data.

  @retval None.
**/
extern
void
MrcCltmPrintMchRegisters (
  MrcParameters          *MrcData
  );
#endif

#pragma pack(pop)
#endif
