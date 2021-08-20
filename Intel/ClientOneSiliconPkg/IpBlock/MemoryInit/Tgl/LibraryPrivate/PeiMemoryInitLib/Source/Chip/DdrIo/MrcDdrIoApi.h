/** @file
  Contains functions that are used outside of the DdrIo Library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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
#ifndef _MrcDdrIoApi_h_
#define _MrcDdrIoApi_h_

/// Defines
#define MRC_DDRIO_RX_TO_FIFO_GB_PS  (500)

/// Functions
/**
  This function runs Comp Calibration.

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcSuccess if successful or an error status
**/
MrcStatus
MrcDdrCompCalPre (
  IN OUT MrcParameters *const MrcData
  );

/**
  This function train the current supply for the DCO such that the FLL is able to hit 4 GHz.

  @param[in]  MrcData - Pointer to global data.

  @retval MrcStatus - mrcFail if Inputs->ExitOnFailure is set and we cannot reach 4 GHz; otherwise mrcSuccess.
**/
MrcStatus
MrcFllInit (
  IN  MrcParameters *const  MrcData
  );

/**
  This function runs DDRIO Offset Correction - PreTraining
  (VsxHi FB/FF Offset Correction & VccDLL Per Partition Nbias Vref Offset Correction)

  @param[in, out] MrcData - Include all MRC global data.

  @retval mrcSuccess
**/
MrcStatus
MrcOffsetCorrectionPre (
  IN OUT MrcParameters *const MrcData
  );

/**
  This function trains VccDll for Write, Read and Idle FeedForward timing.
  Idle isnt coded for A0

  @param[in]  MrcData - Pointer to global MRC data.
  @retval MrcStatus - mrcSuccess
**/
MrcStatus
MrcVccDllFFTiming (
  IN  MrcParameters *const  MrcData
  );

/**
  This function trains VccDll Per Module FF Offset Correction

  @param[in]  MrcData - Pointer to global MRC data.
  @retval MrcStatus - mrcSuccess
**/
MrcStatus
MrcVccDllFFOffsetCorrection (
  IN MrcParameters    *const MrcData
  );

#endif //_MrcDdrIoApi_h_
