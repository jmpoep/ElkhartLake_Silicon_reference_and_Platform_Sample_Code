/** @file
  The physical memory map configuration definitions.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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
#ifndef _MrcMemoryMap_h_
#define _MrcMemoryMap_h_

#include "MrcTypes.h"
#include "MrcApi.h"
#include "McAddress.h"
#include "MrcCommon.h"

#define MEM_4GB   (0x1000)  ///< Define the 4GB size in 1MB units (1000MB = 1GB).
#define MEM_128MB 128       ///< Define the 128MB size in 1MB units

/**
  After BIOS determines the total physical memory size.
  Determines TOM which is defined by the total physical memory size.
  Determines TOM minus the ME memory size. The ME memory size is calculated from MESEG_BASE and MESEG_MASK.
  Determines MMIO allocation, which is system configuration dependent.

  Determines TOLUD which is the minimum value by comparing between "4GB minus MMIO size" and "TOM minus ME size".
  Determines Graphics Stolen Base, BDSM by subtracting the graphics data stolen memory size from TOLUD.
  Graphics Data Stolen Memory size is given by GMS field in GGC register.  It must be define before this stage.
  Determines Graphics GTT Stolen Base, BGSM by subtracting the GTT graphics stolen memory size from BDSM.
  GTT Stolen Memory size is given by GGMS field in GGC register.  It must be define before this stage.
  Determines TSEG Base, TSEGMB by subtracting TSEG size from BGSM.
  TSEG should be defined.
  Remove the memory hole caused by aligning TSEG to a 8MB boundary.
  Determine whether Memory Reclaim is available.  If "TOM minus ME Stolem Memory Size" is greater than the value of TOLUD, then memory reclaim is available to enable.
  Determine REMAPBASE if reclaim is enabled.  This is the maximum value by comparing between 4GB and "TOM minus ME size".
  Determine REMAPLIMIT () if reclaim is enabled.  This is the value of REMAPBASE plus "the difference between the value in TOLUD register and the lower of either 4GB or 'TOM minus ME Stolen memory size", and then minus 1 boundary.
  Determine TOUUD. TOUUD indicates the address one byte above the maximum DRAM.  If relcaim is disabled, this value is calculated by "TOM minus ME stolen size".  Otherwise, this value is set to REMAPLIMIT plus 1MB.

  @param[in, out] MrcData - Include all MRC global data. include also the memory map data.

  @retval MrcStatus -  if the reset is succeded.
**/
extern
MrcStatus
MrcSetMemoryMap (
  MrcParameters *const MrcData
  );

/**
  This function find the total memory in the system.
  and write it to TotalPhysicalMemorySize in MrcData structure.

  @param[in, out] MrcData - Include all MRC global data.

  @retval Nothing
**/
extern
void
MrcTotalMemory (
  MrcParameters *const MrcData
  );

/**
  this function write to the memory init registers.

  @param[in] PciEBaseAddress  - Address of the PCI Express BAR
  @param[in] MemoryMap        - Include all the memory map definitions

  @retval Nothing
**/
extern
void
UpdateMemoryMapRegisters (
  IN OUT MrcParameters  *const MrcData,
  IN const UINT32              PciEBaseAddress,
  IN const MrcMemoryMap *const MemoryMap
  );

/**
  Input parameter for Bit Error Recovery Address compared against Memory Map

  @param[in, out] MrcData  - The MRC "global data" area.
  @param[in]      Address  - UINT64 Address to be compared against Memory Map

  @retval mrcSuccess if Address is within Memory Map and mrcFail if Address is outside Memory Map
**/
MrcStatus
MrcBitErrRecAddressCompare (
  IN OUT MrcParameters *const MrcData,
  IN     UINT64               Address
  );

#endif // _MrcMemoryMap_h_
