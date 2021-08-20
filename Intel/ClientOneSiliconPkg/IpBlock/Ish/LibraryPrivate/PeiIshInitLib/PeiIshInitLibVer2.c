/** @file
  ISH Init Library - Ver2 specified functions

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

#include <Library/DebugLib.h>
#include <Library/PchPcrLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/PeiIshLib.h>

#include <Register/IshRegs.h>
#include <Register/PchPcrRegs.h>
#include <Library/PsfLib.h>
#include <Library/PcdLib.h>


/**
  Product level ISH initialization

  @param[in] SiPolicy
**/
VOID
IshSocInit (
  IN  SI_POLICY_PPI    *SiPolicy
  )
{
  // Set BAR1_Disable and PCI_CFG_DISABLE bits by sending SB MSG to ISH Bridge
  //
  PchPcrAndThenOr32 (
    PID_ISHBR,
    R_ISH_PCR_FPAK_PCICFGCTRL,
    ~0u,
    (B_ISH_PCR_PCICFGCTRL_BAR1DIS | B_ISH_PCR_PCICFGCTRL_PCI_CFG_DIS)
    );

  //
  // Read back FPAK PCICFGCTRL register to enforce Sideband/primary ordering
  //
  PchPcrRead32 (PID_ISHBR, R_ISH_PCR_FPAK_PCICFGCTRL);
}
