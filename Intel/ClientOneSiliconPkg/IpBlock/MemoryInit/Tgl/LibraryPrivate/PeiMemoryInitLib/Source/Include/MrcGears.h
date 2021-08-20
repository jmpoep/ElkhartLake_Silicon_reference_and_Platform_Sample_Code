/** @file
  This file include all the MRC Gears related algorithms.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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
#ifndef _MrcGears_h_
#define _MrcGears_h_

/**
  This function will setup the fields in MCMISCS_DCCMAINFSMCONTROL0.  Currently adjusting fields:
  ActiveClks, ActiveBytes, dcocompen

  @params[in] MrcData   - Pointer to MRC global data.
  @params[in] IsClock   - Whether this is setup for Clk DCC vs (DQ DCC or DQS DCC).
  @params[in] DcoCompEn - Whether DcoCompEn is set (only is set if both Clock and DcoCompEn are TRUE).

  @retval Nothing
**/
void
MrcDccMainFsmControl0 (
  IN  MrcParameters * const MrcData,
  IN  BOOLEAN         IsClock,
  IN  BOOLEAN         DcoCompEn
  );

/**
  This function will find the first populated channel and read various DCC[CLK/DATA]CONTROL registers for
  that channel (Byte 0 if DATA).

  @params[in]  MrcData       - Pointer to MRC global data.
  @params[in]  Clock         - Whether this is to read from CLK registers or DATA registers
  @params[out] DccControl0   - Pointer to DCC[CLK/DATA]CONTROL0.
  @params[out] DccControl1   - Pointer to DCC[CLK/DATA]CONTROL1.
  @params[out] DccControl3   - Pointer to DCC[CLK/DATA]CONTROL3.
  @params[out] DccControl4   - Pointer to DCC[CLK/DATA]CONTROL4.

  @retval Nothing.
**/
void
MrcDccControlRegsRead (
  IN  MrcParameters * const MrcData,
  IN  BOOLEAN               Clock,
  OUT UINT32                *DccControl0,
  OUT UINT32                *DccControl1,
  OUT UINT32                *DccControl3,
  OUT UINT32                *DccControl4
  );

/**
  This function will setup MCMISCS_DCCCONTROL0 register to kick off Correction FSM and poll on trainingdone field for test completion.

  @params[in] MrcData   - Pointer to MRC global data.

  @retval mrcSuccess if FSM finished test within Timeout, otherwise mrcFail.
**/
MrcStatus
MrcDccRunTest (
  IN  MrcParameters * const MrcData
  );

/**
  This function will do the initial sweeps of the various DCC training steps to populate the Look Up Tables (LUT)

  @params[in] MrcData   - Pointer to MRC global data.

  @retval Success if each DCC training steps was successful, otherwise mrcFail.
**/
MrcStatus
MrcDccInitialization (
  IN  MrcParameters * const MrcData
  );

/**
  This function will do the final setup of the various DCC settings prior to end of either SAGV or MRC.

  @params[in] MrcData   - Pointer to MRC global data.

  @retval mrcSuccess if each DCC final steps was successful, otherwise mrcFail.
**/
MrcStatus
MrcDccFinalization (
  IN  MrcParameters * const MrcData
  );

/**
  This function finalizes the DCC FSM control registers for normal operation.

  @param[in]  MrcData - Pointer to global MRC data.
**/
VOID
MrcDccFsmFinalize (
  IN  MrcParameters * const MrcData
  );

/**
  This function will do the initial sweep of DCC CLK to populate the Look Up Table (LUT)

  @params[in] MrcData   - Pointer to MRC global data.

  @retval mrcSuccess if all tested points was able to finish testing, otherwise mrcFail.
**/
MrcStatus
MrcDccClkInitSweep (
  IN  MrcParameters * const MrcData
  );

/**
  This function will do the initial sweep of DCC DQS to populate the Look Up Table (LUT)

  @params[in] MrcData   - Pointer to MRC global data.

  @retval mrcSuccess if all tested points was able to finish testing, otherwise mrcFail.
**/
MrcStatus
MrcDccDqsInitSweep (
  IN  MrcParameters * const MrcData
  );

/**
  This function will do the initial sweep of DCC DQ Byte

  @params[in] MrcData   - Pointer to MRC global data.

  @retval mrcSuccess if all tested points was able to finish testing, otherwise mrcFail.
**/
MrcStatus
MrcDccDqByteInitSweep (
  IN  MrcParameters * const MrcData
  );

/**
  This function will do the initial sweep of DCC DQ Bit

  @params[in] MrcData   - Pointer to MRC global data.

  @retval mrcSuccess if all tested points was able to finish testing, otherwise mrcFail.
**/
MrcStatus
MrcDccDqBitInitSweep (
  IN  MrcParameters * const MrcData
  );

/**
  This function will update the corresponding stored register values (from LUT) for DCC DQS PI setting

  @params[in] MrcData - Pointer to MRC global data.
  @params[in] Channel - The Channel being adjusted for.
  @params[in] Rank    - The Rank in the Channel being adjusted for.
  @params[in] Strobe  - The Byte in the Rank being adjusted for.
  @params[in] Group   - GetSet group to update.
  @params[in] Value   - The PI setting being adjusted for.
  @params[in] Flush   - TRUE to flush the register cache at end of function or FALSE and let caller take care of this.

  @retval Nothing
**/
void
MrcDccUpdate (
  IN  MrcParameters * const MrcData,
  IN  UINT32                Channel,
  IN  UINT32                Rank,
  IN  UINT32                Strobe,
  IN  GSM_GT        const   Group,
  IN  INT64         *const  Value,
  IN  BOOLEAN               Flush  );

/**
  This function will do the final setup of DCC CLK prior to end of SAGV.

  @params[in] MrcData   - Pointer to MRC global data.

  @retval mrcSuccess if no Timeout occurred, otherwise mrcFail.
**/
MrcStatus
MrcDccClkFinalization (
  IN  MrcParameters * const MrcData
  );

/**
  This function will do the final setup of DCC DQS prior to end of SAGV.

  @params[in] MrcData   - Pointer to MRC global data.

  @retval mrcSuccess if no Timeout occurred, otherwise mrcFail.
**/
MrcStatus
MrcDccDqsFinalization (
  IN  MrcParameters * const MrcData
  );

/**
  This function will do the final setup of the various DCC settings prior to end of SAGV.

  @params[in] MrcData   - Pointer to MRC global data.

  @retval mrcSuccess if each DCC final steps was successful, otherwise mrcFail.
**/
MrcStatus
MrcDccReplica (
  IN  MrcParameters * const MrcData
  );

/**
  This function will do the final setup of the various DCC settings after all SAGV.

  @params[in] MrcData   - Pointer to MRC global data.

  @retval mrcSuccess.
**/
MrcStatus
MrcDccFinalization (
  IN  MrcParameters * const MrcData
  );

/**
  This function will re-initialize DCC...

  @params[in] MrcData   - Pointer to MRC global data.

  @retval mrcSuccess.
**/
MrcStatus
MrcDccReInit (
  IN  MrcParameters * const MrcData
  );

#ifdef MRC_DEBUG_PRINT
/**
  This function will print the Look Up Table results for CLK and/or Tx DQS

  @params[in] MrcData   - Pointer to MRC global data.
  @params[in] ClkDcc    - TRUE to print CLK DCC LUT, otherwise FALSE.
  @params[in] DqsDcc    - TRUE to print TxDqs DCC LUT, otherwise FALSE.
**/
void
MrcDccResultsDebugPrint (
  IN  MrcParameters * const MrcData,
  IN  BOOLEAN               ClkDcc,
  IN  BOOLEAN               DqsDcc
  );
#endif //MRC_DEBUG_PRINT
#endif // _MrcGears_h_
