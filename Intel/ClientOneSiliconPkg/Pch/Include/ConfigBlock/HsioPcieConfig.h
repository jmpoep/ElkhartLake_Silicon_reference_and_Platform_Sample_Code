/** @file
  HSIO pcie policy

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2016 Intel Corporation.

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
#ifndef _HSIO_PCIE_CONFIG_H_
#define _HSIO_PCIE_CONFIG_H_

#define HSIO_PCIE_PREMEM_CONFIG_REVISION 1
extern EFI_GUID gHsioPciePreMemConfigGuid;

#pragma pack (push,1)

/**
  The PCH_HSIO_PCIE_LANE_CONFIG describes HSIO settings for PCIe lane
**/
typedef struct {
  //
  // HSIO Rx Eq
  // Refer to the EDS for recommended values.
  // Note that these setting are per-lane and not per-port
  //
  UINT32  HsioRxSetCtleEnable           : 1;      ///< <b>0: Disable</b>; 1: Enable PCH PCIe Gen 3 Set CTLE Value
  UINT32  HsioRxSetCtle                 : 6;      ///< PCH PCIe Gen 3 Set CTLE Value
  UINT32  HsioTxGen1DownscaleAmpEnable  : 1;      ///< <b>0: Disable</b>; 1: Enable PCH PCIe Gen 1 TX Output Downscale Amplitude Adjustment value override
  UINT32  HsioTxGen1DownscaleAmp        : 6;      ///< PCH PCIe Gen 1 TX Output Downscale Amplitude Adjustment value
  UINT32  HsioTxGen2DownscaleAmpEnable  : 1;      ///< <b>0: Disable</b>; 1: Enable PCH PCIe Gen 2 TX Output Downscale Amplitude Adjustment value override
  UINT32  HsioTxGen2DownscaleAmp        : 6;      ///< PCH PCIe Gen 2 TX Output Downscale Amplitude Adjustment value
  UINT32  HsioTxGen3DownscaleAmpEnable  : 1;      ///< <b>0: Disable</b>; 1: Enable PCH PCIe Gen 3 TX Output Downscale Amplitude Adjustment value override
  UINT32  HsioTxGen3DownscaleAmp        : 6;      ///< PCH PCIe Gen 3 TX Output Downscale Amplitude Adjustment value
  UINT32  RsvdBits0                     : 4;      ///< Reserved Bits

  UINT32  HsioTxGen1DeEmphEnable        : 1;      ///< <b>0: Disable</b>; 1: Enable PCH PCIe Gen 1 TX Output De-Emphasis Adjustment Setting value override
  UINT32  HsioTxGen1DeEmph              : 6;      ///< PCH PCIe Gen 1 TX Output De-Emphasis Adjustment Setting
  UINT32  HsioTxGen2DeEmph3p5Enable     : 1;      ///< <b>0: Disable</b>; 1: Enable PCH PCIe Gen 2 TX Output -3.5dB Mode De-Emphasis Adjustment Setting value override
  UINT32  HsioTxGen2DeEmph3p5           : 6;      ///< PCH PCIe Gen 2 TX Output -3.5dB Mode De-Emphasis Adjustment Setting
  UINT32  HsioTxGen2DeEmph6p0Enable     : 1;      ///< <b>0: Disable</b>; 1: Enable PCH PCIe Gen 2 TX Output -6.0dB Mode De-Emphasis Adjustment Setting value override
  UINT32  HsioTxGen2DeEmph6p0           : 6;      ///< PCH PCIe Gen 2 TX Output -6.0dB Mode De-Emphasis Adjustment Setting
  UINT32  RsvdBits1                     : 11;     ///< Reserved Bits
} PCH_HSIO_PCIE_LANE_CONFIG;

///
/// The PCH_HSIO_PCIE_CONFIG block describes the configuration of the HSIO for PCIe lanes
///
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                   ///< Config Block Header
  ///
  /// These members describe the configuration of HSIO for PCIe lanes.
  ///
  PCH_HSIO_PCIE_LANE_CONFIG         Lane[PCH_MAX_PCIE_ROOT_PORTS];
} PCH_HSIO_PCIE_PREMEM_CONFIG;

#pragma pack (pop)

#endif // _HSIO_PCIE_LANE_CONFIG_H_
