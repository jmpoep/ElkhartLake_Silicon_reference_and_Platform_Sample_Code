/** @file
  This files contains PCH DMI services for RCs usage

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

#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/ConfigBlockLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/PchPcrLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PeiPchDmiLib.h>
#include <Register/PchDmiRegs.h>
#include <Register/PchPcrRegs.h>

#include "PchDmi14.h"
#include "PchDmi15.h"

/**
  Get PCH default TC VC Mapping settings. This funciton returns the default PCH setting
  System Agent can update the settings according to polices.

  @param[in, out] PchDmiTcVcMap         Buffer for PCH_DMI_TC_VC_MAP instance.

**/
VOID
PchDmiTcVcMapInit (
  IN OUT  PCH_DMI_TC_VC_MAP             *PchDmiTcVcMap
  )
{
  if (PchDmiTcVcMap == NULL) {
    return;
  }

  PchDmiTcVcMap->DmiTc[PchDmiVcTypeVc0].Vc   = PchDmiVcTypeVc0;
  PchDmiTcVcMap->DmiTc[PchDmiVcTypeVc0].TcId = 0;
  PchDmiTcVcMap->DmiTc[PchDmiVcTypeVc1].Vc   = PchDmiVcTypeVc1;
  PchDmiTcVcMap->DmiTc[PchDmiVcTypeVc1].TcId = 1;
  PchDmiTcVcMap->DmiTc[PchDmiVcTypeVcm].Vc   = PchDmiVcTypeVcm;
  PchDmiTcVcMap->DmiTc[PchDmiVcTypeVcm].TcId = 7;

  PchDmiTcVcMap->DmiVc[0].Enable          = TRUE;
  PchDmiTcVcMap->DmiVc[0].VcId            = 0;
  PchDmiTcVcMap->DmiVc[1].Enable          = TRUE;
  PchDmiTcVcMap->DmiVc[1].VcId            = 1;
  PchDmiTcVcMap->DmiVc[2].Enable          = TRUE;
  PchDmiTcVcMap->DmiVc[2].VcId            = 7;
}

/**
  Programing transaction classes of the corresponding virtual channel and Enable it

  @param[in] Vc                   The virtual channel number for programming
  @param[in] VcId                 The Identifier to be used for this virtual channel
  @param[in] VcMap                The transaction classes are mapped to this virtual channel.
                                  When a bit is set, this transaction class is mapped to the virtual channel

  @retval EFI_INVALID_PARAMETER   Invalid parameter.
  @retval EFI_SUCCESS             The function completed successfully
**/
STATIC
VOID
SetPchDmiTcVcMapping (
  IN   PCH_DMI_VC_TYPE  Vc,
  IN   UINT8            VcId,
  IN   UINT8            VcMap
  )
{
  UINT32         VxCtlAnd;
  UINT32         VxCtlOr;
  UINT16         VcCtlAddress;
  UINT16         VcStsAddress;

  if (IsPchWithPdmi ()) {
    PchDmi15VcRegs (Vc, &VcCtlAddress, &VcStsAddress);
  } else {
    PchDmi14VcRegs (Vc, &VcCtlAddress, &VcStsAddress);
  }

  VxCtlAnd  = (UINT32) (~(B_PCH_DMI_PCR_V1CTL_ID | V_PCH_DMI_PCR_V1CTL_TVM_MASK));
  VxCtlOr   = ((UINT32) VcId << N_PCH_DMI_PCR_V1CTL_ID) & B_PCH_DMI_PCR_V1CTL_ID;
  VxCtlOr |= (UINT32) VcMap;
  VxCtlOr |= B_PCH_DMI_PCR_V1CTL_EN;

  PchPcrAndThenOr32 (PID_DMI, VcCtlAddress, VxCtlAnd, VxCtlOr);
  //
  // Reads back for posted write to take effect
  // Read back is done in PchPcr lib
  //
}

/**
  Polling negotiation status of the corresponding virtual channel

  @param[in] Vc                   The virtual channel number for programming

  @retval EFI_INVALID_PARAMETER   Invalid parameter.
  @retval EFI_SUCCESS             The function completed successfully
**/
STATIC
VOID
PollPchDmiVcStatus (
  IN PCH_DMI_VC_TYPE   Vc
  )
{
  UINT16         VcCtlAddress;
  UINT16         VcStsAddress;

  if (IsPchWithPdmi ()) {
    PchDmi15VcRegs (Vc, &VcCtlAddress, &VcStsAddress);
  } else {
    PchDmi14VcRegs (Vc, &VcCtlAddress, &VcStsAddress);
  }

  //
  // Wait for negotiation to complete
  //
  while ((PchPcrRead16 (PID_DMI, VcStsAddress) & B_PCH_DMI_PCR_V1STS_NP) != 0) {
  }
}


/**
  The function performing TC/VC mapping program, and poll all PCH Virtual Channel
  until negotiation completion.

  @param[in] PchDmiTcVcMap              Buffer for PCH_DMI_TC_VC_MAP instance.

  @retval EFI_SUCCESS                   The function completed successfully
  @retval Others                        All other error conditions encountered result in an ASSERT.
**/
EFI_STATUS
PchDmiTcVcProgPoll (
  IN  PCH_DMI_TC_VC_MAP                 *PchDmiTcVcMap
  )
{
  PCH_DMI_VC_TYPE         Index;
  UINT8                   VcMap[PchDmiVcTypeMax];

  ZeroMem (VcMap, PchDmiVcTypeMax);

  ///
  /// Set the TC/VC mappings
  ///
  for (Index = 0; Index < PchDmiTcTypeMax; Index++) {
    DEBUG ((DEBUG_INFO, "TC:%0x VC:%0x!\n", PchDmiTcVcMap->DmiTc[Index].TcId, PchDmiTcVcMap->DmiTc[Index].Vc));
    VcMap[PchDmiTcVcMap->DmiTc[Index].Vc] |= (BIT0 << PchDmiTcVcMap->DmiTc[Index].TcId);
  }

  for (Index = 0; Index < PchDmiVcTypeMax; Index++) {
    DEBUG ((DEBUG_INFO, "VC:%0x VCID:%0x Enable:%0x!\n",Index, PchDmiTcVcMap->DmiVc[Index].VcId, PchDmiTcVcMap->DmiVc[Index].Enable));
    if (PchDmiTcVcMap->DmiVc[Index].Enable == TRUE) {
      SetPchDmiTcVcMapping (
        Index,
        PchDmiTcVcMap->DmiVc[Index].VcId,
        VcMap[Index]
        );
    }
  }

  ///
  /// After both above and System Agent DMI TC/VC mapping are programmed,
  /// poll VC negotiation pending status until is zero:
  ///
  for (Index = 0; Index < PchDmiVcTypeMax; Index++) {
    if (PchDmiTcVcMap->DmiVc[Index].Enable == TRUE) {
      PollPchDmiVcStatus (Index);
    }
  }

  return EFI_SUCCESS;
}

/**
  The function set the Target Link Speed in PCH to DMI GEN 3.

  @param[in] TargetLinkSpeed        Target Link Speed
                                    2: GEN2
                                    3: GEN3
**/
VOID
PchDmiSetTargetLinkSpeed (
  IN  UINT8                 TargetLinkSpeed
  )
{
  if (IsPchWithPdmi ()) {
    PchDmi15SetTargetLinkSpeed (TargetLinkSpeed);
  }
}
