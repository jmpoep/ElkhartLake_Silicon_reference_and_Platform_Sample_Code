/** @file
  This file contains functions that initializes PCI Express Root Ports of CPU PCIe.

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
#include <Library/PeiCpuPciePreMemRpInitLib.h>
#include <SaDataHob.h>
#include <Library/CpuPcieRpLib.h>
#include <Library/PeiPchPcieClocksLib.h>
#include <Library/CpuPcieInfoLib.h>
#include <Library/PeiCpuPcieDekelInitLib.h>
#include <Register/CpuPcieRegs.h>
#include <Library/GpioPrivateLib.h>
#include <CpuPcieInfo.h>
#include <Library/TimerLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/PeiServicesLib.h>

/**
  Initialize the CPU PciExpress in PEI

  @param[in] IN SA_MISC_PEI_PREMEM_CONFIG MiscPeiPreMemConfig to access Platform relevant information
  @param[in] IN PCIE_PEI_PREMEM_CONFIG    PciePeiPreMemConfig to access the PCIe Config related information
**/
VOID
EFIAPI
PciExpressInit (
  IN  CPU_PCIE_RP_PREMEM_CONFIG     *CpuPcieRpPreMemConfig
  )
{
  return;
}


