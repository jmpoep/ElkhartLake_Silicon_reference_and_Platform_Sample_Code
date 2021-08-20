/** @file
  This module contains functions to configure and use Memory Controller
  maintenance features.

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
#ifndef _MrcMaintenance_h_
#define _MrcMaintenance_h_

/**
  This function will disable the DQS Oscillator maintenance feature in the Memory Controller.

  @params[in] MrcData - Pointer to MRC global data.
**/
VOID
MrcDisableDqsOscillatorMc (
  IN  MrcParameters * const MrcData
  );

/**
  This function executes the requested ZQ command.
  This function will wait the appropriate wait time as specified in the JEDEC spec.
  ZQ is sent to all populated controllers, channels, and ranks.

  @param[in]  MrcData   - Pointer to MRC global data.
  @param[in]  ChBitMask - Bit mask of channels to run.

  @retval MrcStatus - mrcSuccess if successful, else an error status.
**/
MrcStatus
MrcSendZq (
  IN  MrcParameters *const  MrcData
  );

/**
  Issue ZQ calibration command on all populated controller, channels and ranks.
  When done, wait appropriate delay depending on the ZQ type.

  @param[in] MrcData  - include all the MRC data
  @param[in] ZqType   - Type of ZQ Calibration: see MrcZqType enum

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status
**/
MrcStatus
MrcIssueZQ (
  IN  MrcParameters *const  MrcData,
  IN  MrcZqType             ZqType
  );

/**
  Issue DDR4 MRS command (PDA Mode)

  @param[in] MrcData         - Include all the MRC general data.
  @param[in] Controller      - Memory Controller Number within the processor (0-based).
  @param[in] Channel         - Channel to send command to
  @param[in] Rank            - Rank to send command to
  @param[in] Address         - MRS data
  @param[in] MR              - MR # to change
  @param[in] DeviceMask      - Devices/Bytes to send MRS data to

  @retval mrcSuccess    - PDA command was sent successfully
  @retval mrcDeviceBusy - Timed out waiting for MRH
**/
MrcStatus
MrcDdr4PdaCmd (
  IN MrcParameters *const MrcData,
  IN UINT32               Controller,
  IN UINT32               Channel,
  IN UINT32               Rank,
  IN UINT16               Address,
  IN UINT8                MR,
  IN UINT16               DeviceMask
  );

/**
  This function provides the initial configuration of the Memory Controller's
  maintenance services.  Some items are disabled during MRC training, and will need
  to be configured at the end of MRC.

  @params[in] MrcData - Pointer to MRC global data.
**/
VOID
MrcMaintenanceConfig (
  IN  MrcParameters * const MrcData
  );

#endif // _MrcMaintenance_h_
