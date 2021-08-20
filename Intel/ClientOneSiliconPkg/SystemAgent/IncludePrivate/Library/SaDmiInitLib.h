/** @file
  Header file for the SA Dmi Init library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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
#ifndef _SA_DMI_PEIM_H_
#define _SA_DMI_PEIM_H_

#include <Library/PeiPchDmiLib.h>
#include <Library/PcdLib.h>

///
/// Driver Consumed PPI Prototypes
///
#include <SaPolicyCommon.h>

#define BUNDLE_STEP   0x20

/**
  Initialize DMI.

  @param[in] PciePeiPreMemConfig           - Instance of PCIE_PEI_PREMEM_CONFIG

  @retval EFI_SUCCESS
**/
EFI_STATUS
DmiInit (
  IN       PCIE_PEI_PREMEM_CONFIG       *PciePeiPreMemConfig
  );

/**
  Initialize DMI Tc/Vc mapping through SA-PCH.

  @param[in] PciePeiPreMemConfig           - Instance of PCIE_PEI_PREMEM_CONFIG

  @retval EFI_SUCCESS
**/
EFI_STATUS
SaDmiTcVcInit (
#if FixedPcdGetBool(PcdCpuPcieEnable) == 1
  IN       PCIE_PEI_PREMEM_CONFIG                  *PciePeiPreMemConfig
#endif
  );

/**
  Map SA DMI TCs to VC

  @param[in] PchDmiTcVcMap        - Instance of PCH_DMI_TC_VC_MAP
  @param[in] DmiBar               - DMIBAR address

  @retval EFI_SUCCESS
**/
EFI_STATUS
SaSetDmiTcVcMapping (
  IN    PCH_DMI_TC_VC_MAP  *PchDmiTcVcMap,
  IN    UINT64             DmiBar
  );

/**
  Poll SA DMI negotiation completion

  @param[in] PchDmiTcVcMap        - Instance of PCH_DMI_TC_VC_MAP
  @param[in] DmiBar               - DMIBAR address

  @retval EFI_SUCCESS
**/
EFI_STATUS
SaPollDmiVcStatus (
  IN    PCH_DMI_TC_VC_MAP  *PchDmiTcVcMap,
  IN    UINT64             DmiBar
  );

/**
  DMI link training

  @param[in] DmiBar - DMIBAR address
**/
VOID
DmiLinkTrain (
  IN  UINT64 DmiBar
  );


/**
  DMI Max Payload Size Init

  @param[in] PciePeiPreMemConfig - Pointer to PCIE_PEI_PREMEM_CONFIG
**/
VOID
MaxPayloadSizeInit (
  IN PCIE_PEI_PREMEM_CONFIG          *PciePeiPreMemConfig
  );

/**
  Set SB Min Duration
**/
VOID
SetSbMin (
  VOID
  );


 /**
  Configure DMI nFTS

  @param[in] DmiBar                 - DMIBAR address
**/
VOID DmiConfigureNFts (
  IN UINT64                   Dmibar
);


#endif
