/** @file
  Hsio Sata policy

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
#ifndef _HSIO_SATA_CONFIG_H_
#define _HSIO_SATA_CONFIG_H_

#define HSIO_SATA_PREMEM_CONFIG_REVISION 1
extern EFI_GUID gHsioSataPreMemConfigGuid;

#pragma pack (push,1)

/**
  The PCH_HSIO_SATA_PORT_LANE describes HSIO settings for SATA Port lane
**/
typedef struct {
  //
  // HSIO Rx Eq
  //
  UINT32  HsioRxGen1EqBoostMagEnable   : 1;       ///< <b>0: Disable</b>; 1: Enable Receiver Equalization Boost Magnitude Adjustment Value override
  UINT32  HsioRxGen1EqBoostMag         : 6;       ///< SATA 1.5 Gb/sReceiver Equalization Boost Magnitude Adjustment value
  UINT32  HsioRxGen2EqBoostMagEnable   : 1;       ///< <b>0: Disable</b>; 1: Enable Receiver Equalization Boost Magnitude Adjustment Value override
  UINT32  HsioRxGen2EqBoostMag         : 6;       ///< SATA 3.0 Gb/sReceiver Equalization Boost Magnitude Adjustment value
  UINT32  HsioRxGen3EqBoostMagEnable   : 1;       ///< <b>0: Disable</b>; 1: Enable Receiver Equalization Boost Magnitude Adjustment Value override
  UINT32  HsioRxGen3EqBoostMag         : 6;       ///< SATA 6.0 Gb/sReceiver Equalization Boost Magnitude Adjustment value
  //
  // HSIO Tx Eq
  //
  UINT32  HsioTxGen1DownscaleAmpEnable : 1;       ///< <b>0: Disable</b>; 1: Enable SATA 1.5 Gb/s TX Output Downscale Amplitude Adjustment value override
  UINT32  HsioTxGen1DownscaleAmp       : 6;       ///< SATA 1.5 Gb/s TX Output Downscale Amplitude Adjustment value
  UINT32  RsvdBits0                    : 4;       ///< Reserved bits

  UINT32  HsioTxGen2DownscaleAmpEnable : 1;       ///< <b>0: Disable</b>; 1: Enable SATA 3.0 Gb/s TX Output Downscale Amplitude Adjustment value override
  UINT32  HsioTxGen2DownscaleAmp       : 6;       ///< SATA 3.0 Gb/s TX Output Downscale Amplitude Adjustment
  UINT32  HsioTxGen3DownscaleAmpEnable : 1;       ///< <b>0: Disable</b>; 1: Enable SATA 6.0 Gb/s TX Output Downscale Amplitude Adjustment value override
  UINT32  HsioTxGen3DownscaleAmp       : 6;       ///< SATA 6.0 Gb/s TX Output Downscale Amplitude Adjustment
  UINT32  HsioTxGen1DeEmphEnable       : 1;       ///< <b>0: Disable</b>; 1: Enable SATA 1.5 Gb/s TX Output De-Emphasis Adjustment Setting value override
  UINT32  HsioTxGen1DeEmph             : 6;       ///< SATA 1.5 Gb/s TX Output De-Emphasis Adjustment Setting

  UINT32  HsioTxGen2DeEmphEnable       : 1;       ///< <b>0: Disable</b>; 1: Enable SATA 3.0 Gb/s TX Output De-Emphasis Adjustment Setting value override
  UINT32  HsioTxGen2DeEmph             : 6;       ///< SATA 3.0 Gb/s TX Output De-Emphasis Adjustment Setting
  UINT32  RsvdBits1                    : 4;       ///< Reserved bits

  UINT32  HsioTxGen3DeEmphEnable       : 1;       ///< <b>0: Disable</b>; 1: Enable SATA 6.0 Gb/s TX Output De-Emphasis Adjustment Setting value override
  UINT32  HsioTxGen3DeEmph             : 6;       ///< SATA 6.0 Gb/s TX Output De-Emphasis Adjustment Setting value override
  UINT32  RsvdBits2                    : 25;      ///< Reserved bits
} PCH_HSIO_SATA_PORT_LANE;

///
/// The PCH_HSIO_SATA_CONFIG block describes the HSIO configuration of the SATA controller.
///
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                   ///< Config Block Header
  ///
  /// These members describe the configuration of HSIO for SATA lanes.
  ///
  PCH_HSIO_SATA_PORT_LANE        PortLane[PCH_MAX_SATA_PORTS];
} PCH_HSIO_SATA_PREMEM_CONFIG;

#pragma pack (pop)

#endif // _HSIO_SATA_CONFIG_H_
