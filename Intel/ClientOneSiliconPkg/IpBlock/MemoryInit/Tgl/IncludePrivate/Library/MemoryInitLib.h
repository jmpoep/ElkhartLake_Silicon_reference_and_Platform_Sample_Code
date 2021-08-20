/** @file
  Memory Initialization library API.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2017 Intel Corporation.

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
#ifndef _MEMORY_INIT_LIB_H_
#define _MEMORY_INIT_LIB_H_

/**
  <b>Entry point of MemoryInit library</b>
  This function will invoke main memory detection code after the required dependencies satisified.
  - <b>Introduction</b> \n
    The Memory Reference Code (MRC) for Broadwell configures the Broadwell System Agent Memory controller and performs DRAM initialization tasks (MRC is included in System Agent Reference Code package and is not released separately).
    Please refer to the Framework Client BIOS Broadwell Memory Reference Code Porting Guide for detailed porting information.
    Please refer the MRC_ReleaseNote for MRC release and version information.
    MemoryInit PEIM is required by all systems supporting Intel Broadwell.

  - @pre
    - _SI_SA_POLICY_PPI: A PPI published by a platform PEIM executed earlier; documented in this chapter as well.
    - @link SA_PEI_INIT_PPI_GUID @endlink (@link gSaPeiInitPpiGuid @endlink): A PPI published by SA Init PEIM executed earlier.
    - PEI_SMBUS_PPI: A PPI published by PCH SMBUS PEIM executed earlier.
    - @link PEI_TXT_MEMORY_UNLOCKED_PPI_GUID @endlink (@link gPeiTxtMemoryUnlockedPpiGuid @endlink): A PPI published by TXT PEIM executed earlier (Conditional if TXT support is enabled).
    - PEI_STALL_PPI: A PPI published by SB PEI executed earlier (Conditional if TXT support is enabled).
    - PCH_ME_UMA_PPI: A PPI published by ME PEIM (PchMeUma) executed earlier (Conditional if ME support is enabled, refer to ME Ref. Code package).
    - WDT_PPI (_WDT_PROTOCOL): A PPI published by PCH PEIM executed earlier.
    - _SI_CPU_POLICY_PPI: A PPI published by CPU PEIM executed earlier.
    - PEI_MASTER_BOOT_MODE_PEIM_PPI: A PPI published by foundation to get bootmode executed earlier. This PPI is the last dependency of the notify PPI registration to perform MemoryInit.

  - @result
    System Agent Memory Controller is configured and DRAM is initialized and ready for EFI to use. EFI memory HOBs are installed, and on non S3 resume path, S3 Restore Data are saved to Hob. \n

  - <b>Integration Checklist</b> \n
    Note: Not all of the memory range options are properly handled by the current implementation, previous known implementation, and subsequent resource configuration modules. Please be very careful and verify expected implementation behavior when using this interface. For example PCI memory mask is not currently handled by wrapper and PCI memory use is determined by PciHostBridge driver.
    - Ensure that your platform is publishing the SI_SA_POLICY_PPI on all boot paths
    - Ensure that your platform is publishing the _PEI_CAPSULE_PPI on the capsule update boot path
    - Ensure that your platform is publishing the PEI_READ_ONLY_VARIABLE_PPI on the S3 resume path
    - Verify SMRAM initialization and configuration
    - If TXT feature is required and implemented, @link PEI_TXT_MEMORY_UNLOCKED_PPI_GUID @endlink (@link gPeiTxtMemoryUnlockedPpiGuid @endlink) should be added as dependency.
**/
EFI_STATUS
EFIAPI
InstallMrcCallback (
  VOID
  );

#endif
