/** @file
  TCSS PEI PreMem policy

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2019 Intel Corporation.

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
#ifndef _TCSS_PEI_PREMEM_CONFIG_H_
#define _TCSS_PEI_PREMEM_CONFIG_H_

#include <ConfigBlock.h>
#include <SaRegs.h>

#define TCSS_PEI_PREMEM_CONFIG_REVISION 1
extern EFI_GUID gTcssPeiPreMemConfigGuid;

#pragma pack (push,1)

///
/// The TCSS_MISC_PEI_PREMEM_CONFIG block describes MISC settings for TCSS.
///
typedef union {
    UINT32      TcssDevEn;            ///< Maps to bits in TCSS_DEVEN_0_0_0_MCHBAR_IMPH
    struct{
      UINT32    TcssItbtPcie0En:1;
      UINT32    TcssItbtPcie1En:1;
      UINT32    TcssItbtPcie2En:1;
      UINT32    TcssItbtPcie3En:1;
      UINT32    :4;
      UINT32    TcssXhciEn:1;
      UINT32    TcssXdciEn:1;
      UINT32    TcssDma0En:1;
      UINT32    TcssDma1En:1;
      UINT32    :20;
    } TcssDevEnBit;
} TCSS_DEVEN_PEI_PREMEM_CONFIG;

///
/// The TCSS_USBTC_PEI_PERMEM_CONFIG block describes IOM settings for TCSS.
///
typedef struct {
    UINT32     UsbTcPortEn : 4;     ///< bitmap for USB Type C enabled ports
    UINT32     Rsvd : 28;     ///< Reserved bytes for future use
} TCSS_USBTC_PEI_PERMEM_CONFIG;

typedef struct {
  /**
    This is policy to control Multiple Segment setting.
    When Disabled all the iTBT PCIe RP are located at Segment0
    When Enabled all the iTBT PCIe RP are located at Segment1,
    FSP Wrapper need to update PCIEXBAR and PcdPciExpressRegionLength to 512MB
    prior to FspmWrapperPeim.
    <b>0: Disable</b>, 1: Enable
  **/
  UINT8      PcieMultipleSegmentEnabled;
  UINT8      Rsvd[3];     ///< Reserved bytes for future use, align to multiple 4
} TCSS_MISC_PEI_PREMEM_CONFIG;

/**
  This configuration block describes TCSS settings.\n
  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER            Header;     ///< Offset 0-27 Config Block Header
  TCSS_DEVEN_PEI_PREMEM_CONFIG   DevEnConfig;///< TCSS DEVEN
  TCSS_USBTC_PEI_PERMEM_CONFIG   UsbTcConfig;///< USB Type C Port Configuration
  TCSS_MISC_PEI_PREMEM_CONFIG    MiscConfig; ///< The MISC PreMem Config
} TCSS_PEI_PREMEM_CONFIG;

#pragma pack (pop)

#endif /* _TCSS_PEI_PREMEM_CONFIG_H_ */
