/** @file
  MRC Common / Generic functions

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
#ifndef _MrcGeneral_h_
#define _MrcGeneral_h_

#include "MrcApi.h"
#include "MrcAddressDecodeConfiguration.h"
#include "MrcCommon.h"
#include "MrcCrosser.h"
#include "MrcDebugHook.h"
#include "MrcPowerModes.h"
#include "MrcSpdProcessing.h"
#include "MrcMemoryMap.h"
#include "MrcGlobal.h"

#define PCH_PWRM_BASE_ADDRESS                       0xFE000000     ///< PMC MBAR MMIO base address
#define R_PCH_PWRM_GEN_PMCON_A                      0x1020
#define B_PCH_PWRM_GEN_PMCON_A_MEM_SR_MRC           MRC_BIT21
#define B_PCH_PWRM_GEN_PMCON_A_DISB_MRC             MRC_BIT23

#define RX_ANALOG_GRACE_COUNT_GUARDBAND             (8)
///
/// Define the total memory size of a channel, see CAPID0_A.DDRSZ
///
typedef enum {
  tcs64GB,  ///< 64 GB per channel (Unlimited)
  tcs8GB,   ///< 8 GB
  tcs4GB,   ///< 4 GB
  tcs2GB    ///< 2 GB
} MrcTotalChannelSize;


/**
  This function changes the MC to normal mode, enables the ECC if needed, lock configuration and set PU_MRC_Done.
  If the ECC is enabled, this function should be called after memory is cleaned.

  @param[in, out] MrcData - Include all MRC global data.

  @retval Always returns mrcSuccess.
**/
extern
MrcStatus
MrcMcActivate (
  IN OUT MrcParameters *const MrcData
  );

/**
  Program MC/CPGC engines to either Normal mode of operation
  or CPGC training mode.

  @param[in] MrcData  - The MRC general data.
  @param[in] Mode     - TRUE for Normal mode, FALSE for CPGC mode

  @retval Always returns mrcSuccess.
**/
void
MrcSetNormalMode (
  IN MrcParameters *const MrcData,
  IN BOOLEAN              Mode
  );

/**
  This function enables Normal Mode and configures the Power Down Modes
  for the boot flows other than Cold Boot.

  @param[in] MrcData - The MRC general data.

  @retval Always returns mrcSuccess.
**/
extern
MrcStatus
MrcNormalMode (
  IN MrcParameters *const MrcData
  );

/**
  Clear Delta DQS before switching SA GV point

  @param[in] MrcData - include all the MRC general data.
**/
void
MrcClearDeltaDqs (
  IN     MrcParameters *const MrcData
  );

/**
  Early MRC overrides of input parameters.
  This is called at the very beginning of MRC, so DDR type is not known yet.

  @param[in]  MrcData - Pointer to global MRC data.

  @retval - mrcSuccess
**/
MrcStatus
MrcEarlyOverrides (
  IN  MrcParameters *const  MrcData
  );

/**
  This function will override MRC Inputs based on current safe configuration.
  Called if MrcSafeConfig is TRUE.
  These overrides don't depend on DDR type because we don't know it yet.
  Overrides that depend on DDR type will be done during SPD Processing in MrcMcCapabilityPreSpd() below in this file.

  @param[in]  MrcData - Pointer to global MRC data.

  @retval - mrcSuccess
**/
MrcStatus
MrcSafeMode (
  IN  MrcParameters *const  MrcData
  );

/**
  SA GV flow

  @param[in] MrcData - include all the MRC general data.

  @retval mrcStatus if succeeded.
**/
MrcStatus
MrcSaGvSwitch (
  IN     MrcParameters *const MrcData
  );

/**
  SA GV flow for the Fixed mode.

  @param[in] MrcData  - include all the MRC general data.
  @param[in] SaGvMode - The SAGV mode to be fixed to.

  @retval mrcStatus if succeeded.
**/
MrcStatus
MrcSetSaGvFixed (
  IN  MrcParameters *const MrcData,
  IN  MrcSaGv              SaGvMode
  );

/**
  This function is the last function that call from the MRC core.
  The function set DISB and set the MRC_Done.

  @param[in, out] MrcData - include all the MRC general data.

  @retval Always returns mrcSuccess.
**/
extern
MrcStatus
MrcDone (
  IN OUT MrcParameters *const MrcData
  );

/**
Enables IBECC if supported

@param[in] *MrcData - Pointer to the MRC Debug structure.

@retval Returns mrcSuccess if the Ibecc is enabled
**/
MrcStatus
MrcIbecc (
  IN MrcParameters *MrcData
);

/**
  This function set the MRC vertion to MCDECS_SPARE register.
  The function need to be call by the wrapper after MrcStartMemoryConfiguration function where the MC CLK enable.
  The function write:
  - Major number to bits 16-23
  - Minor number to bits 8-15
  - Build number to bits 0 - 7

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess - Return success.
**/
extern
MrcStatus
MrcSetMrcVersion (
  IN     MrcParameters *const MrcData
  );

/**
  This function locks the memory controller and memory map registers.

  @param[in] MrcData - Include all MRC global data.
**/
extern
void
McRegistersLock (
  IN     MrcParameters *const MrcData
  );

/**
  This function sets the DISB bit in General PM Configuration 2 B:D:F 0,31,0 offset 0xA2.
**/
extern
void
MrcSetDISB (
  IN MrcParameters * const MrcData
  );

/**
  This function reads the CAPID0 register and sets the memory controller's capability.

  @param[in, out] MrcData - All the MRC global data.

  @retval Returns mrcSuccess if the memory controller's capability has been determined, otherwise returns mrcFail.
**/
extern
MrcStatus
MrcMcCapability (
  IN OUT MrcParameters *const MrcData
  );

/**
  This function reads the CAPID0 register and sets the memory controller's capability.

  @param[in, out] MrcData - All the MRC global data.

  @retval Returns mrcSuccess if the memory controller's capability has been determined, otherwise returns mrcFail.
**/
MrcStatus
MrcMcCapabilityPreSpd (
  IN OUT MrcParameters *const MrcData
  );

/**
  This function reads the input data structure and sets the appropriate timing overrides in the output structure.

  @param[in, out] MrcData - All the MRC global data.

  @retval Returns mrcSuccess if the timing overrides have been conpleted.
**/
extern
MrcStatus
MrcSetOverrides (
  IN OUT MrcParameters *const MrcData
  );

/**
  This function fills the scratch registers
  [DDRDATAxCHx_CR_DATATRAINFEEDBACK_REG] with MR data per rank and channel.
  These MRs are copied from the host structure.
  It also logs the final MR values and saves MR registers to MRS FSM for SA GV.

  ------------------- DDR4 ------------------------
  Note: DDR4 values are for Byte 0 only
  Per channel:
   DDRDATA0CHx_CR_DATATRAINFEEDBACK    [MR1_Rank0, MR0_Rank0] (31-16, 15-0)
   DDRDATA1CHx_CR_DATATRAINFEEDBACK    [MR1_Rank1, MR0_Rank1] (31-16, 15-0)
   DDRDATA2CHx_CR_DATATRAINFEEDBACK    [MR1_Rank2, MR0_Rank2] (31-16, 15-0)
   DDRDATA3CHx_CR_DATATRAINFEEDBACK    [MR1_Rank3, MR0_Rank3] (31-16, 15-0)
   DDRDATA4CHx_CR_DATATRAINFEEDBACK    [MR2_Rank1, MR2_Rank0] (31-16, 15-0)
   DDRDATA5CHx_CR_DATATRAINFEEDBACK    [MR2_Rank3, MR2_Rank2] (31-16, 15-0)

  @param[in] MrcData - The global host structure
  @retval mrcSuccess.
**/
MrcStatus
MrcFillMrScratchRegs (
  IN     MrcParameters *const MrcData
  );

/**
  Enable/Disable DLL WeakLock if needed.
  Note: We don't enable it in McConfig because CKE is still low during that step.

  @param[in] MrcData - The MRC general data.
  @param[in]  Enable - BOOLEAN control to enable (if TRUE), or disable (if FALSE) WeakLock.

  @retval None
**/
void
MrcWeaklockEnDis (
  IN MrcParameters *const MrcData,
  IN BOOLEAN              Enable
  );

#ifdef MRC_DEBUG_PRINT
/**
  Print the input parameters to the debug message output port.

  @param[in] MrcData - The MRC global data.

  @retval mrcSuccess
**/
extern
MrcStatus
MrcPrintInputParameters (
  MrcParameters * const MrcData
  );

/**
  Print the specified memory to the serial message debug port.

  @param[in] Debug - Serial message debug structure.
  @param[in] Start - The starting address to dump.
  @param[in] Size  - The amount of data in bytes to dump.
**/
extern
void
MrcPrintMemory (
  IN MrcDebug *const    Debug,
  IN const UINT8 *const Start,
  IN const UINT32       Size
  );
#endif


/**
  Sets CpuModel and CpuStepping in MrcData based on CPUID values.

  @param[out] MrcData     - The Mrc Host data structure
  @param[in]  CpuModel    - The CPU Family Model.
  @param[in]  CpuStepping - The CPU Stepping.

  @retval mrcSuccess if the model and stepping is found.  Otherwise mrcFail
**/
MrcStatus
MrcSetCpuInformation (
  OUT MrcParameters  *MrcData,
  IN  MrcCpuModel    CpuModel,
  IN  MrcCpuStepping CpuStepping
  );

#endif
